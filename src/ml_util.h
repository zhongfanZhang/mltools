#ifndef ML_UTIL_H
#define ML_UTIL_H

#include <vector>
#include <iostream>
#include <iomanip>
#include "DataContainer.h"

namespace ml_util {

    /*
     * Printing and Debug functions
     */

	template<typename T>
	void printVec1d(std::vector<T> vec, bool verbose = false, int col_width = 10);

    template<typename T>
    void printVec2d(std::vector< std::vector<T>> vec, int col_width = 10);

    /*
     * String processing functions
     */

	std::vector<std::string> split(std::string str, const char& delimiter = ',');

    /*
     * data wrangling functions
     */

    /**
     * Performs one hot encoding on the column of a DataContainer specified by
     * col_index, creating a number of new columns based on the unique value
     * count and removing the old column
     *
     * @param col_index: the column to be encoded
     * @param data_container: the DataContainer to be encoded
     */
    void oneHotEncoding(const int &col_index, DataContainer &data_container);
}

#endif //ML_UTIL_H