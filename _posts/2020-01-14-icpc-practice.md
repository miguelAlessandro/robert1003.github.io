---
layout: post
title: The 2019 University of Jordan Collegiate Programming Contest
tags: icpc gym

---

This round is kinda too easy for expericened competitive programmers. I do it just for boosting my confidence (though I didn't solve all problems during virtual...). Also, I should see the scoreboard more often, as serveral trivial problems aren't discovered by me after the first hour.


## pA <span style="font-size:medium;">[00:02], 1 try</span>

Just print `1` when $x \ge y$, `0` otherwise.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-14-icpc-practice/A.cpp %}
```

</details>

## pB <span style="font-size:medium;">[00:05], 1 try</span>

Do [Sieve of Eratosthenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes) to get all prime numbers between $1\sim 10000000$, then enumerate all possible combination for the given $n$. The complexity is $O(10000000)$.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-14-icpc-practice/B.cpp %}
```

</details>

## pC <span style="font-size:medium;">[00:09], 1 try</span>

Just calculate it directly, the complexity will be $O(\log n)$ as $X \ge 2$.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-14-icpc-practice/C.cpp %}
```

</details>

## pD <span style="font-size:medium;">[00:28], 1 try</span>

This can be solve directly by BFS (or DFS), the complexity will be $O(Lrc)$. However, we can also solve it by executing `LD` for several times until it reach the left-bottom of the grid, then execute `RRUU`. The complexity will be much lower.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-14-icpc-practice/D.cpp %}
```

</details>

## pE <span style="font-size:medium;">[03:50], 7 tries</span>

As the memory limit is unusually small, we can't do BFS like the previous problem. The solution is similar to the second solution of the previous problem. First, observe that if the four blocks is at $(9,1),(10,1),(11,1),(12,1)$, we can just execute `RRRRRRRRDDUUURDDDDUUUUULLDDDDRRUUUU`. Then, observe that no matter which four blocks we have in the beginning, we can always make it into the situation described above by executing `UUUUULLLLLDDDDDDDDDDDDLLLLLL` i.e. some ups, then some lefts, then down to the bottom, and finally some lefts.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-14-icpc-practice/E.cpp %}
```

</details>

## pF <span style="font-size:medium;">[02:30], 3 tries</span>

First observe that if $A$ can see $B$, then we must kill $A$ before we kill $B$. Thus, We can build a directed graph for it and do topological sort on it. Every edge $(u, v)$ indicates that $u$ can see $v$. If the graph have rings, then there's no solution. Be careful with the calculation of visibility.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-14-icpc-practice/F.cpp %}
```

</details>

## pG <span style="font-size:medium;">[-\-:-\-], 0 try</span>



<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-14-icpc-practice/G.cpp %}
```

</details>

## pH <span style="font-size:medium;">[01:18], 1 try</span>

We can calculate the radius by [sine law](https://en.wikipedia.org/wiki/Law_of_sines):
$$
\theta = \frac{\pi - \frac{2\pi}{V}}{2}, \frac{r}{\sin \theta}=\frac{S}{\sin \frac{2\pi}{V}} \implies r=\frac{S\sin\theta}{\sin\frac{2\pi}{n}}
$$
Then the answer is $\pi r^2$.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-14-icpc-practice/H.cpp %}
```

</details>

## pI <span style="font-size:medium;">[01:37], 2 tries</span>

Just implement the parser. Note that if doing it naively, you'll get `TLE` as the complexity is $O(|length|^2)$ (consider $1(2(3(4(....))))$). Therefore, we need to construct a helping array, `nxt[]`, where `nxt[i]` indicates the pairing `)`'s position for the `(` at the $i^{th}$ position. This array can help us to reduce the complexity to $O(|length|)$.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-14-icpc-practice/I.cpp %}
```

</details>

## pJ <span style="font-size:medium;">[04:08], 3 tries</span>

First observe that if we encode each walk with $1$/$-1$, meaning walking to the next node/previous node, then the original problem is transformed into counting the number of arrays with length less then $m$ and no prefix sum is less then $0$. This can be calculate with a simple dp: 

<ul>
 <li> State: $dp[len][sum]$, where $len$ is the current length of array and $sum$ is the current sum of array.
 <li> Transition: $dp[i][j] = dp[i - 1][j + 1] + dp[i - 1][j - 1]$, assuming $j < k$ and $j > 0$.
 <li> Answer: $2n\times(dp[2][0] + dp[4][0] + \dots + dp[m][0])$ as you can only walk even steps if you want to walk back to the staring point, and you can choose $n$ starting points and $2$ directions.
</ul>


<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-14-icpc-practice/J.cpp %}
```

</details>

## pK <span style="font-size:medium;">[02:07], 2 tries</span>

Enumerate all possible subset directly. The complexity is $O(n2^n)$. Be careful that the answer will overflow `int`.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-14-icpc-practice/K.cpp %}
```

</details>

If you're curious, there exist another solution with $O(n\log C)$ where $C$ is the range of $a_i$. We can calculate the answer by considering each bit (in binary) seperately. Let $cnt_i$ be the number of $a$'s such that it contain the $i^{th}$ bit. Then this bit will contribute $2^i \times (2^n - 2^{n - cnt_i})$ to the answer ($2^{n - cnt_i}$ is the number of subsets that didn't have the $i^{th}$ bits).

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-14-icpc-practice/K2.cpp %}
```

</details>

## pL <span style="font-size:medium;">[-\-:-\-], 0 try</span>

To solve this problem, we first need several observations:

1. If we have an `a`, we can eliminate it by `a -> ab -> abc -> ""`.
2. If we have `ab`, we can eliminate it by `ab -> abc -> ""`.
    1. If there's no `a` before `b`, then it's unsolvable.
3. Now we have to deal with `c`:
    1. If we have `ac`, we can eliminate it by `ac -> abc -> ""`.
    2. If we have `abc`, we can eliminate it by `abc -> ""`.
    3. If we have `bbc`, we can elminate it by `bbc -> bcbc -> bbabc -> bb`.
    4. If we have `bc` (no `a` before it), then it's unsolvable.
    5. If we have `c` (no `a` before it), then it's unsolvable.

The sequence listed above won't generate addtional characters. Thus we can first remove all `c`, then all `b`, and finally all `a`. Every operation can be done in three steps, thus the number of operations won't exceed $3n$. Time complexity is $O(n)$.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-14-icpc-practice/L.cpp %}
```

</details>

