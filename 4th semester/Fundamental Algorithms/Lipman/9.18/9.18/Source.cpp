#include<iostream>
#include<deque>
#include<string>
using namespace std;

int main() {
    string str;
    deque<string> dq;
    
    auto it = dq.begin();
    while (getline(cin, str))
    {
        dq.insert(dq.end(),str);
    }

    auto b = dq.begin();
    auto e = dq.end();
    while (b != e){
        cout << *b << "\n";
        ++b;
    }
	return 0;
}