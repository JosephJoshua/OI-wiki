A chordal graph is a special kind of graph. Many problems that are NP-hard on general graphs have excellent linear-time algorithms on chordal graphs.

## Some definitions and properties

**Subgraph**: a graph whose vertex set and edge set are subsets of the original graph's vertex set and edge set.

**Induced subgraph**: a graph whose vertex set is a subset of the original vertex set, and whose edge set consists of all edges **with both endpoints in the chosen vertex set**.

**Clique**: a complete subgraph.

**Maximal clique**: a clique that is not a subgraph of any other clique.

**Maximum clique**: a clique with the most vertices.

**Clique number**: the number of vertices in a maximum clique, written $\omega(G)$.

**Minimum coloring**: coloring the vertices with as few colors as possible so that the two endpoints of every edge have different colors.

**Chromatic number**: the number of colors in a minimum coloring, written $\chi(G)$.

**Maximum independent set**: a largest vertex set in which no two vertices are joined by an edge. Its size is written $\alpha(G)$.

**Minimum clique cover**: covering all vertices with as few cliques as possible. The number of cliques used is written $\kappa(G)$.

**Chord**: an edge joining two non-adjacent vertices of a cycle.

**Chordal graph**: a graph in which every cycle of length greater than $3$ has a chord.

**Lemma 1**: clique number $\omega(G)\le \chi(G)$ chromatic number

Proof: coloring just the induced subgraph of a maximum clique already needs at least $\omega(G)$ colors.

**Lemma 2**: maximum independent set size $\alpha(G)\le \kappa(G)$ minimum clique cover size

Proof: each clique contains at most one vertex of the independent set.

**Lemma 3**: every induced subgraph of a chordal graph is a chordal graph.

Proof: if some induced subgraph of a chordal graph were not chordal, it would contain a chordless cycle of length greater than $3$. Then no matter what the rest of the original graph looks like (however edges are added), the original graph could not be chordal, a contradiction.

**Lemma 4**: no induced subgraph of a chordal graph can be a cycle with more than $3$ vertices.

Proof: a cycle with more than $3$ vertices is not chordal; apply the lemma above.

## Recognizing chordal graphs

### Problem statement

Given an undirected graph, decide whether it is chordal.

### Vertex separators

For two vertices $u,v$ of a graph $G$, a **vertex separator** of $u,v$ is a set of vertices whose deletion disconnects $u$ from $v$. If no proper subset of a vertex separator of $u,v$ is a vertex separator, it is called a **minimal vertex separator**.

**Lemma 5**: a minimal vertex separator of $u,v$ splits the graph into several connected components. Let $V_1$ be the component containing $u$ and $V_2$ the component containing $v$. Then for every vertex $a$ in the minimal separator, $N(a)$ contains vertices from both $V_1$ and $V_2$.

Proof: if $N(a)$ contains vertices from at most one of $V_1$ and $V_2$, then removing $a$ from the separator still leaves $u,v$ disconnected, so the original separator was not minimal.

**Lemma 6**: in a chordal graph, the induced subgraph of any minimal vertex separator between two vertices is a clique.

Proof: if the minimal separator has size $\le 1$, its induced subgraph is trivially a clique.

Otherwise, let $x,y$ be two vertices of the minimal separator. By **Lemma 5**, $N(x)$ contains vertices from $V_1$ and $V_2$; call them $x_1,x_2$. Similarly define $y_1,y_2$. Note that $x_1=y_1,x_2=y_2$ is possible.

Since $V_1$ and $V_2$ are both connected, there are shortest paths between $x_1,y_1$ and between $x_2,y_2$. Let the shortest paths from $x$ to $y$ through $V_1$ and $V_2$ be $x-x_1\sim y_1-y,x-x_2\sim y_2-y$. Then the graph contains the cycle $x-x_1\sim y_1-y-y_2\sim x_2-x$, whose length is $\ge 4$. By the definition of a chordal graph, this cycle has a chord.

If the chord joined $V_1$ and $V_2$, the set would not be a separator. If the chord joined two vertices inside one component, or a vertex inside a component and a vertex of the separator, it would contradict the paths being shortest. So the chord can only join $x$ and $y$.

Hence any two vertices of a minimal separator in a chordal graph are joined by an edge, which proves the property.

### Simplicial vertices

Let $N(x)$ be the set of vertices adjacent to $x$. If the induced subgraph of $\{x\}+N(x)$ is a clique, $x$ is called a simplicial vertex.

**Lemma 7**: every chordal graph has at least one simplicial vertex, and every chordal graph that is not complete has at least two non-adjacent simplicial vertices.

Proof: by induction. Consider each connected component separately.

Base case: if the graph is isomorphic to a complete graph, every vertex is simplicial. If the graph has $\le 3$ vertices, the lemma holds.

If the graph has $\ge 4$ vertices and is not complete, there must be $u,v$ with $(u,v)\notin E$. Let $I$ be a minimal vertex separator of $u,v$. Let $A,B$ be the components containing $u$ and $v$ in the induced subgraph after deleting $I$. By symmetry we only consider the side of $A$. Let $L=A+I$. If $L$ is complete, then $u$ is simplicial. Otherwise, since $L$ is an induced subgraph of the original graph, it is also chordal and so has two non-adjacent simplicial vertices. Since $I$ is a clique, any two of its vertices are adjacent, so $A$ must contain a simplicial vertex. That vertex is also simplicial in the whole graph.

Each step splits the graph into several connected components, whose sizes are strictly smaller and which all satisfy the property, so the induction holds.

### Perfect elimination ordering

Let $n=|V|$. A perfect elimination ordering $v_1,v_2,\ldots ,v_n$ is a permutation of $1,2,\ldots ,n$ such that $v_i$ is simplicial in the induced subgraph of $\{v_i,v_{i+1},\ldots ,v_n\}$.

**Lemma 8**: an undirected graph is chordal if and only if it has a perfect elimination ordering.

Sufficiency: a chordal graph with $1$ vertex has a perfect elimination ordering. By **Lemma 3** and **Lemma 7**, a perfect elimination ordering of a chordal graph with $n$ vertices can be obtained from one of a chordal graph with $n-1$ vertices plus one simplicial vertex.

Necessity: suppose an undirected graph has a (chordless) cycle with $>3$ vertices and also has a perfect elimination ordering. Let $v$ be the first vertex of the cycle to appear in the ordering, and let $v_1,v_2$ be its neighbors on the cycle. By the property of the ordering, that is, the definition of a simplicial vertex, $v_1$ and $v_2$ are joined by an edge, a contradiction.

### Naive algorithm

Each time, find a **simplicial vertex** $v$ and append it to the perfect elimination ordering.

Delete $v$ and its incident edges from the graph.

Repeat. If all vertices get deleted, the graph is chordal and we have found a perfect elimination ordering; if at some point no simplicial vertex exists, the graph is not chordal.

The time complexity is $O(n^4)$.

### MCS algorithm

**Maximum Cardinality Search** (MCS) finds a perfect elimination ordering of an undirected graph in $O(n+m)$ time.

We number the vertices in reverse, that is, assign labels from $n$ down to $1$.

Let $label_x$ be the number of already-numbered vertices adjacent to vertex $x$. Each time, pick an unnumbered vertex with the largest $label$ and number it.

Use linked lists to keep, for each $i$, the vertices $x$ with $label_x=i$.

Since each edge contributes at most $2$ to $\sum_{i=1}^n label_i$, the time complexity is $O(n+m)$.

**Proof of correctness**:

Let $\alpha(x)$ be the position of $x$ in the ordering.
We need to show that for every chordal graph, the ordering found by the algorithm is a perfect elimination ordering, that is, all vertices after a vertex in the ordering and adjacent to it are pairwise adjacent.

**Lemma 9**: consider three vertices $u,v,w$ with $\alpha(u)<\alpha(v)<\alpha(w)$. If $uw$ is an edge and $vw$ is not, then $w$ contributes to the $label$ of $u$ but not of $v$. For $v$ to enter the ordering before $u$, there must be some $x$ with $\alpha(v)<\alpha(x)$ such that $vx$ is an edge and $ux$ is not, that is, $x$ contributes to $v$ but not to $u$.

**Lemma 10**: no chordal graph has a sequence $v_0,v_1,\dots,v_k(k\ge 2)$ with all of the following properties:

1.  $v_iv_j$ is an edge if and only if $|i-j|=1$.
2.  $\alpha(v_0)>\alpha(v_i)(i\in[1,k])$.
3.  There is $i\in[1,k-1]$ with $\alpha(v_i)<\alpha(v_{i+1})<\dots<\alpha(v_k)$ and $\alpha(v_i)<\alpha(v_{i-1})<\dots<\alpha(v_1)<\alpha(v_k)<\alpha(v_0)$.

Proof:

Since $\alpha(v_1)<\alpha(v_k)<\alpha(v_0)$, $v_1v_0$ is an edge, and $v_kv_0$ is not, by Lemma 9 there is an $x$ with $\alpha(v_k)<\alpha(x)$ such that $v_kx$ is an edge and $v_1x$ is not.

Take the smallest $j\in(1,k]$ such that $v_jx$ is an edge. Then $v_0x$ is not an edge, otherwise $v_0v_1\cdots v_jx$ would form a chordless cycle of length $\ge 4$.

If $x<v_0$, then $v_0,v_1,\dots,v_j,x$ is also a sequence with these properties; if $v_0<x$, then $x,v_j,\dots,v_1,v_0$ is also such a sequence.

In this argument we increased $\min(v_0,v_k)$. Repeating it forever must eventually lead to a contradiction.

**Theorem 1**: for every chordal graph, the ordering found by maximum cardinality search is a perfect elimination ordering.

Proof: take any three vertices $u,v,w$ with $\alpha(u)<\alpha(v)<\alpha(w)$. We need to show that if $uv$ and $uw$ are edges, then $vw$ is an edge.

Suppose for contradiction it is not. Then $w,u,v$ is a sequence with the properties in **Lemma 10**, but we proved no such sequence exists. This is a contradiction, so $vw$ is an edge.

???+ note "Reference implementation"
    ```cpp
    --8<-- "docs/graph/code/chord/chord_1.cpp:var"
    --8<-- "docs/graph/code/chord/chord_1.cpp:mcs"
    ```

If the graph is chordal, the ordering found is a perfect elimination ordering. But the graph may not be chordal, in which case the ordering is certainly not a perfect elimination ordering. So the problem becomes **checking whether the found ordering is a perfect elimination ordering of the graph**.

### Checking whether an ordering is a perfect elimination ordering

#### Naive algorithm

By definition, for each $v_i$ in the ordering $v$, check whether the vertices among $\{v_i,v_{i+1},\ldots ,v_n\}$ adjacent to $v_i$ form a clique. The time complexity is $O(nm)$.

#### Optimized algorithm

Let $N^+(u)$ be the set of vertices adjacent to $u$ that come after $u$ in the ordering, and let $f(u)$ be the earliest of them in the ordering. For each vertex $u$ with non-empty $N^+(u)$, we only need to check that every vertex in $N^+(u)\setminus\{f(u)\}$ is adjacent to $f(u)$.

This condition is clearly necessary. Sufficiency follows by induction from the back of the ordering to the front: if all later vertices satisfy the perfect elimination requirement, then $N^+(f(u))$ is a clique. When the check passes, $N^+(u)\setminus\{f(u)\}\subseteq N^+(f(u))$ and all its vertices are adjacent to $f(u)$, so $N^+(u)$ is a clique too. When $N^+(u)$ is empty, nothing needs checking.

First scan the adjacency lists to compute $f(u)$ for each vertex, and group vertices with the same $f(u)$. To process the group with $f(u)=v$, first mark all neighbors of $v$, then scan the adjacency list of each $u$ in the group and check that all its neighbors after $v$ in the ordering are marked. Using the vertex id $v$ as the mark value means we never have to clear the mark array between groups. Each vertex belongs to at most one group, and each adjacency list is scanned at most once each for computing $f(u)$, setting marks and checking, so the total time complexity is $O(n+m)$.

???+ note "Reference implementation"
    ```cpp
    --8<-- "docs/graph/code/chord/chord_1.cpp:var"
    --8<-- "docs/graph/code/chord/chord_1.cpp:core"
    ```

So the **chordal graph recognition problem** can be solved in $O(n+m)$ time.

## Maximal cliques of a chordal graph

Let $N(x)$ be the set of vertices adjacent to $x$ that come after $x$ in the perfect elimination ordering. Then every maximal clique of a chordal graph has the form $\{x\}+N(x)$.

Proof: take a maximal clique $V$ of the chordal graph, and let $x$ be its first vertex in the perfect elimination ordering. Then $V\subseteq \{x\}+N(x)$, and since $V$ is maximal, $V=\{x\}+N(x)$.

A chordal graph has at most $n$ maximal cliques. To find all of them, we check whether each $\{x\}+N(x)$ is a maximal clique.

Let $A=\{x\}+N(x),B=\{y\}+N(y)$. If $A\subsetneqq B$, then $A$ is not a maximal clique. In that case $y$ clearly comes before $x$ in the perfect elimination ordering.

Let $nxt_x$ be the earliest vertex of $N(x)$ in the perfect elimination ordering, and let $y*$ be the latest among all $y$ with $A\subseteq B$. Then $nxt_{y*}=x$ must hold; otherwise $y*$ would not be the latest, since $y*=nxt_{y*}$ would still satisfy the condition.

$A\subsetneqq B$ if and only if $|A|+1\le |B|$.

The problem becomes checking whether some $y$ has $nxt_y=x$ and $|N(x)|+1\le |N(y)|$. The time complexity is $O(n+m)$.

```cpp
for (int i = 1; i <= n; i++) {
  cur = 0;
  for (vector<int>::iterator it = G[p[i]].begin(); it != G[p[i]].end(); it++)
    if (rnk[p[i]] < rnk[*it]) {
      s[++cur] = *it;
      if (rnk[s[cur]] < rnk[s[1]]) swap(s[1], s[cur]);
    }
  fst[p[i]] = s[1];
  N[p[i]] = cur;
}
for (int i = 1; i <= n; i++) {
  if (!vis[p[i]]) ans++;
  if (N[p[i]] >= N[fst[p[i]]] + 1) vis[fst[p[i]]] = true;
}
```

## Chromatic number / clique number of a chordal graph

One construction: go through the perfect elimination ordering from back to front and give each vertex the smallest color it can take. The time complexity is $O(m+n)$.

Proof of correctness: suppose this method uses $t$ colors; then $t\ge \chi(G)$. Since all vertices of a clique get different colors, $t=\omega(G)$, and by **Lemma 1**, $t=\omega(G)\le \chi(G)$. Together, $t=\chi(G)=\omega(G)$.

If we only need the chromatic number / clique number and not the coloring itself, we can take the maximum of $|\{x\}+N(x)|$.

```cpp
for (int i = 1; i <= n; i++) ans = max(ans, deg[i] + 1);
```

## Maximum independent set / minimum clique cover of a chordal graph

Maximum independent set: go through the perfect elimination ordering from front to back, and pick every vertex that has no edge to an already picked vertex.

Minimum clique cover: if the maximum independent set is $\{v_1,v_2,\ldots ,v_t\}$, then the set of cliques $\{\{v_1+N(v_1)\},\{v_2+N(v_2)\},\ldots ,\{v_t+N(v_t)\} \}$ is a minimum clique cover of the graph. Both take $O(n+m)$ time.

Proof of correctness: let $t$ be the size of the independent set and the clique cover above. By definition $t\le \alpha(G),t\ge \kappa(G)$, and by **Lemma 2**, $\alpha(G)\le \kappa(G)$, so $t=\alpha(G)=\kappa(G)$.

```cpp
for (int i = 1; i <= n; i++)
  if (!vis[p[i]]) {
    ans++;
    for (vector<int>::iterator it = G[p[i]].begin(); it != G[p[i]].end(); it++)
      vis[*it] = true;
  }
```

## Exercises

[Library Checker - Chordal Graph Recognition](https://judge.yosupo.jp/problem/chordal_graph_recognition)

[SPOJ FISHNET - Fishing Net](https://www.spoj.com/problems/FISHNET)

[P3196\[HNOI2008\] The Magical Country](https://www.luogu.com.cn/problem/P3196)

[P3852\[TJOI2007\] Children](https://www.luogu.com.cn/problem/P3852)

## References

[On chordal graphs](https://yhx-12243.github.io/OI-transit/memos/15.html)

[2009 WC lecture slides](https://github.com/hzwer/shareOI/blob/master/%E5%9B%BE%E8%AE%BA/%E5%BC%A6%E5%9B%BE%E4%B8%8E%E5%8C%BA%E9%97%B4%E5%9B%BE_%E9%99%88%E4%B8%B9%E7%90%A6.pptx)

[Chordal graph summary - zhoushuyu](https://www.cnblogs.com/zhoushuyu/p/8716935.html)

[R. E. Tarjan and M. Yannakakis, Simple linear-time algorithms to test chordality of graphs,test acyclicity of hypergraphs,and selectively reduce acyclic hypergraphs, SIAM J. Comput., 13 (1984), pp. 566–579.](https://dl.acm.org/doi/abs/10.1137/0213035)
