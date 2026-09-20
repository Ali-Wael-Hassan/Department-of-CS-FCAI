/**
 * benchmark.js — prints an estimate of the compressed size.
 *
 * A naive "compare token count to character count" is misleading, because each
 * Token is an OBJECT holding up to three numbers (distance, length, character):
 * one token is not one byte. Instead we add up the bits actually needed for
 * each token's fields, the same way the C++ version bit-packs tuples to disk.
 *
 * Assumption: every input character is one byte (ASCII / single-byte input).
 */

/** Smallest number of bits needed to represent `value` (0 still needs 1 bit). */
function bitsNeeded(value) {
  if (value <= 0) return 1;
  return Math.floor(Math.log2(value)) + 1;
}

export function printBenchmark(input, tokens) {
  const originalSize = input.length; // bytes, assuming 1 char = 1 byte

  // Pick one field width large enough for the biggest value actually used.
  const maxDistance = tokens.reduce((m, t) => Math.max(m, t.distance), 0);
  const maxLength = tokens.reduce((m, t) => Math.max(m, t.length), 0);
  const distanceBits = bitsNeeded(maxDistance);
  const lengthBits = bitsNeeded(maxLength);
  const characterBits = 8; // the literal 'character' field is one byte

  // Math.ceil(.../8) rounds the total number of bits up to whole bytes.
  const bitsPerToken = distanceBits + lengthBits + characterBits;
  const estimatedBytes = Math.ceil((tokens.length * bitsPerToken) / 8);

  const ratio = estimatedBytes > 0 ? originalSize / estimatedBytes : 0;
  const saved =
    originalSize > 0 ? (1 - estimatedBytes / originalSize) * 100 : 0;

  console.log("========== LZ77 Benchmark ==========");
  console.log(`Original size : ${originalSize} bytes`);
  console.log(`Token count   : ${tokens.length}`);
  console.log(
    `Field widths  : distance ${distanceBits}b, length ${lengthBits}b, character ${characterBits}b`,
  );
  console.log(`Packed size   : ${estimatedBytes} bytes`);
  console.log(`Ratio         : ${ratio.toFixed(2)}:1`);
  console.log(`Saved         : ${saved.toFixed(2)}%`);
  console.log("====================================");
}
