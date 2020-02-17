---
layout: post
title: DP optimization - monotone-queue optimization
tags: icpc algorithm dp dp-optimization monotone-queue

---

## Outline

+ [Monotone Queue & Relation with DP](#monotone-queue)
+ [Relation with DP]()
+ [Example problems](#example-problems)
+ [More problems](#more-problems)

## Monotone Queue & Relation with DP

To understand what it is, we first look at a problem:

> #### Maximum value in a sliding window
> Given an sequence $A_1, A_2, \dots, A_N$ and a integer $K$, for every $1\le i\le N - K + 1$, find $\min\_{i\le j \le i + k - 1} A_j$.

This can be solved with monotone queue in $O(N)$ time complexity.
This [link](https://www.nayuki.io/page/sliding-window-minimum-maximum-algorithm) explained it thoroughly.
My implementation is given below:

```cpp
deque<pair<int, int> > dq; // <id, value>
for(int i = 1, j = 1 ; i <= n - k + 1 ; ++i) {
  // pop : remove expired elements
  while(!dq.empty() && dq.front().first <= i - k) dq.pop_front();
  // push : add new element
  while(j <= n && j <= i + k - 1) {
    // We want to put A_j into the deque
    // First, remove elements that is useless
    while(!dq.empty() && A[j] <= dq.back().second) dq.pop_back();
    // Then, put it in
    dq.push_back({j, A[j]}), ++j;
  }
  // value of min { A_i, A_{i + 1}, ..., A_{i + k - 1} }
  cout << dq.front().second << '\n';
}
```

So what's the relation between Monotone queue and DP ? Sometimes calculating DP you may encounter similar problems above i.e. maximum / minimum value for consecutive $k$ elements. See example problems below to understand more.


## Example problems

### [CF1077F - Pictures with Kittens](https://codeforces.com/contest/1077/problem/F2)

#### Problem description

You're given a sequence of number $A_1, A_2, \dots, A_N$, please choose exactly $X$ numbers out of them. Moreover, if the index you chose is $x_1, x_2, \dots, x_X, x_1 \lt x_2 \lt  \dots x_X$, they need to satisfy $x 3, \dots, X$. In other words, at least one number in every $K$ consecutive number must been chosen.

$1\le K, X \le N\le 5000, 1\le A_i \le 10^9$

#### Problem analysis

+ DP state : $dp\_{i, j}$ represents maximum value if you choose $j$ from $1, 2, \dots, i$ <br>
+ DP transition : $dp\_{i, j} = \max \left\\\{ dp\_{i-1, j-1}, dp\_{i-2, j-1}, \dots, dp\_{i-k, j-1} \right\\\} = \max\_{1\le k\le K} dp\_{i - k, j - 1}$ <br>
+ Final answer : $\max \left\\\{ dp\_{N-k+1, x}, dp\_{N-k+2, x}, \dots, dp\_{N, x} \right\\\}$

If we calculate it directly the time complexity will be $O(NK\times K) = O(NK^2)$, which is unacceptable. <br>
However, if we look more carefully, we may observe that DP transition is exactly the problem above (maximum value for consecutive $K$ elements) ! Therefore, the time complexity can be improved to $O(NK)$.

#### Problem solution

Remember to initialize dp values to $-\infty$.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-16-dp-opt-monotone-queue/cf-1077f.cpp %} 
```

</details>

### [CF445A - Boredom](https://codeforces.com/contest/455/problem/A)

#### Problem description

Given a sequence $A$ consisting of $N$ integers. The player can make several steps. In a single step he can choose an element of the sequence (let's denote it $A_k$) and delete it, at that all elements equal to $A_k + 1$ and $A_k - 1$ also must be deleted from the sequence. That step brings $A_k$ points to the player.

Now, calculate the maximum point a player can get on $A$ if arbitrary steps can be made.

$1\le N\le 10^5, 1\le A_i \le 10^5$

#### Problem analysis

First, if at a step we choose $A_i$ to delete it, then all other $j$ with $A_j = A_i$ will also be chosen as there's no cost choosing them (choosing $A_i$ will remove all elements equal to $A_i + 1$ and $A_i - 1$). Base on this observation, we can create a sequence $cnt_i$ represents how many time $i$ appears in $A$. 

Another observation is that you always start deleting elements from the largest or the smallest. This is because deleting the largest element (or smallest) will minimize the numbers being removed (as $largest + 1$ doesn't exist). 

Base on the two observations above, we can write our dp equations:

+ DP state : $dp_i$ represents maximum point you can achieve considering numbers from $1$ to $i$ <br>
+ DP transition : 
$$
dp_i=\max
\begin{cases}
dp\_{i-1} &, \text{ don't choose } i \\\\
cnt_i\times i + \max\_{j\lt i-1} \left\\\{ dp_j \right\\\} &, \text{ choose } i \text{, so } i-1 \text{ can't be chosen } \\\\
\end{cases}
$$
+ Final answer : $\max\_{1\le i\le C} \left\\\{ dp_i \right\\\}$, where $C$ is the range of $A_i$

Similarly, the $\max$ term in the DP transition is exactly the problem mentioned in the beginning.

#### Problem solution

Note that the time complexity is $O(C)$, which can be optimized to $O(N)$ (My implementation is $O(C)$, though).

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-16-dp-opt-monotone-queue/cf-445a.cpp %} 
```

</details>

### [CF372C - Watching Fireworks is Fun](https://codeforces.com/contest/372/problem/C)

#### Problem description

$M$ fireworks are going to be launched on a line with length $N$. The $i^{th}$ firework will be launched at time $t_i$, position $a_i$. If you're at $x$ when firework $i$ launched, then you gain happiness value $b_i - |a_i - x|$ (might be negetive).

Now, you can move $d$ unit every second and choose arbitrary starting point between $1$ and $N$. Please maximize your happiness value (note that you cannot move to position $x$ if $x < 1$ or $x > N$).

$1\le N\le 1.5\times 10^5, 1\le M\le 300, 1\le d\le N, 1\le a_i\le N, 1\le b_i, t_i\le 10^9,  t_i\le t\_{i+1}$

#### Problem analysis

+ DP state : $dp\_{i, j}$ represents maximum happiness value after watching fireworks $1\sim i$ and standing at $j$
+ DP transition : $dp\_{i, j}=\max\_{|k-j|\le d(t_i-t\_{i-1})} dp\_{i-1, k} + b_i - |a_i - j|$. In other words, we considered all possible position aftre watching fireworks $i-1$.
+ Final answer : $\max\_{1\le i\le N} dp\_{M, i}$

If we calculate DP transition directly, the time complexity will be $O(NM\times N)=O(N^2M)$, which is too slow. How can we optimize it ?

Observe that $|k-j|\le d(t_i-t\_{i-1})$ can be rewritten to: 
$$
\max\left\\\{1, j - d(t_i-t\_{i-1})\right\\\} \le k \le \min\left\\\{N, j + d(t_i-t\_{i-1})\right\\\}
$$
which is exactly maximum value in a sliding window ! Thus, the time complexity can be optimized to $O(NM)$.

#### Problem solution

Note that we can't declare $dp[150000][300]$ directly. Rolling array techniques is needed to optimize the space complexity to $O(N)$. Details in code.

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-16-dp-opt-monotone-queue/cf-372c.cpp %}
```

</details>

### [CF939F - Cutlet](https://codeforces.com/contest/939/problem/F)

#### Problem description

You're given a steak. Your mission is to cook each side exactly $N$ minutes. However, you can't flip at anytime you want. You can only flip in $K$ time intervals $[l_i, r_i]$. Now, please calculate the minimum number of flips to achieve the goal or determine it is impossible to do it.

$1\le N\le 10^5, 1\le K\le 100, 1\le l_i\le r_i\le 2N$

#### Problem analysis

+ DP state : $dp\_{i, j}$ represents the minimum number of flipes if in the first $i$ minutes, the side which **isn't cooked right now** has already been cooked $j$ minutes.
+ DP transition : 
$$
dp\_{i, j}=\min
\begin{cases}
dp\_{i-1, j} &, \text{ don't flip at minute} i \\\\
dp\_{i-1, i-j-1}&, \text{ (if we can) flip at minute } i \\\\
\end{cases}
$$
+ Final answer : $dp\_{2N, N}$

Is this solution feasible ? We have $O(N^2)$ states and the transition takes $O(1)$, so the time complexity is $O(N^2)\implies$ Not feasible QQ. How do we improve it ?

Observe that there are at most $100$ intervals that we can flip, and in every interval we will either filp one or two times or not flip at all. Therefore, we can redesign of DP:

+ DP state : $dp\_{i, j}$ represents the minimum number of flipes if in the **first $r_i$ minutes**, the side which **isn't cooked right now** has already been cooked $j$ minutes.
+ DP transition : 
$$
dp\_{i, j}=\min
\begin{cases}
dp\_{i-1, j} &, \text{ don't flip in } [l_i, r_i] \\\\
\min\_{0\le k\le r_i-l_i}+1\left\\\{ dp\_{i-1, r_i-j-k}\right\\\} &, \text{ flip once at time } l_i+k\\\\
\min\_{0\le k\le r_i-l_i}+2\left\\\{ dp\_{i-1, j-k}\right\\\} &, \text{ flip twice, and the time between the two flip is } k\\\\
\end{cases}
$$
+ Final answer : $dp\_{M, N}$

Now the time complexity is $O(NK^2)$, and can be reduced to $O(NK)$ with techniques mentioned in the beginning (the range $\min$ parts in the transition).


#### Problem solution

Like the previous problem, I used rolling array techniques to reduce space complexity. Also, be careful when calculating the indexes (I debugged for like two hours...).

<details><summary>code</summary>

```cpp
{% include code-snippets/2020-02-16-dp-opt-monotone-queue/cf-939f.cpp %}
```

</details>

## More problems

+ [POJ1821 - Fence](http://poj.org/problem?id=1821)
+ [Atcoder abc146 F - Sugoroku](https://atcoder.jp/contests/abc146/tasks/abc146_f)
