## Polynomials and generating functions

Working with polynomials, with finitely or infinitely many terms, is an important part of OI mathematics, especially of generating functions.

Polynomial algorithms built on the [fast Fourier transform](./fft.md) give competitive programmers the power to work with generating functions directly.

## Basic concepts

For a sum $\sum a_nx^n$ with finitely many terms, we call it a polynomial and write $f(x)=\sum_{n=0}^m a_nx^n$.

A sum of countably many terms is called a series. In the sum $\sum_{n=0}^\infty a_nx^n$, every term is a constant coefficient times a power of $x$ with a non-negative integer exponent. A series of this form is called a power series.

When studying polynomial arithmetic, we first look at the simpler case of polynomials; the idea of a power series is only used to make things easier to understand. Convergence and divergence of power series are studied further in mathematical analysis.

For the general definitions of rings, fields and related structures, see [Basic concepts of abstract algebra](../algebra/basic.md).

For a general ring $R$, we define the **polynomial ring** $R[x]$ over $R$.

Each element $f$ is called a **polynomial** over $R$, and can be written as

$$
f=\left<f_0,f_1,f_2,\cdots,f_n\right>\quad(f_0,f_1,f_2,\cdots,f_n\in R)
$$

In other words, we define a polynomial directly as its sequence of coefficients. It can also be written as

$$
f(x)=f_0+f_1x+f_2x^2+\cdots+f_nx^n
$$

Here we treat $x$ only as a **formal symbol**, a marker for the position of each coefficient.

If we also allow infinitely many terms, that is,

$$
f(x)=f_0+f_1x+f_2x^2+\cdots
$$

then we get the **formal power series ring** $R[[x]]$. Each element $f$ in it is called a **formal power series**, or just a power series below.

### Degree of a polynomial

For a polynomial $f(x)$, the exponent of its highest-order term is called the **degree** of the polynomial, written $\operatorname{deg}{f}$.

### Polynomial multiplication

The most central operation is multiplying two polynomials. Given polynomials $f(x)$ and $g(x)$:

$$
\begin{alignedat}{3}
f(x)&=a_0+a_1x+\dots+a_nx^n\quad \quad &(1)\\
g(x)&=b_0+b_1x+\dots+b_mx^m\quad \quad &(2)
\end{alignedat}
$$

we want to compute the polynomial $Q(x)=f(x)\cdot g(x)$:

$$
\boxed {Q(x) = \sum \limits_ {i = 0} ^ n \sum \limits_ {j = 0 } ^ m a_i b_j x ^ {i + j}} = c_0 + c_1 x + \dots + c_ {n + m} x ^ {n + m}
$$

Multiplication of polynomials or power series is associative and distributes over addition. If $R$ is a commutative ring or a ring with identity, multiplication is correspondingly commutative or has an identity element.

If $R$ has a $2^n$-th root of unity, the [fast Fourier transform](./fft.md) lets us compute the product of two polynomials of degree $2^n$ in $O(n2^n)$ time instead of $O(2^{2n})$.

### Composition

Define powers of an element $f$ of $R[[x]]$ as

$$
f^1=f,f^k=f^{k-1}\times f
$$

Based on this, define the composition of elements $f,g$ of $R[[x]]$ as

$$
(f\circ g)(x)=f(g(x))=f_0+\sum_{k=1}^{+\infty}f_kg^k(x)
$$

We say $f\circ g$ exists if and only if $f$ has finitely many terms or $g_0=0$. This way, no limits over $R$ are involved.

$\circ$ is associative (when both $(f\circ g)\circ h$ and $f\circ (g\circ h)$ exist), but not commutative. When $R$ is a ring with identity, $\circ$ has the identity element $1\times x$.

Polynomial composition (and compositional inverse) can be done in $\Theta(n\log^2 n)$. This method was proposed by Yasunori Kinoshita and Baitian Li in 2024; see [Formal power series composition | compositional inverse](./comp-rev.md).

### Derivative

Even though limits may not even exist in a general ring,  
we can still define the **formal derivative** of a formal power series as

$$
\left(\sum_{k=0}^{+\infty}f_kx^k\right)'=\sum_{k=1}^{+\infty}kf_kx^{k-1}
$$

where

$$
kf_k=\underbrace{f_k+f_k+\cdots+f_k}_{k \text{ copies of } f_k}
$$

The basic rules of differentiation, namely the sum rule, the product rule and the chain rule (when composition is allowed), still hold.

If division is allowed in $R$, we can define the **formal indefinite integral** of a formal power series in a similar way.

### Multiplicative inverse

From the example

$$
\dfrac{1}{1-x}=1+x+x^2+\cdots
$$

we see that the reciprocal of a polynomial can expand into an infinite series. A reciprocal exists if and only if the constant term is not $0$, and the reciprocal also has a non-zero constant term.

So we define: for a formal power series $f$ with $f_0\not=0$, its **multiplicative inverse** $f^{-1}$ is another formal power series such that

$$
f\times f^{-1}=f^{-1}\times f=1
$$

Expanding this with the definition of formal power series multiplication gives a recurrence for the coefficients of $f^{-1}$:

$$
f^{-1}_0=\dfrac{1}{f_0},f^{-1}_n=\dfrac{-1}{f_0}\sum_{k=0}^{n-1}f^{-1}_kf_{n-k}
$$

Computing the first $n$ terms directly with this recurrence takes $O(n^2)$. [Using FFT](./elementary-func.md#polynomial-inverse) gives an $O(n\log n)$ algorithm.

???+ note "Note"
    It is easy to see that the reciprocal of $f(x)$ is just the infinite Maclaurin expansion of $\frac{1}{f(x)}$ (the infinite Taylor expansion at $x=0$).

### Common power series expansions

In mathematical analysis, a function of one variable that is differentiable a certain number of times at a point or on an interval can be expanded as a polynomial in that range. This is usually called a Taylor expansion. If the expansion is at $0$, it is also called a Maclaurin expansion.

If the function is infinitely differentiable, it can be expanded as a power series. The most common case is still the expansion at $0$.

In complex analysis, some functions cannot be Taylor-expanded at singular points, but they can still be Laurent-expanded.

The equations below only hold where the power series converge, and do not hold where they diverge. We only write the expansions here and do not discuss the regions of convergence.

There are two basic expansions, the exponential function and the power function:

$$
\mathrm{e}^x=1+x+\frac{1}{2!}x^2+\ldots+\frac{1}{n!}x^n+\ldots
$$

$$
(1+x)^a=1+ax+\frac{a(a-1)}{2!}x^2+\ldots+\frac{a(a-1)\ldots(a-n+1)}{n!}x^n+\ldots
$$

More expansions are often derived from these two. For example, sine and cosine come from substituting complex numbers into the exponential function:

$$
\cos x=1-\frac{1}{2!}x^2+\frac{1}{4!}x^4+\ldots+\frac{(-1)^n}{(2n)!}x^{2n}+\ldots
$$

$$
\sin x=x-\frac{1}{3!}x^3+\frac{1}{5!}x^5+\ldots+\frac{(-1)^n}{(2n+1)!}x^{2n+1}+\ldots
$$

The logarithm, arctangent and arcsine come from integration:

$$
\frac{1}{1+x}=1-x+x^2+\ldots+{(-1)}^n x^n+\ldots
$$

$$
\ln(1+x)=x-\frac{1}{2}x^2+\frac{1}{3}x^3+\ldots+\frac{{(-1)}^{n-1}}{n}x^n+\ldots
$$

$$
\frac{1}{1+x^2}=1-x^2+x^4+\ldots+{(-1)}^n x^{2n}+\ldots
$$

$$
\arctan x=x-\frac{1}{3}x^3+\frac{1}{5}x^5+\ldots+\frac{{(-1)}^{n}}{2n+1}x^{2n+1}+\ldots
$$

$$
\frac{1}{\sqrt{1+x}}=1-\frac{1}{2}x+\frac{3}{8}x^2+\ldots+{(-1)}^n\frac{(2n)!}{{(n!)}^2 4^n} x^{n}+\ldots
$$

$$
\frac{1}{\sqrt{1-x^2}}=1+\frac{1}{2}x^2+\frac{3}{8}x^4+\ldots+\frac{(2n)!}{{(n!)}^2 4^n} x^{2n}+\ldots
$$

$$
\arcsin x=x+\frac{1}{6}x^3+\frac{3}{40}x^5+\ldots+\frac{(2n)!}{{(n!)}^2(2n+1)4^n} x^{2n+1}+\ldots
$$

### Compositional inverse

The **compositional inverse** generalizes the idea of an inverse function to the ring of formal power series.

For a formal power series $f$ with $f_0=0$ and $f_1\not=0$, its compositional inverse is the formal power series $g$ such that $g(f(x))=f(g(x))=x$. Lagrange inversion gives, for any integers $n,k$,

$$
n[x^n]f^k=k[x^{n-k}]\left(\dfrac{x}{g}\right)^n
$$

where $[x^k]f(x)$ denotes the coefficient of $x^k$ in $f(x)$.

### Polynomial divisibility

For polynomials $f(x)$ and $g(x)$, if there is a polynomial $h(x)$ such that:

$$
f(x)=g(x)h(x)
$$

then the polynomial $g(x)$ divides the polynomial $f(x)$.

Clearly, $g(x)$ divides $f(x)$ if and only if every root of $g(x)$ is a root of $f(x)$, and its multiplicity in $g(x)$ is at most its multiplicity in $f(x)$.

### Polynomial quotient and remainder

For polynomials $f(x), g(x)$, there are **unique** $Q(x), R(x)$ such that:

$$
\begin{aligned}
    f(x) &= Q(x) g(x) + R(x) \\
    \operatorname{deg}{R} &< \operatorname{deg}{g}
\end{aligned}
$$

When $\operatorname{deg}{f} \ge \operatorname{deg}{g}$, we have $\operatorname{deg}{Q} = \operatorname{deg}{f} - \operatorname{deg}{g}$; otherwise $Q(x) = 0$. We call $Q(x)$ the **quotient** of $f(x)$ divided by $g(x)$, and $R(x)$ the **remainder** of $f(x)$ divided by $g(x)$.

## Polynomials modulo a polynomial

Polynomials modulo a polynomial form a quotient of the polynomial ring, obtained by dividing the polynomial ring by the congruence equivalence relation.

In the division with remainder above, the polynomial $f(x)$ and its remainder $R(x)$ are congruent modulo the polynomial $g(x)$.

$$
f(x) \equiv R(x) \pmod{g(x)}
$$

This congruence also means that for any root $x_0$ of $g(x)$, substituting it into $f(x)$ and $R(x)$ gives the same value. That is:

$$
f(x_0)=R(x_0)
$$

Moreover, if the root $x_0$ has multiplicity $k$ in $g(x)$, that is, $(x-x_0)^k$ divides $g(x)$, then for every integer $t$ with $0 \le t < k$:

$$
f^{t}(x_0)=R^{t}(x_0)
$$

Here the notation means the $t$-th derivative.

Congruence modulo a polynomial also applies to power series. A power series with infinitely many terms can be congruent, modulo a specific polynomial, to a polynomial with finitely many terms. For example:

$$
1+x+x^2+x^3+\ldots \equiv 1+x+\ldots+x^{n-1} \pmod{x^n}
$$

Clearly all the remaining terms are divisible by $x^n$, so taking a power series modulo $x^n$ is the same as "truncating" it: we cut the infinite series down to its first $n$ terms and simply throw away the higher-order information.

In some specific cases, we can also take the modulus by other polynomials; the cases are explained below.

### Multipoint evaluation and interpolation of polynomials

**Multi-point evaluation** of a polynomial means: given a polynomial $f(x)$ and $n$ points $x_{1}, x_{2}, \dots, x_{n}$, compute

$$
f(x_{1}), f(x_{2}), \dots, f(x_{n})
$$

**Interpolation** of a polynomial means: given $n+1$ points

$$
(x_{0}, y_{0}), (x_{1}, y_{1}), \dots, (x_{n}, y_{n})
$$

find a polynomial $f(x)$ of degree $n$ that passes through all these $n+1$ points.

In essence, these two operations convert a polynomial between its **coefficient representation** and its **point-value representation**. Multipoint evaluation converts the coefficient representation into the point-value representation, and interpolation converts the point-value representation into the coefficient representation.

???+ note "Note"
    From the power series point of view, multipoint evaluation "compresses" the information of infinitely many terms into finitely many point values, so some information is lost. Interpolation then restores a coefficient representation of the matching degree.
    
    In the evaluation and interpolation commonly used in programming, such as the discrete Fourier transform (and its inverse), the $n+1$ chosen points all have multiplicity $1$, i.e. they are pairwise distinct. This avoids the trouble of taking derivatives.
    
    This "compression" only guarantees agreement at the $n+1$ points. By the explanation of congruence modulo a polynomial above, if a power series $f(x)$ is evaluated at the points $x_0$ to $x_n$ and then interpolated to give a polynomial $R(x)$, then take the polynomial:
    
    $$
    g(x)=(x-x_0)\ldots(x-x_n)
    $$
    
    and we have:
    
    $$
    f(x) \equiv R(x) \pmod{g(x)}
    $$
    
    Since the degree of $R(x)$ is strictly less than that of $g(x)$, the $R(x)$ obtained by evaluation and interpolation is exactly the remainder. So in this situation, if the power series can be evaluated at the roots, it can be taken modulo the polynomial. A counterexample is:
    
    $$
    \frac{1}{1-x}=1+x+x^2+x^3+\ldots
    $$
    
    It cannot be evaluated at $x=1$, so the series $1+x+x^2+x^3+\ldots$ cannot be taken modulo the polynomial $x-1$.
    
    Since every derivative of a power series always has a value at $0$, taking the modulus by $x^n$ can always be computed, which matches the meaning of "truncation" above. The discrete Fourier transform (and its inverse) is equivalent to taking the modulus by the polynomial $x^n-1$.

### Factorization and the Euclidean algorithm

Many results from elementary number theory can be generalized to polynomials.

Over the complex numbers, the fundamental theorem of algebra says that for a polynomial $f$ of degree $n$, the equation

$$
f(x)=0
$$

has exactly $n$ solutions (counting repeated roots with multiplicity).

So $f(x)$ has a unique factorization over the complex numbers of the form

$$
a(x-x_1)^{c_1}(x-x_2)^{c_2}\cdots(x-x_m)^{c_m}
$$

$$
c_1+c_2+\cdots+c_m=n,x_1,x_2,\cdots,x_m \text{ pairwise distinct}
$$

By analogy with the greatest common divisor of positive integers, we get the [**greatest common divisor**](../number-theory/gcd.md) of polynomials  
(gcd). It can be computed with the Euclidean algorithm:

$$
\gcd(f,0)=f,\gcd(f,g)=\gcd(g,f\bmod g)
$$

This property generalizes to a more general setting:

> For the polynomial ring $P[x]$ over any field $P$,  
> every polynomial has a unique factorization, and the greatest common divisor can be computed with the Euclidean algorithm.
> Note that for polynomials over a general ring, this result may not hold.

When the Euclidean algorithm works, the extended Euclidean algorithm gives a particular solution $(P(x),Q(x))$ of the indeterminate equation

$$
f(x)P(x)+g(x)Q(x)=\gcd(f(x),g(x))
$$

and [Bézout's theorem](../number-theory/bezouts.md) decides whether the indeterminate equation

$$
f(x)P(x)+g(x)Q(x)=h(x)
$$

has a solution.

[HALF-GCD](https://loj.ac/p/172) lets us run the polynomial Euclidean algorithm in $O(n\log^2 n)$ time.

### Multiplicative inverse modulo a polynomial

Modulo a polynomial $h(x)$, a power series $f(x)$ sometimes has an inverse. The inverse is the remainder of the reciprocal of $f(x)$ modulo $h(x)$.

Equivalently, for a polynomial $f(x)$, if there is a $g(x)$ such that:

$$
\begin{aligned}
    f(x) g(x) & \equiv 1 \pmod{h(x)}
\end{aligned}
$$

then $g(x)$ is called the **inverse element** of $f(x)$ modulo $h(x)$. When the polynomial Euclidean algorithm works, the inverse exists if and only if $\gcd(f,h)=1$.

The inverse modulo a polynomial $h(x)$ is always unique. If the degree of $f(x)$ is also less than that of $h(x)$, then $g(x)$ and $f(x)$ are inverses of each other.

Following the idea of "truncation", the inverse modulo $x^n$ is usually written $f^{-1}(x)$, and this is the notion of inverse used by default in later sections. Unless stated otherwise, the modulus for an inverse means $x^n$.

???+ note "Note"
    One question is whether we can compute the "inverse" directly with some interpolation transform, for example by computing:
    
    $$
    IDFT\left(\frac{DFT(1)}{DFT(f(x))}\right)
    $$
    
    The answer is no. By the explanation above, the inverse computed directly with the discrete Fourier transform (and its inverse) is the inverse modulo the polynomial $x^n-1$, not the usual inverse modulo $x^n$. Also, the original polynomial may be $0$ at some of the points, so this computation may not even be possible.

## Generating functions

A generating function is a formal power series whose coefficients carry information about a sequence.

There are many kinds of generating functions, but most of them can be written in a single form:

$$
F(x)=\sum_n a_nk_n(x)
$$

where $k_n(x)$ is called the kernel function. Different kernel functions lead to different generating functions with different properties. For example:

1.  Ordinary generating function: $k_n(x)=x^n$.
2.  Exponential generating function: $k_n(x)=\dfrac{x^n}{n!}$.
3.  [Dirichlet generating function](../number-theory/dirichlet.md#dirichlet-generating-functions): $k_n(x)=\dfrac{1}{n^x}$.

## References and further reading

-   [**Picks's Blog**](https://picks.logdown.com)
-   [**Miskcoo's Space**](https://blog.miskcoo.com)
-   [**Polynomial ring - Wikipedia**](https://en.wikipedia.org/wiki/Polynomial_ring)
-   [**Formal power series - Wikipedia**](https://en.wikipedia.org/wiki/Formal_power_series#The_ring_of_formal_power_series)
-   "A Theoretical Framework for Computing Generating Functions in Informatics Competitions"
