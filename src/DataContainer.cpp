//
// Created by Admin on 30/12/2021.
//

#include "DataContainer.h"
#include <fstream>
#include <iostream>
#include "ml_util.h"
#include <string>
#include <iomanip>


DataContainer::DataContainer(const std::string& filename, std::string  cont_name, const char& delimiter)
 : container_name(std::move(cont_name)) {
    // open file and mitigate file doesn't exist error
    std::ifstream file;
    file.open(filename);
    if(!file.is_open())
        throw std::runtime_error("could not open file");
    // read the first line as column names
    std::string curr_line;
    std::getline(file, curr_line);
    col_names = ml_util::split(curr_line, delimiter);
    // read the rest of the lines into data
    while(!file.eof()){
        std::getline(file, curr_line);
        std::vector<std::string> temp_line = ml_util::split(curr_line, delimiter);
        std::vector<std::any> temp_data;
        // convert any convertible values into doubles else keep as string
        for(auto &element : temp_line){
            try{
                double temp_element = std::stod(element);
                temp_data.emplace_back(temp_element);
            }catch(std::invalid_argument &e){
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
    std::cout << "Displaying the first " << row_count << " rows of " << container_name << ":\n";
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

int DataContainer::dropRow(const int &start_row, const int &row_count) {
    // if start out of range
    if(start_row >= data.size()) return -1;
    // if end of out range
    if((start_row + row_count) >= data.size()) return -2;
    // if within range, erase rows
    data.erase(data.begin() + start_row, data.begin() + start_row + row_count);
    // if no rows remain, return 0 else return 1
    if(data.empty()) return 0;
    else return 1;
}

int DataContainer::dropCol(const int &start_col) {
    // remove the column header
    col_names.erase(col_names.begin() + start_col);
    // remove element col_num from every row
    for(auto &row : data){
        // if column index out of range return
        if(start_col >= row.size()) return -1;
        else row.erase(row.begin() + start_col);
    }
    // if empty return 0, else return 1
    if(data.empty()) return 0;
    else return 1;
}

unsigned int DataContainer::size(bool rows) {
    if(rows)
        return data.size();
    else
        return data[0].size();
}

std::vector<std::vector<double>> DataContainer::getRows(const int &start_index, const int &row_count) {
    // if out of range
    if(start_index + row_count >= data.size())
        throw std::out_of_range("Requested row is out of range");
    std::vector< std::vector<double>> output;
    // any_cast data elements into double
    for(auto i = start_index; i < row_count; i++){
        std::vector<double> temp;
        for(auto &element : data[i]){
            try{
                temp.emplace_back(std::any_cast<double>(element));
            }
            // if bad any-cast, break to skip current row
            catch(std::bad_any_cast &e){
                break;
            }
        }
        output.emplace_back(temp);
    }
    return output;
}

std::vector<double> DataContainer::getCol(const int &index) {
    // if out of range
    if(index >= data[0].size())
        throw std::out_of_range("Requested column is out of range");
    std::vector<double> output;
    // any cast data into double
    for(auto &row : data){
        try{
            output.emplace_back(std::any_cast<double>(row[index]));
        }
        // if bad any_cast, break to skip current row
        catch(std::bad_any_cast &e){
            break;
        }
    }
    return output;
}

std::map<std::string, int> DataContainer::unique(int col_index) {
    return std::map<std::string, int>();
}

