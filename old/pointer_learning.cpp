#include <iostream>
#include <vector>
using namespace std;

int main() {
	char a = 'a';
	int zero = 0;
	string test = "test";
	vector<int> v;

	for (int i = 0; i < 10; i++) {
		v.push_back(i);
	}

	void** arr = (void**)malloc(sizeof(void*) * 4);
	char* c = &a;
	int* i = &zero;
	string* s = &test;


	arr[0] = c;
	arr[1] = i;
	arr[2] = s;
	arr[3] = &v;

	cout << *(char*)arr[0] << endl;
	cout << *(int*)arr[1] << endl;
	cout << *((char**)arr[2])[0] << endl;
	cout << test[0] << endl;

	*((char**)arr[2])[0] = 'r';
	cout << *((char**)arr[2]) << endl;

	for(int j = 0; j < 10; j++){
		cout << (*(vector<int>*)arr[3])[j];
	}
}