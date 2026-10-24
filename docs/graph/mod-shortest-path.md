You can use the "shortest paths modulo a number" method (congruence shortest paths) for problems like these: "Given $n$ integers, how many other integers can be formed by summing them (each of the $n$ integers may be used any number of times)?", "Given $n$ integers, find the smallest (or largest) integer that they cannot form", or "At least how many pieces are needed to form a number that is congruent to $p$ modulo $K$?"

Congruence shortest paths uses congruence classes to build states, which lowers the space complexity.

Similar to the [difference constraints](./diff-constraints.md) method, the states built from congruence classes can be seen as vertices in a single-source shortest path problem. The state transition usually looks like $f(i+y) = f(i) + y$, similar to $f(v) = f(u) +edge(u,v)$ in single-source shortest paths.

## Example problems

### Example 1

???+ note "[P3403 Elevator](https://www.luogu.com.cn/problem/P3403)"
    Summary: given $x, y, z, h$, how many $k \in [1,h]$ satisfy $ax+by+cz=k$? ($0\leq a,b,c$, $1\le x,y,z\le 10^5$, $h\le 2^{63}-1$)

Assume without loss of generality that $x < y < z$.

Let $d_i$ be the lowest floor $p$ with $p\bmod x = i$ that can be reached using only **operation 2** and **operation 3**. In other words, it is the smallest number congruent to $i$ modulo $x$ that operations 2 and 3 can produce. We use it to count the valid numbers in that congruence class.

We get two transitions:

-   $i \xrightarrow{y} (i+y) \bmod x$

-   $i \xrightarrow{z} (i+z) \bmod x$

Note that we usually take the modulus to be the smallest of the given numbers $a_i$, here $x$. This keeps the space complexity as low as possible (the smallest residue system).

In effect, this is the same as adding edges in a shortest path graph:

`add(i, (i+y) % x, y)`

`add(i, (i+z) % x, z)`

Next we only need $d_0, d_1, d_2, \dots, d_{x-1}$. One run of a shortest path algorithm gives all the $d_i$.

??? example "Implementation based on shortest paths"
    ```cpp
    --8<-- "docs/graph/code/mod-shortest-path/mod-shortest-path_1.cpp"
    ```

In fact, we do not even need a general shortest path algorithm. Note two special properties:

First, there are only two edge weights, and on any path the order in which the two kinds of edges are taken does not matter, because addition is commutative. So we can run the shortest path twice, each time with only the edges of one weight.

Second, in a graph with only one edge weight, each vertex $u$ has one incoming edge (from $(u-y) \bmod x$) and one outgoing edge (to $(u+y) \bmod x$). So the whole graph must consist of several cycles. One can show that there are exactly $\gcd(x,y)$ cycles, all of the same length.

???+ note "Proof"
    Let $d=\gcd(x,y)$, and write $x=da,y=db$, so $\gcd(a,b)=1$.
    
    Starting from $u$ and taking $k$ steps, we reach $(u+ky) \bmod x$. If we are back at the start, then $ky \equiv 0 \pmod x$, that is, $kb \equiv 0 \pmod a$.
    
    Since $\gcd(a,b)=1$, the smallest such $k$ is $a$, so the cycle length is $a = \dfrac{x}{d}$. Since this holds for any starting vertex, all cycles have the same length, and there are $d$ cycles.

Also, the edge weights are positive, so after going around a cycle twice, no further relaxation is possible. We just loop around and update directly. This way we are not limited by the complexity of a shortest path algorithm, and we get $O(x)$.

As in difference constraints, if $\{a_1,a_2,\cdots,a_n\}$ is a solution, then $\{a_1+d,a_2+d,\cdots,a_n+d\}$ is also a solution. So in this problem we use $i=1$ as the source. The source value $dis_{1}=1$ is the smallest possible within the known range, so the solution we get is also the smallest one.

The answer is:

$$
\sum_{i=0}^{x-1}\left(\frac{h-d_i}{x} + 1\right)
$$

We add 1 because floor $d_i$ itself also counts.

In the implementation, note that $h \leq 2^{63}-1$. So before running the shortest path, the initial value of $d_i$ must be at least $2^{63}$, which is larger than the maximum of `long long` in C++. You can use `unsigned long long`, or first set $h \gets h - 1$ and treat the lowest floor as floor $0$; the rest of the code is the same.

??? example "Implementation with the cycle optimization"
    ```cpp
    --8<-- "docs/graph/code/mod-shortest-path/mod-shortest-path_2.cpp"
    ```

### Example 2

???+ note "[ARC084B Small Multiple](https://atcoder.jp/contests/arc084/tasks/arc084_b)"
    Summary: given $n$, among all multiples of $n$, find the smallest digit sum. ($1\le n\le 10^5$)

This problem can be solved in $O(n\log^2 n)$ time with an unbounded knapsack optimized by cyclic convolution, but we want a linear algorithm.

Notice that every positive integer can be obtained by starting from $1$ and applying "multiply by $10$" and "add $1$" in some order, and the number of "add $1$" operations is exactly the digit sum. This suggests using shortest paths.

For every $0\le k\le n-1$, add an edge of weight $0$ from $k$ to $10k$, and an edge of weight $1$ from $k$ to $k+1$ (all vertex numbers are taken modulo $n$).

Each multiple of $n$ corresponds to a path from vertex $1$ to vertex $0$ in this graph, so we just need the shortest path from $1$ to $0$. Some paths are invalid (for example, taking $10$ edges of weight $1$ in a row), but such paths never give a better answer, so they do not affect the result.

The time complexity is $O(n)$.

## Exercises

[Luogu P3403 Elevator](https://www.luogu.com.cn/problem/P3403)

[Luogu P2662 Cattle Pen Fence](https://www.luogu.com.cn/problem/P2662)

[\[National Training Team\] Momo's Equation](https://www.luogu.com.cn/problem/P2371)

[NOIP2018 Currency System](https://loj.ac/problem/2951)

[AGC057D - Sum Avoidance](https://atcoder.jp/contests/agc057/tasks/agc057_d)

[THUPC 2023 Preliminary Round - Knapsack](https://loj.ac/p/6872)
