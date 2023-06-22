#include<iostream>
#include <cstdlib>
#include <math.h>
using namespace std;

void Input(float** ptrarray, int rows, int columns) {
	cout << "Cin elements of matrix: ";
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			cin >> ptrarray[i][j];
}

void Processing(float** ptrarray, int rows, int columns) {
	float max, srarifm = 0;
	int flag = 1;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			if (ptrarray[i][j] < 0) {
				flag = 0;
				max = ptrarray[i][j];
				break;
			}
	if (flag == 1)
		cout << "No one element negative\n";
	else {
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				if (max < ptrarray[i][j] && ptrarray[i][j]<0)
					max = ptrarray[i][j];
		cout << "Max negative element: " << max;
	}
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++) {
			srarifm += ptrarray[i][j];
		}
	srarifm = srarifm / (rows * columns);
	cout << "\nThe arithmetic mean: " << srarifm;
}


int main() {
	int rows, columns;
	cout << "Cin number of lines: ";
	cin >> rows;
	cout << "Cin number of columns: ";
	cin >> columns;

	float** ptrarray = new float* [rows]; // кол-во строк в массиве
	for (int count = 0; count < rows; count++)
		ptrarray[count] = new float[columns];

	 
	Input(ptrarray, rows, columns);
	Processing(ptrarray, rows, columns);



	for (int count = 0; count < rows; count++)
		delete[] ptrarray[count];

	
	return 0;
}