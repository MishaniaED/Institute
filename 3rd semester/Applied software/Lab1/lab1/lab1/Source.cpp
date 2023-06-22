#include<iostream>
#include<cmath>
using namespace std;

int main()
{
	int i = 1;
	double a1, a2=0, E, sum, kont, x;
	cout << "Cin number: ";
	cin >> x;
	cout << "Cin accuracy: ";
	cin >> E;
	a1 = 2 * pow(x, 3) / (3);
	sum = a1;
	do
	{
		a2 = a1;
		a1 *= (-1) * ((2 * i - 1) * pow(x, 2)) / (2 * i + 3);
		sum += a1;
		i++;
	} while (fabs(a1 - a2) > E);

	kont = (1 + pow(x, 2)) * atan(x) - x;
	cout << "Sum: " << sum << "\n" << "Kont: " << kont << "\n";
	if (fabs(sum - kont) < E)
		cout << "Correct";
	else cout << "Error";
}