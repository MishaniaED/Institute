#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

int check_of_convex(int n, ...)
{
    if (n % 2 == 1) { // ѕроверка переданных координат
        printf("Insufficient number of auto coordinates transferred");
        return -1;
    }
    // ѕровер€ем через знак соседних произведений векторов
    va_list vl;
    va_start(vl, n);
    int arr_vect[100][2];
    int arr_arg[100];
    int i, j, count = 0, prev_flag, flag;

    for (i = 0; i < n; i++)
        arr_arg[i] = va_arg(vl, int);

    for (i = 0; i < n - 2; i += 2, count++) // «адаем векторы
    {
        arr_vect[count][0] = arr_arg[i + 2] - arr_arg[i];
        arr_vect[count][1] = arr_arg[i + 3] - arr_arg[i + 1];
    }

    if (arr_vect[i][0] * arr_vect[0][1] - arr_vect[0][0] * arr_vect[i][1] < 0)
        flag = 1;
    else
        flag = 0;

    for (i = 0; i < count; i++)
    {
        prev_flag = flag;
        j = i + 1;

        if (arr_vect[i][0] * arr_vect[j][1] - arr_vect[j][0] * arr_vect[i][1] < 0)
            flag = 1;
        else
            flag = 0;
        if (i == 0)
            continue;

        if (flag != prev_flag)
        {
            printf("Multiangle isnt convex\n");
            va_end(vl);
            return 0;
        }
    }
    printf("Multiangle is convex\n");
    va_end(vl);
}

int polynomial(int n, ...)
{
    va_list vl;
    va_start(vl, n);
    double x = va_arg(vl, int), power = va_arg(vl, int);
    int sum = 0;
    double x1 = 1 / x;

    for (int i = 0; i <= power; i++) {
        sum += va_arg(vl, int) * x * x1;
        x1 *= x;

    }
    printf("Result: %d", sum);
    va_end(vl);
    return 0;
}

int main()
{
    check_of_convex(12, 0, 0, 0, 3, 1, 4, 3, 4, 6, 2, 4, -2); // структура point с пол€ми x, y
    polynomial(7, 2, 5, 1, 1, 1, 1, 1, 0);
    // 2-й параметр зн-е аргумента, 3-й параметр степень многочлена
    return 0;
}