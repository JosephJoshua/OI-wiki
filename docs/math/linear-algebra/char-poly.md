This part on eigenvalues and eigenvectors only studies square matrices, that is, the linear transformation of a matrix $A$ maps $n$ vectors to $n$ vectors.

In practice we often need to apply the same transformation many times in a row. Describing it only as "the linear transformation of matrix $A$ turns the identity matrix $I$ into $A$" is too abstract. The best approach is to look for "fixed points", that is, the parts that do not move under the transformation.

In fact, though, the linear transformation of a matrix $A$ may well have no fixed points. So we settle for the next best thing: look for parts that stay on the same line, or that undergo only simple deformations.

## Eigenvalues and eigenvectors

Under the linear transformation of a matrix $A$, some vectors keep their direction and are only stretched or shrunk.

Let $V$ be a vector space over $F$ and $T$ a linear transformation on $V$. If there exist $\lambda$ in $F$ and a **non-zero vector** $\xi$ in $V$ such that

$$
T\xi=\lambda\xi
$$

then $\lambda$ is called an **eigenvalue** of $T$, and $\xi$ is called **an eigenvector of $T$ belonging to the eigenvalue $\lambda$**.

Eigenvectors lie on the same line and keep their direction under the linear transformation (being shrunk to zero also counts as keeping the direction). Eigenvectors are not unique: every vector collinear with an eigenvector is also an eigenvector. By convention, the zero vector is not an eigenvector; a vector that has a direction is naturally non-zero. The eigenvalue of an eigenvector is the factor by which it is scaled.

In practice, for eigenvectors sharing the same eigenvalue, we usually pick a basis to represent all of them.

Let $\alpha_1,\alpha_2,\cdots,\alpha_n$ be a basis of $V$, and let $A$ be the matrix of $T$ under this basis, that is:

$$
T(\alpha_1,\alpha_2,\cdots,\alpha_n)=(\alpha_1,\alpha_2,\cdots,\alpha_n)A
$$

Let $\lambda_0$ be an eigenvalue of $T$, $\xi$ an eigenvector of $T$ belonging to $\lambda_0$, and $X$ a non-zero vector with:

$$
\xi=(\alpha_1,\alpha_2,\cdots,\alpha_n)X
$$

Then:

$$
T\xi=\lambda_0\xi
$$

$$
T(\alpha_1,\alpha_2,\cdots,\alpha_n)X=\lambda_0(\alpha_1,\alpha_2,\cdots,\alpha_n)X
$$

$$
(\alpha_1,\alpha_2,\cdots,\alpha_n)AX=\lambda_0(\alpha_1,\alpha_2,\cdots,\alpha_n)X
$$

$$
AX=\lambda_0X
$$

$$
(A-\lambda_0I)X=0
$$

So the corresponding determinant is also $0$.

## Characteristic polynomial

Consider an $n\times n$ matrix $A$, where $n\geq 0\land n\in\mathbb{Z}$. Let $\lambda$ be a parameter. The matrix $\lambda I-A$ is called the **characteristic matrix** of $A$.

The determinant of the characteristic matrix is called the **characteristic polynomial** of $A$. Expanded, it is a polynomial of degree $n$ whose roots are the eigenvalues of $A$. We write it as $p_A(\lambda)$:

$$
p_A(\lambda)=\det(\lambda I_n-A)=\begin{vmatrix}
\lambda-a_{11} & -a_{12} &  \cdots & -a_{1n} \\
-a_{21} & \lambda-a_{22} &  \cdots & -a_{2n} \\
\vdots & \vdots &  & \vdots  \\
-a_{n1} & -a_{n2} &  \cdots & \lambda-a_{nn} \\
\end{vmatrix}
$$

Here $I_n$ is the $n\times n$ identity matrix. Some sources define it as $p_A(\lambda)=\det(A-\lambda I_n)$, which differs from our definition only by a sign $(-1)^n$. With our definition, $p_A(\lambda)$ is always monic, while with the other definition it is monic only when $n$ is even. Note that the determinant of a $0\times 0$ matrix is well defined and equals $1$.

A non-zero solution vector $X$ of $(\lambda_0 I-A)X=0$ is called an eigenvector of $A$ belonging to $\lambda_0$.

A linear transformation $T$ has eigenvalue $\lambda_0$ if and only if the matrix $A$ has eigenvalue $\lambda_0$.

A linear transformation $T$ has eigenvector $\xi$ if and only if the matrix $A$ has eigenvector $X$, where:

$$
\xi=(\alpha_1,\cdots,\alpha_n)X
$$

By the fundamental theorem of algebra, the characteristic polynomial factors as:

$$
f(\lambda)=|\lambda I-A|={(\lambda-\lambda_1)}^{d_1}\cdots{(\lambda-\lambda_m)}^{d_m}
$$

$d_i$ is called the **algebraic multiplicity** of the eigenvalue $\lambda_i$. The algebraic multiplicities add up to the dimension $n$ of the space.

### Finding all eigenvalues and eigenvectors of a matrix

The steps are:

-   Compute the determinant $|\lambda I-A|$.
-   Find all roots in the field $F$ of the polynomial $f(\lambda)=|\lambda I-A|$. These are the eigenvalues of $A$.
-   For each eigenvalue $\lambda$ of $A$, solve the homogeneous linear system $(\lambda I-A)X=0$ and find a fundamental system of solutions $X_1,\cdots,X_t$. Then all eigenvectors of $A$ belonging to $\lambda$ are:

$$
k_1X_1+k_2X_2+\cdots+k_tX_t
$$

where the $k_i$ are not all zero.

-   The eigenvectors of the linear transformation $T$ belonging to $\lambda$ are:

$$
\xi_i=(\alpha_1,\cdots,\alpha_n)X_i
$$

So all eigenvectors belonging to $\lambda$ are:

$$
k_1\xi_1+k_2\xi_2+\cdots+k_t\xi_t
$$

where the $k_i$ are not all zero.

Whether eigenvalues and eigenvectors exist depends on the field that $V$ is over.

## Similarity transformations

### Introduction

If the $n\times n$ matrix $A$ is upper triangular, like

$$
A=
\begin{bmatrix}
a_{1,1}&a_{1,2}&\cdots &a_{1,n}\\
&a_{2,2}&\cdots &a_{2,n}\\
&&\ddots &\vdots \\
&&&a_{n,n}
\end{bmatrix}
$$

then

$$
\begin{aligned}
p_A(x)&=\det(xI_n-A)\\
&=
\begin{bmatrix}
x-a_{1,1}&-a_{1,2}&\cdots &-a_{1,n}\\
&x-a_{2,2}&\cdots &-a_{2,n}\\
&&\ddots &\vdots \\
&&&x-a_{n,n}
\end{bmatrix}
\\
&=\prod_{i=1}^n(x-a_{i,i})
\end{aligned}
$$

This is easy to compute, and lower triangular matrices work the same way. But if $A$ is neither, we need a similarity transformation to turn the matrix into a form whose characteristic polynomial is easy to find.

### Definition

For $n\times n$ matrices $A$ and $B$, if there is an invertible $n\times n$ matrix $P$ with

$$
B=P^{-1}AP
$$

then $A$ and $B$ are similar, and the transformation $A\mapsto P^{-1}AP$ is called a similarity transformation. Moreover, $A$ and $P^{-1}AP$ have the same characteristic polynomial.

Consider

$$
\begin{aligned}
\det(xI_n-P^{-1}AP)&=\det(xP^{-1}I_nP-P^{-1}AP)\\
&=\det(P^{-1}xI_nP-P^{-1}AP)\\
&=\det(P^{-1})\cdot \det(P)\cdot \det(xI_n-A)\\
&=\det(xI_n-A)\\
&=p_A(x)
\end{aligned}
$$

This proves the claim, and the same holds for $A\mapsto PAP^{-1}$. Also, $p_A(0)=(-1)^n\cdot \det(A)$, because $p_A(0)=\det(-1\cdot I_nA)=\det(-1\cdot I_n)\cdot \det(A)$, so $\det(A)=\det(P^{-1}AP)$.

Theorem: similar matrices have the same characteristic polynomial and eigenvalues, but the converse is false.

The theorem shows that the characteristic polynomial of the matrix of a linear transformation does not depend on the choice of basis; it is determined by the linear transformation itself. So we can call it the characteristic polynomial of the linear transformation.

The characteristic polynomial $f(\lambda)=|\lambda I-A|$ of a matrix $A$ is monic. By Vieta's formulas, its coefficient of degree $n-1$ is:

$$
-(\lambda_1+\cdots+\lambda_n)=-(a_{11}+\cdots+a_{nn})=-tr A
$$

Here $tr A$ is called the trace of $A$, the sum of the entries on the main diagonal of $A$.

By Vieta's formulas, the constant term of the characteristic polynomial is:

$$
{(-1)}^n|A|={(-1)}^n(\lambda_1\cdots\lambda_n)
$$

Theorem: similar matrices have the same trace.

### Commutation formula

Theorem: whether or not $A$ and $B$ are square, as long as the products are defined, the trace of $AB$ equals the trace of $BA$.

One proof is to expand directly, and we are done. Another proof uses the commutation formula.

Theorem: let $A$ be an $m\times n$ matrix and $B$ an $n\times m$ matrix. Then:

$$
\lambda^n|\lambda I_m-AB|=\lambda^m|\lambda I_n-BA|
$$

This formula shows that $AB$ and $BA$ have the same non-zero eigenvalues.

### Schur's lemma

Every $n\times n$ matrix $A$ is similar to an upper triangular matrix. That is, there is a full-rank matrix $P$ such that $P^{-1}AP$ is upper triangular, and the entries on its main diagonal are all the eigenvalues of $A$.

Corollary: let the $n$ eigenvalues of $A$ be $\lambda_1,\cdots,\lambda_n$ and let $\phi(x)$ be any polynomial. Then the $n$ eigenvalues of the matrix polynomial $\phi(A)$ are:

$$
\phi(\lambda_1),\cdots,\phi(\lambda_n)
$$

In particular, the eigenvalues of $kA$ are $k\lambda_1,\cdots,k\lambda_n$, and the eigenvalues of $A^m$ are ${\lambda_1}^m,\cdots,{\lambda_n}^m$.

### Similarity transformations using Gaussian elimination

We can run Gaussian elimination on an $n\times n$ matrix $B$. Its basic operations are elementary row operations.

After applying such an operation to a matrix (multiplying on the left by an elementary matrix), multiplying on the right by its inverse gives a similarity transformation. Left multiplication is a row operation, and it is easy to see that right multiplication is a column operation.

If a similarity transformation can turn the matrix into upper or lower triangular form, its characteristic polynomial is easy to find. But applying $A\mapsto T_{ij}(k)AT_{ij}(-k)$ to entries on the main diagonal causes a problem: after $A\mapsto T_{ij}(k)A$ eliminates the entry in row $i$, column $j$ to zero, the right multiplication by $T_{ij}(-k)$ adds $-k$ times column $i$ of $A$ to column $j$, which may make previously eliminated entries non-zero again. So we may not be able to reach upper or lower triangular form.

Below we show that if we apply the transformation to entries on the subdiagonal instead, the resulting matrix still has an easy-to-compute characteristic polynomial.

### Upper Hessenberg matrices

For $n\gt 2$, a matrix of the form

$$
H=
\begin{bmatrix}
\alpha_{1}&h_{12}&\dots&\dots&h_{1n}\\
\beta_{2}&\alpha_{2}&h_{23}&\dots &\vdots \\
&\ddots &\ddots & \ddots &\vdots \\
& &\ddots &\ddots & h_{(n-1)n}\\
&&& \beta_{n}& \alpha_{n}
\end{bmatrix}
$$

is called an upper Hessenberg matrix, where $\beta$ is the subdiagonal.

Using similarity transformations to eliminate the entries below the subdiagonal to zero gives an upper Hessenberg matrix, and the characteristic polynomial of an $n\times n$ upper Hessenberg matrix can be found in $O(n^3)$ time.

Let $H_i$ be the matrix that keeps only the first $i$ rows and first $i$ columns of $H$, and let $p_i(x)=\det(xI_i-H_i)$. Then

$$
H_0=
\begin{bmatrix}
\end{bmatrix},\quad
p_0(x)=1
$$

$$
H_1=
\begin{bmatrix}
\alpha_1
\end{bmatrix},\quad
p_1(x)=\det(x I_1-H_1)=x -\alpha_1
$$

$$
H_2=
\begin{bmatrix}
\alpha_1&h_{12}\\
\beta_2&\alpha_2
\end{bmatrix},\quad
p_2(x)=\det(xI_2-H_2)=(x-\alpha_2)p_1(x)-\beta_2h_{12}p_0(x)
$$

When computing a determinant, we usually expand along the row or column with the most zeros, using minors. A minor is the matrix left after deleting the row and column of the chosen entry. Here we expand along the last row:

$$
\begin{aligned}
p_3(x)&=
\det(xI_3-H_3)\\
&=\begin{vmatrix}
x-\alpha_1&-h_{12}&-h_{13}\\
-\beta_2&x-\alpha_2&-h_{23}\\
&-\beta_3&x-\alpha_3
\end{vmatrix}\\
&=(x-\alpha_3)\cdot (-1)^{3+3}p_2(x)-\beta_3\cdot (-1)^{3+2}
\begin{vmatrix}
x-\alpha_1&-h_{13}\\
-\beta_2&-h_{23}
\end{vmatrix}\\
&=(x-\alpha_3)p_2(x)-\beta_3(h_{23}p_1(x)+\beta_2h_{13}p_0(x))
\end{aligned}
$$

By observation and induction, for $2\leq i\leq n$ we have

$$
p_i(x)=(x-\alpha_i)p_{i-1}(x)-
\sum_{m=1}^{i-1}h_{i-m,i}
\left(
\prod_{j=i-m+1}^{i}\beta_j
\right)
p_{i-m-1}(x)
$$

This completes the algorithm, which is usually called the Hessenberg algorithm.

## Cayley–Hamilton theorem

For any $n\times n$ matrix $A$ with characteristic polynomial $f(\lambda)=|\lambda I-A|$, we always have $f(A)=0$.

There is a parallel result for a linear transformation $T$: if $f(\lambda)$ is the characteristic polynomial of $T$, then $f(T)$ is the zero transformation.

It follows from this theorem that every matrix $A$ has a polynomial that annihilates it.

## Minimal polynomial

Let $V$ be an $n$-dimensional vector space. Since the matrix of a linear transformation has $n^2$ entries, all linear transformations form an $n^2$-dimensional vector space.

For a particular linear transformation $T$, consider applying it $0$ times up to $n^2$ times: that gives $n^2+1$ linear transformations in total, and their matrices must be linearly dependent. So there is a non-zero polynomial $f$ such that $f(T)$ is the zero transformation; we say $T$ satisfies the polynomial $f$. Among all polynomials $f$ that $T$ satisfies, there is one of lowest degree.

The monic polynomial of lowest degree that annihilates a matrix $A$ is called the minimal polynomial of $A$, written $m_A(\lambda)$.

By the Euclidean algorithm for polynomials, the minimal polynomial is unique and divides every annihilating polynomial of $A$. In particular, the minimal polynomial divides the characteristic polynomial.

Theorem: ignoring multiplicities, the characteristic polynomial $f(\lambda)$ and the minimal polynomial $m_A(\lambda)$ of a matrix $A$ have the same roots.

Theorem: eigenvectors of a matrix $A$ belonging to different eigenvalues are linearly independent.

## Applications

In competitive programming we usually consider matrices over $(\mathbb{Z}/m\mathbb{Z})^{n\times n}$. Usually $m$ is prime, and the similarity transformation above is simple. When $m$ is composite, we can use a method similar to the Euclidean algorithm.

??? note "Implementation"
    ```cpp
    #include <cassert>
    #include <iostream>
    #include <random>
    #include <vector>
    
    using Matrix = std::vector<std::vector<int>>;
    using i64 = int64_t;
    
    Matrix to_upper_Hessenberg(const Matrix &M, int mod) {
      Matrix H(M);
      int n = H.size();
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          if ((H[i][j] %= mod) < 0) H[i][j] += mod;
        }
      }
      for (int i = 0; i < n - 1; ++i) {
        int pivot = i + 1;
        for (; pivot < n; ++pivot) {
          if (H[pivot][i] != 0) break;
        }
        if (pivot == n) continue;
        if (pivot != i + 1) {
          for (int j = i; j < n; ++j) std::swap(H[i + 1][j], H[pivot][j]);
          for (int j = 0; j < n; ++j) std::swap(H[j][i + 1], H[j][pivot]);
        }
        for (int j = i + 2; j < n; ++j) {
          for (;;) {
            if (H[j][i] == 0) break;
            if (H[i + 1][i] == 0) {
              for (int k = i; k < n; ++k) std::swap(H[i + 1][k], H[j][k]);
              for (int k = 0; k < n; ++k) std::swap(H[k][i + 1], H[k][j]);
              break;
            }
            if (H[j][i] >= H[i + 1][i]) {
              int q = H[j][i] / H[i + 1][i], mq = mod - q;
              for (int k = i; k < n; ++k)
                H[j][k] = (H[j][k] + i64(mq) * H[i + 1][k]) % mod;
              for (int k = 0; k < n; ++k)
                H[k][i + 1] = (H[k][i + 1] + i64(q) * H[k][j]) % mod;
            } else {
              int q = H[i + 1][i] / H[j][i], mq = mod - q;
              for (int k = i; k < n; ++k)
                H[i + 1][k] = (H[i + 1][k] + i64(mq) * H[j][k]) % mod;
              for (int k = 0; k < n; ++k)
                H[k][j] = (H[k][j] + i64(q) * H[k][i + 1]) % mod;
            }
          }
        }
      }
      return H;
    }
    
    std::vector<int> get_charpoly(const Matrix &M, int mod) {
      Matrix H(to_upper_Hessenberg(M, mod));
      int n = H.size();
      std::vector<std::vector<int>> p(n + 1);
      p[0] = {1 % mod};
      for (int i = 1; i <= n; ++i) {
        const std::vector<int> &pi_1 = p[i - 1];
        std::vector<int> &pi = p[i];
        pi.resize(i + 1, 0);
        int v = mod - H[i - 1][i - 1];
        if (v == mod) v -= mod;
        for (int j = 0; j < i; ++j) {
          pi[j] = (pi[j] + i64(v) * pi_1[j]) % mod;
          if ((pi[j + 1] += pi_1[j]) >= mod) pi[j + 1] -= mod;
        }
        int t = 1;
        for (int j = 1; j < i; ++j) {
          t = i64(t) * H[i - j][i - j - 1] % mod;
          int prod = i64(t) * H[i - j - 1][i - 1] % mod;
          if (prod == 0) continue;
          prod = mod - prod;
          for (int k = 0; k <= i - j - 1; ++k)
            pi[k] = (pi[k] + i64(prod) * p[i - j - 1][k]) % mod;
        }
      }
      return p[n];
    }
    
    bool verify(const Matrix &M, const std::vector<int> &charpoly, int mod) {
      if (mod == 1) return true;
      int n = M.size();
      std::vector<int> randvec(n), sum(n, 0);
      std::mt19937 gen(std::random_device{}());
      std::uniform_int_distribution<int> dis(1, mod - 1);
      for (int i = 0; i < n; ++i) randvec[i] = dis(gen);
      for (int i = 0; i <= n; ++i) {
        int v = charpoly[i];
        for (int j = 0; j < n; ++j) sum[j] = (sum[j] + i64(v) * randvec[j]) % mod;
        std::vector<int> prod(n, 0);
        for (int j = 0; j < n; ++j) {
          for (int k = 0; k < n; ++k) {
            prod[j] = (prod[j] + i64(M[j][k]) * randvec[k]) % mod;
          }
        }
        randvec.swap(prod);
      }
      for (int i = 0; i < n; ++i)
        if (sum[i] != 0) return false;
      return true;
    }
    
    int main() {
      std::ios::sync_with_stdio(false);
      std::cin.tie(nullptr);
      int n, mod;
      std::cin >> n >> mod;
      Matrix M(n, std::vector<int>(n));
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) std::cin >> M[i][j];
      std::vector<int> charpoly(get_charpoly(M, mod));
      for (int i = 0; i <= n; ++i) std::cout << charpoly[i] << ' ';
      assert(verify(M, charpoly, mod));
      return 0;
    }
    ```

The Hessenberg algorithm above is not numerically stable, so matrices over $\mathbb{R}^{n\times n}$ need to be adjusted by other algorithms first, or a numerically stable algorithm should be used instead.

We can connect the characteristic polynomial with homogeneous linear recurrences with constant coefficients. Together with the Cayley–Hamilton theorem and polynomial modulo, it can also speed up computing matrix powers over some fields.

The Cayley–Hamilton theorem states that

$$
\begin{aligned}
p_A(A)&=A^n+c_1A^{n-1}+\cdots +c_{n-1}A+c_nI\\
&=O
\end{aligned}
$$

where $O$ is the $n\times n$ zero matrix, $A\in\mathbb{C}^{n\times n}$, and $p_A(x)=x^n+\sum_{i=1}^nc_ix^{n-i}\in\mathbb{C}[x]$ is the characteristic polynomial of $A$.

If we want $A^K$ for a large $K$, we can compute $f(x)=x^K\bmod{p_A(x)}$ and then use $f(A)=A^K$.

Clearly $\deg(f(x))\lt n$. Let $f(x)=\sum_{i=0}^{n-1}f_ix^i$ and $n=km$. Then

$$
\begin{aligned}
f_{km-1}x^{km-1}+\cdots +f_1x+f_0&=(\cdots (f_{km-1}x^{k-1}+\cdots +f_{k(m-1)})x^k\\
&+f_{k(m-1)-1}x^{k-1}+\cdots +f_{k(m-2)})x^k\\
&+\cdots\\
&+f_{k-1}x^{k-1}+\cdots +f_1x+f_0
\end{aligned}
$$

Setting $k=\sqrt{n}$, we see that computing $f(A)$ takes about $O(\sqrt{n})$ matrix-matrix multiplications.

## References

-   Rizwana Rehman, Ilse C.F. Ipsen.[La Budde’s Method for Computing Characteristic Polynomials](https://ipsen.math.ncsu.edu/ps/charpoly3.pdf).
-   Marshall Law.[Computing Characteristic Polynomials of Matrices of Structured Polynomials](http://summit.sfu.ca/system/files/iritems1/17301/etd10125_.pdf).
-   Mike Paterson.[On the Number of Nonscalar Multiplications Necessary to Evaluate Polynomials](https://epubs.siam.org/doi/10.1137/0202007).
