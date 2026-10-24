## Introduction

???+ question "Problem"
    Given a graph, find the smallest total edge weight of a cycle made of $n$ vertices $(n\ge 3)$.

The length of the minimum cycle of a graph is also called its girth.

## Process

### Brute force

Suppose there is an edge of length $w$ between $u$ and $v$. Let $dis(u,v)$ be the shortest path between $u$ and $v$ after deleting the edge between them.

Then the minimum cycle through this edge in an undirected graph has length $dis(u,v)+w$.

Note that for a directed graph the formula must be changed: the minimum cycle is $dis(v,u)+w$.

The total time complexity is $O(n^2m)$.

### Dijkstra

Related link: [Shortest paths/Dijkstra](./shortest-path.md#dijkstras-algorithm)

#### Process

Enumerate all edges. Each time, delete one edge and run Dijkstra from its starting vertex. The reasoning is the same as above.

#### Properties

The time complexity is $O(m(n+m)\log n)$.

### Floyd

Related link: [Shortest paths/Floyd](./shortest-path.md#floyds-algorithm)

#### Process

Let the weight of the edge between $u,v$ in the original graph be $val\left(u,v\right)$.

Notice that the Floyd algorithm has a property: when the outermost loop reaches vertex $k$ (before the $k$-th iteration starts), $dis_{u,v}$ in the shortest path array $dis$ is the shortest path from $u$ to $v$ that only passes through vertices numbered in $\left[1, k\right)$.

By definition, a minimum cycle has at least three vertices. Let $w$ be the vertex with the largest number on it, and let $u,v$ be the two neighbors of $w$ on the cycle. Then when the outermost loop reaches $k=w$, the length of this cycle is $dis_{u,v}+val\left(v,w\right)+val\left(w,u\right)$.

So during the loop, for each $k$, enumerate the pairs $(i,j)$ with $i<k,j<k$ and update the answer.

#### Recording the path

We now know the cycle looks like $u\to k\to v$, followed by a way back from $v$ to $u$ (through vertices numbered $<k$).

The problem becomes finding the path $v\leadsto u$. By the triangle inequality $dis_{u,v}\le dis_{u,i}+dis_{i,v}$, we record $pos_{u,v}=j$, a vertex such that $dis_{u,v}=dis_{u,j}+dis_{j,v}$. Clearly $j$ lies on the path $v\leadsto u$.

So we can split the path into two parts, $v\leadsto j$ and $j\leadsto u$, and handle each one recursively.

???+ note "Proof that the recursion does not loop forever"
    We use proof by contradiction.
    
    Suppose the cycle passes through some vertex $u$ more than once. Then the cycle must contain a part that starts at $u$, goes through some edges, and comes back to $u$. This forms a new cycle.
    
    Since the graph has no negative cycles (if it had one, there would be no minimum cycle), the total weight of the new cycle must be at most that of the original cycle.
    
    So we only need to cut out this smaller cycle, and then no vertex $u$ is visited twice. This contradicts the assumption, so the cycle never visits a vertex twice.
    
    So when the recursion reaches two vertices $u,v$, $pos_{u,v}$ must differ from both of their numbers; that is, a new vertex is added.
    
    In particular, when $u$ and $v$ are adjacent, we simply return.
    
    Since there are $n$ vertices in total, the number of additions (that is, the number of recursive calls) cannot exceed $n$, so the recursion does not loop forever.

#### Properties

Time complexity: $O(n^3)$.

#### Implementation

Here are reference implementations in C++ and Python (with path recording):

=== "C++"
    ```cpp
    // the graph has n vertices
    int val[MAXN + 1][MAXN + 1];  // adjacency matrix of the original graph
    int cnt, path[MAXN + 5];      // path and length of the minimum cycle
    
    void get_path(int u, int v) {  // get the path between u and v
      if (pos[u][v] == 0) return;
    
      int k = pos[u][v];
      get_path(u, k);
      path[++cnt] = k;
      get_path(k, v);
    }
    
    void Floyd(const int &n) {
      static int dis[MAXN + 1][MAXN + 1];  // shortest path matrix
      static int pos[MAXN + 1][MAXN + 1];
      memcpy(dis, val, sizeof(val));
      memset(pos, 0, sizeof(pos));
      for (int k = 1; k <= n; ++k) {
        for (int i = 1; i < k; ++i)
          for (int j = 1; j < i; ++j)
            if (ans >
                (long long)val[i][k] + val[k][j] + dis[i][j]) {  // found a shorter cycle
              // since j<i<k here, the three vertices are distinct, so no zero-length cycle appears.
              ans = val[i][k] + val[k][j] + dis[i][j], cnt = 0;
              path[++cnt] = i, path[++cnt] = k,
              path[++cnt] = j;  // add i, k, j in order
              get_path(j, i);   // add the path from j to i
            }
    
        for (int i = 1; i <= n; ++i)  // regular Floyd shortest path update
          for (int j = 1; j <= n; ++j) {
            if (dis[i][j] > dis[i][k] + dis[k][j]) {
              dis[i][j] = dis[i][k] + dis[k][j];
              pos[i][j] = k;  // the current path is improved via k
            }
          }
      }
    }
    ```

=== "Python"
    ```python
    # a large enough value to represent infinity
    INF = sys.maxsize
    
    
    def get_path(i, j, pos, path, cnt):
        """
        Recursively get the intermediate nodes on the shortest path from node i to node j.
    
        Args:
            i (int): start node (0-based index).
            j (int): end node (0-based index).
            pos (list[list[int]]): matrix of intermediate nodes on shortest paths. pos[i][j] = k means the shortest path from i to j goes through k.
            path (list[int]): list storing the path nodes (0-based index).
            cnt (int): current number of path nodes.
    
        Returns:
            int: updated number of path nodes.
        """
        # if pos[i][j] is -1, there is no intermediate node between i and j
        if pos[i][j] == -1:
            return cnt
    
        # get the intermediate node k
        k = pos[i][j]
        # recursively get the path from i to k
        cnt = get_path(i, k, pos, path, cnt)
        # add the intermediate node k to the path
        path[cnt] = k
        cnt += 1
        # recursively get the path from k to j
        cnt = get_path(k, j, pos, path, cnt)
        return cnt
    
    
    def find_minimum_cycle_undirected(n, edges):
        """
        Find the minimum cycle in an undirected graph with the Floyd-Warshall algorithm.
    
        Args:
            n (int): number of nodes in the graph (1 to n).
            edges (list[tuple]): list of edges; each element is (u, v, w), meaning an edge of weight w between nodes u and v.
                                 Node indices are 1 to n.
    
        Returns:
            tuple: the length and path of the minimum cycle.
                   If there is no cycle, return (INF, []).
                   The path is a list of node indices (1-based index).
        """
        # 0-based indexing is used internally
        N = n
        # initialize adjacency matrix g with the original edge weights
        g = [[INF for _ in range(N)] for _ in range(N)]
        # initialize shortest path matrix dis, same as g at the start
        dis = [[INF for _ in range(N)] for _ in range(N)]
        # initialize the pos matrix, which records intermediate nodes of shortest paths
        pos = [[-1 for _ in range(N)] for _ in range(N)]
    
        # set the diagonal to 0 (distance from a node to itself)
        for i in range(N):
            g[i][i] = 0
            dis[i][i] = 0
    
        # build the adjacency matrix from the input edges (undirected graph)
        for u, v, w in edges:
            # convert 1-based indices to 0-based
            u -= 1
            v -= 1
            # in an undirected graph, edges go both ways
            g[u][v] = min(g[u][v], w)
            g[v][u] = min(g[v][u], w)
            dis[u][v] = min(dis[u][v], w)
            dis[v][u] = min(dis[v][u], w)
    
        # initialize the minimum cycle length to infinity
        min_cycle_len = INF
        # initialize the minimum cycle path
        min_cycle_path = []
    
        # core of the Floyd-Warshall algorithm
        # k is the intermediate node (0-based index)
        for k in range(N):
            # before updating dis[i][j], check whether node k forms a smaller cycle
            # the cycle is i -> k -> j -> ... -> i
            # dis[i][j] here is the shortest path using only nodes 0 to k-1 as intermediate nodes
            # the C++ code loops with i < k and j < i; we follow the same logic here (0-based)
            for i in range(k):  # 0 <= i < k
                for j in range(i):  # 0 <= j < i
                    # check whether i, k, j form a cycle closed through dis[i][j]
                    # make sure the original edges g[i][k] and g[k][j] exist (not INF)
                    # and the shortest path dis[i][j] from i to j exists (not INF)
                    if g[i][k] != INF and g[k][j] != INF and dis[i][j] != INF:
                        current_cycle_len = g[i][k] + g[k][j] + dis[i][j]
                        if current_cycle_len < min_cycle_len:
                            min_cycle_len = current_cycle_len
                            # rebuild the path
                            path = [0] * (N + 5)  # temporary array for the path, large enough
                            cnt = 0
                            # add i, k, j to the path in this order
                            path[cnt] = i
                            cnt += 1
                            path[cnt] = k
                            cnt += 1
                            path[cnt] = j
                            cnt += 1
                            # get the intermediate nodes on the shortest path from j to i (using dis and pos computed so far)
                            cnt = get_path(j, i, pos, path, cnt)
                            # extract the actual path nodes (drop the unused part)
                            # convert 0-based indices to 1-based
                            min_cycle_path = [node + 1 for node in path[:cnt]]
    
            # standard Floyd-Warshall shortest path update
            for i in range(N):
                for j in range(N):
                    if (
                        dis[i][k] != INF
                        and dis[k][j] != INF
                        and dis[i][j] > dis[i][k] + dis[k][j]
                    ):
                        dis[i][j] = dis[i][k] + dis[k][j]
                        # record that the shortest path from i to j goes through k
                        pos[i][j] = k
    
        return min_cycle_len, min_cycle_path
    ```

## Template problem

??? note "[AcWing 344 Sightseeing Trip](https://www.acwing.com/problem/content/346)"
    Given an undirected graph with $n$ vertices, find a cycle with at least $3$ vertices, with no repeated vertices, whose total edge length is as small as possible.
    
    This is called the minimum cycle problem for undirected graphs.
    
    You need to output a minimum cycle. If there are several, output any one of them.
    
    $n \le 100$

An $O(n^3)$ solution is fast enough, so we just apply the Floyd minimum cycle method.

=== "C++"
    ```cpp
    #include <bits/stdc++.h>
    using lint = long long;
    // a large enough constant for the maximum number of nodes
    const int MAXN = 110;
    
    // a large enough value representing infinity, used to initialize the minimum cycle length
    lint ans = 1e9;  // lint is an alias for long long
    
    // number of nodes n and edges m
    // cnt is the number of nodes on the minimum cycle path
    // path stores the nodes of the minimum cycle
    int n, m, cnt, path[MAXN];
    
    // g is the adjacency matrix of the original graph
    // dis is the shortest path matrix (updated while Floyd-Warshall runs)
    // pos records intermediate nodes; pos[i][j] = k means the shortest path from i to j goes through k
    int g[MAXN][MAXN], dis[MAXN][MAXN], pos[MAXN][MAXN];
    
    // recursive function: get the intermediate nodes on the shortest path from u to v
    // rebuild the path from the pos matrix
    void get_path(int u, int v) {
      // if pos[u][v] is 0, there is no intermediate node between u and v; return
      if (pos[u][v] == 0) return;
    
      // get the intermediate node k
      int k = pos[u][v];
      // recursively get the path from u to k
      get_path(u, k);
      // add the intermediate node k to the path
      path[++cnt] = k;
      // recursively get the path from k to v
      get_path(k, v);
    }
    
    // Floyd-Warshall function: find the minimum cycle in the graph
    void Floyd() {
      // outer loop: k is the intermediate node (1 to n)
      for (int k = 1; k <= n; ++k) {
        // inner loops over i and j: check whether node k forms a smaller cycle
        // the loop order is i from 1 to k-1, j from 1 to i-1
        // this checks the cycle i -> k -> j -> ... -> i
        for (int i = 1; i < k; ++i)
          for (int j = 1; j < i; ++j)
            // check whether joining i and j through node k forms a smaller cycle
            // the cycle length is the original edge weight g[i][k] from i to k + the original edge weight g[k][j] from k to j
            // + the current shortest path dis[i][j] from i to j
            if (ans > (long long)g[i][k] + g[k][j] + dis[i][j]) {
              // found a smaller cycle
              ans = g[i][k] + g[k][j] + dis[i][j];  // update the minimum cycle length
              cnt = 0;                              // reset the path count
              // add i, k, j to the path in order
              path[++cnt] = i, path[++cnt] = k, path[++cnt] = j;
              // add the intermediate nodes on the shortest path from j to i
              get_path(j, i);
            }
    
        // standard Floyd-Warshall shortest path update
        // i from 1 to n, j from 1 to n
        for (int i = 1; i <= n; ++i)
          for (int j = 1; j <= n; ++j) {
            // if going through k gives a shorter path from i to j
            if (dis[i][j] > dis[i][k] + dis[k][j]) {
              // update the shortest path
              dis[i][j] = dis[i][k] + dis[k][j];
              // record that the shortest path from i to j goes through k
              pos[i][j] = k;
            }
          }
      }
    }
    
    // main function
    int main() {
      // read the number of nodes n and edges m
      std::cin >> n >> m;
      // initialize the adjacency matrix g with all weights set to infinity (0x3f usually means a large value)
      memset(g, 0x3f, sizeof(g));
      // set the distance from each node to itself to 0
      for (int i = 1; i <= n; ++i) g[i][i] = 0;
      // read m edges and build the adjacency matrix g
      // in an undirected graph, edges go both ways; keep the smaller weight
      for (int i = 0, u, v, w; i < m; ++i) {
        std::cin >> u >> v >> w;
        g[u][v] = g[v][u] = std::min(g[u][v], w);
      }
      // copy the adjacency matrix g into the shortest path matrix dis
      memcpy(dis, g, sizeof(g));
      // run Floyd to find the minimum cycle
      Floyd();
      // check from the minimum cycle length whether a cycle exists
      if (ans == 1e9) {  // if it is still infinity, there is no cycle
        puts("No solution.");
      } else {
        // if a cycle exists, print the path nodes
        // std::cout << "ans = " << ans << std::endl; // print the minimum cycle length (commented out)
        // print the path nodes, separated by spaces
        for (int i = 1; i <= cnt; ++i)
          std::cout << path[i]
                    << (i == cnt ? "" : " ");  // no space after the last node
        std::cout << std::endl;                // newline after printing the path
      }
      return 0;
    }
    ```

=== "Python"
    ```python
    import copy
    import sys
    
    # a large enough value to represent infinity
    INF = sys.maxsize
    
    
    def get_path(i, j, pos, path, cnt):
        """
        Recursively get the intermediate nodes on the shortest path from node i to node j.
    
        Args:
            i (int): start node (0-based index).
            j (int): end node (0-based index).
            pos (list[list[int]]): matrix of intermediate nodes on shortest paths. pos[i][j] = k means the shortest path from i to j goes through k.
            path (list[int]): list storing the path nodes (0-based index).
            cnt (int): current number of path nodes.
    
        Returns:
            int: updated number of path nodes.
        """
        # if pos[i][j] is -1, there is no intermediate node between i and j
        if pos[i][j] == -1:
            return cnt
    
        # get the intermediate node k
        k = pos[i][j]
        # recursively get the path from i to k
        cnt = get_path(i, k, pos, path, cnt)
        # add the intermediate node k to the path
        path[cnt] = k
        cnt += 1
        # recursively get the path from k to j
        cnt = get_path(k, j, pos, path, cnt)
        return cnt
    
    
    def find_minimum_cycle_undirected(n, edges):
        """
        Find the minimum cycle in an undirected graph with the Floyd-Warshall algorithm.
    
        Args:
            n (int): number of nodes in the graph (1 to n).
            edges (list[tuple]): list of edges; each element is (u, v, w), meaning an edge of weight w between nodes u and v.
                                 Node indices are 1 to n.
    
        Returns:
            tuple: the length and path of the minimum cycle.
                   If there is no cycle, return (INF, []).
                   The path is a list of node indices (1-based index).
        """
        # 0-based indexing is used internally
        N = n
        # initialize adjacency matrix g with the original edge weights
        g = [[INF for _ in range(N)] for _ in range(N)]
        # initialize shortest path matrix dis, same as g at the start
        dis = [[INF for _ in range(N)] for _ in range(N)]
        # initialize the pos matrix, which records intermediate nodes of shortest paths
        pos = [[-1 for _ in range(N)] for _ in range(N)]
    
        # set the diagonal to 0 (distance from a node to itself)
        for i in range(N):
            g[i][i] = 0
            dis[i][i] = 0
    
        # build the adjacency matrix from the input edges (undirected graph)
        for u, v, w in edges:
            # convert 1-based indices to 0-based
            u -= 1
            v -= 1
            # in an undirected graph, edges go both ways
            g[u][v] = min(g[u][v], w)
            g[v][u] = min(g[v][u], w)
            dis[u][v] = min(dis[u][v], w)
            dis[v][u] = min(dis[v][u], w)
    
        # initialize the minimum cycle length to infinity
        min_cycle_len = INF
        # initialize the minimum cycle path
        min_cycle_path = []
    
        # core of the Floyd-Warshall algorithm
        # k is the intermediate node (0-based index)
        for k in range(N):
            # before updating dis[i][j], check whether node k forms a smaller cycle
            # the cycle is i -> k -> j -> ... -> i
            # dis[i][j] here is the shortest path using only nodes 0 to k-1 as intermediate nodes
            # the C++ code loops with i < k and j < i; we follow the same logic here (0-based)
            for i in range(k):  # 0 <= i < k
                for j in range(i):  # 0 <= j < i
                    # check whether i, k, j form a cycle closed through dis[i][j]
                    # make sure the original edges g[i][k] and g[k][j] exist (not INF)
                    # and the shortest path dis[i][j] from i to j exists (not INF)
                    if g[i][k] != INF and g[k][j] != INF and dis[i][j] != INF:
                        current_cycle_len = g[i][k] + g[k][j] + dis[i][j]
                        if current_cycle_len < min_cycle_len:
                            min_cycle_len = current_cycle_len
                            # rebuild the path
                            path = [0] * (N + 5)  # temporary array for the path, large enough
                            cnt = 0
                            # add i, k, j to the path in this order
                            path[cnt] = i
                            cnt += 1
                            path[cnt] = k
                            cnt += 1
                            path[cnt] = j
                            cnt += 1
                            # get the intermediate nodes on the shortest path from j to i (using dis and pos computed so far)
                            cnt = get_path(j, i, pos, path, cnt)
                            # extract the actual path nodes (drop the unused part)
                            # convert 0-based indices to 1-based
                            min_cycle_path = [node + 1 for node in path[:cnt]]
    
            # standard Floyd-Warshall shortest path update
            for i in range(N):
                for j in range(N):
                    if (
                        dis[i][k] != INF
                        and dis[k][j] != INF
                        and dis[i][j] > dis[i][k] + dis[k][j]
                    ):
                        dis[i][j] = dis[i][k] + dis[k][j]
                        # record that the shortest path from i to j goes through k
                        pos[i][j] = k
    
        return min_cycle_len, min_cycle_path
    
    
    # --- main entry point ---
    if __name__ == "__main__":
        # read the number of nodes n and edges m
        n, m = map(int, sys.stdin.readline().split())
    
        # read the edges
        edges = []
        for _ in range(m):
            u, v, w = map(int, sys.stdin.readline().split())
            edges.append((u, v, w))
    
        # find the minimum cycle
        min_len, path = find_minimum_cycle_undirected(n, edges)
    
        # print the result
        if min_len == INF:
            print("No solution.")
        else:
            # print the path nodes (1-based index), separated by spaces
            print(" ".join(map(str, path)))
    ```

## Example problem 2

GDOI2018 Day2 Patrol

Given an undirected graph with $n$ vertices and no negative edges, perform $q$ operations of three kinds:

1.  Delete a vertex and its incident edges from the graph
2.  Restore a deleted vertex and its incident edges
3.  Query the size of the minimum cycle containing vertex $x$

For $50\%$ of the data, $n,q \le 100$.

For every simple cycle that contains vertex $x$, there are two edges on it incident to $x$. Deleting either of them turns the simple cycle into a simple path.

So enumerate all edges incident to $x$, delete one of them each time, and run Dijkstra once.

Or simply run Floyd for each query to find the minimum cycle, in $O(qn^3)$.

For $100\%$ of the data, $n,q \le 400$.

We still use the Floyd minimum cycle algorithm.

Ignoring deletions for a moment: removing the query vertex breaks a simple cycle into a simple path.

But this time we compute the second step with Floyd instead.

So the answer requires the distance between every pair of vertices without passing through the query vertex $x$.

How do we handle this online?

We force it offline and use an offline method to avoid deletions.

Sort the queries by time and build a segment tree over them.

Each vertex is present during all queries except the moments when it is the query vertex. If a vertex is queried $x$ times, its presence can be seen as $x + 1$ intervals, which we insert into the segment tree.

Then traverse the whole segment tree. When entering a node, save a backup of the Floyd array, then add all vertices inserted on this interval. When leaving, restore from the backup.

The time complexity of this approach is $O(qn^2\log q)$.

There is also an online approach with better time complexity.

For a query on vertex $x$, run a shortest path from $x$, build the shortest path tree, and along the way record which subtree of $x$ each vertex belongs to.

Then we can always find a non-tree edge whose two endpoints lie in different subtrees of the root, such that this non-tree edge $+$ the paths from its two endpoints to the root form the minimum cycle.

Proof:

Clearly the minimum cycle contains at least one non-tree edge whose two endpoints lie in different subtrees of the root.

Let this edge be $(u,v)$. The path from $x$ to $u$ in the shortest path tree is the shortest among all paths from $x$ to $u$, and the same holds for the path from $x$ to $v$. So the cycle $x\to u\to v\to x$ is certainly no longer than the minimum cycle.

So we can enumerate all non-tree edges and update the answer.

Each query costs one single-source shortest path run, which is $O(n^2)$.

The total time complexity is $O(qn^2)$.
