//
// Created by bkisl on 15.05.2022.
//

#ifndef CAFE_TABLE_H
#define CAFE_TABLE_H

#include <vector>
#include "customer.h"

class Table {
private:
    unsigned int id;
    unsigned int capacity;
    vector<Customer> customers;

    void customersValidation(const vector<Customer> &customers);

public:
    Table(unsigned int id, unsigned int capacity);

    unsigned int GetId() const;
    unsigned int GetCapacity() const;
    const vector<Customer> &GetCustomers() const;

    bool TryAddCustomers(vector<Customer> customers);
    string ToString();
};


#endif //CAFE_TABLE_H
