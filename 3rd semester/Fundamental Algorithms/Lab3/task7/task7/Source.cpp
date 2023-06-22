/******************************************************************************

7. Структура Flight содержит номер рейса, название аэропорта и город вылета, название
аэропорта и город прилёта, местное время вылета и местное время прилета
(информация о времени задаётся отдельной структурой). Данные о рейсах хранятся во
входном файле, путь к которому передаётся через аргументы командной строки.
Реализовать возможность добавления, удаления и просмотра списка рейсов в
интерактивном диалоге с пользователем. Вывод информации о рейсах должен быть
информативным.

В Файле:
32 Nasko Torronto Vnukovo Moscow 9 15 30 18 45 0
10 Liste Mayami Sayonara Atlantida 10 00 02 23 15 13
78 Sheremetyevo Moscow Exo Urianuk 02 02 02 13 15 7
\n

*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_errors(int argc, char* argv[]);
struct s_flight* fill_flight_struct_from_file(FILE* infile, int* counter);
void add_new_flight_info(struct s_flight** flights, int* counter);
void delete_flight_info(struct s_flight** flights, int* counter);
void print_flights_info(struct s_flight* flights, int counter);
void update_file_info(FILE* infile, struct s_flight* flights, int counter);

struct s_time
{
    int hours;
    int minutes;
    int seconds;
};

struct s_flight
{
    int number;
    char* departure_airport_name;
    char* departure_city;
    char* arrival_airport_name;
    char* arrival_city;
    struct s_time local_departure_time;
    struct s_time local_arrival_time;
};



int main(int argc, char* argv[])
{
    int choise = 0, flag = 0;
    int operation;
    int size;
    FILE* input_file;
    struct s_flight* flight;

    check_errors(argc, argv);
    input_file = fopen(argv[1], "r");
    flight = fill_flight_struct_from_file(input_file, &size);
    fclose(input_file);
    while (1){
        printf("Operations:\n");
        printf("1. Add information about new flight\n");
        printf("2. Delete information about flight by ID\n");
        printf("3. Display actual list of flights\n");
        printf("4. Exit\n");
        printf("Choose operation: ");
        scanf("%d", &operation);
        switch (operation)
        {
        case 1:
            add_new_flight_info(&flight, &size);
            print_flights_info(flight, size);
            break;
        case 2:
            delete_flight_info(&flight, &size);
            print_flights_info(flight, size);
            break;
        case 3:
            print_flights_info(flight, size);
            break;
        case 4:
            flag = 1;
            //printf("flag = %d\n", flag);
            break;
        default: printf("\n Invalid number of operation!\n\n");
        };
        if (flag == 1) break;
    }
    input_file = fopen(argv[1], "w");
    update_file_info(input_file, flight, size);
    fclose(input_file);
    getchar();
    return (0);
}

void check_errors(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("\n Invalid arguments!\n\n");
        exit(-1);
    }
    if (!(fopen(argv[1], "r")))
    {
        perror("\nFailed to open file!\n\n");
        exit(-2);
    }
}

struct s_flight* fill_flight_struct_from_file(FILE* input_file, int* counter)
{
    char buf_departure_airport[BUFSIZ];
    char buf_arrival_airport[BUFSIZ];
    char buf_departure_city[BUFSIZ];
    char buf_arrival_city[BUFSIZ];
    struct s_flight* flights = NULL;

    (*counter) = 0;
    while (!feof(input_file))
    {
        flights = (struct s_flight*)realloc(flights, (++(*counter)) * sizeof(struct s_flight));
        fscanf(input_file, "%d %s %s %s %s %d %d %d %d %d %d", &flights[(*counter) - 1].number, \
            buf_departure_airport, buf_departure_city, buf_arrival_airport, buf_arrival_city, \
            & flights[(*counter) - 1].local_departure_time.hours,\
            & flights[(*counter) - 1].local_departure_time.minutes, \
            & flights[(*counter) - 1].local_departure_time.seconds, \
            & flights[(*counter) - 1].local_arrival_time.hours,\
            &flights[(*counter) - 1].local_arrival_time.minutes, \
            & flights[(*counter) - 1].local_arrival_time.seconds);

        flights[(*counter) - 1].departure_airport_name = (char*)malloc(strlen(buf_departure_airport) * sizeof(char) + 1);
        flights[(*counter) - 1].departure_airport_name[strlen(buf_departure_airport)] = '\0';
        strcpy(flights[(*counter) - 1].departure_airport_name, buf_departure_airport);

        flights[(*counter) - 1].arrival_airport_name = (char*)malloc(strlen(buf_arrival_airport) * sizeof(char) + 1);
        flights[(*counter) - 1].arrival_airport_name[strlen(buf_arrival_airport)] = '\0';
        strcpy(flights[(*counter) - 1].arrival_airport_name, buf_arrival_airport);

        flights[(*counter) - 1].departure_city = (char*)malloc(strlen(buf_departure_city) * sizeof(char) + 1);
        flights[(*counter) - 1].departure_city[strlen(buf_departure_city)] = '\0';
        strcpy(flights[(*counter) - 1].departure_city, buf_departure_city);

        flights[(*counter) - 1].arrival_city = (char*)malloc(strlen(buf_arrival_city) * sizeof(char) + 1);
        flights[(*counter) - 1].arrival_city[strlen(buf_arrival_city)] = '\0';
        strcpy(flights[(*counter) - 1].arrival_city, buf_arrival_city);
    }
    (*counter)--;
    return (flights);
}

/*add new elements in struct*/
void  add_new_flight_info(struct s_flight** flights, int* counter)
{
    char buf_departure_airport[BUFSIZ];
    char buf_arrival_airport[BUFSIZ];
    char buf_departure_city[BUFSIZ];
    char buf_arrival_city[BUFSIZ];
    (*flights) = (struct s_flight*)realloc((*flights), ++(*counter) * sizeof(struct s_flight));

    printf("Enter ID of flight: ");
    scanf("%d", &(*flights)[*counter - 1].number);

    printf("Enter departure airport name: ");
    scanf("%s", buf_departure_airport);
    (*flights)[*counter - 1].departure_airport_name = (char*)malloc(strlen(buf_departure_airport) * sizeof(char));
    strcpy((*flights)[*counter - 1].departure_airport_name, buf_departure_airport);

    printf("Enter departure city: ");
    scanf("%s", buf_departure_city);
    (*flights)[*counter - 1].departure_city = (char*)malloc(strlen(buf_departure_city) * sizeof(char));
    strcpy((*flights)[*counter - 1].departure_city, buf_departure_city);

    printf("Enter arrival airport name: ");
    scanf("%s", buf_arrival_airport);
    (*flights)[*counter - 1].arrival_airport_name = (char*)malloc(strlen(buf_arrival_airport) * sizeof(char));
    strcpy((*flights)[*counter - 1].arrival_airport_name, buf_arrival_airport);
   
    printf("Enter arrival city: ");
    scanf("%s", buf_arrival_city);
    (*flights)[*counter - 1].arrival_city = (char*)malloc(strlen(buf_arrival_city) * sizeof(char));
    strcpy((*flights)[*counter - 1].arrival_city, buf_arrival_city);

    printf("Enter local departure time(hh mm ss): ");
    scanf("%d %d %d", &(*flights)[*counter - 1].local_departure_time.hours, &(*flights)[*counter - 1].local_departure_time.minutes, \
        & (*flights)[*counter - 1].local_departure_time.seconds);

    printf("Enter local arrival time(hh mm ss): ");
    scanf("%d %d %d", &(*flights)[*counter - 1].local_arrival_time.hours, &(*flights)[*counter - 1].local_arrival_time.minutes, \
        & (*flights)[*counter - 1].local_arrival_time.seconds);
}

/*delete element from struct by ID*/
void delete_flight_info(struct s_flight** flights, int* counter)
{
    int i;
    int id;
    int flag1 = 0;

    printf("Enter id of flight: ");
    scanf("%d", &id);
    
    for (i = 0; i < (*counter); i++) {
        if ((*flights)[i].number == id) {
        flag1 = 1;
        break;
    }
    }
    if (flag1 != 1) {
        printf("\n Invalid ID!\n\n");
        exit(-3);
    }
    //printf("i = %d", i);
    for (i; i < (*counter)-1; i++)
    {
        (*flights)[i].number = (*flights)[i + 1].number;
        strcpy((*flights)[i].departure_airport_name, (*flights)[i + 1].departure_airport_name);
        strcpy((*flights)[i].departure_city, (*flights)[i + 1].departure_city);
        strcpy((*flights)[i].arrival_airport_name, (*flights)[i + 1].arrival_airport_name);
        strcpy((*flights)[i].arrival_city, (*flights)[i + 1].arrival_city);
        (*flights)[i].local_departure_time.hours = (*flights)[i + 1].local_departure_time.hours;
        (*flights)[i].local_departure_time.minutes = (*flights)[i + 1].local_departure_time.minutes;
        (*flights)[i].local_departure_time.seconds = (*flights)[i + 1].local_departure_time.seconds;
    }
    (*flights) = (struct s_flight*)realloc((*flights), --(*counter) * sizeof(struct s_flight));
}

void print_flights_info(struct s_flight* flights, int counter)
{
    int i;

    for (i = 0; i < counter; i++)
    {
        printf("%d: %s(%s) -> %s(%s); %d:%d:%d -> %d:%d:%d\n", flights[i].number, flights[i].departure_airport_name, flights[i].departure_city, \
            flights[i].arrival_airport_name, flights[i].arrival_city, \
            flights[i].local_departure_time.hours, flights[i].local_departure_time.minutes, flights[i].local_departure_time.seconds, \
            flights[i].local_arrival_time.hours, flights[i].local_arrival_time.minutes, flights[i].local_arrival_time.seconds);
    }
}

void update_file_info(FILE* infile, struct s_flight* flights, int counter)
{
    int i;

    for (i = 0; i < counter; i++)
    {
        fprintf(infile, "%d %s %s %s %s %d %d %d %d %d %d\n", flights[i].number, \
            flights[i].departure_airport_name, flights[i].departure_city, \
            flights[i].arrival_airport_name, flights[i].arrival_city, \
            flights[i].local_departure_time.hours, flights[i].local_departure_time.minutes, flights[i].local_departure_time.seconds, \
            flights[i].local_arrival_time.hours, flights[i].local_arrival_time.minutes, flights[i].local_arrival_time.seconds);
    }
    printf("Check result in flights info file\n");
}