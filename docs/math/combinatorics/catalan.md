## Introduction

Catalan numbers show up in many counting problems. The Belgian mathematician Eugène Charles Catalan found this sequence in 1958 while studying the problem of counting bracket sequences, and the sequence is named after him. The Qing dynasty mathematician Minggatu had already found this sequence back in the 1730s.

The Catalan numbers satisfy the following recurrence:

$$
C_n = \begin{cases}
1, & n = 0, \\
\sum_{i=0}^{n-1} C_{i}C_{n-1-i}, & n > 0.
\end{cases}\tag{1}
$$

The first few terms of the sequence are ([OEIS: A000108](https://oeis.org/A000108), indexed from $0$):

$$
1,1,2,5,14,42,132,429,1430,\ldots
$$

## Applications

The recurrence for the Catalan numbers $C_n$ has a natural recursive structure: a counting problem $C_n$ of size $n$ can be split, by enumerating a split point, into two subproblems of sizes $i$ and $(n-1-i)$. Because of this, Catalan numbers appear in many problems with a similar recursive structure.

-   **Counting lattice paths**: take an $n\times n$ grid with the lower-left corner at $(0, 0)$ and the upper-right corner at $(n, n)$. Starting from the lower-left corner, each step moves one unit right or one unit up. The number of paths that reach the upper-right corner without going above the diagonal $y=x$ (touching it is allowed) is $C_n$.

    ??? note "Proof"
        Let the number of paths be $T_n$. Consider the case $n \ge 2$. Let $(k,k)~(k \in [1,n])$ be the point where the path reaches the diagonal $y=x$ for the **first time**. Look at the paths from $(0,0)$ to $(k,k)$ whose points, other than the start and the end, **do not lie on the diagonal (cannot touch it)**.
        
        ![catalan2](./images/catalan-2.svg)
        
        As the figure shows, the first step of such a path must go right, from $(0,0)$ to $(1,0)$, and the last step must go up, from $(k,k-1)$ to $(k,k)$. So these paths are exactly the paths from $(1,0)$ to $(k,k-1)$ that do not cross the line $y=x-1$, and there are $T_{k-1}$ of them. Also, the number of valid paths from $(k,k)$ to $(n,n)$ is $T_{n-k}$. By the multiplication principle, the number of paths that touch the diagonal for the first time at $(k,k)$ is $T_{k-1} T_{n-k}$. Enumerating all possible $k$, the total number of valid paths is
        
        $$
        T_n = \sum_{k=1}^n T_{k-1}T_{n-k}.
        $$
        
        Substituting $k=i+1$ shows that this is exactly the Catalan recurrence. Since $T_0=1$, we get $T_n = C_n$.

    <!-- To make bot happy. Do NOT delete this line. -->

-   **Counting non-crossing chords in a circle**: there are $2n$ points on a circle. The number of ways to join them in pairs so that the resulting $n$ segments do not cross each other is $C_n$.

    ??? note "Proof"
        Let $T_n$ be the number of ways for $2n$ points. Label the $2n$ points clockwise as $1,2,\ldots,2n$. Since no two chords cross, point $1$ can only be joined to an even-numbered point; otherwise, the odd number of points between the two could not be paired up without crossing the chord between them. If $1$ is joined to $2k~(k\in[1,n])$, then there are $2k-2$ points on the left side and $2n-2k$ points on the right side, so by the multiplication principle there are $T_{k-1}T_{n-k}$ such ways. So, enumerating $k$, we have $T_n = \sum_{k=1}^n T_{k-1} T_{n-k}$. Setting $k=i+1$ gives the Catalan recurrence. Since $T_0=1$, we get $T_n=C_n$.

    <!-- To make bot happy. Do NOT delete this line. -->

-   **Counting triangulations**: the number of ways to divide a convex $(n+2)$-gon into triangles using non-crossing diagonals is $C_n$.

    ??? note "Proof"
        Let $T_n$ be the number of triangulations of an $(n+2)$-gon. First fix an edge $(1,n+2)$ as the base edge. It must belong to some triangle; call the third vertex of that triangle $k~(k\in[2,n+1])$. This splits the original convex polygon into three parts:
        
        -   The triangle $(1,k,n+2)$.
        -   A $k$-gon with vertices $1\sim k$.
        -   An $(n+3-k)$-gon with vertices $k\sim (n+2)$.
        
        The last two parts are both subproblems, so we get the recurrence
        
        $$
        T_n = \sum_{k=2}^{n+1} T_{k-2}T_{n+1-k}.
        $$
        
        Setting $k=i+2$ gives the Catalan recurrence. Since $T_0=T_1=1$, we get $T_n=C_n$.

    <!-- To make bot happy. Do NOT delete this line. -->

-   **Counting binary trees**: the number of binary trees with $n$ nodes, distinct in shape, is $C_n$. Equivalently, the number of full binary trees with $n$ non-leaf nodes, distinct in shape, is $C_{n}$.

    ??? note "Proof"
        Let $T_n$ be the number of binary trees with $n$ nodes. Take a root node and enumerate the sizes of the left and right subtrees. If the left subtree has size $i\in[0,n-1]$, then the right subtree has size $(n-1-i)$. Both subtrees are subproblems, so we get the recurrence
        
        $$
        T_n = \sum_{i=0}^{n-1}T_iT_{n-1-i}.
        $$
        
        This is exactly the Catalan recurrence. Since $T_0=T_1=1$, we get $T_n=C_n$.

    <!-- To make bot happy. Do NOT delete this line. -->

-   **Counting bracket sequences**: the number of valid bracket sequences made of $n$ pairs of brackets is $C_n$.

    ??? note "Proof"
        Relate this to the lattice path problem. Treat a left bracket as a step up and a right bracket as a step right. A bracket sequence is valid when, at every position, the number of left brackets so far is at least the number of right brackets. In the path problem, this means that at every moment the number of up steps is at least the number of right steps. So there is a bijection between valid bracket sequences and valid paths, and the number of valid bracket sequences is also $C_n$.

    <!-- To make bot happy. Do NOT delete this line. -->

-   **Counting stack pop sequences**: the push order of a stack (of unlimited size) is $1,2,3, \ldots ,n$. The number of valid pop sequences is $C_n$.

    ??? note "Proof"
        Relate this to the bracket sequence problem. Treat a push as a left bracket and a pop as a right bracket. At every moment, the number of pushes is at least the number of pops. So there is a bijection between valid pop sequences and valid bracket sequences, and the number of valid pop sequences is also $C_n$.

    <!-- To make bot happy. Do NOT delete this line. -->

-   **Counting sequences**: among the sequences $a_1,a_2, \ldots ,a_{2n}$ made of $n$ copies of $+1$ and $n$ copies of $-1$, the number whose partial sums satisfy $a_1+a_2+ \ldots +a_k \geq 0~(k=1,2,3, \ldots ,2n)$ is $C_n$.

    ??? note "Proof"
        Relate this to the bracket sequence problem. Treat $+1$ as a left bracket and $-1$ as a right bracket. At every moment, the number of $+1$s is at least the number of $-1$s. So there is a bijection between valid sequences and valid bracket sequences, and the number of valid sequences is also $C_n$.

Although this recurrence is widely used, computing it directly is slow, so we want simpler formulas.

## Common forms

The Catalan numbers have the following common expressions:

$$
C_n = \frac{1}{n+1}\binom{2n}{n} = \dfrac{(2n)!}{n!(n+1)!},~ n\ge 0. \tag{2}
$$

$$
C_n = \binom{2n}{n} - \binom{2n}{n+1},~n \ge 0. \tag{3}
$$

$$
C_n = \frac{(4n-2)}{n+1}C_{n-1},~ n > 0,~ C_0 = 1. \tag{4}
$$

All these forms of the Catalan numbers can be computed efficiently: the first two turn the problem into computing factorials and binomial coefficients, and the third gives a recurrence for computing the terms one after another.

For these three common forms, this page gives two kinds of proofs.

### Algebraic derivation

Deriving these expressions for the Catalan numbers algebraically takes two steps. First, check that the three forms are equivalent to each other.

??? note "Proof that expressions $(2)\sim(4)$ are equivalent"
    We only need to show that expression $(3)$ can be turned into the factorial form in expression $(2)$:
    
    $$
    \begin{aligned}
    C_n &= \binom{2n}{n} - \binom{2n}{n+1} \\
    &= \frac{(2n)!}{n!n!} - \frac{(2n)!}{(n-1)!(n+1)!} \\
    &= \frac{(2n)!}{n!n!}\left(1 - \frac{n!}{(n-1)!(n+1)}\right) \\
    &= \frac{(2n)!}{n!n!}\left(1- \frac{n}{n+1}\right) \\
    &= \dfrac{(2n)!}{n!(n+1)!}.
    \end{aligned}
    $$
    
    Also, expression $(4)$ can be turned into the factorial form in expression $(2)$:
    
    $$
    C_n = \prod_{i=1}^n\frac{(4i-2)}{i+1} = \prod_{i=1}^n\frac{2i(2i-1)}{i(i+1)} = \dfrac{(2n)!}{n!(n+1)!}.
    $$
    
    So the three expressions are equivalent to each other.

Next, check that these forms really solve the Catalan recurrence. To do this, we use generating functions to solve recurrence $(1)$ directly.

??? note "Solving recurrence $(1)$ with generating functions"
    Consider the ordinary generating function of the Catalan numbers, $C(x)=\sum_{n=0}^{\infty}C_nx^n$. The Catalan recurrence looks a lot like a convolution, so we use convolution to build an equation for $C(x)$:
    
    $$
    \begin{aligned}
    C(x)&=\sum_{n=0}^{\infty}C_nx^n\\
    &=1+\sum_{n=1}^{\infty}\left(\sum_{i=0}^{n-1}C_iC_{n-i-1}\right)x^{n}\\
    &=1+x\sum_{n=1}^{\infty}\sum_{i=0}^{n-1}C_ix^iC_{n-i-1}x^{n-i-1}\\
    &=1+x\sum_{i=0}^{\infty}C_ix^i\sum_{j=0}^{\infty}C_jx^j\\
    &=1+xC^2(x).
    \end{aligned}
    $$
    
    Here the second-to-last equality swaps the order of summation and sets $j=n-1-i$. Solving gives:
    
    $$
    C(x)=\dfrac{1\pm \sqrt{1-4x}}{2x} = \frac{2}{1\mp \sqrt{1-4x}}.
    $$
    
    From the initial condition $C_0=1$, we know $C(0)=1$. Checking both roots shows that the only valid solution is
    
    $$
    C(x) = \dfrac{1- \sqrt{1-4x}}{2x}.
    $$
    
    Next, we need to expand it as a power series. Using the [power series expansion](../poly/intro.md#常见的幂级数展开式) of $(1+x)^a$, we get:
    
    $$
    \sqrt{1-4x} = \sum_{n=0}^{\infty} \dfrac{\left(\frac{1}{2}\right)_{-n}}{n!}(-4x)^n,
    $$
    
    Here $\left(\dfrac{1}{2}\right)_{-n}$ is a falling factorial power:
    
    $$
    \begin{aligned}
    \left(\frac{1}{2}\right)_{-n} &= \prod_{k=0}^{n-1}\left(\dfrac{1}{2}-k\right) = \dfrac{1}{2^n}\prod_{k=1}^{n-1}(1-2k) = \dfrac{(-1)^{n-1}}{2^n}\prod_{k=1}^{n-1}(2k-1)\\
    &= \dfrac{(-1)^{n-1}}{2^{2n-1}}\prod_{k=1}^{n-1}\dfrac{(2k-1)2k}{k} = \dfrac{(-1)^{n-1}}{2^{2n-1}}\dfrac{(2n-2)!}{(n-1)!}.
    \end{aligned}
    $$
    
    Substituting into the expression for $C(x)$, we have
    
    $$
    \begin{aligned}
    C(x) &= \dfrac{1}{2x}\left(1-\sum_{n=0}^{\infty} \dfrac{\left(\frac{1}{2}\right)_{-n}}{n!}(-4x)^n\right)\\
    &= -\dfrac{1}{2x}\sum_{n=1}^\infty \dfrac{(-4x)^n}{n!}\left(\frac{1}{2}\right)_{-n} \\
    &= -\dfrac{1}{2x}\sum_{n=1}^\infty \dfrac{(-4x)^n}{n!}\dfrac{(-1)^{n-1}}{2^{2n-1}}\dfrac{(2n-2)!}{(n-1)!} \\
    &= \sum_{n=1}^{\infty}\dfrac{(2n-2)!}{(n-1)!n!}x^{n-1}\\
    &= \sum_{n=0}^{\infty}\dfrac{(2n)!}{n!(n+1)!}x^n.
    \end{aligned}
    $$
    
    This gives expression $(2)$ for $C_n$.

### Combinatorial meaning

Since the Catalan numbers have a clear combinatorial meaning, these forms can also be proved using only combinatorial counting. This section gives a combinatorial proof for each of the three expressions.

??? note "Proof of expression $(2)$"
    Consider the sequence counting problem. For any sequence $\{a_i\}_{i=1}^{2n}$ of $\pm 1$s, define its partial sums as $S_i = \sum_{j=1}^{i}a_i$, and define its **exceedance** as the number of indices with $S_i < 0$ and $a_i = -1$. An exceedance of $0$ means exactly that the sequence is valid. The exceedance ranges over $[0,n]$, so it has $(n+1)$ possible values. We need to show that the number of sequences is the same for every exceedance value.
    
    To do this, we build a map $f$ from sequences with exceedance $e > 0$ to sequences with exceedance $(e-1)$. For a sequence $\{a_i\}$ with exceedance $e > 0$, let $k$ be the smallest index with $S_i = 0$ and $a_i = +1$. Swapping the parts of the sequence to the left and right of $a_k$ gives the following sequence $\{a'_i\}$:
    
    $$
    a_{k+1},a_{k+2},\cdots,a_{2n},a_k,a_{1},a_{2},\cdots,a_{k-1}.
    $$
    
    The part to the right of $a_k$ in the original sequence keeps the same partial sums after the swap, so its contribution to the exceedance does not change. For the part to the left of $a_k$ in the original sequence, all partial sums go up by $1$ after the swap, so its contribution to the exceedance goes down, and the decrease is exactly the number of indices in the part to the left of $a_k$ in the original sequence with $S_i=-1$ and $a_i=-1$. The choice of $a_k$ guarantees there is exactly one such index, so the exceedance of $\{a'_i\}$ is $(e-1)$. In other words, the map $f$ lowers the exceedance of a sequence by exactly $1$.
    
    The map $f$ is invertible. Note that in $\{a'_i\}$, the position of $a_k$ is exactly the largest index with $S'_k=+1$ and $a'_i = +1$. This is because after the swap, those partial sums are each exactly $1$ larger than before, so a partial sum of $+1$ now corresponds to a partial sum of $0$ before the swap. But by the choice of $k$, that part before the swap (the part to the left of $a_k$ in the original sequence) has no index with $S_i = 0$ and $a_i = +1$.
    
    So the map $f$ is a bijection between sequences with exceedance $e>0$ and sequences with exceedance $(e-1)$. This shows that the number of sequences is the same for every exceedance value. Since there are $\dbinom{2n}{n}$ sequences in total, the number of valid sequences (those with exceedance $0$) is
    
    $$
    C_n = \dfrac{1}{n+1}\dbinom{2n}{n}.
    $$
    
    This proves expression $(2)$ for the Catalan numbers.

??? note "Proof of expression $(3)$"
    Consider the lattice path problem. This is a classic lattice path counting problem that can be solved with the reflection principle. Here, we subtract the number of invalid paths from the total number of paths. A path takes $2n$ steps in total, $n$ of which go right, so there are $\dbinom{2n}{n}$ paths in total. A path is invalid if and only if it touches the line $y = x+1$. For any invalid path, find the first point where it touches $y = x+1$, and reflect the part of the path after that point across the line $y=x+1$. Then an invalid path from $(0,0)$ to $(n,n)$ becomes a path from $(0,0)$ to $(n-1,n+1)$.
    
    ![catalan1](./images/catalan-1.svg)
    
    Every path from $(0,0)$ to $(n-1,n+1)$ must cross the line $y = x+1$, so each such path corresponds to an invalid path from $(0,0)$ to $(n,n)$. Counting as for the total, the number of invalid paths is $\dbinom{2n}{n+1}$. So the total number of valid paths is
    
    $$
    C_n = \binom{2n}{n} - \binom{2n}{n+1}.
    $$
    
    This is expression $(3)$ for the Catalan numbers.

??? note "Proof of expression $(4)$"
    Consider the triangulation counting problem. Let $P$ be a convex $(n+2)$-gon, and fix one of its edges as the base edge. For each triangulation of $P$, we can choose one non-base edge (including the edges added by the triangulation), mark it, and give it a direction. This gives $(4n+2)C_n$ ways to triangulate and then mark. Now let $Q$ be a convex $(n+3)$-gon, again with one edge fixed as the base edge. For $Q$, we can choose one non-base edge to mark, and then triangulate. This gives $(n+2)C_{n+1}$ ways to mark and then triangulate.
    
    ![](./images/catalan-triangulation.svg)
    
    As the figure shows, there is an obvious bijection between the results of these two procedures. Given a triangulated and marked $P$, expand its marked edge into a triangle, expand the endpoint that the direction points to into a new edge, and mark this new edge; this gives a marked and triangulated $Q$. Given a marked and triangulated $Q$, shrink its marked edge into a single vertex, and mark the diagonal produced by the shrinking, directed toward the shrunken vertex; this gives a triangulated and marked $P$. So
    
    $$
    (4n+2)C_n = (n+2)C_{n+1}.
    $$
    
    Rearranging a little and using $C_0=1$ gives expression $(4)$ for the Catalan numbers.

## Example problem

???+ example "[Luogu P1044 Stack](https://www.luogu.com.cn/problem/P1044)"
    The push order is $1,2,\ldots ,n$. Find the total number of possible pop orders.

??? note "Reference code"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/combinatorics/catalan/catalan_1.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/combinatorics/catalan/catalan_1.py"
        ```

## Exercises

-   [Luogu P2532 \[AHOI2012\] Tree House Staircase](https://www.luogu.com.cn/problem/P2532)
-   [Luogu P1641 \[SCOI2010\] Generating Strings](https://www.luogu.com.cn/problem/P1641)
-   [Luogu P3200 \[HNOI2009\] Interesting Sequence](https://www.luogu.com.cn/problem/P3200)
-   [AtCoder Beginner Contest 205 E - White and Black Balls](https://atcoder.jp/contests/abc205/tasks/abc205_e)
-   [AtCoder Regular Contest 145 C - Split and Maximize](https://www.luogu.com.cn/problem/AT_arc145_c)
-   [Luogu P5014 Water Triangle (Modified Version)](https://www.luogu.com.cn/problem/P5014)
-   [Luogu P3978 \[TJOI2015\] Probability Theory](https://www.luogu.com.cn/problem/P3978)

## References and notes

-   [Catalan number - Wikipedia](https://en.wikipedia.org/wiki/Catalan_number)
