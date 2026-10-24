## Definition

Interval DP is an extension of linear DP. When it splits a problem into stages, it depends heavily on the order in which elements appear within a stage and on which elements of the previous stage are merged to form them.

Let the state $f(i,j)$ be the maximum value obtainable by merging all elements from index $i$ to $j$. Then $f(i,j)=\max\{f(i,k)+f(k+1,j)+cost\}$, where $cost$ is the value gained by merging these two groups of elements.

## Properties

Interval DP has the following features:

**Merging**: combining two or more parts into one (or, of course, the reverse);

**Feature**: the problem can be broken down into a form where parts are merged two at a time;

**Solving**: define the optimal value for the whole problem, enumerate the merge point to split the problem into a left part and a right part, and finally merge the optimal values of the two parts to get the optimal value of the original problem.

## Explanation

### Example problem

???+ note "[NOI1995 Merging Stones](https://loj.ac/problem/10147)"
    Summary: there are $n$ numbers $a_1,a_2,\dots,a_n$ arranged in a circle. Perform $n-1$ merge operations. Each operation merges two adjacent piles into one, and you score the total number of stones in the new pile. Maximize your score.

First consider the case where the piles are in a line rather than a circle.

Let $f(i,j)$ be the maximum score for merging all the stones in the interval $[i,j]$ into one pile.

Write down the **state transition equation**: $f(i,j)=\max\{f(i,k)+f(k+1,j)+\sum_{t=i}^{j} a_t \}~(i\le k<j)$

Let $sum_i$ be the prefix sums of the array $a$. The state transition equation becomes $f(i,j)=\max\{f(i,k)+f(k+1,j)+sum_j-sum_{i-1} \}$.

### How to do the state transitions

Computing $f(i,j)$ requires all values of $f(i,k)$ and $f(k+1,j)$, and both of these contain fewer elements than $f(i,j)$. So we use $len=j-i+1$ as the stage of the DP. First enumerate $len$ from small to large, then enumerate $i$, compute $j$ from $len$ and $i$, and then enumerate $k$. The time complexity is $O(n^3)$

### How to handle the circle

The stones in the problem form a circle, not a line. What should we do?

**Method 1**: since the stones form a circle, we can enumerate where to cut it, turning the circle into a line. Since we enumerate $n$ times, the final time complexity is $O(n^4)$.

**Method 2**: we double the length of the line, making $2\times n$ piles, where pile $i$ is the same as pile $n+i$. After solving with dynamic programming, take the best of $f(1,n),f(2,n+1),\dots,f(n,2n-1)$ as the final answer. The time complexity is $O(n^3)$.

## Implementation

=== "C++"
    ```cpp
    for (len = 2; len <= n; len++)
      for (i = 1; i <= 2 * n - len; i++) {
        int j = len + i - 1;
        for (k = i; k < j; k++)
          f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j] + sum[j] - sum[i - 1]);
      }
    ```

=== "Python"
    ```python
    for len in range(2, n + 1):
        for i in range(1, 2 * n - len + 1):
            j = len + i - 1
            for k in range(i, j):
                f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j] + sum[j] - sum[i - 1])
    ```

## Practice problems

[NOIP 2006 Energy Necklace](https://www.luogu.com.cn/problem/P1063)

[NOIP 2007 Matrix Number-Taking Game](https://www.luogu.com.cn/problem/P1005)

[IOI2000 Post Office](https://www.luogu.com.cn/problem/P4767)
