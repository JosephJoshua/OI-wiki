This page gives a short introduction to the concept, implementation and applications of Eulerian graphs.

## Definition

This article only discusses finite graphs.

In graph theory, an **Eulerian path** is a path that uses every edge of the graph exactly once, and an **Eulerian circuit** is a circuit that uses every edge of the graph exactly once.
A graph that has an Eulerian circuit is called an **Eulerian graph**. A graph that has no Eulerian circuit but has an Eulerian path is called a **semi-Eulerian graph**.

??? warning "Warning"
    Although the definition uses the word "path", strictly speaking the concept here should be a "trail". An Eulerian path or circuit must use each edge exactly once, but there is no restriction on how vertices are visited.

## Properties

Below we assume the graph $G$ under discussion has no isolated vertices. This loses no generality: if $G$ has isolated vertices, the properties below still hold for the graph $G'$ obtained by deleting them.

For a connected graph $G$, the following three properties are equivalent:

1.  $G$ is Eulerian;
2.  Every vertex of $G$ has even degree (for directed graphs, every vertex has in-degree equal to out-degree);
3.  $G$ can be decomposed into a union of edge-disjoint circuits.

Below we prove the equivalence.

If a graph $G$ is Eulerian, then every vertex of $G$ has even degree: start from any vertex and walk once around the Eulerian circuit. The degree of each vertex $v$ equals the number of times we leave $v$ plus the number of times we arrive at $v$. Since the walk is a circuit, for every vertex $v$ the number of times we leave it equals the number of times we arrive at it. In other words, every degree has the form $2k$, which is even.
In particular, for directed graphs, the same argument shows that every vertex has in-degree equal to out-degree.

If every vertex of a graph $G$ has even degree (or equal in-degree and out-degree), then $G$ can be decomposed into a disjoint union of edge-disjoint circuits: start from any vertex $u$, pick any outgoing edge $(u, v)$, move to the neighbor $v$ and delete $(u, v)$, and repeat until we return to the starting vertex $u$. We can show that the process must eventually return to $u$: whenever we arrive at a new vertex $v \neq u$, by the previous property the remaining degree of that vertex is odd, so there must be an outgoing edge, and the process does not stop at $v$. (In other words, the process stops if and only if it returns to $u$.) Since $G$ has finitely many edges, the process must stop after finitely many steps, so it must return to $u$ and give a circuit. Note that the proof above only uses the fact that all degrees are even, and after finding and deleting one circuit the rest of the graph still has this property. So we can repeat the process until the remaining graph is empty, which splits $G$ into edge-disjoint circuits.
Going further, each circuit can be split at the vertices it visits more than once into a disjoint union of simple cycles, so the simple circuits in the property above can also be replaced by simple cycles.

If a connected graph $G$ can be decomposed into a disjoint union of edge-disjoint circuits, then $G$ is Eulerian: given a set of edge-disjoint circuits, repeatedly pick two circuits that share a vertex and merge them into one, until no two circuits share a vertex.
We can show that only one circuit remains when this process ends. For any two edge-disjoint circuits $P_1, P_2$: if $P_1$ and $P_2$ share a vertex, they can be merged directly at that vertex. Otherwise, take any vertex $v_1$ on $P_1$ and any vertex $v_2$ on $P_2$. Since $G$ is connected, there is a path $e_1, e_2, \ldots, e_k$ connecting $v_1$ and $v_2$. Each edge $e_i$ is contained in some circuit $C_i$, and $P_1$ and $C_1$, $C_i$ and $C_{i+1}$, and $C_k$ and $P_2$ all share a vertex (or $C_i = C_{i+1}$, which does not affect the proof). In this case, $P_1$ and $P_2$ can be merged through $C_1, \ldots, C_k$. That is, any two circuits can be merged, so the final circuit is unique, and its edge set is the union of all the edge-disjoint circuits, namely $E(G)$. This circuit is an Eulerian circuit of $G$, so $G$ is Eulerian.

These properties also give a test for Eulerian graphs. Specifically, a graph is Eulerian if and only if all vertices with nonzero degree are mutually (strongly) connected and every vertex has even degree (or equal in-degree and out-degree).

Semi-Eulerian graphs have similar properties: a semi-Eulerian graph has exactly two vertices of odd degree, and these two vertices are the two ends of the Eulerian path. Connecting these two vertices turns a semi-Eulerian graph into an Eulerian graph. Deleting any one edge of an Eulerian graph gives a semi-Eulerian graph.
This gives a test for semi-Eulerian graphs: a graph is semi-Eulerian if and only if all vertices with nonzero degree are mutually (strongly) connected and there are exactly two vertices of odd degree. For directed graphs, the second condition becomes: there are exactly two vertices $u, v$ with $\deg^+(u) - \deg^-(u) = 1, \deg^+(v) - \deg^-(v) = -1$, and every other vertex has in-degree equal to out-degree.

## Constructing an Eulerian circuit/path

Here we introduce the most commonly used algorithm, Hierholzer's algorithm. Its core idea is the third property above: an Eulerian graph can be split into a union of edge-disjoint circuits.
Notice that the proof above already describes a complete, workable way to merge edge-disjoint circuits into an Eulerian circuit, and it is not hard to implement with a suitable data structure (for example, storing cycles in a linked-list-like structure).

The algorithm works as follows. First find a circuit in the graph and call it the current circuit. Each time, pick a vertex on the current circuit that still has nonzero remaining degree, find a new simple circuit starting from it, and merge that simple circuit into the current circuit. Repeat until no vertex on the current circuit has remaining degree. The current circuit is then an Eulerian circuit.

The algorithm also works for directed graphs. For a semi-Eulerian graph, first find a path connecting the two odd-degree vertices and call it the current path. Each time, pick a vertex with nonzero degree, find a simple circuit and merge it into the current path. In the end we get an Eulerian path.

### Implementation

The pseudocode of Hierholzer's algorithm is as follows:

$$
\begin{array}{ll}
1 &  \textbf{Input. } \text{The edges of the graph } e , \text{ where each element in } e \text{ is } (u, v) \\
2 &  \textbf{Output. } \text{The vertex of the Euler Road of the input graph}.\\
3 &  \textbf{Method. } \\
4 &  \textbf{Function } \text{Hierholzer } (v) \\
5 &  \qquad circle \gets \text{Find a Circle in } e \text{ Begin with } v \\
6 &  \qquad \textbf{if } circle=\varnothing \\
7 &  \qquad\qquad \textbf{return } v \\
8 &  \qquad e \gets e-circle \\
9 &  \qquad \textbf{for} \text{ each } v \in circle \\
10&  \qquad\qquad v \gets \text{Hierholzer}(v) \\
11&  \qquad \textbf{return } circle \\
12&  \textbf{Endfunction}\\
13&  \textbf{return } \text{Hierholzer}(\text{any vertex})
\end{array}
$$

### Time complexity

The time complexity of Hierholzer's algorithm is $O(|E| + |V|)$.

Note that, as in the correctness argument above, finding a simple circuit (or the initial path of a semi-Eulerian graph) in an Eulerian or semi-Eulerian graph **needs no backtracking**: just keep walking along the remaining edges and you will always find the circuit or path you need, and **each edge is visited only once**.
To make use of this, the implementation should store the edges in a linked-list-like way, such as adjacency lists or a linked forward star (chained adjacency list), so that each edge can be deleted right after it is visited. With a plain adjacency matrix, each edge lookup costs $O(|V|)$, and the total complexity becomes $O(|V||E|)$.

???+ note "Note"
    In fact, the exact complexity of this algorithm is $O(|E|)$ rather than $O(|V| + |E|)$, because the algorithm can be implemented in a way that depends on edges instead of vertices, by keeping one global linked list of remaining edges to find the next circuit.

If you need the lexicographically smallest Eulerian path or circuit, you have to sort the edges. The time complexity is then $\Theta(|E|\log |E|)$, or $\Theta(|E|)$ with counting sort or radix sort.

### Applications

Directed Eulerian graphs can be used in computer decoding.

Suppose we have $m$ letters and want to build a disk with $m^n$ sectors, each holding one letter, so that every $n$ consecutive positions on the disk form a string of length $n$. After one full turn ($m^n$ steps) we get all $m^n$ distinct strings of length $n$ over the $m$ letters.

![](images/euler1.svg)

Build the following directed Eulerian graph:

Let $S = \{a_1, a_2, \cdots, a_m\}$, and build $D=\langle V, E\rangle$ as follows:

$V = \{a_{i_1}a_{i_2}\cdots a_{i_{n-1}} |a_i \in S, 1 \leq i \leq n - 1 \}$

$E = \{a_{j_1}a_{j_2}\cdots a_{j_{n-1}}|a_j \in S, 1 \leq j \leq n\}$

The incidence between the vertices and edges of $D$ is defined as follows:

Vertex $a_{i_1}a_{i_2}\cdots a_{i_{n-1}}$ has $m$ outgoing edges: $a_{i_1}a_{i_2}\cdots a_{i_{n-1}}a_r, r=1, 2, \cdots, m$.

Edge $a_{j_1}a_{j_2}\cdots a_{j_{n-1}}$ goes into vertex $a_{j_2}a_{j_3}\cdots a_{j_{n}}$.

![](images/euler2.svg)

This $D$ is connected, and every vertex has in-degree equal to out-degree (both equal to $m$), so $D$ is a directed Eulerian graph.

Find any Eulerian circuit $C$ in $D$, take the last letter of each edge in $C$, and place them around the disk in the order the edges appear in $C$.

## Example problems

???+ note "[Luogu P2731 Riding the Fences](https://www.luogu.com.cn/problem/P2731)"
    You are given an undirected graph with 500 vertices. Find an Eulerian path or Eulerian circuit of the graph. If there are several solutions, output the smallest one.
    
    In this problem, the Eulerian path or circuit does not need to visit every vertex.
    
    The number of edges m satisfies $1\leq m \leq 1024$.

??? note "Solution idea"
    This problem is a direct application of Hierholzer's algorithm.
    
    You can store the answer in a `std::stack<int>`, because if what we find is not a circuit, that part must be placed at the end.
    
    Note that you cannot store the graph in an adjacency matrix; otherwise the time complexity degrades to $\Theta(nm)$. Since the edges need to be sorted, we suggest storing the graph with a linked forward star or `std::vector`. The sample code uses `std::vector`.

??? note "Sample code"
    ```cpp
    --8<-- "docs/graph/code/euler/euler_1.cpp"
    ```

## Exercises

-   [SGU 101 Domino](https://codeforces.com/problemsets/acmsguru/problem/99999/101)

-   [POJ 1780 Code](http://poj.org/problem?id=1780)

-   [Luogu P1127 Word Chain](https://www.luogu.com.cn/problem/P1127)

-   [Luogu P1333 Ruirui's Sticks](https://www.luogu.com.cn/problem/P1333)

-   [Luogu P1341 Unordered Letter Pairs](https://www.luogu.com.cn/problem/P1341)

-   [Luogu P6066 \[USACO05JAN\]Watchcow S](https://www.luogu.com.cn/problem/P6066)

-   [Luogu P6628 \[Joint Provincial Selection 2020 Paper B\] Lilac Road](https://www.luogu.com.cn/problem/P6628)

-   [Luogu P3520 \[POI 2011\] SMI-Garbage](https://www.luogu.com.cn/problem/P3520)
