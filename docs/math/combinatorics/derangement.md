## Derangements

### Definition

A derangement is a permutation in which no element appears in its original position. That is, a permutation $P$ of $1\sim n$ is called a derangement of $n$ if $P_i\neq i$ for all $i$.

For example, the derangements of 3 elements are $\{2,3,1\}$ and $\{3,1,2\}$. The derangements of 4 elements are $\{2,1,4,3\}$, $\{2,3,4,1\}$, $\{2,4,1,3\}$, $\{3,1,4,2\}$, $\{3,4,1,2\}$, $\{3,4,2,1\}$, $\{4,1,2,3\}$, $\{4,3,1,2\}$ and $\{4,3,2,1\}$. A derangement is a permutation with no fixed points, that is, with no cycles of length 1.

### Computing with inclusion–exclusion

The universe $U$ is the set of permutations of $1\sim n$, so $|U|=n!$. Let $S_i$ be the set of permutations in it with $P_i\neq i$. Using complements and the [inclusion–exclusion principle](./inclusion-exclusion-principle.md), the problem becomes computing:

$$
\begin{aligned}
\left|\bigcap_{i=1}^n S_i\right|
&=|U|-\left|\bigcup_{i=1}^n\overline{S_i}\right|\\
&=n!-\sum_{k=1}^n(-1)^{k-1}\sum_{a_i<a_{i+1}}\left|\bigcap_{i=1}^{k}\overline{S_{a_i}}\right|
\end{aligned}
$$

Here the sum ranges over choices of $a_1, a_2, \cdots, a_k$ from $1, 2, \cdots, n$ with $a_i<a_{i+1}$. Then

$$
\left|\bigcap_{i=1}^{k}\overline{S_{a_i}}\right|
$$

is the number of permutations in which the $k$ numbers $a_1,a_2,\cdots,a_k$ satisfy $P_{a_i}=a_i$, and the remaining $n-k$ numbers can be in any positions. So:

$$
\left|\bigcap_{i=1}^{k}\overline{S_{a_i}}\right|=(n-k)!
$$

There are $\dbinom{n}{k}$ ways to choose these $k$ numbers. Summing gives:

$$
\begin{aligned}
&\sum_{k=1}^n(-1)^{k-1}\sum_{a_i<a_{i+1}}\left|\bigcap_{i=1}^{k}\overline{S_{a_i}}\right|\\
=&\sum_{k=1}^n(-1)^{k-1}\dbinom{n}{k}(n-k)!\\
=&\sum_{k=1}^n(-1)^{k-1}\frac{n!}{k!}\\
=&n!\sum_{k=1}^n\frac{(-1)^{k-1} }{k!}
\end{aligned}
$$

So the number of derangements of $n$ elements is:

$$
D_n=n!-n!\sum_{k=1}^n\frac{(-1)^{k-1} }{k!}=n!\sum_{k=0}^n\frac{(-1)^k}{k!}
$$

The first few terms of the derangement sequence are $0,1,2,9,44,265$ ([OEIS A000166](http://oeis.org/A000166)).

### Computing with a recurrence

To make the derangement problem concrete, consider the following problem:

There are $n$ different letters, numbered $1,2,3,4,5$. We want to put these five letters into envelopes numbered $1,2,3,4,5$ so that no letter goes into the envelope with its own number. How many different ways are there?

Suppose we are now considering the $n$-th envelope. At first, temporarily put letter $n$ into envelope $n$, then consider two cases for the recurrence:

-   all of the first $n-1$ envelopes hold the wrong letters;
-   among the first $n-1$ envelopes, exactly one holds the right letter and the rest hold wrong letters.

In the first case, all of the first $n-1$ envelopes hold wrong letters. Since the first $n-1$ are already all wrong, letter $n$ just needs to swap with any one of the earlier positions, giving $D_{n-1}\times (n-1)$ cases in total.

In the second case, among the first $n-1$ envelopes exactly one holds the right letter and the rest are wrong. We consider this case because if exactly one of the $n-1$ envelopes is right, swapping that one with $n$ gives a full derangement.

In any other case, a single operation cannot turn it into a derangement of length $n$.

So the number of derangements satisfies the recurrence:

$$
D_n=(n-1)(D_{n-1}+D_{n-2})
$$

Here is another recurrence as well:

$$
D_n=nD_{n-1}+{(-1)}^n
$$

### Other relations

The number of derangements has a simple rounding formula, and its growth differs from the factorial only by a constant factor:

$$
D_n=\left\lfloor\frac{n!}{\mathrm{e}} + \frac{1}{2}\right\rfloor
$$

As the number of elements grows, the probability P that a permutation is a derangement approaches:

$$
P=\lim_{n\to\infty}\frac{D_n}{n!}=\frac{1}{\mathrm{e}}
$$
