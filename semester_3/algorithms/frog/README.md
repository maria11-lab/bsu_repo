# Frog's Path

Simple DP with backward path reconstruction.

## Problem

A frog starts on the first lily in a row and wants to reach the last one. It can only jump forward over one or two lilies: from lily `i` to `i + 2` or `i + 3` (1-indexed: from lily 1 to lily 3 or 4). Lily `i` has `a_i` mosquitoes, and the frog eats all of them when it lands there.

Find the maximum number of mosquitoes the frog can eat and the lilies it visits (in increasing order, any optimal route). If the last lily is unreachable, print `-1`.

**Input:** `n` (1 ≤ n ≤ 100 000), then `n` integers `a_i` (0 ≤ a_i ≤ 1000).

**Output:** the maximum count, then the visited lily numbers. Or `-1`.

| Input | Output |
|-------|--------|
| `6`<br>`1 100 3 4 1000 0` | `5`<br>`1 4 6` |
| `2`<br>`8 9` | `-1` |

## Idea

`dp[i]` is the maximum mosquitoes eaten when standing on lily `i` (0-indexed):

```
dp[i] = max(dp[i - 2], dp[i - 3]) + a[i]
```

- `dp[0] = a[0]`
- `dp[1] = -1` (unreachable, the frog can't jump to the adjacent lily)
- `dp[2] = a[0] + a[2]`

`ind[i]` stores where the frog jumped from to reach `i`. The path is restored **backwards** from the last lily using `ind`, then reversed.

Edge cases: `n = 1` prints `a[0]` and `1`; `n = 2` prints `-1`.
