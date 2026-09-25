#include <stdio.h>
#include <stdlib.h>

#include "Linkedlist.h"

typedef struct {
    int id;
    double score;
} Record;

static int fail(const char *name);
static int check_int(const LinkedList *list, size_t index, int expected,
                     const char *name);
static int test_int_list(void);
static int test_record_list(void);
static int test_clear_and_free(void);
static int test_null_and_bounds(void);

static int fail(const char *name)
{
    fprintf(stderr, "FAIL: %s\n", name);
    return 1;
}

static int check_int(const LinkedList *list, size_t index, int expected,
                     const char *name)
{
    int actual;

    actual = -1;
    if (!linkedlist_get(list, index, &actual) || actual != expected) {
        return fail(name);
    }

    return 0;
}

static int test_int_list(void)
{
    LinkedList *list;
    int value;
    int output;
    size_t i;
    int failures;

    list = linkedlist_create(sizeof(int));
    if (list == NULL) {
        return fail("int create");
    }
    failures = 0;
    if (linkedlist_size(list) != 0 || !linkedlist_empty(list) ||
        list->head != NULL || list->element_size != sizeof(int)) {
        failures += fail("int initial state");
    }

    for (i = 0; i < 5; ++i) {
        value = (int) i;
        if (!linkedlist_push_back(list, &value)) {
            failures += fail("int push_back");
            break;
        }
    }
    for (i = 0; i < linkedlist_size(list); ++i) {
        failures += check_int(list, i, (int) i, "int push_back order");
    }

    value = 99;
    if (!linkedlist_push_front(list, &value)) {
        failures += fail("int push_front");
    } else {
        failures += check_int(list, 0, 99, "int push_front order");
    }
    value = 100;
    if (!linkedlist_push_back(list, &value)) {
        failures += fail("int push_back end");
    } else {
        failures += check_int(list, linkedlist_size(list) - 1, 100,
                              "int push_back end order");
    }
    if (linkedlist_size(list) != 7) {
        failures += fail("int size");
    }

    value = 55;
    if (!linkedlist_set(list, 2, &value)) {
        failures += fail("int set");
    } else {
        failures += check_int(list, 2, 55, "int set value");
    }
    output = 4321;
    if (linkedlist_get(list, 7, &output) != 0 || output != 4321) {
        failures += fail("int get bounds");
    }
    if (linkedlist_set(list, 7, &value) != 0) {
        failures += fail("int set bounds");
    }

    output = 0;
    if (!linkedlist_pop_front(list, &output) || output != 99) {
        failures += fail("int pop_front");
    }
    output = 0;
    if (!linkedlist_pop_back(list, &output) || output != 100) {
        failures += fail("int pop_back");
    }
    if (linkedlist_size(list) != 5) {
        failures += fail("int size after pops");
    }
    failures += check_int(list, 0, 0, "int order after pop_front");
    failures += check_int(list, 4, 4, "int order after pop_back");

    linkedlist_free(list);
    return failures;
}

static int test_record_list(void)
{
    LinkedList *list;
    Record input;
    Record output;
    int failures;

    list = linkedlist_create(sizeof(Record));
    if (list == NULL) {
        return fail("record create");
    }
    failures = 0;
    input.id = 7;
    input.score = 1.5;
    if (!linkedlist_push_back(list, &input)) {
        linkedlist_free(list);
        return fail("record push_back");
    }
    input.id = 99;
    input.score = 9.0;
    output.id = 0;
    output.score = 0.0;
    if (!linkedlist_get(list, 0, &output) ||
        output.id != 7 || output.score != 1.5) {
        failures += fail("record copy ownership");
    }

    input.id = 2;
    input.score = 2.5;
    if (!linkedlist_push_front(list, &input)) {
        failures += fail("record push_front");
    } else {
        output.id = 0;
        output.score = 0.0;
        if (!linkedlist_get(list, 0, &output) ||
            output.id != 2 || output.score != 2.5) {
            failures += fail("record front order");
        }
    }

    input.id = 3;
    input.score = 3.5;
    if (!linkedlist_set(list, 1, &input)) {
        failures += fail("record set");
    }
    output.id = 0;
    output.score = 0.0;
    if (!linkedlist_pop_front(list, &output) ||
        output.id != 2 || output.score != 2.5) {
        failures += fail("record pop_front");
    }
    output.id = 0;
    output.score = 0.0;
    if (!linkedlist_pop_back(list, &output) ||
        output.id != 3 || output.score != 3.5) {
        failures += fail("record pop_back");
    }
    if (!linkedlist_empty(list)) {
        failures += fail("record empty");
    }

    linkedlist_free(list);
    return failures;
}

static int test_clear_and_free(void)
{
    LinkedList *list;
    int value;
    int output;
    int failures;

    list = linkedlist_create(sizeof(int));
    if (list == NULL) {
        return fail("clear create");
    }
    failures = 0;
    value = 1;
    if (!linkedlist_push_back(list, &value) ||
        !linkedlist_push_back(list, &value)) {
        linkedlist_free(list);
        return fail("clear setup");
    }
    linkedlist_clear(list);
    if (linkedlist_size(list) != 0 || !linkedlist_empty(list) ||
        list->head != NULL) {
        failures += fail("clear state");
    }
    output = 1234;
    if (linkedlist_pop_front(list, &output) != 0 || output != 1234) {
        failures += fail("pop after clear");
    }
    value = 5;
    if (!linkedlist_push_back(list, &value) ||
        !linkedlist_get(list, 0, &output) || output != 5) {
        failures += fail("push after clear");
    }
    linkedlist_free(list);
    linkedlist_free(NULL);
    return failures;
}

static int test_null_and_bounds(void)
{
    LinkedList *list;
    int value;
    int output;
    int failures;

    failures = 0;
    value = 11;
    if (linkedlist_push_front(NULL, &value) != 0 ||
        linkedlist_pop_front(NULL, &value) != 0 ||
        linkedlist_pop_back(NULL, &value) != 0 ||
        linkedlist_get(NULL, 0, &value) != 0 ||
        linkedlist_set(NULL, 0, &value) != 0) {
        failures += fail("null list operations");
    }
    if (linkedlist_size(NULL) != 0) {
        failures += fail("null list size");
    }
    linkedlist_clear(NULL);

    list = linkedlist_create(sizeof(int));
    if (list == NULL) {
        return failures + fail("bounds create");
    }
    output = 9876;
    if (!linkedlist_push_back(list, &value)) {
        linkedlist_free(list);
        return failures + fail("bounds setup");
    }
    if (linkedlist_pop_front(list, NULL) != 0 ||
        linkedlist_pop_back(list, NULL) != 0 ||
        linkedlist_get(list, 0, NULL) != 0 ||
        linkedlist_set(list, 0, NULL) != 0 ||
        linkedlist_get(list, 1, &output) != 0 ||
        linkedlist_set(list, 1, &value) != 0) {
        failures += fail("bounds and null output");
    }
    if (output != 9876) {
        failures += fail("failed operation changed output");
    }
    linkedlist_free(list);
    return failures;
}

int main(void)
{
    int failures;

    failures = 0;
    failures += test_int_list();
    failures += test_record_list();
    failures += test_clear_and_free();
    failures += test_null_and_bounds();

    if (failures == 0) {
        printf("linked list: all tests passed\n");
        return EXIT_SUCCESS;
    }

    fprintf(stderr, "linked list: %d test(s) failed\n", failures);
    return EXIT_FAILURE;
}
