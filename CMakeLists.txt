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
        includes/model/MenuItem/menuItem.h src/model/MenuItem/menuItem.cpp
        includes/model/MenuItem/beverage.h src/model/MenuItem/beverage.cpp
        includes/model/MenuItem/dessert.h src/model/MenuItem/dessert.cpp
        includes/model/MenuItem/dish.h src/model/MenuItem/dish.cpp
        includes/model/helpers/exceptions.h src/model/MenuItem/employeeExceptions.cpp
)

add_library(
        customer
        includes/model/Customer/table.h src/model/Customer/table.cpp
        includes/model/Customer/customer.h src/model/Customer/customer.cpp
        includes/model/Customer/customersGroup.h src/model/Customer/customersGroup.cpp
)

add_library(
        helpers
        includes/model/helpers/price.h src/model/Helpers/price.cpp
)

add_library(
        employee
        includes/model/Employee/Cook.h src/model/Employee/Cook.cpp
        includes/model/Employee/Waiter.h src/model/Employee/Waiter.cpp
        includes/model/Employee/Employee.h src/model/Employee/Employee.cpp
        includes/model/Employee/employeeExceptions.h
)

add_library(
        database
        includes/model/Databases/iDatabase.h
        includes/model/Databases/menuDatabase.h src/model/Databases/menuDatabase.cpp
        includes/model/Databases/templateDatabase.h src/model/Databases/CustomTableDb.cpp includes/model/Databases/CustomTableDb.h src/model/Databases/CustomEmployeesDb.cpp includes/model/Databases/CustomEmployeesDb.h src/controller/DataService.cpp includes/controller/DataService.h src/controller/OnlineService.cpp includes/controller/OnlineService.h)

add_library(
        viewModel
        includes/model/cafeModel.h src/model/cafeModel.cpp
        includes/view/cafeView.h src/view/cafeView.cpp
        includes/controller/databaseSimulationService.h src/controller/databaseSimulationService.cpp
)

# tests
add_executable(priceTests tests/unitTests/priceTests.cpp)
target_link_libraries(priceTests PRIVATE helpers)

add_executable(menuItemsTests tests/unitTests/menuItemsTests.cpp)
target_link_libraries(menuItemsTests PRIVATE menu helpers)

add_executable(employeeTests tests/unitTests/employeeTests.cpp)
target_link_libraries(employeeTests PRIVATE employee helpers menu customer)

add_executable(employeeSimulationTests tests/integrationTests/employeeSimulationTests.cpp)
target_link_libraries(employeeSimulationTests PRIVATE database employee helpers menu customer)

add_executable(customerTableTests tests/unitTests/customerTableTests.cpp)
target_link_libraries(customerTableTests PRIVATE customer menu helpers employee)

add_executable(menuDatabaseTests tests/unitTests/menuDatabaseTests.cpp)
target_link_libraries(menuDatabaseTests PRIVATE menu database helpers)

add_executable(simulationRunner tests/integrationTests/simulationRunner.cpp)
target_link_libraries(simulationRunner PRIVATE viewModel menu database employee helpers customer)

add_executable(dbEmployeesTests tests/unitTests/DbEmployeeTests.cpp)
target_link_libraries(dbEmployeesTests PRIVATE employee helpers menu customer database)

add_executable(databaseSchemeTests tests/unitTests/databaseScheme.cpp)
target_link_libraries(databaseSchemeTests PRIVATE customer database menu helpers employee)

add_executable(httpsTests tests/integrationTests/httpTests.cpp)
target_link_libraries(databaseSchemeTests PRIVATE customer database menu helpers employee)

# TODO: run all tests executable

# runners
add_executable(Cafe main.cpp src/model/Databases/CustomEmployeesDb.cpp includes/model/Databases/CustomEmployeesDb.h)
target_link_libraries(Cafe PRIVATE viewModel customer employee menu database helpers)
