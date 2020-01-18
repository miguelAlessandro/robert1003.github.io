---
layout: post
title: A Simple Introduction to Centroid Decomposition
tags: icpc algorithm tree decomposition

---

## Outline

+ [What's a centroid?](#whats-a-centroid)
  + [How to find it?](#how-to-find-a-centroid)
+ [Centroid decomposition](#centroid-decomposition)
  + [What is it?](#what-is-centroid-decomposition)
  + [Implemention](#implementation)
  + [Several properties](#properties)
+ [Example problems](#example-problems)
  + [CF342E - Xenia and Tree](#a-hrefhttpcodeforcescomproblemsetproblem342ecf342e---xenia-and-treea)
  + [IOI'11 - Race](#a-hrefhttpwcipegcomproblemioi1112ioi11---racea)
  + [Codechef - Prime Distance On Tree](#a-hrefhttpswwwcodechefcomproblemsprimedstcodechef---prime-distance-on-treea)
  + [More problems](#more-problems)

## What's a centroid?

Let $T$ be a tree with $n$ nodes. A node $u$ is a **centroid** iff the size of each subtree after removing $u$ is not greater than $\frac{n}{2}$. Note that the **center** of a tree is different from the centroid of a tree, which is usually related with height of the tree. Intuitively, centroid can be viewed as the "center of mass" of $T$.

<div style="text-align:center"><img src="/assets/images/centroid-decomposition/centroid-def.gif" /></div>
<br>

### How to find a centroid?

First, we choose an arbitrary node $x$. We use a DFS to calculate the size of each subtree ($x$ is the root). Then, we can "walk" to the centroid starting from $x$ by:

+ If $x$ is the centroid, return $x$.
+ Else, we know that exist exactly one node $y$ adjacent to $x$ satisfying $|y| > \frac{n}{2}$. Walk to $y$ and do it again.

<div style="text-align:center"><img src="/assets/images/centroid-decomposition/centroid-alg.gif" /></div>
<br>

$|y|$ is the number of nodes of the subtree rooted at $y$. Why is there exactly one $y$? There must be **at least** one such nodes since $x$ is not a centroid, and there must be **at most** one such nodes since two or more such nodes implies that $|x| > n$ which is impossible.

```c++
vector<int> G[N]; // tree stored in adjacency list
int sz[N];

int dfs(int u, int p) {
  sz[u] = 1;
  for(auto v : G[u]) if(v != p) {
    sz[u] += dfs(v, u);
  }
  return sz[u];
}
int centroid(int u, int p, int n) { // n is the size of tree
  for(auto v : G[u]) if(v != p) {
    if(sz[v] > n / 2) return v;
  }
  return u;
}
```

The total complexity is $O(n)$.

## Centroid decomposition

This technique is actually *Divide and Conquer* applied on tree.

### What is centroid decomposition?

A **centroid decomposition** of a tree $T$ is another tree $T^{'}$ defined recursively as:

+ root of $T^{'}$ is the centroid of $T$
+ childs of the root are the centroid of the subtrees resulting from erasing the centroid of $T$

Too difficult to understand? Let's see an example:

<div style="text-align:center"><img src="/assets/images/centroid-decomposition/centroid-tree.png" /></div>
<br>

+ $3$ is the root of the centroid tree/centroid of the original tree, and $11, 1, 7, 4$ are children of $3$, which are the centroids of the subtrees after removing $3$.
+ $11$ is the root of the centroid tree/centroid of the original tree, and $15, 13, 6$ are children of $11$, which are the centroids of the subtrees after removing $11$.

... so on and so on.

### Implementation

```c++
set<int> G[N]; // adjacency list (note that this is stored in set, not vector)
int sz[N], pa[N];

int dfs(int u, int p) {
  sz[u] = 1;
  for(auto v : G[u]) if(v != p) {
    sz[u] += dfs(v, u);
  }
  return sz[u];
}
int centroid(int u, int p, int n) {
  for(auto v : G[u]) if(v != p) {
    if(sz[v] > n / 2) return centroid(v, u, n);
  }
  return u;
}
void build(int u, int p) {
  int n = dfs(u, p);
  int c = centroid(u, p, n);
  if(p == -1) p = c;
  pa[c] = p;

  vector<int> tmp(G[c].begin(), G[c].end());
  for(auto v : tmp) {
    G[c].erase(v); G[v].erase(c);
    build(v, c);
  }
}
```

It costs $O(n)$ to build each level of the centroid tree, and the height of the centroid tree is $O(\log n)$. The deletion of edge is also $O(n\log n)$, as we only have $O(n)$ edges to remove and each removal cost $O(\log n)$. Therefore, the total complexity is $O(n\log n)$.

### Properties

1. A node $u$ belongs to the component of all its ancesters.
2. Every path from $u$ to $v$ can be decomposed into path from $u$ to $w$, $w$ to $v$ where $w$ is the least common ancestor of $u$, $v$ in centroid tree.
3. We can represent all possible paths in the original tree (there are $n^2$ paths) as a concatenation of two paths in a $O(n\log n)$ set composed of paths like this: $(u, fa(u)), (u, fa(fa(u))), \dots$ for all possible $u$.

If you don't understand the statement above, the example below might help :)

<details><summary>Example</summary>

<div style="text-align:center"><img src="/assets/images/centroid-decomposition/centroid-tree.png" /></div>
<br>

1. Let's focus on $9$. We can observe that $9$ is in the component of its ancestors $6, 11, 3$.
2. Take $14$ to $10$ as an example $\implies$ $path(14,10)=path(14,3)+path(3,10)$, where $3=lca(14,10)$.
3. The "$O(n\log n)$ set" contains paths (on the centroid tree) like $(14, 15), (14, 11), (14, 3)$ and $(13, 11), (13, 3)$ and so on. Now we pick an arbitrary path, say $(1, 4)$. Then $(1, 4)=(1, 3)+(4, 3)$, which are both in the given set.

</details>
<br>

Proofs are given below, click it if you're interested.

<details><summary>Proof</summary>

1. Immediate from the construction of centroid tree.
2. This can be proved by contradiction. Suppose that $w=lca(u, v)$ is not in the path from $u, v$. This implies that $u, v$ belongs to the same subtree when removing $w$. However, this means that $lca(u, v)$ is not $w\implies $ contradiction.
3. First, as the height of centroid tree is $O(\lg n)$, the size of the set is $O(n\lg n)$. Then, by the second property, every path can be decomposed into two parts, splitting at the lca's. Thus, all possible paths can be represented with elements in that set.

</details>

## Example problems

### [CF342E - Xenia and Tree](http://codeforces.com/problemset/problem/342/E)

#### Problem description

You are given a tree consist of $N$ nodes, indexed from $1$ to $N$. Every node is painted either red or blue. In the beginning, node $1$ is red, and all other nodes are blue. Now, you need to handle $Q$ queries of two kinds:

+ $1\space u$: Paint a blue node $u$ into red.
+ $2\space u$: Answer the index of the red node closest to $u$.

$2\le N \le 10^5, 1 \le Q \le 10^5$

#### Problem analysis

First, we can observe that the answer to type $2$ query requires us to consider all paths starting from $u$, which will take $O(N)$ if we do it naively and is unacceptable. Now, take a look at the property 3 of centroid decomposition. This property tells us that if what we want to maintain about a path can be "merged" by two parts of the path, then we can answer type $2$ query in $O(\lg N)$. 

#### Problem solution

For each node $u$, we maintain a value $ans_u=\min\limits\_{v\text{ is red, } v\in \text{centroid tree rooted at }u} dis(u, v)$, which is the distance of closest red node to $u$ consider only nodes in component where $u$ is a centroid. Then, we can handle the queries by:

+ Paint: update the ans value of all ancestors of $u$ i.e. do $ans_v=\min\left\\{ans_v, dis(u, v)\right\\}$ for all $v\in \text{ancestors of }u$.
+ Query: $\min\limits\_{v\in \text{ancestors of} u} \\{ans_v + dis(u, v)\\}$ is the answer.

Both query take $O(\log N)$, as the depth of centroid tree is at most $O(\log N)$. Thus, the total complexity is $O(Q\log N)$.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-16-centroid-decomposition/xenia-and-tree.cpp %}
```

</details>

### [IOI'11 - Race](http://wcipeg.com/problem/ioi1112)

#### Problem description

You are given a **weight** tree with $N$ nodes, indexed from $1$ to $N$. Find the minimum number of edges used in a path with length $K$ or print "-1" if the path doesn't exist. 

$1\le N \le 2\times 10^5, 1\le w\_{i,j}\in \mathbb{N} \le 10^6, 1\le K \le 10^6$. 

#### Problem analysis

Similar to the previous problem, we need to consider all possible paths. However, in this problem, instead of minimizing the distance of path, we need to find a specific value of path while minimizing the number of edges. Recall that centroid decomposition is a D&C algorithm. Let's try to solve this problem using it. The divide part is easy, just collect answers from the subtrees (resulting from removing centroid). For the merge part, we need to consider paths that pass the current centroid. We can do a DFS to get the distance from centroid to its children. Then, do another DFS to get the answer. Look below for more details.

#### Problem solution

First, we do centroid decomposition on the tree. Let $u$ be the centroid. Then, we get the answer by the following algorithm:

```
Solve(u):
  ans = inf
  for v in child of u:
    ans = min(ans, Solve(v))
  do a DFS starting from u to calculate the distance and number of edges used 
    for nodes in component of u
  do another DFS to calculate the answer, while using an array to keep track of 
    possible distances starting from u and the minimum edges needed
  update ans from the previous DFS
  return ans
```

The complexity is $(N\log N)$.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-01-16-centroid-decomposition/race.cpp %}
```

</details>

<!--
### [Codechef - Prime Distance On Tree](https://www.codechef.com/problems/PRIMEDST)

#### Problem description

You're given a tree with $N$ nodes. If we select 2 distinct nodes uniformly at random, what's the probability that the distance between these 2 nodes is a prime number? Please calculate it.

#### Problem analysis

Obviously, we need to calculate number of pairs $(u, v)$ such that $dis(u, v)$ is a prime number. Again, we need to deal with all possible paths. Let's try centroid decomposition. For a centroid $u$, we can first collect the answers from the subtree, then do convolution to calculate number of paths that pass $u$.

#### Problem solution

Do centroid decomposition on the tree. Then, for each centroid $u$, first solve it for children $v$, and maintain an array that record how many decendents are at each distance. Then, we can maintain the "decendent array" of $v$ be adding 1 to it. Finally, we use fft to calculate the number of paths that pass $u$ for each distance. How can this be done? Look at this example:

<div style="text-align:center"><img src="/assets/images/centroid-decomposition/tree.png" style="max-height:200px"/></div>
<br>

Let $1$ be the centroid. Then, the calculation will be: $(1+x)(1+x+x^2)=1+2x+2x^2+x^3$, meaning that there're $1$ path with distance $0((1,1))$ (corresponds to $1\times x^0$), $2$ paths with distance $1((1,2),(1,3))$ (corresponds to $2\times x^1$), $2$ paths with distance $2((1,4),(2,4))$  (corresponds to $2\times x^2$), and $1$ path with distance $3((2,4))$ (corresponds to $1\times x^3$).

The complexity will be $O(N\log N \times \log N)=O(N\log^2N)$ as the convolution part can be done in $O(N\log N)$ by fft.

-->

### More problems

[Here](https://codeforces.com/blog/entry/52492) is a list of problmes solvable by centroid decomposition. Have fun!

### References

+ [Carpanese's Blog](https://medium.com/carpanese/an-illustrated-introduction-to-centroid-decomposition-8c1989d53308)
