Bézout's theorem reveals a deep connection between the greatest common divisor and integer linear combinations. It is one of the most basic and most important results in number theory. Building on it, this page also discusses how to solve linear Diophantine equations.

## Bézout's theorem

**Bézout's theorem** (Bézout's lemma), also called Bézout's identity, gives a necessary and sufficient condition for an integer to be expressible as an integer linear combination of two integers.

???+ note "Bézout's theorem"
    Let $a,b$ be integers that are not both zero. Then for all integers $x,y$, $\gcd(a,b)\mid ax+by$; moreover, there exist integers $x,y$ such that $ax+by=\gcd(a,b)$.

??? note "Proof"
    Let $d=\gcd(a,b)$. Since $d\mid a,b$, there exist integers $u,v$ such that $a=du,~b=dv$. Therefore we always have
    
    $$
    ax + by = d(ux+vy).
    $$
    
    This shows $d\mid ax+by$.
    
    Conversely, we need to show that there exist $x,y$ for which equality holds. Since $\gcd(a,b)=\gcd(-a,b)=\gcd(a,-b)$, we may assume $a,b$ are both nonnegative. If one of $a,b$ is $0$, say $b=0$, then their greatest common divisor is $d=a$, and clearly $(x,y)=(1,0)$ works. Next, consider the case where neither $a$ nor $b$ is zero, so both are positive.
    
    Consider the steps of the Euclidean algorithm:
    
    $$
    \begin{aligned}
    a   &= q_1b   + r_1, && 0\le r_1 < b,\\
    b   &= q_2r_1 + r_2, && 0\le r_2 < r_1,\\
    r_1 &= q_3r_2 + r_3, && 0\le r_3 < r_2,\\
        & \cdots \\
    r_{n-3} &= q_{n-1}r_{n-2} + r_{n-1}, && 0\le r_{n-1} < r_{n-2},\\
    r_{n-2} &= q_nr_{n-1} + r_n,         && 0\le r_n     < r_{n-1},\\
    r_{n-1} &= q_{n+1}r_n.
    \end{aligned}
    $$
    
    Since the greatest common divisor is $d$, the last step of the algorithm must have $r_n=d$. So the second-to-last equation can be written as
    
    $$
    d = r_n = r_{n-2} - q_nr_{n-1}.
    $$
    
    From the third-to-last equation, solve for
    
    $$
    r_{n-1} = r_{n-3} - q_{n-1}r_{n-2}
    $$
    
    and substitute it into the equation above to eliminate $r_{n-1}$:
    
    $$
    \begin{aligned}
    d &= r_{n-2} - q_n(r_{n-3} - q_{n-1}r_{n-2}) \\
    &= (1 + q_nq_{n-1})r_{n-2} - q_nr_{n-3}.
    \end{aligned}
    $$
    
    In the same way, we can eliminate $r_{n-2},r_{n-3},\cdots,r_2,r_1$ one by one, and finally get
    
    $$
    d = xa + yb.
    $$
    
    This proves that there exist $x,y$ with $ax+by=d$. By the analysis above, this also proves the original statement.

The existence proof here is constructive: it also gives a way to compute the coefficients. This method is the [extended Euclidean algorithm](./gcd.md#extended-euclidean-algorithm).

Looking at the special case $\gcd(a,b)=1$ of Bézout's theorem gives the following corollary:

???+ note "Corollary"
    Integers $a,b$ are coprime if and only if there exist integers $x,y$ such that $ax+by=1$.

### More than two integers

Bézout's theorem extends to more than two integers.

???+ note "Theorem"
    Let $a_1,a_2,\cdots,a_n$ be integers that are not all zero. Then for all integers $x_1,x_2,\cdots,x_n$, $\gcd(a_1,a_2,\cdots,a_n)\mid a_1x_1+a_2x_2+\cdots+a_nx_n$; moreover, there exist integers $x_1,x_2,\cdots,x_n$ such that $\gcd(a_1,a_2,\cdots,a_n)=a_1x_1+a_2x_2+\cdots+a_nx_n$.

??? note "Proof"
    Use $\gcd(a_1,a_2,\cdots,a_n)=\gcd(\gcd(a_1,a_2,\cdots,a_{n-1}),a_n)$ and induct on $n$.

### Example problem

???+ example "[Codeforces 510 D. Fox And Jumping](https://codeforces.com/problemset/problem/510/D)"
    There are $n\le 300$ cards; card $i$ has values $l_i$ and $c_i$. On an infinitely long tape, you may pay $c_i$ to buy card $i$; after that, you can jump $l_i$ units left or right any number of times. Find the minimum total cost needed to be able to reach every position on the tape. If it is impossible, output $-1$.

??? note "Solution"
    To reach every cell, the chosen numbers $l_{i_1}, \cdots, l_{i_k}$ must be able to produce absolute value $1$ through repeated additions and subtractions. That is, there must exist integers $x_1, \cdots, x_k$ with $l_{i_1} x_1 + \cdots + l_{i_k} x_k = 1$. By Bézout's theorem for several integers, this means choosing some numbers from $l_1, \cdots, l_n$ whose greatest common divisor is $1$, with the minimum total cost.
    
    **Solution 1**: Treat the minimum total cost as a shortest path problem and solve it with Dijkstra's algorithm. Each vertex stores a current value of the greatest common divisor. The start vertex is $0$ and the target vertex is $1$. Each step goes from the current vertex $x$ along an edge of length $c_i$ to vertex $\gcd(x,l_i)$. The time complexity of this algorithm is $O(n^2\log n)$.
    
    **Solution 2**: Choosing some numbers from $l_1, \cdots, l_n$ with greatest common divisor $1$ and minimum total cost suggests the 0-1 knapsack problem.
    
    Let $f_{i, j}$ be the minimum cost when considering the first $i$ numbers with greatest common divisor $j$. The transition is:
    
    $$
    f_{i, j} = \min\left\{f_{i - 1, j},~\min_{\gcd(k, l_i) = j}\{f_{i - 1, k} + c_i\}\right\}.
    $$
    
    After the DP, the answer is $f_{n, 1}$.
    
    As in the usual 0-1 knapsack problem, a rolling array removes the first dimension. Also, the possible greatest common divisors $j$ formed by 300 numbers are very sparse, so they can be stored in a hash table.
    
    In fact, the graph built in Solution 1 is exactly the state transition graph of the DP in Solution 2. Solution 2 amounts to finding a shortest path in a directed acyclic graph with dynamic programming, so the two solutions are equivalent. But Solution 2 does not need to store the whole graph, and the DP runs in $O(n + m)$ time (where $m$ is the number of edges in the state transition graph), which is faster than Dijkstra's algorithm. So Solution 2 is better in both time and space.

## Linear Diophantine equations

A **linear Diophantine equation** is an equation of the form

$$
a_1x_1 + a_2x_2 + \cdots + a_nx_n = b
$$

where $a_1,a_2,\cdots,a_n$ are all integers. The goal of this section is to find all of its integer solutions.

### Two variables

First consider the linear Diophantine equation in two variables:

$$
a_1x_1 + a_2x_2 = b.
$$

Bézout's theorem says this equation has a solution if and only if

$$
d = \gcd(a_1,a_2) \mid b.
$$

From now on, assume this condition holds. The extended Euclidean algorithm gives an integer solution $(x_1^*,x_2^*)$ of $a_1x_1 + a_2x_2 = d$. From it we get a particular solution of the original equation:

$$
(x_1^\circ,x_2^\circ) = \left(\frac{b}{d}x_1^*,\frac{b}{d}x_2^*\right).
$$

To get all solutions, subtract the identity $a_1x_1^\circ+a_2x_2^\circ = b$ from the original equation:

$$
a_1(x_1 - x_1^\circ) + a_2(x_2 - x_2^\circ) = 0.
$$

This is a homogeneous linear Diophantine equation in $(x_1-x_1^\circ,x_2-x_2^\circ)$, whose general solution is

$$
(x_1-x_1^\circ,x_2-x_2^\circ) = \left(t\dfrac{a_2}{d},-t\dfrac{a_1}{d}\right).\quad(t\in\mathbf Z)
$$

So the general solution of the original equation is

$$
(x_1,x_2) = \left(x_1^\circ + t\dfrac{a_2}{d},x_2^\circ - t\dfrac{a_1}{d}\right).\quad(t\in\mathbf Z)
$$

These are evenly spaced lattice points on the line $a_1x_1+a_2x_2 = b$.

### More than two variables

Once the two-variable case is solved, the general case is easy. For the linear Diophantine equation in $n$ variables

$$
a_1x_1 + a_2x_2 + \cdots + a_nx_n = b,\quad (n>2)
$$

Bézout's theorem says it has a solution if and only if

$$
\gcd(a_1,a_2,\cdots,a_n) \mid b.
$$

As in the two-variable case, the general solution of a linear Diophantine equation in several variables can also be written in the form

$$
(x_1^\circ,x_2^\circ,\cdots,x_n^\circ) + \sum_{k=1}^{n-1} t_k(x_1^{(k)},x_2^{(k)},\cdots,x_n^{(k)})
$$

where $x^\circ$ is a particular solution and the $x^{(k)}$ are $(n-1)$ linearly independent solutions of the corresponding homogeneous equation.

To find the general solution explicitly, reduce the equation in $n$ variables to one in $(n-1)$ variables. Let $d_1 = \gcd(a_1,a_2)$. By Bézout's theorem, the values of $a_1x_1+a_2x_2$ are exactly all multiples of $d_1$. So we can first solve the linear Diophantine equation in $(n-1)$ variables:

$$
d_1y_1 + a_3x_3 + a_4x_4 + \cdots + a_nx_n = b.
$$

Suppose its general solution is

$$
\begin{aligned}
y_1 &= y_1^\circ + \sum_{k=2}^{n-1}t_ky_1^{(k)}, \\
x_i &= x_i^\circ + \sum_{k=2}^{n-1}t_kx_i^{(k)},\quad i=3,\cdots,n.
\end{aligned}
$$

Let $(x_1^*,x_2^*)$ be a particular solution of $a_1x_1+a_2x_2=d_1$. By the previous section, the general solution of the two-variable equation $a_1x_1+a_2x_2=d_1y_1$ in $x_1,x_2$ is

$$
x_1 = x_1^*y_1 + t_1\dfrac{a_2}{d_1},~x_2 = x_2^*y_1 - t_1\dfrac{a_1}{d_1}.
$$

Substituting the expression for $y_1$ gives the general solution of the original equation:

$$
\begin{aligned}
x_1 &= x_1^*y_1^\circ + t_1\dfrac{a_2}{d_1} + \sum_{k=2}^{n-1}t_kx_1^*y_1^{(k)}, \\
x_2 &= x_2^*y_1^\circ - t_1\dfrac{a_1}{d_1} + \sum_{k=2}^{n-1}t_kx_2^*y_1^{(k)}, \\
x_i &= x_i^\circ + \sum_{k=2}^{n-1}t_kx_i^{(k)},\quad i=3,\cdots,n.
\end{aligned}
$$

## Frobenius coin problem

Bézout's theorem gives a necessary and sufficient condition for an integer to be a linear combination of some given integers. Closely related is the **Frobenius coin problem**:

-   If there are coins of integer denominations $a_1,a_2,\cdots,a_n$ with $\gcd(a_1,a_2,\cdots,a_n)=1$, what is the largest integer that cannot be made from these coins?

Both ask when an integer $k$ can be written as $a_1x_1+a_2x_2+\cdots+a_nx_n$. In Bézout's theorem the $x_i$ can be any integers, while in the Frobenius coin problem the $x_i$ must be natural numbers.

The case of a single coin is trivial: we must have $a_1=1$, and every natural number can be made from it. The case $n>2$ is too complicated, so this section only discusses $n=2$.

### Sylvester's theorem

In 1882, Sylvester completely solved the Frobenius coin problem for $n = 2$:

???+ note "Theorem (Sylvester)"
    For coprime positive integers $a_1,a_2$, the largest integer that cannot be written as $a_1x_1+a_2x_2~(x_1,x_2\in\mathbf N)$ is $C = a_1a_2 - a_1 - a_2$. Moreover, for every $k\in\mathbf Z$, exactly one of $k$ and $C-k$ can be written in this form.

For convenience, an integer that can be written as $a_1x_1+a_2x_2~(x_1,x_2\in\mathbf N)$ is called **representable**.

??? note "Proof 1"
    Since $a_1,a_2$ are coprime, for any integer $k$ the equation $a_1x_1+a_2x_2=k$ always has a solution, with general solution
    
    $$
    (x_1,x_2) = (x_1^\circ + ta_2, x_2^\circ - ta_1).\quad(t\in\mathbf Z)
    $$
    
    Take $t$ to be the quotient of $x_2^\circ$ divided by $a_1$ (division with remainder). Then the remainder $x_2 = x_2^\circ-ta_1$ lies between $0$ and $a_1-1$. Look at the resulting solution $(x_1,x_2)$. Since $x_2$ is the smallest nonnegative value it can take, $k$ is representable if and only if $x_1\ge 0$.
    
    **Step 1**: Show that every integer greater than $C$ is representable.
    
    When $k > C$,
    
    $$
    a_1x_1 = k - a_2x_2 > C - a_2(a_1-1) = -a_1.
    $$
    
    So $x_1 > -1$, that is, $x_1\ge 0$. This means $(x_1,x_2)$ is a solution in natural numbers, so $k$ can be written in the required form.
    
    **Step 2**: Show that $C$ is not representable. Consequently, $C$ is the largest non-representable integer, and $k$ and $C-k$ are not both representable.
    
    By contradiction. Suppose $C$ is representable, that is, there exist $x_1,x_2\in\mathbf N$ with $a_1x_1+a_2x_2=C$. Substituting the expression for $C$ gives
    
    $$
    a_1a_2 = a_1(x_1+1) + a_2(x_2+1).
    $$
    
    Hence $a_2\mid (x_1+1)$ and $a_1\mid (x_2+1)$. Since $x_1+1,x_2+1$ are both positive, we get
    
    $$
    a_1a_2 \ge a_1a_2 + a_2a_1 = 2a_1a_2.
    $$
    
    This is a contradiction, so $C$ is not representable. Together with Step 1, it is the largest non-representable integer.
    
    If both $k$ and $C-k$ were representable, adding the coefficients of their representations would give a representation of $C$, contradicting the fact that $C$ is not representable. So at most one of $k$ and $C-k$ is representable.
    
    **Step 3**: Show that if $k$ is not representable, then $C-k$ is representable.
    
    Let $(x_1,x_2)$ be the integer solution of $a_1x_1+a_2x_2=k$ chosen above. As shown earlier, $k$ being non-representable is equivalent to $x_1<0$. Therefore
    
    $$
    C - k = a_1a_2 - a_1 - a_2 - a_1x_1 - a_2x_2 = a_1(-1-x_1) + a_2(a_1-1-x_2).
    $$
    
    Here $-1-x_1$ and $a_1-1-x_2$ are both nonnegative integers, so $C-k$ is representable.

??? note "Proof 2"
    Here we only prove that $C=a_1a_2-a_1-a_2$ is the largest non-representable integer; the rest of the proof is similar to Proof 1.
    
    Modulo $a_2$, consider the smallest representable natural number in each residue class. Different natural numbers in the same residue class can be turned into each other by adding or subtracting multiples of $a_2$, so when looking for the smallest representable number, we only need to consider adding multiples of $a_1$. Since $a_1$ and $a_2$ are coprime, the smallest representable natural numbers in the residue classes are exactly the multiples of $a_1$
    
    $$
    0,~a_1,~2a_1,~\cdots,~(a_2-1)a_1.
    $$
    
    So the largest non-representable number is
    
    $$
    \max_{0\le i < a_2} ia_1 - a_2 = (a_2-1)a_1 - a_2 = C.
    $$

### Geometric meaning

View the equation $a_1x_1 + a_2x_2 = k$ as a line. Then $k$ is representable if and only if this line passes through at least one lattice point in the first quadrant (including the axes). When $k < a_1a_2$, the line passes through at most one lattice point in the first quadrant. So for $0\le k < a_1a_2$, the integer $k$ is representable if and only if the line passes through exactly one lattice point in the first quadrant.

Therefore, for $k < a_1a_2$, the number of representable natural numbers not exceeding $k$ equals the number of lattice points in the first quadrant on or below the line $a_1x_1 + a_2x_2 = k$ (including points on the boundary). This number is

$$
\sum_{i=0}^{\lfloor k / a_1 \rfloor} \left(\left\lfloor\dfrac{k-ia_1}{a_2}\right\rfloor+1\right).
$$

This is the classic problem of counting lattice points under a line, which can be solved in $O(\log\min\{a_1,a_2,k\})$ time with the [floor sum (Euclidean-like) algorithm](./euclidean.md#euclidean-like-algorithm).

### Exercises

-   [Luogu P3951 NOIP 2017 Senior Group — Xiaokai's Puzzle / Lanqiao Cup 2013 Provincial — The Number You Can't Buy](https://www.luogu.com.cn/problem/P3951)
