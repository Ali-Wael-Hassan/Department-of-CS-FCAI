# 8. Stack, Queue and Deque

## Goal

Learn common abstract data types. This task intentionally implements only the Stack portion; Queue and Deque are reserved for a later extension.

## Project

Implement a generic LIFO Stack by reusing the linked-list component.

```c
typedef struct {
    LinkedList *list;
} Stack;
```

The Stack stores copies of elements with the element size supplied to `stack_create`.

## Implemented API

```c
Stack *stack_create(size_t element_size);
void stack_free(Stack *stack);
int stack_push(Stack *stack, const void *data);
int stack_pop(Stack *stack, void *out);
int stack_peek(const Stack *stack, void *out);
size_t stack_size(const Stack *stack);
int stack_empty(const Stack *stack);
```

Queue and Deque operations are not part of this implementation.

## Concepts

- LIFO
- FIFO
- Circular buffers
- Abstract data types
- Reusing previous components
- Ownership
- Dynamic allocation
- Traversal

## Requirements

- Implement push and pop at the front of the backing list so the most recent element is removed first.
- Preserve a caller-supplied element size and copy each element into the list.
- Return `0` when an operation cannot be completed and nonzero on success.
- Make `stack_peek` leave the stack unchanged.
- Release the backing list and the Stack object in `stack_free`.
- Reject null Stack pointers and handle an empty Stack without changing output buffers.
- Follow C90 syntax: declare variables at the beginning of each block, use explicit function prototypes, and include the relevant standard headers.
- Keep mutable state local; do not use global mutable variables.

## Tests

Test creation, LIFO ordering, `stack_peek`, size and empty state, empty-operation failures, copy ownership with both `int` and a struct element, null arguments, and cleanup. The test program belongs in [`solution/task8.c`](solution/task8.c).

## Workflow

1. Keep the supplied declarations in [`solution/Stack.h`](solution/Stack.h).
2. Use [`solution/Linkedlist.c`](solution/Linkedlist.c) as the backing storage.
3. Implement the test `main` in [`solution/task8.c`](solution/task8.c).
4. Compile and run the tests.

## Book Reference

*Read these parts of* The C Programming Language, 2nd edition, Brian W. Kernighan and Dennis M. Ritchie. A copy is bundled with the tutorial in [`../../reference/`](<../../reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>). Page numbers are the printed page numbers.

- **pp. 95–96 — §5.5, the `push` and `pop` remark** — the book points here from the pointer-array discussion to note that pushing and popping an array is the standard stack idiom. That is this task in one sentence.
- **pp. 68–70 — §4.3 External Variables (the calculator program)** — the book's stack: `push` stores into a fixed array and increments an index, `pop` decrements and returns. Read it to see the LIFO invariant, then notice how much of it this task replaces with a linked list.
- **p. 71 — Exercise 4-3** — extending the calculator is the book's own way of learning stacks; a useful mental comparison with the reusable `Stack` here.
- **pp. 114–115 — §6.1 Basics of Structures** — the thin `Stack` struct that holds a `LinkedList *`.
- **pp. 116–117 — §6.2 Structures and Functions** — passing `Stack *` and `const Stack *` so operations mutate or observe without copying.
- **pp. 122–123 — §6.4 Pointers to Structures** — delegation: the stack's implementation lives in the list, reached through one pointer.
- **pp. 124–126 — §6.5 Self-referential Structures** — the backing list's node structure and the traversal loop that `stack_pop` and `stack_peek` rely on.
- **p. 129 — §6.6, the list-walking idiom** — the exact loop shape for "read the front element without changing the list".
- **pp. 83–86 — §5.1 Pointers and Addresses** — pointer fundamentals for the delegation layer.
- **p. 148 — §7.8.5 Storage Management, and p. 230 — Appendix B.5 `<stdlib.h>`** — `malloc` and `free`, and who is responsible for releasing them.
- **p. 93 — §5.5, the `size_t` note** — why the element size and the size counter are `size_t`.
- **pp. 67–72 — §4.3, and p. 72 — §4.4 Scope Rules** — why the calculator's globals are not repeated here: state belongs to the object the caller owns.

## Book Exercises Worth Trying First

- **Exercise 4-3 (p. 71)** — extend the book's calculator. It forces you to add commands that push and pop more than one value, which is where LIFO bugs usually appear.
- **Exercise 4-4 (p. 71)** — print the top of the stack without popping it. This is `stack_peek`; the book's version is on a fixed array, and comparing the two implementations is instructive.
- **Exercise 4-5 (p. 72)** — add access to library functions such as `sin`, `exp`, and `pow`. A small test that pushes and pops several times in one session.

## Friendly References

- **The book** ([`../../reference/`](<../../reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>) — *The C Programming Language*, 2nd edition, PDF) — the stack is the one abstract data type the book implements for real, in §4.3. Read `push`/`pop` there, then read §6.5 and you have both halves of this task: the discipline and the storage.
- [cppreference: `struct`](https://en.cppreference.com/w/c/language/struct) — the one-field `Stack` that wraps a list, a common composition pattern.
- [cppreference: `const`](https://en.cppreference.com/w/c/language/const) — why `stack_peek` and `stack_size` take `const Stack *` while the mutating operations do not.
- [cppreference: pointers](https://en.cppreference.com/w/c/language/pointer) — the mechanics of the delegation call chain.
- [cppreference: `malloc`](https://en.cppreference.com/w/c/memory/malloc) and [`free`](https://en.cppreference.com/w/c/memory/free) — the allocation contract behind `stack_create` and `stack_free`.
- [cppreference: `size_t`](https://en.cppreference.com/w/c/types/size_t) — the type behind `stack_size` and the caller-supplied element size.
- [cppreference: `assert`](https://en.cppreference.com/w/c/error/assert) — useful in the tests to assert that `stack_peek` leaves the size unchanged.
- [Bee's Guide to C Programming](https://beej.us/guide/bgc/) — its arrays section makes the original fixed-array stack easy to picture, which helps when you switch to a linked list.

## Navigation

[← 7. Linked List](../task7/task7.md) · [Task instructions](../instructions.md) · [All tasks](../../README.md) · [Course guide](../../../README.md) · [9. Hash Table →](../task9/task9.md)
