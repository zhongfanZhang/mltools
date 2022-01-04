//
// Created by Admin on 4/01/2022.
//

#ifndef MLTOOLS_DECISIONTREECLASSIFIER_H
#define MLTOOLS_DECISIONTREECLASSIFIER_H


#include "DecisionTree.h"
#include "src/DataContainer.h"

class DecisionTreeClassifier {
private:
    DecisionTree tree;
public:
    DecisionTreeClassifier();

    void fit(const DataContainer &data);
};


#endif //MLTOOLS_DECISIONTREECLASSIFIER_H
