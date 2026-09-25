#include <stdio.h>
#include <stdlib.h>

#include "Vector.h"

static int fail(const char *name);
static int test_init_and_growth(void);
static int test_access(void);
static int test_pop_and_clear(void);
static int test_free_and_null(void);
static int test_overflow_guard(void);

static int fail(const char *name)
{
    fprintf(stderr, "FAIL: %s\n", name);
    return 1;
}

static int test_init_and_growth(void)
{
    Vector v;
    size_t i;
    int value;
    int failures;

    vector_init(&v);
    failures = 0;
    if (v.size != 0) {
        failures += fail("init size");
    }
    if (v.data == NULL) {
        vector_free(&v);
        return failures + fail("init allocation");
    }
    if (v.capacity == 0) {
        failures += fail("init capacity");
    }

    for (i = 0; i < 100; ++i) {
        if (!vector_push(&v, (int) i)) {
            failures += fail("push");
            break;
        }
    }
    if (v.size != 100) {
        failures += fail("growth size");
    }
    if (v.capacity < v.size) {
        failures += fail("growth capacity");
    }
    for (i = 0; i < v.size; ++i) {
        value = -1;
        if (!vector_get(&v, i, &value) || value != (int) i) {
            failures += fail("push/get round trip");
        }
    }

    vector_free(&v);
    return failures;
}

static int test_access(void)
{
    Vector v;
    int value;
    int failures;

    vector_init(&v);
    failures = 0;
    if (!vector_push(&v, 10) ||
        !vector_push(&v, 20) ||
        !vector_push(&v, 30)) {
        vector_free(&v);
        return fail("access setup");
    }

    value = 0;
    if (!vector_get(&v, 1, &value) || value != 20) {
        failures += fail("vector_get");
    }
    if (!vector_set(&v, 1, 99) ||
        !vector_get(&v, 1, &value) || value != 99) {
        failures += fail("vector_set");
    }
    if (vector_get(&v, 0, NULL) != 0) {
        failures += fail("vector_get null output");
    }
    if (vector_get(&v, 3, &value) != 0 || value != 99) {
        failures += fail("vector_get bounds");
    }
    if (vector_set(&v, 3, 1) != 0) {
        failures += fail("vector_set bounds");
    }

    vector_free(&v);
    return failures;
}

static int test_pop_and_clear(void)
{
    Vector v;
    int value;
    int *data;
    size_t capacity;
    int failures;

    vector_init(&v);
    failures = 0;
    if (!vector_push(&v, 1) ||
        !vector_push(&v, 2) ||
        !vector_push(&v, 3)) {
        vector_free(&v);
        return fail("pop setup");
    }

    value = 0;
    if (!vector_pop(&v, &value) || value != 3 || v.size != 2) {
        failures += fail("vector_pop value");
    }
    if (!vector_pop(&v, NULL) || v.size != 1) {
        failures += fail("vector_pop null output");
    }
    value = 1234;
    if (!vector_pop(&v, &value) || value != 1 || v.size != 0) {
        failures += fail("vector_pop last value");
    }
    value = 4321;
    if (vector_pop(&v, &value) != 0 || value != 4321) {
        failures += fail("vector_pop empty");
    }

    if (!vector_push(&v, 4) || !vector_push(&v, 5)) {
        vector_free(&v);
        return failures + fail("clear setup");
    }
    data = v.data;
    capacity = v.capacity;
    vector_clear(&v);
    if (v.size != 0 || v.data != data || v.capacity != capacity) {
        failures += fail("vector_clear");
    }
    if (vector_pop(&v, &value) != 0) {
        failures += fail("pop after clear");
    }
    if (!vector_push(&v, 6)) {
        failures += fail("push after clear");
    } else {
        value = 0;
        if (!vector_get(&v, 0, &value) || value != 6) {
            failures += fail("get after clear");
        }
    }

    vector_free(&v);
    return failures;
}

static int test_free_and_null(void)
{
    Vector v;
    int value;
    int failures;

    vector_init(&v);
    failures = 0;
    if (!vector_push(&v, 7)) {
        vector_free(&v);
        return fail("free setup");
    }
    vector_free(&v);
    if (v.data != NULL || v.size != 0 || v.capacity != 0) {
        failures += fail("vector_free state");
    }
    vector_free(&v);
    if (!vector_push(&v, 8) ||
        !vector_get(&v, 0, &value) || value != 8) {
        failures += fail("push after free");
    }
    vector_free(&v);

    vector_init(NULL);
    if (vector_push(NULL, 1) != 0 ||
        vector_pop(NULL, &value) != 0 ||
        vector_get(NULL, 0, &value) != 0 ||
        vector_set(NULL, 0, 1) != 0) {
        failures += fail("null vector arguments");
    }
    vector_clear(NULL);
    vector_free(NULL);

    return failures;
}

static int test_overflow_guard(void)
{
    Vector v;
    int *data;
    int failures;

    vector_init(&v);
    failures = 0;
    if (v.data == NULL) {
        return fail("overflow setup");
    }
    data = v.data;
    v.size = (size_t) -1;
    v.capacity = (size_t) -1;
    if (vector_push(&v, 1) != 0) {
        failures += fail("growth overflow");
    }
    if (v.data != data || v.size != (size_t) -1) {
        failures += fail("growth overflow state");
    }
    v.size = 0;
    v.capacity = 0;
    if (!vector_push(&v, 9)) {
        failures += fail("push after overflow state");
    }
    vector_free(&v);

    return failures;
}

int main(void)
{
    int failures;

    failures = 0;
    failures += test_init_and_growth();
    failures += test_access();
    failures += test_pop_and_clear();
    failures += test_free_and_null();
    failures += test_overflow_guard();

    if (failures == 0) {
        printf("vector: all tests passed\n");
        return EXIT_SUCCESS;
    }

    fprintf(stderr, "vector: %d test(s) failed\n", failures);
    return EXIT_FAILURE;
}