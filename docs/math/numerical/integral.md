author: H-J-Granger, Chrogeek, countercurrent-time, Enter-tainer, Great-designer, iamtwz, Ir1d, ksyx, mao1t, Menci, NachtgeistW, Nanarikom, ShaoChenHeng, StudyingFather, SukkaW, Tiphereth-A, zyj-111

## Definition of the definite integral

Simply put, the definite integral $\int_{l}^{r}f(x)\mathrm{d}x$ of a function $f(x)$ over the interval $[l,r]$ is the area of the region between $f(x)$ and the $x$-axis over $[l,r]$ (area above the $x$-axis counts as positive, and area below it counts as negative).

In many cases we need to compute an approximate value of an integral efficiently and accurately. **Simpson's rule**, introduced below, is one such method of numerical integration.

## Simpson's rule

The idea is to split the integration interval into many small pieces and apply the integral formula for quadratic functions to each piece.

??? note "Integral formula for quadratics (Simpson's formula)"
    For a quadratic function $f(x)=ax^2+bx+c$, we have:
    
    $$
    \int_l^r f(x) {\mathrm d}x = \frac{(r-l)(f(l)+f(r)+4 f(\frac{l+r}{2}))}{6}
    $$
    
    Derivation:
    Take a quadratic function $f(x)=ax^2+bx+c$;
    integrating gives $F(x)=\int_0^x f(x) {\mathrm d}x = \frac{a}{3}x^3+\frac{b}{2}x^2+cx+D$, where D is a constant. Then
    
    $$
    \begin{aligned}
    \int_l^r f(x) {\mathrm d}x &= F(r)-F(l) \\
    &= \frac{a}{3}(r^3-l^3)+\frac{b}{2}(r^2-l^2)+c(r-l) \\
    &=(r-l)(\frac{a}{3}(l^2+r^2+lr)+\frac{b}{2}(l+r)+c) \\
    &=\frac{r-l}{6}(2al^2+2ar^2+2alr+3bl+3br+6c)\\
    &=\frac{r-l}{6}((al^2+bl+c)+(ar^2+br+c)+4(a(\frac{l+r}{2})^2+b(\frac{l+r}{2})+c)) \\
    &=\frac{r-l}{6}(f(l)+f(r)+4f(\frac{l+r}{2}))
    \end{aligned}
    $$

Based on Simpson's formula, we first introduce the ordinary Simpson integration method.

### Ordinary Simpson's rule

This method was published in a paper by Thomas Simpson in 1743.

#### Description

Given a natural number $n$, split the interval $[l, r]$ into $2n$ subintervals of equal length, with points $x$:

$x_i = l + i h, ~~ i = 0 \ldots 2n,$ $h = \frac {r-l} {2n}.$

We can then compute the integral over each small interval $[x_ {2i-2}, x_ {2i}]$, $i = 1\ldots n$, and add them all up to get the total integral.

For an interval $[x_ {2i-2}, x_ {2i}]$, $i = 1\ldots n$, the three points $(x_ {2i-2}, x_ {2i-1}, x_ {2i})$ determine a parabola, giving a function $P(x)$. This function exists and is unique. Computing the integral of the original function over this interval becomes computing the integral of the new quadratic $P(x)$ over it, which we can approximate with Simpson's formula.

$\int_{x_ {2i-2}} ^ {x_ {2i}} f (x) ~dx \approx \int_{x_ {2i-2}} ^ {x_ {2i}} P (x) ~dx = \left(f(x_{2i-2}) + 4f(x_{2i-1})+(f(x_{2i})\right)\frac {h} {3}$

Summing over all pieces gives:

$\int_l ^ r f (x) dx \approx \left(f (x_0) + 4 f (x_1) + 2 f (x_2) + 4f(x_3) + 2 f(x_4) + \ldots + 4 f(x_{2N-1}) + f(x_{2N}) \right)\frac {h} {3}$

#### Error

We state the result directly. The error of ordinary Simpson's rule is:

$$
-\tfrac{1}{90} \left(\tfrac{r-l}{2}\right)^5 f^{(4)}(\xi)
$$

where $\xi$ is some value in the interval $[l,r]$.

#### Implementation

=== "C++"
    ```cpp
    constexpr int N = 1000 * 1000;
    
    double simpson_integration(double a, double b) {
      double h = (b - a) / N;
      double s = f(a) + f(b);
      for (int i = 1; i <= N - 1; ++i) {
        double x = a + h * i;
        s += f(x) * ((i & 1) ? 4 : 2);
      }
      s *= h / 3;
      return s;
    }
    ```

=== "Python"
    ```python
    N = 1000 * 1000
    
    
    def simpson_integration(a, b):
        h = (b - a) / N
        s = f(a) + f(b)
        for i in range(1, N):
            x = a + h * i
            if i & 1:
                s = s + f(x) * 4
            else:
                s = s + f(x) * 2
        s = s * (h / 3)
        return s
    ```

### Adaptive Simpson's rule

To keep the ordinary method accurate, the running time is clearly limited by $n$. We should look for a better method.

The only real question is how to split the interval. With too few pieces, the error is large; with too many, it is slow. We need a balance between accuracy and efficiency.

Think about it this way: if some part of the graph is already very close to a quadratic, plugging it straight into the formula gives a very accurate value, so there is no need to split that part any further.

This gives the following way of splitting: each time, check how similar the current piece is to a quadratic. If it is similar enough, compute it directly with the formula. Otherwise, split the current piece into a left half and a right half and solve each recursively.

That leaves one question: how do we check whether a piece is similar to a quadratic?

Plug the current piece straight into the formula to get its integral. Then split the piece at its midpoint into two halves and plug each half into the formula. If the integral of the whole piece is very close to the sum of the integrals of the two halves, we can consider the piece close to a quadratic and stop splitting it.

That is the idea of adaptive Simpson's rule. When making the divide-and-conquer decision, besides checking whether the precision is good enough, you usually also force a minimum number of iterations.

Reference code:

=== "C++"
    ```cpp
    double simpson(double l, double r) {
      double mid = (l + r) / 2;
      return (r - l) * (f(l) + 4 * f(mid) + f(r)) / 6;  // Simpson's formula
    }
    
    double asr(double l, double r, double eps, double ans, int step) {
      double mid = (l + r) / 2;
      double fl = simpson(l, mid), fr = simpson(mid, r);
      if (abs(fl + fr - ans) <= 15 * eps && step < 0)
        return fl + fr + (fl + fr - ans) / 15;  // similar enough: return directly
      return asr(l, mid, eps / 2, fl, step - 1) +
             asr(mid, r, eps / 2, fr, step - 1);  // otherwise split in two and recurse
    }
    
    double calc(double l, double r, double eps) {
      return asr(l, r, eps, simpson(l, r), 12);
    }
    ```

=== "Python"
    ```python
    def simpson(l, r):
        mid = (l + r) / 2
        return (r - l) * (f(l) + 4 * f(mid) + f(r)) / 6  # Simpson's formula
    
    
    def asr(l, r, eps, ans, step):
        mid = (l + r) / 2
        fl = simpson(l, mid)
        fr = simpson(mid, r)
        if abs(fl + fr - ans) <= 15 * eps and step < 0:
            return fl + fr + (fl + fr - ans) / 15  # similar enough: return directly
        return asr(l, mid, eps / 2, fl, step - 1) + asr(
            mid, r, eps / 2, fr, step - 1
        )  # otherwise split in two and recurse
    
    
    def calc(l, r, eps):
        return asr(l, r, eps, simpson(l, r), 12)
    ```

## Exercises

-   [Luogu4525 [Template] Adaptive Simpson's Rule 1](https://www.luogu.com.cn/problem/P4525)
-   [HDU1724 Ellipse](https://acm.hdu.edu.cn/showproblem.php?pid=1724)
-   [NOI2005 Lemon Tree Under the Moon](https://www.luogu.com.cn/problem/P4207)

## References

<https://doi.org/10.1145/321526.321537>: this paper discusses an improvement to adaptive Simpson's rule and explains in detail where the constant `15` in the code above comes from and why it helps.
