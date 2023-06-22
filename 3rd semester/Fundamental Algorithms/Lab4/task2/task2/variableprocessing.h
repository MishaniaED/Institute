#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memorycell.h"

char**  parse_string(char string[], int* size);
int     struct_cmp_by_name(const void* a, const void* b);
int     dichotomy_search(memoryCell* variables, int size, char* string);
int     arithmetic_operation(int num1, int num2, char* operation, int* code);

/*task - variables processing
returns 1 if correct*/
int     variable_processing(FILE* file)
{
    int         i, j;
    char**      parsed_string = NULL;
    char        string[BUFSIZ];
    int         size;
    int         amount_of_variables;
    int         counter;
    int         temp1, temp2, temp3, result_temp;
    int         error_code;
    memoryCell* variables;

    size = 0;
    counter = 1;
    amount_of_variables = 0;
    error_code = 0;
    variables = NULL;
    while (!feof(file))
    {
        fgets(string, sizeof(string), file);
        strtok(string, "\n");
        parsed_string = parse_string(string, &size);
        qsort(variables, amount_of_variables, sizeof(memoryCell), struct_cmp_by_name);

        /*initialization of variable*/
        if (strcmp(parsed_string[0], "print") && size == 4)
        {
            variables = (memoryCell*)realloc(variables, ++amount_of_variables * sizeof(memoryCell));
            variables[amount_of_variables - 1].name = (char*)malloc(strlen(parsed_string[0]) * sizeof(char) + 1);
            strcpy(variables[amount_of_variables - 1].name, parsed_string[0]);
            variables[amount_of_variables - 1].data = atoi(parsed_string[2]);
            printf("[INITIALIZATION]: %s = %d\n\n", variables[amount_of_variables - 1].name, variables[amount_of_variables - 1].data);
        }

        /*operations with variables*/
        else if (strcmp(parsed_string[0], "print") && size == 6)
        {
            temp1 = dichotomy_search(variables, amount_of_variables, parsed_string[2]);
            temp2 = dichotomy_search(variables, amount_of_variables, parsed_string[4]);
            result_temp = dichotomy_search(variables, amount_of_variables, parsed_string[0]);
            if (temp1 != -1 && temp2 != -1)
            {
                temp3 = arithmetic_operation(variables[temp1].data, variables[temp2].data, parsed_string[3], &error_code);
                if (error_code != -1 && error_code != -2)
                {
                    if (result_temp != -1)
                    {
                        variables[result_temp].data = temp3;
                        printf("[OPERATION %s]: %s = %s %s %s = %d %s %d = %d\n\n", parsed_string[3], \
                            variables[result_temp].name, variables[temp1].name, parsed_string[3], variables[temp2].name, \
                            variables[temp1].data, parsed_string[3], variables[temp2].data, variables[result_temp].data);
                    }
                    else
                    {
                        variables = (memoryCell*)realloc(variables, ++amount_of_variables * sizeof(memoryCell));
                        variables[amount_of_variables - 1].name = (char*)malloc(strlen(parsed_string[0]) * sizeof(char) + 1);
                        strcpy(variables[amount_of_variables - 1].name, parsed_string[0]);
                        variables[amount_of_variables - 1].data = temp3;
                        printf("[OPERATION %s]: %s = %s %s %s = %d %s %d = %d\n\n", parsed_string[3], \
                            variables[amount_of_variables - 1].name, variables[temp1].name, parsed_string[3], variables[temp2].name, \
                            variables[temp1].data, parsed_string[3], variables[temp2].data, variables[amount_of_variables - 1].data);
                    }
                }
                else
                    return (counter);
            }
            else
                return (counter);
        }

        /*print variables*/
        else if (!strcmp(parsed_string[0], "print"))
        {
            if (size == 2)
            {
                printf("[PRINT ALL]: %s = %d\n", variables[0].name, variables[0].data);
                for (i = 1; i < amount_of_variables; i++)
                    printf("             %s = %d\n", variables[i].name, variables[i].data);
                printf("\n");
            }
            else if (size == 4)
            {
                temp1 = dichotomy_search(variables, amount_of_variables, parsed_string[2]);
                if (temp1 == -1)
                    return (counter);
                else
                    printf("[PRINT ELEMENT]: %s = %d\n\n", variables[temp1].name, variables[temp1].data);
            }
            else
            {
                return (counter);
            }
        }
        counter++;
        for (i = 0; i < size; i++)
        {
            free(parsed_string[i]);
            parsed_string[i] = NULL;
        }
        free(parsed_string);
        parsed_string = NULL;
    }
    for (i = 0; i < amount_of_variables; i++)
    {
        free(variables[i].name);
        variables[i].data = 0;
    }
    free(variables);
    variables = NULL;
    
    return (0);
}

int     struct_cmp_by_name(const void* a, const void* b)
{
    memoryCell* ia = (memoryCell*)a;
    memoryCell* ib = (memoryCell*)b;
    return (strcmp(ia->name, ib->name));
}

/*return value - correct(found, returns index)
return -1 - incorrect(didn`t find)*/
int dichotomy_search(memoryCell* variables, int size, char* string)
{
    int bottom;
    int top;
    int mid;

    top = size - 1;
    bottom = 0;
    while (bottom <= top) {
        mid = (bottom + top) / 2;
        if (strcmp(variables[mid].name, string) == 0)
        {
            return (mid);
        }
        else if (strcmp(variables[mid].name, string) > 0)
        {
            top = mid - 1;
        }
        else if (strcmp(variables[mid].name, string) < 0)
        {
            bottom = mid + 1;
        }
    }
    return (-1);
}

/*arithmetic operations*/
/*return value and exit code
code = -1 - incorrect division
code = -2 - incorrect mod*/
int     arithmetic_operation(int num1, int num2, char* operation, int* code)
{
    int result;

    *code = 0;
    result = 0;
    if (!strcmp(operation, "+"))
        result = num1 + num2;
    else if (!strcmp(operation, "-"))
        result = num1 - num2;
    else if (!strcmp(operation, "*"))
        result = num1 * num2;
    else if (!strcmp(operation, "/"))
    {
        if (num2 == 0)
            *code = -1;
        else
            result = num1 / num2;
    }
    else if (!strcmp(operation, "%"))
    {
        if (num2 == 0)
            *code = -2;
        else
            result = num1 % num2;
    }
    return (result);
}
