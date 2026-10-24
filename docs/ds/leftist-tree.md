author: JiZiQian, llleixx, firefly-zjyjoe

## What is a leftist heap?

A **leftist heap**, like the [**pairing heap**](./pairing-heap.md), is a **mergeable heap**: it has the heap property and can be merged quickly.

## Definition and properties of a leftist heap

For a binary tree, we define an **external node** as a node with fewer than two children, and define the $\mathrm{dist}$ of a node as the number of edges from it to the nearest external node in its subtree. The $\mathrm{dist}$ of an empty node is $0$.

???+ note "Note"
    Some sources define $\mathrm{dist}$ as this page's $\mathrm{dist}$ minus $1$. This lets the code skip some null checks, but you must set the $\mathrm{dist}$ of empty nodes to $-1$ beforehand. All code on this page **uses the definition where the $\mathrm{dist}$ of an empty node is $-1$**. Keep in mind how this differs from the $\mathrm{dist}$ definition used in the text.

A leftist heap is a binary tree that not only has the heap property but is also "leftist": for every node, the $\mathrm{dist}$ of its left child is greater than or equal to the $\mathrm{dist}$ of its right child.

So the $\mathrm{dist}$ of every node in a leftist heap equals the $\mathrm{dist}$ of its right child plus one.

Note that $\mathrm{dist}$ is not depth. **The depth of a leftist heap is not bounded**: a chain going left also satisfies the definition of a leftist heap.

## Core operation: merge

When merging two heaps, to keep the heap property, first take the root with the smaller value (for convenience, this page discusses min-heaps) as the root of the merged heap. Keep this root's left child as the left child of the merged heap, and recursively merge its right child with the other heap to get the right child of the merged heap. To keep the leftist property, after merging, if the $\mathrm{dist}$ of the left child is less than the $\mathrm{dist}$ of the right child, swap the two children.

Reference code:

???+ note "Implementation"
    ```cpp
    int merge(int x, int y) {
      if (!x || !y) return x | y;  // If one heap is empty, return the other
      if (t[x].val > t[y].val) swap(x, y);  // Use the smaller value as the root
      t[x].rs = merge(t[x].rs, y);          // Recursively merge the right child with the other heap
      if (t[t[x].rs].d > t[t[x].ls].d)
        swap(t[x].ls, t[x].rs);   // Swap the children if the leftist property is broken
      t[x].d = t[t[x].rs].d + 1;  // Update dist
      return x;
    }
    ```

Because of the leftist property, each level of recursion reduces the $\mathrm{dist}$ of one of the heap roots by $1$. In a binary tree with $n$ nodes, the root's $\mathrm{dist}$ is at most $\left\lceil\log (n+1)\right\rceil$. So merging two heaps of sizes $n$ and $m$ takes $O(\log n+\log m)$.

???+ note "Proof of the $\mathrm{dist}$ property"
    A binary tree whose root has $\mathrm{dist}$ $x$ has at least $x-1$ full levels, so it has at least $2^x-1$ nodes. Note that this property holds for all binary trees, not just leftist heaps.

There is also a way to write a leftist heap without swapping children: treat the child with the larger $\mathrm{dist}$ as the left child and the child with the smaller $\mathrm{dist}$ as the right child:

???+ note "Implementation"
    ```cpp
    int& rs(int x) { return t[x].ch[t[t[x].ch[1]].d < t[t[x].ch[0]].d]; }
    
    int merge(int x, int y) {
      if (!x || !y) return x | y;
      if (t[x].val < t[y].val) swap(x, y);
      int& rs_ref = rs(x);
      rs_ref = merge(rs_ref, y);
      t[x].d = t[rs(x)].d + 1;
      return x;
    }
    ```

## Other operations on leftist heaps

### Inserting a node

A single node can also be seen as a heap, so just merge it in.

### Deleting the root

Just merge the root's left and right children.

### Deleting an arbitrary node

#### Method

First merge the left and right children, then update $\mathrm{dist}$ from the bottom up, swapping the children wherever the leftist property is broken. Stop the recursion once $\mathrm{dist}$ no longer needs updating:

???+ note "Implementation"
    ```cpp
    int& rs(int x) { return t[x].ch[t[t[x].ch[1]].d < t[t[x].ch[0]].d]; }
    
    // With pushup, merging the left and right children directly deletes the node and keeps the leftist property
    int merge(int x, int y) {
      if (!x || !y) return x | y;
      if (t[x].val < t[y].val) swap(x, y);
      int& rs_ref = rs(x);
      rs_ref = merge(rs_ref, y);
      t[rs_ref].fa = x;
      t[x].d = t[rs(x)].d + 1;
      return x;
    }
    
    void pushup(int x) {
      if (!x) return;
      if (t[x].d != t[rs(x)].d + 1) {
        t[x].d = t[rs(x)].d + 1;
        pushup(t[x].fa);
      }
    }
    
    void erase(int x) {
      int y = merge(t[x].ch[0], t[x].ch[1]);
      t[y].fa = t[x].fa;
      if (t[t[x].fa].ch[0] == x)
        t[t[x].fa].ch[0] = y;
      else if (t[t[x].fa].ch[1] == x)
        t[t[x].fa].ch[1] = y;
      pushup(t[y].fa);
    }
    ```

#### Proof of complexity

First consider `merge`. Each step moves $x$ or $y$ down one level. In the most extreme case, we always go down to the right child of the leftist heap (the child with the smallest $\mathrm{dist}$), and then $\mathrm{dist}$ decreases by $1$.

Next consider `pushup`. Let the node currently being processed by `pushup` be $x$ and its parent be $y$, and call a node's $\mathrm{dist}$ before `pushup` its "initial $\mathrm{dist}$". Starting the recursion from the parent of the deleted node, there are two cases:

1.  $x$ is the right child of $y$. Then $y$'s initial $\mathrm{dist}$ is $x$'s initial $\mathrm{dist}$ plus one.
2.  $x$ is the left child of $y$. Since a node's $\mathrm{dist}$ decreases by at most one, the recursion continues only if $y$'s left and right children had equal initial $\mathrm{dist}$ (in which case decreasing the left child's $\mathrm{dist}$ by one causes the children to swap). So $y$'s initial $\mathrm{dist}$ is still $x$'s initial $\mathrm{dist}$ plus one.

So each level of recursion increases $x$'s initial $\mathrm{dist}$ by one, and the recursion goes at most $O(\log n)$ levels deep.

### Adding/subtracting a value to the whole heap, or multiplying it by a positive number

In fact, any operation that can be done with a tag and does not change relative order works.

Put a tag on the root, and push the tag down when deleting the root or merging heaps (that is, when visiting children):

???+ note "Implementation"
    ```cpp
    int merge(int x, int y) {
      if (!x || !y) return x | y;
      if (t[x].val > t[y].val) swap(x, y);
      pushdown(x);
      t[x].rs = merge(t[x].rs, y);
      if (t[t[x].rs].d > t[t[x].ls].d) swap(t[x].ls, t[x].rs);
      t[x].d = t[t[x].rs].d + 1;
      return x;
    }
    
    int pop(int x) {
      pushdown(x);
      return merge(t[x].ls, t[x].rs);
    }
    ```

## Other mergeable heaps

### Randomized heap

???+ note "Implementation"
    ```cpp
    int merge(int x, int y) {
      if (!x || !y) return x | y;
      if (t[y].val < t[x].val) swap(x, y);
      if (rand() & 1)  // Randomly decide whether to swap the children
        swap(t[x].ls, t[x].rs);
      t[x].ls = merge(t[x].ls, y);
      return x;
    }
    ```

As you can see, the only difference in this implementation is that it uses random numbers for merging, which saves all the $\mathrm{dist}$ calculations. The average time complexity is also $O(\log n)$. For a detailed proof, see [Randomized Heap](https://cp-algorithms.com/data_structures/randomized_heap.html).

### Skew heap

A skew heap is a self-adjusting form of the leftist heap. When merging two heaps, it unconditionally swaps the children of every node on the merge path, in an attempt to stay balanced. By amortized analysis, insert, merge, and delete-min on a top-down skew heap cost $O(\log n)$[^ref1].

## Example problems

### Template problems

[Luogu P3377 [Template] Leftist Heap (Mergeable Heap)](https://www.luogu.com.cn/problem/P3377)

[Monkey King](https://www.luogu.com.cn/problem/P1456)

[Roman Game](https://www.luogu.com.cn/problem/P2713)

Things to watch out for:

1.  Before merging, check whether the two nodes are already in the same heap.

2.  The depth of a leftist heap can reach $O(n)$, so finding the top of the heap containing a node must be done with a DSU. You cannot just brute-force jump up through parents. (Although in many problems the test data is weak and brute-force jumping passes...) (When using a DSU to maintain the roots, make sure the old root points to the new root and the new root points to itself.)

??? note "Reference code for Roman Game"
    ```cpp
    --8<-- "docs/ds/code/leftist-tree/leftist-tree_1.cpp"
    ```

### Problems on trees

[APIO2012 Dispatching](https://www.luogu.com.cn/problem/P1552)

[JLOI2015 Capturing Cities](https://loj.ac/problem/2107)

In this kind of problem, each node usually keeps a heap, merges it with its children's heaps, and then pops, updates, and computes the answer as the problem requires. It is somewhat like problems solved by segment tree merging.

??? note "Reference code for Capturing Cities"
    ```cpp
    --8<-- "docs/ds/code/leftist-tree/leftist-tree_2.cpp"
    ```

### [SCOI2011 Tricky Operations](https://loj.ac/problem/2441)

First, finding the top of the heap containing a node must use a DSU, not brute-force jumping up.

Next, consider single-point queries. If tags are placed in the usual way, we have to sum the tags along the path from the point to the root, which can cost $O(n)$ in the worst case. If only the heap top had a tag, queries would be fast. But how do we achieve that?

We can use something like small-to-large merging. Each time we merge, brute-force push the tag of the smaller heap down to each of its nodes, and use the larger heap's tag as the tag of the merged heap. Since the merged heap carries the other heap's tag, when pushing down the smaller heap's tag, push down its tag minus the other heap's tag. Each time a node is merged, the size of its heap at least doubles, so each node receives pushed-down tags at most $O(\log n)$ times, and the total cost of brute-force pushing tags is $O(n\log n)$.

Next, for single-point addition: delete the node, update it, then insert it back.

Then for the global maximum, we can use a balanced binary search tree / a heap that supports deleting arbitrary nodes (such as a leftist heap) / a multiset to maintain the tops of all heaps.

So the operations are:

1.  Brute-force push down the tag of the heap with fewer nodes, merge the two heaps, update size and tag, and remove from the multiset whichever old heap top is no longer the top after merging.
2.  Delete the node, update its value, insert it back, and update the multiset. You need to handle separately whether the deleted node is the root.
3.  Put a tag on the heap top and update the multiset.
4.  Add to the global tag.
5.  Query the value + heap-top tag + global tag.
6.  Query the root's value + heap-top tag + global tag.
7.  Query the multiset maximum + global tag.

??? note "Reference code for Tricky Operations"
    ```cpp
    --8<-- "docs/ds/code/leftist-tree/leftist-tree_3.cpp"
    ```

### [BOI2004 Sequence](https://www.luogu.com.cn/problem/P4331)

This problem comes from a paper. See [Huang Yuanhe - Features and Applications of Leftist Trees](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2005%E8%AE%BA%E6%96%87%E9%9B%86/%E9%BB%84%E6%BA%90%E6%B2%B3--%E5%B7%A6%E5%81%8F%E6%A0%91%E7%9A%84%E7%89%B9%E7%82%B9%E5%8F%8A%E5%85%B6%E5%BA%94%E7%94%A8/%E9%BB%84%E6%BA%90%E6%B2%B3.pdf) for details.

## References

[^ref1]: [Self-Adjusting Heaps](https://epubs.siam.org/doi/10.1137/0215004)
