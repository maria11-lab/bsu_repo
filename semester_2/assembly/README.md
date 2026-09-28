# Assembly Practical Works

A collection of university practical works on x86 assembly (MASM and inline `_asm`), combined with C++. All projects target 32-bit (x86 / Win32) in Visual Studio.

## Featured works

### [swap_row_col](https://github.com/maria11-lab/bsu_repo/tree/main/semester_2/assembly/swap_row_col)
Fills square matrices with random numbers, picks a random index `k` and swaps row `k` with column `k` using MASM routines. The same algorithm is implemented for three calling conventions: `__stdcall`, `__cdecl` and `__fastcall`.

### [remove_min_fun](https://github.com/maria11-lab/bsu_repo/tree/main/semester_2/assembly/remove_min_fun)
Removes all occurrences of the minimum element from an array using a separate MASM module, with the same three calling conventions.

## Other works

| Project | Description |
|---|---|
| [prime_factors](https://github.com/maria11-lab/bsu_repo/tree/main/semester_2/assembly/prime_factors) | Prime factorization of a number (inline assembly) |
| [remove_min](https://github.com/maria11-lab/bsu_repo/tree/main/semester_2/assembly/remove_min) | Removes the minimum element from an array (inline assembly) |

## Build

Requires Visual Studio (MSVC) targeting **x86 / Win32**. Inline `_asm` does not work on x64. For projects with a separate `.asm` file, enable **MASM** in *Project > Build Customizations*.

## Technologies

- C++
- x86 Assembly
- Inline Assembly
- Calling conventions
