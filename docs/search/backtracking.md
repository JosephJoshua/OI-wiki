This page gives a short introduction to the idea of backtracking and its uses.

## Introduction

Backtracking is a technique often used in [depth-first search (DFS)](./dfs.md) and [breadth-first search (BFS)](./bfs.md).

Its essence is: if a path is a dead end, turn back.

## Process

1.  Build the search space tree;

2.  Traverse it;

3.  When a boundary condition is hit, stop going deeper and search another branch instead;

4.  When the goal condition is reached, output the result.

## Example problems

???+ example "[USACO 1.5.4 Checker Challenge](https://www.luogu.com.cn/problem/P1219)"
    Below is a $6 \times 6$ checkers board. Six pieces are placed on the board so that every row, every column, and every diagonal (all diagonals, including the two main diagonals) contains at most one piece.
    
    ```plain
    0   1   2   3   4   5   6
      -------------------------
    1 |   | O |   |   |   |   |
      -------------------------
    2 |   |   |   | O |   |   |
      -------------------------
    3 |   |   |   |   |   | O |
      -------------------------
    4 | O |   |   |   |   |   |
      -------------------------
    5 |   |   | O |   |   |   |
      -------------------------
    6 |   |   |   |   | O |   |
      -------------------------
    ```
    
    The layout above can be described by the sequence $\{2,4,6,1,3,5\}$, where the $i$-th number means there is a piece in row $i$, column $a_i$, as follows:
    
    Row $i$: $\{1,2,3,4,5,6\}$
    
    Column $a_i$: $\{2,4,6,1,3,5\}$
    
    This is just one way to place the pieces. Write a program that finds all placements and outputs them in the sequence format above, in lexicographic order. You only need to output the first $3$ solutions, and on the last line output the total number of solutions. Note: you need to optimize your program so it stays efficient on larger boards.

??? note "Reference code"
    ```cpp
    --8<-- "docs/search/code/backtracking/backtracking_1.cpp"
    ```

???+ example "[Maze](https://www.luogu.com.cn/problem/P1605)"
    There is a maze of size $N \times M$ with $T$ obstacles, and obstacle cells cannot be entered. Given the start and end coordinates, and with each cell visited at most once, how many ways are there to go from the start to the end? In the maze you can move up, down, left or right, one cell at a time. The start is guaranteed not to be an obstacle.

??? note "Reference code"
    ```cpp
    --8<-- "docs/search/code/backtracking/backtracking_2.cpp"
    ```
