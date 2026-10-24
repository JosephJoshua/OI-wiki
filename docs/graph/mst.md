author: Chrogeek, Enter-tainer, HeRaNO, Ir1d, Marcythm, ShadowsEpic, StudyingFather, Xeonacid, bear-good, billchenchina, diauweb, diauweb, greyqz, kawa-yoiko, ouuan, partychicken, sshwy, stevebraveman, zhouyuyang2002, renbaoshuo, Hszzzx, y-kx-b, toprise

## Definition

Before reading the following, make sure you have read [Graph theory basics](./concept.md) and [Tree basics](./tree-basic.md), and know these definitions:

1.  Spanning subgraph
2.  Spanning tree

We define the **minimum spanning tree** (MST) of a connected undirected graph as the spanning tree with the smallest total edge weight.

Note: only connected graphs have spanning trees. A disconnected graph only has spanning forests.

## Kruskal's algorithm

Kruskal's algorithm is a common and easy-to-write MST algorithm, invented by Kruskal. Its basic idea is to add edges from smallest to largest weight. It is a greedy algorithm.

### Prerequisites

[Disjoint set union](../ds/dsu.md), [Greedy](../basic/greedy.md), [Graph storage](./save.md).

### Implementation

Illustration:

![](./images/mst-2.apng)

Pseudocode:

<!--
```pseudo
\begin{algorithm}
\caption{Kruskal}
\begin{algorithmic}
\INPUT{ The edges of the graph $e$ where each element in $e$ is $(u, v, w)$ denoting that there is an edge between $u$ and $v$ weighted $w$. }
\OUTPUT The edges of the MST of the input graph
\STATE $result \gets \varnothing$
\STATE sort $e$ into nondecreasing order by weight $w$
\FOR{each $(u, v, w)$ in the sorted $e$}
    \IF{$u$ \AND $v$ are not connected in the union-find set}
        \STATE connect $u$ \AND $v$ in the union-find set
        \STATE $result \gets result \bigcup (u, v, w)$
    \ENDIF
\ENDFOR
\RETURN $result$
\end{algorithmic}
\end{algorithm}
```
-->

$$
\begin{array}{ll}
1 &  \textbf{Input. } \text{The edges of the graph } e , \text{ where each element in } e \text{ is } (u, v, w) \\
  &  \text{ denoting that there is an edge between } u \text{ and } v \text{ weighted } w . \\
2 &  \textbf{Output. } \text{The edges of the MST of the input graph}.\\
3 &  \textbf{Method. } \\ 
4 &  result \gets \varnothing \\
5 &  \text{sort } e \text{ into nondecreasing order by weight } w \\ 
6 &  \textbf{for} \text{ each } (u, v, w) \text{ in the sorted } e \\ 
7 &  \qquad \textbf{if } u \text{ and } v \text{ are not connected in the union-find set } \\
8 &  \qquad\qquad \text{connect } u \text{ and } v \text{ in the union-find set} \\
9 &  \qquad\qquad  result \gets result\;\bigcup\ \{(u, v, w)\} \\
10 &  \textbf{return }  result
\end{array}
$$

The algorithm is simple, but it needs a suitable data structure to support it. Specifically, we maintain a forest, check whether two vertices are in the same tree, and connect two trees.

More abstractly, we maintain a collection of **sets**, check whether two elements are in the same set, and merge two sets.

Checking whether two vertices are connected and connecting two vertices can both be done with a DSU.

If we use an $O(m\log m)$ sorting algorithm and an $O(m\alpha(m, n))$ or $O(m\log n)$ DSU, we get Kruskal's algorithm with time complexity $O(m\log m)$.

### Proof

The idea is simple. To build an MST, start from the edge with the smallest weight and add edges in increasing order of weight. If adding an edge creates a cycle, discard it. Continue until $n-1$ edges have been added, which forms a tree.

Proof: by induction, we show that at any time, the set of edges chosen by Kruskal's algorithm is contained in some MST.

Base case: at the start of the algorithm, this clearly holds (an MST exists).

Inductive step: suppose it holds at some point. Let the current edge set be $F$ and let $T$ be that MST. Consider the next edge $e$ to be added.

If $e$ belongs to $T$, the claim holds.

Otherwise, $T+e$ must contain a cycle. Consider another edge $f$ on this cycle that does not belong to $F$ (there is at least one).

First, the weight of $f$ cannot be smaller than that of $e$; otherwise $f$ would have been chosen before $e$.

Next, the weight of $f$ cannot be larger than that of $e$; otherwise $T+e-f$ would be a spanning tree better than $T$.

So $T+e-f$ contains $F$ and is also an MST. The induction holds.

### Example problem

???+ note "[Luogu P1195 Sky in a Pocket](https://www.luogu.com.cn/problem/P1195)"
    There are $n$ clouds, and you need to connect them into $k$ marshmallows. Connecting cloud $X_i$ and cloud $Y_i$ costs $L_i$. Find the minimum cost.

??? note "Example code"
    === "C++"
        ```cpp
        --8<-- "docs/graph/code/mst/mst_3.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/graph/code/mst/mst_3.py"
        ```
    
    === "Java"
        ```java
        --8<-- "docs/graph/code/mst/mst_3.java"
        ```

## Prim's algorithm

Prim's algorithm is another common and easy-to-write MST algorithm. Its basic idea is to start from one vertex and keep adding vertices (instead of adding edges, as Kruskal's algorithm does).

### Implementation

Illustration:

![](./images/mst-3.apng)

Specifically, each time we pick the vertex with the smallest distance, and use its new edges to update the distances of other vertices.

This works just like Dijkstra's algorithm: to find the vertex with the smallest distance each time, you can search by brute force or maintain a heap.

The heap optimization is similar to Dijkstra's heap optimization. But with a heap such as a binary heap that does not support $O(1)$ decrease-key, the complexity is no better than Kruskal and the constant factor is larger. So Kruskal is usually used. On dense graphs, especially complete graphs, brute-force Prim has better complexity than Kruskal, but it does **not necessarily** run faster in practice.

Brute force: $O(n^2+m)$.

Binary heap: $O((n+m) \log n)$.

Fibonacci heap: $O(n \log n + m)$.

Pseudocode:

$$
\begin{array}{ll}
1 &  \textbf{Input. } \text{The nodes of the graph }V\text{ ; the function }g(u, v)\text{ which}\\
  &  \text{means the weight of the edge }(u, v)\text{; the function }adj(v)\text{ which}\\
  &  \text{means the nodes adjacent to }v.\\
2 &  \textbf{Output. } \text{The sum of weights of the MST of the input graph.} \\
3 &  \textbf{Method.} \\
4 &  result \gets 0 \\
5 & \text{choose an arbitrary node in }V\text{ to be the }root \\
6 &  dis(root)\gets 0 \\
7 &  \textbf{for } \text{each node }v\in(V-\{root\}) \\
8 &  \qquad  dis(v)\gets\infty \\
9 &  rest\gets V \\
10 &  \textbf{while }  rest\ne\varnothing \\
11 &  \qquad cur\gets \text{the node with the minimum }dis\text{ in }rest \\
12 &  \qquad  result\gets result+dis(cur) \\
13 &  \qquad  rest\gets rest-\{cur\} \\
14 &  \qquad  \textbf{for}\text{ each node }v\in adj(cur) \\
15 &  \qquad\qquad  dis(v)\gets\min(dis(v), g(cur, v)) \\
16 &  \textbf{return }  result 
\end{array}
$$

Note: the code above only computes the total weight of the MST. To output the tree itself, you also need to record which edge each vertex's $dis$ comes from.

??? note "Implementation"
    ```cpp
    // Prim's algorithm optimized with a binary heap.
    #include <cstring>
    #include <iostream>
    #include <queue>
    using namespace std;
    constexpr int N = 5050, M = 2e5 + 10;
    
    struct E {
      int v, w, x;
    } e[M * 2];
    
    int n, m, h[N], cnte;
    
    void adde(int u, int v, int w) { e[++cnte] = E{v, w, h[u]}, h[u] = cnte; }
    
    struct S {
      int u, d;
    };
    
    bool operator<(const S &x, const S &y) { return x.d > y.d; }
    
    priority_queue<S> q;
    int dis[N];
    bool vis[N];
    
    int res = 0, cnt = 0;
    
    void Prim() {
      memset(dis, 0x3f, sizeof(dis));
      dis[1] = 0;
      q.push({1, 0});
      while (!q.empty()) {
        if (cnt >= n) break;
        int u = q.top().u, d = q.top().d;
        q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        ++cnt;
        res += d;
        for (int i = h[u]; i; i = e[i].x) {
          int v = e[i].v, w = e[i].w;
          if (w < dis[v]) {
            dis[v] = w, q.push({v, w});
          }
        }
      }
    }
    
    int main() {
      cin >> n >> m;
      for (int i = 1, u, v, w; i <= m; ++i) {
        cin >> u >> v >> w, adde(u, v, w), adde(v, u, w);
      }
      Prim();
      if (cnt == n)
        cout << res;
      else
        cout << "No MST.";
      return 0;
    }
    ```

### Proof

Start from any vertex and split the vertices into two groups: added and not yet added.

Each time, among the vertices not yet added, find the one whose minimum edge weight to the added vertices is the smallest.

Then add this vertex, together with that minimum-weight edge.

Repeat $n-1$ times.

Proof: again, we show that at every step there is an MST containing the chosen edge set.

Base case: with only one vertex, this clearly holds.

Inductive step: suppose it holds at some step. The current edge set $F$ belongs to the MST $T$, and the next edge to add is $e$.

If $e$ belongs to $T$, the claim holds.

Otherwise, consider another edge $f$ on the cycle in $T+e$ that could be added to the current edge set.

First, the weight of $f$ is at least the weight of $e$; otherwise $f$ would have been chosen instead of $e$.

Next, the weight of $f$ is at most the weight of $e$; otherwise $T+e-f$ would be a smaller spanning tree.

So $e$ and $f$ have equal weights, and $T+e-f$ is also an MST that contains $F$.

## Boruvka's algorithm

Next we introduce another MST algorithm: Boruvka's algorithm. Its idea combines the previous two algorithms. It can find the minimum spanning forest of an undirected graph. (For a connected undirected graph, this is the MST.)

Boruvka's algorithm has an advantage on problems where the edges have many special properties, such as the complete graph problem [CF888G](https://codeforces.com/problemset/problem/888/G).

To describe the algorithm, we need some definitions:

1.  Let $E'$ be the edges of the minimum spanning forest found so far. During the algorithm we add edges to $E'$ step by step. A **component** is a vertex set $V'\subseteq V$ such that any two vertices $u$, $v$ in it are connected (reachable from each other) in the subgraph formed by the edges of $E'$.
2.  The **cheapest edge** of a component is the edge with the smallest weight among its edges leading to other components.

Initially $E'=\varnothing$, and each vertex is its own component:

1.  Compute which component each vertex belongs to. Mark every component as having "no cheapest edge".
2.  Go through each edge $(u, v)$. If $u$ and $v$ are in different components, use this edge's weight to update the cheapest edges of the components of $u$ and $v$.
3.  If no component has a cheapest edge, stop: $E'$ is now the edge set of the minimum spanning forest of the original graph. Otherwise, add the cheapest edge of every component that has one to $E'$, and go back to step 1.

Here is an animated example (image from [Wikipedia](https://en.wikipedia.org/wiki/Bor%C5%AFvka%27s_algorithm)):

![eg](./images/mst-1.apng)

When the original graph is connected, each iteration at least halves the number of components, so the algorithm runs at most $O(\log V)$ iterations. A disconnected graph is just several subproblems, so the complexity is $O(E\log V)$. Here is the pseudocode (adapted from [Wikipedia](https://en.wikipedia.org/wiki/Bor%C5%AFvka%27s_algorithm)):

$$
\begin{array}{ll}
1 &  \textbf{Input. } \text{A graph }G\text{ whose edges have distinct weights. } \\
2 &  \textbf{Output. } \text{The minimum spanning forest of }G .  \\
3 &  \textbf{Method. }  \\
4 & \text{Initialize a forest }F\text{ to be a set of one-vertex trees} \\
5 &  \textbf{while } \text{True} \\
6 &  \qquad \text{Find the components of }F\text{ and label each vertex of }G\text{ by its component } \\
7 &  \qquad \text{Initialize the cheapest edge for each component to "None"} \\
8 &  \qquad  \textbf{for } \text{each edge }(u, v)\text{ of }G  \\
9 &  \qquad\qquad  \textbf{if }  u\text{ and }v\text{ have different component labels} \\
10 &  \qquad\qquad\qquad  \textbf{if }  (u, v)\text{ is cheaper than the cheapest edge for the component of }u  \\
11 &  \qquad\qquad\qquad\qquad\text{ Set }(u, v)\text{ as the cheapest edge for the component of }u \\
12 &  \qquad\qquad\qquad  \textbf{if }  (u, v)\text{ is cheaper than the cheapest edge for the component of }v  \\
13 &  \qquad\qquad\qquad\qquad\text{ Set }(u, v)\text{ as the cheapest edge for the component of }v  \\
14 &  \qquad  \textbf{if }\text{ all components'cheapest edges are "None"} \\
15 &  \qquad\qquad  \textbf{return }  F \\
16 &  \qquad  \textbf{for }\text{ each component whose cheapest edge is not "None"} \\
17 &  \qquad\qquad\text{ Add its cheapest edge to }F \\
\end{array}
$$

Note that comparing edges usually needs a second key (for example, the edge index), so that edges with equal weights can still be ordered.

## Exercises

-   [HAOI2006 Clever Monkeys](https://www.luogu.com.cn/problem/P2504)
-   [SCOI2005 Busy City](https://loj.ac/problem/2149)

## Uniqueness of the MST

Consider whether the MST is unique. If an edge **not in the MST** can replace another edge that **has the same weight and is in the MST**, then the MST is not unique.

For Kruskal's algorithm, count how many edges of the current weight could be added and how many were actually added. If these two numbers differ, some of these edges form a cycle with earlier edges (this cycle has at least two edges of the current weight; otherwise, by the DSU, the edge could not be added). This means the MST is not unique.

To find the edges with the same weight as the current edge, we only need to keep head and tail pointers. Using a monotonic queue, this can be solved nicely in $O(\alpha(m))$ time ($m$ is the number of edges), which is basically the same as the original algorithm.

??? note "Example problem: [POJ 1679](http://poj.org/problem?id=1679)"
    ```cpp
    --8<-- "docs/graph/code/mst/mst_1.cpp"
    ```

## Second-best minimum spanning tree

### Non-strict second-best MST

#### Definition

In an undirected graph, it is the spanning tree with the smallest total weight among those whose total weight is **greater than or equal to** that of the MST.

#### How to compute it

-   Find the MST $T$ of the undirected graph, and let its total weight be $M$.
-   For each unused edge $e = (u,v,w)$, find the edge $e' = (s,t,w')$ with the largest weight on the path from $u$ to $v$ in $T$. Replacing $e'$ with $e$ in $T$ gives a spanning tree $T'$ with total weight $M' = M + w - w'$.
-   Take the minimum of all such $M'$.

How do we find the largest edge weight on the path between $u$ and $v$?

We can use binary lifting. Precompute each vertex's $2^i$-th ancestor and the largest edge weight on the path to that ancestor. Then we get the answer directly while computing the LCA with binary lifting.

### Strict second-best MST

#### Definition

In an undirected graph, it is the spanning tree with the smallest total weight among those whose total weight is **strictly greater than** that of the MST.

#### How to compute it

Look at the process for the non-strict second-best MST above. Why is the result non-strict?

Because the MST guarantees that the largest edge weight on the tree path from $u$ to $v$ is **no greater than** the largest edge weight on any other path from $u$ to $v$. In other words, when the replacing edge has the same weight as the replaced edge in the original tree, the second-best MST we get is non-strict.

The fix is natural: along with the largest edge weight on the path to the $2^i$-th ancestor, we also maintain the **strictly second largest edge weight**. When the replacing edge has the same weight as the largest edge on the path, we replace using the strictly second largest value instead.

This can be done with binary lifting in $O(m \log m)$.

??? note "Implementation"
    ```cpp
    #include <algorithm>
    #include <iostream>
    
    constexpr int INF = 0x3fffffff;
    constexpr long long INF64 = 0x3fffffffffffffffLL;
    
    struct Edge {
      int u, v, val;
    
      bool operator<(const Edge &other) const { return val < other.val; }
    };
    
    Edge e[300010];
    bool used[300010];
    
    int n, m;
    long long sum;
    
    class Tr {
     private:
      struct Edge {
        int to, nxt, val;
      } e[600010];
    
      int cnt, head[100010];
    
      int pnt[100010][22];
      int dpth[100010];
      // largest edge weight on the path to the ancestor
      int maxx[100010][22];
      // strictly second largest edge weight on the path to the ancestor; -INF if none
      int minn[100010][22];
    
     public:
      void addedge(int u, int v, int val) {
        e[++cnt] = Edge{v, head[u], val};
        head[u] = cnt;
      }
    
      void insedge(int u, int v, int val) {
        addedge(u, v, val);
        addedge(v, u, val);
      }
    
      void dfs(int now, int fa) {
        dpth[now] = dpth[fa] + 1;
        pnt[now][0] = fa;
        minn[now][0] = -INF;
        for (int i = 1; (1 << i) <= dpth[now]; i++) {
          pnt[now][i] = pnt[pnt[now][i - 1]][i - 1];
          int kk[4] = {maxx[now][i - 1], maxx[pnt[now][i - 1]][i - 1],
                       minn[now][i - 1], minn[pnt[now][i - 1]][i - 1]};
          // get the maximum of the four values
          std::sort(kk, kk + 4);
          maxx[now][i] = kk[3];
          // get the strictly second largest value
          int ptr = 2;
          while (ptr >= 0 && kk[ptr] == kk[3]) ptr--;
          minn[now][i] = (ptr == -1 ? -INF : kk[ptr]);
        }
    
        for (int i = head[now]; i; i = e[i].nxt) {
          if (e[i].to != fa) {
            maxx[e[i].to][0] = e[i].val;
            dfs(e[i].to, now);
          }
        }
      }
    
      int lca(int a, int b) {
        if (dpth[a] < dpth[b]) std::swap(a, b);
    
        for (int i = 21; i >= 0; i--)
          if (dpth[pnt[a][i]] >= dpth[b]) a = pnt[a][i];
    
        if (a == b) return a;
    
        for (int i = 21; i >= 0; i--) {
          if (pnt[a][i] != pnt[b][i]) {
            a = pnt[a][i];
            b = pnt[b][i];
          }
        }
        return pnt[a][0];
      }
    
      int query(int a, int b, int val) {
        int res = -INF;
        for (int i = 21; i >= 0; i--) {
          if (dpth[pnt[a][i]] >= dpth[b]) {
            if (val != maxx[a][i])
              res = std::max(res, maxx[a][i]);
            else
              res = std::max(res, minn[a][i]);
            a = pnt[a][i];
          }
        }
        return res;
      }
    } tr;
    
    int fa[100010];
    
    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
    
    void Kruskal() {
      int tot = 0;
      std::sort(e + 1, e + m + 1);
      for (int i = 1; i <= n; i++) fa[i] = i;
    
      for (int i = 1; i <= m; i++) {
        int a = find(e[i].u);
        int b = find(e[i].v);
        if (a != b) {
          fa[a] = b;
          tot++;
          tr.insedge(e[i].u, e[i].v, e[i].val);
          sum += e[i].val;
          used[i] = true;
        }
        if (tot == n - 1) break;
      }
    }
    
    int main() {
      std::ios::sync_with_stdio(false);
      std::cin.tie(nullptr);
    
      std::cin >> n >> m;
      for (int i = 1; i <= m; i++) {
        int u, v, val;
        std::cin >> u >> v >> val;
        e[i] = Edge{u, v, val};
      }
    
      Kruskal();
      long long ans = INF64;
      tr.dfs(1, 0);
    
      for (int i = 1; i <= m; i++) {
        if (!used[i]) {
          int _lca = tr.lca(e[i].u, e[i].v);
          // find the largest edge weight on the path that is not equal to e[i].val
          long long tmpa = tr.query(e[i].u, _lca, e[i].val);
          long long tmpb = tr.query(e[i].v, _lca, e[i].val);
          // such an edge may not exist; update the answer only if it does
          if (std::max(tmpa, tmpb) > -INF)
            ans = std::min(ans, sum - std::max(tmpa, tmpb) + e[i].val);
        }
      }
      // output -1 if no second-best spanning tree exists
      std::cout << (ans == INF64 ? -1 : ans) << '\n';
      return 0;
    }
    ```

## Bottleneck spanning tree

### Definition

A bottleneck spanning tree of an undirected graph $G$ is a spanning tree whose largest edge weight is the smallest among all spanning trees of $G$.

### Properties

**Being an MST is a sufficient but not necessary condition for being a bottleneck spanning tree.** That is, every MST is a bottleneck spanning tree, but a bottleneck spanning tree is not necessarily an MST.

The claim that every MST is a bottleneck spanning tree can be proved by contradiction. Let $w$ be the largest edge weight in the MST. If the MST were not a bottleneck spanning tree, then all edge weights of a bottleneck spanning tree would be less than $w$. Remove the longest edge from the MST, and use an edge from the bottleneck spanning tree to connect the two resulting trees. The new spanning tree would have a smaller total weight than the MST, a contradiction.

### Example problem

???+ note "POJ 2395 Out of Hay"
    There are n farms and m edges, with farms numbered 1 to n. Someone starts from farm 1 and travels to the other farms. Find the largest amount of water he must carry along the way. Note that he can refill water at every farm he reaches, and the total path length must be minimized.
    The problem asks for the largest edge of a bottleneck tree, which can be solved by finding an MST.

## Minimum bottleneck path

### Definition

A minimum bottleneck path from x to y in an undirected graph $G$ is a simple path whose largest edge weight is the smallest among all simple paths from x to y.

### Properties

By the definition of the MST, the largest edge weight on a minimum bottleneck path from x to y equals the largest edge weight on the path from x to y in the MST. Although the MST may not be unique, the largest edge weight on the x-to-y path is the same, and minimal, for every MST. In other words, the x-to-y path in any MST is a minimum bottleneck path.

However, not every minimum bottleneck path is the x-to-y path of some MST.

For example, consider the graph below:

![](./images/mst5.png)

There are clearly two minimum bottleneck paths from 1 to 4: 1-2-3-4 and 1-3-4.

But edge 1-2 does not appear in any MST.

### Applications

Since minimum bottleneck paths are not unique, problems usually ask for the largest edge weight on a minimum bottleneck path.

That is, we need the max over a path in the MST.

Both binary lifting and heavy-light decomposition can do this; we will not go into details here.

## Kruskal reconstruction tree

### Definition

While running Kruskal, we add some edges in increasing order of weight. We keep using this order here.

First create $n$ sets, each containing exactly one node with weight $0$.

Each added edge merges two sets. We create a new node whose weight is the weight of the added edge, and make the roots of the two sets its left and right children. Then we merge the two sets and the new node into one set, with the new node as its root.

It is easy to see that after $n-1$ rounds we get a binary tree with exactly $n$ leaves, where every non-leaf node has exactly two children. This tree is called the Kruskal reconstruction tree.

For example:

![](./images/mst5.png)

The Kruskal reconstruction tree of this graph is:

![](./images/mst6.png)

### Properties

It is easy to see that, for two vertices of the original graph, the minimum over all simple paths between them of the largest edge weight = the largest edge weight on the simple path between them in the MST = the weight of their LCA in the Kruskal reconstruction tree.

In other words, all vertices $y$ for which the minimum over simple paths to $x$ of the largest edge weight is $\leq val$ lie in one subtree of the Kruskal reconstruction tree, and they are exactly the leaves of that subtree.

In the Kruskal reconstruction tree, find the shallowest node on the path from $x$ to the root whose weight is $\leq val$. Clearly this is the root of the subtree containing all the valid nodes.

If you need the maximum over all simple paths between two vertices of the smallest edge weight, add edges in decreasing order of weight while running Kruskal.

??? note "[LOJ 137 Minimum Bottleneck Path (Hard Version)](https://loj.ac/problem/137)"
    ```cpp
    --8<-- "docs/graph/code/mst/mst_2.cpp"
    ```

??? note "[NOI 2018 Return Journey](https://uoj.ac/problem/393)"
    First precompute the shortest path from every vertex to the root vertex.
    
    Build the maximum spanning tree by altitude. Clearly, the vertices reachable for each query are those whose path to the query vertex in the maximum spanning tree has minimum edge weight $> p$.
    
    By the properties of the Kruskal reconstruction tree, these vertices all lie in one subtree and are exactly its leaves.
    
    That is, we only need the min weight over the leaves of each subtree of the Kruskal reconstruction tree to answer subtree queries.
    
    The root for each query can be found with binary lifting on the Kruskal reconstruction tree.
    
    The time complexity is $O((n+m+Q) \log n)$.
