#include<iostream>
#include <cstdlib>
#include <math.h>
using namespace std;

float** vvod_proverca(float* values, float** ptrarray, int N, float R, int* k) {
	cout << "Cin coordinates: ";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 2; j++) {
			cin >> ptrarray[i][j];
		}
		if (pow(ptrarray[i][0], 2) + pow(ptrarray[i][1], 2) >= pow(R, 2)) {
			values = (float*)realloc(values, (++(*k)) * sizeof(float));
			values[*k-1] = i+1;		
			cout << values[*k - 1];
		}
		cout << endl;
	}
	return ptrarray;
}

void vivod(float* values, float** ptrarray, int N, float x, float y, int* k) {
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
		cout << "Middle abscissa: " << x << "\nMiddle odinate: " << y;
	}
}

int main() {
	float* values = new float[1];
	values[0] = NULL;
	int k = 0;
	//vector<float> values; 
	float x = 0, y = 0, R;
	int N;
	
	cout << "Cin radius of circle: ";
	cin >> R;

	printf("Cin quantity of coordinates: ");
	cin >> N;

	float** ptrarray = new float* [N]; // кол-во строк в массиве
	for (int count = 0; count < N; count++)
		ptrarray[count] = new float[2]; // кол-во столбцов
	//  ptrarray  – массив указателей на выделенный участок памяти под массив вещественных чисел
	//  типа float

	ptrarray = vvod_proverca(values, ptrarray, N, R, &k);
	vivod(values, ptrarray, N, x, y, &k);

	// высвобождение памяти отводимой под двумерный динамический массив:
	for (int count = 0; count < N; count++)
		delete[] ptrarray[count];

	delete[] values;

	return 0;
}