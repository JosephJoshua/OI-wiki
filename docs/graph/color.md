## Vertex coloring

(We consider undirected graphs without self-loops.)

We color the vertices of an undirected graph so that adjacent vertices never share a color. If G is $k$-colorable but not $(k-1)$-colorable, then k is called the chromatic number of G, written $\chi(G)$.

For every graph G, $\chi(G) \leq \Delta(G) + 1$, where $\Delta(G)$ is the maximum degree.

### Brooks' theorem

If a connected graph is neither a complete graph nor an odd cycle, then $\chi(G) \leq \Delta(G)$.

#### Proof

???+ note "Proof"
    Let $|V(G)|=n$ and use induction.
    
    First, for $n\leq 3$ the statement clearly holds.
    
    Next, assume the statement holds for $n-1$. We will strengthen the claim step by step.
    
    We may consider only $\Delta(G)$-regular graphs, since a non-regular graph can be seen as a regular graph with some edges deleted, and this does not affect the conclusion.
    
    For any regular graph G that is neither complete nor an odd cycle, pick any vertex v and consider the subgraph $H:=G-v$. By the induction hypothesis $\chi(H)\leq\Delta(H)=\Delta(G)$. We just need to show that inserting v back into H does not break the conclusion.
    
    Let $\Delta:=\Delta(G)$, let the $\Delta$ colors used on H be $c_1,c_2,\dots,c_{\Delta}$, and let the $\Delta$ neighbors of v be $v_1,v_1,\dots,v_{\Delta}$. We may assume these neighbors of v have pairwise distinct colors; otherwise the claim already follows.
    
    Next, let $H_{i,j}$ be the subgraph formed by all vertices of H colored $c_i$ or $c_j$ and all edges between them. We may assume any two distinct vertices $v_i$, $v_j$ lie in the same connected component of $H_{i,j}$. Otherwise, if they were in two different components, we could swap the colors of all vertices in one of the components, making $v_i$ and $v_j$ the same color.
    
    > Swapping colors here means: if the graph uses only two colors a and b, recolor every vertex that was a to b, and every vertex that was b to a.
    
    Call this component $C_{i,j}$. Then $C_{i,j}$ must be just a path from $v_i$ to $v_j$. Since $v_i$ has degree $\Delta-1$ in H, its neighbors in H must have pairwise distinct colors; otherwise $v_i$ could be recolored to some other color, matching another neighbor of v. So $v_i$ has exactly 1 neighbor in $C_{i,j}$, and the same holds for $v_j$. Now take a path P from $v_i$ to $v_j$ in $C_{i,j}$. If $C_{i,j}\ne P$, walk along P coloring its vertices in order, and let u be the first vertex of degree greater than 2 that we meet. The neighbors of u use at most $\Delta-2$ colors, so u can be recolored, which disconnects $v_i$ from $v_j$.
    
    Then it is easy to see that for any 3 distinct vertices $v_i$, $v_j$, $v_k$, $V(C_{i,j})\cap V(C_{j,k})=\{v_j\}$.
    
    This completes the strengthening of the claim.
    
    The rest is simple. First, if the neighbors of v are pairwise adjacent, the claim follows. Otherwise, suppose $v_1$ and $v_2$ are not adjacent. Take the neighbor w of $v_1$ in $C_{1,2}$ and swap the colors in $C_{1,3}$. In the new graph, $w\in V(C_{1,2})\cap V(C_{2,3})$, a contradiction.
    
    This completes the proof.

### Welsh–Powell algorithm

The Welsh–Powell algorithm is a greedy algorithm that finds a coloring when **the number of colors is not limited**.

For an undirected graph G without self-loops, let $V(G):=\{v_1,v_2,\dots,v_n\}$ be ordered so that

$\deg(v_i)\geq\deg(v_{i+1}),~\forall 1\leq i\leq n-1$

The coloring produced by Welsh–Powell uses at most $\max_{i=1}^n\min\{\deg(v_i)+1,i\}$ colors, and the time complexity is $O\left(n\max_{i=1}^n\min\{\deg(v_i)+1,i\}\right)=O(n^2)$.

#### Process

1.  Sort the uncolored vertices by degree in descending order.
2.  Give the first vertex a color that has not been used yet.
3.  Go through the remaining vertices in order. If the current vertex is **not adjacent** to any vertex that has the **same** color as the first vertex, give it the first vertex's color.
4.  If uncolored vertices remain, go back to step 1; otherwise stop.

Here is an example:

![Original](images/color1.png)

(Made with [Graph Editor](https://csacademy.com/app/graph_editor/).)

First sort the vertices by degree in descending order:

| Order                      | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9  | 10 | 11 | 12 | 13 |
| ----------------------- | - | - | - | - | - | - | - | - | -- | -- | -- | -- | -- |
| Vertex                    | 4 | 5 | 0 | 2 | 9 | 1 | 3 | 6 | 10 | 12 | 7  | 8  | 11 |
| Degree                      | 5 | 5 | 4 | 4 | 4 | 3 | 3 | 3 | 3  | 3  | 2  | 2  | 1  |
| $\min\{\deg(v_i)+1,i\}$ | 1 | 2 | 3 | 4 | 5 | 4 | 4 | 4 | 4  | 4  | 3  | 3  | 2  |

So Welsh–Powell uses at most 5 colors on this graph.

Also, since the graph contains $C_3$ as a subgraph, its chromatic number is at least 3.

-   First round:

    ![Colored 1](images/color2.png)

    Color vertices `4 9 3 11`.
-   Second round:

    ![Colored 2](images/color3.png)

    Color vertices `5 2 6 7 8`.
-   Third round:

    ![Colored 3](images/color4.png)

    Color vertices `0 1 10 12`.

#### Proof

???+ note "Proof"
    For an undirected graph G without self-loops, let $V(G):=\{v_1,v_2,\dots,v_n\}$ be ordered so that
    
    $\deg(v_i)\geq\deg(v_{i+1}),~\forall 1\leq i\leq n-1$
    
    Let $V_0=\varnothing$. We take a subset $V_m$ of $V(G)\setminus\bigcup_{i=0}^{m-1} V_i$ whose elements satisfy
    
    1.  $v_{k_m}\in V_m$, where $k_m=\min\{k:v_k\notin\bigcup_{i=0}^{m-1} V_i\}$
    2.  If
    
        $\{v_{i_{m,1}},v_{i_{m,2}},\dots,v_{i_{m,l_m}}\}\subset V_m,~i_{m,1}<i_{m,2}<\dots<i_{m,l_m}$
    
        then $v_j\in V_m$ if and only if
    
        1.  $j>i_{m,l_m}$
        2.  $v_j$ is adjacent to none of $v_{i_{m,1}},v_{i_{m,2}},\dots,v_{i_{m,l_m}}$
    
    Clearly, if we give the vertices in $V_i$ the i-th color, we get exactly the coloring produced by Welsh–Powell. Clearly
    
    -   $V_1\neq\varnothing$
    -   $V_i\cap V_j=\varnothing\iff i\neq j$
    -   $\exists \alpha(G)\in\Bbb{N}^*,\forall i>\alpha(G),~s.t.~ V_i=\varnothing$
    
    We only need to prove:
    
    $\bigcup_{i=1}^{\alpha(G)} V_i=V(G)$
    
    where
    
    $\chi(G)\leq\alpha(G)\leq\max_{i=1}^n\min\{\deg(v_i)+1,i\}$
    
    The left inequality clearly holds, so consider the right one.
    
    First, it is easy to see:
    
    If $v\notin\bigcup_{i=1}^mV_i$, then v is adjacent to at least one vertex in each of $V_1,V_2,\dots,V_m$, so $\deg(v)\geq m$
    
    Therefore
    
    $v_j\in\bigcup_{i=1}^{\deg(v_j)+1}V_i$
    
    On the other hand, from how the sequence $\{V_i\}$ is built, it is easy to see that
    
    $v_j\in\bigcup_{i=1}^j V_i$
    
    Combining the two gives the result.

## Edge coloring

We color the edges of an undirected graph so that adjacent edges get different colors. If G is k-edge-colorable but not $(k-1)$-edge-colorable, then k is called the edge chromatic number (chromatic index) of G, written $\chi'(G)$.

### Vizing's theorem

If G is a simple graph, then $\Delta(G) \leq \chi'(G) \leq \Delta(G) + 1$

If G is bipartite, then $\chi'(G)=\Delta(G)$

When $n$ is odd ($n \neq 1$), $\chi'(K_n)=n$; when $n$ is even, $\chi'(K_n)=n-1$

### Constructive proof of Vizing's theorem for bipartite graphs

???+ note "Proof"
    Add the edges to the bipartite graph one by one.
    
    When we try to add edge $(x,y)$, we find the smallest-numbered color not yet used at $x$ and at $y$; call them $l_x$ and $l_y$.
    
    If $l_x=l_y$, we can simply give this edge color $l_x$.
    
    Otherwise, assume $l_x<l_y$. We try to change the color of the edge of color $l_x$ leaving $y$ to $l_y$.
    
    This change can be roughly seen as a finite, unique augmenting path starting from $y$ and passing through edges of colors $l_x,l_y,\cdots$ in turn.
    
    Since the augmenting path is finite, we can flip the colors of all edges on it: edges of color $l_x$ become $l_y$, and edges of color $l_y$ become $l_x$.
    
    By the properties of bipartite graphs, $x$ cannot be on the augmenting path, otherwise it would contradict $l_x$ being the smallest unused color at $x$.
    
    So after augmenting, we can directly give the edge between $x$ and $y$ color $l_x$.
    
    The total construction takes $O(nm)$ time.

???+ note "Example code [UVa10615 Rooks](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=18&page=show_problem&problem=1556)"
    ```cpp
    --8<-- "docs/graph/code/color/color_1.cpp"
    ```

??? note "A far-from-easy example problem [UOJ 444 Bipartite Graph](https://uoj.ac/problem/444)"
    This problem was set by the author in 2018 as a first-round homework problem for the national training team.
    
    First, note that a lower bound on the answer is the number of vertices whose degree is not a multiple of k.
    
    The lower bound is achieved by splitting the vertices of the bipartite graph.
    
    If $degree \bmod k \neq 0$, split the vertex into $degree/k$ vertices of degree k and one vertex of degree $degree \bmod k$.
    
    If $degree \bmod k = 0$, split the vertex into $degree/k$ vertices of degree k.
    
    The split vertices mean the same thing in the original graph; that is, as long as the degree limits are respected, an endpoint of an edge may attach to any of the split vertices.
    
    By Vizing's theorem, we can clearly construct a k-coloring of this graph.
    
    The edge deletion part has little to do with Vizing's theorem, so we skip it here.
    
    Interested readers can read the editorial the author wrote at the time.

## Chromatic polynomial

$P(G,k)$ is the number of different k-colorings of G.

$P(K_n, k) = k(k-1)\cdots(k-n+1)$

$P(N_n, k) = k^n$

In an undirected acyclic graph G,

1.  if $e=(v_i, v_j) \notin E(G)$, then $P(G, k) = P(G \cup e, k)+P(G\setminus e, k)$
2.  if $e=(v_i, v_j) \in E(G)$, then $P(G,k)=P(G-e,k)-P(G\setminus e,k)$

Theorem: let $V_1$ be a vertex cut of G such that $G[V_1]$ is a complete subgraph of G of order $|V_1|$, and let $G-V_1$ have $p(p \geq 2)$ connected components. Then:

$P(G,k)=\frac{\Pi_{i=1}^{p}{(P(H_i, k))}}{P(G[V_1], k)^{p-1}}$

where $H_i=G[V_1 \cup V(G_i)]$

## References

1.  [Graph coloring - Wikipedia](https://en.wikipedia.org/wiki/Graph_coloring)
2.  Welsh, D. J. A.; Powell, M. B. (1967), "[An upper bound for the chromatic number of a graph and its application to timetabling problems](https://doi.org/10.1093%2Fcomjnl%2F10.1.85)", The Computer Journal, 10 (1): 85–86
