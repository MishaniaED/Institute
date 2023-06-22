#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 60

int main() {
	int i, r;
	int arr[N], size, max_i = 0, min_i = 0;
	printf("Enter size of massive(1 <= size <= %d): ", N);
	scanf("%d", &size);

	if (size < 1 || size > N) {
		printf("[ERROR]:Invalid size\n");
		return 1;
	}

	srand(time(NULL));
	for (i = 0; i < size; i++) {
		arr[i] = rand()%100;
		printf("%d ", arr[i]);
	}
	for (i = 1; i < size; i++)
	{
		if (arr[max_i] < arr[i]) {
			max_i = i;
		}
		if (arr[min_i] > arr[i]) {
			min_i = i;
		}
	}
	printf("\n");
	r = arr[max_i];
	arr[max_i] = arr[min_i];
	arr[min_i] = r;
	for (i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}

}
