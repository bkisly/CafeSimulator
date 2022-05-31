//
// Created by bkisl on 26.05.2022.
//

#ifndef CAFE_CAFEVIEW_H
#define CAFE_CAFEVIEW_H

#include <iostream>
#include <thread>
#include <chrono>
#include "../model/cafeModel.h"

class CafeView {
private:
    CafeModel model;

public:
    CafeView(bool readFromService = true);
    void InitSimulation(unsigned int numberOfCycles, double intervalSeconds, unsigned int customersInterval);
};


#endif //CAFE_CAFEVIEW_H
