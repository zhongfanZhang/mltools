//
//  main.cpp
//  mltools
//
//  Created by Zhongfan Zhang on 4/11/21.
//

#include <iostream>
#include "dataframe.h"
#include "util.h"

std::vector<std::string> split(std::string str, char delimiter = ',') {
    std::vector<std::string> output;
    // make substrs based on delimiter
    int start = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == delimiter) {
            output.push_back(str.substr(start, i - start));
            start = i + 1;
        }
        else if (i == str.length() - 1) {
            output.push_back(str.substr(start, i - start + 1));
        }
    }
    return output;
}

int main(int argc, const char * argv[]) {
    // test 1 - default delimiter
    std::string str = "one,two,three,four";
    std::vector<std::string> splitstr = split(str);
    if (splitstr[0] == "one" && splitstr[1] == "two" && splitstr[2] == "three" && splitstr[3] == "four") {
        std::cout << "Comma delimiter split test passed.\n";
    }
    else {
        std::cout << "Comma delimiter split test failed.\n";
    }
    // test 2 - whitespace delimiter
    std::string str1 = "one two three four";
    std::vector<std::string> splitstr1 = split(str1,' ');
    if (splitstr1[0] == "one" && splitstr1[1] == "two" && splitstr1[2] == "three" && splitstr1[3] == "four") {
        std::cout << "whitespace delimiter split test passed.\n";
    }
    else {
        std::cout << "whitespace delimiter split test failed.\n";
    }
    return 0;
}
