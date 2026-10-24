## Introduction

You are given a sequence ${\left\langle a_i\right\rangle}_{i=1}^n$ of length n and an associative operation $\circ$ (for example, $\gcd,\min,\max,+,\operatorname{and},\operatorname{or},\operatorname{xor}$ are all associative). For each range query $[l,r]$, we need to compute $a_l\circ a_{l+1}\circ\dotsb\circ a_{r}$.

A Sqrt Tree can be preprocessed in $O(n\log\log n)$ time and answers each query in $O(1)$ time.

## Explanation

### Splitting the sequence into blocks

First, we split the whole sequence into $O(\sqrt{n})$ blocks, each of size $O(\sqrt{n})$. For each block, we compute:

1.  $P_i$: the answers for prefixes within the block
2.  $S_i$: the answers for suffixes within the block
3.  An extra array $\left\langle B_{i,j}\right\rangle$, the answer for the range from block $i$ to block $j$.

For example, let $\circ$ be addition $+$, and let the sequence be $\{1,2,3,4,5,6,7,8,9\}$.

First we split the sequence into three blocks: $\{1,2,3\},\{4,5,6\},\{7,8,9\}$.

Then the prefix answers and suffix answers of each block are

$$
\begin{aligned}
&P_1=\{1,3,6\},S_1=\{6,5,3\}\\
&P_2=\{4,9,15\},S_2=\{15,11,6\}\\
&P_3=\{7,15,24\},S_3=\{24,17,9\}\\
\end{aligned}
$$

The $B$ array is:

$$
B=\begin{bmatrix}
6 & 21 & 45\\
0 & 15 & 39\\
0 & 0 & 24\\
\end{bmatrix}
$$

(For the invalid cases with $i>j$, we take the answer to be 0.)

Clearly we can precompute these values in $O(n)$ time, and the space complexity is also $O(n)$. Once they are ready, we can use them to answer queries that span several blocks in $O(1)$ time. But we still cannot handle queries whose whole range lies inside a single block, so we need something more.

### Building a tree

A natural idea is to build the same structure recursively inside each block, to support queries within a block. For a block of size $1$, we can answer queries in $O(1)$. This builds a tree in which each node represents a range of the sequence. Leaf nodes have ranges of length $1$ or $2$. A node of size $k$ has $O(\sqrt{k})$ children, so the height of the whole tree is $O(\log\log n)$, and the total length of the ranges on each level is $O(n)$. Therefore building the tree takes $O(n\log\log n)$ time.

??? note "Proof of the tree height"
    By definition, let $T(n)$ be the height of the subtree of a node that "controls" $n$ elements. We can write the recurrence:
    
    $$
    T(n)=T(\sqrt n)+1
    $$
    
    Substituting $n=2^m$ gives
    
    $$
    T(2^m)=T(2^{\frac m2})+1
    $$
    
    Then define $S(m)=T(2^m)$ and substitute:
    
    $$
    S(m)=S(\dfrac m2)+1
    $$
    
    By the master theorem, $S(m)=O(\log m)$, so $T(n)=S(\log n)=O(\log\log n)$.

Now we can answer queries in $O(\log\log n)$ time. For a query $[l,r]$, we just need to quickly find the node $u$ with the shortest range that contains $[l,r]$. Then $[l,r]$ must span several blocks of $u$, and we can compute the answer in $O(1)$. The total cost of one query is $O(\log\log n)$, because the tree height is $O(\log\log n)$. But we can still speed this up.

### Optimizing query time

A natural idea is to binary search on the height, since we can check whether a height works in $O(1)$. That makes the complexity $O(\log\log\log n)$. But we can speed it up even further.

We assume that

1.  the size of every block is a power of $2$;
2.  all blocks on the same level have the same size.

To achieve this, we pad the end of the sequence with some $0$ elements so that its length becomes a power of $2$. Some blocks may become twice as large as before, but they are still $O(\sqrt{k})$, so preprocessing the blocks still takes $O(n)$ time.

Now we can easily tell whether a query range lies entirely inside one block. For a range $[l,r]$ (0-indexed), write the endpoints in binary. For example, with $k=4, l=39, r=46$, the binary forms are

$$
l = 39_{10} = 100111_2,
r = 46_{10} = 101110_2
$$

We know that all ranges on a level have the same length, and the blocks also have the same size ($2^k=2^4=16$ in the example above). These blocks cover the whole sequence, so the first block covers elements $[0,15]$ (in binary $[000000_2,001111_2]$), the second block covers $[16,31]$ (in binary $[010000_2,011111_2]$), and so on. We can see that positions of elements in the same block differ only in their last $k$ bits ($k=4$ in the example). In the example, $l$ and $r$ also differ only in their last $k$ bits, so they are in the same block.

So we need to check whether the two endpoints of the range differ only in their last $k$ bits, i.e. $l\oplus r\le 2^k-1$. This lets us quickly find the level that holds the answer range:

1.  For each $i\in [1,n]$, find the highest set bit of $i$;
2.  Now for a query $[l,r]$, compute the highest bit of $l\oplus r$. This quickly tells us which level holds the answer range.

And so we can answer queries in $O(1)$ time.

## Updating elements

We can update elements in a Sqrt Tree. Both point updates and range updates are supported.

### Point update

Consider a point assignment $a_x=val$. We want to update the stored information for this operation efficiently.

#### Naive implementation

First, let us see what happens to the Sqrt Tree after one point update.

Consider a node of length $l$ and its arrays $\left\langle P_i\right\rangle,\left\langle S_i\right\rangle,\left\langle B_{i,j}\right\rangle$. It is easy to see that only $O(\sqrt{l})$ elements change in $\left\langle P_i\right\rangle$ and in $\left\langle S_i \right\rangle$, while $O(l)$ elements change in $\left\langle B_{i,j}\right\rangle$. So $O(l)$ elements are updated in this node of the tree. Therefore a point update on a Sqrt Tree costs $O(n+\sqrt{n}+\sqrt{\sqrt{n}}+\dotsb)=O(n)$.

#### Replacing the B array with a Sqrt Tree

Notice that the bottleneck of a point update is updating the root's $\left\langle B_{i,j}\right\rangle$. So we try to replace the root's $\left\langle B_{i,j}\right\rangle$ with another Sqrt Tree, called $index$. It plays the same role as the original 2D array: it stores answers for runs of whole blocks. All other non-root nodes still use $\left\langle B_{i,j}\right\rangle$. Note: if the root of a Sqrt Tree has an $index$ structure, we call the Sqrt Tree **indexed**; if the root of a Sqrt Tree has a $\left\langle B_{i,j}\right\rangle$ structure, we call it **unindexed**. The $index$ tree itself is unindexed.

So we can update the $index$ tree like this:

1.  Update $\left\langle P_i\right\rangle$ and $\left\langle S_i\right\rangle$ in $O(\sqrt{n})$ time.
2.  Update $index$. Its length is $O(n)$, but we only need to update one element of it (the element that represents the changed block). This step takes $O(\sqrt{n})$ time (using the naive algorithm).
3.  Go into the child node that changed and use the naive algorithm to update its information in $O(\sqrt{n})$ time.

Note that queries still take $O(1)$ time, because we use the $index$ tree at most once. So a point update takes $O(\sqrt{n})$ time.

### Updating a range

A Sqrt Tree also supports range assignment $\operatorname{Update}(l,r,x)$, which sets every number in the range $[l,r]$ to $x$. There are two ways to implement this. One spends $O(\sqrt{n}\log\log n)$ on updates and $O(1)$ on queries; the other spends $O(\sqrt{n})$ on updates, but queries go up to $O(\log\log n)$.

We can put lazy tags on a Sqrt Tree just like on a segment tree. But there is one difference on a Sqrt Tree. Pushing down the lazy tag of a node may cost up to $O(\sqrt{n})$, so instead of pushing tags down during queries, we check whether the parent has a tag, and if it does, we push it down.

#### First implementation

In the first implementation, we only put lazy tags on nodes on level $1$ (nodes whose range length is $O(\sqrt{n})$). When pushing down a tag, we update the whole subtree directly, which costs $O(\sqrt{n}\log\log n)$. The process is:

1.  Look at the nodes on level $1$. Put a lazy tag on each node whose range is fully contained in the updated range;

2.  Two blocks are only partly covered. We **rebuild** these two blocks directly in $O(\sqrt{n}\log\log n)$ time. If such a block already has a lazy tag from an earlier update, push that tag down during the rebuild;

3.  Update the root's $\left\langle P_i\right\rangle$ and $\left\langle S_i\right\rangle$, in $O(\sqrt{n})$ time;

4.  Rebuild the $index$ tree, in $O(\sqrt{n}\log\log n)$ time.

Now range updates are efficient. How do we answer queries with the lazy tags? Like this:

1.  If the query lies inside one block that has a lazy tag, we can compute the answer from the lazy tag;

2.  If the query covers several blocks, we only need to care about the answers for the incomplete leftmost and rightmost blocks. The answer for the blocks in the middle can be queried from the $index$ tree (since the $index$ tree is rebuilt after every update), in $O(1)$.

So queries still take $O(1)$ time.

#### Second implementation

In this implementation, every node can have a lazy tag. So when handling a query, we must take the lazy tags of the ancestors into account, and the query cost becomes $O(\log\log n)$. In exchange, updates become faster. The process is:

1.  For blocks fully contained in the updated range, add a lazy tag to those blocks, in $O(\sqrt{n})$;
2.  For blocks partly covered by the updated range, update $\left\langle P_i\right\rangle$ and $\left\langle S_i\right\rangle$, in $O(\sqrt{n})$ (since only two blocks are partly covered);
3.  Update the $index$ tree, in $O(\sqrt{n})$ (using the same update algorithm);
4.  For unindexed subtrees, update their $\left\langle B_{i,j}\right\rangle$;
5.  Recursively update the two ranges that are not fully covered.

The time complexity is $O(\sqrt{n}+\sqrt{\sqrt{n}}+\dotsb)=O(\sqrt{n})$.

## Implementation

The implementation below builds the tree in $O(n\log\log n)$ time, answers queries in $O(1)$ time, and does point updates in $O(\sqrt{n})$ time.

```cpp
SqrtTreeItem op(const SqrtTreeItem &a, const SqrtTreeItem &b);

int log2Up(int n) {
  int res = 0;
  while ((1 << res) < n) {
    res++;
  }
  return res;
}

class SqrtTree {
 private:
  int n, lg, indexSz;
  vector<SqrtTreeItem> v;
  vector<int> clz, layers, onLayer;
  vector<vector<SqrtTreeItem>> pref, suf, between;

  void buildBlock(int layer, int l, int r) {
    pref[layer][l] = v[l];
    for (int i = l + 1; i < r; i++) {
      pref[layer][i] = op(pref[layer][i - 1], v[i]);
    }
    suf[layer][r - 1] = v[r - 1];
    for (int i = r - 2; i >= l; i--) {
      suf[layer][i] = op(v[i], suf[layer][i + 1]);
    }
  }

  void buildBetween(int layer, int lBound, int rBound, int betweenOffs) {
    int bSzLog = (layers[layer] + 1) >> 1;
    int bCntLog = layers[layer] >> 1;
    int bSz = 1 << bSzLog;
    int bCnt = (rBound - lBound + bSz - 1) >> bSzLog;
    for (int i = 0; i < bCnt; i++) {
      SqrtTreeItem ans;
      for (int j = i; j < bCnt; j++) {
        SqrtTreeItem add = suf[layer][lBound + (j << bSzLog)];
        ans = (i == j) ? add : op(ans, add);
        between[layer - 1][betweenOffs + lBound + (i << bCntLog) + j] = ans;
      }
    }
  }

  void buildBetweenZero() {
    int bSzLog = (lg + 1) >> 1;
    for (int i = 0; i < indexSz; i++) {
      v[n + i] = suf[0][i << bSzLog];
    }
    build(1, n, n + indexSz, (1 << lg) - n);
  }

  void updateBetweenZero(int bid) {
    int bSzLog = (lg + 1) >> 1;
    v[n + bid] = suf[0][bid << bSzLog];
    update(1, n, n + indexSz, (1 << lg) - n, n + bid);
  }

  void build(int layer, int lBound, int rBound, int betweenOffs) {
    if (layer >= (int)layers.size()) {
      return;
    }
    int bSz = 1 << ((layers[layer] + 1) >> 1);
    for (int l = lBound; l < rBound; l += bSz) {
      int r = min(l + bSz, rBound);
      buildBlock(layer, l, r);
      build(layer + 1, l, r, betweenOffs);
    }
    if (layer == 0) {
      buildBetweenZero();
    } else {
      buildBetween(layer, lBound, rBound, betweenOffs);
    }
  }

  void update(int layer, int lBound, int rBound, int betweenOffs, int x) {
    if (layer >= (int)layers.size()) {
      return;
    }
    int bSzLog = (layers[layer] + 1) >> 1;
    int bSz = 1 << bSzLog;
    int blockIdx = (x - lBound) >> bSzLog;
    int l = lBound + (blockIdx << bSzLog);
    int r = min(l + bSz, rBound);
    buildBlock(layer, l, r);
    if (layer == 0) {
      updateBetweenZero(blockIdx);
    } else {
      buildBetween(layer, lBound, rBound, betweenOffs);
    }
    update(layer + 1, l, r, betweenOffs, x);
  }

  SqrtTreeItem query(int l, int r, int betweenOffs, int base) {
    if (l == r) {
      return v[l];
    }
    if (l + 1 == r) {
      return op(v[l], v[r]);
    }
    int layer = onLayer[clz[(l - base) ^ (r - base)]];
    int bSzLog = (layers[layer] + 1) >> 1;
    int bCntLog = layers[layer] >> 1;
    int lBound = (((l - base) >> layers[layer]) << layers[layer]) + base;
    int lBlock = ((l - lBound) >> bSzLog) + 1;
    int rBlock = ((r - lBound) >> bSzLog) - 1;
    SqrtTreeItem ans = suf[layer][l];
    if (lBlock <= rBlock) {
      SqrtTreeItem add =
          (layer == 0) ? (query(n + lBlock, n + rBlock, (1 << lg) - n, n))
                       : (between[layer - 1][betweenOffs + lBound +
                                             (lBlock << bCntLog) + rBlock]);
      ans = op(ans, add);
    }
    ans = op(ans, pref[layer][r]);
    return ans;
  }

 public:
  SqrtTreeItem query(int l, int r) { return query(l, r, 0, 0); }

  void update(int x, const SqrtTreeItem &item) {
    v[x] = item;
    update(0, 0, n, 0, x);
  }

  SqrtTree(const vector<SqrtTreeItem> &a)
      : n((int)a.size()), lg(log2Up(n)), v(a), clz(1 << lg), onLayer(lg + 1) {
    clz[0] = 0;
    for (int i = 1; i < (int)clz.size(); i++) {
      clz[i] = clz[i >> 1] + 1;
    }
    int tlg = lg;
    while (tlg > 1) {
      onLayer[tlg] = (int)layers.size();
      layers.push_back(tlg);
      tlg = (tlg + 1) >> 1;
    }
    for (int i = lg - 1; i >= 0; i--) {
      onLayer[i] = max(onLayer[i], onLayer[i + 1]);
    }
    int betweenLayers = max(0, (int)layers.size() - 1);
    int bSzLog = (lg + 1) >> 1;
    int bSz = 1 << bSzLog;
    indexSz = (n + bSz - 1) >> bSzLog;
    v.resize(n + indexSz);
    pref.assign(layers.size(), vector<SqrtTreeItem>(n + indexSz));
    suf.assign(layers.size(), vector<SqrtTreeItem>(n + indexSz));
    between.assign(betweenLayers, vector<SqrtTreeItem>((1 << lg) + bSz));
    build(0, 0, n, 0);
  }
};
```

## Exercises

[CodeChef - SEGPROD](https://www.codechef.com/NOV17/problems/SEGPROD)

**This page is mainly translated from [Sqrt Tree - Algorithms for Competitive Programming](https://cp-algorithms.com/data_structures/sqrt-tree.html), licensed under CC-BY-SA 4.0.**
