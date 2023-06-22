#include<iostream>
using namespace std;

int main() {
	int a = 10;
	auto f = [a]( int b) {return a + b; };
	cout << f(13);
	return 0;
}