//
// Created by bkisl on 22.05.2022.
//

#include "../includes/model/cafeModel.h"

CafeModel::CafeModel(bool readFromService) {
    // TODO: implement CafeModel constructor which initializes menu with sample value
}

// Getters

const MenuDatabase &CafeModel::GetMenu() const {
    return menuDb;
}

const vector<Customer> &CafeModel::GetUnassignedCustomers() const {
    return unassignedCustomers;
}

const vector<Table> &CafeModel::GetTables() const {
    return tables;
}

unsigned int CafeModel::GetCurrentCycle() const {
    return currentCycle;
}

// Action methods

void CafeModel::Simulate(unsigned int cycles) {
    currentCycle = 0;

    while(currentCycle < cycles)
    {
        // TODO: magic here!

        currentCycle++;
    }
}