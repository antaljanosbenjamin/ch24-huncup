cmake_minimum_required(VERSION 3.3)
project(hexa)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(SOURCE_FILES main.cpp)
add_executable(hexa ${SOURCE_FILES})