//
// Created by bkisl on 15.05.2022.
//

#include "../../includes/model/Customer/table.h"

void Table::customersValidation(const vector<Customer> &customers) {
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

    for(Customer &customer : this->customers)
    {
        unsigned int customerId = customer.GetId();

        if(!idOccurrences.contains(customerId))
            idOccurrences.insert(pair{ customerId, 0 });

        idOccurrences[customerId]++;
    }

    for(const auto& [key, value] : idOccurrences)
    {
        if(value > 1) throw invalid_argument("Customer IDs must be unique.");
    }
}

Table::Table(unsigned int id, unsigned int capacity) {
    if(capacity == 0) throw invalid_argument("Table capacity must be greater than 0.");

    this->id = id;
    this->capacity = capacity;
}

unsigned int Table::GetId() const {
    return id;
}

unsigned int Table::GetCapacity() const {
    return capacity;
}

const vector<Customer> &Table::GetCustomers() const {
    return customers;
}

bool Table::TryAddCustomers(vector<Customer> &customers) {
    if(customers.size() <= capacity - this->customers.size())
    {
        customersValidation(customers);
        for(Customer &customer : this->customers)
            if(!customer.DoesAllowOthers())
                return false;

        for(Customer &customer : customers)
        {
            if (!customer.DoesAllowOthers())
                return false;

            this->customers.push_back(move(customer));
        }

        return true;
    }

    return false;
}

string Table::ToString() {
    string peopleString = capacity > 1 ? " people" : " person";
    return "Table nr " + to_string(id) + " for " + to_string(capacity) + peopleString;
}