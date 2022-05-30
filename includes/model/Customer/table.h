//
// Created by bkisl on 15.05.2022.
//

#ifndef CAFE_TABLE_H
#define CAFE_TABLE_H

#include <vector>
#include "customer.h"
#include "customersGroup.h"

class Table {
private:
    unsigned int id;
    unsigned int capacity = 0;
    bool hasAssignedWaiter = false;
    vector<Customer> customers;

    void customersGroupValidation(CustomersGroup &customersGroup);

    vector<shared_ptr<MenuItem>> menuItemsToPrepare;

public:
    Table();
    Table(unsigned int id, unsigned int capacity);

    unsigned int GetId() const;
    unsigned int GetCapacity() const;
    vector<Customer> &GetCustomers();
    bool GetHasAssignedWaiter() const;
    void SetHasAssignedWaiter(bool hasAssignedWaiter);

    unsigned int GetAmountOfItemsToPrepare() const;
    shared_ptr<MenuItem> GetLastItemToPrepare();

    void AddItemToPrepare(shared_ptr<MenuItem> menuItem);
    void  RemoveLastItemToPrepare();
    void AdvanceStateAll();

    bool TryAddCustomers(CustomersGroup &customersGroup);
    string ToString() const;
};


#endif //CAFE_TABLE_H
