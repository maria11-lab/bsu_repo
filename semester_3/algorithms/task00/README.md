# Task 0.0

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 second  
**Memory limit:** No limit

Given a binary search tree whose node keys are integers in the range from −2³¹ to 2³¹ − 1 inclusive. Find the sum of the keys of all nodes in the tree.

## Input Format

The input file contains a sequence of node keys in the order in which they are inserted into the tree. Each key is given on a separate line.

All keys in a binary search tree are unique by definition. Therefore, if a key that already exists in the tree is inserted, it is ignored.

## Output Format

Output a single number — the sum of all keys in the constructed tree.

## Examples

| **input.txt** | **output.txt** |
| :--- | ---: |
| 2<br>3 | **5** |
| 5<br>2<br>4<br>1<br>8<br>7 | **27** |
| 0<br>100<br>-100 | **0** |

---

## Solution

The tree itself does not actually need to be constructed: its structure is irrelevant, since we only need the sum of its **unique** keys. Uniqueness is exactly what a `set` provides.

The idea is simple:

1. Read all numbers from the input file.
2. Insert them into a `set` (or `unordered_set`) so that duplicate keys are automatically ignored, just as they would be in the binary search tree.
3. Sum all remaining values in the set and output the result.

This means that there is no need to explicitly construct the tree — the set handles the required uniqueness for us.

### Implementation

- [**C++ implementation**](https://github.com/maria11-lab/bsu_repo/tree/main/semester_3/algorithms/task00/task00.cpp)
- [**Python implementation**](https://github.com/maria11-lab/bsu_repo/tree/main/semester_3/algorithms/task00/task00.py)
