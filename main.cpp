//
// Created by Admin on 30/12/2021.
//

#include <iostream>
#include <any>
#include <fstream>
#include <vector>
#include "DataContainer.h"


int main(){
    // testing datacontainer stuff
    DataContainer data_container("test.csv");
    data_container.display(4);
    return 0;
}