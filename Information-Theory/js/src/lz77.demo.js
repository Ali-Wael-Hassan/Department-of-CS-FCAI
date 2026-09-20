/**
 * lz77.demo.js — runnable demo / command-line interface.
 *
 *   node src/lz77.demo.js                # uses the default sample string
 *   node src/lz77.demo.js "your text"    # uses a string you supply
 *
 * Prints the tokens the encoder produces, verifies the decoder round-trips
 * back to the original text, and prints an honest size benchmark.
 */
import { compress, decompress } from "./lossless/dictionary/lz77/lz77.js";
import { printBenchmark } from "./lossless/dictionary/lz77/benchmark.js";

// process.argv looks like: [node, "src/lz77.demo.js", <your string>, ...]
const input =
  process.argv[2] ??
  "the cat sat on the mat and the cat sat on the mat and the cat sat on the mat";

const tokens = compress(input);
const decoded = decompress(tokens);

console.log("Input   :", JSON.stringify(input));
console.log("Tokens  :");
for (const t of tokens) {
  console.log(
    `  { distance: ${t.distance}, length: ${t.length}, character: ${JSON.stringify(t.character)} }`,
  );
}
console.log("Decoded :", JSON.stringify(decoded));
console.log("Match   :", decoded === input ? "YES ✓" : "NO ✗");

printBenchmark(input, tokens);
