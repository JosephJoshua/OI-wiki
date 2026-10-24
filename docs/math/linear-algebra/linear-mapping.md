Studying linear maps means studying maps between vector spaces.

Linear maps can be written as matrices, so many concepts about matrices have counterparts for linear maps.

## Linear maps and linear transformations

Let $V$ and $W$ be two vector spaces over a field $F$, and $T$ a map from $V$ to $W$.

If for any vectors $x$ and $y$ in $W$ and any scalars $k$ and $l$ in $F$, we have:

$$
T(kx+ly)=kTx+lTy
$$

then $T$ is called a linear map from $V$ to $W$. If $W=V$, $T$ is called a linear transformation on $V$.

For example, the identity transformation $T_e$ leaves the space unchanged, and the zero transformation $T_0$ maps the space to the zero space.

Let $L(V,W)$ denote the set of all linear maps from $V$ to $W$. The set of all linear transformations $L(V,V)$ is also written $L(V)$.

### Properties

-   A linear map sends the zero vector to the zero vector.
-   A linear map preserves the form of linear operations: applying the map to a linear combination equals the same linear combination of the mapped vectors.
-   A linear map preserves linear dependence: vectors that are linearly dependent before the map are still linearly dependent after it.

But a linear map does not preserve linear independence. Vectors that are linearly independent before the map are not necessarily linearly independent after it.

## Matrix representation of a linear map

Let $V$ have dimension $n$ with basis $\alpha_1,\cdots,\alpha_n$, let $W$ have dimension $m$ with basis $\beta_1,\cdots,\beta_m$, and let $T$ be a linear map from $V$ to $W$.

Write the image of each $\alpha$ under $T$ in terms of the $\beta$:

$$
T\alpha_j=a_{1j}\beta_1+\cdots+a_{mj}\beta_m
$$

In matrix notation:

$$
T(\alpha_1,\cdots,\alpha_n)=(T\alpha_1,\cdots,T\alpha_n)=(\beta_1,\cdots,\beta_m)A
$$

The matrix $A$ is called the matrix representation of the linear map $T$ under these two bases.

## Kernel and image of a linear map

Here the kernel and image are described from the point of view of linear maps. From the matrix representation, we can see that the kernel and image of a linear map agree with the kernel and image of its matrix.

Let $T$ be a linear map from a space $V$ to a space $W$, and let:

$$
N(T)=\{x\in V|Tx=0\}
$$

$$
R(T)=Im(T)=\{y\in W|y=Tx,Vx\in V\}
$$

It is easy to check that $N(T)$ is a subspace of $V$ and $R(T)$ is a subspace of $W$. $N(T)$ and $R(T)$ are called the kernel and the image, the dimension of $N(T)$ is called the **nullity** (or **defect**) of $T$, and the dimension of $R(T)$ is called the **rank** of $T$.

Theorem: let $T$ be a linear map from a space $V$ to a space $W$, with $V$ finite-dimensional. Then $N(T)$ and $R(T)$ are both finite-dimensional, and:

$$
\operatorname{dim} N(T)+\operatorname{dim} R(T)=\operatorname{dim} V
$$

That is, the nullity plus the rank of $T$ equals the dimension of its domain $V$.

## Matrix representation of a linear transformation

Let $V$ have dimension $n$ with basis $\alpha_1,\cdots,\alpha_n$, and let $T$ be a linear transformation on $V$. Then:

$$
T\alpha_j=a_{1j}\alpha_1+\cdots+a_{nj}\alpha_n
$$

In matrix notation:

$$
T(\alpha_1,\cdots,\alpha_n)=(T\alpha_1,\cdots,T\alpha_n)=(\alpha_1,\cdots,\alpha_n)A
$$

The matrix $A$ is called the matrix representation of the linear transformation $T$ under this basis.

By the structure of the space and the linearity of $T$, $T$ is completely determined by $T\alpha_1,\cdots,T\alpha_n$, so $T$ uniquely determines a matrix $A$.

Theorem: let $V$ have dimension $n$ and basis $\alpha_1,\cdots,\alpha_n$. For any $n\times n$ matrix $A$, there is exactly one linear transformation $T$ from $V$ to $V$ whose matrix is $A$.

Corollary: there is a one-to-one correspondence between $L(V,V)$ and all $n\times n$ matrices.

For example, the zero transformation corresponds to the zero matrix, and the identity transformation corresponds to the identity matrix.

## The space of linear transformations

Theorem: $L(V)$ also forms a vector space, with the following operations on $L(V)$: for any $T_1$ and $T_2$ in $L(V)$, any $x$ in $V$, and any $k$ in $F$:

$$
(T_1+T_2)x=T_1x+T_2x
$$

$$
(kT_1)x=k(T_1x)
$$

It is easy to check that $L(V)$ is a vector space over $F$, called the space of linear transformations.

For linear transformations $T_1$ and $T_2$ in $L(V)$, define their product $T_1T_2$ as:

$$
(T_1T_2)x=T_2(T_1x)
$$

One can check that $(T_1T_2)$ is also a linear transformation in $L(V)$, and that multiplication of linear transformations is associative but not commutative, just like matrix multiplication.

For a linear transformation $T_1$ in $L(V)$, if a linear transformation $T_2$ in $L(V)$ satisfies, for every vector $x$ in $V$:

$$
(T_1T_2)x=T_1(T_2x)=x
$$

then $T_2$ is called the inverse transformation of $T_1$, written:

$$
T_2=T_1^{-1}
$$

and we have:

$$
T_1T_2=T_2T_1=T_e
$$

Theorem: let $V$ have dimension $n$ and basis $\alpha_1,\cdots,\alpha_n$, and under this basis let the matrix of $T_1$ be $A$ and the matrix of $T_2$ be $B$. Then:

-   The matrix of the linear transformation $T_1+T_2$ is $A+B$
-   The matrix of the scalar multiple $kT_1$ is $kA$
-   The matrix of the product $T_1T_2$ is $AB$
-   If the inverse of $T_1$ exists, its matrix is $A^{-1}$

## Coordinates

Let the $n$ vectors $x$ form a basis of an $n$-dimensional space $V$. For any vector $y$ in $V$, write $y$ as:

$$
y=a_1x_1+a_2x_2+\cdots+a_nx_n=(x_1,x_2,\cdots,x_n)\begin{pmatrix}a_1\\a_2\\\vdots\\a_n\end{pmatrix}
$$

The column vector:

$$
\begin{pmatrix}a_1\\a_2\\\vdots\\a_n\end{pmatrix}
$$

is called the **coordinates** of $y$ under the basis $x_1,x_2,\cdots,x_n$.

So coordinates are a column vector made of scalars from the field, and should be distinguished from vectors in the abelian group.

## Coordinate transformation formula

Let $V$ have dimension $n$, and let $T$ be a transformation in $L(V)$ whose matrix under the basis $\alpha_1,\cdots,\alpha_n$ is $A$. Let:

$$
\xi=(\alpha_1,\cdots,\alpha_n)\begin{pmatrix}x_1\\x_2\\\vdots\\x_n\end{pmatrix}
$$

and:

$$
T\xi=T(\alpha_1,\cdots,\alpha_n)\begin{pmatrix}y_1\\y_2\\\vdots\\y_n\end{pmatrix}
$$

Then:

$$
T\xi=T(\alpha_1,\cdots,\alpha_n)\begin{pmatrix}y_1\\y_2\\\vdots\\y_n\end{pmatrix}=(\alpha_1,\cdots,\alpha_n)A\begin{pmatrix}x_1\\x_2\\\vdots\\x_n\end{pmatrix}
$$

Every column-vector point in $V$ is essentially of the form "basis times coordinates". A column-vector point $x$ in $V$ itself uses the identity matrix $I$ as its basis, i.e. $x=Ix$.

Only when the basis stays the same and does not move is a plain linear transformation $T$ the same as multiplying the coordinates on the left by an ordinary matrix.

Think of a linear transformation $T$ as a viewing filter on the space $V$. $T$ acts on the space $V$ and distorts it. After the filter is applied, the points themselves have not moved.

This theorem also shows that a linear transformation $T$ on a basis of column vectors is equivalent to multiplying the basis on the right by a transition matrix.

So between different bases, coordinates are related by multiplying on the left by the inverse of the transition matrix.

## Transition matrices

Let the $n$ vectors $x$ and the $n$ vectors $y$ be two bases of a space $V$. For $1\leq i\leq n$, let the coordinates of each vector $y_i$ under the basis $x_1,x_2,\cdots,x_n$ be:

$$
y_i=(x_1,x_2,\cdots,x_n)\begin{pmatrix}a_{1i}\\a_{2i}\\\vdots\\a_{ni}\end{pmatrix}
$$

Then the $n$ vectors $y$ form the matrix on the left side, and the $n$ coordinate vectors form the matrix $A$ on the right side:

$$
(y_1,y_2,\cdots,y_n)=(x_1,x_2,\cdots,x_n)A
$$

The matrix $A$ is called the **transition matrix** from the basis $x_1,x_2\cdots,x_n$ to the basis $y_1,y_2\cdots,y_n$, also called the change-of-basis matrix.

Clearly a transition matrix is invertible. For the equation above, the transition matrix from the basis $y_1,y_2\cdots,y_n$ to the basis $x_1,x_2\cdots,x_n$ is $A^{-1}$.

So a transition matrix is a matrix of scalars from the field, not a matrix formed by vectors of the abelian group; the two should be distinguished.

Let the $n$ vectors $x$ and the $n$ vectors $y$ be two bases of a space $V$. For the same vector $z$ in $V$:

$$
z=(x_1,x_2,\cdots,x_n)\begin{pmatrix}\xi_1\\\xi_2\\\vdots\\\xi_n\end{pmatrix}=(y_1,y_2\cdots,y_n)\begin{pmatrix}\eta_1\\\eta_2\\\vdots\\\eta_n\end{pmatrix}
$$

Substituting the earlier

$$
(y_1,y_2\cdots,y_n)=(x_1,x_2\cdots,x_n)A
$$

by uniqueness we get:

$$
\begin{pmatrix}\xi_1\\\xi_2\\\vdots\\\xi_n\end{pmatrix}=A\begin{pmatrix}\eta_1\\\eta_2\\\vdots\\\eta_n\end{pmatrix}
$$

or

$$
\begin{pmatrix}\eta_1\\\eta_2\\\vdots\\\eta_n\end{pmatrix}=A^{-1}\begin{pmatrix}\xi_1\\\xi_2\\\vdots\\\xi_n\end{pmatrix}
$$

This is a transformation purely between coordinates, and the coordinate transformation formulas all live in the scalar field. As distinguished above, vectors in a vector space or abelian group are "abstract vectors", while coordinates and the entries of transition matrices are in the scalar field and are seen as "concrete vectors". The two kinds of vectors should be treated as "different things".

A matrix can transform the whole space, i.e. all coordinates; as coordinates, column vectors $x$ cover the whole space.

The identity matrix $I$ is made of unit vectors. A matrix $A$ transforms the identity matrix $I$ into the columns of $A$, that is, it maps the unit vectors to the columns of $A$. So multiplying on the left by $A$ can also be seen as applying this transformation to the space.

Multiplying a vector on the left by a matrix can also be seen as multiplying coordinates on the left by a set of vectors. From the point of view of coordinates:

$$
Iy=Xa
$$

The same column vector $y$ has coordinates $y$ in the "normal" space represented by the identity matrix $I$, and its coordinates in the new transformed space are written $a$. So the matrix $X$ is not only a basis of the normal space, but also the transition matrix from the set of vectors $I$ to the set of vectors $X$.

A linear transformation $T$ maps one basis to another, so coordinates are also mapped to other coordinates.

If the transition matrix of the linear transformation $T$ that maps basis $\alpha$ to $\beta$ is $A$, then the basis matrices satisfy $\beta=\alpha A$.

So the relation between coordinates goes exactly the other way. Suppose the coordinates after the linear transformation $T$ are $b$, i.e. we observe coordinates $b$ through the filter. Then the point in $V$ is represented as $\beta b$. To recover it, use the transition matrix and write the point in $V$ as $\alpha Ab$. This makes it clear why the coordinate transformation is multiplication on the left by the inverse of the transition matrix.

## Linear transformations and similar matrices

The relation between a linear transformation $T$ on a space $V$ and a basis $\alpha$ of $V$:

The linear transformation $T$ acts on the basis $\alpha$ and maps it to $T(\alpha)$, which is the same as multiplying $\alpha$ on the right by some $A$, i.e. $T(\alpha)=\alpha A$.

Matrix similarity asks: the same linear transformation $T$ is described by a matrix $B$ in the space $V$ with basis $\beta$, and by a matrix $A$ in the space $V$ with basis $\alpha$.

If the transition matrix is $C$, i.e. $\beta=\alpha C$, how are the two descriptions $B$ and $A$ related?

Since it is the same transformation $T$, we notice that the transition-matrix relation still holds after the transformation, that is:

$$
T(\beta)=T(\alpha)C=\alpha AC
$$

Seen from the basis $\beta$, the linear transformation $T$ is still a right multiplication; converting basis $\beta$ to basis $\alpha$ then multiplies on the right by $C$, and the transition-matrix relation $C$ is kept before and after the transformation:

$$
T(\beta)=\beta B=\alpha CB
$$

This solves the problem:

$$
B=C^{-1}AC
$$

Theorem: for a transformation $T$ in $L(V)$, the matrices of $T$ under different bases are **similar**.

For square matrices $A$ and $B$, if there is an invertible matrix $C$ with $B=C^{-1}AC$, then $A$ and $B$ are similar.

Similarity preserves rank, so similar matrices are equivalent. However, two equivalent matrices are not necessarily similar.

Since similarity is closely tied to the shape of the matrix, it has nothing to do with equivalence of vector sets or with linear systems having the same solutions.

Looking back, matrix similarity is explained by 4 equations: $\beta=\alpha C$, $T(\alpha)=\alpha A$, $T(\beta)=\beta B$, $T(\beta)=T(\alpha)C$.

## References

-   [[Official bilingual / collection] Essence of Linear Algebra - Series P13 09 - Change of basis](https://www.bilibili.com/video/BV1Ls411b7r2)
