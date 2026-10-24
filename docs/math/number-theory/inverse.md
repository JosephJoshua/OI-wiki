This article introduces the inverse of multiplication under a modulus, and discusses the common ways to compute it.

## Basic concepts

The multiplicative inverse of a nonzero real number $a\in\mathbf R$ is its reciprocal $a^{-1}$. Similarly, in number theory we can define the inverse of an integer $a$ modulo $m$, written $a^{-1}\bmod m$, or simply $a^{-1}$. This is the **modular multiplicative inverse**, also called the **number-theoretic reciprocal**.

???+ abstract "Inverse"
    For an integer $a$ and a positive integer $m$, if there exists $b$ such that $ab\equiv 1\pmod m$, then $b$ is called the **inverse** of $a$ modulo $m$.

In other words, $b$ is a solution of the linear congruence $ax\equiv 1\pmod m$. By the properties of [linear congruences](./linear-equation.md), the inverse $a^{-1}\bmod m$ exists if and only if $\gcd(a,m)=1$, i.e., $a$ and $m$ are coprime, and it is unique modulo $m$.

## Computing a single inverse

With the extended Euclidean algorithm or fast exponentiation, the inverse of a single integer can be found in $O(\log m)$ time.

### Extended Euclidean algorithm

Finding an inverse is the same as solving a linear congruence. So we can use the [extended Euclidean algorithm](./gcd.md#扩展欧几里得算法) to find the inverse in $O(\log\min\{a,m\})$ time. Also, since the linear equation for an inverse is a special case, the steps can be simplified a bit.

???+ example "Reference implementation"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/inverse/inverse-1.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/inverse/inverse-1.py:core"
        ```

This algorithm works in every case where the inverse exists.

### Fast exponentiation

This method mainly applies when the modulus is a prime $p$. In this case, by [Fermat's little theorem](./fermat.md#费马小定理), for any $a\perp p$ we have

$$
a\cdot a^{p-2} = a^{p-1} \equiv 1 \pmod p.
$$

Since the inverse is unique, the inverse $a^{-1}\bmod p$ equals $a^{p-2}\bmod p$, so we can compute it directly with [fast exponentiation](../binary-exponentiation.md) in $O(\log p)$ time:

???+ example "Reference implementation"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/inverse/inverse-2.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/inverse/inverse-2.py:core"
        ```

Of course, in theory this method can be extended to a general modulus $m$ using [Euler's theorem](./fermat.md#欧拉定理), i.e., computing the inverse as $a^{\varphi(m)-1}\bmod m$. However, computing [Euler's totient function](./euler-totient.md) $\varphi(m)$ for a single value is not easy, so this algorithm is usually not efficient in the general case.

## Computing many inverses

Sometimes we need to quickly find the inverses of many integers $a_1,a_2,\cdots,a_n$ modulo $m$. Finding them one by one takes $O(n\log m)$ time in total. In fact, if we handle them together, we can find all the inverses in $O(n+\log m)$ time.

Consider the prefix products of the sequence $\{a_i\}$:

$$
S_0 = 1,~ S_i = a_iS_{i-1},~ i=1,2,\cdots,n.
$$

As long as every $a_i$ is coprime to $m$, their product $S_n$ is coprime to $m$. So we can find $S_n^{-1}\bmod m$ with the algorithms above. Since the inverse of a product is the product of the inverses, starting from $S_n^{-1}$ and going through the sequence backwards, we can find the inverse of every $S_i$:

$$
S_{i-1}^{-1} = a_iS_i^{-1} \bmod m,~ i = n,n-1,\cdots,1.
$$

Then the inverse of each $a_i$ can be computed by:

$$
a_i^{-1} = S_{i-1}S_i^{-1} \bmod m,~ i = 1,2,\cdots,n.
$$

A reference implementation:

???+ example "Reference implementation"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/inverse/inverse-3.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/inverse/inverse-3.py:core"
        ```

The algorithm computes the inverse of a single element only once, so the total time complexity is $O(n+\log m)$.

## Precomputing inverses in linear time

If we want to precompute the inverses of the first $n$ positive integers modulo a prime $p$, we can also use the recurrence discussed in this section to do it in $O(n)$ time. This method is often used to precompute the inverses of the factorials of the first $n$ positive integers when computing binomial coefficients.

For a positive integer $i$ with $1< i < p$, consider division with remainder:

$$
p = \left\lfloor \dfrac{p}{i} \right\rfloor i + (p\bmod i).
$$

Taking this equation modulo the prime $p$ gives

$$
0 \equiv \left\lfloor \dfrac{p}{i} \right\rfloor i + (p\bmod i) \pmod p.
$$

Multiplying both sides by $i^{-1}(p\bmod i)^{-1}$ gives

$$
i^{-1} \equiv - \left\lfloor \dfrac{p}{i} \right\rfloor (p\bmod i)^{-1} \pmod p.
$$

This is the formula for computing inverses by a linear-time recurrence. Since $p\bmod i < i$, the formula reduces finding $i^{-1}\bmod p$ to the smaller problem $(p\bmod i)^{-1}\bmod p$. So, starting from $1^{-1}\bmod p=1$ and applying the formula to each $i$ in order, we get the inverses of the first $n$ integers in $O(n)$ time.

A reference implementation:

???+ example "Reference implementation"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/inverse/inverse-4.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/inverse/inverse-4.py:core"
        ```

This algorithm only works when the modulus is prime. When the modulus $m$ is not prime, there is no guarantee that $m\bmod i$ in the recurrence is still coprime to $m$, so the needed $(m\bmod i)^{-1}$ may not exist. One such example is $m=8,i=3$. Here $m\bmod i = 2$, which has no inverse modulo $m$.

Also, once we have this recurrence, a natural idea is to find the inverse of any single number $a$ by recursion directly. Each recursive step uses the recurrence to reduce the problem to the inverse of a smaller remainder $p\bmod a$, stopping when the remainder becomes $1$. The complexity of this approach is still unknown[^linear-recursion], so the standard methods above are recommended instead.

## Exercises

-   [LOJ 110 Modular Multiplicative Inverse](https://loj.ac/problem/110)
-   [LOJ 161 Modular Multiplicative Inverse 2](https://loj.ac/problem/161)
-   [LOJ 2605 "NOIP2012" Congruence Equation](https://loj.ac/problem/2605)
-   [Luogu P2054 "AHOI2005" Shuffling Cards](https://www.luogu.com.cn/problem/P2054)
-   [LOJ 2034 "SDOI2016" Permutation Counting](https://loj.ac/problem/2034)

## References and notes

-   [Modular multiplicative inverse - Wikipedia](https://en.wikipedia.org/wiki/Modular_multiplicative_inverse)

[^linear-recursion]: [riteme's answer on Zhihu](https://www.zhihu.com/question/59033693/answer/323292359) (in Chinese) points out that the best known theoretical upper bound for this approach is $O(p^{1/3+\varepsilon})$, while on random data it behaves close to $O(\log p)$.
