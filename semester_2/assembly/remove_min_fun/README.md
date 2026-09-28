# Remove Minimum: C++ and x86 MASM

A small university project that mixes C++ with 32-bit MASM assembly.
The assembly routine finds the minimum element of an integer array, removes
**all** its occurrences, shifts the remaining elements to the left, and fills
the freed tail with zeros.

The same algorithm is declared once per calling convention:
`RemoveMin1` (`__stdcall`), `RemoveMin2` (`__cdecl`) and
`RemoveMin3` (`__fastcall`).

## How it works

1. Find the minimum value of the array (signed comparison).
2. Copy every element that is not equal to the minimum to the front of the
   array, keeping their original order.
3. Fill the remaining positions with `0`.

Signature (C++ side):

```cpp
int fn(int* arr, int n);
```

## What the demo does

1. Creates three arrays: `{1, -1, -1, 5}`, `{10, 2, 8, 2}`, `{3, 3, 3, 3}`.
2. Prints them before the call.
3. Calls `RemoveMin1` on each array.
4. Prints the arrays after the call.

Expected output:

```
1 -1 -1 5      ->   1 5 0 0
10 2 8 2       ->   10 8 0 0
3 3 3 3        ->   0 0 0 0
```