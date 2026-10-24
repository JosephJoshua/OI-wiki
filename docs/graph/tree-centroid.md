author: Ir1d, Marcythm, LucienShui, Anguei, H-J-Granger, CornWorld, ttzc

This article introduces the concept and basic properties of the centroid of a tree.

## Definition

If deleting a node $v$ from a tree $T$ leaves a graph $T\setminus\{v\}$ in which every connected component has size at most half the number of nodes in the original tree, then $v$ is called a **centroid** of the tree. The size of the largest connected component left after deleting a node is also called the **weight** of that node. Using this idea, a centroid can be defined as a node whose weight is at most half the number of nodes in the tree.

???+ info "\"Subtree\""
    This article may deal with unrooted trees, rooted trees, and trees obtained by rerooting a rooted tree at a non-root node. To avoid confusion, we write $T$ for an unrooted tree and $T^{(v)}$ for the rooted tree with root $v$. Every "subtree" mentioned here means, in a **rooted tree**, the tree made of a node and all of its descendants. In the rooted tree $T^{(v)}$, the subtree of node $u$ is written $T^{(v)}_u$. Subtrees defined this way of course include the whole tree itself. When we want to explicitly exclude the whole tree, we call it a "proper subtree".
    
    In an unrooted tree, a "subtree" usually means a connected subgraph. When discussing centroids, some authors use "subtree" to mean specifically a maximal connected subgraph that does not contain some node, or one of the two connected components left after deleting an edge. It is easy to check that these two definitions give the same set of "subtrees", and that this set does not include the whole tree. Since this set differs from the set of subtrees of a rooted tree, this article avoids using the word "subtree" for unrooted trees.
    
    When actually finding a centroid or solving related problems, there is usually a default root. In that case, the connected components left after deleting a non-root node $v$ include, besides the subtrees of its children, one "upward" subtree. If the parent of $v$ is $u$, this "upward" subtree is $T_u^{(v)}$. When this article mentions such a subgraph, it explicitly calls it the "upward" subtree. Unless stated otherwise, subtrees in this article do not include this "upward" subtree.

Note that the resulting connected components are also unrooted trees. By deleting the centroid, a tree becomes several trees, each at most half the size of the original. This property makes it possible to apply divide and conquer on trees. This is [centroid decomposition](./tree-divide.md#centroid-decomposition).

## Properties

This section discusses properties of centroids. First, there are the following equivalent definitions of a centroid:

???+ note "Equivalent definitions"
    A node $v$ in tree $T$ is a centroid if and only if any one of the following holds:
    
    === "Unrooted version"
        1.  After deleting node $v$ from the tree, every connected component of the graph $T\setminus\{v\}$ has size at most half the number of nodes in the original tree.
        2.  Among the sizes of the largest connected component obtained by deleting each node, the value obtained by deleting $v$ is the smallest.
        3.  Among the sums of distances from all nodes to a given node, the sum of distances to $v$ is the smallest.
    
    === "Rooted version"
        1.  When the tree is rooted at $v$, every proper subtree has size at most half the number of nodes in the original tree.
        2.  Among the sizes of the largest proper subtree when rooting at each node, the value when rooting at $v$ is the smallest.
        3.  Among the sums of depths of all nodes when rooting at each node, the sum when rooting at $v$ is the smallest.

??? note "Proof"
    First, some notation. The rooted and unrooted versions are clearly equivalent. Define $W(x)=\max_{u\sim x}|T_u^{(x)}|$, where $u\sim x$ means $u$ and $x$ are adjacent. Define $S(x)=\sum_{u\in T}d(u,x)$, where $d(u,x)$ is the distance between nodes $u$ and $x$. Then definition 1 requires $W(v)\le |T|/2$, definition 2 requires $v\in\arg\min_{x\in T}W(x)$, and definition 3 requires $v\in\arg\min_{x\in T}S(x)$. We need to prove that these three conditions are equivalent.
    
    Think of $S(x)$ as the sum of node depths when rooted at $x$, and look at how it changes when the root moves from node $v$ to an adjacent node $u$. Deleting edge $(v,u)$ from the tree leaves two connected components, the subtrees $T_v^{(u)}$ and $T_u^{(v)}$. When the root moves, every node in $T_v^{(u)}$ gets $1$ deeper, and every node in $T_u^{(v)}$ gets $1$ shallower. So the change in the depth sum is
    
    $$
    \Delta S_{v\to u} = S(u) - S(v) = |T_v^{(u)}| - |T_u^{(v)}| = |T| - 2|T_u^{(v)}|.
    $$
    
    So the condition of definition 1 is equivalent to requiring $\Delta S_{v\to u}\ge 0$ for every neighbor $u$ of $v$. In other words, $v$ is a local minimum of $S(\cdot)$.
    
    Now let $v$ be a (global) minimum of $S(\cdot)$ (definition 3). Such a $v$ must exist, and it must be a local minimum. Consider the tree $T^{(v)}$ rooted at $v$. Let $u\neq v$ be a non-root node. On the directed path from $v$ to $u$, let $y$ be the node right after $v$ (possibly $u$ itself), and let $x$ be the node right before $u$ (possibly $v$ itself). Since $T_u^{(x)}\subseteq T_y^{(v)}$, we have
    
    $$
    2|T_x^{(u)}| = 2|T| - 2|T_u^{(x)}| \ge 2|T| - 2|T_y^{(v)}| \ge |T|.
    $$
    
    The last step uses the fact that $v$ is a local minimum of $S(\cdot)$. There are now two cases:
    
    -   There is a node $u$ with $2|T_x^{(u)}|=|T|$. By the inequality above, we must have $(x,u)=(v,y)$ and $|T_v^{(u)}|=|T_{u}^{(v)}| = |T|/2$. That is, any node $u$ that makes the equality hold must be adjacent to $v$. Also, the subtrees of the neighbors of $v$ have total size $|T|-1<|T|$, so there can be only one such $u$. Then for every other node $u'\neq u,v$, there must be some $x'\sim u'$ with $|T_{x'}^{(u')}| > |T|/2$. The set of nodes satisfying condition 1 is $\{v,u\}$.
    
        Note that when any node is deleted, the sizes of the resulting components always add up to $|T|-1$. So as soon as one component has size at least $|T|/2$, it must be the largest component. Therefore in this case $W(v)=W(u)=|T|/2$, and $W(u') > |T|/2$ for every $u'\neq u,v$. So the set of nodes satisfying condition 2 is $\arg\min W(\cdot) = \{v,u\}$.
    
        Also, since $\Delta S_{v\to u} = 0$, we have $S(v)=S(u)$. Since $v$ is a minimum, $u$ must be a minimum too. For each $u'\neq u,v$ there is some $x'\sim u'$ with $|T_{x'}^{(u')}| > |T|/2$, which violates the condition for a local minimum, so $u'$ is not a minimum either. Therefore the set of nodes satisfying condition 3 is $\arg\min S(\cdot) = \{v,u\}$.
    -   There is no node $u$ with $2|T_x^{(u)}|=|T|$. Then for every node $u\neq v$, there is a node $x\sim u$ with $|T_x^{(u)}| > |T|/2$. Repeating the analysis above, every node $u\neq v$ has $W(u) > |T|/2$ and is not a local minimum of $S(\cdot)$. So the only node satisfying condition 1 is $v$, and $\arg\min W(\cdot)=\arg\min S(\cdot) = \{v\}$.
    
    In both cases, the three conditions give the same set. This proves that the three definitions are equivalent.

Besides these equivalent definitions, centroids have the following common properties:

???+ note "Properties"
    1.  If the centroid of a tree is not unique, there are exactly two. These two centroids are adjacent. Moreover, after deleting the edge between them, the tree splits into two connected components of the same size.
    2.  If we add or remove one leaf, the centroid moves by at most one edge.
    3.  If we join two trees with one edge to form a new tree, the centroid of the new tree lies on the path between the centroids of the two original trees.
    4.  The centroid of a rooted tree always lies on the heavy path containing the root. The centroid of a tree is always an ancestor of the centroid of the subtree of the root's heavy child.

??? note "Proof"
    Property 1 follows from the proof of the equivalent definitions.
    
    For property 2, we only need to consider adding a leaf. There are two cases:
    
    -   Tree $T$ has only one centroid $v$. Let $x$ be the new leaf, and in the new tree, let $B\cup\{x\}$ be the component containing $x$ in the graph $T\cup\{x\}\setminus\{v\}$ obtained by deleting $v$. Since $v$ is the only centroid of $T$, we have $2|B| < |T|$, that is, $2|B|+1\le |T|$. So
    
        $$
        2|B\cup\{x\}| = 2(|B|+1) \le |T| + 1 = |T\cup\{x\}|.
        $$
    
        Therefore $v$ is still a centroid of the new tree $T\cup\{x\}$. Even if the new tree's centroid is not unique, the other one must be a neighbor of $v$. So the centroid moves by at most one edge.
    -   Tree $T$ has two centroids $u,v$. Deleting $(u,v)$ leaves two components $T_u^{(v)}$ and $T_v^{(u)}$ of equal size $|T|/2$. Without loss of generality, assume the new leaf $x$ is attached to the component $T_v^{(u)}$ containing $v$. Then, since
    
        $$
        |T_v^{(u)}\cup\{x\}| = |T|/2 + 1 > (|T|+1)/2 = |T\cup\{x\}|/2,
        $$
    
        $u$ is no longer a centroid of the new tree. On the other hand, after deleting $v$ there is still a component $T_u^{(v)}$ of size $|T|/2$, and the other components have total size
    
        $$
        |T\cup\{x\}| - 1 - |T_u^{(v)}| = |T|/2 \le |T_u^{(v)}|,
        $$
    
        so $v$ is still a centroid of the new tree. Since the new tree has an odd number of nodes, its centroid must be unique. So again the centroid moves by at most one edge.
    
    Putting the two cases together, the centroid of the new tree always lies on the path between the old centroid and the newly added leaf.
    
    Property 3 can be shown by induction. When $T$ and $T'$ are joined, let the new edge be $(x,y)$ with $x\in T,y\in T'$. Without loss of generality, assume (a) centroid of the new tree is in $T$. Start from tree $T$ and add the nodes of $T'$ one by one as leaves. Fix a centroid $c$ of $T$. We show by induction that (a) centroid of the tree always lies on the path between $c$ and node $x$. The base case is obvious. Suppose the claim holds up to some moment, and let the centroid at that time be $v$. By the analysis of property 2, the new centroid must lie on the path between the newly added node and the current centroid $v$. Since it never moves outside $T$, we only need the part of this path inside $T$, which is the path between the current centroid $v$ and node $x$. By the induction hypothesis, $v$ is on the path between $c$ and $x$, so the new centroid is also on the path between $c$ and $x$. By induction, the claim holds.
    
    Property 4 follows from the [properties of heavy-light decomposition](./hld.md#properties-of-heavy-light-decomposition). Let $v$ be (a) centroid of tree $T$. If $v$ is the root, the claim is obvious. Otherwise let $v$ be a non-root node and $u$ its parent. Since $|T_u^{(v)}| \le |T|/2$, the subtree of $v$ has size at least $|T|/2$. But if the path from it to the root passes through even one light edge, its subtree size would be strictly less than $|T|/2$, a contradiction. So it must lie on the heavy path containing the root. Further, by the definition of heavy paths, the heavy path containing the root within the subtree of the root's heavy child is part of the heavy path containing the root in the original tree. And by property 3, when we add the root and the subtrees of all its light children to the heavy child's subtree, the centroid moves along the path between the current centroid and the root. So the new centroid must be an ancestor of the old one (possibly the old one itself).

## How to find it

Based on the equivalent definitions, there are two ways to find all centroids of a tree in $O(n)$ time, where $n$ is the size of the tree.

### Counting subtree sizes with DFS

Compute the size of every subtree with DFS. For each node, record the sizes of its children's subtrees, and get the size of the "upward" subtree by subtracting the current subtree size from the total number of nodes. Then we can find the centroids directly from the definition.

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/graph/code/tree-centroid/tree-centroid-2.cpp:core"
    ```

### Computing depth sums with rerooting DP

We can also use rerooting DP to compute, for each choice of root, the sum of depths of all nodes (that is, the sum of distances to the current root). By the definition, we just need the node that minimizes this sum.

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/graph/code/tree-centroid/tree-centroid-3.cpp:core"
    ```

## Example problem

???+ example "[Codeforces Round 359 (Div. 1) B. Kay and Snowflake](https://codeforces.com/problemset/problem/685/B)"
    Given a rooted tree, find the centroid of every subtree.

??? note "Solution idea"
    By property 4, for the subtree rooted at node $u$, its centroid lies on the path from the centroid of the subtree rooted at $u$'s heavy child up to $u$.
    
    As in the DFS method above, for each subtree rooted at $u$, first find the centroid of its heavy child's subtree (a leaf's centroid is the leaf itself). Then walk up from that centroid and check whether each node on the path is a centroid. If none of them is, then $u$ itself is the centroid.
    
    Since the centroids of subtrees along the same heavy path only move upward along that path, the total number of upward checks on each heavy path is of the same order as its length. So we can find the centroids of all subtrees in $O(n)$ time.

??? note "Reference code"
    ```cpp
    --8<-- "docs/graph/code/tree-centroid/tree-centroid-1.cpp"
    ```

## Exercises

-   [Gym 101649G Godfather](https://codeforces.com/gym/101649/problem/G)
-   [POJ 1655 Balancing Act](http://poj.org/problem?id=1655)
-   [Luogu P1364 Hospital Placement](https://www.luogu.com.cn/problem/P1364)
-   [Codeforces 1406C Link Cut Centroids](https://codeforces.com/contest/1406/problem/C)
-   [Codeforces 708C Centroids](https://codeforces.com/problemset/problem/708/C)

## References

-   [Some properties and dynamic maintenance of the tree "centroid" - fanhq666](https://web.archive.org/web/20181122041458/http://fanhq666.blog.163.com/blog/static/81943426201172472943638) ([repost on cnblogs](https://www.cnblogs.com/qlky/p/5781081.html))
-   [Tree diameter, tree centroid and centroid decomposition - cyendra](https://www.cnblogs.com/zinthos/p/3899075.html)
-   [Properties of the tree centroid and their proofs - suxxsfe](https://www.cnblogs.com/suxxsfe/p/13543253.html)
-   *Dictionary of the Olympiad in Informatics*, Section 2.4.7.11, Part 1: Centroid of a tree
