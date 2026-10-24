**Counting DP** uses a DP-like memoized search (somewhat different from DP in the narrow sense, i.e. optimization problems) to solve counting (and summation) problems.

## Basics

### Basic idea

A counting problem usually asks for the size of a set $S$. In OI, the size of $S$ can sometimes reach $\Theta(n^n)$ or even $\Theta(2^{n!})$ (usually taken modulo some fixed number, of course), where $n$ is the problem size. So we cannot list the elements of $S$ one by one.

If we can split $S$ into several disjoint subsets, then the number of elements in $S$ equals the sum of the sizes of these parts. If counting these subsets happens to look like the original problem, we can solve it in a DP-like way.

### Example problem

???+ note "Example problem"
    Given a positive integer $n$, count the ways to write $n$ as a sum of $k$ positive integers. Different orders count as different ways.

Let the set $S_{n,k}$ consist of tuples of positive integers $(a_1, \dots, a_k)$ with $a_1 + \dots + a_k = n$. If $a_k$ is fixed, we can derive: since $a_1 + a_2 + \dots + a_{k-1} + a_k = n$, we have $a_1 + a_2 + \dots + a_{k-1} = n - a_k$. By the definition of $S_{n,k}$, $(a_1, a_2, \dots, a_{k-1}) \in S_{n - a_k, k - 1}$.

Since $a_1, a_2, \dots, a_k$ are positive integers, $a_k$ ranges over $[1, n - k + 1] \cap \mathbb Z$. So $S_{n,k}$ can be split by $a_k$ into $n - k + 1$ subsets, where the subset for $a_k = i$ is:

$$
\{(L, i) \mid L \in S_{n-i,k-1}\}.
$$

The number of elements in this subset is clearly equal to that of $S_{n-i,k-1}$. Since the values of $i$ differ, these subsets are pairwise disjoint. So:

$$
|S_{n,k}| = \sum_{i=1}^{n-k+1} |S_{n-i,k-1}|.
$$

So we can handle it in a DP-like way: let $f_{n,k}$ be $|S_{n,k}|$. Then the state transition equation is:

$$
f_{n,k} = \sum_{i=1}^{n-k+1} f_{n-i,k-1}.
$$

Now it can be solved with DP.

### Similarities and differences with optimization DP

Notice that both counting DP and optimization DP compute a value (a size, or an optimal value) over a domain $\Omega$. This value is obtained by processing every element of $\Omega$ once and then combining the processed values.

For example, in the 0-1 knapsack problem, the elements of $\Omega$ are the sets of items put in the knapsack. For a choice $S$ in $\Omega$, we process $S$ to get $w(S)$, the total value of the items in $S$. Taking the maximum over all processed values gives the answer.

For a counting problem, $\Omega$ is the set $S$ whose size we want. Processing turns every element of $S$ into $1$, and these $1$s are then combined by addition. Since each element of $S$ corresponds to one $1$, the result is the number of elements of $S$.

When the combining operation is max/min, we can split $\Omega$ into any number of parts, as long as their union is $\Omega$; they do not need to be disjoint. Counting does not allow this, so we need to split $\Omega$ into parts that are pairwise disjoint. This is the difference from optimization DP.

## Example problem

???+ note "Example problem"
    Given a positive integer $n$, count the ways to write $n$ as a sum of any number of positive integers. Different orders count as the **same** way.

### Solution 1

The elements of the set we need to count are multisets of positive integers whose sum is $n$. But this is clearly hard to work with directly.

If a multiset $T$ contains only positive integers $\le M$ and the sum of all elements of $T$ is $n$, we say $T \in S_{n, M}$. Consider how many times $M$ appears. It can be $k \in \left[0, \left\lfloor \dfrac nM \right\rfloor\right] \cap \mathbb Z$. Then it transitions to $S_{n - kM, M - 1}$. Just sum these up. The complexity is $\Theta(n^2 \log n)$ (the $\log$ comes from the harmonic series caused by the range of $k$).

But this is not good enough. Consider the example below:

$$
\begin{aligned}
f_{8, 3} &= {\color{red}f_{8, 2} + f_{5, 2} + f_{2, 2}} \\
f_{9, 3} &= {\color{blue}f_{9, 2} + f_{6, 2} + f_{3, 2} + f_{0, 2}} \\
f_{10, 3} &= {\color{green}f_{10, 2} + f_{7, 2} + f_{4, 2} + f_{1, 2}}\\
f_{11, 3} &= f_{11, 2} + {\color{red}f_{8, 2} + f_{5, 2} + f_{2, 2}}\\
f_{12, 3} &= f_{12, 2} + {\color{blue}f_{9, 2} + f_{6, 2} + f_{3, 2} + f_{0, 2}}\\
f_{13, 3} &= f_{13, 2} + {\color{green}f_{10, 2} + f_{7, 2} + f_{4, 2} + f_{1, 2}}\\
\end{aligned}
$$

Substituting equal parts gives $f_{11, 3} = f_{11, 2} + f_{8, 3}$, $f_{12, 3} = f_{12, 2} + f_{9, 3}$, $f_{13, 3} = f_{13, 2} + f_{10, 3}$. In the same way we get a general state transition equation:

$$
f_{n, M} = f_{n, M - 1} + \begin{cases} f_{n - M, M} & n \ge M, \\ 0 & \text{otherwise}. \end{cases}
$$

Now the time complexity is $\Theta(n^2)$.

### Solution 2

Any multiset $T$ of positive integers can be obtained using two operations: "increase every element of $T$ by one" and "add an element with value $1$ to $T$". Different sequences of operations give different results.

So transitions on $T$ can be turned into transitions on operation sequences. Consider the operation sequences that split $n$ into $m$ numbers (denote the set of all of them by $B_{n,m}$), and look at the last operation. If it is operation $1$, no number is added, but $\sum T$ increases by $m$. For the final $\sum T = n$, the previous $T$ (denoted $T'$) must have sum $n-m$. So $B_{n,m} \to B_{n-m,m}$. If it is operation $2$, one number is added and $\sum T$ increases by $1$. So $B_{n,m} \to B_{n-1,m-1}$.

The time complexity of this approach is still $\Theta(n^2)$.

### Solution 3

Split $T$ into the part $T_1$ of elements greater than $\sqrt n$ and the part $T_2$ of elements less than or equal to $\sqrt n$. $T_2$ can be counted with Solution 1, and the number of $T_1$ can be counted by slightly modifying Solution 2: change the two operations to "increase every element of $T_1$ by one" and "add an element with value $\lfloor \sqrt n \rfloor + 1$ to $T_1$". The state transition equation is easy to write.

Split $n$ into two parts $A$ and $B$. Enumerating one of them determines the other. Count the $T_1$ with $\sum T_1 = A$ and the $T_2$ with $\sum T_2 = B$, multiply the two counts, and sum over all $A$ to get the final answer.

When counting $T_1$, $M \le \sqrt n$, so computing $T_1$ with Solution 1 takes $\Theta(n^{3/2})$ time. Similarly, when counting $T_2$, $|T_2| \le \dfrac{\sum T_2}{\sqrt n} \le \dfrac{n}{\sqrt n} = \sqrt n$, so computing $T_2$ with Solution 2 also takes $\Theta(n^{3/2})$ time. So the total time complexity is $\Theta(n^{3/2})$.
