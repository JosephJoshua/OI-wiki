## Definition

The Powerful Number sieve (PN sieve for short) is similar to Du's sieve, or you could say it is an extension of Du's sieve. It can be used to compute prefix sums of some multiplicative functions.

**Requirements**:

-   There is a function $g$ such that:
    -   $g$ is multiplicative.
    -   The prefix sums of $g$ are easy to compute.
    -   For every prime $p$, $g(p) = f(p)$.

Suppose we want the prefix sum $F(n) = \sum_{i=1}^{n} f(i)$ of a multiplicative function $f$.

## Powerful Number

**Definition**: for a positive integer $n$, write its prime factorization as $n = \prod_{i=1}^{m} p_{i}^{e_{i}}$. $n$ is a PN if and only if $\forall 1 \le i \le m, e_{i} > 1$.

**Property 1**: every PN can be written in the form $a^{2}b^{3}$.

**Proof**: if $e_i$ is even, merge $p_{i}^{e_{i}}$ into $a^{2}$; if $e_i$ is odd, first merge $p_{i}^{3}$ into $b^{3}$, then merge $p_{i}^{e_{i}-3}$ into $a^{2}$.

**Property 2**: there are at most $O(\sqrt{n})$ PNs up to $n$.

**Proof**: enumerate $a$ and count the valid $b$; the number of PNs is approximately

$$
\int_{1}^{\sqrt{n}} \sqrt[3]{\frac{n}{x^2}} \mathrm{d}x = O(\sqrt{n})
$$

So how do we find all PNs up to $n$? Use a linear sieve to find all primes up to $\sqrt{n}$, then use DFS to search over the exponent of each prime. Since there are at most $O(\sqrt{n})$ PNs up to $n$, the search visits at most $O(\sqrt{n})$ states.

## PN sieve

First, construct a multiplicative function $g$ whose prefix sums are easy to compute, with $g(p) = f(p)$ for every prime $p$. Let $G(n) = \sum_{i=1}^{n} g(i)$.

Then construct the function $h = f / g$, where $/$ denotes Dirichlet division (the inverse of Dirichlet convolution). By the properties of Dirichlet convolution, $h$ is also multiplicative, so $h(1) = 1$. $f = g * h$, where $*$ denotes Dirichlet convolution.

For a prime $p$, $f(p) = g(1)h(p) + g(p)h(1) = h(p) + g(p) \implies h(p) = 0$. From $h(p)=0$ and the fact that $h$ is multiplicative, $h(n) = 0$ for every $n$ that is not a PN, that is, $h$ is nonzero only at PNs.

Now, from $f = g * h$ we get

$$
\begin{aligned}
F(n) &= \sum_{i = 1}^{n} f(i)\\
     &= \sum_{i = 1}^{n} \sum_{d|i} h(d) g\left(\frac{i}{d}\right)\\
     &= \sum_{d=1}^{n} \sum_{i=1}^{\lfloor \frac{n}{d}\rfloor} h(d) g(i)\\
     &= \sum_{d=1}^{n} h(d) \sum_{i=1}^{\lfloor \frac{n}{d}\rfloor}  g(i) \\
     &= \sum_{d=1}^{n} h(d) G\left(\left\lfloor \frac{n}{d}\right\rfloor\right)\\
     &= \sum_{\substack{d=1 \\ d \text{ is PN}}}^{n}h(d) G\left(\left\lfloor \frac{n}{d}\right\rfloor\right)
\end{aligned}
$$

Find all PNs in $O(\sqrt{n})$ and compute all nonzero values of $h$. To get them, you only need the values $h(p^c)$; since $h$ is multiplicative, they determine all nonzero values of $h$. Then, for each PN $d$, compute $h(d)G\left(\left\lfloor \dfrac{n}{d} \right\rfloor\right)$ and add them up to get $F(n)$.

Now consider computing $h(p^c)$. There are two ways. One is to derive a formula for $h(p^c)$ that depends only on $p$ and $c$, and compute $h(p^c)$ from the formula. The other uses $f = g * h$, which gives $f(p^c) = \sum_{i=0}^c g(p^i)h(p^{c-i})$; rearranging gives $h(p^c) = f(p^c) - \sum_{i=1}^{c}g(p^i)h(p^{c-i})$, and then you can enumerate the prime $p$ and the exponent $c$ to find all $h(p^c)$.

### Process

1.  Construct $g$
2.  Find a fast way to compute $G$
3.  Compute $h(p^c)$
4.  Search for PNs, adding to the answer along the way
5.  Get the result

For step 3, you can compute directly from a formula, precompute a table by enumeration, or derive values on the fly when the search reaches them.

### Properties

We analyze the case where $h(p^c)$ is computed with the second method. The analysis splits into two parts: computing $h(p^c)$ and the search.

For the first part: there are $O\left(\dfrac{\sqrt{n}}{\log n}\right)$ primes up to $O(\sqrt{n})$, the exponent $c$ of each prime $p$ is at most $\log n$, and computing $h(p^c)$ takes $(c - 1)$ loop iterations. So the first part takes $O\left(\dfrac{\sqrt{n}}{\log n} \cdot \log n \cdot \log n\right) = O(\sqrt{n}\log{n})$ time, and this is a loose upper bound. Depending on the problem, different optimizations can lower the time complexity of the first part.

For the search: since there are at most $O(\sqrt{n})$ PNs up to $n$, the search visits at most $O(\sqrt{n})$ states. The cost for each PN depends on how $G$ is computed. For example, if computing $G\left(\left\lfloor \dfrac{n}{d}\right\rfloor\right)$ takes $O(1)$, the second part takes $O(\sqrt{n})$.

In particular, if $G\left(\left\lfloor \dfrac{n}{d}\right\rfloor\right)$ is computed with Du's sieve, the second part takes the same time as Du's sieve, that is, $O(n^{\frac{2}{3}})$. This is because, if you compute $G(n)$ once beforehand, using a linear sieve for small values and a data structure with fast random access (such as `std::map` or `std::unordered_map` in C++) to record larger values, then every $G\left(\left\lfloor \dfrac{n}{d}\right\rfloor\right)$ needed later has already been recorded either by the linear sieve or in the `std::map`. You can check this directly with a program.

For space complexity, the bottleneck is storing $h(p^c)$. If you store it in a two-dimensional array $a$, where $a_{i,j}$ is the value of $h(p_i^j)$, the space complexity is $O\left(\dfrac{\sqrt{n}}{\log n} \cdot \log n\right) = O(\sqrt{n})$.

## Example problems

### [Luogu P5325 [Template] Min\_25 sieve](https://www.luogu.com.cn/problem/P5325)

**Problem**: given the multiplicative function $f(p^k) = p^k(p^k-1)$, compute $\sum_{i=1}^{n} f(i)$.

It is easy to see that $f(p) = p(p-1) = \operatorname{id}(p)\varphi(p)$, so construct $g(n) = \operatorname{id}(n)\varphi(n)$.

Compute $G(n)$ with Du's sieve: from $(\operatorname{id}\cdot \varphi) * \operatorname{id} = \operatorname{id}_2$ we get $G(n)= \sum_{i=1}^{n} i^2 - \sum_{d=2}^{n} d \cdot G\left(\left\lfloor \dfrac{n}{d} \right\rfloor\right)$.

After that, the values of $h(p^k)$ can be computed by enumeration; we skip the details of this method.

Alternatively, for this problem you can derive a formula for $h(p^k)$ that depends only on $p$ and $k$, as follows:

$$
\begin{aligned}
& f(p^k) = \sum_{i=0}^{k} g(p^{k-i})h(p^i)\\
\iff & p^k(p^k-1) = \sum_{i=0}^{k} p^{k-i}\varphi(p^{k-i}) h(p^i)\\
\iff & p^k(p^k-1) = \sum_{i=0}^{k} p^{2k-2i-1}(p - 1) h(p^i)\\
\iff & p^k(p^k-1) = h(p^k) + \sum_{i=0}^{k-1} p^{2k-2i-1}(p - 1) h(p^i)\\
\iff & h(p^k) = p^k(p^k-1) - \sum_{i=0}^{k-1} p^{2k-2i-1}(p - 1) h(p^i)\\
\iff & h(p^k) - p^2h(p^{k-1}) = p^{k}(p^k-1)-p^{k+1}(p^{k-1}-1) - p(p-1)h(p^{k-1})\\
\iff & h(p^k) - ph(p^{k-1}) = p^{k+1} - p^k\\
\iff & \frac{h(p^k)}{p^k} - \frac{h(p^{k-1})}{p^{k-1}} = p - 1\\
\end{aligned}
$$

Then, using $h(p) = 0$ and summing up these differences, we get $h(p^k) = (k-1)(p-1)p^k$.

??? note "Reference code"
    ```cpp
    --8<-- "docs/math/code/powerful-number/powerful-number_1.cpp"
    ```

### [LOJ #6053 "Simple Function"](https://loj.ac/problem/6053)

Given $f(n)$:

$$
f(n) =
\begin{cases}
1 & n = 1 \\
p \oplus c & n=p^c \\
f(a)f(b) & n=ab \text{ and } a \perp b
\end{cases}
$$

It is easy to get:

$$
f(p) =
\begin{cases}
p + 1 & p = 2 \\
p - 1 & \text{otherwise} \\
\end{cases}
$$

Construct $g$ as

$$
g(n) =
\begin{cases}
3 \varphi(n) & 2 \mid n \\
\varphi(n) & \text{otherwise} \\
\end{cases}
$$

It is easy to show that $g(p) = f(p)$ and that $g$ is multiplicative.

Now consider computing $G(n)$.

$$
\begin{aligned}
G(n)
&= \sum_{i=1}^{n}[i \bmod 2 = 1] \varphi(i) + 3 \sum_{i=1}^{n}[i \bmod 2 = 0] \varphi(i)\\
&= \sum_{i=1}^{n} \varphi(i) + 2\sum_{i=1}^{n} [i \bmod 2 = 0]\varphi(i) \\
&= \sum_{i=1}^{n} \varphi(i) + 2\sum_{i=1}^{\lfloor \frac{n}{2} \rfloor} \varphi(2i)
\end{aligned}
$$

Let $S_1(n) = \sum_{i=1}^{n} \varphi(i)$ and $S_2(n) = \sum_{i=1}^{n} \varphi(2i)$; then $G(n) = S_1(n) + 2S_2\left(\left\lfloor \dfrac{n}{2} \right\rfloor\right)$.

When $2 \mid n$,

$$
\begin{aligned}
S_2(n)
&= \sum_{i=1}^{n} \varphi(2i) \\
&= \sum_{i=1}^{\frac{n}{2}} (\varphi(2(2i-1)) + \varphi(2(2i))) \\
&= \sum_{i=1}^{\frac{n}{2}} (\varphi(2i-1) + 2\varphi(2i)) \\
&= \sum_{i=1}^{\frac{n}{2}} (\varphi(2i-1) + \varphi(2i)) + \sum_{i=1}^{\frac{n}{2}} \varphi(2i) \\
&= \sum_{i=1}^{n} \varphi(i) + S_2\left(\frac{n}{2}\right)\\
&= S_1(n) + S_2\left(\left\lfloor \frac{n}{2} \right\rfloor\right)\\
\end{aligned}
$$

When $2 \nmid n$,

$$
\begin{aligned}
S_2(n)
&= S_2(n-1) + \varphi(2n) \\
&= S_2(n-1) + \varphi(n) \\
&= \sum_{i=1}^{n-1} \varphi(i) + S_2\left(\frac{n-1}{2}\right) + \varphi(n)\\
&= S_1(n) + S_2\left(\left\lfloor \frac{n}{2} \right\rfloor\right)\\
\end{aligned}
$$

In summary, $S_2(n) = S_1(n) + S_2\left(\left\lfloor \dfrac{n}{2} \right\rfloor\right)$.

$S_1$ can be computed with Du's sieve, and $S_2$ directly from the formula, so $G$ can be computed as well.

??? note "Reference code"
    ```cpp
    --8<-- "docs/math/code/powerful-number/powerful-number_2.cpp"
    ```

## Exercises

-   [PE708 Twos are all you need](https://projecteuler.net/problem=708)
-   [PE639 Summing a multiplicative function](https://projecteuler.net/problem=639)
-   [PE484 Arithmetic Derivative](https://projecteuler.net/problem=484)

## References

-   [wallbreaker5th - A brief explanation of the Powerful Number sieve (Chinese)](https://www.cnblogs.com/wallbreaker5th/p/13901487.html)
-   [command\_block - Du's sieve (+ Bell series + powerful number) (Chinese)](https://www.luogu.com.cn/blog/command-block/du-jiao-shai)
