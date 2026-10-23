## Introduction

Prefix sums and difference arrays are common techniques in competitive programming. Prefix sums let you quickly find the sum of a range, and difference arrays let you efficiently apply updates to a range.

???+ tip "Convention"
    To keep things simple, this article assumes that the array $\{a_i\}$ is indexed from $1$, and we also define $a_0 = 0$.

## Prefix sums

You can think of a prefix sum simply as "the sum of the first $n$ terms of a sequence". It is an important kind of preprocessing.

### 1D prefix sums

Suppose you have a sequence $\{a_i\}$ of length $n$ and need to answer many queries asking for the sum of the numbers in a range $[l,r]$. This is a good time to use prefix sums. The prefix sums of the sequence are

$$
S_{i} = \sum_{j=1}^i a_j.
$$

They can be computed one by one using the recurrence

$$
S_0 = 0,~ S_i = S_{i-1} + a_i
$$

To answer a query for the sum over the range $[l,r]$, just compute the difference

$$
S([l,r]) = S_r - S_{l-1}.
$$

In this way, after $O(n)$ preprocessing, each range sum query takes only $O(1)$ time.

???+ example "Reference implementation"
    === "C++"
        ```cpp
        --8<-- "docs/basic/code/prefix-sum/prefix-sum_1.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/basic/code/prefix-sum/prefix-sum_1.py:core"
        ```

The C++ standard library provides a prefix sum function, [`std::partial_sum`](https://zh.cppreference.com/w/cpp/algorithm/partial_sum), defined in the header `<numeric>`. Since C++17, the standard library also provides [`std::inclusive_scan`](https://zh.cppreference.com/w/cpp/algorithm/inclusive_scan), which does the same job and is also defined in `<numeric>`.

### 2D and higher-dimensional prefix sums

Extending 1D prefix sums to more dimensions gives multidimensional prefix sums. There are two common ways to compute them.

#### Using the inclusion-exclusion principle

This method is mostly used for 2D prefix sums. Given a 2D array $A$ of size $m\times n$, we want its prefix sums $S$. Then $S$ is also a 2D array of size $m\times n$, where

$$
S_{i,j} = \sum_{i'\le i}\sum_{j'\le j}A_{i',j'}.
$$

Just like in the 1D case, we would like to compute $S_{i,j}$ from $S_{i-1,j}$ or $S_{i,j-1}$, so that we don't have to re-add all the earlier terms. However, if we simply add $S_{i-1,j}$ and $S_{i,j-1}$ and then add $A_{i,j}$, the overlapping part $S_{i-1,j-1}$ is counted twice, so we have to subtract it once. This is the [inclusion-exclusion principle](../math/combinatorics/inclusion-exclusion-principle.md). It gives the following recurrence:

$$
S_{i,j} = A_{i,j} + S_{i-1,j} + S_{i,j-1} - S_{i-1,j-1}. 
$$

To implement it, just loop over every $(i,j)$ and apply the formula.

???+ note "Example"
    Let's look at a concrete example.
    
    ![2D prefix sum example](./images/prefix-sum-2d.svg)
    
    Here, $S$ is the prefix sum of matrix $A$. By definition, $S_{3,3}$ is the sum of the submatrix inside the dashed box in the left picture. Also, $S_{3,2}$ is the sum of the blue submatrix, $S_{2,3}$ is the sum of the red submatrix, and their overlap sums to $S_{2,2}$. So if we just add $S_{3,2}$ and $S_{2,3}$, we count $S_{2,2}$ twice. Therefore
    
    $$
    S_{3,3} = A_{3,3} + S_{2,3} + S_{3,2} - S_{2,2} = 5 + 18 + 15 - 9 = 29.
    $$

By the same reasoning, once the 2D prefix sums are ready, the sum of the submatrix with top-left corner $(i_1,j_1)$ and bottom-right corner $(i_2,j_2)$ is

$$
S_{i_2,j_2} - S_{i_1-1,j_2} - S_{i_2,j_1-1} + S_{i_1-1,j_1-1}.
$$

This takes $O(1)$ time.

In 2D, the time complexity of the algorithm above is simply $O(mn)$, which is linear in the size of the array. But as the number of dimensions $k$ grows, the number of terms in the inclusion-exclusion formula grows exponentially, and the time complexity becomes $O(2^kN)$, where $k$ is the number of dimensions and $N$ is the size of the array. So this method is no longer practical in high dimensions.

???+ example "[Luogu P1387 Largest Square](https://www.luogu.com.cn/problem/P1387)"
    Given an $n\times m$ matrix containing only $0$ and $1$, find the largest square that contains no $0$, and output its side length.

??? note "Reference code"
    === "C++"
        ```cpp
        --8<-- "docs/basic/code/prefix-sum/prefix-sum_2.cpp:full-text"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/basic/code/prefix-sum/prefix-sum_2.py:full-text"
        ```

#### Dimension by dimension

In the general case, we are given a $k$-dimensional array $A$ of size $N$, and again want its prefix sums $S$. Here,

$$
S_{i_1,\cdots,i_k} = \sum_{i'_1\le i_1}\cdots\sum_{i'_k\le i_k} A_{i'_1,\cdots,i'_k}.
$$

The formula shows that a $k$-dimensional prefix sum is just $k$ nested sums. So an obvious algorithm is: handle one dimension at a time, keep all other dimensions fixed, and compute ordinary 1D prefix sums along that dimension. After doing this for all $k$ dimensions, you get the $k$-dimensional prefix sums.

??? example "Reference implementation for 3D prefix sums"
    ```cpp
    --8<-- "docs/basic/code/prefix-sum/prefix-sum_4.cpp:core"
    ```

Each dimension only needs one pass over the whole array, so this algorithm runs in $O(kN)$ time, which is usually acceptable.

#### Special case: sum over subsets DP

High-dimensional cases often show up in a class of problems called **sum over subsets** (SOS). This is a special case of high-dimensional prefix sums.

The problem is as follows. Let $f$ be a function defined on all subsets of a set of size $n$. We want to compute its subset-sum function $g$, which satisfies

$$
g(S) = \sum_{T\subseteq S}f(T).
$$

In other words, $g(S)$ is the sum of $f(T)$ over all subsets $T\subseteq S$.

First, the sum over subsets problem can be written as a high-dimensional prefix sum. Using the idea of bitmasks, any subset $S$ can be represented as a 0-1 string $s$ of length $n$, and a subset $T$ as a string $t$. If we treat each bit of the string as one dimension of an array index, then $f$ is really an $n$-dimensional array whose index in every dimension is either $0$ or $1$. Also, the subset relation is the same as comparing indices:

$$
T\subseteq S \iff \forall i(t_i \le s_i). 
$$

So summing over subsets is exactly computing the prefix sums of this $n$-dimensional array.

Now we can directly use the dimension-by-dimension method above to compute the subset sums. The time complexity is $O(n2^n)$.

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/basic/code/prefix-sum/prefix-sum_5.cpp:core"
    ```

The inverse of the subset sum is computed using the [inclusion-exclusion principle](../math/combinatorics/inclusion-exclusion-principle.md). The sum over subsets is also one of the key steps of the fast Möbius transform.

### Prefix sums on trees

1D prefix sums can also be extended to rooted trees (with root $1$). After preprocessing prefix sums, you can quickly find the total weight of a path in the tree.

#### Vertex weights

First, consider weights stored on the vertices. Let vertex $x$ have weight $a_x$. Using the recurrence

$$
S_1 = a_1,~ S_{x} = S_{\operatorname{fa}(x)} + a_x
$$

we get the sum of vertex weights on the path from the root to vertex $x$, where $\operatorname{fa}(x)$ is the parent of $x$. After this preprocessing, the formula

$$
S_x + S_y - S_{\operatorname{lca}(x, y)} - S_{\operatorname{fa}(\operatorname{lca}(x, y))}
$$

gives the sum of vertex weights on the path between vertices $x$ and $y$. Here, $\operatorname{lca}(x, y)$ is the [lowest common ancestor](../graph/lca.md) of $x$ and $y$.

#### Edge weights

The case where weights are stored on edges can almost be turned into the vertex case. For every non-root vertex $x\neq 1$, let $\operatorname{edge}(x)$ be the edge between $x$ and its parent $\operatorname{fa}(x)$. We can store each edge weight at the endpoint farther from the root. That is, vertex $x$ stores the weight of edge $\operatorname{edge}(x)$, and the root stores weight $0$. Then, using the recurrence from the previous subsection, we can preprocess $S_x$, the total weight of all edges on the path from the root to vertex $x$.

Now the sum of edge weights on the path between vertices $x$ and $y$ can be found with

$$
S_x + S_y - 2S_{\operatorname{lca}(x, y)}
$$

Note that, unlike the vertex case, this sum does not include the value stored at $\operatorname{lca}(x, y)$, because the edge weight stored there is not on the path.

#### Subtree sums

Unlike arrays, a tree's two ends are not symmetric. So computing "prefix sums" bottom-up (from leaves to root) and top-down (from root to leaves) gives different results. Usually, "prefix sums on trees" means the top-down version. To keep the discussion clear, this article calls the bottom-up "prefix sum" the **subtree sum**.

The sum of vertex weights in the subtree rooted at $x$, that is, its subtree sum, is

$$
T_x = \sum_{y\in\operatorname{desc}(x)} a_y.
$$

Here, $\operatorname{desc}(x)$ is the set of all descendants of $x$ (including $x$ itself).

Unlike prefix sums on trees, subtree sums cannot be used to get path sums in $O(1)$. However, they help in understanding difference arrays on trees, discussed below.

## Difference arrays

A difference array is the counterpart of prefix sums: it is the inverse operation. In contests, you rarely need to compute the difference array of a given sequence for its own sake. More often, you maintain a difference array to apply many range updates. After all updates are done, you take prefix sums to recover the original sequence and answer queries on it. Note that all updates must come before the queries.

If you need to support updates and queries mixed together, use a [Fenwick tree](../ds/fenwick.md) instead, though the underlying idea is the same.

### 1D difference arrays

For a sequence $\{a_i\}$, its difference array $\{D_i\}$ is

$$
D_i = a_i - a_{i-1},~ a_0 = 0.
$$

The C++ standard library provides a difference function, [`std::adjacent_difference`](https://zh.cppreference.com/w/cpp/algorithm/adjacent_difference), defined in the header `<numeric>`.

Prefix sums and difference arrays are related as follows:

???+ note "Properties"
    Let $\{D_i\}$ be the difference array of $\{a_i\}$. Then:
    
    -   The sequence $\{a_i\}$ is the prefix sum of $\{D_i\}$, that is,
    
        $$
        a_i = \sum_{j=1}^i D_j.
        $$
    -   The prefix sums of $\{a_i\}$ are
    
        $$
        S_i = \sum_{j=1}^i\sum_{k=1}^jD_k = \sum_{j=1}^i(i-j+1)D_j. 
        $$

Difference arrays are often used when you need to add a value to a range of the sequence many times, and then afterwards ask for the value at certain positions one or more times.

Suppose we want to add $v$ to every element of $\{a_i\}$ in the range $[l,r]$. We can do this on its difference array $\{D_i\}$:

$$
D_{l} \gets D_{l} + v,~ D_{r+1}\gets D_{r+1} - v.
$$

After all updates are done, take prefix sums to recover the updated values of $\{a_i\}$. Each update takes $O(1)$. Before querying, you do one $O(n)$ prefix sum pass, and after that each query is $O(1)$.

???+ example "Reference code"
    ```cpp
    --8<-- "docs/basic/code/prefix-sum/prefix-sum_6.cpp:core"
    ```

### 2D and higher-dimensional difference arrays

Difference arrays also extend to more dimensions. If we view the multidimensional difference as the inverse of multidimensional prefix sums, then computing the difference array means recovering the original array from its prefix sums. From the discussion above, we can use inclusion-exclusion. For example, the 2D difference is defined as

$$
D_{i,j} = a_{i,j} - a_{i-1,j} - a_{i,j-1} + a_{i-1,j-1}.
$$

However, to compute the whole difference array, a simpler and faster way is to go dimension by dimension: loop over every dimension and take the 1D difference of the array along it.

2D difference arrays are often used to add a value to many rectangles of a 2D array. For example, to add $v$ to every number in the submatrix with top-left corner $(x_1,y_1)$ and bottom-right corner $(x_2,y_2)$, apply the following to its difference array $\{D_{i,j}\}$:

$$
\begin{aligned}
D_{x_1,y_1} &\gets D_{x_1,y_1} + v, \\
D_{x_1,y_2+1} &\gets D_{x_1,y_2+1} - v,\\
D_{x_2+1,y_1} &\gets D_{x_2+1,y_1} - v,\\
D_{x_2+1,y_2+1} &\gets D_{x_2+1,y_2+1} + v.
\end{aligned}
$$

After all updates are done, just compute the 2D prefix sums once, and you can quickly query the updated array.

??? example "Reference code"
    ```cpp
    --8<-- "docs/basic/code/prefix-sum/prefix-sum_7.cpp:core"
    ```

Of course, the same idea works for $k>2$ dimensions, but each update takes $O(2^k)$ time, which becomes impractical as $k$ grows.

### Difference arrays on trees

Difference arrays can be extended to rooted trees to add a value along a path in the tree. Depending on whether the data is stored on vertices or on edges, there are **vertex differences** and **edge differences**, which are implemented slightly differently. Also, instead of tree prefix sums, it is more common to compute subtree sums after all updates and then answer queries. That is the case discussed in this section.

#### Vertex differences

To add $v$ to the weight of every vertex on the path between $x$ and $y$, apply the following to the difference array $\{D_x\}$:

$$
\begin{aligned}
D_x &\gets D_x + v, \\
D_{\operatorname{lca}(x, y)} &\gets D_{\operatorname{lca}(x, y)} - v,\\
D_y &\gets D_y + v, \\
D_{\operatorname{fa}(\operatorname{lca}(x, y))} &\gets D_{\operatorname{fa}(\operatorname{lca}(x, y))} - v.
\end{aligned}
$$

After all updates are done, compute the subtree sums once to get the updated vertex weights.

???+ example "Example"
    When adding a value to the vertex weights on the path between $S$ and $T$, the first two lines of the formula above perform a 1D difference update on the path in the blue box, and the last two lines perform one on the path in the red box:
    
    ![](./images/prefix-sum1.svg)
    
    Summing bottom-up is the same as computing prefix sums from bottom to top along these two ranges. Comparing with the 1D difference array above shows why vertex differences work.

#### Edge differences

To add $v$ to the weight of every edge on the path between $x$ and $y$, apply the following to the difference array $\{D_x\}$:

$$
\begin{aligned}
D_x &\gets D_x + v, \\
D_y &\gets D_y + v, \\
D_{\operatorname{lca}(x, y)} &\gets D_{\operatorname{lca}(x, y)} - 2v.
\end{aligned}
$$

After all updates are done, compute the subtree sums once to get the updated edge weights (each stored at the child endpoint of its edge).

???+ example "Example"
    As shown in the figure, edge differences can be used to add a value to the edge weights along the red path.
    
    ![](./images/prefix-sum2.svg)
    
    Taking differences directly on edges is awkward, so we move the value that should be added to each red edge down into the adjacent vertex, which makes things much easier. Comparing with the vertex difference formula helps explain the edge difference formula.

### Example problem

???+ example "[USACO15DEC Max Flow](https://usaco.org/index.php?page=viewproblem2&cpid=576)"
    FJ has installed $N-1$ pipes between the $N(2 \le N \le 50,000)$ stalls in his barn. The stalls are numbered from $1$ to $N$, and all of them are connected by the pipes.
    
    FJ has $K(1 \le K \le 100,000)$ routes for shipping milk. Route $i$ goes from stall $s_i$ to stall $t_i$. Each route adds one unit of pressure to both endpoint stalls and to every stall along the way. You need to find the maximum pressure on any stall.

??? note "Solution"
    We need to count how many times each vertex is passed through. So we use a tree difference array to add one to every vertex on each path, which quickly gives the count for each vertex. Here, LCA is computed with binary lifting. Finally, we traverse the whole tree with DFS and add up the difference array while backtracking to get the answer.

??? note "Reference code"
    ```cpp
    --8<-- "docs/basic/code/prefix-sum/prefix-sum_3.cpp"
    ```

## Exercises

Prefix sums:

-   [Luogu B3612 \[Deep Dive 1, Example 1\] Range Sum](https://www.luogu.com.cn/problem/B3612)
-   [Luogu U69096 Inverse of Prefix Sums](https://www.luogu.com.cn/problem/U69096)
-   [AtCoder joi2007ho\_a Maximum Sum](https://atcoder.jp/contests/joi2007ho/tasks/joi2007ho_a)
-   [USACO16JAN Subsequences Summing to Sevens](https://usaco.org/index.php?page=viewproblem2&cpid=595)
-   [USACO05JAN Moo Volume S](https://www.luogu.com.cn/problem/P6067)

2D and higher-dimensional prefix sums:

-   [HDU 6514 Monitor](https://acm.hdu.edu.cn/showproblem.php?pid=6514)
-   [Luogu P1387 Largest Square](https://www.luogu.com.cn/problem/P1387)
-   [HNOI2003 Laser Bomb](https://www.luogu.com.cn/problem/P2280)
-   [CF 165E Compatible Numbers](https://codeforces.com/contest/165/problem/E)
-   [CF 383E Vowels](https://codeforces.com/problemset/problem/383/E)
-   [ARC 100C Or Plus Max](https://atcoder.jp/contests/arc100/tasks/arc100_c)

Prefix sums on trees:

-   [LOJ 10134.Dis](https://loj.ac/problem/10134)
-   [LOJ 2491. Summation](https://loj.ac/problem/2491)

Difference arrays:

-   [Fenwick Tree 3: Range Update, Range Query](https://loj.ac/problem/132)
-   [Poetize6 IncDec Sequence](https://www.luogu.com.cn/problem/P4552)
-   [Luogu P4231 Three-Step Kill](https://www.luogu.com.cn/problem/P4231)

2D and higher-dimensional difference arrays:

-   [Luogu P3397 Carpet](https://www.luogu.com.cn/problem/P3397)
-   [Luogu P8228 Wdoi-5 Modular Nuclear Fusion Furnace](https://www.luogu.com.cn/problem/P8228)

Difference arrays on trees:

-   [USACO15DEC Max Flow](https://usaco.org/index.php?page=viewproblem2&cpid=576)
-   [JLOI2014 The Squirrel's New Home](https://loj.ac/problem/2236)
-   [NOIP2015 Transport Plan](http://uoj.ac/problem/150)
-   [NOIP2016 Running Every Day](http://uoj.ac/problem/261)
