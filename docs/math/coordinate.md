author: Ir1d, HeRaNO, Chrogeek, abc1763613206, mxdyzmx

## Definition of an angle

In primary or middle school you learned the **static definition** of an angle: a figure made of two rays with a common endpoint is called an angle.

However, this definition limits angles to $[0, 360^\circ]$. That makes deeper study harder, and leaves some questions unanswered, for example: what does it mean to rotate by $720^\circ$?

High school math gives the **dynamic definition** of an angle: the figure formed when a ray in the plane rotates about its endpoint from one position to another is called an angle.

The starting position is called the **initial side**, and the ending position is called the **terminal side**. We also agree that:

-   An angle formed by rotating **counterclockwise** is called a **positive angle**, and its measure is positive;
-   An angle formed by rotating **clockwise** is called a **negative angle**, and its measure is negative;
-   An angle whose terminal side has not rotated at all relative to its initial side is called a **zero angle**, and its measure is $0^\circ$.

This extends the idea of an angle to **angles of any size**.

???+ note "Note"
    For a zero angle, the initial and terminal sides coincide. But not every angle whose initial and terminal sides coincide is a zero angle, for example angles that are multiples of $360^\circ$.

## Radian measure

In practice we often need to convert angles into various other quantities, and describing angles in radians reduces the number of constant factors we need. So next we introduce **radian measure**:

The central angle subtended by an arc whose length equals the radius is called an angle of $1$ radian. It is written with the symbol $\text{rad}$, read as "radian".

Following the conventions above, a positive angle has a positive radian measure, a negative angle has a negative radian measure, and a zero angle has radian measure $0$. If a central angle $\alpha$ of a circle with radius $r$ subtends an arc of length $l$, then:

$$
|\alpha|=\dfrac{l}{r}
$$

From this formula you can also derive the formulas for arc length and the area of a sector, which we skip here.

So an angle of $360^\circ$ measures $2\pi$ radians. With this correspondence, we can convert between degrees and radians:

$$
k \operatorname{rad} = \frac{\pi}{180^\circ} n^\circ
$$

Consider an angle. Rotate its terminal side by one more full turn, or even several, while keeping the initial side fixed. The terminal side always ends up in the same position. These angles are called angles with the same terminal side.

The set of angles with the same terminal side as $\alpha$ is easy to find: $\{\varphi \mid \varphi = \alpha + 2k\pi, k \in \mathbf{Z}\}$.

You can think of it this way: keep adding full turns to the angle, and the terminal side stays where it is.

???+ note "The two mathematical constants $\pi$ and $\tau$"
    Some people in the Western math community currently argue that "the true circle constant" should be $2\pi$, and they write this value as the Greek letter $\tau$. Supporters of the new circle constant celebrate the "true" Pi Day (Tau Day) on June 28.
    
    For example, in radian measure a full angle is $2\pi$, so dividing $2\pi$ into equal parts directly gives equal parts of a full turn. As another example, the combination $2\pi$ appears frequently in complex analysis, and so on.
    
    To follow the established convention across Chinese-speaking regions, **OI Wiki** uses $\pi$ for the circle constant.

???+ note "How to write pi in code"
    In C/C++, $\pi$ is usually taken as `acos(-1)`, which gives the floating-point number closest to $\pi$. The value of $\pi$ obtained from `acos(-1)` or `4 * atan(1)` is $3.14159265358979310000$.
    
    Other expressions, such as `acos(-1.0/2.0)`, `acos(1.0/2.0)`, `asin(1.0/2.0)` and so on, give $3.14159265358979360000$, which is not the floating-point number closest to $\pi$.
    
    If you can memorize it, you can also write $3.1415926535897932$ directly.

## Cartesian coordinates in the plane

Two number lines in the same plane that are perpendicular to each other and share a common origin form a plane Cartesian coordinate system (Rectangular Coordinates).

Usually the two number lines are placed horizontally and vertically, with right and up as their positive directions. The horizontal number line is called the $x$-axis (x-axis) or horizontal axis, and the vertical one is called the $y$-axis (y-axis) or vertical axis. Together the $x$-axis and $y$-axis are called the coordinate axes. Their common origin $O$ is called the origin of the coordinate system. A plane Cartesian coordinate system with origin $O$ is written as the coordinate system $xOy$.

The $x$-axis and $y$-axis divide the coordinate plane into four quadrants. The upper-right part is called the first quadrant, and the other three parts, going counterclockwise, are called the second, third and fourth quadrants. The quadrants are bounded by the axes: points on the horizontal axis, on the vertical axis, and the origin do not belong to any quadrant. Usually the $x$-axis and $y$-axis use the same unit length, but in special cases they can use different unit lengths.

### Describing positions in Cartesian coordinates

In a plane Cartesian coordinate system, every point in the plane corresponds to exactly one ordered pair of numbers (its coordinates). Conversely, every ordered pair corresponds to exactly one point in the plane.

For any point $C$ in the plane, draw perpendiculars from $C$ to the $x$-axis and the $y$-axis. The feet of these perpendiculars give values $a, b$ on the $x$-axis and $y$-axis, called the $x$-coordinate (abscissa) and $y$-coordinate (ordinate) of $C$. The ordered pair $(a, b)$ is called the Cartesian coordinates of $C$. Points in different quadrants or on different axes have different coordinates.

## Polar coordinates in the plane

Think of real-life situations such as navigation. People say "point $B$ is $100$ meters from point $A$, in the direction $30^\circ$ east of north", not "set up a Cartesian coordinate system with $A$ as the origin; then $B(50,50\sqrt 3)$".

So:

1.  Choose a fixed point $O$ in the plane, called the **pole**;
2.  Draw a ray $Ox$ from the pole, called the **polar axis**;
3.  Choose a unit of length (usually $1$ in math problems), a unit of angle (usually radians) and a positive direction for angles (usually counterclockwise);

This sets up a **polar coordinate system**.

### Describing positions in polar coordinates

Let $A$ be a point in the plane.

-   The distance $|OA|$ between the pole $O$ and $A$ is called the **radial coordinate** (polar radius), written $\rho$;
-   The angle $\angle xOA$, with the polar axis as initial side and $OA$ as terminal side, is called the **polar angle**, written $\varphi$;

Then the ordered pair $(\rho,\varphi)$ is the **polar coordinates** of $A$.

By the definition of angles with the same terminal side, $(\rho,\varphi)$ and $(\rho,\varphi + 2k\pi)\ (k\in \mathbf{Z})$ actually describe the same point. In particular, the pole has polar coordinates $(0,\varphi)\ (\varphi \in \mathbf{R})$. So each point in the plane has infinitely many polar representations.

If we require $\rho \ge 0,0 \le \varphi < 2\pi$, then every point in the plane except the pole can be represented by a unique ordered pair $(\rho,\varphi)$, and the point described by polar coordinates $(\rho,\varphi)$ is uniquely determined.

### Converting between Cartesian and polar coordinates

Of course, studying figures in polar coordinates is sometimes inconvenient. To switch to Cartesian coordinates, we have conversion formulas. The Cartesian coordinates $(x,y)$ of the point $A(\rho,\varphi)$ are:

$$
\begin{aligned}
x &= \rho \cos \varphi \\
y &= \rho \sin \varphi
\end{aligned}
$$

From this we get:

$$
\begin{aligned}
\rho^2 &= x^2 + y^2\\
\tan \varphi &= \frac{y}{x}\ \ \ \ (x\not =0)
\end{aligned}
$$

So $\rho = \sqrt{x^2+y^2}$.

However, a given value of $\tan\varphi = \dfrac{y}{x}$ corresponds to two possible values of $\varphi$, so we also need the values of $x, y$ to determine the direction. Specifically, define the function:

$$
\operatorname{atan2}(y, x) = \begin{cases}
\arctan(\frac{y}{x}) & \text{if } x > 0 \\
\arctan(\frac{y}{x}) + \pi & \text{if } y \ge 0, x < 0 \\
\arctan(\frac{y}{x}) - \pi & \text{if } y < 0, x < 0 \\
\pi/2 & \text{if } y > 0, x = 0 \\
-\pi/2 & \text{if } y < 0, x = 0 \\
\text{any} & \text{if } y = 0, x = 0
\end{cases}
$$

Then $\varphi = \operatorname{atan2}(y, x)$. Note that the range of this function is $(-\pi, \pi]$.

[This function](https://zh.cppreference.com/w/cpp/numeric/math/atan2) is defined in the C/C++ `<math.h>` or `<cmath>` library; just call `atan2(y, x)`.

## Cartesian coordinates in space

Set up a 3D Cartesian coordinate system as follows:

1.  Choose a point $O$ in space;
2.  Through $O$, draw three mutually perpendicular number lines $\overrightarrow{Ox}, \overrightarrow{Oy}, \overrightarrow{Oz}$, called the $x$-axis (horizontal axis), the $y$-axis (vertical axis) and the $z$-axis (upright axis), together called the coordinate axes. Their positive directions follow the right-hand rule: grip the $z$-axis with your right hand so that your four fingers curl from the positive $x$-axis toward the positive $y$-axis; then your thumb points along the positive $z$-axis;
3.  Choose a unit of length on each axis, usually $1$.

This forms a 3D Cartesian coordinate system, written $O-xyz$. The fixed point $O$ is called the origin of the coordinate system.

Any two coordinate axes determine a plane, which gives three mutually perpendicular planes, together called the coordinate planes. The plane determined by the $x$-axis and $y$-axis is called the $xOy$ plane, and similarly there are the $yOz$ plane and the $zOx$ plane. The three coordinate planes divide space into eight parts, and each part is called an octant.

### Describing positions in 3D Cartesian coordinates

Once a 3D Cartesian coordinate system $O-xyz$ is fixed, we can set up a one-to-one correspondence between points in space and triples of numbers.

Let $M$ be a point in space. Through $M$, draw planes perpendicular to the $x$-axis, the $y$-axis and the $z$-axis. Let these three planes meet the $x$-axis, $y$-axis and $z$-axis at $P, Q, R$ respectively. The points $P, Q, R$ are called the projections of $M$ onto the $x$-axis, $y$-axis and $z$-axis. Let the coordinates of $P, Q, R$ on the $x$-axis, $y$-axis and $z$-axis be $x, y, z$ respectively. Then the point $M$ determines a triple $(x, y, z)$.

Conversely, given a triple $(x, y, z)$, take the point $P$ with coordinate $x$ on the $x$-axis, the point $Q$ with coordinate $y$ on the $y$-axis, and the point $R$ with coordinate $z$ on the $z$-axis. Then through $P, Q, R$ draw three planes perpendicular to the $x$-axis, $y$-axis and $z$-axis respectively. They meet at a single point $M$ in space, and $M$ is the point determined by the triple $(x, y, z)$.

In this way, we get a one-to-one correspondence between points $M$ in space and triples $(x, y, z)$. The triple $(x, y, z)$ is called the coordinates of $M$, written $M(x, y, z)$, where $x$ is called the $x$-coordinate, $y$ the $y$-coordinate and $z$ the $z$-coordinate.

## Cylindrical coordinates

Cylindrical coordinates extend polar coordinates to three dimensions: start with a polar coordinate system in a plane, then add a $z$-axis through the pole $O$, perpendicular to that plane and pointing up.

To find the point described by cylindrical coordinates $(\rho, \varphi, z)$, first handle $\rho$ and $\varphi$ in the polar coordinate system, then move "up" or "down" along the $z$-axis according to the $z$ coordinate.

### Converting between cylindrical and 3D Cartesian coordinates

The value of $z$ is the same in both coordinate systems.

For converting between $(x,y)$ and $(\rho, \varphi)$, see [Converting between Cartesian and polar coordinates](#converting-between-cartesian-and-polar-coordinates) above.

## Spherical coordinates

Spherical coordinates can be determined as follows:

1.  Stand at the origin, facing the direction of the horizontal polar axis; the vertical axis points from your feet to your head;
2.  Raise your arm straight up, pointing along the vertical polar axis;
3.  Rotate counterclockwise by the angle $\varphi$;
4.  Rotate your arm down by the angle $\vartheta$; your arm now points in the direction given by $\varphi$ and $\vartheta$;
5.  Move a distance $r$ from the origin along this direction.

This brings you to the point described by spherical coordinates $(r,\vartheta,\varphi)$. Here $\vartheta$ is called the **zenith angle** (polar angle) and $\varphi$ is called the **azimuth angle**.

???+ warning "Warning"
    For various reasons, some sources use $\phi$ for the zenith angle and $\theta$ for the azimuth angle. Pay close attention to this whenever you read an article that uses spherical coordinates.
    
    Also, when you write an article that uses spherical coordinates, it is a good idea to state clearly up front which symbols you use for the zenith angle and the azimuth angle.

### Converting between cylindrical and spherical coordinates

The value of $\varphi$ is the same in both coordinate systems.

From cylindrical to spherical coordinates:

$$
\begin{aligned}
r &= \sqrt{\rho^2 + z^2} \\
\vartheta &= \begin{cases}
\arctan\left(\frac{\rho}{z}\right) & \text{if }z > 0 \\
\pi/2 & \text{if }z = 0, \rho \not= 0 \\
\arctan\left(\frac{\rho}{z}\right) + \pi & \text{if }z < 0 \\
\end{cases}
\end{aligned}
$$

Note that for the point $(0,0,0)$ in cylindrical coordinates, the spherical coordinate $\vartheta$ is undefined.

From spherical to cylindrical coordinates:

$$
\begin{aligned}
\rho &= r \sin \vartheta \\
z &= r \cos \vartheta
\end{aligned}
$$

### Converting between 3D Cartesian and spherical coordinates

You can combine [Converting between Cartesian and polar coordinates](#converting-between-cartesian-and-polar-coordinates) and [Converting between cylindrical and spherical coordinates](#converting-between-cylindrical-and-spherical-coordinates) above, or use the formulas below directly:

From 3D Cartesian to spherical coordinates:

$$
\begin{aligned}
r &= \sqrt{x^2 + y^2 + z^2} \\
\vartheta &= \arccos\left(\frac{z}{\sqrt{x^2 + y^2 + z^2}}\right) \\
\varphi &= \operatorname{atan2}(y, x)
\end{aligned}
$$

For the definition of $\operatorname{atan2}$, see [Converting between Cartesian and polar coordinates](#converting-between-cartesian-and-polar-coordinates).

Note that for the point $(0,0,0)$ in 3D Cartesian coordinates, the spherical coordinates $\vartheta$ and $\varphi$ are undefined.

From spherical to 3D Cartesian coordinates:

$$
\begin{aligned}
x &= r \sin \vartheta \cos \varphi \\
y &= r \sin \vartheta \sin \varphi \\
z &= r \cos \vartheta
\end{aligned}
$$
