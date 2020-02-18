---
layout: post
title: January Lunchtime 2020 Division 1 
tags: icpc codechef ltime80 lunchtime under-construction

---


Contest link: [Codechef ltime80 div 1](https://www.codechef.com/LTIME80A)

## POPTUNNL <span style="font-size:medium;">[00:22]</span>

We can build a directed graph and do a simple BFS on it. Be careful that for tile $i$, only tile $j, i-k\le j \le i+k$ can be considered.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-26-codechef-ltime80/POPTUNNL.cpp %}
```

</details>

## CARR <span style="font-size:medium;">[01:46]</span>

Let $dp_i$ be the number of required sequence with length $i$. Then, $dp_0=1, dp_1=M, dp_i=(M-1)\times dp\_{i - 1} + (M-1)\times dp\_{i - 2}$. We need to calculate $dp_N$. For the first subtask, we can do it naively in $O(N)$. For the second subtask, first observe that the transition can be written in matrix form:
$$
\begin{bmatrix}
  dp_i\\\ 
  dp\_{i-1}
\end{bmatrix}=
\begin{bmatrix}
  M-1 & M-1\\\ 
  1 & 0
\end{bmatrix}
\begin{bmatrix}
  dp\_{i-1}\\\ 
  dp\_{i-2}
\end{bmatrix}
$$
Therefore, 
$$
\begin{bmatrix}
  dp_N\\\ 
  dp\_{N-1}
\end{bmatrix}=
\begin{bmatrix}
  M-1 & M-1\\\ 
  1 & 0
\end{bmatrix}^{N-1}
\begin{bmatrix}
  dp\_{1}\\\ 
  dp\_{0}
\end{bmatrix}
$$
The second term can be done with fast matrix exponentiation in $O(2^3\log N)$.
<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-26-codechef-ltime80/CARR.cpp %}
```

</details>

## PAPER <span style="font-size:medium;">[02:40]</span>

First, let $ans2$ be the shortest distance between the initial $M$ points. Observe that when we unfold a paper, the distance shorter than $ans2$ will only appears at the edge that we unfolded. Therefore, we can first do discretization on both $x$ and $y$ axis, and maintain the points that is closest to edges on the top, bottom, left and right. Refer to the code for more details.

<div style="text-align:center"><img style="width:50%" src="/assets/images/codechef-ltime80/paper.png" /></div>
<br>

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-26-codechef-ltime80/PAPER.cpp %}
```

</details>

## MINMAXIN <span style="font-size:medium;">[--:--]</span>

We can build a "compare tree" for this problem. For example, suppose that $N=4$, then the compare tree looks like this:

<div style="text-align:center"><img style="width:50%" src="/assets/images/codechef-ltime80/compare-tree.png" /></div>
<br>

This tree tells us how to what questions to ask. For this example, we need to compare $(A_1,A_2)$ from node $4, 5$, $(A_3,A_4)$ from node $6, 7$, and then compare the winner of the two groups. Every node will collect result from the two children of it, then compare them. Why using compare tree? Because when we find the largest/smallest element, in order to find the second largest/smallest element, we only need to consider the elements that the largest/smallest wins in the compare tree. This is correct because the second largest/smallest must have lose to the largest/smallest element. By doing this, we can solve this problem in $2N+2\log N$, as the height of the tree is $\log N$. To reduce it to $\lfloor \frac{3}{2}N \rfloor + 2\log N$, we can memorize the result of comparision. More details in code.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-26-codechef-ltime80/MINMAXIN.cpp %}
```

</details>

## CCDSAP <span style="font-size:medium;">[--:--]</span>

</details>

