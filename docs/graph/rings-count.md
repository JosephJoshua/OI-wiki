## Counting simple cycles

???+ note "[Example problem 1: Codeforces Beta Round 11 D. A Simple Task](https://codeforces.com/problemset/problem/11/D)"
    Given a simple graph, count its simple cycles. A simple cycle is a cycle with no repeated vertices or edges.
    
    The number of vertices is $1\leq n\leq 19$.

??? note "Solution"
    Use bitmask DP. Let $f(s,i)$ be the number of paths that have visited exactly the vertex set $s$, are currently at vertex $i$, and whose first vertex is **the one with the smallest label** in $s$.
    
    For a state $f(s,i)$, enumerate the next vertex $u$. If $u$ is in $s$ and is the one with the smallest label (that is, the start), add $f(s,i)$ to the answer $A$. If $u$ is not in $s$, add $f(s,i)$ to $f(s\cup\{u\},u)$.
    
    This also counts cycles of length 2 (that is, single edges walked back and forth), and every longer cycle is counted twice (because from a fixed start you can go around in two directions). So the answer is $\dfrac{A-m}2$, where $m$ is the number of edges. The time complexity is $O(2^nm)$.

??? note "Sample code"
    ```cpp
    --8<-- "docs/graph/code/rings-count/rings-count_1.cpp"
    ```

## Counting triangles

A **triangle** (3-cycle) in a simple graph $G$ is an unordered triple $(u,\ v,\ w)$ such that there are edges $(u,\ v)$, $(v,\ w)$ and $(w,\ u)$. The **triangle counting problem** asks for the number of all triangles in the graph.

First, give every edge a direction. We direct each edge from the endpoint with smaller degree to the one with larger degree; if the degrees are equal, from the smaller label to the larger label. The resulting graph is a directed acyclic graph (DAG).

??? note "Proof that the graph has no cycles"
    By contradiction: suppose there is a cycle. Along the cycle, the degrees never decrease, so to close the cycle, all vertices must have the same degree. But then their labels must keep increasing along the cycle, which is impossible.
    
    So after orienting the edges, the graph has no cycle.
    
    In fact, the orientation rule above defines a [partial order](../math/order-theory.md#二元关系), so the graph built by this rule (which is the [Hasse diagram](../math/order-theory.md#偏序集的可视化表示hasse-图) of that partial order) must be a DAG.

Enumerate $u$ and each vertex $v$ that $u$ points to, then enumerate $w$ among the vertices that $v$ points to, and check whether $u$ is connected to $w$.

The time complexity of this algorithm is $O(m\sqrt m)$.

???+ note "Proof of the time complexity"
    Orienting the edges visits every edge once, which takes $O(n+m)$ time.
    
    For each pair $(v,\ w)$, the number of $u$ is at most the in-degree $d^-(v)$ of $v$.
    
    If $d^-(v)\leq\sqrt m$: since there are at most $n$ choices of $w$, this part takes $O(n\sqrt m)$ time.
    
    If $d^-(v) > \sqrt m$: since $v$ points to $w$, $d(v) \leq d(w)$, so $d(w) > \sqrt m$. But there are only $m$ edges in total, so there are at most $\sqrt m$ such $w$. So this part takes $O(m\sqrt m)$ time.
    
    The total time complexity is $O(n+m+n\sqrt m+m\sqrt m)=O(m\sqrt m)$.
    
    In fact, directing edges from larger degree to smaller degree also gives the correct complexity: just swap $u$ and $w$, and the proof above still works.

???+ note "Sample code ([Luogu P1989 Counting Triangles in an Undirected Graph](https://www.luogu.com.cn/problem/P1989))"
    ```cpp
    --8<-- "docs/graph/code/rings-count/rings-count_2.cpp"
    ```

### Example problem 2

???+ note "[HDU 6184 Counting Stars](https://acm.hdu.edu.cn/showproblem.php?pid=6184)"
    Given an undirected graph with $n$ vertices and $m$ edges, count how many times the shape below appears.
    
    ![](./images/rings-count1.svg)
    
    $2\leq n\leq 10^5$, $1\leq m\leq\min\left\{2\times 10^5,\ \dfrac{n(n-1)}2\right\}$.

??? note "Solution"
    This shape is two triangles sharing one edge. So we first run triangle counting and count how many triangles each edge belongs to. Then we enumerate the shared edge: if $x$ triangles contain it, it contributes $\dbinom x2$ to the answer.
    
    The time complexity is $O(m\sqrt m)$.

??? note "Sample code"
    ```cpp
    --8<-- "docs/graph/code/rings-count/rings-count_3.cpp"
    ```

## Counting 4-cycles

Similarly, a **4-cycle** is four vertices $a,\ b,\ c,\ d$ such that the edges $(a,\ b)$, $(b,\ c)$, $(c,\ d)$ and $(d,\ a)$ all exist.

First, sort the vertices: vertices with smaller degree come first, and those with larger degree come later.

Enumerate the vertex $a$ that comes last in this order. Then for each vertex $c$ ranked before $a$, we only need to count how many vertices $b$ ranked before $a$ have edges $(a,\ b)$ and $(b,\ c)$. Any two of these $b$ together form a 4-cycle. Counting the $b$ only needs one pass over $b$ and $c$.

Notice that this enumeration is essentially the same as enumerating triangles, so the time complexity is also $O(m\sqrt m)$ (assuming $n$ and $m$ are of the same order).

Note that $(a,\ b,\ c,\ d)$ and $(a,\ c,\ b,\ d)$ can be two different 4-cycles.

Also, vertices with the same degree must still get different ranks, and remember to check that $a\neq c$.

???+ note "Sample code ([LibreOJ P191 Counting 4-Cycles in an Undirected Graph](https://loj.ac/p/191))"
    ```cpp
    --8<-- "docs/graph/code/rings-count/rings-count_4.cpp"
    ```

### Example problem 3

???+ note "[Gym 102028L Connected Subgraphs](https://codeforces.com/gym/102028/problem/L)"
    Given an undirected graph with $n$ vertices and $m$ edges, count the sets of four edges whose induced subgraph is connected.
    
    $4\leq n\leq 10^5$, $4\leq m\leq 2\times 10^5$.

??? note "Solution"
    The cases split easily into five types: a star, a 4-cycle, a triangle with one extra edge hanging off one of its vertices, a path of four vertices with one extra edge hanging off a middle vertex, and a path of five vertices.
    
    For stars, just enumerate each vertex's degree and use binomial coefficients. 4-cycles can be counted directly with the algorithm above. For the triangle case, enumerate each triangle $(u,\ v,\ w)$; its contribution to the answer is $[d(u)-2]+[d(v)-2]+[d(w)-2]$.
    
    Now the fourth case. Enumerate a vertex $x$ of degree $2$ in the shape, then enumerate one of its neighbors $y$ as the vertex of degree $3$. The contribution is $[d(x)-1]\cdot\dbinom{d(y)-1}2$. But a neighbor of $y$ may coincide with the neighbor of $x$, and then the shape is really the third case. Each such wrongly counted third-case shape is counted twice (because it has two vertices of degree $3$), so we subtract twice the number of third-case shapes.
    
    For the last case, first enumerate the middle vertex $x$. It is easy to see that its contribution is
    
    $$
    \sum_{y\in son_x}\sum_{z\in son_x}[d(y)-1]\cdot[d(z)-1].
    $$
    
    Again, some shapes are counted wrongly here. Let the other neighbor of $y$ be $s$ and the other neighbor of $z$ be $t$. Thinking it through, the wrongly counted cases are:
    
    1.  $y$ coincides with $t$ but $s$ does not coincide with $z$: this is the third case;
    2.  $s$ coincides with $z$ but $y$ does not coincide with $t$: this is also the third case;
    3.  $y$ coincides with $t$ and $s$ coincides with $z$: this is a triangle;
    4.  $s$ coincides with $t$: this is a 4-cycle (the second case).
    
    In a third-case shape, taking each of the two vertices of degree $2$ as $x$ gives exactly the wrongly counted cases 1 and 2 above, so we subtract another two times the number of third-case shapes. For a triangle, each of its three vertices can be $x$, so it is counted $3$ extra times. Similarly, a 4-cycle is counted $4$ extra times.
    
    So we now have an algorithm for every case, with time complexity $O(n+m\sqrt m)$.

??? note "Sample code"
    ```cpp
    --8<-- "docs/graph/code/rings-count/rings-count_5.cpp"
    ```

## Exercises

[Luogu P3547 \[POI2013\] CEN-Price List](https://www.luogu.com.cn/problem/P3547)

[CodeForces 985G Team Players](https://codeforces.com/contest/985/problem/G) (inclusion–exclusion principle)
