//
// Created by bkisl on 26.05.2022.
//

#include "../includes/View/cafeView.h"

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
    cout << "Adding new menu item..." << endl;
}

void CafeView::removeItem() {
    cout << "Removing a menu item..." << endl;
}

void CafeView::showMenu() {
    cout << "Showing menu..." << endl;
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

void CafeView::InitSimulation(unsigned int numberOfCycles) {
    try
    {
        model.Simulate(numberOfCycles);
        cout << model.GetSimulationLog() << endl;
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