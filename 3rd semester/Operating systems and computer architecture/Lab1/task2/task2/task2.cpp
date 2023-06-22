#include <iostream>
#include <string>
using namespace std;

int bracket(string s)
{
    int len = s.length();
    int a = 0, b = 0, c = 0;
    char last = ' ';
    for (int i = 0; i < len; i++) {
        if (s[i] == '(') {
            a++; last = '(';
        }
        else if (s[i] == '[') {
            b++; last = '[';
        }
        else if (s[i] == '{') {
            c++; last = '{';
        }
        else if (s[i] == ')') {
            a--;
            if (last == '[' || last == '{') return -1;
            last = ')';
        }
        else if (s[i] == ']') {
            b--;
            if (last == '(' || last == '{') return -1;
            last = ']';
        }
        else if (s[i] == '}') {
            c--;
            if (last == '(' || last == '[') return -1;
            last = '}';
        }
    }
    return a + b + c;
}

int main()
{
    string s;
    cin >> s;
    if (bracket(s) == 0) {
        cout << "Correct";
    }
    else cout << "Uncorrect";
    return 0;
}