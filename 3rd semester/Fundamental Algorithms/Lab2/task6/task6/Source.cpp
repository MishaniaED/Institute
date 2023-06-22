#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdarg.h>

// использовал алгоритм КМП

// Поиск строки str2 в str1 

int seek_substring_KMP(char s[], char p[])
{
    int i, j, N, M;
    N = strlen(s);
    M = strlen(p);

    // Динамический массив длины М
    int* d = (int*)malloc(M * sizeof(int));

    // Вычисление префикс-функции
    d[0] = 0;
    for (i = 1, j = 0; i < M; i++)
    {
        while (j > 0 && p[j] != p[i])
            j = d[j - 1];
        if (p[j] == p[i])
            j++;
        d[i] = j;
    }

    // Поиск
    for (i = 0, j = 0; i < N; i++)
    {
        while (j > 0 && p[j] != s[i])
            j = d[j - 1];
        if (p[j] == s[i])
            j++;
        if (j == M)
        {
            free(d);
            return i - j + 1;
        }
    }
    free(d);
    return -1;
}



int main(int argc, char** argv)
{
    char str1[] = "hello";
    char str2[] = "Hello hello hi my hello hrre";
    seek_substring_KMP(str1, str2);
    return 0;
}
