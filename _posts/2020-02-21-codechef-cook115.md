---
layout: post
title: February Cook-Off 2020 Division 1
tags: icpc codechef codechef-cookoff

---

This round is quite easy compare to previous Cookoffs, the solutions are not hard to come up (although the solution I came up aren't the best solution and need some constant optimization tricks XD). However, I implemented them slow and buggy...and I couldn't solve them all in the contest (stucked in PEPPERA, an easy DP problem...).

Contest link: [Codechef cook115 div 1](https://www.codechef.com/COOK115A)

+ [XORGM](#a-hrefhttpswwwcodechefcomcook115aproblemsxorgmxorgma-span-stylefont-sizemedium0012-1-tryspan)
+ [CYCLCSUM](#a-hrefhttpswwwcodechefcomcook115aproblemscyclcsumcyclcsuma-span-stylefont-sizemedium0039-1-tryspan)
+ [PEPPERA](#a-hrefhttpswwwcodechefcomcook115aproblemspepperapepperaa-span-stylefont-sizemedium-----1-tryspan)
+ [CHFDIV](#a-hrefhttpswwwcodechefcomcook115aproblemschfdivchfdiva-span-stylefont-sizemedium0212-3-triesspan)
+ [SUBMAXA](#a-hrefhttpswwwcodechefcomcook115aproblemssubmaxasubmaxaa-span-stylefont-sizemedium-----0-tryspan)

## [XORGM](https://www.codechef.com/COOK115A/problems/XORGM) <span style="font-size:medium;">[00:12], 1 try</span>

Let $target = A_1 \oplus C_1=A_2 \oplus C_2 =\dots=A_N \oplus C_N$. As $N$ is odd, $target = \oplus\_{i=1}^{N}\left(A_i\oplus C_i\right)$, which can be calculated with the given $A$ and $C$. Now, as we know the $target$, then for each $A_i$, we know that the corresponding $C_j$ satisfies $C_j=A_i\oplus target$(as $target = A_i\oplus C_j$). Therefore, we can find the corresponding value for each $A_i$ and determine whether $C$ is satisfiable or not. See code for implementation details.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-21-codechef-cook115/XORGM.cpp %}
```

</details>

## [CYCLCSUM](https://www.codechef.com/COOK115A/problems/CYCLCSUM) <span style="font-size:medium;">[00:39], 1 try</span>

To solve this problem, you first need to know how to solve "Maximum Subarray Sum in a given Range"([link](https://www.geeksforgeeks.org/maximum-subarray-sum-given-range/)). After knowing how to solve the previous problem, then this problem is just the exactly same problem: Given $B_1, B_2, \dots, B_N, B\_{N+1}, \dots, B\_{2N}$ where $B_i=B\_{i+N}=A_i$, ask the maximum subarray sum of $(1, N), (2, N + 1), \dots, (N, 2N - 1)$.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-21-codechef-cook115/CYCLCSUM.cpp %}
```

</details>

## [PEPPERA](https://www.codechef.com/COOK115A/problems/PEPPERA) <span style="font-size:medium;">[--:--], 1 try</span>

Let $p$ be the pizza, $s_1[i]=\sum\_{j=1}^{\frac{N}{2}} p\_{i, j} , s_2[i]=\sum\_{j=\frac{N}{2}+1}^{N} p\_{i, j}$. Then this problem can be solved by DP:

+ DP state : $dp\_{i, j}$ represents that considering row from $1$ to $i$, whether a total of $j$ pepperoni on the first half is achievable or not
+ DP transition : $dp\_{i, j}=dp\_{i-1, j-s_1[i]} \lor dp\_{i-1, j-s_2[i]}$

Then, as we want to minimize the difference between them, we can choose a $j$ such that $dp\_{N, j} = 1$ and it is closest to the half of the total numbers of pepperoni. Finally, we backtrack the answer. See more details in the code.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-21-codechef-cook115/PEPPERA.cpp %}
```

</details>

## [CHFDIV](https://www.codechef.com/COOK115A/problems/CHFDIV) <span style="font-size:medium;">[02:12], 3 tries</span>

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-21-codechef-cook115/CHFDIV.cpp %}
```

</details>

## [SUBMAXA](https://www.codechef.com/COOK115A/problems/SUBMAXA) <span style="font-size:medium;">[--:--], 0 try</span>

Let's consider the largest number $x=\max\_{i=1}^{N}A_i$ first. How much will it contribute to each $F_i$? After some thinking, you might find out that it adds $x$ to $F_1$, $2x$ to $F_2$, ..., $Nx$ to $F_N$. Then, suppose that $A_k=x$. As $x$ is the largest value in $A$, we can split $A$ into two parts and solve it recursively. This is because for those $(i, j)$ such that $i\le k \le j$, the maximum value will be $x$.

Now, suppose that we're considering $[l, r]$ and the position of the $x=\max\_{i=l}^{r}A_i$ is $p$. Then, one can observe that $x$ will contribute $x$ to $F_1$, $2x$ to $F_2$, ..., $tx$ to $F_t$, $(t-1)x$ to $F\_{t+1}$, ..., $x$ to $F\_{r-l+1}$, where $t=\min\\\{p - l + 1, r - p + 1\\\}$. 

So now we know how to calculate the final answers. However, if we can't find the maximum value and its position efficiently or didn't maintain those contributions properly, our time complexity will explode. Let's handle them seperately. First, the maximum value part can be handled with Sparse Table ([tutorial](https://cp-algorithms.com/data_structures/sparse-table.html)) which can answer queries in $O(1)$ after $O(N\log N)$ preprocessing. Second, note that every $A_i$'s contribution has this kind of form: $x, 2x, \dots, (t-1)x, tx, (t-1)x, \dots, x$. The **difference** of them will be $x, x, \dots, x, -x, -x, \dots, -x$. The **difference of difference** of them will be $x, 0, \dots, 0, -2x, 0, \dots, 0$. Therefore, we can maintain every element's contribution in $O(1)$ time by maintaining the **difference of difference** of them. To reconstruct the original array, we simply just reconstruct the first difference array then reconstruct the original array.

Our time complexity is $O(N\log N)$, which is a little bit high (The expected complexity is $O(N)$). So we need some constant optimization tricks including faster I/O and replace "recursion" with a stack (in our case, a queue is enough). See details in code below.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-21-codechef-cook115/SUBMAXA.cpp %}
```

</details>
