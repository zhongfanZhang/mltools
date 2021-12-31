#include <iostream>
#include "dataframe.cpp"
using namespace std;

int main() {
	Dataframe* df = new Dataframe("test.csv");
	cout << df->col_count << endl;
	cout << df->row_count << endl;
}