#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int array_max(struct array array, int *index)
{
    int  i;
    int  max;

    *index = 0;
    max = array.array[0];
    for(i = 0; i < array.size; i++){
        if(array.array[i] > max){
            max = array.array[i];
            *index = i;
        }
    }
    return (max);
}

int array_min(struct array array, int *index)
{
    int     i;
    int     min;

    *index = 0;
    min = array.array[0];
    for(i = 0; i < array.size; i++){
        if(array.array[i] < min){
            min = array.array[i];
            *index = i;
        }
    }
    return (min);
}

int  array_recurre(struct array array)
{
    int     i, k;
    int     num;
    int     max_frq, frq;

    num = array.array[0];
    max_frq = 1;
    for(i = 0; i < array.size; i++){
        frq = 1;
        for(k = i + 1; k < array.size; k++)
            if(array.array[i] == array.array[k])
                frq += 1;
        if(frq > max_frq){
            max_frq = frq;
            num = array.array[i];
        }
    }
    if (max_frq > 1)
        return (num);
    else
        return (0);
}

double  array_arithmetical_mean(struct array array)
{
    int     i;
    double  average = 0;

    for(i = 0; i < array.size; i++){
        average += array.array[i];
    }
    average /= array.size;
    return (average);
}

double  array_max_average(struct array array, double mean)
{
    double      temp;
    int         i;

    temp = fabs(fabs(array.array[0]) - fabs(mean));
    for(i = 0; i < array.size; i++){
        if(fabs(fabs(array.array[i]) - fabs(mean)) > temp)
            temp = fabs(fabs(array.array[i]) - fabs(mean));
    }
    return (temp);
}
