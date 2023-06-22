#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

typedef struct tree_leaf {
	char value;
    tree_leaf* parent;
	tree_leaf* left;
	tree_leaf* right;
} tree_leaf;

tree_leaf* addnode(int x, tree_leaf* tree, tree_leaf* parent) {
    tree_leaf *parent = NULL;
    if (tree == NULL) { // ≈сли дерева нет, то формируем корень
        tree = (tree_leaf*)malloc(sizeof(tree_leaf)); // пам€ть под узел
        tree->value = x;   // поле данных
        tree->left = NULL;
        tree->parent = parent;
        tree->right = NULL; // ветви инициализируем пустотой
    }
    else  if (x < tree->value) {   // условие добавление левого потомка
        parent = tree;
        tree->left = addnode(x, tree->left, parent);
    }
    else {   // условие добавление правого потомка
        parent = tree;
        tree->right = addnode(x, tree->right, parent);
    }
    return(tree);
}

// подкоректировать услови€ добавлени€ в праввое и левое поддеревь€

// сделать ф-ю распечатки в файл

// смотреть на сайте: http://aliev.me/runestone/Trees/ParseTree.html