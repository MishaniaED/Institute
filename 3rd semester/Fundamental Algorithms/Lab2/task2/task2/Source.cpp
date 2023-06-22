#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
	// TODO: Сделать проверку на пустой файл
int main() {
	int mass[128], new_mass[128], i = 0, flag=0;
	char a, check[BUFSIZ];
	FILE* input_file;
	if ((input_file = fopen("out.txt", "r")) == NULL) {
		printf("input file could not be opened\n"); // fprintf stde
		exit(-1);
	}
	else {
		while (!feof(input_file)) {
			check[i] = fgetc(input_file);
			if (isdigit(check[i])) {
				flag = 1;
				break;
			}
			i++;
		}
		i = 0;
		if (flag == 0) {
			printf("File is empty!");
			fclose(input_file);
			return 0;
		}
		else rewind(input_file); //устанавливает указатель на начало файла
		/*if ((check = fgetc(input_file)) == EOF) {
			printf("File is empty!"); // посимвольно пройтись по файлу

			fclose(input_file);
			return -2;
		}
		else rewind(input_file);*/
		/*fseek(input_file, 0, SEEK_END);
		long pos = ftell(input_file); //Функция ftell() возвращает текущее значение указателя положения в файле
		if (pos > 0)
			// файл непустой.
			rewind(input_file); 
		else {
			printf("File is empty!");
			return -2;
		} */
			
		while (!feof(input_file)) {
			fscanf(input_file, "%d", &mass[i]);
			printf("%d ", mass[i]);
			i++;
		}
		fclose(input_file);
		printf("\nDo you want to rewrite mass whith numbers standing in an odd position or even number?\n");
		printf("Enter key 1 or 2 respectively: ");
		scanf("%c", &a);
		if (a == '1') {
			if ((input_file = fopen("out.txt", "w")) == NULL) {
				printf("file could not be opened\n");
				exit(-2);
			}
			for (int j = 0; j < i; j++) {
				if ((j + 1) % 2 == 1) {
					new_mass[j] = mass[j];
					fprintf(input_file, "%d ", new_mass[j]);
				}
			}
			fclose(input_file);
		}
		else if (a == '2') {
			if ((input_file = fopen("out.txt", "w")) == NULL) {
				printf("file could not be opened\n");
				exit(-3);
			}
			for (int j = 0; j < i; j++) {
				if (mass[j] % 2 == 0) {
					new_mass[j] = mass[j];
					fprintf(input_file, "%d ", new_mass[j]);
				}
			}
			fclose(input_file);
		}
		else {
			printf("wrong key");
			return -1;
		}
	}
	return 0;
}