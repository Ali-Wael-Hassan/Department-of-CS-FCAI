// Unit tests using Node's built-in test runner (no external dependencies).
// Run with:  npm test   (which runs `node --test`)
import { test } from "node:test";
import assert from "node:assert/strict";
import { Encoder, Decoder } from "../src/lossless/dictionary/index.js";

// Encoder and Decoder are stateless, so one shared instance is fine.
const encoder = new Encoder();
const decoder = new Decoder();

/** Encode then decode `input`; returns whatever the decoder produced. */
function roundTrip(input) {
  return decoder.decode(encoder.encode(input)); // decode() returns a string
}

test("round trip reproduces the original string", () => {
  const samples = [
    "",
    "a",
    "abc",
    "abababababab",
    "the cat sat on the mat",
    "this is random charachters",
  ];
  for (const s of samples) {
    assert.equal(roundTrip(s), s, `round trip failed for: ${JSON.stringify(s)}`);
  }
});

test("a literal-only token has distance 0 and length 0", () => {
  // "z" has no earlier occurrence, so it becomes a literal-only token.
  const tokens = encoder.encode("z");
  assert.ok(tokens.length >= 1);
  for (const t of tokens) {
    assert.equal(t.distance, 0);
    assert.equal(t.length, 0);
  }
  assert.equal(decoder.decode(tokens), "z");
});

test("repeated input actually compresses", () => {
  const input = "a".repeat(1000);
  const tokens = encoder.encode(input);
  assert.ok(tokens.length < input.length); // fewer tokens than characters
  assert.equal(roundTrip(input), input); // and it still round-trips
});
