author: Marcythm, Xeonacid, CSPNOIP

## Definition

Based on the idea behind it, this sieve is also called the "Extended Eratosthenes Sieve".

Since it was invented and first used by [Min\_25](https://web.archive.org/web/20211104125457/http://min-25.hatenablog.com/), it is called the "Min\_25 sieve".

## Properties

It solves the prefix-sum problem for a class of **multiplicative functions** in $O\left(\frac{n^{\frac{3}{4}}}{\log{n}}\right)$ or $\Theta\left(n^{1 - \epsilon}\right)$ time.

Requirements: $f(p)$ is a sum of completely multiplicative functions of $p$ that can be evaluated quickly (e.g., a polynomial); $f(p^{c})$ can be evaluated quickly.

## Notation

-   **Unless stated otherwise, every variable named $p$ in this section ranges over all primes.**
-   $x / y := \left\lfloor\frac{x}{y}\right\rfloor$
-   $\operatorname{isprime}(n) := [ |\{d : d \mid n\}| = 2 ]$, i.e., its value is $1$ when $n$ is prime and $0$ otherwise.
-   $p_{k}$: the $k$-th smallest prime (e.g., $p_{1} = 2, p_{2} = 3$). In particular, let $p_{0} = 1$.
-   $\operatorname{lpf}(n) := [1 < n] \min\{p : p \mid n\} + [1 = n]$, i.e., the least prime factor of $n$. In particular, its value is $1$ when $n=1$.
-   $F_{\mathrm{prime}}(n) := \sum_{2 \le p \le n} f(p)$
-   $F_{k}(n) := \sum_{i = 2}^{n} [p_{k} \le \operatorname{lpf}(i)] f(i)$

## Explanation

From the definition of $F_{k}(n)$, the answer is $F_{1}(n) + f(1) = F_{1}(n) + 1$.

Now consider how to compute $F_{k}(n)$. Enumerating the least prime factor of each $i$ and its exponent gives the recurrence:

$$
\begin{aligned}
    F_{k}(n)
    &= \sum_{i = 2}^{n} [p_{k} \le \operatorname{lpf}(i)] f(i) \\
    &= \sum_{\substack{k \le i \\ p_{i}^{2} \le n}} \sum_{\substack{c \ge 1 \\ p_{i}^{c} \le n}} f\left(p_{i}^{c}\right) ([c > 1] + F_{i + 1}\left(n / p_{i}^{c}\right)) + \sum_{\substack{k \le i \\ p_{i} \le n}} f(p_{i}) \\
    &= \sum_{\substack{k \le i \\ p_{i}^{2} \le n}} \sum_{\substack{c \ge 1 \\ p_{i}^{c} \le n}} f\left(p_{i}^{c}\right) ([c > 1] + F_{i + 1}\left(n / p_{i}^{c}\right)) + F_{\mathrm{prime}}(n) - F_{\mathrm{prime}}(p_{k - 1}) \\
    &= \sum_{\substack{k \le i \\ p_{i}^{2} \le n}} \sum_{\substack{c \ge 1 \\ p_{i}^{c + 1} \le n}} \left(f\left(p_{i}^{c}\right) F_{i + 1}\left(n / p_{i}^{c}\right) + f\left(p_{i}^{c + 1}\right)\right) + F_{\mathrm{prime}}(n) - F_{\mathrm{prime}}(p_{k - 1})
\end{aligned}
$$

The last step relies on this fact: for $c$ with $p_{i}^{c} \le n < p_{i}^{c + 1}$, we have $p_{i}^{c + 1} > n \iff n / p_{i}^{c} < p_{i} < p_{i + 1}$, so $F_{i + 1}\left(n / p_{i}^{c}\right) = 0$.  
The boundary condition is $F_{k}(n) = 0 (p_{k} > n)$.

Suppose we have already computed all $F_{\mathrm{prime}}(n)$. Then there are two ways to compute all $F_{k}(n)$:

1.  Compute directly from the recurrence.
2.  Enumerate $p$ from large to small and do the transitions. The added value is nonzero only when $p^{2} < n$, so we can optimize the recurrence with suffix sums.

Now consider how to compute $F_{\mathrm{prime}}{(n)}$.  
Looking at how $F_{k}(n)$ is computed, it is easy to see that only the $O(\sqrt{n})$ values of $F_{\mathrm{prime}}$ at $1, 2, \dots, \left\lfloor\sqrt{n}\right\rfloor, n / \sqrt{n}, \dots, n / 2, n$ are ever used.  
Usually, $f(p)$ is a low-degree polynomial in $p$ and can be written as $f(p) = \sum a_{i} p^{c_{i}}$.  
Then each $p^{c_{i}}$ contributes $a_{i} \sum_{2 \le p \le n} p^{c_{i}}$ to $F_{\mathrm{prime}}(n)$.  
Treating the contribution of each $p^{c_{i}}$ separately, the problem becomes: given $n, s, g(p) = p^{s}$, compute $\sum_{p \le m} g(p)$ for all $m = n / i$.

???+ tip "Note"
    $g(p) = p^{s}$ is a completely multiplicative function!

So let $G_{k}(n) := \sum_{i = 2}^{n} \left[p_{k} < \operatorname{lpf}(i) \lor \operatorname{isprime}(i)\right] g(i)$, i.e., the sum of $g$ over the numbers that remain after the $k$-th round of the sieve of Eratosthenes.  
For a composite $x \le n$, we must have $\operatorname{lpf}(x) \le \sqrt{x} \le \sqrt{n}$. Let $p_{\ell(n)}$ be the largest prime not greater than $\sqrt{n}$. Then $\sum_{2\le p\le n}g(p) = G_{\ell(n)}(n)$, i.e., after $\ell$ rounds of the sieve of Eratosthenes, only primes remain.
The boundary value of $G$ is clearly $G_{0}(n) = \sum_{i = 2}^{n} g(i)$. (Remember? We specially defined $p_{0} = 1$.)  
For the transition, consider the sieving process and look at each part's contribution separately:

1.  For $n < p_{k}^{2}$, the value of $G$ does not change, i.e., $G_{k}(n) = G_{k - 1}(n)$.
2.  For $p_{k}^{2} \le n$, every number sieved out must have the prime factor $p_{k}$, giving $-g(p_{k}) G_{k - 1}(n / p_{k})$.
3.  In the second part, since $p_{k}^{2} \le n \iff p_{k} \le n / p_{k}$, the values $i$ with $\operatorname{lpf}(i) < p_{k}$ are subtracted by mistake. We need to add them back, i.e., $g(p_{k}) G_{k - 1}(p_{k - 1})$.

So we have:

$$
G_{k}(n) = G_{k - 1}(n) - \left[p_{k}^{2} \le n\right] g(p_{k}) (G_{k - 1}(n / p_{k}) - G_{k - 1}(p_{k - 1}))
$$

## Complexity analysis

For computing $F_{k}(n)$, the first method has been proved to run in $O\left(n^{1 - \epsilon}\right)$ time (see Section 2.3 of Zhu Zhenting's national training team paper [*Some Special Summation Problems of Arithmetic Functions*](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2018%E8%AE%BA%E6%96%87%E9%9B%86.pdf), in Chinese);  
the second method is essentially the second part of the Zhouge sieve, which is also discussed in Ren Zhizhou's paper [*Several Methods for Summing Multiplicative Functions*](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2016%E8%AE%BA%E6%96%87%E9%9B%86.pdf) (in Chinese, Section 6.5.4), and its time complexity has been proved to be $O\left(\frac{n^{\frac{3}{4}}}{\log{n}}\right)$.

For computing $F_{\mathrm{prime}}(n)$, the implementation is in fact the same as the first part of the Zhouge sieve.  
For each $m = n / i$, only the transitions over $p_{k}$ with $p_{k}^{2} \le m$ contribute to the running time, so the time complexity can be estimated as:

$$
\begin{aligned}
    T(n)
    &= \sum_{i^{2} \le n} O\left(\pi\left(\sqrt{i}\right)\right) + \sum_{i^{2} \le n} O\left(\pi\left(\sqrt{\frac{n}{i}}\right)\right) \\
    &= \sum_{i^{2} \le n} O\left(\frac{\sqrt{i}}{\ln{\sqrt{i}}}\right) + \sum_{i^{2} \le n} O\left(\frac{\sqrt{\frac{n}{i}}}{\ln{\sqrt{\frac{n}{i}}}}\right) \\
    &= O\left(\int_{1}^{\sqrt{n}} \frac{\sqrt{\frac{n}{x}}}{\log{\sqrt{\frac{n}{x}}}} \mathrm{d} x\right) \\
    &= O\left(\frac{n^{\frac{3}{4}}}{\log{n}}\right)
\end{aligned}
$$

For the space complexity, note that both $F_{k}$ and $F_{\mathrm{prime}}$ are only needed at the points $n / i$, of which there are $O(\sqrt{n})$. Storing only these useful values reduces the space complexity to $O(\sqrt{n})$.

First, one pass of number-theoretic blocking gives all the useful values, which we store in an array $\text{lis}$ of size $O(\sqrt{n})$. For a useful value $v$, let $\text{id}(v)$ be the index of $v$ in $\text{lis}$. It is easy to see that $\text{id}(v) \le \sqrt{n}$ for every useful value $v$.

Then handle useful values at most $\sqrt{n}$ and those greater than $\sqrt{n}$ separately: for a useful value $v \le \sqrt{n}$, store $\text{id}(v)$ in an array $\text{le}$, i.e., $\text{le}_v = \text{id}(v)$; for a useful value $v > \sqrt{n}$, store $\text{id}(v)$ in an array $\text{ge}$. Since $v$ is too large, we use $v' = n / v < \sqrt{n}$ as the index, i.e., $\text{ge}_{v'} = \text{id}(v)$.

This way, two arrays of size $O(\sqrt{n})$ store the $\text{id}$ of every useful value with $O(1)$ lookup. When computing $F_{k}$ or $F_{\mathrm{prime}}$, use the $\text{id}$ of a useful value instead of the value itself as the index, which reduces the space complexity to $O(\sqrt{n})$.

## How it works

For computing $F_{k}(n)$, we usually implement the first method, which is easier to write and often performs better than the second method when the input is not very large;

For computing $F_{\mathrm{prime}}(n)$, just implement the recurrence directly.

For $p_{k}^{2} \le n$, we can precompute $s_{k} := F_{\mathrm{prime}}(p_{k})$ with a linear sieve and use it in place of $F_{\mathrm{prime}}(p_{k - 1})$ in the recurrence for $F_{k}$.  
Similarly, $G_{k - 1}(p_{k - 1}) = \sum_{i = 1}^{k - 1} g(p_{i})$ in the recurrence for $G$ can be precomputed the same way.

When using the Extended Eratosthenes Sieve to compute the prefix sums of a **multiplicative function** $f$, you should be clear about the following:

-   How to quickly (usually in linear time) sieve the first $\sqrt{n}$ values of $f$;
-   The polynomial form of $f(p)$;
-   How to quickly compute $f(p^{c})$.

Once these are clear, implement the following parts in order:

1.  Sieve the primes in $[1, \sqrt{n}]$ and the first $\sqrt{n}$ values of $f$;
2.  For each term in the polynomial form of $f(p)$, sieve the corresponding $G$, and combine them to get all $O(\sqrt{n})$ useful values of $F_{\mathrm{prime}}$;
3.  Implement the recursion following the recurrence for $F_{k}$, and compute $F_{1}(n)$.

## Example problems

???+ example "[Luogu P4213 [Template] Du's Sieve](https://www.luogu.com.cn/problem/P4213)"
    Compute $\displaystyle \sum_{i = 1}^{n} \varphi(i)$ and $\displaystyle \sum_{i = 1}^{n} \mu(i)$.

??? note "Solution"
    For the prefix sums of $\varphi(i)$, first note that $f(p) = p - 1$. For the linear term $(p)$ of $f(p)$, we have $g(p) = p, G_{0}(n) = \sum_{i = 2}^{n} g(i) = \frac{(n + 2) (n - 1)}{2}$; for the constant term $(-1)$ of $f(p)$, we have $g(p) = -1, G_{0}(n) = \sum_{i = 2}^{n} g(i) = -n + 1$. Sieve twice and add the results to get all $O(\sqrt{n})$ needed values of $F_{\mathrm{prime}}$.
    
    For the prefix sums of $\mu(i)$, clearly $f(p) = -1$. Then $g(p) = -1, G_{0}(n) = \sum_{i = 2}^{n} g(i) = -n + 1$. Sieving directly gives all $O(\sqrt{n})$ needed values of $F_{\mathrm{prime}}$.

???+ example "[LOJ 6053 A Simple Function](https://loj.ac/p/6053)"
    Given $f(n)$:
    
    $$
    f(n) = \begin{cases}
        1 & n = 1 \\
        p \operatorname{xor} c & n = p^{c} \\
        f(a)f(b) & n = ab \land a \perp b
    \end{cases}
    $$
    
    compute $\displaystyle \sum_{i = 1}^{n} f(i)$.

??? note "Solution"
    Clearly $f(p) = p - 1 + 2[p = 2]$. So sieve the same way as for $\varphi$, and handle $2$ as a special case.

??? note "Reference code"
    ```cpp
    --8<-- "docs/math/code/min-25/min-25_1.cpp"
    ```
