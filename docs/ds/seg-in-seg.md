author: Chrogeek, HeRaNO, Dev-XYS, Dev-jqe

## Common uses

In competitive programming we sometimes need to maintain information in several dimensions. In such cases we often use a tree of trees (nested trees) to store it.

## How it works

Let's see how a tree of trees supports point updates and rectangle queries on a 2D plane. Consider the outer segment tree. Its leaves $1$ to $n$ each hold a segment tree for row $1$ to row $n$. A parent of these leaves then stands for the region covered by the subtrees of its two children.

## Properties

### Space complexity

Usually we cannot build an inner segment tree for every node of the outer segment tree, because that needs too much memory. A tree of trees normally uses dynamically allocated nodes. A single update touches $\log{n}$ nodes of the outer segment tree, and for each of them touches $\log{n}$ nodes of its inner tree, so a single update creates at most $\log^2{n}$ new nodes.

### Time complexity

For a query, we do $\log{n}$ operations on the outer segment tree, and each of them does $\log{n}$ operations on an inner segment tree, so the time complexity is $\log^2{n}$.
An update has the same complexity as a query, also $\log^2{n}$.

## Classic example problem

[Flowers Bloom on the Path (3D partial order)](https://www.luogu.com.cn/problem/P3810): sort by the first dimension, then use a tree of trees to handle the second and third dimensions.

## Sample code

Query on the second dimension

```cpp
int tree_query(int k, int l, int r, int x) {
  if (k == 0) return 0;
  if (1 <= l && r <= sec[x].y) return vec_query(ou_root[k], 1, p, 1, sec[x].z);
  int mid = l + r >> 1, res = 0;
  if (1 <= mid) res += tree_query(ou_ch[k][0], l, mid, x);
  if (sec[x].y > mid) res += tree_query(ou_ch[k][1], mid + 1, r, x);
  return res;
}
```

Update on the second dimension

```cpp
void tree_insert(int &k, int l, int r, int x) {
  if (k == 0) k = ++ou_tot;
  vec_insert(ou_root[k], 1, p, sec[x].z);
  if (l == r) return;
  int mid = l + r >> 1;
  if (sec[x].y <= mid)
    tree_insert(ou_ch[k][0], l, mid, x);
  else
    tree_insert(ou_ch[k][1], mid + 1, r, x);
}
```

Query on the third dimension

```cpp
int vec_query(int k, int l, int r, int x, int y) {
  if (k == 0) return 0;
  if (x <= l && r <= y) return data[k];
  int mid = l + r >> 1, res = 0;
  if (x <= mid) res += vec_query(ch[k][0], l, mid, x, y);
  if (y > mid) res += vec_query(ch[k][1], mid + 1, r, x, y);
  return res;
}
```

Update on the third dimension

```cpp
void vec_insert(int &k, int l, int r, int loc) {
  if (k == 0) k = ++tot;
  data[k]++;
  if (l == r) return;
  int mid = l + r >> 1;
  if (loc <= mid) vec_insert(ch[k][0], l, mid, loc);
  if (loc > mid) vec_insert(ch[k][1], mid + 1, r, loc);
}
```

## Related algorithms

For problems with multi-dimensional information, if the problem does not force online processing, you can also consider divide-and-conquer algorithms such as **CDQ divide and conquer** or **parallel binary search** to avoid advanced data structures and make the code easier to write.
