author: Dev-XYS, ttzytt, Sora233, qwqAutomaton

Prerequisites: [basic binary search trees](./bst.md), [heap basics](./heap.md).

## Introduction

A treap (tree + heap) is a **weakly balanced** **binary search tree**.

Besides the **value** ($\textit{val}$) that it stores, each treap node also has a random **priority** ($\textit{priority}$). The values satisfy the binary search tree property, and the priorities satisfy the heap property (min-heap or max-heap).

The binary search tree property means:

-   Every node in the left subtree has a smaller value ($\textit{val}$) than the parent.
-   Every node in the right subtree has a larger value ($\textit{val}$) than the parent.

The heap property means:

-   A child's priority ($\textit{priority}$) is larger or smaller than its parent's (depending on whether it is a min-heap or a max-heap).

It is easy to see that if both properties used the same value, combining the two structures would just give a chain. So on top of the search tree we add a separate value for the heap, $\textit{priority}$. We maintain the search tree property for $\textit{val}$ and the heap property for $\textit{priority}$. The $\textit{priority}$ value is chosen at random.

The figure below shows an example of a treap (it uses a min-heap, so the root has the smallest priority).

![An example of a treap](./images/treap-treap-example.svg)

So why go to all this trouble to make the structure satisfy both the tree and heap properties, and to pick the heap values at random?

To understand this, first look at the problem with a basic binary search tree. To insert a new node into a basic search tree, we recurse from the root: if the new node is smaller than the current node, go left; otherwise go right.

When we reach a node with no child in that direction, the new node becomes its left or right child, depending on its value.

If the inserted values are random (in other words, the nodes are inserted in random order), the basic search tree has a small height (close to $\log n$, where $n$ is the number of nodes) and many nodes on each level, so it looks very "bushy". The treap in the figure above is an example. In this case every operation takes about $O(\log n)$.

However, that is only the complexity in the random case. If we insert nodes into a basic search tree in this very ordered sequence:

```plain
1 2 3 4 5
```

then the tree degenerates into a chain and becomes very "tall and thin" (each new node is larger than all previous ones, so it always becomes a right child):

![An example of degenerating into a chain](./images/treap-search-tree-chain.svg)

Clearly, the query complexity also goes from $O(\log n)$ to $O(n)$.

To solve this problem and reach a fairly "balanced" state, a treap keeps random priorities that satisfy the heap property. This "shuffles" the insertion order of the nodes, so the binary search tree reaches the ideal complexity and does not degenerate into a chain.

## Proof of the treap's complexity

The cost of every treap operation depends on the depth of the nodes involved, so we first prove that every node has expected depth $O(\log n)$.

### Notation

For convenience, we use the following notation:

-   $n$ is the number of nodes.
-   In a treap node, the key that satisfies the binary search tree property is called the **value**, and the key that satisfies the heap property (the random one) is called the **priority**. Assume the priorities satisfy the min-heap property.
-   $x_k$ is the node with the $k$-th smallest value.
-   $X_{i,j}$ is the set $\{x_i,x_{i+1},\cdots,x_{j-1},x_j\}$, i.e., the set of the $i$-th through $j$-th nodes when sorted by value in ascending order.
-   $\operatorname{dep}(x)$ is the depth of node $x$. The root has depth $0$.
-   $Y_{i,j}$ is an indicator random variable: it is $1$ when $x_i$ is an ancestor of $x_j$, and $0$ otherwise. In particular, $Y_{i,i}=0$.
-   $\Pr(A)$ is the probability that event $A$ happens.

### Proof of the expected node depth

The depth of node $x_i$ equals the number of its ancestors, so

$$
\operatorname{dep}(x_i)=\sum_{k=1}^nY_{k,i}.
$$

By linearity of expectation,

$$
E(\operatorname{dep}(x_i))=E\left(\sum_{k=1}^nY_{k,i}\right)=\sum_{k=1}^nE(Y_{k,i}).
$$

Since $Y_{k,i}$ is an indicator random variable, its expected value equals the probability that it is $1$, so

$$
E(\operatorname{dep}(x_i))=\sum_{k=1}^n\Pr(Y_{k,i}=1).
$$

First we prove a lemma: $Y_{i,j}=1$ if and only if $x_i$ has the smallest priority in $X_{i,j}$.

??? note "Proof of the lemma"
    Consider the cases for $x_i$ and $x_j$.
    
    1.  If $x_i$ is the root: since the priorities form a min-heap, $x_i$ has the smallest priority, and $x_i$ is an ancestor of every $x_j$.
    2.  If $x_j$ is the root: similarly, $x_j$ has the smallest priority, so $x_i$ does not have the smallest priority in $X_{i,j}$; also, $x_i$ is not an ancestor of $x_j$.
    3.  If $x_i$ and $x_j$ are in the two different subtrees of the root (one left, one right), then the root $r\in X_{i,j}$. So $x_i$ cannot have the smallest priority in $X_{i,j}$ (the root's priority is smaller). Also, since $x_i$ and $x_j$ are in different subtrees, $x_i$ is not an ancestor of $x_j$.
    4.  If $x_i$ and $x_j$ are in the same subtree of the root, take that subtree on its own as a new treap and apply the argument above recursively.

By the lemma, the expected depth becomes

$$
E(\operatorname{dep}(x_i))=\sum_{k=1}^n\Pr(x_k=\min X_{i,k}\land k\neq i).
$$

Since the priorities are random, we assume every node in $X_{i,j}$ is equally likely to have the smallest priority. Then

$$
\begin{aligned}
E(\operatorname{dep}(x_i))&=\sum_{k=1}^n\Pr(x_k=\min X_{i,k}\land k\neq i)\\
&=\sum_{k=1}^{n}\Pr(x_k=\min X_{i,k})-1\\
&=\sum_{k=1}^n\dfrac{1}{|i-k|+1}-1\\
&=\sum_{k=1}^{i-1}\dfrac{1}{i-k+1}+\sum_{k=i+1}^n\dfrac{1}{k-i+1}\\
&=\sum_{j=2}^i\dfrac 1j+\sum_{j=2}^{n-i+1}\dfrac 1j\\
&\le 2\sum_{j=2}^n\dfrac 1j < 2\sum_{j=2}^n\int_{j-1}^j\dfrac 1x\mathrm dx\\
&=2\int_1^n\dfrac 1x\mathrm dx=2\ln n=O(\log n).
\end{aligned}
$$

So every node has expected depth $O(\log n)$.

Every operation on a basic binary search tree costs $O(h)$, and maintaining the heap property in a treap also costs $O(h)$. So every treap operation has expected complexity $O(\log n)$.

???+ note "An intuitive view of the expected complexity"
    First, note that a node's $\textit{priority}$ is directly related to its level in the tree. Recall the heap property:
    
    -   A child's value ($\textit{priority}$) is larger or smaller than its parent's (depending on whether it is a min-heap or a max-heap)
    
    We see that nodes on low levels, such as the root of the whole tree, have smaller $\textit{priority}$ (in a min-heap). Also, in a basic search tree, nodes inserted earlier are more likely to be on lower levels. So we can think of $\textit{priority}$ as being tied to the insertion order. This explains why a treap can use $\textit{priority}$ to shuffle the insertion order of the nodes.

When inserting a new node into a treap, we must maintain both the tree property and the heap property. The search tree property can be kept during insertion. For the heap property there are two approaches: rotation, or split and merge. Treaps using these two approaches are called **rotating treaps** and **non-rotating treaps**, respectively.

## Rotating treap

A **rotating treap** keeps itself balanced by rotations. Like the rotations in an AVL tree, there are **left rotations** and **right rotations**. That is, while keeping the binary search tree property, we rebalance the treap according to the heap priorities.

For standard balanced-tree problems, the rotating treap has one of the smallest constant factors among all balanced trees.

The code in the explanation below implements a rotating treap with pointers. A complete array-based implementation is given at the end of the page.

???+ info "Info"
    In the code, `rank` stands for the priority described above (the $\textit{priority}$ attribute), and it satisfies the min-heap property.

### Node structure

```cpp
struct Node {
  Node *ch[2];  // addresses of the two children
  int val, rank;
  int rep_cnt;  // number of times the current value (val) appears
  int siz;      // size of the subtree rooted at this node

  Node(int val) : val(val), rep_cnt(1), siz(1) {
    ch[0] = ch[1] = nullptr;
    rank = rand();
    // note that rank is chosen at random on initialization
  }

  void upd_siz() {
    // recompute siz after a rotation or deletion
    siz = rep_cnt;
    if (ch[0] != nullptr) siz += ch[0]->siz;
    if (ch[1] != nullptr) siz += ch[1]->siz;
  }
};
```

### Rotation

Rotation is a very important treap operation. It changes the levels of nodes while keeping the search tree property, so that the heap property can be maintained.

Left and right rotations can be hard to tell apart. Here are two fairly clear features:

What a rotation does:

-   Without breaking the search tree property, it makes the subtree on the side opposite to the rotation direction the new root (for a left rotation, the right subtree becomes the root)
-   It does not break the property, and after the rotation, the child on the same side as the rotation direction is the old root (for a left rotation, the left child after rotating is the root before rotating)

Left and right rotations are inverses of each other, as shown below.

![Rotation](./images/treap-rotate.svg)

```cpp
enum rot_type { LF = 1, RT = 0 };

void _rotate(Node *&cur,
             rot_type dir) {  // dir is the rotation direction: 0 = right, 1 = left
  // note that cur is passed as a reference to a pointer, so changing
  // cur changes the variable itself; if cur is a child of another node, then
  // following ch from that node also leads here

  // the comments below all describe the left-rotation case
  Node *tmp = cur->ch[dir];  // make C the root;
                             // tmp here
                             // is a temporary node pointer to the node that becomes the new root

  /* left rotation: make the right child the root
   *         A                 C
   *        / \               / \
   *       B  C    ---->     A   E
   *         / \            / \
   *        D   E          B   D
   */
  cur->ch[dir] = tmp->ch[!dir];    // make D the right child of A
  tmp->ch[!dir] = cur;             // make A the left child of C
  cur->upd_siz(), tmp->upd_siz();  // update size info
  cur = tmp;  // finally assign the temporary C to the current root (cur is a reference)
}
```

### Insertion

This is like insertion in a basic binary search tree, but during insertion we use rotations to keep the heap property of the priorities.

```cpp
void _insert(Node *&cur, int val) {
  if (cur == nullptr) {
    // no such node: create it directly
    cur = new Node(val);
    return;
  } else if (val == cur->val) {
    // a node with the same value exists: increase its count by one
    cur->rep_cnt++;
    cur->siz++;
  } else if (val < cur->val) {
    // keep the search tree property: smaller val goes left, larger goes right
    _insert(cur->ch[0], val);
    if (cur->ch[0]->rank < cur->rank) {
      // in a min-heap, the upper node must have the smaller priority
      // the new left child is smaller than its parent, so it must become the parent
      _rotate(cur, RT);  // by the rotation rules above, bringing up the left child needs a right rotation
    }
    cur->upd_siz();  // the size changes after insertion and must be updated
  } else {
    _insert(cur->ch[1], val);
    if (cur->ch[1]->rank < cur->rank) {
      _rotate(cur, LF);
    }
    cur->upd_siz();
  }
}
```

### Deletion

This is mainly case analysis: different cases are handled differently. The tree size changes after deletion, so remember to update it. If the node to delete has both a left and a right subtree, we must decide which one becomes the parent after deletion (keep the node with the smaller rank on top).

```cpp
void _del(Node *&cur, int val) {
  if (val > cur->val) {
    _del(cur->ch[1], val);
    // a larger value is in the right subtree, and vice versa
    cur->upd_siz();
  } else if (val < cur->val) {
    _del(cur->ch[0], val);
    cur->upd_siz();
  } else {
    if (cur->rep_cnt > 1) {
      // if the node to delete has duplicates, just decrease the count
      cur->rep_cnt--, cur->siz--;
      return;
    }
    uint8_t state = 0;
    state |= (cur->ch[0] != nullptr);
    state |= ((cur->ch[1] != nullptr) << 1);
    // 00 neither, 01 left only, 10 right only, 11 both
    Node *tmp = cur;
    switch (state) {
      case 0:
        delete cur;
        cur = nullptr;
        // no children: just delete this node
        break;
      case 1:  // left only
        cur = tmp->ch[0];
        // make the left child the root, then delete the old root; note tmp is
        // a copy of cur, while cur is a reference
        delete tmp;
        break;
      case 2:  // right only
        cur = tmp->ch[1];
        delete tmp;
        break;
      case 3:
        rot_type dir = cur->ch[0]->rank < cur->ch[1]->rank
                           ? RT
                           : LF;  // dir is the child with the smaller rank
        _rotate(cur, dir);  // this rotation brings up the child with smaller priority; RT is 0
                            // and LF is 1, exactly the reverse of the actual child index
        _del(
            cur->ch[!dir],
            val);  // after rotating, the old root is on the rotation side, so we
                   // keep deleting that old root
                   // if the node to delete is "high up" in the tree, we keep
                   // rotating it down until it has no subtrees (or only one), then delete it.
        cur->upd_siz();
        // deletion changes the size
        break;
    }
  }
}
```

### Finding the rank of a value

What it does: in the subtree rooted at cur, find the rank of the value val (the number of nodes in the subtree smaller than val, plus 1)

```cpp
int _query_rank(Node *cur, int val) {
  int less_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
  // number of nodes in this tree smaller than val
  if (val == cur->val)
    // this node is the one we are looking for
    return less_siz + 1;
  else if (val < cur->val) {
    if (cur->ch[0] != nullptr)
      return _query_rank(cur->ch[0], val);
    else
      return 1;  // the left subtree is empty, so val is smaller than the smallest node: it is the smallest
  } else {
    if (cur->ch[1] != nullptr)
      // if val is larger than this node, the left subtree and this node are all smaller than val
      // so add these two counts, plus the result from searching the right side
      // (the rank of val within the subtree rooted at the right child)
      return less_siz + cur->rep_cnt + _query_rank(cur->ch[1], val);
    else
      return cur->siz + 1;
    // with no right subtree, it is the whole tree + 1, i.e. less_siz + cur->rep_cnt + 1
  }
}
```

### Finding the value with a given rank

To find the value with a given rank, we first need to know which part of the tree the target node is in:

Here is a table for deciding:

| Left subtree         | Root / current node                           | Right subtree                    |
| ----------- | ---------------------------------- | ---------------------- |
| rank ≤ size of left subtree | rank > size of left subtree, and ≤ size of left subtree + count of root | rank > size of left subtree + count of root |

Note that if it is in the right subtree, we must adjust the original `rank` when recursing. Recursing means looking for the value with this rank inside the right subtree. To convert the rank so that it is relative to the right subtree, subtract the size of the left subtree and the count of the root from the original `rank`.

You can imagine all nodes as a sorted array, or a number line (as below):

    1 -> |left subtree nodes|root|right subtree nodes| -> n
                               ^
                               rank we want
                         ⬇ convert to a rank in the right subtree
    1 -> |right subtree nodes| -> n
           ^
           rank we want

The conversion simply subtracts the size of the left subtree and the count of the root from the rank.

```cpp
int _query_val(Node *cur, int rank) {
  // find the value of the node with rank `rank` in the tree
  int less_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
  // less_siz is the size of the left subtree
  if (rank <= less_siz)
    return _query_val(cur->ch[0], rank);
  else if (rank <= less_siz + cur->rep_cnt)
    return cur->val;
  else
    return _query_val(cur->ch[1], rank - less_siz - cur->rep_cnt);  // see above
}
```

### Finding the first node smaller than val

Note that this uses a class member variable, `q_prev_tmp`.

This variable is only changed when val is larger than the current node's value. So returning it returns the last node whose value was smaller than val; after that, the nodes visited were larger.

```cpp
int _query_prev(Node *cur, int val) {
  if (val <= cur->val) {
    // still not smaller than val, so search the left subtree
    if (cur->ch[0] != nullptr) return _query_prev(cur->ch[0], val);
  } else {
    // q_prev_tmp is only updated when we enter this else branch
    q_prev_tmp = cur->val;
    // the current node is already smaller than val, but may not be the largest such node, so keep searching the right subtree
    if (cur->ch[1] != nullptr) _query_prev(cur->ch[1], val);
    // the following recursion may not change q_prev_tmp
    // again, so just return this value; in any case we return the cur->val from the last time we
    // entered this else branch
    return q_prev_tmp;
  }
  return NIL;
}
```

### Finding the first node larger than val

This is very similar to the previous one; only the comparison signs are swapped.

```cpp
int _query_nex(Node *cur, int val) {
  if (val >= cur->val) {
    if (cur->ch[1] != nullptr) return _query_nex(cur->ch[1], val);
  } else {
    q_nex_tmp = cur->val;
    if (cur->ch[0] != nullptr) _query_nex(cur->ch[0], val);
    return q_nex_tmp;
  }
  return NIL;
}
```

## Non-rotating treap

The way a non-rotating treap works makes it naturally support maintaining sequences, persistence, and similar features.

A **non-rotating treap** is also called a split-merge treap. It has only two core operations: **split** and **merge**. With these two operations, many other operations are often easier to implement than in a rotating treap. We introduce the two operations one by one below.

???+ note "Note"
    Any discussion of the non-rotating treap should mention **FHQ-Treap** (by Fan Haoqiang), a non-rotating treap that supports persistence and range operations. For more, see the slides "Fan Haoqiang on Data Structures".

### Split

#### Split by value

The split procedure takes two arguments: the root pointer $\textit{cur}$ and a key $\textit{key}$. It splits the treap pointed to by the root into two treaps: every node in the first treap has value ($\textit{val}$) less than or equal to $\textit{key}$, and every node in the second treap has value greater than $\textit{key}$.

The procedure first checks whether $\textit{key}$ is less than the value of $\textit{cur}$. If so, $\textit{cur}$ and its whole right subtree are greater than $\textit{key}$ and belong to the second treap. Of course, part of the left subtree may also be greater than $\textit{key}$, so we keep splitting the left subtree recursively. We make the part of the left subtree that is greater than $\textit{key}$ the left subtree of $\textit{cur}$. Then every node under $\textit{cur}$ is greater than $\textit{key}$.

Similarly, if $\textit{key}$ is greater than or equal to the value of $\textit{cur}$, then the whole left subtree of $\textit{cur}$ and $\textit{cur}$ itself are less than or equal to $\textit{key}$, and belong to the first treap after the split. Part of the right subtree of $\textit{cur}$ may also be less than or equal to $\textit{key}$, so we keep splitting the right subtree recursively. We make the part that is less than or equal to $\textit{key}$ the right subtree of $\textit{cur}$. Then every node under $\textit{cur}$ is less than or equal to $\textit{key}$.

The figure below shows a split by value when the value of $\textit{cur}$ is less than or equal to $\textit{key}$.[^ref1]

![Split by value](./images/treap-none-rot-split-by-val.svg)

```cpp
pair<Node *, Node *> split(Node *cur, int key) {
  if (cur == nullptr) return {nullptr, nullptr};
  if (cur->val <= key) {
    // cur and its left subtree must belong to the first tree after the split
    auto temp = split(cur->ch[1], key);
    // but part of its right subtree may also be smaller than key
    cur->ch[1] = temp.first;
    // take out the part not greater than key and make it cur's right subtree, so all of cur is not greater than
    // key; the rest of the right subtree becomes the second treap after the split
    cur->upd_siz();
    // the tree size changes after a split and must be updated
    return {cur, temp.second};
  } else {
    // same as above
    auto temp = split(cur->ch[0], key);
    cur->ch[0] = temp.second;
    cur->upd_siz();
    return {temp.first, cur};
  }
}
```

#### Split by rank

Compared with splitting by value, this operation is more like finding a value by rank in a rotating treap (the rank of a node is the number of nodes in the tree with a smaller value, $+ 1$):

This function takes two arguments, a node pointer $\textit{cur}$ and a rank $\textit{rk}$, and returns the three treaps after the split.

Every node in the first treap has rank less than $\textit{rk}$. The second treap has rank equal to $\textit{rk}$ and contains only one node (there cannot be several equal ones; duplicates increase `cnt` in the `Node` struct). The third has ranks greater than $\textit{rk}$.

The key point of this operation is deciding which part of the tree contains the node whose rank equals $\textit{rk}$. This is also the key part of finding a value by rank in a rotating treap, which is explained in detail above, so we do not repeat it here.

The recursive part of this operation is also very similar to splitting by value, so we skip the details.

```cpp
tuple<Node *, Node *, Node *> split_by_rk(Node *cur, int rk) {
  if (cur == nullptr) return {nullptr, nullptr, nullptr};
  int ls_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
  if (rk <= ls_siz) {
    // the node with rank rk is in the left subtree
    Node *l, *mid, *r;
    tie(l, mid, r) = split_by_rk(cur->ch[0], rk);
    cur->ch[0] = r;  // all ranks in the third returned treap are greater than rk
    // after cur's left subtree is set to r, every node under cur has rank greater than rk
    cur->upd_siz();
    return {l, mid, cur};
  } else if (rk <= ls_siz + cur->cnt) {
    // the current node is the one with rank rk
    Node *lt = cur->ch[0];
    Node *rt = cur->ch[1];
    cur->ch[0] = cur->ch[1] = nullptr;
    // the second treap after the split has only one node, so set its subtrees to empty
    return {lt, cur, rt};
  } else {
    // the node with rank rk is in the right subtree
    // the recursion is the same as above
    Node *l, *mid, *r;
    tie(l, mid, r) = split_by_rk(cur->ch[1], rk - ls_siz - cur->cnt);
    cur->ch[1] = l;
    cur->upd_siz();
    return {cur, mid, r};
  }
}
```

### Merge

The merge procedure takes two arguments: the root pointer $\textit{u}$ of the left treap and the root pointer $\textit{v}$ of the right treap. Every node value in $\textit{u}$ must be less than or equal to every node value in $\textit{v}$. Usually the two treaps we merge were split from a single treap earlier, so it is easy to guarantee that every value in $\textit{u}$ is less than those in $\textit{v}$.

In a rotating treap, we use rotations to keep $\textit{priority}$ satisfying the heap property, without breaking the tree property. In a non-rotating treap, we use merge to achieve the same effect.

Since the two treaps are already in order, when merging we only need to decide which tree goes "on top" and which goes "below", i.e., which tree becomes a subtree. Clearly, by the heap property, the one with the smaller $\textit{priority}$ goes on top (we use a min-heap here).

We also need the search tree property. So if the root of $\textit{u}$ has smaller $\textit{priority}$ than the root of $\textit{v}$, then $\textit{u}$ becomes the new root, and since $\textit{v}$ has larger values than $\textit{u}$, it is merged with the right subtree of $\textit{u}$. Otherwise, $\textit{v}$ becomes the new root, and since $u$ has smaller values than $\textit{v}$, it is merged with the left subtree of $v$.

```cpp
Node *merge(Node *u, Node *v) {
  // each of the two trees passed in already satisfies the search tree property
  // and every value in u < every value in v
  // so when merging we need to maintain the heap property
  // a min-heap is used here
  if (u == nullptr && v == nullptr) return nullptr;
  if (u != nullptr && v == nullptr) return u;
  if (v != nullptr && u == nullptr) return v;

  if (u->prio < v->prio) {
    // u has the smaller prio, so u should be the parent
    u->ch[1] = merge(u->ch[1], v);
    // v is larger than u, so v becomes part of u's right subtree
    u->upd_siz();
    return u;
  } else {
    // v is smaller, so v should be the parent
    v->ch[0] = merge(u, v->ch[0]);
    // u is smaller than v, hence the argument order in the recursion
    v->upd_siz();
    return v;
  }
}
```

### Insertion

In a non-rotating treap, basic operations such as insertion, deletion and finding the rank of a value can be done either with the usual binary search tree methods or with split and merge. Split and merge usually give shorter code, but are a bit slower[^ref2]. To help you understand the non-rotating treap better, all operations below are implemented with split and merge.

To implement insertion, we use a property of split: nodes with value less than or equal to $\textit{val}$ go into the first treap.

So suppose we split the current treap by $\textit{val}$. We get two trees satisfying:

$$
\begin{aligned}
T_1 &\le val\\
T_2 &> val
\end{aligned}
$$

Here $T_1$ is the set of nodes that went into the first treap after the split, and $T_2$ is the second.

If we then split $T_1$ by $\textit{val} - 1$, we get two trees satisfying:

$$
\begin{gathered}
T_{1\ \text{left}} \le val - 1\\
T_{1\ \text{right}} > val - 1 \ \And \ T_{1\ \text{right}} \le val
\end{gathered}
$$

Here $T_{1\ \text{left}}$ is the set of nodes of $T_1$ that went into the first treap after the split, and $T_{1\ \text{right}}$ is the second. In the formula above, the second half $\And \ T_{1\ \text{right}} \le val$ comes from the condition $T_1 \le val$ that $T_1$ satisfies.

It is easy to see that as long as $\textit{val}$ and the node values are integers (which is the case in most uses), only one node can satisfy the condition for $T_{1\ \text{right}}$: the node whose value equals $\textit{val}$.

When inserting, if a node in $T_{1\ \text{right}}$ exists, we just increase its count; otherwise we create a new node.

Note that after splitting the tree, we need to "glue" it back with merge, so that it can be used next time. Also note that merge requires a specific argument order: every value in the first tree must be less than those in the second.

```cpp
void insert(int val) {
  auto temp = split(root, val);
  // split the whole tree into two by val
  // note that in the split implementation, nodes equal to val go to the left subtree
  auto l_tr = split(temp.first, val - 1);
  // the left part of l_tr is <= val - 1; if a node equal to val exists, it must be in the right part
  Node *new_node;
  if (l_tr.second == nullptr) {
    // if there is no such node, create one; otherwise just increase the count.
    new_node = new Node(val);
  } else {
    l_tr.second->cnt++;
    l_tr.second->upd_siz();
  }
  Node *l_tr_combined =
      merge(l_tr.first, l_tr.second == nullptr ? new_node : l_tr.second);
  // merge T_1 left and T_1 right
  root = merge(l_tr_combined, temp.second);
  // merge T_1 and T_2
}
```

### Deletion

Deletion uses a method similar to insertion: find the node whose value equals $\textit{val}$ and delete it.

```cpp
void del(int val) {
  auto temp = split(root, val);
  auto l_tr = split(temp.first, val - 1);
  if (l_tr.second->cnt > 1) {
    // if this node appears more than once, just decrease the count
    l_tr.second->cnt--;
    l_tr.second->upd_siz();
    l_tr.first = merge(l_tr.first, l_tr.second);
  } else {
    if (temp.first == l_tr.second) {
      // T_1 might consist of this node alone, so also set it to null to mark it as deleted
      temp.first = nullptr;
    }
    delete l_tr.second;
    l_tr.second = nullptr;
  }
  root = merge(l_tr.first, temp.second);
}
```

### Finding the rank of a value

The rank is the number of nodes with a smaller value, $+ 1$. So we split the current tree by $\textit{val} - 1$, and the first tree after the split satisfies:

$$
T_1 \le val - 1
$$

If the tree values and $\textit{val}$ are integers, $T_1$ contains exactly the nodes with value less than $\textit{val}$.

```cpp
int qrank_by_val(Node* cur, int val) {
  auto temp = split(cur, val - 1);
  int ret = (temp.first == nullptr ? 0 : temp.first->siz) + 1;  // + 1 by definition
  root = merge(temp.first, temp.second);  // glue it back after splitting
  return ret;
}
```

### Finding the value with a given rank

`split_by_rk()` returns the three treaps after the split. The second contains only one node, whose rank equals $\textit{rk}$, so we just return that node's $\textit{val}$.

```cpp
int qval_by_rank(Node *cur, int rk) {
  Node *l, *mid, *r;
  tie(l, mid, r) = split_by_rk(cur, rk);
  int ret = mid->val;
  root = merge(merge(l, mid), r);
  return ret;
}
```

### Finding the first node smaller than val

We can turn this into: among all nodes smaller than $\textit{val}$, find the one with the largest rank. We split the treap by $\textit{val}$, so every node in the first returned treap is smaller than $\textit{val}$. Then we call `qval_by_rank()` to find the node with the largest value in that tree.

```cpp
int qprev(int val) {
  auto temp = split(root, val - 1);
  // temp.first is the subtree of values smaller than val
  int ret = qval_by_rank(temp.first, temp.first->siz);
  // this finds the value of the largest node among all nodes smaller than val
  root = merge(temp.first, temp.second);
  return ret;
}
```

### Finding the first node larger than val

Like the previous operation, we can turn this into: among all nodes larger than $\textit{val}$, find the one with the smallest rank. After splitting by $\textit{val}$, every node in the second returned treap is larger than $\textit{val}$.

Then we look up the value of the node with rank $1$ in that tree (the node with the smallest value), which is the first node larger than $\textit{val}$.

```cpp
int qnex(int val) {
  auto temp = split(root, val);
  int ret = qval_by_rank(temp.second, 1);
  // find the smallest value in the subtree of values larger than val
  root = merge(temp.first, temp.second);
  return ret;
}
```

### Building the tree

Turn a sequence $\{a_n\}$ of $n$ nodes into a treap.

We can insert the $n$ nodes one by one by brute force. Each time we insert a node with value $v$, we split the whole treap by value into the part with values at most $v$ and the part with values greater than $v$, create a new node with value $v$, and merge the two parts and the new node in increasing order. Each insertion takes $O(\log n)$ time, so the total time complexity is $O(n\log n)$.

Some problems may insert a sorted sequence many times. Then we need to build the tree in $O(n)$ time.

Method 1: when building recursively, always pick the midpoint of the current range as the root for that range, and assign each node a suitable priority so that the new tree satisfies the heap property. This guarantees a tree height of $O(\log n)$.

Method 2: when building recursively, always pick the midpoint of the current range as the root for that range, then give each node a random priority. This guarantees a tree height of $O(\log n)$, but does not guarantee the heap property. This is still correct, because in a non-rotating treap the priorities are used to make `merge` more random, not to guarantee the tree height.

Method 3: note that a treap is a Cartesian tree, so we can use the $O(n)$ Cartesian tree construction, maintaining the right chain with a monotonic stack.

### Range operations on a non-rotating treap

#### Building the tree

A big advantage of the non-rotating treap over the rotating treap is that it supports all kinds of range operations. Below we use the [template problem](https://loj.ac/problem/105) "Literary Balanced Tree" as an example to introduce range operations on a treap.

> You need to write a data structure (see the problem title) to maintain an ordered sequence.
>
> It must support the following operation: reverse a range. For example, if the original sequence is $5\ 4\ 3\ 2\ 1$ and the range to reverse is $[2,4]$, the result is $5\ 2\ 3\ 4\ 1$.
> For $100\%$ of the data, $1 \le n$ (initial sequence length), $m$ (number of reversals) $\le 10^5$

In this problem we need to implement range reversal. First we need to think about how to build the tree: the tree we build must represent the initial sequence.

We just insert the indices of the sequence into the treap in order. Then an in-order traversal (left subtree first, then the current node, then the right subtree) gives back the sequence[^ref3].

We know that if we insert nodes in increasing order into a basic binary search tree, we get a long chain, and its in-order traversal naturally gives the sequence.

<div align=center>
  <img style="width: 50%; " src="../images/treap-search-tree-chain.svg" >
</div>

As shown above, if we insert nodes into a basic search tree in the order $1\ 2\ 3\ 4\ 5$, the in-order traversal also gives $1\ 2\ 3\ 4\ 5$.

But in a treap, after inserting nodes in increasing order, the merge operation also adjusts the tree structure according to $\textit{priority}$. In this case, how can we be sure the in-order traversal still gives the right output?

To understand this, see [building a Cartesian tree with a monotonic stack](./cartesian-tree.md).

Let the newly inserted node be $\textit{u}$.

First, since nodes are inserted in increasing order, every new node is attached to the right chain of the treap (the chain of nodes visited by starting at the root and always going to the right subtree).

Starting from the root, the $\textit{priority}$ values on the right chain are increasing (min-heap). So we can find the first node on the right chain whose $\textit{priority}$ is greater than that of $\textit{u}$; call it $\textit{v}$, and replace it with $\textit{u}$.

Since $\textit{u}$ is greater than every other node in the tree, we make $\textit{v}$ and its subtree the left subtree of $\textit{u}$. At this point $\textit{u}$ has no right subtree.

We can see that $\textit{u}$ is always the last node visited in the in-order traversal (because $\textit{u}$ is the last node on the right chain, and in an in-order traversal the right subtree is visited last).

The figure below shows how a treap changes when node $5$ is inserted while inserting nodes $1 \sim 5$ in increasing order. It helps to understand the process of inserting in increasing order.

![Inserting a node](./images/treap-none-rot-seg-build.svg)

#### Range reversal

To reverse the range $[l, r]$, the basic idea is to split the tree into the three ranges $[1, l - 1],\ [l, r],\ [r + 1, n]$, and then reverse the middle range $[l, r]$[^ref3].

Concretely, reversal swaps the left and right children of every node in the subtree for that range. The figure below shows the treap from the previous figure after reversing the ranges $[3, 4]$ and $[3, 5]$.

![Range reversal](./images/treap-none-rot-seg-flip-ex.svg)

Note that if we reverse this way, each reversal of $[l, r]$ swaps $r - l$ nodes. Doing this so often clearly cannot handle the $10^5$ data range. The $O(n \times \log_2 n)$ cost of a single reversal is even worse than brute force (because besides spending linear time swapping nodes, we also spend $O(\log_2 n)$ time in the tree finding the nodes to swap).

Looking at the problem again, we only need to output the sequence after all operations, so we do not have to actually swap every time. So we can use the lazy tag commonly used in segment trees to improve the complexity. When swapping, we just put a tag on the parent node, meaning that the left and right children of every node in this subtree need to be swapped.

In a segment tree, we usually push down lazy tags during updates and queries. This is because the range we want to update or query may not match the range a lazy tag stands for, so we push the tag down first to make sure the values we read and update are correct.

The same holds in a non-rotating treap. Concretely, we split the treap into the three trees described above, put a lazy tag on the middle tree, and then merge the three trees. Since the range we want to reverse may not match the range a lazy tag stands for, we push tags down during split. Also, split and merge change which nodes each node and its lazy tag cover, so we also push lazy tags down before merging.

In other words, whenever the tree structure changes, i.e., when split or merge is about to change a node's left or right child, we should push the tag down before the change, not after. A lazy tag needs to be passed to the children, but if the children are changed before the tag is pushed down, the tag loses the nodes it was meant for.[^ref4]

<!-- TODO: add a figure explaining why tags must be pushed down during split and merge -->

The code is explained below; it is based on [^ref3].

Most range operations are the same as in an ordinary non-rotating treap, so we only explain the parts that differ.

#### Pushing down tags

Note that the lazy tag here means every child in this tree needs to be swapped. So if a child of the current node also has a lazy tag, the two reversals cancel out. If the child does not need reversing, the lazy tag must be passed further down to it.

```cpp
// pushdown here is a member function of the Node class, and to_rev is the lazy tag
void pushdown() {
  swap(ch[0], ch[1]);
  if (ch[0] != nullptr) ch[0]->to_rev ^= 1;
  if (ch[1] != nullptr) ch[1]->to_rev ^= 1;
  to_rev = false;
}

void check_tag() {
  if (to_rev) pushdown();
}
```

#### Split

Note that in this problem, because of reversals, the $\textit{val}$ values in the treap no longer satisfy the binary search tree property (see the figure in the range reversal part). So we cannot use $\textit{val}$ to decide whether to recurse into the left or the right subtree.

So the split here is more like the split by rank in an ordinary non-rotating treap: it decides whether to go left or right based on subtree sizes. In other words, we decide by the node's position in the tree.

Every node in the first returned treap has rank at most $\textit{sz}$, and every node in the second has rank greater than $\textit{sz}$.

```cpp
#define siz(_) (_ == nullptr ? 0 : _->siz)

pair<Node*, Node*> split(Node* cur, int sz) {
  // decide by tree size
  if (cur == nullptr) return {nullptr, nullptr};
  cur->check_tag();
  // push down before splitting
  if (sz <= siz(cur->ch[0])) {
    auto temp = split(cur->ch[0], sz);
    cur->ch[0] = temp.second;
    cur->upd_siz();
    return {temp.first, cur};
  } else {
    auto temp =
        split(cur->ch[1],
              sz - siz(cur->ch[0]) -
                  1);  // this conversion is explained in "finding the value with a given rank" for the rotating treap
    cur->ch[1] = temp.first;
    cur->upd_siz();
    return {cur, temp.second};
  }
}
```

#### Merge

The only thing to note is to push down lazy tags before merging

```cpp
Node *merge(Node *sm, Node *bg) {
  // small, big
  if (sm == nullptr && bg == nullptr) return nullptr;
  if (sm != nullptr && bg == nullptr) return sm;
  if (sm == nullptr && bg != nullptr) return bg;
  sm->check_tag(), bg->check_tag();
  if (sm->prio < bg->prio) {
    sm->ch[1] = merge(sm->ch[1], bg);
    sm->upd_siz();
    return sm;
  } else {
    bg->ch[0] = merge(sm, bg->ch[0]);
    bg->upd_siz();
    return bg;
  }
}
```

#### Range reversal

As described above, split out the three ranges $[1, l - 1],\ [l, r],\ [r + 1, n]$, put a tag on the middle range, and merge them back.

```cpp
void seg_rev(int l, int r) {
  // less and more here are relative to l
  auto less = split(root, l - 1);
  // everything at positions <= l - 1 goes into the left part, less.first
  auto more = split(less.second, r - l + 1);
  // the range of the first r - l + 1 elements starting from l
  more.first->to_rev = true;
  root = merge(less.first, merge(more.first, more.second));
}
```

#### Printing by in-order traversal

Remember to push down tags while printing.

```cpp
void print(Node* cur) {
  if (cur == nullptr) return;
  cur->check_tag();
  // in-order traversal -> left subtree first, then the node itself, then the right subtree
  print(cur->ch[0]);
  cout << cur->val << " ";
  print(cur->ch[1]);
}
```

## Complete code

### Rotating treap

#### Pointer implementation

??? note "Complete code"
    Below is the complete version of the code explained above. It is template code for the standard balanced tree problem.
    
    ```cpp
    // author: (ttzytt)[ttzytt.com]
    #include <cstdint>
    #include <cstdio>
    #include <cstdlib>
    using namespace std;
    
    struct Node {
      Node *ch[2];
      int val, rank;
      int rep_cnt;
      int siz;
    
      Node(int val) : val(val), rep_cnt(1), siz(1) {
        ch[0] = ch[1] = nullptr;
        rank = rand();
      }
    
      void upd_siz() {
        siz = rep_cnt;
        if (ch[0] != nullptr) siz += ch[0]->siz;
        if (ch[1] != nullptr) siz += ch[1]->siz;
      }
    };
    
    class Treap {
     private:
      Node *root;
    
      constexpr static int NIL = -1;  // means the queried value does not exist
    
      enum rot_type { LF = 1, RT = 0 };
    
      int q_prev_tmp = 0, q_nex_tmp = 0;
    
      void _rotate(Node *&cur, rot_type dir) {  // 0 = right rotation, 1 = left rotation
        Node *tmp = cur->ch[dir];
        cur->ch[dir] = tmp->ch[!dir];
        tmp->ch[!dir] = cur;
        cur->upd_siz(), tmp->upd_siz();
        cur = tmp;
      }
    
      void _insert(Node *&cur, int val) {
        if (cur == nullptr) {
          cur = new Node(val);
          return;
        } else if (val == cur->val) {
          cur->rep_cnt++;
          cur->siz++;
        } else if (val < cur->val) {
          _insert(cur->ch[0], val);
          if (cur->ch[0]->rank < cur->rank) {
            _rotate(cur, RT);
          }
          cur->upd_siz();
        } else {
          _insert(cur->ch[1], val);
          if (cur->ch[1]->rank < cur->rank) {
            _rotate(cur, LF);
          }
          cur->upd_siz();
        }
      }
    
      void _del(Node *&cur, int val) {
        if (val > cur->val) {
          _del(cur->ch[1], val);
          cur->upd_siz();
        } else if (val < cur->val) {
          _del(cur->ch[0], val);
          cur->upd_siz();
        } else {
          if (cur->rep_cnt > 1) {
            cur->rep_cnt--, cur->siz--;
            return;
          }
          uint8_t state = 0;
          state |= (cur->ch[0] != nullptr);
          state |= ((cur->ch[1] != nullptr) << 1);
          // 00 neither, 01 left only, 10 right only, 11 both
          Node *tmp = cur;
          switch (state) {
            case 0:
              delete cur;
              cur = nullptr;
              break;
            case 1:  // left only
              cur = tmp->ch[0];
              delete tmp;
              break;
            case 2:  // right only
              cur = tmp->ch[1];
              delete tmp;
              break;
            case 3:
              rot_type dir = cur->ch[0]->rank < cur->ch[1]->rank ? RT : LF;
              _rotate(cur, dir);
              _del(cur->ch[!dir], val);
              cur->upd_siz();
              break;
          }
        }
      }
    
      int _query_rank(Node *cur, int val) {
        int less_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
        if (val == cur->val)
          return less_siz + 1;
        else if (val < cur->val) {
          if (cur->ch[0] != nullptr)
            return _query_rank(cur->ch[0], val);
          else
            return 1;
        } else {
          if (cur->ch[1] != nullptr)
            return less_siz + cur->rep_cnt + _query_rank(cur->ch[1], val);
          else
            return cur->siz + 1;
        }
      }
    
      int _query_val(Node *cur, int rank) {
        int less_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
        if (rank <= less_siz)
          return _query_val(cur->ch[0], rank);
        else if (rank <= less_siz + cur->rep_cnt)
          return cur->val;
        else
          return _query_val(cur->ch[1], rank - less_siz - cur->rep_cnt);
      }
    
      int _query_prev(Node *cur, int val) {
        if (val <= cur->val) {
          if (cur->ch[0] != nullptr) return _query_prev(cur->ch[0], val);
        } else {
          q_prev_tmp = cur->val;
          if (cur->ch[1] != nullptr) _query_prev(cur->ch[1], val);
          return q_prev_tmp;
        }
        return NIL;
      }
    
      int _query_nex(Node *cur, int val) {
        if (val >= cur->val) {
          if (cur->ch[1] != nullptr) return _query_nex(cur->ch[1], val);
        } else {
          q_nex_tmp = cur->val;
          if (cur->ch[0] != nullptr) _query_nex(cur->ch[0], val);
          return q_nex_tmp;
        }
        return NIL;
      }
    
     public:
      void insert(int val) { _insert(root, val); }
    
      void del(int val) { _del(root, val); }
    
      int query_rank(int val) { return _query_rank(root, val); }
    
      int query_val(int rank) { return _query_val(root, rank); }
    
      int query_prev(int val) { return _query_prev(root, val); }
    
      int query_nex(int val) { return _query_nex(root, val); }
    };
    
    Treap tr;
    
    int main() {
      srand(0);
      int t;
      scanf("%d", &t);
      while (t--) {
        int mode;
        int num;
        scanf("%d%d", &mode, &num);
        switch (mode) {
          case 1:
            tr.insert(num);
            break;
          case 2:
            tr.del(num);
            break;
          case 3:
            printf("%d\n", tr.query_rank(num));
            break;
          case 4:
            printf("%d\n", tr.query_val(num));
            break;
          case 5:
            printf("%d\n", tr.query_prev(num));
            break;
          case 6:
            printf("%d\n", tr.query_nex(num));
            break;
        }
      }
    }
    ```

#### Array implementation

Below is template code for the BZOJ standard balanced tree problem, implemented with arrays.

??? note "Complete code"
    ```cpp
    --8<-- "docs/ds/code/treap/treap_1.cpp"
    ```

### Non-rotating treap

#### Pointer implementation

??? note "Complete code"
    Below is the complete version of the code explained above. It is template code for the standard balanced tree problem.
    
    ```cpp
    
    // author: (ttzytt)[ttzytt.com]
    #include <cstdio>
    #include <cstdlib>
    #include <ctime>
    #include <tuple>
    using namespace std;
    
    struct Node {
      Node *ch[2];
      int val, prio;
      int cnt;
      int siz;
    
      Node(int _val) : val(_val), cnt(1), siz(1) {
        ch[0] = ch[1] = nullptr;
        prio = rand();
      }
    
      Node(Node *_node) {
        val = _node->val, prio = _node->prio, cnt = _node->cnt, siz = _node->siz;
      }
    
      void upd_siz() {
        siz = cnt;
        if (ch[0] != nullptr) siz += ch[0]->siz;
        if (ch[1] != nullptr) siz += ch[1]->siz;
      }
    };
    
    struct none_rot_treap {
    #define _3 second.second
    #define _2 second.first
      Node *root;
    
      pair<Node *, Node *> split(Node *cur, int key) {
        if (cur == nullptr) return {nullptr, nullptr};
        if (cur->val <= key) {
          auto temp = split(cur->ch[1], key);
          cur->ch[1] = temp.first;
          cur->upd_siz();
          return {cur, temp.second};
        } else {
          auto temp = split(cur->ch[0], key);
          cur->ch[0] = temp.second;
          cur->upd_siz();
          return {temp.first, cur};
        }
      }
    
      tuple<Node *, Node *, Node *> split_by_rk(Node *cur, int rk) {
        if (cur == nullptr) return {nullptr, nullptr, nullptr};
        int ls_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
        if (rk <= ls_siz) {
          Node *l, *mid, *r;
          tie(l, mid, r) = split_by_rk(cur->ch[0], rk);
          cur->ch[0] = r;
          cur->upd_siz();
          return {l, mid, cur};
        } else if (rk <= ls_siz + cur->cnt) {
          Node *lt = cur->ch[0];
          Node *rt = cur->ch[1];
          cur->ch[0] = cur->ch[1] = nullptr;
          return {lt, cur, rt};
        } else {
          Node *l, *mid, *r;
          tie(l, mid, r) = split_by_rk(cur->ch[1], rk - ls_siz - cur->cnt);
          cur->ch[1] = l;
          cur->upd_siz();
          return {cur, mid, r};
        }
      }
    
      Node *merge(Node *u, Node *v) {
        if (u == nullptr && v == nullptr) return nullptr;
        if (u != nullptr && v == nullptr) return u;
        if (v != nullptr && u == nullptr) return v;
        if (u->prio < v->prio) {
          u->ch[1] = merge(u->ch[1], v);
          u->upd_siz();
          return u;
        } else {
          v->ch[0] = merge(u, v->ch[0]);
          v->upd_siz();
          return v;
        }
      }
    
      void insert(int val) {
        auto temp = split(root, val);
        auto l_tr = split(temp.first, val - 1);
        Node *new_node;
        if (l_tr.second == nullptr) {
          new_node = new Node(val);
        } else {
          l_tr.second->cnt++;
          l_tr.second->upd_siz();
        }
        Node *l_tr_combined =
            merge(l_tr.first, l_tr.second == nullptr ? new_node : l_tr.second);
        root = merge(l_tr_combined, temp.second);
      }
    
      void del(int val) {
        auto temp = split(root, val);
        auto l_tr = split(temp.first, val - 1);
        if (l_tr.second->cnt > 1) {
          l_tr.second->cnt--;
          l_tr.second->upd_siz();
          l_tr.first = merge(l_tr.first, l_tr.second);
        } else {
          if (temp.first == l_tr.second) {
            temp.first = nullptr;
          }
          delete l_tr.second;
          l_tr.second = nullptr;
        }
        root = merge(l_tr.first, temp.second);
      }
    
      int qrank_by_val(Node *cur, int val) {
        auto temp = split(cur, val - 1);
        int ret = (temp.first == nullptr ? 0 : temp.first->siz) + 1;
        root = merge(temp.first, temp.second);
        return ret;
      }
    
      int qval_by_rank(Node *cur, int rk) {
        Node *l, *mid, *r;
        tie(l, mid, r) = split_by_rk(cur, rk);
        int ret = mid->val;
        root = merge(merge(l, mid), r);
        return ret;
      }
    
      int qprev(int val) {
        auto temp = split(root, val - 1);
        int ret = qval_by_rank(temp.first, temp.first->siz);
        root = merge(temp.first, temp.second);
        return ret;
      }
    
      int qnex(int val) {
        auto temp = split(root, val);
        int ret = qval_by_rank(temp.second, 1);
        root = merge(temp.first, temp.second);
        return ret;
      }
    };
    
    none_rot_treap tr;
    
    int main() {
      srand(time(nullptr));
      int t;
      scanf("%d", &t);
      while (t--) {
        int mode;
        int num;
        scanf("%d%d", &mode, &num);
        switch (mode) {
          case 1:
            tr.insert(num);
            break;
          case 2:
            tr.del(num);
            break;
          case 3:
            printf("%d\n", tr.qrank_by_val(tr.root, num));
            break;
          case 4:
            printf("%d\n", tr.qval_by_rank(tr.root, num));
            break;
          case 5:
            printf("%d\n", tr.qprev(num));
            break;
          case 6:
            printf("%d\n", tr.qnex(num));
            break;
        }
      }
    }
    ```

### Range operations on a non-rotating treap

#### Pointer implementation

??? note "Complete code"
    Below is the complete version of the code explained above. It is template code for the "Literary Balanced Tree" problem.
    
    ```cpp
    
    // author: (ttzytt)[ttzytt.com]
    #include <cstdlib>
    #include <ctime>
    #include <iostream>
    using namespace std;
    
    // Reference: https://www.cnblogs.com/Equinox-Flower/p/10785292.html
    struct Node {
      Node* ch[2];
      int val, prio;
      int cnt;
      int siz;
      bool to_rev = false;  // every node in this subtree needs to be flipped
    
      Node(int _val) : val(_val), cnt(1), siz(1) {
        ch[0] = ch[1] = nullptr;
        prio = rand();
      }
    
      int upd_siz() {
        siz = cnt;
        if (ch[0] != nullptr) siz += ch[0]->siz;
        if (ch[1] != nullptr) siz += ch[1]->siz;
        return siz;
      }
    
      void pushdown() {
        swap(ch[0], ch[1]);
        if (ch[0] != nullptr) ch[0]->to_rev ^= 1;
        // if the child also needs flipping, the two flips cancel out; if the child does not, this
        //  tag must be pushed further down to the child
        if (ch[1] != nullptr) ch[1]->to_rev ^= 1;
        to_rev = false;
      }
    
      void check_tag() {
        if (to_rev) pushdown();
      }
    };
    
    struct Seg_treap {
      Node* root;
    #define siz(_) (_ == nullptr ? 0 : _->siz)
    
      pair<Node*, Node*> split(Node* cur, int sz) {
        // split by tree size
        if (cur == nullptr) return {nullptr, nullptr};
        cur->check_tag();
        if (sz <= siz(cur->ch[0])) {
          // the left subtree is enough
          auto temp = split(cur->ch[0], sz);
          // not all of the left subtree is needed; temp.second is the unneeded part
          cur->ch[0] = temp.second;
          cur->upd_siz();
          return {temp.first, cur};
        } else {
          // the left side plus part of the right side (including this node itself, of course)
          auto temp = split(cur->ch[1], sz - siz(cur->ch[0]) - 1);
          cur->ch[1] = temp.first;
          cur->upd_siz();
          return {cur, temp.second};
        }
      }
    
      Node* merge(Node* sm, Node* bg) {
        // small, big
        if (sm == nullptr && bg == nullptr) return nullptr;
        if (sm != nullptr && bg == nullptr) return sm;
        if (sm == nullptr && bg != nullptr) return bg;
        sm->check_tag(), bg->check_tag();
        if (sm->prio < bg->prio) {
          sm->ch[1] = merge(sm->ch[1], bg);
          sm->upd_siz();
          return sm;
        } else {
          bg->ch[0] = merge(sm, bg->ch[0]);
          bg->upd_siz();
          return bg;
        }
      }
    
      void insert(int val) {
        auto temp = split(root, val);
        auto l_tr = split(temp.first, val - 1);
        Node* new_node;
        if (l_tr.second == nullptr) new_node = new Node(val);
        Node* l_tr_combined =
            merge(l_tr.first, l_tr.second == nullptr ? new_node : l_tr.second);
        root = merge(l_tr_combined, temp.second);
      }
    
      void seg_rev(int l, int r) {
        // less and more here are relative to l
        auto less = split(root, l - 1);
        // everything at positions <= l - 1 goes to the left part, less.first
        auto more = split(less.second, r - l + 1);
        // take the first r - l + 1 elements starting from l
        more.first->to_rev = true;
        root = merge(less.first, merge(more.first, more.second));
      }
    
      void print(Node* cur) {
        if (cur == nullptr) return;
        cur->check_tag();
        print(cur->ch[0]);
        cout << cur->val << " ";
        print(cur->ch[1]);
      }
    };
    
    Seg_treap tr;
    
    int main() {
      srand(time(nullptr));
      int n, m;
      cin >> n >> m;
      for (int i = 1; i <= n; i++) tr.insert(i);
      while (m--) {
        int l, r;
        cin >> l >> r;
        tr.seg_rev(l, r);
      }
      tr.print(tr.root);
    }
    ```

## Example problems

[Ordinary Balanced Tree](https://loj.ac/problem/104)

[Literary Balanced Tree (Splay)](https://loj.ac/problem/105)

[ZJOI2006 Bookshelf](https://www.luogu.com.cn/problem/P2596)

[NOI2005 Maintaining a Sequence](https://www.luogu.com.cn/problem/P2042)

[CF 702F T-Shirts](http://codeforces.com/problemset/problem/702/F)

## References and notes

[^ref1]: The design of this figure is based on [the figure in the Wikipedia article on treaps](https://en.wikipedia.org/wiki/Treap)

[^ref2]: <https://charleswu.site/archives/1051>

[^ref3]: <https://www.cnblogs.com/Equinox-Flower/p/10785292.html>

[^ref4]: <https://www.luogu.com.cn/blog/85514/fhq-treap-xue-xi-bi-ji>
