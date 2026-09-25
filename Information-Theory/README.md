# Information Theory — Course Guide

Part of the CS department (FCAI, Cairo University) study guides at the
[repository root](../README.md).

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
  - [`theory/Lectures/`](theory/Lectures/Lecture1/README.md) — lecture notes
    (currently [Lecture 1 — Introduction to LZ77](theory/Lectures/Lecture1/README.md))
  - [`theory/Reference/`](theory/Reference/README.md) — the reference book used
    for the course
- **Code** — the same algorithm in four languages, each with its own guide

| Language | Guide | Build |
| --- | --- | --- |
| C++ | [`cpp/`](cpp/) ([CMakeLists.txt](cpp/CMakeLists.txt)) | CMake, C++17 |
| C# | [`c#/`](c%23/README.md) ([c#.csproj](c%23/c%23.csproj)) | .NET SDK (targets `net10.0`) |
| JavaScript | [`js/`](js/README.md) ([package.json](js/package.json)) | Node 18+, no dependencies |
| Rust | [`rust/`](rust/README.md) ([Cargo.toml](rust/Cargo.toml)) | Cargo, edition 2024 |

## How to study

1. Read the lecture notes in `theory/Lectures/` in order, starting with
   [Lecture 1 — Introduction to LZ77](theory/Lectures/Lecture1/README.md).
2. Cross-check with the reference in [`theory/Reference/`](theory/Reference/README.md).
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

### C++ files

| File | What it is |
| --- | --- |
| [`cpp/include/lossless/dictionary/LZ77.h`](cpp/include/lossless/dictionary/LZ77.h) | the LZ77 encoder / decoder interface |
| [`cpp/include/lossless/dictionary/LZTuple.h`](cpp/include/lossless/dictionary/LZTuple.h) | the `(distance, length, next)` triplet |
| [`cpp/src/lossless/dictionary/LZ77.cpp`](cpp/src/lossless/dictionary/LZ77.cpp) | the LZ77 implementation |
| [`cpp/src/LZ77Demo.cpp`](cpp/src/LZ77Demo.cpp) | the interactive demo |
| [`cpp/CMakeLists.txt`](cpp/CMakeLists.txt) | build configuration (binary name `lz77_demo`) |

## Running the JavaScript demo

Install Node 18 or newer (only Node built-ins are used), then run from
`Information-Theory/js`:

```sh
npm start                   # runs the demo on a default sample string
npm start -- "my string"    # runs the demo on a string you supply
npm test                    # runs the unit tests in test/
```

The demo encodes the input into LZ77 tokens, decodes them back, and prints the
token list plus a size benchmark. The [JS guide](js/README.md) explains the
files and how to add an algorithm.

## Running the Rust demo

Install Rust with support for edition 2024 (Rust 1.85 or newer), then run from
`Information-Theory/`:

```sh
cargo run --manifest-path rust/Cargo.toml
```

The demo encodes sample bytes, decodes them, and prints the tokens and token-count
statistics. The [Rust guide](rust/README.md) explains the files and how to add an algorithm.

## Building and running the C# demo

Install the .NET SDK (the project targets `.NET 10`), then run from
`Information-Theory/`:

```sh
dotnet run --project c#
```

The interactive `CodecCLI` is populated by auto-discovering every `IDictCodec` in
the assembly (currently `LZ77`) and offers these commands:

1. **list** — show the available codecs.
2. **compress** — pick a codec, an input file, an output path, and the max search /
   lookahead sizes; it packs the produced LZ77 tuples into a bit-packed `.lz` file.
3. **decompress** — pick a codec and read a compressed file back into the original bytes.
4. **quit** — exit.

The [C# guide](c%23/README.md) lists the source files and the same commands.

## Layout

```text
Information-Theory/
├── README.md                                    ← this file
├── theory/
│   ├── Lectures/Lecture1/README.md              ← [Lecture 1 — Introduction to LZ77](theory/Lectures/Lecture1/README.md)
│   │   └── LZ77-from-book.pdf                   ← the book chapter for this lecture
│   └── Reference/README.md                      ← [theory/Reference/](theory/Reference/README.md)
│       └── Introduction-to-data-compression.pdf ← the course reference book
├── c#/                                         ← [C# guide](c%23/README.md)
├── cpp/                                        ← C++ LZ77 (CMake → cpp/bin/lz77_demo)
├── js/                                         ← [JavaScript guide](js/README.md)
└── rust/                                       ← [Rust guide](rust/README.md)
```

Build outputs (`bin/`, `build/`, `obj/`, `target/`, `*.exe`) are ignored by git.

## Navigation

- [Repository root](../README.md)
- [Lecture 1 — Introduction to LZ77](theory/Lectures/Lecture1/README.md)
- [Reference book](theory/Reference/README.md)
- [C++ demo](cpp/) · [C# guide](c%23/README.md) · [JS guide](js/README.md) · [Rust guide](rust/README.md)
