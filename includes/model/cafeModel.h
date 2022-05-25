//
// Created by bkisl on 22.05.2022.
//

#ifndef CAFE_CAFEMODEL_H
#define CAFE_CAFEMODEL_H

#include <cstdlib>

#include "Databases/menuDatabase.h"
#include "Customer/customer.h"
#include "Customer/table.h"

#include "MenuItem/beverage.h"
#include "MenuItem/dessert.h"
#include "MenuItem/dish.h"

class CafeModel {
private:
    // Cafe resources
    MenuDatabase menuDb = MenuDatabase(make_shared<Beverage>("Coffee", Price(2, 49), CupType::Cup, 3));
    vector<Table> tables;

    // Simulation status
    vector<Customer> unassignedCustomers;
    unsigned int currentCycle;
    string simulationLog;
    unsigned int totalCustomers;

    // Value generators
    shared_ptr<MenuItem> randomMenuItem();
    Customer randomCustomer(bool allowsOthers);
    void addNewCustomers();

public:
    CafeModel(bool readFromService = true);    // readFromService parameter decides whether to read cafe information using DatabaseService object or read defaults for test purposes

    // Getters
    const MenuDatabase &GetMenu() const;
    const vector<Customer> &GetUnassignedCustomers() const;
    const vector<Table> &GetTables() const;
    unsigned int GetCurrentCycle() const;
    string GetSimulationLog() const;

    // Action methods
    void Simulate(unsigned int cycles);
};


#endif //CAFE_CAFEMODEL_H
