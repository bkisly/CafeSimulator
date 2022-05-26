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

public:
    Table(unsigned int id, unsigned int capacity);

    unsigned int GetId() const;
    unsigned int GetCapacity() const;
    vector<Customer> &GetCustomers();

    bool TryAddCustomers(CustomersGroup &customersGroup);
    string ToString() const;
};


#endif //CAFE_TABLE_H
