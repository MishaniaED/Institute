#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
using namespace std;

int main() {
	vector<int> vec;
	copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(vec));
	//copy(vec.begin(), vec.end(), vec_int);
	sort(vec.begin(), vec.end());
	for (auto it : vec) {
		cout << it << " ";
	}
	return 0;
}