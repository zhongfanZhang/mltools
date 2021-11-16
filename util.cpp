#include <vector>
#include <iostream>

namespace util {
	template<typename T>
	void printVec1d(std::vector<T> vec, bool verbose = false) {
		// verbose mode outputs the index of each element and each element per line
		// non-verbose mode outputs the entire vector on one line separated by commas
		if (verbose) {
			for (int i = 0; i < vec.size(); i++) {
				std::cout << "index " << i << ": " << vec[i] << std::endl;
			}
		}
		else {
			std::cout << "{";
			for (int i = 0; i < vec.size() - 1; i++) {
				std::cout << vec[i] << ", ";
			}
			std::cout << vec.back() << "}" << std::endl;
		}
	}
}