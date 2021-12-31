//
// Created by Admin on 30/12/2021.
//

#include "DataContainer.h"

DataContainer::DataContainer(std::string filename, char delimiter, bool skip_header) {

}

void DataContainer::display(int row_count) {

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

