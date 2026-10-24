## Jordan decomposition

Let $T$ be a linear transformation on an $n$-dimensional space $V$. If the minimal polynomial of $T$ is:

$$
m_A(\lambda)={(\lambda-\lambda_1)}^{r_1}{(\lambda-\lambda_2)}^{r_2}\cdots{(\lambda-\lambda_k)}^{r_k}
$$

then by the primary decomposition, $V$ splits into a direct sum of subspaces:

$$
V=V_1\oplus V_2\oplus\cdots\oplus V_k
$$

where $V_i=N\left({(A-\lambda_i I)}^{r_i}\right)$ and $A$ is the matrix of $T$. All these subspaces are invariant under $T$.

Let the transformation $T_i$ be the projection of $V$ onto the subspace $V_i$, that is, construct polynomials $u_i(T)$ such that:

-   $$
    T_i=u_i(T)\frac{m_A(T)}{{(T-\lambda_i T_e)}^{r_i}}
    $$
-   $$
    T_1+T_2+\cdots+T_k=T_e
    $$

Here $T_e$ is the identity transformation of $V$. Then we have the properties:

-   The restriction ${T_i|}_{V_i}$ of $T_i$ to $V_i$ is the identity transformation of $V_i$.
-   If $i$ and $j$ are different, the restriction ${T_i|}_{V_j}$ of $T_i$ to $V_j$ is the zero transformation of $V_j$.

So $T_i$ maps each vector $\xi$ of $V$ to its component $\xi_i$ in $V_i$.

Construct the transformation:

$$
T_D=\lambda_1 T_1+\lambda_2 T_2+\cdots+\lambda_k T_k
$$

Since each $T_i$ is a polynomial in $T$, $T_D$ is also a polynomial in $T$, so every subspace $V_i$ is invariant under $T_D$.

From the equalities above, the restriction ${T_D|}_{V_i}$ of $T_D$ to $V_i$ is a homothety (scaling) of $V_i$ with ratio $\lambda_i$. So $T_D$ is diagonalizable.

Construct:

$$
T_N=T-T_D
$$

Then $T_N$ is also a polynomial in $T$, so every subspace $V_i$ is invariant under $T_N$. For any vector $\xi_i$ in $V_i$:

$$
{T_N}^{r_i}(\xi_i)={T-T_D}^{r_i}(\xi_i)={T-\lambda_i T_i}^{r_i}(\xi_i)=0
$$

Let $r$ be the largest of all $r_i$. Then for any vector $\xi$ in $V$, the $r$-th power of $T_N$ maps $\xi$ to the zero vector. So $T_N$ is a nilpotent transformation.

Thus every transformation $T$ of $V$ can be written as:

$$
T=T_D+T_N
$$

where $T_D$ is diagonalizable and $T_N$ is nilpotent. Since $T_D$ and $T_N$ are both polynomials in $T$, they commute:

$$
T_DT_N=T_NT_D
$$

Theorem: let $T_1$ and $T_2$ be two diagonalizable transformations of $V$ with $T_1T_2=T_2T_1$. Then there is a basis under which the matrices of both $T_1$ and $T_2$ are diagonal.

Theorem: let $T$ be a linear transformation on an $n$-dimensional space $V$. Then there exist a diagonalizable transformation $T_D$ and a nilpotent transformation $T_N$ such that:

-   $$
    T=T_D+T_N
    $$
-   $$
    T_DT_N=T_NT_D
    $$

Both are polynomials in $T$, and they are uniquely determined by $T$.

This theorem gives a decomposition of $T$, called the Jordan decomposition of $T$. $T_D$ is called the diagonalizable part of $T$, and $T_N$ the nilpotent part of $T$.

Similarly, there is a Jordan decomposition for matrices:

Theorem: let $A$ be an $n\times n$ matrix. Then there exist a diagonalizable matrix $D$ and a nilpotent matrix $N$ such that:

-   $$
    A=D+N
    $$
-   $$
    DN=ND
    $$

Both are polynomials in $A$, and they are uniquely determined by $A$.

This theorem gives a decomposition of $A$, called the Jordan decomposition of $A$. $D$ is called the diagonalizable part of $A$, and $N$ the nilpotent part of $A$.

## Lambda matrices

Next we introduce a more general kind of matrix that contains a variable parameter $\lambda$, rather than just a table of numbers. This discussion is broader than for matrices made only of numbers.

For $\lambda$ matrices, the field of the corresponding space becomes the field of rational functions in one variable $\lambda$.

A matrix whose entries are polynomials in $\lambda$ is called a $\lambda$ matrix, written $A(\lambda)$.

Since the polynomials include the numbers, a numeric matrix is a special $\lambda$ matrix, and the characteristic matrix $\lambda I-A$ of a numeric matrix $A$ is a $\lambda$ matrix.

### Elementary operations on lambda matrices

For $\lambda$ matrices we can likewise define addition, subtraction, multiplication, elementary operations and rank. For square $\lambda$ matrices we can likewise define determinants, minors and cofactors.

Elementary operations on $\lambda$ matrices are mostly the same as on numeric matrices. Only the row addition is changed to (using row operations as the example):

-   Multiply a row by a polynomial $\varphi(\lambda)$ in $\lambda$ and add it to another row.

Note that scaling is not changed. This is because row addition does not change the determinant, while scaling does. To keep the rank properties over polynomials, the determinant may only change by a factor from the number field.

The corresponding elementary matrices are changed accordingly.

It is easy to see that the determinants of all three kinds of elementary matrices are non-zero constants, so they all have full rank. So multiplying on the left or right by them does not change the rank of a $\lambda$ matrix.

If $A(\lambda)$ can be turned into $B(\lambda)$ by finitely many elementary operations, $A(\lambda)$ and $B(\lambda)$ are called equivalent.

Equivalent $\lambda$ matrices have the same rank. The converse is false, which differs from numeric matrices.

## Smith normal form

Theorem: if the rank of a $\lambda$ matrix $A(\lambda)$ is $r$, then $A(\lambda)$ is always equivalent to:

$$
\begin{pmatrix}
D(\lambda) & 0\\
0 & 0\\
\end{pmatrix}
$$

where:

$$
D(\lambda)=\begin{pmatrix}
d_1(\lambda) &  & \\
 & \ddots & \\
 &  & d_r(\lambda)\\
\end{pmatrix}
$$

Each $d_i(\lambda)$ is a monic polynomial, and each one divides the next: $d_i(\lambda)|d_{i+1}(\lambda)$.

This normal form is called the Smith normal form, and the $d_i(\lambda)$ are called invariant factors.

To compute the Smith normal form, eliminate from the top-left to the bottom-right. At each step, the top-left entry is the greatest common divisor of all remaining polynomials to its lower right, and we use it to eliminate the rest of its row and column to $0$.

Theorem: $A(\lambda)$ and $B(\lambda)$ are equivalent if and only if they have exactly the same invariant factors.

### Elementary divisors

By the fundamental theorem of algebra, let the invariant factors $d_1(\lambda),d_2(\lambda),\cdots,d_m(\lambda)$ of $A(\lambda)$ factor as:

$$
d_i(\lambda)={(\lambda-\lambda_1)}^{e_{i1}}{(\lambda-\lambda_2)}^{e_{i2}}\cdots{(\lambda-\lambda_S)}^{e_{iS}}
$$

where $\lambda_1,\cdots,\lambda_S$ are all distinct. Since:

$$
d_i(\lambda)|d_{i+1}(\lambda)
$$

the exponents $e_{1j},e_{2j},\cdots,e_{mj}$ are non-decreasing, and all exponents of the last factor $d_m(\lambda)$ are non-zero.

All the factors above with exponent greater than zero are together called the elementary divisors of $A(\lambda)$.

Note that elementary divisors are counted with multiplicity. If for some $j$ the exponent $e_{ij}$ appears several times, then the corresponding elementary divisor ${(\lambda-\lambda_j)}^{e_{ij}}$ also appears that many times.

The previous theorem says that $A(\lambda)$ and $B(\lambda)$ are equivalent if and only if they have exactly the same invariant factors. If the invariant factors are the same, then naturally the elementary divisors are also the same, but not the other way round. In fact:

Theorem: $A(\lambda)$ and $B(\lambda)$ have exactly the same invariant factors if and only if they have exactly the same elementary divisors and the same rank.

So "the same elementary divisors and the same rank" is also a criterion for equivalence of $\lambda$ matrices.

When doing elementary operations, we can also first turn $A(\lambda)$ into a diagonal matrix, then find the elementary divisors and the rank, and then the invariant factors to get the normal form. We have:

Theorem: suppose $A(\lambda)$ is equivalent to the diagonal matrix:

$$
\operatorname{diag}\{f_1(\lambda),f_2(\lambda),\cdots,f_r(\lambda),0,\cdots,0\}
$$

Then the powers of linear factors ${(\lambda-\lambda_j)}^{e_{ij}}$ of all of $f_1(\lambda),f_2(\lambda),\cdots,f_r(\lambda)$ form the elementary divisors of $A(\lambda)$.

To build the invariant factors from the elementary divisors and the rank: group the elementary divisors by their linear factor and arrange them in a table, putting each group in one row in descending order of degree, so the highest powers of each group form one column. Pad the number of columns with $1$ up to the rank $r$. Then the product of each column is an invariant factor.

### Application to characteristic matrices

If $A$ and $B$ are numeric matrices, their characteristic matrices are $\lambda$ matrices. We have:

Theorem: numeric matrices $A$ and $B$ are similar if and only if their characteristic matrices $\lambda I-A$ and $\lambda I-B$ are equivalent.

Since the characteristic matrix $\lambda I-A$ contains $n$ copies of $\lambda$, all on the main diagonal, its rank is $n$. By the reasoning above, the characteristic matrices of numeric matrices of the same size always have the same rank, so we get the equivalence:

Numeric matrices $A$ and $B$ are similar if and only if the characteristic matrices $\lambda I-A$ and $\lambda I-B$ have exactly the same elementary divisors.

For the characteristic matrix $\lambda I-A$, elementary operations preserve equivalence, so they do not change the rank.

Look at the three elementary operations. The only rewritten one, row addition, does not change the determinant. In fact, the three elementary operations only change the resulting determinant polynomial by a constant factor, so they do not change its factorization or degree.

So the determinant of the characteristic matrix $\lambda I-A$ is a polynomial of degree $n$. After elementary operations turn it into Smith normal form, since the rank is $n$, the determinant is the product of all invariant factors on the main diagonal, which is also the product of all elementary divisors. So the degrees of all elementary divisors of $\lambda I-A$ add up to $n$.

## Jordan normal form

The matrix

$$
\begin{pmatrix}
\lambda & 1 & 0 & \cdots & 0 & 0\\
0 & \lambda & 1 & \cdots & 0 & 0\\
0 & 0 & \lambda & \cdots & 0 & 0\\
\vdots & \vdots & \vdots &  & \vdots & \vdots\\
0 & 0 & 0 & \cdots & \lambda & 1\\
0 & 0 & 0 & \cdots & 0 & \lambda\\
\end{pmatrix}
$$

whose diagonal entries are all $\lambda$, whose entries just above the main diagonal are all $1$, and whose other entries are all $0$, is called a Jordan matrix belonging to $\lambda$, or a Jordan block.

Clearly a nilpotent Jordan matrix is a special case of a Jordan matrix, namely the case $\lambda=0$.

Theorem: let $T$ be a transformation of an $n$-dimensional space $V$, and let $\lambda_1,\cdots,\lambda_k$ be all the distinct eigenvalues of $T$. Then there is a basis under which the matrix of $T$ has the form:

$$
\begin{pmatrix}
B_1 &  &  & 0\\
 & B_2 &  & \\
 &  & \ddots & \\
0 &  &  & B_k\\
\end{pmatrix}
$$

where

$$
B_i=\begin{pmatrix}
J_{i1} &  &  & 0\\
 & J_{i2} &  & \\
 &  & \ddots & \\
0 &  &  & J_{is_i}\\
\end{pmatrix}
$$

and $J_{i1},\cdots,J_{is_i}$ are all Jordan blocks belonging to $\lambda_i$.

The reason is as follows. First, from the minimal polynomial:

$$
m_A(\lambda)={(\lambda-\lambda_1)}^{r_1}{(\lambda-\lambda_2)}^{r_2}\cdots{(\lambda-\lambda_k)}^{r_k}
$$

we get the primary decomposition:

$$
V=V_1\oplus V_2\oplus\cdots\oplus V_k
$$

where:

$$
V_i=N\left({(A-\lambda_i I)}^{r_i}\right)
$$

and $A$ is the matrix of $T$.

Let $S_i$ be the restriction ${T|}_{V_i}$ of $T$ to $V_i$. Next we try to find the Jordan decomposition of each $S_i$.

Let $T_e$ be the identity transformation on $V$. Unlike in the Jordan decomposition above, let $T_i$ denote the nilpotent part of the Jordan decomposition of $S_i$:

$$
S_i=\lambda_i T_e+T_i
$$

So $T_i$ is a nilpotent transformation of the subspace $V_i$; in fact it is also the restriction ${(T-\lambda_i T_e)|}_{V_i}$ of $T-\lambda_i T_e$ to $V_i$.

The subspace $V_i$ can be decomposed into a direct sum of cyclic subspaces of the nilpotent transformation $T_i$:

$$
V_i=W_{i1}\oplus W_{i2}\oplus\cdots\oplus W_{is_i}
$$

In each cyclic subspace $W_{ij}$, take a cyclic basis in reverse order, and put them together into a basis of $V_i$. Then the matrix of $T_i$ under this basis has the form:

$$
N_i=\begin{pmatrix}
N_{i1} &  &  & 0\\
 & N_{i2} &  & \\
 &  & \ddots & \\
0 &  &  & N_{is_i}\\
\end{pmatrix}
$$

All $N_{ij}$ are nilpotent Jordan blocks. So under the basis of $V_i$ chosen above, the matrix of $S_i$ is:

$$
B_i=\begin{pmatrix}
\lambda_i &  &  & 0\\
 & \lambda_i &  & \\
 &  & \ddots & \\
0 &  &  & \lambda_i\\
\end{pmatrix}+\begin{pmatrix}
N_{i1} &  &  & 0\\
 & N_{i2} &  & \\
 &  & \ddots & \\
0 &  &  & N_{is_i}\\
\end{pmatrix}=\begin{pmatrix}
J_{i1} &  &  & 0\\
 & J_{i2} &  & \\
 &  & \ddots & \\
0 &  &  & J_{is_i}\\
\end{pmatrix}
$$

Here $J_{i1},J_{i2},\cdots,J_{is_i}$ are all Jordan blocks belonging to $\lambda_i$.

Choose a basis of each subspace $V_i$ in this way and put them together into a basis of $V$. Then the matrix of $T$ under this basis has the form stated in the theorem.

An $n\times n$ matrix of the form:

$$
\begin{pmatrix}
J_1 &  &  & 0\\
 & J_2 &  & \\
 &  & \ddots & \\
0 &  &  & J_m\\
\end{pmatrix}
$$

where each $J_i$ is a Jordan block, is called a Jordan normal form.

Theorem: every $n\times n$ matrix $A$ is similar to a Jordan normal form. Apart from the order of the Jordan blocks, the Jordan normal form similar to $A$ is uniquely determined by $A$.

Note that in the matrix $B_i$ constructed above, the first term is a multiple of the identity matrix, so it naturally commutes with the second term. Hence the first term is the diagonalizable part of the Jordan decomposition of $B_i$, and the second term is its nilpotent part.

In the Jordan normal form of a matrix, the diagonal matrix formed by the entries on the main diagonal is the diagonalizable part of that Jordan normal form, and replacing the diagonal entries with $0$ gives its nilpotent part.

Theorem: in the Jordan normal form of a matrix $A$, each Jordan block:

$$
J_i=\begin{pmatrix}
\lambda_i & 1 &  &  & \\
 & \lambda_i & 1 &  & \\
 &  & \ddots & \ddots & \\
 &  &  & \ddots & 1\\
 &  &  &  & \lambda_i\\
\end{pmatrix}
$$

corresponds to an elementary divisor ${(\lambda-\lambda_i)}^{n_i}$ of the characteristic matrix $\lambda I-A$, and all elementary divisors of $\lambda I-A$ correspond to all Jordan blocks in the Jordan normal form of $A$.

This is because $A$ is similar to its Jordan normal form, so their characteristic matrices are equivalent; turning the characteristic matrix of the Jordan normal form into Smith normal form makes this clear.

By this theorem, we can write down the Jordan normal form of $A$ from the elementary divisors of the characteristic matrix $\lambda I-A$.

A corollary is that $A$ is diagonalizable if and only if all elementary divisors of the characteristic matrix $\lambda I-A$ are of degree one.

## Frobenius theorem

As noted above, the Smith normal form of an $n\times n$ characteristic matrix has rank $n$.

Theorem: let the Smith normal form of the characteristic matrix $\lambda I-A$ of a matrix $A$ be:

$$
\operatorname{diag}\{d_1(\lambda),d_2(\lambda),\cdots,d_n(\lambda)\}
$$

Then the last invariant factor $d_n(\lambda)$ is exactly the minimal polynomial $m_A(\lambda)$ of $A$.

Corollary: each of the following is equivalent to $A$ being diagonalizable:

-   The minimal polynomial $m_A(\lambda)$ has no repeated roots.
-   The invariant factors of the characteristic matrix $\lambda I-A$ have no repeated roots.
-   All elementary divisors of the characteristic matrix $\lambda I-A$ are of degree one.
