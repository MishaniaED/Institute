#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<malloc.h>

struct  Employee {	
	int ID;
	char name[20]; // Указатель
	char surname[20];
	int salary;
};

void sotr1(int i, int counter, struct Employee* data_base) { // компаратор
	struct Employee tmp_struct;
	while (i < counter) { // Гномья сортировка
		if (i == 0 || data_base[i - 1].salary <= data_base[i].salary)
			i++;
		else {
			tmp_struct = data_base[i];
			data_base[i] = data_base[i - 1];
			data_base[i - 1] = tmp_struct;
			i--;
		}
	}
}

void sort2(int i, int counter, struct Employee* base) {
	struct Employee tmp_struct;
	while (i < counter) {
		if (i == 0 || base[i - 1].salary >= base[i].salary)
			i++;
		else {
			tmp_struct = base[i];
			base[i] = base[i - 1];
			base[i - 1] = tmp_struct;
			i--;
		}
	}
}



int main(int argc, char* argv[]) {

	struct Employee *base;
	FILE* input_file, * output_file;
	int i = 0, flag = 0, counter = 1;
	char check[BUFSIZ];

	// Ошибки
	if (argc != 3) {
		perror("[ERROR]: invalid number of arguments");
		exit(-1);
	}
	if (strcmp(argv[2], "-d") && strcmp(argv[2], "-a") && strcmp(argv[2], "/d") && strcmp(argv[2], "/a")) {
		perror("[ERROR]: There is no such key!\n"); // распасить
		exit(-2);
	}
	if (!(input_file = fopen(argv[1], "r"))) {
		fprintf(stderr, "[ERROR]: file '%s' not open\n", argv[1]);
		exit(-3);
	}
	if (!(output_file = fopen("out.txt", "w"))) {
		perror("[ERROR]: file out.txt not open\n");
		exit(-4);
	}
	
	while (!feof(input_file)) {  // Проверка файла на пустоту (вынести в ф-ю)
		check[i] = fgetc(input_file);
		if (check[i] != ' ' && check[i] != '\n') {
			flag = 1;
		}
		if (check[i] == '\n')
			counter++;
		i++;
	}
	if (flag == 0) {
		printf("File is empty!");
		fclose(input_file);
		fclose(output_file);
		return 0;
	}
	else rewind(input_file); // Ставит указатель на начало файла

	base = (struct Employee*)malloc(counter * sizeof(struct Employee));

	for (i = 0; i < counter; i++) { // Считывание данных из файла
		fscanf(input_file, "%d", &(base + i)->ID);
		fscanf(input_file, "%s", &(base + i)->name);
		fscanf(input_file, "%s", &(base + i)->surname);
		fscanf(input_file, "%d", &(base + i)->salary);
	}

	i = 0;

	if (!strcmp(argv[2], "-a") || !strcmp(argv[2], "/a")) 
		sotr1(i, counter, base);
	else sort2(i, counter, base);
		

	for (i = 0; i < counter; i++) {  // Запись в файл
		fprintf(output_file, "%d ", (base + i)->ID);
		fprintf(output_file, "%s ", (base + i)->name);
		fprintf(output_file, "%s ", (base + i)->surname);
		fprintf(output_file, "%d\n", (base + i)->salary);
	}

	free(base);

	fclose(input_file);
	fclose(output_file);

	return 0;
}