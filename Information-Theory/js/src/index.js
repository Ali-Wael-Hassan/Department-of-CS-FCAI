/**
 * index.js — the top-level "barrel" (library entry point).
 *
 * One import exposes the entire API:
 *   import { Encoder, Decoder, Token, compress, decompress, printBenchmark }
 *     from "src/index.js";
 */
export * from "./lossless/index.js";
