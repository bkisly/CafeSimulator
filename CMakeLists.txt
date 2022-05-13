cmake_minimum_required(VERSION 3.22)
project(Cafe)

set(CMAKE_CXX_STANDARD 20)

# libs
add_library(
        menu
        includes/model/helpers/price.h src/price.cpp
        includes/model/MenuItem/menuItem.h src/menuItem.cpp
        includes/model/MenuItem/beverage.h src/beverage.cpp
        includes/model/MenuItem/dessert.h src/dessert.cpp
        includes/model/MenuItem/dish.h src/dish.cpp
        includes/model/MenuItem/exceptions.h src/exceptions.cpp
)

add_library(
        employee
        includes/model/Employee/Cook.h src/Employee/Cook.cpp
        includes/model/Employee/Waiter.h src/Employee/Waiter.cpp
        includes/model/Employee/Employee.h src/Employee/Employee.cpp
        includes/model/Employee/DbWorkers.h src/Employee/DbWorkers.cpp
        includes/model/Employee/Price.h src/Employee/Price.cpp
        includes/model/Employee/Exceptions.h
)

# tests
add_executable(priceTests tests/priceTests.cpp)
target_link_libraries(priceTests PRIVATE menu)

add_executable(menuItemsTests tests/menuItemsTests.cpp)
target_link_libraries(menuItemsTests PRIVATE menu)

add_executable(employeeTests tests/testEmployee.cpp)
target_link_libraries(employeeTests PRIVATE employee)

# runners
add_executable(Cafe main.cpp)
target_link_libraries(Cafe PRIVATE menu employee)