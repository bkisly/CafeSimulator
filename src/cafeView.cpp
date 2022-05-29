//
// Created by bkisl on 26.05.2022.
//

#include "../includes/View/cafeView.h"

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


