#include <iostream>
#include "includes/View/cafeView.h"

void printHelp()
{
    cout << "USAGE:" << endl;
    cout << "-h -> open help" << endl;
    cout << "-s [number of cycles] [print interval] [customers interval] [output "
            "filename] "
            "-> "
            "perform a simulation for the given number of cycles" << endl;
    cout << "-a -> enter admin mode (modify menu and employee databases)" << endl;
}

int main(int argc, char* argv[]) {
    CafeView cafeView(false);
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
        if(argc > 2)
        {
            cerr << "Too many arguments." << endl << endl;
            printHelp();
        }
        else
            cafeView.InitAdminMode();
    }
    else if(modeArg == "-s")
    {
        if(argc < 6)
        {
            cerr << "Insufficient amount of arguments." << endl << endl;
            printHelp();
        }
        else if(argc > 6)
        {
            cerr << "Too many arguments." << endl << endl;
            printHelp();
        }
        else
        {
            unsigned int numberOfCycles, customersInterval;
            double interval;
            string outputName = argv[5];
            ss << argv[2];
            ss >> numberOfCycles;
            ss.clear();

            ss << argv[3];
            ss >> interval;
            ss.clear();

            ss << argv[4];
            ss >> customersInterval;

            cafeView.InitSimulation(numberOfCycles, interval, customersInterval, outputName);
        }
    }
    else
    {
        cerr << "Invalid option." << endl << endl;
        printHelp();
    }

    return 0;
}
