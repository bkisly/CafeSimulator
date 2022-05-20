#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../includes/model/helpers/price.h"
#include "../includes/model/Employee//Employee.h"
#include "../includes/model/Employee//Exceptions.h"
#include "../includes/model/Employee//Waiter.h"
#include "../includes/model/Employee//Cook.h"
#include "../includes/model/MenuItem/dessert.h"
#include "../includes/model/MenuItem/dish.h"
#include <sstream>

using std::stringstream;

TEST_CASE("Employee exceptions") {
    Price p1(3000, 0);
    REQUIRE_THROWS_AS(Employee(1, "Jan", "Kowal", 2, p1, 5), GenderException);
}

TEST_CASE("Employee in out operators") {
    Price p1(3000, 0);
    Employee Employee1(2, "Jan Marek", "Kowal", Employee::Gender::male, p1, 5);
    stringstream ss;
    ss << Employee1;
    CHECK(ss.str() == "Jan Marek\nKowal\n2 1 3000 0 5");
    Employee Employee2;
    ss >> Employee2;
    CHECK(Employee1 == Employee2);
}

TEST_CASE("waiter setter") {
    Price salary(3000, 0);
    Waiter waiter1(1, "Tomasz", "Nowak", Waiter::Gender::male, salary, 4, true);
    CHECK(waiter1.get_name() == "Tomasz");
    waiter1.set_name("Jan");
    CHECK(waiter1.get_name() == "Jan");
}

TEST_CASE("waiter printStateLog currentState") {
    Price salary(3000, 0);
    Waiter waiter1(1, "Tomasz", "Nowak", Waiter::Gender::male, salary, 4, true);
    CHECK(waiter1.printStateLog() == "waiter 1 - awaiting\n");
    waiter1.setAssignedTable(make_unique<Table>(Table()));
    waiter1.setState(Waiter::WaiterState::collectOrder);
    CHECK(waiter1.printStateLog() == "waiter 1 - collecting orders to table nr 23\n");
}

TEST_CASE("setAssignedTable") {
    Price salary(3000, 0);
    Waiter waiter1(1, "Tomasz", "Nowak", Waiter::Gender::male, salary, 4, true);
    Table table1();
    CHECK_NOTHROW(waiter1.setAssignedTable(make_unique<Table>(Table())));
    waiter1.advanceCycle();
    REQUIRE_THROWS_AS(waiter1.setAssignedTable(make_unique<Table>(Table())),
                      BusyWaiterException);

}

TEST_CASE("waiter states simulation") {
    Price salary(3000, 0);
    Waiter waiter(3, "Tomasz", "Nowak", Waiter::Gender::male, salary, 4, 0);
    CHECK(waiter.getState() == Waiter::WaiterState::awaiting);
//    advanceCycle - no assigned tables - wait
    waiter.advanceCycle();
    CHECK(waiter.getState() == Waiter::WaiterState::awaiting);

//    setAssignedTable
    waiter.setAssignedTable(make_unique<Table>(Table()));
    waiter.advanceCycle();
    CHECK(waiter.getState() == Waiter::WaiterState::giveMenu);

    waiter.advanceCycle();
    CHECK(waiter.getState() == Waiter::WaiterState::collectOrder);

//    todo check other states, especially asssigned cook
}


TEST_CASE("waiter in out operators") {
    Price salary(3000, 0);
    Waiter waiter(3, "Tomasz", "Nowak", Waiter::Gender::male, salary, 4, 0);
    stringstream ss;
    ss << waiter;
    CHECK(ss.str() == "Tomasz\nNowak\n3 1 3000 0 4 0");
    Waiter new_waiter;
    ss >> new_waiter;
    CHECK(new_waiter == waiter);
}


TEST_CASE("cook setter") {
    Price salary(3000, 0);
    Cook cook1(11, "Tomasz", "Nowak", Waiter::Gender::male, salary, 4, 26);
    CHECK(cook1.get_name() == "Tomasz");
    cook1.set_name("Jan");
    CHECK(cook1.get_name() == "Jan");
}

TEST_CASE("cook setAssignedDish") {
    Cook cook(11, "Tomasz", "Nowak", Waiter::Gender::male, Price(3000, 0), 4, 26);
    CHECK_NOTHROW(cook.setAssignedMenuItem(
            make_unique<Dessert>(Dessert("Cake", Price(5, 0), 3))));
//    assigment to busy cook
    REQUIRE_THROWS_AS(cook.setAssignedMenuItem(
            make_unique<Dessert>(Dessert("Cake", Price(5, 0), 3))), BusyCookException);
}

TEST_CASE("cook printStateLog") {
    Price salary(3000, 0);
    Cook cook(11, "Tomasz", "Nowak", Waiter::Gender::male, salary, 4, 26);
    CHECK(cook.printStateLog() == "cook 11 - free\n");
    cook.setAssignedMenuItem(make_unique<Dessert>(Dessert("Cake", Price(5, 0), 3)));
    CHECK(cook.printStateLog() == "cook 11 - prepares Cake\n");
}

TEST_CASE("cook simulation states") {
    Cook cook(11, "Tomasz", "Nowak", Waiter::Gender::male, Price(3000, 0), 4, 26);
    CHECK(cook.getState() == Cook::CookState::free);
    cook.setAssignedMenuItem(make_unique<Dessert>(Dessert("Cake", Price(5, 0), 2)));
//    assigned dish with 2 cycle to prepare
    cook.advanceCycle();
    CHECK(cook.getState() == Cook::CookState::busy);
    CHECK(cook.isDishToCollect() == false);
    cook.advanceCycle();
//    dish is ready
    CHECK(cook.getState() == Cook::CookState::free);
    CHECK(cook.isDishToCollect() == true);
//    advance cycle without assigning dish - no longer dish to collect
    cook.advanceCycle();
    CHECK(cook.isDishToCollect() == false);
}


TEST_CASE("cook in out operators") {
    Price salary(3000, 0);
    Cook cook(11, "Tomasz", "Nowak", Waiter::Gender::male, salary, 4, 26);
    stringstream ss;
    ss << cook;
    CHECK(ss.str() == "Tomasz\nNowak\n11 1 3000 0 4 26");
    Cook new_cook;
    ss >> new_cook;
//    Cleaner::read(ss, new_cook);
    CHECK(new_cook == cook);
}





