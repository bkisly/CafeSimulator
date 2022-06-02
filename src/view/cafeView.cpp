//
// Created by bkisl on 26.05.2022.
//

#include "../../includes/View/cafeView.h"

unsigned int CafeView::printOptions(string header, vector<string> options) {
    cout << header << endl;

    for(int i = 0; i < options.size(); i++)
    {
        cout << i + 1 << ". " << options[i] << endl;
    }

    bool validOption = false;
    string selectedOptionString;
    unsigned int selectedOption;

    do {
        stringstream ss;
        cin >> selectedOptionString;
        ss << selectedOptionString;
        ss >> selectedOption;

        if(selectedOption - 1 >= options.size())
            cerr << "Invalid option number. Try again." << endl;
        else validOption = true;
    }
    while(!validOption);

    return selectedOption - 1;
}

// Menu items options

void CafeView::addItem() {
    cout << "Adding new menu item..." << endl << endl;

    vector<string> itemTypeOptions = {
            "Beverage",
            "Dessert",
            "Dish",
            "Cancel"
    };

    bool validItem = false;

    while(!validItem)
    {
        unsigned int itemType = printOptions("Select type of the item to add:", itemTypeOptions);
        if(itemType == 3) return;

        string itemName;
        stringstream ss;
        unsigned int dollars;
        string dollarsString;
        unsigned int cents;
        string centsString;
        unsigned int cyclesToPrepare;
        string cyclesString;

        cout << "Item name: ";
        cin.ignore();
        getline(cin, itemName);

        cout << "Price (dollars part): ";
        cin >> dollarsString;
        ss << dollarsString;
        ss >> dollars;
        ss.clear();

        cout << "Price (cents part): ";
        cin >> centsString;
        ss << centsString;
        ss >> cents;
        ss.clear();

        cout << "Cycles to prepare:";
        cin >> cyclesString;
        ss << cyclesString;
        ss >> cyclesToPrepare;
        ss.clear();

        try
        {
            Price price(dollars, cents);

            switch (itemType) {
                case 0:
                {
                    vector<string> cupTypes = {
                            "Cup",
                            "Mug",
                            "Glass"
                    };

                    unsigned int cupType = printOptions("Select cup type:", cupTypes);
                    model.GetMenu().AddItem(make_shared<Beverage>(itemName, price, (CupType)cupType, cyclesToPrepare));
                    break;
                }
                case 1:
                {
                    model.GetMenu().AddItem(make_shared<Dessert>(itemName, price, cyclesToPrepare));
                    break;
                }
                case 2:
                {
                    vector<string> vegetarianOptions = {
                            "Yes",
                            "No"
                    };

                    bool vegetarian = false;
                    if(printOptions("Select whether the dish is vegetarian:", vegetarianOptions) == 0)
                        vegetarian = true;

                    model.GetMenu().AddItem(make_shared<Dish>(itemName, price, vegetarian, cyclesToPrepare));
                    break;
                }
            }

            cout << "Successfully added new item!" << endl << endl;
            model.SaveMenu();
            validItem = true;
        }
        catch (exception &e)
        {
            cerr << "An error has occurred while adding new item: " << e.what() << endl;
            cerr << "Try again." << endl << endl;
        }
    }
}

void CafeView::removeItem() {
    cout << "Removing a menu item..." << endl << endl;

    for(const auto &item : model.GetMenu().GetItems())
    {
        cout << item->ToString() << endl;
    }

    string itemName;
    cout << endl << "Type item name to remove: ";
    cin.ignore();
    getline(cin, itemName);

    try
    {
        model.GetMenu().RemoveItem(itemName);
        model.SaveMenu();
        cout << "Successfully removed an item!" << endl << endl;
    }
    catch(exception &e)
    {
        cerr << "An error has occurred while removing an item: " << e.what() << endl << endl;
    }
}

void CafeView::showMenu() {
    int positionNumber = 1;
    cout << "Showing menu..." << endl;

    for(const auto &item : model.GetMenu().GetItems())
    {
        cout << positionNumber << ". " << item->ToString() << endl;
        positionNumber++;
    }

    cout << endl;
}

// Employee options

void CafeView::addEmployee() {
    cout << "Adding new employee..." << endl << endl;

    vector<string> employeeTypes = {
        "Waiter",
        "Cook",
        "Cancel"
    };

    bool finished = false;

    do {
        unsigned int employeeTypeOption = printOptions("Select employee type to add:", employeeTypes);

        if(employeeTypeOption == 2) break;

        stringstream ss;
        string name, surname, dollarsString, centsString, shiftsString;
        unsigned int dollars, cents, shifts;

        cout << "Name: ";

        if(cin.peek() == '\n')
            cin.ignore();

        getline(cin, name);

        cout << "Surname: ";

        if(cin.peek() == '\n')
            cin.ignore();

        getline(cin, surname);

        vector<string> genderOptions = { "Female", "Male" };
        int gender = (int)printOptions("Gender:", genderOptions);

        cout << "Salary (dollars part): ";
        cin >> dollarsString;
        ss << dollarsString;
        ss >> dollars;
        ss.clear();
        cout << endl;

        cout << "Salary (cents part): ";
        cin >> centsString;
        ss << centsString;
        ss >> cents;
        ss.clear();
        cout << endl;

        cout << "Shifts amount: ";
        cin >> shiftsString;
        ss << shiftsString;
        ss >> shifts;
        ss.clear();
        cout << endl;

        try
        {
            Price salary(dollars, cents);

            switch (employeeTypeOption) {
                case 0:
                {
                    vector<string> alcoholOptions = { "Yes", "No" };
                    unsigned int alcoholOption = printOptions("Choose whether the waiter can serve alcohol or not:", alcoholOptions);
                    bool canServeAlcohol = alcoholOption == 0;

                    model.GetEmployees().addWaiter(name, surname, gender, salary, shifts, canServeAlcohol);
                    break;
                }
                case 1:
                {

                    string cuisinesString;
                    unsigned int cuisines;

                    cout << "Known cuisines amount: ";
                    cin >> cuisinesString;
                    ss << cuisinesString;
                    ss >> cuisines;
                    ss.clear();
                    cout << endl;

                    model.GetEmployees().addCook(name, surname, gender, salary, shifts, cuisines);
                    break;
                }
                default:
                {
                    finished = true;
                    break;
                }
            }
        }
        catch(exception &e)
        {
            cerr << "An error has occurred while adding new employee: " << e.what() << endl << "Try again." << endl << endl;
            continue;
        }

        cout << "Successfully added new employee!" << endl << endl;
        model.SaveEmployees();
        finished = true;
    }
    while(!finished);
}

void CafeView::removeEmployee() {
    cout << "Removing an employee..." << endl << endl;

    unsigned int id;
    string idString;
    stringstream ss;

    cout << "Type employee ID to remove: ";
    cin >> idString;
    ss << idString;
    ss >> id;

    try
    {
        model.GetEmployees().RemoveItem(id);
        model.SaveEmployees();
        cout << "Successfully removed an employee!" << endl << endl;
    }
    catch(exception &e)
    {
        cerr << "An error has occurred while removing an employee: " << e.what() << endl << endl;
    }
}

void CafeView::showEmployees() {
    cout << "Showing employees collection..." << endl << endl;

    for(auto &employee : model.GetEmployees().GetItems())
        cout << employee->printProperties() << endl;

    cout << endl;
}


// Table options

void CafeView::addTable() {
    cout << "Adding new table..." << endl << endl;

    unsigned int capacity;
    string capacityString;
    stringstream ss;

    cout << "Enter table capacity: ";
    cin >> capacityString;
    ss << capacityString;
    ss >> capacity;

    try {
        model.GetTablesDb().AddTable(capacity);
        model.SaveTables();
        cout << "Successfully added a table!" << endl << endl;
    }
    catch(exception &e)
    {
        cerr << "An error has occurred while adding new table: " << e.what() << endl << endl;
    }
}

void CafeView::removeTable() {
    cout << "Removing a table..." << endl << endl;

    unsigned int id;
    string idString;
    stringstream ss;

    cout << "Type table ID to remove: ";
    cin >> idString;
    ss << idString;
    ss >> id;

    try
    {
        model.GetTablesDb().RemoveItem(id);
        model.SaveTables();
        cout << "Successfully removed a table!" << endl << endl;
    }
    catch(exception &e)
    {
        cerr << "An error has occurred while removing a table: " << e.what() << endl << endl;
    }
}

void CafeView::showTables() {
    cout << "Showing tables collection..." << endl;

    for(auto &table : model.GetTablesDb().GetItems())
        cout << table->ToString() << endl;

    cout << endl;
}

// Public members

CafeView::CafeView(string menuFile, string employeesFile, string tablesFile) {
    // TODO: try-catch should be added here while reading from service - errors may occur
    try
    {
        model = CafeModel(menuFile, employeesFile, tablesFile);
    }
    catch(exception &e)
    {
        cerr << "An error has occurred while reading databases from given files: " << e.what() << endl;
    }
}

void CafeView::InitSimulation(unsigned int numberOfCycles, double intervalSeconds, unsigned int customersInterval, const string& outputName) {
    try
    {
        model.Simulate(numberOfCycles, customersInterval);
        model.SaveLog(outputName);

        for(const string &block : model.GetSimulationLogBlocks())
        {
            cout << block;
            this_thread::sleep_for(chrono::milliseconds((int)(intervalSeconds * 1000)));
        }
    }
    catch(exception &e)
    {
        cerr << "An error has occurred while performing simulation: " << e.what() << endl;
    }
}

void CafeView::InitAdminMode() {
    cout << "==================\nCAFE SIMULATOR ADMIN MODE\n==================" << endl << endl;

    vector<string> mainMenuOptions {
            "Add menu item",
            "Remove menu item",
            "Show menu",
            "Add employee",
            "Remove employee",
            "Show employees",
            "Add table",
            "Remove table",
            "Show tables",
            "Exit"
    };

    bool exitSelected = false;

    do {
        unsigned int selectedOption = printOptions("Choose the operation to perform:", mainMenuOptions);

        switch (selectedOption) {
            case 0:
            {
                addItem();
                break;
            }
            case 1:
            {
                removeItem();
                break;
            }
            case 2:
            {
                showMenu();
                break;
            }
            case 3:
            {
                addEmployee();
                break;
            }
            case 4:
            {
                removeEmployee();
                break;
            }
            case 5:
            {
                showEmployees();
                break;
            }
            case 6:
            {
                addTable();
                break;
            }
            case 7:
            {
                removeTable();
                break;
            }
            case 8:
            {
                showTables();
                break;
            }
            default:
            {
                exitSelected = true;
                break;
            }
        }
    }
    while(!exitSelected);
}