## Introduction

Before reading the following, make sure you are familiar with the [basic graph theory concepts](./concept.md).

Related reading: [Cut vertices and bridges](./cut.md)

## Definition

For more rigorous definitions of cut vertices and bridges, see [basic graph theory concepts](./concept.md).

In a connected undirected graph, two vertices $u$ and $v$ are **edge-biconnected** if deleting any single edge (only one edge may be deleted) never disconnects them.

In a connected undirected graph, two vertices $u$ and $v$ are **vertex-biconnected** if deleting any single vertex (only one, and not $u$ or $v$ themselves) never disconnects them.

Edge-biconnectivity is transitive: if $x,y$ are edge-biconnected and $y,z$ are edge-biconnected, then $x,z$ are edge-biconnected.

Vertex-biconnectivity is **not** transitive. In the counterexample below, $A,B$ are vertex-biconnected and $B,C$ are vertex-biconnected, but $A,C$ are **not** vertex-biconnected.

![bcc-counterexample.png](./images/bcc-0.svg)

A **maximal** edge-biconnected subgraph of an undirected graph is called an **edge-biconnected component**.

A **maximal** vertex-biconnected subgraph of an undirected graph is called a **vertex-biconnected component**.

## DFS spanning tree

For a connected undirected graph, we can start a DFS from any vertex and get a DFS spanning tree of the graph (rooted at the starting vertex). Edges on this spanning tree are called **tree edges**, and edges not on it are called **non-tree edges**.

By the nature of DFS, every non-tree edge connects two vertices where one is an ancestor of the other in the spanning tree.

The DFS code is as follows:

???+ note "Implementation"
    === "C++"
        ```cpp
        void DFS(int p) {
          visited[p] = true;
          for (int to : edge[p])
            if (!visited[to]) DFS(to);
        }
        ```
    
    === "Python"
        ```python
        def DFS(p):
            visited[p] = True
            for to in edge[p]:
                if visited[to] == False:
                    DFS(to)
        ```

## Edge-biconnected components

???+ note "[Example problem: Luogu P8436 [Template] Edge-Biconnected Components](https://www.luogu.com.cn/problem/P8436)"
    Given a graph with $n$ vertices and $m$ undirected edges, output the number of its edge-biconnected components and list each of them.

### Tarjan's algorithm 1

Finding biconnected components with Tarjan's algorithm is similar to finding strongly connected components. You may want to read about Tarjan's algorithm on the [strongly connected components](./scc.md) page first.

Our plan is to find all bridges first, then use DFS to find the edge-biconnected components.

For finding bridges, see the bridge section of [Cut vertices and bridges](./cut.md).

The time complexity is $O(n+m)$.

??? note "Example code"
    ```cpp
    --8<-- "docs/graph/code/bcc/bcc_1.cpp"
    ```

### Tarjan's algorithm 2

First, an important property: in an undirected graph, every edge relative to the DFS spanning tree is either a tree edge or a non-tree edge.

Recall how we find strongly connected components. In an undirected graph, as long as a component has no bridge, all its vertices lie in the same strongly connected component with respect to the DFS spanning tree.

Conversely, a strongly connected component with respect to the DFS spanning tree is an edge-biconnected component of the original undirected graph.

So finding edge-biconnected components is really the same process as finding strongly connected components.

The time complexity is $O(n+m)$.

??? note "Example code"
    ```cpp
    --8<-- "docs/graph/code/bcc/bcc_2.cpp"
    ```

### Difference-array algorithm

Like Tarjan's algorithm 1, we first find all bridges, then use differences to find the edge-biconnected components.

First, run a DFS on the graph.

![bcc-1.png](./images/bcc-1.svg)

In the figure above, black and green edges are tree edges and red edges are non-tree edges. The two endpoints of each non-tree edge correspond to a unique simple path of tree edges in the tree. We say the non-tree edge **covers** every edge on that simple path.

In the figure, green tree edges are covered by **at least** one non-tree edge, and black tree edges are not covered by **any** non-tree edge.

Clearly, **non-tree edges** and **green tree edges** are never bridges, while **black tree edges** are always bridges.

A brute-force approach: for each non-tree edge, color every tree edge it covers green, one by one. This takes $O(nm)$ time.

We can speed this up with a difference array. For each non-tree edge, put a `-1` mark on its endpoint with smaller depth in the tree and a `+1` mark on its endpoint with larger depth. Then compute, in $O(n)$, the sum of marks inside each vertex's subtree.

For a vertex $u$, the sum of marks in its subtree equals the number of non-tree edges covering the tree edge between $u$ and $fa_u$. If this value is $0$, then the tree edge between $u$ and $fa_u$ is a **bridge**.

Then use DFS to find the edge-biconnected components.

The time complexity is $O(n+m)$.

??? note "Example code"
    ```cpp
    --8<-- "docs/graph/code/bcc/bcc_4.cpp"
    ```

???+ note "[#2788. CEOI2015 Day1 Pipes](https://loj.ac/p/2788)"
    Given an undirected graph with $N$ vertices and $M$ edges, not necessarily connected, treat each connected component as a subgraph and find the bridges in each one. **You only have 16 MB of memory.**

??? note "Solution"
    The key feature of this problem is that you cannot store all the edges.
    
    Optimize edge storage: if a non-tree edge is completely covered by another non-tree edge, it is useless.
    
    Maintain this with a disjoint set union.

## Vertex-biconnected components

???+ note "[Example problem: Luogu P8435 [Template] Vertex-Biconnected Components](https://www.luogu.com.cn/problem/P8435)"
    Given a graph with $n$ vertices and $m$ undirected edges, output the number of its vertex-biconnected components and list each of them.

### Tarjan's algorithm

You need to learn about cut vertices first; see the cut vertex section of [Cut vertices and bridges](./cut.md).

Two properties first:

1.  Two vertex-biconnected components share at most one vertex, and that vertex must be a cut vertex.
2.  In any vertex-biconnected component, the vertex with the smallest dfn value in the DFS tree must be a cut vertex or the root of the tree.

Based on the second property, we consider cases:

1.  If the vertex is a cut vertex, it must be the root of the vertex-biconnected component, because if the component included its parent, it would still be a cut vertex.
2.  If the vertex is the root of the tree:
    1.  If it has two or more subtrees, it is a cut vertex.
    2.  If it has exactly one subtree, it is the root of a vertex-biconnected component.
    3.  If it has no subtrees, it is treated as a vertex-biconnected component by itself.

??? note "Example code"
    ```cpp
    --8<-- "docs/graph/code/bcc/bcc_3.cpp"
    ```

### Difference-array algorithm

![bcc-2.png](./images/bcc-2.svg)

In the figure above, black edges are tree edges and red edges are non-tree edges. The two endpoints of each non-tree edge correspond to a unique simple path of tree edges in the tree.

Consider a new graph in which each vertex corresponds to a tree edge of the original graph (shown as blue vertices in the figure). For each non-tree edge in the original graph, connect into one connected component the blue vertices of all edges on the tree path that this non-tree edge corresponds to (shown as blue edges in the figure).

Then a vertex is **not** a cut vertex if and only if the blue vertices of all edges incident to it **belong to** the same connected component of the new graph.

Two vertices **are** vertex-biconnected if and only if the blue vertices of all edges on their tree path in the original graph **belong to** the same connected component. In other words, each connected component formed by blue vertices is a vertex-biconnected component.

The connectivity among blue vertices can be maintained with a difference method similar to the one used for edge-biconnected components. The time complexity is $O(n+m)$.
