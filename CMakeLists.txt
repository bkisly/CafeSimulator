cmake_minimum_required(VERSION 3.22)
project(Cafe)

set(CMAKE_CXX_STANDARD 20)

add_library(
        lib
        includes/model/MenuItem/price.h src/price.cpp
        includes/model/MenuItem/menuItem.h src/menuItem.cpp
        includes/model/MenuItem/beverage.h src/beverage.cpp
        includes/model/MenuItem/dessert.h src/dessert.cpp
        includes/model/MenuItem/dish.h src/dish.cpp
        includes/model/MenuItem/exceptions.h src/exceptions.cpp
)

add_executable(priceTests tests/priceTests.cpp)
target_link_libraries(priceTests PRIVATE lib)

add_executable(menuItemsTests tests/menuItemsTests.cpp)
target_link_libraries(menuItemsTests PRIVATE lib)

add_executable(Cafe main.cpp)
target_link_libraries(Cafe PRIVATE lib)