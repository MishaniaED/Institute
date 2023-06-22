#include <iostream>
#include <math.h>
#include <array>

using namespace std;

int main()
{
    char f1 = 0, prevf1 = 0;
    short int f2 = 0, prevf2 = 0;
    int f3 = 0, prevf3 = 0;
    long long f4 = 0, prevf4 = 0;
    int n, i, a1 = 0, a2 = 0, a3 = 0, a4 = 0;
    long long res = 0;
    cout << "Cin number:";
    cin >> n;
    for (i = 0; i < n; i++) {
        prevf1 = f1;
        f1 += pow(i, i);
        if (f1 < prevf1)
        {
            cout << "Overflow Char - " << i << endl;
            a1 = 1;
            break;
        }
    }
    for (i = 0; i < n; i++) {
        prevf2 = f2;
        f2 += pow(i, i);
        if (f2 < prevf2)
        {
            cout << "Overflow Short Int -- " << i << endl;
            a2 = 1;
            break;
        }
    }
    for (i = 0; i < n; i++) {
        prevf3 = f3;
        f3 += pow(i, i);
        if (f3 < prevf3)
        {
            cout << "Overflow Int -- " << i << endl;
            a3 = 1;
            break;
        }
    }
    for (i = 0; i < n; i++) {
        prevf4 = f4;
        f4 += pow(i, i);
        if (f4 < prevf4)
        {
            cout << "Overflow Long Long -- " << i << endl;
            a4 = 1;
            break;
        }
    }
    cout << "\n";
    if (a1 == 0) cout << "Your result Char: " << f1 * 1 << endl;
    if (a2 == 0) cout << "Your result Short Int: " << f2 << endl;
    if (a3 == 0) cout << "Your result Int: " << f3 << endl;
    if (a4 == 0) cout << "Your result Long Long: " << f4 << endl;
    return 0;
}
