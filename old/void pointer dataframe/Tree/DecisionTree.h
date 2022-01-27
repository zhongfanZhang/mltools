//
// Created by Admin on 4/01/2022.
//

#ifndef MLTOOLS_DECISIONTREE_H
#define MLTOOLS_DECISIONTREE_H

#include <vector>
#include "DecisionTreeNode.h"

class DecisionTree {
private:
    DecisionTreeNode* root;
    std::vector<DecisionTreeNode*> leaves;
public:
    /**
     * default constructor, allocates space for the root node
     */
    DecisionTree();

    /**
     * Provides access to write details into a node
     *
     * @param node: the address of the node : DecisionTreeNode*
     * @param cond: condition of the node : double
     * @param samples: the samples and corresponding labels : std::pair< vector<vector<double>>, vector<string>>
     * @param gini: the gini index at the node : float
     */
    static void write_node(DecisionTreeNode* node, const double &cond, std::string &col, const float& gini,
                           const std::pair<std::vector<std::vector<double>>, std::vector<std::string>> &samples);

    /**
     * Creates children for a particular node
     * Adds the new child nodes to the leaves vector
     * Removes the new parent from the leaves vector
     *
     * @param node: the address of the node : DecisionTreeNode*
     * @param left: if true, create left child, set to true by default : bool
     * @param right: if true, create right child, set to true by default : bool
     */
    void create_children(DecisionTreeNode* node, bool left = true, bool right = true);

    /**
     * Gets a pointer to the leaf nodes
     *
     * @return self.leaves : std::vector<DecisionTreeNode*>*
     */
    std::vector<DecisionTreeNode*>* get_leaves();

    /**
     * provides access to the root node of the tree
     *
     * @return a pointer to the root node of the decision tree : DecisionTreeNode*
     */
    DecisionTreeNode* get_root();
};


#endif //MLTOOLS_DECISIONTREE_H
