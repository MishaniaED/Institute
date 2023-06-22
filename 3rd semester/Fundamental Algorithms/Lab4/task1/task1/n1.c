#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include "header.h"
#include "arrayprocessing.h"
#include "mathmethods.h"
#include "parsingstring.h"

int     main(int argc, char *argv[])
{
    FILE* input_file;
    struct array variables[26] = {0};
    int result;

    if(argc != 2){
        perror("Arguments error");
        exit(-1);
    }
    if(!(input_file = fopen(argv[1], "r"))){
        perror("Input file error");
        exit(-2);
    }
    result = array_processing(input_file, variables);
    if(result != 0){
        printf("Error in %d line!\n", result);
    }
    return (0);
}
