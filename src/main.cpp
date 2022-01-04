//
// Created by Admin on 30/12/2021.
//

#include "DataContainer.h"
#include "ml_util.h"
#include <chrono>
#define GET_VAR_NAME(x) (#x)

//TODO: cleanup function names - either use camelcase or underscore
//TODO: implement DecisionTreeClassifier
//TODO: implement one_hot_encoding
//TODO: implement addRows
//TODO: implement train_test_split

int main(){
    DataContainer data("test.csv");
    data.display(4);
    std::vector<double> test{1,2,3,4};
    data.addCol("test5",test);
    data.addCol("test6",test);
    data.display(4);
    data.oneHotEncoding(4, false);
    data.display(4);
    return 0;
}