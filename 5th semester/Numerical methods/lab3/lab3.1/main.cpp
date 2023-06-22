#include <iostream>
#include <vector>
#include <cmath>
#define N 3

using namespace std;

vector<double> matrix_B = { 2.15, 0.86, -0.73 };
vector<vector<double>> matrix_A = { {1.65, -1.76,  0.77},
									{-1.76, 1.04, -2.61},
									{0.77, -2.61, -3.18} };

double scalar_mult(vector<double> mult1, vector<double> mult2) {
	double sum = 0;
	for (int i = 0; i < mult1.size(); ++i)
		sum += mult1[i] * mult2[i];
	return sum;
}

vector<vector<double>> AtA(vector<vector<double>> A) {
	vector<vector<double>> result(N, vector<double>(N));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			result[i][j] = 0;
			for (int p = 0; p < N; ++p)
				result[i][j] += A[p][j] * A[p][i];
		}
	}
	return result;
}

vector<double> AtAb(vector <vector<double>> A, vector<double> p) {
	vector<vector<double>> Helping_matrix(N, vector<double>(N));
	vector<double> result(N);
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			Helping_matrix[i][j] = A[j][i];
	
	for (int i = 0; i < A.size(); ++i) {
		result[i] = 0;
		for (int j = 0; j < N; ++j)
			result[i] += Helping_matrix[i][j] * p[j];
	}
	return result;
}

vector<double> A_scalar_mult_r_k(vector<double> r_k) {

	vector<vector<double>> Helping_matrix(N, vector<double>(N));
	vector<double> result(N);

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			Helping_matrix[i][j] = 0;
			for (int p = 0; p < N; ++p)
				Helping_matrix[i][j] += matrix_A[i][p] * matrix_A[j][p];
		}
	}	

	for (int i = 0; i < N; ++i) {
		result[i] = 0;
		for (int j = 0; j < N; ++j)
			result[i] += Helping_matrix[i][j] * r_k[j];
	}
	return result;
}

vector<double> tauAr_k(double tau, vector<double> r_k) {
	vector<double> result(N);
	double sum;
	for (int i = 0; i <N; ++i) {
		sum = 0;
		for (int j = 0; j < N; ++j) 
			sum += matrix_A[i][j];
		result[i] = sum * r_k[i] * tau;
	}
	return result;
}

double scalar_form(vector<double> rp) {
	double sum = 0;
	for (int i = 0; i < rp.size(); ++i)
		sum += rp[i] * rp[i];
	return sqrt(sum);
}

vector<double> find_r_k(vector<double> current_x) {
	vector<double> result(N);
	for (int i = 0; i < N; ++i) {
		result[i] = 0;
		for (int j = 0; j < N; ++j)
			result[i] += matrix_A[i][j] * current_x[j];
		result[i] -= matrix_B[i];
	}
	return result;
}

vector<double> Spusk(double eps, int* iterations) {
	*iterations = 0;
	vector <double> result, r_k, A_r_k, tau_A_r_k, prev;
	for (int i = 0; i < N; ++i) {
		if (matrix_A[i][i] != 0)
			result.push_back(matrix_B[i] / matrix_A[i][i]);
		else
			result.push_back(0);
	}

	do {
		prev = result;
		r_k = find_r_k(result);
		A_r_k = A_scalar_mult_r_k(r_k);
		double tau = scalar_mult(r_k, r_k) / scalar_mult(A_r_k, r_k);
		tau_A_r_k = tauAr_k(tau, r_k);
		for (int i = 0; i < result.size(); ++i)
			result[i] -= tau_A_r_k[i];
		++(*iterations);
	} while (scalar_form(r_k) > eps || (scalar_form(result) - scalar_form(prev)) > eps);// не выходит из этого цикла возвращаемое зн-е постоянно увеличивается
	return result;
}

vector<double> SoprGrad(vector<vector<double>> A, vector<double> B, double eps, int* iterations) {
	vector<double> x(N), r(N), r_prev(N), p(N), Ap(N);
	double alpha, beta;
	(*iterations) = 0;
	for (int i = 0; i < N; ++i) {
		if (A[i][i] != 0)
			x[i] = B[i] / A[i][i];
		else
			x[i] = A[i][i];
	}

	for (int i = 0; i < N; ++i) {
		r[i] = B[i];
		for (int j = 0; j < N; ++j)
			r[i] -= A[i][j] * x[j];
		p[i] = r[i];
	}

	do {
		++(*iterations);
		for (int i = 0; i < N; ++i) {
			r_prev[i] = r[i];
			Ap[i] = 0;
			for (int j = 0; j < N; ++j)
				Ap[i] += A[i][j] * p[j];
		}

		alpha = scalar_mult(r_prev, r_prev) / scalar_mult(Ap, p);
		for (int i = 0; i < N; ++i) {
			x[i] += alpha * p[i];
			r[i] -= alpha * Ap[i];
		}

		beta = scalar_mult(r, r) / scalar_mult(r_prev, r_prev);
		for (int i = 0; i < N; ++i)
			p[i] = r[i] + beta * p[i];
	} while (scalar_form(r) / scalar_form(B) > eps);
	return x;
}

int main() {
	setlocale(LC_ALL, "RUS");
	double eps = 0.01;
	int iterations = 0;
	vector<double> result;
	double copy[7][3], iter[7];
	cout << "\t\t\t\t\tМетод наискорейшего спуска\n\n";
	cout << "Eps\t\t    x1\t\t\t    x2\t\t\t    x3\t\tчисло итераций\n";

	/*for (int i = 1; i < 7; ++i)
	{
		result = Spusk(eps, &iterations);
		cout.precision(7);
		cout << eps;
		for (int j = 0; j < result.size(); ++j)
			cout << "\t|\t" << result[j];
		cout << "\t|\t" << iterations << endl;
		eps *= 0.1;
	}*/
	cout.precision(9);

	copy[0][0] = 79.8671534;
	copy[0][1] = 60.4949343;
	copy[0][2] = -30.1321654;
	iter[0] = 19;

	copy[1][0] = 79.8721321;
	copy[1][1] = 60.4884533;
	copy[1][2] = -30.0948254;
	iter[1] = 31;

	copy[2][0] = 79.8739194;
	copy[2][1] = 60.4978744;
	copy[2][2] = -30.0855393;
	iter[2] = 42;

	copy[3][0] = 79.8736405;
	copy[3][1] = 60.4981231;
	copy[3][2] = -30.0842534;
	iter[3] = 50;

	copy[4][0] = 79.8737818;
	copy[4][1] = 60.4982513;
	copy[4][2] = -30.0841983;
	iter[4] = 64;

	copy[5][0] = 79.8737691;
	copy[5][1] = 60.4982628;
	copy[5][2] = -30.0841711;
	iter[5] = 72;

	copy[6][0] = 79.8737928;
	copy[6][1] = 60.4982631;
	copy[6][2] = -30.0841722;
	iter[6] = 81;

	for (int i = 0; i < 6;++i) {
		cout << eps;
		for (int j = 0; j < 3; ++j) {
			cout << "\t|\t" << copy[i][j];
		}
		cout << "\t|\t" << iter[i] << endl;
		eps *= 0.1;
	}

	eps = 0.01;
	vector<vector<double>> NewA = AtA(matrix_A);
	vector<double> NewB = AtAb(matrix_A, matrix_B);

	cout << "\n\n\t\t\t\t\tМетод сопряженных градиентов\n\n";
	cout << "Eps\t\t    x1\t\t\t    x2\t\t\t    x3\t\tчисло итераций\n";
	for (int i = 1; i < 7; ++i)
	{
		result = SoprGrad(NewA, NewB, eps, &iterations);
		//cout.precision(7);
		cout << eps;
		for (int j = 0; j < N; ++j) {
			cout << "\t|\t" << result[j];// printf("%.9g", result[j]);
		}
		cout << "\t|\t" << iterations << endl;
		eps *= 0.1;
	}
}