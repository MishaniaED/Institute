#include <iostream>
#include <list>
#include <string>
using namespace std;
int main() {
	string s;
	list<string> l(5);
	cout << "Enter 5 strings of deque:\n";
	auto b = l.begin();
	auto e = l.end();
	while (b != e) 
	{
		getline(cin, s);
		*b = s;
		++b;
	}
	b = l.begin();
	while (b != e) {
		cout << (*b) << "\n";
		++b;
	}
	return 0;
}

/*int main() {
	string s;
	deque<string> q(5); //= {"haahahhaahhadidioadalsdkla", "lol", "hihi"};
	auto b = q.begin();
	//auto e = q.end();

	for (auto& i : q) {
		getline(cin, s);
	}
	return 0;
}*/

/*int main() {
	string s;
	list<string> l;
	getline(cin, s);
	if(s == "end") return 0;
	l.push_back(s);
	auto b = l.begin();
	while (true) {
		getline(cin, s);
		if (s == "end") break;
		l.emplace_back(s);
	}
	auto e = l.end();
	while (b != e) {
		cout << (*b) << "\n";
		++b;
	}
	return 0;
}*/