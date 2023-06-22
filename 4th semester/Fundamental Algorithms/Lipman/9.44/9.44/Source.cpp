#include <iostream>
#include <string>
using namespace std;

string repl(string, string, string);

int main()
{
    string s = "tho, thru, tho", oldval = "tho", newval = "thought";
    s = repl(s, oldval, newval);
    cout << s;
    return 0;
}

string repl(string s, string oldval, string newval) {
    int i = s.find(oldval);
    if (i == string::npos) {
        return s;
    }
    while (i != string::npos) {
        s.replace(i, oldval.size(), newval);
        i++;
        i = s.find(oldval, i);
    }
    return s;
}
