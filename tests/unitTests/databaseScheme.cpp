
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
    db.AddItem(make_shared<Cook>(Cook(3, "Jan", "Nowal", Employee::Gender::male,
                                          Price(2000,0), 4, 9)));
    CHECK(db.GetItems().size() == 3);
    stringstream ss;
    ss << db;
    string a =ss.str();
    CHECK(ss.str() =="3\nw Jan\nNowal\n1 1 2000 0 4 1\nw Jan\nNowal\n2 1 2000 0 4 1\nc"
                     " Jan\nNowal\n3 1 2000 0 4 9\n");
    CustomEmployeesDb db2;
    stringstream ss2;
    ss >> db2;
    ss2 << db2;
    string b = ss2.str();
    CHECK(db2.GetItems()[2]->get_base_amount_of_shifts() == 4);

}

TEST_CASE("tables in out"){
    CustomTableDb db1;
    db1.AddItem(make_shared<Table>(Table(1,5)));
    db1.AddItem(make_shared<Table>(Table(2,5)));
    stringstream ss;
    ss << db1;
    CHECK(ss.str() == "2\n1 5\n2 5\n");

    CustomTableDb db2;
    stringstream  ss2;
    ss >> db2;
    ss2 << db2;
    CHECK(ss.str() == ss2.str());
}

