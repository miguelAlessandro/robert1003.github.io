---
layout: post
title: February Challenge 2020 Division 1
tags: icpc codechef codechef-challenge

---

Contest link: [Codechef feb20 div 1](https://www.codechef.com/FEB20A)

+ [NOCHANGE](#a-hrefhttpswwwcodechefcomfeb20aproblemsnochangenochangea-span-stylefont-sizemedium100span)
+ [LONGCOOK](#a-hrefhttpswwwcodechefcomfeb20aproblemslongcooklongcooka-span-stylefont-sizemedium100span)
+ [CHEFRAIL](#a-hrefhttpswwwcodechefcomfeb20aproblemschefrailchefraila-span-stylefont-sizemedium40span)
+ [EXPCH](#a-hrefhttpswwwcodechefcomfeb20aproblemsexpchexpcha-span-stylefont-sizemedium100span)
+ [CHGORAM2](#a-hrefhttpswwwcodechefcomfeb20aproblemschgoram2chgoram2a-span-stylefont-sizemedium15span)
+ [BALNET](#a-hrefhttpswwwcodechefcomfeb20aproblemsbalnetbalneta-span-stylefont-sizemedium0span)
+ [POLCHAIN](#a-hrefhttpswwwcodechefcomfeb20aproblemspolchainpolchaina-span-stylefont-sizemedium0span)

## [NOCHANGE](https://www.codechef.com/FEB20A/problems/NOCHANGE) <span style="font-size:medium;">[100]</span>

The pseudocode is given as below:

+ If $D_i \nmid P$, then print $\left\\\{ \lceil \frac{P}{D_i} \rceil \right\\\}$
+ If for some $k, i, j$ exists such that $p-k\cdot D_j \mid D_i$ and $p\gt k\cdot D_j$, then print $\left\\\{ D_i, \lceil \frac{p-k\cdot D_j}{D_i} \rceil \right\\\}$
+ Otherwise, no solution

The time complexity is $O(N^2)$. Note that $O(N)$ solution exists and is described in the official editorial.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-19-codechef-feb20/NOCHANGE.cpp %}
```

</details>

## [LONGCOOK](https://www.codechef.com/FEB20A/problems/LONGCOOK) <span style="font-size:medium;">[100]</span>

We can first find the pattern using [Zeller's congruence](https://en.wikipedia.org/wiki/Zeller%27s_congruence). Then, you may find that the required overlap will only happen in February and the pattern will have a cycle every 400 year. Details given in code.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-19-codechef-feb20/LONGCOOK.cpp %}
```

</details>

## [CHEFRAIL](https://www.codechef.com/FEB20A/problems/CHEFRAIL) <span style="font-size:medium;">[40]</span>

The original problem can be transfered into: Given three sets of number $A, B, C$, find how many triplets $(a, b, c), a\in A, b\in B, c\in C$ satisfies $ab=c^2$. This can be solve in two ways.

The first way to solve it is to do prime factorization on every $c^2$. This can be done ny multiplying the every term of the prime factorization of $c$ by $2$. Then, enumerate all factors of $c^2$ which is less then $C$ ($C$ is the range of the numbers, which is $10^5$ in this problem) and check whether the corresponding elements in $A$ and $B$ exists (This can be done in $O(1)$ as we can store a frequency array first). It can be proven that the time complexity of this solution is $O(N\sqrt{N})$.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-19-codechef-feb20/CHEFRAIL.cpp %}
```
</details>

The second way is enumerate the Greatest Common Divisor (gcd). Let $g=gcd(a, b), a=gc, b=gd$. Then $c^2=g^2cd$ implying that $c$ and $d$ must both be square numbers. So we can rewrite them as $a=gc=gx^2, b=gd=gy^2, c=gxy$, and $gcd(x, y)=1$. 

Now, given the new form of the required number, we can enumerate them in an effective way. We can enumerate $x$ from $1$ to $\sqrt{C}$, $y$ from $1$ to $\sqrt{C}$, then enumerate $g$ from $1$ until $gxy$ is larger then $C$. It can be proven that the time complexity of this solution is $O(N\log N)$.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-19-codechef-feb20/CHEFRAIL-2.cpp %}
```
</details>

## [EXPCH](https://www.codechef.com/FEB20A/problems/EXPCH) <span style="font-size:medium;">[100]</span>

First, if the problem only ask the number of changes considering substring $s[l..r]$, then we can solve it by simulate it directly with a stack (or a number, as we only care about the size of the stack).

Second, the required answer can be calculated as $\frac{\sum\_{1\le l \le r\le N} \text{number_of_change}(s[l..r])}{N(N+1)/2}$.

We can simulate $N$ stacks $s_1, s_2, \dots, s_N$, starting from $1, 2, \dots, N$ respectively and get all changes. Of course we can't really simulate them. What we can do is to maintain one stack $s$ where each elements in the stack represent number of stacks in that state. For example, suppose there's stack that looks like this: $(bottom) [ 1, 2, 0, 3 ] (top)$. Then this means that there's $3$ empty stacks, $0$ stack with size $1$, $2$ stack with size $2$, and $1$ stack with size $3$. There're some cases:

+ met "(" : This means that the size of all stacks will increase by one. So we push a $0$ into $s$.
+ met ")" : This means that the size of all stacks will decrease by one. Thus we need to pop the top element of $s$ out of it (let it be $x$). Our answer will increase by $x$, and we need to add $x$ to the second-top element.
+ met "\*" : This means that the number of empty stacks will increase by one. So we increase the top element of $s$ by one.

The time complexity is $O(N)$.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-19-codechef-feb20/EXPCH.cpp %}
```

</details>

## [CHGORAM2](https://www.codechef.com/FEB20A/problems/CHGORAM2) <span style="font-size:medium;">[15]</span>

First observe that there always exist a center node for every sutiable triplets. Then, we can solve it with two DPs:

+ DP state : 
  + $dp^1\_{u, i}$ represents the number of nodes $v\in sub_u$ which satisfies $dis(u, v)=i$
  + $dp^2\_{u, i}$ represents the number of pairs $(v, w)\in sub_u$ satisfies $dis(u, v)=dis(u, w)$ and $dis(u, v)-dis(u, lca(v, w))-dis(u, lca(v, w))=i$
+ DP transition :
  + $dp^1\_{u, i}=\sum\_{v\in sub_u} dp^1\_{v, i - 1}$
  + $dp^2\_{u, i}=\sum\_{v\in sub_u} dp^2\_{v, i - 1} + \sum\_{v, w \in sub_u} dp^1\_{v, i - 1}\cdot dp^1\_{w, i - 1}$
+ Final answer (calculated during DPs) :
  + For $u$, $ans$ += $\sum\_{v, w\in sub_u} dp^1\_{v, i}\cdot dp^2\_{w, i}, i=0, 1, \dots$

You might think that the time complexity is $O(N^2)$ or more. However, we can use "merge small to large" strategy and use deque as dp array and can reduce the time complexity to $O(N)$. See the code below for details.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-19-codechef-feb20/CHGORAM2.cpp %}
```

</details>

## [BALNET](https://www.codechef.com/FEB20A/problems/BALNET) <span style="font-size:medium;">[0]</span>

We can first make those wires into pairs $(1, 2), (3, 4), \dots, $. If $N$ is odd, then there's one wire that is single. Then, we can view every balancer as a change of pairing. Finally, we can set all wires belong to the upper pair to $1$ and recover the answer. More details in code.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-19-codechef-feb20/BALNET.cpp %}
```

</details>

## [POLCHAIN](https://www.codechef.com/FEB20A/problems/POLCHAIN) <span style="font-size:medium;">[0]</span>

First notice that inorder for a polygon $a$ to "fit" in polygon $b$, the area of $a$ must not be greater then area of $b$. Thus, we can sort all the given polygons by area first. Then, let $l_i, r_i, d_i, u_i$ represents the movement of the $i^{th}$ polygon to the left, right, down, up ($l_i, r_i, d_i, u_i \ge 0$). For a polygon $a$ to "fit" in another polygon $b$, all vertices in $a$ must be inside $b$. In other words, all vertices in $a$ must be at the intersection of half planes formed by all edges of $b$. Let $A$ be a vertice in $a$, $B, C$ be neighboring vertices in $b$, $\textbf{v}=A-B$, $\textbf{w}=C-B$ which are two vectors.

<div style="text-align:center"><img style="width:30%" src="/assets/images/codechef-feb20/POLCHAIN.png" /></div>

$A$ is in the left half plane formed by $B, C$ iff $\textbf{v}\times \textbf{w}\le 0$. Substitute those variables into it we can get
$$
\begin{align*}
&\implies (v_x+r_i-r\_{i+1}-l_i+l\_{i+1})w_y - (v_y+u_i-u\_{i+1}-d_i+d\_{i+1})w_x \le 0 \\\\
&\implies r_iw_y-r\_{i+1}w_y-l_iw_y+l\_{i+1}w_y-u_iw_x+u\_{i+1}w_x+d_iw_x-d\_{i+1}w_x \le \textbf{w}\times \textbf{v}
\end{align*}
$$
where the last equation is a linear inequality. Thus, the original problem can be transformed into a bunch of linear inequalities and we want to minimize $\sum_i l_i+r_i+d_i+u_i$. This is a classic problem called linear programming, and can be solved with the Simplex algorithm. I used the Simplex solver online ([link](https://github.com/ivangalban/TeamReference/blob/master/Numeric/simplex.cpp)).

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-19-codechef-feb20/POLCHAIN.cpp %}
```

</details>

