//
// Created by Admin on 30/12/2021.
//

#include "DataContainer.h"
#include "ml_util.h"
#include <chrono>

//TODO: implement ml_util::filter
//TODO: implement DecisionTreeClassifier

int main(){
    auto start = std::chrono::high_resolution_clock::now();
    DataContainer data("test_double.csv","test_container");
    data.display(4);
    // testing add_col
    std::vector<double> test{1,2,3,4};
    try{
        data.add_col("test5", test);
        data.add_col("test6", test);
    }
    catch(std::range_error &e){
        std::cout << e.what() << '\n';
    }
    data.display(4);
    // testing one hot encoding
    data.one_hot_encoding(6);
    data.display(4, 8);
    // testing train_test_split
    data.train_test_split(0.2);
    std::cout << "Train set size: " << data.get_train().size() << '\n';
    std::cout << "Test set size: " << data.get_test().size() << '\n';
    // testing operator[]
    std::cout << "The second value of the \"address\" column: " << data["address"][1] << '\n';
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << double (duration.count()) / 1000000 << "s\n";

    // test with maps, arrays, and vectors
    int* a = new int[10];
    for(int i = 0; i < 10; i++){
        a[i] = i * 2;
    }
    std::map<std::string, int*> t;
    t.insert(std::pair<std::string, int*>{"fish", a});
    for(int i = 0; i < 10; i++){
        std::cout << t["fish"][i] << " ";
    }
    std::cout << '\n';
    return 0;
}