# C90 Tutorial — Task Index

Ten C90 tasks that build up from a command-line greeting to file utilities,
using *The C Programming Language*, 2nd edition, as the reference text.

- Course guide: [Computer Architecture and Organization](../README.md)
- Rules for every task: [task instructions](tasks/instructions.md)
- The book itself: [`reference/` — *The C Programming Language*, 2nd edition (PDF)](<reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>)

## The tasks

Work them in order; each one assumes the previous ones.

| # | Task | Main C material | Solution files |
| --- | --- | --- | --- |
| 1 | [Hello C: Command-Line Greeting](tasks/task1/task1.md) | `argc`/`argv`, `printf`, exit statuses | [`task1.c`](tasks/task1/solution/task1.c) |
| 2 | [C90 Command-Line Calculator](tasks/task2/task2.md) | expressions, conversions, control flow | [`task2.c`](tasks/task2/solution/task2.c) |
| 3 | [Line, Word, and Character Counter](tasks/task3/task3.md) | `getchar`, `EOF`, streams | [`task3.c`](tasks/task3/solution/task3.c) |
| 4 | [Custom String Library](tasks/task4/task4.md) | pointers, address arithmetic, `char *` | [`duck_string.h`](tasks/task4/solution/duck_string.h), [`duck_string.c`](tasks/task4/solution/duck_string.c), [`task4.c`](tasks/task4/solution/task4.c) |
| 5 | [Dynamic Array](tasks/task5/task5.md) | `malloc`/`realloc`/`free`, growth | [`Vector.h`](tasks/task5/solution/Vector.h), [`Vector.c`](tasks/task5/solution/Vector.c), [`task5.c`](tasks/task5/solution/task5.c) |
| 6 | [Generic Dynamic Array](tasks/task6/task6.md) | byte buffers, `size_t` arithmetic | [`Vector.h`](tasks/task6/solution/Vector.h), [`Vector.c`](tasks/task6/solution/Vector.c), [`task6.c`](tasks/task6/solution/task6.c) |
| 7 | [Linked List](tasks/task7/task7.md) | self-referential structs, `->` | [`Linkedlist.h`](tasks/task7/solution/Linkedlist.h), [`Linkedlist.c`](tasks/task7/solution/Linkedlist.c), [`task7.c`](tasks/task7/solution/task7.c) |
| 8 | [Stack, Queue and Deque](tasks/task8/task8.md) | ADT discipline over shared storage | [`Stack.h`](tasks/task8/solution/Stack.h), [`Stack.c`](tasks/task8/solution/Stack.c), [`Linkedlist.c`](tasks/task8/solution/Linkedlist.c), [`task8.c`](tasks/task8/solution/task8.c) |
| 9 | [Hash Table](tasks/task9/task9.md) | linear probing, function pointers | [`HashTable.h`](tasks/task9/solution/HashTable.h), [`HashTable.c`](tasks/task9/solution/HashTable.c), [`task9.c`](tasks/task9/solution/task9.c) |
| 10 | [File Utility](tasks/task10/task10.md) | `fopen`/`fread`/`fwrite`, `fseek`/`ftell` | [`duck_file.h`](tasks/task10/solution/duck_file.h), [`duck_file.c`](tasks/task10/solution/duck_file.c), [`task10.c`](tasks/task10/solution/task10.c) |

## Compiling a task

No build system is needed — compile the task's own `.c` files with a C90
compiler. From inside a task folder:

```sh
cc -std=c90 -pedantic -Wall -Wextra task1.c -o duckhello
./duckhello Alice
```

For the tasks that ship a library plus a test program, compile both units:

```sh
cc -std=c90 -pedantic -Wall -Wextra solution/duck_string.c solution/task4.c -o task4
```

## Rules

Read [tasks/instructions.md](tasks/instructions.md) before starting: it defines the
C90 baseline that every task and every solution follows, and it explains when to
open a `solution/` directory.
