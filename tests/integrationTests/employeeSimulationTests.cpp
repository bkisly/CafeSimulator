//
// Created by wojtek on 28.05.22.
//
#define CATCH_CONFIG_MAIN

#include "../catch.hpp"
#include "../../includes/model/helpers/price.h"
#include "../../includes/model/Employee/Employee.h"
#include "../../includes/model/Employee/DbWorkers.h"
#include "../../includes/model/Employee/Exceptions.h"
#include "../../includes/model/Employee/Waiter.h"
#include "../../includes/model/Employee/Cook.h"
#include "../../includes/model/MenuItem/dessert.h"
#include "../../includes/model/MenuItem/dish.h"
#include "../../includes/model/MenuItem/beverage.h"
#include <sstream>

using std::stringstream;



#if DEBUG

TEST_CASE("cook simple simulation states") {
    DbWorkers workers;
    Price salary(3000, 0);
    workers.addCook("Tomasz", "Nowak", Cook::Gender::male, salary, 4, 26);
    workers.addCook("Tomasz", "Kowal", Cook::Gender::male, salary, 4, 26);


    CHECK(workers.getWorkerState(0) == Cook::CookState::free);
    workers.getCook(0)
            ->setAssignedMenuItem(make_unique<Dessert>(Dessert("Cake", Price(5, 0), 2)));
//    assigned dish with 2 cycle to prepare
    workers.advanceCycleAll();
    CHECK(workers.getCook(0)->getState() == Cook::CookState::busy);
    workers.advanceCycleAll();
//    free after 2 cycles
    CHECK(workers.getCook(0)->getState() == Cook::CookState::free);
//    advance cycle without assigning dish - no longer dish to collect, cook is free
    workers.advanceCycleAll();
//    advance cycle once again when free
    CHECK(workers.getCook(0)->getState() == Cook::CookState::free);

    workers.getCook(0)
            ->setAssignedMenuItem(make_unique<Dessert>(Dessert("Cake", Price(5, 0), 2)));
//    assigned dish with 2 cycle to prepare - new cycle

//    assigned another dish with 2 cycle to prepare (after 1 cycles out of 2 for
//    previous item) => needs 1 more cycle to be free
    workers.getCook(0)
           ->setAssignedMenuItem(make_unique<Dessert>(Dessert("Cake", Price(5, 0), 2)));
    CHECK(workers.getWorkerState(0) == Cook::CookState::busy);

    workers.advanceCycleAll(); // 1st
    CHECK(workers.getWorkerState(0) == Cook::CookState::busy);

    workers.advanceCycleAll(); // 2nd
    CHECK(workers.getWorkerState(0) == Cook::CookState::free);
}
#endif

#if DEBUG
TEST_CASE("waiter setAssignedTable") {
    Price salary(3000, 0);
    DbWorkers workers;
    workers.addWaiter("Tomasz", "Nowak", Waiter::Gender::male, salary, 4, true);
    CHECK_NOTHROW(workers.getWaiter(0)->setAssignedTable(make_shared<Table>(Table())));
    // not that without advancing cycle state is not updated -> table can be reassigned
    CHECK_NOTHROW(workers.getWaiter(0)->setAssignedTable(make_shared<Table>(Table())));
    workers.advanceCycleAll();
    REQUIRE_THROWS_AS(workers.getWaiter(0)->setAssignedTable(make_shared<Table>(Table())),
                      BusyWaiterException);
}
#endif

#if DEBUG
TEST_CASE("waiter cook big simulation") {
    DbWorkers workers;
    Price salary(3000, 0);
    workers.addCook("Tomasz", "Nowak", Cook::Gender::male, salary, 4, 26);
    workers.addWaiter("Tomasz", "Kowal", Waiter::Gender::male, salary, 4, 0);
    workers.addWaiter("Tomasz", "Burak", Waiter::Gender::male, salary, 4, 0);

    //     prepare table and customers
    Beverage coffee("Coffee", Price(2, 49), CupType::Cup, 2);
    Beverage tee("tee", Price(1, 49), CupType::Cup, 2);

    vector<Customer> customers1;
    customers1.emplace_back(Customer(1, true, make_unique<Beverage>(coffee)));
    customers1.emplace_back(Customer(2, true, make_unique<Beverage>(tee)));
    customers1.emplace_back(Customer(3, true, make_unique<Beverage>(coffee)));

    CustomersGroup group1(customers1);
    Table table(1, 5);
    shared_ptr<Table> tablePtr =  make_shared<Table>(table);
    CHECK(tablePtr->TryAddCustomers(group1));


    workers.getWaiter(1)->setAssignedTable(tablePtr);

    tablePtr->AdvanceStateAll();
    workers.advanceCycleAll();
    workers.advanceCycleAll();
    workers.advanceCycleAll();
//    workers.getWaiter(1)->collectOrders();

    tablePtr->AdvanceStateAll(); // ReadyToOrder -> Awaiting (cyclesLeft = 2)
    tablePtr->AdvanceStateAll(); // Awaiting (cyclesLeft = 1)
    tablePtr->AdvanceStateAll(); // Awaiting (cyclesLeft = 1) -> Eating
    tablePtr->AdvanceStateAll(); // Eating -> EatingFinished

    workers.advanceCycleAll(); // after that cycles left 2
    workers.advanceCycleAll(); // after that cycles left 1
    CHECK(workers.getWorkerState(0) == Cook::CookState::busy);

    workers.advanceCycleAll(); // after that cycles left 2 (item for another customer)
    workers.advanceCycleAll(); //after that cycles left 1
    CHECK(workers.getWorkerState(0) == Cook::CookState::busy);

    workers.advanceCycleAll(); // after that cycles left 2 (item for another customer)
    workers.advanceCycleAll(); //after that cycles left 1
    CHECK(workers.getWorkerState(0) == Cook::CookState::busy);

    workers.advanceCycleAll(); // hand in order
    CHECK(workers.getWorkerState(0) == Cook::CookState::free);
    workers.advanceCycleAll(); // readyToTakeReceipt

    workers.advanceCycleAll(); // calcRecceipt -> TakenReceipt

    CHECK(workers.getWorkerState(1) == Waiter::WaiterState::TakenReceipt);
    // @important - changes are applied to customers hold in tables' vectors, so it should satisfy simulation demands
    for (auto &customer : tablePtr->GetCustomers()){
        if (customer.GetCurrentState() == CustomerState::FinishedEating){
            CHECK(customer.isCollectedOrder());
            CHECK(customer.isReceivedReceipt());
        }
    }
    for (auto &customer : workers.getWaiter(1)->getAssignedTable() ->GetCustomers()){
        if (customer.GetCurrentState() == CustomerState::FinishedEating){
            CHECK(customer.isCollectedOrder());
            CHECK(customer.isReceivedReceipt());
        }
    }
    workers.advanceCycleAll(); // still clients at table
    CHECK(workers.getWorkerState(1) == Waiter::WaiterState::collectOrder);
}

TEST_CASE("waiter - finish serving the table"){
    DbWorkers workers;
    Price salary(3000, 0);
    workers.addCook("Tomasz", "Nowak", Cook::Gender::male, salary, 4, 26);
    workers.addWaiter("Tomasz", "Kowal", Waiter::Gender::male, salary, 4, 0);
    workers.addWaiter("Tomasz", "Burak", Waiter::Gender::male, salary, 4, 0);

    //     prepare table and customers
    Beverage coffee("Coffee", Price(2, 49), CupType::Cup, 2);
    Beverage tee("tee", Price(1, 49), CupType::Cup, 2);

    vector<Customer> customers1;
    customers1.emplace_back(Customer(1, true, make_unique<Beverage>(coffee)));
    customers1.emplace_back(Customer(2, true, make_unique<Beverage>(tee)));
    customers1.emplace_back(Customer(3, true, make_unique<Beverage>(coffee)));

    CustomersGroup group1(customers1);
    Table table(1, 5);
    shared_ptr<Table> tablePtr =  make_shared<Table>(table);
    CHECK(tablePtr->TryAddCustomers(group1));


    workers.getWaiter(1)->setAssignedTable(tablePtr);
    workers.getWaiter(1)->setState(Waiter::WaiterState::TakenReceipt);
    tablePtr->ClearAllCustomers();
    workers.advanceCycleAll();
    CHECK(workers.getWorkerState(1)==Waiter::WaiterState::awaiting);
}


#endif

#if DEBUG
TEST_CASE("waiter collect orders"){
    DbWorkers workers;
    Price salary(3000, 0);
    workers.addCook("Tomasz", "Nowak", Cook::Gender::male, salary, 4, 26);
    workers.addWaiter("Tomasz", "Kowal", Waiter::Gender::male, salary, 4, 0);
    workers.addWaiter("Tomasz", "Burak", Waiter::Gender::male, salary, 4, 0);
//     prepare table and customers
    Beverage coffee("Coffee", Price(2, 49), CupType::Cup, 4);
    Beverage tee("tee", Price(2, 49), CupType::Cup, 4);

    vector<Customer> customers1;
    customers1.emplace_back(Customer(1, true, make_unique<Beverage>(coffee)));
    customers1.emplace_back(Customer(2, true, make_unique<Beverage>(tee)));
    customers1.emplace_back(Customer(3, true, make_unique<Beverage>(coffee)));

    CustomersGroup group1(customers1);
    Table table(1, 5);
    shared_ptr<Table> tablePtr =  make_shared<Table>(table);
    CHECK(tablePtr->TryAddCustomers(group1));


    workers.getWaiter(1)->setAssignedTable(tablePtr);

    SECTION("customers not ready"){
        workers.getWaiter(1)->collectOrders();
        CHECK(tablePtr->GetAmountOfItemsToPrepare() == 0);
    }

    tablePtr->AdvanceStateAll();
    SECTION("customers ready"){
        workers.getWaiter(1)->collectOrders();
        CHECK(tablePtr->GetAmountOfItemsToPrepare() == 3);

        // @important - changes are applied to customers hold in tables' vectors, so it should satisfy simulation demands
        for (auto &customer : tablePtr->GetCustomers()){
            CHECK(customer.isCollectedOrder());
        }
        for (auto &customer : workers.getWaiter(1)->getAssignedTable() ->GetCustomers()){
            CHECK(customer.isCollectedOrder());
        }
    }


}
#endif

#if DEBUG
TEST_CASE("waiter calculate receipt"){
    DbWorkers workers;
    Price salary(3000, 0);
    workers.addCook("Tomasz", "Nowak", Cook::Gender::male, salary, 4, 26);
    workers.addWaiter("Tomasz", "Kowal", Waiter::Gender::male, salary, 4, 0);
    workers.addWaiter("Tomasz", "Burak", Waiter::Gender::male, salary, 4, 0);

    SECTION("same time for preparation"){
        //     prepare table and customers
        Beverage coffee("Coffee", Price(2, 49), CupType::Cup, 2);
        Beverage tee("tee", Price(2, 49), CupType::Cup, 2);

        vector<Customer> customers1;
        customers1.emplace_back(Customer(1, true, make_unique<Beverage>(coffee)));
        customers1.emplace_back(Customer(2, true, make_unique<Beverage>(tee)));
        customers1.emplace_back(Customer(3, true, make_unique<Beverage>(coffee)));

        CustomersGroup group1(customers1);
        Table table(1, 5);
        shared_ptr<Table> tablePtr =  make_shared<Table>(table);
        CHECK(tablePtr->TryAddCustomers(group1));


        workers.getWaiter(1)->setAssignedTable(tablePtr);

        tablePtr->AdvanceStateAll();
        workers.getWaiter(1)->collectOrders();

        tablePtr->AdvanceStateAll(); // ReadyToOrder -> Awaiting (cyclesLeft = 2)
        tablePtr->AdvanceStateAll(); // Awaiting (cyclesLeft = 1)
        tablePtr->AdvanceStateAll(); // Awaiting (cyclesLeft = 1) -> Eating
        tablePtr->AdvanceStateAll(); // Eating -> EatingFinished

        CHECK(workers.getWaiter(1)->calcReceipt() == Price(7, 47));
        // @important - changes are applied to customers hold in tables' vectors, so it should satisfy simulation demands
        for (auto &customer : tablePtr->GetCustomers()){
            CHECK(customer.isCollectedOrder());
            CHECK(customer.isReceivedReceipt());
        }
        for (auto &customer : workers.getWaiter(1)->getAssignedTable() ->GetCustomers()){
            CHECK(customer.isCollectedOrder());
            CHECK(customer.isReceivedReceipt());
        }
    }

    SECTION("different time for preparation"){
        //     prepare table and customers
        Beverage coffee("Coffee", Price(2, 49), CupType::Cup, 2);
        Beverage tee("tee", Price(1, 49), CupType::Cup, 6);

        vector<Customer> customers1;
        customers1.emplace_back(Customer(1, true, make_unique<Beverage>(coffee)));
        customers1.emplace_back(Customer(2, true, make_unique<Beverage>(tee)));
        customers1.emplace_back(Customer(3, true, make_unique<Beverage>(coffee)));

        CustomersGroup group1(customers1);
        Table table(1, 5);
        shared_ptr<Table> tablePtr =  make_shared<Table>(table);
        CHECK(tablePtr->TryAddCustomers(group1));


        workers.getWaiter(1)->setAssignedTable(tablePtr);

        tablePtr->AdvanceStateAll();
        workers.getWaiter(1)->collectOrders();

        tablePtr->AdvanceStateAll(); // ReadyToOrder -> Awaiting (cyclesLeft = 2)
        tablePtr->AdvanceStateAll(); // Awaiting (cyclesLeft = 1)
        tablePtr->AdvanceStateAll(); // Awaiting (cyclesLeft = 1) -> Eating
        tablePtr->AdvanceStateAll(); // Eating -> EatingFinished

        CHECK(workers.getWaiter(1)->calcReceipt() == Price(4, 98));
        // @important - changes are applied to customers hold in tables' vectors, so it should satisfy simulation demands
        for (auto &customer : tablePtr->GetCustomers()){
            if (customer.GetCurrentState() == CustomerState::FinishedEating){
                CHECK(customer.isCollectedOrder());
                CHECK(customer.isReceivedReceipt());
            }
        }
        for (auto &customer : workers.getWaiter(1)->getAssignedTable() ->GetCustomers()){
            if (customer.GetCurrentState() == CustomerState::FinishedEating){
                CHECK(customer.isCollectedOrder());
                CHECK(customer.isReceivedReceipt());
            }
        }
    }

    SECTION("customer joining later => their states differ"){
        //     prepare table and customers
        Beverage coffee("Coffee", Price(2, 49), CupType::Cup, 2);
        Beverage tee("tee", Price(1, 49), CupType::Cup, 2);

        vector<Customer> customers1;
        customers1.emplace_back(Customer(1, true, make_unique<Beverage>(coffee)));
        customers1.emplace_back(Customer(2, true, make_unique<Beverage>(coffee)));

        CustomersGroup group1(customers1);
        Table table(1, 5);
        shared_ptr<Table> tablePtr =  make_shared<Table>(table);
        CHECK(tablePtr->TryAddCustomers(group1));


        workers.getWaiter(1)->setAssignedTable(tablePtr);

        tablePtr->AdvanceStateAll();
        workers.getWaiter(1)->collectOrders();

        tablePtr->AdvanceStateAll(); // ReadyToOrder -> Awaiting (cyclesLeft = 2)
        tablePtr->AdvanceStateAll(); // Awaiting (cyclesLeft = 1)

        vector<Customer> customers2;
        customers2.emplace_back(Customer(3, true, make_unique<Beverage>(tee)));
        customers2.emplace_back(Customer(4, true, make_unique<Beverage>(tee)));

        CustomersGroup group2(customers2);
        CHECK(tablePtr->TryAddCustomers(group2));


        tablePtr->AdvanceStateAll(); // Awaiting (cyclesLeft = 1) -> Eating
        tablePtr->AdvanceStateAll(); // Eating -> EatingFinished

        CHECK(workers.getWaiter(1)->calcReceipt() == Price(4, 98));
        // @important - changes are applied to customers hold in tables' vectors, so it should satisfy simulation demands
        for (auto &customer : tablePtr->GetCustomers()){
            if (customer.GetCurrentState() == CustomerState::FinishedEating){
                CHECK(customer.isCollectedOrder());
                CHECK(customer.isReceivedReceipt());
            }
        }
        for (auto &customer : workers.getWaiter(1)->getAssignedTable() ->GetCustomers()){
            if (customer.GetCurrentState() == CustomerState::FinishedEating){
                CHECK(customer.isCollectedOrder());
                CHECK(customer.isReceivedReceipt());
            }
        }

        // extra 2 cycles for customer who joined later
        workers.getWaiter(1)->collectOrders();
        tablePtr->AdvanceStateAll(); // Awaiting (cyclesLeft = 1) -> Eating

        tablePtr->AdvanceStateAll(); // Eating -> EatingFinished
        tablePtr->AdvanceStateAll(); // Eating -> EatingFinished
        tablePtr->AdvanceStateAll(); // Eating -> EatingFinished

        CHECK(workers.getWaiter(1)->calcReceipt() == Price(7, 96));
        // @important - changes are applied to customers hold in tables' vectors, so it should satisfy simulation demands
        for (auto &customer : tablePtr->GetCustomers()){
            if (customer.GetCurrentState() == CustomerState::FinishedEating){
                CHECK(customer.isCollectedOrder());
                CHECK(customer.isReceivedReceipt());
            }
        }
        for (auto &customer : workers.getWaiter(1)->getAssignedTable() ->GetCustomers()){
            if (customer.GetCurrentState() == CustomerState::FinishedEating){
                CHECK(customer.isCollectedOrder());
                CHECK(customer.isReceivedReceipt());
            }
        }
    }


}
#endif
