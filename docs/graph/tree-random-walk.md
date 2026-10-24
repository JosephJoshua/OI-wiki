Given a rooted tree, a coin sits on some node. At each moment the coin moves to one of the adjacent nodes, each with equal probability. We want the expected distance the coin travels to reach an adjacent node.

## Definitions used

-   $T=(V,E)$: the tree under discussion
-   $d(u)$: the degree of node $u$
-   $w(u,v)$: the weight of the edge between nodes $u$ and $v$
-   $p_u$: the parent of node $u$
-   $\textit{root}$: the root of the tree
-   $\textit{son}_u$: the set of children of node $u$
-   $\textit{sibling}_u$: the set of siblings of node $u$

## Expected distance to walk to the parent

Let $f(u)$ be the expected distance for node $u$ to walk to its parent $p_u$. Then:

$$
f(u) = \cfrac{w(u,p_u) + \sum\limits_{v \in \textit{son}_u}(w(u,v) + f(v) + f(u))}{d(u)}
$$

The first part of the numerator is walking straight to the parent. The second part is walking to a child first, coming back from that child, and then walking to the parent. The denominator $d(u)$ reflects that node $u$ moves to each of its neighbors with equal probability.

Simplifying:

$$
\begin{aligned}
    f(u) &= \cfrac{w(u,p_u) + \sum\limits_{v \in \textit{son}_u}(w(u,v) + f(v) + f(u))}{d(u)} \\
         &= \cfrac{w(u,p_u) + \sum\limits_{v \in \textit{son}_u}(w(u,v) + f(v)) + (d(u)-1)f(u)}{d(u)} \\
         &= w(u,p_u) + \sum\limits_{v \in \textit{son}_u}(w(u,v) + f(v)) \\
         &= \sum\limits_{(u,t) \in E}w(u,t) + \sum\limits_{v \in \textit{son}_u}f(v)
\end{aligned}
$$

For a leaf $l$, the initial value is $f(l) = w(p_l, l)$.

When every edge in the tree has weight $1$, the formula becomes:

$$
f(u) = d(u) + \sum\limits_{v \in \textit{son}_u}f(v)
$$

That is, the sum of the degrees of all nodes in $u$'s subtree, which is twice the size of $u$'s subtree, $-1$ (each node has exactly one edge to its parent; every edge contributes $2$ to the degree sum, except the edge between $u$ and $p_u$, which contributes only $1$).

## Expected distance to walk to a child

Let $g(u)$ be the expected distance for node $p_u$ to walk to its child $u$. Then:

$$
g(u) = \cfrac{w(p_u,u) + \left(w(p_u,p_{p_u})+g(p_u)+g(u)\right) + \sum\limits_{s \in \textit{sibling}_u}(w(p_u,s)+f(s)+g(u))}{d(p_u)}
$$

The first part of the numerator is walking straight to the child $u$. The second part is walking to the parent first, coming back from it, and then walking to $u$. The third part is walking to a sibling of $u$ first, coming back from it, and then walking to $u$. The denominator $d(p_u)$ reflects that node $p_u$ moves to each of its neighbors with equal probability.

Simplifying:

$$
\begin{aligned}
    g(u) &= \cfrac{w(p_u,u) + \left(w(p_u,p_{p_u})+g(p_u)+g(u)\right) + \sum\limits_{s \in \textit{sibling}_u}(w(p_u,s)+f(s)+g(u))}{d(p_u)} \\
         &= \cfrac{w(p_u,u) + w(p_u,p_{p_u}) + g(p_u) + \sum\limits_{s \in \textit{sibling}_u}\left(w(p_u,s)+f(s)\right)+(d(p_u)-1)g(u)}{d(p_u)} \\
         &= w(p_u,u) + w(p_u,p_{p_u}) + g(p_u) + \sum\limits_{s \in \textit{sibling}_u}(w(p_u,s)+f(s)) \\
         &= \sum\limits_{(p_u,t) \in E}w(p_u,t) + g(p_u) + \sum\limits_{s \in \textit{sibling}_u}f(s) \\
         &= \sum\limits_{(p_u,t) \in E}w(p_u,t) + g(p_u) + \left(f(p_u)-\sum\limits_{(p_u,t) \in E}w(p_u,t)-f(u)\right) \\
         &= g(p_u) + f(p_u) - f(u)
\end{aligned}
$$

The initial value is $g(\text{root}) = 0$.

## Implementation (for an unweighted tree)

```cpp
vector<int> G[MAXN];

void dfs1(int u, int p) {
  f[u] = G[u].size();
  for (auto v : G[u]) {
    if (v == p) continue;
    dfs1(v, u);
    f[u] += f[v];
  }
}

void dfs2(int u, int p) {
  if (u != root) g[u] = g[p] + f[p] - f[u];
  for (auto v : G[u]) {
    if (v == p) continue;
    dfs2(v, u);
  }
}
```
