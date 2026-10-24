This article discusses how to solve linear congruences.

## Basic concepts

Let $a,b,n$ be integers and $x$ the unknown. An equation of the form

$$
ax\equiv b\pmod n
$$

is called a **linear congruence equation**.

To solve a linear congruence, we need to find all solutions $x$ in the range $[0,n-1]$. Of course, adding or subtracting any multiple of $n$ to them still gives solutions. Modulo $n$, these are all the solutions of the equation.

The rest of this article introduces two ways to solve linear congruences, one using modular inverses and one using Diophantine equations. In the general case, both computing inverses and solving Diophantine equations rely on the [extended Euclidean algorithm](./gcd.md#extended-euclidean-algorithm), so the two approaches are really the same.

## Solving with inverses

First, consider the case where $a$ and $n$ are coprime, i.e., $\gcd(a,n)=1$. In this case, we can compute the [inverse](./inverse.md) $a^{-1}$ of $a$ and multiply both sides of the equation by $a^{-1}$, which gives the unique solution:

$$
x \equiv ba^{-1} \pmod n.
$$

Next, consider the case where $a$ and $n$ are not coprime, i.e., $\gcd(a,n)=d>1$. In this case, the equation may have no solution. For example, $2x\equiv 1\pmod 4$ has no solution. So there are two cases to consider:

-   When $d$ does not divide $b$, there is no solution. For any $x$, the left-hand side $ax$ is a multiple of $d$, but the right-hand side $b$ is not. So they cannot differ by a multiple of $n$, since every multiple of $n$ is also a multiple of $d$. Therefore, the equation has no solution.

-   When $d$ divides $b$, we can divide the parameters $a,b,n$ by $d$ to get a new equation:

    $$
    a'x \equiv b'\pmod{n'}.
    $$

    Here $\gcd(a',n')=1$, that is, $a'$ and $n'$ are coprime. This case has already been solved above, so we can find the smallest non-negative solution $x'$ by computing an inverse.

    Clearly, $x'$ is also a solution of the original equation. But it is not the only one. All solutions of the reduced equation are

    $$
    \{x' + kn' : k\in\mathbf Z\}.
    $$

    The ones that fall in the range $[0,n-1]$ are exactly all solutions of the original equation in $[0,n-1]$:

    $$
    x \equiv (x' + kn')\pmod{n},\quad k = 0, 1, \cdots, d-1.
    $$

Putting the two cases together, the **number of solutions** of a linear congruence is either $d=\gcd(a,n)$ or $0$.

## Solving with Diophantine equations

A linear congruence is equivalent to the [linear Diophantine equation in two variables](./bezouts.md#two-variables) $x,y$:

$$
ax + ny = b.
$$

From the discussion on the linked page, this equation has a solution if and only if $\gcd(a,n)\mid b$, and its general solution is

$$
\begin{aligned}
x &= x_0 + t\dfrac{n}{d},\\
y &= y_0 - t\dfrac{a}{d},
\end{aligned}
$$

where $d=\gcd(a,n)$ is their greatest common divisor and $t$ is any integer.

So the general solution of the linear congruence is

$$
x \equiv \left(x_0+t\dfrac{n}{d}\right)\pmod{n},\quad t\in\mathbf Z.
$$

Taking $x_0$ modulo $n/d$ gives the smallest (non-negative) integer solution of the congruence, which is the $x'$ above.

## Reference implementation

The reference implementation in this section finds the smallest non-negative integer solution of the congruence. If no solution exists, it outputs $-1$.

???+ example "Reference implementation"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/linear-equation/linear-equation.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/linear-equation/linear-equation.py:core"
        ```

## Exercises

-   ["NOIP2012" Congruence Equation](https://loj.ac/problem/2605)

**This page is mainly translated from the article [Модульное линейное уравнение первого порядка](http://e-maxx.ru/algo/diofant_1_equation) and its English version [Linear Congruence Equation](https://cp-algorithms.com/algebra/linear_congruence_equation.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0. The content has been modified.**
