/*#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


int* find_numbers1(int k, int l, int* new_amount, int amount, ...)
{
    int i, j, curr_num, curr_l, counter = 0, size = 1;
    int* result;
    va_list arg;

    result = NULL;
    (*new_amount) = 0;
    va_start(arg, amount);
    for (i = 0; i < amount; i++)
    {
        curr_l = 0;
        curr_num = va_arg(arg, int);
        for (j = 0; j < k; j++)
        {
            if ((curr_num >> j) & 1) // делим на 2 и проверяем на четность
                curr_l++;
        }
        if (curr_l == l)
        {
            counter++;
            result = (int*)realloc(result, size * sizeof(int));
            result[(*new_amount)] = curr_num;
            (*new_amount)++;
            if (size == counter) size *= 2;
        }
    }
    return (result);
}

int* find_numbers2(int k, int l, int* new_amount, int amount, ...)
{
    int i, j, curr_num, curr_l, counter = 0, size = 1;
    int* result;
    va_list arg;

    result = NULL;
    (*new_amount) = 0;
    va_start(arg, amount);
    for (i = 0; i < amount; i++)
    {
        curr_l = 0;
        curr_num = va_arg(arg, int);
        for (j = 0; j < k; j++)
        {
            if ((curr_num >> j) & 1) // делим на 2 и проверяем на четность
                curr_l++;
            else
                curr_l = 0;
            if (curr_l == l)
            {
                counter++;
                result = (int*)realloc(result, size * sizeof(int));
                result[(*new_amount)] = curr_num;
                (*new_amount)++;
                if (size == counter) size *= 2;
                curr_l = 0;
            }
        }
    }
    return (result);
}

int main()
{
    int i, k, l, size;
    int* result1, * result2;

    result1 = NULL;
    printf("1-st functiion:\nEnter size of number in bytes(k): ");
    scanf("%d", &k);
    printf("Enter amount of 1(l):");
    scanf("%d", &l);
    if (l > k)
    {
        perror("[ERROR]: k must be bigger than l!");
        exit(-1);
    }
    result1 = find_numbers1(k, l, &size, 4, 2, 4, 17, 33);

    if (size == 0)
        printf("There are no such numbers\n");
    else
    {
        for (i = 0; i < size; i++)
            printf("Correct for %d\n", result1[i]);
    }

    result2 = NULL;
    printf("\n2-nd functiion:\nEnter size of number in bytes(k): ");
    scanf("%d", &k);
    printf("Enter amount of 1(l):");
    scanf("%d", &l);
    if (l > k)
    {
        perror("[ERROR]: k must be bigger than l!\n");
        exit(-2);
    }
    //size = 0;
    result2 = find_numbers2(k, l, &size, 4, 15, 3, 61, 33);
    if (size == 0)
        printf("There are no such numbers\n");
    else
    {
        for (i = 0; i < size; i++)
            printf("Correct for %d\n", result2[i]);
    }
    return(0);
}*/

