## Introduction

The Lindström–Gessel–Viennot lemma, or LGV lemma, can be used for problems such as counting non-intersecting paths in a directed acyclic graph.

Prerequisites: the basics in [Graph theory concepts](./concept.md), [Matrices](../math/linear-algebra/matrix.md), [Computing determinants with Gaussian elimination](../math/numerical/gauss.md).

The LGV lemma only applies to **directed acyclic graphs**.

## Definition

$\omega(P)$ is the product of the weights of all edges on the path $P$. (When counting paths, set all edge weights to $1$.) (In fact, edge weights can even be generating functions.)

$e(u, v)$ is the sum of $\omega(P)$ over **every** path $P$ from $u$ to $v$, that is, $e(u, v)=\sum\limits_{P:u\rightarrow v}\omega(P)$.

The start set $A$ is a subset of the vertex set of the DAG, of size $n$.

The end set $B$ is also a subset of the vertex set of the DAG, also of size $n$.

A set of non-intersecting paths $S$ from $A$ to $B$: $S_i$ is a path from $A_i$ to $B_{\sigma(S)_i}$ (where $\sigma(S)$ is a permutation), and for any $i\ne j$, $S_i$ and $S_j$ share no vertex.

$t(\sigma)$ is the number of inversions of the permutation $\sigma$.

## Lemma

$$
M = \begin{bmatrix}e(A_1,B_1)&e(A_1,B_2)&\cdots&e(A_1,B_n)\\
e(A_2,B_1)&e(A_2,B_2)&\cdots&e(A_2,B_n)\\
\vdots&\vdots&\ddots&\vdots\\
e(A_n,B_1)&e(A_n,B_2)&\cdots&e(A_n,B_n)\end{bmatrix}
$$

$$
\det(M)=\sum\limits_{S:A\rightarrow B}(-1)^{t(\sigma(S))}\prod\limits_{i=1}^n \omega(S_i)
$$

Here $\sum\limits_{S:A\rightarrow B}$ runs over every set $S$ of non-intersecting paths from $A$ to $B$ as required above.

### Proof

By the definition of the determinant,

$$
\begin{align}
\det(M)&=\sum_{\sigma}(-1)^{t(\sigma)}\prod_{i=1}^n e(a_i,b_{\sigma(i)})\\
&=\sum_{\sigma}(-1)^{t(\sigma)}\prod_{i=1}^n \sum_{P:a_i\to b_{\sigma(i)}} \omega(P)
\end{align}
$$

Notice that $\prod\limits_{i=1}^n \sum\limits_{P:a_i\to b_{\sigma(i)}} \omega(P)$ is actually the sum of $\omega(P)$ over all path sets $P$ from $A$ to $B$ whose permutation is $\sigma$.

$$
\begin{align}
&\sum_{\sigma}(-1)^{t(\sigma)}\prod_{i=1}^n \sum_{P:a_i\to b_{\sigma(i)}} \omega(P)\\
=&\sum_{\sigma}(-1)^{t(\sigma)}\sum_{P=\sigma}\omega(P)\\
=&\sum_{P:A\to B}(-1)^{t(\sigma)}\prod_{i=1}^n \omega(P_i)
\end{align}
$$

Here $P$ is an arbitrary path set.

Let $U$ be the non-intersecting path sets and $V$ the intersecting path sets. Then

$$
\begin{align}
&\sum_{P:A\to B}(-1)^{t(\sigma)}\prod_{i=1}^n \omega(P_i)\\
=&\sum_{U:A\to B}(-1)^{t(U)}\prod_{i=1}^n \omega(U_i)+\sum_{V:A\to B}(-1)^{t(V)}\prod_{i=1}^n \omega(V_i)
\end{align}
$$

If $P$ contains an intersecting pair of paths $P_i:a_1 \to u \to b_1,P_j:a_2 \to u \to b_2$, then there must be a matching intersecting path set with $P_i'=a_1\to u\to b_2,P_j'=a_2\to u\to b_1$, where the other paths of $P'$ are the same as in $P$. Then $\omega(P)=\omega(P'),t(P)=t(P')\pm 1$.

So we have $\sum\limits_{V:A\to B}(-1)^{t(\sigma)}\prod\limits_{i=1}^n \omega(V_i)=0$.

Therefore $\det(M)=\sum\limits_{U:A\to B}(-1)^{t(U)}\prod\limits_{i=1}^n \omega(U_i)$.

This completes the proof[^1].

## Example problems

???+ note "Example 1 [CF348D Turtles](https://codeforces.com/contest/348/problem/D)"
    Statement: there is an $n\times m$ grid board, where some cells can be walked on and some cannot. A turtle at $(x, y)$ can only move to $(x+1, y)$ or $(x, y+1)$. Find the number of pairs of non-intersecting paths from $(1, 1)$ to $(n, m)$, modulo $10^9+7$. $2\le n,m\le3000$.

This is a fairly direct application of the LGV lemma. Looking at all valid paths, a path from $(1,1)$ must pass through $A=\{(1,2), (2,1)\}$, and a path reaching the end must pass through $B=\{(n-1, m), (n, m-1)\}$, so $A$ and $B$ are chosen right away. Applying the LGV lemma, the answer is:

$$
\begin{vmatrix}
f(a_1, b_1) & f(a_1, b_2) \\
f(a_2, b_1) & f(a_2, b_2)
\end{vmatrix} = f(a_1, b_1)\times f(a_2, b_2) - f(a_1, b_2)\times f(a_2, b_1)
$$

Here $f(a, b)$ is the number of paths $a\rightarrow b$ in the graph. Counting paths on a grid with blocked cells can be done directly with an $O(nm)$ DP, so $f$ is easy to compute. The final complexity is $O(nm)$.

??? note "Reference code"
    ```cpp
    --8<-- "docs/graph/code/lgv/lgv_2.cpp"
    ```

???+ note "Example 2 [HDU 5852 Intersection is not allowed!](https://acm.hdu.edu.cn/showproblem.php?pid=5852)"
    Statement: there is an $n\times n$ board. A piece at $(x, y)$ can only move to $(x, y+1)$ or $(x + 1, y)$. There are $k$ pieces; the $i$-th piece starts at $(1, a_i)$ and must end at $(n, b_i)$, and the paths must be pairwise non-intersecting. Find the number of ways modulo $10^9+7$. $1\le n\le 10^5$, $1\le k\le 100$, and it is guaranteed that $1\le a_1<a_2<\dots<a_n\le n$ and $1\le b_1<b_2<\dots<b_n\le n$.

Notice that if the paths do not intersect, they must go from $a_i$ to $b_i$, so in the LGV lemma we always have $\sigma(S)_i=i$, and there is no need to worry about signs. Set all edge weights to $1$ and apply the lemma directly.

The number of paths from $(1, a_i)$ to $(n, b_j)$ equals the number of ways to choose $n-1$ downward moves out of $n-1+b_j-a_i$ moves, so $e(A_i, B_j)=\binom{n-1+b_j-a_i}{n-1}$.

The determinant can be computed with Gaussian elimination.

The complexity is $O(n+k(k^2 + \log p))$, where $\log p$ is the cost of computing a modular inverse.

??? note "Reference code"
    ```cpp
    --8<-- "docs/graph/code/lgv/lgv_1.cpp"
    ```

## References

[^1]: The proof comes from [Zhihu - Proof of the LGV lemma (Chinese)](https://zhuanlan.zhihu.com/p/517819133)
