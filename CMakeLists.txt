cmake_minimum_required(VERSION 3.21)
project(Cafe)

set(CMAKE_CXX_STANDARD 20)

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
        includes/model/helpers/price.h src/price.cpp
        src/Table.cpp includes/model/helpers/Table.h)

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
        model
        includes/model/cafeModel.h src/cafeModel.cpp
)

# tests
add_executable(priceTests tests/priceTests.cpp)
target_link_libraries(priceTests PRIVATE helpers)

add_executable(menuItemsTests tests/menuItemsTests.cpp)
target_link_libraries(menuItemsTests PRIVATE menu helpers)

add_executable(employeeTests tests/testEmployee.cpp)
target_link_libraries(employeeTests PRIVATE employee helpers menu)

add_executable(customerTableTests tests/customerTableTests.cpp)
target_link_libraries(customerTableTests PRIVATE customer menu helpers)

add_executable(menuDatabaseTests tests/menuDatabaseTests.cpp)
target_link_libraries(menuDatabaseTests PRIVATE menu menuDatabase helpers)

add_executable(simulationRunner tests/simulationRunner.cpp)
target_link_libraries(simulationRunner PRIVATE model menu menuDatabase helpers customer)

add_executable(dbEmployeesTests tests/DbEmployeeTests.cpp)
target_link_libraries(dbEmployeesTests PRIVATE employee helpers menu)

# runners
add_executable(Cafe main.cpp)
target_link_libraries(Cafe PRIVATE model menu menuDatabase employee helpers customer)