# 6. Generic Dynamic Array

## Goal

Extend the dynamic array to store values of any type while learning how element size, pointer arithmetic, and ownership work together.

## Project

Implement a growable array whose elements are copied as bytes. The caller supplies the element size during initialization.

```c
typedef struct {
    void *data;
    size_t size;
    size_t capacity;
    size_t element_size;
} Vector;
```

## API

```c
void vector_init(Vector *v, size_t element_size);
int vector_push(Vector *v, const void *value);
int vector_pop(Vector *v, void *out);
int vector_get(const Vector *v, size_t index, void *out);
int vector_set(Vector *v, size_t index, const void *value);
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
- `void *` and typed pointers
- Pointer arithmetic on `unsigned char *`
- Copying objects by bytes

## Requirements

- Accept any element type by storing a caller-supplied `element_size`.
- Automatically grow the array when capacity is exhausted.
- Detect allocation failure and leave the vector unchanged when growth fails.
- Reject a zero element size.
- Prevent out-of-bounds access.
- Release all allocated memory.
- Preserve `element_size` after `vector_free` so a cleared allocation can be reused.
- Follow C90 syntax: declare variables at the beginning of each block, use explicit function prototypes, and include the relevant standard headers.
- Keep mutable state local; do not use global mutable variables.

## Tests

Write tests using at least two element types, including a struct whose size differs from `int`. Cover growth, bounds failures, clearing, freeing, reuse after `vector_free`, zero element size, null arguments, and growth overflow. The test program belongs in [`solution/task6.c`](solution/task6.c).

## Workflow

1. Declare the generic interface in [`solution/Vector.h`](solution/Vector.h).
2. Implement the functions in [`solution/Vector.c`](solution/Vector.c).
3. Implement the test `main` in [`solution/task6.c`](solution/task6.c).
4. Compile and run the tests.

## Book Reference

*Read these parts of* The C Programming Language, 2nd edition, Brian W. Kernighan and Dennis M. Ritchie. A copy is bundled with the tutorial in [`../../reference/`](<../../reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>). Page numbers are the printed page numbers.

- **pp. 83–86 — §5.1 Pointers and Addresses** — the address arithmetic that replaces compile-time element typing: everything reduces to byte offsets once the element size is known.
- **pp. 87–89 — §5.3 Pointers and Arrays** — array indexing as scaled address arithmetic; the same trick reappears here with an element size supplied at runtime.
- **pp. 90–92 — §5.4 Address Arithmetic** — why pointer arithmetic scales by the pointed-to type, and what that implies for a byte-addressed buffer.
- **pp. 114–115 — §6.1 Basics of Structures** — the `Vector` struct and the `element_size` field.
- **pp. 116–117 — §6.2 Structures and Functions** — passing `Vector *` so mutations reach the caller.
- **pp. 118–121 — §6.3 Arrays of Structures** — a second look at contiguous arrays, this time of variable-size objects; the layout rule is identical to this task's.
- **p. 121 — the `size_t` remark** — `size_t` is the type of `sizeof`, which is where the initial `element_size` value comes from.
- **p. 127 — §6.6, the `malloc` and cast discussion** — `malloc` returns a pointer to `void`, and casting it to a typed pointer is the standard approach; this task instead keeps `void *` and does its own casts.
- **pp. 129–130 — §6.7 `typedef`** — the `typedef struct {...} Vector;` pattern used by the required API.
- **pp. 148 and 230 — §7.8.5 Storage Management and Appendix B.5 `<stdlib.h>`** — `malloc`, `calloc`, `realloc`, and `free`, including `realloc` preserving contents and possibly returning a new address.
- **pp. 163–167 — §8.7 Example: A Storage Allocator** — the book's block allocator, which tracks sizes and headers; it clarifies what a byte-counted buffer must guarantee.
- **p. 167 — §8.7, the `calloc(n, size)` note** — the `n * size` overflow trap that this task's growth arithmetic must handle explicitly.
- **p. 176 — §A.6.7 `void` and §A.6.8 Pointers to `void`** — the precise meaning of `void *`, and the rule that it converts to any object pointer type without a cast.
- **p. 181 — §A.7.5 Casts** — the `(unsigned char *)` cast used when copying elements of arbitrary size.

## Book Exercises Worth Trying First

- **Exercise 8-6 (p. 167)** — implement `calloc(n, size)`. It is the closest C90 exercise to "allocate space for objects of a known size" and it is short.
- **Exercise 8-7 (p. 167)** — `malloc` trusts any size; adding a plausibility check mirrors the "leave the vector unchanged when growth fails" requirement.
- **Exercise 5-7 (p. 99)** — `readlines` writes into a caller-supplied array, a clean example of a buffer whose element size is fixed at compile time, which is exactly what this task generalizes.

## Friendly References

- **The book** ([`../../reference/`](<../../reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>) — *The C Programming Language*, 2nd edition, PDF) — the through-line to follow is: the book always scales pointer arithmetic by a type, and this task is the exercise of doing that scaling by a number you keep in the struct.
- [cppreference: `malloc`](https://en.cppreference.com/w/c/memory/malloc) — why the return type is `void *` and what the alignment guarantee means for a byte buffer.
- [cppreference: `realloc`](https://en.cppreference.com/w/c/memory/realloc) — read the failure case carefully: on failure the old block is untouched, which is how "leave the vector unchanged" is implemented.
- [cppreference: `free`](https://en.cppreference.com/w/c/memory/free) — the invalidation rule that the reuse-after-`vector_free` test must respect.
- [cppreference: `calloc`](https://en.cppreference.com/w/c/memory/calloc) — the multiplication-overflow discussion worth reading before the growth arithmetic in this task.
- [cppreference: `void*` conversion rules](https://en.cppreference.com/w/c/language/pointer) — when a cast is required and when it is not.
- [cppreference: `size_t`](https://en.cppreference.com/w/c/types/size_t) — the type of `sizeof`, and why multiplying capacity by `element_size` in this type matters.
- [cppreference: `struct`](https://en.cppreference.com/w/c/language/struct) and [`typedef`](https://en.cppreference.com/w/c/language/typedef) — the declaration style the required API uses.
- [cppreference: `assert`](https://en.cppreference.com/w/c/error/assert) — handy in the tests for the two element types, where a wrong element size shows up as an assertion failure rather than silent corruption.
- [Bee's Guide to C Programming](https://beej.us/guide/bgc/) — read its arrays and pointers sections first; this task is much easier once `data + i` is routine.

## Navigation

[← 5. Dynamic Array](../task5/task5.md) · [Task instructions](../instructions.md) · [All tasks](../../README.md) · [Course guide](../../../README.md) · [7. Linked List →](../task7/task7.md)
