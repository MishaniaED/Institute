#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <malloc.h>

#define N 10

void swap(int* a, int* b) {
	int* p;
	p = *a;
	*a = *b;
	*b = p;
}

int main() {
	int arr[N], A, B, r, max, max_i=0, min, min_i=0;
	srand(time(NULL));
	printf("Enter left border: ");
	scanf("%d", &A);
	printf("Enter right border: ");
	scanf("%d", &B);
	if (A > B) {
		printf("Error: left border bigger than right border");
		exit(-1);
	}
	
	printf("Array: ");
	if (A >= 0 && B >= 0) {
		if (A == B) {
			for (int i = 0; i < N; i++) {
			arr[i] = A;
			printf("%d ", arr[i]);
			}				
		}
		else {
			for (int i = 0; i < N; i++) {
				r = A + rand() % (B-A+1);
				arr[i] = r;
				printf("%d ", arr[i]);
			}
		}
	}
	else if (A <= 0 && B >= 0) {
		for (int i = 0; i < N; i++) {
			r = A + rand() % (-A + B + 1);
			arr[i] = r;
			printf("%d ", arr[i]);
		}
	}
	else if (A <= 0 && B <= 0) {
		for (int i = 0; i < N; i++) {
			r = A + rand() % (-A + B + 1);
			arr[i] = r;
			printf("%d ", arr[i]);
		}
	}
	printf("\nEnter 1 to to change max and min elem in mass");
	printf("\nEnter 2 to create a new array that contains non-repeating elements from the original array in the same order\n");
	scanf("%d", &r);
	if (r == 1) {
		max = arr[0];
		min = arr[0];
		for (int i = 0; i < N; i++) {
			if (arr[i] > max) {
				max = arr[i];
				max_i = i;
			}
			if (arr[i] < min) {
				min = arr[i];
				min_i = i;
			}
		}

		swap(&arr[max_i], &arr[min_i]);
		
		printf("MAX elem in array: %d", max);
		printf("\nMIN elem in array: %d\n", min);
		for (int i = 0; i < N; i++) {
			printf("%d ", arr[i]);
		}
	}
	else if (r == 2) {
		int flag, k=0;
		int* new_arr;
		new_arr = (int*)malloc(sizeof(int));
		if (new_arr == NULL) {
			printf("Memory allocation error");
			exit(-1);
		}
		printf("New mass: ");
		for (int i = 0; i < N; i++) {
			flag = 1;
			for (int j = 0; j < N; j++)
				if (arr[i] == arr[j] && i < j) {
					flag = 0;
					break;
				}
			if (flag == 1) {
				new_arr = (int*)realloc(new_arr, (k+1) * sizeof(int));
				new_arr[k] = arr[i];
				printf("%d ", new_arr[k]);
				k++;
			}
		}
	}
	else printf("Error: wrong key");
	return 0;
}