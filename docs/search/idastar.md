Prerequisites: [A\* algorithm](./astar.md), [iterative deepening search](./iterative.md)

This page gives a short introduction to the IDA\* algorithm. IDA\* is the A\* algorithm combined with iterative deepening.

## Process

IDA\* is a variant of iterative deepening search. Iterative deepening search limits the search depth in each DFS run, while IDA\* limits the path cost in each DFS run.

In one iteration, the algorithm runs a DFS from the start $s$. It records the actual cost $g(x)$ of reaching the current vertex $x$, and prunes using $h(x)$, an estimate of the minimum cost from $x$ to the end. If the estimated total cost of reaching the end along the current path,

$$
f(x) = g(x) + h(x)
$$

exceeds the threshold $C$, the search of this branch stops.

The threshold $C$ is updated dynamically between iterations. The initial threshold is the estimated total cost at the start, $h(s)$. Within an iteration, every time the search stops because the threshold is exceeded, we record the minimum estimated total cost among all successors not yet visited. After the iteration ends, the threshold is updated to this minimum, and the next round of search begins.

## Properties

Since IDA\* uses the same pruning strategy as A\*, the discussion of A\*'s properties also applies to IDA\*.

Compared with A\*, IDA\* has the following advantages:

-   No need to detect duplicate states and no need for sorting, which makes depth-based pruning easy.
-   Lower space usage. Each iteration is a depth-first search with a limit on the path cost, and using DFS reduces memory consumption.

It also has a drawback:

-   Repeated search. Even if two consecutive searches differ only slightly, every time the limit is relaxed, the search starts again from scratch.

## Implementation

Let $h$ be a suitable evaluation function and $s$ the start of the search. The full algorithm looks roughly like this:

$$
\begin{array}{l}
\textbf{Algorithm. }\textrm{IdaStar}():\\
\textbf{Output. }\text{The shortest path, }\textit{path}\text{, and its cost, }C\text{, if a path exists,}\\
\quad \text{and }\textrm{NOT}\_\textrm{FOUND}\text{, otherwise.}\\
\textbf{Method.}\\
\begin{array}{ll}
1  & C \gets h(s) \\
2  & path \gets [s] \\
3  & \textbf{while }\text{true}\\
4  & \quad t \gets \textrm{Search}(\textit{path},0,C)\\
5  & \quad \textbf{if } t=\text{FOUND}\textbf{ then return }(\textit{path},C) \\
6  & \quad \textbf{if } t=\infty\textbf{ then return }\textrm{NOT}\_\textrm{FOUND} \\
7  & \quad C \gets t
\end{array}\\
\\
\textbf{Sub-Algorithm. }\textrm{Search}(\textit{path},g,C):\\
\textbf{Input. }\text{The current path, }\textit{path}\text{, its cost, }g\text{, and search limit }C.\\
\textbf{Output. }\text{FOUND, if the target node has been reached; }\infty\text{, if all}\\
\quad \text{reachable nodes have been explored; otherwise, the minimum}\\
\quad \text{total cost, }t\text{, among nodes not yet explored.}\\
\textbf{Method.}\\
\begin{array}{ll}
1  & \textit{node} \gets \text{the last element in }\textit{path}\\
2  & f \gets g + h(\textit{node}) \\
3  & \textbf{if } f > C \textbf{ then return } f \\
4  & \textbf{if }\textit{node}\text{ is the target }\textbf{then return }\text{FOUND}\\
5  & \textit{min} \gets \infty \\
6  & \textbf{for }\text{each }\textit{child}\text{ of }\textit{node }\textbf{do}\\
7  & \quad \textbf{if }\textit{child}\text{ not in }\textit{path}\textbf{ then}\\
8  & \quad \quad \text{append }\textit{child}\text{ to }\textit{path}\\
9  & \quad \quad t \gets \text{Search}(\textit{path}, g + \text{Cost}(\textit{node},\textit{child}), C)\\
10 & \quad \quad \textbf{if }t = \text{FOUND}\textbf{ then return }\text{FOUND}\\
11 & \quad \quad \textbf{if }t < \textit{min}\textbf{ then }\textit{min}\gets t\\
12 & \quad \quad \text{remove the last element of }\textit{path}\\
13 & \textbf{return }\textit{min}
\end{array}
\end{array}
$$

## Example problem

???+ example "[Egyptian Fractions](https://www.luogu.com.cn/problem/P1763)"
    In ancient Egypt, people wrote every rational number as a sum of distinct unit fractions (that is, $1/a$ with $a\in\mathbf{N}_+$). For example, $\dfrac{2}{3}=\dfrac{1}{2}+\dfrac{1}{6}$, but $\dfrac{2}{3}=\dfrac{1}{3}+\dfrac{1}{3}$ is not allowed, because the same unit fraction cannot appear twice among the terms.
    
    A fraction $\dfrac{a}{b}$ can be written in many ways. The rules: among different ways of writing the same fraction, fewer terms is better than more terms; if the number of terms is the same, the larger the smallest fraction, the better. For example, $\dfrac{19}{45}=\dfrac{1}{5}+\dfrac{1}{6}+\dfrac{1}{18}$ is the best way.
    
    Given integers $a,b$ ($0<a<b<1000$), write a program to compute the best expression.

??? note "Solution idea"
    In theory this problem can be solved with backtracking, but the solution tree is "terrifying": not only is there no obvious upper bound on its depth, but in theory there are also infinitely many choices for each term. In other words, with breadth-first traversal you could not even finish expanding a single level, because every level is infinitely large.
    
    The fix is iterative deepening search: enumerate the depth limit $C$ from small to large, and in each search only consider vertices whose depth is at most $C$. This way, as long as the solution has finite depth, it will be found in finite time.
    
    The depth limit $C$ can also be used for pruning. Expand in increasing order of denominators. If at level $i$ the sum of the first $i$ fractions is $\dfrac{c}{d}$ and the $i$-th fraction is $\dfrac{1}{e}$, then we still need at least
    
    $$
    h = \left(\dfrac{a}{b}-\dfrac{c}{d}\right)/\left(\dfrac{1}{e+1}\right)
    $$
    
    more fractions for the sum to reach $\dfrac{a}{b}$. For example, if the search is currently at $\dfrac{19}{45}=\dfrac{1}{5}+\dfrac{1}{100}+\cdots$, then each later fraction is at most $\dfrac{1}{101}$, so at least $\left({\dfrac{19}{45}-\dfrac{1}{5}}\right)/\left({\dfrac{1}{101}}\right)=23$ terms are needed for the sum to reach $\dfrac{19}{45}$. Therefore the first $22$ iterations never consider this subtree at all. The key point is that we can estimate how many more steps are needed, at least, to reach a solution.
    
    Note that the word "at least" here means the estimate is "optimistic". As with A\*, a good estimate function must be "optimistic", meaning it must never overestimate the actual cost. Replacing the depth limit $g\le C$ of iterative deepening search with the stricter limit $g + h \le C$ gives the IDA\* algorithm discussed on this page. Because the path cost in this article is just its length, IDA\* is still limiting the path length, only with an added estimate of how many more steps are needed. In more general problems, other estimate functions can be designed depending on the cost being minimized.
    
    In the implementation, IDA\* is pruned further:
    
    1.  When expanding a vertex, the next denominator to consider is at least $\left(\dfrac{a}{b}-\dfrac{c}{d}\right)^{-1}$; we can use this to improve the starting point of the enumeration of $e$.
    2.  The IDA\* path cost limit can be rewritten as
    
        $$
        e \le \left(\dfrac{a}{b}-\dfrac{c}{d}\right)^{-1}(C-g) - 1.
        $$
    
        So there is no need to enumerate all later denominators and check each one; we only need to enumerate up to this upper bound.
    3.  When the search reaches the last two fractions, we check feasibility directly with a quadratic equation instead of searching further. Specifically, to find $e<x<y\le E_\text{max}$ such that
    
        $$
        \dfrac{1}{x} + \dfrac{1}{y} = \dfrac{p}{q} := \dfrac{a}{b}-\dfrac{c}{d},
        $$
    
        we only need to solve the system of equations
    
        $$
        \begin{cases}
        x + y = kp,\\
        xy = kq
        \end{cases}
        $$
    
        where $k\in\mathbf N_+$. From what we know about quadratic equations, the system has two distinct real roots only when
    
        $$
        \Delta = k^2p^2-4kq > 0 \iff k > \dfrac{4q}{p^2}
        $$
    
        In that case, the roots are
    
        $$
        x = \dfrac{kp - \sqrt{\Delta}}{2},~ y = \dfrac{kp + \sqrt{\Delta}}{2}.
        $$
    
        So we can directly enumerate all feasible $k$ and check whether such an integer solution exists. When enumerating $k$, the upper bound is checked by $y < E_\text{max}$.
    4.  Every time we get an answer, we set the upper bound $M_e$ on denominators to the largest denominator in the current answer minus one.
    
    Also, the implementation directly stores the values of $\dfrac{a}{b}-\dfrac{c}{d}$ and $C-g$. The numerator and denominator of the former are stored in variables `a` and `b`, and the latter is stored in variable `d`.

??? note "Sample code"
    ```cpp
    --8<-- "docs/search/code/idastar/idastar_1.cpp"
    ```

## Exercises

-   [UVa1343 The Rotation Game](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=4089)
