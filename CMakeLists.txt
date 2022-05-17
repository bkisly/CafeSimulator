cmake_minimum_required(VERSION 3.22)
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

# tests
add_executable(priceTests tests/priceTests.cpp)
target_link_libraries(priceTests PRIVATE helpers)

add_executable(menuItemsTests tests/menuItemsTests.cpp)
target_link_libraries(menuItemsTests PRIVATE menu helpers)

add_executable(employeeTests tests/testEmployee.cpp)
target_link_libraries(employeeTests PRIVATE employee helpers)

add_executable(customerTableTests tests/customerTableTests.cpp)
target_link_libraries(customerTableTests PRIVATE customer menu helpers)

# runners
add_executable(Cafe main.cpp)
target_link_libraries(Cafe PRIVATE menu employee helpers)