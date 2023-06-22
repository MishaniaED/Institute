#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double func(double x) {
	return (x-4);
}
int find_root(double (*f)(double), double* A, double* B, double E, double* x) {
	while (fabs(*(A) - *(B)) > E) { // вынести в ф-ю
		*(x) = (*(A) + *(B)) / 2;
		if ((f(*(A)) * f(*(x)) > 0))
		*(A) = *(x);
		else *(B) = *(x);
	}
	printf("Result: %lf", *(x));
	return 0;
}


int main()
{
	double A, B, E, x;
	printf( "Enter left border: ");
	scanf("%lf", &A);
	printf("Enter right border: ");
	scanf("%lf", &B);
	printf("Enter accuracy: ");
	scanf("%lf", &E);
	if(A>B){
		printf("[ERROR]: left border bigger than right border!");
		exit(-1);
	}
	if (E < 0) {
		printf("[ERROR]: accuracy can not be negative!");
		exit(-2);
	}

	find_root(func, &A, &B, E, &x);
	
	return 0;
}