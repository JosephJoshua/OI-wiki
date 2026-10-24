author: 383494, CCXXXI, chunibyo-wly, Enter-tainer, Great-designer, megakite, Menci, shawlleyw, shuzhouliu, StudyingFather, Tiphereth-A, untitledunrevised, c-forrest, Resorie

## Introduction

A continued fraction represents a real number as the limit of a convergent sequence of rational numbers. The rationals in this sequence are easy to compute, and they give the best approximations of the real number, so continued fractions often come up in competitive programming. Continued fractions are also closely tied to the Euclidean algorithm, so they apply to a whole range of number theory problems.

???+ info "About the implementations of continued fraction algorithms"
    This page gives a number of implementations of continued fraction algorithms. Some of them cannot guarantee that every integer that appears during the computation fits in a 32-bit or 64-bit integer variable. In that case, please refer to the corresponding Python implementation, or replace the integer variables in the C++ implementation with a [big integer class](../bignum.md). To keep the focus on the main ideas, some code on this page calls functions implemented earlier on the page without repeating their implementations.

## Continued fractions

A **continued fraction** is, by itself, just a formal notation.

???+ abstract "Finite continued fraction"
    For a sequence $\{a_k\}_{k=0}^n$, the continued fraction $[a_0,a_1,\ldots,a_n]$ denotes the expression
    
    $$
    x = a_0+\dfrac{1}{a_1+\dfrac{1}{a_2+\dfrac{1}{\cdots+\dfrac{1}{a_n}}}}.
    $$
    
    The continued fraction is meaningful if and only if this expression is meaningful. The numbers $a_k$ are called the **terms** or **coefficients** of the continued fraction.

???+ info "Notation"
    More general continued fractions allow the numerators in the expansion to be something other than $1$, and the notation has to change accordingly; that is beyond the scope of this page. Also, some references write the first comma "$,$" as a semicolon "$;$". This means exactly the same as the notation on this page.

Of course, continued fractions also extend to infinite sequences.

???+ abstract "Infinite continued fraction"
    For an infinite sequence $\{a_k\}_{k=0}^\infty$, the continued fraction $[a_0,a_1,\ldots]$ denotes the limit
    
    $$
    x = \lim_{k\rightarrow\infty} x_k = \lim_{k\rightarrow\infty} [a_0,a_1,\ldots,a_k].
    $$
    
    The continued fraction is meaningful if and only if this limit exists. Here $x_k=[a_0,a_1,\ldots,a_k]$ is called the $k$-th **convergent** of $x$, and $r_k=[a_k,a_{k+1},\ldots]$ is called the $k$-th **remainder** or **complete quotient** of $x$. Correspondingly, the term $a_k$ is sometimes called the $k$-th **partial quotient**.

### Simple continued fractions

In number theory, we mainly consider continued fractions whose terms are all integers.

???+ abstract "Simple continued fraction"
    A continued fraction $[a_0,a_1,\ldots]$ where $a_0$ is an integer and $a_1,a_2,\ldots$ are all positive integers is called a **simple continued fraction**, or just a **continued fraction**. If the sequence $\{a_i\}$ is finite, it is called a **finite (simple) continued fraction**; otherwise, it is called an **infinite (simple) continued fraction**. Also, $a_0$ is called its **integer part**.

Unless stated otherwise, "continued fraction" on this page always means a simple continued fraction. One can prove that an infinite simple continued fraction always converges, and that the remainders of a simple continued fraction are always positive.

Continued fractions have the following basic properties:

???+ note "Properties"
    Let the real number $x=[a_0,a_1,a_2,\ldots]$. Then:
    
    1.  For any $k\in\mathbf Z$, $x+k=[a_0+k,a_1,a_2,\ldots]$;
    2.  For a real number $x>1$, $a_0>0$, and its reciprocal is $x^{-1}=[0,a_0,a_1,a_2,\ldots]$.

Finite continued fractions correspond to rational numbers. Every rational number can be written as a continued fraction in exactly two ways, and the two lengths are always one odd and one even. The only difference between the two is whether the last term is $1$, that is,

$$
x = [a_0,a_1,\ldots,a_n] = [a_0,a_1,\ldots,a_n-1,1].
$$

These two continued fractions are called the **continued fraction representations** of the rational number $x$. The one whose last term is not one is called the canonical representation, and the one whose last term is one is called the non-canonical representation.[^one-representation]

??? example "Example"
    The continued fraction representations of the rational number $x=\dfrac{5}{3}$ are
    
    $$
    \begin{aligned}
    x = [1,1,1,1] &= 1+\dfrac{1}{1+\dfrac{1}{1+\dfrac{1}{1}}},\\
    x = [1,1,2] &= 1+\dfrac{1}{1+\dfrac{1}{2}}.
    \end{aligned}
    $$

Infinite continued fractions correspond to irrational numbers. Moreover, every irrational number can be written as a continued fraction in exactly one way, called the continued fraction representation of the irrational number.

### Computing the continued fraction representation

To find the continued fraction representation of a real number $x$, just note that if a remainder $r_k$ is not an integer, it must satisfy

$$
r_k = [a_k,a_{k+1},\ldots] = [a_k,r_{k+1}] = a_k + \dfrac{1}{r_{k+1}}.
$$

Moreover, $r_{k+1}>1$. So, starting from $r_0=x$, we can compute recursively

$$
a_k = \lfloor r_k\rfloor,\ r_{k+1} = \dfrac{1}{r_k-a_k}.
$$

The sequence $\{a_k\}$ produced this way is always uniquely determined, unless some remainder $r_k$ becomes an integer. If $r_k$ is an integer, the process should stop, and we may output either the canonical or the non-canonical representation.

In competitive programming, we usually deal with a rational number $x=\dfrac{p}{q}$. Then every remainder $r_k$ is a rational number $\dfrac{p_k}{q_k}$, and for $k>0$, since $r_k>1$, we always have $p_k>q_k$. Working out the recurrence above explicitly, we find

$$
a_k = \left\lfloor\frac{p_k}{q_k}\right\rfloor,\ r_{k+1} = \dfrac{1}{r_k-a_k} = \dfrac{q_k}{p_k-a_kq_k} = \dfrac{q_k}{p_k\bmod q_k}.
$$

This computation is really just the [Euclidean algorithm](./gcd.md#euclidean-algorithm) applied to $p$ and $q$. It also shows that for a rational number $x=\dfrac{p}{q}$, the length of the continued fraction representation is $O(\log\min\{p, q\})$. The complexity of computing it for $\dfrac{p}{q}$ is also $O(\log\min\{p, q\})$.

???+ example "Reference implementation"
    Given the numerator $p$ and denominator $q$ of a fraction, output the coefficient sequence $[a_0,a_1,\ldots,a_n]$ of its continued fraction.
    
    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/diophantine.cpp:fraction"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/diophantine.py:fraction"
        ```

## Convergents

The definition of continued fractions introduced convergents. The convergents of a real number are the convergents of its continued fraction representation: in the continued fraction representation of a real number $x$, keep only the first $k$ terms; the resulting continued fraction $x_k$ is called the $k$-th convergent of $x$. The convergents $x_k$ of a real number $x$ are all rational, and the sequence $\{x_k\}$ converges to $x$.

??? example "Example: convergents of the golden ratio"
    The first few convergents of the continued fraction $x=[1,1,1,1,\ldots]$ are
    
    $$
    \begin{aligned}
    x_0 &= [1]=1,\\
    x_1 &= [1,1]=2,\\
    x_2 &= [1,1,1]=\dfrac{3}{2},\\
    x_3 &= [1,1,1,1]=\dfrac{5}{3},\\
    x_4 &= [1,1,1,1,1]=\dfrac{8}{5}.
    \end{aligned}
    $$
    
    By induction one can show that
    
    $$
    x_k = \frac{F_{k+2}}{F_{k+1}},
    $$
    
    where $\{F_k\}$ is the [Fibonacci sequence](../combinatorics/fibonacci.md). From its closed-form formula,
    
    $$
    x_k = \frac{\phi^{k+2}-(-\phi)^{-(k+2)}}{\phi^{k+1}-(-\phi)^{-(k+1)}},
    $$
    
    where $\phi=\dfrac{1+\sqrt{5}}{2}$ is the golden ratio. As $k$ tends to infinity,
    
    $$
    x=\lim_{k\rightarrow\infty}x_k=\phi.
    $$
    
    So the continued fraction $x=[1,1,1,1,\ldots]$ represents the golden ratio $\phi$.

These convergents approach the corresponding real number, so they can be used to approximate it. For that, we need to understand the properties of convergents.

### Recurrence

First, we need to compute these convergents. Although each convergent just appends one more term to the continued fraction, we don't need to recompute its value from scratch every time. In fact, convergents satisfy the following recurrence:

???+ note "Recurrence formula"
    For a continued fraction $x=[a_0,a_1,a_2,\ldots]$, let its $k$-th convergent $x_k=[a_0,a_1,\ldots,a_k]$ be written uniquely as the reduced fraction $\dfrac{p_k}{q_k}$. Then
    
    $$
    \begin{aligned}
    p_k &= a_kp_{k-1}+p_{k-2},\\
    q_k &= a_kq_{k-1}+q_{k-2}.
    \end{aligned}
    $$
    
    The recurrence starts from the (formal) fractions
    
    $$
    x_{-1}=\frac{p_{-1}}{q_{-1}}=\frac{1}{0},\ x_{-2}=\frac{p_{-2}}{q_{-2}}=\frac{0}{1}.
    $$

??? note "Proof"
    Every convergent is a finite continued fraction. As mentioned above, evaluating a finite continued fraction is essentially running the Euclidean algorithm. But the Euclidean algorithm actually produces a suffix of the continued fraction, while a convergent needs a prefix. To get this prefix, we need to see how the continued fraction changes when we add one more step. For this, we can express one step of the Euclidean algorithm as a matrix multiplication:
    
    $$
    M(a)=\begin{pmatrix} a & 1 \\ 1 & 0 \end{pmatrix},\qquad
    M(a)\begin{pmatrix} u\\ v \end{pmatrix}=\begin{pmatrix} au+v\\u \end{pmatrix},\qquad
    \frac{au+v}{u}=a+\frac{1}{u/v}.
    $$
    
    The vector $(a_k,1)^{\mathrm{T}}$ represents the finite continued fraction $[a_k]$; multiplying by matrices on the left one by one adds coefficients to the continued fraction on the left one by one. Extending this continued fraction to the convergent $x_k=\dfrac{p_k}{q_k}=[a_0,a_1,\ldots,a_k]$ gives the following equation:
    
    $$
    M(a_0)M(a_1)M(a_2)\cdots M(a_{k-1})\begin{pmatrix}a_k\\1\end{pmatrix}=\begin{pmatrix}p_k\\q_k\end{pmatrix}.
    $$
    
    Since $\det(M(a_0)M(a_1)\cdots M(a_{k-1}))=(-1)^{k}$, this matrix maps the primitive vector $(a_k,1)^{\mathrm{T}}$ to $(p_k,q_k)^{\mathrm{T}}$, so $p_k$ and $q_k$ must be coprime. The second column of $M(a_k)$ is $(1,0)^{\mathrm{T}}$, and $M(a_{k-1})(1,0)^{\mathrm{T}}=(a_{k-1},1)^{\mathrm{T}}$, so the product for this column can be obtained by substituting recursively. Adding this column, we get
    
    $$
    M(a_0)M(a_1)M(a_2)\cdots M(a_k)=\begin{pmatrix}p_k & p_{k-1}\\q_k & q_{k-1}\end{pmatrix}.
    $$
    
    Now just substitute the product of the first $k$ factors, and the recurrence for convergents follows easily:
    
    $$
    \begin{aligned}
    \begin{pmatrix}p_{k-1} & p_{k-2}\\q_{k-1} & q_{k-2}\end{pmatrix}M(a_k)
    &=\begin{pmatrix}p_k & p_{k-1}\\q_k & q_{k-1}\end{pmatrix}\\
    \Rightarrow\quad p_k&=a_k p_{k-1}+p_{k-2},\qquad q_k=a_k q_{k-1}+q_{k-2}.
    \end{aligned}
    $$

???+ info "Notation"
    Whenever this page writes a convergent $x_k$ as $\dfrac{p_k}{q_k}$, it always assumes that the numerator $p_k$ and denominator $q_k$ are given by the recurrence above. The proof above shows that this always gives the reduced form of the convergent.

This recurrence shows that

$$
x_k=\dfrac{a_kp_{k-1}+p_{k-2}}{a_kq_{k-1}+q_{k-2}}
$$

lies between $x_{k-1}$ and $x_{k-2}$.

Using the recurrence from this section, we get the following algorithm for computing convergents:

???+ example "Reference implementation"
    Given the coefficients $a_0,a_1,\ldots,a_n$ of a continued fraction, find the sequences of numerators and denominators of the convergents $(p_0,q_0),(p_1,q_1),\ldots,(p_n,q_n)$.
    
    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/diophantine.cpp:convergents"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/diophantine.py:convergents"
        ```

### Continuants

A **continuant** comes from the intermediate quantities in the recurrence for convergents.[^continuant]

???+ abstract "Continuant"
    For any finite sequence, define the continuant recursively as follows:
    
    -   $K(\varnothing)=1,\, K(a)=a$;
    -   for $n\ge 1$, $K(a_0,\ldots,a_n)=a_n K(a_0,\ldots,a_{n-1})+K(a_0,\ldots,a_{n-2})$.

From the recurrence for convergents, it is easy to see that for $x=[a_0,a_1,a_2,\ldots]$, its convergent $\dfrac{p_k}{q_k}=[a_0,a_1,\ldots,a_k]$ can be written in terms of continuants:

$$
p_k=K(a_0,a_1,\ldots,a_k),\quad q_k=K(a_1,\ldots,a_k).
$$

In other words, continuants can represent finite continued fractions:

$$
\frac{K(a_0,a_1,\ldots,a_k)}{K(a_1,\ldots,a_k)}=[a_0,a_1,\ldots,a_k].
$$

The earlier matrix form is also easy to rewrite with continuants. For $k\ge 1$,

$$
M(a_0)\cdots M(a_k)=
\begin{pmatrix}
K(a_0,\ldots,a_k)&K(a_0,\ldots,a_{k-1})\\
K(a_1,\ldots,a_k)&K(a_1,\ldots,a_{k-1})
\end{pmatrix}.
$$

The most important property of continuants is their symmetry.

???+ note "Symmetry of continuants"
    For any finite sequence $(a_0,\ldots,a_n)$,
    
    $$
    K(a_0,\ldots,a_n)=K(a_n,\ldots,a_0).
    $$

??? note "Proof"
    Since every matrix $M(a)$ is symmetric, transposing the product gives
    
    $$
    (M(a_0)\cdots M(a_n))^{\mathrm{T}}=M(a_n)^{\mathrm{T}}\cdots M(a_0)^{\mathrm{T}}=M(a_n)\cdots M(a_0).
    $$
    
    Comparing the top-left entries of the two products gives the result immediately.

By symmetry, the recurrence for continuants can also be written in reverse:

$$
K(a_0,\ldots,a_n)=a_0 K(a_1,\ldots,a_n)+K(a_2,\ldots,a_n).
$$

??? info "Determinant form of continuants"
    A continuant can be written as a determinant:
    
    $$
    K(a_0,\ldots,a_k)=\det
    \begin{pmatrix}
    a_0 & 1 & 0 & \cdots & 0 \\
    -1 & a_1 & 1 & \ddots & \vdots \\
    0 & -1 & a_2 & \ddots & 0 \\
    \vdots & \ddots & \ddots & \ddots & 1 \\
    0 & \cdots & 0 & -1 & a_k
    \end{pmatrix}.
    $$
    
    This is the determinant of a [tridiagonal matrix](https://en.wikipedia.org/wiki/Tridiagonal_matrix). Expanding from the top-left corner gives the reverse recurrence. Conversely, expanding from the bottom-right corner gives the recurrence in the definition.

Another interesting property of continuants is the concatenation property.

???+ note "Concatenation of continuants"
    For two non-empty sequences $(a_1,\ldots,a_m)$ and $(b_1,\ldots,b_n)$,
    
    $$
    K(a_1,\ldots,a_m,b_1,\ldots,b_n)=K(a_1,\ldots,a_m)K(b_1,\ldots,b_n)+K(a_1,\ldots,a_{m-1})K(b_2,\ldots,b_n).
    $$

??? note "Proof"
    Just split the matrix product into two parts using associativity. Let
    
    $$
    P=M(a_1)\cdots M(a_m),\quad Q=M(b_1)\cdots M(b_n),
    $$
    
    then
    
    $$
    (PQ)_{1,1}=P_{1,1}Q_{1,1}+P_{1,2}Q_{2,1}.
    $$
    
    This is exactly the identity of the concatenation property.

This property can be used to study the intermediate quantities of the Euclidean algorithm. For example, Heilbronn used it to estimate the average number of steps of the Euclidean algorithm[^heilbronn]. Below is a contest problem that uses this property to handle a related sum.

???+ example "[Luogu P17229 \[Math×Girl²\] Heroic Variations](https://www.luogu.com.cn/problem/P17229)"
    Given a positive integer $N$ and the values of two integer-valued functions $g,h:\{1,2,\ldots,N\}\to\mathbf{Z}$.
    
    For integers $x,y$ with $1\le y<x\le N$, let $z=x\bmod y$, and define recursively
    
    $$
    f(x,y)=
    \begin{cases}
    0, & z=0,\\
    g\!\left(\left\lfloor\dfrac{x}{y}\right\rfloor\right)
    h\!\left(\left\lfloor\dfrac{y}{z}\right\rfloor\right)
    +f(y,z), & z>0.
    \end{cases}
    $$
    
    Compute
    
    $$
    S(N)=
    \sum_{\substack{1\le b<a\le N\\\gcd(a,b)=1}}f(a,b).
    $$

??? note "Idea"
    The definition of $f(x,y)$ in the problem follows the steps of the Euclidean algorithm. Express the Euclidean algorithm with continued fractions: let $\dfrac{x}{y}=[a_0,a_1,\ldots,a_k]$ be the canonical representation of the finite continued fraction. Then
    
    $$
    f(x,y)=\sum_{i=0}^{k-1}g(a_i)h(a_{i+1}).
    $$
    
    Using the concatenation property of continuants and cutting the continuant at $a_i$, we get
    
    $$
    K(a_0,a_1,\ldots,a_k)=K(a_0,\ldots,a_i)K(a_{i+1},\ldots,a_k)+K(a_0,\ldots,a_{i-1})K(a_{i+2},\ldots,a_k).
    $$
    
    Let
    
    $$
    \begin{aligned}
    X&=K(a_0,\ldots,a_i),\quad Y=K(a_0,\ldots,a_{i-1}),\\
    Z&=K(a_{i+1},\ldots,a_k),\quad W=K(a_{i+2},\ldots,a_k).
    \end{aligned}
    $$
    
    Since continuants represent finite continued fractions, we get
    
    $$
    \frac{X}{Y}=[a_i,a_{i-1},\ldots,a_0],\quad \frac{Z}{W}=[a_{i+1},a_{i+2},\ldots,a_k].
    $$
    
    The conditions to satisfy are $\gcd(X,Y)=\gcd(Z,W)=1$, $1\le Y\le X$, $1\le W\le Z$, $XZ+YW=x\le N$. It looks like we have built a bijection between $(x,y,i)$ and $(X,Y,Z,W)$. But note that since $a_0$ may be $1$, the continued fraction for $\dfrac{X}{Y}$ may be the non-canonical representation, while the continued fraction for $\dfrac{Z}{W}$ is always the canonical representation (so $Z=W=1$ is also impossible).
    
    Now let's compute the contribution of a quadruple $(X,Y,Z,W)$ to the original sum after this transformation. Taking the floor of a fraction gives the first term of its continued fraction, which gives us the function arguments. Next, we split into cases on $(X,Y)$:
    
    1.  $Y>1$: both the canonical and the non-canonical representations of $\dfrac{X}{Y}$ correspond to a triple $(x,y,i)$, so the contribution is $2g\left(\left\lfloor\dfrac{X}{Y}\right\rfloor\right)h\left(\left\lfloor\dfrac{Z}{W}\right\rfloor\right)$;
    2.  $Y=1,X\ge2$: $\dfrac{X}{Y}=X$, corresponding to $[X]$ and $[X-1,1]$. Note that the latter contributes differently, so the total contribution is $(g(X)+g(X-1))h\left(\left\lfloor\dfrac{Z}{W}\right\rfloor\right)$;
    3.  $X=Y=1$: the contribution is $g(1)h\left(\left\lfloor\dfrac{Z}{W}\right\rfloor\right)$.
    
    This turns the very hard sum $S(N)$ into the following sum over $X,Y,Z,W$ (with the extra definition $g(0)=2g(1)$):
    
    $$
    \begin{aligned}
    S(N)={}&2\sum_{\substack{XZ+YW\le N\\X>Y\ge 1,\, Z>W\ge 1\\ \gcd(X,Y)=\gcd(Z,W)=1}}g(\lfloor X/Y\rfloor)h(\lfloor Z/W\rfloor) \\
    &+\sum_{\substack{XZ+W\le N\\X\ge 1,\, Z>W\ge 1\\\gcd(Z,W)=1}}(g(X-1)-g(X))h(\lfloor Z/W\rfloor).
    \end{aligned}
    $$
    
    This sum is easier to handle with standard tools, so we won't go into the details here.

As corollaries of the recurrence for convergents and the properties of continuants, we have the following reversal theorem and reciprocal theorem:

???+ note "Reversal theorem"
    Let the $k$-th convergent of a real number $x=[a_0,a_1,a_2,\ldots]>0$ be $\dfrac{p_k}{q_k}$. Then the ratios of the numerators and of the denominators of two consecutive convergents are
    
    $$
    \begin{aligned}
    \frac{p_k}{p_{k-1}}&=[a_k,a_{k-1},\ldots,a_1,a_0],\\
    \frac{q_k}{q_{k-1}}&=[a_k,a_{k-1},\ldots,a_1].
    \end{aligned}
    $$
    
    If $a_0=0$ and $k\ge 2$, the first continued fraction should be understood as cut off at the second-to-last term, that is, $[a_k,a_{k-1},\ldots,a_2]$.

??? note "Proof"
    From the continuant representation,
    
    $$
    \frac{q_k}{q_{k-1}}=\frac{K(a_1,\ldots,a_{k-1},a_k)}{K(a_1,\ldots,a_{k-1})}=\frac{K(a_k,a_{k-1},\ldots,a_1)}{K(a_{k-1},\ldots,a_1)}=[a_k,a_{k-1},\ldots,a_1].
    $$
    
    If $a_0\neq 0$, then
    
    $$
    \frac{p_k}{p_{k-1}}=\frac{K(a_0,\ldots,a_{k-1},a_k)}{K(a_0,\ldots,a_{k-1})}=\frac{K(a_k,a_{k-1},\ldots,a_0)}{K(a_{k-1},\ldots,a_0)}=[a_k,a_{k-1},\ldots,a_0].
    $$
    
    If $a_0=0$, the recurrence for continuants gives $K(0,a_1,a_2,\ldots,a_k)=K(a_2,\ldots,a_k)$, so
    
    $$
    \frac{p_k}{p_{k-1}}=\frac{K(a_2,\ldots,a_{k-1},a_k)}{K(a_2,\ldots,a_{k-1})}=\frac{K(a_k,a_{k-1},\ldots,a_2)}{K(a_{k-1},\ldots,a_2)}=[a_k,a_{k-1},\ldots,a_2].
    $$

???+ note "Reciprocal theorem"
    The reciprocals of the convergents of a real number $x>0$ are the convergents of $x^{-1}$.

??? note "Proof"
    Without loss of generality, let $x>1$ have the continued fraction representation $[a_0,a_1,a_2,\ldots]$. Then the continued fraction representation of $x^{-1}$ is $[0,a_0,a_1,a_2,\ldots]$. Their convergents can be found from the recurrence. For $x$, the initial values are $x_{-2}=\dfrac{0}{1}$ and $x_{-1}=\dfrac{1}{0}$; for $y=x^{-1}$, the initial values are $y_{-1}=\dfrac{1}{0}$ and $y_{0}=\dfrac{0}{1}$. So $x_{-2}=(y_{-1})^{-1}$ and $x_{-1}=(y_0)^{-1}$. By the recurrence, $x_k=y_{k+1}^{-1}$. This shows that the reciprocals of the convergents of $x$ are the convergents of $y=x^{-1}$. The case $0<x\le 1$ can be handled similarly.

### Error estimates

Using the recurrence for convergents, we can estimate the error made when approximating a real number by its convergents.

First, we can compute the difference between consecutive convergents:

???+ note "Differences of convergents"
    Let $x_k=\dfrac{p_k}{q_k}$ be the $k$-th convergent of a real number $x$. Then
    
    $$
    p_{k+1}q_k - p_kq_{k+1} = (-1)^k.
    $$
    
    So the difference between two consecutive convergents is
    
    $$
    x_{k+1} - x_k = \dfrac{(-1)^k}{q_{k+1}q_k}.
    $$

??? note "Proof"
    By the recurrence,
    
    $$
    \begin{aligned}
    \det\begin{pmatrix}
    p_{k+1} & p_k \\
    q_{k+1} & q_k 
    \end{pmatrix}
    &=
    \det\begin{pmatrix}
    a_{k+1}p_{k}+p_{k-1} & p_k \\
    a_{k+1}q_{k}+q_{k-1} & q_k 
    \end{pmatrix}
    =
    \det\begin{pmatrix}
    p_{k-1} & p_k\\
    q_{k-1} & q_k
    \end{pmatrix}
    \\
    &=
    -
    \det\begin{pmatrix}
    p_k & p_{k-1}\\
    q_k & q_{k-1}
    \end{pmatrix}
    =
    (-1)^{k+2}
    \det\begin{pmatrix}
    1 & 0\\
    0 & 1
    \end{pmatrix}
    =(-1)^k.
    \end{aligned}
    $$
    
    This is $p_{k+1}q_k - p_kq_{k+1} = (-1)^k$. Dividing both sides by $q_{k+1}q_k$ gives the result for $x_{k+1}-x_k$.

So each odd-indexed convergent is always larger than its two neighbors, and each even-indexed convergent is always smaller than its two neighbors: the convergents alternate.

If we look only at the even-indexed (odd-indexed) convergents, the sequence is also monotonically increasing (decreasing). This is because

$$
x_{k+2}-x_k = \dfrac{(-1)^{k+1}}{q_{k+2}q_{k+1}}+\dfrac{(-1)^{k}}{q_{k+1}q_{k}} = \dfrac{(-1)^k(q_{k+2}-q_k)}{q_{k+2}q_{k+1}q_k} = \dfrac{(-1)^ka_{k+2}}{q_{k+2}q_k}
$$

is positive (negative) when $k$ is even (odd). Also, because of the recurrence $q_{k}=a_kq_{k-1}+q_{k-2}$, the denominators $q_k$ grow at least as fast as the Fibonacci sequence. So the difference between consecutive terms must tend to zero. This shows that the even-indexed and odd-indexed convergents approach the same limit from below and from above, respectively. This proves that an infinite simple continued fraction always converges. The figure below shows how the convergents approach the corresponding real number:

![](./images/golden-ratio-convergents.svg)

???+ abstract "Upper (lower) convergents"
    For a real number $x$ and its convergent $x_k$, if $x_k>x$ ($x_k<x$), then $x_k$ is called an **upper (lower) convergent** of $x$.

As shown above, the upper convergents are exactly the odd-indexed convergents, and the lower convergents are exactly the even-indexed convergents.

Using the difference formula, we can write a real number $x$ as an alternating series:

$$
x = a_0+\sum_{k=0}^{\infty}\dfrac{(-1)^k}{q_{k+1}q_k}.
$$

The convergents and remainders in the definition of continued fractions are exactly the partial sums and remainders of this series.

The difference formula also lets us directly estimate the error of approximating a real number by its convergents:

???+ note "Error"
    Let $x_k=\dfrac{p_k}{q_k}\neq x$ be the $k$-th convergent of a real number $x$. Then
    
    $$
    x_k - x = \dfrac{(-1)^k}{q_k\left(r_{k+1}q_k+q_{k-1}\right)},
    $$
    
    where $r_{k+1}$ is the $(k+1)$-th remainder of $x$. Furthermore,
    
    $$
    \dfrac{1}{2q_{k+1}^2} \le \dfrac{1}{q_k(q_k+q_{k+1})} \le \left|x-\frac{p_k}{q_k}\right| \le \dfrac{1}{q_kq_{k+1}} \le \dfrac{1}{q_k^2}.
    $$

??? note "Proof"
    Since $x=[a_0,a_1,\ldots,a_k,r_{k+1}]$, and the difference formula for convergents also holds for formal continued fractions, we have
    
    $$
    x-x_k = \dfrac{(-1)^k}{q_k\left(r_{k+1}q_k+q_{k-1}\right)},
    $$
    
    where $r_{k+1}q_k+q_{k-1}$ is exactly the denominator of the $(k+1)$-th convergent of this formal continued fraction given by the recurrence.
    
    To finish the inequalities that follow, just note that when $x_k\neq x$, we always have
    
    $$
    1\le a_{k+1}\le r_{k+1} \le a_{k+1}+1,
    $$
    
    so
    
    $$
    q_{k+1}=a_{k+1}q_k+q_{k-1}\le r_{k+1}q_k+q_{k-1} \le q_k+(a_{k+1}q_k+q_{k-1}) = q_k+q_{k+1}.
    $$
    
    Therefore, we get the inequality
    
    $$
    \dfrac{1}{q_k(q_k+q_{k+1})} \le \left|x-\frac{p_k}{q_k}\right| = \dfrac{1}{q_k\left(r_{k+1}q_k+q_{k-1}\right)} \le \dfrac{1}{q_kq_{k+1}}.
    $$
    
    For the outer bounds, just note that $q_k\le q_{k+1}$.

The difference formula in this section has another simple corollary: the convergents $\dfrac{p_k}{q_k}$ are all in lowest terms.

???+ note "Corollary"
    For any real number $x$, if the numerator and denominator of the convergent $x_k=\dfrac{p_k}{q_k}$ are given by the recurrence, then $\dfrac{p_k}{q_k}$ is a reduced fraction, that is, $\gcd(p_k,q_k)=1$.

??? note "Proof"
    Just apply [Bézout's theorem](./bezouts.md) to the difference formula.

In fact, linear Diophantine equations in two variables can be solved with continued fractions.

???+ example "Solving linear Diophantine equations in two variables"
    Given $A, B, C \in \mathbf Z$, find $x, y \in \mathbf Z$ such that $Ax + By = C$.

??? note "Solution"
    Although this problem is usually solved with the [extended Euclidean algorithm](./bezouts.md#two-variables), it can also be solved with continued fractions.
    
    Let $\dfrac{A}{B}=[a_0, a_1, \ldots, a_k]$. We proved above that $p_k q_{k-1} - p_{k-1} q_k = (-1)^{k-1}$. Replacing $p_k$ and $q_k$ with $A$ and $B$, we get
    
    $$
    Aq_{k-1} - Bp_{k-1} = (-1)^{k-1} g,
    $$
    
    where $g = \gcd(A, B)$. If $g$ divides $C$, then one solution is $x = (-1)^{k-1}\dfrac{C}{g} q_{k-1}$ and $y = (-1)^{k}\dfrac{C}{g} p_{k-1}$; otherwise there is no solution.
    
    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/diophantine.cpp:dio"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/diophantine.py:dio"
        ```

## Diophantine approximation

An important application of continued fraction theory is Diophantine approximation. Diophantine approximation means approximating real numbers by rational numbers. Of course, since the rationals are dense, without any restriction we can get approximations with arbitrarily small error. So we need to restrict which rationals may be used, for example only rationals whose denominator is below some value. This section discusses the relationship between best approximations under such restrictions and continued fractions.

### Approximating real numbers by convergents

First, the error estimate for convergents immediately gives the following result:

???+ note "Theorem (Dirichlet)"
    For an irrational number $x$, there are infinitely many reduced fractions $\dfrac{p}{q}$ such that
    
    $$
    \left|x-\dfrac{p}{q}\right| < \dfrac{1}{q^2} 
    $$
    
    holds.

??? note "Proof"
    By the error estimate for convergents, the $k$-th convergent $x_k=\dfrac{p_k}{q_k}$ of an irrational number $x$ satisfies
    
    $$
    \left|x-\dfrac{p_k}{q_k}\right|\le\frac{1}{q_k^2}.
    $$
    
    Checking the proof of the error formula shows that equality never holds for an irrational $x$. So the numerators and denominators of all its convergents satisfy the requirement.

This theorem can also be seen as a corollary of [Dirichlet's approximation theorem](https://en.wikipedia.org/wiki/Dirichlet%27s_approximation_theorem). This is almost the best possible result. The exponent $2$ in the denominator on the right side can no longer be improved, but the constant can be. Hurwitz's theorem says that the right side can be reduced to $\dfrac{1}{\sqrt{5}q^2}$, and this is the best bound.

???+ note "Hurwitz's theorem"
    For an irrational number $x$, there are infinitely many reduced fractions $\dfrac{p}{q}$ such that
    
    $$
    \left|x-\dfrac{p}{q}\right| < \dfrac{1}{\sqrt{5}q^2} 
    $$
    
    holds, and the $\sqrt{5}$ on the right side cannot be replaced by any larger real number.

??? note "Proof (Borel)"
    Borel actually proved that among any three consecutive convergents of an irrational number $x$, at least one satisfies the condition above. Since there are infinitely many convergents and they are all reduced fractions, the first part of Hurwitz's theorem must hold.
    
    Proof by contradiction. Suppose there is an irrational number $x$ with convergents $x_{k-1},x_k,x_{k+1}$ such that
    
    $$
    \left|x-\dfrac{p_{k-1}}{q_{k-1}}\right|\ge\dfrac{1}{\sqrt{5}q_{k-1}^2},\ 
    \left|x-\dfrac{p_{k}}{q_{k}}\right|\ge\dfrac{1}{\sqrt{5}q_{k}^2},\ 
    \left|x-\dfrac{p_{k+1}}{q_{k+1}}\right|\ge\dfrac{1}{\sqrt{5}q_{k+1}^2}
    $$
    
    hold. Since consecutive convergents always lie on opposite sides of $x$, the difference formula gives
    
    $$
    \dfrac{1}{q_{k-1}q_{k}}=\left|\dfrac{p_{k-1}}{q_{k-1}}-\dfrac{p_{k}}{q_{k}}\right|=\left|x-\dfrac{p_{k-1}}{q_{k-1}}\right|+\left|x-\dfrac{p_{k}}{q_{k}}\right|\ge\dfrac{1}{\sqrt{5}q_{k-1}^2}+\dfrac{1}{\sqrt{5}q_{k}^2}.
    $$
    
    This can be written as an inequality in the ratio $\dfrac{q_{k}}{q_{k-1}}$:
    
    $$
    \dfrac{q_k}{q_{k-1}}+\dfrac{q_{k-1}}{q_k}\le\sqrt 5.
    $$
    
    Since the left side is rational and the right side is irrational, equality cannot hold. And since $q_k\ge q_{k-1}$, solving gives
    
    $$
    1\le \dfrac{q_{k}}{q_{k-1}} < \dfrac{\sqrt{5}+1}{2}.
    $$
    
    In the same way, we can show
    
    $$
    1\le \dfrac{q_{k+1}}{q_{k}} < \dfrac{\sqrt{5}+1}{2}.
    $$
    
    But by the recurrence, combining the two inequalities,
    
    $$
    a_{k+1} = \frac{q_{k+1}}{q_k}-\frac{q_{k-1}}{q_k} < \dfrac{\sqrt{5}+1}{2}-\dfrac{\sqrt{5}-1}{2} = 1
    $$
    
    This contradicts the definition of a simple continued fraction. So Borel's result holds.
    
    To show that this bound is the best, we just need to find an $x$ such that for any $C>\sqrt{5}$, only finitely many reduced fractions $\dfrac{p}{q}$ satisfy the inequality
    
    $$
    \left|x-\dfrac{p}{q}\right| < \dfrac{1}{Cq^2} 
    $$
    
    Below we prove that $\phi=\dfrac{\sqrt{5}+1}{2}$ is such an $x$.[^sqrt5]
    
    Let $\phi'=\dfrac{-\sqrt{5}+1}{2}$ be the conjugate root of $\phi$. Both are roots of the equation $x^2-x-1=0$. So for any real number $x$,
    
    $$
    x^2-x-1 = (x-\phi)(x-\phi').
    $$
    
    Substituting a reduced fraction $\dfrac{p}{q}$, we get
    
    $$
    \dfrac{1}{q^2}\le\frac{|p^2-pq-q^2|}{q^2}=\left|\dfrac{p}{q}-\phi\right|\left|\dfrac{p}{q}-\phi'\right|\le\left|\dfrac{p}{q}-\phi\right|\left(\left|\dfrac{p}{q}-\phi\right|+|\phi-\phi'|\right)<\dfrac{1}{Cq^2}\left(\dfrac{1}{Cq^2}+\sqrt{5}\right).
    $$
    
    For $C>\sqrt{5}$, solving directly gives $q<\dfrac{1}{\sqrt{C(C-\sqrt{5})}}$, so there cannot be infinitely many solutions to the inequality above.

The proofs of these theorems show that convergents give quite good Diophantine approximations. But they are not necessarily the best approximations. To discuss best approximations, we need a measure of how good an approximation is. There are usually two choices.

???+ warning "Cases where results about best approximations may fail"
    The next two sections state some results about best approximations. These results may fail in a few uninteresting cases. For example, both definitions of best approximation require strict inequalities, but a half-integer $x=n+\dfrac12$ with $n\in\mathbf Z$ can have the continued fraction $[n,1,1]$. Then its first two convergents $x_0=n$ and $x_1=n+1$ both have denominator $1$ and are at the same distance from $x$. So neither of them is a best approximation. When reading the results in this section, assume such cases have been excluded. If you don't care about the last few convergents, or only care about approximating irrational numbers, you can ignore these extra complications.

### Best approximations of the first kind: semiconvergents

Best approximations of the first kind use

$$
\left|x-\dfrac{p}{q}\right|
$$

to measure how good an approximation is.

???+ abstract "Best approximation of the first kind"
    For a real number $x$ and a rational number $\dfrac{p}{q}$, if for every $\dfrac{p'}{q'}\neq \dfrac{p}{q}$ with $0<q'\le q$ we have
    
    $$
    \left|x-\dfrac{p}{q}\right|<\left|x-\dfrac{p'}{q'}\right|,
    $$
    
    then the rational number $\dfrac{p}{q}$ is called a **best approximation of the first kind** of the real number $x$.

A best approximation of the first kind is not necessarily a convergent; it belongs to a broader class of fractions.

???+ abstract "Semiconvergent"
    Let a real number $x$ have the convergent $x_{k+1}=[a_0,a_1,\ldots,a_k,a_{k+1}]$, and let the integer $t$ satisfy $0\le t\le a_{k+1}$[^semi-range]. Then the fraction $x_{k,t}=[a_0,a_1,\ldots,a_{k},t]$ is called an **intermediate fraction**, **semiconvergent**, or **secondary convergent** of $x$.[^semiconvergent]
    
    As with convergents, semiconvergents larger (smaller) than $x$ are called **upper (lower) semiconvergents**.

By the recurrence, a semiconvergent can be written as

$$
x_{k,t} = \frac{tp_{k}+p_{k-1}}{tq_{k}+q_{k-1}}.
$$

It is always a reduced fraction, and it lies between the convergents $x_{k-1}$ and $x_{k+1}$. As $t$ increases, it moves steadily toward $x_{k+1}$ (taking even $k$ as an example):

$$
x_{k-1} = x_{k,0} < x_{k,1} < x_{k,2} < \cdots < x_{k,a_{k+1}} = x_{k+1}.
$$

Since the numerators and denominators of convergents are increasing, the numerator and denominator of a semiconvergent $x_{k,t}$ ($t\neq 0$) lie between those of $x_{k}$ and $x_{k+1}$. If we sort these fractions by denominator, the semiconvergents are the fractions lying between consecutive convergents.

Every best approximation of the first kind is a semiconvergent, but not every semiconvergent is a best approximation of the first kind.

???+ note "Theorem"
    Every best approximation of the first kind is a semiconvergent.

??? note "Proof"
    Since $a_0\le x\le a_0+1$, a best approximation of the first kind must lie between $x_{1,0}=a_0$ and $x_{0,1}=a_0+1$. All semiconvergents can be listed in increasing order as
    
    $$
    x_{1,0}<x_{1,1}< \cdots < x_{1,a_2}=x_{3,0}<\cdots<x<\cdots<x_{2,0}=x_{0,a_1}<\cdots<x_{0,1}.
    $$
    
    Semiconvergents of the same order appear consecutively, and there are no gaps between semiconvergents of different orders. This means any rational number $\dfrac{p}{q}$ between $x_{1,0}=a_0$ and $x_{0,1}=a_0+1$ must fall between two semiconvergents $x_{k,t}$ and $x_{k,t+1}$ of the same order. Without loss of generality, suppose it is not a semiconvergent and is less than $x$, so
    
    $$
    x_{k,t}<\dfrac{p}{q}<x_{k,t+1}<x.
    $$
    
    Now, on one hand,
    
    $$
    \left|x_{k,t}-\dfrac{p}{q}\right| < \left|x_{k,t}-x_{k,t+1}\right| = \dfrac{1}{((t+1)q_k+q_{k-1})(tq_k+q_{k-1})}.
    $$
    
    On the other hand,
    
    $$
    \left|x_{k,t}-\dfrac{p}{q}\right| = \dfrac{|q(tp_k+p_{k-1})-p(tq_k+q_{k-1})|}{q(tq_k+q_{k-1})}\ge\dfrac{1}{q(tq_k+q_{k-1})}.
    $$
    
    So we must have
    
    $$
    q>(t+1)q_k+q_{k-1}.
    $$
    
    That is, the denominator of the rational number $\dfrac{p}{q}$ is larger than that of $x_{k,t+1}$, yet it is not a better approximation:
    
    $$
    \left|x-\dfrac{p}{q}\right|>\left|x-x_{k,t+1}\right|
    $$
    
    So it cannot be a best approximation of the first kind. This shows that anything that is not a semiconvergent is not a best approximation of the first kind; that is, every best approximation of the first kind is a semiconvergent.

Conversely, we cannot claim that every semiconvergent is a best approximation of the first kind. But we can give the condition under which a semiconvergent is a best approximation of the first kind.

???+ note "Theorem"
    Every convergent is a best approximation of the first kind. Besides these, for $0<t<a_{k+1}$, the semiconvergent $x_{k,t}$ is a best approximation of the first kind if and only if $t>\dfrac{a_{k+1}}{2}$, or $t=\dfrac{a_{k+1}}{2}$ and $r_{k+2}>\dfrac{q_k}{q_{k-1}}$.

??? note "Proof"
    We will show below that convergents are all best approximations of the second kind, and so must be best approximations of the first kind. The key is the semiconvergents that are not convergents.
    
    As mentioned above, the denominator of a semiconvergent $x_{k,t}$ lies between those of $x_k$ and $x_{k+1}$ and increases with $t$, while $x_{k,t}$ moves closer to $x_{k+1}$ and hence closer to $x$. Taking $x_{k,t}<x$ as an example, its position relative to the nearby fractions is:
    
    $$
    x_{k-1} < x_{k,t} < x_{k+1} < x < x_{k}.
    $$
    
    Since the denominator of $x_k$ is smaller than that of $x_{k,t}$, a necessary condition for $x_{k,t}$ to be a best approximation of the first kind is that it is closer to $x$ than $x_k$. This is also sufficient: as a convergent, $x_k$ has no fraction with a smaller denominator that is closer, and any semiconvergent with a denominator larger than that of $x_k$ must be of the same order as $x_{k,t}$ but with a smaller denominator, so it must be farther from $x$. For the errors of the convergent and the semiconvergent, a computation gives
    
    $$
    \begin{aligned}
    \left|x_k-x\right| &= \dfrac{1}{q_k(r_{k+1}q_k+q_{k-1})},\\
    \left|x_{k,t}-x\right| &= \left|\dfrac{tp_{k}+p_{k-1}}{tq_{k}+q_{k-1}}-\dfrac{r_{k+1}p_{k}+p_{k-1}}{r_{k+1}q_{k}+q_{k-1}}\right| \\
    &=\dfrac{r_{k+1}-t}{(tq_{k}+q_{k-1})(r_{k+1}q_{k}+q_{k-1})}.
    \end{aligned}
    $$
    
    Here we used $r_{k+1}\ge a_{k+1}>t$. So $x_{k,t}$ is closer to $x$ than $x_k$, and is a best approximation of the first kind, if and only if
    
    $$
    \dfrac{r_{k+1}-t}{tq_{k}+q_{k-1}}<\dfrac{1}{q_k} \iff r_{k+1}<2t+\dfrac{q_{k-1}}{q_k}.
    $$
    
    There are three possible cases:
    
    1.  If $t<\dfrac{a_{k+1}}{2}$, then $2t<a_{k+1}$. Since both sides are integers, $2t\le a_{k+1}-1$, so $2t+\dfrac{q_{k-1}}{q_k}\le 2t+1\le a_{k+1}\le r_{k+1}$. In this case, $x_{k,t}$ is not a best approximation of the first kind;
    2.  If $t>\dfrac{a_{k+1}}{2}$, then $2t>a_{k+1}$. Since both sides are integers, $2t\ge a_{k+1}+1>r_{k+1}$. In this case, $x_{k,t}$ is a best approximation of the first kind;
    3.  If $a_{k+1}$ is even, there is a third case, $t=\dfrac{a_{k+1}}{2}$. The condition above is equivalent to $\dfrac{1}{r_{k+2}}=r_{k+1}-a_{k+1}<\dfrac{q_{k-1}}{q_k}$, that is, $r_{k+2}>\dfrac{q_k}{q_{k-1}}$.

So if we list all best approximations of the first kind of a real number $x$ in increasing order of denominator, the list splits into several segments according to which side of $x$ they lie on. Each segment consists of some number (possibly zero) of consecutive semiconvergents of the same order, and always ends with a convergent. Within a segment, the fractions stay on one side of $x$; consecutive segments alternate between the two sides of $x$.

??? example "Example: best approximations of the first kind of $\pi$"
    $\pi=[3,7,15,1,292,\ldots]$, so its first 15 best approximations of the first kind, by smallest denominator, are:
    
    $$
    \begin{aligned}
    &x_0 = \dfrac{3}{1},\
    x_{0,4} = \dfrac{13}{4},\
    x_{0,5} = \dfrac{16}{5},\
    x_{0,6} = \dfrac{19}{6},\
    x_1 = \dfrac{22}{7},\\
    &x_{1,8} = \dfrac{179}{57},\
    x_{1,9} = \dfrac{201}{64},\
    x_{1,10} = \dfrac{223}{71},\
    x_{1,11} = \dfrac{245}{78},\
    x_{1,12} = \dfrac{267}{85},\\
    &x_{1,13} = \dfrac{289}{92},\ 
    x_{1,14} = \dfrac{311}{99},\
    x_2 = \dfrac{333}{106},\
    x_3 = \dfrac{355}{113},\
    x_{3,146} = \dfrac{52163}{16604}.
    \end{aligned}
    $$

### Best approximations of the second kind

Best approximations of the second kind use $|qx-p|$ to measure how good an approximation is.

???+ abstract "Best approximation of the second kind"
    For a real number $x$ and a rational number $\dfrac{p}{q}$, if for every $\dfrac{p'}{q'}\neq \dfrac{p}{q}$ with $0<q'\le q$ we have
    
    $$
    \left|qx-p\right|<\left|q'x-p'\right|,
    $$
    
    then the rational number $\dfrac{p}{q}$ is called a **best approximation of the second kind** of the real number $x$.

The condition for a best approximation of the second kind is equivalent to

$$
\left|x-\dfrac{p}{q}\right|<\dfrac{q'}{q}\left|x-\dfrac{p'}{q'}\right|.
$$

Since $q'\le q$, the condition for a best approximation of the second kind is stricter than that of the first kind.

The best approximations of the second kind are exactly the convergents.

???+ note "Theorem"
    Every best approximation of the second kind is a convergent, and every convergent is a best approximation of the second kind.

??? note "Proof"
    For the first part, since a best approximation of the second kind is also a best approximation of the first kind, we only need to show that a semiconvergent that is not a convergent cannot be a best approximation of the second kind. Let $x_{k,t}=\dfrac{p}{q}$ be a semiconvergent but not a convergent. Assuming $x_{k,t}<x$, we have
    
    $$
    x_{k-1} < x_{k,t} < x_{k+1} < x < x_{k}.
    $$
    
    The error between $x_{k,t}$ and $x$ satisfies
    
    $$
    |x_{k,t}-x|\ge |x_{k,t}-x_{k+1}|=\left|\dfrac{p}{q}-\dfrac{p_{k+1}}{q_{k+1}}\right|=\dfrac{|pq_{k+1}-p_{k+1}q|}{qq_{k+1}}\ge\dfrac{1}{qq_{k+1}},
    $$
    
    and using the error estimate for convergents, we always have
    
    $$
    |qx_{k,t}-p| \ge \dfrac{1}{q_{k+1}} \ge |q_kx_k-p_k|,
    $$
    
    that is, $x_{k,t}$ approximates no better than $x_k$, which has a smaller denominator, so it cannot be a best approximation of the second kind.
    
    Conversely, for the second part we need to show that every convergent $x_k=\dfrac{p_k}{q_k}$ is a best approximation of the second kind. That is, for every fraction $\dfrac{p}{q}$ with $q\le q_k$, we have $|q_kx-p_k|<|qx-p|$. Ignoring the half-integer case, we can assume $k>0$. First, by the error estimate for convergents,
    
    $$
    |q_{k-1} x-p_{k-1}| \ge \frac{1}{q_{k-1}+q_{k}} \ge \dfrac{1}{q_{k+1}}\ge |q_kx-p_k|.
    $$
    
    All of these inequalities hold with equality if and only if $a_{k+1}=1$ and it is the last term of the continued fraction. Excluding this case, $x_{k-1}=\dfrac{p_{k-1}}{q_{k-1}}$ is strictly worse than $x_k=\dfrac{p_k}{q_k}$.
    
    Take any fraction $\dfrac{p}{q}\neq x_k$ with $0<q\le q_k$. Since the difference formula gives $p_{k}q_{k-1} - p_{k-1}q_{k} = (-1)^{k-1}$, Cramer's rule shows that the linear system
    
    $$
    \begin{cases}
    \lambda p_k+\mu p_{k-1} = p,\\
    \lambda q_k+\mu q_{k-1} = q
    \end{cases}
    $$
    
    has a unique integer solution $(\lambda,\mu)$. If $\lambda\mu>0$, then $q>|\lambda|q_k\ge q_k$, a contradiction. Otherwise, $\lambda\mu\le 0$, that is, $\lambda$ and $\mu$ have opposite signs. Since $q_{k-1}x-p_{k-1}$ and $q_kx-p_k$ also have opposite signs, $\lambda(q_{k-1}x-p_{k-1})$ and $\mu(q_kx-p_k)$ have the same sign, so
    
    $$
    |qx-p|=|\lambda||q_kx-p_k|+|\mu||q_{k-1}x-p_{k-1}|>|q_{k}x-p_{k}|.
    $$
    
    The last inequality is strict because $x_{k-1}$ is strictly worse than $x_k$ and $\dfrac{p}{q}\neq x_k$. This shows that $x_k$ is a best approximation of the second kind.

This property shows that convergents really are quite good Diophantine approximations.

### Recognizing convergents

Best approximations of the second kind give a necessary and sufficient condition for a fraction to be a convergent. This means we can decide whether a fraction is a convergent by checking how well it approximates relative to other fractions. Legendre's criterion gives a way to recognize convergents from how well they approximate in absolute terms. The original statement of Legendre's criterion gives a necessary and sufficient condition, but its form is not practical. This section gives a simplified version of Legendre's criterion and shows that it does not miss too many convergents.

???+ note "Theorem (Legendre)"
    For a real number $x$ and a fraction $\dfrac{p}{q}$, if
    
    $$
    \left|x-\dfrac{p}{q}\right|<\dfrac{1}{2q^2}
    $$
    
    then $\dfrac{p}{q}$ must be a convergent of $x$.

??? note "Proof"
    Let $\epsilon\in\{-1,1\}$ and $\theta\in(0,1/2)$ be the constants such that
    
    $$
    x-\dfrac{p}{q} = \dfrac{\epsilon\theta}{q^2}
    $$
    
    holds. Expand the rational number $\dfrac{p}{q}$ as a continued fraction $[a_0,a_1,\ldots,a_n]$. A rational number has two continued fraction representations whose values of $n$ differ by exactly one, so we can choose the representation with $(-1)^n=\epsilon$, and denote its convergents by $\dfrac{p_k}{q_k}$. Let the real number $\omega$ satisfy
    
    $$
    x = \dfrac{\omega p_n+p_{n-1}}{\omega q_n+q_{n-1}}.
    $$
    
    Then we must have
    
    $$
    \dfrac{\epsilon\theta}{q^2} = x-\dfrac{p}{q} = x-\dfrac{p_n}{q_n} = \dfrac{p_{n-1}q_n-p_nq_{n-1}}{(\omega q_n+q_{n-1})q_n} = \dfrac{(-1)^n}{(\omega q_n+q_{n-1})q_n}.
    $$
    
    So
    
    $$
    \theta = \dfrac{q_n}{\omega q_n+q_{n-1}}.
    $$
    
    This shows
    
    $$
    \omega=\dfrac{1}{\theta}-\dfrac{q_{n-1}}{q_n}>1.
    $$
    
    Expand $\omega$ as a continued fraction $[b_0,b_1,\ldots]$ as well. Then
    
    $$
    x = \dfrac{\omega p_n+p_{n-1}}{\omega q_n+q_{n-1}} = [a_0,a_1,\ldots,a_n,\omega] = [a_0,a_1,\ldots,a_n,b_0,b_1,\ldots].
    $$
    
    This is a valid simple continued fraction, so $\dfrac{p}{q}$ is a convergent of $x$.
    
    This proof actually shows that $\dfrac{p}{q}$ is a convergent if and only if $\omega>1$ in the proof above. This is exactly the original form of Legendre's criterion.

This criterion says that any approximation that is good enough must be a convergent. The next theorem says there are plenty of such good convergents: at least half of all convergents satisfy this condition.

???+ note "Theorem (Vahlen)"
    Of any two consecutive convergents of a real number $x$, at least one satisfies
    
    $$
    \left|x-\dfrac{p}{q}\right|<\dfrac{1}{2q^2}.
    $$

??? note "Proof"
    Suppose not. Then there is a real number $x$ with two consecutive convergents $x_k$ and $x_{k+1}$ such that
    
    $$
    \left|x-\dfrac{p_k}{q_k}\right|\ge \dfrac{1}{2q_{k}^2},\ \left|x-\dfrac{p_{k+1}}{q_{k+1}}\right|\ge \dfrac{1}{2q_{k+1}^2}.
    $$
    
    Since $x$ lies between $x_k$ and $x_{k+1}$,
    
    $$
    \dfrac{1}{2q_{k}^2} + \dfrac{1}{2q_{k+1}^2} \le \left|x-\dfrac{p_k}{q_k}\right| + \left|x-\dfrac{p_{k+1}}{q_{k+1}}\right| = \left|\dfrac{p_k}{q_k}-\dfrac{p_{k+1}}{q_{k+1}}\right| = \dfrac{1}{q_kq_{k+1}}.
    $$
    
    This shows $q_k=q_{k+1}$. So we must have $k=0$ and $a_1=1$. Then the first two convergents are $x_0=a_0$ and $x_1=a_0+1$. So the only counterexamples to the statement are half-integers, which, as explained above, this page does not consider.

## Geometric interpretation

The theory of continued fractions has a beautiful geometric interpretation.

![](./images/continued-convergents-geometry.svg)

As shown in the figure, for a real number $\xi>0$, the line $y=\xi x$ splits the lattice points in the first quadrant (including points on the $x$ and $y$ axes but excluding the origin; the same below) into an upper part and a lower part. When $\xi$ is rational, points on the line $y=\xi x$ count both as points above the line and as points below the line. Consider the convex hulls of these two sets of points. Then the odd-indexed convergents are the vertices of the convex hull of the upper part, and the even-indexed convergents are the vertices of the convex hull of the lower part. The lattice points on the segments between two adjacent vertices of a hull are the semiconvergents. The figure shows the convergents and semiconvergents (gray points) of $\xi=\dfrac{9}{7}$.

Most of the earlier results about continued fractions have a geometric interpretation:

??? note "Geometric interpretation"
    -   Each fraction $\nu=\dfrac{p}{q}$ corresponds to a lattice point $\vec\nu=(q,p)$ in the first quadrant, and the value of the fraction corresponds to the slope of the line through it and the origin.
    -   The direction vector of the line $y=\xi x$ is $\vec\xi=(1,\xi)$. Using the [cross product](../linear-algebra/product.md#the-2d-case) $(x_1,y_1)\times(x_2,y_2)=x_1y_2-x_2y_1$, we can tell whether a point is above or below the line from the sign of $\vec\xi\times\vec\nu=p-q\xi$. So points above the line correspond to fractions greater than or equal to $\xi$, and points below the line correspond to fractions less than or equal to $\xi$. The absolute value of the cross product $|\vec\xi\times\vec\nu|$ is proportional to the distance from the point $\vec\nu$ to the line $y=\xi x$
    
        $$
        \dfrac{|p-q\xi|}{\sqrt{1+\xi^2}},
        $$
    
        which measures how well the fraction $\nu$ approximates the real number $\xi$.
    -   Denote the point of the convergent $\xi_k=\dfrac{p_k}{q_k}$ by $\vec\xi_k=(q_k,p_k)$. Then the recurrence can be written as
    
        $$
        \vec\xi_k = a_k\vec\xi_{k-1} + \vec\xi_{k-2}.
        $$
    
        The recursion starts from $\vec\xi_{-2} = (1,0)$ and $\vec\xi_{-1} = (0,1)$.
    -   For an integer $t$ with $0\le t\le a_k$, the point
    
        $$
        \vec\xi_{k-1,t} = t\vec\xi_{k-1} + \vec\xi_{k-2}
        $$
    
        lies on the segment joining $\vec\xi_{k-2}$ and $\vec\xi_k$. These points correspond to the semiconvergents $\xi_{k-1,t}$.
    -   All convergents and semiconvergents can be constructed geometrically. Start from the points $\vec\xi_{-2}=(1,0)$ and $\vec\xi_{-1}=(0,1)$. The two points lie on opposite sides of the line $y=\xi x$, which means $\vec\xi\times\vec\xi_{-2}$ and $\vec\xi\times\vec\xi_{-1}$ have opposite signs. Add $\vec\xi_{-1}$ to $\vec\xi_{-2}$ by vector addition repeatedly, until adding it again would cross the line $y=\xi x$; call the result $\vec\xi_0$. It is still on the opposite side from $\vec\xi_{-1}$. Then add $\vec\xi_0$ to $\vec\xi_{-1}$ repeatedly, until adding it again would cross the line $y=\xi x$; call the result $\vec\xi_1$. It is still on the opposite side from $\vec\xi_0$. This process can go on forever, unless some $\vec\xi_n$ lands exactly on the line $y=\xi x$ after finitely many steps. The latter means the vectors $\vec\xi$ and $\vec\xi_n$ are collinear, that is, $\xi=\dfrac{p_n}{q_n}$ is a rational point. This process produces the figure shown above. Boris Delaunay vividly called this process the nose-stretching algorithm[^nose-stretching].
    -   To quickly compute how many times $\vec\xi_{k-1}$ is added to $\vec\xi_{k-2}$ in each step, we can use the cross product. Since $\vec\xi\times\vec\xi_{k-1}$ and $\vec\xi\times\vec\xi_{k-2}$ have opposite signs, if $\vec\xi_{k-1,t}=t\vec\xi_{k-1}+\vec\xi_{k-2}$ denotes the result of adding $\vec\xi_{k-1}$ to $\vec\xi_{k-2}$ $t$ times, then the line is not crossed as long as $\vec\xi\times\vec\xi_{k-1,t}=t(\vec\xi\times\vec\xi_{k-1})+(\vec\xi\times\vec\xi_{k-2})$ keeps its sign. Until the sign changes, the absolute value of $\vec\xi\times\vec\xi_{k-1,t}$ keeps decreasing. Let
    
        $$
        r_{k} = \left|\dfrac{\vec\xi\times\vec\xi_{k-2}}{\vec\xi\times\vec\xi_{k-1}}\right| = -\dfrac{\vec\xi\times\vec\xi_{k-2}}{\vec\xi\times\vec\xi_{k-1}}.
        $$
    
        Then the maximum number of decreasing steps is
    
        $$
        a_{k} = \lfloor r_{k}\rfloor = \left\lfloor\left|\dfrac{q_{k-1}\xi-p_{k-1}}{q_{k-2}\xi-p_{k-2}}\right|\right\rfloor.
        $$
    
        This is the $k$-th term of the continued fraction expansion. Moreover, $r_k$ is exactly the remainder of the continued fraction expansion, and it satisfies:
    
        $$
        r_k = -\dfrac{q_{k-1}\xi-p_{k-1}}{q_{k-2}\xi-p_{k-2}} \iff \xi = \dfrac{p_{k-1}r_k + p_{k-2}}{q_{k-1}r_k+q_{k-2}}.
        $$
    
        This is the continued fraction relation $\xi = [a_0,a_1,\ldots,a_{k-1},r_k]$.
    -   Since each added vector changes $\vec\xi\times\vec\xi_{k-1,t}$ by a step of $|\vec\xi\times\vec\xi_{k-1}|$, the remaining distance $|\vec\xi\times\vec\xi_k|$ at the end must be strictly smaller than $|\vec\xi\times\vec\xi_{k-1}|$. This shows that the quality of approximation of the convergents (measured by $|qx-p|$) strictly improves as $k$ increases.
    -   By the rules of the cross product,
    
        $$
        \vec\xi_{k}\times\vec\xi_{k+1} = \vec\xi_{k}\times(a_{k+1}\vec\xi_k+\vec\xi_{k-1}) = \vec\xi_{k}\times\vec\xi_{k-1} = -\vec\xi_{k-1}\times\vec\xi_{k}.
        $$
    
        By induction,
    
        $$
        \vec\xi_{k}\times\vec\xi_{k+1} = (-1)^{k+2}\vec\xi_{k-2}\times\vec\xi_{k-1} = (-1)^{k}.
        $$
    
        This is the difference formula for convergents, $p_{k+1}q_k-p_kq_{k+1}=(-1)^k$.
    -   The region between the upper and lower convex hulls can be divided into several (possibly infinitely many) triangles, each with vertices $\vec\xi_{k-2}$, $\vec\xi_k$ and $\vec 0$. The area of such a triangle is
    
        $$
        \dfrac12|\vec\xi_{k-2}\times\vec\xi_k| = \dfrac12|\vec\xi_{k-2}\times(a_k\vec\xi_{k-1}+\vec\xi_{k-2})| = \dfrac{a_k}{2}|\vec\xi_{k-2}\times\vec\xi_{k-1}| = \dfrac{a_k}{2}.
        $$
    
        By [Pick's theorem](../../geometry/pick.md), if $I$ and $B$ are the numbers of lattice points inside the triangle and on its boundary, then
    
        $$
        I + \dfrac{B}{2} - 1 = \dfrac{a_k}{2}.
        $$
    
        We already know the boundary of the triangle contains the $a_k+2$ lattice points $\{\vec 0\}\cup\{\vec\xi_{k-1,t}:0\le t\le a_k\}$. So we must have $I=0$ and $B=a_k+2$. Hence there are no more lattice points on the edges of the triangle, and no lattice points inside it. That is, $q_k$ and $p_k$ are coprime, the semiconvergents are all the lattice points on the edge joining $\vec\xi_{k-2}$ and $\vec\xi_k$, and all lattice points in the first quadrant lie inside the upper and lower convex hulls.

The upper and lower convex hulls obtained this way are called Klein polygons. A similar definition works in higher dimensions and gives the [Klein polyhedron](https://en.wikipedia.org/wiki/Klein_polyhedron), which generalizes continued fractions to higher-dimensional spaces.

## Continued fractions and trees

Main article: [Stern–Brocot tree and Farey sequences](./stern-brocot.md)

The Stern–Brocot tree is a [binary search tree](../../ds/bst.md) that stores all fractions in $[0,\infty]$. A finite continued fraction actually encodes the path in the Stern–Brocot tree from the root to the position of some fraction. That is, the continued fraction representation $[a_0,a_1,\ldots,a_{n-1},1]$ of a rational number $x$ means: starting from the root $\dfrac{1}{1}$, first move to the right child $a_0$ times, then to the left child $a_1$ times, and keep alternating directions until you have moved $a_{n-1}$ times in some direction. Note that only the representation ending in $1$ can be used here.

Viewing a continued fraction representation as a path in the Stern–Brocot tree gives an algorithm for comparing continued fractions.

???+ example "Comparing continued fractions"
    Given continued fractions $\alpha=[\alpha_0,\alpha_1,\ldots,\alpha_n]$ and $\beta=[\beta_0,\beta_1,\ldots,\beta_m]$, compare them.

??? note "Solution"
    First convert both continued fraction representations to the form ending in $1$. Without loss of generality, assume the given continued fractions are already in this form, that is, $\alpha_n=\beta_m=1$. Since even positions (indexed from $0$) are the numbers of steps to the right, and odd positions are the numbers of steps to the left, $\alpha<\beta$ if and only if, in [lexicographic order](../../string/basic.md#lexicographic-order),
    
    $$
    (\alpha_0,-\alpha_1,\alpha_2,\ldots,(-1)^{n-1}\alpha_{n-1},0,\ldots)<(\beta_0,-\beta_1,\beta_2,\ldots,(-1)^{m-1}\beta_{m-1},0,\ldots).
    $$
    
    Compared with the continued fraction representation, we alternate the signs, drop the trailing $1$, and pad the missing positions with $0$.
    
    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/compare.cpp:core"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/compare.py:core"
        ```

???+ example "Best inner point"
    For $\dfrac{0}{1}\le\dfrac{p_0}{q_0}<\dfrac{p_1}{q_1}\le\dfrac{1}{0}$, find the rational number $\dfrac{p}{q}$ with the smallest $(q,p)$ such that $\dfrac{p_0}{q_0}<\dfrac{p}{q}<\dfrac{p_1}{q_1}$.

??? note "Solution"
    Since the Stern–Brocot tree is both a binary search tree of the fractions in $[0,\infty]$ and a [Cartesian tree](../../ds/cartesian-tree.md) of the pairs $(q,p)$, the problem almost reduces to finding the LCA (lowest common ancestor) of two nodes in the Stern–Brocot tree. But the LCA only handles closed intervals, and the LCA might be one of the endpoints itself. To avoid extra case analysis, we can first construct $\dfrac{p_0}{q_0}+\varepsilon$ and $\dfrac{p_1}{q_1}-\varepsilon$, and then compute the LCA. Once the paths from the root to the nodes have been computed via continued fractions, the LCA is just the longest common prefix of the paths.
    
    To construct $x\pm\varepsilon$, just move once to the right (left) at node $x$, then move $\infty$ times to the left (right). In the language of continued fractions, for a fraction $x=[a_0,a_1,\ldots,a_{n-1},1]$, $x\pm\varepsilon$ must be $[a_0,a_1,\ldots,a_{n-1}+1,\infty]$ and $[a_0,a_1,\ldots,a_{n-1},1,\infty]$. So we only need to compare these two continued fractions and define the larger (smaller) one as $x\pm\varepsilon$.
    
    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/inner-point.cpp:core"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/inner-point.py:core"
        ```

???+ example "[GCJ 2019, Round 2 - New Elements: Part 2](https://github.com/google/coding-competitions-archive/blob/main/codejam/2019/round_2/new_elements_part_2/statement.pdf)"
    Given $N$ pairs of positive integers $(C_i,J_i)$, find a pair of positive integers $(x,y)$ such that $\{C_ix+J_iy\}$ is strictly increasing. Among all valid pairs, output the lexicographically smallest one.

??? note "Solution"
    Let $A_i=C_i-C_{i-1}$ and $B_i=J_i-J_{i-1}$. The problem becomes finding $(x,y)$ such that every $A_ix+B_iy$ is positive. These pairs fall into four cases:
    
    1.  The case $A_i,B_i>0$ can be ignored, since we already assume $(x,y)>0$;
    2.  In the case $A_i,B_i\le 0$, output "IMPOSSIBLE" directly;
    3.  The case $A_i>0,B_i\le 0$ is equivalent to the constraint $\dfrac{y}{x}<\dfrac{A_i}{-B_i}$;
    4.  The case $A_i\le 0,B_i>0$ is equivalent to the constraint $\dfrac{y}{x}>\dfrac{-A_i}{B_i}$.
    
    So let $\dfrac{p_0}{q_0}$ be the largest $\dfrac{-A_i}{B_i}$ from the fourth case, and let $\dfrac{p_1}{q_1}$ be the smallest $\dfrac{A_i}{-B_i}$ from the third case. The original problem becomes finding the lexicographically smallest $(q,p)$ such that $\dfrac{p_0}{q_0}<\dfrac{p}{q}<\dfrac{p_1}{q_1}$.
    
    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/gcj-2019.cpp:core"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/gcj-2019.py:core"
        ```

To learn more about the properties and applications of the Stern–Brocot tree, see its main article.

## Fractional linear transformations

Another important concept related to continued fractions is the fractional linear transformation.

???+ abstract "Fractional linear transformation"
    A **fractional linear transformation** is a function $L:\mathbf R\rightarrow\mathbf R$ such that
    
    $$
    L(x) = \dfrac{ax+b}{cx+d},
    $$
    
    where $a,b,c,d\in\mathbf R$ and $ad-bc\neq 0$.

???+ info "About the condition $ad-bc\neq 0$"
    It is easy to check that when $ad-bc=0$, the function may be undefined or constant.

Fractional linear transformations have the following properties:

???+ note "Properties of fractional linear transformations"
    Let $L_1,L_2,L_3$ be fractional linear transformations, and let the matrix formed by the coefficients of $L_i$ be
    
    $$
    M_i=\begin{pmatrix}a_i & b_i \\ c_i & d_i\end{pmatrix}
    $$
    
    Then they have the following properties:[^pgl2]
    
    1.  The composition $L_1\circ L_2$ and the inverse $L_1^{-1}$ of fractional linear transformations are still fractional linear transformations; that is, all fractional linear transformations form a [group](../algebra/basic.md#groups);
    2.  A fractional linear transformation does not change when all its coefficients are multiplied by the same non-zero constant; that is, for any $\lambda\neq 0$, if $M_2=\lambda M_1$, then $L_2=L_1$;
    3.  The coefficient matrix of a composition of fractional linear transformations corresponds to the product of the coefficient matrices; that is, if $M_1M_2=M_3$, then $L_1\circ L_2=L_3$;
    4.  The coefficient matrix of the inverse of a fractional linear transformation corresponds to the inverse of the coefficient matrix; that is, if $M_1^{-1}=M_2$, then $L_1^{-1}=L_2$.

??? note "Proof"
    Here we only give the forms of the composition and the inverse of fractional linear transformations. Once we have these forms, all the properties are easy to check.
    
    The composition of fractional linear transformations $L_1$ and $L_2$:
    
    $$
    \begin{aligned}
    L_1\circ L_2 &= \dfrac{a_1\dfrac{a_2x+b_2}{c_2x+d_2}+b_1}{c_1\dfrac{a_2x+b_2}{c_2x+d_2}+d_1} = \dfrac{(a_1a_2+b_1c_2)x+(a_1b_2+b_1d_2)}{(c_1a_2+d_1c_2)x+(c_1b_2+d_1d_2)}.
    \end{aligned}
    $$
    
    The inverse of the fractional linear transformation $L_1(x)$:
    
    $$
    y = L_1(x) = \dfrac{a_1x+b_1}{c_1x+d_1} \iff x = L_1^{-1}(y) = \dfrac{d_1y - b_1}{-c_1y + a_1}.
    $$

A finite continued fraction $[a_0,a_1,\ldots,a_n]$ can be seen as the result of composing a series of fractional linear transformations. Let

$$
L_i(x) = \dfrac{a_ix+1}{x} = [a_i,x]. 
$$

Then the finite continued fraction is

$$
[a_0,a_1,\ldots,a_n] = L_0\circ L_1\circ\cdots\circ L_n(\infty).
$$

Here the value of the fractional linear transformation $L(x)=\dfrac{ax+b}{cx+d}$ at $x=\infty$ is $\dfrac{a}{c}$, which is the limit of the function as $x\rightarrow\pm\infty$.

For a general continued fraction, let $r_{k+1}$ be a remainder of the real number $x$, that is, $x=[a_0,\ldots,a_k,r_{k+1}]$. Then

$$
x = L_0\circ L_1\circ\cdots\circ L_k(r_{k+1}) = \dfrac{p_kr_{k+1}+p_{k-1}}{q_kr_{k+1}+q_{k-1}}.
$$

This also gives the form of the fractional linear transformation $L_0\circ L_1\circ\cdots\circ L_k$.

Of course, this expression can also be checked directly. At the very beginning we have

$$
x=\dfrac{x+0}{0x+1}=\dfrac{p_{-1}x+p_{-2}}{q_{-1}x+q_{-2}}.
$$

Then, if $L_0\circ L_1\circ\cdots\circ L_{k-1}$ has the form

$$
\dfrac{p_{k-1}x+p_{k-2}}{q_{k-1}x+q_{k-2}}
$$

then by the composition formula for fractional linear transformations,

$$
L_0\circ L_1\circ\cdots\circ L_{k-1}\circ L_k = \dfrac{(p_{k-1}a_k+p_{k-2})x+p_{k-1}}{(q_{k-1}a_k+q_{k-2})x+q_{k-1}} = \dfrac{p_kx+p_{k-1}}{q_kx+q_{k-1}}.
$$

This proves the form above by induction. Fractional linear transformations also give another way to understand the recurrence and its initial values.

???+ example "[DMOPC '19 Contest 7 P4 - Bob and Continued Fractions](https://dmoj.ca/problem/dmopc19c7p4)"
    Given an array of positive integers $a_1,\ldots,a_n$ and $m$ queries. Each query gives $l\le r$ and asks for the value of $[a_l,\ldots,a_r]$.

??? note "Solution"
    View the continued fraction as the value at $x=\infty$ of a composition of a sequence of fractional linear transformations. Then we just need to answer many queries for the composition of a range of fractional linear transformations. Since every fractional linear transformation is invertible, we can precompute prefix compositions and answer queries by "subtracting" prefixes, in $O(n+m)$ time; if updates are needed, we can also store them in a segment tree or a similar structure.
    
    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/flt-presum.cpp"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/flt-presum.py"
        ```

### Arithmetic on continued fractions

Using fractional linear transformations, we can do arithmetic (addition, subtraction, multiplication and division) on continued fractions. This algorithm was first proposed by Gosper.

The cornerstone of the algorithm is applying a fractional linear transformation to a continued fraction. This section uses finite continued fractions as an example. But since the algorithm only needs to read finitely many terms of the continued fraction to output each term, it also works for infinite continued fractions and can compute to any precision. Combined with the comparison algorithm for continued fractions above, it can compare real numbers exactly to any precision.

???+ example "Fractional linear transformation of a continued fraction"
    Given a fractional linear transformation $L(x)=\dfrac{ax+b}{cx+d}$ and a continued fraction $\alpha=[\alpha_0,\alpha_1,\ldots,\alpha_n]$, find the continued fraction representation $[\beta_0,\beta_1,\ldots,\beta_m]$ of $\beta=L(\alpha)$.

??? note "Solution"
    The basic idea of the algorithm is to determine the values $\beta_i$ one by one. Let
    
    $$
    L_\gamma(x) = \gamma+\dfrac{1}{x} = \dfrac{\gamma x+1}{x}.
    $$
    
    Since the continued fraction gives
    
    $$
    L(\alpha) = L\circ L_{\alpha_0}\circ L_{\alpha_1}\circ\cdots\circ L_{\alpha_n}(\infty),
    $$
    
    we can compute $L(\alpha)$ by composing $L$ with $L_{\alpha_k}$ step by step. But if we want the continued fraction representation of $L(\alpha)$, we don't need to compute the full value of $L(\alpha)$ first and then find its continued fraction representation. We can determine the values of $\beta_0,\beta_1,\ldots$ while composing the $L_{\alpha_i}$.
    
    For example, suppose we have computed
    
    $$
    L\circ L_{\alpha_0}\circ L_{\alpha_1}\circ\cdots\circ L_{\alpha_k}(x) = \dfrac{a_kx+b_k}{c_kx+d_k}
    $$
    
    and $c_k,d_k$ have the same sign. Then $L\circ L_{\alpha_0}\circ L_{\alpha_1}\circ\cdots\circ L_{\alpha_k}(x)$ is monotonic on $[0,\infty]$, and its value must lie between $\dfrac{a_k}{c_k}$ and $\dfrac{b_k}{d_k}$. So if
    
    $$
    \left\lfloor\dfrac{a_k}{c_k}\right\rfloor = \left\lfloor\dfrac{b_k}{d_k}\right\rfloor,
    $$
    
    we know that this is the integer part $\beta_0$ of $L\circ L_{\alpha_0}\circ L_{\alpha_1}\circ\cdots\circ L_{\alpha_k}(x)$. Then composing $L_{\beta_0}^{-1}$ on the left gives
    
    $$
    L_{\beta_0}^{-1}\circ L\circ L_{\alpha_0}\circ L_{\alpha_1}\circ\cdots\circ L_{\alpha_k}.
    $$
    
    Now we keep adding $L_{\alpha_{k+1}},L_{\alpha_{k+2}},\ldots$ until we can determine the new integer part, that is, $\beta_1$. We continue this way until all values $\beta_j$ are determined.
    
    The algorithm requires $c$ and $d$ to have the same sign to make sure the discontinuity of the function is not in $[0,\infty]$. This is always achievable, because the definition of a simple continued fraction requires the coefficients (except $\alpha_0$) to be positive integers. From this one can show that $c$ and $d$ must have the same sign after finitely many steps, and keep the same sign from then on.
    
    In the implementation, we just maintain the coefficient matrix $\begin{pmatrix}a&b\\c&d\end{pmatrix}$ of the current fractional linear transformation, and check whether $c$ and $d$ have the same sign and whether $\dfrac{a}{c}$ and $\dfrac{b}{d}$ have the same integer part. Composing $L_{\alpha_i}$ on the right gives $\begin{pmatrix}a\alpha_i+b&a\\ c\alpha_i+d&c\end{pmatrix}$. If the two integer parts are both equal to $\beta_j$, append $\beta_j$ to the resulting continued fraction and compose $L_{\beta_j}^{-1}$ on the left, which amounts to computing $\begin{pmatrix}c&d\\ a\bmod c & b \bmod d \end{pmatrix}$.

Fractional linear transformations of continued fractions are already enough for arithmetic between a fraction and a continued fraction:

$$
\dfrac{p}{q}\pm x = \dfrac{\pm qx+p}{0x+q},\ \dfrac{p}{q}x = \dfrac{px+0}{0x+q},\ \frac{p}{q}/x = \dfrac{0x+p}{qx+0}.
$$

For arithmetic between two general continued fractions, we need bilinear fractional transformations:

$$
x+y = \dfrac{0xy+x+y+0}{0xy+0x+0y+1},\ xy = \dfrac{1xy+0x+0y+0}{0xy+0x+0y+1},\ \dfrac{x}{y} = \dfrac{0xy+x+0y+0}{0xy+0x+y+0}.
$$

???+ example "Bilinear fractional transformation of continued fractions"
    Given a bilinear fractional transformation $L(x,y)=\dfrac{axy+bx+cy+d}{exy+fx+gy+h}$ and continued fractions $\alpha=[\alpha_0,\alpha_1,\ldots,\alpha_n]$ and $\beta=[\beta_0,\beta_1,\ldots,\beta_m]$, find the continued fraction representation $[\gamma_0,\gamma_1,\ldots,\gamma_\ell]$ of $\gamma=L(\alpha,\beta)$.

??? note "Solution"
    As in the single-variable case, to determine an integer part we just need the integer part of the current transformation to stay constant over $(x,y)\in[0,\infty]\times[0,\infty]$, that is, $e,f,g,h$ all have the same sign, and
    
    $$
    \left\lfloor\dfrac{a}{e}\right\rfloor = \left\lfloor\dfrac{b}{f}\right\rfloor = \left\lfloor\dfrac{c}{g}\right\rfloor = \left\lfloor\dfrac{d}{h}\right\rfloor.
    $$
    
    Composition on the right becomes computing $L(x,y)\mapsto L(L_{\alpha_i}(x),y)$ and $L(x,y)\mapsto L(x,L_{\beta_j}(y))$, which can also be expressed as linear transformations of the coefficients. Composition on the left is exactly the same as in the single-variable case: just take remainders.
    
    Compared with the single-variable case, the two-variable case needs to decide whether to compose $L_{\alpha_i}$ or $L_{\beta_j}$ first. Since the order of composition does not affect the final result, we can choose the order freely, for example alternating between $L_{\alpha_i}$ and $L_{\beta_j}$. Or we can use a rule of thumb and first compose along the dimension where the ratios differ more: if $\left|\dfrac{b}{f}-\dfrac{d}{h}\right|>\left|\dfrac{c}{g}-\dfrac{d}{h}\right|$, compose $L_{\alpha_i}$ first; otherwise, compose $L_{\beta_j}$ first.

## Periodic continued fractions

Similar to repeating decimals, if the coefficients of a continued fraction form a repeating cycle, it is called a periodic continued fraction.

???+ abstract "Periodic continued fraction"
    Let $x=[a_0,a_1,a_2,\ldots]$ be a continued fraction. If there exist a natural number $K$ and a positive integer $L$ such that $a_k=a_{k+L}$ for every $k\ge K$, then $x$ is called a **periodic continued fraction**. The smallest such $L$ is called its minimal period, and the sequence $a_{k},\ldots,a_{k+L-1}$ that repeats in the continued fraction is called its repeating block. Using the repeating block, a periodic continued fraction can be written as $x=[a_0,\ldots,a_{k-1},\overline{a_k,\ldots,a_{k+L-1}}]$. If $K$ can be taken to be $0$, that is, $x=[\overline{a_0,\ldots,a_{L-1}}]$, it is called a **purely periodic continued fraction**; otherwise, it is called an **eventually periodic continued fraction**.

### Quadratic irrationals

A concept closely related to periodic continued fractions is the [(real) quadratic irrational](./quadratic.md), that is, an irrational solution of a quadratic equation with integer coefficients. Every quadratic irrational can be written in the form

$$
a+b\sqrt D
$$

where $a,b$ are rational and $D$ is a square-free positive integer. Quadratic irrationals on this page are always assumed to be real. Also, the conjugate of $a+b\sqrt D$ is $a-b\sqrt{D}$.

A result of Euler shows that every periodic continued fraction is a quadratic irrational.

???+ note "Theorem (Euler)"
    Every periodic continued fraction represents a quadratic irrational.

??? note "Proof"
    For a general periodic continued fraction $x=[a_0,\ldots,a_{k-1},\overline{a_k,\ldots,a_{k+L-1}}]$, let $y=[\overline{a_k,\ldots,a_{k+L-1}}]$. Then
    
    $$
    \begin{aligned}
    x&=[a_0,\ldots,a_{k-1},y] = L_0(y),\\
    y&=[a_k,\ldots,a_{k+L-1},y] = L_1(y),
    \end{aligned}
    $$
    
    where $L_0(\cdot)$ and $L_1(\cdot)$ are both fractional linear transformations. So $x$ satisfies the equation
    
    $$
    x = L_0\circ L_1\circ L_0^{-1}(x). 
    $$
    
    Let the fractional linear transformation be $L_0\circ L_1\circ L_0^{-1}(x) = \dfrac{ax+b}{cx+d}$. Then $x$ satisfies the equation
    
    $$
    cx^2+(d-a)x-b=0.
    $$
    
    So every periodic continued fraction is a solution of a quadratic equation with integer coefficients. And since every infinite continued fraction is irrational, every periodic continued fraction represents a quadratic irrational.

A result of Lagrange shows that the converse also holds, so quadratic irrationals and periodic continued fractions are equivalent.

???+ note "Theorem (Lagrange)"
    Every quadratic irrational can be written as a periodic continued fraction.

??? note "Proof"
    The idea is to show that the remainders repeat. Let the quadratic irrational $x$ be written in the form
    
    $$
    x = \dfrac{P_0+\sqrt{D}}{Q_0}
    $$
    
    where $P_0,Q_0,D$ are integers and $Q_0\mid D-P_0^2$. This is always possible. For example, a quadratic irrational $x$ can always be written as
    
    $$
    a+b\sqrt{D'} = \dfrac{p_a}{q_a}+\dfrac{p_b}{q_b}\sqrt{D'} = \dfrac{p_aq_b+\sqrt{p_b^2q_a^2D'}}{q_aq_b} = \dfrac{p_aq_aq_b^2+\sqrt{(q_aq_b)^2p_b^2q_a^2D'}}{(q_aq_b)^2}
    $$
    
    and then we take $P=p_aq_aq_b^2$, $Q=(q_aq_b)^2$ and $D=Qp_b^2q_a^2D'$ (here we assume $b>0$; if $b<0$, just negate both $P$ and $Q$).
    
    The advantage of this form is that we can show all its remainders have a similar form:
    
    $$
    r_k=\dfrac{P_k+\sqrt D}{Q_k},
    $$
    
    where $P_k,Q_k$ are integers and $Q_k\mid D-P_k^2$. The condition $Q_k\mid D-P_k^2$ ensures that in the numerators of all remainders, the coefficient of $\sqrt{D}$ is $1$.
    
    To get the form of the remainders, we use induction. The case $k=0$ is obvious. Suppose we already have the form of $r_k$, and let $a_k=\lfloor r_k\rfloor$. Then
    
    $$
    r_k = a_k+\dfrac{1}{r_{k+1}}.
    $$
    
    Suppose $r_{k+1}$ has a similar form, and substitute it together with $r_k$ into the equation above:
    
    $$
    \dfrac{P_k+\sqrt D}{Q_k} = a_k + \dfrac{Q_{k+1}}{P_{k+1}+\sqrt{D}} = a_k + \dfrac{Q_{k+1}P_{k+1}-Q_{k+1}\sqrt{D}}{P_{k+1}^2-D}.
    $$
    
    Since a quadratic irrational can be written as $a+b\sqrt{D}$ in only one way, comparing coefficients on both sides gives
    
    $$
    \dfrac{P_k}{Q_k} = a_k+\dfrac{Q_{k+1}P_{k+1}}{P_{k+1}^2-D},\ \dfrac{1}{Q_k}=-\dfrac{Q_{k+1}}{P_{k+1}^2-D}.
    $$
    
    Substituting the second equation into the first, we can solve for $P_{k+1}$:
    
    $$
    \dfrac{P_k}{Q_k} = a_k-\dfrac{P_{k+1}}{Q_k} \iff P_{k+1} = a_kQ_k-P_k.
    $$
    
    Substituting back into the second equation, we can solve for $Q_{k+1}$:
    
    $$
    Q_{k+1} = \dfrac{D-P_{k+1}^2}{Q_k} = \dfrac{D-(a_kQ_k-P_k)^2}{Q_k} = -a_k^2Q_k+2a_kP_k+\dfrac{D-P_k^2}{Q_k}.
    $$
    
    By the induction hypothesis, $Q_k\mid D-P_k^2$, so $P_{k+1}$ and $Q_{k+1}$ are indeed integers; that is, $r_{k+1}$ also has the required form.
    
    Finally, we show that the remainders can take only finitely many values, so they must repeat. We found the remainder above:
    
    $$
    \dfrac{P_k+\sqrt{D}}{Q_k} = r_k = -\dfrac{q_{k-2}x-p_{k-2}}{q_{k-1}x-p_{k-1}}
    $$
    
    and for an irrational number, we always have $r_k>1$. Meanwhile, its conjugate
    
    $$
    \dfrac{P_k-\sqrt{D}}{Q_k} = r_k^* = -\dfrac{q_{k-2}x^*-p_{k-2}}{q_{k-1}x^*-p_{k-1}} = -\dfrac{q_{k-2}}{q_{k-1}}\dfrac{x^*-\dfrac{p_{k-2}}{q_{k-2}}}{x^*-\dfrac{p_{k-1}}{q_{k-1}}}
    $$
    
    must be less than $0$ for large enough $k$, because
    
    $$
    \dfrac{q_{k-2}}{q_{k-1}}>0,\ \lim_{k\rightarrow\infty}\dfrac{x^*-\dfrac{p_{k-2}}{q_{k-2}}}{x^*-\dfrac{p_{k-1}}{q_{k-1}}}=\dfrac{x^*-x}{x^*-x}=1.
    $$
    
    This shows
    
    $$
    \dfrac{2\sqrt{D}}{Q_k} = r_k-r_k^*>1 \iff 0<Q_k\le 2\sqrt{D}.
    $$
    
    So $Q_k$ can take only finitely many values. Furthermore,
    
    $$
    D-P_{k}^2=Q_kQ_{k-1}>0 \iff |P_k|<\sqrt{D},
    $$
    
    so $P_k$ can also take only finitely many values. Hence the remainder $r_k$ has only finitely many possible values, and must repeat among infinitely many terms.

The proof of the theorem also gives a recurrence for computing the remainders of a quadratic irrational:

???+ note "Recurrence for the remainders of a quadratic irrational"
    A quadratic irrational can always be written in the form
    
    $$
    x=\dfrac{P_0+\sqrt{D}}{Q_0}
    $$
    
    with $Q_0\mid D-P^2_0$. In its remainders
    
    $$
    r_{k}=\dfrac{P_k+\sqrt{D}}{Q_k}
    $$
    
    $P_k,Q_k$ are integers and satisfy the recurrence
    
    $$
    \begin{aligned}
    P_{k+1} &= a_kQ_k-P_k,\\
    Q_{k+1} &= \dfrac{D-P_{k+1}^2}{Q_k}.
    \end{aligned}
    $$

This recurrence can be used directly to compute the continued fraction of a quadratic irrational, and by the proof of the theorem, $|P_k|<\sqrt{D}$ and $Q_k\le 2\sqrt{D}$. The complexity of this algorithm depends on the length of the period, which can be shown to be $O(\sqrt{D}\log D)$[^period-surd].

???+ example "Quadratic irrational"
    Given a quadratic irrational $\alpha=\dfrac{x+y\sqrt{n}}{z}$, find its continued fraction representation. Here $x,y,z,n\in\mathbf Z$, and $n>0$ is not a perfect square.

??? note "Solution"
    First write the quadratic irrational in the form above, then compute with the recurrence. The terms of the continued fraction are given by $a_k=\lfloor r_k\rfloor$. To find the repeating block, store the index where each $(P_k,Q_k)$ first appears.
    
    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/quadratic-irrational.cpp:core"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/quadratic-irrational.py:core"
        ```

???+ example "[Tavrida NU Akai Contest - Continued Fraction](https://timus.online/problem.aspx?space=1&num=1814)"
    Given $x$ and $k$, where $x$ is not a perfect square and $0\le k\le 10^9$, find the $k$-th convergent $x_k$ of $\sqrt{x}$.

??? note "Solution"
    First use the algorithm above to find the period of $\sqrt{x}$. Express the repeating block as a fractional linear transformation; then [binary exponentiation](../binary-exponentiation.md) gives the value of $x_k$. Of course, the part before the period starts and the part that is shorter than a full period need to be handled separately.
    
    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/surd-convergent.cpp"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/surd-convergent.py"
        ```

### Purely periodic continued fractions

Being a quadratic irrational is a necessary and sufficient condition for a real number to have a periodic continued fraction representation. This section gives a necessary and sufficient condition for a real number to have a purely periodic continued fraction representation.

First, since a purely periodic continued fraction looks like a finite continued fraction, we can "reverse" it. As with the reversal theorem, the continued fraction obtained this way has a definite relationship with the original one.

???+ note "Theorem (Galois)"
    For a purely periodic continued fraction
    
    $$
    x = \left[\overline{a_0,a_1,\ldots,a_{\ell}}\right],
    $$
    
    let
    
    $$
    x' = \left[\overline{a_{\ell},\ldots,a_1,a_0}\right].
    $$
    
    Then $x$ and $x'$ are "negative reciprocal conjugates" of each other; that is, the negative of the reciprocal of the conjugate of $x$ is $x'$.

??? note "Proof"
    Since $\ell+1$ is not required to be the minimal period, we may assume $\ell>0$. By the reversal theorem,
    
    $$
    \begin{aligned}
    \dfrac{p_\ell}{p_{\ell-1}} &= [a_\ell,\ldots,a_1,a_0] = \dfrac{p'_\ell}{q'_\ell},\\
    \dfrac{q_\ell}{q_{\ell-1}} &= [a_\ell,\ldots,a_1] = \dfrac{p'_{\ell-1}}{q'_{\ell-1}}.
    \end{aligned}
    $$
    
    Since both sides of each equation are reduced fractions,
    
    $$
    p'_\ell = p_\ell,\ q'_\ell = p_{\ell-1},\ p'_{\ell-1}=q_\ell,\ q'_{\ell-1} = q_{\ell-1}.
    $$
    
    For a purely periodic continued fraction $x$, its $(\ell+1)$-th remainder is $x$ itself, so
    
    $$
    x = \dfrac{xp_\ell+p_{\ell-1}}{xq_\ell+q_{\ell-1}}.
    $$
    
    So it satisfies the quadratic equation
    
    $$
    q_\ell x^2+(q_{\ell-1}-p_\ell)x-p_{\ell-1} = 0.
    $$
    
    Similarly, $x'$ satisfies the quadratic equation
    
    $$
    q'_\ell(x')^2+(q'_{\ell-1}-p'_\ell)x'-p'_{\ell-1} = 0.
    $$
    
    Using the relations between the coefficients, this equation can be written as
    
    $$
    p_{\ell-1}(x')^2+(q_{\ell-1}-p_\ell)x'-q_\ell = 0.
    $$
    
    Let $y=-\dfrac{1}{x'}$. Then $x$ and $y$ satisfy the same equation. But $x>0>y$, so they are not the same root; they are conjugates of each other. This proves the statement.

Using this observation, Galois went further and gave a necessary and sufficient condition for a quadratic irrational to have a purely periodic continued fraction representation.

???+ note "Theorem (Galois)"
    A quadratic irrational $x$ can be written as a purely periodic continued fraction if and only if $x>1$ and its conjugate satisfies $-1<x^*<0$.

??? note "Proof"
    If $x$ is a purely periodic continued fraction, then with the notation above, $a_0=a_{\ell+1}\ge 1$, so $x>1$. And since its negative reciprocal conjugate is also a periodic continued fraction, its conjugate $x^*$ satisfies $-\dfrac{1}{x^*}>1$, that is, $-1<x^*<0$. This proves that every purely periodic continued fraction satisfies the condition.
    
    Conversely, let the quadratic irrational $x>1$ with $-1<x^*<0$. The remainders $r_k$ of $x$ satisfy the recurrence
    
    $$
    r_k = a_k+\dfrac{1}{r_{k+1}}.
    $$
    
    Both sides are quadratic irrationals, so taking conjugates gives
    
    $$
    r_{k}^* = a_k+\dfrac{1}{r_{k+1}^*}.
    $$
    
    Using this recurrence, we can show that $-1<r_{k}^*<0$ holds for all $k\ge 0$.
    
    First, for $k=0$, $-1<r_0^*=x^*<0$ is clear. For $k\ge 0$, the definition of a simple continued fraction and $x>1$ give $a_k\ge 1$. So, assuming $-1<r_k^*<0$, we have
    
    $$
    -1<-\dfrac{1}{a_k}< r_{k+1}^* = \dfrac{1}{r_k^*-a_k} < -\dfrac{1}{1+a_k} < 0.
    $$
    
    This proves by induction that $-1<r_{k}^*<0$ for all $k\ge 0$. Therefore,
    
    $$
    a_k = -\dfrac{1}{r_{k+1}^*}+r_k^* = \left\lfloor-\dfrac{1}{r_{k+1}^*}\right\rfloor.
    $$
    
    Since a quadratic irrational is always a periodic continued fraction, there is a positive integer $L$ such that $r_{k}=r_{k+L}$ for at least some large enough $k$. But then we must also have
    
    $$
    a_{k-1} = \left\lfloor-\dfrac{1}{r_{k}^*}\right\rfloor = \left\lfloor-\dfrac{1}{r_{k+L}^*}\right\rfloor = a_{k+L-1}.
    $$
    
    So
    
    $$
    r_{k-1} = a_{k-1}+\dfrac{1}{r_k} = a_{k+L-1}+\dfrac{1}{r_{k+L}} = r_{k+L-1}.
    $$
    
    This means the smallest $k$ with $r_{k}=r_{k+L}$ must be $0$. That is, $x$ can be written as a purely periodic continued fraction.

Galois's theorem reveals the pattern in the continued fraction representations of pure quadratic surds, that is, quadratic irrationals of the form $\sqrt{r}$.

???+ note "Corollary"
    For a rational number $r>1$, if $\sqrt{r}$ is irrational, then
    
    $$
    \sqrt{r} = [\lfloor\sqrt{r}\rfloor,\overline{a_1,\ldots,a_{\ell},2\lfloor\sqrt{r}\rfloor}]
    $$
    
    and $a_k = a_{\ell+1-k}$ for every $1\le k\le\ell$.

??? note "Proof"
    For the quadratic irrational $\sqrt{r}$, since $\lfloor\sqrt{r}\rfloor+\sqrt{r}>1$ and $-1<\lfloor\sqrt{r}\rfloor-\sqrt{r}<0$, $\lfloor\sqrt{r}\rfloor+\sqrt{r}$ is a purely periodic continued fraction:
    
    $$
    \lfloor\sqrt{r}\rfloor+\sqrt{r} = [\overline{2\lfloor\sqrt{r}\rfloor,a_1,\ldots,a_\ell}].
    $$
    
    By the theorem above, its negative reciprocal conjugate has the form
    
    $$
    \dfrac{1}{\sqrt{r}-\lfloor\sqrt{r}\rfloor} = [\overline{a_\ell,\ldots,a_1,2\lfloor\sqrt{r}\rfloor}].
    $$
    
    By the basic properties of continued fractions,
    
    $$
    \sqrt{r}=\lfloor\sqrt{r}\rfloor+\dfrac{1}{\dfrac{1}{\sqrt{r}-\lfloor\sqrt{r}\rfloor}}=[\lfloor\sqrt{r}\rfloor,\overline{a_\ell,\ldots,a_1,2\lfloor\sqrt{r}\rfloor}].
    $$
    
    But from the continued fraction representation of $\lfloor\sqrt{r}\rfloor+\sqrt{r}$, we also have
    
    $$
    \sqrt{r} = -\lfloor\sqrt{r}\rfloor+\left(\lfloor\sqrt{r}\rfloor+\sqrt{r}\right) = [\lfloor\sqrt{r}\rfloor,\overline{a_1,\ldots,a_\ell,2\lfloor\sqrt{r}\rfloor}].
    $$
    
    Since the continued fraction representation of an irrational number is unique, comparing the middle coefficients shows that $a_k=a_{\ell+1-k}$ for all $1\le k\le\ell$.

??? example "Example: continued fraction expansion of $\sqrt{74}$"
    The continued fraction of $\sqrt{74}$ can be computed as follows (this is only for illustration; a program should use the recursive algorithm described above):
    
    $$
    \begin{aligned}
    \sqrt{74}&=8+(-8)+\sqrt{74}=\left[8,\frac{8+\sqrt{74}}{10}\right]\\
    &=\left[8,1+\frac{-2+\sqrt{74}}{10}\right]=\left[8,1,\frac{2+\sqrt{74}}{7}\right]\\
    &=\left[8,1,1+\frac{-5+\sqrt{74}}{7}\right]=\left[8,1,1,\frac{5+\sqrt{74}}{7}\right]\\
    &=\left[8,1,1,1+\frac{-2+\sqrt{74}}{7}\right]=\left[8,1,1,1,\frac{2+\sqrt{74}}{10}\right]\\
    &=\left[8,1,1,1,1+\frac{-8+\sqrt{74}}{10}\right]=\left[8,1,1,1,1,8+\sqrt{74}\right]\\
    &=\left[8,1,1,1,1,16+(-8)+\sqrt{74}\right]=\left[8,\overline{1,1,1,1,16}\right]
    \end{aligned}
    $$
    
    The remainders are:
    
    $$
    \begin{alignedat}{3}
    r_1&=\frac{8+\sqrt{74}}{10}&&=\left[\overline{1,1,1,1,16}\right]\\
    r_2&=\frac{2+\sqrt{74}}{7}&&=\left[\overline{1,1,1,16,1}\right]\\
    r_3&=\frac{5+\sqrt{74}}{7}&&=\left[\overline{1,1,16,1,1}\right]\\
    r_4&=\frac{2+\sqrt{74}}{10}&&=\left[\overline{1,16,1,1,1}\right]\\
    r_5&=8+\sqrt{74}&&=\left[\overline{16,1,1,1,1}\right]
    \end{alignedat}
    $$
    
    By Galois's result, the periodic parts of the remainders $r_k$ and $r_{L+1-k}$ are exact reverses of each other, so they are negative reciprocal conjugates of each other. If the period length $L$ of $\sqrt{D}$ is odd, the middle term is its own negative reciprocal conjugate; if the period length $L$ is even, there is no such term. The discussion in the section on Pell's equation will show that the parity of the period length determines whether the equation $x^2-Dy^2=-1$ has a solution.

The continued fraction expansion of the quadratic irrational $\sqrt{D}$ is mainly used for solving [Pell's equation](./pell-equation.md).

## Example problems

After learning the basic concepts, let's study some concrete example problems to see how continued fraction methods are used in competitive programming.

???+ example "Convex hull under a line"
    Given $r=[a_0,a_1,\ldots,a_n]$, find the convex hull of the set of lattice points $(x,y)$ with $0\le x\le N$ and $0\le y\le rx$.

??? note "Solution"
    For the unbounded set $x\ge 0$, the upper hull is just the line $y=rx$ itself. However, as the figure below shows, if we also require $x\le N$, the upper hull eventually moves away from the line.
    
    ![](./images/lattice-hull.svg)
    
    Starting from $(0,0)$, we can find all lattice points of the upper hull from left to right. Suppose the last lattice point of the upper hull found so far is $(x,y)$. Now we want the next lattice point $(x',y')$. The vertex $(x',y')$ is above and to the right of $(x,y)$; let $(\Delta x,\Delta y)=(x'-x,y'-y)$ be their difference. Then we must have
    
    $$
    0<\Delta x\le N-x,\ 0\le \Delta y\le r\Delta x.
    $$
    
    The second inequality holds because the condition $\Delta y>r\Delta x$ would contradict the fact that $(x,y)$ is already on the upper hull. Looking at the conditions $(\Delta x,\Delta y)$ must satisfy, only the upper bound on $\Delta x$ changes for different points $(x,y)$. So if we can solve this subproblem, we can recursively find all the lattice points of the original problem.
    
    Next, consider how to solve the subproblem. Compared with the original problem, the subproblem changes the upper bound on $x$ to $N'$ and asks for the first lattice point of the upper hull next to the origin. Let the solution of the subproblem be $(q,p)$. Then $p$ and $q$ must be coprime (otherwise it would not be the first lattice point), and the slope $\dfrac{p}{q}$ of the line to the origin is the largest among all lattice points below the line $y=rx$ with $x$-coordinate at most $N'$ (otherwise it would not be on the convex hull). From the [geometric interpretation](#geometric-interpretation) above, such a point $(x,y)$ must correspond to a lower semiconvergent of $r$. Since lower semiconvergents with larger denominators are closer to $r$, the solution $(q,p)$ of the subproblem corresponds to the lower semiconvergent with the largest denominator among all those with denominator at most $N'$.
    
    Of course, in practice there is no need to recompute such a lower semiconvergent for every subproblem. We should first compute all convergents, which gives us a way to go through all lower semiconvergents. Then go through the lower semiconvergents from the largest denominator to the smallest, each time trying to add it to the previous lattice point $(x,y)$, and move on to the next lower semiconvergent only when it can no longer be added.
    
    There are some obvious optimizations here. First, for a lower semiconvergent $(q,p)$, there must be an odd $k$ and $0\le t<a_{k+1}$ such that $(q,p)=(q_{k-1},p_{k-1})+t(q_k,p_k)$. We just need to find the largest $t$ with $q_{k-1}+tq_k+x\le N$, that is, $t=\left\lfloor\dfrac{N-q_{k-1}-x}{q_k}\right\rfloor$. We don't need to worry about $t$ going out of range, because the larger lower convergent $(q_{k+1},p_{k+1})$ has already been fully added. And to determine how many times to add each time, just compute $\left\lfloor\dfrac{N-x}{q}\right\rfloor$ directly instead of trying one at a time.
    
    The optimized algorithm runs in $O(n)$ time. Although there may be many lattice points corresponding to lower semiconvergents, few of them actually become increments. We now show that among all lower semiconvergents $(q,p)=(q_{k-1},p_{k-1})+t(q_k,p_k)$ with $0\le t<a_{k+1}$, at most two increments appear. Suppose an increment does appear among these lower semiconvergents; then we must have $q_{k-1}\le N-x<q_{k+1}$. Let $t=\left\lfloor\dfrac{N-q_{k-1}-x}{q_k}\right\rfloor$. If $t=0$, the increment has $\Delta x=q_{k-1}$, so after adding it, $N-x'<q_{k-1}$, and no new increment will appear among these lower semiconvergents; if $t>0$, then after adding the increment, $N-x'=(N-q_{k-1}-x)\bmod q_k<q_k$, so even if another increment appears in the same group of lower semiconvergents, it must have $t'=0$. So at most two increments appear in each such group of lower semiconvergents. This shows that the total time complexity is $O(n)$.
    
    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/hull-under-line.cpp:core"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/hull-under-line.py:core"
        ```

???+ example "[Timus - Crime and Punishment](https://timus.online/problem.aspx?space=1&num=1430)"
    Given positive integers $A,B,N \le 2\times 10^9$, find $x,y\ge 0$ such that $Ax+By\le N$ and $Ax+By$ is as large as possible.

??? note "Solution"
    This problem has an $O(\sqrt N)$ solution: assume $A\ge B$. Since $A(B+x)+By=Ax+B(A+y)$, we only need to search for the answer among $x\le\min\{N/A, B\}$. This is enough to pass the problem. But with continued fractions, the time complexity drops to $O(\log N)$.
    
    For convenience, first flip the sign of $x$ with the substitution $x\mapsto\left\lfloor N/A\right\rfloor-x$. Let $C=N\bmod A$ and $M=\left\lfloor N/A\right\rfloor$. Then the problem becomes: under the conditions $0\le x\le M$ and $By-Ax\le C$, find the optimal $(x,y)$ that maximizes $By-Ax$. For each fixed $x$, the optimal value of $y$ is $\left\lfloor\dfrac{Ax+C}{B}\right\rfloor$.
    
    Next we show that this problem has a solution similar to the previous example. But unlike the previous example, where lower semiconvergents move away from the line, here we need upper semiconvergents to move toward the line. Specifically, the value $C-(By-Ax)$ is proportional to the distance from the point $(x,y)$ to the line $By-Ax=C$. Maximizing $By-Ax$ is equivalent to minimizing this distance. The goal of the algorithm is to find the feasible lattice point below the line $By-Ax=C$ that is closest to it. The idea is to start from the leftmost point and search along the upper hull of these lattice points, reducing the distance to the line step by step, until we get the optimal solution.
    
    In the $(x,y)$ coordinate system, the algorithm starts from $(0,\lfloor C/B\rfloor)$ and recursively finds and adds the best increment $(\Delta x,\Delta y)$, making sure that the new point is closer to the line $By-Ax=C$ than before, but does not reach the other side of the line and does not have an $x$-coordinate larger than $M$. Let the current point be $(x,y)$. Then the increment $(\Delta x,\Delta y)$ must satisfy
    
    $$
    0<B\Delta y-A\Delta x\le C-(By-Ax),\ 0<\Delta x\le M-x.
    $$
    
    Following the idea of searching along the lower hull, we just need to find the point with the smallest $\Delta x$ among those satisfying these conditions. Rewrite the first inequality as
    
    $$
    \Delta y \le \dfrac{A}{B}\Delta x+\dfrac{C-(By-Ax)}{B}.
    $$
    
    From the [geometric interpretation](#geometric-interpretation) above, as long as the constant term at the end is less than $1$, the lattice point $(\Delta x,\Delta y)$ with the smallest $x$-coordinate satisfying this inequality must correspond to some upper semiconvergent. This is because, among all fractions whose denominators do not exceed its denominator, it approximates a certain real number from above the best, and only an upper semiconvergent can do that. And each added increment makes the upper bound on $\Delta y$ tighter, which means we must look at upper semiconvergents with larger denominators.
    
    Follow the idea of the previous example. Go through all upper semiconvergents from the smallest denominator to the largest. If we find an upper semiconvergent where neither the $x$- nor the $y$-coordinate goes out of bounds, add it and update the corresponding bounds. When all feasible upper semiconvergents have been added, we have the optimal solution. Compared with before, this problem must keep both coordinates in bounds at the same time, which needs extra care. With an argument similar to the previous example, but using $B\Delta y-A\Delta x$ in place of $\Delta x$, we can show that this algorithm runs in $O(\log\min\{A,B\})$ time.
    
    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/closest-dio.cpp:core"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/closest-dio.py:core"
        ```

???+ example "[June Challenge 2017 - Euler Sum](https://www.codechef.com/problems/ES)"
    Compute $\sum\limits_{x=1}^N \lfloor \mathrm{e}x \rfloor$, where $\mathrm{e}$ is the base of the natural logarithm.
    
    Hint: $\mathrm{e} = [2,1,2,1,1,4,1,1,6,1,\ldots,1,2n,1, \ldots]$.[^continued-fraction-of-e]

??? note "Solution"
    This sum equals the number of lattice points in the set $\{(x,y):1\le x\le N,1\le y\le\mathrm{e}x\}$. After building the convex hull of the lattice points under the line $y=\mathrm{e}x$, we can count the lattice points with [Pick's theorem](../../geometry/pick.md). The time complexity is $O(\log N)$.
    
    The original problem has $N \le 10^{4000}$. The C++ code here is only for illustration and does not implement a big integer class.
    
    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/sum-floor.cpp:core"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/sum-floor.py:core"
        ```

???+ example "[NAIPC 2019 - It's a Mod, Mod, Mod, Mod World](https://open.kattis.com/problems/itsamodmodmodmodworld)"
    Given positive integers $p,q,n$, compute $\sum\limits_{i=1}^n [pi \bmod q]$.

??? note "Solution"
    Since the sum can be rewritten as
    
    $$
    \sum_{i=1}^n [pi \bmod q] 
    =\sum_{i=1}^n\left(pi - q\left\lfloor\dfrac{pi}{q}\right\rfloor\right) = \dfrac{pn(n+1)}{2} - q\sum_{i=1}^n\left\lfloor\dfrac{p}{q}i\right\rfloor,
    $$
    
    this problem reduces to the previous one, just with $\dfrac{p}{q}$ in place of $\mathrm{e}$. Each query takes $O(\log\min\{p,q\})$ time.
    
    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/mod-mod-mod.cpp:core"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/mod-mod-mod.py:core"
        ```

???+ example "[Library Checker - Sum of Floor of Linear](https://judge.yosupo.jp/problem/sum_of_floor_of_linear)"
    Given positive integers $N,M,A,B$, compute $\displaystyle\sum_{i=0}^{N-1} \left\lfloor \dfrac{A \cdot i + B}{M} \right\rfloor$.

??? note "Solution"
    This is the most complex problem so far. It can be solved with the [Euclidean-like algorithm](./euclidean.md). Here we give an algorithm based on continued fractions, with time complexity $O(\log\min\{A,M\})$.
    
    We can build the convex hull of all lattice points under the line $y=\dfrac{Ax+B}{M}$ with $0\le x< N$, and count the lattice points with Pick's theorem. We already solved the case $B=0$. The general case can be done in two steps. First, add upper semiconvergents to move closer and closer to the line (as in the second example) until we find the point closest to the line; then add lower semiconvergents to move away from the line step by step (as in the first example).
    
    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/sum-floor-axbc.cpp:core"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/sum-floor-axbc.py:core"
        ```

???+ example "[OKC 2 - From Modular to Rational](https://codeforces.com/gym/102354/problem/I)"
    There is an unknown rational number $\dfrac{p}{q}$ with $1\le p, q\le 10^9$. You may ask for the value of $pq^{-1}$ modulo some prime $m\in[10^9,10^{12}]$. Determine $p$ and $q$ using at most ten queries.
    
    This problem is equivalent to finding the $x$ in $[1,n]$ that minimizes $rx\bmod m$, where $r$ is $pq^{-1}$ modulo $m$ and $n=10^9$.

??? note "Solution"
    By the [Chinese remainder theorem](./crt.md), asking for the results modulo several primes is equivalent to asking for the result modulo the product of these primes. So this problem can be seen as asking for the value of the fraction modulo a large enough modulus $m$, and then determining the numerator and denominator of the fraction.
    
    For a given modulus $m$, the pair $(p,q)$ with $qr\equiv p\pmod m$ may not be unique. Suppose both $(p_1,q_1)$ and $(p_2,q_2)$ satisfy this congruence. Then we must have $(p_1q_2-p_2q_1)r\equiv 0\pmod m$. By the construction of $r$, $r$ is coprime to $m$, so $p_1q_2-p_2q_1\equiv 0\pmod m$, that is, $m\mid(p_1q_2-p_2q_1)$. If $p_1q_2-p_2q_1$ is non-zero, its absolute value is at least $m$. The problem restricts $p,q\in[1,10^9]$, so this difference cannot exceed $10^{18}$. So just taking $m>10^{18}$ guarantees that the $(p,q)$ we find is unique.
    
    Now the problem comes down to: given the modulus $m$ and the remainder $r$, find a pair of positive integers $(p,q)$, each at most $n$, such that $qr\equiv p\pmod m$. Knowing that such a solution is unique, we only need to find the $q\in[1,n]$ that minimizes $qr\bmod m$, because exactly one $q$ makes the remainder at most $n$. This is exactly the equivalent statement mentioned above.
    
    In the plane with coordinates $(q,k)$, this means finding, for $q\in[1,n]$, the lattice point below the line $qr-km=0$ that is closest to it, because the remainder $qr\bmod m$ is proportional to the distance from the lattice point to the line. From the [geometric interpretation](#geometric-interpretation) above, such a lattice point must correspond to some lower semiconvergent of the rational number $\dfrac{r}{m}$. The algorithm runs in $O(\log\min\{r,m\})$ time.
    
    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/recover-fraction.cpp:core"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/recover-fraction.py:core"
        ```

## Exercises

-   [UVa OJ - Continued Fractions](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=775)
-   [ProjectEuler+ #64: Odd period square roots](https://www.hackerrank.com/contests/projecteuler/challenges/euler064/problem)
-   [LibreOJ NOI Round #2 Single-Handed](https://loj.ac/p/573)
-   [Codeforces Round #184 (Div. 2) - Continued Fractions](https://codeforces.com/contest/305/problem/B)
-   [Codeforces Round #201 (Div. 1) - Doodle Jump](https://codeforces.com/contest/346/problem/E)
-   [Codeforces Round #325 (Div. 1) - Alice, Bob, Oranges and Apples](https://codeforces.com/contest/585/problem/C)
-   [POJ Founder Monthly Contest 2008.03.16 - A Modular Arithmetic Challenge](http://poj.org/problem?id=3530)
-   [2019 Multi-University Training Contest 5 - fraction](http://acm.hdu.edu.cn/showproblem.php?pid=6624)
-   [SnackDown 2019 Elimination Round - Election Bait](https://www.codechef.com/SNCKEL19/problems/EBAIT)
-   [Luogu P5179. Fraction](https://www.luogu.com.cn/problem/P5179)
-   [Luogu P7739. \[NOI2021\] Password Box](https://www.luogu.com.cn/problem/P7739)

## References and further reading

-   Hardy, G. H., Wright, E. M., Heath-Brown, R., & Silverman, J. (2008). An Introduction to the Theory of Numbers. Oxford Mathematics.
-   Zhu Yaochen and Wang Lianxiang, *An Introduction to Diophantine Approximation* (in Chinese)
-   [FatFish's blog - An introduction to continued fractions (in Chinese)](https://chaoli.club/index.php/2756)
-   [Simple continued fraction - Wikipedia](https://en.wikipedia.org/wiki/Simple_continued_fraction)
-   [Periodic continued fraction - Wikipedia](https://en.wikipedia.org/wiki/Periodic_continued_fraction)
-   [Gosper's original notes on continued fraction arithmetic algorithms](https://perl.plover.com/yak/cftalk/INFO/gosper.txt)
-   [Understanding Bill Gosper's continued fraction arithmetic (implemented in Python)](https://hsinhaoyu.github.io/cont_frac/)

**Most of this page is translated from the blog post [Continued fractions](https://cp-algorithms.com/algebra/continued-fractions.html), licensed under CC-BY-SA 4.0, with modifications.**

[^one-representation]: The natural number $1$ has only a non-canonical representation: $1=[1]=[0,1]$.

[^continuant]: The Chinese name of this term follows Section 6.7 of the Chinese translation of *Concrete Mathematics* by Zhang Mingyao and Zhang Fan.

[^heilbronn]: [H. Heilbronn, On the Average Length of a Class of Finite Continued Fractions, 1969.](https://link.springer.com/chapter/10.1007/978-1-4615-4819-5_7)

[^sqrt5]: Here we cannot assume that the reduced fraction $\dfrac{p}{q}$ is a convergent, although Legendre's theorem shows that $\dfrac{p}{q}$ can indeed only be some convergent. For the case of convergents, the proof can start from the error of approximating a real number by its convergents.

[^semi-range]: Different references may differ on whether the range of $t$ here includes the endpoints.

[^semiconvergent]: When $t=0$, this should be understood as a formal continued fraction, which amounts to cutting the continued fraction off at the second-to-last term.

[^nose-stretching]: This name is not a standard technical term. It may be translated from the Russian book [ЦЕПНЫЕ ДРОБИ](https://old.mccme.ru/free-books/mmmf-lectures/book.14-full.pdf), in the section Алгоритм «вытягивания носов».

[^pgl2]: These properties show that the group of all fractional linear transformations is isomorphic to the [projective linear group](https://en.wikipedia.org/wiki/Projective_linear_group)  $PGL_2(\mathbf R)$.

[^period-surd]: For a proof, see the references on the [Wikipedia page](https://en.wikipedia.org/wiki/Periodic_continued_fraction#Length_of_the_repeating_block).

[^continued-fraction-of-e]: For a proof of the continued fraction expansion of the base of the natural logarithm $\mathrm{e}$, see [here](https://proofwiki.org/wiki/Continued_Fraction_Expansion_of_Euler%27s_Number).
