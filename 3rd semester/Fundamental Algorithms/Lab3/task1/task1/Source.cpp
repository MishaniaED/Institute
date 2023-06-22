#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>

void reverse(char* result, int* i, int* copy, int k, int j, int z)
{
	if (*(i) == 2) { 
		*(copy) = result[1];
		result[1] = result[0];
		result[0] = *(copy);
	}
	else
		for (j; j < k; j = -~j) {
			*(copy) = result[j];
			result[j] = result[~-(z - j)];
			result[~-(z - j)] = *(copy);
		}
}

int main() {
	int x, r, base, copy, k=0, i=0, j=0, z, rest, y;
	char result[BUFSIZ];
	printf("Enter the number in 10 base: x = ");
	scanf("%d", &x);
	if (x == 0) {
		printf("Result: %d", x);
		return 0;
	}
	copy = x;
	printf("Enter r: base = 2^");
	scanf("%d", &r);
	if (r > 5 || r < 1) {
		perror("Wrong input");
		return -1;
	}
	base = 2 << (r - 1); // ѕолучаем с/с (1<<r)
	printf("Base: %d\n", base);
	while (copy) {
		rest = copy & (~-base); // отстаток от делени€ на с/с
		//printf("rest = %d", rest);
		result[i] = rest;
		for (y = 0; y < 48; y = -~y) {
			result[i] = -~result[i];
		}
		if ((base == 16 || base == 32) && rest >= 10) {
			for (y = 48; y < 55; y = -~y) {
				result[i] = -~result[i];
			}
		}
		//printf("res[%d] = %c\n", i,result[i]);
		copy >>= r; // делим на r-ю степень двойки
		i = -~i; // прибавление единицы
	}
	z = i;
	k = i >> r;
	if (k == 0 && i == 1) {
		printf("Result: %c", result[0]);
		return 0;
	}
	
	reverse(result, &i, &copy, k, j, z);

	printf("Result: ");
	for (int u=0; u < z; u = -~u) {
		printf("%c", result[u]);
	}
	return 0;
}