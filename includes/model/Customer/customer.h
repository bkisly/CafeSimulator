//
// Created by bkisl on 15.05.2022.
//

#ifndef CAFE_CUSTOMER_H
#define CAFE_CUSTOMER_H

#include <memory>
#include "../MenuItem/menuItem.h"

enum class CustomerState
{
    Unassigned,
    SitTaken,
    ReadyToOrder,
    Awaiting,
    Eating,
    ReadyToPay,
};

class Customer {
private:
    unsigned int id;
    bool allowsOthers;
    shared_ptr<MenuItem> preferredMenuItem;

    CustomerState currentState;
    bool collectedOrder, receivedReceipt;
    int cyclesLeft;

public:
    Customer(unsigned int id, bool allowsOthers, shared_ptr<MenuItem> preferredMenuItem);

    unsigned int GetId() const;
    bool DoesAllowOthers() const;
    const shared_ptr<MenuItem> &GetPreferredMenuItem();
    CustomerState GetCurrentState() const;

    void AdvanceState();
    string ToString();
};


#endif //CAFE_CUSTOMER_H
