# Advanced Datastructures — Course Guide

Part of the CS department (FCAI, Cairo University) study guides at the
[repository root](../README.md).

## What to expect

Advanced Datastructures goes beyond the basics (arrays, linked lists) into
structures designed for performance: how data is stored, hashed, indexed, and
searched under memory/speed constraints. The current material focuses on hash
tables, with more topics as lectures are added.

- **Core topics**
  - Hashing: hash functions, collisions, load factor
  - Open addressing: probing sequences and table growth
  - Deletion and re-insertion strategies (keeping probes correct)
  - Load-factor-triggered growth (re-hash into a bigger table)
- **Theory material**
  - [`theory/Lectures/`](theory/Lectures/Lecture1/README.md) — lecture notes
    (currently [Lecture 1 — Hash Tables](theory/Lectures/Lecture1/README.md))
  - [`theory/Reference/`](theory/Reference/README.md) — the reference material
    used for the course
- **Code**
  - [`cpp/include/`](cpp/include/) — C++ headers (the `duck` hash-table
    implementation)
  - [`cpp/src/`](cpp/src/) — C++ implementations + a demo
  - [`cpp/CMakeLists.txt`](cpp/CMakeLists.txt) — C++ build configuration

## How to study

1. Read the lecture notes in `theory/Lectures/` in order, starting with
   [Lecture 1 — Hash Tables](theory/Lectures/Lecture1/README.md).
2. Cross-check with the reference in [`theory/Reference/`](theory/Reference/README.md).
3. Implement and experiment with the code demo (see below).

## Building and running the C++ demo

Run these commands from `Advanced-Datastructures/` with CMake and a C++17
compiler installed:

```sh
cmake -S cpp -B cpp/build
cmake --build cpp/build
```

The `advanced_datastructures_demo` binary is written to `cpp/bin/` (or a
configuration subfolder such as `cpp/bin/Debug/` with Visual Studio). It
exercises the `duck::DuckHashtable` template:

- inserting 0..99 into an `int` table and reporting size vs. capacity
- `contains` / `get` lookups, including false-positive checks
- removing every even element and verifying consistency
- a `std::string` table with duplicate-insert handling
- copy/move construction and `clear()`

### C++ files

| File | What it is |
| --- | --- |
| [`cpp/include/DuckHashtable.h`](cpp/include/DuckHashtable.h) | the `duck::DuckHashtable<T>` class declaration |
| [`cpp/include/DuckHash.h`](cpp/include/DuckHash.h) | `duck_hash` and its `int` / `std::string` specializations |
| [`cpp/src/Hashtable.tpp`](cpp/src/Hashtable.tpp) | the template implementation (probing, growth, deletion) |
| [`cpp/src/DuckHashtableDemo.cpp`](cpp/src/DuckHashtableDemo.cpp) | the demo program |
| [`cpp/CMakeLists.txt`](cpp/CMakeLists.txt) | build configuration (binary name `advanced_datastructures_demo`) |

## Layout

```text
Advanced-Datastructures/
├── README.md                                    ← this file
├── theory/
│   ├── Lectures/Lecture1/README.md              ← [Lecture 1 — Hash Tables](theory/Lectures/Lecture1/README.md)
│   └── Reference/README.md                      ← [theory/Reference/](theory/Reference/README.md)
└── cpp/                                        ← hash table (CMake → cpp/bin/advanced_datastructures_demo)
    ├── include/
    │   ├── DuckHash.h
    │   └── DuckHashtable.h
    └── src/
        ├── DuckHashtableDemo.cpp
        └── Hashtable.tpp
```

Build outputs (`bin/`, `build/`, `*.exe`) are ignored by git.

## Navigation

- [Repository root](../README.md)
- [Lecture 1 — Hash Tables](theory/Lectures/Lecture1/README.md)
- [Reference material](theory/Reference/README.md)
- [C++ demo source](cpp/src/DuckHashtableDemo.cpp)
