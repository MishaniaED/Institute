#include<iostream>
#include<vector>
#include<list>
using namespace std;
int main() {
	vector<int> vec = { 1,2,3,4,5,6 };
	list<int> list = { 1,2,3,4,5,6 }, cpy(list.size());
	cpy = list;
	int tmp;
	int size_vec = vec.size();
	
	if (size_vec == list.size()) {
		for (int i = 0; i < size_vec; i++) {
			tmp = cpy.front();
			if (vec[i] != tmp) {
				cout << "false";
				return 0;
			}
			cpy.pop_front();
		}
	}
	else { 
		cout << "false"; 
		return 0;
	}
	cout << "true";
	return 0;
}