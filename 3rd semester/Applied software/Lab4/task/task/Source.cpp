#include "Class.h"

int main() {
	double a, b;
	cout << "Input coefficient at x: "; cin >> a;
	cout << "Input free member: ";      cin >> b;
	Lineral_equation equation(a,b);
	return 0;
}