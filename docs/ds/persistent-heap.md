Persistent mergeable heaps are mainly used to solve the $k$-th shortest path problem.

If a mergeable heap's time complexity is not amortized, then after making it persistent each operation is still guaranteed to take $O(\log n)$ time. That is, special inputs cannot make the complexity degrade.

## Persistent leftist heap

Before reading this, please learn about the [leftist heap](./leftist-tree.md) first.

### Process

Recall how leftist heaps are merged. Suppose we want to merge two leftist heaps with roots $x,y$ respectively, and the heaps are min-heaps:

1.  If one of $x,y$ is empty, return $x+y$.

2.  Of the two nodes $x,y$, pick the one with the smaller value as the root of the merged heap.

3.  Recursively merge the right subtree of $x$ with $y$, and make the merged root the right child of $x$.

4.  Restore the leftist property of the merged heap, update the `dist` value, and return the chosen root.

Each recursive call decreases `dist[x]+dist[y]` by one, and `dist[x]` is $O(\log n)$, so at most $O(\log n)$ nodes are changed per merge. Thus the time complexity is $O(\log n)$.

Persistence requires keeping historical information so that earlier versions can be accessed later. To make a leftist heap persistent, we copy every node along the path we modify.

So merging in a persistent leftist heap works like this:

1.  If one of $x,y$ is empty, return $x+y$.

2.  Of the two nodes $x,y$, pick the one with the smaller value, create a copy $p$ of it, and use it as the root of the merged heap.

3.  Recursively merge the right subtree of $p$ with $y$, and make the merged root the right child of $p$.

4.  Restore the leftist property of the heap rooted at $p$, update its `dist` value, and return $p$.

A leftist heap changes and creates at most $O(\log n)$ nodes per operation. If there are $m$ operations, the persistent leftist heap has time and space complexity $O(m\log n)$.

### Reference implementation

```cpp
int merge(int x, int y) {
  if (!x || !y) return x + y;
  if (v[x] > v[y]) swap(x, y);
  int p = ++cnt;
  lc[p] = lc[x];
  v[p] = v[x];
  rc[p] = merge(rc[x], y);
  if (dist[lc[p]] < dist[rc[p]]) swap(lc[p], rc[p]);
  dist[p] = dist[rc[p]] + 1;
  return p;
}
```
