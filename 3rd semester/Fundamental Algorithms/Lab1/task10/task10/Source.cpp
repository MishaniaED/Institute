#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<ctype.h>

void convert_number(int, int);

int main() {
    int base;
    int i = 0, j = 0;
    long int result = 0, result_max = 0;
    char str[BUFSIZ], number[BUFSIZ];

    // Инициализация системы и строк
    printf("Enter base: ");
    scanf("%d", &base);

    if (base < 2 || isalpha(base)) {
        printf("[ERROR]: Invalid base\n");
        return -1;
    }

    printf("Enter number in this system: ");
    while (strcmp(str, "stop")) {
        scanf("%s", str);
        if (strcmp(str, "stop")) {

            // Проверка ввода на ошибки
            for (i = 0; i < strlen(str); i++) {
                if (isalpha(str[i])) {
                    if (toupper(str[i]) - '7' > base) {
                        printf("[ERROR]: Invalid numbers\n");
                        return -2;
                    }
                }
                else if (isdigit(str[i])) {
                    if (str[i] - '0' + 1 > base) {
                        printf("[ERROR]: Invalid numbers\n");
                        return -2;
                    }
                }
            }

            // Запись числа
            for (i = 0; i < strlen(str); i++) {
                number[i] = (isdigit(str[i])) ? str[i] - '0' : toupper(str[i]) - 'A' + 10;
            }

            // Перевод в 10-ую с/с
            for (i = 0; i < strlen(str); i++) {
                result = result * base + number[i];
            }
            // Поиск максимального числа
            if (result > result_max)
                result_max = result;

            memset(number, 0, sizeof(number));
            result = 0;
            j++;
        }
    }

    printf("\nMax result(10 base) = %ld\n", result_max);

    convert_number(result_max, 9);
    convert_number(result_max, 18);
    convert_number(result_max, 27);
    convert_number(result_max, 36);

    return 0;
}

void convert_number(int num, int sys) {
    int i = 0, MAX, temp;
    char mass[BUFSIZ];

    temp = num;             //просто сохраняем для вывода
    while (num) {
        //printf("%d\n", (num % sys ));
        mass[i] = ((num % sys) >= 10) ? toupper(num % sys + 'W') : num % sys + '0';
        i++;
        num /= sys;
    }
    MAX = i;
    printf("%d(10) -> ", temp);
    for (i = MAX - 1; i >= 0; i--) {
        printf("%c", mass[i]);
    }
    printf("(%d base)\n", sys);
}