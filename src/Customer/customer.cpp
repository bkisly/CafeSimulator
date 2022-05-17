//
// Created by bkisl on 15.05.2022.
//

#include "../../includes/model/Customer/customer.h"

Customer::Customer(unsigned int id, bool allowsOthers, unique_ptr<MenuItem> preferredMenuItem) {
    this->id = id;
    this->allowsOthers = allowsOthers;
    this->preferredMenuItem = move(preferredMenuItem);
    currentState = CustomerState::Unassigned;
}

unsigned int Customer::GetId() const {
    return id;
}

bool Customer::DoesAllowOthers() const {
    return allowsOthers;
}

const unique_ptr<MenuItem> &Customer::GetPreferredMenuItem() {
    return preferredMenuItem;
}

CustomerState Customer::GetCurrentState() const {
    return currentState;
}

void Customer::AdvanceState() {
    currentState = (CustomerState)(((int)currentState + 1) % 6);
}

string Customer::ToString() {
    string result = "Customer nr " + to_string(id) + " ";

    switch (currentState) {
        case CustomerState::SitTaken:
        {
            result += "has taken the seat.";
            break;
        }
        case CustomerState::ReadyToOrder:
        {
            result += "is ready to order.";
            break;
        }
        case CustomerState::Awaiting:
        {
            result += "is awaiting for " + preferredMenuItem->GetName();
            break;
        }
        case CustomerState::Eating:
        {
            result += "is eating/drinking " + preferredMenuItem->GetName();
            break;
        }
        case CustomerState::ReadyToPay:
        {
            result += "is ready to pay.";
            break;
        }
        default:
        {
            result += "is not assigned to any table.";
            break;
        }
    }

    return result;
}