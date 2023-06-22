#include <iostream>
#include <math.h>
# define M_PI 3.14159265358979323846
# define EPS 10e-5
using namespace std;

double F(double x) {
	return ((x * sin(x)) / (1 + cos(x) * cos(x)));
}

double Trapez_method(double left, double right, int segments) {
	double integral = 0.0, h = (right - left) / segments,
		F_left = F(left), F_right;

	if (segments == 1)
		return integral;

	for (int i = 0; i < segments; ++i) {
		F_right = F(left + i * h + h);
		integral += (F_left + F_right) * (h) / 2;
		F_left = F_right;
	}
	return integral;
}

double Simpson_method(double left, double right, int segments) {
	double integral = 0.0, h = (right - left) / (2 * segments), tmp;
	for (int i = 0; i < segments; ++i) {
		tmp = left + i * 2 * h;
		integral += (h / 3) * (F(tmp) + 4 * F(tmp + h) + F(tmp + 2 * h));
	}
	return integral;
}

int main() {
	cout.precision(7);
	setlocale(LC_ALL, "Russian");
	double left = 0.0, right = M_PI, integral_trapez, Trapez_Richardson, prev;
	double Simpson_integral, Simpson_Richardson;
	int segments = 2;

	do {
		prev = Trapez_method(left, right, segments);
		segments *= 2;
		integral_trapez = Trapez_method(left, right, segments);
	} while (fabs(integral_trapez - prev) > EPS / 2);

	cout << "\nМетод трапеций:\nПриближенное значение интеграла = " << integral_trapez << "\nЧисло разбиений = " << segments << endl;;
	Trapez_Richardson = (4 * Trapez_method(left, right, segments * 2) - integral_trapez) / 3;
	cout << "\nПосле уточнения методом Ричардсона:\nПриближенное значение интеграла = " << Trapez_Richardson << endl;

	segments = 2;

	do {
		prev = Simpson_method(left, right, segments);
		segments *= 2;
		Simpson_integral = Simpson_method(left, right, segments);
	} while (fabs(Simpson_integral - prev) > EPS);

	cout << "\nМетодом Симпсона:\nПриближенное значение интеграла = " << Simpson_integral << "\nЧисло разбиений = " << segments << endl;;
	Simpson_Richardson = (16 * Simpson_method(left, right, segments * 2) - Simpson_integral) / 15;
	cout << "\nПосле уточнения методом Ричардсона: \nПриближенное значение интеграла = " << Simpson_Richardson << endl;

	return 0;
}
