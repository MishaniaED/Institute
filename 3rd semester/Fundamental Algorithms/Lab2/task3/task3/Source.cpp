#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int	flag_l(char* str)
{
	int n = strlen(str);
	printf("%d\n", n);
	return 0;
}

int	flag_r(char* str)
{
	for (int i = 0; i < strlen(str) / 2; ++i)
	{
		char t = str[i];
		str[i] = str[strlen(str) - i - 1];
		str[strlen(str) - i - 1] = t;
	}
	printf("%s\n", str);
	return 0;
}

int flag_u(char* str)
{
	int i = 0;
	int size = strlen(str);
	for (size; size > 0; size--) {
		if (i % 2 == 0 && isalpha(str[i]))
		{
			str[i] = toupper(str[i]);
		}
		i++;
	}
	printf("%s", str);
	return 0;
}

int	flag_n(char* str)
{
	int i;
	int j = 0;

	for (i = 0; str[i] != '\0'; i++) {
		if (isdigit(str[i]))
		{
			char t1 = str[j];
			str[j] = str[i];
			str[i] = t1;
			j++;
		}
	}
	i = j;
	for (i; str[i] != '\0'; i++) {
		if (isalpha(str[i]))
		{
			char t2 = str[j];
			str[j] = str[i];
			str[i] = t2;
			j++;
		}
	}
	printf("%s\n", str);
	return 0;
}

int	flag_c(char* str1, char* str2)
{
	int len1 = strlen(str1);
	int len2 = strlen(str2);

	char* result = malloc(len1 + len2 + 1);
	result[len1 + len2 + 1] = '\0';
	if (!result) {
		printf("malloc() failed\n");
		return NULL;
	}

	memcpy(result, str1, len1);
	memcpy(result + len1, str2, len2 + 1);

	printf("%s\n", result);
	return 0;
}


int	main(int argc, char* argv[])
{
	if (argc == 3 || argc == 4)
	{
		if (!strcmp(argv[2], "-l"))
			flag_l(argv[1]);
		else if (!strcmp(argv[2], "-r"))
			flag_r(argv[1]);
		else if (!strcmp(argv[2], "-u"))
			flag_u(argv[1]);
		else if (!strcmp(argv[2], "-n"))
			flag_n(argv[1]);
		else if (!strcmp(argv[2], "-c"))
			if (argc == 4)
				flag_c(argv[1], argv[3]);
			else printf("Not enough arguments");
		else
			printf("Argument not found\n");	
	}
	else
		printf("Wrong string\n");
	return 0;
}