//
// Created by Admin on 30/12/2021.
//

#include "DataContainer.h"
#include <fstream>
#include <iostream>
#include "util.h"
#include <string>
#include <iomanip>

#define GET_VAR_NAME(var) (#var)

DataContainer::DataContainer(const std::string& filename, const char& delimiter) {
    // open file and mitigate file doesn't exist error
    std::ifstream file;
    file.open(filename);
    if(!file.is_open())
        throw "Unable to open file";
    // read the first line as column names
    std::string curr_line;
    std::getline(file, curr_line);
    col_names = util::split(curr_line, delimiter);
    // read the rest of the lines into data
    while(!file.eof()){
        std::getline(file, curr_line);
        std::vector<std::string> temp_line = util::split(curr_line, delimiter);
        std::vector<std::any> temp_data;
        // convert any convertible values into doubles else keep as string
        for(auto &element : temp_line){
            try{
                double temp_element = std::stod(element);
                temp_data.emplace_back(temp_element);
            }catch(std::invalid_argument e){
                temp_data.emplace_back(std::string(element));
            }
        }
        data.emplace_back(temp_data);
    }
    // clean up
    file.close();
}

void DataContainer::display(int row_count, int display_width) {
    // info dump
    std::cout << "Displaying the first " << row_count << " rows of the DataContainer:\n";
    // print column headers first
    for(auto &name : col_names){
        std::cout << std::setw(display_width) << name << " ";
    }
    std::cout << "\n";
    // every row
    for(int i = 0; i < row_count; i++){
        // every element
        for(auto &element : data[i]){
            // check typeid for any_cast
            if(element.type() == typeid(std::string)){
                std::cout << std::setw(display_width) << std::any_cast<std::string>(element) << " ";
            }else{
                std::cout << std::setw(display_width) << std::any_cast<double>(element) << " ";
            }
        }
        printf("\n");
    }
}

int DataContainer::dropRow(int start_row, int row_count) {
    return 0;
}

int DataContainer::dropCol(int start_col, int col_count) {
    return 0;
}

int DataContainer::size(bool rows) {
    return 0;
}

std::vector<std::vector<double>> DataContainer::getRows(int start_index, int row_count) {
    return std::vector<std::vector<double>>();
}

std::vector<double> DataContainer::getCol(int index) {
    return std::vector<double>();
}

std::map<std::string, int> DataContainer::unique(int col_index) {
    return std::map<std::string, int>();
}

