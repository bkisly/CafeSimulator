//
// Created by bkisl on 22.05.2022.
//

#include "../../includes/model/cafeModel.h"
#include "../../includes/controller/DataService.h"

// Generators

int CafeModel::randomInt(int min, int max) {
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 generator(seed);
    return (generator() % (max + 1 - min)) + min;
}

shared_ptr<MenuItem> CafeModel::randomMenuItem() {
    return menuDb.GetItems()[randomInt(0, menuDb.GetItems().size() - 1)];
}

Customer CafeModel::randomCustomer(bool allowsOthers) {
    totalCustomers++;
    return { totalCustomers, allowsOthers, randomMenuItem() };
}

// Simulation sub-procedures

void CafeModel::addNewCustomers() {
    unsigned int customersAmount = randomInt(1, 5);
    bool allowOthers = randomInt(0, 1) == 1;
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
        if(tablesDb.TryAssignCustomersGroup(customersGroup))
        {
            groupsIdsToRemove.push_back(groupId);
            assignedCustomers.insert(assignedCustomers.end(), customersGroup.GetCustomers().begin(), customersGroup.GetCustomers().end());
        }

        groupId++;
    }

    for(int id : groupsIdsToRemove)
        unassignedCustomers.erase(unassignedCustomers.begin() + id);
}

void CafeModel::printLog(vector<Customer> &assignedCustomers) {
    // 7a. Print header
    string block = "==========\nSIMULATION CYCLE NR " + to_string(currentCycle + 1) + "\n==========\n\n";
    simulationLogBlocks.push_back(block);

    // 7b. Print customers state
    block = "--- Customers state ---\n";
    for(Customer &customer : assignedCustomers)
        block += customer.ToString() + "\n";

    for(CustomersGroup customersGroup : unassignedCustomers)
    {
        for(Customer &customer : customersGroup.GetCustomers())
            block += customer.ToString() + "\n";
    }

    simulationLogBlocks.push_back(block);

    // 7c. Print tableDb.GetItems() state
    block = "\n--- Tables state ---\n";

    for(const auto &table : tablesDb.GetItems())
    {
        block += table->ToString() + "\n";
    }

    simulationLogBlocks.push_back(block);

    // 7d. Print employees state

    block = "\n--- Employees state ---\n";
    for(auto &employee : employeesDb.GetItems())
    {
        block += employee->printStateLog();
    }

    block += "\n";
    simulationLogBlocks.push_back(block);
}

CafeModel::CafeModel(string menuFile, string employeesFile, string tablesFile) {
    currentCycle = 0;
    totalCustomers = 0;

//    if(!readFromService || !DatabaseSimulationService::FileExists(DatabaseSimulationService::MENU_FILENAME))
//    {
//        vector<shared_ptr<MenuItem>> menuItems
//        {
//            make_shared<Beverage>("Coffee", Price(2, 49), CupType::Cup, 3),
//            make_shared<Beverage>("Water", Price(0, 99), CupType::Glass, 1),
//            make_shared<Beverage>("Tea", Price(1, 50), CupType::Mug, 2),
//
//            make_shared<Dessert>("Cake", Price(5, 99), 3),
//            make_shared<Dessert>("Ice cream", Price(0, 99), 2),
//
//            make_shared<Dish>("Caesar salad", Price(12, 99), false, 5),
//            make_shared<Dish>("Vegan wrap", Price(9, 99), true, 4)
//        };
//
//        menuDb = MenuDatabase(menuItems);
//
//        employeesDb.addCook("Jan", "Kowalski", 0, Price(25, 0), 2, 4);
//        employeesDb.addCook("Maciej", "Nowak", 0, Price(30, 0), 1, 5);
//        employeesDb.addCook("Bożena", "Kowalska", 1, Price(25, 0), 2, 6);
//
//        employeesDb.addWaiter("Borys", "Groch", 0, Price(15, 0), 1, true);
//        employeesDb.addWaiter("Grzegorz", "Brzęczyszczykiewicz", 0, Price(20, 0), 2, false);
//        employeesDb.addWaiter("Halina", "Grzmot", 1, Price(30, 0), 1, true);
//
//        vector<shared_ptr<Table>> initialTables
//        {
//            make_shared<Table>(1, 2),
//            make_shared<Table>(2, 2),
//            make_shared<Table>(3, 3),
//            make_shared<Table>(4, 4),
//            make_shared<Table>(5, 4),
//            make_shared<Table>(6, 5)
//        };
//
//        tableDb.GetItems() = initialTables;
//    }
//    else
//    {
//        // Load application data from service
//        menuDb = dbService.ReadMenu();
//    }

    this->menuFile = menuFile;
    this->employeesFile = employeesFile;
    this->tablesFile = tablesFile;

    service.ReadEmployees(employeesDb, this->employeesFile);
    service.ReadTables(tablesDb, this->tablesFile);
    service.ReadMenu(menuDb, this->menuFile);
}

// Getters

MenuDatabase &CafeModel::GetMenu() {
    return menuDb;
}

CustomEmployeesDb &CafeModel::GetEmployees() {
    return employeesDb;
}

CustomTableDb &CafeModel::GetTablesDb() {
    return tablesDb;
};

string CafeModel::GetSimulationLog() const {
    string simulationLog;

    for(const string &block : simulationLogBlocks)
        simulationLog += block;

    return simulationLog;
}

const vector<string> &CafeModel::GetSimulationLogBlocks() const {
    return simulationLogBlocks;
}

// Action methods

void CafeModel::Simulate(unsigned int cycles, unsigned int customersInterval) {
    if(cycles == 0) throw invalid_argument("Number of cycles must be a number greater than 0.");
    if(customersInterval == 0)
        throw invalid_argument("Customers appearance interval must be a number greater than 0.");

    currentCycle = 0;
    simulationLogBlocks.clear();

    while(currentCycle < cycles)
    {
        // Assigning customers must be performed as the last step before adding new ones
        // in order not to let the change propagate (we don't want to let the customer be assigned and serviced at once)

        // 1. Collect customers who sit by the tableDb.GetItems()
        vector<Customer> assignedCustomers;

        for(auto &table : tablesDb.GetItems())
        {
            for(Customer &customer : table->GetCustomers())
                assignedCustomers.push_back(customer);
        }


        // 2. Assign tableDb.GetItems() to free waiters
        for(auto &employee : employeesDb.GetItems())
        {
            if(typeid(*employee.get()) == typeid(Waiter&))
            {
                auto* waiter = dynamic_cast<Waiter*>(&*employee);

                if(waiter->getState() == Waiter::WaiterState::awaiting)
                {
                    for(auto &table : tablesDb.GetItems())
                    {
                        if(!table->GetHasAssignedWaiter() && !table->GetCustomers().empty())
                            waiter->setAssignedTable(table);
                    }
                }
            }
        }

        // 3. Remove served customers
        for(auto &table : tablesDb.GetItems())
            table->RemoveServedCustomers();

        // 4. Update state of all employees
        employeesDb.advanceCycleAll();

        // 4. Update state of all assigned customers
        tablesDb.AdvanceStateAllTables();

        // 5. Assign unassigned customers
        assignCustomers(assignedCustomers);

        // 6. Add new customers
        if(currentCycle % customersInterval == 0)
            addNewCustomers();

        // 7. Save log
        printLog(assignedCustomers);

        currentCycle++;
    }
}

void CafeModel::SaveMenu() {
    service.WriteMenu(menuDb, menuFile);
}

void CafeModel::SaveEmployees() {
    service.WriteEmployees(employeesDb, employeesFile);
}

void CafeModel::SaveTables() {
    service.WriteTables(tablesDb, tablesFile);
}

void CafeModel::SaveLog(const string &outputName) {
    dbService.WriteSimulationLog(GetSimulationLog(), outputName);
}