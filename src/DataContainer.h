/**
 * Created by Admin on 30/12/2021.
 * DataContainer.h
 * This class is responsible for reading, storing, and outputting data
 */

#ifndef MLTOOLS_DATACONTAINER_H
#define MLTOOLS_DATACONTAINER_H

#include <any>
#include <vector>
#include <string>
#include <map>


class DataContainer {
private:
    std::vector< std::vector<std::any>> data; // contains all the data excluding the headers
    std::vector< std::string> col_names; // contains the name of all columns
    const std::string container_name;
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
     *
     * Example usage: DataContainer("data.csv")
     */
    explicit DataContainer(const std::string& filename, std::string cont_name = "data_container", const char& delimiter = ',');

    /**
     * Displays the top number of rows excluding the header row
     * @param row_count: the number of rows to be displayed
     *
     * Example usage: data_container.display(5);
     * This will display the top 5 rows of the DataContainer called data_container
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
     *
     * If the last row is removed from the DataContainer, the destructor will be
     * called
     *
     * Example usage: data_container.dropRow(0,2);
     * This will remove rows 0 and 1 from the DataContainer called data_container
     */
    int dropRow(const int &start_row = 0, const int &row_count = 1);

     /**
      * Removes a set number of columns from the DataContainer
      * @param start_col: the index of the first column to be removed, set to 0 by default
      * @param col_count: the number of columns to be removed, set to 1 by default
      *
      * @returns 0: if no cols exist after the completion
      * @returns 1: if col removal is successful, but DataContainer is not empty
      * @returns -1: if the col removal failed due to start_col out of bounds
      *
      * If the last column is removed from the DataContainer, the destructor will be
      * called
      *
      * Example usage: data_container.dropCol(0);
      * This will drop the first column from the DataContainer called data_container;
      */
    int dropCol(const int &start_col = 0);

    /**
     * Gets the size of the DataContainer in terms of rows and columns
     * @param rows: rows if true (default), cols if false
     *
     * @return (int) The number of rows if no parameters, or true is provided. The
     * number of columns if false is provided.
     *
     * Example usage: data_container.size();
     * returns the number of rows of the DataContainer data_container
     *                data_container.size(false);
     * returns the number of columns of the DataContainer data_container
     */
     unsigned int size(bool rows = true);

     /**
      * Returns a specified number of rows from the starting index
      * @param row_count: the number of rows to be returned, set to 1 by default
      * @return a specified number of rows in a 2D vector
      *
      * Example Usage: data_container.getRows(1,1);
      * Gets 1 row starting from the second row.
      */
     std::vector< std::vector<double>> getRows(const int &start_index, const int &row_count = 1);

     /**
      * Gets the column specified by the index
      *
      * @param index: the index of the column to be returned
      * @return the column at the index in the form of a std::vector
      *
      * Example Usage: data_container.getCol(0);
      * Gets the first column of the DataContainer
      */
     template<typename T>
     std::vector<T> getCol(const int &index);

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
     void addCol(const std::string &col_name, const std::vector<T> &input_data);

};

#include "DataContainer_impl.h"
#endif //MLTOOLS_DATACONTAINER_H





















