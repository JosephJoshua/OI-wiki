## Persistent non-rotating treap

### Prerequisites

**The persistent balanced tree commonly used in OI** is usually the **persistent non-rotating treap**, so we recommend learning the [**non-rotating treap**](./treap.md) first.

### Idea/approach

For a non-rotating treap, we can make it persistent by copying the nodes along the path visited during **Merge** and **Split** (usually the copying happens in **Split**, so that earlier versions are not affected).

For a rotating treap, besides copying the nodes along the path, we also need to copy the nodes affected by rotations (unless they were already copied in this operation). A single rotation usually affects only two nodes, so this does not increase the time complexity.

This method is usually called path copying.

"Every supported operation can be done with **Merge Split Newnode Build**". **Build** is only used to construct the tree and can be ignored here, and **Newnode** (creating a new node) is the tool that makes persistence possible.

Look at **Merge** and **Split**: both are top-down operations!

So we can make the treap persistent **in the same way as a persistent segment tree**.

### Persistent operations

**Persistence** is something we do to a **data structure**: we keep historical information so that earlier versions can be accessed later.

For a **persistent segment tree**, each new version is created by copying **the path of modifications along the way**

For a persistent treap (the version commonly used in Chinese OI today):

After creating a new version $X_{a+1}$ (version $a+1$ of node $X$) by copying a node $X_{a}$ (version $a$ of node $X$):

-   If a child node $Y$ does not need to change, just point $X_{a+1}$'s pointer directly at $Y_{a}$ (version $a$ of node $Y$).
-   Otherwise, if $Y$ must change, then **when recursing to the lower level**, **create** a new node $Y_{a+1}$ (version $a+1$ of node $Y$) to **store the new information**, and point $X_{a+1}$'s pointer at $Y_{a+1}$ (version $a+1$ of node $Y$).

### Making it persistent

What we need:

-   A `struct` array that stores the information of **each node** (usually called the `tree` array); (experts who write the **pointer version** of the balanced tree can of course skip this array)

-   A **root array** that stores the *root* of each version. Every query on a version starts from **the node stored in the root array**;

-   `split()`: **splits one tree into two trees**

-   `merge()`: **merges two trees according to their random priorities**

-   `newNode()`: creates a new node

-   `build()`: builds the tree

#### Split

For the **split operation**, each time we split along the path we **create new nodes** pointing to the split-off parts, and use `std::pair` to store the roots of the two new trees.

`split(x,k)` returns a `std::pair`;

It puts the first $k$ elements of the tree rooted at $_x$ into **one tree** and the remaining nodes into another tree, and returns the roots of these two trees (first is the root of the first tree, second is the root of the second).

-   If $key \geq k$ holds for the **left subtree** of $x$, **recurse directly into the left subtree**, and merge the second tree split from the left subtree with the current **right subtree** of $x$.
-   Otherwise recurse into the **right subtree**.

```cpp
static std::pair<int, int> _split(int _x, int k) {
  if (_x == 0)
    return std::make_pair(0, 0);
  else {
    int _vs = ++_cnt;  // create a new node (the essence of persistence)
    _trp[_vs] = _trp[_x];
    std::pair<int, int> _y;
    if (_trp[_vs].key <= k) {
      _y = _split(_trp[_vs].leaf[1], k);
      _trp[_vs].leaf[1] = _y.first;
      _y.first = _vs;
    } else {
      _y = _split(_trp[_vs].leaf[0], k);
      _trp[_vs].leaf[0] = _y.second;
      _y.second = _vs;
    }
    _trp[_vs]._update();
    return _y;
  }
}
```

#### Merge

`merge(x,y)` returns the root of the merged tree.

It is also implemented recursively. If **the random priority of x** > **the random priority of y**, then `merge(x_{rc},y)`; otherwise `merge(x,y_{lc})`.

```cpp
static int _merge(int _x, int _y) {
  if (_x == 0 || _y == 0)
    return _x ^ _y;
  else {
    if (_trp[_x].fix < _trp[_y].fix) {
      _trp[_x].leaf[1] = _merge(_trp[_x].leaf[1], _y);
      _trp[_x]._update();
      return _x;
    } else {
      _trp[_y].leaf[0] = _merge(_x, _trp[_y].leaf[0]);
      _trp[_y]._update();
      return _y;
    }
  }
}
```

## Persistent WBLT

### Prerequisites

The persistent WBLT is a modification of the WBLT, so learn [WBLT](./wblt.md) first.

### Idea/approach

Use **path copying**: copy every node that is **modified** during an operation, so that earlier nodes are not affected.

### Handling lazy tags

To handle lazy tags, think about it this way: in a persistent WBLT, a node may have several parents, but it always has either $0$ or $2$ children. A pushdown only affects the node's children, so doing a pushdown on a node does no harm to the node itself. The problem is its children: a child may have parents other than this node. Pushing the tag down into such a child would give the versions that use the other parents an extra lazy tag that does not belong to them, which is wrong—unless the child has this node as its only parent. So during pushdown we should copy the children first and put the lazy tag on the new children.

### Implementing path copying

For path copying, we can define a refresh function. It takes a reference to a node $p$, copies $p$ to make a new node, and assigns the new node back to $p$. The rule for using refresh is: if a node is about to be modified, or the set of children it owns is about to change (as opposed to the information inside its children changing), refresh it; otherwise there is no need.

For static queries, no refresh is needed except in pushdown. If every operation does path copying, the order of pushdown and refresh does not matter.

### A small optimization for the persistent WBLT

Here is an optimization. Notice that pushdown copies two nodes. We could use permanent tags (tag permanence) instead, but as said above, if a child has only one parent, we do not need to copy it. We can use this property to avoid copying unnecessary nodes.

Record for each node how many parents it has (the root of each version counts as having one parent), and call it $use$. On each refresh, if $use\leq 1$ we do not need to copy the node. Otherwise we create a new node and decrease $use$ by $1$, meaning that the parent has "taken this child away", so the parent can freely change the new node without affecting other versions. Also, each time we copy a node that has children, the $use$ of both children increases by $1$; when merging two subtrees, the returned node also counts as one parent in the $use$ of its two children; when deleting a node, both of its children lose a parent. This saves some time and memory.

### Implementation

??? note "Full code (persistent balanced tree with range reversal)"
    ```cpp
    --8<-- "docs/ds/code/persistent-balanced/persistent-wblt.cpp"
    ```

## Example problem

???+ note "[Luogu P3835 [Template] Persistent Balanced Tree](https://www.luogu.com.cn/problem/P3835)"
    You need to implement a data structure that supports the following operations (it starts out empty):
    
    1.  Insert the number $x$;
    2.  Delete the number $x$ (if there are several equal numbers, delete only one; if there is none, ignore this operation);
    3.  Query the rank of $x$ (the rank is defined as the number of numbers smaller than it, plus 1);
    4.  Query the number with rank $x$;
    5.  Find the predecessor of $x$ (the predecessor is the largest number smaller than $x$; if it does not exist, output $-2\,147\,483\,647$);
    6.  Find the successor of $x$ (the successor is the smallest number larger than $x$; if it does not exist, output $2\,147\,483\,647$).
    
    Each operation is based on some historical version and creates a new version (operations 3, 4, 5, 6 keep the original version unchanged). The version number is the index of the operation. In particular, the initial version is numbered 0.

This is just the persistent version of the **ordinary balanced tree** problem, and the operations are similar to that problem.

The only difference is that we use the persistent merge and split operations.

## Recommended practice problems

1.  ["Luogu P3919" Persistent Array (template problem)](https://www.luogu.com.cn/problem/P3919)

2.  ["Codeforces 702F" T-shirt](http://codeforces.com/problemset/problem/702/F)

3.  ["Luogu P5055" Persistent Balanced Tree with Range Reversal](https://www.luogu.com.cn/problem/P5055)

4.  ["Luogu P5350" Sequence](https://www.luogu.com.cn/problem/P5350)
