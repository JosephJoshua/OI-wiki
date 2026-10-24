author: Ir1d, Tiphereth-A, c-forrest, Xeonacid, Enter-tainer, StudyingFather, iamtwz, ksyx, Marcythm, MegaOwIer, 383494, Alpacabla, HeRaNO, abc1763613206, alphagocc, Backl1ght, CCXXXI, drkelo, Early0v0, Great-designer, greyqz, GuanghaoYe, H-J-Granger, HHH2309, isdanni, kenlig, lazyasn, Menci, ouuan, r-value, shawlleyw, shopee-jin, shuzhouliu, Siger Young, TrisolarisHD, untitledunrevised, void-mian, Voileexperiments, weilycoder, xtlsoft, yusancky, YuzhenQin1, sun2snow

For the definitions of prime and composite numbers, see [Number theory basics](./basic.md).

The prime counting function, written $\pi(x)$, is the number of primes less than or equal to $x$. As $x$ grows, it satisfies the approximation $\pi(x) \sim \dfrac{x}{\ln(x)}$.

## Primality testing

A **primality test** decides whether a given natural number is prime.

There are two kinds of primality tests:

1.  Deterministic tests: decide with certainty whether a number is prime. Common examples include trial division, the Lucas–Lehmer test and elliptic curve primality proving.
2.  Probabilistic tests: usually much faster than deterministic tests, but they may (with small probability) wrongly report a [composite number](./basic.md#素数与合数) as prime (though never the other way around). So numbers that pass a probabilistic primality test are called **probable primes** until their primality is proven deterministically. Numbers that pass the test but are actually composite are called **pseudoprimes**. There are many specific kinds of pseudoprimes; the most common are Fermat pseudoprimes, which are composite numbers that satisfy Fermat's little theorem. A common example of a probabilistic test is the Miller–Rabin test.

### Trial division

The brute-force approach is to try every number from small to large and see whether it divides the input.

???+ example "Reference implementation"
    === "C++"
        ```cpp
        bool isPrime(int a) {
          if (a < 2) return false;
          for (int i = 2; i < a; ++i)
            if (a % i == 0) return false;
          return true;
        }
        ```
    
    === "Python"
        ```python
        def isPrime(a):
            if a < 2:
                return False
            for i in range(2, a):
                if a % i == 0:
                    return False
            return True
        ```

This is certainly safe, but do we really need to check every number?

It is easy to see that if $x$ is a divisor of $a$, then $\frac{a}{x}$ is also a divisor of $a$.

This tells us that for each pair $(x, \frac{a}{x} )$, checking just one of them is enough. For convenience, we only check the smaller number of each pair. It is easy to see that all these smaller numbers lie in the interval $[1, \sqrt{a}]$.

Since $1$ is always a divisor, we do not check it.

???+ example "Reference implementation"
    === "C++"
        ```cpp
        bool isPrime(int a) {
          if (a < 2) return 0;
          for (int i = 2; (long long)i * i <= a; ++i)  // avoid overflow
            if (a % i == 0) return 0;
          return 1;
        }
        ```
    
    === "Python"
        ```python
        def isPrime(a):
            if a < 2:
                return False
            for i in range(2, int(sqrt(a)) + 1):
                if a % i == 0:
                    return False
            return True
        ```

### Fermat primality test

The **Fermat primality test** is the simplest probabilistic primality test.

[Fermat's little theorem](./fermat.md#费马小定理) suggests a way to test for primes:

The basic idea is to repeatedly pick a base $a$ in $[2, n-1]$ and check whether $a^{n-1} \equiv 1 \pmod n$ holds every time.

???+ example "Reference implementation"
    === "C++"
        ```cpp
        bool fermat(int n) {
          if (n < 3) return n == 2;
          // test_time is the number of rounds; it should be an integer of at
          // least 8 for accuracy, but not too large, or it will be slow
          for (int i = 1; i <= test_time; ++i) {
            int a = rand() % (n - 2) + 2;
            if (quickPow(a, n - 1, n) != 1) return false;
          }
          return true;
        }
        ```
    
    === "Python"
        ```python
        def fermat(n):
            if n < 3:
                return n == 2
            # test_time is the number of rounds; it should be an integer of at
            # least 8 for accuracy, but not too large, or it will be slow
            for i in range(1, test_time + 1):
                a = random.randint(0, 32767) % (n - 2) + 2
                if quickPow(a, n - 1, n) != 1:
                    return False
            return True
        ```

If $a^{n-1} \equiv 1 \pmod n$ but $n$ is not prime, then $n$ is called a **Fermat pseudoprime** to base $a$. In practice we observe that if $a^{n-1} \equiv 1 \pmod n$, then $n$ is usually prime. But counterexamples exist: for $n = 341$ and $a = 2$, we have $2^{340}\equiv 1 {\pmod {341}}$, yet $341 = 11 \cdot 31$ is composite. In fact, for any fixed base $a$, there are infinitely many such counterexamples[^inf-fermat-pp].

Since the Fermat test cannot guarantee correctness for a single base, a natural idea is to check several bases. However, even checking every base $a$ coprime to $n$ still does not guarantee that $n$ is prime. In other words, the converse of Fermat's little theorem is false: even if $a^{n-1}\equiv 1\pmod n$ for all $a\perp n$, $n$ is not necessarily prime. Such numbers are called [Carmichael numbers](./primitive-root.md#carmichael-数), and there are infinitely many of them as well. This forces us to look for a stricter primality test.

### Miller–Rabin primality test

The **Miller–Rabin primality test** is a better way to test primality. Miller and Rabin obtained it by improving the Fermat test. Like other probabilistic tests, it can only detect probable primes; to be sure a number is prime, a much slower deterministic algorithm is needed. However, no composite number is currently known to pass advanced probabilistic tests such as Miller–Rabin, so we can use it with confidence.

Ignoring the cost of multiplication, running $k$ rounds of the test on $n$ takes $O(k \log n)$ time. The Miller–Rabin test is often used on big integers, where it takes $O(k \log^3n)$ time; with techniques such as FFT this can be improved to [$O(k \log^2n \log \log n \log \log \log n)$](https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test#Complexity).

To deal with the challenge posed by Carmichael numbers, the Miller–Rabin test also uses the following property of primes:

???+ note "Quadratic probing theorem"
    If $p$ is an odd prime, then the solutions of $x^2 \equiv 1 \pmod p$ are $x \equiv 1 \pmod p$ and $x \equiv p - 1 \pmod p$.

??? note "Proof"
    It is easy to check that when $p$ is an odd prime, both $x\equiv 1\pmod p$ and $x\equiv p-1\pmod p$ satisfy the equation. By [Lagrange's theorem](./congruence-equation.md#素数模同余方程), these are all of its solutions.

Combining Fermat's little theorem with the quadratic probing theorem gives the Miller–Rabin test:

1.  Write the exponent $n-1$ in $a^{n-1} \equiv 1 \pmod n$ as $n-1=u \times 2^t$, where $u$ is odd;
2.  In each round, for a random $a$, first compute $v = a^{u} \bmod n$, then square this value at most $t$ times;
3.  If at any point a nontrivial square root of $1$ (a root other than $\pm 1$) is found, the number is not prime;
4.  Otherwise, finish with the Fermat test.

There are also a few small implementation details:

-   In a round, if at some point $a^{u \times 2^s} \equiv n-1 \pmod n$, all later squarings give $1$, so the number passes this round right away.
-   If a nontrivial square root is found, that is, $a^{u \times 2^s} \not\equiv n-1 \text{ or } 1 \pmod n$ but $a^{u \times 2^{s+1}} \equiv 1 \pmod n$, all later squarings give $1$. You can return `false` right away, or return `false` after the $t$ squarings.

This gives a fairly correct Miller–Rabin (from fjzzq2002):

???+ example "Reference implementation"
    === "C++"
        ```cpp
        bool millerRabin(int n) {
          if (n < 3 || n % 2 == 0) return n == 2;
          if (n % 3 == 0) return n == 3;
          int u = n - 1, t = 0;
          while (u % 2 == 0) u /= 2, ++t;
          // test_time is the number of rounds; it should be an integer of at
          // least 8 for accuracy, but not too large, or it will be slow
          for (int i = 0; i < test_time; ++i) {
            // 0, 1, n-1 pass the test directly, so a is taken from [2, n-2]
            int a = rand() % (n - 3) + 2, v = quickPow(a, u, n);
            if (v == 1) continue;
            int s;
            for (s = 0; s < t; ++s) {
              if (v == n - 1) break;  // got the trivial square root n-1, passes this round
              v = (long long)v * v % n;
            }
            // if a nontrivial square root was found, we cannot break early, so s reaches t
            // if the Fermat test fails, v never equals -1 before s reaches t
            if (s == t) return 0;
          }
          return 1;
        }
        ```
    
    === "Python"
        ```python
        def millerRabin(n):
            if n < 3 or n % 2 == 0:
                return n == 2
            if n % 3 == 0:
                return n == 3
            u, t = n - 1, 0
            while u % 2 == 0:
                u = u // 2
                t = t + 1
            # test_time is the number of rounds; it should be an integer of at
            # least 8 for accuracy, but not too large, or it will be slow
            for i in range(test_time):
                # 0, 1, n-1 pass the test directly, so a is taken from [2, n-2]
                a = random.randint(2, n - 2)
                v = pow(a, u, n)
                if v == 1:
                    continue
                s = 0
                while s < t:
                    if v == n - 1:
                        break
                    v = v * v % n
                    s = s + 1
                # if a nontrivial square root was found, we cannot break early, so s reaches t
                # if the Fermat test fails, v never equals -1 before s reaches t
                if s == t:
                    return False
            return True
        ```

It can be shown[^millerrabinproof] that an odd composite $n > 9$ passes the Miller–Rabin test for a randomly chosen base $a$ with probability at most one quarter. So after $k$ random bases, the probability of still misjudging a composite as prime is at most $1/4^k$.

??? note "Proof"
    Let $n-1=u2^t$, where $u$ is odd and $t$ is a positive integer. Then the integer $n$ passes the Miller–Rabin test with base $a$ means
    
    $$
    a^u\equiv 1{\textstyle\pmod n},\text{ or }a^{u2^i}\equiv -1{\textstyle\pmod n}\text{ for some }0\le i < t.
    $$
    
    Let $S$ be the set of such $a$ (as residue classes). We want to show
    
    $$
    |S| \le \dfrac14\varphi(n).
    $$
    
    Here $\varphi(n)$ is [Euler's totient function](./euler-totient.md). The proof has three steps.
    
    **Step 1**: Let $\ell$ be the largest positive integer such that $2^\ell \mid p-1$ for every prime factor $p$ of $n$. Then we can show
    
    $$
    S\subseteq S' = \{a\bmod n:a^{u2^{\ell-1}}\equiv\pm 1{\textstyle\pmod n}\}.
    $$
    
    An element $a$ of $S$ falls into one of two cases. If $a^u\equiv 1\pmod n$, then clearly $a^{u2^{\ell-1}}\equiv 1\pmod n$ too, so $a\in S'$. If $a^{u2^i}\equiv -1\pmod n$ for some $0\le i < t$, then for every prime factor $p\mid n$ we have $a^{u2^i}\equiv-1\pmod p$. Let $\delta_p(a)$ be the [order](./primitive-root.md#阶) of $a$ modulo $p$. Clearly $\delta_p(a)\mid u2^{i+1}$ but $\delta_p(a)\nmid u2^{i}$, so the exponent of $2$ in the prime factorization of $\delta_p(a)$ is exactly $i+1$, and hence $2^{i+1}\mid\delta_p(a)$. By Fermat's little theorem, $\delta_p(a)\mid p-1$, so $2^{i+1}\mid p-1$. This holds for every prime factor $p$ of $n$. Therefore $i+1\le\ell$. This means $a^{u2^{\ell-1}} = (a^{u2^i})^{2^{\ell-1-i}} \equiv \pm 1 \pmod n$, so again $a\in S'$. Combining the two cases gives $S\subseteq S'$.
    
    **Step 2**: Compute $|S'|$.
    
    Suppose $n$ has the prime factorization $n = p_1^{e_1}p_2^{e_2}\cdots p_k^{e_k}$. By the [Chinese remainder theorem](./crt.md), the condition $a^{u2^{\ell - 1}}\equiv 1\pmod n$ is equivalent to $a^{u2^{\ell - 1}}\equiv 1\pmod{p_i^{e_i}}$ for every $p_i^{e_i}$. Since a [primitive root](./primitive-root.md#原根) modulo an odd prime power $p_i^{e_i}$ always exists, the [number of solutions](./residue.md#性质) of the congruence $a^{u2^{\ell - 1}}\equiv 1\pmod{p_i^{e_i}}$ is
    
    $$
    \gcd(u2^{\ell-1},p_i^{e_i-1}(p_i-1)) = \gcd(u2^{\ell-1},p_i-1) = 2^{\ell-1}\gcd(u,p_i-1).
    $$
    
    The first equality holds because $u$ is a factor of $n-1$ and so cannot be a multiple of $p_i$; the second holds because of how $\ell$ was chosen. So by the Chinese remainder theorem, the number of solutions of $a^{u2^{\ell-1}}\equiv 1\pmod n$ is
    
    $$
    \prod_{p\mid n}2^{\ell-1}\gcd(u,p-1).
    $$
    
    Similarly, the condition $a^{u2^{\ell - 1}}\equiv -1\pmod n$ is equivalent to $a^{u2^{\ell - 1}}\equiv -1\pmod{p_i^{e_i}}$ for every $p_i^{e_i}$. For any factor $p_i^{e_i}$, the condition $a^{u2^{\ell - 1}}\equiv -1\pmod{p_i^{e_i}}$ is equivalent to $a^{u2^{\ell - 1}}\not\equiv 1\pmod{p_i^{e_i}}$ together with $a^{u2^{\ell}}\equiv 1\pmod{p_i^{e_i}}$. As above, the congruence $a^{u2^{\ell}}\equiv 1\pmod{p_i^{e_i}}$ has $2^{\ell}\gcd(u,p_i-1)$ solutions, so the number of solutions of $a^{u2^{\ell - 1}}\equiv -1\pmod{p_i^{e_i}}$ is
    
    $$
    2^{\ell}\gcd(u,p_i-1) - 2^{\ell-1}\gcd(u,p_i-1) = 2^{\ell-1}\gcd(u,p_i-1).
    $$
    
    Applying the Chinese remainder theorem again, the number of solutions of $a^{u2^{\ell - 1}}\equiv -1\pmod n$ is
    
    $$
    \prod_{p\mid n}2^{\ell-1}\gcd(u,p-1).
    $$
    
    So, combining the two cases,
    
    $$
    |S'| = 2\prod_{p\mid n}2^{\ell-1}\gcd(u,p-1).
    $$
    
    **Step 3**: Prove $|S'|\le\varphi(n)/4$.
    
    Using the formula for Euler's totient function $\varphi(n)=\prod_ip_i^{e_i-1}(p_i-1)$, we get
    
    $$
    \dfrac{\varphi(n)}{|S'|} = \dfrac{1}{2}\prod_ip_i^{e_i-1}\dfrac{p_i-1}{2^{\ell-1}\gcd(u,p_i-1)}.
    $$
    
    For each $i$, the factor $p_i^{e_i-1}\dfrac{p_i-1}{2^{\ell-1}\gcd(u,p_i-1)}$ is even, so $\varphi(n)/|S'|$ is an integer. Suppose $|S'|\le\varphi(n)/4$ is false. Then $\varphi(n)/|S'|=1,2,3$, that is,
    
    $$
    \prod_ip_i^{e_i-1}\dfrac{p_i-1}{2^{\ell-1}\gcd(u,p_i-1)} = 2,4,6.
    $$
    
    Since every factor of the product is even, either the product has a single factor equal to $2,4,6$, or it has exactly two factors, both equal to $2$.
    
    First consider the case of two factors. Then neither factor has an odd prime factor, so $p_i^{e_i-1}=1$, that is, $n$ is squarefree. Without loss of generality, let $n=p_1p_2$ with primes $p_1<p_2$. Both factors equal $2$, so $p_i-1=2^{\ell}\gcd(u,p_i-1)$. Hence $p_i=1+2^\ell m_i$, where $m_i$ is odd and $m_i\mid u$. Reducing $p_1p_2=n=1+u2^t$ modulo $m_1$ gives $p_1p_2\equiv 1\pmod{m_1}$, so $p_2\equiv 1\pmod{m_1}$, which means $m_1\mid m_2$. The converse also holds. So $m_1=m_2$, that is, $p_1=p_2$. This contradicts $p_1<p_2$, so this case is impossible.
    
    Finally, consider the case of a single factor, that is, a composite $n=p^e$ with $e>1$. Then $p^{e-1}\mid 2,4,6$ must hold. The only possibility is $p=3,e=2$, that is, $n=9$, which contradicts the assumption. So this case is impossible too.
    
    Combining all cases, $|S'|\le\varphi(n)/4$ holds.
    
    Putting the three steps together, $|S|\le |S'|\le \varphi(n)/4$ holds for every odd composite $n>9$.

Moreover, if the [generalized Riemann hypothesis](https://en.wikipedia.org/wiki/Generalized_Riemann_hypothesis) (GRH) holds, then to **determine** the primality of $n$ it is enough to test all integers in $[2, \min\{n-2, \lfloor 2\ln^2 n \rfloor\}]$.[^deterministic-proof]

In OI, primality tests are usually for numbers in $[1, 2^{64})$. For numbers in $[1, 2^{32})$, running Miller–Rabin with the three bases $\{2, 7, 61\}$ determines primality; for numbers in $[1, 2^{64})$, running Miller–Rabin with the seven bases $\{2, 325, 9375, 28178, 450775, 9780504, 1795265022\}$ determines primality.[^witnesses]

You can also use $\{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37\}$ (the first $12$ primes) to test primes in $[1, 2^{64})$.

Note that when using the numbers $a$ in the lists above as bases to test $n$:

-   Use every number in the list, not just the ones less than $n$;
-   Replace $a$ with $a \bmod n$;
-   If $a \equiv 0 \pmod n$ or $a \equiv \pm 1 \pmod n$, the round passes directly.

## Antiprimes

As the name suggests: a prime is a number with only two divisors, while an antiprime is a number with the most divisors (and the smallest value among numbers with the same number of divisors). So antiprimes are defined relative to a set.

An intuitive definition of an antiprime: in a set of positive integers, the number with the most divisors and the smallest value is the antiprime.

???+ abstract "Antiprime"
    A positive integer $n$ is called an **antiprime** (anti-prime, a.k.a. highly composite number) if every positive integer less than $n$ has fewer divisors than $n$.

???+ warning "Note"
    Do not confuse this with [emirp](https://en.wikipedia.org/wiki/Emirp), which means a prime whose digit reversal is a different prime (for example, 149 and 941 are both emirps, but 101 is not).

### How it works

So how do we find antiprimes?

First, since we need the number of divisors, the first step is prime factorization. Write $n$ as $n=p_{1}^{k_{1}}p_{2}^{k_{2}} \cdots p_{m}^{k_{m}}$, where each $p$ is a prime and $k$ is its exponent. Then the total number of divisors is $(k_1+1) \times (k_2+1) \times \cdots \times (k_m+1)$.

But prime factorization is clearly expensive, and the result for one number cannot be reused for the next. So we need a different approach.

Let us look at the features of antiprimes.

1.  An antiprime must be a product of powers of consecutive primes starting from $2$.

2.  Smaller primes have exponents at least as large as larger primes, that is, in $n=p_{1}^{k_{1}}p_{2}^{k_{2}} \cdots p_{m}^{k_{m}}$ we have $k_1 \geq k_2 \geq k_3 \geq \cdots \geq k_m$.

Explanation:

1.  If the primes are not consecutive primes starting from $2$, then keeping the exponents and replacing a prime with a smaller prime keeps the number of divisors the same but makes $n$ smaller. $n$ is smallest when the primes are the consecutive primes starting from $2$.

2.  If a smaller prime has a smaller exponent than a larger prime, then swapping the two primes (keeping the exponents) gives an $n$ with the same number of divisors but a smaller value.

There are two more questions:

1.  For a given $n$, up to which prime do we enumerate?

    In the most extreme case, $n=p_{1}p_{2} \cdots p_{m}$, so we only need to multiply consecutive primes until the product is just at most $n$. Enumerating a larger prime would mean some earlier prime has exponent $0$, so the result cannot be an antiprime.

2.  Up to which exponent do we enumerate?

    Consider an extreme case: if some power of the smallest prime already exceeds the given $n$ (its maximum value), then any other factorization has a smaller maximum exponent. In the extreme case $n$ is a power of $2$, so enumerating up to $\lfloor\log_2 n\rfloor$ is enough.

Now that we have the details, how do we implement it?

We can treat the point just before each prime as the root of a tree and search level by level. When do we stop?

1.  The current number is already larger than the number we want;

2.  The current divisor can no longer be used;

3.  The current number of divisors is larger than what we want;

4.  The current number of divisors is exactly what we want (then check whether to update the minimum $\mathit{ans}$).

Then, in the DFS, keep enumerating exponents level by level and recurse downward.

### Example problems

???+ example "[Codeforces 27E. A number with a given number of divisors](https://codeforces.com/problemset/problem/27/E)"
    Find the smallest natural number with a given number of divisors. The answer is guaranteed not to exceed $10^{18}$.

??? note "Solution idea"
    For this kind of problem, just use the number of divisors as the DFS stopping condition and keep updating the smallest value found.

??? note "Reference code"
    ```cpp
    --8<-- "docs/math/code/prime/prime_1.cpp"
    ```

???+ example "[ZOJ 2562 More Divisors](https://pintia.cn/problem-sets/91827364500/exam/problems/type/7?problemSetProblemId=91827366061)"
    Among the numbers not exceeding $n$, find the one with the most divisors.

??? note "Solution idea"
    Same idea as above, only the DFS stopping condition needs to change. Watch the data range for such problems: 32-bit integers may overflow.

??? note "Reference code"
    ```cpp
    --8<-- "docs/math/code/prime/prime_2.cpp"
    ```

## References and notes

1.  Rui-Juan Jing, Marc Moreno-Maza, Delaram Talaashrafi, "[Complexity Estimates for Fourier-Motzkin Elimination](https://arxiv.org/abs/1811.01510)", Journal of Functional Programming 16:2 (2006) pp 197-217.
2.  [Number theory, part 1: primes and primality testing](http://www.matrix67.com/blog/archives/234)
3.  [Miller–Rabin and Pollard–Rho study notes - Bill Yang's Blog](https://blog.bill.moe/miller-rabin-notes/)
4.  [Primality test - Wikipedia](https://en.wikipedia.org/wiki/Primality_test)
5.  [Fermat pseudoprime - Wikipedia](https://en.wikipedia.org/wiki/Fermat_pseudoprime)
6.  [Taozi's algorithm notes: antiprimes explained (ACM/OI)](https://zhuanlan.zhihu.com/p/41759808)
7.  [The Rabin-Miller Primality Test](http://home.sandiego.edu/~dhoffoss/teaching/cryptography/10-Rabin-Miller.pdf)
8.  [Highly composite number - Wikipedia](https://en.wikipedia.org/wiki/Highly_composite_number)

[^inf-fermat-pp]: Theorem 1 of Pomerance, Carl, John L. Selfridge, and Samuel S. Wagstaff. "The pseudoprimes to 25⋅ 10⁹." Mathematics of Computation 35, no. 151 (1980): 1003-1026. shows that for a fixed base $a$, there are also infinitely many composites that pass the stronger Miller–Rabin test.

[^millerrabinproof]: This result and its proof follow Section 3.5 of Crandall, Richard, and Carl Pomerance. Prime numbers: a computational perspective. New York, NY: Springer New York, 2005.

[^deterministic-proof]: Bach, Eric , "[Explicit bounds for primality testing and related problems](https://doi.org/10.2307%2F2008811)", Mathematics of Computation, 55:191 (1990) pp 355–380.

[^witnesses]: For more results like this, see [Deterministic variant of the Miller–Rabin primality test](https://miller-rabin.appspot.com/#).
