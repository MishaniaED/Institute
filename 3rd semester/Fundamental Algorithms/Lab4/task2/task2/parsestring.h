#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** parse_string(char string[], int* size)
{
    int     i;
    int     j;
    int     k;
    int     ind;
    char**  parsed_string = NULL;
    char*   buf = NULL;

    *size = 0;
    k = 0;
    ind = 0;
    for (i = 0; i < strlen(string); i++)
    {
        if (string[i] == '-' && isdigit(string[i + 1]))
        {
            ind = 1;
            continue;
        }
        if (isdigit(string[i]) || isalpha(string[i]))
        {
            j = i;
            if (ind)
            {
                buf = (char*)realloc(buf, ++k * sizeof(char) + 1);
                buf[k - 1] = '-';
                ind = 0;
            }
            while (isdigit(string[j]) || isalpha(string[j]))
            {
                buf = (char*)realloc(buf, ++k * sizeof(char) + 1);
                buf[k - 1] = string[j];
                j++;
            }
            buf[k] = '\0';
            parsed_string = (char**)realloc(parsed_string, ++(*size) * sizeof(char*));
            parsed_string[(*size) - 1] = (char*)malloc(strlen(buf) + 1);
            strcpy(parsed_string[(*size) - 1], buf);
            free(buf);
            buf = NULL;
            k = 0;
            i = j - 1;
            
        }
        else
        {
            buf = (char*)malloc(sizeof(char) + 1);
            buf[0] = string[i];
            buf[1] = '\0';
            parsed_string = (char**)realloc(parsed_string, ++(*size) * sizeof(char*));
            parsed_string[(*size) - 1] = (char*)malloc(strlen(buf) + 1);
            strcpy(parsed_string[(*size) - 1], buf);
            free(buf);
            buf = NULL;
        }
    }
    return (parsed_string);
}
