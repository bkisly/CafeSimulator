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
    vector<Customer> customersToAdd;

    for(int i = 0; i < customersAmount; i++) {
        customersToAdd.push_back(randomCustomer(allowOthers));
    }

    unassignedCustomers.push_back(CustomersGroup(customersToAdd));
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

        vector<Table> tables
        {
            Table(1, 2),
            Table(2, 2),
            Table(3, 3),
            Table(4, 4),
            Table(5, 4),
            Table(6, 5)
        };

        this->tables = tables;
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

const vector<CustomersGroup> &CafeModel::GetUnassignedCustomers() const {
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
    simulationLog = "";

    while(currentCycle < cycles)
    {
        // Assigning customers must be performed as the last step before adding new ones
        // in order not to let the change propagate (we don't want to let the customer be assigned and serviced at once)
        // 1. Collect customers who sit by the tables

        vector<Customer> assignedCustomers;
        for(Table table : tables)
        {
            for(Customer &customer : table.GetCustomers())
                assignedCustomers.push_back(customer);
        }

        // 2. Perform work for assigned customers
        // TODO: need EmployeesDatabase class to complete this step
        for(Customer &customer : assignedCustomers)
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

        vector<int> groupsIdsToRemove;
        // 3. Assign unassigned customers
        for(auto iter = unassignedCustomers.begin(); iter < unassignedCustomers.end(); iter++)
        {
            for(Table table : tables)
            {
                if(table.TryAddCustomers(*iter))
                {
                    groupsIdsToRemove.push_back(iter - unassignedCustomers.begin());
                    assignedCustomers.insert(assignedCustomers.end(), iter->GetCustomers().begin(), iter->GetCustomers().end());
                    break;
                }
            }
        }

        for(int id : groupsIdsToRemove)
            unassignedCustomers.erase(unassignedCustomers.begin() + id);

        // 4. Add new customers
        addNewCustomers();

        // 5. SAVE LOG

        // 5a. Print header
        simulationLog += "==========\nSIMULATION CYCLE NR " + to_string(currentCycle) + "\n==========\n\n";

        // 5b. Print customers state
        simulationLog += "--- Customers state ---\n";
        for(Customer customer : assignedCustomers)
            simulationLog += customer.ToString() + "\n";

        for(CustomersGroup customersGroup : unassignedCustomers)
        {
            for(Customer customer : customersGroup.GetCustomers())
                simulationLog += customer.ToString() + "\n";
        }

        // 5c. Print employees state

        simulationLog += "\n--- Employees state ---\n";
        // TODO: print employees state

        simulationLog += "\n\n";
        currentCycle++;
    }
}