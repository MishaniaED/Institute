#include<iostream>
#include<cmath>
using namespace std;

double func(double x) {
	return (-cosf(powf(x, 0.49) + sqrt(30 / 7)) + pow(x, 0.2) / x - x);
}

int main()
{
	double A, B, E, x;
	cout << "A = ";
	cin >> A;
	cout << "B = ";
	cin >> B;
	cout << "E = ";
	cin >> E;
	x = (A + B) / 2;
	while (fabs(A-B)>E) {
		x = (A + B) / 2;
		(func(A) * func(x)) > 0 ? A = x : B = x;

	}
	cout << "Result: " <<x;
}