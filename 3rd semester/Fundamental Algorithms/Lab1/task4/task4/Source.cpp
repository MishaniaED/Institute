#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    char buf1[BUFSIZ], buf2[BUFSIZ], buf3[BUFSIZ];
    FILE* input_file, * out_file = NULL;
    char c;

    if ((input_file = fopen("inout.txt", "r")) == NULL) {
        printf("input file could not be opened\n");

    }
    else {
        if ((out_file = fopen("out.txt", "w")) == NULL) {
            printf("output file couldn't be opened\n");
            fclose(input_file);
            return 0;
        }        
        while (!feof(input_file)) {
            fscanf(input_file, "%s %s %s", buf1, buf2, buf3);
            fprintf(out_file, "%s %s %s\n", buf2, buf3, buf1);
        }
    }

    fclose(input_file);
    fclose(out_file);
    input_file = fopen("inout.txt", "w");
    out_file = fopen("out.txt", "r");
    while ((c = fgetc(out_file)) != EOF) {
        fprintf(input_file, "%c", c);
    }
    fclose(input_file);
    fclose(out_file);
    return 0;
}