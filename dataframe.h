//
//  dataframe.h
//  mltools
//
//  Created by Zhongfan Zhang on 4/11/21.
//

#ifndef dataframe_h
#define dataframe_h

#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>

class Dataframe{
private:
    /*
     vectors to contain the data read from the file and the names of the columns
     */
    std::vector<std::vector<double>> data;
    std::vector<std::string> col_names;
    //--------------------------------------private functions--------------------------------------
    std::vector<std::string> split(std::string str, char delimiter = ',');
public:
    /*
     Public members used to access information about the data
     */
    int rows;
    int cols;
    //--------------------------------------public functions--------------------------------------
    /*
     Constructor: takes a filename and a delimiter and reads the contents of the file
     into vectors.
     */
    Dataframe(std::string filename, bool header = true, std::string delimiter = ",");
    /*
     getData: provides access to the data vector
     */
    std::vector<std::vector<double>> getData();
    /*
     getColName: provides access to vector containing the column names
     */
    std::vector<std::string> getColNames();
    /*
     getUnique: provides a list of unique values found in a given column
     */
    std::map<std::string, int> getUnique(std::string colName);
    /*
     getRow: get a individual row from the dataframe
     */
    std::vector<double> getRow(int index);
    /*
     Isolate a individual column
     */
    std::vector<double> getCol(std::string col_name);
    
};

#endif
