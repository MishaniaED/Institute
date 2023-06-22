/******************************************************************************
Запустить через онлайн компилятор
6. 1. Реализовать структуру String, содержащую в себе поля для динамического массива
символов и длины строки. Реализовать функции создания строки, удаления строки,
сравнения строк, копирования строки, конкатенации строк, дублирования строки.
Продемонстрировать работу с этой структурой.


*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct String {
    char* Str;
    int len;
} String;

String Make_string(const char str[BUFSIZ]) {
    String tmp;
    int i;
    tmp.len = 0;
    const char* ptr = str;
    while (*ptr != '\0') {
        tmp.len++;
        ptr++;
    }

    tmp.Str = (char*)malloc(sizeof(char) * (tmp.len + 1));

    if (!tmp.Str) {
        fprintf(stderr, "malloc() failed!\n");
        exit(-1);
    }

    tmp.Str[tmp.len] = '\0';

    for (i = 0; i < tmp.len; i++)
        tmp.Str[i] = str[i];
    return tmp;
}

void Delete_string(String* name) {
    free((*name).Str);
    (*name).len = 0;
}

void Compare(String name_1, String name_2) {
    int i;
    int k;
    i = (name_1.len > name_2.len) ? name_2.len : name_1.len;

    for (k = 0; k <= i; k++) {
        if (name_1.Str[k] > name_2.Str[k]) {
            printf("LG order: %s, %s\n", name_2.Str, name_1.Str);
            return;
        }
        if (name_1.Str[k] < name_2.Str[k]) {
            printf("LG order: %s, %s\n", name_1.Str, name_2.Str);
            return;
        }
    }
    printf("Str are simmular: %s %s\n", name_1.Str, name_2.Str);
}

String Concatinate_string(String name_1, String name_2) {
    String name_3;
    int i;
    int k;
    name_3.len = name_2.len + name_1.len;
    name_3.Str = (char*)malloc(sizeof(const char) * name_3.len + 1);

    if (!name_3.Str) {
        fprintf(stderr, "malloc() failed!\n");
        exit(-2);
    }

    for (i = 0; i < name_1.len; i++)
        name_3.Str[i] = name_1.Str[i];

    for (i = name_1.len, k = 0; i < name_3.len; i++, k++)
        name_3.Str[i] = name_2.Str[k];

    name_3.Str[name_1.len + name_2.len] = '\0';

    return name_3;
}

String Copy_string(String name) {
    String tmp;
    int i;
    tmp.len = name.len;
    tmp.Str = (char*)malloc(sizeof(char) * (tmp.len + 1));

    if (!tmp.Str) {
        fprintf(stderr, "malloc() failed!\n");
        exit(-3);
    }

    for (i = 0; i < tmp.len; i++)
        tmp.Str[i] = name.Str[i];

    tmp.Str[tmp.len] = '\0';
    return tmp;
}

String Duplication_string(String name) {
    String tmp;
    int i, j;
    tmp.len = name.len * 2;
    tmp.Str = (char*)malloc(sizeof(char) * (tmp.len + 1));

    if (!tmp.Str) {
        fprintf(stderr, "malloc() failed!\n");
        exit(-4);
    }

    for (i = 0, j = 0; i < name.len; i++, j++) {
        tmp.Str[i] = name.Str[j];
        tmp.Str[i + name.len] = name.Str[j];
    }
    tmp.Str[tmp.len] = '\0';
    return tmp;
}

int main() {
    String a;
    String b;
    String c;

    printf("---Creating---\n");
    a = Make_string("Somebody help me!");
    printf("Str '%s' create sucssesful!\n\n", a.Str);

    printf("---Deleting str---\nDel str : '%s'\n", a.Str);
    Delete_string(&a);
    printf("Delete sucsessful\n");
    printf("String becomes: %s\nLenght str = %d\n\n", a.Str, a.len);

    printf("---String comparison ---\n");
    a = Make_string("abcd");
    b = Make_string("aabc");
    Compare(a, b);
    Delete_string(&a);
    Delete_string(&b);
    printf("\n");

    printf("---Copying string---\n");
    a = Make_string("Example_copy-1.");
    printf("String: a = %s\n", a.Str);
    b = Copy_string(a);
    printf("Copy it to b = %s\n\n", b.Str);
    Delete_string(&a);
    Delete_string(&b);

    printf("---String concatenation---\n");
    a = Make_string("Good");
    b = Make_string("news!");
    printf("We have strings: '%s', '%s'\n", a.Str, b.Str);
    c = Concatinate_string(a, b);
    printf("Union: %s\n\n", c.Str);
    Delete_string(&a);
    Delete_string(&b);
    Delete_string(&c);

    printf("---Duplicate---\n");
    a = Make_string("1234_+.");
    printf("String: '%s'\n", a.Str);
    b = Duplication_string(a);
    printf("Duplicating : %s", b.Str);
    Delete_string(&a);
    Delete_string(&b);

    return 0;
}