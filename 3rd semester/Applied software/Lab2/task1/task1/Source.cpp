#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>


float absolut(float a[], int size) {
    float max = a[0];
    for (int j = 0; j < size; j++) {
        if ((abs(max)) < (abs(a[j]))) {
             max = a[j];
        }
    }

    return max;
}

int main()
{
    float* a, * b;  // указатель на массив
    int i, size_a, size_b;
    float max_a, max_b;

    printf("Cin size of mass 1: ");
    scanf("%d", &size_a);
    printf("Cin elements of mass 1: ");

    a = (float*)malloc(size_a * sizeof(float));
 
    for (i = 0; i < size_a; i++)
    {
        scanf("%f", &a[i]);
    }

    printf("Cin size of mass 2: ");
    scanf("%d", &size_b);
    printf("Cin elements of mass 2: ");

    b = (float*)malloc(size_b * sizeof(float));

    for (i = 0; i < size_b; i++)
    {
        scanf("%f", &b[i]);
    }
    
    max_a=absolut(a, size_a);
    max_b=absolut(b, size_b);

    printf("For mass 1: %f\nFor mass 2: %f", max_a, max_b);

    free(a);
    free(b);
    return 0;
}

