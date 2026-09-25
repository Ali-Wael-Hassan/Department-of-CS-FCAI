# 10. File Utility

## Goal

Become comfortable with standard C file I/O.

## Project

Implement four stream-based file utilities:

- `duckcat` — copy two input streams to one output stream
- `duckcopy` — copy one stream to another
- `duckhead` — copy the first ten lines
- `ducktail` — copy the last ten lines

The supplied implementation exposes these operations as functions over `FILE *` streams:

```c
void duckcat(FILE *left, FILE *right, FILE *out);
void duckcopy(FILE *dst, FILE *src);
void duckhead(FILE *src, FILE *out);
void ducktail(FILE *src, FILE *out);
```

## Concepts

- `fopen`
- `fclose`
- `fread`
- `fwrite`
- `fseek`
- `ftell`
- `fgetc`
- `fputc`
- `EOF`
- Text and binary streams
- Stream error indicators

## Requirements

- Handle missing files at the caller side with `fopen` failure checks.
- Propagate stream errors visibly through `ferror` after reads and writes.
- Treat `EOF` as the normal end-of-input condition, not as a data byte.
- Preserve text contents and arbitrary binary bytes.
- Use `fseek` and `ftell` for the tail operation.
- Copy the first ten complete lines for `duckhead` and the last ten complete lines for `ducktail`.
- Close every successfully opened stream.
- Follow C90 syntax: declare variables at the beginning of each block, use explicit function prototypes, and include the relevant standard headers.
- Keep mutable state local; do not use global mutable variables.

## Tests

Use temporary binary streams to test concatenation, binary copying, head and tail boundaries, short and empty files, EOF handling, `fseek`/`ftell`, missing-file opening, and stream error indicators. The test program belongs in [`solution/task10.c`](solution/task10.c).

## Workflow

1. Keep the supplied declarations in [`solution/duck_file.h`](solution/duck_file.h).
2. Keep the supplied implementation in [`solution/duck_file.c`](solution/duck_file.c).
3. Implement the test `main` in [`solution/task10.c`](solution/task10.c).
4. Compile and run the tests.

## Book Reference

*Read these parts of* The C Programming Language, 2nd edition, Brian W. Kernighan and Dennis M. Ritchie. A copy is bundled with the tutorial in [`../../reference/`](<../../reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>). Page numbers are the printed page numbers.

- **pp. 18–19 — §1.5 Character Input and Output** — text streams, `getchar`, and why `EOF` is a distinct `int` value rather than a byte. This is the rule that keeps `duckhead` and `ducktail` from copying a stray `0xFF` at the end of a file.
- **pp. 135–136 — §7.1 Standard Input and Output** — what a `FILE *` is and why streams are the portable interface; the four utilities in this task are written against that interface, not against a specific operating system.
- **pp. 137–139 — §7.2 Formatted Output (`printf`)** — `printf` and `fprintf` on a stream, which is how the caller reports diagnostics.
- **pp. 142–145 — §7.5 File Access** — the core of this task: `fopen`, `fgetc`, `fputc`, `fclose`, and the book's `cat` program. Note the rule that `fclose` is what flushes a write buffer.
- **p. 145 — §7.6 Error Handling: Stderr and Exit** — the book's criticism of `cat`'s error handling, and the convention of reporting diagnostics on standard error with a nonzero exit status.
- **pp. 155–156 — §8.4 Random Access: `lseek`** — the system-call view of "move the file position, then read backwards". The concept behind `ducktail`'s use of `fseek` and `ftell`.
- **p. 220 — Appendix B, library summary introduction** — the split between the language and the library, which is why these utilities are four small functions rather than one program.
- **p. 221 — Appendix B.1.1 File Operations** — `fopen` and the full list of modes, including `"rb"` and `"wb"`. The reference for choosing binary mode when copying arbitrary bytes.
- **p. 225 — Appendix B.1.4 and B.1.5 Character and Direct Input/Output** — `getc`, `putc`, `fgetc`, `fputc`, `fread`, and `fwrite`, including the return values to check.
- **p. 226 — Appendix B.1.6 File Positioning Functions** — `fseek` with `SEEK_SET`, `SEEK_CUR`, and `SEEK_END`, and `ftell`; the exact contract `ducktail` depends on.
- **p. 226 — Appendix B.1.7 Error Functions** — `feof`, `ferror`, `clearerr`, and `perror`, the functions the tests use to assert that EOF is distinguished from a read error.
- **pp. 87–89 — §5.3 Pointers and Arrays** — how the simple ring-buffer or last-ten-line approach can be written with pointer arithmetic if the byte-copy version proves awkward.
- **p. 106 — Exercise 5-13** — the book's own `tail` program, which prints the last `n` lines of its input and defaults to ten. Read it before writing `ducktail`; the boundary case where the file does not end in a newline is exactly the trap in this task.
- **p. 155 — Exercise 8-1** — rewrite the Chapter 7 `cat` using `read`, `write`, `open`, and `close`. Optional, and a good contrast between buffered streams and raw descriptors.

## Book Exercises Worth Trying First

- **Exercise 1-7 (p. 20)** — print the value of `EOF`. Thirty seconds of work that makes the `int` return contract of `fgetc` concrete.
- **Exercise 5-13 (p. 106)** — the `tail` program. The single most relevant exercise in the book for this task; implement it standalone, then adapt it to the `FILE *` signature.
- **Exercise 7-6 (p. 147)** — compare two files and print the first line where they differ. An excellent model for a byte-oriented `duckcat` test and for reasoning about line boundaries.
- **Exercise 1-9 (p. 22)** — squeeze repeated blanks while copying input to output. A small, complete `duckcopy`-style program.

## Friendly References

- **The book** ([`../../reference/`](<../../reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>) — *The C Programming Language*, 2nd edition, PDF) — Chapter 7's `cat` (p. 18 and p. 143) and `tail` (p. 106) are the ancestor programs of all four utilities here. Reading them side by side with this task's specification makes the differences obvious.
- [cppreference: C input/output](https://en.cppreference.com/w/c/io) — the whole stream library in one index; the fastest way to look up a function while writing tests.
- [cppreference: `fopen`](https://en.cppreference.com/w/c/io/fopen) — mode strings, the `NULL` failure convention, and why `"rb"` matters for byte-preserving copies.
- [cppreference: `fgetc`](https://en.cppreference.com/w/c/io/fgetc) — the precise return contract: an `unsigned char` value as `int`, or `EOF`. Copy this rule into your loop conditions.
- [cppreference: `fread`](https://en.cppreference.com/w/c/io/fread) and [`fwrite`](https://en.cppreference.com/w/c/io/fwrite) — block copying, and the return value to check when a transfer ends early.
- [cppreference: `fputc`](https://en.cppreference.com/w/c/io/fputc) — the byte-at-a-time counterpart, used by the line-oriented utilities.
- [cppreference: `fseek`](https://en.cppreference.com/w/c/io/fseek) and [`ftell`](https://en.cppreference.com/w/c/io/ftell) — the `SEEK_END` repositioning and size query that `ducktail` is built on, including the text-versus-binary caveat.
- [cppreference: `ferror`](https://en.cppreference.com/w/c/io/ferror), [`feof`](https://en.cppreference.com/w/c/io/feof), and [`clearerr`](https://en.cppreference.com/w/c/io/clearerr) — the three stream indicators, and the rule that `feof` only becomes true after a read attempt hits the end.
- [cppreference: `fclose`](https://en.cppreference.com/w/c/io/fclose) — the flush guarantee, and why every success path in the caller must close its streams.
- [cppreference: `tmpfile`](https://en.cppreference.com/w/c/io/tmpfile) — the anonymous temporary stream used by the test program so no cleanup files are needed.
- [cppreference: `perror`](https://en.cppreference.com/w/c/io/perror) — the shortest way to turn a failed `fopen` into a useful message.
- [Bee's Guide to C Programming](https://beej.us/guide/bgc/) — its file-handling material is approachable if the book's terse `cat` walkthrough moves too quickly.

## Navigation

[← 9. Hash Table](../task9/task9.md) · [Task instructions](../instructions.md) · [All tasks](../../README.md) · [Course guide](../../../README.md)
