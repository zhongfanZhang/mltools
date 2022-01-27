#pragma once
#include "DataContainer.h"
#include "DecisionTree.h"

class DecisionTreeClassifier : public DataContainer, public DecisionTree
{
public:
	void process_data(const std::string& filename, float& test_ratio, bool delim, const std::string& label_col,
		bool encoding) override;
};
