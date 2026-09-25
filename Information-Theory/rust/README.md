# Rust Labs (Information Theory)

Small, byte-oriented implementations organized by topic. The project uses Rust
edition 2024 (Rust 1.85 or newer) and has no external dependencies. Mirrors the
structure of the [`cpp/`](../cpp/) and [`js/`](../js/) implementations in this
course.

- Course guide: [Information Theory](../README.md)
- Sibling implementations: [C++](../cpp/) · [C#](../c%23/README.md) · [JavaScript](../js/README.md)

## Run

From the course folder:

```sh
cargo run --manifest-path rust/Cargo.toml
```

Or from this `rust/` directory:

```sh
cargo run
```

Edit the sample `input` in [`src/main.rs`](src/main.rs) to try other text or bytes.

## File layout

```text
rust/
├── Cargo.toml
├── Cargo.lock
├── src/
│   ├── main.rs                         # Sample input and demonstration
│   └── lossless/
│       ├── mod.rs                      # Declares topic modules
│       └── dictionary/
│           ├── mod.rs                  # Declares dictionary algorithms
│           └── lz77/
│               ├── mod.rs              # Exposes the algorithm's components
│               ├── token.rs            # Back-reference and optional literal
│               ├── encoder.rs          # Bytes -> tokens
│               ├── decoder.rs          # Tokens -> bytes
│               └── benchmark.rs        # Prints token-count statistics
└── target/                             # build output (git-ignored)
```

| File | What it is |
| --- | --- |
| [`Cargo.toml`](Cargo.toml) | package manifest (`Comperesion`, edition 2024) |
| [`src/main.rs`](src/main.rs) | sample input and the demonstration |
| [`src/lossless/mod.rs`](src/lossless/mod.rs) | declares topic modules |
| [`src/lossless/dictionary/mod.rs`](src/lossless/dictionary/mod.rs) | declares dictionary algorithms |
| [`src/lossless/dictionary/lz77/mod.rs`](src/lossless/dictionary/lz77/mod.rs) | exposes the algorithm's components |
| [`src/lossless/dictionary/lz77/token.rs`](src/lossless/dictionary/lz77/token.rs) | back-reference and optional literal |
| [`src/lossless/dictionary/lz77/encoder.rs`](src/lossless/dictionary/lz77/encoder.rs) | bytes → tokens |
| [`src/lossless/dictionary/lz77/decoder.rs`](src/lossless/dictionary/lz77/decoder.rs) | tokens → bytes |
| [`src/lossless/dictionary/lz77/benchmark.rs`](src/lossless/dictionary/lz77/benchmark.rs) | prints token-count statistics |

Start with `main.rs`, then read `token.rs`, `encoder.rs`, and `decoder.rs`.
Each `mod.rs` connects its folder's files to Rust's module tree. `pub use` in
`lz77/mod.rs` lets the demo import the components directly from `lz77`.

LZ77 searches the previous 4,096 bytes for matches up to 258 bytes long and
supports overlapping matches. Tokens stay in memory. The printed ratio compares
input bytes to token count, not an actual compressed file size.

## Adding another algorithm

1. Create a sibling folder, for example
   [`src/lossless/dictionary/lz78/`](src/lossless/dictionary/lz77/).
2. Add its `mod.rs` and implementation files. Split into token, encoder, and
   decoder files when useful, following LZ77's layout.
3. Add `pub mod lz78;` to [`src/lossless/dictionary/mod.rs`](src/lossless/dictionary/mod.rs).
4. Import and call the new algorithm from [`src/main.rs`](src/main.rs) to try it.

For a different topic, create another folder under
[`src/lossless/`](src/lossless/) and declare it in
[`src/lossless/mod.rs`](src/lossless/mod.rs) the same way. Each algorithm keeps
its own types and functions.

## Navigation

- [Information Theory](../README.md) — course guide
- [Lecture 1 — Introduction to LZ77](../theory/Lectures/Lecture1/README.md) — the theory behind this code
- [JavaScript LZ77](../js/README.md) — the same algorithm with unit tests
