//
// Created by Admin on 4/01/2022.
//

#ifndef MLTOOLS_DATACONTAINER_IMPL_H
#define MLTOOLS_DATACONTAINER_IMPL_H

#include <stdexcept>
#include <algorithm>
#include "DataContainer.h"

template <typename T>
std::vector<T> DataContainer::getCol(const int &index) {
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
    return output;
}

/*
 * TODO: optimise unique by deleting all occurrences of counted elements
 */
template<typename T>
std::map<T, int> DataContainer::unique(const int &col_index) {
    std::map<T, int> output;
    // get the column
    std::vector<T> col = getCol<T>(col_index);
    // tally unique counts
    for(auto &element : col){
        // get key and tally
        long long tally = std::count(col.begin(), col.end(), element);
        // add key and tally to output
        output.insert(std::pair<T, double>(element, tally));
        // remove all occurrences of tallied element - optimisations possible
    }
    return output;
}

template<typename T>
void DataContainer::addCol(const std::string &col_name, const std::vector<T> &input_data) {

}
#endif //MLTOOLS_DATACONTAINER_IMPL_H
