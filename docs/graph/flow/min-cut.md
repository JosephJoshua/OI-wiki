## Concepts

### Cut

For a flow network $G=(V,E)$, a cut is defined as **a way to partition the vertices**: split all vertices into two sets $S$ and $T=V-S$, where the source $s\in S$ and the sink $t\in T$.

### Capacity of a cut

We define the capacity $c(S,T)$ of a cut $(S,T)$ as the total capacity of all edges going from $S$ to $T$, that is, $c(S,T)=\sum_{u\in S,v\in T}c(u,v)$. We may also write $c(s,t)$ for $c(S,T)$.

### Minimum cut

The minimum cut problem asks for a cut $(S,T)$ whose capacity $c(S,T)$ is as small as possible.

## Proof

### Max-flow min-cut theorem

See the section on the max-flow min-cut theorem on the [maximum flow](max-flow.md) page.

## Code

### Minimum cut

By the **max-flow min-cut theorem**, we directly get the following code:

??? note "Reference code"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <queue>
    
    constexpr int N = 1e4 + 5, M = 2e5 + 5;
    int n, m, s, t, tot = 1, lnk[N], ter[M], nxt[M], val[M], dep[N], cur[N];
    
    void add(int u, int v, int w) {
      ter[++tot] = v, nxt[tot] = lnk[u], lnk[u] = tot, val[tot] = w;
    }
    
    void addedge(int u, int v, int w) { add(u, v, w), add(v, u, 0); }
    
    int bfs(int s, int t) {
      memset(dep, 0, sizeof(dep));
      memcpy(cur, lnk, sizeof(lnk));
      std::queue<int> q;
      q.push(s), dep[s] = 1;
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = lnk[u]; i; i = nxt[i]) {
          int v = ter[i];
          if (val[i] && !dep[v]) q.push(v), dep[v] = dep[u] + 1;
        }
      }
      return dep[t];
    }
    
    int dfs(int u, int t, int flow) {
      if (u == t) return flow;
      int ans = 0;
      for (int &i = cur[u]; i && ans < flow; i = nxt[i]) {
        int v = ter[i];
        if (val[i] && dep[v] == dep[u] + 1) {
          int x = dfs(v, t, std::min(val[i], flow - ans));
          if (x) val[i] -= x, val[i ^ 1] += x, ans += x;
        }
      }
      if (ans < flow) dep[u] = -1;
      return ans;
    }
    
    int dinic(int s, int t) {
      int ans = 0;
      while (bfs(s, t)) {
        int x;
        while ((x = dfs(s, t, 1 << 30))) ans += x;
      }
      return ans;
    }
    
    int main() {
      scanf("%d%d%d%d", &n, &m, &s, &t);
      while (m--) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addedge(u, v, w);
      }
      printf("%d\n", dinic(s, t));
      return 0;
    }
    ```

### Finding the cut

Starting from the source $s$, run a DFS that only follows edges with residual capacity greater than $0$. This finds all vertices in the set $S$.

```cpp
void dfs(int u) {
  vis[u] = 1;
  for (int i = lnk[u]; i; i = nxt[i]) {
    int v = ter[i];
    if (!vis[v] && val[i]) dfs(v);
  }
}
```

### Number of cut edges

If you want the cut with the fewest cut edges, just set the capacity of every edge to $1$ and find a minimum cut. If you want the minimum cut that has the fewest cut edges among all minimum cuts, there are two methods:

1.  Change the capacity of every edge from $c(u,v)$ to $c(u,v)(|E| + 1) + 1$ and find a minimum cut in the new graph. This gives the minimum cut of the original graph with the fewest cut edges. The capacity of the new graph's minimum cut divided by $|E| + 1$, rounded down, is the original minimum cut, and the remainder is the number of cut edges.

    This is the same as finding the lexicographically smallest cut, with the cut size as the first key and the number of cut edges as the second key. The factor $|E| + 1$ is strictly larger than the total number of edges, and the number of cut edges is at most the total number of edges. So no matter how many cut edges there are, they cannot outweigh the size of the cut, and the result must be a minimum cut of the original graph. Among the minimum cuts of the original graph, the one with the fewest cut edges becomes the minimum cut of the new graph.

    Note that this method is only correct when all edge capacities are integers: only then is it guaranteed that the number of cut edges $k\le|E|<|E|+1$ never carries over into the higher part. If the capacities are rational, first multiply by a common denominator to make them integers. If the capacities are arbitrary real numbers, or integers would overflow, use the pair $(c(u,v),1)$ as the capacity directly, add componentwise and compare lexicographically. Then any augmenting-path algorithm that only adds, subtracts and compares capacities (such as Dinic's algorithm) runs unchanged.

2.  First find the maximum flow of the graph, then build a new graph: for each arc in the **residual graph** (that is, the forward arc of each edge that is not saturated, and the reverse arc of each edge that carries flow), add an edge with capacity $\infty$; for each saturated edge, add an edge with capacity $1$. Running min cut again then gives the minimum number of cut edges.

    The cut edges of the new graph's minimum cut never include an edge of capacity $\infty$, which means no residual arc points from $S$ to $T$. So in the new graph's minimum cut, every forward edge of the original graph is saturated and every backward edge carries no flow. This shows its capacity equals the maximum flow, so it is also a minimum cut of the original graph. Conversely, every forward edge of any minimum cut of the original graph is saturated, so its capacity in the new graph is exactly its number of cut edges. Therefore the new graph's minimum cut is the minimum cut of the original graph with the fewest cut edges.

    ??? warning "Common mistake: \"only set the capacity of unsaturated edges to $\infty$\""
        There is a common wrong version of this method: after finding the maximum flow, set the capacity of saturated edges to $1$ and of unsaturated edges to $\infty$, then run min cut directly. This seems intuitive, but it is wrong. A counterexample is shown below.
        
        ![](images/min-cut-1.svg)
        
        In the figure, the maximum flow is $16$ (all outgoing edges of $s$ are saturated), the maximum flow is unique, and only edge $A\to B$ is not saturated. Every minimum cut of the original graph has $3$ cut edges. But after resetting the capacities as in the wrong version, the new graph's minimum cut is $2$, reached at $S = \{s,x,y,B\}$. This cut has capacity $20$, so it is not a minimum cut of the original graph: its forward edges $s\to A$ and $B\to t$ are both saturated, but the edge $A\to B$, which carries flow, points from the $T$ side back to the $S$ side, and the wrong version does not rule this out. In the correct method, $A\to B$ carries flow, so a reverse edge $B\to A$ with capacity $\infty$ is added, which prevents this wrong minimum cut.

## Problem model 1

There are $n$ items and two sets $A,B$. If an item is not put into set $A$, it costs $a_i$; if it is not put into set $B$, it costs $b_i$. There are also several constraints of the form $u_i,v_i,w_i$, meaning that if $u_i$ and $v_i$ are not in the same set, it costs $w_i$. Each item must belong to exactly one set. Find the minimum cost.

This is a classic **choose one of two** min cut problem. We create a source $s$ and a sink $t$, one for each set. For the $i$-th item, add an edge from $s$ with capacity $a_i$ and an edge to $t$ with capacity $b_i$. For a constraint $u,v,w$, add a bidirectional edge with capacity $w$ between $u$ and $v$.

When the source and sink are disconnected, every item has picked one of the sets. Cutting an edge to $s$ or $t$ means the item is not put into $A$ or $B$, respectively. Cutting an edge between two items means the two items are not in the same set.

The minimum cut is the minimum cost.

## Problem model 2

Maximum weight closure: given a directed graph where each vertex has a weight (positive, negative or $0$), choose a subgraph with the maximum total weight such that every successor of a vertex in the subgraph is also in the subgraph.

Method: create a super source $s$ and a super sink $t$. If vertex $u$ has positive weight, add a directed edge from $s$ to $u$ whose weight is the vertex's weight. If vertex $u$ has negative weight, add a directed edge from $u$ to $t$ whose weight is the negative of the vertex's weight. Set the weights of all edges of the original graph to $\infty$. Run maximum flow; the sum of all positive weights minus the maximum flow is the answer.

A few small lemmas prove this:

1.  Every valid subgraph corresponds to a cut in the flow network. Each cut splits the network into two parts, and the part connected to $s$ has no edge pointing to the other part, so it satisfies the condition above. This statement holds in both directions.
2.  Each edge removed by the minimum cut must be connected to $s$ or $t$. Otherwise its weight is $\infty$, and it could not be part of a minimum cut.
3.  For the chosen subgraph, total weight $=$ sum of all positive weights $-$ sum of weights of the positive vertices we did not choose $+$ sum of weights of the negative vertices we chose. When we do not choose a positive vertex, its edge to $s$ is cut; when we choose a negative vertex, its edge to $t$ is cut. The total weight of the cut edges is the capacity of the cut. So the formula becomes: total weight $=$ sum of all positive weights $-$ capacity of the cut.
4.  So we conclude: maximum total weight $=$ sum of all positive weights $-$ minimum cut $=$ sum of all positive weights $-$ maximum flow.

## Exercises

-   [USACO 4.4 Pollutant Control](https://www.luogu.com.cn/problem/P1344)
-   [USACO 5.4 Telecowmunication](https://www.luogu.com.cn/problem/P1345)
-   [Luogu 1361 Little M's Crops](https://www.luogu.com.cn/problem/P1361)
-   [SHOI 2007 Kind Voting](https://www.luogu.com.cn/problem/P2057)
-   [Space Flight Planning Problem](https://www.luogu.com.cn/problem/P2762)
