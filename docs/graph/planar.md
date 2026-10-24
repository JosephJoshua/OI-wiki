This page introduces planar graphs and related concepts.

## Planar graphs

If a graph $G$ can be drawn on a plane $S$ so that no two edges cross except at vertices, we say $G$ can be embedded in the plane $S$, and $G$ is a **planar graph**. Such a drawing with no crossing edges is called a planar representation or **planar embedding** of $G$. A planar embedding of a planar graph is also called a **plane graph**.

???+ info "\"Plane graph\""
    The Chinese term for "plane graph" can mean different things in different texts. In this article's definitions, a planar graph is a graph-theoretic object, and it may be embedded in the plane in different ways. A plane graph is a geometric object: besides the graph structure, it also fixes how the graph is drawn. One planar graph often corresponds to many plane graphs. So in this article, a result that depends only on the graph structure is stated for "planar graphs", and a result that also depends on the embedding is stated for "plane graphs".

Here are some simple examples of plane graphs:

![](images/planar-1.svg)

(Left: the butterfly graph; right: the complete graph $K_4$ on $4$ vertices)

Here are some simple examples of non-planar graphs:

![](images/planar-2.svg)

(Left: the complete graph $K_5$ on $5$ vertices; right: the complete bipartite graph $K_{3,3}$ with $3$ vertices on each side)

## Properties

This section introduces properties of plane graphs.

### Faces and their degrees

Let $G$ be a plane graph. The edges of $G$ divide the plane into several regions, and each region is called a **face** of $G$. The unbounded face is called the **unbounded face** or **external face**; the bounded ones are called finite faces or internal faces. Every plane graph has exactly one external face.

The closed walk formed by all the edges around a face is called the **boundary** of that face, and the edges on the boundary are said to be **incident** to the face. The length of the boundary is the **degree** of the face. When computing the degree of a face, every bridge is counted twice. In a plane graph, the sum of the degrees of all faces equals $2$ times the number of edges $|E|$.

In a plane graph, the boundary of a face of degree $1$ is a self-loop, and the boundary of a face of degree $2$ usually corresponds to a pair of parallel edges[^face-2]. In a simple connected plane graph with $|V|\ge 3$ vertices, every face has degree at least $3$.

### Euler's formula

An important property of plane graphs is **Euler's formula**. It gives the relation between the number of vertices $|V|$, the number of edges $|E|$ and the number of faces $|F|$.

???+ note "Euler's formula"
    For a connected plane graph $G$,
    
    $$
    |V| - |E| + |F| = 2.
    $$

??? note "Proof"
    Use induction on the number of faces $|F|$. The base case is $|F|=1$. Then the plane graph has only the external face, and every edge is a bridge. So $G$ is a tree and $|E|=|V|-1$; plugging this in shows that Euler's formula holds. Now assume Euler's formula holds for plane graphs with $|F| = k$ faces. For a plane graph $G$ with $|F|=k + 1$ faces, there must be an edge $e$ that is not a bridge, and it is shared by two different faces. Delete $e$ from the graph to get $G-e$, which has $|V|$ vertices, $|E|-1$ edges and $|F|-1$ faces. By the induction hypothesis, Euler's formula holds for $G-e$, that is, $|V|-(|E|-1)+(|F|-1)=2$. Rearranging gives Euler's formula for $G$. So by induction, Euler's formula holds for all connected plane graphs.

???+ note "Corollary"
    For a plane graph $G$ with $k$ connected components,
    
    $$
    |V| - |E| + |F| = k + 1.
    $$

??? note "Proof"
    Each connected component of $G$ is a plane graph, but they all share the same external face. If we apply Euler's formula to each component and add the results, the total numbers of vertices and edges are correct, but the total number of faces is too large by $(k-1)$, because the single external face is counted $k$ times. Taking this correction into account gives $|V|-|E|+|F| = 2k - (k-1) = k+1$.

From this, we can derive a relation between the numbers of edges and vertices of a plane graph.

???+ note "Theorem"
    For a plane graph $G$ with $k$ connected components, if every face of $G$ has degree at least $l \ge 3$, then
    
    $$
    |E| \le \dfrac{l}{l-2}(|V|-k-1).
    $$

??? note "Proof"
    Since every face of $G$ has degree at least $l$, the sum of the face degrees is at least $l|F|$, that is, $2|E| \ge l|F|$. Substituting into the corollary of Euler's formula $|V| - |E| + |F| = k + 1$ gives
    
    $$
    2|E| \ge l(k + 1 - |V| + |E|).
    $$
    
    Using $l \ge 2$ and solving for $|E|$ gives
    
    $$
    |E| \le \dfrac{l}{l-2}(|V|-k-1).
    $$

???+ note "Corollary"
    Let $G$ be a simple planar graph with $|V|\ge 3$. Then
    
    $$
    |E| \le 3|V|-6.
    $$

??? note "Proof"
    When $G$ is connected, every face has degree at least $3$. Taking $k=1$ and $l=3$ in the theorem above gives $|E|\le 3|V|-6$.
    
    When $G$ is not connected, there are two cases:
    
    -   If some connected component has at least $3$ vertices, then for each such component we get the inequality $|E_i|\le 3|V_i|-6$. The components with fewer than $3$ vertices always satisfy $|E_i|\le |V_i| \le 3|V_i|$. Adding the inequalities for all components gives $|E|\le 3|V|-6$.
    -   If every connected component has fewer than $3$ vertices, then overall $|E|\le |V|$. Since $|V|\le 3|V|-6$ when $|V|\ge 3$, $|E|\le 3|V|-6$ still holds.
    
    This proves the claim.

This corollary shows that simple planar graphs are sparse.

### Dual graphs

Every plane graph has a corresponding (geometric) dual graph.

![](images/planar-dual-1.svg)

Let $G$ be a plane graph. We can draw a graph $G^*$ as follows:

1.  Inside each face $f_i$ of $G$, draw a point $v_i^*$.
2.  For each edge $e$ of $G$, if $e$ lies on the common boundary of faces $f_i$ and $f_j$, draw an edge $e^*$ joining $v_i^*$ and $v_j^*$ so that it crosses $e$ exactly once and crosses no other edge of $G$ or $G^*$. In particular, if $e$ lies on the boundary of only one face $f_i$, draw a self-loop at $v_i^*$ that crosses $e$.

The graph $G^*$ obtained this way is called the **dual graph** of $G$.

???+ note "Theorem"
    Let $G^*$ be the dual graph of a plane graph $G$. Then $G^*$ is a connected plane graph. Moreover, $G^{**}$ is isomorphic to $G$ if and only if $G$ is connected.

??? note "Proof"
    The construction guarantees that $G^*$ is a plane graph. We still need to show that $G^*$ is connected. For any two vertices $v^*_i,v^*_j$ of $G^*$, suppose the straight segment joining $v^*_i$ and $v^*_j$ in the plane passes, in order, through the faces and edges $f_i,e_{s_1},f_{s_1},\cdots,f_{s_{r-1}},e_{s_r},f_j$ of $G$. These correspond to the vertices and edges $v_i^*,e_{s_1}^*,v^*_{s_1},\cdots,v^*_{s_{r-1}},e^*_{s_r},v^*_j$ of the dual graph. By the construction of $G^*$, adjacent vertices and edges in this sequence are incident, so this describes a walk in $G^*$. Hence $G^*$ is connected.
    
    $G^{**}$ is the dual graph of $G^*$, so it must be connected. So for $G$ to be isomorphic to $G^{**}$, it is necessary that $G$ is connected. Next we show that this condition is also sufficient. For this, it is enough to show that when $G$ is connected, $G$ satisfies the requirements of the construction of the dual graph of $G^*$. Since the edges of $G^*$ naturally correspond to the edges of $G$, we only need to show that each face of $G^*$ contains exactly one vertex of $G$. For any face $f^*$ of $G^*$, let $e^*$ be an edge on its boundary; then one endpoint of the corresponding edge $e$ in $G$ must lie inside $f^*$. So the face $f^*$ contains at least one vertex of $G$. Since $G^*$ and $G$ are both connected, Euler's formula holds for both. The two graphs have the same number of edges, and the number of faces of $G$ equals the number of vertices of $G^*$, so the number of vertices of $G$ equals the number of faces of $G^*$. Therefore each face of $G^*$ contains exactly one vertex of $G$. This proves the claim.

There are many correspondences between the structure of a plane graph and that of its dual:

-   Faces of $G$ correspond to vertices of $G^*$, edges of $G$ correspond to edges of $G^*$, and vertices of $G$ correspond to faces of $G^*$.
-   Self-loops in $G$ correspond to bridges in $G^*$, and self-loops in $G^*$ correspond to bridges in $G$.
-   Edge cuts in $G$ correspond to cycles in $G^*$, and cycles in $G^*$ correspond to edge cuts in $G$.

Note that the dual graph is defined only for a specific plane graph, not for an arbitrary planar graph. In fact, two isomorphic plane graphs may have non-isomorphic duals. In other words, different planar embeddings of the same graph can have different dual graphs.

???+ example "Example"
    The figure below shows two isomorphic plane graphs whose dual graphs are not isomorphic.
    
    ![](images/planar-dual-2.svg)
    
    The duals are not isomorphic because the right graph has a face of degree $1$, so its dual has a vertex of degree $1$, while the left graph does not.

Moving a problem on a planar graph over to its dual graph sometimes makes it easier to solve. A typical example is that the [minimum cut](./flow/min-cut.md) problem on a planar graph can be turned into a [shortest path](./shortest-path.md) problem on the dual graph. Let $G$ be an edge-weighted planar graph and $s,t$ two of its vertices; we want the minimum $s$-$t$ cut.

![](images/planar-dual-3.svg)

As shown in the figure, pick a suitable planar embedding so that $s,t$ both lie on the boundary of the external face of $G$. Then add rays going out from $s$ and $t$, which split the external face into two parts $f_{+}$ and $f_{-}$. Build the dual graph of this drawing and give each dual edge the weight of its corresponding edge. Then the paths in $G^*$ between the vertices for $f_{+}$ and $f_{-}$ (thick red lines) correspond one-to-one to the $s$-$t$ edge cuts of $G$ (thick black lines), with the same weights. So computing a shortest path in the dual graph gives the minimum $s$-$t$ cut of $G$.

A common mistake is to claim, based on this method, that the minimum cut of a planar graph always equals a shortest path in the dual graph. In fact, it only works when $G$ has a planar embedding in which $s$ and $t$ lie on the same face. It is just that in contest problems testing this topic, the given graph usually has such an embedding, and the embedding is usually given along with it. Here is a theorem that can be used to check whether such an embedding exists.

???+ note "Theorem"
    For two vertices $s,t$ of a planar graph $G=(V,E)$, there is a planar embedding of $G$ in which $s,t$ lie on the same face if and only if $(V,E \cup \{(s,t)\}$ is planar.

??? note "Proof"
    If $G$ has a planar embedding in which $s,t$ lie on the same face, we can add an edge $(s,t)$ inside this face and the graph stays planar.
    
    If $(V, E \cup \{(s,t)\})$ is planar, take any planar embedding of it; $s,t$ both lie on a face containing the edge $(s,t)$. After deleting $(s,t)$, $s,t$ still lie on the same face. This proves the claim.

For example, in the figure below, adding the edge $(s,t)$ gives the non-planar graph $K_5$, so no such embedding exists and the method above does not apply.

![](images/planar-st.svg)

### More results

Of course, planar graphs have many other famous results. This section just lists some of them without discussion.

???+ note "Four color theorem"
    Every plane graph (without self-loops) is $4$‑colorable.

???+ note "Fáry's theorem"
    Every simple planar graph has a planar embedding in which all edges are straight line segments.

???+ note "Theorem (Wood)"
    A planar graph has at most $8|V|-16$ maximal cliques.

???+ note "Theorem (Tutte)"
    Every $4$‑vertex-connected planar graph is Hamiltonian.

## Planarity testing

This section discusses how to decide whether a given graph is planar.

### Forbidden graphs

The most classic characterization of planar graphs uses **forbidden graphs**.

First, $K_5$ and $K_{3,3}$ are not planar.

???+ note "Theorem"
    $K_5$ and $K_{3,3}$ are not planar.

??? note "Proof"
    As shown above, every simple connected plane graph with $|V|\ge 3$ must satisfy
    
    $$
    |E| \le \dfrac{l}{l-2}(|V|-2).
    $$
    
    Here, $l$ is the minimum face degree. For $K_5$, $l=3,~|V|=5,~|E|=10$, so $K_5$ cannot be drawn as a plane graph. For $K_{3,3}$, $l=4,~|V|=6,~|E|=9$, so $K_{3,3}$ cannot be drawn as a plane graph.

In fact, they are the smallest structures that make a graph non-planar. That is, as long as a graph does not contain these two graphs as substructures (in a certain sense), it must be planar.

The first planarity criterion is Kuratowski's theorem. It uses the idea of graph homeomorphism: two graphs $G_1$ and $G_2$ are **homeomorphic** if they are isomorphic, or become isomorphic after repeatedly inserting or removing vertices of degree $2$. With this, we can state the following result:

???+ note "Kuratowski's theorem"
    A graph $G$ is planar if and only if $G$ has no subgraph homeomorphic to $K_5$ or $K_{3,3}$.

Another related theorem is Wagner's theorem. It characterizes planar graphs using contractions. A contraction means repeatedly contracting an edge of the graph into a single vertex. With this, we can state the following result:

???+ note "Wagner's theorem"
    A graph $G$ is planar if and only if $G$ has no subgraph that can be contracted to $K_5$ or $K_{3,3}$.

It is fairly obvious that a planar graph contains no such subgraphs, so the key part of both theorems is that the forbidden graph condition is sufficient. A subgraph homeomorphic to $K_5$ or $K_{3,3}$ can always be contracted to it, but not the other way around. So Kuratowski's theorem gives a weaker condition for planarity that is also easier to check.

### Planarity testing algorithms

Although it may not look easy, the planarity testing problem actually has many linear-time algorithms. However, these algorithms are usually complex to implement, so they almost never appear in competitive programming.

The earliest linear-time algorithm is the Hopcroft–Tarjan algorithm[^ht74], but it is quite complex to implement. The de Fraysseix–Ossona de Mendez–Rosenstiehl algorithm (also called the LR planarity algorithm)[^dor06][^df08][^bra09] further improves the procedure of the Hopcroft–Tarjan algorithm and is one of the best planarity testing algorithms today. Python's NetworkX library [implements](https://github.com/networkx/networkx/blob/main/networkx/algorithms/planarity.py) this algorithm.

Another equally good algorithm is the Boyer–Myrvold algorithm[^bm99][^bm04]. It decides in linear time whether a given graph is planar. Moreover, if the graph is planar, it outputs a planar embedding; otherwise it outputs a Kuratowski subgraph (a subgraph homeomorphic to $K_5$ or $K_{3,3}$). C++'s Boost library [implements](https://www.boost.org/doc/libs/1_67_0/boost/graph/planar_detail/boyer_myrvold_impl.hpp) this algorithm.

For more related algorithms, see the references at the end of this page.

## Special planar graphs

This section introduces several special classes of planar graphs.

### Maximal planar graphs

A simple planar graph $G$ is called **maximal planar** if adding an edge between any two non-adjacent vertices makes it non-planar. A planar embedding of a maximal planar graph is called a **maximal plane graph**.

???+ note "Theorem"
    A maximal planar graph $G$ is always connected. Moreover, when $|V|\ge 3$, $G$ has no bridges.

??? note "Proof"
    If a planar graph $G$ is not connected, take any planar embedding of it. We can pick two vertices from different connected components and join them inside the external face. The resulting graph is clearly still a plane graph, so $G$ is not maximal planar. Hence a maximal planar graph $G$ must be connected.
    
    Suppose a planar graph $G$ has $|V|\ge 3$ vertices and a bridge $e=(u,v)$. Then $G - e$ has exactly two connected components, with $u$ and $v$ in different components. Assume the component containing $v$ has at least two vertices. First draw the component $G_1$ containing $u$ in the plane, pick any face $f$ of $G_1$ whose boundary contains $u$, and draw the other component $G_2$ inside $f$. Since $G_2$ is simple, the boundary of its external face cannot be a single self-loop, so it contains another vertex $w\neq u,v$. Joining both $v$ and $w$ to $u$ gives a plane graph that contains $G$ as a subgraph. So $G$ is not maximal planar. Therefore a maximal planar graph with $|V|\ge 3$ has no bridges.

The structure of maximal plane graphs can be described more precisely.

???+ note "Theorem"
    A plane graph $G$ with $|V|\ge 3$ vertices is a maximal plane graph if and only if it is simple and every face has degree $3$.

??? note "Proof"
    Sufficiency is obvious. We only need necessity, that is, to show that every face of a maximal plane graph $G$ with $|V|\ge 3$ has degree $3$. Since $G$ is a connected simple plane graph with $|V|\ge 3$, every face has degree at least $3$. So if the claim were false, some face $f$ would have a boundary of length at least $4$. Since $G$ has no bridges, this boundary must be a cycle; call it $v_1v_2v_3v_4\cdots v_1$. If $v_1$ and $v_3$ were not adjacent, joining them inside $f$ would not break planarity, contradicting the maximality of $G$. So $v_1$ and $v_3$ are adjacent; similarly, $v_2$ and $v_4$ are adjacent. But neither edge $(v_1,v_3)$ nor $(v_2,v_4)$ lies inside face $f$. So both edges must lie outside $f$. This is impossible: no matter how they are drawn, the two edges must cross. So $G$ has no face of degree more than $3$, which proves the claim.

???+ note "Corollary"
    For such a graph $G$ with $|V|\ge 3$ vertices, the number of edges is always $|E|=3|V|-6$ and the number of faces is $|F|=2|V|-4$.

Since every face of a maximal plane graph is bounded by three edges, maximal plane graphs are also called **plane triangulations**.

### Outerplanar graphs

Let $G$ be a planar graph. If $G$ has a planar embedding $\tilde{G}$ in which all vertices of $G$ lie on the boundary of one face of $\tilde{G}$, then $G$ is called an **outerplanar graph**. Such an embedding is called an outerplanar embedding or an **outerplane graph**. Usually, the face whose boundary passes through all vertices is drawn as the external face.

![](images/planar-outer.svg)

Every outerplanar graph is planar, but not the other way around. Outerplanar graphs can also be characterized by forbidden graphs.

???+ note "Theorem"
    A graph $G$ is outerplanar if and only if $G$ has no subgraph homeomorphic to $K_4$ or $K_{2,3}$.

For outerplanar graphs we can also talk about maximal outerplanar graphs. A simple outerplanar graph $G$ is called **maximal outerplanar** if adding an edge between any two non-adjacent vertices makes it no longer outerplanar. An outerplanar embedding of a maximal outerplanar graph is called a **maximal outerplane graph**. A maximal outerplane graph is really just a triangulation of a polygon in the plane.

???+ note "Theorem"
    Let $G$ be a maximal outerplane graph with $|V|\ge 3$ vertices, all lying on the boundary of the external face. Then $G$ has exactly $|V|-2$ internal faces.

??? note "Proof"
    Use induction on $|V|$. The base case is $|V|=3$: $G$ is a triangle with only $1$ internal face, so the claim holds. Assume the claim holds for $|V| = k$. We now show it still holds for $|V| = k+1$.
    
    First, $G$ must have a vertex of degree $2$. Otherwise, every vertex is joined to some third vertex besides its neighbors on the boundary of the external face. Number the vertices on the boundary of the external face in order, and for each $i = 1,2,\cdots,k+1$ define $f(i)$ as the smallest number of a vertex joined to vertex $i$ that is not next to $i$ in the numbering. Consider the possible values of $f(i)$. First, $1 < f(1)$. Since vertex $1$ is already joined to $f(1)$, the edge from vertex $2$ to $f(2)$ cannot cross the edge $(1,f(1))$, so $1 < 2 < f(2) < f(1)$. Similarly, $2 < 3 < f(3) < f(2)$. Since there are only finitely many vertices, this shrinking process must stop after finitely many steps. Let $i^*$ be the largest $i$ satisfying $1 < \cdots < i-1 < i < f(i) < f(i-1) < \cdots < f(1)$. Since vertices $i^*$ and $f(i^*)$ are not adjacent in the numbering, $i^* < i^* + 1 < f(i^*)$. Repeating the earlier argument, we should still have $i^* < i^*+1 < f(i^*+1) < f(i^*)$, which contradicts the maximality of $i^*$. This contradiction shows that $G$ must have a vertex of degree $2$.
    
    Let $v$ be a vertex of degree $2$. Deleting it from $G$ gives an outerplane graph $G-v$ with $k$ vertices. It must be maximal outerplane; otherwise any valid way to add an edge to it would also work for $G$. By the induction hypothesis, $G-v$ has exactly $k-2$ internal faces, and deleting $v$ removes exactly one internal face of $G$. So $G$ has $k-1$ internal faces. This proves the claim.

???+ note "Theorem"
    Let $G$ be an outerplane graph with $|V|\ge 3$ vertices, all lying on the boundary of the external face. Then $G$ is a maximal outerplane graph if and only if the boundary of its external face is a cycle of length $|V|$ and the boundary of every internal face is a cycle of length $3$.

??? note "Proof"
    Sufficiency is obvious. Indeed, consider joining two non-adjacent vertices on the boundary of the external face. If the edge is drawn in the external face, then the vertices can no longer all lie on the boundary of one face; otherwise, the edge must cross the boundary of an internal face.
    
    Next we prove necessity. Suppose the boundary $v_1v_2v_3\cdots v_nv_1~(n = |V|)$ of the external face of $G$ is not a cycle. Then it passes through some vertex more than once, that is, there are $i\neq j$ with $i-j\neq\pm 1\pmod{n}$ and $v_i=v_j$. Without loss of generality let $1 < i < j < n$. Then the edges incident to $v_{i-1}$ can only lie inside the bounded region enclosed by the closed walk $v_jv_{j+1}\cdots v_nv_1\cdots v_{i-1}v_i$, and the edges incident to $v_{i+1}$ can only lie inside the bounded region enclosed by the closed walk $v_iv_{i+1}\cdots v_{j-1}v_{j}$. So $v_{i-1}$ and $v_{i+1}$ cannot be adjacent. We can add an edge $e$ joining $v_{i-1}$ and $v_{i+1}$ inside the external face to get $G+e$. This is clearly still a plane graph, and all its vertices still lie on the boundary of the external face. This contradicts the maximality of $G$. So the external face of $G$ must be a cycle of length $|V|$. The reason that every internal face of $G$ is bounded by a cycle of length $3$ is the same as for maximal plane graphs, so we do not repeat it.

???+ note "Corollary"
    For a maximal outerplane graph $G$ with $|V|\ge 3$ vertices:
    
    1.  $|E|=2|V|-3$.
    2.  $G$ has at least $3$ vertices of degree at most $3$, and at least $2$ vertices of degree $2$.
    3.  The vertex connectivity of $G$ is $2$.

## Exercises

-   [Luogu P3209 \[HNOI2010\] Planarity Testing](https://www.luogu.com.cn/problem/P3209)
-   [Luogu P3249 \[HNOI2016\] Mining Area](https://www.luogu.com.cn/problem/P3249)
-   [Luogu P4001 \[ICPC-Beijing 2006\] Wolf Catching Rabbits](https://www.luogu.com.cn/problem/P4001)
-   [Luogu P4073 \[WC2013\] Plane Graph](https://www.luogu.com.cn/problem/P4073)
-   [Luogu P7295 \[USACO21JAN\] Paint by Letters P](https://www.luogu.com.cn/problem/P7295)

## References and notes

-   [Planar graph - Wikipedia](https://en.wikipedia.org/wiki/Planar_graph)
-   [Planarity testing - Wikipedia](https://en.wikipedia.org/wiki/Planarity_testing)
-   Bondy, John Adrian, and Uppaluri Siva Ramachandra Murty. Graph theory with applications. Vol. 290. London: Macmillan, 1976.
-   Diestel, Reinhard. Graph theory. Vol. 173. Springer Nature, 2025.
-   Patrignani, Maurizio. "Planarity Testing and Embedding." (2013): 1-42.

[^face-2]: But this is not the only possibility. Two nested self-loops also form a face of degree $2$. Also, a face of degree $2$ does not mean the graph is not simple. For example, in a graph with a single edge, the only face (the external face) has degree $2$.

[^ht74]: Hopcroft, John, and Robert Tarjan. "Efficient planarity testing." Journal of the ACM (JACM) 21, no. 4 (1974): 549-568.

[^dor06]: De Fraysseix, Hubert, Patrice Ossona De Mendez, and Pierre Rosenstiehl. "Trémaux trees and planarity." International Journal of Foundations of Computer Science 17, no. 05 (2006): 1017-1029.

[^df08]: De Fraysseix, Hubert. "Trémaux trees and planarity." Electronic Notes in Discrete Mathematics 31 (2008): 169-180.

[^bra09]: Brandes, Ulrik. "The left-right planarity test." Manuscript submitted for publication 3 (2009).

[^bm99]: Boyer, John M., and Wendy J. Myrvold. "Stop Minding Your p's and q's: A Simplified O (n) Planar Embedding Algorithm." In SODA, vol. 99, pp. 140-146. 1999.

[^bm04]: Boyer, John M., and Wendy J. Myrvold. "Simplified o (n) planarity by edge addition." Graph Algorithms and Applications 5 (2006): 241.
