#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>

int get_determinant(double** a, int m) {
	int i, j = 0, d = 0, k = 1, n = m - 1;
	double** p;
	p = (double**)malloc(sizeof(double) * m);
	for (i = 0; i < m; i++)
		p[i] = (double*)malloc(sizeof(double) * m);
	
	if (m < 1) printf("Cannot find determinant\n");
	else if (m == 1) {
		d = a[0][0];
		return(d);
	}
	else if (m == 2) {
		d = a[0][0] * a[1][1] - (a[1][0] * a[0][1]);
		return(d);
	}
	else if (m > 2) {
		for (i = 0; i < m; i++) {
			d = d + k * a[i][0] * get_determinant(p, n);
			k = -k;
		}
	}
}

void get_multiplication(double** a, double** b, double** c, int N, int M, int T)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			c[i][j] = 0;
			for (int k = 0; k < T; k++)
				c[i][j] += a[i][k] * b[k][j];
		}
	}
}

int	main()
{
	int rowA, colA, rowB, colB, det1, det2;
	double** matrA, ** matrB, ** matrC;

	printf("Number of rows in matrix A = ");
	scanf("%d", &rowA);
	printf("Number of columns in matrix A = ");
	scanf("%d", &colA);
	printf("Enter matrix A :\n");

	matrA = (double**)malloc(sizeof(double) * rowA);
	if (matrA == NULL) {
		printf("Memory allocation error");
		exit(-1);
	}
	for (int i = 0; i < rowA; i++) {
		matrA[i] = (double*)malloc(sizeof(double) * colA);
		if (matrA[i] == NULL) {
			printf("Memory allocation error");
			exit(-1);
		}
		for (int j = 0; j < colA; j++)
			scanf("%lf", &matrA[i][j]);
	}
	printf("Number of rows in matrix B = ");
	scanf("%d", &rowB);
	printf("Number of columns in matrix B = ");
	scanf("%d", &colB);
	printf("Enter matrix B :\n");

	matrB = (double**)malloc(sizeof(double) * rowB);
	if (matrB == NULL) {
		printf("Memory allocation error");
		exit(-1);
	}
	for (int i = 0; i < rowB; i++) {
		matrB[i] = (double*)malloc(sizeof(double) * colB);
		if (matrB[i] == NULL) {
			printf("Memory allocation error");
			exit(-1);
		}
		for (int j = 0; j < colB; j++)
			scanf("%lf", &matrB[i][j]);
	}

	matrC = (double**)malloc(sizeof(double) * rowA);
	if (matrC == NULL) {
		printf("Memory allocation error");
		exit(-1);
	}
	for (int i = 0; i < rowA; i++) {
		matrC[i] = (double*)malloc(sizeof(double) * colB);
		if (matrC[i] == NULL) {
			printf("Memory allocation error");
			exit(-1);
		}
	}
		

	if (rowA == colA) {
		det1 = get_determinant(matrA, rowA);
		printf("Determinant of matrix A = ");
		printf("%d\n", det1);
	}
	else printf("Cannot find determinant of matrix A\n");

	if (rowB == colB) {
		det2 = get_determinant(matrB, rowB);
		printf("Determinant of matrix B = ");
		printf("%d\n", det2);
	}
	else printf("Cannot find determinant of matrix B\n");

	if (colA == rowB) {
		get_multiplication(matrA, matrB, matrC, rowA, colB, colA);
		printf("Matrix C :\n");
		for (int i = 0; i < rowA; i++) {
			for (int j = 0; j < colB; j++)
				printf("%lf\t", matrC[i][j]);
			printf("\n");
		}
	}
	else printf("Multiplication is impossible\n");

	for (int i = 0; i < rowA; i++) {
		free(matrA[i]);
	}
	free(matrA);
	for (int i = 0; i < rowB; i++) {
		free(matrB[i]);
	}
	free(matrB);
	for (int i = 0; i < rowA; i++) {
		free(matrC[i]);
	}
	free(matrC);
	return 0;
}