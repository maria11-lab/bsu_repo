# row_mode_sub

A Java console application for processing matrices by subtracting the mode (the most frequently occurring value) from each row.

## Task

Develop a console application. Use the `Arrays` class where possible. If no solution is available, display a message explaining the reason.

**Variant 6.** Read `n` — the size of the `a[n][n]` matrix. Generate matrix elements as random integers in the range `[-n, n]`. Create a new matrix by subtracting the mode of each row from every element in that row. Print both the original matrix and the result.

## Example

Input:

```text
Enter n (matrix size): 4
````

Output (random values are different on each run):

```text
Original matrix:
[2, -1, 2, 0]
[-3, -3, 1, -3]
[0, 4, 0, -2]
[1, 1, -2, 1]

Result (row mode subtracted):
[0, -3, 0, -2]
[0, 0, 4, 0]
[0, 4, 0, -2]
[0, 0, -3, 0]
```

In the first row, the mode is `2` (appears twice). In the second row, it is `-3`; in the third row, `0`; and in the fourth row, `1`.

## How it works

1. The `n x n` matrix is filled with random integers in the range `[-n, n]` using `Random`.
2. The mode of each row is found by sorting a copy of the row with `Arrays.sort`. The program then iterates through the sorted array, counts the length of each sequence of equal values, and stores the value with the highest frequency. If multiple values occur equally often, the smallest one is selected.
3. A new matrix is created by subtracting the mode of each row from every element in that row.
4. The original and resulting matrices are printed row by row using `Arrays.toString`.

If the entered `n` is not positive, the program displays a message indicating that no solution is available instead of creating the matrix.
