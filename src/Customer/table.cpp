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

bool Table::TryAddCustomers(CustomersGroup &customersGroup) {
    if(customersGroup.GroupSize() <= capacity - this->customers.size())
    {
        customersGroupValidation(customersGroup);
        for(Customer &customer : this->customers)
            if(!customer.DoesAllowOthers())
                return false;

        if(!customersGroup.AllowOthers() && !customers.empty()) return false;

        for(Customer &customer : customersGroup.GetCustomers()) {
            customer.AdvanceState();
            // @important - I suppose that here we might pass copy to table's vector of customers
            // so far it's not an issue, because waiter "works on table" and simulation processes customers
            // via table (loop creating assignedCustomers)
            customers.push_back(customer);
        }

        return true;
    }

    return false;
}

string Table::ToString() const {
    string peopleString = capacity > 1 ? " people" : " person";
    return "Table nr " + to_string(id) + " for " + to_string(capacity) + peopleString + " currently has " + to_string(customers.size()) + " customers";
}

unsigned int Table::GetAmountOfItemsToPrepare() const {
    return menuItemsToPrepare.size();
}


shared_ptr<MenuItem> Table::PopLastItemToPrepare() {
    shared_ptr<MenuItem> item =  menuItemsToPrepare.back();
    // TODO: why it was commented out?
     menuItemsToPrepare.pop_back();
    return item;
}

void Table::AddItemToPrepare(shared_ptr<MenuItem> menuItem) {
    menuItemsToPrepare.push_back(menuItem);
}

void Table::RemoveItemsToPrepare() {
    menuItemsToPrepare.clear();
}

void Table::AdvanceStateAll() {
    for(Customer &customer : customers)
    {
        customer.AdvanceState();
    }
}
#if DEBUG
void Table::ClearAllCustomers() {
    customers.clear();
}
#endif

bool Table::GetHasAssignedWaiter() const {
    return hasAssignedWaiter;
}

void Table::SetHasAssignedWaiter(bool hasAssignedWaiter) {
    this->hasAssignedWaiter = hasAssignedWaiter;
}

bool Table::HaveAllEaten() const {
    for(const Customer &customer : customers)
    {
        if(customer.GetCurrentState() == CustomerState::Eating)
            return false;
    }

    return true;
}

