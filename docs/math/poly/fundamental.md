## Definition

Every polynomial equation in one variable of degree $n$ (with $n$ at least $1$) with complex coefficients has at least one root in the complex numbers.

It follows that a polynomial equation of degree $n$ with complex coefficients has exactly $n$ roots in the complex numbers, counting multiple roots with their multiplicity.

Sometimes the theorem is also stated as:

Every nonzero polynomial in one variable of degree $n$ with complex coefficients has exactly $n$ complex roots.

Proofs of the fundamental theorem of algebra usually need complex analysis or abstract algebra, so it is usually just used as a well-known result.

By the fundamental theorem of algebra, a polynomial with complex coefficients $f(x)=a_nx^n+a_{n-1}x^{n-1}+\ldots+a_0$ can always be uniquely factored as:

$$
f(x)=a_n{(x-x_1)}^{k_1}{(x-x_2)}^{k_2}\ldots{(x-x_t)}^{k_t}
$$

where all roots are complex numbers and $k_1+k_2+\ldots+k_t=n$.

## Conjugate root theorem

The fundamental theorem of algebra is about polynomials with complex coefficients. When studying polynomials with real coefficients, we can still factor out complex roots, but that requires enlarging the setting, which is inconvenient.

Imaginary root: a root that is not real.

Theorem: the complex conjugate of a root of a polynomial with real coefficients is also a root of that polynomial.

Proof: take the conjugate of both sides of the equation in the fundamental theorem of algebra.

If a root is real, its conjugate is itself, so nothing changes.

If a root is imaginary, its complex conjugate is also a root of the polynomial. So the imaginary roots can be paired up.

Theorem: conjugate imaginary roots of an equation with real coefficients always come in pairs, and conjugate roots have the same multiplicity.

Proof: suppose one root is $a+b\mathrm{i}$; then another root is $a-b\mathrm{i}$. This means the factorization contains two factors:

$$
(x-a-b\mathrm{i})(x-a+b\mathrm{i})=x^2-2ax+a^2+b^2
$$

Multiplying the two factors together makes all coefficients real. The real quadratic polynomial on the right side of this equation divides the original polynomial.

So in the equation of the fundamental theorem of algebra, divide both sides by this quadratic; the result is still an equation of polynomials with real coefficients. Repeat on the new equation; as the degree drops, after some steps there are no imaginary roots left.

So each pair of conjugate imaginary roots has equal multiplicity. This completes the proof.

Corollaries of the conjugate root theorem:

-   A polynomial of odd degree with real coefficients has at least one real root, and an odd number of real roots in total.
-   A polynomial of even degree with real coefficients may have no real roots, and has an even number of real roots in total.

The quadratic $x^2-2ax+a^2+b^2=x^2+px+q$ above is called an irreducible real quadratic factor. Irreducible means it cannot be factored over the real numbers.

Theorem: every polynomial with real coefficients is a product of linear factors and irreducible quadratic factors with real coefficients.

Proof:

Each real root $c$ of the polynomial corresponds to a real factor $x-c$; each pair of imaginary roots $a\pm b\mathrm{i}$ corresponds to a real factor $x^2-2ax+a^2+b^2$.

So it suffices to pair up the roots in the original factorization from the fundamental theorem of algebra using the conjugate root theorem. This completes the proof.

By the conjugate root theorem, a polynomial with real coefficients $f(x)=a_nx^n+a_{n-1}x^{n-1}+\ldots+a_0$ can always be uniquely factored as:

$$
f(x)=a_n{(x-x_1)}^{k_1}{(x-x_2)}^{k_2}\ldots{(x-x_t)}^{k_t}{(x^2+p_1x+q_1)}^{l_1}{(x^2+p_2x+q_2)}^{l_2}\ldots{(x^2+p_sx+q_s)}^{l_s}
$$

where all coefficients are real and $k_1+k_2+\ldots+k_t+2(l_1+l_2+\ldots+l_s)=n$.

## Lin's method

### Overview

How do we factor a polynomial with real coefficients as in the fundamental theorem of algebra? Extending the field to the complex numbers makes things complicated.

If we only factor over the real numbers, all we can guarantee is that when the degree is greater than $2$, there is always a real quadratic factor.

This is because if the polynomial has imaginary roots, we can just take a pair of conjugate imaginary roots. If the polynomial has only real roots, multiplying the linear factors of any two real roots also gives a real quadratic factor.

Once a quadratic factor is found, solving it for real or complex roots is very easy. This leads to a method that finds the complex roots of an equation by **finding one quadratic factor** at a time, which avoids complex arithmetic.

In August 1940, August 1943 and July 1947, Lin Shih-Nge formally published three papers in a row on methods for finding the complex roots of high-degree equations in the *Journal of Mathematics and Physics* published by MIT[^note1], improving the method each time.

This method is still used for fast computation on modern computers today, and polynomial root-finding routines in software packages (such as MATLAB) are based on the same idea.

### How it works

To find a quadratic factor, we want to factor the polynomial as:

$$
f(x)=(x^2+p_1x+q_1)g(x)
$$

Since we cannot find the quadratic factor right away, we solve iteratively. For the initial values we have:

$$
f(x)=(x^2+px+q)g(x)+rx+s
$$

This leaves a linear remainder. As long as the remainder is small enough, we have approximately found the factor we want.

We want the final solution to be the initial value plus a correction:

$$
p_1=p+dp
$$

$$
q_1=q+dq
$$

The two numbers $(r, s)$ in the remainder are determined by the given coefficients $(p, q)$ of the divisor. By partial derivatives:

$$
dr=\frac{\partial r}{\partial p}dp+\frac{\partial r}{\partial q}dq
$$

$$
ds=\frac{\partial s}{\partial p}dp+\frac{\partial s}{\partial q}dq
$$

In the initial equation, the dividend $f(x)$ is fixed, and the quotient $g(x)$ and the remainder $rx+s$ change as the divisor $x^2+px+q$ changes. So we have the partial derivative relations

$$
0=xg(x)+\frac{\partial g(x)}{\partial p}(x^2+px+q)+\frac{\partial r}{\partial p}x+\frac{\partial s}{\partial p}
$$

$$
0=g(x)+\frac{\partial g(x)}{\partial q}(x^2+px+q)+\frac{\partial r}{\partial q}x+\frac{\partial s}{\partial q}
$$

Note that the partial derivatives are just numbers and do not depend on the variable $x$. So we have the division relations

$$
xg(x)=-\frac{\partial g(x)}{\partial p}(x^2+px+q)-\frac{\partial r}{\partial p}x-\frac{\partial s}{\partial p}
$$

$$
g(x)=-\frac{\partial g(x)}{\partial q}(x^2+px+q)-\frac{\partial r}{\partial q}x-\frac{\partial s}{\partial q}
$$

The conclusion is that the partial derivatives we want are exactly the remainders of dividing the quotient again. Dividing a polynomial by a given quadratic is a direct computation. This gives all four partial derivatives.

We want $s$ and $r$ plus the corrections $ds$ and $dr$ to become $0$, that is, $ds$ and $dr$ are the negatives of $s$ and $r$. So we solve:

$$
-\frac{\partial r}{\partial p}dp-\frac{\partial r}{\partial q}dq=r
$$

$$
-\frac{\partial s}{\partial p}dp-\frac{\partial s}{\partial q}dq=s
$$

Solve this system for the corrections $dp$ and $dq$ of $p$ and $q$; a $2\times 2$ determinant (Cramer's rule) does it directly.

### Implementation

```C
// a is the original polynomial, n is its degree, p is the linear coefficient to find, q is the constant term to find
void Shie(double a[], int n, double *p, double *q) {
  // array b is the quotient of polynomial a divided by the current quadratic
  memset(b, 0, sizeof(b));
  // array c is the quotient of polynomial b times x squared, divided by the current quadratic
  memset(c, 0, sizeof(c));
  *p = 0;
  *q = 0;
  double dp = 1;
  double dq = 1;
  while (dp > eps || dp < -eps || dq > eps || dq < -eps)  // choose eps yourself
  {
    double p0 = p;
    double q0 = q;
    b[n - 2] = a[n];
    c[n - 2] = b[n - 2];
    b[n - 3] = a[n - 1] - p0 * b[n - 2];
    c[n - 3] = b[n - 3] - p0 * b[n - 2];
    int j;
    for (j = n - 4; j >= 0; j--) {
      b[j] = a[j + 2] - p0 * b[j + 1] - q0 * b[j + 2];
      c[j] = b[j] - p0 * c[j + 1] - q0 * c[j + 2];
    }
    double r = a[1] - p0 * b[0] - q0 * b[1];
    double s = a[0] - q0 * b[0];
    double rp = c[1];
    double sp = b[0] - q0 * c[2];
    double rq = c[0];
    double sq = -q0 * c[1];
    dp = (rp * s - r * sp) / (rp * sq - rq * sp);
    dq = (r * sq - rq * s) / (rp * sq - rq * sp);
    *p += dp;
    *q += dq;
  }
}
```

## References and notes

[^note1]: [Lin Shih-Nge. On the application of the factor-splitting method to finding the roots of high-order characteristic equations (in Chinese). Advances in Mathematics, 1963(03):207-217.](https://cnki.net/kcms/detail/detail.aspx?filename=SXJZ196303000&dbcode=CJFD&dbname=CJFD1979)
