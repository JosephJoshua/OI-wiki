## Introduction

Given $n$ points in the 2D plane, find a pair of points with the smallest Euclidean distance.

Below we introduce a divide and conquer algorithm with time complexity $O(n\log n)$ for this problem. It was proposed by [Franco P. Preparata](https://en.wikipedia.org/wiki/Franco_P._Preparata) in 1975, and Preparata and [Michael Ian Shamos](https://en.wikipedia.org/wiki/Michael_Ian_Shamos) proved that it is optimal in the decision tree model.

## How it works

As in a usual divide and conquer algorithm, we split the set of $n$ points into two sets $S_1, S_2$ of equal size, and keep recursing. But we run into a hard question: how do we merge? That is, how do we find the closest pair with one point in $S_1$ and the other in $S_2$? Suppose for now that merging takes $O(n)$ time. Then the total complexity is $T(n) = 2T(\frac{n}{2}) + O(n) = O(n\log n)$.

First sort all points with $x_i$ as the first key and $y_i$ as the second key, and use point $p_m (m = \lfloor \frac{n}{2} \rfloor)$ as the dividing point to split the points into $A_1,A_2$:

$$
\begin{aligned}
A_1 &= \{p_i \ \big | \ i = 0 \ldots m \}\\
A_2 &= \{p_i \ \big | \ i = m + 1 \ldots n-1 \}
\end{aligned}
$$

Recurse to find the closest pair inside each of the two sets. Let their distances be $h_1,h_2$, and let $h$ be the smaller one.

Now it's time to merge! We want to find a pair of points, one in $A_1$ and the other in $A_2$, whose distance is less than $h$. So we put every point whose x-coordinate differs from $x_m$ by less than $h$ into a set $B$:

$$
B = \{ p_i \ \big | \ \lvert x_i - x_m \rvert < h \}
$$

In the figure, line $m$ splits the points into two parts: $A_1$ on the left of $m$ and $A_2$ on the right.

Then by the rule $B = \{ p_i \ \big | \ \lvert x_i - x_m \rvert < h \}$, we get the set $B$ made of the green points. ![nearest-points1](./images/nearest-points1.png)

For each point $p_i$ in $B$, our goal is to find a point that is also in $B$ and is at distance less than $h$ from it. To avoid considering each pair twice, we only look at points with y-coordinate less than $y_i$. Clearly, for a valid point $p_j$, $y_i - y_j$ must be less than $h$. So we get a set $C(p_i)$:

$$
C(p_i) = \{ p_j\ \big |\ p_j \in B,\ y_i - h < y_j \le y_i \}
$$

Pick a point $p_i$ in $B$. By the rule $C(p_i) = \{ p_j\ \big |\ p_j \in B,\ y_i - h < y_j \le y_i \}$, we get the set $C$ made of the yellow points inside the red box.

![nearest-points2](./images/nearest-points2.png)

If we sort the points in $B$ by $y_i$, $C(p_i)$ is easy to get: it is a few consecutive points right next to $p_i$.

This gives us the merge steps:

1.  Build the set $B$.
2.  Sort the points in $B$ by $y_i$. The usual way takes $O(n\log n)$, but we can change the strategy to make it $O(n)$ (explained below).
3.  For each $p_i \in B$, consider each $p_j \in C(p_i)$; for each pair $(p_i,p_j)$, compute the distance and update the answer (the closest pair of the current set).

Note that we sort twice above. Since the point coordinates never change, the first sort only needs to be done once, before the divide and conquer starts. For the second sort, we let each recursive call return its points sorted by $y_i$; the upper level then simply merges the two sorted sets returned by the lower level.

It may still seem that the algorithm is not efficient enough: $|C(p_i)|$ could be of order $O(n)$, which would ruin the total complexity. In fact it cannot: its size is at most $7$. Here is the proof:

## Proof of the complexity

We already know that all points in $C(p_i)$ have y-coordinates in the range $(y_i-h,y_i]$, and that all points in $C(p_i)$, together with $p_i$ itself, have x-coordinates in $(x_m-h,x_m+h)$. This forms a $2h \times h$ rectangle.

Split this rectangle into two $h \times h$ squares. Ignoring $p_i$, the points in one square are $C(p_i) \cap A_1$ and the points in the other are $C(p_i) \cap A_2$, and any two points within the same square are at distance at least $h$ (because they come from the same lower-level recursive call).

Split each $h \times h$ square into four small $\frac{h}{2} \times \frac{h}{2}$ squares. Each small square contains at most $1$ point: the largest distance between two points in a small square is its diagonal, $\frac{h}{\sqrt 2}$, which is less than $h$.

![nearest-points3](./images/nearest-points3.png)

So each square has at most $4$ points, and the rectangle has at most $8$ points. Removing $p_i$ itself, $\max(C(p_i))=7$.

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/geometry/code/nearest-points/nearest-points_1.cpp"
    ```

## Generalization: minimum-perimeter triangle in the plane

The algorithm above generalizes nicely to this problem: among a given set of points, choose three points so that the sum of their pairwise distances is as small as possible.

The algorithm stays mostly the same. Each time, we try to find a triangle with a smaller perimeter than the current answer $d$: put every point whose x-coordinate differs from $x_m$ by less than $\frac{d}{2}$ into the set $B$, and try to update the answer. (The longest side of a triangle with perimeter $d$ is less than $\frac{d}{2}$.)

## Non-divide-and-conquer algorithm

Besides the divide and conquer algorithm above, there is also a non-divide-and-conquer algorithm with the same $O(n \log n)$ time complexity.

We can use a common idea for counting over a sequence: for each element, add the contribution of it paired with every element to its left. The closest pair problem can use this idea too.

Specifically, sort all points with $x_i$ as the first key and $y_i$ as the second key, and build a multiset keyed by $y_i$. For each position $i$, do the following:

1.  Delete from the set all points with $x_i - x_j \ge d$. They can no longer contribute to the answer.
2.  For every point in the set with $\lvert y_i - y_j \rvert < d$, compute its distance to $p_i$.
3.  Insert $p_i$ into the set.

Each point is inserted and deleted at most once, so insertions and deletions take $O(n \log n)$ time in total. The proof of the time complexity of the counting part is similar to the proof for the divide and conquer algorithm; try it yourself.

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/geometry/code/nearest-points/nearest-points_2.cpp"
    ```

## Expected linear-time approach

Besides the $O(n \log n)$ approaches above, there is also an algorithm with **expected** complexity $O(n)$.

First [randomly shuffle](../misc/random.md#shuffle) the points. We maintain the answer for each prefix of the points, and compute the answer for the first $i$ points from the answer for the first $i - 1$ points.

Let $s$ be the closest-pair distance among the first $i - 1$ points. Divide the plane into a grid of cells with side length $s$, and store the points in each cell (using a [hash table](../ds/hash.md)). Then check all points in the nine cells around the cell containing point $i$, and update the answer. Only $O(1)$ points need to be checked: since the closest-pair distance among the first $i - 1$ points is $s$, each cell holds at most $4$ points.

If the answer is updated during this step, rebuild the grid; otherwise don't. Among the first $i$ points, the probability that the closest pair includes point $i$ is $O\left(\frac{1}{i}\right)$, and rebuilding the grid costs $O(i)$, so the expected cost of point $i$ is $O(1)$. So for $n$ points, the algorithm runs in expected $O(n)$ time.

## Exercises

-   [UVa 10245 "The Closest Pair Problem"\[Difficulty: Low\]](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1186)
-   [SPOJ #8725 CLOPPAIR "Closest Point Pair"\[Difficulty: Low\]](https://www.spoj.com/problems/CLOPPAIR/)
-   [CODEFORCES Team Olympiad Saratov - 2011 "Minimum amount"\[Difficulty: Medium\]](http://codeforces.com/contest/120/problem/J)
-   [SPOJ #7029 CLOSEST "Closest Triple"\[Difficulty: Medium\]](https://www.spoj.com/problems/CLOSEST/)
-   [Google Code Jam 2009 Final "Min Perimeter"\[Difficulty: Medium\]](https://github.com/google/coding-competitions-archive/blob/main/codejam/2009/world_finals/min_perimeter/statement.pdf)

## References and further reading

**The divide and conquer part of this page is mainly translated from the article [Нахождение пары ближайших точек](http://e-maxx.ru/algo/nearest_points) and its English translation [Finding the nearest pair of points](https://github.com/e-maxx-eng/e-maxx-eng/blob/master/src/geometry/nearest_points.md). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**

[Zhihu column: Computational geometry - the closest pair problem](https://zhuanlan.zhihu.com/p/74905629)
