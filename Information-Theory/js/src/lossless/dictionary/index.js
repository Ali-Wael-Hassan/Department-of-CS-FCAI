/**
 * index.js — a "barrel" file.
 *
 * A barrel is a real convention in the JS/TS community: a file that only
 * re-exports the modules in its folder so consumers can import from ONE
 * place instead of many long paths. There is no logic here, only re-exports.
 *
 *     import { Encoder, Decoder, Token } from ".../dictionary/index.js";
 */
export { Token } from "./lz77/token.js";
export { Encoder } from "./lz77/encoder.js";
export { Decoder } from "./lz77/decoder.js";
export { compress, decompress } from "./lz77/lz77.js";
export { printBenchmark } from "./lz77/benchmark.js";
