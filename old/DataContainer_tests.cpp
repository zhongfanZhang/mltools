//
// Created by Admin on 5/01/2022.
//
#include <chrono>
#include <iostream>
#include <vector>
#include <map>
#include "src/DataContainer.h"



int main() {
    auto start = std::chrono::high_resolution_clock::now();
// testing datacontainer stuff
    DataContainer fish("test_double.csv", "container_1");
// dropRow test
    printf("before droprow, size = %d:\n", fish.size());
    fish.display(4);
    fish.dropRow(0);
    printf("after droprow, size = %d:\n", fish.size());
    fish.display(3);
// dropCol test
    printf("\ndropping 1st col, col_size = %d:\n", fish.size(false));
    fish.dropCol();
    fish.display(3);
    printf("\ncol_size after dropping = %d", fish.size(false));
// getRows test
    std::vector <std::vector<double>> vec2d = fish.getRows(0, 1);
    std::cout << "\nrows 0 to 3:\n";
    for (auto &row: vec2d) {
        for (auto &element: row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
// getCol test
    std::vector<double> test_col = fish.getCol<double>(0);
//    for(auto &element : test_col){
//        std::cout << element << "\n";
//    }
//    std::cout << "\n";
// unique test
    std::map<double, int> uniques = fish.unique<double>(1);
    for (auto it = uniques.begin(); it != uniques.end(); ++it) {
        std::cout << it->first << ":" << it->second << "\n";
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double dur = double(duration.count()) / 1000000;
    std::cout << "time elapsed: " << dur << "s\n";
}