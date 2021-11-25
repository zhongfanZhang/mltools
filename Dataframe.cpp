#include <iostream>
#include <fstream>
#include <vector>
#include "util.cpp"

/*
	The following are not supported at this stage:
		- Missing data in rows
		- delimiters other than ','
*/

int main() {

	// dev
	std::string filename; // provided as function arg
	bool header = true;   // provided as function arg
	std::cin >> filename; // provided as function arg
	void** data;			  // provided as class var
	int col_count = 0;		  // provided as class var
	int row_count = 0;		  // provided as class var
	std::vector<std::string> col_names; // provided as class var
	std::vector<std::string> col_types; // provided as class var
	// end dev

	// first pass - get metadata
	std::ifstream first_pass;
	first_pass.open(filename);
	std::string line;
	// if header exists, store col names
	if (header) {
		getline(first_pass, line);
		col_names = util::split(line);
	}
	// store data types
	getline(first_pass, line);
	std::vector<std::string> curr_line = util::split(line);
	for (int i = 0; i < curr_line.size(); i++) {
		bool is_alpha = false;
		for (int j = 0; j < curr_line[i].length(); j++) {
			if (isalpha(curr_line[i][j])) {
				is_alpha = true;
			}
		}
		col_types.push_back((is_alpha ? "string" : "num"));
	}
	row_count++;
	// get row count
	while (getline(first_pass, line)) {
		row_count++;
	}
	// close file
	first_pass.close();

	// second pass - store data
	data = (void**)malloc(sizeof(void*) * row_count);
	
}