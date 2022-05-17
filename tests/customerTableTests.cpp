//
// Created by bkisl on 17.05.2022.
//

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../includes/model/Customer/customer.h"
#include "../includes/model/Customer/table.h"
#include "../includes/model/MenuItem/beverage.h"

TEST_CASE("Customer tests")
{
    Beverage coffee("Coffee", Price(2, 49), CupType::Cup, 4);
    Customer customer(1, true, make_unique<Beverage>(coffee));
    SECTION("Customer initialization")
    {
        REQUIRE_NOTHROW(Customer(1, true, make_unique<Beverage>("Coffee", Price(2, 49), CupType::Cup, 4)));

        CHECK(customer.GetId() == 1);
        CHECK(customer.DoesAllowOthers());
        CHECK(customer.GetPreferredMenuItem()->GetName() == "Coffee");
        CHECK(customer.GetCurrentState() == CustomerState::Unassigned);
    }

    SECTION("Advance state")
    {
        customer.AdvanceState();
        CHECK(customer.GetCurrentState() == CustomerState::SitTaken);

        customer.AdvanceState();
        CHECK(customer.GetCurrentState() == CustomerState::ReadyToOrder);

        customer.AdvanceState();
        CHECK(customer.GetCurrentState() == CustomerState::Awaiting);

        customer.AdvanceState();
        CHECK(customer.GetCurrentState() == CustomerState::Eating);

        customer.AdvanceState();
        CHECK(customer.GetCurrentState() == CustomerState::ReadyToPay);

        customer.AdvanceState();
        CHECK(customer.GetCurrentState() == CustomerState::Unassigned);
    }

    SECTION("To string")
    {
        CHECK(customer.ToString() == "Customer nr 1 is not assigned to any table.");

        customer.AdvanceState();
        CHECK(customer.ToString() == "Customer nr 1 has taken the seat.");

        customer.AdvanceState();
        CHECK(customer.ToString() == "Customer nr 1 is ready to order.");

        customer.AdvanceState();
        CHECK(customer.ToString() == "Customer nr 1 is awaiting for Coffee");

        customer.AdvanceState();
        CHECK(customer.ToString() == "Customer nr 1 is eating/drinking Coffee");

        customer.AdvanceState();
        CHECK(customer.ToString() == "Customer nr 1 is ready to pay.");
    }
}