???+ warning "Note"
    The "Eulerian numbers" on this page are the Eulerian numbers in the strict sense. Do not confuse them with the Euler numbers, or with Euler's number (mathematical constants related to Euler, such as $\gamma$ or $\mathrm{e}$).

In enumerative combinatorics, the **Eulerian number** is the **number** of permutations of $1$ to $n$ in which exactly $m$ elements are larger than the element before them (permutations with $m$ "ascents"). It is written as:

$$
A(n, m) = 
\left\langle 
\begin{matrix}
  n\\
  m - 1
\end{matrix}
\right\rangle
$$

For example, there are $4$ permutations of the numbers $1$ to $3$ in which exactly one element is larger than the element before it:

| Permutation | Adjacent pairs that qualify | Count |
| ----------- | --------------------------- | ----- |
| 1 2 3 | 1, 2 & 2, 3 | 2  |
| 1 3 2 | 1, 3        | 1  |
| 2 1 3 | 1, 3        | 1  |
| 2 3 1 | 2, 3        | 1  |
| 3 1 2 | 1, 2        | 1  |
| 3 2 1 |             | 0  |

So by the definition of $A(n, m)$: when $n$ is $3$ and $m$ is $1$, the Eulerian number is $4$, meaning there are $4$ permutations with exactly $1$ element larger than the element before it.

For Eulerian numbers with small $n$ and $m$, we can write down the results directly:

| $A(n, m)$ | Qualifying permutations                      | Count |
| --------- | -------------------------------------------- | ----- |
| $A(1, 0)$ | $(1)$                                        | 1  |
| $A(2, 0)$ | $(2, 1)$                                     | 1  |
| $A(2, 1)$ | $(1, 2)$                                     | 1  |
| $A(3, 0)$ | $(3, 2, 1)$                                  | 1  |
| $A(3, 1)$ | $(1, 3, 2), (2, 1, 3), (2, 3, 1), (3, 1, 2)$ | 4  |
| $A(3, 2)$ | $(1, 2, 3)$                                  | 1  |

## Formula

Eulerian numbers can be computed by a recurrence or by recursion.

First, when $m \ge n$ or $n = 0$, no permutation qualifies, so the Eulerian number is $0$.

Next, when $m = 0$, only the decreasing permutation qualifies, so the Eulerian number is $1$.

Finally, consider building a permutation of $n$ by inserting $n$ into a permutation of $n-1$. Inserting $n$ raises the number of ascents by at most $1$, so $A(n, m)$ can be obtained from only $A(n-1, m-1)$ and $A(n-1, m)$.

Consider where $n$ is inserted: when $p_{i-1} < p_{i}$, inserting $n$ right before $p_{i}$, i.e. inserting $n$ into an "ascent", leaves the number of ascents unchanged. Inserting $n$ at the front of the permutation also leaves it unchanged. Inserting $n$ anywhere else raises the number of ascents by $1$.

For the transition from $A(n-1, m-1)$ to $A(n, m)$, the number of ascents must go up by $1$, so $n$ cannot be inserted into an "ascent" or at the front. This gives $n - (m-1) - 1 = n-m$ choices.

For the transition from $A(n-1, m)$ to $A(n, m)$, the number of ascents must stay the same, so $n$ can only be inserted into an "ascent" or at the front. This gives $m+1$ choices.

Putting it all together, we have

$$
A(n, m) = \begin{cases}
    0, & m > n \text{ or } n = 0, \\
    1, & m = 0, \\
    (n-m) \cdot A(n-1, m-1) + (m+1) \cdot A(n-1, m), & \text{otherwise}.
\end{cases}
$$

## Implementation

=== "C++"
    ```cpp
    int eulerianNumber(int n, int m) {
      if (m >= n || n == 0) return 0;
      if (m == 0) return 1;
      return (((n - m) * eulerianNumber(n - 1, m - 1)) +
              ((m + 1) * eulerianNumber(n - 1, m)));
    }
    ```

=== "Python"
    ```python
    def eulerianNumber(n, m):
        if m >= n or n == 0:
            return 0
        if m == 0:
            return 1
        return ((n - m) * eulerianNumber(n - 1, m - 1)) + (
            (m + 1) * eulerianNumber(n - 1, m)
        )
    ```

## Exercises

-   [CF1349F1 Slime and Sequences (Easy Version)](https://codeforces.com/problemset/problem/1349/F1)
-   [CF1349F2 Slime and Sequences (Hard Version)](https://codeforces.com/problemset/problem/1349/F2)
-   [UOJ 593. New Year's Army](https://uoj.ac/problem/593)
-   [P7511 Three to Six](https://www.luogu.com.cn/problem/P7511)
