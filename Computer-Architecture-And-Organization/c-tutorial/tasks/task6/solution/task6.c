#include <stdio.h>
#include <stdlib.h>

#include "Vector.h"

typedef struct {
    int id;
    double score;
} Record;

static int fail(const char *name);
static int test_int_vector(void);
static int test_generic_record_vector(void);
static int test_bounds_and_null(void);
static int test_clear_and_free(void);
static int test_growth_overflow(void);

static int fail(const char *name)
{
    fprintf(stderr, "FAIL: %s\n", name);
    return 1;
}

static int test_int_vector(void)
{
    Vector v;
    size_t i;
    int value;
    int output;
    int failures;

    vector_init(&v, sizeof(int));
    failures = 0;
    if (v.size != 0 || v.element_size != sizeof(int)) {
        failures += fail("int init");
    }

    for (i = 0; i < 100; ++i) {
        value = (int) i;
        if (!vector_push(&v, &value)) {
            failures += fail("int push");
            break;
        }
    }
    if (v.size != 100 || v.capacity < v.size) {
        failures += fail("int growth");
    }
    for (i = 0; i < v.size; ++i) {
        output = -1;
        if (!vector_get(&v, i, &output) || output != (int) i) {
            failures += fail("int get");
        }
    }

    value = 1234;
    output = 0;
    if (!vector_set(&v, 0, &value) ||
        !vector_get(&v, 0, &output) || output != 1234) {
        failures += fail("int set");
    }

    output = 0;
    if (!vector_pop(&v, &output) || output != 99 || v.size != 99) {
        failures += fail("int pop");
    }

    vector_free(&v);
    return failures;
}

static int test_generic_record_vector(void)
{
    Vector v;
    Record input;
    Record output;
    size_t i;
    int failures;

    vector_init(&v, sizeof(Record));
    failures = 0;
    if (v.element_size != sizeof(Record)) {
        failures += fail("record init");
    }

    for (i = 0; i < 20; ++i) {
        input.id = (int) i;
        input.score = (double) i / 2.0;
        if (!vector_push(&v, &input)) {
            failures += fail("record push");
            break;
        }
    }
    for (i = 0; i < v.size; ++i) {
        output.id = -1;
        output.score = -1.0;
        if (!vector_get(&v, i, &output) ||
            output.id != (int) i ||
            output.score != (double) i / 2.0) {
            failures += fail("record get");
        }
    }

    input.id = 99;
    input.score = 4.5;
    output.id = 0;
    output.score = 0.0;
    if (!vector_set(&v, 1, &input) ||
        !vector_get(&v, 1, &output) ||
        output.id != 99 || output.score != 4.5) {
        failures += fail("record set");
    }

    if (!vector_pop(&v, &output) || output.id != 19) {
        failures += fail("record pop");
    }

    vector_free(&v);
    return failures;
}

static int test_bounds_and_null(void)
{
    Vector v;
    Vector invalid;
    int value;
    int output;
    int failures;

    vector_init(&v, sizeof(int));
    vector_init(&invalid, 0);
    failures = 0;
    value = 7;
    if (!vector_push(&v, &value)) {
        vector_free(&v);
        vector_free(&invalid);
        return fail("bounds setup");
    }
    if (vector_push(&invalid, &value) != 0) {
        failures += fail("zero element size push");
    }
    if (vector_push(&v, NULL) != 0) {
        failures += fail("null value push");
    }
    if (vector_get(&v, 0, NULL) != 0) {
        failures += fail("null output get");
    }
    if (vector_set(&v, 0, NULL) != 0) {
        failures += fail("null value set");
    }

    output = 4321;
    if (vector_get(&v, 1, &output) != 0 || output != 4321) {
        failures += fail("get bounds");
    }
    if (vector_set(&v, 1, &value) != 0) {
        failures += fail("set bounds");
    }
    if (vector_get(NULL, 0, &output) != 0 ||
        vector_set(NULL, 0, &value) != 0 ||
        vector_push(NULL, &value) != 0 ||
        vector_pop(NULL, &output) != 0) {
        failures += fail("null vector");
    }
    vector_init(NULL, sizeof(int));
    vector_clear(NULL);
    vector_free(NULL);

    vector_free(&invalid);
    vector_free(&v);
    return failures;
}

static int test_clear_and_free(void)
{
    Vector v;
    int value;
    int output;
    void *data;
    size_t capacity;
    size_t element_size;
    int failures;

    vector_init(&v, sizeof(int));
    failures = 0;
    value = 1;
    if (!vector_push(&v, &value)) {
        vector_free(&v);
        return fail("clear setup");
    }
    value = 2;
    if (!vector_push(&v, &value)) {
        vector_free(&v);
        return fail("clear setup push");
    }
    data = v.data;
    capacity = v.capacity;
    element_size = v.element_size;
    vector_clear(&v);
    if (v.size != 0 || v.data != data || v.capacity != capacity ||
        v.element_size != element_size) {
        failures += fail("clear state");
    }
    if (vector_pop(&v, &output) != 0) {
        failures += fail("pop after clear");
    }

    value = 3;
    if (!vector_push(&v, &value) || !vector_get(&v, 0, &output) ||
        output != 3) {
        failures += fail("push after clear");
    }
    vector_free(&v);
    if (v.data != NULL || v.size != 0 || v.capacity != 0) {
        failures += fail("free state");
    }
    vector_free(&v);

    value = 4;
    if (!vector_push(&v, &value) || !vector_get(&v, 0, &output) ||
        output != 4) {
        failures += fail("push after free");
    }
    vector_free(&v);
    return failures;
}

static int test_growth_overflow(void)
{
    Vector v;
    void *data;
    int value;
    int failures;

    vector_init(&v, sizeof(int));
    failures = 0;
    if (v.data == NULL) {
        return fail("overflow setup");
    }
    data = v.data;
    v.size = (size_t) -1;
    v.capacity = (size_t) -1;
    value = 5;
    if (vector_push(&v, &value) != 0) {
        failures += fail("growth overflow");
    }
    if (v.data != data || v.size != (size_t) -1) {
        failures += fail("overflow state");
    }
    v.size = 0;
    v.capacity = 0;
    if (!vector_push(&v, &value)) {
        failures += fail("push after overflow");
    }
    vector_free(&v);
    return failures;
}

int main(void)
{
    int failures;

    failures = 0;
    failures += test_int_vector();
    failures += test_generic_record_vector();
    failures += test_bounds_and_null();
    failures += test_clear_and_free();
    failures += test_growth_overflow();

    if (failures == 0) {
        printf("generic vector: all tests passed\n");
        return EXIT_SUCCESS;
    }

    fprintf(stderr, "generic vector: %d test(s) failed\n", failures);
    return EXIT_FAILURE;
}
