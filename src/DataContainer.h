/**
 * Created by Admin on 30/12/2021.
 * DataContainer.h
 * This class is responsible for reading, storing, and outputting data
 */

#ifndef MLTOOLS_DATACONTAINER_H
#define MLTOOLS_DATACONTAINER_H

#include <any>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <utility>
#include "ml_util.h"

class DataContainer {
private:
    const std::string container_name;

    std::vector< std::vector<std::any>> data; // contains all the data excluding the headers
    std::vector< std::string> col_names; // contains the name of all columns

    std::vector< std::vector<double>> train; // stores the training data set once train_test_split has been called
    std::vector< std::vector<double>> test; // stores the testing data set once train_test_split has been called

    std::vector< std::string> target; // stores the class labels
    std::vector< std::string> train_tar; // stores the class labels for the training set
    std::vector< std::string> test_tar; // stores the class labels for the test set

public:
    /**
     * Reads the file specified by the filename
     *
     * string and loads the character delimited data into a DataContainer
     * @param filename: the name of the file
     * @param delimiter: the delimiter used to separate columns in the file
     * @param cont_name: the name of the container, set to data_container by default
     *
     * The delimiter is set to comma by default, and skip_header
     * is false by default.
     */
    explicit DataContainer(const std::string& filename, std::string cont_name = "data_container", const char& delimiter = ',');

    /**
     * Creates a DataContainer object with 3 vectors
     *
     * @param in_data: Data in the form of a vector of a vector of anys
     * @param in_col_name: column names of the data table
     * @param in_cont_name: a name for the instance of DataContainer
     */
    [[maybe_unused]]
    DataContainer(std::vector< std::vector<std::any>> in_data, std::vector< std::string> in_col_name, std::string in_cont_name);

    /**
     * Displays the top number of rows excluding the header row
     * @param row_count: the number of rows to be displayed
     */
    void display(int row_count, int display_width = 10);

    /**
     * Removes a set number of rows from the DataContainer
     * @param start_row: the index of the first row to be removed, set to 0 by default
     * @param row_count: the number of rows to be removed, set to 1 by default
     *
     * @returns 0: if no rows exist after the completion
     * @returns 1: if row removal is successful, but the DataContainer is not empty
     * @returns -1: if the row removal failed due to start_row out of bounds
     * @returns -2: if the row removal failed due to row_count out of bounds
     */
    [[maybe_unused]]
    int drop_row(const unsigned int &start_row = 0, const unsigned int &row_count = 1);

     /**
      * Removes a set number of columns from the DataContainer
      * @param start_col: the index of the first column to be removed, set to 0 by default
      * @param col_count: the number of columns to be removed, set to 1 by default
      *
      * @returns 0: if no cols exist after the completion
      * @returns 1: if col removal is successful, but DataContainer is not empty
      * @returns -1: if the col removal failed due to start_col out of bounds
      */
    int drop_col(const unsigned int &start_col = 0);

    /**
     * Gets the size of the DataContainer in terms of rows and columns
     * @param rows: rows if true (default), cols if false
     *
     * @return (int) The number of rows if no parameters, or true is provided. The
     * number of columns if false is provided.
     */
     unsigned int size(bool rows = true);

     /**
      * Returns a specified number of rows from the starting index
      * @param row_count: the number of rows to be returned, set to 1 by default
      * @return a specified number of rows in a 2D vector
      *
      * Example Usage: data_container.get_rows(1,1);
      * Gets 1 row starting from the second row.
      */
     [[maybe_unused]] [[deprecated("Replaced with train_test_split, which outputs the data after splitting it")]]
     std::vector< std::vector<double>> get_rows(const unsigned int &start_index, const unsigned int &row_count = 1);

     /**
      * Gets the column specified by the index
      *
      * @param index: the index of the column to be returned
      * @return the column at the index in the form of a std::vector
      *
      * Example Usage: data_container.get_col(0);
      * Gets the first column of the DataContainer
      */
     template<typename T>
     std::vector<T> get_col(const int &index, bool del = false);

     /**
      * Tallies the unique values of a column
      *
      * @param col_index: the index of the column to be tallied
      * @return a key-value pair of values and their counts in the particular column
      *
      * Example Usage: data_container.unique(1);
      * This should return a map of all unique values in the second column of data_container
      */
      template<typename T>
     std::map<T, int> unique(const int &col_index);

     /**
      * Adds a single 1 dimensional vector as a column to the DataContainer,
      * the size of the input column must be same
      * as the size of the columns of the DataContainer
      *
      * @param col_name: name of the new column
      * @param input_data: Data in the form of a 1d vector
      */
     template<typename T>
     void add_col(const std::string &col_name, const std::vector<T> &input_data);

     /**
      * Creates a new data_container that will contain the test data
      * @param test : the proportion desired for the testing data (0-1)
      */
     void train_test_split(const float &test_ratio);

     /**
      * Overloads the [] operator to provide access to a column using
      * the column name
      *
      * @param col_name: the name of the column that needs to be accessed
      * @return all values in the column in the form of a vector of doubles
      */
     std::vector<double> operator[](const std::string &col_name);

    /**col_name
    * Performs one hot encoding on the column of a DataContainer specified by
    * col_index, creating a number of new columns based on the unique value
    * count and removing the old column
    *
    * @param col_index: the column to be encoded
    */
    void one_hot_encoding(const int &col_index, bool remove_old = true);

    /**
     * Returns the index of a column given the name of the column
     *
     * @param col_name: the name of the column : std::string
     * @return the index of the column : int
     */
    int get_col_index(const std::string &col_name);

    /**
     * Getter for self.train
     * @return a copy of the training data
     */
    std::vector< std::vector<double>> get_train();

    /**
     * Getter for self.test
     * @return a copy of the testing data
     */
    [[maybe_unused]]
    std::vector< std::vector<double>> get_test();

    /**
     * filters the train or test data set based on a set of parameters
     *
     * @param col_index: the column that the filter will be based on
     * @param val: the value that the column will be evaluated against
     * @param comparison: gt if 1, lt if -1, if 0 and equals = true then equ
     * @param equals: if true, then a gte, lte, or eq comparison will be made, else gt, lt, ne
     * @param train_set: if true filter train set, else filter test set
     * @return filtered train or test data in a vector<vector<double>>
     */
    std::pair<std::vector <std::vector<double>>, std::vector<std::string>>
    filter(const int &col_index, const double &val, const char &comparison, bool equals = false, bool train_set = true);

    /**
     * returns a vector based on whether a col is less than or
     * less than or equals to a value
     * @param col_index: the index of the column to be evaluated
     * @param val: the value to be compared to
     * @param equals: if true then, lte (less than or equal to), else lt
     * @param train_set: if true then filters the training set, else test set
     * @return returns self.train or self.test based on train_set
     */
    [[maybe_unused]] [[deprecated("All filter functions are combined into filter() instead")]]
    std::vector< std::vector<double>>
    filter_if_lt(const int &col_index, const double &val, bool train_set = true, bool equals = false);

    /**
     * returns a vector based on whether a col is greater than or
     * greater than or equals to a value
     * @param col_index: the index of the column to be evaluated
     * @param val: the value to be compared to
     * @param train_set: if true then filters the training set, else test set
     * @param equals: if true then gte, else gt
     * @return returns self.train or self.test based on train_set
     */
    [[maybe_unused]] [[deprecated("All filter functions are combined into filter() instead")]]
    std::vector< std::vector<double>>
    filter_if_gt(const int &col_index, const double &val, bool train_set = true, bool equals = false);

    /**
     * returns a vector based on whether a col is equal to
     * or not equal to a value
     * @param col_index: the index of the column to be evaluated
     * @param val : the value to be compared to
     * @param train_set: if true then filters the training set, else test set
     * @param equals: if true then equivalence is tested, else the complement
     * @return
     */
    [[maybe_unused]] [[deprecated("All filter functions are combined into filter() instead")]]
    std::vector< std::vector<double>>
    filter_if_eq(const int &col_index, const double &val, bool train_set = true, bool equals = true);

    /**
     * sets a column as the class label column
     * @param col_index: the index of the column to be set as the target
     */
    void set_target(const int &col_index);

    /**
     * getter for self.target
     * @return the class label column for the current dataset
     */
    [[maybe_unused]]
    std::vector<std::string>* get_target();

    /**
     * getter for labels of the training set
     * @return a reference of the labels of the training set
     */
    std::vector<std::string>* get_train_tar();

    /**
     * getter for labels of the testing set
     * @return a reference to the labels of the testing set
     */
    std::vector<std::string>* get_test_tar();
};

#include "DataContainer_impl.h"
#endif //MLTOOLS_DATACONTAINER_H





















