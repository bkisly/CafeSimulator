#include <iostream>
#include "includes/View/cafeView.h"

void printHelp()
{
    cout << "USAGE:" << endl;
    cout << "-h -> open help" << endl;
    cout << "-s [number of cycles] [print interval] [customers interval] [output "
            "filename] [menu filename] [employees filename] [tables filename] "
            "-> "
            "perform a simulation for the given number of cycles. Read cafe data from given filenames" << endl;
    cout << "-a [menu filename] [employees filename] [tables filename] -> enter admin mode (modify menu and employee databases), operate on given filenames" << endl;
}

int main(int argc, char* argv[]) {
    stringstream ss;

    if(argc == 1)
    {
        printHelp();
        return 0;
    }

    string modeArg;
    ss << argv[1];
    ss >> modeArg;
    ss.clear();

    if(modeArg == "-h") printHelp();
    else if(modeArg == "-a")
    {
        if(argc > 5)
        {
            cerr << "Too many arguments." << endl << endl;
            printHelp();
        }
        else if(argc < 5)
        {
            cerr << "Insufficient amount of arguments." << endl << endl;
            printHelp();
        }
        else
        {
            string menuFile = argv[2];
            string employeesFile = argv[3];
            string tablesFile = argv[4];

            try
            {
                CafeView cafeView = CafeView(menuFile, employeesFile, tablesFile);
                cafeView.InitAdminMode();
            }
            catch(exception &e)
            {
                cerr << "An error has occurred while entering admin mode: " << e.what() << endl;
                return 1;
            }
        }
    }
    else if(modeArg == "-s")
    {
        if(argc < 9)
        {
            cerr << "Insufficient amount of arguments." << endl << endl;
            printHelp();
        }
        else if(argc > 9)
        {
            cerr << "Too many arguments." << endl << endl;
            printHelp();
        }
        else
        {
            unsigned int numberOfCycles, customersInterval;
            double interval;
            string outputName = argv[5];
            string menuFile = argv[6];
            string employeesFile = argv[7];
            string tablesFile = argv[8];
            ss << argv[2];
            ss >> numberOfCycles;
            ss.clear();

            ss << argv[3];
            ss >> interval;
            ss.clear();

            ss << argv[4];
            ss >> customersInterval;

            try
            {
                CafeView cafeView = CafeView(menuFile, employeesFile, tablesFile);
                cafeView.InitSimulation(numberOfCycles, interval, customersInterval, outputName);
            }
            catch(exception &e)
            {
                cerr << "An error has occurred while initializing simulation: " << e.what() << endl;
                return 2;
            }
        }
    }
    else
    {
        cerr << "Invalid option." << endl << endl;
        printHelp();
    }

    return 0;
}
