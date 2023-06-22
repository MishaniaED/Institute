#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*parsing string from file*/
char** parse_string(char *string, int *size)
{
    char    **parsed_string = NULL;
    char    *token = NULL;
    int     sort_sign = 0;

    *size = 0;
    if(string[strlen(string) - 1] == '-')
        sort_sign = -1;
    if(string[strlen(string) - 1] == '+')
        sort_sign = 1;
    token = strtok(string, ", )(");
    while(token != NULL){
        parsed_string = (char **)realloc(parsed_string, ++(*size) * sizeof(char *));
        parsed_string[(*size) - 1] = (char *)malloc(strlen(token) * sizeof(char));
        strcpy(parsed_string[(*size) - 1], string_to_lower(token));
        token = strtok(NULL, ", )(");
    }
    if(sort_sign != 0){
        token = strtok(parsed_string[1], "+-");
        parsed_string = (char **)realloc(parsed_string, ++(*size) * sizeof(char *));
        parsed_string[(*size) - 1] = (char *)malloc(sizeof(char));
        if(sort_sign == 1)
            strcpy(parsed_string[(*size) - 1], "+");
        if(sort_sign == -1)
            strcpy(parsed_string[(*size) - 1], "-");
    }
    return (parsed_string);
}

/*1 - correct
0 - incorrect*/
int check_array_name(char *string)
{
    if(strlen(string) > 1)
        return(0);
    else if(!isupper(string[0]))
        return (0);
    return (1);
}

/*all string symbols to lower case*/
char* string_to_lower(char *string)
{
    int i;

    for(i = 0; i < strlen(string); i++){
        string[i] = tolower(string[i]);
    }
    return (string);
}

/*all string symbols to upper case*/
char* string_to_upper(char *string)
{
    int i;
    for(i = 0; i < strlen(string); i++){
        string[i] = toupper(string[i]);
    }
    return (string);
}
