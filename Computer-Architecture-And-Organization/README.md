# Computer Architecture and Organization — Course Guide

Part of the CS department (FCAI, Cairo University) study guides at the
[repository root](../README.md).

## What to expect

Computer Architecture and Organization is about how a machine is built and how
software maps onto that machine. In this repository the material currently
covers two things:

- the **C90 tutorial** — ten hands-on tasks that rebuild the parts of C you
  otherwise only use, from the command line up to file utilities
- the **architecture reference** — Patterson & Hennessy, the standard text for
  how the ISA, the datapath, the memory hierarchy, and the pipeline fit together

- **Core topics in the tutorial**
  - The C90 language standard: declarations, `printf`, and exit statuses
  - Expressions, conversions, operators, and control flow
  - Streams: `getchar`/`fgetc`, `EOF`, line counting
  - Pointers, address arithmetic, and byte strings
  - Dynamic storage: `malloc`, `realloc`, `free`
  - Structures, self-referential structures, and `typedef`
  - Linear probing hash tables
  - File access: `fopen`, `fread`/`fwrite`, `fseek`/`ftell`
- **Theory material**
  - [`theory/Lectures/Lecture1/`](theory/Lectures/Lecture1/intro-from-book.pdf) — the
    lecture excerpt for the first session
    ([`intro-from-book.pdf`](theory/Lectures/Lecture1/intro-from-book.pdf))
  - [`theory/Reference/`](theory/Reference/README.md) — *Computer Organization and
    Design*, the MIPS edition
- **Code**
  - [`c-tutorial/`](c-tutorial/README.md) — the ten C90 tasks, their reference
    solutions, and the bundled copy of *The C Programming Language*

## How to study

1. Read the [C tutorial guide](c-tutorial/README.md) and the
   [task instructions](c-tutorial/tasks/instructions.md).
2. Work the tasks in order — each one only assumes the previous ones.
3. Read the book pages listed in each task before implementing it.
4. Use the [architecture reference](theory/Reference/) for the hardware side.

## The C90 tutorial

```sh
cd c-tutorial/tasks/task1
cc -std=c90 -pedantic -Wall -Wextra task1.c -o duckhello
./duckhello Alice
```

Each task has a `taskN.md` specification and a `solution/` directory with a
reference implementation. Write your own attempt first — see the
[instructions on solutions](c-tutorial/tasks/instructions.md#solutions).

| # | Task | What you build |
| --- | --- | --- |
| 1 | [Hello C: Command-Line Greeting](c-tutorial/tasks/task1/task1.md) | `argc`/`argv`, `printf`, exit statuses |
| 2 | [C90 Command-Line Calculator](c-tutorial/tasks/task2/task2.md) | expressions, conversions, control flow |
| 3 | [Line, Word, and Character Counter](c-tutorial/tasks/task3/task3.md) | `getchar`, `EOF`, stream reading |
| 4 | [Custom String Library](c-tutorial/tasks/task4/task4.md) | pointers, address arithmetic, `char *` |
| 5 | [Dynamic Array](c-tutorial/tasks/task5/task5.md) | `malloc`/`realloc`/`free`, growth |
| 6 | [Generic Dynamic Array](c-tutorial/tasks/task6/task6.md) | byte buffers, `size_t` arithmetic |
| 7 | [Linked List](c-tutorial/tasks/task7/task7.md) | self-referential structs, `->` |
| 8 | [Stack, Queue and Deque](c-tutorial/tasks/task8/task8.md) | ADT discipline over shared storage |
| 9 | [Hash Table](c-tutorial/tasks/task9/task9.md) | linear probing, function pointers |
| 10 | [File Utility](c-tutorial/tasks/task10/task10.md) | `fopen`/`fread`/`fwrite`, `fseek`/`ftell` |

## Layout

```text
Computer-Architecture-And-Organization/
├── README.md                              ← this file
├── theory/
│   ├── Lectures/Lecture1/README.md        ← [Introduction](theory/Lectures/Lecture1/README.md) + `intro-from-book.pdf`
│   └── Reference/README.md                ← [Computer Organization and Design (MIPS edition)](theory/Reference/README.md)
└── c-tutorial/
    ├── README.md                          ← [tutorial guide and task index](c-tutorial/README.md)
    ├── reference/                         ← The C Programming Language, 2nd edition (PDF)
    └── tasks/
        ├── instructions.md                ← [C90 rules that every task follows](c-tutorial/tasks/instructions.md)
        ├── task1/task1.md                 ← specification (+ solution/)
        ├── ...
        └── task10/task10.md               ← specification (+ solution/)
```

## Navigation

- [Repository root](../README.md)
- [C90 tutorial index](c-tutorial/README.md) — all ten tasks
- [Task instructions](c-tutorial/tasks/instructions.md) — the C90 baseline
- [Lecture 1 — Introduction](theory/Lectures/Lecture1/README.md)
- [Reference book](theory/Reference/README.md)

Build outputs (`bin/`, `build/`, `obj/`, `target/`, `*.exe`) are ignored by git.
