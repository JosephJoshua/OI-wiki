author: FFjet, ChungZH, frank-xjh, hsfzLZH1, Xarfa, AndrewWayne, hcx1204

This page gives a short introduction to two bidirectional search algorithms: "simultaneous bidirectional search" and "meet in the middle".

## Simultaneous bidirectional search

### Definition

The basic idea of simultaneous bidirectional search is to start a [BFS](./bfs.md) or [DFS](./dfs.md) from both the start and the end of the state graph at the same time.

If the two searches meet, we can consider a feasible solution found.

### Process

Steps of bidirectional BFS:

```text
push the start node and the target node into queue q
mark the start node as 1
mark the target node as 2
while (queue q is not empty)
{
  expand s new nodes from q.front()
  
  if a newly expanded node is already marked with the other number
    then the two ends of the search have met
    then end the loop
  
  if the s new nodes were expanded from the start node
    then mark these s nodes as 1 and push them into q 
  
  if the s new nodes were expanded from the target node
    then mark these s nodes as 2 and push them into q
}
```

### Example problem

???+ note "Example problem [8-Puzzle](https://www.luogu.com.cn/problem/P1379)"
    On a $3\times 3$ board there are eight pieces, each labeled with a number from $1$ to $8$. One cell of the board is empty, shown as $0$. A piece next to the empty cell can move into it. The task: given a starting layout (initial state) and a target layout (to keep the problem simple, the target state is fixed as $123804765$), find a way to transform the starting layout into the target layout in the fewest moves.

??? note "Solution idea"
    A brute-force BFS is easy to come up with, and brute-force BFS will not even time out on this problem. Here, though, we use it as an example of simultaneous bidirectional search. We can run two BFS searches: one forward from the start state, and one backward from the end state. By alternating between the two, the search trees become much smaller. As soon as one BFS reaches a state that the other BFS has already reached, we have the answer.

??? note "Reference code"
    ```cpp
    --8<-- "docs/search/code/bidirectional/bidirectional_1.cpp"
    ```

## Meet in the middle

???+ warning "Warning"
    This section is not about [**binary search**](../basic/binary.md) (one Chinese name for binary search, "half search", is the same as a common Chinese name for meet in the middle).

### Introduction

Meet in the middle has no official Chinese name; it is commonly translated as "half search", "bidirectional search", or "meeting halfway".

It suits cases where the input is small, but not small enough for brute-force search to work directly.

### Process

The main idea of meet in the middle is to split the whole search into two halves, search each half separately, and finally combine the results of the two halves.

### Properties

The complexity of brute-force search is often exponential. With meet in the middle, the exponent can be halved, bringing the complexity down from $O(a^b)$ to $O(a^{b/2})$.

### Example problem

???+ note "Example problem [USACO09NOV Lights](https://www.luogu.com.cn/problem/P2962)"
    There are $n$ lights. Each light is connected to some other lights, and each light has a switch. Pressing a light's switch toggles the state of that light and of every light connected to it. At the start all lights are off. You need to turn all lights on. Find the minimum number of switch presses.
    
    $1\le n\le 35$.

??? note "Solution idea"
    If we use brute-force DFS over the switch states, the time complexity is $O(2^{n})$, which clearly times out. But with meet in the middle, the time complexity can be reduced to $O(n2^{n/2})$. Meet in the middle means we first find the states for one half: the states reachable using only switches $1$ to $\mathrm{mid}$. Then we find the states reachable using only the other half of the switches. If the lights turned on by the first half and by the second half complement each other, combining the two gives a way to turn on all lights. In the implementation, we can store the states of the first half, along with the minimum number of presses to reach each state, in a map. When searching the second half, every time we find a result, we combine it with the complementary first-half result to update the answer.

??? note "Reference code"
    ```cpp
    --8<-- "docs/search/code/bidirectional/bidirectional_2.cpp"
    ```

## External links

-   [What is meet in the middle algorithm w.r.t. competitive programming? - Quora](https://www.quora.com/What-is-meet-in-the-middle-algorithm-w-r-t-competitive-programming)
-   [Meet in the Middle Algorithm - YouTube](https://www.youtube.com/watch?v=57SUNQL4JFA)
