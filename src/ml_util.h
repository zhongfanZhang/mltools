#ifndef ML_UTIL_H
#define ML_UTIL_H

#include <vector>
#include <iostream>
#include <iomanip>

namespace ml_util {
	template<typename T>
	void printVec1d(std::vector<T> vec, bool verbose = false, int col_width = 10);

    template<typename T>
    void printVec2d(std::vector< std::vector<T>> vec, int col_width = 10);

	std::vector<std::string> split(std::string str, const char& delimiter = ',');
}

#endif //ML_UTIL_H