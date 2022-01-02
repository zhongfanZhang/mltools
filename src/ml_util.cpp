//
// Created by Admin on 2/01/2022.
//

#include "ml_util.h"

template<typename T>
void ml_util::printVec1d(std::vector<T> vec, bool verbose, int col_width) {
    // verbose mode outputs the index of each element and each element per line
    // non-verbose mode outputs the entire vector on one line separated by commas
    if (verbose) {
        for (int i = 0; i < vec.size(); i++) {
            std::cout << "index " << i << ": " << vec[i] << "\n";
        }
    }
    else {
        for (int i = 0; i < vec.size() - 1; i++) {
            std::cout << std::setw(col_width) << vec[i] << ", ";
        }
        std::cout << vec.back() << "\n";
    }
}

template<typename T>
void ml_util::printVec2d(std::vector< std::vector<T>> vec, int col_width){
    for(auto &row : vec){
        for(auto &element : row){
            std::cout << std::setw(col_width) << element << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

std::vector<std::string> ml_util::split(std::string str, const char& delimiter) {
    std::vector<std::string> output;
    // make substrs based on delimiter
    int start = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == delimiter) {
            output.push_back(str.substr(start, i - start));
            start = i + 1;
        }
        else if (i == str.length() - 1) {
            output.push_back(str.substr(start, i - start + 1));
        }
    }
    return output;
}

void ml_util::oneHotEncoding(const int &col_index, DataContainer &data_container) {}