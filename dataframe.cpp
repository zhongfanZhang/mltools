//
//  dataframe.cpp
//  mltools
//
//  Created by Zhongfan Zhang on 4/11/21.
//

#include "dataframe.h"

Dataframe::Dataframe(std::string filename, bool header = true, std::string delimiter = ","){
    // 1st pass - get number of rows
    ofstream first_pass;
    first_pass.open(filename);
    std::string line;
    int line_count = 0;
    while (getline(first_pass, line))
        line_count++;

    // if header then reduce line count by 1
    if (header)
        line_count -= 1;
    row_count = line_count;
    first_pass.close();

    // second pass - get content of file
    int line_counter = 0;
    ofstream file;
    file.open(filename);

    // read contents of the file
    std::vector<std::string> curr_line;

    // put first line into col_names
    if(header){
        // store col names and col count
        getline(file, line);
        col_names = split(line);
        col_count = col_names.size();
    }

    // set up an arrays to store data
    data = malloc(sizeof(void*) * col_count);

    // get next line and determine types
    getline(file, line);
    curr_line = split(line);
    for (int i = 0; i < curr_line.size(); i++) {
        bool is_alpha = false;
        // check every character, if any isalpha then save as string
        for (int j = 0; j < curr_line[i].length(); j++) {
            if (isalpha(curr_line[i][j])) {
                is_alpha = true;
            }
        }
        // if is_alpha is true, make string array else make double
        if (is_alpha) {
            double* temp = new double[row_count];
            col_types.push_back("double");
            temp[0] = curr_line[i];
            data[i] = &temp;
        }
        else {
            std::string* temp = new std::string[row_count];
            col_types.push_back("string");
            temp[0] = curr_line[i];
            data[i] = &temp;
        }
    }
    line_counter++;

    while(getline(file, line)){
        // split line by delimiter
        curr_line = split(line);
        //store values
        for (int k = 0; k < curr_line.size(); k++) {
            if (col_types[k] == "double")
                *((double*)data[k])[line_counter] = curr_line[k];
            else
                *((std::string*)data[k])[line_counter] = curr_line[k];

        }
        line_counter++;
    }
    
}

std::vector<std::string> split(std::string str, char delimiter = ',') {
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