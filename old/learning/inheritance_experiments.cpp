#include <iostream>
using namespace std;

class Parent {
public:
	virtual ~Parent() = default;
	explicit Parent(const int &in) : a(in) {};
	virtual int add(int) = 0;
	auto get_a() const -> int { return a; }
	void set_a(int in) { a = in; }

protected:
	int a;
};

class Other_parent {
public:
	virtual int sub(int) = 0;
};

class Child : public Parent, public Other_parent {
public:
	using Parent::Parent;
	int add(int b) override { return a + b; }
	int sub(int b) override { return a - b; }
};


int main(){
	Child test(10);
	cout << test.add(1) << '\n';
	cout << test.get_a() << '\n';
	test.set_a(100);
	cout << test.get_a() << '\n';
	cout << test.sub(2) << '\n';
}
