#include <iostream>
using namespace std;

int main()
{
    int n, cnt = 0;
    cout << "cin the number: ";
    cin >> n;
    for (int i = 1; i * i <= n; i++) {
        for (int j = i; i * i + j * j <= n; j++) {
            if (i * i + j * j == n) {
                cout << i << "^2 + " << j << "^2" << endl;
                cnt = 1;
            }
        }
    }
    if (cnt == 0) cout << "NO";
    return 0;
}
