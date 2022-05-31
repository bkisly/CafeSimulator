//
// Created by bkisl on 26.05.2022.
//

#include "../includes/View/cafeView.h"

CafeView::CafeView(bool readFromService) {
    // TODO: try-catch should be added here while reading from service - errors may occur
    model = CafeModel(readFromService);
}

void CafeView::InitSimulation(unsigned int numberOfCycles, double intervalSeconds, unsigned int customersInterval) {
    try
    {
        model.Simulate(numberOfCycles, customersInterval);

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


