Prerequisites: [continued fractions](./continued-fraction.md), [quadratic fields](./quadratic.md)

## Introduction

This page discusses how to solve the (generalized) Pell equation. The generalized Pell equation is the Diophantine equation in $x$ and $y$

$$
x^2-Dy^2=N,
$$

where $D$ is a positive integer that is not a perfect square[^not-square], and $N$ is a nonzero integer. The Pell equation in the narrow sense refers to the special case $N=1$ or $N=\pm 1$, and sometimes also $N=\pm 4$. The generalized Pell equation is closely related to finding quadratic integers of norm $N$ in a real quadratic integer ring, and the cases often called the (narrow-sense) Pell equation can be seen as finding units in a real quadratic integer ring.

When this page says "Pell equation", it means the case $N=1$. Correspondingly, the case $N=-1$ is called the negative Pell equation[^neg-pell] (negative Pell's equation).

## Structure of the solutions

Integer solutions $(x,y)$ of the generalized Pell equation are closely tied to the quadratic integer $x+y\sqrt{D}$, so in the literature solutions of the Pell equation are often written as $x+y\sqrt{D}$. Since the norm of a quadratic integer is

$$
N(x+y\sqrt{D}) = x^2-Dy^2,
$$

the generalized Pell equation roughly amounts to finding quadratic integers of norm $N$. But there is a subtle difference. When $x$ and $y$ are both integers, $x+y\sqrt{D}$ is always a quadratic integer; conversely, a quadratic integer does not require $x$ and $y$ to be integers: when $D\equiv 1\pmod 4$, $x$ and $y$ can also both be half-integers[^half-int].

This difference matters a lot when finding the fundamental unit. A unit in a quadratic integer ring is a quadratic integer of norm $\pm 1$. For $D\equiv 2,3\pmod 4$, to find such units you only need to solve the generalized Pell equation with $N=\pm 1$; but for $D\equiv 1\pmod 4$, you also need to consider $N=\pm 4$. How to find units is discussed [below](#the-case-of-norm-4).

To understand the structure of solutions of the generalized Pell equation, start from [Brahmagupta's identity](https://en.wikipedia.org/wiki/Brahmagupta%27s_identity):

$$
(x_1^2-Dy_1^2)(x_2^2-Dy_2^2)=(x_1x_2+Dy_1y_2)^2-D(x_1y_2+x_2y_1)^2.
$$

It says that the norm of quadratic integers is multiplicative, that is,

$$
\begin{aligned}
N\left(x_1+y_1\sqrt{D}\right)N\left(x_2+y_2\sqrt{D}\right) &= N\left((x_1+y_1\sqrt{D})(x_2+y_2\sqrt{D})\right) \\
&= N\left((x_1x_2+Dy_1y_2)+(x_1y_2+x_2y_1)\sqrt{D}\right).
\end{aligned}
$$

With this identity, integer solutions of $x^2-Dy^2=N_1$ and of $x^2-Dy^2=N_2$ can be combined into an integer solution of $x^2-Dy^2=N_1N_2$. Of course, from the viewpoint of quadratic integers, combining solutions is just multiplying quadratic integers, which shows why it is convenient to write solutions of the Pell equation as quadratic integers. In particular, taking $N_1=N$ and $N_2=1$, we see that if we know one solution of $x^2-Dy^2=N$ and all solutions of the corresponding Pell equation $x^2-Dy^2=1$, we get more solutions of $x^2-Dy^2=N$. This method does not necessarily produce all solutions. But it at least shows that understanding the structure of the solutions of the Pell equation is important for understanding those of the generalized Pell equation.

### Pell equation

Geometrically, the equation $x^2-Dy^2=1$ is a hyperbola whose real axis is the $x$-axis and whose imaginary axis is the $y$-axis. Each point on the hyperbola corresponds to exactly one nonzero value of $x+y\sqrt{D}$: the left branch corresponds to negative values of $x+y\sqrt{D}$, and the right branch to positive values. Moreover, on each branch, the value of $x+y\sqrt{D}$ strictly increases from bottom to top. So the value of the quadratic integer gives the solutions of the Pell equation a natural order.

The hyperbola is symmetric about both the $x$-axis and the $y$-axis, so when discussing solutions of the Pell equation we only need the part in the first quadrant; the other solutions follow by symmetry. This amounts to only considering solutions with $x+y\sqrt{D}>1$. If the equation has nontrivial solutions other than $(\pm 1,0)$, then there must be a solution $(x_1,y_1)$ in the first quadrant with the smallest value of $x+y\sqrt{D}$. It is also the lattice point in the first quadrant (excluding the axes) with the smallest coordinates, and it is called the fundamental solution of the Pell equation[^fundamental-solution]. By the discussion above, every integer pair $(x_k,y_k)$ with $x_k+y_k\sqrt{D}=(x_1+y_1\sqrt{D})^k$ is a solution of the Pell equation, and all of them lie in the first quadrant. Conversely, these are indeed all the solutions of the Pell equation in the first quadrant. Using symmetry, we get the following result:

???+ note "Theorem"
    Let $(x_1,y_1)$ be the fundamental solution of the Pell equation $x^2-Dy^2=1$. Then all its solutions are
    
    $$
    \{(x,y):x+y\sqrt{D}=\pm(x_1+y_1\sqrt{D})^k,k\in\mathbf Z\}.
    $$

??? note "Proof"
    First we show that there are no other solutions in the first quadrant. Suppose there is another solution $x+y\sqrt{D}$ and, for some $k\ge 0$,
    
    $$
    x_k+y_k\sqrt{D}< x+y\sqrt{D}< x_{k+1}+y_{k+1}\sqrt{D}.
    $$
    
    Geometrically, this says that the lattice point $(x,y)$ lies on the hyperbola strictly between $(x_k,y_k)$ and $(x_{k+1},y_{k+1})$. Multiplying the inequality by $x_k-y_k\sqrt{D}=(x_k+y_k\sqrt{D})^{-1}$ gives
    
    $$
    1< (x+y\sqrt{D})(x_k-y_k\sqrt{D})=(xx_k-Dyy_k)+(x_ky-xy_k)\sqrt{D} < x_1+y_1\sqrt{D}.
    $$
    
    By the monotonicity mentioned above, this inequality says that $(xx_k-Dyy_k,x_ky-xy_k)$ is a lattice point between $(1,0)$ and $(x_1,y_1)$. This contradicts the choice of $(x_1,y_1)$.
    
    To extend the first-quadrant solutions to the whole plane: negating the exponent $k$ (that is, taking the reciprocal) reflects about the $x$-axis, and negating the whole value reflects about the origin. Adding the trivial solution for $k=0$, we get all solutions of the Pell equation.

The discussion so far simply assumed that the fundamental solution exists. Now we show that the Pell equation always has a nontrivial solution.

???+ note "Theorem"
    The Pell equation $x^2-Dy^2=1$ always has integer solutions other than $(\pm 1,0)$.

??? note "Proof"
    First, [Dirichlet's theorem](./continued-fraction.md#approximating-real-numbers-by-convergents) says there are infinitely many pairs of positive integers $(x,y)$ such that
    
    $$
    \left|\dfrac{x}{y}-\sqrt{D}\right| \le \dfrac{1}{y^2}
    $$
    
    holds, and they all satisfy the inequality
    
    $$
    |x^2-Dy^2|=y^2\left|\dfrac{x}{y}-\sqrt{D}\right|\left|\dfrac{x}{y}+\sqrt{D}\right| \le \dfrac{1}{y^2}+2\sqrt{D}<1+2\sqrt{D}.
    $$
    
    So there must be an integer $m\in(-1-2\sqrt{D},1+2\sqrt{D})$ such that infinitely many pairs $(x,y)$ satisfy $x^2-Dy^2 = m$. Grouping these $(x,y)$ by their remainders modulo $m$, we see that for some pair of integers $(x_0,y_0)$, there are infinitely many pairs $(x,y)$ with $x\equiv x_0\pmod m$ and $y\equiv y_0\pmod m$. Pick any two distinct such pairs $(x_1,y_1)$ and $(x_2,y_2)$. Then
    
    $$
    \dfrac{x_1+y_1\sqrt{D}}{x_2+y_2\sqrt{D}}=\dfrac{x_1x_2-Dy_1y_2}{m}+\dfrac{x_2y_1-x_1y_2}{m}\sqrt{D}.
    $$
    
    By the congruences we have
    
    $$
    \begin{aligned}
    x_1x_2-Dy_1y_2 &\equiv x_0^2-Dy_0^2 = m \equiv 0 \pmod{|m|},\\
    x_2y_1-x_1y_2 &\equiv x_0y_0-x_0y_0 = 0 \pmod{|m|},
    \end{aligned}
    $$
    
    which shows that the right-hand side above gives an integer solution. Moreover, since $(x_1,y_1)\neq(x_2,y_2)$, it is not trivial. So the Pell equation indeed has a nontrivial solution.

Of course, this section gives a non-constructive proof. When we discuss how to solve the Pell equation below, we will construct its solutions directly from the convergents of a continued fraction, which gives another proof that nontrivial solutions exist. Also, although the structure of the Pell equation's solutions found in this section matches the structure of units of a real quadratic integer ring, for $D\equiv 1\pmod 4$ this section does not fully settle the structure of the units of the corresponding quadratic integer ring; this is discussed further below.

### Generalized Pell equation

The graph of the generalized Pell equation $x^2-Dy^2=N$ is also a hyperbola in the plane, again symmetric about the $x$-axis and the $y$-axis. As pointed out above, some solutions of $x^2-Dy^2=N$ may differ only by a factor that is a solution of the Pell equation, so the solutions of $x^2-Dy^2=N$ can be split into equivalence classes. For two solutions $(x_1,y_1)$ and $(x_2,y_2)$ of $x^2-Dy^2=N$, if there is a solution $(u,v)$ of the Pell equation with $x_2+y_2\sqrt{D}=(x_1+y_1\sqrt{D})(u+v\sqrt{D})$, the solutions $(x_1,y_1)$ and $(x_2,y_2)$ are called equivalent. Two solutions are equivalent if and only if

$$
N\mid (x_1x_2-Dy_1y_2),\ N\mid (x_2y_1-x_1y_2).
$$

Since solutions of the Pell equation are relatively easy to find, a natural idea is to find one solution in each of the equivalence classes above. Once you know these, you can use the solutions of the corresponding Pell equation to get all solutions of the generalized Pell equation. By symmetry, each equivalence class of solutions has a solution whose $y$ coordinate is nonnegative and as small as possible: if this solution is unique, it is called the fundamental solution of that class; otherwise the class has exactly two solutions with the smallest nonnegative $y$, symmetric about the $y$-axis, and the one with $x>0$ is chosen as the fundamental solution. So solving the generalized Pell equation $x^2-Dy^2=N$ amounts to finding its set $U$ of fundamental solutions. Let $(r,s)$ be the fundamental solution of the corresponding Pell equation. Then the set of all solutions of the generalized Pell equation is

$$
\{(x,y):x+y\sqrt{D}=\pm(r+s\sqrt{D})^k(u+v\sqrt{D}),k\in\mathbf Z,u+v\sqrt{D}\in U\}.
$$

The generalized Pell equation always has finitely many fundamental solutions. This is because, by the general solution formula above, the absolute value $|u+v\sqrt{D}|$ must lie between $r-s\sqrt{D}$ and $r+s\sqrt{D}$. The references at the end of the page give tighter bounds on the coordinates of the fundamental solutions. Of course, unlike the Pell equation, the generalized Pell equation may have no solution.

Given one solution $(u,v)$ of the generalized Pell equation and the fundamental solution $(r,s)$ of the Pell equation, besides combining solutions, you can also get all solutions in the same equivalence class with the recurrence

$$
x_{k} = 2rx_{k-1} - x_{k-2},\ y_{k} = 2ry_{k-1} - y_{k-2},
$$

where $x_k+y_k\sqrt{D}=(r+s\sqrt{D})^k(u+v\sqrt{D})$. This is because both $x_k$ and $y_k$ can be written as $A(r+s\sqrt{D})^k+B(r-s\sqrt{D})^k$ for some real pair $(A,B)$, and by Vieta's formulas $r\pm s\sqrt{D}$ are the two real roots of $x^2-2rx+1=0$, so $x_k$ and $y_k$ both satisfy the second-order linear recurrence above. Compared with combining solutions, this recurrence uses fewer multiplications.

## How to solve

Both the Pell equation and the generalized Pell equation can be solved with continued fractions.

### The PQa algorithm

All algorithms on this page are based on the PQa algorithm, which computes the continued fraction expansion of certain quadratic irrationals.

Let integers $P_0,Q_0,D$ satisfy $Q_0\neq 0$, $D>0$ not a perfect square, and $P_0^2\equiv D\pmod{Q_0}$. Then the continued fraction expansion $[a_0,a_1,\cdots]$ of the quadratic irrational

$$
\omega=\dfrac{P_0+\sqrt{D}}{Q_0}
$$

can be computed with the following [recurrence](./continued-fraction.md#quadratic-irrationals):

$$
a_k = \left\lfloor\dfrac{P_k+\sqrt{D}}{Q_k}\right\rfloor,\ P_{k+1} = a_kQ_k - P_k,\ Q_{k+1} = \dfrac{D-P_{k+1}^2}{Q_k}.
$$

Then the numerator $A_k$ and denominator $B_k$ of the $k$-th convergent of $\omega$ are given by the [recurrence](./continued-fraction.md#recurrence)

$$
A_k = a_kA_{k-1} + A_{k-2},\ B_k = a_kB_{k-1} + B_{k-2}
$$

with $A_{-1} = 1$, $A_{-2}=0$, $B_{-1}=0$, $B_{-2}=1$.

These formulas are proved in the continued fractions article. It also shows that, because a quadratic irrational has a [periodic continued fraction](./continued-fraction.md#quadratic-irrationals), the triple $(P_k,Q_k,a_k)$ eventually becomes periodic, so the algorithm always ends in a finite number of steps. Let the minimal period length be $\ell$, and let the earliest start of the period be $k_0$. Then the continued fraction expansion of the quadratic irrational can be written as

$$
\omega=[a_0,\cdots,a_{k_0-1},\overline{a_{k_0},\cdots,a_{k_0+\ell-1}}].
$$

To solve the Pell equation with the PQa algorithm, we need the following result:

???+ note "Theorem"
    Keep the notation above. Let $G_k=Q_0A_k-P_0B_k$. Then the integer pair $(G_{k-1},B_{k-1})$ satisfies
    
    $$
    G_{k-1}^2-DB_{k-1}^2=(-1)^{k}Q_0Q_{k},
    $$
    
    and their greatest common divisor $\gcd(G_{k-1},B_{k-1})$ divides $Q_{k}$.

??? note "Proof"
    Let $\omega_{k}$ be the $k$-th remainder (complete quotient) in the continued fraction expansion of $\omega$, that is,
    
    $$
    \omega = [a_0,a_1,\cdots,a_{k-1},\omega_k] = \dfrac{\omega_k A_{k-1}+A_{k-2}}{\omega_k B_{k-1}+B_{k-2}}.
    $$
    
    Substituting $\omega=(P_0+\sqrt{D})/Q_0$ and $\omega_k=(P_k+\sqrt{D})/Q_k$ into this gives
    
    $$
    \dfrac{P_0+\sqrt{D}}{Q_0} = \dfrac{(P_k+\sqrt{D})A_{k-1}+Q_kA_{k-2}}{(P_k+\sqrt{D})B_{k-1}+Q_kB_{k-2}}.
    $$
    
    Clearing denominators on both sides, comparing the rational and irrational coefficients, and substituting the expression for $G_k$, we get:
    
    $$
    \begin{aligned}
    G_{k-1} &= P_kB_{k-1} + Q_kB_{k-2},\\
    DB_{k-1} &= P_kG_{k-1} + Q_kG_{k-2}.
    \end{aligned}
    $$
    
    So multiplying the first equation by $G_{k-1}$ and subtracting the second multiplied by $B_{k-1}$ gives
    
    $$
    \begin{aligned}
    G_{k-1}^2-DB_{k-1}^2 &= (B_{k-2}G_{k-1}-B_{k-1}G_{k-2})Q_k \\
    &= (A_{k-1}B_{k-2}-B_{k-1}A_{k-2})Q_0Q_k \\
    &= (-1)^kQ_0Q_k.
    \end{aligned}
    $$
    
    The last step uses the [difference formula](./continued-fraction.md#error-estimates) for convergents. This proves the first claim.
    
    To prove the second claim, substitute the expression for $G_k$ into the first claim:
    
    $$
    (Q_0A_{k-1}-P_0B_{k-1})^2 - DB_{k-1}^2 = (-1)^kQ_0Q_k.
    $$
    
    So, using $Q_0\mid(P_0^2-D)$, we get
    
    $$
    Q_0A_{k-1}^2 +\left(\dfrac{P_0^2-D}{Q_0}B_{k-1}- 2P_0A_{k-1}\right)B_{k-1} = (-1)^kQ_k.
    $$
    
    Hence $\gcd(G_{k-1},B_{k-1}) = \gcd(Q_0A_{k-1},B_{k-1})$ divides $Q_k$.

This result gives a way to find solutions of $x^2-Dy^2=N$. If you choose $Q_0>0$ sensibly and choose $P_0$ as a solution of the congruence $P_0^2\equiv D\pmod{Q_0}$, then run the PQa algorithm on $(P_0+\sqrt{D})/Q_0$ until you find $(-1)^kQ_0Q_{k}=N$; at that point $(G_{k-1},B_{k-1})$ is a solution of the original equation. Moreover, if $Q_k=\pm 1$, the solution obtained this way is always primitive, that is, $G_{k-1}$ and $B_{k-1}$ are always coprime.

This idea is the core of solving the Pell equation and the generalized Pell equation. With it in mind, we now work out some details of the algorithm and prove that every solution can be found this way.

### Pell equation

To solve the Pell equation $x^2-Dy^2=1$, just run the PQa algorithm on $(P_0,Q_0,D)=(0,1,D)$ until $(-1)^kQ_k=1$; then $(A_{k-1},B_{k-1})$ is a solution of the Pell equation (because $G_{k-1}$ is then just $A_{k-1}$). Of course, for the Pell equation this process can be described more precisely.

First, the solution always appears at the end of a period. The process above amounts to the continued fraction expansion of $\sqrt{D}$. For it, we already have the [result](./continued-fraction.md#purely-periodic-continued-fractions):

$$
\sqrt{D} = [\lfloor\sqrt{D}\rfloor,\overline{a_1,\cdots,a_{\ell-1},2\lfloor\sqrt{D}\rfloor}].
$$

Here the period length is $\ell$, and the period starts at term $1$ (indices start from $0$). Moreover, its $\ell$-th remainder equals $\lfloor\sqrt{D}\rfloor+\sqrt{D}$, which means $Q_{\ell}=1$. So if $\ell$ is even, $(A_{\ell-1},B_{\ell-1})$ is a nontrivial solution of the Pell equation; if $\ell$ is odd, $(A_{2\ell-1},B_{2\ell-1})$ is a nontrivial solution of the Pell equation.

Next we show that the solution just found is always the fundamental solution. There are two reasons. First, for every positive integer solution $(x,y)$ of the Pell equation, the fraction $x/y$ appears among the convergents of $\sqrt{D}$, which guarantees that $(x,y)$ is some $(A_k,B_k)$ in the PQa algorithm. Second, $Q_k=1$ does not occur anywhere other than at the end of a period, and since the recurrences for $A_k$ and $B_k$ make them grow with the index, the smallest positive integer solution (that is, the fundamental solution) must appear at the position just identified. These two reasons follow from the following two theorems:

???+ note "Theorem"
    Suppose $x^2-Dy^2=N$ has a positive integer solution $(x,y)$. If $|N|<\sqrt{D}$, then $\dfrac{x}{y}$ must be a convergent of $\sqrt{D}$.

??? note "Proof"
    When $N>0$, since $x^2-Dy^2>0$, we have $x>y\sqrt{D}$. So
    
    $$
    \left|\dfrac{x}{y}-\sqrt{D}\right| = \dfrac{N}{y(x+y\sqrt{D})}<\dfrac{N}{2y^2\sqrt{D}}<\dfrac{1}{2y^2}.
    $$
    
    By [Legendre's criterion](./continued-fraction.md#recognizing-convergents), $\dfrac{x}{y}$ is a convergent of $\sqrt{D}$.
    
    When $N<0$, $x>y\sqrt{D}$ no longer holds. So consider instead solutions of $y^2-\dfrac{1}{D}x^2=-\dfrac{N}{D}$. Since $\dfrac{|N|}{D}<\sqrt{\dfrac{1}{D}}$, the argument above still works. This shows that $\dfrac{y}{x}$ is a convergent of $\dfrac{1}{\sqrt{D}}$. By the [reciprocal theorem](./continued-fraction.md#recurrence), $\dfrac{x}{y}$ is also a convergent of $\sqrt{D}$.

???+ note "Theorem"
    When running the PQa algorithm above on $(P_0,Q_0,D)=(0,1,D)$, $Q_k=1$ implies $\ell\mid k$.

??? note "Proof"
    In the continued fraction expansion of $\sqrt{D}$, every remainder except the $0$-th is a [purely periodic continued fraction](./continued-fraction.md#purely-periodic-continued-fractions). Suppose $Q_k=1$. By Galois's result, the remainder $\omega_k=P_k+\sqrt{D}>1$ and its conjugate satisfies $-1<P_k-\sqrt{D}<0$, so $P_k=\lfloor\sqrt{D}\rfloor$. Hence the remainder $\omega_k$ equals $\omega_\ell$. But a repeated remainder means the continued fraction repeats from there, so if $k$ is not a multiple of $\ell$, this contradicts $\ell$ being the minimal period. So $\ell\mid k$.

Putting this section together: just expand $\sqrt{D}$ as a continued fraction, that is, run the PQa algorithm starting from $(P_0,Q_0,D)=(0,1,D)$. The first time you get $Q_\ell=1$, you have reached the end of the first period. Then, if $\ell$ is even, $(A_{\ell-1},B_{\ell-1})$ is the fundamental solution of the Pell equation; otherwise $(A_{2\ell-1},B_{2\ell-1})$ is. When the period length $\ell$ is odd, you do not need to continue the PQa algorithm to twice the period: as shown shortly, $A_{2\ell-1}+B_{2\ell-1}\sqrt{D}=(A_{\ell-1}+B_{\ell-1}\sqrt{D})^2$, so the fundamental solution of the Pell equation can be computed directly from $(A_{\ell-1},B_{\ell-1})$. All other solutions of the Pell equation can be computed from the fundamental solution.

??? example "Examples"
    1.  Solve $x^2-14y^2=1$.
    
        Running the PQa algorithm on $(P_0,Q_0,D)=(0,1,14)$ gives: (the red part is the first period)
    
        | $k$ | $P$ | $Q$ |        $a$       |  $A$  |  $B$ |  $G$  | $G^2-DB^2$ |
        | :-: | :-: | :-: | :--------------: | :---: | :--: | :---: | :--------: |
        | $0$ | $0$ | $1$ |        $3$       |  $3$  |  $1$ |  $3$  |    $-5$    |
        | $1$ | $3$ | $5$ | $\color{red}{1}$ |  $4$  |  $1$ |  $4$  |     $2$    |
        | $2$ | $2$ | $2$ | $\color{red}{2}$ |  $11$ |  $3$ |  $11$ |    $-5$    |
        | $3$ | $2$ | $5$ | $\color{red}{1}$ |  $15$ |  $4$ |  $15$ |     $1$    |
        | $4$ | $3$ | $1$ | $\color{red}{6}$ | $101$ | $27$ | $101$ |    $-5$    |
        | $5$ | $3$ | $5$ |        $1$       | $116$ | $31$ | $116$ |     $2$    |
    
        The period length $\ell=4$ is even. The smallest positive integer solution is $(G_3,B_3)=(15,4)$.
    2.  Solve $x^2-41y^2=1$.
    
        Running the PQa algorithm on $(P_0,Q_0,D)=(0,1,41)$ gives: (the red part is the first period)
    
        | $k$ | $P$ | $Q$ |        $a$        |   $A$   |   $B$  |   $G$   | $G^2-DB^2$ |
        | :-: | :-: | :-: | :---------------: | :-----: | :----: | :-----: | :--------: |
        | $0$ | $0$ | $1$ |        $6$        |   $6$   |   $1$  |   $6$   |    $-5$    |
        | $1$ | $6$ | $5$ |  $\color{red}{2}$ |   $13$  |   $2$  |   $13$  |     $5$    |
        | $2$ | $4$ | $5$ |  $\color{red}{2}$ |   $32$  |   $5$  |   $32$  |    $-1$    |
        | $3$ | $6$ | $1$ | $\color{red}{12}$ |  $397$  |  $62$  |  $397$  |     $5$    |
        | $4$ | $6$ | $5$ |        $2$        |  $826$  |  $129$ |  $826$  |    $-5$    |
        | $5$ | $4$ | $5$ |        $2$        |  $2049$ |  $320$ |  $2049$ |     $1$    |
        | $6$ | $6$ | $1$ |        $12$       | $25414$ | $3969$ | $25414$ |    $-5$    |
        | $7$ | $6$ | $5$ |        $2$        | $52877$ | $8258$ | $52877$ |     $5$    |
    
        The period length $\ell=3$ is odd. The smallest positive integer solution is $(G_5,B_5)=(2049,320)$. It can also be computed from $(G_2,B_2)=(32,5)$:
    
        $$
        (32+5\sqrt{41})^2=2049+320\sqrt{41}.
        $$

### Negative Pell equation

By the previous section, solutions of the negative Pell equation must also correspond to convergents of $\sqrt{D}$, and can only appear where $(-1)^kQ_k=-1$. This can only happen at the end of a period. So the negative Pell equation has a solution if and only if the period length $\ell$ is odd. When a solution exists, $(A_{\ell-1},B_{\ell-1})$ is the fundamental solution of the negative Pell equation. It is found the same way as in the previous section.

Using an argument similar to the earlier proof of the structure of the Pell equation's solutions, we can prove the following:

???+ note "Theorem"
    Suppose $x^2-Dy^2=-1$ has a solution, and its fundamental solution is $(x_1,y_1)$. Then all integer solutions of $x^2-Dy^2=\pm 1$ belong to the set
    
    $$
    \{(x,y):x+y\sqrt{D}=\pm(x_1+y_1\sqrt{D})^k,k\in\mathbf Z\}.
    $$
    
    In particular, the integer solution $(x_2,y_2)$ with $x_2+y_2\sqrt{D}=(x_1+y_1\sqrt{D})^2$ is exactly the fundamental solution of $x^2-Dy^2=1$.

??? note "Proof"
    By symmetry, we only need positive integer solutions, that is, $x+y\sqrt{D}>1$. But since $x^2-Dy^2=\pm 1$ consists of two hyperbolas, $x+y\sqrt{D}$ is no longer in one-to-one correspondence with $(x,y)$. To deal with this, first prove that the $(x_2,y_2)$ above is the fundamental solution of $x^2-Dy^2=1$.
    
    Clearly $(x_2,y_2)$ is a solution of $x^2-Dy^2=1$. Let $(z,w)$ be the fundamental solution of $x^2-Dy^2=1$; then $1<z+w\sqrt{D}\le x_2+y_2\sqrt{D}$. If the right inequality is strict, dividing by $x_1+y_1\sqrt{D}$ gives $-x_1+y_1\sqrt{D}<(z+w\sqrt{D})(-x_1+y_1\sqrt{D})<x_1+y_1\sqrt{D}$. Expanding the middle term gives the form $x'+y'\sqrt{D}$, whose norm is $-1$, and $(x',y')$ is also an integer solution. Taking reciprocals of this inequality shows that $-x'+y'\sqrt{D}$ also lies between $-x_1+y_1\sqrt{D}$ and $x_1+y_1\sqrt{D}$. The quadratic integers $\pm x'+y'\sqrt{D}$ are reciprocals of each other, so one of them is greater than $1$. But no other quadratic integer of norm $-1$ should lie between $1$ and $x_1+y_1\sqrt{D}$, contradicting the minimality of $x_1+y_1\sqrt{D}$. So $x_2+y_2\sqrt{D}=z+w\sqrt{D}$ must hold, that is, $(x_2,y_2)$ is the fundamental solution of $x^2-Dy^2=1$.
    
    Based on this, if some solution $(x,y)$ of $x^2-Dy^2=\pm 1$ does not correspond to any $(x_1+y_1\sqrt{D})^k$, then there is a $k$ with $(x_1+y_1\sqrt{D})^{2k}<x+y\sqrt{D}<(x_1+y_1\sqrt{D})^{2k+2}$. Removing the factor $(x_1+y_1\sqrt{D})^{2k+1}$ shows that there is a quadratic integer $x'+y'\sqrt{D}\neq 1$ of norm $\pm 1$ between $-x_1+y_1\sqrt{D}$ and $x_1+y_1\sqrt{D}$. Repeating the reciprocal argument from the previous paragraph, this contradicts the minimality of $x_1+y_1\sqrt{D}$. This proves the claim.

Since $(A_{\ell-1},B_{\ell-1})$ is the smallest positive integer solution of the negative Pell equation, and all positive integer solutions of $x^2-Dy^2=\pm 1$ appear in the set

$$
\{(x,y):x+y\sqrt{D}=(A_{\ell-1}+B_{\ell-1}\sqrt{D})^k,k\in\mathbf N_+\}
$$

and since these positive integer solutions must correspond to convergents of $\sqrt{D}$ at the end of a period (the position just before it), and the numerators and denominators of convergents are strictly increasing, for all $k\in\mathbf N_+$ we always have

$$
(A_{\ell-1}+B_{\ell-1}\sqrt{D})^k = A_{k\ell-1}+B_{k\ell-1}\sqrt{D}.
$$

Among all these positive integer solutions, odd $k$ gives solutions of the negative Pell equation and even $k$ gives solutions of the Pell equation; the two alternate.

To decide whether the negative Pell equation has a solution, you need the period length of the continued fraction expansion of $\sqrt{D}$, which is not easy to compute, so one would like a simpler test. However, no simple, easy-to-compute criterion is currently known[^solubility-neg-pell]. Here we only give a simple result.

???+ note "Theorem"
    If $x^2-Dy^2=-1$ has a solution, then $4$ does not divide $D$ and $D$ has no prime factor of the form $4k+3$. Conversely, if $D=2$ or $D$ is a prime of the form $4k+1$, the equation must have a solution.

??? note "Proof"
    First, if the negative Pell equation has a solution, then $-1$ is a quadratic residue modulo $D$, so $-1$ is also a quadratic residue modulo every divisor $d$ of $D$; hence $d\neq 4$ and $d$ is not a prime of the form $4k+3$. Conversely, $x^2-2y^2=-1$ has the nontrivial solution $(1,1)$. What remains is the case where $D$ is a prime of the form $4k+1$.
    
    Let $D$ be a prime of the form $4k+1$; we want to show that $x^2-Dy^2=-1$ has a solution. The idea is to start from the fundamental solution $(u,v)$ of the Pell equation $x^2-Dy^2=1$ and construct a solution $(\alpha,\beta)$ of $x^2-Dy^2=-1$. If $u$ is even, taking $u^2-Dv^2=1$ modulo $4$ gives $v^2\equiv -1\pmod 4$, but $-1$ is not a quadratic residue modulo $4$. This contradiction shows $u$ is odd. Look at $Dv^2=u^2-1=(u+1)(u-1)$. Since $u$ is odd, $\gcd(u+1,u-1)=\gcd(u+1,2)=2$. So when the factors of $Dv^2$ are split between $u+1$ and $u-1$, one of them must be $2\alpha^2$ and the other $2D\beta^2$, where $\alpha$ and $\beta$ are coprime positive integers and $v=2\alpha\beta$. Substituting $u=\alpha^2+D\beta^2$ and $v=2\alpha\beta$ into $u^2-Dv^2=1$ gives $\alpha^2-D\beta^2=\pm 1$. Since $(u,v)$ is the fundamental solution of the Pell equation and $(\alpha,\beta)$ is a smaller positive integer pair, the right-hand side cannot be $+1$, so it must be $-1$. This proves that $x^2-Dy^2=-1$ has the solution $(\alpha,\beta)$.

If $D$ is composite, having no prime factor of the form $4k+3$ and no square factor still does not guarantee that $x^2-Dy^2=-1$ has a solution; for example, $x^2-34y^2=-1$ has no solution.

??? example "Example"
    From the computations in the examples above, $x^2-14y^2=-1$ has no solution, and the smallest positive integer solution of $x^2-41y^2=-1$ is $(G_2,B_2)=(32,5)$.

### The case of norm ±4

Next we discuss solutions of $x^2-Dy^2=\pm 4$. Here the behavior of the solutions depends on $D\bmod 4$.

Some cases are easy. If $D\equiv 0\pmod 4$, then $x$ is even, so $(x/2,y)$ is a solution of $u^2-(D/4)v^2=\pm 1$. In the remaining cases, $x$ and $y$ must be both odd or both even. If $x$ and $y$ are both odd, taking the equation modulo $4$ gives $D\equiv 1\pmod 4$. So if $D\equiv 2,3\pmod 4$, $x$ and $y$ must both be even, and $(x/2,y/2)$ is a solution of $u^2-Dv^2=\pm 1$. Hence, except when $D\equiv 1\pmod 4$, solutions of $x^2-Dy^2=\pm 4$ can be obtained from solutions of the corresponding (negative) Pell equation.

Now consider $D\equiv 1\pmod 4$, which cannot simply be reduced to the cases already solved. To find the fundamental solution, apply the PQa algorithm to $(P_0,Q_0,D)=(1,2,D)$. The first time you get $Q_\ell=2$, you have reached the end of the first period. If the period length $\ell$ is even, $(G_{\ell-1},B_{\ell-1})$ is the fundamental solution of $x^2-Dy^2=4$; otherwise $(G_{\ell-1},B_{\ell-1})$ is the fundamental solution of $x^2-Dy^2=-4$. Starting from $(G_{\ell-1},B_{\ell-1})$, you get all solutions of $x^2-Dy^2=\pm 4$:

$$
\left\{(x,y):\dfrac{x+y\sqrt{D}}{2}=\pm\left(\dfrac{G_{\ell-1}+B_{\ell-1}\sqrt{D}}{2}\right)^k,k\in\mathbf Z\right\}.
$$

If the period length $\ell$ is even, all of these are solutions of $x^2-Dy^2=4$; otherwise, $(x,y)$ is a solution of $x^2-Dy^2=-4$ when $k$ is odd and of $x^2-Dy^2=4$ when $k$ is even.

The correctness of this algorithm relies on the following facts:

???+ note "Theorem"
    Suppose $x^2-Dy^2=\pm 4$ has a positive integer solution $(x,y)$. If $D\equiv 1\pmod 4$, then $\dfrac{(x+y)/2}{y}$ must be a convergent of $\dfrac{1+\sqrt{D}}{2}$.

??? note "Proof"
    First note that here $x$ and $y$ must have the same parity, so $(x+y)/2$ is an integer. If $(x,y)$ is a solution of $x^2-Dy^2=4$, then $x>y\sqrt{D}>2y$, so
    
    $$
    \left|\dfrac{(x+y)/2}{y}-\dfrac{1+\sqrt{D}}{2}\right| = \dfrac{2}{y(x+y\sqrt{D})}<\dfrac{1}{2y^2}.
    $$
    
    By [Legendre's criterion](./continued-fraction.md#recognizing-convergents), $\dfrac{(x+y)/2}{y}$ is a convergent of $\dfrac{1+\sqrt{D}}{2}$.
    
    If $(x,y)$ is a solution of $x^2-Dy^2=-4$, then to establish the inequality above, it suffices to show $4y<x+y\sqrt{D}$. This holds at least for all cases except $D=5,13$. For $D=5,13$, substituting $x=\sqrt{Dy^2-4}$ into the inequality shows it is equivalent to $2(\sqrt{D}-2)y^2>1$. Except for $(D,y)=(5,1)$, this inequality holds for $D=5,13$ and all positive integers $y$. What remains is $(D,y)=(5,1)$: here the solution of $x^2-5y^2=-4$ is $(x,y)=(1,1)$, and we need to check that $\dfrac{1}{1}$ is a convergent of $\dfrac{1+\sqrt{5}}{2}=[\overline{1}]$, which is obviously true.

???+ note "Theorem"
    Let $D$ be a positive integer that is not a perfect square. The continued fraction expansion of the quadratic irrational $\omega=\dfrac{1+\sqrt{D}}{2}$ has the form
    
    $$
    \omega = [\lfloor\omega\rfloor,\overline{a_1,\cdots,a_{\ell-1},2\lfloor\omega\rfloor-1}],
    $$
    
    where $\ell$ is the period length, and $a_k=a_{\ell-k}$ for all $1\le k<\ell$.

??? note "Proof"
    Since $\lfloor\omega\rfloor-1+\omega>1$ and its conjugate equals $\lfloor\omega\rfloor - \omega$, which lies between $-1$ and $0$, by [Galois's result](./continued-fraction.md#purely-periodic-continued-fractions) $\lfloor\omega\rfloor-1+\omega$ is a purely periodic continued fraction and can be written as
    
    $$
    \lfloor\omega\rfloor-1+\omega = [\overline{2\lfloor\omega\rfloor-1,a_1,\cdots,a_{\ell-1}}].
    $$
    
    Galois's result on the negative reciprocal of the conjugate says
    
    $$
    \dfrac{1}{\omega-\lfloor\omega\rfloor} = [\overline{a_{\ell-1},\cdots,a_1,2\lfloor\omega\rfloor-1}].
    $$
    
    So, by the definition of continued fractions,
    
    $$
    \lfloor\omega\rfloor-1+\omega = 2\lfloor\omega\rfloor-1 + \dfrac{1}{\dfrac{1}{\omega-\lfloor\omega\rfloor}} = [2\lfloor\omega\rfloor-1,\overline{a_{\ell-1},\cdots,a_1,2\lfloor\omega\rfloor-1}].
    $$
    
    Uniqueness of continued fraction expansions shows that $a_k=a_{\ell-k}$ for all $1\le k<\ell$, so the claimed expansion holds.

???+ note "Theorem"
    Let $D\equiv 1\pmod 4$. When running the PQa algorithm above on $(P_0,Q_0,D)=(1,2,D)$, $Q_k=2$ implies $\ell\mid k$.

??? note "Proof"
    In the continued fraction expansion of $\dfrac{1+\sqrt{D}}{2}$, every remainder except the $0$-th is a [purely periodic continued fraction](./continued-fraction.md#purely-periodic-continued-fractions). Suppose $Q_k=2$. By Galois's result, the conjugate of the remainder $\omega_k=\dfrac{P_k+\sqrt{D}}{2}$ satisfies $-1<\dfrac{P_k-\sqrt{D}}{2}<0$, that is, $\sqrt{D}-2<P_k<\sqrt{D}$. Since the PQa algorithm always has $Q_k\mid P_k^2-D$ (see the [proof of correctness](./continued-fraction.md#quadratic-irrationals)), $P_k$ must be odd, so $P_k$ is uniquely determined: $P_k=P_0+2(\lfloor\omega\rfloor-1)$. That is, the remainder $\omega_k=\omega_\ell$. But a repeated remainder means the continued fraction repeats from there, so if $k$ is not a multiple of $\ell$, this contradicts $\ell$ being the minimal period. So $\ell\mid k$.

???+ note "Theorem"
    Let $(x_1,y_1)$ be the smallest positive integer solution of $x^2-Dy^2=\pm 4$. Then all its solutions are
    
    $$
    \left\{(x,y):\dfrac{x+y\sqrt{D}}{2}=\pm\left(\dfrac{x_1+y_1\sqrt{D}}{2}\right)^k,k\in\mathbf Z\right\}.
    $$

??? note "Proof"
    By symmetry, we only need positive integer solutions $(x,y)$. The only thing to prove here is that the real pairs $(x,y)$ in the set are indeed integer solutions of $x^2-Dy^2=\pm 4$. The rest just repeats the proof of the structure of solutions of $x^2-Dy^2=\pm 1$.
    
    What we actually need to show is that, for any integer solutions $(x_1,y_1)$ and $(x_2,y_2)$ of $x^2-Dy^2=\pm 4$, the positive real pair $(x_3,y_3)$ defined below is again an integer solution:
    
    $$
    \dfrac{x_3+y_3\sqrt{D}}{2} = \dfrac{x_1+y_1\sqrt{D}}{2}\dfrac{x_2+y_2\sqrt{D}}{2}.
    $$
    
    Expanding the right-hand side and comparing rational and irrational coefficients gives
    
    $$
    x_3=\dfrac{x_1x_2+Dy_1y_2}{2},\ y_3=\dfrac{x_1y_2+x_2y_1}{2}.
    $$
    
    Since $x_i\equiv x_i^2\equiv Dy_i^2\equiv Dy_i\pmod 2$ for $i=1,2$,
    
    $$
    \begin{aligned}
    2x_3 &= x_1x_2+Dy_1y_2 \equiv D^2y_1y_2+Dy_1y_2=D(D+1)y_1y_2 \equiv 0 \pmod 2,\\
    2y_3 &= x_1y_2+x_2y_1 \equiv Dy_1y_2+Dy_2y_1 = 2Dy_1y_2 \equiv 0 \pmod 2.
    \end{aligned}
    $$
    
    So $x_3$ and $y_3$ are both integers. Since the norm is multiplicative, $(x_3,y_3)$ is a solution of $x^2-Dy^2=\pm 4$.

Putting these facts together and repeating the arguments of the previous sections proves that the algorithm above for $x^2-Dy^2=\pm 4$ is correct. These results show that $x^2-Dy^2=\pm 4$ has a simple solution structure like that of $x^2-Dy^2=\pm 1$: all its solutions can be expressed through its smallest positive integer solution, without solving any other equation.

In fact, every solution of $x^2-Dy^2=\pm 1$ can be found among the solutions of $x^2-Dy^2=\pm 4$, so from this point of view $x^2-Dy^2=\pm 4$ is more fundamental. Clearly, $(x,y)$ is a solution of $x^2-Dy^2=\pm 1$ if and only if $(2x,2y)$ is a solution of $x^2-Dy^2=\pm 4$. The analysis above shows that when $D\equiv 2,3\pmod 4$, all solutions of $x^2-Dy^2=\pm 4$ are both even, so they correspond to solutions of $x^2-Dy^2=\pm 1$.

When $D\equiv 0\pmod 4$, in a solution $(x,y)$ of $x^2-Dy^2=\pm 4$, $x$ must be even, but $y$ may be odd. If $y_1$ is even in the smallest positive integer solution $(x_1,y_1)$ of $x^2-Dy^2=\pm 4$, then $y$ is even in all solutions, and these integer solutions correspond one-to-one to the integer solutions of $x^2-Dy^2=\pm 1$; but if $y_1$ is odd in the smallest solution $(x_1,y_1)$, the parity of $y_k$ follows that of $k$ and alternates, so only even $k$ gives solutions of $x^2-Dy^2=\pm 1$. If $y_1$ is odd in the smallest positive integer solution of $x^2-Dy^2=\pm 4$ and the norm of $x_1+y_1\sqrt{D}$ is $-4$, then for such $D$, $x^2-Dy^2=-4$ has a solution but $x^2-Dy^2=-1$ does not.

When $D\equiv 1\pmod 4$, a solution $(x,y)$ of $x^2-Dy^2=\pm 4$ may be both odd or both even. If the smallest positive integer solution $(x_1,y_1)$ is already both even, then all its integer solutions are also both even, so they always correspond to integer solutions of $x^2-Dy^2=\pm 1$. If the smallest positive integer solution $(x_1,y_1)$ is both odd, we have the following:

???+ note "Theorem"
    Let $(x_1,y_1)$ be the smallest positive integer solution of $x^2-Dy^2=\pm 4$. If $x_1$ and $y_1$ are both odd, then $D\equiv 5\pmod 8$, and an integer solution $(x,y)$ of the equation is both even if and only if
    
    $$
    \dfrac{x+y\sqrt{D}}{2} = \pm\left(\dfrac{x_1+y_1\sqrt{D}}{2}\right)^{3k},k\in\mathbf Z.
    $$

??? note "Proof"
    Taking both sides of $x_1^2-Dy_1^2=\pm 4$ modulo $8$ gives $D\equiv 5\pmod 8$. To prove the second claim, first show that $(x_3,y_3)$ are both even. Since
    
    $$
    \dfrac{x_3+y_3\sqrt{D}}{2} = \left(\dfrac{x_1+y_1\sqrt{D}}{2}\right)^{3} = \dfrac{x_1^3+3Dx_1y_1^2}{8}+\dfrac{3x_1^2y_1+Dy_1^3}{8}\sqrt{D},
    $$
    
    we only need to show the right-hand side is an integer. Since the square of an odd number is $1$ modulo $8$,
    
    $$
    \begin{aligned}
    &x_1^3+3Dx_1y_1^2 = x_1(x_1^2+3Dy_1^2) \equiv x_1(1+3\times 5\times 1) = 16x_1 = 0 \pmod 8,\\
    &3x_1^2y_1+Dy_1^3 = y_1(3x_1^2+Dy_1^2) \equiv y_1(3\times 1+5\times 1) = 8y_1 = 0 \pmod 8.
    \end{aligned}
    $$
    
    This shows that $x_3,y_3$ are both even. Then, for all $k\in\mathbf Z$,
    
    $$
    \dfrac{x+y\sqrt{D}}{2} = \pm\left(\dfrac{x_1+y_1\sqrt{D}}{2}\right)^{3k} = \pm\left(\dfrac{x_3+y_3\sqrt{D}}{2}\right)^k \in \mathbf Z[\sqrt{D}],
    $$
    
    so all such $(x,y)$ are even. Conversely, for $r=1,2$ we always have
    
    $$
    \pm\left(\dfrac{x_1+y_1\sqrt{D}}{2}\right)^{3k+r} = \pm\left(\dfrac{x_3+y_3\sqrt{D}}{2}\right)^k\left(\dfrac{x_r+y_r\sqrt{D}}{2}\right).
    $$
    
    To show the corresponding $(x,y)$ are not integers, it suffices to show this expression is not an integer, that is, the second factor in the product on the right is not an integer. For $r=1$, this is the hypothesis; for $r=2$, since
    
    $$
    \dfrac{x_2+y_2\sqrt{D}}{2} = \left(\dfrac{x_1+y_1\sqrt{D}}{2}\right)^2 = \dfrac{x_1^2+Dy_1^2}{4} + \dfrac{x_1y_1}{2}\sqrt{D},
    $$
    
    and $x_1^2+Dy_1^2\equiv 1+1\times 1=2\pmod 4$, $x_1y_1\equiv 1\pmod 2$, this is not an integer either. This proves that the corresponding solutions are both even only when the exponent is a multiple of $3$.

In other words, one out of every three solutions of $x^2-Dy^2=\pm 4$ is both even, and it corresponds to an integer solution of $x^2-Dy^2=\pm 1$. This also shows that for $D\equiv 1\pmod 4$, $x^2-Dy^2=-4$ has a solution if and only if $x^2-Dy^2=-1$ does.

The discussion so far is enough to compute the fundamental unit of a real quadratic integer ring. Let $D$ be a square-free positive integer. For $D\equiv 2,3\pmod 4$, you only need the smallest positive integer solution of $x^2-Dy^2=\pm 1$; for $D\equiv 1\pmod 4$, you only need the smallest positive integer solution of $x^2-Dy^2=\pm 4$. Given the smallest positive integer solution $(x,y)$, for $D\equiv 2,3\pmod 4$ the fundamental unit is $\pm x\pm y\sqrt{D}$; for $D\equiv 1\pmod 4$ it is $\dfrac{\pm x\pm y\sqrt{D}}{2}$.

??? example "Examples"
    1.  Solve $x^2-14y^2=\pm 4$.
    
        From the computations in the earlier example, the smallest positive integer solution of $x^2-14y^2=4$ is $(30,8)$, and $x^2-14y^2=-4$ has no solution.
    2.  Solve $x^2-41y^2=\pm 4$.
    
        Running the PQa algorithm on $(P_0,Q_0,D)=(1,2,41)$ gives: (the red part is the first period)
    
        |  $k$ | $P$ | $Q$ |        $a$       |   $A$   |   $B$  |   $G$   | $G^2-DB^2$ |
        | :--: | :-: | :-: | :--------------: | :-----: | :----: | :-----: | :--------: |
        |  $0$ | $1$ | $2$ |        $3$       |   $3$   |   $1$  |   $5$   |    $-16$   |
        |  $1$ | $5$ | $8$ | $\color{red}{1}$ |   $4$   |   $1$  |   $7$   |     $8$    |
        |  $2$ | $3$ | $4$ | $\color{red}{2}$ |   $11$  |   $3$  |   $19$  |    $-8$    |
        |  $3$ | $5$ | $4$ | $\color{red}{2}$ |   $26$  |   $7$  |   $45$  |    $16$    |
        |  $4$ | $3$ | $8$ | $\color{red}{1}$ |   $37$  |  $10$  |   $64$  |    $-4$    |
        |  $5$ | $5$ | $2$ | $\color{red}{5}$ |  $211$  |  $57$  |  $365$  |    $16$    |
        |  $6$ | $5$ | $8$ |        $1$       |  $248$  |  $67$  |  $429$  |    $-8$    |
        |  $7$ | $3$ | $4$ |        $2$       |  $707$  |  $191$ |  $1223$ |     $8$    |
        |  $8$ | $5$ | $4$ |        $2$       |  $1662$ |  $449$ |  $2875$ |    $-16$   |
        |  $9$ | $3$ | $8$ |        $1$       |  $2369$ |  $640$ |  $4098$ |     $4$    |
        | $10$ | $5$ | $2$ |        $5$       | $13507$ | $3649$ | $23365$ |    $-16$   |
        | $11$ | $5$ | $8$ |        $1$       | $15876$ | $4289$ | $27463$ |     $8$    |
    
        The period length $\ell=5$ is odd. The smallest positive integer solution of $x^2-41y^2=-4$ is $(G_4,B_4)=(64,10)$, and that of $x^2-41y^2=4$ is $(G_9,B_9)=(4098,640)$. They are related by:
    
        $$
        \dfrac{4098+640\sqrt{41}}{2} = \left(\dfrac{64+10\sqrt{41}}{2}\right)^2.
        $$
    
        Of course, since $D\equiv 1\pmod 8$, by the result above the smallest positive integer solutions of $x^2-41y^2=\pm 4$ here are always even and are always $2$ times the smallest positive integer solutions of $x^2-41y^2=\pm 1$, so they also follow directly from the earlier example.
    3.  Solve $x^2-13y^2=\pm 4$.
    
        Running the PQa algorithm on $(P_0,Q_0,D)=(1,2,13)$ gives: (the red part is the first period)
    
        | $k$ | $P$ | $Q$ |        $a$       |  $A$ |  $B$ |  $G$  | $G^2-DB^2$ |
        | :-: | :-: | :-: | :--------------: | :--: | :--: | :---: | :--------: |
        | $0$ | $1$ | $2$ |        $2$       |  $2$ |  $1$ |  $3$  |    $-4$    |
        | $1$ | $3$ | $2$ | $\color{red}{3}$ |  $7$ |  $3$ |  $11$ |     $4$    |
        | $2$ | $3$ | $2$ |        $3$       | $23$ | $10$ |  $36$ |    $-4$    |
        | $3$ | $3$ | $2$ |        $3$       | $74$ | $33$ | $119$ |     $4$    |
    
        The period length $\ell=1$ is odd. The smallest positive integer solution of $x^2-13y^2=-4$ is $(G_0,B_0)=(3,1)$, and that of $x^2-13y^2=4$ is $(G_1,B_1)=(11,3)$.
    
        Since the smallest positive integer solutions of this equation are odd, we can use the pair $(G_2,B_2)=(36,10)$ at the end of the third period to get the smallest positive integer solution $(18,5)$ of the corresponding (negative) Pell equation $x^2-13y^2=\pm 1$. It can also be computed directly:
    
        $$
        \dfrac{36+10\sqrt{13}}{2}=\left(\dfrac{3+\sqrt{13}}{2}\right)^3.
        $$
    
        Moreover, this is a solution of the negative Pell equation. The smallest positive integer solution of the corresponding Pell equation is $(649,180)$.
    4.  Solve $x^2-52y^2=\pm 4$.
    
        Since the smallest positive integer solutions of $x^2-13y^2=\pm 1$ are $(18,5)$ and $(649,180)$, the smallest positive integer solutions of $x^2-52y^2=\pm 4$ are $(36,10)$ and $(1298,360)$.

### General case

Finally, we discuss how to solve the generalized Pell equation.

For $|N|<\sqrt{D}$ there is a simple method. The results above show that for a solution $(x,y)$ of $x^2-Dy^2=N$, $\dfrac{x}{y}$ must equal some convergent of $\sqrt{D}$. Moreover, by the solution structure discussed above, every fundamental solution $(x,y)$ has $x+y\sqrt{D}$ at most the fundamental solution $x_1+y_1\sqrt{D}$ of the corresponding Pell equation $x^2-Dy^2=1$. Since the denominators $B_k$ in the PQa algorithm are monotonic, these fundamental solutions of the generalized Pell equation must appear before the fundamental solution of the corresponding Pell equation. So just run the PQa algorithm on $(P_0,Q_0,D)=(0,1,D)$ until $Q_{\ell'}=1$ with $\ell'$ even, and for each $(A_k,B_k)$ along the way, check whether there is an integer $f$ such that

$$
A_k^2-DB_k^2 = (-1)^{k+1}Q_{k+1} = N/f^2
$$

holds. If it does, record $(fA_{k},fB_{k})$ as a smallest positive integer solution. All the $(fA_k,fB_k)$ recorded this way are exactly all the smallest positive integer solutions of $x^2-Dy^2=N$. Using $(A_{\ell'-1},B_{\ell'-1})$, the fundamental solution of the corresponding Pell equation, you can generate all solutions of the generalized Pell equation from these smallest positive integer solutions. Note that, depending on whether the period length $\ell$ is even or odd, the $\ell'$ above may be $\ell$ or $2\ell$.

For more general $N$, the method above no longer works. First, enumerate every square factor $f^2$ of $N$, let $m=N/f^2$, and enumerate all solutions $z$ of the congruence $z^2\equiv D\pmod{|m|}$ with $-|m|/2<z \le |m|/2$. Then run the PQa algorithm on $(P_0,Q_0,D)=(z,|m|,D)$ until $Q_k=\pm 1$ or a full period has ended. In the second case, the equation has no solution associated with this $(f,z)$. In the first case, you further check whether $(-1)^kQ_k=N/|N|$. If the signs agree, $(fG_{k-1},fB_{k-1})$ is a solution of $x^2-Dy^2=N$. Otherwise it is a solution of $x^2-Dy^2=-N$, and you can get a solution of $x^2-Dy^2=N$ by combining it with the fundamental solution of the corresponding negative Pell equation, if and only if that negative Pell equation has a solution. After going through all pairs $(f,z)$, you get exactly one solution of $x^2-Dy^2=N$ in each equivalence class of solutions, and it is either the fundamental solution or the smallest positive integer solution of that class. Using these and the fundamental solution of the corresponding Pell equation, you can generate all integer solutions of the equation. This algorithm is called the **Lagrange–Matthews–Mollin algorithm**.

The correctness of this algorithm is guaranteed by the following theorem:

???+ note "Theorem"
    Suppose $x^2-Dy^2=N$ has an integer solution $(x,y)$ with $x\ge 0, y>0,\gcd(x,y)=1$. Let $Q_0=|N|$; then $\gcd(Q_0,y)=1$. Let $P_0$ be the solution of the congruence $x\equiv -P_0y\pmod{Q_0}$ with $-Q_0/2<P_0\le Q_0/2$, and let the integer $X$ satisfy $x=Q_0X-P_0y$. Then $P_0^2\equiv D\pmod{Q_0}$, $\dfrac{X}{y}$ is a convergent $\dfrac{A_{k-1}}{B_{k-1}}$ of $\omega=\dfrac{P_0+\sqrt{D}}{Q_0}$, and $Q_k=(-1)^k\dfrac{N}{|N|}$.

??? note "Proof"
    From $x\equiv -P_0y\pmod{Q_0}$ and $x^2-Dy^2=N\equiv 0\pmod{Q_0}$, clearly $P_0^2\equiv D\pmod{Q_0}$. Hence
    
    $$
    P_0x+Dy\equiv -P_0^2y+Dy = (D-P_0^2)y\equiv 0\pmod{Q_0}.
    $$
    
    So we can consider the integer matrix
    
    $$
    \begin{pmatrix}P & R \\ Q & S\end{pmatrix}
    =
    \begin{pmatrix}X & \dfrac{P_0x+Dy}{Q_0} \\ y & x\end{pmatrix}.
    $$
    
    Its determinant is
    
    $$
    PS-QR = \dfrac{x(x+P_0y)-y(P_0x+Dy)}{Q_0} = \dfrac{x^2-Dy^2}{Q_0} = \pm 1.
    $$
    
    Moreover, letting $\zeta =\sqrt{D} > 1$, we have
    
    $$
    \dfrac{P\zeta+R}{Q\zeta+S} = \dfrac{(x+P_0y)\sqrt{D}+(P_0x+Dy)}{(x+y\sqrt{D})Q_0} = \dfrac{P_0+\sqrt{D}}{Q_0} = \omega.
    $$
    
    Now we show that $\dfrac{P}{Q}$ is a convergent of $\omega$. Suppose $\dfrac{P}{Q}$ has the [continued fraction expansion](./continued-fraction.md#simple-continued-fractions)
    
    $$
    \dfrac{P}{Q} = [a_0,a_1,\cdots,a_k]
    $$
    
    with $PS-QR = (-1)^{k-1}$. Let $\dfrac{p_k}{q_k}$ be its $k$-th convergent; then $(p_k,q_k)=(P,Q)$, and by the [difference formula for convergents](./continued-fraction.md#error-estimates), $p_kq_{k-1}-q_kp_{k-1}=(-1)^{k-1}$. This means
    
    $$
    p_k(S-q_{k-1}) = q_k(R-p_{k-1}).
    $$
    
    Consider the cases:
    
    -   If $S=0$, it is easy to check that $Q=R=1$, so $\omega=P+\zeta^{-1}=[P,\zeta]$, and $\dfrac{P}{Q}=P$ is the $0$-th convergent of $\omega$;
    -   If $Q=S>0$, then $Q=S=1$ and $P-R=\pm 1$. In this case,
        -   if $P=R+1$, then $\omega=R+\dfrac{1}{1+\zeta^{-1}}=[R,1,\zeta]$, so $\dfrac{P}{Q}=\dfrac{R+1}{1}=[R,1]$ is the $1$-st convergent of $\omega$;
        -   if $P=R-1$, then $\omega=R-1+\dfrac{1}{1+\zeta}=[R-1,\zeta-1]$, so $\dfrac{P}{Q}=R-1$ is the $0$-th convergent of $\omega$;
    -   If $Q\neq S>0$, then since $Q=q_k\mid(S-q_{k-1})$, there is always an integer $\kappa$ with $S=\kappa q_k+q_{k-1}$ and $R=\kappa p_k+p_{k-1}$. Since $q_k\ge q_{k-1}$ and $S>0$, $\kappa\ge 0$. So $\omega=\dfrac{(\kappa+\zeta)p_k+p_{k-1}}{(\kappa+\zeta)q_k+q_{k-1}}=[a_0,a_1,\cdots,a_k,\kappa+\zeta]$, and $\dfrac{P}{Q}$ is its $k$-th convergent.
    
    In all cases, $\dfrac{X}{y}$ is a convergent of $\omega=\dfrac{P_0+\sqrt{D}}{Q_0}$, which in the notation of the PQa algorithm we write as $\dfrac{A_{k-1}}{B_{k-1}}$. Since $A_{k-1}^2-DB_{k-1}^2=(-1)^kQ_0Q_k$, we get $Q_k=(-1)^k\dfrac{N}{|N|}$.

This theorem guarantees that all positive solutions of the equation appear among the convergents of the corresponding quadratic irrationals. When computing convergents with the PQa algorithm, once you are inside the period, the convergents are guaranteed to be positive. So by enumerating all quadratic irrationals allowed by the theorem's conditions and computing their convergents up to one period, you will find a solution. Since two solutions appearing among the convergents of the same quadratic irrational are always equivalent, you can stop as soon as you get the first solution with $(-1)^kQ_k=N/|N|$. Unlike all the earlier algorithms, here a suitable $k$ may appear before the period starts.

??? example "Examples"
    1.  Solve $x^2-157y^2=12$.
    
        Since $12^2<157$, run the PQa algorithm on $(P_0,Q_0,D)=(0,1,157)$. The result is: (the red part is the first period)
    
        |  $k$ |  $P$ |  $Q$ |        $a$        |         $A$        |        $B$       |         $G$        | $G^2-DB^2$ |
        | :--: | :--: | :--: | :---------------: | :----------------: | :--------------: | :----------------: | :--------: |
        |  $0$ |  $0$ |  $1$ |        $12$       |        $12$        |        $1$       |        $12$        |    $-13$   |
        |  $1$ | $12$ | $13$ |   $\color{red}1$  |        $13$        |        $1$       |        $13$        |    $12$    |
        |  $2$ |  $1$ | $12$ |   $\color{red}1$  |        $25$        |        $2$       |        $25$        |    $-3$    |
        |  $3$ | $11$ |  $3$ |   $\color{red}7$  |        $188$       |       $15$       |        $188$       |    $19$    |
        |  $4$ | $10$ | $19$ |   $\color{red}1$  |        $213$       |       $17$       |        $213$       |    $-4$    |
        |  $5$ |  $9$ |  $4$ |   $\color{red}5$  |       $1253$       |       $100$      |       $1253$       |     $9$    |
        |  $6$ | $11$ |  $9$ |   $\color{red}2$  |       $2719$       |       $217$      |       $2719$       |    $-12$   |
        |  $7$ |  $7$ | $12$ |   $\color{red}1$  |       $3972$       |       $317$      |       $3972$       |    $11$    |
        |  $8$ |  $5$ | $11$ |   $\color{red}1$  |       $6691$       |       $534$      |       $6691$       |    $-11$   |
        |  $9$ |  $6$ | $11$ |   $\color{red}1$  |       $10663$      |       $851$      |       $10663$      |    $12$    |
        | $10$ |  $5$ | $12$ |   $\color{red}1$  |       $17354$      |      $1385$      |       $17354$      |    $-9$    |
        | $11$ |  $7$ |  $9$ |   $\color{red}2$  |       $45371$      |      $3621$      |       $45371$      |     $4$    |
        | $12$ | $11$ |  $4$ |   $\color{red}5$  |      $244209$      |      $19490$     |      $244209$      |    $-19$   |
        | $13$ |  $9$ | $19$ |   $\color{red}1$  |      $289580$      |      $23111$     |      $289580$      |     $3$    |
        | $14$ | $10$ |  $3$ |   $\color{red}7$  |      $2271269$     |     $181267$     |      $2271269$     |    $-12$   |
        | $15$ | $11$ | $12$ |   $\color{red}1$  |      $2560849$     |     $204378$     |      $2560849$     |    $13$    |
        | $16$ |  $1$ | $13$ |   $\color{red}1$  |      $4832118$     |     $385645$     |      $4832118$     |    $-1$    |
        | $17$ | $12$ |  $1$ | $\color{red}{24}$ |     $118531681$    |     $9459858$    |     $118531681$    |    $13$    |
        | $18$ | $12$ | $13$ |        $1$        |     $123363799$    |     $9845503$    |     $123363799$    |    $-12$   |
        | $19$ |  $1$ | $12$ |        $1$        |     $241895480$    |    $19305361$    |     $241895480$    |     $3$    |
        | $20$ | $11$ |  $3$ |        $7$        |    $1816632159$    |    $144983030$   |    $1816632159$    |    $-19$   |
        | $21$ | $10$ | $19$ |        $1$        |    $2058527639$    |    $164288391$   |    $2058527639$    |     $4$    |
        | $22$ |  $9$ |  $4$ |        $5$        |    $12109270354$   |    $966424985$   |    $12109270354$   |    $-9$    |
        | $23$ | $11$ |  $9$ |        $2$        |    $26277068347$   |   $2097138361$   |    $26277068347$   |    $12$    |
        | $24$ |  $7$ | $12$ |        $1$        |    $38386338701$   |   $3063563346$   |    $38386338701$   |    $-11$   |
        | $25$ |  $5$ | $11$ |        $1$        |    $64663407048$   |   $5160701707$   |    $64663407048$   |    $11$    |
        | $26$ |  $6$ | $11$ |        $1$        |   $103049745749$   |   $8224265053$   |   $103049745749$   |    $-12$   |
        | $27$ |  $5$ | $12$ |        $1$        |   $167713152797$   |   $13384966760$  |   $167713152797$   |     $9$    |
        | $28$ |  $7$ |  $9$ |        $2$        |   $438476051343$   |   $34994198573$  |   $438476051343$   |    $-4$    |
        | $29$ | $11$ |  $4$ |        $5$        |   $2360093409512$  |  $188355959625$  |   $2360093409512$  |    $19$    |
        | $30$ |  $9$ | $19$ |        $1$        |   $2798569460855$  |  $223350158198$  |   $2798569460855$  |    $-3$    |
        | $31$ | $10$ |  $3$ |        $7$        |  $21950079635497$  |  $1751807067011$ |  $21950079635497$  |    $12$    |
        | $32$ | $11$ | $12$ |        $1$        |  $24748649096352$  |  $1975157225209$ |  $24748649096352$  |    $-13$   |
        | $33$ |  $1$ | $13$ |        $1$        |  $46698728731849$  |  $3726964292220$ |  $46698728731849$  |     $1$    |
        | $34$ | $12$ |  $1$ |        $24$       | $1145518138660728$ | $91422300238489$ | $1145518138660728$ |    $-13$   |
        | $35$ | $12$ | $13$ |        $1$        | $1192216867392577$ | $95149264530709$ | $1192216867392577$ |    $12$    |
    
        The period length $\ell=17$ is odd, so within two periods we look for places where $G_k^2-157B_k^2$ differs from $12$ by a square factor, that is, $k=1,9,13,19,23,31$. The corresponding solutions are the $(fG,fB)$ in the table below:
    
        |  $k$ | $f$ |      $fG_k$      |      $fB_k$     |    $x$    |   $y$   |
        | :--: | :-: | :--------------: | :-------------: | :-------: | :-----: |
        |  $1$ | $1$ |       $13$       |       $1$       |    $13$   |   $1$   |
        |  $9$ | $1$ |      $10663$     |      $851$      |  $10663$  |  $851$  |
        | $13$ | $2$ |     $579160$     |     $46222$     |  $579160$ | $46222$ |
        | $19$ | $2$ |    $483790960$   |    $38610722$   | $-579160$ | $46222$ |
        | $23$ | $1$ |   $26277068347$  |   $2097138361$  |  $-10663$ |  $851$  |
        | $31$ | $1$ | $21950079635497$ | $1751807067011$ |   $-13$   |   $1$   |
    
        All the $(fG,fB)$ are the smallest positive integer solutions in all equivalence classes of the solution set of $x^2-157y^2=12$. To get all solutions from them, use the fundamental solution $(46698728731849,3726964292220)$ of the corresponding Pell equation. For example, you can turn them into the fundamental solutions $(x,y)$ of their equivalence classes; these are also listed in the table above.
    2.  Solve $x^2-157y^2=12$.
    
        This time we use the Lagrange–Matthews–Mollin algorithm. First, enumerate the square factors of $N=12$:
    
        -   For $f^2=1^2$, $m=12$, and the congruence $z^2\equiv 157\pmod{12}$ has solutions $z=\pm 1,\pm 5$;
        -   For $f^2=2^2$, $m=3$, and the congruence $z^2\equiv 157\pmod{3}$ has solutions $z=\pm 1$.
    
        For every possible pair $(f,z)$, run the PQa algorithm with initial parameters $(P_0,Q_0,D)=(z,|m|,D)$ and find the first position with $(-1)^kQ_k=1$; the corresponding $(fG_{k-1},fB_{k-1})$ is a solution. The results are shown below:
    
        | $f$ |  $z$ |  $m$ |  $k$ |    $fG_{k-1}$    |    $fB_{k-1}$   |
        | :-: | :--: | :--: | :--: | :--------------: | :-------------: |
        | $1$ |  $1$ | $12$ | $32$ | $21950079635497$ | $1751807067011$ |
        | $1$ | $-1$ | $12$ |  $2$ |       $13$       |       $1$       |
        | $1$ |  $5$ | $12$ | $24$ |   $26277068347$  |   $2097138361$  |
        | $1$ | $-5$ | $12$ | $10$ |      $10663$     |      $851$      |
        | $2$ |  $1$ |  $3$ | $20$ |    $483790960$   |    $38610722$   |
        | $2$ | $-1$ |  $3$ | $14$ |     $579160$     |     $46222$     |
    
        These are exactly the smallest positive integer solutions of all the equivalence classes listed above, and they can be turned into fundamental solutions using the fundamental solution of the Pell equation.
    3.  Solve $x^2-79y^2=\pm 101$.
    
        Again use the Lagrange–Matthews–Mollin algorithm. Since $N=101$ is prime, $f=1$. Then $m=101$, and the congruence $z^2\equiv 79\pmod{101}$ has solutions $z=\pm 33$.
    
        Running the PQa algorithm on $(P_0,Q_0,D)=(33,101,79)$ gives: (the red part is the first period)
    
        | $k$ |  $P$  |  $Q$  |       $a$      |  $A$  |   $B$  |   $G$   | $G^2-DB^2$ |
        | :-: | :---: | :---: | :------------: | :---: | :----: | :-----: | :--------: |
        | $0$ |  $33$ | $101$ |       $0$      |  $0$  |   $1$  |  $-33$  |   $1010$   |
        | $1$ | $-33$ | $-10$ |       $2$      |  $1$  |   $2$  |   $35$  |    $909$   |
        | $2$ |  $13$ |  $9$  |       $2$      |  $2$  |   $5$  |   $37$  |   $-606$   |
        | $3$ |  $5$  |  $6$  | $\color{red}2$ |  $5$  |  $12$  |  $109$  |    $505$   |
        | $4$ |  $7$  |  $5$  | $\color{red}3$ |  $17$ |  $41$  |  $364$  |   $-303$   |
        | $5$ |  $8$  |  $3$  | $\color{red}5$ |  $90$ |  $217$ |  $1929$ |   $1010$   |
        | $6$ |  $7$  |  $10$ | $\color{red}1$ | $107$ |  $258$ |  $2293$ |   $-707$   |
        | $7$ |  $3$  |  $7$  | $\color{red}1$ | $197$ |  $475$ |  $4222$ |    $909$   |
        | $8$ |  $4$  |  $9$  | $\color{red}1$ | $304$ |  $733$ |  $6515$ |   $-606$   |
        | $9$ |  $5$  |  $6$  |       $2$      | $805$ | $1941$ | $17252$ |    $505$   |
    
        The period length $\ell=6$ is even. Up to the end of one period, $Q_k=\pm 1$ never occurs, so this case has no solution. Similarly, running the PQa algorithm on $(P_0,Q_0,D)=(-33,101,79)$ shows the same thing. So the equation has no solution.

## Exercises

-   [LOJ 6687. "Project Euler 66" Solving the Equation](https://loj.ac/p/6687)
-   [SPOJ EQU2 - Yet Another Equation](https://www.spoj.com/problems/EQU2/)
-   [SPOJ PELL2 - Pell (Mid pelling)](https://www.spoj.com/problems/PELL2/)
-   [UVa 12909. Numeric Center](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=862&page=show_problem&problem=4774)
-   [UVa 10241. Semi-triangular and also Square](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1182)

## References and notes

-   [Pell's equation - Wikipedia](https://en.wikipedia.org/wiki/Pell%27s_equation)
-   [John P. Robertson - Solving the generalized Pell equation $x^2-Dy^2=N$](https://citeseerx.ist.psu.edu/document?repid=rep1&type=pdf&doi=5ac34a344ee346855184ff949eeaed18685b155c)
-   [Keith Matthews - The Diophantine Equation $x^2-Dy^2=N$,$D>0$](http://www.numbertheory.org/PDFS/patz5.pdf)
-   [Existence of Solution to Pell’s Equation - Suryateja Gavva's Blog](https://surya-teja.com/2011/01/11/existence-of-solution-to-pells-equation/)
-   [Calculating the simple continued fraction of a quadratic irrational - Number Theory Web](http://www.numbertheory.org/php/surd.html) (PQa algorithm)
-   [Solving the diophantine equation x2–Dy2 = N, D > 0 and not a perfect square, N ≠ 0 - Number Theory Web](http://www.numbertheory.org/php/patz.html) (Lagrange–Matthews–Mollin algorithm)

[^not-square]: When $D$ is a perfect square, factoring directly gives $(x+y\sqrt{D})(x-y\sqrt{D})=N$, so all solutions can be found by going through the divisors of $N$. In particular, when $N=1$ the equation has only the solutions $(\pm 1,0)$; when $N=-1$ and $D\neq 1$, it has no solution.

[^neg-pell]: Some Chinese literature also calls it the Pell equation of the second kind.

[^half-int]: That is, a rational number of the form $n+\dfrac12$ with $n\in\mathbf Z$.

[^fundamental-solution]: Note that the definition of the fundamental solution of the Pell equation does not match that of the fundamental unit of a real quadratic integer ring. First, in some real quadratic integer rings the $x,y$ in the fundamental unit $x+y\sqrt{D}$ are half-integers, so it is not a solution of the Pell equation. Second, a real quadratic integer ring has four fundamental units, but there is only one fundamental solution, because the fundamental solution requires $x,y$ to both be positive.

[^solubility-neg-pell]: A fairly practical test and tool can be found [here](http://www.numbertheory.org/php/hardy_williams.html) and in its references. The list of positive integers $D$ for which $x^2-Dy^2=-1$ has a solution is [OEIS A031396](https://oeis.org/A031396).
