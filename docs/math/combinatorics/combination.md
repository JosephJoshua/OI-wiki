## Introduction

Permutations and combinations are the foundation of combinatorics. A permutation means taking a given number of elements out of a given set of elements and arranging them in order; a combination means just taking a given number of elements out of a given set, without caring about order. The central question is counting how many permutations and combinations satisfy given requirements. Permutations and combinations are closely tied to classical probability theory.

In high school mathematics, problems on permutations and combinations are mostly solved by methods such as listing and enumeration.

## The addition and multiplication principles

### Addition principle

Suppose a task can be done by $n$ kinds of methods, and $a_i(1 \le i \le n)$ is the number of methods of kind $i$. Then there are $S=a_1+a_2+\cdots +a_n$ different ways to do the task.

### Multiplication principle

Suppose a task is done in $n$ steps, and $a_i(1 \le i \le n)$ is the number of different ways to do step $i$. Then there are $S = a_1 \times a_2 \times \cdots \times a_n$ different ways to do the task.

## Basics of permutations and combinations

### Number of permutations

Taking any $m$ elements ($m\leq n$, where $m$ and $n$ are natural numbers; the same below) from $n$ distinct elements and arranging them in a row in some order is called a permutation of $m$ elements taken from $n$ distinct elements. The number of all such permutations of $m$ ($m\leq n$) elements taken from $n$ distinct elements is called the number of permutations of $m$ elements out of $n$, written $\mathrm A_n^m$ (or $\mathrm P_n^m$).

The formula for the number of permutations is:

$$
\mathrm A_n^m = n(n-1)(n-2) \cdots (n-m+1) = \frac{n!}{(n - m)!}
$$

$n!$ is the factorial of $n$, for example $6! = 1 \times 2 \times 3 \times 4 \times 5 \times 6$.

You can understand the formula like this: choose $m$ out of $n$ people to stand in a line ($m \le n$). The first position has $n$ choices, the second has $n-1$ choices, and so on, so the $m$-th (last) position has $n-m+1$ choices. This gives:

$$
\mathrm A_n^m = n(n-1)(n-2) \cdots (n-m+1) = \frac{n!}{(n - m)!}
$$

Full permutation: all $n$ people stand in a line, so the line has length $n$. The first position has $n$ choices, the second has $n-1$ choices, and so on, which gives:

$$
\mathrm A_n^n = n(n-1)(n-2) \cdots 3 \times 2 \times 1 = n!
$$

A full permutation is a special case of the number of permutations.

### Binomial coefficients

Taking any $m \leq n$ elements from $n$ distinct elements to form a set is called a combination of $m$ elements taken from $n$ distinct elements. The number of all such combinations of $m \leq n$ elements taken from $n$ distinct elements is called the number of combinations of $m$ elements out of $n$. It is written $\dbinom{n}{m}$ and read "$n$ choose $m$".

Formula for the number of combinations

$$
\dbinom{n}{m} = \frac{\mathrm A_n^m}{m!} = \frac{n!}{m!(n - m)!}
$$

How do we understand this formula? Consider choosing $m$ out of $n$ people ($m \le n$), without lining them up, so the order does not matter. If order mattered, the answer would be $\mathrm A_n^m$. Since it does not, we must divide out the repeats. How many repeats are there? The same $m$ chosen people can be "fully permuted" in $m!$ ways, so:

$$
\begin{aligned}
\dbinom{n}{m} \times m! &= \mathrm A_n^m\\
\dbinom{n}{m} &= \frac{\mathrm A_n^m}{m!} = \frac{n!}{m!(n-m)!}
\end{aligned}
$$

The number of combinations is also often written $\mathrm C_n^m$, i.e. $\displaystyle \mathrm C_n^m=\binom{n}{m}$. Today mathematicians generally use the notation $\dbinom{n}{m}$ instead of $\mathrm C_n^m$.

Numbers of combinations are also called "binomial coefficients". The binomial theorem below explains the connection.

In particular, when $m>n$, we define $\mathrm A_n^m=\dbinom{n}{m}=0$.

## Stars and bars

Stars and bars is a technique for counting the ways to split identical elements into groups. It can also be used to count the solutions of a class of linear Diophantine equations.

### Number of sums of positive integers

Problem 1: there are $n$ **identical** elements. In how many ways can we split them into $k$ groups so that each group has at least one element?

Think of inserting $k - 1$ bars into the $n - 1$ gaps between adjacent elements.

Since the elements are identical, the answer is $\dbinom{n - 1}{k - 1}$.

In essence, this counts the positive integer solutions of $x_1+x_2+\cdots+x_k=n$.

### Number of sums of non-negative integers

Problem 2: what if we change the problem so that groups may be empty?

Clearly we can no longer insert the bars directly, because several bars could go into the same gap, which is very awkward to count.

We create conditions that turn it into Problem 1, which has the restriction. First borrow $k$ elements, then insert bars into the $n + k - 1$ gaps formed by these $n + k$ elements. The answer is

$$
\binom{n + k - 1}{k - 1} = \binom{n + k - 1}{n}
$$

Even though this does not count the original problem directly, this expression is the answer to the original problem. Here is why:

At the start we borrowed $k$ elements to make sure each group has at least one element. After inserting the bars, we take these $k$ borrowed elements back out of the $k$ groups. Since the elements are identical, the cases after the transformation correspond one-to-one with the cases before it, so the answers are equal.

This gives the stars and bars formula: $\dbinom{n + k - 1}{n}$.

In essence, this counts the non-negative integer solutions of $x_1+x_2+\cdots+x_k=n$ (that is, with $x_i \ge 0$).

### Number of integer sums with different lower bounds

Problem 3: extending one step further, what if group $i$ must get at least $a_i$ elements, where $\sum a_i \le n$?

In essence, this counts the solutions of $x_1+x_2+\cdots+x_k=n$ with $x_i \ge a_i$.

As in the unrestricted case, we borrow $\sum a_i$ elements to make sure group $i$ gets at least $a_i$. That is, let

$$
x_i^{\prime}=x_i-a_i
$$

This gives a new equation:

$$
\begin{aligned}
(x_1^{\prime}+a_1)+(x_2^{\prime}+a_2)+\cdots+(x_k^{\prime}+a_k)&=n\\
x_1^{\prime}+x_2^{\prime}+\cdots+x_k^{\prime}&=n-a_1-a_2-\cdots-a_k\\
x_1^{\prime}+x_2^{\prime}+\cdots+x_k^{\prime}&=n-\sum a_i
\end{aligned}
$$

where

$$
x_i^{\prime}\ge 0
$$

Now Problem 3 has become Problem 2, and the stars and bars formula gives the answer

$$
\binom{n - \sum a_i + k - 1}{n - \sum a_i}
$$

### Non-adjacent selections

The number of ways to choose $k$ of the $n$ natural numbers $1 \sim n$ so that no two of the chosen $k$ numbers are adjacent is $\dbinom {n-k+1}{k}$.

## Binomial theorem

Before moving on to the advanced part on permutations and combinations, we first introduce a theorem closely tied to binomial coefficients: the binomial theorem.

The binomial theorem gives the coefficients of an expansion:

$$
(a+b)^n=\sum_{i=0}^n\binom{n}{i}a^{n-i}b^i
$$

It can be proved by mathematical induction, using $\dbinom{n}{k}+\dbinom{n}{k-1}=\dbinom{n+1}{k}$ for the inductive step.

The binomial theorem also extends easily to the multinomial form:

Let $n$ be a positive integer and $x_i$ be real numbers. Then

$$
(x_1 + x_2 + \cdots + x_t)^n = \sum_{\text{non-negative integer solutions of } n_1 + \cdots + n_t=n} \binom{n}{n_1,n_2,\cdots,n_t} x_1^{n_1}x_2^{n_2}\cdots x_t^{n_t}
$$

Here $\dbinom{n}{n_1,n_2,\cdots,n_t}$ is the multinomial coefficient. Its properties are also similar:

$$
\sum{\binom{n}{n_1,n_2,\cdots,n_t}} = t^n
$$

## Advanced permutations and combinations

Next we introduce some variants of permutations and combinations.

### Permutations of a multiset | Multinomial coefficients

Be sure to tell apart **multinomial coefficients** and **combinations of a multiset**! They are completely different concepts!

A multiset is a generalized set that may contain repeated elements. Let $S=\{n_1\cdot a_1,n_2\cdot a_2,\cdots,n_k\cdot a_k\}$ be the multiset made of $n_1$ copies of $a_1$, $n_2$ copies of $a_2$, ..., $n_k$ copies of $a_k$. The number of full permutations of $S$ is

$$
\frac{n!}{\prod_{i=1}^kn_i!}=\frac{n!}{n_1!n_2!\cdots n_k!}
$$

This amounts to dividing out the permutations among identical elements. Concretely, think of having $k$ different kinds of balls, with $n_1,n_2,\cdots,n_k$ balls of each kind, and $n=n_1+n_2+\ldots+n_k$. The number of full permutations of these $n$ balls is the **number of permutations of the multiset**. It is often called the **multinomial coefficient**. We can write the expression above using multinomial coefficient notation:

$$
\binom{n}{n_1,n_2,\cdots,n_k}=\frac{n!}{\prod_{i=1}^kn_i!}
$$

We can see that $\dbinom{n}{m}$ is the same as $\dbinom{n}{m,n-m}$, but the latter is more cumbersome, so it is not used.

### Combinations of a multiset 1

Let $S=\{n_1\cdot a_1,n_2\cdot a_2,\cdots,n_k\cdot a_k\}$ be the multiset made of $n_1$ copies of $a_1$, $n_2$ copies of $a_2$, ..., $n_k$ copies of $a_k$. For an integer $r(r<n_i,\forall i\in[1,k])$, the number of ways to choose $r$ elements from $S$ to form a multiset is the **number of combinations of the multiset**. This problem is the same as counting the non-negative integer solutions of $x_1+x_2+\cdots+x_k=r$, which stars and bars solves. The answer is

$$
\binom{r+k-1}{k-1}
$$

### Combinations of a multiset 2

Consider this problem: let $S=\{n_1\cdot a_1,n_2\cdot a_2,\cdots,n_k\cdot a_k,\}$ be the multiset made of $n_1$ copies of $a_1$, $n_2$ copies of $a_2$, ..., $n_k$ copies of $a_k$. For a positive integer $r$, find the number of ways to choose $r$ elements from $S$ to form a multiset.

This limits how many of each kind of element we can take. As before, we can turn this into solving a linear equation with constraints:

$$
\forall i\in [1,k],\ x_i\le n_i,\ \sum_{i=1}^kx_i=r
$$

This naturally suggests the inclusion–exclusion principle. The inclusion–exclusion model is:

1.  Universe: the non-negative integer solutions of $\displaystyle \sum_{i=1}^kx_i=r$.
2.  Properties: $x_i\le n_i$.

Let $S_i$ be the set satisfying property $i$, and $\overline{S_i}$ the set not satisfying property $i$, i.e. the set with $x_i\ge n_i+1$ (which becomes Problem 3 of stars and bars above). Then the answer is

$$
\left|\bigcap_{i=1}^kS_i\right|=|U|-\left|\bigcup_{i=1}^k\overline{S_i}\right|
$$

By the inclusion–exclusion principle, we have:

$$
\begin{aligned}
\left|\bigcup_{i=1}^k\overline{S_i}\right|
=&\sum_i\left|\overline{S_i}\right|
-\sum_{i,j}\left|\overline{S_i}\cap\overline{S_j}\right|
+\sum_{i,j,k}\left|\overline{S_i}\cap\overline{S_j}\cap\overline{S_k}\right|
-\cdots\\
&+(-1)^{k-1}\left|\bigcap_{i=1}^k\overline{S_i}\right|\\
=&\sum_i\binom{k+r-n_i-2}{k-1}
-\sum_{i,j}\binom{k+r-n_i-n_j-3}{k-1}+\sum_{i,j,k}\binom{k+r-n_i-n_j-n_k-4}{k-1}
-\cdots\\
&+(-1)^{k-1}\binom{k+r-\sum_{i=1}^kn_i-k-1}{k-1}
\end{aligned}
$$

Subtracting this from the universe $\displaystyle |U|=\binom{k+r-1}{k-1}$ gives the number of combinations of the multiset:

$$
Ans=\sum_{p=0}^k(-1)^p\sum_{A}\binom{k+r-1-\sum_{A} n_{A_i}-p}{k-1}
$$

Here A acts as the enumerated subset, with $|A|=p,\ A_i<A_{i+1}$.

### Circular permutations

Let all $n$ people stand in a circle, and write $\mathrm Q_n^n$ for the number of all arrangements. Take one arranged circle and break it at different positions; this gives different lines.
So we have

$$
\mathrm Q_n^n \times n = \mathrm A_n^n \Longrightarrow \mathrm Q_n = \frac{\mathrm A_n^n}{n} = (n-1)!
$$

From this we get the formula for partial circular permutations:

$$
\mathrm Q_n^r = \frac{\mathrm A_n^r}{r} = \frac{n!}{r \times (n-r)!}
$$

## Properties of binomial coefficients | Corollaries of the binomial theorem

Binomial coefficients are very important in OI, so here are some of their properties.

$$
\binom{n}{m}=\binom{n}{n-m}\tag{1}
$$

This amounts to taking the complement of the chosen set within the whole set, so the value is unchanged. (Symmetry)

$$
\binom{n}{k} = \frac{n}{k} \binom{n-1}{k-1}\tag{2}
$$

A recurrence derived from the definition.

$$
\binom{n}{m}=\binom{n-1}{m}+\binom{n-1}{m-1}\tag{3}
$$

The recurrence for binomial coefficients (the formula behind Pascal's triangle). We can use it to compute binomial coefficients in $O(n^2)$ time.

$$
\binom{n}{0}+\binom{n}{1}+\cdots+\binom{n}{n}=\sum_{i=0}^n\binom{n}{i}=2^n\tag{4}
$$

This is a special case of the binomial theorem. Taking $a=b=1$ gives the formula above.

$$
\sum_{i=0}^n(-1)^i\binom{n}{i}=[n=0]\tag{5}
$$

Another special case of the binomial theorem, taking $a=1, b=-1$. The special case is $n=0$, where the answer is $1$.

$$
\sum_{i=0}^k \binom{n}{i}\binom{m}{k-i} = \binom{m+n}{k}\tag{6}
$$

A formula for splitting binomial coefficients, used in some data structure problems. It is called [Vandermonde's identity](https://en.wikipedia.org/wiki/Vandermonde%27s_identity).

$$
\sum_{i=0}^n\binom{n}{i}^2=\binom{2n}{n}\tag{7}
$$

This is a special case of $(6)$ with $n=k=m$.

$$
\sum_{i=0}^ni\binom{n}{i}=n2^{n-1}\tag{8}
$$

A weighted sum formula. It can be proved by differentiating the polynomial function behind $(4)$.

$$
\sum_{i=0}^ni^2\binom{n}{i}=n(n+1)2^{n-2}\tag{9}
$$

Like the formula above, it can be proved by differentiating a polynomial function.

$$
\sum_{l=0}^n\binom{l}{k} = \binom{n+1}{k+1}\tag{10}
$$

It can be proved combinatorially by counting the $(k+1)$-subsets of $S=\{a_1, a_2, \cdots, a_{n+1}\}$ case by case. It is often used in proving identities. It is called the [hockey-stick identity](https://en.wikipedia.org/wiki/Hockey-stick_identity) (also known as Zhu Shijie's identity).

$$
\binom{n}{r}\binom{r}{k} = \binom{n}{k}\binom{n-k}{r-k}\tag{11}
$$

It can be proved from the definition.

$$
\sum_{i=0}^n\binom{n-i}{i}=F_{n+1}\tag{12}
$$

Here $F$ is the Fibonacci sequence.

$$
\binom{n+k}{k}^2=\sum_{j=0}^k\binom{k}{j}^2\binom{n+2k-j}{2k}\tag{13}
$$

It can be proved using $(6)$. It is called the [Li Shanlan identity](https://en.wikipedia.org/wiki/Li_Shanlan_identity).

## Binomial inversion

Let $f_n$ be the number of ways to form a particular structure using exactly $n$ distinct elements, and $g_n$ be the total number of ways to choose $i \geq 0$ elements out of $n$ distinct elements and form that structure.

If $f_n$ is known and we want $g_n$, then clearly:

$$
g_n = \sum_{i = 0}^{n} \binom{n}{i} f_i
$$

If $g_n$ is known and we want $f_n$, then:

$$
f_n = \sum_{i = 0}^{n} \binom{n}{i} (-1)^{n-i} g_i
$$

The process above of finding $f_n$ from $g_n$ is called **binomial inversion**.

### Proof

Expanding $g_i$ in the inversion formula gives:

$$
\begin{aligned}
f_n &= \sum_{i = 0}^{n} \binom{n}{i} (-1)^{n-i} \left[\sum_{j = 0}^{i} \binom{i}{j} f_j\right] \\
&= \sum_{i = 0}^{n}\sum_{j = 0}^{i}\binom{n}{i}\binom{i}{j} (-1)^{n-i}f_j
\end{aligned}
$$

Enumerate $j$ first and then $i$, which gives:

$$
\begin{aligned}
f_n &= \sum_{j = 0}^{n}\sum_{i = j}^{n}\binom{n}{i}\binom{i}{j} (-1)^{n-i}f_j \\
&= \sum_{j = 0}^{n}f_j\sum_{i = j}^{n}\binom{n}{i}\binom{i}{j} (-1)^{n-i}
\end{aligned}
$$

Using formula (11) from ["Properties of binomial coefficients | Corollaries of the binomial theorem"](#properties-of-binomial-coefficients--corollaries-of-the-binomial-theorem), we get:

$$
\begin{aligned}
f_n &= \sum_{j = 0}^{n}f_j\sum_{i = j}^{n}\binom{n}{j}\binom{n - j}{i - j} (-1)^{n-i} \\
&= \sum_{j = 0}^{n}\binom{n}{j}f_j\sum_{i = j}^{n}\binom{n - j}{i - j} (-1)^{n-i}
\end{aligned}
$$

Let $k = i - j$. Then $i = k + j$, and the expression becomes:

$$
f_n = \sum_{j = 0}^{n}\binom{n}{j}f_j\sum_{k = 0}^{n - j}\binom{n - j}{k} (-1)^{n-j-k}1^{k}
$$

Using formula (5) from ["Properties of binomial coefficients | Corollaries of the binomial theorem"](#properties-of-binomial-coefficients--corollaries-of-the-binomial-theorem), we get:

$$
f_n = \sum_{j = 0}^{n}\binom{n}{j}f_j[n = j] = f_n
$$

This completes the proof.
