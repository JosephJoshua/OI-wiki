This article introduces the A\* search algorithm.

The A\* search algorithm (A\* is read "A-star"), or A\* for short, is an algorithm that finds the shortest path between a given start and end on a weighted directed graph. It is a graph traversal algorithm and a best-first search algorithm, and it is also an improvement on [BFS](./bfs.md).

## Process

The goal of A\* is to find the shortest path from a start $s$ to an end $t$ on a directed graph. Let $d(x,y)$ be the distance between vertices $x$ and $y$, that is, the length of the shortest path between them. Let $g(x)=d(s,x)$ be the distance from the start $s$ to vertex $x$, let $h^*(x)$ be the distance from vertex $x$ to the end $t$, and let $h(x)$ be an estimate of $h^*(x)$[^note1]. Finally, the estimated length of the shortest path from $s$ through $x$ to $t$ is

$$
f(x) = g(x) + h(x).
$$

During the search, A\* repeatedly takes the vertex with the smallest $f$ out of a priority queue. It then pushes all of that vertex's successors $x$ into the priority queue, updating $f(x)$ using the actually recorded $g(x)$ and the estimated $h(x)$.

## Properties

The actual value of $h^*(x)$ is unknown during the search, so we use an easy-to-compute $h(x)$ as its estimate. The real cost of A\* search depends on the properties of this estimate function $h(x)$. It is easy to see that if $h\equiv h^*$, meaning the estimate is exact, the search moves strictly along the shortest path. If $h\equiv 0$, A\* reduces to [Dijkstra's algorithm](./../graph/shortest-path.md#dijkstra-算法); and when $h\equiv 0$ and every edge weight is $1$, it is just [BFS](./bfs.md).

Assume the graph has no negative-weight edges. If the estimate $h(x)$ never exceeds the real distance $h^*(x)$, that is, $0\le h\le h^*$, then A\* is guaranteed to find the optimal solution. An estimate function $h(x)$ that satisfies this condition is called **admissible**. From the discussion above, the closer $h$ is to $h^*$, the more efficient A\* is. In general, in the worst case the algorithm visits every vertex satisfying

$$
f(x) = g(x) + h(x) \le C^*
$$

where $C^*$ is the shortest distance between the start $s$ and the end $t$. Intuitively, the closer $h$ is to $h^*$, the fewer successors satisfy this condition at each expansion, so the algorithm explores fewer branches. So A\* can be seen as a kind of "pruning" optimization of search.

If $h$ is not only admissible but also **consistent**, that is,

$$
h(x) \le h(y) + d(x, y),
$$

then A\* never pushes a vertex that has already been popped from the queue back into it. The consistency condition can be understood as the triangle inequality among vertices $x,y,t$.

## Example problem

A classic application of A\* is the k-th shortest path problem. For the problem statement, the A\* solution, and a faster solution using persistent mergeable heaps, see the [k-th shortest path](./../graph/kth-path.md) page.

This section presents a classic problem that can be solved with A\*.

???+ example "[8-Puzzle](https://www.luogu.com.cn/problem/P1379)"
    On a $3\times 3$ board there are eight pieces, each labeled with a number from $1$ to $8$. One cell of the board is empty, shown as $0$. A piece next to the empty cell can move into it, and its old position then becomes empty. Given a starting layout and a target layout (to keep the problem simple, the target state is fixed as shown below), find a way to move from the starting layout to the target layout in the fewest steps.
    
    $$
    \begin{aligned}
    123\\
    804\\
    765
    \end{aligned}
    $$

??? note "Solution idea"
    We can define the $h$ function as the number of pieces that are not in their correct positions. It is easy to see that $h$ is both admissible and consistent. So this problem can be solved with A\*.

??? note "Reference code"
    ```cpp
    --8<-- "docs/search/code/astar/astar_1.cpp"
    ```

## References and notes

-   [A\* search algorithm - Wikipedia](https://en.wikipedia.org/wiki/A*_search_algorithm)

[^note1]: Here $h$ stands for heuristic. See [Heuristic search - Wikipedia (Chinese)](https://zh.wikipedia.org/wiki/%E5%90%AF%E5%8F%91%E5%BC%8F%E6%90%9C%E7%B4%A2) and the Bounded relaxation section of [A\* search algorithm - Wikipedia](https://en.wikipedia.org/wiki/A*_search_algorithm#Bounded_relaxation).
