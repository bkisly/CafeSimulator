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

    void customersGroupValidation(const CustomersGroup &customersGroup);

public:
    Table(unsigned int id, unsigned int capacity);

    unsigned int GetId() const;
    unsigned int GetCapacity() const;
    const vector<Customer> &GetCustomers() const;

    bool TryAddCustomers(const CustomersGroup &customersGroup);
    string ToString() const;
};


#endif //CAFE_TABLE_H
