#include<iostream>

#define Eps 0.000001


double F(double x){
	return pow(1.4, x) - 2 * x - 0.5;
}

double F_der(double x) {
	return 1 / (log(1.4) * pow(1.4, x) - 2);
}

int main() {
	double a1 = 0, b1 = 5, x1 = 0, x2 = 0, param;
	int iter1 = 0, iter2 = 0;

	while (fabs(b1 - a1) / 2 > Eps) {
		++iter1;
		x1 = (a1 + b1) / 2;
		if ((F(a1) * F(x1)) > 0) a1 = x1;
		else b1 = x1;
	}

	a1 = 5, b1 = 10;
	while (fabs(b1 - a1) / 2 > Eps) {
		++iter2;
		x2 = (a1 + b1) / 2;
		if ((F(a1) * F(x2)) > 0) a1 = x2;
		else b1 = x2;
	}

	std::cout << "Method dihotomie:\n";
	std::cout.precision(6);
	std::cout << "x1 = " << x1 << "  ";
	std::cout << "Iterations: " << iter1 << "\n";
	std::cout << "x2 = " << x2 << "  "; 
	std::cout << "Iterations: " << iter2 << "\n";

	iter1 = 0;
	iter2 = 0;
	std::cout << "Method of simple iterations:\n";
	double x0 = 0;
	param = F_der(x0);

	for (;;)
	{
		++iter1;
		x1 = x1 - param * F(x1);
		if (fabs(x1 - x0) < Eps) break;
		x0 = x1;
	}

	x0 = 8;
	param = F_der(x0);
	for (;;)
	{
		++iter2;
		x2 = x2 - param * F(x2);
		if (fabs(x2 - x0) < Eps) break;
		x0 = x2;
	}

	std::cout << "x1 = " << x1 << "  ";
	std::cout << "Iterations: " << iter1 << "\n";
	std::cout << "x2 = " << x2 << "  ";
	std::cout << "Iterations: " << iter2 << "\n";

	/*double roots[2];
	double x, tau = 2 / (F_der(0) + F_der(10));
	int i, sign = (F(0) < 0) ? -1 : 1;

	for (int j = 0; j < 2; j++)
	{
		x = x0;
		for (i = 1; ; i++)
		{
			if (i > 1000)
				return false;

			x -= sign * tau * F(x);
			if (((fabs(x - x0) < Eps) || (fabs(F(x)) < Eps)))
				break;
		}
		std::cout << "\t" << i;
		roots[j] = x;
	}*/
	
	return 0;
}