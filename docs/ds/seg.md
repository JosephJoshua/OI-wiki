author: Ir1d, hsfzLZH1, Tiphereth-A, ksyx, Marcythm, StudyingFather, Xeonacid, ChungZH, Early0v0, chenryang, Enter-tainer, CCXXXI, cjsoft, HeRaNO, konnyakuxzy, NachtgeistW, orzAtalod, wy-luke, amlhdsan, billchenchina, c-forrest, Chrogeek, countercurrent-time, ethan-enhe, GavinZhengOI, H-J-Granger, iamtwz, luoguojie, AKindMouse, AngelKitty, chenzheAya, CJSoft, DawnMagnet, diauweb, ezoixx130, GekkaSaori, Gesrua, Haohu Shen, Henry-ZHR, hjsjhn, hly1204, jaxvanyang, Jebearssica, kenlig, Konano, kxccc, LovelyBuggies, lychees, Makkiy, megakite, Menci, mgt, minghu6, moon-dim, onelittlechildawa, ouuan, P-Y-Y, Peanut-Tang, PotassiumWings, SamZhangQingChuan, shadowice1984, shawlleyw, shuzhouliu, sshwy, SukkaW, Suyun514, weiyong1024, x2e6, Ycrpro, yifan0305, zeningc

## Introduction

A segment tree is a data structure widely used in competitive programming to maintain **range information**.

A segment tree supports point updates, point queries, range updates, range queries and similar operations in $O(\log N)$ time.

## Basic structure and operations

A segment tree is a binary tree. Each node stores information about one interval:

-   A leaf stores information about a single element $x$, which can also be seen as information about the interval $[x,x]$ of length $1$.
-   For a non-leaf node, the leaves of its subtree form a contiguous interval $[l,r]$. That node stores the information about $[l,r]$.

A non-leaf node always has two children, and its interval is exactly the disjoint union of its children's intervals. If a non-leaf node stores information about $[l,r]~(l < r)$, then its two children store information about $[l,m]$ and $[m+1,r]$, where $l \le m < r$.

The root of the segment tree stores information about the whole interval $[L,R]$. The size of the segment tree is the length of this interval, $N = R - L + 1$.

### Range information

A segment tree maintains range information. This section describes the common properties range information must have, and how to implement them.

In general, **range information** is a function of an interval, $\varphi:\mathcal I\rightarrow M$. Here $\mathcal I$ is the set of all subintervals of $[L,R]$ (including the empty interval), and $M$ is the set of values the information can take, which this article calls the **information space**. The range information $\varphi$ stored in a segment tree must satisfy the following properties:

1.  When an interval is split into two subintervals, its information can be obtained by merging the information of the two parts. That is, if $I$ is the disjoint union of $I_1$ and $I_2$, with $I_1$ to the left of $I_2$, then $\varphi(I)=\varphi(I_1)\circ\varphi(I_2)$, where the operation $\circ$ is called **information merging**.
2.  When an interval is split into a disjoint union of several subintervals, merging their information gives the same result no matter how the interval is split or how the merges are grouped, and it always equals the information of the original interval. That is, the operation $\circ$ is associative.
3.  The empty interval $\varnothing$ also has well-defined information $e=\varphi(\varnothing)$. Since any interval $I$ is the disjoint union of itself and the empty interval $\varnothing$, merging any range information with the empty interval's information leaves it unchanged. That is, $\varphi(I)\circ e = e\circ\varphi(I) = \varphi(I)$. So $e$ is the identity element of $\circ$.

These properties guarantee that to query the information of an interval $I$, it is enough to find a set of nodes whose intervals form a partition of $I$; we can then merge the information stored at these nodes to get the information of $I$.

Range information can be merged, merging is associative, and there is an identity element. This means the information space $M$ forms a [monoid](../math/algebra/basic.md#groups) under the merge operation $\circ$.[^monoid]

???+ info "Convention"
    In the reference implementations of segment tree operations, this article assumes elements of the information space $M$ are stored in an `Info` struct. Its default constructor gives the identity element, and it overloads the addition operator to implement information merging.

???+ example "Examples"
    Many kinds of range information satisfy the monoid properties. Interval length, interval sum, interval product and interval maximum are simple examples. Their monoids are $(\mathbf N,+),~(\mathbf R,+),~(\mathbf R,\times),~(\mathbf R\cup\{-\infty\},\max)$, with identity elements $0,0,1,-\infty$. These examples extend to other common operations with the monoid property, such as bitwise XOR, matrix multiplication and function composition.
    
    There are also more complex examples. For instance, the maximum (non-empty) subarray sum of an interval can also be maintained as a monoid. Of course, if we only store the maximum subarray sum itself, we cannot merge. For a partition $I = I_1 \cup I_2$, the maximum subarray of $I$ may lie inside $I_1$, inside $I_2$, or cross the boundary between $I_1$ and $I_2$. To compute the best value in the last case, we also need to store the interval sum, the maximum (non-empty) prefix sum and the maximum (non-empty) suffix sum.
    
    === "Interval sum"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-2.cpp:info"
        ```
    
    === "Interval maximum (non-negative values)"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-bisect-recursive.cpp:info"
        ```
    
    === "Linear function"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-recursive.cpp:info"
        ```
    
    === "Maximum non-empty subarray sum"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-1.cpp:info"
        ```

Note that merging range information is not necessarily commutative. When merging, you must strictly follow the order of the subintervals from left to right.

### Recursive building and storage

To keep the tree as short as possible, we split the current node's interval $[l,r]$ into two halves as evenly as possible. For this we usually choose

$$
m = \left\lfloor\dfrac{l + r}{2}\right\rfloor.
$$

Then, if the current node's interval has length $n > 1$, its two children $[l,m]$ and $[m+1,r]$ have lengths $\lceil n/2\rceil$ and $\lfloor n/2\rfloor$. The resulting segment tree has height $\lceil\log_2N\rceil$. This guarantees that the segment tree is a balanced binary tree, and point operations always cost $O(\log N)$.

![](images/seg-1.svg)

To store information over an interval of length $N$, we build a segment tree with $N$ leaves. As a full binary tree (every node has $0$ or $2$ children), the segment tree has exactly $2N-1$ nodes that store information. So a segment tree built this way uses $\Theta(N)$ space. Building it recursively visits each node exactly once, so it also takes $\Theta(N)$ time.

Although the shape of a segment tree is fairly fixed, there is more than one way to store it.

![](images/seg-2.svg)

The first common way is heap-style storage (shown above), which embeds the segment tree into a perfect binary tree. The root has index $1$; if the current node has index $i$, its left and right children have indices $2i$ and $2i+1$. Since the tree height is $\lceil\log_2N\rceil$, this needs an array of length $2^{\lceil\log_2N\rceil + 1}$. For simplicity, people usually just allocate an array of length $4N$[^heap-size], or pad $N$ to a power of $2$, $N'$, and allocate an array of length $2N'$. The advantage is that children's indices need not be stored; the disadvantage is that some nodes are unused, so memory is not used efficiently.

![](images/seg-3.svg)

The second common way uses a memory pool and assigns node indices dynamically. Since the shape of the segment tree is fixed, node indices only need to be assigned once while building. This leaves no unused nodes, so an array of length $2N$ is enough. Here a node's index is its position in the preorder traversal of the segment tree. However, since the index of the (right) child cannot be computed from the current node's index alone[^child-id], we usually allocate extra arrays of total length $4N$ to store the left and right children's indices. If storing one index takes space $1$ and storing one node takes space $K$, then as long as $2NK + 4N \le 4NK$, that is, $K \ge 2$, dynamic allocation uses no more memory than heap-style storage.

Here are implementations of these two ways of storing and building a segment tree:

???+ example "Reference implementation"
    === "Heap-style storage"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-recursive.cpp:build"
        ```
    
    === "Dynamically allocated nodes"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-lazy-recursive.cpp:build"
        ```

???+ tip "Tips"
    1.  When computing the midpoint $m = \lfloor(l+r)/2\rfloor$ of $[l,r]$, writing `m = l + (r - l) / 2` instead of `m = (l + r) / 2` avoids integer overflow and the problem of negative division rounding toward zero.
    2.  It is common to write a `push_up` function that merges the children's information into the current node.

Apart from how children are accessed, the choice of storage does not affect how the other operations are implemented after building. However, with heap-style storage a node's index is determined by its position in the perfect binary tree, which is less flexible: it cannot support extensions such as dynamically allocated nodes or persistence.

### Point updates and queries

The simplest segment tree operations are point operations.

First consider a point query. The leaves of a segment tree store the elements in order. So at a non-leaf node, we only need to compare the queried position with the midpoint of the current interval to decide whether to go to the left child or the right child. When we reach a leaf, we return the information stored there. That completes a point query.

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/seg/seg-recursive.cpp:point-get"
    ```

A point update is similar. Again we go top-down to the leaf we need. Then we modify that leaf. Finally, while returning from the recursion, we update the information of all ancestors of that leaf. That is a point update. Since any update to a single point can be seen as replacing its value, we only give a reference implementation for setting a value. The section [Range updates and lazy tags](#range-updates-and-lazy-tags) discusses more general updates.

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/seg/seg-recursive.cpp:point-set"
    ```

Since the tree height is $\Theta(\log N)$, point operations on a segment tree all take $O(\log N)$ time.

### Range queries

Next, consider range queries.

![](images/seg-5.svg)

As explained above, we just need to split the query interval into a disjoint union of intervals of segment tree nodes, and then merge the information at these nodes in order. Of course, the fewer nodes the better. This means the nodes should correspond to the **maximal intervals** contained in the query interval. In the figure above, the shaded area marks the query interval, and nodes with thick borders correspond to maximal intervals. Finding these nodes is easy: starting from the root, search downward through every node whose interval intersects the query interval. When we reach a node whose interval is fully contained in the query interval, we have found a node for a maximal interval, so there is no need to search its descendants.

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/seg/seg-recursive.cpp:range-get"
    ```

???+ tip "Tips"
    1.  Besides the implementation above, you can also stop the search when you reach a node whose interval does not intersect the query interval.
    2.  Since the result is initialized to the identity element of the information space $M$, the result from the left child can simply overwrite it without a merge.

One can show that the total number of nodes visited during a range query, namely all maximal-interval nodes and their ancestors, is $O(\log N)$. So a range query also takes $O(\log N)$ time.

??? note "Proof"
    During a range query, for every visited non-root node, its parent's interval must contain the left or right endpoint of the query interval. Otherwise, the parent's interval would either be fully inside the query interval or disjoint from it, and in both cases we would not visit its children (including the current node). Moreover, nodes at the same depth have pairwise disjoint intervals, so at most $1$ of them contains the left endpoint and at most $1$ contains the right endpoint, and each node has at most $2$ children. So a range query visits at most $4$ nodes at each depth. The segment tree has height $\Theta(\log N)$, so a range query visits $O(\log N)$ nodes.

### Range updates and lazy tags

Finally, consider range updates.

Unlike range queries, a range update does not only affect the maximal-interval nodes and their ancestors; it also affects their descendants. This is because the update changes subintervals of these maximal intervals, which belong to the descendants of those nodes. Updating every node affected by the range would clearly be too slow to be practical. So range updates use the idea of a **lazy tag**. Specifically, each range update actually changes only the maximal-interval nodes and their ancestors, and the changes to the descendants of the maximal-interval nodes are postponed until they are really needed. To remember the pending changes, we leave a tag at each maximal-interval node. This tag records the operation that still needs to be applied to the node's descendants (not the node itself) but has not been applied yet. This is the lazy tag.

???+ info "Convention"
    This article assumes that a node carrying a lazy tag has already been updated itself. This is not required, and it may differ between implementations.

In a segment tree that supports range updates, the other operations must be adjusted accordingly. In any operation, whenever we need to visit a node's children, we must check whether the current node has a lazy tag that has not been cleared. If it does, we first push down the lazy tag, and then visit the children or do other work. Pushing down a lazy tag means applying the corresponding update to the node's children, putting the lazy tag on those children, and finally clearing the tag at the current node.

???+ example "Example"
    The figure below shows the segment tree built from the array $[4,1,3,2,5]$.
    
    ![](images/seg-lazy-1.svg)
    
    At each node, $s$ is the sum of the elements in the interval, and $t$ is the lazy tag used for range addition. Initially, all interval sums are correct and all lazy tags are empty. Now add $2$ to every element in the interval $[2,5]$. The result is shown below.
    
    ![](images/seg-lazy-2.svg)
    
    In the figure, the shaded area marks the update interval, and nodes with thick borders correspond to maximal intervals. At these maximal-interval nodes, the sum $s$ increases by $2$ times the interval length, which correctly reflects the range addition; at the same time the lazy tag increases by $2$, meaning that the descendants have not been updated yet. The ancestors of the maximal-interval nodes get updated sums from their children. If we now query the sum of the interval $[4,4]$, the result is shown below.
    
    ![](images/seg-lazy-3.svg)
    
    While visiting $[4,4]$, we first visit $[4,5]$ and notice that it has the lazy tag $t=2$. Before visiting its children, we must push down the lazy tag: apply a range addition of $2$ to each child, and increase each child's lazy tag by $2$ to show that their descendants (which don't exist in this figure) have not been updated yet. Finally, clear the tag at $[4,5]$. After pushing down, we continue to the child $[4,4]$ and read the correct sum $4$.

When doing a range update or pushing down a lazy tag, the node to be tagged may already have a lazy tag that has not been cleared. In that case we cannot simply overwrite the tag; we must update it to the composition of the two operations. Since composition is not necessarily commutative, the order matters: the new operation is always composed after the existing tag. When pushing down, the parent's tag is always composed after the child's existing tag. This is because tags are always pushed down before children are visited, so when the child's existing tag was placed, the parent must have had no tag; the parent's current tag can only come from later operations.

To record range updates correctly, we need to understand the properties these updates must have. As before, let the range information stored in the segment tree be the function $\varphi:\mathcal I\rightarrow M$. Further, let an update be $\pi:M\rightarrow M$, which turns old information into new information by some rule. Then a range update $\pi$ must satisfy the following properties:

1.  It is well-defined. That is, the result of the update depends only on the information $m\in M$, not on the interval $I\in\mathcal I$ it belongs to. If the result of an update depends on features of the interval, those features (such as its length or its endpoints) can be treated as part of the range information.
2.  The update must be compatible with merging range information. That is, if the information of an interval can be merged from the information of its subintervals, then the result of updating the interval can still be merged from the results of updating the subintervals. In other words, for $m_1,m_2\in M$ we always have $\pi(m_1\circ m_2) = \pi(m_1)\circ\pi(m_2)$.
3.  In particular, updating the information of the empty interval still gives the information of the empty interval, that is, $\pi(e)=e$.[^endo]

This means an update is an [endomorphism](../math/algebra/group-theory.md#group-homomorphisms) of the monoid $M$. Moreover, consider the set $\Pi$ of these updates. As long as it is closed under composition, $\Pi$ is also a monoid, since composition of maps is associative and the identity map is the identity element.

???+ info "Convention"
    In the reference implementations of segment tree operations, this article assumes updates are stored in a `Transform` struct. Its default constructor gives the identity operation; it overloads the addition operator to implement composition of operations, and overloads the call operator to apply the update to range information. To make it easy to check whether a lazy tag is empty (that is, does nothing), it also overloads an explicit conversion to bool.

???+ example "Examples"
    Segment trees support many kinds of updates. Range addition, range multiplication, range assignment and range affine transformations are common examples. The difficulty is usually not the operation itself, but how to apply it to the range information, that is, how to make it satisfy the three properties above. For example, if we maintain interval sums and need range addition, the contribution of the increment to the sum is the added value times the interval length, and the interval length is not part of the range information. In that case, following the first property, we just add the interval length to the range information.
    
    === "Interval minimum info & range addition"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-perm-recursive.cpp:info"
        --8<-- "docs/ds/code/seg/seg-perm-recursive.cpp:transform"
        ```
    
    === "Interval sum info & range addition"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-5.cpp:info"
        --8<-- "docs/ds/code/seg/seg-5.cpp:transform"
        ```
    
    === "Interval maximum info & range assignment"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-bisect-recursive.cpp:info"
        --8<-- "docs/ds/code/seg/seg-bisect-recursive.cpp:transform"
        ```

Once the struct for storing range updates is in place, lazy updating and pushing down lazy tags can be implemented as follows:

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/seg/seg-lazy-recursive.cpp:tag"
    ```

???+ tip "Tips"
    1.  Don't put lazy tags on empty nodes.
    2.  With a careful implementation, you can also avoid putting lazy tags on leaves.

A single push-down usually takes $O(1)$ time.

Then a range update can be implemented as follows:

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/seg/seg-lazy-recursive.cpp:range-set"
    ```

Like a range query, a range update on a segment tree with lazy tags takes $O(\log N)$ time. The other operations on a segment tree with lazy tags are implemented almost the same as without them; you only need to push down tags before visiting children. Since a single operation pushes down at most $O(\log N)$ tags, these operations still take $O(\log N)$ time, only with a larger constant. If there are no range updates, people usually implement a segment tree without lazy tags to keep the constant small.

### Reference implementation

Below are complete reference implementations of segment trees without and with lazy tags.

??? example "Reference implementation"
    === "Without lazy tags"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-recursive.cpp:seg-tree"
        ```
    
    === "With lazy tags"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-lazy-recursive.cpp:seg-tree"
        ```

In real use, you may need to check whether update and query operations are valid.

## Common techniques

This section introduces several techniques often used when solving concrete problems with segment trees. Some reduce the constant factor, others extend the basic functionality.

### Non-recursive implementation

The recursive segment trees described above can only be accessed top-down by recursion, and pay the corresponding recursion overhead. Another approach is to maintain the segment tree bottom-up. In Chinese contest materials this implementation became widely known through Zhang Kunwei's introduction, so it is often called the **zkw segment tree**.

![](images/seg-4.svg)

The figure above shows how the non-recursive implementation is stored. It still embeds the segment tree into a perfect binary tree, but builds it bottom-up. First, all leaves are stored on the same level at depth $\lceil\log_2N\rceil$; extra leaves store the identity element $e$, which can be seen as the information of an empty interval. Then the non-leaf nodes are visited bottom-up, and each merges its children's information. Because all leaves are on the same level, the resulting tree has a slightly different shape from the two earlier methods, but it can still maintain range information. Its space usage is the same as heap-style storage: an array of length $2^{\lceil\log_2N\rceil + 1}$.

The biggest advantage of this layout is that the leaves have consecutive indices and are easy to locate, and the indices of parents and children can be computed directly. As the figure shows, let $n=2^{\lceil\log_2N\rceil}$, that is, $N$ rounded up to a power of $2$. Then the value of element $x\in[L,R]$ is stored at node $n+x-L$. For a non-root node $i$, its parent is $\lfloor i/2\rfloor$, and more generally its ancestor $d$ levels up is $\lfloor i/2^d\rfloor$. For a non-leaf node $i$, its left and right children are $2i$ and $2i+1$.

With these properties, building and point operations are very easy. To build, copy each element's information to its leaf, then go through nodes $[1,n-1]$ in reverse order and merge the children's information. A point query can directly return the information stored at the leaf. A point update can also modify the leaf directly, and then it must update the information of its ancestors.

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/seg/seg-nonrecursive.cpp:build"
    --8<-- "docs/ds/code/seg/seg-nonrecursive.cpp:point-get"
    --8<-- "docs/ds/code/seg/seg-nonrecursive.cpp:point-set"
    ```

![](images/seg-6.svg)

Range queries are a bit more involved: we need to find all maximal-interval nodes of $[l,r]$ in the tree. Ignore the right endpoint for now and consider the maximal interval containing the left endpoint $l$. The nodes whose intervals contain $l$ are exactly the leaf for $l$ and its ancestors. So start from the leaf for $l$ and keep jumping up until the current node is the right child of its parent. At that point the parent also contains elements to the left of the current node, which are not part of what still needs counting, so the current node's interval is the maximal interval containing $l$. After adding its information, move one node to the right on the same level and then jump to the parent; this gives the node containing the leftmost element not yet counted. Repeat the process. The right endpoint is handled symmetrically. In practice both sides are processed together until they meet, at which point the query interval has been fully counted. Note that the information must be accumulated separately for the left and right sides, and the two results merged at the end, so that the merge order is correct.

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/seg/seg-nonrecursive.cpp:range-get"
    ```

???+ tip "Tips"
    Implementations of range queries differ in small details. The implementation here queries the closed interval $[l,r]$, the [AtCoder Library](https://github.com/atcoder/ac-library/blob/master/atcoder/segtree.hpp#L52-L65) queries $[l,r)$, and Zhang Kunwei's original material queries $(l,r)$. There is no real difference among them; they only handle the boundaries differently.

Finally, consider range updates. The key is handling the lazy tags. Nodes can still be visited bottom-up, but tags must be pushed down top-down; otherwise we cannot clear all tags on a root-to-leaf path. So we just need to find all ancestors of the maximal-interval nodes and push down their tags from top to bottom. To do this, note that the parent of a maximal-interval node must contain one of the two endpoints, and the nodes containing a given endpoint all lie on the path from the root to that endpoint's leaf. However, not every node on that path is an ancestor of a maximal-interval node: the part starting from the maximal-interval node that contains the endpoint, down to the leaf, is not, and it should be skipped. So we push tags down once from root toward leaf along the two paths to the leaves of the left and right endpoints, skipping that part. After the update, we go back up the same two paths and update the ancestors' information bottom-up.

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/seg/seg-lazy-nonrecursive.cpp:range-set"
    ```

???+ tip "Tips"
    1.  The implementation here still updates the closed interval $[l,r]$; for the half-open $[l,r)$ version, see the [AtCoder Library](https://github.com/atcoder/ac-library/blob/master/atcoder/lazysegtree.hpp#L110-L138). Both versions use bit operations, and the core idea is the same: in the part of nodes that should be skipped, the left (right) endpoint of each node's interval is aligned with the left (right) endpoint of the update interval.
    2.  For this part of nodes, skipping them while pushing down only affects efficiency, but skipping them while going back up is required: calling `push_up` on a node that just got a lazy tag would overwrite it with the children's information, which has not been updated yet.

In the non-recursive implementation with lazy tags, the other operations likewise only need an extra root-to-leaf push-down before visiting nodes.

Here are complete reference implementations of the non-recursive segment tree, again in two versions, without and with lazy tags:

??? example "Reference implementation"
    === "Without lazy tags"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-nonrecursive.cpp:seg-tree"
        ```
    
    === "With lazy tags"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-lazy-nonrecursive.cpp:seg-tree"
        ```

Apart from point queries in the version without lazy tags, which drop to $O(1)$, all operations have the same complexity as in the recursive version, only with a smaller constant.

In summary, the non-recursive implementation also supports all basic segment tree operations, including range updates and lazy tags. But like heap-style storage, node indices are determined by position, so all nodes of the perfect binary tree must exist in advance. So it cannot allocate nodes dynamically, and it is hard to make persistent.

### Dynamic node allocation

All the storage methods above allocate $\Theta(N)$ space at once when building. This is not feasible when the interval length $N$ is large (for example $\sim 10^9$). To save space, we can avoid building the whole tree at once: at first we create only a root representing the whole interval, and we create a child for a subinterval only when we need to visit it. Since node indices are not fixed, a dynamically allocated segment tree must use a memory pool, and it needs arrays to record children's indices.

This only works if the information of nodes that have not been created is known. The simplest case is when the information of an uncreated node's interval is exactly the identity element $e$ of the information space $M$ (the information of an empty interval). Then a query that reaches an empty node simply returns $e$, and merging needs no special handling; only when an update needs to write information do we create the nodes along the path. In the more general case, the information of an uncreated node depends on its interval. For such problems, when querying an empty node, creating a new node or merging children's information, we must compute the information from the current interval's endpoints. Either way, a dynamically allocated segment tree usually cannot be built from an arbitrary given initial array. Also, since node indices no longer encode interval information, splitting intervals must follow the recursive approach and pass the current node's interval down as parameters. Pay special attention that the children must also be created before a lazy tag is pushed down.

![](images/seg-7.svg)

For reference, here are dynamically allocated segment trees without and with lazy tags. To match the two cases above, the first assumes that uncreated nodes hold exactly the identity element $e$, and the second assumes their information depends on their interval.

??? example "Reference implementation"
    === "Without lazy tags"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-dynamic.cpp:seg-tree"
        ```
    
    === "With lazy tags"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-lazy-dynamic.cpp:seg-tree"
        ```

???+ tip "Tips"
    Pushing down a tag requires creating the children first, which increases the space constant factor. Make sure to allocate enough space.

Since each update creates nodes only along at most two root-to-leaf paths, a single operation creates at most $O(\log N)$ new nodes. So after $q$ operations there are $O(q\log N)$ nodes in total, which is exactly why dynamic allocation can handle huge intervals. The time complexity is the same as before: $O(\log N)$ per operation. The bound $O(q\log N)$ is quite loose. In practice, if the operation intervals overlap a lot, far fewer nodes are created; if every operation touches disjoint intervals, the count gets close to this bound. When initializing the segment tree, allocate enough space based on this bound.

Dynamic allocation is only one way to handle such problems. If all endpoints used by the operations are known in advance, you can first [discretize](../misc/discrete.md) them and build an ordinary segment tree on the discretized range. This has the same effect and is easier to implement. Dynamic allocation is needed only when the operations cannot be known in advance (for example, when the problem forces online processing).

In addition, the [persistent segment tree](./persistent-seg.md) is also built on dynamic allocation: each update creates only the nodes on one root-to-leaf path and shares the rest with the old version, so each update needs only $O(\log N)$ extra space.

### Permanent tags

All lazy tags described so far need to be pushed down. But every push-down reads and writes the children, which has a noticeable constant cost, and in some cases tags are hard to push down. To avoid pushing down lazy tags, we can use permanent tags: once a tag is placed, it stays there forever and is never pushed down. During a query, we compose the tags along the path from the root to the node and apply them to the information stored at that node.

![](images/seg-8.svg)

As before, assume the tag at node $x$ affects only its descendants, and the information stored at $x$ already includes the effect of that tag. In other words, $x$ stores the information of its interval ignoring the tags at its ancestors. Using the recursive implementation as an example, the range operations work like this:

-   Range update: recurse top-down. When reaching a maximal-interval node, put a tag there, update its information, and return immediately without going further down. While returning, merge the children's information to get the current node's information, then apply the current node's tag.
-   Range query: recurse top-down. When reaching a maximal-interval node, return its stored information directly. While returning, merge the results from the children, then apply the current node's tag. Level by level, the tags of all nodes on the way get applied to the result.

Both operations still take $O(\log N)$ time, but all push-downs are saved, so the constant is smaller. The non-recursive version is similar; it just replaces recursion with iteration. Reference implementations follow:

??? example "Reference implementation"
    === "Recursive implementation"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-perm-recursive.cpp:seg-tree"
        ```
    
    === "Non-recursive implementation"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-perm-nonrecursive.cpp:seg-tree"
        ```

However, permanent tags are not always possible; they put an extra requirement on updates. The composition of updates must be **commutative**. As explained earlier, composing lazy tags is not necessarily commutative. Pushing down keeps the order correct because tags are always pushed down before children are visited, so on a root-to-leaf path, a tag closer to the root always corresponds to a later operation. Permanent tags give up exactly this property: tags stay where they were placed, at positions determined by the update interval, regardless of when the operations happened. So a tag on an ancestor may come either before or after a tag on a descendant. Since a query composes tags in root-to-leaf order, the result is guaranteed to be correct only if composition is commutative.

???+ example "Examples"
    Range addition, range multiplication and similar operations are commutative and can use permanent tags. Range affine transformations (allowing both range addition and range multiplication) and range assignment[^assign] are not commutative and cannot use permanent tags.

Permanent tags are often used in [persistent segment trees](./persistent-seg.md) and various trees of trees. In these two settings pushing down is expensive, so permanent tags, even when not strictly needed, are often the better choice. In some problems tags cannot be pushed down at all (see the "Area of union of rectangles" example later); then permanent tags are the only option.

### Binary search on a segment tree

Some problems need a binary search over a sequence. For example, given $l$, find the largest $r$ such that the information of $[l,r]$ satisfies some condition. The direct approach is to binary search on $r$ and query the segment tree each time, which costs $O(\log^2 N)$. But a segment tree is itself a binary-splitting structure; by doing the binary search on the segment tree itself, we can get $O(\log N)$.

As before, let the range information stored in the segment tree be $\varphi:\mathcal I\rightarrow M$. Let the condition be a predicate $g:M\rightarrow\{\text{True},\text{False}\}$ on the information space $M$. For binary search to make sense, $g$ must be **monotonic** (with respect to merging on the right): if $g(m)$ is false, then $g(m\circ m')$ is also false for any $m'$. That is, once the interval is extended to the right far enough that the condition fails, it never holds again. We also need $g(e)$ to be true, meaning the empty interval always satisfies the condition. The problem then becomes: given $l$, find the largest $r$ such that $g(\varphi([l,r]))$ is true; if $g(\varphi([l,l]))$ is already false, the answer is defined as $l-1$.

![](images/seg-9.svg)

In the recursive segment tree, the binary search works like this: recurse top-down while keeping an accumulated value $m$, the information of the part already confirmed to be in the answer interval. When reaching a node whose interval $I$ lies entirely inside $[l,R]$, first try to take the whole node: compute $m\circ\varphi(I)$. If $g$ is still true, the whole node can be included, so update $m$ and return the node's right endpoint. Otherwise, the boundary of the answer is inside this node, and we keep recursing down. If we reach a leaf and the condition still fails, the boundary is right there.

This still takes $O(\log N)$ time. During the recursion, only two kinds of nodes go further down: nodes whose intervals go outside $[l,R]$, which all lie on the path from the root to $l$; and nodes whose full inclusion would make $g$ false, of which only the nodes on the path to the boundary actually go down, at most one per level. Both kinds have only $O(\log N)$ nodes, and every other node is either taken whole or skipped whole.

![](images/seg-10.svg)

The non-recursive implementation splits this process into two phases. First bottom-up: starting from the leaf for $l$, keep jumping up while the current node is a left child, until it is a right child. At that point the left endpoint of its interval lines up with the part not yet included, so try to include the whole node. If that succeeds, move one node to the right and keep jumping up. As soon as including some node would make $g$ false, switch to top-down: go down inside that node, and at each level first try to include the left child; if that succeeds, move to the right child, otherwise go into the left child, until reaching a leaf, which gives the boundary. Each phase makes only one pass, so this also takes $O(\log N)$.

Symmetrically, we can also, given $r$, find the smallest $l$ such that $g(\varphi([l,r]))$ is true. Here the accumulated information is merged from right to left, computing $\varphi(I)\circ m$, to keep the merge order correct; if there is no solution, the answer is defined as $r+1$. Also, $g$ must be monotonic with respect to merging on the left: if $g(m)$ is false, then $g(m'\circ m)$ is also false for any $m'$.

??? example "Reference implementation"
    === "Recursive implementation"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-bisect-recursive.cpp:max-right"
        --8<-- "docs/ds/code/seg/seg-bisect-recursive.cpp:min-left"
        ```
    
    === "Non-recursive implementation"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-bisect-nonrecursive.cpp:max-right"
        --8<-- "docs/ds/code/seg/seg-bisect-nonrecursive.cpp:min-left"
        ```

???+ tip "Tips"
    1.  With lazy tags, you also need to push down tags before visiting children. In the non-recursive implementation, before the jump-up phase starts, push down once along the path from the root to $l$.
    2.  If the check depends only on the current node's own information (for example, "is there an element greater than $x$ in the interval"), there is no need to keep accumulated information, and the implementation is simpler.
    3.  In the non-recursive implementation, the extra leaves store the identity element, on which $g$ is always true, so the jump-up phase may pass over all of them. In that case, return $R$ directly instead of converting a node index to a position.

### Value-domain segment tree

The segment trees so far are built over the indices of a sequence. But a segment tree does not care what the indices mean. If we build it over the value range instead, letting the leaf for value $v$ record how many times $v$ appears in a multiset, we get a **value-domain segment tree** (weight segment tree).

![](images/seg-11.svg)

Such a segment tree can be used as a set that supports the common operations of a [balanced binary search tree](./bst.md), and these operations follow directly from the operations above:

-   Insert element $v$: add one at position $v$.
-   Delete element $v$: subtract one at position $v$; remember to check that the element exists.
-   Find the rank of $v$: query the sum over the value range $[L,v-1]$ and add one.
-   Find the $k$-th smallest element: use binary search on the segment tree to find the largest $r$ such that the number of elements in the value range $[L,r]$ is less than $k$; then $r+1$ is the answer. Since counts can be subtracted, when going down we only need to compare the left child's count with $k$, with no accumulated information.
-   Find the predecessor and successor: these can be done with the rank query and the $k$-th smallest query.

Compared with common balanced trees, a value-domain segment tree is much simpler to implement and has a smaller constant. The price is that it can only handle elements over a value range, and it does not support operations that depend on the tree structure itself, such as range reversal.

Since the value range is usually much larger than the number of elements, building the full tree directly is often not possible. If all elements are known in advance, [discretize](../misc/discrete.md) the value range and build an ordinary segment tree. Otherwise, use dynamic node allocation. In the latter case, the information of nodes for values that never appear is exactly the identity element, which is the simplest case described above.

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/seg/seg-as-bst.cpp:seg-tree"
    ```

The value-domain segment tree is also the most common basis for extensions such as the [persistent segment tree](./persistent-seg.md) and segment tree merging. The former can query the $k$-th smallest value in a range of a sequence; the latter can merge two sets efficiently.

## Extensions

Segment trees are used very widely. Common extensions and variants include:

-   [Persistent segment tree](./persistent-seg.md)
-   Various trees of trees:
    -   [Segment tree of segment trees](./seg-in-seg.md)
    -   [Fenwick tree of segment trees](./seg-in-bit.md)
    -   [Segment tree of balanced trees](./balanced-in-seg.md)
    -   [Balanced tree of segment trees](./seg-in-balanced.md)
-   [Li Chao tree](./li-chao-tree.md)
-   [Cat tree](./cat-tree.md)
-   [Segment tree beats (Ji Driver segment tree)](./seg-beats.md)

See the corresponding pages for details.

## Example problems

The sections above covered the basic ideas of segment trees and gave several template implementations. But segment trees can be implemented in very flexible ways, and the reference implementations in this section do not stick strictly to the templates.

???+ example "[Library Checker - Point Add Range Sum](https://judge.yosupo.jp/problem/point_add_range_sum)"
    Given an array, perform the following operations:
    
    -   Add $x$ to the $p$-th number.
    -   Find the sum of the elements in $[l,r)$.

??? note "Solution"
    Just implement a segment tree with point updates and range queries.
    
    === "Implementation 1"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-2.cpp"
        ```
    
    === "Implementation 2"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-3.cpp"
        ```

???+ example "[Luogu P3372 \[Template\] Segment Tree 1](https://www.luogu.com.cn/problem/P3372)"
    Given an array, perform the following two operations:
    
    -   Add $k$ to every number in a range.
    -   Find the sum of all numbers in a range.

??? note "Solution"
    Just implement a segment tree with range updates and range queries. Note that to support range addition, you need to keep the current interval length as part of the range information, or compute it from the interval endpoints during a range update.
    
    === "Implementation 1"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-5.cpp"
        ```
    
    === "Implementation 2"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-4.cpp"
        ```

???+ example "[Luogu P3373 \[Template\] Segment Tree 2](https://www.luogu.com.cn/problem/P3373)"
    Given an array, perform the following three operations:
    
    -   Multiply every number in a range by $x$.
    -   Add $x$ to every number in a range.
    -   Find the sum of all numbers in a range.

??? note "Solution"
    Just implement a segment tree with range updates and range queries. You can directly implement range affine transformations to support both range addition and range multiplication. If you use two lazy tags to record addition and multiplication separately, pay attention to the order in which the two tags are pushed down.
    
    === "Implementation 1"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-7.cpp"
        ```
    
    === "Implementation 2"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-6.cpp"
        ```

???+ example "[SPOJ GSS3 - Can you answer these queries III](https://www.spoj.com/problems/GSS3/)"
    Given an array, perform the following operations:
    
    -   Set the $x$-th number to $y$.
    -   Find the maximum non-empty subarray sum in $[x,y]$.

??? note "Solution"
    Just implement a segment tree with point updates and range queries. [Earlier](#range-information) we analyzed how to maintain the maximum non-empty subarray sum. In this problem, merging information is no longer commutative, so pay attention to the merge order in the implementation.
    
    ```cpp
    --8<-- "docs/ds/code/seg/seg-1.cpp"
    ```

???+ example "[Luogu P13825 \[Template\] Segment Tree 1.5](https://www.luogu.com.cn/problem/P13825)"
    A sequence $\{a_i\}$ of length $n\le 10^9$ starts with $a_i = i$. Perform the following operations:
    
    -   Add $k$ to every number in a range.
    -   Find the sum of all numbers in a range.

??? note "Solution"
    Since $n$ is too large, we cannot build the tree directly and need dynamic node allocation. Also, the information of an interval that has never been modified is not the identity element, so the information of an empty node must be computed from its interval endpoints, and new nodes must be initialized the same way. This also means that pushing down tags and merging children's information both need the current interval's endpoints passed in.
    
    For this particular problem, we can also compute the contribution of the initial values separately and let the segment tree maintain only the increments of the elements. Then the sum of increments of an empty node is $0$, which is exactly the identity element, so creating nodes and merging information no longer need the interval endpoints. But applying a range addition still needs the interval length, so it must come from the recursion parameters and cannot be part of the range information.
    
    Since this problem does not force online processing, we can also store all operations first, discretize the endpoints, and then use an ordinary segment tree. After discretization, each leaf corresponds to a contiguous block of the original sequence, and its information must be initialized from that block's length and the sum of its elements.
    
    === "Implementation 1"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-8.cpp"
        ```
    
    === "Implementation 2"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-9.cpp"
        ```
    
    === "Implementation 3"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-10.cpp"
        ```

???+ example "[Luogu P5490 \[Template\] Sweep Line & Area of Union of Rectangles](https://www.luogu.com.cn/problem/P5490)"
    Find the area of the union of $n$ rectangles whose sides are parallel to the coordinate axes.

??? note "Solution"
    This is a template problem for the [sweep line](../geometry/scanning.md#area-of-a-union-of-rectangles-in-2d). For details of how the sweep line transforms the problem, see the linked page; here we only discuss the data structure needed afterward. After the transformation, we need a structure that supports adding to or subtracting from the cover count over a range: each operation adds one or subtracts one from the cover count of some range, and each query asks for the total length of positions with cover count at least one.
    
    Consider implementing these range operations with a segment tree. A natural idea is to store at each node the cover count of the interval and the total length with cover count at least one. But once a whole interval is covered, the coverage of its subintervals is lost from the total length, and when this layer of coverage is later removed, there is no way to recover it. The fix is to record the two kinds of things separately: the cover count only counts operations that cover exactly this whole interval, and the total length only counts the covered length recorded in the descendants. Then the actual covered length of the interval is the interval length if the cover count is positive, and the recorded total length otherwise. When merging, add up the actual lengths computed for the two children to get this node's total length. With this, the cover count cannot be pushed down, because the addition and the removal of each cover land on the same set of nodes, and they can cancel each other out only if the counts stay where they are. This is exactly permanent tags.
    
    Of course, this problem can also be solved with the segment tree template from earlier. Let the range information be the minimum cover count in the interval, together with the total length of the parts that attain this minimum. It is easy to check that this information space is a monoid, and adding to or subtracting from the cover count is an endomorphism of it, so range updates and range queries can follow the template directly. To get the total covered length, subtract the length of the parts with cover count zero from the length of the whole interval; the latter is the recorded length if the minimum cover count is zero, and zero otherwise.
    
    === "Implementation 1"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-11.cpp"
        ```
    
    === "Implementation 2"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-12.cpp"
        ```

???+ example "[Luogu P2894 \[USACO08FEB\] Hotel G](https://www.luogu.com.cn/problem/P2894)"
    There are $n$ rooms, all empty at first. Perform the following operations:
    
    -   Find $x$ consecutive empty rooms. If they exist, check guests into them.
    -   Check out rooms $[x,x+y-1]$.
    
    For each operation of the first type, output the smallest room number of the $x$ consecutive empty rooms; if there are none, output $0$.

??? note "Solution"
    Build a segment tree that maintains the maximum length of consecutive empty rooms in each interval. To merge this information, also maintain the longest empty prefix, the longest empty suffix and the interval length: a run of empty rooms crossing the midpoint is exactly the longest suffix of the left half joined with the longest prefix of the right half. The lazy tag only needs range assignment, that is, setting a whole range to empty or occupied; "no change" is stored as a special value (for example $-1$). To find the smallest available room number, find the smallest $r$ such that the maximum length of consecutive empty rooms in $[1,r]$ is at least $x$; the room number is then $r-x+1$. This can be done with binary search on the segment tree.
    
    ```cpp
    --8<-- "docs/ds/code/seg/seg-13.cpp"
    ```

???+ example "[Luogu P1168 Median](https://www.luogu.com.cn/problem/P1168)"
    Given an array of length $n$. For every odd $i\le n$, output the median of the first $i$ numbers.

??? note "Solution"
    The median depends only on the relative order of the elements, not on their positions in the array, so a value-domain segment tree can maintain it. Insert the elements one by one, and after inserting an odd number of them, query the $(i+1)/2$-th smallest element. You only need two operations: insertion and the $k$-th smallest query.
    
    ```cpp
    --8<-- "docs/ds/code/seg/seg-14.cpp"
    ```

## Exercises

Basic implementation and designing range information:

-   [Luogu P2574 The Art of XOR](https://www.luogu.com.cn/problem/P2574)
-   [Luogu P4588 \[TJOI2018\] Mathematical Calculation](https://www.luogu.com.cn/problem/P4588)
-   [Luogu P1253 Fusu's Problem](https://www.luogu.com.cn/problem/P1253)
-   [Luogu P1471 Variance](https://www.luogu.com.cn/problem/P1471)
-   [Luogu P4513 Xiaobai Strolls in the Park](https://www.luogu.com.cn/problem/P4513)
-   [Luogu P2572 \[SCOI2010\] Sequence Operations](https://www.luogu.com.cn/problem/P2572)

Dynamic node allocation:

-   [Codeforces 915 E. Physical Education Lessons](https://codeforces.com/problemset/problem/915/E)
-   [Library Checker - Range Affine Range Sum (Large Array)](https://judge.yosupo.jp/problem/range_affine_range_sum_large_array)
-   [Codeforces 817 F. MEX Queries](https://codeforces.com/problemset/problem/817/F)

Permanent tags:

-   [Luogu P1502 Stars in a Window](https://www.luogu.com.cn/problem/P1502)
-   [2018 Multi-University Training Contest 5 G. Glad You Came](https://acm.hdu.edu.cn/showproblem.php?pid=6356)

Binary search on a segment tree:

-   [AtCoder Library Practice Contest J - Segment Tree](https://atcoder.jp/contests/practice2/tasks/practice2_j)
-   [AtCoder Beginner Contest 292 Ex - Rating Estimator](https://atcoder.jp/contests/abc292/tasks/abc292_h)
-   [Luogu P4137 Rmq Problem/mex](https://www.luogu.com.cn/problem/P4137)
-   [Codeforces 773 E. Blog Post Rating](https://codeforces.com/problemset/problem/773/E)
-   [Codeforces 407 E. k-d-sequence](https://codeforces.com/problemset/problem/407/E)
-   [Codeforces 671 E. Organizing a Race](https://codeforces.com/problemset/problem/671/E)

Value-domain segment tree:

-   [Luogu P1908 Inversions](https://www.luogu.com.cn/problem/P1908)
-   [Luogu P1801 Black Box](https://www.luogu.com.cn/problem/P1801)
-   [Luogu P1637 Increasing Triples](https://www.luogu.com.cn/problem/P1637)
-   [Luogu P2286 \[HNOI2004\] Pet Adoption Center](https://www.luogu.com.cn/problem/P2286)

## Application: optimizing graph construction with a segment tree

When building a graph, we sometimes meet problems where a vertex must be connected to every vertex in a contiguous range, or every vertex in a contiguous range must be connected to one vertex. If we really add the edges one by one, the complexity blows up once there are many vertices. Here we can use the interval structure of a segment tree to optimize the graph construction.

Below is a segment tree.

![](./images/segt5.svg)

Each node represents an interval. Suppose we want to add edges to the range $[2, 4]$.

![](./images/segt6.svg)

Some problems also have edges from a range to a single vertex. In that case, just reverse all directed edges in the first figure above. The tree above is called the "in" tree, and the one below is called the "out" tree.

![](./images/segt7.svg)

???+ note "[Legacy](https://codeforces.com/problemset/problem/786/B)"
    Summary: there are $n$ vertices and $q$ operations. Each operation is one of the following three types:
    
    -   Type 1: add a directed edge $u \rightarrow v$ with weight $w$.
    -   Type 2: for every $i \in [l,r]$, add a directed edge $u \rightarrow i$ with weight $w$.
    -   Type 3: for every $i \in [l,r]$, add a directed edge $i \rightarrow u$ with weight $w$.
    
    Find the shortest paths from vertex $s$ to all other vertices.
    
    $1 \le n,q \le 10^5, 1 \le w \le 10^9$.
    
    ??? note "Reference code"
        ```cpp
        --8<-- "docs/ds/code/seg/seg_8.cpp"
        ```

## References and notes

-   [The Power of Statistics - Zhang Kunwei](https://github.com/hzwer/shareOI/blob/master/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/%E7%BB%9F%E8%AE%A1%E7%9A%84%E5%8A%9B%E9%87%8F%E2%80%94%E2%80%94%E7%BA%BF%E6%AE%B5%E6%A0%91%E5%85%A8%E6%8E%A5%E8%A7%A6_%E5%BC%A0%E6%98%86%E7%8E%AE.pptx)
-   [Generalizing Segment Trees by Eklavya](https://sharmaeklavya2.github.io/blog/generalizing-segment-trees.html)
-   [Advanced Segment Trees Part 1 by Alex\_Wei - Luogu](https://www.luogu.com.cn/article/r1mp3hga)

[^monoid]: Strictly speaking, the information maintained by a segment tree only needs to form a semigroup; an identity element is not required. The recursive implementation uses the identity element mainly because a range query uses it as the initial value of the accumulated information; this can be avoided by handling the intersection cases separately. However, the extra leaves in the non-recursive implementation and the empty nodes in dynamic allocation cannot avoid the identity element. Even when it is truly needed, we can always add an element $e$ to a semigroup $S$ and define its operation with any element to give that element itself, which gives a monoid $S\cup\{e\}$. For convenience, this article always assumes the information is a monoid.

[^endo]: As in the discussion of range information, in many implementations the identity element is never given as input to an update, so this property is not needed; it is enough for the update to be an endomorphism of a semigroup. However, in the non-recursive implementation of permanent tags later, the accumulated information starts from the identity element and has the tags along the path applied level by level, so this property cannot be ignored. For convenience, this article always assumes updates are endomorphisms of a monoid.

[^child-id]: In fact, when nodes are numbered in preorder as in the figure, the right child's index can be computed from the current node's index and the size of the left subtree, and the size of the left subtree can be computed from the interval length. Since recursive visits of segment tree nodes usually keep track of the interval's endpoints, the right child's index can also be computed directly.

[^heap-size]: Consider the ratio between the space taken by the binary tree, $2^{\lceil\log_2N\rceil+1}$, and the segment tree size $N$. The former depends only on the height of the binary tree. When the segment tree has height $k$, its smallest possible size is $N = 2^{k-1}+1$. The ratio is then $(4N-4)/N = 4 - 4/N$, whose supremum is $4$. This is why, to store a segment tree of size $N$, we allocate an array of size $4N$ for the corresponding perfect binary tree.

[^assign]: Range assignment itself is not commutative. If we also record a timestamp $t$ for each assignment, and define the composition of tags $(v_1,t_1)$ and $(v_2,t_2)$ as the one with the larger timestamp, we get commutative tags. With this trick, we can build a permanent-tag segment tree that supports range assignment and point queries: during a query, take the tag with the largest timestamp along the path and apply it to the leaf. However, it cannot support range queries, because $(v,t)$ is not an endomorphism of the information space: from the information of an interval alone, we cannot tell which positions have already been overwritten by later assignments.
