author: hly1204, ShaoChenHeng, Chrogeek, Enter-tainer, Great-designer, iamtwz, monkeysui, nanmenyangde, rgw2010, sshwy, StudyingFather, TachikakaMin, Tiphereth-A, Xeonacid, xyf007, marscheng1

## Introduction

Quadratic residues are about whether we can take **square roots** modulo some number. For roots of higher degree, see [k-th power residues](./residue.md).

## Definition

???+ abstract "Quadratic residue"
    Let $a$ and $p$ be integers with $(a,p)=1$. If there is an integer $x$ such that
    
    $$
    x^2\equiv a\pmod p,
    $$
    
    then $a$ is called a quadratic residue modulo $p$. Otherwise, $a$ is called a quadratic non-residue modulo $p$. Later on, when the modulus $p$ is clear, we may just say quadratic (non-)residue.

## Euler's criterion

When the modulus is an odd prime, we have the following theorem:

???+ abstract "Euler's criterion"
    For an odd prime $p$ and an integer $a$ with $(a,p)=1$,
    
    $$
    a^{\frac{p-1}{2}}\equiv\begin{cases}
        1 \pmod p,  & (\exists x\in\mathbf{Z}),~~a\equiv x^2\pmod p,\\
        -1 \pmod p, & \text{otherwise}.\\
    \end{cases}
    $$
    
    That is, for such $p$ and $a$:
    
    1.  $a$ is a quadratic residue modulo $p$ if and only if $a^{\frac{p-1}{2}}\equiv 1 \pmod p$.
    2.  $a$ is a quadratic non-residue modulo $p$ if and only if $a^{\frac{p-1}{2}}\equiv -1 \pmod p$.

??? note "Proof"
    First, by [Fermat's little theorem](./fermat.md#费马小定理), $a^{p-1}\equiv 1\pmod p$, so
    
    $$
    \left(a^{\frac{p-1}{2}}+1\right)\left(a^{\frac{p-1}{2}}-1\right)\equiv 0\pmod p,
    $$
    
    hence every $a$ with $(a,p)=1$ satisfies $a^{(p-1)/2}\equiv \pm 1\pmod p.$
    
    Also, since $p$ is an odd prime, we have:
    
    $$
    x^{p-1}-a^{\frac{p-1}{2}}={\left(x^2\right)}^{\frac{p-1}{2}}-a^{\frac{p-1}{2}}=(x^2-a)P(x),
    $$
    
    where $P(x)$ is some polynomial with integer coefficients. Then:
    
    $$
    \begin{aligned}
        x^p-x&=x\left(x^{p-1}-a^{\frac{p-1}{2}}\right)+x\left(a^{\frac{p-1}{2}}-1\right)\\
        &=(x^2-a)xP(x)+\left(a^{\frac{p-1}{2}}-1\right)x.\\
    \end{aligned}
    $$
    
    By [Theorem 5 on congruence equations](./congruence-equation.md#素数模同余方程), $a$ is a quadratic residue modulo $p$ if and only if $a^{(p-1)/2}\equiv 1\pmod p$. Therefore $a$ is a quadratic non-residue modulo $p$ if and only if $a^{(p-1)/2}\equiv -1\pmod p$.

From Euler's criterion we get the following corollary:

???+ note "Number of quadratic residues"
    For an odd prime $p$, there are exactly $\dfrac{p-1}{2}$ quadratic residues and $\dfrac{p-1}{2}$ quadratic non-residues modulo $p$.

??? note "Proof"
    By Euler's criterion, consider $a^{\frac{p-1}{2}}\equiv 1\pmod p.$
    
    Note that $\dfrac{p-1}{2}\mid (p-1)$. By [Theorem 6 on congruence equations](./congruence-equation.md#素数模同余方程), $a^{\frac{p-1}{2}}\equiv 1\pmod p$ has $\dfrac{p-1}{2}$ solutions. So there are $\dfrac{p-1}{2}$ quadratic residues and $\dfrac{p-1}{2}$ quadratic non-residues modulo $p$.

## Legendre symbol

To make the discussion below easier, we introduce the following notation:

???+ abstract "Legendre symbol"
    For an **odd prime**  $p$ and an integer $a$, the Legendre symbol is defined as:
    
    $$
    \left(\frac{a}{p}\right)=\begin{cases}
        0,  & p\mid a,\\
        1,  & (p\nmid a) \land ((\exists x\in\mathbf{Z}),~~a\equiv x^2\pmod p),\\
        -1, & \text{otherwise}.\\
    \end{cases}
    $$

That is, for $a$ with $(a,p)=1$:

-   $a$ is a quadratic residue modulo $p$ if and only if $\left(\dfrac{a}{p}\right)=1.$
-   $a$ is a quadratic non-residue modulo $p$ if and only if $\left(\dfrac{a}{p}\right)=-1.$

The table below shows some values of the Legendre symbol (from [Wikipedia](https://en.wikipedia.org/wiki/Legendre_symbol#Table_of_values)).

![](./images/quad_residue.png)

### Properties

1.  For any integer $a$,

    $$
    a^{\frac{p-1}{2}}\equiv \left(\frac{a}{p}\right)\pmod p.
    $$

    As a further consequence:

    -   $$
        \left(\dfrac{1}{p}\right)=1.
        $$
    -   $$
        \left(\dfrac{-1}{p}\right)=(-1)^{\frac{p-1}{2}}=\begin{cases}
            1,  & p\equiv 1\pmod 4,\\
            -1, & p\equiv 3\pmod 4.
            \end{cases}
        $$

2.  $a_1\equiv a_2\pmod p\implies \left(\dfrac{a_1}{p}\right)=\left(\dfrac{a_2}{p}\right).$

3.  ([Completely multiplicative](./basic.md#积性函数)) For any integers $a_1,a_2$,

    $$
    \left(\frac{a_1a_2}{p}\right)=\left(\frac{a_1}{p}\right)\left(\frac{a_2}{p}\right).
    $$

    Corollary: for integers $a,b$ with $p\nmid b$,

    $$
    \left(\frac{ab^2}{p}\right)=\left(\frac{a}{p}\right).
    $$

4.  $$
    \left(\frac{2}{p}\right)=(-1)^{\frac{p^2-1}{8}}=\begin{cases}
            1,  & p\equiv \pm 1\pmod 8, \\
            -1, & p\equiv \pm 3\pmod 8. \\
        \end{cases}
    $$

??? note "Proof"
    1.  This follows easily from the [definition of the Legendre symbol](#legendre-symbol) and [Euler's criterion](#eulers-criterion).
    2.  Note that
    
        $$
        a_1\equiv a_2\pmod p\implies \left(\frac{a_1}{p}\right)\equiv\left(\frac{a_2}{p}\right)\pmod p,
        $$
    
        and $\left|\left(\dfrac{a_1}{p}\right)-\left(\dfrac{a_2}{p}\right)\right|\leq 2$ with $p>2$, so:
    
        $$
        a_1\equiv a_2\pmod p\implies \left(\frac{a_1}{p}\right)=\left(\frac{a_2}{p}\right).
        $$
    3.  By property 1,
    
        $$
        \left(\frac{a_1a_2}{p}\right)\equiv a_1^{\frac{p-1}{2}}a_2^{\frac{p-1}{2}}\equiv\left(\frac{a_1}{p}\right)\left(\frac{a_2}{p}\right)\pmod p.
        $$
    
        Also $\left|\left(\dfrac{a_1a_2}{p}\right)-\left(\dfrac{a_1}{p}\right)\left(\dfrac{a_2}{p}\right)\right|\leq 2$ and $p>2$, so
    
        $$
        \left(\frac{a_1a_2}{p}\right)=\left(\frac{a_1}{p}\right)\left(\frac{a_2}{p}\right).
        $$
    4.  See [Quadratic reciprocity](#quadratic-reciprocity).

By these properties, if we can compute $\left(\dfrac{p}{q}\right)$ for any odd primes $p$ and $q$, then we can compute the Legendre symbol in every valid case. Next comes a beautiful theorem. It cleverly links $\left(\dfrac{p}{q}\right)$ and $\left(\dfrac{q}{p}\right)$, so we can compute the symbol with an approach similar to the [Euclidean algorithm](./gcd.md#欧几里得算法).

### Quadratic reciprocity

???+ note "Law of quadratic reciprocity"
    Let $p$ and $q$ be two distinct odd primes. Then
    
    $$
    \left(\frac{p}{q}\right)\left(\frac{q}{p}\right)=(-1)^{\frac{p-1}{2}\frac{q-1}{2}}.
    $$

There are many proofs[^ref5]. One of them is based on the following lemma[^ref6]:

???+ note "Gauss's lemma"
    Let $p$ be an odd prime and $(n,p)=1$. For integers $k~\left(1\leq k\leq (p-1)/2\right)$, let $r_k=nk\bmod p$. Let $A=\{r_k:r_k < p/2\}$ and $B=\{r_k:r_k > p/2\}$. Then
    
    $$
    \left(\frac{n}{p}\right)=(-1)^{|B|}.
    $$

??? note "Proof"
    Let $\lambda=|A|$ and $\mu=|B|$. Clearly $\lambda+\mu=(p-1)/2$, so
    
    $$
    n^{\frac{p-1}{2}}\left(\frac{p-1}{2}\right)!=\prod_{k=1}^{\frac{p-1}{2}} nk\equiv\prod_{a\in A}a\prod_{b\in B}b\pmod{p}.
    $$
    
    For any element $b$ of $B$ we know $\dfrac{p}{2} < b < p$, so $0 < p-b < \dfrac{p}{2}$. Moreover, for any $b$ in $B$ we have $p-b\notin A$. Otherwise, if there were elements $a\in A$ and $b\in B$ with $a=p-b$, there would be integers $0 < k_1,k_2 < (p-1)/2$ with $a=nk_1$, $b=nk_2$ and $p\mid n(k_1+k_2)$. Since $(n,p)=1$, we get $p\mid (k_1+k_2)$. But $0 < k_1+k_2 < p$, a contradiction. Therefore
    
    $$
    n^{\frac{p-1}{2}}\left(\frac{p-1}{2}\right)!\equiv(-1)^{\mu}\prod_{a\in A}a\prod_{b\in B}(p-b)=(-1)^{\mu}\left(\frac{p-1}{2}\right)!\pmod{p},
    $$
    
    that is,
    
    $$
    n^{\frac{p-1}{2}}\equiv(-1)^{\mu}\pmod{p}.
    $$
    
    The claim then follows from [property 1](#properties) of the Legendre symbol.

??? tip "Generalization"
    Gauss's lemma can be generalized as follows[^ref7]:
    
    Let $p$ be an odd prime, and let $I\subset\mathbf{Z}_p^*$ satisfy $I\cup -I=\mathbf{Z}_p^*$ and $I\cap -I=\varnothing$, where $-I:=\{-i:i\in I\}$. Then for any integer $n$ coprime to $p$,
    
    $$
    \left(\frac{n}{p}\right)=(-1)^{|J|},
    $$
    
    where $J=\{j\in I:nj\in -I\}$.
    
    Taking $I=\{1,2,\dots,(p-1)/2\}$ gives Gauss's lemma. The proof is basically the same as the proof of Gauss's lemma, so we omit it.

The following corollary is easy to obtain:

???+ note "Corollary"
    For an odd prime $p$,
    
    $$
    \left(\frac{2}{p}\right)=(-1)^{\frac{p^2-1}{8}}=\begin{cases}
            1,  & p\equiv \pm 1\pmod 8, \\
            -1, & p\equiv \pm 3\pmod 8. \\
        \end{cases}
    $$
    
    For an odd prime $p$ and an odd number $n$ with $(n,p)=1$,
    
    $$
    \left(\frac{n}{p}\right)=(-1)^{\sum_{i=1}^{(p-1)/2}\lfloor ni/p \rfloor}.
    $$

??? note "Proof"
    With $n,k,r_k,A,B,\lambda,\mu$ as in Gauss's lemma, we have $nk=p\left\lfloor\dfrac{nk}{p}\right\rfloor+r_k$, so
    
    $$
    \begin{aligned}
        n\cdot\frac{p^2-1}{8}=\sum_{k=1}^{\frac{p-1}{2}}nk&=p\sum_{k=1}^{\frac{p-1}{2}}\left\lfloor\dfrac{nk}{p}\right\rfloor+\sum_{a\in A}a+\sum_{b\in B}b\\
        &=p\sum_{k=1}^{\frac{p-1}{2}}\left\lfloor\dfrac{nk}{p}\right\rfloor+\sum_{a\in A}a+\sum_{b\in B}(p-b)+2\sum_{b\in B}b-p\mu\\
        &=p\sum_{k=1}^{\frac{p-1}{2}}\left\lfloor\dfrac{nk}{p}\right\rfloor+\sum_{k=1}^{\frac{p-1}{2}}k+2\sum_{b\in B}b-p\mu\\
        &=p\sum_{k=1}^{\frac{p-1}{2}}\left\lfloor\dfrac{nk}{p}\right\rfloor+\frac{p^2-1}{8}+2\sum_{b\in B}b-p\mu,
    \end{aligned}
    $$
    
    hence
    
    $$
    (n-1)\frac{p^2-1}{8}=p\sum_{k=1}^{\frac{p-1}{2}}\left\lfloor\dfrac{nk}{p}\right\rfloor+2\sum_{b\in B}b-p\mu.
    $$
    
    If $n=2$, then $0 < \dfrac{nk}{p}\leq\dfrac{p-1}{p} < 1$, so
    
    $$
    \frac{p^2-1}{8}\equiv\mu\pmod{2}.
    $$
    
    If $2\nmid n$, then
    
    $$
    \sum_{k=1}^{\frac{p-1}{2}}\left\lfloor\dfrac{nk}{p}\right\rfloor\equiv\mu\pmod{2}.
    $$

By the corollary above, to prove quadratic reciprocity we only need to check that

$$
\frac{p-1}{2}\frac{q-1}{2}=\sum_{k=1}^{\frac{p-1}{2}}\left\lfloor\dfrac{qk}{p}\right\rfloor+\sum_{k=1}^{\frac{q-1}{2}}\left\lfloor\dfrac{pk}{q}\right\rfloor.
$$

Consider the set $S$ of points $(px,qy)$ with $1\leq x\leq \dfrac{q-1}{2},1\leq y\leq \dfrac{p-1}{2}$. Split it into two parts by comparing $px$ and $qy$ (clearly $px\neq qy$), and then check the sizes of the three sets.

Quadratic reciprocity can tell us not only whether a number $n$ is a quadratic residue modulo $p$, but also what the moduli that make $n$ a quadratic residue look like.

???+ example "Example"
    -   The odd primes $p$ for which $5$ is a quadratic residue are those with $p\equiv \pm 1\pmod 5.$
    -   The odd primes $p$ for which $-3$ is a quadratic residue are those with $p\equiv 1\pmod 3.$
    -   The odd primes $p$ for which $-2$ and $3$ are both quadratic residues are those with $p\equiv 11\pmod{24}.$

We can also prove results such as "there are infinitely many primes of the form $4k+1$". Results of this kind are actually simple corollaries of [Dirichlet's theorem](https://en.wikipedia.org/wiki/Dirichlet%27s_theorem_on_arithmetic_progressions).

## Jacobi symbol

Quadratic reciprocity suggests a natural way to generalize the Legendre symbol:

???+ abstract "Jacobi symbol"
    For a **positive odd number**  $m=p_1^{\alpha_1}\dots p_k^{\alpha_k}$ and an integer $a$, where $p_1,\dots,p_k$ are primes and $\alpha_1,\dots,\alpha_k$ are positive integers, the Jacobi symbol is defined as:
    
    $$
    \left(\frac{a}{m}\right):=\prod_{i=1}^k\left(\frac{a}{p_i}\right)^{\alpha_i}.
    $$
    
    Here each $\left(\frac{a}{p_i}\right)$ on the right-hand side is a [Legendre symbol](#legendre-symbol). Also, for any integer $a$, $\left(\dfrac{a}{1}\right)=1.$

???+ warning "Warning"
    We usually do not distinguish between the Legendre symbol and the Jacobi symbol. By complete multiplicativity, the Jacobi symbol has the same properties as the Legendre symbol, so both are computed in the same way. But note one thing: when $m$ is **not an odd prime**, the value of $\left(\dfrac{a}{m}\right)$ **says nothing** about whether $a$ is a quadratic residue modulo $m$. However, if $\left(\dfrac{a}{m}\right)=-1$, then $m$ has at least one (in fact an odd number of) prime factor $p$ such that $a$ is a quadratic non-residue modulo $p$, and so $a$ is a quadratic non-residue modulo $m$.

We can generalize the modulus further to any **integer** (we only need to add definitions for $\left(\dfrac{a}{-1}\right)$, $\left(\dfrac{a}{0}\right)$ and $\left(\dfrac{a}{2}\right)$). This gives the [Kronecker symbol](https://en.wikipedia.org/wiki/Kronecker_symbol).

## Modular square roots

This section covers algorithms for taking square roots modulo a number. We mainly look at prime moduli. For general moduli, see the discussion in [modular higher-degree roots](./residue.md#模意义下开方).

### Algorithms for special cases

For the congruence $x^2\equiv a\pmod p$, where $p$ is an odd prime and $a$ is a quadratic residue, there is a simpler method when $p\bmod 4=3$. Consider

$$
\begin{aligned}
\left(a^{(p+1)/4}\right)^2&\equiv a^{(p+1)/2}&\pmod p\\
&\equiv x^{p+1}&\pmod p\\
&\equiv \left(x^2\right)\left(x^{p-1}\right)&\pmod p\\
&\equiv x^2&\pmod p&\quad (\because{\text{Fermat's little theorem}})
\end{aligned}
$$

So $a^{(p+1)/4}\bmod p$ is a solution.

#### Atkin's algorithm

Consider the same congruence, now with $p\bmod 8=5$. Let $b\equiv (2a)^{(p-5)/8}\pmod p$ and $\mathrm{i}\equiv 2ab^2\pmod p$. Then $\mathrm{i}^2\equiv -1\pmod p$, and $ab(\mathrm{i}-1)\bmod p$ is a solution.

???+ note "Proof"
    $$
    \begin{aligned}
    \mathrm{i}^2&\equiv\left(2ab^2\right)^2&\pmod p\\
    &\equiv \left(2a\cdot \left(2a\right)^{(p-5)/4}\right)^2&\pmod p\\
    &\equiv \left(\left(2a\right)^{(p-1)/4}\right)^2&\pmod p\\
    &\equiv \left(2a\right)^{\frac{p-1}{2}}&\pmod p\\
    &\equiv -1&\pmod p
    \end{aligned}
    $$
    
    Then
    
    $$
    \begin{aligned}
    \left(ab(\mathrm{i}-1)\right)^2&\equiv a^2\cdot \left(2a\right)^{(p-5)/4}\cdot (-2\mathrm{i})&\pmod p\\
    &\equiv a\cdot (-\mathrm{i})\cdot \left(2a\right)^{(p-1)/4}&\pmod p\\
    &\equiv a&\pmod p
    \end{aligned}
    $$

### Cipolla's algorithm

Cipolla's algorithm solves the congruence $y^2\equiv a\pmod p$, where $p$ is an odd prime and $a$ is a quadratic residue.

In this section we work in $\mathbf{F}_p\lbrack x\rbrack /(x^2-g)$, where $g \in \mathbf{F}_p$.

??? note "How to compute"
    If you are not familiar with [polynomial rings](../algebra/ring-theory.md#多项式环), you can simply think of every element of this set as having the form $a_0+a_1x$ with $a_0,a_1\in\mathbf F_p$, following these rules:
    
    $$
    \begin{aligned}
    (a_0+a_1x)+(b_0+b_1x) &\equiv (a_0+b_0)+(a_1+b_1)x &\pmod{(x^2-g)}\\
    (a_0+a_1x)(b_0+b_1x) &\equiv (a_0b_0+a_1b_1g)+(a_1b_0+a_0b_1)x &\pmod{(x^2-g)}
    \end{aligned}
    $$
    
    Note that $x$ here is not a concrete number. It is a formal symbol in a polynomial. The key step in these operations is to use $x^2 \equiv g \pmod{(x^2-g)}$ to turn the quadratic term into a linear term and a constant term. Also, all integer arithmetic is done modulo $p$.
    
    For more about this structure, see pages such as [Polynomials](../poly/intro.md) and [Field theory](../algebra/field-theory.md).

The first step of the algorithm is to find an $r$ such that $r^2-a$ is a quadratic non-residue. Of course, no such $r$ exists when $a \equiv 0 \pmod p$, so that case needs special handling. Below we only discuss $a \not\equiv 0 \pmod p$. In that case, we can pick a random $r$ and test it; on average it takes $2$ tries to find one. Then $(r-x)^{\frac{p+1}{2}}\bmod (x^2-(r^2-a))$ is a solution, which can be computed with fast exponentiation.

??? note "Why it takes only two tries on average"
    Consider the case where $r^2-a$ is a quadratic residue. Then there is an $x$ with $r^2-a \equiv x^2 \pmod p$. Rearranging gives $(r+x)(r-x) \equiv a \pmod p$. Each value $(r+x) \in [1, p-1]$ corresponds to exactly one solution pair $(r,x)$, so the equation has $p-1$ solution pairs in total. We split into the cases $x \equiv 0$ and $x \not\equiv 0$. For $x \equiv 0$, since $a$ is a quadratic residue, there are $2$ values of $r$. For $x \not\equiv 0$, there are $p-1-2$ pairs, and each $r$ corresponds to two of them, giving $\dfrac{p-3}{2}$ values of $r$. In total, $2+\dfrac{p-3}{2}=\dfrac{p+1}{2}$ values make $r^2-a$ a quadratic residue. So each random try gives a quadratic non-residue with probability $\dfrac{p-1}{2p}$, and the expected number of tries is $\dfrac{2p}{p-1} \approx 2$.

???+ note "Proof"
    For convenience, first let $f(x)=x^2-(r^2-a)\in\mathbf{F}_p\lbrack x\rbrack$.
    
    We need to show that $(r-x)^{\frac{p+1}{2}} \bmod f(x)$ is a solution of the original equation and that it lies in $\mathbf{F}_p$. We start with the first claim, that is, $(r-x)^{p+1}\equiv a\pmod {f(x)}$. For this we first prove two lemmas:
    
    **Lemma 1:** $x^p \equiv -x \pmod {f(x)}$
    
    Proof:
    
    $$
    \begin{aligned}
    x^p&= x(x^2)^{\frac{p-1}{2}}\\
    &\equiv x(r^2-a)^{\frac{p-1}{2}}&\pmod{f(x)}&\quad (\because{x^2\equiv r^2-a\pmod{f(x)}})\\
    &\equiv -x&\pmod{f(x)}&\quad (\because{r^2-a}\text{ is quadratic non-residue})
    \end{aligned}
    $$
    
    **Lemma 2:** $(a+b)^p \equiv a^p+b^p \pmod p$
    
    By the binomial theorem, in every term except the first and the last, the factor $p$ in the numerator cannot be cancelled, so only $a^p+b^p$ is left.
    
    $$
    \begin{aligned}
    (a+b)^p&=\sum_{i=0}^p\binom{p}{i}a^ib^{p-i}\\
    &=\sum_{i=0}^p\frac{p!}{i!(p-i)!}a^ib^{p-i}\\
    &\equiv a^p+b^p\pmod p
    \end{aligned}
    $$
    
    With these two lemmas, we can prove the claim:
    
    $$
    \begin{aligned}
    (r-x)^{p+1}
    &= (r-x)^p(r-x)\\
    &\equiv (r^p-x^p)(r-x)&\pmod{f(x)}\\
    &\equiv (r+x)(r-x)&\pmod{f(x)}\\
    &= r^2-x^2\\
    &\equiv r^2-(r^2-a)&\pmod{f(x)}\\
    &= a\\
    \end{aligned}
    $$
    
    Next we prove by contradiction that the solution lies in $\mathbf{F}_p$, that is, its coefficient of $x$ is $0$.
    
    Suppose some $(a_0+a_1x)^2 \equiv a \pmod {f(x)}$ has $a_1 \not\equiv 0 \pmod p$, that is, $a_0^2+2a_0a_1x+a_1^2x^2 \equiv a \pmod {f(x)}$. Rearranging and simplifying gives:
    
    $$
    a_0^2+a_1^2(r^2-a)-a \equiv -2a_0a_1x \pmod {f(x)}
    $$
    
    The coefficient of $x$ on the left is $0$, so the coefficient of $x$ on the right is also $0$, that is, $a_0a_1 \equiv 0 \pmod p$. Since we assumed $a_1 \not\equiv 0 \pmod p$, we must have $a_0 \equiv 0 \pmod p$. Then $(a_1x)^2 \equiv a \pmod {f(x)}$, that is, $r^2-a \equiv aa_1^{-2} \pmod p$.
    
    Both $a$ and $a_1^{-2}$ are quadratic residues, so by the multiplicativity of the Legendre symbol, $aa_1^{-2}$ is also a quadratic residue. This contradicts $r^2-a$ being a quadratic non-residue. So the equation has no solution with a nonzero coefficient of $x$, and the coefficient of $x$ in our solution must be $0$.

??? example "Template problem [Luogu P5491 [Template] Quadratic Residue](https://www.luogu.com.cn/problem/P5491)"
    ```cpp
    --8<-- "docs/math/code/quad-residue/quad-residue_1.cpp"
    ```

### Bostan–Mori algorithm

This algorithm builds on Cipolla's algorithm. We turn the problem into a [linear recurrence with constant coefficients](../poly/linear-recurrence.md) and then apply the Bostan–Mori algorithm. Consider another common description of Cipolla's algorithm: $b=x^{\left(p+1\right)/2}\bmod{\left(x^2-tx+a\right)}$ is a solution of $b^2\equiv a\pmod{p}$[^ref3], where $x^2-tx+a\in \mathbf{F}_p\lbrack x\rbrack$ is an irreducible polynomial. The coefficient $t$ is again chosen at random. We skip the proof. Following the algorithm in the paper by Bostan and Mori[^ref4], the problem becomes finding one coefficient of the multiplicative inverse of a formal power series:

$$
b=\left\lbrack x^{(p+1)/2}\right\rbrack\dfrac{1}{1-tx+ax^2}
$$

and

$$
\left\lbrack x^n\right\rbrack\dfrac{k_0+k_1x}{1+k_2x+k_3x^2}=
\begin{cases}
\left\lbrack x^{(n-1)/2}\right\rbrack\dfrac{k_1-k_0k_2+k_1k_3x}{1+(2k_3-k_2^2)x+k_3^2x^2},&\text{if }n\bmod 2=1\\
\left\lbrack x^{n/2}\right\rbrack\dfrac{k_0+(k_0k_3-k_1k_2)x}{1+(2k_3-k_2^2)x+k_3^2x^2},&\text{else if }n\neq 0
\end{cases}
$$

When $n=0$, clearly $\left\lbrack x^0\right\rbrack\dfrac{k_0+k_1x}{1+k_2x+k_3x^2}=k_0$. This algorithm uses fewer multiplications than Cipolla's algorithm. For other algorithms with fewer multiplications, see Müller's paper[^ref2].

### Legendre's algorithm

Consider the congruence $x^2\equiv a\pmod p$, where $p$ is an odd prime and $a$ is a quadratic residue. Legendre's algorithm works like this: find $r$ such that $r^2-a$ is a quadratic non-residue, and let $a_0+a_1x=(r-x)^{\frac{p-1}{2}}\bmod (x^2-a)$. Then $a_0\equiv 0\pmod p$ and $a_1^{-2}\equiv a\pmod p$.

???+ note "Proof"
    Pick $b$ with $b^2\equiv a\pmod p$. Then $(r-b)(r+b)=r^2-a$ is a quadratic non-residue, so
    
    $$
    (r-b)^{\frac{p-1}{2}}(r+b)^{\frac{p-1}{2}}\equiv -1\pmod p
    $$
    
    There is a ring homomorphism
    
    $$
    \begin{aligned}
    \phi:\mathbf{F}_p\lbrack x\rbrack/(x^2-a)&\to \mathbf{F}_p\times \mathbf{F}_p\\
    x&\mapsto (b,-b)
    \end{aligned}
    $$
    
    Then
    
    $$
    \begin{aligned}
    (a_0+a_1b,a_0-a_1b)&=\phi(a_0+a_1x)\\
    &=\phi(r-x)^{\frac{p-1}{2}}\\
    &=((r-b)^{\frac{p-1}{2}},(r+b)^{\frac{p-1}{2}})\\
    &=(\pm 1,\mp 1)
    \end{aligned}
    $$
    
    So $2a_0=(\pm 1)+(\mp 1)=0$ and $2a_1b=(\pm 1)-(\mp 1)=\pm 2$.

### Tonelli–Shanks algorithm

The Tonelli–Shanks algorithm solves the congruence $x^2\equiv a\pmod p$ using discrete logarithms[^ref1], where $p$ is an odd prime and $a$ is a quadratic residue modulo $p$.

Let $p-1=m2^n$ with $m$ odd. Again, use random tries to find $r\in\mathbf{F}_p$ that is a quadratic non-residue. Let $g\equiv r^m\pmod p$ and $b\equiv a^{(m-1)/2}\pmod p$. Then there is an integer $e\in\lbrace 0,1,2,\dots ,2^n-1\rbrace$ with $ab^2\equiv g^e\pmod p$. If $a$ is a quadratic residue, then $e$ is even and $\left(abg^{-e/2}\right)^2\equiv a\pmod p$.

???+ note "Proof"
    By Fermat's little theorem,
    
    $$
    g^{2^n} \equiv r^{m2^n} = r^{p-1} \equiv 1 \pmod p.
    $$
    
    Since $r$ is a quadratic non-residue,
    
    $$
    g^{2^{n-1}} \equiv r^{m2^{n-1}} = r^{\frac{p-1}{2}} \equiv -1 \pmod p.  
    $$
    
    So the order of $g$ modulo $p$ is $2^n$. Also, $ab^2\equiv a^m\pmod p$ is a solution of $x^{2^n}\equiv 1\pmod p$, so $a^m$ is a power of $g$. Write $a^m\equiv g^e\pmod p$.
    
    Since $a$ is a quadratic residue,
    
    $$
    g^{e2^{n-1}} \equiv a^{m2^{n-1}} = a^{\frac{p-1}{2}} \equiv 1 \pmod p.
    $$
    
    By the properties of the order, $2^n\mid e2^{n-1}$, so $e$ is even. Therefore $abg^{-e/2}\bmod p$ is well-defined, and
    
    $$
    \left(abg^{-e/2}\right)^2 = a^2b^2g^{-e} \equiv a^{m+1}g^{-e} \equiv a \pmod p.
    $$

What remains is how to compute $e$. Tonelli and Shanks proposed finding $e$ one binary digit at a time. Write $e$ in binary as $e=e_0+2e_1+4e_2+\cdots$, where $e_k\in\lbrace 0,1\rbrace$. Since $a$ is a quadratic residue, $e_0=0$ at the start. Then we find each $e_k$ in turn using the following property:

$$
\left(g^eg^{-(e\bmod 2^k)}\right)^{2^{n-1-k}}\equiv g^{2^{n-1}\cdot e_k}\equiv 
\begin{cases}
1\pmod p,&\text{if }e_k=0\\
-1\pmod p,&\text{if }e_k=1
\end{cases}
$$

Here $g^e\equiv ab^2\pmod p$ is known, and $e\bmod 2^k$ can be computed from the earlier digits $e_0,e_1,\cdots,e_{k-1}$. In an implementation, we can simply maintain the product $g^eg^{-(e\bmod 2^k)}\bmod p$ directly.

## Exercises

-   [Luogu P5491 [Template] Quadratic Residue](https://www.luogu.com.cn/problem/P5491)
-   [Timus 1132 Square Root](https://acm.timus.ru/problem.aspx?space=1&num=1132)

## References and notes

1.  [Quadratic residue - Wikipedia](https://en.wikipedia.org/wiki/Quadratic_residue)
2.  [Euler's criterion - Wikipedia](https://en.wikipedia.org/wiki/Euler%27s_criterion)

[^ref1]: Daniel. J. Bernstein. Faster Square Roots in Annoying Finite Fields.

[^ref2]: S. Müller, On the computation of square roots in finite fields, Design, Codes and Cryptography, Vol.31, pp. 301-312, 2004.

[^ref3]: A. Menezes, P. van Oorschot and S. Vanstone. Handbook of Applied Cryptography, 1996.

[^ref4]: Alin Bostan, Ryuhei Mori. A Simple and Fast Algorithm for Computing the N-th Term of a Linearly Recurrent Sequence. Available at <https://arxiv.org/abs/2008.08822>.

[^ref5]: [Proofs of quadratic reciprocity - Wikipedia](https://en.wikipedia.org/wiki/Proofs_of_quadratic_reciprocity)

[^ref6]: Carl Friedrich Gauss. Untersuchungen über höhere Arithmetik, 1965. Page 458-462.

[^ref7]: Kobi Kremnizer.[Lectures in number theory 2022](https://courses.maths.ox.ac.uk/pluginfile.php/29788/mod_resource/content/1/numbertheory-2022.pdf). Proposition 4.3.
