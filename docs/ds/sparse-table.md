## Definition

![Sparse table illustration](images/st.svg)

A sparse table (ST) is a data structure for solving **idempotent problems**.

???+ note "What is an idempotent problem?"
    For an operation $\operatorname{opt}$ that satisfies $x\operatorname{opt} x=x$, the corresponding range query is an **idempotent problem** (an element may be counted more than once without changing the answer). For example, the maximum satisfies $\max(x,x)=x$ and gcd satisfies $\operatorname{gcd}(x,x)=x$, so RMQ and range GCD are idempotent problems. A range sum does not have this property: if the precomputed intervals used for a range sum overlap, the overlapping part is counted twice, which is not what we want. Also, $\operatorname{opt}$ must be associative for a sparse table to work.

???+ note "What is RMQ?"
    RMQ stands for Range Maximum/Minimum Query, that is, the maximum (minimum) value of a range. There are many ways to solve RMQ; see the [RMQ topic](../topic/rmq.md).

## Introduction

???+ example "[Luogu P3865 \[Template\] Sparse Table & RMQ](https://www.luogu.com.cn/problem/P3865)"
    Given $n$ ($1\le n\le 10^5$) integers and $m$ ($1\le m\le 2\times 10^6$) queries, for each query output the maximum value in the range $[l,r]$.

Consider brute force: scan the range $[l,r]$ for every query to find the maximum.

Clearly, this algorithm is too slow.

## Sparse table

A sparse table is based on the idea of [binary lifting (doubling)](../basic/binary-lifting.md). It needs $\Theta(n\log n)$ preprocessing and answers each query in $\Theta(1)$. However, it does not support updates.

Let's think about how to find the range maximum with the doubling idea. If we follow the usual doubling process and jump $2^i$ steps at a time, a query still takes $\Theta(\log n)$, which is no better than a segment tree, and the preprocessing is even slower than a segment tree.

Notice that $\max(x,x)=x$, which means the range maximum is an "idempotent" problem. Even if the precomputed intervals we use overlap, as long as their union is the query range, the computed answer is correct.

If you try a few cases by hand, you will find that we can always cover the query range with at most two precomputed intervals. So a query can be answered in $\Theta(1)$ time, which is very effective for problems with many queries.

Here are the details:

Let $f(i,j)$ be the maximum of the interval $[i,i+2^j-1]$.

Clearly $f(i,0)=a_i$.

By the definition, the second index means we "jumped $2^j-1$ steps" in the doubling process. Following the doubling idea, the transition is: $f(i,j)=\max(f(i,j-1),f(i+2^{j-1},j-1))$.

![](./images/st-preprocess-lift.svg)

That is the preprocessing. A query can be implemented simply as follows:

For each query $[l,r]$, split it into two parts: $[l,l+2^s-1]$ and $[r-2^s+1,r]$, where $s=\left\lfloor\log_2(r-l+1)\right\rfloor$. The answer is the maximum of the results of the two parts.

![How a sparse table answers a query](./images/st-query.svg)

By the argument about "idempotent problems" above, since the maximum is an "idempotent problem", the overlap does not affect the range maximum. And since the two intervals fully cover $[l,r]$, the answer is guaranteed to be correct.

???+ example "Reference implementation for [Luogu P3865 \[Template\] Sparse Table & RMQ](https://www.luogu.com.cn/problem/P3865)"
    === "C style"
        ```cpp
        --8<-- "docs/ds/code/sparse-table/sparse-table_1.cpp"
        ```
    
    === "C++ style"
        ```cpp
        --8<-- "docs/ds/code/sparse-table/sparse-table_2.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/ds/code/sparse-table/sparse-table_1.py"
        ```

## Notes

1.  There is usually a lot of input and output, so fast I/O is recommended.

2.  When preprocessing a sparse table, you usually create an array with one dimension of size $\log n$ and the other of size $n$. Prefer making the dimension of size $\log n$ the first dimension, for better cache locality.

3.  Recomputing logarithms with [std::log](https://en.cppreference.com/w/cpp/numeric/math/log) every time is not worth it. Use builtin functions such as `__builtin_clz` or `__lg` instead. If you cannot use these builtins, you can also precompute the logarithm values as follows:

$$
\begin{cases}
\texttt{Logn}[1] \gets 0, \\
\texttt{Logn}\left[i\right] \gets \texttt{Logn}\left[\frac{i}{2}\right] + 1.
\end{cases}
$$

## Maintaining other information with a sparse table

Besides RMQ, there are other "idempotent problems", such as "range bitwise AND", "range bitwise OR" and "range GCD". A sparse table solves all of them efficiently.

Note that for "range GCD", sparse table queries are not faster than a segment tree's (let the value range be $w$; a sparse table query takes $\Theta(\log w)$, while a segment tree takes $\Theta(\log n+\log w)$, and the value range is usually larger than $n$). But the sparse table's preprocessing is not worse than a segment tree's either, and a sparse table is much simpler to code.

If you look closely, "idempotent problems" usually have something RMQ-like in them. For example, "range bitwise AND" takes the minimum of each bit, and "range GCD" takes the minimum exponent of each prime factor.

## Summary

A sparse table handles "idempotent" range information well (the operation must also be associative). It has low time complexity and very little code compared with other algorithms. However, it can maintain only very limited kinds of information, does not extend well, and does not support updates.

## Exercises

-   ["SCOI2007" Rainfall](https://loj.ac/p/2279)

-   [\[USACO07JAN\] Balanced Lineup](https://www.luogu.com.cn/problem/P2880)

## Appendix: time complexity of range GCD with a sparse table

While the algorithm runs, it may go through $\Theta(\log n)$ iterations. Each iteration may call the GCD function, which recurses; let the value range be $w$, then the GCD function takes up to $\Omega(\log w)$ time. So the total time complexity seems to be $O(n\log n\log w)$.

However, during GCD, every recursive step (except the last) at least halves some number in the sequence, and the numbers in the sequence can be halved at most $\log_2 (w^n)=\Theta(n\log w)$ times in total. So the recursive part of GCD runs at most $O(n\log w)$ times. Adding the $\Theta(n\log n)$ for the loop part (and the last level of recursion), the final time complexity is $O(n(\log w+\log n))$. Since one can construct data that makes it take $\Omega(n(\log w+\log n))$, the final time complexity is $\Theta(n(\log w+\log n))$.

The query part is easy to analyze. In the worst case, every query asks about the worst pair of numbers, which takes $\Theta(\log w)$. So a sparse table for "range GCD" takes $\Theta(n(\log n+\log w))$ preprocessing and $\Theta(\log w)$ per query.

The corresponding segment tree operations take $\Theta(n\log w)$ preprocessing and $\Theta(\log n+\log w)$ per query.

This is not a rigorous mathematical argument; a more rigorous one is given below:

??? note "A more rigorous proof"
    To understand this part, you may need to know about the "potential method" from [time complexity](../basic/complexity.md).
    
    First, analyze the time complexity of preprocessing:
    
    Let the "current sequence" be the sequence handled by the current level of the loop while preprocessing the sparse table. For example, the level-zero sequence is the original sequence, and the level-one sequence is the level-zero sequence after one iteration, that is, `st[1..n][1]`. We call it $A$.
    
    Define the potential function as the base-2 logarithm of the product of all numbers in the "current sequence", that is: $\Phi(A)=\log_2\left(\prod\limits_{i=1}^n A_i\right)$.
    
    The time spent in one iteration is the time of the loop itself plus the time spent in GCD. GCD may take more or less time: as few as two or even one recursive call, or as many as $O(\log w)$. But during GCD, every recursive call except the first and the last at least halves some value in the "current sequence". That is, $\Phi(A)$ decreases by at least $1$, so the time of that recursive call can be amortized against the potential function.
    
    Also, the initial value of $\Phi(A)$ is at most $\log_2 (w^n)=\Theta(n\log w)$, and $\Phi(A)$ never increases. So preprocessing the sparse table takes $O(n(\log w+\log n))$ time.
