//
// Created by Admin on 30/12/2021.
//

#include "DataContainer.h"
#define GET_VAR_NAME(x) (#x)

int main(){
    // testing datacontainer stuff
    DataContainer fish("test.csv", GET_VAR_NAME(fish));
    printf("before droprow, size = %d:\n", fish.size());
    fish.display(4);
    fish.dropRow(0);
    printf("after droprow, size = %d:\n", fish.size());
    fish.display(3);
    printf("\ndropping 1st col, col_size = %d:\n", fish.size(false));
    fish.dropCol();
    fish.display(3);
    printf("\ncol_size after dropping = %d", fish.size(false));

    return 0;
}