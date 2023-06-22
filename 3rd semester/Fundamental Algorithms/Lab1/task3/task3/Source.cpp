#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(int argc, char *argv[]) {

	FILE *input_file, *output_file;
	int str = 1, i = 0;
	char c, name[BUFSIZ];

	// Ошибки
	if (argv[1][1] == 'n' && argc != 4) {
		perror("Error");
		return -1;
	}
	if (argv[1][1] != 'n' && argc != 3) {
		perror("Error");
		return -1;
	}

	if (strcmp(argv[1], "-d") && strcmp(argv[1], "-i") && strcmp(argv[1], "-s") && strcmp(argv[1], "-a") &&
		strcmp(argv[1], "/d") && strcmp(argv[1], "/i") && strcmp(argv[1], "/s") && strcmp(argv[1], "/a") &&
		strcmp(argv[1], "-nd") && strcmp(argv[1], "-ni") && strcmp(argv[1], "-ns") && strcmp(argv[1], "-na") &&
		strcmp(argv[1], "/nd") && strcmp(argv[1], "/ni") && strcmp(argv[1], "/ns") && strcmp(argv[1], "/na")) {
		perror("ERROR: There is no such key!\n");
			return -1;
	}
	if (!(input_file = fopen(argv[2], "r"))) {
		perror("input_file not open\n");
			return -1;
	}
	if (argv[1][1] != 'n') {
		strcpy(name, "out");
		strcat(name, argv[2]);  // объединяет строки
		if (!(output_file = fopen(name, "w"))) {
			perror("output_file not open\n");
			return -1;
		}
	}
	else {
		if (!(output_file = fopen(argv[3], "w"))) {
			perror("output_file not open\n");
			return -1;
		}
	}
	// Work with files

	if (!strcmp(argv[1], "-d") || !strcmp(argv[1], "/d") || !strcmp(argv[1], "-nd") || !strcmp(argv[1], "/nd")) {
		while ((c = fgetc(input_file)) != EOF) {
			if (!isdigit(c)) fprintf(output_file, "%c", c);
		}
	}
	else if (!strcmp(argv[1], "-i") || !strcmp(argv[1], "/i") || !strcmp(argv[1], "-ni") || !strcmp(argv[1], "/ni")) {
		while ((c = fgetc(input_file)) != EOF) {
			if (isalpha(c)) i++;
			if (c == '\n') {
				fprintf(output_file, "str №%d have %d letters\n", str, i);
				str++;
				i = 0;
			} 
		}
		fprintf(output_file, "str №%d have %d letters", str, i);
	}
	else if (!strcmp(argv[1], "-s") || !strcmp(argv[1], "/s") || !strcmp(argv[1], "-ns") || !strcmp(argv[1], "/ns")) {
		while ((c = fgetc(input_file)) != EOF) {
			if (!isalpha(c) && !isdigit(c) && c != ' ')	i++;
			if (c == '\n') {
				fprintf(output_file, "str №%d have %d symbols\n", str, i);
				str++;
				i = 0;
			}
		}
		fprintf(output_file, "str №%d have %d symbols", str, i);
	}
	else if (!strcmp(argv[1], "-a") || !strcmp(argv[1], "/a") || !strcmp(argv[1], "-na") || !strcmp(argv[1], "/na")) {
		while ((c = fgetc(input_file)) != EOF) {
			if (!isdigit(c)) fprintf(output_file, "%d", (int)(c));	
			else fprintf(output_file, "%c", c);
		}
	}
	fclose(input_file);
	fclose(output_file);
	return 0;
}