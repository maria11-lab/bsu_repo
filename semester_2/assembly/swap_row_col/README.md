# Row/Column Swap: C++ and x86 MASM

A small university project that mixes C++ with 32-bit MASM assembly.
The program fills square integer matrices with random numbers, picks a random
index `k`, and swaps **row k** with **column k** using assembly routines.

The same algorithm is implemented three times, once per calling convention,
to demonstrate how each one passes arguments and cleans up the stack.

## How it works

For a matrix `A` of size `n x n` and an index `k`, the routine swaps
`A[k][i]` with `A[i][k]` for every `i != k`. The diagonal element `A[k][k]`
stays where it is.

Example (`n = 3`, `k = 1`):

```
Before:        After:
 1  2  3        1  4  3
 4  5  6        2  5  8
 7  8  9        7  6  9
```

## What the demo does

1. **5x5 matrix** (values 10..19), swapped with the stdcall routine.
2. **3x3 matrix** (values 0..9), swapped with the fastcall routine.
3. **3x3 matrix in a heap array** (`new int[9]`, values 10..19), swapped with
   the cdecl routine.
4. Prints the matrix before and after each swap.
5. Finishes with a small inline-asm block that shows how a pointer,
   `[b]` and `[eax]` addressing behave (debug output of four numbers).


## Notes

- Random values come from `rand()`, seeded with `time(NULL)`.
- Matrices are stored row-major: element `(i, j)` is at `arr[i * n + j]`.