#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>


// STACK - CHAR //

typedef struct stack_elem { // структура элемента стека
    char value;
    struct stack_elem* next;
} stack_elem;

typedef struct stack { // структура стека
    size_t size;
    stack_elem* body;
} stack;

int size(stack* st) {    // Размер стека
    return st->size;
}

int empty(stack* st) {   // Проверка на пустоту
    return st->size == 0 ? 1 : 0;
}

char top(stack* st) {    // Вывести верхний элемент
    if (!empty(st))
        return st->body->value;
    else{
        printf("Stack is empty\n");
        return 0;
    }
}

void pop(stack* st) {
    if (empty(st)) return;
    stack_elem* tmp;
    tmp = st->body;
    st->body = st->body->next;          // Удаление верхнего элемента
    free(tmp);
    st->size--;
}

void push(stack* st, char value){
    stack_elem* new_elem = (stack_elem*)malloc(sizeof(stack_elem));
    if (!new_elem) {
        perror("malloc() failed!");
        exit(-2);
    }
    new_elem->next = st->body;
    st->body = new_elem;
    st->body->value = value;                    // Добавление элемента в стек
    st->size++;
}

stack* stack_init(stack* st){
    st->size = 0;                       // Init stack 
    st->body = NULL;
}


void stack_del(stack* st){
    if (empty(st)) return;
    stack_elem* tmp;
    while (st->body->next != NULL)           //Delete whole stack
    {
        tmp = st->body;
        st->body = st->body->next;
        free(tmp);
    }
    free(st->body);
}