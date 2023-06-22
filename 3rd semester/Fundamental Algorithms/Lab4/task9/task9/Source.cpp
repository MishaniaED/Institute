#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <locale>
#include "Stack.h"

/*-------------------------------*/
int Priority(char s)
{
    switch (s)
    {
    case '*':
    case '/':
        return 3;
    case '+':
    case '-':
        return 2;
    case '(':
        return 1;
    }
    return 0;
}

/*-------------------------------*/
typedef struct _tree{
    struct _tree* left; 
    struct _tree* right;
    char s;
}tree;
/*-------------------------------*/
tree* Leaf(char s){
    tree* temp = (tree*)malloc(sizeof(tree));
    if (!temp) return NULL;
    temp->left = temp->right = NULL;
    temp->s = s;
    return temp;
}

char checker(char s)
{
    switch (s)
    {
    case '+':
    case '-':
    case '/':
    case '*':
        return 1;
    }
    return 0;
}

int main()
{
    char word = NULL;

    setlocale(LC_ALL, "RUSSIAN");
    FILE* input_file, * output_file;
    if (!(input_file = fopen("my.txt", "r")) || !(output_file = fopen("out.txt", "w"))) {
        perror("Не удалось открыть файл");
        exit(-2);
    }

    while(!feof(input_file)){ // считываем информацию из файла
        fscanf(input_file, "%s", word);
        if (word == '\n')   continue;
        else if(checker(word)){} // устанавливаем корневое значение текущего узла равным оператору из этого токена. Добавляем новый узел на место правого потомка текущего и спускаемся вниз по правому поддереву.
        else if(word == '('){} // добавляем новый узел, как левого потомка текущего, и спускаемся к нему вниз.
        else if(word == ')'){} // перемещаемся к родителю текущего узла.
        else if(isalpha(word)){} //  устанавливаем корневое значение равным этой величине и возвращаемся к родителю
    }

    getchar();
    return 0;
}