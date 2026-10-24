## Introduction

Vandermonde's convolution is a formula for combining binomial coefficients. It is mainly used in deriving formulas in combinatorics.

## Vandermonde's convolution formula

$$
\sum_{i=0}^k\binom{n}{i}\binom{m}{k-i}=\binom{n+m}{k}
$$

### Proof

We prove it with the binomial theorem:

$$
\begin{aligned}
\sum_{k=0}^{n+m}\binom{n+m}{k}x^k&=(x+1)^{n+m}\\
&=(x+1)^n(x+1)^m\\
&=\sum_{r=0}^n\binom{n}{r}x^r\sum_{s=0}^m\binom{m}{s}x^s\\
&=\sum_{k=0}^{n+m}\sum_{r=0}^k\binom{n}{r}\binom{m}{k-r}x^k\\
\end{aligned}
$$

So we have:

$$
\binom{n+m}{k}=\sum_{r=0}^k\binom{n}{r}\binom{m}{k-r}
$$

We can also prove it using its combinatorial meaning:

Choosing $k$ numbers from a set of size $n+m$ is the same as splitting the set of size $n+m$ into two sets of sizes $n$ and $m$, then counting the ways to choose $i$ numbers from the $n$ and $k-i$ numbers from the $m$. Since we enumerate over $i$, we only need to consider one way of splitting, because all ways of splitting are equivalent.

## Corollaries

### Corollary 1 and proof

$$
\sum_{i=-r}^{s}\binom{n}{r+i}\binom{m}{s-i}=\binom{n+m}{r+s}
$$

The proof is similar to the proof of the original formula.

### Corollary 2 and proof

$$
\sum_{i=1}^n\binom{n}{i}\binom{n}{i-1}=\binom{2n}{n-1}
$$

Using basic combinatorics, we have:

$$
\sum_{i=1}^n\binom{n}{i}\binom{n}{i-1}=\sum_{i=0}^{n-1}\binom{n}{i+1}\binom{n}{i}=\sum_{i=0}^{n-1}\binom{n}{n-1-i}\binom{n}{i}=\binom{2n}{n-1}
$$

### Corollary 3 and proof

$$
\sum_{i=0}^n\binom{n}{i}^2=\binom{2n}{n}
$$

Using basic combinatorics, we have:

$$
\sum_{i=0}^n\binom{n}{i}^2=\sum_{i=0}^n\binom{n}{i}\binom{n}{n-i}=\binom{2n}{n}
$$

### Corollary 4 and proof

$$
\sum_{i=0}^m\binom{n}{i}\binom{m}{i}=\binom{n+m}{m}
$$

Using basic combinatorics, we have:

$$
\sum_{i=0}^m\binom{n}{i}\binom{m}{i}=\sum_{i=0}^m\binom{n}{i}\binom{m}{m-i}=\binom{n+m}{m}
$$

Here $\binom{n+m}{m}$ is the familiar number of lattice paths in a grid. So we can also give a proof based on its combinatorial meaning.

In a grid, walking from $(0,0)$ to $(n,m)$ takes $n+m$ steps in total. Put $(0,0)$ at the top-left corner of the grid. We take $n$ steps down and $m$ steps right, so the number of ways is $\binom{n+m}{m}$.

Looking at it another way, we split the $n+m$ steps into two parts: first $n$ steps, then $m$ steps. If $i$ of the first $n$ steps go right, then $m-i$ of the last $m$ steps go right. This proves the identity.

## Exercises

-   [CF785D Anton and School - 2](https://codeforces.com/problemset/problem/785/D)

-   [Luogu P2791 Kindergarten Basketball Problem](https://www.luogu.com.cn/problem/P2791)

## References and notes

1.  [Vandermonde's Convolution Formula](https://www.cut-the-knot.org/arithmetic/algebra/VandermondeConvolution.shtml)
