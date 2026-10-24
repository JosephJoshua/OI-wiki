author: PeterlitsZo, Tiphereth-A

This page discusses Fermat's little theorem, Euler's theorem and its extension. Together, these theorems let us compute powers with arbitrarily large exponents modulo any number.

## Fermat's little theorem

**Fermat's little theorem** is one of the most basic theorems in number theory. It is also the theoretical basis of the [Fermat primality test](./prime.md#fermat-primality-test).

???+ note "Fermat's little theorem"
    Let $p$ be a prime. For any integer $a$ with $p\nmid a$, we have $a^{p-1}\equiv 1\pmod p$.

???+ note "Theorem"
    Let $p$ be a prime. For any integer $a$, we have $a^{p}\equiv a\pmod p$.

These two congruences are equivalent when $p\nmid a$; and when $p\mid a$, $a^p\equiv 0\equiv a\pmod p$ holds trivially. So the two statements are equivalent, and both are often called Fermat's little theorem.

??? note "Proof 1"
    Let $p$ be a prime with $p\nmid a$. First we show that the remainders $ia \bmod p$ for $i=1,2,\cdots,p-1$ are all distinct. Suppose not: then there are $1\le i < j < p$ with
    
    $$
    ia \bmod p = ja \bmod p \iff (j-i)a\equiv 0.\pmod p
    $$
    
    But neither $(j-i)$ nor $a$ is a multiple of $p$, which is a contradiction.
    
    In other words, these remainders are a permutation of $\{1,2,\cdots,p-1\}$. Therefore,
    
    $$
    \prod_{i=1}^{p-1}i = \prod_{i=1}^{p-1}(ia\bmod p) \equiv \prod_{i=1}^{p-1}ia = a^{p-1}\prod_{i=1}^{p-1}i.\pmod p
    $$
    
    This means
    
    $$
    (a^{p-1}-1)\prod_{i=1}^{p-1}i \equiv 0. \pmod{p}
    $$
    
    That is, the left-hand side is a multiple of $p$, but none of $i=1,2,\cdots, p-1$ is a multiple of $p$. So we must have $p\mid (a^{p-1}-1)$, which is Fermat's little theorem.

??? note "Proof 2"
    Note that the second form of Fermat's little theorem holds for all $a\in\mathbf N$, so we can use mathematical induction. The case of negative integers easily reduces to the nonnegative case.
    
    The base case is $0^p\equiv 0\pmod p$, which clearly holds. Suppose it holds for $a\in\mathbf N$; we need to show it holds for $a+1$. By the binomial theorem,
    
    $$
    (a+1)^p=a^p+\binom{p}{1}a^{p-1}+\binom{p}{2}a^{p-2}+\cdots +\binom{p}{p-1}a+1.
    $$
    
    For every term except the first and last, in the binomial coefficient $\dbinom{p}{k} = \dfrac{p!}{k!(p-k)!}$, $p$ divides the numerator but not the denominator. So these coefficients are multiples of $p$ for $k\neq 0,p$. Therefore,
    
    $$
    (a+1)^p \equiv a^p + 1\equiv a + 1. \pmod{p}
    $$
    
    The second step uses the induction hypothesis. So by mathematical induction, Fermat's little theorem holds.

The converse of Fermat's little theorem is false. Even if $a^{n-1}\equiv 1\pmod n$ for every $a$ coprime to $n$, $n$ need not be prime. See the section on the [Fermat primality test](./prime.md#fermat-primality-test) for details.

## Euler's theorem

**Euler's theorem** generalizes Fermat's little theorem to arbitrary moduli, but still requires the base to be coprime to the modulus.

???+ note "Euler's theorem"
    For an integer $m>0$ and an integer $a$ with $\gcd(a,m)=1$, we have $a^{\varphi(m)}\equiv 1\pmod{m}$, where $\varphi(\cdot)$ is [Euler's totient function](./euler-totient.md).

??? note "Proof"
    Like Proof 1 of Fermat's little theorem, we take a set of numbers coprime to $m$ and work with it. Consider the set
    
    $$
    R = \{r\in\mathbf N : 0 < r < m,~\gcd(r,m)=1\}.
    $$
    
    This is a [reduced residue system](./basic.md#residue-classes-and-residue-systems) modulo $m$. By the definition of Euler's totient function, $|R|=\varphi(m)$. As above, multiplying them by $a$ just permutes the set:
    
    $$
    R = \{ar\bmod m: r\in R\}.
    $$
    
    This is because it is easy to check that $\gcd(ar,m)=1$, and different $r_1,r_2\in R$ give different $ar_1\bmod m$ and $ar_2\bmod m$. Therefore,
    
    $$
    \prod_{r\in R}r \equiv \prod_{r\in R}ar = a^{\varphi(m)}\prod_{r\in R}r. \pmod{m}
    $$
    
    Repeating the earlier argument and cancelling $\prod_{r\in R}r$ gives $a^{\varphi(m)}\equiv 1\pmod m$.

For a prime $p$, $\varphi(p)=p-1$, so Fermat's little theorem is a special case of Euler's theorem. Also, the exponent $\varphi(m)$ in Euler's theorem is in general not the smallest exponent for which the congruence holds. It can be improved to $\lambda(m)$, where $\lambda(\cdot)$ is the [Carmichael function](./primitive-root.md#carmichael-function). For the algebraic background of these results, see the section on the [multiplicative group of integers modulo $m$](../algebra/ring-theory.md#application-the-multiplicative-group-of-integers-modulo-n).

## Extended Euler's theorem

The extended Euler's theorem[^ex-euler] further generalizes the result to the case where the base is not coprime to the modulus. With it, we can compute any power of any base modulo any number: it reduces the exponent to less than $2\varphi(m)$, after which [binary exponentiation](../binary-exponentiation.md) computes the power in $O(\log\varphi(m))$ time.

???+ note "Extended Euler's theorem"
    For any positive integer $m$, integer $a$ and nonnegative integer $k$,
    
    $$
    a^k \equiv \begin{cases}
    a^{k \bmod \varphi(m)},                &\gcd(a,m) =  1,                   \\
    a^k,                                   &\gcd(a,m)\ne 1, k <   \varphi(m), \\
    a^{(k \bmod \varphi(m)) + \varphi(m)}, &\gcd(a,m)\ne 1, k \ge \varphi(m).
    \end{cases} \pmod m
    $$

The second case says that if $k < \varphi(m)$, there is no need to reduce the exponent; just use binary exponentiation directly. The main difference between the third case and the first is whether we need to add $\varphi(m)$ after reducing the exponent modulo $\varphi(m)$. Of course, merging the first case into the second and third cases is also correct.

### Intuition

Before proving the theorem rigorously, let us first understand what it means intuitively.

![fermat1](./images/fermat.svg)

Consider how the remainder $a^k\bmod m$ changes as $k$ grows. The remainder always lies in $[0,m)$, while there are infinitely many values of $k$. Treat $a^k\bmod m \mapsto a^{k+1}\bmod m$ as a directed edge between these remainder nodes. Then they must form a cycle like the one in the figure.

The extended Euler's theorem says that the cycle is either purely periodic (the first case) or eventually periodic (the second and third cases). In a purely periodic cycle, no node has two predecessors; in an eventually periodic one, such a node appears. So in general, if we can find the length of the cycle and the length of the part before entering it, we can use this property to reduce the exponent.

### Rigorous proof

This section gives a rigorous proof of the extended Euler's theorem.

??? note "Proof"
    First we show that there exists $k_0\in\mathbf N$ such that the integer $a$ is coprime to $m':=\dfrac{m}{\gcd(a^{k_0},m)}$. To see this, let $\nu_p(n)$ be the exponent of the prime $p$ in the prime factorization of the integer $n$, and take
    
    $$
    k_0 = \max\left\{\left\lceil\dfrac{\nu_p(m)}{\nu_p(a)}\right\rceil : \nu_p(a)>0\right\}.
    $$
    
    Since the full powers of all prime factors that $m$ shares with $a$ are already contained in $a^{k_0}$, $a$ is coprime to the remaining factor $m'=\dfrac{m}{\gcd(a^{k_0},m)}$ of $m$.
    
    Now, for $k\ge k_0$, consider the congruence
    
    $$
    b\equiv a^k. \pmod m
    $$
    
    Since $\gcd(a^{k_0},m)=\gcd(a^k,m)\mid b$, dividing both sides (and the modulus) by $\gcd(a^{k_0},m)$ gives
    
    $$
    \dfrac{b}{\gcd(a^{k_0},m)} \equiv \dfrac{a^{k_0}}{\gcd(a^{k_0},m)}\cdot a^{k-k_0}. \pmod{m'}
    $$
    
    Now $a$ is coprime to the modulus $m'$, so we can apply Euler's theorem directly and get
    
    $$
    \dfrac{b}{\gcd(a^{k_0},m)} \equiv \dfrac{a^{k_0}}{\gcd(a^{k_0},m)}\cdot a^{(k-k_0)\bmod\varphi(m')}. \pmod{m'}
    $$
    
    Multiplying the factor $\gcd(a^{k_0},m)$ back in gives
    
    $$
    b \equiv a^{k_0}\cdot a^{(k-k_0)\bmod\varphi(m')} = a^{k_0 + (k-k_0)\bmod\varphi(m')}. \pmod{m}
    $$
    
    This is the form of the extended Euler's theorem. The formula shows that the cycle has length $\varphi(m')$, and the part before entering the cycle has length $k_0$.
    
    The parameters obtained here are tighter than those in the extended Euler's theorem, but they are relatively hard to compute. We can show that they can be relaxed to those in the extended Euler's theorem. First, by the [formula for Euler's totient function](./euler-totient.md), since $m'\mid m$, we have $\varphi(m')\mid\varphi(m)$. That is, $\varphi(m)$ is also a period. Second, $k_0$ can be relaxed to $\varphi(m)$, because for all $m\in\mathbf N_+$ and any $p\mid m$,
    
    $$
    \begin{aligned}
    \varphi(m) &\ge \varphi(p^{\nu_p(m)}) = (p-1)p^{\nu_p(m)-1} \ge p^{\nu_p(m)-1} \\
    &= (1+(p-1))^{\nu_p(m)-1} \ge 1 + (p-1)(\nu_p(m)-1) \\
    &\ge 1 + (\nu_p(m)-1) = \nu_p(m).
    \end{aligned}
    $$
    
    The inequality in the second line uses the binomial expansion, keeping only the constant and linear terms. Therefore,
    
    $$
    k_0 \le \max\{\nu_p(m):p\in\mathbf P\}\le \varphi(m).
    $$
    
    This completes the proof.

## Example problem

This section shows a classic application of the extended Euler's theorem through an example problem: computing power towers modulo any number. A **power tower** is an expression of the form $A\uparrow(B\uparrow(C\uparrow(D\uparrow\cdots)))$, where $\uparrow$ is Knuth's up-arrow notation and $A,B,C,D,\cdots$ are nonnegative integers.

???+ example "[Library Checker - Tetration Mod](https://judge.yosupo.jp/problem/tetration_mod)"
    There are $T$ test cases. In each, given $A,B,M$, find $(A\uparrow\uparrow B)\bmod M$. Here $A\uparrow\uparrow B$ is a power tower of $B$ copies of $A$. Formally, define
    
    $$
    A \uparrow\uparrow B =
    \begin{cases}
    1 , & B = 0,\\
    A\uparrow(A\uparrow\uparrow(B-1)), & B > 0.
    \end{cases}
    $$
    
    By convention, $0^0=1$.

??? note "Solution"
    Compute recursively using the definition of $A\uparrow\uparrow B$. To compute $(A\uparrow\uparrow B)\bmod M$, apply the extended Euler's theorem, which only needs $(A\uparrow\uparrow(B-1))\bmod\varphi(M)$. Since $\varphi(\varphi(n)) \le n/2$ for all $n\ge 2$, the recursion finishes within $O(\log M)$ steps. Because we apply the extended Euler's theorem, we need to know whether the current result is strictly less than the current modulus. For this, just add one extra check when taking the remainder. Also, take care with edge cases.

??? note "Reference code"
    ```cpp
    --8<-- "docs/math/code/fermat/tetration.cpp"
    ```

??? warning "Proof that the modulo trick is correct"
    This implementation uses
    
    $$
    r_m(v) = \begin{cases} v\bmod m, &\text{if }v < m, \\ v \bmod m + m, &\text{if }v \ge m\end{cases}
    $$
    
    instead of taking the plain remainder. This records both the remainder $v\bmod m$ and the overflow flag $v \ge m$. The extended Euler's theorem only says that when both the remainder and the overflow flag of the exponent are correct, exponentiation gives the correct remainder; it does not guarantee that the overflow flag is correct. For example, when computing $r_6(2^4)$, the exponent is reduced modulo $\varphi(6)=2$, and $r_2(4)=2$ (that is, remainder $0$ with overflow). Exponentiating then gives $r_6(2^2) = 4$. Compared with the correct answer $r_6(2^4) = 10$, the remainder modulo $6$ is right, but the overflow flag is lost. However, we can prove that even though the overflow flag may be lost, the remainder is always correct. So exponentiation based on this modulo trick is always correct.
    
    Consider the iterations of the algorithm. Going back out from the innermost level, suppose the first wrong overflow flag appears when computing $r_m(a^k)$. When $k<\varphi(m)$, the exponent is exact and nothing goes wrong, so assume $k\ge\varphi(m)$. Then $k\ge k\bmod\varphi(m)+\varphi(m)$; that is, the reduction can only underestimate the exponent, and an overflow flag cannot appear out of nowhere. The only possible error is a missing overflow flag that should have been set, that is,
    
    $$
    a^{k\bmod\varphi(m)+\varphi(m)} < m \le a^{k}.
    $$
    
    This inequality can only hold when $a \ge 2$, so the left-hand side is at least $2^{\varphi(m)}$. But $2^{\varphi(m)} < m$ only happens for $m = 6$.[^phi-ineq] Substituting, we get $a^{k\bmod 2 + 2} < 6 \le a^{k}$. On the left-hand side, if $k$ is even, the exponent is $2$, so $a = 2$ and $k \ge 4$; if $k$ is odd, the exponent is $3$, and there is no solution. In summary, the overflow flag is lost only when $m=6$, $a=2$, and $k\ge 4$ is even.
    
    Next we show that losing the overflow flag in this case does not affect later computation. We only consider the nontrivial case $a_i\ge 2$ (when $a_i\le 1$, the power is at most $1$ and never overflows). The inner modulus is $6$, so the modulus $m_1$ one level out satisfies $\varphi(m_1)=6$, which means it is one of $7,9,14,18$. At that level we need $r_{m_1}(a_1^{k_1})$, where $k_1$ should be $10$ but is actually $4$. But for all $a_1$ and these $m_1$, $a_1^{4}\equiv a_1^{10}\pmod {m_1}$. To see this, recall from the [proof](#rigorous-proof) of the extended Euler's theorem above: for any $a$ and $m$, the length $k_0$ before the remainders $a^k\bmod m$ enter the cycle is at most $\nu_+(m):=\max\{\nu_p(m) : p\mid m\}$, and the cycle length divides $\varphi(m)$. Since $\nu_+(m_1)\le 2$, $k_1=4$ is already in the cycle, and it differs from $10$ by $\varphi(m_1)=6$, so the congruence always holds. So the remainder is correct. Now look at the overflow flag. Since the true inner value is $2^k\ge 16>10$, we have $a_1^{2^k}\ge a_1^{10}\ge m_1$, so this level should always be flagged as overflowing. But this level only reports whether $a_1^4$ overflows; the only possible error is $a_1^4<m_1$, which forces $a_1=2,~m_1=18$. In all other cases the overflow flag is set correctly, and going further out is naturally correct. When $a_1=2,~m_1=18$, the value should be $34$ but $16$ is returned, so we go out one more level, where $m_2$ must be one of $19,27,38,54$. Here we always have $\nu_+(m_2)\le 3 < 16$ and $34-16=\varphi(m_2)$, so the remainder is correct; and $a_2^{16}\ge m_2$ always holds, so the overflow flag is correct too. So the result here is correct, and every level further out is correct as well.
    
    Since the moduli strictly decrease from level to level, $m=6$ appears at most once. In summary, when this modulo trick is used to compute nested powers, the remainder at every level is correct, and at most two levels have a wrong overflow flag. Note that the proof does not assume that every level has the same base, so the conclusion also holds when the bases differ.

## Exercises

-   [Luogu P5091 [Template] Extended Euler's Theorem](https://www.luogu.com.cn/problem/P5091)
-   [Codeforces 906 D. Power Tower](https://codeforces.com/problemset/problem/906/D)
-   [Luogu P3747 \[Six-Province Joint Exam 2017\] Meeting Is a Greeting](https://www.luogu.com.cn/problem/P3747)
-   [Luogu P4139 God and the Correct Use of Sets](https://www.luogu.com.cn/problem/P4139)
-   [Luogu P3934 \[Ynoi Easy Round 2016\] Jabberwock I](https://www.luogu.com.cn/problem/P3934)
-   [Luogu P6736 "Wdsr-2" Hakutaku Education](https://www.luogu.com.cn/problem/P6736)

## References and notes

-   [Fermat's little theorem - Wikipedia](https://en.wikipedia.org/wiki/Fermat%27s_little_theorem)
-   [Euler's theorem - Wikipedia](https://en.wikipedia.org/wiki/Euler%27s_theorem)
-   Hardy, Godfrey Harold, and Edward Maitland Wright. An introduction to the theory of numbers. Oxford university press, 1979.

[^ex-euler]: This name is mainly used in the competitive programming community; it is not a standard name for the result.

[^phi-ineq]: According to Kendall, R. and Osborn, R. (1965) Two Simple Lower Bounds for the Euler ϕ-Function. Texas Journal of Science, 17, 324-326, $\varphi(m)\ge\sqrt{m}$ for all $m > 6$. Direct computation shows that $\sqrt{m}\ge\log_2m$ for $m\ge 16$. So the inequality $\varphi(m)\ge\log_2m$ holds for all $m\ge 16$. The remaining cases can be checked one by one.
