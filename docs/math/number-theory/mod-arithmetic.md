author: 383494, buuzzing, c-forrest, cr4c1an, Emp7iness, Enter-tainer, Great-designer, HeRaNO, jifbt, Kaiser-Yang, Koishilll, ksyx, Marcythm, Qiu-Quanzhi, Saisyc, sshwy, StarryReverie, StudyingFather, Tiphereth-A, Xeonacid, xyf007

In competitive programming, one important part of number theory is **modular arithmetic**, that is, doing integer operations under a fixed modulus. Besides the four basic operations and exponentiation, you can also conveniently take logarithms, take roots of any degree, and compute factorials and binomial coefficients.

Modular arithmetic shows up in all kinds of problems, not only in number theory. The real answer to many problems can be huge, far beyond the range of the usual integer types. To avoid big-integer arithmetic and printing long numbers, problems often ask you to print the answer modulo some number. So you need to be fluent with the various modular arithmetic techniques.

## Integer division and modulo in C/C++

In C/C++, integer division and the modulo operation do not match the usual mathematical conventions.

For every standard version of C/C++, integer division is specified as follows:

1.  If the divisor is 0, the behavior is undefined;
2.  Otherwise, `(a / b) * b + a % b` equals `a`.

In other words, the sign of the remainder depends on how division rounds; and how division rounds is implementation-defined (decided by the compiler).

Since the [C99](https://en.cppreference.com/w/c/language/operator_arithmetic) and [C++11](https://en.cppreference.com/w/cpp/language/operator_arithmetic) standards, **the quotient is rounded toward zero** (the fractional part is discarded); the remainder then has the same sign as the dividend. So from then on, the following assertions are guaranteed to hold:

```c
assert(5 % 3 == 2);
assert(5 % -3 == 2);
assert(-5 % 3 == -2);
assert(-5 % -3 == -2);
```

## Modular integer class

Modular arithmetic can be viewed as doing operations on the [residue classes](./basic.md#同余类与剩余系) under some modulus. If you represent a residue class with a struct, and wrap addition, subtraction, multiplication and so on between residue classes as methods or operator overloads, modular arithmetic naturally becomes a modular integer class. Below is a simple example. It supports addition, subtraction, multiplication and fast exponentiation of $32$-bit signed integers under a modulus $M < 2^{30}$:

???+ example "A simple modular integer class"
    ```cpp
    --8<-- "docs/math/code/mod-arithmetic/mod-arithmetic.cpp:core"
    ```

This implementation deliberately reduces the number of modulo operations, because taking a remainder is usually much slower than an ordinary addition, subtraction, multiplication or comparison. The code comments give equivalent, more direct implementations. The main idea of these simple optimizations is: when you add or subtract two integers in $[0,M)$, the result always lies in $(-M,2M)$, so a single addition or subtraction brings it back into $[0,M)$. Exponentiation in this implementation uses the [fast exponentiation](../binary-exponentiation.md#模意义下取幂) technique.

Besides these basic operations, you can also do the following under various moduli:

-   [Modular inverse](./inverse.md)
-   [Division](./linear-equation.md)
-   [Factorials](./factorial.md)
-   [Binomial coefficients](./lucas.md)
-   [Square roots](./quad-residue.md#模意义下开平方)
-   [Logarithms](./discrete-logarithm.md)
-   [Roots](./residue.md#模意义下开方)

These operations are usually easier when the modulus is prime. For a composite modulus, you often need an extended version of the corresponding algorithm together with the [Chinese remainder theorem](./crt.md). Most of these modular operations can be seen as solving some kind of congruence equation. For general methods of solving congruence equations, see the [congruence equations](./congruence-equation.md) page.

## Related algorithms

This section introduces several ways to speed up modulo, multiplication and fast exponentiation under a modulus. For the vast majority of problems, the simple implementation above is already fast enough. But when a problem is strict about constant factors, these techniques help: they avoid unnecessary computation and modulo operations, which further lowers the running time.

### Fast multiplication

In primality testing and integer factorization, you often need to multiply modulo a number in the `long long` range. To avoid integer overflow during the computation, this section introduces a "fast multiplication" that handles moduli in the `long long` range, does not need `__int128`, and runs in $O(1)$. The algorithm requires that, on the judge, `long double` is at least an $80$-bit extended-precision floating-point type[^long-double-80bit].

Assume $0 \le a, b < m$ and we want $ab\bmod m$. Note that:

$$
ab\bmod m=ab-\left\lfloor \dfrac{ab}m \right\rfloor m.
$$

Using the natural overflow of `unsigned long long`:

$$
ab\bmod m=ab-\left\lfloor \dfrac{ab}m \right\rfloor m=\left(ab-\left\lfloor \dfrac{ab}m \right\rfloor m\right)\bmod 2^{64}.
$$

As long as we can compute the quotient $\left\lfloor\dfrac{ab}m\right\rfloor$, the multiplication and subtraction in the rightmost expression can be done directly with `unsigned long long`.

Next, we only need to work out how to compute $\left\lfloor\dfrac {ab}m\right\rfloor$. The solution is to first compute $\dfrac am$ with `long double` and then multiply by $b$. Since we use `long double`, there will certainly be rounding error. Assume `long double` is an $80$-bit extended-precision float (that is, $1$ sign bit, $15$ exponent bits and a $64$-bit significand). Then `long double` can represent at most $64$ significant bits exactly[^floating-format]. So in the worst case $\dfrac am$ goes wrong starting from bit $65$, and the error lies in[^ld-mul-err] $\left(-2^{-64},2^{-64}\right)$. After multiplying by $b$, a $64$-bit signed integer, the error lies in $(-0.5,0.5)$. To simplify the discussion, add $0.5$ before rounding down; then the final error is in $\{0,1\}$.

Finally, when we plug this into the formula above, we multiply by $-m$, so the final error is in $\{0,-m\}$. Since $m$ is in the `long long` range, if the result $r\in[0,m)$, return $r$ directly; otherwise return $r+m$.

The code is as follows:

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/mod-arithmetic/i64-mul.cpp:ld-mul"
    ```

Today, the C/C++ compilers on most judges support the `__int128` type[^int128], so you can also simply cast the factors to `__int128` and take the remainder:

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/mod-arithmetic/i64-mul.cpp:i128-mul"
    ```

Of course, taking a remainder of an `__int128` is not cheap either. If you need further constant-factor optimization, consider the methods in the next two sections.

### Barrett reduction

As mentioned above, division and modulo are usually slower than the other arithmetic operations. To cut the cost of modulo operations, some algorithms get the same result without directly taking a remainder. Barrett reduction, introduced in this section, is one of them.

Let $m$ be a fixed modulus, and suppose we need to compute $a\bmod m$ many times for different $a > 0$. By division with remainder,

$$
z = a\bmod m = a - \left\lfloor\dfrac{a}{m}\right\rfloor m.
$$

The key is computing the quotient $\left\lfloor\dfrac{a}{m}\right\rfloor$. Let $R$ be some constant; then[^floor-barrett]

$$
\left\lfloor\dfrac{a}{m}\right\rfloor = \left\lfloor a\dfrac{R}{m} / R\right\rfloor \approx \left\lfloor a\left\lfloor\dfrac{R}{m}\right\rfloor/R\right\rfloor.
$$

If we choose $R = 2^k$, then $\left\lfloor\dfrac{R}{m}\right\rfloor$ on the right can be precomputed, and dividing by $R$ is just a shift. So computing the quotient with the right-hand side needs only one multiplication and one shift. Plugging it into the expression for $a\bmod m$ gives an estimate $z'$ of the remainder.

Now let us analyze the error. The [floor function](./basic.md#取整函数) has the property that for $x > y > 0$, $\lfloor x\rfloor - \lfloor y\rfloor \le \lceil x - y\rceil$. So the error is

$$
\begin{aligned}
\Delta &= |z' - z| = m\left|\left\lfloor\dfrac{a}{m}\right\rfloor - \left\lfloor a\left\lfloor\dfrac{R}{m}\right\rfloor/R\right\rfloor\right|\\
&\le m\left\lceil a\left(\dfrac{R}{m} - \left\lfloor\dfrac{R}{m}\right\rfloor\right) /R\right\rceil \le m\left\lceil\dfrac{a}{R}\right\rceil.
\end{aligned}
$$

As long as $a \le R$, the error $\Delta$ is at most $m$. Since $z' \ge z$, the estimate $z'$ can only be $z$ or $z + m$. After getting the estimate, subtract the extra $m$ when $z' \ge m$, and the answer is guaranteed to be correct.

Barrett reduction takes a remainder using only two multiplications, one shift and at most two subtractions. But the speedup is not free: the intermediate values in Barrett reduction are often longer than the input. It is easy to see that the longest intermediate value is $a\left\lfloor\dfrac{R}{m}\right\rfloor$. Let $\ell(x)$ be the length of the binary representation of an integer $x$. Then

$$
\ell\left(a\left\lfloor\dfrac{R}{m}\right\rfloor\right) \approx \ell(a) + \ell(R) - \ell(m).
$$

Since $R$ must satisfy $a \le R$, this length is at least $2\ell(a) - \ell(m)$. But when we need a remainder at all, we usually have $\ell(m)\le\ell(a)$, so this intermediate value may be longer than the input length $\ell(a)$. For example, to reduce a $64$-bit integer modulo a $32$-bit integer, the intermediate value actually needs a $64 \times 2 - 32 = 96$-bit integer.

One use of Barrett reduction is computing the remainder of a product, $ab\bmod m$. If one factor is fixed, say $b$, you can estimate in the same way as above using

$$
ab\bmod m = ab - \left\lfloor a\left\lfloor\dfrac{bR}{m}\right\rfloor/R\right\rfloor m
$$

as long as you precompute $\left\lfloor\dfrac{bR}{m}\right\rfloor$. This fixed-$b$ case is sometimes called Shoup modular multiplication[^shoup].

The more common case is when neither $a$ nor $b$ is fixed. Then you first compute $ab$, and then use Barrett reduction to get $ab\bmod m$. For example, to implement modular multiplication you need $ab\bmod m$ for $0 \le a,b < m$. Here $R$ must satisfy $ab \le R$. By the analysis above, the longest intermediate value has length $2\ell(ab)-\ell(m)$. When $\ell(a)\approx\ell(b)\approx\ell(m)$, that is $3\ell(m)$. In other words, implementing $32$-bit modular multiplication with Barrett reduction needs $96$-bit intermediate integers. This is one limitation of Barrett reduction in practice in competitive programming.

As an example, here is a reference implementation of $32$-bit signed modular multiplication using Barrett reduction:

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/mod-arithmetic/i32-mul.cpp:barrett"
    ```

The implementation needs $128$-bit integers[^int128].

### Montgomery multiplication

Montgomery multiplication serves much the same purpose as Barrett reduction: it also cuts the cost of modulo operations in modular integer arithmetic. Unlike the previous two algorithms, which both approximate the quotient, Montgomery multiplication maps all integers into Montgomery space, where operations are relatively cheap, which lowers the overall cost.

Let the modulus $m$ be odd, and choose $R = 2^k > m$. Then the Montgomery form of the residue class $a \bmod m$ is

$$
aR\bmod m.
$$

Since $R\perp m$, there is a bijection between the residue class $a \bmod m$ and its Montgomery form $aR\bmod m$. So you can convert integers into Montgomery form, do a number of operations modulo $m$, and then convert the resulting Montgomery form back to an integer; the result is always correct.

Many modular integer operations are easy in Montgomery form. As just explained, to check whether two residue classes are equal, you only need to compare their Montgomery forms. Also, since

$$
(a\pm b)R\bmod m = ((aR\bmod m)\pm(bR\bmod m)) \bmod{m},
$$

adding and subtracting residue classes corresponds to adding and subtracting their Montgomery forms. However, to multiply residue classes, you cannot just multiply their Montgomery forms. Since

$$
(ab)R\bmod m =  ((aR\bmod m)(bR\bmod m)R^{-1}) \bmod{m},
$$

when multiplying two Montgomery forms, you need to apply the following **Montgomery reduction** to their product $x$:

$$
\operatorname{REDC}: x \mapsto xR^{-1}\bmod m.
$$

With this operation, the Montgomery form of the product $ab$ is $\operatorname{REDC}((aR\bmod m)(bR\bmod m))$. Montgomery reduction is the core operation of Montgomery multiplication:

-   Converting $a$ to its Montgomery form is $\operatorname{REDC}((a\bmod m)(R^2\bmod m))$.
-   Converting the Montgomery form of $a$ back to $a\bmod m$ is $\operatorname{REDC}(aR\bmod m)$.
-   The Montgomery form of the modular inverse $a^{-1}\bmod m$ is $\operatorname{REDC}((aR\bmod m)^{-1}(R^3\bmod m))$.

Now let us see how to implement the Montgomery reduction $\operatorname{REDC}$. When computing $\operatorname{REDC}(x)$, we always assume $0 \le x < m^2$, which holds in all the cases above. Since $R\perp m$, by [Bézout's identity](./bezouts.md) there exist integers $R^{-1},m'$ such that

$$
RR^{-1} + mm' = 1.
$$

So, letting $q=\lfloor xm' / R\rfloor$, we have

$$
\begin{aligned}
xR^{-1} &= x\dfrac{1 - mm'}{R} \equiv \dfrac{x-xmm' + qmR}{R} = \dfrac{x - m(xm'\bmod R)}{R} \pmod{m}.
\end{aligned}
$$

Since $0 \le x < m^2 < mR$ and $0 \le xm'\bmod R < R$,

$$
-m < \dfrac{x - m(xm'\bmod R)}{R} < m.
$$

That is, this quotient differs from $xR^{-1}\bmod m$ by at most one $m$. If the quotient is negative, add $m$, and you get $\operatorname{REDC}(x)$. Computing this quotient takes only two integer multiplications, one integer subtraction and two bit operations (taking the remainder modulo $R=2^k$ and dividing by it). So Montgomery reduction is efficient.

To use Montgomery multiplication, you need to precompute some constants. First, Montgomery reduction uses $m' = m^{-1}\bmod R$, which can be computed with the Newton–Hensel method described [below](#integers-modulo-a-power-of-2). Second, reducing the various operations to Montgomery reduction involves constants such as $R^2\bmod m$. To get it, compute $R\bmod m$ once and add it to itself to get $2R\bmod m$. Then treat this as the Montgomery form of $2$ and run fast exponentiation directly to get $2^kR\bmod m = R^2\bmod m$.

As an example, here is Montgomery multiplication for $32$-bit signed integers:

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/mod-arithmetic/i32-mul.cpp:montgomery"
    ```

Compared with modular multiplication via Barrett reduction, Montgomery multiplication involves several steps: conversion, multiplication in Montgomery form, and conversion back. So only when there are enough modular operations between the conversion and the conversion back does the cost of converting get amortized, giving good overall efficiency. However, Montgomery multiplication only needs intermediate values of length $2\ell(m)$, which makes it more flexible to implement. For example, $32$-bit modular multiplication needs only $64$-bit intermediate integers. So if you want a modular integer class for general number-theoretic computation, Montgomery multiplication is the better fit.

### Integers modulo a power of 2

This section discusses implementing a modular integer class when the modulus is a power of $2$. In this special case, division and modulo can be done with bit operations, which is very fast. Barrett reduction and Montgomery multiplication both speed things up by exploiting exactly this property of $2^e$ as a divisor and modulus. In particular, when the modulus is exactly $2^{32}$ or $2^{64}$, you can implement the modular integer class with unsigned integers of that width and natural overflow, with no explicit modulo at all. Even if the modulus is not exactly one of these, you can reduce to these special moduli. For example, with modulus $2^{58}$, you can do the intermediate computation modulo $2^{64}$ and take the result modulo $2^{58}$ at the end. Besides easy reduction, other operations on integers modulo $2^e$ also have many special implementations. This section focuses on inversion and exponentiation.

First, inversion: given an odd $a$ and modulus $m=2^e~(e > 2)$, find $a^{-1}\bmod m$. Common ways to find inverses are the extended Euclidean algorithm and fast exponentiation. The extended Euclidean algorithm needs remainders modulo general numbers; plain fast exponentiation computes $a^{\varphi(m)-1}\bmod{m}$, which needs $\Theta(e)$ integer multiplications. A faster way is the [Newton–Hensel method](../poly/newton.md). Specifically, use the following fact:[^newton-hensel]

$$
ax \equiv 1 \pmod{2^e} \implies ax(2 - ax) \equiv 1\pmod{2^{2e}}.
$$

By this formula, starting from $x = 1$ and repeatedly applying $x \gets x(2-ax)$, you get $a^{-1}\bmod m$ after $\lceil\log_2 e\rceil$ iterations.

As an example, here is a reference implementation of inversion modulo $2^{32}$:

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/mod-arithmetic/mod-32-inv-pow.cpp:inv"
    ```

Next, exponentiation: given $x,a,b$ and modulus $m=2^e~(e > 2)$, find $xa^b\bmod m$, where $a$ is odd. From the [analysis](./primitive-root.md#递推公式) of the multiplicative structure of integers modulo $2^e$, $a$ can always be written as $\pm g^{\ell}$[^mod-2-g], and the minus sign appears exactly when $a\equiv 3\pmod 4$. In that case, replace $a$ with $-a$ and multiply the final result by $(-1)^b$. So from now on we may assume $a\equiv 1\pmod 4$. The core idea of the algorithm is to write $a$ as $g^{L(a)}\bmod m$, and then compute the power as $xg^{bL(a)}\bmod m$.

Computing $L(a)$ means computing the discrete logarithm $\operatorname{ind}_ga$. Note that as long as $a\equiv 1\pmod 4$, $a$ can always be written as

$$
a \equiv (2^{e_1}+1)(2^{e_2}+1)\cdots(2^{e_s}+1) \pmod{m},
$$

where $1 < e_1 < e_2 < \cdots < e_s < e$. To see this, expand the product: the second-lowest $1$ bit in the binary representation of $a$ is exactly bit $e_1$ (indices start from $0$), and from this the representation can be found recursively. By the [properties](./discrete-logarithm.md#性质) of discrete logarithms,

$$
4L(a) \equiv 4L(2^{e_1}+1) + 4L(2^{e_2}+1) + \cdots + 4L(2^{e_s}+1) \pmod{m}. 
$$

The discrete logarithm is taken modulo the order $\delta_m(g)=2^{e-2}=m/4$, so here the whole congruence is multiplied by $4$, so that the computation can be done modulo $m$. So once you precompute all $4L(2^d+1)$ for $1 < d < e$, you can quickly compute $4L(a)$.

Conversely, getting $g^{L(a)}\bmod{m}$ from $L(a)$ is also easy. By the [binomial theorem](../combinatorics/combination.md#二项式定理), for $1 < d < e$ we have

$$
\begin{aligned}
(2^d+1)^{2^{e-d}} \equiv 1 \pmod{m},\quad
(2^d+1)^{2^{e-d-1}} \equiv 1 + 2^{e-1} \pmod{m},
\end{aligned}
$$

so $\delta_m(2^d+1) = 2^{e-d}$. By the properties of the order,

$$
\delta_m(2^d+1) = \dfrac{\delta_m(g)}{\gcd(\delta_m(g), \operatorname{ind}_g(2^d+1))}.
$$

So $\gcd(\delta_m(g), \operatorname{ind}_g(2^d+1)) = 2^{d-2}$. This means $L(2^d+1) = \operatorname{ind}_g(2^d+1) = 2^{d-2}r$ with $2\nmid r$. So the lowest $1$ bit of $4L(2^d+1)$ is exactly bit $d$ (indices start from $0$). Hence, again using the binary representation, you can recursively split $4L(a)$ into a sum of terms of the form $4L(2^d+1)$. From this you get the value of $a$.

In practice there are a few more optimizations. First, splitting $a$ into the product still needs division. It is more convenient to find the decomposition of $a^{-1}$, that is, to find $1 < e_1 < e_2 < \cdots < e_s < e$ such that

$$
a(2^{e_1}+1)(2^{e_2}+1)\cdots(2^{e_s}+1) \equiv 1 \pmod{m}
$$

holds. You still find $e_1$ from the second-lowest $1$ bit, but to remove the factor $2^{e_1}+1$ from $a^{-1}$, you only need to multiply $a$ by $2^{e_1}+1$, which can be done with bit operations. Since $4L(a^{-1})=-4L(a)$, when accumulating $4L(a)$ you subtract instead of add. Second, for a specially chosen base $g$, the iteration does not need to go all the way to $d = e-1$; it can stop at $d = \lceil e/2\rceil - 1$. For this, choose $g$ such that

$$
4L(2^{\lceil e/2\rceil} + 1) = 2^{\lceil e/2\rceil}.
$$

For every $d \ge e / 2$,

$$
(2^d+1)^2 = 2^{2d} + 2^{d+1} + 1 \equiv 2^{d+1} + 1 \pmod{m}.
$$

So by induction starting from $d = \lceil e/2\rceil$, $4L(2^d+1)=2^d$ holds for all $d \ge e/2$. Then, as long as $e/2 \le e_1 < e_2 < \cdots < e_s < e$, we have

$$
(2^{e_1}+1)(2^{e_2}+1)\cdots(2^{e_s}+1) \equiv 1 + 2^{e_1} + 2^{e_2} + \cdots + 2^{e_s} \pmod{m}
$$

and

$$
4L((2^{e_1}+1)(2^{e_2}+1)\cdots(2^{e_s}+1)) = 2^{e_1} + 2^{e_2} + \cdots + 2^{e_s}.
$$

So after handling all bits with $d < e/2$, you can read off the discrete logarithm of the remaining part directly, without going bit by bit. With the first optimization, the whole exponentiation needs only $O(e)$ additions, subtractions and bit operations plus $1$ multiplication; with the second, about half of the additions, subtractions and bit operations are saved, at the cost of $1$ extra multiplication.

As an example, here is a reference implementation of exponentiation modulo $2^{32}$:

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/mod-arithmetic/mod-32-inv-pow.cpp:pow"
    ```

The discrete logarithms can be precomputed with the Pohlig–Hellman algorithm, and the base $g$ can be chosen as

$$
5^{\operatorname{ind}_5(2^{\lceil e/2\rceil}+1)/2^{\lceil e/2\rceil - 2}}\bmod{2^e}.
$$

## References and notes

-   [Fast modular multiplication by orz - Codeforces](https://codeforces.com/blog/entry/96759)
-   [Barrett Reduction - Wikipedia](https://en.wikipedia.org/wiki/Barrett_reduction)
-   [Barrett Reduction - A41](https://encrypt.a41.io/primitives/modular-arithmetic/modular-reduction/barrett-reduction#cost-analysis-of-modular-multiplication)
-   [The principle of Barrett reduction and a proof of its correctness, by Chen - Zhihu (Chinese)](https://zhuanlan.zhihu.com/p/690876166)
-   [Montgomery Multiplication - CP Algorithms](https://cp-algorithms.com/algebra/montgomery_multiplication.html)
-   [Montgomery multiplication, by Chen - Zhihu (Chinese)](https://zhuanlan.zhihu.com/p/645428404)
-   [Binary Exponentiation by Factoring - CP Algorithms](https://cp-algorithms.com/algebra/factoring-exp.html)
-   Barrett, Paul. "Implementing the Rivest Shamir and Adleman public key encryption algorithm on a standard digital signal processor." In Conference on the Theory and Application of Cryptographic Techniques, pp. 311-323. Berlin, Heidelberg: Springer Berlin Heidelberg, 1986.
-   Becker, Hanno, Vincent Hwang, Matthias J. Kannwischer, Bo-Yin Yang, and Shang-Yi Yang. "Neon NTT: Faster Dilithium, Kyber, and Saber on Cortex-A72 and Apple M1." IACR Transactions on Cryptographic Hardware and Embedded Systems (2022): 221-244.
-   Montgomery, Peter L. "Modular multiplication without trial division." Mathematics of computation 44, no. 170 (1985): 519-521.

[^long-double-80bit]: This holds for GCC and Clang on most 64-bit systems.

[^floating-format]: See [Extended precision - Wikipedia](https://en.wikipedia.org/wiki/Extended_precision).

[^ld-mul-err]: This uses the condition $a < m$, that is, $a / m \in [0,1)$.

[^int128]: Among today's mainstream compilers, only MSVC on Windows does not support `__int128`. If you need code that works on several platforms, you can detect MSVC with the `_MSC_VER` macro, include the [`<intrin.h>`](https://learn.microsoft.com/en-us/cpp/intrinsics/x64-amd64-intrinsics-list?view=msvc-170) header in that case, and use its intrinsics (such as `_umul128`) to implement 128-bit integer arithmetic indirectly (only available on 64-bit platforms).

[^floor-barrett]: Here $\left\lfloor\dfrac{R}{m}\right\rfloor$ can also be replaced by other integer estimates of $\dfrac{R}{m}$, such as the ceiling $\left\lceil\dfrac{R}{m}\right\rceil$ or rounding to nearest $\left\lfloor\dfrac{R}{m}\right\rceil$, as long as the error-correction step is adjusted accordingly.

[^shoup]: Shoup implemented this extension of Barrett reduction in his number theory library [NTL](https://libntl.org/), hence the name.

[^newton-hensel]: Direct check: from $ax \equiv 1 \pmod{2^e}$, write $ax = 1 + \lambda 2^e$; then $ax(2-ax) = (1+\lambda 2^e)(1-\lambda 2^e) = 1 - \lambda^2 2^{2e} \equiv 1\pmod{2^{2e}}$.

[^mod-2-g]: The page cited in the text only proves that $g$ can be $5$. In fact, repeating that proof word for word shows that $g$ can be any integer congruent to $5$ modulo $8$. How to choose $g$ is discussed later.
