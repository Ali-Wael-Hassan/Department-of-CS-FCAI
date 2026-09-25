#include <stdlib.h>

#include "Stack.h"

Stack *stack_create(size_t element_size) {
    Stack *stack = malloc(sizeof(*stack));

    if (stack == NULL)
        return NULL;

    stack->list = linkedlist_create(element_size);
    if (stack->list == NULL) {
        free(stack);
        return NULL;
    }

    return stack;
}

void stack_free(Stack *stack) {
    if (stack == NULL)
        return;

    if (stack->list != NULL) {
        linkedlist_free(stack->list);
    }

    free(stack);
}

int stack_push(Stack *stack, const void *data) {
    if (stack == NULL || stack->list == NULL)
        return 0;

    return linkedlist_push_front(stack->list, data);
}

int stack_pop(Stack *stack, void *out) {
    if (stack == NULL || stack->list == NULL)
        return 0;

    return linkedlist_pop_front(stack->list, out);
}

int stack_peek(const Stack *stack, void *out) {
    if (stack == NULL || stack->list == NULL)
        return 0;

    return linkedlist_get(stack->list, 0, out);
}

size_t stack_size(const Stack *stack) {
    if (stack == NULL || stack->list == NULL)
        return 0;

    return linkedlist_size(stack->list);
}

int stack_empty(const Stack *stack) {
    if (stack == NULL || stack->list == NULL)
        return 0;

    return linkedlist_empty(stack->list);
}