#include <iostream>
#include <list>
#include <vector>
using namespace std;
	
int main() {
	int ia[] = { 0,1,1,2,3,5,8,13,21,55,89 };
	vector<int> vec;
	list<int> lis;
	for (int i = 0; i < 11; i++) {
		vec.push_back(ia[i]);
		lis.push_back(ia[i]);
	}
	auto begin = vec.begin();

	while(begin != vec.end()) {
		if ((*begin) % 2 == 0) begin = vec.erase(begin); 
		else {
			cout << (*begin);
			++begin;
		}
	}
	cout << "\n";
	auto begin1 = lis.begin();

	while (begin1 != lis.end()) {
		if ((*begin1) % 2 != 0) begin1 = lis.erase(begin1);
		else {
			cout << (*begin1);
			++begin1;
		}
	}
	
	return 0;
}