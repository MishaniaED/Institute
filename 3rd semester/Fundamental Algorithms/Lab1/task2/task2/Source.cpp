#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


int main(int argc, char* argv[]) {
	double a, b, c;
	long double x1, x2;
	int x, y, i=0, j=0;
	// Ошибки
	if (argc < 3) {
		printf("[ERROR_1]: Input error(no keys or numbers)\n");
		return 1;
	}

	if (strcmp(argv[1], "-q") && strcmp(argv[1], "-m") && strcmp(argv[1], "-t") &&
		strcmp(argv[1], "/q") && strcmp(argv[1], "/m") && strcmp(argv[1], "/t")) {
		printf("[ERROR_2]: Input error(invalid keys)\n");
		return 1;
	}

	for (i = 2; i < argc; i++) {
		for (j = 0; j < strlen(argv[i]); j++) {
			if ((argv[i][j] < 48 || argv[i][j] > 57) && argv[i][0] != '-' && argv[i][j] != '.') {
				printf("[ERROR_3]: Wrong number input\n");
				return 1;
			}
		}
	}

	for (i = 2; i < argc; i++) {
		if (strlen(argv[i]) > 1 && argv[i][0] == '0' && argv[i][1] != '.') {
			printf("[ERROR_4]: Wrong number input(starting with 0)\n");
			return 1;
		}
	}

	if (*argv[1] == '-' || *argv[1] == '/') {
		if (argv[1][1] == 'q')
		{
			a = atoi(argv[2]);
			b = atoi(argv[3]);
			c = atoi(argv[4]);
			if (b * b - 4 * a * c >= 0) {
				x1 = ((-b) + sqrt(b * b - 4 * a * c)) / 2 * a;
				x2 = ((-b) - sqrt(b * b - 4 * a * c)) / 2 * a;
				printf("\nx1 = %.2lf, x2 = %.2lf\n", x1, x2);
			}
			else printf("D < 0\n");
		}
		else if (argv[1][1] == 'm')
		{
			x = atoi(argv[2]);
			y = atoi(argv[3]);
			if (x == 0) {
				printf("Error: x = 0");
							}
			else if (y % x == 0) printf("Yes\n");
			else printf("No\n");
		}
		else if (argv[1][1] == 't')
		{
			a = atoi(argv[2]);
			b = atoi(argv[3]);
			c = atoi(argv[4]);
			if (a * a + b * b == c * c || a * a + c * c == b * b || b * b + c * c == a * a) printf("Yes\n");
			else printf("No\n");
		}
	}
}
