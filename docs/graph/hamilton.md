## Definition

A path that visits every vertex of the graph exactly once is called a Hamiltonian path.

A cycle that visits every vertex of the graph exactly once is called a Hamiltonian cycle.

A graph that has a Hamiltonian cycle is called a Hamiltonian graph.

A graph that has a Hamiltonian path but no Hamiltonian cycle is called a semi-Hamiltonian graph.

## Properties

Let $G=\langle V, E\rangle$ be a Hamiltonian graph. Then for every nonempty proper subset $V_1$ of $V$, we have $p(G-V_1) \leq |V_1|$, where $p(x)$ is the number of connected components of $x$.

Corollary: Let $G=\langle V, E\rangle$ be a semi-Hamiltonian graph. Then for every nonempty proper subset $V_1$ of $V$, we have $p(G-V_1) \leq |V_1|+1$, where $p(x)$ is the number of connected components of $x$.

The complete graph $K_{2k+1} (k \geq 1)$ contains $k$ edge-disjoint Hamiltonian cycles, and together these $k$ edge-disjoint Hamiltonian cycles contain all edges of $K_{2k+1}$.

The complete graph $K_{2k} (k \geq 2)$ contains $k-1$ edge-disjoint Hamiltonian cycles. After removing these $k-1$ edge-disjoint Hamiltonian cycles from $K_{2k}$, the remaining graph consists of $k$ pairwise non-adjacent edges.

## Sufficient conditions

Let $G$ be a simple undirected graph with $n(n \geq 2)$ vertices. If every pair of non-adjacent vertices $v_i, v_j$ in $G$ satisfies $d(v_i)+ d(v_j) \geq n - 1$, then $G$ has a Hamiltonian path.

Corollary 1: Let $G$ be a simple undirected graph with $n(n \geq 3)$ vertices. If every pair of non-adjacent vertices $v_i, v_j$ in $G$ satisfies $d(v_i)+ d(v_j) \geq n$, then $G$ has a Hamiltonian cycle, so $G$ is a Hamiltonian graph.

Corollary 2: Let $G$ be a simple undirected graph with $n(n \geq 3)$ vertices. If every vertex $v_i$ in $G$ satisfies $d(v_i) \geq \frac{n}{2}$, then $G$ has a Hamiltonian cycle, so $G$ is a Hamiltonian graph.

Let $D$ be a tournament with $n(n \geq 2)$ vertices. Then $D$ has a Hamiltonian path.

If $D$ contains a tournament with $n(n \geq 2)$ vertices as a subgraph, then $D$ has a Hamiltonian path.

A strongly connected tournament is a Hamiltonian graph.

If $D$ contains a strongly connected tournament with $n(n \geq 2)$ vertices as a subgraph, then $D$ has a Hamiltonian cycle.
