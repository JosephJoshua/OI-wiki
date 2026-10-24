The determinant is an operation on square matrices. For a square matrix $A$, $\det A$ denotes the determinant of $A$.

This page introduces three definitions of the determinant. One can prove that they are equivalent.

## Definition via permutations

Prerequisites: [permutations](../permutation.md), [inversion number](../permutation.md#逆序数).

This method works for computing low-order determinants by hand. Its time complexity is factorial.

Let $\pi(j_1j_2\cdots j_n)$ denote the inversion number of the permutation $j_1j_2\cdots j_n$, and let $S_n$ be the set of all permutations of length $n$. The notation

$$
\begin{aligned}
\det A &= \begin{vmatrix}
a_{11} & a_{12} & \cdots & a_{1n}\\
a_{21} & a_{22} & \cdots & a_{2n}\\
\vdots & \vdots &  & \vdots\\
a_{n1} & a_{n2} & \cdots & a_{nn}\\
\end{vmatrix} \\
&= \sum_{(j_1j_2\cdots j_n) \in S_n} (-1)^{\pi(j_1j_2\cdots j_n)} a_{1 j_1} a_{2 j_2}\dots a_{n j_n}
\end{aligned}
$$

denotes the determinant of order $n$, which is the signed sum of $n!$ terms. These terms are all possible products $a_{1j_1}a_{2j_2}\cdots a_{nj_n}$ of $n$ entries of $A$ taken from different rows and different columns.

The sign in front of the term $a_{1j_1}a_{2j_2}\cdots a_{nj_n}$ is ${(-1)}^{\pi(j_1j_2\cdots j_n)}$. That is, the sign is positive when $j_1j_2\cdots j_n$ is an even permutation, and negative when it is an odd permutation.

The diagonal rule for determinants of order 2 and 3 actually uses the permutation definition. The same reason explains why the diagonal rule no longer works for determinants of order 4 or higher. In particular, a determinant of order 1 is just the entry itself.

Theorem: take the product of entries from rows $i_1,i_2,\cdots,i_n$ and columns $j_1,j_2,\cdots,j_n$ of a determinant of order $n$:

$$
a_{i_1j_1}a_{i_2j_2}\cdots a_{i_nj_n}
$$

where $i_1,i_2,\cdots,i_n$ and $j_1,j_2,\cdots,j_n$ are both permutations of the $n$ numbers $1,2,\cdots,n$. Then the sign of this term in the determinant is ${(-1)}^{s+t}$, where

$$
s=\pi(i_1i_2\cdots i_n)
$$

$$
t=\pi(j_1j_2\cdots j_n)
$$

Theorem: a determinant equals the determinant of its transpose.

Theorem: suppose every entry in row $i$ of the determinant $\det A$ can be written as a sum of two terms:

$$
\begin{vmatrix}
a_{11} & a_{12} & \cdots & a_{1n}\\
\vdots & \vdots &  & \vdots\\
b_{i1}+c_{i1} & b_{i2}+c_{i2} & \cdots & b_{in}+c_{in}\\
\vdots & \vdots &  & \vdots\\
a_{n1} & a_{n2} & \cdots & a_{nn}\\
\end{vmatrix}
$$

Then this determinant equals the sum of two determinants $\det A_1$ and $\det A_2$, where row $i$ of $A_1$ is $b_{i1},b_{i2},\cdots,b_{in}$, row $i$ of $A_2$ is $c_{i1},c_{i2},\cdots,c_{in}$, and all other rows of $A_1$ and $A_2$ are the same as in $A$. The same property also holds for columns.

## Inductive definition

This method only describes an algebraic property of the determinant. Its time complexity is also factorial, so it is not suitable for computation.

### Cofactors

In a determinant $\det A$ of order $n$, pick any $k$ rows and $k$ columns of the matrix $A$. The entries where these rows and columns cross form a $k\times k$ matrix called a submatrix of order $k$, and its determinant is called a minor of order $k$.

For a determinant $\det A$ of order $n$, the complementary submatrix $M_{ij}$ of an entry $a_{ij}$ is the $(n-1)\times(n-1)$ submatrix left after deleting the row and column containing $a_{ij}$ from $A$; its determinant $\det M_{ij}$ is called the minor.

For a determinant $\det A$ of order $n$, the minor $\det M_{ij}$ of the entry $a_{ij}$ with the sign ${(-1)}^{i+j}$ attached is called the cofactor of $a_{ij}$, written $A_{ij}$.

From the permutation definition in the previous section we can derive:

Theorem: if, in a determinant $\det A$ of order $n$, all entries of row $i$ or of column $j$ other than $a_{ij}$ are $0$, then the determinant equals the product of $a_{ij}$ and its cofactor $A_{ij}$.

### Cofactor expansion

Since transposing a square matrix does not change its determinant, we only need to introduce one of row expansion or column expansion.

The determinant $\det A$ is defined as the sum of the products of all entries in any one row (or column) with their corresponding cofactors.

In other words, the determinant can be defined recursively by expansion along a row (or column):

$$
\begin{aligned}
\det A &= a_{i1}A_{i1}+a_{i2}A_{i2}+\cdots+a_{in}A_{in} \\
&= \sum_{j = 1}^{n} a_{ij}A_{ij} \\
&= \sum_{j = 1}^{n} (-1)^{i + j} a_{ij} \det M_{ij}
\end{aligned}
$$

$$
\begin{aligned}
\det A &= a_{1j}A_{1j}+a_{2j}A_{2j}+\cdots+a_{nj}A_{nj} \\
&= \sum_{i = 1}^{n} a_{ij}A_{ij} \\
&= \sum_{i = 1}^{n} (-1)^{i + j} a_{ij} \det M_{ij}
\end{aligned}
$$

The recursion ends at the determinant of a $1\times 1$ matrix, which is the only entry of that matrix.

This gives the following result:

Theorem: the sum of the products of the entries of one row (or column) of $\det A$ with the cofactors of the corresponding entries of another row (or column) is $0$.

In other words, when $i\neq j$:

$$
a_{i1}A_{j1}+a_{i2}A_{j2}+\cdots+a_{in}A_{jn}=0
$$

$$
a_{1i}A_{1j}+a_{2i}A_{2j}+\cdots+a_{ni}A_{nj}=0
$$

## Axiomatic definition

The axiomatic definition says that an operation satisfying certain properties can only be the determinant.

Prerequisites: [elementary operations](./elementary-operations.md).

Let $D_i(k)$ be a [scaling matrix](./elementary-operations.md#倍乘矩阵), $P_{ij}$ a [swap matrix](./elementary-operations.md#对换矩阵), and $T_{ij}(k)$ a [row-addition matrix](./elementary-operations.md#倍加矩阵).

An operation $\det$ on $n\times n$ matrices $A$ is called the determinant if it satisfies the following four properties:

-   Multiplying all entries of one row or one column of a determinant by a number $k$ multiplies the determinant by $k$.

    $$
    \det(D_i(k)A) = \det(AD_i(k)) = k \det A
    $$

-   Swapping two rows or two columns of a determinant changes its sign.

    $$
    \det(P_{ij}A) = \det(AP_{ij}) = -\det A
    $$

-   Multiplying the entries of one row or column by the same number and adding them to the corresponding entries of another row or column does not change the determinant.

    $$
    \det(T_{ij}(k)A) = \det(AT_{ij}(k))= \det A
    $$

-   The determinant of the identity matrix is $1$.

    $$
    \det I = 1
    $$

The properties of the determinant under elementary operations make it convenient to compute higher-order determinants by hand. [Computing the determinant with Gaussian elimination](../numerical/gauss.md#行列式计算) also uses these properties, with time complexity $O(n^3)$.

These properties have several corollaries:

-   A common factor of one row or one column can be pulled out in front of the determinant.
-   If all entries of one row or one column of a determinant are $0$, the determinant is $0$.
-   If two rows or two columns of a determinant are proportional, the determinant is $0$.
-   If two rows or two columns of a determinant are identical, the determinant is $0$.

These corollaries are used all the time when computing determinants by hand.
