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
    unique_ptr<MenuItem> preferredMenuItem;

    CustomerState currentState;

public:
    Customer(unsigned int id, bool allowsOthers, unique_ptr<MenuItem> preferredMenuItem);

    unsigned int GetId() const;
    bool DoesAllowOthers() const;
    const unique_ptr<MenuItem> &GetPreferredMenuItem();
    CustomerState GetCurrentState() const;

    void AdvanceState();
    string ToString();
};


#endif //CAFE_CUSTOMER_H
