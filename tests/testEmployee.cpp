#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../includes/model/helpers/price.h"
#include "../includes/model/Employee//Employee.h"
#include "../includes/model/Employee//Exceptions.h"
#include "../includes/model/Employee//Waiter.h"
#include "../includes/model/Employee//Cook.h"
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

TEST_CASE("waiter printProperties currentState") {
    Price salary(3000, 0);
    Waiter waiter1(1, "Tomasz", "Nowak", Waiter::Gender::male, salary, 4, true);
    CHECK(waiter1.printStateLog() == "waiter 1 - awaiting\n");
    waiter1.setAssignedTable(make_unique<Table>(Table()));
    waiter1.setState(Waiter::WaiterState::collectOrder);
    CHECK(waiter1.printStateLog() == "waiter 1 - collecting orders to table nr 23\n");
}

TEST_CASE("waiter virtual methods") {
    Price salary(3000, 0);
    Waiter waiter1(2, "Tomasz", "Nowak", Waiter::Gender::male, salary, 4, true);
    SECTION("calculate salary") {
        CHECK(waiter1.calculate_salary() == Price(9000, 0));
    }
    SECTION("calculate shifts") {
        CHECK(waiter1.calculate_shifts_per_week() == 5);
    }
}

TEST_CASE("waiter in out operators") {
    Price salary(3000, 0);
    Waiter waiter(3, "Tomasz", "Nowak", Waiter::Gender::male,
                  salary, 4, 0);
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

TEST_CASE("cook virtual methods") {
    Price salary(3000, 0);
    Cook cook1(11, "Tomasz", "Nowak", Waiter::Gender::male, salary, 4, 26);
    SECTION("calculate salary") {
        Price cooker_salary = cook1.calculate_salary();
        CHECK(cook1.calculate_salary() == Price(6000, 0));
    }
    SECTION("calculate shifts") {
        CHECK(cook1.calculate_shifts_per_week() == 5);
    }
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





