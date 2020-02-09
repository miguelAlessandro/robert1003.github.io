---
layout: post
title: A Simple Introduction to Parallel Binary Search
tags: icpc algorithm parallel-binary-search binary-search offline-techniques

---

## Outline

+ [What is parallel binary search?](#what-is-parallel-binary-search)
+ [Example problems](#example-problems)
  + [POI XVIII MET - Meteors](#a-hrefhttpsszkopuleduplproblemsetproblem7jrcyz7lhek4nbr5zbaxpcmmsitekeystatementpoi-xviii-met---meteorsa)
  + [HDU5412 - CRB and Queries](#a-hrefhttpacmhdueducnshowproblemphppid5412hdu5412---crb-and-queriesa)
  + [More problems](#more-problems)

## What is parallel binary search?

Do binary search parallelly(of course 😃). Usually this kind of problems needs to do lots of binary search. See problems for more understanding.

## Example problems

### [POI XVIII MET - Meteors](https://szkopul.edu.pl/problemset/problem/7JrCYZ7LhEK4nBR5zbAXpcmM/site/?key=statement) 

#### Problem description

You're given $N$ people and $M$ lands, every land has an owner $o_i$, and every person has a target resource level $g_i$. Now, $K$ events will happen sequentially. Every event is described by $l_i, r_i, x_i$, meaning that lands from $l_i$ to $r_i$ will generate $x_i$ resources ($l_i$ may be greater than $r_i$ as the land is arranged as a circle), and the owner of the land will get the resource it generate. In other words, the person that have $c$ lands in $[l_i, r_i]$ will get $cx_i$ resources. For each person, please output after which event does he/she achieved his/her target resource level. If he/she can't achieve his/her target, then output "NIE"(polish for no). 

$1\le N, M, K \le 3\times 10^5, 1\le o_i, l_i, r_i\le N, 1\le g_i\le 10^9, 1\le x_i\le 10^9$

#### Problem analysis

Suppose that we only have one person to calculate, than we can do binary search on the answer and maintain the events using [BIT(range update, single query)]({{ site.baseurl }}{% link _posts/2020-01-27-fenwick-tree.md %}). The complexity is $O((K+C_i)\log K)$, where $C_i$ is the number of lands he/she owns.

If we do this $N$ times, the complexity will rise to $O(NK+M)\log K)$, which is unacceptable.

So we cannot do $N$ times binary search. This is where parallel binary search can be used.

#### Problem solution

The pseudocode of the solution is:

```
parallel_binary_search(L, R, candidates): // its called totBS in code
  if L + 1 == R:
    the answer of all people in candidates is L
    return
  mid = (L + R) / 2
  Add events in [L, mid) into BIT
  split candidates into two groups, left(done) and right(undone)
  Remove events in [L, mid) from BIT
  parallel_binary_search(L, mid, left)
  parallel_binary_search(mid, R, right)
```

The time complexity is $O((N+M+K)\log M\log K)$, and the space complexity is $O(N\log N)$. Note that the space complexity can be reduced to $O(N)$.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-05-parallel-binary-search/poi-meteors.cpp %}
```

</details>

### [HDU5412 - CRB and Queries](http://acm.hdu.edu.cn/showproblem.php?pid=5412)

#### Problem description

You are given $N$ elements $A_1, A_2, \dots, A_N$, and you need to handle $Q$ queries of two type:

+ $1\space l\space v$ : Change $A_l$ to $v$
+ $2\space l\space r\space k$ : Answer the $k^{th}$ smallest value in $A_l, A\_{l+1}, \dots, A_r$

$1\le N, Q \le 10^5, 1\le A_i, v \le 10^9, 1\le l \le r \le N, 1\le k \le r-l+1$

#### Problem analysis

Let's view every number in this problem as a four-tuple $(i, v, t, val)$, representing that after time $t$, $A_i=v$. Then, the first type of query can be transformed to:

> + $1\space l\space v$ : Create $(l, old\space A_l, t, -1)$ and $(l, v, t, 1)$

Now, a second query $(l, r, k)$ can be handled with a binary search. We can do binary search on answer. For a value $x$, we sum up the $val$ part of tuples $(i, v, t, val)$ that satisfy $l\le i\le r$, $v\le x$, $t\le \text{time of the query }$. If the sum of $val$ is smaller than $k$, then we know the answer is greater than $x$, else the answer is smaller than $x$. The time complexity is $O((N+Q)\log N\log C)$ if we use BIT to maintain interval sums.

So now we can solve each type $2$ query with one binary search. Similar to the previous problem, instead of doing $Q$ binary searches, we can do all binary searches at the same time i.e. use parallel binary search technique! The time compelxity will be $O((N + Q)\log N\log C)$, which is same as one binary search.

#### Problem solution

The pseudocode of the main part of the solution is:

```
def totBS(L, R, events, queries):
  if L + 1 == R:
    the answer to query in queries is L
    return
  mid = (L + R) / 2
  split events into l_event, r_event and queries into l_query, r_query
  clear updates in BIT
  totBS(L, mid, l_event, l_query)
  totBS(mid, R, r_event, r_query)
```
Note that the events and queries are sorted by time, and all values are discretized. Thus the time complexity is $O((N+Q)\log N\log(N+Q))$. 

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-05-parallel-binary-search/hdu-5412.cpp %}
```

</details>

### More problems

+ [BZOJ2738 - Matrix multiplication](https://www.luogu.com.cn/problem/P1527)

