//
// Created by Admin on 30/12/2021.
//

#include "DataContainer.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <utility>


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
        // if line is empty, goto next line
        if(curr_line.empty()) continue;
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

DataContainer::DataContainer(std::vector< std::vector<std::any>>  in_data,
                             std::vector< std::string>  in_col_names,
                             std::string in_container_name)
                             : container_name(std::move(in_container_name)),
                             data(std::move(in_data)),
                             col_names(std::move(in_col_names)) {}


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

DataContainer DataContainer::train_test_split(const float &train, const float &test) {

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

void DataContainer::oneHotEncoding(const int &col_index, bool remove_old) {
    // get key-value pair of unique values
    std::map<std::string, int> value_counts = unique<std::string>(col_index);
    // get new col names
    std::vector<std::string> new_col_names;
    for(auto &item : value_counts){
        new_col_names.emplace_back(item.first);
    }
    // create new encoded vectors
    std::vector< std::vector<double>> encoded_cols;
    for(auto &col_name : new_col_names) {
        std::vector<double> temp_encoded_col;
        for (auto &row: data) {
            auto value = std::any_cast<std::string>(row[col_index]);
            if (value == col_name)
                temp_encoded_col.emplace_back(1);
            else
                temp_encoded_col.emplace_back(0);
        }
        encoded_cols.emplace_back(temp_encoded_col);
    }
    // add new_col_names to col_names
    for(int i = 0; i < encoded_cols.size(); i++){
        addCol(new_col_names[i], encoded_cols[i]);
    }
    // remove old col if remove_old is true
    if(remove_old){
        dropCol(col_index);
    }
}

std::vector<std::vector<double>> DataContainer::operator[](const std::string &condition) {
    std::vector< std::vector<double>> output;
    // parse condition
    std::string col_name;
    std::string op;
    double cond;
    auto cond_line = ml_util::split(condition, ' ');
    col_name = cond_line[0];
    op = cond_line[1];
    cond = std::stod(cond_line[2]);
    // get index of the column
    int col_index = getColIndex(col_name);
    // filter DataContainer
    for(auto &row : data){
        // TODO: apply conditions

    }
    return output;
}

int DataContainer::getColIndex(const std::string &col_name) {
    auto ip = find(col_names.begin(), col_names.end(), col_name);
    // if the name was found
    if(ip != col_names.end())
        return ip - col_names.begin();
}

/**
 * less than
 * less than or eq
 * greater than
 * greater than or eq
 * equals
 * not equal to
 */