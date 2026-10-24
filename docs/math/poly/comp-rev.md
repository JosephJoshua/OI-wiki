Composition and compositional inverse are also common operations on formal power series. For a general $f$ with no special properties, we have mostly used $O\left(n^2\right)$ algorithms (which still need FFT) to compute $f(g) \bmod{x^n}$, where $f\in\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack,g\in x\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack$, but because they are slow they are rarely used. Here we introduce the $O\left(\mathsf{M}\left(n\right)\log n\right)$ algorithm of Kinoshita–Li, where $O\left(\mathsf{M}\left(n\right)\right)$ is the time to multiply two polynomials of degree $O\left( n\right)$.

## Composition of formal power series / polynomials

To compute $f\left(g\left(x\right)\right)\bmod{x^n}$, every coefficient of $f\left(g\left(x\right)\right)$ must be a finite sum. That is why we previously required $f(x)\in\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack,g(x)\in x\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack$; the condition also holds if $f(x),g(x)\in\mathbb{C}\left\lbrack x\right\rbrack$. Since we truncate the coefficients of $f\left(g\left(x\right)\right)$ anyway, we may simply consider the case where both $f(x),g(x)$ are polynomials. For $f(x)=\sum_{j=0}^{n-1}f_jx^j$, we have

$$
f\left(g\left(x\right)\right)=\sum_{j=0}^{n-1}f_jg\left(x\right)^j
$$

Consider the rational function over the ring $\mathbb{C}\left\lbrack x\right\rbrack\left(\left( y\right)\right)$

$$
\begin{aligned}
\frac{f\left(y^{-1}\right)}{1-y\cdot g(x)}&=\sum_{j\geq 0}\left(\cdots +f_jy^{-j}+\cdots\right)g(x)^jy^j \\
f\left(g\left(x\right)\right)&=\left\lbrack y^0\right\rbrack\frac{f\left(y^{-1}\right)}{1-y\cdot g(x)}
\end{aligned}
$$

Kinoshita and Li pointed out that the Bostan–Mori algorithm from [linear recurrences with constant coefficients](./linear-recurrence.md) can be modified into a bivariate form:

$$
\begin{aligned}
\frac{P\left(y\right)}{Q\left(x,y\right)}\bmod{x^n}&=\left(\frac{P\left(y\right)}{Q\left(x,y\right)Q\left(-x,y\right)}\bmod{x^n}\right)Q\left(-x,y\right)\bmod{x^n} \\
&=\left(\frac{P(y)}{V(x^2,y)}\bmod{x^n}\right)Q\left(-x,y\right)\bmod{x^n} \\
&=\left.\left(\frac{P(y)}{V(z,y)}\bmod{z^{\left\lceil n/2\right\rceil}}\right)\right|_{z=x^2}Q\left(-x,y\right)\bmod{x^n}
\end{aligned}
$$

Computing this recursively, when $n=1$ we only need to compute

$$
\frac{P(y)}{Q(x,y)}\bmod{x}=\frac{P(y)}{Q(0,y)}\in\mathbb{C}\left(\left( y\right)\right)
$$

When computing $\dfrac{P(y)}{V(z,y)}\bmod{z^{\left\lceil n/2\right\rceil}}\in\mathbb{C}\left\lbrack z\right\rbrack\left(\left( y\right)\right)$, we do not need to keep all coefficients in $y$. In the end we only extract the coefficient of $y^0$, so the coefficients of $y^{>0}$ are not needed. After computing the former, we multiply it by several "**polynomials**" of the form $Q(-x,y)\in\mathbb{C}\left\lbrack x,y\right\rbrack$, so we only need to keep the coefficients that contribute to $y^0$. We are now ready to give the pseudocode:

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{Comp}}\left(P(y),Q(x,y),n,m\right)\text{:} \\
&\textbf{Input}\text{: }P=\sum_{0\leq j< n}p_jy^{-j}\in\mathbb{C}((y)),Q\in\mathbb{C}\left\lbrack x,y\right\rbrack ,n,m\in\mathbb{N}_{>0}\text{.} \\
&\textbf{Output}\text{: }\left\lbrack y^{\left(-m,0\right\rbrack}\right\rbrack\dfrac{P(y)}{Q(x,y)}\bmod{x^n}\text{.} \\
&\textbf{Require}\text{: }\left\lbrack x^0y^0\right\rbrack Q=1\text{.} \\
1&\textbf{if }n=1\textbf{ then return }\left(\left\lbrack y^{-m+1}\right\rbrack\frac{P(y)}{Q(0,y)},\dots ,\left\lbrack y^0\right\rbrack\frac{P(y)}{Q(0,y)}\right) \\
2&V(x^2,y)\gets Q(x,y)Q(-x,y)\bmod{x^n} \\
3&d\gets\deg_y Q\left(-x,y\right)\\
4&\left(t_{-(m+d)+1},\dots ,t_0\right)\gets \operatorname{\mathsf{Comp}}\left(P(y),V(x,y),\left\lceil n/2\right\rceil,m+d\right) \\
5&T(x,y)\gets \sum_{j=-(m+d)+1}^0t_jy^j \\
6&U(x,y)=\sum_{j=-(m+d)+1}^d u_jy^j\gets T(x^2,y)Q(-x,y)\bmod{x^n} \\
7&\textbf{return }\left(u_{-m+1},\dots ,u_0\right)
\end{array}
$$

Then we have

$$
f\left(g\left(x\right)\right)\bmod{x^n}=\operatorname{\mathsf{Comp}}\left(f\left(y^{-1}\right),1-y\cdot g(x),\max\left\lbrace 1+\deg f,n\right\rbrace ,1\right)\bmod{x^n}
$$

The third argument is chosen this way because $g(0)$ may be nonzero: if $\deg f\geq n$, we cannot truncate $f(x)$ before computing $f\left(g(x)\right)$. Alternatively, we can compute $f(g)=f\circ \left(x+g(0)\right)\circ \left(g-g(0)\right)$: take $F:=f\left(x+g(0)\right)\bmod{x^n}$ and $G:=g-g(0)$, and compute $\operatorname{\mathsf{Comp}}\left(F\left(y^{-1}\right),1-y\cdot G(x),n,1\right)$ instead.

Also, because of how the function is called, $Q(0,y)^{-1}$ at the base case of the recursion can be written down directly, so there is no need for the formal power series inverse algorithm; we only need one multiplication and then extract the needed coefficients.

## Common special compositions

The common [elementary functions of polynomials](./elementary-func.md) can all be computed as compositions:

$$
\begin{aligned}
g(0)=1&,\space g^{-1}=1+(1-g)+(1-g)^2+\cdots \\
g(0)=1&,\space \log g=-\dfrac{1-g}{1}-\dfrac{(1-g)^2}{2}-\dfrac{(1-g)^3}{3}-\cdots \\
g(0)=0&,\space \exp g=1+\dfrac{g}{1!}+\dfrac{g^2}{2!}+\dfrac{g^3}{3!}+\cdots \\
g(0)=1&,\space g^e=1+\dfrac{e}{1!}(g-1)+\dfrac{e(e-1)}{2!}(g-1)^2+\cdots
\end{aligned}
$$

Powers are also used when computing the compositional inverse.

### Kronecker substitution

Before analyzing the time complexity, let us consider how to multiply bivariate polynomials. One idea is to "pack" the coefficients. This method, due to Kronecker in 1882, uses $y\mapsto x^N$ to reduce multiplication in $R\left\lbrack x,y\right\rbrack$ to multiplication in $R\left\lbrack x\right\rbrack$, but it requires $N$ to be large enough.

Suppose $\deg_x \left(AB\right)<N$. Then after computing $A\left(x,x^N\right)B\left(x,x^N\right)$ we can still recover $A(x,y)B(x,y)$, and "packing" and "unpacking" take linear time.

So we use Kronecker substitution and then do univariate polynomial multiplication. It is not hard to see that when $n$ is a power of two, the algorithm above runs in $O\left(\mathsf{M}\left(n\right)\log n\right)$ time, because in each recursion step the degree in $y$ doubles but the degree in $x$ halves.

??? note "Template ([Luogu P5373 [Template] Polynomial Composition](https://www.luogu.com.cn/problem/P5373))"
    The code simplifies and modifies the original algorithm a bit to make it shorter.
    
    ```cpp
    --8<-- "docs/math/code/poly/comp-rev/comp_1.cpp"
    ```

## Compositional inverse of a formal power series

Given $f\in x\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack$ with $f'(0)\neq 0$, find $g(x)\bmod{x^n}$ such that $f(g)\equiv g(f)\equiv x\pmod{x^n}$.

By [Lagrange inversion](./lagrange-inversion.md), for $n>1,k\geq 0$ we have

$$
\left\lbrack x^{n-1}\right\rbrack f(x)^k=\frac{k}{n-1}\left\lbrack x^{n-1-k}\right\rbrack \left(\frac{g(x)}{x}\right)^{-(n-1)}
$$

That is, if we can compute $\left\lbrack x^{n-1}\right\rbrack f(x)^k$ for $k=0,1,\dots ,n-1$, we can recover the compositional inverse.

Kinoshita and Li pointed out that we can consider the bivariate rational function

$$
\frac{1}{1-y\cdot f(x)}=\sum_{j\geq 0}f(x)^jy^j
$$

This problem has a more general form, the Power Projection problem: compute

$$
u:=\left\lbrack x^{n-1}\right\rbrack\frac{P(x,y)}{Q(x,y)}\bmod{y^m}
$$

When $n-1=0$, clearly $u=\dfrac{P(0,y)}{Q(0,y)}\bmod{y^m}$. Otherwise we have

$$
\frac{P(x,y)}{Q(x,y)}=\frac{P(x,y)Q(-x,y)}{Q(x,y)Q(-x,y)}=\frac{U_e\left(x^2,y\right)+xU_o\left(x^2,y\right)}{V\left(x^2,y\right)}
$$

so

$$
\begin{aligned}
u&=\begin{cases}
\left\lbrack x^{n-1}\right\rbrack\dfrac{U_e\left(x^2,y\right)}{V\left(x^2,y\right)}&\text{ if }n-1\text{ is even,} \\
\left\lbrack x^{n-1}\right\rbrack\dfrac{xU_o\left(x^2,y\right)}{V\left(x^2,y\right)}&\text{ if }n-1\text{ is odd.}
\end{cases} \\
&=\begin{cases}
\left\lbrack x^{\left\lceil n/2\right\rceil-1}\right\rbrack\dfrac{U_e\left(x,y\right)}{V\left(x,y\right)}&\text{ if }n-1\text{ is even,} \\
\left\lbrack x^{\left\lceil n/2\right\rceil-1}\right\rbrack\dfrac{U_o\left(x,y\right)}{V\left(x,y\right)}&\text{ if }n-1\text{ is odd.}
\end{cases}
\end{aligned}
$$

Here is the pseudocode:

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{PowProj}}\left(P(x,y),Q(x,y),n,m\right)\text{:} \\
&\textbf{Input}\text{: }P,Q\in\mathbb{C}\left\lbrack x,y\right\rbrack ,n,m\in\mathbb{N}_{>0}\text{.} \\
&\textbf{Output}\text{: }\left\lbrack x^{n-1}\right\rbrack\dfrac{P(x,y)}{Q(x,y)}\bmod{y^m}\text{.} \\
&\textbf{Require}\text{: }\left\lbrack x^0y^0\right\rbrack Q=1\text{.} \\
1&\textbf{while }n>1\textbf{ do} \\
2&\qquad U(x,y)\gets P(x,y)Q(-x,y)\bmod{x^n}\bmod{y^m} \\
3&\qquad \textbf{if }n-1\text{ is even }\textbf{then} \\
4&\qquad\qquad P(x,y)\gets \sum_{j=0}^{\left\lceil n/2\right\rceil +1}\left(\left\lbrack x^{2j}\right\rbrack U(x,y)\right)x^j \\
5&\qquad \textbf{else} \\
6&\qquad\qquad P(x,y)\gets \sum_{j=0}^{\left\lceil n/2\right\rceil +1}\left(\left\lbrack x^{2j+1}\right\rbrack U(x,y)\right)x^j \\
7&\qquad \textbf{end if} \\
8&\qquad V(x,y)\gets Q(x,y)Q(-x,y)\bmod{x^n}\bmod{y^m} \\
9&\qquad Q(x,y)\gets \sum_{j=0}^{\left\lceil n/2\right\rceil +1}\left(\left\lbrack x^{2j}\right\rbrack V(x,y)\right)x^j \\
10&\qquad n\gets \left\lceil n/2\right\rceil \\
11&\textbf{end while} \\
12&\textbf{return }\left(\frac{P(0,y)}{Q(0,y)}\bmod{y^m}\right)
\end{array}
$$

Again, we can write down $Q(0,y)^{-1}$ directly without computing a formal power series inverse. The compositional inverse algorithm is then

$$
\begin{array}{ll} &\textbf{Algorithm }\operatorname{\mathsf{Rev}}(f(x),n)\text{:} \\
&\textbf{Input}\text{: }f\in x\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack, f'(0)\neq 0,n\in\mathbb{N}_{\geq 2}\text{.} \\
&\textbf{Output}\text{: }g(x)\bmod{x^n} \text{ such that }f(g)\equiv g(f)\equiv x\pmod{x^n}\text{.} \\
1&t\gets f'(0) \\
2&F(x)\gets f\left(t^{-1}x\right) \\
3&\sum_{k=0}^{n-1}a_ky^k\gets \operatorname{\mathsf{PowProj}}\left(1,1-y\cdot F(x),n,n\right) \\
4&G(x)\gets \sum_{k=1}^{n-1}\frac{n-1}{k}a_{k}x^{n-1-k} \\
5&H(x)\gets \left(G(x)^{1/(n-1)}\right)^{-1}\bmod{x^{n-1}} \\
6&\textbf{return }\left((t^{-1}x) \circ \left(x\cdot H\right)\right)
\end{array}
$$

??? note "Template ([Luogu P5809 [Template] Polynomial Compositional Inverse](https://www.luogu.com.cn/problem/P5809))"
    The code simplifies and modifies the original algorithm a bit to make it shorter.
    
    ```cpp
    --8<-- "docs/math/code/poly/comp-rev/rev_1.cpp"
    ```

### Derivation via the transposition principle

The Power Projection problem is the transpose of Modular Composition. Kinoshita and Li pointed out that the composition algorithm above can be obtained directly by transposing the Power Projection algorithm. Likewise, any optimization that applies to the Power Projection algorithm also applies to the Modular Composition algorithm. We omit the details.

## References

1.  Yasunori Kinoshita, Baitian Li.[Power Series Composition in Near-Linear Time](https://arxiv.org/abs/2404.05177). FOCS 2024.
2.  Alin Bostan, Ryuhei Mori.[A Simple and Fast Algorithm for Computing the N-th Term of a Linearly Recurrent Sequence](https://arxiv.org/abs/2008.08822). SOSA 2021: 118-132
3.  R. P. Brent and H. T. Kung. 1978.[Fast Algorithms for Manipulating Formal Power Series](https://doi.org/10.1145/322092.322099). J. ACM 25, 4 (Oct. 1978), 581–595.
4.  Daniel J. Bernstein. "[Fast multiplication and its applications](https://cr.yp.to/papers.html#multapps)." Pages 325–384 in Algorithmic number theory: lattices, number fields, curves and cryptography, edited by Joe Buhler, Peter Stevenhagen, Cambridge University Press, 2008, ISBN 978-0521808545.
