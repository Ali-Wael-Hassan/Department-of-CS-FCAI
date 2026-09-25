#ifndef STACK_H
#define STACK_H

#include "Linkedlist.h"

typedef struct {
    LinkedList *list;
} Stack;

Stack *stack_create(size_t element_size);

void stack_free(Stack *stack);

int stack_push(Stack *stack, const void *data);
int stack_pop(Stack *stack, void *out);

int stack_peek(const Stack *stack, void *out);

size_t stack_size(const Stack *stack);
int stack_empty(const Stack *stack);

#endif