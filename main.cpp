#include <iostream>
#include <sstream>
#include "includes/View/cafeView.h"

void printHelp()
{
    cout << "USAGE:" << endl;
    cout << "-h -> open help" << endl;
    cout << "-s [number of cycles] -> perform a simulation for the given number of cycles" << endl;
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
    else if(argc > 3)
    {
        cerr << "Too many arguments." << endl << endl;
        printHelp();
        return 1;
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
        {
            cout << "Entering admin mode";
            // TODO: enter admin mode here
        }
    }
    else if(modeArg == "-s")
    {
        if(argc == 2)
        {
            cerr << "Insufficient amount of arguments." << endl << endl;
            printHelp();
        }
        else
        {
            unsigned int numberOfCycles;
            ss << argv[2];
            ss >> numberOfCycles;

            cafeView.InitSimulation(numberOfCycles, 1, 20);
        }
    }
    else
    {
        cerr << "Invalid option." << endl << endl;
        printHelp();
    }

    return 0;
}
