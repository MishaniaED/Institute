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
        perror("�� ������� ������� ����");
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
    printf("������� ������: %d\n", depth);

    tofile(root, output_file, flag);
    fclose(output_file);
    if (!(input_file = fopen("out.txt", "r"))) {
        perror("�� ������� ������� ����");
        exit(-3);
    }
    tmp = fromFile(input_file);
    treeprint(tmp);
    //printf("count = %d, word = %s\n", tmp->left->count, tmp->left->word);   
    //printf("count = %d, word = %s\n", tmp->right->count, tmp->right->word);
    while (1) {
        printf("�������� �������:\n1 - ����� ���-�� ���������� ���������� �����\n2 - ����� ������ n \
�������� ����� ������������� ���� � �����\n3 - ����� ������ �������� ����� � ������ ���������\n0 - �����\n��� �����: ");
        flag = NULL;
        scanf("%d", &flag);
        switch (flag) {
        case 1:
            struct tnode* result;
            printf("������� ������� �����: ");
            scanf("%s", word);
            result = search(root, word);
            if (result == 0)
                printf("��� ������ �����\n\n");
            else printf("���-�� ���������: %d\n\n", result->count);
            break;
        case 2:
            printf("������� ���-�� ��������� ������� ����� ������� � ������� �������� ���������: ");
            scanf("%d", &buf);
            mostfrequent(root, buf);
            break;
        case 3:
            char* smallest = (char*)malloc(sizeof(char) * BUFSIZ);
            char* biggest = (char*)malloc(sizeof(char) * BUFSIZ);
            smallest = find_smallest(root); 
            biggest = find_biggest(root);
            printf("���������� �� ����� �����: %s\n���������� �� ����� �����: %s\n\n", smallest, biggest);
            free(smallest);
            free(biggest);
            break;
        /*default:
            printf("������ �������� ����!\n\n");
            break;*/
        }
        printf("������ ��� ��� ��������������� ��� �������?\n��/��� - 1/0\n");
        flag = NULL;
        scanf("%d", &flag);
        if (flag == 0) break;
    }

    freemem(root);;
    return 0;
}