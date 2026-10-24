author: greyqz, Ir1d, hsfzLZH1, huaruoji, banglee13

Fractional programming is used to find the extreme value of a fraction. Formally: given $a_i$ and $b_i$, find a set of $w_i\in\{0,1\}$ that minimizes or maximizes

$$
\displaystyle\frac{\sum\limits_{i=1}^na_i\times w_i}{\sum\limits_{i=1}^nb_i\times w_i}
$$

In plain words, problems of this kind look like this: each item has two weights $a$ and $b$, and you choose some items so that $\displaystyle\frac{\sum a}{\sum b}$ is as small or as large as possible.

Fractional programming problems usually come with some extra constraints, such as "the denominator must be at least $W$".

## Solving

### Binary search

The general method for fractional programming is binary search on the answer. Suppose the current candidate answer is $\textit{mid}$. Then a valid choice of $\{w_i\}$ must make the value at least $\textit{mid}$. Write this as an inequality and rearrange it:

$$
\displaystyle
\begin{aligned}
&\frac{\sum a_i\times w_i}{\sum b_i\times w_i}\ge mid\\
\Longrightarrow&\sum a_i\times w_i-mid\times \sum b_i\cdot w_i\ge 0\\
\Longrightarrow&\sum w_i\times(a_i-mid\times b_i)\ge 0
\end{aligned}
$$

So we only need the maximum of the left-hand side. If the maximum is greater than $0$, then $mid$ is feasible; otherwise it is not. The main difficulty of fractional programming lies in finding the maximum or minimum of $\displaystyle \sum w_i\times(a_i-mid\times b_i)$.

### Dinkelbach's algorithm

The rough idea of Dinkelbach's algorithm[^note1] is to use the answer from the previous round as the new $L$, and keep iterating until the answer converges.

## Example problems

???+ example "[LOJ 149 0/1 Fractional Programming](https://loj.ac/p/149)"
    There are $n$ items, and each item has two weights $a$ and $b$. Find a set of $w_i\in\{0,1\}$ with exactly $k$ of the $w_i$ equal to $1$ that maximizes $\displaystyle\frac{\sum a_i\times w_i}{\sum b_i\times w_i}$.

??? note "Solution"
    Use $a_i-mid\times b_i$ as the weight of item $i$, and greedily pick the $k$ items with the largest weights. If the sum of the weights is greater than $0$, $mid$ is feasible; otherwise it is not.

??? note "Reference code"
    ```cpp
    --8<-- "docs/misc/code/frac-programming/frac-1.cpp"
    ```

???+ example "[Luogu 4377 Talent Show G](https://www.luogu.com.cn/problem/P4377)"
    There are $n$ items, and each item has two weights $a$ and $b$.
    
    You need to choose a set of $w_i\in\{0,1\}$ that maximizes $\displaystyle\frac{\sum w_i\times a_i}{\sum w_i\times b_i}$.
    
    It is required that $\displaystyle\sum w_i\times b_i \geq W$.

??? note "Solution"
    This problem adds the constraint that the denominator must be at least $W$, so the greedy method from the previous problem no longer works.
    
    We can use 0/1 knapsack instead. Treat $b_i$ as the weight of item $i$ and $a_i-mid\times b_i$ as its value, and the problem becomes a knapsack problem. Then $dp[n][W]$ is the maximum.
    
    During the DP, the total weight of the items may exceed $W$. In that case, just treat it as $W$.

??? note "Reference code"
    ```cpp
    --8<-- "docs/misc/code/frac-programming/frac-2.cpp"
    ```

???+ example "[POJ2728 Desert King](http://poj.org/problem?id=2728)"
    Each edge has two weights $a_i$ and $b_i$. Find a spanning tree $T$ that minimizes $\displaystyle\frac{\sum_{e\in T}a_e}{\sum_{e\in T}b_e}$.

??? note "Solution"
    Use $a_i-mid\times b_i$ as the weight of each edge; then the minimum spanning tree gives the minimum. In this problem we need the minimum spanning tree of a complete graph, so Prim's algorithm should be used.

??? note "Reference code"
    ```cpp
    --8<-- "docs/misc/code/frac-programming/frac-3.cpp"
    ```

???+ example "[\[HNOI2009\] Minimum Cycle](https://www.luogu.com.cn/problem/P3199)"
    Each edge has weight $w$. Find a cycle $C$ that minimizes $\displaystyle\frac{\sum_{e\in C}w}{|C|}$.

??? note "Solution"
    Use $a_i-mid$ as the edge weight; then the cycle with the smallest total weight gives the minimum.
    
    Since we only need to check whether the minimum is less than $0$, it is enough to check whether the graph has a negative cycle.
    
    This problem also has an $O(nm)$ algorithm. If you are interested, you can read [this article](https://www.cnblogs.com/y-clever/p/7043553.html).

??? note "Reference code"
    ```cpp
    --8<-- "docs/misc/code/frac-programming/frac-4.cpp"
    ```

## Exercises

-   [JSOI2016 Best Team](https://loj.ac/problem/2071)
-   [SDOI2017 Freshman Dance](https://loj.ac/problem/2003)
-   [UVa1389 Hard Life](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=4135)
-   [Luogu P2868 \[USACO07DEC\] Sightseeing Cows G](https://www.luogu.com.cn/problem/P2868)
-   [AtCoder Beginner Contest 324 F - Beautiful Path](https://atcoder.jp/contests/abc324/tasks/abc324_f)

## References and notes

[^note1]: [Dinkelbach, Werner. "On nonlinear fractional programming." Management science 13.7 (1967): 492-498.](https://doi.org/10.1287/mnsc.13.7.492)
