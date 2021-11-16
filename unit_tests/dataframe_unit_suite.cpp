//
//  unit_suite.cpp
//  mltools
//
//  Created by Zhongfan Zhang on 5/11/21.
//

#include <stdio.h>
#include "dataframe.h"
using namespace std;

bool load_header_csv(){
    // set correct results for column names
    vector<string> correct_cols;
    correct_cols.push_back("col1");
    correct_cols.push_back("col2");
    correct_cols.push_back("col3");
    correct_cols.push_back("col4");
    //test setup - testing csv reading with headers by checking headers and data
    Dataframe* test = new Dataframe("data.csv", true, ",");
    col_names = test.getColNames();
    data = test.getData();
    // tests
    if(test -> rows != 1){
        return false;
    }
    if(test -> cols != 4){
        return false;
    }
    for(int i = 0; i < 4; i++){
        if(data[0][i] != i){
            return false;
        }
        if(col_names[i] != correct_cols[i]){
            return false;
        }
    }
    return true;
}

int main(){
    //result counters
    int success = 0;
    int fail = 0;
    
    if(load_header_csv()){
        cout << "load_header_csv test passed!\n";
        success++;
    }else{
        cout << "load_header_csv test failed!\n";
        fail++;
    }
}
