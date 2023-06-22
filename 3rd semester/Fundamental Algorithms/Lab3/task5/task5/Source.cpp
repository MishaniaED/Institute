#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<locale.h> 

int Check_choice_error(int ch, int k) {

    int i;
    int flag = 0;
    for (i = 1; i <= k; i++)
        if (ch == i){
            flag = 1;
            break;
        }
    return flag;
}

typedef struct Student
{
    int id;
    char* name;
    char* surname;
    char* group;
    int mark[5];
} Student, * PtrStudent;

//void Print_struct(Student* PtrStudent, int);

void SearchOnGroup(Student* PtrStudent, char* str, int count) {
    setlocale(LC_ALL, "Rus");
    //printf("%s", str);
    int i = 0;
    int flag = 0;
    for (i = 0; i < count; i++){
        if (strcmp(PtrStudent[i].group, str) == 0){
            printf("%d\t%s\t%s\t%s\t%", PtrStudent[i].id, PtrStudent[i].name, PtrStudent[i].surname, PtrStudent[i].group);
            for (int k = 0; k < 5; k++) {
                printf("%d ", PtrStudent[i].mark[k]);
            }
            printf("\n");
            flag = 1;
        }
    }

    if (flag == 0) {
        printf("\nДанной группы не существует!\n");
    }
}

int comp_name(const void* a, const void* b)
{
    int cmp;
    Student* pa = a;
    Student* pb = b;
    cmp = strcmp(pa->name, pb->name);
    return cmp;
}

int comp_surname(const void* a, const void* b)
{
    int cmp;
    Student* pa = a;
    Student* pb = b;
    cmp = strcmp(pa->surname, pb->surname);
    return cmp;
}

int intcmp(const void* a, const void* b)
{
    Student* pa = a;
    Student* pb = b;
    return pb->id - pa->id; // вернет разницу между id
}

void Print_struct(Student* PtrStudent, int count) {
    for (int i = 0; i < count; i++){
        printf("%d\t%s\t%s\t%s\t %d %d %d %d %d\n", PtrStudent[i].id, PtrStudent[i].name, PtrStudent[i].surname,
            PtrStudent[i].group, PtrStudent[i].mark[0], PtrStudent[i].mark[1], PtrStudent[i].mark[2], PtrStudent[i].mark[3], PtrStudent[i].mark[4]);
    }
}


int main(int argc, char* argv[])
{
    char bufname[BUFSIZ], bufsurname[BUFSIZ], bufgroup[BUFSIZ];
    int bufMark[5] = {0,0,0,0,0};
    double midl[5] = {0,0,0,0,0};
    PtrStudent student = NULL;
    int studentcount = 0, id = 0, i, choice1, choice2;
    double median = 0;
    const char* output = "out.txt";
    FILE* input_file, *output_file;
    char* group_example = NULL;

    setlocale(LC_ALL, "Rus");
    if (!(input_file = fopen(argv[1], "r"))){
        perror("---Ошибка: Входной файл не найден\n");
        exit(-1);
    }
    if (argc != 2) {
        perror("---Ошибка: некорректное число аргументов\n");
        exit(-2);
    }


    double sum1 = 0;
    int sum = 0;
    while (!feof(input_file)){
        sum = 0;
        fscanf(input_file, "%d%s%s%s%d%d%d%d%d", &id, bufname, bufsurname, bufgroup, &bufMark[0], &bufMark[1], &bufMark[2], &bufMark[3], &bufMark[4]);
        
        student = (PtrStudent)realloc(student, ++studentcount * sizeof(Student));
        student[studentcount - 1].id = id;
        for (i = 0; i < 5; ++i) {
            student[studentcount - 1].mark[i] = bufMark[i];
            sum += bufMark[i];
        }
        midl[studentcount - 1] = sum / 5.0;
        sum1 += midl[studentcount - 1];

        (student + studentcount - 1)->name = (char*)malloc(sizeof(char) * (strlen(bufname) + 1));
        (student + studentcount - 1)->name[strlen(bufname)] = '\0';
        strcpy(student[studentcount - 1].name, bufname);
        (student + studentcount - 1)->surname = (char*)malloc(sizeof(char) * (strlen(bufsurname) + 1));
        (student + studentcount - 1)->surname[strlen(bufsurname)] = '\0';
        strcpy(student[studentcount - 1].surname, bufsurname);
        (student + studentcount - 1)->group = (char*)malloc(sizeof(char) * (strlen(bufgroup) + 1));
        (student + studentcount - 1)->group[strlen(bufgroup)] = '\0';
        strcpy(student[studentcount - 1].group, bufgroup);

    }

    fclose(input_file);

    median = sum1 / studentcount;
    printf("Первоначальный список:\n\n");
    Print_struct(student, studentcount);
    printf("\n");

    while (1) {
        printf("Выберите действие: \n");

        printf("1 - Сортировка студентов\n");
        printf("2 - Вывод в трассировочный файл ФИО студента, группу и среднюю оценку за экзамен\n");
        printf("3 - Вывод студентов по указанной группе\n");
        printf("4 - Выйти из программы\n\n");
        printf("Ваш выбор: ");

        scanf("%d", &choice1);
        if (!Check_choice_error(choice1, 4))
            printf("\n---Ошибка: Некорректный выбор!\n\n");

        switch (choice1) {
        case 1:
            printf("Выберите, по чему нужно отсортировать: \n\n"
                " 1 - по id\n"
                " 2 - по фамилии\n"
                " 3 - по имени\n\n"
                "Ваш выбор: ");
            scanf("%d", &choice2);
            if (!Check_choice_error(choice2, 3))
                perror("\n---Ошибка: Некорректный выбор!\n\n");

            if (choice2 == 1) {
                qsort(student, studentcount, sizeof(Student), intcmp); // от большего к меньшему
                Print_struct(student, studentcount);
                printf("\n");
            }
            else if (choice2 == 2) {
                qsort(student, studentcount, sizeof(Student), comp_surname); // по алфавиту
                Print_struct(student, studentcount);
                printf("\n");
            }
            else if (choice2 == 3) {
                qsort(student, studentcount, sizeof(Student), comp_name); // по алфавиту
                Print_struct(student, studentcount);
                printf("\n");
            }
            break;

        case 2:
            if (!(output_file = fopen(output, "w"))){
                perror("---Ошибка: файл для вывода информации не найден\n");
                exit(-2);
            }

            for (i = 0; i < studentcount; i++){
                if (student[i].id != 1) fprintf(output_file, "\n");
                fprintf(output_file, "%d\t%s\t%s\t%s\t%lf", student[i].id, student[i].name, student[i].surname, student[i].group, midl[i]);
            }
            fprintf(output_file, "\nСредний балл за все экзамены = %f", median);
            fprintf(output_file, "\n\nСтуденты, чей средний балл за все экзамены выше среднего: \n");
            for (i = 0; i < studentcount; i++){
                if (midl[i] > median)
                    fprintf(output_file, "%s\t%s\n", student[i].name, student[i].surname);
            }
            printf("Средние баллы за экзамены можно посмотреть в файле \"out.txt\"\n");
            printf("\n");
            fclose(output_file);
            break;
        case 3:
            printf("Введите группу, список студентов которой Вы хотите получить: ");
            
            scanf("%s", bufgroup);
            group_example = (char*)malloc(strlen(bufgroup) * sizeof(char) + 1);
            group_example[strlen(bufgroup)] = '\0';
            strcpy(group_example, bufgroup);
            //printf("%s", group_example);
            SearchOnGroup(student, group_example, studentcount);
            printf("\n");
            break;
        case 4:
            for (i = 0; i < studentcount; i++){
                free(student[i].name);
                free(student[i].surname);
                free(student[i].group);
            }
            free(student);
            printf("\n");
            return 0;

        default:
            break;
        }
    }
}