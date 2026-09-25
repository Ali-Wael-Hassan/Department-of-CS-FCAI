#include <stdlib.h>
#include <string.h>

#include "HashTable.h"

#define HASH_TABLE_MIN_CAPACITY 8
#define ENTRY_EMPTY 0
#define ENTRY_OCCUPIED 1
#define ENTRY_TOMBSTONE 2

typedef struct {
    char *key;
    void *value;
    unsigned char state;
} HashEntry;

struct HashTable {
    HashEntry *entries;
    size_t capacity;
    size_t size;
    size_t tombstones;
    HashFunction hash;
};

static size_t default_hash(const char *key);
static size_t next_index(size_t index, size_t capacity);
static void locate(const HashTable *table, const char *key, size_t *slot, int *found);
static int should_resize(const HashTable *table);
static HashTable *create_table(size_t initial_capacity, HashFunction hash);

static size_t default_hash(const char *key) {
    size_t hash;

    hash = 5381;
    while (*key != '\0') {
        hash = hash * 33u + (size_t) (unsigned char) *key;
        ++key;
    }

    return hash;
}

static size_t next_index(size_t index, size_t capacity) {
    ++index;
    if (index == capacity) {
        return 0;
    }

    return index;
}

static void locate(const HashTable *table, const char *key, size_t *slot, int *found) {
    size_t index;
    size_t first_deleted;
    size_t steps;
    int have_deleted;

    *slot = table->capacity;
    *found = 0;
    first_deleted = table->capacity;
    have_deleted = 0;
    index = table->hash(key) % table->capacity;

    for (steps = 0; steps < table->capacity; ++steps) {
        if (table->entries[index].state == ENTRY_OCCUPIED) {
            if (strcmp(table->entries[index].key, key) == 0) {
                *slot = index;
                *found = 1;
                return;
            }
        } else if (table->entries[index].state == ENTRY_TOMBSTONE) {
            if (!have_deleted) {
                first_deleted = index;
                have_deleted = 1;
            }
        } else {
            if (have_deleted) {
                *slot = first_deleted;
            } else {
                *slot = index;
            }
            return;
        }
        index = next_index(index, table->capacity);
    }

    if (have_deleted) {
        *slot = first_deleted;
    }
}

static int should_resize(const HashTable *table) {
    size_t used;
    size_t threshold;

    if (table->size == (size_t) -1 || table->size > (size_t) -1 - table->tombstones) {
        return 1;
    }

    used = table->size + table->tombstones + 1;
    threshold = table->capacity - table->capacity / 4;

    return used >= threshold;
}

static HashTable *create_table(size_t initial_capacity, HashFunction hash) {
    HashTable *table;
    size_t capacity;

    capacity = initial_capacity;
    if (capacity < HASH_TABLE_MIN_CAPACITY) {
        capacity = HASH_TABLE_MIN_CAPACITY;
    }
    if (capacity > (size_t) -1 / sizeof(HashEntry)) {
        return NULL;
    }

    table = malloc(sizeof(*table));
    if (table == NULL) {
        return NULL;
    }

    table->entries = calloc(capacity, sizeof(*table->entries));
    if (table->entries == NULL) {
        free(table);
        return NULL;
    }

    table->capacity = capacity;
    table->size = 0;
    table->tombstones = 0;
    table->hash = hash;

    return table;
}

HashTable *hash_table_create(size_t initial_capacity) {
    return create_table(initial_capacity, default_hash);
}

HashTable *hash_table_create_with_hash(size_t initial_capacity, HashFunction hash) {
    if (hash == NULL) {
        hash = default_hash;
    }

    return create_table(initial_capacity, hash);
}

void hash_table_free(HashTable *table) {
    if (table == NULL) {
        return;
    }

    hash_table_clear(table);
    free(table->entries);
    free(table);
}

int hash_table_insert(HashTable *table, const char *key, void *value) {
    char *key_copy;
    size_t key_length;
    size_t slot;
    int found;

    if (table == NULL || key == NULL) {
        return 0;
    }

    locate(table, key, &slot, &found);
    if (found) {
        table->entries[slot].value = value;
        return 1;
    }

    if (should_resize(table)) {
        if (table->capacity > (size_t) -1 / 2 || !hash_table_resize(table, table->capacity * 2)) {
            return 0;
        }
        locate(table, key, &slot, &found);
        if (found) {
            table->entries[slot].value = value;
            return 1;
        }
    }

    if (slot >= table->capacity) {
        return 0;
    }

    key_length = strlen(key);
    if (key_length == (size_t) -1) {
        return 0;
    }
    key_copy = malloc(key_length + 1);
    if (key_copy == NULL) {
        return 0;
    }
    memcpy(key_copy, key, key_length + 1);

    if (table->entries[slot].state == ENTRY_TOMBSTONE) {
        --table->tombstones;
    }
    table->entries[slot].key = key_copy;
    table->entries[slot].value = value;
    table->entries[slot].state = ENTRY_OCCUPIED;
    ++table->size;

    return 1;
}

void *hash_table_find(const HashTable *table, const char *key) {
    size_t slot;
    int found;

    if (table == NULL || key == NULL) {
        return NULL;
    }

    locate(table, key, &slot, &found);
    if (!found || slot >= table->capacity) {
        return NULL;
    }

    return table->entries[slot].value;
}

int hash_table_contains(const HashTable *table, const char *key) {
    size_t slot;
    int found;

    if (table == NULL || key == NULL) {
        return 0;
    }

    locate(table, key, &slot, &found);

    return found && slot < table->capacity;
}

int hash_table_remove(HashTable *table, const char *key) {
    size_t slot;
    int found;

    if (table == NULL || key == NULL) {
        return 0;
    }

    locate(table, key, &slot, &found);
    if (!found || slot >= table->capacity) {
        return 0;
    }

    free(table->entries[slot].key);
    table->entries[slot].key = NULL;
    table->entries[slot].value = NULL;
    table->entries[slot].state = ENTRY_TOMBSTONE;
    --table->size;
    ++table->tombstones;

    return 1;
}

int hash_table_resize(HashTable *table, size_t new_capacity) {
    HashEntry *new_entries;
    size_t i;
    size_t index;
    size_t steps;

    if (table == NULL || new_capacity < HASH_TABLE_MIN_CAPACITY ||
        new_capacity < table->size ||
        new_capacity > (size_t) -1 / sizeof(HashEntry)) {
        return 0;
    }

    new_entries = calloc(new_capacity, sizeof(*new_entries));
    if (new_entries == NULL) {
        return 0;
    }

    for (i = 0; i < table->capacity; ++i) {
        if (table->entries[i].state == ENTRY_OCCUPIED) {
            index = table->hash(table->entries[i].key) % new_capacity;
            for (steps = 0; steps < new_capacity; ++steps) {
                if (new_entries[index].state == ENTRY_EMPTY) {
                    new_entries[index] = table->entries[i];
                    break;
                }
                index = next_index(index, new_capacity);
            }
        }
    }

    free(table->entries);
    table->entries = new_entries;
    table->capacity = new_capacity;
    table->tombstones = 0;

    return 1;
}

void hash_table_clear(HashTable *table) {
    size_t i;

    if (table == NULL) {
        return;
    }

    for (i = 0; i < table->capacity; ++i) {
        if (table->entries[i].state == ENTRY_OCCUPIED) {
            free(table->entries[i].key);
        }
        table->entries[i].key = NULL;
        table->entries[i].value = NULL;
        table->entries[i].state = ENTRY_EMPTY;
    }
    table->size = 0;
    table->tombstones = 0;
}

size_t hash_table_size(const HashTable *table) {
    if (table == NULL) {
        return 0;
    }

    return table->size;
}

size_t hash_table_capacity(const HashTable *table) {
    if (table == NULL) {
        return 0;
    }

    return table->capacity;
}
