---
layout: post
title: A Simple Introduction to Li-Chao Segment Tree
tags: icpc algorithm segment-tree convex-hull

---

## Outline

+ [What is Li-Chao Segment Tree?](#what-is-li-chao-segment-tree)
+ [Implementation](#implementation)
  + [Insert](#insert)
  + [Query](#query)
+ [Example problems](#example-problems)
  + [BZOJ1568 - Blue Mary's Company](#a-hrefhttpswwwlydsycomjudgeonlineproblemphpid1568bzoj1568---blue-marys-companya)
  + [Codechef - Polynomials](#a-hrefhttpswwwcodechefcomnov17problemspolycodechef---polynomialsa)
  + [CF923F - Escape Through Leaf](#a-hrefhttpscodeforcescomproblemsetproblem932fcf923f---escape-through-leafa)
+ [More problems](#more-problems)

## What is Li-Chao Segment Tree?

Basically, Li-Chao Segment Trees can solve problems like this:

> You're given a set $S$ containing function of the same "type" (ex. lines, $y=ax+b$). The type of function need to have the **transcending property** (will be explained later). You need to handle two type of queries:
> + Add a function to $S$
> + Answer the maximum/minimum value at $x=t$ considering all functions in $S$

A type of function has **transcending property** if:

> Given two functions $f(x), g(x)$ of that type, if $f(t)$ is greater than/smaller than $g(t)$ for some $x=t$, then $f(x)$ will be greater than/smaller than $g(x)$ for $x>t$. In other words, once $f(x)$ "win/lose" $g(x)$, $f(x)$ will continue to "win/lose" $g(x)$.

## Implementation

We use line as an example here:
```c++
struct Line {
  ld m, b;
  ld operator()(ld x) { return m * x + b; }
} a[C * 4];
```

On every node of the segment tree, we store the line that maximize(or minimize) the value of the middle i.e. if the interval of the node is $\[L, R)$ , then the line stored on it maximize(or minimize) $\frac{L+R}{2}$.

### Insert

Suppose that we are inserting a new line to the node which corresponding interval is $\[L, R)$. For conveinence, we assume that the line on the node have a smaller slope. Let $mid=\frac{L+R}{2}$. Then, we have two cases to consider ($red$ is the original line in the node):

1. $red(mid) < blue(mid)$

<div style="text-align:center"><img src="/assets/images/li-chao-segment-tree/smaller.png" /></div>

In this case, we should replace $red$ with $blue$. But should we discard $red$? No! As you can see, somewhere in $\[L, mid)$ needs $red$. Therefore, we should pass this line to the node with interval $\[L, mid)$, which is its left son.

2. $red(mid) > blue(mid)$ 

<div style="text-align:center"><img src="/assets/images/li-chao-segment-tree/greater.png" /></div>

Similarly, we should keep $red$ in this node and pass $blue$ to its right son, whose corresponding interval is $\[mid, R)$.

```c++
void insert(int l, int r, Line seg, int o=0) {
  if(l + 1 == r) {
    if(seg(l) > a[o](l)) a[o] = seg;
    return;
  }
  int mid= (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
  if(a[o].m > seg.m) swap(a[o], seg);
  if(a[o](mid) < seg(mid)) {
    swap(a[o], seg);
    insert(l, mid, seg, lson);
  }
  else insert(mid, r, seg, rson);
}
```

The time complexity is $O(\log C)$, where $C$ is the size of range we maintain.

### Query

From the way we insert lines, we know that we only need to consider intervals that conatins the point we want to ask.

```c++
ld query(int l, int r, int x, int o=0) {
  if(l + 1 == r) return a[o](x);
  int mid = (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
  if(x < mid) return max(a[o](x), query(l, mid, x, lson));
  else return max(a[o](x), query(mid, r, x, rson));
}
```

The time complexity is still $O(\log C)$, as we will only pass $O(\log C)$ nodes.

## Example problems

### [BZOJ1568 - Blue Mary's Company](https://www.lydsy.com/JudgeOnline/problem.php?id=1568)

#### Problem description

You have a empty set of lines $S$ in the beginning. You need to handle $Q$ queries of two kinds:

+ $Project\space a\space b$ : Insert a line $f(x)=bx+(a-b)$.
+ $Query\space t$ : Calculate $\max\_{f\in S} \left\\\{ f(t) \right\\\}$

$1\le Q\le 10^5, 1\le T \le 5\times 10^4, |a| \le 10^6, 0 < b < 100$

#### Problem analysis

You might discover that this problem can be solved with dynamic hull, and commonly used dynamic hull algorithm has $O(N\log N)$ complexity, where $N$ is the number of lines. However, dynamic hull is usually hard to implement and have a large constant factor in practice. So, let's solve this problem using Li-Chao segment tree! Observe that "line" is a function type that have the transcending property, thus we can use Li-Chao segment tree.

#### Problem solution

This problem can be solved almost directly by the code above. Please kindly refer to the code for more details. The complexity is $O(Q\log T)$ .

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-06-li-chao-segment-tree/bzoj-1568.cpp %}
```

</details>

### [Codechef - Polynomials](https://www.codechef.com/NOV17/problems/POLY)

#### Problem description

You're given $N$ functions $y_i(x)=a\_0 + a\_1x + a\_2x^2 + a\_3x^3$. Now, you need to answer $Q$ queries. For every query, you are given an integer $t$ and you need to answer $\min\_{1\le i\le N}\left\\\{ y\_i(t) \right\\\}$ .

$1\le N, Q\le 10^5, 0\le t\le 10^5, 0\le a_3\le 10^3, 0\le a_0, a_1, a_2\le 10^5$

#### Problem analysis

First, notice that the range of query is $[0, 10^5]$. Then, it can be prove that after $sqrt(a_0)$, two functions can intersect at most one time. Therefore, we can maintain $x=[0, sqrt(a_0)]$ directly and maintain $x=[sqrt(a_0)+1, 10^5]$ using li-chao segment trees.

#### Problem solution

The solution is described above. Note that we do not use slope to decide which function to pass down, but uses the value of $x=L$ and $x=mid$. Refer to the code for more details. The time complexity is $O((N+Q)\log C)$.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-06-li-chao-segment-tree/codechef-poly.cpp %}
```

</details>

### [CF923F - Escape Through Leaf](https://codeforces.com/problemset/problem/932/F)

#### Problem description

You're given a tree with $n$ nodes rooted at node $1$. Each node has two associated value $a_i, b_i$. You can jump from a node to any node in its subtree. The cost of jump from node $u$ to $v$ is $a_u\times b_v$. Note that you cannot jump from a node to itself.

Now, you need to calculate the minimum cost to reach leaf for every node. Node that node $1$ is not considered a leaf even it's degree is $1$.

$1\le N\le 2\times 10^5, |a_i|, |b_i| \le 10^5$

#### Problem analysis

First, that this problem is a DP problem with the transition equation be:
$$
dp_u = \max\_{v\in subtree_u} \left\\\{ dp_v + a_u \times b_v \right\\\}
$$
Then, observe that $dp_v + a_u \times b_v$ can be viewed as lines $b_v\times x + dp_v$, which means that what we are finding is the maximum value of $x=a_u$ among all lines formed by nodes in its subtree. This can be done by li-chao segment tree, obviously.

Thus, we can build a li-chao segment tree for every node and merge it to its parent. If we always merge the small ones to the big ones, then the number of extra inserts will only be $O(N\log N)$. 

#### Problem solution

The solution is described above. We implemented li-chao segment tree with dynamic node creation. More details in code. The time complexity is $O(N\log N\log C + N\log C)$, and the space complexity is $O(N)$(we have only $N$ lines).

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-06-li-chao-segment-tree/cf-923f.cpp %}
```

</details>

## More problems

+ [CS Academy - Squared Ends](https://csacademy.com/contest/archive/task/squared-ends)
+ [BZOJ4515 - Game](https://www.lydsy.com/JudgeOnline/problem.php?id=4515)
+ [BZOJ3938 - Robot](https://www.lydsy.com/JudgeOnline/problem.php?id=3938)

