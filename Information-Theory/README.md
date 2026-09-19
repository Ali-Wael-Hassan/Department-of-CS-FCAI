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
  - `cpp/include/` — C++ headers, organized by topic (e.g. `lossless/dictionary/`)
  - `cpp/src/` — C++ implementations + an interactive demo
  - `cpp/CMakeLists.txt` — C++ build configuration
  - `rust/` — simple Rust implementations and a sample-text demo (see [Rust guide](rust/README.md))

## How to study

1. Read the lecture notes in `theory/Lectures/` in order.
2. Cross-check with the reference in `theory/Reference/`.
3. Implement and experiment with the code demos (see below).

## Building and running the C++ demo

Run these commands from `Information-Theory/` with CMake and a C++17 compiler installed:

```sh
cmake -S cpp -B cpp/build
cmake --build cpp/build
```

The interactive `lz77_demo` is written to `cpp/bin/` (or a configuration
subfolder such as `cpp/bin/Debug/` with Visual Studio) and offers two options:

1. **Compress a text file** — enter the input path, output path, and the search /
   lookahead window sizes in bits; it prints the tuple count and compression ratio.
2. **Decompress a file** — read back a `.lz77` file and write the original text to
   the output path.

Example:

```sh
cpp/bin/lz77_demo
# choose 1
# input text file  : sample.txt
# output file      : sample.lz77
# search bits (12): 12
# lookahead bits (8): 8
# choose 2 to decompress sample.lz77 back into a new file
```

## Running the Rust demo

Install Rust with support for edition 2024 (Rust 1.85 or newer), then run from
`Information-Theory/`:

```sh
cargo run --manifest-path rust/Cargo.toml
```

The demo encodes sample bytes, decodes them, and prints the tokens and token-count
statistics. The [Rust guide](rust/README.md) explains the files and how to add an algorithm.
