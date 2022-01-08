//
// Created by Admin on 30/12/2021.
//

#include "DataContainer.h"


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

int DataContainer::drop_row(const unsigned int &start_row, const unsigned int &row_count) {
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

int DataContainer::drop_col(const unsigned int &start_col) {
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

void DataContainer::train_test_split(const float &test_ratio) {
    // initialise random seed
    srand(time(NULL));
    // if class label column has not been set throw exception
    if(target.empty()) throw std::out_of_range("This function requires a class label column to be set.");
    // multiply test_proportion by 100 and roll random numbers every row to decide set
    int test_proportion = test_ratio * 100;
    for(int i = 0; i < data.size(); i++){
        int roll = rand()% 100 + 0;
        std::vector<double> temp_row;
        // cast row from any to double
        temp_row.reserve(data[i].size());
        for(auto &element : data[i]){
            temp_row.emplace_back(std::any_cast<double>(element));
        }
        // insert row according to the roll
        if(roll <= test_proportion) {
            test.push_back(temp_row);
            test_tar.push_back(target[i]);
        }
        else {
            train.push_back(temp_row);
            train_tar.push_back(target[i]);
        }
    }
}

unsigned int DataContainer::size(bool rows) {
    if(rows)
        return data.size();
    else
        return data[0].size();
}

[[maybe_unused]] std::vector<std::vector<double>> DataContainer::get_rows(const unsigned int &start_index, const unsigned int &row_count) {
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

void DataContainer::one_hot_encoding(const int &col_index, bool remove_old) {
    // get key-value pair of unique values
    std::map<std::string, int> value_counts = unique<std::string>(col_index);
    // get new col names and resize vector
    std::vector<std::string> new_col_names;
    new_col_names.reserve(value_counts.size());
    // add keys to new_col_names vector
    for(auto &item : value_counts){
        new_col_names.push_back(item.first);
    }
    // create new encoded vectors
    std::vector< std::vector<double>> encoded_cols;
    for(auto &col_name : new_col_names) {
        std::vector<double> temp_encoded_col;
        temp_encoded_col.reserve(data.size());
        for (auto &row: data) {
            auto value = std::any_cast<std::string>(row[col_index]);
            if (value == col_name)
                temp_encoded_col.push_back(1);
            else
                temp_encoded_col.push_back(0);
        }
        encoded_cols.push_back(temp_encoded_col);
    }
    // add new_col_names to col_names
    for(int i = 0; i < encoded_cols.size(); i++){
        add_col(new_col_names[i], encoded_cols[i]);
    }
    // remove old col if remove_old is true
    if(remove_old){
        drop_col(col_index);
    }
}

int DataContainer::get_col_index(const std::string &col_name) {
    auto ip = find(col_names.begin(), col_names.end(), col_name);
    // if the name was found
    if(ip != col_names.end())
        return ip - col_names.begin();
    else return -1;
}

std::vector<std::vector<double>> DataContainer::get_train() {
    return train;
}

[[maybe_unused]] std::vector<std::vector<double>> DataContainer::get_test() {
    return test;
}

std::vector<double> DataContainer::operator[](const std::string &col_name) {
    int idx = get_col_index(col_name);
    return get_col<double>(idx, false);
}

[[maybe_unused]] std::vector<std::vector<double>>
DataContainer::filter_if_lt(const int &col_index, const double &val, bool train_set, bool equals) {
    // target pointer, if train_set true, then points to self.train, else points to self.test
    std::vector< std::vector<double>>* tar;
    if(train_set) tar = &train;
    else tar = &test;
    // copy all rows that fit the criteria into output
    std::vector< std::vector<double>> output;
    if(equals)
        std::copy_if (tar -> begin(), tar -> end(),std::back_inserter(output),
                      [&col_index, &val](std::vector<double> row){return row[col_index]<=val;} );
    else
        std::copy_if (tar -> begin(), tar -> end(),std::back_inserter(output),
                      [&col_index, &val](std::vector<double> row){return row[col_index]<val;} );
    return output;
}

[[maybe_unused]] std::vector<std::vector<double>>
DataContainer::filter_if_gt(const int &col_index, const double &val, bool train_set, bool equals) {
    // target pointer, if train_set true, then points to self.train, else points to self.test
    std::vector< std::vector<double>>* tar;
    if(train_set) tar = &train;
    else tar = &test;
    // copy all rows that fit the criteria into output
    std::vector< std::vector<double>> output;
    if(equals)
        std::copy_if (tar -> begin(), tar -> end(),std::back_inserter(output),
                      [&col_index, &val](std::vector<double> row){return row[col_index]>=val;} );
    else
        std::copy_if (tar -> begin(), tar -> end(),std::back_inserter(output),
                      [&col_index, &val](std::vector<double> row){return row[col_index]>val;} );
    return output;
}

[[maybe_unused]] std::vector<std::vector<double>>
DataContainer::filter_if_eq(const int &col_index, const double &val, bool train_set, bool equals) {
    // target pointer, if train_set true, then points to self.train, else points to self.test
    std::vector< std::vector<double>>* tar;
    if(train_set) tar = &train;
    else tar = &test;
    // copy all rows that fit the criteria into output
    std::vector< std::vector<double>> output;
    if(equals)
        std::copy_if (tar -> begin(), tar -> end(),std::back_inserter(output),
                      [&col_index, &val](std::vector<double> row){return row[col_index]==val;} );
    else
        std::copy_if (tar -> begin(), tar -> end(),std::back_inserter(output),
                      [&col_index, &val](std::vector<double> row){return row[col_index]!=val;} );
    return output;
}

std::pair<std::vector <std::vector<double>>, std::vector<std::string>>
DataContainer::filter(const int &col_index, const double &val, const char &comparison, bool equals, bool train_set) {
    // target pointer, if train_set true, then points to self.train, else points to self.test
    std::vector< std::vector<double>>* tar;
    // target pointer for class label
    std::vector< std::string>* tar_tar;
    // set target pointers
    if(train_set){
        tar = &train;
        tar_tar = &train_tar;
    }
    else{
        tar = &test;
        tar_tar = &test_tar;
    }
    // if target hasnt been set yet, throw exception
    if(tar_tar->empty()) throw std::out_of_range("This function requires a class label column to be set");
    // copy all rows that fit the criteria into output
    std::vector< std::vector<double>> output;
    std::vector< std::string> output_tar;
    if(equals) {
        // equ case
        if(comparison == 'e') {
            for(int i = 0; i < tar -> size(); i++ ){
                if(tar->at(i)[col_index] == val){
                    output.push_back(tar->at(i));
                    output_tar.push_back(tar_tar->at(i));
                }
            }
        }
        // gte case
        else if(comparison == 'g'){
            for(int i = 0; i < tar -> size(); i++ ){
                if(tar->at(i)[col_index] >= val){
                    output.push_back(tar->at(i));
                    output_tar.push_back(tar_tar->at(i));
                }
            }
        }
        // lte case
        else if(comparison == 'l'){
            for(int i = 0; i < tar -> size(); i++ ){
                if(tar->at(i)[col_index] <= val){
                    output.push_back(tar->at(i));
                    output_tar.push_back(tar_tar->at(i));
                }
            }
        }
    }
    else {
        // neq case
        if(comparison == 'e') {
            for(int i = 0; i < tar -> size(); i++ ){
                if(tar->at(i)[col_index] != val){
                    output.push_back(tar->at(i));
                    output_tar.push_back(tar_tar->at(i));
                }
            }
        }
        // gt case
        else if(comparison == 'g'){
            for(int i = 0; i < tar -> size(); i++ ){
                if(tar->at(i)[col_index] > val){
                    output.push_back(tar->at(i));
                    output_tar.push_back(tar_tar->at(i));
                }
            }
        }
        // lt case
        else if(comparison == 'l'){
            for(int i = 0; i < tar -> size(); i++ ){
                if(tar->at(i)[col_index] < val){
                    output.push_back(tar->at(i));
                    output_tar.push_back(tar_tar->at(i));
                }
            }
        }
    }
    return {output, output_tar};
}

void DataContainer::set_target(const int &col_index) {
    // if string set target to get col
    if(data[0][col_index].type() == typeid(std::string)) {
        target = get_col<std::string>(col_index, true);
        return;
    }
    // if double cast to string first
    else{
        // add col to target after casting to string
        for(auto &row : data){
            target.emplace_back(std::to_string(std::any_cast<double>(row[col_index])));
        }
        // remove col
        drop_col(col_index);
    }
}

[[maybe_unused]] std::vector<std::string> *DataContainer::get_target() {
    return &target;
}



