# Frog's Path

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 second  
**Memory limit:** No limit

A dynamic programming problem with backward path reconstruction.

## Problem

A frog starts on the first lily in a row and wants to reach the last one. It can only jump forward over one or two lilies: from lily `i` to `i + 2` or `i + 3` (1-indexed: from lily 1 to lily 3 or 4).

Lily `i` contains `a_i` mosquitoes, and the frog eats all of them when it lands on that lily.

Find the maximum number of mosquitoes the frog can eat and the lilies it visits in increasing order. If the last lily is unreachable, output `-1`.

### Input

- `n` — the number of lilies (`1 ≤ n ≤ 100 000`)
- `n` integers `a_i` — the number of mosquitoes on each lily (`0 ≤ a_i ≤ 1000`)

### Output

If the last lily is reachable, output the maximum number of mosquitoes eaten and the numbers of the visited lilies.

If the last lily is unreachable, output `-1`.

## Examples

| **Input** | **Output** |
| :--- | :--- |
| 6<br>1 100 3 4 1000 0 | 5<br>1 4 6 |
| 2<br>8 9 | -1 |
---

## Solution

The problem is solved using **dynamic programming** with backward path reconstruction.

`dp[i]` stores the maximum number of mosquitoes the frog can eat when standing on lily `i` (0-indexed):

dp[i] = max(dp[i - 2], dp[i - 3]) + a[i]

### Implementation

- [**C++   implementation**](https://github.com/maria11-lab/bsu_repo/tree/main/semester_3/algorithms/frog/frog.cpp)
- [**Python   implementation**](https://github.com/maria11-lab/bsu_repo/tree/main/semester_3/algorithms/frog/frog.py)
