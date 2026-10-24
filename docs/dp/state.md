## Introduction

Bitmask DP is a kind of dynamic programming. It encodes a set of states as an integer and stores that integer in the DP state, so that transitions can be made between such sets.

To get a lower time complexity, we usually look for a state design with fewer states. Most problems use binary states: an $n$-bit binary number describes $n$ independent two-valued states.

Bitmask DP usually involves bit operations. For the basics of bit operations, see the [Bit operations](../math/bit.md) page.

## Example problem 1

???+ note "['SCOI2005' Non-attacking Kings](https://loj.ac/problem/2153)"
    Place $K$ kings on an $N\times N$ chessboard ($1 \leq N \leq 9, 1 \leq K \leq N \times N$) so that no two of them attack each other. How many ways are there to place them?
    
    A king attacks the one adjacent cell in each of the eight directions: up, down, left, right, up-left, down-left, up-right and down-right. That is $8$ cells in total.

### Solution

Let $f(i,j,l)$ be the number of valid placements of the first $i$ rows, where the state of row $i$ is $j$ and $l$ kings have been placed on the board so far.

For the state numbered $j$, we use a binary integer $sit(j)$ to describe where the kings are. A bit of $sit(j)$ is $0$ if no king is placed at the corresponding position, and $1$ if a king is placed there. We use $sta(j)$ for the number of kings in this state, which is the number of $1$ bits in $sit(j)$. For example, the state in the figure below can be written as the binary number $100101$ (the left side of the board corresponds to the low bits), so $sit(j)=100101_{(2)}=37, sta(j)=3$.

![](./images/SCOI2005-互不侵犯.png)

Let the state of the current row be $j$ and the state of the previous row be $x$. We get the transition equation: $f(i,j,l) = \sum f(i-1,x,l-sta(j))$.

Let the state number of the previous row be $x$. We enumerate every possible $x$ that does not conflict with the current row and make the transition:

$$
f(i,j,l) = \sum f(i-1,x,l-sta(j))
$$

### Implementation

??? note "Reference code"
    ```cpp
    --8<-- "docs/dp/code/state/state_1.cpp"
    ```

## Example problem 2

???+ note "[\[POI2004\] PRZ](https://www.luogu.com.cn/problem/P5911)"
    $n$ people need to cross a bridge. Person $i$ weighs $w_i$ and takes $t_i$ time to cross. The people cross in several groups, and a group can only start after every person in the previous group has finished crossing. The bridge can hold at most $W$ weight. Find the minimum total time for everyone to cross.
    
    $100\le W \le 400$, $1\le n\le 16$, $1\le t_i\le 50$, $10\le w_i\le 100$.

### Solution

Let $S$ be a subset of the set of all people. Let $t(S)$ be the longest crossing time among the people in $S$, $w(S)$ the total weight of the people in $S$, and $f(S)$ the minimum time for everyone in $S$ to cross. Then:

$$
\begin{cases}
    f(\varnothing)=0,\\
    f(S)=\min\limits_{T\subseteq S;~w(T)\leq W}\left\{t(T)+f(S\setminus T)\right\}.
\end{cases}
$$

Note that you should not enumerate all sets and then check whether each one is a subset. Instead, use [submask enumeration](../math/binary-set.md#遍历所有掩码的子掩码), which makes the time complexity $O(3^n)$.

### Implementation

??? note "Reference code"
    ```cpp
    --8<-- "docs/dp/code/state/state_2.cpp"
    ```

## Exercises

-   ['NOI2001' Artillery Positions](https://loj.ac/problem/10173)
-   ['USACO06NOV' Corn Fields](https://www.luogu.com.cn/problem/P1879)
-   ['Nine-Province Joint Exam 2018' A Pair of Wooden Chess](https://loj.ac/problem/2471)
