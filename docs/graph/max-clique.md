author: Persdre

Prerequisites: [Clique](./concept.md)

## Introduction

In computer science, the clique problem is the computational problem of finding cliques in a given graph. A clique is a subset of vertices that are all adjacent to each other; it is also called a complete subgraph.

Clique problems also show up in real life. For example, consider a social network where vertices are users and an edge means the two users know each other. Finding a clique means finding a group of people who all know each other.

If we want to find the largest group of people in this social network who all know each other, we need a maximum clique search algorithm.

We have already introduced the concept of a [maximal clique](./concept.md). A maximum clique is a maximal clique with the largest number of vertices.

## Explanation

The idea is to use recursion and backtracking. We keep a list of vertices, and each time we add a vertex we check whether the vertices still form a clique. If adding the vertex breaks the clique, we backtrack to a valid state and try adding other vertices.

We use backtracking because we do not know whether a vertex $v$ will **eventually** be part of a maximum clique. If the recursive algorithm picks $v$ as a member of the maximum clique and does not find one, it should backtrack and look for a maximum clique without $v$.

## Process

The **Bron–Kerbosch** algorithm is an optimized implementation of this idea. Its basic form searches recursively with three sets: $R$, $P$, $X$. The steps are:

1.  Initialize sets $R$ and $X$ as empty, and set $P$ as the set of all vertices of the graph.
2.  Each time, take a vertex $v$ from set $P$. When the set has no vertices left, there are two cases:
    1.  Set $R$ is a maximum clique; in this case set $X$ is empty
    2.  There is no maximum clique; backtrack
3.  For each vertex $v$ taken from set $P$, do the following:
    1.  Add vertex $v$ to set $R$, then recurse on sets $R,P,X$
    2.  Remove vertex $v$ from set $P$ and add it to set $X$
    3.  If sets $P$ and $X$ are both empty, then set $R$ is a maximum clique

This method can be optimized further. To save time and let the algorithm backtrack sooner, we can search using a pivot vertex. Another optimization is to sort all vertices at the start and enumerate them in index order to avoid duplicates.

## Implementation

### Pseudocode

```text
R := {}
P := node set of G 
X := {}

BronKerbosch1(R, P, X):
    if P and X are both empty:
        report R as a maximal clique
    for each vertex v in P:
        BronKerbosch1(R ⋃ {v}, P ⋂ N(v), X ⋂ N(v))
        P := P \ {v}
        X := X ⋃ {v}
```

### C++ implementation

??? note "Implementation"
    ```cpp
    --8<-- "docs/graph/code/max-clique/max-clique_1.cpp"
    ```

## Example problem

???+ note "[POJ 2989: All Friends](http://poj.org/problem?id=2989)"
    Summary: there are $n$ people and $m$ pairs of friends. Find the number of maximal cliques.

Idea: a template problem; use the Bron–Kerbosch algorithm.

Pseudocode:

```text
 BronKerbosch(All, Some, None):  
     if Some and None are both empty:  
         report All as a maximal clique // all vertices chosen and no forbidden vertices left; add to the answer  
     for each vertex v in Some: // enumerate each element of Some  
         BronKerbosch1(All ⋃ {v}, Some ⋂ N(v), None ⋂ N(v))   
         // add v to All; only friends of v can still be candidates, and only friends of v in None affect what follows  
         Some := Some - {v} // already searched: remove from Some and add to None  
         None := None ⋃ {v} 
```

To save time and let the algorithm backtrack sooner, we can optimize by choosing a pivot vertex $v$.

In the algorithm above, there must be many cases where we recompute a maximal clique we already found and then backtrack.

Take the three sets $R$, $P$, $X$ from before as an example:

Consider this: pick a vertex $u$ in $P\cup X$. To form a maximal clique together with $R$, the chosen vertex must be in $P\cap N(u)$ ($N(u)$ is the set of vertices adjacent to $u$).

If, after taking $u$, we can also add a vertex $v$ adjacent to $u$ to the maximal clique, then it is enough to take only $u$. This avoids repeated computation for $v$ later. Afterwards we only need to take vertices not adjacent to $u$.

C++ implementation with the optimization:

??? note "Implementation"
    ```cpp
    --8<-- "docs/graph/code/max-clique/max-clique_2.cpp"
    ```

## Exercises

-   [ZOJ 1492 Maximum Clique](https://pintia.cn/problem-sets/91827364500/exam/problems/type/7?page=4&problemSetProblemId=91827364991)
-   [POJ 1419 Maximum Clique in an Undirected Graph](http://poj.org/problem?id=1419)
-   [POJ 1129 Radio Stations](http://poj.org/problem?id=1129)

## References

-   [Clique problem - Wikipedia](https://en.wikipedia.org/wiki/Clique_problem)
-   [Maximal and maximum cliques of undirected graphs (Bron–Kerbosch algorithm)](https://blog.csdn.net/yo_bc/article/details/77453478)
-   [The maximum clique problem: Bron–Kerbosch algorithm](https://hallelujahjeff.github.io/2018/04/12/34/)
-   [The maximum clique problem](https://www.cnblogs.com/zhj5chengfeng/archive/2013/07/29/3224092.html)
