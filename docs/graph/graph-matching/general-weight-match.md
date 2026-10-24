author: accelsao, Henry-ZHR, yuhuoji

This page goes from maximum weight perfect matching in general graphs to maximum weight matching in general graphs (a maximum weight matching can be turned into a maximum weight perfect matching by adding zero-weight edges).

## Prerequisites

### Blossoms

Unlike bipartite matching, a general graph may contain odd cycles. Even cycles can be treated as in a bipartite graph.

The blossom algorithm handles an odd cycle by shrinking it into a **blossom** and making every vertex in the blossom an even vertex. Since every vertex in a blossom can become an even vertex, the whole blossom can be shrunk into a single even vertex. Note that a blossom can contain other blossoms.

This can also be written as a linear program and its dual, but blossoms need some special handling.

### Vertex labeling and equality edges

Let $z_u$ be the label of vertex $u$ (vertex labeling), with the same meaning as the labels in the $KM$ algorithm. An edge $e(u,v)$ is called an "equality edge" if and only if the labels of $u$ and $v$ add up to the weight of $e$ ($z_u + z_v = w(e)$). In that case the label of the edge is $z_e = z_u + z_v − w(e) = 0$.

## Linear program for maximum weight perfect matching in general graphs

### Definition

A blossom has at least three vertices, and after shrinking it becomes one vertex. Let $O$ be the family of all sets of odd size $≥3$ (this includes all blossoms), and let $\gamma(S)$ denote the edges inside the set $S$.

$$
\begin{aligned}
& \text{Let } S\subseteq V \\
& \gamma(S)=\{(u,v)\in E:u\in S,v\in S\} \\
& O=\{B\subseteq V:|B|\text{ is odd and }|B|\geq3\} \\
\end{aligned}
$$

### Dual problem

???+ note "Primal problem"
    $$
    \begin{aligned}
    & \max\sum_{e\in E}w(e)x_e \\
    & \text{subject to:} \\
    & x(\delta(u))=1:\forall u\in V \\
    & x(\gamma(B))\leq\lfloor\frac{|B|}{2}\rfloor:\forall B\in O \\
    & x_e\geq0:\forall e\in E \\
    \end{aligned}
    $$

Then, using the primal-dual method, we turn the problem into its dual.

???+ note "Dual problem"
    $$
    \begin{aligned}
    & \min\sum_{u\in V}z_u+\sum_{B\in O}\left\lfloor\frac{|B|}{2}\right\rfloor z_B \\
    & \text{subject to:} \\
    & z_B\geq0:\forall B\in O \\
    & z_e\geq0:\forall e\in E \\
    & \text{let } e=(u,v),\text{ where} \\
    & \begin{array}{lll}
    z_e & = & z_u + z_v - w(e) + \sum_{\substack{B \in O \\ u,v \in \gamma(B)}} z_B
    \end{array}
    \end{aligned}
    $$

Edges with $x_e=1$ are matched edges and edges with $x_e=0$ are unmatched edges. As in the bipartite case, we must satisfy $x_e\in\{0,1\}:\forall e\in E$. So in the maximum weight perfect matching, every matched edge must be an **equality edge**.

Unlike the bipartite case, general graphs also have $z_B$ to deal with. Below we consider when $z_B$ is greater than $0$.

It is best to keep $z_B=0$ whenever possible, but sometimes $z_B>0$ is unavoidable. We only let $z_B>0$ when $x(\gamma(B)) = \left\lfloor \dfrac{|B|}2 \right\rfloor \text{ and } x(\delta(B)) = 1$, because $z_B>0$ is meaningless in any other case.

By the complementary slackness conditions, we have the following correspondences:

-   For a chosen edge $e$, we must have $z_e=0$.

    $$
    x_e>0 \longrightarrow z_e=0,\quad \forall e\in E
    $$

-   For a chosen set *B*, $z_B>0 \longrightarrow x(\gamma(B))= \left\lfloor \dfrac{|B|}2 \right\rfloor$. That is, every set $B$ with $z_B>0$ has half its size (rounded down) of edges chosen, which means $B$ is a blossom and one edge of the blossom is chosen for augmentation. We also add a condition: $x(\delta(B))=1$, meaning $z_B>0$ only makes sense when the blossom $B$ has exactly one edge leading outside.

    $$
    z_B>0 \longrightarrow x(\gamma(B))=\left\lfloor\frac{|B|}2\right\rfloor, x(\delta(B))=1\quad \forall B\in O
    $$

Combine the idea of "**equality edges**" with the blossom algorithm from before: keep extending with augmenting paths made of "equality edges". Since every edge used for extending is an "equality edge", the final maximum weight perfect matching still consists entirely of "equality edges".

### Handling blossoms

When we meet a blossom, we shrink it into an even vertex. Make every vertex in the blossom an even vertex, and set its $z_B=0$.

After shrinking, the blossom is stored and only taken apart when certain conditions hold, so we cannot record blossoms the way we did before.

Unless stated otherwise, "vertices" below include the even vertices formed by shrinking blossoms.

Blossoms may also be shrunk into vertices and pushed into the queue, and the number of blossoms is not fixed. So we cannot check for augmenting paths by enumerating each vertex as before. Instead, during the breadth-first search (BFS), we must put all unmatched vertices into the queue.

This creates many alternating trees at the same time.

### The four steps of the algorithm

The algorithm can be split into four steps.

1.  GROW (equality edges): build alternating trees from "equality edges".
2.  AUGMENT: find an augmenting path and extend the matching.
3.  SHRINK: shrink a blossom into a single vertex.
4.  EXPAND: take a blossom apart.

![general-weight-match-1](images/general-weight-match-1.png)

In the AUGMENT step, since all unmatched vertices are in different alternating trees, when even vertices of two alternating trees get connected, we have found an augmenting path.

### When no equality edge can extend the tree

As in the bipartite case, sometimes no "equality edge" can extend the tree. Then we need to adjust the vertex labeling.

### Adjusting the vertex labeling

The vertex labeling must still satisfy the greater-than-or-equal property, the existing "equality edges" must not change, and $z_B$ should be kept as small as possible.

???+ note "Notation for odd and even vertices"
    $u^−$ means $u$ is an odd vertex in an alternating tree.  
    $u^+$ means $u$ is an even vertex in an alternating tree.  
    $u^\varnothing$ means $u$ is not in any alternating tree.  
    From now on, $B$ always denotes a blossom, and also the vertex it is shrunk into.  
    Blossoms can also be odd or even, so the notation $B^+$, $B^−$ and $B^\varnothing$ also applies.

Suppose there are currently r alternating trees $T_i=(U_{t_i},V_{t_i}):1\leq i\leq r$. Let

$$
\begin{aligned}
d1 &= \min(\{z_e : e = (u^+,v^\varnothing)\}) \\
d2 &= \min(\{z_e : e = (u^+,v^+), ~ u^+ \in T_i, ~ v^+ \in T_j, ~ i \neq j\}) / 2 \\
d3 &= \min(\{z_{B^-} : B^- \in O\}) / 2
\end{aligned}
$$

Note that *B* here is the vertex after shrinking, so it can be odd or even.

Let $d=min(d1,d2,d3)$, and set

$$
\begin{aligned}
z_{u^+} - &= d \\
z_{v^-} + &= d \\
z_{B^+} + &= 2d \\
z_{B^-} - &= 2d \\
\end{aligned}
$$

If $z_B=0(d=d3)$ occurs, we must take this blossom apart (EXPAND) to prevent $z_B<0$.
After taking the blossom apart, only the alternating path inside it is kept, and the vertices of the blossom that are not on the alternating path are marked unvisited ($\varnothing$).

This creates one (or more) new equality edges, keeps the existing equality edges unchanged, maintains $z_e\geq0:\forall e\in E$, and increases $z_B$ as little as possible. Now we can continue searching for augmenting paths.

## Maximum weight matching in general graphs

The above finds a maximum weight perfect matching. To find a maximum weight matching, add one more constraint to the vertex labeling: for every matched vertex $u$, $z_u>0$.

At the start, set every $z_u=max(\{w(e):e\in E\})/2$.

Vertices whose label reaches $0$ end up unmatched.

### Reference code

To make the implementation easier, we multiply edge weights by $2$ when computing $z_e$, so there are no floating-point errors.

???+ note "Storage"
    ```cpp
    constexpr int INF = INT_MAX;
    constexpr int MAXN = 400;
    
    struct edge {
      int u, v, w;
    
      // (u,v) is an edge with weight w
      edge() {}
    
      edge(int u, int v, int w) : u(u), v(v), w(w) {}
    };
    
    int n, n_x;
    // there are n vertices, numbered 1 ~ n
    // n_x is the number of vertices plus blossoms; numbers n+1 to n_x are blossom nodes
    edge g[MAXN * 2 + 1][MAXN * 2 + 1];
    // the graph is stored as an adjacency matrix; there are at most n-1 blossoms, so the size is MAXN*
    vector<int> flower[MAXN * 2 + 1];
    // flower[b] records which vertices are in blossom b
    // we only record the outermost sub-blossoms inside a blossom
    ```

Below is an example of nested blossoms.

![general-weight-match-2](images/general-weight-match-2.png)

Here $\{ 6, 5, 8\} \in b1,\{ b1, 4, 3, 2, 11, 10, 9\} \in b2$. They are stored as:

```text
flower[b2] = {b1, 4, 3, 2, 11, 10, 9} 
flower[b1] = {6, 5, 8}
```

![general-weight-match-3](images/general-weight-match-3.png)

```text
flower[b2] = {9, b1, 4, 3, 2, 11, 10} 
flower[b1] = {5, 8, 6}
```

```cpp
int lab[MAXN * 2 + 1];
// lab[u] stores z_u, lab[b] stores z_B
int match[MAXN * 2 + 1], slack[MAXN * 2 + 1], st[MAXN * 2 + 1],
    pa[MAXN * 2 + 1];
// match[x]=y means (x,y) is a matched pair; x and y may be blossoms
// slack[x]=u means z(x,u) is the smallest among all edges adjacent to x
// st[x]=b means the blossom containing node x is b. If x=b and b<=n, then x
// is a plain node (not in any blossom). pa[v]=u means the parent of node v in the alternating tree is u
int flower_from[MAXN * 2 + 1][MAXN + 1], S[MAXN * 2 + 1], vis[MAXN * 2 + 1];
/*
flower_from[b][x]=xs means the largest sub-blossom of b that contains x is xs
x is a vertex inside b, xs is a blossom or vertex inside b, and either x=xs or x is one of the vertices of xs
*/
// S[u]={-1: not visited, 0: even vertex, 1: odd vertex}
// vis is only used when finding the lca, to check whether a node was visited
queue<int> q;
// queue used by BFS to find augmenting paths
```

![general-weight-match-4](images/general-weight-match-4.png)

```text
flower_from[b2][6] = b1 
flower_from[b2][5] = b1 
flower_from[b2][9] = 9 
flower_from[b1][6] = 6 
and so on
```

```cpp
int e_delta(const edge &e) {
  // compute ze; for convenience, all edge weights are doubled
  // computing e_delta directly inside a blossom gives wrong results
  return lab[e.u] + lab[e.v] - g[e.u][e.v].w * 2;
}

void update_slack(int u, int x) {
  // update slack[x] using u
  if (!slack[x] || e_delta(g[u][x]) < e_delta(g[slack[x]][x])) {
    slack[x] = u;
  }
}

void set_slack(int x) {
  // compute slack[x]; slack[x]=0 means x is a node in an alternating tree
  slack[x] = 0;
  for (int u = 1; u <= n; ++u) {
    if (g[u][x].w > 0 && st[u] != x && S[st[u]] == 0) {
      update_slack(u, x);
    }
  }
}
```

```cpp
void q_push(int x) {
  // push x into the queue; we require that a blossom is never pushed directly
  if (x <= n)
    q.push(x);
  else {
    // to push a blossom, push all original vertices inside it instead
    for (size_t i = 0; i < flower[x].size(); i++) {
      q_push(flower[x][i]);
    }
  }
}

void set_st(int x, int b) {
  // set the blossom containing x to b
  st[x] = b;
  if (x > n) {
    // if x is also a blossom, set the blossom of every vertex inside x to b as well
    for (size_t i = 0; i < flower[x].size(); ++i) {
      set_st(flower[x][i], b);
    }
  }
}
```

```cpp
int get_pr(int b, int xr) {
  // xr is an element of flower[b]; the return value pr is its position
  // to make the code simpler, we keep flower[b][0]~flower[b][pr] as the alternating path in the blossom
  int pr = find(flower[b].begin(), flower[b].end(), xr) - flower[b].begin();
  if (pr % 2 == 1) {
    // check its position in the blossom; if flower[b][0]~flower[b][pr] is not an alternating path,
    // reverse the whole blossom and recompute pr
    // so that flower[b][0]~flower[b][pr] is the alternating path in the blossom
    reverse(flower[b].begin() + 1, flower[b].end());
    return (int)flower[b].size() - pr;
  } else
    return pr;
}
```

![general-weight-match-5](images/general-weight-match-5.png)

If you call `get_pr(b2,11)`, `flower[b2]` becomes `{9,10,11,2,3,4,b1}` and it returns 2.

If you call `get_pr(b2,2)`, `flower[b2]` becomes `{9,b1,4,3,2,11,10}` and it returns 4.

```cpp
void set_match(int u, int v) {
  // make (u,v) a matched edge; u and v may be blossoms
  match[u] = g[u][v].v;
  if (u > n) {
    // if u is a blossom
    edge e = g[u][v];
    int xr = flower_from[u][e.u];  // find which sub-blossom of flower[u] contains e.u
    int pr = get_pr(u, xr);  // find the position of xr and make 0~pr the alternating path in the blossom
    for (int i = 0; i < pr; ++i) {  // flip matched and unmatched edges along the alternating path in the blossom
      set_match(flower[u][i], flower[u][i ^ 1]);
    }
    set_match(xr, v);  // make (xr,v) a matched edge
    rotate(flower[u].begin(), flower[u].begin() + pr, flower[u].end());
    // finally make pr the base, since by our storage flower[u][0] is the base of u
    // so rotate flower[u][pr] to the front
  }
}

void augment(int u, int v) {
  // augment along u and all its ancestors, and make (u,v) a matched edge
  for (;;) {
    int xnv = st[match[u]];
    set_match(u, v);
    if (!xnv) return;
    set_match(xnv, st[pa[xnv]]);
    u = st[pa[xnv]];
    v = xnv;
  }
}

int get_lca(int u, int v) {
  // find the lca of u and v in the alternating tree
  static int t = 0;
  for (++t; u || v; swap(u, v)) {
    if (u == 0) continue;
    if (vis[u] == t) return u;
    vis[u] = t;  // this way the vis array never needs to be cleared
    u = st[match[u]];
    if (u) u = st[pa[u]];
  }
  return 0;
}
```

???+ note "Adding an odd blossom"
    ```cpp
    void add_blossom(int u, int lca, int v) {
      // shrink the blossom formed by u, v and lca into a single vertex b
      // the lca of u and v in the alternating tree is the base
      int b = n + 1;
      while (b <= n_x && st[b]) ++b;
      if (b > n_x) ++n_x;
      // find an unused blossom number
      lab[b] = 0;             // set zB=0
      S[b] = 0;               // the whole blossom is an even vertex
      match[b] = match[lca];  // the blossom's matched edge is the base's matched edge
      flower[b].clear();
      flower[b].push_back(lca);
      for (int x = u, y; x != lca; x = st[pa[y]]) {
        flower[b].push_back(x);
        y = st[match[x]];
        flower[b].push_back(y);
        q_push(y);
      }
      reverse(flower[b].begin() + 1, flower[b].end());
      for (int x = v, y; x != lca; x = st[pa[y]]) {
        flower[b].push_back(x);
        y = st[match[x]];
        flower[b].push_back(y);
        q_push(y);
      }
      // add all vertices of b to flower[b] in cycle order, with the base as the first element
      set_st(b, b);  // set the blossom of every element inside it to b
      for (int x = 1; x <= n_x; ++x) {
        g[b][x].w = 0;
        g[x][b].w = 0;
      }
      for (int x = 1; x <= n; ++x) {
        flower_from[b][x] = 0;
      }
      for (size_t i = 0; i < flower[b].size(); ++i) {
        int xs = flower[b][i];
        for (int x = 1; x <= n_x; ++x) {
          // set the edge between b and x to the edge inside b adjacent to x with the smallest e_delta
          if (g[b][x].w == 0 || e_delta(g[xs][x]) < e_delta(g[b][x])) {
            g[b][x] = g[xs][x];
            g[x][b] = g[x][xs];
          }
        }
        for (int x = 1; x <= n; ++x) {
          if (flower_from[xs][x]) {
            // if xs inside b contains x
            // then flower_from[b][x] is xs
            flower_from[b][x] = xs;
          }
        }
      }
      set_slack(b);
      // finally, set the slack value of b
    }
    ```

???+ note "Expanding a blossom"
    ```cpp
    void expand_blossom(int b) {
      // when b is an odd blossom and zB=0, b must be taken apart
      // we only take b itself apart, so if b contains other blossoms,
      // they do not need to be taken apart
      for (size_t i = 0; i < flower[b].size(); ++i) {
        set_st(flower[b][i], flower[b][i]);
        // first set the blossom of each element of flower[b] to itself
      }
      int xr = flower_from[b][g[b][pa[b]].u];
      // xr is the sub-blossom of flower[b] containing b's parent on the alternating path
      int pr = get_pr(b, xr);  // find the position of xr and make 0~pr the alternating path in the blossom
      for (int i = 0; i < pr; i += 2) {
        // move the alternating path out into the alternating tree
        // and push the even vertices on it into the queue
        int xs = flower[b][i];
        int xns = flower[b][i + 1];
        pa[xs] = g[xns][xs].u;
        S[xs] = 1;
        S[xns] = 0;
        slack[xs] = 0;
        set_slack(xns);
        q_push(xns);
      }
      S[xr] = 1;  // now xr is an odd vertex or an odd blossom
      pa[xr] = pa[b];
      for (size_t i = pr + 1; i < flower[b].size(); ++i) {
        // mark all vertices of the blossom that are not on the alternating path as unvisited
        int xs = flower[b][i];
        S[xs] = -1;
        set_slack(xs);
      }
      st[b] = 0;
    }
    ```

???+ note "Trying to augment along an equality edge"
    ```cpp
    bool on_found_edge(const edge &e) {
      // BFS found an equality edge e
      // process it as follows
      // here u is always an even vertex
      int u = st[e.u], v = st[e.v];
      if (S[v] == -1) {
        // v is unvisited
        pa[v] = e.u;
        S[v] = 1;
        int nu = st[match[v]];
        slack[v] = 0;
        slack[nu] = 0;
        S[nu] = 0;
        q_push(nu);
      } else if (S[v] == 0) {
        // v is an even vertex
        int lca = get_lca(u, v);
        if (!lca) {  // lca=0 means u and v are in different alternating trees, so there is an augmenting path
          augment(u, v);
          augment(v, u);
          return true;  // found an augmenting path
        } else
          add_blossom(u, lca, v);
        // otherwise u and v are in the same tree and form a blossom, which must be shrunk
      }
      return false;
    }
    ```

???+ note "Augmentation"
    ```cpp
    bool matching() {
      memset(S + 1, -1, sizeof(int) * n_x);
      memset(slack + 1, 0, sizeof(int) * n_x);
      q = queue<int>();  // clear the queue
      for (int x = 1; x <= n_x; ++x) {
        if (st[x] == x && !match[x]) {
          // push all unmatched vertices into the queue and mark them even
          pa[x] = 0;
          S[x] = 0;
          q_push(x);
        }
      }
      if (q.empty()) return false;  // every vertex is matched
      for (;;) {
        while (q.size()) {
          // BFS
          int u = q.front();
          q.pop();
          if (S[st[u]] == 1) continue;
          for (int v = 1; v <= n; ++v) {
            if (g[u][v].w > 0 && st[u] != st[v]) {
              if (e_delta(g[u][v]) == 0) {
                if (on_found_edge(g[u][v])) return true;
              } else
                update_slack(u, st[v]);
            }
          }
        }
        // update the lab values
        int d = INF;
        for (int u = 1; u <= n; ++u) {
          // this prevents lab<0 from happening
          // stop as soon as any lab[u]=0
          if (S[st[u]] == 0) d = min(d, lab[u]);
        }
        for (int b = n + 1; b <= n_x; ++b) {
          if (st[b] == b && S[b] == 1) d = min(d, lab[b] / 2);
        }
        for (int x = 1; x <= n_x; ++x)
          if (st[x] == x && slack[x]) {
            if (S[x] == -1)
              d = min(d, e_delta(g[slack[x]][x]));
            else if (S[x] == 0)
              d = min(d, e_delta(g[slack[x]][x]) / 2);
          }
        for (int u = 1; u <= n; ++u) {
          if (S[st[u]] == 0) {
            if (lab[u] == d) return false;
            // if lab[u]=0, stop right away
            lab[u] -= d;
          } else if (S[st[u]] == 1)
            lab[u] += d;
        }
        for (int b = n + 1; b <= n_x; ++b) {
          if (st[b] == b) {
            if (S[st[b]] == 0)
              lab[b] += d * 2;
            else if (S[st[b]] == 1)
              lab[b] -= d * 2;
          }
        }
        q = queue<int>();  // clear the queue
        for (int x = 1; x <= n_x; ++x) {
          // check whether an augmenting path has appeared
          if (st[x] == x && slack[x] && st[slack[x]] != x &&
              e_delta(g[slack[x]][x]) == 0)
            if (on_found_edge(g[slack[x]][x])) return true;
        }
        for (int b = n + 1; b <= n_x; ++b) {
          // EXPAND: take apart every odd blossom with lab[b]=0
          if (st[b] == b && S[b] == 1 && lab[b] == 0) expand_blossom(b);
        }
      }
      return false;
    }
    ```

???+ note "Main function"
    ```cpp
    pair<long long, int> weight_blossom() {
      // main function; initialize first
      memset(match + 1, 0, sizeof(int) * n);
      n_x = n;  // no blossoms at the start
      int n_matches = 0;
      long long tot_weight = 0;
      for (int u = 0; u <= n; ++u) {
        // first set each vertex's blossom to itself
        st[u] = u;
        flower[u].clear();
      }
      int w_max = 0;
      for (int u = 1; u <= n; ++u)
        for (int v = 1; v <= n; ++v) {
          // when u is a vertex, it contains only itself
          flower_from[u][v] = (u == v ? u : 0);
          w_max = max(w_max, g[u][v].w);
          // find the largest edge weight
        }
      for (int u = 1; u <= n; ++u) lab[u] = w_max;
      // set every lab to the largest edge weight
      // since edge weights are doubled when computing ze, no need to divide by two
      while (matching()) ++n_matches;
      for (int u = 1; u <= n; ++u)
        if (match[u] && match[u] < u) tot_weight += g[u][match[u]].w;
      return make_pair(tot_weight, n_matches);
    }
    ```

???+ note "Initialization"
    Very important: always initialize before use
    
    ```cpp
    void init_weight_graph() {
      // must initialize before adding edges to the graph
      // since this is maximum weight matching, missing edges get weight 0
      for (int u = 1; u <= n; ++u)
        for (int v = 1; v <= n; ++v) g[u][v] = edge(u, v, 0);
    }
    ```

## Complexity analysis

In one BFS, each blossom is shrunk or expanded at most once. Each shrink or expand takes $O(|V|)$ time. There are at most $O(|V|)$ blossoms in total, so handling blossoms takes $O(|V|^2)$ time. The BFS itself takes $O(|V| + |E|)$ time. So finding an augmenting path takes $O(|V| + |E|) + O(|V|^2) = O(|V|^2)$ time.

At most $|V|$ BFS runs are needed. So the total time complexity is $O(|V|^3)$.

## Exercises

-   [UOJ #81. Maximum Weight Matching in General Graphs](https://uoj.ac/problem/81)

## References

1.  [Kolmogorov, Vladimir (2009), "Blossom V: A new implementation of a minimum cost perfect matching algorithm"](http://pub.ist.ac.at/~vnk/papers/BLOSSOM5.html)
2.  [From the Hungarian algorithm to the weighted blossom algorithm: the dual problem in graph matching explained (in Chinese)](https://www.luogu.com.cn/blog/potassium/solution-p6699)
