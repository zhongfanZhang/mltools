#include <iostream>
using namespace std;

class Base {
private:
	int secret_;
	friend class Composed
public:
	void set_secret(int in) { secret = in; }
};

class Composed{
protected:
	Base secret_;
public:
	Composed(const int& in) { secret_.set_secret(in); }
};

class Derived_composed : public Composed
{
public:
	void print_secret() const { cout << secret_.secret_ << '\n'; }
};


int main(){
	Composed c(10);
	c.print_secret();
}
