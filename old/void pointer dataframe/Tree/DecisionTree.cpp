//
// Created by Admin on 4/01/2022.
//

#include "DecisionTree.h"
#include <algorithm>
#include <set>

DecisionTree::DecisionTree() {
    // allocate space on heap for root node
    root = new DecisionTreeNode;
    // add root to leaves
    leaves.push_back(root);
}

void DecisionTree::write_node(DecisionTreeNode *node, const double& cond,
                              std::string &col, const float &gini,
                              const std::pair<std::vector<std::vector<double>>, std::vector<std::string>> &samples) {
    node -> samples = samples.first;
    node -> labels = samples.second;
    node -> attribute = col;
    node -> condition = cond;
    node -> gini = gini;
    // set node class
    std::set<std::string> unique(node -> labels.begin(), node -> labels.end());
    auto itr = unique.begin();
    // if there is only one unique value, set node_class to that value
    if(unique.size() == 1) node -> node_class = *itr;
    // if there is multiple, find the majority
    else if(unique.size() > 1){
        std::vector<int> tally(unique.size(), 0);
        // for each value in label, check which unique label it is and tally
        for(auto &value : node -> labels){
            for(int i = 0; i < unique.size(); i++){
                if(value == *itr)
                    tally[i]++;
            }
        }
        // get the index of the highest tally and set label
        auto it = std::max_element(tally.begin(), tally.end());
        auto index = std::distance(tally.begin(), it);
        std::advance(itr,index);
        node -> node_class = *itr;
    }
}

void DecisionTree::create_children(DecisionTreeNode *node, bool left, bool right) {
    // create child, add self as child -> parent, add child to leaves
    if(left) {
        node -> left_child = new DecisionTreeNode;
        node -> left_child -> parent = node;
        leaves.push_back(node -> left_child);
    }
    if(right) {
        node -> right_child = new DecisionTreeNode;
        node -> right_child -> parent = node;
        leaves.push_back(node -> right_child);
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
