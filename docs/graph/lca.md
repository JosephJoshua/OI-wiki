author: ouuan, Backl1ght, billchenchina, CCXXXI, ChickenHu, ChungZH, cjsoft, countercurrent-time, diauweb, Early0v0, Enter-tainer, EtaoinWu, H-J-Granger, H-Shen, Henry-ZHR, HeRaNO, hsfzLZH1, huaruoji, iamtwz, imp2002, Ir1d, kenlig, Konano, Lyccrius, Marcythm, Menci, NachtgeistW, PeterlitsZo, psz2007, shuzhouliu, SkqLiao, sshwy, SukkaW, therehello, TrisolarisHD, ttzztztz, vincent-163, WAAutoMaton, Hunter19019

## Definition

LCA is short for Lowest Common Ancestor. The lowest common ancestor of two nodes is, among the common ancestors of the two nodes, the one farthest from the root.
For convenience, we write the lowest common ancestor of a node set $S=\{v_1,v_2,\ldots,v_n\}$ as $\text{LCA}(v_1,v_2,\ldots,v_n)$ or $\text{LCA}(S)$.

## Properties

> Part of the **Properties** section is translated from [wcipeg](http://wcipeg.com/wiki/Lowest_common_ancestor), with modifications.

1.  $\text{LCA}(\{u\})=u$;
2.  $u$ is an ancestor of $v$ if and only if $\text{LCA}(u,v)=u$;
3.  If $u$ is not an ancestor of $v$ and $v$ is not an ancestor of $u$, then $u$ and $v$ are in two different subtrees of $\text{LCA}(u,v)$;
4.  In a preorder traversal, $\text{LCA}(S)$ appears before all elements of $S$; in a postorder traversal, $\text{LCA}(S)$ appears after all elements of $S$;
5.  The LCA of the union of two node sets is the LCA of the two sets' LCAs, that is, $\text{LCA}(A\cup B)=\text{LCA}(\text{LCA}(A), \text{LCA}(B))$;
6.  The LCA of two nodes always lies on the shortest path between them in the tree;
7.  $d(u,v)=h(u)+h(v)-2h(\text{LCA}(u,v))$, where $d$ is the distance between two nodes in the tree, and $h$ is the distance from a node to the root.

## Methods

### Naive algorithm

#### Process

Each time, take the deeper of the two nodes and move it up. Clearly, in a tree the two nodes will eventually meet, and the meeting point is the LCA we want.
Alternatively, first move the deeper node up until both nodes have the same depth, then move both up together; they will also eventually meet.

#### Properties

The naive algorithm needs a DFS over the whole tree for preprocessing, which takes $O(n)$ time, and each query takes $\Theta(n)$ time. If the tree is random, the time complexity depends on the expected height of such random trees.

### Binary lifting

#### Process

Binary lifting is the most classic way to find the LCA, and it improves on the naive algorithm. By precomputing the array $\text{fa}_{x,i}$, the cursor can move quickly, which greatly reduces the number of jumps. $\text{fa}_{x,i}$ is the $2^i$-th ancestor of node $x$. The array $\text{fa}_{x,i}$ can be precomputed with a DFS.

Now let's see how to speed up these jumps:
In the first phase of moving the cursors, we need to bring $u$ and $v$ to the same depth. We can compute the depth difference of $u$ and $v$; call it $y$. By splitting $y$ into its binary representation, we turn $y$ single jumps into "the number of `1` bits in the binary representation of $y$" jumps.
In the second phase, we try each $i$ from the largest down to $0$ (inclusive). If $\text{fa}_{u,i}\not=\text{fa}_{v,i}$, then set $u\gets\text{fa}_{u,i},v\gets\text{fa}_{v,i}$. In the end, the LCA is $\text{fa}_{u,0}$.

#### Properties

Binary lifting takes $O(n \log n)$ time to preprocess, and each query takes $O(\log n)$ time.
Also, in binary lifting you can swap the two dimensions of the `fa` array so that the smaller dimension comes first. This reduces cache misses and makes the program faster.

??? note "Example problem"
    [HDU 2586 How far away?](https://acm.hdu.edu.cn/showproblem.php?pid=2586) Shortest path queries on a tree.

You can first find the LCA and then use property $7$. You can also compute the result directly while finding the LCA.

??? note "Reference code"
    ```cpp
    --8<-- "docs/graph/code/lca/lca_1.cpp"
    ```

### Tarjan's algorithm

#### Process

Tarjan's algorithm is an **offline algorithm**. It uses a [disjoint set union (DSU)](../ds/dsu.md) to record the ancestor of a node. It works as follows:

1.  First, read the input edges (an adjacency list) and the query edges (stored in another adjacency list). Query edges are really virtual edges added for convenience: each time a query edge is read, add both the edge and its reverse to the `queryEdge` array.
2.  Then do one DFS traversal, using the `visited` array to record whether a node has been visited and `parent` to record the parent of the current node.
3.  This uses the idea of **backtracking**. Each time we reach a node, we consider the root of that node to be itself. After the DFS of the subtree rooted at this node is completely finished, we set the root of this node to its parent.
4.  When backtracking from a node, if the other endpoint of a `queryEdge` query edge starting at this node has also already been visited, update the LCA result of that query edge directly.
5.  Finally, output the results.

#### Properties

Tarjan's algorithm needs to initialize the DSU, so preprocessing takes $O(n)$ time.

The naive Tarjan algorithm handles all $m$ queries in $O(m \alpha(m+n, n) + n)$ time, but its constant is larger than that of binary lifting. An $O(m + n)$ implementation exists.

???+ warning "Note"
    There is no such fact as "the DSU used in the naive Tarjan LCA algorithm is special, so a single call to `find()` takes amortized $O(1)$ time".
    
    The naive Tarjan implementation below runs in $O(m \alpha(m+n, n) + n)$. If you need strictly linear time, see [the 1983 paper by Gabow and Tarjan](https://dl.acm.org/doi/pdf/10.1145/800061.808753), which gives an $O(m + n)$ method.

#### Implementation

??? note "Reference code"
    ```cpp
    --8<-- "docs/graph/code/lca/lca_tarjan.cpp"
    ```

### Reducing to RMQ with the Euler tour

#### Definition

Do a DFS on a tree, and each time you arrive at a node, whether it is the first visit or a return from backtracking, record its index. This gives a sequence of length $2n-1$, called the Euler tour (Euler sequence) of the tree.

Below, the position where node $u$ first appears in the Euler tour is written $pos(u)$ (also called the Euler index of node $u$), and the Euler tour itself is written $E[1..2n-1]$.

#### Process

With the Euler tour, the LCA problem can be reduced to an RMQ problem in linear time, namely $pos(LCA(u, v))=\min\{pos(k)|k\in E[pos(u)..pos(v)]\}$.

This equation is easy to understand: walking from $u$ to $v$ must pass through $LCA(u,v)$, but never through an ancestor of $LCA(u,v)$. So among the nodes passed on the way from $u$ to $v$, the one with the smallest Euler index is $LCA(u, v)$.

Computing the Euler tour with a DFS takes $O(n)$ time, and the Euler tour has length $O(n)$, so the LCA problem can be reduced to an RMQ problem of the same size in $O(n)$ time.

#### Implementation

???+ note "Reference code"
    ```cpp
    int dfn[N << 1], pos[N], tot, st[30][(N << 1) + 2],
        rev[30][(N << 1) + 2];  // rev is the node with the minimum depth
    
    void dfs(int cur, int dep) {
      dfn[++tot] = cur;
      depth[tot] = dep;
      pos[cur] = tot;
      for (int i = head[t]; i; i = side[i].next) {
        int v = side[i].to;
        if (!pos[v]) {
          dfs(v, dep + 1);
          dfn[++tot] = cur, depth[tot] = dep;
        }
      }
    }
    
    void init() {
      for (int i = 2; i <= tot + 1; ++i)
        lg[i] = lg[i >> 1] + 1;  // precompute lg instead of calling log2, to reduce the constant
      for (int i = 1; i <= tot; i++) st[0][i] = depth[i], rev[0][i] = dfn[i];
      for (int i = 1; i <= lg[tot]; i++)
        for (int j = 1; j + (1 << i) - 1 <= tot; j++)
          if (st[i - 1][j] < st[i - 1][j + (1 << i - 1)])
            st[i][j] = st[i - 1][j], rev[i][j] = rev[i - 1][j];
          else
            st[i][j] = st[i - 1][j + (1 << i - 1)],
            rev[i][j] = rev[i - 1][j + (1 << i - 1)];
    }
    
    int query(int l, int r) {
      int k = lg[r - l + 1];
      return st[k][l] < st[k][r + 1 - (1 << k)] ? rev[k][l]
                                                : rev[k][r + 1 - (1 << k)];
    }
    ```

To query the LCA of a pair $(u, v)$, just find the node corresponding to the minimum on the interval $[\min\{pos[u], pos[v]\}, \max\{pos[u], pos[v]\}]$.

If a sparse table is used for RMQ, this algorithm does not support online modification; preprocessing takes $O(n\log n)$ time, and each LCA query takes $O(1)$ time.

### Reducing to RMQ with the DFS order

The Euler tour has length $2n-1$, so its time and memory constants are a bit large. In fact, we can find the LCA directly with the DFS timestamps $\operatorname{dfn}$.

Consider the LCA of a pair $(u,v)$, and let $d=\operatorname{LCA}(u,v)$. If $u=v$, then $d=u$, which needs special handling. Otherwise, assume without loss of generality that $\operatorname{dfn}(u) < \operatorname{dfn}(v)$; then $v$ is not an ancestor of $u$. Unlike in the Euler tour, $d$ does not appear in the interval $(\operatorname{dfn}(u), \operatorname{dfn}(v)]$ of the DFS order. But the interval always contains the child of $d$ that lies on the path from $d$ to $v$. This holds whether or not $u$ is an ancestor of $v$. So we just need to find the node with the smallest depth in the interval $[\operatorname{dfn}(u) + 1, \operatorname{dfn}(v)]$ (it may not be unique), and its parent must be the LCA. The interval starts at $\operatorname{dfn}(u) + 1$ because if $u$ is an ancestor of $v$ and the interval included $u$, the node with the smallest depth would be $u$ itself, whose parent is not the LCA.

So finding the LCA becomes an RMQ problem again.

If you don't want to store extra depth and parent information, you can store $\operatorname{fa}(u)$ directly at position $\operatorname{dfn}(u)$ of the DFS order, and compare values in this sequence by their timestamps. Then the element with the smallest timestamp in the interval $[\operatorname{dfn}(u) + 1, \operatorname{dfn}(v)]$ of this sequence is $\operatorname{LCA}(u,v)$. This is because the nodes in the interval $[\operatorname{dfn}(u) + 1, \operatorname{dfn}(v)]$ are all proper descendants of $d$, so the DFS timestamps of their parents are never smaller than $\operatorname{dfn}(d)$; and the minimum $\operatorname{dfn}(d)$ is reached exactly at the child of $d$ in the interval, which must exist by the discussion above.

Reducing LCA to RMQ with the DFS order takes $O(n)$ time, and the total complexity depends on the RMQ method used. Here is a reference implementation using a sparse table with $O(n\log n)$ preprocessing and $O(1)$ queries:

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/graph/code/lca/lca-dfs.cpp:lca"
    ```

### Heavy-light decomposition

The LCA is the node pointed to by the shallower of the two cursors once both have jumped onto the same heavy path.

Heavy-light decomposition takes $O(n)$ time to preprocess, and each query takes $O(\log n)$ time with a small constant.

### Link Cut Tree

In a [Link Cut Tree](../ds/lct.md), if two consecutive [access](../ds/lct.md#access) operations are done on nodes `u` and `v`, then the node returned by the second [access](../ds/lct.md#access) is the LCA of `u` and `v`.

Without link, cut or similar operations, each query with a Link Cut Tree takes $O(\log n)$ time.

### Standard RMQ

As discussed above, the Euler tour turns the LCA problem into an RMQ problem, so the bottleneck is RMQ. If RMQ can be solved in $O(n) \sim O(1)$, then LCA can also be solved in $O(n) \sim O(1)$.

Notice that adjacent values in the Euler tour differ by exactly 1 or -1, so we can use the $O(n) \sim O(1)$ [±1 RMQ](../topic/rmq.md#加减-1rmq).

The time complexity is $O(n) \sim O(1)$ and the space complexity is $O(n)$. It supports online queries, but the constant is large.

#### Example problem [Luogu P3379 [Template] Lowest Common Ancestor (LCA)](https://www.luogu.com.cn/problem/P3379)

??? note "Reference code"
    ```cpp
    --8<-- "docs/graph/code/lca/lca_2.cpp"
    ```

## Exercises

-   [Ancestor and Descendant Queries](https://loj.ac/problem/10135)
-   [Truck Transport](https://loj.ac/problem/2610)
-   [Distance Between Nodes](https://loj.ac/problem/10130)

## References

-   [An obscure trick: finding the LCA with the DFS order, by Alex\_Wei - Luogu (Chinese)](https://www.luogu.com.cn/article/pu52m9ue)
