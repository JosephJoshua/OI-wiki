## Dynamic centroid decomposition

Dynamic centroid decomposition solves path-statistics problems on trees **with updates to vertex/edge weights**.

### Centroid tree

Let's review how centroid decomposition computes things.

For a node $x$, the simple paths in its subtree come in two kinds: those that pass through $x$, made of one or two paths starting at $x$; and those that do not pass through $x$, which are already contained in the subtrees of its children.

To compute the simple paths in a subtree, we choose a divide center $rt$, compute the information of the paths in the subtree that pass through it, and then, for each of its children, take the connected component containing that child after deleting $rt$ as a new subtree and recurse. The chosen centers form a tree structure called the **centroid tree**. Notice that for nodes on the same level of the centroid tree, the total size of the components they represent (the components in which each is the divide center) is $O(n)$. This means the time complexity of centroid decomposition depends on the depth of the centroid tree: if the depth is $h$, the complexity is $O(nh)$.

It can be shown that if we always choose the centroid of the component as the divide center, the centroid tree has the smallest depth, which is $O(\log n)$. Then we can compute the information of all $O(n^2)$ paths in the tree in $O(n\log n)$ time.

Since the shape of the tree does not change during dynamic centroid decomposition, the shape of the centroid tree does not change either.

Reference code for building the centroid tree:

```cpp
void calcsiz(int x, int f) {
  siz[x] = 1;
  maxx[x] = 0;
  for (int j = h[x]; j; j = nxt[j])
    if (p[j] != f && !vis[p[j]]) {
      calcsiz(p[j], x);
      siz[x] += siz[p[j]];
      maxx[x] = max(maxx[x], siz[p[j]]);
    }
  maxx[x] =
      max(maxx[x], sum - siz[x]);  // maxx[x] is the largest subtree size when x is the root
  if (maxx[x] < maxx[rt])
    rt = x;  // do not use <= here, so rt stays the same in the second calcsiz
}

void pre(int x) {
  vis[x] = true;  // vertex x is ignored in the rest of the process
  for (int j = h[x]; j; j = nxt[j])
    if (!vis[p[j]]) {
      sum = siz[p[j]];
      rt = 0;
      maxx[rt] = inf;
      calcsiz(p[j], -1);
      calcsiz(rt, -1);  // run twice; the second run gets subtree sizes with rt as the root
      fa[rt] = x;
      pre(rt);  // record the parent in the centroid tree
    }
}

int main() {
  sum = n;
  rt = 0;
  maxx[rt] = inf;
  calcsiz(1, -1);
  calcsiz(rt, -1);
  pre(rt);
}
```

### Handling updates

For queries and updates, we walk up through the parents in the centroid tree by brute force. Since the depth of the centroid tree is at most $O(\log n)$, the complexity is guaranteed.

In dynamic centroid decomposition, we need information such as the distance from a node to its ancestors in the centroid tree. Since a node has at most $O(\log n)$ ancestors, we can compute the depth $dep[x]$ while building the centroid tree, or use LCA, to precompute these distances or answer them on the fly. **Note**: the distance from a node to its ancestors in the centroid tree is not necessarily increasing, so you cannot just add them up!

In dynamic centroid decomposition, a node may be counted more than once in the information of its ancestors in the centroid tree, so we need to cancel out the duplicated part. The usual method is to record each component in two ways: one is the distance information to its divide center, and the other is the distance information to the parent of the divide center in the centroid tree. This will be shown in the example problems.

??? note "Example problem [ZJOI2007 Hide and Seek](https://www.luogu.com.cn/problem/P2056)"
    You are given a tree with $n$ nodes. Initially all nodes are black. You need to support two operations:
    
    1.  Flip the color of a node (white becomes black, black becomes white);
    2.  Query the distance between the two farthest black nodes in the tree.
    
        $n\le 10^5,m\le 5\times 10^5$

Build the centroid tree, and for each node $x$ maintain two **deletable heaps**. $dist[x]$ stores the distances from all black nodes in the component represented by $x$ to $x$. $ch[x]$ stores the distances to $x$ of the black nodes among $x$ itself and all its children in the centroid tree. Because this problem computes the answer greedily, and two paths from the same subtree cannot form a complete path, we only insert into this heap the value of $x$ itself and the maximum of each subtree. Then the sum of the two largest values in $ch[x]$ (or all values, if there are fewer than two) is the longest path with black endpoints that passes through $x$ when $x$ is the divide center. We can use a deletable heap $ans$ to store the answers of all nodes; the maximum in this heap is the answer we want.

We can maintain the deletable heaps $dist[x],ch[x],ans$ according to these definitions. When a value in $dist[x]$ changes, we can also update $ch[x],ans$ in $O(\log n)$ time.

Now let's see how $dist[x]$ changes when we flip the color of a node. If the node was black, we perform a deletion; if it was white, we perform an insertion.

Suppose we flip the color of node $x$. For every ancestor $u$ of it, we insert or delete $dist(x,u)$ in $dist[u]$, and at the same time maintain $ch[x],ans$. In particular, we insert or delete the value $0$ in $ch[x]$.

Reference code:

```cpp
--8<-- "docs/graph/code/dynamic-tree-divide/dynamic-tree-divide_1.cpp"
```

???+ note "Example problem [Luogu P6329 [Template] Centroid Tree | Earthquake Waves](https://www.luogu.com.cn/problem/P6329)"
    You are given a tree with $n$ nodes, and each node has a weight $v[x]$. Support two operations:
    
    1.  Query the sum of weights of nodes at distance at most $y$ from node $x$;
    2.  Change the weight of node $x$ to $y$, that is, $v[x]=y$.

We use a dynamically allocated value segment tree (indexed by value) to record distance information.

Similar to the previous problem, for each node we maintain a segment tree $dist[x]$ that stores the distances from all nodes in the divide block $x$ to node $x$: the index is the distance, and the value adds up the vertex weights. The segment tree $ch[x]$ stores the distances from all nodes in the divide block $x$ to the parent of $x$ in the centroid tree.

In this problem, every query and update needs to touch all ancestors in the centroid tree.

Take a query as an example. To find the sum of weights of nodes at distance at most $y$ from node $x$, we first add the sum of indices $0$ to $y$ in segment tree $dist[x]$ to the answer. Then we go through every ancestor $u$ of $x$. Let $v$ be the ancestor one level below $u$, and let $d=dist(x,u)$. For the part that does not enter the subtree containing $x$ (the subtree rooted at $v$), we add the sum of indices $0$ to $y-d$ in segment tree $dist[u]$ to the answer. Since the part rooted at $v$ is counted twice, we subtract the sum of indices $0$ to $y-d$ in segment tree $ch[v]$ from the answer.

For updates, we maintain both $dist[x]$ and $ch[x]$ at the same time.

Reference code:

```cpp
--8<-- "docs/graph/code/dynamic-tree-divide/dynamic-tree-divide_2.cpp"
```
