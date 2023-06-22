#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <math.h>
#include <stdarg.h>


void check(int number_system, int count, ...)
{
    int end, f;
    double d, whole_part, arr[100], eps = 0.0000001;
    va_list p;
    va_start(p, count);
    for (int k = 0; k < count - 1; k++)
    {
        d = va_arg(p, double);
        printf("Num %lf is ", d);
        end = 0;
        arr[end++] = d;
        f = 1;
        while (d > eps && f)
        {
            d *= number_system;
            d = modf(d, &whole_part);
            for (int i = 0; i < end; i++)
            {
                if (fabs(d - arr[i]) < eps)
                {
                    printf("infinite\n");
                    f = 0;
                    break;
                }
            }
            arr[end++] = d;
        }
        if (f)
            printf("finite\n");
    }
}

int main()
{
    int number_system;
    printf("Enter number system: ");
    scanf("%d", &number_system);
    check(number_system, 0, 0.5, 0.4, 0.3, 0, 0.8, 1);
    return 0;
}