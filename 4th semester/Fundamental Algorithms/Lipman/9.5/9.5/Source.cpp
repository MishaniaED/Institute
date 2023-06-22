#include <iostream>
#include <vector>

using namespace std;

vector<int>::iterator search(vector<int>::iterator begin, vector<int>::iterator end, int x);


int main()
{
    int x;
    vector<int> vec = { 1,2,3,4,5,6 };
    auto b = vec.begin();
    auto e = vec.end();
    cout << "Enter the number you are looking for: x = ";
    cin >> x;
    auto result = search(b, e, x);
    if (result != e) cout << "Value found";
    else cout << "Value not found";
    cin >> x;
    return 0;
}

vector<int>::iterator search(vector<int>::iterator begin, vector<int>::iterator end, int x) {
    while (begin != end) {
        if (*begin == x) return begin;
        ++begin;
    }
    return end;
}
