//
// Created by Admin on 30/12/2021.
//

#include <iostream>
#include <any>


int main(){
    std::cout << "Hello World!\n";
    std::any a = 5;
    std::cout << std::any_cast<int>(a) << std::endl;
    a = "fish\n";
    std::cout << std::any_cast<std::string&>(a) << std::endl;
    return 0;
}