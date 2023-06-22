#include <iostream>
using namespace std;

class Lineral_equation {
private:
	double a, b;
public:
	Lineral_equation(double data_a, double data_b) {
		setdata(data_a, data_b);
	}
	void setdata(double data_a, double data_b) {
		a = data_a;
		b = data_b;
		if (a == 0 && b == 0)
			cout << "You enter: y = 0\nThe plot will coincide with the x-axis";
		else cout << "You enter: y = " << a << "*x + " << b;
	}
	void plot() {
		return;
	}
};

