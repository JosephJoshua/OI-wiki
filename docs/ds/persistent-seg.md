## Persistent segment tree (Chairman tree)

The "Chairman tree" (the common Chinese nickname for this structure) is short for the persistent value-domain segment tree, that is, a persistent segment tree built over values; see [this Zhihu discussion](https://www.zhihu.com/question/59195374).

???+ warning "About functional segment trees"
    A **functional segment tree** is a segment tree built with the ideas of functional programming. Functional programming treats computation as evaluating mathematical functions and avoids mutable state or variables. It is easy to see that a functional segment tree is [fully persistent](persistent.md#完全可持久化-fully-persistent).

## Introduction

Let us start with a problem: given a sequence $a$ of $n$ integers, answer queries for the $k$-th smallest value in a given closed range $[l, r]$.

How would you solve it?

One workable approach is to use a persistent segment tree.
The main idea of the persistent segment tree is: keep the historical version after each insertion, so that we can query the $k$-th smallest value in a range.

How do we keep them? The simple brute-force way is to build a whole new segment tree each time.  
But wouldn't that blow up the memory?

## Explanation

Looking closer, we see that each modification changes the same number of nodes.  
(For example, in the figure below we modify the node for value 1 in $[1,8]$; the red nodes are the changed ones.)  
![](./images/persistent-seg.png)

Only $O(\log{n})$ nodes change, and they form a chain. In other words, the number of nodes changed each time equals the height of the tree.  
Note that a persistent segment tree cannot use heap-style storage, which means you cannot use $x\times 2$ and $x\times 2+1$ for the left and right children. Instead, create nodes dynamically and store the indices of each node's left and right children.  
So as long as we record the left and right children and save the root after inserting each number, we get persistence.

Let us simplify the problem first: each query asks for the $k$-th smallest value in $[1,r]$.  
How? Just find the root of the version right after inserting r, and then query it as an ordinary value-domain segment tree (also called a key-value segment tree or range-of-values segment tree).

That should be easy to understand. Now back to the original problem: find the $k$-th smallest value in $[l,r]$.  
Here we connect it with another idea: **prefix sums**.  
This little trick cleverly uses the fact that ranges can be subtracted, and with preprocessing it answers each query in $O(1)$.

We can see that the counts stored in a persistent segment tree have the same property.  
So... to get the counts for $[l,r]$, just subtract the counts for $[1,l - 1]$ from the counts for $[1,r]$.

And the problem is solved!

Now let us analyze the memory. Since nodes are created dynamically, one segment tree has only $2n-1$ nodes.  
Then there are $n$ modifications, each adding at most $\lceil\log_2{n}\rceil+1$ nodes. So in the worst case, after $n$ modifications the total number of nodes reaches $2n-1+n(\lceil\log_2{n}\rceil+1)$.
In this problem $n \leq 10^5$, and each modification adds at most $\lceil\log_2{10^5}\rceil+1 = 18$ nodes. So after $n$ modifications there are $2\times 10^5-1+18\times 10^5$ nodes in total. Ignoring the $-1$, that is about $20\times 10^5$.

One last piece of advice: do not be stingy with memory (in most problems the memory limit is fairly generous, so you usually need not worry about exceeding it)! Be bold and just allocate $2^5\times 10^5$, close to twice the computed size (that is, `n << 5`).

## Implementation

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
constexpr int MAXN = 1e5;  // data range
int tot, n, m;
int sum[(MAXN << 5) + 10], rt[MAXN + 10], ls[(MAXN << 5) + 10],
    rs[(MAXN << 5) + 10];
int a[MAXN + 10], ind[MAXN + 10], len;

int getid(const int &val) {  // coordinate compression
  return lower_bound(ind + 1, ind + len + 1, val) - ind;
}

int build(int l, int r) {  // build the tree
  int root = ++tot;
  if (l == r) return root;
  int mid = l + r >> 1;
  ls[root] = build(l, mid);
  rs[root] = build(mid + 1, r);
  return root;  // return the root of this subtree
}

int update(int k, int l, int r, int root) {  // insertion
  int dir = ++tot;
  ls[dir] = ls[root], rs[dir] = rs[root], sum[dir] = sum[root] + 1;
  if (l == r) return dir;
  int mid = l + r >> 1;
  if (k <= mid)
    ls[dir] = update(k, l, mid, ls[dir]);
  else
    rs[dir] = update(k, mid + 1, r, rs[dir]);
  return dir;
}

int query(int u, int v, int l, int r, int k) {  // query
  int mid = l + r >> 1,
      x = sum[ls[v]] - sum[ls[u]];  // range subtraction gives the count of numbers stored in the left child
  if (l == r) return l;
  if (k <= x)  // if k <= x, the k-th smallest number is in the left child
    return query(ls[u], ls[v], l, mid, k);
  else  // otherwise it is in the right child
    return query(rs[u], rs[v], mid + 1, r, k - x);
}

void init() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) scanf("%d", a + i);
  memcpy(ind, a, sizeof ind);
  sort(ind + 1, ind + n + 1);
  len = unique(ind + 1, ind + n + 1) - ind - 1;
  rt[0] = build(1, len);
  for (int i = 1; i <= n; ++i) rt[i] = update(getid(a[i]), 1, len, rt[i - 1]);
}

int l, r, k;

void work() {
  while (m--) {
    scanf("%d%d%d", &l, &r, &k);
    printf("%d\n", ind[query(rt[l - 1], rt[r], 1, len, k)]);  // answer the query
  }
}

int main() {
  init();
  work();
  return 0;
}
```

## Extension: persistent DSU based on a persistent segment tree

A persistent segment tree is a convenient way to implement a persistent disjoint set union. Here is an example implementation of a persistent DSU based on a persistent segment tree.

```cpp
--8<-- "docs/ds/code/persistent-seg/persistent-seg_1.cpp"
```

## References

<https://en.wikipedia.org/wiki/Persistent_data_structure>

<https://www.cnblogs.com/zinthos/p/3899565.html>
