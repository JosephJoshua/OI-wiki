author: inkydragon, TravorLZH, YOYO-UIAT, wood3, shuzhouliu, Mr-Python-in-China, HeRaNO, weilycoder

## Prime sieves

### Introduction

What if we want to know how many primes there are up to $n$?

A natural idea is to run a primality test on every number up to $n$. This brute-force approach clearly cannot reach the best complexity.

### Sieve of Eratosthenes

#### How it works

Consider this fact: for any positive integer $n$ greater than $1$, every multiple $xn$ with $x > 1$ is composite. Using this, we can avoid many unnecessary checks.

If we go through the numbers from small to large and, at each number, mark all of its (larger) multiples as composite, then the numbers left unmarked at the end are exactly the primes.

#### Implementation

=== "C++"
    ```cpp
    vector<int> prime;
    bool is_prime[N];
    
    void Eratosthenes(int n) {
      is_prime[0] = is_prime[1] = false;
      for (int i = 2; i <= n; ++i) is_prime[i] = true;
      for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
          prime.push_back(i);
          if ((long long)i * i > n) continue;
          for (int j = i * i; j <= n; j += i)
            // multiples of 2 to i - 1 were already sieved, so start directly
            // from i times i, which makes it run faster
            is_prime[j] = false;  // multiples of i are not prime
        }
      }
    }
    ```

=== "Python"
    ```python
    prime = []
    is_prime = [False] * N
    
    
    def Eratosthenes(n):
        is_prime[0] = is_prime[1] = False
        for i in range(2, n + 1):
            is_prime[i] = True
        for i in range(2, n + 1):
            if is_prime[i]:
                prime.append(i)
                if i * i > n:
                    continue
                for j in range(i * i, n + 1, i):
                    is_prime[j] = False
    ```

This is the **sieve of Eratosthenes** (Eratosthenes' sieve for short). Its time complexity is $O(n\log\log n)$.

???+ note "Proof"
    Let's go through the derivation.
    
    If each operation on the array costs 1 unit of time, the time complexity is:
    
    $$
    O\left(\sum_{k=1}^{\pi(n)}{\frac{n}{p_k}}\right)=O\left(n\sum_{k=1}^{\pi(n)}{\frac{1}{p_k}}\right)
    $$
    
    Here $p_k$ is the $k$-th smallest prime and $\pi(n)$ is the number of primes $\le n$. $\sum_{k=1}^{\pi(n)}$ stands for the outer for loop, where the upper limit $\pi(n)$ is the number of times `if (prime[i])` takes the true branch; $\frac{n}{p_k}$ is the number of iterations of the inner for loop.
    
    By Mertens' second theorem, there is a constant $B_1$ such that:
    
    $$
    \sum_{k=1}^{\pi(n)}{\frac{1}{p_k}}=\log\log n+B_1+O\left(\frac{1}{\log n}\right)
    $$
    
    So the time complexity of the **sieve of Eratosthenes** is $O(n\log\log n)$. Next we prove a weaker version of Mertens' second theorem, $\sum_{k\le\pi(n)}1/p_k=O(\log\log n)$:
    
    Since $\pi(n)=\Theta(n/\log n)$, the $n$-th prime is $\Theta(n\log n)$. So
    
    $$
    \begin{aligned}
    \sum_{k=1}^{\pi(n)}{\frac{1}{p_k}}
    &=O\left(\sum_{k=2}^{\pi(n)}{\frac{1}{k\log k}}\right) \\
    &=O\left(\int_2^{\pi(n)}{\frac{\mathrm dx}{x\log x}}\right) \\
    &=O(\log\log\pi(n))=O(\log\log n)
    \end{aligned}
    $$
    
    Of course, the approach above is still not efficient enough. The methods below can speed it up somewhat.

#### Sieving up to the square root

Clearly, to find all primes up to $n$, it is enough to sieve with the primes not exceeding $\sqrt n$.

=== "C++"
    ```cpp
    vector<int> prime;
    bool is_prime[N];
    
    void Eratosthenes(int n) {
      is_prime[0] = is_prime[1] = false;
      for (int i = 2; i <= n; ++i) is_prime[i] = true;
      // i * i <= n means i <= sqrt(n)
      for (int i = 2; i * i <= n; ++i) {
        if (is_prime[i])
          for (int j = i * i; j <= n; j += i) is_prime[j] = false;
      }
      for (int i = 2; i <= n; ++i)
        if (is_prime[i]) prime.push_back(i);
    }
    ```

=== "Python"
    ```python
    prime = []
    is_prime = [False] * N
    
    
    def Eratosthenes(n):
        is_prime[0] = is_prime[1] = False
        for i in range(2, n + 1):
            is_prime[i] = True
        # let i loop up to <= sqrt(n)
        for i in range(2, isqrt(n) + 1):  # `isqrt` was added in Python 3.8
            if is_prime[i]:
                for j in range(i * i, n + 1, i):
                    is_prime[j] = False
        for i in range(2, n + 1):
            if is_prime[i]:
                prime.append(i)
    ```

This optimization does not change the asymptotic time complexity. Repeating the proof above, we get $n \ln \ln \sqrt n + o(n)$. By the properties of logarithms, this is asymptotically the same, but the number of operations drops noticeably.

#### Sieving only odd numbers

Every even number other than 2 is composite, so we can skip them and only care about odd numbers.

First, this halves the memory we need. Second, it also roughly halves the number of operations.

#### Reducing memory usage

Note that sieving only needs an array of type `bool`. One element of a `bool` array usually takes $1$ byte (i.e., $8$ bits), but storing a boolean only needs $1$ bit.

Using [bit manipulation](../bit.md), we can pack each boolean into a single bit. Then we only need $n$ bits (i.e., $\dfrac n 8$ bytes) instead of $n$ bytes, which greatly reduces memory usage. This is called "bit packing".

It is worth noting that some data structures do bit packing automatically, such as `vector<bool>` and `bitset<>` in C++.

Also, `vector<bool>` and `bitset<>` give constant-factor speedups. With `bitset<>` or `vector<bool>`, the $O(n \log \log n)$ sieve of Eratosthenes can even outperform the $O(n)$ Euler sieve.

See [bitset: combining with the sieve of Eratosthenes](../../lang/csl/bitset.md#与埃氏筛结合).

#### Segmented sieve

From the "sieving up to the square root" optimization, we don't need to keep the whole `is_prime[1...n]` array. For sieving, it is enough to keep the primes up to $\sqrt n$, i.e., `prime[1...sqrt(n)]`. Then we split the whole range into blocks and sieve each block separately. This way we never need several blocks in memory at once, and the CPU can make better use of the cache.

Let $s$ be a constant that sets the block size. Then there are $\lceil {\frac n s} \rceil$ blocks, and block $k$ ($k = 0 \dots \lfloor {\frac n s} \rfloor$) contains the numbers in the interval $[ks, ks + s - 1]$. We process the blocks in order: for each block $k$, we go through all primes (from $1$ to $\sqrt n$) and sieve with them.

Note that we need to change the strategy slightly for the first block: first, we should keep all primes in $[1, \sqrt n]$; second, the numbers $0$ and $1$ should be marked as non-prime. When processing the last block, don't forget that the last number $n$ is not necessarily at the end of the block.

The implementation below uses a segmented sieve to count the primes up to $n$.

???+ note "Implementation"
    ```cpp
    int count_primes(int n) {
      constexpr static int S = 10000;
      vector<int> primes;
      int nsqrt = sqrt(n);
      vector<char> is_prime(nsqrt + 1, true);
      for (int i = 2; i <= nsqrt; i++) {
        if (is_prime[i]) {
          primes.push_back(i);
          for (int j = i * i; j <= nsqrt; j += i) is_prime[j] = false;
        }
      }
      int result = 0;
      vector<char> block(S);
      for (int k = 0; k * S <= n; k++) {
        fill(block.begin(), block.end(), true);
        int start = k * S;
        for (int p : primes) {
          int start_idx = (start + p - 1) / p;
          int j = max(start_idx, p) * p - start;
          for (; j < S; j += p) block[j] = false;
        }
        if (k == 0) block[0] = block[1] = false;
        for (int i = 0; i < S && start + i <= n; i++) {
          if (block[i]) result++;
        }
      }
      return result;
    }
    ```

The segmented sieve has the same asymptotic time complexity as the sieve of Eratosthenes (unless the blocks are very small), but the memory needed shrinks to $O(\sqrt{n} + S)$, and it uses the cache better.
On the other hand, we have to do a division for each pair of a block and a prime in $[1, \sqrt{n}]$, which is much worse for small blocks.
So we need to strike a balance when choosing the constant $S$.

A block size $S$ between $10^4$ and $10^5$ gives the best speed.

### Linear sieve

The sieve of Eratosthenes can still be improved: it marks a composite number many times. Is there a way to skip these useless steps? Yes.

If every composite number is marked only once, the time complexity drops to $O(n)$.

???+ note "Implementation"
    === "C++"
        ```cpp
        vector<int> pri;
        bool not_prime[N];
        
        void pre(int n) {
          for (int i = 2; i <= n; ++i) {
            if (!not_prime[i]) {
              pri.push_back(i);
            }
            for (int pri_j : pri) {
              if (i * pri_j > n) break;
              not_prime[i * pri_j] = true;
              if (i % pri_j == 0) {
                // i % pri_j == 0
                // in other words, i was already sieved by pri_j
                // the primes in pri are in increasing order, so i times any later
                // prime will be sieved by a multiple of pri_j; no need to do it now,
                // so just break here
                break;
              }
            }
          }
        }
        ```
    
    === "Python"
        ```python
        pri = []
        not_prime = [False] * N
        
        
        def pre(n):
            for i in range(2, n + 1):
                if not not_prime[i]:
                    pri.append(i)
                for pri_j in pri:
                    if i * pri_j > n:
                        break
                    not_prime[i * pri_j] = True
                    if i % pri_j == 0:
                        """
                        i % pri_j == 0
                        in other words, i was already sieved by pri_j
                        the primes in pri are in increasing order, so i times any later
                        prime will be sieved by a multiple of pri_j; no need to do it now,
                        so just break here
                        """
                        break
        ```

The **linear sieve** above is also called the **Euler sieve**.

???+ note "Note"
    Note that while sieving for primes, we also get the smallest prime factor of every number.

## Sieving Euler's totient function

In the linear sieve, every composite number is sieved out by its smallest prime factor. For example, let $p_1$ be the smallest prime factor of $n$ and $n' = \frac{n}{p_1}$. Then in the linear sieve, $n$ is sieved out as $n' \times p_1$.

Looking at the linear sieve, there are two cases to handle. We split on $n' \bmod p_1$.

If $n' \bmod p_1 = 0$, then $n'$ contains all prime factors of $n$.

$$
\begin{aligned}
\varphi(n) & = n \times \prod_{i = 1}^s{\frac{p_i - 1}{p_i}} \\\\
& = p_1 \times n' \times \prod_{i = 1}^s{\frac{p_i - 1}{p_i}} \\\\
& = p_1 \times \varphi(n')
\end{aligned}
$$

What if $n' \bmod p_1 \neq 0$? Then $n'$ and $p_1$ are coprime, and by the properties of Euler's totient function:

$$
\begin{aligned}
\varphi(n) & = \varphi(p_1) \times \varphi(n') \\\\
& = (p_1 - 1) \times \varphi(n')
\end{aligned}
$$

### Implementation

=== "C++"
    ```cpp
    vector<int> pri;
    bool not_prime[N];
    int phi[N];
    
    void pre(int n) {
      phi[1] = 1;
      for (int i = 2; i <= n; i++) {
        if (!not_prime[i]) {
          pri.push_back(i);
          phi[i] = i - 1;
        }
        for (int pri_j : pri) {
          if (i * pri_j > n) break;
          not_prime[i * pri_j] = true;
          if (i % pri_j == 0) {
            phi[i * pri_j] = phi[i] * pri_j;
            break;
          }
          phi[i * pri_j] = phi[i] * phi[pri_j];
        }
      }
    }
    ```

=== "Python"
    ```python
    pri = []
    not_prime = [False] * N
    phi = [0] * N
    
    
    def pre(n):
        phi[1] = 1
        for i in range(2, n + 1):
            if not not_prime[i]:
                pri.append(i)
                phi[i] = i - 1
            for pri_j in pri:
                if i * pri_j > n:
                    break
                not_prime[i * pri_j] = True
                if i % pri_j == 0:
                    phi[i * pri_j] = phi[i] * pri_j
                    break
                phi[i * pri_j] = phi[i] * phi[pri_j]
    ```

## Sieving the Möbius function

### Definition

By the definition of the Möbius function, let $n$ be a composite number, $p_1$ the smallest prime factor of $n$, and $n'=\frac{n}{p_1}$. Then:

$$
\mu(n)=
\begin{cases}
    0 & n' \bmod p_1 = 0\\\\
    -\mu(n') & \text{otherwise}
\end{cases}
$$

If $n$ is prime, then $\mu(n)=-1$.

### Implementation

=== "C++"
    ```cpp
    vector<int> pri;
    bool not_prime[N];
    int mu[N];
    
    void pre(int n) {
      mu[1] = 1;
      for (int i = 2; i <= n; ++i) {
        if (!not_prime[i]) {
          mu[i] = -1;
          pri.push_back(i);
        }
        for (int pri_j : pri) {
          if (i * pri_j > n) break;
          not_prime[i * pri_j] = true;
          if (i % pri_j == 0) {
            mu[i * pri_j] = 0;
            break;
          }
          mu[i * pri_j] = -mu[i];
        }
      }
    }
    ```

=== "Python"
    ```python
    pri = []
    not_prime = [False] * N
    mu = [0] * N
    
    
    def pre(n):
        mu[1] = 1
        for i in range(2, n + 1):
            if not not_prime[i]:
                pri.append(i)
                mu[i] = -1
            for pri_j in pri:
                if i * pri_j > n:
                    break
                not_prime[i * pri_j] = True
                if i % pri_j == 0:
                    mu[i * pri_j] = 0
                    break
                mu[i * pri_j] = -mu[i]
    ```

## Sieving the number of divisors

Let $d_i$ be the number of divisors of $i$, and $num_i$ the number of times the smallest prime factor of $i$ appears.

### Divisor count theorem

Theorem: if $n=\prod_{i=1}^m p_i^{c_i}$, then $d_i=\prod_{i=1}^m (c_i+1)$.

Proof: the divisors of $p_i^{c_i}$ are $p_i^0,p_i^1,\dots ,p_i^{c_i}$, which is $c_i+1$ of them. By the multiplication principle, the number of divisors of $n$ is $\prod_{i=1}^m (c_i+1)$.

### Implementation

Since $d_i$ is a multiplicative function, we can use the linear sieve.

Here is a short explanation of how the linear sieve computes it.

1.  When $i$ is prime, $\textit{num}_i \gets 1,\textit{d}_i \gets 2$. Also let $q = \left\lfloor \dfrac {i}{p} \right\rfloor$, where $p$ is the smallest prime factor of $i$.
2.  When $p$ is a prime factor of $q$, $\textit{num}_i \gets \textit{num}_q + 1,\textit{d}_i \gets \dfrac{\textit{d}_q}{\textit{num}_i} \times (\textit{num}_i + 1)$.
3.  When $p,q$ are coprime, $\textit{num}_i \gets 1,\textit{d}_i \gets \textit{d}_q \times (\textit{num}_i+1)$.

=== "C++"
    ```cpp
    vector<int> pri;
    bool not_prime[N];
    int d[N], num[N];
    
    void pre(int n) {
      d[1] = 1;
      for (int i = 2; i <= n; ++i) {
        if (!not_prime[i]) {
          pri.push_back(i);
          d[i] = 2;
          num[i] = 1;
        }
        for (int pri_j : pri) {
          if (i * pri_j > n) break;
          not_prime[i * pri_j] = true;
          if (i % pri_j == 0) {
            num[i * pri_j] = num[i] + 1;
            d[i * pri_j] = d[i] / num[i * pri_j] * (num[i * pri_j] + 1);
            break;
          }
          num[i * pri_j] = 1;
          d[i * pri_j] = d[i] * 2;
        }
      }
    }
    ```

=== "Python"
    ```python
    pri = []
    not_prime = [False] * N
    d = [0] * N
    num = [0] * N
    
    
    def pre(n):
        d[1] = 1
        for i in range(2, n + 1):
            if not not_prime[i]:
                pri.append(i)
                d[i] = 2
                num[i] = 1
            for pri_j in pri:
                if i * pri_j > n:
                    break
                not_prime[i * pri_j] = True
                if i % pri_j == 0:
                    num[i * pri_j] = num[i] + 1
                    d[i * pri_j] = d[i] // num[i * pri_j] * (num[i * pri_j] + 1)
                    break
                num[i * pri_j] = 1
                d[i * pri_j] = d[i] * 2
    ```

## Sieving the sum of divisors

$f_i$ is the sum of divisors of $i$, and $g_i$ is $p^0+p^1+p^2+\dots p^k$ for the smallest prime factor $p$ of $i$.

### Implementation

=== "C++"
    ```cpp
    vector<int> pri;
    bool not_prime[N];
    int g[N], f[N];
    
    void pre(int n) {
      g[1] = f[1] = 1;
      for (int i = 2; i <= n; ++i) {
        if (!not_prime[i]) {
          pri.push_back(i);
          g[i] = i + 1;
          f[i] = i + 1;
        }
        for (int pri_j : pri) {
          if (i * pri_j > n) break;
          not_prime[i * pri_j] = true;
          if (i % pri_j == 0) {
            g[i * pri_j] = g[i] * pri_j + 1;
            f[i * pri_j] = f[i] / g[i] * g[i * pri_j];
            break;
          }
          f[i * pri_j] = f[i] * f[pri_j];
          g[i * pri_j] = 1 + pri_j;
        }
      }
    }
    ```

=== "Python"
    ```python
    pri = []
    not_prime = [False] * N
    f = [0] * N
    g = [0] * N
    
    
    def pre(n):
        g[1] = f[1] = 1
        for i in range(2, n + 1):
            if not not_prime[i]:
                pri.append(i)
                g[i] = i + 1
                f[i] = i + 1
            for pri_j in pri:
                if i * pri_j > n:
                    break
                not_prime[i * pri_j] = True
                if i % pri_j == 0:
                    g[i * pri_j] = g[i] * pri_j + 1
                    f[i * pri_j] = f[i] // g[i] * g[i * pri_j]
                    break
                f[i * pri_j] = f[i] * f[pri_j]
                g[i * pri_j] = 1 + pri_j
    ```

## General multiplicative functions

Suppose a [multiplicative function](./basic.md#积性函数)  $f$ has the property that, for any prime $p$ and positive integer $k$, $f(p^k)$ can be computed in time polynomial of low degree in $k$. Then we can sieve the values $f(1),f(2),\dots,f(n)$ in $O(n)$ time.

Let the prime factorization of a composite number $n$ be $\prod_{i=1}^k p_i^{\alpha_i}$, where $p_1<p_2<\dots<p_k$ are primes. In the linear sieve we record $g_n=p_1^{\alpha_1}$. If $n$ is sieved out as $x\cdot p$ ($p$ prime), then $g$ satisfies the recurrence:

$$
g_n=
\begin{cases}
    g_x\cdot p & x\bmod p=0\\\\
    p & \text{otherwise}
\end{cases}
$$

If $n=g_n$, then $n$ is a power of some prime, and $f(n)$ can be computed in $O(1)$. Otherwise, $f(n)=f(\frac{n}{g_n})\cdot f(g_n)$.

**Parts of this section are translated from the article [Решето Эратосфена](http://e-maxx.ru/algo/eratosthenes_sieve) and its English version [Sieve of Eratosthenes](https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**
