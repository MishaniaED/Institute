#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
const int N1 = 5;
const int N2 = 10;


int main() {
    int i, N, r;
    int arr1[N1], arr2[N2], arr3[N1], eps, max_j = 0;

    srand(time(NULL));
    for (i = 0; i < N1; i++) {
        r = rand() % 100;
        arr1[i] = r;
        printf("%d ", arr1[i]);
    }
    printf("\n");
    for (i = 0; i < N2; i++) {
        r = rand() % 100;
        arr2[i] = r;
        printf("%d ", arr2[i]);
    }
    printf("\n");
    
    for (i = 0; i < N1; i++) {
        eps = fabs(arr1[i] - arr2[0]);
        for (int j = 0; j < N2; j++) {
            if (fabs(arr1[i] - arr2[j])<eps) {
                max_j = j;
                eps = fabs(arr1[i] - arr2[j]);
            }
        }
        arr3[i] = arr1[i] + arr2[max_j];
        printf("%d ", arr3[i]);
    }
    return 0;
}
