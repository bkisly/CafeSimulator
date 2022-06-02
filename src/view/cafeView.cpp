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
        cout << "Successfully removed an item!" << endl << endl;
        model.SaveMenu();
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
}

void CafeView::removeEmployee() {
    cout << "Removing an employee..." << endl << endl;
}

void CafeView::showEmployees() {
    cout << "Showing employees collection..." << endl << endl;
}


// Table options

void CafeView::addTable() {
    cout << "Adding new table..." << endl;
}

void CafeView::removeTable() {
    cout << "Removing a table..." << endl;
}

void CafeView::showTables() {
    cout << "Showing tables collection..." << endl;
}

// Public members

CafeView::CafeView(bool readFromService) {
    // TODO: try-catch should be added here while reading from service - errors may occur
    model = CafeModel(readFromService);
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