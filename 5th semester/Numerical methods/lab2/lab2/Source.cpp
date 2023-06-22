#include<iostream>

constexpr auto Eps = 0.000001;;

double func1(double x, double y) {
	return (pow(x, 3) + 2 * x * x - 3 * x * y * y + 6 * x * y - x - 2 * y * y + y + 4);
}

double func1dx(double x, double y) {
	return (3 * x * x + 4 * x - 3 * y * y + 6 * y - 1);
}

double func1dy(double x, double y) {
	return  (-6 * x * y + 6 * x - 4 * y + 1);
}

double func2(double x, double y) {
	return (-pow(y, 3) + 3 * y * y + 3 * x * x * y + 4 * x * y - y - 3 * x * x - x - 2);
}

double func2dx(double x, double y) {
	return (6 * x * y + 4 * y - 6 * x - 1);
}

double func2dy(double x, double y) {
	return (-3 * y * y + 6 * y + 3 * x * x + 4 * x - 1);
}

double Proizv(double x, double y, char n, int k)
{
	double h = 0.0001;
	if (k == 0) {
		if (n == 'x')
			return (func1(x + h, y) - func1(x, y)) / h;
		else
			return (func1(x, y + h) - func1(x, y)) / h;
	}
	else
	{
		if (n == 'x')
			return (func2(x + h, y) - func2(x, y)) / h;
		else
			return (func2(x, y + h) - func2(x, y)) / h;
	}
}

bool method_Analays() {
	std::cout << "Аналитическая производная";
	double x_0 = 1, y_0 = 1, x_curr=1, y_curr=1, det;
	int i = 0;
	double matrix[2][2];
	for (i; sqrt(pow(x_curr, 2) + pow(y_curr, 2)) > Eps; ++i) {
		matrix[0][0] = func1dx(x_0, y_0);
		matrix[0][1] = func1dy(x_0, y_0);
		matrix[1][0] = func2dx(x_0, y_0);
		matrix[1][1] = func2dy(x_0, y_0);
		det = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
		x_curr = (matrix[1][1] * func1(x_0, y_0) - matrix[0][1] * func2(x_0, y_0)) / det;
		y_curr = (matrix[0][0] * func2(x_0, y_0) - matrix[1][0] * func1(x_0, y_0)) / det;
		x_0 -= x_curr;
		y_0 -= y_curr;
	}
	std::cout << "\nКоличество итераций: " << i << "\n";
	std::cout << "x: " << x_0 << "\n" << "y: " << y_0 << "\n";
	return true;
}

bool method_Chisl() {
	std::cout << "Численная производная";
	double x_0 = 1, y_0 = 1, x_curr = 1, y_curr = 1, det;
	int i = 0;
	double matrix[2][2];
	for (i; sqrt(pow(x_curr, 2) + pow(y_curr, 2)) > Eps; ++i) {
		matrix[0][0] = Proizv(x_0, y_0, 'x', 0);
		matrix[0][1] = Proizv(x_0, y_0, 'y', 0);
		matrix[1][0] = Proizv(x_0, y_0, 'x', 1);
		matrix[1][1] = Proizv(x_0, y_0, 'y', 1);
		det = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
		x_curr = (matrix[1][1] * func1(x_0, y_0) - matrix[0][1] * func2(x_0, y_0)) / det;
		y_curr = (matrix[0][0] * func2(x_0, y_0) - matrix[1][0] * func1(x_0, y_0)) / det;
		x_0 -= x_curr;
		y_0 -= y_curr;
	}
	std::cout << "\nКоличество итераций: " << i << "\n";
	std::cout << "x: " << x_0 << "\n" << "y: " << y_0 << "\n";
	return true;
}

int main() {
	setlocale(LC_ALL, "RUS");
	method_Analays();
	method_Chisl();
	return 0;
}