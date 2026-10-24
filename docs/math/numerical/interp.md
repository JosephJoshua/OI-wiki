author: AtomAlpaca, billchenchina, caibyte, Chrogeek, Early0v0, EndlessCheng, Enter-tainer, Henry-ZHR, hly1204, hsfzLZH1, Ir1d, Ghastlcon, kenlig, Marcythm, megakite, Peanut-Tang, qwqAutomaton, qz-cqy, StudyingFather, swift-zym, swiftqwq, Tiphereth-A, TrisolarisHD, Watersail2005, x4Cx58x54, Xeonacid, xiaopangfeiyu, YanWQ-monad

## Introduction

Interpolation is a way to estimate new data points within some range from a set of known, discrete data points. It is often used for curve fitting.

For example, take these data points:

| $x$    | $0$ | $1$      | $2$      | $3$      | $4$       | $5$       | $6$       |
| ------ | --- | -------- | -------- | -------- | --------- | --------- | --------- |
| $f(x)$ | $0$ | $0.8415$ | $0.9093$ | $0.1411$ | $-0.7568$ | $-0.9589$ | $-0.2794$ |

![](../images/interp-1.svg)

Here $f(x)$ is unknown. Interpolation estimates unknown data points by fitting $f(x)$ with a function of a certain form.

For example, we can fit $f(x)$ with a piecewise linear function:

![](../images/interp-2.svg)

This is called [linear interpolation](https://en.wikipedia.org/wiki/Linear_interpolation).

We can also fit $f(x)$ with a polynomial:

![](../images/interp-3.svg)

This is called [polynomial interpolation](https://en.wikipedia.org/wiki/Polynomial_interpolation).

The general form of polynomial interpolation is as follows:

???+ note "Polynomial interpolation"
    Given $n+1$ known points $(x_0,y_0),(x_1,y_1),\dots,(x_n,y_n)$, find a polynomial $f(x)$ of the form $f(x)=\sum_{i=0}^n a_ix^i$ such that
    
    $$
    f(x_i)=y_i,\qquad\forall i=0,1,\dots,n
    $$
    
    holds.

Below we cover two methods of polynomial interpolation: Lagrange interpolation and Newton interpolation. It is not hard to prove that they give the same result.

## Lagrange interpolation

We want to build a function $f(x)$ that passes through the points $P_1(x_1, y_1), P_2(x_2,y_2),\cdots,P_n(x_n,y_n)$. First, let the projection of the $i$-th point onto the $x$-axis be $P_i^{\prime}(x_i,0)$.

Build $n$ functions $f_1(x), f_2(x), \cdots, f_n(x)$ such that the graph of the $i$-th function $f_i(x)$ passes through $\begin{cases}P_j^{\prime}(x_j,0),(j\neq i)\\P_i(x_i,y_i)\end{cases}$. Then the function we want is $f(x)=\sum\limits_{i=1}^nf_i(x)$.

So we can let $f_i(x)=a\cdot\prod_{j\neq i}(x-x_j)$. Plugging in the point $P_i(x_i,y_i)$ gives $a=\dfrac{y_i}{\prod_{j\neq i} (x_i-x_j)}$, so

$$
f_i(x)=y_i\cdot\dfrac{\prod_{j\neq i} (x-x_j)}{\prod_{j\neq i} (x_i-x_j)}=y_i\cdot\prod_{j\neq i}\dfrac{x-x_j}{x_i-x_j}
$$

This gives the Lagrange interpolation formula:

$$
f(x)=\sum_{i=1}^ny_i\cdot\prod_{j\neq i}\dfrac{x-x_j}{x_i-x_j}
$$

A naive implementation takes $O(n^2)$ time. This can be improved to $O(n\log^2 n)$; see [fast polynomial interpolation](../poly/multipoint-eval-interpolation.md#fast-polynomial-interpolation).

???+ note "[Luogu P4781 [Template] Lagrange Interpolation](https://www.luogu.com.cn/problem/P4781)"
    You are given $n$ point pairs $(x_i,y_i)$ and $k$, where $\forall i,j$ we have $i\neq j \iff x_i\neq x_j$, $f(x_i)\equiv y_i\pmod{998244353}$ and $\deg(f(x)) < n$ (with $\deg(0)=-\infty$). Find $f(k)\bmod{998244353}$.
    
    ??? note "Solution"
        This problem only asks for the value $f(k)$, so you can plug $k$ in directly while evaluating the formula above. Sometimes you need more complex operations, such as evaluating at many points, and then you need the coefficients of $f$. The code shows one way to compute the coefficients.
        
        $$
        f(k)=\sum_{i=1}^{n}y_i\prod_{j\neq i }\frac{k-x_j}{x_i-x_j}
        $$
        
        This problem also needs modular inverses. If you first compute the numerator and denominator separately, then multiply the numerator by the inverse of the denominator and add it to the answer, computing inverses is no longer the bottleneck, and the time complexity is $O(n^2)$.
        
        Since all computation is modulo the fixed prime $998244353$, we treat computing a modular inverse as constant time here.
    
    ??? note "Code"
        ```cpp
        --8<-- "docs/math/code/numerical/interp/interp_1.cpp"
        ```

### Lagrange interpolation when the x-coordinates are consecutive integers

If the x-coordinates of the known points are consecutive integers, we can interpolate in $O(n)$.

Let $f(x)$ be the polynomial we want, and suppose we know $f(1),\cdots,f(n+1)$ ($1\le i\le n+1$). Plug them into the interpolation formula above:

$$
\begin{aligned}
f(x)&=\sum\limits_{i=1}^{n+1}y_i\prod\limits_{j\ne i}\frac{x-x_j}{x_i-x_j}\\
&=\sum\limits_{i=1}^{n+1}y_i\prod\limits_{j\ne i}\frac{x-j}{i-j}
\end{aligned}
$$

Handle the numerator and denominator of the product separately. The numerator is easily seen to be:

$$
\dfrac{\prod\limits_{j=1}^{n+1}(x-j)}{x-i}
$$

The product of $i-j$ in the denominator can be split into two factorials:

$$
(-1)^{n+1-i}\cdot(i-1)!\cdot(n+1-i)!
$$

So the interpolation formula for x-coordinates $1,\cdots,n+1$ is:

$$
f(x)=\sum\limits_{i=1}^{n+1}(-1)^{n+1-i}y_i\cdot\frac{\prod\limits_{j=1}^{n+1}(x-j)}{(i-1)!(n+1-i)!(x-i)}
$$

Precompute prefix and suffix products of $(x-i)$, factorials and inverse factorials, then plug them into this formula. This takes $O(n)$ time.

???+ note "Example problem [CF622F The Sum of the k-th Powers](https://codeforces.com/contest/622/problem/F)"
    Given $n,k$, find $\sum\limits_{i=1}^ni^k$ modulo $10^9+7$.
    
    ??? note "Solution"
        Here the answer is a polynomial of degree $k+1$, so we can compute $1^i,\cdots,(k+2)^i$ with a linear sieve and then interpolate in $O(n)$.
        
        Using some combinatorics, you can also derive the following from the finite-difference formula:
        
        $$
        f(x)=\sum_{i=1}^{n+1}\binom{x-1}{i-1}\sum_{j=1}^{i}(-1)^{i+j}\binom{i-1}{j-1}y_{j}=\sum\limits_{i=1}^{n+1}y_i\cdot\frac{\prod\limits_{j=1}^{n+1}(x-j)}{(x-i)\cdot(-1)^{n+1-i}\cdot(i-1)!\cdot(n+1-i)!}
        $$
    
    ??? note "Code"
        ```cpp
        --8<-- "docs/math/code/numerical/interp/interp_2.cpp"
        ```

## Newton interpolation

Newton interpolation is based on higher-order differences. Its advantage is that a new data point can be added in $O(n)$.

To allow adding a new data point in $O(n)$, we write:

$$
f(x)=\sum_{j=0}^n a_jn_j(x)
$$

where $n_j(x):=\prod_{i=0}^{j-1}(x-x_i)$ is called the **Newton basis**.

Once we solve for $a_j$, we have the interpolating polynomial $f(x)$. Define the **forward divided differences** as follows:

$$
\begin{aligned}
    \lbrack y_k\rbrack  & := y_k,                                                                & k=0,\dots,n, \\
    [y_k,\dots,y_{k+j}] & := \dfrac{[y_{k+1},\dots,y_{k+j}]-[y_k,\dots,y_{k+j-1}]}{x_{k+j}-x_k}, & k=0,\dots,n-j,~j=1,\dots,n.
\end{aligned}
$$

Then:

$$
\begin{aligned}
    f(x)&=[y_0]+[y_0,y_1](x-x_0)+\dots+[y_0,\dots,y_n](x-x_0)\dots(x-x_{n-1})\\
    &=\sum_{j=0}^n [y_0,\dots,y_j]n_j(x)
\end{aligned}
$$

This is the Newton form of the interpolating polynomial. A naive implementation takes $O(n^2)$ time.

If the sample points are equally spaced (that is, $x_i=x_0+ih$, $i=1,\dots,n$), we can derive

$$
[y_k,\dots,y_{k+j}]=\frac{1}{j!h^j}\Delta^{(j)}y_k,
$$

where $\Delta^{(j)}y_k$ are the **forward differences**, defined as:

$$
\begin{aligned}
    \Delta^{(0)}y_k & := y_k,                                       & k=0,\dots,n, \\
    \Delta^{(j)}y_k & := \Delta^{(j-1)} y_{k+1}-\Delta^{(j-1)} y_k, & k=0,\dots,n-j,~j=1,\dots,n.
\end{aligned}
$$

Let $x=x_0+sh$. Then the Newton interpolation formula becomes

$$
f(x)=\sum_{j=0}^n \binom{s}{j}j!h^j[y_0,\dots,y_j]=\sum_{j=0}^n \binom{s}{j}\Delta^{(j)}y_0.
$$

??? note "Code ([Luogu P4781 [Template] Lagrange Interpolation](https://www.luogu.com.cn/problem/P4781))"
    ```cpp
    --8<-- "docs/math/code/numerical/interp/interp_3.cpp"
    ```

### Newton interpolation when the x-coordinates are consecutive integers

For example: find the coefficients of the polynomial $f(x)=\sum_{i=0}^{3} a_ix^i$, given that $f(1)$ through $f(6)$ are $1, 5, 14, 30, 55, 91$.

$$
\begin{array}{cccccccccccc}
1 &    &  5 &    & 14 &    & 30 &    & 55 &    & 91 & \\
&  4 &    &  9 &    & 16 &    & 25  &    & 36 & \\
&    &  5 &    &  7 &    &  9 &    &  11 & \\
&    &    &  2 &    &  2 &    &  2 & \\
\end{array}
$$

The first row holds the first $n$ consecutive values of $f(x)$. Each following row holds the differences of adjacent entries in the row above. Notice that if you repeat this enough times (as long as $f(x)$ is a polynomial), you always end up with a constant.

The first entry of the $(i-1)$-th order difference is $\sum_{j=1}^{i}(-1)^{i+j}\binom{i-1}{j-1}f(j)$, and it contributes $\binom{k-1}{i-1}$ times to $f(k)$.

$$
f(k)=\sum_{i=1}^n\binom{k-1}{i-1}\sum_{j=1}^{i}(-1)^{i+j}\binom{i-1}{j-1}f(j)
$$

The time complexity is $O(n^2)$.

## Implementation in C++

Since C++20, the standard library provides the functions [`std::midpoint`](https://en.cppreference.com/w/cpp/numeric/midpoint) and [`std::lerp`](https://en.cppreference.com/w/cpp/numeric/lerp), for computing the midpoint and for linear interpolation respectively.

## Exercises

-   [NOIP2020 WeChat Steps](https://loj.ac/p/3389)
-   [Joint Provincial Selection 2022 Filling the Tree](https://loj.ac/p/3701)
-   [NOI2019 Robot](https://loj.ac/p/3157)

## References

1.  [Interpolation - Wikipedia](https://en.wikipedia.org/wiki/Interpolation)
2.  [Newton polynomial - Wikipedia](https://en.wikipedia.org/wiki/Newton_polynomial)
