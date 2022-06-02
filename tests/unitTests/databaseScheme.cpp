
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../../includes/model/Databases/menuDatabase.h"
#include "../../includes/model/MenuItem/beverage.h"
#include "../../includes/model/MenuItem/dessert.h"
#include "../../includes/model/MenuItem/dish.h"
#include "../../includes/model/helpers/exceptions.h"
#include "../../includes/model/Databases/menuDatabase.h"
#include "../../includes/model/Databases/templateDatabase.h"
#include "../../includes/model/Databases/CustomTableDb.h"
#include "../../includes/model/Databases/CustomEmployeesDb.h"
#include "../../includes/model/Employee/Waiter.h"
#include "../../includes/model/Employee/Cook.h"
#include <fstream>


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

TEST_CASE("tables in out") {
    CustomTableDb db1;
    db1.AddItem(make_shared<Table>(Table(1, 5)));
    db1.AddItem(make_shared<Table>(Table(2, 5)));
    stringstream ss;
    ss << db1;
    CHECK(ss.str() == "2\n1 5\n2 5\n");

    CustomTableDb db2;
    stringstream ss2;
    ss >> db2;
    ss2 << db2;
    CHECK(ss.str() == ss2.str());
}

TEST_CASE("sava to file") {
    vector<shared_ptr<MenuItem>> menuItems{
            make_shared<Beverage>("Coffee", Price(2, 49), CupType::Cup, 3),
            make_shared<Beverage>("Water", Price(0, 99), CupType::Glass, 1),
            make_shared<Beverage>("Tea", Price(1, 50), CupType::Mug, 2),

            make_shared<Dessert>("Cake", Price(5, 99), 3),
            make_shared<Dessert>("Ice cream", Price(0, 99), 2),

            make_shared<Dish>("Caesar salad", Price(12, 99), false, 5),
            make_shared<Dish>("Vegan wrap", Price(9, 99), true, 4)
    };

    MenuDatabase menuDb(menuItems);
    ofstream file;
    file.open("../textFiles/menuDb.txt");
    file << menuDb; // write
    file.close();

    CustomEmployeesDb employeesDb;
    employeesDb.addCook("Jan", "Kowalski", 0, Price(25, 0), 2, 4);
    employeesDb.addCook("Maciej", "Nowak", 0, Price(30, 0), 1, 5);
    employeesDb.addCook("Bożena", "Kowalska", 1, Price(25, 0), 2, 6);

    employeesDb.addWaiter("Borys", "Groch", 0, Price(15, 0), 1, true);
    employeesDb.addWaiter("Grzegorz", "Brzęczyszczykiewicz", 0, Price(20, 0), 2, false);
    employeesDb.addWaiter("Halina", "Grzmot", 1, Price(30, 0), 1, true);
    file.open("../textFiles/employeesDb.txt");
    file << employeesDb; // write
    file.close();

    CustomTableDb tablesDb;
    tablesDb.AddTable(2);
    tablesDb.AddTable(2);
    tablesDb.AddTable(3);
    tablesDb.AddTable(4);
    tablesDb.AddTable(4);
    tablesDb.AddTable(5);
    file.open("../textFiles/tablesDb.txt");
    file << tablesDb; // write
    file.close();
}

TEST_CASE("read from file") {
    MenuDatabase menuDb;
    ifstream file;
    file.open("../textFiles/menuDb.txt");
    file >> menuDb; // write
    file.close();

    CustomEmployeesDb employeesDb;
    file.open("../textFiles/employeesDb.txt");
    file >> employeesDb; // write
    file.close();

    CustomTableDb tablesDb;
    file.open("../textFiles/tabasfddasflesDb.txt");
    file >> tablesDb; // write
    file.close();
    for (auto &worker : employeesDb.GetItems()){
        cout<< worker->get_name()<<"--";
    }
}

