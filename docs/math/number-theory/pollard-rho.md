## Introduction

Given a positive integer $N \in \mathbf{N}_{+}$, quickly find one of its [nontrivial divisors](./basic.md).

Consider the naive algorithm. Divisors come in pairs, so all divisors of $N$ split into two parts: $[2, \sqrt N]$ and $[\sqrt N+1,N)$. Just go through the numbers in $[2, \sqrt N]$, and with division you find at least two divisors. This method takes $O(\sqrt N)$ time.

When $N\ge10^{18}$, this running time is unacceptable, so we want a better algorithm. One idea is to guess randomly whether a number is a divisor of $N$. With luck, you get the answer in $O(1)$ time, but for $N\ge10^{18}$, the probability of a correct guess is $\frac{1}{10^{18}}$, and the expected number of guesses is $10^{18}$. Guessing within $[2,\sqrt N]$ gives a somewhat higher success rate. We want a way to make the guessing smarter.

## Naive algorithm

The simplest algorithm just goes through $[2, \sqrt N]$.

=== "C++"
    ```cpp
    vector<int> breakdown(int N) {
      vector<int> result;
      for (int i = 2; i * i <= N; i++) {
        if (N % i == 0) {  // If i divides N, then i is a prime factor of N.
          while (N % i == 0) N /= i;
          result.push_back(i);
        }
      }
      if (N != 1) {  // After the loop, what is left of N is a prime
        result.push_back(N);
      }
      return result;
    }
    ```

=== "Python"
    ```python
    def breakdown(N):
        result = []
        for i in range(2, int(sqrt(N)) + 1):
            if N % i == 0:  # If i divides N, then i is a prime factor of N.
                while N % i == 0:
                    N //= i
                result.append(i)
        if N != 1:  # After the loop, what is left of N is a prime
            result.append(N)
        return result
    ```

We can prove that the elements of `result` are exactly all the prime factors of `N`.

??? note "Proof that the elements of `result` are exactly all the prime factors of $N$"
    First look at how `N` changes. When the loop finishes with `i`, it has just run `while(N % i == 0) N /= i`, so `i` no longer divides `N`. Also, each time a factor is divided out, `N` still divides $N$. These two facts guarantee that when the loop starts on `i`, `N` is a divisor of $N$ and is not divisible by any integer less than `i`.
    
    Next we show that every element of `result` is a divisor of $N$. When the loop is at `i`, `i` is stored in `result` only if `N % i == 0`, which means `i` divides `N`; since `N` is a divisor of $N$, `i` is a divisor of $N$. When the loop over `i` ends, `N` is also stored in `result` if it is not one. By the above, it is also a divisor of $N$.
    
    Next we show that all elements of `result` are prime. Suppose some composite $K$ is in `result`. Then there is an `i` greater than one and at most $\sqrt K$ that divides $K$. Such a $K$ cannot be stored as some `i` in the loop, because the first paragraph showed that when the loop reaches $K$, `N` is not divisible by any `i` less than $K$. Such a $K$ also cannot be added after the loop, because the loop exits when `i * i > N`, so every `i` up to $\sqrt K$ has already been tried, and as said above, none of these `i` can divide the current `N`, which is $K$.
    
    Finally we show that every prime factor of $N$ appears in `result`. Suppose $p$ is a prime factor of $N$ that does not appear in `result`. By the discussion above, $p$ cannot be any `i` seen in the loop. Let `i` be the last `i` before the loop exits; then `i` is strictly less than $p$, and the `N` left after the loop is not divisible by any earlier `i`, so $p$ divides `N`. So the final `N` is greater than one, and by the above it must be prime, so `N` equals $p$ and is added to `result` at the end, a contradiction.

It is worth noting that if you have precomputed a table of primes, the time complexity drops from $O(\sqrt N)$ to $O(\frac {\sqrt{N}} {\ln N})$. See [sieve](./sieve.md) for more on building such tables.

Example problem: [CF 1445C](https://codeforces.com/problemset/problem/1445/C)

## Pollard Rho algorithm

### Introduction

Finding a nontrivial factor by brute force takes $O(p)=O(\sqrt N)$, where $p$ is the smallest prime factor of $N$. The Pollard Rho algorithm introduced below is a randomized algorithm that finds a nontrivial factor in $O(\sqrt p)=O(N^{1/4})$ expected time (**note**: a nontrivial factor is not necessarily a prime factor).

Its core idea is this: for a random map $f: \mathbf Z_p \rightarrow \mathbf Z_p$ from a set to itself, starting from any point $x_1$ and iterating $x_n = f(x_{n-1})$, the sequence enters a cycle in $O(\sqrt p)$ expected time. If we can find $x_i \equiv x_j \pmod p$, then $p$ divides $\gcd(|x_i-x_j|, N)$, and this greatest common divisor is a nontrivial factor of $N$.

To see why the expected time to enter a cycle is $O(\sqrt p)$, the birthday paradox gives a hint.

### Birthday paradox

Ignoring birth years (assume every year has 365 days), how many people must be in a room for the probability that two of them share a birthday to reach $50\%$?

Solution: suppose a year has $n$ days and the room has $k$ people, numbered $1, 2,\dots, k$. Assume each person's birthday is uniformly distributed over the $n$ days, and different people's birthdays are independent.

Let $A$ be the event that all $k$ birthdays are distinct. Then the probability of $A$ is

$$
P(A)=\prod_{i=0}^{k-1}\frac{n-i}{n}
$$

The probability that at least two people share a birthday is $P(\overline A)=1-P(A)$. We want $P(\overline A)\ge\frac{1}{2}$, so

$$
P(A)=\prod_{i=0}^{k-1}\frac{n-i}{n} \le \frac{1}{2}
$$

From the inequality $1+x\le \mathrm{e}^x$ we get

$$
P(A) \le \prod_{i=1}^{k-1}\exp\left({-\frac{i}{n}}\right)=\exp \left({-\frac{k(k-1)}{2n}}\right)
$$

Therefore

$$
\exp\left({-\dfrac{k(k-1)}{2n}}\right) \le \frac{1}{2}\implies P(A) \le \frac{1}{2}
$$

Plugging in $n=365$ gives $k\geq 23$. So with at least $23$ people in a room, the probability that two share a birthday reaches $50\%$. This mathematical fact is very counterintuitive, which is why it is called a paradox.

When $k>56$ and $n=365$, the probability that two people share a birthday is over $99\%$[^ref1]. In general, with $n$ days in a year, when the room has $\frac{1}{2}(\sqrt{8n\ln 2+1}+1)\approx \sqrt{2n\ln 2}$ people, the probability that at least two share a birthday is about $50\%$.

Similarly, if you draw a sequence of birthdays uniformly at random, the expected number of people until the first repeated birthday is also $O(\sqrt n)$. Let this number be $X$; then

$$
E(X) = \sum_{x=0}^{n}P(X\ge x+1) = \sum_{x=0}^n\frac{n!}{(n-x)!n^x} = \sqrt{\frac{\pi n}{2}}+\frac23+o(1).
$$

This suggests that if we pick a sequence of numbers at random, the expected number of samples until a repeat appears is also $O(\sqrt n)$.

### Finding a divisor with the greatest common divisor

Actually building a random sequence modulo $p$ is not realistic, because $p$ is exactly what we are looking for. So we use $f(x)=(x^2+c)\bmod N$ to generate a pseudo-random sequence $\{x_i\}$: pick a random $x_1$, and let $x_2=f(x_1),\ x_3=f(x_2),\ \dots,\ x_i=f(x_{i-1})$, where $c\in[1,N)$ is a randomly chosen constant.

The function chosen here is easy to compute and usually produces a fairly random-looking sequence. But it is not truly random. For example, with $N=50,\ c=6,\ x_1=1$, $f(x)$ produces

$$
1, 7, 5, 31, 17, 45, 31, 17, 45, 31,\dots
$$

After $x_4$, the values cycle among $31,17,45$. If you draw these numbers as in the figure below, the picture looks a lot like a $\rho$, which is where the name rho comes from.

![pollard-rho](./images/pollard-rho.svg)

More importantly, such a function really does give a map from $\mathbf Z_p$ to itself. That is, it has the property: if $x\equiv y\pmod p$, then $f(x)\equiv f(y)\pmod p$.

???+ note "Proof"
    If $x\equiv y\pmod p$, then $x^2+c\equiv y^2+c\pmod p$. Note that $f(x)=x^2+c-k_xN$, where $k_x$ is an integer depending on $x$, and $p\mid N$, so $f(x)\equiv x^2+c\pmod p$, and hence $f(x)\equiv f(y)\pmod p$.

As a sequence obtained by repeatedly applying a pseudo-random map on $\mathbf Z_p$, $\{x_n\bmod p\}$ repeats within $O(\sqrt p)$ expected time. As soon as we observe such a repeat $x_i\equiv x_j\pmod p$, we can get a nontrivial factor of $N$ from $\gcd(|x_i-x_j|,N)$. Note that since $p$ is unknown, we cannot directly detect the repeat; a simple test is exactly whether $\gcd(|x_i-x_j|,N)$ is strictly greater than one.

This algorithm does not always succeed, because $\gcd(|x_i-x_j|,N)$ may equal $N$, that is, $x_i\equiv x_j\pmod N$. In that case, when $\{x_n\bmod p\}$ first repeats, $\{x_n\}$ itself happens to repeat too. We do not get a nontrivial factor. Moreover, once $\{x_n\}$ starts cycling, further iteration is pointless, because it will only repeat the cycle. The algorithm should report failure, and you need to choose a different $c$ in $f(x)$ and try again.

By the analysis above, in theory any function $f(x)$ (for example, certain polynomials) that satisfies $\forall x \equiv y \pmod p, f(x) \equiv f(y) \pmod p$ and is reasonably pseudo-random can be used here. In practice, $f(x)=x^2+c\ (c\neq 0,-2)$ is the main choice.[^pseudo]

### Implementation

We need an algorithm that, during the iteration, can quickly tell whether $\{x_n\bmod p\}$ has already repeated. Viewing $f$ as the edges of a directed graph whose vertices are $\mathbf Z_p$, what we actually need is a cycle detection algorithm. The only difference is that the equality test is replaced by checking whether $\gcd(|x_i-x_j|,N)$ is greater than one.

#### Floyd's cycle detection

Suppose two people are running a race on a loop track: A is fast and B is slow. After some time, A will certainly catch up with B, and when they meet, the total distance A has run minus the total distance B has run is a multiple of the loop length.

Let $a=f(0),b=f(f(0))$, and at each step update $a=f(a),b=f(f(b))$. Just check during the updates whether $a$ and $b$ are equal; if they are, a cycle has appeared.

At each step we set $d=\gcd(|x_i-x_j|,N)$ and check whether $1< d< N$; if so, return $d$ directly. If $d=N$, then $\{x_i\}$ has already formed a cycle, and once that happens we cannot continue; return $N$ itself, and in later steps change the random constant $c$ and try again.

??? note "Pollard Rho based on Floyd's cycle detection"
    === "C++"
        ```cpp
        ll Pollard_Rho(ll N) {
          if (N == 4) return 2;  // We take two steps at the start, so 4 needs a special case
          ll c = rand() % (N - 1) + 1;
          ll t = f(0, c, N);
          ll r = f(f(0, c, N), c, N);
          while (t != r) {
            ll d = gcd(abs(t - r), N);
            if (d > 1) return d;
            t = f(t, c, N);
            r = f(f(r, c, N), c, N);
          }
          return N;
        }
        ```
    
    === "Python"
        ```python
        import random
        
        
        def Pollard_Rho(N):
            if N == 4:
                return 2  # We take two steps at the start, so 4 needs a special case
            c = random.randint(1, N - 1)
            t = f(0, c, N)
            r = f(f(0, c, N), c, N)
            while t != r:
                d = gcd(abs(t - r), N)
                if d > 1:
                    return d
                t = f(t, c, N)
                r = f(f(r, c, N), c, N)
            return N
        ```

#### Brent's cycle detection

In fact, Floyd's cycle detection can be improved by a constant factor. Brent's cycle detection increases $k$ starting from $k=1$. In round $k$, A stays in place and B moves forward $2^k$ steps. If B meets A along the way, a cycle has been found; otherwise A teleports to B's position and the next round begins.

It can be shown[^brent] that the number of calls to $f$ before finding the cycle this way is never more than with Floyd's algorithm. Tests in the original paper show that Brent's method takes $24\%$ less time on average than Floyd's.

#### Doubling optimization

Whether you use Floyd's or Brent's cycle detection, the number of iterations is $O(\sqrt p)$. But checking for a cycle with a $\gcd$ at every iteration slows the algorithm down. You can reduce the number of $\gcd$ computations by accumulating a product.

Put simply, if $\gcd(a,N)>1$, then $\gcd(ab\bmod N,N)=\gcd(ab,N)>1$ for any $b\in\mathbf N_+$. That is, if we find $\gcd(\prod |x_i-x_j| \bmod N,N)>1$, then some pair $(x_i,x_j)$ must satisfy $\gcd(|x_i-x_j|,N)>1$. If the product becomes zero at some point, the factorization fails; exit and return $N$ itself.

If we compute one $\gcd$ every $k$ pairs, the complexity drops to $O(\sqrt p+k^{-1}\sqrt p\log N)$, where $\log N$ is the cost of one $\gcd$ computation. When $k$ is about the same order as $\log N$, we get $O(\sqrt p)$ expected complexity. Most implementations choose $k=127$.

Here is an implementation of Pollard Rho with Brent's cycle detection and the doubling optimization.

??? note "Implementation"
    === "C++"
        ```cpp
        ll Pollard_Rho(ll x) {
          ll t = 0;
          ll c = rand() % (x - 1) + 1;
          ll s = t;
          int step = 0, goal = 1;
          ll val = 1;
          for (goal = 1;; goal <<= 1, s = t, val = 1) {
            for (step = 1; step <= goal; ++step) {
              t = f(t, c, x);
              val = val * abs(t - s) % x;
              // If val is 0, exit and try the factorization again
              if (!val) return x;
              if (step % 127 == 0) {
                ll d = gcd(val, x);
                if (d > 1) return d;
              }
            }
            ll d = gcd(val, x);
            if (d > 1) return d;
          }
        }
        ```
    
    === "Python"
        ```python
        from random import randint
        from math import gcd
        
        
        def Pollard_Rho(x):
            c = randint(1, x - 1)
            s = t = f(0, c, x)
            goal = val = 1
            while True:
                for step in range(1, goal + 1):
                    t = f(t, c, x)
                    val = val * abs(t - s) % x
                    if val == 0:
                        return x  # If val is 0, exit and try the factorization again
                    if step % 127 == 0:
                        d = gcd(val, x)
                        if d > 1:
                            return d
                d = gcd(val, x)
                if d > 1:
                    return d
                s = t
                goal <<= 1
                val = 1
        ```

#### Complexity

The expected number of iterations in Pollard Rho is $O(\sqrt p)$, where $p$ is the smallest prime factor of $N$. Whether the implementation uses Floyd's or Brent's cycle detection, without the doubling optimization the expected complexity is $O(\sqrt p\log N)$; with the doubling optimization, it is roughly $O(\sqrt p)$ expected.

It is worth mentioning that the analysis above assumes a truly random map, but Pollard Rho actually uses a pseudo-random function, so the algorithm has no rigorous complexity analysis. In practice it usually runs fast.

#### Example problem: finding the largest prime factor of a number

Example problem: [Luogu P4718 [Template] Pollard-Rho algorithm](https://www.luogu.com.cn/problem/P4718)

For a number $n$, use the [Miller–Rabin algorithm](./prime.md#millerrabin-primality-test) to check whether it is prime. If it is, return it directly. Otherwise use Pollard Rho to find a factor $p$, and divide $n$ by $p$. Then recursively factor $n$ and $p$, use Miller–Rabin to detect prime factors, and update max\_factor to get the largest prime factor. Since this problem's data is very large, Floyd's cycle detection is not fast enough; here we use the doubling optimization.

??? note "Implementation"
    ```cpp
    --8<-- "docs/math/code/pollard-rho/pollard-rho_1.cpp"
    ```

## References and links

[^ref1]: <https://en.wikipedia.org/wiki/Birthday_problem#Reverse_problem>

[^pseudo]: Menezes, Alfred J.; van Oorschot, Paul C.; Vanstone, Scott A. (2001). Handbook of Applied Cryptography. Section 3.11 and 3.12.

[^brent]: Brent, R. P. (1980), An improved Monte Carlo factorization algorithm, BIT Numerical Mathematics, 20(2): 176–184, doi:10.1007/BF01933190
