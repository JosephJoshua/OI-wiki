author: jifbt, Mayuri0v0

## Definition

For definitions of the following, see [basic graph theory concepts](./concept.md):

-   edge connectivity, edge cut;
-   vertex connectivity, vertex cut;
-   clique.

## Properties

### Whitney's inequality

**Whitney's inequality** (1932) relates the vertex connectivity $\kappa$, the edge connectivity $\lambda$ and the minimum degree $\delta$:

$$
\kappa \le \lambda \le \delta
$$

???+ note "Proof"
    Intuitively, given an edge cut of size $\lambda$, picking one endpoint of each of its edges gives a vertex cut of size $\lambda$, so the first inequality holds.
    
    All edges incident to a vertex of minimum degree (pick any one if there are several) form an edge cut of size $\delta$, so the second inequality also holds.

This inequality cannot be improved: for every triple satisfying it, there is a graph with exactly those values.

???+ note "Construction"
    Connect two cliques of size $\delta + 1$ with $\lambda$ edges, so that $\lambda$ distinct vertices of one clique and $\kappa$ distinct vertices of the other are attached to these edges.

### Menger's theorem

The [max-flow min-cut theorem](./flow/min-cut.md) (also called the Ford–Fulkerson theorem) implies that the maximum number of disjoint paths (pairwise sharing no edge) between two vertices equals the minimum size of a cut between them (this corollary is also called **Menger's theorem** — translator's note).

## Computation

All graphs below have edge weights $1$.

### Edge connectivity via maximum flow

Enumerate pairs $(s, t)$ and run a maximum flow with edge weights $1$ from source $s$ to sink $t$. This needs $O(n^2)$ maximum flows; with the Edmonds–Karp algorithm the complexity is $O(|V|^3 |E|^2)$. Dinic's algorithm does better, with complexity $O(|V|^2 |E| \min(|V|^{2/3}, |E|^{1/2}))$.

### Global minimum cut

With the [Stoer–Wagner algorithm](./stoer-wagner.md), a single run of a minimum cut without a fixed source and sink is enough. The complexity is $O(|V||E| + |V|^{2}\log|V|)$, usually treated as roughly $O(|V|^3)$.

### Vertex connectivity

Again enumerate pairs of vertices. This time split each vertex $x$ other than the source and sink into two vertices $x_1$ and $x_2$, and add an edge $(x_1, x_2)$. Replace every edge $(u, v)$ of the original graph with two edges $(u_2, v_1)$ and $(v_2, u_1)$. The maximum flow then equals the size of a minimum vertex cut between $s$ and $t$ (also called the local vertex connectivity). The complexity is the same as computing edge connectivity via maximum flow.

**This page is translated from the posts [Рёберная связность. Свойства и нахождение](http://e-maxx.ru/algo/rib_connectivity) and [Вершинная связность. Свойства и нахождение](http://e-maxx.ru/algo/vertex_connectivity) and their English translation [Edge connectivity/Vertex connectivity](https://cp-algorithms.com/graph/edge_vertex_connectivity.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**

## Further reading

-   The paper [*Connectivity Algorithms*](https://www.cse.msu.edu/~cse835/Papers/Graph_connectivity_revised.pdf) surveys recent progress in algorithms for computing connectivity. Interested readers can take a look.
