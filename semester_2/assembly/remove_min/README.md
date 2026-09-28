# Remove Minimum: C++ and x86 Inline Assembly

A small university project that mixes C++ with 32-bit inline assembly.
The program finds the minimum element of an integer array, removes **all**
its occurrences, shifts the remaining elements to the left, and fills the
freed tail with zeros.

## How it works

1. Scan the array and find the minimum value (signed comparison).
2. Copy every element that is not equal to the minimum to the front of the
   array, keeping their original order.
3. Fill the remaining positions with `0`.
4. Return the minimum to C++ through the variable `d`.

Example:

```
old arr: 3 1 4 1 5
min: 1
new arr: 3 4 5 0 0
```