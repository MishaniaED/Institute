#pragma once
#include <iostream>
#include <cstdlib>
#include <math.h>
using namespace std;

float** vvod_proverca(int* values, float** ptrarray, int N, float R, int* k) {
	cout << "Cin coordinates: ";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 2; j++) {
			cin >> ptrarray[i][j];
		}
		if (pow(ptrarray[i][0], 2) + pow(ptrarray[i][1], 2) >= pow(R, 2)) {
			values = (int*)realloc(values, (++(*k)) * sizeof(int));
			values[*k - 1] = i + 1;
			cout << values[*k - 1];
		}
		cout << endl;
	}
	return ptrarray;
}

void vivod(int* values, float** ptrarray, int N, float x, float y, int* k) {
	if (values[0] != NULL) {
		cout << "Numbers of points which outside the circle: ";
		for (int i = 0; i < *k; i++)
			cout << values[i] << ' ';
	}
	else {
		for (int i = 0; i < N; i++) {
			x = x + ptrarray[i][0];
			y = y + ptrarray[i][1];
		}
		x = x / N;
		y = y / N;
		cout << "Middle abscissa: " << x << "\nMiddle ordinate: " << y;
	}
}

int* Amain(float R, int N, float** ptrarray, int* values, int k) {
	float x = 0, y = 0;

	ptrarray = vvod_proverca(values, ptrarray, N, R, &k);
	vivod(values, ptrarray, N, x, y, &k);

	// высвобождение памяти отводимой под двумерный динамический массив:
	for (int count = 0; count < N; count++)
		delete[] ptrarray[count];

	return values;
}