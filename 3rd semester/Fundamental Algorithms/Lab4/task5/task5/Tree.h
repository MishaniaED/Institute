#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct word {
    char field[BUFSIZ];
    int count;
}word;

struct tnode {                   // узел дерева
    char* word;                  // указатель на строку (слово)
    int count;                   // число вхождений
    int flag = 0;
    struct tnode* left;          // левый потомок
    struct tnode* right;         // правый потомок
};

// Функция добавления узла к дереву
struct tnode* addtree(struct tnode* p, char* w) {
    int cond;
    if (p == NULL) {
        p = (struct tnode*)malloc(sizeof(struct tnode));
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if (strlen(w) < strlen(p->word))
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

// Функция удаления поддерева
void freemem(tnode* tree) {
    if (tree != NULL) {
        freemem(tree->left);
        freemem(tree->right);
        free(tree);
    }
}

// Функция вывода дерева
void treeprint(struct tnode* p) {
    if (p != NULL /*&& strlen(p->word) < 511)*/) {
        printf("%d %s\n", p->count, p->word);
        if (p->left != NULL)
            treeprint(p->left);
        if (p->right != NULL) 
            treeprint(p->right);
    }
}

// Функция поиска слова
struct tnode* search(struct tnode* p, char* word)                         //searching
{
    if ((p == NULL) || strcmp(p->word, word) == 0)         //if tree is empty or root is the answer
        return p;
    if (strcmp(word, p->word) > 0 && p->left != NULL)                            //if words are different and key is bigger
        return search(p->left, word);                         //search in it left subtree
    else if (p->right != NULL) return search(p->right, word);  
    //search in it right subtree
}

// Функция поиска самого длинного слова
char* find_biggest(struct tnode* p) {
    if (p->right != NULL) {         //Пока не встретится пустой узел
        find_biggest(p->right);
    }
    else return p->word;
}

// Функция поиска самого короткого слова
char* find_smallest(struct tnode* p) {
    if (p->left != NULL) {         //Пока не встретится пустой узел
        find_smallest(p->left);
    }
    else return p->word;
}

// Получение числа потомков под корнем
int getsize(struct tnode* root) {
    if (root == NULL)
        return 0;
    else
        return getsize(root->right) + getsize(root->left) + 1;
}

// копирование дерева в массив
word* copytoarray(struct tnode* root, word* array) { 
    if (root == NULL)
        return array;
    array = copytoarray(root->left, array);
    strcpy(array->field, root->word);
    array->count = root->count;
    return copytoarray(root->right, array + 1);
}

// компаратор для сортировку по вхождениям
int comparebycount(const void* a, const void* b) {
    word* a1 = (word*)a;
    word* b1 = (word*)b;
    return b1->count - a1->count;
}

// поиск n самых часто встречаемых слов
void mostfrequent(struct tnode* p, int n) {
    word* array = (word*)malloc(sizeof(word) * getsize(p));
    copytoarray(p, array);
    qsort(array, getsize(p), sizeof(word), comparebycount);
    int i;
    for (i = 0; i < n; i++) {
        printf("%s:  ", array[i].field);
        printf("%d\n", array[i].count);
    }
    free(array);
}

// поиск глубины дерева
int getMaxDepth(struct tnode* p, int depth)
{
    if (p == NULL)
        return depth;
    else if (getMaxDepth(p->left, depth + 1) > getMaxDepth(p->right, depth + 1))
        return getMaxDepth(p->left, depth + 1);
    else return getMaxDepth(p->right, depth + 1);
}

// запись в файл
void tofile(struct tnode* root, FILE* outfile, int flag) {
   /* if (root == NULL) {
        //fprintf(outfile, "\n");
        return;
    }*/
    //fprintf(outfile, "%s %d %d\n", root->word, root->count, flag);
    if (root->left != NULL && root->right != NULL) {
        flag = 3;
        fprintf(outfile, "%s %d %d\n", root->word, root->count, flag);
        tofile(root->left, outfile, flag);
        tofile(root->right, outfile, flag);
    }
    else if (root->left == NULL && root->right != NULL) {
        flag = 2;
        fprintf(outfile, "%s %d %d\n", root->word, root->count, flag);
        tofile(root->right, outfile, flag);
    }
    else if (root->left != NULL && root->right == NULL) {
        flag = 1;
        fprintf(outfile, "%s %d %d\n", root->word, root->count, flag);
        tofile(root->left, outfile, flag);
    }
    else if (root->left == NULL && root->right == NULL) {
        flag = 0;
        fprintf(outfile, "%s %d %d\n", root->word, root->count, flag);
    }
    else return;
}

// чтение из файла
struct tnode* fromFile(FILE* infile)
{
    int flag;
    char    line[BUFSIZ];
    struct tnode* newNode = NULL;
    fgets(line, sizeof(line), infile);
    if (strcmp(line, "\n") == 0 || strlen(line) > 511)
        return (NULL);
    strtok(line, "\n"); 
    
    newNode = (struct tnode*)malloc(sizeof(tnode));
    newNode->word = (char*)malloc(sizeof(char)*BUFSIZ);
    strcpy(newNode->word, strtok(line, " "));
    newNode->count = atoi(strtok(NULL, " "));
    flag = atoi(strtok(NULL, " "));
    //printf("count = %d, word = %s", newNode->left->count, newNode->left->word);
    //if (newNode->left != NULL)

    if (flag == 3) {//newNode->left != NULL && newNode->right != NULL
        newNode->left = fromFile(infile);
        newNode->right = fromFile(infile);
    }
    else if (flag == 2 && newNode->right != NULL) {//newNode->left == NULL && newNode->right != NULL 
        newNode->right = fromFile(infile);
        newNode->left = NULL;
    }
    else if (flag == 1 && newNode->left != NULL) {// && newNode->right == NULL
        newNode->left = fromFile(infile);
        newNode->right = NULL;
    }
    else if (flag == 0) {
        newNode->left = NULL;
        newNode->right = NULL;
    }
    //else return;

    //newNode->left = fromFile(infile);
    //if(newNode->right != NULL)
    //newNode->right = fromFile(infile);
    return newNode;
}