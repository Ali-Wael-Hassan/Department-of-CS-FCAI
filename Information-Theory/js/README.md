# JavaScript Labs (Information Theory)

JS implementation of the dictionary (LZ77) compression labs for the
Information Theory course. Mirrors the structure of the [`cpp/`](../cpp/) and
[`rust/`](../rust/) implementations in this course.

- Course guide: [Information Theory](../README.md)
- Sibling implementations: [C++](../cpp/) · [C#](../c%23/README.md) · [Rust](../rust/README.md)

## Layout

```text
js/
├── package.json
├── src/
│   ├── index.js                ← library entry point
│   ├── lz77.demo.js            ← runnable demo / CLI
│   └── lossless/
│       ├── index.js            ← lossless entry point
│       └── dictionary/
│           ├── index.js        ← dictionary module entry point
│           └── lz77/
│               ├── lz77.js     ← high-level compress / decompress wrapper
│               ├── token.js    ← LZ77 tuple / token type
│               ├── encoder.js  ← LZ77 encoder
│               ├── decoder.js  ← LZ77 decoder
│               └── benchmark.js ← size-statistics printer
└── test/
    └── lz77.test.js            ← unit tests
```

## Files

| File | What it is |
| --- | --- |
| [`package.json`](package.json) | ESM package, `start` → the demo, `test` → `node --test` |
| [`src/index.js`](src/index.js) | library entry point |
| [`src/lz77.demo.js`](src/lz77.demo.js) | runnable demo / CLI |
| [`src/lossless/index.js`](src/lossless/index.js) | lossless entry point |
| [`src/lossless/dictionary/index.js`](src/lossless/dictionary/index.js) | dictionary module entry point |
| [`src/lossless/dictionary/lz77/lz77.js`](src/lossless/dictionary/lz77/lz77.js) | high-level compress / decompress wrapper |
| [`src/lossless/dictionary/lz77/token.js`](src/lossless/dictionary/lz77/token.js) | LZ77 tuple / token type |
| [`src/lossless/dictionary/lz77/encoder.js`](src/lossless/dictionary/lz77/encoder.js) | LZ77 encoder |
| [`src/lossless/dictionary/lz77/decoder.js`](src/lossless/dictionary/lz77/decoder.js) | LZ77 decoder |
| [`src/lossless/dictionary/lz77/benchmark.js`](src/lossless/dictionary/lz77/benchmark.js) | size-statistics printer |
| [`test/lz77.test.js`](test/lz77.test.js) | unit tests |

## Running

No dependencies are required — this is pure JavaScript using only Node's
built-in modules (ESM and the `node:test` runner).

```sh
node --version             # needs Node 18+ for the test runner
npm start                  # runs src/lz77.demo.js
npm start -- "my string"   # run the demo on a specific string
npm test                   # runs the unit tests in test/
```

The demo encodes the input into LZ77 tokens, decodes them back, and prints the
token list plus a size benchmark.

## Adding another algorithm

1. Create a sibling folder, for example `src/lossless/dictionary/lz78/`.
2. Add its `index.js` and implementation files. Split into token, encoder, and
   decoder files when useful, following LZ77's layout.
3. Re-export it from [`src/lossless/dictionary/index.js`](src/lossless/dictionary/index.js).
4. Import and call it from [`src/lz77.demo.js`](src/lz77.demo.js) to try it, and
   add a matching test file under [`test/`](test/).

For a different topic, create another folder under
[`src/lossless/`](src/lossless/) and re-export it from
[`src/lossless/index.js`](src/lossless/index.js). Each algorithm keeps its own
types and functions.

## Navigation

- [Information Theory](../README.md) — course guide
- [Lecture 1 — Introduction to LZ77](../theory/Lectures/Lecture1/README.md) — the theory behind this code
- [C++ LZ77](../cpp/) — the same algorithm with file I/O
