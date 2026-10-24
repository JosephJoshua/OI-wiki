author: iamtwz, billchenchina, CBW2007, CCXXXI, chinggg, Enter-tainer, eyedeng, FFjet, gaojude, Great-designer, H-J-Granger, Henry-ZHR, hsfzLZH1, Ir1d, kenlig, Konano, ksyx, luoguyuntianming, Marcythm, Menci, NachtgeistW, ouuan, Peanut-Tang, qwqAutomaton, sshwy, StudyingFather, Tiphereth-A, TrisolarisHD, TRSWNCA, Xeonacid, Yuuko10032, Zhangjiacheng2006, Zhoier, Hszzzx, shenshuaijie, kfy666

## Introduction

**Fast exponentiation**, also called **binary exponentiation** or **exponentiation by squaring**, is a small trick for computing $a^n$ in $\Theta(\log n)$ time, while the brute-force computation takes $\Theta(n)$ time.

The trick works in any setting where multiplication of $a$ is associative, for example modular exponentiation and matrix powers. See the [Applications](#applications) section below for details.

## How it works

Computing the $n$-th power of $a$ means multiplying $n$ copies of $a$ together: $a^{n} = \underbrace{a \times a \cdots \times a}_{n\text{ copies of a}}$. But when $n$ is too large or a single multiplication is too expensive, this approach does not work well. The idea of binary exponentiation is to split the task into smaller tasks according to the **binary representation** of the exponent.

???+ example "Example"
    Suppose we want to compute $3^{13}$. Writing it out as a product takes $13-1=12$ multiplications. But since
    
    $$
    3^{13} = 3^{(1101)_2} = 3^8 \times 3^4 \times 3^1,
    $$
    
    as long as we can quickly compute $3^{1},3^{2},3^{4},3^{8}$, we can get $3^{13}$ with $2$ more multiplications. So we only need a fast way to compute this sequence of powers $3^{2^k}$. That is easy, because every element of the sequence (except the first) is the square of the previous one.
    
    Based on this, $3^{13}$ is computed as follows:
    
    $$
    \begin{aligned}
    3^1 &= 3, \\
    3^2 &= \left(3^1\right)^2 = 3^2 = 9, \\
    3^4 &= \left(3^2\right)^2 = 9^2 = 81, \\
    3^8 &= \left(3^4\right)^2 = 81^2 = 6561, \\
    3^{13} &= 6561 \times 81 \times 3 = 1594323.
    \end{aligned}
    $$
    
    Only $5$ multiplications are used in the process.

This is the basic idea of fast exponentiation. There are two common ways to implement it.

### Iterative version

Let the binary representation of $n$ be $(n_tn_{t-1}\cdots n_1n_0)_2$, that is,

$$
n = n_t2^t + n_{t-1}2^{t-1} + \cdots + n_12^1 + n_02^0,
$$

where $n_i\in\{0,1\}$. Then

$$
\begin{aligned}
a^n & = a^{n_t2^t + n_{t-1}2^{t-1} + \cdots + n_12^1 + n_02^0}\\
& = a^{n_0 2^0} \times a^{n_1 2^1}\times \cdots \times a^{n_{t-1}2^{t-1}} \times a^{n_t2^t}.
\end{aligned}
$$

Note that only the terms with $n_i=1$ actually appear in the product.

From this expression, we can first compute the $\Theta(\log n)$ values $a^{2^k}$ in $\Theta(\log n)$ time, and then spend $\Theta(\log n)$ time multiplying the powers whose binary digit is $1$ into the final result. This is the iterative version of fast exponentiation.

The pseudocode is as follows:

$$
\begin{array}{l}
\textbf{Algorithm }\text{FastPow}(a, n): \\
\textbf{Input. }\text{Base }a\text{ and exponent }n.\\
\textbf{Output. }\text{Power }a^n.\\
\textbf{Method.}\\
\begin{array}{ll}
1 & \textit{result}\gets\mathrm{Id}\\
2 & \textbf{while }n > 0\textbf{ do}\\
3 & \qquad \textbf{if }n \bmod 2 = 1\textbf{ then}\\
4 & \qquad \qquad \textit{result} \gets \textit{result}\cdot a\\
5 & \qquad \textbf{end if}\\
6 & \qquad a \gets a \cdot a\\
7 & \qquad n \gets n / 2\\
8 & \textbf{end while}\\
9 & \textbf{return }\textit{result}
\end{array}
\end{array}
$$

Computing a power this way takes $\Theta(\log n)$ multiplications.

### Recursive version

The same process can also be written recursively. Note that the binary expansion of the exponent $n$ can be written recursively as

$$
(n_tn_{t-1}\cdots n_1n_0)_2 = 2 \times (n_tn_{t-1}\cdots n_1)_2 + n_0.
$$

So the power $a^n$ can be computed recursively as

$$
a^n = \begin{cases}
1, & n = 0,\\
(a^{\lfloor n/2\rfloor})^2, & n > 0 \text{ and }n\text{ is even},\\
(a^{\lfloor n/2\rfloor})^2\cdot a, & n > 0 \text{ and }n\text{ is odd}.\\
\end{cases}
$$

This is the recursive version of fast exponentiation.

The pseudocode is as follows:

$$
\begin{array}{l}
\textbf{Algorithm }\text{FastPow}(a, n): \\
\textbf{Input. }\text{Base }a\text{ and exponent }n.\\
\textbf{Output. }\text{Power }a^n.\\
\textbf{Method.}\\
\begin{array}{ll}
1 & \textbf{if }n = 0\textbf{ then}\\
2 & \qquad \textbf{return }\mathrm{Id}\\
3 & \textbf{end if}\\
4 & \textit{result} \gets \text{FastPow}(a, n / 2) \\
5 & \textbf{if }n\bmod 2 = 0\textbf{ then}\\
6 & \qquad \textbf{return }\textit{result}\cdot\textit{result}\\
7 & \textbf{else}\\
8 & \qquad \textbf{return }\textit{result}\cdot\textit{result}\cdot a\\
9 & \textbf{end if}
\end{array}
\end{array}
$$

Computing a power this way takes $\Theta(\log n)$ levels of recursion, and also $\Theta(\log n)$ multiplications. Although the complexity is the same, recursion has some overhead of its own, so in practice the iterative version is faster.

## Applications

### Modular exponentiation

???+ example "[Luogu P1226 [Template] Fast Exponentiation](https://www.luogu.com.cn/problem/P1226)"
    Given three integers $a,b,p$, compute $a^b\bmod p$, where $p\ge 2$.

This is a very common application; for example, it can be used to compute modular multiplicative inverses. Since taking remainders does not interfere with multiplication, we only need to take the remainder during the computation.

First, we can implement the recursive method above directly:

???+ note "Reference implementation"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/binary-exponentiation/luogu-P1226-1.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/binary-exponentiation/luogu-P1226-1.py:core"
        ```

The second implementation is non-recursive. During the loop, it multiplies the power for each binary digit equal to 1 into the answer. Although both have the same theoretical complexity, the second one is faster in practice, because recursion has some overhead.

???+ note "Reference implementation"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/binary-exponentiation/luogu-P1226-2.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/binary-exponentiation/luogu-P1226-2.py:core"
        ```

???+ warning "Note"
    -   The modulus is usually greater than $1$. In very special cases the modulus $p$ may equal $1$, and then the case $b=0$ needs special handling.
    -   When the exponent is very large, use the [extended Euler's theorem](./number-theory/fermat.md#扩展欧拉定理) to reduce the exponent first.

### Computing Fibonacci numbers

From the recurrence of the Fibonacci sequence $F_n = F_{n-1} + F_{n-2}$, we can build a $2\times 2$ matrix that represents the transformation from $F_i,F_{i+1}$ to $F_{i+1},F_{i+2}$. Then, using the idea of fast exponentiation to compute the $n$-th power of this matrix, we get the result in $\Theta(\log n)$ time. For more details see [Fibonacci sequence](./combinatorics/fibonacci.md); for an implementation of fast matrix exponentiation see [speeding up recurrences with matrices](../math/linear-algebra/matrix.md#矩阵加速递推).

### Applying a permutation many times

???+ note "Problem"
    You are given a sequence of length $n$ and a permutation. Apply the permutation to the sequence $k$ times.

Just raise the permutation to the $k$-th power and apply it to the sequence. The time complexity is $O(n \log k)$. For more details see [composition of permutations](./permutation.md#复合).

???+ warning "Note"
    If you build a graph from the permutation and take the $k$-th power on each cycle separately (which is really the same as taking $k$ modulo the cycle length), you can solve this problem in $O(n)$ time.

### Speeding up operations on point sets in geometry

???+ example "[HDU 4087 A Letter to Programmers](https://acm.hdu.edu.cn/showproblem.php?pid=4087)"
    You are given $n$ points $p_i$ in 3D space and must apply $m$ operations to them. There are 3 kinds of operations:
    
    1.  Move the points along some vector (Shift).
    2.  Scale the coordinates of the points by some factor (Scale).
    3.  Rotate around some line (Rotate).
    
    There is also a special operation that repeats some sequence of operations $k$ times (Repeat), and Repeat operations can be nested. Output the coordinates of every point after all operations.

As explained in [vectors and matrices](./linear-algebra/vector.md#向量与矩阵), each operation can be represented by a transformation matrix, and a series of consecutive transformations can be represented by the product of their matrices. A Repeat operation is just taking the $k$-th power of a matrix. This way the final matrix of the whole sequence of transformations can be computed in $O(m \log k)$ time. Finally, apply it to the $n$ points, for a total complexity of $O(n + m \log k)$.

### Counting paths of fixed length

???+ note "Problem"
    Given a directed graph (with edge weights 1), for every pair of vertices $u,v$, find the number of paths of length $k$ from $u$ to $v$.

Raise the adjacency matrix $M$ of the graph to the $k$-th power; then $M_{i,j}$ is the number of paths of length $k$ from $i$ to $j$. This algorithm runs in $O(n^3 \log k)$ time. For details see the [matrix](./linear-algebra/matrix.md#定长路径统计) page.

### Modular integer multiplication

???+ note "Problem"
    Given non-negative integers $a,b$ and a positive integer $m$, compute $a\times b\bmod m$, where $a,b\le m\le 10^{18}$.

Just like binary exponentiation, we write one of the factors as a sum of integer powers of 2. When we multiply a number by 2 and take the remainder, we can turn this into additions and subtractions to avoid integer overflow. This solves the problem in $O (\log m)$ time. The recursion is as follows:

$$
a \cdot b = \begin{cases}
0 &\text{if }a = 0 \\
2 \cdot \frac{a}{2} \cdot b &\text{if }a > 0 \text{ and }a \text{ even} \\
2 \cdot \frac{a-1}{2} \cdot b + b &\text{if }a > 0 \text{ and }a \text{ odd}
\end{cases}
$$

In practice, however, this method is slow because it adds extra computational cost. In real code, multiplication with a modulus in the `long long` range is usually done with [fast multiplication](./number-theory/mod-arithmetic.md#快速乘).

### Fast exponentiation with big integers

Prerequisite: [big integer multiplication](./bignum.md#乘法)

???+ example "[Luogu P1045 \[NOIP 2003 Junior Group\] Mersenne Number](https://www.luogu.com.cn/problem/P1045)"
    Given an integer $P$ ($1000 < P < 3100000$), compute the number of digits of $2^P−1$ and its last $500$ digits (in decimal). If there are fewer than $500$ digits, pad the high positions with 0.

??? note "Implementation"
    ```cpp
    --8<-- "docs/math/code/binary-exponentiation/luogu-P1045.cpp"
    ```

## Precomputed fast exponentiation with a fixed base

When the base $a$ is fixed, we can use the idea of [sqrt decomposition](../ds/decompose.md): after some preprocessing, each power query can be answered in $O(1)$ time. This algorithm is often called "light-speed exponentiation". It works as follows:

1.  Choose a number $s$, precompute the values $a^0,a^1,\cdots,a^{s-1}$ and $a^0,a^s,\cdots,a^{\lfloor p/s\rfloor s}$, and store them in two arrays;
2.  For each query $a^b$, split $b$ into $\lfloor b/s\rfloor s+(b\bmod s)$. Then $a^b=a^{\lfloor b/s\rfloor s}\cdot a^{b\bmod s}$, and the answer is found in $O(1)$.

If the exponent $b$ is in $[0,n]$, the block length $s$ is often chosen as $\sqrt{n}$ or a power of $2$ close to it. Choosing $\sqrt{n}$ gives the optimal preprocessing complexity $O(\sqrt{n})$, while choosing a power of $2$ lets you simplify the computation with bit operations.

In particular, for modular powers, having the same base $a$ implicitly requires the same modulus $m$ as well. By the [extended Euler's theorem](./number-theory/fermat.md#扩展欧拉定理), for any modulus $m$ the exponent range to precompute has upper bound $n = 2\varphi(m)$; for a prime modulus $p$, the upper bound is $n = p - 1$. In both cases the preprocessing complexity is $O(\sqrt{m})$.

???+ example "Reference code"
    ```cpp
    --8<-- "docs/math/code/binary-exponentiation/pre-exp.cpp:core"
    ```

## Exercises

-   [UVa 1230 - MODEX](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=3671)
-   [UVa 374 - Big Mod](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=310)
-   [UVa 11029 - Leading and Trailing](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1970)
-   [Codeforces - Parking Lot](http://codeforces.com/problemset/problem/630/I)
-   [SPOJ - The last digit](http://www.spoj.com/problems/LASTDIG/)
-   [SPOJ - Locker](http://www.spoj.com/problems/LOCKER/)
-   [SPOJ - Just add it](http://www.spoj.com/problems/ZSUM/)

**Part of this page is translated from the post [Бинарное возведение в степень](http://e-maxx.ru/algo/binary_pow) and its English translation [Binary Exponentiation](https://cp-algorithms.com/algebra/binary-exp.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**
