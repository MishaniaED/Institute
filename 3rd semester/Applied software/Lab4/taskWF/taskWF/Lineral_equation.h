#pragma once
//#include <iostream>

class Lineral_equation {
public:
	
	double a, b;
	
	void setdata(double data_a, double data_b) {
		a = data_a;
		b = data_b;
	}
	bool check(double a, double b) {
		if (a == 0 && b == 0) return true;
		else return false;
	}
};


