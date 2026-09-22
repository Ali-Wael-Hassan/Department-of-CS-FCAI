# CS-Department-Guide

Study guides and resources for the **Computer Science (CS) department** at the
**Faculty of Computers and Artificial Intelligence (FCAI)**, **Cairo University**.

This repository is a collection of course guides. Each course lives in its own
folder and contains its own `README` describing:

- what the course is about
- what to expect (topics, material, grading signals, common gotchas)
- how to study it (lectures, references, practice)
- any code/labs and how to build and run them

## Courses

| Folder | Course | What to expect |
| --- | --- | --- |
| `Information-Theory/` | Information Theory | entropy, source coding, dictionary methods (LZ77), lossless vs. lossy compression, lecture notes + reference book, C#, C++, JavaScript and Rust implementations/demos |
| `Advanced-Datastructures/` | Advanced Data Structures | hashing and hash tables (collisions, probing, growth), lecture notes + reference book, C++ implementations/demos |

## Layout

```
CS-Department-Guide/
├── README.md              ← this file
└── <Course>/              ← one folder per course
    ├── README.md           ← what to expect in that course
    ├── theory/             ← lectures and reference material
    └── ...                 ← code, labs, assignments
```

## How to study

1. Read the course `README` first to get the big picture and know what to expect.
2. Go through the `theory/` material of that course.
3. Practice with the C#, C++, JavaScript or Rust demos (commands below).

## Building and running the C# labs

C# code lives in each course's `c#/` folder and builds with the .NET SDK:

```sh
dotnet run --project <Course>/c#
```

`dotnet` compiles the code into `c#/bin` and `c#/obj`, which are ignored by git.
See the course `README` for demo details.

## Building the C++ labs

C++ code lives in each course's `cpp/` folder and builds with CMake:

```sh
cmake -S <Course>/cpp -B <Course>/cpp/build
cmake --build <Course>/cpp/build
```

Binaries land in `<Course>/cpp/bin` (possibly in a configuration subfolder).
Build artifacts are ignored by git. See the course `README` for demo details.

## Running the Rust labs

Rust code lives in each course's `rust/` folder. Install Rust 1.85 or newer, then run:

```sh
cargo run --manifest-path <Course>/rust/Cargo.toml
```

Cargo compiles the code into `rust/target/`, which is ignored by git.
See the course `README` for demo details.

## Running the JavaScript labs

JS code lives in each course's `js/` folder and uses only Node.js built-ins (no
third-party dependencies). Install Node 18 or newer, then run from the course folder:

```sh
npm start                  # runs the demo
npm start -- "my string"   # run the demo on a specific string
npm test                   # runs the unit tests in test/
```

See the course `README` (and `js/README.md`) for demo details.