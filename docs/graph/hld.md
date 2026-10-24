author: GoodCoder666, Ir1d, Marcythm, ouuan, hsfzLZH1, Xeonacid, greyqz, Chrogeek, ftxj, sshwy, LuoshuiTianyi, hyp1231, sun2snow, Desmos666-xh

## Introduction

Tree chain decomposition splits a tree into a number of chains, so that information on paths in the tree can be maintained.

More precisely, we split the whole tree into chains, arrange them into a linear structure, and then maintain the information with some other data structure.

**Tree chain decomposition** comes in several forms, such as **heavy-light decomposition**, **long-path decomposition**, and the decomposition used in the Link/cut Tree (sometimes called "preferred-path decomposition"). In most cases (unless stated otherwise), "tree chain decomposition" means heavy-light decomposition.

Heavy-light decomposition splits any path in the tree into at most $O(\log n)$ contiguous chains. On each chain, all nodes have different depths (that is, each chain goes from bottom to top, and the LCA of all nodes on the chain is one endpoint of the chain).

Heavy-light decomposition also guarantees that the DFS order of the nodes on each chain is contiguous. So we can easily use data structures that maintain sequences (such as a segment tree) to maintain information on tree paths. For example:

1.  Modify the values of all nodes **on the path between two nodes of the tree**.
2.  Query the **sum / maximum or minimum / other information (anything that can be maintained by a data structure on a sequence and is easy to merge)** of the node weights **on the path between two nodes of the tree**.

Besides maintaining path information together with a data structure, HLD can also find the LCA in $O(\log n)$ time (with a small constant). In some problems, its properties can also be used in more flexible ways.

## Heavy-light decomposition

Here are some definitions:

The **heavy child** of a node is its child with the largest subtree. If several children have the largest subtree, pick any one of them. If a node has no children, it has no heavy child.

The **light children** are all the remaining children.

The edge from a node to its heavy child is a **heavy edge**.

The edges to its other, light children are **light edges**.

A sequence of heavy edges joined end to end forms a **heavy path** (heavy chain).

If we also treat each leftover single node as a heavy path, then the whole tree is split into a number of heavy paths.

As shown in the figure:

![HLD](./images/hld.png)

## Implementation

HLD is implemented with two DFS passes. The pseudocode is as follows:

The first DFS records each node's parent ($\textit{father}$), depth ($\textit{depth}$), subtree size ($\textit{size}$) and heavy child ($\textit{hson}$).

$$
\begin{array}{l}
\text{TREE-BUILD }(u,\textit{dep}) \\
\begin{array}{ll}
1 & u.\textit{hson}\gets 0 \\
2 & u.\textit{hson}.\textit{size}\gets 0 \\
3 & u.\textit{depth}\gets \textit{dep} \\
4 & u.\textit{size}\gets 1 \\
5 & \textbf{for }\text{each son }v\text{ of }u \\
6 & \qquad u.\textit{size}\gets u.\textit{size} + \text{TREE-BUILD }(v,\textit{dep}+1) \\
7 & \qquad v.\textit{father}\gets u \\
8 & \qquad \textbf{if }v.\textit{size}> u.\textit{hson}.\textit{size} \\
9 & \qquad \qquad u.\textit{hson}\gets v \\
10 & \textbf{return } u.\textit{size}
\end{array}
\end{array}
$$

The second DFS records the top of the chain the node lies on ($\textit{top}$, which should be initialized to the node itself), the DFS order when heavy edges are visited first ($\textit{dfn}$), and the node corresponding to each DFS order ($\textit{rank}$).

$$
\begin{array}{l}
\text{TREE-DECOMPOSITION }(u,\textit{top}) \\
\begin{array}{ll}
1 & u.\textit{top}\gets \textit{top} \\
2 & \textit{tot}\gets \textit{tot}+1\\
3 & u.\textit{dfn}\gets \textit{tot} \\
4 & \textit{rank}(\textit{tot})\gets u \\
5 & \textbf{if }u.\textit{hson}\text{ is not }0 \\
6 & \qquad \text{TREE-DECOMPOSITION }(u.\textit{hson},\textit{top}) \\
7 & \qquad \textbf{for }\text{each son }v\text{ of }u \\
8 & \qquad \qquad \textbf{if }v\text{ is not }u.\textit{hson} \\
9 & \qquad \qquad \qquad \text{TREE-DECOMPOSITION }(v,v) 
\end{array}
\end{array}
$$

Below is the code implementation.

First we give some definitions:

-   $\operatorname{fa}(x)$ is the parent of node $x$ in the tree.
-   $\operatorname{dep}(x)$ is the depth of node $x$ in the tree.
-   $\operatorname{siz}(x)$ is the number of nodes in the subtree of $x$.
-   $\operatorname{son}(x)$ is the **heavy child** of node $x$.
-   $\operatorname{top}(x)$ is the top node (the one with smallest depth) of the **heavy path** containing $x$.
-   $\operatorname{dfn}(x)$ is the **DFS order** of node $x$, which is also its index in the segment tree.
-   $\operatorname{rnk}(x)$ is the node corresponding to a DFS order, so $\operatorname{rnk}(\operatorname{dfn}(x))=x$.

We compute these values with two DFS passes. The first DFS computes $\operatorname{fa}(x)$, $\operatorname{dep}(x)$, $\operatorname{siz}(x)$, $\operatorname{son}(x)$, and the second DFS computes $\operatorname{top}(x)$, $\operatorname{dfn}(x)$, $\operatorname{rnk}(x)$.

```cpp
void dfs1(int u, int f) {
  fa[u] = f, dep[u] = dep[f] + 1, siz[u] = 1;
  for (auto v : G[u]) {
    if (v == f) continue;
    dfs1(v, u);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
}

void dfs2(int u, int ftop) {
  top[u] = ftop, dfn[u] = ++idx, rnk[idx] = u;
  if (son[u]) dfs2(son[u], ftop);
  for (auto v : G[u])
    if (v != son[u] && v != fa[u]) dfs2(v, v);
}
```

## Properties of heavy-light decomposition

**Every node of the tree belongs to exactly one heavy path**.

The first node of a heavy path is never a heavy child (because the first node of a heavy path is either the root or a light child of its parent).

The heavy paths **completely partition** the whole tree.

During the decomposition, **heavy edges are visited first**, so in the final DFS order of the tree, the DFS order within each heavy path is contiguous. Sorting the nodes by DFN gives the decomposed chains.

The DFS order within a subtree is contiguous.

Notice that whenever we go down along a **light edge**, the size of the current subtree is at least halved.

So for any path in the tree, split it into two parts going down from the [LCA](./lca.md) on each side. Each part goes through at most $O(\log n)$ light edges, so every path in the tree can be split into at most $O(\log n)$ heavy paths.

??? info "How to build tests that actually slow down HLD"
    In general, the $O(\log n)$ bound of HLD is rarely tight, so it is hard to make it slow. To make it slow, you would need a binary tree, but then the depth is small.
    
    So we can consider a compromise.
    
    Build a binary tree with $\sqrt{n}$ nodes. Replace each edge from a node to its child with a chain of length $\sqrt{n}$.
    
    This way, a random query switches between light and heavy paths $\frac{\log n}{2}$ times on average, while the depth is $O(\sqrt{n} \log n)$.
    
    Adding some random leaves seems to make HLD slow. But because HLD has a small constant, it may still not be slow enough.

## Common applications

### Maintaining paths

Here is the pseudocode for using HLD to compute the sum of weights on the path between two nodes:

$$
\begin{array}{l}
\text{TREE-PATH-SUM }(u,v) \\
\begin{array}{ll}
1 & \textit{tot}\gets 0 \\
2 & \textbf{while }u.\textit{top}\text{ is not }v.\textit{top} \\
3 & \qquad \textbf{if }u.\textit{top}.\textit{depth}< v.\textit{top}.\textit{depth} \\
4 & \qquad \qquad \text{SWAP}(u, v) \\
5 & \qquad \textit{tot}\gets \textit{tot} + \text{sum of values between }u\text{ and }u.\textit{top} \\
6 & \qquad u\gets u.\textit{top}.\textit{father} \\
7 & \textit{tot}\gets \textit{tot} + \text{sum of values between }u\text{ and }v \\
8 & \textbf{return } \textit{tot} 
\end{array}
\end{array}
$$

The DFS order on a chain is contiguous, so it can be maintained with a segment tree or a Fenwick tree.

Each time, jump up from the chain whose top is deeper, until the two nodes are on the same chain.

The same chain-jumping structure works for maintaining and computing other information on paths.

### Maintaining subtrees

Sometimes we need to maintain information on subtrees, for example adding $v$ to the weights of all nodes in the subtree rooted at $x$.

During the DFS, the DFS orders of the nodes in a subtree are contiguous.

Each node records bottom, the node at the end of the contiguous interval of its subtree.

This turns subtree information into information on one contiguous interval.

### Finding the lowest common ancestor

Keep jumping up along heavy paths. Once both nodes are on the same heavy path, the one with smaller depth is the LCA.

When jumping up, first move the node whose heavy path top is deeper.

Reference code:

```cpp
int lca(int u, int v) {
  while (top[u] != top[v]) {
    if (dep[top[u]] > dep[top[v]])
      u = fa[top[u]];
    else
      v = fa[top[v]];
  }
  return dep[u] > dep[v] ? v : u;
}
```

### Changing the root

Consider a new type of problem: besides the basic operations HLD supports, there is also a root-change operation.

The information HLD maintains is static and does not support dynamic changes. Also, re-preprocessing everything after each root change is too slow. So we need to make full use of the information we already have to handle root changes.

For path modifications and queries, the simple path between two nodes in a tree is unique, so nothing changes, and we handle them as usual.

For subtree modifications and queries, the usual idea is to map the subtree after the root change back to subtrees of the original tree. This needs case analysis on the relative positions of the root of the subtree being operated on, the root of the whole tree after the change, and the root of the original tree. For details, see the [example problem "LOJ 139. Tree Chain Decomposition" below](#example-problems).

## Example problems

This section uses example problems to show how to apply heavy-light decomposition. First, a template problem.

???+ example "['ZJOI2008' Tree Statistics](https://loj.ac/problem/10138)"
    Given a static tree with $n$ weighted nodes, perform $q$ operations of three kinds:
    
    1.  Change the weight of a single node;
    2.  Query the maximum weight on the path from $u$ to $v$;
    3.  Query the sum of weights on the path from $u$ to $v$.
    
    It is guaranteed that $1\le n\le 30000$ and $0\le q\le 200000$.

??? note "Solution"
    From the statement and the properties above, the segment tree needs to support three operations:
    
    1.  Point update;
    2.  Range maximum query;
    3.  Range sum query.
    
    Point update is easy to implement.
    
    Since the DFS order of a subtree is contiguous (this is true with or without HLD), modifying the subtree of a node only requires modifying one contiguous interval of DFS orders.
    
    The question is how to modify/query the path between two nodes.
    
    Recall how we **find the LCA with binary lifting**. First we **lift the two nodes to the same depth, then jump both nodes up together**. The same idea works for HLD.
    
    While jumping up, if the current node is on a heavy path, jump to the top of that heavy path; if it is not on a heavy path, jump up one node. Repeat until the two nodes are the same. Update/query interval information along the way.
    
    Each query passes through at most $O(\log n)$ heavy paths, and the segment tree costs $O(\log n)$ on each one, so the total time complexity is $O(n\log n+q\log^2 n)$. In practice, the number of heavy paths rarely reaches $O(\log n)$ (a complete binary tree can make it tight), so HLD usually has a small constant.

??? note "Reference code"
    ```cpp
    --8<-- "docs/graph/code/hld/hld_1.cpp"
    ```

Next is a heavy-light decomposition template problem with root changes.

???+ example "[LOJ 139. Tree Chain Decomposition](https://loj.ac/p/139)"
    Given a tree with $n$ nodes (the initial root is $1$), support the following $m$ operations:
    
    -   Change root: make node $u$ the new root.
    -   Modify path: add $w$ to the weights of all nodes on the path between $u$ and $v$ (including both nodes).
    -   Modify subtree: add $w$ to the weights of all nodes in the subtree rooted at $u$.
    -   Query path: find the sum of weights of all nodes on the path between $u$ and $v$ (including both nodes).
    -   Query subtree: find the sum of weights of all nodes in the subtree rooted at $u$.
    
    $1 \le n,m \le 10^5$.

??? note "Solution"
    First run a DFS with $1$ as the root to precompute the information HLD needs. For convenience, call the tree rooted at $1$ the "original tree", and the tree after some root changes the "current tree". During the operations, we maintain $\textit{root}$, the root of the current tree. Since the segment tree stores information in the DFS order of the original tree, every query and modification on the current tree must be converted to the original tree.
    
    For a root change, we just set $\textit{root}\gets u$. For path operations, changing the root does not affect paths, so we just perform the operation on the original tree.
    
    The main issue is subtree operations. We split into cases by the relative position of $u$ and $\textit{root}$:
    
    -   $u = \textit{root}$: this is the most special case, and it means operating on the whole tree. So we just put a tag on, or read the answer from, the root of the segment tree.
    -   $u$ is an ancestor of $\textit{root}$ in the original tree, that is, $u$ lies on the simple path from $1$ to $\textit{root}$.
    
        This is the case that needs the most care. Let $v$ be the vertex with the smallest depth, other than $u$, on the simple path from $u$ to $\textit{root}$ in the original tree. Notice that the part of the original tree outside $v$ and its subtree is exactly $u$ and its subtree in the current tree.
    
        How do we find $v$ efficiently? First set $v\gets\textit{root}$, then jump up along heavy paths until $\operatorname{dep}(\operatorname{top}(v))\le\operatorname{dep}(u)+1$.
    
        -   If $\operatorname{dep}(\operatorname{top}(v))=\operatorname{dep}(u)+1$, set $v\gets\operatorname{top}(v)$. Then $v$ is a light child of $u$.
        -   If $\operatorname{dep}(\operatorname{top}(v))<\operatorname{dep}(u)+1$, that is, $\operatorname{dep}(\operatorname{top}(v))\le \operatorname{dep}(u)$, then $u,v$ are on the same heavy path. Since the DFS order is contiguous on one heavy path, the $v$ we want must satisfy $\operatorname{dfn}(v)=\operatorname{dfn}(u)+1$. So we can set $v\gets\operatorname{rnk}(\operatorname{dfn}(u)+1)$.
    
        Note that the two cases can be merged: after jumping, we can directly set
    
        $$
        v\gets\operatorname{rnk}(\operatorname{dfn}(\operatorname{top}(v))+\operatorname{dep}(u)+1-\operatorname{dep}(\operatorname{top}(v))).
        $$
    
        It is easy to check that the $v$ found by this expression is the same as the one found by the case analysis. The reference implementation uses this expression.
    
        Since the subtree of $v$ covers the interval $[\operatorname{dfn}(v),\operatorname{dfn}(v)+\operatorname{siz}(v))$, we only need to operate on $[1,\operatorname{dfn}(v))\cup[\operatorname{dfn}(v)+\operatorname{siz}(v),n]$.
    -   Other cases. Notice that the root change does not affect the subtree of $u$, so we handle it in the normal way.
    
    The complexity of this approach is the same as without root changes: $O(n\log^2 n)$.

??? note "Reference code"
    ```cpp
    --8<-- "docs/graph/code/hld/hld_4.cpp"
    ```

Finally, an interactive problem, which is also a non-traditional application of HLD.

???+ example "[Nauuo and Binary Tree](https://loj.ac/problem/6669)"
    There is a binary tree rooted at $1$. You can ask for the distance between any two nodes. Find the parent of every node.
    
    There are at most $3000$ nodes, and you can make at most $30000$ queries.

??? note "Solution"
    First, we can find the depth of every node with $n-1$ queries.
    
    Then we determine the parents of the nodes in increasing order of depth. This way, when we determine a node's parent, all of its ancestors are already known.
    
    Before determining a node's parent, run heavy-light decomposition on the known part of the tree.
    
    Suppose we need to locate node $k$ within the subtree of $u$. We can ask for the distance between $k$ and the bottom end of the heavy path containing $u$, which narrows down the position of $k$. See the figure:
    
    ![](./images/hld2.png)
    
    The red dashed line is a heavy path, $d$ is the query result, that is, $\textit{dis}(k, \textit{bot}(u))$, and the depth of $v$ is $(\textit{dep}(k)+\textit{dep}(\textit{bot}(u))-d)/2$.
    
    So if $v$ has only one child, the parent of $k$ is $v$; otherwise we recursively look for the parent of $k$ in the subtree of $w$.
    
    The time complexity is $O(n^2)$, and the number of queries is $O(n\log n)$.
    
    More precisely, let $T(n)$ be the number of queries needed in the worst case to locate a new node in a tree of size $n$. Then:
    
    $$
    T(n)\le
    \begin{cases}
    0&n=1\\
    T\left(\left\lfloor\frac{n-1}2\right\rfloor\right)+1&n\ge2
    \end{cases}
    $$
    
    $2999+\sum_{i=1}^{2999}T(i)\le 29940$. In fact, this upper bound can be reached by carefully constructed data, but with a little random perturbation (for example, using an unstable sorting algorithm when sorting by depth), the number of queries rarely exceeds $21000$.

??? note "Reference code"
    ```cpp
    --8<-- "docs/graph/code/hld/hld_2.cpp"
    ```

## Long-path decomposition

Long-path decomposition is essentially just another way of decomposing a tree into chains.

The **heavy child** of a node is now its child whose subtree has the greatest depth. If several children have the greatest subtree depth, pick any one of them. If a node has no children, it has no heavy child.

The **light children** are the remaining children.

The edge from a node to its heavy child is a **heavy edge**.

The edges to its other, light children are **light edges**.

A sequence of heavy edges joined end to end forms a **heavy path** (here also called a long path).

If we also treat each leftover single node as a heavy path, then the whole tree is split into a number of heavy paths.

As shown in the figure (this decomposition can be seen either as a heavy-light decomposition or as a long-path decomposition):

![HLD](./images/hld.png)

Long-path decomposition is implemented in a similar way to heavy-light decomposition, so we won't go into details here.

### Common applications

First, notice that with long-path decomposition, the number of light edges on the path from a node to the root is on the order of $\sqrt{n}$.

??? info "How to build data that makes the number of light/heavy switches as large as possible"
    We can build a binary tree T like this:
    
    Suppose the parameter of the binary tree being built is $D$.
    
    If $D \neq 0$, build a binary tree with parameter $D-1$ as the left child, and a chain of length $2D-1$ as the right child.
    
    If $D = 0$, just build a single leaf node and stop.
    
    With this construction, the path from that single leaf to the root consists entirely of light edges, and the tree needs on the order of $D^2$ nodes.
    
    Just take $D=\sqrt{n}$.

#### Optimizing DP with long-path decomposition

DP that can be optimized with long-path decomposition usually has one dimension of the state that is depth.

We can use long-path decomposition to optimize tree DP.

Specifically, each node directly inherits the DP state of its heavy child, and merges the DP states of its light children by brute force.

???+ example "[Codeforces 1009 F. Dominant Indices](http://codeforces.com/contest/1009/problem/F)"
    Given a rooted tree with $n$ vertices, rooted at vertex $1$.
    
    The depth array of vertex $x$ is an infinite sequence $[d_{x, 0}, d_{x, 1}, d_{x, 2}, \dots]$, where $d_{x, i}$ is the number of vertices $y$ that satisfy both conditions below:
    
    -   $x$ is an ancestor of $y$;
    -   the simple path from $x$ to $y$ has exactly $i$ edges.
    
    The dominant index of the depth array of vertex $x$ (the dominant index of vertex $x$ for short) is the index $j$ such that:
    
    -   for all $k < j$, $d_{x, k} < d_{x, j}$;
    -   for all $k > j$, $d_{x, k} \le d_{x, j}$.
    
    Compute the dominant index of every vertex in the tree.

??? note "Solution"
    Let $f_{i,j}$ be the number of vertices in the subtree of i at distance j from i.
    
    Doing the transitions directly by brute force takes $O(n^2)$ time.
    
    Instead, at each transition we directly inherit the DP array and answer of the heavy child, and update on top of that.
    
    First, we insert an element 1 at the front of the heavy child's DP array; it represents the current node.
    
    Then we merge the DP arrays of all light children into the current node's DP array by brute force.
    
    Notice that the length of a light child's DP array is the length of the long path containing that light child, and the total length of all long paths is $n$.
    
    That is, the total time for merging all light children by brute force is $O(n)$.

??? note "Reference code"
    ```cpp
    --8<-- "docs/graph/code/hld/hld_3.cpp"
    ```

Note that in general, memory for the DP arrays is allocated once for each whole long path, and different nodes on the path get different starting pointers into it.

The length of a DP array can be computed from the deepest node in the subtree.

Of course, there are many tricks for optimizing DP with long-path decomposition, including but not limited to lazy tags. We won't go into them here.

See [Zu Suyu's blog (Chinese)](https://www.cnblogs.com/zhoushuyu/p/9468669.html).

#### Finding the k-th ancestor with long-path decomposition

That is, a query asks which node you reach after jumping from a node to its parent $k$ times.

First, assume we have precomputed the $2^i$-th ancestor of every node.

Now suppose we have found the $2^i$-th ancestor of the queried node, where $2^i \le k < 2^{i+1}$.

Take the nodes of the long path that this ancestor lies on, and list them in a table by depth. Suppose the path has length $d$.

Also, during preprocessing, find the $1$st to $d$-th ancestors of the top node of each long path, and put them in the table as well.

By the properties of long-path decomposition, $k-2^i \le 2^i \leq d$. That is, we can find the $k$-th ancestor of the queried node in $O(1)$ from the table of this path.

Preprocessing needs binary lifting for the $2^i$-th ancestors, and also the table for each long path.

Preprocessing takes $O(n\log n)$ time, and each query takes $O(1)$.

## Exercises

-   ["Luogu P3379" [Template] Lowest Common Ancestor (LCA)](https://www.luogu.com.cn/problem/P3379) (finding the LCA with HLD needs no data structure, so this is good practice)
-   ["JLOI2014" The Squirrel's New Home](https://loj.ac/problem/2236) (it can also be solved with difference arrays on trees)
-   ["HAOI2015" Tree Operations](https://loj.ac/problem/2125)
-   ["Luogu P3384" [Template] Heavy-Light Decomposition](https://www.luogu.com.cn/problem/P3384)
-   ["Luogu P1505" \[National Training Team\] Travel](https://www.luogu.com.cn/problem/P1505)
-   ["NOI2015" Package Manager](https://uoj.ac/problem/128)
-   ["SDOI2011" Coloring](https://www.luogu.com.cn/problem/P2486)
-   ["SDOI2014" Journey](https://hydro.ac/p/bzoj-P3531)
-   ["Luogu P3979" The Distant Country](https://www.luogu.com.cn/problem/P3979)
-   ["POI2014" Hotel (Enhanced Version)](https://hydro.ac/p/bzoj-P4543) (long-path decomposition optimizing DP)
-   [Walkthrough](https://hydro.ac/p/bzoj-P3252) (long-path decomposition optimizing a greedy)
