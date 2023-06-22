#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

/****************part1****************/

template <class N>
struct Node{
	N data;
	Node<N>* next;
};

template <class S>
class Stack
{

private:
	int size = 0;
	Node<S>* top;

public:

	Stack(){
		top = NULL;
	}

	void insert(S x){
		Node<S>* tmp = new Node<S>;
		tmp->data = x;
		tmp->next = top;
		top = tmp;
		size++;
	}

	S remove(){
		Node<S>* tmp = new Node <S>;
		tmp = top;
		if (is_empty() == true) {
			top = NULL;
		}
		else top = top->next;
		size--;
		return tmp->data;
	}

	int get_size(){
		return size;
	}

	bool is_empty(){
		if (size == 0) return true;
		else		   return false;
	}
};

template < typename T >
double ariph(vector<T> vec, T number) {
	int sum_of_elements = 0;
	int counter = 0;
	double ariphmetical_mean = 0;
	for (int j = 0; j < vec.size(); j++) {
		if (vec[j] == number) {
			sum_of_elements += j + 1;
			counter++;
		}
	}
	ariphmetical_mean = sum_of_elements / counter;
	return ariphmetical_mean;
}


int main(){
	int i = 0, buf, N=1, flag=0, number;
	Stack <int> l;
	vector<int> vec;

	ifstream input_file("input.txt", ios_base::in);
	ofstream output_1("1.txt", ios_base::out | ios_base::trunc);
	ofstream output_2("2.txt", ios_base::out | ios_base::trunc);
	if (!input_file.is_open() || !output_1.is_open() || !output_2.is_open()) {
		cerr << "Can't open file!\n";
		exit(-1);
	}
	
	cout << "Enter the item you are looking for: ";
	cin >> number;

	while (!input_file.eof()){
		input_file >> buf;
		l.insert(buf);
		vec.push_back(buf);
		if (buf == number) flag = 1;
	}

	while (!l.is_empty()){
		buf = l.remove();
		if (buf%2 == 0) {
			output_1 << buf << ' ';
		}
		else output_2 << buf << ' ';	
	}

	if (flag == 0) cout << "There are no elements equal to the entered number!\n";
	else cout << "Ariphmetical mean: " << ariph(vec, number) << endl;
	cout << "\nChek result in files 1 and 2\n";
	input_file.close();
	output_1.close();
	output_2.close();
	return 0;
}