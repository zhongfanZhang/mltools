#ifndef ML_UTIL_H
#define ML_UTIL_H

#include <vector>
#include <iostream>
#include <iomanip>

namespace ml_util {

    /*
     * Printing and Debug functions
     */

	template<typename T>
	void print_vec_1d(std::vector<T> vec, bool verbose = false, int col_width = 10);

    template<typename T>
    void print_vec_2d(std::vector< std::vector<T>> vec, int col_width = 10);

    /*
     * String processing functions
     */

	std::vector<std::string> split(std::string str, const char& delimiter = ',');

    /*
     * data wrangling functions
     */

    std::vector<std::vector<double>> filter(std::string condition, std::vector< std::vector<double>> data);

}

#endif //ML_UTIL_H