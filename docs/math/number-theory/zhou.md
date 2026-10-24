author: Early0v0

## Prerequisites

-   [Multiplicative functions](./basic.md#积性函数)

## Definition

The Zhouge sieve (named after Zhou Ge) is a sieve that computes prefix sums of most multiplicative functions in sublinear time.

Below we explain how the Zhouge sieve works, using the computation of $\displaystyle\sum_{i=1}^nf(i)$ as the running example.

## Notation

-   $\mathbb P$ is the set of primes, and $p_i$ is the $i$-th prime.
-   $m$ is the number of primes up to $\sqrt n$.

## Requirements

For $p\in\mathbb P,c\in\mathbb N$, $f(p^c)$ must be a low-degree polynomial in $p$.

## Idea

-   Every integer in $[1,n]$ has at most one prime factor $>\sqrt n$.
-   $\left\lfloor\dfrac ni\right\rfloor(i\in[1,n]\cap\mathbb N)$ takes only about $\sqrt n$ distinct values. We use this to reduce the time complexity.

## Process

Split all integers in $[1,n]$ into two groups, depending on whether they have a prime factor $>\sqrt n$:

$$
\sum_{i=1}^nf(i)=\sum_{i=1}^n\left[\exists d\in(\sqrt n,n]\cap\mathbb P,d\mid i\right]f(i)+\sum_{i=1}^n\left[\forall d\in(\sqrt n,n]\cap\mathbb P,d\nmid i\right]f(i)
$$

For the first part, enumerate the largest prime factor. Since $f$ is multiplicative, we can rewrite it as:

$$
\sum_{i=1}^nf(i)=\sum_{i=1}^{\sqrt n}f(i)\cdot\left(\sum_{d=\lfloor\sqrt n\rfloor+1}^{\lfloor\frac ni\rfloor}[d\in\mathbb P]f(d)\right)+\sum_{i=1}^n\left[\forall d\in(\sqrt n,n]\cap\mathbb P,d\nmid i\right]f(i)
$$

The two parts can be computed separately.

### Part 1

> Compute $\displaystyle\sum_{i=1}^{\sqrt n}f(i)\cdot\left(\sum_{d=\lfloor\sqrt n\rfloor+1}^{\lfloor\frac ni\rfloor}[d\in\mathbb P]f(d)\right)$.

We enumerate $i$ and compute the part in parentheses in $O(1)$.

Let $\displaystyle g(t,l)=\sum_{i=1}^l[\forall j\in[1,t],\gcd(i,p_j)=1]f(i)$, that is, the sum of $f$ over the numbers in $[1,l]$ that are coprime to all of $p_1,p_2,\dots,p_t$.

Then Part 1 becomes $\displaystyle\sum_{i=1}^{\sqrt n}f(i)\cdot g\left(m,\left\lfloor\frac ni\right\rfloor\right)$.

The base case is $g(0,l)=\sum_{i=1}^lf(i)$, and the transition is $g(t,l)=g(t-1,l)-f(p_t)\cdot g\left(t-1,\left\lfloor\frac l{p_t}\right\rfloor\right)$.

$l$ takes about $\sqrt n$ values, and for each value we enumerate the primes, so the complexity is $\displaystyle O\left(\frac{\sqrt n}{\ln\sqrt n}\cdot\sqrt n\right)= O\left(\frac n{\log n}\right)$. This needs to be optimized.

Notice that when $p_{t+1}^2>l$, the only qualifying number is $1$, so $g(t,l)=f(1)=1$.

Substituting into the recurrence: when $p_t^2>l$, $g(t,l)=g(t-1,l)-f(p_t)$.

So as soon as $p_t^2>l$, stop the transitions and call the current $t$ $t_l$. Then $\forall t>t_l,g(t,l)=g(t_l,l)-\sum_{i=t_l}^{t-1}f(p_i)$.

Precompute prefix sums of $f$ over primes to get $g$ quickly. The time complexity drops to $O\left(\dfrac{n^{\frac34}}{\log n}\right)$.

### Part 2

> Compute $\displaystyle\sum_{i=1}^n\left[\forall d\in(\sqrt n,n]\cap\mathbb P,d\nmid i\right]f(i)$.

Let $\displaystyle h(t,l)=\sum_{i=1}^l\left[i=\prod_{j=t}^mp_j^{c_j},c_j\in\mathbb N\right]f(i)$, that is, the sum of $f$ over the numbers in $[1,l]$ whose prime factors are all among $p_t,p_{t+1},\dots,p_m$.

Part 2 is then $h(0,n)$.

The base case is $h(m+1,l)=1$, and the transition is $\displaystyle h(t,l)=h(t+1,l)+\sum_{c\in\mathbb N^*}f(p_t^c)\cdot h\left(t+1,\left\lfloor\frac l{p_t^c}\right\rfloor\right)$.

$l$ takes about $\sqrt n$ values, so doing the transitions directly costs $\displaystyle O\left(\sqrt n\cdot\frac{\sqrt n}{\ln\sqrt n}\right)= O\left(\frac n{\log n}\right)$. This needs to be optimized.

As with $g$, notice that when $p_t>l$, the only number that can be formed from $p_t,p_{t+1},\dots,p_m$ is $1$, so $h(t,l)=f(1)=1$.

Similarly, we get $\forall p_t^2>l,h(t,l)=h(t+1,l)+f(p_t)$.

So as soon as $p_t^2>l$, stop the transitions and call the current $t$ $t_l$. Later, whenever this $h$ is used, add $\displaystyle\sum_{i=p_{t_l}}^{\min(l,\sqrt n)}[i\in\mathbb P]f(i)$ to its value.

The time complexity drops to $O\left(\dfrac{n^{\frac34}}{\log n}\right)$.

### Summing up

After computing Part 1 and Part 2, add them together to get $\displaystyle\sum_{i=1}^nf(i)$.

## References

[Study notes on the linear sieve, Du's sieve and Zhouge sieve for multiplicative functions | Bill Yang's Blog](https://blog.bill.moe/multiplicative-function-sieves-notes)
