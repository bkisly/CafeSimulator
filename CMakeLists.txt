cmake_minimum_required(VERSION 3.21)
project(Cafe)

set(CMAKE_CXX_STANDARD 20)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()

# todo: add -Wall options - display all warnings

# libs
add_library(
        menu
        includes/model/MenuItem/menuItem.h src/MenuItem/menuItem.cpp
        includes/model/MenuItem/beverage.h src/MenuItem/beverage.cpp
        includes/model/MenuItem/dessert.h src/MenuItem/dessert.cpp
        includes/model/MenuItem/dish.h src/MenuItem/dish.cpp
        includes/model/MenuItem/exceptions.h src/MenuItem/exceptions.cpp
)

add_library(
        customer
        includes/model/Customer/table.h src/Customer/table.cpp
        includes/model/Customer/customer.h src/Customer/customer.cpp
        includes/model/Customer/customersGroup.h src/Customer/customersGroup.cpp
)

add_library(
        helpers
        includes/model/helpers/price.h src/Helpers/price.cpp
)

add_library(
        employee
        includes/model/Employee/Cook.h src/Employee/Cook.cpp
        includes/model/Employee/Waiter.h src/Employee/Waiter.cpp
        includes/model/Employee/Employee.h src/Employee/Employee.cpp
        includes/model/Employee/DbWorkers.h src/Employee/DbWorkers.cpp
        includes/model/Employee/Exceptions.h
)

add_library(
        menuDatabase
        includes/model/Databases/iDatabase.h
        includes/model/Databases/menuDatabase.h src/Databases/menuDatabase.cpp
)

add_library(
        viewModel
        includes/model/cafeModel.h src/cafeModel.cpp
        includes/view/cafeView.h src/cafeView.cpp
)

# tests
add_executable(priceTests tests/unitTests/priceTests.cpp)
target_link_libraries(priceTests PRIVATE helpers)

add_executable(menuItemsTests tests/unitTests/menuItemsTests.cpp)
target_link_libraries(menuItemsTests PRIVATE menu helpers)

add_executable(employeeTests tests/unitTests/employeeTests.cpp)
target_link_libraries(employeeTests PRIVATE employee helpers menu customer)

add_executable(employeeSimulationTests tests/integrationTests/employeeSimulationTests.cpp)
target_link_libraries(employeeSimulationTests PRIVATE employee helpers menu customer)

add_executable(customerTableTests tests/unitTests/customerTableTests.cpp)
target_link_libraries(customerTableTests PRIVATE customer menu helpers employee)

add_executable(menuDatabaseTests tests/unitTests/menuDatabaseTests.cpp)
target_link_libraries(menuDatabaseTests PRIVATE menu menuDatabase helpers)

add_executable(simulationRunner tests/integrationTests/simulationRunner.cpp)
target_link_libraries(simulationRunner PRIVATE viewModel menu menuDatabase employee helpers customer)

add_executable(dbEmployeesTests tests/unitTests/DbEmployeeTests.cpp)
target_link_libraries(dbEmployeesTests PRIVATE employee helpers menu customer)

# TODO: run all tests executable

# runners
add_executable(Cafe main.cpp)
target_link_libraries(Cafe PRIVATE viewModel customer employee menu menuDatabase helpers)