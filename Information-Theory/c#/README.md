# C# Labs (Information Theory)

C# implementation of the dictionary (LZ77) compression labs for the
Information Theory course. Mirrors the structure of the [`cpp/`](../cpp/),
[`js/`](../js/), and [`rust/`](../rust/) implementations in this course.

- Course guide: [Information Theory](../README.md)
- Theory: [Lecture 1 — Introduction to LZ77](../theory/Lectures/Lecture1/README.md) ·
  [reference book](../theory/Reference/README.md)

## Running

Requires the .NET SDK; the project targets `net10.0`. From the course folder:

```sh
dotnet run --project c#
```

Or from inside this `c#` folder:

```sh
dotnet run
```

The interactive `CodecCLI` auto-discovers every `IDictCodec` in the assembly
(currently `LZ77`) and accepts:

| Command | What it does |
| --- | --- |
| `list` | show the available codecs |
| `compress` | pick a codec, an input file, an output path, and the max search / lookahead sizes; writes a bit-packed `.lz` file |
| `decompress` | pick a codec and read a compressed file back into the original bytes |
| `quit` (or `q`, or an empty line) | exit |

Defaults: max search `4096`, max lookahead `64`, output `<input>.lz` for
compression and `<input>.out` for decompression.

## Layout

```text
c#/
├── c#.csproj                ← project file (net10.0, nullable, implicit usings)
├── Program.cs               ← entry point: starts the CLI
├── CodecCLI.cs              ← interactive CLI (list / compress / decompress / quit)
├── IDictCodec.cs            ← the interface every dictionary codec implements
├── LZ77.cs                  ← the LZ77 codec
├── LZTuple.cs               ← the (distance, length, next) tuple
├── bin/                     ← build output (git-ignored)
└── obj/                     ← build output (git-ignored)
```

`CodecCLI` finds codecs by reflecting over the assembly, so adding a new codec
is only a matter of writing a new `IDictCodec` implementation — no registration
step. `Save`/`Load` live on the codec, which keeps the file format next to the
algorithm that produces it.

## Adding another algorithm

1. Create a class next to [`LZ77.cs`](LZ77.cs) that implements
   [`IDictCodec`](IDictCodec.cs): `Name`, `Compress`, `Decompresss`, `Save`, `Load`.
2. Reuse [`LZTuple`](LZTuple.cs) if the triplet shape fits, or add your own type
   next to it.
3. Run the CLI and use `list` to confirm the new codec was discovered.
