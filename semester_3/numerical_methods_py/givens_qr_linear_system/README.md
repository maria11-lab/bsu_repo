# Square Root Method

A Python implementation for solving systems of linear equations using the
square root method with the decomposition

The program works with symmetric matrices and provides intermediate calculation
steps and the final solution.

## Features

- Matrix symmetry check
- Decomposition of `A` into `SᵀDS`
- Forward substitution to solve `Sᵀy = f`
- Backward substitution to solve `DSx = y`
- Calculation of the determinant
- Step-by-step output of intermediate results
- Formatted matrix and vector output

## Technologies

- Python
- NumPy
- Numerical Methods
- Linear Algebra