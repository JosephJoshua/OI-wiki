This page gives an overview of some concepts in graph theory. Not all of them are common in OI. OI contestants only need to master the basic parts of this page; if you meet a concept you don't understand while studying, you can come back and look it up.

??? warning "Warning"
    Definitions in graph theory often differ between textbooks. When you meet one, judge its meaning from the context.

## Graph

A **graph** is a pair $G=(V(G), E(G))$. Here $V(G)$ is a non-empty set called the **vertex set**; each element of $V$ is called a **vertex** or **node**. $E(G)$ is the set of edges between the vertices of $V(G)$, called the **edge set**.

A graph is usually written $G=(V,E)$.

If both $V$ and $E$ are finite, $G$ is called a **finite graph**.

If $V$ or $E$ is infinite, $G$ is called an **infinite graph**.

There are several kinds of graphs, including **undirected graphs**, **directed graphs**, **mixed graphs** and so on.

If $G$ is an undirected graph, each element of $E$ is an unordered pair $(u, v)$ with $u, v \in V$, called an **undirected edge**, or simply an **edge**. For $e = (u, v)$, $u$ and $v$ are called the **endpoints** of $e$.

If $G$ is a directed graph, each element of $E$ is an ordered pair $(u, v)$, sometimes written $u \to v$, called a **directed edge** or **arc**; when there is no risk of confusion it can also be called an **edge**. For $e = u \to v$, $u$ is called the **tail** of $e$ and $v$ the **head** of $e$; the tail and head are also called the **endpoints** of $e$. We also say $u$ is a direct predecessor of $v$, and $v$ is a direct successor of $u$.

???+ note "Why is the start the tail and the end the head?"
    Edges are usually drawn as arrows, and an arrow points from its "tail" to its "head".

If $G$ is a mixed graph, $E$ contains both **directed edges** and **undirected edges**.

If each edge $e_k=(u_k,v_k)$ of $G$ is assigned a number as its **weight**, $G$ is called a **weighted graph**. If all weights are positive reals, $G$ is called a **positively weighted graph**.

The number of vertices $\left| V(G) \right|$ of a graph $G$ is also called the **order** of $G$.

Informally, a graph consists of some vertices and edges connecting pairs of vertices.

## Adjacency

In an undirected graph $G = (V, E)$, if vertex $v$ is an endpoint of edge $e$, then $v$ and $e$ are said to be **incident** (or **adjacent**). Two vertices $u$ and $v$ are **adjacent** if the edge $(u, v)$ exists.

The **neighborhood** of a vertex $v \in V$ is the set of all vertices adjacent to it, written $N(v)$.

The neighborhood of a vertex set $S$ is the set of all vertices adjacent to at least one vertex in $S$, written $N(S)$, that is:

$$
N(S) = \bigcup_{v \in S} N(v)
$$

## Simple graphs

**Loop**: an edge $e = (u, v)$ in $E$ with $u = v$ is called a loop (self-loop).

**Multiple edges**: if $E$ contains two identical elements (edges) $e_1, e_2$, they are called (a group of) multiple edges.

**Simple graph**: a graph with no loops and no multiple edges is called a simple graph. Any simple undirected graph with at least two vertices has two vertices of the same degree ([pigeonhole principle](../math/combinatorics/drawer-principle.md)).

A graph with loops or multiple edges is called a **multigraph**.

??? warning "Warning"
    In an undirected graph, $(u, v)$ and $(v, u)$ count as multiple edges, but in a directed graph, $u \to v$ and $v \to u$ are not multiple edges.

??? warning "Warning"
    In problems, unless stated otherwise, loops and multiple edges may exist, and you need to handle them specially.

## Degree

The number of edges incident to a vertex $v$ is called its **degree**, written $d(v)$. In particular, each edge $(v, v)$ contributes $2$ to $d(v)$.

For a simple undirected graph, $d(v) = \left| N(v) \right|$.

Handshaking lemma (also called the fundamental theorem of graph theory): for every undirected graph $G = (V, E)$, $\sum_{v \in V} d(v) = 2 \left| E \right|$.

Corollary: every graph has an even number of vertices of odd degree.

If $d(v) = 0$, $v$ is called an **isolated vertex**.

If $d(v) = 1$, $v$ is called a **leaf vertex**/**pendant vertex**.

If $2 \mid d(v)$, $v$ is called an **even vertex**.

If $2 \nmid d(v)$, $v$ is called an **odd vertex**. The number of odd vertices in a graph is even.

If $d(v) = \left| V \right| - 1$, $v$ is called a **universal vertex**.

For a graph, the minimum degree over all vertices is called the **minimum degree** of $G$, written $\delta (G)$; the maximum is called the **maximum degree**, written $\Delta (G)$. That is: $\delta (G) = \min_{v \in G} d(v)$, $\Delta (G) = \max_{v \in G} d(v)$.

In a directed graph $G = (V, E)$, the number of edges with tail $v$ is called the **out-degree** of $v$, written $d^+(v)$. The number of edges with head $v$ is called the **in-degree** of $v$, written $d^-(v)$. Clearly $d^+(v)+d^-(v)=d(v)$.

For every directed graph $G = (V, E)$:

$$
\sum_{v \in V} d^+(v) = \sum_{v \in V} d^-(v) = \left| E \right|
$$

If every vertex of an undirected graph $G = (V, E)$ has the same constant degree $k$, $G$ is called a **$k$-regular graph**.

If, for a given sequence a, there is a graph G with a as its degree sequence, a is called **graphic**.

If, for a given sequence a, there is a simple graph G with a as its degree sequence, a is called **simple-graphic** (realizable by a simple graph).

## Paths

**Walk**: a walk is a sequence of edges joining a sequence of vertices; it can be finite or infinite. Formally, a finite walk $w$ is a sequence of edges $e_1, e_2, \ldots, e_k$ such that there is a vertex sequence $v_0, v_1, \ldots, v_k$ with $e_i = (v_{i-1}, v_i)$ for $i \in [1, k]$. Such a walk can be written $v_0 \to v_1 \to v_2 \to \cdots \to v_k$. Usually the number of edges $k$ is called the **length** of the walk (if edges are weighted, the length usually means the sum of edge weights along the walk; a problem may also define it differently).

**Trail**: a walk $w$ is a trail if $e_1, e_2, \ldots, e_k$ are pairwise distinct.

**Path** (also called a **simple path**): a trail $w$ is a path if the vertices in its vertex sequence are pairwise distinct.

**Circuit**: a trail $w$ is a circuit if $v_0 = v_k$.

**Cycle** (also called a **simple circuit**): a circuit $w$ is a cycle if $v_0 = v_k$ is the only repeated pair in its vertex sequence.

??? warning "Warning"
    Definitions of paths may vary from place to place. For example, "path" may mean what this page calls a "walk", and "cycle" may mean what this page calls a "circuit". If you see such words in a problem with no clarification such as "simple path"/"non-simple path" (the latter being a "walk" here), it is best to ask what exactly is meant.

## Subgraphs

For a graph $G = (V, E)$, if another graph $H = (V', E')$ satisfies $V' \subseteq V$ and $E' \subseteq E$, then $H$ is a **subgraph** of $G$, written $H \subseteq G$.

If $H \subseteq G$ satisfies: for $\forall u, v \in V'$, whenever $(u, v) \in E$, also $(u, v) \in E'$, then $H$ is an **induced subgraph** of $G$.

It is easy to see that an induced subgraph is determined by its vertex set alone. So the induced subgraph with vertex set $V'$ ($V' \subseteq V$) is called the subgraph induced by $V'$, written $G \left[ V' \right]$.

If $H \subseteq G$ satisfies $V' = V$, $H$ is called a **spanning subgraph** of $G$.

Clearly, $G$ is a subgraph, a spanning subgraph and an induced subgraph of itself; the [edgeless graph](#special-graphs) is a spanning subgraph of $G$. The graph $G$ itself and the edgeless graph are both trivial subgraphs of $G$.

If a spanning subgraph $F$ of an undirected graph $G$ is $k$-regular, $F$ is called a **$k$-factor** of $G$.

If an induced subgraph $H = G \left[ V^\ast \right]$ of a directed graph $G = (V, E)$ satisfies: for $\forall v \in V^\ast, (v, u) \in E$, we have $u \in V^\ast$, then $H$ is called a **closed subgraph** of $G$.

## Connectivity

### Undirected graphs

In an undirected graph $G = (V, E)$, two vertices $u, v \in V$ are **connected** if there is a walk with $v_0 = u, v_k = v$. By definition, every vertex is connected to itself, and the two endpoints of any edge are connected.

If any two vertices of an undirected graph $G = (V, E)$ are connected, $G$ is called a **connected graph**, and this property of $G$ is called **connectivity**.

If $H$ is a connected subgraph of $G$ and there is no connected graph $F$ with $H\subsetneq F \subseteq G$, then $H$ is a **connected component** of $G$ (a maximal connected subgraph).

### Directed graphs

In a directed graph $G = (V, E)$, for $u, v \in V$, if there is a walk with $v_0 = u, v_k = v$, we say $u$ **can reach** $v$. By definition, every vertex can reach itself, and the tail of any edge can reach its head. (Connectivity in undirected graphs can be seen as reachability in both directions.)

If every pair of vertices in a directed graph can reach each other, the graph is **strongly connected**.

If replacing all edges of a directed graph with undirected edges gives a connected graph, the directed graph is **weakly connected**.

Similar to connected components, there are **weakly connected components** (maximal weakly connected subgraphs) and **strongly connected components** (maximal strongly connected subgraphs).

For related algorithms, see [strongly connected components](./scc.md).

### Cuts

For related algorithms, see [cut vertices and bridges](./cut.md) and [biconnected components](./bcc.md).

In this part, "connected" for directed graphs usually means "strongly connected".

For a connected graph $G = (V, E)$, if $V'\subseteq V$ and $G\left[V\setminus V'\right]$ (that is, $G$ with the vertices of $V'$ deleted) is not connected, then $V'$ is a **vertex cut/separating set** of $G$. A vertex cut of size one is called a **cut vertex**.

For a connected graph $G = (V, E)$ and an integer $k$, if $|V|\ge k+1$ and $G$ has no vertex cut of size $k-1$, $G$ is called **$k$-vertex-connected**, and the largest $k$ for which this holds is called the **vertex connectivity** of $G$, written $\kappa(G)$. (For a non-complete graph, the vertex connectivity is the size of a minimum vertex cut; for the complete graph $K_n$ it is $n-1$.)

For a graph $G = (V, E)$ and $u, v\in V$ with $u\ne v$, $u$ and $v$ not adjacent, and $u$ able to reach $v$: if $V'\subseteq V$, $u, v\notin V'$, and $u$ and $v$ are not connected in $G\left[V\setminus V'\right]$, then $V'$ is called a vertex cut from $u$ to $v$. The size of a minimum vertex cut from $u$ to $v$ is called the **local connectivity** from $u$ to $v$, written $\kappa(u, v)$.

Similar definitions can be made for edges:

For a connected graph $G = (V, E)$, if $E'\subseteq E$ and $G' = (V, E\setminus E')$ (that is, $G$ with the edges of $E'$ deleted) is not connected, then $E'$ is an **edge cut** of $G$. An edge cut of size one is called a **bridge**.

For a connected graph $G = (V, E)$ and an integer $k$, if $G$ has no edge cut of size $k-1$, $G$ is called **$k$-edge-connected**, and the largest $k$ for which this holds is called the **edge connectivity** of $G$, written $\lambda(G)$. (For every graph, the edge connectivity is the size of a minimum edge cut.)

For a graph $G = (V, E)$ and $u, v\in V$ with $u\ne v$ and $u$ able to reach $v$: if $E'\subseteq E$ and $u$ and $v$ are not connected in $G'=(V, E\setminus E')$, then $E'$ is called an edge cut from $u$ to $v$. The size of a minimum edge cut from $u$ to $v$ is called the **local edge-connectivity** from $u$ to $v$, written $\lambda(u, v)$.

**Biconnected** (vertex-biconnected) is almost exactly the same as $2$-vertex-connected, except for the graph made of two vertices joined by one edge: it is biconnected but not $2$-vertex-connected. In other words, a connected graph with no cut vertex is biconnected.

**Edge-biconnected ($2$-edge-connected)** is exactly the same as $2$-edge-connected. In other words, a connected graph with no bridge is edge-biconnected.

Similar to connected components, there are **biconnected components** (maximal biconnected subgraphs) and **$2$-edge-connected components** (maximal edge-biconnected subgraphs).

**Whitney's theorem**: for every graph $G$, $\kappa(G)\le \lambda(G)\le \delta(G)$. (The three terms are the vertex connectivity, the edge connectivity and the minimum degree.)

## Sparse and dense graphs

A graph whose number of edges is much smaller than the square of its number of vertices is a **sparse graph**.

A graph whose number of edges is close to the square of its number of vertices is a **dense graph**.

These two notions have no strict definition. They are mostly used when comparing the efficiency of algorithms with [time complexity](../basic/complexity.md) $O(|V|^2)$ and $O(|E|)$ (on dense graphs the two are about equally fast, while on sparse graphs the $O(|E|)$ algorithm is clearly faster).

## Complement graph

For a simple undirected graph $G = (V, E)$, its **complement graph**, written $\bar G$, is the graph with $V \left( \bar G \right) = V \left( G \right)$ such that for every pair of vertices $(u, v)$, $(u, v) \in E \left( \bar G \right)$ if and only if $(u, v) \notin E \left( G \right)$.

## Transpose graph

For a directed graph $G = (V, E)$, its **transpose graph** (reverse graph) has the same vertex set with every edge reversed. That is, if the transpose of $G$ is $G'=(V, E')$, then $E'=\{(v, u)|(u, v)\in E\}$.

## Special graphs

If a simple undirected graph $G$ has an edge between every two distinct vertices, $G$ is called a **complete graph**; the complete graph of order $n$ is written $K_n$. If a directed graph $G$ has two edges in opposite directions between every two distinct vertices, $G$ is called a **complete digraph**.

A graph with an empty edge set is called an **edgeless graph**, **empty graph** or **null graph**; the edgeless graph of order $n$ is written $\overline{K}_n$ or $N_n$. $N_n$ and $K_n$ are complements of each other.

??? warning "Warning"
    **Null graph** can also mean the **order-zero graph** $K_0$, that is, the graph whose vertex set and edge set are both empty.

If a simple directed graph $G$ has exactly one edge (in one direction) between every two distinct vertices, $G$ is called a **tournament graph**.

If all edges of a simple undirected graph $G = \left( V, E \right)$ form exactly one cycle, $G$ is called a **cycle graph**; the cycle graph of order $n$ ($n \geq 3$) is written $C_n$. It is easy to see that a graph is a cycle graph if and only if it is a connected $2$-regular graph.

If a simple undirected graph $G = \left( V, E \right)$ has a universal vertex $v$ and no edges among the other vertices, $G$ is called a **star graph**; the star graph of order $n + 1$ ($n \geq 1$) is written $S_n$.

If a simple undirected graph $G = \left( V, E \right)$ has a universal vertex $v$ and the other vertices form a cycle, $G$ is called a **wheel graph**; the wheel graph of order $n + 1$ ($n \geq 3$) is written $W_n$.

If all edges of a simple undirected graph $G = \left( V, E \right)$ form exactly one simple path, $G$ is called a **chain/path graph**; the path graph of order $n$ is written $P_n$. It is easy to see that a path graph is a cycle graph with one edge deleted.

A connected undirected graph with no cycle is called a **tree**. See [tree basics](./tree-basic.md) for more.

A connected undirected graph with exactly one cycle is called a **pseudotree** (unicyclic graph).

A weakly connected directed graph in which every vertex has in-degree $1$ is called an **out-pseudotree** (outward-directed pseudotree).

A weakly connected directed graph in which every vertex has out-degree $1$ is called an **in-pseudotree** (inward-directed pseudotree).

Several trees form a **forest**, several pseudotrees form a **pseudoforest**, several out-pseudotrees form an **out-pseudotree forest**, and several in-pseudotrees form an **in-pseudotree forest (functional graph)**.

A connected undirected graph in which every edge lies on at most one cycle is called a **cactus**. Several cacti form a **desert**.

If the vertex set of a graph can be split into two parts with no edges inside either part, the graph is a **bipartite graph**. If every two vertices in different parts of a bipartite graph are joined by an edge, it is a **complete bipartite graph/biclique**; the complete bipartite graph with parts of sizes $n$ and $m$ is written $K_{n, m}$. See [bipartite graphs](./bi-graph.md) for more.

If a graph can be drawn in the plane with no two edges crossing except at endpoints, it is a **planar graph**. For a simple connected planar graph $G=(V, E)$ with $V\ge 3$, $|E|\le 3|V|-6$.  
**Kuratowski's theorem**: a graph is planar if and only if it has no subgraph **homeomorphic** to $K_5$ or $K_{3, 3}$. Graphs $G$ and $G'$ are homeomorphic if both can be turned into the same graph by adding some vertices of degree $2$ on edges[^ref1].

## Isomorphism

For two graphs $G$ and $H$, if there is a bijection $f : V(G) \to V(H)$ such that $(u,v)\in E(G)$ if and only if $(f(u),f(v))\in E(H)$, then $f$ is called an **isomorphism** from $G$ to $H$, and $G$ and $H$ are **isomorphic**, written $G \cong H$.

From the definition, if $G \cong H$, then:

-   $|V(G)|=|V(H)|,|E(G)|=|E(H)|$
-   $G$ and $H$ have the same non-increasing degree sequence
-   $G$ and $H$ have isomorphic induced subgraphs

## Binary operations on simple undirected graphs

For simple undirected graphs, we can define the following binary operations:

**Intersection**: the intersection of graphs $G = \left( V_1, E_1 \right), H = \left( V_2, E_2 \right)$ is the graph $G \cap H = \left( V_1 \cap V_2, E_1 \cap E_2 \right)$.

It is easy to prove that the intersection of two simple undirected graphs is again a simple undirected graph.

**Union**: the union of graphs $G = \left( V_1, E_1 \right), H = \left( V_2, E_2 \right)$ is the graph $G \cup H = \left( V_1 \cup V_2, E_1 \cup E_2 \right)$.

**Sum/direct sum**: for $G = \left( V_1, E_1 \right), H = \left( V_2, E_2 \right)$, construct any $H' \cong H$ with $V \left( H' \right) \cap V_1 = \varnothing$ ($H'$ may equal $H$). Then any graph isomorphic to $G \cup H'$ is called the sum/direct sum/disjoint union of $G$ and $H$, written $G + H$ or $G \oplus H$.

If the vertex sets of $G$ and $H$ are already disjoint, then $G \cup H = G + H$.

For example, a forest can be defined as the sum of several trees.

???+ note "Union vs. sum"
    Think of it this way: "union" merges vertices and edges with "the same name" in the two graphs, while "sum" does not.

## Special vertex sets and edge sets

### Dominating set

For an undirected graph $G=(V, E)$, if $V'\subseteq V$ and $\forall v\in(V\setminus V')$ there is an edge $(u, v)\in E$ with $u\in V'$, then $V'$ is a **dominating set** of $G$.

The size of a minimum dominating set of an undirected graph $G$ is written $\gamma(G)$. Finding a minimum dominating set is [NP-hard](../misc/cc-basic.md#np-hard).

For a directed graph $G=(V, E)$, if $V'\subseteq V$ and $\forall v\in(V\setminus V')$ there is an edge $(u, v)\in E$ with $u\in V'$, then $V'$ is an **out-dominating set** of $G$. Similarly, we can define an **in-dominating set** of a directed graph.

The size of a minimum out-dominating set of a directed graph $G$ is written $\gamma^+(G)$, and that of a minimum in-dominating set is written $\gamma^-(G)$.

### Edge dominating set

For a graph $G=(V, E)$, if $E'\subseteq E$ and $\forall e\in(E\setminus E')$ shares an endpoint with some edge in $E'$, then $E'$ is an **edge dominating set** of $G$.

Finding a minimum edge dominating set is [NP-hard](../misc/cc-basic.md#np-hard).

### Independent set

For a graph $G=(V, E)$, if $V'\subseteq V$ and no two vertices of $V'$ are adjacent, then $V'$ is an **independent set** of $G$.

The size of a maximum independent set of $G$ is written $\alpha(G)$. Finding a maximum independent set is [NP-hard](../misc/cc-basic.md#np-hard).

### Matching

For a graph $G=(V, E)$, if $E'\subseteq E$, no two distinct edges of $E'$ share an endpoint, and no edge of $E'$ is a loop, then $E'$ is a **matching** of $G$, also called an **independent edge set**. A vertex that is an endpoint of some edge in the matching is called **matched/saturated**; otherwise it is called **unmatched**.

A matching with the most edges is called a **maximum-cardinality matching** of the graph. The size of a maximum matching of $G$ is written $\nu(G)$.

If edges are weighted, a matching with the largest total weight is called a **maximum-weight matching**.

If a matching stops being a matching after adding any edge, it is a **maximal matching**. The largest maximal matching is a maximum matching, and every maximum matching is maximal. A maximal matching is always an edge dominating set, but an edge dominating set is not necessarily a matching. A minimum maximal matching and a minimum edge dominating set have the same size, but a minimum edge dominating set is not necessarily a matching. Finding a minimum maximal matching is NP-hard.

If all vertices are matched in a matching, it is a **perfect matching**. If exactly one vertex is unmatched, it is a **near-perfect matching**.

Counting matchings or perfect matchings of a general graph or a bipartite graph is [#P-complete](../misc/cc-basic.md#p_1).

For a matching $M$, a path that starts at an unmatched vertex and whose consecutive edges alternate between being in the matching and not in the matching is called an **alternating path**; an alternating path that ends at an unmatched vertex is called an **augmenting path**.

**Tutte's theorem**: an undirected graph $G$ of order $n$ has a perfect matching if and only if for every $V' \subset V(G)$, $p_{\text{odd}}(G-V')\leq |V'|$, where $p_{\text{odd}}$ is the number of connected components of odd order.

**Tutte's theorem (corollary)**: every bridgeless 3-regular graph has a perfect matching.

### Vertex cover

For a graph $G=(V, E)$, if $V'\subseteq V$ and $\forall e\in E$, $e$ has at least one endpoint in $V'$, then $V'$ is a **vertex cover** of $G$.

A vertex cover is always a dominating set, but a minimal vertex cover is not necessarily a minimal dominating set.

A vertex set is a vertex cover if and only if its complement is an independent set, so the complement of a minimum vertex cover is a maximum independent set. Finding a minimum vertex cover is [NP-hard](../misc/cc-basic.md#np-hard).

The size of any matching in a graph is at most the size of any vertex cover. For the complete bipartite graph $K_{n, m}$, the maximum matching and the minimum vertex cover both have size $\min(n, m)$.

### Edge cover

For a graph $G=(V, E)$, if $E'\subseteq E$ and $\forall v\in V$, $v$ is incident to at least one edge of $E'$, then $E'$ is an **edge cover** of $G$.

The size of a minimum edge cover is written $\rho(G)$. It can be found by greedily extending a maximum matching: for every unmatched vertex, add one of its incident edges to the maximum matching, and the result is a minimum edge cover.

A maximum matching can also be found from a minimum edge cover: for each pair of edges in the minimum edge cover that share a vertex, delete one of them.

The size of a minimum edge cover plus the size of a maximum matching equals the number of vertices, that is, $\rho(G)+\nu(G)=|V(G)|$.

The size of a maximum matching is at most the size of a minimum edge cover, that is, $\nu(G)\le\rho(G)$. In particular, a perfect matching is always a minimum edge cover, and this is the only case where equality holds.

The size of any independent set in a graph is at most the size of any edge cover. For the complete bipartite graph $K_{n, m}$, the maximum independent set and the minimum edge cover both have size $\max(n, m)$.

### Clique

For a graph $G=(V, E)$, if $V'\subseteq V$ and any two distinct vertices of $V'$ are adjacent, then $V'$ is a **clique** of $G$. The induced subgraph of a clique is a complete graph.

If a clique stops being a clique after adding any vertex, it is a **maximal clique**.

The size of a maximum clique of a graph is written $\omega(G)$; it equals the size of a maximum independent set of the complement graph, that is, $\omega(G)=\alpha(\bar{G})$. Finding a maximum clique is [NP-hard](../misc/cc-basic.md#np-hard).

## References

[OI Transit - Overview of graph theory concepts](https://yhx-12243.github.io/OI-transit/memos/14.html)

[Wikipedia](https://en.wikipedia.org/wiki/Glossary_of_graph_theory_terms) (and the articles for the related concepts)

Discrete Mathematics (revised edition), by Tian Wencheng and Zhou Luxin, Tianjin Literature Publishing House, pp. 184-187

Dai Yiqi, Hu Guanzhang, Chen Wei. Graph Theory and Algebraic Structures \[M]. Beijing: Tsinghua University Press, 1995.

[^ref1]: This operation is also called subdivision.
