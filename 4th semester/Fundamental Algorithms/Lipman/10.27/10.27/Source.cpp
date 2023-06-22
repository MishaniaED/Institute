#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
using namespace std;

int main() {
	vector<int> vec = { 1,2,3,4,5,1,3 };
	list<int> ls(vec.size());
	auto b = vec.begin();
	auto e = vec.end();
	auto el = ls.begin();
	sort(b, e);
	unique_copy(b, e, el);
	el = ls.begin();
	for (auto it = ls.begin(); it != ls.end(); ++it)
		cout << *it << " ";
	return 0;
}