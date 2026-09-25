# 7. Linked List

## Goal

Understand pointer-based data structures.

## Project

Implement a generic singly linked list. Each node owns a private copy of one element.

```c
typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    size_t size;
    size_t element_size;
} LinkedList;
```

## Implemented API

The supplied header exposes:

```c
LinkedList *linkedlist_create(size_t element_size);
void linkedlist_free(LinkedList *list);
int linkedlist_push_front(LinkedList *list, const void *data);
int linkedlist_push_back(LinkedList *list, const void *data);
int linkedlist_pop_front(LinkedList *list, void *out);
int linkedlist_pop_back(LinkedList *list, void *out);
int linkedlist_get(const LinkedList *list, size_t index, void *out);
int linkedlist_set(LinkedList *list, size_t index, const void *data);
size_t linkedlist_size(const LinkedList *list);
int linkedlist_empty(const LinkedList *list);
void linkedlist_clear(LinkedList *list);
void node_free(Node *node);
```

`insert`, `remove`, `find`, and `reverse` are not declared by the supplied header, so the tests cover the implemented API. The supplied `linkedlist_push_back` dereferences a null list before its null check, so that specific unsafe null case is left for an implementation fix.

## Concepts

- Structs
- Self-referential structs
- Pointers
- Dynamic allocation
- Ownership
- Traversal
- Copying elements by bytes

## Requirements

- Accept any element type through the caller-supplied `element_size`.
- Copy each element into node-owned memory.
- Detect allocation failure and leave the list unchanged when insertion fails.
- Prevent out-of-bounds access in `linkedlist_get` and `linkedlist_set`.
- Release every node and element allocation in `linkedlist_clear` and `linkedlist_free`.
- Keep `size` and `head` consistent after every operation.
- Follow C90 syntax: declare variables at the beginning of each block, use explicit function prototypes, and include the relevant standard headers.
- Keep mutable state local; do not use global mutable variables.

## Tests

Test creation, front and back insertion and removal, ordering, get, set, size, empty, clear, copy ownership with both `int` and a struct element, bounds failures, null arguments, and cleanup. The test program belongs in [`solution/task7.c`](solution/task7.c).

## Workflow

1. Keep the supplied declarations in [`solution/Linkedlist.h`](solution/Linkedlist.h).
2. Keep the supplied implementation in [`solution/Linkedlist.c`](solution/Linkedlist.c).
3. Implement the test `main` in [`solution/task7.c`](solution/task7.c).
4. Compile and run the tests.

## Book Reference

*Read these parts of* The C Programming Language, 2nd edition, Brian W. Kernighan and Dennis M. Ritchie. A copy is bundled with the tutorial in [`../../reference/`](<../../reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>). Page numbers are the printed page numbers.

- **pp. 114–115 — §6.1 Basics of Structures** — the `Node` and `LinkedList` structs.
- **pp. 116–117 — §6.2 Structures and Functions** — passing `Node *` and `LinkedList *` so the list is modified in place, and why the list pointer must be passed to every operation.
- **pp. 122–123 — §6.4 Pointers to Structures** — the `->` operator, used pervasively in this task.
- **pp. 124–126 — §6.5 Self-referential Structures** — the heart of this task. The book builds a linked list of words, allocates each node with `malloc`, and shows the `for` loop that walks it.
- **pp. 124–126 — §6.5, the `struct nlist` example** — the exact node-plus-next shape required here, and the reason `head` must be updated by the caller.
- **p. 127 — §6.6, the `malloc` and cast discussion** — allocating one node's worth of storage, and why allocation failure must leave the list unchanged.
- **p. 129 — §6.6, the list-walking idiom** — the book's "walk a list" loop, which is what `linkedlist_get` and `linkedlist_pop_back` need.
- **pp. 129–130 — §6.7 `typedef`** — the `typedef struct Node {...} Node;` pattern from the required API.
- **pp. 83–86 — §5.1 Pointers and Addresses** — the pointer fundamentals behind every node link.
- **p. 148 — §7.8.5 Storage Management, and p. 230 — Appendix B.5 `<stdlib.h>`** — `malloc` and `free`, and the `NULL` failure convention.
- **pp. 163–167 — §8.7 Example: A Storage Allocator** — optional background on what happens to freed memory and why double frees are undefined.
- **p. 176 — §A.6.8 Pointers to `void`** — why node payloads are stored as `void *` and how the `unsigned char *` cast copies them.

## Book Exercises Worth Trying First

- **Exercise 6-5 (p. 129)** — add `undef` to the word table so a name and its definition can be removed. It is a small, complete list mutation, the same shape as `linkedlist_remove` here.
- **Exercise 6-3 (p. 127)** — a cross-referencer that collects every word in a document. The interesting part is the traversal and the allocation-per-node pattern.
- **Exercise 8-6 (p. 167)** — implement `calloc(n, size)` as a small, self-contained allocation exercise before wiring up `linkedlist_create`.
- **Exercise 5-6 (p. 96)** — rewrite an earlier program using pointers; good practice for the `const LinkedList *` signatures.

## Friendly References

- **The book** ([`../../reference/`](<../../reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>) — *The C Programming Language*, 2nd edition, PDF) — §6.5 is a direct model for this task: allocate a node, link it, walk the list, then free it. Read it twice; the second pass is much shorter.
- [cppreference: `struct`](https://en.cppreference.com/w/c/language/struct) — including self-referential members and the `->` operator.
- [cppreference: `typedef`](https://en.cppreference.com/w/c/language/typedef) — the declaration style used by `Linkedlist.h`.
- [cppreference: `malloc`](https://en.cppreference.com/w/c/memory/malloc) and [`free`](https://en.cppreference.com/w/c/memory/free) — the failure convention and the rule against using a pointer after `free`.
- [cppreference: `realloc`](https://en.cppreference.com/w/c/memory/realloc) — not used by the list itself, but the clearest statement of the "leave the old block alone on failure" pattern that insertion also needs.
- [cppreference: pointers](https://en.cppreference.com/w/c/language/pointer) and [arrays](https://en.cppreference.com/w/c/language/array) — the mechanics behind `node->next` chains.
- [cppreference: `void*`](https://en.cppreference.com/w/c/language/pointer) — the conversion rules for storing and retrieving element copies of arbitrary type.
- [cppreference: `size_t`](https://en.cppreference.com/w/c/types/size_t) — the type of `linkedlist_size` and of every index the API accepts.
- [cppreference: `assert`](https://en.cppreference.com/w/c/error/assert) — a simple way to assert that `size` and `head` stay consistent after each operation in the tests.
- [Bee's Guide to C Programming](https://beej.us/guide/bgc/) — its structures and pointers material is a good second explanation of linked lists.

## Navigation

[← 6. Generic Dynamic Array](../task6/task6.md) · [Task instructions](../instructions.md) · [All tasks](../../README.md) · [Course guide](../../../README.md) · [8. Stack, Queue and Deque →](../task8/task8.md)
