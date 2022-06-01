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
    Table() = default;
    Table(unsigned int id, unsigned int capacity);

    unsigned int GetId() const;
    unsigned int GetCapacity() const;
    vector<Customer> &GetCustomers();
    bool GetHasAssignedWaiter() const;
    void SetHasAssignedWaiter(bool hasAssignedWaiter);

    unsigned int GetAmountOfItemsToPrepare() const;
    shared_ptr<MenuItem> PopLastItemToPrepare();
    void AddItemToPrepare(shared_ptr<MenuItem> menuItem);
    void  RemoveItemsToPrepare();

    void AdvanceStateAll();

    bool TryAddCustomers(CustomersGroup &customersGroup);
    string ToString() const;

    ostream &Write(ostream &os) ;
    istream &Read(istream &is);

#if DEBUG
    // only for tests
    void ClearAllCustomers();
#endif
};


#endif //CAFE_TABLE_H
