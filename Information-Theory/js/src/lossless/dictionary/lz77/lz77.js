/**
 * lz77.js — convenience wrapper.
 *
 * Gives callers two high-level functions so they never have to touch the
 * Encoder/Decoder classes or Token objects directly:
 *
 *     compress("...")      -> Token[]
 *     decompress(tokens)   -> string (the original text back)
 */
import { Encoder } from "./encoder.js";
import { Decoder } from "./decoder.js";

// Sharing one instance is fine: both classes are stateless.
const encoder = new Encoder();
const decoder = new Decoder();

/** Compress a string into an array of Token objects. */
export function compress(input) {
  return encoder.encode(input);
}

/** Decompress an array of Token objects back into the original string. */
export function decompress(tokens) {
  // decode() already joins the characters into a string for us.
  return decoder.decode(tokens);
}
