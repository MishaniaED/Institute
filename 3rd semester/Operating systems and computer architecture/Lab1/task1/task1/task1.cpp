#include <iostream>
using namespace std;

int main()
{
	int a, b, res;
	cout << "cin 2 numbers: ";
	cin >> a >> b;
	res = a * b;
	while (a != 0 && b != 0)
	{
		(a > b) ? a = a % b : b = b % a;
	}
	res /= (a + b);
	cout << "NOD: " << a + b << "\nNOK:" << res;
}