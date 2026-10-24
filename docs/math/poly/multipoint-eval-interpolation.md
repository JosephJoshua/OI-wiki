## Multipoint evaluation of a polynomial

### Problem

Given a polynomial $f\left(x\right)$ and $n$ points $x_{1},x_{2},\dots,x_{n}$, compute

$$
f\left(x_{1}\right),f\left(x_{2}\right),\dots,f\left(x_{n}\right)
$$

### Solution

We use divide and conquer to cut the problem size in half.

Split the given points into two parts:

$$
\begin{aligned}
    X_{0}&=\left\{x_{1},x_{2},\dots,x_{\left\lfloor\frac{n}{2}\right\rfloor}\right\}\\
    X_{1}&=\left\{x_{\left\lfloor\frac{n}{2}\right\rfloor+1},x_{\left\lfloor\frac{n}{2}\right\rfloor+2},\dots,x_{n}\right\}
\end{aligned}
$$

Build the polynomial

$$
g_{0}\left(x\right)=\prod_{x_{i}\in X_{0}}\left(x-x_{i}\right)
$$

Then $\forall x\in X_{0}:g_{0}\left(x\right)=0$.

Write $f\left(x\right)$ in the form $g_{0}\left(x\right)Q\left(x\right)+f_{0}\left(x\right)$, that is:

$$
f_{0}\left(x\right)\equiv f\left(x\right)\pmod{g_{0}\left(x\right)}
$$

Then $\forall x\in X_{0}:f\left(x\right)=g_{0}\left(x\right)Q\left(x\right)+f_{0}\left(x\right)=f_{0}\left(x\right)$, and the same holds for $X_{1}$.

Now the problem size is halved, so it can be solved with divide and conquer plus polynomial modulo.

The time complexity is

$$
T\left(n\right)=2T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log^{2}{n}\right)
$$

## Fast polynomial interpolation

### Problem

Given a set of $n+1$ points

$$
X=\left\{\left(x_{0},y_{0}\right),\left(x_{1},y_{1}\right),\dots,\left(x_{n},y_{n}\right)\right\}
$$

find a polynomial $f\left(x\right)$ of degree $n$ such that $\forall\left(x,y\right)\in X:f\left(x\right)=y$.

### Solution

Consider the Lagrange interpolation formula

$$
f(x) = \sum_{i=1}^{n} \prod_{j\neq i }\frac{x-x_j}{x_i-x_j} y_i
$$

Let $M(x) = \prod_{i=1}^n (x - x_i)$. By L'Hôpital's rule,

$$
\prod_{j\neq i} (x_i - x_j) = \lim_{x\rightarrow x_i} \frac{\prod_{j=1}^n (x - x_j)}{x - x_i} = M'(x_i)
$$

So the polynomial can be written as

$$
f(x) = \sum_{i = 1}^n \frac{y_i}{M'(x_i)}\prod_{j \neq i}(x - x_j)
$$

We first compute the coefficients of $M(x)$ with divide and conquer. Then we can compute all the $M'(x_i)$ in $O(n\log^2 n)$ time with multipoint evaluation.

Let $v_i = \frac{y_i}{M'(x_i)}$. Next we compute $f(x)$. When $n = 1$, we have $f(x) = v_1, M(x) = x - x_1$. Otherwise, let

$$
\begin{aligned}
f_0(x) & = \sum_{i = 1}^{\left\lfloor \frac n2 \right \rfloor} v_i\prod_{j \neq i \wedge j \le \left\lfloor \frac n2 \right \rfloor}(x - x_j)\\
M_0(x) & = \prod_{i = 1}^{\left\lfloor \frac n2 \right \rfloor} (x - x_i)\\
f_1(x) & = \sum_{i = \left\lfloor \frac n2 \right \rfloor+1}^n v_i\prod_{j \neq i \wedge \left\lfloor \frac n2 \right \rfloor < j \le n}(x - x_j) \\
M_1(x) & = \prod_{i = \left\lfloor \frac n2 \right \rfloor+1}^n (x - x_i)
\end{aligned}
$$

Then $f(x) = f_0(x)M_1(x) + f_1(x)M_0(x), M(x) = M_0(x)M_1(x)$, so this can also be computed with divide and conquer. This part also takes $O(n\log^2 n)$ time.
