author: Ir1d, sshwy, Xeonacid, partychicken, Anguei, HeRaNO

In OI, before you can work with a graph, you first need to learn how to store it.

## Conventions

This page assumes the reader has read and understood the basics in [Graph theory concepts](./concept.md). If you run into trouble while reading, you can also look things up in [Graph theory concepts](./concept.md).

On this page, $n$ is the number of vertices, $m$ is the number of edges, and $d^+(u)$ is the out-degree of vertex $u$, that is, the number of edges starting at $u$.

## Edge list

### Method

Use an array to store the edges. Each element of the array holds the start and end of one edge (and its weight, for a weighted graph). (Or use several arrays to store the starts, ends and weights separately.)

??? note "Reference code"
    === "C++"
        ```cpp
        #include <iostream>
        #include <vector>
        
        using namespace std;
        
        struct Edge {
          int u, v;
        };
        
        int n, m;
        vector<Edge> e;
        vector<bool> vis;
        
        bool find_edge(int u, int v) {
          for (int i = 1; i <= m; ++i) {
            if (e[i].u == u && e[i].v == v) {
              return true;
            }
          }
          return false;
        }
        
        void dfs(int u) {
          if (vis[u]) return;
          vis[u] = true;
          for (int i = 1; i <= m; ++i) {
            if (e[i].u == u) {
              dfs(e[i].v);
            }
          }
        }
        
        int main() {
          cin >> n >> m;
        
          vis.resize(n + 1, false);
          e.resize(m + 1);
        
          for (int i = 1; i <= m; ++i) cin >> e[i].u >> e[i].v;
        
          return 0;
        }
        ```
    
    === "Python"
        ```python
        class Edge:
            def __init__(self, u=0, v=0):
                self.u = u
                self.v = v
        
        
        n, m = map(int, input().split())
        
        e = [Edge() for _ in range(m)]
        vis = [False] * n
        
        for i in range(m):
            e[i].u, e[i].v = map(int, input().split())
        
        
        def find_edge(u, v):
            for i in range(m):
                if e[i].u == u and e[i].v == v:
                    return True
            return False
        
        
        def dfs(u):
            if vis[u]:
                return
            vis[u] = True
            for i in range(m):
                if e[i].u == u:
                    dfs(e[i].v)
        ```

### Complexity

Checking whether a given edge exists: $O(m)$.

Going through all outgoing edges of a vertex: $O(m)$.

Traversing the whole graph: $O(nm)$.

Space complexity: $O(m)$.

### Applications

Since traversal with an edge list is slow, it is usually not used to traverse graphs.

In [Kruskal's algorithm](./mst.md#kruskals-algorithm), the edges must be sorted by weight, so an edge list is needed.

Some problems require building the graph several times (for example, once for the original graph and once for the reversed graph). You can either store several graphs at once using other data structures, or store the edges directly and rebuild the graph from them when needed.

## Adjacency matrix

### Method

Use a 2D array `adj` to store the edges, where `adj[u][v]` is 1 if there is an edge from $u$ to $v$ and 0 otherwise. For a weighted graph, you can store the weight of the edge from $u$ to $v$ in `adj[u][v]`.

??? note "Reference code"
    === "C++"
        ```cpp
        #include <iostream>
        #include <vector>
        
        using namespace std;
        
        int n, m;
        vector<bool> vis;
        vector<vector<bool>> adj;
        
        bool find_edge(int u, int v) { return adj[u][v]; }
        
        void dfs(int u) {
          if (vis[u]) return;
          vis[u] = true;
          for (int v = 1; v <= n; ++v) {
            if (adj[u][v]) {
              dfs(v);
            }
          }
        }
        
        int main() {
          cin >> n >> m;
        
          vis.resize(n + 1);
          adj.resize(n + 1, vector<bool>(n + 1));
        
          for (int i = 1; i <= m; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u][v] = true;
          }
        
          return 0;
        }
        ```
    
    === "Python"
        ```python
        vis = [False] * (n + 1)
        adj = [[False] * (n + 1) for _ in range(n + 1)]
        
        for i in range(1, m + 1):
            u, v = map(lambda x: int(x), input().split())
            adj[u][v] = True
        
        
        def find_edge(u, v):
            return adj[u][v]
        
        
        def dfs(u):
            if vis[u]:
                return
            vis[u] = True
            for v in range(1, n + 1):
                if adj[u][v]:
                    dfs(v)
        ```

### Complexity

Checking whether a given edge exists: $O(1)$.

Going through all outgoing edges of a vertex: $O(n)$.

Traversing the whole graph: $O(n^2)$.

Space complexity: $O(n^2)$.

### Applications

An adjacency matrix only works when there are no parallel edges (or when parallel edges can be ignored).

Its biggest advantage is that it can check whether an edge exists in $O(1)$.

An adjacency matrix is very inefficient on sparse graphs (and on graphs with many vertices, it uses too much memory), so it is usually only used on dense graphs.

## Adjacency list

### Method

Use an array of data structures that support adding elements dynamically, such as `vector<int> adj[n + 1]`, to store the edges. Here `adj[u]` stores information about all outgoing edges of vertex $u$ (end vertex, weight, and so on).

??? note "Reference code"
    === "C++"
        ```cpp
        #include <iostream>
        #include <vector>
        
        using namespace std;
        
        int n, m;
        vector<bool> vis;
        vector<vector<int>> adj;
        
        bool find_edge(int u, int v) {
          for (int i = 0; i < adj[u].size(); ++i) {
            if (adj[u][i] == v) {
              return true;
            }
          }
          return false;
        }
        
        void dfs(int u) {
          if (vis[u]) return;
          vis[u] = true;
          for (int i = 0; i < adj[u].size(); ++i) dfs(adj[u][i]);
        }
        
        int main() {
          cin >> n >> m;
        
          vis.resize(n + 1);
          adj.resize(n + 1);
        
          for (int i = 1; i <= m; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
          }
        
          return 0;
        }
        ```
    
    === "Python"
        ```python
        vis = [False] * (n + 1)
        adj = [[] for _ in range(n + 1)]
        
        for i in range(1, m + 1):
            u, v = map(lambda x: int(x), input().split())
            adj[u].append(v)
        
        
        def find_edge(u, v):
            for i in range(0, len(adj[u])):
                if adj[u][i] == v:
                    return True
            return False
        
        
        def dfs(u):
            if vis[u]:
                return
            vis[u] = True
            for i in range(0, len(adj[u])):
                dfs(adj[u][i])
        ```

### Complexity

Checking whether there is an edge from $u$ to $v$: $O(d^+(u))$ (if the lists are sorted in advance, [binary search](../basic/binary.md) brings this down to $O(\log(d^+(u)))$).

Going through all outgoing edges of vertex $u$: $O(d^+(u))$.

Traversing the whole graph: $O(n+m)$.

Space complexity: $O(m)$.

### Applications

It works well for storing all kinds of graphs, unless you have special needs (for example, if you need to check quickly whether an edge exists and there are few vertices, you can use an adjacency matrix).

It is especially suitable when you need to sort the outgoing edges of a vertex.

## Linked forward star

### Method

It is essentially an adjacency list implemented with linked lists. The core code is:

=== "C++"
    ```cpp
    // head[u] and cnt both start at -1
    void add(int u, int v) {
      nxt[++cnt] = head[u];  // next edge after the current one
      head[u] = cnt;         // first edge of start vertex u
      to[cnt] = v;           // end vertex of the current edge
    }
    
    // Go through the outgoing edges of u
    for (int i = head[u]; ~i; i = nxt[i]) {  // ~i means i != -1
      int v = to[i];
    }
    ```

=== "Python"
    ```python
    # head[u] and cnt both start at -1
    def add(u, v):
        cnt = cnt + 1
        nex[cnt] = head[u]  # next edge after the current one
        head[u] = cnt  # first edge of start vertex u
        to[cnt] = v  # end vertex of the current edge
    
    
    # Go through the outgoing edges of u
    i = head[u]
    while ~i:  # ~i means i != -1
        v = to[i]
        i = nxt[i]
    ```

??? note "Reference code"
    ```cpp
    #include <iostream>
    #include <vector>
    
    using namespace std;
    
    int n, m;
    vector<bool> vis;
    vector<int> head, nxt, to;
    
    void add(int u, int v) {
      nxt.push_back(head[u]);
      head[u] = to.size();
      to.push_back(v);
    }
    
    bool find_edge(int u, int v) {
      for (int i = head[u]; ~i; i = nxt[i]) {  // ~i means i != -1
        if (to[i] == v) {
          return true;
        }
      }
      return false;
    }
    
    void dfs(int u) {
      if (vis[u]) return;
      vis[u] = true;
      for (int i = head[u]; ~i; i = nxt[i]) dfs(to[i]);
    }
    
    int main() {
      cin >> n >> m;
    
      vis.resize(n + 1, false);
      head.resize(n + 1, -1);
    
      for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        add(u, v);
      }
    
      return 0;
    }
    ```

### Complexity

Checking whether there is an edge from $u$ to $v$: $O(d^+(u))$.

Going through all outgoing edges of vertex $u$: $O(d^+(u))$.

Traversing the whole graph: $O(n+m)$.

Space complexity: $O(m)$.

### Applications

It works well for storing all kinds of graphs, but it cannot quickly check whether an edge exists, and it is not convenient for sorting the outgoing edges of a vertex.

Its advantage is that the edges are numbered, which is sometimes very useful. Also, if `cnt` starts at an odd value, then when storing edges in both directions, `i ^ 1` is the reverse edge of `i` (often used in [network flow](./flow.md)).
