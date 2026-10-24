author: GitPinkRabbit, Early0v0, Backl1ght, mcendu, ksyx, iamtwz, Xeonacid, kenlig, Menci, Enter-tainer, CCXXXI, hcx2012Git

Before reading the following, make sure you are familiar with the [basic graph theory concepts](./concept.md).

Related reading: [Cut vertices and bridges](./cut.md).

## Introduction

As we all know, trees (and forests) have nice properties and are easy to maintain with many common data structures.

General graphs do not have such nice properties. Fortunately, we can sometimes turn a problem on a general graph into a problem on a tree.

The block forest (also called the round-square tree)[^ref1] is one way to turn a graph into a tree. This article covers how to build a block forest, its properties, and some applications.

Due to space limits, some conclusions in this article are given without proof; readers can work them out or prove them on their own.

## Definition

The block forest was first a tool for handling "cactus graphs" (undirected graphs in which every edge lies on at most one simple cycle). By exploring more of its properties, we can sometimes use it on general undirected graphs too.

To introduce the block forest, we first need **vertex-biconnected components**.

One definition of a **vertex-biconnected graph** is: between any two distinct vertices there are at least two vertex-disjoint paths.  
Vertex-disjoint means both that no vertex repeats within a path (a simple path) and that the two paths share no vertices (of course both paths pass through the start and end vertices; those are not counted).

It is awkward to say whether a graph with only one vertex is vertex-biconnected, so for now we ignore graphs with $1$ vertex.

An almost equivalent definition is: a graph with no cut vertex.  
This definition only differs when the graph has exactly two vertices and one edge between them. It has no cut vertex, but we cannot find two disjoint paths, because there is only one path.  
(You can also think of that single path as counted twice; the two copies indeed do not intersect, since they pass through no other vertices.)

Although the original definition is the former, for convenience we use the latter as the definition of a vertex-biconnected graph.

A **vertex-biconnected component** of a graph is a **maximal vertex-biconnected subgraph**.  
Unlike strongly connected components and similar notions, a vertex may belong to several vertex-biconnected components, but each edge belongs to exactly one (under the first definition, an edge might belong to none).

In the block forest, each vertex of the original graph corresponds to a **round vertex**, and each vertex-biconnected component corresponds to a **square vertex**.  
So there are $n+c$ vertices in total, where $n$ is the number of vertices in the original graph and $c$ is the number of its vertex-biconnected components.

For each vertex-biconnected component, its square vertex is connected by an edge to every vertex in that component.  
Each component becomes a "star graph", and the stars are joined together at the cut vertices of the original graph (because vertex-biconnected components are separated by cut vertices).

Clearly, every edge in the block forest connects a round vertex and a square vertex.

The figures below show a graph, its vertex-biconnected components, and its block forest.[^ref2]

![](./images/block-forest1.svg)![](./images/block-forest2.svg)![](./images/block-forest3.svg)

The block forest has fewer than $2n$ vertices, because there are fewer than $n$ cut vertices. So remember to make your arrays twice as large.

In fact, the block forest is a single tree only if the original graph is connected. If the original graph has $k$ connected components, its block forest is a forest of $k$ trees.

If a connected component of the original graph has only one vertex, it has to be handled case by case. In what follows we ignore isolated vertices.

## Process

How do we build the block forest of a graph? First, if the graph is disconnected, we can handle each connected subgraph separately, so we only consider connected graphs.

The block forest is based on vertex-biconnected components, which in turn are based on cut vertices. So we can use a method similar to finding cut vertices.

The usual algorithm for finding cut vertices is Tarjan's algorithm. If you know it, the following will be easy; if not, that is fine too.

We skip Tarjan's cut-vertex algorithm and go straight to the algorithm used for the block forest (which is actually a variant of Tarjan's):

Run a DFS on the graph, using two key arrays `dfn` and `low` (similar to Tarjan's algorithm).

`dfn[u]` stores the DFS order of vertex $u$, that is, $u$ was the how-manyth vertex visited when it was first reached.  
`low[u]` stores the **smallest** DFS order that any vertex $v$ in the DFS subtree of $u$ can reach by using **at most one back edge or the tree edge to its parent**.  
This may be a bit hard to understand if you have never heard of Tarjan's algorithm, so let's look at an example:

![](./images/block-forest4.svg)

(Note that this graph is actually the same as the graph in the figures above.)  
Here tree edges are drawn as straight lines going downward, and back edges as curves going upward. Each vertex is labeled with its DFS order.

The `low` array is then:

|        $i$        | $1$ | $2$ | $3$ | $4$ | $5$ | $6$ | $7$ | $8$ | $9$ |
| :---------------: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| $\mathrm{low}[i]$ | $1$ | $1$ | $1$ | $3$ | $3$ | $4$ | $3$ | $3$ | $7$ |

Not too hard, right? Note that here the `low` of $9$ is $7$, which differs from some cut-vertex algorithms. This is because, for convenience, we allow going up along the parent edge. The main idea is the same.

We can easily write a DFS function that computes `dfn` and `low` (with `dfn` initially all zero):

???+ note "Implementation"
    === "C++"
        ```cpp
        void Tarjan(int u) {
          low[u] = dfn[u] = ++dfc;                // initialize low to the current dfn
          for (int v : G[u]) {                    // go through the neighbors of u
            if (!dfn[v]) {                        // if not visited yet
              Tarjan(v);                          // recurse
              low[u] = std::min(low[u], low[v]);  // unvisited: take min with low
            } else
              low[u] = std::min(low[u], dfn[v]);  // visited: take min with dfn
          }
        }
        ```
    
    === "Python"
        ```python
        def Tarjan(u):
            low[u] = dfn[u] = dfc  # initialize low to the current dfn
            dfc = dfc + 1
            for v in G[u]:  # go through the neighbors of u
                if dfn[v] == False:  # if not visited yet
                    Tarjan(v)  # recurse
                    low[u] = min(low[u], low[v])  # unvisited: take min with low
                else:
                    low[u] = min(low[u], dfn[v])  # visited: take min with dfn
        ```

Next, let's look at how vertex-biconnected components relate to the DFS tree and these two arrays.

Each vertex-biconnected component forms a connected subtree of the DFS tree with at least two vertices; in particular, its topmost vertex has only one child inside the component.

Also, each tree edge lies in exactly one vertex-biconnected component.

Consider the topmost vertex $u$ of a vertex-biconnected component in the DFS tree. We identify the component at $u$, because the subtree of $u$ contains all the information about the component.

Since the component has at least two vertices, consider the next vertex $v$ of the component; there is a tree edge between $u$ and $v$.

It is not hard to see that then $\mathrm{low}[v]=\mathrm{dfn}[u]$.  
More precisely, for a tree edge $u\to v$, $u$ and $v$ are in the same vertex-biconnected component and $u$ is the shallowest vertex of that component **if and only if** $\mathrm{low}[v]=\mathrm{dfn}[u]$.

So during the DFS we can tell where the vertex-biconnected components are, but we cannot yet tell exactly which vertices each one contains.

This is easy to handle: during the DFS we maintain a stack of vertices whose components (there may be several) have not been determined yet.

When we find a component, all its vertices except $u$ are at the top of the stack, so we just pop until $v$ has been popped.

Of course, we can process the popped vertices at the same time by connecting each to the newly created square vertex. Finally, we also connect $u$ to the square vertex.

This builds the block forest in a natural way. We can number the square vertices starting from $n+1$, which clearly separates round vertices from square vertices.

This part may not be explained clearly enough, so below is a piece of code with detailed comments, debug output to help understanding, and a sample input. We suggest copying the code and trying it yourself; after all, code is often the best way to understand (don't forget to enable `c++11`).

???+ note "Implementation"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <vector>
    
    constexpr int MN = 100005;
    
    int N, M, cnt;
    std::vector<int> G[MN], T[MN * 2];
    
    int dfn[MN], low[MN], dfc;
    int stk[MN], tp;
    
    void Tarjan(int u) {
      printf("  Enter : #%d\n", u);
      low[u] = dfn[u] = ++dfc;                // initialize low to the current dfn
      stk[++tp] = u;                          // push onto the stack
      for (int v : G[u]) {                    // go through the neighbors of u
        if (!dfn[v]) {                        // if not visited yet
          Tarjan(v);                          // recurse
          low[u] = std::min(low[u], low[v]);  // unvisited: take min with low
          if (low[v] == dfn[u]) {  // found a vertex-biconnected component rooted at u
            ++cnt;                 // one more square vertex
            printf("  Found a New BCC #%d.\n", cnt - N);
            // pop the component's vertices other than u and add block-forest edges
            for (int x = 0; x != v; --tp) {
              x = stk[tp];
              T[cnt].push_back(x);
              T[x].push_back(cnt);
              printf("    BCC #%d has vertex #%d\n", cnt - N, x);
            }
            // note: u itself also gets an edge (but is not popped)
            T[cnt].push_back(u);
            T[u].push_back(cnt);
            printf("    BCC #%d has vertex #%d\n", cnt - N, u);
          }
        } else
          low[u] = std::min(low[u], dfn[v]);  // visited: take min with dfn
      }
      printf("  Exit : #%d : low = %d\n", u, low[u]);
      printf("  Stack:\n    ");
      for (int i = 1; i <= tp; ++i) printf("%d, ", stk[i]);
      puts("");
    }
    
    int main() {
      scanf("%d%d", &N, &M);
      cnt = N;  // component / square vertex numbering starts after N
      for (int i = 1; i <= M; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);  // add an undirected edge
        G[v].push_back(u);
      }
      // handle disconnected graphs
      for (int u = 1; u <= N; ++u)
        if (!dfn[u]) Tarjan(u), --tp;
      // when Tarjan returns, one element (the root) is still on the stack; pop it
      return 0;
    }
    ```

Here is a test case:

```text
13 15
1 2
2 3
1 3
3 4
3 5
4 5
5 6
4 6
3 7
3 8
7 8
7 9
10 11
11 10
11 12
```

The graph for this example (it includes multi-edges and isolated vertices):

![](./images/block-forest5.svg)

## Example problems

Here are some example problems that can be solved with the block forest.

???+ note "[APIO2018 Duathlon](https://loj.ac/p/2587)"
    ??? note "Problem summary"
        Given a simple undirected graph, count the triples $\langle s, c, f \rangle$ ($s, c, f$ pairwise distinct) such that there is a simple path starting at $s$, passing through $c$, and ending at $f$.
    
    ??? note "Solution"
        Speaking of simple paths, we must mention a very nice property of vertex-biconnected components: for two vertices in one component, the union of all simple paths between them is exactly that whole component.  
        That is, for two distinct vertices $u,v$ in the same component, there is always a simple path between them that passes through any given third vertex $w$ in the same component.
        
        Proof of this property:
        
        -   Clearly, if a simple path leaves the component, it can never come back into it, otherwise it would contradict the definition of a vertex-biconnected component.
        -   So we only need to prove that for any three distinct vertices $u,v,c$ in a vertex-biconnected graph, there is a simple path from $u$ to $v$ through $c$.
        -   First set aside the case of $2$ vertices: it satisfies the property, but we cannot pick $3$ distinct vertices.
        -   For the remaining cases, build a network flow model: add an edge of capacity $2$ from the source to $c$, and edges of capacity $1$ from $u$ and $v$ to the sink.
        -   Each undirected edge $\langle x,y\rangle$ of the original graph becomes an edge of capacity $1$ from $x$ to $y$ and an edge of capacity $1$ from $y$ to $x$.
        -   Finally, give every vertex other than the source, the sink and $c$ a capacity of $1$, which can be done by splitting vertices.
        -   Since the edge from the source to $c$ has capacity $2$, if the maximum flow of this network is $2$, there must be a path through $c$.
        -   By the max-flow min-cut theorem, the minimum cut is clearly at most $2$, so it remains to show that the minimum cut is greater than $1$.
        -   This is the same as showing that cutting any single capacity-$1$ edge cannot disconnect the source from the sink.
        -   If we cut the edge from $u$ or $v$ to the sink, then by the first definition of vertex-biconnectivity, there is still a simple path from $c$ to the other, uncut vertex.
        -   If we cut the internal edge of a split vertex, this is the same as deleting a vertex; by the second definition of vertex-biconnectivity, the remaining graph is still connected.
        -   If we cut an edge built from an original edge, this is the same as deleting an edge, which is weaker than deleting a vertex, so clearly a path still exists.
        -   So the minimum cut is greater than $1$, that is, the maximum flow is $2$. QED.
        
        What does this tell us? It tells us: take the path between two round vertices in the block forest; the set of round vertices adjacent to the square vertices on that path equals the set of vertices on simple paths between the two vertices in the original graph.
        
        Back to the problem. Fix $s$ and $f$ and count the valid $c$. Clearly the number of valid $c$ equals the number of vertices in the union of simple paths between $s$ and $f$, minus $2$ (excluding $s$ and $f$ themselves).
        
        So after building the block forest of the graph, the number of vertices on simple paths between two vertices depends on the square vertices (components) and round vertices on their path in the block forest.
        
        Next comes a common block forest trick: when counting along paths, give each vertex a suitable weight.  
        In this problem, each square vertex gets weight equal to the size of its component, and each round vertex gets weight $-1$.
        
        With these weights, the sum of vertex weights on the block forest path between two round vertices equals exactly the size of the union of simple paths in the original graph, minus $2$.
        
        The problem becomes computing the $\sum$ of path weight sums over all pairs of round vertices in the block forest.
        
        Looking at it from another angle, count each vertex's contribution to the answer instead: its weight times the number of paths passing through it. This can be computed with a simple tree DP.
        
        Finally, don't forget to handle disconnected graphs. Here is the code:
    
    ??? note "Reference code"
        ```cpp
        --8<-- "docs/graph/code/block-forest/block-forest_1.cpp"
        ```
    
    By the way, the answer for the test case above in this problem is $212$.

???+ note "[Codeforces #487 E. Tourists](https://codeforces.com/contest/487/problem/E)"
    ??? note "Problem summary"
        Given a simple connected undirected graph, support two operations:
        
        1.  Change the weight of a vertex.
        
        2.  Query the minimum vertex weight over all simple paths between two vertices.
    
    ??? note "Solution"
        Again, build the block forest of the graph and set each square vertex's weight to the minimum weight of its adjacent round vertices. The problem becomes finding the minimum along a path.
        
        Path minimums can be maintained with heavy-light decomposition and a segment tree, but what about updates?
        
        Changing a round vertex's weight requires updating all square vertices adjacent to it, so a test can easily force $O(n)$ updates per change.
        
        Here we use the fact that the block forest is a tree: set each square vertex's weight to the minimum weight of its child round vertices. Then an update only needs to change the parent square vertex.
        
        To maintain square vertices, just keep a `multiset` of weights for each square vertex.
        
        Note that in a query, if the LCA is a square vertex, you also need to check the weight of the LCA's parent round vertex.
        
        Note: the block forest needs twice as many vertices as the original graph, otherwise arrays will overflow.
    
    ??? note "Reference code"
        ```cpp
        --8<-- "docs/graph/code/block-forest/block-forest_2.cpp"
        ```

???+ note "[SDOI2018 Strategy Game](https://loj.ac/p/2562)"
    ??? note "Problem summary"
        Given a simple connected undirected graph, answer $q$ queries:
        
        Each query gives a vertex set $S$ ($2 \le |S| \le n$). Count the vertices $u$ with $u \notin S$ such that after deleting $u$, the vertices of $S$ are not all in one connected component.
        
        Each test file contains multiple test cases.
    
    ??? note "Solution"
        First build the block forest. The query becomes: the number of round vertices in the connected subgraph of the block forest spanned by $S$, minus $|S|$.
        
        How do we count the round vertices in the connected subgraph? Here is one method:
        
        Move each round vertex's weight onto the edge between it and its parent square vertex, so the problem becomes a sum of edge weights. This can be solved like one of the solutions to [SDOI2015 Treasure Hunt Game](https://loj.ac/p/2182).  
        That is, sort the vertices of $S$ by DFS order and add up the distances between consecutive vertices (including the distance between the first and the last). The answer is half of this sum, because every edge is traversed exactly twice.
        
        Finally, if the shallowest vertex of the subgraph is a round vertex, add $1$ to the answer, since we did not count it.
        
        Since there are multiple test cases, remember to reset the arrays.
    
    ??? note "Reference code"
        ```cpp
        --8<-- "docs/graph/code/block-forest/block-forest_3.cpp"
        ```

## Exercises

-   [UVa 1464 Traffic Real Time Query](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4210)
-   [Luogu P4320 Road Meeting](https://www.luogu.com.cn/problem/P4320)
-   [Luogu P10517 Land Planning](https://www.luogu.com.cn/problem/P10517)

## External links

immortalCO, [The Block Forest: A Powerful Tool for Cactus Graphs](https://immortalco.blog.uoj.ac/blog/1955), Universal OJ.

## References and notes

[^ref1]: In 2017, Chen Junkun defined and named the block forest in his IOI2017 China National Training Team paper, "Problem Report on *Magic Subgraph* and Its Extensions".

[^ref2]: Chen Junkun, "The Ordinary Block Forest and Magical (~~Dynamic~~) Dynamic Programming", NOI2018 Winter Camp, p. 4.
