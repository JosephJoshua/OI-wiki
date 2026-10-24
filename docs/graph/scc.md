## Introduction

Before reading the following, make sure you know the basics in [Graph theory concepts](./concept.md).

Strong connectivity is defined as follows: a directed graph G is strongly connected if every two nodes in G are mutually reachable.

A strongly connected component (SCC) is defined as a maximal strongly connected subgraph.

This page explains how to find strongly connected components.

## Tarjan's algorithm

### Introduction

Robert E. Tarjan (1948\~), born in Pomona, California, USA, is a computer scientist.

Tarjan invented many algorithms and data structures. Quite a few of them are named after him, which sometimes makes it easy to confuse different algorithms, for example Tarjan's algorithm for various kinds of connected components and Tarjan's algorithm for LCA (Lowest Common Ancestor). Disjoint set union, the splay tree and the top tree were also invented by Tarjan.

Here we introduce Tarjan's algorithm for finding strongly connected components in a directed graph.

### DFS spanning tree

Before introducing the algorithm, let us first look at the **DFS spanning tree**, using the directed graph below as an example:

![DFS spanning tree](./images/dfs-tree.svg)

When running DFS on a directed graph $G$, the edges have directions, so starting from a single node may not reach every node of the graph. So we go through the whole vertex set: for every node that has not been visited yet, we start a new DFS. In each DFS run from some start node, the tree edges it uses (see below) form a tree, called a **DFS spanning tree**. Once all nodes have been visited, all the DFS spanning trees together form the **DFS spanning forest** of the directed graph.

Note that the exact shape of the spanning tree (and spanning forest), as well as the edge classification below, depends on which start nodes the DFS picks and the order in which neighbors are visited.

The edges of a directed graph $G$ fall into four types:

1.  Tree edge: shown in black in the figure. Each time the search finds a node that has not been visited yet, it creates a tree edge. All the tree edges together form the DFS spanning tree.
2.  Back edge: shown in red in the figure (that is, $7 \rightarrow 1$). It is a non-tree edge that, during the search, goes from a node to one of its ancestors.
3.  Forward edge: shown in green in the figure (that is, $3 \rightarrow 6$). It is a non-tree edge that, during the search, goes from a node to a descendant in its subtree.
4.  Cross edge: shown in blue in the figure (that is, $9 \rightarrow 7$). It is an edge that, during the search, goes from a node to an already visited node that is neither an ancestor nor a descendant; in other words, any edge not in the three types above.

Let us look at how DFS spanning trees relate to strongly connected components.

If node $u$ is the first node of some strongly connected component reached in the search tree, then all the other nodes of this component must be in the subtree rooted at $u$. Node $u$ is called the root of this strongly connected component.

Proof by contradiction: suppose some node $v$ is in this component but not in the subtree rooted at $u$. Then the path from $u$ to $v$ must contain an edge that leaves the subtree. But such an edge can only be a cross edge or a back edge, and both of these point to nodes that have already been visited. This contradicts the fact that $v$ is not in the subtree rooted at $u$. This proves the claim.

### Finding SCCs with Tarjan's algorithm

Tarjan's algorithm is based on a [depth-first search](./dfs.md) of the graph. We treat each component as a subtree of the search tree. During the search, we keep a stack: each node of the search tree that has not been finished yet is pushed onto the stack, and nodes whose answer is determined are popped off.

Tarjan's algorithm keeps the following values for each node $u$:

1.  $\textit{dfn}_u$: the order in which node $u$ is visited by the depth-first search.
2.  $\textit{low}_u$: the earliest node still on the stack that can be reached back from the subtree of $u$. Let $\textit{Subtree}_u$ be the subtree rooted at $u$ in the search tree. $\textit{low}_u$ is defined as the minimum $\textit{dfn}$ over the following nodes: nodes on the stack that can be reached from $\textit{Subtree}_u$ through one edge that is not in the search tree.

Every node in the subtree of a node has a larger dfn than that node.

Along a path starting from the root, dfn strictly increases and low never decreases.

Visit all nodes of the graph in depth-first search order, keep the `dfn` and `low` values of each node, and push each visited node onto the stack. Each time a strongly connected component is found, pop as many elements from the stack as it has nodes. During the search, for a node $u$ and a neighbor $v$ ($v$ is not the parent of $u$), there are 3 cases:

1.  $v$ has not been visited: keep searching deeper from $v$. When backtracking, update $\textit{low}_u$ with $\textit{low}_v$. Since there is a direct path from $u$ to $v$, any node on the stack that $v$ can reach back to can also be reached back to from $u$.
2.  $v$ has been visited and is on the stack: by the definition of low, update $\textit{low}_u$ with $\textit{dfn}_v$.
3.  $v$ has been visited and is no longer on the stack: this means $v$ is finished and its component has already been handled, so nothing needs to be done.

For a strongly connected component, it is easy to see that there is exactly one $u$ in it with $\textit{dfn}_u=\textit{low}_u$. This node must be the first node of the component visited during the depth-first traversal, because its dfn and low values are the smallest and cannot be affected by the other nodes of the component.

So while backtracking, we check whether $\textit{dfn}_u=\textit{low}_u$ holds. If it does, $u$ and the nodes above it on the stack form an SCC.

The algorithm above in pseudocode:

???+ note "Implementation"
    ```text
    TARJAN_SEARCH(int u)
        vis[u]=true
        low[u]=dfn[u]=++dfncnt
        push u to the stack
        for each (u,v) then do
            if v hasn't been searched then
                TARJAN_SEARCH(v) // search
                low[u]=min(low[u],low[v]) // backtrack
            else if v has been in the stack then
                low[u]=min(low[u],dfn[v])
        if dfn[u] equal to low[u] then
            ++scccnt
            while top of stack not equal to u then
                scc[top of stack] = scccnt
                pop stack
            scc[u] = scccnt
            pop stack // handle and remove the remaining u
    ```

### Implementation

=== "C++"
    ```cpp
    int dfn[N], low[N], dfncnt, s[N], in_stack[N], tp;
    int scc[N], sc;  // ID of the SCC that node i belongs to
    int sz[N];       // size of SCC i
    
    void tarjan(int u) {
      low[u] = dfn[u] = ++dfncnt, s[++tp] = u, in_stack[u] = 1;
      for (int i = h[u]; i; i = e[i].nex) {
        const int &v = e[i].t;
        if (!dfn[v]) {
          tarjan(v);
          low[u] = min(low[u], low[v]);
        } else if (in_stack[v]) {
          low[u] = min(low[u], dfn[v]);
        }
      }
      if (dfn[u] == low[u]) {
        ++sc;
        do {
          scc[s[tp]] = sc;
          sz[sc]++;
          in_stack[s[tp]] = 0;
        } while (s[tp--] != u);
      }
    }
    ```

=== "Python"
    ```python
    dfn = [0] * N
    low = [0] * N
    dfncnt = 0
    s = [0] * N
    in_stack = [0] * N
    tp = 0
    scc = [0] * N
    sc = 0  # ID of the SCC that node i belongs to
    sz = [0] * N  # size of SCC i
    
    
    def tarjan(u):
        low[u] = dfn[u] = dfncnt
        s[tp] = u
        in_stack[u] = 1
        dfncnt = dfncnt + 1
        tp = tp + 1
        i = h[u]
        while i:
            v = e[i].t
            if dfn[v] == False:
                tarjan(v)
                low[u] = min(low[u], low[v])
            elif in_stack[v]:
                low[u] = min(low[u], dfn[v])
            i = e[i].nex
        if dfn[u] == low[u]:
            sc = sc + 1
            while s[tp] != u:
                scc[s[tp]] = sc
                sz[sc] = sz[sc] + 1
                in_stack[s[tp]] = 0
                tp = tp - 1
            scc[s[tp]] = sc
            sz[sc] = sz[sc] + 1
            in_stack[s[tp]] = 0
            tp = tp - 1
    ```

The time complexity is $O(n + m)$.

### Relation between component labels and topological order

Tarjan's algorithm actually finds the strongly connected components in some **reverse topological order**. This is because the depth-first search finishes the nodes with no outgoing edges first, which is the opposite of how topological sorting works.

If we contract every strongly connected component of the graph into a single node and topologically sort the resulting DAG, the order we get is the reverse of the order in which Tarjan's algorithm labels the components.

So we can say that in the contracted DAG, **the label order of the (contracted) strongly connected components is the reverse of a topological order**. But note that this only holds when we consider the dependencies between components (that is, directed edges from one strongly connected component to another). The nodes inside a single strongly connected component form cycles, so they do not satisfy the definition of a topological order.

## Kosaraju's algorithm

### Introduction

Kosaraju's algorithm was first proposed by S. Rao Kosaraju in an unpublished paper in 1978, but Micha Sharir was the first to publish it.

### Process

The algorithm uses two simple DFS passes:

First DFS: starting from any vertex, visit all unvisited vertices, and number each vertex just before backtracking from it, that is, in postorder.

Second DFS: on the reversed graph, start a DFS from the vertex with the largest number. The set of vertices it reaches is one strongly connected component. Among all unvisited nodes, pick the one with the largest number and repeat.

After the two DFS passes, all strongly connected components have been found. The time complexity of Kosaraju's algorithm is $O(n+m)$.

### Implementation

=== "C++"
    ```cpp
    // g is the original graph, g2 is the reversed graph
    
    void dfs1(int u) {
      vis[u] = true;
      for (int v : g[u])
        if (!vis[v]) dfs1(v);
      s.push_back(u);
    }
    
    void dfs2(int u) {
      color[u] = sccCnt;
      for (int v : g2[u])
        if (!color[v]) dfs2(v);
    }
    
    void kosaraju() {
      sccCnt = 0;
      for (int i = 1; i <= n; ++i)
        if (!vis[i]) dfs1(i);
      for (int i = n - 1; i >= 0; --i)
        if (!color[s[i]]) {
          ++sccCnt;
          dfs2(s[i]);
        }
    }
    ```

=== "Python"
    ```python
    def dfs1(u):
        vis[u] = True
        for v in g[u]:
            if vis[v] == False:
                dfs1(v)
        s.append(u)
    
    
    def dfs2(u):
        color[u] = sccCnt
        for v in g2[u]:
            if color[v] == False:
                dfs2(v)
    
    
    def kosaraju(u):
        sccCnt = 0
        for i in range(1, n + 1):
            if vis[i] == False:
                dfs1(i)
        for i in range(n - 1, -1, -1):
            if color[s[i]] == False:
                sccCnt = sccCnt + 1
                dfs2(s[i])
    ```

## Garbow's algorithm

### Process

Garbow's algorithm is another way to implement Tarjan's algorithm. Tarjan's algorithm uses dfn and low to find the root of each strongly connected component. Garbow's algorithm keeps a stack of nodes, and uses a second stack to decide when to pop the nodes of one strongly connected component off the first stack. During the DFS from node $w$, when a path shows that a group of nodes all belong to the same strongly connected component, we keep popping the top node of the second stack as long as its visit time is greater than that of the root $w$, so in the end only the root $w$ remains. Every node popped in this process belongs to the same strongly connected component.

When backtracking to a node $w$, if this node is on top of the second stack, it is the starting node of a strongly connected component, and all nodes visited after it belong to the same component. So we pop those nodes off the first stack, and they form the strongly connected component.

### Implementation

=== "C++"
    ```cpp
    int garbow(int u) {
      stack1[++p1] = u;
      stack2[++p2] = u;
      low[u] = ++dfs_clock;
      for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (!low[v])
          garbow(v);
        else if (!sccno[v])
          while (low[stack2[p2]] > low[v]) p2--;
      }
      if (stack2[p2] == u) {
        p2--;
        scc_cnt++;
        do {
          sccno[stack1[p1]] = scc_cnt;
          // all_scc[scc_cnt] ++;
        } while (stack1[p1--] != u);
      }
      return 0;
    }
    
    void find_scc(int n) {
      dfs_clock = scc_cnt = 0;
      p1 = p2 = 0;
      memset(sccno, 0, sizeof(sccno));
      memset(low, 0, sizeof(low));
      for (int i = 1; i <= n; i++)
        if (!low[i]) garbow(i);
    }
    ```

=== "Python"
    ```python
    def garbow(u):
        stack1[p1] = u
        stack2[p2] = u
        p1 = p1 + 1
        p2 = p2 + 1
        low[u] = dfs_clock
        dfs_clock = dfs_clock + 1
        i = head[u]
        while i:
            v = e[i].to
            if low[v] == False:
                garbow(v)
            elif sccno[v] == False:
                while low[stack2[p2]] > low[v]:
                    p2 = p2 - 1
        if stack2[p2] == u:
            p2 = p2 - 1
            scc_cnt = scc_cnt + 1
            while stack1[p1] != u:
                p1 = p1 - 1
                sccno[stack1[p1]] = scc_cnt
    
    
    def find_scc(n):
        dfs_clock = scc_cnt = 0
        p1 = p2 = 0
        sccno = []
        low = []
        for i in range(1, n + 1):
            if low[i] == False:
                garbow(i)
    ```

## Applications

We can contract each strongly connected component of a graph into a single node.

The graph then becomes a DAG, on which we can do topological sorting and many other things.

A simple example: find a path, which may visit nodes more than once, that visits as many distinct nodes as possible.

## Exercises

[USACO Fall/HAOI 2006 Popular Cows](https://loj.ac/problem/10091)

[POJ1236 Network of Schools](http://poj.org/problem?id=1236)
