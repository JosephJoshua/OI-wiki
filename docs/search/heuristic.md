This page gives a short introduction to heuristic search and how to use it.

## Definition

Heuristic search is a search algorithm that adds a heuristic function on top of an ordinary search algorithm.

The heuristic function uses the information we already have to estimate the value of each branch choice in the search, and then picks branches based on that estimate. Simply put, heuristic search analyzes both "take" and "don't take", and keeps the better option or removes invalid ones.

## Example problem

The idea is quite abstract, so we explain it with an example problem.

???+ note "[NOIP 2005 Junior Group — Herb Picking](https://www.luogu.com.cn/problem/P1048)"
    Summary: there are $N$ items and a knapsack of capacity $W$. Each item has a weight $w_i$ and a value $v_i$. Choose some items (each item can be chosen at most once) to put into the knapsack so that the total value is as large as possible and the total weight does not exceed the capacity.

??? note "Solution idea"
    We write an evaluation function $f$ that can cut off all useless $0$ branches (that is, prune the many useless "don't take" branches).
    
    The evaluation function $f$ works like this:
    
    When we take an item, we check whether it exceeds the allowed volume (feasibility pruning). When we don't take an item, we check whether the total value of all remaining herbs plus the current value is greater than the best solution found so far (optimality pruning).

??? note "Sample code"
    ```cpp
    --8<-- "docs/search/code/heuristic/heuristic_1.cpp"
    ```
