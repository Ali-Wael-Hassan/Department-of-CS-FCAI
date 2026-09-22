/**
 * index.js — a "barrel" file.
 *
 * Passes everything from the dictionary/ folder up one level so the whole
 * library is reachable from a single import at src/index.js.
 */
export * from "./dictionary/index.js";
