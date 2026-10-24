author: Dev-jqe, HeRaNO, huaruoji

## Common uses

In competitive programming, we sometimes need to maintain information in several dimensions. In such cases we often need a tree-in-tree structure to store the information. When we need to support predecessor, successor, the $k$-th largest value, the rank of a value, or insertions and deletions, we usually use a balanced tree to meet these needs, that is, a segment tree with a balanced tree in each node.

## Process

We use **Second-Rate Balanced Tree** (a classic problem) as an example to explain how it works.

To build the tree-in-tree, we build the outer segment tree as usual. For each node of the segment tree, we build a balanced tree that contains the part of the sequence covered by that node. In practice, we can insert the sequence elements one by one: for each segment tree node we pass through, we add the element to that node's balanced tree.

Operation 1, find the rank of a value in a range: we work on the outer segment tree as usual. For the balanced tree of each node inside the range, we return the number of elements smaller than the value. When merging ranges, we just add up these counts. Finally, add $1$ to the result to get the rank of the value in the range.

Operation 2, find the value with rank $k$ in a range: we can use binary search. An element may appear several times, so its rank is a range, and some values do not appear in the original sequence at all. So we use an idea similar to operation 1: binary search using the number of elements smaller than the value as the guide, and we get the answer.

Operation 3, replace one number with another: we just delete the old number from every balanced tree that contains it, then insert the new number. The outer segment tree is handled as usual.

Operation 4, find the predecessor of a value in a range: we work on the outer segment tree as usual. For the balanced tree of each node inside the range, we return the predecessor of the value in that balanced tree. When merging the results of segment tree ranges, we take the maximum.

## Properties

### Space complexity

Each element is added to $O(\log n)$ balanced trees, so the space complexity is $O((n + q)\log{n})$.

### Time complexity

-   For operations 1, 3 and 4: we do $O(\log{n})$ operations on the outer segment tree, and each one does $O(\log{n})$ work on an inner balanced tree, so the time complexity is $O(\log^2{n})$.
-   Operation 2 adds a binary search on top, so it takes $O(\log^3{n})$.

## Classic example problem

[Second-Rate Balanced Tree](https://loj.ac/problem/106): segment tree outside, balanced tree inside.

## Implementation

For the balanced tree code, see [Splay](./splay.md) and other pages.

Operation 1:

```cpp
int vec_rank(int k, int l, int r, int x, int y, int t) {
  if (x <= l && r <= y) {
    return spy[k].chk_rank(t);
  }
  int mid = l + r >> 1;
  int res = 0;
  if (x <= mid) res += vec_rank(k << 1, l, mid, x, y, t);
  if (y > mid) res += vec_rank(k << 1 | 1, mid + 1, r, x, y, t);
  if (x <= mid && y > mid) res--;
  return res;
}
```

Operation 2:

```cpp
int el = 0, er = 100000001, emid;
while (el != er) {
  emid = el + er >> 1;
  if (vec_rank(1, 1, n, tl, tr, emid) - 1 < tk)
    el = emid + 1;
  else
    er = emid;
}
printf("%d\n", el - 1);
```

Operation 3:

```cpp
void vec_chg(int k, int l, int r, int loc, int x) {
  int t = spy[k].find(dat[loc]);
  spy[k].dele(t);
  spy[k].insert(x);
  if (l == r) return;
  int mid = l + r >> 1;
  if (loc <= mid) vec_chg(k << 1, l, mid, loc, x);
  if (loc > mid) vec_chg(k << 1 | 1, mid + 1, r, loc, x);
}
```

Operation 4:

```cpp
int vec_front(int k, int l, int r, int x, int y, int t) {
  if (x <= l && r <= y) return spy[k].chk_front(t);
  int mid = l + r >> 1;
  int res = 0;
  if (x <= mid) res = max(res, vec_front(k << 1, l, mid, x, y, t));
  if (y > mid) res = max(res, vec_front(k << 1 | 1, mid + 1, r, x, y, t));
  return res;
}
```

## Related algorithms

For problems with multi-dimensional information, if the problem does not force online processing, we can also consider divide-and-conquer algorithms such as [CDQ divide and conquer](../misc/cdq-divide.md) or [parallel binary search](../misc/parallel-binsearch.md). They avoid advanced data structures and make the code easier to write.
