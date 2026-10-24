## Definition

Edges are directed, and there are no cycles.

Its full name is Directed Acyclic Graph, abbreviated DAG.

## Properties

-   A graph that can be [topologically sorted](./topo.md) must be a directed acyclic graph;

    if there were a cycle, no ordering could satisfy the condition for any two vertices on that cycle.

-   A directed acyclic graph can always be topologically sorted;

    (by induction) assume every directed acyclic graph with at most $k$ vertices can be topologically sorted; for one with exactly $k$ vertices, just consider what remains after the first step of the topological sort.

## Testing

How do we test whether a graph is a directed acyclic graph?

Just check whether it can be [topologically sorted](./topo.md).

There is also another way: run a [DFS](../search/dfs.md) on the graph and check whether the resulting DFS tree has any non-tree edge pointing to an ancestor (a back edge). If it does, there is a cycle.

## Applications

### Longest (shortest) paths with DP

On a general graph, the best time complexity for single-source longest (shortest) paths is $O(nm)$ ([Bellman–Ford algorithm](./shortest-path.md#bellmanford-算法), which works with negative weights) or $O(m \log m)$ ([Dijkstra's algorithm](./shortest-path.md#dijkstra-算法), which needs non-negative weights).

On a DAG, however, we can find longest (shortest) paths with DP, bringing the time complexity down to $O(n+m)$. The transition is $dis_v = min(dis_v, dis_u + w_{u,v})$ or $dis_v = max(dis_v, dis_u + w_{u,v})$.

After topological sorting, go through the vertices in topological order and use the current vertex to update the vertices after it.

```cpp
struct edge {
  int v, w;
};

int n, m;
vector<edge> e[MAXN];
vector<int> L;                               // stores the topological order
int max_dis[MAXN], min_dis[MAXN], in[MAXN];  // in stores each vertex's in-degree

void toposort() {  // topological sort
  queue<int> S;
  memset(in, 0, sizeof(in));
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < e[i].size(); j++) {
      in[e[i][j].v]++;
    }
  }
  for (int i = 1; i <= n; i++)
    if (in[i] == 0) S.push(i);
  while (!S.empty()) {
    int u = S.front();
    S.pop();
    L.push_back(u);
    for (int i = 0; i < e[u].size(); i++) {
      if (--in[e[u][i].v] == 0) {
        S.push(e[u][i].v);
      }
    }
  }
}

void dp(int s) {  // single-source longest (shortest) paths from s
  toposort();     // topologically sort first
  memset(min_dis, 0x3f, sizeof(min_dis));
  memset(max_dis, 0, sizeof(max_dis));
  min_dis[s] = 0;
  for (int i = 0; i < L.size(); i++) {
    int u = L[i];
    for (int j = 0; j < e[u].size(); j++) {
      min_dis[e[u][j].v] = min(min_dis[e[u][j].v], min_dis[u] + e[u][j].w);
      max_dis[e[u][j].v] = max(max_dis[e[u][j].v], max_dis[u] + e[u][j].w);
    }
  }
}
```

See also: [DP on DAGs](../dp/dag.md).
