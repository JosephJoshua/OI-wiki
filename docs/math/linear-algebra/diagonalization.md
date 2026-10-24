## Eigenspaces

All eigenvectors of a matrix $A$ belonging to $\lambda_0$, together with the zero vector, form a vector space called an eigenspace of $A$, written $E(\lambda_0)$. It is made up of the solutions of the homogeneous linear system:

$$
(\lambda_0 I-A)X=0
$$

In other words, it is the solution space of this system.

For the eigenspace $E(\lambda_i)=N(\lambda_i I-A)$, the rank–nullity theorem gives:

$$
r(\lambda_i I-A)+\operatorname{dim} N(\lambda_i I-A)=n
$$

So the dimension of the eigenspace $E(\lambda_i)$ is:

$$
\operatorname{dim} E(\lambda_i)=n-r(\lambda_i I-A)
$$

This is also called the **geometric multiplicity** of $\lambda_i$.

## Invariant subspaces

When studying a linear transformation $T$, we often want to choose a basis of the space $V$ so that the matrix of $T$ under this basis is as simple as possible.

Let $V$ be a vector space over a number field $F$, $W$ a subspace of $V$, and $T$ a linear transformation on $V$. If for every vector $x$ in $W$, $T(x)$ is also in $W$ (we also say the space is invariant or stable under the transformation), then $W$ is called an invariant subspace of $T$.

A space being invariant under a transformation does not mean the coordinates truly "do not change". The vectors may be stretched or otherwise deformed; they just still land inside the space after the deformation.

-   Every subspace of a vector space $V$ is an invariant subspace of a scalar multiplication transformation.
-   For any linear transformation $T$ on $V$, the space $V$ and the zero subspace are invariant subspaces of $T$, called the trivial invariant subspaces.
-   Intersections and sums of invariant subspaces are also invariant subspaces.

Let $W$ be an invariant subspace of a linear transformation $T$. Considering only how $T$ acts on $W$ gives a linear transformation of $W$ itself, called the restriction of $T$ to the subspace $W$, written ${T|}_W$.

For any linear transformation $T$ on $V$, the image $R(T)$ and the kernel $N(T)$ are invariant subspaces of $T$. Intuitively, under the transformation the space $V$ either gets compressed into itself (the image) or compressed to $0$ (the kernel).

For any linear transformation $T$ on $V$, the eigenspaces of $T$ are invariant subspaces of $T$.

## Primary decomposition

By the fundamental theorem of algebra, the minimal polynomial factors as:

$$
m_A(\lambda)={(\lambda-\lambda_1)}^{r_1}\cdots{(\lambda-\lambda_S)}^{r_S}
$$

Substitute the matrix $A$ for the variable $\lambda$ in the minimal polynomial. The kernels of the factors form a series of invariant subspaces of $A$:

$$
W_i=N({(\lambda_i I-A)}^{r_i})
$$

Theorem: the dimension of the invariant subspace $W_i$ is exactly the algebraic multiplicity of the eigenvalue $\lambda_i$.

Recall that the algebraic multiplicity is the degree of a factor of the characteristic polynomial, and the geometric multiplicity is the dimension of the eigenspace $E(\lambda_i)=N(\lambda_i I-A)$. The invariant subspace $W_i$ and the eigenspace $E(\lambda_i)$ are both kernels of matrices, and the two matrices are related by the $r_i$-th power from the minimal polynomial. In other words, the dimension of the eigenspace is the geometric multiplicity; raising to the $r_i$-th power from the minimal polynomial takes the "eigenspace" to an "invariant subspace", whose dimension reaches the algebraic multiplicity from the characteristic polynomial.

This theorem is actually a corollary of the primary decomposition theorem below.

Let $T$ be the linear transformation of the matrix $A$, and let $T_i={T|}_{W_i}$ be its restriction to each subspace $W_i$. Then the minimal polynomial of $T_i$ is $(x-\lambda_i)^{r_i}$.

Theorem: let $V$ be a vector space over a field $F$ and $T$ a linear transformation on $V$. Then $V$ has a primary decomposition with respect to $T$: it splits into a direct sum of invariant subspaces $W_i$.

$$
V=W_1\oplus W_2\oplus\cdots\oplus W_S
$$

This means that the matrix of $T$ under some basis is block diagonal:

$$
\operatorname{diag}\{A_1,A_2,\cdots,A_S\}
$$

where $A_i$ is the matrix of $T_i$ under the corresponding basis.

This theorem shows that invariant subspaces can be used to simplify the matrix of a linear transformation.

## Diagonalizable matrices

An $n\times n$ square matrix $A$ that is similar to a diagonal matrix is called diagonalizable, or a simple matrix.

-   Sums, products and inverses (when they exist) of diagonal matrices are still diagonal, and the entries on the diagonal are the eigenvalues.
-   The matrix of a linear transformation $T$ is diagonalizable if and only if the matrix of $T$ under some basis is diagonal.

Theorem: let $\lambda_1,\cdots,\lambda_m$ be all the distinct eigenvalues of a matrix $A$. Then the following are equivalent:

-   $A$ is diagonalizable.
-   $A$ has $n$ linearly independent eigenvectors.
-   The following holds:

$$
\operatorname{dim} E(\lambda_1)+\cdots+\operatorname{dim} E(\lambda_m)=n
$$

As noted above, the exponent of an eigenvalue in the factorization of the characteristic polynomial is its algebraic multiplicity, and the dimension of its eigenspace is its geometric multiplicity. This theorem also shows that $A$ is diagonalizable if and only if, for every eigenvalue $\lambda$ of $A$, the algebraic multiplicity equals the geometric multiplicity.

Corollary: if an $n\times n$ matrix $A$ has exactly $n$ distinct eigenvalues, it must be diagonalizable. The converse is not necessarily true.

Theorem: a matrix $A$ is diagonalizable if and only if its minimal polynomial has no repeated roots.

Similarity of matrices also preserves the linear dependence relations among eigenvectors.

Eigenvectors may well not be real, and it may well be impossible to find $n$ linearly independent eigenvectors.

For a repeated eigenvalue, the eigenvectors span a space. To describe this space we need to pick representatives from it. We usually pick linearly independent representatives, and their number is the dimension of the space.

When picking representatives, we often orthogonalize and normalize them. The final result is a set of orthonormal representatives.

Eigenvectors are not necessarily orthogonal, and eigenvectors for different eigenvalues may not be orthogonalizable. So orthogonalization can only be done among eigenvectors of a repeated eigenvalue. Normalization, however, can be done on any eigenvector.

## Nilpotent matrices

Let $T$ be a linear transformation of a space $V$. If there is a positive integer $r$ such that $T^r$ is the zero transformation, $T$ is called a nilpotent transformation of $V$.

A matrix satisfying $N^r=0$ for some positive integer $r$ is called a nilpotent matrix.

We can usually further assume that $r$ is the smallest positive integer such that $T^r$ is the zero transformation, so the minimal polynomial of $T$ is $x^r$. Then there is a vector $\xi_0$ such that:

-   $$
    T^r(\xi_0)=0
    $$
-   $$
    T^{r-1}(\xi_0)\neq 0
    $$

### Cyclic subspaces

Theorem: let $T$ be a linear transformation of a space $V$ and $\xi$ a vector in $V$. If there is a positive integer $s$ such that:

-   $$
    T^s(\xi)=0
    $$
-   $$
    T^{s-1}(\xi)\neq 0
    $$

then the vectors $\xi,T(\xi),\cdots,T^{s-1}(\xi)$ are linearly independent.

This theorem leads to a definition:

Let $T$ be a linear transformation of a space $V$ and $W$ a subspace of $V$. If there is a vector $\xi_0$ and a positive integer $r$ such that:

-   the vectors $\xi_0,T(\xi_0),\cdots,T^{r-1}(\xi_0)$ form a basis of $W$;
-   the following holds:

    $$
    T^r(\xi_0)=0
    $$

then the subspace $W$ is called a cyclic subspace with respect to $T$, or a $T$-cyclic subspace for short. In this case $\xi_0$ is called a generating vector of the cyclic subspace $W$, and the vectors $\xi_0,T(\xi_0),\cdots,T^{r-1}(\xi_0)$ are called a cyclic basis of $W$.

Clearly a $T$-cyclic subspace $W$ is invariant under $T$, and every vector $\xi$ in the cyclic subspace $W$ satisfies $T^r(\xi)=0$, where $r$ is the dimension of the cyclic subspace.

### Nilpotent Jordan blocks

If $W$ is a cyclic subspace of the transformation $T$, then the restriction ${T|}_W$ of $T$ to $W$ is a nilpotent transformation of $W$, and the matrix of ${T|}_W$ with respect to the cyclic basis of $W$ in reverse order, $T^{r-1}(\xi_0),T^{r-2}(\xi_0),\cdots,\xi_0$, is the following $r\times r$ upper triangular matrix:

$$
N_r=\begin{pmatrix}
0 & 1 & 0 & \cdots & 0 & 0\\
0 & 0 & 1 & \cdots & 0 & 0\\
0 & 0 & 0 & \cdots & 0 & 0\\
\vdots & \vdots & \vdots &   & \vdots& \vdots\\
0 & 0 & 0 & \cdots & 0 & 1\\
0 & 0 & 0 & \cdots & 0 & 0\\
\end{pmatrix}
$$

The matrix $N_r$ is called a nilpotent Jordan matrix of order $r$, or a nilpotent Jordan block of order $r$.

Let $T$ be a nilpotent transformation of an $n$-dimensional space $V$. The uniquely determined positive integers $r_1\geq\cdots\geq r_S$ that appear in the decomposition of $V$ into $T$-cyclic subspaces are called the invariant indices of $T$.

An $n\times n$ nilpotent matrix $A$ is similar to a matrix $N$ of the form above, which also uniquely determines a sequence of positive integers $r_1\geq\cdots\geq r_S$, called the invariant indices of $A$.

A nilpotent matrix cannot be similar to a diagonal matrix, but it can be similar to this standard form. The Jordan normal form combines diagonalization by similarity with the standard form of nilpotent matrices, giving the standard form that a general matrix can reach through similarity transformations.

### Some theorems

1.  Let $T$ be a nilpotent transformation of a space $V$, and let

    $$
    h(x)=a_0+a_1x+\cdots+a_mx^m
    $$

    be a polynomial. Then the linear transformation $h(T)$ has an inverse if and only if $a_0\neq 0$. When $h(T)$ is invertible, its inverse is also a polynomial in $T$.

2.  Let $T$ be a nilpotent transformation of a space $V$, $W$ an $r$-dimensional $T$-cyclic subspace, and $\xi$ a vector in $W$. If there is an integer $k$ such that

    $$
    T^{r-k}(\xi)=0
    $$

    then there is a vector $\eta$ in $W$ such that

    $$
    \xi=T^k(\eta)
    $$

3.  Let $T$ be a nilpotent transformation of an $n$-dimensional space $V$ with minimal polynomial $x^r$, and let $W_1$ be an $r$-dimensional $T$-cyclic subspace. Then there is a complementary subspace $W_2$ of $W_1$ such that:

    $$
    V=W_1\oplus W_2
    $$

    and $W_2$ is also invariant under $T$.

4.  Let $T$ be a nilpotent transformation of an $n$-dimensional space $V$. Then $V$ can be decomposed into a direct sum of $T$-cyclic subspaces:

    $$
    V=W_1\oplus W_2\oplus\cdots\oplus W_S
    $$

5.  Every $n\times n$ nilpotent matrix is similar to a matrix of the form:

    $$
    N=\begin{pmatrix}
    N_{r_1} &   &   & 0\\
      & N_{r_2} &   &  \\
      &   & \cdots &  \\
    0 &   &   & N_{r_S}\\
    \end{pmatrix}
    $$

    where each $N_{r_i}$ is a nilpotent Jordan block of order $r_i$.

6.  If we require the $T$-cyclic subspaces $W_i$ to be sorted in descending order of dimension $r_1\geq\cdots\geq r_S$, then the way to decompose $V$ into $T$-cyclic subspaces is uniquely determined by $T$.
