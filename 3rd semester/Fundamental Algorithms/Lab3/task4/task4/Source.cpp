#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

/******************************************************************************

4. Структура Message содержит следующие поля: id сообщения, текст сообщения и длина
сообщения в байтах. Программа предлагает пользователю ввести сообщение, после
чего происходит заполнение структуры и запись её в файл. Когда пользователь вводит
команду, текст которой передаётся как аргумент командной строки, ввод данных
завершается, и программа должна считать данные из файла в динамический массив
структур и вывести их на экран

*******************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

typedef struct Message {
	int ID;
	char* message;
	int bytes;
} Message, * PMessage;

int main(int argc, char* argv[]) {
	char buf[BUFSIZ], bufMessage[BUFSIZ], bytes_buf[20];
	Message m;
	PMessage pmessages = NULL;
	int messagescounter = 0, id = 0, i = 0, j = 0, k = 0, size = 1;
	FILE* output_file;
	int bytes;

	if (argc != 2) {
		perror("Invalid arguments");
		exit(-1);
	}

	if (!(output_file = fopen("out.txt", "w"))) {
		perror("'out.txt' file сan`t open");
		exit(-2);
	}

	printf("Start input message, \"%s\" to stop:\n", argv[1]);

	while (1) { // Для ввода используем одну структуру 'm' которая перезаписывается
		//scanf("%[^\n]s", buf);
		fgets(buf, sizeof(buf), stdin);
		strtok(buf, "\n");
		if (!strcmp(buf, argv[1])) // Проверка стоп слова
			break;

		m.ID = i + 1;
		m.bytes = strlen(buf) + 1;
		m.message = (char*)malloc(sizeof(char) * (strlen(buf) + 1)); // только строковые литералы получают нуль-конец (автоматически)
		strcpy(m.message, buf);
		m.message[strlen(buf)] = '\0';
		fprintf(output_file, "%d %s %d\n", m.ID, m.message, m.bytes);
		i++;
		free(m.message);
	}

	fclose(output_file);
	if (!(output_file = fopen("out.txt", "r"))) {
		perror("'out.txt' file сan`t open");
		exit(-3);
	}

	while (!feof(output_file)) {

		fscanf(output_file, "%d", &id);
		fgets(buf, sizeof(buf), output_file);

		bytes = 0;
		i = 0, j = 0, k = 0;
		while (buf[i] != '\n')
		{
			if (isdigit(buf[i]) == 0) {
				bufMessage[j] = buf[i];
				j++;
			}
			else {
				bytes_buf[k] = buf[i];
				k++;
			}
			i++;
		}
		i = 0;
		bufMessage[j] = '\0';

		/*printf("\nk = %d", k);
		printf("Bytes_buf: %s", bytes_buf);
		printf("\nBytes(before while): %d", bytes);*/

		while (i < k) // Сделать перевод строки в число
		{
			if (i >= 1)
				bytes *= 10;
			bytes += bytes_buf[i] - '0';
			i++;
			//printf("\nBytes(in while): %d", bytes);
		}
		//printf("\nBytes(after while): %d", bytes);

		//printf("%d%s%d", &id, bufMessage, &bytes);
		messagescounter++;
		if (messagescounter == size) {
			size *= 2;
			pmessages = (PMessage)realloc(pmessages, size * sizeof(Message));
		}
		//pmessages = (PMessage)realloc(pmessages, ++messagescounter * sizeof(Message)); // не эффективно
		pmessages[messagescounter - 1].ID = id;
		(pmessages + messagescounter - 1)->message = (char*)malloc(sizeof(char) * (strlen(bufMessage))); // Завершающий нуль
		strcpy(pmessages[messagescounter - 1].message, bufMessage);
		//printf("\nMessage: %s", pmessages[messagescounter - 1].message);
		//pmessages[messagescounter - 1].message[strlen(bufMessage)] = '\0';
		//printf("\nBytes(before): %d", bytes);
		pmessages[messagescounter - 1].bytes = bytes;
		//printf("\nBytes(after): %d", bytes);
		//printf("\nBytes(in_struct) %d", pmessages[messagescounter - 1].bytes);
		//printf("\nBytes(in_struct) %d", pmessages[0].bytes);
		//printf("\nbytes count = %d\n", pmessages[messagescounter - 1].bytes);

	}

	fclose(output_file);

	for (i = 0; i < messagescounter - 1; i++) {
		printf("\n%d: %s, bytes count = %d\n", pmessages[i].ID, pmessages[i].message, pmessages[i].bytes);
		//free(pmessages[i].message);
	}
	free(pmessages);

	return 0;
}