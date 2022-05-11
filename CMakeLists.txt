cmake_minimum_required(VERSION 3.22)
project(Cafe)

set(CMAKE_CXX_STANDARD 20)

add_library(lib includes/price.h src/price.cpp)

add_executable(priceTests tests/priceTests.cpp)
target_link_libraries(priceTests PRIVATE lib)

add_executable(Cafe main.cpp)
target_link_libraries(Cafe PRIVATE lib)