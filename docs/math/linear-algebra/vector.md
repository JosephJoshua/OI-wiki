Before we start, a quick note on terminology. For historical reasons, Chinese mathematics and Chinese physics translate the word "vector" differently.

In physics it is usually rendered as *shiliang* (literally "arrow quantity"), as the counterpart of *biaoliang* ("scalar"). In mathematics it is usually rendered as *xiangliang* ("directed quantity"). Similar differences exist for other pairs, such as the two Chinese renderings of "eigen-" and of "unitary".

**OI Wiki** is mainly aimed at computer science and other engineering fields, which are closer to mathematics, so the original Chinese text uses the mathematical term *xiangliang*. In English, both are simply "vector".

## Definitions and related concepts

**Vector**: a quantity that has both a magnitude and a direction. The vectors studied in mathematics are **free vectors**: as long as the magnitude and direction stay the same, the vector can be moved parallel to itself, so its start and end points can be anywhere. A vector is written $\vec a$ or $\boldsymbol{a}$.

**Directed line segment**: a line segment with a direction. A directed line segment has three elements: **start point, direction, length**. Once these three are known, the end point is uniquely determined. Vectors are usually represented by directed line segments.

**Magnitude (norm) of a vector**: the length of the directed line segment $\overrightarrow{AB}$ is called the magnitude of the vector, that is, its size. It is written $|\overrightarrow{AB}|$ or $|\boldsymbol{a}|$.

**Zero vector**: the vector with magnitude $0$. Its direction is arbitrary. It is written $\vec 0$ or $\boldsymbol{0}$.

**Unit vector**: a vector with magnitude $1$ is called the unit vector in its direction. It is usually written $\vec e$ or $\boldsymbol{e}$.

**Parallel vectors**: two **nonzero** vectors with the same or opposite directions. Written $\boldsymbol a\parallel \boldsymbol b$. For several mutually parallel vectors, we can draw any line parallel to them, and every one of them can be moved onto that same line. That is why parallel vectors are also called **collinear vectors**.

**Equal vectors**: vectors with equal magnitudes and the same direction.

**Opposite vectors**: vectors with equal magnitudes and opposite directions.

**Angle between vectors**: given two nonzero vectors $\boldsymbol a,\boldsymbol b$, draw $\overrightarrow{OA}=\boldsymbol a,\overrightarrow{OB}=\boldsymbol b$. Then $\theta=\angle AOB$ is the angle between $\boldsymbol a$ and $\boldsymbol b$, written $\langle \boldsymbol a,\boldsymbol b\rangle$. Clearly, when $\theta=0$ the two vectors point the same way; when $\theta=\pi$ they point in opposite directions; when $\theta=\frac{\pi}{2}$ they are perpendicular, written $\boldsymbol a\perp \boldsymbol b$. By convention, $\theta \in [0,\pi]$.

Note that plane vectors have direction, so two vectors cannot be compared by size (though their magnitudes can be compared). Two vectors can, however, be equal.

## Linear operations on vectors

### Vector addition and subtraction

Once we have defined a new kind of quantity, we want to be able to compute with it. Vector operations can be modeled on operations on numbers, and they can also be studied from a physics point of view.

Think of displacement in physics. If a person walks from $A$ through $B$ to $C$, the total displacement is $\overrightarrow{AB}+\overrightarrow{BC}$. This is the same as walking directly from $A$ to $C$, so $\overrightarrow{AB}+\overrightarrow{BC}=\overrightarrow{AC}$.

The rule for combining forces, the parallelogram rule, can also be seen as adding vectors.

To sum up, the rules for vector addition are:

1.  **Triangle rule of vector addition**: if the vectors to be added are placed head to tail in order, their sum is the vector from the start of the first vector to the end of the last one;
2.  **Parallelogram rule of vector addition**: if the two vectors to be added **share a start point**, their sum is the diagonal of the parallelogram with these two vectors as adjacent sides. It starts at the shared start point and points along the diagonal.

This gives vector addition a geometric meaning. One can also check that vector addition is **commutative and associative**.

Since subtracting a real number can be written as adding its negative, we do the same for vectors: $\boldsymbol a-\boldsymbol b=\boldsymbol a+(-\boldsymbol b)$.

Now take two vectors with a common start point and build their difference with the parallelogram rule. After moving it into place, we see that **"the difference of two vectors with a common start point" is the directed segment pointing from the "subtrahend" to the "minuend"**. This is the geometric meaning of vector subtraction.

Sometimes we have two points $A,B$ and want $\overrightarrow{AB}$. We can get it by subtraction: $\overrightarrow{AB}=\overrightarrow{OB}-\overrightarrow{OA}$.

### Scalar multiplication

We define "the product of a real number $\lambda$ and a vector $\boldsymbol a$" to be a vector. This operation is called **scalar multiplication** and is written $\lambda \boldsymbol a$. Its length and direction are defined as follows:

1.  $|\lambda \boldsymbol a|=|\lambda||\boldsymbol a|$;
2.  When $\lambda >0$, $\lambda\boldsymbol a$ points the same way as $\boldsymbol a$; when $\lambda =0$, $\lambda \boldsymbol a=\boldsymbol 0$; when $\lambda<0$, $\lambda \boldsymbol a$ points opposite to $\boldsymbol a$.

From the definition of scalar multiplication, one can check the following laws:

$$
\begin{aligned}
\lambda(\mu \boldsymbol a)&=(\lambda \mu)\boldsymbol a\\
(\lambda+\mu)\boldsymbol a&=\lambda \boldsymbol a+\mu \boldsymbol a\\
\lambda(\boldsymbol a+\boldsymbol b)&=\lambda \boldsymbol a+\lambda \boldsymbol b
\end{aligned}
$$

In particular:

$$
\begin{gathered}
(-\lambda)\boldsymbol a=-(\lambda \boldsymbol a)=-\lambda(\boldsymbol a)\\
\lambda(\boldsymbol a-\boldsymbol b)=\lambda \boldsymbol a-\lambda \boldsymbol b
\end{gathered}
$$

### Testing whether two vectors are collinear

Two **nonzero** vectors $\boldsymbol a$ and $\boldsymbol b$ are collinear $\iff$ there is a unique real number $\lambda$ such that $\boldsymbol b=\lambda \boldsymbol a$.

Proof: by the definition of scalar multiplication, for a **nonzero** vector $\boldsymbol a$, if some real $\lambda$ satisfies $\boldsymbol b=\lambda \boldsymbol a$, then $\boldsymbol a \parallel \boldsymbol b$.

Conversely, if $\boldsymbol a\parallel \boldsymbol b$, $\boldsymbol a \not = \boldsymbol 0$, and $|\boldsymbol b|=\mu |\boldsymbol a|$, then $\boldsymbol b=\mu \boldsymbol a$ when $\boldsymbol a$ and $\boldsymbol b$ point the same way, and $\boldsymbol b=-\mu \boldsymbol a$ when they point in opposite directions.

Finally, vector addition, subtraction and scalar multiplication are together called the linear operations on vectors.

## Fundamental theorem of plane vectors and coordinates

### Fundamental theorem of plane vectors

Statement: if two vectors $\boldsymbol{e_1},\boldsymbol{e_2}$ are not collinear, then for every vector $\boldsymbol p$ in the same plane as $\boldsymbol{e_1},\boldsymbol{e_2}$ there is a unique pair of real numbers $(x,y)$ such that $\mathbf p=x\boldsymbol{e_1}+y\boldsymbol{e_2}$.

There are so many plane vectors. How can we describe all of them using as few quantities as possible?

Clearly one vector is not enough to describe every vector; at most it describes the vectors on one line.

Add a second vector, so we use two **non-collinear** vectors (two collinear vectors would act like a single one here). Now any plane vector can be decomposed along the directions of these two vectors.

Two non-collinear vectors in the same plane are called a **basis**. If the basis vectors are perpendicular to each other, the decomposition is called an **orthogonal decomposition**.

### Coordinates of plane vectors

If we take the unit vectors $i,j$ along the horizontal and vertical axes as a basis, then by the fundamental theorem of plane vectors, the plane vectors are in one-to-one correspondence with ordered pairs of real numbers $(x,y)$.

Ordered pairs $(x,y)$ are also in one-to-one correspondence with points in the Cartesian plane. So if we draw $\overrightarrow{OP}=\boldsymbol p$, the end point $P(x,y)$ is uniquely determined. Since we study free vectors, whose start point can be moved freely, every vector in the Cartesian plane can be uniquely represented by an ordered pair of real numbers.

## Coordinate operations on plane vectors

### Linear operations on plane vectors

The coordinate formulas follow from the linear operations: write everything in terms of the basis, combine terms using the operation laws, and then read off the coordinates of the result.

If $\boldsymbol a=(m,n)$ and $\boldsymbol b=(p,q)$, then:

$$
\begin{aligned}
\boldsymbol a+\boldsymbol b&=(m+p,n+q)\\
\boldsymbol a-\boldsymbol b&=(m-p,n-q)\\
k\boldsymbol a&=(km,kn)
\end{aligned}
$$

### Finding the coordinates of a vector

Given two points $A(a,b),B(c,d)$, it is easy to show that $\overrightarrow{AB}=(c-a,d-b)$.

### Translating a point

Sometimes we need to move a point $P$ some distance in some direction. Combine the direction and distance into one vector. By the triangle rule of vector addition, add this vector to $\overrightarrow{OP}$; the end point of the result is the moved point.

### Testing whether three points are collinear

If the three points $A,B,C$ are collinear, then $\overrightarrow{OB}=\lambda \overrightarrow{OA}+(1-\lambda)\overrightarrow{OC}$.

### An extension of the collinearity test

In triangle $ABC$, if $D$ is a point dividing $BC$ in a given ratio ($n\ BD=k\ DC$), then $\overrightarrow{AD}=\frac{n}{k+n}\overrightarrow{AB}+\frac{k}{k+n}\overrightarrow{AC}$

## Extension to three dimensions (solid geometry / space vectors)

In space, everything above still holds. In addition:

### Fundamental theorem of space vectors

Statement: if three vectors $\boldsymbol{e_1},\boldsymbol{e_2},\boldsymbol{e_3}$ are not coplanar, then for every vector $\boldsymbol p$ in space there is a unique triple of real numbers $(x,y,z)$ such that $\mathbf p=x\boldsymbol{e_1}+y\boldsymbol{e_2}+z\boldsymbol{e_3}$.
By this theorem, we can likewise take three mutually perpendicular vectors $\boldsymbol{e_1},\boldsymbol{e_2},\boldsymbol{e_3}$ as an orthogonal basis, set up a **three-dimensional Cartesian coordinate system**, and represent space vectors by triples $(x,y,z)$.

### Fundamental theorem of coplanar vectors

If $\boldsymbol{x},\boldsymbol{y}$ are two non-collinear vectors, then a vector $\boldsymbol{p}$ is coplanar with $\boldsymbol{x},\boldsymbol{y}$ if and only if there is a unique pair of real numbers $(a,b)$ such that $\boldsymbol{p}=a\boldsymbol{x}+b\boldsymbol{y}$.

### Direction vectors

The direction of a line in space is described by a nonzero vector parallel to the line. Such a vector is called a direction vector of the line. The position of a line in space is **completely determined** by one point on it and one of its direction vectors.

Note that lines in the plane also have direction vectors.

For a line in **space**, a direction vector can be found as follows:

-   Given $A(x_1,y_1,z_1),B(x_2,y_2,z_2)$, one direction vector of line $AB$ is $\boldsymbol{s}=(x_2-x_1,y_2-y_1,z_2-z_1)$.

-   Given a plane **perpendicular** to the line, with general equation $ax+by+cz+d=0$, one direction vector of a line perpendicular to this plane is $\boldsymbol{s}=(a,b,c)$. This direction vector is also **a normal vector** of the plane.

### Normal vectors

For a plane $ABCD$, its normal vector $\boldsymbol{n}$ is perpendicular to the plane.

How to compute it: take any two lines in the plane, $\overrightarrow{AB},\overrightarrow{AD}$, and require $\overrightarrow{AB} \cdot \boldsymbol{n}=\boldsymbol{0}$ and $\overrightarrow{AD} \cdot \boldsymbol{n}=\boldsymbol{0}$. Then solve with coordinates.

## Vectors and matrices

In linear algebra, linear transformations can be represented by matrices. Let $T$ be a linear transformation from $\mathbf R^n$ to $\mathbf R^m$ and let $\mathbf x$ be an $n$-dimensional column vector. Then there is an $m\times n$ matrix $A$ such that

$$
T(\mathbf x)=A\mathbf x.
$$

The matrix $A$ is called the transformation matrix of $T$. In algorithm problems, linear transformations usually keep the dimension the same, so $A$ is a square matrix. In this way, a linear transformation of vectors becomes a matrix multiplication problem.

Next we look at three transformations that are fairly common in contests and their transformation matrices: scaling (matrix $S$), rotation (matrix $R$) and translation (matrix $T$).

### Scaling

For an $n$-dimensional column vector $\boldsymbol a$, scale its coordinates by factors $v_1,v_2,\ldots,v_n$. It is easy to see that the transformation matrix $R$ of scaling is the $n\times n$ diagonal matrix $S=\operatorname{diag}\{v_1,v_2,\ldots,v_n\}$.

### Rotation

Rotating a vector is a relatively complicated operation. We only discuss two and three dimensions.

#### Rotating a vector about a point

Rotating a vector about a point usually means rotating it about the origin. To rotate a point about another point $P$, first translate so that $P$ is at the origin, rotate the vector, then translate back. If $T$ is the translation matrix and $R$ is the matrix of rotation about the origin, the whole process has transformation matrix $TRT^{-1}$. Geometrically, $T^{-1}$ always exists.

In two dimensions, let $\boldsymbol a=(x,y)$ have angle of inclination $\theta$ and length $l=\sqrt{x^2+y^2}$. Then $x=l\cos \theta,y=l\sin\theta$. Rotating it counterclockwise about the origin by angle $\alpha$ gives the vector $\boldsymbol b=(l\cos(\theta+\alpha),l\sin(\theta+\alpha))$.

![](./images/vector-rotation.svg)

By trigonometric identities,

$$
\boldsymbol{b}=(l(\cos\theta\cos\alpha-\sin\theta\sin\alpha),l(\sin\theta\cos\alpha+\cos\theta\sin\alpha))
$$

Simplifying,

$$
\boldsymbol b=(l\cos\theta\cos\alpha-l\sin\theta\sin\alpha,l\sin\theta\cos\alpha+l\cos\theta\sin\alpha)
$$

Substituting $x,y$ back in gives

$$
\boldsymbol b=(x\cos\alpha-y\sin\alpha,y\cos\alpha+x\sin\alpha)
$$

So in two dimensions, the transformation matrix $R$ is

$$
R=
\begin{bmatrix}
\cos\alpha & -\sin\alpha\\
\sin\alpha & \cos\alpha
\end{bmatrix}.
$$

In three dimensions, rotating a vector needs two angle parameters, the change in the zenith (polar) angle and the change in the azimuth angle. The rotation can be done using [spherical coordinates](../coordinate.md#空间球坐标系).

#### Rotating a vector about a line

For 3D vectors, it is more common to rotate about a line. Again for convenience, assume the line passes through the origin. If it does not, we can still translate the coordinate system to reduce to this case.

Take a direction vector $\boldsymbol u=(u_x,u_y,u_z)$ of the line, and rotate the 3D vector counterclockwise about it by angle $\theta$. The corresponding transformation matrix $R$ is[^note1]

$$
R=
\begin{bmatrix}
u_x^2 \left(1-\cos \theta\right) + \cos \theta & u_x u_y \left(1-\cos \theta\right) - u_z \sin \theta & u_x u_z \left(1-\cos \theta\right) + u_y \sin \theta \\ 
u_x u_y \left(1-\cos \theta\right) + u_z \sin \theta & u_y^2\left(1-\cos \theta\right) + \cos \theta & u_y u_z \left(1-\cos \theta\right) - u_x \sin \theta \\ 
u_x u_z \left(1-\cos \theta\right) - u_y \sin \theta & u_y u_z \left(1-\cos \theta\right) + u_x \sin \theta & u_z^2\left(1-\cos \theta\right) + \cos \theta
\end{bmatrix}.
$$

### Translation

Translation is not a linear transformation; it is an affine transformation. But an affine transformation on $\mathbf R^n$ can still be represented by a linear transformation on $\mathbf R^{n+1}$.

Consider an $n$-dimensional vector $\boldsymbol a=(a_1,a_2, \ldots , a_n)$ that we want to translate by the vector $\boldsymbol t=(t_1, t_2, \ldots , t_n)$. Add one more coordinate to the column vector $\boldsymbol a$ and set it to $1$, giving the new column vector $\boldsymbol a'=(a_1, a_2, \ldots , a_n, 1)$. Then the transformation matrix $T$ can be written as

$$
T=
\begin{bmatrix}
1 &   &        &   & t_1    \\
  & 1 &        &   & t_2    \\
  &   & \ddots &   & \vdots \\
  &   &        & 1 & t_n    \\
  &   &        &   & 1      \\
\end{bmatrix}.
$$

For any other linear transformation matrix, add one row and one column, set the bottom-right entry to $1$ and fill the rest of the new row and column with $0$. In this way every linear transformation matrix can be turned into an affine transformation matrix. For example, the 2D rotation matrix becomes

$$
R'=
\begin{bmatrix}
\cos\alpha & -\sin\alpha & 0\\
\sin\alpha & \cos\alpha & 0\\
0 & 0 & 1
\end{bmatrix}.
$$

## A more rigorous definition of vectors

Above, vectors were defined as directed line segments in space. Strictly speaking, though, vectors are more than directed line segments. To give a more rigorous definition, we first need to define [vector spaces](./vector-space.md). See the [vector spaces](./vector-space.md) page for details.

[^note1]: See [Rotation matrix from axis and angle - Wikipedia](https://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle)
