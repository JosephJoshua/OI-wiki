author: hydingsy, hyp1231, ranwen, 383494

Prerequisites: [number-theoretic blocking](./sqrt-decomposition.md), [Dirichlet convolution](./dirichlet.md#dirichlet-卷积)

Möbius inversion is an important topic in number theory. For some functions $f(n)$ whose values are hard to compute directly, but whose sums over multiples or divisors $g(n)$ are easy to compute, Möbius inversion can simplify the computation and give the values of $f(n)$.

## Möbius function

The Möbius function is defined as

$$
\mu(n)=
\begin{cases}
1,&n=1,\\
0,&n\text{ is divisible by a square }>1,\\
(-1)^k,&n\text{ is the product of }k\text{ distinct primes}.\\
\end{cases}
$$

More concretely, suppose the positive integer $n$ has prime factorization $n=\prod_{i=1}^kp_i^{e_i}$, where the $p_i$ are primes and the $e_i$ are positive integers. Then the three cases are:

1.  $\mu(1) = 1$;
2.  If there is an $i$ with $e_i > 1$, i.e., some prime factor appears more than once, then $\mu(n)=0$;
3.  Otherwise, $e_i = 1$ for all $i$, i.e., every prime factor appears exactly once, and $\mu(n)=(-1)^k$, where $k$ is the number of distinct prime factors.

### Properties

It is easy to check from the definition that the Möbius function $\mu(n)$ is multiplicative, but not completely multiplicative. Beyond that, its most important property is the following identity:

???+ note "Property"
    For a positive integer $n$,
    
    $$
    \sum_{d\mid n}\mu(d) = [n = 1] =
    \begin{cases}
    1,&n=1,\\
    0,&n\neq 1.\\
    \end{cases}
    $$
    
    Here $[\cdot]$ is the Iverson bracket.

??? note "Proof"
    Let $n=\prod_{i=1}^kp_i^{e_i}$ and $n' = \prod_{i=1}^kp_i$. By the [binomial theorem](../combinatorics/combination.md#二项式定理),
    
    $$
    \sum_{d\mid n}\mu(d) = \sum_{d\mid n'}\mu(d) = \sum_{i=0}^k\binom{k}{i}(-1)^i = (1 + (-1))^k = [k = 0] = [n = 1].
    $$

In terms of Dirichlet convolution, this identity can be written as $\varepsilon = 1 * \mu$. In other words, the Möbius function is the Dirichlet inverse of the constant function $1$.

This property has a very common application:

$$
[i\perp j] = [\gcd(i,j) = 1] = \sum_{d\mid\gcd(i,j)} \mu(d) = \sum_{d}[d\mid i][d\mid j]\mu(d).
$$

It turns the coprimality condition into a sum involving the Möbius function, which makes further derivations easier.

### Computing it

To compute the Möbius function $\mu(n)$ for a single $n$, we can use its [prime factorization](./pollard-rho.md). For example, when $n$ is not too large, $\mu(n)$ can be computed in $O(\sqrt{n})$ time.

???+ example "Reference implementation"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/mobius/mobius-func-1.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/mobius/mobius-func-1.py:core"
        ```

To precompute $\mu(n)$ for the first $n$ positive integers, we can use the fact that it is multiplicative and compute it with a [linear sieve](./sieve.md#筛法求莫比乌斯函数) in $O(n)$ time.

???+ example "Reference implementation"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/mobius/mobius-func-2.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/mobius/mobius-func-2.py:core"
        ```

## Möbius inversion

The most important application of the Möbius function is Möbius inversion.

???+ note "Möbius inversion"
    Let $f(n),g(n)$ be two arithmetic functions. Then
    
    $$
    f(n) = \sum_{d\mid n}g(d) \iff g(n) = \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)f(d).
    $$

??? note "Proof 1"
    Checking directly:
    
    $$
    \begin{aligned}
    \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)f(d)
    &= \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)\sum_{k\mid d}g(k)\\
    &= \sum_{k\mid n}g(k)\sum_d[k\mid d\mid n]\mu\left(\dfrac{n}{d}\right)\\
    &= \sum_{k\mid n}g(k)\sum_{d\mid n}\left[\frac{n}{d}\mid\frac{n}{k}\right]\mu\left(\dfrac{n}{d}\right)\\
    &= \sum_{k\mid n}g(k)\left[\frac{n}{k} = 1\right] \\
    &= g(n).
    \end{aligned}
    $$
    
    The key step is to swap the order of summation and notice that $k\mid d\mid n$ is equivalent to $\dfrac{n}{d}\mid\dfrac{n}{k}$. The second-to-last equality sums the Möbius function over the divisors $\dfrac{n}{d}$ of $\dfrac{n}{k}$, so it equals $\left[\dfrac{n}{k} = 1\right]$. This expression is nonzero only at $n=k$, and we end up with $g(n)$.

??? note "Proof 2"
    In terms of Dirichlet convolution, the statement is equivalent to
    
    $$
    f = 1 * g \iff g = \mu * f.
    $$
    
    Using $1 * \mu = \varepsilon$ and convolving both sides of the left-hand equation with $\mu$ gives
    
    $$
    f * \mu = (1 * g) * \mu = (1 * \mu) * g = \varepsilon * g = g.
    $$

For sums of arithmetic functions involving all kinds of divisibility relations, Möbius inversion is a powerful tool for transforming them.

???+ example "Examples"
    1.  [Euler's totient function](./euler-totient.md) $\varphi(n)$ satisfies $n = \sum_{d\mid n}\varphi(d)$, i.e., $\mathrm{id}=1*\varphi$. Inverting it gives $\varphi = \mu * \mathrm{id}$, i.e.,
    
        $$
        \varphi(n) = \sum_{d\mid n}d\mu\left(\dfrac{n}{d}\right).
        $$
    2.  The divisor function $\sigma_k(n) = \sum_{d\mid n}d^k$, i.e., $\sigma_k = 1 * \mathrm{id}_k$. Inverting it gives $\mathrm{id}_k = \mu * \sigma_k$, i.e.,
    
        $$
        n^k = \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)\sigma_k(d).
        $$
    3.  The number of distinct prime factors $\omega(n)=\sum_{d\mid n}[d\in\mathbf P]$, i.e., $\omega = 1* \mathbf{1}_{\mathbf P}$, where $\mathbf{1}_{\mathbf P}$ is the indicator function of the set of primes $\mathbf P$. Inverting it gives $\mathbf{1}_{\mathbf P} = \mu * \omega$, i.e.,
    
        $$
        [n\in\mathbf P] = \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)\omega(d).
        $$
    4.  Consider the arithmetic function $\Lambda(n)$ satisfying $\log n = \sum_{d\mid n}\Lambda(d)$. It is the Möbius inversion of the logarithm, also called the von Mangoldt function:
    
        $$
        \Lambda(n) = \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)\log d = 
        \begin{cases}
        \log p, & n = p^e,~p\in\mathbf P,~e\in\mathbf N_+, \\
        0, &\text{otherwise}.
        \end{cases}
        $$

??? note "Appendix: proof of the formula for $\Lambda(n)$"
    For a prime power $n=p^e~(e\in\mathbf N_+)$,
    
    $$
    \Lambda(n) = \sum_{i=0}^e\mu(p^{e-i})\log p^i = \log p^{e} - \log p^{e-1} = \log p.
    $$
    
    For $n=1$, clearly $\Lambda(n)=\log 1=0$. For any other composite $n$,
    
    $$
    \Lambda(n) = \sum_{d\mid n}\mu(d)(\log n-\log d) = \left(\sum_{d\mid n}\mu(d)\right)\log n-\sum_{d\mid n}\mu(d)\log d.
    $$
    
    By the property of the Möbius function, the coefficient of $\log n$ is $[n=1]=0$. For the second term, we can further split $d$ into a product of primes. For any prime $p\mid n$, write $n=p^em$ with $p\perp m$ (since $n$ is not a prime power, $m>1$). Looking at the coefficient of $\log p$ (only squarefree $d$ contribute), we get:
    
    $$
    -\sum_{p\mid d\mid n}\mu(d) = -\sum_{d'\mid m}\mu(pd') = \sum_{d'\mid m}\mu(d') = [m=1]=0.
    $$
    
    Therefore, for every composite $n$ with more than one prime factor, $\Lambda(n)=0$.

### Extended forms

Besides the basic form above, Möbius inversion has some common extended forms. First, there is a version with sums over multiples.

???+ note "Extension 1"
    Let $f(n),g(n)$ be two arithmetic functions. Then
    
    $$
    f(n) = \sum_{n\mid d}g(d) \iff g(n) = \sum_{n\mid d}\mu\left(\dfrac{d}{n}\right)f(d).
    $$

??? note "Proof"
    Checking directly:
    
    $$
    \begin{aligned}
    \sum_{n\mid d}\mu\left(\dfrac{d}{n}\right)f(d)
    &= \sum_{n\mid d}\mu\left(\dfrac{d}{n}\right)\sum_{d\mid k}g(k)\\
    &= \sum_{n\mid k}g(k)\sum_{d}[n\mid d\mid k]\mu\left(\dfrac{d}{n}\right)\\
    &= \sum_{n\mid k}g(k)\sum_{n\mid d}\left[\dfrac{d}{n}\mid\dfrac{k}{n}\right]\mu\left(\dfrac{d}{n}\right)\\
    &= \sum_{n\mid k}g(k)\left[\dfrac{k}{n}=1\right]\\
    &= g(n).
    \end{aligned}
    $$
    
    This is exactly dual to the derivation of the basic form.

Second, Möbius inversion is not limited to addition; it actually holds for the operation of any [abelian group](../algebra/basic.md#群). For example, it has the following multiplicative form:

???+ note "Extension 2"
    Let $f(n),g(n)$ be two arithmetic functions. Then
    
    $$
    f(n) = \prod_{d\mid n}g(d) \iff g(n) = \prod_{d\mid n}f(d)^{\mu(n/d)}.
    $$

??? note "Proof"
    Checking directly:
    
    $$
    \begin{aligned}
    \prod_{d\mid n}f(d)^{\mu(n/d)}
    &= \prod_{d\mid n}\left(\prod_{k\mid d}g(k)\right)^{\mu(n/d)}\\
    &= \prod_{k\mid n}g(k)\uparrow\left(\sum_d[k\mid d\mid n]\mu\left(\dfrac{n}{d}\right)\right)\\
    &= \prod_{k\mid n}g(k)\uparrow\left(\sum_{d\mid n}\left[\frac{n}{d}\mid\frac{n}{k}\right]\mu\left(\dfrac{n}{d}\right)\right)\\
    &= \prod_{k\mid n}g(k)\uparrow\left[\frac{n}{k} = 1\right] \\
    &= g(n).
    \end{aligned}
    $$
    
    Here $a\uparrow b = a^b$ is Knuth's arrow notation. Compared with the proof of the basic form, the only difference is that addition is replaced by multiplication, and multiplication by exponentiation.

From the viewpoint of Dirichlet convolution, Möbius inversion only uses the fact that "the Möbius function is the Dirichlet inverse of the constant function". It is easy to imagine that relations similar to Möbius inversion also hold for a general [Dirichlet inverse](./dirichlet.md#dirichlet-卷积).

???+ note "Extension 3"
    Let $f(n),g(n),\alpha(n)$ be arithmetic functions, and let $\alpha^{-1}(n)$ be the Dirichlet inverse of $\alpha(n)$, i.e.,
    
    $$
    [n=1] = \sum_{d\mid n}\alpha\left(\dfrac{n}{d}\right)\alpha^{-1}(d).
    $$
    
    Then
    
    $$
    f(n) = \sum_{d\mid n}\alpha\left(\dfrac{n}{d}\right)g(d) \iff g(n) = \sum_{d\mid n}\alpha^{-1}\left(\dfrac{n}{d}\right)f(d).
    $$

??? note "Proof"
    Checking directly:
    
    $$
    \begin{aligned}
    \sum_{d\mid n}\alpha^{-1}\left(\dfrac{n}{d}\right)f(d)
    &= \sum_{d\mid n}\alpha^{-1}\left(\dfrac{n}{d}\right)\sum_{k\mid d}\alpha\left(\dfrac{d}{k}\right)g(k)\\
    &= \sum_{k\mid n}g(k)\sum_d[k\mid d\mid n]\alpha\left(\dfrac{d}{k}\right)\alpha^{-1}\left(\dfrac{n}{d}\right)\\
    &= \sum_{k\mid n}g(k)\sum_{d\mid n}\left[\frac{n}{d}\mid\frac{n}{k}\right]\alpha\left(\dfrac{d}{k}\right)\alpha^{-1}\left(\dfrac{n/k}{d/k}\right)\\
    &= \sum_{k\mid n}g(k)\left[\frac{n}{k} = 1\right] \\
    &= g(n).
    \end{aligned}
    $$
    
    Compared with the proof of the basic form, we only need to replace the second-to-last equality with the definition of the Dirichlet inverse.

???+ note "Corollary"
    Let $f(n),g(n)$ be arithmetic functions, and let $t(n)$ be completely multiplicative. Then
    
    $$
    f(n) = \sum_{d\mid n}t\left(\dfrac{n}{d}\right)g(d) \iff g(n) = \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)t\left(\dfrac{n}{d}\right)f(d).
    $$

??? note "Proof"
    By a [property](./dirichlet.md#性质) of Dirichlet convolution, for a completely multiplicative function $t(n)$, its Dirichlet inverse is $\mu(n)t(n)$.

Finally, Möbius inversion can also be generalized to complex-valued functions on $[1,+\infty)$, not just arithmetic functions. The basic form of Möbius inversion can be seen as the special case where the complex-valued functions are zero at every non-integer point.

???+ note "Extension 4"
    Let $F(x)$ and $G(x)$ be complex-valued functions on $[1,+\infty)$. Then
    
    $$
    F(x) = \sum_{n = 1}^{\lfloor x\rfloor}G\left(\dfrac{x}{n}\right) \iff G(x) = \sum_{n = 1}^{\lfloor x\rfloor}\mu(n)F\left(\dfrac{x}{n}\right).
    $$

??? note "Proof"
    Extend the definitions of $F$ and $G$ by setting $F(x)=G(x)=0$ for all $x < 1$. Then the statement is equivalent to:
    
    $$
    F(x) = \sum_n G\left(\dfrac{x}{n}\right) \iff G(x) = \sum_n \mu(n)F\left(\dfrac{x}{n}\right).
    $$
    
    All these sums are over $n\in\mathbf N_+$.
    
    Checking directly:
    
    $$
    \begin{aligned}
    \sum_n \mu(n)F\left(\dfrac{x}{n}\right)
    &= \sum_n\mu(n)\sum_d G\left(\dfrac{x/n}{d}\right)\\
    &= \sum_k G\left(\dfrac{x}{k}\right)\sum_{n\mid k}\mu(n)\\
    &= \sum_k G\left(\dfrac{x}{k}\right)[k=1]\\
    &= G(x).
    \end{aligned}
    $$
    
    To get the second equality, set $k = nd$.

???+ note "Corollary"
    Let $f(n),g(n)$ be arithmetic functions. Then
    
    $$
    f(n) = \sum_{k=1}^ng\left(\left\lfloor\dfrac{n}{k}\right\rfloor\right) \iff g(n)=\sum_{k=1}^n\mu(k)f\left(\left\lfloor\dfrac{n}{k}\right\rfloor\right).
    $$

??? note "Proof"
    Just take $F(x)=f(\lfloor x\rfloor)$ and $G(x)=g(\lfloor x\rfloor)$.

These extended forms can be combined with each other to get more complex inversion relations.

### Dirichlet prefix sums

Prerequisites: [Prefix sums and difference arrays](../../basic/prefix-sum.md)

Consider the basic form of Möbius inversion:

$$
f(n) = \sum_{d\mid n}g(d) \iff g(n) = \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)f(d).
$$

In the left-hand equation, $f(n)$ is the sum of $g$ over all divisors of $n$. If we think of $a\mid b$ as "$a$ comes before $b$", then $f(n)$ can be seen as a kind of prefix sum of $g(n)$. So in the Chinese competitive programming community, computing $\{f(k)\}_{k=1}^n$ from $\{g(k)\}_{k=1}^n$ is also called the **Dirichlet prefix sum**, and the reverse process is called the Dirichlet difference. These methods mostly appear when we need to precompute an arithmetic function at the first $N$ points.

Next, let's discuss how to compute Dirichlet prefix sums. If we treat each prime as a dimension, this is a kind of high-dimensional prefix sum. Recall the [dimension-by-dimension prefix sum algorithm](../../basic/prefix-sum.md#dimension-by-dimension) for high-dimensional prefix sums: go through the dimensions one by one, and add the value at each position to its successor position along that dimension. For arithmetic functions, this means going through all primes $p$ from small to large and adding the function value at $n$ to the value at $np$. This is the same order as in the [sieve of Eratosthenes](./sieve.md#埃拉托斯特尼筛法). So this algorithm computes the Dirichlet prefix sums of a sequence of length $n$ in $O(n\log\log n)$ time. Similarly, the Dirichlet difference of a sequence can be computed with dimension-by-dimension differences in the same time complexity.

???+ example "Reference implementation"
    === "Dirichlet prefix sum"
        ```cpp
        --8<-- "docs/math/code/mobius/mobius-func-3.cpp:presum"
        ```
    
    === "Dirichlet difference"
        ```cpp
        --8<-- "docs/math/code/mobius/mobius-func-3.cpp:diff"
        ```

This method can be generalized to the extended forms, such as sums over multiples (Extension 1), the product form (Extension 2), and replacing the constant function with a completely multiplicative function (the corollary of Extension 3).

## Example problems

This section uses example problems to show how to apply Möbius inversion, along with some common transformation tricks. First, an example problem to get familiar with the basic technique for handling gcd conditions in sums.

???+ example "[Luogu P2522 \[HAOI 2011\] Problem b](https://www.luogu.com.cn/problem/P2522)"
    There are $T$ test cases. For each test case, compute:
    
    $$
    \sum_{i=x}^{n}\sum_{j=y}^{m}[\gcd(i,j)=k].
    $$
    
    Constraints: $1\le T,x,y,n,m,k\le 5\times 10^4$.

??? note "Solution"
    By the inclusion–exclusion principle, the sum can be split into $4$ parts, each of the form
    
    $$
    f(n,m,k)=\sum_{i=1}^{n}\sum_{j=1}^{m}[\gcd(i,j)=k].
    $$
    
    For sums like this, the following is a standard derivation: factor out the common divisor, apply the property of the Möbius function, and swap the order of summation.
    
    First, since $i,j$ can only be multiples of $k$, we can factor this out. This is the same as substituting $i=ki'$ and $j=kj'$, which gives:
    
    $$
    f(n,m,k)=\sum_{i=1}^{\lfloor n/k\rfloor}\sum_{j=1}^{\lfloor m/k\rfloor}[\gcd(i,j)=1].
    $$
    
    Then, by the property of the Möbius function:
    
    $$
    [\gcd(i,j)=1] = \sum_{d\mid\gcd(i,j)}\mu(d) = \sum_d[d\mid i][d\mid j]\mu(d).
    $$
    
    Substituting this into the expression and swapping the order of summation gives:
    
    $$
    f(n,m,k)=\sum_d\mu(d)\left(\sum_{i=1}^{\lfloor n/k\rfloor}[d\mid i]\right)\left(\sum_{j=1}^{\lfloor m/k\rfloor}[d\mid j]\right).
    $$
    
    The benefit of these steps is that, for fixed $d$, the terms involving $i$ and $j$ are separated and can be summed independently. Next, since
    
    $$
    \sum_{i=1}^{\lfloor n/k\rfloor}[d\mid i] = \left\lfloor\dfrac{\lfloor n/k\rfloor}{d}\right\rfloor,~\sum_{j=1}^{\lfloor m/k\rfloor}[d\mid j]=\left\lfloor\dfrac{\lfloor m/k\rfloor}{d}\right\rfloor,
    $$
    
    we have
    
    $$
    f(n,m,k)=\sum_d\mu(d)\left\lfloor\dfrac{\lfloor n/k\rfloor}{d}\right\rfloor\left\lfloor\dfrac{\lfloor m/k\rfloor}{d}\right\rfloor.
    $$
    
    After precomputing $\mu(d)$ with a linear sieve along with its prefix sums, we can solve it with number-theoretic blocking. The total time complexity is $O(N + T\sqrt{N})$, where $N$ is the upper bound of $n,m$ and $T$ is the number of test cases.

??? note "Reference code"
    ```cpp
    --8<-- "docs/math/code/mobius/mobius_1.cpp"
    ```

The next two example problems show how to handle enumerating the common divisor, and use a [sieve](./sieve.md#一般的积性函数) to compute the values of a general multiplicative function.

???+ example "[SPOJ LCMSUM](https://www.spoj.com/problems/LCMSUM/)"
    There are $T$ test cases. For each test case, compute:
    
    $$
    \sum_{i=1}^n \operatorname{lcm}(i,n).
    $$
    
    Constraints: $1\le T\le 3\times 10^5,~1\le n\le 10^6$.

??? note "Solution 1"
    The problem gives the least common multiple, but the greatest common divisor is usually easier to handle. So we first rewrite:
    
    $$
    f(n)=\sum_{i=1}^n \operatorname{lcm}(i,n) = \sum_{i=1}^n \frac{i\cdot n}{\gcd(i,n)}.
    $$
    
    Pull out $n$ and enumerate the greatest common divisor $k$:
    
    $$
    f(n)=n\sum_{k\mid n}\sum_{i=1}^n\dfrac{i}{k}[\gcd(i,n)=k].
    $$
    
    The inner sum is the most common case involving a gcd. Repeating the standard steps gives:
    
    $$
    \begin{aligned}
    f(n) &= n\sum_{k\mid n}\sum_{i=1}^{n/k}i\left[\gcd\left(i,\dfrac{n}{k}\right)=1\right]\\
    &= n\sum_{k\mid n}\sum_{i=1}^{n/k}i\sum_d\mu(d)[d\mid i]\left[d\mid \dfrac{n}{k}\right]\\
    &= n\sum_{k\mid n}\sum_d\mu(d)\left[d\mid \dfrac{n}{k}\right]\left(\sum_{i=1}^{n/k}i[d\mid i]\right).
    \end{aligned}
    $$
    
    Again, the sum over $i$ is separated from the rest and can be handled on its own. The last sum is actually the sum of an arithmetic sequence (take $i=di'$):
    
    $$
    \sum_{i=1}^{n/k}i[d\mid i] = d\frac{1}{2}\left(\dfrac{n}{kd}+1\right)\dfrac{n}{kd}=:dG\left(\dfrac{n}{kd}\right).
    $$
    
    This gives the following expression:
    
    $$
    f(n) = n\sum_{k\mid n}\sum_d\mu(d)\left[d\mid \dfrac{n}{k}\right]dG\left(\dfrac{n}{kd}\right).
    $$
    
    After enumerating the common divisor, double sums of this form are very common. There is also a standard way to handle them: introduce the product as a new variable $\ell=kd$, then swap the order of summation again. Since $d\mid(n/k)$ is equivalent to $d\mid\ell\mid n$, the expression becomes:
    
    $$
    f(n) = n\sum_{\ell\mid n}G\left(\dfrac{n}{\ell}\right)\sum_{d\mid\ell}\mu(d)d.
    $$
    
    Let $F(\ell)=\sum_{d\mid\ell}\mu(d)d$. Then the expression has the form:
    
    $$
    f(n) = n\sum_{\ell\mid n}G\left(\dfrac{n}{\ell}\right)F(\ell).
    $$
    
    Since $\mu(d)d$ is multiplicative, its convolution $F(n)$ with the constant function $1$ is also multiplicative. Although the sum in the expression above has the form of a Dirichlet convolution, $G(n)$ is not multiplicative, so the sum as a whole is not multiplicative. However, $G(n)$ is a polynomial, so it is a linear combination of completely multiplicative functions. Therefore,
    
    $$
    f(n) = \dfrac{1}{2}n\left(\sum_{\ell\mid n}\left(\dfrac{n}{\ell}\right)^2F(\ell) + \sum_{\ell\mid n}\dfrac{n}{\ell}F(\ell)\right).
    $$
    
    Both terms (without the coefficient) are multiplicative functions and can be precomputed directly with a linear sieve (or, after sieving the inner function linearly, with Dirichlet prefix sums in $O(N\log\log N)$ time). Specifically, let
    
    $$
    H_s(n) = \sum_{\ell\mid n}\left(\dfrac{n}{\ell}\right)^sF(\ell),~s=1,2.
    $$
    
    To derive their formulas, we only need their values at prime powers. For a prime $p$ and a positive exponent $e$,
    
    $$
    \begin{aligned}
    F(p^e) &= \mu(1) + \mu(p)p + \sum_{j=2}^e\mu(p^j)p^j = 1-p,\\
    H_s(p^e) &= (p^e)^{s}F(1) + \sum_{j=1}^e(p^{e-j})^sF(p^j) = p^{es} + (1-p)\dfrac{1-p^{es}}{1-p^s},~s=1,2.
    \end{aligned}
    $$
    
    In particular, $H_1(p^e)=1$ is a constant function, and
    
    $$
    H_2(p^e) = p^{2e} + (1-p)\dfrac{1-p^{2e}}{1-p^2} = H_2(p^{e-1}) + p^{2e} - p^{2e-1}.
    $$
    
    This is easy to compute with a linear sieve. After precomputing $H_2(n)$ with a linear sieve, each query can be answered in $O(1)$ time with the formula $f(n)=(n/2)(H_2(n)+1)$. The total time complexity is $O(N+T)$, where $N$ is the upper bound of $n$ and $T$ is the number of test cases.
    
    The reference implementation uses the special form of this problem's formula to simplify the linear sieve part further, but this is not necessary. Using only the values at prime powers, the preprocessing can still be done in $O(N)$ time. See Solution 2 for these derivations.

??? note "Solution 2"
    For this particular problem, there is a more flexible approach. From Solution 1 we see that
    
    $$
    f(n) = n\sum_{k\mid n}\sum_{i=1}^{n/k}i\left[\gcd\left(i,\dfrac{n}{k}\right)=1\right] = n\sum_{k\mid n}F\left(\dfrac{n}{k}\right).
    $$
    
    Instead of continuing with Möbius inversion at this step, observe that the inner sum is actually the sum of the integers not exceeding $d=n/k$ that are coprime to it. For $d>1$, integers coprime to $d$ come in pairs, i.e., $i$ and $d-i$ are either both coprime to $d$ or both not, so
    
    $$
    F(d)=\sum_{i=1}^{d}i[i\perp d] = \sum_{i=1}^{d}(d-i)[i\perp d] = \dfrac{1}{2}d\sum_{i=1}^{d}[i\perp d] = \dfrac{1}{2}d\varphi(d).
    $$
    
    For $d=1$,
    
    $$
    F(d)=1=\dfrac{1}{2}+\dfrac{1}{2}d\varphi(d).
    $$
    
    So the expression can be written as
    
    $$
    f(n) = \dfrac{1}{2}n\left(\sum_{d\mid n}d\varphi(d) + 1\right).
    $$
    
    Since $G(n)=\sum_{d\mid n}d\varphi(d)$ is the Dirichlet convolution of the multiplicative function $n\varphi(n)$ with the constant function $1$, it is also multiplicative and can be precomputed with a linear sieve. For this, we only need its values at prime powers. For a prime $p$ and a positive exponent $e$,
    
    $$
    G(p^e) = 1 + \sum_{i=1}^ep^i\cdot p^{i-1}(p-1) = G(p^{e-1}) + p^{2e} - p^{2e-1}.
    $$
    
    This formula matches the result derived in Solution 1. The total time complexity of this method is still $O(N+T)$.
    
    Finally, using the formula of this problem's multiplicative function, we can further simplify the linear sieve. For a prime $p$,
    
    $$
    G(p) = 1 - p + p^2.
    $$
    
    The key to the linear sieve is computing $G(pn)$ for a general $n$. There are two cases. When $p\perp n$, since $G$ is multiplicative,
    
    $$
    G(pn) = G(p)G(n).
    $$
    
    Otherwise, when $p\mid n$, write $n=p^em$ with $p\perp m$. Then
    
    $$
    \begin{aligned}
    G(pn) &= G(p^{e+1})G(m)\\
    &= G(p^e)G(m) + (p^{2e+2} - p^{2e+1})G(m)\\
    &= G(n) + (p^{2e+2} - p^{2e+1})G(m).
    \end{aligned}
    $$
    
    One can check directly that this formula also holds when $p\perp n$ (i.e., $e=0$). When $p\mid n$, we also have
    
    $$
    G(n) - G\left(\dfrac{n}{p}\right) = (p^{2e}-p^{2e-1})G(m).
    $$
    
    Substituting this into the formula above gives
    
    $$
    G(pn) = G(n) + p^2\left(G(n) - G\left(\dfrac{n}{p}\right)\right).
    $$
    
    This simplifies the linear sieve. Of course, this derivation is not necessary: for multiplicative functions without special properties, the linear sieve can be done directly with $G(pn)=G(p^{e+1})G(m)$.

??? note "Reference code"
    ```cpp
    --8<-- "docs/math/code/mobius/mobius_2.cpp"
    ```

???+ example "[BZOJ 2154 \[National Training Team\] Crash's Digital Table](https://hydro.ac/p/bzoj-P2154)"
    Compute:
    
    $$
    \sum_{i=1}^n\sum_{j=1}^m\operatorname{lcm}(i,j)\mod{20101009}.
    $$
    
    Constraints: $1\le n,m\le 10^7$.

??? note "Solution"
    We ignore the modulus during the derivation. Let
    
    $$
    f(n,m) = \sum_{i=1}^n\sum_{j=1}^m\operatorname{lcm}(i,j).
    $$
    
    Again, convert the least common multiple into the greatest common divisor, enumerate the common divisor, and apply the standard steps to get
    
    $$
    \begin{aligned}
    f(n,m)
    &= \sum_k\sum_{i=1}^n\sum_{j=1}^m\dfrac{ij}{k}[\gcd(i,j)=k] \\
    &= \sum_k\sum_{i=1}^{\lfloor n/k\rfloor}\sum_{j=1}^{\lfloor m/k\rfloor} kij[\gcd(i,j)=1]\\
    &= \sum_k\sum_{i=1}^{\lfloor n/k\rfloor}\sum_{j=1}^{\lfloor m/k\rfloor} kij\sum_d\mu(d)[d\mid i][d\mid j]\\
    &= \sum_kk\sum_d\mu(d)\left(\sum_{i=1}^{\lfloor n/k\rfloor}i[d\mid i]\right)\left(\sum_{j=1}^{\lfloor m/k\rfloor}j[d\mid j]\right).
    \end{aligned}
    $$
    
    Again, the sums over $i$ and $j$ are separated. First compute these inner sums by factoring out $d$ (i.e., taking $i=di'$):
    
    $$
    \sum_{i=1}^{\lfloor n/k\rfloor}i[d\mid i] = d\sum_{i=1}^{\lfloor\lfloor n/k\rfloor/d\rfloor}i = dG\left(\left\lfloor\dfrac{\lfloor n/k\rfloor}{d}\right\rfloor\right) = dG\left(\left\lfloor\dfrac{n}{kd}\right\rfloor\right).
    $$
    
    Here $G(n)=\dfrac{1}{2}n(n+1)$ is the sum of an arithmetic sequence, and the last equality uses a property of the [floor function](./basic.md#取整函数). The other sum is computed symmetrically. Substituting back into the expression above gives
    
    $$
    f(n,m) = \sum_k k\sum_{d}\mu(d)d^2G\left(\left\lfloor\dfrac{n}{kd}\right\rfloor\right)G\left(\left\lfloor\dfrac{m}{kd}\right\rfloor\right).
    $$
    
    As before, for sums like this that enumerate a common divisor, we usually enumerate the product $\ell = kd$ and swap the order of summation again:
    
    $$
    f(n,m) = \sum_{\ell}\left(\sum_{d\mid\ell}\mu(d)d\ell\right)G\left(\left\lfloor\dfrac{n}{\ell}\right\rfloor\right)G\left(\left\lfloor\dfrac{m}{\ell}\right\rfloor\right).
    $$
    
    Let
    
    $$
    F(\ell) = \sum_{d\mid\ell}\mu(d)d\ell.
    $$
    
    This is the product of the multiplicative function $\ell$ and the multiplicative function $\sum_{d\mid\ell}\mu(d)d$, so it is also multiplicative. We can precompute it and its prefix sums directly with a linear sieve. Then $f(n,m)$ can be computed with number-theoretic blocking. The total time complexity is $O(\min\{n,m\})$.

??? note "Reference code"
    ```cpp
    --8<-- "docs/math/code/mobius/mobius_3.cpp"
    ```

The next example problem is a bit special: it requires transforming the divisor-count function of a product.

???+ example "[LOJ 2185. \[SDOI2015\] Sum of Divisor Counts](https://loj.ac/problem/2185)"
    There are $T$ test cases. For each test case, compute:
    
    $$
    \sum_{i=1}^n\sum_{j=1}^m\sigma_0(ij).
    $$
    
    Here $\sigma_0(n)=\sum_{d \mid n}1$ is the number of divisors of $n$.
    
    Constraints: $1\le n,m,T\le 5\times 10^4$.

??? note "Solution"
    The hard part of this problem is turning $\sigma_0(ij)$ into an expression involving the gcd. Since $\sigma_0$ is multiplicative, first consider prime powers. For a prime $p$ and non-negative exponents $e_1,e_2$, let $i=p^{e_1},~j=p^{e_2}$. Then
    
    $$
    \sigma_0(ij) = 1 + e_1 + e_2 = \sum_{x\mid i}\sum_{y\mid j}[x\perp y].
    $$
    
    In the general case, write $i=\prod_p i_p$ and $j=\prod_p j_p$, where $i_p,j_p$ are the prime-power factors for $p$ in the prime factorizations of $i,j$. Then
    
    $$
    \sigma_0(ij) = \prod_p\sigma_0(i_pj_p)= \prod_p\sum_{x_p\mid i_p}\sum_{y_p\mid j_p}[x_p\perp y_p].
    $$
    
    Note that enumerating a divisor $x_p$ of every prime-power factor $i_p$ of $i$ is the same as enumerating a divisor $x$ of $i$ and then splitting it into its prime-power factors $x_p$; the same holds for $j$. So, by the distributive law, we get
    
    $$
    \sigma_0(ij) = \sum_{x\mid i}\sum_{y\mid j}\prod_p[x_p\perp y_p] = \sum_{x\mid i}\sum_{y\mid j}[x\perp y].
    $$
    
    The last step uses the fact that $x\perp y$ if and only if $x_p\perp y_p$ holds for every prime factor $p$.
    
    With this expression, we can apply the standard steps:
    
    $$
    \begin{aligned}
    \sigma_0(ij) 
    &= \sum_{x\mid i}\sum_{y\mid j}[x\perp y]\\
    &= \sum_{x\mid i}\sum_{y\mid j}\sum_d\mu(d)[d\mid x][d\mid y]\\
    &= \sum_d\mu(d)\left(\sum_{x}[d\mid x\mid i]\right)\left(\sum_{y}[d\mid y\mid j]\right)\\
    &= \sum_d\mu(d)[d\mid i][d\mid j]\sigma_0\left(\dfrac{i}{d}\right)\sigma_0\left(\dfrac{j}{d}\right).
    \end{aligned}
    $$
    
    The last step means: the function is nonzero only when $d\mid i$ and $d\mid j$, and in that case, enumerating $x$ with $d\mid x\mid i$ is the same as enumerating the divisors $\dfrac{x}{d}$ of $\dfrac{i}{d}$; the same goes for $y$ with $d\mid y\mid j$.
    
    Substitute this expression back into the original sum and swap the order of summation:
    
    $$
    \begin{aligned}
    f(n,m)
    &= \sum_{i=1}^n\sum_{j=1}^m\sigma_0(ij)\\
    &= \sum_{i=1}^n\sum_{j=1}^m\sum_d\mu(d)[d\mid i][d\mid j]\sigma_0\left(\dfrac{i}{d}\right)\sigma_0\left(\dfrac{j}{d}\right)\\
    &= \sum_d\mu(d)\left(\sum_{i=1}^n[d\mid i]\sigma_0\left(\dfrac{i}{d}\right)\right)\left(\sum_{j=1}^m[d\mid j]\sigma_0\left(\dfrac{j}{d}\right)\right)\\
    &= \sum_d\mu(d)\left(\sum_{i=1}^{\lfloor n/d\rfloor}\sigma_0(i)\right)\left(\sum_{j=1}^{\lfloor m/d\rfloor}\sigma_0(j)\right).
    \end{aligned}
    $$
    
    Let $G(n)=\sum_{i=1}^n\sigma_0(i)$. Then
    
    $$
    f(n,m)=\sum_{d}\mu(d)G\left(\left\lfloor\dfrac{n}{d}\right\rfloor\right)G\left(\left\lfloor\dfrac{m}{d}\right\rfloor\right).
    $$
    
    This can be solved with number-theoretic blocking. We only need to precompute the prefix sums of $\mu(n)$ and $\sigma_0(n)$. The total time complexity is $O(N+T\sqrt{N})$, where $N$ is the upper bound of $n,m$ and $T$ is the number of test cases.

??? note "Reference code"
    ```cpp
    --8<-- "docs/math/code/mobius/mobius_4.cpp"
    ```

The last example problem shows how to apply the multiplicative version of Möbius inversion.

???+ example "[Luogu P5221 Product](https://www.luogu.com.cn/problem/P5221)"
    Compute:
    
    $$
    \prod_{i=1}^n\prod_{j=1}^n\dfrac{\operatorname{lcm}(i,j)}{\gcd(i,j)}\pmod{104857601}.
    $$
    
    Constraints: $1\le n\le 1\times 10^6$.

??? note "Solution 1"
    We ignore the modulus during the derivation. Let
    
    $$
    f(n) = \prod_{i=1}^n\prod_{j=1}^n\dfrac{\operatorname{lcm}(i,j)}{\gcd(i,j)}.
    $$
    
    Again, convert the least common multiple into the greatest common divisor:
    
    $$
    f(n) = \prod_{i=1}^n\prod_{j=1}^n\dfrac{ij}{(\gcd(i,j))^2}.
    $$
    
    Note that the products of these factors are independent and can be computed separately. Let
    
    $$
    g(n) = \prod_{i=1}^n\prod_{j=1}^n\gcd(i,j).
    $$
    
    Then the expression equals:
    
    $$
    f(n) = \dfrac{(n!)^{2n}}{g(n)^2}.
    $$
    
    The main task is computing $g(n)$. The steps are similar to those above, but we need the corresponding multiplicative versions. First, enumerate and factor out the common divisor:
    
    $$
    \begin{aligned}
    g(n) &= \prod_k\prod_{i=1}^n\prod_{j=1}^nk\uparrow[\gcd(i,j)=k]\\
    &= \prod_k\prod_{i=1}^{\lfloor n/k\rfloor}\prod_{j=1}^{\lfloor n/k\rfloor}k\uparrow[\gcd(i,j)=1].
    \end{aligned}
    $$
    
    Here $a\uparrow b=a^b$ is Knuth's arrow notation. Next, substitute $[\gcd(i,j)=1]=\sum_d\mu(d)[d\mid i][d\mid j]$, and turn the sum in the exponent into a product of powers:
    
    $$
    g(n) = \prod_k\prod_d\prod_{i=1}^{\lfloor n/k\rfloor}\prod_{j=1}^{\lfloor n/k\rfloor}k\uparrow(\mu(d)[d\mid i][d\mid j]).
    $$
    
    Factor out further (i.e., let $i=di'$, $j=dj'$) and apply a property of the [floor function](./basic.md#取整函数) to get:
    
    $$
    g(n) = \prod_k\prod_d\prod_{i=1}^{\lfloor n/(kd)\rfloor}\prod_{j=1}^{\lfloor n/(kd)\rfloor}k\uparrow\mu(d).
    $$
    
    Then separate the products over $i,j$. The factor does not contain $i,j$, so this is just raising it to a power:
    
    $$
    g(n) = \prod_k\prod_d k\uparrow\left(\mu(d)\left\lfloor\dfrac{n}{kd}\right\rfloor^2\right).
    $$
    
    Since we enumerated the common divisor earlier, we need to swap the order of the products again. Let $\ell = kd$:
    
    $$
    \begin{aligned}
    g(n) &= \prod_{\ell}\prod_{d\mid\ell}\left(\dfrac{\ell}{d}\right)\uparrow\left(\mu(d)\left\lfloor\dfrac{n}{\ell}\right\rfloor^2\right)\\
    &= \prod_\ell\left(\prod_{d\mid\ell}\left(\dfrac{\ell}{d}\right)\uparrow\mu(d)\right)\uparrow\left\lfloor\dfrac{n}{\ell}\right\rfloor^2.
    \end{aligned}
    $$
    
    Let
    
    $$
    F(n) = \prod_{d\mid n}\left(\dfrac{n}{d}\right)\uparrow\mu(d).
    $$
    
    It is easy to see that this is the multiplicative-form Möbius inversion of $\tilde F(n)=n$. Even without knowing its formula, we can precompute it in $O(n\log\log n)$ time with the [Dirichlet difference](#dirichlet-prefix-sums) method. Of course, since $\tilde F(n)$ is very simple, the formula of $F(n)$ can be found directly:
    
    $$
    F(n) = 
    \begin{cases}
    p, & n = p^e,~p\in\mathbf P,~e\in\mathbf N_+, \\
    1, &\text{otherwise}.
    \end{cases}
    $$
    
    The [von Mangoldt function](#möbius-inversion) is its natural logarithm. Once we have the values of $F(n)$, we can directly apply the product version of number-theoretic blocking to find $g(n)$ in $O(\sqrt{n})$ time, and then $f(n)$. The total time complexity is $O(n)$.
    
    Note that when computing products, we often need [Euler's theorem](./fermat.md), so the modulus used for the exponents is different from the modulus given in the problem.

??? note "Solution 2"
    The hard part of the product version is that working with products and powers feels less familiar. So for problems like this, we can also take logarithms first and then derive. For this problem, we only consider the derivation of $g(n)$. Taking logarithms gives:
    
    $$
    \log g(n) = \sum_{i=1}^n\sum_{j=1}^n\log\gcd(i,j).
    $$
    
    For a sum involving the gcd like this, applying the standard steps directly gives:
    
    $$
    \begin{aligned}
    \log g(n) 
    &= \sum_k\log k\sum_{i=1}^n\sum_{j=1}^n[\gcd(i,j)=k]\\
    &= \sum_k\log k\sum_{i=1}^{\lfloor n/k\rfloor}\sum_{j=1}^{\lfloor n/k\rfloor}[\gcd(i,j)=1]\\
    &= \sum_k\log k\sum_d\mu(d)\left(\sum_{i=1}^{\lfloor n/k\rfloor}[d\mid i]\right)\left(\sum_{j=1}^{\lfloor n/k\rfloor}[d\mid j]\right)\\
    &= \sum_k\log k\sum_d\mu(d)\left\lfloor\dfrac{n}{kd}\right\rfloor^2\\
    &= \sum_{\ell}\left(\sum_{d\mid\ell}\mu(d)\log\dfrac{\ell}{d}\right)\left\lfloor\dfrac{n}{\ell}\right\rfloor^2\\
    &= \sum_{\ell}\Lambda(\ell)\left\lfloor\dfrac{n}{\ell}\right\rfloor^2.
    \end{aligned}
    $$
    
    Here $\Lambda(n)$ is the [von Mangoldt function](#möbius-inversion). Exponentiating this result gives the result of Solution 1.

??? note "Reference code"
    ```cpp
    --8<-- "docs/math/code/mobius/mobius_5.cpp"
    ```

## Exercises

-   [Luogu P3312 \[SDOI2014\] Number Table](https://www.luogu.com.cn/problem/P3312)
-   [Luogu P3700 \[CQOI2017\] Little Q's Table](https://www.luogu.com.cn/problem/P3700)
-   [Luogu P3704 \[SDOI2017\] Digital Table](https://www.luogu.com.cn/problem/P3704)
-   [Luogu P3768 A Simple Math Problem](https://www.luogu.com.cn/problem/P3768)
-   [Luogu P4464 \[National Training Team\] JZPKIL](https://www.luogu.com.cn/problem/P4464)
-   [Luogu P4619 \[SDOI2018\] Old Problem](https://www.luogu.com.cn/problem/P4619)
-   [Luogu P5518 \[MtOI2019\] Phantom Ensemble](https://www.luogu.com.cn/problem/P5518)
-   [Luogu P6222 Simple Problem (Enhanced Version)](https://www.luogu.com.cn/problem/P6222)
-   [Luogu P6825 "EZEC-4" Summation](https://www.luogu.com.cn/problem/P6825)
-   [Luogu P7486 "Stoi2031" Rainbow](https://www.luogu.com.cn/problem/P7486)
-   [AtCoder Grand Contest 038 C - LCMs](https://atcoder.jp/contests/agc038/tasks/agc038_c)
-   [Codeforces 1139 D. Steps to One](https://codeforces.com/problemset/problem/1139/D)

## References

-   [Möbius function - Wikipedia](https://en.wikipedia.org/wiki/M%C3%B6bius_function)
-   [Möbius inversion formula - Wikipedia](https://en.wikipedia.org/wiki/M%C3%B6bius_inversion_formula)
-   [Von Mangoldt function - Wikipedia](https://en.wikipedia.org/wiki/Von_Mangoldt_function)
-   [algocode algorithm blog](https://web.archive.org/web/20190523150159/https://algocode.net/2018/04/18/20180418-KB-Mobius-Inversion-Formula/) (in Chinese)
