## Introduction

BFS (breadth-first search) is a basic algorithm in graph theory; see the [BFS (graph theory)](../graph/bfs.md) page for details. In **search algorithms**, BFS usually means a search that uses a queue to expand states level by level. It follows the same idea as BFS in graph theory and is especially good for **shortest path** or **fewest steps** problems.

## Explanation

The core idea of BFS is **expanding level by level**: starting from the start point, it scans reachable positions one level at a time. The path length when the target is first reached is the shortest path. This guarantees that the search is layered and optimal.

In practice, BFS starts from the start point and first visits every vertex directly reachable from it; these vertices form the first level of the search. Then it uses these vertices as new starting points and visits their neighbors in turn, forming the second level, and so on. It keeps expanding outward until it finds the target vertex or has visited every reachable vertex. During this process, the algorithm uses a queue and a visited array. It pushes the newly found vertices of each level (those not yet recorded in the visited array) into the queue in order, so vertices on the same level are processed in the order they were visited. This strictly follows the "expand level by level" logic.

BFS is very good at quickly finding the **shortest path** or **fewest steps**. When the algorithm first meets the target at some level, the path length (number of steps) so far must be the shortest. This is because the "expand level by level" mechanism ensures that every vertex is reached with the fewest possible steps: it is like searching outward from the start along the most direct routes until reaching the end, with no detours or extra steps. For this kind of problem, BFS is usually also more efficient than DFS.

However, BFS also has drawbacks compared with DFS. BFS usually needs more memory, has no natural backtracking process, and its depth-based pruning is less flexible than in DFS.

## Example problems

???+ example "Example problem [Luogu B3625 Maze Pathfinding](https://www.luogu.com.cn/problem/B3625)"
    In an $n \times m$ maze grid, `.` is a passable cell and `#` is an obstacle. Starting from $(1,1)$, you can move up, down, left or right each step. Can you reach the end $(n,m)$?

??? note "Solution"
    The implementation keeps a queue of coordinates waiting to be processed, together with a visited array to avoid repeated work. When a vertex expands to reachable vertices, it moves up, down, left and right; the four directions are $(x, y + 1)$, $(x, y - 1)$, $(x + 1, y)$, $(x - 1, y)$. The code uses a direction array for them. Be careful not to expand into cells with obstacles.

??? note "Reference implementation"
    ```cpp
    --8<-- "docs/search/code/bfs/bfs-1.cpp"
    ```

???+ example "Example problem [Luogu P1135 The Strange Elevator](https://www.luogu.com.cn/problem/P1135)"
    There are $n$ floors and one elevator. When the elevator is on floor $i$, it moves up or down by exactly a fixed number of floors $k_i$. If the target floor is invalid, that is, not between $1$ and $n$, that move cannot be made. What is the minimum number of elevator moves to get from floor $a$ to floor $b$? If it is impossible, output $-1$.

??? note "Solution"
    This problem asks for a shortest path, which is exactly what BFS is good at. In the implementation, the queue stores both the floor to be processed and the shortest distance from the start $a$ to that floor, and a visited array prevents the same element from being pushed twice. When vertex $i$ expands to reachable vertices, it goes to $i + k_i$ and $i - k_i$; be careful not to reach an invalid floor. When we reach a valid floor that has not been visited yet, we push it into the queue and record its shortest distance as the current floor's shortest distance plus one. When vertex $b$ is reached for the first time, its recorded shortest distance is the answer.
    
    In the code, we store a distance array directly and check whether a vertex is unvisited by whether its distance still has the default value (that is, $-1$).

??? note "Reference implementation"
    ```cpp
    --8<-- "docs/search/code/bfs/bfs-2.cpp"
    ```

## Exercises

-   [Luogu P1443 Knight's Traversal](https://www.luogu.com.cn/problem/P1443)
-   [Luogu P3956 \[NOIP 2017 Junior Group\] Chessboard](https://www.luogu.com.cn/problem/P3956)
-   [Luogu P1126 Robot Moving Heavy Objects](https://www.luogu.com.cn/problem/P1126)
