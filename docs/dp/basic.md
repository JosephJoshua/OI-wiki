author: Ir1d, CBW2007, ChungZH, xhn16729, Xeonacid, tptpp, hsfzLZH1, ouuan, Marcythm, HeRaNO, greyqz, Chrogeek, partychicken, zhb2000, xyf007, Persdre, XiaoSuan250, hhc0001, ZhangZhanhaoxiang, Taoran\_01

This page introduces the basic ideas of dynamic programming and how to design states and state transition equations, to give beginners a first understanding of dynamic programming.

The other pages in this section show how to build DP models for various kinds of problems, as well as some DP optimization techniques.

## Introduction

???+ note "[\[IOI1994\] Number Triangle](https://www.luogu.com.cn/problem/P1216)"
    Given a number triangle with $r$ rows ($r \leq 1000$), find a path that starts at the top and ends anywhere on the bottom row, such that the sum of the numbers on the path is as large as possible. At each step you can move to the number down-left or down-right of the current one.
    
    ```plain
            7 
          3   8 
        8   1   0 
      2   7   4   4 
    4   5   2   6   5 
    ```
    
    In the example above, the best path is $7 \to 3 \to 8 \to 7 \to 5$.

The most straightforward idea is to try every path. But the number of paths is $O(2^r)$, so this is not acceptable.

Notice this fact: in an optimal path, every single decision is optimal.

Take the optimal path from the example. Look only at the first four steps $7 \to 3 \to 8 \to 7$: there is no path from the top to the $2$-nd number of row $4$ with a larger sum.

For each position, there are only two possible next moves: down-left or down-right (if they exist). So we only need to record the maximum sum for the current position, and use it when making the next move to update the maximum sums of the following positions.

This has another benefit: we have reduced the size of the problem, splitting one problem into several smaller ones. To get the best path from the top to row $r$, we only need to know information about the best paths from the top to row $r-1$.

One issue remains: subproblems overlap a lot, and the same subproblem may be visited many times, so this is still not efficient. The fix is to store the answer of each subproblem, and use memoization to control the order of visits, so that each subproblem is visited only once.

These are some of the basic ideas of dynamic programming. Below we introduce the ideas of dynamic programming more systematically.

## Principles of dynamic programming

A problem that can be solved by dynamic programming must satisfy three conditions: optimal substructure, no aftereffects, and overlapping subproblems.

### Optimal substructure

A problem with optimal substructure may also be suitable for a greedy approach.

Make sure we consider all the subproblems used in the optimal solution.

1.  Show that the first part of an optimal solution to the problem is making a choice;
2.  For a given problem, among its possible first choices, assume you already know which choice leads to an optimal solution. You do not care for now how this choice is found; you just assume you know it;
3.  Given the choice that leads to an optimal solution, determine which subproblems this choice creates, and how best to describe the space of subproblems;
4.  Show that, as parts of an optimal solution to the original problem, the solution of each subproblem is itself an optimal solution of that subproblem. Use proof by contradiction: suppose the solution of some subproblem is not optimal for that subproblem. Then we could replace this non-optimal solution with the optimal solution of the subproblem inside the solution to the original problem, getting a better solution to the original problem. This contradicts the assumption that the original solution was optimal.

Keep the subproblem space as simple as possible, and only extend it when necessary.

Optimal substructure differs between problems in two ways:

1.  How many subproblems an optimal solution of the original problem involves;
2.  How many choices we need to consider when deciding which subproblems an optimal solution uses.

In the subproblem graph, each vertex corresponds to a subproblem, and the choices to consider correspond to the edges incident to the subproblem vertices.

### No aftereffects

Once a subproblem is solved, its answer is not affected by later decisions.

### Overlapping subproblems

If there are many overlapping subproblems, we can spend memory to store their answers, so that the same subproblem is never solved twice, which improves efficiency.

### Basic approach

For a problem that can be solved by dynamic programming, the usual approach is:

1.  Divide the original problem into several **stages**. Each stage corresponds to several subproblems. Extract the features of these subproblems (called **states**);
2.  Find the possible **decisions** for each state, that is, how states transition to each other (in mathematical terms, the **state transition equation**).
3.  Solve the problems of each stage in order.

From a graph theory point of view, we build a [directed acyclic graph](../graph/dag.md) where each state is a vertex and each decision is an edge between vertices. The problem then becomes finding the longest (or shortest) path in a DAG (see: [DP on a DAG](./dag.md)).

## Longest common subsequence

???+ note "Longest common subsequence problem"
    Given a sequence $A$ of length $n$ and a sequence $B$ of length $m$ ($n,m \leq 5000$), find the longest sequence that is a subsequence of both $A$ and $B$.

For the definition of a subsequence, see [Subsequence](../string/basic.md). A short example: the common subsequences of the strings `abcde` and `acde` are `a`, `c`, `d`, `e`, `ac`, `ad`, `ae`, `cd`, `ce`, `de`, `acd`, `ade`, `ace`, `cde`, `acde`, and the length of the longest common subsequence is 4.

Let $f(i,j)$ be the length of the longest common subsequence when only the first $i$ elements of $A$ and the first $j$ elements of $B$ are considered. Finding this length is a **subproblem**. $f(i,j)$ is what we call a **state**, and $f(n,m)$ is the final state, which is the answer we want.

For each $f(i,j)$, there are three decisions: if $A_i=B_j$, we can append it to the end of the common subsequence; the other two decisions are to skip $A_i$ or to skip $B_j$. The state transition equation is:

$$
f(i,j)=\begin{cases}f(i-1,j-1)+1&A_i=B_j\\\max(f(i-1,j),f(i,j-1))&A_i\ne B_j\end{cases}
$$

You can use the [interactive LCS page on SourceForge](http://lcs-demo.sourceforge.net/) to better understand how LCS is computed.

???+ example "Reference implementation"
    === "C++"
        ```cpp
        --8<-- "docs/dp/code/basic/lcs.cpp:core"
        ```
    
    === "Python"
        ```cpp
        --8<-- "docs/dp/code/basic/lcs.py:core"
        ```

The time complexity of this approach is $O(nm)$.

There is also an $O\left(\dfrac{nm}{w}\right)$ algorithm for this problem[^ref1]. Interested readers can explore it on their own.

## Longest non-decreasing subsequence

???+ note "Longest non-decreasing subsequence problem"
    Given a sequence $a$ of length $n$ ($n \leq 5000$), find the longest subsequence of $a$ in which each element is not less than the one before it.

### Algorithm 1

Let $f(i)$ be the length of the longest non-decreasing subsequence ending at $a_i$. Then the answer is $\max_{1 \leq i \leq n} f(i)$.

When computing $f(i)$, try appending $a_i$ to other longest non-decreasing subsequences to update the answer. So we can write this state transition equation: $f(i)=\max_{1 \leq j < i,~a_j \leq a_i} (f(j)+1)$.

???+ example "Reference implementation"
    === "C++"
        ```cpp
        --8<-- "docs/dp/code/basic/lis-1.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/dp/code/basic/lis-1.py:core"
        ```

It is easy to see that this algorithm runs in $O(n^2)$ time.

### Algorithm 2

When the range of $n$ grows to $n \leq 10^5$, the first approach is no longer fast enough. Below is an $O(n \log n)$ approach.

Consider the state $(i, l)$ defined before, meaning the longest non-decreasing subsequence ending at the $i$-th element has length $l$. Instead of processing states with a fixed $i$ as before, here we directly decide whether $(i, l)$ is valid:

-   The initial state $(1,1)$ is always valid.
-   For any $(i, l)$, if there is $j < i$ such that $(j, l-1)$ is valid and $a_j \le a_i$, then $(i, l)$ is valid.

In the end, we just need to find the valid state $(i,l)$ with the largest $l$ to get the length of the longest non-decreasing subsequence.

Let the original sequence be $a_1, \cdots, a_n$. Define an array $d$ whose $x$-th entry is the smallest possible last element of a non-decreasing subsequence of length $x$. Initially the sequence is empty. Let $i$ go from $1$ to $n$, finding in turn the length of the longest non-decreasing subsequence of the first $i$ elements. For the current element $a_i$:

-   If $a_i$ is greater than or equal to the last element of $d$, append $a_i$ directly to the end of $d$.
    -   Explanation: if $a_i$ is greater than or equal to the last element of the current longest subsequence, there is a non-decreasing subsequence that $a_i$ can extend. Not appending it would break optimality.
-   If $a_i$ is strictly less than the last element of $d$, find the **first** element greater than it, and replace that element with $a_i$.
    -   Explanation: appending it at the end would break the monotonicity of $d$. Replacing keeps the last element for each length as small as possible, which leaves more options for later elements.
    -   Optimization: since $d$ is non-decreasing, we can use binary search to find the position directly, bringing the overall complexity down to $O(n\log n)$ instead of $O(n^2)$ with a linear search.

If you also need to output an actual longest non-decreasing subsequence, you can maintain an extra array $d'_x$: the position of the smallest last element among non-decreasing subsequences of length $x$ (if there are several, pick any one). To maintain it, whenever you put $a_i$ into $d_x$, also set $d'_x$ to $i$. At the same time, record the best predecessor of $i$ as $p_i = d'_{x-1}$. Finally, start from any state with the maximum length and follow the predecessors $p_i$ backward to get the full subsequence.

???+ example "Reference implementation"
    === "C++"
        ```cpp
        --8<-- "docs/dp/code/basic/lis-2.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/dp/code/basic/lis-2.py:core"
        ```

This algorithm runs in $O(n\log n)$ time. Outputting the answer takes $O(\textit{ans})$ time.

???+ tip "Note"
    For the longest **increasing** subsequence problem, similarly let $d_i$ be the smallest last element among all increasing subsequences of length $i$.
    
    Note that in step 2, if $a_i \leq d_{len}$, since adjacent elements in an increasing subsequence cannot be equal, you need to find the **first** element in $d$ that is **not less than** $a_i$, and replace it with $a_i$.
    
    In the implementation (taking C++ as an example), change the `upper_bound` function to `lower_bound`.

## References and notes

-   [A detailed explanation of the n log n algorithm for the longest non-decreasing subsequence - lvmememe - cnblogs](https://www.cnblogs.com/itlqs/p/5743114.html)

[^ref1]: [Computing the longest common subsequence with bit operations - -Wallace- - cnblogs](https://www.cnblogs.com/-Wallace-/p/bit-lcs.html)
