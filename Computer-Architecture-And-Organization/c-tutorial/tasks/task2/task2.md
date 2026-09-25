# 2. C90 Command-Line Calculator

## Goal

Learn C expressions and control flow by writing a command-line calculator that reads two integers and performs one arithmetic operation.

## Specification

Create an executable named `duckcalc` with this interface:

```text
duckcalc <left> <operator> <right>
```

The program must support these operators:

- `+` for addition
- `-` for subtraction
- `*` for multiplication
- `/` for integer division
- `%` for the integer remainder

For a valid operation, print exactly the result in this format, followed by a newline:

```text
ans = <result>
```

Examples:

```console
$ duckcalc 10 + 20
ans = 30
$ duckcalc 20 * 5
ans = 100
$ duckcalc 100 / 4
ans = 25
$ duckcalc 17 % 3
ans = 2
```

The operands are signed decimal integers. A number may have an optional `+` or `-` sign, but must contain at least one digit and no other characters. Do not prompt for input.

If the argument count is wrong, a number is invalid, the operator is missing or unsupported, division by zero occurs, or an operation cannot produce an `int` result, print a diagnostic to standard error and return a nonzero exit status. Return `0` only after a successful calculation.

## Concepts

- Arithmetic operators: `+`, `-`, `*`, `/`, and `%`
- Integer types and the limits of `int`
- Floating-point types and why this task stays with integer arithmetic
- Comparisons and Boolean expressions
- `if` and `else`
- `switch`, `case`, `default`, and `break`
- `while` and `for`
- Functions, function prototypes, parameters, and return values
- Manual character-to-integer conversion and type conversions
- Command-line arguments, standard error, and exit statuses

## Requirements

- Require exactly three command-line arguments after the executable name.
- Parse both operands manually by inspecting their characters.
- Do not initially use `atoi()`; implement the conversion rather than delegating it to a library function.
- Accept only one of the five specified operator characters.
- Use integer arithmetic for all five operations; do not convert the operands to `float` or `double`.
- Reject division or remainder by zero.
- Reject values and operation results that are outside the range of `int`.
- Print the exact success format, including the trailing newline.
- Send error diagnostics to standard error and return an explicit status from `main`.
- Keep mutable state local; do not use global mutable variables.
- Follow C90 syntax: declare variables at the beginning of each block, use `/* ... */` comments if needed, and use explicit function prototypes.
- Store the implementation in `task2.c` in this directory and include the relevant standard headers.
- Compile with warnings enabled and resolve warnings caused by the program.

## Extension

After the required calculator works, add support for a parenthesized expression passed as one quoted command-line argument:

```console
$ duckcalc "(10 + 5) * 3"
ans = 45
```

The extension should support the five operators, parentheses, unary signs, and normal operator precedence. Keep the required two-operand interface working as well.

## Workflow

1. Create `task2.c` in this directory and implement the required interface without opening `solution/`.
2. Compile with a C90 compiler, for example:

   ```text
   cc -std=c90 -pedantic -Wall -Wextra task2.c -o duckcalc
   ```

3. Test valid operations, negative operands, malformed numbers, unsupported or multi-character operators, wrong argument counts, division by zero, and out-of-range values.
4. After making a genuine attempt, compare your work with [[`solution/task2.c`](solution/task2.c)](solution/task2.c). Use it to understand the reasoning, not as code to copy.
5. Treat this task's specification as authoritative; make sure your implementation meets it even if the reference solution takes a different approach.

## Book Reference

*Read these parts of* The C Programming Language, 2nd edition, Brian W. Kernighan and Dennis M. Ritchie. A copy is bundled with the tutorial in [`../../reference/`](<../../reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>). Page numbers are the printed page numbers.

- **pp. 11–14 — §1.2 Variables and Arithmetic Expressions** — declaration syntax, `int`, `char`, and arithmetic expressions; the manual character-to-integer conversion in this task is a direct extension of this material.
- **pp. 14–17 — §1.2 Expressions, `for`, and symbolic constants** — operator results become the building blocks of the parser loop.
- **pp. 25–27 — §1.7 Functions** — prototypes, parameters, and returning a value; the manual parser is a function that returns a status.
- **pp. 31–34 — §1.10 External Variables and Scope** — why the task requires local state: it disappears when the function returns.
- **pp. 35–39 — §2.1–2.4 Types, Sizes, Constants, and Declarations** — the `int` range, the `const` idea, and where C90 requires declarations to appear.
- **pp. 40–41 — §2.5 Arithmetic Operators** — `+`, `-`, `*`, `/`, and `%`, including integer division truncating and the remainder rule.
- **pp. 41–44 — §2.6 Relational and Logical Operators, §2.7 Type Conversions** — the comparison logic for each operator, and the character-to-`int` conversions this task performs by hand.
- **p. 49 — §2.12 Precedence and Order of Evaluation** — required reading before you add the parenthesized-expression extension.
- **pp. 52–53 — §3.1 Statements and Blocks, §3.2 If-Else, §3.3 Else-If** — block scope and the branch structure used for validation.
- **pp. 54–55 — §3.4 Switch** — the natural structure for dispatching on `+`, `-`, `*`, `/`, and `%`; note the book's habit of ending each `case` with `break`.
- **pp. 56–58 — §3.5 Loops: While and For** — walking the characters of each operand.
- **pp. 62–66 — §4.1 Basics of Functions, §4.2 Functions Returning Non-integers** — declaration order, explicit prototypes, and why the parser can return an `int` status.
- **pp. 67–71 — §4.3 External Variables (the calculator program)** — the book's own calculator: a `switch`-driven loop that converts text to numbers. Read it as the model for the required extension.
- **pp. 73–74 — §4.5 Header Files** — separating declarations from the implementation when the program grows.
- **pp. 102–105 — §5.10 Command-line Arguments** — `argc`, `argv`, and the exact argument-count checks this task demands.
- **pp. 137–139 — §7.2 Formatted Output (`printf`)** — the `%d` conversion and the exact `ans = <result>` format.
- **p. 145 — §7.6 Error Handling: Stderr and Exit** — diagnostics on the error stream and nonzero exit statuses.
- **p. 235 — Appendix B.11 `<limits.h>`** — `INT_MIN` and `INT_MAX`, the bounds the range checks use.

## Book Exercises Worth Trying First

- **Exercise 2-3 (p. 44)** — write `htoi(s)`, which converts a string of hexadecimal digits to a value. It is the same "inspect characters and build a number" loop this task needs, in about ten lines.
- **Exercise 5-1 (p. 87)** — `getint` treats a `+` or `-` not followed by a digit as a valid number. Fixing that is precisely the "must contain at least one digit" rule in this specification.
- **Exercise 4-3 (p. 71)** — extend the book's calculator. Do this after the required two-operand version works; it is a direct model for the parenthesized-expression extension.

## Friendly References

- **The book** ([`../../reference/`](<../../reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>) — *The C Programming Language*, 2nd edition, PDF) — Chapters 2 and 3 are the whole task in miniature: operators, conversions, and the three control-flow statements you need. Read them in order and the calculator stops feeling arbitrary.
- [cppreference: operators in C](https://en.cppreference.com/w/c/language/operators) — one page for every operator, including the integer-division and remainder rules and the full precedence table.
- [cppreference: `switch`](https://en.cppreference.com/w/c/language/switch) — the `case`/`default`/`break` pattern, including the "fall through" warning that matters here.
- [cppreference: `for`](https://en.cppreference.com/w/c/language/for) and [`while`](https://en.cppreference.com/w/c/language/while) — loop syntax, including the empty-body and null-statement idioms the book uses.
- [cppreference: `<limits.h>` integer limits](https://en.cppreference.com/w/c/types/limits) — where `INT_MIN`, `INT_MAX`, and `UINT_MAX` are defined and their minimum required values.
- [cppreference: type conversions](https://en.cppreference.com/w/c/language/conversion) — what happens to a value that does not fit, which is the reasoning behind the range checks.
- [Bee's Guide to C Programming](https://beej.us/guide/bgc/) — a gentler second pass if operator precedence and integer division are still slippery.

Note: the book's examples use some older declaration styles; follow the C90-compatible declarations required by this task.

## Navigation

[← 1. Hello C: Command-Line Greeting](../task1/task1.md) · [Task instructions](../instructions.md) · [All tasks](../../README.md) · [Course guide](../../../README.md) · [3. Line, Word, and Character Counter →](../task3/task3.md)
