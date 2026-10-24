Prerequisites: [Factorials modulo a number](./factorial.md)

## Introduction

This article discusses computing large binomial coefficients modulo a number. A binomial coefficient is the expression:

$$
\binom{n}{k} = \dfrac{n!}{k!(n-k)!}.
$$

When the input is small, binomial coefficients can be computed with the [recurrence](../combinatorics/combination.md#properties-of-binomial-coefficients--corollaries-of-the-binomial-theorem) in $O(nk)$ time; or, under a large prime modulus $p>n$, by computing the factorials in the numerator and denominator in $O(n)$ time. But when the input is very large ($n\sim 10^{18}$), these methods no longer work.

Based on Lucas's theorem and its generalization, this article discusses a method that computes binomial coefficients when the modulus is not too large ($m \sim 10^6$). More precisely, the method works as long as the sum of all prime powers in the factorization $m=\prod p_i^{e_i}$ (i.e., $\sum p_i^{e_i}$) is on the order of $10^6$, since the algorithm's preprocessing is roughly of that size.

## Lucas's theorem

First, consider the case where the modulus is a prime $p$. Here we have Lucas's theorem:

???+ note "Lucas's theorem"
    For a prime $p$,
    
    $$
    \binom{n}{k}\equiv \binom{\lfloor n/p\rfloor}{\lfloor k/p\rfloor}\binom{n\bmod p}{k\bmod p}\pmod p.
    $$
    
    Here, when $n<k$, the binomial coefficient $\dbinom{n}{k}$ is defined to be $0$.

??? note "Proof with generating functions"
    Consider the value of $\displaystyle\binom{p}{n} \bmod p$. Since
    
    $$
    \binom{p}{n} = \frac{p!}{n!(p-n)!},
    $$
    
    when $n\neq 0,p$, the denominator has no factor $p$ but the numerator does, so the fraction must be a multiple of $p$ and its remainder modulo $p$ is $0$. When $n=0,p$, the fraction is just $1$. Therefore,
    
    $$
    \binom{p}{n} \equiv [n=0\lor n=p] \pmod p.
    $$
    
    Let $f(x) = ax^n + bx^m$. In general, by the [binomial expansion](../combinatorics/combination.md#binomial-theorem) and [Fermat's little theorem](./fermat.md#fermats-little-theorem),
    
    $$
    \begin{aligned}
    (f(x))^p 
    &= \left(ax^n + bx^m\right)^p \\
    &= \sum_{k=0}^p\binom{p}{k}(ax^n)^k(bx^m)^{p-k}\\
    &\equiv a^px^{pn} + b^px^{pm} \\
    &\equiv a(x^p)^n+b(x^p)^m\\
    &= f(x^p) \pmod p.
    \end{aligned}
    $$
    
    The congruence on the third line uses the result above: the binomial coefficient is not a multiple of $p$ only when $k=0,p$.
    
    Using this result, consider the binomial expansion:
    
    $$
    \begin{aligned}
    (1+x)^n &= (1+x)^{p\lfloor n/p\rfloor}(1+x)^{n\bmod p} \\
    &\equiv (1+x^p)^{\lfloor n/p\rfloor}(1+x)^{n\bmod p} \pmod p.
    \end{aligned}
    $$
    
    On the left-hand side, the coefficient of $x^k$ is
    
    $$
    \binom{n}{k}\bmod p.
    $$
    
    Now compute the coefficient of $x^k$ on the right-hand side. Every term in the first factor has degree a multiple of $p$, and every term in the second factor has degree less than $p$. There is exactly one way to split $k$ into such a sum, namely division with remainder: $k=p\lfloor k/p\rfloor +(k\bmod p)$. So the first factor can only contribute its term of degree $p\lfloor k/p\rfloor$, and the second factor can only contribute its term of degree $k\bmod p$. Therefore, the coefficient of $x^k$ on the right-hand side is the product of the coefficients contributed by the two factors:
    
    $$
    \binom{\lfloor n/p\rfloor}{\lfloor k/p\rfloor}\binom{n\bmod p}{k\bmod p}\bmod p.
    $$
    
    Setting the coefficients on both sides equal gives Lucas's theorem.

??? note "Proof using results on factorials modulo a number"
    Here is a proof based on results about [factorials modulo a number](./factorial.md#prime-modulus), which makes it easier to connect with the exLucas method later. Recall that the binomial coefficient is
    
    $$
    \binom{n}{k} = \dfrac{n!}{k!(n-k)!}.
    $$
    
    Separating the power of $p$ in the factorial $n!$ from its other factors gives the decomposition:
    
    $$
    n! = p^{\nu_p(n!)}(n!)_p.
    $$
    
    This gives an expression for the binomial coefficient:
    
    $$
    \binom{n}{k} = p^{\nu_p(n!)-\nu_p(k!)-\nu_p((n-k)!)}\dfrac{(n!)_p}{(k!)_p((n-k)!)_p}.
    $$
    
    Both the exponent $\nu_p(n!)$ and the factorial remainder $(n!)_p\bmod p$ satisfy recurrences:
    
    $$
    \begin{aligned}
    \nu_p(n!) &= \lfloor n/p\rfloor+\nu_p( \lfloor n/p\rfloor!),\\
    (n!)_p &\equiv (-1)^{\lfloor n/p\rfloor}\cdot (n\bmod p)!\cdot (\lfloor n/p\rfloor!)_p\pmod p.
    \end{aligned}
    $$
    
    The first is a corollary of Legendre's formula, and the second is a corollary of Wilson's theorem.
    
    Substituting the recurrences into the expression for the binomial coefficient and simplifying gives:
    
    $$
    \begin{aligned}
    \binom{n}{k} &\equiv (-p)^{\lfloor n/p\rfloor-\lfloor k/p\rfloor-\lfloor(n-k)/p\rfloor}\cdot\dfrac{(n\bmod p)!}{(k\bmod p)!((n-k)\bmod p)!} \\
    &\quad \cdot p^{\nu_p(\lfloor n/p\rfloor!)-\nu_p(\lfloor k/p\rfloor!)-\nu_p(\lfloor(n-k)/p\rfloor!)}\dfrac{(\lfloor n/p\rfloor!)_p}{(\lfloor k/p\rfloor!)_p(\lfloor(n-k)/p\rfloor!)_p} \pmod p.
    \end{aligned}
    $$
    
    Now look at the value of $\lfloor n/p\rfloor-\lfloor k/p\rfloor-\lfloor(n-k)/p\rfloor$. Since
    
    $$
    \begin{aligned}
    n &= \lfloor n/p\rfloor p + (n\bmod p),\\
    k &= \lfloor k/p\rfloor p + (k\bmod p),\\
    n-k &= \lfloor (n-k)/p\rfloor p + ((n-k)\bmod p),\\
    \end{aligned}
    $$
    
    subtracting the last two equations from the first gives
    
    $$
    (\lfloor n/p\rfloor-\lfloor k/p\rfloor-\lfloor(n-k)/p\rfloor)p = (k\bmod p)+((n-k)\bmod p)-(n\bmod p).
    $$
    
    On the right-hand side, the sum of the first two terms is strictly less than $2p$, and the third term $n\bmod p$ is exactly the remainder of that sum. So the right-hand side is non-negative and less than $2p$, and it must also be a multiple of $p$, so it can only be $0$ or $p$. This means $\lfloor n/p\rfloor-\lfloor k/p\rfloor-\lfloor(n-k)/p\rfloor$ can only be $0$ or $1$:
    
    -   If it is $0$, then $(n\bmod p) = (k\bmod p)+((n-k)\bmod p)$ also holds. So the exponent of the first factor above is $0$, and that factor equals one; the second factor is $\dbinom{n\bmod p}{k\bmod p}$; and by the expansion above (note that here $\lfloor(n-k)/p\rfloor=\lfloor n/p\rfloor-\lfloor k/p\rfloor$), the third factor equals $\dbinom{\lfloor n/p\rfloor}{\lfloor k/p\rfloor}$. So Lucas's theorem holds;
    -   If it is $1$, then the exponent of the first factor is $1$, so that factor equals zero, and the binomial coefficient has remainder zero. At the same time, the term $\dbinom{n\bmod p}{k\bmod p}$ on the right-hand side of Lucas's theorem must also be zero, because in this case we must have $(n\bmod p)<(k\bmod p)$; otherwise, we would have
    
        $$
        ((n-k)\bmod p) = p + (n\bmod p) - (k\bmod p) \ge p.
        $$
    
        This clearly contradicts the definition of a remainder.
    
    Combining the two cases proves Lucas's theorem. This proof shows that, for binomial coefficients modulo a prime, Lucas's theorem and the exLucas algorithm give equivalent results.

Lucas's theorem says that when the modulus is a prime $p$, computing a large binomial coefficient can be reduced to computing smaller ones. On the right-hand side, the first binomial coefficient can be handled recursively until $k=0$; the second can be computed directly or precomputed. In code:

???+ example "Sketch"
    ```cpp
    long long Lucas(long long n, long long k, long long p) {
      if (k == 0) return 1;
      return (C(n % p, k % p, p) * Lucas(n / p, k / p, p)) % p;
    }
    ```

Here `C(n, k, p)` computes small binomial coefficients.

The recursion runs at most $O(\log_p n)$ times, so the complexity of the algorithm is $O(f(p)+g(p)\log_p n)$, where $f(p)$ is the cost of preprocessing binomial coefficients and $g(p)$ is the cost of computing one binomial coefficient.

### Reference implementation

The reference implementation below precomputes the factorials up to $p$ and their inverses in $O(p)$ time, after which each binomial coefficient can be computed in $O(1)$ time:

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/lucas/lucas.cpp"
    ```

The time complexity of this implementation is $O(p+T\log_p n)$, where $T$ is the number of queries.

## exLucas algorithm

Lucas's theorem requires the modulus $p$ to be prime. When the modulus is not prime, we need the exLucas algorithm. Despite its name, the algorithm does not actually use Lucas's theorem. Its key step is [computing factorials modulo a prime power](./factorial.md). The second proof above shows how it is connected to Lucas's theorem.

### Prime power modulus

First, consider the case where the modulus is a prime power $p^\alpha$. Separating the power of $p$ in the factorial $n!$ from its other factors gives the decomposition:

$$
n! = p^{\nu_p(n!)}(n!)_p.
$$

Here $\nu_p(n!)$ is the exponent of $p$ in the prime factorization of $n!$, and $(n!)_p$ is clearly coprime to $p$. So the binomial coefficient can be written as:

$$
\binom{n}{k} = p^{\nu_p(n!)-\nu_p(k!)-\nu_p((n-k)!)}\dfrac{(n!)_p}{(k!)_p((n-k)!)_p}.
$$

Terms like $\nu_p(n!)$ can be computed with [Legendre's formula](./factorial.md#legendres-formula), and terms like $(n!)_p$ can be computed with a [recurrence](./factorial.md#prime-power-modulus). Since the latter are coprime to $p^\alpha$, the inverse of the product in the denominator can be computed with the [extended Euclidean algorithm](./inverse.md#extended-euclidean-algorithm). This solves the problem.

Note that if the exponent $\nu_p(n!)-\nu_p(k!)-\nu_p((n-k)!)\ge\alpha$, the remainder must be zero, and no further computation is needed.

### General modulus

When $m$ is a general composite number, first find its [prime factorization](./pollard-rho.md):

$$
m = p_1^{\alpha_1}p_2^{\alpha_2}\cdots p_s^{\alpha_s}.
$$

Then compute the remainder of the binomial coefficient $\dbinom{n}{k}$ modulo each $p_i^{\alpha_i}$, which gives $s$ congruences:

$$
\begin{cases}
\dbinom{n}{k} \equiv r_1 &\pmod{p_1^{\alpha_1}}, \\
\dbinom{n}{k} \equiv r_2 &\pmod{p_2^{\alpha_2}}, \\
\quad\quad\cdots\\
\dbinom{n}{k} \equiv r_s &\pmod{p_s^{\alpha_s}}.
\end{cases}
$$

Finally, use the [Chinese remainder theorem](./crt.md) to find the remainder modulo $m$.

### Reference implementation

Finally, here is a reference implementation for the template problem [Binomial Coefficients](https://loj.ac/p/181).

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/lucas/exlucas.cpp"
    ```

During preprocessing, the algorithm factors the modulus $m$ into prime powers. Then, for every $p^\alpha$, it precomputes the product of all natural numbers from $1$ to $p^\alpha$ that are not multiples of $p$, as well as the coefficient used for that modulus when combining answers with the Chinese remainder theorem. Preprocessing takes $O(\sqrt{m}+\sum_ip_i^{\alpha_i})$ time. Each query takes $O(\log m+\sum_i\log_{p_i}n)$ time; the two terms are the costs of computing inverses and of computing the exponents and factorial remainders, respectively.

## Exercises

-   [Luogu P3807 [Template] Lucas's Theorem](https://www.luogu.com.cn/problem/P3807)
-   [SDOI2010 Ancient Pig Script (Lucas's theorem)](https://loj.ac/problem/10229)
-   [Luogu P4720 [Template] Extended Lucas](https://www.luogu.com.cn/problem/P4720)
-   [Ceizenpok's formula](http://codeforces.com/gym/100633/problem/J)
