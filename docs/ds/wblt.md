author: hsfzLZH1, cesonic, AtomAlpaca, caijianhong, Persdre, aofall, CoelacanthusHex, Marcythm, shuzhouliu, Tiphereth-A

## Introduction

**Weight Balanced Leafy Tree**, called **WBLT** below, is a kind of balanced tree. Compared with other balanced trees, its main advantages are simple implementation and a small constant factor. It supports range operations and can be made persistent.

As the name suggests, a Weight Balanced Leafy Tree combines a Weight Balanced Tree and a Leafy Tree.

In a Weight Balanced Tree, each node stores the size of its subtree, and the tree height is kept small by keeping the sizes of the left and right subtrees within a certain ratio of each other.

In a Leafy Tree, the original data is stored only in the **leaves** of the tree. Non-leaf nodes are only used to maintain information about their children and to hold the shape of the structure. The segment tree we know well is a kind of Leafy Tree.

![](images/leafy-tree-1.svg)

In this article, "tree" always means a binary Leafy Tree, i.e., every node has either $0$ or $2$ children. Here $n$ means the number of leaves in the tree. A tree with $n$ leaves has $2n-1$ nodes in total, so a WBLT uses $\Theta(n)$ space.

## Basic structure and keeping balance

This section introduces the basic structure of a WBLT, defines what it means for a tree to be $\alpha$‑balanced, and explains how to keep the tree balanced by rotation or by merging.

### Node information

To implement a basic WBLT, each node only needs to record the following:

-   `lc[x]`, `rc[x]`: the left and right children;
-   `sz[x]`: the number of leaves in the subtree rooted at $x$.

To use a WBLT as a balanced tree, each node also needs to store information about keys:

-   `val[x]`: the key at node $x$.

Only leaves actually store keys, so the information at other nodes is obtained by combining their children, to make later queries easier.

For example, a common way to combine is to store the larger of the two children's keys at the node. Then each node stores the maximum key among all leaves in its subtree. Based on this, a node's information is updated as follows:

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:push-up"
    ```

Of course, you can also implement a matching `push_down(x)` function if needed.

### Helper functions

Besides maintaining the basic node information, a WBLT usually also needs the following helper functions for memory management:

-   `new_node()`: create a new node;
-   `del_node(x)`: delete node $x$;
-   `new_leaf(v)`: create a new leaf with key $v$;
-   `join(x, y)`: join subtrees, i.e., create a new node $z$ with $x$ and $y$ as its left and right children;
-   `cut(x)`: cut a subtree apart, i.e., get the two children of node $x$ and delete node $x$.

If a WBLT implementation relies heavily on cutting and joining subtrees, it creates many new nodes and frees an equal number of old ones. If the old unused nodes are not recycled in time, the space usage will no longer be linear. Here is an array implementation of these helper functions:

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:helper"
    ```

Once these helper functions are wrapped up, the array implementation and the pointer implementation look the same in all later functions.

### What balance means

For a tree, define its **balance** at a non-leaf node $x$ as

$$
\rho(x) = \dfrac{\min\{w(T_{\operatorname{left}(x)}),w(T_{\operatorname{right}(x)})\}}{w(T_x)}.
$$

Here $T_x$ is the subtree rooted at $x$, $w(\cdot)$ is the weight of a subtree (its number of leaves), and $\operatorname{left}(x)$ and $\operatorname{right}(x)$ are the left and right children of $x$. In particular, at a leaf we define $\rho(x)=1/2$.

For $\alpha\in(0,1/2]$, if the balance at some node $x$ satisfies $\rho(x)\ge\alpha$, we say the node is **$\alpha$‑balanced**. If every node of a tree is $\alpha$‑balanced, we say the tree is **$\alpha$‑balanced**. The set of such trees is written $BB[\alpha]$. A tree is **$\alpha$‑balanced** if and only if it is a leaf, or its root is $\alpha$‑balanced and both its left and right subtrees are $\alpha$‑balanced.

An obvious benefit of an $\alpha$‑balanced tree is that its height is $O(\log n)$. This is because each step from a leaf toward the root multiplies the number of leaves in the subtree by at least $1/(1-\alpha)$, so we can take only $O(\log_{\frac{1}{1-\alpha}}n) = O(\log n)$ steps. This guarantees that in an $\alpha$‑balanced tree, a single query always takes strictly $O(\log n)$ time, and the constant factor of the algorithm is inversely proportional to $\log(1/(1-\alpha))$ (base $2$). When $\alpha$ is in the reasonable range given below, this constant is roughly $2\sim 3.5$.

A WBLT is usually kept balanced either by rotation or by merging. With either method, a single insertion, deletion and so on takes strictly $O(\log n)$ time. However, unlike a [Treap](./treap.md) with fixed priorities, the structure of a WBLT is not unique, so the two methods produce trees with different shapes, though this does not affect how they are used. Of course, balance can also be kept with a strategy like the [scapegoat tree](./sgt.md), using rebuilding to get amortized $O(\log n)$ complexity, but then the WBLT loses its advantages such as persistence and range operations, so this is not recommended.

Below we introduce keeping balance by rotation and by merging, and implement the corresponding functions for maintaining balance and for merging. Once these functions are wrapped up, the two ways of keeping the tree balanced make no difference in the rest of the balanced tree implementation. Moreover, with either method, a single balancing step takes $O(1)$ time, and merging trees $T_1$ and $T_2$ once takes $O\left(\left|\log\dfrac{w(T_1)}{w(T_2)}\right|\right)$ time.

???+ info "Notation that omits the weight"
    To keep the tree balanced, we only need the weight of each subtree. So for convenience, the next two sections on keeping balance use the same notation for a tree and its weight. For example, the weight of subtree $x$ is also written $x$, not $w(x)$. Similarly, the tree obtained by merging subtrees $x$ and $y$ is also denoted by its weight, written directly as the tree $x+y$.

### Keeping balance by rotation

Rotation in a WBLT is exactly the same as [rotation in a Treap](./treap.md#旋转), and we can use exactly the same rotation strategy as in a Treap. Of course, a rotation can also be seen as redistributing subtree weights, so it can also be done by cutting and joining subtrees. The two implementations give exactly the same result, but the second one makes it easier to make a WBLT persistent.

???+ example "Reference code"
    === "Without joining"
        ```cpp
        --8<-- "docs/ds/code/wblt/wblt-1.cpp:rotate-not-by-joining"
        ```
    
    === "With joining"
        ```cpp
        --8<-- "docs/ds/code/wblt/wblt-1.cpp:rotate-by-joining"
        ```

Suppose that after some modification of the tree, we are restoring balance from the bottom up. Now the left and right subtrees $x$ and $y$ are no longer balanced with each other, but each of them is balanced. Without loss of generality, suppose the right subtree $y$ is too light, i.e., $y<\alpha(x+y)$. The tree then looks like the tree on the left of the figure.

![](images/wblt-balance.svg)

A simple balancing strategy is to rotate $x$ up to the root. Then its old right child $w$ becomes, together with $y$, the right child of the new tree, and its old left child $z$ becomes the left child of the new tree. This amounts to moving the weight of $w$ from the left side of the old tree to its right side. If $w$ has a suitable weight, this restores balance. The resulting tree is shown on the right of the figure.

However, if $w$ itself is too heavy, this may move too much weight to the right subtree, so the left subtree of the new tree becomes too light, i.e., $z<\alpha(x+y)$. In this case, since both subtree $z$ and subtree $y$ are too light, the only option is to split $w$ into two subtrees, join them with $z$ and $y$ respectively, and make those the two subtrees of the new tree. This amounts to first rotating node $w$ up to node $x$, and then rotating it up to the root. Again, we can expect the resulting tree to be balanced; it is shown in the middle of the figure.

These two strategies are called single rotation and double rotation. Which one to use depends mainly on the weight of subtree $w$ relative to subtree $x$: there is a threshold $\beta$ such that

-   when $w\le\beta x$, use a single rotation;
-   when $w>\beta x$, use a double rotation.

The hard part is choosing the threshold $\beta$, which needs some concrete calculation. Blum and Mehlhorn proved that for the parameters[^wrong-range]

$$
\alpha\in\left(\dfrac{2}{11},1-\dfrac{\sqrt{2}}{2}\right]\approx(0.182,0.292],~\beta=\frac{1}{2-\alpha},
$$

the combined single/double rotation strategy above can restore the balance of a WBLT that became unbalanced after a single insertion or deletion.

??? note "Proof"
    We need to prove that if the tree becomes unbalanced after a single insertion or deletion, the strategy above restores its balance. With the figure above, let
    
    $$
    \rho_1 = \dfrac{y}{x+y}, ~\rho_2 = \dfrac{w}{x}, ~\rho_3 = \dfrac{v}{w}.
    $$
    
    Then $\rho_1<\alpha\le\rho_2,\rho_3\le 1-\alpha$. There is also a hidden condition on the range of $\rho_1$:
    
    -   If the imbalance was caused by inserting one element, then
    
        $$
        \dfrac{y}{x-1+y} \ge \alpha \implies \rho_1 \ge \dfrac{\alpha y}{y+\alpha} \ge \dfrac{\alpha}{1+\alpha}.
        $$
    -   If the imbalance was caused by deleting one element, then
    
        $$
        \dfrac{y+1}{x+y+1} \ge \alpha \implies \rho_1 \ge \dfrac{\alpha y}{y+1-\alpha} \ge \dfrac{\alpha}{2-\alpha}.
        $$
    
    Since $\alpha/(2-\alpha)<\alpha/(1+\alpha)$ always holds for $0<\alpha<1/2$, deleting an element can cause a worse imbalance than inserting one, especially when the tree is small.
    
    Next, restoring balance splits into two cases:
    
    ??? note "Case 1: $w$ is not too heavy, i.e., $\rho_2\le\beta$: single rotation"
        First, $z$ and $w+y$ are balanced, because
        
        $$
        \left(1-\dfrac{\alpha}{2-\alpha}\right)\alpha+\dfrac{\alpha}{2-\alpha} \le \dfrac{w+y}{x+y} = (1-\rho_1)\rho_2+\rho_1 < (1-\alpha)\dfrac{1}{2-\alpha}+\alpha.
        $$
        
        The left-hand expression is always greater than $\alpha$ for $\alpha\in(0,1)$, and the right-hand expression is always at most $(1-\alpha)$ for $\alpha\in(0,1-\sqrt{2}/2]$.
        
        Second, $w$ and $y$ are balanced. Similarly, consider
        
        $$
        \dfrac{y}{w+y} = \dfrac{\rho_1}{(1-\rho_1)\rho_2+\rho_1}.
        $$
        
        On one hand, for all $\alpha\in(0,(3-\sqrt{5})/2)$,
        
        $$
        \dfrac{y}{w+y} < \dfrac{\alpha}{(1-\alpha)\alpha+\alpha} < 1-\alpha.
        $$
        
        On the other hand, for all $\alpha\in(0,1/3)$, except when an element is deleted and $y=1$, we have
        
        $$
        \rho_1 \ge \min\left\{\dfrac{\alpha}{1+\alpha},\dfrac{2\alpha}{3-\alpha}\right\} = \dfrac{2\alpha}{3-\alpha},
        $$
        
        so
        
        $$
        \dfrac{y}{w+y} \ge \dfrac{\dfrac{2\alpha}{3-\alpha}}{\left(1-\dfrac{2\alpha}{3-\alpha}\right)\dfrac{1}{2-\alpha}+\dfrac{2\alpha}{3-\alpha}} > \alpha.
        $$
        
        Finally, consider the remaining case: an element is deleted and $y=1$. The case most likely to be unbalanced is when $x=\lfloor 2/\alpha\rfloor-2$ and $w=\lfloor\beta x\rfloor$. The tree can be rebalanced if and only if
        
        $$
        \dfrac{1}{1+\lfloor\beta x\rfloor}\ge\alpha \iff \lfloor\beta x\rfloor\le\dfrac{1}{\alpha}-1 \iff \beta x < \dfrac{1}{\alpha} \iff x < \dfrac{2}{\alpha}-1.
        $$
        
        and this always holds. This completes the proof of this case. Note that the proof of the last case uses the fact that weights are always integers, so it cannot be merged into the earlier argument.
    
    ??? note "Case 2: $w$ is too heavy, i.e., $\rho_2>\beta$: double rotation"
        First, $z+u$ and $v+y$ are balanced, because
        
        $$
        \dfrac{\alpha}{2-\alpha}+\left(1-\dfrac{\alpha}{2-\alpha}\right)\dfrac{1}{2-\alpha}\alpha < \dfrac{v+y}{x+y} = \rho_1+(1-\rho_1)\rho_2\rho_3 <\alpha+(1-\alpha)^3
        $$
        
        The left-hand expression is always greater than $\alpha$ for $\alpha\in(0,1)$, and the right-hand expression is always less than $(1-\alpha)$ for $\alpha\in(0,(3-\sqrt{5})/2)$.
        
        Next, $z$ and $u$ are balanced, because for $\alpha\in(0,1)$ it always holds that
        
        $$
        \alpha=\dfrac{\dfrac{1}{2-\alpha}\alpha}{1-\dfrac{1}{2-\alpha}(1-\alpha)}<\dfrac{u}{z+u} = \dfrac{\rho_2(1-\rho_3)}{1-\rho_2\rho_3} <\dfrac{(1-\alpha)^2}{1-(1-\alpha)\alpha} < 1-\alpha.
        $$
        
        Finally, $v$ and $y$ are balanced. As in the other cases, consider
        
        $$
        \dfrac{y}{v+y} = \dfrac{\rho_1}{\rho_1+(1-\rho_1)\rho_2\rho_3}.
        $$
        
        On one hand, for all $\alpha\in(0,1-\sqrt{2}/2]$,
        
        $$
        \dfrac{y}{v+y} < \dfrac{\alpha}{\alpha+(1-\alpha)\dfrac{1}{2-\alpha}\alpha} \le 1-\alpha.
        $$
        
        On the other hand,
        
        $$
        \dfrac{y}{v+y} \ge \dfrac{\rho_1}{\rho_1+(1-\rho_1)(1-\alpha)^2}.
        $$
        
        The right-hand expression is at least $\alpha$ if and only if
        
        $$
        \rho_1 \ge \dfrac{\alpha(1-\alpha)}{1+\alpha(1-\alpha)}.
        $$
        
        If the imbalance was caused by an insertion, then $\rho_1\ge \alpha/(1+\alpha)$, and this clearly holds. Otherwise, things are a bit more complicated:
        
        -   When $y\ge 3$, $\rho_1\ge 3\alpha/(4-\alpha)$, and $3\alpha/(4-\alpha)\ge\alpha(1-\alpha)/(1+\alpha(1-\alpha))$ holds for all $\alpha\in[1-\sqrt{3}/2,1)$;
        -   When $y=2$, the case most likely to be unbalanced is when $x=\lfloor 3/\alpha\rfloor-3$, $w=\lfloor(1-\alpha)x\rfloor$ and $v=\lfloor(1-\alpha)w\rfloor$; then $y/(v+y)\ge\alpha$ holds for all $\alpha\in(3/22,1)$;
        -   When $y=1$, the case most likely to be unbalanced is when $x=\lfloor 2/\alpha\rfloor-2$, $w=\lfloor(1-\alpha)x\rfloor$ and $v=\lfloor(1-\alpha)w\rfloor$; then $y/(v+y)\ge\alpha$ holds for all $\alpha\in(2/11,1)$.
        
        The last two cases also use the fact that all node weights are integers.
    
    Combining the two cases, when $\alpha\in(2/11,1-\sqrt{2}/2]$, the combined single/double rotation strategy above keeps the tree balanced.
    
    This analysis shows that balance is hardest to keep when deleting nodes from a small tree. For choices of $\beta$ other than $\beta=1/(2-\alpha)$, correctness can be proved by repeating the process above, with some of the inequalities adjusted accordingly.

Later, Hirai and Yamamoto used a computer-assisted proof to fully determine the range of all feasible $(\alpha,\beta)$. The result is a fairly complicated two-dimensional region:

![](images/wblt-param-range.svg)

In their paper, they recommend the following balancing strategy:

-   When $x>3y$, the tree is considered unbalanced;
-   When $w\le 2z$, use a single rotation; otherwise, use a double rotation.

The reason is that this is the only strategy in the feasible parameter range that can be written with simple integers, which avoids the slowdown from floating-point arithmetic. Their recommended strategy is equivalent to $(\alpha,\beta)=(1/4,2/3)$. In practice, you can choose suitable parameters for your situation.

A reference implementation:

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:too-heavy"
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:balance"
    ```

With the balancing strategy in place, merging two trees is very simple. Again assume $x>y$. The merge strategy is:

-   If the right subtree $y$ is empty, return the left subtree $x$ directly;
-   If the left and right subtrees $x$ and $y$ are already balanced, i.e., $y\ge\alpha(x+y)$, join the two subtrees directly;
-   Otherwise, merge the right subtree $w$ of $x$ with $y$, join the left subtree $z$ with the result, and rebalance the new tree.

A reference implementation:

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:merge-by-balancing"
    ```

It can be proved that this keeps the merged tree balanced, and that this takes $O(|\log(x/y)|)$ time.

??? note "Proof of balance and complexity"
    We only need to consider the case where $y$ is too light, i.e., $y<\alpha(x+y)$. Then we first merge $w$ and $y$, and then join $z$ and $w+y$. We need to prove that adjusting the balance at the root is enough to make the tree balanced. Suppose the left and right subtrees of tree $w+y$ are $c$ and $d$, and the left and right subtrees of $c$ are $a$ and $b$. Adjusting the balance at the root falls into three cases:
    
    ??? note "Case 1: $z$ and $w+y$ are already balanced and need no further adjustment, i.e., $z\ge\alpha(x+y)$"
        By the definition of balance, subtrees $z$ and $w+y$ are each balanced and balanced with each other, so the whole tree is balanced.
    
    ??? note "Case 2: $z$ is too light and $c$ is not too heavy, so a single rotation restores balance, i.e., $z<\alpha(x+y)$ and $c\le\beta(w+y)$"
        Here, since $z$ and $w$ are balanced but $y$ is too light compared with $x = z+w$, the weight of subtree $z$ satisfies
        
        $$
        \alpha(1-\alpha)(x+y) <  \alpha(z+w) \le z \le \alpha(x+y) .
        $$
        
        and the weight of $c$ satisfies
        
        $$
        \alpha(w+y) \le c \le \beta(w+y).
        $$
        
        So $z$ and $c$ are balanced with each other as long as
        
        $$
        \dfrac{\alpha}{1-\alpha}<\dfrac{1-\alpha}{\alpha}\alpha<\dfrac{c}{z}=\dfrac{w+y}{z}\dfrac{c}{w+y} < \dfrac{1-\alpha(1-\alpha)}{\alpha(1-\alpha)}\beta\le\dfrac{1-\alpha}{\alpha},
        $$
        
        which requires
        
        $$
        \beta\le \dfrac{(1-\alpha)^2}{1-\alpha(1-\alpha)}.
        $$
        
        and $z+c$ and $d$ are balanced with each other as long as
        
        $$
        \alpha\le (1-\beta)(1-\alpha)\le \dfrac{d}{w+y}\dfrac{w+y}{x+y}  = \dfrac{d}{x+y} < \dfrac{d}{c+d} \le 1-\alpha,
        $$
        
        which requires
        
        $$
        \beta \le \dfrac{1-2\alpha}{1-\alpha}.
        $$
    
    ??? note "Case 3: $z$ is too light and $c$ is too heavy, so a double rotation restores balance, i.e., $z<\alpha(x+y)$ and $c>\beta(w+y)$"
        As in Case 2, we have
        
        $$
        \begin{aligned}
        \alpha(1-\alpha)(x+y) < z &\le \alpha(x+y),\\
        \beta(w+y)<c &\le (1-\alpha)(w+y),\\
        \alpha c\le a,b &\le (1-\alpha)c.
        \end{aligned}
        $$
        
        So $z$ and $a$ are balanced with each other as long as
        
        $$
        \dfrac{\alpha}{1-\alpha}\le\dfrac{1-\alpha}{\alpha}\beta\alpha\le\dfrac{a}{z} = \dfrac{w+y}{z}\dfrac{a}{c+d} < \dfrac{1-\alpha(1-\alpha)}{\alpha(1-\alpha)}(1-\alpha)^2,
        $$
        
        which requires
        
        $$
        \beta\ge\dfrac{\alpha}{(1-\alpha)^2}.
        $$
        
        Next, $b$ and $d$ are balanced with each other as long as
        
        $$
        \dfrac{\alpha}{1-\alpha}\le\dfrac{\beta}{1-\beta}\alpha \le \dfrac{b}{d} = \dfrac{c}{d}\dfrac{b}{c} \le \dfrac{1-\alpha}{\alpha}(1-\alpha) < \dfrac{1-\alpha}{\alpha},
        $$
        
        which requires
        
        $$
        \beta\ge\dfrac{1}{2-\alpha}.
        $$
        
        Finally, $z+a$ and $b+d$ are balanced with each other as long as
        
        $$
        \alpha<(1-\alpha)(1-(1-\alpha)^2)\le\frac{b+d}{x+y} = \dfrac{w+y}{x+y}\dfrac{b+d}{w+y} < (1-\alpha(1-\alpha))(1-\beta\alpha) \le 1-\alpha,
        $$
        
        which requires
        
        $$
        \beta\ge\dfrac{\alpha}{1-\alpha+\alpha^2}.
        $$
    
    Combining the three cases, as long as
    
    $$
    0<\alpha\le 1-\dfrac{\sqrt{2}}{2},~\dfrac{1}{2-\alpha}\le\beta\le\dfrac{1-2\alpha}{1-\alpha},
    $$
    
    the merged tree can be rebalanced with the combined single/double rotation strategy. This clearly includes the parameter range given in the main text.
    
    Finally, a short explanation of why the algorithm takes $O(|\log(x/y)|)$ time. During the merge, if $y$ is too light compared with $x$, we try to merge it with the right subtree of $x$, and this continues until the subtree rooted at some descendant of $x$ is balanced with $y$. Each level we go down, the subtree weight shrinks to at most $(1-\alpha)$ times its previous value, so at most $\log_{\frac{1}{1-\alpha}}(x/y)$ iterations are needed to find a subtree balanced with $y$. So the merge algorithm calls the balancing algorithm $O(|\log(x/y)|)$ times[^merge-complexity-cmp], and its complexity is $O(|\log(x/y)|)$.
    
    Although it is not obvious, this argument relies on the following fact: while we keep taking right subtrees, $y$ cannot go from being too light compared with the subtree on the left to being too heavy compared with it within a single iteration. This is because the weights of subtrees that can be balanced with $y$ lie between $\alpha y/(1-\alpha)$ and $(1-\alpha)y/\alpha$. So if $y$ went from too light to too heavy in one iteration, the weight of the subtree of $x$ would shrink to at most $\alpha^2/(1-\alpha)^2$ times its previous value in that iteration. But in a single iteration the subtree weight can shrink to at most $\alpha$ times its previous value, and in the range of $\alpha$ above, $\alpha>\alpha^2/(1-\alpha)^2$. So the assumed situation is impossible, and after some iteration $y$ must be balanced with some subtree of $x$.

### Keeping balance by merging

Merging two subtrees means: given that every key in the left subtree is not greater than every key in the right subtree, build a new tree whose leaves hold exactly the union of the leaves of the two subtrees, while keeping the tree balanced.

For this, we use the following strategy[^more-join]: (again assume $x\ge y$)

-   If the right subtree $y$ is empty, return the left subtree $x$ directly;
-   If the left and right subtrees $x$ and $y$ are already balanced, i.e., $y\ge\alpha(x+y)$, join the two subtrees directly;
-   Otherwise, the right subtree $y$ is too light. If the left subtree $z$ of $x$ can be balanced with $w+y$, i.e., $z\ge\alpha(x+y)$, first merge $w$ and $y$, then merge $z$ and $w+y$;
-   Otherwise, both $z$ and $y$ are too light. Then first merge $z$ with the left subtree $u$ of $w$, then merge the right subtree $v$ of $w$ with $y$, and finally **merge** the results of the two merges into a new tree.

Comparing this strategy with the balancing strategy above, we see that in the last two cases the nodes are combined just like the results of single and double rotation in the balancing strategy, except that joining subtrees is replaced by merging.

It can be proved that when

$$
0<\alpha \le 1-\dfrac{\sqrt{2}}{2}\approx 0.292
$$

the resulting tree is always balanced, and this takes $O(|\log(x/y)|)$ time. In other words, the cost of merging two trees does not depend on their absolute sizes, only on their relative sizes.

??? note "Proof of balance and complexity"
    Let $\tau(x,y)$ be the number of direct joins of two subtrees needed when merging two subtrees of weights $x$ and $y$. Strictly speaking, we need to prove that when $0<\alpha\le 1-\sqrt{2}/2$, there is a constant $C>0$ such that for all $x\ge y>0$,
    
    $$
    \tau(x,y) \le 1+C\log^+\dfrac{\alpha x}{(1-\alpha)^2y},
    $$
    
    where $\log^+ x = \max\{0,\log x\}$; moreover, $\tau(x,y)=1$ for all $x/y\le(1-\alpha)/\alpha$. In fact, the constant in the formula can be taken as
    
    $$
    C = -\dfrac{2}{\log(1-\alpha)}.
    $$
    
    This shows that the merge algorithm takes $O(|\log(x/y)|)$ time.
    
    To prove that the merge algorithm always produces a balanced tree and that the complexity bound above holds, we use induction. Give every lattice point $(x,y)\in\mathbf N^2_+$ in the first quadrant the lexicographic order of $(x+y,|x-y|)$. This is clearly a well-order on the set, so we can do induction along it. The base case is $(x,y)=(1,1)$: both subtrees have only one leaf, joining them directly certainly gives a balanced tree, and $\tau(x,y)=1$, which satisfies the formula. Now suppose the induction has reached $(x,y)$ and the claim holds for all points before $(x,y)$. There are three cases:
    
    ??? note "Case 1: trees $x$ and $y$ are balanced, i.e., $y\ge\alpha(x+y)$"
        Then the tree obtained by joining them directly is also balanced, and the join algorithm is called only once, so $\tau(x,y)=1$.
    
    ??? note "Case 2: tree $y$ is too light, but $z$ is not, i.e., $y<\alpha(x+y)\le z$"
        Here we first merge $w$ and $y$, then merge $z$ and $w+y$, so
        
        $$
        \tau(x,y) = \tau(w,y) + \tau(z,w+y).
        $$
        
        By the induction hypothesis, subtree $w+y$ is already balanced. For the second merge, we can actually prove directly that $z$ and $w+y$ are balanced:
        
        $$
        \alpha \le \dfrac{z}{z+(w+y)} = \dfrac{z}{x+y} < \dfrac{z}{z+w} \le 1-\alpha.
        $$
        
        So merging $z$ and $w+y$ is really just joining the two subtrees directly, and $\tau(z,w+y) = 1$. So the final tree is also balanced.
        
        Now estimate $\tau(w,y)$. Since $y<(\alpha/(1-\alpha))x$ and $\alpha x\le w\le(1-\alpha)x$, bounding gives
        
        $$
        \dfrac{\alpha}{1-\alpha}<1-\alpha=\dfrac{\alpha x}{(\alpha/(1-\alpha))x}< \dfrac{w}{y} \le \dfrac{(1-\alpha)x}{y}.
        $$
        
        This shows that $w$ and $y$ can be unbalanced only when $w>y$, so
        
        $$
        \begin{aligned}
        \tau(w,y) &\le 1+C\log^+\dfrac{\alpha w}{(1-\alpha)^2y} \le 1+C\log^+\dfrac{\alpha x}{(1-\alpha)y} \\
        &= 1 + C\log(1-\alpha) + C\log^+\dfrac{\alpha x}{(1-\alpha)^2y}.
        \end{aligned}
        $$
        
        The last equality holds because $x/y>(1-\alpha)/\alpha$.
        
        Therefore,
        
        $$
        \tau(x,y) \le 2 + C\log(1-\alpha) + C\log^+\dfrac{\alpha x}{(1-\alpha)^2y}.
        $$
    
    ??? note "Case 3: trees $y$ and $z$ are both too light, i.e., $y,z<\alpha(x+y)$"
        Here we first merge $z$ and $u$, then merge $v$ and $y$, and finally merge $z+u$ and $v+y$. So
        
        $$
        \tau(x,y) = \tau(z,u) + \tau(v,y) + \tau(z+u,v+y).
        $$
        
        As in the previous case, we can estimate the weight ratio of the two subtrees at each merge step.
        
        Since $z,y<\alpha(x+y)$, we have $w>(1-2\alpha)(x+y)$. Also, by the balance condition, $\alpha\le z/x,w/x,u/w,v/w\le 1-\alpha$. This shows that
        
        $$
        \begin{aligned}
        \dfrac{\alpha}{1-\alpha}<\dfrac{\alpha}{1-\alpha}\frac{1}{1-\alpha}\le \dfrac{z}{u} &= \dfrac{z}{w}\dfrac{w}{u} < \dfrac{\alpha}{1-2\alpha}\dfrac{1}{\alpha} \le \dfrac{1-\alpha}{\alpha},\\
        \dfrac{\alpha}{1-\alpha}\le\alpha\dfrac{1-2\alpha}{\alpha}< \dfrac{v}{y} &= \dfrac{v}{w}\dfrac{w}{y} \le (1-\alpha)\dfrac{(1-\alpha)x}{y} = (1-\alpha)^2\dfrac{x}{y}.
        \end{aligned}
        $$
        
        For the last term,
        
        $$
        \dfrac{z+u}{v+y} = \dfrac{x+y}{v+y}-1 = \dfrac{x+y}{y}\dfrac{y}{v+y} - 1 < (1-\alpha)\left(\dfrac{x}{y}+1\right)-1 < (1-\alpha)\dfrac{x}{y}.
        $$
        
        Conversely,
        
        $$
        \dfrac{z+u}{v+y} = \dfrac{x+y}{v+y}-1 \ge \dfrac{x+y}{(1-\alpha)^2x+y}-1 > \dfrac{1}{(1-\alpha)^3+\alpha}-1 > \dfrac{\alpha}{1-\alpha}.
        $$
        
        Using these inequalities, we can show that the final tree must be balanced. By the induction hypothesis, merging $z$ with $u$ and merging $v$ with $y$ both give balanced trees. Moreover, the first step, merging $z$ and $u$, is actually a direct join of the two trees. For the merge of tree $z+u$ and tree $v+y$, there are two subcases:
        
        -   If $z+u\le v+y$, their weight ratio is strictly greater than $\alpha/(1-\alpha)$, so they can be joined directly and the result is balanced;
        -   Otherwise, their weight ratio must be strictly less than $x/y$, but $(z+u)+(v+y)=x+y$, so $|(z+u)-(v+y)|<|x-y|$. By the lexicographic order given above, the induction hypothesis also applies in this case, and the result is balanced too.
        
        Applying the induction hypothesis further gives:
        
        $$
        \begin{aligned}
        \tau(z,u) &= 1,\\
        \tau(v,y) &\le 1+C\log^+\dfrac{\alpha x}{y},\\
        \tau(z+u,v+y) &\le 1 + C\log^+\dfrac{\alpha x}{(1-\alpha)y}.
        \end{aligned}
        $$
        
        Simply adding the three inequalities would make the coefficient in front of the logarithm $2C$, and the induction would fail. So a more careful estimate is needed here.
        
        When $\min\{v/y,(z+u)/(v+y)\}\le(1-\alpha)/\alpha$, one of $\tau(v,y)$ and $\tau(z+u,v+y)$ must be $1$, so
        
        $$
        \begin{aligned}
        \tau(v,y) + \tau(z+u,v+y) &\le 2 + C\log^+\dfrac{\alpha x}{(1-\alpha)y}\\
        &= 2 + C\log(1-\alpha) + C\log^+\dfrac{\alpha x}{(1-\alpha)^2y}.
        \end{aligned}
        $$
        
        Otherwise, we have
        
        $$
        \begin{aligned}
        \tau(v,y) + \tau(z+u,v+y) 
        &\le 2 + C\log^+\dfrac{\alpha v}{(1-\alpha)^2y} + C\log^+\dfrac{\alpha(z+u)}{(1-\alpha)^2(v+y)}\\
        &= 2 + C\log\dfrac{\alpha}{(1-\alpha)^2} + C\log^+\dfrac{\alpha v(z+u)}{(1-\alpha)^2y(v+y)}.
        \end{aligned}
        $$
        
        For $0<\alpha\le 1-\sqrt{2}/2$,
        
        $$
        \dfrac{\alpha}{(1-\alpha)^2} < 1-\alpha.
        $$
        
        Also,
        
        $$
        \begin{aligned}
        \dfrac{v(z+u)}{y(v+y)} &= \left(\dfrac{v+y}{y}-1\right)\left(\dfrac{x+y}{y}\dfrac{y}{v+y} - 1\right) \\
        &= \dfrac{x+y}{y} + 1 -\dfrac{x+y}{y}\dfrac{y}{v+y}-\dfrac{v+y}{y} < \dfrac{x}{y}.
        \end{aligned}
        $$
        
        This shows that in the latter case we also have
        
        $$
        \tau(v,y) + \tau(z+u,v+y) < 2 + C\log(1-\alpha) + C\log^+\dfrac{\alpha x}{(1-\alpha)^2y}.
        $$
        
        The overall merge complexity is
        
        $$
        \tau(x,y) \le 3 + C\log(1-\alpha) + C\log^+\dfrac{\alpha x}{(1-\alpha)^2y}.
        $$
    
    Combining all cases,
    
    $$
    \tau(x,y) \le 3 + C\log(1-\alpha) + C\log^+\dfrac{\alpha x}{(1-\alpha)^2y}.
    $$
    
    So as long as we choose $2+C\log(1-\alpha)\le 0$, the induction on the complexity goes through. An obvious choice is
    
    $$
    C = -\dfrac{2}{\log(1-\alpha)}.
    $$
    
    This constant shows that when merging two trees, the number of direct joins of subtrees is roughly at most twice the difference in tree heights.

A reference implementation:

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:merge"
    ```

With this merge strategy, keeping the tree balanced is also easy: when it is unbalanced, just merge the left and right subtrees.

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:balance-by-merging"
    ```

Since the two trees to rebalance always have nearly balanced sizes, maintaining balance takes $O(1)$ time.

## Basic balanced tree operations

Using the functions implemented above, a WBLT supports all the basic operations of a balanced tree. This section uses a multiset as an example to show how to implement a balanced tree with a WBLT.

### Building the tree

Building the tree is very similar to a segment tree: recursively split the range in half until its length is $1$, put the stored information in the leaf, and combine the range information while backtracking.

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-2.cpp:build"
    ```

The time complexity is $O(n)$.

### Insertion and deletion

To insert, recurse down from the root until we find, among the leaves with value greater than or equal to the element to insert, the one with the smallest value. Then create two new nodes: one stores the newly inserted value, and the other becomes the new parent of the two leaves and takes the place of that smallest leaf. Then connect the two leaves to this parent. While backtracking, maintain the balance of the tree.

![](./images/wblt-insert-delete.svg)

As shown in the figure, we want to insert an element with value $4$ into the tree on the left. First find the leaf with value $5$, then create a new leaf $4$ and a non-leaf node $\text{d}$, and connect $4$ and $5$ to $\text{d}$. This gives the tree on the right.

For deletion, reverse the process above: find a leaf whose value equals the value to delete, delete it and its parent, and put the parent's other child in the parent's place. While backtracking, also maintain the balance of the tree.

A reference implementation:

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:insert-remove"
    ```

Watch out for the empty tree. If you do not want to handle an empty tree, you can insert an $\infty$ element into the tree beforehand.

Both operations take $O(\log n)$ time.

### Finding the rank

Since a WBLT looks very much like a segment tree, we can find the rank in a way similar to binary search on a segment tree: if the maximum of the left subtree is greater than or equal to the value we are looking for, go to the left child; otherwise, go to the right child and add the weight of the left subtree to the answer.

A reference implementation:

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:rank"
    ```

The time complexity is $O(\log n)$.

### Finding by rank

This again uses the idea of binary search on a segment tree, except that here we compare node weights.

A reference implementation:

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:kth-element"
    ```

The time complexity is $O(\log n)$.

### Finding the predecessor and successor

Just combine the two operations above.

A reference implementation:

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:prev-next"
    ```

If you want to implement them directly, note that equal keys may be stored in several leaves.

### Split

Splitting a WBLT is similar to splitting a [non-rotating Treap](./treap.md#分裂split): based on subtree sizes or values, decide whether to recursively split the left or the right subtree. The difference is that a WBLT needs to **merge** the subtrees that are split off, to keep the final split trees balanced.

A reference implementation of splitting by subtree size:

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-2.cpp:split"
    ```

The time complexity is $O(\log n)$.

??? note "Proof of the complexity"
    The recursion depth is clearly at most the tree height, which is $O(\log n)$. We need to prove that merging the subtrees split off on the left side and on the right side takes $O(\log n)$ time. Consider only the left side, since the right side is symmetric. Let the subtrees split off on the left be $T_1,T_2,\cdots,T_\ell$ from bottom to top; the number of them is $\ell\in O(\log n)$. The merging process can be described as follows: starting from $T'_1=T_1$, merge $T'_{i-1}$ with $T_i$ to get $T'_i$, until all subtrees are merged. The total cost of merging can be written as
    
    $$
    \sum_{i=2}^\ell \tau(T_i,T'_{i-1}),
    $$
    
    where $\tau(T_i,T'_{i-1})$ is the cost of merging $T_i$ and $T'_{i-1}$.
    
    If $w(T_i)\ge w(T'_{i-1})$ always holds, then by the complexity of merging two subtrees,
    
    $$
    \tau(T_i,T'_{i-1}) \in O\left(\log\dfrac{w(T_i)}{w(T'_{i-1})}\right) \subseteq O\left(\log\dfrac{w(T'_i)}{w(T'_{i-1})}\right).
    $$
    
    Since the constants in these big-$O$ terms are all the same, we can add them up directly, and the sum telescopes.
    
    However, note that $w(T_i)\ge w(T'_{i-1})$ does not always hold, because $T'_{i-1}$ was split from the right subtree corresponding to $T_i$ in the original tree, and that right subtree may be larger than the left subtree $T_i$. Even so, if $T'_{i-1}$ is larger than $T_i$, since it is part of that right subtree, its weight $w(T'_{i-1})$ is at most $(1-\alpha)/\alpha$ times $w(T_i)$. This means $T'_{i-1}$ and $T_i$ must be balanced in this case, and merging them takes $O(1)$ time.
    
    Putting the two cases together, the cost of a single merge can be written as
    
    $$
    \tau(T_i,T'_{i-1}) \in O\left(\log\dfrac{w(T'_i)}{w(T'_{i-1})}\right) + O(1).
    $$
    
    So the total cost of merging is
    
    $$
    O\left(\sum_{i=2}^\ell\left( 1+\log\dfrac{w(T'_i)}{w(T'_{i-1})}\right) \right) \subseteq O(\ell+\log w(T'_\ell)) \subseteq O(\log n).
    $$
    
    This shows that the split algorithm takes $O(\log n)$ time in total.

## Reference implementation

This article has shown how to use a WBLT for the basic operations of a balanced tree. Below is the [standard balanced tree template](https://loj.ac/p/104) implemented with a WBLT.

??? example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:full-text"
    ```

With merge and split, we can also implement the "Literary Balanced Tree" problem. Below is the [Literary Balanced Tree template](https://loj.ac/p/105) implemented with a WBLT; lazy tags must be pushed down when visiting nodes on the way down.

??? example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-2.cpp:full-text"
    ```

Note that a WBLT needs twice the space. When split and merge are involved, take care of garbage collection and recycle unused nodes in time, or the space usage will not be linear.

## References and notes

-   [Weight-balanced tree - Wikipedia](https://en.wikipedia.org/wiki/Weight-balanced_tree)
-   Nievergelt, J.; Reingold, E. M. (1973). "Binary Search Trees of Bounded Balance". SIAM Journal on Computing. 2: 33–43.
-   Blum, Norbert; Mehlhorn, Kurt (1980). "On the average number of rebalancing operations in weight-balanced trees". Theoretical Computer Science. 11 (3): 303–320.
-   Hirai, Y.; Yamamoto, K. (2011). "Balancing weight-balanced trees". Journal of Functional Programming. 21 (3): 287.
-   Blelloch, Guy E.; Ferizovic, Daniel; Sun, Yihan (2016), "Just Join for Parallel Ordered Sets", Symposium on Parallel Algorithms and Architectures, Proc. of 28th ACM Symp. Parallel Algorithms and Architectures (SPAA 2016), ACM, pp. 253–264.
-   Straka, Milan. (2011). "Adams’Trees Revisited: Correctness Proof and Efficient Implementation." International Symposium on Trends in Functional Programming. Berlin, Heidelberg: Springer Berlin Heidelberg.

[^wrong-range]: The parameter range $\alpha < 1-\dfrac{\sqrt{2}}{2},~\beta=\dfrac{1-2\alpha}{1-\alpha}$ given in the original paper by Nievergelt and Reingold is wrong. The paper by Hirai and Yamamoto gives counterexamples. The problem mainly appears on some very small trees, which breaks the whole inductive proof. Of course, in real contests it is very hard to construct data that breaks these wrong parameters, so in practice it may not matter much.

[^merge-complexity-cmp]: A single balancing step is equivalent to at most two subtree joins, and when the two subtrees are finally balanced, one more call to the join algorithm is needed. So if we count the number of calls to the join algorithm, the merge operation based on balancing and the balancing operation based on direct merging below have the same constant factor.

[^more-join]: The proof below shows that in the third case, $z$ and $w+y$ are always balanced, and in the fourth case, $z$ and $u$ are always balanced. They can be joined directly without merging.
