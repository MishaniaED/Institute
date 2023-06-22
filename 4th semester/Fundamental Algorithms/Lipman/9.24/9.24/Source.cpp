#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<int> vec = {};
	cout << vec.front() << "\n";
	cout << vec.at(0) << "\n";
	auto iter = vec.begin();
	cout << (*iter)<<"\n";
	cout << vec[0];
	return 0;
}