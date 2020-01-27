---
layout: post
title: January Cook-Off 2020 Division 1 
tags: icpc codechef cook114 cookoff centroid-decomposition dp tree-dp fenwick-tree

---

I made A LOT of stupid mistake this round... probably because I'm too tired ><. Hope this won't happen in future rounds.

Contest link: [Codechef cook114 div 1](https://www.codechef.com/COOK114A)

## RGAND <span style="font-size:medium;">[01:46], 4 tries</span>

Let $a_i=\land\_{j=L}^{j=i}=L\land L+1 \land \dots \land i$. Then, we can observe that the sequence of $a$ is non-increasing i.e. $a\_i \ge a\_{i+1}$, and every bit (in binary) of $a_i$ will only appear in a continuous segment. Therefore, we can calculate the answer bit by bit. The time complexity is $O(\log C)$. See the code for more details.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-20-codechef-cook114/RGAND.cpp %}
```

</details>

## CFINASUM <span style="font-size:medium;">[02:11], 4 tries</span>

Let $a_i=\sum\_{j=1}^{j=i}=A_1+A_2+\dots+A_i$, the prefix sum of A. Then, if we set $A_j=0,j=1,2,\dots,N$, we can observe that only $a_j, a\_{j+1}, \dots, a_N$ will be affected. Therefore, we can maintain two sets, one for prefixes that won't be influence, another for prefixes that will be influence, and count the answer in $O(N\log N)$. See code for more details.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-20-codechef-cook114/CFINASUM.cpp %}
```

</details>

## PRT <span style="font-size:medium;">[--:--], 4 tries</span>

I solved this problem during contest, however, make some stupid bugs (overflow) and can't find it before the contest ends...
This problem is a simple tree dp. The original problem wants us to find a best assignment of $A_1, A_2, \dots, A_N$ to vertices $1, 2, \dots, N$ such that $\sum\_{i=1}^{N}A_i\times \text{# of leaf paths that pass vertex } i$ is maximized. Let $c_i$ be # of leaf paths that pass vertex $i$. Then if we know the values of $c_i$, we can assign large $A_i$ to nodes with large $c_i$. To calculate $c_i$, we first calculate number of leaves in subtree $i$, $l_i$. Then, we calculate $c_i$ with another dfs (details are in the code). Note that we need to handle $N=1, 2$ seperately.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-20-codechef-cook114/PRT.cpp %}
```

</details>

## PLIND <span style="font-size:medium;">[--:--], 0 try</span>

In my opinion, this problem is the most difficult problem in this contest (though more people solve this than the next problem). First, we can observe that given $[L, R]$, we can solve it by calculating $[1, R], [1, L - 1]$ and subtract them. Now, given $X$, how do we solve $[1, X]$? Suppose we fill the number one by one starting from the largest digit. Let $dp[i][j][k]$ represent the number of ways to fill the question marks in $S_1S_2...S\_{i-1}??.??$, where we've already fill $S_1S_2...S\_{i-1}$ with some values and there are $j$ digits occuring odd number of times in $S_1S_2...S\_{i-1}$. Finally, $k$ represent whether $S_1S_2...S\_{i-1}$ is less then $X_1X_2...X\_{i-1}$ or not. Let $odd_i$ be number of digits that occur odd number of times in $X_1X_2...X_i$, and $small_i$ be number of digits that is smaller than $X_i$ and occur odd number of times in $X_1X_2...X\_{i-1}$. Then, the transition of dp will be:

<ul>
  <li> $k=0$:
    <ul>
      <li>fill $S_i$ with $X_i$ $\implies dp[i + 1][odd[i]][0]$</li>
      <li>fill $S_i$ with digits in $0, 1, \dots, X_i - 1$ that occurs odd number of times in $S_1S_2...S_{i-1}$ $\implies small[i]\times dp[i + 1][odd[i-1]-1][1]$</li>
      <li>fill $S_i$ with digits in $0, 1, \dots, X_i - 1$ that occurs even number of times in $S_1S_2...S_{i-1}$ $\implies (X_i-small[i])\times dp[i + 1][odd[i-1]+1][1]$</li>
    </ul>
  </li>
  <li> $k=1$: 
    <ul> 
      <li>fill $S_i$ with digits in $0, 1, \dots, 9$ that occurs odd number of times in $S_1S_2...S\_{i-1}$ $\implies (10-j)\times dp[i + 1][j - 1][1]$ </li>
      <li>fill $S_i$ with digits in $0, 1, \dots, 9$ that occurs even number of times in $S_1S_2...S\_{i-1}$ $\implies j\times dp[i + 1][j + 1][1]$ </li>
    </ul>
  Therefore, $dp[i][j][k]=(10-j)\times dp[i + 1][j - 1][k] + j\times dp[i + 1][j + 1][k]$ 
  </li>
</ul>

The answer for $[1,X]$ is $dp[2][1][0]+(X_1-1)\times dp[2][1][1]+\sum\_{i=1}^{len(X)-1}9\times dp[i + 2][1][1]$.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-20-codechef-cook114/PLIND.cpp %}
```

</details>

## CNTIT <span style="font-size:medium;">[--:--], 0 try</span>

To solve this problem, we need several observations:

<ul>
  <li> $M$ integers are polygonable $\Longleftrightarrow$ $\sum_{a\in M\text{ and a is not the largest}}a \ge \text{ max element in } M$.
  <li> If $M$ integers are not polygonable, then exist exactly one element (max element in $M$) which is larger then the sum of the rest elements.</li>
</ul>

Using the observations above, and $K\le 10$, we can iterate over all colors and count number of paths that is not polygonable caused by caused by a specific color.
To do this, suppose that we're considering color $c$. Then for all edges with color $c$, we give it a weight $-1$. For all other colors, we give them weight $1$. Then, a path is not polygonable $\Longleftrightarrow$ sum of weights over the path $<0$. Now, to count paths that have negetive weight sums, we can use [centroid decomposition]({% link _posts/2020-01-16-centroid-decomposition.md %}) (a kind of divide and conquer) plus fenwick tree to do it. The total time complexity is $O(KN\log^2N)$. See code for more details.


<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-20-codechef-cook114/CNTIT.cpp %}
```

</details>

