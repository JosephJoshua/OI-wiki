This page introduces some simple operations between vectors.

Before we start, a quick note on terminology. For historical reasons, Chinese mathematics and physics use a confusing variety of translations for "inner product" and "outer product".

In Chinese physics they are usually called by names meaning "scalar product" and "vector product", which describe whether the result is a scalar or a vector. Chinese high school math textbooks also use descriptive names of this kind ("quantity product" and "vector product").

In mathematics they are usually translated literally as "inner product" and "outer product". The informal names "dot product" and "cross product" come from the operator symbols, and they are also very common.

In the "dot product", the dot is often omitted. In linear algebra it is simply treated as matrix multiplication and written without the dot.

## Inner product

The inner product **makes sense for vectors of any dimension**.

### Definition

There are several different but equivalent ways to define the inner product. Some of them are given below.

#### Geometric definition

In $n$-dimensional Euclidean space $\mathbf{R}^n$, given two vectors $\boldsymbol{a}, \boldsymbol{b}$ with angle $\theta$ between them,

$$
\boldsymbol{a} \cdot \boldsymbol{b} = |\boldsymbol{a}| |\boldsymbol{b}| \cos \theta
$$

is the **inner product** of the two vectors, also called the **dot product** or **scalar product**. Here $|\boldsymbol{b}|\cos \theta$ is called the projection of $\boldsymbol{b}$ onto the direction of $\boldsymbol{a}$. Geometrically, the inner product $\boldsymbol{a} \cdot \boldsymbol{b}$ equals the magnitude of $\boldsymbol{a}$ times the projection of $\boldsymbol{b}$ onto the direction of $\boldsymbol{a}$.

#### Algebraic definition

In $n$-dimensional Euclidean space $\mathbf{R}^n$, given two vectors $\boldsymbol{a} = (a_1, a_2, \dots, a_n), \boldsymbol{b} = (b_1, b_2, \dots, b_n)$,

$$
\boldsymbol{a} \cdot \boldsymbol{b} = \sum_{i = 1}^{n} a_i b_i
$$

is the **inner product** of the two vectors, also called the **dot product** or **scalar product**. In Euclidean space the geometric and algebraic definitions are equivalent, and the algebraic one is easier to use.

When there is no risk of confusion, the dot can be omitted. A superscript $2$ on a vector is shorthand for the inner product of the vector with itself, that is, **the square of its length**, with the magnitude bars left out. This superscript $2$ must not be read as "the square of a vector": the inner product of two vectors is a scalar, so there is no inner product of any number of vectors other than $2$. For the same reason, the square of the squared length cannot be written with a superscript $4$; you must treat the result of the superscript $2$ as a single quantity, and so on.

### Properties

The result of an inner product is a scalar. What makes it special is that it is a bilinear operation: it is linear in each of the two vectors separately. Concretely, the inner product satisfies:

$$
\begin{aligned}
(\boldsymbol{a} + \boldsymbol{b}) \cdot \boldsymbol{c} &= \boldsymbol{a} \cdot \boldsymbol{c} + \boldsymbol{b} \cdot \boldsymbol{c} \\
\boldsymbol{a} \cdot (\boldsymbol{b} + \boldsymbol{c}) &= \boldsymbol{a} \cdot \boldsymbol{b} + \boldsymbol{a} \cdot \boldsymbol{c} \\
(\lambda \boldsymbol{a}) \cdot \boldsymbol{b} &= \lambda (\boldsymbol{a} \cdot \boldsymbol{b}) \\
\boldsymbol{a} \cdot (\lambda \boldsymbol{b}) &= \lambda (\boldsymbol{a} \cdot \boldsymbol{b})
\end{aligned}
$$

The inner product is also commutative:

$$
\boldsymbol{a} \cdot \boldsymbol{b} = \boldsymbol{b} \cdot \boldsymbol{a}
$$

### Applications

Here are some common uses of the inner product.

1.  Testing whether two vectors are perpendicular:

    $$
    \boldsymbol{a} \perp \boldsymbol{b} \iff \boldsymbol{a} \cdot \boldsymbol{b} = 0
    $$

    So the inner product of two perpendicular vectors is $0$, and the inner product of any vector with the zero vector is $0$. If we define "perpendicular" as "inner product equal to zero", then the zero vector is perpendicular to every vector.

2.  Testing whether two vectors are collinear:

    $$
    \exists\lambda \in \mathbf{R} (\boldsymbol{a} = \lambda \boldsymbol{b}) \iff |\boldsymbol{a} \cdot \boldsymbol{b}| = |\boldsymbol{a}| |\boldsymbol{b}|
    $$

3.  Computing the magnitude of a vector:

    $$
    |\boldsymbol a| = \sqrt{\boldsymbol{a} \cdot \boldsymbol{a}}
    $$

4.  Computing the angle between two vectors:

    $$
    \theta = \arccos \frac{\boldsymbol{a} \cdot \boldsymbol{b}}{|\boldsymbol a| |\boldsymbol b|}
    $$

## Determinants of order 2 and 3

Determinants of order 2 and 3 can be defined directly as simple special cases of the determinant. In the field theory part at the end of calculus, Green's theorem uses a 2nd-order determinant, Gauss's (divergence) theorem uses the dot product, and Stokes' theorem uses a 3rd-order determinant.

A 2nd-order determinant can be seen as a function of four variables, defined as:

$$
\begin{vmatrix}
    a & b \\
    c & d
\end{vmatrix}=ad-bc
$$

A 3rd-order determinant can be seen as a function of nine variables, defined as:

$$
\begin{vmatrix}
    a & b & c \\
    d & e & f \\
    g & h & i
\end{vmatrix}=aei+dhc+gbf-ahf-dbi-gec
$$

A handy way to remember these is the "diagonal rule" (Sarrus' rule), which only works for determinants of order 2 and 3.

Be careful: a 4th-order determinant has 24 terms when expanded, and the anti-diagonal term has a positive sign. If you force the "diagonal rule" for order 3 onto it, not only are there too few terms, the sign of the anti-diagonal term is also wrong. So the diagonal rule does not work for higher-order determinants, and higher-order determinants are not well suited to direct expansion either.

## Outer product

The outer product (cross product) is **an operation specific to 3D vectors**.

In physics, 3D vectors are by default vectors tied to positions in space and are always written in bold. However, the 4-vectors of relativity are not written in bold; they use special notation and indices.

In linear algebra, all vectors are written in bold. Since this is tedious to do by hand, and linear algebra is mostly about operations on vectors and matrices where ambiguity is rare, the vector notation can be omitted in handwriting.

### Definition

There are several different but equivalent ways to define the outer product. Some of them are given below.

#### Geometric definition

In 3D Euclidean space $\mathbf{R}^3$, the outer product of vectors $\boldsymbol{a}, \boldsymbol{b}$ is defined to be a vector, written $\boldsymbol{a} \times \boldsymbol{b}$, whose magnitude and direction are:

1.  $|\boldsymbol{a} \times \boldsymbol{b}| = |\boldsymbol{a}| |\boldsymbol{b}| \sin \langle \boldsymbol{a}, \boldsymbol{b} \rangle$;
2.  $\boldsymbol{a} \times \boldsymbol{b}$ is perpendicular to both $\boldsymbol{a}$ and $\boldsymbol{b}$, and the directions of $\boldsymbol{a}, \boldsymbol{b}, \boldsymbol{a} \times \boldsymbol{b}$ follow the right-hand rule.

Look at the magnitude of the outer product and recall the triangle area formula $S=\frac{1}{2}ab\sin C$. We see the geometric meaning of the outer product: **$|\boldsymbol{a} \times \boldsymbol{b}|$ is the area of the parallelogram with sides $\boldsymbol{a}, \boldsymbol{b}$**.

#### Algebraic definition

In 3D Euclidean space $\mathbf{R}^3$, the outer product of vectors $\boldsymbol{a} = (x_1, y_1, z_1), \boldsymbol{b} = (x_2, y_2, z_2)$ is defined to be a vector $\boldsymbol{c}$, written $\boldsymbol{c} = \boldsymbol{a} \times \boldsymbol{b}$. It can be written as a 3rd-order determinant:

$$
\begin{vmatrix}
    \boldsymbol{i} & \boldsymbol{j} & \boldsymbol{k} \\
    x_1 & y_1 & z_1  \\
    x_2 & y_2 & z_2
\end{vmatrix}
$$

Here $\boldsymbol{i}, \boldsymbol{j}, \boldsymbol{k}$ are the unit vectors along the coordinate axes $x, y, z$, placed in the matching coordinate positions. Expanding gives

$$
\begin{aligned}
\boldsymbol{c} &= \boldsymbol{a} \times \boldsymbol{b} \\
&= (y_1z_2 - y_2z_1)\boldsymbol{i} + (z_1x_2 - z_2x_1)\boldsymbol{j} + (x_1y_2 - x_2y_1)\boldsymbol{k} \\
&= (y_1z_2 - y_2z_1, z_1x_2 - z_2x_1, x_1y_2 - x_2y_1)
\end{aligned}
$$

### Properties

1.  The outer product is a bilinear operation: it is linear in each of the two vectors separately. Concretely, it satisfies:

    $$
    \begin{aligned}
    (\boldsymbol{a} + \boldsymbol{b}) \times \boldsymbol{c} &= \boldsymbol{a} \times \boldsymbol{c} + \boldsymbol{b} \times \boldsymbol{c} \\
    \boldsymbol{a} \times (\boldsymbol{b} + \boldsymbol{c}) &= \boldsymbol{a} \times \boldsymbol{b} + \boldsymbol{a} \times \boldsymbol{c} \\
    (\lambda \boldsymbol{a}) \times \boldsymbol{b} &= \lambda (\boldsymbol{a} \times \boldsymbol{b}) \\
    \boldsymbol{a} \times (\lambda \boldsymbol{b}) &= \lambda (\boldsymbol{a} \times \boldsymbol{b})
    \end{aligned}
    $$

    The first two lines are also called the distributive law: the outer product distributes over vector addition.

2.  The outer product is anti-commutative:

    $$
    \boldsymbol a \times \boldsymbol b=-\boldsymbol b \times \boldsymbol a
    $$

3.  From the geometric definitions of the inner and outer products above:

    $$
    \begin{aligned}
    |\boldsymbol a \times \boldsymbol b| &= |\boldsymbol a| |\boldsymbol b| \sin \langle \boldsymbol a, \boldsymbol b \rangle \\
    \boldsymbol a \cdot \boldsymbol b &= |\boldsymbol a| |\boldsymbol b| \cos \theta \\
    &= |\boldsymbol a| |\boldsymbol b| \cos \langle \boldsymbol a, \boldsymbol b\rangle
    \end{aligned}
    $$

    we get the identity:

    $$
    (\boldsymbol a\times \boldsymbol b) \cdot (\boldsymbol a\times \boldsymbol b) = |\boldsymbol a|^2 |\boldsymbol b|^2-{(\boldsymbol a \cdot \boldsymbol b)}^2
    $$

4.  The outer product satisfies the Jacobi identity:

    $$
    \boldsymbol a \times (\boldsymbol b \times \boldsymbol c) + \boldsymbol b \times (\boldsymbol c \times \boldsymbol a) + \boldsymbol c \times (\boldsymbol a \times \boldsymbol b) = \boldsymbol 0
    $$

### Applications

Here are some common uses of the outer product.

1.  Testing whether two vectors are collinear:

    $$
    \exists\lambda \in \mathbf{R} (\boldsymbol{a} = \lambda \boldsymbol{b}) \iff \boldsymbol{a} \times \boldsymbol{b} = \boldsymbol{0}
    $$

    So the outer product of two collinear 3D vectors is $\boldsymbol 0$; the outer product of a 3D vector with itself is $\boldsymbol 0$; the outer product of a 3D vector with the zero vector is $\boldsymbol 0$. If we define "collinear" as "outer product equal to zero", then the zero vector is collinear with every vector.

2.  Computing the area of the parallelogram spanned by two vectors:

    $$
    S \langle \boldsymbol a, \boldsymbol b \rangle = |\boldsymbol a \times \boldsymbol b|
    $$

#### The 2D case

For 2D vectors, the outer product cannot be computed, but we can still compute the area of the parallelogram spanned by two vectors:

Let $\boldsymbol{a} = (m, n), \boldsymbol{b} = (p, q)$. Extend the Cartesian plane to 3D Cartesian coordinates, with the original plane as the $xOy$ plane of the new system. The coordinates $(m, n)$ and $(p, q)$ become $(m, n, 0)$ and $(p, q, 0)$.

The outer product of the two vectors is then $(0, 0, mq - np)$, so the area of the parallelogram is $|mq - np|$. This can be seen as the absolute value of a 2nd-order determinant.

Also, from the right-hand rule and the sign of the $z$ coordinate, we can tell which way $\boldsymbol b$ lies relative to $\boldsymbol a$: if it is counterclockwise, the $z$ coordinate is positive; otherwise it is negative. A short way to remember this: **clockwise negative, counterclockwise positive**.

## Mixed product

Like the outer product, the mixed product (scalar triple product) is **an operation specific to 3D vectors**.

### Definition

Let $\boldsymbol a, \boldsymbol b, \boldsymbol c$ be three vectors in 3D space. Then $(\boldsymbol a \times \boldsymbol b) \cdot \boldsymbol c$ is called the mixed product of $\boldsymbol a, \boldsymbol b, \boldsymbol c$, written $[\boldsymbol a \boldsymbol b \boldsymbol c]$, $(\boldsymbol a, \boldsymbol b, \boldsymbol c)$, $(\boldsymbol a \boldsymbol b \boldsymbol c)$ or $\det(\boldsymbol a, \boldsymbol b, \boldsymbol c)$. Geometrically, its absolute value $|(\boldsymbol a \times \boldsymbol b) \cdot \boldsymbol c|$ is the volume of the parallelepiped with edges $\boldsymbol a, \boldsymbol b, \boldsymbol c$.

The mixed product can be written as a 3rd-order determinant:

$$
\begin{aligned}
(\boldsymbol a \times \boldsymbol b) \cdot \boldsymbol c &= \det(\boldsymbol a, \boldsymbol b, \boldsymbol c) \\
&= \begin{vmatrix}
    a_x & b_x & c_x \\
    a_y & b_y & c_y \\
    a_z & b_z & c_z
\end{vmatrix} \\
&= a_x b_y c_z + a_y b_z c_x + a_z b_x c_y - a_z b_y c_x -a _y b_x c_z - a_x b_z c_y
\end{aligned}
$$

### Properties

1.  The mixed product is linear in each of the three vectors separately. Concretely:

    $$
    \begin{aligned}
    \det(\lambda\boldsymbol{u} + \mu\boldsymbol{v}, \boldsymbol{b}, \boldsymbol{c}) &= \lambda\det(\boldsymbol{u}, \boldsymbol{b}, \boldsymbol{c}) + \mu\det(\boldsymbol{v}, \boldsymbol{b}, \boldsymbol{c}) \\
    \det(\boldsymbol{a}, \lambda\boldsymbol{u} + \mu\boldsymbol{v}, \boldsymbol{c}) &= \lambda\det(\boldsymbol{a}, \boldsymbol{u}, \boldsymbol{c}) + \mu\det(\boldsymbol{a}, \boldsymbol{v}, \boldsymbol{c}) \\
    \det(\boldsymbol{a}, \boldsymbol{b}, \lambda\boldsymbol{u} + \mu\boldsymbol{v}) &= \lambda\det(\boldsymbol{a}, \boldsymbol{b}, \boldsymbol{u}) + \mu\det(\boldsymbol{a}, \boldsymbol{b}, \boldsymbol{v})
    \end{aligned}
    $$

2.  The mixed product is antisymmetric: swapping two of the vectors negates it. So:

    $$
    \det(\boldsymbol a, \boldsymbol b, \boldsymbol c) = \det(\boldsymbol b, \boldsymbol c, \boldsymbol a) = \det(\boldsymbol c, \boldsymbol a, \boldsymbol b) = -\det(\boldsymbol b, \boldsymbol a, \boldsymbol c) = -\det(\boldsymbol a, \boldsymbol c, \boldsymbol b)= -\det(\boldsymbol c, \boldsymbol b, \boldsymbol a)
    $$

    From this we also get the following relation between the inner and outer products:

    $$
    (\boldsymbol a \times \boldsymbol b) \cdot \boldsymbol c = \boldsymbol a \cdot (\boldsymbol b \times \boldsymbol c)
    $$

### Applications

Common uses of the mixed product:

1.  Computing the volume of tetrahedron $ABCD$:

    $$
    V=\frac{1}{6}\left|\det(\overrightarrow{AB}, \overrightarrow{AC}, \overrightarrow{AD})\right|
    $$

2.  Testing whether $\boldsymbol a, \boldsymbol b, \boldsymbol c$ are coplanar;

    Three 3D vectors $\boldsymbol a, \boldsymbol b, \boldsymbol c$ are coplanar if and only if $\det(\boldsymbol a, \boldsymbol b, \boldsymbol c)=0$.

3.  Determining the handedness of the coordinate system formed by $\boldsymbol a, \boldsymbol b, \boldsymbol c$;

    Whether the mixed product $\det(\boldsymbol a, \boldsymbol b, \boldsymbol c)$ is positive or negative depends on whether the angle between $\boldsymbol a \times \boldsymbol b$ and $\boldsymbol c$ is acute or obtuse, that is, whether they point to the same side or opposite sides of the plane spanned by $\boldsymbol a$ and $\boldsymbol b$. This is the same as asking whether $\boldsymbol a, \boldsymbol b, \boldsymbol c$, in this order, form a right-handed or a left-handed system. Concretely:

    -   $\det(\boldsymbol a, \boldsymbol b, \boldsymbol c) < 0$ is equivalent to $\boldsymbol a, \boldsymbol b, \boldsymbol c$, in this order, forming a left-handed system;
    -   $\det(\boldsymbol a, \boldsymbol b, \boldsymbol c) > 0$ is equivalent to $\boldsymbol a, \boldsymbol b, \boldsymbol c$, in this order, forming a right-handed system.

## Vector triple product

The mixed product of 3D vectors combines the inner and outer products and has cyclic symmetry. The outer product of two 3D vectors is again a 3D vector, so is there a result for the outer product of an outer product?

First we prove a lemma.

$$
(\boldsymbol a \times \boldsymbol b)\times \boldsymbol a = (\boldsymbol a \cdot \boldsymbol a) \boldsymbol b - (\boldsymbol a \cdot \boldsymbol b) \boldsymbol a
$$

Proof: by the right-hand rule, $\boldsymbol a \times \boldsymbol b$ is perpendicular to both $\boldsymbol a$ and $\boldsymbol b$. The left-hand side of the claimed identity is perpendicular to $\boldsymbol a \times \boldsymbol b$, so it lies in the same plane as $\boldsymbol a$ and $\boldsymbol b$.

So we can write:

$$
(\boldsymbol a \times \boldsymbol b)\times \boldsymbol a = \lambda \boldsymbol a + \mu \boldsymbol b
$$

Using the results about the mixed product, take the inner product of both sides with $\boldsymbol a$ and with $\boldsymbol b$:

$$
\begin{aligned}
\lambda (\boldsymbol a \cdot \boldsymbol a)+\mu (\boldsymbol a \cdot \boldsymbol b) &= 0 \\
\lambda (\boldsymbol a \cdot \boldsymbol b) + \mu (\boldsymbol b \cdot \boldsymbol b) &= \det(\boldsymbol b, \boldsymbol a \times \boldsymbol b, \boldsymbol a) \\
&= (\boldsymbol a \times \boldsymbol b) \cdot (\boldsymbol a \times \boldsymbol b)
\end{aligned}
$$

By the identity derived earlier:

$$
(\boldsymbol a \times \boldsymbol b) \cdot (\boldsymbol a \times \boldsymbol b) = |\boldsymbol a|^2|\boldsymbol b|^2-(\boldsymbol a \cdot \boldsymbol b)^2
$$

we can solve:

$$
\begin{aligned}
\lambda &= -\boldsymbol a \cdot \boldsymbol b \\
\mu &= \boldsymbol a \cdot \boldsymbol a
\end{aligned}
$$

This completes the proof.

The proof above shows that the cross product of $\boldsymbol a \times \boldsymbol b$ with any vector lies in the same plane as $\boldsymbol a$ and $\boldsymbol b$. Next we prove the formula for the **vector triple product**:

$$
(\boldsymbol a\times \boldsymbol b)\times \boldsymbol c=(\boldsymbol a \cdot \boldsymbol c)\boldsymbol b - (\boldsymbol b \cdot \boldsymbol c)\boldsymbol a
$$

This coplanarity makes the formula easier to remember. Note that the lemma above is a special case of the vector triple product.

Proof: we only need to consider the case where all three vectors are nonzero and not collinear; the other special cases are obvious.

The 3D vectors $\boldsymbol a$, $\boldsymbol b$ and $\boldsymbol a \times \boldsymbol b$ are not coplanar, so we can write:

$$
\boldsymbol c = \alpha \boldsymbol a + \beta \boldsymbol b + \gamma(\boldsymbol a \times \boldsymbol b)
$$

Therefore:

$$
\begin{aligned}
(\boldsymbol a \times \boldsymbol b) \times \boldsymbol c &= (\boldsymbol a \times \boldsymbol b) \times (\alpha \boldsymbol a + \beta \boldsymbol b + \gamma(\boldsymbol a \times \boldsymbol b)) \\
&= \alpha(\boldsymbol a \times \boldsymbol b) \times \boldsymbol a + \beta(\boldsymbol a \times \boldsymbol b) \times \boldsymbol b
\end{aligned}
$$

By the lemma above:

$$
\begin{aligned}
(\boldsymbol a \times \boldsymbol b) \times \boldsymbol a &=(\boldsymbol a \cdot \boldsymbol a) \boldsymbol b - (\boldsymbol a \cdot \boldsymbol b) \boldsymbol a \\
(\boldsymbol a \times \boldsymbol b) \times \boldsymbol b
&= -(\boldsymbol b \times \boldsymbol a) \times \boldsymbol b \\
&= -(\boldsymbol b \cdot \boldsymbol b)\boldsymbol a+(\boldsymbol a \cdot \boldsymbol b) \boldsymbol b
\end{aligned}
$$

Therefore:

$$
\begin{aligned}
(\boldsymbol a \times \boldsymbol b) \times \boldsymbol c &= \alpha((\boldsymbol a \cdot \boldsymbol a)\boldsymbol b - (\boldsymbol a \cdot \boldsymbol b)\boldsymbol a) + \beta((\boldsymbol a \cdot \boldsymbol b)\boldsymbol b - (\boldsymbol b \cdot \boldsymbol b)\boldsymbol a) \\
&=(\alpha(-\boldsymbol a \cdot \boldsymbol b) + \beta(-\boldsymbol b \cdot \boldsymbol b))\boldsymbol a + (\alpha \boldsymbol a \cdot \boldsymbol a + \beta \boldsymbol a \cdot \boldsymbol b)\boldsymbol b \\
&= (\boldsymbol a \cdot \boldsymbol c) \boldsymbol b - (\boldsymbol b \cdot \boldsymbol c) \boldsymbol a
\end{aligned}
$$

This completes the proof.

Using the anti-commutativity of the outer product, we get two formulas for the vector triple product:

$$
\begin{aligned}
(\boldsymbol a\times \boldsymbol b)\times \boldsymbol c &=(\boldsymbol a \cdot \boldsymbol c)\boldsymbol b - (\boldsymbol b \cdot \boldsymbol c)\boldsymbol a \\
\boldsymbol a \times(\boldsymbol b \times \boldsymbol c) &= (\boldsymbol a \cdot \boldsymbol c)\boldsymbol b - (\boldsymbol a \cdot \boldsymbol b)\boldsymbol c
\end{aligned}
$$

So the vector triple product depends strictly on the order of operations.

Using the mixed product and the vector triple product, we can also prove Lagrange's identity.

$$
(\boldsymbol a \times \boldsymbol b) \cdot (\boldsymbol c \times \boldsymbol d)=(\boldsymbol a \cdot \boldsymbol c)(\boldsymbol b \cdot \boldsymbol d)-(\boldsymbol a \cdot \boldsymbol d)(\boldsymbol b \cdot \boldsymbol c)
$$

Proof:

$$
\begin{aligned}
(\boldsymbol a \times \boldsymbol b) \cdot (\boldsymbol c \times \boldsymbol d) &= \det(\boldsymbol c, \boldsymbol d, \boldsymbol a \times \boldsymbol b) \\
&= \det(\boldsymbol a \times \boldsymbol b, \boldsymbol c, \boldsymbol d) \\
&= ((\boldsymbol a \times \boldsymbol b)\times \boldsymbol c)\cdot \boldsymbol d \\
&= (\boldsymbol b(\boldsymbol a \cdot \boldsymbol c)- \boldsymbol a(\boldsymbol b \cdot \boldsymbol c))\cdot \boldsymbol d \\
&= (\boldsymbol a \cdot \boldsymbol c)(\boldsymbol b \cdot \boldsymbol d) - (\boldsymbol a \cdot \boldsymbol d)(\boldsymbol b \cdot \boldsymbol c)
\end{aligned}
$$

So the earlier identity

$$
(\boldsymbol a \times \boldsymbol b) \cdot (\boldsymbol a \times \boldsymbol b) = |\boldsymbol a|^2|\boldsymbol b|^2 - (\boldsymbol a \cdot \boldsymbol b)^2
$$

is a special case of Lagrange's identity.
