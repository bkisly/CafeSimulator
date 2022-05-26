//
// Created by bkisl on 26.05.2022.
//

#ifndef CAFE_CUSTOMERSGROUP_H
#define CAFE_CUSTOMERSGROUP_H

#include <vector>
#include "customer.h"

class CustomersGroup {
private:
    vector<Customer> customers;
    void validateCustomers(const vector<Customer> &customers);

public:
    CustomersGroup(vector<Customer> &customers);
    vector<Customer> &GetCustomers();
    unsigned int GroupSize() const;
    bool AllowOthers() const;
};


#endif //CAFE_CUSTOMERSGROUP_H
