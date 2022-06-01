#define CATCH_CONFIG_MAIN

#include "../catch.hpp"
#include "../../includes/model/helpers/price.h"
#include "../../includes/model/Employee/Employee.h"
#include "../../includes/model/Employee/Exceptions.h"
#include "../../includes/model/Employee/Waiter.h"
#include "../../includes/model/Employee/Cook.h"
#include "../../includes/model/MenuItem/dessert.h"
#include "../../includes/model/MenuItem/dish.h"
#include "../../includes/model/Databases/CustomEmployeesDb.h"

using std::stringstream;

TEST_CASE("Employee status") {
    Price salary(3000, 0);
    CustomEmployeesDb workers;
    workers.addCook("Tomasz", "Nowak", Waiter::Gender::male, salary, 4, 26);
    workers.addWaiter("Tomasz", "Nowak", Waiter::Gender::male, salary, 4, true);
    workers.addWaiter("Tomasz", "Nowak", Waiter::Gender::male, salary, 4, true);
    CHECK(workers.getWorkerState(0) == Cook::CookState::free);

}

TEST_CASE("employee removal"){
    Price salary(3000, 0);
    CustomEmployeesDb workers;
    workers.addCook("Tomasz", "Nowak", Waiter::Gender::male, salary, 4, 26);
    workers.addWaiter("Tomasz", "Nowak", Waiter::Gender::male, salary, 4, true);
    workers.addWaiter("Tomasz", "Nowak", Waiter::Gender::male, salary, 4, true);

    SECTION("remove non existing"){
        REQUIRE_THROWS(workers.RemoveItem(5));
    }
    SECTION("remove existing"){
        REQUIRE_NOTHROW(workers.RemoveItem(1));
        CHECK(workers.GetItems().size() == 2);

        REQUIRE_THROWS(workers.RemoveItem(2));
    }
}









