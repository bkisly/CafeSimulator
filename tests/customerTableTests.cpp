//
// Created by bkisl on 17.05.2022.
//

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../includes/model/Customer/customer.h"
#include "../includes/model/MenuItem/beverage.h"
#include "../includes/model/Customer/table.h"

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

TEST_CASE("Table tests")
{
    SECTION("Table initialization")
    {
        REQUIRE_NOTHROW(Table(1, 5));
        REQUIRE_THROWS_AS(Table(1, 0), invalid_argument);

        Table table(1, 5);
        CHECK(table.GetId() == 1);
        CHECK(table.GetCapacity() == 5);
        CHECK(table.GetCustomers().empty());
    }

    SECTION("Adding customers")
    {
        Beverage coffee("Coffee", Price(2, 49), CupType::Cup, 4);

        vector<Customer> customers1;
        customers1.emplace_back(Customer(1, true, make_unique<Beverage>(coffee)));
        customers1.emplace_back(Customer(2, true, make_unique<Beverage>(coffee)));
        customers1.emplace_back(Customer(3, true, make_unique<Beverage>(coffee)));

        vector<Customer> customers2;
        customers2.emplace_back(Customer(4, true, make_unique<Beverage>(coffee)));
        customers2.emplace_back(Customer(5, true, make_unique<Beverage>(coffee)));

        vector<Customer> customers3;
        customers3.emplace_back(Customer(6, true, make_unique<Beverage>(coffee)));
        customers3.emplace_back(Customer(7, true, make_unique<Beverage>(coffee)));
        customers3.emplace_back(Customer(8, true, make_unique<Beverage>(coffee)));

        vector<Customer> customers4;
        customers4.emplace_back(Customer(9, false, make_unique<Beverage>(coffee)));
        customers4.emplace_back(Customer(10, false, make_unique<Beverage>(coffee)));

        vector<Customer> invalidCustomers1;
        invalidCustomers1.emplace_back(Customer(1, true, make_unique<Beverage>(coffee)));
        invalidCustomers1.emplace_back(Customer(2, true, make_unique<Beverage>(coffee)));

        vector<Customer> invalidCustomers2;
        invalidCustomers2.emplace_back(Customer(1, true, make_unique<Beverage>(coffee)));
        invalidCustomers2.emplace_back(Customer(1, false, make_unique<Beverage>(coffee)));

        Table table(1, 5);

        CHECK(table.TryAddCustomers(customers1));
        CHECK_FALSE(table.TryAddCustomers(customers3));
        CHECK_FALSE(table.TryAddCustomers(customers4));
        CHECK_THROWS_AS(table.TryAddCustomers(invalidCustomers1), invalid_argument);
        CHECK_THROWS_AS(table.TryAddCustomers(invalidCustomers2), invalid_argument);
        CHECK(table.TryAddCustomers(customers2));
    }

    SECTION("To string")
    {
        Table table1(1, 5);
        Table table2(2, 1);
        CHECK(table1.ToString() == "Table nr 1 for 5 people");
        CHECK(table2.ToString() == "Table nr 2 for 1 person");
    }
}