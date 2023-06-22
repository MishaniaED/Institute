#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* add0(char*, int);
char* rm0(char*);
char* add(char*, char*, int);
char* sum(int, int, ...);


int main()
{
    printf("result: %s\n", sum(2, 10, "99999999999999999999999999", "100000000001"));
    return 0;
}

char* add0(char* number, int len) // добовляем ведущие нули к меньшему из чисел
{
    int i;
    if (strlen(number) > len){
        char* d = (char*)malloc((sizeof(char) * strlen(number) + 1));
        strcpy(d + 1, number);
        d[0] = '0';
        return d;
        free(d);
    }
    else {
        char* d = (char*)malloc((sizeof(char) * len + 1));
        for (i = 0; i < len - strlen(number) + 1; ++i)
            d[i] = '0';
        strcpy(d + len - strlen(number) + 1, number);
        return d;
        free(d);
    }
}

char* rm0(char* withzero) // удаляем ведущие нули
{
    if (withzero[0] != '0')
        return withzero;

    char* withoutzero = (char*)malloc(sizeof(char) * strlen(withzero) + 1);
    strcpy(withoutzero, withzero + 1);
    return(withoutzero);
}

char* add(char* firstnum, char* secondnum, int base)
{
    int i, k = 0;
    char* res = (char*)malloc((sizeof(char)) * (strlen(firstnum) + strlen(secondnum)));
    res = res + strlen(res);

    firstnum = add0(firstnum, strlen(secondnum));
    secondnum = add0(secondnum, strlen(firstnum));

    for (i = 0; i < strlen(firstnum); ++i){
        char num1 = firstnum[strlen(firstnum) - i - 1];
        char num2 = secondnum[strlen(secondnum) - i - 1];
        int result = k + (isdigit(num1) ? num1 - '0' : toupper(num1) - 'A' + 10) + (isdigit(num2) ? num2 - '0' : toupper(num2) - 'A' + 10);
        *(--res) = ((result % base > 9) ? (result % base) - 10 + 'A' : (result % base) + '0');
        k = result / base;
    }
    return (rm0(res));
}

char* sum(int count, int base, ...)
{
    int i;
    char* s = "0", * curnum;
    va_list args;
    va_start(args, base);
    if (base < 2 || base > 36)
    {
        printf("Wrong count system!");
        exit(-1);
    }
    
    for (i = 0; i < count; i++) // Сделать ф-ю проверяющую на правильность переданного числа
    {
        curnum = va_arg(args, char*);
        int k = 0, flag=1;
        //printf("strlen of curnum: %d\n", strlen(curnum));
        while (k<strlen(curnum)-1){
            if (!(isdigit(curnum[k]) || isalpha(curnum[k])) || (isdigit(curnum[k]) && (curnum[k] - '0' >= base))\
            || (isalpha(curnum[k]) && (curnum[k] - 'A' + 10 >= base))){
                 printf("Invalid number %s!\n", curnum);
                 flag = 0;
             }
            k++;
        }
        if (flag == 1)
            s = add(s, curnum, base);
        flag = 1;
    }
    va_end(args);
    return rm0(s);
}