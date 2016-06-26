cmake_minimum_required(VERSION 3.3)
project(power)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(SOURCE_FILES main.cpp)
add_executable(power ${SOURCE_FILES})