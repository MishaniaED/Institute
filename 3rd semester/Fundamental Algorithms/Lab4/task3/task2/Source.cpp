#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>
#include "Queue.h"

void file_prc(Node** pq, char* file_name, int flag) {
	FILE* input_file;
	if (!(input_file = fopen(file_name, "r"))) {
		perror("File opening error\n");
		exit(-1);
	}
	char buf1[BUFSIZ], buf2[BUFSIZ], str[BUFSIZ], str1[BUFSIZ];
	char* buf3;
	fgets(buf1, BUFSIZ, input_file);
	strcpy(buf2, strtok(buf1, "\n"));
	strtok(buf1, " ");
	int i = 0, point = 0, prior;
	while (buf1[strlen(buf1) - i - 1] != '=') {
		point = strlen(buf1) - i - 1;
		i++;
	}
	i = 0;
	while (point != strlen(buf1)) {
		str[i] = buf1[point];
		point++;
		i++;
	}
	str[i] = '\0';
	point = 0, i = 0;
	while (buf2[strlen(buf2) - i - 1] != '=') {
		point = strlen(buf2) - i - 1;
		i++;
	}
	i = 0;
	while (point != strlen(buf2)) {
		str1[i] = buf2[point];
		point++;
		i++;
	}
	str1[i] = '\0';
	prior = atoi(str);
	if (flag == 0)
		*pq = newNode(str1, prior);
	else push(pq, str1, prior);
	
	while (fgets(buf1, BUFSIZ, input_file)) {
		strcpy(buf2, strtok(buf1, "\n"));
		strtok(buf1, " ");
		int i = 0, point = 0, prior;
		while (buf1[strlen(buf1) - i - 1] != '=') {
			point = strlen(buf1) - i - 1;
			i++;
		}
		i = 0;
		while (point != strlen(buf1)) {
			str[i] = buf1[point];
			point++;
			i++;
		}
		str[i] = '\0';
		point = 0, i = 0;
		while (buf2[strlen(buf2) - i - 1] != '=') {
			point = strlen(buf2) - i - 1;
			i++;
		}
		i = 0;
		while (point != strlen(buf2)) {
			str1[i] = buf2[point];
			point++;
			i++;
		}
		str1[i] = '\0';
		prior = atoi(str);
		push(pq, str1, prior);	
	}
}

int main()
{
	setlocale(LC_CTYPE, "rus");
	int i, flag = 0, choice;
	Node* pq;
	char str[BUFSIZ];
	printf("Вводите имена файлов (стоп слово - 'stop'):\nИмя файла: ");
	scanf("%s", str);
	while (strcmp(str, "stop")) {
		file_prc(&pq, str, flag);				// считываем строку из файла, парсим ее, заносим в очередь, так пока не кончится файл
		if (flag == 0) {
			flag = 1;
		}
		printf("\nИмя файла: ");
		scanf("%s", str);
	}
	
	while (1)
	{
		printf("Выбирите действие:\n1 - вывести все элементы очереди\n2 - добавить элемент в конец очереди\n3 - вставить с учетом приоритета\n4 - удалить элемент из очереди\n0 - заврешить");
		printf("\nВаш выбор: ");
		choice = NULL;
		scanf("%d", &choice);
		switch (choice) {
		case 0: 
			break;
		case 1:
			print(&pq);
			break;
		case 2: 
			int prior;
			char buff[BUFSIZ];
			printf("Введите приоритет: ");
			scanf("%d", &prior);
			printf("Введите текст: ");
			scanf("%s", buff);
			push_not_prior(&pq, buff, prior);
			print(&pq);
			break;
		case 3:
			int prior2;
			char buff9[BUFSIZ];
			printf("Введите приоритет: ");
			scanf("%d", &prior2);
			printf("Введите текст: ");
			scanf("%s", buff9);
			push(&pq, buff9, prior2);
			print(&pq);
			break;
		case 4: 
			pop(&pq);
			print(&pq);
			break;
		}

		if (choice == 0) {
			break;
		}
	}
	getchar();
	return 0;
}