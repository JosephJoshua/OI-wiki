author: Ir1d, 0xis-cn

## Introduction

A **scapegoat tree** is a weight-balanced tree that stays balanced by rebuilding. After each insertion or deletion, a scapegoat tree checks whether the tree has become unbalanced; if so, it rebuilds a chosen part of the tree to restore balance.

In general, scapegoat trees do not support range operations and cannot be made fully persistent, but they are simple to implement and have a small constant factor.

## Basic structure and operations

The core operations of a scapegoat tree are rebuilding, insertion and deletion.

### Node information

A scapegoat tree stores the following information, used to keep the tree balanced:

-   Tree structure:
    -   `id`: the number of nodes used;
    -   `rt`: the root;
    -   `lc[x]`, `rc[x]`: the left and right children;
    -   `tot[x]`: the size of the subtree rooted at $x$ (each node counts as $1$)[^tot-cnt];
    -   `tot_active`: the number of nodes in the whole tree that are not deleted (that is, `cnt[x] != 0`).

When a scapegoat tree is used as a balanced binary search tree, it also stores the following:

-   Node information for the balanced tree:
    -   `val[x]`: the value stored at the node;
    -   `cnt[x]`: the count of the value stored at the node (may be $0$);
    -   `sz[x]`: the total count of values stored in the subtree rooted at $x$.

To maintain the node information, we can write a `push_up` operation:

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/sgt/sgt.cpp:push-up"
    ```

Note that `tot[x]` and `sz[x]` are updated differently.

### Rebuilding

When the tree becomes unbalanced, we rebuild some subtree to make it as balanced as possible. Rebuilding has two steps:

-   Do an in-order traversal of the subtree to be rebuilt and store all non-deleted nodes in a sequence;
-   Build the tree by halving: take the middle element as the root, build the left and right subtrees recursively from the two sides, and update the node information.

The reference implementation is as follows:

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/sgt/sgt.cpp:rebuild"
    ```

When building, remember to maintain the node information, including that of the leaves.

A single rebuild costs $\Theta(|T_x|)$, so rebuilding on every insertion and deletion would be far too slow. The core idea of the scapegoat tree is choosing when to rebuild, which gives $O(\log n)$ amortized complexity.

### Insertion

An insertion may make the tree unbalanced. To decide whether the tree is unbalanced, we introduce a parameter $\alpha\in(0.5,1)$, usually chosen in the range $0.7\sim 0.8$.

If the depth of the newly inserted node exceeds $\lfloor\log_{1/\alpha}|T|\rfloor$, where $|T|$ is the size of the tree after the update, then while returning up we look for the node where the imbalance happens and rebuild it. The subtree rooted at $x$ is considered unbalanced when

$$
\max\{|T_{\mathrm{left}(x)}|,|T_{\mathrm{right}(x)}|\} > \alpha\cdot |T_x|,
$$

where $\mathrm{left}(x)$ and $\mathrm{right}(x)$ are the left and right children of $x$, and $|T_x|$ is the size of the subtree rooted at $x$.

An insertion works as follows:

-   First go down using the binary search tree property to find where the value goes, recording the depth on the way down;
-   If a node with this value already exists, update its information directly; otherwise create a new node;
-   Go back up to the root, updating node information; if the new node is too deep, also record the first (or any) node on the way up whose subtree is unbalanced;
-   If there is an unbalanced node, rebuild its subtree.

The reference implementation is as follows:

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/sgt/sgt.cpp:insert"
    ```

Note that a single insertion causes at most one rebuild. If no node was added, or the new node is not too deep, or a rebuild has already happened on the way up, there is no need to keep checking for imbalance. Extra rebuilds may cost efficiency[^insert-complexity]. The first unbalanced node on the way up is the so-called "scapegoat".

### Deletion

Deletion is very simple. A scapegoat tree uses "lazy deletion": when a node becomes empty, it is not removed but left to be dealt with later.

Of course, if the tree has too many empty nodes, accessing it becomes much slower. So the scapegoat tree keeps two counts: the number of non-deleted nodes in the whole tree, and the number of nodes the tree actually uses. For a chosen threshold[^threshold] $\alpha\in(0,1)$, when the ratio of the former to the latter drops below $\alpha$, the whole tree is rebuilt once, removing all empty nodes.

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/sgt/sgt.cpp:remove"
    ```

### Time complexity

In a scapegoat tree of size $n$, a single node access takes $O(\log n)$ time; $\Theta(n)$ insertions and deletions also take $O(\log n)$ amortized time each.

This section only gives a brief argument for the time complexity of the scapegoat tree; see the original paper for a detailed proof.

??? note "Argument for the time complexity of the scapegoat tree"
    Because of lazy deletion, a scapegoat tree with $n$ non-deleted nodes may occupy $\alpha^{-1}n$ nodes. Since these differ only by a constant factor, this article does not distinguish between the number of non-deleted nodes and the number of occupied nodes, and calls both "the size of the tree".
    
    1.  **Access**: access complexity is guaranteed because a scapegoat tree of size $n$ always has height $O(\log n)$.
    
        First, distinguish two concepts:
    
        -   $\alpha$‑weight-balanced: at every node, the sizes of the subtrees of the left and right children are at most $\alpha$ times the size of the subtree at that node;
        -   $\alpha$‑height-balanced: the height of the tree is at most $\lfloor\log_{1/\alpha}|T|\rfloor$, where $|T|$ is the size of the tree.
    
        $\alpha$‑weight-balance implies $\alpha$‑height-balance, because each time the depth increases by one, the subtree size shrinks to at most $\alpha$ times what it was; the converse is not necessarily true. More precisely, after every operation, the scapegoat tree is always $\alpha$‑height-balanced[^hei-bal], which guarantees the access complexity.
    
        Only insertion changes the structure of the tree, so we only need to show that the scapegoat tree is still $\alpha$‑height-balanced after every insertion. If the newly inserted node is too deep, so that the whole tree is no longer $\alpha$‑height-balanced, then on the way from that node back to the root we meet at least one node, the "scapegoat", whose subtree is no longer $\alpha$‑weight-balanced. After rebuilding it, the height of that subtree drops by at least one, so the new node is no longer too deep.
    2.  **Insertion**: insertion takes $O(\log n)$ amortized time.
    
        Suppose that after some insertion, the subtree at node $x$ is rebuilt, at a cost of $\Theta(|T_x|)$. When node $x$ was just inserted, or right after its previous rebuild (of itself or of an ancestor), its left and right subtrees differed by at most one node. And right before this rebuild, node $x$ must satisfy
    
        $$
        \max\{|T_{\mathrm{left}(x)}|,|T_{\mathrm{right}(x)}|\} > \alpha\cdot |T_x|.
        $$
    
        This condition guarantees that the sizes of the left and right subtrees differ by at least $(2\alpha-1)|T_x|$. So between these two rebuilds, $\Omega(|T_x|)$ nodes were inserted into subtree $T_x$.
    
        By amortized analysis[^alternative-analysis]: if each insertion adds $\Theta(1)$ potential at every node on the path from the root to the inserted node (before any possible rebuild), then by the time the subtree at $x$ is rebuilt, $\Omega(|T_x|)$ potential has built up at node $x$, which is enough to pay for the cost $\Theta(|T_x|)$ of rebuilding the subtree at $x$. Since the tree depth is always $O(\log n)$, a single insertion adds $O(\log n)$ potential; so the total potential added by $\Theta(n)$ insertions is $O(n\log n)$. Therefore the total cost of rebuilding subtrees is also $O(n\log n)$, and a single insertion (including rebuilding) takes $O(\log n)$ amortized time.
    
        Note that the analysis does not assume that no other rebuilds happen inside subtree $T_x$ between the two rebuilds at node $x$. So as long as we only rebuild subtrees at nodes that meet the imbalance condition, the complexity is correct.
    3.  **Deletion**: deletion also takes $O(\log n)$ amortized time.
    
        A rebuild caused by deletion leaves the whole tree with no empty nodes. Before some deletion causes a rebuild, the tree already has $\Theta(n)$ empty nodes, which means at least $\Theta(n)$ deletions have been done. Each deletion takes $O(\log n)$ to locate its node, and a single rebuild costs $\Theta(n)$, so the actual total cost of these $\Theta(n)$ deletions is
    
        $$
        \Theta(n)O(\log n)+\Theta(n)
        $$
    
        So a single deletion takes $O(\log n)$ amortized time.

## Balanced tree operations

This section shows how to maintain a multiset with a scapegoat tree.

Apart from the operations in the previous section, the other operations are the usual ones of a balanced binary search tree. But because a scapegoat tree may contain empty nodes, these operations need some adjustment.

### Finding the rank

Go down using the binary search tree property to find the node's position, and count the number of values stored on the left side of the path along the way.

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/sgt/sgt.cpp:find-rank"
    ```

### Finding the value with a given rank

Go down using the subtree value counts recorded at the nodes. Note that there may be nodes whose count is zero.

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/sgt/sgt.cpp:find-kth"
    ```

### Finding the predecessor and successor

Just combine the two operations above.

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/sgt/sgt.cpp:pred-succ"
    ```

If you want to implement them directly, remember to handle nodes whose count is zero.

### Reference implementation

To end this section, here is a reference implementation for the template problem [Ordinary Balanced Tree](https://loj.ac/p/104).

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/sgt/sgt.cpp:full-text"
    ```

## References

-   Galperin, Igal, and Ronald L. Rivest. "Scapegoat trees." Proceedings of the fourth annual ACM-SIAM Symposium on Discrete algorithms. 1993.
-   [Scapegoat Tree - Wikipedia](https://en.wikipedia.org/wiki/Scapegoat_tree)
-   [Scapegoat Tree - riteme's blog](https://riteme.site/blog/2016-4-6/scapegoat.html)

[^tot-cnt]: You can also count only the non-deleted nodes. Then you no longer need `tot_active`, but you need the number of all occupied nodes, `tot_max`, and the code changes accordingly.

[^insert-complexity]: By the complexity analysis below, this loss of efficiency only means a larger constant factor; the complexity is still correct. Since checking the tree depth may involve many floating-point logarithms, code that skips the depth check and only checks for imbalance may be faster on some data.

[^threshold]: It need not be the same as the parameter chosen for insertion above. Although the original paper makes this assumption, choosing a different parameter only changes the constant in the cost of a single operation; the overall complexity is still correct.

[^hei-bal]: Under the original paper's definition, $n$ is the number of non-deleted nodes, so it can only guarantee that the height is at most $\lfloor\log_{1/\alpha}n\rfloor+1$. This is called weak $\alpha$‑height-balance. We do not look closely at this difference in the constant term here.

[^alternative-analysis]: Some articles simply argue that $\Omega(|T_x|)$ insertions correspond to one rebuild, so the amortized complexity is $\dfrac{\Omega(|T_x|)O(\log n)+\Theta(|T_x|)}{\Omega(|T_x|)} = O(\log n)$. This helps explain why the amortized complexity is right, but it is not rigorous. The reason is that one insertion may correspond to rebuilds at several ancestors, so when node $x$ is rebuilt, it is not obvious that the number of nodes in its subtree that did not cause a rebuild is $\Omega(|T_x|)$.
