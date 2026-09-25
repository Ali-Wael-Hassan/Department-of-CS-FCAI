# 4. Custom String Library

## Goal

Understand pointers and C strings instead of treating strings as magic.

## Project

Implement your own subset of `<string.h>`.

## Required Functions

```c
size_t duck_strlen(const char *str);
char *duck_strcpy(char *dest, const char *src);
char *duck_strncpy(char *dest, const char *src, size_t n);
int duck_strcmp(const char *left, const char *right);
int duck_strncmp(const char *left, const char *right, size_t n);
char *duck_strchr(const char *str, int c);
char *duck_strstr(const char *haystack, const char *needle);
void *duck_memcpy(void *dest, const void *src, size_t n);
void *duck_memmove(void *dest, const void *src, size_t n);
void *duck_memset(void *dest, int c, size_t n);
```

## Concepts

- Pointers
- Pointer arithmetic
- Arrays vs pointers
- `const`
- Null termination
- Memory representation
- Function parameters
- Return pointers

## Requirements

- Do not use the corresponding standard function internally.
- `duck_strlen` must calculate the length itself.
- Follow C90 syntax: declare variables at the beginning of each block, use explicit function prototypes, and include the relevant standard headers.
- Keep mutable state local; do not use global mutable variables.
- Return `0` for a successful test run and a nonzero value for errors.

## Extension

Write tests comparing your functions against the standard library. The test program belongs in [`solution/task4.c`](solution/task4.c).

## Workflow

1. Declare the shared interface in [`solution/duck_string.h`](solution/duck_string.h).
2. Implement the functions in [`solution/duck_string.c`](solution/duck_string.c).
3. Implement the test `main` in [`solution/task4.c`](solution/task4.c).
4. Compile and run the tests.

## Book Reference

*Read these parts of* The C Programming Language, 2nd edition, Brian W. Kernighan and Dennis M. Ritchie. A copy is bundled with the tutorial in [`../../reference/`](<../../reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>). Page numbers are the printed page numbers.

- **pp. 29–30 — §1.9 Character Arrays** — the first look at strings: a null-terminated `char` array is a C string.
- **pp. 83–86 — §5.1 Pointers and Addresses** — what a pointer is, `&`, `*`, and the `char *` parameter style used by every function in this task.
- **pp. 87–89 — §5.3 Pointers and Arrays** — array elements are addressable through a pointer; this is what makes `duck_strlen` and `duck_strchr` possible.
- **pp. 90–92 — §5.4 Address Arithmetic** — `p++`, `p + n`, and `p - s`; the reason `duck_strlen` returns a length by subtracting two pointers.
- **pp. 93–95 — §5.5 Character Pointers and Functions** — the core of this task. The book implements `strlen`, `strcpy`, `strcat`, `strcmp`, and `strchr` from scratch, which is the required behavior here.
- **p. 93 — the `size_t` and `ptrdiff_t` note** — why the standard library returns `size_t` from `strlen`, and why the signed difference of pointers is not the right return type.
- **p. 96 — §5.5, Exercises 5-3, 5-4, and 5-5** — write pointer versions of `strcat`, `strend`, `strncpy`, `strncat`, and `strncmp`. Three of the ten required functions come straight from these exercises.
- **pp. 95–96 — §5.5, the `push` and `pop` remark** — a reminder that pointer-based stack idioms generalize to any array-like storage.
- **pp. 116–117 — §6.2 Structures and Functions** — how `const` parameters and pointer returns are written in real function signatures.
- **p. 148 — §7.8.1 String Operations** — the standard library names these functions, and the return-value conventions you must match.
- **p. 176 — §A.6.8 Pointers to `void`** — why `duck_memcpy` and `duck_memset` return `void *` and how a `void *` is cast to `unsigned char *` inside.
- **p. 227 — Appendix B.3 `<string.h>`** — the reference behavior of the functions you are reimplementing. Compare signatures and null-pointer returns carefully.

## Book Exercises Worth Trying First

- **Exercise 5-3 (p. 96)** — a pointer version of `strcat`. Ten lines and it teaches both copying and termination.
- **Exercise 5-4 (p. 96)** — `strend`, a small search that returns an `int` instead of a pointer, a useful contrast with `duck_strstr`.
- **Exercise 5-5 (p. 96)** — `strncpy`, `strncat`, and `strncmp` with an explicit length. Read the book's note about `strncpy` padding with nulls before you start.
- **Exercise 5-6 (p. 96)** — rewrite an earlier program using pointers. A good way to feel the difference between array syntax and pointer syntax.
- **Exercise 4-1 (p. 65)** — `strindex`, which returns the position of the rightmost occurrence. It is a template for `duck_strstr`.

## Friendly References

- **The book** ([`../../reference/`](<../../reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>) — *The C Programming Language*, 2nd edition, PDF) — §5.5 is the closest thing to a lecture on this task. If a function here feels obvious after reading it, you have understood pointers well enough.
- [cppreference: `<string.h>` byte strings](https://en.cppreference.com/w/c/string/byte) — the exact behavior you must reproduce, including `strncpy` padding and what the comparison functions return.
- [cppreference: pointers](https://en.cppreference.com/w/c/language/pointer) — pointer arithmetic, `const` qualification, and the rule that a pointer past the end of an array may not be formed.
- [cppreference: arrays](https://en.cppreference.com/w/c/language/array) — the array-versus-pointer decay rules that make `char dest[]` and `char *dest` interchangeable in a parameter list.
- [cppreference: `const` qualifiers](https://en.cppreference.com/w/c/language/const) — why `const char *src` and `char *src` are different promises about the caller's data.
- [cppreference: `size_t`](https://en.cppreference.com/w/c/types/size_t) and [`ptrdiff_t`](https://en.cppreference.com/w/c/types/ptrdiff_t) — the two integer types involved in `duck_strlen` and its return value.
- [cppreference: `NULL`](https://en.cppreference.com/w/c/types/NULL) — the null pointer constant returned by `duck_strchr` and `duck_strstr` for "not found".
- [cppreference: pointers to `void` and byte-level access](https://en.cppreference.com/w/c/language/pointer) — casting `void *` to `unsigned char *` when copying bytes, and why `unsigned char` is the right type for inspecting object representation.
- [Bee's Guide to C Programming](https://beej.us/guide/bgc/) — the pointers chapter there is written for beginners and is a good second explanation of `p++` and `p - s`.

## Navigation

[← 3. Line, Word, and Character Counter](../task3/task3.md) · [Task instructions](../instructions.md) · [All tasks](../../README.md) · [Course guide](../../../README.md) · [5. Dynamic Array →](../task5/task5.md)
