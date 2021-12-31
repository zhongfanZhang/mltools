#include <string>
#include <iostream>
using namespace std;

int main() {
	void** data = (void**)malloc(sizeof(void*) * 3);
	
	int* int_arr = new int[2];
	int_arr[0] = 0;
	int_arr[1] = 1;
	
	string* str_arr = new string[3];
	str_arr[0] = "zero";
	str_arr[1] = "one";
	str_arr[2] = "two";

	double* double_arr = new double[4];
	double_arr[0] = 0.1415;
	double_arr[1] = 1.1415;
	double_arr[2] = 2.1415;
	double_arr[3] = 3.1415;

	data[0] = int_arr;
	data[1] = str_arr;
	data[2] = double_arr;

	cout << "\nint array\n";
	for (int i = 0; i < 2; i++) {
		cout << &int_arr[i] << ":" << ((int*)data[0])[i] << endl;
	}

	cout << "\nstring array\n";
	for (int i = 0; i < 3; i++) {
		std::cout << &str_arr[i] << ":" << ((string*)data[1])[i] << std::endl;
	}

	cout << "\ndouble array\n";
	for (int i = 0; i < 4; i++) {
		cout << &double_arr[i] << ":" << ((double*)data[2])[i] << endl;
	}

	return 0; 
}