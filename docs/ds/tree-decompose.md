author: ouuan, Ir1d, Marcythm, Xeonacid

## Ways to split a tree into blocks

See [the real tree Mo's algorithm](../misc/mo-algo-on-tree.md).

You can also see [ouuan's blog / A detailed look at Mo's algorithm, Mo's with updates, and Mo's on trees / Mo's on trees](https://ouuan.github.io/莫队、带修莫队、树上莫队详解/#树上莫队).

For Mo's algorithm on trees, you can also refer to the two articles above.

## Applications of tree sqrt decomposition

Besides Mo's algorithm, tree sqrt decomposition can be used flexibly in some other tree problems. However, problems that can be solved with tree sqrt decomposition often have better solutions, so there are not many problems like this.

As a side note, the tree sqrt decomposition solution to "gty's Girl Tree" can be broken by a star graph.

### [BZOJ4763 Snow Shine](https://hydro.ac/p/bzoj-P4763)

First split the tree into blocks. For the key node of each block, precompute the bitset of colors on the path from it to every key node among its ancestors, and also its nearest ancestor that is a key node. The complexity is $O(n\sqrt n+\frac{nc}{32})$, where $n\sqrt n$ is the cost of jumping up by brute force from every key node, and $\frac{nc}{32}$ is the cost of storing $O(n)$ `bitset`s.

To answer a query, first jump by brute force from each endpoint of the path to the key node of its block. Then jump upward from key node to key node, one block at a time, until reaching the block that contains $lca$. Finally, jump by brute force to $lca$. The `bitset`s between key nodes are already precomputed; the rest is computed during the brute-force jumps. Each query costs $O(\sqrt n+\frac c{32})$, where $\sqrt n$ is the cost of the brute-force jumps inside blocks plus the jumps from block to block, and $O(\frac c{32})$ is the cost of combining the precomputed results with the results of the brute-force jumps. You can count the colors with the `bitset` method `count()`, and find the $\operatorname{mex}$ with the `bitset` method `_Find_first()`.

So the total complexity is $O((n+m)(\sqrt n+\frac c{32}))$.

??? note "Reference code"
    ```cpp
    --8<-- "docs/ds/code/tree-decompose/tree-decompose_1.cpp"
    ```

### [BZOJ4812 Yuno Plays Poker](https://hydro.ac/p/bzoj-P4812)

This problem is almost the same as the previous one. The only difference is how to compute the answer once you have the `bitset`.

~~Since BZOJ limits the total time over all test cases, which is hard to make tight, you can get away with `_Find_next()`.~~

The intended solution handles $16$ bits at a time. First precompute, for all $2^{16}$ possible cases, the number of consecutive $1$s at the high end, the number of consecutive $1$s at the low end, and the contribution in the middle. The catch is that you have to write your own `bitset`, because the standard library `bitset` cannot extract a given group of $16$ bits...

For code, see [this blog post](https://www.cnblogs.com/FallDream/p/bzoj4763.html).
