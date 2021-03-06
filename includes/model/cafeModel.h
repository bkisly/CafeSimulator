//
// Created by bkisl on 22.05.2022.
//

#ifndef CAFE_CAFEMODEL_H
#define CAFE_CAFEMODEL_H

#include <cstdlib>
#include <random>
#include <chrono>

#include "MenuItem/beverage.h"
#include "MenuItem/dessert.h"
#include "MenuItem/dish.h"

#include "Databases/menuDatabase.h"
#include "../controller/databaseSimulationService.h"
#include "../controller/DataService.h"
#include "Databases/CustomTableDb.h"
#include "Databases/CustomEmployeesDb.h"
#include "Databases/CustomTableDb.h"

#include "Customer/customer.h"
#include "Customer/customersGroup.h"
#include "Customer/table.h"

class CafeModel {
private:
    // Cafe resources
    MenuDatabase menuDb = MenuDatabase(make_shared<Beverage>("Coffee", Price(2, 49), CupType::Cup, 3));
    CustomEmployeesDb employeesDb;
    DatabaseSimulationService dbService;
    CustomTableDb tablesDb;

    // Service information
    DataService service;
    string menuFile, employeesFile, tablesFile;

    // Simulation status
    vector<CustomersGroup> unassignedCustomers;
    unsigned int currentCycle;
    vector<string> simulationLogBlocks;
    unsigned int totalCustomers;

    // Value generators
    int randomInt(int min, int max);
    shared_ptr<MenuItem> randomMenuItem();
    Customer randomCustomer(bool allowsOthers);

    // Simulation sub-procedures
    void addNewCustomers();
    void assignCustomers(vector<Customer> &assignedCustomers);
    void printLog(vector<Customer> &assignedCustomers);

public:
    CafeModel(string menuFile = "menuDb.txt", string employeesFile = "employeesDb.txt", string tablesFile = "tablesDb.txt");    // readFromService parameter decides whether to read cafe information using DatabaseSimulationService object or Read defaults for test purposes

    // Getters
    MenuDatabase &GetMenu();
    CustomEmployeesDb &GetEmployees();
    CustomTableDb &GetTablesDb();
    string GetSimulationLog() const;
    const vector<string> &GetSimulationLogBlocks() const;

    // Action methods
    void Simulate(unsigned int cycles, unsigned int customersInterval);

    // Serialization
    void SaveMenu();
    void SaveEmployees();
    void SaveTables();
    void SaveLog(const string &outputName);
};


#endif //CAFE_CAFEMODEL_H
