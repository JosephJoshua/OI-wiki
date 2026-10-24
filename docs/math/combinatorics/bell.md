The Bell numbers $B_n$, named after Eric Temple Bell, are an integer sequence in combinatorics. The sequence begins with ([OEIS A000110](https://oeis.org/A000110)):

$$
B_0 = 1,B_1 = 1,B_2=2,B_3=5,B_4=15,B_5=52,B_6=203,\dots
$$

$B_n$ is the number of ways to partition a set with $n$ elements. A partition of a set $S$ is a family of pairwise disjoint non-empty subsets of $S$ whose union is $S$. For example, $B_3 = 5$ because the 3-element set ${a, b, c}$ has 5 different partitions:

$$
\begin{aligned}
&\{ \{a\},\{b\},\{c\}\} \\
&\{ \{a\},\{b,c\}\} \\
&\{ \{b\},\{a,c\}\} \\
&\{ \{c\},\{a,b\}\} \\
&\{ \{a,b,c\}\} \\
\end{aligned}
$$

$B_0$ is 1 because the empty set has exactly 1 partition.

## Recurrence

The Bell numbers satisfy the recurrence:

$$
B_{n+1}=\sum_{k=0}^n\binom{n}{k}B_{k}
$$

Proof:

$B_{n+1}$ is the number of partitions of a set with $n+1$ elements. Let the set for $B_n$ be $\{b_1,b_2,b_3,\dots,b_n\}$ and the set for $B_{n+1}$ be $\{b_1,b_2,b_3,\dots,b_n,b_{n+1}\}$. We can view $B_{n+1}$ as coming from $B_{n}$ by adding one element $b_{n+1}$. Consider the element $b_{n+1}$.

-   If it is in a block by itself, $n$ elements remain, and the number of partitions in this case is $\dbinom{n}{n}B_{n}$;

-   If it is in a block with exactly 1 other element, $n-1$ elements remain, and the number of partitions in this case is $\dbinom{n}{n-1}B_{n-1}$;

-   If it is in a block with exactly 2 other elements, $n-2$ elements remain, and the number of partitions in this case is $\dbinom{n}{n-2}B_{n-2}$;

-   ...

Continuing this way gives the formula above.

Each Bell number is the sum of the corresponding [Stirling numbers of the second kind](./stirling.md#stirling-numbers-of-the-second-kind-stirling-number),
because a Stirling number of the second kind counts the ways to partition a set of $n$ elements into exactly $k$ non-empty subsets.

$$
B_{n} = \sum_{k=0}^n{n\brace k}
$$

## Bell triangle

Build a triangular array as follows (similar in form to Pascal's triangle):

-   $a_{0,0} = 1$;
-   for $n \ge 1$, the first entry of row $n$ equals the last entry of the previous row, i.e. $a_{n,0}=a_{n-1,n-1}$;
-   for $m,n \ge 1$, entry $m$ of row $n$ is the sum of the two numbers to its left and to its upper left, i.e. $a_{n,m}=a_{n,m-1}+a_{n-1,m-1}$.

The first few rows are:

$$
\begin{aligned}
& 1   \\
& 1\quad\qquad 2  \\
& 2\quad\qquad 3\quad\qquad 5  \\
& 5\quad\qquad 7\quad\qquad 10\,\,\,\qquad 15 \\
& 15\,\,\,\qquad 20\,\,\,\qquad  27\,\,\,\qquad 37\,\,\,\qquad 52  \\
& 52\,\,\,\qquad  67\,\,\,\qquad 87\,\,\,\qquad 114\qquad 151\qquad 203\\
& 203\qquad  255\qquad 322\qquad  409\qquad 523\qquad  674\qquad 877 \\  
\end{aligned}
$$

The first entry of each row is a Bell number. We can use this triangle to compute Bell numbers one row at a time.

??? note "Reference implementation"
    === "C++"
        ```cpp
        constexpr int MAXN = 2000 + 5;
        int bell[MAXN][MAXN];
        
        void f(int n) {
          bell[0][0] = 1;
          for (int i = 1; i <= n; i++) {
            bell[i][0] = bell[i - 1][i - 1];
            for (int j = 1; j <= i; j++)
              bell[i][j] = bell[i - 1][j - 1] + bell[i][j - 1];
          }
        }
        ```
    
    === "Python"
        ```python
        MAXN = 2000 + 5
        bell = [[0 for i in range(MAXN + 1)] for j in range(MAXN + 1)]
        
        
        def f(n):
            bell[0][0] = 1
            for i in range(1, n + 1):
                bell[i][0] = bell[i - 1][i - 1]
                for j in range(1, i + 1):
                    bell[i][j] = bell[i - 1][j - 1] + bell[i][j - 1]
        ```

## Exponential generating function

Consider the exponential generating function of the Bell numbers and its derivative:

$$
\begin{aligned}
\hat B(x) &= \sum_{n = 0}^{+\infty}\frac{B_n}{n!}x^n \\
&= 1 + \sum_{n = 0}^{+\infty}\frac{B_{n+1}}{(n + 1)!}x^{n + 1} \\
\hat B'(x) &= \sum_{n = 0}^{+\infty}\frac{B_{n+1}}{n!}x^{n}
\end{aligned}
$$

From the recurrence for Bell numbers we get:

$$
\frac{B_{n+1}}{n!} = \sum_{k = 0}^{n}\frac{1}{(n-k)!}\frac{B_{k}}{k!}
$$

This is a convolution, so:

$$
\hat B'(x) = \mathrm{e}^x \hat B(x)
$$

This is a differential equation. Solving it gives:

$$
\hat B(x) = \exp\left(\mathrm{e}^x + C\right)
$$

Finally, $\hat B(x) = 1$ when $x = 0$. Substituting gives $C = -1$, so the closed form of the exponential generating function of the Bell numbers is:

$$
\hat B(x) = \exp\left(\mathrm{e}^x - 1\right)
$$

Precompute the first $n$ terms of $\mathrm{e}^x - 1$, then apply one [polynomial exp](../poly/elementary-func.md#polynomial-logarithm--exponential) to get the first $n$ Bell numbers. The bottleneck is the polynomial exp, so the time complexity can be $O(n \log n)$.

## References

<https://en.wikipedia.org/wiki/Bell_number>
