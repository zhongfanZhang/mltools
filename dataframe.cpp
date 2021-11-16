//
//  dataframe.cpp
//  mltools
//
//  Created by Zhongfan Zhang on 4/11/21.
//

#include "dataframe.h"

Dataframe::Dataframe(std::string filename, bool header = true, std::string delimiter = ","){
    // read contents of the file
    ofstream file;
    std::string line;
    file.open(filename);
    // put first line into col_names
    if(header){
        getline(file, line);
        // split line by delimiter
        
    }
    while(getline(file, line)){
        // split line by delimiter
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