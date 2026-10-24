author: 310552025atNYCU, accelsao, Chrogeek, Enter-tainer, iamtwz, mcendu, Shen-Linwood, shuzhouliu, StudyingFather, t4rf9, Tiphereth-A, TrickEye, wlbksy, Xeonacid, yuhuoji, c-forrest, aaron20100919

## Introduction

A **matching**, or **independent edge set**, is a set of edges in a graph where no two edges share an endpoint. Graph matching algorithms are common in informatics olympiads. They fall roughly into two groups: maximum matching and maximum weight matching. Matching in a [bipartite graph](../bi-graph.md) is equivalent to a network flow problem; it has nice properties and is relatively easy to handle. So this page first introduces both kinds of algorithms on bipartite graphs, and then discusses algorithms for general graphs.

## Matchings in graphs

Let $G=(V,E)$ be an undirected graph, where $V$ is the vertex set and $E$ is the edge set. If a set of edges $M\subseteq E$ contains no self-loops and no two of its edges share a vertex, then $M$ is called a **matching** or **independent edge set** of $G$. An edge $e\in E$ is called a **matched edge** if it is in the matching $M$, and an **unmatched edge** otherwise. Similarly, a vertex $v\in V$ is called a **matched vertex** if it is an endpoint of a matched edge, and an **unmatched vertex** (or free vertex) otherwise.

The size of a matching $M$ is the number of edges it contains. For matchings in (weighted) undirected graphs, the following concepts often come up:

-   **Maximal matching**: a matching to which no more edges can be added. A maximal matching is not necessarily a maximum matching.

    ![maximal matching](images/graph-match-1.svg)

-   **Maximum matching** (maximum cardinality matching): a matching with the largest number of edges. There may be more than one maximum matching, but the number of edges in a maximum matching is fixed, and it can never exceed half the number of vertices.

    ![maximum cardinality matching](images/graph-match-2.svg)

-   **Maximum weight matching**: in a weighted graph, a matching with the largest total edge weight.

    ![maximum weight matching](images/graph-match-3.svg)

-   **Maximum weight maximum cardinality matching**: among all matchings with the largest number of edges, the one with the largest total edge weight. In other words, it is the maximum matching with the largest total weight.

    ![maximum weight maximum cardinality matching](images/graph-match-4.svg)

-   **Perfect matching**: a matching in which every vertex is matched. A perfect matching is always a maximum matching. A complete graph with an even number of vertices always has a perfect matching.

-   **Near-perfect matching**: a matching with exactly one unmatched vertex. This can only happen when the graph has an odd number of vertices. A near-perfect matching is also always a maximum matching. A complete graph with an odd number of vertices always has a near-perfect matching.

In competitive programming, graph matching problems are mostly about maximum matching or maximum weight matching.

## Augmenting paths

In graph matching algorithms, the augmenting path is the key structure used to improve a matching.

### Definition

For a graph $G=(V,E)$ and a matching $M$ of it, we define two kinds of (simple) paths:

-   An **alternating path** is a path whose edges alternate between matched and unmatched edges;
-   An **augmenting path** is an alternating path that starts at an unmatched vertex and ends at an unmatched vertex.

An augmenting path has one more unmatched edge than matched edges, so the number of edges on it is always odd. If we flip the matched and unmatched edges along an augmenting path, it is still an alternating path, and the size of the matching increases by $1$. The process of finding an augmenting path and flipping it to enlarge the matching is called **augmentation**. In mathematical terms, augmentation takes the symmetric difference of the matching $M$ and the augmenting path $P$, giving a new matching $M\oplus P$.

The figure below shows one augmentation, which increases the matching size from $2$ to $3$.

![augment-1](./images/augment-1.png)

### Berge's lemma

Berge's lemma says that improving a matching with augmenting paths is enough. In other words, once no augmenting path can be found, we already have a maximum matching.

???+ note "Berge's lemma"
    For a graph $G=(V,E)$ and a matching $M$ of it, $M$ is a maximum matching if and only if there is no augmenting path with respect to $M$.

??? note "Proof"
    We have already shown that if an augmenting path $P$ exists, then $M\oplus P$ is a larger matching than $M$, so $M$ cannot be a maximum matching.
    
    Conversely, we need to show that if there is a matching $M'$ larger than $M$, then there must be an augmenting path $P$ with respect to $M$. To do this, look at the symmetric difference $M\oplus M'$. In the graph $(V,M\oplus M')$, every vertex has degree $0$, $1$ or $2$, so each connected component of this graph is a path, a cycle, or an isolated vertex. Moreover, the two edges at a vertex of degree $2$ must come from different matchings, so each such cycle has the same number of edges from $M$ and from $M'$. Since $M'$ is larger than $M$, at least one path has more edges from $M'$ than from $M$; call this path $P$. Then both endpoints of $P$ are unmatched vertices with respect to $M$, and $P$ is an alternating path with respect to $M$, so $P$ must be an augmenting path with respect to $M$. This completes the proof.

This theorem gives the core idea for finding a maximum matching:

-   Go through all unmatched vertices and look for augmenting paths, until no augmenting path can be found.

In fact, after each augmentation, we do not need to go through all unmatched vertices again. During the whole process of finding a maximum matching, each vertex only needs to be visited once.

??? note "Proof"
    We only need to show this: if, when the enumeration reaches vertex $v$, there is no augmenting path starting at $v$, then after any number of later augmentations there is still no augmenting path starting at $v$. This means that even though augmentations change the matching, we never need to recheck unmatched vertices that have already been enumerated.
    
    Suppose this is false. That is, suppose $v$ is an unmatched vertex that has already been enumerated, and after some augmentation along an augmenting path $P$ from $u$ to $w$, a new augmenting path $P'$ starting at $v$ appears that did not exist before. Then $P'$ must share an edge with $P$. Otherwise, augmenting along $P$ would not change the matching status of any edge of $P'$, and $P'$ would not be a new augmenting path created by this augmentation.
    
    ![augment-2](./images/augment-2.svg)
    
    (In the figure, black means unmatched edges, and red and blue mean different matching states.)
    
    Let $x$ be the first vertex of $P$ reached when walking along $P'$ from $v$. Before this augmentation, there was already an alternating path from $v$ to $x$, while there was no augmenting path starting at $v$. So $x$ must be a matched vertex, which means it cannot be $u$ or $w$. Therefore, on the augmenting path $P$, $x$ has two incident edges, and their matching states are opposite. This means that no matter what the matching state of the last edge is when the alternating path from $v$ reaches $x$, we can extend the alternating path along $P$ to either $u$ or $w$. So an augmenting path starting at $v$ already existed before the augmentation, which contradicts the assumption.

### Alternating trees

Another concept closely related to augmenting paths is the alternating tree. It is the tree produced when we run a DFS or BFS from an unmatched vertex $r$ to search for an augmenting path.

For a graph $G=(V,E)$ and a matching $M$ of it, if a subgraph $H\subseteq G$ is a tree rooted at an unmatched vertex $r$, and the path connecting $r$ to any $v\in V(H)$ is an alternating path, then $H$ is called an **alternating tree**. Vertices at even depth in the tree are called even vertices, and vertices at odd depth are called odd vertices.

The figure below shows one possible alternating tree obtained by a BFS starting from the unmatched vertex $1$. (In the figure, red edges are matched edges and black edges are unmatched edges; dark vertices are matched vertices and light vertices are unmatched vertices.)

![](images/alternating-tree.svg)

## Existence of perfect matchings

Graph matching theory has two important existence theorems. They can be used to decide whether a perfect matching exists in a bipartite graph or in a general graph.

### Hall's theorem

Suppose $G=(X,Y,E)$ is a bipartite graph with $|X|\le |Y|$. For a matching $M$ of $G$, if every vertex in $X$ is matched, then $M$ is called an **$X$‑perfect matching**, sometimes simply called a perfect matching (of the bipartite graph $G$). This is the largest matching that can possibly exist in a bipartite graph. Hall's theorem gives a necessary and sufficient condition for such a matching to exist.

Hall's theorem says that as long as every subset of $X$ has enough vertices in $Y$ that it could be matched with, an $X$‑perfect matching must exist.

???+ note "Hall's theorem"
    Suppose $G=(X,Y,E)$ is a bipartite graph with $|X|\le |Y|$. For any $W\subseteq X$, let $N_G(W)$ be the set of vertices in $G$ that are adjacent to some vertex in $W$. Then an $X$‑perfect matching exists if and only if $|W|\le |N_G(W)|$ holds for all $W\subseteq X$.

??? note "Proof"
    The condition is clearly necessary. Suppose an $X$‑perfect matching $M$ exists. Then each vertex in $X$ is matched to a different vertex in $Y$. The set $N_G(W)$ contains at least the vertices matched to the vertices of $W$, so its size is at least $|W|$.
    
    The condition is also sufficient. Suppose no $X$‑perfect matching exists. Then there is a maximum matching $M$ in which some vertex $v\in X$ is still unmatched. Let $Z$ be the set of all vertices reachable from $v$ by alternating paths, and let $S=Z\cap X$ and $T=Z\cap Y$. Every vertex in $S\setminus\{v\}$ must be matched: since $G$ is bipartite, an alternating path from $v$ to a vertex of $X$ has even length, so its last edge must be a matched edge. Every vertex in $T$ must also be matched; otherwise there would be an augmenting path, which by Berge's lemma contradicts $M$ being a maximum matching. Since all of them are matched, and matching edges only go between $X$ and $Y$, the vertices in $S\setminus\{v\}$ and in $T$ are in one-to-one correspondence. That is, $|T|=|S|-1$. Also, since the vertices of $T$ are matched with vertices of $S$, we have at least $T\subseteq N_G(S)$. On the other hand, for any $u\in N_G(S)$, say $u$ is adjacent to $v'$ in $S$; then we can extend the alternating path that reaches $v'$ to get an alternating path that reaches $u$, so $u\in T$. This shows $T=N_G(S)$. Together these arguments show $|N_G(S)|<|S|$, which contradicts the condition in Hall's theorem. So an $X$‑perfect matching exists.

???+ note "Corollary"
    Every $k$‑regular ($k\ge 1$) bipartite graph has a perfect matching.

??? note "Proof"
    In a regular bipartite graph, every vertex has the same degree; call it $k\ge 1$. First we check Hall's condition: for every $W\subseteq X$, $|N_G(W)|\ge |W|$. The number of edges incident to vertices of $W$ is $k|W|$, and each vertex in $N_G(W)$ can be incident to at most $k$ of these edges, so $k|W|\le k|N_G(W)|$, that is, $|W|\le |N_G(W)|$. In particular, $|X|\le |Y|$; since $X$ and $Y$ play symmetric roles, $|X|=|Y|$. This means that in a regular bipartite graph, an $X$‑perfect matching is also a perfect matching. Since Hall's theorem guarantees that an $X$‑perfect matching exists, a perfect matching must exist too.

### Tutte's theorem

Tutte's theorem gives a necessary and sufficient condition for a general graph to have a perfect matching. The condition comes from a simple observation: a graph with an odd number of vertices can never have a perfect matching.

???+ note "Tutte's theorem"
    A graph $G=(V,E)$ has a perfect matching if and only if for every $U\subseteq V$, $\operatorname{odd}(G-U)\le |U|$. Here $G-U$ is the subgraph obtained from $G$ by deleting the vertices in $U$ and their incident edges, and $\operatorname{odd}(G-U)$ is the number of connected components of $G-U$ with an odd number of vertices.

??? note "Proof"
    It is enough to consider simple graphs, because multiple edges and self-loops do not affect the Tutte condition or whether a perfect matching exists.
    
    Necessity is relatively easy. Suppose a perfect matching $M$ exists. For any $U\subseteq V$, after deleting the vertices of $U$ from $G$, each connected component with an odd number of vertices has at least one vertex that cannot be matched with a vertex in the same component, and such vertices can only be matched with vertices in $U$. For such a matching to exist, we need at least $\operatorname{odd}(G-U)\le |U|$. This is the Tutte condition.
    
    Sufficiency is more involved. Suppose $G$ satisfies the Tutte condition but has no perfect matching. Adding any edge to $G$ keeps the Tutte condition true, so we may assume $G$ is a maximal such graph. That is, $G$ has no perfect matching, but adding any edge $e$ not yet in $G$ makes $G+e$ have a perfect matching. Let $U\subseteq V$ be the set of all vertices of degree $|V|-1$. We can show that every connected component of $G-U$ is a complete graph. From this we can build a perfect matching of $G$: first take a maximum matching in each connected component of $G-U$; a component then has one unmatched vertex only when its number of vertices is odd. Match these unmatched vertices with vertices in $U$. Since $G$ has an even number of vertices (take $U=\varnothing$ in the Tutte condition), the number of vertices left unmatched in $U$ is also even, and we just pair them up. This contradiction shows that there is no $G$ that satisfies the Tutte condition but has no perfect matching.
    
    The key is to prove that every connected component of $G-U$ is a complete graph. Suppose not. Then we may assume vertices $x,y,z$ belong to such a component, with $(x,y)\in E$, $(y,z)\in E$ and $(x,z)\notin E$. Moreover, since $y\notin U$, there must be some $w\in V\setminus U$ with $(y,w)\notin E$. By the maximality of $G$, the graphs $G+(x,z)$ and $G+(y,w)$ have perfect matchings $M_1$ and $M_2$ respectively. Look at their symmetric difference $M_1\oplus M_2$. Every vertex of the graph $(V,M_1\oplus M_2)$ has degree $0$ or $2$, so $M_1\oplus M_2$ is actually a disjoint union of even cycles, and each even cycle alternates between edges of $M_1$ and edges of $M_2$. We may assume $(x,z)\in M_1$ and $(y,w)\in M_2$; otherwise $M_1$ or $M_2$ would already be a perfect matching of $G$. So both edges appear in $M_1\oplus M_2$.
    
    ![](images/tutte-proof.svg)
    
    As shown in the figure, there are two cases:
    
    -   $(x,z)$ and $(y,w)$ lie on different cycles (left of the figure): let $C$ be the cycle containing $(y,w)$. Then the edge set $M_2\oplus C$ is a perfect matching of $G$;
    -   $(x,z)$ and $(y,w)$ lie on the same cycle (right of the figure): by symmetry we may assume the cycle passes through $x,y,w,z$ in this order. Take the path $P$ on the cycle from $y$ through $w$ to $z$, and let $C$ be the cycle $\{(y,z)\}\cup P$. Then the edge set $M_2\oplus C$ is also a perfect matching of $G$.
    
    In either case we contradict the choice of $G$. This contradiction shows that every connected component of $G-U$ is a complete graph.

???+ note "Corollary"
    Every bridgeless 3‑regular graph has a perfect matching.

??? note "Proof"
    To check the Tutte condition, take any $U\subseteq V$; we need to show $\operatorname{odd}(G-U)\le |U|$. Let $G_1,\cdots,G_n$ be all the connected components of $G-U$ with an odd number of vertices. Let $m_i$ be the number of edges connecting vertices of $G_i$ to vertices of $U$. Simple counting gives
    
    $$
    3|V(G_i)| = \sum_{v\in V(G_i)} d(v) = 2|E(G_i)| + m_i.
    $$
    
    So $m_i$ must be odd. Since $G$ has no bridges (cut edges), $m_i\ge 3$. This shows
    
    $$
    \operatorname{odd}(G-U) = n \le \dfrac{1}{3}\sum_{i=1}^n m_i \le \dfrac{1}{3}\sum_{v\in U} d(v) = |U|.
    $$
    
    So the Tutte condition holds, and $G$ must have a perfect matching.

## Common algorithms

A basic problem in combinatorial optimization is finding a maximum matching and a maximum weight matching of a graph.

### Maximum matching in bipartite graphs

See the [Maximum matching in bipartite graphs](./bigraph-match.md) page for details.

In an unweighted bipartite graph, the problem can be solved in $O(|V||E|)$ time with Kuhn's algorithm, or in $O(|V|^{1/2}|E|)$ time with the Hopcroft–Karp algorithm.

### Maximum weight matching in bipartite graphs

See the [Maximum weight matching in bipartite graphs](./bigraph-weight-match.md) page for details.

In a weighted bipartite graph, the problem can be solved with the Hungarian algorithm. If the Bellman–Ford algorithm is used to find shortest paths, the time complexity is $O(|V|^2|E|)$; if Dijkstra's algorithm with a Fibonacci heap is used, it can be solved in $O(|V|^{2}\log {|V|}+|V||E|)$ time.

### Maximum matching in general graphs

See the [Maximum matching in general graphs](./general-match.md) page for details.

In an unweighted general graph, the problem can be solved in $O(|V|^2|E|)$ time with Edmonds' blossom algorithm.

### Maximum weight matching in general graphs

See the [Maximum weight matching in general graphs](./general-weight-match.md) page for details.

In a weighted general graph, the problem can be solved in $O(|V|^2|E|)$ time with Edmonds' blossom algorithm.

## Related problems

Maximum (weight) matching is closely connected to other graph problems. This section only discusses general graphs; for the results on bipartite graphs, see the [Maximum matching in bipartite graphs](./bigraph-match.md#相关问题) page.

### Maximum weight maximum cardinality matching

The maximum weight maximum cardinality matching problem and the maximum weight matching problem can be reduced to each other. One clear difference between them is that negative-weight edges may appear in a maximum weight maximum cardinality matching, but never in a maximum weight matching.

First, the maximum weight matching problem can be reduced to the maximum weight maximum cardinality matching problem. To do this, first set the weight of every negative-weight edge of $G$ to $0$. Then add edges of weight $0$ to extend the graph into a complete graph $G'$. Note that in a complete graph with non-negative edge weights, a maximum weight maximum cardinality matching is the same as a maximum weight matching. So we only need to compute a maximum weight maximum cardinality matching $M'$ of $G'$ and delete all zero-weight edges from $M'$; the resulting edge set $M$ is a maximum weight matching of $G$.[^other-approach]

![graph-match](images/graph-match-5.svg)

Conversely, the maximum weight maximum cardinality matching problem can be reduced to the maximum weight matching problem. Just add a large enough positive number $K$ to the weight of every edge of $G$. This guarantees that a maximum weight matching of the resulting graph $G'$ is also a maximum matching, and hence a maximum weight maximum cardinality matching. The reason is that computing a maximum weight matching of $G'$ is the same as maximizing, over all matchings of $G$,

$$
K|M| + \sum_{e\in M}w(e).
$$

When $K$ is large enough, the gain $K$ from matching one more edge outweighs any change in the second term, the sum of weights. So the algorithm first matches as many edges as possible, and only then maximizes the total weight of the matched edges. The constant $K$ just needs to be strictly larger than the difference between the total weights of any two matchings. An obvious choice is

$$
K = \sum_{e\in E}|w(e)| + 1.
$$

![graph-match](images/graph-match-6.svg)

### Minimum (weight) edge cover

Another problem closely related to maximum (weight) matching is minimum (weight) edge cover. The relationship between edge covers and matchings (also called independent edge sets) is similar to the relationship between vertex covers and independent sets.

A set of edges $C\subseteq E$ of a graph $G=(V,E)$ is called an **edge cover** of $G$ if every vertex $v\in V$ is an endpoint of some edge in $C$. When discussing edge covers, we always assume $G$ has no isolated vertices.

For unweighted graphs, the minimum edge cover problem is almost the same as the maximum matching problem. For any maximum matching $M$ of $G$, adding one incident edge for each unmatched vertex gives a minimum edge cover $C$. Their sizes satisfy a simple relation: $|M|+|C|=|V|$. The figure below shows some examples of minimum edge covers:

![graph-match](images/graph-match-7.svg)

For weighted graphs, the minimum weight edge cover problem can be reduced to a **minimum weight perfect matching** problem. First, make a copy $\tilde G=(\tilde V,\tilde E)$ of the graph $G=(V,E)$, with the same edge weights. Then connect each vertex $v\in V$ to its copy $\tilde v\in\tilde V$, with weight equal to the minimum weight among the edges of $G$ incident to $v$. Call the resulting graph $G'=(V',E')$. If $G$ is bipartite or sparse, then $G'$ is also bipartite or sparse, respectively. The minimum weight edge cover problem on $G$ then reduces to the minimum weight perfect matching problem on $G'$[^edge-cover]: for a minimum weight perfect matching $M'$ of $G'$, keep the edges that are in $E$, and replace every matched pair $(v,\tilde v)$ with the minimum-weight edge of $G$ incident to $v$. This gives a minimum weight edge cover of $G$.

## References

1.  [Wikiwand - Matching (graph theory)](https://www.wikiwand.com/en/Matching_%28graph_theory%29)
2.  [Wikiwand - Blossom algorithm](https://www.wikiwand.com/en/Blossom_algorithm)
3.  Chen Yinbo, *A Brief Discussion of Graph Matching Algorithms and Their Applications* (2015, in Chinese)
4.  [Algorithm Notes - Matching (Chinese)](http://web.ntnu.edu.tw/~algo/Matching.html)
5.  [the-tourist/algo](https://github.com/the-tourist/algo)
6.  [Bill Yang's Blog - Notes on the blossom algorithm (Chinese)](https://blog.bill.moe/blossom-algorithm-notes/)
7.  [Maximum matching, perfect matching and the Hungarian algorithm in bipartite graphs (Chinese)](https://www.renfei.org/blog/bipartite-matching.html)
8.  [Wikiwand - Hopcroft–Karp algorithm](https://www.wikiwand.com/en/Hopcroft%E2%80%93Karp_algorithm)
9.  Bondy, John Adrian, and Uppaluri Siva Ramachandra Murty. Graph theory with applications. Vol. 290. London: Macmillan, 1976.

[^other-approach]: Of course, this is not the only way to do the reduction. For a graph $G=(V,E)$, we can also attach a copy $\tilde G=(\tilde V,\tilde E)$ to the original graph vertex by vertex, and set the weight of every edge that is new relative to $G$ (including the edges in the copy) to $0$, giving a graph $G'=(V',E')$. In other words, the vertex set of $G'$ is $V\cup\tilde V$. Besides the edges of $G$, its edge set connects every vertex $v\in V$ to its copy $\tilde v\in\tilde V$ with a zero-weight edge, and for every edge $(u,v)\in E$, it connects $\tilde u$ and $\tilde v$ with a zero-weight edge. Every matching $M$ of $G$ corresponds to a perfect matching of $G'$ with the same total weight: match every unmatched vertex $v$ of $G$ with its copy $\tilde v$, and for every matched edge $(u,v)$, match $\tilde u$ with $\tilde v$. So a maximum weight maximum cardinality matching of $G'$, which is a maximum weight perfect matching, restricted to $E$, gives a maximum weight matching of $G$. The advantage of this reduction is that if $G$ is bipartite or sparse, then the extended graph $G'$ is also bipartite or sparse, respectively.

[^edge-cover]: Every perfect matching $M'$ of $G'$ gives an edge cover $C$ of $G$ in the way described here, and the total weight of $C$ is half that of $M'$; reversing this construction, every edge cover $C$ of $G$ gives a perfect matching $M'$ of $G'$ whose total weight is at most twice that of $C$. This shows the reduction is correct.
