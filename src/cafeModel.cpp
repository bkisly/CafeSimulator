//
// Created by bkisl on 22.05.2022.
//

#include "../includes/model/cafeModel.h"

// Generators

shared_ptr<MenuItem> CafeModel::randomMenuItem() {
    return menuDb.GetItems()[rand() % menuDb.GetItems().size()];
}

Customer CafeModel::randomCustomer(bool allowsOthers) {
    totalCustomers++;
    return Customer(totalCustomers, allowsOthers, randomMenuItem());
}

void CafeModel::addNewCustomers() {
    unsigned int customersAmount = rand() % 5 + 1;
    bool allowOthers = rand() % 2 == 1;

    for(int i = 0; i < customersAmount; i++) {
        unassignedCustomers.push_back(randomCustomer(allowOthers));
    }
}

CafeModel::CafeModel(bool readFromService) {
    if(!readFromService)
    {
        vector<shared_ptr<MenuItem>> menuItems
        {
            make_shared<Beverage>("Coffee", Price(2, 49), CupType::Cup, 3),
            make_shared<Beverage>("Water", Price(0, 99), CupType::Glass, 1),
            make_shared<Beverage>("Tea", Price(1, 50), CupType::Mug, 2),

            make_shared<Dessert>("Cake", Price(5, 99), 3),
            make_shared<Dessert>("Ice cream", Price(0, 99), 2),

            make_shared<Dish>("Caesar salad", Price(12, 99), false, 5),
            make_shared<Dish>("Vegan wrap", Price(9, 99), true, 4)
        };

        menuDb = MenuDatabase(menuItems);
    }
    else
    {
        // TODO: load application data from service
    }
}

// Getters

const MenuDatabase &CafeModel::GetMenu() const {
    return menuDb;
}

const vector<Customer> &CafeModel::GetUnassignedCustomers() const {
    return unassignedCustomers;
}

const vector<Table> &CafeModel::GetTables() const {
    return tables;
}

unsigned int CafeModel::GetCurrentCycle() const {
    return currentCycle;
}

string CafeModel::GetSimulationLog() const {
    return simulationLog;
}

// Action methods

void CafeModel::Simulate(unsigned int cycles) {
    currentCycle = 0;

    while(currentCycle < cycles)
    {
        // Assigning customers must be performed as the last step before adding new ones
        // in order not to let the change propagate (we don't want to let the customer be assigned and serviced at once)
        // 1. Collect customers who sit by the tables

        vector<Customer> assignedCustomers;
        for(Table table : tables)
        {
            for(Customer customer : table.GetCustomers())
                assignedCustomers.push_back(customer);
        }

        // 2. Perform work for assigned customers
        // TODO: need EmployeesDatabase class to complete this step
        for(Customer customer : assignedCustomers)
        {
            switch (customer.GetCurrentState())
            {
                case CustomerState::SitTaken:
                {
                    break;
                }
                case CustomerState::ReadyToOrder:
                {
                    break;
                }
                case CustomerState::Awaiting:
                {
                    break;
                }
                case CustomerState::Eating:
                {
                    break;
                }
                case CustomerState::ReadyToPay:
                {
                    break;
                }
                default:
                    break;
            }
        }

        // 3. Assign unassigned customers
        // TODO: modify Table implementation in order to assign single customers

        // 4. Add new customers
        addNewCustomers();

        // 5. Print every customer's state

        // 6. Print every employee's state

        currentCycle++;
    }
}