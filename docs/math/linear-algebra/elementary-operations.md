## Elementary matrices

The following three kinds of square matrices are called elementary matrices.

### Scaling matrices

A scaling matrix is a special diagonal matrix.

$$
D_i(k)=\operatorname{diag}\{1,\cdots,1,k,1,\cdots,1\}
$$

denotes a diagonal matrix whose $i$-th entry on the main diagonal is $k$, where $k$ must not be $0$, and all other diagonal entries are $1$.

In particular, when $k$ is $1$, $D_i(1)$ is the identity matrix $I$.

### Swap matrices

A swap matrix is a special symmetric matrix.

$$
P_{ij}=\begin{pmatrix}
I_{i-1} &  &  &  & \\
 & 0 &  & 1 & \\
 &  & I_{j-i-1} &  & \\
 & 1 &  & 0 & \\
 &  &  &  & I_{n-j}\\
\end{pmatrix}
$$

All entries of a swap matrix are $1$ or $0$. The entries on the main diagonal are all $1$ except the $i$-th and $j$-th, which are $0$, and the two entries in row $i$, column $j$ and in row $j$, column $i$ are $1$.

A swap matrix requires $i$ and $j$ to be different.

### Row-addition matrices

A row-addition matrix is the identity matrix $I$ with the entry in row $i$, column $j$ set to $k$.

$$
T_{ij}(k)=\begin{pmatrix}
1 &  &  &  &  &  & \\
 & \ddots &  &  &  &  & \\
 &  & 1 & \cdots & k &  & \\
 &  &  & \ddots & \vdots &  & \\
 &  &  &  & 1 &  & \\
 &  &  &  &  & \ddots & \\
 &  &  &  &  &  & 1\\
\end{pmatrix}
$$

A row-addition matrix requires $i$ and $j$ to be different. If $k$ is $0$, $T_{ij}(0)$ degenerates into the identity matrix $I$.

A row-addition matrix is either upper triangular or lower triangular.

### Determinants of elementary matrices

The three kinds of elementary matrices have determinants:

$$
|D_i(k)|=k
$$

$$
|P_{ij}|=-1
$$

$$
|T_{ij}(k)|=1
$$

Since the determinant of a product of square matrices is the product of their determinants, and by the equivalence between elementary operations and matrix multiplication shown below, this property of elementary matrices can be used to compute determinants.

## Elementary operations

Not only square matrices: for a general matrix $A$ we can apply elementary row operations and elementary column operations, together called elementary operations.

Like elementary column operations, elementary row operations come in 3 kinds: multiplication (scaling), switching, and addition. We first introduce the elementary row operations:

-   Multiply row $i$ by a non-zero number $k$: $B\mapsto D_i(k)B$.
-   Swap rows $i$ and $j$: $B\mapsto P_{ij}B$.
-   Add $k$ times row $j$ to row $i$: $B\mapsto T_{ij}(k)B$.

Replacing rows with columns in the operations above gives the elementary column operations.

Among the elementary operations, a swap can be achieved with scalings and additions. Clearly an addition cannot be achieved with scalings and swaps. Using determinants and the equivalence between elementary operations and matrix multiplication shown below, one can also show that a scaling cannot be achieved with additions and swaps.

So compared with swapping, scaling and addition are the more fundamental operations. Swapping is a helper operation introduced to keep elimination orderly in the elimination method.

## Elementary operations and matrix multiplication

Notice that each of the three kinds of elementary matrices is the result of applying the corresponding operation once to the identity matrix $I$. The later page on linear transformations points out a correspondence between linear transformations and matrices, similar to the relationship here.

Whether or not $A$ is square, applying an elementary row operation to $A$ is the same as multiplying $A$ on the left by an elementary matrix. Applying an elementary column operation to $A$ is the same as multiplying $A$ on the right by an elementary matrix.

### Scaling

Multiplying on the left by a scaling matrix $D_i(k)$ multiplies row $i$ by $k$. Multiplying on the right by a scaling matrix $D_i(k)$ multiplies column $i$ by $k$.

The product of diagonal matrices is diagonal: to multiply diagonal matrices, multiply the corresponding entries on the main diagonal. Since the identity matrix is a special scaling matrix, and a scaling matrix requires $k$ to be non-zero, we see that a diagonal matrix can be split into a product of scaling matrices as long as all its diagonal entries are non-zero.

For a general diagonal matrix, whether or not its entries are $0$, there is a similar result. Multiplying on the left by a diagonal matrix multiplies each row by some factor, namely the corresponding entry on the main diagonal. Multiplying on the right by a diagonal matrix does the same to the columns.

Since the determinant of a scaling matrix $D_i(k)$ is $k$, after scaling a row or column of a square matrix, its determinant is multiplied by $k$. The determinant of a diagonal matrix is the product of its diagonal entries.

Multiplication of scaling matrices is commutative, and so is multiplication of diagonal matrices. When a product contains only diagonal matrices, the factors can be arranged in any order.

The scaling operation corresponding to the identity matrix leaves $A$ unchanged, so it is not used in practice.

### Swapping

Multiplying on the left by a swap matrix $P_{ij}$ swaps rows $i$ and $j$. Multiplying on the right by a swap matrix $P_{ij}$ swaps columns $i$ and $j$.

Similar to the relation between scaling matrices and diagonal matrices, we introduce permutation matrices here. A permutation matrix is a square matrix with exactly one $1$ in each row and each column and $0$ everywhere else. The identity matrix $I$ is also a special permutation matrix.

A permutation matrix is the same as permuting the rows of the identity matrix $I$, and also the same as permuting the columns of $I$. The identity matrix $I$ itself corresponds to the identity transformation.

Multiplying on the left by a permutation matrix permutes the rows of the original matrix, and multiplying on the right permutes its columns, in the same way the permutation matrix permutes the rows or columns of the identity matrix $I$.

Permutation matrices correspond exactly to permutations, and the multiplicative group of permutation matrices is isomorphic to the permutation group. By a theorem, treating the identity as a product of zero transpositions, every permutation can be written as a product of transpositions, so every permutation matrix can also be split into a product of swap matrices.

Since the determinant of a swap matrix is $-1$, after swapping two rows or two columns of a square matrix, its determinant is multiplied by $-1$.

Multiplication of swap matrices is not commutative, and neither is multiplication of permutation matrices.

The determinant of a permutation matrix is ${(-1)}^p$, where $p$ is the inversion number of the corresponding permutation, i.e. the number of transpositions it splits into (mod 2).

### Row addition

Multiplying on the left by a row-addition matrix $T_{ij}(k)$ adds $k$ times row $j$ to row $i$. Multiplying on the right by $T_{ij}(k)$ adds $k$ times column $i$ to column $j$.

If this is hard to remember, look at what operation $T_{ij}(k)$ applies to the identity matrix $I$; the two match. Left multiplication acts on rows and right multiplication acts on columns, following the mnemonic "left rows, right columns".

Since the determinant of a row-addition matrix is $1$, a row addition does not change the determinant of a square matrix.

Multiplication of row-addition matrices is not commutative.

The row addition corresponding to the identity matrix leaves $A$ unchanged, so it is not used in practice.

#### Upper triangular matrices

A row-addition matrix is either upper triangular or lower triangular. Since the two kinds are symmetric about the main diagonal, we discuss upper triangular matrices here. In fact, this example needs only elementary row operations, not column operations.

If all diagonal entries of an upper triangular matrix are $1$, it can be split into a product of row-addition matrices. The order of splitting is: first apply row additions to the first row of the identity matrix $I$, then to the second row, and so on, until every row has been processed.

Since multiplication of row-addition matrices is not commutative, the order of these operations cannot be changed.

If all diagonal entries of an upper triangular matrix are non-zero, it can be split into a product of row-addition and scaling matrices. When processing each row of the identity matrix $I$, first scale that row so that its diagonal entry becomes the required non-zero value.

If some diagonal entry of an upper triangular matrix is $0$, it cannot be split into a product of elementary matrices.

Whether or not there are $0$ entries on the main diagonal, the determinant of an upper triangular matrix equals the product of its diagonal entries, just like a diagonal matrix.

#### Turning a square matrix into a diagonal matrix with row additions

Using only row additions, any square matrix can be turned into a diagonal matrix. This example needs both elementary row operations and elementary column operations.

If the first row or first column of the matrix has a non-zero entry, row additions can make the top-left entry non-zero. Then, using elementary row and column operations, every entry of the first row and first column except the top-left one can be made $0$.

If the first row and first column are already all $0$, just move on to the second row and second column.

With this method, we can even require all non-zero entries of the diagonal matrix to be in the top-left part.

If the first row and first column are already all $0$, check whether the remaining rows and columns contain a non-zero entry. If they do, row additions can make some entry of the first row or first column non-zero, which reduces to the first case and makes the top-left entry non-zero.

Only when the remaining rows and columns also have no non-zero entry is it impossible to make the top-left entry non-zero; in that case the remaining matrix is already the zero matrix.

#### Canonical form matrices

With elementary operations, any matrix, of any shape, can be reduced to a canonical form matrix.

A canonical form matrix has an identity matrix $I$ as a submatrix in the top-left corner, and $0$ everywhere else. The reduction works like turning a square matrix into a diagonal matrix, plus scaling to turn the non-zero top-left entries into $1$.

After a matrix is turned into canonical form, the number of entries equal to $1$ is exactly the rank of the matrix.

## Invertible matrices

Let $A$ be an $n\times n$ matrix. If there is an $n\times n$ matrix $B$ with $AB=BA=I$, then $A$ is called an invertible or non-singular matrix, and $B$ is called the inverse of $A$, written $A^{-1}$.

If $A$ is invertible, its inverse is uniquely determined by $A$.

The inverse $A^{-1}$ of an invertible matrix $A$ is also invertible, and the inverse of $A^{-1}$ is $A$.

The product $AB$ of two invertible matrices $A$ and $B$ is also invertible, and its inverse is $B^{-1}A^{-1}$.

The transpose $A^T$ of an invertible matrix $A$ is also invertible, and the inverse of the transpose equals the transpose of the inverse.

### Inverses of elementary matrices

All elementary matrices are invertible, and their inverses are elementary matrices of the same kind:

$$
{D_i(k)}^{-1}=D_i\left(\frac{1}{k}\right)
$$

$$
P_{ij}^{-1}=P_{ij}
$$

$$
T_{ij}(k)^{-1}=T_{ij}(-k)
$$

Clearly the identity matrix $I$ is invertible, and its inverse is $I$.

Elementary operations preserve invertibility: before and after the operation, the matrices are either both invertible or both not invertible.

A matrix $A$ is invertible if and only if it can be written as a product of elementary matrices, that is, if it can be turned into the identity matrix $I$ by elementary operations.

After introducing determinants, we will know that:

A matrix $A$ is invertible if and only if its rank is $n$, if and only if its determinant is non-zero.

A simple notation: let $E_{ij}$ be the $n\times n$ matrix whose entry in row $i$, column $j$ is $1$ and all other entries are zero. Then

-   $D_i(k)=I_n+(k-1)E_{ii}$
-   $P_{ij}=I_n-E_{ii}-E_{jj}+E_{ij}+E_{ji}$
-   $T_{ij}(k)=I_n+kE_{ij}$

This notation also works for their inverses.

## Applications

### Solving systems of linear equations

For a system of linear equations, the coefficients of the unknowns form the coefficient matrix. Appending the constant terms of the system to the right of the coefficient matrix gives the augmented matrix.

Using elementary row operations, we can turn the augmented matrix of the system first into row echelon form and then into reduced row echelon form, which solves the system. This is called solving linear systems by elimination. Gauss–Jordan elimination, covered later, is an elimination algorithm that works in a fixed order.

### Computing determinants

The determinant of a product of square matrices is the product of their determinants, the determinants of elementary matrices are easy to compute, and elementary operations are equivalent to multiplying by elementary matrices. So elementary operations are also used to compute determinants.

Since performing elementary operations in a fixed order makes the program easier to write, determinants can also be computed with the Gauss–Jordan elimination algorithm covered later.
