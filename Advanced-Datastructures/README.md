# Advanced Datastructures — Course Guide

Part of the CS department (FCAI, Cairo University) study guides at the
repository root (`CS-Department-Guide`).

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
  - `theory/Lectures/` — lecture notes (e.g. `Lecture1/`)
  - `theory/Reference/` — the reference book used for the course
- **Code**
  - `cpp/include/` — C++ headers (the `duck` hash-table implementation)
  - `cpp/src/` — C++ implementations + a demo
  - `cpp/CMakeLists.txt` — C++ build configuration

## How to study

1. Read the lecture notes in `theory/Lectures/` in order.
2. Cross-check with the reference in `theory/Reference/`.
3. Implement and experiment with the code demos (see below).

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