//
// Created by Admin on 4/01/2022.
//

#ifndef MLTOOLS_DECISIONTREECLASSIFIER_H
#define MLTOOLS_DECISIONTREECLASSIFIER_H


#include "DecisionTree.h"
#include "src/DataContainer.h"

class DecisionTreeClassifier {
private:
    DecisionTree* tree; // The decision tree
    DataContainer* data; // used to store the data set

    /*
     * helper functions
     */

    /**
     * Calculates the entropy of a column
     *
     * @param col: a reference of the column
     * @param labels: a reference to the labels associated with the column
     * @return the entropy of the column : double
     */
    double entropy(const std::vector<double> &col, const std::vector<std::string> &labels);
public:
    /**
     * constructor that stores the pointer of a DataContainer
     * @param data_container: the DataContainer that contains all data used for the decision tree
     */
    explicit DecisionTreeClassifier(DataContainer* data_container);

    /**
     * uses entropy() to determine the best columns to split and build
     * the decision tree
     *
     * @param max_depth: the maximum depth of the decision tree
     */
    void fit(int max_depth = 30);
};


#endif //MLTOOLS_DECISIONTREECLASSIFIER_H
