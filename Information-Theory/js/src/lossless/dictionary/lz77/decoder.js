/**
 * Decoder — replays an array of Token objects then Joins the characters to rebuild the original text.
 *
 * For each token:
 *   - distance 0   -> literal-only: append the token's character.
 *   - distance > 0 -> copy 'length' bytes starting 'distance' bytes back,
 *                     reading one byte at a time so overlapping matches
 *                     (when length > distance) decode correctly.
 */
export class Decoder {
  decode(tokens) {
    // Our output "array" — push() always appends at the current end.
    const decompressed = [];

    tokens.forEach((token) => {
      if (token.distance === 0) {
        // Literal-only token: emit just its carried character (if any).
        if (token.character) decompressed.push(token.character);
      } else {
        // Where in the already-decoded output the match starts.
        const start = decompressed.length - token.distance;
        const end = start + token.length;

        // Copy byte by byte (not a slice) so a tile like "ab" can decode the
        // run "ababab": newly appended bytes become usable sources mid-loop.
        for (let i = start; i < end; i++) {
          decompressed.push(decompressed[i]);
        }

        // The literal byte that followed the match, if there was one.
        if (token.character) decompressed.push(token.character);
      }
    });

    // Join the array of single characters into one string.
    return decompressed.join("");
  }
}
