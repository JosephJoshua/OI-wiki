## Centroid decomposition

Centroid decomposition is good for handling large-scale problems about paths in a tree.

??? note "Example problem 1 [Luogu P3806 [Template] Centroid Decomposition 1](https://www.luogu.com.cn/problem/P3806)"
    Given a tree with $n$ nodes and weighted edges, answer $m$ queries. Each query gives $k$ and asks whether there is a pair of nodes at distance $k$ in the tree.
    
    $n\le 10000,m\le 100,k\le 10000000$

First pick any node as the root $\mathit{rt}$. All paths lying entirely in its subtree fall into two kinds: paths that pass through the current root, and paths that do not. Paths through the current root again fall into two kinds: paths with the root as one endpoint, and paths where neither endpoint is the root. A path of the second kind can be formed by joining two paths of the first kind. So for the chosen root $rt$, we first count the contribution of paths in its subtree that pass through it, and then recurse into its subtrees to handle the paths that do not pass through it.

In this problem, for paths through the root $\mathit{rt}$, we first enumerate all its children $\mathit{ch}$, and for each one compute the distances from all nodes in the subtree of $\mathit{ch}$ to $\mathit{rt}$. Let $\mathit{dist}_i$ be the distance from node $i$ to the current root $rt$, and let $\mathit{tf}_{d}$ say whether some node $v$ in the previously processed subtrees has $\mathit{dist}_v=d$. If a query's $k$ has $tf_{k-\mathit{dist}_i}=true$, then a path of length $k$ exists. After checking whether paths through the subtree of $\mathit{ch}$ can be an answer, we add these new distances to the $\mathit{tf}$ array.

Note that when clearing the $\mathit{tf}$ array you must not just use `memset`. Instead, put every $\mathit{tf}$ position you used into a queue and clear those. Only this keeps the time complexity correct.

In centroid decomposition, all the recursive calls on one level together process each node once. If there are $h$ levels of recursion, the total time complexity is $O(hn)$.

If each time we choose the [centroid](./tree-centroid.md) of the subtree as the root, the number of recursion levels is as small as possible, and the time complexity is $O(n\log n)$. This is why the technique is usually called **centroid decomposition** in contests outside China.

Be sure to recompute subtree sizes after choosing a new root. Otherwise a seemingly tiny change can break the time complexity or make correctness hard to guarantee.

??? note "Reference code"
    ```cpp
    --8<-- "docs/graph/code/tree-divide/tree-divide_1.cpp"
    ```

??? note "Example problem 2 [Luogu P4178 Tree](https://www.luogu.com.cn/problem/P4178)"
    Given a tree with $n$ nodes and weighted edges, and a value $k$, count the pairs of nodes whose distance in the tree is at most $k$.
    
    $n\le 40000,k\le 20000,w_i\le 1000$

Since here we count pairs of nodes at distance in $[0,k]$, we use a segment tree to support updates and queries.

??? note "Reference code"
    ```cpp
    --8<-- "docs/graph/code/tree-divide/tree-divide_2.cpp"
    ```

??? note "Example problem 3 [Luogu P2664 Tree Game](https://www.luogu.com.cn/problem/P2664)"
    Each node of a tree has a color. Define $s(i,j)$ as the number of colors on the path from $\mathit{i}$ to $\mathit{j}$, and $\mathit{sum_{i}}=\sum_{j=1}^n s(i,j)$. Find $sum_i$ for all $1\leq i\leq n$. ($1 \le n, c_i \le 10^5$)

This problem really tests your understanding and use of centroid decomposition. It makes a good harder example and practice problem for the technique.

First we need to see a transformation. The problem defines $\mathit{sum_i}$ as the total number of colors over the paths from $i$ to all nodes. But with this definition it is hard to count the answer in centroid decomposition, because it is hard to merge information from two subtrees of the current root. So we change what $\mathit{sum_i}$ means. For each color $j$, let $\mathit{cnt_j}$ be the number of paths that have $i$ as one endpoint and contain color $j$. Then $\mathit{sum_i}$ is just $\sum \mathit{cnt_j}$. This step simply changes what we look at: we consider each color's contribution to $\mathit{sum_i}$. And $\mathit{cnt_j}$ is easy to compute: whenever we meet a new color, do $\mathit{cnt_{col_u}}+=\mathit{size_u}$, where $\mathit{size_u}$ is the size of u's subtree. This means every node in that subtree contributes to $u$'s answer through this color.

During centroid decomposition, we only need to count these separately:

1.  The contribution to the root of paths in the subtree that have the current root as an endpoint
2.  The contribution to each node in the subtree of paths whose LCA is the current root

Part 1 is fairly easy. In centroid decomposition there are at most $\log{n}$ levels of recursion, and on each level we can traverse all subtrees, so we can count it directly from the definition of $\mathit{sum_i}$ while traversing.

For part 2, let $d$ be a child of the current root $u$, and let $v$ be any node in the subtree of $d$. Then the answer of $v$ splits into two parts:

1.  Colors that appear on the path $(u, v)$. Let their number be $\mathit{num}$, and let $\mathit{siz1}$ be the total size of all subtrees of $u$ other than $d$. Then these colors contribute $\mathit{num}\times \mathit{siz1}$ to $v$'s answer.
2.  Colors $j$ that do not appear on the path $(u, v)$. Their contribution comes from the $\mathit{cnt_j}$ of all subtrees of $u$ other than $d$, giving $\sum_{j \notin (u, v)} \mathit{cnt_j}$.

That is the whole counting idea; see the reference code for implementation details.

??? note "Reference code"
    ```cpp
    --8<-- "docs/graph/code/tree-divide/tree-divide_3.cpp"
    ```

## Edge decomposition

Similar to centroid decomposition above, we pick an edge that splits the tree into two parts as evenly as possible (so the $\mathit{size}$s of the two subtrees joined by the edge are as close as possible). Then we recurse into the two sides and collect information.

But this does not work. Consider a star graph:

![Star graph](./images/tree-divide1.svg)

We see that when a node has many children with similar $\mathit{size}$, the time complexity of edge decomposition is unacceptable.

If the graph is a binary tree, we avoid the problem that edge decomposition has on the star graph above. So we convert a tree with many children per node into a binary tree.

Clearly, we only need to build it the way we build a segment tree. Like this:

![Building the tree](./images/tree-divide2.svg)

Give the newly created nodes whatever information the problem needs. For example, when counting path lengths, give original edges weight $1$ and new edges weight $0$.

For the complexity: at most $O(n)$ nodes are added, so the total complexity is $O(n\log n)$.

Edge decomposition can solve almost every centroid decomposition problem (with a different constant factor, but not enough to fail), so we do not give an example problem.

## Centroid tree

The centroid tree is a rebuilt tree that changes the shape of the original tree so that its number of levels is reliably $\log n$.

It is often used for problems with updates that do not depend on the original shape of the tree.

### Analysis

We rebuild the original tree using the way centroid decomposition picks a centroid each time.

Make each centroid we find a child of the centroid found on the level above. This gives a tree with $\log n$ levels.

Since the tree has $\log n$ levels, many brute-force methods that would not normally be fast enough have the right complexity on the centroid tree.

### Implementation

A small trick: the total size of the current level is the total size $\mathit{tot}$ of the previous level of recursion minus the size of the heavy child of the node on the previous level. This way, finding the centroid needs only one DFS.

???+ note "Reference code"
    ```cpp
    #include <algorithm>
    #include <iostream>
    #include <vector>
    using namespace std;
    
    using IT = vector<int>::iterator;
    
    struct Edge {
      int to, nxt, val;
    
      Edge() {}
    
      Edge(int to, int nxt, int val) : to(to), nxt(nxt), val(val) {}
    } e[300010];
    
    int head[150010], cnt;
    
    void addedge(int u, int v, int val) {
      e[++cnt] = Edge(v, head[u], val);
      head[u] = cnt;
    }
    
    int siz[150010], son[150010];
    bool vis[150010];
    
    int tot, lasttot;
    int maxp, root;
    
    void getG(int now, int fa) {
      siz[now] = 1;
      son[now] = 0;
      for (int i = head[now]; i; i = e[i].nxt) {
        int vs = e[i].to;
        if (vs == fa || vis[vs]) continue;
        getG(vs, now);
        siz[now] += siz[vs];
        son[now] = max(son[now], siz[vs]);
      }
      son[now] = max(son[now], tot - siz[now]);
      if (son[now] < maxp) {
        maxp = son[now];
        root = now;
      }
    }
    
    struct Node {
      int fa;
      vector<int> anc;
      vector<int> child;
    } nd[150010];
    
    int build(int now, int ntot) {
      tot = ntot;
      maxp = 0x7f7f7f7f;
      getG(now, 0);
      int g = root;
      vis[g] = true;
      for (int i = head[g]; i; i = e[i].nxt) {
        int vs = e[i].to;
        if (vis[vs]) continue;
        int tmp = build(vs, ntot - son[vs]);
        nd[tmp].fa = now;
        nd[now].child.push_back(tmp);
      }
      return g;
    }
    
    int virtroot;
    
    int main() {
      int n;
      cin >> n;
      for (int i = 1; i < n; i++) {
        int u, v, val;
        cin >> u >> v >> val;
        addedge(u, v, val);
        addedge(v, u, val);
      }
      virtroot = build(1, n);
    }
    ```
