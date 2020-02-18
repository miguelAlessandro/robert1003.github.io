---
layout: post
title: DP optimization - convex hull optimization
tags: icpc algorithm dp dp-optimization convex-hull-trick under-construction

---

## Outline

+ [Convex hull trick (CHT)](#convex-hull-trick-cht)
  + [Introduction](#introduction)
  + [Implementation]($implementation)
+ [Example problems](#example-problems)
  + [CF631E - Product Sum](#a-hrefhttpscodeforcescomcontest631problemecf631e---product-suma)
  + [CF660F - Bear and Bowling 4](#a-hrefhttpscodeforcescomcontest660problemfcf660f---bear-and-bowling-4a)
  + [CF311B - Cats Transport](#a-hrefhttpscodeforcescomcontest311problembcf311b---cats-transporta)
  + [CF673E - Levels and Regions](#a-hrefhttpscodeforcescomcontest673problemecf673e---levels-and-regionsa)
  + [CF1179D - Fedor Runs for President](#a-hrefhttpscodeforcescomcontest1179problemdcf1179d---fedor-runs-for-presidenta)
  + [CF455E - Function](#a-hrefhttpscodeforcescomcontest455problemecf455e---functiona)
+ [More problems](#more-problems)

## Convex hull trick (CHT)

### Introduction

[This](https://codeforces.com/blog/entry/63823) post on Codeforces explained how CHT works thorough. I'll focus on when to use CHT here.

To solve problems using CHT, you need to transform the original problem to forms like $\max\_{k} \left\\\{ a_k x + b_k \right\\\}$ ( or $\min\_{k} \left\\\{ a_k x + b_k \right\\\}$, of course). Sometimes, the problem will give you the "lines" explicity. However, sometimes the "lines" might be complicated and needs some observations. Usually this kind of problems are wrapped into a DP problem (that's why the title mentioned DP optimization). Let's go to the examples to see how it works.

Note that usually CHT can be replaced with a special kind of segment tree called Li-Chao segmemt tree. I've written a post about it ([link]({{ site.baseurl }}{% link _posts/2020-02-06-li-chao-segment-tree.md %})). Futhermore, if the problem doesn't require us to solve it online, we usually can use a technique called CDQ divide and conquer to solve it. I also have written a post about it ([link]({{ site.baseurl }}{% link _posts/2020-01-31-cdq-divide-and-conquer.md %})).

### Implementation

Two kinds of implementation are given here.

The first one is found in the KTH notebook, called "LineContainer" ([ref](https://github.com/kth-competitive-programming/kactl/blob/master/content/data-structures/LineContainer.h)).

<details><summary>code</summary>

```cpp
struct Line {
  mutable ll m, b, p;
  bool operator<(const Line& o) const { return m < o.m; }
  bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  const ll inf = LLONG_MAX;
  ll div(ll a, ll b) { // floored division
    return a / b - ((a ^ b) < 0 && a % b); 
  }
  bool isect(iterator x, iterator y) {
    if (y == end()) { x->p = inf; return false; }
    if (x->m == y->m) x->p = x->b > y->b ? inf : -inf;
    else x->p = div(y->b - x->b, x->m - y->m);
    return x->p >= y->p;
  }
  void add(ll m, ll b) {
    auto z = insert({m, b, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
  }
  ll query(ll x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.m * x + l.b;
  }
};
```

</details>

The second one is called "HullDynamic" ([ref](https://codeforces.com/blog/entry/11155?#comment-162462)).

<details><summary>code</summary>

```cpp
const ll is_query = -(1LL<<62);
struct Line {
  ll m, b;
  mutable function<const Line*()> succ;
  bool operator<(const Line& rhs) const {
    if (rhs.b != is_query) return m < rhs.m;
    const Line* s = succ();
    return s ? b - s->b < (s->m - m) * rhs.m : 0;
  }
}; // maintain upper hull for maximum
struct HullDynamic : public multiset<Line> {
  bool bad(iterator y) {
    auto z = next(y);
    if (y == begin()) {
      if (z == end()) return 0;
      return y->m == z->m && y->b <= z->b;
    }
    auto x = prev(y);
    if(z==end())return y->m==x->m&&y->b<=x->b;
    return (x->b-y->b)*(z->m-y->m)>=
            (y->b-z->b)*(y->m-x->m);
  }
  void insert_line(ll m, ll b) {
    auto y = insert({m, b});
    y->succ = [=]{return next(y)==end()?0:&*next(y);};
    if(bad(y)) {erase(y); return; }
    while(next(y)!=end()&&bad(next(y)))erase(next(y));
    while(y!=begin()&&bad(prev(y)))erase(prev(y));
  }
  ll eval(ll x) {
    auto l = *lower_bound((Line) {x, is_query});
    return l.m * x + l.b;
  }
};
```

</details>

According to [this](https://codeforces.com/blog/entry/63823?#comment-477568) comment on Codeforces, the first implementation is faster and simpler than other implementations. However, it needs `std=c++14` too work properly, while the second implementation only needs `std=c++11`.

## Example problems

### [CF631E - Product Sum](https://codeforces.com/contest/631/problem/E)
  
#### Problem description

You're given an array $a$ of length $N$. The characteristic value of the array is $C=\sum\_{i=1}^{N}a_i\cdot i$. Now, you can perform the following operation at most one: pick some element in the array, remove it,  and insert it to another (or same) position. Please calculate the maximum $C$ you can achieve after performing at most one operations.

$2\le N\le 2\times 10^5, |a_i| \le 10^6$

#### Problem analysis

Suppose we move the $i^{th}$ element to the $j^{th}$ position $(j \neq i)$. How much does the characteristic value changes? Elements before $i$ and elements after $j$ won't change, only elements $a\_{i+1}, a\_{i+2}, \dots, a_j$ and $a_i$ will change the characteristic value. How much will it change?
$$
a_i\cdot j - a_i\cdot i + \left(\sum\_{k=i+1}^{j}a_k\cdot (k \pm 1)\right) - \left(\sum\_{k=i+1}^{j}a_k \cdot k \right)= \pm\left(\sum\_{k=i+1}^{j}a_k\right) + a_i\cdot j - a_i\cdot i
$$
, where the $\pm$ sign is decided by relation bewteen $i$ and $j$. Observe that the summation term in the last equation can be handled with prefix sums ($sum_j-sum_i$), so we can calculate the cost in $O(1)$.

Let $C_0$ be the characteristic value of $a$ before any operations. Now, let's try to solve it with DP:

+ DP state : $dp_i$ represents the maximum $C$ you can achieve by moving $a_i$ to some position $1\le j\lt i$
+ DP transition : $dp_i = \max_j \left\\\{ C_0 + change(i, j) \right\\\}$, where $change(i, j)$ is mentioned above.
+ Final answer : $\max_i \left\\\{ dp_i \right\\\}$

Now, if we calculate it naively, the complexity is $O(N^2)$. However, observe that 
$$
\begin{align*}
C_0 + change(i, j) 
  &= C_0 \pm(sum_j - sum_i) + a_i \cdot j - a_i \cdot i \\\\
  &= C_0 \pm sum_j \mp sum_i + a_i \cdot j - a_i \cdot i \\\\
  &= C_0 \mp sum_i - a_i\cdot i + j \cdot a_i \pm sum_j \\\\
\end{align*}
$$
If we let $m_j=j$, $x=a_i$, and $b_j=sum_j$, then we have a line $mx\pm b$! Therefore, it can be solved with CHT and improve the time complexity to $O(N\log N)$.

#### Problem solution

Be careful that $i<j$ and $i>j$ need to be calculate seperately (at least in my implementation).

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-17-dp-opt-convex-hull-trick/cf-631e.cpp %}
```

</details>

### [CF660F - Bear and Bowling 4](https://codeforces.com/contest/660/problem/F)

#### Problem description

You are given an array $a$ with length $N$. For a subarray $a[i..j]$, we define its score as $\sum\_{k=i}^{j} (k - i + 1) \cdot a_k$. Please find the subarray with the largest score and ouput the score.

$1\le N\le 2\times 10^5, |a_i| \le 10^7$

#### Problem analysis

Similar to the previous problem, we can get a formula to calculate the score for subarray $a[i..j]$ in $O(1)$:
$$
score(i, j) = \sum\_{k=i}^{j} (k - i + 1) \cdot a_k = \left( \sum\_{k=i}^{j} k\cdot a_k \right) - (i - 1)\left( \sum\_{k=i}^{j} a_k \right)
$$
The two summation can also be calculated with prefix sums, so we can get the value in $O(1)$.

After we have the formula above, this problem is just like the previous problem:

+ DP state : $dp_i$ represents the maximum subarray ending at $i$
+ DP transition : $dp_i=\max\_{1\le j\le i} \\\{ score(j, i) \\\}$
+ Final answer : $\max\_{1\le i\le N} dp_i$

The $score(j, i)$ term can be rewritten to 
$$
\begin{align*}
score(j, i) 
  &= pre_i - pre\_{j-1} - (j-1)sum\_{i} + (j - 1)sum\_{j-1} \\\\
  &= pre_i - pre\_{j-1} - j\cdot sum\_{i} + (j - 1)sum\_{j-1} \\\\
  &= pre_i + (-j\cdot sum\_{i} + (j-1)sum\_{j-1}-pre\_{j-1}) \\\\
\end{align*}
$$
Let $m_j=-j, x=sum_i, b_j=(j-1)sum\_{j-1}-pre\_{j-1}$, then we have a line $m_jx+b_j$! So CHT can be used here.

#### Problem solution

Note that I didn't explicitly declare the dp arrays (it may get `MLE` result). See code for more details.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-17-dp-opt-convex-hull-trick/cf-660f.cpp %}
```

</details>

### [CF311B - Cats Transport](https://codeforces.com/contest/311/problem/B)

#### Problem description

Zxr960115 is owner of a large farm. He feeds $M$ cute cats and employs $P$ feeders. There's a straight road across the farm and $N$ hills along the road, numbered from $1$ to $N$ from left to right. The distance between hill $i$ and $(i - 1)$ is $d_i$ meters. The feeders live in hill $1$.

One day, the cats went out to play. Cat $i$ went on a trip to hill $h_i$, finished its trip at time $t_i$, and then waited at hill $h_i$ for a feeder. The feeders must take all the cats. Each feeder goes straightly from hill $1$ to $N$ without waiting at a hill and takes all the waiting cats at each hill away. Feeders walk at a speed of $1$ meter per unit time and are strong enough to take as many cats as they want.

Your task is to schedule the time leaving from hill $1$ for each feeder so that the sum of the waiting time of all cats is minimized. Note that the time leaving from the hill can be negetive (time travelling???).

$2\le N\le 10^5, 1\le M\le 10^5, 1\le P\le 100, 1\le d_i\lt 10^4, 1\le h_i\le N, 0\le t_i\le 10^9$

#### Problem analysis

For each cat, we can first calculate the earliest time that the feeder can leave hill $1$. Let it be $et_i$. Then $et_i=t_i+\sum\_{j=2}^{h_i} d_j$, as the feeder must walk pass hill $2, 3, \dots, h_i$ before he collect it. Then, we sort the cats according to $et_i$ from small to large. Observe that the feeder will always collect a continus segment (in the sorted array) of cats.

Now, suppose the feeder wants to collect cats from $[l, r]$ and leave hill $1$ at time $x$. Observe that $x\ge et_r$ in order to collect all cats from $[l, r]$. How long will the $i^{th}$ cat wait? It will wait exactly $x - et_i$! Therefore we can calculate the time in $O(1)$ by prefix sums.

Finally, we can write our DP equations:

+ DP state : $dp\_{i, j}$ : smallest waiting time for $j$ feeders to collect cats in $[i, l]$
+ DP transition : $dp\_{i, j} = \min\_{0\le k\lt i} \left\\\{ dp\_{k, j} + cost(k + 1, i) \right\\\}$
+ Final answer : $dp\_{N, M}$

Calculating it directly take $O(N^2K)$. However, we can transform the DP transition into lines!
$$
\begin{align*}
dp\_{k, j} + cost(k+1,i)
  &= dp\_{k, j} + \left( \sum\_{l=k+1}^{i} et_i - et_l \right) \\\\
  &= dp\_{k, j} + et_i(i-k) - \left( \sum\_{l=k+1}^{i} et_l \right) \\\\
  &= dp\_{k, j} + i\cdot et_i - k\cdot et_i - sum_i + sum_k \\\\
  &= i\cdot et_i -sum_i + (-k\cdot et_i + sum_k + dp\_{k, j}) \\\\
\end{align*}
$$
Let $m_k=-k, x=et_i, b_k=sum_k + dp\_{k, j}$, then we get a line $m_ix+b_i$. Thus the time complexity is improved to $O(NK\log N)$.

#### Problem solution

I use rolling array techniques to optimize space complexity. Also, as the slope of the lines we insert are increasing and our queries are increasing too, we don't need to implement the complete version of CHT. Only a deque is needed here. More details in code.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-17-dp-opt-convex-hull-trick/cf-311b.cpp %}
```

</details>

### [CF673E - Levels and Regions](https://codeforces.com/contest/673/problem/E)

#### Problem description

You are given a game with $N$ levels, the hardness of the $i^{th}$ level is $t_i$. Now you need to parition the $N$ levels into $K$ groups. Each groups contains some positive number of consecutive levels.

The game repeats the the following process:

1. Choose the first group with at least one non-beaten level. Denote it as $X$. (If all is beaten, you're done)
2. Suppose that $X=\left\\\{x_1, x_1 + 1, \dots, x_i,\dots\right\\\}$ and you've beat level $x_1, x_2 + 1, \dots x_i - 1$. You now have only $\frac{t\_{x_i}}{t\_{x_1} + t\_{x_1+1} + \dots + t\_{x_i}}$ chance to choose the level $x_i$. If you failed to choose $x_i$, you'll waste one hour playing some level you've beaten already. Otherwise, you'll spent one hour to beat level $x_i$.

Now, please output the minimum possible expected number of hours required to finish the game.

#### Problem analysis

First, observe that we must play the game from level $1$, $2$ until $N$. That is, we must play it in order.

Then, we need to calculate the expected time to finish (choose) some level $i$. Suppose we have $p$ probability to choose level $i$. If $x$ is the expected time to finish it, then
$$
x=p\text{ (choose level i) }+(1-p)(x+1) \text{ (fail to choose level i) }\implies x=\frac{1}{p}
$$
Or you can calculate directly ($x=1\cdot p + 2\cdot p(p-1) + 3\cdot p(p-1)^2\dots$).

Now, for a group $X=\left\\\{x_1, x_1 + 1, \dots, x_k\right\\\}$, the expected time to pass all levels in this group is 
$$
\begin{align*}
\sum\_{i=x_1}^{x_k} \frac{\sum\_{j=x_1}^{i}t_j}{t_i}
  &= \sum\_{i=x_1}^{x_k} \left( \frac{\sum\_{j=1}^{i}t_j}{t_i} - \frac{\sum\_{j=1}^{x_1-1}t_j}{t_i}\right) \\\\
  &= \sum\_{i=x_1}^{x_k} \left(\frac{\sum\_{j=1}^{i}t_j}{t_i}\right) - \sum\_{j=1}^{x_1-1}t_j\left(\frac{1}{t\_{x_1}} + \frac{1}{t\_{x_1+1}} + \dots + \frac{1}{t\_{x_k}} \right) \\\\
\end{align*}
$$
, which can be calculate in $O(1)$ with prefix sum (this one is tricky, in my opinion).

Finally, we can write DP equations and solve it with CHT:

+ DP state : $dp\_{i, j}$ represents the minimum expected value if we partition the first $i$ levels into $j$ groups
+ DP transition : $dp\_{i, j}=\max\_{0\le k\lt i} \left\\\{ dp\_{k, j - 1} + cost(k + 1, i) \right\\\}$
+ Final answer : $dp\_{N, K}$

We can use CHT to optimize it from $O(N^2K)$ to $O(NK\log N)$.

#### Problem solution

Observe that both the slope and queries are increasing.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-17-dp-opt-convex-hull-trick/cf-673e.cpp %}
```

</details>

### [CF1179D - Fedor Runs for President](https://codeforces.com/contest/1179/problem/D)

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-17-dp-opt-convex-hull-trick/cf-1179d.cpp %}
```

</details>

### [CF455E - Function](https://codeforces.com/contest/455/problem/E)

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-17-dp-opt-convex-hull-trick/cf-455e.cpp %}
```

</details>

## More problems

https://codeforces.com/blog/entry/63823
