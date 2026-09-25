# CS-Department-Guide

Study guides and resources for the **Computer Science (CS) department** at the
**Faculty of Computers and Artificial Intelligence (FCAI)**, **Cairo University**.

This repository is a collection of course guides. Each course lives in its own
folder and contains its own `README` describing:

- what the course is about
- what to expect (topics, material, grading signals, common gotchas)
- how to study it (lectures, references, practice)
- any code/labs and how to build and run them

## Courses

| Course | Guide | What to expect |
| --- | --- | --- |
| [Computer Architecture and Organization](Computer-Architecture-And-Organization/README.md) | course guide | the C90 tutorial (10 graded tasks built on *The C Programming Language*) plus the Patterson & Hennessy reference material |
| [Information Theory](Information-Theory/README.md) | course guide | entropy, source coding, dictionary methods (LZ77), lossless vs. lossy compression, lecture notes + reference book, C#, C++, JavaScript and Rust implementations |
| [Advanced Datastructures](Advanced-Datastructures/README.md) | course guide | hashing and hash tables (collisions, probing, growth), lecture notes + web reference, C++ implementations |

## Repository map

Every entry below is a link. Start at a course guide, then follow its links
down to lectures, references, and code.

```text
CS-Department-Guide/
├── README.md                                   ← this file
├── Advanced-Datastructures/                    ← course guide: [README](Advanced-Datastructures/README.md)
│   ├── theory/
│   │   ├── Lectures/Lecture1/README.md         ← [Lecture 1 — Hash Tables](Advanced-Datastructures/theory/Lectures/Lecture1/README.md)
│   │   └── Reference/README.md                 ← [Reference](Advanced-Datastructures/theory/Reference/README.md)
│   └── cpp/                                    ← C++ hash table (CMake)
├── Computer-Architecture-And-Organization/     ← course guide: [README](Computer-Architecture-And-Organization/README.md)
│   ├── theory/
│   │   ├── Lectures/Lecture1/                  ← [intro-from-book.pdf](Computer-Architecture-And-Organization/theory/Lectures/Lecture1/intro-from-book.pdf)
│   │   └── Reference/                          ← [Computer Organization and Design (PDF)](<Computer-Architecture-And-Organization/theory/Reference/Computer Organization and Design MIPS Edition (David A. Patterson, John L. Hennessy) (z-library.sk, 1lib.sk, z-lib.sk).pdf>)
│   └── c-tutorial/                             ← C tutorial: [README](Computer-Architecture-And-Organization/c-tutorial/README.md)
│       ├── reference/                          ← [The C Programming Language (PDF)](<Computer-Architecture-And-Organization/c-tutorial/reference/C Programming Language, 2nd Edition (Brian W. Kernighan, Dennis M. Ritchie) (z-library.sk, 1lib.sk, z-lib.sk).pdf>)
│       └── tasks/                              ← [task instructions](Computer-Architecture-And-Organization/c-tutorial/tasks/instructions.md) + `task1` … `task10`
└── Information-Theory/                         ← course guide: [README](Information-Theory/README.md)
    ├── theory/
    │   ├── Lectures/Lecture1/README.md         ← [Lecture 1 — Introduction to LZ77](Information-Theory/theory/Lectures/Lecture1/README.md)
    │   └── Reference/                          ← [Introduction to Data Compression (PDF)](Information-Theory/theory/Reference/Introduction-to-data-compression.pdf)
    ├── c#/                                     ← [C# guide](Information-Theory/c%23/README.md)
    ├── cpp/                                    ← C++ LZ77 (CMake)
    ├── js/                                     ← [JavaScript guide](Information-Theory/js/README.md)
    └── rust/                                   ← [Rust guide](Information-Theory/rust/README.md)
```

## How to study

1. Read the course `README` first to get the big picture and know what to expect.
2. Go through the `theory/` material of that course.
3. Practice with the code: the C90 tasks for Computer Architecture, or the C#,
   C++, JavaScript and Rust demos for the other courses (commands below).

## Building and running the C90 tutorial

The C tutorial is plain C90 and needs no build system. Compile a single task
from its own folder:

```sh
cd Computer-Architecture-And-Organization/c-tutorial/tasks/task1
cc -std=c90 -pedantic -Wall -Wextra task1.c -o duckhello
./duckhello Alice
```

See the [C tutorial guide](Computer-Architecture-And-Organization/c-tutorial/README.md)
for the task list and the [task instructions](Computer-Architecture-And-Organization/c-tutorial/tasks/instructions.md)
for the rules every task must follow.

## Building and running the C# labs

C# code lives in each course's `c#/` folder and builds with the .NET SDK:

```sh
dotnet run --project Information-Theory/c#
```

`dotnet` compiles the code into `c#/bin` and `c#/obj`, which are ignored by git.
See the [C# guide](Information-Theory/c%23/README.md) for demo details.

## Building the C++ labs

C++ code lives in each course's `cpp/` folder and builds with CMake:

```sh
cmake -S Information-Theory/cpp -B Information-Theory/cpp/build
cmake --build Information-Theory/cpp/build
```

Binaries land in `<Course>/cpp/bin` (possibly in a configuration subfolder).
Build artifacts are ignored by git. See the course `README` for demo details.

## Running the Rust labs

Rust code lives in each course's `rust/` folder. Install Rust 1.85 or newer, then run:

```sh
cargo run --manifest-path Information-Theory/rust/Cargo.toml
```

Cargo compiles the code into `rust/target/`, which is ignored by git.
See the [Rust guide](Information-Theory/rust/README.md) for demo details.

## Running the JavaScript labs

JS code lives in each course's `js/` folder and uses only Node.js built-ins (no
third-party dependencies). Install Node 18 or newer, then run from `Information-Theory/js`:

```sh
npm start                  # runs the demo
npm start -- "my string"   # run the demo on a specific string
npm test                   # runs the unit tests in test/
```

See the [JavaScript guide](Information-Theory/js/README.md) for demo details.
