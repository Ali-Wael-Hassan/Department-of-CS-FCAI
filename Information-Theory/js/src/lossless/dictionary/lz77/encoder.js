/**
 * Encoder — turns a string into an array of Token objects (greedy LZ77).
 *
 * Walks left to right. At each position it:
 *   1. looks back through the "search buffer" for the longest match against the
 *      text ahead (the "lookahead buffer");
 *   2. emits ONE token:
 *        - a match   -> { distance, length, character } where character is the
 *                       byte just after the match;
 *        - no match  -> a literal-only token { 0, 0, input[position] }.
 */

import { Token } from "./token.js";

export class Encoder {
  encode(input) {
    // output is a JS array that grows as we push tokens to it.
    const output = [];
    let position = 0;

    // Tuning knobs: how far back we look, and how long a match we allow.
    const searchBufferSize = 1024; // max back-distance, in characters
    const lookaheadBufferSize = 32; // max match length, in characters
    const inputLength = input.length;

    while (position < inputLength) {
      // Default to "no match found": emit the current literal.
      const token = new Token(0, 0, input[position]);

      // We cannot look back further than we already have, nor match further
      // ahead than what remains in the input / than the lookahead cap allows.
      const maxSearchLength = Math.min(searchBufferSize, position);
      const maxLookaheadLength = Math.min(
        lookaheadBufferSize,
        inputLength - position,
      );

      // Try every possible distance, nearest first; ties prefer the closest match
      // (smallest distance), so a run like "BBBBB..." matches at distance 1, not 2.
      for (let distance = 1; distance <= maxSearchLength; distance++) {
        let length = 0;

        // Repetitive-data handling: count how many characters agree when
        // comparing the text starting at 'position' with the text 'distance'
        // characters earlier.
        //
        // The trick is the comparison index `position + length - distance`.
        // While `length < distance` it reads previously seen input. But once
        // `length` grows PAST `distance`, that index re-reads characters that
        // are part of this very match's output — the repetition "feeds itself".
        // That is how a short tile like "ab" encodes the run "ababababa" as ONE
        // long match instead of many short ones.
        while (
          length < maxLookaheadLength &&
          input[position + length] == input[position + length - distance]
        ) {
          length++;
        }

        // Keep the longest match found so far (and the distance it used).
        // Scanning near→far means equal-length matches keep the closest distance.
        if (length > token.length) {
          token.distance = distance;
          token.length = length;
          // The literal right after the best match (undefined at end of input).
          token.character = input[position + length];
        }
      }

      // Consume the match plus its trailing literal. When the match reaches
      // the end of the input this moves past the end and stops the loop.
      position += token.length + 1;
      output.push(token);
    }

    return output;
  }
}
