//
// Created by Admin on 4/01/2022.
//

#include "DecisionTree.h"
#include <algorithm>

DecisionTree::DecisionTree() {
    // allocate space on heap for root node
    root = new DecisionTreeNode;
    // add root to leaves
    leaves.emplace_back(root);
}

void DecisionTree::write_node(DecisionTreeNode *node, const std::pair<std::string, std::string>& cond, const std::string& node_class,
                              const float &gini) {
    node -> condition = cond;
    node -> node_class = node_class;
    node -> gini = gini;
}

void DecisionTree::create_children(DecisionTreeNode *node, bool left, bool right) {
    // create child, add self as child -> parent, add child to leaves
    if(left) {
        node -> left_child = new DecisionTreeNode;
        node -> left_child -> parent = node;
        leaves.emplace_back(node -> left_child);
    }
    if(right) {
        node -> right_child = new DecisionTreeNode;
        node -> right_child -> parent = node;
        leaves.emplace_back(node -> right_child);
    }
    // remove self from leaves
    leaves.erase(std::remove(leaves.begin(), leaves.end(), node), leaves.end());
}

std::vector<DecisionTreeNode *> *DecisionTree::get_leaves() {
    return &leaves;
}

DecisionTreeNode *DecisionTree::get_root() {
    return root;
}
