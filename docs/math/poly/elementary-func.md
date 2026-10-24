author: 97littleleaf11, abc1763613206, CCXXXI, EndlessCheng, Enter-tainer, fps5283, Great-designer, H-J-Granger, hly1204, hsfzLZH1, huayucaiji, Ir1d, kenlig, Marcythm, ouuan, SamZhangQingChuan, shuzhouliu, sshwy, StudyingFather, test12345-pupil, Tiphereth-A, TrisolarisHD, untitledunrevised

This page covers the common elementary function operations on polynomials. Specifically, it contains:

1.  Polynomial inverse
2.  Polynomial square root
3.  Polynomial division
4.  Polynomial modulo
5.  Polynomial exponential
6.  Polynomial logarithm
7.  Polynomial trigonometric functions
8.  Polynomial inverse trigonometric functions

??? note "Elementary and non-elementary functions"
    Elementary functions are defined as follows[^ref1]:
    
    If a field $F$ has a map $u\to \partial u$ such that:
    
    1.  $\partial(u+v)=\partial u+\partial v$
    2.  $\partial(uv)=u\partial v+v\partial u$
    
    then the field is called a **differential field**.
    
    A function $u$ over a differential field $F$ is called elementary if it satisfies any one of the following:
    
    1.  $u$ is an algebraic function over $F$.
    2.  $u$ is an exponential function over $F$, that is, there is $a\in F$ such that $\partial u=u\partial a$.
    3.  $u$ is a logarithmic function over $F$, that is, there is $a\in F$ such that $\partial u=\frac{\partial a}{a}$.
    
    Common elementary functions include:
    
    1.  Algebraic functions: functions $f(x)$ for which there is a polynomial $P$ of finite degree with $P(f(x))=0$, such as $2x+1$,$\sqrt{x}$,$(1+x^2)^{-1}$,$|x|$.
    2.  Exponential functions
    3.  Logarithmic functions
    4.  Trigonometric functions
    5.  Inverse trigonometric functions
    6.  Hyperbolic functions
    7.  Inverse hyperbolic functions
    8.  Compositions of the above, such as:
    
        $$
        \frac{\mathrm{e}^{\tan x}}{1+x^2}\sin\left(\sqrt{1+\ln^2 x}\right)
        $$
    
        $$
        -\mathrm{i} \ln\left(x+\mathrm{i}\sqrt{1-x^2}\right)
        $$
    
    A common non-elementary function is:
    
    1.  The error function:
    
        $$
        \operatorname{erf}(x):=\frac{2}{\sqrt{\pi}}\int_{0}^{x}\exp\left(-t^2\right)\mathrm{d}t
        $$

## Polynomial inverse

Given a polynomial $f\left(x\right)$, find $f^{-1}\left(x\right)$.

### Solution

#### Doubling method

First, it is easy to see that

$$
\left[x^{0}\right]f^{-1}\left(x\right)=\left(\left[x^{0}\right]f\left(x\right)\right)^{-1}
$$

Suppose we have already found the inverse $f^{-1}_{0}\left(x\right)$ of $f\left(x\right)$ modulo $x^{\left\lceil\frac{n}{2}\right\rceil}$.
Then:

$$
\begin{aligned}
    f\left(x\right)f^{-1}_{0}\left(x\right)&\equiv 1 &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
    f\left(x\right)f^{-1}\left(x\right)&\equiv 1 &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
    f^{-1}\left(x\right)-f^{-1}_{0}\left(x\right)&\equiv 0 &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}
\end{aligned}
$$

Squaring both sides gives:

$$
f^{-2}\left(x\right)-2f^{-1}\left(x\right)f^{-1}_{0}\left(x\right)+f^{-2}_{0}\left(x\right)\equiv 0 \pmod{x^{n}}
$$

Multiplying both sides by $f\left(x\right)$ and rearranging gives:

$$
f^{-1}\left(x\right)\equiv f^{-1}_{0}\left(x\right)\left(2-f\left(x\right)f^{-1}_{0}\left(x\right)\right) \pmod{x^{n}}
$$

Then compute recursively.

**Time complexity**

$$
T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right)
$$

#### Newton's Method

See [Newton's Method](./newton.md#newtons-method).

#### Graeffe's method

To find $f^{-1}(x)\bmod x^{2n}$, consider

$$
\begin{aligned}
f^{-1}(x)\bmod x^{2n}&= f(-x)(f(x)f(-x))^{-1}\bmod x^{2n}\\
&=f(-x)g^{-1}(x^2)\bmod x^{2n}
\end{aligned}
$$

Since $f(x)f(-x)$ is an even function, we only need $g^{-1}(x)\bmod x^n$ to recover $g^{-1}(x^2)\bmod x^{2n}$. The time complexity is the same as above.

### Code

??? note "Polynomial inverse"
    ```cpp
    constexpr int MAXN = 262144;
    constexpr int mod = 998244353;
    
    using i64 = long long;
    using poly_t = int[MAXN];
    using poly = int *const;
    
    void polyinv(const poly &h, const int n, poly &f) {
      /* f = 1 / h = f_0 (2 - f_0 h) */
      static poly_t inv_t;
      std::fill(f, f + n + n, 0);
      f[0] = fpow(h[0], mod - 2);
      for (int t = 2; t <= n; t <<= 1) {
        const int t2 = t << 1;
        std::copy(h, h + t, inv_t);
        std::fill(inv_t + t, inv_t + t2, 0);
    
        DFT(f, t2);
        DFT(inv_t, t2);
        for (int i = 0; i != t2; ++i)
          f[i] = (i64)f[i] * sub(2, (i64)f[i] * inv_t[i] % mod) % mod;
        IDFT(f, t2);
    
        std::fill(f + t, f + t2, 0);
      }
    }
    ```

### Example problems

1.  Counting labeled simple connected undirected graphs: [POJ 1737 Connected Graph](http://poj.org/problem?id=1737)

## Polynomial square root

Given a polynomial $g\left(x\right)$, find $f\left(x\right)$ such that:

$$
f^{2}\left(x\right)\equiv g\left(x\right) \pmod{x^{n}}
$$

### Solution

#### Doubling method

First consider the case where $\left[x^0\right]g(x)$ is not $0$.

It is easy to see that:

$$
\left[x^0\right]f(x) = \sqrt{\left[x^0\right]g(x)}
$$

If $\left[x^0\right]g(x)$ has no square root, then the polynomial $g(x)$ has no square root.

> $\left[x^0\right]g(x)$ may have several square roots; choosing different ones gives different $f(x)$.

Suppose we have already found the square root $f_{0}\left(x\right)$ of $g\left(x\right)$ modulo $x^{\left\lceil\frac{n}{2}\right\rceil}$. Then:

$$
\begin{aligned}
    f_{0}^{2}\left(x\right)&\equiv g\left(x\right) &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
    f_{0}^{2}\left(x\right)-g\left(x\right)&\equiv 0 &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
    \left(f_{0}^{2}\left(x\right)-g\left(x\right)\right)^{2}&\equiv 0 &\pmod{x^{n}}\\
    \left(f_{0}^{2}\left(x\right)+g\left(x\right)\right)^{2}&\equiv 4f_{0}^{2}\left(x\right)g\left(x\right) &\pmod{x^{n}}\\
    \left(\frac{f_{0}^{2}\left(x\right)+g\left(x\right)}{2f_{0}\left(x\right)}\right)^{2}&\equiv g\left(x\right) &\pmod{x^{n}}\\
    \frac{f_{0}^{2}\left(x\right)+g\left(x\right)}{2f_{0}\left(x\right)}&\equiv f\left(x\right) &\pmod{x^{n}}\\
    2^{-1}f_{0}\left(x\right)+2^{-1}f_{0}^{-1}\left(x\right)g\left(x\right)&\equiv f\left(x\right) &\pmod{x^{n}}
\end{aligned}
$$

Then compute by doubling.

**Time complexity**

$$
T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right)
$$

A version with a smaller constant factor maintains $f^{-1}\left(x\right)$ alongside $f\left(x\right)$ during the doubling, instead of computing the inverse from scratch each time.

> When $\left[x^{0}\right]g\left(x\right)\neq 1$, you may need quadratic residues to compute $\left[x^{0}\right]f\left(x\right)$.

The method above needs the inverse of $f_{0}(x)$, so the constant term cannot be $0$.

If $\left[x^0\right]g(x) = 0$, factor $g(x)$ as $x^{k}h(x)$ with $\left[x^0\right]h(x) \not = 0$.

-   If $k$ is odd, $g(x)$ has no square root.

-   If $k$ is even, find the square root $\sqrt{h(x)}$ of $h(x)$, and then $f(x) \equiv x^{k/2} \sqrt{h(x)} \pmod{x^{n}}$.

??? note "Reference code for the Luogu template problem [P5205 [Template] Polynomial Square Root](https://www.luogu.com.cn/problem/P5205)"
    ```cpp
    --8<-- "docs/math/code/poly/sqrt/sqrt_1.cpp"
    ```

#### Newton's Method

See [Newton's Method](./newton.md#newtons-method).

### Example problems

1.  [Codeforces Round #250 E. The Child and Binary Tree](https://codeforces.com/contest/438/problem/E)

## Polynomial division & modulo

Given polynomials $f\left(x\right),g\left(x\right)$, find the quotient $Q\left(x\right)$ and remainder $R\left(x\right)$ of $f\left(x\right)$ divided by $g\left(x\right)$.

### Solution

Notice that if we can remove the effect of $R\left(x\right)$, the problem can be solved directly with the [polynomial inverse](#polynomial-inverse).

Consider the transformation

$$
f^{R}\left(x\right)=x^{\operatorname{deg}{f}}f\left(\frac{1}{x}\right)
$$

Looking at it, we see that it simply reverses the coefficients of $f\left(x\right)$.

Let $n=\operatorname{deg}{f},m=\operatorname{deg}{g}$.

In $f\left(x\right)=Q\left(x\right)g\left(x\right)+R\left(x\right)$, replace $x$ by $\frac{1}{x}$ and multiply both sides by $x^{n}$ to get:

$$
\begin{aligned}
    x^{n}f\left(\frac{1}{x}\right)&=x^{n-m}Q\left(\frac{1}{x}\right)x^{m}g\left(\frac{1}{x}\right)+x^{n-m+1}x^{m-1}R\left(\frac{1}{x}\right)\\
    f^{R}\left(x\right)&=Q^{R}\left(x\right)g^{R}\left(x\right)+x^{n-m+1}R^{R}\left(x\right)
\end{aligned}
$$

Note that in the equation above $R^{R}\left(x\right)$ is multiplied by $x^{n-m+1}$, so working modulo $x^{n-m+1}$ removes the effect of $R^{R}\left(x\right)$.

Also, since $Q^{R}\left(x\right)$ has degree $\left(n-m\right)<\left(n-m+1\right)$, $Q^{R}\left(x\right)$ is not affected.

Then:

$$
f^{R}\left(x\right)\equiv Q^{R}\left(x\right)g^{R}\left(x\right)\pmod{x^{n-m+1}}
$$

Use the polynomial inverse to find $Q\left(x\right)$, then substitute back to get $R\left(x\right)$.

**Time complexity**  $O\left(n\log{n}\right)$.

## Polynomial logarithm & exponential

Given a polynomial $f(x)$, find $\ln{f(x)}$ and $\exp{f(x)}$ modulo $x^{n}$.

### Solution

#### Basic method

=== "Polynomial logarithm"
    First, for a polynomial $f(x)$, if $\ln{f(x)}$ exists, then by its [definition](./intro.md#composition) it must satisfy:
    
    $$
    [x^{0}]f(x)=1
    $$
    
    Differentiating $\ln{f(x)}$ and then integrating gives:
    
    $$
    \begin{aligned}
        \frac{\mathrm{d} \ln{f(x)}}{\mathrm{d} x} & \equiv \frac{f'(x)}{f(x)} & \pmod{x^{n}} \\
        \ln{f(x)} & \equiv \int \mathrm{d} \ln{f(x)} \equiv \int\frac{f'(x)}{f(x)} \mathrm{d} x & \pmod{x^{n}}
    \end{aligned}
    $$
    
    Differentiating and integrating a polynomial take $O(n)$ time, and the inverse takes $O(n\log{n})$ time, so the polynomial $\ln$ takes $O(n\log{n})$ time.

=== "Polynomial exponential"
    First, for a polynomial $f(x)$, if $\exp{f(x)}$ exists, it must satisfy:
    
    $$
    [x^{0}]f(x)=0
    $$
    
    Otherwise the constant term of $\exp{f(x)}$ does not converge.
    
    Differentiating $\exp{f(x)}$ gives:
    
    $$
    \frac{\mathrm{d} \exp{f(x)}}{\mathrm{d} x} \equiv \exp{f(x)}f'(x)\pmod{x^{n}}
    $$
    
    Comparing coefficients on both sides gives:
    
    $$
    [x^{n-1}]\frac{\mathrm{d} \exp{f(x)}}{\mathrm{d} x} = \sum_{i = 0}^{n - 1} \left([x^{i}]\exp{f(x)}\right) \left([x^{n-i-1}]f'(x)\right)
    $$
    
    $$
    n[x^{n}]\exp{f(x)} = \sum_{i = 0}^{n - 1} \left([x^{i}]\exp{f(x)}\right) \left((n - i)[x^{n - i}]f(x)\right)
    $$
    
    This can be solved with divide-and-conquer FFT.
    
    **Time complexity**  $O(n\log^{2}{n})$.

#### Newton's Method

With [Newton's Method](./newton.md#newtons-method), the polynomial $\exp$ can be computed in $O(n\log{n})$ time.

### Code

??? note "Polynomial ln/exp"
    ```cpp
    constexpr int MAXN = 262144;
    constexpr int mod = 998244353;
    
    using i64 = long long;
    using poly_t = int[MAXN];
    using poly = int *const;
    
    void derivative(const poly &h, const int n, poly &f) {
      for (int i = 1; i != n; ++i) f[i - 1] = (i64)h[i] * i % mod;
      f[n - 1] = 0;
    }
    
    void integrate(const poly &h, const int n, poly &f) {
      for (int i = n - 1; i; --i) f[i] = (i64)h[i - 1] * inv[i] % mod;
      f[0] = 0; /* C */
    }
    
    void polyln(const poly &h, const int n, poly &f) {
      /* f = ln h = ∫ h' / h dx */
      assert(h[0] == 1);
      static poly_t ln_t;
      const int t = n << 1;
    
      derivative(h, n, ln_t);
      std::fill(ln_t + n, ln_t + t, 0);
      polyinv(h, n, f);
    
      DFT(ln_t, t);
      DFT(f, t);
      for (int i = 0; i != t; ++i) ln_t[i] = (i64)ln_t[i] * f[i] % mod;
      IDFT(ln_t, t);
    
      integrate(ln_t, n, f);
    }
    
    void polyexp(const poly &h, const int n, poly &f) {
      /* f = exp(h) = f_0 (1 - ln f_0 + h) */
      assert(h[0] == 0);
      static poly_t exp_t;
      std::fill(f, f + n + n, 0);
      f[0] = 1;
      for (int t = 2; t <= n; t <<= 1) {
        const int t2 = t << 1;
    
        polyln(f, t, exp_t);
        exp_t[0] = sub(pls(h[0], 1), exp_t[0]);
        for (int i = 1; i != t; ++i) exp_t[i] = sub(h[i], exp_t[i]);
        std::fill(exp_t + t, exp_t + t2, 0);
    
        DFT(f, t2);
        DFT(exp_t, t2);
        for (int i = 0; i != t2; ++i) f[i] = (i64)f[i] * exp_t[i] % mod;
        IDFT(f, t2);
    
        std::fill(f + t, f + t2, 0);
      }
    }
    ```

### Example problems

1.  Compute $f^{k}(x)$

    The usual approach is polynomial fast exponentiation, with time complexity $O(n\log{n}\log{k})$.

    When $[x^{0}]f(x)=1$, we have:

    $$
    f^{k}(x)=\exp{\left(k\ln{f(x)}\right)}
    $$

    When $[x^{0}]f(x)\neq 1$, let the lowest-degree term of $f(x)$ be $f_{i}x^{i}$. Then:

    $$
    f^{k}(x)=f_{i}^{k}x^{ik}\exp{\left(k\ln{\frac{f(x)}{f_{i}x^{i}}}\right)}
    $$

    **Time complexity**  $O(n\log{n})$.

## Polynomial trigonometric functions

Given a polynomial $f\left(x\right)$, find $\sin{f\left(x\right)}, \cos{f\left(x\right)}$ and $\tan{f\left(x\right)}$ modulo $x^{n}$.

### Solution

First, from [Euler's formula](../complex.md#eulers-formula) $\left(\mathrm{e}^{\mathrm{i}x} = \cos{x} + \mathrm{i}\sin{x}\right)$ we get [another expression for the trigonometric functions](https://en.wikipedia.org/wiki/Trigonometric_functions#Relationship_to_exponential_function_and_complex_numbers):

$$
\begin{aligned}
    \sin{x} &= \frac{\mathrm{e}^{\mathrm{i}x} - \mathrm{e}^{-\mathrm{i}x}}{2\mathrm{i}} \\
    \cos{x} &= \frac{\mathrm{e}^{\mathrm{i}x} + \mathrm{e}^{-\mathrm{i}x}}{2}
\end{aligned}
$$

Substituting $f\left(x\right)$ gives:

$$
\begin{aligned}
    \sin{f\left(x\right)} &= \frac{\exp{\left(\mathrm{i}f\left(x\right)\right)} - \exp{\left(-\mathrm{i}f\left(x\right)\right)}}{2\mathrm{i}} \\
    \cos{f\left(x\right)} &= \frac{\exp{\left(\mathrm{i}f\left(x\right)\right)} + \exp{\left(-\mathrm{i}f\left(x\right)\right)}}{2}
\end{aligned}
$$

Writing a program directly from these expressions gives $\sin{f\left(x\right)}$ and $\cos{f\left(x\right)}$ modulo $x^{n}$. Then $\tan{f\left(x\right)}$ follows from $\tan{f\left(x\right)} = \frac{\sin{f\left(x\right)}}{\cos{f\left(x\right)}}$.

### Code

??? note "Polynomial trigonometric functions"
    Note that we are doing NTT over $\mathbb{Z}_{998244353}$, so the imaginary unit $\mathrm{i}$ should be replaced by $86583718$ or $911660635$:
    
    $$
    \begin{aligned}
               & \mathrm{i} = \sqrt{-1} \equiv \sqrt{998244352} \pmod{998244353}       \\
      \implies & \phantom{\text{or}} \quad \mathrm{i} \equiv 86583718 \pmod{998244353} \\
               & \text{or} \quad \mathrm{i} \equiv 911660635 \pmod{998244353}
    \end{aligned}
    $$
    
    ```cpp
    constexpr int MAXN = 262144;
    constexpr int mod = 998244353;
    constexpr int imgunit = 86583718; /* sqrt(-1) = sqrt(998233452) */
    
    using i64 = long long;
    using poly_t = int[MAXN];
    using poly = int *const;
    
    void polytri(const poly &h, const int n, poly &sin_t, poly &cos_t) {
      /* sin(f) = (exp(i * f) - exp(- i * f)) / 2i */
      /* cos(f) = (exp(i * f) + exp(- i * f)) / 2 */
      /* tan(f) = sin(f) / cos(f) */
      assert(h[0] == 0);
      static poly_t tri1_t, tri2_t;
    
      for (int i = 0; i != n; ++i) tri2_t[i] = (i64)h[i] * imgunit % mod;
      polyexp(tri2_t, n, tri1_t);
      polyinv(tri1_t, n, tri2_t);
    
      if (sin_t != nullptr) {
        const int invi = fpow(pls(imgunit, imgunit), mod - 2);
        for (int i = 0; i != n; ++i)
          sin_t[i] = (i64)(tri1_t[i] - tri2_t[i] + mod) * invi % mod;
      }
      if (cos_t != nullptr) {
        for (int i = 0; i != n; ++i) cos_t[i] = div2(pls(tri1_t[i], tri2_t[i]));
      }
    }
    ```

## Polynomial inverse trigonometric functions

Given a polynomial $f\left(x\right)$, find $\arcsin{f\left(x\right)}, \arccos{f\left(x\right)}$ and $\arctan{f\left(x\right)}$ modulo $x^{n}$.

### Solution

As with the polynomial $\ln$, differentiating the inverse trigonometric functions and then integrating gives:

$$
\begin{aligned}
    \frac{\mathrm{d}}{\mathrm{d} x} \arcsin{x} &= \frac{1}{\sqrt{1 - x^{2}}} \\
    \arcsin{x} &= \int \frac{1}{\sqrt{1 - x^{2}}} \mathrm{d} x \\
    \frac{\mathrm{d}}{\mathrm{d} x} \arccos{x} &= - \frac{1}{\sqrt{1 - x^{2}}} \\
    \arccos{x} &= - \int \frac{1}{\sqrt{1 - x^{2}}} \mathrm{d} x \\
    \frac{\mathrm{d}}{\mathrm{d} x} \arctan{x} &= \frac{1}{1 + x^{2}} \\
    \arctan{x} &= \int \frac{1}{1 + x^{2}} \mathrm{d} x
\end{aligned}
$$

Substituting $f\left(x\right)$ gives:

$$
\begin{aligned}
    \frac{\mathrm{d}}{\mathrm{d} x} \arcsin{f\left(x\right)} &= \frac{f'\left(x\right)}{\sqrt{1 - f^{2}\left(x\right)}} \\
    \arcsin{f\left(x\right)} &= \int \frac{f'\left(x\right)}{\sqrt{1 - f^{2}\left(x\right)}} \mathrm{d} x \\
    \frac{\mathrm{d}}{\mathrm{d} x} \arccos{f\left(x\right)} &= - \frac{f'\left(x\right)}{\sqrt{1 - f^{2}\left(x\right)}} \\
    \arccos{f\left(x\right)} &= - \int \frac{f'\left(x\right)}{\sqrt{1 - f^{2}\left(x\right)}} \mathrm{d} x \\
    \frac{\mathrm{d}}{\mathrm{d} x} \arctan{f\left(x\right)} &= \frac{f'\left(x\right)}{1 + f^{2}\left(x\right)} \\
    \arctan{f\left(x\right)} &= \int \frac{f'\left(x\right)}{1 + f^{2}\left(x\right)} \mathrm{d} x
\end{aligned}
$$

Just compute directly from these formulas.

### Code

??? note "Polynomial inverse trigonometric functions"
    ```cpp
    constexpr int MAXN = 262144;
    constexpr int mod = 998244353;
    
    using i64 = long long;
    using poly_t = int[MAXN];
    using poly = int *const;
    
    void derivative(const poly &h, const int n, poly &f) {
      for (int i = 1; i != n; ++i) f[i - 1] = (i64)h[i] * i % mod;
      f[n - 1] = 0;
    }
    
    void integrate(const poly &h, const int n, poly &f) {
      for (int i = n - 1; i; --i) f[i] = (i64)h[i - 1] * inv[i] % mod;
      f[0] = 0; /* C */
    }
    
    void polyarcsin(const poly &h, const int n, poly &f) {
      /* arcsin(f) = ∫ f' / sqrt(1 - f^2) dx  */
      static poly_t arcsin_t;
      const int t = n << 1;
      std::copy(h, h + n, arcsin_t);
      std::fill(arcsin_t + n, arcsin_t + t, 0);
    
      DFT(arcsin_t, t);
      for (int i = 0; i != t; ++i) arcsin_t[i] = sqr(arcsin_t[i]);
      IDFT(arcsin_t, t);
    
      arcsin_t[0] = sub(1, arcsin_t[0]);
      for (int i = 1; i != n; ++i)
        arcsin_t[i] = arcsin_t[i] ? mod - arcsin_t[i] : 0;
    
      polysqrt(arcsin_t, n, f);
      polyinv(f, n, arcsin_t);
      derivative(h, n, f);
    
      DFT(f, t);
      DFT(arcsin_t, t);
      for (int i = 0; i != t; ++i) arcsin_t[i] = (i64)f[i] * arcsin_t[i] % mod;
      IDFT(arcsin_t, t);
    
      integrate(arcsin_t, n, f);
    }
    
    void polyarccos(const poly &h, const int n, poly &f) {
      /* arccos(f) = - ∫ f' / sqrt(1 - f^2) dx  */
      polyarcsin(h, n, f);
      for (int i = 0; i != n; ++i) f[i] = f[i] ? mod - f[i] : 0;
    }
    
    void polyarctan(const poly &h, const int n, poly &f) {
      /* arctan(f) = ∫ f' / (1 + f^2) dx  */
      static poly_t arctan_t;
      const int t = n << 1;
      std::copy(h, h + n, arctan_t);
      std::fill(arctan_t + n, arctan_t + t, 0);
    
      DFT(arctan_t, t);
      for (int i = 0; i != t; ++i) arctan_t[i] = sqr(arctan_t[i]);
      IDFT(arctan_t, t);
    
      inc(arctan_t[0], 1);
      std::fill(arctan_t + n, arctan_t + t, 0);
    
      polyinv(arctan_t, n, f);
      derivative(h, n, arctan_t);
    
      DFT(f, t);
      DFT(arctan_t, t);
      for (int i = 0; i != t; ++i) arctan_t[i] = (i64)f[i] * arctan_t[i] % mod;
      IDFT(arctan_t, t);
    
      integrate(arctan_t, n, f);
    }
    ```

## References and links

[^ref1]: [Elementary function - Wikipedia](https://en.wikipedia.org/wiki/Elementary_function)
