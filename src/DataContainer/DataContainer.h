#ifndef DATACONTAINER_H
/**
 * \brief Parses and stores data from character delimited files, provides methods to process data for machine learning models
 */
#define DATACONTAINER_H

#include <map>
#include <string>
#include <vector>

namespace ml_tools
{
	class DataContainer
	{
	private:
		std::map<std::string, std::string> m_raw_data;
	public:
		/*
		 *  Containers
		 */
		std::map<std::string, std::vector<double>> numeric_data_train;
		std::vector<std::string> label_train;

		std::map<std::string, std::vector<double>> numeric_data_test;
		std::vector<std::string> label_test;

		/*
		 * Methods
		 */

		/**
		 * \brief saves the content of a delimiter separated file into a DataContainer
		 * \param filename the name of the delimiter separated file to read
		 * \param delimiter the delimiter used to separate values, set to ',' by default
		 */
		void read_csv(const std::string & filename, char delimiter = ',');

		/**
		 * \brief randomly splits the data into train and test data sets
		 * \param test_ratio : the proportion desired for the testing data (0-1)
		 */
		void train_test_split(const float& test_ratio);

		/**
		 * \brief Performs one hot encoding on the column of a DataContainer specified by
		 * col_index, creating a number of new columns based on the unique value
		 * count and removing the old column
		 * \param col_name the name column to be encoded
		 * \param remove_old whether the old column should be removed
		 */
		void one_hot_encoding(const std::string & col_name, bool remove_old = true);

		/**
		 * \brief Sets a column as the class label column
		 * \param col_name the name of the column to be set as the target
		 */
		void set_label_col(const std::string & col_name);

		/**
		 * \param train returns the size of the train or test set based on this flag
		 * \return the number of rows in the data set
		 */
		unsigned int data_row_count(bool train = true);


		/**
		 * \param train returns the size of the train or test set based on this flag
		 * \return the number of rows in the data set
		 */
		unsigned int data_col_count(bool train = true);
	};
}

#endif // DATACONTAINER_H