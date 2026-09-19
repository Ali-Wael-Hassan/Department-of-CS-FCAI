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
| `Information-Theory/` | Information Theory | entropy, source coding, dictionary methods (LZ77), lossless vs. lossy compression, lecture notes + reference book, a C++ encoder/demo |

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
3. Practice with the code/demos; every C++ lab builds the same way (see below).

## Building the C++ labs

Every course folder with code uses CMake and keeps its build artifacts inside
itself (ignored by git):

```sh
cmake -S <Course>/ -B <Course>/build
cmake --build <Course>/build
```

Binaries land in `<Course>/bin`. See the course `README` for how to run each demo.