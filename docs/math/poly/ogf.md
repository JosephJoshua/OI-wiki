author: sshwy

The ordinary generating function (OGF) of a sequence $a$ is defined as the formal power series:

$$
F(x)=\sum_{n}a_n x^n
$$

$a$ can be either a finite or an infinite sequence. Some common examples (assuming $a$ starts at index $0$):

1.  The ordinary generating function of the sequence $a=\langle 1,2,3\rangle$ is $1+2x+3x^2$.
2.  The ordinary generating function of the sequence $a=\langle 1,1,1,\cdots\rangle$ is $\sum_{n\ge 0}x^n$.
3.  The generating function of the sequence $a=\langle 1,2,4,8,16,\cdots\rangle$ is $\sum_{n\ge 0}2^nx^n$.
4.  The generating function of the sequence $a=\langle 1,3,5,7,9,\cdots\rangle$ is $\sum_{n\ge 0}(2n+1)x^n$.

In other words, if the sequence $a$ has a closed formula for its general term, then the coefficients of its ordinary generating function are given by that formula.

## Basic operations

Consider the ordinary generating functions $F(x),G(x)$ of two sequences $a,b$. Then

$$
F(x)\pm G(x)=\sum_n (a_n\pm b_n)x^n
$$

So $F(x)\pm G(x)$ is the ordinary generating function of the sequence $\langle a_n\pm b_n\rangle$.

Now consider multiplication, i.e. convolution:

$$
F(x)G(x)=\sum_n x^n \sum_{i=0}^na_ib_{n-i}
$$

So $F(x)G(x)$ is the ordinary generating function of the sequence $\langle \sum_{i=0}^n a_ib_{n-i} \rangle$.

## Closed form

When working with generating functions, we do not always keep them as formal power series. At the right moments we convert them to closed form, which makes simplification easier.

For example, for the ordinary generating function $F(x)=\sum_{n\ge 0}x^n$ of $\langle 1,1,1,\cdots\rangle$, we notice that

$$
F(x)x+1=F(x)
$$

Solving this equation gives

$$
F(x)=\frac{1}{1-x}
$$

This is the closed form of $\sum_{n\ge 0}x^n$.

For the generating function $F(x)=\sum_{n\ge 0}p^nx^n$ of the geometric sequence $\langle 1,p,p^2,p^3,p^4,\cdots\rangle$, we have

$$
\begin{aligned}F(x)px+1 &=F(x)\\F(x) &=\frac{1}{1-px}\end{aligned}
$$

Switching between the closed form and the expanded form of a geometric sequence is a commonly used transformation.

???+ note "Quick exercises"
    Find the ordinary generating functions of the following sequences (both as a formal power series and in closed form). They get gradually harder.
    
    1.  $a=\langle 0,1,1,1,1,\cdots\rangle$.
    2.  $a=\langle 1,0,1,0,1,\cdots \rangle$.
    3.  $a=\langle 1,2,3,4,\cdots \rangle$.
    4.  $a_n=\binom{m}{n}$ ($m$ is a constant, $n\ge 0$).
    5.  $a_n=\binom{m+n}{n}$ ($m$ is a constant, $n\ge 0$).

??? note "Answers"
    First:
    
    $$
    F(x)=\sum_{n\ge 1}x^n=\dfrac{x}{1-x}
    $$
    
    Second:
    
    $$
    \begin{aligned}
    F(x)&=\sum_{n\ge 0}x^{2n}\\
    &=\sum_{n\ge 0}(x^2)^{n}\\
    &=\frac{1}{1-x^2}
    \end{aligned}
    $$
    
    Third (by differentiation):
    
    $$
    \begin{aligned}F(x)&=\sum_{n\ge 0}(n+1)x^n\\&=\sum_{n\ge 1}nx^{n-1}\\&=\sum_{n\ge 0}(x^n)'\\&=\left(\frac{1}{1-x}\right)'\\&=\frac{1}{(1-x)^2}\end{aligned}
    $$
    
    Fourth (binomial theorem):
    
    $$
    F(x)=\sum_{n\ge 0}\binom{m}{n}x^n=(1+x)^m
    $$
    
    Fifth:
    
    $$
    F(x)=\sum_{n\ge 0}\binom{m+n}{n}x^n=\frac{1}{(1-x)^{m+1}}
    $$
    
    This can be proved by induction.
    
    First, when $m=0$, $F(x)=\dfrac{1}{1-x}$.
    
    When $m>0$,
    
    $$
    \begin{aligned}
    \frac{1}{(1-x)^{m+1}}
    &=\frac{1}{(1-x)^m}\frac{1}{1-x}\\
    &=\left(\sum_{n\ge 0}\binom{m+n-1}{n}x^n \right)\left(\sum_{n\ge 0}x^n \right)\\
    &=\sum_{n\ge 0} x^n\sum_{i=0}^n \binom{m+i-1}{i}\\
    &=\sum_{n\ge 0}\binom{m+n}{n}x^n
    \end{aligned}
    $$

## Generating function of the Fibonacci sequence

Next we derive the generating function of the Fibonacci sequence.

The Fibonacci sequence is defined by $a_0=0,a_1=1,a_n=a_{n-1}+a_{n-2}\;(n>1)$. Let its ordinary generating function be $F(x)$. From the recurrence, we can similarly write an equation in $F(x)$:

$$
F(x)=xF(x)+x^2F(x)-a_0x+a_1x+a_0
$$

Solving it gives

$$
F(x)=\frac{x}{1-x-x^2}
$$

The next question is: how do we find its expanded form?

### Expansion method 1

Treat $x+x^2$ as a single unit. Then we get

$$
\begin{aligned}
F(x) &= \dfrac{x}{1-(x+x^2)} \\
&= x\sum_{k=0}^{\infty}(x+x^2)^k \\
&= x\sum_{k=0}^{\infty}\sum_{i=0}^k\binom{k}{i}x^{k-i}(x^2)^i \\
&= \sum_{k=0}^{\infty}\sum_{i=0}^k\binom{k}{i}x^{k+i+1} \\
&= \sum_{n=1}^{\infty}\sum_{i=0}^{\lfloor(n-1)/2\rfloor}\binom{n-i-1}{i}x^n.
\end{aligned}
$$

In the last step, we let $n=k+i+1$ and swap the order of summation. This gives the formula for the general term:

$$
a_n = \sum_{i=0}^{\lfloor(n-1)/2\rfloor}\binom{n-i-1}{i}.
$$

This is not the familiar form involving the golden ratio.

### Expansion method 2

Solve an equation with undetermined coefficients:

$$
\frac{A}{1-ax}+\frac{B}{1-bx}= \frac{x}{1-x-x^2}
$$

Putting the left side over a common denominator gives

$$
\frac{A-Abx+B-aBx}{(1-ax)(1-bx)} = \frac{x}{1-x-x^2}
$$

Matching coefficients, we get

$$
\begin{cases}
A+B=0\\
-Ab-aB=1\\
a+b=1\\
ab=-1
\end{cases}
$$

Solving gives

$$
\begin{cases}
A=\frac{1}{\sqrt{5}}\\
B=-\frac{1}{\sqrt{5}}\\
a=\frac{1+\sqrt{5}}{2}\\
b=\frac{1-\sqrt{5}}{2}
\end{cases}
$$

Then, using the expansion of a geometric series, we get the formula for the general term of the Fibonacci sequence:

$$
\frac{x}{1-x-x^2}=\sum_{n\ge 0}x^n
\frac{1}{\sqrt{5}}\left( \left(\frac{1+\sqrt{5}}{2}\right)^n-\left(\frac{1-\sqrt{5}}{2}\right)^n \right)
$$

This is also called another closed form of the Fibonacci sequence ($\frac{x}{1-x-x^2}$ is a closed form).

For any polynomials $P(x),Q(x)$, the expansion of the generating function $\dfrac{P(x)}{Q(x)}$ can be found with the method above. In practice, we usually first find the roots of $Q(x)$, write the denominator in the form $\prod (1-p_ix)^{d_i}$, and then work out the numerators.

When the factored denominator has repeated roots, each extra repetition of a root needs one more fraction. For example, to find the formula for the coefficients of the generating function

$$
G(x)=\frac{1}{(1-x)(1-2x)^2}
$$

we write

$$
G(x)=\frac{c_0}{1-x}+\frac{c_1}{1-2x}+\frac{c_2}{(1-2x)^2}
$$

Solving gives

$$
\begin{cases}
c_0&=1\\
c_1&=-2\\
c_2&=2
\end{cases}
$$

So

$$
[x^n]G(x)=1-2^{n+1}+(n+1)\cdot 2^{n+1}
$$

## Newton's binomial theorem

We redefine the binomial coefficient:

$$
\binom{r}{k}=\frac{r^{\underline{k}}}{k!}\quad(r\in\mathbf{C},k\in\mathbf{N})
$$

Note that $r$ ranges over the complex numbers. In this setting, for $\alpha\in\mathbf{C}$,

$$
(1+x)^{\alpha}=\sum_{n\ge 0}\binom{\alpha}{n}x^n
$$

The binomial theorem is in fact a special case of Newton's binomial theorem.

## Generating function of the Catalan numbers

See [the algebraic derivation of the Catalan numbers](../combinatorics/catalan.md#代数推演).

## Applications

Next are some example problems that show how generating functions are used in OI.

### Food

???+ note "[Food](https://hydro.ac/p/bzoj-P3028)"
    Choose $n$ items from many different kinds of food. The limits for each kind are:
    
    1.  Chengde hamburgers: an even number
    2.  Cola: 0 or 1
    3.  Chicken drumsticks: 0, 1 or 2
    4.  Mitaoduo (a peach drink): an odd number
    5.  Chicken nuggets: a multiple of 4
    6.  Steamed buns: 0, 1, 2 or 3
    7.  Stir-fried potato slices with pork: at most one
    8.  Bread: a multiple of 3
    
    Every kind of food is counted in whole items, and any choice whose total is $n$ counts as one way. For the given $n$, compute the number of ways modulo $10007$.

This is a classic generating function problem. For one kind of food, let $a_n$ be the number of ways to choose $n$ items of that food, and find its generating function. The generating function for the number of ways to choose $n$ items in total from two kinds of food is the convolution of their generating functions. The same holds for many kinds of food: the generating function is the convolution of all their generating functions.

Once we see that the number of ways can be expressed as a convolution, we can build the generating functions (numbered as the foods in the problem):

1.  $\displaystyle\sum_{n\ge 0}x^{2n}=\dfrac{1}{1-x^2}$.
2.  $1+x$.
3.  $1+x+x^2=\dfrac{1-x^3}{1-x}$.
4.  $\dfrac{x}{1-x^2}$.
5.  $\displaystyle \sum_{n\ge 0}x^{4n}=\dfrac{1}{1-x^4}$.
6.  $1+x+x^2+x^3=\dfrac{1-x^4}{1-x}$.
7.  $1+x$.
8.  $\dfrac{1}{1-x^3}$.

Multiplying them all together gives the generating function of the answer:

$$
F(x)=\frac{(1+x)(1-x^3)x(1-x^4)(1+x)}{(1-x^2)(1-x)(1-x^2)(1-x^4)(1-x)(1-x^3)}
=\frac{x}{(1-x)^4}
$$

Then convert it to expanded form (using the fifth closed-form exercise):

$$
F(x)=\sum_{n\ge 1}\binom{n+2}{n-1}x^n
$$

So the answer is $\dbinom{n+2}{n-1}=\dbinom{n+2}{3}$.

### Sweet

???+ note "[CEOI 2004 Sweet](https://hydro.ac/p/bzoj-P3027)"
    There are $n$ piles of candy. Different piles hold different kinds of candy (all candies in one pile are the same kind, and candies in different piles are different kinds). Pile $i$ has $m_i$ candies. You want to eat at least $a$ candies but no more than $b$. Count the number of ways.
    
    Two ways are different if and only if the number of candies eaten is different, or for some kind of candy, the number eaten of that kind is different in the two ways.
    
    $n\le 10,0\le a\le b\le 10^7,m_i\le 10^6$.

The generating function for the number of ways to eat $j$ candies from pile $i$ (clearly 1 way) is

$$
F_i(x)=\sum_{j=0}^{m_i}x^j=\frac{1-x^{m_i+1}}{1-x}
$$

So the generating function for the number of ways to eat $i$ candies in total is

$$
G(x)=\prod_{i=1}^n F_i(x)=(1-x)^{-n}\prod_{i=1}^n(1-x^{m_i+1})
$$

Now we want $\sum_{i=a}^b[x^i]G(x)$.

Since $n\le 10$, we can expand $\prod_{i=1}^n(1-x^{m_i+1})$ by brute force (it has at most $2^n$ terms).

Then apply Newton's binomial theorem to $(1-x)^{-n}$:

$$
\begin{aligned}
(1-x)^{-n}
&=\sum_{i\ge 0}\binom{-n}{i}(-x)^i\\
&=\sum_{i\ge 0}\binom{n-1+i}{i}x^i
\end{aligned}
$$

We enumerate the coefficient of each $x^k$ term in $\prod_{i=1}^n(1-x^{m_i+1})$; call it $c_k$. After multiplying it by $(1-x)^{-n}$, its contribution to the answer is

$$
c_k\sum_{i=a-k}^{b-k}\binom{n-1+i}{i}=c_k\left(
\binom{n+b-k}{b-k}-
\binom{n+a-k-1}{a-k-1}
\right)
$$

This way the answer can be computed in $O(b)$.

The time complexity is $O(2^n+b)$.
