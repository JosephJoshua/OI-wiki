## Entringer numbers

The Entringer number $E(n,k)$ ([OEIS A008281](http://oeis.org/A008281)) is the number of permutations of the $n+1$ numbers $0$ to $n$ that satisfy the following conditions:

-   the first element is $k$;
-   the next element is smaller than the first, the one after is larger than the previous one, the one after that is smaller than the previous one, and so on: every pair of adjacent elements after that follows this pattern.

The initial values of the Entringer numbers are:

$$
E(0,0)=1
$$

$$
E(n,0)=0
$$

They satisfy the recurrence:

$$
E(n,k)=E(n,k-1)+E(n-1,n-k)
$$

## The Seidel–Entringer–Arnold triangle

Arranging the Entringer numbers suitably gives a triangle of numbers called the Seidel–Entringer–Arnold triangle ([OEIS A008280](http://oeis.org/A008280)). It lists the Entringer numbers $E_(n,k)$ in "ox-plowing" order (boustrophedon order):

$$
\begin{aligned}
& E(0,0) \\
& E(1,0) \rightarrow E(1,1) \\
& E(2,2) \leftarrow E(2,1) \leftarrow E(2,0) \\
& E(3,0) \rightarrow E(3,1) \rightarrow E(3,2) \rightarrow E(3,3) \\
& E(4,4) \leftarrow E(4,3) \leftarrow E(4,2) \leftarrow E(4,1) \leftarrow E(4,0)
\end{aligned}
$$

That is:

$$
\begin{aligned}
& 1 \\
& 0 \rightarrow 1 \\
& 1 \leftarrow 1 \leftarrow 0 \\
& 0 \rightarrow 1 \rightarrow 2 \rightarrow 2 \\
& 5 \leftarrow 5 \leftarrow 4 \leftarrow 2 \leftarrow 0
\end{aligned}
$$

The advantage of arranging the Entringer numbers this way is that it matches their recurrence $E(n,k)=E(n,k-1)+E(n-1,n-k)$, which makes it easy to remember and understand.

The Entringer numbers have an exponential generating function:

$$
\sum_{m=0}^\infty\sum_{n=0}^\infty E\left(m+n,\frac{1}{2}\left(m+n+{(-1)}^{m+n}(n-m)\right)\right)\frac{x^m}{m!}\frac{x^n}{n!}=\frac{\cos x+\sin x}{\cos (x+y)}
$$

The layout of the coefficients of this generating function is in fact a simple stretched version of the Seidel–Entringer–Arnold triangle above:

$$
\begin{array}{ccccc}
E(0,0) & E(1,1) & E(2,0) & E(3,3) & E(4,0) \\
E(1,0) & E(2,1) & E(3,2) & E(4,1) & \\
E(2,2) & E(3,1) & E(4,2) & & \\
E(3,0) & E(4,3) & & & \\
E(4,4) & & & &
\end{array}
$$

That is:

$$
\begin{aligned}
& 1\quad 1\quad 0\quad 2\quad 0\\
& 0\quad 1\quad 2\quad 2\\
& 1\quad 1\quad 4\\
& 0\quad 5\\
& 5
\end{aligned}
$$

## Zigzag permutations

A zigzag permutation is a permutation $c_1$ to $c_i$ of $1$ to $n$ such that no element $c_i$ lies between $c_{i-1}$ and $c_{i+1}$ in value.

The numbers of zigzag permutations $Z_n$ ([OEIS A001250](http://oeis.org/A001250)), starting from $n=0$, are:

$$
1, 1, 2, 4, 10, 32, 122, 544, \cdots
$$

For example, the alternating permutations for the first few $n$ are:

$$
\begin{aligned}
n=1: & \{1\}\\
n=2: & \{1,2\}, \{2,1\}\\
n=3: & \{1,3,2\}, \{2,1,3\}, \{2,3,1\}, \{3,1,2\}\\
n=4: & \{1,3,2,4\}, \{1,4,2,3\}, \{2,1,4,3\}, \{2,3,1,4\}, \{2,4,1,3\}, \\
& \{3,1,4,2\}, \{3,2,4,1\}, \{3,4,1,2\}, \{4,1,3,2\}, \{4,2,3,1\}
\end{aligned}
$$

## Alternating permutations and zigzag numbers

(Do not confuse this concept with "derangements".)

For $n$ greater than $1$, reversing a zigzag permutation gives another zigzag permutation, so they can be paired up, and their number must be even.

Here is another way to pair them: split the zigzag permutations into alternating permutations and reverse alternating permutations.

In an alternating permutation, the first element is larger than the second, and the order relations are:

$$
c_1>c_2<c_3>\cdots
$$

In a reverse alternating permutation, the first element is smaller than the second, and the order relations are:

$$
c_1<c_2>c_3<\cdots
$$

If we swap the positions of $1$ and $n$, of $2$ and $n-1$, and so on, the set of alternating permutations and the set of reverse alternating permutations map onto each other. So the numbers of alternating and reverse alternating permutations are equal, each exactly half the number of zigzag permutations.

For $n$ greater than $1$, let:

$$
A_n=\frac{Z_n}{2}
$$

Define the initial values:

$$
A_0=A_1=1
$$

Here $A_n$ is called the zigzag number (Euler zigzag number, [OEIS A000111](http://oeis.org/A000111)). Starting from $n=0$, they are:

$$
1, 1, 1, 2, 5, 16, 61, 272, \cdots
$$

Next, let us try to find $A_n$.

There are $\dbinom{n}{k}$ ways to choose a subset of $k$ numbers from $1$ to $n$.

Within this $k$-element subset, there are $A_k$ ways to choose a reverse alternating permutation $u$. Removing this $k$-element subset from the whole set leaves an $(n-k)$-element subset, in which there are $A_{n-k}$ ways to choose a reverse alternating permutation $v$.

Consider the permutation $w$ of $n+1$ elements formed by $u$ reversed, followed by $n+1$, followed by $v$. Then $w$ must be a zigzag permutation. Moreover, any zigzag permutation of $n+1$ elements can be cut at $n+1$ to get the matching reverse alternating permutations $u$ and $v$, and different zigzag permutations of $n+1$ elements give different pairs $u$ and $v$.

So we get the recurrence:

$$
2A_{n+1}=\sum_{k=0}^n \dbinom{n}{k} A_k A_{n-k}
$$

$$
2(n+1)\frac{A_{n+1}}{(n+1)!}=\sum_{k=0}^n \frac{A_k}{k!}\frac{A_{n-k}}{(n-k)!}
$$

This recurrence does not hold when $n$ is $0$; the initial values $A_0$ and $A_1$ are both $1$.

We can see that this is a convolution of exponential generating functions. If $y$ is the exponential generating function of $A_n$, we get the differential equation:

$$
2\frac{\mathrm{d}y}{\mathrm{d}x}=y^2+1
$$

The $1$ added on the right-hand side handles the special case when $n$ is $0$. The general solution of this equation is:

$$
y=\tan\left(\frac{1}{2}x+C\right)
$$

Plugging in that the $0$-th term is $1$ gives the particular solution:

$$
y=\tan x+\sec x
$$

Tangent is an odd function and secant is an even function, and their sum is the generating function of the zigzag numbers.

## Relation between Entringer numbers and zigzag numbers

By definition, the Entringer number $E(n,k)$ is the number of alternating permutations of $0$ to $n$ whose first element is $k$. So the Entringer numbers and zigzag numbers are related by:

$$
A_n=E(n,n)
$$

There is also a reason to call $A_n$ "zigzag numbers": let $E_n$ be the Euler numbers and $B_n$ the Bernoulli numbers.

When $n$ is even, the zigzag numbers with even index are also called "secant numbers" $S_n$ or "zig numbers". They satisfy:

$$
A_n=(-1)^{n/2}E_n
$$

The first few are ([OEIS A000364](http://oeis.org/A000364)):

$$
1, 1, 5, 61, 1385, \cdots
$$

When $n$ is odd, the zigzag numbers with odd index are also called "tangent numbers" $T_n$ or "zag numbers". They satisfy:

$$
A_n=\frac{(-1)^{(n-1)/2}2^{n+1}(2^{n+1}-1)B_{n+1}}{n+1}
$$

The first few are ([OEIS A000182](http://oeis.org/A000182)):

$$
1, 2, 16, 272, 7936, \cdots
$$

So the Taylor expansions at $x=0$ give the secant numbers and tangent numbers:

$$
\sec x=A_0+A_2\frac{x^2}{2!}+A_4\frac{x^4}{4!}+\cdots
$$

$$
\tan x=A_1x+A_3\frac{x^3}{3!}+A_5\frac{x^5}{5!}+\cdots
$$

Or, written together:

$$
\sec x+\tan x=A_0+A_1x+A_2\frac{x^2}{2!}+A_3\frac{x^3}{3!}+A_4\frac{x^4}{4!}+A_5\frac{x^5}{5!}+\cdots
$$

This is the generating function of the zigzag numbers.

## References and links

1.  [Alternating permutation - Wikipedia](https://en.wikipedia.org/wiki/Alternating_permutation)
