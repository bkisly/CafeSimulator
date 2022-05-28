//
// Created by bkisl on 26.05.2022.
//

#define CATCH_CONFIG_MAIN

#include <iostream>
#include "../catch.hpp"
#include "../../includes/model/cafeModel.h"

TEST_CASE("Runner")
{
    CafeModel model(false);
    model.Simulate(5);
    std::cout << model.GetSimulationLog() << std::endl;
}