#include <iostream>
#include <list>
#include <deque>
using namespace std;
int main() {
	list<int> l = {0,1,2,3,4,5,6};
	int tmp;
	deque<int> chet, nechet;
	auto b = l.begin();
	auto e = l.end();
	while (b != e)
	{
		if ((*b) % 2 == 0) chet.push_back(*b);
		else nechet.push_back(*b);
		++b;
	}
	auto b1 = chet.begin();
	auto e1 = chet.end();
	while (b1 != e1)
	{
		cout << (*b1)<< " ";
		++b1;
	}
	cout << "\n";
	b1 = nechet.begin();
	e1 = nechet.end();
	while (b1 != e1)
	{
		cout << (*b1)<<" ";
		++b1;
	}
	return 0;
}