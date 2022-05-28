//
// Created by bkisl on 15.05.2022.
//

#include "../../includes/model/Customer/customer.h"

Customer::Customer(unsigned int id, bool allowsOthers, shared_ptr<MenuItem> preferredMenuItem) {
    this->id = id;
    this->allowsOthers = allowsOthers;
    this->cyclesLeft = preferredMenuItem->GetCyclesToPrepare();
    this->preferredMenuItem = move(preferredMenuItem);
    currentState = CustomerState::Unassigned;
    this->collectedOrder = false;
    this->receivedReceipt = false;
}

unsigned int Customer::GetId() const {
    return id;
}

bool Customer::DoesAllowOthers() const {
    return allowsOthers;
}

const shared_ptr<MenuItem> &Customer::GetPreferredMenuItem() {
    return preferredMenuItem;
}

CustomerState Customer::GetCurrentState() const {
    return currentState;
}

void Customer::AdvanceState() {
    // advance state to awaiting only when waiter collected orders
    if (currentState == CustomerState::ReadyToOrder){
        if (this->collectedOrder){
            currentState = (CustomerState)((int)currentState + 1);
        }
    }
    // advance state to eating only after meal preparation
    // TODO: potential de-synchronisation, waiter might be preparing meal longer -> he
    //  may be waiting for free cook -> fix up or discard ??
    else if (currentState == CustomerState::Awaiting){
        if (this->cyclesLeft > 0){
            cyclesLeft--;
        }
        if (this->cyclesLeft == 0){
            currentState = (CustomerState)((int)currentState + 1);
        }
    }
    // advance state to unassigned only after waiter gives receipt
    else if (currentState == CustomerState::FinishedEating){
        if (this->receivedReceipt){
            // advance state
            currentState = (CustomerState) (((int) currentState + 1) % 6);
            // reset properties
            this->receivedReceipt = false;
            this->collectedOrder = false;
            // TODO: not sure whether customer will be "reused" in future cycles
        }
    }
    // other cases
    else {
        currentState = (CustomerState) ((int) currentState + 1);
    }
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
        case CustomerState::FinishedEating:
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

bool Customer::isCollectedOrder() const {
    return collectedOrder;
}

void Customer::setCollectedOrder(bool collectedOrder) {
    Customer::collectedOrder = collectedOrder;
}

bool Customer::isReceivedReceipt() const {
    return receivedReceipt;
}

void Customer::setReceivedReceipt(bool receivedReceipt) {
    Customer::receivedReceipt = receivedReceipt;
}
