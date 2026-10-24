author: Peanut-Tang, Early0v0, Vxlimo, GHLinZhengyu, 1196131597, c-forrest

This page introduces sublinear algorithms for the prime counting problem. The prime counting problem asks for $\pi(n)$, the number of primes not exceeding $n$. For $n\sim 10^8$, it can be computed with a [sieve](./sieve.md) in $\tilde O(n)$ time. However, once $n \sim 10^{10}$ or larger, sieves and other enumeration-based algorithms are no longer practical. For this case, the page presents a series of fairly easy-to-implement algorithms, most of which run in time between $\tilde O(n^{2/3})$ and $\tilde O(n^{3/4})$.

The prime counting problem is a special case of summing powers of primes over a prefix. The Lucy algorithm described here extends directly to prime power prefix sums, and this extension is a building block of algorithms for summing multiplicative functions, such as the [Min\_25 sieve](./min-25.md).

???+ tip "Tip"
    This page gives many prime counting algorithms. To keep them readable, none of them has much constant-factor optimization. They differ in time and memory performance and in how hard they are to implement, so pick the one that fits your needs. For inputs in the range $10^{11}\sim 10^{13}$, the algorithm in the [Lehmer truncation rule](#lehmer-truncation-rule) section is usually fast enough and fairly simple to implement. The [optimized Lucy algorithm](#further-optimization) is a bit more complex to implement but has excellent time and memory performance. For smaller inputs, the [original Lucy algorithm](#lucy-algorithm) is the simplest to implement, and it has much wider uses in summing multiplicative functions.

## Basic concepts and notation

This page uses the following notation:

-   $\mathbf P$ is the set of (positive) primes, and $p_a$ is the $a$-th smallest prime (indexed from $1$). For convenience, also set $p_0=1$. On this page, the letters $p$ and $q$ always denote primes.
-   $\operatorname{lpf}(n)$ is the least prime factor of $n$. Also set $\operatorname{lpf}(1)=+\infty$.
-   $D(x) = \{\lfloor x/i\rfloor : i = 1,2,\dots,\lfloor x\rfloor\}$. For its properties, see the section [properties of sqrt decomposition in number theory](./sqrt-decomposition.md#properties).
-   $\pi(x)$ is the number of primes not exceeding $x$.
-   $\varphi(x,a)=\#\{n \in\mathbf N_+ : n \le x,~ (p\mid n \implies p > p_a)\}$ is the number of positive integers not exceeding $x$ whose prime factors are all greater than $p_a$.
-   $P_k(x,a)=\#\{n\in\mathbf N_+ : n \le x,~ n = q_1q_2\cdots q_k,~ \forall i(q_i > p_a)\}$ is the number of positive integers not exceeding $x$ that have exactly $k$ prime factors (counted with multiplicity), all greater than $p_a$.
-   $S(x,a)$ is the number of integers greater than $1$ and not exceeding $x$ that remain after the sieve of Eratosthenes has sieved with the first $a$ primes.

These functions have the following simple properties:

-   $\varphi(x,0) = \lfloor x\rfloor$.
-   $S(x,a) = \varphi(x,a) + \min\{\pi(x),a\} - 1$.
-   $\varphi(x,a) = \sum_{k=0}^{\infty} P_k(x,a)$.
-   $P_0(x,a) = 1$.
-   $P_1(x,a) = \pi(x) - \min\{\pi(x),a\}$.
-   For $x < p_{a+1}^k$, $P_k(x,a) = 0$.

All of these follow easily from the definitions.

## Meissel–Lehmer algorithm

Substituting the expressions for $P_0$ and $P_1$ into the expansion of $\varphi$ and rearranging gives

$$
\pi(x) = \varphi(x,a) + a - 1 - P_2(x,a) - P_3(x,a) - \cdots.
$$

So $\pi(x)$ can be obtained by computing $\varphi(x,a)$, with the error given by a series of $P_k$ terms. As $a$ grows, the number of error terms shrinks. In particular, for $a = \pi(\sqrt{x})$, we have $P_2(x,a)=P_3(x,a)=\cdots=0$, that is,

$$
\pi(x) = \varphi(x,\pi(\sqrt{x})) + \pi(\sqrt{x}) - 1.
$$

For $\pi(x^{1/3}) \le a < \pi(\sqrt{x})$, the term $P_2(x,a)$ is nonzero, but all later terms are still zero, so

$$
\pi(x) = \varphi(x,a) + a - 1 - P_2(x,a).
$$

Similarly, for $\pi(x^{1/4}) \le a < \pi(x^{1/3})$, both $P_2(x,a)$ and $P_3(x,a)$ are nonzero, and so on. In short, these relations turn the computation of $\pi(x)$ into computing $\varphi(x,a)$ and the $P_k(x,a)$ terms. Every algorithm built on these relations can be called a Meissel–Lehmer algorithm.

$\varphi(x,a)$ satisfies the recurrence:

$$
\varphi(x,a) = \varphi(x,a - 1) - \varphi\left(\dfrac{x}{p_a},a-1\right).
$$

Naturally, the base case is $\varphi(x,0) = \lfloor x\rfloor$.

???+ example "Example"
    Take $x=30,a=2$ ($p_a=3$). One step of the recurrence is shown below:
    
    ![](images/phi-recurrence.svg)
    
    The green cells are integers whose prime factors are all greater than $p_a=3$ ($1$ has no prime factors, so it is included too). Green and orange together are the integers whose prime factors are all greater than $2$. There are $\varphi(x,a)=\varphi(30,2)=10$ of the former and $\varphi(x,a-1)=\varphi(30,1)=15$ of the latter.
    
    Their difference is exactly the orange part: numbers divisible by $3$ with no prime factor smaller than $3$. So every orange number has the form $n=3k$. Every prime factor of $k$ is also a prime factor of $n$, so $k$ has no prime factor smaller than $3$ either, which means $k$ itself is green or orange. Also, $3k\le 30$ gives $k\le\lfloor x/p_a\rfloor=10$. The converse holds as well: the prime factors of $n=3k$ are just $3$ and the prime factors of $k$, so whenever $k\le 10$ has no prime factor smaller than $3$, $n$ is orange. This gives a one-to-one correspondence.
    
    The table is deliberately laid out in $30/3=10$ columns, so the first row is exactly $1,\dots,10$. The valid $k$ are exactly the green and orange cells inside the dashed box, $\varphi(x/p_a,a-1)=\varphi(30/3,1)=5$ of them. The label $3\times k$ in the top-right corner of each orange cell shows its matching $k$. Therefore
    
    $$
    \varphi(x,a) = \varphi(x,a-1) - \varphi\left(\left\lfloor\dfrac{x}{p_a}\right\rfloor,a-1\right).
    $$
    
    That is, $\varphi(30,2)=\varphi(30,1)-\varphi(30/3,1)=15-5=10$.

Computing recursively with this relation gives a recursion tree that is a binary tree. Fully expanded, it becomes

$$
\varphi(x,a) = \sum_{n\mid p_1p_2\cdots p_a} \mu(n)\left\lfloor\dfrac{x}{n}\right\rfloor.
$$

So the number of leaves of this binary tree equals the number of squarefree $p_a$-smooth numbers (integers with no prime factor greater than $p_a$) not exceeding $x$, which is $\Theta(x)$[^smooth]. This means plain recursion still takes $\Omega(x)$ time. To compute faster, the binary tree must be pruned in a suitable way. Different Meissel–Lehmer algorithms differ mainly in how they prune. The literature calls these **truncation rules**. This section focuses on a few simple truncation rules.

Finally, we need to handle $P_k(x,a)$. Take $P_2(x,a)$ as an example:

$$
\begin{aligned}
P_2(x,a) &= \sum_{i,j:~p_a < p_i\le p_j\le x/p_i} 1 = \sum_{i = a+1}^{\pi(\sqrt{x})}\sum_{j=i}^{\pi(x/p_i)} 1 \\
&= \sum_{i = a+1}^{\pi(\sqrt{x})}\left(\pi\left(\dfrac{x}{p_i}\right) - i + 1\right)\\
&= \sum_{i = a+1}^{\pi(\sqrt{x})}\pi\left(\dfrac{x}{p_i}\right)-\dfrac{1}{2}\left(\pi(\sqrt{x})+a-1\right)\left(\pi(\sqrt{x}) - a\right).
\end{aligned}
$$

So computing $P_2(x,a)$ reduces to computing several values $\pi(x/p)$. For $k>2$ there are similar sums, but with more nested levels, so they become less and less practical. Most common algorithms choose $a\ge\pi(x^{1/3})$ to avoid computing more $P_k$ terms. In practice, the needed values $\pi(x/p)$ are usually precomputed with a sieve.

Mathematicians thought long ago about computing $\pi(x)$ directly without enumeration. Legendre gave the expression above for $a=\pi(\sqrt{x})$, but fully expanding $\varphi(x,a)$ gives far too many terms to be usable. In 1870, Meissel proposed computing at $a=\pi(x^{1/3})$, which reduces the number of terms in the expansion of $\varphi(x,a)$ while keeping the error easy to compute. In 1959, Lehmer further improved and simplified the process. In 1985, the truncation rule proposed by Lagarias, Miller and Odlyzko brought this approach to sublinear complexity for the first time, with $\tilde O(x^{2/3})$ time and $\tilde O(x^{1/3})$ space. Later, Deléglise and Rivat (1996), Gourdon (2001), Staple (2015) and others optimized further in this direction, lowering the power of $\log x$ in the complexity. Note that, to keep the space complexity low enough to handle problems as large as $x\sim 10^{26}$, these algorithms are usually quite intricate. This section greatly simplifies their details and presents only some simple optimization ideas. This costs some time and space complexity, but the code is much easier to write. Readers interested in the original treatments can study the references at the end of the page.

Besides enumeration and the combinatorial methods on this page, $\pi(x)$ can also be computed with analytic methods in $\tilde O(\sqrt{x})$ time. However, these cannot be used in competitive programming, so this page does not cover them.

### Lehmer truncation rule

Lehmer (1959) proposed a truncation rule. In the following two cases, $\varphi(u,b)$ is not expanded further:

1.  when $u < p_b$;
2.  when $b = c$, where $c$ is a small positive integer chosen in advance.

In the first case, by the discussion above, $\varphi(u,b)=1$ necessarily, so nothing needs to be computed. In the second case, the value of $\varphi(u,c)$ must be computed separately. By definition,

$$
\varphi(u,c) = \sum_{n=1}^{u} \prod_{b=1}^{c} [p_b \nmid n].
$$

Divisibility by $p_b$ is periodic with period $p_b$, so the summand $\prod_{b=1}^{c} [p_b \nmid n]$ is periodic with period $p_c\# = \prod_{b=1}^{c}p_b$. Using this periodicity,

$$
\varphi(u,c) = \left\lfloor\dfrac{u}{p_c\#}\right\rfloor \varphi(p_c\#, c) + \varphi(u \bmod p_c\#, c).
$$

So once all values $\varphi(n,c)$ for $n=0,1,2,\dots,p_c\#$ are precomputed with the recurrence, the value of $\varphi(u,c)$ in the second case can be looked up quickly.

Note that although these two truncation rules do make the computation faster, they do not significantly improve the asymptotic complexity. Lagarias, Miller, and Odlyzko (1985) proved that in Lehmer's algorithm the recursion tree has $\Omega\left(\dfrac{x}{\log^4 x}\right)$ leaves, so the time complexity is still $\tilde\Theta(x)$.

Of course, Lehmer's first truncation rule can be improved:

$$
\varphi(u,b) = \begin{cases}
1,  & u \le p_b,\\
\pi(u) - b + 1, & p_b < u \le p_b^2,\\
\pi(u) -\dfrac{1}{2}\left(\pi(\sqrt{u})+b-2\right)\left(\pi(\sqrt{u}) - b+1\right) + \sum\limits_{i = b+1}^{\pi(\sqrt{u})}\pi\left(\dfrac{u}{p_i}\right), & p_b^2 < u \le p_b^3.
\end{cases}
$$

The last two cases use the relations derived earlier. This improvement shrinks the recursion tree further, but adds more $\pi(u/p)$ terms to compute. Since $u/p$ can be as large as $x/p_{c+1}$, to avoid useless pruning we can set an upper bound $V$ on the $u$ that may trigger this rule and precompute $\pi(u)$ on $[1,V]$; when $u > V$, the normal recursion is still used.

Below is an implementation of the improved Lehmer truncation rule:

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/prime-counting/lehmer.cpp:core"
    ```

Although the theoretical complexity of this implementation is hard to prove[^sgtlaugh], it has a very small constant factor and is simple to implement, so it runs very fast in practice. Constants in the code such as $c,V,N$ can be tuned to fit your needs.

### LMO truncation rule

Lagarias, Miller, and Odlyzko (1985) proposed another truncation rule. Choose $y$ with $x^{1/3} \le y \le x^{2/5}$ and let $a=\pi(y)$. Then $\varphi(x/n,b)$ is not expanded further in the following two cases:

1.  when $b=c$ and $n\le y$, where $c$ is a small natural number chosen in advance;
2.  when $n > y$.

LMO call the first case ordinary leaves and the second case special leaves.

The advantage of this rule is that the leaves are easy to count. Note that different leaves always have different $n$. Ordinary leaves always satisfy $n \le y$, so there are $O(y)$ of them. Special leaves always satisfy $n > y$ and $\dfrac{n}{\operatorname{lpf}(n)} \le y$. So special leaves can be split into two classes: $\operatorname{lpf}(n) < \sqrt{y}$ and $\operatorname{lpf}(n) \ge \sqrt{y}$. In the first class, $\operatorname{lpf}(n) < \sqrt{y}$, so there are at most $\pi(\sqrt{y})$ choices for $\operatorname{lpf}(n)$, and at most $y$ choices for $\dfrac{n}{\operatorname{lpf}(n)} \le y$, so the number of possible $n$ (that is, the number of such leaves) is at most $y\pi(\sqrt{y})$. In the second class, necessarily $n=pq$ with $\sqrt{y} \le p < q \le y$, so there are at most $\dfrac{1}{2}\pi(y)^2$ such leaves. Combining both cases, there are $O\left(\dfrac{y^2}{\log^2x}\right)$ special leaves in total.

Ordinary leaves can use the same precomputation as before. For special leaves, to compute $\varphi(x/n,b)$, read it by definition as "the number of positive integers not exceeding $x/n$ whose least prime factor is strictly greater than $p_b$". (Recall that we set $\operatorname{lpf}(1) = +\infty$.) With this view, all queries at special leaves can be handled offline: precompute $\operatorname{lpf}$ for the integers in $[1,x/y]$, sort them, then update and query with a Fenwick tree. Counting the sorting of offline queries and the Fenwick tree operations, the time complexity is

$$
O\left(\dfrac{y^2}{\log^2x}\log \dfrac{y^2}{\log^2x} + \left(\dfrac{x}{y} + \dfrac{y^2}{\log^2x}\right)\log\pi\left(\dfrac{x}{y}\right)\right) = O\left(\dfrac{x}{y}\log x + \dfrac{y^2}{\log x}\right).
$$

Apart from the special handling of $\varphi(x,a)$, the rest is similar to the previous section. Just precompute $\pi(u)$ on $[1,x/y]$ and then compute $P_2(x,a)$ with the relation above; when $c > 0$, also precompute the values $\varphi(u,c)$. Note that for the offline queries, the recursive search for leaves must also record the sign in front of each leaf, that is, the value of $\mu(n)$, to add up its contribution. This gives the complete algorithm.

Both the time and space complexity of this algorithm are $\tilde O(x^{2/3})$. If $c = 0$, the other parts are negligible, and the total complexity reaches its minimum $O(x^{2/3}\log^{1/3}x)$ at $y = x^{1/3}\log^{2/3}x$. The space complexity is then $O(x^{2/3}\log^{-2/3}x)$. If $c$ is a small positive integer, we need to balance the time and memory cost of precomputation against the constant-factor gain in later queries, but the overall complexity does not change.

Below is a reference implementation of the algorithm with $c=0$:

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/prime-counting/lmo-offline.cpp:core"
    ```

This offline approach uses a lot of memory and struggles with problems of size $10^{13}$. The bottleneck is that precomputation must store the $\operatorname{lpf}$ information for $[1,x/y]$. In fact, this information is only used by the later offline queries and is accessed once in order, so it can be computed during the queries with a [segmented sieve](./sieve.md#segmented-sieve).

In fact, the original paper gives an implementation based entirely on the segmented sieve. Both $P_2(x,a)$ and $\varphi(x,a)$ are computed inside the segmented sieve, giving an algorithm with $\tilde O(x^{2/3})$ time and $\tilde O(x^{1/3})$ space. This requires enumerating all leaves directly in some way, turning the offline algorithm into an online one. A simple implementation is described next.

The core of the implementation is the segmented sieve: after precomputing the primes in $[1,y]$, split $[1,x/y]$ into blocks of length $y$ and sieve each block separately. While processing each block, keep the values of $\pi(u)$ and $\varphi(u,b)$ at the elements of the block. Since these values are all counts, they are easy to maintain block by block. Then we need to find which queries fall inside the current block. In the algorithm described so far in this section, let $y=\tilde O(x^{1/3})$ and $c=0$. Then the prime count $\pi(x)$ has the following expression:

$$
\begin{aligned}
\pi(x) &= \dfrac{1}{2}\left(\pi(\sqrt{x})+a-2\right)\left(\pi(\sqrt{x}) - a + 1\right) - \sum_{y < p\le\sqrt{x}}\pi\left(\dfrac{x}{p}\right) \\
&\quad +\sum_{n\le y}\mu(n)\varphi\left(\dfrac{x}{n},0\right) + \sum_{n > y,~{n}/{\operatorname{lpf}(n)}\le y,~\operatorname{lpf}(n)\le y}\mu(n)\varphi\left(\dfrac{x}{n},\pi(\operatorname{lpf}(n))-1\right).
\end{aligned}
$$

The first term only needs $\pi(\sqrt{x})$, which can be computed when the block containing that element is processed. The second term requires enumerating primes $p$ such that $x/p$ lies in the current block; after solving for the range of $p$, the corresponding primes can be obtained with a segmented sieve. Since the range of $p$ contains no element greater than $\sqrt{x}$, this inner segmented sieve only needs the primes up to $x^{1/4}$. The third term only needs enumeration over $[1,y]$. The fourth term requires enumerating the primes in $[1,y]$ as $\operatorname{lpf}(n)$, which determines the range of $\dfrac{n}{\operatorname{lpf}(n)}$; then enumerate the elements in that range whose prime factors are all at least $\operatorname{lpf}(n)$[^lmo-segsieve], and the values of these leaves can be computed. The contribution of the current block can be maintained with a Fenwick tree. This keeps the space complexity at $\tilde O(x^{1/3})$ while still achieving $\tilde O(x^{2/3})$ time. Of course, it is more tedious to implement than the offline algorithm.

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/prime-counting/lmo-online.cpp:core"
    ```

The original paper and later papers classify and analyze special leaves in more detail to improve the time and space complexity further. However, the implementation given in this section is enough for contests, so we do not discuss the more complex optimizations of the Meissel–Lehmer algorithm.

## Lucy algorithm

One of the core problems in applying the Meissel–Lehmer algorithm is that the recursion tree of $\varphi(x,a)$ is too large. This is because the recurrence for $\varphi(x,a)$ only stops at $a=0$. Consider replacing $\varphi(x,a)$ with $S(x,a)$. The benefit is that if $p_a^2 > x$, then sieving with the prime $p_a$ in the sieve of Eratosthenes removes no composite numbers (they all have a smaller prime factor), so $S(x,a)=S(x,a-1)$. This makes it possible to stop the recursion early. When $p_a^2\le x$, we have $a\le\pi(x)$, so $S(x,a) = \varphi(x,a)+a-1$. Also, since $a-1\le\pi(x/p_a)$, every term in the recurrence for $\varphi(x,a)$ can be replaced by the corresponding $S(\cdot,\cdot)$, which gives a recurrence for $S(x,a)$. Combining both cases, the recurrence for $S(x,a)$ can be written as

$$
S(x,a) = S(x,a-1) - [p_a^2 \le x]\left(S\left(\dfrac{x}{p_a},a-1\right)-(a-1)\right).
$$

The base case is $S(x,0)=\lfloor x\rfloor -1$. Finally, from the relation

$$
\pi(x) = S(x,\pi(\sqrt{x})),
$$

we get the value of the prime counting function $\pi(x)$ directly.

???+ example "Example"
    Again take $x=30,a=2$. The recurrence for $S(x,a)$ is shown below:
    
    ![](images/s-recurrence.svg)
    
    The sieve of Eratosthenes starts from the range $[2,x] = [2,30]$, so cell $1$ is drawn in white and is not counted. Gray cells are composites sieved out earlier, and orange cells are composites sieved out in this round by the prime $p_a=3$. Among the remaining cells, light purple marks earlier primes, dark purple marks the current prime $3$, and green marks integers not yet sieved out (these may be primes or composites, such as $25$). So $S(x,a-1)=S(30,1)=15$ is the total of orange, purple and green cells, $S(x,a)=S(30,2)=11$ is the total of purple and green cells, and their difference is exactly the $4$ orange cells.
    
    As with $\varphi(x,a)$, these numbers still have the form $3k$, and $3k\le 30$ means $k$ lies in $[2,\lfloor x/p_a\rfloor] = [2,10]$ inside the dashed box ($k=1$ is not included, which is exactly why $3$ itself stays and does not turn orange). The difference is that $k$ now only ranges over $3,5,7,9$ (marked in the top-right corner of each orange cell): $k$ must survive the previous round (otherwise $3k$ would already have been sieved out together with $k$), so it is one of $2,3,5,7,9$ in the box, $S(x/p_a,a-1)=S(10,1)=5$ in total. From these we must also remove the primes smaller than $p_a$, which are exactly the first $a-1$ primes, here just $k=2$, because $3\times 2=6$ was already sieved out by $2$. Therefore
    
    $$
    S(x,a) = S(x,a-1) - \left(S\left(\left\lfloor\dfrac{x}{p_a}\right\rfloor, a-1\right) - (a-1)\right).
    $$
    
    That is, $S(30,2)=S(30,1)-\bigl(S(10,1)-(2-1)\bigr)=15-(5-1)=11$.

This recurrence is easy to compute with dynamic programming. Since $S(x,a)=S(\lfloor x\rfloor,a)$, every division in the recurrence can be treated as integer division. By the [properties of sqrt decomposition in number theory](./sqrt-decomposition.md#properties), the first dimension of the DP always takes values in the set $D(x)$, which has only $\Theta(\sqrt{x})$ elements. Moreover, thanks to the special form of the recurrence, the values $S(\cdot,a)$ can be stored in a single array of length $|D(x)|$. For each $a$, go through the elements of $D(x)$ from largest to smallest and update the array with the recurrence, until the element is strictly smaller than $p_a^2$. Only $\pi(\sqrt{x})$ rounds of updates are needed to get the final result.

The space complexity is clearly $O(x^{1/2})$. As for time, the precomputation takes $O(x^{1/2})$, and the DP part takes

$$
I = \sum_{a=1}^{\pi(\sqrt{x})}|\{u\in D(x) : u \ge p_a^2\}|
$$

This can be estimated in two parts. For $a\in[1,\pi(x^{1/4})]$, each summand is at most $|D(x)|$, so this part is at most $\pi(x^{1/4})|D(x)|$, which is $O(x^{3/4}\log^{-1}x)$. For $a\in(\pi(x^{1/4}),\pi(\sqrt{x})]$, we have $p_a^2 > \sqrt{x}$; from the structure of $D(x)$, the number of such elements is exactly $\lfloor x/p_a^2\rfloor$. Combined with the prime number theorem $p_a\sim a\log a$, this gives

$$
\sum_{a=\pi(x^{1/4})+1}^{\pi(\sqrt{x})}\dfrac{x}{p_a^2} \in O\left(\int_{\pi(x^{1/4})}^{+\infty}\dfrac{x}{a^2\log^2a}da\right) = O\left(\dfrac{x^{3/4}}{\log x}\right).
$$

Adding the two parts, the total time complexity is $O(x^{3/4}\log^{-1}x)$.

In the implementation, the step of precomputing the primes up to $\sqrt{x}$ can be merged into the DP. Just enumerate every integer $u$ in $[2,\sqrt{x}]$ in increasing order and check whether $S(u,\pi(u-1)) \neq S(u-1,\pi(u-1))$; this finds all primes in the range, and whenever the condition holds, a DP transition is performed. The reason is that when we reach $u$, the DP has already been advanced to $S(\cdot,\pi(u-1))$, so $\pi(u) = S(u,\pi(u-1))$ and $\pi(u-1) = S(u-1,\pi(u-1))$; if the condition holds, $u$ must be prime. Also, the value of $a-1$ in the transition is given by $S(u-1,\pi(u-1))$, so it need not be kept separately. This gives the following implementation:

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/prime-counting/lucy.cpp:core"
    ```

This algorithm is simple to implement. Its time complexity is slightly worse, but its constant factor is very small, so it performs well on smaller inputs. More importantly, since $\pi(x)=S(x,a)$ holds for all $a\ge \pi(\sqrt{x})$, the algorithm actually produces, as a by-product, the value of $\pi(\cdot)$ at every element of $D(x)$. This is especially important for summing multiplicative functions; its generalization and applications are discussed later.

### Fenwick tree optimization

With a Fenwick tree, it is easy to lower the time complexity of the Lucy algorithm from $\tilde O(x^{3/4})$ to $\tilde O(x^{2/3})$.

To do this, pick a real number $y\in (\sqrt{x},x]$. Maintain the current state $S(\cdot,a)$ in two parts: the part greater than $y$ is still computed with the recurrence above, and the part not greater than $y$ is maintained with the sieve of Eratosthenes, using a Fenwick tree to update and query the current values of $S(\cdot,a)$.

The space complexity is clearly $O(y)$. For the time complexity, consider three parts. In the sieve of Eratosthenes part, the Fenwick tree is updated once per composite sieved out; there are $O(y)$ composites, for a total cost of $O(y\log y)$. For $p_a^2 \le y$, each such round needs $O(x/y)$ transitions, each with an $O(\log y)$ query, and there are $O(\pi(\sqrt{y}))$ such rounds, for a total cost of

$$
O\left(\pi(\sqrt{y})\dfrac{x}{y}\log y\right) = O\left(\dfrac{x}{\sqrt{y}}\right)
$$

Finally, for $p_a^2 > y$, each round needs $O(x/p_a^2)$ transitions; by the method of the previous subsection, the total cost is

$$
O\left(\sum_{a=\pi(\sqrt{y})+1}^{\pi(\sqrt{x})}\dfrac{x}{p_a^2}\log y\right) = O\left(\dfrac{x}{\sqrt{y}}\right)
$$

Adding the three parts and setting $y = x^{2/3}\log^{-2/3}x$ gives a total time complexity of $O(x^{2/3}\log^{1/3}x)$. The space complexity is then also $\tilde O(x^{2/3})$.

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/prime-counting/lucy-fenwick.cpp:core"
    ```

Note that although the theoretical time complexity does go down, the constant-factor overhead of the Fenwick tree makes the algorithm slower on smaller inputs, while on larger inputs its much larger memory usage limits its use. So this optimization is not very practical.

### Further optimization

Although the Fenwick tree brings the Lucy algorithm down to $\tilde O(x^{2/3})$, it is still not fast in practice. To get an efficient algorithm, the Lucy algorithm can be optimized further as follows (let $z < w < y < x$, all powers of $x$):

1.  In the Fenwick-tree-optimized Lucy algorithm, the sieve of Eratosthenes part costs $O(y\log y)$. In fact, the first few rounds of transitions sieve out a huge number of composites, and there is no need to maintain them with a Fenwick tree. So choose $z < y$. When $p_a \le z$, use only the transition equation; when $p_a > z$, bring in the Fenwick tree to maintain the part of $S(\cdot,a)$ not exceeding $y$. By the time the Fenwick tree is introduced, all integers with a prime factor not greater than $z$ have been sieved out. Among the remaining numbers, often called $z$-rough numbers, only $O\left(\dfrac{y}{\log z}\right)$ do not exceed $y$[^rough]. This lowers the cost of the sieve part to $O(y)$. The first rounds of transitions cost $O(x^{1/2}z/\log x)$.

2.  The Lucy algorithm described above always ends up with the values of $\pi(\cdot)$ at all elements of $D(x)$. If we only want $\pi(x)$, many transitions are unnecessary. For example, to compute $S(x,a)$ we only need $S(x,a-1)$ and $S\left(\dfrac{x}{p_a},a-1\right)$; and to compute those two, we only need

    $$
    S(x,a-2),~ S\left(\dfrac{x}{p_a},a-2\right),~ S\left(\dfrac{x}{p_{a-1}},a-2\right),~ S\left(\dfrac{x}{p_ap_{a-1}},a-2\right)
    $$

    By induction, in round $i$ of the transitions, every needed state $S\left(\dfrac{x}{n},i\right)$ has $n$ a $p_i$-rough number. Since $p_i$-rough numbers are closed under multiplication, it is enough to process all $p_i$-rough numbers (as divisors of nodes) in each transition; then, when the transitions finish, the values at all $p_i$-rough nodes are correct.

    Of course, the set of $p_i$-rough numbers can be maintained dynamically during the sieve[^lucy-rough]; alternatively, we can reuse the set of $z$-rough numbers from above in place of all $p_i$-rough numbers. The second way seems to do some extra useless work, but both remove a factor of $\log x$ from the complexity of the transition part; they differ only in the constant factor.

3.  As with the sieve part, the transition part also suffers an extra $\log x$ from the Fenwick tree. To reduce Fenwick tree queries, the part of the Fenwick tree that will no longer be updated can be stored in a static array. Specifically, when the transitions reach round $i$, the values $S(u,i)$ for $u < p_i^2$ will not change anymore, so they can be queried once and stored.

    Let us compute the improvement this gives. To account for the other optimizations, assume here that transitions with the Fenwick-tree sieve only handle $z < p_i \le w$, and assume $y \ge w^2$ so that the counts below are tight. Every $u$ that needs a transition has the form $\lfloor x/j\rfloor$, so it suffices to count the corresponding $j$. For simplicity, ignore boundary cases of the inequalities. Since $u > y$, we must have $j < x / y$. If $jp_i < x / y$, the Fenwick tree is not involved; if $x / y < jp_i < \min\{x/p_i^2,p_ix/y\}$, the query can only be made on the Fenwick tree; if $\min\{x/p_i^3,x/y\} < j < x/y$, the query can use either the static array or the Fenwick tree. The total count of the first part is

    $$
    \sum_{z < p_i < w}\dfrac{x}{yp_i} = \dfrac{x}{y}\log\dfrac{\log w}{\log z} \in O\left(\dfrac{x}{y}\right).
    $$

    The total count of the second part is

    $$
    \sum_{z < p_i < y^{1/3}}\dfrac{x}{y}\left(1-\dfrac{1}{p_i}\right) + \sum_{y^{1/3} < p_i < w}\left(\dfrac{x}{p_i^3} - \dfrac{x}{yp_i}\right) \le \dfrac{x}{y}\pi(y^{1/3}) + \dfrac{x}{y^{2/3}\log y} \in O\left(\dfrac{x}{y^{2/3}\log y}\right).
    $$

    The total count of the third part is

    $$
    \sum_{y^{1/3} < p_i < w}\left(\dfrac{x}{y}-\dfrac{x}{p_i^3}\right) \le \pi(w)\dfrac{x}{y} \in O\left(\dfrac{xw}{y\log w}\right).
    $$

    The first part is much smaller than the other two and can be ignored. When $w^2 \le y \ll w^3$, the third part is much larger than the second. Only then does storing these values in a static array remove a factor of $\log x$ from the total time of the transition part; otherwise, the queries of the second part become the bottleneck. In summary, with this optimization the total time complexity of the transition part is

    $$
    O\left(\max\left\{\dfrac{x}{y^{2/3}},\dfrac{xw}{y\log x}\right\}\right).
    $$

    Note that since rough numbers are distributed roughly uniformly, the effect of optimization 2 (the rough-number optimization of the transition part) is independent of this one. If the rough-number optimization is applied as well, the complexity here drops by another factor of $\log x$.

4.  The transitions can stop early, updating only up to $p_a\le w$, and the rest can be handled with the idea of the Meissel–Lehmer algorithm. Unlike Meissel–Lehmer algorithms based on $\varphi(x,a)$, $S(x,a)$ already holds the needed values of $\pi(x)$ for $x \le p_a^2$, so no extra precomputation is needed. But when combining this with the optimizations above, watch out for the effect of the rough-number optimization of the DP (optimization 2), and do not use values that were not updated correctly. This improves both time and space complexity, but how much depends heavily on how the other parts are implemented, so we do not give a general analysis here. The analysis of this part for the reference implementation is given below.

Combine these four small optimizations. For any $w \le x^{1/3}$, with $z < w$ and $w^2 \le y < w^3$, the total time complexity of the sieve part and the transition part is

$$
O\left(y + \dfrac{z\sqrt{x}}{\log x} + \dfrac{xw}{y\log x}\right).
$$

So with $y=x^{5/8}\log^{-1}x$ and $z=w^{1/2}$, the total time complexity is $O\left(\dfrac{\sqrt{xw}}{\log x}\right)$. Here $z$ is chosen as large as possible without increasing the overall complexity, to lower the density of $z$-rough numbers and thus the constant factor.

If the algorithm stops early at $w=x^{1/3}$, both its time and space complexity are at least[^complex-third] $O(x^{2/3}\log^{-1}x)$. We now show that stopping at $w=x^{1/4}$ gives lower time and space complexity.

Let $w=x^{1/4}$. Since we stop early at $a=\pi(x^{1/4})$, getting $\pi(x)$ requires the relation:

$$
\pi(x) = S(x,a) - P_2(x,a) - P_3(x,a).
$$

From the earlier analysis,

$$
P_2(x,a) = \sum_{i=a+1}^{\pi(\sqrt{x})}\pi\left(\dfrac{x}{p_i}\right) - \dfrac{1}{2}(\pi(\sqrt{x})+a-1)(\pi(\sqrt{x})-a).
$$

Since we have sieved up to $p_a$, $\pi(\sqrt{x})$ can be read from $S(\cdot,a)$. However, since $x/p_i\in[\sqrt{x},x^{3/4})$, the values $\pi(\cdot)$ in the sum still differ from $S(\cdot,a)$. Expanding further,

$$
\sum_{i=a+1}^{\pi(\sqrt{x})}\pi\left(\dfrac{x}{p_i}\right) = \sum_{i=a+1}^{\pi(\sqrt{x})}S\left(\dfrac{x}{p_i},a\right) - \sum_{i=a+1}^{\pi(\sqrt{x})}P_2\left(\dfrac{x}{p_i},a\right).
$$

Substituting back into the previous formula gives

$$
\begin{aligned}
\pi(x) &= S(x,a) + \dfrac{1}{2}(\pi(\sqrt{x})+a-1)(\pi(\sqrt{x})-a) \\
&\quad - \sum_{i=a+1}^{\pi(\sqrt{x})}S\left(\dfrac{x}{p_i},a\right) + \underbrace{ \sum_{i=a+1}^{\pi(\sqrt{x})}P_2\left(\dfrac{x}{p_i},a\right) - P_3(x,a) }_{\Delta(x)}.
\end{aligned}
$$

To compute $\Delta(x)$, consider what it counts. From the definitions of $P_2(x,a)$ and $P_3(x,a)$,

$$
\begin{aligned}
\sum_{i=a+1}^{\pi(\sqrt{x})}P_2\left(\dfrac{x}{p_i},a\right) &= \#\{p_ip_jp_k \le x : a < i,~ a < j \le k\},\\
P_3(x,a) &= \#\{p_ip_jp_k \le x : a < i \le j \le k\}.
\end{aligned}
$$

Taking the difference of the two sets gives

$$
\Delta(x) = \#\{p_ip_jp_k \le x : a < j,~ j < i,~ j \le k\}.
$$

To count this, again enumerate the smallest prime factor $p_j$ (since it has the smallest upper limit). For a fixed $j$, the other indices must satisfy $i > j$ and $k \ge j$. Split off the special case $k=j$; in the remaining cases $i,k > j$, and symmetry simplifies things further, giving:

$$
\Delta(x) = \underbrace{\sum_{j=a+1}^{\pi(x^{1/3})}\left(\pi\left(\dfrac{x}{p_j^2}\right) - j\right)}_{i > j = k} + \underbrace{2\sum_{j=a+1}^{\pi(x^{1/3})}\left(\sum_{i=j+1}^{\pi(\sqrt{x/p_j})}\left(\pi\left(\dfrac{x}{p_ip_j}\right) - i\right) \right)}_{i > k > j \text{ or }k > i > j } + \underbrace{\sum_{j=a+1}^{\pi(x^{1/3})}\left(\pi\left(\sqrt{\dfrac{x}{p_j}}\right) - j\right)}_{i=k > j}.
$$

Simplifying the sums gives

$$
\Delta(x) = \sum_{j=a+1}^{\pi(x^{1/3})}\left(\pi\left(\dfrac{x}{p_j^2}\right) - j + 2 \sum_{i=j+1}^{\pi(\sqrt{x/p_j})}\pi\left(\dfrac{x}{p_ip_j}\right) - \left( \pi\left(\sqrt{\dfrac{x}{p_j}}\right) ^ 2 - j^2 \right) \right).
$$

With this expression, computing $\Delta(x)$ takes (estimated the same way as in the complexity analysis of the Lucy algorithm above)

$$
O\left(\sum_{x^{1/4} < p \le x^{1/3}}\pi\left(\sqrt{\dfrac{x}{p}}\right)\right) = O\left(\dfrac{x^{2/3}}{\log^2 x}\right).
$$

This is exactly the complexity of the last part of the computation. A quick check shows that every term $\pi(x/n)$ involved in computing $\Delta(x)$ has $x/n\le\sqrt{x} < y$, so all of them can be read directly from $S(\cdot,a)$ stored in the Fenwick tree (they should be copied into a static array beforehand to avoid an extra $O(\log x)$ per query).

Combined with the earlier analysis, with $z=x^{1/8},~w=x^{1/4},~y=x^{5/8}\log^{-1}x$, the total time of the sieve and DP parts is $O(x^{5/8}\log^{-1}x)$, so the overall time complexity is $O(x^{2/3}\log^{-2}x)$. The space complexity is the length of the Fenwick tree, $O(y)=O(x^{5/8}\log^{-1}x)$.

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/prime-counting/lucy-opt.cpp:core"
    ```

For the input ranges common in competitive programming ($10^{10}\sim 10^{14}$), this implementation is excellent in both time and memory. Note that although the last part is the bottleneck in the theoretical analysis, its complexity has a smaller log factor and a better constant, so in the ranges above the real bottleneck is still the sieve and DP parts. This is exactly why optimizing their complexity is essential.

## Generalization: prefix sums of prime powers

More generally, consider the following problem:

$$
F_{\text{prime}}(x) = \sum_{p\in\mathbf P,~p\le x}f(p).
$$

That is, compute the sum of the values of an arithmetic function $f(\cdot)$ over the primes not exceeding $x$. The prime counting function $\pi(x)$ is the special case $f\equiv 1$.

Assume the arithmetic function $f$ satisfies:

1.  $f$ is completely multiplicative, that is, $f(mn)=f(m)f(n)$ for all positive integers $m,n$;
2.  the prefix sum $F(x)=\sum_{n \le x}f(n)$ is easy to compute.

Common arithmetic functions satisfying these conditions include power functions and [Dirichlet characters](https://en.wikipedia.org/wiki/Dirichlet_character) (for example the [Legendre symbol](./quad-residue.md#legendre-symbol)). Of course, if a function is a linear combination of functions satisfying these conditions, its prefix sum over primes can also be computed. So the method in this section handles the cases where $f$ is a polynomial or $f$ is periodic[^periodic]. Another, simpler way to handle periodic functions is shown in the example problems later.

Under these conditions, the recurrence above generalizes. Define $S(x,a)$ as the sum of $f(\cdot)$ over the integers in $[2,x]$ that remain after sieving with the first $a$ primes, that is,

$$
S(x,a) = \sum_{1 < n \le x,~ (n\in\mathbf P) \lor (\operatorname{lpf}(n) > p_a)} f(n).
$$

Now the recurrence for $S(x,a)$ can be rewritten as:

$$
S(x,a) = S(x,a-1) - [p_a^2 \le x]f(p_a)\left(S\left(\dfrac{x}{p_a},a-1\right)-S(p_{a}-1,a-1)\right).
$$

The base case is $S(x,0) = F(x) - 1$. The formula says the same thing as before: in the sieve of Eratosthenes, every composite sieved out by $p_a$ is the product of $p_a$ and some integer not yet sieved out by the first $a-1$ primes. But the integers not yet sieved out by the first $a-1$ primes also include the first $a-1$ primes themselves, and they must be removed. So, to get the sum of the function over these composites, use **complete multiplicativity** to pull out the factor $f(p_a)$; the remaining sum is $S(x/p_a,a-1)$ minus the contribution of the first $(a-1)$ primes, $S(p_a-1,a-1)$. Note that the subtracted term can also be written as $S(p_{a-1},a-1)$; the two are equal.

With this recurrence, the Lucy algorithm computes $F_{\text{prime}}(x)$ in $O(x^{3/4}\log^{-1}x)$ time with only $O(x^{1/2})$ space. A Fenwick tree can lower the time to $\tilde O(x^{2/3})$, but this is not very practical.

??? example "Reference implementation for the template problem [Luogu P5493 Prime Prefix Statistics](https://www.luogu.com.cn/problem/P5493)"
    ```cpp
    --8<-- "docs/math/code/prime-counting/prime-power-sum.cpp"
    ```

In principle, for the generalized Lucy algorithm it is better to precompute the primes rather than merge that step into the DP. This is because the test $S(u,\pi(u-1))\neq S(u-1,\pi(u-1))$ does not necessarily work for a general $f$. Also, although this section only discusses generalizing the Lucy algorithm, the other algorithms can be generalized in a similar way; but the Lucy algorithm gives the values of $F_\text{prime}$ at all elements of $D(x)$, which is more useful for summing multiplicative functions afterwards, so this section only covers its generalization.

## Example problems

???+ example "[Codeforces 665 F. Four Divisors](https://codeforces.com/problemset/problem/665/F)"
    Given $n$, count the integers in $[1,n]$ with exactly $4$ divisors. Here $1\le n\le 10^{11}$.

??? note "Solution"
    An integer with exactly $4$ divisors must have the form $p^3$ or $pq$, where $p,q$ are primes and $p < q$. In $[1,n]$ there are $\pi(n^{1/3})$ integers of the form $p^3$, and the number of integers of the form $pq$ is
    
    $$
    \sum_{p < \sqrt{n}}\left(\pi\left(\dfrac{n}{p}\right)-\pi(p)\right)
    $$
    
    Every prime counting value in the expression above can be computed from values at the set $D(n)$, so one run of the Lucy algorithm solves the problem. The time complexity is $O(n^{3/4}\log^{-1}n)$ and the space complexity is $O(n^{1/2})$.

??? note "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/prime-counting/prime-count-1.cpp"
    ```

???+ example "[LOJ 6028. "from CommonAnts" Prime Counting II](https://loj.ac/p/6028)"
    Given $n,m$, for each of $0,1,2,\dots,m-1$, count the primes in $[1,n]$ congruent to it modulo $m$. Here $1\le n\le 3\times 10^{10}$, $1 < m\le 12$ and $n > m$.

??? note "Solution"
    For any remainder $r=0,1,2,\dots,m-1$, the function $[n\bmod m = r]$ is clearly periodic. As explained above, this kind of problem can be handled by summing Dirichlet characters, but that is tedious and involves complex numbers. So this problem uses another method.
    
    Add one more dimension to the transition equation of the Lucy algorithm. Let $S(n,r,a)$ be the number of integers in $[2,n]$ congruent to $r$ modulo $m$ that remain after sieving with the first $a$ primes. As in the main text, we get the recurrence:
    
    $$
    S(n,rp_a\bmod m,a) = S(n,rp_a\bmod m,a-1) - [p_a^2 \le n]\left(S\left(\dfrac{n}{p_a},r,a-1\right)-S(p_{a}-1,r,a-1)\right).
    $$
    
    In the recurrence, the second argument uses multiplication instead of division because $p_a\mid m$ is possible. The base case is $S(n,r,0) = \left\lfloor\dfrac{n-r}{m}\right\rfloor + [r> 1]$. With this, the problem is solved by dynamic programming. The time complexity is $O(mn^{3/4}\log^{-1}n)$ and the space complexity is $O(mn^{1/2})$.

??? note "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/prime-counting/prime-count-2.cpp"
    ```

## Exercises

-   [Counting Primes - Library Checker](https://judge.yosupo.jp/problem/counting_primes)
-   [P7884 [Template] Meissel-Lehmer](https://www.luogu.com.cn/problem/P7884)
-   [SPOJ NTHPRIME - Nth Prime](https://www.spoj.com/problems/NTHPRIME/)
-   [SPOJ SUMPRIM1 - Sum of primes](https://www.spoj.com/problems/SUMPRIM1/)
-   [SPOJ BBAD - Breaking Math](https://www.spoj.com/problems/BBAD/)
-   [SPOJ APS2 - Amazing Prime Sequence (hard)](https://www.spoj.com/problems/APS2/)
-   [SPOJ DIVFACT4 - Divisors of factorial (extreme)](https://www.spoj.com/problems/DIVFACT4/)

## References and notes

-   [Meissel–Lehmer algorithm - Wikipedia](https://en.wikipedia.org/wiki/Meissel%E2%80%93Lehmer_algorithm)
-   [Lucy's Algorithm + Fenwick Trees - griff's math blog!](https://gbroxey.github.io/blog/2023/04/09/lucy-fenwick.html)
-   [Counting primes in $\tilde O(n^{2/3})$ by Maksim1744 - Codeforces](https://codeforces.com/blog/entry/91632)
-   [Editorial for P7884 [Template] Meissel–Lehmer algorithm by Jianbianse - Luogu](https://www.luogu.com.cn/article/q4d4jl20)
-   Lehmer, Derrick H. "On the exact number of primes less than a given limit." Illinois Journal of Mathematics 3, no. 3 (1959): 381-388.
-   Lagarias, Jeffrey C., Victor S. Miller, and Andrew M. Odlyzko. "Computing $\pi(x)$: the Meissel-Lehmer method." Mathematics of Computation 44.170 (1985): 537-560.
-   [Deléglise, Marc, and Joël Rivat. "Computing 𝜋 (𝑥): the Meissel, Lehmer, Lagarias, Miller, Odlyzko method." Mathematics of Computation 65.213 (1996): 235-245.](https://dl.acm.org/doi/abs/10.1090/s0025-5718-96-00674-6)
-   [Staple, Douglas B. "The combinatorial algorithm for computing $\pi(x)$." arXiv preprint arXiv:1503.01839 (2015).](https://arxiv.org/pdf/1503.01839)

[^lucy-rough]: For a dynamic implementation, see [the section on optimization tricks in griff's blog post](https://gbroxey.github.io/blog/2023/04/09/lucy-fenwick.html#trick-for-further-optimization).

[^periodic]: Every arithmetic function with period $m$ that is nonzero only at integers coprime to $m$ can be written as a linear combination of Dirichlet characters modulo $m$. When computing prefix sums over primes, only finitely many integers not coprime to $m$ are involved, so the original periodic function can always be adjusted to be zero at those integers, which lets it be written as a linear combination of Dirichlet characters modulo $m$.

[^rough]: See [Buchstab function - Wikipedia](https://en.wikipedia.org/wiki/Buchstab_function#Applications).

[^complex-third]: A simple analysis shows that the time and space complexity are in fact exactly $O(x^{2/3}\log^{-1}x)$.

[^sgtlaugh]: Although the original author noted in the code that the complexity is roughly $O(x^{2/3})$, actual measurements show that for a fixed $V$ the complexity is roughly $\Theta(x)$. Even if $V$ is tuned to the problem size, the complexity is still at least $\Omega(x^{0.8})$.

[^smooth]: See [Smooth number - Wikipedia](https://en.wikipedia.org/wiki/Smooth_number#Distribution).

[^lmo-segsieve]: The total number of $n$ enumerated in this step is actually larger than the number of special leaves, but this does not affect the overall complexity. See the original paper for the proof.
