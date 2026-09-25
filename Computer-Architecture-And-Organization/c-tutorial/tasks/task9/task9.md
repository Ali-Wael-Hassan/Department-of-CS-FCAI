# 9. Hash Table

## Goal

Learn hashing and more advanced dynamic data structures. This implementation uses open addressing with linear probing only; separate chaining is not used.

## Project

Implement a hash table mapping string keys to `void *` values. Keys are copied into the table, while values are stored as caller-owned pointers.

## Implemented API

```c
typedef struct HashTable HashTable;
typedef size_t (*HashFunction)(const char *key);

HashTable *hash_table_create(size_t initial_capacity);
HashTable *hash_table_create_with_hash(size_t initial_capacity, HashFunction hash);
void hash_table_free(HashTable *table);
int hash_table_insert(HashTable *table, const char *key, void *value);
void *hash_table_find(const HashTable *table, const char *key);
int hash_table_contains(const HashTable *table, const char *key);
int hash_table_remove(HashTable *table, const char *key);
int hash_table_resize(HashTable *table, size_t new_capacity);
void hash_table_clear(HashTable *table);
size_t hash_table_size(const HashTable *table);
size_t hash_table_capacity(const HashTable *table);
```

## Concepts

- Hash functions
- Collision handling
- Load factor
- Resizing
- Open addressing
- Linear probing
- Tombstones
- Function pointers
- String ownership
- `void *` values

## Collision Handling

Every entry has one of three states: empty, occupied, or tombstone. Lookups and insertions probe forward with `index = (index + 1) % capacity`. A tombstone keeps probe sequences intact after a deletion, and a later insertion may reuse it. Insertion remembers the first tombstone but continues probing in case the key already exists later in the cluster.

## Requirements

- Use linear probing exclusively; do not use separate chaining.
- Copy every non-null key into table-owned memory.
- Store `void *` values without taking ownership of the pointed-to objects.
- Support duplicate-key updates without increasing the size.
- Return `0` from `hash_table_find` for an absent key or a stored null value, and use `hash_table_contains` to distinguish them.
- Grow automatically near a 0.75 load factor, counting tombstones toward the probe pressure.
- Preserve all entries across automatic and manual resizing.
- Reject invalid resize requests and report allocation failure without corrupting the table.
- Release all table-owned keys and the table itself.
- Follow C90 syntax: declare variables at the beginning of each block, use explicit function prototypes, and include the relevant standard headers.
- Keep mutable state local; do not use global mutable variables.

## Tests

Test key ownership, `void *` values, updates, missing keys, stored null values, forced collisions, tombstone reuse, cluster reinsertion, automatic growth, manual resize, invalid resize, null arguments, clearing, and cleanup. The test program belongs in [`solution/task9.c`](solution/task9.c).

## Workflow

1. Declare the interface in [`solution/HashTable.h`](solution/HashTable.h).
2. Implement the linear-probing table in [`solution/HashTable.c`](solution/HashTable.c).
3. Implement the test `main` in [`solution/task9.c`](solution/task9.c).
4. Compile and run the tests.

## Book Reference

*Read these parts of* The C Programming Language, 2nd edition, Brian W. Kernighan and Dennis M. Ritchie. A copy is bundled with the tutorial in [`../../reference/`](<../../reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>). Page numbers are the printed page numbers.

- **pp. 127–129 — §6.6 Table Lookup** — the closest match in the book to this task. The book hashes a string to an index, walks a bucket, and supports `lookup` and `install`. Read it for the hashing idea and the modulo indexing.
- **p. 128 — §6.6, the `hash` function** — summing the characters of the key and returning `hashval % HASHSIZE`; the note that unsigned arithmetic keeps the result non-negative, which matters for `size_t` indices.
- **p. 129 — §6.6, the `lookup` function** — searching one bucket and returning `NULL` for "not found", the same contract as `hash_table_find`.
- **p. 129 — §6.6, the list-walking idiom** — the `for` loop that walks a bucket; the linear probing probe sequence in this task is the array-shaped equivalent.
- **p. 129 — §6.6, the `install` function** — the book's "insert or update" step, which is what duplicate-key updates must do here without growing `size`.
- **pp. 129–130 — §6.7 `typedef`** — the `typedef` pattern used by the required `HashFunction` type.
- **pp. 106–107 — §5.11 Pointers to Functions** — why a function itself is not a variable but a pointer to it is, and how that is written in a struct field. This is the `HashFunction` design in this task.
- **pp. 114–115 — §6.1 Basics of Structures** — the entry struct with `key`, `count`, and `next`.
- **pp. 116–117 — §6.2 Structures and Functions** — passing `HashTable *` and `const HashTable *` so lookups do not mutate the table.
- **pp. 122–123 — §6.4 Pointers to Structures** — `->` on entries inside the bucket array.
- **pp. 83–86 — §5.1 Pointers and Addresses** — pointer fundamentals, including the array of pointers the book uses for buckets.
- **p. 148 — §7.8.5 Storage Management, and p. 230 — Appendix B.5 `<stdlib.h>`** — `malloc` and `free` for entries, copied keys, and the table itself.
- **p. 235 — Appendix B.11 `<limits.h>`** — the guaranteed ranges of the unsigned types behind the hash arithmetic; the book's note about unsigned wraparound assumes the bucket index is taken modulo the table size.
- **pp. 163–167 — §8.7 Example: A Storage Allocator** — optional background on how the book manages a table of fixed-size blocks, which is a resize-free alternative to this task's growth strategy.

## Book Exercises Worth Trying First

- **Exercise 6-2 (p. 127)** — print every identifier in a C program in alphabetical order. It is a complete hash-table exercise: collect, hash, look up, print.
- **Exercise 6-3 (p. 127)** — a cross-referencer over a document. The interesting part is the extra per-key data, similar to the `void *` values here.
- **Exercise 6-4 (p. 127)** — print distinct words sorted by decreasing frequency. Requires `lookup` to find an existing key so the count can be updated in place, which is the duplicate-key update path in this task.
- **Exercise 6-5 (p. 129)** — add `undef`. It is a small delete operation, the same shape as removing a key while keeping the probe sequence intact.

## Friendly References

- **The book** ([`../../reference/`](<../../reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>) — *The C Programming Language*, 2nd edition, PDF) — §6.6 is a hash table in thirty lines, and it is the single most useful page range in the tutorial for this task. The only structural difference is chaining versus open addressing, which is worth understanding rather than skipping.
- [cppreference: `qsort`](https://en.cppreference.com/w/c/algorithm/qsort) — not required here, but its comparison-function parameter is the clearest example of a function pointer used as data, which is what `HashFunction` is.
- [cppreference: functions](https://en.cppreference.com/w/c/language/functions) — the rules for declaring and storing a function pointer, and the type compatibility requirements.
- [cppreference: `struct`](https://en.cppreference.com/w/c/language/struct) — entry layout, `const` members, and the `->` operator used while probing.
- [cppreference: `malloc`](https://en.cppreference.com/w/c/memory/malloc), [`realloc`](https://en.cppreference.com/w/c/memory/realloc), and [`free`](https://en.cppreference.com/w/c/memory/free) — the allocation paths for the table, its entries, and the key copies.
- [cppreference: `size_t`](https://en.cppreference.com/w/c/types/size_t) — the type used for capacities, hashes, and indices, and the reason bucket indices stay non-negative.
- [cppreference: `NULL`](https://en.cppreference.com/w/c/types/NULL) — the sentinel shared by empty slots, removed keys, and the "absent" return of `hash_table_find`.
- [cppreference: `const`](https://en.cppreference.com/w/c/language/const) — why `hash_table_find` and `hash_table_contains` take a `const HashTable *`.
- [Bee's Guide to C Programming](https://beej.us/guide/bgc/) — read its structures section for a second take on structs-of-arrays versus arrays-of-structs before you choose an entry layout.

## Navigation

[← 8. Stack, Queue and Deque](../task8/task8.md) · [Task instructions](../instructions.md) · [All tasks](../../README.md) · [Course guide](../../../README.md) · [10. File Utility →](../task10/task10.md)
