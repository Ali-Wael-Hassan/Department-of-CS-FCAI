# Lecture 1 — Introduction to LZ77

## What this lecture covers

- What lossless dictionary/list compression is
- The sliding-window idea behind LZ77
- The `(distance, length, next)` triplet
- Motivations for LZ77: repetition, redundancy, dictionary reuse

## Lecture material (local)

| File | What it is |
| --- | --- |
| `Lect-1IntroLZ77.pdf` | The lecture slides for this session |
| `LZ77-from-book.pdf` | The relevant chapter from the course reference book |

## References

A guided path — start watching, then read the theory, then dig into the details.

### 1. Watch first — the big picture (video)

[**LZ77 — Introduction video**](https://www.youtube.com/watch?v=y2egZuJBOQM)

Get the intuition before the math: how a sliding window and a small dictionary
can replace long repeated patterns with a single short triplet.

### 2. Then read — the formal definition (Springer)

[**Dictionary Coding — Springer, Encyclopedia of Information Systems**](https://link.springer.com/rwe/10.1007/978-0-387-30162-4_108)

The authoritative reference entry:
- formal problem statement, terminology, and the exact notation
- history and place of LZ77 within the LZ family (LZ77, LZ78, LZW)
- complexity and context: where dictionary coding sits among compression methods

Use it as the document that gives the definitions you are expected to know.

### 3. Then go deep — implementation walk-through (blog)

[**Exploring the LZ77 Algorithm — Coderspirit blog**](https://blog.coderspirit.xyz/blog/2023/06/04/exploring-the-lz77-algorithm/)

A hands-on tutorial with concrete examples:
- step-by-step encoding with the `(distance, length, next)` triplets
- decoding and how the sequential copy handles overlapping matches
- trade-offs: window size, lookahead buffer, speed vs. compression ratio

## Suggested study flow

1. Watch the video (reference 1) to see what LZ77 does.
2. Skim the lecture slides for the terminology used in class.
3. Read the Springer entry (reference 2) for the precise definitions.
4. Follow the blog example (reference 3), then try the repo demo:

```sh
cmake --build Information-Theory/build
Information-Theory/bin/lz77_demo
```

Experiment with a repetitive text file (e.g. a long line of `abababab...`) and
observe how one tuple compresses a whole repeated run.