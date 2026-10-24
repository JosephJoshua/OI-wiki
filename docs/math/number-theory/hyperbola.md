author: Backl1ght, c-forrest, Enter-tainer, Great-designer, Henry-ZHR, huayucaiji, hsfzLZH1, Ir1d, kenlig, ksyx, Marcythm, MegaOwIer, Menci, Nanarikom, nanmenyangde, ouuan, purple-vine, shawlleyw, sshwy, StudyingFather, Tiphereth-A, Xeonacid

Prerequisites: [Dirichlet convolution](./dirichlet.md), [number-theoretic blocking](./sqrt-decomposition.md)

This article introduces the Dirichlet hyperbola method, which computes the prefix sums of the Dirichlet convolution of two arithmetic functions in sublinear time. Analyzing this algorithm leads to the idea of a block sieve, and based on it, this article then shows how to quickly compute the convolution of block sieves. Finally, this article introduces Du's sieve, which computes the prefix sums of the quotient of two arithmetic functions under Dirichlet convolution.

## Dirichlet hyperbola method

The Dirichlet hyperbola method computes the prefix sums of the Dirichlet convolution of two arithmetic functions.

Let $f,g,h$ be arithmetic functions with $h = f\ast g$. Then, by the definition of Dirichlet convolution, the prefix sum of $h$ is

$$
H(n) = \sum_{k=1}^nh(k) = \sum_{k=1}^n\sum_{xy=k}f(x)g(y).
$$

The set of points this sum runs over is exactly the set of lattice points in the first quadrant (excluding the axes) on or below the hyperbola $xy=n$. Give the lattice point $(x,y)$ the weight $f(x)g(y)$; then $H(n)$ is the total weight.

![](./images/dirichlet-hyperbola.svg)

As shown in the figure, this total weight can be computed with the inclusion–exclusion principle:

$$
H(n) = \sum_{x=1}^{\lfloor x_0\rfloor}f(x)G\left(\left\lfloor\dfrac{n}{x}\right\rfloor\right) + \sum_{y=1}^{\lfloor y_0\rfloor}F\left(\left\lfloor\dfrac{n}{y}\right\rfloor\right)g(y) - F(\lfloor x_0\rfloor)G(\lfloor y_0\rfloor).
$$

Here $F,G$ are the prefix-sum functions of $f,g$, and $(x_0,y_0)$ is any point on the hyperbola $xy=n$. In this expression, the first term is the total weight of the green region in the figure, the second term is the total weight of the orange region, and the third term is the total weight of the overlap of the two regions. The expression has only $\lfloor x_0\rfloor + \lfloor y_0\rfloor + 1$ terms. With a sensible choice of $(x_0,y_0)$, it is much faster than computing the prefix sums of $h(n)$ by brute force. This is the **Dirichlet hyperbola method**.

### Computing a single value of the convolution's prefix sum

The most basic use of the Dirichlet hyperbola method is to compute a single value $H(n)$ of the prefix-sum function.

If the values of $F,G$ are known (or can be computed in $O(1)$ time), then so are the values of $f,g$, and every term in the Dirichlet hyperbola expression can be computed in $O(1)$ time. The total time complexity is then $O(x_0+y_0)$. Since $x_0y_0=n$, the AM–GM inequality shows that the lowest time complexity, $O(\sqrt{n})$, is reached when $x_0=y_0=\sqrt{n}$.

This is not a new result. Setting $x_0 > n$ in the Dirichlet hyperbola expression gives

$$
H(n) = \sum_{x=1}^nf(x)G\left(\left\lfloor\dfrac{n}{x}\right\rfloor\right).
$$

Using [number-theoretic blocking](./sqrt-decomposition.md), when the values of $F,G$ are known, this sum can be computed in $O(\sqrt{n})$ time. This is in fact almost equivalent to the algorithm in this section: the two methods need basically the same known information, and the expressions they compute are roughly the same.

??? note "Why they are equivalent"
    Looking closely at how number-theoretic blocking computes the sum, the expression it actually evaluates is
    
    $$
    H(n) = \sum_{y\in D(n)}\left(F\left(\left\lfloor\dfrac{n}{y}\right\rfloor\right)-F\left(\left\lfloor\dfrac{n}{y+1}\right\rfloor\right)\right)G(y).
    $$
    
    Here $D(n) = \left\{\left\lfloor\dfrac{n}{x}\right\rfloor : 1 \le x \le n,~x\in\mathbf N_+\right\}$ is the set of key points in number-theoretic blocking.
    
    By the properties of number-theoretic blocking, for $x\le\sqrt{n}$ the corresponding block heights $y = \lfloor n/x\rfloor$ are all distinct, so these blocks all have length $1$, that is,
    
    $$
    \left\lfloor\dfrac{n}{y+1}\right\rfloor + 1 = x = \left\lfloor\dfrac{n}{y}\right\rfloor.
    $$
    
    Therefore, the sum over these blocks is
    
    $$
    I_1 = \sum_{x=1}^{\lfloor\sqrt{n}\rfloor}\left(F(x)-F(x-1)\right)G\left(\left\lfloor\dfrac{n}{x}\right\rfloor\right) = \sum_{x=1}^{\lfloor\sqrt{n}\rfloor}f(x)G\left(\left\lfloor\dfrac{n}{x}\right\rfloor\right).
    $$
    
    For the remaining blocks, the height $y$ runs over $1,2,\cdots,y^*= \left\lfloor\dfrac{n}{\lfloor\sqrt{n}\rfloor + 1}\right\rfloor$. Applying [Abel's transformation](https://en.wikipedia.org/wiki/Summation_by_parts) (the summation form of integration by parts) to the remaining sum gives
    
    $$
    \begin{aligned}
    I_2 &= \sum_{y=1}^{y^*}\left(F\left(\left\lfloor\dfrac{n}{y}\right\rfloor\right)-F\left(\left\lfloor\dfrac{n}{y+1}\right\rfloor\right)\right)G(y) \\
    &= \sum_{y=1}^{y^*}F\left(\left\lfloor\dfrac{n}{y}\right\rfloor\right)g(y) - F\left(\left\lfloor\dfrac{n}{y^*+1}\right\rfloor\right)G(y^*).
    \end{aligned}
    $$
    
    The properties of number-theoretic blocking show that $\lfloor n/\lfloor \sqrt{n}\rfloor\rfloor \ge \lfloor \sqrt{n}\rfloor$. So there are two cases:
    
    -   When $\lfloor n/\lfloor \sqrt{n}\rfloor\rfloor = \lfloor \sqrt{n}\rfloor$, we must have $y^* < \lfloor \sqrt{n}\rfloor$. Since this block is adjacent to the block containing $x = \lfloor \sqrt{n}\rfloor$, their heights can differ by exactly one, i.e., $y^* = \lfloor \sqrt{n}\rfloor - 1$. In this case,
    
        $$
        \begin{aligned}
        I_2 &= \sum_{y=1}^{\lfloor\sqrt{n}\rfloor-1}F\left(\left\lfloor\dfrac{n}{y}\right\rfloor\right)g(y) - F(\lfloor\sqrt{n}\rfloor)G(\lfloor\sqrt{n}\rfloor-1)\\
        &= \sum_{y=1}^{\lfloor\sqrt{n}\rfloor-1}F\left(\left\lfloor\dfrac{n}{y}\right\rfloor\right)g(y) -  F(\lfloor\sqrt{n}\rfloor)\left(G(\lfloor\sqrt{n}\rfloor) - g(\lfloor\sqrt{n}\rfloor)\right) \\
        &= \sum_{y=1}^{\lfloor\sqrt{n}\rfloor}F\left(\left\lfloor\dfrac{n}{y}\right\rfloor\right)g(y) - F(\lfloor\sqrt{n}\rfloor)G(\lfloor\sqrt{n}\rfloor).
        \end{aligned}
        $$
    
    -   When $\lfloor n/\lfloor \sqrt{n}\rfloor\rfloor > \lfloor \sqrt{n}\rfloor$, we must have $y^* = \lfloor \sqrt{n}\rfloor$. Substituting directly into the sum gives
    
        $$
        I_2 = \sum_{y=1}^{\lfloor\sqrt{n}\rfloor}F\left(\left\lfloor\dfrac{n}{y}\right\rfloor\right)g(y) - F(\lfloor\sqrt{n}\rfloor)G(\lfloor\sqrt{n}\rfloor).
        $$
    
    In summary, apart from one Abel transformation, number-theoretic blocking is really computing the following expression:
    
    $$
    H(n) = \sum_{x=1}^{\lfloor\sqrt{n}\rfloor}f(x)G\left(\left\lfloor\dfrac{n}{x}\right\rfloor\right) + \sum_{y=1}^{\lfloor\sqrt{n}\rfloor}F\left(\left\lfloor\dfrac{n}{y}\right\rfloor\right)g(y) - F(\lfloor\sqrt{n}\rfloor)G(\lfloor\sqrt{n}\rfloor).
    $$
    
    This is exactly the Dirichlet hyperbola expression with $(x_0,y_0)=(\sqrt{n},\sqrt{n})$. So we can say the two algorithms compute almost the same thing. Moreover, since the Dirichlet hyperbola method uses more properties of number-theoretic blocking, it avoids some unnecessary work done by naive blocking and has a slightly smaller constant factor.

In real problems, requiring the values of $F,G$ to be known may be too strong. However, the Dirichlet hyperbola method (or the corresponding number-theoretic blocking) does not actually need all values of $F,G$. Looking at the sum, we see that we only need the values of $F$ and $G$ at the set of key points of number-theoretic blocking

$$
D(n) = \left\{\left\lfloor\dfrac{n}{x}\right\rfloor : 1 \le x \le n,~x\in\mathbf N_+\right\}
$$

This set is both the set of all block heights and the set of all right endpoints of blocks. Note that by the [properties](./sqrt-decomposition.md#properties) of number-theoretic blocking, this set contains every integer $1\le x\le\sqrt{n}$, so knowing $F,G$ on $D(n)$ is the same as knowing $f,g$ at every $1\le x\le\sqrt{n}$. This set has size $\Theta(\sqrt{n})$, so to compute $H(n)$ we only need the values of $F,G$ on a sparse set. This observation is the key to speeding up prefix sums of arithmetic functions.

## Block sieves and their convolution

Sometimes $h=f\ast g$ is not the final function whose prefix sums we need, but only an intermediate step. From the analysis above, for later computations we need the values of the prefix-sum function $H$ on the set $D(n)$. This is called the **block sieve** of the arithmetic function $h$:

$$
\mathcal S_h(n) = \left\{H(x) : x \in D(n)\right\}.
$$

This section discusses how to solve the **block sieve convolution** problem: given the block sieves of $f,g$, find the block sieve of their Dirichlet convolution $h = f\ast g$.

### Naive algorithm

The naive algorithm treats computing the block sieve as computing $|D(n)|$ single prefix-sum values. The total time complexity is

$$
\begin{aligned}
O\left(\sum_{d\in D(n)}\sqrt{d}\right) &= O\left(\sum_{x=1}^{\lfloor\sqrt{n}\rfloor}\sqrt{x} + \sum_{x=1}^{\lfloor\sqrt{n}\rfloor}\sqrt{\dfrac{n}{x}}\right) \\
&= O\left(\int_1^{\sqrt{n}}\sqrt{x}\mathrm{d}x + \int_1^{\sqrt{n}}\sqrt{\dfrac{n}{x}}\mathrm{d}x\right)\\
&= O(n^{3/4}).
\end{aligned}
$$

It is precisely because the block sieve is sparse that the whole block sieve can be computed in sublinear time.

However, this algorithm is clearly too brute-force. The smaller elements of $D(n)$ are relatively dense, so adjacent prefix sums in the block sieve differ only a little. We can simply compute the values of the convolution $h$ directly and then take prefix sums. This is faster than computing each prefix-sum value separately. For example, computing the prefix-sum values separately for $x = 1,2,\cdots,\lfloor\sqrt{n}\rfloor$ takes

$$
O\left(\sum_{x=1}^{\lfloor\sqrt{n}\rfloor}\sqrt{x}\right) = O(n^{3/4})
$$

time, while computing the values of $h$ at these points directly and summing them up takes only $O(n^{1/2}\log n)$ time. Even so, if we only know the block sieves of $f,g$ and nothing more, this idea cannot improve the complexity further. The reason is that the block sieve only contains values at $x \le \sqrt{n}$, so we can compute the values of $h$ only at $1\le x\le\sqrt{n}$, and computing the remaining prefix-sum values still takes $O(n^{3/4})$ time.

### Optimizing with known values

If, besides the block sieves of $f,g$, we also know more of their values, then we can indeed improve the complexity. In practice, this algorithm is usually used when the values of $f,g$ can be preprocessed quickly.

Choose $z \ge \sqrt{n}$. The block sieve of the convolution $h$ is computed in two parts:

-   Compute the values of the convolution $h$ of $f\ast g$ at $1\le x \le z$, then add them up directly to get the values of $H$ at $1\le x\le z$.
-   For $x\in D(n)$ with $x > z$, compute the value of $H$ at $x$ with the Dirichlet hyperbola method.

In the general case, the time complexity is

$$
\begin{aligned}
O\left(z\log z + \sum_{d\in D(n),~d\ge z}\sqrt{d}\right) &= O\left(z\log z + \sum_{x=1}^{n/z}\sqrt{\dfrac{n}{x}}\right)\\
&= O\left(z\log z + \int_1^{n/z}\sqrt{\dfrac{n}{x}}\mathrm{d}x\right)\\
&= O\left(z\log z + \dfrac{n}{\sqrt{z}}\right).
\end{aligned}
$$

When $z=\left(\dfrac{n}{\log n}\right)^{2/3}$, the total time complexity reaches its minimum $O\left(n^{2/3}(\log n)^{1/3}\right)$.

Of course, the complexity of [computing values](./dirichlet.md#computing-dirichlet-convolutions) of a Dirichlet convolution depends on the properties of $f,g,h$. When $f,g,h$ have special properties, the best split point and the complexity are slightly different:

-   If $f$ or $g$ is multiplicative, then with $z=\left(\dfrac{n}{\log\log n}\right)^{2/3}$, the total time complexity reaches its minimum $O\left(n^{2/3}(\log\log n)^{1/3}\right)$.
-   If $h$ is multiplicative, then with $z=n^{2/3}$, the total time complexity reaches its minimum $O(n^{2/3})$.

This optimization does not need all values of $f,g$, only their values at $1\le x\le z$. Since the algorithm also produces the values of $h$ at $1\le x\le z$, when $h$ is an intermediate result, its values can also be used to speed up later steps. The block sieve of an arithmetic function, together with these values, forms an enhanced block sieve: it is all the information needed to compute convolution prefix sums in $O(n^{2/3+\varepsilon})$ time.

### Fast block sieve convolution

Prerequisites: [Fast Fourier transform](../poly/fft.md)

???+ warning "Note"
    Beginners can skip this section.

This section discusses the fast block sieve convolution algorithm proposed by Zhou Kangyang in his 2024 national training team paper. Given the block sieves $\mathcal S_f$ and $\mathcal S_g$, it computes their convolution $\mathcal S_h$ in $O(\sqrt{n}\log^2n)$ time. The algorithm does not rely on extra known values or on multiplicativity, but it is fairly complex to implement.

The block sieve convolution problem asks for the prefix sums of

$$
h(z) = \sum_{xy=z} f(x)g(y)
$$

at the points $D(n) = \{\left\lfloor n / t\right\rfloor : 1\le t \le n\}$. For this problem, a single contribution can be labeled by $(x,y,t)$, meaning that the term $f(x)g(y)$ is added to the prefix sum at $\left\lfloor n / t\right\rfloor$. The algorithm handles these contributions in several groups.

First, consider the contributions of all points with $x > \sqrt{n}$ to these prefix sums; contributions with $y > \sqrt{n}$ are handled the same way. Since every contribution must satisfy $xy \le \lfloor n / t\rfloor$, i.e., $xyt \le n$, we only need to enumerate all possible $t,y$. Using prefix-sum tricks and the information in the block sieve $\mathcal S_f$, this part can be computed in $O(\sum_{t,y: ty\le\sqrt{n}} 1) = O(\sqrt{n}\log n)$ time.

Next, consider the contributions with $\left\lfloor n / t\right\rfloor\le\sqrt{n}$. This part can also be done by brute-force enumeration of all possible $x,y$, still in $O(\sum_{x,y:xy\le\sqrt{n}}1) = O(\sqrt{n}\log n)$ time. This part actually gives the first $\lfloor\sqrt{n}\rfloor$ values of $h$ on $D(n)$.

Now consider the remaining contributions, namely those with $x,y\le\sqrt{n}$ and $\left\lfloor n / t\right\rfloor > \sqrt{n}$. Every contribution must satisfy $xyt\le n$, i.e., $\ln x + \ln y \le \ln(n/t)$. Choose a positive number $S$; we can approximate this condition by $\lceil S\ln x\rceil + \lceil S\ln y\rceil \le S\ln(n/t)$. Define polynomials $\sigma_f(u)$ and $\sigma_g(u)$ whose coefficients $[u^k]\sigma_f$ and $[u^k]\sigma_g$ are the sum of $f(x)$ over $x$ with $\lceil S\ln x\rceil = k$ and the sum of $g(y)$ over $y$ with $\lceil S\ln y\rceil = k$, respectively (only for $x,y\le\sqrt{n}$). Using the fast Fourier transform (FFT), we get their product $\sigma_f\sigma_g$, whose coefficient $[u^k](\sigma_f\sigma_g)$ is the sum of $f(x)g(y)$ over pairs with $\lceil S\ln x\rceil + \lceil S\ln y\rceil = k$. Then, for each remaining $\lfloor n/t\rfloor$ in $D(n)$, we just find the largest $k$ with $k \le S\ln(n/t)$, and we get an estimate of this part of the contribution.

Finally, we correct the error in this part. Above, we used the stronger condition $\lceil S\ln x\rceil + \lceil S\ln y\rceil \le S\ln(n/t)$ to approximate $\ln x + \ln y \le \ln(n/t)$, which may miss some contributions. This only happens when $\lceil S\ln x\rceil + \lceil S\ln y\rceil > S\ln(n/t)$, so

$$
S\ln x + 1 +  S\ln y + 1 \ge \lceil S\ln x\rceil + \lceil S\ln y\rceil >  S\ln(n/t) \ge S\ln x + S\ln y.
$$

This is equivalent to

$$
xyt \in (n\mathrm{e}^{-2/S},n].
$$

This is an interval of length $O(n/S)$. We enumerate every possible contribution $(x,y,t)$ in the interval and check one by one whether it was missed, which corrects the error. To enumerate all contributions in the interval quickly, first sieve all primes up to $\sqrt{n}$, then divide the integers in the interval by these primes. Whatever factor remains must be a prime greater than $\sqrt{n}$. This gives the prime factorization of every integer in the interval, so we can quickly enumerate all possible $(x,y,t)$.

Let's look at the time complexity of this last part. For the estimate, we multiply polynomials of length $S\log n$, which takes $O(S\log n\log(S\log n))$ time. For the error correction, preprocessing the prime factorizations takes $O(\sqrt{n}+(n/S)\log\log n)$ time, and enumerating all contributions in the interval takes $O(\sum_{k\in(n\mathrm{e}^{-2/S},n]}d_3(k))$ time, where $d_3(n)$ is the number of ways to write $n$ as an ordered product of three integers. A result from analytic number theory[^piltz] states:

$$
\sum_{k\le n}d_3(k) = nP(\log n) + O(n^{43/96+\varepsilon}),
$$

where $P(\cdot)$ is a quadratic polynomial. Since the first two steps already take $O(\sqrt{n}\log n)$ time, ignoring all $o(\sqrt{n}\log n)$ terms, the time complexity of this last part is

$$
O\left(S\log n\log(S\log n) + \dfrac{n}{S} \log^2n\right).
$$

Taking $S = \sqrt{n}$ gives a time complexity of $O(\sqrt{n}\log^2n)$. This is also the total time complexity of the algorithm.

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/hyperbola/fast_bs_conv.cpp:core"
    ```

## Du's sieve

The sections above discussed how to compute prefix sums of the Dirichlet convolution of arithmetic functions. This section considers the reverse: let $f \ast g = h$, where $f,h$ are known, and compute the prefix sum of $g$

$$
G(n) = \sum_{x=1}^ng(x).
$$

In other words, this section considers computing prefix sums of the quotient of two arithmetic functions under Dirichlet convolution. Throughout this section we assume $f(1)\neq 0$, so that $f$ is invertible.

To do this, set $x_0 > n$ in the Dirichlet hyperbola expression to get

$$
H(n) = \sum_{x=1}^{n}f(x)G\left(\left\lfloor\dfrac{n}{x}\right\rfloor\right).
$$

Solving for $G(n)$ gives

$$
G(n) = \dfrac{1}{f(1)}\left(H(n)-\sum_{x=2}^nf(x)G\left(\left\lfloor\dfrac{n}{x}\right\rfloor\right)\right).
$$

This is the formula of Du's sieve. In fact, for any $x_0 \ge 1$, we always have

$$
G(n) = \dfrac{1}{f(1)}\left(H(n)-\sum_{x=2}^{\lfloor x_0\rfloor}f(x)G\left(\left\lfloor\dfrac{n}{x}\right\rfloor\right) - \sum_{y=1}^{\lfloor y_0\rfloor}F\left(\left\lfloor\dfrac{n}{y}\right\rfloor\right)g(y) + F(\lfloor x_0\rfloor)G(\lfloor y_0\rfloor)\right).
$$

Either way, this is a recurrence for $G(n)$. To compute $G(n)$, we need the values of $G$ on $D(n)\setminus\{n\}$. Since $D(n)$ has a [recursive structure](./sqrt-decomposition.md#properties), namely $D(m)\subseteq D(n)$ for every $m\in D(n)$, the whole recursive computation only needs to compute $G$ once at each element of $D(n)$. In other words, computing $G(n)$ actually gives us the block sieve $\mathcal S_g(n)$ of $g$.

In practice, we can use recursion with memoization to avoid repeated work. Alternatively, we can iterate and compute the value of $G$ at each point of $D(n)$ from small to large. In this case, the sums in the expression can be computed with either number-theoretic blocking or the Dirichlet hyperbola method.

These implementations have the same complexity. Since Du's sieve always produces a block sieve, its complexity is really the complexity of computing a block sieve. If the only known information is the block sieves of $F,H$, then Du's sieve runs in $O(n^{3/4})$; if, for some $z\ge\sqrt{n}$, the values of $g$ at $1\le x \le z$ can be preprocessed in $T_0(z)$ time, then Du's sieve runs in

$$
O\left(T_0(z) + \dfrac{n}{\sqrt{z}}\right).
$$

When $g$ is multiplicative, we can use the linear sieve, i.e., $T_0(z)=\Theta(z)$, so the best choice is to preprocess up to $z = n^{2/3}$, giving a total time complexity of $O(n^{2/3})$. In the more general case, the total time complexity is $O(n^{2/3}(\log n)^{1/3})$. All of this matches the analysis in the block sieve section exactly.

??? warning "A recursive implementation without memoization has the wrong complexity"
    In the formula of Du's sieve, computing $G(n)$ depends on the values of $G$ on $D(n)\setminus\{n\}$. The key to the complexity bound is the recursive structure of $D(n)$: when $m\in D(n)$, $D(m)\subseteq D(n)$. This property allows memoization to speed things up. With memoization, as shown above, the algorithm runs in $O(n^{3/4})$. Here we show that without memoization, the complexity is wrong.
    
    Let $T(n)$ be the cost of computing $G(n)$ recursively without memoization. Then
    
    $$
    \begin{aligned}
    T(n) &= \Theta(\sqrt{n}) + \sum_{d\in D(n),~d\neq n}T(d)\\
    &= \Theta(\sqrt{n}) + \sum_{x=1}^{\lfloor n/\lfloor\sqrt{n}\rfloor\rfloor - 1} T(x) + \sum_{x = 2}^{\lfloor\sqrt{n}\rfloor}T\left(\left\lfloor\dfrac{n}{x}\right\rfloor\right).
    \end{aligned}
    $$
    
    Using an argument similar to the proof of the [master theorem](../../basic/complexity.md#master-theorem), one can show that the last term dominates the growth, and $T(n)\in\Theta(n^\alpha)$, where $\alpha\approx 1.73$ is the root of $\zeta(\alpha)=2$.

When using Du's sieve to compute prefix sums of an arithmetic function $g$, the key is to find suitable $f,h$ with $h=f\ast g$ such that the block sieves of $f,h$ are both easy to compute. Sometimes such $f,h$ are obvious; at other times they have to be derived from properties of Dirichlet convolution, or found by computing the corresponding Dirichlet generating function or Bell series (for multiplicative functions). The example problems below show these situations.

## Example problems

This section presents several problems about computing prefix sums of arithmetic functions.

???+ example "[AtCoder Regular Contest 116 C - Multiple Sequences](https://atcoder.jp/contests/arc116/tasks/arc116_c)"
    Given positive integers $N$ and $M$, count the sequences $A$ of length $N$ such that $1 \le A_i \le M$ and $A_i$ divides $A_{i+1}$. Output the answer modulo $998244353$. Constraints: $1 \le N, M \le 2\times 10^5$.

??? note "Solution"
    Let $f_n(m)$ be the number of such sequences of length $n$ with $A_n=m$. Then the final answer is $\sum_{m=1}^M f_N(m)$. To compute $f_n(m)$, we use dynamic programming. The transition is:
    
    $$
    f_n(m) = \sum_{k\mid m}f_{n-1}(k).
    $$
    
    In Dirichlet convolution notation, this is $f_n = f_{n-1}\ast 1$, where $1$ is the constant arithmetic function. Since $f_1 = 1$, by induction $f_n = 1 ^{\ast n}$. That is, $f_n$ is the convolution of $n$ constant functions. The final answer is the prefix sum of $f_N$. Since only multiplicative functions are involved, using the method above for prefix sums of Dirichlet convolutions, each convolution prefix sum takes only $O(M^{2/3})$ time. Then, with [fast exponentiation](../binary-exponentiation.md), we only need $O(\log N)$ convolution prefix sums to get the prefix sum of $f_N$. The overall time complexity is $O(M^{2/3}\log N)$.

??? note "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/hyperbola/hyperbola.cpp"
    ```

???+ example "[Luogu P4213 [Template] Du's Sieve (Sum)](https://www.luogu.com.cn/problem/P4213)"
    Let $\mu$ and $\varphi$ be the Möbius function and Euler's totient function. Compute $S_1(n)= \sum_{i=1}^{n} \mu(i)$ and $S_2(n)= \sum_{i=1}^{n} \varphi(i)$. Constraints: $1\leq n<2^{31}$.

??? note "Solution"
    Note the Dirichlet convolution identities:
    
    $$
    \varepsilon = \mu \ast 1,~ \operatorname{id} = \varphi \ast 1.
    $$
    
    Here $\varepsilon(n) = [n=1]$ is the identity element of Dirichlet convolution, $\operatorname{id}(n) = n$ is the identity function, and $1(n) = 1$ is the constant function. Since the prefix sums of these three functions can all be computed in $O(1)$ time and they are all multiplicative, Du's sieve as described above computes the answer in $O(n^{2/3})$ time.
    
    For the prefix sums of Euler's totient function, another method uses [Möbius inversion](./mobius.md). Note that
    
    $$
    \begin{aligned}
    S_2(n) &= \sum_{i=1}^n\varphi(i) = \sum_{i=1}^n\sum_{j=1}^i[i\perp j] \\
    &= \sum_{i=1}^n\sum_{j=1}^i\sum_d\mu(d)[d\mid i][d\mid j] \\
    &= \sum_d\mu(d)\dfrac{1}{2}\left\lfloor\dfrac{n}{d}\right\rfloor\left(\left\lfloor\dfrac{n}{d}\right\rfloor+1\right).
    \end{aligned}
    $$
    
    The number-theoretic blocking needs prefix sums of $\mu(d)$, which can be precomputed with Du's sieve. The time complexity is still $O(n^{2/3})$.

??? note "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/du/du_1.cpp"
    ```

???+ example "[Luogu P3768 A Simple Math Problem](https://www.luogu.com.cn/problem/P3768)"
    Given $p,n$, compute
    
    $$
    \sum_{i=1}^n\sum_{j=1}^nij\cdot\gcd(i,j)\pmod p.
    $$
    
    Constraints: $n\leq 10^{10}$, $5\times 10^8\leq p\leq 1.1\times 10^9$, and $p$ is prime.

??? note "Solution"
    Using a property of [Euler's totient function](./euler-totient.md), we do the following inversion:
    
    $$
    \begin{aligned}
    T(n) &= \sum_{i=1}^n\sum_{j=1}^nij\cdot\gcd(i,j)\\
    &= \sum_{i=1}^n\sum_{j=1}^nij\sum_d\varphi(d)[d\mid i][d\mid j]\\
    &= \sum_d\varphi(d)\left(\sum_{i=1}^{\lfloor n/d\rfloor}id\right)\left(\sum_{j=1}^{\lfloor n/d\rfloor}jd\right)\\
    &= \sum_d d^2\varphi(d) F\left(\left\lfloor\dfrac{n}{d}\right\rfloor\right)^2.
    \end{aligned}
    $$
    
    Here $F(n) = \dfrac{1}{2}n(n+1)$. This sum can be computed with number-theoretic blocking, but we need the prefix sums of $d^2\varphi(d)$.
    
    For this, we can use Du's sieve. Let $f(n)=(\operatorname{id}^2\varphi)(n)$ and $S(n)=\sum_{i=1}^n f(i)$. The key to Du's sieve is to construct a function $g$ such that both $f\ast g$ and $g$ have easy prefix sums. Above, we already discussed using Du's sieve to precompute prefix sums of $\varphi$, which only uses the identity $\operatorname{id} = \varphi\ast 1$. Compared with $\varphi$, the $f$ here has an extra factor $\operatorname{id}^2$. Since $\operatorname{id}$ is completely multiplicative, by a [property](./dirichlet.md#properties) of Dirichlet convolution, we just multiply every term by $\operatorname{id}^2$ in the same way and get
    
    $$
    \operatorname{id}^3 = f \ast \operatorname{id}^2.
    $$
    
    Since the prefix sums of $\operatorname{id}^2(n)=n^2$ and $\operatorname{id}^3(n)=n^3$ can both be computed in $O(1)$ time, the prefix sums of $f$ can be precomputed in $O(n^{2/3})$ time. Adding number-theoretic blocking, the overall time complexity is still $O(n^{2/3})$.
    
    Another way to express a similar multiplicative function as the quotient (under Dirichlet convolution) of two functions is to use the [Dirichlet generating function](./dirichlet.md#dirichlet-generating-functions).

??? note "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/du/du_2.cpp"
    ```

## Exercises

-   [AtCoder Xmas Contest 2019 D - Sum of (-1)^f(n)](https://atcoder.jp/contests/xmascon19/tasks/xmascon19_d)

## References and notes

-   Ren Zhizhou. 2016. *Several Methods for Summing Multiplicative Functions*. Paper of the 2016 Chinese National Team Candidates for the Olympiad in Informatics (in Chinese).
-   Zhou Kangyang. 2024. *Some Progress on Summing Multiplicative Functions*. Paper of the 2024 Chinese National Team Candidates for the Olympiad in Informatics (in Chinese).
-   [Dirichlet hyperbola method - Wikipedia](https://en.wikipedia.org/wiki/Dirichlet_hyperbola_method)
-   [Time and space complexity analysis of Du's sieve - riteme.site](https://riteme.site/blog/2018-9-11/time-space-complexity-dyh-algo.html) (in Chinese)
-   [A simplified account of common methods for summing arithmetic functions in OI, by negiizhao - UOJ](https://negiizhao.blog.uoj.ac/blog/7165) (in Chinese)
-   [Dirichlet products and cumulative sums of arithmetic functions, by maspy](https://maspypy.com/dirichlet-%e7%a9%8d%e3%81%a8%e3%80%81%e6%95%b0%e8%ab%96%e9%96%a2%e6%95%b0%e3%81%ae%e7%b4%af%e7%a9%8d%e5%92%8c) (in Japanese)
-   [Dirichlet convolution. Part 1: Fast prefix sum computations by adamant - Codeforces](https://codeforces.com/blog/entry/117635)

[^piltz]: [Piltz divisor problem - Divisor summatory function - Wikipedia](https://en.wikipedia.org/wiki/Divisor_summatory_function#Piltz_divisor_problem)
