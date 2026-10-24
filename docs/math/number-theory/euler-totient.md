author: iamtwz, Chrogeek, Enter-tainer, StudyingFather, aofall, CCXXXI, CoelacanthusHex, frank-xjh, Great-designer, greyqz, guodong2005, henrytbtrue, Ir1d, kZime, lihaoyu1234, Marcythm, MegaOwIer, Menci, nalemy, orzAtalod, ouuan, Persdre, segment-tree, ShaoChenHeng, shuzhouliu, sshwy, Struggler-q, Tiphereth-A, TrisolarisHD, Xeonacid, yuhuoji

## Definition

Euler's totient function, $\varphi(n)$, is the number of integers from $1$ to $n$ that are coprime to $n$.

For example, $\varphi(1) = 1$.

When $n$ is prime, clearly $\varphi(n) = n - 1$.

## Properties

-   Euler's totient function is a [multiplicative function](./basic.md#积性函数).

    That is, for any integers $a,b$ with $\gcd(a, b) = 1$, we have $\varphi(ab) = \varphi(a)\varphi(b)$.

    In particular, when $n$ is odd, $\varphi(2n) = \varphi(n)$.

    For the proof, see [composition of residue systems](./basic.md#剩余系的复合).

-   $n = \sum_{d \mid n}{\varphi(d)}$.

    ???+ note "Proof"
        This follows from [Möbius inversion](./mobius.md).
        
        You can also think of it this way: if $\gcd(k, n) = d$, then $\gcd(\dfrac{k}{d},\dfrac{n}{d}) = 1, ( k < n )$.
        
        Let $f(x)$ be the number of $k$ with $\gcd(k, n) = x$. Then $n = \sum_{i = 1}^n{f(i)}$.
        
        From the argument above, $f(x) = \varphi(\dfrac{n}{x})$, so $n = \sum_{d \mid n}\varphi(\dfrac{n}{d})$. Since the divisors $d$ and $\dfrac{n}{d}$ are symmetric, this becomes $n = \sum_{d \mid n}\varphi(d)$.

-   If $n = p^k$ where $p$ is prime, then $\varphi(n) = p^k - p^{k - 1}$.
    (This follows from the definition.)

-   By unique factorization, write $n = \prod_{i=1}^{s}p_i^{k_i}$ with each $p_i$ prime. Then $\varphi(n) = n \times \prod_{i = 1}^s{\dfrac{p_i - 1}{p_i}}$.

    ???+ note "Proof"
        -   Lemma: for any prime $p$, $\varphi(p^k)=p^{k-1}\times(p-1)$.
        
            Proof: among the numbers from $1$ to $p^k$, all except the $p^{k-1}$ multiples of $p$ are coprime to $p^k$. So $\varphi(p^k)=p^k-p^{k-1}=p^{k-1}\times(p-1)$. QED.
        
        Now we prove $\varphi(n) = n \times \prod_{i = 1}^s{\dfrac{p_i - 1}{p_i}}$. By unique factorization and the multiplicativity of $\varphi(x)$,
        
        $$
        \begin{aligned}
            \varphi(n) &= \prod_{i=1}^{s} \varphi(p_i^{k_i}) \\
            &= \prod_{i=1}^{s} (p_i-1)\times {p_i}^{k_i-1}\\
            &=\prod_{i=1}^{s} {p_i}^{k_i} \times(1 - \frac{1}{p_i})\\
            &=n~ \prod_{i=1}^{s} (1- \frac{1}{p_i})
            &\square
        \end{aligned}
        $$

-   For any positive integers $m,n$, $\varphi(mn)\varphi(\gcd(m,n))=\varphi(m)\varphi(n)\gcd(m,n)$.

    This follows by direct computation from the previous property.

## Implementation

If you only need the totient of a single number, just compute it from the definition while factoring the number. This can be sped up with the [Pollard Rho](./pollard-rho.md) algorithm.

???+ note "Reference implementation"
    === "C++"
        ```cpp
        #include <cmath>
        
        int euler_phi(int n) {
          int ans = n;
          for (int i = 2; i * i <= n; i++)
            if (n % i == 0) {
              ans = ans / i * (i - 1);
              while (n % i == 0) n /= i;
            }
          if (n > 1) ans = ans / n * (n - 1);
          return ans;
        }
        ```
    
    === "Python"
        ```python
        import math
        
        
        def euler_phi(n):
            ans = n
            for i in range(2, math.isqrt(n) + 1):
                if n % i == 0:
                    ans = ans // i * (i - 1)
                    while n % i == 0:
                        n = n // i
            if n > 1:
                ans = ans // n * (n - 1)
            return ans
        ```

To get the totients of many numbers, use the linear sieve described later.

See: [Computing Euler's totient function with a sieve](./sieve.md#筛法求欧拉函数)

## Applications

Euler's totient function is often used to simplify sums of greatest common divisors. Some Chinese articles call this **Euler inversion**[^1].

Substituting $n=\gcd(a,b)$ into

$$
n=\sum_{d \mid n}\varphi(d)
$$

we get

$$
\gcd(a,b) = \sum_{d \mid \gcd(a,b)}\varphi(d) = \sum_d [d \mid a][d \mid b]\varphi(d),
$$

where $[\cdot]$ is the Iverson bracket. Summing this gives

$$
\sum_{i=1}^n\gcd(i,n)=\sum_{d}\sum_{i=1}^n[d \mid i][d \mid n]\varphi(d)=\sum_d\left\lfloor\frac{n}{d}\right\rfloor[d \mid n]\varphi(d)=\sum_{d \mid n}\left\lfloor\frac{n}{d}\right\rfloor\varphi(d).
$$

The key observation is $\sum_{i=1}^n[d \mid i]=\lfloor\frac{n}{d}\rfloor$, i.e., the number of $i$ between $1$ and $n$ divisible by $d$ is $\lfloor\frac{n}{d}\rfloor$.

With this formula, we can compute the sum by iterating over divisors. For many queries, precompute prefix sums of the totient function and use floor-division blocks (sqrt decomposition on $\lfloor n/d\rfloor$) to answer them.

???+ note "[GCD SUM](https://www.luogu.com.cn/problem/P2398)"
    Given $n\le 100000$, find
    
    $$
    \sum_{i=1}^n\sum_{j=1}^n\gcd(i,j).
    $$
    
    ??? note "Idea"
        Following the derivation above, we get
        
        $$
        \sum_{i=1}^n\sum_{j=1}^n\gcd(i,j) = \sum_{d=1}^n\left\lfloor\frac{n}{d}\right\rfloor^2\varphi(d).
        $$
        
        Here we need the totient of every number from $1$ to $n$; with a linear sieve the answer takes $O(n)$ time.

## Euler's theorem

A theorem closely related to Euler's totient function is Euler's theorem. It says:

If $\gcd(a, m) = 1$, then $a^{\varphi(m)} \equiv 1 \pmod{m}$.

### Extended Euler's theorem

There is also an extended Euler's theorem that handles general $a$ and $m$.

$$
a^b\equiv
\begin{cases}
a^{b\bmod\varphi(m)},\,&\gcd(a,\,m)=1\\
a^b,&\gcd(a,\,m)\ne1,\,b<\varphi(m)\\
a^{b\bmod\varphi(m)+\varphi(m)},&\gcd(a,\,m)\ne1,\,b\ge\varphi(m)
\end{cases}
\pmod m
$$

For the proof and exercises, see [Euler's theorem](./fermat.md).

## Exercises

-   [SPOJ ETF. Euler Totient Function](http://www.spoj.com/problems/ETF/)
-   [UVa 10179. Irreducible Basic Fractions](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1120)
-   [UVa 10299. Relatives](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1240)
-   [UVa 11327. Enumerating Rational Numbers](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2302)
-   [TIMUS 1673. Admission to Exam](http://acm.timus.ru/problem.aspx?space=1&num=1673)
-   [Luogu P1390 Sum of Common Divisors](https://www.luogu.com.cn/problem/P1390)
-   [Luogu P2155 \[SDOI2008\] Princess Sara's Puzzle](https://www.luogu.com.cn/problem/P2155)
-   [Luogu P2568 GCD](https://www.luogu.com.cn/problem/P2568)

## References and notes

[^1]: This term does not appear in academic journals or in forums outside China, so use it with care.
