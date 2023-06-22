#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double srgeom(int size, ...)
{
    int size_cp = size;
    int res = 1;
    for (int* ptr = &size; size > 0; size--)
    {
        // Обработать отрицательные числа
        if (*(ptr) < 0) {
            printf("Negative number was entered\n");
            exit(-1);
        }
        res *= *(++ptr);
    }
    return pow(res, 1.0 / size_cp);
}

double rec_pow(double x, int n)
{
    if (n == 0)
        return 1;
    else if (n > 0)
        return x * rec_pow(x, n - 1);
    else if (n < 0)
        return  1.0 / rec_pow(x, -n);
}


int main() {
	printf("Srednee geometr: %g\n", srgeom(3, -4, 4, 4));
    printf("Pow %g\n", rec_pow(2, 0));
    return 0;
}

