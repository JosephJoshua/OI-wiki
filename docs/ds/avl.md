The AVL tree is a balanced binary search tree. Many algorithm textbooks introduce AVL trees at great length, which leaves many people with the impression that AVL trees are complicated and impractical. In fact, the idea behind an AVL tree is simple, and the implementation is not hard either.

## Properties

1.  An empty binary tree is an AVL tree
2.  If T is an AVL tree, then its left and right subtrees are also AVL trees, and $|h(ls) - h(rs)| \leq 1$, where h is the height of the left/right subtree
3.  The height of the tree is $O(\log n)$

Balance factor: height of the right subtree - height of the left subtree

???+ note "Proof of the tree height"
    Let $f_n$ be the minimum number of nodes in an AVL tree of height $n$. Then
    
    $$
    f_n=
    \begin{cases}
    1&(n=1)\\
    2&(n=2)\\
    f_{n-1}+f_{n-2}+1& (n>2)
    \end{cases}
    $$
    
    By the method for solving non-homogeneous linear difference equations with constant coefficients, $\{f_n+1\}$ is a Fibonacci sequence. The closed form of $f_n$ is:
    
    $$
    f_n=\frac{5+2\sqrt{5}}{5}\left(\frac{1+\sqrt{5}}{2}\right)^n+\frac{5-2\sqrt{5}}{5}\left(\frac{1-\sqrt{5}}{2}\right)^n-1
    $$
    
    The Fibonacci sequence grows exponentially, so for tree height $n$ we have:
    
    $$
    n<\log_{\frac{1+\sqrt{5}}{2}} (f_n+1)<\frac{3}{2}\log_2 (f_n+1)
    $$
    
    So the height of an AVL tree is $O(\log f_n)$, where $f_n$ is the number of nodes.

## Process

### Inserting a node

As in a BST (binary search tree), first do an unsuccessful search to find where to insert. After inserting the node, use the balance factors to decide whether the tree needs to be adjusted.

### Deleting a node

Deletion works like in a BST: swap the node with its successor, then delete it.

Deletion can change tree heights and balance factors. We then fix these changes along the path from the deleted node to the root.

### Keeping balance

After inserting or deleting a node, property 2 of the AVL tree may be broken. So we need to fix the tree along the path from the inserted/deleted node to the root. Suppose property 2 no longer holds at some node. Since we only inserted/deleted one node, the height changes by at most 1, so the absolute value of that node's balance factor is at most 2. By symmetry, we only discuss the case where the left subtree is 2 higher than the right subtree, that is, $h(B)-h(E)=2$ in the figure below. We then split into two cases depending on how $h(A)$ compares with $h(C)$. Note that since we restore balance from the bottom up, property 2 still holds for all descendants of node D.

![](./images/avl1.svg)

#### Case 1: the height of A is not less than the height of C

Let $h(E)=x$. Then

$$
\begin{cases}
    h(B)=x+2\\
    h(A)=x+1\\
    x\leq h(C)\leq x+1
\end{cases}
$$

Here $h(C)\geq x$ holds because node B satisfies property 2, so $h(C)$ and $h(A)$ differ by at most 1. Now we do a right rotation at node D (rotations work the same as in other kinds of balanced binary search trees), as shown below.

![](./images/avl2.svg)

Clearly the heights of nodes A, C and E do not change, and

$$
\begin{cases}
    0\leq h(C)-h(E)\leq 1\\
    x+1\leq h'(D)=\max(h(C),h(E))+1=h(C)+1\leq x+2\\
    0\leq h'(D)-h(A)\leq 1
\end{cases}
$$

So after the rotation, nodes B and D also satisfy property 2.

#### Case 2: the height of A is less than the height of C

Let $h(E)=x$. By the same reasoning as before,

$$
\begin{cases}
    h(B)=x+2\\
    h(C)=x+1\\
    h(A)=x
\end{cases}
$$

Now we first do a left rotation at node B, then a right rotation at node D, as shown below.

![](./images/avl3.svg)

Clearly the heights of nodes A and E do not change. The new right child of B and the new left child of D are the old left and right children of C, respectively. So

$$
\begin{cases}
    x-1\leq h'(rs_B),h'(ls_D)\leq x\\
    0\leq h(A)-h'(rs_B)\leq 1\\
    0\leq h(E)-h'(ls_D)\leq 1\\
    h'(B)=\max(h(A),h'(rs_B))+1=x+1\\
    h'(D)=\max(h(E),h'(ls_D))+1=x+1\\
    h'(B)-h'(D)=0
\end{cases}
$$

So after the rotations, nodes B, C and D also satisfy property 2.

???+ note "Keeping balance: pseudocode"
    $$
    \begin{array}{ll}
    1 &  \textbf{function } \mathrm{MaintainBalance}(p) \\
    2 &  \qquad l \gets ls_p, r \gets rs_p \\
    3 &  \qquad \textbf{if } h(l)-h(r)=2 \\
    4 &  \qquad\qquad \textbf{if } h(ls_l) \ge h(rs_l) \\
    5 &  \qquad\qquad\qquad \mathrm{RightRotate}(p) \\
    6 &  \qquad\qquad \textbf{else} \\
    7 &  \qquad\qquad\qquad \mathrm{LeftRotate}(l) \\
    8 &  \qquad\qquad\qquad \mathrm{RightRotate}(p) \\
    9 &  \qquad \textbf{else if } h(l)-h(r)=-2 \\
    10 &  \qquad\qquad \textbf{if } h(ls_r) \le h(rs_r) \\
    11 &  \qquad\qquad\qquad \mathrm{LeftRotate}(p) \\
    12 &  \qquad\qquad \textbf{else} \\
    13 &  \qquad\qquad\qquad \mathrm{RightRotate}(r) \\
    14 &  \qquad\qquad\qquad \mathrm{LeftRotate}(p) \\
    \end{array}
    $$

As in other balanced binary search trees, information such as node heights and subtree sizes in an AVL tree must be updated during rotations.

## Other operations

Other AVL tree operations (Predecessor, Successor, Select, Rank, etc.) are the same as in an ordinary binary search tree.

## Reference code

The code below implements a `Map` with an AVL tree, that is, an ordered map with unique keys:

??? note "Reference code"
    ```cpp
    --8<-- "docs/ds/code/avl-tree/AvlTreeMap.hpp"
    ```

## Further reading

You can watch how an AVL tree keeps itself balanced at [AVL Tree Visualization](https://www.cs.usfca.edu/~galles/visualization/AVLtree.html).

[Wikipedia -- AVL tree](https://en.wikipedia.org/wiki/AVL_tree)
