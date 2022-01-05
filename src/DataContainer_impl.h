//
// Created by Admin on 4/01/2022.
//

#ifndef MLTOOLS_DATACONTAINER_IMPL_H
#define MLTOOLS_DATACONTAINER_IMPL_H

#include <stdexcept>
#include <algorithm>
#include "DataContainer.h"
#include "ml_util.h"

template <typename T>
std::vector<T> DataContainer::getCol(const int &index, bool del) {
    // if out of range
    if(index >= data[0].size())
        throw std::out_of_range("Requested column is out of range");
    std::vector<T> output;
    // any cast data into double
    for(auto &row : data){
        try{
            output.emplace_back(std::any_cast<T>(row[index]));
        }
            // if bad any_cast, break to skip current row
        catch(std::bad_any_cast &e){
            break;
        }
    }
    // delete col if specified
    if(del)
        dropCol(index);
    // return column stored in output
    return output;
}

template<typename T>
std::map<T, int> DataContainer::unique(const int &col_index) {
    std::map<T, int> output;
    // get the column
    std::vector<T> col = getCol<T>(col_index);
    // tally unique counts
    while(!col.empty()){
        // get first value
        T val = col[0];
        // make tally and insert with key
        long long tally = std::count(col.begin(), col.end(), val);
        output.insert(std::pair<T, int>(val, tally));
        // erase all occurrences of tallied value
        col.erase(std::remove(col.begin(),col.end(),val), col.end());
    }
    return output;
}

template<typename T>
void DataContainer::addCol(const std::string &col_name, const std::vector<T> &input_data) {
    if(input_data.size() != data.size()) throw std::range_error("The length of the input data and the existing database does not match.");
    col_names.template emplace_back(col_name);
    for(int i = 0; i < data.size(); i++){
        data[i].template emplace_back(input_data[i]);
    }
}

#endif //MLTOOLS_DATACONTAINER_IMPL_H
