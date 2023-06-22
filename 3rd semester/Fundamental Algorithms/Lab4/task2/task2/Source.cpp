#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parsestring.h"
#include "variableprocessing.h"


int     main(int argc, char* argv[])
{
    int   result;
    FILE* file;

    if (argc != 2){
        perror("Arguments error");
        exit(-1);
    }
    if (!(file = fopen(argv[1], "r"))){
        perror("File error");
        exit(-2);
    }
    result = variable_processing(file);
    if (result != 0){
        printf("Error in line %d!\n", result);
        return (-1);
    }
    fclose(file);
    return 0;
}
