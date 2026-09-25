# 5. Dynamic Array

## Goal

Learn manual dynamic memory management.

## Project

Implement a growable array of `int` values.

```c
typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Vector;
```

## API

```c
void vector_init(Vector *v);
int vector_push(Vector *v, int value);
int vector_pop(Vector *v, int *out);
int vector_get(const Vector *v, size_t index, int *out);
int vector_set(Vector *v, size_t index, int value);
void vector_clear(Vector *v);
void vector_free(Vector *v);
```

## Concepts

- `malloc`
- `realloc`
- `free`
- `sizeof`
- Heap allocation
- Ownership
- Capacity vs size
- Dynamic growth

## Requirements

- Automatically grow the array.
- Detect allocation failure.
- Prevent out-of-bounds access.
- Release all allocated memory.
- Use `size_t` for sizes, capacities, and indices.
- Follow C90 syntax: declare variables at the beginning of each block, use explicit function prototypes, and include the relevant standard headers.
- Keep mutable state local; do not use global mutable variables.

## Tests

Write tests for the `Vector` API, including growth, bounds failures, clearing, freeing, reuse after `vector_free`, and null arguments. The test program belongs in [`solution/task5.c`](solution/task5.c).

## Workflow

1. Declare the interface in [`solution/Vector.h`](solution/Vector.h).
2. Implement the functions in [`solution/Vector.c`](solution/Vector.c).
3. Implement the test `main` in [`solution/task5.c`](solution/task5.c).
4. Compile and run the tests.

## Book Reference

*Read these parts of* The C Programming Language, 2nd edition, Brian W. Kernighan and Dennis M. Ritchie. A copy is bundled with the tutorial in [`../../reference/`](<../../reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>). Page numbers are the printed page numbers.

- **pp. 83–86 — §5.1 Pointers and Addresses** — what a pointer holds, and why a pointer is the only way to name heap storage.
- **pp. 87–89 — §5.3 Pointers and Arrays** — an array name as a pointer to its first element, and how the compiler scales `data[i]`.
- **pp. 90–92 — §5.4 Address Arithmetic** — how `data + i` becomes an address, the arithmetic behind storing elements back to back.
- **pp. 99–100 — §5.7 Multi-dimensional Arrays** — a worked example of contiguous rows of contiguous elements, the same layout `Vector` produces.
- **pp. 114–115 — §6.1 Basics of Structures** — the `Vector` struct: grouping `data`, `size`, and `capacity` under one name.
- **pp. 116–117 — §6.2 Structures and Functions** — passing `Vector *` to every function so the caller's vector is modified in place; this is the ownership model the task requires.
- **pp. 129–130 — §6.7 `typedef`** — optional, but `typedef struct {...} Vector;` is exactly the pattern used in the required API.
- **pp. 31–34 — §1.10 External Variables and Scope, and p. 72 — §4.4 Scope Rules** — why the vector's fields live inside a caller-owned struct instead of in file-scope variables.
- **p. 148 — §7.8.5 Storage Management** — `malloc` and `free`, and the rule that every allocation has exactly one owner responsible for freeing it.
- **p. 220 — Appendix B, `<stdlib.h>` introduction** — which header declares the allocation functions.
- **p. 230 — Appendix B.5 `<stdlib.h>`** — `calloc`, `malloc`, `realloc`, and `free`: signatures, the `NULL`-on-failure convention, and what `realloc` does when it moves the block.
- **pp. 163–167 — §8.7 Example: A Storage Allocator** — how the book's own block allocator manages free lists, sizes, and coalescing. Skim it; it explains why `realloc` may return a different address and why alignment matters.
- **p. 167 — §8.7, the note on `calloc(n, size)`** — overflow thinking for `capacity * element_size`, which the growth arithmetic in this task must respect.
- **p. 93 — §5.5, the `size_t` note** — `size_t` is the unsigned type returned by `sizeof`, which is why capacities and indices use it.

## Book Exercises Worth Trying First

- **Exercise 8-6 (p. 167)** — implement `calloc(n, size)`. It is a ten-line wrapper over `malloc` plus a zeroing loop, and it is the smallest possible version of `vector_init`.
- **Exercise 8-7 (p. 167)** — `malloc` accepts any size request and `free` trusts it. Handling a plausibility check is exactly the kind of defensive check this task asks for.
- **Exercise 8-8 (p. 167)** — `bfree(p, n)` frees an arbitrary block. Useful reading for thinking about what `vector_clear` and `vector_free` must do differently.
- **Exercise 5-7 (p. 99)** — `readlines` stores lines in an array supplied by `main`. A small, complete example of a caller-owned growable buffer.

## Friendly References

- **The book** ([`../../reference/`](<../../reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>) — *The C Programming Language*, 2nd edition, PDF) — read §5.1 to §5.4 once, then §7.8.5 for `malloc` and `free`. After that, a growable array is just "a pointer, a count, and a `realloc` when the count runs out".
- [cppreference: `malloc`](https://en.cppreference.com/w/c/memory/malloc) — the return contract, the `NULL` failure convention, and the alignment guarantee.
- [cppreference: `realloc`](https://en.cppreference.com/w/c/memory/realloc) — the behavior that matters most here: the old contents are preserved, the address may change, and the old pointer must not be used afterwards.
- [cppreference: `free`](https://en.cppreference.com/w/c/memory/free) — the rule that a pointer is invalid after `free`, which is why the tests need to check reuse rather than reuse a stale pointer.
- [cppreference: `calloc`](https://en.cppreference.com/w/c/memory/calloc) — a useful contrast: zero-initialized allocation, and the overflow check a naive `n * size` lacks.
- [cppreference: `size_t`](https://en.cppreference.com/w/c/types/size_t) — the unsigned type for sizes, capacities, and indices, and why the arithmetic is done in that type.
- [cppreference: arrays](https://en.cppreference.com/w/c/language/array) and [pointers](https://en.cppreference.com/w/c/language/pointer) — the indexing and pointer-arithmetic rules that `vector_get` and `vector_set` depend on.
- [cppreference: `struct`](https://en.cppreference.com/w/c/language/struct) — how members are laid out and why passing `Vector *` is the right way to mutate one.
- [cppreference: `assert`](https://en.cppreference.com/w/c/error/assert) — optional but useful while developing: assert preconditions and postconditions in the tests, then remove or keep them as you prefer.
- [Bee's Guide to C Programming](https://beej.us/guide/bgc/) — its arrays and pointers sections are a good second read if pointer arithmetic still feels shaky.

## Navigation

[← 4. Custom String Library](../task4/task4.md) · [Task instructions](../instructions.md) · [All tasks](../../README.md) · [Course guide](../../../README.md) · [6. Generic Dynamic Array →](../task6/task6.md)
