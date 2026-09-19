# Rust compression examples

Small, byte-oriented implementations organized by topic. The project uses Rust
edition 2024 (Rust 1.85 or newer) and has no external dependencies.

## Run

From this `rust/` directory:

```sh
cargo run
```

Edit the sample `input` in `src/main.rs` to try other text or bytes.

## File layout

```text
src/
├── main.rs                         # Sample input and demonstration
└── lossless/
    ├── mod.rs                      # Declares topic modules
    └── dictionary/
        ├── mod.rs                  # Declares dictionary algorithms
        └── lz77/
            ├── mod.rs              # Exposes the algorithm's components
            ├── token.rs            # Back-reference and optional literal
            ├── encoder.rs          # Bytes -> tokens
            ├── decoder.rs          # Tokens -> bytes
            └── benchmark.rs        # Prints token-count statistics
```

Start with `main.rs`, then read `token.rs`, `encoder.rs`, and `decoder.rs`.
Each `mod.rs` connects its folder's files to Rust's module tree. `pub use` in
`lz77/mod.rs` lets the demo import the components directly from `lz77`.

LZ77 searches the previous 4,096 bytes for matches up to 258 bytes long and
supports overlapping matches. Tokens stay in memory. The printed ratio compares
input bytes to token count, not an actual compressed file size.

## Adding another algorithm

1. Create a sibling folder, for example `src/lossless/dictionary/lz78/`.
2. Add its `mod.rs` and implementation files. Split into token, encoder, and
   decoder files when useful, following LZ77's layout.
3. Add `pub mod lz78;` to `src/lossless/dictionary/mod.rs`.
4. Import and call the new algorithm from `src/main.rs` to try it.

For a different topic, create another folder under `lossless/` and declare it in
`lossless/mod.rs` the same way. Each algorithm keeps its own types and functions.
