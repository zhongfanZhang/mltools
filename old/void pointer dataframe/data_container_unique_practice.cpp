//
// Created by Admin on 4/01/2022.
//

#include <map>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iostream>

int main() {
    std::map<int, int> output;
    std::vector<int> test{1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 6, 2, 3, 4, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1,
                          2, 3, 1, 24, 2, 4, 6, 8, 98, 2, 1, 2, 3, 4, 5, 1, 2, 3, 54, 1, 2, 3, 45, 5, 3, 1, 23, 4, 5, 1,
                          23, 4, 12, 31, 3, 23, 2,};

    auto start_first = std::chrono::high_resolution_clock::now();
    int counter = 0;
    for (auto &element: test) {
        counter++;
// get key and tally
        long long tally = std::count(test.begin(), test.end(), element);
// add key and tally to output
        output.insert(std::pair<int, int>(element, tally));
// remove all occurrences of tallied element - optimisations possible
    }
    auto end_first = std::chrono::high_resolution_clock::now();

    auto start_second = std::chrono::high_resolution_clock::now();
    std::map<int, int> output1;
    int counter_1 = 0;
    while (!test.empty()) {
        counter_1++;
        int val = test[0];
        long long tally = std::count(test.begin(), test.end(), val);
        output1.insert(std::pair<int, int>(val, tally));
        test.erase(std::remove(test.begin(), test.end(), val), test.end());
    }
    auto end_second = std::chrono::high_resolution_clock::now();

    for (auto it = output.begin(); it != output.end(); ++it) {
        std::cout << it->first << ":" << it->second << "\n";
    }

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_first - start_first);
    double dur = double(duration.count()) / 1000000;
    std::cout << "first version time elapsed: " << dur << "s\n";
    std::cout << "first version took: " << counter << " cycles\n";

    std::cout << "second version:\n";
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end_second - start_second);
    double dur1 = double(duration1.count()) / 1000000;
    std::cout << "second version time elapsed: " << dur1 << "s\n";
    std::cout << "second version took: " << counter_1 << " cycles\n";

    for (auto &it: output1) {
        std::cout << it.first << ":" << it.second << "\n";
    }

}
