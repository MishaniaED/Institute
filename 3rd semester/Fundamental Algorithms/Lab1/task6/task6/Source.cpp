#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
    int i = 1;
    char c;
    FILE* input_file, * output_file;
    // Ошибки
    if (argc != 2) {
        printf("[ERROR]: Not enough or too many arguments\n");
        return -1;
    }
    if (!(input_file = fopen(argv[1], "r")) || !(output_file = fopen("out.txt", "w"))) {
        printf("[ERROR]: Can`t open one of file\n");
        return -1;
    }
    

    // Work with files
    input_file = fopen(argv[1], "r");
    output_file = fopen("out.txt", "w");

    while ((c = fgetc(input_file)) != EOF) {
        if (!isalpha(c) && !isdigit(c)) {  // isalpha - возвращает не нулевое значение если его аргумент 
            i++;                           // является буквой (Заглавной или строчной), иначе 0
            fprintf(output_file, "%c", c); // isdigit - возвращает ненулевое значение если аргумент является
        }                                  // цифрой от 0 до 9
        
        else {
            if (i % 2 == 0 && isalpha(c)) {
                c = tolower(c);
            }
            if (i % 5 == 0) {
                fprintf(output_file, "%d", c);
                continue;
            }
            fprintf(output_file, "%c", c);
        }
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}
