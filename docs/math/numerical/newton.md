author: Marcythm, iamtwz, nutshellfool, sshwy, allenanswerzq, countercurrent-time, Enter-tainer, H-J-Granger, hly1204, Ir1d, Menci, NachtgeistW, SukkaW, Tiphereth-A, Xeonacid

## Introduction

This article shows how to find approximate solutions of equations with Newton's method for finding roots. The method was introduced by Newton in the 17th century.

The task is: given a function $f(x)$ that is continuous and monotonic on $[a,b]$, find an approximate solution of the equation $f(x)=0$.

## Explanation

We start from the given $f(x)$ and an initial approximation $x_0$ (the choice of starting value is related to the Newton fractal; see 3Blue1Brown's video on [Newton's fractal](https://www.bilibili.com/video/BV1HQ4y1q78v)).

Suppose our current approximation is $x_i$. Draw the line $l$ tangent to $f(x)$ at the point $(x_i,f(x_i))$, and let $x_{i+1}$ be the x-coordinate where $l$ crosses the $x$-axis. This is a better approximation. Repeat this process.
From the geometric meaning of the derivative, we get:

$$
 f'(x_i) = \frac{f(x_i)}{x_{i} - x_{i+1}}
$$

Rearranging gives the recurrence:

$$
 x_{i+1} = x_i - \frac{f(x_i)}{f'(x_i)}
$$

Intuitively, if $f(x)$ is fairly smooth, then as the number of iterations grows, $x_i$ gets closer and closer to the solution of the equation.

Newton's method converges quadratically, which means the number of correct digits roughly doubles with each iteration.
For a proof of the convergence of Newton's method, see [citizendium - Newton method Convergence analysis](http://en.citizendium.org/wiki/Newton%27s_method#Convergence_analysis)

Of course, Newton's method also has weaknesses; for details see [Xiaolin Wu - Roots of Equations, analysis on pages 18 - 20](https://www.ece.mcmaster.ca/~xwu/part2.pdf)

## Square roots

Let us use Newton's method to compute square roots. Let $f(x)=x^2-n$. An approximate solution of this equation is an approximation of $\sqrt{n}$. This gives

$$
x_{i+1}=x_i-\frac{x_i^2-n}{2x_i}=\frac{x_i+\frac{n}{x_i}}{2}
$$

When implementing it, be careful to choose a suitable precision. The code is below.

### Implementation

=== "C++"
    ```cpp
    double sqrt_newton(double n) {
      constexpr static double eps = 1E-15;
      double x = 1;
      while (true) {
        double nx = (x + n / x) / 2;
        if (abs(x - nx) < eps) break;
        x = nx;
      }
      return x;
    }
    ```

=== "Python"
    ```python
    def sqrt_newton(n):
        eps = 1e-15
        x = 1
        while True:
            nx = (x + n / x) / 2
            if abs(x - nx) < eps:
                break
            x = nx
        return x
    ```

## Integer square roots

Although we could call the `sqrt()` function to get the square root, here we describe a variant of Newton's method that finds the largest integer solution of the inequality $x^2\le n$. We still use a process similar to Newton's method, but with a small change in the stopping condition. If the previous iteration made the approximation smaller and this iteration would make it larger, we skip this iteration and exit the loop.

### Implementation

=== "C++"
    ```cpp
    int isqrt_newton(int n) {
      int x = 1;
      bool decreased = false;
      for (;;) {
        int nx = (x + n / x) >> 1;
        if (x == nx || (nx > x && decreased)) break;
        decreased = nx < x;
        x = nx;
      }
      return x;
    }
    ```

=== "Python"
    ```python
    def isqrt_newton(n):
        x = 1
        decreased = False
        while True:
            nx = (x + n // x) // 2
            if x == nx or (nx > x and decreased):
                break
            decreased = nx < x
            x = nx
        return x
    ```

## Big-number square roots

Finally, consider Newton's method with big numbers. The iteration is the same, but this time we need to pay attention to the initial approximation, that is, the value of $x_0$. Numbers that need arbitrary precision are usually very large, so the initial value has a big effect on efficiency. A natural choice is $x_0=2^{\left\lfloor\frac{1}{2}\log_2n\right\rfloor}$, which is fast to compute and fairly close to the square root.

### Implementation

Here is a Java implementation:

```java
public static BigInteger isqrtNewton(BigInteger n) {
  BigInteger a = BigInteger.ONE.shiftLeft(n.bitLength() / 2);
  boolean p_dec = false;
  for (;;) {
    BigInteger b = n.divide(a).add(a).shiftRight(1);
    if (a.compareTo(b) == 0 || a.compareTo(b) < 0 && p_dec)
      break;
    p_dec = a.compareTo(b) > 0;
    a = b;
  }
  return a;
}
```

In practice: for $n=10^{1000}$ this algorithm runs in 60 ms. If we do not optimize $x_0$ and start from $x_0=1$, the running time goes up to 120 ms.

## Exercises

-   [UVa 10428 - The Roots](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1369)
-   [LeetCode 69. Sqrt(x)](https://leetcode-cn.com/problems/sqrtx/)

    **This page is mainly translated from the article [Метод Ньютона (касательных) для поиска корней](http://e-maxx.ru/algo/roots_newton) and its English translation [Newton's method for finding roots](https://cp-algorithms.com/num_methods/roots_newton.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**
