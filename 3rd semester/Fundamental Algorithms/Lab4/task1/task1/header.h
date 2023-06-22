#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

struct  array
{
    int *array;
    int size;
};

int     array_processing(FILE *file, struct array variables[]);
char    **parse_string(char *string, int *size);
char    *string_to_lower(char *string);
char    *string_to_upper(char *string);
int     check_array_name(char *string);
int     array_load(struct array *array, FILE *file);
int     array_save(struct array array, FILE **file);
int     array_rand(struct array *array, int size, int left, int right);
int     array_concat(struct array *array1, struct array array2);
int     array_free(struct array *array);
int     array_remove(struct array *array, int index, int amount);
int     array_copy(struct array array1, int start, int stop, struct array *array2);
int     array_sort(struct array *array, char *key);
int     cmpfunc(const void *a, const void *b);
int     reverse_cmpfunc(const void *a, const void *b);
int     array_permute(struct array *array);
int     array_stat(struct array array);
int     array_max(struct array array, int *index);
int     array_min(struct array array, int *index);
int     array_recurre(struct array array);
double  array_arithmetical_mean(struct array array);
double  array_max_average(struct array array, double mean);
int     array_print_interval(struct array array, int start, int stop);
int     array_print_all(struct array array);
