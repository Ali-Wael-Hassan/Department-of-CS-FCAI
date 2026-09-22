/**
 * Token — one LZ77 output item.
 *
 * Represents the (distance, length, character) triplet from the course:
 *
 *   distance  : how many bytes back in the decoded data the match starts
 *   length    : how many bytes to copy from that back-reference
 *   character : the literal byte emitted right after the match; it is
 *               undefined when the match reaches the very end of the input
 *
 * A "literal-only" token (distance 0, length 0) just emits its character.
 */
export class Token {
  constructor(distance, length, character) {
    this.distance = distance; // distance in bytes back to the match start
    this.length = length; // number of bytes copied from the back-reference
    this.character = character; // literal byte after the match (or undefined)
  }
}
