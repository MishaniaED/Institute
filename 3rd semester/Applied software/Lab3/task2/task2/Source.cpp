#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct tnode {
	string field;           // ���� ������
	struct tnode* left;	    // ����� �������
	struct tnode* right;	// ������ �������
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
	if (tree != NULL) {						 //���� �� ���������� ������ ����
		cout << tree->field<<" ";			 //���������� ������ ������
		cout << counter << " ";
		counter++;
		treeprint(tree->left, counter);		 //����������� ������� ��� ������ ���������
		treeprint(tree->right, counter);	 //����������� ������� ��� ������� ���������
	}
}

struct tnode* addnode(string x, tnode* tree) {
	if (tree == NULL) {						 // ���� ������ ���, �� ��������� ������
		tree = new tnode;					 // ������ ��� ����
		tree->field = x;					 // ���� ������
		tree->left = NULL;
		tree->right = NULL;					 // ����� �������������� ��������
	}
	else  if (x.size() < tree->field.size()) // ������� ���������� ������ �������
		tree->left = addnode(x, tree->left);
	else									 // ������� ���������� ������� �������
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
	if (!fin.is_open()) {					// ���� ���� �� ������
		cout << "File can not be oppened!\n";
		exit(-1);
	}
	while (!fin.eof()) {
		fin >> s;
		root = addnode(s, root);
	}
	treeprint(root, counter);		// ����� �������� ��������� �� ����������� ������ ����� �� �������� ���������� ������� �� ������ ���������� ����
	find(root, &s1, &counter1);		// �-� ��� ������ ������ �������� ����� � ������� ��� ��� ����������� 
	cout << "\nThe longest word: " << s1 << "\nHow many times have we met: " << counter1;
	freemem(root);
	fin.close();
	return 0;
}