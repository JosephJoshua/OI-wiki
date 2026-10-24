The longest simple path between any two nodes of a tree is called the "diameter" of the tree.

Prerequisites: [Tree basics](./tree-basic.md).

## Introduction

Clearly, a tree can have several diameters, all of the same length.

We can find the diameter of a tree in $O(n)$ time with either two DFS passes or tree DP.

## Two DFS passes

First run a DFS from any node $y$ and find the node farthest from it; call it $z$. Then run a second DFS from $z$ and find the node farthest from $z$; call it $z'$. Then $\delta(z,z')$ is a diameter of the tree.

Clearly, if the node $z$ reached by the first DFS is an endpoint of a diameter, then the node $z'$ reached by the second DFS must also be an endpoint of a diameter. So we only need to prove that $z$ is always an endpoint of a diameter.

Theorem: in a tree, if we run a DFS from any node $y$, the node $z$ farthest from it must be an endpoint of a diameter.

???+ note "Proof"
    We use proof by contradiction. Let the starting node be $y$. Suppose the true diameter is $\delta(s,t)$, and the farthest node $z$ found by the first DFS from $y$ is neither $t$ nor $s$. There are three cases:
    
    -   $y$ lies on $\delta(s,t)$:
    
    ![y lies on s-t](./images/tree-diameter1.svg)
    
    Then $\delta(y,z) > \delta(y,t) \Longrightarrow \delta(x,z) > \delta(x,t) \Longrightarrow \delta(s,z) > \delta(s,t)$, which contradicts $\delta(s,t)$ being the longest simple path between any two nodes.
    
    -   $y$ is not on $\delta(s,t)$, and $\delta(y,z)$ shares part of its path with $\delta(s,t)$:
    
    ![y is not on s-t, and y-z shares part of its path with s-t](./images/tree-diameter2.svg)
    
    Then $\delta(y,z) > \delta(y,t) \Longrightarrow \delta(x,z) > \delta(x,t) \Longrightarrow \delta(s,z) > \delta(s,t)$, which contradicts $\delta(s,t)$ being the longest simple path between any two nodes.
    
    -   $y$ is not on $\delta(s,t)$, and $\delta(y,z)$ shares no part of its path with $\delta(s,t)$:
    
    ![y is not on s-t, and y-z shares no path with s-t](./images/tree-diameter3.svg)
    
    Then $\delta(y,z) > \delta(y,t) \Longrightarrow \delta(x',z) > \delta(x',t) \Longrightarrow \delta(x,z) > \delta(x,t) \Longrightarrow \delta(s,z) > \delta(s,t)$, which contradicts $\delta(s,t)$ being the longest simple path between any two nodes.
    
    In all three cases the assumption leads to a contradiction, so the theorem is proved.

???+ warning "Negative edge weights"
    The proof above assumes that no path has negative length. If the tree has negative-weight edges, the proof does not hold. So if there are negative edges, you cannot find the diameter with two DFS passes.

If you need all nodes on a diameter, record the predecessor of each node during the second DFS. Then you can walk back from one end of the diameter and visit every node on it.

## Tree DP

### Method 1

Root the tree at $1$. For each node, record the length $d_1$ of the longest path going down from it into its subtree, and the length $d_2$ of the second-longest such path (sharing no edge with the longest one). Then the diameter is the maximum value of $d_1 + d_2$ over all nodes.

Tree DP can find the diameter even when there are negative-weight edges.

If you need all nodes on a diameter, during the DP record, for each node, the children that its longest and second-longest downward paths (defined as above) go through. When computing $d$, also record the node $u$ with $d = d_1[u] + d_2[u]$. Then follow the children of the longest and the second-longest paths starting from $u$, each in its own direction (for an unrooted tree, even though we chose $1$ as the root here, you still need to record which direction each node jumps to; for a rooted tree, just keep jumping up), and you visit every node on the diameter.

### Method 2

Here is a tree DP method that uses only one array.

Define $dp[u]$ as the longest path starting from $u$ within the subtree rooted at $u$. The transition is easy: $dp[u] = \max(dp[u], dp[v] + w(u, v))$, where $v$ is a child of $u$ and $w(u, v)$ is the weight of the edge between them.

The diameter is really the maximum sum of two different paths starting from the same node, over all nodes. So during the DP, just before updating $dp[u]$, compute $d = \max(d, dp[u] + dp[v] + w(u, v))$, and you get the diameter $d$.

## Example problem

???+ example "[Luogu B4016 Diameter of a Tree](https://www.luogu.com.cn/problem/B4016)"
    Given a tree with $n$ nodes, find the length of its diameter. $1\leq n\leq 10^5$.

??? note "Reference implementation with two DFS passes"
    ```cpp
    --8<-- "docs/graph/code/tree-diameter/tree-diameter_1.cpp"
    ```

??? note "Reference implementation of tree DP with two arrays"
    ```cpp
    --8<-- "docs/graph/code/tree-diameter/tree-diameter_2.cpp"
    ```

??? note "Reference implementation of tree DP with one array"
    ```cpp
    --8<-- "docs/graph/code/tree-diameter/tree-diameter_3.cpp"
    ```

## Properties

The diameter of a tree has this property: if all edge weights are positive, then all diameters of the tree share the same midpoint.

???+ note "Proof"
    Proof: by contradiction. Suppose two diameters $\delta(s,t)$ and $\delta(s',t')$ have different midpoints $x$ and $x'$. Clearly, $\delta(s,x) = \delta(x,t) = \delta(s',x') = \delta(x',t')$.
    
    ![In a tree without negative edges, all diameters share the same midpoint](./images/tree-diameter4.svg)
    
    Then $\delta(s,t') = \delta(s,x) + \delta(x,x') + \delta(x',t') > \delta(s,x) + \delta(x,t) = \delta(s,t)$, which contradicts $\delta(s,t)$ being the longest simple path between any two nodes. So the property holds.

## Exercises

-   [CodeChef, Diameter of Tree](https://www.codechef.com/problems/DTREE)
-   [Educational Codeforces Round 35, Problem F, Tree Destruction](https://codeforces.com/contest/911/problem/F)
-   [ZOJ 3820 Building Fire Stations](https://pintia.cn/problem-sets/91827364500/exam/problems/type/7?problemSetProblemId=91827369872&page=28)
-   [CEOI2019/CodeForces 1192B. Dynamic Diameter](https://codeforces.com/contest/1192/problem/B)
-   [ICPC 2019 Shanghai Regional Online Contest Lightning Routing I](https://vjudge.net/problem/%E8%AE%A1%E8%92%9C%E5%AE%A2-A2290)
-   [NOIP2007 Senior Group — Core of a Tree Network](https://www.luogu.com.cn/problem/P1099)
-   [SDOI2011 Firefighting](https://www.luogu.com.cn/problem/P2491)
-   [APIO2010 Patrol](https://www.luogu.com.cn/problem/P3629)
