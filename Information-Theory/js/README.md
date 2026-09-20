# JavaScript Labs (Information Theory)

JS implementation of the dictionary (LZ77) compression labs for the
Information Theory course. Mirrors the structure of the `cpp/` and `rust/`
implementations in this folder.

## Layout

```
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

## Running

No dependencies are required — this is pure JavaScript using only Node's
built-in modules (ESM and the `node:test` runner).

```sh
node --version             # needs Node 18+ for the test runner
npm start                  # runs src/lz77.demo.js
npm start -- "my string"   # run the demo on a specific string
npm test                   # runs the unit tests in test/
```