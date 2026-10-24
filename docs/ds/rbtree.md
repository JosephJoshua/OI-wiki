author: 0x03A6, abc1763613206, auuuu4, CCXXXI, Conless, Enter-tainer, fanenr, happyZYM, hsfzLZH1, iamtwz, LeverImmy, leverimmy, Lhcfl, Marcythm, RIvance, Tiphereth-A, trudbot, Xeniume, Xeonacid, YBYCS, yuhuoji

A red-black tree is a self-balancing binary search tree. Each node stores an extra color field ("RED" or "BLACK"), which is used to keep the tree balanced during insertions and deletions.

The red-black tree is a variant of the B-tree of order 4 (the [2-3-4 tree](https://en.wikipedia.org/wiki/2%E2%80%933%E2%80%934_tree)).[^gilbas1978]

## Properties

A valid red-black tree must satisfy the following four properties:

1.  Every node is red or black
2.  NIL nodes (empty leaves) are black
3.  The children of a red node are black
4.  Every path from the root to a NIL node contains the same number of black nodes

The figure below shows a valid red-black tree:

![rbtree-example](images/rbtree-example.svg)

???+ note "Note"
    Some sources add a fifth property: the root must be black. This property requires that if the root is red after an insertion, it is recolored black. But since recoloring the root black can also be postponed until a deletion, this property is not strictly necessary (the code in this article does satisfy it). To be rigorous, here is the relevant passage from [Wikipedia](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree#Properties):
    
    > Some authors, e.g. Cormen & al.,[^cite_note-cormen2009-18]claim "the root is black" as fifth requirement; but not Mehlhorn & Sanders[^cite_note-mehlhorn2008-17]or Sedgewick & Wayne.[^cite_note-algs4-16]Since the root can always be changed from red to black, this rule has little effect on analysis. This article also omits it, because it slightly disturbs the recursive algorithms and proofs.

## Definition of the red-black tree class

```cpp
--8<-- "docs/ds/code/rbtree/rbtree.hpp:class-node1"
  // ...
--8<-- "docs/ds/code/rbtree/rbtree.hpp:class-node2"
```

???+ note "Note"
    When storing red-black tree nodes, using an array for the child pointers makes it easier to reuse code.

## Operations

???+ note "Note"
    There are many ways to implement insertion/deletion in a red-black tree. This article follows *Introduction to Algorithms*: rebalancing after insertion is split into 3 cases, and rebalancing after deletion into 4 cases.

Traversal, finding the minimum/maximum, searching for an element, finding an element's rank, finding an element by rank, finding the predecessor/successor and similar operations are the same as in a [binary search tree](./bst.md), so we will not repeat them here.

Also, in the code comments for rebalancing after insertion/deletion below, we use the following conventions:

-   `p` means node `p` is black;
-   `[p]` means node `p` is red;
-   `{p}` means node `p` is red or black;
-   `|p|` means node `p` is a NIL node or is black.

### Rotation

Rotation is the key to keeping most balanced trees balanced. It changes the depth of some local nodes without changing the in-order traversal of a valid BST.

![rbtree-rotations](images/rbtree-rotate.svg)

???+ note "Implementation"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:rotate"
    ```

### Insertion

Insertion in a red-black tree is similar to insertion in an ordinary BST. In a red-black tree, the newly inserted node starts out red. After insertion, we fix things up according to the state of the inserted node and related nodes, so that the four properties above hold.

???+ note "Implementation"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:insert"
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:insert-leaf"
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:insert-fixup1"
        // ...
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:insert-fixup2"
    ```

### Rebalancing after insertion

???+ note "Note"
    To deepen your understanding, check for yourself that property 4 holds after rebalancing.

If the inserted node is not the root, it must be red, so the insertion may violate property 3, and we need to rebalance.

Let the inserted node be $n$, its parent $p$, its grandparent $g$, and its uncle $u$. By property 3, $g$ must be black.

We fix things recursively upward starting from the inserted position. If $p$ is black we can stop; otherwise there are 3 cases.

```cpp
--8<-- "docs/ds/code/rbtree/rbtree.hpp:insert-aux1"
      // ...
--8<-- "docs/ds/code/rbtree/rbtree.hpp:insert-aux2"
```

#### Insert case 1

$p$ and $u$ are both red. Here we only need to recolor.

![](images/rbtree-insert-case1.svg)

???+ note "Implementation"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:insert-case1"
    ```

#### Insert case 2

$p$ is red, $u$ is black, and $p$ and $n$ are on different sides (one is a left child, the other a right child).

Here we rotate at $p$ to turn this into case 3.

![](images/rbtree-insert-case2.svg)

???+ note "Implementation"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:insert-case2"
    ```

#### Insert case 3

$p$ is red, $u$ is black, and $p$ and $n$ are on the same side.

Here we rotate at $g$ to make $p$ the root of the subtree, and then swap the colors of $p$ and $g$.

![](images/rbtree-insert-case3.svg)

???+ note "Implementation"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:insert-case3"
    ```

### Deletion

Deletion in a red-black tree needs a few more steps than in an ordinary BST. Specifically:

-   If the node $n$ to delete has two children, swap the data of $n$ with the smallest node $s$ in its right subtree, and set $n$ to $s$. Now $n$ cannot have two children.
-   If the node $n$ to delete has one child $s$: by property 4, $s$ must be red, and then by property 3, $n$ must be black. So we just replace the pointer to $n$ in its parent $p$ with the address of $s$, set the parent pointer of $s$ to the address of $p$, and then color $s$ black.
-   If the node $n$ to delete has no children: if $n$ is the root or $n$ is red, just delete it. Otherwise deleting it directly would violate property 4, and we need to rebalance.

???+ note "Implementation"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:delete"
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:delete-leaf"
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:delete-fixup1"
        // ...
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:delete-fixup2"
    ```

### Rebalancing after deletion

???+ note "Note"
    To deepen your understanding, check for yourself that property 4 holds after rebalancing.

From the discussion above, $n$ is a black leaf and not the root. Let the parent of $n$ be $p$, its sibling $s$, and its nephews $c$ and $d$.

Rebalancing after deletion also proceeds recursively upward from $n$. If $n$ is the root or $n$ is red we can stop; otherwise there are 4 cases.

```cpp
--8<-- "docs/ds/code/rbtree/rbtree.hpp:delete-aux1"
      // Delete case 1
      // ...
      // Other cases
--8<-- "docs/ds/code/rbtree/rbtree.hpp:delete-aux2"
      // ...
--8<-- "docs/ds/code/rbtree/rbtree.hpp:delete-aux3"
```

#### Delete case 1

$s$ is red.

Here we rotate at $p$ to make $s$ the root of the subtree, and then swap the colors of $s$ and $p$. This turns it into one of the other three cases.

![](images/rbtree-remove-case1.svg)

???+ note "Implementation"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:delete-case1"
    ```

#### Delete case 2

The color of $p$ is unknown, and $s$, $c$ and $d$ are all black.

Here we just color $s$ red.

![](images/rbtree-remove-case2.svg)

Note that if $p$ is red, this would violate property 3. But if $p$ is red, the loop exits right away, so we color it black at the end.

???+ note "Implementation"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:delete-case2"
    ```

#### Delete case 3

The color of $p$ is unknown, $s$ and $d$ are both black, and $c$ is red.

Here we rotate at $s$ so that $c$ becomes the root of the subtree that $s$ used to root, and swap the colors of $s$ and $c$. This turns it into case 4.

![](images/rbtree-remove-case3.svg)

???+ note "Implementation"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:delete-case3"
    ```

#### Delete case 4

The colors of $p$ and $c$ are unknown, $s$ is black, and $d$ is red.

Here we rotate at $p$ to make $s$ the root of the subtree, swap the colors of $s$ and $p$, and color $d$ black. Then rebalancing is finished.

![](images/rbtree-remove-case4.svg)

???+ note "Implementation"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:delete-case4"
    ```

## Reference code

The code below implements a set with a red-black tree:

??? note "Implementation"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:full"
    ```

??? note "Example problems: [Luogu P3369 [Template] Ordinary Balanced Tree](https://www.luogu.com.cn/problem/P3369) and [Luogu P6136 [Template] Ordinary Balanced Tree (Enhanced Data)](https://www.luogu.com.cn/problem/P6136)"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:class"
    --8<-- "docs/ds/code/rbtree/rbtree_1.cpp:main"
    ```

## Relation to 2-3-4 trees

A 2-3-4 tree is a B-tree of order 4. Like ordinary B-trees, a 2-3-4 tree supports search, insertion and deletion in $O(\log n)$ time. A 2-3-4 tree has three kinds of nodes: 2-nodes, 3-nodes and 4-nodes, holding one, two and three data elements respectively. All leaves are at the same depth (the bottom level), and all data is stored in sorted order.

2-3-4 trees and red-black trees are isomorphic: every red-black tree corresponds to exactly one 2-3-4 tree. Insertions and deletions on a 2-3-4 tree cause nodes to grow, split and merge, which correspond to recoloring and rotations in a red-black tree. The figure below shows the red-black tree nodes corresponding to the 2-nodes, 3-nodes and 4-nodes of a 2-3-4 tree. Note that a 3-node corresponds to two red-black configurations, with the red node leaning left or right, so one 2-3-4 tree can correspond to several red-black trees.

![2-3-4-tree-rbt-1](images/2-3-4-tree-rbt-1.svg)

The figure below shows a red-black tree and its corresponding 2-3-4 tree. Moving each red node up to the left or right of its parent to form a B-tree node gives the corresponding 2-3-4 tree. Notice that the number of nodes in the red-black tree equals the number of nodes in the 2-3-4 tree.

![2-3-4-tree-rbt](images/2-3-4-tree-rbt-2.svg)

You can understand insertion and deletion in red-black trees by comparing them with 2-3-4 trees.[^234-vs-rbt]

## Use in real-world projects

The red-black tree is currently the in-memory balanced tree with the best overall performance in mainstream industry, so it is widely used in real projects. Here are a few real use cases with links to their source code, so you can compare and learn from them.

### Linux

Source code:

-   [`linux/lib/rbtree.c`](https://elixir.bootlin.com/linux/latest/source/lib/rbtree.c)

All red-black tree operations in Linux are implemented iteratively with loops. The code is efficient and also has many comments that keep it readable, so it is well worth reading. Red-black trees are used all over the Linux kernel; here are just a few classic examples.

-   [CFS scheduling of non-real-time tasks](https://www.kernel.org/doc/html/latest/scheduler/sched-design-CFS.html)

    Since stable kernel version 2.6.24, Linux uses a new scheduler, CFS. All runnable non-real-time processes are kept in a red-black tree keyed by virtual runtime, so that all tasks are scheduled more fairly and efficiently. CFS drops the active/expired arrays and dynamic priority calculation, and no longer tracks task sleep time or tries to tell whether a task is interactive. Instead, it picks the next task using a red-black tree keyed by time, and sets scheduling priority based on how much CPU time each task has used.

-   [epoll](https://man7.org/linux/man-pages/man7/epoll.7.html)

    epoll, short for event poll, is the Linux kernel's implementation of IO multiplexing and an improved version of the older poll/select. The Linux implementation of epoll uses a red-black tree to store file descriptors.

### Nginx

Source code:

-   [`nginx/src/core/ngx_rbtree.h`](https://github.com/nginx/nginx/blob/master/src/core/ngx_rbtree.h)
-   [`nginx/src/core/ngx_rbtree.c`](https://github.com/nginx/nginx/blob/master/src/core/ngx_rbtree.c)

User-space timers in nginx are implemented with a red-black tree. In nginx, all timer nodes are kept in a red-black tree. Each loop of a worker process calls `ngx_process_events_and_timers`, which calls the timer-handling function `ngx_event_expire_timers`. Each time, this function repeatedly takes the node with the smallest time value out of the red-black tree, checks whether it has expired, and runs its handler, until it finds a node that has not expired yet.

There are many public source-code analyses of nginx's red-black tree, which you can look up yourself.

### C++

Source code:

-   GNU libstdc++

    -   [`libstdc++-v3/include/bits/stl_tree.h`](https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/bits/stl_tree.h)
    -   [`libstdc++-v3/src/c++98/tree.cc`](https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/src/c%2B%2B98/tree.cc)

    In addition, `libstdc++` provides [`__gnu_cxx::rb_tree`](https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/ext/rb_tree) in `<ext/rb_tree>`. It inherits from `std::_Rb_tree` and can be seen as a type alias for external use. Note that this header is **not** part of the C++ standard, so avoid it unless you really need it.

    `libstdc++` also provides a red-black tree in [`pb_ds`](../lang/pb-ds/tree.md).

-   LLVM libcxx
    -   [`libcxx/include/__tree`](https://github.com/llvm/llvm-project/blob/main/libcxx/include/__tree)

-   Microsoft STL
    -   [`stl/inc/xtree`](https://github.com/microsoft/STL/blob/main/stl/inc/xtree)

In most STL implementations (such as the ones above), the internal data structure of `std::set` and `std::map` is a red-black tree. Note, however, that the C++ standard does not require `std::set` and `std::map` to be implemented with red-black trees, so real projects should not rely directly on their internal data structure.

### OpenJDK

Source code:

-   [`java.util.TreeMap<K, V>`](https://github.com/openjdk/jdk/blob/master/src/java.base/share/classes/java/util/TreeMap.java)
-   [`java.util.TreeSet<K, V>`](https://github.com/openjdk/jdk/blob/master/src/java.base/share/classes/java/util/TreeSet.java)
-   [`java.util.HashMap<K, V>`](https://github.com/openjdk/jdk/blob/master/src/java.base/share/classes/java/util/HashMap.java)

In the JDK, both `TreeMap` and `TreeSet` use a red-black tree as their underlying data structure. Also, since JDK 1.8, when the linked list in a bucket of `HashMap`'s internal hash table grows longer than 8, it is automatically turned into a red-black tree to speed up lookups.

## References

-   Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2022).*Introduction to algorithms*. MIT press.
-   [Red-Black Tree - Wikipedia](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree)
-   [Red-Black Tree Visualization](https://www.cs.usfca.edu/~galles/visualization/RedBlack.html)

[^gilbas1978]: L. J. Guibas and R. Sedgewick, "A dichromatic framework for balanced trees,"*19th Annual Symposium on Foundations of Computer Science (sfcs 1978)*, Ann Arbor, MI, USA, 1978, pp. 8-21, doi:[10.1109/SFCS.1978.3](https://doi.org/10.1109%2FSFCS.1978.3).

[^cite_note-cormen2009-18]: <https://en.wikipedia.org/wiki/Red–black_tree#cite_note-Cormen2009-18>

[^cite_note-mehlhorn2008-17]: <https://en.wikipedia.org/wiki/Red–black_tree#cite_note-Mehlhorn2008-17>

[^cite_note-algs4-16]: <https://en.wikipedia.org/wiki/Red–black_tree#cite_note-Algs4-16>: 432–447

[^234-vs-rbt]: [This blog post](https://www.cnblogs.com/zhenbianshu/p/8185345.html) gives a detailed description.
