Prerequisites: [Discrete logarithm](./discrete-logarithm.md)

This page discusses higher-power residues and roots of unity modulo $m$, and introduces algorithms for taking roots modulo $m$.

## Higher-power residues

Higher-power residues modulo $m$ are about whether we can take roots of higher degree modulo $m$. They generalize [quadratic residues](./quad-residue.md).

???+ abstract "$k$-th power residue"
    Let $k\geq 2$ be an integer, and let the integer $a$ be coprime to the positive integer $m$. If there is an integer $x$ such that
    
    $$
    x^k\equiv a\pmod m,
    $$
    
    then $a$ is called a **$k$-th power residue** ($k$-th residue) modulo $m$, and $x$ is called a **$k$-th root** of $a$ modulo $m$. Otherwise, $a$ is called a **$k$-th power non-residue** ($k$-th nonresidue) modulo $m$.

In other words, a $k$-th root of $a$ modulo $m$ exists if and only if $a$ is a $k$-th power residue modulo $m$.

### Properties

As with quadratic residues, we can ask how to test for $k$-th power residues, how many $k$-th roots there are, and how many $k$-th power residue classes there are. As with other [congruence equation](./congruence-equation.md) problems, the [Chinese remainder theorem](./crt.md) reduces them to prime power moduli. Depending on whether a primitive root exists, this further splits into odd prime power moduli and moduli that are powers of $2$.

The odd prime power case is simpler. In fact, whenever a primitive root exists, we have the following result:

???+ note "Theorem"
    Let $k\geq 2$ be an integer, and let the integer $a$ be coprime to the positive integer $m$. Suppose a primitive root modulo $m$ exists, and let $g$ be a primitive root modulo $m$. Let $d=\gcd(k,\varphi(m))$ and $d'=\dfrac{\varphi(m)}{d}$, where $\varphi(m)$ is [Euler's totient function](./euler-totient.md). Then:
    
    1.  $a$ is a $k$-th power residue modulo $m$ if and only if
    
        $$
        a^{d'} \equiv 1 \pmod m.
        $$
    2.  When $a$ is a $k$-th power residue modulo $m$, $a$ has exactly $d$ distinct $k$-th roots modulo $m$ (up to congruence), and they have the form
    
        $$
        x \equiv g^{y_0+id'}\pmod m,~0\le y_0 < d',~i=0,1,\cdots,d-1.
        $$
    3.  There are $d'$ $k$-th power residue classes modulo $m$, and they are exactly
    
        $$
        \{g^{di}\bmod m : 0 \le i < d'\}.
        $$

??? note "Proof"
    Since $a\perp m$, we have $x\perp m$. Since $g$ is a primitive root modulo $m$, both $x$ and $a$ are congruent to some power of $g$. Let $x\equiv g^y\pmod m$. Then the equation $x^k\equiv a\pmod m$ is equivalent to
    
    $$
    g^{ky} \equiv g^{\operatorname{ind}_g a}\pmod m.
    $$
    
    Here $\operatorname{ind}_g a$ is the discrete logarithm. By the [properties of the order](./primitive-root.md#cyclic-structure-of-powers) and $\delta_m(g)=\varphi(m)$, this is equivalent to the congruence
    
    $$
    ky \equiv \operatorname{ind}_g a \pmod{\varphi(m)}.
    $$
    
    This is a [linear congruence](./linear-equation.md) in $y$. Using the analysis of its solutions on that page, the equation has a solution if and only if $d\mid\operatorname{ind}_g a$, and the general solution is
    
    $$
    y \equiv y_0 + id' \pmod{\varphi(m)},~0\le y_0 < d',~i=0,1,\cdots,d-1.
    $$
    
    This gives almost everything in the theorem. The only thing left to explain is the test $a^{d'} \equiv 1 \pmod m$. By [property 3 of the order](./primitive-root.md#cyclic-structure-of-powers),
    
    $$
    \delta_m(a) = \delta_m(g^{\operatorname{ind}_g a}) = \dfrac{\varphi(m)}{\gcd(\varphi(m),\operatorname{ind}_g a)}.
    $$
    
    We also know the equation has a solution if and only if $d\mid \operatorname{ind}_g a$, that is, $\delta_m(a)\mid d'$. By [property 2 of the order](./primitive-root.md#cyclic-structure-of-powers), this is equivalent to the test.

The case where the modulus is a power of $2$ is special. To handle it, we need a [result](./primitive-root.md#recursive-formula) about the structure of the reduced residue system modulo $2^e$: every odd number $a$ is congruent to exactly one integer of the form $(-1)^s5^r\bmod 2^e$, where $s\in\{0,1\}$ and $0\le r < 2^{e-2}$. With this result we get the following:

???+ note "Theorem"
    Let $k\ge 2$ be an integer, $a$ an odd number, and $m=2^e$ a positive integer with $e \ge 2$. When $k$ is odd:
    
    1.  $a$ is always a $k$-th power residue modulo $m$.
    2.  $a$ has exactly one $k$-th root modulo $m$.
    3.  There are $2^{e-1}$ $k$-th power residue classes modulo $m$, and they are all the reduced residue classes.
    
    When $k$ is even, let $d=\gcd(k,2^{e-2})$ and $d'=\dfrac{2^{e-2}}{d}$. Then:
    
    1.  $a$ is a $k$-th power residue modulo $m$ if and only if $a\equiv 1\pmod 4$ and $a^{d'}\equiv 1\pmod m$.
    2.  When $a$ is a $k$-th power residue modulo $m$, $a$ has exactly $2d$ distinct $k$-th roots modulo $m$ (up to congruence), and they have the form
    
        $$
        x \equiv \pm 5^{y_0 + id'} \pmod{2^e},~ 0 \le y_0 < d',~i = 0, 1,\cdots,d-1. 
        $$
    3.  There are $d'$ $k$-th power residue classes modulo $m$, and they are exactly
    
        $$
        \{5^{di}\bmod m : 0 \le i < d'\}.
        $$

??? note "Proof"
    Since $a\perp m$, we have $x\perp m$. Since $x$ and $a$ are both odd, by the result above we can write $a\equiv (-1)^s5^r\pmod{2^e}$ and $x\equiv(-1)^z5^{y}\pmod{2^e}$. Since the representation is unique, the congruence $x^k\equiv a\pmod{2^e}$ is equivalent to the system of [linear congruences](./linear-equation.md)
    
    $$
    \begin{aligned}
    kz &\equiv s \pmod{2},\\
    ky &\equiv r \pmod{2^{e-2}}.
    \end{aligned}
    $$
    
    Combined with that page's analysis of linear congruences, this gives the structure of the solutions of $x^k\equiv a\pmod{2^e}$. There are two cases depending on the parity of $k$:
    
    -   When $k$ is odd, $\gcd(k,2)=\gcd(k,2^{e-2})=1$, so both linear congruences have solutions for all $s,r$. Hence the original congruence always has a solution for every odd $a$.
    -   When $k$ is even, the first equation has a solution if and only if $2\mid s$, and the second has a solution if and only if $d=\gcd(k,2^{e-2})\mid r$. Combining the two gives the form of all $k$-th power residue classes. A direct calculation shows that the first condition is equivalent to $a\equiv 1\pmod 4$. Repeating the analysis from the odd prime power case shows that the second condition is equivalent to $a^{d'}\equiv 1\pmod m$. Together these give the test in the theorem. The general solutions of the two linear congruences are also known:
    
        $$
        \begin{aligned}
        z &\equiv0,1\pmod 2, \\
        y &\equiv y_0 + id' \pmod{2^{e-2}},~ 0\le y_0 < d',~i=0,1,\cdots,d-1.
        \end{aligned}
        $$
    
        Combining them gives the general solution of the original equation.

This fully settles how to test for $k$-th power residues under any modulus. The Legendre symbol, quadratic reciprocity and related ideas from quadratic residues also extend to higher-power residues, but this is not easy and needs concepts such as [cyclotomic fields](../algebra/field-theory.md#cyclotomic-fields). In algebraic number theory, quadratic reciprocity is ultimately generalized to [Artin reciprocity](https://en.wikipedia.org/wiki/Artin_reciprocity).

## Roots of unity

As a special case of $k$-th roots, this section discusses $k$-th (primitive) roots of unity. They can be seen as the counterpart, in the reduced residue system $\mathbf Z_m^*$ modulo $m$, of $k$-th [roots of unity](../complex.md#roots-of-unity) in the complex numbers $\mathbf C$. For a suitable modulus $m$, using a $k$-th primitive root of unity modulo $m$ in place of the complex root $\omega_k$ can speed up computation.

As in the complex case, we have the following definition:

???+ abstract "$k$-th root of unity modulo $m$"
    For a modulus $m$, a $k$-th root of the element $1$ is called a **$k$-th root of unity modulo $m$**. In particular, if $x$ is a $k$-th root of unity modulo $m$ and is not a $k'$-th root of unity modulo $m$ for any $k' < k$, then $x$ is called a **$k$-th primitive root of unity modulo $m$**.

Comparing with the [definition of a primitive root](./primitive-root.md#primitive-root), a primitive root $g$ is exactly a $\varphi(m)$-th primitive root of unity modulo $m$, where $\varphi(m)$ is [Euler's totient function](./euler-totient.md).

When a $k$-th primitive root of unity modulo $m$ exists, it has the same algebraic properties as the complex $k$-th primitive root of unity $\omega_k$, so it can replace $\omega_k$ in all kinds of calculations. For example, using it in the [fast Fourier transform](../poly/fft.md) gives the [number theoretic transform](../poly/ntt.md) over a finite field[^fnnt].

### Properties

In the complex numbers, (primitive) roots of unity of every order exist. This is not the case for (primitive) roots of unity in number theory.

???+ note "Properties"
    For a modulus $m$, let $\lambda(m)$ be its [Carmichael function](./primitive-root.md#carmichael-function). Then:
    
    1.  Every integer $a$ coprime to $m$ is a $\delta_m(a)$-th primitive root of unity modulo $m$, where $\delta_m(a)$ is the [order](./primitive-root.md#order) of $a$ modulo $m$.
    2.  If $a$ is a $k$-th root of unity modulo $m$ and $k'$ is any multiple of $k$, then $a$ is also a $k'$-th root of unity modulo $m$.
    3.  If $a$ is a $k$-th (primitive) root of unity modulo $m$, then $a^{\ell}$ is a $\dfrac{k}{\gcd(k,\ell)}$-th (primitive, respectively) root of unity modulo $m$.
    4.  As $k'$ runs over the divisors of $k$, the $k'$-th primitive roots of unity modulo $m$ form a partition of the $k$-th roots of unity modulo $m$. Moreover, for $\ell\perp k$, the map $x\mapsto x^\ell$ is a bijection on the $k$-th roots of unity and preserves this partition: it maps $k'$-th primitive roots of unity (for $k'\mid k$) to $k'$-th primitive roots of unity.
    5.  A $k$-th primitive root of unity modulo $m$ exists if and only if $k\mid\lambda(m)$. In particular, a $\lambda(m)$-th primitive root of unity modulo $m$ exists, and it is called a **$\lambda$-primitive root modulo $m$**.
    6.  $a$ is a $k$-th primitive root of unity modulo $m$ if and only if $a^k\equiv 1\pmod{m}$ and $a^{k/p}\not\equiv 1\pmod{m}$ for every prime factor $p\mid k$.

??? note "Proof"
    By the definition of the order, every integer $a$ coprime to $m$ is a $\delta_m(a)$-th primitive root of unity modulo $m$, where $\delta_m(a)$ is the order of $a$ modulo $m$. Conversely, if $a$ is a $k$-th root of unity modulo $m$, then $\gcd(a^k,m)=1$, so $\gcd(a,m)=1$. So $a$ is a (primitive) root of unity modulo $m$ if and only if $a$ is coprime to $m$. This is property 1.
    
    Checking the definition directly, whenever $k\mid k'$, $a^k\equiv 1\pmod m$ implies $a^{k'}\equiv 1\pmod m$. This is property 2. By the [properties of the order](./primitive-root.md#cyclic-structure-of-powers),
    
    $$
    \delta_m(a^\ell) = \dfrac{\delta_m(a)}{\gcd(\delta_m(a),\ell)}.
    $$
    
    If $a$ is a $k$-th primitive root of unity modulo $m$, then $\delta_m(a)=k$, and substituting into the formula shows that $a^\ell$ is a $\dfrac{k}{\gcd(k,\ell)}$-th primitive root of unity modulo $m$. If $a$ is only a $k$-th root of unity modulo $m$, suppose it is a $k'$-th primitive root of unity with $k'\mid k$. Then $a^\ell$ is a $\dfrac{k'}{\gcd(k',\ell)}$-th primitive root of unity modulo $m$. Since $k'\mid k$,
    
    $$
    \dfrac{k'}{\gcd(k',\ell)} \mid \dfrac{k}{\gcd(k,\ell)},
    $$
    
    so by property 2, $a^\ell$ is a $\dfrac{k}{\gcd(k,\ell)}$-th root of unity modulo $m$. This is property 3.
    
    For $k'\mid k$, by property 2, every $k'$-th primitive root of unity modulo $m$ is a $k$-th root of unity modulo $m$. Conversely, every $k$-th root of unity $a$ modulo $m$ is a $\delta_m(a)$-th primitive root of unity, with $\delta_m(a)\mid k$. These sets are pairwise disjoint, so they form a partition. For $\ell\perp k$, we always have $\ell\perp k'$, so for any $k'$-th primitive root of unity $a$ modulo $m$, $a^\ell$ is also a $k'$-th primitive root of unity modulo $m$. Taking $\ell'=\ell^{-1}\bmod k$, one can check that $x\mapsto x^\ell$ and $x\mapsto x^{\ell'}$ are inverse maps, so $x\mapsto x^\ell$ is a bijection. This is property 4.
    
    By the properties of the Carmichael function, a $\lambda(m)$-th primitive root of unity modulo $m$ always exists. Call it $a$, so $\delta_m(a)=\lambda(m)$. For $k\mid\lambda(m)$, let $k'=\dfrac{\lambda(m)}{k}$. Then
    
    $$
    \delta_m(a^{k'}) = \dfrac{\lambda(m)}{\gcd(\lambda(m),k')} = \dfrac{\lambda(m)}{k'} = k.
    $$
    
    So $a^{k'}$ is a $k$-th primitive root of unity. And by the definition of the Carmichael function, the order of every $x\perp m$ divides $\lambda(m)$. This gives property 5.
    
    Property 6 follows by repeating, almost word for word, the proof of the [primitive root test](./primitive-root.md#primitive-root-test). This test actually checks that $\delta_m(a)=k$.

These properties show that $\lambda$-primitive roots modulo $m$ play a basic role similar to that of primitive roots when those exist. Unlike primitive roots, though, the powers of a $\lambda$-primitive root cannot generate all roots of unity modulo $m$. Still, $\lambda$-primitive roots are not rare[^lambda-density], so if we really need a $k$-th primitive root of unity, we can first find a $\lambda$-primitive root by random tries and then raise it to a suitable power to get a $k$-th primitive root of unity.

If we know one $k$-th root of $a$ modulo $m$, we can get all $k$-th roots of $a$ modulo $m$ from all the $k$-th roots of unity modulo $m$.

???+ note "Theorem"
    Let $x$ be a $k$-th root of $a$ modulo $m$. As $r$ runs over all $k$-th roots of unity modulo $m$, $xr$ runs over all $k$-th roots of $a$ modulo $m$.

??? note "Proof"
    For two $k$-th roots $x,y$ of $a$ modulo $m$, let $r=x^{-1}y\bmod m$. Then $r^k\equiv 1\pmod m$, so $r$ is a $k$-th root of unity modulo $m$. Conversely, if $r$ is a $k$-th root of unity modulo $m$, then $(xr)^{k}= x^kr^k\equiv a\pmod m$, that is, $xr$ is a $k$-th root of $a$ modulo $m$.

Generating all $k$-th roots from the $k$-th roots of unity is like generating the general solution of a non-homogeneous system of linear equations from the solutions of the homogeneous system.

So far we have looked at the general case. When a primitive root exists, the structure of the roots of unity is simpler:

???+ note "Theorem"
    For a modulus $m$, suppose a primitive root modulo $m$ exists, and let $a$ be a $k$-th primitive root of unity modulo $m$. Then $b$ is a $k$-th root of unity modulo $m$ if and only if it can be written as a power of $a$.

??? note "Proof"
    Let $g$ be a primitive root modulo $m$. Then every element coprime to $m$ is a power of $g$. So $a$ is a $k$-th primitive root of unity modulo $m$ if and only if
    
    $$
    \delta_m(a) = \delta_m(g^{\operatorname{ind}_ga}) = \dfrac{\varphi(m)}{\gcd(\varphi(m),\operatorname{ind}_ga)} = k.
    $$
    
    Similarly, $b$ is a $k$-th root of unity modulo $m$ if and only if
    
    $$
    \delta_m(b) = \delta_m(g^{\operatorname{ind}_gb}) = \dfrac{\varphi(m)}{\gcd(\varphi(m),\operatorname{ind}_gb)} = k' \mid k.
    $$
    
    So
    
    $$
    \gcd(\varphi(m),\operatorname{ind}_ga) \mid \gcd(\varphi(m),\operatorname{ind}_gb)\mid \operatorname{ind}_gb.
    $$
    
    By the [analysis](./linear-equation.md) of linear congruences, this condition is equivalent to the equation
    
    $$
    (\operatorname{ind}_ga) x \equiv \operatorname{ind}_gb \pmod{\varphi(m)}
    $$
    
    having a solution. Raising $g$ to both sides gives $a^x\equiv b\pmod{m}$, that is, $b$ is a power of $a$.

This theorem shows that when a primitive root exists, the $k$-th roots of unity form a [cyclic group](../algebra/group-theory.md#cyclic-groups), and the $k$-th primitive roots of unity are its generators. As we will see later, the Tonelli–Shanks algorithm uses exactly this to speed up the discrete logarithm part of root extraction.

## Modular roots

Finally, this page discusses how to find $k$-th roots. For $k=2$, there are [many efficient algorithms](./quad-residue.md#modular-square-roots) for taking square roots modulo $m$. For general $k$, however, no polynomial-time algorithm is known. This section introduces two common algorithms, which find one $k$-th root in $O(m^{1/2})$ and $O(m^{1/4+\varepsilon})$ time, respectively. The Chinese remainder theorem always reduces the problem to prime power moduli, so this section mainly deals with prime power moduli.

### Naive algorithm

The [analysis](#properties) of $k$-th power residues above already gives a way to find $k$-th roots modulo a prime power. Strictly speaking, it covers the case where the radicand $a$ is coprime to the modulus $m$. The algorithm is summarized as follows:

-   When $m=p^e$ is an odd prime power, let $g$ be a primitive root modulo $m$. Then $x^k\equiv a\pmod m$ turns into the linear congruence

    $$
    ky \equiv \operatorname{ind}_g a \pmod{\varphi(m)}.
    $$

    Here $\operatorname{ind}_g a$ can be found with the [BSGS algorithm](./discrete-logarithm.md#baby-step-giant-step), and all solutions of the [linear congruence](./linear-equation.md) are easy to find. This gives all $k$-th roots of $a$ as $x\equiv g^y\pmod m$.

    There is another, similar approach. Again let $x\equiv g^y\pmod m$, and rewrite the equation as

    $$
    x^k \equiv (g^k)^y \equiv a \pmod m
    $$

    which turns it into finding the discrete logarithm of $a$ to the base $g^k$. BSGS can also find one particular solution here. The general solution follows from the expression for the solutions above, i.e., by multiplying the particular solution by each $k$-th root of unity.

    Either way, once a primitive root is known, this algorithm finds one solution in $O(m^{1/2})$ time. A primitive root can be found in $o(m^{1/2})$ time, so the overall time complexity is still $O(m^{1/2})$.

-   When $m=2^e$ with $e\in\mathbf N_+$, first find $s,r$ in $a\equiv (-1)^s5^r\pmod m$. Of these two exponents, $s$ can be found in $O(1)$ time:

    $$
    s = \begin{cases}0, & a\equiv 1\pmod 4, \\ 1, & a\equiv 3\pmod 4.\end{cases}
    $$

    And $r=\operatorname{ind}_5((-1)^sa)$ can be found with BSGS in $O(m^{1/2})$ time. Then we only need to solve the system of linear congruences:

    $$
    \begin{aligned}
    kz &\equiv s \pmod{2},\\
    ky &\equiv r \pmod{2^{e-2}}.
    \end{aligned}
    $$

    The general solution $(z,y)$ of this system is easy to find, and $x=(-1)^z5^y$ is the root we want. This algorithm still finds one solution in $O(m^{1/2})$ time.

Of course, the case with no solution can be detected quickly in $O(\log m)$ time with the test described above, instead of during the solving process.

Here is a reference implementation for $k$-th roots modulo a prime. (The code is only for illustration. Its time complexity is too high to pass this problem.)

??? example "Reference implementation for the template problem [Library Checker - Kth Root (Mod)](https://judge.yosupo.jp/problem/kth_root_mod)"
    ```cpp
    --8<-- "docs/math/code/residue/bsgs-mod-p.cpp"
    ```

### Improved Tonelli–Shanks algorithm

Suitably generalizing the [Tonelli–Shanks algorithm](./quad-residue.md#tonellishanks-algorithm) for modular square roots solves root extraction modulo prime powers. A fairly direct generalization is the Adleman–Manders–Miller algorithm[^amm], but its complexity is still not good enough[^amm-comp]. This section introduces the improved Tonelli–Shanks algorithm proposed by sugarknri, Min\_25, 37zigen and others. It finds one $k$-th root in $O(m^{1/4+\varepsilon})$ time.

The core idea of Tonelli–Shanks is to move the discrete logarithm into a group of order $2^e$, which lowers the time complexity. Similarly, discrete logarithms in a group of any prime power order $p^e$ can also be computed fairly efficiently, but the algorithm costs $\Omega\left(\sqrt{p}\right)$. The Adleman–Manders–Miller algorithm splits finding a $k$-th root into several discrete logarithms in groups of prime power order, but it is limited by the size of the largest prime factor $p_\text{max}(k)$ of $k$, so its complexity is still $\Omega\left(\sqrt{p_\text{max}(k)}\right)$. The algorithm in this section improves this process further. It avoids computing discrete logarithms for large prime factors, which brings the overall complexity down to $O(m^{1/4+\varepsilon})$.

#### How it works

Consider computing a $k$-th root of $a$ modulo a prime power $m$, that is, solving the congruence:

$$
x^k \equiv a \pmod m.
$$

In particular, when $m=2^e$, we also require $a\equiv 1\pmod{4}$, so that $a$ is a power of $g=5$. As discussed above, finding $k$-th roots modulo $2^e$ can always be reduced to this case. When handling modulus $2^e$, every $\varphi(m)$ in this section should be replaced by $\delta_m(5)=2^{e-2}$.

First, the problem can be reduced to the case where the root degree divides $\varphi(m)$. Let $d=\gcd(k,\varphi(m))$. By the properties of $k$-th power residues, when $a$ is a $k$-th power residue modulo $m$, $a$ is always a $\dfrac{\varphi(m)}{d}$-th root of unity modulo $m$. By the properties of roots of unity, for any $\ell\perp\dfrac{\varphi(m)}{d}$, the map $x\mapsto x^{\ell}$ is a bijection on the $\dfrac{\varphi(m)}{d}$-th roots of unity. So we can take

$$
\ell = \left(\dfrac{k}{d}\right)^{-1}\bmod\dfrac{\varphi(m)}{d}.
$$

Raising both sides of the original congruence to the $\ell$-th power gives

$$
x^d\equiv x^{k\ell} \equiv a^{\ell} =: b \pmod{m}.
$$

The leftmost congruence uses [Euler's theorem](./fermat.md#eulers-theorem) and the following congruence (with $c\in\mathbf Z$):

$$
k\ell = d\left(\frac{k}{d}\ell\right) = d\left(c\dfrac{\varphi(m)}{d}+1\right) \equiv d \pmod{\varphi(m)}.
$$

For the reduced problem, consider the prime factorization of $d$:

$$
d = \prod_{p\in\mathbf P}p^e.
$$

Starting from $b=a^\ell$, take a $p^e$-th root for each $p^e\neq 1$ in turn. At the end we get a $d$-th root of $b$, which is a $k$-th root of $a$.

Finally, the problem becomes solving the following equation:

$$
x^{p^e} \equiv b \pmod m.
$$

Let $\varphi(m)=p^sr$ with $p\perp r$. Let $q\in\mathbf N_+$ be a solution of $qr\equiv -1\pmod{p^e}$. Since $b$ is an $rp^{s-e}$-th root of unity, $b^{qr}$ must be a $p^{s-e}$-th root of unity. Let $\zeta$ be a $p^s$-th primitive root of unity modulo $m$. Then $\zeta^{p^e}$ is a $p^{s-e}$-th primitive root of unity, so there is $h\in\mathbf N$ with $b^{qr}\equiv \zeta^{hp^{e}}\pmod{m}$. A direct check then shows that

$$
x\equiv b^{(qr+1)/p^e}\zeta^{-h} \pmod{m}
$$

is a $p^e$-th root of $b$ modulo $m$.

To compute $x$, we need a $p$-th power non-residue $\eta$ modulo $m$. By the properties above, we just pick a random $\eta\perp m$ and check that $\eta^{\varphi(m)/p}\bmod{m}\neq 1$. The density of such numbers is

$$
\dfrac{\varphi(m)}{m}\left(1-\dfrac{1}{p}\right) \ge \dfrac{1}{4}.
$$

So on average at most $4$ random integers are needed to find one. Note that $\eta^{rp^{s-1}}\not\equiv 1\pmod m$ and $\eta^{rp^s}\equiv 1\pmod m$, so if we let $\zeta=\eta^r\bmod m$ and $\xi=\eta^{rp^{s-1}}\bmod m$, they are a $p^s$-th and a $p$-th primitive root of unity, respectively.

Finally, we need to compute $h\in\mathbf N$. Clearly we can take $h < p^{s-e}$. Consider $h$ written in base $p$:

$$
h = \sum_{j=0}^{s-e-1}h_jp^j = h_0 + h_1p + h_2p^2 +\cdots.
$$

We compute these digits one at a time. Once the first $j$ digits are known, we must have

$$
\left(b^{qr}\zeta^{-p^e(h_0+h_1p+\cdots + h_{j-1}p^{j-1})}\right)^{p^{s-e-j-1}} \equiv \zeta^{h_jp^{s-1}} \equiv \xi^{h_j} \pmod{m}.
$$

So $h_j$ can be found by computing a discrete logarithm to the base $\xi$. For a better time complexity, we use BSGS. We need $(s-e)$ discrete logarithms in total. If we precompute $B$ powers of $\xi$, each discrete logarithm takes $O(p/B)$ time, so the total time complexity is

$$
O\left(B+(s-e)\dfrac{p}{B}\right).
$$

The total time is smallest when $B=\sqrt{(s-e)p}$, namely $O\left(\sqrt{(s-e)p}\right)$. Once we have $h$, plugging it into the expression for $x$ above gives one particular solution.

#### Time complexity

The time complexity of this algorithm is $O(m^{1/4+\varepsilon})$. In this analysis we always assume a single multiplication takes $O(1)$ time, and when computing powers we always reduce the exponent with Euler's theorem, so each power can be computed in $O(\log m)$ time.

First consider computing a single $p^e$-th root. Finding a $p$-th power non-residue needs to check $O(1)$ numbers on average, for a total of $O(\log m)$ time. Computing each of $s,r,\zeta,\eta,b^{qr}$ takes $O(\log m)$ time. When computing $h$, each digit needs $O(\log m)$ time for a power, and there are $(s-e)$ digits, so this takes $O((s-e)\log m)$ in total. As shown above, the precomputation and $(s-e)$ queries for the discrete logarithms take $O\left(\sqrt{(s-e)p}\right)$ in total. Since $s-e\in O(\log m)$, computing a single $p^e$-th root takes $O(p^{1/2+\varepsilon})$ time. In particular, when $s=e$, the time complexity drops further to $O(\log m)$.

Now consider the total time complexity of the algorithm. Computing $\varphi(m),d,\ell$ takes $O(\log m)$ time each. Next we need the prime factorization $d=\prod_p{p^e}$, which the [Pollard Rho algorithm](./pollard-rho.md#pollard-rho-algorithm) does in $O(m^{1/4})$ time. Finally, taking the $p^e$-th roots one by one costs in total

$$
O\left(\sum_{e < s}p^{1/2+\varepsilon}\right).
$$

A prime factor $p$ with $e < s$ appears at least $2$ times in $\varphi(m)$, so we must have $p < m^{1/2}$. Therefore the total time complexity is $O(m^{1/4+\varepsilon})$.

In fact, in this setting we can still get $O(m^{1/4+\varepsilon})$ time without using Pollard Rho to factor. Specifically, we just factor $d$ by brute-force trial division, only trying prime factors up to $m^{1/4}$. Let $z$ be the integer left after removing these small prime factors. Then for each prime factor $p > m^{1/4}$ of $z$, we must have $\nu_p(\varphi(m)) < 4$, where $\nu_p(n)$ is the exponent of $p$ in the prime factorization of $n$. Since we only need to consider the case

$$
1 \le e = \nu_p(d) < s = \nu_p(\varphi(m)) < 4
$$

there can be at most one prime factor $p$ that satisfies this condition. Otherwise, each of them would appear in $\varphi(m)$ with exponent at least $2$, and their product would exceed $m$. To separate out this (possible) single large prime factor, we only need to compute

$$
p^\star=\gcd\left(z,\dfrac{\varphi(m)}{z}\right) = \prod_{p\mid z,~\nu_p(d) < \nu_p(\varphi(m))}p^{\min\{\nu_p(d),\nu_p(\varphi(m))-\nu_p(d)\}}.
$$

Going through all possible values of $\nu_p(d),\nu_p(\varphi(m))$ shows that the exponent of $p$ in this product is always $1$, so this computes exactly the single large prime factor $p^\star$ (if it exists). The remaining part $z/p^\star$ can only contain prime factors with $e=s$, so it does not need to be factored further.

Here is a reference implementation for $k$-th roots modulo a prime:

??? example "Reference implementation for the template problem [Library Checker - Kth Root (Mod)](https://judge.yosupo.jp/problem/kth_root_mod)"
    ```cpp
    --8<-- "docs/math/code/residue/tonelli-shanks-mod-p.cpp"
    ```

### Handling the general case

Now consider the general case. Again let the modulus $m$ be a prime power $p^e$, but now $\gcd(a,m)>1$. If $a\equiv 0\pmod{m}$, then all of

$$
x \equiv p^{\lceil e/k \rceil}\ell\pmod{p^e},~\ell=0,1,\cdots,p^{e-\lceil e/k\rceil}-1
$$

are solutions of the original equation. Next, consider the case $a\not\equiv 0\pmod{m}$. Let $a = p^sa'$ with $p\perp a'$. Let $x=p^zx'$ with $p\perp x'$. Then

$$
x^k = p^{kz}(x')^k\equiv p^sa'\pmod{p^e}.
$$

Since $(x')^k\perp p$, this holds if and only if $kz = s$ and $(x')^k\equiv a'\pmod{p^{e-s}}$. The first equation has a solution $z=\dfrac{s}{k}$ if and only if $k\mid s$, and we already know how to solve the second. Note that the general solution of the second equation has a different modulus from the general solution of the original equation, so each solution $x'$ of the second equation corresponds to several solutions of the original equation:

$$
x \equiv p^{s/k}(x' + \ell p^{e-s})\pmod{p^e},~\ell = 0,1,\cdots, p^{s-s/k}-1.
$$

Here is a reference implementation that finds all $k$-th roots under any modulus:

??? example "Reference code for the template problem [Luogu P5668 [Template] N-th Residue](https://www.luogu.com.cn/problem/P5668)"
    === "Naive algorithm"
        ```cpp
        --8<-- "docs/math/code/residue/bsgs.cpp"
        ```
    
    === "Improved Tonelli–Shanks algorithm"
        ```cpp
        --8<-- "docs/math/code/residue/tonelli-shanks.cpp"
        ```

## References and notes

-   Feng Keqin. Elementary Number Theory and Its Applications.
-   [Root of unity modulo n - Wikipedia](https://en.wikipedia.org/wiki/Root_of_unity_modulo_n)
-   [No.981 General Power Root, editorial by 37zigen](https://yukicoder.me/problems/no/981/editorial)

[^fnnt]: In fact, the modulus $m$ does not have to be prime. As long as $a$ is a $k=2^e$-th primitive root of unity modulo $m$, it can be used for the number theoretic transform modulo $m$. However, the $2^e$ we usually need is fairly large, which means every prime factor of $m$ has the form $c2^e+1$. So each prime factor is already large, and the modulus $m$ is usually even larger. That is why general moduli are used much less often than prime moduli.

[^lambda-density]: By the [result on the number of primitive roots](./primitive-root.md#number-of-primitive-roots), there are exactly $\varphi(\lambda(m))$ $\lambda$-primitive roots, where $\varphi(\cdot)$ and $\lambda(\cdot)$ are Euler's totient function and the Carmichael function. For almost all integers $m$, $\lambda(m)/m = \exp(-(1+o(1))\log\log m\log\log\log m)$, and there is $C > 0$ such that $\varphi(m)/m \ge C / \log\log m$ for all integers $m > 2$. So for almost all integers $m$, $\varphi(\lambda(m))/m = \exp(-(1+o(1))\log\log m\log\log\log m)$. Here the $o(1)$ in the coefficient of the exponent absorbs the contribution of the factor $\varphi(\lambda(m))/\lambda(m)$. So a $\lambda$-primitive root can be found in $\exp((1+o(1))\log\log m\log\log\log m)$ tries on average. For estimates of Euler's totient function, see Rosser, J. Barkley, and Lowell Schoenfeld. "Approximate formulas for some functions of prime numbers." Illinois Journal of Mathematics 6, no. 1 (1962): 64-94. For estimates of the Carmichael function, see Erdos, Paul, Carl Pomerance, and Eric Schmutz. "Carmichael’s lambda function." Acta Arith 58, no. 4 (1991): 363-385.

[^amm]: For the original paper, see Adleman, Leonard, Kenneth Manders, and Gary Miller. "On taking roots in finite fields." In 18th Annual Symposium on Foundations of Computer Science (sfcs 1977), pp. 175-178. IEEE Computer Society, 1977. A more readable introduction is Cao, Zhengjun, Qian Sha, and Xiao Fan. "Adleman-Manders-Miller root extraction method revisited." In International Conference on Information Security and Cryptology, pp. 77-85. Berlin, Heidelberg: Springer Berlin Heidelberg, 2011.

[^amm-comp]: This algorithm requires $k$ to be prime, so in the worst case it has to find a $p$-th root of $a$ modulo $m$ for the largest prime factor $p$ of $\varphi(m)$. This needs the discrete logarithm of $a$ modulo $m$ with respect to a $p$-th primitive root of unity. Even with BSGS, this takes $O(\sqrt{p})$ time. However, the paper Fouvry, Étienne. "Theoreme de Brun-Titchmarsh; application au theoreme de Fermat." Inventiones mathematicae 79, no. 2 (1985): 383-407 shows that there is a positive density of primes $m$ for which the largest prime factor of $\varphi(m)=m-1$ is $p=\Omega(m^{2/3})$. So this algorithm takes at least $\Omega(m^{1/3})$ time, which is worse than the improved Tonelli–Shanks algorithm described here.
