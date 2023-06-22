#include<iostream>
#include<vector>
#include<list>
#include<forward_list>
#include<deque>
#include<algorithm>
#include<iterator>
using namespace std;

int main() {
	vector<int> vec = { 1,2,3,4,5,6,7,8,9 };
	list<int> ls;
	auto b1 = ls.begin();
	forward_list<int> frls;
	auto b2 = frls.begin();
	deque<int> dq;
	auto b3 = dq.begin();
	copy(vec.begin(), vec.end(), b1);
	copy(vec.begin(), vec.end(), b2);
	copy(vec.begin(), vec.end(), b3);
	front_inserter(ls);
	front_inserter(ls);
	front_inserter(ls);
	cout << "list:\n";
	for (int i : ls)
		cout << i << ' ';
	cout << "\nforward_list:\n";
	for (int i : frls)
		cout << i << ' ';
	cout << "\ndeque:\n";
	for (int i : dq)
		cout << i << ' ';

	return 0;
}