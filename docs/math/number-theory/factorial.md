author: aofall, c-forrest, CoelacanthusHex, Early0v0, Enter-tainer, Great-designer, iamtwz, Marcythm, Persdre, shuzhouliu, Tiphereth-A, wsyhb, Xeonacid

## Introduction

This page discusses results about computing factorials modulo a number, and gives a method whose time complexity is linear in the size of the modulus. So the method is mainly suited to moduli that are not too large ($\sim 10^6$). Besides the method on this page, depending on the situation, [polynomial techniques](../poly/shift.md#factorial-modulo-a-prime) can also be used for fast computation.

By the [Chinese remainder theorem](./crt.md), computing factorials modulo a number reduces to the case where the modulus is a prime power $p^\alpha$. For such problems, given a prime $p$ and a positive integer $n$, we often need to pull all factors of $p$ out of $n!$, giving the decomposition:

$$
n! = p^{\nu_p(n!)}(n!)_p.
$$

Here $\nu_p(n!)$ is the exponent of $p$ in the prime factorization of $n!$, and $(n!)_p$ is the integer obtained from $n!$ by removing all powers of $p$. This page discusses how to compute the remainder of $(n!)_p$ modulo a prime (power), and how to compute the exponent $\nu_p(n!)$.

This decomposition is especially useful when factorials appear in both the numerator and the denominator, for example when [computing binomial coefficients modulo a number](./lucas.md). In such problems, the powers of $p$ in the numerator and denominator can simply be subtracted, and the part coprime to $p$, $(n!)_p$, can be handled with [modular inverses](./inverse.md).

This page also covers related results: Wilson's theorem and its generalization, Legendre's formula, and Kummer's theorem.

## Wilson's theorem

Wilson's theorem gives a necessary and sufficient condition for a natural number to be prime.

???+ note "Wilson's theorem"
    For a natural number $n>1$, $(n-1)!\equiv -1\pmod n$ if and only if $n$ is prime.

??? note "Proof"
    First, we show that $(p-1)!\equiv -1\pmod{p}$ for a prime $p$. There are two short proofs of this using [congruence equations](./congruence-equation.md#congruence-equations-modulo-primes) or [primitive roots](./primitive-root.md), which we omit here. Below is a proof that needs less background:
    
    The claim is clear for $p=2$. Now let $p\geq 3$. We need to show that the product of all nonzero elements (i.e., residue classes) of $\mathbf{Z}_p$ is $\overline{-1}$. Every nonzero element $\overline{a}$ of $\mathbf{Z}_p$ has an inverse $\overline{a}^{-1}$, so the product of each pair of mutually inverse elements is $\overline{1}$. But note that $\overline{a}$ and $\overline{a}^{-1}$ may be equal: $\overline{a}=\overline{a}^{-1}$ if and only if $a^2\equiv 1\pmod p$, that is,
    
    $$
    0\equiv a^2-1\equiv (a+1)(a-1)\pmod p,
    $$
    
    so $a\equiv 1\pmod p$ or $a\equiv -1\pmod p$. This shows that the product of all elements of $\mathbf{Z}_p\setminus\{\overline{0},\overline{1},\overline{-1}\}$ is $\overline{1}$, so the product of all nonzero elements of $\mathbf{Z}_p$ is $\overline{-1}$.
    
    Conversely, for composite $n$, we need to show $(n-1)!\not\equiv-1\pmod{n}$. Suppose for contradiction that $(n-1)!\equiv -1\pmod{n}$, i.e., there is an integer $k$ with $(n-1)!=kn-1$. Since $n$ is composite, there is a prime $p<n$ with $n=pm$, so $(n-1)!=kpm-1\equiv -1\pmod{p}$. But $p$ already appears in the product $(n-1)!$, so $(n-1)!\equiv 0\pmod{p}$. This contradiction shows $(n-1)!\not\equiv-1\pmod{n}$.

In the notation of this page, Wilson's theorem can be written as $(p!)_p\equiv -1\pmod{p}$.

### Generalization

Wilson's theorem can be generalized to arbitrary moduli.

???+ note "Theorem (Gauss)"
    For a natural number $m>1$,
    
    $$
    \prod_{1\le k<m,\ k\perp m} k \equiv \pm 1 \pmod{m}.
    $$
    
    Moreover, the remainder is $-1$ if and only if a [primitive root exists](./primitive-root.md#existence-theorem-for-primitive-roots) modulo $m$, that is, when $m=2,4,p^\alpha,2p^\alpha$, where $p$ is an odd prime and $\alpha$ is a positive integer.

??? note "Proof"
    This theorem can be proved easily using the structure of the [multiplicative group of integers modulo $m$](../algebra/ring-theory.md#application-the-multiplicative-group-of-integers-modulo-n). Here we give a more elementary proof along similar lines.
    
    For $m=2$, $1!=1\equiv -1\pmod{2}$. For the other cases where a primitive root exists, let $g$ be a primitive root. Then every positive integer $k$ less than $m$ and coprime to $m$ can be written uniquely as $g^i\bmod m$, where $0\le i<\varphi(m)$ and $\varphi(m)$ is [Euler's totient function](./euler-totient.md). A direct check shows that $\varphi(m)$ is always even. Since $g^i$ and $g^{\varphi(m)-i}$ are multiplicative inverses of each other, pairing them up in the product gives
    
    $$
    \prod_{1\le k<m,\ k\perp m} k \equiv \prod_{i=0}^{\varphi(m)-1}g^i = g^{\varphi(m)/2}\prod_{i=1}^{\varphi(m)/2-1}g^{i}g^{\varphi(m)-i} \equiv g^{\varphi(m)/2} \pmod{m}.
    $$
    
    Since $g^{\varphi(m)/2}\bmod m$ is the only element other than $1\bmod{m}$ that is its own multiplicative inverse, it equals $-1\bmod{m}$. So in this case the remainder is $-1$.
    
    When no primitive root exists modulo $m$, we need to show the remainder is $1$. First, factor $m=p_1^{e_1}p_2^{e_2}\cdots p_s^{e_s}$. By the [Chinese remainder theorem](./crt.md), it suffices to show that
    
    $$
    \prod_{1\le k<m,\ k\perp m} k\equiv 1\pmod{p_j^{e_j}}
    $$
    
    for every factor $p_j^{e_j}$. The Chinese remainder theorem says that each possible combination of remainders $(r_1,r_2,\cdots,r_s)$, with $1\le r_j<p_j^{e_j}$ and $p_j\perp r_j$, corresponds to exactly one $k$ with $1\le k<m$, $k\perp m$ and $k\equiv r_j\pmod{p_j^{e_j}}$. So for each remainder $r_j$, there are exactly ${\varphi(m)}/{\varphi(p_j^{e_j})}$ values of $k$ with $k\equiv r_j\pmod{p_j^{e_j}}$. Grouping the product accordingly gives
    
    $$
    \prod_{1\le k<m,\ k\perp m} k\equiv\left(\prod_{1\le r_j<p_j^{e_j},\ r_j\perp p_j} r_j\right)^{{\varphi(m)}/{\varphi(p_j^{e_j})}}\pmod{p_j^{e_j}}.
    $$
    
    For the exponent ${\varphi(m)}/{\varphi(p_j^{e_j})}=\varphi(m/p_j^{e_j})$ to be odd, we would need $m/p_j^{e_j}=1,2$, because Euler's totient $\varphi(n)$ is even for all $n\ge 3$. If $p_j$ is an odd prime, then since no primitive root exists modulo $m$, we must have $m/p_j^{e_j}\neq 1,2$. If $p_j^{e_j}=2,4$, then since no primitive root exists modulo $m$, $m/p_j^{e_j}$ must have some odd prime factor, so it is greater than $2$. In both cases the exponent ${\varphi(m)}/{\varphi(p_j^{e_j})}$ is even. We have already shown that the term in parentheses is $-1$ modulo $p_j^{e_j}$, so this power is $1$ modulo $p_j^{e_j}$. The only remaining case is $p_j=2$ with $e_j>2$. For this case, we can show directly that
    
    $$
    \prod_{1\le r_j<2^{e_j},\ r_j\perp 2}r_j \equiv 1\pmod{2^{e_j}}.
    $$
    
    Following the earlier proof, we can pair up and cancel the odd numbers $r_j$ with $1\le r_j<2^{e_j}$. The ones that cannot be paired must be solutions of $x^2\equiv 1\pmod{2^{e_j}}$. This equation means $2^{e_j}\mid (x-1)(x+1)$. Writing $x=2y+1$, we get $2^{e_j-2}\mid y(y+1)$. One of $y$ and $y+1$ is odd and the other even, so $y=t2^{e_j-2}$ or $y=t2^{e_j-2}-1$. Hence $x=t2^{e_j-1}\pm 1$ for some integer $t$. Modulo $2^{e_j}$, these give only four remainders: $\pm 1$ and $2^{e_j-1}\pm 1$. Therefore,
    
    $$
    \prod_{1\le r_j<2^{e_j},\ r_j\perp 2}r_j \equiv (-1)(2^{e_j-1}-1)(2^{e_j-1}+1) \equiv 1\pmod{2^{e_j}}.
    $$
    
    This completes the proof for all cases.

For computation, the most important case is when the modulus is a prime power:

???+ note "Corollary"
    For a prime $p$ and a positive integer $\alpha$,
    
    $$
    \prod_{1\le k<p^\alpha,\ k\perp p}k \equiv 
    \begin{cases}
    1, & p=2\text{ and }\alpha\ge3,\\
    -1, &\text{otherwise}
    \end{cases}
    \pmod{p^\alpha}.
    $$

Note that the left-hand side is not $(p^\alpha!)_p$, since the latter also includes the contribution of the multiples of $p$.

## Computing the remainder of a factorial

This section discusses how to compute $(n!)_p\bmod p^{\alpha}$.

### Prime modulus

The expression $(n!)_p$ has a clear recursive structure. To see this, first look at a concrete example:

???+ example "Example"
    To compute $(32!)_5 \bmod{5}$, we can proceed recursively as follows:
    
    $$
    \begin{aligned}
    (32!)_5 &= 1\times 2\times 3 \times 4\times \underbrace{1}_{5}\times 6 \times 7 \times 8\times 9 \times \underbrace{2}_{10} \\
    &\quad\times 11 \times 12 \times 13 \times 14\times \underbrace{3}_{15}\times 16 \times 17\times 18\times 19\times \underbrace{4}_{20} \\
    &\quad\times 21 \times 22 \times 23 \times 24\times \underbrace{1}_{25}\times 26 \times 27\times 28\times 29\times \underbrace{6}_{30} \times 31 \times 32 \\
    &\equiv 1\times 2\times 3 \times 4\times \underbrace{1}_{5}\times 1 \times 2 \times 3\times 4 \times \underbrace{2}_{10} \\
    &\quad\times 1 \times 2 \times 3 \times 4\times \underbrace{3}_{15}\times 1 \times 2\times 3\times 4\times \underbrace{4}_{20} \\
    &\quad\times 1 \times 2 \times 3 \times 4\times \underbrace{1}_{25}\times 1 \times 2\times 3\times 4\times \underbrace{1}_{30}\times 1\times 2\\
    &= (1\times 2\times 3\times 4)^{6}\times(1\times 2)\times(\underbrace{1}_{5}\times \underbrace{2}_{10}\times \underbrace{3}_{15} \times \underbrace{4}_{20}\times \underbrace{1}_{25}\times \underbrace{1}_{30}) \pmod{5}
    \end{aligned}
    $$
    
    Because remainders modulo $5$ are periodic, the product can be split into blocks of length $5$, and the only difference between blocks is the remainder of the last element. Since $32$ divided by $5$ gives quotient $6$ and remainder $2$, the product splits into $6$ complete blocks and a final incomplete block of length $2$. So we can take the parts of the first $6$ blocks other than their last elements (exactly what Wilson's theorem handles), multiply by the product of the final incomplete block, and finally multiply by the product of the last elements of the first $6$ blocks. The last element of each block is a multiple of $5$; after removing the powers of $5$, their product is exactly $(6!)_{5}\pmod{5}$. This turns the original problem into a smaller one.

Generalizing the recursive structure in this example gives the following recurrence:

???+ note "Recurrence"
    For a prime $p$ and a positive integer $n$,
    
    $$
    (n!)_p \equiv (-1)^{\left\lfloor n/p\right\rfloor}\cdot (n\bmod p)!\cdot\left(\left\lfloor n/p\right\rfloor!\right)_p\pmod{p}.
    $$

??? note "Proof"
    Let $(n)_p$ be $n$ with all powers of $p$ removed from its prime factorization. Then
    
    $$
    \begin{aligned}
    (n!)_p &= \prod_{k=1}^n(k)_p = \left(\prod_{1\le k\le n,\ k\perp p}(k)_p\right)\left(\prod_{1\le k\le\lfloor n/p\rfloor}(pk)_p\right) \\
    &= \left(\prod_{i=0}^{\lfloor n/p\rfloor-1}\prod_{j=1}^{p-1}(ip+j)\right)\left(\prod_{j=1}^{n\bmod p}(\lfloor n/p\rfloor p+j)\right)\left(\prod_{1\le k\le\lfloor n/p\rfloor}(k)_p\right) \\
    &\equiv\left(\prod_{j=1}^{p-1}j\right)^{\lfloor n/p\rfloor}\left(\prod_{j=1}^{n\bmod p}j\right)(\lfloor n/p\rfloor!)_p \\
    &\equiv (-1)^{\lfloor n/p\rfloor}\cdot(n\bmod p)!\cdot(\lfloor n/p\rfloor!)_p \pmod p.
    \end{aligned}
    $$
    
    This completes the proof. Below is a more concrete explanation of this formal proof.
    
    We want $(n!)_p\bmod p$. Following the example above,
    
    $$
    \begin{aligned}
    (n!)_p &= 1 \cdot 2 \cdot 3 \cdot \ldots \cdot (p-2) \cdot (p-1) \cdot \underbrace{1}_{p} \cdot (p+1) \cdot (p+2) \cdot \ldots \cdot (2p-1) \cdot \underbrace{2}_{2p} \\
    &\quad \cdot (2p+1) \cdot \ldots \cdot (p^2-1) \cdot \underbrace{1}_{p^2} \cdot (p^2 +1) \cdot \ldots \cdot n \\
    &\equiv 1 \cdot 2 \cdot 3 \cdot \ldots \cdot (p-2) \cdot (p-1) \cdot \underbrace{1}_{p} \cdot 1 \cdot 2 \cdot \ldots \cdot (p-1) \cdot \underbrace{2}_{2p} \cdot 1 \cdot 2 \\
    &\quad \cdot \ldots \cdot (p-1) \cdot \underbrace{1}_{p^2} \cdot 1 \cdot 2 \cdot \ldots \cdot (n \bmod p) \pmod{p}.
    \end{aligned}
    $$
    
    We can clearly see that, apart from the last block, the factorial is split into several complete blocks of the same length.
    
    $$
    \begin{aligned}
    (n!)_p&\equiv \underbrace{1 \cdot 2 \cdot 3 \cdot \ldots \cdot (p-2) \cdot (p-1) \cdot 1}_{1\text{st}} \cdot \underbrace{1 \cdot 2 \cdot 3 \cdot \ldots \cdot (p-2) \cdot (p-1) \cdot 2}_{2\text{nd}} \cdot \ldots \\
    &\quad \cdot \underbrace{1 \cdot 2 \cdot 3 \cdot \ldots \cdot (p-2) \cdot (p-1) \cdot 1}_{p\text{th}} \cdot \ldots \cdot \quad \underbrace{1 \cdot 2 \cdot \ldots \cdot (n \bmod p)}_{\text{tail}} \pmod{p}.
    \end{aligned}
    $$
    
    Apart from the last element of each block, the main part of a complete block, $(p-1)!\bmod p$, is easy to compute with Wilson's theorem:
    
    $$
    (p-1)!\equiv -1\pmod p.
    $$
    
    There are $\left\lfloor \dfrac{n}{p} \right\rfloor$ complete blocks in total, so $-1$ is raised to the power $\left\lfloor \dfrac{n}{p} \right\rfloor$.
    
    The value of the last partial block is $(n\bmod p)!\bmod p$, which can be computed separately.
    
    What is left are the last elements of the blocks. Hiding the elements already handled, we see this pattern:
    
    $$
    (n!)_p = \underbrace{ \ldots \cdot 1 } \cdot \underbrace{ \ldots \cdot 2} \cdot \ldots \cdot \underbrace{ \ldots \cdot (p-1)} \cdot \underbrace{ \ldots \cdot 1 } \cdot \underbrace{ \ldots \cdot 1} \cdot \underbrace{ \ldots \cdot 2} \cdots
    $$
    
    This is again a modified factorial, just much shorter. It is:
    
    $$
    \left(\left\lfloor \frac{n}{p} \right\rfloor !\right)_p.
    $$
    
    Multiplying the parts together gives the recurrence above.

Computing with this recurrence, the recursion depth is $O(\log_p n)$. If the middle term is recomputed every time, each level costs $O(p)$, and the total time complexity is $O(p\log_p n)$. If $n!\bmod p$ is precomputed for all $n=1,2,\cdots,p-1$, the precomputation costs $O(p)$, each level costs $O(1)$, and the total time complexity is $O(p+\log_p n)$.

Since this is tail recursion, it can be implemented iteratively. The implementation below precomputes the first $p-1$ factorials. If the function is called many times, the precomputation can be moved outside the function.

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/factorial/fact-mod-p.cpp:core"
    ```

If memory is limited and you cannot store all the factorials, you can instead compute every $n$ for which $n!\bmod p$ is actually used in the calls, sort them, and then compute all of these factorials in one pass at the end and combine them into the final result. This avoids storing every factorial.

### Prime power modulus

The prime power case can be solved the same way as the prime case; we just replace Wilson's theorem with its generalization. In both results of this section, $\pm 1$ has a specific meaning: it is $1$ when $p=2$ and $\alpha\ge 3$, and $-1$ otherwise.

???+ note "Recurrence"
    For a prime $p$ and positive integers $\alpha,n$,
    
    $$
    (n!)_{p} \equiv (\pm 1)^{\lfloor n/p^\alpha\rfloor}\cdot\left(\prod_{1\le j\le (n\bmod p^\alpha),\ j\perp p}j\right)\cdot(\lfloor n/p\rfloor!)_p\pmod{p^\alpha}.
    $$
    
    Here $\pm 1$ is as specified in the [generalization of Wilson's theorem](#generalization).

??? note "Proof"
    The proof is exactly like the prime case. Let $(k)_p$ be $k$ with all powers of $p$ removed from its prime factorization. Then
    
    $$
    \begin{aligned}
    (n!)_p
    &= \prod_{1\le k\le n}(k)_p = \left(\prod_{1\le k\le n,\ k\perp p}(k)_p\right)\left(\prod_{1\le k\le\lfloor n/p\rfloor}(pk)_p\right) \\
    &= \left(\prod_{i=0}^{\lfloor n/p^\alpha\rfloor-1}\prod_{1\le j\le p^\alpha,\ j\perp p}(ip^\alpha+j)_p\right)\left(\prod_{1\le j\le (n\bmod p^\alpha),\ j\perp p}(\lfloor n/p^\alpha\rfloor p^\alpha+j)_p\right)\left(\prod_{1\le k\le\lfloor n/p\rfloor}(k)_p\right)\\
    &\equiv \left(\prod_{1\le j\le p^\alpha,\ j\perp p}j\right)^{\lfloor n/p^\alpha\rfloor}\cdot\left(\prod_{1\le j\le (n\bmod p^\alpha),\ j\perp p}j\right)\cdot(\lfloor n/p\rfloor!)_p\\
    &\equiv (\pm 1)^{\lfloor n/p^\alpha\rfloor}\cdot\left(\prod_{1\le j\le (n\bmod p^\alpha),\ j\perp p}j\right)\cdot(\lfloor n/p\rfloor!)_p \pmod{p^\alpha}.
    \end{aligned}
    $$

Compared with the prime case, besides possibly replacing $-1$ with $\pm 1$, the precomputed data is also different. For a prime power modulus, for every positive integer $n$ up to $p^\alpha$ we precompute the product of all integers from $1$ to $n$ that are not multiples of $p$, that is,

$$
\prod_{1\le k\le n,\ k\perp p} k\bmod{p^\alpha}.
$$

In the prime case, for $n<p$ this reduces to $n!\bmod p$, but that no longer holds for a general prime power.

Here is an example of computing a factorial remainder modulo a prime power, to help understand the method:

???+ example "Example"
    To compute $(32!)_3\bmod 9$, we can proceed recursively as follows:
    
    $$
    \begin{aligned}
    (32!)_3 
    &= 1\times 2\times \underbrace{1}_{3} \times 4\times 5\times \underbrace{2}_{6}\times 7\times 8\times\underbrace{1}_{9}\\
    &\quad\times 10\times 11\times\underbrace{4}_{12}\times 13\times 14\times\underbrace{5}_{15}\times 16\times 17\times\underbrace{2}_{18}\\
    &\quad\times 19\times 20\times\underbrace{7}_{21}\times 22\times 23\times\underbrace{8}_{24}\times 25\times 26\times\underbrace{1}_{27}\\
    &\quad\times 28\times 29\times\underbrace{10}_{30}\times 31\times 32\\
    &\equiv 1\times 2\times \underbrace{1}_{3} \times 4\times 5\times \underbrace{2}_{6}\times 7\times 8\times\underbrace{1}_{9}\\
    &\quad\times 1\times 2\times\underbrace{4}_{12}\times 4\times 5\times\underbrace{5}_{15}\times 7\times 8\times\underbrace{2}_{18}\\
    &\quad\times 1\times 2\times\underbrace{7}_{21}\times 4\times 5\times\underbrace{8}_{24}\times 7\times 8\times\underbrace{1}_{27}\\
    &\quad\times 1\times 2\times\underbrace{1}_{30}\times 4\times 5\\
    &=(1\times 2\times 4\times 5\times 7\times 8)^{3}\times (1\times 2\times 4\times 5)\\
    &\quad\times\begin{pmatrix}\underbrace{1}_{3}\times\underbrace{2}_{6}\times\underbrace{1}_{9}\times\underbrace{4}_{12}\times\underbrace{5}_{15}\times\underbrace{2}_{18}\\\times\underbrace{7}_{21}\times\underbrace{8}_{24}\times\underbrace{1}_{27}\times\underbrace{1}_{30}\end{pmatrix}\pmod{9}.
    \end{aligned}
    $$
    
    The decomposition of $(32!)_3\bmod 9$ also splits into three parts:
    
    -   Complete blocks: the product of all integers from $1$ to $9$ not divisible by $3$; there are $\lfloor 32/9\rfloor=3$ such blocks;
    -   The incomplete block at the end: the product of all integers not divisible by $3$ from $1$ up to $32\bmod 9$;
    -   The product of all integers divisible by $3$. Comparing with the result before the second-to-last equals sign, this is exactly its first $\lfloor 32/3\rfloor=10$ terms, i.e., $(\lfloor 32/3\rfloor!)_3\bmod 9$.
    
    The part in the last parentheses is solved recursively, which turns the original problem into a smaller one.

This gives the following result:

???+ note "Result of the recurrence"
    For a prime $p$ and positive integers $\alpha,n$,
    
    $$
    (n!)_p \equiv (\pm 1)^{\sum_{j\ge\alpha}\lfloor{n}/{p^j}\rfloor}\prod_{j\ge 0}F(\lfloor n/p^j\rfloor\bmod p^\alpha)\pmod{p^\alpha},
    $$
    
    where $F(m) = \prod_{1\le k\le m,\ k\perp p} k\bmod{p^\alpha}$ and $\pm 1$ is as defined above.

The implementation for a prime power modulus is similar to the prime case, with only a few differences in the details. As before, the precomputation can be moved outside the function.

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/factorial/fact-mod-pa.cpp:core"
    ```

The precomputation takes $O(p^\alpha)$ time, and each query takes $O(\log_p n)$ time.

## Computing the exponent

This section discusses how to compute the exponent $\nu_p(n!)$ of $p$ in $n!$. It can be used to compute binomial coefficients modulo a number: factorials appear in both the numerator and denominator of a binomial coefficient, and whether the factors of a prime $p$ cancel out between them is a key factor in the final remainder.

### Legendre's formula

The exponent of a prime $p$ in $n!$ can be computed with Legendre's formula, and it is related to the base-$p$ representation of $n$.

???+ note "Legendre's formula"
    For a positive integer $n$, the exponent $\nu_p(n!)$ of a prime $p$ in $n!$ is
    
    $$
    \nu_p(n!) = \sum_{i=1}^{\infty} \left\lfloor \dfrac{n}{p^i} \right\rfloor = \dfrac{n-S_p(n)}{p-1},
    $$
    
    where $S_p(n)$ is the sum of the digits of $n$ in base $p$. In particular, the exponent of $2$ in a factorial is $\nu_2(n!)=n-S_2(n)$.

??? note "Proof"
    We have
    
    $$
    n! = 1\times 2\times \cdots \times p\times \cdots \times 2p\times \cdots \times \lfloor n/p\rfloor p\times \cdots \times n.
    $$
    
    The product of the multiples of $p$ is $p\times 2p\times \cdots \times \lfloor n/p\rfloor p=p^{\lfloor n/p\rfloor }\lfloor n/p\rfloor !$, and $\lfloor n/p\rfloor !$ may contain further multiples of $p$. So the exponent satisfies the recurrence:
    
    $$
    \nu_p(n!) = \lfloor n/p\rfloor + \nu_p(\lfloor n/p\rfloor!).
    $$
    
    Expanding it gives Legendre's formula.
    
    To prove the second equality, first write $n$ in base $p$, i.e., as the sum:
    
    $$
    n = n_\ell p^{\ell} + \cdots + n_1 p + n_0 = \sum_{k=0}^\ell n_kp^k.
    $$
    
    Then
    
    $$
    \begin{aligned}
    \nu_p(n!)
    &= \sum_{i=1}^{\ell}\left\lfloor\dfrac{n}{p^i}\right\rfloor 
    = \sum_{i=1}^\ell\sum_{k=i}^{\ell}n_kp^{k-i}
    = \sum_{k=1}^\ell n_k\sum_{i=1}^kp^{k-i} \\
    &= \sum_{k=1}^\ell n_k\dfrac{p^k-1}{p-1} 
    = \dfrac{\sum_{k=0}^\ell n_kp^k - \sum_{k=0}^\ell n_k}{p-1} 
    = \dfrac{n - S_p(n)}{p-1}.
    \end{aligned}
    $$

A reference implementation for the exponent of a prime in a factorial:

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/factorial/multiplicity.cpp:core"
    ```

Its time complexity is $O(\log n)$.

### Kummer's theorem

Binomial coefficients modulo a number often form fractal patterns. For example, the Sierpiński triangle can be obtained from binomial coefficients modulo $2$.

On closer analysis, whether $p$ divides a binomial coefficient depends on whether subtracting the lower index from the upper index in base $p$ needs borrowing. This leads to **Kummer's theorem**.

???+ note "Kummer's theorem"
    The exponent of a prime $p$ in the binomial coefficient $\dbinom{m}{n}$ is exactly the number of borrows when subtracting $n$ from $m$ in base $p$, i.e.,
    
    $$
    \nu_p\left(\dbinom{m}{n}\right)=\frac{S_p(n)+S_p(m-n)-S_p(m)}{p-1}.
    $$
    
    In particular, the exponent of $2$ in a binomial coefficient is $\nu_2\left(\dbinom{m}{n}\right)=S_2(n)+S_2(m-n)-S_2(m)$.

??? note "Proof"
    First we prove the formula. By Legendre's formula,
    
    $$
    \begin{aligned}
    \nu_p\left(\dbinom{m}{n}\right)
    &=\nu_p(m!)-\nu_p(n!)-\nu_p((m-n)!)\\
    &=\sum_{i=1}^\infty\left(\left\lfloor\dfrac{m}{p^i}\right\rfloor-\left\lfloor\dfrac{n}{p^i}\right\rfloor-\left\lfloor\dfrac{m-n}{p^i}\right\rfloor\right)\\
    &=\frac{S_p(n)+S_p(m-n)-S_p(m)}{p-1}.
    \end{aligned}
    $$
    
    This formula can be read as the number of borrows when subtracting $n$ from $m$ in base $p$. If, when computing digit $i$ (the lowest digit has index $1$), the subtraction does not fit and needs a borrow, then the digits of the result above position $i$, $\left\lfloor\dfrac{m-n}{p^i}\right\rfloor$, equal the digits of $m$ above position $i$, $\left\lfloor\dfrac{m}{p^i}\right\rfloor$, minus one (the borrowed one), minus the digits of $n$ above position $i$, $\left\lfloor\dfrac{n}{p^i}\right\rfloor$. So the difference
    
    $$
    \left\lfloor\dfrac{m}{p^i}\right\rfloor-\left\lfloor\dfrac{n}{p^i}\right\rfloor-\left\lfloor\dfrac{m-n}{p^i}\right\rfloor = 1
    $$
    
    if and only if a borrow happens; otherwise it is $0$. So the sum in the formula counts the number of borrows. This gives the verbal statement of Kummer's theorem.

## Example problems

???+ example "Example problem [HDU 2973 - YAPTCHA](https://acm.hdu.edu.cn/showproblem.php?pid=2973)"
    Given $n$, compute
    
    $$
    \sum_{k=1}^n\left\lfloor\frac{(3k+6)!+1}{3k+7}-\left\lfloor\frac{(3k+6)!}{3k+7}\right\rfloor\right\rfloor
    $$

??? note "Solution"
    If $3k+7$ is prime, then
    
    $$
    (3k+6)!\equiv-1\pmod{3k+7}
    $$
    
    Let $(3k+6)!+1=m(3k+7)$.
    
    Then
    
    $$
    \left\lfloor\frac{(3k+6)!+1}{3k+7}-\left\lfloor\frac{(3k+6)!}{3k+7}\right\rfloor\right\rfloor=\left\lfloor m-\left\lfloor m-\frac{1}{3k+7}\right\rfloor\right\rfloor=1
    $$
    
    If $3k+7$ is not prime, it is a composite number greater than $4$, so $(3k+7)\mid(3k+6)!$, that is,
    
    $$
    (3k+6)!\equiv 0\pmod{3k+7}
    $$
    
    Let $(3k+6)!=m(3k+7)$. Then
    
    $$
    \left\lfloor\frac{(3k+6)!+1}{3k+7}-\left\lfloor\frac{(3k+6)!}{3k+7}\right\rfloor\right\rfloor=\left\lfloor m+\frac{1}{3k+7}-m\right\rfloor=0
    $$
    
    Therefore
    
    $$
    \sum_{k=1}^n\left\lfloor\frac{(3k+6)!+1}{3k+7}-\left\lfloor\frac{(3k+6)!}{3k+7}\right\rfloor\right\rfloor=\sum_{k=1}^n[3k+7\text{ is prime}]
    $$

??? example "Reference code"
    ```cpp
    --8<-- "docs/math/code/factorial/wilson_1.cpp"
    ```

## References

-   Feng Keqin. *Elementary Number Theory and Its Applications* (in Chinese).
-   [Wilson's theorem - Wikipedia](https://en.wikipedia.org/wiki/Wilson%27s_theorem)
-   [Legendre's formula - Wikipedia](https://en.wikipedia.org/wiki/Legendre%27s_formula)

**This page is mainly translated from the article [Вычисление факториала по модулю](http://e-maxx.ru/algo/modular_factorial) and its English translation [Factorial modulo p](https://cp-algorithms.com/algebra/factorial-modulo.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0. The content has been modified.**
