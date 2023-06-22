#include <iostream>
#define N 3

double A[N][N] = {{1.65, -1.76,  0.77},
				  {-1.76, 1.04, -2.61},
				  {0.77, -2.61, -3.18}
				 };

double B[N] = { 2.15, 0.86, -0.73 };

void Gauss(double* X)
{
	for (int i = 0; i < N; i++) {
		double copy_aii = A[i][i];
		B[i] /= copy_aii;
		for (int j = 0; j < N; j++)
			A[i][j] /= copy_aii;

		for (int k = i + 1; k < N; k++) {
			double t = A[k][i] / A[i][i];
			B[k] -= B[i] * t;
			for (int l = 0; l < N; l++)
				A[k][l] -= A[i][l] * t;
		}
	}

	X[N - 1] = B[N - 1];
	for (int i = N - 2; i >= 0; --i) {
		X[i] = B[i];
		for (int j = N - 1; j > i; --j)
			X[i] -= A[i][j] * X[j];
		X[i] /= A[i][i];
	}
}

int main() {
	double* Answer = new double[N];
	std::cout << "\t Matrix a \t\t\tMatrix b\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; ++j)
			std::cout << A[i][j] << "\t";
		std::cout << "|\t   " << B[i] << "\n";
	}

	std::cout.precision(9);
	Gauss(Answer);
	std::cout << "\n\n\t\tAnswer\n";
	for (int i = 0; i < N; ++i)
		std::cout << Answer[i] << " \t";

	delete[] Answer;
	return 0;
}
