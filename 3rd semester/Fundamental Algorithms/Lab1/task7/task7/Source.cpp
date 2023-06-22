#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>




int main() {
    FILE* input_file, * out_file;
    char arr[BUFSIZ], min_base = '0';
    int i;
    
    if (!(input_file = fopen("my.txt", "r"))|| !(out_file = fopen("out.txt", "w"))) {
        printf("file could't be opened\n");
        return -1;
    } 

    while (!feof(input_file)) {
        fscanf(input_file, "%s ", arr);
        for (i = 0; i <= strlen(arr); i++)
            arr[i] = toupper(arr[i]);  // обратный эффект tolower
        i = 0;
        while (arr[i] != '\0') {
            if (min_base < arr[i])
                min_base = arr[i];
            i++;
        }
        if (min_base <= '9')
            min_base = min_base + 1 - '0'; // делаем число из символа
        else
            min_base = min_base + 11 - 'A';

        fprintf(out_file, "%s %d %ld\n", arr, min_base, strtol(arr, NULL, min_base));
    }   // strtol - преобразует число в нужную с/с (min_base), в строке arr пропускаются пробелы 
        // NULL - указывает на неиспользованную часть строки

    fclose(input_file);
    fclose(out_file);
    return 0;
}

