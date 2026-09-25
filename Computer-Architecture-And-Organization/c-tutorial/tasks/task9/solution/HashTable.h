#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>

typedef struct HashTable HashTable;

typedef size_t (*HashFunction)(const char *key);

HashTable *hash_table_create(size_t initial_capacity);
HashTable *hash_table_create_with_hash(size_t initial_capacity,
                                       HashFunction hash);
void hash_table_free(HashTable *table);

int hash_table_insert(HashTable *table, const char *key, void *value);
void *hash_table_find(const HashTable *table, const char *key);
int hash_table_contains(const HashTable *table, const char *key);
int hash_table_remove(HashTable *table, const char *key);
int hash_table_resize(HashTable *table, size_t new_capacity);

void hash_table_clear(HashTable *table);
size_t hash_table_size(const HashTable *table);
size_t hash_table_capacity(const HashTable *table);

#endif
