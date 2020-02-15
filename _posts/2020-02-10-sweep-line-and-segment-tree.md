---
layout: post
title: Sweep Line and Segment Trees
tags: icpc algorithm segment-tree geometry sweep-line

---

## Outline

+ [What is this post about?](#what-is-this-post-about)
+ [Example problems](#example-problems)
  + [TIOJ1224 - Rectangle union area](#a-hrefhttpstiojcktpedutwproblems1224tioj1224---rectangle-union-areaa-chinese)
  + [HDU1255 - Rectangle union area 2](#a-hrefhttpacmhdueducnshowproblemphppid1255hdu1255---rectangle-union-area-2a-chinese)
  + [IOI '98 - Picture](#a-hrefhttpswcipegcomproblemioi9821ioi-98---picturea)
+ [More problems](#more-problems)

## What is this post about?

Demonstrate some well-known usage of sweep line with segment tree. The most classic type of problem that this technique can solve is rectangle union area/perimeter.

## Example problems

### [TIOJ1224 - Rectangle union area](https://tioj.ck.tp.edu.tw/problems/1224) (Chinese)

#### Problem description

Given $N$ rectangles described by $L_i, R_i, D_i, U_i$ , representing that the $i^{th}$ bottom-left corner of the rectangle is $(L_i, D_i)$ , and the top-right corner of the rectangle is $(R_i, U_i)$ , please calculate the union area of those $N$ rectangles.

$1\le N\le 10^5, 0\le L_i < R_i \le 10^6, 0\le D_i < U_i \le 10^6$

#### Problem analysis

A classic type of problem that sweep line + segment tree can solve. Let see the algorithm by example.

<details><summary>example</summary>

Suppose in the beginning, we're given these rectangles:

<div style="text-align:center"><img style="width:85%" src="/assets/images/sweep-line-and-segment-tree/sweep-line-0.png" /></div>
<br>

Now, we sweep a line starting from $y=0$.

<div style="text-align:center"><img style="width:85%" src="/assets/images/sweep-line-and-segment-tree/sweep-line-1.png" /></div>
<br>

We'll stop at $y=2$, as we met a bottom edge of some rectangle. We add $1$ to $sum[4, 5, 6, 7]$. Then, we continue sweeping.

<div style="text-align:center"><img style="width:85%" src="/assets/images/sweep-line-and-segment-tree/sweep-line-2.png" /></div>
<br>

We stop at $y=3$. This time, we first update the answer by adding the area we've passed from the previous stopped point i.e. $y=2$. As we can see in the picture, only $sum[4, 5, 6, 7]$ have value greater than $0$. Therefore answer is updated with $4 \times (3 - 2)=4$. Then, we add $1$ to $sum[11, 12, 13, 14]$, as the edge we met is a bottom edge.

<div style="text-align:center"><img style="width:85%" src="/assets/images/sweep-line-and-segment-tree/sweep-line-3.png" /></div>
<br>

Stop at $y=4$. Update ans with $8\times (4-3)=8$ ($8$ values greater than $0$). Add $1$ to $sum[6, 7, 8, 9]$.

<div style="text-align:center"><img style="width:85%" src="/assets/images/sweep-line-and-segment-tree/sweep-line-4.png" /></div>
<br>

Stop at $y=5$. Update ans with $10\times (5-4)=10$ ($10$ values greater than $0$). As we met a **upper** edge, add $-1$ to $sum[4, 5, 6, 7]$.

<div style="text-align:center"><img style="width:85%" src="/assets/images/sweep-line-and-segment-tree/sweep-line-5.png" /></div>
<br>

Stop at $y=6$. Update ans with $8\times (6-5)=8$ ($8$ values greater than $0$). Add $1$ to $sum[2, 3, 4, 5, 6, 7]$ and $-1$ to $sum[11, 12, 13, 14]$.

<div style="text-align:center"><img style="width:85%" src="/assets/images/sweep-line-and-segment-tree/sweep-line-6.png" /></div>
<br>

Stop at $y=7$. Update ans with $8\times (7-6)=8$ ($8$ values greater than $0$). Add $-1$ to $sum[6, 7, 8, 9]$.

<div style="text-align:center"><img style="width:85%" src="/assets/images/sweep-line-and-segment-tree/sweep-line-7.png" /></div>
<br>

Stop at $y=9$. Update ans with $6\times (9-7)=12$ ($6$ values greater than $0$). Add $-1$ to $sum[2, 3, 4, 5, 6, 7]$.

<div style="text-align:center"><img style="width:85%" src="/assets/images/sweep-line-and-segment-tree/sweep-line-8.png" /></div>
<br>

So the final answer is $50$.

</details>

#### Problem solution

For implementation, we need to maintain a segment tree that can tell us how many values are greater than $0$. How do we do this?

For every node is the segment tree, we maintain two values: $tag$ and $sum$, representing "values added in that interval"(lazy tag) and "numbers of element greater than $0$" respectively. The update rule is given as following:

The time complexity is $O(N\log C)$.

```cpp
void pull(int l, int r, int o) {
  // tag[o] > 0 means that all elements in intervel [l, r) is greater than 0
  if(tag[o]) sum[o] = r - l; 
  // tag[o] = 0 means some elements in this intervel is zero;
  // thus, we need to get the value from lson and rson
  else sum[o] = (l + 1 == r ? 0 : sum[o * 2 + 1] + sum[o * 2 + 2]);
}
```

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-10-sweep-line-and-segment-tree/tioj-1224.cpp %}
```

</details>

### [HDU1255 - Rectangle union area 2](http://acm.hdu.edu.cn/showproblem.php?pid=1255) (Chinese)

#### Problem description

Given $N$ rectangles where every rectangle is described by $(X_1, Y_1, X_2, Y_2)$(floating point numbers), meaning that the top-left corner of the rectangle is $(X_1, Y_1)$ and the bottom-right of the rectangle is $(X_2, Y_2)$, please calculate the total area that has been covered by at least two different rectangles. 

There are $T$ testcases in a testdata.

$1\le T \le 100, 1\le N\le 10^3, 0\le X_1, Y_1, X_2, Y_2 \le 10^5$

#### Problem analysis

Similar to the previous problem, we can sweep a line and maintain some values in the segment tree to solve it. However, two values are not enough in this problem. Therefore, we use three values(?) to solve it.

#### Problem solution

For every node is the segment tree, we maintain two values: $tag$, $sum$ and $sum2$, representing "values added in that interval"(lazy tag), "number of element greater than $0$" and "number of element greater than $1$" respectively. The update rule is given as following:

```cpp
void pull(int l, int r, int o) {
  int lson = o * 2 + 1, rson = o * 2 + 2;
  // Update sum: This part is same as the previous problem
  if(tag[o]) sum[o] = x[r] - x[l];
  else sum[o] = (l + 1 == r ? 0 : sum[lson] + sum[rson]);
  // Update sum2
  // tag[o] > 1 means that all elements in intervel [l, r) is greater than 1
  if(tag[o] > 1) sum2[o] = x[r] - x[l];
  else if(l + 1 == r) sum2[o] = 0; // special case
  // tag[o] = 1 means that all elements in intervel [l, r) is greater than 0, 
  // but some elements may be 1; thus, sum2[o] = sum[lson] + sum[rson] 
  // as if a element is added in lson/rson and added in this node, then its sum is greater than 1
  else if(tag[o]) sum2[o] = sum[lson] + sum[rson];
  // similarly, tag[o] = 0 means that we need to get the value from sum2[lson] and sum2[rson]
  else sum2[o] = sum2[lson] + sum2[rson];
}
```

The time complexity is $O(N\log C)$.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-10-sweep-line-and-segment-tree/hdu-1255.cpp %}
```

</details>

### [IOI '98 - Picture](https://wcipeg.com/problem/ioi9821)

#### Problem description

Given $N$ rectangles where every rectangle is described by $(X_1, Y_1, X_2, Y_2)$, meaning that the bottom-left corner of the rectangle is $(X_1, Y_1)$ and the top-right of the rectangle is $(X_2, Y_2)$, please calculate the union perimeter of those $N$ rectangles.

$0\le N\le 5\times 10^3, -10^4\le X_1, Y_1, X_2, Y_2\le 10^4$

#### Problem analysis

Still, we sweep over the rectangles like above. However, this time we need to maintain a different information: number of (not connected) segments and total lenght of those segments. The second one same as above, but can the first one be done with segment trees? 

Yes! (of course otherwise I won't mention this problem here :p). We maintain several informations including $lp$ (position of the leftmost element that's greater than $0$), $rp$ (position of the rightmost element that's greater than $0$). Then, we're good to go.

#### Problem solution

These are Informations needed to maintain:
+ $sum$ : number of segments in this interval
+ $len$ : number of elements greater than $0$ in this interval
+ $tag$ : lazy tag
+ $lp$ : position of the leftmost element that's greater than $0$
+ $rp$ : position of the rightmost element that's greater than $0$

The update rules are:
```cpp
void pull(int l, int r, int o) {
  // tag[o] > 0 means that all elements in this interval is > 0
  if(tag[o]) sum[o] = lp[o] = rp[o] = 1, len[o] = r - l;
  else if(l + 1 == r) sum[o] = len[o] = lp[o] = rp[o] = 0;
  else {
    int lson = o * 2 + 1, rson = o * 2 + 2;
    sum[o] = sum[lson] + sum[rson] - (rp[lson] && lp[rson]);
    len[o] = len[lson] + len[rson];
    lp[o] = lp[lson], rp[o] = rp[rson];
  }
}
```

The time complexity is again $O(N\log C)$.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-10-sweep-line-and-segment-tree/ioi-picture.cpp %}
```

</details>

## More problems

+ [HDU1542 - Atlantis](http://acm.hdu.edu.cn/showproblem.php?pid=1542)
+ [HDU3265 - Posters](http://acm.hdu.edu.cn/showproblem.php?pid=3265)
+ [UVa12647 - Balloon](https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=4376)
