#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"

typedef struct {
    int id;
    double score;
} Record;

static int fail(const char *name);
static int test_int_stack(void);
static int test_record_stack(void);
static int test_null_stack(void);

static int fail(const char *name)
{
    fprintf(stderr, "FAIL: %s\n", name);
    return 1;
}

static int test_int_stack(void)
{
    Stack *stack;
    int value;
    int output;
    int failures;

    stack = stack_create(sizeof(int));
    if (stack == NULL) {
        return fail("stack create");
    }
    failures = 0;
    if (stack_size(stack) != 0 || !stack_empty(stack) ||
        stack->list == NULL) {
        failures += fail("stack initial state");
    }

    value = 10;
    if (stack_push(stack, &value) != 1) {
        failures += fail("stack push");
    }
    value = 20;
    if (stack_push(stack, &value) != 1) {
        failures += fail("stack push second");
    }
    value = 30;
    if (stack_push(stack, &value) != 1) {
        failures += fail("stack push third");
    }
    if (stack_size(stack) != 3 || stack_empty(stack)) {
        failures += fail("stack size");
    }

    output = 0;
    if (!stack_peek(stack, &output) || output != 30) {
        failures += fail("stack peek");
    }
    output = 0;
    if (!stack_pop(stack, &output) || output != 30) {
        failures += fail("stack pop first");
    }
    output = 0;
    if (!stack_pop(stack, &output) || output != 20) {
        failures += fail("stack pop second");
    }
    output = 0;
    if (!stack_pop(stack, &output) || output != 10) {
        failures += fail("stack pop third");
    }
    if (stack_size(stack) != 0 || !stack_empty(stack)) {
        failures += fail("stack empty after pops");
    }
    output = 9876;
    if (stack_pop(stack, &output) != 0 || output != 9876) {
        failures += fail("stack pop empty");
    }
    if (stack_peek(stack, &output) != 0 || output != 9876) {
        failures += fail("stack peek empty");
    }

    stack_free(stack);
    return failures;
}

static int test_record_stack(void)
{
    Stack *stack;
    Record input;
    Record output;
    int failures;

    stack = stack_create(sizeof(Record));
    if (stack == NULL) {
        return fail("record stack create");
    }
    failures = 0;
    input.id = 7;
    input.score = 1.5;
    if (!stack_push(stack, &input)) {
        stack_free(stack);
        return fail("record push");
    }
    input.id = 99;
    input.score = 9.0;
    output.id = 0;
    output.score = 0.0;
    if (!stack_peek(stack, &output) ||
        output.id != 7 || output.score != 1.5) {
        failures += fail("record copy ownership");
    }

    input.id = 2;
    input.score = 2.5;
    if (!stack_push(stack, &input)) {
        failures += fail("record push second");
    }
    output.id = 0;
    output.score = 0.0;
    if (!stack_pop(stack, &output) ||
        output.id != 2 || output.score != 2.5) {
        failures += fail("record pop first");
    }
    output.id = 0;
    output.score = 0.0;
    if (!stack_pop(stack, &output) ||
        output.id != 7 || output.score != 1.5) {
        failures += fail("record pop second");
    }

    stack_free(stack);
    return failures;
}

static int test_null_stack(void)
{
    int value;
    int failures;

    failures = 0;
    value = 1;
    if (stack_push(NULL, &value) != 0 ||
        stack_pop(NULL, &value) != 0 ||
        stack_peek(NULL, &value) != 0 ||
        stack_size(NULL) != 0) {
        failures += fail("null stack operations");
    }
    stack_free(NULL);
    return failures;
}

int main(void)
{
    int failures;

    failures = 0;
    failures += test_int_stack();
    failures += test_record_stack();
    failures += test_null_stack();

    if (failures == 0) {
        printf("stack: all tests passed\n");
        return EXIT_SUCCESS;
    }

    fprintf(stderr, "stack: %d test(s) failed\n", failures);
    return EXIT_FAILURE;
}
