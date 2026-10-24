The AA tree is a balanced tree structure for storing and looking up ordered data efficiently. Professor Arne Andersson introduced it in 1993 in his paper "Balanced search trees made simple". It was designed to reduce the number of different cases that a red-black tree has to handle. An AA tree supports search, insertion and deletion in $O(\log N)$ time. Below is an example of an AA tree.

![aa-tree-1](images/aa-tree-1.jpg)

The AA tree is a variant of the red-black tree. Unlike a red-black tree, a red node in an AA tree can only be a right child. As a result, the AA tree simulates a 2-3 tree instead of a 2-3-4 tree, which greatly simplifies maintenance. The maintenance algorithm of a red-black tree has to handle seven different cases to balance the tree correctly.

![red-black tree](images/aa-tree-2.svg)

Because red nodes can only be right children, an AA tree only needs to handle two cases.

![aa-tree](images/aa-tree-3.svg)

## Definition

An AA tree follows the same rules as a red-black tree, plus one new rule: **a red node cannot be a left child**.

1.  Every node is either red or black.
2.  The root is always black.
3.  Leaf nodes (NULL) are always black.
4.  Both children of a red node must be black, that is, no two adjacent nodes are red.
5.  Every path from the root to a NULL node contains the same number of black nodes.
6.  A red node can only be a right child.

## Keeping balance

Each node of an AA tree stores a **level** field, just as each node of a red-black tree stores a color field ("RED" or "BLACK"). The levels satisfy the following 5 conditions:

1\. The level of every leaf node is 1.

2\. The level of every left child is its parent's level minus 1.

3\. The level of every right child is equal to its parent's level, or its parent's level minus 1.

4\. The level of every right grandchild is strictly less than the level of its grandparent.

5\. Every node with level greater than 1 has two children.

![aa-tree-4](images/aa-tree-4.jpg)

### Horizontal link

A link where the child's level equals the parent's level is called a **horizontal link**, similar to a red link in a red-black tree. A single right horizontal link is allowed, but two consecutive right horizontal links are not, and left horizontal links are not allowed at all. These restrictions are stricter than those of a red-black tree, so balancing an AA tree is much simpler to program than balancing a red-black tree.

![aa-tree-5](images/aa-tree-5.jpg)

Insertion and deletion may temporarily make an AA tree unbalanced (that is, break the AA tree invariants). Restoring balance needs only two different operations: "**skew**" and "**split**". "Skew" is a right rotation that replaces a subtree containing a left horizontal link with one containing a right horizontal link instead. "Split" is a left rotation plus a level increase, which replaces a subtree containing two or more consecutive right horizontal links with one containing two fewer consecutive right horizontal links. Insertion and deletion with balancing become simpler because they rely on "skew" and "split" to change the tree only when needed, instead of having the caller decide whether to skew or split.

### split (left rotation)

This happens when there is a chain of consecutive rightward horizontal links (three consecutive right children are on the same level, and nodes R and X are both red).

In this case, rotate node *T* to the left, treating the nodes with level at most this level as one subtree.

1.  The right child of the subtree's root becomes the new root of the subtree;
2.  The old root of the subtree becomes the left child of the new root;
3.  The level of the new root increases by 1.

![aa-tree-split](images/aa-tree-split.svg)

???+ note "Pseudocode"
    $$
    \begin{array}{ll}
    1 & \textbf{function } \text{split}(\text{root}) \\
    2 & \qquad \textbf{if } \text{root}\rightarrow\text{right}\rightarrow\text{right}\rightarrow\text{level} == \text{root}\rightarrow\text{level} \\
    3 & \qquad\qquad \text{rotate\_left}(\text{root}) \\
    4 & \textbf{end function}
    \end{array}
    $$

### skew (right rotation)

This happens when there is a leftward horizontal link (two consecutive left children are on the same level).

Rotate node *T* to the right, treating the nodes with level at most this level as one subtree.

1.  The left child of the subtree's root becomes the new root of the subtree;
2.  The old root of the subtree becomes the right child of the new root.

![aa-tree-skew](images/aa-tree-skew.svg)

???+ note "Pseudocode"
    $$
    \begin{array}{ll}
    1 & \textbf{function } \text{skew}(\text{root}) \\
    2 & \qquad \textbf{if } \text{root}\rightarrow\text{left}\rightarrow\text{level} == \text{root}\rightarrow\text{level} \\
    3 & \qquad\qquad \text{rotate\_right}(\text{root}) \\
    4 & \textbf{end function}
    \end{array}
    $$

## AA tree operations

An AA tree is itself a binary search tree, so search works the same way as in any other binary search tree. Insertion and deletion work like in an *AVL* tree: first insert or delete the key in the tree, then walk back up the search path to the root, restructuring the tree along the way.

### Insertion

???+ note "Pseudocode"
    $$
    \begin{array}{ll}
    1 & \textbf{function } \text{insert}(\text{root}, \text{add}) \\
    2 & \qquad \textbf{if } \text{root} == \text{NULL} \\
    3 & \qquad\qquad \text{root} \gets \text{add} \\
    4 & \qquad \textbf{else if } \text{add}\rightarrow\text{key} < \text{root}\rightarrow\text{key} \qquad \text{//use <= if duplicates are allowed} \\ 
    5 & \qquad\qquad \text{insert}(\text{root}\rightarrow\text{left}, \text{add}) \\
    6 & \qquad \textbf{else if } \text{add}\rightarrow\text{key} > \text{root}\rightarrow\text{key} \\
    7 & \qquad\qquad \text{insert}(\text{root}\rightarrow\text{right}, \text{add}) \\
    8 & \qquad \textbf{end if} \\
    9 & \qquad \text{//if duplicates are not allowed, skew and split on each level} \\
    10 & \qquad \text{skew}(\text{root}); \\
    11 & \qquad \text{split}(\text{root}); \\
    12 & \textbf{end function}
    \end{array}
    $$

### Deletion

Deletion works like in other balanced binary trees. First, turn the deletion of an internal node into the deletion of a leaf. To do this, replace the internal node with its closest predecessor or successor. Since every node with level greater than 1 in an AA tree has two children, the predecessor or successor is on level 1, and deleting a node on level 1 is simple.

???+ note "Pseudocode"
    $$
    \begin{array}{ll}
    1 &  \text{//To rebalance the tree} \\
    2 &  \textbf{if} \ \text{root->left->level} < \text{root->level} -1 \ \textbf{or} \ \text{root->right->level} < \text{root->level} -1 \\
    3 &  \{ \\
    4 & \qquad \textbf{if} \ \text{root->right->level} > \text{--root->level} \\
    5 & \qquad \{ \\
    6 & \qquad\qquad \text{root->right->level} \gets \text{root->level} \\
    7 & \qquad \} \\
    8 & \qquad \text{skew}(\text{root}) \\
    9 & \qquad \text{skew}(\text{root->right}) \\
    10 & \qquad \text{skew}(\text{root->right->right}) \\
    11 & \qquad \text{split}(\text{root}) \\
    12 & \qquad \text{split}(\text{root->right}) \\
    13 &  \} \\
    \end{array}
    $$

## Performance

The performance of an AA tree is about the same as that of a red-black tree. An AA tree does more rotations than a red-black tree, but its algorithms are simpler, so the overall performance ends up similar. A red-black tree performs more consistently across different situations, while an AA tree tends to be flatter, which makes searching in an AA tree slightly faster.

## References

1.  [AA tree - Wikipedia](https://en.wikipedia.org/wiki/AA_tree)
2.  [Introduction to AA trees](https://iq.opengenus.org/aa-trees/)
3.  [AA tree - Visualization](https://kubokovac.eu/gnarley-trees/AAtree.html)
4.  [CMSC 420 Lecture 6: 2-3, Red-black, and AA trees](https://www.cs.umd.edu/class/fall2019/cmsc420-0201/Lects/lect06-aa.pdf)
