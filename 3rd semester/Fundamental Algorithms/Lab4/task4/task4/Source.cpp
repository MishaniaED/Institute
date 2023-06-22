#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<locale.h>

typedef struct Citizen {
    char* surname;
    char* name;
    char* patronymic;
    int day;
    int month;
    int year;
    char* gender;
    int income;
} Citizen;

typedef struct List{
    Citizen info;      // ���� ������
    struct List* next; // ��������� �� ��������� �������
}List;

struct List* init(Citizen a) // �- �������� ������� ����
{
    List* list;
    // ��������� ������ ��� ������ ������
    list = (List*)malloc(sizeof(struct List));
    list->info = a;
    list->next = NULL; // ��� ��������� ���� ������
    return(list);
}

void listprint(List* list){
    struct List* p;
    p = list;
    if (p == NULL){
        printf("\n[FAIL]: Citizen list is empty\n");
        return;
    }
    do {
        printf("%s %s %s %d %d %d %s %d\n", p->info.surname, p->info.name, p->info.patronymic, \
            p->info.day, p->info.month, p->info.year, p->info.gender, p->info.income); // ����� �������� �������� p
        p = p->next; // ������� � ���������� ����
    } while (p != NULL);
    printf("\n");
}

void addelem(List** list, Citizen data)
{

    List* newPtr, * previousPtr, *currentPtr;
    newPtr = (struct List*)malloc(sizeof(List));
    if (!newPtr) {
        perror("malloc () failed"); exit(-1);
    }
    if (newPtr != NULL) {
        
        newPtr->info = data;
        newPtr->next = NULL;
        previousPtr = NULL;
        currentPtr = *list;
        /*while (currentPtr != NULL)
        {
            previousPtr = currentPtr;
            currentPtr = currentPtr->next;
        }*/
        while ((currentPtr != NULL) && (data.year < currentPtr->info.year)) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->next;
         }    
        while ((currentPtr != NULL) && (data.year == currentPtr->info.year) && (data.month < currentPtr->info.month)) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->next;
        }
        while ((currentPtr != NULL) && (data.year == currentPtr->info.year) && (data.month == currentPtr->info.month) && (data.day < currentPtr->info.day)) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->next;
        }
        if (previousPtr == NULL) {
            newPtr->next = *list;
            *list = newPtr;
        }
        else {
            previousPtr->next = newPtr;
            newPtr->next = currentPtr;
        }
    }
    else { perror("malloc () failed"); exit(-1); }
}

void deleteList(List** head) {          // �������� ������
    while ((*head)->next){
        free((*head)->info.surname);
        free((*head)->info.name);
        free((*head)->info.patronymic);
        free((*head)->info.gender);
        (*head)->info.day = 0;
        (*head)->info.month = 0;
        (*head)->info.year = 0;
        (*head)->info.income = 0;
        *head = (*head)->next;
    }
    free(*head);
}

void find(List* list, int flag, int param_i, char param_c[BUFSIZ]) {
    while (list != NULL) {
        switch (flag) {
        case 1:
            if (!strcmp(list->info.surname, param_c)) {
                printf("%s %s %s %d %d %d %s %d\n", list->info.surname, list->info.name, list->info.patronymic, \
                    list->info.day, list->info.month, list->info.year, list->info.gender, list->info.income);
            }
            break;
        case 2:
            if (!strcmp(list->info.name, param_c)) {
                printf("%s %s %s %d %d %d %s %d\n", list->info.surname, list->info.name, list->info.patronymic, \
                    list->info.day, list->info.month, list->info.year, list->info.gender, list->info.income);
            }
            break;
        case 3:
            if (!strcmp(list->info.patronymic, param_c)) {
                printf("%s %s %s %d %d %d %s %d\n", list->info.surname, list->info.name, list->info.patronymic, \
                    list->info.day, list->info.month, list->info.year, list->info.gender, list->info.income);
            }
            break;
        case 4:
            if (list->info.day == param_i) {
                printf("%s %s %s %d %d %d %s %d\n", list->info.surname, list->info.name, list->info.patronymic, \
                    list->info.day, list->info.month, list->info.year, list->info.gender, list->info.income);
            }
            break;
        case 5:
            if (list->info.month == param_i) {
                printf("%s %s %s %d %d %d %s %d\n", list->info.surname, list->info.name, list->info.patronymic, \
                    list->info.day, list->info.month, list->info.year, list->info.gender, list->info.income);
        }
            break;
        case 6:
            if (list->info.year == param_i) {
                printf("%s %s %s %d %d %d %s %d\n", list->info.surname, list->info.name, list->info.patronymic, \
                    list->info.day, list->info.month, list->info.year, list->info.gender, list->info.income);
            }
            break;
        case 7:
            if (!strcmp(list->info.gender, param_c)) {
                printf("%s %s %s %d %d %d %s %d\n", list->info.surname, list->info.name, list->info.patronymic, \
                    list->info.day, list->info.month, list->info.year, list->info.gender, list->info.income);
            }
            break;
        case 8:
            if (list->info.income == param_i) {
                printf("%s %s %s %d %d %d %s %d\n", list->info.surname, list->info.name, list->info.patronymic, \
                    list->info.day, list->info.month, list->info.year, list->info.gender, list->info.income);
            }
            break;
        }
        list = list->next;
    }
}

void deleteById(List** list, int id){
    int i = 0;
    id--;
    List* currPtr, * prevPtr, * tempPtr;
    if (list == NULL){
        printf("\n[FAIL]: Citizen list is empty\n");
        return;
    }
    if (id == 0){
        printf("\n[SUCCESS]: Deleted element by id %d\n", id);
        tempPtr = *list;
        *list = (*list)->next;
        free(tempPtr);
    }
    else
    {
        prevPtr = NULL;
        currPtr = *list;
        while (currPtr != NULL && i != id)
        {
            prevPtr = currPtr;
            currPtr = currPtr->next;
            i++;
        }
        if (currPtr != NULL)
        {
            printf("\n[SUCCESS]: Deleted element by id %d\n", id+1);
            tempPtr = currPtr;
            prevPtr->next = currPtr->next;
            free(tempPtr);
        }
        else
            printf("\n[FAIL]: Didn`t file citizen with given id %d!\n", id+1);
    }
}

void add_to_file(List* list, FILE* input_file) {
    if (!(input_file = fopen("my.txt", "w"))) {
        perror("�� ������� ������� ����");
        exit(-2);
    }
    int counter = 0;
    struct List* p;
    p = list;
    while (p != NULL){
        printf("counter = %d\n", counter);
        counter++;
        fprintf(input_file, "%s %s %s %d %d %d %s %d\n", p->info.surname, p->info.name, p->info.patronymic, \
            p->info.day, p->info.month, p->info.year, p->info.gender, p->info.income);
        p = p->next;
    } 
    fclose(input_file);
    
}

int main() {
    char* locale = setlocale(LC_ALL, "");

    int flag = 0, choice = 0;
    FILE* input_file;
    Citizen* people_p = (Citizen*)malloc(sizeof(Citizen));
    List* list = (List*)malloc(sizeof(List));
    
    char buf_surename[BUFSIZ], buf_name[BUFSIZ], buf_patronymic[BUFSIZ], buf_gender[BUFSIZ];
    int buf_day = 0, buf_month = 0, buf_year = 0, buf_income = 0;

    if (!(input_file = fopen("my.txt", "r"))){
        perror("�� ������� ������� ����");
        exit(-2);
    }

    int counter = 0;

    while (!feof(input_file)) {
        counter++;
        list = (List*)realloc(list, sizeof(List) * counter);
        fscanf(input_file, "%s%s%s%d%d%d%s%d", buf_surename, buf_name, buf_patronymic, &buf_day, &buf_month, &buf_year, buf_gender, &buf_income);
        people_p->surname = (char*)malloc(sizeof(char) * strlen(buf_surename) + 1);
        people_p->name = (char*)malloc(sizeof(char) * strlen(buf_name) + 1);
        people_p->patronymic = (char*)malloc(sizeof(char) * strlen(buf_patronymic) + 1);
        people_p->gender = (char*)malloc(sizeof(char) * strlen(buf_gender) + 1);
        if (!people_p->surname || !people_p->name || !people_p->patronymic || !people_p->gender) {
            perror("malloc () failed"); exit(-1);
        }
        strcpy(people_p->surname, buf_surename);
        strcpy(people_p->name, buf_name);
        strcpy(people_p->patronymic, buf_patronymic);
        strcpy(people_p->gender, buf_gender);
        people_p->day = buf_day;
        people_p->month = buf_month;
        people_p->year = buf_year;
        people_p->income = buf_income;

        if (counter == 1)  list = init(*people_p);
        else addelem(&list, *(people_p));
        
    }
    fclose(input_file);

    listprint(list);
    printf("������ ����������� ����� �� ����������?\n��/��� - 1/0\n��� �����: ");
    flag = NULL;
    scanf("%d", &choice);
    if(choice == 1)
    while (1) {
        printf("\n �������� �������� �� �������� ����� �������������� �����:\n1 - �� �������\n2 - �� �����\n3 - ��������\n\
4 - �� ���\n5 - �� ������\n6 - �� ����\n7 - �� �������\n8 - �� ���������\n");
        printf("��� �����: ");
        flag = NULL;
        scanf("%d", &flag);
        switch (flag)
        {                           
        case 1:
            printf("������� �������: ");
            scanf("%s", buf_surename);
            find(list, flag, buf_day, buf_surename);
            break;
        case 2:
            printf("������� ���: ");
            scanf("%s", buf_name);
            find(list, flag, buf_day, buf_name);
            break;
        case 3:
            printf("������� ��������: ");
            scanf("%s", buf_patronymic);
            find(list, flag, buf_day, buf_patronymic);
            break;
        case 4:
            printf("������� ����: ");
            scanf("%d", &buf_day);
            find(list, flag, buf_day, buf_patronymic);
            break;
        case 5:
            printf("������� �����: ");
            scanf("%d", &buf_month);
            find(list, flag, buf_month, buf_patronymic);
            break;
        case 6:
            printf("������� ���: ");
            scanf("%d", &buf_year);
            find(list, flag, buf_year, buf_patronymic);
            break;
        case 7:
            printf("������� ������: ");
            scanf("%s", buf_gender);
            find(list, flag, buf_year, buf_gender);
            break;
        case 8:
            printf("������� ���������: ");
            scanf("%d", &buf_income);
            find(list, flag, buf_income, buf_gender);
            break;
        case 9: 
        default: printf("������ �������� ����!\n");
        }
        printf("������ ��� ��� ����������� �����?\n��/��� - 1/0\n��� �����: ");
        scanf("%d", &flag);
        if (flag == 0) break;
    }
        printf("������ �������/��������/������� � ���� 'my.txt'?\n��/��� - 1/0\n��� �����: ");
        flag = NULL;
        scanf("%d", &flag);
        if (flag == 1) {
            while (1) {
                printf("�������� ��������:\n1 - �������\n2 - ��������\n3 - ������� � ���� 'my.txt'\n");
                printf("��� �����: ");
                flag = NULL;
                scanf("%d", &flag);
                switch (flag) {
                case 1:
                    printf("�������� ����� ������� �� ����� � ������ ����� �������:\n");
                    listprint(list);
                    printf("��� �����: ");
                    choice = NULL;
                    scanf("%d", &choice);
                    deleteById(&list, choice);
                    listprint(list);
                    break;
                case 2:
                    printf("������� ����������� ������ ��� ���������� ���������:\n");
                    printf("�������, ���, ��������, ����, �����, ���, ������, ��������:\n");
                    counter++;
                    list = (List*)realloc(list, sizeof(List) * counter);
                    scanf("%s%s%s%d%d%d%s%d", buf_surename, buf_name, buf_patronymic, &buf_day, &buf_month, &buf_year, buf_gender, &buf_income);
                    people_p->surname = (char*)malloc(sizeof(char) * strlen(buf_surename) + 1);
                    people_p->name = (char*)malloc(sizeof(char) * strlen(buf_name) + 1);
                    people_p->patronymic = (char*)malloc(sizeof(char) * strlen(buf_patronymic) + 1);
                    people_p->gender = (char*)malloc(sizeof(char) * strlen(buf_gender) + 1);
                    if (!people_p->surname || !people_p->name || !people_p->patronymic || !people_p->gender) {
                        perror("malloc () failed"); exit(-1);
                    }
                    strcpy(people_p->surname, buf_surename);
                    strcpy(people_p->name, buf_name);
                    strcpy(people_p->patronymic, buf_patronymic);
                    strcpy(people_p->gender, buf_gender);
                    people_p->day = buf_day;
                    people_p->month = buf_month;
                    people_p->year = buf_year;
                    people_p->income = buf_income;

                    addelem(&list, *(people_p));
                    
                    listprint(list);
                    break;

                case 3:
                    add_to_file(list, input_file);
                    printf("���������� ��������� � �����\n");
                    break;

                default: break;
                }

                printf("������ ��� ��� ��������/������� ��� ������� � ����?\n��/��� - 1/0\n");
                flag = NULL;
                scanf("%d", &flag);
                if (flag == 0) break;
            }
        }
    //listprint(list);
    deleteList(&list);
    getchar();
    return 0;
}        