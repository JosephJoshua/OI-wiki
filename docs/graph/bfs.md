author: Ir1d, greyqz, yjl9903, Anguei, Marcythm, ChungZH, Xeonacid, ylxmf2005

BFS stands for [Breadth First Search](https://en.wikipedia.org/wiki/Breadth-first_search).

It is one of the most basic and most important search algorithms on graphs.

"Breadth first" means that we always try to visit nodes on the same level first.
Only after the whole level has been visited do we move on to the next level.

As a result, the path BFS finds is the **shortest** valid path from the start. In other words, it contains the fewest edges.

When BFS finishes, every node has been reached along a shortest path from the start.

You can think of the algorithm as fire spreading over the graph: at first only the start is on fire, and at each moment every burning node spreads the fire to all its neighbors.

## Implementation

The C++ and Python code below stores the graph as a linked forward star (an array-based adjacency list); see the [graph storage](./save.md) page for how it works.

=== "Pseudocode"
    ```text
    bfs(s) {
      q = new queue()
      q.push(s), visited[s] = true
      while (!q.empty()) {
        u = q.pop()
        for each edge(u, v) {
          if (!visited[v]) {
            q.push(v)
            visited[v] = true
          }
        }
      }
    }
    ```

=== "C++"
    ```cpp
    void bfs(int u) {
      while (!Q.empty()) Q.pop();
      Q.push(u);
      vis[u] = 1;
      d[u] = 0;
      p[u] = -1;
      while (!Q.empty()) {
        u = Q.front();
        Q.pop();
        for (int i = head[u]; i; i = e[i].nxt) {
          if (!vis[e[i].to]) {
            Q.push(e[i].to);
            vis[e[i].to] = 1;
            d[e[i].to] = d[u] + 1;
            p[e[i].to] = u;
          }
        }
      }
    }
    
    void restore(int x) {
      vector<int> res;
      for (int v = x; v != -1; v = p[v]) {
        res.push_back(v);
      }
      std::reverse(res.begin(), res.end());
      for (int i = 0; i < res.size(); ++i) printf("%d", res[i]);
      puts("");
    }
    ```

=== "Python"
    ```python
    from queue import Queue
    
    
    def bfs(u):
        Q = Queue()
        Q.put(u)
        vis[u] = True
        d[u] = 0
        p[u] = -1
        while Q.qsize() != 0:
            u = Q.get()
            i = head[u]
            while i:
                if vis[e[i].to] == False:
                    Q.put(e[i].to)
                    vis[e[i].to] = True
                    d[e[i].to] = d[u] + 1
                    p[e[i].to] = u
                i = e[i].nxt
    
    
    def restore(x):
        res = []
        v = x
        while v != -1:
            res.append(v)
            v = p[v]
        res.reverse()
        for i in range(0, len(res)):
            print(res[i])
    ```

Concretely, we use a queue Q to hold the nodes waiting to be processed, and a Boolean array `vis[]` to mark whether a node has been visited.

At the start, we set `vis` to 0 for all nodes, meaning none has been visited. Then we push the start s into Q and set `vis[s]` to 1.

After that, each step takes the front node u out of Q, marks every unvisited neighbor v of u as visited, and pushes v into Q.

We repeat until Q is empty, which means BFS is finished.

During BFS we can also record extra information. For example, in the code above, the array d stores the shortest distance from the start to each node (the fewest edges needed), and the array p stores which node we came from to reach the current node.

With d, we can easily get the distance from the start to any node.

With p, we can easily rebuild the shortest path from the start to any node. The `restore` function above uses this array to print, in order, the nodes on the shortest path from the start to node x.

Time complexity: $O(n + m)$

Space complexity: $O(n)$ (the `vis` array and the queue)

## Open and closed lists

When implementing BFS, we are essentially keeping the nodes not yet visited in a container called open, and the nodes already visited in a container called closed.

## BFS on trees and graphs

### BFS order

Similar to the DFS order, the BFS order is the sequence of node indices in the order BFS visits them.

### BFS on general graphs

If the graph is disconnected, BFS only reaches the vertices reachable from the start.

The BFS order is usually not unique either.

Similarly, we can define the BFS tree: during BFS, record for each node which node it was reached from. This gives a tree structure, called the BFS tree.

## Applications

-   Find shortest paths from a start vertex to all other vertices in an unweighted graph.
-   Find all connected components in $O(n+m)$ time. (Just start a BFS from every node not yet visited; each BFS clearly covers exactly one connected component.)
-   If each move in a game is seen as an edge (a transition) in a state graph, BFS can find the minimum number of moves needed to get from one state to another.
-   Find the shortest cycle in a directed unweighted graph. (Start a BFS from every vertex. When we are about to reach a vertex visited earlier in that BFS, we know we have found a cycle. The shortest cycle of the graph is the minimum of the shortest cycles found by each BFS.)
-   Find the edges that lie on some shortest path between $(a, b)$. (Run BFS from a and from b to get two d arrays. Then for each edge $(u, v)$, if $d_a[u]+1+d_b[v]=d_a[b]$, the edge lies on a shortest path.)
-   Find the vertices that lie on some shortest path between $(a, b)$. (Run BFS from a and from b to get two d arrays. Then for each vertex v, if $d_a[v]+d_b[v]=d_a[b]$, the vertex lies on some shortest path.)
-   Find a shortest path of even length. (Build a new graph by splitting each vertex into two new vertices; each edge $(u, v)$ of the original graph becomes $((u, 0), (v, 1))$ and $((u, 1), (v, 0))$. Run BFS on the new graph; the shortest path between $(s, 0)$ and $(t, 0)$ is the answer.)
-   Find shortest paths in a graph with 0/1 edge weights; see 0-1 BFS (deque BFS) below.

## 0-1 BFS (deque BFS)

If you are not familiar with the double-ended queue `deque`, see [the section on deque](../lang/csl/sequence-container.md#deque).

Deque BFS is also called 0-1 BFS.

### When it applies

Shortest path problems where each edge either has a weight or has none (since BFS works on graphs whose weights are all 1, the weights are usually 0 or 1), or problems that can be turned into such edge weights.

For example, in a maze problem where you can walk 5 steps for 1 coin or 1 step for free, 0-1 BFS can solve it.

### Implementation

Usually, nodes reached through a weight-0 edge are pushed to the front of the queue, and nodes reached through a weighted edge are pushed to the back. This keeps the weights along the queue from front to back non-decreasing, just as in ordinary BFS.

Here is the pseudocode:

```cpp
while (queue is not empty) {
  int u = front of queue;
  pop front;
  for (each neighbor of u) {
    update data
    if (...)
      push to front;
    else
      push to back;
  }
}
```

### Example problem

### [Codeforces 173B](http://codeforces.com/problemset/problem/173/B)

Given an $n \times m$ grid, a laser beam enters from the top-left corner heading right. Each time it meets a '#', you may make the light shoot out in all four directions, or do nothing. Find the minimum number of '#' cells that must shoot in all four directions so that the light exits row $n$ heading right.

The intended solution is not 0-1 BFS, but 0-1 BFS works and needs less thinking. Many strong contestants solved it this way during the contest.

The approach is simple: continuing in one direction costs nothing (0), while shooting in all four directions costs 1. Then just run 0-1 BFS.

#### Code

```cpp
--8<-- "docs/graph/code/bfs/bfs_1.cpp"
```

## Priority queue BFS

A priority queue is essentially a binary heap. The STL provides [`std::priority_queue`](../lang/csl/container-adapter.md), which makes priority queues easy to use.

In priority-queue-based BFS, each step takes the node with the smallest cost from the front of the queue and searches further from it. This greedy idea is easy to prove correct: a search that expands from this node can never update nodes that already had a higher cost. In other words, we never go back and update those other higher-cost nodes.

Of course, each node may be pushed into the queue several times, each time with a different cost. Once a node is taken out of the priority queue for the first time, we never need to search from it again and can simply skip it. So in priority queue BFS, each node is processed only once.

Compared with BFS using an ordinary queue, the time complexity gains a factor of $\log n$, since we have to maintain the priority queue. However, ordinary BFS on such graphs may push and pop each node many times, reaching $O(n^2)$ rather than $O(n)$. So priority queue BFS is usually still fast.

Hey, doesn't this sound a lot like heap-optimized [Dijkstra](./shortest-path.md#dijkstras-algorithm)? In fact, heap-optimized Dijkstra is exactly priority queue BFS.

## Exercises

-   [NOIP2017 Cheese](https://uoj.ac/problem/332)

0-1 BFS:

-   [CF1063B. Labyrinth](https://codeforces.com/problemset/problem/1063/B)
-   [CF173B. Chamber of Secrets](https://codeforces.com/problemset/problem/173/B)
-   [BalticOI 2011 Day1 Switch the Lamp On](https://loj.ac/p/2632)

## References

<https://cp-algorithms.com/graph/breadth-first-search.html>
