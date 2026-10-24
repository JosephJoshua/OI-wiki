Prerequisites: [Dijkstra's algorithm](./shortest-path.md#dijkstra-算法), [A\* algorithm](../search/astar.md), [persistent mergeable heaps](../ds/persistent-heap.md)

## Problem statement

Given a directed graph with $n$ nodes and $m$ edges, find the length of the $k$-th shortest path among all distinct paths from $s$ to $t$.

???+ info "On the word 'path'"
    The "paths" on this page may use the same edge or the same node more than once, so strictly speaking they should be called "[walks](./concept.md#路径)" rather than "paths". Strictly speaking, the problem discussed here is also the **$k$ shortest walk** problem. However, following common usage, this page still uses the word "path", and calls paths that do not intersect themselves "simple paths".

## A\* algorithm

The A\* algorithm is a search algorithm. For each current state $x$ it defines an evaluation function $f(x)=g(x)+h(x)$, where $g(x)$ is the actual cost to reach the current state from the initial state, and $h(x)$ is the estimated cost of the best path from the current state to the goal state. During the search, it always takes out the state $x$ with the best $f(x)$ and expands all of its successor states. A **priority queue** can be used to maintain these values.

For the $k$ shortest paths problem, let $h(x)$ be the length of the shortest path from the current node to the target node $t$. This value can be precomputed for every node by running a single-source shortest path from $t$ on the reversed graph. Each state needs two values: the node $x$ currently reached and the distance $g(x)$ already traveled; write such a state as $(x,g(x))$. At the start, push the initial state $(s,0)$ into the priority queue. Each time, take out the state with the smallest evaluation $f(x)=g(x)+h(x)$, go through all outgoing edges of its node $x$, and push the corresponding successor states into the priority queue. When a node is taken out of the queue for the $k$-th time, the $g(x)$ of that state is the length of the $k$-th shortest path from the start node $s$ to that node.

This search can be optimized. Since we only need the $k$-th shortest path from the start node to the target node, once a node has been taken out of the queue $k$ times, later states at that node do not need to expand their successors. These states cannot affect the final answer, because the first $k$ times this node was taken out already give $k$ valid paths to it, which are enough to build the first $k$ shortest paths to the target node.

Since each node is expanded at most $k$ times, each edge is pushed into the priority queue at most $k$ times, so the time complexity is $O(km\log km)$ and the space complexity is $O(km)$. Compared with plain search, the A\* algorithm prunes toward the target node $t$, but this only improves the constant, not the asymptotic complexity. Although the complexity of the algorithm in this section is not great, within the same complexity it can find the first $k$ shortest paths from the start node $s$ to every node (in the shortest path tree rooted at $t$).

### Implementation

??? example "Template problem [Library Checker - K-Shortest Walk](https://judge.yosupo.jp/problem/k_shortest_walk) reference implementation"
    ```cpp
    --8<-- "docs/graph/code/k-shortest-walk/k-shortest-walk-1.cpp"
    ```

## Approach with persistent mergeable heaps

The algorithm above actually finds the $k$ shortest paths to all nodes. If we only want the $k$ shortest paths to a given target node $t$, we can do better. This section gives an $O(m\log m+k\log k)$ approach based on persistent mergeable heaps.

### Shortest path tree and sidetrack edges

The bottleneck of the algorithm above is that the answer is only updated when the target node $t$ is reached. But different paths may differ very little. For example, the second shortest path may differ from the shortest path only by a detour through one extra node at one edge, with the rest of the path being the same; yet the algorithm above may need to search these same edges all over again to find the second shortest path. Since only the detour part matters, to get the $k$ shortest paths we only need to consider the $k$ cheapest ways of making detours. This leads to the concept of the shortest path tree.

Run a single-source shortest path from the target node $t$ on the reversed graph. Record, for each node $x$, the shortest distance $h(x)$ from $x$ to $t$, and the first edge $f_x$ on the shortest path starting from $x$; if there are several optimal choices, take the one recorded when Dijkstra's algorithm relaxed it. All these edges $f_x$ and their endpoints form a tree, and the simple path from every node $x$ in the tree to the root $t$ is a shortest path from $x$ to $t$. This is the **shortest path tree** $T$.

Once we have the shortest path tree $T$, we can compute how much extra distance each edge not in $T$ adds. For an edge $e=(u,v)\notin T$ with weight $w$, define a new edge, still from $u$ to $v$, with cost $\Delta(e)=w + h(v) - h(u)$. This page calls these edges with weight $\Delta(e)$ **sidetrack edges**, and $\Delta(e)$ the sidetrack cost. Since $h(u)\le w+h(v)$, the sidetrack cost is always non-negative. If an edge does not have both endpoints in the shortest path tree $T$, it cannot affect the $k$ shortest paths to $t$, and can be deleted.

The figure below shows a directed graph $G$ on the left, and on the right its shortest path tree $T$ (thick edges) and the corresponding sidetrack edges (thin edges):

![](./images/k-shortest-path-1.svg)

Let $P$ be the sequence of edges of a path from $s$ to $t$, and let $P'$ be $P$ with the edges of $T$ removed. Then, listing the edges of $P'$ in order, any two adjacent edges $e_1=(u_1,v_1)$ and $e_2=(u_2,v_2)$ must satisfy

-   Condition $(*)$: the start $u_2$ of the latter is an ancestor (possibly itself) of the end $v_1$ of the former in the shortest path tree $T$. For the first edge, we take "the end of the former" to be $s$.

This is because in the original path $P$, $v_1$ and $u_2$ are connected by some tree edges of $T$. Conversely, for any edge sequence $P'$ satisfying condition $(*)$, there is exactly one path $P$ in $G$ that corresponds to it, because the simple path between $v_1$ and $u_2$ in the shortest path tree $T$ is unique. This shows that paths $P$ in the original graph correspond one-to-one with sidetrack edge sequences $P'$ satisfying condition $(*)$. Moreover, the length of $P$ equals the shortest distance $h(s)$ plus the sum of these sidetrack costs:

$$
h(s)+\sum_{e\in P'}\Delta(e).
$$

This discussion shows that finding the $k$ shortest paths becomes finding the sidetrack edge sequence $P'$ with the $k$-th smallest cost that satisfies condition $(*)$.

To handle condition $(*)$, instead of searching for ancestors in the shortest path tree at each query, we can directly pass each node's set of sidetrack edges down to its descendants in the shortest path tree. This is the same as building the graph $G'$ below:

![](./images/k-shortest-path-2.svg)

In this graph, condition $(*)$ becomes the requirement that the edges of $P'$ are joined end to end, that is, $P'$ is a path in $G'$. The problem further becomes finding the $k$-th shortest path in this graph that starts at $s$ and **ends at any node**. Compared with the original $k$ shortest paths problem, the path no longer has to end at the target node $t$.

The transformed problem is easy to solve. Start directly from the start node $s$ and expand paths in increasing order of length with a priority queue (the same node may be taken out several times). Each time a node is taken out of the priority queue, we have found a path in $G'$, which corresponds to a path in $G$ that reaches the target node $t$.

### Optimization with persistent mergeable heaps

The idea of the algorithm is now clear. But a naive implementation is too slow. In $G'$, a single node may have $\Theta(m)$ edges, so each expansion may need to push a set of $\Theta(m)$ edges into the priority queue. In fact, there is no need to push all edges into the priority queue: in many cases, only the shortest of the pushed edges can ever be popped later. That is, we can push the whole edge set of a node into the priority queue as one unit, as long as we can quickly access the shortest edge in the set.

This suggests using a min-heap to store the edge set of each node. The priority queue then only stores these heaps, and the cost of each heap is the path cost of the edge at its top. Each time we pop the front of the queue, we also pop the top edge from that heap. Then we push the heap (with its top removed) back into the priority queue, and also push the heap of the sidetrack edge set at the end node of the popped top edge.

Storing edge sets in heaps also solves the problem of passing edge sets down the shortest path tree. Passing an edge set down means merging the current node's edge set into its children, so the heap must support merging; and while merging into the children, the edge set at the current node must not be destroyed, so the heap must also be persistent. This is exactly a persistent mergeable heap.

This gives the complete algorithm:

1.  Run a single-source shortest path from the target node $t$ to get the shortest path tree.
2.  For each node of the shortest path tree, build its set of sidetrack edges and store it in a persistent mergeable heap.
3.  Going along the edges of the shortest path tree from the target node $t$ downward (for example in BFS order), merge the heap at each node into the heaps of its children.
4.  Record the shortest distance $h(s)$ as the first answer, then start from the start node $s$ and push its heap into the priority queue.
5.  Pop the heap at the front of the queue and record an answer. Then push the heap with its top removed back into the priority queue, and push the heap at the end node of the top edge into the priority queue.

Persistent mergeable heaps are usually implemented with leftist heaps or randomized heaps. In that case, the last step can be optimized further. The internal structure of these heaps is a binary tree. After popping the top, we would normally merge the left and right children and push the merged heap into the priority queue; but in this algorithm we can skip the merge and push the heaps of the two children into the priority queue separately. This saves the $O(\log m)$ cost of one merge. Since each pop of the front heap pushes at most three new heaps into the priority queue, the size of the priority queue is $O(k)$. So the time per query drops to $O(\log k)$, and the total query complexity is $O(k\log k)$.

Building the shortest path tree and building the persistent mergeable heaps both take $O(m\log m)$ time, so the total time complexity of the algorithm is $O(m\log m+k\log k)$.

### Implementation

??? example "Template problem [Library Checker - K-Shortest Walk](https://judge.yosupo.jp/problem/k_shortest_walk) reference implementation"
    ```cpp
    --8<-- "docs/graph/code/k-shortest-walk/k-shortest-walk-2.cpp"
    ```

## Exercises

-   ["SDOI2010" Magic Pig Academy](https://www.luogu.com.cn/problem/P2483)

## References and notes

-   [\[Tutorial\] k shortest paths and Eppstein's algorithm by meooow - Codeforces](https://codeforces.com/blog/entry/102085)
