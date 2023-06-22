#include<iostream>
#include<forward_list>
#include<string>
using namespace std;

forward_list<string> search(forward_list<string>, string, string);

int main() {
	forward_list<string> flst = { "1","2","4","5" };
	string s1 = "-1", s2 = "3";
	flst = search(flst, s1, s2);
	auto curr = flst.begin();
	while (curr != flst.end()) {
		cout << (*curr);
		++curr;
	}
}

forward_list<string> search(forward_list<string> flst, string s1, string s2) {
	auto prev = flst.before_begin();
	int flag = 0;
	auto curr = flst.begin();
	while (curr != flst.end()) {
		if ((*curr) == s1) {
			flag = 1;
			curr = flst.insert_after(curr, s2);
		}
		++curr;
	}
	if (flag == 0) {
		curr = flst.begin();
		while (curr != flst.end()) {
			prev = curr;
			++curr;
		}
		prev = flst.insert_after(prev, s2);
	}
	return flst;
}