//
// Created by Admin on 30/12/2021.
//

#include "DataContainer.h"
#include "ml_util.h"
#define GET_VAR_NAME(x) (#x)

int main(){
    // testing datacontainer stuff
    DataContainer fish("test_double.csv", GET_VAR_NAME(fish));
    printf("before droprow, size = %d:\n", fish.size());
    fish.display(4);
    fish.dropRow(0);
    printf("after droprow, size = %d:\n", fish.size());
    fish.display(3);
    printf("\ndropping 1st col, col_size = %d:\n", fish.size(false));
    fish.dropCol();
    fish.display(3);
    printf("\ncol_size after dropping = %d", fish.size(false));
    std::vector< std::vector<double>> vec2d = fish.getRows(0,1);
    std::cout << "\nrows 0 to 3:\n";
    for(auto &row : vec2d){
        for(auto &element : row){
            std::cout << element << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    std::vector<double> test_col = fish.getCol(0);
    for(auto &element : test_col){
        std::cout << element << "\n";
    }
    std::cout << "\n";
    return 0;
}