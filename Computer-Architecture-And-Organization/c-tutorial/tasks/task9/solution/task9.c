#include <stdio.h>
#include <stdlib.h>

#include "HashTable.h"

static int fail(const char *name);
static size_t constant_hash(const char *key);
static int test_basic_table(void);
static int test_linear_probing(void);
static int test_resize_and_null(void);

static int fail(const char *name)
{
    fprintf(stderr, "FAIL: %s\n", name);
    return 1;
}

static size_t constant_hash(const char *key)
{
    (void) key;
    return 0;
}

static int test_basic_table(void)
{
    HashTable *table;
    int value_one;
    int value_two;
    int value_three;
    int replacement;
    char key[6];
    void *found;
    int failures;

    table = hash_table_create(8);
    if (table == NULL) {
        return fail("basic create");
    }
    failures = 0;
    value_one = 1;
    value_two = 2;
    value_three = 3;
    replacement = 4;

    key[0] = 'a';
    key[1] = 'l';
    key[2] = 'p';
    key[3] = 'h';
    key[4] = 'a';
    key[5] = '\0';
    if (!hash_table_insert(table, key, &value_one)) {
        failures += fail("insert key copy");
    }
    key[0] = 'z';
    found = hash_table_find(table, "alpha");
    if (!hash_table_contains(table, "alpha") || found != &value_one) {
        failures += fail("key ownership");
    }

    if (!hash_table_insert(table, "beta", &value_two) ||
        !hash_table_insert(table, "null", NULL)) {
        failures += fail("basic inserts");
    }
    if (hash_table_size(table) != 3 || hash_table_capacity(table) < 8) {
        failures += fail("basic size");
    }
    if (!hash_table_contains(table, "null") ||
        hash_table_find(table, "null") != NULL) {
        failures += fail("null value");
    }
    if (!hash_table_insert(table, "beta", &value_three) ||
        hash_table_size(table) != 3) {
        failures += fail("update existing key");
    }
    found = hash_table_find(table, "beta");
    if (found != &value_three) {
        failures += fail("updated value");
    }
    if (hash_table_contains(table, "missing") ||
        hash_table_find(table, "missing") != NULL) {
        failures += fail("missing key");
    }

    replacement = 99;
    if (!hash_table_insert(table, "gamma", (void *) &replacement) ||
        hash_table_find(table, "gamma") != (void *) &replacement) {
        failures += fail("void pointer value");
    }
    if (!hash_table_remove(table, "alpha") ||
        hash_table_contains(table, "alpha") ||
        hash_table_size(table) != 3) {
        failures += fail("remove key");
    }
    if (hash_table_remove(table, "alpha") != 0) {
        failures += fail("remove missing key");
    }
    if (!hash_table_remove(table, "null") ||
        hash_table_contains(table, "null") || hash_table_size(table) != 2) {
        failures += fail("remove null value");
    }

    hash_table_clear(table);
    if (hash_table_size(table) != 0 || hash_table_contains(table, "beta") ||
        hash_table_find(table, "beta") != NULL) {
        failures += fail("clear table");
    }
    if (!hash_table_insert(table, "after-clear", &value_one) ||
        hash_table_size(table) != 1) {
        failures += fail("insert after clear");
    }

    hash_table_free(table);
    return failures;
}

static int test_linear_probing(void)
{
    HashTable *table;
    const char *keys[20];
    int values[20];
    int replacement;
    size_t i;
    int failures;

    keys[0] = "key-00";
    keys[1] = "key-01";
    keys[2] = "key-02";
    keys[3] = "key-03";
    keys[4] = "key-04";
    keys[5] = "key-05";
    keys[6] = "key-06";
    keys[7] = "key-07";
    keys[8] = "key-08";
    keys[9] = "key-09";
    keys[10] = "key-10";
    keys[11] = "key-11";
    keys[12] = "key-12";
    keys[13] = "key-13";
    keys[14] = "key-14";
    keys[15] = "key-15";
    keys[16] = "key-16";
    keys[17] = "key-17";
    keys[18] = "key-18";
    keys[19] = "key-19";

    table = hash_table_create_with_hash(8, constant_hash);
    if (table == NULL) {
        return fail("collision create");
    }
    failures = 0;
    for (i = 0; i < 20; ++i) {
        values[i] = (int) i * 3;
        if (!hash_table_insert(table, keys[i], &values[i])) {
            failures += fail("collision insert");
            break;
        }
    }
    if (hash_table_size(table) != 20 || hash_table_capacity(table) <= 8) {
        failures += fail("collision growth");
    }
    for (i = 0; i < 20; ++i) {
        if (!hash_table_contains(table, keys[i]) ||
            hash_table_find(table, keys[i]) != &values[i]) {
            failures += fail("collision lookup");
        }
    }

    if (!hash_table_remove(table, keys[1])) {
        failures += fail("tombstone remove");
    }
    replacement = 1234;
    if (!hash_table_insert(table, "replacement", &replacement) ||
        hash_table_find(table, "replacement") != &replacement) {
        failures += fail("tombstone reuse");
    }
    if (hash_table_contains(table, keys[1]) ||
        !hash_table_contains(table, keys[0]) ||
        !hash_table_contains(table, keys[2])) {
        failures += fail("tombstone cluster");
    }
    if (!hash_table_remove(table, keys[0]) ||
        !hash_table_insert(table, keys[0], &replacement) ||
        hash_table_find(table, keys[0]) != &replacement) {
        failures += fail("cluster reinsertion");
    }
    for (i = 2; i < 20; ++i) {
        if (!hash_table_contains(table, keys[i]) ||
            hash_table_find(table, keys[i]) != &values[i]) {
            failures += fail("post-tombstone lookup");
        }
    }

    hash_table_free(table);
    return failures;
}

static int test_resize_and_null(void)
{
    HashTable *table;
    int values[3];
    void *found;
    size_t old_capacity;
    int failures;

    table = hash_table_create(8);
    if (table == NULL) {
        return fail("resize create");
    }
    failures = 0;
    values[0] = 10;
    values[1] = 20;
    values[2] = 30;
    if (!hash_table_insert(table, "a", &values[0]) ||
        !hash_table_insert(table, "b", &values[1]) ||
        !hash_table_insert(table, "c", &values[2])) {
        hash_table_free(table);
        return fail("resize setup");
    }
    old_capacity = hash_table_capacity(table);
    if (!hash_table_resize(table, 32) ||
        hash_table_capacity(table) != 32 ||
        hash_table_size(table) != 3) {
        failures += fail("manual resize");
    }
    found = hash_table_find(table, "b");
    if (found != &values[1]) {
        failures += fail("resize lookup");
    }
    if (hash_table_resize(table, 4) != 0 ||
        hash_table_resize(table, 2) != 0 ||
        hash_table_resize(NULL, 8) != 0) {
        failures += fail("invalid resize");
    }
    if (hash_table_capacity(table) != 32 ||
        hash_table_size(table) != 3) {
        failures += fail("resize unchanged after failure");
    }
    if (old_capacity == 0) {
        failures += fail("initial capacity");
    }

    hash_table_free(table);
    table = hash_table_create_with_hash(0, NULL);
    if (table == NULL) {
        return failures + fail("default hash create");
    }
    if (!hash_table_insert(table, "default", &values[0]) ||
        !hash_table_contains(table, "default") ||
        hash_table_find(table, "default") != &values[0]) {
        failures += fail("default hash");
    }
    hash_table_free(table);

    if (hash_table_insert(NULL, "key", &values[0]) != 0 ||
        hash_table_find(NULL, "key") != NULL ||
        hash_table_contains(NULL, "key") != 0 ||
        hash_table_remove(NULL, "key") != 0 ||
        hash_table_size(NULL) != 0 ||
        hash_table_capacity(NULL) != 0) {
        failures += fail("null table operations");
    }
    hash_table_clear(NULL);
    hash_table_free(NULL);
    hash_table_insert(NULL, NULL, &values[0]);

    return failures;
}

int main(void)
{
    int failures;

    failures = 0;
    failures += test_basic_table();
    failures += test_linear_probing();
    failures += test_resize_and_null();

    if (failures == 0) {
        printf("hash table: all tests passed\n");
        return EXIT_SUCCESS;
    }

    fprintf(stderr, "hash table: %d test(s) failed\n", failures);
    return EXIT_FAILURE;
}
