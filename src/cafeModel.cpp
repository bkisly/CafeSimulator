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
    return { totalCustomers, allowsOthers, randomMenuItem() };
}

// Simulation sub-procedures

void CafeModel::addNewCustomers() {
    unsigned int customersAmount = rand() % 5 + 1;
    bool allowOthers = rand() % 2 == 1;
    vector<Customer> customersToAdd;

    for(int i = 0; i < customersAmount; i++) {
        customersToAdd.push_back(randomCustomer(allowOthers));
    }

    unassignedCustomers.emplace_back(CustomersGroup(customersToAdd));
}

void CafeModel::assignCustomers(vector<Customer> &assignedCustomers) {
    vector<int> groupsIdsToRemove;
    int groupId = 0;
    for(CustomersGroup &customersGroup : unassignedCustomers)
    {
        for(Table &table : tables)
        {
            if(table.TryAddCustomers(customersGroup))
            {
                groupsIdsToRemove.push_back(groupId);
                assignedCustomers.insert(assignedCustomers.end(), customersGroup.GetCustomers().begin(), customersGroup.GetCustomers().end());
                break;
            }
        }

        groupId++;
    }

    for(int id : groupsIdsToRemove)
        unassignedCustomers.erase(unassignedCustomers.begin() + id);
}

void CafeModel::saveLog(vector<Customer> &assignedCustomers) {
    // 5a. Print header
    simulationLog += "==========\nSIMULATION CYCLE NR " + to_string(currentCycle + 1) + "\n==========\n\n";

    // 5b. Print customers state
    simulationLog += "--- Customers state ---\n";
    for(Customer &customer : assignedCustomers)
        simulationLog += customer.ToString() + "\n";

    for(CustomersGroup customersGroup : unassignedCustomers)
    {
        for(Customer &customer : customersGroup.GetCustomers())
            simulationLog += customer.ToString() + "\n";
    }

    // 5c. Print tables state
    simulationLog += "\n--- Tables state ---\n";

    for(const Table &table : tables)
    {
        simulationLog += table.ToString() + "\n";
    }

    // 5d. Print employees state

    simulationLog += "\n--- Employees state ---\n";
    // TODO: print employees state

    simulationLog += "\n\n";
}

CafeModel::CafeModel(bool readFromService) {
    currentCycle = 0;
    totalCustomers = 0;

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

        vector<Table> initialTables
        {
            Table(1, 2),
            Table(2, 2),
            Table(3, 3),
            Table(4, 4),
            Table(5, 4),
            Table(6, 5)
        };

        tables = initialTables;
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
    if(cycles == 0) throw invalid_argument("Number of cycles must be a number greater than 0.");

    currentCycle = 0;
    simulationLog = "";

    while(currentCycle < cycles)
    {
        // Assigning customers must be performed as the last step before adding new ones
        // in order not to let the change propagate (we don't want to let the customer be assigned and serviced at once)

        // 1. Collect customers who sit by the tables
        vector<Customer> assignedCustomers;
        for(Table &table : tables)
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
                case CustomerState::FinishedEating:
                {
                    break;
                }
                default:
                    break;
            }
        }

        // 3. Assign unassigned customers
        assignCustomers(assignedCustomers);

        // 4. Add new customers
        addNewCustomers();

        // 5. SAVE LOG
        saveLog(assignedCustomers);

        currentCycle++;
    }
}