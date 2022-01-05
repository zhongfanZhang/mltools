//
// Created by Admin on 30/12/2021.
//

#include "DataContainer.h"
#include "ml_util.h"
#include <chrono>
#define GET_VAR_NAME(x) (#x)

//TODO: cleanup function names - either use camelcase or underscore
//TODO: implement DecisionTreeClassifier
//TODO: implement train_test_split

int main(){
    auto start = std::chrono::high_resolution_clock::now();
    DataContainer data("test_double.csv","test_container");
    data.display(4);
    std::vector<double> test{1,2,3,4};
    try{
        data.addCol("test5",test);
        data.addCol("test6",test);
    }
    catch(std::range_error &e){
        std::cout << e.what() << '\n';
    }
    data.display(4);
    data.oneHotEncoding(6);
    data.display(4, 8);
    auto out = data.train_test_split(0.8, 0.2);
    std::cout << "Train set size: " << out.first.size() << '\n';
    std::cout << "Test set size: " << out.second.size() << '\n';
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << double (duration.count()) / 1000000 << "s\n";
    return 0;
}