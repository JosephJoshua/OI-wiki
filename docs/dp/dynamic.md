Prerequisites: [Matrix](../math/linear-algebra/matrix.md), [Heavy-light decomposition](../graph/hld.md).

Dynamic DP is an advanced technique presented by Mao Kun at WC2018 (the Winter Camp). It is usually used for DP problems on trees with updates to vertex (or edge) weights.

## Example

Let's use this template problem as an example to explain how dynamic DP works.

???+ note "Example problem [Luogu P4719 \[Template\] Dynamic DP](https://www.luogu.com.cn/problem/P4719)"
    Given a tree with $n$ vertices, each with a weight. There are $m$ operations; each gives $x,y$ and changes the weight of vertex $x$ to $y$. After each operation, output the weight of the maximum-weight independent set of the tree.

### Generalized matrix multiplication

Define the generalized matrix multiplication $A\times B=C$ as:

$$
C_{i,j}=\max_{k=1}^{n}(A_{i,k}+B_{k,j})
$$

This is ordinary matrix multiplication with multiplication replaced by addition, and addition replaced by $\max$.

Generalized matrix multiplication is also associative, so fast matrix exponentiation can be used.

### Without updates

Let $f_{i,0}$ be the best answer when $i$ is not chosen, and $f_{i,1}$ the best answer when $i$ is chosen.

Then the DP equations are:

$$
\begin{cases}f_{i,0}=\sum_{son}\max(f_{son,0},f_{son,1})\\f_{i,1}=w_i+\sum_{son}f_{son,0}\end{cases}
$$

The answer is $\max(f_{root,0},f_{root,1})$.

### With updates

First apply heavy-light decomposition to the tree. Suppose there is a heavy path like this:

![](./images/dynamic.png)

Let $g_{i,0}$ be the best answer when $i$ is not chosen and only vertices in the subtrees of $i$'s light children may be chosen. Let $g_{i,1}$ be the best answer when $i$ is chosen, ignoring $son_i$. Here $son_i$ is the heavy child of $i$.

Assuming we know $g_{i,0/1}$, the DP equations are:

$$
\begin{cases}f_{i,0}=g_{i,0}+\max(f_{son_i,0},f_{son_i,1})\\f_{i,1}=g_{i,1}+f_{son_i,0}\end{cases}
$$

The answer is $\max(f_{root,0},f_{root,1})$.

We can build the matrix:

$$
\begin{bmatrix}
g_{i,0} & g_{i,0}\\
g_{i,1} & -\infty
\end{bmatrix}\times 
\begin{bmatrix}
f_{son_i,0}\\f_{son_i,1}
\end{bmatrix}=
\begin{bmatrix}
f_{i,0}\\f_{i,1}
\end{bmatrix}
$$

Note that we use the generalized multiplication rule here.

We can see that an update only needs to change $g_{i,1}$ and each heavy path going upward.

### Detailed approach

1.  Use a DFS to precompute $f_{i,0/1}$ and $g_{i,0/1}$.

2.  Apply heavy-light decomposition to the tree (note: querying a vertex requires the matrix product over the range from that vertex to the end of its heavy path, so for each vertex record $End_i$, the index of the last vertex of the heavy path containing $i$). Build a segment tree for each heavy path; the segment tree maintains the $g$ matrices and the products of $g$ matrices over ranges.

3.  For an update, first change $g_{i,1}$ and the matrix of vertex $i$ in the segment tree, compute how much the matrix of $top_i$ changes, and apply that change to the matrix of $fa_{top_i}$.

4.  For a query, take the range product from 1 to the end of its heavy path, and finally take a $\max$.

??? note "Implementation"
    ```cpp
    --8<-- "docs/dp/code/dynamic/dynamic_1.cpp"
    ```

## Exercises

-   [SPOJ GSS3 - Can you answer these queries III](https://www.spoj.com/problems/GSS3/)
-   [NOIP2018 Defend the Kingdom](https://loj.ac/p/2955)
-   [SDOI2017 Tree Cutting Game](https://loj.ac/p/2269)
