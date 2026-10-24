author: sshwy, zhouyuyang2002, StudyingFather, Ir1d, ouuan, Enter-tainer, AtomAlpaca

## Introduction

A Cartesian tree is a binary tree in which each node holds a key pair $(k,w)$. The $k$ values must satisfy the binary search tree (BST) property, and the $w$ values must satisfy the heap property. If the keys $k,w$ of a Cartesian tree are fixed, all $k$ are distinct, and all $w$ are distinct, then the structure of the Cartesian tree is unique. See the figure below:

![eg](./images/cartesian-tree1.png)

(Image from Wikipedia)

The Cartesian tree above takes the array values as the keys $w$ and the array indices as the keys $k$. We can see that the keys $k$ satisfy the BST property and the keys $w$ satisfy the min-heap property. Also, by the binary search tree property, in this special kind of Cartesian tree the indices inside any subtree form a contiguous range.

When Cartesian trees are used in contests, the array index is usually taken as the key $k$ of the pair, and the array indices $k$ satisfy the BST property.

Below, when we write $k,w$, we assume that $k$ satisfies the BST property and $w$ satisfies the heap property.

## Building a Cartesian tree with a monotonic stack

### Process

We insert the elements into the current Cartesian tree one by one in increasing order of $k$.

For a Cartesian tree, define the "right chain" as the chain formed by starting at the root and repeatedly going to the right child until we reach a node with no right child. After a node is inserted, it must be on the right chain. Since we insert in increasing order of $k$, which satisfies the BST property, the newly inserted node must be at the **rightmost end** of the tree. This node cannot be a left child, and it has no right child.

So we do the following: compare the $w$ of the nodes on the right chain with that of the current node $u$, from bottom to top. If we find a node $x$ on the right chain with $w_x<w_u$, we attach $u$ as the right child of $x$, and the original right subtree of $x$ becomes the left subtree of $u$.

The part in the red box is the right chain that we keep maintaining:

![build](./images/cartesian-tree2.png)

Clearly each number enters and leaves the right chain at most once (in other words, each node stays on the right chain for one continuous period of time). This process can be maintained with a monotonic stack, which holds the nodes on the right chain of the current Cartesian tree. When a node is no longer on the right chain, pop it. Each node is pushed and popped at most once, so the complexity is $O(n)$.

???+ note "Cartesian trees and Treaps"
    In fact, a Treap is a kind of Cartesian tree, except that its $w$ values are completely random. Treaps have a linear-time construction: if the keys $k$ are sorted beforehand, the monotonic stack algorithm above can build it. It's just rarely used this way.

### C++ implementation

```cpp
// stk stores the sequence indices of the nodes in the Cartesian tree
for (int i = 1; i <= n; i++) {
  int k = top;  // top is the stack top before the operation, k is the current stack top
  while (k > 0 && w[stk[k]] > w[i]) k--;  // maintain the nodes on the right chain
  if (k) rs[stk[k]] = i;  // top element's right child := current element
  if (k < top) ls[i] = stk[k + 1];  // current element's left child := last popped element
  stk[++k] = i;                     // push the current element
  top = k;
}
```

## Example problem

???+ note "[HDU 1506. Largest Rectangle in a Histogram](https://acm.hdu.edu.cn/showproblem.php?pid=1506)"
    There are $n$ positions, and the height at each position is $h_i$. Find the largest rectangle. See the figure below:
    
    ![eg](./images/cartesian-tree3.png)
    
    The shaded area is the largest rectangle in the figure.

??? note "Solution idea"
    Specifically, we take the index as key $k$ and $h_i$ as key $w$ satisfying the min-heap property, and build a Cartesian tree of $(i,h_i)$.
    
    Then we enumerate each node $u$ and take $w_u$ (the height $h$ of node $u$) as the height of the rectangle. Since our Cartesian tree satisfies the min-heap property, every node in the subtree of $u$ has height at least that of $u$. We also know that the indices in the subtree of $u$ form a contiguous range. So we only need the size of the subtree to compute the area of the largest rectangle over this range. Update the answer with the value computed at every node. Clearly this can be done with one DFS, so the complexity is $O(n)$.

??? note "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/cartesian-tree/cartesian-tree_1.cpp"
    ```

## References

[Cartesian tree - Wikipedia](https://zh.wikipedia.org/wiki/%E7%AC%9B%E5%8D%A1%E5%B0%94%E6%A0%91)
