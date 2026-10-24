author: Marcythm, hsfzLZH1, abc1763613206, greyqz, Ir1d, billchenchina, Chrogeek, Enter-tainer, StudyingFather, MrFoodinChina, luoguyuntianming, sshwy, wood3

## Introductory example problem

???+ note "[HNOI2008 Toy Packing](https://loj.ac/problem/10188)"
    There are $n$ toys in a row, and toy $i$ has value $c_i$. Split these $n$ toys into several segments. The cost of a segment $[l,r]$ is $(r-l+\sum_{i=l}^r c_i-L)^2$, where $L$ is a constant. Find the minimum total cost of the split.
    
    $1\le n\le 5\times 10^4, 1\le L, c_i\le 10^7$.

### Naive DP approach

Let $f_i$ be the minimum cost of splitting the first $i$ items into segments.

State transition equation: $f_i=\min_{j<i}\{f_j+(i-(j+1)+pre_i-pre_j-L)^2\}=\min_{j<i}\{f_j+(pre_i-pre_j+i-j-1-L)^2\}$.

Here $pre_i$ is the sum of the first $i$ numbers, that is, $\sum_{j=1}^i c_j$.

The time complexity of this approach is $O(n^2)$, which is too slow for this problem.

### Optimization

Let's simplify the transition equation above: let $s_i=pre_i+i,L'=L+1$. Then $f_i=\min_{j<i}\{f_j+(s_i-s_j-L')^2\}$.

Moving the terms that do not depend on $j$ outside, we get

$$
f_i - (s_i-L')^2=\min_{j<i}\{f_j+s_j^2 + 2s_j(L'-s_i) \} 
$$

Consider the slope-intercept form of a linear function, $y=kx+b$. Rearranging gives $b=y-kx$. We express the information that depends only on $j$ as $y$, the information that depends on both $i$ and $j$ as $kx$, and the quantity to minimize (which depends on $i$) as $b$, the intercept. Specifically, let

$$
\begin{aligned}
x_j&=s_j\\
y_j&=f_j+s_j^2\\
k_i&=-2(L'-s_i)\\
b_i&=f_i-(s_i-L')^2\\
\end{aligned}
$$

Then the transition becomes $b_i = \min_{j<i}\{ y_j-k_ix_j \}$. If we view $(x_j,y_j)$ as points in the plane, then $k_i$ is the slope of a line, and $b_i$ is the intercept of the line with slope $k_i$ passing through $(x_j,y_j)$. The problem becomes: choose a suitable $j$ ($1\le j<i$) to minimize the intercept of the line.

![slope\_optimization](../images/optimization.svg)

As shown in the figure, we move this line with slope $k_i$ upward from below until it hits some point $(x_p,y_p)$. Then $b_i=y_p-k_ix_p$, and this is the minimum value of $b_i$. After computing $f_i$, we add the point $(x_i,y_i)$ to the point set as a new DP decision. So how do we maintain the point set?

It is easy to see that any point that can give the minimum $b_i$ must lie on the lower convex hull. So when looking for $p$ we do not need to enumerate all $i-1$ points; we only need to consider points on the hull. In this problem, $k_i$ increases with $i$, so we can maintain the hull with a monotonic queue.

Specifically, let $K(a,b)$ be the slope of the line through $(x_a,y_a)$ and $(x_b,y_b)$. Consider the queue $q_l,q_{l+1},\ldots,q_r$, which stores the points on the lower convex hull. That is, for $l<i<r$, $K(q_{i-1},q_i) < K(q_i,q_{i+1})$ always holds.

We maintain a pointer $e$ to compute the minimum of $b_i$. We need to find an $e$ with $K(q_{e-1},q_e)\le k_i< K(q_e,q_{e+1})$ (the cases $e=l$ and $e=r$ need special handling). Then $p=q_e$, that is, $q_e$ is the optimal decision point for $i$. Since $k_i$ is monotonically increasing, $e$ moves an amortized $O(1)$ times.

When inserting a point $(x_i,y_i)$, we check whether $K(q_{r-1},q_r)<K(q_r,i)$. If the inequality does not hold, pop $q_r$, and repeat until it holds. Then push $i$ onto the back of $q$.

This reduces the complexity of the DP to $O(n)$.

To summarize the algorithm for this template convex hull trick problem:

1.  Push the initial state into the queue.
2.  Each time, use a line $f(i)$ related to $i$ to touch the maintained convex hull, find the optimal decision, and update $dp_i$.
3.  Add the state $dp_i$. If some state (that is, a point on the hull) is no longer on the hull after $dp_i$ is added, remove it before adding $dp_i$.

Next we introduce advanced uses of the convex hull trick: combining it with binary search, divide and conquer, data structures and so on, to handle DP equations with weaker properties (missing some monotonicity).

## DP optimization with binary search/CDQ/balanced trees

When we look for the optimal decision at point $i$, we use a line $f(i)$ related to $i$ to touch the convex hull we maintain. The point it touches is the optimal decision.

In the example above, the slope of the line changes monotonically with $i$, but in some problems the slope is not monotonic. Then we need to keep every point on the convex hull, and each time touch the hull with the current line. This can be done with binary search, because the slopes between adjacent points on the hull are monotonic.

???+ note "Toy Packing, modified"
    There are $n$ toys in a row, and toy $i$ has value $c_i$. Split these $n$ toys into several segments. The cost of a segment $[l,r]$ is $(r-l+\sum_{i=l}^r c_i-L)^2$, where $L$ is a constant. Find the minimum total cost of the split.
    
    $1\le n\le 5\times 10^4,1\le L\le 10^7,-10^7\le c_i\le 10^7$.

The only difference from "Toy Packing" is that toy values can be negative. Following the same idea, let $f_i$ be the minimum cost of splitting the first $i$ items into segments.

State transition equation: $f_i=\min_{j<i}\{f_j+(pre_i-pre_j+i-j-1-L)^2\}$.

Here $pre_i = \sum_{j=1}^i c_j$.

Apply the same transformation to the equation:

$$
f_i - (s_i-L')^2=\min_{j<i}\{f_j+s_j^2 + 2s_j(L'-s_i) \} 
$$

But now two conditions no longer hold:

1.  The slope of the line is no longer monotonic;
2.  The x-coordinates of the decision points added each time are no longer monotonic.

We still think about maintaining the convex hull.

When looking for the optimal decision point, that is, touching the hull with a line, we replace "take the front of the monotonic queue" with "binary search on the hull". We binary search for the hull edge whose slope is closest to the slope of the line, which gives the optimal decision.

When adding a decision point, that is, adding a point to the hull, there are two ways to maintain the hull.

The first way is to maintain the hull directly with a balanced binary search tree. Then the binary search for the decision point becomes a binary search on the tree, and inserting a decision point becomes inserting a node into the tree and deleting the points that get kicked off the hull. This idea is simple but tedious to implement.

Below we introduce an approach based on [CDQ divide and conquer](../../misc/cdq-divide.md).

Let $\text{CDQ}(l,r)$ mean computing $f_i,i\in [l,r]$. Consider $\text{CDQ}(1,n)$:

-   First call $\text{CDQ}(1,mid)$ to compute $f_i,i\in[1,mid]$. Then build the convex hull of the decision points in $[1,mid]$, and use this hull to update $f_i,i\in [mid+1,n]$. At this point the set of decision points is fixed, unlike before where we added decision points while computing DP values. So we can first sort the $f_i$ with $i \in [mid+1,n]$ by the slope $k_i$ of their lines, and then use a monotonic queue to compute the DP values. Alternatively, we can binary search on the static hull to compute them.

-   For each point in $[mid+1,n]$, if its optimal decision lies in $[1,mid]$, it will be updated to the optimal answer in this step. After this step, all points in $[1,mid]$ have done their job; whether they stay in the hull no longer affects later updates. So we can discard the decision points of this range and use $\text{CDQ}(mid+1,n)$ to solve the rest of the right half.

The time complexity is $O(n\log^2 n)$.

Comparing "Toy Packing" and "Toy Packing, modified", we can draw two conclusions:

-   Binary search/CDQ/balanced trees and so on can speed up computing a DP equation and lower the complexity to some degree, but they cannot change the equation itself.
-   The properties of a DP equation depend on the characteristics of the data, but the DP equation itself depends on the mathematical model of the problem.

## Summary

The convex hull trick needs to be applied flexibly. Its core idea is to turn an optimization problem into a problem of finding the extreme intercept related to a convex hull in the plane. For equations with weaker properties, data structures are sometimes needed; handle those case by case.

## Exercises

-   [SDOI2016 Journey](https://loj.ac/problem/2035)
-   [ZJOI2007 Warehouse Construction](https://loj.ac/problem/10189)
-   [APIO2010 Commando](https://loj.ac/problem/10190)
-   [JSOI2011 Lemons](https://www.luogu.com.cn/problem/P5504)
-   [Codeforces 311B Cats Transport](http://codeforces.com/problemset/problem/311/B)
-   [NOI2007 Currency Exchange](https://loj.ac/problem/2353)
-   [NOI2019 Route Home](https://loj.ac/problem/3156)
-   [NOI2016 The King's Drinking Water](https://uoj.ac/problem/223)
-   [NOI2014 Ticket Purchase](https://uoj.ac/problem/7)
