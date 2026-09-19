# Information Theory — Course Guide

Part of the CS department (FCAI, Cairo University) study guides at the
repository root (`CS-Department-Guide`).

## What to expect

Information Theory is about quantifying and communicating information. Expect a
mix of math (entropy, probabilities) and applied coding (compression
algorithms).

- **Core topics**
  - Entropy and source coding: entropy, Huffman coding, arithmetic coding
  - Lossless compression: the source is recovered exactly
    - dictionary methods (LZ77 / LZ78, and the LZ77 implementation here)
  - Lossy compression: rate–distortion trade-off, information allowed to be lost
  - Measures: entropy, information content, coding efficiency, redundancy
- **Theory material**
  - `theory/Lectures/` — lecture notes (e.g. `Lecture1/`)
  - `theory/Reference/` — the reference book used for the course
- **Code**
  - `include/` — headers, organized like the topics (e.g. `lossless/dictionary/`)
  - `src/` — implementations + an interactive demo

## How to study

1. Read the lecture notes in `theory/Lectures/` in order.
2. Cross-check with the reference in `theory/Reference/`.
3. Implement and experiment with the code demos (see below).

## Building and running the demo

```sh
cmake -S . -B build
cmake --build build
```

The interactive `lz77_demo` is written to `bin/` and offers two options:

1. **Compress a text file** — enter the input path, output path, and the search /
   lookahead window sizes in bits; it prints the tuple count and compression ratio.
2. **Decompress a file** — read back a `.lz77` file and write the original text to
   the output path.

Example:

```sh
bin/lz77_demo
# choose 1
# input text file  : sample.txt
# output file      : sample.lz77
# search bits (12): 12
# lookahead bits (8): 8
# choose 2 to decompress sample.lz77 back into a new file
```