author: iamtwz, aofall, CCXXXI, CoelacanthusHex, Great-designer, Marcythm, Persdre, shuzhouliu, Tiphereth-A, Xeonacid

## Definition

???+ abstract "Congruence equation"
    For a positive integer $m$ and a polynomial in one variable with integer coefficients $f(x)=\sum_{i=0}^n a_ix^i$, where the unknown $x\in\mathbf{Z}_m$, an equation of the form
    
    $$
    f(x)\equiv 0\pmod m\tag{1}
    $$
    
    is called a **congruence equation** in one unknown $x$ modulo $m$.
    
    If $a_n\not\equiv 0\pmod m$, the equation above is called a congruence equation of degree $n$.
    
    Systems of congruence equations are defined in the same way.

For linear congruence equations and systems of them, see [Linear Congruence Equations](./linear-equation.md) and [Chinese Remainder Theorem](./crt.md).

This page first studies when congruence equations are solvable and the structure of their solution sets, and then briefly introduces how to solve higher-degree congruence equations.

By the [Chinese remainder theorem](./crt.md), solving a congruence equation modulo a composite $m$ reduces to solving it modulo prime powers. So below we only cover the theory of congruence equations modulo prime powers and modulo primes.

## Congruence equations modulo prime powers

Below, assume the modulus is $m=p^e~(p\in\mathbf{P},~e\in\mathbf{Z}_{>1})$.

Note that if $x_0$ is a solution of

$$
f(x)\equiv 0\pmod{p^e}
$$

then $x_0$ is also a solution of

$$
f(x)\equiv 0\pmod{p^{e-1}}
$$

This suggests building solutions modulo higher prime powers from solutions modulo lower ones. We have the following theorem:

???+ note "Theorem 1 (Hensel's lemma)"
    For a prime $p$ and an integer $e>1$, take a polynomial with integer coefficients $f(x)=\sum_{i=0}^na_ix^i~(p^e\nmid a_n)$, and let $f'(x)=\sum_{i=1}^nia_ix^{i-1}$ be its derivative. Let $x_0$ be a solution of
    
    $$
    f(x)\equiv 0\pmod{p^{e-1}}\tag{2}
    $$
    
    Then:
    
    1.  If $f'(x_0)\not\equiv 0\pmod p$, there exists an integer $t$ such that
    
        $$
        x=x_0+p^{e-1}t \tag{3}
        $$
    
        satisfies
    
        $$
        f(x)\equiv 0\pmod{p^e} \tag{4}
        $$
    
        That is, $(3)$ gives a solution of $(4)$.
    2.  If $f'(x_0)\equiv 0\pmod p$ and $f(x_0)\equiv 0\pmod{p^e}$, then for $t=0,1,\dots,p-1$, every $x$ given by $(3)$ is a solution of $(4)$.
    3.  If $f'(x_0)\equiv 0\pmod p$ and $f(x_0)\not\equiv 0\pmod{p^e}$, then no solution of $(4)$ can be built from $(3)$.

???+ note "Proof"
    Suppose $(3)$ is a solution of $(4)$, that is,
    
    $$
    f(x_0+p^{e-1}t)\equiv 0\pmod{p^e}
    $$
    
    Rearranging gives
    
    $$
    f(x_0)+p^{e-1}tf'(x_0)\equiv 0\pmod{p^e}
    $$
    
    so
    
    $$
    tf'(x_0)\equiv -\frac{f(x_0)}{p^{e-1}}\pmod p\tag{5}
    $$
    
    1.  If $f'(x_0)\not\equiv 0\pmod p$, then equation $(5)$ in $t$ has a unique solution $t_0$. Substituting it into $(3)$, we can check that it is a solution of $(4)$.
    2.  If $f'(x_0)\equiv 0\pmod p$ and $f(x_0)\equiv 0\pmod{p^e}$, then every $t$ satisfies $(5)$. Substituting into $(3)$, we can check that all of them are solutions of $(4)$.
    3.  If $f'(x_0)\equiv 0\pmod p$ and $f(x_0)\not\equiv 0\pmod{p^e}$, then $(5)$ has no solution, so no solution of $(4)$ can be built from $(3)$.

This gives the following corollary:

???+ note "Corollary 1"
    For $p$, $e$, $f(x)$, $x_0$ as in Theorem 1,
    
    1.  If $s$ is a solution of $f(x)\equiv 0\pmod p$ and $f'(s)\not\equiv 0\pmod p$, then there exists $x_s\in\mathbf{Z}_{p^e}$ with $x_s\equiv s\pmod p$ such that $x_s$ is a solution of $(4)$.
    2.  If $f(x)\equiv 0\pmod p$ and $f'(x)\equiv 0\pmod p$ have no common solution, then $(4)$ and $f(x)\equiv 0\pmod p$ have the same number of solutions.

So we can reduce congruence equations modulo prime powers to congruence equations modulo primes.

## Congruence equations modulo primes

Below, let $p\in\mathbf{P}$ and let $f(x)=\sum_{i=0}^na_ix^i$ be a polynomial with integer coefficients, where $p\nmid a_n$ and $x\in\mathbf{Z}_p$.

???+ note "Theorem 2"
    If the equation
    
    $$
    f(x)\equiv 0\pmod p\tag{6}
    $$
    
    has $k$ distinct solutions $x_1,x_2,\dots,x_k~(k\leq n)$, then
    
    $$
    f(x)\equiv g(x)\prod_{i=1}^k(x-x_i)\pmod p,
    $$
    
    where $\deg g=n-k$ and $[x^{n-k}]g(x)=a_n$.

???+ note "Proof"
    Use induction on $k$.
    
    -   When $k=1$, polynomial division with remainder gives $f(x)=(x-x_1)g(x)+r$, where $r\in\mathbf{Z}$.
    
        Since $f(x_1)\equiv 0\pmod p$, we get $r\equiv 0\pmod p$, so $f(x)\equiv(x-x_1)g(x)\pmod p$.
    -   Assume the statement holds for $k-1$ ($k>1$). Now suppose $f(x)$ has $k$ distinct solutions $x_1,x_2,\dots,x_k$. Then $f(x)\equiv(x-x_1)h(x)\pmod p$, and so
    
        $$
        (\forall i=2,3,\dots,k),~~0\equiv f(x_i)\equiv (x_i-x_1)h(x_i)\pmod p
        $$
    
        Hence $h(x)$ has $k-1$ distinct solutions $x_2,x_3,\dots,x_k$. By the induction hypothesis,
    
        $$
        h(x)\equiv g(x)\prod_{i=2}^k(x-x_i)\pmod p
        $$
    
        where $\deg g=n-k$ and $[x^{n-k}]g(x)=a_n$.
    
        This proves the statement.

???+ note "Corollary 2"
    For a prime $p$,
    
    -   $(\forall x\in\mathbf{Z}),~~x^{p-1}-1 \equiv \prod_{i=1}^{p-1}(x-i)\pmod p$.
    -   ([Wilson's theorem](./factorial.md#wilsons-theorem)) $(p-1)! \equiv -1 \pmod p$.

???+ note "Theorem 3 (Lagrange's theorem)"
    Equation $(6)$ has at most $n$ distinct solutions.

???+ note "Proof"
    Suppose $f(x)$ has $n+1$ distinct solutions $x_1,x_2,\dots,x_{n+1}$. By Theorem 2 applied to $x_1,x_2,\dots,x_n$,
    
    $$
    f(x)\equiv a_n\prod_{i=1}^n(x-x_i)\pmod p
    $$
    
    Let $x=x_{n+1}$. Then
    
    $$
    0\equiv f(x_{n+1})\equiv a_n\prod_{i=1}^n(x_{n+1}-x_i)\pmod p
    $$
    
    But the right-hand side is clearly not a multiple of $p$, a contradiction.

???+ note "Corollary 3"
    If the congruence equation $\sum_{i=0}^nb_ix^i\equiv 0\pmod p$ has more than $n$ solutions, then
    
    $$
    (\forall i=0,1,\dots,n),~~p\mid b_i.
    $$

???+ note "Theorem 4"
    If the number of solutions of $(6)$ is not $p$, then there must be a polynomial $r(x)$ with integer coefficients and $\deg r<p$ such that $f(x)\equiv 0\pmod p$ and $r(x)\equiv 0\pmod p$ have the same solution set.

???+ note "Proof"
    We may assume $n\geq p$. Do polynomial division with remainder on $f(x)$:
    
    $$
    f(x)=g(x)\left(x^p-x\right)+r(x)
    $$
    
    where $\deg r<p$.
    
    By [Fermat's little theorem](./fermat.md), $x^p\equiv x\pmod p$ for every integer $x$, so
    
    -   if $r(x)\equiv 0\pmod p$, then by Corollary 2, $f(x)$ has $p$ distinct solutions;
    -   if $r(x)\not\equiv 0\pmod p$, then since $f(x)\equiv r(x)\pmod p$, $f(x)$ and $r(x)$ have the same solution set.

We can use this theorem to lower the degree of a congruence equation.

???+ note "Theorem 5"
    Let $n\leq p$. Then the equation
    
    $$
    x^n+\sum_{i=0}^{n-1}a_ix^i\equiv 0\pmod p\tag{7}
    $$
    
    has $n$ solutions if and only if there exist polynomials with integer coefficients $q(x)$, $r(x)~(\deg r < n)$ such that
    
    $$
    x^p-x=f(x)q(x)+pr(x). \tag{8}
    $$

???+ note "Proof"
    -   Necessity: by polynomial division, there exist polynomials with integer coefficients $q(x)$, $r_1(x)~(\deg r_1 < n)$ such that
    
        $$
        x^p-x=f(x)q(x)+r_1(x).
        $$
    
        If $(7)$ has $n$ solutions, then $r_1\equiv 0\pmod p$ also has these same $n$ solutions. By Corollary 3, there is a polynomial $r(x)$ with integer coefficients such that $r_1(x)=pr(x)$, which proves the claim.
    -   Sufficiency: if $(8)$ holds, then by [Fermat's little theorem](./fermat.md), for every integer $x$,
    
        $$
        0\equiv x^p-x\equiv f(x)q(x)\pmod p.
        $$
    
        That is, $f(x)q(x)\equiv 0\pmod p$ has $p$ solutions.
    
        Let $s$ be the number of solutions of $(7)$. By Lagrange's theorem, $s\leq n$.
    
        Also, since $\deg q=p-n$, Lagrange's theorem says $q(x)\equiv 0\pmod p$ has at most $p-n$ solutions. The solution set of $f(x)q(x)\equiv 0\pmod p$ is the union of the solution sets of $f(x)\equiv 0\pmod p$ and $q(x)\equiv 0\pmod p$, so $s+(p-n)\geq p$, which gives $s\geq n$.
    
        Therefore $s=n$.

For a polynomial that is not monic, since $\mathbf{Z}_p$ is a field, we can turn it into a monic polynomial, and then the theorem applies.

???+ note "Theorem 6"
    Let $n\mid p-1$ and $p\nmid a$. Then the equation
    
    $$
    x^n\equiv a\pmod p\tag{9}
    $$
    
    has a solution if and only if
    
    $$
    a^{\frac{p-1}{n}}\equiv 1\pmod p.
    $$
    
    Moreover, if $(9)$ has a solution, it has exactly $n$ solutions.

???+ note "Note"
    For the exact structure of the solution set of $(9)$, see [k-th Power Residues](./residue.md).

???+ note "Proof"
    -   Necessity: if $(9)$ has a solution $x_0$, then
    
        $$
        a^{\frac{p-1}{n}}\equiv {\left(x_0^n\right)}^{\frac{p-1}{n}}\equiv 1\pmod p
        $$
    -   Sufficiency: if $a^{\frac{p-1}{n}}\equiv 1\pmod p$, then
    
        $$
        \begin{aligned}
            x^p-x&=x\left(x^{p-1}-1\right)\\
            &=x\left(\left(x^n\right)^{\frac{p-1}{n}}-a^{\frac{p-1}{n}}+a^{\frac{p-1}{n}}-1\right)\\
            &=\left(x^n-a\right)P(x)+x\left(a^{\frac{p-1}{n}}-1\right)\\
        \end{aligned}
        $$
    
        where $P(x)$ is some polynomial with integer coefficients. So by Theorem 5, $(9)$ has $n$ solutions.

## Solving higher-degree congruence equations (and systems)

First, using the [Chinese remainder theorem](./crt.md), we can turn a **system of congruence equations** into single **congruence equations**, and turn a congruence equation modulo a **composite** $m$ into congruence equations modulo **prime powers**. Then, using [Theorem 1](#congruence-equations-modulo-prime-powers), we turn a congruence equation modulo a **prime power** into one modulo a **prime**.

Combining the theorems on congruence equations modulo primes, we only need to consider how to solve

$$
x^n+\sum_{i=0}^{n-1}a_ix^i\equiv 0\pmod p
$$

where $p$ is prime and $n<p$.

By substituting $x-\dfrac{a_{n-1}}{n}$ for $x$, we can eliminate the $x^{n-1}$ term, so we only need to consider how to solve

$$
x^n+\sum_{i=0}^{n-2}a_ix^i\equiv 0\pmod p\tag{10}
$$

where $p$ is prime and $n<p$.

-   If $n=1$, see [Linear Congruence Equations](./linear-equation.md).
-   If $n=2$, see [Quadratic Residues](./quad-residue.md).
-   If $(10)$ can be rewritten as

    $$
    x^n\equiv a\pmod p,
    $$

    see [k-th Power Residues](./residue.md).

## References

1.  [Congruence Equation -- from Wolfram MathWorld](https://mathworld.wolfram.com/CongruenceEquation.html)
2.  [Lagrange's theorem (number theory) - Wikipedia](https://en.wikipedia.org/wiki/Lagrange%27s_theorem_%28number_theory%29)
3.  Pan Chengdong, Pan Chengbiao. Elementary Number Theory.
4.  Feng Keqin. Elementary Number Theory and Its Applications.
5.  Min Sihe, Yan Shijian. Elementary Number Theory.
