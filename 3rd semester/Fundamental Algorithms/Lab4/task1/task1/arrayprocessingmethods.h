#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

/*load command: load elements from file to array
1 - correct file
0 - incorrect file*/
int array_load(struct array *array, FILE *file)
{
    int  i, j;
    int  size;
    char buf[BUFSIZ];

    size = 0;
    array->array = NULL;
    if(array->array != NULL)
        free(array->array);
    while(!feof(file)){
        fgets(buf, sizeof(buf), file);
        for(i = 0; i < strlen(buf); i++){
            if(isdigit(buf[i])){
                array->array = (int *)realloc((*array).array , ++size * sizeof(int));
                array->array[size - 1] = buf[i] - '0';
            }
            else if(buf[i] == '-'){
                j = i + 1;
                if(isdigit(buf[j])){
                    array->array  = (int *)realloc((*array).array , ++size * sizeof(int));
                    array->array[size - 1] = (-1) * (buf[j] - '0');
                }
                else
                    return (0);                
                i = j;
            }
        }
    }
    array->size = size;
    return (1);
}

/*load command: load elements from file to array
1 - saved
0 - failed to save*/
int     array_save(struct array array, FILE **file)
{
    int i;
    
    if(array.array == NULL || array.size == 0)
        return (0);
    for(i = 0; i < array.size; i++){
        fprintf(*file, "%d ", array.array[i]);
    }
    return (1);
}

/*rand command
1 - correct
0 - incorrect*/
int    array_rand(struct array *array, int size, int left, int right)
{
    int i;

    if(array->array != NULL || array->size != 0)
        return (0);
    srand(time(NULL));
    array->array  = (int *)malloc(size * sizeof(int));
    array->size = size;
    if(right < left)
        return (0);
    for(i = 0; i < size; i++)
        array->array[i] = rand() % (right - left + 1) + left;
    return (1);
}

/*concat
1 - correct
0 - incorrect*/
int     array_concat(struct array *array1, struct array array2)
{
    int     i;
    int     temp;

    if((array1->array == NULL || array1->size == 0) || array2.array == NULL || array2.size == 0)
        return (0);
    temp = array1->size;
    array1->size = temp + array2.size;
    array1->array = (int *)realloc(array1->array, (array1->size + array2.size) * sizeof(int));
    for(i = temp ; i < array1->size; i++){
        array1->array[i] = array2.array[i - temp];
    }
    free(array2.array);
    array2.size = 0;
    return (1);
}

/*free
1 - correct
0 - incorrect*/
int     array_free(struct array *array)
{
    int i;
    if(array->array == NULL || array->size == 0)
        return (0);
    free(array->array);
    array->size = 0;
}

/*remove
1 - correct
0 - incorrect*/
int     array_remove(struct array *array, int index, int amount)
{
    int i;

    if(array->array == NULL || array->size == 0)
        return (0);
    else if(index < 0 || amount < 0)
        return 0;
    else if(amount > array->size || index > array->size)
        return (0);
    else if(index <= array->size && amount > (array->size - index))
        return (0);
    else{
        for(i = 0; i < amount; i++){
            for(int j = index; j < array->size; j++){
                array->array[j] = array->array[j + 1];
            }
        }
    }
    array->array = (int *)realloc(array->array, (array->size - amount) * sizeof(int));
    array->size = array->size - amount;
    return (1);
}

/*copy
1 - correct
0 - incorrect*/
int array_copy(struct array array1, int start, int stop, struct array *array2)
{
    int i;
    int size;

    size = 0;
    if(array2->array != NULL){
        free(array2->array);
        array2->size = 0;
    }
    if(array1.array == NULL || array1.size == 0)
        return 0;
    else if(start > stop)
        return 0;
    else if(start < 0 || stop < 0)
        return 0;                                                                    
    else if(start >= array1.size || stop >= array1.size)
        return 0;
    else{
        array2->array = (int *)malloc((stop - start + 1) * sizeof(int));
        for(i = start; i <= stop; i++){
            array2->array[size++] = array1.array[i];
        }
    }
    array2->size = size;
    return 1;
}

/*sort
1 - sorted
0 - error*/
int array_sort(struct array *array, char *key)
{
    int i;

    if(array->array == NULL || array->size == 0)        // заменить на  ->  !!!
        return (0);
    if(!strcmp(key, "+"))
    {
        qsort(array->array, array->size, sizeof(int), cmpfunc);         // тернарный оператор
    }
    else if(!strcmp(key, "-"))
    {
        qsort(array->array, array->size, sizeof(int), reverse_cmpfunc);
    }
    else
        return 0;
    return 1;
}

int cmpfunc(const void *a, const void *b)
{
   return (*(int*)a - *(int*)b);
}
int reverse_cmpfunc(const void *a, const void *b)
{
   return (*(int*)b - *(int*)a);
}

/*permute
1 - correct
0 - incorrect*/
int array_permute(struct array *array)
{   
    int     i;
    int     id;
    int     temp;

    if(array->array == NULL || array->size == 0)
        return (0);
    srand(time(NULL));
    for(i = 0; i < array->size; i++)
    {
        id = rand() % array->size;
        temp = array->array[i];
        array->array[i] = array->array[id];
        array->array[id] = temp;
    }
    return (1);
}

/*stat
1 - correct
0 - incorrect*/
int array_stat(struct array array)
{
    int         index;
    int         max;
    int         min;
    int         recurre_num;
    double      arithmetical_mean;
    double      average;

    if(array.array == NULL || array.size == 0)
        return (0);
    printf("Size = %d\n", array.size);
    max = array_max(array, &index);
    printf("Max element = %d[%d in array]\n", max, index);
    min = array_min(array, &index);
    printf("Min element = %d[%d in array]\n", min, index);
    recurre_num = array_recurre(array);
    if(recurre_num != 0)
        printf("Most recurring item = %d\n", recurre_num);
    else
        printf("All numbera are unique\n");
    arithmetical_mean = array_arithmetical_mean(array);
    printf("Arithmetical mean = %lf\n", arithmetical_mean);
    average = array_max_average(array, arithmetical_mean);
    printf("Max average = %lf\n", average);
    return (1);
}

/*print interval
1 - correct
0 - incorrect*/
int array_print_interval(struct array array, int start, int stop)
{
    int     i;
    if(array.array == NULL || array.size == 0)
        return (0);
    else if(start > stop)
        return (0);
    else if(start < 0 || stop < 0)
        return (0);
    else if(start >= array.size || stop >= array.size)
        return (0);
    else{
        for(i = start; i <= stop; i++)
        printf("%d ", array.array[i]);
    }
    printf("\n");
    return (1);
}

/*print all
1 - correct
0 - incorrect*/
int array_print_all(struct array array)
{
    int     i;
    if(array.array == NULL || array.size == 0)
        return (0);
    for(i = 0; i < array.size; i++)
        printf("%d ", array.array[i]);
    printf("\n");
    return (1);
}
