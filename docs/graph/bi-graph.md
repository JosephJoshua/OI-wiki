## Introduction

A bipartite graph is a graph with a special structure. Its vertex set can be split into two disjoint subsets so that every edge connects a vertex in one subset to a vertex in the other, and no edge connects two vertices in the same subset.

Thanks to this simple structure, bipartite graphs have many elegant properties and are widely used to model real-life situations such as task assignment, recommender systems and matching markets. Many optimization problems that are hard on general graphs can be solved efficiently and exactly on bipartite graphs.

## Definition

If the vertex set $V$ of a graph $G=(V,E)$ can be split into two disjoint subsets $X$ and $Y$ so that every edge $e\in E$ has one endpoint in $X$ and the other in $Y$, then $G$ is called a **bipartite graph**. The sets $X$ and $Y$ are often called its two **parts**, or the left part and the right part. When the two parts $X$ and $Y$ are known, the bipartite graph $G$ can also be written as the triple $(X, Y, E)$.

A typical bipartite graph is shown below.

![](./images/bi-graph-1.svg)

Trees, even cycles and grid graphs are common examples of bipartite graphs.

## Characterization

A bipartite graph can be equivalently defined by either of the following properties:

-   The graph $G$ is 2-colorable. That is, all its vertices can be colored with at most two colors so that adjacent vertices have different colors.
-   The graph $G$ has no cycle of odd length.

The first property is clearly equivalent to the definition: just color each of the two parts with its own color.

The second property is a bit more involved. Try to color $G$ with two colors. Since coloring different connected components does not interfere, we can handle components one at a time. Pick any vertex $s$ in a component, run a DFS, and record for every vertex $v$ in the component its distance from $s$ in the DFS spanning tree (that is, its depth). By induction along the DFS spanning tree starting from $s$, if a valid coloring exists, it must color each vertex $v$ by the parity of its distance to the start $s$.

![](./images/bi-graph-2.svg)

Next, consider the edges not in the spanning tree. If both endpoints of every non-tree edge have different colors, the current coloring is valid; otherwise no valid coloring exists. Moreover, two vertices have different colors if and only if one of their distances to the root $s$ is odd and the other is even, which is equivalent to the non-tree edge closing an even cycle rather than an odd one. So as long as there is no odd cycle, every non-tree edge connects vertices of different colors, the whole graph can be colored with two colors, and the graph is bipartite.

## Testing

To test whether a graph is bipartite, we just use the characterization above and try to color the graph. We can traverse the graph with [DFS](./dfs.md) or [BFS](./bfs.md). If we find an odd cycle, meaning the coloring gets stuck, the graph is not bipartite; otherwise, it is.

The steps are:

-   Go through the vertices. An uncolored vertex means we have found a new connected component.
-   Give that vertex either color, and run [DFS](./dfs.md) or [BFS](./bfs.md) from it to try to color the component.
-   When visiting an adjacent vertex that is already colored, check whether its color equals the current vertex's color. If it does, the graph is not bipartite, and we return immediately; otherwise, continue.
-   When visiting an adjacent vertex that is not yet colored, give it the opposite color of the current vertex.

The reference code is as follows:

???+ example "Reference code"
    ```cpp
    --8<-- "docs/graph/code/bi-graph/check-bipartite.cpp:core"
    ```

The time complexity is $O(|V|+|E|)$.

## Applications

Thanks to their simple structure, many graph optimization problems can be solved efficiently on bipartite graphs. See the main articles for details.

-   Maximum clique (trivial)
-   Minimum vertex coloring (trivial)
-   [Minimum edge coloring](./color.md#二分图-vizing-定理的构造性证明)
-   [Maximum matching](./graph-matching/bigraph-match.md)
-   [Minimum edge cover](./graph-matching/graph-match.md#最小权边覆盖)
-   [Minimum vertex cover](./graph-matching/bigraph-match.md#二分图最小点覆盖)
-   [Maximum independent set](./graph-matching/bigraph-match.md#二分图最大独立集)
-   [Maximum weight matching](./graph-matching/bigraph-weight-match.md)
-   [Games on bipartite graphs](../math/game-theory/impartial-game.md#二分图博弈)
