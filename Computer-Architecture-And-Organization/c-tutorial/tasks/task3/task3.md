# 3. Line, Word, and Character Counter

## Goal

Read a file one character at a time and learn how C signals the end of a stream, how to count without loading the whole file into memory, and how to report read errors.

## Project

Create an executable named `duckcount` that takes one input file and prints three counts:

```text
duckcount <file>
```

For a successful run, print exactly these three lines, with the numbers right-aligned in a column that starts at position 13:

```text
Lines:      <count>
Words:      <count>
Characters: <count>
```

Example:

```console
$ duckcount notes.txt
Lines:      12
Words:      87
Characters: 641
```

The three counts must be produced by three separate passes over the file. A line is any `\n` character, a word is any run of non-whitespace characters, and the character count includes every character returned by the reader, including newlines.

If no file is supplied, print a usage message to standard error and return a nonzero exit status. If the file cannot be opened or a read fails, print a diagnostic to standard error and return a nonzero exit status. Do not prompt for input.

## Concepts

- `fopen`, `fclose`, and the `FILE *` stream
- `fgetc` and the `int` return value
- `EOF` and why it is not the same as any byte value
- Stream error indicators: `ferror` and `feof`
- `rewind` to start a second pass over the same stream
- `<ctype.h>` classification with `isspace`
- Counting with `size_t`
- Reading a file without buffering it in memory

## Requirements

- Require exactly one command-line argument; treat anything else as a usage error.
- Check the result of `fopen` and report the failure instead of using the stream.
- Distinguish end of input (`EOF`) from a read error using `ferror`.
- Count with three separate passes, using `rewind` between them.
- Cast counts to `unsigned long` when printing so the format matches the argument.
- Close the input file on every path, including the error paths.
- Send diagnostics to standard error and return an explicit status from `main`: `0` for success, nonzero for errors.
- Follow C90 syntax: declare variables at the beginning of each block, use explicit function prototypes, and write comments with `/* ... */`.
- Keep mutable state local; do not use global mutable variables.
- Store the implementation in `task3.c` in this directory and include the relevant standard headers.
- Compile with warnings enabled and resolve any warnings caused by the program.

## Extension

Rewrite the three passes as a single pass that updates all three counters at once, then compare the results and the runtime on a large file. Note which version is easier to reason about.

## Workflow

1. Create `task3.c` in this directory and implement the specification without opening `solution/`.
2. Compile it with a C90 compiler, for example:

   ```text
   cc -std=c90 -pedantic -Wall -Wextra task3.c -o duckcount
   ```

3. Test an empty file, a file with no trailing newline, a file containing only whitespace, a file with several blank lines, a missing file, and a wrong argument count.
4. After making a genuine attempt, compare your work with [[`solution/task3.c`](solution/task3.c)](solution/task3.c). Use it to understand the reasoning, not as code to copy.
5. Treat this task's specification as authoritative; make sure your implementation meets it even if the reference solution takes a different approach.

## Book Reference

*Read these parts of* The C Programming Language, 2nd edition, Brian W. Kernighan and Dennis M. Ritchie. A copy is bundled with the tutorial in [`../../reference/`](<../../reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>). Page numbers are the printed page numbers.

- **pp. 18–19 — §1.5 Character Input and Output** — the stream model, `getchar`, and the crucial point that a distinct `EOF` value separates "no more input" from a valid data byte. `fgetc` is the `FILE *` version of the same idea.
- **p. 20 — §1.5.2 Character Counting** — the first counting program: read to `EOF` and increment a counter per character.
- **p. 21 — §1.5.3 Line Counting** — counting `\n` while reading, which is exactly the `count_lines` requirement.
- **pp. 22–23 — §1.5.4 Word Counting** — the `in_word` flag pattern that separates "another whitespace character" from "the start of a new word".
- **p. 23 — §1.5.4, discussion after the word counter** — the book asks how you would test a word counter; that question is this task's test list.
- **pp. 25–27 — §1.7 Functions** — split each pass into its own function that takes a `FILE *` and returns a count.
- **pp. 31–34 — §1.10 External Variables and Scope** — why the counters are function-local and reset for each pass.
- **pp. 73–74 — §4.5 Header Files** — where to put shared declarations if you split the program across files.
- **pp. 102–105 — §5.10 Command-line Arguments** — `argc`, `argv`, and the argument-count check for the file name.
- **pp. 135–136 — §7.1 Standard Input and Output** — what a `FILE *` is and why streams are the portable interface.
- **pp. 137–139 — §7.2 Formatted Output (`printf`)** — the `%lu` conversion used for the three counts.
- **pp. 142–145 — §7.5 File Access** — `fopen`, `fgetc`, and `fclose`, plus the book's `cat` program and the rule that `fclose` is what flushes buffered output.
- **p. 145 — §7.6 Error Handling: Stderr and Exit** — why diagnostics belong on standard error, and how the shell sees a nonzero status.
- **p. 148 — §7.8.2 Character Class Testing and Conversion** — `isspace`, and the requirement that its argument be `EOF` or an `unsigned char` value. This is why the counter casts before classifying.
- **p. 226 — Appendix B.1.7 Error Functions** — `feof`, `ferror`, `clearerr`, and `perror`, the exact functions this task's error handling uses.
- **pp. 226–227 — Appendix B.2 `<ctype.h>`** — the full list of character tests, including `isspace`.

## Book Exercises Worth Trying First

- **Exercise 1-7 (p. 20)** — print the value of `EOF`. Knowing the actual number makes the `int` return value of `fgetc` concrete.
- **Exercise 1-8 (p. 22)** — count blanks, tabs, and newlines. A five-line warm-up for the line counter and the whitespace rule.
- **Exercise 1-11 (p. 23)** — the book asks how you would test the word count program. Turn your answer into this task's test list before you start coding.
- **Exercise 1-9 (p. 22)** — squeeze repeated blanks. A good second exercise once the counting passes work.

## Friendly References

- **The book** ([`../../reference/`](<../../reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>) — *The C Programming Language*, 2nd edition, PDF) — §1.5 is the shortest, densest chapter-to-task match in the tutorial. Read `cat` (p. 18) and the three counters (pp. 20–23) in one sitting; they are variations of a single loop.
- [cppreference: `fgetc`](https://en.cppreference.com/w/c/io/fgetc) — the return contract in full: an `unsigned char` value promoted to `int`, or `EOF` on end of input or error.
- [cppreference: character input/output](https://en.cppreference.com/w/c/io) — the whole `getchar`/`fgetc` family in one place, with the "check `EOF` before the value" rule stated explicitly.
- [cppreference: `ferror`](https://en.cppreference.com/w/c/io/ferror), [`feof`](https://en.cppreference.com/w/c/io/feof), and [`clearerr`](https://en.cppreference.com/w/c/io/clearerr) — the three stream indicators, and why `feof` is only meaningful after a read.
- [cppreference: `perror`](https://en.cppreference.com/w/c/io/perror) — the shortest way to report a failed `fopen` with a real system message.
- [cppreference: `fopen`](https://en.cppreference.com/w/c/io/fopen) and [`fclose`](https://en.cppreference.com/w/c/io/fclose) — the `NULL` failure convention and the guarantee that `fclose` flushes buffers.
- [cppreference: `rewind`](https://en.cppreference.com/w/c/io/rewind) — the exact semantics of restarting a stream for the second and third passes.
- [cppreference: `size_t`](https://en.cppreference.com/w/c/types/size_t) — why the counters are unsigned and what the cast to `unsigned long` is for.
- [Bee's Guide to C Programming](https://beej.us/guide/bgc/) — a friendlier walkthrough of `for` loops and reading input, useful before you try the three-pass version.

## Navigation

[← 2. C90 Command-Line Calculator](../task2/task2.md) · [Task instructions](../instructions.md) · [All tasks](../../README.md) · [Course guide](../../../README.md) · [4. Custom String Library →](../task4/task4.md)
