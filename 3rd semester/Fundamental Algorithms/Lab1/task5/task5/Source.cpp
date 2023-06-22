#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    int i = 1;
    char *c[BUFSIZ], *s[BUFSIZ];
    FILE *input_file1, * input_file2, *output_file;
    
    // Errors
    if (argc != 3) {
        printf("[ERROR]: Not enough or too many arguments\n");
        return -1;
    }
    if (!(input_file1 = fopen(argv[1], "r"))) {
        printf("[ERROR]: Can`t open input file1\n");
        return -1;
    }
    if (!(input_file2 = fopen(argv[2], "r"))) {
        printf("[ERROR]: Can`t open input file2\n");
        return -1;
    }
    if (!(output_file = fopen("out.txt", "w"))) {
        printf("[ERROR]: Can`t create output file\n");
        return -1;
    }
    

    // Work with files

    while (!feof(input_file1) || !feof(input_file2)) {
        if (!feof(input_file1) && !feof(input_file2)) {
            fscanf(input_file1, "%s ", c);
            fscanf(input_file2, "%s ", s);
            fprintf(output_file, "%s ", c);
            fprintf(output_file, "%s ", s);
        }
        else if (feof(input_file1) && !feof(input_file2)) {
            fscanf(input_file2, "%s ", s);
            fprintf(output_file, "%s ", s);
        }
        else if (!feof(input_file1) && feof(input_file2)) {
            fscanf(input_file2, "%s ", c);
            fprintf(output_file, "%s ", c);
        }
    }

fclose(input_file1);
fclose(input_file2);
fclose(output_file);

return 0;
}
