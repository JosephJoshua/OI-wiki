author: accelsao, thallium, Chrogeek, Enter-tainer, ksyx, StudyingFather, H-J-Granger, Henry-ZHR, countercurrent-time, william-song-shy, 5ab-juruo, XiaoQuQuSD, hhc0001, GCVillager

Prerequisites: [bipartite graphs](../bi-graph.md), [graph matching](./graph-match.md)

## Introduction

This page discusses the maximum matching problem in a bipartite graph $G=(X,Y,E)$.

A typical real-life example of bipartite matching is pairing up boys and girls. Suppose there are some boys ($X$) and some girls ($Y$). Each person can be paired at most once, and the allowed pairs are given by a list ($E$). The task of a bipartite maximum matching algorithm is to find as many pairs as possible under these constraints, so that as many people as possible get paired.

???+ info "Tip"
    This page assumes that a partition (coloring) of the vertex set $V$ of the bipartite graph is already known: $V=X\cup Y$. If you do not know the partition of $V$ in advance, you can find one in $O(|V|+|E|)$ time with the [bipartite coloring algorithm](../bi-graph.md#testing).

## Kuhn's algorithm

Kuhn's algorithm is a direct application of [Berge's lemma](./graph-match.md#berges-lemma). It is also a part of the [Hungarian algorithm](./bigraph-weight-match.md#hungarian-algorithm-kuhnmunkres-algorithm).

### How it works

To find a maximum matching, the algorithm goes through all vertices one by one, tries to find an augmenting path starting from each, and augments along it. An augmenting path always has odd length, so in a bipartite graph its two endpoints lie on different sides. This means we only need to consider augmenting paths that start from the left side.

To find augmenting paths, we can orient the bipartite graph based on the current matching $M$. On an augmenting path (or any alternating path) starting from an unmatched left vertex, we can only go from a left vertex to a right vertex along an unmatched edge, and from a right vertex back to a left vertex along a matched edge. So we can make every unmatched edge point toward its right vertex, and every matched edge point toward its left vertex. Finding an augmenting path then becomes finding a simple path in this directed graph from some unmatched left vertex to some unmatched right vertex. This is easy to do in $O(|E|)$ time with [DFS](../dfs.md) or [BFS](../bfs.md).

![](images/bigraph-match-1.svg)

(In the figure, dark vertices are matched and light vertices are unmatched. Red edges are matched edges and black edges are unmatched edges. Arrows show the orientation given by the current matching. From the figure, the path $1\rightarrow 8\rightarrow 3\rightarrow 11\rightarrow 6\rightarrow 12$ is an augmenting path with respect to the current matching.)

At the start, all edges point toward the right side. Each time an augmenting path is found, we reverse every edge along it, to show that their matched status has flipped. When the algorithm ends, the edges pointing toward the left side are exactly the matched edges.

We only need to try each of $O(|V|)$ left vertices [once](./graph-match.md#berges-lemma), so the total time complexity of the algorithm is $O(|V||E|)$.

### Optimization

A few simple tricks can reduce the constant factor of Kuhn's algorithm:

1.  Kuhn's algorithm is based on Berge's lemma, which does not require the two sides of the bipartite graph to be known in advance. So Kuhn's algorithm runs correctly even if the two sides are not explicitly separated, as long as the graph is bipartite. However, it is usually faster to first color the bipartite graph and fix its left and right sides.
2.  The time complexity of Kuhn's algorithm as described above is actually $O(|X||E|)$, so you can pick the smaller of the two sides as the left side $X$.
3.  When searching for augmenting paths, the visited marks used to avoid repeated searching do not need to be cleared before every DFS. Before clearing the marks, you can try to find augmenting paths for all unmatched left vertices. In one such round, each edge is visited at most once, so the cost is still $O(|E|)$. But one round may find several augmenting paths, so the total number of rounds $k$ is at most $|M|+1$, where $M$ is the maximum matching. Accordingly, the overall complexity drops to $O(k|E|)$.
4.  When searching for an augmenting path, try unmatched right vertices first, since that gives a shorter augmenting path.
5.  Berge's lemma does not require the initial matching to be empty. So at the start of Kuhn's algorithm, you can randomly pick some pairwise disjoint edges as the initial matching, which reduces the number of later searches. If optimization 3 is already applied, you can skip this one.

The worst-case complexity is still $O(|V||E|)$, but a well-optimized Kuhn's algorithm is quite fast. Still, to keep specific test data from forcing the worst case, you should randomly shuffle the order of the edges or vertices before matching.

### Reference implementation

In the implementation, you do not need to actually maintain the orientation. It is enough to store, for each vertex, the vertex it is matched to.

??? example "Template problem [Library Checker - Matching on Bipartite Graph](https://judge.yosupo.jp/problem/bipartitematching)"
    ```cpp
    --8<-- "docs/graph/code/graph-matching/bigraph-match/bigraph-match_1.cpp"
    ```

## The Hopcroft–Karp algorithm

The Hopcroft–Karp algorithm further optimizes how Kuhn's algorithm searches for augmenting paths. It cuts the total number of rounds to $O(|V|^{1/2})$, which gives a time complexity of $O(|V|^{1/2}|E|)$. This algorithm is actually a special case of [Dinic's algorithm](../flow/max-flow.md#dinics-algorithm).

### How it works

The algorithm still searches for augmenting paths, but to finish the matching in fewer rounds, it uses the following strategy in every round:

1.  Orient matched edges toward their left vertices and unmatched edges toward their right vertices.
2.  Starting from all unmatched left vertices, run a BFS on the directed graph and record the level $d(v)$ of each visited vertex, until some level contains an unmatched right vertex. If the BFS ends without finding an unmatched right vertex, the current matching is already maximum.
3.  Run a DFS from each unmatched left vertex in turn to find augmenting paths and augment along them. The DFS only moves forward along edges whose levels increase by exactly one (that is, $d(v') = d(v) + 1$), and only visits vertices not yet visited by a DFS in this round. In particular, the DFS never visits a vertex that the BFS in the previous step did not reach.

In network flow terms, step 2 builds a level graph and step 3 finds a blocking flow in the level graph. In a level graph, every edge goes from one level to the next. A blocking flow, in this context, is a maximal set of augmenting paths that pairwise share no vertices. The set of augmenting paths found in step 3 must be maximal: if not, there would be another augmenting path, and it should already have been found when its starting vertex was processed.

Compared with Kuhn's algorithm, the key change in Hopcroft–Karp is the extra step of building the level graph before finding the blocking flow. Running DFS on the level graph forces the algorithm to always reach each vertex along a shortest path. The benefit is that the lengths of the augmenting paths found strictly increase from round to round. Moreover, one can prove that until the maximum matching is found, the length of augmenting paths increases at most $3|M|^{1/2}$ times, where $|M|$ is the size of the maximum matching. So the total number of augmentation rounds is $O(|M|^{1/2})$, which gives a time complexity of $O(|M|^{1/2}|E|)$. Since $2|M|\le |V|$, the time complexity can also be written with the looser upper bound $O(|V|^{1/2}|E|)$.

??? note "Proof"
    First, we show that the lengths of the augmenting paths found strictly increase from round to round.
    
    Suppose the BFS in the current round extends $\ell$ levels. Since the unmatched right vertices found by the BFS all lie on the same level, every augmenting path the DFS finds in this round has length $\ell$. We need to show that after augmenting along this set of paths $\{P_i\}$, the re-oriented directed graph no longer has any augmenting path of length at most $\ell$.
    
    In fact, if $P$ is a shortest augmenting path with respect to $M$ and $P'$ is an augmenting path with respect to $M\oplus P$, then $|P'|\ge |P| + 2|P\cap P'|$ always holds. This is because $N=(M\oplus P)\oplus P'$ is obtained from $M$ by augmenting twice, so, as in the [proof of Berge's lemma](./graph-match.md#berges-lemma), the symmetric difference $M\oplus N=P\oplus P'$ contains at least two disjoint augmenting paths $P_1$ and $P_2$ with respect to $M$. Since $P$ is shortest, we have
    
    $$
    2|P|\le |P_1|+|P_2|\le |P\oplus P'| = |P| + |P'| - 2|P\cap P'|.
    $$
    
    This shows $|P'|\ge |P| + 2|P\cap P'|$. So if, after augmenting along $\{P_i\}$, a new augmenting path $P'$ is still as long as them, it must be disjoint from all of them, which contradicts the maximality of $\{P_i\}$. This contradiction shows that after augmenting along a blocking flow, new augmenting paths are strictly longer.
    
    Finally, we show that the length of augmenting paths increases at most $3|M|^{1/2}$ times.
    
    Let $p=\lfloor|M|^{1/2}\rfloor$. After the first $p$ rounds, the remaining augmenting paths have length at least $|M|^{1/2}$. Let the current matching be $M_p$. Then, as before, one can show that the graph $(V,M\oplus M_p)$ contains $|M|-|M_p|$ augmenting paths with respect to $M_p$ that pairwise share no vertices. Each augmenting path uses at least $|M|^{1/2}/2$ matched edges of $M$, so there are at most $2|M|^{1/2}$ such paths, that is, $|M|-|M_p|\le 2|M|^{1/2}$. This means that starting from $M_p$, we can augment at most $2|M|^{1/2}$ more times, so the algorithm runs at most $2|M|^{1/2}$ more rounds. Therefore the length of augmenting paths increases at most $3|M|^{1/2}$ times in total.

This is only a worst-case estimate for the Hopcroft–Karp algorithm. In fact, on random graphs, the time complexity of Hopcroft–Karp is $O(|E|\log |V|)$ with high probability[^hk-comp-ref].

### Optimization

When building the level graph, Hopcroft–Karp, like the usual Dinic's algorithm, stops as soon as it reaches an unmatched right vertex. But for bipartite matching alone, this is not necessary. Also, because the BFS stops early, it limits the range of the following DFS, so each round finds only a limited number of augmenting paths, which slows down the whole matching. On some graphs it is even slower than an optimized Kuhn's algorithm. So a simple improvement is to not stop the BFS early, and instead build the level graph over all reachable vertices.

??? note "Proof of correctness"
    In the optimized algorithm, the augmenting paths in a blocking flow no longer all have the same length, so the complexity proof above no longer applies. However, by building an auxiliary graph for each round of the algorithm, we can still show that the length of the shortest augmenting path strictly increases, so the worst-case complexity still holds.
    
    Let the bipartite graph be $G=(X,Y,E)$ and the current matching be $M$. Let $W\subseteq Y$ be the set of unmatched right vertices reachable by the BFS, and let $d(y)$ be the length of the shortest augmenting path reaching $y\in W$. Let $d_\text{max} = \max_{y\in W}d(y)$. Then for each $y\in W$, add a new chain of length $d_\text{max} - d(y)$ starting at $y$, label the new vertices alternately as left and right vertices, and label the new edges alternately as matched and unmatched. Call the resulting graph $G'=(X',Y',E')$ with matching $M'$; its shortest augmenting path has length $d_\text{max}$. Then there is a bijection between the augmenting paths with respect to $M$ that can be found along the level graph in $G$ (that is, the shortest augmenting paths reaching the corresponding vertices) and the globally shortest augmenting paths with respect to $M'$ in $G'$. So finding a blocking flow in the level graph of $G$ and augmenting is equivalent to finding a blocking flow in the level graph of $G'$ and augmenting. By the proof above, after augmenting, $G'$ has no augmenting path of length $d_\text{max}$. So $G$ has no augmenting path of length $d_\text{min}=\min_{y\in W} d(y)$ either: such a path, extended by the new alternating chain, would correspond to an augmenting path of length $d_\text{max}$ in $G'$. This again shows that the length of the shortest augmenting path strictly increases between rounds. So the overall complexity is still $O(|M|^{1/2}|E|)$.

### Reference implementation

??? example "Template problem [Library Checker - Matching on Bipartite Graph](https://judge.yosupo.jp/problem/bipartitematching)"
    ```cpp
    --8<-- "docs/graph/code/graph-matching/bigraph-match/bigraph-match_2.cpp"
    ```

## Reduction to maximum flow

The bipartite maximum matching problem can be reduced to the maximum flow problem.

![](images/bigraph-match-2.svg)

As shown in the figure, add two vertices as the source and the sink. Add an edge from the source to each left vertex, an edge from each right vertex to the sink, and for each undirected edge of the bipartite graph, an edge from its left vertex to its right vertex. All edges have capacity $1$. Every integer flow in this directed graph corresponds one-to-one to a matching in the bipartite graph, and the value of the flow is the size of the matching. So finding a maximum bipartite matching is the same as finding a maximum flow in this directed graph.

Any algorithm that solves maximum flow can be used to solve bipartite maximum matching. It is easy to see that Kuhn's algorithm and Hopcroft–Karp are special cases of the corresponding maximum flow algorithms. Likewise, the [push-relabel algorithm](../flow/max-flow.md#push-relabel-preflow-push-algorithms) and others can also be used for bipartite maximum matching. Note, however, that any maximum flow algorithm needs to be specifically optimized when applied to bipartite matching, to avoid a large constant factor.

### Linear programming formulation

Like other maximum flow problems, the maximum matching problem in a bipartite graph $G=(X,Y,E)$ (with $V=X\cup Y$) can be written as a linear program. Let $x_e\in\{0,1\}$ indicate whether edge $e$ is in the matching. Then we get the following linear program:

$$
\begin{aligned}
\max_{\{x_e\}}\;& \sum_{e\in E}x_e \\
\text{subject to } & \sum_{e\sim v} x_{e} \le 1,~\forall v\in V,\\
& x_e\ge 0,~\forall e\in E.
\end{aligned}
$$

Here $e\sim v$ denotes incidence, that is, vertex $v$ is one of the endpoints of edge $e$. Besides non-negativity, the constraints require that each vertex $v\in V$ is incident to at most one chosen edge, which is exactly the definition of a matching. So every matching corresponds to some integer point in the feasible region of this linear program.

The converse does not hold. In a feasible solution, $x_e$ may be fractional, which does not represent any actual matching. Even so, for a bipartite graph $G$, every extreme point solution of the linear program above is an integer point. This means the optimal value of the objective can always be reached at an integer point, so non-integer cases need not be considered. This property does not hold for general graphs, so in general graphs this linear program is not equivalent to the maximum matching problem.

The dual of this linear program can be written as follows:

$$
\begin{aligned}
\min_{\{y_v\}}\;& \sum_{v\in V}y_v \\
\text{subject to } & y_u+y_v \ge 1,~\forall (u,v)\in E,\\
& y_v\ge 0,~\forall v\in V.
\end{aligned}
$$

As we will see shortly, this is exactly the minimum vertex cover problem on bipartite graphs.

## Dulmage–Mendelsohn decomposition

Using a maximum matching of a bipartite graph, we can split the vertices into several disjoint subsets that fully describe how all maximum matchings of the graph are distributed and structured. This is the Dulmage–Mendelsohn decomposition. In competitive programming, this decomposition can identify the critical vertices and critical edges of maximum matchings, which helps decide whether the maximum matching is unique or solve games on bipartite graphs.

### Construction

Let $M$ be a maximum matching of the bipartite graph $G=(X,Y,E)$.

![](images/bigraph-match-4.svg)

As shown in the figure, we define the following three subsets of all vertices $V=X\cup Y$:

-   Even-reachable vertices $\mathcal E$: the set of vertices that can be reached from some unmatched vertex along an alternating path of even length;
-   Odd-reachable vertices $\mathcal O$: the set of vertices that can be reached from some unmatched vertex along an alternating path of odd length;
-   Unreachable vertices $\mathcal U$: the set of vertices that cannot be reached from any unmatched vertex along an alternating path.

One can prove that these three vertex sets $\mathcal E,\mathcal O,\mathcal U$ have the following properties:

???+ note "Properties"
    1.  The sets $\mathcal E,\mathcal O,\mathcal U$ form a partition of the vertex set, and this partition does not depend on which maximum matching $M$ is chosen.
    2.  Every maximum matching of $G$ contains a perfect matching among the vertices of $\mathcal U$, and matches each vertex of $\mathcal O$ to a vertex of $\mathcal E$. In other words, the size of a maximum matching of $G$ is $|\mathcal O|+|\mathcal U|/2$.
    3.  $G$ has no edge between a vertex of $\mathcal E$ and a vertex of $\mathcal E\cup\mathcal U$.

??? note "Proof"
    1.  By definition, $\mathcal U$ is disjoint from $\mathcal E\cup\mathcal O$. We only need to show that $\mathcal E$ and $\mathcal O$ are disjoint. Suppose not. For a vertex $v\in\mathcal E\cap\mathcal O$, there is an even-length alternating path from an unmatched vertex $a$ to $v$, and an odd-length alternating path from an unmatched vertex $b$ to $v$. Since $G$ is bipartite, $a\neq b$, and the two paths reach $v$ through a matched edge and an unmatched edge, respectively. So joining the two paths gives an alternating path from $a$ through $v$ to $b$. This is an augmenting path, which contradicts $M$ being a maximum matching. So $\mathcal E\cap\mathcal O=\varnothing$.
    
        Let $M'$ be a maximum matching different from $M$. Repeating the [proof of Berge's lemma](./graph-match.md#berges-lemma) shows that $M'\oplus M$ consists only of even-length paths and even cycles. Starting from the maximum matching $M$, we can flip the edges of these components (paths and cycles) one by one (swapping matched and unmatched edges) to get the maximum matching $M'$. When flipping an even cycle, unmatched vertices stay unmatched, and the parity of the lengths of alternating paths from them does not change. When flipping an even-length path, the matched status of its two endpoints swaps, but the parity of the path length from either of them to any vertex on the path is the same. So the sets $\mathcal E,\mathcal O,\mathcal U$ never change during the flipping. This shows the decomposition does not depend on the choice of the maximum matching $M$.
    2.  If a matched edge appears on some alternating path starting from an unmatched vertex $v$, then its two endpoints have distances to $v$ of different parity, so one is in $\mathcal E$ and the other in $\mathcal O$. Otherwise, both endpoints must be in $\mathcal U$. This shows that matched edges of a maximum matching are always $\mathcal E\mathcal O$ edges or $\mathcal U\mathcal U$ edges. On the other hand, an unmatched vertex can be reached by the zero-length alternating path starting from itself, so it only appears in $\mathcal E$. This shows that all vertices in $\mathcal O$ and $\mathcal U$ are matched. Simple counting shows that the size of a maximum matching is $|\mathcal O|+|\mathcal U|/2$.
    3.  By definition, any vertex $a$ in $\mathcal E$ can be reached from an unmatched vertex $v$ along an even-length alternating path. That is, a vertex of $\mathcal E$ is either unmatched, or the alternating path $P$ reaching it ends with a matched edge. If $G$ has an edge between $a$ and some vertex $b$ in $\mathcal E\cup\mathcal U$, then by the discussion above this edge must be unmatched, and we can extend the alternating path $P$ along it. This shows that $b$ also belongs to $\mathcal O$, which contradicts the first property. So $G$ has no edge between a vertex of $\mathcal E$ and a vertex of $\mathcal E\cup\mathcal U$.

The resulting decomposition of the vertex set $V=\mathcal E\cup\mathcal O\cup\mathcal U$ is called the **Dulmage–Mendelsohn decomposition**. After finding a maximum matching with the algorithms above, you can compute the Dulmage–Mendelsohn decomposition with a BFS in $O(|V|+|E|)$ time.

### Critical vertices of maximum matchings

If a vertex $v$ is matched in every maximum matching of the bipartite graph $G$, it is called a critical vertex of the maximum matching. The following result says: a vertex is critical if and only if, in some maximum matching, there is no even-length alternating path from an unmatched vertex to it.

???+ note "Theorem"
    Let the Dulmage–Mendelsohn decomposition of the bipartite graph $G=(X,Y,E)$ be $V=\mathcal E\cup\mathcal O\cup\mathcal U$. Then a vertex $v\in V$ is critical if and only if $v\in\mathcal O\cup \mathcal U$.

??? note "Proof"
    By the properties of the Dulmage–Mendelsohn decomposition, in every maximum matching of $G$, the vertices of $\mathcal O$ and $\mathcal U$ are all matched. So the vertices of $\mathcal O\cup \mathcal U$ are critical. Next, we show that $\mathcal E$ contains no critical vertex. Suppose that a vertex $a\in\mathcal E$ is critical. Then in a maximum matching $M$ there is an even-length alternating path $P$ connecting $a$ and some unmatched vertex $b\in\mathcal E$. Flipping all edges on this path gives the maximum matching $M\oplus P$, in which $a$ becomes unmatched. So $\mathcal E$ has no critical vertices.

So to find the critical vertices of maximum matchings, you only need to compute the Dulmage–Mendelsohn decomposition.

### Critical edges of maximum matchings

Similarly, if an edge $e$ is matched in every maximum matching of the bipartite graph $G$, it is called a critical edge of the maximum matching. The maximum matching of a bipartite graph is unique if and only if, in one of its maximum matchings, every matched edge is critical.

???+ note "Theorem"
    Let the Dulmage–Mendelsohn decomposition of the bipartite graph $G=(X,Y,E)$ be $V=\mathcal E\cup\mathcal O\cup\mathcal U$, and let $M$ be one of its maximum matchings. Then an edge $e\in E$ is critical if and only if both endpoints of $e$ are in $\mathcal U$, $e$ is a matched edge of $M$, and there is no alternating cycle with respect to $M$ that contains $e$.

??? note "Proof"
    The endpoints of a critical edge must be critical vertices. By the properties of the Dulmage–Mendelsohn decomposition, edges of a maximum matching can only be $\mathcal E\mathcal O$ edges or $\mathcal U\mathcal U$ edges. But $\mathcal E$ has no critical vertices, so a critical edge can only be a $\mathcal U\mathcal U$ edge. Of course, a critical edge must also be a matched edge of $M$. Let $e\in M$ be a $\mathcal U\mathcal U$ edge. It is not critical if and only if there is another maximum matching $M'\neq M$ with $e\in M\oplus M'$. Repeating the [proof of Berge's lemma](./graph-match.md#berges-lemma) shows that $M'\oplus M$ consists only of even-length paths and even cycles. One endpoint of each such path is unmatched with respect to $M$, so no vertex on the path is in $\mathcal U$, which contradicts the choice of $e$. So $e$ can only appear in an even cycle. Therefore a $\mathcal U\mathcal U$ edge $e\in M$ is not critical if and only if there is an alternating cycle with respect to $M$ that contains $e$. This is what we wanted to prove.

So to find the critical edges of maximum matchings, follow these steps:

1.  Find a maximum matching $M$ of $G$;
2.  Orient the edges of $G$ according to $M$ to get the directed graph $G_M$;
3.  Run a BFS to find the set $\mathcal U$ of the Dulmage–Mendelsohn decomposition, that is, the set of vertices that cannot be reached from unmatched vertices along alternating paths;
4.  Use [Tarjan's algorithm](../scc.md#tarjans-algorithm) to find all strongly connected components of the directed graph $G_M$;
5.  Go through the edges of the matching $M$. If both endpoints of an edge are in $\mathcal U$ but not in the same strongly connected component, it is a critical edge.

After the maximum matching is found, the remaining steps take $O(|V|+|E|)$ time.

## Related problems

Algorithms for bipartite maximum matching can also solve other combinatorial optimization problems.

### Minimum vertex cover in bipartite graphs

The minimum vertex cover problem asks you to choose as few vertices as possible in an undirected graph so that every edge has at least one chosen endpoint.

Minimum vertex cover in general graphs is NP-hard, but for bipartite graphs, Kőnig's theorem shows that it reduces to maximum matching and can be solved efficiently. The proof of the theorem also gives a construction of the minimum vertex cover.

???+ note "Kőnig's theorem"
    In a bipartite graph, the number of vertices in a minimum vertex cover equals the number of edges in a maximum matching.

??? note "Proof"
    Let $M$ be a maximum matching of the bipartite graph $G=(X,Y,E)$. Let $U$ be the set of unmatched left vertices, and let $Z$ be the set of vertices of $G$ that can be reached from a vertex of $U$ along some alternating path. Then the vertex set $C=(X\setminus Z)\cup(Y\cap Z)$ is the minimum vertex cover we want.
    
    ![](images/bigraph-match-3.svg)
    
    First, $C$ is a vertex cover. Suppose not; then there is an edge $(u,v)\in E$ with $u\in X\cap Z$ and $v\in Y\setminus Z$. Let $P_u$ be an alternating path reaching $u$. If $(u,v)$ is a matched edge, then the last edge of $P_u$ is $(v,u)$, which contradicts $v\notin Z$. If $(u,v)$ is not matched, we can extend $P_u$ along $(u,v)$ to get an alternating path reaching $v$, which also contradicts $v\notin Z$. These contradictions show that every edge has at least one endpoint in $C$, so $C$ is a vertex cover.
    
    Next, we show that $C$ is a minimum vertex cover. To cover all edges of the maximum matching $M$, any vertex cover needs at least $|M|$ vertices. So it suffices to prove $|C|=|M|$. This is the same as proving that $C$ contains nothing besides one endpoint of each matched edge, that is, $C$ contains no unmatched vertex. Suppose not; then there is an unmatched vertex $v\in C$. If $v\in X$, then $v\in U\subseteq Z$, which contradicts the construction of $C$. If $v\in Y$, then an alternating path reaching $v$ is an augmenting path with respect to $M$, which by Berge's lemma contradicts $M$ being a maximum matching. These contradictions show that there is no such unmatched vertex, so $C$ is a minimum vertex cover.

From the network flow point of view, minimum vertex cover is a minimum cut problem: choosing a left vertex means cutting its edge from the source, and choosing a right vertex means cutting its edge to the sink. From the linear programming point of view, minimum vertex cover is the dual of maximum matching. So Kőnig's theorem can be seen as a special case of the [max-flow min-cut theorem](../flow/max-flow.md#max-flow-min-cut-theorem), or more generally, a special case of the strong duality theorem of linear programming.

### Maximum independent set in bipartite graphs

The maximum independent set problem asks you to choose as many vertices as possible in an undirected graph so that no two of them are adjacent.

For general graphs, the following theorem holds:

???+ note "Theorem"
    In a graph $G=(V,E)$, a vertex set $C\subseteq V$ is a vertex cover if and only if its complement $V\setminus C$ is an independent set.

??? note "Proof"
    $C$ is a vertex cover if and only if every edge $e$ in $E$ has at least one endpoint in $C$, if and only if no edge in $E$ has both endpoints in $V\setminus C$, if and only if $V\setminus C$ is an independent set.

???+ note "Corollary"
    In a graph $G=(V,E)$, the size of a minimum vertex cover plus the size of a maximum independent set equals the number of vertices.

So, like minimum vertex cover, maximum independent set is NP-hard for general graphs, but for bipartite graphs it reduces to maximum matching and can be solved efficiently.

### Minimum path cover in DAGs

The minimum path cover problem asks you to choose as few simple paths as possible in a directed graph so that every vertex appears in exactly one path.

Minimum path cover in general directed graphs is NP-hard, but for directed acyclic graphs it reduces to bipartite maximum matching. For a DAG $G=(V,E)$, build the bipartite graph $G'=(V^\text{in},V^\text{out},E')$ as follows:

-   For each vertex $v\in V$, create an in-vertex $v^\text{in}$ and an out-vertex $v^\text{out}$. Let $V^\text{in}$ and $V^\text{out}$ be the sets of all in-vertices and out-vertices. They become the left and right sides of the new graph.
-   For each directed edge $(u,v)\in E$, add the undirected edge $(u^\text{out},v^\text{in})$. The set of all these undirected edges is $E'$.

This gives the following result:

???+ note "Theorem"
    The size of a minimum path cover of a DAG $G=(V,E)$ plus the size of a maximum matching of the corresponding bipartite graph $G'=(V^\text{in},V^\text{out},E')$ equals the number of vertices.

??? note "Proof"
    Each matching $M'$ of the bipartite graph $G'$ corresponds to a subgraph $F$ of $G$ in which every vertex has in-degree and out-degree at most one. That is, $F$ is actually a set of pairwise disjoint paths or cycles in the directed graph $G$. But we assumed $G$ has no cycles, so $F$ consists only of disjoint paths. Conversely, every such subgraph $F$ gives a corresponding matching. Since the size of $M'$ is the number of vertices minus the number of paths in $F$, the minimum path cover problem on $G$ corresponds to the maximum matching problem on $G'$.

The proof is constructive, so it is easy to build the corresponding minimum path cover from the maximum matching found. Also, this construction shows why the reduction fails for general directed graphs: a matching in the bipartite graph may correspond to a cycle in the directed graph.

In particular, for a set $X$ with a partial order $P$ on it, we can build the DAG $G=(X,P)$. Then by [Dilworth's theorem](../../math/order-theory.md#dilworths-theorem-and-mirskys-theorem), the size of a minimum path cover of $G$ equals the size of its largest antichain, which is the width of the poset $(X,P)$. So this section actually gives an efficient way to compute the width of any poset.

## Example problems

The hard part of applying bipartite matching is building the graph. This section shows graph-building techniques through some example problems.

???+ example "[Luogu P1129 Matrix Game](https://www.luogu.com.cn/problem/P1129)"
    You are given a 0/1 square matrix. Each move swaps two rows or two columns. Can you make the main diagonal (top-left to bottom-right) all 1s?

??? note "Solution"
    Note that if there are $n$ ones such that no two are in the same row or column, then there is a solution; otherwise there is none. So the problem becomes whether we can find these $n$ ones.
    
    For a single $1$, choosing it in the final arrangement means its row and its column are used up. So we can build a bipartite graph with $n$ left vertices and $n$ right vertices: for each element equal to $1$, add an edge between the left vertex of its row and the right vertex of its column. Then we just run bipartite matching.

??? note "Code"
    ```cpp
    --8<-- "docs/graph/code/graph-matching/bigraph-match/bigraph-match_3.cpp"
    ```

???+ example "[Gym 104427B Lawyers](https://codeforces.com/gym/104427/problem/B)"
    There are $n$ lawyers, all accused of fraud. They need to defend each other so that every lawyer is released. Among the $n$ lawyers there are $m$ trust relations. A trust relation $(a, b)$ means $a$ can defend $b$. Every lawyer who is defended is found not guilty, with one exception: if $a$ and $b$ defend each other, both are found guilty.
    
    Determine whether every lawyer can be released.

??? note "Solution"
    For each **unordered pair** $(a, b)$, if $a$ can defend $b$, add an edge from this unordered pair to $b$, and vice versa.
    
    Keep only the pairs $(a, b)$ that have edges. The problem becomes a bipartite maximum matching with $m$ left vertices and $n$ right vertices.

??? note "Code"
    ```cpp
    --8<-- "docs/graph/code/graph-matching/bigraph-match/bigraph-match_4.cpp"
    ```

???+ example "[Codeforces 1404E Bricks](https://codeforces.com/problemset/problem/1404/E)"
    Cover an $n \times m$ grid exactly with some $1 \times x$ bricks. Bricks can be rotated, and some cells must not be covered.

??? note "Solution"
    Think about how the final arrangement is formed:
    
    First place a $1 \times 1$ brick on every cell that can be covered. A $1 \times x$ brick can be formed by "row-merging" $x$ consecutive $1 \times 1$ bricks in the same row one after another. Similarly, an $x \times 1$ brick can be formed by "column-merging" $x$ consecutive $1 \times 1$ bricks in the same column.
    
    Clearly, a row merge and a column merge cannot both involve the same brick, and the more merges we do, the fewer bricks we have. So we can build a bipartite graph with row merges as left vertices, column merges as right vertices, and the conflicts above as edges. The original problem then becomes a maximum independent set problem in a bipartite graph.

??? note "Code"
    ```cpp
    --8<-- "docs/graph/code/graph-matching/bigraph-match/bigraph-match_5.cpp"
    ```

???+ example "[Codeforces 1139E - Maximize Mex](https://codeforces.com/problemset/problem/1139/E)"
    There are $m$ multisets with $n$ elements in total. Each time, one element is removed from one of the multisets, and then you are asked: "If you pick at most one element from each multiset, what is the largest $\operatorname{mex}$ you can get?"

??? note "Solution"
    First consider the case with no removals.
    
    Create a new vertex for each multiset and a new vertex for each possible answer. Then for each element $a$ of the multiset corresponding to vertex $l_i$, add an edge from $l_i$ to $r_a$. This weaker version becomes a bipartite maximum matching.
    
    Now add back the removal operations, and it seems hopeless: removing an edge may change the matching drastically, and the cost is too high. So instead, go in reverse: add one edge at a time and continue augmenting from where we left off. That is why only Kuhn's algorithm works for this problem.

??? note "Code"
    ```cpp
    --8<-- "docs/graph/code/graph-matching/bigraph-match/bigraph-match_6.cpp"
    ```

???+ example "[Luogu P3355 - Knight Coexistence Problem](https://www.luogu.com.cn/problem/P3355)"
    There is an $n \times n$ chessboard, and some cells cannot hold a piece. What is the maximum number of knights you can place so that no two knights attack each other?

??? note "Solution"
    If we color the whole board so that no two black cells or two white cells are adjacent, then a knight can only attack cells of the other color.
    
    Then this is directly a maximum independent set problem in a bipartite graph.

??? note "Code"
    ```cpp
    --8<-- "docs/graph/code/graph-matching/bigraph-match/bigraph-match_7.cpp"
    ```

## Exercises

-   [Codeforces 1765A - Access Levels](https://codeforces.com/problemset/problem/1765/A)
-   [AtCoder abc274G - Security Camera 3](https://atcoder.jp/contests/abc274/tasks/abc274_g)
-   [Codeforces 1773D - Dominoes](https://codeforces.com/problemset/problem/1773/D)
-   [Luogu P5030 - Long-Necked Deer Placement](https://www.luogu.com.cn/problem/P5030)
-   [Luogu P2071 - Seat Arrangement](https://www.luogu.com.cn/problem/P2071)
-   [LibreOJ 6002 - Minimum Path Cover](https://loj.ac/p/6002)

## References

-   [Kuhn's Algorithm - Maximum Bipartite Matching](https://cp-algorithms.com/graph/kuhn_maximum_bipartite_matching.html)
-   [König's theorem on bipartite maximum matching and its proof (in Chinese)](https://matrix67.com/blog/archives/116)
-   [Implementing Dinitz on bipartite graphs by adamant - Codeforces blogs](https://codeforces.com/blog/entry/118098)
-   Bondy, John Adrian, and Uppaluri Siva Ramachandra Murty. Graph theory with applications. Vol. 290. London: Macmillan, 1976.
-   Chen Yinbo. A Brief Discussion of Graph Matching Algorithms and Their Applications. Proceedings of the 2015 Chinese National Team Candidates in Informatics Olympiad.
-   [Dulmage–Mendelsohn decomposition - Wikipedia](https://en.wikipedia.org/wiki/Dulmage%E2%80%93Mendelsohn_decomposition)
-   [Notes on Dulmage–Mendelsohn decomposition](https://www.cse.iitm.ac.in/~meghana/matchings/bip-decomp.pdf)

[^hk-comp-ref]: Bast, Holger; Mehlhorn, Kurt; Schäfer, Guido; Tamaki, Hisao (2006), "Matching algorithms are fast in sparse random graphs", Theory of Computing Systems, 39 (1): 3–14.
