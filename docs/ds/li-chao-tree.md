## Introduction

???+ note "[Luogu P4097 \[HEOI2013\] Segment](https://www.luogu.com.cn/problem/P4097)"
    Support the following two operations in the Cartesian plane (forced online):
    
    1.  Add a segment to the plane. The $i$-th inserted segment is labeled $i$, and its two endpoints are $(x_0,y_0)$ and $(x_1,y_1)$.
    2.  Given a number $k$, among the segments that intersect the line $x = k$, report the label of the one whose intersection point has the largest y-coordinate (if several segments tie for the largest y-coordinate, output the smallest label). In particular, if no segment intersects the given line, output $0$.
    
    Constraints: total number of operations $1 \leq n \leq 10^5$, $1 \leq k, x_0, x_1 \leq 39989$, $1 \leq y_0, y_1 \leq 10^9$.

An ordinary segment tree cannot maintain this kind of information well. This is where the **Li Chao tree** comes in.

## How it works

We can turn the task into supporting the following operations:

-   Add a linear function whose domain is $[l,r]$;
-   Given $k$, among all linear functions whose domain contains $k$, find the one with the largest value at $x=k$. If several functions have the same value, choose the one with the smallest label.

???+ warning "Note"
    When a segment is perpendicular to the $x$ axis, we would divide by zero. Suppose the segment's endpoints are $(x,y_0)$ and $(x,y_1)$ with $y_0<y_1$. Then insert the linear function $f(x)=0\cdot x+y_1$ with domain $[x,x]$.

Since we have range updates, we follow the usual segment tree approach for range problems and give each node a lazy tag. The lazy tag of each node $i$ is a segment, written $l_i$, meaning that $l_i$ should be used to update the whole interval represented by that node.

Now we need to insert a segment $f$. Consider a segment tree interval fully covered by the new segment $f$. If the interval has no tag, simply tag it with this segment.

If the interval already has a tag, since tags are hard to merge, we have to push a tag down. But the child nodes also have their own tags, which may also conflict, so we need to push tags down recursively.

![](images/li-chao-tree-1.png)

As shown in the figure, we can split the current interval into two sub-intervals based on whether the new segment $f$ is larger than the old tag $g$. **One of these sub-intervals must be fully contained in the left half or the right half**. In other words, of the two segments, one can only be the answer in the left half, or only in the right half. We use this segment to recursively update the matching subtree, and use the other segment as the lazy tag for the whole interval. This keeps the cost of recursive push-down bounded. A segment is pushed down only when it can be the answer only in the left half or only in the right half, so we don't need to worry about missing any segment.

Specifically, let the midpoint of the current interval be $m$. We compare the value of the new segment $f$ at the midpoint with the value of the old best segment $g$ at the midpoint.

If the new segment $f$ is better, swap $f$ and $g$. Now consider the case where $f$ is not better than $g$ at the midpoint:

1.  If $f$ is better at the left endpoint, then $f$ and $g$ must intersect in the left half, and $f$ can only beat $g$ in the left half. Recurse into the left child to push it down;
2.  If $f$ is better at the right endpoint, then $f$ and $g$ must intersect in the right half, and $f$ can only beat $g$ in the right half. Recurse into the right child to push it down;
3.  If $g$ is better at both endpoints, then $f$ can never be the answer, and there is no need to push it down.

Besides these cases, $f$ and $g$ may intersect exactly at the midpoint. In the implementation, this can be treated as the case where $f$ is not better than $g$ at the midpoint, and the result is a recursive push-down toward the endpoint where $f$ is better.

Finally, make $g$ the lazy tag of the current interval.

Pushing down a tag:

???+ note "Implementation"
    ```cpp
    constexpr double eps = 1e-9;
    
    int cmp(double x, double y) {  // Floating-point numbers are used, so there are precision errors
      if (x - y > eps) return 1;
      if (y - x > eps) return -1;
      return 0;
    }
    
    //...
    
    void upd(int root, int cl, int cr, int u) {  // Update an interval fully covered by the segment
      int &v = s[root], mid = (cl + cr) >> 1;
      int bmid = cmp(calc(u, mid), calc(v, mid));
      if (bmid == 1 || (!bmid && u < v))  // In this problem, remember to compare segment labels
        swap(u, v);
      int bl = cmp(calc(u, cl), calc(v, cl)), br = cmp(calc(u, cr), calc(v, cr));
      if (bl == 1 || (!bl && u < v)) upd(root << 1, cl, mid, u);
      if (br == 1 || (!br && u < v)) upd(root << 1 | 1, mid + 1, cr, u);
      // At most one of the two if conditions above holds, which guarantees the Li Chao tree's time complexity
    }
    ```

Splitting a segment:

???+ note "Implementation"
    ```cpp
    void update(int root, int cl, int cr, int l, int r,
                int u) {  // Find intervals fully covered by the inserted segment
      if (l <= cl && cr <= r) {
        upd(root, cl, cr, u);  // Fully covers the current interval; update its tag
        return;
      }
      int mid = (cl + cr) >> 1;
      if (l <= mid) update(root << 1, cl, mid, l, r, u);  // Recursively split the interval
      if (mid < r) update(root << 1 | 1, mid + 1, cr, l, r, u);
    }
    ```

Note that the lazy tag is not the same as the segment with the largest value at the interval's midpoint.

![](images/li-chao-tree-2.png)

As shown in the figure, after the yellow segment is added, only the tags of the red nodes are updated, and the tags of the green nodes have not changed yet. But at the midpoints of the second, third and fourth green intervals, the yellow segment clearly has the largest value.

When querying, we can use the idea of permanent tags (tags that are never pushed down): compare the tagged segments of all segment tree intervals containing $x$ (at most $O(\log n)$ of them) to get the final answer.

Query:

???+ note "Implementation"
    ```cpp
    pdi query(int root, int l, int r, int d) {  // Query
      if (r < d || d < l) return {0, 0};
      int mid = (l + r) >> 1;
      double res = calc(s[root], d);
      if (l == r) return {res, s[root]};
      return pmax({res, s[root]}, pmax(query(root << 1, l, mid, d),
                                       query(root << 1 | 1, mid + 1, r, d)));
    }
    ```

From the description above, a query clearly takes $O(\log n)$ time. For insertion, we split the segment into $O(\log n)$ intervals, and for each interval we spend $O(\log n)$ time on recursive push-down. So insertion takes $O(\log^2 n)$ time.

??? note "Reference code for [\[HEOI2013\] Segment](https://www.luogu.com.cn/problem/P4097)"
    ```cpp
    --8<-- "docs/ds/code/li-chao-tree/li-chao-tree_1.cpp"
    ```

## Merging

Similar to merging ordinary segment trees, we define the following process to merge two Li Chao tree nodes $u,v$, with $u$ as the new root.

1.  If $v$ is empty, stop.

2.  If $u$ is empty, copy $v$ into $u$.

3.  Insert the segment of $v$ into the subtree rooted at $u$.

4.  Recursively merge the left subtrees of $u,v$ with each other, and the right subtrees with each other.

If the total number of nodes involved in merging several Li Chao trees is $n$, this process takes $O(n\log n)$: for the node of any segment in the tree, every time we move it, we either increase its depth by $1$ or remove it from the tree directly. Both cost $O(1)$, and each node's depth is at most $O(\log n)$, which gives the complexity above.

???+ note "Implementation"
    ```cpp
    void upd(int &root, int cl, int cr,
             int u) {  // Merging several Li Chao trees, so nodes are created dynamically.
      static int idx = 0;
      if (!root) {
        s[root = ++idx] = u;
        return;
      }
      int &v = s[root], mid = (cl + cr) >> 1;
      int bmid = cmp(calc(u, mid), calc(v, mid));
      if (bmid == 1 || (!bmid && u < v)) swap(u, v);
      int bl = cmp(calc(u, cl), calc(v, cl)), br = cmp(calc(u, cr), calc(v, cr));
      if (bl == 1 || (!bl && u < v)) upd(ls[root], cl, mid, u);
      if (br == 1 || (!br && u < v)) upd(rs[root], mid + 1, cr, u);
    }
    
    int merge(int &u, int &v, int l, int r) {
      if (!u || !v) {
        return u + v;
      }
      if (l == r) {
        int b = cmp(calc(s[v], l), calc(s[u], l));
        if (b == 1 || (!b && s[v] < s[u])) return v;
        return u;
      }
      upd(u, l, r, s[v]);
      int mid = (l + r) >> 1;
      ls[u] = merge(ls[u], ls[v], l, mid);
      rs[u] = merge(rs[u], rs[v], mid + 1, r);
      return u;
    }
    ```

## Exercises

[JSOI2008 Blue Mary Starts a Company](https://www.luogu.com.cn/problem/P4254)

[CodeChef TSUM2 Sum on Tree](https://www.codechef.com/problems/TSUM2)

[USACO13MAR Hill Walk G](https://www.luogu.com.cn/problem/P3081)

[CF932F Escape Through Leaf](https://codeforces.com/problemset/problem/932/F)
