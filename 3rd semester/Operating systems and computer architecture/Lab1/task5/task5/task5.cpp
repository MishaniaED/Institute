#include <iostream>
using namespace std;

int main()
{
    int m, i = 0, j = 1, k, n = 1;
    cin >> m;
    if (m <= 0) {
        cout << "fibo number: " << i << "\nserial number: " << n;
        return 0;
    }

    while (j <= m) {
        k = j;
        j = i + j;
        i = k;
        n++;
    }
    cout << "fibo number: " << j << "\nserial number: " << n;
}
