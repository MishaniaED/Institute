#include <iostream>
using namespace std;

int main() {
    int n, m = 0, t;
    cin >> n;
    t = n * (n - 1) + 1;
    for (int i = 1; i <= n; i++)
    {
        cout << t;
        if (i < n)
            cout << '+';
        m = m + t;
        t = t + 2;
    }
    cout << "=" << m;
}