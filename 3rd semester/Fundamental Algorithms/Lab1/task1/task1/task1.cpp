#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

long double fact(int N)
{
	long int res = 1;
	for (int i = 1; i <= N; i++)
	{
		res *= i;
	}
	return res;
}

int main(int argc, char *argv[]) {
	int x, k, i;
	double sam = 0;

	// Обработка ошибок
	if (argc < 3) {
		printf("[ERROR_1]: No key!\n");
		return 1;
	}

	if (argc > 3) {
		printf("[ERROR_2]: Too much flags and numbers!\n");
		return 1;
	}
	if (argc = 3 && !atoi(argv[1]) && *argv[1] != '0') {
		printf("[ERROR_3]: The key should not be placed first!\n");
		return 1;
	}

	if (strcmp(argv[2], "-h") && strcmp(argv[2], "-p") && strcmp(argv[2], "-s") && strcmp(argv[2], "-e") && strcmp(argv[2], "-a") && strcmp(argv[2], "-f") &&
		strcmp(argv[2], "/h") && strcmp(argv[2], "/p") && strcmp(argv[2], "/s") && strcmp(argv[2], "/e") && strcmp(argv[2], "/a") && strcmp(argv[2], "/f")) {
		printf("[ERROR_4]: There is no such key!\n");
		return 1;
	}

	for (i = 0; i < strlen(argv[1]); i++) {
		if (((argv[1][i] < 48 /*'0'*/ || argv[1][i] > 57 /*'9'*/) && argv[1][0] != '-') || (strlen(argv[1]) > 1 && argv[1][0] == '0')) {
			printf("[ERROR_5]: You entered an incorrect number!\n");
			return 1;
		}
	}
	x = atoi(argv[1]); // строку в число
	k = x;
	if (*argv[2] == '-' || *argv[2] == '/') {
		if (argv[2][1] == 'h') {
			if (k < 100) {
				printf("Multiples numbers: ");
				while (k < 100) {
					printf("%d ", k);
					k += x;
				}
				printf("\n");
			}
			else printf("no one\n");
		}
		else if (argv[2][1] == 'p') {
			k = 0;
			for (i = 2; i <= sqrt(x); i++) {
				if (x % i == 0) {
					k = 1;
					break;
				}
			}
			k > 0 ? printf("Composite\n") : printf("Simple\n");
		}
		else if (argv[2][1] == 's') {
			k = x;
			i = 0;
			while (k > 0) {
				printf("%d", k % 10);
				k /= 10;
			}
			printf("\n");
		}
		else if (argv[2][1] == 'e') {
			if (x <= 10)
			{
				for (k = 1; k <= 10; k++) {
					for (i = 1; i <= x; i++) {
						
						printf("%d^%d =  %.0lf; ", k, i, pow(k, i));
					}
					printf("\n");
				}
			}
		}
		else if (argv[2][1] == 'a') {
			sam = 0;
			for (int i = 1; i <= x; i++) {
				sam += i;
			}
			printf("Sum: %.0lf\n", sam);
		}
		else if (argv[2][1] == 'f') {
			printf("Factorial: %.0lf\n", fact(x));
		}
		else printf("Error\n");
	}
}