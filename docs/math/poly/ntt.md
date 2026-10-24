author: ChungZH, Yukimaikoriya, tigerruanyifan, isdanni, Saisyc, 383494, Tiphereth-A, XuYueming520

## Introduction

The **number-theoretic transform** (NTT) is the discrete Fourier transform (DFT) carried out over number-theoretic structures; the **fast number-theoretic transform** (FNTT) is the [fast Fourier transform](./fft.md) (FFT) carried out over number-theoretic structures.

The **number-theoretic transform** is a fast algorithm for computing convolutions. The most common such algorithm is the fast Fourier transform mentioned earlier. However, the fast Fourier transform has some practical drawbacks. For example, the data vector has to be multiplied by a matrix of complex coefficients, and the real and imaginary parts of each complex coefficient are a sine and a cosine, so most coefficients are floating-point numbers. This means we have to do complex floating-point arithmetic, which is more expensive and produces larger errors.

NTT handles polynomial multiplication with a modulus. You could say it is somewhat limited by the modulus, and the numbers are fairly large. The most common modulus today is 998244353.

## Prerequisites

To learn the number-theoretic transform, you need: the discrete Fourier transform, generated subgroups, [primitive roots](../number-theory/primitive-root.md), and discrete logarithms. You can learn these on their own pages; we will not repeat them here.

## Definition

### Number-theoretic transform

In mathematics, the NTT is the discrete Fourier transform (DFT) over an arbitrary [ring](../algebra/basic.md#环). In the case of a finite field, it is usually called the number-theoretic transform (NTT).

The **number-theoretic transform** (NTT) is obtained by moving the discrete Fourier transform to $F={\mathbb {Z}/p}$, the integers modulo a prime $p$. This is a **finite field**, and as long as $n$ divides $p-1$, a primitive $n$-th root of unity exists, so we have $p=\xi n+1$ for a positive integer $\xi$. Concretely, for a prime $p=qn+1, (n=2^m)$, the primitive root $g$ satisfies $g^{qn} \equiv 1 \pmod p$. Treat $g_n=g^q\pmod p$ as the equivalent of $\omega_n$; it has similar properties, such as $g_n^n \equiv 1 \pmod p, g_n^{n/2} \equiv -1 \pmod p$.

Because number theory is involved here, $N$ (we call this $n$ "$N$" to tell it apart from the $n$ in FFT) can be larger than the $n$ in FFT. Just treat $\frac{qN}{n}$ as the $q$ here, and the size issue goes away.

Common choices are:

$$
p = 167772161 = 5 \times 2^{25}+1, g=3
$$

$$
p = 469762049 = 7 \times 2^{26}+1, g=3
$$

$$
p = 754974721 = 3^2 \times 5 \times 2^{24}+1, g=11
$$

$$
p = 998244353 = 7 \times 17 \times 2^{23}+1, g=3
$$

$$
p = 1004535809 = 479 \times 2^{21}+1, g=3
$$

Here $g^{qn}$ plays the role of $\mathrm{e}^{2\pi \mathrm{i} n}$.

When the iteration reaches length $l$, $g_l = g^{\frac{p-1}{l}}$, or $\omega_n = g_l = g_N^{\frac{N}{l}} = g_N^{\frac{p-1}{l}}$.

## Fast number-theoretic transform

The **fast number-theoretic transform** (FNTT) is the fast algorithm obtained by adding divide and conquer to the number-theoretic transform (NTT).

The divide-and-conquer approach used by the fast number-theoretic transform is exactly the same as the one used by the fast Fourier transform. This means you can get code for the fast number-theoretic transform by making simple changes to fast Fourier transform code.

In competitive programming, the term NTT usually actually means the fast number-theoretic transform; "number-theoretic transform" is generally taken to mean "fast number-theoretic transform" by default.

The logic of this shorthand is similar to that of the fast Fourier transform. In fact, the term "fast Fourier transform" (FFT) refers to the "fast discrete Fourier transform" (FDFT). But since the "fast" part only applies to the discrete case, and even only to the special case where the order of the primitive root of unity is a power of $2$, and it cannot apply to the continuous case, the word "discrete" is dropped and FDFT becomes FFT. That is, FFT always refers to the special discrete case.

The number-theoretic transform and the fast number-theoretic transform work modulo a number. There is no continuous case; they are always discrete, so there is no need to mention the word discrete.

In algorithms, an operation that is not sped up is pointless. The fast Fourier transform article introduces the term DFT because the DFT also has other concrete uses in signal processing and image processing, and because the DFT is the principle behind, and a prerequisite for, the FFT.

When there is no risk of confusion, NTT is often used to mean FNTT. To avoid confusion in what follows, the terms NTT and FNTT are kept separate below.

The exact relationship between DFT, FFT, NTT and FNTT is:

-   Adding divide and conquer to DFT and NTT gives FFT and FNTT. For how and why the divide-and-conquer step works, see the fast Fourier transform article.

-   Starting from DFT and FFT, replace complex addition and multiplication with addition and multiplication modulo $p$ (values are usually kept between $0$ and $p-1$), and replace the primitive root of unity with a primitive root of unity of the same order modulo $p$, where the order is a power of $2$. This gives NTT and FNTT.

Since the replaced operations only involve addition and multiplication, DFT, FFT, NTT and FNTT all work on the same principle. They all work over a ring with addition and multiplication, and do not need the stricter condition of a field that also supports division.

In fact, as long as there is a primitive root, i.e. a generator in group-theory terms, NTT or FNTT can be done under that modulus. The moduli $1$, $2$ and $4$ are too small to be of practical use. For an odd prime $p$ and a positive integer $\alpha$, as long as we are given a primitive root $g$ modulo $p^\alpha$ or $2p^\alpha$, NTT or FNTT can still be done in the same way.

## Template

??? example "[Library Checker - Convolution](https://judge.yosupo.jp/problem/convolution_mod)"
    ```cpp
    --8<-- "docs/math/code/poly/ntt/ntt_1.cpp"
    ```

## References and further reading

1.  [FWT (Fast Walsh Transform) explained from scratch qaq (ACM/OI)](https://zhuanlan.zhihu.com/p/41867199)
2.  [FFT (Fast Fourier Transform) explained from scratch! With NTT (ACM/OI)](https://zhuanlan.zhihu.com/p/40505277)
3.  [Number-theoretic transform(NTT) - Wikipedia](https://en.wikipedia.org/wiki/Discrete_Fourier_transform_%28general%29#Number-theoretic_transform)
4.  [Tutorial on FFT/NTT—The tough made simple. (Part 1)](https://codeforces.com/blog/entry/43499)
5.  [NTT template - BlackJack\_ CSDN blog](https://blog.csdn.net/blackjack_/article/details/79346433)
