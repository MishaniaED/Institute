#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct tnode {
	string field;           // поле данных
	struct tnode* left;	    // левый потомок
	struct tnode* right;	// правый потомок
};

void find(tnode* tree, string* s1, int* counter1) {
	if (tree != NULL) {
	   if (*(s1) == tree->field)  
		*(counter1) += 1;
		else {
			*(counter1) = 1;
			*(s1) = tree->field;
		}
		find(tree->right, s1, counter1);
	}	
}

void treeprint(tnode* tree, int counter) {
	if (tree != NULL) {						 //Пока не встретится пустой узел
		cout << tree->field<<" ";			 //Отображаем корень дерева
		cout << counter << " ";
		counter++;
		treeprint(tree->left, counter);		 //Рекурсивная функция для левого поддерева
		treeprint(tree->right, counter);	 //Рекурсивная функция для правого поддерева
	}
}

struct tnode* addnode(string x, tnode* tree) {
	if (tree == NULL) {						 // Если дерева нет, то формируем корень
		tree = new tnode;					 // память под узел
		tree->field = x;					 // поле данных
		tree->left = NULL;
		tree->right = NULL;					 // ветви инициализируем пустотой
	}
	else  if (x.size() < tree->field.size()) // условие добавление левого потомка
		tree->left = addnode(x, tree->left);
	else									 // условие добавление правого потомка
		tree->right = addnode(x, tree->right);
	return(tree);
}

void freemem(tnode* tree) {
	if (tree != NULL) {
		freemem(tree->left);
		freemem(tree->right);
		delete tree;
	}
}

int main() {
	struct tnode *root;
	root = NULL;
	string s, s1="0";
	int counter = 0, counter1 = 0;
	ifstream fin("my.txt");
	if (!fin.is_open()) {					// если файл не открыт
		cout << "File can not be oppened!\n";
		exit(-1);
	}
	while (!fin.eof()) {
		fin >> s;
		root = addnode(s, root);
	}
	treeprint(root, counter);		// Чтобы понимать правильно ли построилось дерево рядом со значение печатается уровень на котром находиться узел
	find(root, &s1, &counter1);		// Ф-я для поиска самого длинного слова и сколько раз оно встретилось 
	cout << "\nThe longest word: " << s1 << "\nHow many times have we met: " << counter1;
	freemem(root);
	fin.close();
	return 0;
}