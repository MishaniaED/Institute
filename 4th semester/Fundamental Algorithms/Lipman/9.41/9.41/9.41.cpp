#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    vector<char> vec = {'H','e','l','l','o','w'};
    string s(vec.begin(), vec.end());
    cout << s;
}