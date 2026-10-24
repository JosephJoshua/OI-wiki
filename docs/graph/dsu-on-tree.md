author: abc1763613206, cesonic, Ir1d, MingqiHuang, xinchengo, xiaofu-15191, hsefz-ChenJunJie

## Introduction

What is a heuristic algorithm?

A heuristic is an optimization of some algorithm based on human experience and intuition.

For example, the most common one is union by size in a disjoint set union. The code looks like this:

```cpp
void merge(int x, int y) {
  int xx = find(x), yy = find(y);
  if (size[xx] < size[yy]) swap(xx, yy);
  fa[yy] = xx;
  size[xx] += size[yy];
}
```

Here, for two sets of different sizes, we merge the smaller set into the larger one, not the larger one into the smaller one.

Why? The size of a set can be seen as (in normal cases) the height of the set, and merging the shorter set into the taller one clearly helps us find the root faster.

Making the shorter tree a subtree of the taller tree is an optimization called heuristic merging (small-to-large merging).

## The algorithm

DSU on tree (small-to-large merging on trees) is an algorithm for some offline tree problems. It is at least as fast as most other algorithms and is easier to understand and implement.

Consider the following problem: [Counting colors on a tree](https://www.luogu.com.cn/problem/U41492).

???+ note "Introductory example"
    You are given a tree with $n$ nodes rooted at $1$. Node $u$ has color $c_u$. For every node $u$, find how many distinct colors appear in the subtree rooted at $u$.
    
    $n\le 2\times 10^5$.

![dsu-on-tree-1.png](./images/dsu-on-tree-1.svg)

Problems like this are usually solved with heavy data structures (tree of trees and so on). If the problem can be solved offline, is there a simpler way?

## Process

Since offline processing is allowed, we can precompute everything and then output each answer in $O(1)$.

Brute-force precomputation takes $O(n^2)$ time: we traverse once from each node, each traversal clearly costs $O(n)$, and there are $n$ nodes, so the complexity is $O(n^2)$.

Notice that the answer of each node comes from its subtrees and the node itself. Let's use this property.

First precompute the subtree size and the heavy child of each node. As in heavy-light decomposition, the heavy child is the child with the largest subtree. This clearly takes $O(n)$.

Let $cnt_i$ be the number of occurrences of color $i$, and $ans_u$ be the answer of node $u$.

To process a node $u$, we do the following steps:

1.  First traverse the light (non-heavy) children of $u$ and compute their answers, but **do not keep their effect on the $cnt$ array** afterwards;
2.  Traverse its heavy child and **keep its effect on the $cnt$ array**;
3.  Traverse the subtree nodes of the light children of $u$ again and add their contributions, to get the answer of $u$.

![dsu-on-tree-2.png](./images/dsu-on-tree-2.svg)

The figure above shows an example.

This way, for each node, we traverse the heavy subtree once and the light subtrees twice, which is clearly the cheapest option.

By running this process, we get the answers for all subtrees of this node.

Why not merge steps 1 and 3? Because the $cnt$ array cannot be duplicated; otherwise memory would be too large. We must do it in $O(n)$ space.

Clearly, if a node $u$ is traversed $x$ times, its heavy child is traversed $x$ times and its light children (if any) are traversed $2x$ times.

Note that after each traversal, except for the heavy child, $cnt$ must be cleared.

## Proof

Define heavy edges and light edges as in heavy-light decomposition (an edge to the heavy child is heavy, all others are light). See the figure below for the definitions of heavy children and heavy edges. For a tree with $n$ nodes:

The number of light edges from the root to any node is at most $\log n$. Suppose there are $x$ light edges from the root to some node, and the subtree of that node has size $y$. Clearly the child at the end of a light edge has a subtree smaller than half of its parent's (otherwise the edge would not be light), so $y<n/2^x$. Clearly $n>2^x$, so $x<\log n$.

Also, if a node is the heavy child of its parent, its subtree is the largest among its siblings. So for every heavy edge on the path from a node to the root, the parent end of that edge never traverses this node again when computing its answer. Thus the number of times a node is traversed equals the number of light edges on its path to the root $+1$ (the $+1$ is because the node itself has to be visited). So each node is traversed at most $\log n+1$ times, the total time complexity is $O(n(\log n+1))=O(n\log n)$, and outputting the answers costs $O(m)$.

![dsu-on-tree-3.png](./images/dsu-on-tree-3.svg)

*Bold edges in the figure are heavy edges. The child at the end of a heavy edge is a heavy child.*

## Optimization

As mentioned in the proof, dsu on tree uses the light/heavy child idea from heavy-light decomposition to speed up merging. So we can also directly use the DFS order produced by heavy-light decomposition, turn the recursion into iteration, and further reduce the constant factor of dsu on tree.

The DFS order itself has this property: the subtree of a node is always contiguous in the DFS order. So we can loop over the DFS order array backwards. This guarantees that when we reach a node, all other nodes in its subtree have already been processed.

The DFS order from heavy-light decomposition has another nice property: each heavy path is contiguous in the DFS order. So when we visit nodes in reverse DFS order, for a node at the top of a heavy path, the next node to visit is never its parent, so its effect must be cleared. For a node not at the top of a heavy path, the previously visited node is either its own heavy child or a node from another branch whose effect has already been cleared, so it can directly inherit the effect. On top of that, we use the DFS order to quickly add the effect of all light children and record the answer.

This is the non-recursive/iterative implementation of dsu on tree (also called the DFS-order implementation of dsu on tree). Compared with the original recursive version, it avoids the time and memory cost of recursive calls and gives a noticeable constant-factor speedup. **It has a significant stack-space advantage, especially on trees with many long chains.**

## Implementation

??? example "Reference implementation"
    === "Recursive implementation"
        ```cpp
        --8<-- "docs/graph/code/dsu-on-tree/dsu-on-tree_1.cpp"
        ```
    
    === "Non-recursive implementation"
        ```cpp
        --8<-- "docs/graph/code/dsu-on-tree/dsu-on-tree_2.cpp"
        ```

## Applications

1.  Problems whose intended solution is dsu on tree

    For example [CF741D](http://codeforces.com/problemset/problem/741/D). Given a tree where each node's value is a letter from 'a' to 'v', for each query find a path in a subtree whose characters can be rearranged into a palindrome.

    Since the characters are rearranged into a palindrome, a character appearing twice is the same as not appearing. In other words, the path must satisfy **at most one character appears an odd number of times**.

    The straightforward approach is to run a DFS from every node, and at each node brute-force all letters to find paths whose XOR with it has at most one 1 bit, then take the longest. This is $O(n^2\log n)$, and dsu on tree optimizes it to $O(n\log^2n)$. For details, see the further reading below.

2.  Problems where dsu can be used as a hack

    It can get partial points on some tree-of-trees problems (when there are no updates), and dsu has a better complexity than Mo's algorithm on trees, which is $O(n\sqrt{m})$.

## Exercises

[CF600E Lomsat gelral](http://codeforces.com/problemset/problem/600/E)

Statement: Each node of a tree has a color. A color dominates a subtree if and only if no other color appears more times than it in that subtree. For each subtree, find the sum of all colors that dominate it.

[UOJ284 Happy Game Chicken](https://uoj.ac/problem/284)

[CF1709E XOR Tree](https://codeforces.com/contest/1709/problem/E)

## References / further reading

[dsu on tree as introduced by the author of CF741D](http://codeforces.com/blog/entry/44351)

[This author's editorial](http://codeforces.com/blog/entry/48871)
