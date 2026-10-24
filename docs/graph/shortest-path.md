author: du33169, lingkerio, Taoran-01

## Definitions

(Do you remember these definitions? Before reading the following, make sure you know the basics in [Graph theory concepts](./concept.md).)

-   Path
-   Shortest path
-   Shortest paths in directed graphs and in undirected graphs
-   Single-source shortest paths and all-pairs shortest paths

## Notation

For convenience, here is the notation used below.

-   $n$ is the number of vertices of the graph, and $m$ is the number of edges;
-   $s$ is the source of the shortest paths;
-   $D(u)$ is the **actual** shortest path length from $s$ to $u$;
-   $dis(u)$ is the **estimated** shortest path length from $s$ to $u$. At all times $dis(u) \geq D(u)$. In particular, when a shortest path algorithm finishes, $dis(u)=D(u)$ should hold.
-   $w(u,v)$ is the weight of the edge $(u,v)$.

## Properties

In a graph with positive edge weights, a shortest path between any two nodes never visits the same node twice.

In a graph with positive edge weights, a shortest path between any two nodes never uses the same edge twice.

In a graph with positive edge weights, any shortest path between two nodes has at most $n$ nodes and at most $n-1$ edges.

## Floyd's algorithm

It is used to find the shortest paths between every pair of nodes.

Its complexity is fairly high, but its constant factor is small and it is easy to implement (just three `for` loops).

It works on any graph, directed or undirected, with positive or negative edge weights, as long as shortest paths exist. (There must be no negative cycle.)

### Implementation

Define an array `f[k][x][y]` as the length of the shortest path from node $x$ to node $y$ that may only pass through nodes $1$ to $k$ (that is, a path in the subgraph $V'={1, 2, \ldots, k}$; note that $x$ and $y$ themselves need not be in this subgraph).

Clearly, `f[n][x][y]` is the shortest path length from node $x$ to node $y$ (because $V'={1, 2, \ldots, n}$ is $V$ itself, so the shortest path it describes is exactly the one we want).

Next, let us see how to compute the values of `f`.

`f[0][x][y]`: the weight of the edge between $x$ and $y$, or $0$, or $+\infty$ (when should `f[0][x][y]` be $+\infty$? If there is an edge directly joining $x$ and $y$, it is the edge weight; if $x = y$, it is zero, because the distance from a node to itself is zero; if there is no edge directly joining $x$ and $y$, it is $+\infty$).

`f[k][x][y] = min(f[k-1][x][y], f[k-1][x][k]+f[k-1][k][y])` (`f[k-1][x][y]` is the shortest path that does not pass through $k$, and `f[k-1][x][k]+f[k-1][k][y]` is the shortest path that passes through $k$).

Both lines above are clearly correct, so this approach uses $O(N^3)$ space. We grow the problem size step by step ($k$ from $1$ to $n$) and find the shortest path between every two nodes for the current problem size.

=== "C++"
    ```cpp
    for (k = 1; k <= n; k++) {
      for (x = 1; x <= n; x++) {
        for (y = 1; y <= n; y++) {
          f[k][x][y] = min(f[k - 1][x][y], f[k - 1][x][k] + f[k - 1][k][y]);
        }
      }
    }
    ```

=== "Python"
    ```python
    for k in range(1, n + 1):
        for x in range(1, n + 1):
            for y in range(1, n + 1):
                f[k][x][y] = min(f[k - 1][x][y], f[k - 1][x][k] + f[k - 1][k][y])
    ```

The first dimension does not affect the result, so it can be dropped, and we can simply write `f[x][y] = min(f[x][y], f[x][k]+f[k][y])`.

???+ note "Proof that the first dimension does not affect the result"
    For a given `k`, updating `f[k][x][y]` only uses elements in row `k` and column `k` of `f[k-1]`. Now notice that for a given `k`, updating `f[k][k][y]` or `f[k][x][k]` never changes the value, because by the formula `f[k][k][y] = min(f[k-1][k][y], f[k-1][k][k]+f[k-1][k][y])`, `f[k-1][k][k]` is 0, so the value is always `f[k-1][k][y]`. The proof for `f[k][x][k]` is similar.
    
    So if we drop the first dimension, for a given `k`, none of the elements used in an update are changed during this iteration. Hence dropping the first dimension does not affect the result.

=== "C++"
    ```cpp
    for (k = 1; k <= n; k++) {
      for (x = 1; x <= n; x++) {
        for (y = 1; y <= n; y++) {
          f[x][y] = min(f[x][y], f[x][k] + f[k][y]);
        }
      }
    }
    ```

=== "Python"
    ```python
    for k in range(1, n + 1):
        for x in range(1, n + 1):
            for y in range(1, n + 1):
                f[x][y] = min(f[x][y], f[x][k] + f[k][y])
    ```

In summary, the time complexity is $O(N^3)$ and the space complexity is $O(N^2)$.

### Applications

???+ question "Given an undirected graph with positive weights, find a cycle with the minimum total weight."
    First, such a cycle must be a simple cycle.
    
    Think about how this cycle is formed.
    
    Consider the node $u$ with the largest label on the cycle.
    
    `f[u-1][x][y]` together with $(u,x)$ and $(u,y)$ forms the cycle.
    
    Enumerate $u$ during Floyd's algorithm and take the minimum of this sum.
    
    The time complexity is $O(n^3)$.
    
    For more, see [Minimum cycle](./min-cycle.md).

???+ question "Given whether there is an edge between every two nodes of a directed graph, decide for every two nodes whether one can reach the other."
    This problem asks for the **transitive closure of the graph**.
    
    We just follow Floyd's algorithm and add nodes one by one, checking as we go.
    
    The only difference is that edge weights become $1/0$, and taking $\min$ becomes the **OR** operation.
    
    With a further bitset optimization, the complexity can reach $O(\frac{n^3}{w})$.
    
    ```cpp
    // std::bitset<SIZE> f[SIZE];
    for (k = 1; k <= n; k++)
      for (i = 1; i <= n; i++)
        if (f[i][k]) f[i] = f[i] | f[k];
    ```

## Bellman–Ford algorithm

The Bellman–Ford algorithm is a shortest path algorithm based on the relax operation. It can find shortest paths in graphs with negative weights, and it can detect when shortest paths do not exist.

In the Chinese OI community, the "SPFA" you may have heard of is one implementation of the Bellman–Ford algorithm.

### Process

First, let us introduce the relax operation used by the Bellman–Ford algorithm (Dijkstra's algorithm also uses it).

For an edge $(u,v)$, the relax operation is: $dis(v) = \min(dis(v), dis(u) + w(u, v))$.

The meaning is clear: we try to update the shortest path length of $v$ using the path $S \to u \to v$ (where $S \to u$ is the shortest path), and update it if this path is better.

What the Bellman–Ford algorithm does is keep trying to relax every edge of the graph. In each round, we try to relax every edge once. When a round has no successful relaxation, the algorithm stops.

Each round takes $O(m)$ time. So how many rounds can there be at most?

When shortest paths exist, each round of relaxation increases the number of edges of the found shortest paths by at least $1$, and a shortest path has at most $n-1$ edges, so the algorithm runs at most $n-1$ rounds of relaxation. So the total time complexity is $O(nm)$.

But there is another case: if a negative cycle is reachable from $S$, relaxation goes on forever. As argued above, for a graph where shortest paths exist, at most $n-1$ rounds of relaxation are performed. So if some edge can still be relaxed in round $n$, a negative cycle is reachable from $S$.

???+ warning "A common mistake in detecting negative cycles"
    Note that if running the Bellman–Ford algorithm from source $S$ reports no negative cycle, this only means no negative cycle is reachable from $S$. It does not mean the graph has no negative cycle.
    
    So if you need to check whether the whole graph has a negative cycle, the most rigorous way is to add a super source, connect it to every node with an edge of weight 0, and run the Bellman–Ford algorithm from the super source.

### Implementation

??? note "Reference implementation"
    === "C++"
        ```cpp
        struct Edge {
          int u, v, w;
        };
        
        vector<Edge> edge;
        
        int dis[MAXN], u, v, w;
        constexpr int INF = 0x3f3f3f3f;
        
        bool bellmanford(int n, int s) {
          memset(dis, 0x3f, (n + 1) * sizeof(int));
          dis[s] = 0;
          bool flag = false;  // whether any relaxation happened in this round
          for (int i = 1; i <= n; i++) {
            flag = false;
            for (int j = 0; j < edge.size(); j++) {
              u = edge[j].u, v = edge[j].v, w = edge[j].w;
              if (dis[u] == INF) continue;
              // Infinity plus or minus a constant is still infinity,
              // so edges out of a node with distance INF can never be relaxed
              if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                flag = true;
              }
            }
            // Stop when no edge can be relaxed
            if (!flag) {
              break;
            }
          }
          // If relaxation is still possible in round n, s can reach a negative cycle
          return flag;
        }
        ```
    
    === "Python"
        ```python
        class Edge:
            def __init__(self, u=0, v=0, w=0):
                self.u = u
                self.v = v
                self.w = w
        
        
        INF = 0x3F3F3F3F
        edge = []
        
        
        def bellmanford(n, s):
            dis = [INF] * (n + 1)
            dis[s] = 0
            for i in range(1, n + 1):
                flag = False
                for e in edge:
                    u, v, w = e.u, e.v, e.w
                    if dis[u] == INF:
                        continue
                    # Infinity plus or minus a constant is still infinity,
                    # so edges out of a node with distance INF can never be relaxed
                    if dis[v] > dis[u] + w:
                        dis[v] = dis[u] + w
                        flag = True
                # Stop when no edge can be relaxed
                if not flag:
                    break
            # If relaxation is still possible in round n, s can reach a negative cycle
            return flag
        ```

### Queue optimization: SPFA

That is, the Shortest Path Faster Algorithm.

Often we do not need that many useless relaxations.

Clearly, only the edges out of nodes that were relaxed in the previous step can lead to the next relaxation.

So we use a queue to keep track of "which nodes may lead to relaxations", and then we only visit the necessary edges.

SPFA can also check whether $s$ can reach a negative cycle. Just record how many edges the shortest path uses; once it uses at least $n$ edges, $s$ can reach a negative cycle.

??? note "Implementation"
    === "C++"
        ```cpp
        struct edge {
          int v, w;
        };
        
        vector<edge> e[MAXN];
        int dis[MAXN], cnt[MAXN], vis[MAXN];
        queue<int> q;
        
        bool spfa(int n, int s) {
          memset(dis, 0x3f, (n + 1) * sizeof(int));
          dis[s] = 0, vis[s] = 1;
          q.push(s);
          while (!q.empty()) {
            int u = q.front();
            q.pop(), vis[u] = 0;
            for (auto ed : e[u]) {
              int v = ed.v, w = ed.w;
              if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;  // number of edges on the shortest path
                if (cnt[v] >= n) return false;
                // Without a negative cycle, a shortest path has at most n - 1 edges,
                // so using more than n edges means a negative cycle was used
                if (!vis[v]) q.push(v), vis[v] = 1;
              }
            }
          }
          return true;
        }
        ```
    
    === "Python"
        ```python
        from collections import deque
        
        
        class Edge:
            def __init__(self, v=0, w=0):
                self.v = v
                self.w = w
        
        
        e = [[Edge() for i in range(MAXN)] for j in range(MAXN)]
        INF = 0x3F3F3F3F
        
        
        def spfa(n, s):
            dis = [INF] * (n + 1)
            cnt = [0] * (n + 1)
            vis = [False] * (n + 1)
            q = deque()
        
            dis[s] = 0
            vis[s] = True
            q.append(s)
            while q:
                u = q.popleft()
                vis[u] = False
                for ed in e[u]:
                    v, w = ed.v, ed.w
                    if dis[v] > dis[u] + w:
                        dis[v] = dis[u] + w
                        cnt[v] = cnt[u] + 1  # number of edges on the shortest path
                        if cnt[v] >= n:
                            return False
                        # Without a negative cycle, a shortest path has at most n - 1 edges,
                        # so using more than n edges means a negative cycle was used
                        if not vis[v]:
                            q.append(v)
                            vis[v] = True
        ```

SPFA runs fast in most cases, but its worst-case time complexity is $O(nm)$, and it is not hard to build data that forces this. So be careful using it in contests. (When there are no negative edges, it is best to use Dijkstra's algorithm. When there are negative edges and the graph has no special property, if SPFA is part of the intended solution, the problem should not use limits that the Bellman–Ford algorithm cannot pass.)

???+ note "Other optimizations of Bellman–Ford"
    Besides the queue optimization (SPFA), Bellman–Ford has other optimizations. They work well on some graphs, but on certain special graphs their worst-case complexity can become exponential.
    
    -   Heap optimization: replace the queue with a heap. Unlike Dijkstra's algorithm, a node may enter the heap many times. On graphs with negative edges, it can be forced into exponential complexity.
    -   Stack optimization: replace the queue with a stack (turning the BFS-like process into a DFS). It may find negative cycles faster, but its worst-case time complexity is still exponential.
    -   LLL optimization: replace the queue with a deque. Each time a node is added, compare its distance with the average distance of the nodes in the queue; if it is larger, add it to the back, otherwise to the front.
    -   SLF optimization: replace the queue with a deque. Each time a node is added, compare its distance with that of the front node; if it is larger, add it to the back, otherwise to the front.
    -   D´Esopo–Pape algorithm: replace the queue with a deque. If a node has never been in the queue before, add it to the back; otherwise add it to the front.
    
    For more optimizations and ways to hack them, see [fstqwq's answer on Zhihu](https://www.zhihu.com/question/292283275/answer/484871888).

## Dijkstra's algorithm

Dijkstra's algorithm (/ˈdikstrɑ/ or /ˈdɛikstrɑ/) was discovered by the Dutch computer scientist E. W. Dijkstra in 1956 and published in 1959. It finds single-source shortest paths in **graphs with non-negative weights**.

### Process

Split the nodes into two sets: the nodes whose shortest path length is already determined (call this set $S$) and the nodes whose shortest path length is not yet determined (call this set $T$). At the start, all nodes are in $T$.

Initialize $dis(s)=0$ and set $dis$ of every other node to $+\infty$.

Then repeat these steps:

1.  Pick the node in $T$ with the smallest shortest path length and move it to $S$.
2.  Relax all outgoing edges of the node just added to $S$.

Stop when $T$ is empty.

### Time complexity

The naive implementation, after each step 2, scans all of $T$ by brute force to find the node with the smallest shortest path length. Step 2 takes $O(m)$ time in total, step 1 takes $O(n^2)$ in total, and the whole process takes $O(n^2 + m) = O(n^2)$.

We can speed this up with a heap: each time an edge $(u,v)$ is successfully relaxed, insert $v$ into the heap (if $v$ is already in the heap, do a Decrease-key instead), and step 1 just takes the top of the heap. In total there are $O(m)$ Decrease-key operations and $O(n)$ pops, and different heaps give different complexities; see the [Heap](../ds/heap.md) page. The best complexity a heap can achieve is $O(n\log n+m)$, for example with a Fibonacci heap.

In particular, you can use a priority queue. It cannot do Decrease-key, but you can instead insert the node again each time it is relaxed, and when popping a node, check whether it has already been processed and skip it if so. This takes $O(m\log n)$ time and is simpler to implement.

The heap here can also be implemented with a segment tree, which takes $O(m\log n)$ time. With some special non-recursive segment tree implementations, this has a smaller constant factor than a heap. Segment trees also support more operations, and in some special graph problems only a segment tree will do.

In sparse graphs, $m = O(n)$, and the heap-optimized Dijkstra algorithm is much more efficient. In dense graphs, $m = O(n^2)$, and the naive implementation is better.

### Proof of correctness

Below we use induction to prove that Dijkstra's algorithm is correct, assuming **all edge weights are non-negative**[^1].

In short, what we need to prove is that whenever step 1 takes out a node $u$, its shortest path has already been determined, that is, $D(u) = dis(u)$.

At the start $S = \varnothing$, and the claim holds.

Next, we argue by contradiction.

Let $u$ be the first node that does not satisfy $D(u) = dis(u)$ when it is added to $S$. The node $s$ always satisfies $D(u)=dis(u)=0$ and is always the first node added to $S$, so before $u$ is added, $S \neq \varnothing$. If there is no path from $s$ to $u$, then $D(u) = dis(u) = +\infty$, which contradicts the assumption.

So there must be a path $s \to x \to y \to u$, where $y$ is the first node on the path $s \to u$ that belongs to $T$, and $x$ is the node right before $y$ (clearly $x \in S$). Note that we may have $s = x$ or $y = u$, that is, $s \to x$ or $y \to u$ may be empty paths.

All nodes added before $u$ satisfy $D(u) = dis(u)$, so when $x$ was added to $S$, $D(x) = dis(x)$, and at that time the edge $(x,y)$ was relaxed. So when $u$ is added to $S$, we must have $D(y)=dis(y)$.

Now we show $D(u) = dis(u)$. On the path $s \to x \to y \to u$, since all edge weights are non-negative, $D(y) \leq D(u)$. So $dis(y) = D(y) \leq D(u)\leq dis(u)$. But when $u$ is taken out of $T$ in step 1, $y$ has not been taken out of $T$ yet, so at that time $dis(u)\leq dis(y)$. This gives $dis(y) = D(y) = D(u) = dis(u)$, which contradicts the assumption $D(u)\neq dis(u)$. So the assumption is false.

So we have shown that every node taken out in step 1 already has its shortest path determined. This proves the claim.

Note that the key inequality $D(y) \leq D(u)$ in the proof relies on all edge weights being non-negative. When the graph has negative edges, this inequality no longer holds, the correctness of Dijkstra's algorithm is no longer guaranteed, and it may give wrong results.

### Implementation

Here we give both the $O(n^2)$ brute-force implementation and the $O(m \log m)$ priority queue implementation.

???+ note "Naive implementation"
    === "C++"
        ```cpp
        struct edge {
          int v, w;
        };
        
        vector<edge> e[MAXN];
        int dis[MAXN], vis[MAXN];
        
        void dijkstra(int n, int s) {
          memset(dis, 0x3f, (n + 1) * sizeof(int));
          dis[s] = 0;
          for (int i = 1; i <= n; i++) {
            int u = 0, mind = 0x3f3f3f3f;
            for (int j = 1; j <= n; j++)
              if (!vis[j] && dis[j] < mind) u = j, mind = dis[j];
            vis[u] = true;
            for (auto ed : e[u]) {
              int v = ed.v, w = ed.w;
              if (dis[v] > dis[u] + w) dis[v] = dis[u] + w;
            }
          }
        }
        ```
    
    === "Python"
        ```python
        class Edge:
            def __init__(self, v=0, w=0):
                self.v = v
                self.w = w
        
        
        e = [[Edge() for i in range(MAXN)] for j in range(MAXN)]
        INF = 0x3F3F3F3F
        
        
        def dijkstra(n, s):
            dis = [INF] * (n + 1)
            vis = [0] * (n + 1)
        
            dis[s] = 0
            for i in range(1, n + 1):
                u = 0
                mind = INF
                for j in range(1, n + 1):
                    if not vis[j] and dis[j] < mind:
                        u = j
                        mind = dis[j]
                vis[u] = True
                for ed in e[u]:
                    v, w = ed.v, ed.w
                    if dis[v] > dis[u] + w:
                        dis[v] = dis[u] + w
        ```

???+ note "Priority queue implementation"
    === "C++"
        ```cpp
        struct edge {
          int v, w;
        };
        
        struct node {
          int dis, u;
        
          bool operator>(const node& a) const { return dis > a.dis; }
        };
        
        vector<edge> e[MAXN];
        int dis[MAXN], vis[MAXN];
        priority_queue<node, vector<node>, greater<node>> q;
        
        void dijkstra(int n, int s) {
          memset(dis, 0x3f, (n + 1) * sizeof(int));
          memset(vis, 0, (n + 1) * sizeof(int));
          dis[s] = 0;
          q.push({0, s});
          while (!q.empty()) {
            int u = q.top().u;
            q.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            for (auto ed : e[u]) {
              int v = ed.v, w = ed.w;
              if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                q.push({dis[v], v});
              }
            }
          }
        }
        ```
    
    === "Python"
        ```python
        def dijkstra(e, s):
            """
            Input:
            e: adjacency list
            s: start vertex
            Returns:
            dis: shortest path length from s to each vertex
            """
            dis = defaultdict(lambda: float("inf"))
            dis[s] = 0
            q = [(0, s)]
            vis = set()
            while q:
                _, u = heapq.heappop(q)
                if u in vis:
                    continue
                vis.add(u)
                for v, w in e[u]:
                    if dis[v] > dis[u] + w:
                        dis[v] = dis[u] + w
                        heapq.heappush(q, (dis[v], v))
            return dis
        ```

## Johnson's all-pairs shortest path algorithm

Like Floyd's algorithm, Johnson's algorithm finds shortest paths between every pair of nodes in a graph without negative cycles. It was proposed by Donald B. Johnson in 1977.

All-pairs shortest paths can be found by enumerating the start node and running the Bellman–Ford algorithm $n$ times, which takes $O(n^2m)$ time. It can also be solved directly with Floyd's algorithm in $O(n^3)$ time.

Notice that heap-optimized Dijkstra finds single-source shortest paths faster than Bellman–Ford. If we enumerate the start node and run Dijkstra's algorithm $n$ times, we can solve the problem in $O(nm\log m)$ time (depending on the implementation of Dijkstra's algorithm). This is better than running Bellman–Ford $n$ times, and on sparse graphs it is also better than Floyd's algorithm.

But Dijkstra's algorithm cannot correctly find shortest paths with negative edges, so we need to preprocess the edges of the original graph to make sure all edge weights are non-negative.

An easy idea is to add the same positive number $x$ to every edge weight so that all weights become non-negative. If the shortest path from start to end in the new graph uses $k$ edges, subtract $kx$ to get the real shortest path length.

But this approach is wrong. Consider the graph below:

![](./images/shortest-path1.svg)

The shortest path $1 \to 2$ is $1 \to 5 \to 3 \to 2$, with length $−2$.

But what if we add $5$ to every edge weight?

![](./images/shortest-path2.svg)

In the new graph, the shortest path $1 \to 2$ is $1 \to 4 \to 2$, which is no longer the real shortest path.

Johnson's algorithm reweights the edges in a different way.

We add a new virtual node (here we give it label $0$). From this node, add an edge of weight $0$ to every other node.

Then use the Bellman–Ford algorithm to find the shortest paths from node $0$ to all other nodes, and call them $h_i$.

If there is an edge from $u$ to $v$ with weight $w$, we reset its weight to $w+h_u-h_v$.

Then run Dijkstra's algorithm $n$ times, once from each node, to get the shortest paths between every pair of nodes.

The initial Bellman–Ford run is not the time bottleneck. If Dijkstra's algorithm is implemented with `priority_queue`, the time complexity of the whole algorithm is $O(nm\log m)$.

### Proof of correctness

Why is this way of reweighting correct?

Before answering, let us look at a concept from physics: potential energy.

Potential energies such as gravitational potential energy and electric potential energy share one property: the change in potential energy depends only on the positions of the start and end points, not on the path taken between them.

Potential energy has another property: its absolute value usually depends on where we set the zero point, but no matter where the zero point is, the difference in potential energy between two points is fixed.

Now back to the main topic.

In the reweighted graph, the length of a path $s \to p_1 \to p_2 \to \dots \to p_k \to t$ from $s$ to $t$ is:

$(w(s,p_1)+h_s-h_{p_1})+(w(p_1,p_2)+h_{p_1}-h_{p_2})+ \dots +(w(p_k,t)+h_{p_k}-h_t)$

Simplifying gives:

$w(s,p_1)+w(p_1,p_2)+ \dots +w(p_k,t)+h_s-h_t$

No matter which path we take from $s$ to $t$, the value of $h_s-h_t$ stays the same, which matches the property of potential energy!

For convenience, from now on we call $h_i$ the potential of node $i$.

The length of an $s \to t$ path in the new graph above has two parts: the first is the sum of the original edge weights of the path, and the second is the potential difference between the two endpoints. Since the potential difference is fixed, shortest $s \to t$ paths in the original graph correspond to shortest $s \to t$ paths in the new graph.

That is half of the proof: we have shown that after reweighting, the shortest paths in the graph are still the original shortest paths. Next we need to show that every edge weight in the new graph is non-negative, because Dijkstra's algorithm is guaranteed to give correct results on graphs with non-negative weights.

By the triangle inequality, the two endpoints of any edge $(u,v)$ satisfy $h_v \leq h_u + w(u,v)$. The new weight of this edge is $w'(u,v)=w(u,v)+h_u-h_v \geq 0$. So all edge weights in the new graph are non-negative.

This proves that Johnson's algorithm is correct.

## Comparison of the methods

| Shortest path algorithm | Floyd      | Bellman–Ford | Dijkstra     | Johnson       |
| ------- | ---------- | ------------ | ------------ | ------------- |
| Type of shortest path | All pairs | Single source | Single source | All pairs |
| Works on | Any graph | Any graph | Graphs with non-negative weights | Any graph |
| Can detect negative cycles? | Yes | Yes | No | Yes |
| Time complexity | $O(N^3)$   | $O(NM)$      | $O(M\log M)$ | $O(NM\log M)$ |

Note: the complexities of Dijkstra's algorithm in the table assume a `priority_queue` implementation.

## Recovering the path

Keep a `pre` array. When updating a distance, record which node the later node was reached from. At the end, output the path recursively.

For example, Floyd's algorithm records `pre[i][j] = k;`, while Bellman–Ford and Dijkstra usually record `pre[v] = u`.

## Some special cases

-   Shortest paths in a graph whose edge weights are only $0$ and $1$: [0-1 BFS](./bfs.md#0-1-bfs-deque-bfs);
-   Shortest path problems that allow changing path costs or similar operations at most $k$ times: [shortest paths on a layered graph](./node.md#shortest-paths-on-a-layered-graph).

## References and notes

[^1]: *Introduction to Algorithms* (3rd edition, Chinese translation), China Machine Press, 2013, pp. 384-385.
