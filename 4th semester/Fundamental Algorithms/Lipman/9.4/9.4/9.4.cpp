#include <iostream>
#include <vector>

using namespace std;

bool search(vector<int>::iterator begin, vector<int>::iterator end, int x);

int main()
{
    int x;
    cout << "Enter the number you are looking for: x = ";
    cin >> x;
    vector<int> vec = {1,2,3,4,5,6};
    auto b = vec.begin();
    auto e = vec.end();
    search(b, e, x) ? cout << "Value found": cout << "Value not found";
    return 0;

}

bool search(vector<int>::iterator begin, vector<int>::iterator end, int x) {
    while (begin != end) {
        if (*begin == x) return true;
        ++begin;
    }
    return false;
}
