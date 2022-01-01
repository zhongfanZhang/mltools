#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <iostream>
#include <iomanip>

namespace util {
	template<typename T>
	void printVec1d(std::vector<T> vec, bool verbose = false, int col_width = 10) {
		// verbose mode outputs the index of each element and each element per line
		// non-verbose mode outputs the entire vector on one line separated by commas
		if (verbose) {
			for (int i = 0; i < vec.size(); i++) {
				std::cout << "index " << i << ": " << vec[i] << std::endl;
			}
		}
		else {
			for (int i = 0; i < vec.size() - 1; i++) {
				std::cout << std::setw(col_width) << vec[i] << ", ";
			}
			std::cout << vec.back() << std::endl;
		}
	}

	std::vector<std::string> split(std::string str, const char& delimiter = ',') {
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
}

#endif //UTIL_H