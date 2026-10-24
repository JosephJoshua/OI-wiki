Before reading this page, please read the definitions part of [Introduction to network flow](../flow.md).

## Min-cost flow

Given a network $G=(V,E)$, each edge has a capacity $c(u,v)$ and also a cost per unit of flow $w(u,v)$.

When the flow on $(u,v)$ is $f(u,v)$, it costs $f(u,v)\times w(u,v)$.

$w$ is also skew-symmetric, that is, $w(u,v)=-w(v,u)$.

The maximum flow with the smallest total cost in this network is called the **minimum-cost maximum flow**. In other words, we minimize $\sum_{(u,v)\in E}f(u,v)\times w(u,v)$ subject to maximizing $\sum_{(s,v)\in E}f(s,v)$.

## The SSP algorithm

The SSP (Successive Shortest Path) algorithm is a greedy algorithm. Its idea is to repeatedly find the augmenting path with the smallest unit cost and augment along it, until no augmenting path remains in the graph.

If the graph contains a cycle with negative unit cost, the SSP algorithm cannot correctly find the min-cost max flow of the network. In that case, you first need to remove the negative cycles with a cycle-canceling algorithm.

### Proof

We prove that the SSP algorithm is correct using mathematical induction and proof by contradiction.

Let $f_i$ be the minimum cost when the flow is $i$. Assume the initial network has **no negative cycles**. Then $f_0=0$.

Assume the $f_i$ found by the SSP algorithm is the minimum cost. Starting from $f_i$, we find a shortest augmenting path and get $f_{i+1}$. Now $f_{i+1}-f_i$ is the length of this shortest augmenting path.

Suppose there is a smaller $f_{i+1}$; call it $f'_{i+1}$. Since $f_{i+1}-f_i$ already comes from a shortest augmenting path, $f'_{i+1}-f_i$ must correspond to an augmenting path that goes through **at least one negative cycle**.

This gives a contradiction: if there is an augmenting path through at least one negative cycle, then $f_i$ is not the minimum cost. By pushing flow around this negative cycle, we could lower the cost of $f_i$ without increasing the flow out of $s$.

Therefore, the SSP algorithm correctly finds the min-cost max flow of a network without negative cycles.

### Time complexity

If we use the [Bellman–Ford algorithm](../shortest-path.md#bellmanford-algorithm) to find shortest paths, each search for an augmenting path takes $O(nm)$ time. Let the maximum flow of the network be $f$. Then the worst-case time complexity is $O(nmf)$. In fact, the SSP algorithm runs in [pseudo-polynomial time](../../misc/cc-basic.md#pseudo-polynomial-time).

???+ note "Why does the SSP algorithm run in pseudo-polynomial time?"
    The time complexity of the SSP algorithm has an upper bound of $O(nmf)$. This is a polynomial in the range of values, so it is pseudo-polynomial time.
    
    One can construct a network with $m=n^2,f=2^{n/2}$[^note1] on which the SSP algorithm takes $O(n^3 2^{n/2})$ time, so the SSP algorithm is not polynomial time.

### Implementation

Just take the EK algorithm or Dinic's algorithm and replace the step that finds an augmenting path with a shortest-path algorithm that finds the augmenting path with the smallest unit cost.

??? note "Implementation based on the EK algorithm"
    ```cpp
    struct qxx {
      int nex, t, v, c;
    };
    
    qxx e[M];
    int h[N], cnt = 1;
    
    void add_path(int f, int t, int v, int c) {
      e[++cnt] = qxx{h[f], t, v, c}, h[f] = cnt;
    }
    
    void add_flow(int f, int t, int v, int c) {
      add_path(f, t, v, c);
      add_path(t, f, 0, -c);
    }
    
    int dis[N], pre[N], incf[N];
    bool vis[N];
    
    bool spfa() {
      memset(dis, 0x3f, sizeof(dis));
      queue<int> q;
      q.push(s), dis[s] = 0, incf[s] = INF, incf[t] = 0;
      while (q.size()) {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i = h[u]; i; i = e[i].nex) {
          const int &v = e[i].t, &w = e[i].v, &c = e[i].c;
          if (!w || dis[v] <= dis[u] + c) continue;
          dis[v] = dis[u] + c, incf[v] = min(w, incf[u]), pre[v] = i;
          if (!vis[v]) q.push(v), vis[v] = true;
        }
      }
      return incf[t];
    }
    
    int maxflow, mincost;
    
    void update() {
      maxflow += incf[t];
      for (int u = t; u != s; u = e[pre[u] ^ 1].t) {
        e[pre[u]].v -= incf[t], e[pre[u] ^ 1].v += incf[t];
        mincost += incf[t] * e[pre[u]].c;
      }
    }
    
    // Usage: while(spfa())update();
    ```

??? note "Implementation based on Dinic's algorithm"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <queue>
    
    constexpr int N = 5e3 + 5, M = 1e5 + 5;
    constexpr int INF = 0x3f3f3f3f;
    int n, m, tot = 1, lnk[N], cur[N], ter[M], nxt[M], cap[M], cost[M], dis[N], ret;
    bool vis[N];
    
    void add(int u, int v, int w, int c) {
      ter[++tot] = v, nxt[tot] = lnk[u], lnk[u] = tot, cap[tot] = w, cost[tot] = c;
    }
    
    void addedge(int u, int v, int w, int c) { add(u, v, w, c), add(v, u, 0, -c); }
    
    bool spfa(int s, int t) {
      memset(dis, 0x3f, sizeof(dis));
      memcpy(cur, lnk, sizeof(lnk));
      std::queue<int> q;
      q.push(s), dis[s] = 0, vis[s] = true;
      while (!q.empty()) {
        int u = q.front();
        q.pop(), vis[u] = false;
        for (int i = lnk[u]; i; i = nxt[i]) {
          int v = ter[i];
          if (cap[i] && dis[v] > dis[u] + cost[i]) {
            dis[v] = dis[u] + cost[i];
            if (!vis[v]) q.push(v), vis[v] = true;
          }
        }
      }
      return dis[t] != INF;
    }
    
    int dfs(int u, int t, int flow) {
      if (u == t) return flow;
      vis[u] = true;
      int ans = 0;
      for (int &i = cur[u]; i && ans < flow; i = nxt[i]) {
        int v = ter[i];
        if (!vis[v] && cap[i] && dis[v] == dis[u] + cost[i]) {
          int x = dfs(v, t, std::min(cap[i], flow - ans));
          if (x) ret += x * cost[i], cap[i] -= x, cap[i ^ 1] += x, ans += x;
        }
      }
      vis[u] = false;
      return ans;
    }
    
    int mcmf(int s, int t) {
      int ans = 0;
      while (spfa(s, t)) {
        int x;
        while ((x = dfs(s, t, INF))) ans += x;
      }
      return ans;
    }
    
    int main() {
      int s, t;
      scanf("%d%d%d%d", &n, &m, &s, &t);
      while (m--) {
        int u, v, w, c;
        scanf("%d%d%d%d", &u, &v, &w, &c);
        addedge(u, v, w, c);
      }
      int ans = mcmf(s, t);
      printf("%d %d\n", ans, ret);
      return 0;
    }
    ```

### The Primal-Dual algorithm

Finding shortest paths with Bellman–Ford takes $O(nm)$ time, which is worse than Dijkstra's algorithm on both sparse and dense graphs[^note2]. But the network has edges with negative unit cost, so we cannot use Dijkstra's algorithm directly.

The idea of the Primal-Dual algorithm is similar to [Johnson's all-pairs shortest path algorithm](../shortest-path.md#johnsons-all-pairs-shortest-path-algorithm). We give each vertex a potential, which turns the costs of all edges in the network (called edge weights below) into non-negative values. Then we can use Dijkstra's algorithm to find the augmenting path with the smallest unit cost.

First, run a shortest-path algorithm once to get the shortest distance $h_i$ from the source to each vertex (this is also the vertex's initial potential). Then, as in Johnson's algorithm, for an edge from $u$ to $v$ with unit cost $w$, reset its weight to $w+h_u-h_v$.

With potentials set this way, shortest paths in the new network always correspond to shortest paths in the original network. The proof was given in the section on Johnson's algorithm, so we do not repeat it here.

Unlike an ordinary shortest-path problem, the shape of the graph changes after each augmentation, so the potentials of the vertices need to be updated.

How do we update them? Here is the conclusion first. Let $d'_i$ be the shortest distance from the source to vertex $i$ after augmentation (measured with the reset edge weights). Then we just add $d'_i$ to $h_i$. Below we prove that after updating this way, all edge weights in the graph are non-negative.

After one round of augmentation, some edges $(i,j)$ lie on the augmenting path, so the residual network gains the corresponding edges $(j,i)$. These must satisfy $d'_i+(w(i,j)+h_i-h_j)=d'_j$ (otherwise edge $(i,j)$ would not be on the augmenting path). Rearranging gives $w(j,i)+(h_j+d'_j)-(h_i+d'_i)=0$. So the weights of the new edges are non-negative.

For the existing edges, before augmentation we have $d'_i+(w(i,j)+h_i-h_j) - d'_j \geq 0$, so $w(i,j)+(d'_i+h_i)-(d'_j+h_j) \geq 0$. That is, using $h_i+d'_i$ as the new potential does not make the weight of $(i,j)$ negative.

In summary, after augmentation all edge weights are non-negative, and Dijkstra's algorithm correctly finds shortest paths in the graph.

??? note "Reference code"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <queue>
    constexpr int INF = 0x3f3f3f3f;
    using namespace std;
    
    struct edge {
      int v, f, c, next;
    } e[100005];
    
    struct node {
      int v, e;
    } p[10005];
    
    struct mypair {
      int dis, id;
    
      bool operator<(const mypair& a) const { return dis > a.dis; }
    
      mypair(int d, int x) { dis = d, id = x; }
    };
    
    int head[5005], dis[5005], vis[5005], h[5005];
    int n, m, s, t, cnt = 1, maxf, minc;
    
    void addedge(int u, int v, int f, int c) {
      e[++cnt].v = v;
      e[cnt].f = f;
      e[cnt].c = c;
      e[cnt].next = head[u];
      head[u] = cnt;
    }
    
    bool dijkstra() {
      priority_queue<mypair> q;
      for (int i = 1; i <= n; i++) dis[i] = INF;
      memset(vis, 0, sizeof(vis));
      dis[s] = 0;
      q.push(mypair(0, s));
      while (!q.empty()) {
        int u = q.top().id;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u]; i; i = e[i].next) {
          int v = e[i].v, nc = e[i].c + h[u] - h[v];
          if (e[i].f && dis[v] > dis[u] + nc) {
            dis[v] = dis[u] + nc;
            p[v].v = u;
            p[v].e = i;
            if (!vis[v]) q.push(mypair(dis[v], v));
          }
        }
      }
      return dis[t] != INF;
    }
    
    void spfa() {
      queue<int> q;
      memset(h, 63, sizeof(h));
      h[s] = 0, vis[s] = 1;
      q.push(s);
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (int i = head[u]; i; i = e[i].next) {
          int v = e[i].v;
          if (e[i].f && h[v] > h[u] + e[i].c) {
            h[v] = h[u] + e[i].c;
            if (!vis[v]) {
              vis[v] = 1;
              q.push(v);
            }
          }
        }
      }
    }
    
    int main() {
      scanf("%d%d%d%d", &n, &m, &s, &t);
      for (int i = 1; i <= m; i++) {
        int u, v, f, c;
        scanf("%d%d%d%d", &u, &v, &f, &c);
        addedge(u, v, f, c);
        addedge(v, u, 0, -c);
      }
      spfa();  // First compute the initial potentials
      while (dijkstra()) {
        int minf = INF;
        for (int i = 1; i <= n; i++) h[i] += dis[i];
        for (int i = t; i != s; i = p[i].v) minf = min(minf, e[p[i].e].f);
        for (int i = t; i != s; i = p[i].v) {
          e[p[i].e].f -= minf;
          e[p[i].e ^ 1].f += minf;
        }
        maxf += minf;
        minc += minf * h[t];
      }
      printf("%d %d\n", maxf, minc);
      return 0;
    }
    ```

## Exercises

-   [Luogu 3381 [Template] Minimum-Cost Maximum Flow](https://www.luogu.com.cn/problem/P3381)
-   [Luogu 4452 Flight Scheduling](https://www.luogu.com.cn/problem/P4452)
-   [SDOI 2009 Morning Run](https://www.luogu.com.cn/problem/P2153)
-   [SCOI 2007 Car Repair](https://www.luogu.com.cn/problem/P2053)
-   [HAOI 2010 Ordering Goods](https://www.luogu.com.cn/problem/P2517)
-   [NOI 2012 Food Festival](https://loj.ac/problem/2674)

## References and notes

[^note1]: For the detailed construction, see [min\_25's blog](https://web.archive.org/web/20211009144446/https://min-25.hatenablog.com/entry/2018/03/19/235802).

[^note2]: With heap optimization, the time complexity on sparse graphs is $O(m \log n)$. On dense graphs, without heap optimization, it is $O(n^2)$.
