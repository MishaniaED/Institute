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
    auto b = s.begin();
    int size;
    while (b != s.end())
    {
        
        if (*b == *(oldval.begin())) {
            size = oldval.length();
            auto it1 = b;
            auto it2 = oldval.begin();
            while (*it1 == *it2) { it1++, it2++, size--; if (it1 == s.end() || size == 0) break; }
            if (it2 == oldval.end()) // то есть когда нашли подстроку
            {
                b = s.erase(b, b + oldval.length());
                b = s.insert(b, newval.begin(), newval.end());
                b += newval.length();
            }
            else ++b;
        }
        else ++b;
    }
    return s;
}



