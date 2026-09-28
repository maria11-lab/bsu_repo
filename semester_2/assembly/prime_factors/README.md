# Prime Factorization: C++ and x86 Inline Assembly

A small university project that mixes C++ with 32-bit inline assembly.
The program reads a positive integer and prints all of its prime factors
(with repetitions), e.g. `12` gives `3 2 2`.

## How it works

1. Divide out all factors of `2` while the number is even.
2. Then try odd divisors `3, 5, 7, ...`. If a divisor divides the number
   evenly, it is a prime factor and the number is divided by it again.
3. Stop when the remaining number becomes `1`.

Every found factor is pushed onto the stack inside the `_asm` block and
counted in `count`. After that they are popped back into C++ and printed,
so the factors come out in **descending order**.

Example:

```
Enter a num:  60
Result: 5 3 2 2
```