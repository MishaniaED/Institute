#include<iostream>
#include<vector>
using namespace std;
int main() {
	vector<int> vec1 = {1,2,3,4,5,6};
	vector<int> vec2 = {1,3,5,6,7,8};
	vec1 == vec2 ? cout << "true" : cout << "false";
	return 0;
}