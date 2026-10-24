author: xiezheyuan

Problems that combine a segment tree with offline queries also appear in OI. This technique is also called segment tree divide and conquer (offline divide and conquer over time).

Suppose you need to maintain some pieces of information, each of which exists only during some time interval, and you must answer, offline, the union (combination) of the information present at a given moment. Then you can consider using segment tree divide and conquer.

In practice, segment tree divide and conquer is often used for:

1.  Simulating deletion with a data structure that does not support deletion but does support undo. For example, a plain DSU cannot efficiently support deleting edges.
2.  Computing separately for data with different attributes. For example, finding the answer for the data of all colors except one particular color.

Don't worry if this is unclear for now; we will explain both uses in the example problems.

## Process

First, build a segment tree over time. Each node keeps a `vector` that stores the information covering that time range.

Inserting a piece of information into the segment tree is similar to a range update on an ordinary segment tree.

Next, consider how to get the combined information for each moment. Do divide and conquer starting from the root, keeping the current combined information. Whenever we reach a node, merge in all the information stored at that node. When backtracking, undo the contribution of that part. The combined information when we reach a leaf is the answer for that moment.

If changing the information takes $O(T(n))$ time, we can keep a stack of the changes and undo them in $O(T(n))$ time. Undo does not preserve amortized complexity.

The total time complexity of the whole divide and conquer process is $O(n\log n(T(n) + M(n)))$, where $O(M(n))$ is the time to merge information. The space complexity is $O(n\log n)$.

??? note "Implementation"
    ```cpp
    #define ls (i << 1)
    #define rs (i << 1 | 1)
    #define mid ((l + r) >> 1)
    
    vector<Object> tree[N << 2];  // segment tree
    
    void update(int ql, int qr, Object obj, int i, int l, int r) {  // insert
      if (ql <= l && r <= qr) {
        tree[i].push_back(obj);
        return;
      }
      if (ql <= mid) update(ql, qr, obj, ls, l, mid);
      if (qr > mid) update(ql, qr, obj, rs, mid + 1, r);
    }
    
    stack<Object> sta;  // stack used for undo
    Object now;         // current combined information
    Object ans[N];      // answers
    
    void solve(int i, int l, int r) {
      auto lvl = sta.size();  // remember how far to undo back to
      for (Object x : tree[i]) sta.push(now), now = Merge(now, x);  // merge info
      if (l == r)
        ans[i] = now;  // record the answer
      else
        solve(ls, l, mid), solve(rs, mid + 1, r);  // divide and conquer
      while (sta.size() != lvl) {                  // undo info
        now = sta.top();
        sta.pop();
      }
    }
    ```

## Example problems

???+ note "[Luogu P5787 Bipartite Graph / [Template] Segment Tree Divide and Conquer](https://www.luogu.com.cn/problem/P5787)"
    You need to maintain an undirected graph with $n$ vertices and $m$ edges. The $i$-th edge is $(x_i,y_i)$; it exists during the time $[l_i,r_i)$ and is absent at all other times.
    
    For each moment, output `Yes` if the graph is bipartite at that time, and `No` otherwise.
    
    ??? note "Solution idea"
        Use a DSU with parity (a "species" DSU) to maintain whether the graph is bipartite, and then apply segment tree divide and conquer.
        
        Note that a DSU that supports undo cannot use path compression; it can only use union by rank.
    
    ??? note "Reference code"
        ```cpp
        --8<-- "docs/topic/code/segment-tree-offline/segment-tree-offline_1.cpp"
        ```

???+ note "Color restriction"
    You are given an undirected graph with $n$ vertices and $m$ edges. There are $k$ colors numbered $0\sim k-1$, and each edge has one color.
    
    For each color, determine: if all edges of this color are deleted, is the resulting graph connected? Is it a tree?
    
    Output the number of colors whose deletion leaves a connected graph, and the number of colors whose deletion leaves a tree.
    
    ??? note "Solution idea"
        For each color, create a moment in time during which the edges of that color are absent and all other edges are present. Then just maintain it with a DSU.
    
    ??? note "Reference code"
        ```cpp
        --8<-- "docs/topic/code/segment-tree-offline/segment-tree-offline_2.cpp"
        ```

???+ note "[Luogu P4219 \[BJOI2014\] Great Fusion](https://www.luogu.com.cn/problem/P4219)"
    You need to maintain a forest with $n$ vertices, initially all isolated.
    
    There are $q$ operations of the following types:
    
    -   `A x y`: add the edge $(x,y)$.
    -   `Q x y`: output the number of paths that pass through the edge $(x,y)$.
    
    Offline processing is allowed.
    
    ??? note "Solution idea"
        Since offline processing is allowed, segment tree divide and conquer comes to mind.
        
        Next, consider how to support the Q operation. If the edge $(x,y)$ did not exist, the answer would be the size of $x$'s connected component times the size of $y$'s connected component. This can be maintained with a DSU.
        
        So you can split Q into three moments $k-1,k,k+1$, where $k-1$ is an end time of this edge and $k+1$ is a start time of this edge. This way the edge is absent at time $k$, which is exactly what we need to answer the query.
    
    ??? note "Reference code"
        ```cpp
        --8<-- "docs/topic/code/segment-tree-offline/segment-tree-offline_3.cpp"
        ```

???+ note "[Luogu P2056 \[ZJOI2007\] Hide and Seek](https://www.luogu.com.cn/problem/P2056)"
    You are given a tree with $n$ vertices. Each vertex is either black or white. Initially every vertex is black. There are $q$ operations of the following types:
    
    -   `C x`: flip the color of vertex $x$.
    -   `G`: ask for the largest distance between two black vertices in the tree. In particular, if there is no black vertex, output $-1$.
    
    Offline processing is allowed.
    
    ??? note "Solution idea"
        First, consider how to maintain the diameter of a set of vertices in a tree. We have the following corollary:
        
        > Take a set $S$ and a single-vertex set $\{P\}$. If the diameter of $S$ is $(U,V)$, then the diameter of the vertex set $S\cup\{P\}$ can only be $(U,V)$, $(U,P)$ or $(V,P)$.
        
        Now consider the original problem. We maintain the set of black vertices, and for each vertex we keep the time intervals during which it is in the black set (to do this, just use a bucket to record the last time each vertex entered the black set).
        
        This naturally leads to an offline approach: insert all time intervals into a segment tree. Then do divide and conquer on the segment tree. Each segment tree node records the vertices newly added to the set during its time range. For each new vertex, use the corollary above to find the two endpoints of the diameter of the new vertex set.
        
        Undo is trivial: just keep a stack that records the changes to the diameter endpoints.
    
    ??? note "Reference code"
        ```cpp
        --8<-- "docs/topic/code/segment-tree-offline/segment-tree-offline_4.cpp"
        ```

## Exercises

-   [CF601E A Museum Robbery](https://codeforces.com/problemset/problem/601/E): segment tree divide and conquer + knapsack DP.
-   [CF19E Fairy](https://codeforces.com/problemset/problem/19/E): segment tree divide and conquer + DSU with parity.
-   [Luogu P5227 \[AHOI2013\] Connected Graph](https://www.luogu.com.cn/problem/P5227): segment tree divide and conquer + DSU.
-   [Luogu P4319 Changing Roads](https://www.luogu.com.cn/problem/P4319): segment tree divide and conquer + Link Cut Tree to maintain the minimum spanning tree.
-   [Luogu P3733 \[HAOI2017\] Eight Vertical and Eight Horizontal](https://www.luogu.com.cn/problem/P3733): segment tree divide and conquer + linear basis.

**Parts of this page are based on the blog post [Deleting from a data structure](https://cp-algorithms.com/data_structures/deleting_in_log_n.html), licensed under CC-BY-SA 4.0.**
