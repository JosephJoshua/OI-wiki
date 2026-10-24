## Definition

Iterative deepening is a depth-first search that **limits the search depth on each run**.

## Explanation

Iterative deepening search is still depth-first search at heart. The only difference is that the search carries a depth $d$, and returns when $d$ reaches a preset limit. It is usually used to find an optimal solution. If one run finds no valid solution, we increase the depth limit by one and start again from the root.

If the goal is the optimal solution, why not use BFS? BFS is built on a queue, and a queue can take a lot of space. When there are many states, or each state is large, a queue-based BFS is at a disadvantage. In fact, iterative deepening is like a BFS implemented with DFS, and it uses relatively little space.

When the search tree has many branches, the cost of searching grows exponentially with each extra level. The work repeated in earlier runs is then almost negligible. This is why iterative deepening can be seen as an approximation of BFS.

## Process

First set a small depth limit as a global variable and run DFS. Each time we enter the DFS, we increase the current depth by one, and return when $d$ is greater than the limit $\textit{limit}$. If we find an answer during the search, we can backtrack, recording the path along the way. If no answer is found, we go back to the function entry, increase the depth limit, and search again.

???+ note "Implementation (pseudocode)"
    ```text
    IDDFS(u,d)
        if d>limit
            return
        else
            for each edge (u,v)
                IDDFS(v,d+1)
    return
    ```

## Notes

In most problems, breadth-first search is more convenient, and it is easy to detect duplicate states. When BFS uses too much space and the problem asks for an optimal solution, you should consider iterative deepening.
