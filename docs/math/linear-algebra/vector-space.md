author: codewasp942, Tiphereth-A

A vector space (linear space) generalizes $d$-dimensional Euclidean space ($0\leq d\leq 3$) and similar spaces. For how the related concepts correspond, see [relation between Euclidean space and vector spaces](#relation-between-euclidean-space-and-vector-spaces).

Prerequisites: abelian groups, fields.

Informally, a set that is closed under some operation, where the operation is associative and has an identity element and inverses, forms a group. If the operation is also commutative, it forms an abelian group.

A set closed under the four arithmetic operations forms a field. For the precise definitions, see [basic concepts of abstract algebra](../algebra/basic.md#fields).

## Definition

A vector space (linear space) is a basic concept and a central object of study in linear algebra. It is a module-like algebraic structure made up of a set of vectors $V$, a field $\Bbb{P}$, an addition operation $+$ and scalar multiplication.

Concretely, let $(V,+)$ be an abelian group and $\Bbb{P}$ a field.

Define an operation between numbers in $\Bbb{P}$ and elements of $V$, called **scalar multiplication**: $\cdot:\Bbb{P}\times V\mapsto V$, written $p\cdot v$ or $pv$, where $p$ is in the field $\Bbb{P}$ and $v$ is in the abelian group $V$. This operation must be closed: the result is always defined and also lies in the group $V$.

It must also satisfy the following conditions:

1.  **Distributivity of scalar multiplication over vector addition**: for $\mathbf u,\mathbf v\in V,a\in \Bbb{P}$, $a(\mathbf u+\mathbf v)=a\mathbf u+a\mathbf v$
2.  **Distributivity of scalar multiplication over scalar addition**: for $a,b\in \Bbb{P},\mathbf u\in V$, $(a+b)\mathbf u=a\mathbf u+b\mathbf u$
3.  **Associativity of scalar multiplication (compatible with field multiplication)**: for $a,b\in \Bbb{P},\mathbf u\in V$, $a(b\mathbf u)=(ab)\mathbf u$
4.  **Identity of scalar multiplication**: let $1\in \Bbb{P}$ be the multiplicative identity of $\Bbb{P}$; then for $u\in V$, $1\mathbf u=\mathbf u$

Then the algebraic system $(V,+,\cdot,\mathbb{P})$ is called a **vector space** (**linear space**) over $\Bbb{P}$ formed by $V$ with $+,\cdot$. $\Bbb{P}$ is the **base field** of the vector space, elements of $V$ are called **vectors**, and elements of $\Bbb{P}$ are called **scalars**. When $\Bbb{P}$ is the field of real numbers, it is called a real vector space. When $\Bbb{P}$ is the field of complex numbers, it is called a complex vector space.

Whether it is a list of numbers, an arrow or something else, anything that satisfies the axioms above can be treated as a vector, and so can be studied with the theory of linear algebra.

The zero element of the additive group is called the zero vector, written $\mathbf 0$ or $\mathbf\theta$.

Addition and subtraction of vectors from the original abelian group, together with the newly defined scalar multiplication, are called the **linear operations**.

???+ note "Note"
    For convenience, in what follows:
    
    1.  Elements of $V$ are not written in bold.
    2.  An algebraic system $(V,+,\cdot,\mathbb{P})$ satisfying the definition of a vector space is also called a vector space.
    
    Please keep these distinctions in mind.

### Intuition

Loosely speaking, scalar multiplication corresponds to "**scaling**", and the elements of the base field $\Bbb{P}$ are the scaling "**factors**"; vector addition corresponds to "**combining**" (superposition). The elements of $\Bbb{P}$ also give the range of values a vector's "**coordinates**" can take.

Conditions 1-4 describe how "scaling" and "combining" interact. It helps to think of arrows in the 2D plane.

### Basic properties

???+ note "Note"
    The following properties can be found in group theory and related topics.

For a vector space $(V,+,\cdot,\Bbb{P})$,

1.  $\theta$ is unique
2.  $\forall\alpha\in V$, $-\alpha$ is unique
3.  $\exists 0\in\mathbb{P}$, $\forall\alpha\in V$, $0\alpha=\theta$
4.  $\forall k\in\mathbb{P}$, $k\theta=\theta$
5.  $(-1)\alpha=-\alpha,~\forall\alpha\in V$
6.  No zero divisors: $\forall\alpha\in V,k\in\mathbb{P}$, $k\alpha=\theta\implies k=0\lor\alpha=\theta$
7.  Cancellation law for addition: $\forall\alpha,\beta,\gamma\in V$, $\alpha+\beta=\alpha+\gamma\implies\beta=\gamma$

    > In fact, the cancellation law for addition is a property of abelian groups.

### Examples

1.  $\Bbb{P}^n$ with addition and multiplication over the field $\Bbb{P}$ is a vector space over $\Bbb{P}$. For example, $\Bbb{P}$ can be $\Bbb{R}$, $\Bbb{C}$, $\Bbb{N}_p$ ($p$ prime), and so on.
2.  The $n\times m$ matrices $\Bbb{P}^{n\times m}$ over a field $\Bbb{P}$, with matrix addition and scalar multiplication, form a vector space over $\Bbb{P}$.
3.  The univariate polynomial ring $\Bbb{P}[x]$ over a field $\Bbb{P}$, with polynomial addition and scalar multiplication, forms a vector space over $\Bbb{P}$.
4.  All continuous functions on the interval $[a,b]$ (written $C[a,b]$), with "function addition" and "multiplying a continuous function by a value", form a vector space over the codomain's field.

## Related concepts

### Linear dependence and linear independence

For a vector space $(V,+,\cdot,\Bbb{P})$:

1.  We call $a_1,a_2,\dots,a_n\in V$ a **set of vectors** (vector family) in $V$.
2.  For $k_1,k_2,\dots,k_n\in\Bbb{P}$, $\sum_{i=1}^nk_ia_i$ is called a **linear combination** of $a_1,a_2,\dots,a_n$.
3.  If a vector $\beta\in V$ can be written as a linear combination of $a_1,a_2,\dots,a_n$, we say $\beta$ can be **linearly represented** by $a_1,a_2,\dots,a_n$.
4.  For $k_1,k_2,\dots,k_n\in\Bbb{P}$, if $a_1,a_2,\dots,a_n$ satisfy $\sum_{i=1}^nk_ia_i=\theta\iff k_i=0, i=1,2,\dots,n$, then $a_1,a_2,\dots,a_n$ are called **linearly independent**; otherwise they are **linearly dependent**.

By convention, the zero vector is linearly dependent with any vector.

A linear representation or a linear dependence relation can be written as a matrix product:

$$
\beta=k_1a_1+k_2a_2+\cdots+k_ra_r=(a_1,a_2,\cdots,a_r)\begin{pmatrix} k_1 \\ k_2 \\ \vdots \\ k_r \end{pmatrix}
$$

By convention, the vectors $a$ are written side by side on the left in order, and the scalars $k$ are written vertically on the right in order, forming a "column vector".

Note: this "column vector" of scalars is just convenient formal notation. It is not in the space $V$ and is fundamentally different from the vectors on the left. If the vectors on the left happen to be column vectors, placing them side by side formally gives a "matrix", and the product above is exactly the familiar "matrix times column vector" form.

As shown below, this linear representation is also equivalent to saying that $\beta$ lies in the image space of the matrix $(a_1,a_2\cdots,a_r)$.

By the definition below, the zero vector always lies in the image space. From the viewpoint of linear transformations, linear dependence means that several vectors are mapped to the zero vector, while linear independence means that only the zero vector itself is mapped to the zero vector.

#### Properties

For a vector space $(V,+,\cdot,\Bbb{P})$,

1.  If part of a set of vectors is linearly dependent, the whole set is linearly dependent. If a set is linearly independent, every nonempty subset of it is linearly independent. In short: **"whole independent, part independent"; "part dependent, whole dependent"**.
2.  A set of vectors containing $\theta$ is linearly dependent.
3.  A set of vectors is linearly dependent if and only if some vector in it can be linearly represented by the others.
4.  If $\beta$ can be linearly represented by $a_1,a_2,\dots,a_n$, the representation is unique if and only if $a_1,a_2,\dots,a_n$ are linearly independent.
5.  If $a_1,a_2,\dots,a_n$ are linearly independent, then $\beta$ can be linearly represented by $a_1,a_2,\dots,a_n$ if and only if $a_1,a_2,\dots,a_n,\beta$ are linearly dependent.

### Maximal linearly independent subsets and rank

Linear dependence can be thought of as "redundancy": some vectors in the set can be represented by the others and can be removed. After removing all of them, what remains is a maximal linearly independent subset.

For a vector space $(V,+,\cdot,\Bbb{P})$:

1.  For a set of vectors $b_1,b_2,\dots,b_m$, let $\{a_1,a_2,\dots,a_n\}\subseteq\{b_1,b_2,\dots,b_m\}$. If:

    -   $a_1,a_2,\dots,a_n$ are linearly independent;
    -   $\forall\beta\in\{b_1,b_2,\dots,b_m\}\setminus\{a_1,a_2,\dots,a_n\}$, $a_1,a_2,\dots,a_n,\beta$ are linearly dependent,

    then $a_1,a_2,\dots,a_n$ is called a **maximal linearly independent subset** of $b_1,b_2,\dots,b_m$. A maximal linearly independent subset of the vector space $V$ is defined similarly.

    By convention, the maximal linearly independent subset of $\theta,\theta,\dots,\theta$ is the empty set, so the vectors of an all-zero matrix have no (nonempty) maximal linearly independent subset.

    There is more than one way to remove vectors from a set, so the maximal linearly independent subset is not unique either. By habit, we remove vectors from left to right in order.

    Conveniently, if we remove them in order, the vectors that remain are exactly the columns containing the leading $1$s in the reduced row echelon form produced by Gaussian elimination, in the "row view".

    The size of a maximal linearly independent subset of $b_1,b_2,\dots,b_m$ is called the **rank** of the set, written $\operatorname{rank}\{b_1,b_2,\dots,b_m\}$. By convention, $\operatorname{rank}\{\theta,\theta,\dots,\theta\}=0$.

    So the rank of a set of vectors is defined in exactly the same way as the rank of a matrix.

2.  If every vector in $b_1,b_2,\dots,b_m$ can be linearly represented by $a_1,a_2,\dots,a_n$, we say $b_1,b_2,\dots,b_m$ can be linearly represented by $a_1,a_2,\dots,a_n$.

3.  If $a_1,a_2,\dots,a_n$ can be linearly represented by $b_1,b_2,\dots,b_m$, and $b_1,b_2,\dots,b_m$ can be linearly represented by $a_1,a_2,\dots,a_n$, the two sets are called **equivalent**, written $\{a_1,a_2,\dots,a_n\}\cong\{b_1,b_2,\dots,b_m\}$.

    Two sets of vectors are **equivalent** exactly when they span the same space. Sets spanning the same space are equivalent; sets spanning different spaces are not.

    Equivalence of vector sets is stronger than matrix equivalence: it requires not only the same rank but exactly the same space. So placing the two matrices side by side **horizontally** must not change the rank.

    Matrix equivalence only requires equal rank, so it means the first matrix or space can be turned into the second one by invertible transformations.

#### Properties

For a vector space $(V,+,\cdot,\Bbb{P})$,

1.  Suppose $a_1,a_2,\dots,a_n$ can be linearly represented by $b_1,b_2,\dots,b_m$.
    -   If $n>m$, then $a_1,a_2,\dots,a_n$ are linearly dependent.
    -   If $a_1,a_2,\dots,a_n$ are linearly independent, then $n\leq m$.

2.  Equivalent linearly independent sets have the same size.

    All maximal linearly independent subsets of a set of vectors have the same size.

3.  A set of vectors is linearly independent if and only if its rank equals its size.

4.  If $a_1,a_2,\dots,a_n$ can be linearly represented by $b_1,b_2,\dots,b_m$, then $\operatorname{rank}\{a_1,a_2,\dots,a_n\}\leq\operatorname{rank}\{b_1,b_2,\dots,b_m\}$.

5.  Equivalent sets of vectors have equal rank.

### Linear span

For a vector space $(V,+,\cdot,\Bbb{P})$, $\left\{v=\sum_{i=1}^nk_ia_i:a_i\in V,k_i\in\Bbb{P},i=1,2,\dots,n\right\}$ is also a vector space. It is called the space **spanned** by $a_1,a_2,\dots,a_n$ (or their **linear span**), written $\operatorname{span}\{a_1,a_2,\dots,a_n\}$.

The $n$ vectors $a$ here need not be linearly independent.

### Linear subspaces

For a vector space $(V,+,\cdot,\Bbb{P})$, if the algebraic system $(V_1,+,\cdot,\Bbb{P})$ satisfies:

1.  $\varnothing\ne V_1$
2.  $V_1\subseteq V$
3.  $V_1$ is a vector space over $\mathbb{P}$ with $+,\cdot$

then $V_1$ is called a linear subspace of $V$, or just a subspace, written $V_1\leq V$.

Every space $V$ has two **trivial subspaces**: $V$ itself and the zero subspace. The zero subspace contains only the zero vector and has no linearly independent vectors.

If $\subseteq$ in condition 2 is replaced by $\subset$, $V_1$ is called a proper linear subspace of $V$, written $V_1<V$.

It is not hard to prove that a nonempty subset $V_1$ of a vector space $V$ is a linear subspace if and only if $V_1$ is closed under the linear operations, that is:

1.  $\forall u,v\in V_1$, $u+v\in V_1$
2.  $\forall v\in V_1$, $\forall k\in \Bbb{P}$, $kv\in V_1$

### Intersection, sum, direct sum and direct product

For vector spaces $(V_1,+,\cdot,\Bbb{P})$ and $(V_2,+,\cdot,\Bbb{P})$:

1.  It is easy to check that addition and scalar multiplication are closed on $V_1\cap V_2$, so $V_1\cap V_2$ is called the **intersection** of the vector spaces $V_1$ and $V_2$.

    The intersection of several vector spaces $\bigcap_{i=1}^m V_i$ is defined similarly.

2.  If a vector space $V$ satisfies $V=\{u+v|u\in V_1,v\in V_2\}$, then $V$ is called the **sum** of the vector spaces $V_1$ and $V_2$, written $V=V_1+V_2$.

    One can check that $V_1+V_2$ is the smallest subspace containing $V_1\cup V_2$.

    The sum of several vector spaces $\sum_{i=1}^m V_i$ is defined similarly.

3.  Let $V=V_1+V_2$. If for every element $v$ of $V$ there is exactly one pair of vectors $v_1,v_2$ with $v=v_1+v_2$, then $V$ is called the **direct sum** of $V_1$ and $V_2$, written $V_1\oplus V_2$.

    The direct sum of several vector spaces $\bigoplus_{i=1}^m V_i$ is defined similarly.

4.  The **direct product** $V_1\times V_2$ of $V_1$ and $V_2$ is defined as their Cartesian product, which forms a vector space over $\Bbb{P}$ with the following addition and scalar multiplication:

    1.  $+:(V_1\times V_2)\times(V_1\times V_2)\mapsto V_1\times V_2; ((u_1,v_1),(u_2,v_2))\to (u_1+u_2,v_1+v_2)$
    2.  $\cdot:\Bbb{P}\times(V_1\times V_2)\mapsto V_1\times V_2; (k,(u,v))\to (ku,kv)$

    The direct product of several vector spaces $\prod_{i=1}^m V_i$ is defined similarly.

#### Example

For the vector space $V=\Bbb{R}^3$, define the vector spaces:

-   $V_1:=\{(x,0,0)|x\in\Bbb{R}\}$
-   $V_2:=\{(x,y,0)|x,y\in\Bbb{R}\}$
-   $V_3:=\{(0,y,z)|y,z\in\Bbb{R}\}$
-   $V_4:=\{(x,0,z)|x,z\in\Bbb{R}\}$

Then

1.  $V_1<V_2<V$, $V_3<V$
2.  $V_2=V_1+V_2$
3.  $V=V_1\oplus V_3=V_2+V_3$
4.  $V_2+V_3\leq V$

#### Properties

1.  Let $V_1,V_2,V_3$ be vector spaces over $\Bbb{P}$. Like intersections of sets, intersections of vector spaces obey:
    1.  Commutativity: $V_1\cap V_2=V_2\cap V_1$
    2.  Associativity: $V_1\cap(V_2\cap V_3)=(V_1\cap V_2)\cap V_3$
2.  Let $V_1,V_2,V_3$ be vector spaces over $\Bbb{P}$. Similar to unions of sets, sums of vector spaces obey:
    1.  Commutativity: $V_1+V_2=V_2+V_1$
    2.  Associativity: $V_1+(V_2+V_3)=(V_1+V_2)+V_3$
3.  Let $V_1,V_2,V_3$ be vector spaces over $\Bbb{P}$. Intersections and sums of vector spaces are related as follows:
    1.  $V_1\cap (V_2+V_3)\supseteq (V_1\cap V_2)+(V_1\cap V_3)$
    2.  $V_1+(V_2\cap V_3)\subseteq (V_1+V_2)\cap (V_1+V_3)$
4.  $\operatorname{span}\{a_1,a_2,\dots,a_n\}+\operatorname{span}\{b_1,b_2,\dots,b_m\}=\operatorname{span}\{a_1,a_2,\dots,a_n,b_1,b_2,\dots,b_m\}$
5.  Let $V_1,V_2$ be vector spaces over $\Bbb{P}$. Then the following are equivalent:

    1.  $V_1+V_2=V_1\oplus V_2$

    2.  $\exists \beta\in V_1+V_2$ that can be split into a sum of vectors from $V_1$ and $V_2$ in exactly one way ("for all" weakened to "there exists")

    3.  $\theta$ can be split into a sum of vectors from $V_1$ and $V_2$ in exactly one way

    4.  $V_1\cap V_2=\{\theta\}$

    ???+ note "Proof"
        $1\implies 2$: immediate from the definition.
        
        $2 \implies 3$:
        
        Let $\beta=\beta_1+\beta_2$ with $\beta_1\in V_1, \beta_2\in V_2$. If $\theta=\alpha_1+\alpha_2$ with $\theta\ne\alpha_1\in V_1,\alpha_2\in V_2$, then $\beta=\beta+\theta=(\beta_1+\alpha_1)+(\beta_2+\alpha_2)$.
        
        But $\beta_1\ne\beta_1+\alpha_1$, which contradicts the assumption.
        
        $3 \implies 4$:
        
        Take a nonzero vector $\alpha$ in both $V_1$ and $V_2$. Then $\theta=\alpha+(-\alpha)=(-\alpha)+\alpha$, which contradicts the assumption.
        
        $4 \implies 1$:
        
        If $V_1+V_2$ is not a direct sum, there is $\beta\in V_1+V_2$ with $\beta=\beta_1+\beta_2=\gamma_1+\gamma_2$, where $\beta_1,\gamma_1\in V_1,\beta_2,\gamma_2\in V_2$ and $\beta_1,\beta_2,\gamma_1,\gamma_2$ are pairwise distinct.
        
        Then $\theta\ne\beta_1-\gamma_1=\gamma_2-\beta_2\in V_1\cap V_2$, which contradicts the assumption.

### Isomorphism

Let $V,V'$ be vector spaces over a field $\Bbb{P}$. If there is a bijection $\sigma:V\mapsto V'$ that preserves addition and scalar multiplication, that is, $\forall u,v\in V$, $\forall k\in\Bbb{P}$:

1.  $\sigma(u+v)=\sigma(u)+\sigma(v)$
2.  $\sigma(ku)=k\sigma(u)$

then $\sigma$ is called an **isomorphism** from $V$ to $V'$, and $V$ and $V'$ are called **isomorphic**, written $V\cong V'$.

???+ note "Note"
    If $\sigma$ is injective, we get a **monomorphism**; if $\sigma$ is surjective, we get an **epimorphism**.

#### Properties

1.  Two vector spaces over a field $\Bbb{P}$ are isomorphic if and only if they have the same dimension. (For the definition of dimension, see [basis](./basis.md).)
2.  (Corollary of 1) Every $n$-dimensional vector space over $\Bbb{P}$ is isomorphic to $\Bbb{P}^n$.

    ???+ note "Note"
        This property shows that we can basically treat coordinates and vectors as the same thing.

## Relation between Euclidean space and vector spaces

Take the familiar 3D Euclidean space as an example. Some of its concepts correspond to concepts in vector spaces as follows:

| 3D Euclidean space | Vector space |
| ------------------ | ------------ |
| Vector | Vector |
| Perpendicular | Orthogonal (inner product is $0$) |
| Three vectors collinear/coplanar | $k$ vectors linearly dependent |
| Three vectors not coplanar | $k$ vectors linearly independent |
| Basis vectors | [Basis](./basis.md) |
| Dimension of the space | Dimension of the space |

## Applications

From this section on, we mainly take the "column view" of systems of linear equations.

The matrix $A$ is itself made up of column vectors. We view $A$ as a set of column vectors and $x$ as the unknown coefficients, and ask whether the column vectors of $A$, with suitable coefficients, can add up to the column vector $b$. Here the column vector $x$ is completely unknown.

The equation $Ax=b$ then becomes:

$$
\alpha_1 x_1 +\alpha_2 x_2 +\cdots+\alpha_n x_n=b 
$$

In this matrix product, the matrix $A$ on the left can be seen as a set of vectors, namely its column vectors. These column vectors, as a basis, span a space, and we ask whether the column vector $b$ lies in this space.

### Solutions of linear systems in the column view

The rank is the number of vectors in a maximal linearly independent subset, and it represents the "constraints". The remaining vectors give the solution its degrees of freedom: they allow redundant vectors in other directions.

Let $n$ be the number of columns of $A$, that is, the number of column vectors, and let $r(A)$ be the rank of A. Then the number of degrees of freedom $S$ is:

$$
S=n-r(A)
$$

The set of all solutions of a system also forms a set of vectors. The degrees of freedom $S$ equal the rank of the solution vectors of $Ax=0$, that is, the dimension of the null space defined below.

### Systems with the same solutions

The common solutions of two systems are defined as the intersection of their solution sets.

Two systems have **the same solutions** when their solution sets are equal. Systems with equal solution sets have the same solutions; systems with different solution sets do not.

Having the same solutions is also stronger than matrix equivalence: it requires not only equal rank but also that stacking the two matrices **vertically** does not change the rank.

Compare this with equivalence of vector sets, which requires that joining the matrices horizontally does not change the rank. So we have the following relations:

If two matrices are equivalent, the corresponding vector sets need not be equivalent and the corresponding systems need not have the same solutions. But if the vector sets are equivalent or the systems have the same solutions, the corresponding matrices must be equivalent (have the same rank).

If the vector sets of two matrices are equivalent, then after transposing the matrices the corresponding systems have the same solutions, and vice versa.

### Null space and image space of a matrix

The null space and image space here are described from the viewpoint of vector spaces.

For a matrix $A$, let $W$ be the set of all solutions $x$ of $Ax=0$. Then $W$ is a vector space, and its scalar field is the same as the field containing the entries of $A$.

This $W$ is called the **null space** (kernel) of $A$, written $N(A)$.

The null space $N(A)$ is exactly the **solution space** of $Ax=0$. By the definition of a basis given later, a **fundamental system of solutions** of this equation is a basis of the null space.

If $A$ is invertible, its null space $N(A)$ contains only the zero vector.

For a matrix $A$ whose $n$ columns are the vectors $\alpha$, the space spanned by these $n$ column vectors is called the **image space** of $A$, also called the **column space**, written:

$$
R(A)=\operatorname{span}\{\alpha_1,\alpha_2,\cdots,\alpha_n\}
$$

By the definition of dimension given later, the dimension of the image space equals the rank of $A$.

By definition, every element $y$ of the image space $R(A)$ can be written as:

$$
y=k_1\alpha_1+k_2\alpha_2+\cdots+k_n\alpha_n=(\alpha_1,\alpha_2,\cdots,\alpha_n)\begin{pmatrix}k_1\\k_2\\\vdots\\k_n\end{pmatrix}=A\begin{pmatrix}k_1\\k_2\\\vdots\\k_n\end{pmatrix}
$$

So the image space $R(A)$ is exactly the **range** of $Ax$ over all vectors $x$.

Similarly, the **row space** of $A$ is defined as the range of the transpose of $A$, $R(A^T)$.

Since the row rank of a matrix equals its column rank, the dimension of the row space is also the rank of the matrix. So transposing changes the image space but not its dimension.

We can now connect this with the earlier discussion:

Two vector sets are equivalent if and only if the corresponding matrices have the same image space $R(A)$.

Two systems have the same solutions if and only if the corresponding matrices have the same row space $R(A^T)$.

## References and notes

1.  Qiu Weisheng, *Higher Algebra (Volume 2)*. Tsinghua University Press.
2.  [Vector space](https://en.wikipedia.org/w/index.php?title=Vector_space&oldid=1108546097).*Wikipedia, The Free Encyclopedia*.
