# Lecture 1 — Hash Tables

- Course guide: [Advanced Datastructures](../../../README.md)
- Next stop in the code: [C++ hash table](../../../cpp/) and its
  [demo](../../../cpp/src/DuckHashtableDemo.cpp)

## What this lecture covers

- Hash functions and how they map keys to slots
- Collisions and resolution strategies (probing, open addressing)
- Load factor and when a table must grow (re-hash)
- Deletion and keeping the probe sequence consistent

> Placeholder: the lecture slides and notes for this session are not added yet.
> Add your `.pdf`/`.md` material here and list it in the table below.

## Lecture material (local)

| File | What it is |
| --- | --- |
| *(add slides here)* | The lecture slides for this session |

## References

A guided path — get the big picture first, then the hash-function details.

### 1. Watch first — the big picture (video)

[**Hash Table — YouTube**](https://www.youtube.com/watch?v=2Ti5yvumFTU)

Get the intuition before the code: what a hash table is, why lookups are
expected O(1), and how collisions get resolved.

### 2. Then read — the concept

[**Hash Table — GeeksforGeeks DSA**](https://www.geeksforgeeks.org/dsa/hash-table-data-structure/)

An authoritative overview: hash functions, collision handling (chaining,
open addressing, probing), load factor, and re-hashing.

[**Understanding Hash Tables — dev.to (Codesphere)**](https://dev.to/codesphere/understanding-hash-tables-and-why-they-are-important-1819)

A hands-on, beginner-friendly explanation of how hash tables work and why they
matter.

### 3. Then go deep — hash functions

[**String Hashing using Polynomial Rolling Hash — GeeksforGeeks DSA**](https://www.geeksforgeeks.org/dsa/string-hashing-using-polynomial-rolling-hash-function/)

The polynomial rolling hash used by the `duck_hash<std::string>` specialization
in [`DuckHash.h`](../../../cpp/include/DuckHash.h) in this repo's demo.

[**xxHash — Stephan Brumme**](https://create.stephan-brumme.com/xxhash/)

A fast, non-cryptographic hash family and how it is implemented.

[**xxHash Algorithm Implementation — DeepWiki (Ceph)**](https://deepwiki.com/ceph/xxHash/2.2-xxhash-algorithm-implementation)

A walk-through of the xxHash algorithm as used in a real project (Ceph).

## Suggested study flow

1. Watch the video (reference 1) to see what hash tables do.
2. Skim the slides once you add them above.
3. Read the GeeksforGeeks reference (2) for the definitions.
4. Read the rolling-hash and xxHash pages for the hash-function details.
5. Trace the `duck::DuckHashtable` demo by hand on a small table:
   - insert a few keys, observe the load factor and probing
   - trigger growth past the 80% load threshold
   - remove an element and watch the displaced re-insertions
6. Then run the demo. From the repository root:

```sh
cmake -S Advanced-Datastructures/cpp -B Advanced-Datastructures/cpp/build
cmake --build Advanced-Datastructures/cpp/build
Advanced-Datastructures/cpp/bin/advanced_datastructures_demo
```

The class lives in [`DuckHashtable.h`](../../../cpp/include/DuckHashtable.h) with
its implementation in [`Hashtable.tpp`](../../../cpp/src/Hashtable.tpp), and the
hash functions in [`DuckHash.h`](../../../cpp/include/DuckHash.h).

## Navigation

- [Advanced Datastructures](../../../README.md) — course guide
- [Reference material](../../Reference/README.md)
- Other lectures: [`theory/Lectures/`](../)
