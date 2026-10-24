## Problem

Given a polynomial $G\left(x, y\right)$, the polynomial $f\left(x\right)$ is known to satisfy:

$$
G\left(x, f\left(x\right)\right)\equiv 0\pmod{x^{n}}
$$

and there is a value $f_1$ such that $G\left(x, y\right)$ satisfies the following conditions:

-   $G(0, f_1) = 0$;
-   $\dfrac{\partial G}{\partial y}(0, f_1) \neq 0$.

Find $f\left(x\right)$ modulo $x^{n}$.

## Newton's Method

We use doubling.

First, when $n=1$, a solution of $\left[x^{0}\right]G\left(x, f\left(x\right)\right)=0$ has to be found separately; the $f_1$ in the assumption is such a solution.

Suppose we already have the solution $f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)$ modulo $x^{\left\lceil\frac{n}{2}\right\rceil}$, and we want the solution $f\left(x\right) = f_n\left(x\right)$ modulo $x^{n}$.

Taylor-expand $G\left(x, f(x)\right)$ in $f(x)$ around $f(x)=f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)$:

$$
\sum_{i=0}^{+\infty}\frac{\frac{\partial^i G}{\partial y^i}\left(x, f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)}{i!}\left(f\left(x\right)-f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)^{i}\equiv 0\pmod{x^{n}}
$$

Since the lowest non-zero term of $f\left(x\right)-f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)$ has degree at least $\left\lceil\frac{n}{2}\right\rceil$, we have:

$$
\forall 2\leqslant i:\left(f\left(x\right)-f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)^{i}\equiv 0\pmod{x^{n}}
$$

So:

$$
\begin{aligned}
\sum_{i=0}^{+\infty}\frac{\frac{\partial^i G}{\partial y^i}\left(x, f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)}{i!}\left(f\left(x\right)-f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)^{i}&\equiv G\left(x, f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)+\frac{\partial G}{\partial y}\left(x, f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)\left[f\left(x\right)-f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right]\\
&\equiv 0\pmod{x^{n}}
\end{aligned}
$$

$$
f_n\left(x\right)\equiv f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)-\frac{G\left(x, f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)}{\frac{\partial G}{\partial y}\left(x, f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)}\pmod{x^{n}}
$$

or

$$
f_{2n}\left(x\right)\equiv f_n\left(x\right)-\frac{G\left(x, f_n\left(x\right)\right)}{\frac{\partial G}{\partial y}\left(x, f_n\left(x\right)\right)}\pmod{x^{2n}}
$$

## Example problems

### [Polynomial inverse](./elementary-func.md#polynomial-inverse)

Let the given function be $h\left(x\right)$. Then:

$$
G\left(x, y\right)=\frac{1}{y}-h\left(x\right)
$$

Applying Newton's Method gives:

$$
\begin{aligned}
    f_{2n}\left(x\right)&\equiv f_{n}\left(x\right)-\frac{1/f_{n}\left(x\right)-h\left(x\right)}{-1/f_{n}^{2}\left(x\right)}&\pmod{x^{2n}}\\
    &\equiv 2f_{n}\left(x\right)-f_{n}^{2}\left(x\right)h\left(x\right)&\pmod{x^{2n}}
\end{aligned}
$$

The time complexity is

$$
T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right)
$$

### [Polynomial square root](./elementary-func.md#polynomial-square-root)

Let the given function be $h\left(x\right)$. Then:

$$
G\left(x, y\right)=y^{2}-h\left(x\right)\equiv 0
$$

Applying Newton's Method gives:

$$
\begin{aligned}
    f_{2n}\left(x\right)&\equiv f_{n}\left(x\right)-\frac{f_{n}^{2}\left(x\right)-h\left(x\right)}{2f_{n}\left(x\right)}&\pmod{x^{2n}}\\
    &\equiv\frac{f_{n}^{2}\left(x\right)+h\left(x\right)}{2f_{n}\left(x\right)}&\pmod{x^{2n}}
\end{aligned}
$$

The time complexity is

$$
T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right)
$$

### [Polynomial exponential](./elementary-func.md#polynomial-logarithm--exponential)

Let the given function be $h\left(x\right)$. Then:

$$
G\left(x, y\right)=\ln{y}-h\left(x\right)
$$

Applying Newton's Method gives:

$$
\begin{aligned}
    f_{2n}\left(x\right)&\equiv f_{n}\left(x\right)-\frac{\ln{f_{n}\left(x\right)}-h\left(x\right)}{1/f_{n}\left(x\right)}&\pmod{x^{2n}}\\
    &\equiv f_{n}\left(x\right)\left(1-\ln{f_{n}\left(x\right)+h\left(x\right)}\right)&\pmod{x^{2n}}
\end{aligned}
$$

The time complexity is

$$
T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right)
$$

## Worked examples by hand

To make this easier to understand, here are a few examples that walk through the algorithm.

### Square root of a complex polynomial modulo a polynomial

Suppose $h$ is a complex polynomial not divisible by $x$ (it has a constant term). We want its square root modulo $x^n$.

We have the equation:

$$
G\left(f(x)\right) = f^2(x)-h(x) \equiv 0\pmod{x^{n}}
$$

Taylor-expanding $G$ gives the formula below. Note that this is an expansion in $f$, so all derivatives are partial derivatives with respect to $f$, and $x$ is treated as a constant here.

$$
G(f(x)) = \sum_{i=0}^{+\infty}\frac{G^{\left(i\right)}\left(f_{0}(x)\right)}{i!}\left(f(x)-f_{0}(x)\right)^{i}
= G(f_0(x)) + 2f_0(x)(f(x)-f_0(x)) + (f(x)-f_0(x))^2
$$

We compute by doubling. Suppose the intermediate results of the doubling are $f_0(x), f_1(x), \ldots, f_j(x)$. More rigorously, $f_j(x)$ is a complex polynomial with $G(f_j(x))\equiv 0\pmod{x^{2^j}}$, and to make it unique it also satisfies the following two conditions:

-   the degree of $f_{j}(x)$ is at most $2^j$;
-   $f_{j+k}(x)-f_j(x)\equiv 0\pmod{x^{2^j}}$ for all $k$.

Substituting $f_{j+1}(x)$ and $f_j(x)$ into the formula above gives:

$$
G(f_{j+1}(x)) = G(f_j(x)) + 2f_j(f_{j+1}(x)-f_j(x)) + (f_{j+1}(x)-f_{j}(x))^2  \equiv 0 \pmod{x^{2^{j+1}}}
$$

Clearly $f_{j+1}(x)-f_j(x)$ must be a multiple of $x^{2^j}$. So we get

$$
f_{j+1}(x) \equiv f_j(x) - \frac{f_j^2(x)-h(x)}{2f_j(x)} \equiv \frac{f_j(x)^2 + h(x)}{2f_j(x)} \pmod{x^{2^{j+1}}}
$$

If $f_j(x)$ exists, then $2f_j(x)$ is not divisible by $x$ (it has a constant term), so it must have an inverse modulo $x^{2^{j+1}}$. Therefore the sequence $f_0,f_1\ldots,f_j$ exists if and only if $f_0$ exists. A complex polynomial $h(x)$ not divisible by $x$ always has a square root modulo $x$, because $h(x)$ modulo $x$ is just an ordinary non-zero complex number, which always has two square roots. So this algorithm works for every $h(x)$ with a constant term.

Take $h(x)=x+1$ as an example:

-   $f_0(x)=1$,$f_1(x)=\dfrac{1^2+x+1}{2\times 1}\mod x^2 = \dfrac{1}{2}x+1$,$f_2(x)=\dfrac{\left(\dfrac{1}{2}x+1\right)^2+x+1}{2\times \left(\dfrac{1}{2}x+1\right)}\mod x^4 = \dfrac{1}{16}x^3-\dfrac{1}{8}x^2+\dfrac{1}{2}x+1$,$\ldots$
-   $f_0(x)=-1$,$f_1(x)=\dfrac{(-1)^2+x+1}{2\times (-1)}\mod x^2 = -\dfrac{1}{2}x-1$,$\ldots$ (the negation of the previous one)

You can check that both are correct sequences of modular square root polynomials.

### Square root of an integer modulo a prime power

Newton's method can also be carried over to integers modulo a power of a prime.
Suppose $h$ is a "convenient" integer not divisible by 3. ("Convenient" means "a solution must exist"; the exact condition is given below.) Suppose we want the square root $f$ of $h$ modulo $3^n$. We have the equation:

$$
G\left(f\right) = f^2-h \equiv 0\pmod{3^{n}}
$$

Taylor-expanding $G$ gives:

$$
G(f) = \sum_{i=0}^{+\infty}\frac{G^{\left(i\right)}\left(f_{0}\right)}{i!}\left(f-f_{0}\right)^{i}
= G(f_0) + 2f_0(f-f_0) + (f-f_0)^2
$$

We compute by doubling. Suppose the intermediate results of the doubling are $f_0, f_1, \ldots, f_j$. More rigorously, $f_j$ is an integer with $G(f_j)\equiv 0\pmod{3^{2^j}}$, and to make it unique it also satisfies the following two conditions:

-   $0 < f_{j} < 3^{2^j}$;
-   $f_{j+k}-f_j\equiv 0\pmod{3^{2^j}}$ for all $k$.

Substituting $f_{j+1}$ and $f_j$ into the formula above gives:

$$
G(f_{j+1}) = G(f_j) + 2f_j(f_{j+1}-f_j) + (f_{j+1}-f_{j})^2  \equiv 0 \pmod{3^{2^{j+1}}}
$$

Clearly $f_{j+1}-f_j$ must be a multiple of $3^{2^j}$. So we get

$$
f_{j+1} \equiv f_j - \frac{f_j^2-h}{2f_j} \equiv \frac{f_j^2 + h}{2f_j} \pmod{3^{2^{j+1}}}
$$

If $f_j$ exists, then $2f_j$ is not divisible by $3$, so it must have an inverse modulo $3^{2^{j+1}}$. Therefore the sequence $f_0,f_1\ldots,f_j$ exists if and only if $f_0$ exists. For an integer $h$ not divisible by 3, a square root modulo $3$ either does not exist or there are two of them. So the only condition for the whole algorithm to work is that $h$ has a square root modulo $3$.

Here is an actual computation with $h=46$.

-   $f_0=1$,$f_1=\dfrac{1^2+46}{2\times 1}\mod 9 = 1$,$f_2=\dfrac{1^2+46}{2\times 1}\mod 81 = 64$,$f_3=\dfrac{64^2+46}{2\times 64}\mod 6561 = 955$,$\ldots$
-   $f_0=2$,$f_1=\dfrac{2^2+46}{2\times 2}\mod 9 = 8$,$f_2=\dfrac{8^2+46}{2\times 8}\mod 81 = 17$,$f_3=\dfrac{17^2+46}{2\times 17}\mod 6561 = 5606$,$\ldots$ (the negation of the previous one)

You can check that both are correct sequences of modular square roots.

## Algebraic proof

This section extends the discussion above. Using the language of abstract algebra, we prove that as long as $f$ satisfies the initial-solution condition, Newton's method gives a solution for every $n$, and it finds all the solutions.

### Proof that a solution exists

???+ note "Lemma 1"
    Let $R$ be an [integral domain](../algebra/ring-theory.md#integral-domains) with a polynomial or [formal power series](../algebra/ring-theory.md#formal-power-series-rings) $f(X) = \sum_{i\geq 0}a_iX^i$, and let $r,p\in R$ be such that $f(r)\in Rp$ (that is, $r$ is a root of $f(X)$ modulo $p$) and $f'(r)\in R$ is invertible modulo $p$. Here $f'(X) := \sum_{i\geq 0}(i+1)a_{i+1}X^i$ is the **formal derivative** of $f(X)$. Then $f\left(r-\dfrac{f(r)}{f'(r)}\right) \equiv 0\pmod {p^2}$.

??? note "Proof"
    For all $s\in R$,
    
    $$
    \begin{aligned}
    f(r+sp) &= \sum_{i\geq 0}a_i(r+sp)^i \\
    &= \sum_{i\geq 0}a_ir^i + sp\sum_{i\geq 1}ia_ir^{i-1} + s^2p^2\left(\ldots\right) \\
    &= f(r) + spf'(r) + s^2p^2\left(\frac{f''(r)}{2!} + \cdots\right),
    \end{aligned}
    $$
    
    so
    
    $$
    f(r+sp) \in Rp^2 \iff f(r)+f'(r)sp \in Rp^2
    $$
    
    Since $f(r)\in Rp$ and $f'(r)$ is invertible, we can just take $sp = -\dfrac{f(r)}{f'(r)}$, where $\dfrac{1}{f'(r)}$ is the inverse modulo $p^2$. Since $f'(r)$ is invertible modulo $p$, it must also have an inverse modulo $p^2$: let $a,b,c\in R$ satisfy $af'(r) = bp+1$ and $f(r)=cp$. Then $\left(a^2f'(r)-2\right)f'(r) = b^2p^2+1$, so we can take $s=c(2-a^2f'(r))$.

For the polynomial ring $k[X]$ over a field $k$, suppose $G(X, Y)\in k[X, Y]$ and $f_n\in k[X]$ satisfy $G(X, f_n(X))\in k[X]X^n$. Applying Lemma 1 gives

$$
G\left(X, f_n(X) - \frac{G(X, f_n(X))}{\frac{\partial G}{\partial Y}(X, f_n(X))} \right)\equiv 0 \pmod {X^{2n}}
$$

The doubling only needs the initial condition that there is $f_1\in k$ with $G(X, f_1)\equiv 0\pmod X$ and $\dfrac{\partial G}{\partial Y}(X, f_1)\not\equiv 0\pmod X$. The latter condition guarantees that $\dfrac{\partial G}{\partial Y}$ has a non-zero constant term. Also, since $X\left| \dfrac{G(X, f_n(X))}{\frac{\partial G}{\partial Y}(X, f_n(X))} \right.$, for all $n$, $\dfrac{\partial G}{\partial Y}(X, f_n)$ is always invertible modulo $X^n$, which meets the condition for the next iteration.

### Proof that all solutions are found

???+ note "Lemma 2"
    Let $R$ be a [UFD](../algebra/ring-theory.md#unique-factorization-domains), and let $f,r,p$ be as in Lemma 1. Then the value $r-\dfrac{f(r)}{f'(r)}$ given by Lemma 1 is, modulo $p^{2}$, the unique value of $x$ satisfying both of the following conditions:
    
    -   $f(x)\in Rp^{2}$
    -   $x-r\in Rp$
    
    That is,
    
    $$
    \forall x\in R,\qquad p^2\mid f(x)\wedge p\mid (x-r) \implies x\equiv r-\dfrac{f(r)}{f'(r)} \pmod {p^2}
    $$

??? note "Proof"
    Let $s = -\dfrac{f(r)}{f'(r)p}$ and $u = r+sp$. Lemma 1 guarantees that $u$ satisfies both conditions, and that $f(r) + f'(r)sp \in Rp^{2}$.
    Let $v$ be a value satisfying the conditions above. Then $v = r+tp$ and $f(r) + f'(r)tp \in Rp^{2}$.
    So $f'(r)(t-s)p\in Rp^{2}$ and $v-u\in Rp^{2}$.

Newton's method is guaranteed to find all solutions modulo $X^{2^n}$. Suppose $G(X, h)\equiv 0\pmod {X^{2^n}}$. Let $h_{2^i} := h\pmod {X^{2^i}}$, then take $f_1 = h_1$ and run Newton's method. By Lemma 2, $f_{2^i} \equiv h_{2^i}\pmod {X^{2^i}}$, so we must have $f_{2^n} = h$.

The argument above also shows that when $\dfrac{\partial G}{\partial y}(0, y)$ is always invertible, the number of solutions of $G(X, f)\equiv 0\pmod {X^n}$ equals the number of solutions of $G(0, f)\equiv 0\pmod X$. This result is not trivial. See the example below.

??? example "An example where Newton's method fails and the number of solutions grows with the degree"
    Modulo $X$, the only square root of $X^2$ is $0$, but modulo $X^4$ the square roots of $X^2$ include $X, -X, X^3+X, \ldots$.
