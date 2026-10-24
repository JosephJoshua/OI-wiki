author: Ir1d, greyqz, yjl9903, partychicken, ChungZH, qq1010903229, Marcythm, Acfboy, shenshuaijie, Craneplayz

## Introduction

DFS stands for [Depth First Search](https://en.wikipedia.org/wiki/Depth-first_search). It is an algorithm for traversing or searching trees and graphs. "Depth first" means that we always try to go to a deeper node next.

It is often taught alongside BFS. But apart from both being able to traverse the connected components of a graph, the two have completely different uses, and there are few situations where you can use either one.

The term DFS is often used for any search written as a recursive function, but the two are actually not the same. For that kind of search, see [DFS (search)](../search/dfs.md).

## Process

The most notable feature of DFS is that it **calls itself recursively**. Also, like BFS, DFS marks the vertices it has visited and skips marked vertices while traversing the graph, so that **each vertex is visited only once**. Any function that follows these two rules is a DFS in the broad sense.

Concretely, DFS has roughly the following structure:

    DFS(v) // v can be a vertex of the graph, or something abstract, such as a DP state.
      mark v as visited
      for u in neighbors of v
        if u is not marked as visited then
          DFS(u)
        end
      end
    end

The code above contains only the main structure every DFS needs. A real DFS adds more code on top of it to do other work using the properties of DFS.

## Properties

The algorithm usually runs in $O(n+m)$ time and $O(n)$ space, where $n$ is the number of vertices and $m$ the number of edges. Note that the space includes the stack, which takes $O(n)$ space. This time complexity is only achieved when each edge can be traversed in $O(1)$ on average, for example when the graph is stored as a forward star or an adjacency list; with an adjacency matrix this complexity may not be achieved.

> Note: most programming contests today (including NOIP, most provincial team selections, and all contests run by CCF) support **unlimited stack space**: the stack is not limited separately, but total memory is still limited by the problem statement. However, most operating systems put an extra limit on stack space, so when debugging locally you need some way to lift the stack limit.
>
> -   On Windows, the usual way is to add `-Wl,--stack=1000000000` to the **compile options**, which sets the stack limit to 1000000000 bytes.
> -   On Linux, the usual way is to run `ulimit -s unlimited` **in the terminal** before running the program, which makes the stack unlimited. You only need to run it once per terminal; it applies to every later run of the program.

## Implementation

### Stack-based implementation

DFS can be implemented with a [stack](../ds/stack.md) as the temporary container for nodes during traversal; this closely mirrors BFS implemented with a [queue](../ds/queue.md).

=== "C++"
    ```cpp
    vector<vector<int>> adj;  // adjacency list
    vector<bool> vis;         // whether each node has been visited
    
    void dfs(int s) {
      stack<int> st;
      st.push(s);
      vis[s] = true;
    
      while (!st.empty()) {
        int u = st.top();
        st.pop();
    
        for (int v : adj[u]) {
          if (!vis[v]) {
            vis[v] = true;  // make sure the stack has no duplicate elements
            st.push(v);
          }
        }
      }
    }
    ```

=== "Python"
    ```python
    # adj : List[List[int]] adjacency list
    # vis : List[bool] whether each node has been visited
    
    
    def dfs(s: int) -> None:
        stack = [s]  # simulate a stack with a list; push the start
        vis[s] = True  # the start is visited
    
        while stack:  # keep going while the stack is not empty
            u = (
                stack.pop()
            )  # take and remove the last element (the top of the stack); think of it as walking to u
    
            for v in adj[u]:  # for each element v adjacent to u
                if not vis[v]:  # if v has not been visited before
                    vis[v] = True  # make sure the stack has no duplicate elements
                    stack.append(v)  # push v onto the stack
    ```

### Recursive implementation

Evaluating recursive function calls follows the same order as pushing and popping elements of a stack, which is why the memory used by function calls is called the call stack. So DFS can be implemented with recursion.

Using an [adjacency list](./save.md#adjacency-list) to store the graph:

=== "C++"
    ```cpp
    vector<vector<int>> adj;  // adjacency list
    vector<bool> vis;         // whether each node has been visited
    
    void dfs(const int u) {
      vis[u] = true;
      for (int v : adj[u])
        if (!vis[v]) dfs(v)
    }
    ```

=== "Python"
    ```python
    # adj : List[List[int]] adjacency list
    # vis : List[bool] whether each node has been visited
    
    
    def dfs(u: int) -> None:
        vis[u] = True
        for v in adj[u]:
            if not vis[v]:
                dfs(v)
    ```

Using a [linked forward star](./save.md#linked-forward-star) as an example:

=== "C++"
    ```cpp
    void dfs(int u) {
      vis[u] = 1;
      for (int i = head[u]; i; i = e[i].x) {
        if (!vis[e[i].t]) {
          dfs(v);
        }
      }
    }
    ```

=== "Java"
    ```Java
    public void dfs(int u) {
        vis[u] = true;
        for (int i = head[u]; i != 0; i = e[i].x) {
            if (!vis[e[i].t]) {
                dfs(v);
            }
        }
    }
    ```

=== "Python"
    ```python
    def dfs(u):
        vis[u] = True
        i = head[u]
        while i:
            if vis[e[i].t] == False:
                dfs(v)
            i = e[i].x
    ```

### DFS order

The DFS order is the sequence of node indices in the order the DFS visits them.

Notice that every subtree corresponds to a contiguous segment (an interval) of the DFS order.

### Bracket sequence

When the DFS enters a node, record an opening bracket `(`; when it leaves a node, record a closing bracket `)`.

Each node appears twice. The depths of two adjacent nodes differ by 1.

### DFS on general graphs

For a disconnected graph, DFS only reaches the connected component containing the start.

For a connected graph, the DFS order is usually not unique.

Note: the DFS order of a tree is not unique either.

During DFS, by recording for each node which node it was reached from, we can build a tree structure called the DFS tree. The DFS tree is a spanning tree of the original graph.

The [DFS tree](./scc.md#dfs-spanning-tree) has many properties; for example, it can be used to find [strongly connected components](./scc.md).
