## Preface

In 1959, Reese T. Prosser introduced the concept of "dominance" in [a paper on network flow](http://portal.acm.org/ft_gateway.cfm?id=1460314&type=pdf&coll=GUIDE&dl=GUIDE&CFID=79528182&CFTOKEN=33765747), but he did not give a concrete algorithm for computing it. It was not until 1969 that Edward S. Lowry and C. W. Medlock first proposed [an efficient algorithm](http://portal.acm.org/ft_gateway.cfm?id=362838&type=pdf&coll=GUIDE&dl=GUIDE&CFID=79528182&CFTOKEN=33765747). The Lengauer–Tarjan algorithm, which is the most widely used today, was proposed by Lengauer and Tarjan in 1979 in [a paper](https://www.cs.princeton.edu/courses/archive/fall03/cs528/handouts/a%20fast%20algorithm%20for%20finding.pdf).

In the OI community, the dominator tree was first introduced in [ZJOI2012 Catastrophe](https://www.luogu.com.cn/problem/P2597), where it was also called the "extinction tree". Chen Sunli also introduced this algorithm in his 2020 Chinese national training team paper.

Dominator trees are not popular in competitive programming yet, and there are few related exercises. However, they are widely used in industry, especially in compilers.

This article introduces the concept of the dominator tree and several ways to compute it.

## Dominance

Fix an entry vertex $s$ in an arbitrary directed graph. For a vertex $u$, if every path from $s$ to $u$ passes through some vertex $v$, we say that $v$  **dominates**  $u$, or that $v$ is a **dominator** of $u$, written $v\ dom\ u$.

Dominance makes no sense for vertices that cannot be reached from $s$. So unless stated otherwise, this article assumes that $s$ can reach every vertex in the graph.

![](images/dom-tree1.png)

For example, in this directed graph, $2$ is dominated by $1$, $3$ is dominated by $1, 2$, 4 is dominated by $1, 2, 3$, 5 is dominated by $1, 2$, etc.

### Lemmas

In the lemmas below, we assume $u, v, w\ne s$

**Lemma 1:** $s$ dominates every vertex, and every vertex dominates itself.

**Proof:** Clearly, every path from $s$ to $u$ must pass through both $s$ and $u$.

**Lemma 2:** The dominance relation obtained by considering only simple paths is the same as the one obtained by considering all paths.

**Proof:** For a non-simple path, let $S$ be the set of vertices visited between two visits to the same vertex. If we delete the vertices of $S$ from the path, each non-simple path corresponds to a simple path.

A vertex in $S$ that lies on the non-simple path but not on the simple path can never be a dominator, because at least one simple path from $s$ to $u$ does not contain it. A vertex that lies on both the simple and the non-simple path only needs to be considered on the simple path.

So removing non-simple paths does not affect the dominance relation.

**Lemma 3:** If $u$  $dom$  $v$ and $v$  $dom$  $w$, then $u$  $dom$  $w$.

**Proof:** Every path through $w$ must pass through $v$, and every path through $v$ must pass through $u$. So every path through $w$ must pass through $u$, that is, $u \ dom \ w$.

**Lemma 4:** If $u \ dom \ v$ and $v \ dom\ u$, then $u=v$.

**Proof:** Suppose $u \ne v$. Then any path reaching $v$ has already reached $u$, and any path reaching $u$ has already reached $v$, which is a contradiction.

**Lemma 5:** If $u \ne v \ne w$, $u \ dom \ w$ and $v \ dom \ w$, then $u \ dom \ v$ or $v \ dom \ u$.

**Proof:** Consider a path $s \rightarrow \dots \rightarrow u \rightarrow \dots \rightarrow v \rightarrow \dots \rightarrow w$. If neither of $u$, $v$ dominates the other, there must be a path from $s$ to $v$ that avoids $u$, so there is a path $s \rightarrow \dots \rightarrow v \rightarrow \dots \rightarrow w$ that avoids $u$. This contradicts $u\ dom\ w$.

### Computing dominance

#### Vertex deletion method

A statement equivalent to the definition: if we delete a vertex from the graph and some vertices become unreachable, then the deleted vertex dominates exactly those vertices that became unreachable.

So we just try deleting each vertex and run a DFS. The time complexity is $O(n^3)$. The core code is below.

```cpp
// Assume the graph has n vertices and the start vertex is s = 1
std::bitset<N> vis;
std::vector<int> edge[N];
std::vector<int> dom[N];

void dfs(int u, int del) {
  vis[u] = true;
  for (int v : edge[u]) {
    if (v == del or vis[v]) {
      continue;
    }
    dfs(v, del);
  }
}

void getdom() {
  for (int i = 2; i <= n; ++i) {
    vis.reset();
    dfs(1, i);
    for (int j = 1; j <= n; ++j) {
      if (!vis[j]) {
        dom[j].push_back(i);
      }
    }
  }
}
```

#### Iterative data-flow method

The iterative data-flow method is also uncommon in OI, so we first give a short introduction.

Data-flow analysis is a concept from compiler theory. It analyzes how data flows along the execution paths of a program. The iterative data-flow method writes equations on the nodes of a program's flow graph and solves them by repeated iteration, to obtain the data-flow values at certain points of the program. Here we treat the directed graph as a program flow graph.

In this problem, the equation is:

$$
dom(u)=\{u\} \cup \left(\bigcap_{v\in pre(u)}{dom(v)}\right)
$$

Here $pre(u)$ is the set of predecessors of $u$. This equation follows from Lemma 3.

In plain words: the set of dominators of a vertex is the intersection of the dominator sets of all its predecessors, plus the vertex itself. We use this equation to update the dominator set of each vertex over and over until nothing changes.

For efficiency, we want all predecessors of the current vertex to have finished the current round before it is processed, as far as possible. So we use a depth-first ordering to get the reverse postorder of the graph, and iterate in that order.

A reference implementation of the core code is below. It needs the predecessor set of each vertex and the reverse postorder of the graph to be computed beforehand. That is not the main topic of this article, so we do not give code for it here.

```cpp
std::vector<int> pre[N];  // predecessors of each vertex
std::vector<int> ord;     // reverse postorder of the graph
std::bitset<N> dom[N];
std::vector<int> Dom[N];

void getdom() {
  dom[1][1] = true;
  flag = true;
  while (flag) {
    flag = false;
    for (int u : ord) {
      std::bitset<N> tmp;
      tmp[u] = true;
      for (int v : pre[u]) {
        tmp &= dom[v];
      }
      if (tmp != dom[u]) {
        dom[u] = tmp;
        flag = true;
      }
    }
  }
  for (int i = 2; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (dom[i][j]) {
        Dom[i].push_back(j);
      }
    }
  }
}
```

It is easy to see that the complexity of the algorithm above is $O(n^2)$.

## Dominator tree

From the previous section, every vertex other than $s$ has at least two dominators: $s$ and itself.

Among the dominators of a vertex $u$ other than $u$ itself, the one closest to $u$, say $v$, is called the immediate dominator of $u$, written $idom(u) = v$. Clearly every vertex except $s$ has exactly one immediate dominator, and $s$ has none.

For every vertex $u$ other than $s$, add an edge from $idom(u)$ to $u$. This gives a directed graph with $n$ vertices and $n - 1$ edges. By Lemmas 3 and 4, the dominance relation never forms a loop, so these edges never form a cycle. Hence the graph is actually a tree. We call this tree the **dominator tree** of the original graph.

## Computing the dominator tree

### From dom

Consider the dominator set $\{s_1, s_2, \dots, s_k\}$ of some vertex. There must be a path $s \rightarrow \dots \rightarrow s_1 \rightarrow \dots \rightarrow s_2 \rightarrow \dots \rightarrow \dots \rightarrow s_k \rightarrow\dots \rightarrow u$. Clearly the immediate dominator of $u$ is $s_k$. So the definition of the immediate dominator is equivalent to:

For the dominator set $S$ of a vertex $u$, if $v \in S$ satisfies $\forall w \in S\setminus\{u,v\}, w\ dom \ v$, then $idom(u)=v$.

So after computing the dominator set of each vertex with the algorithms above, we can easily get each vertex's immediate dominator from this definition and build the dominator tree. Reference code is below.

```cpp
std::bitset<N> dom[N];
std::vector<int> Dom[N];
int idom[N];

void getidom() {
  for (int u = 2; u <= n; ++u) {
    for (int v : Dom[u]) {
      std::bitset<N> tmp = (dom[v] & dom[u]) ^ dom[u];
      if (tmp.count() == 1 and tmp[u]) {
        idom[u] = v;
        break;
      }
    }
  }
  for (int u = 2; u <= n; ++u) {
    e[idom[u]].push_back(u);
  }
}
```

### Special case: trees

Clearly, the dominator tree of a tree is the tree itself.

### Special case: DAGs

DAGs have a nice property: if we solve in topological order, results computed earlier are not affected by later ones. We can use this to compute the dominator tree of a DAG quickly.

???+ warning "Note"
    Note that the DAG here can have only one source. If there are several sources, a vertex dominated by the sources would have several parents in the "dominator tree", so the dominance relation can no longer be described simply by a dominator tree.

**Lemma 6:** In a directed graph, $v\ dom\ u$ if and only if $\forall w \in pre(u), v\ dom \ w$.

**Proof:** First, sufficiency. Every path from $s$ to $u$ must pass through some vertex $w \in pre(u)$, and $v$ dominates that vertex. So every path from $s$ to $u$ must pass through $v$, and we get $v \ dom \ u$.

Next, necessity. If $\exists w\in pre(u)$ such that $v$ does not dominate $w$, then there is a path $s \rightarrow \cdots \rightarrow w \rightarrow \cdots \rightarrow u$ that avoids $v$, so $v$ does not dominate $u$.

So the dominators of $u$ are exactly the common ancestors of all its predecessors in the dominator tree. Clearly the immediate dominator of $u$ is the LCA of all its predecessors in the dominator tree. Binary lifting LCA supports adding one vertex at a time, so the algorithm above clearly works.

A reference implementation is below:

```cpp
std::stack<int> sta;
std::vector<int> e[N], g[N], tree[N];  // g is the reverse graph, tree is the dominator tree
int n, s, in[N], tpn[N], dep[N], idom[N];  // n: number of vertices, s: start vertex, in: in-degree
int fth[N][17];

void topo(int s) {
  sta.push(s);
  while (!sta.empty()) {
    int u = sta.top();
    sta.pop();
    tpn[++tot] = u;
    for (int v : e[u]) {
      --in[v];
      if (!in[v]) {
        sta.push(v);
      }
    }
  }
}

int lca(int u, int v) {
  if (dep[u] < dep[v]) {
    std::swap(u, v);
  }
  for (int i = 15; i >= 0; --i) {
    if (dep[fth[u][i]] >= dep[v]) {
      u = fth[u][i];
    }
  }
  if (u == v) {
    return u;
  }
  for (int i = 15; i >= 0; --i) {
    if (fth[u][i] != fth[v][i]) {
      u = fth[u][i];
      v = fth[v][i];
    }
  }
  return fth[u][0];
}

void build() {
  topo(s);
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j <= 15; ++j) fth[i][j] = s;
  for (int i = 1; i <= n; ++i) {
    int u = tpn[i];
    if (g[u].size()) {
      int v = g[u][0];
      for (int j = 1, q = g[u].size(); j < q; ++j) {
        v = lca(v, g[u][j]);
      }
      tree[v].push_back(u);
      fth[u][0] = v;
      dep[u] = dep[v] + 1;
      for (int i = 1; i <= 15; ++i) {
        fth[u][i] = fth[fth[u][i - 1]][i - 1];
      }
    }
  }
}

```

### Lengauer–Tarjan algorithm

The Lengauer–Tarjan algorithm is one of the best-known algorithms for computing dominator trees. It finds the dominator tree of a directed graph in $O(n\alpha(n, m))$ time. It introduces the concept of the **semi-dominator** and uses semi-dominators to help find immediate dominators.

#### Conventions

First, run a DFS on the directed graph starting from $s$. The vertices and edges visited form a tree $T$. We call the edges used tree edges, and the other edges non-tree edges. Let $dfn(u)$ be the visiting order of vertex $u$ (it is the $dfn(u)$-th vertex visited). Define $u<v$ if and only if $dfn(u) < dfn(v)$.

#### Semi-dominators

The semi-dominator of a vertex $u$ is the smallest vertex $v$ such that there is a path from $v$ to $u$ on which every vertex other than $u$ and $v$ is greater than $u$. Formally, the semi-dominator $sdom(u)$ of $u$ is defined as:

$sdom(u) = \min(v|\exists v=v_0 \rightarrow v_1 \rightarrow\dots \rightarrow v_k = u, \forall 1\le i\le k - 1, v_i > u)$

Semi-dominators have some useful properties:

**Lemma 7:** For every vertex $u$, $sdom(u) < u$.

**Proof:** From the definition, the parent $fa(u)$ of $u$ in $T$ also qualifies as a semi-dominator candidate, and $fa(u) < u$. So no vertex greater than $u$ can be its semi-dominator.

**Lemma 8:** For every vertex $u$, $idom(u)$ is an ancestor of $u$ in $T$.

**Proof:** The path from $s$ to $u$ in $T$ corresponds to a path in the original graph, so $idom(u)$ must be on this path.

**Lemma 9:** For every vertex $u$, $sdom(u)$ is an ancestor of $u$ in $T$.

**Proof:** Suppose $sdom(u)$ is not an ancestor of $u$. Then $sdom(u)$ cannot have an edge to any vertex whose $\mathrm{dfs}$ order is at least that of $u$ (otherwise that vertex would be in the subtree of $sdom(u)$, not in another subtree), which is a contradiction.

**Lemma 10:** For every vertex $u$, $idom(u)$ is an ancestor of $sdom(u)$.

**Proof:** We can go from $s$ to $sdom(u)$ and then follow the path from the definition to reach $u$. By definition, no vertex on the path from $sdom(u)$ to $u$ dominates $u$, so $idom(u)$ must be an ancestor of $sdom(u)$.

**Lemma 11:** For any vertices $u \ne v$ where $v$ is an ancestor of $u$, either $v$ is an ancestor of $idom(u)$, or $idom(u)$ is an ancestor of $idom(v)$.

**Proof:** For any vertex $w$ between $v$ and $idom(v)$, by the definition of the immediate dominator, there must be a path from $s$ to $idom(v)$ and then to $v$ that avoids $w$. So none of these vertices $w$ can be $idom(u)$. Hence $idom(u)$ is either a descendant of $v$ or an ancestor of $idom(v)$.

From the lemmas above, we get the following theorem:

**Theorem 1:** The semi-dominator of a vertex $u$ is the smallest among: its predecessors that are smaller than $u$, and the semi-dominators of all ancestors (in $T$) greater than $u$ of its predecessors. Formally, $sdom(u)=\min(\{v|\exists v \rightarrow u, v < u \} \cup \{sdom(w) | w > u\ and\ \exists w \rightarrow \dots \rightarrow v \rightarrow u \})$.

**Proof:** Let $x$ be the right-hand side of the equation.

First we prove $sdom(u) \le x$. By Lemma 7, this is equivalent to proving that both kinds of candidates satisfy the condition for being a semi-dominator. The case where $x$ is a predecessor of $u$ is obvious. For the second part, we join the path $x=v_0\rightarrow\dots\rightarrow v_j=w$ described in the definition of the semi-dominator, a path $w=v_j \rightarrow\dots\rightarrow v_k=v$ in $T$ satisfying $\forall i\in[j, k-1], v_i\ge w > u$, and the edge $v \rightarrow u$. This builds a path that satisfies the definition of a semi-dominator.

Next we prove $sdom(u)\ge x$. Consider the path $sdom(u)=v_0\rightarrow v_1 \rightarrow\dots\rightarrow v_k=u$ from the definition of the semi-dominator of $u$. It is easy to see that $k=1$ and $k > 1$ correspond to the two kinds of choices in the formula. If $k = 1$, there is a directed edge $sdom(u) \rightarrow u$, and the claim follows from Lemma 7. If $k>1$, let $j$ be the smallest number such that $j \ge 1$ and $v_j$ is an ancestor of $v_{k-1}$ in $T$. Since $k$ satisfies this condition, such a $j$ always exists.

We show that $v_0 \rightarrow \dots \rightarrow v_j$ is a path that makes $v_0$ qualify as a semi-dominator of $v_j$, that is, $\forall i \in [1, j), v_i>v_j$. If not, let $i$ be the index with the smallest $v_i$ among those with $v_i < v_j$. Then every vertex on the path $v_i\rightarrow\dots\rightarrow v_j$ is at least $v_i$. By a property of DFS trees, $v_i$ must be an ancestor of $v_j$, and hence also an ancestor of $v_{k-1}$. This contradicts the minimality of $j$. So $sdom(v_j)\le sdom(u)$. Also $x\le sdom(v_j)$, so $sdom(u)\ge x$. Combined with $sdom(u) \le x$ proved earlier, we get $x=sdom(u)$.

With Theorem 1 we can compute the semi-dominator of every vertex. The bottleneck is clearly the second case. We optimize it with a weighted disjoint set union: during each path compression, update the minimum.

```cpp
void dfs(int u) {
  dfn[u] = ++dfc;
  pos[dfc] = u;
  for (int i = h[0][u]; i; i = e[i].x) {
    int v = e[i].v;
    if (!dfn[v]) {
      dfs(v);
      fth[v] = u;
    }
  }
}

int find(int x) {
  if (fa[x] == x) {
    return x;
  }
  int tmp = fa[x];
  fa[x] = find(fa[x]);
  if (dfn[sdm[mn[tmp]]] < dfn[sdm[mn[x]]]) {
    mn[x] = mn[tmp];
  }
  return fa[x];
}

void getsdom() {
  dfs(1);
  for (int i = 1; i <= n; ++i) {
    mn[i] = fa[i] = sdm[i] = i;
  }
  for (int i = dfc; i >= 2; --i) {
    int u = pos[i], res = INF;
    for (int j = h[1][u]; j; j = e[j].x) {
      int v = e[j].v;
      if (!dfn[v]) {
        continue;
      }
      find(v);
      if (dfn[v] < dfn[u]) {
        res = std::min(res, dfn[v]);
      } else {
        res = std::min(res, dfn[sdm[mn[v]]]);
      }
    }
    sdm[u] = pos[res];
    fa[u] = fth[u];
  }
}

```

#### Computing immediate dominators

##### Converting to a DAG

But I still don't see what semi-dominators are good for!

On $T$, add a directed edge $sdom(u) \rightarrow u$ for every $u$. By Lemma 9, the new graph $G$ must be a directed acyclic graph. By Lemma 10, adding these edges does not change the dominance relation. So we have turned the original graph into a DAG, and we can use the algorithm above.

##### Using semi-dominators directly

Building a pile of graphs is not elegant at all!

**Theorem 2:** For any vertex $u$, if every vertex $v$ on the path in $T$ from $sdom(u)$ to $w$ satisfies $sdom(v)\ge sdom(w)$, then $idom(u) =sdom(u)$.

**Proof:** By Lemma 10, $idom(u)$ is $sdom(u)$ or one of its ancestors, so we only need to prove $sdom(u) \ dom \ u$.

Consider any path $P$ from $s$ to $u$. We need to show that $sdom(u)$ must be on $P$. Let $v$ be the last vertex in $P$ with $v<sdom(u)$. If $v$ does not exist, then $sdom(u)=idom(u) =s$. Otherwise, let $w$ be the first vertex after $v$ in $P$ that lies on the path in the DFS tree from $sdom(u)$ to $u$.

Next we prove $sdom(w)\le v <sdom(v)$. Consider the path $v = v_0 \rightarrow \dots v_k = w$ in $T$ from $v$ to $w$. If the claim fails, there is some $i\in[1, k- 1]$ with $v_i < w$. Then there must be some $j\in [i, k - 1]$ such that $v_j$ is an ancestor of $w$. By the choice of $v$, $sdom(u)\le v_j$, so $v_j$ also lies on the path in the DFS tree from $sdom(u)$ to $u$, which contradicts the definition of $w$. So $sdom(w)\le v < sdom(v)$. Combined with the condition of the theorem, we get $y=sdom(u)$, that is, the path $P$ contains $sdom(u)$.

**Theorem 3:** For any vertex $u$, let $v$ be the vertex with the smallest semi-dominator among all vertices on the path in $T$ from $sdom(u)$ to $u$. Then $sdom(v)\le sdom(u)$ and $idom(v) = idom(u)$.

**Proof:** Since $u$ itself is a candidate for $v$, we have $sdom(v)\le sdom(u)$.

Since $idom(u)$ is an ancestor of $v$ in $T$, by Lemma 11, $idom(u)$ is also an ancestor of $idom(v)$. So we only need to prove that $idom(v)$ dominates $u$.

Consider any path $P$ from $s$ to $u$. We need to show that $sdom(u)$ must be on $P$. Let $x$ be the last vertex in $P$ with $x<sdom(u)$. If $x$ does not exist, then $sdom(u)=idom(u) =s$. Otherwise, let $y$ be the first vertex after $x$ in $P$ that lies on the path in the DFS tree from $sdom(u)$ to $u$.

In the same way as in the proof of Theorem 2, we get $sdom(y) \le x$. By Lemma 10, $sdom(y)\le x<idom(v) \le sdom(v)$. So by the definition of $v$, $y$ cannot be a descendant of $sdom(u)$. On the other hand, $y$ cannot be both a descendant of $idom(v)$ and an ancestor of $v$. Otherwise, the path that goes along the DFS tree from $s$ to $sdom(y)$, then along P to $y$, and finally along the DFS tree to $v$ avoids $idom(v)$, which contradicts the definition of a dominator. So $y=idom(v)$, that is, $P$ contains $idom(v)$.

From these two theorems, we get the relationship between $sdom(u)$ and $idom(u)$.

Let $v$ be the vertex with the smallest $sdom(v)$ among all vertices between $sdom(u)$ and $u$. Then:

$$
idom(u) =
\left\{ 
\begin{aligned} 
& sdom(u), &\text{if}\ sdom(u) = sdom(v)
\\
&idom(v), &\text{otherwise}
\end{aligned}
\right.
$$

We only need to modify the semi-dominator code above slightly.

```cpp
struct E {
  int v, x;
} e[MAX * 4];

int h[3][MAX * 2];

int dfc, tot, n, m, u, v;
int fa[MAX], fth[MAX], pos[MAX], mn[MAX], idm[MAX], sdm[MAX], dfn[MAX],
    ans[MAX];

void add(int x, int u, int v) {
  e[++tot] = {v, h[x][u]};
  h[x][u] = tot;
}

void dfs(int u) {
  dfn[u] = ++dfc;
  pos[dfc] = u;
  for (int i = h[0][u]; i; i = e[i].x) {
    int v = e[i].v;
    if (!dfn[v]) {
      dfs(v);
      fth[v] = u;
    }
  }
}

int find(int x) {
  if (fa[x] == x) {
    return x;
  }
  int tmp = fa[x];
  fa[x] = find(fa[x]);
  if (dfn[sdm[mn[tmp]]] < dfn[sdm[mn[x]]]) {
    mn[x] = mn[tmp];
  }
  return fa[x];
}

void tar(int st) {
  dfs(st);
  for (int i = 1; i <= n; ++i) {
    fa[i] = sdm[i] = mn[i] = i;
  }
  for (int i = dfc; i >= 2; --i) {
    int u = pos[i], res = INF;
    for (int j = h[1][u]; j; j = e[j].x) {
      int v = e[j].v;
      if (!dfn[v]) {
        continue;
      }
      find(v);
      if (dfn[v] < dfn[u]) {
        res = std::min(res, dfn[v]);
      } else {
        res = std::min(res, dfn[sdm[mn[v]]]);
      }
    }
    sdm[u] = pos[res];
    fa[u] = fth[u];
    add(2, sdm[u], u);
    u = fth[u];
    for (int j = h[2][u]; j; j = e[j].x) {
      int v = e[j].v;
      find(v);
      if (sdm[mn[v]] == u) {
        idm[v] = u;
      } else {
        idm[v] = mn[v];
      }
    }
    h[2][u] = 0;
  }
  for (int i = 2; i <= dfc; ++i) {
    int u = pos[i];
    if (idm[u] != sdm[u]) {
      idm[u] = idm[idm[u]];
    }
  }
}

```

## Example problems

### [Luogu P5180 [Template] Dominator Tree](https://www.luogu.com.cn/problem/P5180)

We can compute only the dominance relation and record how many vertices each vertex dominates during the computation. Or we can build the dominator tree and compute the size of each node's subtree.

Here is the code for the second approach.

??? note "Reference code"
    ```cpp
    --8<-- "docs/graph/code/dom-tree/dom-tree_1.cpp"
    ```

### [ZJOI2012 Catastrophe](https://www.luogu.com.cn/problem/P2597)

Build the dominator tree on the DAG and then compute the subtree size of each node.

??? note "Reference code"
    ```cpp
    --8<-- "docs/graph/code/dom-tree/dom-tree_2.cpp"
    ```
