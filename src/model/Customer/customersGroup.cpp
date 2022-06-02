//
// Created by bkisl on 26.05.2022.
//

#include "../../../includes/model/Customer/customersGroup.h"
#include <stdexcept>

void CustomersGroup::validateCustomers(const vector<Customer> &customers) {
    map<unsigned int, int> idOccurrences;

    if(customers.empty())
        throw invalid_argument("Customers collection must not be empty.");

    for(auto iter = customers.begin(); iter < customers.end(); iter++)
    {
        if(iter > customers.begin() && iter->DoesAllowOthers() != (iter - 1)->DoesAllowOthers())
            throw invalid_argument("All customers must have identical preference regarding other customers presence.");

        unsigned int customerId = iter->GetId();

        if(!idOccurrences.contains(customerId))
            idOccurrences.insert(pair{ customerId, 0 });

        idOccurrences[customerId]++;
    }

    for(const auto& [key, value] : idOccurrences)
    {
        if(value > 1) throw invalid_argument("Customer IDs must be unique.");
    }
}

CustomersGroup::CustomersGroup(vector<Customer> &customers) {
    validateCustomers(customers);
    this->customers = customers;
}

vector<Customer> &CustomersGroup::GetCustomers() {
    return customers;
}

unsigned int CustomersGroup::GroupSize() const {
    return customers.size();
}

bool CustomersGroup::AllowOthers() const {
    return customers[0].DoesAllowOthers();
}