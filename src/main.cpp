//
// Created by Admin on 30/12/2021.
//

#include "DataContainer.h"
#include "ml_util.h"
#include <chrono>


int main(){
    auto start = std::chrono::high_resolution_clock::now();
    DataContainer data("test.csv","test_container");
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
//    // testing one hot encoding
//    data.one_hot_encoding(6);
//    data.display(4, 8);
//    // testing train_test_split
//    data.train_test_split(0.2);
//    std::cout << "Train set size: " << data.get_train().size() << '\n';
//    std::cout << "Test set size: " << data.get_test().size() << '\n';
//    // testing operator[]
//    std::cout << "The second value of the \"address\" column: " << data["address"][1] << '\n';
//    auto end = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//    std::cout << double (duration.count()) / 1000000 << "s\n";
//
//    // test with maps, arrays, and vectors
//    int* a = new int[10];
//    for(int i = 0; i < 10; i++){
//        a[i] = i * 2;
//    }
//    std::map<std::string, int*> t;
//    t.insert(std::pair<std::string, int*>{"fish", a});
//    for(int i = 0; i < 10; i++){
//        std::cout << t["fish"][i] << " ";
//    }
//    std::cout << '\n';
    try {
        data.one_hot_encoding(1);
    }catch(std::exception &e){
        std::cout << "encoding first col: " << e.what() << '\n';
    }
    data.set_target(3);
    data.display(data.size());
    data.train_test_split(0.2);
    auto train = data.get_train();
    std::cout << "training set:\n";
    for(auto &row : train){
        for(auto &elem : row){
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "outputting filtered train set:\n";
    try {
        auto vec = data.filter(0, 2.2, 'l', true);
        for (auto &row: vec.first) {
            for (auto &elem: row) {
                std::cout << elem << ' ';
            }
            std::cout << '\n';
        }
        std::cout << "outputting the filtered targets:\n";
        for(auto &item : vec.second){
            std::cout << item << '\n';
        }
    }catch(std::out_of_range &e){
        std::cout << e.what() << '\n';
    }

    return 0;
}