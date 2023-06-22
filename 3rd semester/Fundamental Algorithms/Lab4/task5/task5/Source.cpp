#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "Tree.h"

int main() {
    char* locale = setlocale(LC_ALL, "");
    struct tnode* root, *tmp;
    tmp = (struct tnode*)malloc(sizeof(struct tnode));
    char word[BUFSIZ];
    char bufc[BUFSIZ];
    int buf;
    int flag = 0;
    int depth = 0;
    FILE* input_file, * output_file;
    if (!(input_file = fopen("my.txt", "r")) || !(output_file = fopen("out.txt", "w"))) {
        perror("Не удалось открыть файл");
        exit(-2);
    }
        
    root = NULL;
    while(!feof(input_file)){
        fscanf(input_file, "%s", word);
        if (isalpha(word[0]))
            root = addtree(root, word);
    }    
    fclose(input_file);
    treeprint(root);
    depth = getMaxDepth(root, depth);
    printf("Глубина дерева: %d\n", depth);

    tofile(root, output_file, flag);
    fclose(output_file);
    if (!(input_file = fopen("out.txt", "r"))) {
        perror("Не удалось открыть файл");
        exit(-3);
    }
    tmp = fromFile(input_file);
    treeprint(tmp);
    //printf("count = %d, word = %s\n", tmp->left->count, tmp->left->word);   
    //printf("count = %d, word = %s\n", tmp->right->count, tmp->right->word);
    while (1) {
        printf("Выбирете дейтвие:\n1 - поиск кол-ва повторений введенного слова\n2 - вывод первых n \
наиболее часто встречающихся слов в файле\n3 - поиск самого длинного слова и самого короткого\n0 - выход\nВаш выбор: ");
        flag = NULL;
        scanf("%d", &flag);
        switch (flag) {
        case 1:
            struct tnode* result;
            printf("Введите искомое слово: ");
            scanf("%s", word);
            result = search(root, word);
            if (result == 0)
                printf("Нет такого слова\n\n");
            else printf("Кол-во вхождений: %d\n\n", result->count);
            break;
        case 2:
            printf("Введите кол-во элементов которые нужно вывести в порядке убывания вхождений: ");
            scanf("%d", &buf);
            mostfrequent(root, buf);
            break;
        case 3:
            char* smallest = (char*)malloc(sizeof(char) * BUFSIZ);
            char* biggest = (char*)malloc(sizeof(char) * BUFSIZ);
            smallest = find_smallest(root); 
            biggest = find_biggest(root);
            printf("Наименьшее по длине слово: %s\nНаибольшее по длине слово: %s\n\n", smallest, biggest);
            free(smallest);
            free(biggest);
            break;
        /*default:
            printf("Введен неверный флаг!\n\n");
            break;*/
        }
        printf("Хотите еще раз воспользоваться доп опциями?\nДа/нет - 1/0\n");
        flag = NULL;
        scanf("%d", &flag);
        if (flag == 0) break;
    }

    freemem(root);;
    return 0;
}