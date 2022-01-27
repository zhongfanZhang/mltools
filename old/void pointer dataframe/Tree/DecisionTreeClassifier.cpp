//
// Created by Admin on 4/01/2022.
//

#include <numeric>
#include "DecisionTreeClassifier.h"

DecisionTreeClassifier::DecisionTreeClassifier(DataContainer* data_container) {
    data = data_container;
    tree = new DecisionTree();
}

void DecisionTreeClassifier::fit(int max_depth) {
    // if no target has been set for data, throw exception
    if(data -> get_target()->empty())
        throw std::out_of_range("DecisionTreeClassifier::fit() requires a target to be set.");
    // get training data
    auto train_data = data -> get_train();


}

double DecisionTreeClassifier::entropy(const std::vector<double> &col, const std::vector<std::string> &labels) {
    // find the average of the column to use as a splitting point
    double col_mean = std::reduce(col.begin(), col.end()) / col.size();
    
}
