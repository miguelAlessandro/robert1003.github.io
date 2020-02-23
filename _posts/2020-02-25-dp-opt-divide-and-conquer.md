---
layout: post
title: DP optimization - Divide and Conquer Optimization
tags: icpc algorithm dp dp-optimization divide-and-conquer under-construction

---

## Outline

+ [Introduction](#introduction)
+ [Example problems](#example-problems)
  + [Atcoder ARC067D - Yakiniku Restaurants](#a-hrefhttpsatcoderjpcontestsarc067tasksarc067datcoder-arc067d---yakiniku-restaurantsa)
  + [CF321E - Ciel and Gondolas](#a-hrefhttpscodeforcescomcontest321problemecf321e---ciel-and-gondolasa)
  + [CF868F - Yet Another Minimization Problem](#a-hrefhttpscodeforcescomcontest868problemfcf868f---yet-another-minimization-problema)
+ [More problems](#more-problems)

## Introduction

## Example problems

### [Atcoder ARC067D - Yakiniku Restaurants](https://atcoder.jp/contests/arc067/tasks/arc067_d)

#### Problem description

There're $N$ restaurants along a street. The restaurants are numbered $1$ through $N$ from west to east, and the distance between restaurant $i$ and $i+1$ is $A_i$.

Joisino has $M$ tickets, numbered $1$ to $M$. Every restaurant offers meals in exchange for these tickets. Restaurant $i$ offers a meal of deliciousness $B\_{i, j}$ in exchange for ticket $j$. Each ticket can only be used once, but any number of tickets can be used at a restaurant.

Joisino wants to have $M$ barbecue meals by starting from a restaurant of her choice, then repeatedly traveling to another barbecue restaurant and using unused tickets at the restaurant at her current location. Her eventual happiness is calculated by the following formula: "(The total deliciousness of the meals eaten) - (The total distance traveled)". Find her maximum possible eventual happiness.

$2\le N\le 5\times 10^3, 1\le M\le 200, 1\le N_i\le 10^9, 1\le B\_{i, j} \le 10^9$

#### Problem analysis
#### Problem solution

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-25-dp-opt-divide-and-conquer/atcoder-arc067d.cpp %}
```

</details>

### [CF321E - Ciel and Gondolas](https://codeforces.com/contest/321/problem/E)

#### Problem description

There're $N$ people numbered from $1$ to $N$ and $K$ cars. Today, they want to go out driving those $K$ cars, so they need to split them into $K$ groups. For any two people $i, j, i\neq j$, we know how much they hate each other, which is given as $u\_{ij}$. The level of hate of a group $G$ is calculated as following:
$$
\sum\_{i, j\in G, i\lt j} u\_{ij}
$$
Now, please find a way to split those $N$ peoples into $K$ groups satisfying 

+ Each part is consisted of people with consecutive indexes 
+ The total sum of level of hate of each group is minimized

$1\le N\le 4000, 1\le K\le \min(N, 800), 0\le u\_{ij}\le 9, u\_{ij}=u\_{ji}, u\_{ii}=0$

#### Problem analysis
#### Problem solution

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-25-dp-opt-divide-and-conquer/cf-321e.cpp %}
```

</details>

### [CF868F - Yet Another Minimization Problem](https://codeforces.com/contest/868/problem/F)

#### Problem description

You are given an array of $N$ integers $a_1, a_2, \dots a_N$. The cost of a subsegment is the number of unordered pairs of distinct indices within the subsegment that contain equal elements. Split the given array into $K$ non-intersecting non-empty subsegments so that the sum of their costs is minimum possible. Each element should be present in exactly one subsegment.

$2\le N\le 10^5, 2\le K\le \min(N, 20), 1\le a_i\le N$

#### Problem analysis
#### Problem solution

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-25-dp-opt-divide-and-conquer/cf-868f.cpp %}
```

</details>

## More problems

+ [CF1101F - Trucks and Cities](https://codeforces.com/problemset/problem/1101/F)
+ [BZOJ5125 - Little Q's Bookshelf](https://www.lydsy.com/JudgeOnline/problem.php?id=5125)
+ [Codechef - Chef and Bitwise OR Operation](https://www.codechef.com/problems/CHEFAOR)
+ [UVa12524 - Arranging Heaps](https://onlinejudge.org/external/125/12524.pdf)
