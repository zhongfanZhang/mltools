cmake_minimum_required(VERSION 3.21)
project(mltools)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(mltools
        src/DataContainer.cpp
        src/DataContainer.h
        src/main.cpp
        src/util.h)
