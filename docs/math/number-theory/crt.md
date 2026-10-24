## Introduction

> The "unknown number of things" problem: there is a number of things, but we don't know how many. Counting them by threes leaves two; counting them by fives leaves three; counting them by sevens leaves two. How many things are there?

That is, find an integer that leaves remainder $2$ when divided by $3$, remainder $3$ when divided by $5$, and remainder $2$ when divided by $7$.

This problem first appeared in the *Sunzi Suanjing* (*The Mathematical Classic of Sunzi*), together with a concrete method for solving it. In 1247, the Song dynasty mathematician Qin Jiushao gave a complete and systematic solution to the "unknown number of things" problem in the section "Dayan Methods" in volumes one and two of his *Shushu Jiuzhang* (*Mathematical Treatise in Nine Sections*). A rhyme for solving the specific problem above was given by the Ming dynasty mathematician Cheng Dawei in his *Suanfa Tongzong* (*General Source of Computational Methods*):

> Three people walking together: seventy is rare; five plum trees: twenty-one branches; seven children reunite: exactly half a month; take away one hundred and five, and you will know.

$2\times 70+3\times 21+2\times 15=233=2\times 105+23$, so the answer is $23$.

## Definition

The Chinese Remainder Theorem (CRT) solves systems of linear congruences in one variable of the following form (where $n_1, n_2, \cdots, n_k$ are pairwise coprime):

$$
\begin{cases}
x &\equiv a_1 \pmod {n_1} \\
x &\equiv a_2 \pmod {n_2} \\
  &\vdots \\
x &\equiv a_k \pmod {n_k} \\
\end{cases}
$$

The "unknown number of things" problem above is one instance of such a system of linear congruences.

## Process

1.  Compute the product $n$ of all moduli;
2.  For the $i$-th equation:
    1.  Compute $m_i=\frac{n}{n_i}$;
    2.  Compute the [modular inverse](./inverse.md)  $m_i^{-1}$ of $m_i$ modulo $n_i$;
    3.  Compute $c_i=m_im_i^{-1}$ (**do not reduce it modulo $n_i$**).
3.  The unique solution of the system modulo $n$ is: $x=\sum_{i=1}^k a_ic_i \pmod n$.

## Implementation

=== "C++"
    ```cpp
    LL CRT(int k, LL* a, LL* r) {
      LL n = 1, ans = 0;
      for (int i = 1; i <= k; i++) n = n * r[i];
      for (int i = 1; i <= k; i++) {
        LL m = n / r[i], b, y;
        exgcd(m, r[i], b, y);  // b * m mod r[i] = 1
        ans = (ans + a[i] * m * b % n) % n;
      }
      return (ans % n + n) % n;
    }
    ```

=== "Python"
    ```python
    def CRT(k, a, r):
        n = 1
        ans = 0
        for i in range(1, k + 1):
            n = n * r[i]
        for i in range(1, k + 1):
            m = n // r[i]
            b = y = 0
            exgcd(m, r[i], b, y)  # b * m mod r[i] = 1
            ans = (ans + a[i] * m * b % n) % n
        return (ans % n + n) % n
    ```

## Proof

We need to show that the $x$ computed by the algorithm above satisfies $x\equiv a_i \pmod {n_i}$ for every $i=1,2,\cdots,k$.

When $i\neq j$, we have $m_j \equiv 0 \pmod {n_i}$, so $c_j \equiv m_j \equiv 0 \pmod {n_i}$. Also, $c_i \equiv m_i \cdot (m_i^{-1} \bmod {n_i}) \equiv 1 \pmod {n_i}$. So we have:

$$
\begin{aligned}
x&\equiv \sum_{j=1}^k a_jc_j                      &\pmod {n_i} \\
 &\equiv a_ic_i                                   &\pmod {n_i} \\
 &\equiv a_i \cdot m_i \cdot (m^{-1}_i \bmod n_i) &\pmod {n_i} \\
 &\equiv a_i                                      &\pmod {n_i}
\end{aligned}
$$

That is, for every $i=1,2,\cdots,k$, the $x$ produced by the algorithm always satisfies $x\equiv a_i \pmod{n_i}$. This proves that the algorithm solves the system of congruences correctly.

Since we put no special restriction on the input $a_i$, every input $\{a_i\}$ corresponds to some solution $x$. Moreover, if $x\neq y$, there is always some $i$ such that $x$ and $y$ are not congruent modulo $n_i$. So the coefficient list $\{a_i\}$ and the solution $x$ are in one-to-one correspondence, and the system always has a unique solution.

## Solution

Below we show how CRT solves the "unknown number of things" problem.

1.  $n=3\times 5\times 7=105$;
2.  Three people walking together: **seventy** is rare: $n_1=3, m_1=n/n_1=35, m_1^{-1}\equiv 2\pmod 3$, so $c_1=35\times 2=70$;
3.  Five plum trees: **twenty-one** branches: $n_2=5, m_2=n/n_2=21, m_2^{-1}\equiv 1\pmod 5$, so $c_2=21\times 1=21$;
4.  Seven children reunite: exactly **half a month**: $n_3=7, m_3=n/n_3=15, m_3^{-1}\equiv 1\pmod 7$, so $c_3=15\times 1=15$;
5.  So the unique solution of the system is $x\equiv 2\times 70+3\times 21+2\times 15\equiv 233\equiv 23 \pmod {105}$. (Take away **one hundred and five**, and you will know.)

## Garner's algorithm

Another use of CRT is to represent a large integer by a set of smaller primes.

For example, suppose $a$ satisfies the following system of linear congruences, and $a < \prod_{i=1}^k p_i$ (where each $p_i$ is prime):

$$
\begin{cases}
a &\equiv a_1 \pmod {p_1} \\
a &\equiv a_2 \pmod {p_2} \\
  &\vdots \\
a &\equiv a_k \pmod {p_k} \\
\end{cases}
$$

We can represent $a$ in the following form (called the mixed radix representation of $a$):

$$
a = x_1 + x_2 p_1 + x_3 p_1 p_2 + \ldots + x_k p_1 \ldots p_{k-1}
$$

**Garner's algorithm** computes the coefficients $x_1, \ldots, x_k$.

Let $r_{ij}$ be the [inverse](./inverse.md) of $p_i$ modulo $p_j$:

$$
p_i \cdot r_{i,j} \equiv 1 \pmod{p_j}
$$

Substituting $a$ into the first equation, we get:

$$
a_1 \equiv x_1 \pmod{p_1}
$$

Substituting into the second equation gives:

$$
a_2 \equiv x_1 + x_2 p_1 \pmod{p_2}
$$

Subtracting $x_1$ from both sides and dividing by $p_1$ gives

$$
\begin{aligned}
    a_2 - x_1           &\equiv x_2 p_1             &\pmod{p_2} \\
    (a_2 - x_1) r_{1,2} &\equiv x_2                 &\pmod{p_2} \\
    x_2                 &\equiv (a_2 - x_1) r_{1,2} &\pmod{p_2}
\end{aligned}
$$

In the same way, we get:

$$
x_k=(\dots((a_k-x_1)r_{1,k}-x_2)r_{2,k})-\dots)r_{k-1,k} \bmod p_k
$$

??? note "Implementation"
    === "C++"
        ```cpp
        for (int i = 0; i < k; ++i) {
          x[i] = a[i];
          for (int j = 0; j < i; ++j) {
            x[i] = r[j][i] * (x[i] - x[j]);
            x[i] = x[i] % p[i];
            if (x[i] < 0) x[i] += p[i];
          }
        }
        ```
    
    === "Python"
        ```python
        for i in range(0, k):
            x[i] = a[i]
            for j in range(0, i):
                x[i] = r[j][i] * (x[i] - x[j])
                x[i] = x[i] % p[i]
                if x[i] < 0:
                    x[i] = x[i] + p[i]
        ```

The time complexity of this algorithm is $O(k^2)$. In fact, Garner's algorithm does not require the moduli to be prime; it only requires them to be pairwise coprime. Here is the pseudocode:

$$
\begin{array}{ll}
&\textbf{Chinese Remainder Algorithm }\operatorname{cra}(\mathbf{v}, \mathbf{m})\text{:} \\
&\textbf{Input}\text{: }\mathbf{m}=(m_0,m_1,\dots ,m_{n-1})\text{, }m_i\in\mathbb{Z}^+\land\gcd(m_i,m_j)=1\text{ for all } i\neq j\text{,} \\
&\qquad \mathbf{v}=(v_0,\dots ,v_{n-1}) \text{ where }v_i=x\bmod m_i\text{.} \\
&\textbf{Output}\text{: }x\bmod{\prod_{i=0}^{n-1} m_i}\text{.} \\
1&\qquad \textbf{for }i\text{ from }1\text{ to }(n-1)\textbf{ do} \\
2&\qquad \qquad C_i\gets \left(\prod_{j=0}^{i-1}m_j\right)^{-1}\bmod{m_i} \\
3&\qquad x\gets v_0 \\
4&\qquad \textbf{for }i\text{ from }1\text{ to }(n-1)\textbf{ do} \\
5&\qquad \qquad u\gets (v_i-x)\cdot C_i\bmod{m_i} \\
6&\qquad \qquad x\gets x+u\prod_{j=0}^{i-1}m_j \\
7&\qquad \textbf{return }(x)
\end{array}
$$

Notice that the computation on line 6 matches the mixed radix representation above.

## Applications

In some counting or number theory problems, whether to make the code longer, to make the problem harder, or for some other reason, the given modulus is **not a prime**!

But if we factor it, we find that it has no square factors; that is, the modulus is a product of distinct primes.

Then we can compute the answer modulo each of these primes separately, and finally combine the answers with CRT.

The following problem is a good example.

???+ note "[Luogu P2480 \[SDOI2010\] Ancient Pig Script](https://www.luogu.com.cn/problem/P2480)"
    Given $G,n$ ($1 \leq G,n \leq 10^9$), compute:
    
    $$
    G^{\sum_{k\mid n}\binom{n}{k}} \bmod 999~911~659
    $$

First, when $G=999~911~659$, the answer is clearly $0$.

Otherwise, by [Euler's theorem](./fermat.md), the answer is:

$$
G^{\sum_{k\mid n}\binom{n}{k} \bmod 999~911~658} \bmod 999~911~659
$$

Now consider how to compute:

$$
\sum_{k\mid n}\binom{n}{k} \bmod 999~911~658
$$

Since $999~911~658$ is not prime, we cannot guarantee that every $x \in [1,999~911~657]$ has a modular inverse, so we cannot compute the expression above directly.

Notice that $999~911~658=2 \times 3 \times 4679 \times 35617$, where each prime factor appears with exponent one. So we can compute $\sum_{k\mid n}\binom{n}{k}$ modulo each of the primes $2$, $3$, $4679$, $35617$ separately, and finally combine the answers with the Chinese remainder theorem.

In other words, what we actually need is the solution of the following system of linear congruences:

$$
\begin{cases}
x \equiv a_1 \pmod 2\\
x \equiv a_2 \pmod 3\\
x \equiv a_3 \pmod {4679}\\
x \equiv a_4 \pmod {35617}
\end{cases}
$$

To compute a binomial coefficient modulo a small prime, we can use [Lucas's theorem](./lucas.md).

## Extension: moduli that are not coprime

### Two equations

Let the two equations be $x\equiv a_1 \pmod {m_1}$ and $x\equiv a_2 \pmod {m_2}$;

Turn them into a Diophantine equation: $x=m_1p+a_1=m_2q+a_2$, where $p, q$ are integers. Then $m_1p-m_2q=a_2-a_1$.

By [Bézout's theorem](./bezouts.md), if $a_2-a_1$ is not divisible by $\gcd(m_1,m_2)$, there is no solution;

Otherwise, we can find one feasible solution $(p, q)$ with the [extended Euclidean algorithm](./gcd.md);

Then the solution of the system formed by the two original equations is $x\equiv b\pmod M$, where $b=m_1p+a_1$ and $M=\text{lcm}(m_1, m_2)$.

### Multiple equations

Just merge the equations two at a time using the method above.

## Exercises

-   [[Template] Chinese Remainder Theorem (CRT) / Cao Chong Raises Pigs](https://www.luogu.com.cn/problem/P1495)
-   [[Template] Extended Chinese Remainder Theorem](https://www.luogu.com.cn/problem/P4777)
-   [NOI2018 The Dragon-Slaying Warrior](https://uoj.ac/problem/396)
-   [TJOI2009 Guess the Number](https://www.luogu.com.cn/problem/P3868)

    **Parts of this page are translated from the blog post [Китайская теорема об остатках](http://e-maxx.ru/algo/chinese_theorem) and its English translation [Chinese Remainder Theorem](https://cp-algorithms.com/algebra/chinese-remainder-theorem.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**
