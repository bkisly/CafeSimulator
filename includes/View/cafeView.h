//
// Created by bkisl on 26.05.2022.
//

#ifndef CAFE_CAFEVIEW_H
#define CAFE_CAFEVIEW_H

#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include "../model/cafeModel.h"

using std::cout, std::cerr, std::endl;

class CafeView {
private:
    CafeModel model;
    unsigned int printOptions(string header, vector<string> options);

    // Menu items options
    void addItem();
    void removeItem();
    void showMenu();

    // Employee options
    void addEmployee();
    void removeEmployee();
    void showEmployees();

    // Tables options
    void addTable();
    void removeTable();
    void showTables();

public:
    CafeView(string menuFile = "menuDb.txt", string employeesFile = "employeesDb.txt", string tablesFile = "tablesDb.txt");

    void InitAdminMode();
    void InitSimulation(unsigned int numberOfCycles, double intervalSeconds, unsigned int customersInterval, const string& outputName);
};


#endif //CAFE_CAFEVIEW_H
