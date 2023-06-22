#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "arrayprocessingmethods.h"

/*0 - correct
any number > 0 - invalid operation*/
/*main task - operations with arrays*/
int     array_processing(FILE *file, struct array variables[])
{
    int     i;
    int     size = 0;
    FILE    *temp_file;
    int     counter = 1;
    char    command[BUFSIZ] = {0};
    char    **parsed_string = NULL;

    while(!feof(file))
    {
        fgets(command, sizeof(command), file);
        strtok(command, "\n");
        parsed_string = parse_string(command, &size);

        /*Load*/
        if(!strcmp(parsed_string[0], "load") && size == 3)
        {
            parsed_string[1] = string_to_upper(parsed_string[1]);
            if(!check_array_name(parsed_string[1]))
                return (counter);
            if(!(temp_file = fopen(parsed_string[2], "r")))
            {
                printf("Load file error\n");
                return (counter);
            }
            if(!array_load(&variables[(*parsed_string[1]) - 'A'], temp_file))
            {
                printf("Load error\n");
                return (counter);
            }
            fclose(temp_file);
            printf("<LOAD>: %s = ", parsed_string[1]);
            for(i = 0; i < variables[(*parsed_string[1] - 'A')].size; i++)
                printf("%d ", variables[(*parsed_string[1]) - 'A'].array[i]);
            printf("\n");
        }
        
        /*Save*/
        else if(!strcmp(parsed_string[0], "save") && size == 3)
        {
            parsed_string[1] = string_to_upper(parsed_string[1]);
            if(!check_array_name(parsed_string[1]))
                return (counter);
            if(!(temp_file = fopen(parsed_string[2], "w")))
            {
                printf("Save file error\n");
                return (counter);
            }
            if(!array_save(variables[(*parsed_string[1]) - 'A'], &temp_file))
            {
                printf("Save error\n");
                return (counter);
            }
            fclose(temp_file);
            printf("<SAVE>: array %s saved in file '%s'\n", parsed_string[1], parsed_string[2]);
        }

        /*Rand*/
        else if(!strcmp(parsed_string[0], "rand") && size == 5)
        {
            parsed_string[1] = string_to_upper(parsed_string[1]);
            if(!check_array_name(parsed_string[1]))
                return (counter);
            if(!array_rand(&variables[(*parsed_string[1]) - 'A'], atoi(parsed_string[2]), atoi(parsed_string[3]), atoi(parsed_string[4])))
            {
                printf("Rand error\n");
                return (counter);
            }
            printf("<RAND>: %s = ", parsed_string[1]);
            for(i = 0; i < variables[(*parsed_string[1] - 'A')].size; i++)
                printf("%d ", variables[(*parsed_string[1]) - 'A'].array[i]);
            printf("\n");
        }

        /*Concat*/
        else if(!strcmp(parsed_string[0], "concat") && size == 3)
        {
            parsed_string[1] = string_to_upper(parsed_string[1]);
            parsed_string[2] = string_to_upper(parsed_string[2]);
            if(!check_array_name(parsed_string[1]) || !check_array_name(parsed_string[2]))
                return (counter);
            if(!array_concat(&variables[(*parsed_string[1]) - 'A'], variables[(*parsed_string[2]) - 'A']))
            {
                printf("Concat error\n");
                return (counter); 
            }
            printf("<CONCAT>: %s and %s = ", parsed_string[1], parsed_string[2]);
            for(i = 0; i < variables[(*parsed_string[1] - 'A')].size; i++)
                printf("%d ", variables[(*parsed_string[1]) - 'A'].array[i]);
            printf("\n");
        }

        /*free*/
        else if(!strcmp(parsed_string[0], "free") && size == 2)
        {
            parsed_string[1] = string_to_upper(parsed_string[1]);
            if(!check_array_name(parsed_string[1]))
                return (counter);
            if(!array_free(&variables[(*parsed_string[1]) - 'A']))
            {
                printf("Free error\n");
                return (counter);
            }
            printf("<FREE>: array %s was cleaned\n", parsed_string[1]);
        }

        /*remove*/
        else if(!strcmp(parsed_string[0], "remove") && size == 4)
        {
            parsed_string[1] = string_to_upper(parsed_string[1]);
            if(!check_array_name(parsed_string[1]))
                return (counter);
            if(!array_remove(&variables[(*parsed_string[1]) - 'A'], atoi(parsed_string[2]), atoi(parsed_string[3])))
            {
                printf("Remove error\n");
                return (counter);
            }
            printf("<REMOVE>: Removed %d-%d elements. Now C = ", atoi(parsed_string[2]), atoi(parsed_string[3]));
            for(i = 0; i < variables[(*parsed_string[1]) - 'A'].size; i++)
                printf("%d ", variables[(*parsed_string[1]) - 'A'].array[i]);
            printf("\n");
        }

        /*copy*/
        else if(!strcmp(parsed_string[0], "copy") && size == 5)
        {
            parsed_string[1] = string_to_upper(parsed_string[1]);
            parsed_string[4] = string_to_upper(parsed_string[4]);
            if(!check_array_name(parsed_string[1]))
                return (counter);
            if(!check_array_name(parsed_string[4]))
                return (counter);
            if(!array_copy(variables[(*parsed_string[1]) - 'A'], atoi(parsed_string[2]), atoi(parsed_string[3]), &variables[(*parsed_string[4]) - 'A']))
            {
                printf("Copy error\n");
                return (counter);
            }
            printf("<COPY>: %d-%d elements from %s array copied to %s array: ", atoi(parsed_string[2]), atoi(parsed_string[3]), parsed_string[1], parsed_string[4]);
            for(i = 0; i < variables[(*parsed_string[4]) - 'A'].size; i++)
                printf("%d ", variables[(*parsed_string[4]) - 'A'].array[i]);
            printf("\n");
        }
        
        /*sort(using qsort)*/
        else if(!strcmp(parsed_string[0], "sort") && size == 3)
        {
            parsed_string[1] = string_to_upper(parsed_string[1]);
            if(!check_array_name(parsed_string[1]))
                return (counter);
            if(!array_sort(&variables[(*parsed_string[1]) - 'A'], parsed_string[2]))
            {
                printf("Sort error\n");
                return (counter);
            }
            if(!strcmp(parsed_string[2], "-"))
                printf("<SORT->: array %s sorted descending: ", parsed_string[1]);
            else if(!strcmp(parsed_string[2], "+"))
                printf("<SORT+>: array %s sorted ascending: ", parsed_string[1]);
            for(i = 0; i < variables[(*parsed_string[1]) - 'A'].size; i++)
                printf("%d ", variables[(*parsed_string[1]) - 'A'].array[i]);
            printf("\n");
        }

        /*permute*/
        else if(!strcmp(parsed_string[0], "permute") && size == 2)
        {
            parsed_string[1] = string_to_upper(parsed_string[1]);
            if(!check_array_name(parsed_string[1]))
                return (counter);
            if(!array_permute(&variables[(*parsed_string[1]) - 'A']))
            {
                printf("Permute error\n");
                return (counter);
            }
            printf("<PERMUTE>: permuted array %s elements: ", parsed_string[1]);
            for(i = 0; i < variables[(*parsed_string[1]) - 'A'].size; i++)
                printf("%d ", variables[(*parsed_string[1]) - 'A'].array[i]);
            printf("\n");
        }

        /*stat*/
        else if(!strcmp(parsed_string[0], "stat") && size == 2)
        {
            parsed_string[1] = string_to_upper(parsed_string[1]);
            if(!check_array_name(parsed_string[1]))
                return (counter);
            printf("<STAT>: Static info about array:\n");
            if(!array_stat(variables[(*parsed_string[1]) - 'A']))
            {
                printf("Stat error\n");
                return (counter);
            }
        }

        /*print elements from n1 to n2*/
        else if(!strcmp(parsed_string[0], "print") && size == 4)
        {
            parsed_string[1] = string_to_upper(parsed_string[1]);
            if(!check_array_name(parsed_string[1]))
                return (counter);
            printf("<PRINT INTERVAL>: print %d-%d elements from array %s: ", atoi(parsed_string[2]), atoi(parsed_string[3]), parsed_string[1]);
            if(!array_print_interval(variables[(*parsed_string[1]) - 'A'], atoi(parsed_string[2]), atoi(parsed_string[3])))
            {
                printf("Print interval error");
                return (counter);
            }
        }

        /*print all*/
        else if(!strcmp(parsed_string[0], "print") && size == 3)
        {
            parsed_string[1] = string_to_upper(parsed_string[1]);
            if(!check_array_name(parsed_string[1]))
                return (counter);
            printf("<PRINT>: print ALL %s array elements: ", parsed_string[1]);
            if(!array_print_all(variables[(*parsed_string[1]) - 'A']))
            {
                printf("Print all error");
                return (counter);
            }
        }

        else
            return(counter);
        
        counter++;
        printf("\n");
    }
    return (0);
}
