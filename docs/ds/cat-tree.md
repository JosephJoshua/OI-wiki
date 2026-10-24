author: ChungZH, billchenchina, Chrogeek, Early0v0, ethan-enhe, HeRaNO, hsfzLZH1, iamtwz, Ir1d, konnyakuxzy, luoguojie, Marcythm, orzAtalod, StudyingFather, wy-luke, Xeonacid, CCXXXI, chenryang, chenzheAya, CJSoft, cjsoft, countercurrent-time, DawnMagnet, Enter-tainer, GavinZhengOI, Haohu Shen, Henry-ZHR, hjsjhn, hly1204, jaxvanyang, Jebearssica, kenlig, ksyx, megakite, Menci, moon-dim, NachtgeistW, onelittlechildawa, ouuan, shadowice1984, shawlleyw, shuzhouliu, SukkaW, Tiphereth-A, x2e6, Ycrpro, yifan0305, zeningc, hcx2012Git, karsl-program

## Introduction

As we all know, a segment tree can quickly answer queries for aggregated information over a range, such as the maximum subarray sum in a range, the range sum, or the product of a range of matrices.

The trouble is that, in the eyes of some nasty problem setters, range queries on an ordinary segment tree may still be a bit slow.

Simply put, building a segment tree takes $O(n)$ merge operations, and each range query takes $O(\log{n})$ merges. That is fine for something like range sums. But if we need to query information whose merge is very expensive, such as range matrix products where a merge (one matrix multiplication) costs $O(k^3)$, even $O(\log{n})$ merges per query may be too slow.

The so-called "cat tree" is a static segment tree that does not support updates and only supports fast range queries. It is really worthwhile only when there are many queries ($m=\Omega(n)$).

Building such a static segment tree takes $O(n\log{n})$ merges, but each query then takes only $O(1)$ merges.

For information with expensive merges such as matrix multiplication, a cat tree reduces the cost of a single query from $O(k^3 \log n)$ to $O(k^3)$.

Note that for static range linear basis queries, although a cat tree can improve on a linear basis built with an ordinary segment tree, there is a method that is better in both time and space: the [prefix linear basis](../math/linear-algebra/basis.md#拓展前缀线性基). Also, an ordinary segment tree can handle dynamic range linear basis problems, while for static range linear basis queries a cat tree is more complicated to implement, is not the best solution, and offers no extra functionality.

## How it works

When querying the aggregate over the range $[l,r]$, find the LCA in the segment tree of the node representing $[l,l]$ and the node representing $[r,r]$. Let the range represented by this node $p$ be $[L,R]$. We find some very interesting properties:

1.  The range $[L,R]$ must contain $[l,r]$. This is obvious, since $p$ is an ancestor of both $l$ and $r$.

2.  The range $[l,r]$ must cross the midpoint of $[L,R]$. Since $p$ is the LCA of $l$ and $r$, the left child of $p$ is an ancestor of $l$ but not of $r$, and the right child of $p$ is an ancestor of $r$ but not of $l$. So $l$ must lie in $[L,\mathit{mid}]$ and $r$ must lie in $(\mathit{mid},R]$.

With these two properties, we can reduce the cost of a query to $O(1)$.

## Implementation

Specifically, when building the tree, consider a node of the segment tree and let the range it represents be $(l,r]$.

Unlike a traditional segment tree, which only stores the aggregate of $[l,r]$ in this node, we also store in this node the suffix-sum array of $(l,\mathit{mid}]$ and the prefix-sum array of $(\mathit{mid},r]$.

Then building the tree costs $T(n)=2T(n/2)+O(n)=O(n\log{n})$. In the same way, the space complexity goes from $O(n)$ to $O(n\log{n})$.

Now comes the most important part: the query.

If the query range is $[l,r]$, we find the LCA of the node representing $[l,l]$ and the node representing $[r,r]$, and call it $p$.

By the two properties above, $l,r$ lie inside the range of $p$, and the query must cross the midpoint of $p$.

This leads to a key fact: we can use the prefix-sum and suffix-sum arrays stored in $p$ to split $[l,r]$ into $[l,\mathit{mid}]+(\mathit{mid},r]$, and so assemble the range $[l,r]$.

And this takes only $O(1)$ merges!

But did we forget something?

Finding the LCA does not seem to be $O(1)$ yet. Brute force takes $O(\log{n})$, binary lifting takes $O(\log{\log{n}})$, and converting to a sparse table costs too much...

## Heap-style tree building

Specifically, we pad the sequence to a power of $2$, then build the segment tree.

Now we find that the index of the LCA of two nodes in the segment tree is the longest common prefix (LCP) of the binary indices of the two nodes.

With a little thought, we see that in binary, `lcp(x,y)=x>>digits[x^y]` for $x$ and $y$. (Here `digits[x]` is the number of binary digits of $x$, that is, $\lfloor \log_2 x \rfloor+1$.)

So we just precompute a `digits` array, and finding the LCA becomes easy.

And that is how we build a cat tree.

Since building the tree involves computing prefix sums and suffix sums, for information like matrix multiplication whose merge costs $O(k^3)$, building takes $O(n\log n \cdot k^3)$. On top of that, the cat tree reduces a single static range matrix product query from $O(k^3 \log n)$ to $O(k^3)$. So when there are many queries ($m=\Omega(n)$), the total cost of $m$ queries improves from $O(n \cdot k^3 + m \cdot k^3 \log n)$ to $O(n\log n \cdot k^3 + m \cdot k^3)$.

### References

-   [immortalCO's blog](https://immortalco.blog.uoj.ac/blog/2102)
-   [\[Kle77\]](http://ieeexplore.ieee.org/document/1675628/) V. Klee, "Can the Measure of be Computed in Less than O (n log n) Steps?," Am. Math. Mon., vol. 84, no. 4, pp. 284–285, Apr. 1977.
-   [\[BeW80\]](https://www.tandfonline.com/doi/full/10.1080/00029890.1977.11994336) Bentley and Wood, "An Optimal Worst Case Algorithm for Reporting Intersections of Rectangles," IEEE Trans. Comput., vol. C–29, no. 7, pp. 571–577, Jul. 1980.
