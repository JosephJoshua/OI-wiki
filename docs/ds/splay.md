This page gives a short introduction to using a Splay tree to maintain a binary search tree.

## Definition

A **Splay tree** is a balanced binary search tree. It keeps rotating some node up to the root through the **splay operation**, while the whole tree still satisfies the binary search tree property. It supports insertion, lookup and deletion in amortized $O(\log n)$ time.[^degen]

The Splay tree was invented by Daniel Sleator and Robert Tarjan in 1985.

## Basic structure and operations

This section covers the basic structure of a Splay tree and its core operations. The most important one is the splay operation.

A Splay tree is a binary search tree, so every node satisfies: the value of any node in the left subtree $<$ the value of the node $<$ the value of any node in the right subtree.

### Stored information

This page implements the Splay tree with arrays that simulate pointers. We need to store the following:

|   rt  |    id   | fa\[i] | ch\[i]\[0/1] | val\[i] | cnt\[i] | sz\[i] |
| :---: | :-----: | :----: | :----------: | :-----: | :-----: | :----: |
| index of the root | number of nodes used |   parent   |    indices of left and right children    |   value of the node  |  number of times the value occurs |  subtree size  |

At initialization, simply set all of this to zero.

### Helper operations

First, some simple helper operations:

-   `dir(x)`: check whether node $x$ is the left child or the right child of its parent;
-   `push_up(x)`: after a node has moved, update the information of node $x$ from its children.

???+ example "Implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:aux"
    ```

### Rotation

To keep the Splay tree balanced, we need rotations. A rotation moves a node up by one level.

A rotation must make sure that:

-   the in-order traversal of the whole Splay tree does not change (the binary search tree property must not be broken);
-   the information stored in the affected nodes stays correct;
-   `rt` points to the root after the rotation.

There are two kinds of rotation in a Splay tree: left rotation and right rotation.

![](./images/splay-rotate.svg)

From the figure, if we want to move node $x$ up by a rotation ($1$ in the left rotation and $2$ in the right rotation), the direction of the rotation is fully determined by whether that node is the left or the right child of its parent. So when implementing rotation, we only need to pass in the node $x$ that should move up.

Here are the steps of a rotation in detail (let the node to move up be $x$, and take a right rotation as the example):

1.  First, record the parent $y$ of $x$ and the parent $z$ of $y$ (which may be empty), and record whether $x$ is the left or the right child of $y$;
2.  In bottom-up order of the tree after rotation, set the left child of $y$ to the right child of $x$, set the right child of $x$ to $y$, and, if $z$ is not empty, set the child of $z$ to $x$;
3.  In the same order, set the parent of the current left child of $y$ (if it exists) to $y$, set the parent of $y$ to $x$, and set the parent of $x$ to $z$;
4.  Update the node information from the bottom up.

???+ example "Implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:rotate"
    ```

In every function, be careful not to modify the information of node $0$.

### Splay operation

A Splay tree requires that every time a node $x$ is accessed, it must be rotated to the root. This is called the splay operation.

Let $x$ be the node that was just accessed. To splay it, we apply a series of **splay steps** to $x$. Each splay step brings $x$ closer to the root. Let $p$ be the parent of $x$. There are three kinds of splay steps:

1.  **zig**: done when $p$ is the root. The Splay tree rotates on the edge between $x$ and $p$. **zig** handles the parity of the depth: it is only done as the last step of a splay operation, and only when $x$ has odd depth at the start of the splay operation.

    ![splay-zig](./images/splay-zig.svg)

    That is, simply rotate $x$ right or left (Figures 1 and 2).

    ![Figure 1](./images/splay-rotate1.svg)![Figure 2](./images/splay-rotate2.svg)

2.  **zig-zig**: done when $p$ is not the root and $x$ and $p$ are both right children or both left children. The figure below shows the case where $x$ and $p$ are both left children. The Splay tree first rotates on the edge between $p$ and its parent $g$, and then rotates on the edge between $x$ and $p$.

    ![splay-zig-zig](./images/splay-zig-zig.svg)

    That is, first rotate $p$ right or left, then rotate $x$ right or left (Figures 3 and 4).

    ![Figure 3](./images/splay-rotate3.svg)![Figure 4](./images/splay-rotate4.svg)

3.  **zig-zag**: done when $p$ is not the root and one of $x$ and $p$ is a right child while the other is a left child. The Splay tree first rotates on the edge between $p$ and $x$, then rotates on the new edge between $x$ and $g$ created by the first rotation.

    ![splay-zig-zag](./images/splay-zig-zag.svg)

    That is, rotate $x$ left then right, or right then left (Figures 5 and 6).

    ![Figure 5](./images/splay-rotate5.svg)![Figure 6](./images/splay-rotate6.svg)

???+ tip "Tip"
    Try simulating the $6$ rotation cases yourself to understand the basic idea of the splay operation.

Comparing the three splay steps, the key to choosing which one to use is to check whether $x$ is a child of the root, and whether $x$ and its parent are on the same side of their respective parents.

The implementation given here lets you pick any root $z$ and move any node $x$ in its subtree up to the position of $z$:

1.  First record the parent $w$ of the root $z$, so that `fa[x] == w` tells us that $x$ has reached the root position;
2.  Record the current parent $y$ of $x$. If $y$ equals $w$, then $x$ has reached the root;
3.  Otherwise, use `fa[y] == w` to check whether $y$ is the root. If it is, do a zig to rotate $x$; if not, use `dir(x) == dir(y)` to choose between zig-zig and zig-zag. The former rotates $y$ first and then $x$; the latter rotates $x$ twice.

???+ example "Implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:splay"
    ```

The splay operation is the core operation of a Splay tree, and it is the key step that guarantees its time complexity. Always make sure to do a splay operation after every downward access to a node.

Also, the splay operation updates, from the bottom up, the information of all nodes on the path from the current node $x$ to the root $z$. Because of this, you can modify a non-root node and then splay it up to the root to update the information of the whole tree.

### Time complexity

Doing $m$ splay operations on a Splay tree of size $n$ takes $O((m+n)\log n)$ time, so each one costs amortized $O(\log n)$.

??? note "Complexity proof using the potential method"
    We only need to analyze the cost of the three steps **zig**, **zig-zig** and **zig-zag**. To do this, we use the **potential method**, which derives the amortized cost of operations by studying how the potential changes. Suppose we do $m$ splay operations on a Splay tree with $n$ nodes. The analysis goes as follows:
    
    **Definitions**:
    
    1.  **Potential of a single node**: $w(x) = \log(\text{size}(x))$, where $\text{size}(x)$ is the size of the subtree rooted at node $x$.
    2.  **Potential of the whole tree**: $\varphi = \sum w(x)$, the sum of the potentials of all nodes in the tree. The initial potential satisfies $\varphi_0 \leq n \log n$.
    3.  **Amortized cost of the $i$-th operation**: $c_i = t_i + \varphi_i - \varphi_{i-1}$, where $t_i$ is the actual cost of the operation, and $\varphi_i$ and $\varphi_{i-1}$ are the potentials after and before the operation.
    
    **Properties**:
    
    1.  If $p$ is the parent of $x$, then $w(p) \geq w(x)$, i.e. the potential of a parent is at least the potential of its child.
    
    2.  Since the subtree size at the root does not change during an operation, the potential of the root does not change either.
    
    3.  If $\text{size}(p)\ge\text{size}(x)+\text{size}(y)$, then $2w(p) - w(x) - w(y) \geq 2$.
    
    ??? note "Proof of Property 3"
        By the AM–GM inequality,
        
        $$
        \begin{aligned}
        2w(p) - w(x) - w(y) 
        &= \log\dfrac{\text{size}(p)^2}{\text{size}(x)\cdot\text{size}(y)} \\
        &\ge \log\dfrac{\left(\text{size}(x)+\text{size}(y)\right)^2}{\text{size}(x)\cdot\text{size}(y)} \\
        &\ge \log 4 \\
        &= 2.
        \end{aligned}
        $$
    
    Next, we analyze the potential for **zig**, **zig-zig** and **zig-zag** one by one. Let $w(x)$ and $w'(x)$ be the potential of node $x$ before and after the step. The node names are the same as [above](#splay-operation).
    
    **zig**: by Properties 1 and 2, $w(p) = w'(x)$ and $w'(x) \geq w'(p)$. So the amortized cost is
    
    $$
    \begin{aligned}
    c_i &= 1 + w'(x) + w'(p) - w(x) - w(p)\\
    &= 1 + w'(p) - w(x)\\
    &\leq 1 + w'(x) - w(x).
    \end{aligned}
    $$
    
    **zig-zig**: by Properties 1 and 2, $w(g) = w'(x)$, $w'(x) \geq w'(p)$ and $w(x) \leq w(p)$. Since
    
    $$
    \begin{aligned}
    \text{size}'(x) 
    &= 3 + \text{size}(A) + \text{size}(B) + \text{size}(C) + \text{size}(D) \\
    &> (1 + \text{size}(A) + \text{size}(B)) + (1 + \text{size}(C) + \text{size}(D)) \\
    &= \text{size}(x) + \text{size}'(g),
    \end{aligned}
    $$
    
    Property 3 gives
    
    $$
    2 w'(x) - w(x) - w'(g) \geq 2.
    $$
    
    So the amortized cost is
    
    $$
    \begin{aligned}
    c_i &= 2 + w'(x) + w'(p) + w'(g) - w(x) - w(p) - w(g) \\
    &= 2 + w'(p) + w'(g) - w(x) - w(p) \\
    &\le (2 w'(x) - w(x) - w'(g)) + w'(p) + w'(g) - w(x) - w(p) \\
    &= 2(w'(x)-w(x)) + w'(p) - w(p) \\
    &\le 3(w'(x)-w(x)).
    \end{aligned}
    $$
    
    **zig-zag**: by Properties 1 and 2, $w(g) = w'(x)$ and $w(p) \geq w(x)$. Since $\text{size}'(x)>\text{size}'(p)+\text{size}'(g)$, Property 3 gives
    
    $$
    2 \cdot w'(x) - w'(g) - w'(p) \geq 2.
    $$
    
    So the amortized cost is
    
    $$
    \begin{aligned}
    c_i &= 2 + w'(x) + w'(p) + w'(g) - w(x) - w(p) - w(g) \\
    &= 2 + w'(p) + w'(g) - w(x) - w(p) \\
    &\le (2w'(x) - w'(g) - w'(p)) + w'(p) + w'(g) - w(x) - w(p) \\
    &= 2w'(x) - w(x) - w(p) \\
    &\le 2(w'(x) - w(x)).
    \end{aligned}
    $$
    
    **A single splay operation**:
    
    Let $w^{(j)}(x)=(w^{(j-1)})'(x)$ and $w^{(0)}(x)=w(x)$. Suppose one splay operation consists of $k$ splay steps and finally moves node $x_{1}$ up to the root. It must consist of some **zig-zig** and **zig-zag** steps and at most one **zig** step. The amortized cost of each of the first two kinds is at most $3(w'(x)-w(x))$, and the amortized cost of the last step is at most $3(w'(x) - w(x))+1$. So the total amortized cost is at most
    
    $$
    3(w^{(k)}(x_1) - w^{(0)}(x_1)) + 1 \le 3\log n + 1.
    $$
    
    Therefore, one splay operation costs amortized $O(\log n)$. As a result, insertion, lookup, deletion and other operations based on splaying also take amortized $O(\log n)$ time.
    
    **Conclusion**:
    
    After $m$ splay operations, the actual cost is
    
    $$
    \begin{aligned}
    \sum_{i=1}^m t_i &= \sum_{i=1}^m \left(c_i + \varphi_{i-1} - \varphi_i \right) \\
    &= \sum_{i=1}^m c_i + \varphi_0 - \varphi_m \\
    &\le m(3\log n+1) + n\log n.
    \end{aligned}
    $$
    
    Therefore, the actual time complexity of $m$ splay operations is $O((m+n)\log n)$.

??? info "Why does the rebalancing of a Splay tree give amortized $O(\log n)$ complexity?"
    The naive way to rebalance is to keep rotating a node upward until it becomes the root. The problem with this naive idea is that on a chain-shaped tree where every child is a left (or right) child, it is the same as doing **zig** over and over. The constant term $1$ in the amortized cost of **zig** then keeps adding up, and the final amortized cost becomes $O(n)$. The Splay tree's rebalancing is designed to avoid this buildup of constants from consecutive **zig** steps: a full splay operation does at most one standalone **zig** step, and this is what improves the time complexity.

## Balanced tree operations

This section shows how to implement common balanced tree operations with a Splay tree. The most important ones are finding an element by value or by rank. They locate a specific element and move it up to the root for further processing.

As an example, this section discusses how to implement the template problem [Ordinary Balanced Tree](https://loj.ac/problem/104).

### Find by value

Since it is a binary search tree, we can find the node for a value $v$ by comparing $v$ with the value of the current node. Once found, move that element up to the root.

Note that quite often the tree has no node with that value. In this case, record the last node visited ($y$ in the implementation) and move $y$ up to the root. The value stored at $y$ must then be either the largest of all elements smaller than $v$ (the predecessor of $v$), or the smallest of all elements larger than $v$ (the successor of $v$). This is because the search guarantees that the left subtree always stores values smaller than $v$, and the right subtree always stores values larger than $v$.

???+ example "Implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:find"
    ```

This implementation lets you choose any node $z$ as the root and search by value in its subtree.

### Access by rank

Since we store subtree sizes, a Splay tree can also access elements by rank, that is, find the $k$-th smallest element in the tree.

Let $k$ be the remaining rank. The steps are:

-   If the left subtree is not empty and the remaining rank $k$ is at most the size of the left subtree, go into the left subtree;
-   Otherwise, if $k$ is at most the size of the left subtree plus the number of occurrences of the root's value, the root is the answer;
-   Otherwise, subtract the size of the left subtree plus the number of occurrences of the root's value from $k$, and continue in the right subtree;
-   Move the element finally found up to the root.

???+ example "Implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:loc"
    ```

This implementation requires that rank $k$ is at most the size of the tree rooted at $z$.

Operation $4$ of the template problem asks for the value at a given rank. Just call this function and return the value.

???+ example "Implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:find-kth"
    ```

### Merge

Sometimes we need to merge two Splay trees.

Let the roots of the two trees be $x$ and $y$. For the result to still be a binary search tree, the maximum value in tree $x$ must be smaller than the minimum value in tree $y$. This condition usually holds, because the two trees are often split from a larger tree.

The merge works as follows:

-   If one or both of $x$ and $y$ are empty, return the root of the non-empty tree, or an empty tree;
-   Otherwise, use `loc(y, 1)` to move the minimum value of tree $y$ up to the root $y$, then set its left child (which must be empty now) to $x$, update the node information, and return node $y$.

???+ example "Implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:merge"
    ```

Splitting is similar. So a Splay tree can imitate the approach of the [non-rotating treap](./treap.md#non-rotating-treap) to do all kinds of operations, including range operations. [Later](#sequence-operations) we will introduce a way to handle range operations that is more in the style of Splay trees.

### Insertion

Insertion is a fairly involved process. The steps are as follows (let the value to insert be $v$):

-   Just like finding by value, walk down according to $v$ until reaching the node that stores $v$ or an empty node, and record the parent $y$ along the way;
-   If a node $x$ storing $v$ exists, update its information directly; otherwise create a new node $x$;
-   Do a splay operation to move this last node $x$ up to the root.

???+ example "Implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:insert"
    ```

This implementation allows inserting a value directly into an empty tree. If you do not want to deal with empty trees, you can insert dummy nodes into the tree in advance.

### Deletion

Deletion is also a fairly involved operation. The steps are as follows (let the value to delete be $v$):

-   First find the node that stores $v$ by value, and move it up to the root;
-   If no such node exists, return directly (the previous step has already done the splay operation);
-   Otherwise, update the node information;
-   If the number of occurrences of the root's value drops to zero, delete the node: merge the left and right subtrees and make the result the new root. Note that before merging, you must set the parents of the roots of both subtrees to empty.

???+ example "Implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:remove"
    ```

### Query rank

Access the node by value $v$ (and move it up to the root), then return the corresponding rank.

Note that when $v$ does not exist, the root returned by `find(rt, v)` could be either smaller or larger than $v$, so this case must be handled separately.

???+ example "Implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:find-rank"
    ```

### Query predecessor

The predecessor is defined as the largest number smaller than $v$. The steps are:

-   Access the node by value $v$ (and move it up to the root);
-   If the value at the root is smaller than $v$, it must be the largest such value, so return it;
-   Otherwise, find the maximum value in the left subtree and move it up to the root.

The last step is the same as calling `loc(ch[rt][0], sz[ch[rt][0]])`, just without some unnecessary checks.

???+ example "Implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:find-prev"
    ```

This implementation allows the predecessor not to exist, in which case it returns $-1$.

### Query successor

The successor is defined as the smallest number larger than $v$. The query is similar to the predecessor, except that the maximum of the left subtree is replaced by the minimum of the right subtree, i.e. we call `loc(ch[rt][1], 1)`.

???+ example "Implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:find-next"
    ```

### Reference implementation

To end this section, here is a reference implementation for the template problem [Ordinary Balanced Tree](https://loj.ac/problem/104).

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:full-text"
    ```

## Sequence operations

A Splay tree can also be used on sequences to maintain information about ranges. Compared with a segment tree, a Splay tree has a larger constant factor, but it supports more complex sequence operations, such as reversing a range. As mentioned above, a Splay tree also supports split and merge, so it can imitate the [non-rotating treap](./treap.md#non-rotating-treap) to do range operations; we will not go into that here. This section mainly discusses how to implement range operations based on the splay operation.

A Splay tree built from a sequence has the following properties:

-   The in-order traversal of the Splay tree is the left-to-right traversal of the original sequence;
-   Each node of the Splay tree represents one element of the original sequence;
-   Each subtree of the Splay tree represents a contiguous range of the original sequence.

Thanks to the splay operation, we can quickly extract the Splay subtree that represents a given range.

As an example, this section discusses how to implement the template problem [Literary Balanced Tree](https://loj.ac/problem/105).

### Building the tree from a sequence

Before any operation, we first build the Splay tree from the given sequence. Because of how Splay trees work, we can simply build a chain where every node only has a left child. The time complexity is $O(n)$.

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-2.cpp:build"
    ```

The final splay operation updates the node information from the bottom up. To make later range operations easier, two sentinel nodes are added at the left and right ends of the sequence.

### Range reversal

Taking range reversal as an example, we can see how range operations work (let the range be $[L,R]$):

-   First move node $L-1$ up to the root, then, within its right subtree, move node $R+1$ up to the root of the right subtree;
-   Now let $x$ be the left child of the root's right child. The subtree rooted at $x$ corresponds exactly to the range $[L,R]$;
-   Apply the operation on $[L,R]$ at $x$, and put a lazy tag on it;
-   Push the tag down once at $x$, then use the splay operation to move $x$ up to the root.

The first step uses "access by rank" from the balanced tree operations above, since the index of an element is its rank. Because lazy tags have to be managed, its implementation is slightly different from the one above.

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-2.cpp:reverse"
    ```

The splay operation in the last step is not there to guarantee the complexity; it is there to update node information. Because the splay operation touches the left and right children of node $x$, the tag at $x$ must be pushed down once before it. Of course, for range reversal alone, reversing a subrange does not affect the ancestors, so skipping this step is also correct. The implementation keeps these two lines to show how things work in the general case.

### Managing lazy tags

First, we need the helper functions `lazy_reverse(x)` and `push_down(x)`. The former swaps the left and right children and updates the lazy tag; the latter pushes the tag down.

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-2.cpp:push-down"
    ```

Then we only need to push tags down whenever we go down through a node. The template problem only asks for simple operations: only finding by rank (i.e. `loc`) goes down through nodes. Note that the tag must be pushed down **before** the function visits each new node.

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-2.cpp:push-down-lazy"
    ```

Since going down has already cleared all lazy tags along the path, we do not need to handle lazy tags when moving a node up with the splay operation. However, the node where the range operation was applied needs care: it is also on the path of the splay operation, but since it was just operated on, it may have a tag that has not been pushed down yet. That tag must be pushed down before splaying, exactly as done above.

### Reference implementation

To end this section, here is a reference implementation for the template problem [Literary Balanced Tree](https://loj.ac/problem/105).

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-2.cpp:full-text"
    ```

## Exercises

These problems are plain uses of a Splay tree to maintain a binary search tree:

-   [[Template] Ordinary Balanced Tree](https://loj.ac/problem/104)
-   [[Template] Literary Balanced Tree](https://loj.ac/problem/105)
-   ["HNOI2002" Turnover Statistics](https://loj.ac/problem/10143)
-   ["HNOI2004" Pet Adoption Center](https://loj.ac/problem/10144)

Splay trees also appear in more complex applications:

-   ["Cerc2007" Robotic Sort](https://www.luogu.com.cn/problem/P4402)
-   ["HNOI2011" Bracket Repair / "JSOI2011" Bracket Sequence](https://www.luogu.com.cn/problem/P3215)
-   [Second-Rate Balanced Tree (tree of trees)](https://loj.ac/problem/106)
-   [BZOJ 2827 Birds Gone from a Thousand Mountains](https://hydro.ac/p/bzoj-P2827)
-   ["Lydsy1706 Monthly Contest" K-th Smallest Query](https://hydro.ac/p/bzoj-P4923)
-   [POJ3580 SuperMemo](http://poj.org/problem?id=3580)

## References and notes

Parts of this page are taken from the algocode algorithm blog. Special thanks to them!

[^degen]: A Splay tree only guarantees amortized $O(\log n)$ complexity. It does not maintain a balance condition like AVL trees or red-black trees do, and it may even degenerate into a chain after a series of operations. So the worst-case cost of a single operation is $O(n)$.
