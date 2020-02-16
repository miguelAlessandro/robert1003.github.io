---
layout: post
title: Graph and Segment Trees (Under construction)
tags: icpc algorithm segment-tree graph

---

## Outline

+ [What is this post about?](#what-is-this-post-about)
+ [Example problems - Shortest path](#example-problems---shortest-path)
  + [CF787D - Legacy](#a-hrefhttpscodeforcescomcontest787problemdcf787d---legacya)
  + [HDU5669 - Road](#a-hrefhttpacmhdueducnshowproblemphppid5669hdu5669---roada)
+ [Example problems - Flow](#example-problems---flow)
  + [CF793G - Oleg and chess](#a-hrefhttpscodeforcescomcontest793problemgcf793g---oleg-and-chessa)
+ [Example problems - DP on DAG](#example-problems---dp-on-dag)
  + [POI XXII PUS - Desert](#a-hrefhttpsszkopuleduplproblemsetproblempljxefyr0xmbq-kz1kgghesitekeystatementpoi-xxii-pus---deserta)
  + [CF1197E - Culture Code](#a-hrefhttpscodeforcescomcontest1197problemecf1197e---culture-codea)
  + [BZOJ5017 - Bomb](#a-hrefhttpswwwlydsycomjudgeonlineproblemphpid5017bzoj5017---bomba)
+ [More problems](#more-problems)

## What is this post about?

In this post, you'll see how to use segment trees to optimize graph construction. We'll go through several examples to demonstrate this technique.

## Example problems - Shortest path

### [CF787D - Legacy](https://codeforces.com/contest/787/problem/D)

#### Problem description

You're given an empty graph $G$ with $N$ nodes in it. Now, you need to add edges to the graph by the following three operations:

+ $1\space u\space v\space w$ : Add a edge from $u$ to $v$ weighted $w$
+ $2\space u\space l\space r\space w$ : Add edges from $u$ to $v=l, l+1, \dots, r$ with weight $w$
+ $3\space v\space l\space r\space w$ : Add edges from $u=l, l+1 \dots, r$ to $v$ with weight $w$

There're $Q$ operations in total. Please calculate the shortest path for all nodes starting from node $s$.

$1\le N, Q\le 10^5, 1\le s \le n, 1\le l, r, u, v\le N, l\le r, 1\le w\le 10^9$

#### Problem analysis

Obviously, we can't build the graph directly. Observe that every time we add edges, either the start or the end of edges are continuous. Therefore, we can build two segment trees like the following:

<details><summary>picture</summary>

<div style="text-align:center"><img style="width:65%" src="/assets/images/graphs-and-segment-tree/legacy-0.png" />
<br>
<br>
Arrows are edges with weight $0$. The leaf node are the original nodes in graph $G$.
</div>

</details>
<br>

For type two operations, we add $O(\log N)$ edges from $u$ to the nodes that correspond to $[l, r]$ with weight $w$. 

For example, if we want to add edge from $1$ to $[2, 6]$, then:

<details><summary>picture</summary>

<div style="text-align:center"><img style="width:65%" src="/assets/images/graphs-and-segment-tree/legacy-1.png" /></div>
<br>

</details>
<br>

For type three operations, we add $O(\log N)$ edges from nodes that correspond to $[l, r]$ to $v$ with weight $w$. 

For example, if we want to add edge from $[4, 8]$ to $2$, then:

<details><summary>picture</summary>

<div style="text-align:center"><img style="width:65%" src="/assets/images/graphs-and-segment-tree/legacy-2.png" /></div>
<br>

</details>
<br>

#### Problem solution

The number of nodes is $O(3N)$, and the number of edges is $O(2N + Q\log N)$, which are both acceptable. The final time complexity is $O(E\log V)=O((2N+Q\log N)\log 3N)$. Details in code.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-14-graphs-and-segment-tree/cf-787d.cpp %}
```

</details>

### [HDU5669 - Road](http://acm.hdu.edu.cn/showproblem.php?pid=5669)

#### Problem description

Given a empty graph $G$ with $N$ nodes, you need to add edges to the graph $M$ times. The format of every addition is $(a, b, c, d, w)$, meaning that there exist an undirected edge with weight $w$ between every pair $(x, y)$ where $x\in [a, b], y\in [c, d]$.

Now, you have $K$ times to fly over an edge $(u, v, w)$, which means that you don't need to pay the cost $w$. Please calculate the minimum cost from node $1$ to node $N$.

$1\le N\le 5\times 10^4, 1\le M\le 10^4, 0\le K\le 10, 1\le w\le 10^3$

#### Problem analysis

The $K$ chance to fly can be easily handled by adding a dimension to the state.

Similar to the previous problem, we first build two segment trees with the leaves as original nodes.
<br>
To handle the addition, we just create $O(\log^2 N)$ edges between nodes that correspond to $[a, b]$ and nodes that correspond to $[c, d]$ with weight $w$. 

For example, if we want to add edge between $[3, 5]$ and $[6, 8]$, then:

<details><summary>picture</summary>

<div style="text-align:center"><img style="width:65%" src="/assets/images/graphs-and-segment-tree/road.png" /></div>
<br>

</details>
<br>

Note that number of edges can be optimized to  $O(\log N)$ if we create an extra node every addition.

#### Problem solution

As we have $O(3NK)$ states (not nodes) and $O(2N + M\log^2 N)$ edges, the time complexity is $O((2N + M\log^2 N)\log 3NK)$.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-14-graphs-and-segment-tree/hdu-5669.cpp %}
```

</details>

## Example problems - Flow

### [CF793G - Oleg and chess](https://codeforces.com/contest/793/problem/G)

#### Problem description

Given a board with size $N\times N$, you want to put a bunch of rooks on it. However, there are $Q$ rectangles $(x_1, y_1, x_2, y_2)$ specifying that you cannot put anything in the rectangle area with lower-left cell $(x_1, y_1)$, upper-right cell $(x_2, y_2)$ on the board. Also, if you've put a rook on $(x, y)$ already, then you cannot put any rooks on $(x, i), (i, y), i\in [1, n]$. 

Please output the maximum number of rooks that can be put on the board not violating the rules specified.

$1\le N\le 10^4, 0\le Q\le 10^4, 1\le x_1 \le  x_2\le N, 1\le y_1 \le y_2 \le N$

#### Problem analysis

Observe that if we create $2N$ nodes, and for every valid position $(i, j)$, we connect an edge between $i$ and $j$. Then the original problem is exactly maximum matching on the graph, which can be solved by maximum flow. 
<br>
Thus, we create a segment tree to optimize our graph construction, and run dinic algorithm on it.

#### Problem solution

Details are given in code. I used persistent segment tree to help graph construction. For more details please refer to the code.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-14-graphs-and-segment-tree/cf-793g.cpp %}
```

</details>

## Example problems - DP on DAG

### [POI XXII PUS - Desert](https://szkopul.edu.pl/problemset/problem/_PLjXEFyR0XMBQ-kZ1k_GgHE/site/?key=statement)

#### Problem description

You're given an array $A$ with length $N$ but you only know $S$ elements in it. Moreover, you're given $M$ description of $A$. Every description is in the following format:

$$
l\space r\space k\space x_1\space x_2\space \dots x_k : \min\_{i\in \left\\\{ x_1, x_2, \dots, x_k \right\\\}} A_i \ge \max\_{i\in [l, r], i\not\in \left\\\{ x_1, x_2, \dots, x_k \right\\\}} A_i
$$

If exist some $A$ with $1\le A_i\le 10^9, i\in [1, N]$ satisfying the given description and inital elements, output $TAK$ and any possible $A$. Otherwise, output $NIE$.

$1\le S\le N\le 10^5, 1\le M\le 2\times 10^5, \sum k \le 2\times 10^5$

#### Problem analysis



#### Problem solution

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-14-graphs-and-segment-tree/poi-desert.cpp %}
```

</details>

### [CF1197E - Culture Code](https://codeforces.com/contest/1197/problem/E)

#### Problem description

You're given $N$ boxes. Every box has two attributes, $out$ and $in$ ($in < out$), specifying the total space of the box and the inner space of the box. A box $i$ can be put into a box $j$ iff $out_i \le in_j$.

Now, given a sequence of box $a_1, a_2, \dots, a_k$ satisfying $out\_{a_1} \le in\_{a_2}$ (such sequence is called *valid sequence*), the *extra space* of them is defined by $in\_{a_1} + \sum\_{i=2}^{k} in\_{a_i} - out\_{a\_{i-1}}$.

A set of boxes is valid if:
1. Exist an arrangement of element in the box such that it's a valid sequence and minimize *extra space*
2. Adding any other box into this set will make it invalid

Please output the number of valid set module $10^9+7$.

$1\le N\le 2\times 10^5, 1\le in\le out\le 10^9$

#### Problem analysis
#### Problem solution

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-14-graphs-and-segment-tree/cf-1197e.cpp %}
```

</details>

### [BZOJ5017 - Bomb](https://www.lydsy.com/JudgeOnline/problem.php?id=5017)

#### Problem description

There's $N$ bombs on a number line. Every bomb is placed at $x_i$, with explosion radius $r_i$. When a bomb explodes, all bombs $j$ with $x_i-r_i\le x_j\le x_i+r_i$ will explodes, too.

Now, let $c_i$ be the number of bombs that will explode if we manually activate the $i^{th}$ bomb. Please calculate $\left(\sum\_{i=1}^{N}ic_i\right)\mod 10^9+7$.

$1\le N\le 5\times 10^5, -10^{18} \le x_i \le 10^{18}, 0\le r_i\le 2\times 10^{18}$

#### Problem analysis
#### Problem solution

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-14-graphs-and-segment-tree/bzoj-5017.cpp %}
```

</details>

## More problems

+ [HDU5420 - Victor and Proposition](http://acm.hdu.edu.cn/showproblem.php?pid=5420)
+ [CF1045A - Last chance](https://codeforces.com/contest/1045/problem/A)
