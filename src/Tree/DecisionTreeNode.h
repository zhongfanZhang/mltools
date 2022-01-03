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
    std::pair<std::string, std::string> condition;
    std::string node_class;
    float gini;
};

#endif //MLTOOLS_DECISIONTREENODE_H
