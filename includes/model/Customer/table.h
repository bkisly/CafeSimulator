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
    unsigned int capacity;
    vector<Customer> customers;

    void customersGroupValidation(CustomersGroup &customersGroup);

    vector<shared_ptr<MenuItem>> menuItemsToPrepare;

public:
    Table();
    Table(unsigned int id, unsigned int capacity);

    unsigned int GetId() const;
    unsigned int GetCapacity() const;
    vector<Customer> &GetCustomers();

    unsigned int GetAmountOfItemsToPrepare() const;
    shared_ptr<MenuItem> GetLastItemToPrepare();
    void AddItemToPrepare(shared_ptr<MenuItem> menuItem);
    void  RemoveLastItemToPrepare();

<<<<<<< HEAD
    void AdvanceStateAll();

=======
>>>>>>> 3733401 (Added sample data to employees database in CafeModel)
    bool TryAddCustomers(CustomersGroup &customersGroup);
    string ToString() const;
};


#endif //CAFE_TABLE_H
