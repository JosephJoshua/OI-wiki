author: billchenchina, c-forrest, CCXXXI, danielqfmai, Enter-tainer, Great-designer, HeRaNO, lychees, Menci, Nanarikom, ouuan, shuzhouliu, sshwy, Tiphereth-A

This page introduces Dirichlet convolution and Dirichlet generating functions.

## Dirichlet convolution

The **Dirichlet convolution** of arithmetic functions $f(n)$ and $g(n)$, written $f \ast g$, is the arithmetic function defined by

$$
(f \ast g)(n) = \sum_{k\mid n}f(k)g\left(\dfrac{n}{k}\right) = \sum_{k\ell=n}f(k)g(\ell).
$$

Dirichlet convolution is an important operation on arithmetic functions. Many properties of arithmetic functions are discovered through it.

???+ example "Examples"
    1.  The unit function $\varepsilon$ is the Dirichlet convolution of the Möbius function $\mu$ and the constant function $1$:
    
        $$
        \varepsilon=\mu \ast 1 \iff\varepsilon(n)=\sum_{d\mid n}\mu(d).
        $$
    
    2.  The divisor-counting function $\tau$ is the Dirichlet convolution of the constant function $1$ with itself:
    
        $$
        \tau=1 \ast 1 \iff \tau(n)=\sum_{d\mid n}1.
        $$
    
    3.  The divisor-sum function $\sigma$ is the Dirichlet convolution of the identity function $\mathrm{id}$ and the constant function $1$:
    
        $$
        \sigma=\mathrm{id} \ast 1 \iff\sigma(n)=\sum_{d\mid n}d.
        $$
    
    4.  Euler's totient function $\varphi$ is the Dirichlet convolution of the identity function $\mathrm{id}$ and the Möbius function $\mu$:
    
        $$
        \varphi=\mathrm{id}\ast \mu \iff\varphi(n)=\sum_{d\mid n}d\cdot\mu\left(\frac{n}{d}\right).
        $$

[Möbius inversion](./mobius.md) is exactly the use of $\varepsilon=\mu \ast 1$ to transform identities between arithmetic functions.

### Properties

Dirichlet convolution has a number of algebraic properties.

???+ note "Theorem"
    Let $f,g,h$ be arithmetic functions. Then:
    
    1.  **Commutativity**: $f\ast g=g\ast f$.
    2.  **Associativity**: $(f\ast g)\ast h=f\ast(g\ast h)$.
    3.  **Distributivity**: $(f+g)\ast h = f\ast h + g\ast h$.
    4.  **Identity**: $f\ast\varepsilon = \varepsilon \ast f = f$, where $\varepsilon(n) = [n=1]$ is the identity for convolution and $[\cdot]$ is the Iverson bracket.
    5.  **Inverse**: there exists $g$ with $f\ast g=g\ast f=\varepsilon$ if and only if $f(1)\neq 0$. Such a $g$ is called the **Dirichlet inverse** of $f$ and can be written $f^{-1}$. Moreover, the inverse $g$ satisfies the recurrence
    
        $$
        g(n) = \dfrac{\varepsilon(n) - \sum_{k\ell = n,~k\neq 1}f(k)g(\ell)}{f(1)}.
        $$

??? note "Proof"
    Commutativity follows from a direct computation:
    
    $$
    (f\ast g)(n) = \sum_{k\ell=n}f(k)g(\ell) = (g\ast f)(n).
    $$
    
    Associativity follows from a direct computation:
    
    $$
    ((f\ast g)\ast h)(n) = \sum_{k\ell m = n}f(k)g(\ell)h(m) = (f\ast (g\ast h))(n).
    $$
    
    Distributivity follows from a direct computation:
    
    $$
    \begin{aligned}
    ((f+g)\ast h)(n) &= \sum_{k\ell = n}(f(k) + g(k))h(\ell) \\
    &= \sum_{k\ell=n}f(k)h(\ell) + \sum_{k\ell=n}g(k)h(\ell) = (f\ast h+g\ast h)(n).
    \end{aligned}
    $$
    
    To check that $\varepsilon(n)$ is the identity, compute directly:
    
    $$
    (f\ast\varepsilon)(n) = \sum_{k\ell = n}f(k)\varepsilon(\ell) = f(n).
    $$
    
    The second equality holds because $\varepsilon(\ell)$ is nonzero only when $\ell=1$, that is, when $k=n$.
    
    Finally, we need to show that $f^{-1}$ exists if and only if $f(1)\neq 0$. For any $f$, suppose there is a $g$ with $f\ast g=\varepsilon$. This means
    
    $$
    (f\ast g)(n) = \sum_{k\ell = n}f(k)g(\ell) = \varepsilon(n).
    $$
    
    This is really a system of equations in the values $g(n)$, and we can solve it for $g(n)$ directly. In particular, for $n=1$ the equation becomes $f(1)g(1)=1$, so for $g$ to exist we need at least $f(1)\neq 0$. And as long as $f(1)\neq 0$, we can solve directly:
    
    $$
    g(n) = \dfrac{\varepsilon(n) - \sum_{k\ell = n,~k\neq 1}f(k)g(\ell)}{f(1)}.
    $$
    
    This can be used to compute the values $g(n)$ recursively. So the inverse $g$ exists if and only if $f(1)\neq 0$.

In the language of abstract algebra, these properties say that all arithmetic functions, under (pointwise) addition and Dirichlet convolution, form a [commutative ring](../algebra/basic.md#rings), and its units are exactly the functions that are nonzero at $n=1$. This ring is called the **Dirichlet ring**.

Multiplicative functions are a special kind of arithmetic function. They are closed under Dirichlet convolution and Dirichlet inverse.

???+ note "Theorem"
    Let $f,g$ be multiplicative functions. Then $f\ast g$ is also multiplicative. Moreover, the inverse $f^{-1}$ always exists, and it is also multiplicative.

??? note "Proof"
    For the first part, let $h=f\ast g$. A direct check shows that for all $n_1\perp n_2$,
    
    $$
    \begin{aligned}
    h(n_1)h(n_2) &= \left(\sum_{k_1\ell_1=n_1}f(k_1)g(\ell_1)\right)\left(\sum_{k_2\ell_2=n_2}f(k_2)g(\ell_2)\right)\\
    &= \sum_{k_1\ell_1=n_1,~k_2\ell_2=n_2}f(k_1)f(k_2)g(\ell_1)g(\ell_2)\\
    &= \sum_{k\ell = n_1n_2}f(k)g(\ell) \\
    &= h(n_1n_2).
    \end{aligned}
    $$
    
    The third equality uses the multiplicativity of $f,g$. The reasoning behind the change in summation order is this: as $k$ runs over the divisors of $n_1n_2$, the prime factors of $k$ split into two groups depending on whether they divide $n_1$ or $n_2$. Multiplying the primes in each group (with multiplicity) gives $k_1$ and $k_2$, which run over the divisors of $n_1$ and $n_2$ respectively. Conversely, from divisors $k_1$ of $n_1$ and $k_2$ of $n_2$, we always get a divisor $k=k_1k_2$ of $n_1n_2$.
    
    For the second part, let $g=f^{-1}$ and use mathematical induction. First, $g(1)=1/f(1)=1$. The recurrence for the inverse can then be written as
    
    $$
    g(n) = \varepsilon(n) - \sum_{k\ell = n,~k\neq 1} f(k)g(\ell).
    $$
    
    So for $n_1\perp n_2$ with $n_1n_2 > 1$,
    
    $$
    \begin{aligned}
    g(n_1n_2) &= -\sum_{k\ell=n_1n_2,~k\neq 1}f(k)g(\ell) \\
    &= -\sum_{k_1\ell_1=n_1,~k_2\ell_2=n_2,~k_1k_2\neq 1}f(k_1)f(k_2)g(\ell_1)g(\ell_2)\\
    &= f(1)f(1)g(n_1)g(n_2) - \sum_{k_1\ell_1=n_1,~k_2\ell_2=n_2}f(k_1)f(k_2)g(\ell_1)g(\ell_2)\\
    &= g(n_1)g(n_2) - \left(\sum_{k_1\ell_1=n_1}f(k_1)g(\ell_1)\right)\left(\sum_{k_2\ell_2=n_2}f(k_2)g(\ell_2)\right) \\
    &= g(n_1)g(n_2) - \varepsilon(n_1)\varepsilon(n_2)\\
    &= g(n_1)g(n_2).
    \end{aligned}
    $$
    
    The second equality uses the induction hypothesis: for $\ell_1\ell_2 < n_1n_2$ with $\ell_1\perp\ell_2$, we have $g(\ell_1\ell_2)=g(\ell_1)g(\ell_2)$.

In the language of abstract algebra, the multiplicative functions under Dirichlet convolution form a [subgroup](../algebra/group-theory.md#subgroups) of the multiplicative group of the Dirichlet ring.

Completely multiplicative functions are even more special.

???+ note "Theorem"
    Let $\alpha$ be a completely multiplicative function and $f,g$ arithmetic functions. Then:
    
    1.  Distributivity: $(\alpha f)\ast(\alpha g) = \alpha\cdot(f\ast g)$.
    2.  Inverse: $(\alpha f)^{-1}=\alpha f^{-1}$, provided $f^{-1}$ exists.
    3.  A multiplicative function $f$ is completely multiplicative if and only if $f^{-1}=\mu f$, where $\mu$ is the [Möbius function](./mobius.md#möbius-function).

??? note "Proof"
    For the first part, check directly:
    
    $$
    \begin{aligned}
    ((\alpha f)\ast(\alpha g))(n) &= \sum_{k\ell = n}(\alpha f)(k)(\alpha g)(\ell) \\
    &= \sum_{k\ell = n}\alpha(k)f(k)\alpha(\ell)g(\ell) \\
    &= \sum_{k\ell = n}\alpha(n)f(k)g(\ell) \\
    &= \alpha(n)(f\ast g)(n).
    \end{aligned}
    $$
    
    The third equality uses the defining property of a completely multiplicative function: $\alpha(n)=\alpha(k)\alpha(\ell)$ for all $n=k\ell$.
    
    For the second part, the first part gives
    
    $$
    (\alpha f)\ast(\alpha f^{-1}) = \alpha(f\ast f^{-1}) = \alpha\varepsilon = \varepsilon.
    $$
    
    The last equality only uses $\alpha(1)=1$. By the definition of the inverse, $(\alpha f)^{-1}=\alpha f^{-1}$.
    
    For the third part, the second part together with $1^{-1}=\mu$ shows that if $f$ is completely multiplicative, then
    
    $$
    f^{-1} = (1f)^{-1} = 1^{-1}\cdot f = \mu f.
    $$
    
    Here $1$ is the constant function. Conversely, suppose $f$ is multiplicative and $f^{-1}=\mu f$. To show that $f$ is completely multiplicative, it suffices to show $f(p^e)=f(p)^e$ for every prime $p$ and every $e\in\mathbf N_+$. We use induction on $e\in\mathbf N_+$. The base case $e=1$ is obvious. For any $e > 1$, the recurrence for the inverse gives
    
    $$
    \begin{aligned}
    f^{-1}(p^e) &= -\sum_{i=1}^{e}f(p^i)f^{-1}(p^{e-i}) \\
    &= -\sum_{i=1}^{e}f(p^i)\mu(p^{e-i})f(p^{e-i})\\
    &= -f(p^e)f(1)\mu(1) - f(p^{e-1})\mu(p)f(p)\\
    &= -f(p^e) + f(p)^e.
    \end{aligned}
    $$
    
    The last equality uses the induction hypothesis $f(p^{e-1})=f(p)^{e-1}$. Using $f^{-1}=\mu f$, we get
    
    $$
    f^{-1}(p^e) = \mu(p^e)f(p^e) = 0.
    $$
    
    Substituting this into the previous equation gives
    
    $$
    f(p^e) = f(p)^e.
    $$
    
    So the inductive step holds, and the claim is proved.

In the language of abstract algebra, if $\alpha$ is completely multiplicative, then the map $f\mapsto \alpha f$ is an [endomorphism](../algebra/ring-theory.md#ideals) of the Dirichlet ring.

## Dirichlet generating functions

Closely related to Dirichlet convolution are Dirichlet generating functions.

The **Dirichlet generating function** (Dirichlet series generating function, DGF) of an arithmetic function $f(n)$ (that is, of the sequence $\{f(n)\}$) is defined as the formal Dirichlet series:

$$
F(s) = \sum_{n=1}^{\infty}\dfrac{f(n)}{n^s}.
$$

Here $s$ is a formal variable. For common Dirichlet generating functions, $s$ can often be viewed as a complex variable, which leads to the analytic properties of Dirichlet series, but that is beyond the scope of competitive programming.

The product of Dirichlet generating functions corresponds to the Dirichlet convolution of the arithmetic functions:

???+ note "Theorem"
    For arithmetic functions $f,g$ with Dirichlet generating functions $F,G$, the generating function of their Dirichlet convolution $f\ast g$ is $F\cdot G$.

??? note "Proof"
    Check directly:
    
    $$
    \begin{aligned}
    F(s)G(s) &= \left(\sum_{k=1}^\infty\dfrac{f(k)}{k^s}\right)\left(\sum_{\ell=1}^\infty\dfrac{g(\ell)}{\ell^s}\right)= \sum_{k=1}^\infty\sum_{\ell=1}^\infty\dfrac{f(k)g(\ell)}{(k\ell)^s}\\
    &= \sum_{n=1}^{\infty}\dfrac{\sum_{k\ell = n}f(k)g(\ell)}{n^s} = \sum_{n=1}^\infty\dfrac{(f\ast g)(n)}{n^s}.
    \end{aligned}
    $$

Using this correspondence between Dirichlet convolution and products of Dirichlet generating functions, we can understand the properties of Dirichlet convolution through generating functions. Since multiplication of formal Dirichlet series is commutative, associative and distributive over addition, Dirichlet convolution of arithmetic functions has the same algebraic properties.

### Euler product

The special nature of multiplicative functions also shows up in their Dirichlet generating functions. Because integers have [unique factorization](./basic.md#fundamental-theorem-of-arithmetic), the generating function $F(s)$ of a multiplicative function $f(n)$ can be written as:

$$
\begin{aligned}
F(s) &= \sum_{n=1}^{\infty}\dfrac{f(n)}{n^s} = \sum_{n=1}^{\infty}\prod_{p\in\mathbf P}\dfrac{f(p^{\nu_p(n)})}{p^{\nu_p(n)s}} = \prod_{p\in\mathbf P}\sum_{e=0}^{\infty}\dfrac{f(p^e)}{p^{es}}\\
&= \prod_{p\in\mathbf P}\left(1 + \dfrac{f(p)}{p^s} + \dfrac{f(p^2)}{p^{2s}} + \dfrac{f(p^3)}{p^{3s}} + \cdots\right).
\end{aligned}
$$

Here $\nu_p(n)$ is the exponent of $p$ in the prime factorization of $n$. This means $F(s)$ factors into a product of terms $F_p(s)=\sum_{e=0}^{\infty}f(p^e)p^{-es}$, where the arithmetic function of each $F_p(s)$ can be nonzero only at powers of $p$. This infinite product is called the **Euler product**. If $F(s)$ and $G(s)$ both factor this way, so does their product. Translated back to arithmetic functions, this says that the Dirichlet convolution of multiplicative functions is still multiplicative.

If $f(n)$ is also completely multiplicative, then $f(p^e)=f(p)^e$, and the formula simplifies further:

$$
F(s) = \prod_{p\in\mathbf P}\sum_{e=0}^{\infty}\dfrac{f(p)^e}{p^{es}} = \prod_{p\in\mathbf P}\left(1-\dfrac{f(p)}{p^s}\right)^{-1}.
$$

Unlike for multiplicative functions, this form of Dirichlet generating function for completely multiplicative functions is not closed under multiplication. So the Dirichlet convolution and Dirichlet inverse of completely multiplicative functions need not be completely multiplicative, but they are always multiplicative.

???+ example "Examples"
    1.  The unit function $\varepsilon(n)$ is completely multiplicative. Its Dirichlet generating function is the constant function in the indeterminate $s$:
    
        $$
        E(s) = \sum_{n=1}^{\infty}\dfrac{\varepsilon(n)}{n^s} = 1.
        $$
    
    2.  The constant function $1(n)$ is completely multiplicative. Its Dirichlet generating function is the Riemann ζ function:
    
        $$
        I(s) = \sum_{n=1}^{\infty}\dfrac{1}{n^s} = \prod_{p\in\mathbf P}\dfrac{1}{1-p^{-s}} = \zeta(s).
        $$
    
    3.  The Möbius function $\mu(n)$ is the Dirichlet inverse of the constant function. Its Dirichlet generating function is the reciprocal of $\zeta(s)$:
    
        $$
        M(s) = \sum_{n=1}^{\infty}\dfrac{\mu(n)}{n^s} = \prod_{p\in\mathbf P}(1-p^{-s}) = \dfrac{1}{\zeta(s)}.
        $$
    
    4.  The power function $\operatorname{id}_k(n)=n^k$ is completely multiplicative. In particular, for $k=0$ it is the constant function, and for $k=1$ it is the identity function. Its Dirichlet generating function is
    
        $$
        I_k(s) = \sum_{n=1}^{\infty}\dfrac{n^k}{n^s} = \prod_{p\in\mathbf P}\dfrac{1}{1-p^{k-s}} = \zeta(s-k).
        $$
    
    5.  Euler's totient function $\varphi(n)$ is multiplicative. Its Dirichlet generating function is
    
        $$
        \begin{aligned}
        \Phi(s) &= \prod_{p\in\mathbf P}\left(1+\dfrac{p-1}{p^s} + \dfrac{p(p-1)}{p^{2s}} + \dfrac{p^2(p-1)}{p^{3s}}+\cdots\right)\\
        &= \prod_{p\in\mathbf P}\left(\dfrac{1}{1-p^{1-s}}-\dfrac{1}{p^s}\dfrac{1}{1-p^{1-s}}\right) = \prod_{p\in\mathbf P}\dfrac{1-p^{-s}}{1-p^{1-s}} = \dfrac{\zeta(s-1)}{\zeta(s)}.
        \end{aligned}
        $$
    
        Combined with the Dirichlet generating function of the power functions, this gives $\mathrm{id} = \varphi\ast 1$.
    
    6.  The divisor function $\sigma_k(n)=\sum_{d\mid n}d^k$ is multiplicative. Its Dirichlet generating function is
    
        $$
        \begin{aligned}
        \Sigma_k(s) &= \prod_{p\in\mathbf P}\left(1+\dfrac{1+p^k}{p^s}+\dfrac{1+p^k+p^{2k}}{p^{2s}}+\dfrac{1+p^k+p^{2k}+p^{3k}}{p^{3s}}+\cdots\right) \\
        &= \prod_{p\in\mathbf P}\dfrac{1}{1-p^k}\left((1-p^k)+\dfrac{1-p^{2k}}{p^s}+\dfrac{1-p^{3k}}{p^{2s}}+\dfrac{1-p^{4k}}{p^{3s}}+\cdots\right)\\
        &= \prod_{p\in\mathbf P}\dfrac{1}{1-p^k}\left(\dfrac{1}{1-p^{-s}} - \dfrac{p^k}{1-p^{k-s}}\right)\\
        &= \prod_{p\in\mathbf P}\dfrac{1}{(1-p^{-s})(1-p^{k-s})} = \zeta(s-k)\zeta(s).
        \end{aligned}
        $$
    
        Combined with the Dirichlet generating function of the power functions, this gives $\sigma_k = \mathrm{id}_k\ast 1$, which is exactly the definition of $\sigma_k$.
    
    7.  The indicator function of squarefree numbers, $u(n)=|\mu(n)|=\mu^2(n)$, is multiplicative. Its Dirichlet generating function is
    
        $$
        U(s) = \prod_{p\in\mathbf P}(1+p^{-s}) = \prod_{p\in\mathbf P}\dfrac{1-p^{-2s}}{1-p^{-s}} = \dfrac{\zeta(s)}{\zeta(2s)}.
        $$

### Bell series

The Euler product shows that the Dirichlet generating function of a multiplicative function factors into local factors $F_p(s)$. If we only care about what happens at a single prime, we can treat $p^{-s}$ as one formal variable. This gives the Bell series.

For a multiplicative function $f$ and a prime $p$, the **Bell series** of $f$ at $p$ is the formal power series

$$
f_p(x) = \sum_{e=0}^{\infty} f(p^e)x^e = 1 + f(p)x + f(p^2)x^2 + \cdots.
$$

Comparing with the Euler product, $f_p(x)$ is just $F_p(s)$ with $p^{-s}$ replaced by $x$, that is, $F_p(s) = f_p(p^{-s})$, so

$$
F(s) = \prod_{p\in\mathbf P}f_p(p^{-s}).
$$

With this notation, we can see that Dirichlet convolution, once localized, is just ordinary multiplication of power series.

Translating the results about Dirichlet generating functions to Bell series gives the following properties:

1.  For multiplicative functions $f,g$ and any prime $p$, $(f\ast g)_p(x) = f_p(x)g_p(x)$.
2.  A multiplicative function $f$ is completely multiplicative if and only if $f_p(x) = \dfrac{1}{1-f(p)x}$ for every prime $p$.
3.  The Dirichlet inverse of a multiplicative function always exists, and $(f^{-1})_p(x) = \dfrac{1}{f_p(x)}$.

Since a multiplicative function is uniquely determined by its values at prime powers, multiplicative functions correspond one-to-one with their families of Bell series $\{f_p\}_{p\in\mathbf P}$. So many questions about Dirichlet convolution of multiplicative functions can be turned, prime by prime, into questions about formal power series. This is somewhat simpler in form than working with Dirichlet generating functions directly. For example, the third property says that to find a Dirichlet inverse, we only need to invert a formal power series for each prime. In actual computation, only the part with $p^e\le n$ is needed, so for each prime the series can be truncated at the $x^{\lfloor\log_p n\rfloor}$ term.

???+ example "Examples"
    The Bell series of the multiplicative functions from the earlier examples are:
    
    |    $f$   | $\varepsilon$ |        $1$       | $\mu$ | $\operatorname{id}_k$ |      $\varphi$      |         $\sigma_k$         | $\lvert\mu\rvert=\mu^2$ |
    | :------: | :-----------: | :--------------: | :---: | :-------------------: | :-----------------: | :------------------------: | :---------------------: |
    | $f_p(x)$ |      $1$      | $\dfrac{1}{1-x}$ | $1-x$ |  $\dfrac{1}{1-p^kx}$  | $\dfrac{1-x}{1-px}$ | $\dfrac{1}{(1-x)(1-p^kx)}$ |          $1+x$          |
    
    With this table, the common Dirichlet convolution identities can be checked directly. For example, $\mu\ast 1=\varepsilon$ corresponds to
    
    $$
    (1-x)\cdot\dfrac{1}{1-x} = 1,
    $$
    
    and $\varphi\ast 1=\operatorname{id}$ corresponds to
    
    $$
    \dfrac{1-x}{1-px}\cdot\dfrac{1}{1-x} = \dfrac{1}{1-px}.
    $$

### Applications

Dirichlet generating functions can be used to express an arithmetic function as a Dirichlet convolution.

For example, in Du's sieve, to compute prefix sums of an arithmetic function $f$, we need another arithmetic function $g$ such that both $f\ast g$ and $g$ have prefix sums that are fast to compute. Dirichlet generating functions can help find such a $g$.

Take the example problem from the Du's sieve section, [Luogu P3768 A Simple Math Problem](../number-theory/hyperbola.md#example-problems). We need to construct an arithmetic function $g(n)$ that meets the conditions above for $f(n)=n^2\varphi(n)$. Since $f$ is multiplicative, its Dirichlet generating function is

$$
F(s) = \prod_{p\in\mathbf P}\left(1 + \sum_{k=1}^{\infty}\dfrac{p^{3k-1}(p-1)}{p^{ks}}\right) = \prod_{p\in\mathbf P}\dfrac{1-p^{2-s}}{1-p^{3-s}} = \dfrac{\zeta(s-3)}{\zeta(s-2)}.
$$

Comparing with the Dirichlet generating functions of the power functions, if we take $g = \mathrm{id}_2$, then $f \ast g = \mathrm{id}_3$. Both have prefix sums that are fast to compute.

Since the arithmetic functions in typical problems are multiplicative, Bell series are often more convenient in practice. For example, the Bell series of $f(n)$ in the example above follows directly from $f(p^e)=p^{3e-1}(p-1)$:

$$
f_p(x) = 1 + \dfrac{p-1}{p}\sum_{e=1}^{\infty}(p^3x)^e = 1 + \dfrac{(p-1)p^2x}{1-p^3x} = \dfrac{1-p^2x}{1-p^3x}.
$$

Comparing with the Bell series of the power functions immediately gives $f \ast \mathrm{id}_2 = \mathrm{id}_3$.

## Computing Dirichlet convolutions

This section is about computing Dirichlet convolutions: given sequences $\{f(k)\}_{k=1}^n$ and $\{g(k)\}_{k=1}^n$, find the first $n$ terms $\{h(k)\}_{k=1}^n$ of the Dirichlet convolution $h=f\ast g$. The complexity of the algorithm varies a little depending on the properties of the functions involved.

### General case

If $f,g,h$ have no special properties, we can only compute the Dirichlet convolution from its definition:

$$
h(n) = \sum_{k\ell = n}f(k)g(\ell).
$$

Enumerate $k$ and $\ell$, and add the contribution $f(k)g(\ell)$ to $h(k\ell)$. The enumeration takes

$$
O\left(\sum_{k=1}^{n}\dfrac{n}{k}\right) = O(n\log n).
$$

Reference implementation:

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/dirichlet/dirichlet-1.cpp:core"
    ```

### Convolution with a multiplicative function

If $g$ is multiplicative, the Euler product can speed up the computation. Computing $h$ is the same as computing the coefficients of its Dirichlet generating function $H$. We have

$$
H(s) = F(s)G(s) = F(s)\prod_{p\in\mathbf P}G_p(s).
$$

Here $G_p(s)$ is a factor in the Euler product of $G(s)$. It contains only the coefficients at powers of $p$:

$$
G_p(s) = \sum_{p^k\le n}\dfrac{g(p^k)}{p^{ks}} = 1 + \dfrac{g(p)}{p^s} + \dfrac{g(p^2)}{p^{2s}} + \cdots.
$$

So, starting from $F(s)$, we can go through every prime $p$ not exceeding $n$ and multiply in $G_p(s)$ one at a time; this also gives the final result $H(s)$. Each multiplication by $G_p(s)$ just uses the brute-force enumeration from the general case. The total number of steps is

$$
\sum_{p\in\mathbf P,~p\le n}\sum_{k=1}^{\infty}\left\lfloor\dfrac{n}{p^k}\right\rfloor \le \sum_{p\in\mathbf P,~p\le n}\dfrac{n}{p-1} \le \sum_{p\in\mathbf P,~p\le n}\dfrac{2n}{p} \in O(n\log\log n).
$$

The estimate in the last step is the same as in the complexity proof of the [sieve of Eratosthenes](./sieve.md#sieve-of-eratosthenes). So this algorithm runs in $O(n\log\log n)$ time.

Reference implementation:

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/dirichlet/dirichlet-2.cpp:core"
    ```

In particular, when the multiplicative function $g$ is completely multiplicative or the Dirichlet inverse of one, for example $g = 1$ or $g = \mu$, the algorithm can be simplified further. In that case, $h = f\ast g$ can be computed with the [Dirichlet prefix sum / difference](./mobius.md#dirichlet-prefix-sums) algorithm, which has a smaller constant factor, though the time complexity is still $O(n\log\log n)$.

### When the result is multiplicative

Finally, consider the case where $h$ is multiplicative. In particular, when $f,g$ are both multiplicative, $h=f \ast g$ is multiplicative. To compute $h$, we only need its values at prime powers; the rest can then be computed with a [linear sieve](./sieve.md#linear-sieve) in $O(n)$ time. The value $h(p^e)$ at a prime power $p^e$ can be computed by brute force:

$$
h(p^e) = \sum_{i=0}^e f(p^i)g(p^{e-i}).
$$

These brute-force computations take this many steps:

$$
\begin{aligned}
\sum_{p\in\mathbf P,~p\le n}\sum_{e=1}^{\lfloor\log_p n\rfloor}(e+1) &\le \sum_{p\in\mathbf P,~p\le\sqrt{n}}2\lfloor\log_p n\rfloor^2 + \sum_{p\in\mathbf P,~\sqrt{n} < p\le n}2 \\
&\le 2\sqrt{n}(\log_2 n)^2 + 2n \in O(n).
\end{aligned}
$$

So the total time complexity of this algorithm is $O(n)$.

Reference implementation:

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/dirichlet/dirichlet-3.cpp:core"
    ```

## References and notes

-   [Dirichlet convolution - Wikipedia](https://en.wikipedia.org/wiki/Dirichlet_convolution)
-   [Dirichlet series - Wikipedia](https://en.wikipedia.org/wiki/Dirichlet_series)
-   [Euler product - Wikipedia](https://en.wikipedia.org/wiki/Euler_product)
-   [Bell series - Wikipedia](https://en.wikipedia.org/wiki/Bell_series)
-   [Dirichlet products and cumulative sums of arithmetic functions by maspy (Japanese)](https://maspypy.com/dirichlet-%e7%a9%8d%e3%81%a8%e3%80%81%e6%95%b0%e8%ab%96%e9%96%a2%e6%95%b0%e3%81%ae%e7%b4%af%e7%a9%8d%e5%92%8c)
-   [Du's sieve (+ Bell series + powerful numbers) by command\_block - Luogu](https://www.luogu.com.cn/article/ygfzawod)
