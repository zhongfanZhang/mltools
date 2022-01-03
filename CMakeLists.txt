cmake_minimum_required(VERSION 3.21)
project(mltools)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(mltools
        src/DataContainer.cpp
        src/DataContainer.h
        src/main.cpp
        src/ml_util.h
        src/ml_util.cpp src/DataContainer_impl.h src/Tree/DecisionTreeClassifier.cpp src/Tree/DecisionTreeClassifier.h src/Tree/DecisionTree.cpp src/Tree/DecisionTree.h src/Tree/DecisionTreeNode.h)
