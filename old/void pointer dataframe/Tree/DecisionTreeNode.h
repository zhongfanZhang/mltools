#ifndef MLTOOLS_DECISIONTREENODE_H
#define MLTOOLS_DECISIONTREENODE_H

#include <utility>
#include <string>

struct DecisionTreeNode{
    // access vars
    DecisionTreeNode* parent = nullptr;
    DecisionTreeNode* left_child = nullptr;
    DecisionTreeNode* right_child = nullptr;
    // data
    std::string attribute;
    double condition;
    std::string node_class;
    float gini;
    // associated data
    std::vector< std::vector<double>> samples;
    std::vector< std::string> labels;
};

#endif //MLTOOLS_DECISIONTREENODE_H
