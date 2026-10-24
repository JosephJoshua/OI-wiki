author: mwsht, sshwy, ouuan, Ir1d, Henry-ZHR, hsfzLZH1

## Introduction

The problems the hanging line method can solve are a subset of those a monotonic stack can solve. Specifically, the hanging line method applies to problems that satisfy these conditions:

-   You need to maintain monotonic information while scanning the sequence;
-   The problem can be solved with a monotonic stack;
-   You don't need binary search on the monotonic stack.

It may seem that the hanging line method can be replaced and is not very useful. But it is conceptually simpler than a monotonic stack, so it is easier for OI beginners to understand and use for problems like the largest submatrix.

## Example problems

???+ note "[SPOJ HISTOGRA - Largest Rectangle in a Histogram](https://www.spoj.com/problems/HISTOGRA)"
    Summary: there are $n$ rectangles of width $1$ standing on a horizontal line. Find the largest area of a rectangle contained in them.

A hanging line is a vertical line. It has two properties, an initial position and a height. It can move left and right as long as its top end does not go above the height of the rectangle at its current position.

For a hanging line, move it left and right as far as possible, keeping its top end no higher than the rectangle at the current position and not moving past the boundary, and find how far it can extend to the left and to the right. The area the line sweeps is then the largest rectangle containing the line. It is easy to see that the largest subrectangle must contain a hanging line with initial position $i$ and height $h_i$. Doing this by brute force takes $O(n ^ 2)$ time, but the hanging line method brings it down to $O(n)$.

Let's think about how to quickly find the leftmost position a hanging line can reach.

### How it works

Let $l_i$ be the leftmost position found so far that the hanging line at position $i$ can extend to. Clearly $l_i$ starts as $i$, and we need to check whether it can extend further left.

-   If currently $l_i = 1$, it has reached the boundary and cannot extend.
-   If currently $a_i > a_{l_i - 1}$, the line cannot extend further left from where it is.
-   If currently $a_i \le a_{l_i - 1}$, the line can still extend left. Moreover, wherever the line at position $l_i - 1$ can reach to the left, the line at position $i$ can surely reach too. So we update $l_i$ to $l_{l_i - 1}$ and keep checking.

Amortized analysis shows that each $l_i$ is visited by other $l_j$ at most once, so the time complexity is $O(n)$.

### Implementation

??? note "Reference code"
    ```cpp
    --8<-- "docs/misc/code/hoverline/hoverline_1.cpp"
    ```

???+ note "[UVa1619 Feel Good](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=4494)"
    For an array of length $n$, find a subarray that maximizes the product of its minimum and the sum of its elements. Among those with the maximum comfort value, minimize the length; among those with minimum length, minimize the left endpoint index.

In this problem, we can enumerate the minimum: treat each $a_i$ as the minimum, and extend left and right from $i$ to find the widest interval $[l, r]$ with $\min\limits _ {j = l} ^ r a_j = a_i$. This turns the problem into the hanging line model.

??? note "Reference code"
    ```cpp
    --8<-- "docs/misc/code/hoverline/hoverline_2.cpp"
    ```

## Largest subrectangle

???+ note "[P4147 Jade Toad Palace](https://www.luogu.com.cn/problem/P4147)"
    Given an $n \times m$ matrix of `'F'` and `'R'`, find the largest area of a submatrix in which every cell is `'F'`, and output that area $\times 3$.

This problem looks a lot like the first one. On closer inspection: if we look only at one row at a time, and use how far the cell at $(x, y)$ can extend upward as the length of the hanging line at that position, then the largest submatrix must be one of the largest rectangles obtained by extending these hanging lines left and right.

??? note "Reference code"
    ```cpp
    --8<-- "docs/misc/code/hoverline/hoverline_3.cpp"
    ```

## Exercises

-   [P1169 ZJOI2007 Chessboard Making](https://www.luogu.com.cn/problem/P1169)
