# Task Instructions

These rules apply to every task in this folder. See the
[tutorial index](../README.md) for the task list and the
[course guide](../../README.md) for the wider course context.

## The tasks

| # | Task | Solution |
| --- | --- | --- |
| 1 | [Hello C: Command-Line Greeting](task1/task1.md) | [`solution/task1.c`](task1/solution/task1.c) |
| 2 | [C90 Command-Line Calculator](task2/task2.md) | [`solution/task2.c`](task2/solution/task2.c) |
| 3 | [Line, Word, and Character Counter](task3/task3.md) | [`solution/task3.c`](task3/solution/task3.c) |
| 4 | [Custom String Library](task4/task4.md) | [`solution/duck_string.h`](task4/solution/duck_string.h), [`solution/duck_string.c`](task4/solution/duck_string.c), [`solution/task4.c`](task4/solution/task4.c) |
| 5 | [Dynamic Array](task5/task5.md) | [`solution/Vector.h`](task5/solution/Vector.h), [`solution/Vector.c`](task5/solution/Vector.c), [`solution/task5.c`](task5/solution/task5.c) |
| 6 | [Generic Dynamic Array](task6/task6.md) | [`solution/Vector.h`](task6/solution/Vector.h), [`solution/Vector.c`](task6/solution/Vector.c), [`solution/task6.c`](task6/solution/task6.c) |
| 7 | [Linked List](task7/task7.md) | [`solution/Linkedlist.h`](task7/solution/Linkedlist.h), [`solution/Linkedlist.c`](task7/solution/Linkedlist.c), [`solution/task7.c`](task7/solution/task7.c) |
| 8 | [Stack, Queue and Deque](task8/task8.md) | [`solution/Stack.h`](task8/solution/Stack.h), [`solution/Stack.c`](task8/solution/Stack.c), [`solution/Linkedlist.c`](task8/solution/Linkedlist.c), [`solution/task8.c`](task8/solution/task8.c) |
| 9 | [Hash Table](task9/task9.md) | [`solution/HashTable.h`](task9/solution/HashTable.h), [`solution/HashTable.c`](task9/solution/HashTable.c), [`solution/task9.c`](task9/solution/task9.c) |
| 10 | [File Utility](task10/task10.md) | [`solution/duck_file.h`](task10/solution/duck_file.h), [`solution/duck_file.c`](task10/solution/duck_file.c), [`solution/task10.c`](task10/solution/task10.c) |

The book every task quotes is bundled next to the tutorial:
[*The C Programming Language*, 2nd edition (PDF)](<../reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>).

## Language Standard

All tasks in this directory use **C90 (ANSI C)**, the C standard published as ISO/IEC 9899:1990. C90 is the required baseline for every task, even when a reference or example uses newer C features.

- Use only language and library features available in C90.
- Do not use post-C90 features such as `//` comments, declarations after statements, declarations in `for` initializers, `long long`, `_Bool`, `restrict`, `inline`, variadic macros, designated initializers, or compound literals.
- Write comments with `/* ... */`; do not nest block comments.
- Declare variables at the beginning of a block, before executable statements.
- Use explicit function prototypes. Use an appropriate hosted entry point such as `int main(void)` or `int main(int argc, char *argv[])`.
- Return an explicit integer status from `main`: use `0` for normal completion and a nonzero value for errors.
- Use standard C90 library headers and facilities unless a task explicitly permits a platform-specific API.
- Do not rely on compiler extensions, implementation-defined behavior, or undocumented behavior.

## General Rules

1. Read the task's goal, specification, concepts, requirements, and references before implementing it.
2. Keep the implementation focused on the requested behavior; avoid unrelated features and dependencies.
3. Prefer clear names, simple control flow, consistent indentation, and readable formatting.
4. Keep state local to functions whenever possible. Do not introduce global mutable state unless the task explicitly allows it.
5. Validate arguments and handle relevant edge cases and failure paths rather than silently ignoring them.
6. Match the specified output exactly, including punctuation, capitalization, whitespace, and a trailing newline where required.
7. Store implementation files in `.c` files and declarations shared between files in `.h` files. Include the relevant standard headers.
8. Compile with a C90 conformance mode and warnings enabled where the toolchain supports them, for example `-std=c90 -pedantic -Wall -Wextra`.
9. Test the successful path, invalid-input paths, and the required exit statuses before considering a task complete.
10. If a task conflicts with these rules, follow these C90 rules and state the ambiguity in the task notes.

## Solutions

Each task may include a `solution/` directory containing one or more reference implementations — the [task index](#the-tasks) above links every one of them.

- Read the task and write your own implementation before opening a solution, unless the task explicitly says otherwise.
- Compile and test your attempt, including the required failure cases, before consulting the solution.
- If you are blocked, first reread the task, inspect compiler diagnostics, and reduce the problem to a small test case; view the relevant solution only after making a genuine attempt.
- Treat a solution as an example of one approach, not as the authoritative specification. The task requirements still take precedence.
- After viewing a solution, understand and reproduce the reasoning in your own code; do not copy it verbatim.
- Do not edit files in `solution/` unless the task explicitly requests changes.

## Navigation

- [C90 tutorial index](../README.md)
- [Course guide: Computer Architecture and Organization](../../README.md)
- [Reference book (PDF)](<../reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>)
