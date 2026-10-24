author: Ir1d, sshwy, GavinZhengOI, Planet6174, ouuan, Marcythm, ylxmf2005, 0xis-cn

Related reading: [Biconnected components](./bcc.md)

For more rigorous definitions of cut vertices and bridges, see [basic graph theory concepts](./concept.md).

## Cut vertices

> In an undirected graph, if deleting a vertex increases the number of maximal connected components, that vertex is a cut vertex (also called an articulation point) of the graph.

### Process

If we try deleting each vertex in turn and checking the graph's connectivity, the complexity is very high. So we introduce a commonly used algorithm: Tarjan's algorithm.

First, here is a graph:

![](./images/cut1.svg)

It is easy to see that the cut vertex is 2, and it is the only cut vertex in this graph.

First, we assign each vertex a timestamp (its visiting order) in DFS order.

![](./images/cut2.svg)

We store this in an array called `dfn`.

We also need another array `low`, which stores the smallest timestamp a vertex can reach without going through its parent.

For example, `low[2]` is 1, and `low[5]` and `low[6]` are 3.

Then we run the DFS. We decide whether a vertex is a cut vertex as follows: for a vertex $u$, if there is at least one vertex $v$ (a child of $u$) with $low_v \geq dfn_u$, that is, $v$ cannot get back to an ancestor, then $u$ is a cut vertex.

This rule does not apply to the starting vertex of the search, which needs special handling. If the start is not a cut vertex, every other vertex can be reached by other paths, so from the start we only "search downward once", that is, it has only one child in the search tree. If it has two or more children in the search tree, it must be a cut vertex (imagine searching the graph above starting from 2: the search tree should have two children, 3 or 4 and 5 or 6). If it has only one child, deleting it has no effect. For example, in the graph below, the vertices form a cycle.

![](./images/cut3.svg)

When visiting the children of 1, suppose the DFS reaches 2 first, marks it as used, and recurses down to 4, and from 4 to 3. When the recursion backtracks, we find that 3 has already been visited, so 1 is not a cut vertex.

The pseudocode for updating `low` is:

$$
\begin{array}{ll}
1 & \textbf{if } v \text{ is a son of } u \\
2 & \qquad \text{low}_u = \min(\text{low}_u, \text{low}_v) \\
3 & \textbf{else} \\
4 & \qquad \text{low}_u = \min(\text{low}_u, \text{dfn}_v) \\
\end{array}
$$

### Example problem

[Luogu P3388 [Template] Cut Vertices (Articulation Points)](https://www.luogu.com.cn/problem/P3388)

??? note "Example code"
    ```cpp
    --8<-- "docs/graph/code/cut/cut_1.cpp"
    ```

## Bridges (without multiple edges)

Bridges are much like cut vertices.

> In an undirected graph, if deleting an edge increases the number of connected components, that edge is called a bridge or cut edge. More rigorously: let $G=\{V,E\}$ be a connected graph and $e$ one of its edges ($e \in E$). If $G-e$ is disconnected, then $e$ is a bridge (cut edge) of $G$.

For example, in the graph below,

![Bridge example](./images/bridge1.svg)

the red edge is a bridge.

### Process

It is almost the same as for cut vertices, with one change: use $low_v>dfn_u$. Also, there is no need to handle the root specially.

Whether an edge is a bridge has nothing to do with the root. For cut vertices, the condition meant that $v$ cannot get back to an ancestor (including the parent) without going through its parent $u$, so $u$ is a cut vertex. If $low_v=dfn_u$, $v$ can still get back to its parent. If $v$ can neither get back to an ancestor nor has another route back to its parent, then the edge $u-v$ is a bridge.

### Implementation

The code below finds the bridges of an undirected graph **without multiple edges**. When `isbridge[x]` is true, `(father[x],x)` is a bridge.

=== "C++"
    ```cpp
    int low[MAXN], dfn[MAXN], idx;
    bool isbridge[MAXN];
    vector<int> G[MAXN];
    int cnt_bridge;
    int father[MAXN];
    
    void tarjan(int u, int fa) {
      father[u] = fa;
      low[u] = dfn[u] = ++idx;
      for (const auto &v : G[u]) {
        if (!dfn[v]) {
          tarjan(v, u);
          low[u] = min(low[u], low[v]);
          if (low[v] > dfn[u]) {
            isbridge[v] = true;
            ++cnt_bridge;
          }
        } else if (v != fa) {
          low[u] = min(low[u], dfn[v]);
        }
      }
    }
    ```

=== "Python"
    ```python
    low = [0] * MAXN
    dfn = [0] * MAXN
    idx = 0
    isbridge = [False] * MAXN
    G = [[0 for i in range(MAXN)] for j in range(MAXN)]
    cnt_bridge = 0
    father = [0] * MAXN
    
    
    def tarjan(u, fa):
        father[u] = fa
        idx = idx + 1
        low[u] = dfn[u] = idx
        for i in range(0, len(G[u])):
            v = G[u][i]
            if dfn[v] == False:
                tarjan(v, u)
                low[u] = min(low[u], low[v])
                if low[v] > dfn[u]:
                    isbridge[v] = True
                    cnt_bridge = cnt_bridge + 1
            elif v != fa:
                low[u] = min(low[u], dfn[v])
    ```

## Bridges (with multiple edges)

However, the method above for graphs without multiple edges goes wrong on undirected graphs with multiple edges.

There may be more than one edge between two vertices, and then none of those edges is a bridge.

### Process

One idea is to change the parameter `fa` to the id of the edge we just came along (both directions of an edge share one id). That is, change "don't update using the parent" to "don't update using the edge we came from".

A simpler idea is to keep a flag recording whether one edge to the parent has already been seen. After the flag is set, any further visit to the parent updates as usual.

The code below finds the bridges of an undirected graph that may have **multiple edges**.

=== "C++"
    ```cpp
    int low[MAXN], dfn[MAXN], idx;
    bool isbridge[MAXN];
    vector<int> G[MAXN];
    int cnt_bridge;
    int father[MAXN];
    
    void tarjan(int u, int fa) {
      bool flag = false;
      father[u] = fa;
      low[u] = dfn[u] = ++idx;
      for (const auto &v : G[u]) {
        if (!dfn[v]) {
          tarjan(v, u);
          low[u] = min(low[u], low[v]);
          if (low[v] > dfn[u]) {
            isbridge[v] = true;
            ++cnt_bridge;
          }
        } else {
          if (v != fa || flag)
            low[u] = min(low[u], dfn[v]);
          else
            flag = true;
        }
      }
    }
    ```

## Exercises

-   [P3388 [Template] Cut Vertices (Articulation Points)](https://www.luogu.com.cn/problem/P3388)
-   [POJ2117 Electricity](http://poj.org/problem?id=2117)
-   [HDU4738 Caocao's Bridges](https://acm.hdu.edu.cn/showproblem.php?pid=4738)
-   [HDU2460 Network](https://acm.hdu.edu.cn/showproblem.php?pid=2460)
-   [POJ1523 SPF](http://poj.org/problem?id=1523)

Tarjan's algorithm has many other uses, such as finding strongly connected components, condensing SCCs, and solving 2-SAT.
