This article introduces numerical characteristics of random variables such as the expected value and the variance.

## Expected value

### Definition

#### Discrete random variables

Let the discrete random variable $X$ have probability distribution $p_i = P\{ X = x_i \}$. If the sum

$$
\sum x_i p_i
$$

converges absolutely, its value is called the **expected value** of $X$, written $EX$.

#### Continuous random variables

Let the continuous random variable $X$ have density function $f(x)$. If the integral

$$
\int_{\mathbb{R}} xf(x) \text{d} x
$$

converges absolutely, its value is called the **expected value** of $X$, written $EX$.

#### Unified definition

Let the random variable $X$ have distribution function $F(x)$. If the [Stieltjes integral](https://en.wikipedia.org/wiki/Riemann%E2%80%93Stieltjes_integral)

$$
\int_{\mathbb{R}} x \text{d} F(x)
$$

converges absolutely, its value is called the **expected value** of $X$, written $EX$.

??? example "Examples where the expected value does not exist"
    Consider a discrete random variable $X$ with the following distribution
    
    $$
    P\left\{ X = (-1)^k \frac{2^k}{k} \right\} = \frac{1}{2^k}, \quad k = 1, 2, \cdots
    $$
    
    Although the sum $\sum x_i p_i$ converges to $- \ln 2$, it does not converge absolutely, so the expected value of $X$ does not exist.
    
    Now consider a continuous random variable $Y$ with the following density function
    
    $$
    f(y) = \frac{1}{\pi} \cdot \frac{1}{1 + y^2}, \quad y \in (-\infty, +\infty)
    $$
    
    It is easy to check that the expected value of $Y$ does not exist either.

### Properties of the expected value

#### Linearity

If the expected values of random variables $X, Y$ exist, then

-   for any real numbers $a, b$, $E(aX + b) = a \cdot EX + b$.
-   $E(X + Y) = EX + EY$.

#### Expected value of a product of random variables

If the expected values of random variables $X$, $Y$ exist and $X$, $Y$ are independent, then

$$
E(XY) = EX \cdot EY
$$

Note: independence in the property above is **not** a necessary condition.

??? example "Counterexample"
    Consider random variables $X$ and $Y$, where $X$ is uniformly distributed on $[-1, 1]$ and $Y = X^2$.

### Converting between expected value and probability

For a random event $A$, consider its indicator function $I_A$:

$$
I_A(\omega) = \begin{cases}
    1, & \omega \in A \\
    0, & \omega \notin A
\end{cases}
$$

From the definition, its expected value is $EI_A = P(A)$. This conversion is very common in practice.

??? example "Example"
    Suppose we have a sequence $\{ a_i \}$ of length $n$, where $a_k$ equals $k$ with probability $p_k$ and $0$ with probability $1 - p_k$. How do we find the expected value of $S = \sum_{i=1}^{n} a_i$?
    
    If we compute it directly from the definition, we need the probability of every possible value of $S$. This is fairly tedious, so we will not go into it here.
    
    On the other hand, let $I_k$ be the indicator function of the random event $a_k = k$. Then
    
    $$
    S = \sum_{k=1}^{n} k \cdot I_k
    $$
    
    and it is easy to get
    
    $$
    ES = E \left( \sum_{k=1}^{n} k \cdot I_k \right) = \sum_{k=1}^{n} k \cdot E[I_k] = \sum_{k=1}^{n} k \cdot p_k
    $$

## Conditional distribution and conditional expectation

We studied conditional probability earlier. In a similar way, we can introduce the concept of conditional expectation.

### Definition

For two random variables $X$, $Y$, the probability distribution (density function) of $X$ given $Y = y$ is called the **conditional probability distribution (conditional probability density)**, written respectively as

$$
P( X = x_i | Y = y ) \qquad f_{X|Y}(x|y)
$$

Under this condition, the expected value of $X$ is called the **conditional expectation**, written $E[X|Y=y]$.

### Properties of conditional expectation

Many properties of conditional expectation can be derived from conditional probability, so we will not repeat them here.

It is worth mentioning that $E[X | Y]$ is in general a function of the random variable $Y$, and this function is usually not linear. But in fact

$$
E[E[X|Y]] = EX
$$

This is called the **law of total expectation**.

### Application

???+ example "[HDU 5984 Pocky](https://acm.hdu.edu.cn/showproblem.php?pid=5984)"
    There is a Pocky stick of length $L$. Each time, it is broken into two pieces at a random point. If the right piece has length at most $d$, stop; otherwise repeat the process on the right piece. Find the expected number of repetitions.

??? note "Solution"
    Let $f(x)$ be the expected number of repetitions for length $x$. The case $x \leq d$ is trivial.
    
    When $x > d$, let the break point be at distance $k$ from the right end. Clearly $k \sim U[0, x]$, and the expected number of repetitions is then
    
    $$
    g(k) = \begin{cases}
        1, & k \leq d \\
        1 + f(k), & k > d
    \end{cases}
    $$
    
    By the law of total expectation,
    
    $$
    f(x) = Eg(k) = 1 + \frac{1}{x} \cdot \int_{d}^{x} f(t) \text{d} t
    $$
    
    Solving this integral equation and plugging in the initial condition gives
    
    $$
    f(x) = 1 + \ln \frac{x}{d}
    $$

## Variance

### Definition

Suppose the expected value $EX$ of a random variable $X$ exists and the expected value

$$
E(X - EX)^2
$$

also exists. Then its value is called the **variance** of the random variable $X$, written $DX$ or $Var(x)$. The arithmetic square root of the variance is called the **standard deviation**, written $\sigma(X) = \sqrt{DX}$.

### Properties of variance

If the variance of the random variable $X$ exists, then

-   for any constants $a, b$, $D(aX + b) = a^2 \cdot DX$
-   $DX = E(X^2) - (EX)^2$

## Covariance and correlation coefficient

In general, the equation $D(X + Y) = DX + DY$ does not hold. Two questions naturally come up:

-   What exactly is the difference between $D(X + Y)$ and $DX + DY$?
-   When are $D(X + Y)$ and $DX + DY$ equal?

To answer the first question, we introduce covariance.

### Definition of covariance

For random variables $X, Y$,

$$
E((X - EX)(Y - EY))
$$

is called the **covariance** of $X$ and $Y$, written $\operatorname{Cov}(X, Y)$.

### Properties of covariance

For random variables $X, Y, Z$,

-   $\operatorname{Cov}(X, Y) = \operatorname{Cov}(Y, X)$
-   for any constants $a, b$, $\operatorname{Cov}(aX + bY, Z) = a \cdot \operatorname{Cov}(X, Z) + b \cdot \operatorname{Cov}(Y, Z)$

Covariance is also related to variance as follows:

-   $DX = \operatorname{Cov}(X, X)$
-   $D(X + Y) = DX + 2 \operatorname{Cov}(X, Y) + DY$

??? note "About covariance"
    You may notice that the properties of covariance look very much like the properties of the inner product of vectors.
    
    From the point of view of functional analysis, for a given probability space, all random variables on it form a linear space. Covariance is an inner product on this space, and the standard deviation is the norm induced by this inner product.

For the second question above, it is easy to see that $D(X + Y) = DX + DY$ if and only if $\operatorname{Cov}(X, Y) = 0$. An intuitive sufficient condition is that $X$ and $Y$ are independent, because then

$$
\operatorname{Cov}(X, Y) = E((X - EX)(Y - EY)) = E(X - EX) E(Y - EY) = 0
$$

But this condition is not necessary. To describe the relationship between random variables $X$, $Y$ that satisfy $\operatorname{Cov}(X, Y) = 0$, we introduce the correlation coefficient.

### Correlation coefficient

For random variables $X, Y$,

$$
\frac{ \operatorname{Cov}(X, Y)}{ \sigma(X)\sigma(Y) }
$$

is called the **Pearson correlation coefficient** of $X$ and $Y$, written $\rho_{X,Y}$.

The Pearson correlation coefficient describes how strongly two random variables are linearly related. The larger $|\rho_{X,Y}|$ is, the stronger the linear relationship between $X$ and $Y$. It is not hard to prove that $|\rho_{X,Y}| \leq 1$, and $|\rho_{X,Y}| = 1$ can only happen in the following two cases

-   when there are a real number $a$ and a positive real number $b$ such that $P(X = a + bY) = 1$, we have $\rho_{X,Y} = 1$;
-   when there are a real number $a$ and a negative real number $b$ such that $P(X = a + bY) = 1$, we have $\rho_{X,Y} = -1$.

When $\rho_{X,Y} = 0$, we say the random variables $X$ and $Y$ are **uncorrelated**; in this case there is no linear relationship between $X$ and $Y$.

??? note "Uncorrelated vs. independent"
    Two random variables being uncorrelated only means there is no linear relationship between them. It does not mean there is no other kind of relationship.
    
    So two random variables $X, Y$ being uncorrelated is a **necessary but not sufficient** condition for them to be independent.

For the second question raised at the start of this subsection, here is the conclusion: $\operatorname{Cov}(X, Y) = 0$ if and only if one of $X$, $Y$ is constant with probability $1$, or $X, Y$ are uncorrelated.
