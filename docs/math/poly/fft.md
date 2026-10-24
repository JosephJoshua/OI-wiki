author: H-J-Granger, ranwen, abc1763613206, Ahacad, Allenyou1126, AndrewWayne, AngelKitty, AtomAlpaca, Backl1ght, billchenchina, c-forrest, CCXXXI, Cheuring, Chrogeek, ChungZH, countercurrent-time, DepletedPrism, Early0v0, EarthMessenger, Enter-tainer, F1shAndCat, GavinZhengOI, Gesrua, Great-designer, greyqz, Haohu Shen, henryrabbit, heroming, hly1204, Ir1d, isdanni, jiang1997, kenlig, Lewy Zeng, lucifer1004, Menci, muoshuosha, NachtgeistW, needtocalmdown, opsiff, ouuan, ouuan, partychicken, schtonn, Sshwy, sshwy, StudyingFather, SukkaW, Taoran-01, Tiphereth-A, TrisolarisHD, untitledunrevised, Xeonacid, YouXam, Yukimaikoriya

Prerequisites: [Complex numbers](../complex.md).

This page introduces an algorithm that multiplies two polynomials of degree $n$ in $O(n\log n)$ time, which is faster than the naive $O(n^2)$ algorithm. Since multiplying two integers can also be treated as polynomial multiplication, this algorithm can also speed up multiplication of big integers.

## Introduction

Consider two polynomials $A$ and $B$:

$$
\begin{aligned}
A ={}& 5x^2 + 3x + 7 \\
B ={}& 7x^2 + 2x + 1 \\
\end{aligned}
$$

Their product $C = A \times B$ can be computed in $O(n^2)$ time (here $n$ is the degree of $A$ or $B$):

$$
\begin{aligned}
C ={}& A \times B \\
  ={}& 35x^4 + 31x^3 + 60x^2 + 17x + 7
\end{aligned}
$$

Clearly, the coefficients $c_i$ of $C$ satisfy $c_i = \sum_{j = 0}^i a_j b_{i - j}$. With this naive algorithm, each coefficient takes $O(n)$ time and there are $O(n)$ coefficients, so the total time complexity is $O(n^2)$.

Can we do better? With the fast Fourier transform, we can bring the complexity down to $O(n \log n)$.

## Fourier transform

The Fourier transform is a method for analyzing signals: it breaks a signal into components, and it can also put a signal back together from those components. Many waveforms can serve as components of a signal; the Fourier transform uses sine waves.

Let $f(t)$ be a function of time $t$. The Fourier transform measures how strongly a periodic component of frequency $\omega$ appears in $f(t)$:

$$
F(\omega)=\mathbb{F}[f(t)]=\int_{-\infty}^{\infty}f(t)\mathrm{e}^{-\mathrm{i}{\omega}t}dt
$$

Its inverse transform is

$$
f(t)=\mathbb{F}^{-1}[F(\omega)]=\frac{1}{2\pi}\int_{-\infty}^{\infty}F(\omega)\mathrm{e}^{\mathrm{i}{\omega}t}d\omega
$$

The inverse transform looks very similar to the forward transform; the $2\pi$ in the denominator is exactly the period of the exponential function.

The Fourier transform is a continuous inner product of the time-domain function with complex exponentials of period $2\pi$. The inverse transform is also an inner product.

The Fourier transform has a convolution theorem: it turns convolution in the time domain into multiplication in the frequency domain, and convolution in the frequency domain into multiplication in the time domain.

## Discrete Fourier transform

The **discrete Fourier transform** (DFT) is the form of the Fourier transform that is discrete in both the time and frequency domains. It turns time-domain samples of a signal into frequency-domain samples of its DTFT (discrete-time Fourier transform).

The Fourier transform is a continuous inner product of functions in integral form; the discrete Fourier transform is an inner product in summation form.

Let $\{x_n\}_{n=0}^{N-1}$ be a sequence satisfying suitable finiteness conditions. Its discrete Fourier transform (DFT) is:

$$
X_k=\sum_{n=0}^{N-1}x_n\mathrm{e}^{-\mathrm{i}\frac{2\pi}{N}kn}
$$

where $\mathrm{e}$ is the base of the natural logarithm and $i$ is the imaginary unit. This transform is usually written with the symbol $\mathcal {F}$, that is,

$$
\hat{x}=\mathcal{F}x
$$

As with the integral form, its **inverse discrete Fourier transform** (IDFT) is:

$$
x_n=\frac{1}{N}\sum_{k=0}^{N-1}X_k\mathrm{e}^{\mathrm{i}\frac{2\pi}{N}kn}
$$

which can be written as:

$$
x=\mathcal{F}^{-1}\hat{x}
$$

In fact, the normalization factors in front of the sums in the DFT and IDFT do not really matter. In the definition above, the factors in front of the DFT and IDFT are $1$ and $\frac {1}{N}$. Sometimes both factors are changed to $\frac{1}{{\sqrt{N}}}$.

The discrete Fourier transform is still a transform from the time domain to the frequency domain. Because of its special summation form, it can also be interpreted in other ways.

If we treat $x_n$ as the coefficient of $x^n$ in a polynomial $f(x)$, then $X_k$ is exactly the value $f(\mathrm{e}^{\frac{-2\pi \mathrm{i}k}{N}})$ of $f(x)$ at the root of unity $\mathrm{e}^{\frac{-2\pi \mathrm{i}k}{N}}$.

This gives another way to understand the convolution theorem: it is a special way of evaluating polynomials. The discrete Fourier transform is exactly evaluating a polynomial at the roots of unity.

For example, compute:

$$
\dbinom{n}{3}+\dbinom{n}{7}+\dbinom{n}{11}+\dbinom{n}{15}+\ldots
$$

Define the function $f(x)$ as:

$$
f(x)={(1+x)}^n=\dbinom{n}{0}x^0+\dbinom{n}{1}x^1+\dbinom{n}{2}x^2+\dbinom{n}{3}x^3+\ldots
$$

Then, substituting the 4th root of unity, $f(\mathrm{i})$ gives this sequence:

$$
f(\mathrm{i})={(1+\mathrm{i})}^n=\dbinom{n}{0}+\dbinom{n}{1}\mathrm{i}-\dbinom{n}{2}-\dbinom{n}{3}\mathrm{i}+\ldots
$$

So the following sum cancels exactly the other terms:

$$
f(1)+\mathrm{i}f(\mathrm{i})-f(-1)-\mathrm{i}f(-\mathrm{i})=4\dbinom{n}{3}+4\dbinom{n}{7}+4\dbinom{n}{11}+4\dbinom{n}{15}+\ldots
$$

So the answer to this math problem is:

$$
\dbinom{n}{3}+\dbinom{n}{7}+\dbinom{n}{11}+\dbinom{n}{15}+\ldots=\frac{2^n+\mathrm{i}(1+\mathrm{i})^n-\mathrm{i}(1-\mathrm{i})^n}{4}
$$

Evaluating at the roots of unity in this problem is exactly a discrete Fourier transform.

### Matrix formula

Since the discrete Fourier transform is a **linear** operator, it can be described by matrix multiplication. In matrix form, the DFT is:

$$
\begin{bmatrix}
    X_{0}  \\
    X_{1}  \\
    X_{2}  \\
    \vdots \\
    X_{N-1}
\end{bmatrix}
=
\begin{bmatrix}
    1      & 1            & 1               & \cdots & 1                   \\
    1      & \alpha       & \alpha^{2}      & \cdots & \alpha^{N-1}        \\
    1      & \alpha^{2}   & \alpha^{4}      & \cdots & \alpha^{2(N-1)}     \\
    \vdots & \vdots       & \vdots          & \ddots & \vdots              \\
    1      & \alpha^{N-1} & \alpha^{2(N-1)} & \cdots & \alpha^{(N-1)(N-1)}
\end{bmatrix}
\begin{bmatrix}
    x_{0}  \\
    x_{1}  \\
    x_{2}  \\
    \vdots \\
    x_{N-1}
\end{bmatrix}
$$

where $\alpha = \mathrm{e}^{-\mathrm{i}\frac{2\pi}{N}}$.

## Fast Fourier transform

The fast Fourier transform (FFT) is an efficient algorithm for computing the DFT. It adds nothing new to Fourier theory, but it was a huge step forward for applying the discrete Fourier transform in computers and digital systems. The number theoretic transform (NTT) is the version of the FFT built on number theory.

In 1965, Cooley and Tukey published the fast Fourier transform algorithm. In fact, the FFT had been discovered before that, but modern computers did not exist yet, and people did not realize how important it was. Some researchers credit Runge and König with discovering the FFT in 1924. But in fact Gauss invented the algorithm as early as 1805, though he never published it.

### Divide-and-conquer implementation

The basic idea of the FFT is divide and conquer. For the DFT, it uses divide and conquer to compute the values of $f(x)$ at $x=\omega_n^k$. Radix-2 FFT divides the polynomial by handling the odd-degree and even-degree terms separately.

For example, take a polynomial with $8$ terms:

$$
f(x) = a_0 + a_1x + a_2x^2+a_3x^3+a_4x^4+a_5x^5+a_6x^6+a_7x^7
$$

Split the terms into two groups by the parity of the degree, and factor an $x$ out of the right group:

$$
\begin{aligned}
f(x) &= (a_0+a_2x^2+a_4x^4+a_6x^6) + (a_1x+a_3x^3+a_5x^5+a_7x^7)\\
     &= (a_0+a_2x^2+a_4x^4+a_6x^6) + x(a_1+a_3x^2+a_5x^4+a_7x^6)
\end{aligned}
$$

Build new functions from the even-degree and odd-degree coefficients:

$$
\begin{aligned}
G(x) &= a_0+a_2x+a_4x^2+a_6x^3\\
H(x) &= a_1+a_3x+a_5x^2+a_7x^3
\end{aligned}
$$

Then the original $f(x)$ can be written with the new functions as:

$$
f(x)=G\left(x^2\right) + x  \times  H\left(x^2\right)
$$

Using the property of roots of unity of even order $\omega^i_n = -\omega^{i + n/2}_n$, and the fact that $G\left(x^2\right)$ and $H\left(x^2\right)$ are even functions, we know that $G(x^2)$ and $H(x^2)$ take the same values at $\omega^i_n$ and $\omega^{i+n/2}_n$ in the complex plane. We get:

$$
\begin{aligned}
f(\omega_n^k) &= G((\omega_n^k)^2) + \omega_n^k  \times H((\omega_n^k)^2) \\
              &= G(\omega_n^{2k}) + \omega_n^k  \times H(\omega_n^{2k}) \\
              &= G(\omega_{n/2}^k) + \omega_n^k  \times H(\omega_{n/2}^k)
\end{aligned}
$$

and:

$$
\begin{aligned}
f(\omega_n^{k+n/2}) &= G(\omega_n^{2k+n}) + \omega_n^{k+n/2}  \times H(\omega_n^{2k+n}) \\
                    &= G(\omega_n^{2k}) - \omega_n^k  \times H(\omega_n^{2k}) \\
                    &= G(\omega_{n/2}^k) - \omega_n^k  \times H(\omega_{n/2}^k)
\end{aligned}
$$

So once we have $G(\omega_{n/2}^k)$ and $H(\omega_{n/2}^k)$, we can get both $f(\omega_n^k)$ and $f(\omega_n^{k+n/2})$. So we just recursively apply the DFT to $G$ and $H$.

The divide-and-conquer DFT can only handle polynomials of length $2^m(m \in \mathbf{N}^ \ast )$; otherwise the two halves have different lengths during the split, and the right half runs out of coefficients. So before the first DFT, pad the sequence to length $2^m(m \in \mathbf{N}^\ast )$ (filling high coefficients with $0$), giving a polynomial of degree $2^m-1$.

When substituting values, we need $n$ different values, so we substitute $\omega_n^0,\omega_n^1,\omega_n^2,\cdots, \omega_n^{n-1} (n=2^m(m \in \mathbf{N}^ \ast ))$, which is $2^m$ different values in total.

For the implementation, the STL provides a complex number template, though you can also write your own. The difference is that with the STL `complex` you can call `exp` to get $\omega_n$. But computing $\omega_n$ from Euler's formula is equivalent.

That is the DFT part of the FFT algorithm: it converts a polynomial from coefficient representation to point-value representation.

Note that since we use complex roots of unity, we need to pad the high-order coefficients of the polynomial with zeros so that $n = 2 ^ k, k \in \mathbf{N}^ \ast$.

???+ note "Recursive FFT"
    ```cpp
    #include <cmath>
    #include <complex>
    
    using Comp = std::complex<double>;  // STL complex
    
    constexpr Comp I(0, 1);  // i
    constexpr int MAX_N = 1 << 20;
    
    Comp tmp[MAX_N];
    
    // rev=1, DFT; rev=-1, IDFT
    // After calling this function, remember to handle the normalization factor
    void DFT(Comp* f, int n, int rev) {
      if (n == 1) return;
      for (int i = 0; i < n; ++i) tmp[i] = f[i];
      // Even indices go to the left, odd indices go to the right
      for (int i = 0; i < n; ++i) {
        if (i & 1)
          f[n / 2 + i / 2] = tmp[i];
        else
          f[i / 2] = tmp[i];
      }
      Comp *g = f, *h = f + n / 2;
      // Recursive DFT
      DFT(g, n / 2, rev), DFT(h, n / 2, rev);
      // cur is the current complex root of unity; for k = 0 it is omega^0_n = 1.
      // step is the ratio between consecutive roots, i.e. omega^k_n = step*omega^{k-1}*n,
      // equivalent to exp(I*(-2*M_PI/n*rev))
      Comp cur(1, 0), step(cos(2 * M_PI / n), sin(-2 * M_PI * rev / n));
      for (int k = 0; k < n / 2;
           ++k) {  // F(omega^k_n) = G(omega^k*{n/2}) + omega^k*n\*H(omega^k*{n/2})
        tmp[k] = g[k] + cur * h[k];
        // F(omega^{k+n/2}*n) = G(omega^k*{n/2}) - omega^k_n*H(omega^k\_{n/2})
        tmp[k + n / 2] = g[k] - cur * h[k];
        cur *= step;
      }
      for (int i = 0; i < n; ++i) f[i] = tmp[i];
    }
    ```

Time complexity $O(n\log n)$.

### Iterative (doubling) implementation

The algorithm can be further optimized from the "divide and conquer" angle. In radix-2 FFT, each step separates the odd-degree and even-degree coefficients of the whole polynomial, until only one coefficient is left. But this recursion needs extra memory. So we can first "imitate the recursion" by "splitting" the coefficients inside the original array, and then "double up" by merging the computed values.

The "splitting" can be done with the bit-reversal permutation.

The "merging" can be done with only $O(1)$ extra space using the butterfly operation.

#### Bit-reversal permutation

Take a polynomial with $8$ terms as an example and simulate the splitting:

-   The initial sequence is $\{x_0, x_1, x_2, x_3, x_4, x_5, x_6, x_7\}$
-   After one split: $\{x_0, x_2, x_4, x_6\},\{x_1, x_3, x_5, x_7 \}$
-   After two splits: $\{x_0,x_4\} \{x_2, x_6\},\{x_1, x_5\},\{x_3, x_7 \}$
-   After three splits: $\{x_0\}\{x_4\}\{x_2\}\{x_6\}\{x_1\}\{x_5\}\{x_3\}\{x_7 \}$

The pattern: write the index of each number in the original sequence in binary and reverse the bits; the result is its final position. For example, $x_1$ is 001, reversed it is 100, which is 4, and indeed its final position is 4. This transformation is called the bit-reversal permutation; the proof is left to the reader.

From its definition, we can compute where every number goes in $O(n)$ time:

???+ note "Bit-reversal permutation implementation ($O(n)$)"
    ```cpp
    /*
     * Bit-reversal permutation applied before FFT and IFFT
     * Swap position i with the position given by reversing the bits of i
     * len must be a power of 2
     */
    void change(Complex y[], int len) {
      // At the start i is 0...01 and j is 10...0, bit-reversals of each other.
      // Then i increases by one each time, and j stays the bit-reversal of i, until i = 1...11.
      for (int i = 1, j = len / 2, k; i < len - 1; i++) {
        // Swap elements whose indices are bit-reversals of each other; i < j makes sure each pair is swapped once
        if (i < j) swap(y[i], y[j]);
        // i is incremented normally, j is incremented in reversed-bit fashion, so i and j always stay reversed.
        // Here k marks the highest bit that is 0. j first subtracts the leading 1 bits
        // until it reaches a 0, then adds that bit.
        // Counting bit flips in j: the highest bit flips n times,
        // the second highest flips n/2 times, and so on, so the time complexity is:
        // T(n) = n + n/2 + n/4 + ... = O(n)
        k = len / 2;
        while (j >= k) {
          j = j - k;
          k = k / 2;
        }
        j += k;
      }
    }
    ```

The bit-reversal permutation can also be computed in $O(n)$ by a recurrence from small to large. Let $len=2^k$, where $k$ is the length of the binary numbers, and let $R(x)$ be the number obtained by reversing the $k$-bit binary number $x$ (padding the high bits with $0$). We want $R(0),R(1),\cdots,R(n-1)$.

First, $R(0)=0$.

We compute $R(x)$ from small to large. So when computing $R(x)$, the value $R\left(\left\lfloor \dfrac{x}{2} \right\rfloor\right)$ is already known. So we shift $x$ right by one (divide by $2$), reverse it, and shift right by one again; this gives the reversal of all bits of $x$ **except the lowest (binary) bit**.

Now consider the lowest bit: if it is $0$, after reversal the highest bit is $0$. If it is $1$, after reversal the highest bit is $1$, so we must also add $\dfrac{len}{2}=2^{k-1}$. In summary,

$$
R(x)=\left\lfloor \frac{R\left(\left\lfloor \frac{x}{2} \right\rfloor\right)}{2} \right\rfloor + (x\bmod 2)\times \frac{len}{2}
$$

For example, let $k=5$ and $len=(100000)_2$. To reverse $(11001)_2$:

1.  Consider $(1100)_2$. We know $R((1100)_2)=R((01100)_2)=(00110)_2$, and shifting right by one more gives $(00011)_2$.
2.  Consider the lowest bit: if it is $1$, it moves to the highest bit, so we add $(10000)_2=2^{k-1}$ to the reversed number; if it is $0$, nothing changes.

???+ note "Bit-reversal permutation implementation ($O(n)$)"
    ```cpp
    // Again, len must be a power of 2
    // rev[i] is the bit-reversal of i
    void change(Complex y[], int len) {
      for (int i = 0; i < len; ++i) {
        rev[i] = rev[i >> 1] >> 1;
        if (i & 1) {  // if the last bit is 1, it becomes len/2 after reversal
          rev[i] |= len >> 1;
        }
      }
      for (int i = 0; i < len; ++i) {
        if (i < rev[i]) {  // make sure each pair is swapped only once
          swap(y[i], y[rev[i]]);
        }
      }
      return;
    }
    ```

#### Butterfly operation

Given $G(\omega_{n/2}^k)$ and $H(\omega_{n/2}^k)$, we use the following two formulas to get $f(\omega_n^k)$ and $f(\omega_n^{k+n/2})$:

$$
\begin{aligned}
    f(\omega_n^k)       & = G(\omega_{n/2}^k) + \omega_n^k \times H(\omega_{n/2}^k) \\
    f(\omega_n^{k+n/2}) & = G(\omega_{n/2}^k) - \omega_n^k \times H(\omega_{n/2}^k)
\end{aligned}
$$

After the bit-reversal permutation, for given $n, k$:

-   The value of $G(\omega_{n/2}^k)$ is stored at index $k$ of the array, and the value of $H(\omega_{n/2}^k)$ is stored at index $k + \dfrac{n}{2}$.
-   The value of $f(\omega_n^k)$ will be stored at index $k$, and the value of $f(\omega_n^{k+n/2})$ will be stored at index $k + \dfrac{n}{2}$.

So we can overwrite the entries at indices $k$ and $k + \frac{n}{2}$ directly, without an extra array. This is called the **butterfly operation**, or more precisely, the radix-2 butterfly.

Here is in more detail how to use the butterfly operation to do all merges of segments of length $\frac{n}{2}$:

1.  Let the segment length be $s = \frac{n}{2}$;
2.  Enumerate together the left endpoints $l_g = 0, 2s, 4s, \cdots, N-2s$ of the segments $\{G(\omega_{n/2}^k)\}$ and the left endpoints $l_h = s, 3s, 5s, \cdots, N-s$ of the segments $\{H(\omega_{n/2}^k)\}$;
3.  To merge two segments, enumerate $k = 0, 1, 2, \cdots, s-1$. Then $G(\omega_{n/2}^k)$ is stored at index $l_g + k$ and $H(\omega_{n/2}^k)$ is stored at index $l_h + k$;
4.  Use the butterfly operation to compute $f(\omega_n^k)$ and $f(\omega_n^{k+n/2})$, and overwrite them in place.

## Inverse fast Fourier transform

The inverse Fourier transform can be expressed with the Fourier transform. There are two ways to understand this.

### Linear algebra view

The IDFT (inverse Fourier transform) converts the point-value form of the target polynomial back to coefficient form. The DFT itself is a linear transformation: treat the target polynomial as a vector and multiply it on the left by a matrix to get the transformed vector, which simulates substituting the complex roots of unity into the polynomial:

$$
\begin{bmatrix}y_0 \\ y_1 \\ y_2 \\ y_3 \\ \vdots \\ y_{n-1} \end{bmatrix}
=
\begin{bmatrix}1 & 1 & 1 & 1 & \cdots & 1 \\
1 & \omega_n^1 & \omega_n^2 & \omega_n^3 & \cdots & \omega_n^{n-1} \\
1 & \omega_n^2 & \omega_n^4 & \omega_n^6 & \cdots & \omega_n^{2(n-1)} \\
1 & \omega_n^3 & \omega_n^6 & \omega_n^9 & \cdots & \omega_n^{3(n-1)} \\
\vdots & \vdots & \vdots & \vdots & \ddots & \vdots \\
1 & \omega_n^{n-1} & \omega_n^{2(n-1)} & \omega_n^{3(n-1)} & \cdots & \omega_n^{(n-1)^2} \end{bmatrix}
\begin{bmatrix} a_0 \\ a_1 \\ a_2 \\ a_3 \\ \vdots \\ a_{n-1} \end{bmatrix}
$$

Now we have the result on the left, and the $x$ values in the middle correspond one-to-one with the point-value representation of the target polynomial. So by basic matrix facts, we just multiply both sides on the left by the inverse of the big matrix in the middle.

Since the entries of this matrix are very special, its inverse is also special: take the **reciprocal** of each entry and then **divide by the transform length $n$**, and you get the inverse matrix.

Note: the length of the Fourier transform is not the length of the polynomial; the transform length must be longer than the length of the product polynomial. If the polynomials to multiply are not long enough, pad their high-order terms with $0$.

To make each entry the reciprocal of the original, by Euler's formula we get

$$
\frac{1}{\omega_k}=\omega_k^{-1}=\mathrm{e}^{-\frac{2\pi \mathrm{i}}{k}}=\cos\left(\frac{2\pi}{k}\right)+\mathrm{i} \sin\left(-\frac{2\pi}{k}\right)
$$

So we can take the root of unity $\omega_k$ to be $\mathrm{e}^{-\frac{2\pi \mathrm{i}}{k}}$, and then our results become the reciprocals of the original. The only extra step is to **divide by the length $n$**; everything else is exactly the same as the DFT. We can write one function with an extra parameter $1$ or $-1$ and multiply it into $\pi$. Passing $1$ gives the DFT, and passing $-1$ gives the IDFT.

### Periodicity of complex roots of unity

The relation between IDFT and DFT can also be understood through the periodicity of complex roots of unity.

Let the original polynomial be $f(x)=a_0+a_1x+a_2x^2+\cdots+a_{n-1}x^{n-1}=\sum_{i=0}^{n-1}a_ix^i$. The IDFT turns the point-value representation back into the coefficient representation.

We use a **construction**. We know $y_i=f\left( \omega_n^i \right),i\in\{0,1,\cdots,n-1\}$ and want $\{a_0,a_1,\cdots,a_{n-1}\}$. Construct the polynomial

$$
A(x)=\sum_{i=0}^{n-1}y_ix^i
$$

That is, we treat $\{y_0,y_1,y_2,\cdots,y_{n-1}\}$ as the coefficient representation of a polynomial $A$.

Now there are two ways to proceed, corresponding to two implementations.

#### Method 1

Let $b_i=\omega_n^{-i}$. Then the point-value representation of $A$ at $x=b_0,b_1,\cdots,b_{n-1}$ is $\left\{ A(b_0),A(b_1),\cdots,A(b_{n-1}) \right\}$.

Rewriting the definition of $A(x)$, we can express $A(b_k)$ as

$$
\begin{aligned}
A(b_k)&=\sum_{i=0}^{n-1}f(\omega_n^i)\omega_n^{-ik}=\sum_{i=0}^{n-1}\omega_n^{-ik}\sum_{j=0}^{n-1}a_j(\omega_n^i)^{j}\\
&=\sum_{i=0}^{n-1}\sum_{j=0}^{n-1}a_j\omega_n^{i(j-k)}=\sum_{j=0}^{n-1}a_j\sum_{i=0}^{n-1}\left(\omega_n^{j-k}\right)^i\\
\end{aligned}
$$

Let $S\left(\omega_n^a\right)=\sum_{i=0}^{n-1}\left(\omega_n^a\right)^i$.

When $a=0 \pmod{n}$, $S\left(\omega_n^a\right)=n$.

When $a\neq 0 \pmod{n}$, we shift and subtract:

$$
\begin{aligned}
S\left(\omega_n^a\right)&=\sum_{i=0}^{n-1}\left(\omega_n^a\right)^i\\
\omega_n^a S\left(\omega_n^a\right)&=\sum_{i=1}^{n}\left(\omega_n^a\right)^i\\
S\left(\omega_n^a\right)&=\frac{\left(\omega_n^a\right)^n-\left(\omega_n^a\right)^0}{\omega_n^a-1}=0\\
\end{aligned}
$$

That is,

$$
S\left(\omega_n^a\right)=
\begin{cases}
n,&a=0\\
0,&a\neq 0
\end{cases}
$$

Substituting back into the original formula,

$$
A(b_k)=\sum_{j=0}^{n-1}a_jS\left(\omega_n^{j-k}\right)=a_k\cdot n
$$

So for the points $b_i=\omega_n^{-i}$, the point-value representation of $A$ is

$$
\begin{aligned}
&\left\{ (b_0,A(b_0)),(b_1,A(b_1)),\cdots,(b_{n-1},A(b_{n-1})) \right\}\\
=&\left\{ (b_0,a_0\cdot n),(b_1,a_1\cdot n),\cdots,(b_{n-1},a_{n-1}\cdot n) \right\}
\end{aligned}
$$

In summary, we take the reciprocal roots of unity, run the FFT on $\{y_0,y_1,y_2,\cdots,y_{n-1}\}$, and divide by $n$ to get the coefficient representation of $f(x)$.

#### Method 2

We substitute $\omega_n^i$ directly into $A(x)$.

The derivation is much the same as in Method 1, and we get $A(\omega_n^k) = \sum_{j=0}^{n-1}a_jS\left(\omega_n^{j+k}\right)$.

$S\left(\omega_n^{j+k}\right) = n$ if and only if $j+k=0 \pmod{n}$, and it is $0$ otherwise. So $A(\omega_n^k) = a_{n-k}\cdot n$.

This means that if we apply the DFT to $\{y_0,y_1,y_2,\cdots,y_{n-1}\}$, divide by $n$, and then reverse the last $n - 1$ elements, we also recover the coefficient representation of $f(x)$.

### Implementation

So our FFT function can do both DFT and IDFT. The code is as follows:

???+ note "Non-recursive FFT (Method 1)"
    ```cpp
    /*
     * Perform FFT
     * len must be of the form 2^k
     * on == 1 means DFT, on == -1 means IDFT
     */
    void fft(Complex y[], int len, int on) {
      // Bit-reversal permutation
      change(y, len);
      // Simulate the merging: first merge length 1 into length 2, and so on up to length len.
      for (int h = 2; h <= len; h <<= 1) {
        // wn: step between consecutive complex roots of unity: w^1_h
        Complex wn(cos(2 * PI / h), sin(on * 2 * PI / h));
        // Merge, len / h times in total.
        for (int j = 0; j < len; j += h) {
          // Current complex root of unity: starts at 1 = w^0_n, then grows by a factor of wn each step: w^1_n
          // ...
          Complex w(1, 0);
          for (int k = j; k < j + h / 2; k++) {
            // The left part and the right part are the solutions of the subproblems
            Complex u = y[k];
            Complex t = w * y[k + h / 2];
            // This adds up the results of the two halves
            y[k] = u + t;
            y[k + h / 2] = u - t;
            // The omega in the second half of a "step" is always the negative of the one in the first half
            // A point on the "red circle" comes back after a full turn and becomes its negative after half a turn
            // The square of the negative of a number equals the square of the number itself
            w = w * wn;
          }
        }
      }
      // For IDFT, each entry of the inverse matrix is not only the reciprocal of the original entry, but also divided by the length len.
      if (on == -1) {
        for (int i = 0; i < len; i++) {
          y[i].x /= len;
          y[i].y /= len;
        }
      }
    }
    ```

???+ note "Non-recursive FFT (Method 2)"
    ```cpp
    /*
     * Perform FFT
     * len must be of the form 2^k
     * on == 1 means DFT, on == -1 means IDFT
     */
    void fft(Complex y[], int len, int on) {
      change(y, len);
      for (int h = 2; h <= len; h <<= 1) {             // simulate the merging
        Complex wn(cos(2 * PI / h), sin(2 * PI / h));  // compute the current complex root of unity
        for (int j = 0; j < len; j += h) {
          Complex w(1, 0);  // compute the current complex root of unity
          for (int k = j; k < j + h / 2; k++) {
            Complex u = y[k];
            Complex t = w * y[k + h / 2];
            y[k] = u + t;  // this adds up the results of the two halves
            y[k + h / 2] = u - t;
            // The omega in the second half of a "step" is always the negative of the one in the first half
            // A point on the "red circle" comes back after a full turn and becomes its negative after half a turn
            // The square of the negative of a number equals the square of the number itself
            w = w * wn;
          }
        }
      }
      if (on == -1) {
        reverse(y + 1, y + len);
        for (int i = 0; i < len; i++) {
          y[i].x /= len;
          y[i].y /= len;
        }
      }
    }
    ```

??? note "FFT template ([HDU 1402 - A * B Problem Plus](http://acm.hdu.edu.cn/showproblem.php?pid=1402))"
    ```cpp
    --8<-- "docs/math/code/poly/fft/fft_3.cpp"
    ```

## References

1.  [Taojiang's algorithm notes (in Chinese)](https://zhuanlan.zhihu.com/p/41867199).
