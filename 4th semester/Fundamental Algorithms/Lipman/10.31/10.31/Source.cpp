#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
using namespace std;

int main() {
	vector<int> vec;
	copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(vec));
	sort(vec.begin(), vec.end());
	unique_copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
	return 0;
}