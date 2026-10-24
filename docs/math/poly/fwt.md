author: Xeonacid, nocriz, ZnPdCo

## Introduction

The Walsh transform[^note1] is an alternative to the discrete Fourier transform for spectral analysis and is widely used in signal processing. The FFT works with doubles, but the Walsh transform decomposes a signal into square waves of different frequencies, so all coefficients are integers with the same absolute value. This means no floating-point multiplication is needed, which makes the computation faster.

So FWT and FFT share the same core idea: both are transforms of arrays. We write the result of applying the fast Walsh–Hadamard transform to an array $A$ as $FWT[A]$.

The core idea of FWT is:

We want a new sequence $C$ obtained from sequences $A$ and $B$ by some operation, written $C = A \cdot B$;

We first compute the forward transforms $FWT[A], FWT[B]$, then compute $FWT[C]$ in $O(n)$ time using $FWT[C]=FWT[A] \cdot FWT[B]$, where $\cdot$ means multiplying entries at the same position;

then we apply the inverse transform to get the sequence $C$. The time complexity is $O(n \log{n})$.

In competitive programming, FWT is the method for computing convolutions where indices are combined by bitwise operations.

Formula: $C_{i} = \sum_{i=j \oplus k}A_{j} B_{k}$

(where $\oplus$ is some binary bitwise operation)

Below we use $\cup$ (bitwise OR), $\cap$ (bitwise AND) and $\oplus$ (bitwise XOR) as examples.

## FWT operations

### OR

If $k=i\cup j$, then the positions of the $1$ bits of $i$ and the positions of the $1$ bits of $j$ must both be subsets of the positions of the $1$ bits of $k$.

We want $FWT[C] = FWT[A] \cdot FWT[B]$, so we need to design the rule of this FWT accordingly.

Following the definition, we can clearly take $FWT[A]_i = A'_i = \sum_{i=i\cup j}A_{j}$, which sums over all $j$ whose $1$ bits form a subset of those of $i$.

Then:

$$
\begin{aligned}
FWT[A]_i\cdot FWT[B]_i&=\left(\sum_{i\cup j=i} A_j\right)\left(\sum_{i\cup k=i} B_k\right) \\
&=\sum_{i\cup j=i}\sum_{i\cup k=i}A_jB_k \\
&=\sum_{i\cup(j\cup k)=i}A_jB_k \\
&= FWT[C]_i
\end{aligned}
$$

Next, let us see how to compute $FWT[A]$.

Brute-force enumeration is out, since it takes $O(n^2)$. Since we cannot enumerate everything, we use divide and conquer.

Split the whole range in half. After the split, the indices written in binary follow a clear pattern.

Let $A_0$ be the first half of $A$ and $A_1$ the second half. In $A_0$ the highest bit of the index is $0$, so its subsets are just its own subsets (since the highest bit is $0$). But in $A_1$ the highest bit is $1$, so the valid subsets include not only its own but also the subsets with the highest bit $0$, that is,

$$
FWT[A] = merge(FWT[A_0], FWT[A_0] + FWT[A_1])
$$

Here merge means concatenating two arrays like strings, and $+$ is ordinary addition of entries at the same position.

So by halving, the concatenation takes $O(\log{n})$ levels, and each level does one pass of work, so we get $FWT[A]$ in $O(n\log{n})$ time.

Next is the inverse. It is actually simple: we know that the subsets of $A_0$ are just its own ($A_0 = FWT[A_0]$), and the subsets of $A_1$ give $FWT[A_0] + FWT[A_1]$, so the recurrence for the inverse follows easily:

$$
UFWT[A'] = merge(UFWT[A_0'], UFWT[A_1'] - UFWT[A_0'])
$$

Here is the code. It is easy to see that the forward and inverse transforms can be combined into one function: $\text{type}=1$ for the forward transform and $\text{type}=-1$ for the inverse.

???+ note "Implementation"
    ```cpp
    void Or(ll *a, ll type) {  // iterative implementation, smaller constant factor
      for (ll x = 2; x <= n; x <<= 1) {
        ll k = x >> 1;
        for (ll i = 0; i < n; i += x) {
          for (ll j = 0; j < k; j++) {
            (a[i + j + k] += a[i + j] * type) %= P;
          }
        }
      }
    }
    ```

### AND

By analogy with OR, AND gives a similar result:

$$
FWT[A] = merge(FWT[A_0] + FWT[A_1], FWT[A_1])
$$

$$
UFWT[A'] = merge(UFWT[A_0'] - UFWT[A_1'], UFWT[A_1'])
$$

Here is the code. $\text{type}=1$ for the forward transform and $\text{type}=-1$ for the inverse.

???+ note "Implementation"
    ```cpp
    void And(ll *a, ll type) {
      for (ll x = 2; x <= n; x <<= 1) {
        ll k = x >> 1;
        for (ll i = 0; i < n; i += x) {
          for (ll j = 0; j < k; j++) {
            (a[i + j] += a[i + j + k] * type) %= P;
          }
        }
      }
    }
    ```

### XOR

XOR convolution is based on the following principle:

Let $x\circ y$ be the parity of the number of $1$ bits in $x\cap y$, that is, $x\circ y=\text{popcnt}(x\cap y)\bmod 2$. Then it is easy to see that $(x\circ y)\oplus (x\circ z)=x\circ(y\oplus z)$.

The transform $FWT[A]$ is also easy to obtain.

Let $FWT[A]_i=\sum_{i\circ j=0}A_j-\sum_{i\circ j=1}A_j$. Let us prove that $FWT[C] = FWT[A] \cdot FWT[B]$ holds:

$$
\begin{aligned}
FWT[A]_iFWT[B]_i&=\left(\sum_{i\circ j=0}A_j-\sum_{i\circ j=1}A_j\right)\left(\sum_{i\circ k=0}B_k-\sum_{i\circ k=1}B_k\right) \\
&=\left(\sum_{i\circ j=0}A_j\sum_{i\circ k=0}B_k+\sum_{i\circ j=1}A_j\sum_{i\circ k=1}B_k\right)-\left(\sum_{i\circ j=0}A_j\sum_{i\circ k=1}B_k+\sum_{i\circ j=1}A_j\sum_{i\circ k=0}B_k\right) \\
&=\sum_{(j\oplus k)\circ i=0}A_jB_k-\sum_{(j\oplus k)\circ i=1}A_jB_k \\
&=FWT[C]_i
\end{aligned}
$$

Now let us see how to compute these values quickly. Again, divide and conquer:

For the subarray $FWT[A_0]$ where the current bit of $i$ is $0$, the $\circ$ operation gives the same result whether the current bit of $j$ is $0$ or $1$ (since $0\cap 0=0,0\cap1=0$), so in $FWT[A]=\sum_{i\circ j=0}A_j-\sum_{i\circ j=1}A_j$ the part $\sum_{i\circ j=1}A_j=0$.

For the subarray $A_1$ where the current bit of $i$ is $1$, the $\circ$ operation gives $0$ with a $0$ bit and $1$ with a $1$ bit (since $1\cap 0=0,1\cap1=1$).

Putting it together:

$$
FWT[A]=merge((FWT[A_0]+FWT[A_1])-0, FWT[A_0]-FWT[A_1])
$$

That is:

$$
FWT[A] = merge(FWT[A_0] + FWT[A_1], FWT[A_0] - FWT[A_1])
$$

The inverse transform follows easily:

$$
UFWT[A'] = merge(\frac{UFWT[A_0'] + UFWT[A_1']}{2}, \frac{UFWT[A_0'] - UFWT[A_1']}{2})
$$

Here is the code: $\text{type}=1$ for the forward transform and $\text{type}=\frac{1}{2}$ for the inverse.

???+ note "Implementation"
    ```cpp
    void Xor(ll *a, ll type) {
      for (ll x = 2; x <= n; x <<= 1) {
        ll k = x >> 1;
        for (ll i = 0; i < n; i += x) {
          for (ll j = 0; j < k; j++) {
            (a[i + j] += a[i + j + k]) %= P;
            (a[i + j + k] = a[i + j] - a[i + j + k] * 2) %= P;
            (a[i + j] *= type) %= P;
            (a[i + j + k] *= type) %= P;
          }
        }
      }
    }
    ```

### XNOR

By analogy with XOR, the formulas are:

$FWT[A]_{i} = \sum_{C_1}A_{j} - \sum_{C_2}A_{j}$ ($C_1$ means $\text{popcnt}(x\cup y)\bmod 2$ is $0$, $C_2$ means $\text{popcnt}(x\cup y)\bmod 2$ is $1$)

$$
FWT[A] = merge(FWT[A_1] - FWT[A_0], FWT[A_1] + FWT[A_0])
$$

$$
UFWT[A'] = merge(\frac{UFWT[A_1'] - UFWT[A_0']}{2}, \frac{UFWT[A_1'] + UFWT[A_0']}{2})
$$

## FWT from another angle

Let $c(i,j)$ be the coefficient with which $A_j$ contributes to $FWT[A]_i$. We can restate the FWT as:

$$
FWT[A]_i = \sum_{j=0}^{n-1} c(i,j) A_j
$$

Since:

$$
FWT[A]_i\cdot FWT[B]_i=FWT[C]_i
$$

a simple argument shows that $c(i,j)c(i,k)=c(i,j\odot k)$, where $\odot$ is the bitwise operation in question.

Also, the function $c$ has an important property: it can be handled bit by bit.

For example, when we transform:

$$
FWT[A]_i = \sum_{j=0}^{n-1} c(i,j) A_j
$$

Doing it this way is inefficient, so we split it:

$$
FWT[A]_i = \sum_{j=0}^{n/2-1} c(i,j) A_j+\sum_{j=n/2}^{n-1} c(i,j) A_j
$$

Compare $i,j$ in the first sum and in the second sum: they differ only in the highest bit.

So let $i',j'$ be $i,j$ with the highest bit removed, and let $i_0$ be the highest bit of $i$. Then:

$$
FWT[A]_i = c(i_0,0)\sum_{j=0}^{n/2-1} c(i',j') A_j+c(i_0,1)\sum_{j=n/2}^{n-1} c(i',j') A_j
$$

If $i_0=0$, then:

$$
FWT[A]_i = c(0,0)\sum_{j=0}^{n/2-1} c(i',j') A_j+c(0,1)\sum_{j=n/2}^{n-1} c(i',j') A_j
$$

If $i_0=1$, then:

$$
FWT[A]_i = c(1,0)\sum_{j=0}^{n/2-1} c(i',j') A_j+c(1,1)\sum_{j=n/2}^{n-1} c(i',j') A_j
$$

In other words, we only need the four numbers

$$
\begin{bmatrix}
c(0,0) & c(0,1) \\
c(1,0) & c(1,1)
\end{bmatrix}
$$

to do the transform. We call this matrix the bit matrix.

For the inverse transform, we need the inverse of this bit matrix.

If the inverse matrix is $c^{-1}$, a similar process recovers the original numbers:

$$
A_i = \sum_{j=0}^n c^{-1}(i,j) FWT[A]_j
$$

The inverse matrix does not always exist; for example, a matrix with a row of $0$s or a column of $0$s has no inverse, so we must be careful when constructing it.

### Bitwise OR

We can construct:

$$
\begin{bmatrix}
1 & 0 \\
1 & 1
\end{bmatrix}
$$

This satisfies $c(i,j)c(i,k)=c(i,j\cup k)$. Notice that this is exactly the same as $FWT[A]=\text{merge}(FWT[A_0], FWT[A_0]+FWT[A_1])$ derived earlier! Similarly, the following matrix also satisfies the condition, but we usually use the one above:

$$
\begin{bmatrix}
1 & 1 \\
1 & 0
\end{bmatrix}
$$

The following matrix also satisfies $c(i,j)c(i,k)=c(i,j\cup k)$, but it has a row of $0$s and no inverse, so it is not valid:

$$
\begin{bmatrix}
0 & 0 \\
1 & 1
\end{bmatrix}
$$

For the inverse transform, we invert the matrix. Taking the **first** matrix above as an example, we get:

$$
\begin{bmatrix}
1 & 0 \\
-1 & 1
\end{bmatrix}
$$

Then plug the inverse matrix into the same procedure as the forward transform.

### Bitwise AND

We can construct:

$$
\begin{bmatrix}
1 & 1 \\
0 & 1
\end{bmatrix}
$$

This satisfies $c(i,j)c(i,k)=c(i,j\cap k)$.

Inverse matrix:

$$
\begin{bmatrix}
1 & -1 \\
0 & 1
\end{bmatrix}
$$

### Bitwise XOR

We can construct:

$$
\begin{bmatrix}
1 & 1 \\
1 & -1
\end{bmatrix}
$$

This satisfies $c(i,j)c(i,k)=c(i,j\oplus k)$.

Inverse matrix:

$$
\begin{bmatrix}
0.5 & 0.5 \\
0.5 & -0.5
\end{bmatrix}
$$

## FWT is a linear transform

FWT is a linear transform. That is, it satisfies:

$$
FWT[A+B]=FWT[A]+FWT[B]
$$

and:

$$
FWT[c\cdot A]=c\cdot FWT[A]
$$

## K-dimensional FWT

Bitwise operations are really operations on $n$-dimensional $\{0,1\}$ vectors. OR takes the $\max$ in each dimension. AND takes the $\min$ in each dimension. XOR adds the coordinates in each dimension and takes $\bmod 2$.

A key feature of bitwise operations: each coordinate of the vector is independent.

What happens if we extend $\{0,1\}$ to $[0,K)\cap \mathbf{Z}$, that is, to base $K$?

### max operation

Extend $\cup$ to base $K$, defining $i\cup j$ as the digit-wise $\max$. We have:

$$
c(i,j)c(i,k)=c(i,j\cup k)
$$

If $j=k$, this becomes:

$$
c(i,j)c(i,j)=c(i,j)
$$

That is, in each row, the $1$s must all come before the $0$s; if any $1$ comes after a $0$, it is invalid. Playing with it by hand gives a valid construction:

$$
\begin{bmatrix}
1 & 0 & 0 & 0 \\
1 & 1 & 0 & 0 \\
1 & 1 & 1 & 0 \\
1 & 1 & 1 & 1
\end{bmatrix}
$$

Its inverse is:

$$
\begin{bmatrix}
1 & 0 & 0 & 0 \\
-1 & 1 & 0 & 0 \\
0 & -1 & 1 & 0 \\
0 & 0 & -1 & 1
\end{bmatrix}
$$

### min operation

Extend $\cap$ to base $K$, defining $i\cap j$ as the digit-wise $\min$. We have:

$$
c(i,j)c(i,k)=c(i,j\cap k)
$$

If $j=k$, this becomes:

$$
c(i,j)c(i,j)=c(i,j)
$$

That is, in each row, the $1$s must all come after the $0$s; if any $1$ comes before a $0$, it is invalid. Playing with it by hand gives a valid construction:

$$
\begin{bmatrix}
1 & 1 & 1 & 1 \\
0 & 1 & 1 & 1 \\
0 & 0 & 1 & 1 \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

Its inverse is:

$$
\begin{bmatrix}
1 & -1 & 0 & 0 \\
0 & 1 & -1 & 0 \\
0 & 0 & 1 & -1 \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

The two above are rarely used. The one used more often is:

### Addition without carry

Extend $\oplus$ to base $K$, defining $i\oplus j$ as digit-wise addition $\bmod K$. We have:

$$
c(i,j)c(i,k)=c(i,j\oplus k)
$$

Taking $c(i,j)=\omega_{K}^j$ satisfies the requirement:

$$
\omega_{K}^j\omega_{K}^k=\omega_{K}^{j\oplus k}
$$

But if every row is the same, the matrix has no inverse, so we take $c(i,j)=\omega_{K}^{(i-1)j}$ instead.

This gives the following matrix:

$$
\begin{bmatrix}
1 & 1 & 1 & \cdots & 1 \\
1 & \omega_{K}^1 & \omega_{K}^2 & \cdots & \omega_{K}^{k-1} \\
1 & \omega_{K}^2 & \omega_{K}^4 & \cdots & \omega_{K}^{2(k-1)} \\
1 & \omega_{K}^3 & \omega_{K}^6 & \cdots & \omega_{K}^{3(k-1)} \\
\vdots & \vdots & \vdots & \ddots & \vdots \\
1 & \omega_{K}^{k-1} & \omega_{K}^{2(k-1)} & \cdots & \omega_{K}^{(k-1)(k-1)}
\end{bmatrix}
$$

This is a [Vandermonde matrix](https://en.wikipedia.org/wiki/Vandermonde_matrix). Its inverse is:

$$
\frac{1}{K}\begin{bmatrix}
1 & 1 & 1 & \cdots & 1 \\
1 & \omega_{K}^{-1} & \omega_{K}^{-2} & \cdots & \omega_{K}^{-(k-1)} \\
1 & \omega_{K}^{-2} & \omega_{K}^{-4} & \cdots & \omega_{K}^{-2(k-1)} \\
1 & \omega_{K}^{-3} & \omega_{K}^{-6} & \cdots & \omega_{K}^{-3(k-1)} \\
\vdots & \vdots & \vdots & \ddots & \vdots \\
1 & \omega_{K}^{-(k-1)} & \omega_{K}^{-2(k-1)} & \cdots & \omega_{K}^{-(k-1)(k-1)}
\end{bmatrix}
$$

If the modulus given in the problem has the required roots of unity, this is easy to implement.

But **roots of unity may not exist modulo the given number**, so we extend the ring: we formally define an $x$ with $x^K=1$ and compute with $x$ directly, so each number becomes a polynomial in $x$ of degree $k-1$. We only need to compute $\bmod {x^K-1}$. Then the matrix can be written as:

$$
\begin{bmatrix}
1 & 1 & 1 & \cdots & 1 \\
1 & x^1 & x^2 & \cdots & x^{k-1} \\
1 & x^2 & x^4 & \cdots & x^{2(k-1)} \\
1 & x^3 & x^6 & \cdots & x^{3(k-1)} \\
\vdots & \vdots & \vdots & \ddots & \vdots \\
1 & x^{k-1} & x^{2(k-1)} & \cdots & x^{(k-1)(k-1)}
\end{bmatrix}
$$

But this may introduce zero divisors, that is, **one number may have several representations**, and we cannot determine its true value.

So instead of working $\bmod {x^K-1}$, we work $\bmod$ the cyclotomic polynomial $\Phi_{K}(x)$, under which $x$ has order $k$ and which is irreducible over $\mathbb{Q}$. So we define the computation above to be carried out $\bmod {\Phi_{K}(x)}$.

Another issue is that working $\bmod \Phi_{K}(x)$ has a large constant factor (because $\Phi$ is itself a polynomial). But since $\Phi_{K}(x)\mid x^k-1$, we can compute $\bmod x^k -1$ throughout and only reduce $\bmod \Phi_{K}(x)$ at the end.

## Example problems

???+ note "[CF 1103E Radix sum](https://www.luogu.com.cn/problem/CF1103E)"
    Given a sequence $a_1,a_2,...,a_n$ of length $n$, for each $p \in [0,n-1]$, count the integer sequences $i_1,i_2,...,i_n$ satisfying the following conditions, modulo $2^{58}$:
    
    -   $\forall j \in [1,n] , i_j \in [1,n]$;
    -   $\sum\limits_{j=1}^n a_{i_j} = p$, where addition is decimal addition without carry.
    
    $n\le10^5,a_i\le10^5$
    
    ??? note "Solution"
        A DP comes to mind: let the state $f_{i,s}$ mean we have considered the first $i$ numbers and the current sum is $s$. Since the FWT is linear, we can transform to the FWT point-value representation, raise it to the $n$-th power, and then transform back.
        
        That part is routine, but the problem uses the modulus $2^{58}$. There are no roots of unity, so we extend the ring.
        
        Here the cyclotomic polynomial is $\Phi_{10}(x)=x^4-x^3+x^2-x+1$.
        
        However, the UFWT needs to divide by the base $10$, and $10$ has no inverse modulo $2^{58}$. But $5$ does have an inverse modulo $2^{58}$: $57646075230342349$, so we only need to deal with the remaining factor of $2$. Let $x$ be the answer after dividing by $5$ and $y$ the true answer, so $2^5y\equiv x\pmod{2^{64}}$. Clearly $y\equiv \frac{x}{2^5}\pmod{2^{64-5}}$, that is, $y\equiv \frac{x}{2^5}\pmod{2^{59}}$, so we just divide the final answer by $2^5$. It is unclear why the problem setter chose the modulus $2^{58}$, but we just reduce modulo it once more.

???+ note "[CF103329F XXII Open Cup, Grand Prix of Xi'an - The Struggle](https://codeforces.com/gym/103329/problem/F)"
    Given an ellipse $E$ where all lattice points have coordinates in $[1,4 \cdot 10^6]$, compute $\sum_{(x,y) \in E} (x \oplus y)^{33}x^{-2}y^{-1} \mod 10^9+7$.
    
    ??? note "Solution"
        This problem is not a straightforward application. The problem setter provided a detailed editorial in English; see [this link](https://codeforces.com/blog/entry/96518).

## References

-   [Taojiang's algorithm notes (in Chinese)](https://zhuanlan.zhihu.com/p/41867199)
-   [ZnPdCo's blog](https://znpdco.github.io/%E7%AE%97%E6%B3%95/2024/05/07/FWT.html)

[^note1]: [Wikipedia (Chinese)](https://zh.wikipedia.org/zh-cn/%E6%B2%83%E7%88%BE%E4%BB%80%E8%BD%89%E6%8F%9B)
