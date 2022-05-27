//
// Created by bkisl on 15.05.2022.
//

#include "../../includes/model/Customer/table.h"
#include <stdexcept>

void Table::customersGroupValidation(CustomersGroup &customersGroup) {
    map<unsigned int, int> idOccurrences;

    for(Customer &customer : customersGroup.GetCustomers())
    {
        unsigned int customerId = customer.GetId();

        if(!idOccurrences.contains(customerId))
            idOccurrences.insert(pair{ customerId, 0 });

        idOccurrences[customerId]++;
    }

    for(const Customer &customer : this->customers)
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

Table::Table() {

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

vector<Customer> &Table::GetCustomers() {
    return customers;
}

bool Table::TryAddCustomers(CustomersGroup customersGroup) {
    if(customersGroup.GroupSize() <= capacity - this->customers.size())
    {
        customersGroupValidation(customersGroup);
        for(Customer &customer : this->customers)
            if(!customer.DoesAllowOthers())
                return false;

        if(!customersGroup.AllowOthers() && !customers.empty()) return false;

        for(Customer &customer : customersGroup.GetCustomers()) {
            customer.AdvanceState();
            customers.push_back(customer);
            menuItemsToPrepare.push_back(customer.GetPreferredMenuItem());
        }

        return true;
    }

    return false;
}

string Table::ToString() const {
    string peopleString = capacity > 1 ? " people" : " person";
    return "Table nr " + to_string(id) + " for " + to_string(capacity) + peopleString + " currently has " + to_string(customers.size()) + " customers";
}

unsigned int Table::GetAmountOfItemToPrepare() const {
    return menuItemsToPrepare.size();
}
