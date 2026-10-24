author: Ir1d, HeRaNO, Xeonacid

## Introduction

Sqrt decomposition is really an idea, not a data structure.

The idea of sqrt decomposition shows up at every level of difficulty, from NOIP to NOI to IOI.

The basic idea of sqrt decomposition is to divide the original data in a suitable way and precompute some information for each block, which gives a better time complexity than plain brute force.

The time complexity of sqrt decomposition mainly depends on the block length. Usually the AM-GM inequality gives the optimal block length for a problem and the corresponding time complexity.

Sqrt decomposition is a very flexible idea. Compared with Fenwick trees and segment trees, its advantage is that it is more general: it can maintain a lot of information that Fenwick trees and segment trees cannot.

Of course, the drawback is that its asymptotic complexity is worse than that of segment trees and Fenwick trees.

Still, for most problems, sqrt decomposition is a good choice.

Here are a few examples.

## Range sum

??? note "Example problem [LibreOJ 6280 Intro to Sequence Sqrt Decomposition 4](https://loj.ac/problem/6280)"
    Given a sequence $\{a_i\}$ of length $n$, perform $n$ operations. There are two kinds of operations:
    
    1.  Add $x$ to every number from $a_l$ to $a_r$;
    2.  Compute $\sum_{i=l}^r a_i$.
    
        $1 \leq n \leq 5 \times 10^4$

We split the sequence into blocks of $s$ elements each and record the sum $b_i$ of each block.

$$
\underbrace{a_1, a_2, \ldots, a_s}_{b_1}, \underbrace{a_{s+1}, \ldots, a_{2s}}_{b_2}, \dots, \underbrace{a_{(s-1) \times s+1}, \dots, a_n}_{b_{\frac{n}{s}}}
$$

The last block may be incomplete (since $n$ is probably not a multiple of $s$), but this does not really matter for our discussion.

First, the query operation:

-   If $l$ and $r$ are in the same block, just sum by brute force. Since the block length is $s$, the worst-case complexity is $O(s)$.
-   If $l$ and $r$ are not in the same block, the answer has three parts: the incomplete block starting at $l$, several complete blocks in the middle, and the incomplete block ending at $r$. For the incomplete blocks, we still use brute force as above. For the complete blocks, we just add up the precomputed $b_i$. In this case, the worst-case complexity is $O(\dfrac{n}{s}+s)$.

Next, the update operation:

-   If $l$ and $r$ are in the same block, just update by brute force. Since the block length is $s$, the worst-case complexity is $O(s)$.
-   If $l$ and $r$ are not in the same block, we need to update three parts: the incomplete block starting at $l$, several complete blocks in the middle, and the incomplete block ending at $r$. For the incomplete blocks, we still update each element by brute force (don't forget to update the block sum $b_i$). For the complete blocks, we just update $b_i$ directly. In this case, the worst-case complexity is still $O(\dfrac{n}{s}+s)$.

By the AM-GM inequality, when $\dfrac{n}{s}=s$, that is, $s=\sqrt n$, a single operation has the best time complexity, $O(\sqrt n)$.

??? note "Reference code"
    ```cpp
    --8<-- "docs/ds/code/decompose/decompose_1.cpp"
    ```

## Range sum 2

The complexity of the previous method is $\Omega(1) , O(\sqrt{n})$.

Here we introduce an $O(\sqrt{n}) - O(1)$ algorithm.

To answer queries in $O(1)$, we can maintain various prefix sums.

However, with updates, they are hard to maintain, so we can only maintain prefix sums inside each block,

plus prefix sums that treat each whole block as one unit.

Each update takes $O(T+\frac{n}{T})$.

Query: it involves three parts, and each part can be read directly from the prefix sums, so the time complexity is $O(1)$.

## Sqrt decomposition on queries

Same problem as before; now the sequence length is $n$ and there are $m$ operations.

If there are only a few operations, we can record them and add their effects when answering a query.

Suppose we record at most $T$ operations. Then an update takes $O(1)$ and a query takes $O(T)$.

After $T$ operations, recompute the prefix sums in $O(n)$.

Total complexity: $O(mT+n\frac{m}{T})$.

With $T=\sqrt{n}$, the total complexity is $O(m \sqrt{n})$.

### Other problems

The idea of sqrt decomposition can also be applied to other problems on integers: counting zero elements, finding the first non-zero element, counting elements that satisfy some property, and so on.

Some other problems can also be solved with sqrt decomposition, for example maintaining a set of numbers that allows adding or deleting numbers, checking whether a number belongs to the set, and finding the $k$-th largest number. To solve this, we store the numbers in increasing order and split them into blocks, each containing $\sqrt{n}$ numbers. Every time a number is added or deleted, we must re-split the blocks by moving numbers across the boundaries of adjacent blocks.

The well-known offline algorithm [Mo's algorithm](../misc/mo-algo.md) is also based on the idea of sqrt decomposition.

## Exercises

-   [UVa - 12003 - Array Transformer](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3154)
-   [UVa - 11990 Dynamic Inversion](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3141)
-   [SPOJ - Give Away](http://www.spoj.com/problems/GIVEAWAY/)
-   [Codeforces - Till I Collapse](http://codeforces.com/contest/786/problem/C)
-   [Codeforces - Destiny](http://codeforces.com/contest/840/problem/D)
-   [Codeforces - Holes](http://codeforces.com/contest/13/problem/E)
-   [Codeforces - XOR and Favorite Number](https://codeforces.com/problemset/problem/617/E)
-   [Codeforces - Powerful array](http://codeforces.com/problemset/problem/86/D)
-   [SPOJ - DQUERY](https://www.spoj.com/problems/DQUERY)

    **This page is mainly translated from the article [Sqrt-декомпозиция](http://e-maxx.ru/algo/sqrt_decomposition) and its English version [Sqrt Decomposition](https://cp-algorithms.com/data_structures/sqrt_decomposition.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**
