## Definition

A DAG is a [directed acyclic graph](../graph/dag.md). Binary relations in many practical problems can be modeled with a DAG, which turns these problems into longest (or shortest) path problems on a DAG.

## Explanation

Let's use this problem as an example to walk through the process of modeling with a DAG.

???+ note "Example problem [UVa 437 The Tower of Babylon](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=378)"
    There are $n (n\leqslant 30)$ kinds of blocks. For each kind, the three edge lengths are known, and there are infinitely many blocks of each kind. Choose some blocks and stack them into a column as tall as possible (each block can choose any one of its edges as its height), such that the length and width of each block's base are strictly smaller than those of the block below it. Find the maximum height of the tower.

## Process

### Building the DAG

Since the length and width of each block's base are strictly smaller than those of the block below it, it is natural to use this relation to build the graph, and the problem turns into a longest path problem.

That is, if block $j$ can be placed on block $i$, there is an edge $(i, j)$ between $i$ and $j$, and its weight is the height chosen for block $j$.

Another issue in this problem is that each block's height can be chosen in three ways. How should we build the graph?

We can split each block into its three stacking orientations, that is, turn one block into three blocks, each with a different height.

The initial starting point is the ground. The ground's base is infinitely large, so every block can be placed on the ground. Of course, we do not need to write out infinity explicitly in the program.

Suppose there are two blocks with edges $31, 41, 59$ and $33, 83, 27$. Then the whole DAG looks like the figure below.

![](./images/dag-babylon.png)

Each blue solid box in the figure is the group of blocks obtained by splitting one block. The base edge lengths are written with $\{\}$ because once a block's height is chosen, the order of its base edges does not matter.

The yellow dashed boxes in the figure show repeated computations, which can be avoided with [memoized search](./memo.md).

### Transitions

The problem asks for the maximum height of the tower, which has become a longest path problem. As noted above, the starting point is the ground. What about the end point? Clearly the end point is determined naturally: it is when no other block can be placed on top of the current block.

Now let's work out the transition equation.

Let $d(i,r)$ be the maximum height when block $i$ is at the bottom using the $r$-th stacking orientation. Then the transition equation is:

$$
d(i, r) = \max\left\{d(j, r') + h\right\}
$$

Here $j$ ranges over all blocks that can be placed on block $i$ when it is stacked in orientation $r$, $r'$ is the corresponding orientation of $j$, and $h$ is the height of block $i$ in its $r$-th stacking orientation.

??? note "Implementation"
    ```cpp
    --8<-- "docs/dp/code/dag/dag_1.cpp"
    ```
