Space optimization techniques are not very common in competitive programming, but they are still worth discussing.

## Information entropy

Information entropy describes the lower bound on the space needed to store data. If the space actually available is below this bound, some information must be lost.

???+ note "Definition"
    For a random variable $X$, its information entropy is defined as
    
    $$
    H(X)=-\sum_{x}P(X=x)\log_2 P(X=x).
    $$

The logarithm in the definition has base $2$ because each bit stored in a computer has only $2$ possible values: $0$ and $1$.

For example, if $X$ is uniformly distributed on $\{1,2,\dots,n\}$, its information entropy is

$$
H(X)=-\sum_{i=1}^n\frac{1}{n}\log_2\frac{1}{n}=\log_2 n,
$$

so we need at least $\log_2 n$ bits to store an integer from $1$ to $n$.

### Example problem

???+ note "[\[WC2022\] Word Guessing](https://www.luogu.com.cn/problem/P8079)"
    This is an interactive problem. You need to guess a 5-letter word within a limited number of tries. Each guess must be a word in the dictionary. If the guess is correct, the game ends. After each wrong guess, the interactor tells you which letters are in the correct position, and which letters appear in the hidden word but in the wrong position.
    
    ??? note "Solution"
        See [Solving Wordle using information theory - 3Blue1Brown](https://www.bilibili.com/video/BV1zZ4y1k7Jw).
        
        Consider computing the information entropy. Clearly, choosing a word with high information entropy for each guess makes the expected number of guesses as small as possible.
        
        Since this problem gives the first letter of the answer before guessing, we can precompute the best guess for each first letter.
        
        Also, when only a few words remain, we can prefer to output words that might be the answer, to reduce the number of guesses.

## Common techniques

### Avoid storing unnecessary data

For example:

-   In a [persistent segment tree](../ds/persistent-seg.md), each update creates only $O(\log n)$ new nodes. So we do not need to store a full copy of the segment tree for each version; we only need to record the new nodes.
-   Consider [graph storage](../graph/save.md). For a sparse graph, an adjacency matrix stores lots of useless $0$s, so sparse graphs are usually stored with adjacency lists.
-   Each element of a `bool` array takes one byte. When needed, you can replace it with `std::vector<bool>` or [bitset](../lang/csl/bitset.md), where each element takes only one bit.
-   In [knapsack DP](../dp/knapsack/basic.md), for the 0-1 knapsack, each round of DP only uses the data from the previous round. So we can save space with a rolling array and only keep the current DP values.

### Use properties of the data

Consider a [disjoint set union](../ds/dsu.md) with path compression and union by size. The usual approach needs two arrays: one for the parent of each node and one for subtree sizes.

Notice that:

1.  With path compression, for each tree in the DSU we only need to record the subtree size of the root.
2.  The parent of a root is always itself.

Using signed integers, we can represent a root with a negative number and a non-root with a non-negative number. So a single array is enough to implement a DSU with path compression and union by size.

???+ note "Implementation"
    ```cpp
    --8<-- "docs/misc/code/space-optimization/space-optimization_1.cpp"
    ```

## Exercises

-   [QOJ 6669 Mapa](https://qoj.ac/problem/6669)
-   [\[SDOI/SXOI2022\] Nowhere to Store](https://www.luogu.com.cn/problem/P8353)

## References and further reading

1.  Chen Zhixuan. "On Space Optimization Problems in Informatics Competitions". 2022 China National Training Team paper
2.  [Information theory - Wikipedia](https://en.wikipedia.org/wiki/Information_theory)
3.  [An Introduction to Information Theory - Luogu Column](https://www.luogu.com.cn/article/i65ca8i5)
