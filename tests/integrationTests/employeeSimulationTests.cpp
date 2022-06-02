//
// Created by wojtek on 28.05.22.
//
#define CATCH_CONFIG_MAIN

#include "../catch.hpp"
#include "../../includes/model/helpers/price.h"
#include "../../includes/model/Employee/Employee.h"
#include "../../includes/model/Employee/employeeExceptions.h"
#include "../../includes/model/Employee/Waiter.h"
#include "../../includes/model/Employee/Cook.h"
#include "../../includes/model/MenuItem/dessert.h"
#include "../../includes/model/MenuItem/dish.h"
#include "../../includes/model/MenuItem/beverage.h"
#include "../../includes/model/Databases/CustomTableDb.h"
#include "../../includes/model/Databases/CustomEmployeesDb.h"
#include <sstream>

using std::stringstream;



#if DEBUG


TEST_CASE("cook - single -  assigned item"){
    CustomEmployeesDb workers;
    Price salary(3000, 0);
    workers.addCook("Tomasz", "Nowak", Cook::Gender::male, salary, 4, 26);
    workers.addWaiter("Tomasz", "Kowal", Waiter::Gender::male, salary, 4, 0);

    //     prepare table and customers
    Beverage coffee("Coffee", Price(2, 49), CupType::Cup, 2);
    Beverage tee("tee", Price(1, 49), CupType::Cup, 2);

    vector<Customer> customers1;
    customers1.emplace_back(Customer(2, true, make_unique<Beverage>(coffee)));
    customers1.emplace_back(Customer(3, true, make_unique<Beverage>(tee)));

    CustomersGroup group1(customers1);
    Table table(1, 5);
    shared_ptr<Table> tablePtr =  make_shared<Table>(table);
    CHECK(tablePtr->TryAddCustomers(group1));


    workers.getWaiter(1)->setAssignedTable(tablePtr);
    tablePtr->AdvanceStateAll();
    tablePtr->AdvanceStateAll();
    tablePtr->AdvanceStateAll();

    workers.advanceCycleAll();
    workers.advanceCycleAll();
    CHECK(workers.getWorkerState(0) == Cook::CookState::free);
    workers.advanceCycleAll();
    // 2 cycles for tee
    workers.advanceCycleAll(); // waiter is preparing orders
    CHECK(workers.getWorkerState(0) == Cook::CookState::busy);
    CHECK(workers.getCook(0)->getAssignedMenuItemName() == "tee, Coffee, ");
    workers.advanceCycleAll();
    CHECK(workers.getCook(0)->getAssignedMenuItemName() == "tee, Coffee, ");
    // 2 cycles for coffee
    workers.advanceCycleAll(); // waiter is preparing orders
    CHECK(workers.getWorkerState(0) == Cook::CookState::busy);
    CHECK(workers.getCook(0)->getAssignedMenuItemName() == "tee, Coffee, ");
    workers.advanceCycleAll();
    CHECK(workers.getCook(0)->getAssignedMenuItemName() == "tee, Coffee, ");
    CHECK(workers.getWorkerState(1) == Waiter::WaiterState::prepareOrder);

    // then free - 2 x 2 cycles per 1 cook
    workers.advanceCycleAll(); // waiter is preparing orders
    CHECK(workers.getWorkerState(0) == Cook::CookState::free);
    CHECK(workers.getWorkerState(1) == Waiter::WaiterState::handInOrder);
}

TEST_CASE("cook - many -  assigned item"){
    CustomEmployeesDb workers;
    Price salary(3000, 0);
    workers.addCook("Tomasz", "Nowak", Cook::Gender::male, salary, 4, 26);
    workers.addWaiter("Tomasz", "Kowal", Waiter::Gender::male, salary, 4, 0);
    workers.addCook("Tomasz", "Nowakowski", Cook::Gender::male, salary, 4, 26);
    //     prepare table and customers
    Beverage coffee("Coffee", Price(2, 49), CupType::Cup, 2);
    Beverage tee("tee", Price(1, 49), CupType::Cup, 2);

    vector<Customer> customers1;
    customers1.emplace_back(Customer(1, true, make_unique<Beverage>(coffee)));
    customers1.emplace_back(Customer(2, true, make_unique<Beverage>(coffee)));
    customers1.emplace_back(Customer(3, true, make_unique<Beverage>(tee)));

    CustomersGroup group1(customers1);
    Table table(1, 5);
    shared_ptr<Table> tablePtr =  make_shared<Table>(table);
    CHECK(tablePtr->TryAddCustomers(group1));


    workers.getWaiter(1)->setAssignedTable(tablePtr);
    tablePtr->AdvanceStateAll();
    tablePtr->AdvanceStateAll();
    tablePtr->AdvanceStateAll();

    workers.advanceCycleAll();
    workers.advanceCycleAll();
    CHECK(workers.getWorkerState(0) == Cook::CookState::free);
    workers.advanceCycleAll();
    // 2 cycles for tee
    workers.advanceCycleAll(); // waiter is preparing orders
    CHECK(workers.getWorkerState(0) == Cook::CookState::busy);
    CHECK(workers.getCook(0)->getAssignedMenuItemName() == "tee, Coffee, Coffee, ");
    workers.advanceCycleAll();
    CHECK(workers.getCook(0)->getAssignedMenuItemName() == "tee, Coffee, Coffee, ");
    // 2 cycles for Coffee
    workers.advanceCycleAll(); // waiter is preparing orders
    CHECK(workers.getWorkerState(0) == Cook::CookState::busy);
    CHECK(workers.getCook(0)->getAssignedMenuItemName() == "tee, Coffee, Coffee, ");


    // then free - 3 x 2 cycles per 2 cook = 3 cycles
    workers.advanceCycleAll(); // waiter is preparing orders
    CHECK(workers.getWorkerState(0) == Cook::CookState::free);
    CHECK(workers.getWorkerState(1) == Waiter::WaiterState::handInOrder);
}


#endif

#if DEBUG
TEST_CASE("waiter setAssignedTable") {
    Price salary(3000, 0);
    CustomEmployeesDb workers;
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
    CustomEmployeesDb workers;
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
    CHECK(workers.getCook(0)->printStateLog() == "cook 0 - free\n");
    workers.advanceCycleAll();
    workers.advanceCycleAll();
    CHECK(workers.getWaiter(1)->printStateLog() == "waiter 1 - collecting orders from "
                                                   "table nr 1\n");
    workers.advanceCycleAll();

//    workers.getWaiter(1)->collectOrders();

    tablePtr->AdvanceStateAll(); // ReadyToOrder -> Awaiting (cyclesLeft = 2)
    tablePtr->AdvanceStateAll(); // Awaiting (cyclesLeft = 1)
    tablePtr->AdvanceStateAll(); // Awaiting (cyclesLeft = 1) -> Eating
    tablePtr->AdvanceStateAll(); // Eating -> EatingFinished

    workers.advanceCycleAll(); // after that cycles left 2
    workers.advanceCycleAll(); // after that cycles left 1
    CHECK(workers.getWorkerState(0) == Cook::CookState::busy);
    CHECK(workers.getWaiter(1)->printStateLog() == "waiter 1 - preparing orders for "
                                                   "table nr 1\n");

    workers.advanceCycleAll(); // after that cycles left 2 (item for another customer)
    workers.advanceCycleAll(); //after that cycles left 1
    CHECK(workers.getWorkerState(0) == Cook::CookState::busy);

    workers.advanceCycleAll(); // after that cycles left 2 (item for another customer)
    workers.advanceCycleAll(); //after that cycles left 1
    CHECK(workers.getWorkerState(0) == Cook::CookState::busy);

    workers.advanceCycleAll(); // hand in order
    CHECK(workers.getWaiter(1)->printStateLog() == "waiter 1 - handing in orders to "
                                                   "table nr 1\n");
    CHECK(workers.getWorkerState(0) == Cook::CookState::free);
    workers.advanceCycleAll(); // readyToTakeReceipt
    CHECK(workers.getWaiter(1)->printStateLog() == "waiter 1 - preparing receipt for "
                                                   "table nr 1\n");

    workers.advanceCycleAll(); // calcRecceipt -> TakenReceipt
    CHECK(workers.getWaiter(1)->printStateLog() == "waiter 1 - receipt for table nr 1 "
                                                   "is $6.47\n");

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

TEST_CASE("waiter cook big simulation CustomTableDB version") {
    CustomEmployeesDb workers;
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

    CustomTableDb tablesCollection;

    Table table(1, 5);
    shared_ptr<Table> tablePtr = make_shared<Table>(table);
    tablesCollection.AddItem(tablePtr);

//    CHECK(tablesCollection.GetItems()[0]->TryAddCustomers(group1));
    CHECK(tablesCollection.TryAssignCustomersGroup(group1));
    tablesCollection.AdvanceStateAllTables();

    workers.getWaiter(1)->setAssignedTable(tablePtr);

    tablePtr->AdvanceStateAll();
    CHECK(workers.getCook(0)->printStateLog() == "cook 0 - free\n");
    workers.advanceCycleAll();
    workers.advanceCycleAll();
    CHECK(workers.getWaiter(1)->printStateLog() == "waiter 1 - collecting orders from "
                                                   "table nr 1\n");
    workers.advanceCycleAll();

//    workers.getWaiter(1)->collectOrders();

    tablesCollection.AdvanceStateAllTables(); // ReadyToOrder -> Awaiting (cyclesLeft = 2)
    tablesCollection.AdvanceStateAllTables(); // Awaiting (cyclesLeft = 1)
    tablesCollection.AdvanceStateAllTables(); // Awaiting (cyclesLeft = 1) -> Eating
    tablesCollection.AdvanceStateAllTables(); // Eating -> EatingFinished

    workers.advanceCycleAll(); // after that cycles left 2
    workers.advanceCycleAll(); // after that cycles left 1
    CHECK(workers.getWorkerState(0) == Cook::CookState::busy);
    CHECK(workers.getWaiter(1)->printStateLog() == "waiter 1 - preparing orders for "
                                                   "table nr 1\n");

    workers.advanceCycleAll(); // after that cycles left 2 (item for another customer)
    workers.advanceCycleAll(); //after that cycles left 1
    CHECK(workers.getWorkerState(0) == Cook::CookState::busy);

    workers.advanceCycleAll(); // after that cycles left 2 (item for another customer)
    workers.advanceCycleAll(); //after that cycles left 1
    CHECK(workers.getWorkerState(0) == Cook::CookState::busy);

    workers.advanceCycleAll(); // hand in order
    CHECK(workers.getWaiter(1)->printStateLog() == "waiter 1 - handing in orders to "
                                                   "table nr 1\n");
    CHECK(workers.getWorkerState(0) == Cook::CookState::free);
    workers.advanceCycleAll(); // readyToTakeReceipt
    CHECK(workers.getWaiter(1)->printStateLog() == "waiter 1 - preparing receipt for "
                                                   "table nr 1\n");

    workers.advanceCycleAll(); // calcRecceipt -> TakenReceipt
    CHECK(workers.getWaiter(1)->printStateLog() == "waiter 1 - receipt for table nr 1 "
                                                   "is $6.47\n");

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
    CustomEmployeesDb workers;
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
    CustomEmployeesDb workers;
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
    CustomEmployeesDb workers;
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

        workers.getWaiter(1)->calcReceipt();
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

        workers.getWaiter(1)->calcReceipt();
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

        workers.getWaiter(1)->calcReceipt();
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

        workers.getWaiter(1)->calcReceipt();
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
