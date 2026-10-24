If you have already learned about complex numbers, feel free to skip this page.

Learning about complex numbers requires some background on vectors. If you have not learned about vectors yet, please read the [vector page](../math/linear-algebra/vector.md) first.

## Complex numbers

### Introduction

???+ note "Note"
    The introduction below follows the approach of the PEP (People's Education Press) high school math textbook, Edition A, Compulsory Volume 2.

From the point of view of equations, asking whether a negative real number has a square root is the same as asking whether the equation $x^2+a=0 (a>0)$ has a solution. This in turn comes down to whether the equation $x^2+1=0$ has a solution.

Looking back at how number sets have been extended so far, we can see that each extension was closely tied to practical needs. For example, to measure the diagonal of a square, and to deal with the fact that equations like $x^2-2=0$ have no solution in the rationals, people extended the set of rational numbers to the set of real numbers. After the extension, the addition and multiplication defined on the reals agree with the addition and multiplication previously defined on the rationals. Both addition and multiplication are commutative and associative, and multiplication distributes over addition.

Following the same idea, to deal with the fact that equations like $x^2+1=0$ have no solution in the real number system, we imagine introducing a new number $\mathrm{i}$ such that $x=\mathrm{i}$ is a solution of $x^2+1=0$, that is, $\mathrm{i}^2=-1$.

Think about it: we add the new number $\mathrm{i}$ to the set of real numbers. We want $\mathrm{i}$ and the real numbers to still support addition and multiplication just like real numbers do, and we want addition and multiplication to be commutative and associative, with multiplication distributing over addition. Then, after extending the real number system, what numbers make up the new number system?

Following this idea, multiply a real number $b$ by $\mathrm{i}$ and write the result as $b\mathrm{i}$; add a real number $a$ to $b\mathrm{i}$ and write the result as $a+b\mathrm{i}$. Note that every real number, as well as $\mathrm{i}$, can be written in the form $a+b\mathrm{i}(a,b\in \mathbf{R})$, so all of them are in the new, extended number set.

### Definition

A number of the form $a+b\mathrm{i}$, where $a,b\in \mathbf{R}$, is called a **complex number**. Here $\mathrm{i}$ is called the **imaginary unit**. The set of all complex numbers is called the **set of complex numbers** and is written $\mathbf{C}$.

A complex number is usually written as $z$, that is, $z=a+b\mathrm{i}$. This is called the **algebraic form of a complex number**. Here $a$ is called the **real part** of $z$, written $\operatorname{Re}(z)$, and $b$ is called the **imaginary part** of $z$, written $\operatorname{Im}(z)$. Unless stated otherwise, we always have $a,b\in \mathbf{R}$.

A complex number $z$ is a real number if and only if $b=0$. When $b\not = 0$, it is an imaginary number. When $a=0$ and $b\not = 0$, it is a purely imaginary number.

The figure below shows how purely imaginary numbers, imaginary numbers, real numbers and complex numbers relate to each other.

![](./images/complex-relation.svg)

## Properties and operations

### Geometric meaning

We now know that numbers of the form $a+b\mathrm{i}$ are called complex numbers, and we have given their definition and classification. We can dig deeper into their properties.

We placed all real numbers on the number line and found that points on the line correspond one-to-one with real numbers. Let us try to do the same for complex numbers.

First, we define **equality of complex numbers**: two complex numbers $z_1=a+b\mathrm{i},z_2=c+d\mathrm{i}$ are equal if and only if $a=c$ and $b=d$.

This definition is very natural, so we will not explain it further here.

In other words, a complex number $z=a+b\mathrm{i}$ can be represented by a unique ordered pair of real numbers $(a,b)$. This reminds us of the Cartesian coordinate plane, and we see that **the set of complex numbers corresponds one-to-one with the set of points in the Cartesian plane**. So we have found one geometric meaning of complex numbers.

This coordinate plane is no longer an ordinary one, because its points now have a special meaning: each represents a complex number. So we call such a plane the **complex plane**, the $x$-axis the **real axis**, and the $y$-axis the **imaginary axis**. We can say more precisely: **the set of complex numbers corresponds one-to-one with the set of all points in the complex plane**.

Recall plane vectors: the coordinate form of a vector is also an ordered pair of real numbers $(a,b)$. Clearly, the complex number $z=a+b\mathrm{i}$ corresponds to the point $Z(a,b)$ in the complex plane, so it also corresponds to the plane vector $\overrightarrow{OZ}=(a,b)$. This gives us another geometric meaning of complex numbers: **the set of complex numbers corresponds one-to-one with the set of vectors in the complex plane (the real number $0$ corresponds to the zero vector)**.

So we carry ideas over from vectors to complex numbers, and define the **modulus of a complex number** as the length (magnitude) of its corresponding vector. The modulus of $z=a+b\mathrm{i}$ is $|z|=\sqrt{a^2+b^2}$.

For convenience, we often call the complex number $z=a+b\mathrm{i}$ the point $Z$ or the vector $\overrightarrow {OZ}$, and we agree that equal vectors represent the same complex number.

Also, from what we know about vectors, we see that imaginary numbers cannot be compared in size (but real numbers can).

### Addition and subtraction

For complex numbers $z_1=a+b\mathrm{i},z_2=c+d\mathrm{i}$, addition is defined as:

$$
z_1+z_2=(a+c)+(b+d)\mathrm{i}
$$

Clearly, the sum of two complex numbers is still a complex number.

Comparing with vector addition, we see that complex addition follows the same rule as vector addition. This also confirms that the geometric meaning of complex numbers is correct.

We can also check that complex addition is **commutative** and **associative**, that is:

$$
\begin{aligned}
z_1+z_2&=z_2+z_1\\
(z_1+z_2)+z_3&=z_1+(z_2+z_3)
\end{aligned}
$$

Subtraction is the inverse of addition. Using the addition rule and the definition of equality of complex numbers, we can derive the subtraction rule:

$$
z_1-z_2=(a-c)+(b-d)\mathrm{i}
$$

This also matches vector subtraction.

### Multiplication, division and conjugates

For complex numbers $z_1=a+b\mathrm{i},z_2=c+d\mathrm{i}$, multiplication is defined as:

$$
\begin{aligned}
z_1z_2&=(a+b\mathrm{i})(c+d\mathrm{i})\\
&=ac+bc\mathrm{i}+ad\mathrm{i}+bd\mathrm{i}^2\\
&=(ac-bd)+(bc+ad)\mathrm{i}
\end{aligned}
$$

As you can see, multiplying two complex numbers is like multiplying two polynomials: just replace $\mathrm{i}^2$ with $-1$, then collect the real parts and the imaginary parts separately.

Complex multiplication looks similar in form to the cross product of vectors.

It is easy to show that complex multiplication is **commutative**, **associative** and **distributive over addition**, that is:

-   $z_1z_2=z_2z_1$
-   $(z_1z_2)z_3=z_1(z_2z_3)$
-   $z_1(z_2+z_3)=z_1z_2+z_1z_3$

Since these laws hold, we see that **the algebraic identities for multiplication over the reals also hold over the complex numbers**.

Division is the inverse of multiplication. Let us derive it:

$$
\begin{aligned}
\frac{a+b\mathrm{i}}{c+d\mathrm{i}}&=\frac{(a+b\mathrm{i})(c-d\mathrm{i})}{(c+d\mathrm{i})(c-d\mathrm{i})}\\
&=\frac{ac+bd}{c^2+d^2}+\frac{bc-ad}{c^2+d^2}\mathrm{i} &(c+d\mathrm{i}\not =0)
\end{aligned}
$$

Since vectors have no division, we do not discuss the relation to vectors here.

To make the denominator real, we multiplied by $c-d\mathrm{i}$. This expression is very meaningful.

For a complex number $z=a+b\mathrm{i}$, the number $a-b\mathrm{i}$ is called the **complex conjugate** of $z$, usually written $\bar z$. We can see that if two complex numbers are conjugates of each other, they are **symmetric about the real axis**.

For complex numbers $z,w$, complex conjugation has the following properties:

-   $z\cdot\bar{z}=|z|^2$
-   $\overline{\overline{z}}=z$
-   $\operatorname{Re}(z)=\dfrac{z+\bar{z}}{2}$, $\operatorname{Im}(z)=\dfrac{z-\bar{z}}{2}$
-   $\overline{z\pm w}=\bar{z}\pm\bar{w}$
-   $\overline{zw}=\bar{z}\bar{w}$
-   $\overline{z/w}=\bar{z}/\bar{w}$

### Argument and principal argument

If we take the real unit $1$ as the positive horizontal direction and the imaginary unit $\mathrm{i}$ as the positive vertical direction, we get the complex plane seen through Cartesian coordinates.

The position of a complex number $z$ can also be given in polar coordinates $(r, \theta)$. As mentioned above, $r$ is the modulus of $z$.

The angle $\theta$ from the positive real axis to the vector of a **nonzero** complex number $z=x+\mathrm{i}y$ satisfies:

$$
\tan \theta=\frac{y}{x}
$$

It is called the **argument** of $z$, written:

$$
\theta= \arg z
$$

Every **nonzero** complex number $z$ has infinitely many arguments, so $\arg z$ is actually a set. We use $\operatorname{Arg} z$, with a capital letter, to denote **one particular value** that satisfies:

$$
-\pi<\operatorname{Arg} z \le \pi
$$

$\operatorname{Arg} z$ is called the **principal value of the argument**, or the **principal argument**. Any argument is the principal argument plus some integer multiple $2k\pi$ (where $k$ may be zero or negative), that is, $\arg z = \{\operatorname{Arg} z + 2k\pi \mid k\in \mathbf Z\}$.

Note that the sum of two principal arguments is not necessarily a principal argument, but the sum of two arguments is always a valid argument.

The shape formed in the complex plane by complex numbers with modulus less than $1$ is called the **unit disk**. A complex number with modulus equal to $1$ is called a **unit complex number**, and the shape formed in the complex plane by all unit complex numbers is called the **unit circle**. When there is no risk of confusion, the term "unit disk" is sometimes also used loosely to mean the unit circle.

From the polar point of view, multiplication and division of complex numbers become very simple. To multiply complex numbers, multiply the moduli and add the arguments. To divide complex numbers, divide the moduli and subtract the arguments.

### Euler's formula

???+ note "Euler's formula[^ref1]"
    For any real number $x$,
    
    $$
    \mathrm{e}^{\mathrm{i}x}=\cos x+\mathrm{i}\sin x
    $$
    
    After defining the [complex exponential and complex trigonometric functions](#exponential-and-trigonometric-functions), this formula extends to all complex numbers.

### Exponential and trigonometric functions

For a complex number $z=x+\mathrm{i}y$, the function $f(z)=\mathrm{e}^x(\cos y+\mathrm{i}\sin y)$ satisfies $f(z_1+z_2)=f(z_1)f(z_2)$. This gives the definition of the **complex exponential function**:

$$
\exp z=\mathrm{e}^x(\cos y+\mathrm{i}\sin y)
$$

On the real numbers, the complex exponential function is exactly the same as the real exponential function. On the complex plane it has these properties:

-   Always positive modulus: $|\exp z|=\exp x>0$.
-   Argument: $\arg(\exp z)=\{y + 2k\pi \mid k\in\mathbf Z\}$.
-   Addition theorem: $\exp (z_1+z_2)=\exp (z_1)\exp (z_2)$.
-   Periodicity: $\exp z$ is a periodic function with fundamental period $2\pi \mathrm{i}$. If every period of a function $f(z)$ is an integer multiple of some period, that period is called the **fundamental period**.

The **complex trigonometric functions** (also simply called **trigonometric functions**) are defined as:

$$
\cos z=\frac{\exp (\mathrm{i}z)+\exp (-\mathrm{i}z)}{2}
$$

$$
\sin z=\frac{\exp (\mathrm{i}z)-\exp (-\mathrm{i}z)}{2\mathrm{i}}
$$

If $z\in\mathbf{R}$, then by [Euler's formula](#eulers-formula):

$$
\cos z=\operatorname{Re}\left(\mathrm{e}^{\mathrm{i}z}\right)
$$

$$
\sin z=\operatorname{Im}\left(\mathrm{e}^{\mathrm{i}z}\right)
$$

On the real numbers, the complex trigonometric functions are exactly the same as the real trigonometric functions. On the complex plane they have these properties:

-   Parity: sine is an odd function and cosine is an even function.
-   Trigonometric identities: the usual trigonometric identities all hold, for example the sum of squares being $1$, or the angle addition and subtraction formulas.
-   Periodicity: sine and cosine have fundamental period $2\pi$.
-   Zeros: the zeros of real sine and real cosine are exactly all the zeros of complex sine and complex cosine. The extension adds no new zeros.
-   Unbounded modulus: the modulus of complex sine and complex cosine can be larger than any given positive number. Unlike real sine and real cosine, they are no longer bounded by $1$.

## Three forms of a complex number

Using the Cartesian and polar points of view, we can write a complex number in three forms.

The **algebraic form** can represent any complex number.

$$
z=x+y\mathrm{i}
$$

The algebraic form is convenient for computing the four operations: addition, subtraction, multiplication and division.

The **trigonometric form** and the **exponential form** represent nonzero complex numbers.

$$
z=r(\cos \theta +\mathrm{i}\sin \theta)=r \exp (\mathrm{i}\theta)
$$

These two forms are more convenient for multiplication, division and the operations that come later. If you only want to use functions seen in high school, use the trigonometric form. Once the complex exponential function is introduced, the equivalent exponential form is more convenient.

## Roots of unity

Consider the solutions of $x^n=1$ over the complex numbers. Clearly there are $n$ such solutions, and each of them is called an **$n$-th root of unity** (complex root of unity). From what we know about the complex plane, the $n$-th roots of unity divide the unit circle into $n$ equal parts.

Let $\omega_n=\exp\dfrac{2\pi \mathrm{i}}{n}$ (the unit complex number with argument $2\pi/n$). Then the solution set of $x^n=1$ is $\{\omega_n^k\mid k=0,1\cdots,n-1\}$, where

$$
w_n^k = \exp\dfrac{2\pi k \mathrm{i}}{n} = \cos\dfrac{2\pi k}{n} + \mathrm{i}\sin\dfrac{2\pi k}{n}.
$$

Unless stated otherwise, "the $n$-th root of unity" usually means the first solution counterclockwise from $1$, that is, $\omega_n$ above. All other solutions can be written as powers of $\omega_n$.

???+ tip "Why does 'the $n$-th root of unity' usually mean the first one?"
    Mainly for convenience in applications. All $n$-th roots of unity can be written as powers of the first $n$-th root of unity $\omega_n$. Also, for any $k < n$, the complex number $\omega_n$ is not a $k$-th root of unity.

### Primitive roots of unity

In fact, $\omega_n$ is not the only $n$-th root of unity with this kind of property. The elements of the set

$$
\{\omega_n^k\mid 0\le k<n,~\gcd(n,k)=1\}
$$

are called **$n$-th primitive roots of unity**. From this expression, there are $\varphi(n)$ primitive $n$-th roots of unity in total, where $\varphi(n)$ is [Euler's totient function](./number-theory/euler-totient.md).

Every primitive root of unity $\omega$ has the same property as $\omega_n$ above: for any $0<k<n$, the $k$-th power of $\omega$ is not $1$. In other words, $\omega$ is not a $k$-th root of unity. Therefore, any primitive root of unity can generate all the roots of unity.

To understand the structure of the $n$-th primitive roots of unity, we need the following property of roots of unity:

???+ note "Property"
    For integers $n$ and $k$, let $d=\gcd(n,k)$. Then $\omega_n^k = \omega_{n/d}^{k/d}$.

??? note "Proof"
    By direct computation,
    
    $$
    w_n^k = \exp\dfrac{2\pi k\mathrm{i}}{n} = \exp\dfrac{2\pi (k/d)\mathrm{i}}{n/d} = \omega_{n/d}^{k/d}.
    $$

This shows that whenever $\gcd(n,k)\neq 1$, $\omega_n^k$ must be a (primitive) $\dfrac{n}{\gcd(n,k)}$-th root of unity. So a root of unity $\omega_n^k$ with the property above must satisfy $\gcd(n,k)=1$. This is exactly why primitive roots of unity are defined the way they are.

Also, as a simple corollary of this analysis:

???+ note "Theorem"
    As $k$ ranges over the divisors of $n$, the primitive $k$-th roots of unity together form a partition of the $n$-th roots of unity. Moreover, for $\ell\perp n$, the map $x\mapsto x^\ell$ is a bijection on the $n$-th roots of unity that preserves this partition: it maps primitive $k$-th roots of unity (for $k\mid n$) to primitive $k$-th roots of unity.

Although there are many choices of primitive root of unity, the first root $\omega_n$ has the simplest form, so $\omega_n$ is still the most commonly used one in competitive programming. In some situations, to make computation faster, you can also replace $\omega_n$ in the complex numbers with a [primitive root of unity](./number-theory/residue.md#roots-of-unity) modulo some number.

## Complex numbers in programming languages

### Complex numbers in C

The C99 standard has the `<complex.h>` header.

The `<complex.h>` header provides three types: `double complex`, `float complex` and `long double complex`.

The arithmetic operators '+', '-', '\*' and '/' can be used with any mix of floating-point and complex numbers. If either operand of an expression is complex, the result is complex.

The header `<complex.h>` provides the imaginary unit `I`. When this header is included, the capital letter `I` cannot be used as a variable name.

For a single complex number, `<complex.h>` provides several operations: `creal` extracts the real part, `cimag` extracts the imaginary part, `cabs` computes the modulus, and `carg` computes the principal argument.

Every function comes in three versions for different types. For example, `creal` comes as `creal`, `crealf` and `creall`, which handle `double`, `float` and `long double` respectively. The version with no suffix handles `double` by default. All functions below follow the same pattern, which we will not repeat.

These functions all return ordinary floating-point numbers. You can assign an ordinary floating-point number directly to a complex number, but you cannot assign a complex number directly to a floating-point number; you need to use the extraction operations above.

The function `conj` computes the complex conjugate and returns a complex number.

The function `cexp` computes the complex exponential, `clog` the principal value of the logarithm, `csin` the sine, `ccos` the cosine, and `ctan` the tangent.

The function `cpow` computes powers, `csqrt` the square root, `casin` the inverse sine, `cacos` the inverse cosine, and `catan` the inverse tangent. All of these compute the principal value of a multivalued function.

### Complex numbers in C++

The C header `<ctype.h>` becomes `<cctype>` in C++, and almost every header follows this naming pattern.

However, `<complex.h>` does not. C++ has no `<ccomplex>` header. C++ complex numbers live directly in `<complex>`, and its contents are completely different from C's.

This is interesting. The reason is that the first version of C++, C++98, already had `<complex>`, while C only added it in C99.

In C++, complex types are `complex<float>`, `complex<double>` and `complex<long double>`. Thanks to object-oriented polymorphism (overloading), each function below has a single name, with no f or l suffix.

A complex object has member functions `real` and `imag` to access the real and imaginary parts.

There are non-member functions `real`, `imag`, `abs` and `arg` that return the real part, imaginary part, modulus and argument.

There are also non-member functions `norm`, the square of the modulus, and `conj`, the complex conjugate.

There are also non-member functions `exp`, `log` (principal value of the logarithm with base $\mathrm{e}$), `log10` (principal value of the base-10 logarithm, not in C), `pow`, `sqrt`, `sin`, `cos` and `tan`, with the same meanings as in C.

C++14 and later define the [literal operators `std::literals::complex_literals::""if, ""i, ""il`](https://zh.cppreference.com/w/cpp/numeric/complex/operator%2522%2522i.html). For example, `100if`, `100i` and `100il` return `std::complex<float>{0.0f, 100.0f}`, `std::complex<double>{0.0, 100.0}` and `std::complex<long double>{0.0l, 100.0l}` respectively. This lets us conveniently write complex declarations like `auto z = 4.0 + 3i`.

## References and links

-   [Complex number - Wikipedia](https://en.wikipedia.org/wiki/Complex_number)
-   [Euler's formula - Wikipedia](https://en.wikipedia.org/wiki/Euler's_formula)
-   [Complex number arithmetic - cppreference.com](https://en.cppreference.com/w/c/numeric/complex)
-   [std::complex - cppreference.com](https://en.cppreference.com/w/cpp/numeric/complex)

[^ref1]: For more on Euler's formula, see these two videos (in Chinese): [Euler's formula and introductory group theory](https://www.bilibili.com/video/BV1fx41187tZ), [Differential equations overview - Chapter 5: understanding $\mathrm{e}^{\mathrm{i}\pi}$ in 3.14 minutes](https://www.bilibili.com/video/BV1G4411D7kZ).
