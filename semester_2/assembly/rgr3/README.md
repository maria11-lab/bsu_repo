# Lab 3 — Variant 6

## Task

Develop three x86 Assembly functions for finding and removing the minimum
element from an integer array.

Each function uses a different calling convention:
- `RemoveMin1` — `__stdcall`
- `RemoveMin2` — `__cdecl`
- `RemoveMin3` — `__fastcall`

## Description

The program:
- works with an array of integers;
- finds the minimum element;
- removes or modifies the minimum element in the array;
- implements the same operation using three different x86 Assembly functions;
- demonstrates the differences between `__stdcall`, `__cdecl`, and `__fastcall` calling conventions.

The Assembly functions are integrated into a C/C++ application.

## Technologies

- C++
- x86 Assembly
- `__stdcall`
- `__cdecl`
- `__fastcall`
