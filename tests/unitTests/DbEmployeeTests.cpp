#define CATCH_CONFIG_MAIN

#include "../catch.hpp"
#include "../../includes/model/helpers/price.h"
#include "../../includes/model/Employee/Employee.h"
#include "../../includes/model/Employee/Exceptions.h"
#include "../../includes/model/Employee/Waiter.h"
#include "../../includes/model/Employee/Cook.h"
#include "../../includes/model/MenuItem/dessert.h"
#include "../../includes/model/MenuItem/dish.h"
#include "../../includes/model/Employee/DbWorkers.h"
#include <sstream>

using std::stringstream;

TEST_CASE("Employee status") {
    Price salary(3000, 0);
    DbWorkers workers;
    workers.addCook("Tomasz", "Nowak", Waiter::Gender::male, salary, 4, 26);
    workers.addWaiter("Tomasz", "Nowak", Waiter::Gender::male, salary, 4, true);
    workers.addWaiter("Tomasz", "Nowak", Waiter::Gender::male, salary, 4, true);
    CHECK(workers.getWorkerState(0) == Cook::CookState::free);

}

TEST_CASE("employee removal"){
    Price salary(3000, 0);
    DbWorkers workers;
    workers.addCook("Tomasz", "Nowak", Waiter::Gender::male, salary, 4, 26);
    workers.addWaiter("Tomasz", "Nowak", Waiter::Gender::male, salary, 4, true);
    workers.addWaiter("Tomasz", "Nowak", Waiter::Gender::male, salary, 4, true);

    SECTION("remove non existing"){
        REQUIRE_THROWS_AS(workers.removeWorkerById(5), IdException);
    }
    SECTION("remove existing"){
        REQUIRE_NOTHROW(workers.removeWorkerById(2));
        REQUIRE_THROWS_AS(workers.removeWorkerById(2), IdException);
    }
}


TEST_CASE("assign free cook"){
    Price salary(3000, 0);
    DbWorkers workers;
    workers.addWaiter("Tomasz", "Nowak", Waiter::Gender::male, salary, 4, true);
    workers.addWaiter("Tomasz", "Nowak", Waiter::Gender::male, salary, 4, true);
    workers.addCook("Tomasz", "Nowak", Waiter::Gender::male, salary, 4, 26);
    CHECK(workers.assignDishToFreeCook(make_unique<Dessert>(Dessert("Cake", Price(5, 0),
                                                                    2))));
    CHECK(workers.assignDishToFreeCook(make_unique<Dessert>(Dessert("Cake", Price(5, 0),
                                                                    2))) == false);
}







