author: sshwy, ComeIntoCalm

The exponential generating function (EGF) of a sequence $a$ is defined as the formal power series:

$$
\hat{F}(x)=\sum_{n}a_n \frac{x^n}{n!}
$$

## Basic operations

Addition and subtraction of EGFs work the same as for ordinary generating functions: you add the coefficients term by term.

Now consider multiplication of EGFs. For two sequences $a,b$ with EGFs $\hat{F}(x),\hat{G}(x)$, we have

$$
\begin{aligned}
\hat{F}(x)\hat{G}(x)
&=\sum_{i\ge 0}a_i\frac{x^i}{i!}\sum_{j\ge 0}b_j\frac{x^j}{j!}\\
&=\sum_{n\ge 0}x^{n}\sum_{i=0}^na_ib_{n-i}\frac{1}{i!(n-i)!}\\
&=\sum_{n\ge 0}\frac{x^{n}}{n!}\sum_{i=0}^n\binom{n}{i}a_ib_{n-i}
\end{aligned}
$$

So $\hat{F}(x)\hat{G}(x)$ is the EGF of the sequence

$$
\left\langle \sum_{i=0}^n \binom{n}{i}a_ib_{n-i} \right\rangle
$$

.

## Closed forms

As with ordinary generating functions, let us look at closed forms of EGFs.

The EGF of the sequence $\langle 1,1,1,\cdots\rangle$ is:

$$
\hat{F}(x) = \sum_{n \ge 0}\frac{x^n}{n!} = \mathrm{e}^x
$$

This is because expanding $\mathrm{e}^x$ as a Taylor series at $x = 0$ gives exactly this infinite series.

Similarly, the EGF of the geometric sequence $\langle 1,p,p^2,\cdots\rangle$ is:

$$
\hat{F}(x) = \sum_{n\ge 0}\frac{p^nx^n}{n!}=\mathrm{e}^{px}
$$

## EGFs and ordinary generating functions

How should we think about EGFs? We defined the EGF of a sequence $a$ as:

$$
F(x)=\sum_{n\ge 0}a_n\frac{x^n}{n!}
$$

But $F(x)$ is also the ordinary generating function of the sequence $\left\langle \dfrac{a_n}{n!} \right\rangle$.

Both views are perfectly fine. In other words, different kinds of generating functions are just different ways of looking at the problem.

## Combinatorial meaning of polynomial exp for EGFs

If you have not learned polynomial exp yet, skip this section for now. It is a meaning that comes from understanding exp, and in some sense it deepens your understanding of EGFs.

In $f^n(x)$, the $f$ is assumed to be an EGF. First consider the product of any two EGFs

$$
\hat{H}(x) = \hat{F}(x)\hat{G}(x) = \sum_{n\geq 0} \left[ \sum_{i = 0}^n\binom {n}{i}f_ig_{n-i} \right] \frac{x^n}{n!}
$$

For the product of two EGFs, $[x^k]\hat{H}(x)$ is really a convolution. For the product of several EGFs, $[x^k]\hat{H}(x)$ is the sum of coefficients over all ways to pick one term $x^{a_i}$ from each EGF such that $\sum_ia_i=k$.
In terms of sets, it is the number of ways to split $n$ labeled elements into $k>0$ labeled sets.

> If $k=0$, the coefficient is clearly the product of the constant terms of the EGFs. But certain requirements of polynomial $\exp$ force the constant term of $f(x)$ in $\exp$ to be $0$; the reasons are explained below.

The definition of multinomial coefficients (see the combinatorial meaning of multinomial coefficients in the combinatorics section) assumes the sets are ordered. But in $f^k(x)$ inside $\exp(f(x))$, the $k$ factors $f(x)$ are identical EGFs, while a set partition is clearly unordered, so the coefficient should be multiplied by $\dfrac{1}{k!}$.

Let $F_k(n)$ be the number of ways to split $n$ labeled elements into $k$ nonempty unordered sets (nonempty because of $\exp$). Let $f_i$ be the number of ways a set of $i$ elements can carry a certain combinatorial structure (this is the original EGF; the count for one set depends only on the size of the set). Then $F_k(n)$ is

$$
F_k(n)=\frac{n!}{k!}\sum_{\sum_{i}^ka_i=n}\prod_{j=1}^{k}\frac{f_{a_j}}{a_j!}
$$

Let the EGF of $f_n$ be $\hat{F}(x)$, that is:

$$
\hat{F}(x) = \sum_{n \geq 0} f_n\frac{x^n}{n!}
$$

Let the EGF of $F_k(n)$ be $G_k(x)$. Then:

$$
\begin{aligned}
G_k(x)&=\sum_{n \geq 0} F_k(n)\frac{x^n}{n!}\\
&=\sum_{n \geq 0} x^n\frac{1}{k!}\sum_{\sum_i^k a_i=n}\prod_{j=1}^{k}\frac{f_{a_j}}{a_j!}\\
&=\frac{1}{k!}\sum_{n \geq 0}\sum_{\sum_i^k a_i=n}\prod_{j=1}^{k}\frac{f_{a_j}x^{a_j}}{a_j!}\\
&=\frac{1}{k!}\hat{F}^k(x)
\end{aligned}
$$

Summing over all $k \geq 0$:

$$
\sum_{k \geq 0}G_k(x) = \sum_{k \geq 0}\frac{\hat{F}^k(x)}{k!} = \exp{\hat{F}(x)}
$$

The above writes the formula directly from a combinatorial viewpoint. We can also prove the relation between $\exp(f(x))$ and $f(x)$ using a recurrence.

Again let $F_k(n)$ be the number of ways to split $n$ labeled elements into $k$ nonempty (unlabeled) sets, let $g_i$ be the number of ways to structure a set of $i$ elements (same meaning as $f_i$ above), let $G(x)$ be the EGF of $\{g_i\}$, and let $H_k(x)$ be the EGF of $\{F_k(n)\}$.

There are $g_i$ ways to take $i$ of the $n$ elements as one separate set, and $F_{k-1}(n-i)$ ways for the remaining $n-i$ elements to form $k-1$ sets. But in the final partition, each set of a given partition gets enumerated as the "separate set", so every partition is counted $k$ times, and we must divide by $k$.

$$
\begin{aligned}
H_k(x) &= \sum_{n\ge 0}\cfrac{x^n}{n!}F_k(n)\\
&=\sum_{n\ge 0}\cfrac{x^n}{n!}\sum_{i=1}^{n-k+1}\binom n {i} F_{k-1}(n-i)\times g_i\times \cfrac{1}{k}\\
&=\cfrac{1}{k}\sum_{n\ge 0}\cfrac{x^n}{n!}\sum_{i=0}^{n}\binom n {i}F_{k-1}(n-i)\times g_i\\
&=\cfrac{1}{k}\cdot  H_{k-1}(x)G(x)
\end{aligned}
$$

The upper bound $n-(k-1)\geq i$ comes from the sets being nonempty (each of the other $k-1$ sets has at least one element). But if we define the terms $F_{k-1}(n-i)$ beyond this bound to be $0$, extending the range changes nothing.

With the recurrence, we can unfold it recursively, with base case $H_1(x)=G(x)$ when $k=1$.

$$
\begin{aligned}
H_k(x) &= \cfrac{1}{k}\cdot   H_{k-1}(x)G(x)\\
&= \cfrac{1}{k}\cdot\cfrac{1}{k-1}\cdot   H_{k-2}(x)G^2(x)\\
&=\cdots \\
&= \cfrac{1}{k}\cdot\cfrac{1}{k-1} \cdots\cfrac{1}{2}\cdot H_{1}(x)G^{k-1}(x)\\
&= \cfrac{1}{k!}G^{k}(x)\\
\end{aligned}
$$

Likewise:

$$
\begin{aligned}
\sum_{k\ge 0}H_k(x)=\sum_{k\ge 0}\cfrac{G^k(x)}{k!}=\exp G(x)
\end{aligned}
$$

Clearly, **defining it as a partition into nonempty sets** ($g_0=0$) matches the intended meaning. If **empty sets are allowed** ($g_0=1$), then $[x^n]G^k$ gets contributions from $[x^n]G^y,y>k$ (by choosing the constant term in at least one $G$), which causes double counting, and we do not get the quantity we want.

From the recurrence viewpoint, the product of several EGFs can also be seen as a knapsack-like combination (the process of merging two groups of counted objects).

To sum up, polynomial $\exp$ means: **the number of ways to form a family of sets from labeled elements**, or the total number of ways to split into any number of nonempty subsets.

## Permutations and circular permutations

The EGF of the number of permutations of length $n$ is

$$
\hat{P}(x)=\sum_{n\ge 0}\frac{n!x^n}{n!}=\sum_{n\ge 0}x^n=\frac{1}{1-x}
$$

A circular permutation is a way to arrange $1,2,\cdots,n$ in a ring. In other words, arrangements that differ by a rotation are equivalent (but reflections are not).

The number of circular permutations of $n$ numbers is clearly $(n-1)!$. So the EGF of the number of circular permutations of $n$ numbers is

$$
\hat{Q}(x)=\sum_{n\ge 1}\frac{(n-1)!x^n}{n!}=\sum_{n\ge 1}\frac{x^n}{n}=-\ln(1-x)=\ln\left( \frac{1}{1-x} \right)
$$

That is, $\exp \hat{Q}(x)=\hat{P}(x)$. But this is just a mathematical derivation. How can we see intuitively that the $\exp$ of the EGF of circular permutations is the EGF of permutations?

A permutation is made up of several permutation cycles. For example, $p=[4,3,2,5,1]$ has two cycles:

![](./images/p1.svg)

(that is, we draw a directed edge from $p_i$ to $i$)

Different cycles give different permutations. For example, if we change the second cycle to

![](./images/p2.svg)

then the corresponding permutation is $[5,3,2,1,4]$.

In other words, the number of permutations of length $n$ is the number of ways to

1.  split $1,2,\cdots,n$ into several sets, and
2.  turn each set into a permutation cycle

. The number of ways to turn a set of numbers into a cycle is clearly the number of circular permutations of that set's size. So the number of permutations of length $n$ is: over all ways to split $1,2,\cdots,n$ into sets, the product of the numbers of circular permutations of each set.

This is the intuitive meaning of polynomial $\exp$.

Generalizing:

-   If the EGF of **labeled** spanning trees on $n$ vertices is $\hat{F}(x)$, then the EGF of **labeled** spanning forests on $n$ vertices is $\exp \hat{F}(x)$. Intuitively: split the $n$ vertices into several sets, and take the product of the numbers of spanning trees on each set.
-   If the EGF of labeled connected undirected graphs on $n$ vertices is $\hat{F}(x)$, then the EGF of labeled undirected graphs on $n$ vertices is $\exp \hat{F}(x)$. The latter is easy to compute:

    $$
    \exp \hat{F}(x)=\sum_{n\ge 0}2^{\binom{n}{2}}\frac{x^n}{n!}
    $$

    So to compute the former, a single polynomial $\ln$ is enough.

Next, let us look at some applications of EGFs.

## Applications

### Derangements

???+ note "Derangements"
    A derangement of length $n$ is a permutation with $p_i\ne i$ for all $i$.
    
    Find the EGF of the number of derangements.

From the viewpoint of permutation cycles, a derangement is a permutation with no self-loops, that is, with no cycle of length $1$. The EGF for cycles of length at least $2$ is

$$
\sum_{n\ge 2}\frac{x^n}{n}=-\ln\left(1-x\right)-x
$$

So the EGF of the number of derangements is $\exp(-\ln(1-x)-x)$.

### Fixed points

???+ note "[Fixed Points](https://www.51nod.com/Html/Challenge/Problem.html#problemId=1728)"
    Problem: count the maps $f:\{1,2,\cdots,n\}\to \{1,2,\cdots,n\}$ such that
    
    $$
    \underbrace{f\circ f\circ\cdots\circ f}_{k}=\underbrace{f\circ f\circ\cdots\circ f}_{k-1}
    $$
    
    $nk\le 2\times 10^6,1\le k\le 3$.

Draw an edge from $i$ to $f(i)$. The condition says that from any $i$, walking $k$ steps and walking $k-1$ steps lead to the same vertex. That is, the cycle of each pseudotree is a self-loop and the depth is at most $k$ (the root has depth $1$). Treating such a pseudotree as a rooted tree is the same thing. So the problem becomes: count forests of labeled rooted trees on $n$ vertices with depth at most $k$.

Consider labeled rooted trees on $n$ vertices with depth at most $k$, and let their generating function be:

$$
\hat{F_k}(x)=\sum_{n\ge 0}f_{n,k}\frac{x^n}{n!}
$$

We compute $\hat{F_k}(x)$ recursively. A rooted tree of depth at most $k$ is just several rooted trees of depth at most $k-1$ whose roots are all connected to one new vertex. So

$$
\hat{F_k}(x)=x\exp \hat{F}_{k-1}(x)
$$

Then the EGF of the answer is $\exp \hat{F}_k(x)$. Just take its $n$-th term.

### Lust

???+ note "[Lust](https://codeforces.com/contest/891/problem/E)"
    You are given a sequence of $n$ numbers $a_1,a_2,\cdots,a_n$ and a variable $s$ with initial value $0$. Repeat the following operation $k$ times:
    
    -   Choose $x$ uniformly at random from $1,2,\cdots,n$.
    -   Add $\prod_{i\ne x}a_i$ to $s$.
    -   Decrease $a_x$ by one.
    
    Find the expected value of $s$ after $k$ operations.
    
    $1\le n\le 5000,1\le k\le 10^9,0\le a_i\le 10^9$.

Suppose that after $k$ operations $a_i$ has decreased by $b_i$. Then in fact

$$
s=\prod_{i=1}^n a_i-\prod_{i=1}^n(a_i- b_i)
$$

So the problem becomes finding the expected value of $\prod_{i=1}^n (a_i- b_i)$ after $k$ operations.

Let us compute the sum of $\prod_{i=1}^n (a_i- b_i)$ over all possible operation sequences, and divide by $n^k$ at the end.

The number of operation sequences of length $k$ in which each $i$ appears $b_i$ times is

$$
\frac{k!}{b_1!b_2!\cdots b_n!}
$$

This looks like the coefficients in EGF multiplication.

Let the EGF for $a_j$ be

$$
F_j(x)=\sum_{i\ge 0}(a_j-i)\frac{x^i}{i!}
$$

Then the answer is

$$
[x^k]\prod_{j=1}^nF_j(x)
$$

To compute the answer quickly, we turn $F_j(x)$ into closed form:

$$
\begin{aligned}
F_j(x)&=\sum_{i\ge 0}a_j\frac{x^i}{i!}-\sum_{i\ge 1}\frac{x^i}{(i-1)!}\\
&=a_j\mathrm{e}^x-x\mathrm{e}^x\\
&=(a_j-x)\mathrm{e}^x
\end{aligned}
$$

So we get

$$
\prod_{j=1}^nF_j(x)=\mathrm{e}^{nx}\prod_{j=1}^n(a_j-x)
$$

Here $\prod_{j=1}^n(a_j-x)$ is a polynomial of degree $n$, which can be computed by brute force. If its expansion is $\sum_{i=0}^nc_ix^i$, then

$$
\begin{aligned}
\prod_{j=1}^nF_j(x)
&=\left(\sum_{i\ge 0} \frac{n^ix^i}{i!}\right)\left(\sum_{i=0}^nc_ix^i\right)\\
&=\sum_{i\ge 0}\sum_{j=0}^i c_jx^j\frac{n^{i-j}x^{i-j}}{(i-j)!}\\
&=\sum_{i\ge 0}\frac{x^{i}}{i!}\sum_{j=0}^i n^{i-j}i^{\underline{j}}c_j
\end{aligned}
$$

Then just compute the coefficient of $x^k$ in this polynomial.
