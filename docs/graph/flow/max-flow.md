This page covers algorithms for the maximum flow problem.

## Overview

For the basic concepts of network flow, see [Introduction to network flow](../flow.md).

Let $G=(V,E)$ be a network with a source and a sink. We want to choose a suitable flow $f$ on $G$ that maximizes the value $|f|$ of the whole network (that is, $\sum_{x \in V} f(s, x) - \sum_{x \in V} f(x, s)$). This is called the maximum flow problem.

## Ford–Fulkerson augmentation

Ford–Fulkerson augmentation is the general name for a family of maximum flow algorithms. The method uses a greedy idea: it keeps finding augmenting paths to update the flow until it reaches the maximum flow.

### Overview

Given a network $G$ and a flow $f$ on $G$, we make the following definitions.

For an edge $(u, v)$, the difference between its capacity and its flow is called its residual capacity $c_f(u,v)$, that is, $c_f(u,v)=c(u,v)-f(u,v)$.

The subgraph of $G$ made of all vertices and all edges with residual capacity greater than $0$ is called the residual network $G_f$, that is, $G_f=(V,E_f)$, where $E_f=\left\{(u,v) \mid c_f(u,v)>0\right\}$.

???+ warning "Warning"
    As we will see shortly, flow can be negative, so edges of $E_f$ may not be in $E$. We explain this in detail below, after introducing augmentation.

A path in $G_f$ from the source $s$ to the sink $t$ is called an augmenting path. For an augmenting path, we add the same amount of flow to every edge $(u, v)$ on it, which increases the flow of the whole network. This process is called augmentation. So computing the maximum flow can be seen as adding up the flows obtained from a number of augmentations.

Also, during Ford–Fulkerson augmentation, for every edge $(u, v)$ we create a reverse edge $(v, u)$. We require $f(u, v) = -f(v, u)$. This can be maintained by adding a flow-cancelling step to every augmentation: when $f(u, v)$ increases, $f(v, u)$ decreases by the same amount.

???+ tip "Tip"
    In code for maximum flow algorithms, we often need quick access to the reverse edge. With an adjacency matrix this is trivial ($g_{u, v} \leftrightarrow g_{v, u}$). But the mainstream implementation is the better linked forward star (chained adjacency list). A common trick is to number edges starting from an even number (usually $0$), and always add the reverse edge right after each edge so their numbers are adjacent. Then edge $i$ and edge $i \oplus 1$ are always reverses of each other.

Readers new to this method may notice something counterintuitive: the flow $f(v, u)$ on a reverse edge can be negative. In fact, during Ford–Fulkerson augmentation, what really matters is the residual capacity $c_f$; the absolute value of $f(v, u)$ does not matter. We can view a decrease of flow on the reverse edge as an increase of its residual capacity $c_f(v, u)$. This matches the meaning of cancelling flow: an increase in the reverse edge's residual capacity means we may later walk along the reverse edge to cancel an earlier forward augmentation, which acts like an "undo".

The following example may help you understand this process. Suppose $G$ is a unit-capacity network, and consider this process:

-   $G$ has several augmenting paths. We choose to augment along one that passes through $u$ and then $v$ (shown in the left figure), and the flow increases by $1$.
-   Notice that if we augmented as in the middle figure, the maximum flow in this local area would be $2$, not $1$. But since the edge into $u$ and the edge out of $v$ used up their capacity in the first augmentation, we cannot do the augmentation in the middle figure now. This means our current flow is not optimal, yet locally there may be no other augmenting path (one using only original edges and no reverse edges).
-   Now add flow cancelling. After the first augmentation, cancelling means $c_f(v, u)$ gains $1$ unit of residual capacity, which is like adding the edge $(v, u)$. So we can augment once more along $p, v, u, q$ (the orange path in the right figure). The flows on the undirected edge $(u, v)$ cancel out across the two augmentations, and surprisingly, the combined result of the two augmentations is equivalent to the middle figure.

![](./images/flow2.png)

This example shows that, thanks to the "cancelling" effect of flow cancelling, we do not need to worry about choosing augmenting paths in the "wrong" order.

It is easy to see that as long as $G_f$ has an augmenting path, augmenting along it increases the total flow. Otherwise, the total flow has already reached its maximum and we are done. This is Ford–Fulkerson augmentation.

### Max-flow min-cut theorem

We now roughly understand the idea of Ford–Fulkerson augmentation, but how do we prove it is correct? Why is the flow $f$ at the end a maximum flow?

In fact, the correctness of Ford–Fulkerson augmentation is equivalent to the max-flow min-cut theorem (The Maxflow-Mincut Theorem). The theorem says that for any network $G = (V, E)$, the maximum flow $f$ and the minimum cut $\{S, T\}$ always satisfy $|f| = ||S, T||$.

To prove the max-flow min-cut theorem, we start from a lemma: for a network $G = (V, E)$, for any flow $f$ and any cut $\{S, T\}$, we always have $|f| \leq ||S, T||$, with equality if and only if all edges in $\{(u, v) | u \in S, v \in T\}$ are saturated and all edges in $\{(u, v) | u \in T, v \in S\}$ carry no flow.

???+ note "Proof"
    $$
    \begin{aligned}
    |f| & = f(s) \\
        & = \sum_{u \in S} f(u) \\
        & = \sum_{u \in S} \left( \sum_{v \in V} f(u, v) - \sum_{v \in V} f(v, u) \right) \\
        & = \sum_{u \in S} \left( \sum_{v \in T} f(u, v) + \sum_{v \in S} f(u, v) - \sum_{v \in T} f(v, u) - \sum_{v \in S} f(v, u) \right) \\
        & = \sum_{u \in S} \left( \sum_{v \in T} f(u, v) - \sum_{v \in T} f(v, u) \right) + \sum_{u \in S} \sum_{v \in S} f(u, v) - \sum_{u \in S} \sum_{v \in S} f(v, u) \\
        & = \sum_{u \in S} \left( \sum_{v \in T} f(u, v) - \sum_{v \in T} f(v, u) \right) \\
        & \leq \sum_{u \in S} \sum_{v \in T} f(u, v) \\
        & \leq \sum_{u \in S} \sum_{v \in T} c(u, v) \\
        & = ||S, T|| \\
    \end{aligned}
    $$
    
    For equality, the first inequality needs all edges in $\{(u, v) \mid u \in T, v \in S\}$ to carry no flow, and the second needs all edges in $\{(u, v) \mid u \in S, v \in T\}$ to be saturated. This proves the lemma.

So, can the equality condition always be met in any network? If yes, the max-flow min-cut theorem is proved. Let's try to prove it.

???+ note "Proof"
    Suppose that after some augmentation we get a flow $f$ such that $G_f$ has no augmenting path, that is, there is no path from $s$ to $t$ in $G_f$. Let $S$ be the set of vertices reachable from $s$, and let $T = V \setminus S$.
    
    Clearly $\{S, T\}$ is a cut of $G_f$, and $||S, T|| = \sum_{u \in S} \sum_{v \in T} c_f(u, v) = 0$. Since residual capacities are non-negative, this means that for any $u \in S, v \in T, (u, v) \in E_f$, we have $c_f(u, v) = 0$. Below we split these edges into two cases: edges of the original graph and reverse edges.
    
    -   $(u, v) \in E$: then $c_f(u, v) = c(u, v) - f(u, v) = 0$, so $c(u, v) = f(u, v)$; that is, all edges in $\{(u, v) \mid u \in S, v \in T\}$ are saturated;
    -   $(v, u) \in E$: then $c_f(u, v) = c(u, v) - f(u, v) = 0 - f(u, v) = f(v, u) = 0$; that is, all edges in $\{(v, u) \mid u \in S, v \in T\}$ carry no flow.
    
    So when augmentation stops, the flow $f$ above meets the equality condition. By the inequality in the lemma, $f$ is naturally a maximum flow of $G$, and $\{S, T\}$ is a minimum cut of $G$.

It is easy to see that Kőnig's theorem is a special case of the max-flow min-cut theorem. In fact, both are related to duality in linear programming.

### Time complexity

On a network $G = (V, E)$ with integer capacities, assuming trivially that each augmentation adds an integer amount of flow, an upper bound on the time complexity of Ford–Fulkerson augmentation is $O(|E||f|)$, where $f$ is the maximum flow of $G$. This is because one augmentation takes $O(|E|)$ time, and each augmentation increases the total flow, so there cannot be more than $|f|$ augmentations.

Different implementations of Ford–Fulkerson augmentation have different time complexities. The main ones are Edmonds–Karp, Dinic, SAP, ISAP and so on, which we introduce one by one below.

### Edmonds–Karp algorithm

#### Idea

How do we find an augmenting path in $G_f$? When we think about a concrete implementation of Ford–Fulkerson augmentation, the most natural choice is BFS. Ford–Fulkerson augmentation then becomes the Edmonds–Karp algorithm. It works as follows:

-   If we can reach $t$ from $s$ by BFS in $G_f$, we have found a new augmenting path.

-   For an augmenting path $p$, compute the minimum residual capacity of the edges on $p$, $\Delta = \min_{(u, v) \in p} c_f(u, v)$. Add $\Delta$ units of flow to every edge on $p$ and cancel $\Delta$ units of flow on their reverse edges. The maximum flow increases by $\Delta$.

-   Since we changed the flow, we get a new $G_f$. Repeat the process on the new $G_f$ until no augmenting path exists; then the flow no longer increases.

This is the Edmonds–Karp algorithm.

#### Time complexity

Now let's analyze the time complexity of the Edmonds–Karp algorithm.

Clearly, one round of BFS augmentation takes $O(|E|)$ time.

The total number of augmentation rounds is bounded by $O(|V||E|)$. This claim is often "proved" incorrectly online (or glossed over vaguely). Below we try to give a more formal proof[^ref_ek].

???+ note "Proof of the bound on the number of augmentation rounds"
    First we introduce a lemma, the non-decreasing shortest path lemma. Let $d_f(u)$ be the distance from vertex $u$ to the source $s$ in $G_f$ (that is, the shortest path length; the same below). For one round of augmentation, let $f$ and $f'$ be the flows before and after augmentation. We claim that for every vertex $u$, augmentation always gives $d_{f'}(u) \geq d_f(u)$. We will prove this lemma later.
    
    Call the edge with the smallest residual capacity on an augmenting path a bottleneck edge (if several edges tie, pick any). If a directed edge $(u, v)$ is chosen as the bottleneck edge, augmentation empties its residual capacity so the bottleneck edge disappears, and cancelling creates the reverse edge (if it did not exist before), that is, $(u, v) \not \in E_{f'}$ and $(v, u) \in E_{f'}$. From this we know that for an undirected edge $(u, v)$, augmentations in its two directions always alternate.
    
    When augmenting along $(u, v)$ in $G_f$, $d_f(u) + 1 = d_f(v)$, and afterwards the residual network becomes $G_{f'}$. When augmenting along $(v, u)$ in $G_{f'}$, $d_{f'}(v) + 1 = d_{f'}(u)$. By the non-decreasing shortest path lemma, $d_{f'}(v) \geq d_f(v)$. Chaining all of these gives $d_{f'}(u) \geq d_{f}(u) + 2$. In other words, if a directed edge $(u, v)$ is chosen as the bottleneck edge, then compared with the previous time it was chosen, the distance from $u$ to $s$ has increased by at least $2$.
    
    The distance from $s$ to any vertex cannot exceed $|V|$. Combined with the property above, each edge is chosen as the bottleneck edge $O(|V|)$ times. Multiplying by the number of edges gives the bound $O(|V||E|)$ on the total number of augmentation rounds.
    
    Next we prove the non-decreasing shortest path lemma, that is, $d_{f'}(u) \geq d_f(u)$. The proof is not hard, but it may be a bit twisty, so take a moment to think it through carefully.
    
    ???+ note "Proof of the non-decreasing shortest path lemma"
        Suppose, for contradiction, that in some round of augmentation there are vertices whose distance to $s$ becomes smaller after the augmentation. Let $v$ be the one among them with the smallest distance to $s$ (that is, $v = \arg \min_{x \in V, d_{f'}(x) < d_f(x)} d_{f'}(x)$). Note that by this assumption, $d_{f'}(v) < d_f(v)$ is given.
        
        On the shortest path from $s$ to $v$ in $G_{f'}$, let $u$ be the vertex just before $v$, that is, $d_{f'}(u) + 1 = d_{f'}(v)$.
        
        So that $u$ does not break the "smallest distance" property of $v$, $u$ must satisfy $d_{f'}(u) \geq d_f(u)$.
        
        Adding one to both sides of this inequality gives $d_{f'}(v) \geq d_f(u) + 1$. Using the assumption to loosen the bound, we get $d_f(v) > d_f(u) + 1$.
        
        Now consider the direction of augmentation on $(u, v)$.
        
        -   Suppose the directed edge $(u, v) \in E_f$. By the "breadth-first" property of BFS, $d_f(u) + 1 \geq d_f(v)$. This conflicts with the bound above, a contradiction.
        -   Suppose the directed edge $(u, v) \not \in E_f$. By the definition of $u$ we know $(u, v) \in E_{f'}$, so this edge must exist because this round's augmentation went through $(v, u)$ and cancelling created the reverse edge, that is, $d_f(v) + 1 = d_f(u)$. This conflicts with the bound above, a contradiction.
        
        Since augmentation on $(u, v)$ in either direction leads to a contradiction, the assumption is false, and the non-decreasing shortest path lemma is proved.

Multiplying the cost of one round of BFS augmentation by the bound on the number of rounds, the time complexity of the Edmonds–Karp algorithm is $O(|V||E|^2)$.

#### Implementation

A possible implementation of the Edmonds–Karp algorithm is as follows.

??? note "Reference code"
    ```cpp
    constexpr int MAXN = 250;
    constexpr int INF = 0x3f3f3f3f;
    
    struct Edge {
      int from, to, cap, flow;
    
      Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
    };
    
    struct EK {
      int n, m;             // n: number of vertices, m: number of edges
      vector<Edge> edges;   // edges: the set of all edges
      vector<int> G[MAXN];  // G: vertex x -> indices in edges of all edges from x
      int a[MAXN], p[MAXN];  // a: vertex x -> max flow given to x by the last edge reaching x in the BFS
                             // p: vertex x -> the last edge reaching x in the BFS
    
      void init(int n) {
        for (int i = 0; i < n; i++) G[i].clear();
        edges.clear();
      }
    
      void AddEdge(int from, int to, int cap) {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
      }
    
      int Maxflow(int s, int t) {
        int flow = 0;
        for (;;) {
          memset(a, 0, sizeof(a));
          queue<int> Q;
          Q.push(s);
          a[s] = INF;
          while (!Q.empty()) {
            int x = Q.front();
            Q.pop();
            for (int i = 0; i < G[x].size(); i++) {  // loop over edges starting at x
              Edge& e = edges[G[x][i]];
              if (!a[e.to] && e.cap > e.flow) {
                p[e.to] = G[x][i];  // G[x][i] is the last edge reaching e.to
                a[e.to] =
                    min(a[x], e.cap - e.flow);  // flow given to e.to by the last edge reaching it
                Q.push(e.to);
              }
            }
            if (a[t]) break;  // if the sink received flow, exit the BFS
          }
          if (!a[t])
            break;  // if the sink received no flow, the source and sink are not connected
          for (int u = t; u != s;
               u = edges[p[u]].from) {  // follow u back along the s -> t path from the BFS
            edges[p[u]].flow += a[t];      // increase flow on the path's edges
            edges[p[u] ^ 1].flow -= a[t];  // decrease flow on the reverse edges
          }
          flow += a[t];
        }
        return flow;
      }
    };
    ```

### Dinic's algorithm

#### Idea

Before augmenting, first run a BFS on $G_f$ to split it into layers: group vertices into levels by their distance $d(u)$ to the source $s$. Flow through $u$ may only go to vertices $v$ in the next level, that is, delete the outgoing edges from $u$ to vertices with an equal or smaller level. The remaining part of $G_f$ is called the level graph. Formally, $G_L = (V, E_L)$ is the level graph of $G_f = (V, E_f)$, where $E_L = \left\{ (u, v) \mid (u, v) \in E_f, d(u) + 1 = d(v) \right\}$.

If we find a maximal augmenting flow $f_b$ on the level graph $G_L$, such that $f_b$ cannot be increased any further using only $G_L$, we call $f_b$ a blocking flow of $G_L$.

??? warning "Warning"
    Although above we only defined augmentation/augmenting flow on a single augmenting path, in a broader sense the word "augment" can refer not only to the augmenting flow on a single path but also to a union of several augmenting flows. The latter is the meaning we use when defining blocking flows.

With the level graph and blocking flow defined, Dinic's algorithm works as follows.

1.  Build the level graph $G_L$ from $G_f$ with BFS.
2.  Find a blocking flow $f_b$ on $G_L$ with DFS.
3.  Add $f_b$ to the current flow $f$, that is, $f \leftarrow f + f_b$.
4.  Repeat until there is no path from $s$ to $t$.

The $f$ at this point is the maximum flow.

Before analyzing the complexity, we need to explain the step "find a blocking flow $f_b$ on $G_L$ with DFS". Building the level graph with BFS should be trivial for readers of this page, but finding the blocking flow with DFS needs a trick: the current-arc optimization.

During the DFS on $G_L$, if a vertex $u$ has many incoming and outgoing edges, and every time $u$ receives flow from an incoming edge it scans its whole list of outgoing edges to decide where to send it, then the local cost at $u$ can reach $O(|E|^2)$ in the worst case. To avoid this, if at some point we know an edge $(u, v)$ has been augmented to its limit (it has no residual capacity left, or everything after $v$ is already blocked), then there is no need for $u$ to try sending flow along $(u, v)$ again. So for each vertex $u$, we keep track of the first outgoing edge in its list that is still worth trying. By convention, this pointer is called the current arc, and the technique is called the current-arc optimization.

??? note "Multi-path augmentation"
    Multi-path augmentation is a constant-factor optimization of Dinic's algorithm. If we have found an augmenting path $p$ from $s$ to $t$ on the level graph, we do not necessarily need to start again from $s$ to find the next one; we can instead branch off from the last position on $p$ that still has residual capacity. Since this matches the shape of backtracking, the optimization comes naturally in a DFS implementation.
    
    ??? failure "Common misconception"
        Probably because of wrong statements spread across many online resources, many contestants like to list the current-arc optimization and multi-path augmentation side by side as "the two optimizations of Dinic's algorithm". In fact, the current-arc optimization is part of what makes Dinic's time complexity correct, while multi-path augmentation is only a constant-factor optimization that does not affect the complexity.

#### Time complexity

With the current-arc optimization, the time complexity of Dinic's algorithm is analyzed as follows.

First, we prove that finding the blocking flow by DFS in one round takes $O(|V||E|)$ time.

???+ note "Proof of the time complexity of one round"
    Every augmenting path in the blocking flow $f_b$ is obtained by repeatedly following current arcs on $G_L$, and each augmenting path takes at most $|V|$ jumps.
    
    Each augmenting path found makes one bottleneck edge disappear (its residual capacity drops to zero). Let $E_1$ be the set of bottleneck edges zeroed by the augmenting paths in $f_b$. Because of the layered structure of $G_L$, after a bottleneck edge disappears, its reverse edge cannot be used by any other augmenting path in the same round. So $E_1$ is a subset of $E_L$.
    
    Also, for walks along current arcs that get blocked somewhere and fail to produce an augmenting path, let $E_2$ be the set of the last edges of these incomplete paths. The members of $E_2$ are not saturated, so $E_1$ and $E_2$ are disjoint, and $E_1 \cup E_2$ is still a subset of $E_L$.
    
    Each member of $E_1 \cup E_2$ costs at most $|V|$ jumps (and with multi-path augmentation some jumps are counted more than once). So, putting it all together, the total number of jumps in the DFS is at most $|V||E_L|$.
    
    ??? failure "A common false proof"
        For each vertex we keep the next edge that can be augmented, and the current arc changes at most $|E|$ times, so the worst-case time of one round is $O(|V||E|)$.
    
    ??? bug "Bug"
        "The current arc changes at most $|E|$ times" does not imply "each vertex visits its outgoing edges at most $|E|$ times". This is because visiting the current arc does not necessarily use up its residual capacity, so vertex $u$ may visit the same current arc many times.

The number of levels in the level graph clearly cannot exceed $|V|$. If we can prove that the number of levels strictly increases during augmentation, then Dinic's algorithm runs $O(|V|)$ rounds. Let's try to prove this[^ref_dinic].

???+ note "Proof that the number of levels is monotonic"
    We need a concept from push-relabel algorithms (another family of maximum flow algorithms): height labels. To make the proof fit better with height labels, in this proof we let $d_f(u)$ be the distance from vertex $u$ to the **sink** $t$ in $G_f$, and build levels from the **sink** instead of the source (this makes no real difference). For one round of augmentation, let $f$ and $f'$ be the flows before and after it. After the blocking flow is found and added in this round, the level graph changes from $G_L = (V, E_L)$ to $G'_{L} = (V, E'_L)$.
    
    We give height labels an informal temporary definition: on a network $G = (V, E)$, let $h$ be a function from the vertex set $V$ to the integers $N$. Then $h$ is a valid height labeling of $G$ if and only if $h(u) \leq h(v) + 1$ holds for every $(u, v) \in E$.
    
    Look at every member $(u, v)$ of $E_{f'}$. We find that $(u, v) \in E_{f'}$ for one of the following two reasons.
    
    -   $(u, v) \in E_f$, and its residual capacity was not used up in this round. By the definition of shortest paths, we have $d_f(u) \leq d_f(v) + 1$;
    -   $(u, v) \not \in E_f$, but in this round the blocking flow went through $(v, u)$ and cancelling created the reverse edge. By the definitions of the level graph and blocking flow, we have $d_f(u) + 1 = d_f(v)$.
    
    These observations give a conclusion: $d_f$ is a valid height labeling on $G_{f'}$. Of course, it is also valid on the subgraph $G'_L$ of $G_{f'}$.
    
    Now, for an augmenting path $p = (s, \dots, u, v, \dots, t)$ on $G'_L$, consider building it from an empty path by adding one vertex at a time, in reverse order of $p$ (from $t$ to $s$). Suppose vertex $v$ is already added and vertex $u$ is being added. After adding $u$, by the definition of the level graph, $d_{f'}(u)$ is $1$ more than $d_{f'}(v)$. Meanwhile, since $d_f$ is a height labeling on $G'_L$, $d_f(u)$ may be $1$ more than $d_f(v)$, or stay the same, or be smaller. So after the whole path is added, we get $d_{f'}(s) \geq d_f(s)$, with equality if and only if $d_f(u) = d_f(v) + 1$ holds for every $(u, v) \in p$. If equality cannot hold, then $d_{f'}(s) > d_f(s)$, which is exactly what we want: "the number of levels strictly increases during augmentation". Below we prove that equality cannot hold.
    
    Suppose, for contradiction, that $d_{f'}(s) = d_f(s)$, and let's derive a contradiction. We claim that on $G'_L$, $p$ contains at least one edge $(u, v)$ that does not exist in $G_L$. If there were no such edge, then since $d_f(s) = d_{f'}(s)$, by the definitions of the level graph and blocking flow, the augmentation on $G_L$ would not have been finished yet. To avoid this contradiction, our claim must be true.
    
    Let $(u, v)$ be such an edge. It can satisfy the claim only for one of the following two reasons.
    
    -   $(u, v) \in E_f$ but $d_f(u) \leq d_f(v) + 1$ is not tight, so by the definition of the level graph $(u, v) \not \in E_L$, and it was added to $E'_L$ when the levels were rebuilt in the new round after augmentation;
    -   $(u, v) \not \in E_f$. This means the edge $(u, v)$ was created because the blocking flow in this round went through $(v, u)$ and cancelling created the reverse edge, that is, $d_f(u) = d_f(v) - 1$.
    
    Either way, we get $d_f(u) \neq d_f(v) + 1$, so the necessary and sufficient condition for equality in $d_{f'}(s) \geq d_f(s)$ cannot be met. This conflicts with the assumption $d_{f'}(s) = d_f(s)$, and the statement is proved.
    
    ??? failure "Another common false proof"
        Suppose, for contradiction, that the number of levels in the level graph stays the same after a round of augmentation. Then there should still be at least one augmenting path from $s$ to $t$ in the level graph where adjacent vertices differ by exactly $1$ in level. This path was not augmented, which means the round of augmentation is not finished. To avoid this contradiction, the statement must hold.
    
    ??? bug "Bug"
        "After a round of augmentation, the $s$-$t$ shortest path in the new level graph has the same length as before" does not imply "this round of augmentation on the old level graph is not finished". This is because there is no reason the two level graphs have the same edge set; the $s$-$t$ shortest path in the new level graph may use edges that do not exist in the old one.

Multiplying the cost $O(|V||E|)$ of one round by the number of rounds $O(|V|)$, the time complexity of Dinic's algorithm is $O(|V|^2|E|)$.

To make Dinic's algorithm actually run close to its theoretical bound, the input network must be specially constructed. In competitive programming practice, network flow problems usually focus on the skill of modeling the original problem as a network flow problem. Our models usually do not have the special properties that make Dinic's algorithm slow; on the contrary, Dinic's algorithm is very efficient on most graphs. So network flow problems often have large constraints, and "plugging $|V|, |E|$ into $|V|^2|E|$ to estimate the running time" does not work. In fact, making an accurate estimate takes some experience with how fast Dinic's algorithm really is, so practice more.

#### Time complexity in special cases

On some well-behaved graphs, Dinic's algorithm has a better time complexity.

For a network $G = (V, E)$, if all edges have capacity $1$, that is, $c(u, v) \in \{0, 1\}$ for every $(u, v) \in E$, we say $G$ has unit capacity.

In a unit-capacity network, one round of augmentation in Dinic's algorithm takes $O(|E|)$ time.

???+ note "Proof"
    This is because each augmentation saturates and removes every edge on the augmenting path, so in one round each edge can be augmented only once.

In a unit-capacity network, Dinic's algorithm runs $O(|E|^{\frac{1}{2}})$ rounds.

???+ note "Proof"
    Build levels around the source $s$, and let $d_f(u)$ be the distance from vertex $u$ to the source $s$ in $G_f$. Also, define the vertex set $\left\{u \mid u \in V, d_f(u) = k \right\}$ as level $k$, $D_k$, and let $S_k = \cup_{i \leq k} D_i$.
    
    Suppose we have already done $|E|^{\frac{1}{2}}$ rounds. By the pigeonhole principle, there is at least one $k$ for which the edge set $\left\{ (u, v) \mid u \in D_k, v \in D_{k+1}, (u, v) \in E_f \right\}$ has size at most $\frac {|E|} {|E|^{\frac{1}{2}}} \approx |E|^{\frac{1}{2}}$. Clearly $\{S_k, V - S_k\}$ is an $s$-$t$ cut of $G_f$ with capacity at most $|E|^{\frac{1}{2}}$. By the max-flow min-cut theorem, the maximum flow on $G_f$ is at most $|E|^{\frac{1}{2}}$, so at most $|E|^{\frac{1}{2}}$ more rounds can run on $G_f$. So the total number of rounds is $O(|E|^{\frac{1}{2}})$.

In a unit-capacity network, Dinic's algorithm runs $O(|V|^{\frac{2}{3}})$ rounds.

???+ note "Proof"
    Suppose we have already done $2 |V|^{\frac{2}{3}}$ rounds. At most half of the levels ($|V|^{\frac{2}{3}}$ of them) can contain more than $|V|^{\frac{1}{3}}$ vertices. So no matter how the level sizes are distributed, there is at least one $k$ such that two adjacent levels both contain at most $|V|^{\frac{1}{3}}$ vertices, that is, $|D_k| \leq |V|^{\frac{1}{3}}$ and $|D_{k+1}| \leq |V|^{\frac{1}{3}}$.
    
    To maximize the number of edges between $D_k$ and $D_{k+1}$, assume they form a complete bipartite graph. Then the edge set $\left\{ (u, v) \mid u \in D_k, v \in D_{k+1}, (u, v) \in E_f \right\}$ has size at most $|V|^{\frac{2}{3}}$. Clearly $\{S_k, V - S_k\}$ is an $s$-$t$ cut of $G_f$ with capacity at most $|V|^{\frac{2}{3}}$. By the max-flow min-cut theorem, the maximum flow on $G_f$ is at most $|V|^{\frac{2}{3}}$, so at most $|V|^{\frac{2}{3}}$ more rounds can run on $G_f$. So the total number of rounds is $O(|V|^{\frac{2}{3}})$.

In a unit-capacity network, if every vertex $u$ other than the source and sink satisfies $\mathit{deg}_{\mathit{in}}(u) = 1$ or $\mathit{deg}_{\mathit{out}}(u) = 1$, then Dinic's algorithm runs $O(|V|^{\frac{1}{2}})$ rounds. Here $\mathit{deg}_{\mathit{in}}(u)$ and $\mathit{deg}_{\mathit{out}}(u)$ are the in-degree and out-degree of vertex $u$.

???+ note "Proof"
    We use the following lemma: in a network of this form, any flow can always be decomposed into a number of unit-flow, **vertex-disjoint** augmenting paths.
    
    Suppose we have already done $|V|^{\frac{1}{2}}$ rounds. By the definition of the level graph, every new augmenting path now has length at least $|V|^{\frac{1}{2}}$.
    
    Consider decomposing the maximum flow on $G_f$ into augmenting paths. There can be at most $\frac {|V|} {|V|^{\frac{1}{2}}} \approx |V|^{\frac{1}{2}}$ of them, which means at most $|V|^{\frac{1}{2}}$ more rounds can run on $G_f$. So the total number of rounds is $O(|V|^{\frac{1}{2}})$.

Putting this together, we get some corollaries.

-   On a unit-capacity network, the total time complexity of Dinic's algorithm is $O(|E| \min(|E|^\frac{1}{2}, |V|^{\frac{2}{3}}))$.
-   On a unit-capacity network, if every vertex $u$ other than the source and sink satisfies $\mathit{deg}_{\mathit{in}}(u) = 1$ or $\mathit{deg}_{\mathit{out}}(u) = 1$, the total time complexity of Dinic's algorithm is $O(|E||V|^{\frac{1}{2}})$. Maximum bipartite matching is usually solved with the Hopcroft–Karp algorithm, which is in fact a special case of Dinic's algorithm on unit-capacity networks with the degree restriction above.

#### Implementation

??? note "Reference code"
    ```cpp
    struct MF {
      struct edge {
        int v, nxt, cap, flow;
      } e[N];
    
      int fir[N], cnt = 0;
    
      int n, S, T;
      ll maxflow = 0;
      int dep[N], cur[N];
    
      void init() {
        memset(fir, -1, sizeof fir);
        cnt = 0;
      }
    
      void addedge(int u, int v, int w) {
        e[cnt] = {v, fir[u], w, 0};
        fir[u] = cnt++;
        e[cnt] = {u, fir[v], 0, 0};
        fir[v] = cnt++;
      }
    
      bool bfs() {
        queue<int> q;
        memset(dep, 0, sizeof(int) * (n + 1));
    
        dep[S] = 1;
        q.push(S);
        while (q.size()) {
          int u = q.front();
          q.pop();
          for (int i = fir[u]; ~i; i = e[i].nxt) {
            int v = e[i].v;
            if ((!dep[v]) && (e[i].cap > e[i].flow)) {
              dep[v] = dep[u] + 1;
              q.push(v);
            }
          }
        }
        return dep[T];
      }
    
      int dfs(int u, int flow) {
        if ((u == T) || (!flow)) return flow;
    
        int ret = 0;
        for (int& i = cur[u]; ~i; i = e[i].nxt) {
          int v = e[i].v, d;
          if ((dep[v] == dep[u] + 1) &&
              (d = dfs(v, min(flow - ret, e[i].cap - e[i].flow)))) {
            ret += d;
            e[i].flow += d;
            e[i ^ 1].flow -= d;
            if (ret == flow) return ret;
          }
        }
        return ret;
      }
    
      void dinic() {
        while (bfs()) {
          memcpy(cur, fir, sizeof(int) * (n + 1));
          maxflow += dfs(S, INF);
        }
      }
    } mf;
    ```

### MPM algorithm

The **MPM** (Malhotra, Pramodh-Kumar and Maheshwari) algorithm can find the maximum flow in two ways: with a heap-based priority queue, in $O(n^3\log n)$ time; or with the common BFS approach, in $O(n^3)$ time. Note that this section only analyzes the $O(n^3)$ algorithm, which is both faster and simpler.

The overall structure of the MPM algorithm is similar to Dinic's algorithm: it also runs in phases. In each phase, it finds augmenting paths in the layered network of the residual network of $G$. The main difference from Dinic's algorithm is how it finds augmenting paths: the path-finding part of MPM takes only $O(n^2)$, so its time complexity is better than Dinic's.

The MPM algorithm works with vertex capacities instead of edge capacities. In the layered network $L$, define the capacity $p(v)$ of vertex $v$ as the minimum of its incoming residual and outgoing residual capacities. Then:

$$
\begin{aligned}
p_{in}(v) &= \sum\limits_{(u,v) \in L} (c(u, v) - f(u, v)) \\
p_{out}(v) &= \sum\limits_{(v,u) \in L} (c(v, u) - f(v, u)) \\
p(v) &= \min (p_{in}(v), p_{out}(v))
\end{aligned}
$$

A vertex $r$ is called a reference vertex if and only if $p(r) = \min {p(v)}$. For a reference vertex $r$, we can always increase the flow through $r$ by $p(r)$ so that its capacity becomes $0$. This is because $L$ is a directed acyclic graph and every vertex in $L$ has capacity at least $p(r)$, so we can always find a directed path from $s$ through $r$ to $t$. We then increase the flow on every edge of this path by $p(r)$. This path is the augmenting path of this phase. BFS can be used to find it. After augmenting, all saturated edges can be removed from $L$, since they will not be used later in this phase. Likewise, every vertex other than $s$ and $t$ with no outgoing or no incoming edges can be removed.

#### Time complexity

Each phase of the MPM algorithm takes $O(V^2)$, because there are at most $V$ iterations (each iteration removes at least the chosen reference vertex), and in each iteration we delete all edges we pass through except at most $V$ of them. Summing up, we get $O(V^2+E)=O(V^2)$. Since the total number of phases is less than $V$, the total running time of the MPM algorithm is $O(V^3)$.

???+ note "Proof that the number of phases is less than V"
    The MPM algorithm finishes in fewer than $V$ phases. To prove this, we first need to prove two lemmas.
    
    **Lemma 1**: After each iteration, the distance from $s$ to every vertex does not decrease, that is, $level_{i+1}[v] \ge level_{i}[v]$.
    
    **Proof**: Fix a phase $i$ and a vertex $v$. Consider any shortest path $P$ from $s$ to $v$ in $G_{i}^R$. The length of $P$ equals $level_{i}[v]$. Note that $G_{i}^R$ can only contain back edges and forward edges of $G_{i}^R$. If $P$ has no back edge of $G_{i}^R$, then $level_{i+1}[v] \ge level_{i}[v]$, because $P$ is also a path in $G_{i}^R$. Now suppose $P$ has at least one back edge, and the first such edge is $(u,w)$. Then $level_{i+1}[u] \ge level_{i}[u]$ (by the first case). The edge $(u,w)$ does not belong to $G_{i}^R$, so $(u,w)$ was affected by the augmenting path of the previous iteration. This means $level_{i}[u] = level_{i}[w]+1$. Also, $level_{i+1}[w] = level_{i+1}[u]+1$. From these two equations and $level_{i+1}[u] \ge level_{i}[u]$, we get $level_{i+1}[w] \ge level_{i}[w]+2$. The same idea applies to the rest of the path.
    
    **Lemma 2**: $level_{i+1}[t] > level_{i}[t]$.
    
    **Proof**: From Lemma 1, $level_{i+1}[t] \ge level_{i}[t]$. Suppose $level_{i+1}[t] = level_{i}[t]$. Note that $G_{i}^R$ can only contain back edges and forward edges of $G_{i}^R$. This means there is a shortest path in $G_{i}^R$ that was not blocked by the augmenting paths. This is a contradiction.

#### Implementation

??? note "Reference code"
    ```cpp
    struct MPM {
      struct FlowEdge {
        int v, u;
        long long cap, flow;
    
        FlowEdge() {}
    
        FlowEdge(int _v, int _u, long long _cap, long long _flow)
            : v(_v), u(_u), cap(_cap), flow(_flow) {}
    
        FlowEdge(int _v, int _u, long long _cap)
            : v(_v), u(_u), cap(_cap), flow(0ll) {}
      };
    
      constexpr static long long flow_inf = 1e18;
      vector<FlowEdge> edges;
      vector<char> alive;
      vector<long long> pin, pout;
      vector<list<int>> in, out;
      vector<vector<int>> adj;
      vector<long long> ex;
      int n, m = 0;
      int s, t;
      vector<int> level;
      vector<int> q;
      int qh, qt;
    
      void resize(int _n) {
        n = _n;
        ex.resize(n);
        q.resize(n);
        pin.resize(n);
        pout.resize(n);
        adj.resize(n);
        level.resize(n);
        in.resize(n);
        out.resize(n);
      }
    
      MPM() {}
    
      MPM(int _n, int _s, int _t) {
        resize(_n);
        s = _s;
        t = _t;
      }
    
      void add_edge(int v, int u, long long cap) {
        edges.push_back(FlowEdge(v, u, cap));
        edges.push_back(FlowEdge(u, v, 0));
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
      }
    
      bool bfs() {
        while (qh < qt) {
          int v = q[qh++];
          for (int id : adj[v]) {
            if (edges[id].cap - edges[id].flow < 1) continue;
            if (level[edges[id].u] != -1) continue;
            level[edges[id].u] = level[v] + 1;
            q[qt++] = edges[id].u;
          }
        }
        return level[t] != -1;
      }
    
      long long pot(int v) { return min(pin[v], pout[v]); }
    
      void remove_node(int v) {
        for (int i : in[v]) {
          int u = edges[i].v;
          auto it = find(out[u].begin(), out[u].end(), i);
          out[u].erase(it);
          pout[u] -= edges[i].cap - edges[i].flow;
        }
        for (int i : out[v]) {
          int u = edges[i].u;
          auto it = find(in[u].begin(), in[u].end(), i);
          in[u].erase(it);
          pin[u] -= edges[i].cap - edges[i].flow;
        }
      }
    
      void push(int from, int to, long long f, bool forw) {
        qh = qt = 0;
        ex.assign(n, 0);
        ex[from] = f;
        q[qt++] = from;
        while (qh < qt) {
          int v = q[qh++];
          if (v == to) break;
          long long must = ex[v];
          auto it = forw ? out[v].begin() : in[v].begin();
          while (true) {
            int u = forw ? edges[*it].u : edges[*it].v;
            long long pushed = min(must, edges[*it].cap - edges[*it].flow);
            if (pushed == 0) break;
            if (forw) {
              pout[v] -= pushed;
              pin[u] -= pushed;
            } else {
              pin[v] -= pushed;
              pout[u] -= pushed;
            }
            if (ex[u] == 0) q[qt++] = u;
            ex[u] += pushed;
            edges[*it].flow += pushed;
            edges[(*it) ^ 1].flow -= pushed;
            must -= pushed;
            if (edges[*it].cap - edges[*it].flow == 0) {
              auto jt = it;
              ++jt;
              if (forw) {
                in[u].erase(find(in[u].begin(), in[u].end(), *it));
                out[v].erase(it);
              } else {
                out[u].erase(find(out[u].begin(), out[u].end(), *it));
                in[v].erase(it);
              }
              it = jt;
            } else
              break;
            if (!must) break;
          }
        }
      }
    
      long long flow() {
        long long ans = 0;
        while (true) {
          pin.assign(n, 0);
          pout.assign(n, 0);
          level.assign(n, -1);
          alive.assign(n, true);
          level[s] = 0;
          qh = 0;
          qt = 1;
          q[0] = s;
          if (!bfs()) break;
          for (int i = 0; i < n; i++) {
            out[i].clear();
            in[i].clear();
          }
          for (int i = 0; i < m; i++) {
            if (edges[i].cap - edges[i].flow == 0) continue;
            int v = edges[i].v, u = edges[i].u;
            if (level[v] + 1 == level[u] && (level[u] < level[t] || u == t)) {
              in[u].push_back(i);
              out[v].push_back(i);
              pin[u] += edges[i].cap - edges[i].flow;
              pout[v] += edges[i].cap - edges[i].flow;
            }
          }
          pin[s] = pout[t] = flow_inf;
          while (true) {
            int v = -1;
            for (int i = 0; i < n; i++) {
              if (!alive[i]) continue;
              if (v == -1 || pot(i) < pot(v)) v = i;
            }
            if (v == -1) break;
            if (pot(v) == 0) {
              alive[v] = false;
              remove_node(v);
              continue;
            }
            long long f = pot(v);
            ans += f;
            push(v, s, f, false);
            push(v, t, f, true);
            alive[v] = false;
            remove_node(v);
          }
        }
        return ans;
      }
    };
    ```

### ISAP

In Dinic's algorithm, we run a BFS to rebuild the levels after every round of augmenting paths. Is there a more efficient way?

The answer is the ISAP algorithm introduced below.

#### Process

As in Dinic's algorithm, we first run a BFS to split the vertices into levels. The small difference from Dinic is that we run the BFS on the reverse graph, from $t$ toward $s$.

After building the levels, we find augmenting paths with DFS.

Augmentation is similar to Dinic: we only augment to vertices whose level is $1$ less than the current vertex's.

Unlike Dinic, we do not rerun BFS to rebuild the levels. Instead, relabeling is done during augmentation.

Specifically, let the level of vertex $i$ be $d_i$. When we finish augmenting at vertex $i$, we go through all outgoing edges of $i$ in the residual network, find the neighbor $j$ with the smallest level, and then set $d_i \gets d_j+1$. In particular, if $i$ has no outgoing edges in the residual network, set $d_i \gets n$.

It is easy to see that when $d_s \geq n$, there is no augmenting path in the graph, and the algorithm can stop.

As in Dinic, ISAP also has the **current-arc optimization**.

ISAP has one more optimization. We record the number $num_i$ of vertices at level $i$. Whenever we update a vertex's level from $x$ to $y$, we also update the $num$ array. If $num_x=0$ after the update, a gap has appeared in the levels, so no more augmenting paths can be found, and we can stop the algorithm right away (in code, just set $d_s$ to $n$). This is called the **GAP optimization**.

#### Implementation

??? note "Reference code"
    ```cpp
    struct Edge {
      int from, to, cap, flow;
    
      Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
    };
    
    bool operator<(const Edge& a, const Edge& b) {
      return a.from < b.from || (a.from == b.from && a.to < b.to);
    }
    
    struct ISAP {
      int n, m, s, t;
      vector<Edge> edges;
      vector<int> G[MAXN];
      bool vis[MAXN];
      int d[MAXN];
      int cur[MAXN];
      int p[MAXN];
      int num[MAXN];
    
      void AddEdge(int from, int to, int cap) {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
      }
    
      bool BFS() {
        memset(vis, 0, sizeof(vis));
        queue<int> Q;
        Q.push(t);
        vis[t] = true;
        d[t] = 0;
        while (!Q.empty()) {
          int x = Q.front();
          Q.pop();
          for (int i = 0; i < G[x].size(); i++) {
            Edge& e = edges[G[x][i] ^ 1];
            if (!vis[e.from] && e.cap > e.flow) {
              vis[e.from] = true;
              d[e.from] = d[x] + 1;
              Q.push(e.from);
            }
          }
        }
        return vis[s];
      }
    
      void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++) G[i].clear();
        edges.clear();
      }
    
      int Augment() {
        int x = t, a = INF;
        while (x != s) {
          Edge& e = edges[p[x]];
          a = min(a, e.cap - e.flow);
          x = edges[p[x]].from;
        }
        x = t;
        while (x != s) {
          edges[p[x]].flow += a;
          edges[p[x] ^ 1].flow -= a;
          x = edges[p[x]].from;
        }
        return a;
      }
    
      int Maxflow(int s, int t) {
        this->s = s;
        this->t = t;
        int flow = 0;
        BFS();
        memset(num, 0, sizeof(num));
        for (int i = 0; i < n; i++) num[d[i]]++;
        int x = s;
        memset(cur, 0, sizeof(cur));
        while (d[s] < n) {
          if (x == t) {
            flow += Augment();
            x = s;
          }
          int ok = 0;
          for (int i = cur[x]; i < G[x].size(); i++) {
            Edge& e = edges[G[x][i]];
            if (e.cap > e.flow && d[x] == d[e.to] + 1) {
              ok = 1;
              p[e.to] = G[x][i];
              cur[x] = i;
              x = e.to;
              break;
            }
          }
          if (!ok) {
            int m = n - 1;
            for (int i = 0; i < G[x].size(); i++) {
              Edge& e = edges[G[x][i]];
              if (e.cap > e.flow) m = min(m, d[e.to]);
            }
            if (--num[d[x]] == 0) break;
            num[d[x] = m + 1]++;
            cur[x] = 0;
            if (x != s) x = edges[p[x]].from;
          }
        }
        return flow;
      }
    };
    ```

## Push-Relabel (preflow-push) algorithms

This approach ignores flow conservation while it runs, and updates the information of one vertex at a time to find the maximum flow.

### Generic push-relabel algorithm

First we introduce the main idea of push-relabel and a workable brute-force implementation.

Push-relabel finds the maximum flow by repeatedly updating single vertices until no vertex needs updating.

The flow function maintained by the algorithm does not have to satisfy flow conservation. For a vertex, we allow the flow entering it to exceed the flow leaving it. The surplus is called the **excess flow**  $e(u)$ of vertex $u(u\in V-\{s,t\})$:

$$
e(u)=\sum_{(x,u)\in E}f(x,u)-\sum_{(u,y)\in E}f(u,y)
$$

If $e(u)>0$, vertex $u$ is called **overflowing**[^note1]. Note that when we talk about overflowing vertices, $s$ and $t$ are not included.

Push-relabel maintains a height $h(u)$ for each vertex. An overflowing vertex $u$ may push its excess flow only to vertices lower than $u$. If $u$ has no adjacent vertex lower than it, we change the height of $u$ (relabel it).

#### Height function[^note2]

To be precise, push-relabel maintains a mapping $h:V\to \mathbf{N}$ such that:

-   $h(s)=|V|,h(t)=0$
-   $\forall (u,v)\in E_f,h(u)\leq h(v)+1$

$h$ is called a height function of the residual network $G_f=(V_f,E_f)$.

Lemma 1: Let $h$ be a height function on $G_f$. For any two vertices $u,v\in V$, if $h(u)>h(v)+1$, then $(u,v)$ is not an edge of $G_f$.

The algorithm only pushes along edges with $h(u)=h(v)+1$.

#### Push

When it applies: vertex $u$ is overflowing, and there is a vertex $v((u,v)\in E_f,c(u,v)-f(u,v)>0,h(u)=h(v)+1)$. Then the push operation applies to $(u,v)$.

We then push as much excess flow as possible from $u$ to $v$. During the push we only care about the minimum of the excess flow and $c(u,v)-f(u,v)$, not about whether $v$ overflows.

If $(u,v)$ is saturated after the push, remove it from the residual network.

#### Relabel

When it applies: if vertex $u$ is overflowing and $\forall (u,v)\in E_f,h(u)\leq h(v)$, the relabel operation applies to $u$.

Then just update $h(u)$ to $\min_{(u,v)\in E_f}h(v)+1$.

#### Initialization

$$
\forall (u,v)\in E,~~f(u,v)=\begin{cases}
c(u,v),&u=s\\
0,&u\neq s
\end{cases}
$$

$$
\forall u\in V,~~h(u)=\begin{cases}
|V|,&u=s\\
0,&u\neq s
\end{cases}
$$

$$
e(u)=\sum_{(x,u)\in E}f(x,u)-\sum_{(u,y)\in E}f(u,y)
$$

This fills every $(s,v)\in E$ with flow and raises $h(s)$, so that $(s,v)\notin E_f$, because $h(s)>h(v)$; and anyway $(s,v)$ is saturated, so there is no need to keep it in the residual network. It also initializes $e(s)$ to the negative of $\sum_{(s,v)\in E}f(s,v)$.

#### Process

Each time we scan the whole graph, and whenever some vertex $u$ meets the condition of push or relabel, we perform that operation.

In the figure, the middle of each vertex shows its index, the lower left shows its height $h(u)$, and the lower right shows its excess flow $e(u)$; the darkness of a vertex's color also shows its height. Edge weights show $c(u,v)-f(u,v)$, and green edges are edges $(u,v)$ with $h(u)=h(v)+1$ (that is, edges of the residual network $E_f$):

![p1](./images/2148.png)

Let's take a quick look at the whole run. Here the author uses a brute-force algorithm: scan for overflowing vertices, and update any that are found.

![p2](./images/2149.gif)

The final result

![p3](./images/2150.png)

We can see that in the end part of the excess flow returned to $s$, and no vertex other than the source and sink is overflowing. Now the flow function $f$ satisfies flow conservation and is a maximum flow, and its value is $e(t)$.

However, the paper[^ref1] points out that processing only overflowing vertices with height less than $n$ still gives the correct maximum flow value. But then, when the algorithm ends, the preflow does not yet satisfy the properties of a flow function, so we cannot know the real flow on each edge.

#### Implementation

???+ note "Core code"
    ```cpp
    constexpr int N = 1e4 + 4, M = 1e5 + 5, INF = 0x3f3f3f3f;
    int n, m, s, t, maxflow, tot;
    int ht[N], ex[N];
    
    void init() {  // initialization
      for (int i = h[s]; i; i = e[i].nex) {
        const int &v = e[i].t;
        ex[v] = e[i].v, ex[s] -= ex[v], e[i ^ 1].v = e[i].v, e[i].v = 0;
      }
      ht[s] = n;
    }
    
    bool push(int ed) {
      const int &u = e[ed ^ 1].t, &v = e[ed].t;
      int flow = min(ex[u], e[ed].v);
      ex[u] -= flow, ex[v] += flow, e[ed].v -= flow, e[ed ^ 1].v += flow;
      return ex[u];  // returns 1 if u is still overflowing
    }
    
    void relabel(int u) {
      ht[u] = INF;
      for (int i = h[u]; i; i = e[i].nex)
        if (e[i].v) ht[u] = min(ht[u], ht[e[i].t]);
      ++ht[u];
    }
    ```

### HLPP algorithm

The Highest Label Preflow Push algorithm is the generic push-relabel algorithm above where, each time a vertex is chosen, the overflowing vertex with the greatest height is chosen first. Its complexity is $O(n^2\sqrt m)$.

#### Process

Specifically, the HLPP algorithm works as follows:

1.  Initialize (as in the push-relabel algorithm);
2.  Pick the overflowing vertex $u$ with the greatest height, and push along all of its edges that allow a push;
3.  If $u$ is still overflowing, relabel it and go back to step 2;
4.  If no vertex is overflowing, the algorithm ends.

A paper[^ref2] that tested the practical performance of maximum flow algorithms showed that preflow-based algorithms actually spend a large share of their time on relabeling. Below we introduce two optimizations from a paper[^ref3] that greatly reduce the number of relabels.

#### BFS optimization

The upper bound of HLPP is $O(n^2\sqrt m)$, and it is fairly tight in practice; we can optimize the initialization of heights. Specifically, initialize $h(u)$ to the shortest distance from $u$ to $t$; in particular, $h(s)=n$.

While running the BFS, we also check the connectivity of the graph to rule out cases with no solution.

#### GAP optimization

HLPP pushes only when $h(u)=h(v)+1$. If at some moment there is some $k$ such that no vertex has $h(u)=k$, then vertices with $h(u)>k$ can never push excess flow to $t$ and can only send it back to $s$. So at that moment we directly raise their heights to at least $n+1$, so they push back to $s$ as soon as possible, which reduces the number of relabels.

The implementation below follows the method in the paper[^ref2]. It uses $N*2-1$ buckets `B`, where `B[i]` records all overflowing vertices whose current height is $i$. It includes the two optimizations above and only processes overflowing vertices with height less than $n$.

Note that the buckets in the paper[^ref2] are linked-list-based stacks, while the default container of `stack` in the STL is `deque`. Simple tests show that `vector`, `deque` and `list` make little difference in efficiency for this problem in practice.

#### Implementation

??? note "Luogu P4722 [Template] Maximum Flow, Enhanced Version / Push-Relabel"
    ```cpp
    #include <cstdio>
    #include <cstring>
    #include <queue>
    #include <stack>
    using namespace std;
    constexpr int N = 1200, M = 120000, INF = 0x3f3f3f3f;
    int n, m, s, t;
    
    struct qxx {
      int nex, t;
      long long v;
    };
    
    qxx e[M * 2 + 1];
    int h[N + 1], cnt = 1;
    
    void add_path(int f, int t, long long v) {
      e[++cnt] = qxx{h[f], t, v}, h[f] = cnt;
    }
    
    void add_flow(int f, int t, long long v) {
      add_path(f, t, v);
      add_path(t, f, 0);
    }
    
    int ht[N + 1];        // height;
    long long ex[N + 1];  // excess flow;
    int gap[N];           // gap optimization. gap[i] is the number of vertices with height i
    stack<int> B[N];      // bucket B[i] holds every v with ht[v]==i
    int level = 0;        // greatest height among overflowing vertices
    
    int push(int u) {      // push excess flow through every edge that allows it, as much as possible
      bool init = u == s;  // whether we are initializing
      for (int i = h[u]; i; i = e[i].nex) {
        const int &v = e[i].t;
        const long long &w = e[i].v;
        // during initialization, ignore the height-difference-of-1 rule
        if (!w || (init == false && ht[u] != ht[v] + 1) || ht[v] == INF) continue;
        long long k = init ? w : min(w, ex[u]);
        // take the min of residual capacity and excess flow; during initialization the source's excess may become negative.
        if (v != s && v != t && !ex[v]) B[ht[v]].push(v), level = max(level, ht[v]);
        ex[u] -= k, ex[v] += k, e[i].v -= k, e[i ^ 1].v += k;  // push
        if (!ex[u]) return 0;  // return once everything has been pushed
      }
      return 1;
    }
    
    void relabel(int u) {  // relabel (the height)
      ht[u] = INF;
      for (int i = h[u]; i; i = e[i].nex)
        if (e[i].v) ht[u] = min(ht[u], ht[e[i].t]);
      if (++ht[u] < n) {  // only handle vertices with height less than n
        B[ht[u]].push(u);
        level = max(level, ht[u]);
        ++gap[ht[u]];  // new height, update gap
      }
    }
    
    bool bfs_init() {
      memset(ht, 0x3f, sizeof(ht));
      queue<int> q;
      q.push(t), ht[t] = 0;
      while (q.size()) {  // reverse BFS; push unvisited vertices into the queue
        int u = q.front();
        q.pop();
        for (int i = h[u]; i; i = e[i].nex) {
          const int &v = e[i].t;
          if (e[i ^ 1].v && ht[v] > ht[u] + 1) ht[v] = ht[u] + 1, q.push(v);
        }
      }
      return ht[s] != INF;  // return 0 if the graph is not connected
    }
    
    // pick one of the vertices with the greatest current height; return 0 if no vertex overflows
    int select() {
      while (level > -1 && B[level].size() == 0) level--;
      return level == -1 ? 0 : B[level].top();
    }
    
    long long hlpp() {            // returns the maximum flow
      if (!bfs_init()) return 0;  // graph not connected
      memset(gap, 0, sizeof(gap));
      for (int i = 1; i <= n; i++)
        if (ht[i] != INF) gap[ht[i]]++;  // initialize gap
      ht[s] = n;
      push(s);  // initialize the preflow
      int u;
      while ((u = select())) {
        B[level].pop();
        if (push(u)) {  // still overflowing
          if (!--gap[ht[u]])
            for (int i = 1; i <= n; i++)
              if (i != s && ht[i] > ht[u] && ht[i] < n + 1)
                ht[i] = n + 1;  // vertices relabeled to n+1 here are not overflowing
          relabel(u);
        }
      }
      return ex[t];
    }
    
    int main() {
      scanf("%d%d%d%d", &n, &m, &s, &t);
      for (int i = 1, u, v, w; i <= m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        add_flow(u, v, w);
      }
      printf("%lld", hlpp());
      return 0;
    }
    ```

Watch how it runs

![HLPP](./images/1152.png)

Here, from pic13 to pic14, Relabel(4) is performed, along with the GAP optimization.

## Footnotes

[^ref_ek]: <http://pisces.ck.tp.edu.tw/~peng/index.php?action=showfile&file=f6cdf7ef750d7dc79c7d599b942acbaaee86a2e3e>

[^ref_dinic]: <https://people.orie.cornell.edu/dpw/orie633/LectureNotes/lecture9.pdf>

[^ref1]: Cherkassky B V, Goldberg A V. On implementing push-relabel method for the maximum flow problem\[C]//International Conference on Integer Programming and Combinatorial Optimization. Springer, Berlin, Heidelberg, 1995: 157-171.

[^ref2]: Ahuja R K, Kodialam M, Mishra A K, et al. Computational investigations of maximum flow algorithms\[J]. European Journal of Operational Research, 1997, 97(3): 509-542.

[^ref3]: Derigs U, Meier W. Implementing Goldberg's max-flow-algorithm—A computational investigation\[J]. Zeitschrift für Operations Research, 1989, 33(6): 383-403.

[^note1]: Usually called "active" in English literature.

[^note2]: In English literature, the height of a vertex is usually called its "distance label". The term "height" used here comes from the relevant chapter of *Introduction to Algorithms*. You can find the reason for this choice in the footnote on page 432 of the Chinese edition (China Machine Press, translation of the 3rd edition) of *Introduction to Algorithms*.
