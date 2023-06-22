#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<string> elimDups(vector<string>);
bool isShorter(const string, const string);

int main()
{
    vector<string> vec = {"b","a","aba","A","aa","AA A"};
    vec = elimDups(vec);
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    return 0;
}

bool isShorter(const string s1, const string s2) {
    return s1.size() < s2.size();
}

vector<string> elimDups(vector<string> vec) {
    stable_sort(vec.begin(), vec.end(), isShorter);
    //stable_sort(vec.begin(), vec.end());
    return vec;
}
