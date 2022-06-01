
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../../includes/model/Databases/menuDatabase.h"
#include "../../includes/model/MenuItem/beverage.h"
#include "../../includes/model/MenuItem/dessert.h"
#include "../../includes/model/MenuItem/dish.h"
#include "../../includes/model/MenuItem/exceptions.h"
#include "../../includes/model/Databases/menuDatabase.h"
#include "../../includes/model/Databases/templateDatabase.h"
#include "../../includes/model/Databases/CustomTableDb.h"
#include "../../includes/model/Databases/CustomEmployeesDb.h"
#include "../../includes/model/Employee/Waiter.h"
#include "../../includes/model/Employee/Cook.h"


TEST_CASE("basic object"){
//    TemplateDatabase<int> db1;
//    db1.AddItem(make_shared<int>(23));
//    db1.foo();

    TemplateDatabase<Table> db2;
    db2.AddItem(make_shared<Table>(Table(1,5)));
    db2.AddItem(make_shared<Table>(Table(2,5)));
    REQUIRE_THROWS(db2.AddItem(make_shared<Table>(Table(1, 2))));
    CHECK(db2.CountItems() == 2);
    CHECK(db2.GetItems().size() == 2);
    REQUIRE_THROWS(db2.RemoveItem(2));
    db2.RemoveItem(1);
    CHECK(db2.CountItems() == 1);


}

TEST_CASE("new employees"){
    CustomEmployeesDb db;
    db.AddItem(make_shared<Waiter>(Waiter(1, "Jan", "Nowal", Employee::Gender::male,
                                          Price(2000,0), 4, true)));
    db.AddItem(make_shared<Waiter>(Waiter(2, "Jan", "Nowal", Employee::Gender::male,
                                          Price(2000,0), 4, true)));
    CHECK(db.GetItems().size() == 2);
}

