# 1. Hello C: Command-Line Greeting

## Goal

Write, compile, and run a small C program that accepts a name from the command line and prints a personalized greeting.

## Specification

Create an executable named `duckhello` that accepts exactly one argument, `<name>`:

```text
duckhello <name>
```

For a successful invocation, print exactly the following line, followed by a newline:

```text
Hello, <name>!
```

Example:

```console
$ duckhello Alice
Hello, Alice!
```

If no name or more than one name is supplied, print a usage message to standard error and return a nonzero exit status. Do not prompt for input.

## Concepts

- `main` and the `int main(int argc, char *argv[])` entry point
- `argc` and `argv`
- Local variables and basic types, including `int` and `char *`
- Format strings, `printf`, and the `%s` conversion
- `return` values and successful versus error exit statuses
- Standard headers such as `<stdio.h>`
- Compilation, `.c` source files, and `.h` header files
- Comments and readable formatting

## Requirements

- Validate the command-line arguments before using `argv[1]`.
- Print the greeting exactly as specified.
- Return `0` for success and a nonzero value for invalid usage.
- Keep mutable state local; do not use global mutable variables.
- Store the implementation in a `.c` file and include the relevant standard header(s).
- Compile with warnings enabled and resolve any warnings caused by the program.

## Workflow

1. Create `task1.c` in this directory and implement the specification without opening `solution/`.
2. Compile it with a C90 compiler and test valid, missing, and extra-argument cases.
3. After making a genuine attempt, compare your work with [`solution/task1.c`](solution/task1.c). Use it to understand the reasoning, not as code to copy.
4. Treat this task's specification as authoritative; make sure your implementation meets it even if the reference solution takes a different approach.

## Book Reference

*Read these parts of* The C Programming Language, 2nd edition, Brian W. Kernighan and Dennis M. Ritchie. A copy is bundled with the tutorial in [`../../reference/`](<../../reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>), so you can read it without leaving it. Page numbers are the printed page numbers.

- **pp. 9–10 — §1.1 Getting Started** — create a `.c` file, compile it with `cc`, and run the result. This is the exact build loop the task asks for.
- **p. 11 — §1.1 `printf` and string constants** — the `"Hello, ...!\n"` literal, string constants, and the `\n` newline you must print.
- **pp. 12–14 — §1.2 Variables, arithmetic, and basic types** — declaration syntax, `int`, `char`, and comments in `/* ... */` form.
- **pp. 14–15 — §1.2, declaring and initializing variables** — why declaring a variable at the point of first use, and initializing it there, is the house style this tutorial follows.
- **pp. 25–27 — §1.7 Functions** — how a function reports a result with `return`, and what returning `0` from `main` means to the shell.
- **pp. 31–34 — §1.10 External Variables and Scope** — why the task forbids global mutable state: local variables disappear when the block ends.
- **pp. 102–105 — §5.10 Command-line Arguments** — the heart of this task: `argc`, `argv`, `argv[0]`, and iterating over arguments.
- **pp. 137–139 — §7.2 Formatted Output (`printf`)** — the `%s` conversion, field widths, and escape sequences in the format string.
- **p. 145 — §7.6 Error Handling: Stderr and Exit** — writing diagnostics to `stderr` and how a nonzero exit status is reported to the shell.
- **pp. 73–74 — §4.5 Header Files** — why declarations belong in a `.h` file and the implementation in a `.c` file.
- **p. 235 — Appendix B.11 `<limits.h>`** — the reference table for `int` limits; handy background for the `int` return type.

## Book Exercises Worth Trying First

- **Exercise 1-1 (p. 11)** — run the book's `hello, world` program and experiment with the `printf` argument string. This is the smallest warm-up for this task.
- **Exercise 1-2 (p. 11)** — deliberately break the string and newline to see how `printf` behaves. Doing this once makes the exact-output requirement in this task obvious.

## Friendly References

- **The book** ([`../../reference/`](<../../reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>) — *The C Programming Language*, 2nd edition, PDF) — start with the pages above in order; the exercises are small on purpose and each one is a stepping stone to the next.
- [cppreference: C language](https://en.cppreference.com/w/c.html) — the front door for the whole language: keywords, basic types, and links into every topic you need.
- [cppreference: `main` function](https://en.cppreference.com/w/c/language/main_function) — the formal rules for `int main(int argc, char *argv[])` and what a return value does.
- [cppreference: arrays](https://en.cppreference.com/w/c/language/array) and [pointers](https://en.cppreference.com/w/c/language/pointer) — use these later, once `argv` starts to feel strange, to see how `argv` is really an array of pointers to strings.
- [cppreference: `printf`](https://en.cppreference.com/w/c/io/printf) — the complete conversion list, including `%s` and the flags that control spacing.
- [cppreference: `fprintf`](https://en.cppreference.com/w/c/io/fprintf) — writing diagnostics to the error stream, which is what a usage message needs.
- [cppreference: `return`](https://en.cppreference.com/w/c/language/return) — the rules for returning a value from `main` and what zero versus nonzero means.
- [Bee's Guide to C Programming](https://beej.us/guide/bgc/) — a warmer, conversational companion if the book's terse style feels abrupt.

Note: some examples in the book use older function-declaration syntax and an implicit `int` return type. Use the modern `int main(int argc, char *argv[])` form that this task requires.

## Navigation

[← Task instructions](../instructions.md) · [All tasks](../../README.md) · [Course guide](../../../README.md) · [2. C90 Command-Line Calculator →](../task2/task2.md)
