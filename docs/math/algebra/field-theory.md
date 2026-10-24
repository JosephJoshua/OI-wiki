Prerequisites: [Basic Concepts of Abstract Algebra](./basic.md), [Group Theory](./group-theory.md), [Ring Theory](./ring-theory.md)

## Introduction

**Field theory** is the theory of fields.

The field theory covered on this page is mainly the theory of field extensions. A field is an algebraic structure closed under addition, subtraction, multiplication and division. In competitive programming we often work modulo a prime $p$, which is the same as computing in the finite field $\mathbf F_p$. Just as with the real field $\mathbf R$, some problems are easier to solve by computing in a larger field (the complex field $\mathbf C$). A common example is using the [Fast Fourier Transform](../poly/fft.md) to speed up multiplying polynomials with real coefficients. The same kind of thing can be done for finite fields. Most readers are less familiar with extensions of finite fields, so it helps to learn the general theory of field extensions. The end of this page gives some algorithmic applications that need extensions of finite fields, and also briefly discusses extensions of the ring of integers that some of these applications may need.

Closely related to field theory is Galois theory. It links a field extension to its automorphism group, so that properties of field extensions can be understood with tools from group theory. Although this theory is usually a core part of algebra courses, it is far from what competitive programming needs, so this page does not go into it much. Interested readers should consult specialized textbooks.

???+ info "Notation"
    When there is no ambiguity, this page may omit the multiplication sign of rings and fields, and will write the ring $(R,+,\cdot)$ as the ring $R$ and the field $(F,+,\cdot)$ as the field $F$. The additive identity of a ring or field is called the zero, and the multiplicative identity is called the unity (or one). Also, on this page $p$ is always a prime and $q$ is always a prime power, which can be written as $p^n$ where $n$ is a positive integer.

## Field extensions

As with groups and rings, we can define subfields and field homomorphisms.

???+ abstract "Subfield"
    For a field $F$, if a subring $E$ of $F$ is also a field, then $E$ is called a **subfield** of $F$.

Here, no matter how the definitions of rings and subrings treat the unity, a subfield $E$ must contain the unity of the field $F$.[^subfield-one]

???+ abstract "Field homomorphism"
    A ring homomorphism $\varphi:F\rightarrow E$ from a field $F$ to a field $E$ is also called a **field homomorphism** from $F$ to $E$.

??? info "How field homomorphisms treat the unity"
    If, unlike the definition used here, ring homomorphisms are required to map the unity to the unity, then field homomorphisms naturally must also map the unity to the unity. Otherwise, the unity may also be mapped to zero.

Since a field has only trivial ideals, a field homomorphism either maps the whole field to zero or is an embedding. This means that the study of field homomorphisms can be reduced to the study of subfields.

For fields, the smaller field is usually the more familiar one. So we usually take the subfield as the base and study the larger field from there. This is the idea of a field extension.

???+ abstract "Field extension"
    For a field $F$, if $F$ is a subfield of $E$, then the field $E$ is called an **extension** of $F$, or an **extension field**, written $E/F$.

???+ info "Notation for field extensions"
    Although the notation looks the same, field extensions have nothing to do with quotient rings. Do not confuse them.

???+ example "Example"
    The complex field $\mathbf C$ is an extension of the real field $\mathbf R$, and the real field $\mathbf R$ is in turn an extension of the rational field $\mathbf Q$.

### Degree of a field extension

For a field extension $E/F$, the field $E$ is always a [vector space](../linear-algebra/vector-space.md) over $F$. The dimension of this vector space is the degree of the extension.

???+ abstract "Degree of a field extension"
    The **degree** of a field extension $E/F$ is the dimension of $E$ viewed as a vector space over $F$, that is, $\dim_F(E)$, written $[E:F]$. If the degree is finite, the extension is called a **finite extension**; otherwise it is called an **infinite extension**.

???+ example "Example"
    The degree $[\mathbf C:\mathbf R]$ of the extension $\mathbf C/\mathbf R$ is $2$, so it is a finite extension. The extension $\mathbf R/\mathbf Q$ is an infinite extension.

Degrees of field extensions are multiplicative.

???+ note "Theorem"
    Let $F\subseteq K\subseteq E$ be fields. Then their degrees satisfy $[E:F]=[E:K][K:F]$.

??? note "Proof"
    If a degree is infinite, this is obvious. Otherwise, if $\{\alpha_i\}$ is a basis of $E$ as a vector space over $K$ and $\{\beta_j\}$ is a basis of $K$ as a vector space over $F$, one can check that $\{\alpha_i\beta_j\}$ is a basis of $E$ as a vector space over $F$.

This page mainly deals with finite extensions.

### Characteristic of a field

A natural starting point for studying field extensions is the smallest subfield containing the unity of $F$. This field is called the **prime subfield** of $F$.

The structure of the prime subfield is determined entirely by the properties of the field's unity. The characteristic of a field sums up these properties.

???+ abstract "Characteristic of a field"
    The **characteristic** of a field $F$ is the smallest positive integer $n$ such that $n\cdot 1=0$. If no such $n$ exists, the characteristic of $F$ is said to be $0$. Here $n\cdot 1$ means the sum of $n$ copies of the unity $1$. If the characteristic of $F$ is not $0$, $F$ is said to have **finite characteristic**.

The characteristic can be understood through ring homomorphisms. The ring of integers $\mathbf Z$ is the closed structure obtained by starting from $0$ and $1$ and repeatedly applying addition, subtraction and multiplication. It can be seen as a kind of "prototype": every ring with unity should "inherit" part of the structure of the integers.[^initial-object-ring] So for a field $F$, we can look at ring homomorphisms $\varphi:\mathbf Z\rightarrow F$ with $\varphi(1)=1$. Such a homomorphism is uniquely determined: it maps $n\in\mathbf N_+$ to $n\cdot 1$, the sum of $n$ copies of the unity $1$. Its image $\varphi(\mathbf Z)$ is embedded in the field $F$, so it has a unity, is commutative and has no zero divisors. Hence it is an integral domain. So the kernel $\ker\varphi$ must be a prime ideal. The prime ideals of $\mathbf Z$ can only have the form $(n)$, where $n=0$ or $n$ is a prime. The $n$ obtained this way is the characteristic of the field.

The characteristic determines the structure of the prime subfield:

1.  When the characteristic is $0$, the homomorphism $\varphi$ is injective, so $\mathbf Z$ is embedded in $F$. The rational field $\mathbf Q$, being the smallest field containing the integers, must also embed in $F$. It is the prime subfield of $F$;
2.  When the characteristic is a prime $p$, the image $\mathbf Z/p\mathbf Z$ of $\varphi$ is embedded in $F$. Here $\mathbf Z/p\mathbf Z$ is already a field, written $\mathbf F_p$, and it is the prime subfield of $F$.

This discussion actually proves the following:

???+ note "Theorem"
    The characteristic of a field $F$ can only be $0$ or a prime $p$. A field of characteristic $0$ has prime subfield $\mathbf Q$, and a field of characteristic $p$ has prime subfield $\mathbf F_p$.

The fields $\mathbf Q$ and $\mathbf F_p$ in the theorem are also called **prime fields**, meaning fields whose only subfield is themselves. A finite field must have finite characteristic, because a field of characteristic $0$ contains at least the subfield $\mathbf Q$.

Fields of finite characteristic often behave differently from fields of characteristic zero. For example, fields of finite characteristic have the following properties:

???+ note "Theorem"
    Let $F$ have characteristic $p$. Then:
    
    1.  In the additive group of $F$, every nonzero element has order $p$, that is, $px=0$ for all $x\in F$;
    2.  The "freshman's dream": $(x+y)^p=x^p+y^p$ for all $x,y\in F$. Moreover, the map $x\mapsto x^p$ is an injective endomorphism of $F$, called the **Frobenius endomorphism**.

??? note "Proof"
    For the first property, just note that $px=(p1)x=0x=0$. For the second, note that in the binomial expansion of $(x+y)^p$, every term other than $x^p$ and $y^p$ has a coefficient divisible by $p$, so by the first property $(x+y)^p=x^p+y^p$. To check that $x\mapsto x^p$ is an endomorphism, we also need $(xy)^p=x^py^p$, which holds because multiplication in a field is commutative. Finally, a ring homomorphism between fields that maps the unity to the unity must be injective.

Of course, for a finite field the Frobenius endomorphism must also be surjective, so it is an automorphism of the field.

### Simple extensions

Just like extending the real field to the complex field, many extensions can be built by adding extra elements to a field and specifying how they behave under the operations. In general, to avoid the trouble of specifying those rules, we may consider a field extension $E/F$ and adjoin elements of $E\setminus F$ to $F$. Then the rules for operating on these extra elements together with elements of $F$ are already fixed inside the larger field $E$.

???+ abstract "Extension generated by a subset"
    Let $E/F$ be a field extension and $S\subseteq E$. The **extension generated by $S$ over $F$** is the smallest subfield of $E$ that contains both $F$ and $S$, written $F(S)$.

The simplest case, of course, is when $S$ has very few elements.

???+ abstract "Finitely generated extension"
    Let $E/F$ be a field extension. If there is a finite set $S=\{\alpha_1,\cdots,\alpha_n\}\subseteq E$ such that $E=F(S)$, then $E$ is called a **finitely generated extension** of $F$, also written $F(\alpha_1,\cdots,\alpha_n)$.

???+ abstract "Simple extension"
    Let $E/F$ be a field extension. If there is $\alpha\in E$ such that $E=F(\alpha)$, then $E$ is called a **simple extension** of $F$. The element $\alpha$ is called a **primitive element** of this simple extension.

???+ example "Example"
    These examples are all obtained by adjoining elements of $\mathbf C$ to $\mathbf Q$.
    
    1.  For a square-free integer $D\neq 0,1$, the quadratic field $\mathbf Q(\sqrt D)$ is the simple extension obtained by adjoining $\sqrt D\in\mathbf C\setminus\mathbf Q$ to $\mathbf Q$. Its degree is $2$, because $\{1,\sqrt D\}$ is a basis.
    2.  The field $\mathbf Q(\sqrt 2,\sqrt 3)$ is the extension obtained by adjoining $\sqrt 2$ and $\sqrt 3$ to $\mathbf Q$. Of course $\mathbf Q(\sqrt 2,\sqrt 3)=\mathbf Q(\sqrt 2)(\sqrt 3)=\mathbf Q(\sqrt 3)(\sqrt 2)$, so the final extension does not depend on the order or the way the elements are added. It is also a simple extension, because $\mathbf Q(\sqrt 2,\sqrt 3)=\mathbf Q(\sqrt 2+\sqrt 3)$. Its degree is $4$, because $\{1,\sqrt 2,\sqrt 3,\sqrt 6\}$ is a basis.
    3.  The field $\mathbf Q(\pi)$ is also a simple extension, where $\pi$ is the circle constant. It is an infinite extension, because $\mathbf Q[\pi]\subseteq \mathbf Q(\pi)$ already has the basis $\{1,\pi,\pi^2,\cdots\}$.
    4.  A finitely generated extension need not be simple. For example, let $x,y$ be two indeterminates. Then the field of rational functions $\mathbf Q(x,y)$ is a finitely generated extension of $\mathbf Q$, but its transcendence degree is $2$, so it is not a simple extension.

These examples show that simple extensions can have very different properties. It depends on the properties of the element being adjoined.

### Algebraic extensions

To analyze every case that can happen when adjoining an element to a field, we can follow the earlier discussion of the characteristic and look at ring homomorphisms from the polynomial ring $F[x]$ to an extension $E/F$. Here $F[x]$ plays the role that $\mathbf Z$ played before: it is exactly the "prototype" of the structure obtained by adjoining an indeterminate $x$ to $F$ and closing under addition, subtraction and multiplication.[^polynomial-universal]

Let $\varphi:F[x]\rightarrow E$ be a ring homomorphism whose restriction to $F$ is the identity and with $\varphi(x)=\alpha$; that is, it maps the indeterminate to some element of the extension $E$. Since the image $\varphi(F[x])=F[\alpha]$ must be an integral domain, the kernel $\ker\varphi$ must be a prime ideal of $F[x]$. A polynomial ring over a field is a principal ideal domain, so the kernel has the form $(f(x))$, where $f(x)=0$ or $f(x)$ is an irreducible element of $F[x]$. There are the following cases:

1.  When the kernel $\ker\varphi=\{0\}$, the polynomial ring $F[x]$ embeds in $E$, and its image $F[\alpha]$ is an integral domain. So the smallest field in $E$ containing both $F$ and $\alpha$ is the field of fractions of $F[\alpha]$, namely $F(\alpha)$. This notation can be read either as substituting $\alpha$ for the indeterminate in the field of rational functions $F(x)$, or as the simple extension of $F$ generated by $\alpha$. In this context, the two readings give the same result;

2.  When the kernel $\ker\varphi=(f(x))$ with $f(x)$ irreducible, we have $\varphi(f(x))=f(\alpha)=0$, that is, $\alpha\in E$ is a root of the polynomial $f(x)$ over $F$. Since $F$ is a field, we may assume $f(x)$ is monic. In this case the image of $\varphi$ is the field $F(\alpha)$, so

    $$
    F[x]/(f(x))\cong F(\alpha).
    $$

    This splits into two more cases:

    1.  If $f(x)$ has degree one, that is, $f(x)=x-\alpha$, then $\alpha\in F$, so the extension $F(\alpha)=F$ is trivial;
    2.  Otherwise, $f(x)$ is an irreducible polynomial of degree greater than one and $\alpha\in E\setminus F$. Then the image $F[\alpha]$ is already a field containing $F$ and $\alpha$, so it is $F(\alpha)$, the extension of $F$ generated by $\alpha$, and $F(\alpha)\supset F$ is not trivial.

This discussion motivates the following definitions:

???+ abstract "Algebraic and transcendental elements"
    For an extension $E/F$, if an element $\alpha\in E$ is a root of some nonzero polynomial $f(x)$ over $F$, then $\alpha$ is called **algebraic** over $F$ (an **algebraic element**). Otherwise $\alpha$ is called **transcendental** over $F$ (a **transcendental element**).

???+ abstract "Minimal polynomial"
    For an algebraic element $\alpha$ over a field $F$, the monic polynomial $f(x)$ of smallest degree having $\alpha$ as a root is called its **minimal polynomial**.

The minimal polynomial here is exactly the irreducible polynomial $f(x)$ from the analysis above. Of course, one can also prove directly that minimal polynomials are irreducible. The minimality of $f(x)$ means that any polynomial over $F$ that has $\alpha$ as a root must have $f(x)$ as a factor.

???+ example "Example"
    1.  $\sqrt 2$ is algebraic over $\mathbf Q$, with minimal polynomial $x^2-2$.
    2.  $\sqrt 2$ is algebraic over $\mathbf R$, with minimal polynomial $x-\sqrt 2$.
    3.  $\pi$ is transcendental over $\mathbf Q$.
    4.  In general, elements algebraic over $\mathbf Q$ are called **algebraic numbers**, and transcendental elements are called **transcendental numbers**. In particular, if the minimal polynomial of an algebraic number has integer coefficients, it is called an **algebraic integer**. The algebraic integers in an algebraic extension form a ring. For example, the algebraic integers in the quadratic field $\mathbf Q(\sqrt{D})$ form the ring of quadratic integers $\mathbf Z[\omega]$. For the meaning of this notation, see [ring of quadratic integers](./ring-theory.md#例子二次整数环).

???+ abstract "Algebraic and transcendental extensions"
    For an extension $E/F$, if every element of $E$ is algebraic over $F$, then $E$ is called an **algebraic extension** of $F$. Otherwise $E$ is called a **transcendental extension** of $F$.

Simple extensions fall into two classes, depending on the element adjoined. When the adjoined element is transcendental, the simple extension is always isomorphic to a field of rational functions. In that case nothing can be simplified further. But when the adjoined element is algebraic, the simple extension is actually $F[\alpha]$, the result of replacing the indeterminate $x$ in $F[x]$ with $\alpha$. From an elementary point of view, compared with the transcendental case, elements of this extension field need no denominators. This means that a process like "rationalizing the denominator" in elementary arithmetic always works in a simple extension by an algebraic element. Since the extension fields in competitive programming are mainly simple algebraic extensions, the next section discusses how to compute in them in more detail.

The importance of simple algebraic extensions is also reflected in the following theorem:

???+ note "Theorem"
    A field extension is finite if and only if it is a finitely generated algebraic extension.

??? note "Proof"
    Let $F$ be a field and $E=F(\alpha_1,\cdots,\alpha_n)$ a finitely generated algebraic extension, so every $\alpha_i$ is algebraic over $F$. Let $E_i=F(\alpha_1,\cdots,\alpha_i)$, so $E_0=F$ and $E_n=E$. Note that $\alpha_i$ must be algebraic over $E_{i-1}$, because the minimal polynomial of $\alpha_i$ over $F$ is also a polynomial over $E_{i-1}$; moreover, the degree of the minimal polynomial of $\alpha_i$ over $E_{i-1}$ is at most the degree of its minimal polynomial over $F$. So $[E_i:E_{i-1}]$ must be finite, and by the multiplicativity of degrees, $[E:F]=\prod_{i=1}^n[E_i:E_{i-1}]$ is finite too. Conversely, start with $E_0=F$. Given $E_i$, pick an element $\alpha_{i+1}$ from $E\setminus E_i$ and adjoin it to $E_i$ to get the extension field $E_{i+1}=E_i(\alpha_{i+1})$, until $E_n=E$. Since the remaining degree keeps decreasing, this process must stop after finitely many steps. Hence a finite extension must be a finitely generated algebraic extension.

This means that to understand finite extensions, it is enough to understand simple algebraic extensions, because every finite extension can be obtained by finitely many simple algebraic extensions.

### Structure of and computation in simple algebraic extensions

In this section, let $F$ be a field, $E$ an extension field of it, and $\alpha\in E\setminus F$ an element algebraic over $F$. Let the minimal polynomial of $\alpha$ be $f(x)$, a monic polynomial of degree $n$, that is,

$$
f(x)=x^n+a_{n-1}x^{n-1}+\cdots+a_1x+a_0,
$$

where $a_0,a_1,\cdots,a_{n-1}\in F$ and $f(x)$ is irreducible over $F$.

The isomorphism $F(\alpha)\cong F[x]/(f(x))$ tells us that computing in the extension field $F(\alpha)$ is the same as computing with polynomials modulo $f(x)$. By polynomial division with remainder, we only need to consider the congruence classes of polynomials of degree less than $n=\deg f(x)$. For these polynomials, a natural basis is $\{1,\alpha,\cdots,\alpha^{n-1}\}$. So we have:

???+ note "Theorem"
    Under the assumptions of this section, the extension field $F(\alpha)$ can be written as
    
    $$
    F(\alpha)=\{\lambda(\alpha)=\lambda_0+\lambda_1\alpha+\cdots+\lambda_{n-1}\alpha^{n-1}:\lambda_0,\lambda_1,\cdots,\lambda_{n-1}\in F\}.
    $$
    
    Here $\lambda(x)$ ranges over all polynomials of degree less than $n$. So the degree $[F(\alpha):F]=n$, the degree of the minimal polynomial of $\alpha$. In the extension field, adding $\lambda(\alpha)$ and $\mu(\alpha)$ is just polynomial addition: add the coefficients in matching positions. Multiplying $\lambda(\alpha)$ and $\mu(\alpha)$ gives $\rho(\alpha)$, where $\rho(x)$ is the remainder of the product $\lambda(x)\mu(x)$ divided by $f(x)$.

Of course, since it is a field, we can also divide elements of $F(\alpha)$. By the multiplication process described in the theorem, this amounts to solving a [linear congruence](../number-theory/linear-equation.md) over the polynomial ring. As with integers, to compute the quotient $\lambda(\alpha)/\mu(\alpha)$, first find the multiplicative inverse of $\mu(\alpha)$, then multiply it by $\lambda(\alpha)$. To find the inverse of $\mu(\alpha)$, solve the congruence $\mu(x)\xi(x)\equiv 1\pmod{f(x)}$. This can be done with the extended Euclidean algorithm.

Below, a few concrete examples show the details of the computation.

???+ example "Example"
    Consider the extension field $\mathbf Q(\alpha)$, where $\alpha$ is a root of $x^3-2x-2=0$. We want to compute the value of
    
    $$
    \frac{1+\alpha}{1+\alpha+\alpha^2}
    $$
    
    .
    
    The first step is to compute the inverse of $1+\alpha+\alpha^2$, that is, to find a solution of
    
    $$
    (x^2+x+1)\xi(x)+(x^3-2x-2)\nu(x)=1
    $$
    
    . We apply the extended Euclidean algorithm. First run the Euclidean algorithm:
    
    $$
    \begin{aligned}
    x^3-2x-2 &= (x-1)(x^2+x+1)+(-2x-1),\\
    x^2+x+1 &= \left(-\frac12x-\frac14\right)(-2x-1)+\frac34,\\
    -2x-1 &= \left(-\frac{8}{3}x-\frac{4}{3}\right)\frac{3}{4}.
    \end{aligned}
    $$
    
    Then work out the coefficients in the congruence:
    
    $$
    \begin{aligned}
    \frac{3}{4}
    &=(x^2+x+1)+\left(\frac12x+\frac14\right)(-2x-1)\\
    &=(x^2+x+1)+\left(\frac12x+\frac14\right)\left((x^3-2x-2)-(x-1)(x^2+x+1)\right)\\
    &=\left(-\frac12x^2+\frac14x+\frac54\right)(x^2+x+1)+\left(\frac12x+\frac14\right)(x^3-2x-2).
    \end{aligned}
    $$
    
    So a solution is
    
    $$
    \xi(x)=-\frac23x^2+\frac13x+\frac53,\ \nu(x)=\frac23x+\frac13.
    $$
    
    This shows that the inverse of $1+\alpha+\alpha^2$ is
    
    $$
    -\frac23\alpha^2+\frac13\alpha+\frac53.
    $$
    
    The second step is to multiply this inverse by $1+\alpha$:
    
    $$
    \begin{aligned}
    (1+\alpha)\left(-\frac23\alpha^2+\frac13\alpha+\frac53\right)
    &=-\frac23\alpha^3-\frac13\alpha^2+2\alpha+\frac53\\
    &=-\frac23(2\alpha+2)-\frac13\alpha^2+2\alpha+\frac53\\
    &=-\frac13\alpha^2+\frac23\alpha+\frac13.
    \end{aligned}
    $$
    
    This is the final answer.

The example only used the fact that $\alpha$ is a root of the equation; it never said which root. The polynomial $x^3-2x-2=0$ has one real root and a pair of complex conjugate roots in $\mathbf C$, and adjoining any one of them to $\mathbf Q$ gives isomorphic extension fields. In other words, from the algebraic point of view, these three distinct roots cannot be told apart.

In general, if an irreducible polynomial $f(x)$ over a field $F$ has distinct roots $\alpha\neq\beta$ in some extension field, these roots show the same algebraic behavior when each is used to make a simple extension of $F$. Such roots are called **conjugates** of each other. The usual conjugate of a complex number is the special case of this concept for the extension $\mathbf C/\mathbf R$.

???+ example "Example"
    Consider the extension field $\mathbf F_2(\alpha)$, where $\alpha$ is a root of $x^2+x+1=0$. In general, for $a+b\alpha$ and $c+d\alpha$ the rules are
    
    $$
    \begin{aligned}
    (a+b\alpha)+(c+d\alpha)&=(a+c)+(b+d)\alpha,\\
    (a+b\alpha)(c+d\alpha)&=ac+(ad+bc)\alpha+bd\alpha^2\\
    &=(ac+bd)+(ad+bc+bd)\alpha.
    \end{aligned}
    $$
    
    These rules are similar to those for complex numbers. Most readers will find such a root $\alpha$ unfamiliar, but that does not stop us from computing with the elements of this field. In fact, $[\mathbf F_2(\alpha):\mathbf F_2]=2$, so as a vector space $|\mathbf F_2(\alpha)|=4$; that is, we get a finite field of size $4$. We will see later that every finite field is built this way.

For small computations, reducing modulo a monic polynomial $f(x)$ can usually be done by substituting

$$
x^n=-a_{n-1}x^{n-1}-\cdots-a_1x-a_0
$$

to lower the degree of the target polynomial. Also, for extensions of low degree, one can often work out the rules for the coefficients directly and use an implementation similar to a complex-number class, without doing a modulo step each time.

For an example of a simple algebraic extension, see the finite field [reference implementation](#reference-implementation) below.

In practice, the algorithms described here can only handle extensions of fairly low degree, which is enough for almost all applications in competitive programming. When the degree is high enough to become the complexity bottleneck, use suitable polynomial techniques ([Fast Fourier Transform](../poly/fft.md), [Number Theoretic Transform](../poly/ntt.md), [fast polynomial modulo](../poly/elementary-func.md#多项式除法--取模), [polynomial Euclidean algorithm](../poly/intro.md#因式分解和欧几里得), etc.) to speed things up.

### Splitting fields

The structure of simple algebraic extensions was discussed in detail above. But such an extension is often not enough:

???+ example "Example"
    Consider the extension $\mathbf Q(\sqrt[3]{2})/\mathbf Q$. The minimal polynomial of the algebraic element $\sqrt[3]{2}$ over $\mathbf Q$ is $x^3-2$. In $\mathbf C$, the polynomial $x^3-2$ has three roots: $\sqrt[3]{2},\sqrt[3]{2}\omega,\sqrt[3]{2}\omega^2$, where $\omega=\mathrm{e}^{2\pi\mathrm{i}/3}$ is a primitive cube root of unity. Although $\mathbf Q(\sqrt[3]{2})\cong\mathbf Q(\sqrt[3]{2}\omega)\cong\mathbf Q(\sqrt[3]{2}\omega^2)$, the field $\mathbf Q(\sqrt[3]{2})$ does not contain the other two roots, so even an operation like $\sqrt[3]{2}+\sqrt[3]{2}\omega$ cannot be carried out. To study all three roots together, we must extend $\mathbf Q(\sqrt[3]{2})$ further, to $\mathbf Q(\sqrt[3]{2},\sqrt[3]{2}\omega,\sqrt[3]{2}\omega^2)$.
    
    As shown earlier, such an extension can be made by doing simple extensions one element at a time. Note that the minimal polynomial of $\sqrt[3]{2}\omega$ over $\mathbf Q$ differs from the one over $\mathbf Q(\sqrt[3]{2})$: the former is $x^3-2\in\mathbf Q[x]$, while the latter is $x^2+\sqrt[3]{2}x+\sqrt[3]{4}\in \mathbf Q(\sqrt[3]{2})[x]$, because
    
    $$
    x^3-2 = (x-\sqrt[3]{2})(x^2+\sqrt[3]{2}x+\sqrt[3]{4}).
    $$
    
    After the field is extended, the original minimal polynomial splits off a linear factor, so the minimal polynomial of the remaining roots has lower degree than over the original field. Extending the field step by step is the same as "splitting" the polynomial step by step. So at every simple extension, the minimal polynomial has to be determined again.

Adjoining all roots of a polynomial to a field gives the splitting field of the polynomial.

???+ abstract "Split"
    Let $F$ be a field. If a polynomial $f(x)$ can be factored in $F[x]$ into a product of linear factors, we say $f(x)$ **splits** over $F$.

???+ abstract "Splitting field"
    For a polynomial $f(x)$ over a field $F$, if an extension $E/F$ is such that $f(x)$ splits over $E$ but not over any proper subfield of $E$, then $E$ is called the **splitting field** of $f(x)$.

One can prove that, as with simple extensions, the splitting field of a given polynomial is unique up to isomorphism, regardless of how it is constructed. A splitting field is always a finite extension.

???+ abstract "Normal extension"
    For an algebraic extension $E/F$, if for every $\alpha\in E$ the minimal polynomial of $\alpha$ splits over $E$, then $E$ is called a **normal extension** of $F$.

Normal extensions play a basic role in Galois theory.

### Algebraically closed fields

Most of the extension concepts above, in principle, need to be worked out inside a field even larger than the extension. For simple extensions we can use polynomial rings to build the extension without relying on a larger field, but there is no such tool in general. For the rational field $\mathbf Q$ and the real field $\mathbf R$, we can always assume algebraic extensions live inside the complex field $\mathbf C$. For finite fields there is no similar well-known field. In fact, every field has an algebraic closure, and all algebraic extensions of the field can be assumed to live inside it. This settles the problem completely.

???+ abstract "Algebraic closure"
    For a field $F$, if a field $\overline F$ is an algebraic extension of $F$ and every $f(x)\in F[x]$ splits over $\overline F$, then $\overline F$ is called an **algebraic closure** of $F$.

An algebraic closure is a normal extension of the field. It is built essentially by adjoining the roots of all possible polynomials to the field. And just like splitting fields, the algebraic closure of a field is unique up to isomorphism.

???+ note "Theorem"
    Every field $F$ has an algebraic closure.

??? note "Proof"
    The difficulty of the proof comes from set theory. Here we give a proof due to Artin.
    
    The first part of the proof starts from $F$ and builds an extension $K_1/F$ such that every polynomial over $F$ has at least one root in $K_1$. For the field $F$, consider the multivariate polynomial ring[^multi-poly-ring] $R=F[\cdots,x_f,\cdots]$, where the indeterminates $x_f$ are indexed by all monic polynomials over $F$. Let $I$ be the ideal generated by all $f(x_f)$. First, $I\neq R$, so a maximal ideal $M\supseteq I$ exists. Otherwise, if $1\in I$, there would be finitely many monic polynomials $f_i$ over $F$ and corresponding elements $g_i$ of $R$ such that $g_1f_1(x_{f_1})+\cdots+g_kf_k(x_{f_k})=1$. Let $F(\alpha_1,\cdots,\alpha_k)$ be the algebraic extension obtained by adjoining to $F$ a root $\alpha_i$ of each $f_i(x)$. In $F(\alpha_1,\cdots,\alpha_k)$, substitute $\alpha_i$ for each $x_{f_i}$ in the identity above, and substitute $0$ for every other indeterminate $x_f$ appearing in the $g_i$. This gives the equation $0=1$ in $F(\alpha_1,\cdots,\alpha_k)$, a contradiction. So $I\neq R$, and the maximal ideal $M$ is well defined. The quotient ring $R/M$ is then a field, written $K_1$, and every monic polynomial $f(x)$ over $F$ has the root $\overline{x_f}$ in $K_1$.
    
    The second part of the proof builds, by induction, an algebraically closed field $K$ containing $F$ (defined below). Repeating the construction above, from the field $K_i$ we can build a field $K_{i+1}$ in which every polynomial over $K_i$ has at least one root. Also, $K_i$ embeds naturally in $K_{i+1}$, so we can define their union $K=\bigcup_{i=1}^\infty K_i$. It is easy to check that this is also a field. The coefficients of any polynomial over $K$ must all lie in some $K_i$, so one of its roots must appear in $K_{i+1}\subseteq K$. This shows every polynomial over $K$ has at least one root in $K$, so $K$ is algebraically closed.
    
    Finally, let $\overline F$ be the set of all elements of $K$ that are algebraic over $F$. It is clearly a field, because for any $\alpha,\beta\in\overline F$ we have $\alpha\pm\beta,\alpha\beta,\alpha/\beta\in F(\alpha,\beta)\subseteq\overline F$. It is also an algebraic extension of $F$, because its elements are all algebraic over $F$. For a polynomial $f(x)$ over $F$, all its roots are algebraic over $F$, so they are in $\overline F$ too, and $f(x)$ must split into linear factors. This shows that $\overline F$ is an algebraic closure of $F$.

???+ example "Example"
    1.  The algebraic closure of the real field $\mathbf R$ is the complex field $\mathbf C$.
    2.  The algebraic closure of the rational field $\mathbf Q$ is the set of all algebraic numbers (the algebraic elements of the extension $\mathbf C/\mathbf Q$), written $\overline{\mathbf Q}$.

Every algebraic extension of an algebraic closure is trivial. Such fields are called algebraically closed fields.

???+ abstract "Algebraically closed field"
    If every non-constant polynomial $f(x)$ over a field $F$ has at least one root $\alpha\in F$, then $F$ is called an **algebraically closed field**.

In fact, it has the following equivalent definitions:

???+ note "Theorem"
    For a field $F$, the following are equivalent:
    
    1.  $F$ is algebraically closed;
    2.  Every polynomial $f(x)$ over $F$ splits;
    3.  The only irreducible polynomials over $F$ are those of degree one;
    4.  $F$ has no nontrivial algebraic extension;
    5.  $F$ has no nontrivial finite extension;
    6.  $F$ is the algebraic closure of some field.

??? note "Proof"
    The equivalence of the first five properties is clear from the definitions. For the sixth: an algebraically closed field is clearly its own algebraic closure, since it has no nontrivial algebraic extension. Conversely, we must show the algebraic closure of a field $F$ is algebraically closed. Let $\overline F$ be an algebraic closure of $F$ and $f(x)$ a polynomial over $\overline F$. Let $\alpha$ be a root of $f(x)$ in its splitting field, and let $S\subseteq\overline F$ be the set of nonzero coefficients of $f(x)$. Since $F(S)(\alpha)=F(S\cup\{\alpha\})$ is a finite extension, $\alpha$ must also be algebraic over $F$. So by the definition of algebraic closure, the minimal polynomial of $\alpha$ over $F$ splits over $\overline F$, and hence $\alpha\in\overline F$. This shows every polynomial over $\overline F$ has at least one root.

Finally, the [fundamental theorem of algebra](../poly/fundamental.md) [^fundamental-algebra] says that $\mathbf C$ is algebraically closed. Irreducible polynomials over the real field $\mathbf R$ have degree at most two, or equivalently, its algebraic extensions have degree at most two, precisely because the largest field reachable by algebraic extensions is $\mathbf C$.

### Separable extensions

The idea of a splitting field guarantees that for any polynomial over any field, there is an extension field containing all its roots, and the splitting field is exactly the smallest such extension. The properties of a polynomial are closely tied to those of its splitting field. But if we want to study a polynomial through its splitting field, the first problem is that the splitting field ignores the multiplicities of the roots. So, if possible, we should consider some kind of "simplest form" of the polynomial. This motivates calling a polynomial separable if it has no repeated roots even in the algebraic closure of the field.

???+ abstract "Separable polynomial"
    For a polynomial $f(x)$ over a field $F$, if $f(x)$ has no repeated roots in the algebraic closure $\overline F$ of $F$, that is, its factorization into linear factors has no repeated factor, then $f(x)$ is called **separable**.

Since we always extend to the algebraic closure of $F$ for this, whether a polynomial is separable does not actually depend on the choice of $F$. But since the coefficients lie in $F$, we would like a test that decides separability inside $F$ itself, without explicitly constructing an extension field.

Readers familiar with analysis know that whether a polynomial function has repeated roots can be checked with its derivative: a repeated root of a polynomial function is also a root of its derivative. Polynomials and polynomial functions are not the same concept, but this test can be carried over to polynomials by analogy. The derivative of a polynomial can be defined formally as follows:

???+ abstract "Formal derivative"
    For a polynomial over a field $F$
    
    $$
    f(x)=a_0+a_1x+a_2x^2+\cdots+a_{n-1}x^{n-1}+a_nx^n=\sum_{i=0}^na_ix^i
    $$
    
    , its **(formal) derivative**, written $Df(x)$, is defined as the polynomial
    
    $$
    Df(x)=a_1+2a_2x+\cdots+(n-1)a_{n-1}x^{n-2}+na_nx^{n-1}=\sum_{i=1}^nia_ix^{i-1}.
    $$

This definition works for polynomials over any field and does not rely on any topology. The derivative operator $D$ here just maps one polynomial to another. Also, by comparing coefficients one can check that the usual rules of differentiation, such as $D(f(x)g(x))=(Df(x))g(x)+f(x)(Dg(x))$, still hold for formal derivatives.

Furthermore, to check whether $f(x)$ and its derivative $Df(x)$ share a root in the splitting field, we do not need to build the splitting field explicitly; we can use their greatest common divisor instead. This is because a root of a polynomial always appears in its minimal polynomial, and a repeated root means the corresponding minimal-polynomial factor is repeated. So the test for repeated roots is:

???+ note "Theorem"
    For a polynomial $f(x)$ over a field $F$, if $f(x)$ has a repeated root $\alpha$, then its derivative $Df(x)$ also has the root $\alpha$. Moreover, $f(x)$ is separable if and only if $f(x)$ and $Df(x)$ are coprime, that is, $\gcd(f(x),Df(x))=1$.

??? note "Proof"
    First, since division with remainder is preserved in extension fields, the result of the Euclidean algorithm does not depend on the choice of extension field, so it is enough to study their common factors in the splitting field. Let $\alpha$ be a root of $f(x)$ of multiplicity $k>1$. Then in the splitting field $f(x)=(x-\alpha)^kg(x)$, so its derivative $Df(x)=k(x-\alpha)^{k-1}g(x)+(x-\alpha)^kDg(x)$ also has the root $\alpha$. Conversely, if both $f(x)$ and $Df(x)$ have the root $\alpha$, then for the factorization $f(x)=(x-\alpha)g(x)$ in the splitting field we have $Df(x)=(x-\alpha)Dg(x)+g(x)$, so $\alpha$ is also a root of $g(x)$, and therefore $\alpha$ is a repeated root of $f(x)$. This proves the first part of the theorem. Furthermore, $f(x)$ having a repeated root $\alpha$ is equivalent to $x-\alpha$ being a factor of $\gcd(f(x),Df(x))$. So $f(x)$ is not separable exactly when $\gcd(f(x),Df(x))$ has degree at least one.

A polynomial over a field can always be factored into a product of irreducible polynomials. Since distinct irreducible polynomials (up to associates) always have distinct roots, repeated roots are naturally linked to repeated polynomial factors. So if a polynomial's factorization has no repeated irreducible factor, can we conclude it is separable? In other words, is every irreducible polynomial separable? Unfortunately, in general the answer is no. The problem shows up in fields of finite characteristic.

For an irreducible polynomial $f(x)$ over a field $F$, the polynomial $\gcd(f(x),Df(x))$ is a factor of $f(x)$, so there are only two possibilities: $1$ or $f(x)$. In the first case, $f(x)$ is of course separable; the problem is the second case. But the definition of the derivative already ensures $Df(x)=0$ or $\deg Df(x)<\deg f(x)$, so $f(x)$ being a factor of $Df(x)$ can only mean $Df(x)=0$. This can happen in fields of finite characteristic.

For a field $F$ of characteristic $p$, if $Df(x)=0$, then all nonzero coefficients of the polynomial can only appear on terms whose degree is a multiple of $p$; that is, $f(x)$ can be written as

$$
f(x)=a_0+a_px^p+a_{2p}x^{2p}+\cdots+a_{(k-1)p}x^{(k-1)p}+a_{kp}x^{kp}.
$$

If a polynomial $f(x)$ over $F$ is both irreducible and not separable, it must have this form. But if every element of $F$ has a $p$-th root, that is, for each coefficient $a_{jp}$ there is $b_j\in F$ such that $a_{jp}$ can be written as $b_j^p$, then by the Frobenius endomorphism we always have

$$
\begin{aligned}
f(x)&=a_0+a_px^p+a_{2p}x^{2p}+\cdots+a_{(k-1)p}x^{(k-1)p}+a_{kp}x^{kp}\\
&=b_0^p+b_1^px^p+b_2^px^{2p}+\cdots+b_{k-1}^px^{(k-1)p}+b_k^px^{kp}\\
&=\left(b_0+b_1x+b_2x^2+\cdots+b_{k-1}x^{k-1}+b_kx^k\right)^p.
\end{aligned}
$$

So over such a field $F$ there is no irreducible polynomial of this form. Therefore, over such fields, every irreducible polynomial is separable. Such fields are called perfect fields.

???+ abstract "Perfect field"
    If every irreducible polynomial over a field $F$ is separable, then $F$ is called a **perfect field**.

For a perfect field, being separable is the same as having no square factor in the unique factorization.

???+ note "Theorem"
    Let $F$ be a perfect field. A polynomial over $F$ is separable if and only if it can be written as a product of distinct (up to associates) irreducible polynomials.

The discussion in this section is actually enough to give a method for removing repeated factors from a polynomial, which is a key step in polynomial factorization algorithms. But that is beyond the scope of this page; interested readers can consult the references at the end.

This discussion also characterizes perfect fields:

???+ note "Theorem"
    A field $F$ is perfect if and only if $F$ has characteristic zero, or $F$ has characteristic $p$ and every element $x\in F$ has a $p$-th root (that is, the Frobenius endomorphism is also an automorphism).

The rational field $\mathbf Q$ and the finite fields $\mathbf F_q$ discussed below are both perfect fields.

For fields that are not perfect, there really are irreducible polynomials that are not separable.

??? example "Example"
    Consider the polynomial $x^2-t$ over $\mathbf F_2(t)$, the field of rational functions over $\mathbf F_2$. Since $\mathbf F_2(t)$ is the field of fractions of the unique factorization domain $\mathbf F_2[t]$, and $t$ is a prime element of $\mathbf F_2[t]$, applying Eisenstein's criterion with the prime $t$ shows that $x^2-t$ is irreducible in $\mathbf F_2[t]$, and hence also in $\mathbf F_2(t)$. But its derivative is $0$, so $x^2-t$ is not separable. In fact, in the extension field $\mathbf F_2(t)(\sqrt t)$ it has the double root $\sqrt t$.

Finally, back to field extensions.

???+ abstract "Separable extension"
    For an algebraic extension $E/F$, if for every $\alpha\in E$ the minimal polynomial of $\alpha$ is separable, then $E$ is called a **separable extension** of $F$.

Every algebraic extension of a perfect field is separable. This can also serve as an equivalent definition of a perfect field.

An algebraic extension that is both normal and separable is called a Galois extension. In a Galois extension, no irreducible polynomial has repeated roots, and the number of roots always equals the degree of the polynomial, so permutations of the roots fully reflect the properties of the extension and of the polynomial. Such extensions are the foundation of Galois theory. Interested readers can consult the references at the end.

## Cyclotomic fields

As a simple example of field extensions, this section discusses cyclotomic fields. Another simple example is [quadratic fields](../number-theory/quadratic.md).

### Group of roots of unity

In the complex field $\mathbf C$, the roots of the polynomial $x^n-1$ are called the **$n$-th roots of unity**. Let $\zeta_n=\mathrm{e}^{2\pi\mathrm{i}/n}$. Then the set of all $n$-th roots of unity is $C_n=\{\zeta_n^k:k\in\mathbf Z\}$. Under multiplication, $C_n$ is a cyclic group of order $n$, which can be written $\langle\zeta_n\rangle$ and is called the group of $n$-th roots of unity. The generators of $C_n$, that is, the elements of order exactly $n$, are called **primitive $n$-th roots of unity**. The set of primitive $n$-th roots of unity $P_n=\{\zeta_n^k:k\in\mathbf Z,k\perp n\}$ has exactly $\varphi(n)$ elements, where $\varphi(n)$ is [Euler's totient function](../number-theory/euler-totient.md). Grouping the elements of $C_n$ by their order gives the decomposition:

$$
C_n=\bigcup_{d|n}P_d.
$$

Counting elements on both sides gives the identity $n=\sum_{d\mid n}\varphi(d)$.

### Cyclotomic fields

A cyclotomic field is the extension field obtained by adjoining roots of unity to the rational field.

???+ abstract "Cyclotomic field"
    The extension field $\mathbf Q(\zeta_n)$ obtained by adjoining the complex $n$-th root of unity $\zeta_n=\mathrm{e}^{2\pi\mathrm{i}/n}$ to the rational field $\mathbf Q$ is called the **$n$-th cyclotomic field**.

Since all $n$-th roots of unity form the cyclic group $\langle\zeta_n\rangle$ under multiplication, the cyclotomic field $\mathbf Q(\zeta_n)$ contains all of these $n$-th roots of unity. In fact, $\mathbf Q(\zeta_n)$ is exactly the splitting field of $x^n-1$ over $\mathbf Q$.

???+ note "Theorem"
    The cyclotomic field $\mathbf Q(\zeta_n)$ is the splitting field of the polynomial $x^n-1$ over the rational field $\mathbf Q$.

??? note "Proof"
    Let $F$ be the splitting field of $x^n-1$ over $\mathbf Q$. Since $\mathbf Q(\zeta_n)$ contains all complex roots of $x^n-1$, we have $F\subseteq\mathbf Q(\zeta_n)$. Conversely, since $\zeta_n\in F$, we must have $\mathbf Q(\zeta_n)=F$. This shows $F=\mathbf Q(\zeta_n)$.

This can serve as an equivalent definition of a cyclotomic field. In fact, adjoining any primitive $n$-th root of unity to $\mathbf Q$ gives $\mathbf Q(\zeta_n)$.

### Cyclotomic polynomials

The cyclotomic field $\mathbf Q(\zeta_n)$ is a simple algebraic extension of $\mathbf Q$. By the analysis above, such a field is always isomorphic to a quotient of a polynomial ring. To get this isomorphism, we need to find the minimal polynomial $f(x)$ of $\zeta_n$. Since $\zeta_n$ is a root of $x^n-1$, $f(x)$ must be a factor of $x^n-1$. So we need to study the factorization of $x^n-1$ in $\mathbf Q[x]$. By Gauss's lemma, it can be factored in $\mathbf Z[x]$ into a product of irreducible monic polynomials.

Since $\mathbf Q(\zeta_n)$ is a splitting field, $x^n-1$ factors as:

$$
x^n-1=\prod_{\zeta\in C_n}(x-\zeta)=\prod_{d\mid n}\prod_{\zeta\in P_d}(x-\zeta).
$$

Roots of unity of different orders have different algebraic properties, so they cannot be roots of the same irreducible polynomial. So to find the minimal polynomial of $\zeta_n$, it suffices to look at the factor

$$
\Phi_n(x)=\prod_{\zeta\in P_n}(x-\zeta)
$$

in the factorization above. The minimal polynomial of $\zeta_n$ must be a factor of $\Phi_n(x)$. Moreover, $\Phi_n(x)$ defined this way has the following property:

???+ note "Theorem"
    $\Phi_n(x)$ is a monic polynomial with integer coefficients, and it is irreducible in $\mathbf Z[x]$.

??? note "Proof"
    By definition, $\Phi_n(x)$ is clearly monic. First we show $\Phi_n(x)\in\mathbf Z[x]$. By Gauss's lemma, $x^n-1$ has the same factorization in $\mathbf Z[x]$ and $\mathbf Q[x]$, and every factor is a monic polynomial with integer coefficients. In this factorization, every factor $f(x)$ is irreducible over $\mathbf Q[x]$ and splits over $\mathbf Q(\zeta_n)$. All its roots are $n$-th roots of unity and must have the same order, so they all belong to a single $P_d$ rather than being spread over different $P_d$. This means every factor $f(x)$ is a factor of some $\Phi_d(x)$. So $\Phi_n(x)$ can be written as a product of monic polynomials with integer coefficients, and so it is itself a monic polynomial with integer coefficients.
    
    Next we show $\Phi_n(x)$ is irreducible in $\mathbf Z[x]$. Suppose it factors as $f(x)g(x)$ with $f(x)$ irreducible in $\mathbf Z[x]$. It suffices to show that $f(x)$ contains all primitive $n$-th roots of unity. That is, if $\zeta$ is a root of $f(x)$, we must show $\zeta^k$ is also a root of $f(x)$ for all $k\perp n$. Since $k$ can always be factored into primes, it suffices to show $\zeta^p$ is a root of $f(x)$ for every prime $p\perp n$. Suppose not, so $\zeta^p$ is a root of $g(x)$. Then $\zeta$ is a common root of the polynomials $f(x)$ and $g(x^p)$ in $\mathbf Z[x]$. Since $f(x)$ is the minimal polynomial of $\zeta$ over $\mathbf Q$, $f(x)$ must divide $g(x^p)$; that is, there is $h(x)\in\mathbf Z[x]$ with $g(x^p)=f(x)h(x)$. Reducing both sides modulo $p$ gives the equation $\overline{g}(x^p)=\overline{f}(x)\overline{h}(x)$ over $\mathbf F_p[x]$. By the Frobenius endomorphism, $\overline{g}(x)^p=\overline{f}(x)\overline{h}(x)$. Since $\mathbf F_p[x]$ is also a unique factorization domain, $\overline{g}(x)$ and $\overline{f}(x)$ must have a nontrivial common factor, so $x^n-\overline 1=\overline{f}(x)\overline{g}(x)$ is not separable over $\mathbf F_p$. But since $p\perp n$, its formal derivative $nx^{n-1}$ is coprime to it, which contradicts its not being separable. So $\zeta^p$ must still be a root of $f(x)$. Therefore $f(x)$ contains all primitive $n$-th roots of unity, and it is $\Phi_n(x)$.

This shows that it is the minimal polynomial of $\zeta_n$, also called the **$n$-th cyclotomic polynomial**. The defining formula above shows that it has $\varphi(n)$ complex roots, and these are exactly all the primitive $n$-th roots of unity; here $\varphi(n)$ is [Euler's totient function](../number-theory/euler-totient.md). It also shows that $\mathbf Q(\zeta_n)/\mathbf Q$ is an extension of degree $\varphi(n)$.

The ring of algebraic integers in the cyclotomic field $\mathbf Q(\zeta_n)$ is $\mathbf Z[\zeta_n]$. Also, when $\varphi(n)=2$, the cyclotomic field is a [quadratic extension](../number-theory/quadratic.md). Specifically, $\mathbf Q(\zeta_4)$ is the quadratic field $\mathbf Q(\sqrt{-1})$, and $\mathbf Q(\zeta_3)$ and $\mathbf Q(\zeta_6)$ are the same, both equal to the quadratic field $\mathbf Q(\sqrt{-3})$.

Using cyclotomic polynomials, $x^n-1$ has the unique factorization in $\mathbf Z[x]$

$$
x^n-1=\prod_{d\mid n}\Phi_d(x).
$$

So $(x^d-1)\mid(x^n-1)$ if and only if $d\mid n$. Moreover, applying [Möbius inversion](../number-theory/mobius.md) to this formula gives

$$
\Phi_n(x)=\prod_{d\mid n}(x^d-1)^{\mu(n/d)}.
$$

With this expression, all cyclotomic polynomials can be computed recursively. Here are the first few, to help the reader get familiar with them.

???+ example "Cyclotomic polynomials"
    The first $10$ cyclotomic polynomials are:
    
    $$
    \begin{aligned}
    \Phi_1(x) &= x-1,\\
    \Phi_2(x) &= x+1,\\
    \Phi_3(x) &= x^2+x+1,\\
    \Phi_4(x) &= x^2+1,\\
    \Phi_5(x) &= x^4+x^3+x^2+x+1,\\
    \Phi_6(x) &= x^2-x+1,\\
    \Phi_7(x) &= x^6+x^5+x^4+x^3+x^2+x+1,\\
    \Phi_8(x) &= x^4+1,\\
    \Phi_9(x) &= x^6+x^3+1,\\
    \Phi_{10}(x) &= x^4-x^3+x^2-x+1.
    \end{aligned}
    $$
    
    An interesting fact: although the coefficients of these cyclotomic polynomials all seem to be $0$ or $\pm1$, this is not true for general $n$. The first counterexample is $\Phi_{105}(x)$, and one can prove that as $n$ grows, the coefficients can become arbitrarily large.

Using the Möbius inversion formula above, we can derive the following properties that simplify computing $\Phi_n(x)$:

???+ note "Properties"
    For the cyclotomic polynomial $\Phi_n(x)$:
    
    1.  If a prime $p\mid n$, then $\Phi_{pn}(x)=\Phi_n(x^p)$;
    2.  If a prime $p\perp n$, then $\Phi_{pn}(x)=\dfrac{\Phi_n(x^p)}{\Phi_n(x)}$;
    3.  In particular, if $n>1$ is odd, then $\Phi_{2n}(x)=\Phi_n(-x)$;
    4.  For a prime $p$, $\Phi_{p}(x)=1+x+\cdots+x^{p-1}$;
    5.  In particular, $\Phi_{2^k}(x)=x^{2^{k-1}}+1$.

These properties show that the key to computing cyclotomic polynomials is the case where the index is a square-free odd number. In that case, we can use property 2 to add prime factors one at a time; adding each prime factor needs just one polynomial division.

Cyclotomic polynomials have many other properties.

???+ note "Theorem"
    Let $\Phi_n(x)$ be the $n$-th cyclotomic polynomial with $n>1$; its degree is $\varphi(n)$. Then:
    
    1.  $\Phi_n(x)$ is a palindromic polynomial: its coefficient of degree $j$ equals its coefficient of degree $\varphi(n)-j$, that is, $\Phi_n(x)=x^{\varphi(n)}\Phi_n(1/x)$;
    2.  Its coefficient of degree $\varphi(n)-1$ equals the Möbius function value $-\mu(n)$;
    3.  If $n$ is a prime power $p^k$, then $\Phi_n(1)=p$; otherwise $\Phi_n(1)=1$;
    4.  Let $b>1$ and let $p$ be a prime factor of $\Phi_n(b)$. Then either $p\mid n$, or $n$ is the order of $b$ in the multiplicative group $(\mathbf Z/p\mathbf Z)^\times$, and the two cases cannot both happen.

??? note "Proof"
    The first three properties follow from Möbius inversion. For 1, look directly at the Möbius inversion form $\Phi_n(x)=\prod_{d\mid n}(x^d-1)^{\mu(n/d)}$. For 2, let $f(n)$ be the coefficient of degree $\varphi(n)-1$ in $\Phi_n(x)$; comparing the coefficients of degree $n-1$ on both sides of $x^n-1=\prod_{d\mid n}\Phi_d(x)$ gives $\sum_{d\mid n}f(d)=-[n=1]$, then apply Möbius inversion. For 3, divide both sides of $x^n-1=\prod_{d\mid n}\Phi_d(x)$ by $\Phi_1(x)=x-1$ and substitute $x=1$, which gives $n=\prod_{d\mid n,d\neq 1}\Phi_d(1)$, then apply Möbius inversion.
    
    Now we prove the fourth property. First, if $n$ is the order of $b$ in $(\mathbf Z/p\mathbf Z)^\times$, then $n$ is the smallest positive integer with $p\mid b^n-1$, so $p\mid\Phi_n(b)$. Conversely, if $p\mid\Phi_n(b)$, then $b^n\equiv 1\pmod p$. If $n$ is not the order of $b$ in $(\mathbf Z/p\mathbf Z)^\times$, let that order be $k$; then $k\mid n$ and $p\mid\Phi_k(b)$. In that case $\Phi_k(x)$ and $\Phi_n(x)$ have the common root $b$ in $\mathbf F_p$, so $x^n-1$ has the repeated root $b$. This implies $p\mid n$; otherwise $x^n-1$ would be coprime to its derivative, hence separable over $\mathbf F_p$, and could not have a repeated root. So a prime factor $p$ of $\Phi_n(b)$ falls into one of two cases: $p\mid n$, or $n$ is the order of $b$ in $(\mathbf Z/p\mathbf Z)^\times$. The two cases are mutually exclusive, because the latter implies $n\mid p-1$.

Cyclotomic polynomials can also be used to solve some number theory and algebra problems. For example, the period length of a fraction written as a repeating decimal in some base is closely related to cyclotomic polynomials. For these specific applications, interested readers can consult the references at the end.

## Finite fields

A **finite field**, also called a **Galois field**, is a field with finitely many elements. The structure of a finite field is uniquely determined by its number of elements, and that number must be a prime power.

???+ note "Theorem"
    A field of size $q$ exists if and only if $q$ is a prime power $p^n$. Moreover, such a field is unique up to isomorphism and is written $\mathbf F_q$. The prime $p$ is the characteristic of $\mathbf F_q$, and the positive integer $n$ is the degree of the extension $\mathbf F_q/\mathbf F_p$. Finally, $\mathbf F_q$ is the splitting field of the polynomial $x^q-x$ over $\mathbf F_p$, and it consists of exactly the $q$ distinct roots of $x^q-x$.

??? note "Proof"
    Let $F$ be a finite field. Its characteristic must be finite; call it $p$. So $F$ has the prime subfield $\mathbf F_p$. Also, $F$ must be a finite extension of $\mathbf F_p$; call its degree $n$. As an $n$-dimensional vector space over $\mathbf F_p$, $F$ has $q=p^n$ elements. The nonzero elements of $F$ form the group $F^\times$ of order $q-1$, so $x^{q-1}=1$. Hence every element of $F=F^\times\cup\{0\}$ satisfies $x^q=x$; that is, they are $q$ distinct roots of $x^q-x$. So in $F$, the polynomial $x^q-x$ has the factor $\prod_{\alpha\in F}(x-\alpha)$. But this factor already has degree $q$ and leading coefficient $1$, so $x^q-x=\prod_{\alpha\in F}(x-\alpha)$. This shows $x^q-x$ splits in $F$. Any field over which $x^q-x$ splits must have at least $q$ elements, since $x^q-x$ has $q$ distinct roots. So $F$ is the smallest field over which $x^q-x$ splits, that is, the splitting field of $x^q-x$. In short, a finite field of size $q$ must be the splitting field of $x^q-x$ over its prime subfield. Since splitting fields are unique up to isomorphism, the field of size $q$ is unique as well.
    
    Conversely, given a prime $p$ and a power $q=p^n$, to show that a field of every prime-power order $q$ exists, we must show that the splitting field of $x^q-x$ over $\mathbf F_p$ has exactly $q$ elements. The splitting field of $x^q-x$ over $\mathbf F_p$ always exists, so let $F$ be the set of all roots of $x^q-x$ in it. We now show $F$ is a field, so that it is the splitting field of $x^q-x$ itself. Iterating the Frobenius endomorphism $n$ times shows that $x\mapsto x^q$ is also an endomorphism, so for any $\alpha,\beta\in F$ we have $(\alpha\pm\beta)^q=\alpha^q\pm\beta^q$, $(\alpha\beta)^q=\alpha^q\beta^q$ and $(\alpha^{-1})^q=(\alpha^q)^{-1}$. So $F$ is closed under addition, subtraction, multiplication and division, and it is a field. This shows $F$ is the splitting field of $x^q-x$ over $\mathbf F_p$.

???+ note "Corollary"
    In a finite field $\mathbf F_q$ ($q>2$), the sum of all nonzero elements is $0$ and their product is $-1$.

??? note "Proof"
    The nonzero elements of a finite field are exactly the $q-1$ roots of $x^{q-1}-1$. Apply Vieta's formulas.

In the prime field $\mathbf F_p$, the statement about the product is exactly (part of) [Wilson's theorem](../number-theory/factorial.md#wilson-定理) from number theory.

### Multiplicative structure

The multiplicative group $\mathbf F_q^\times=\mathbf F_q\setminus\{0\}$ of a finite field is always cyclic.

???+ note "Theorem"
    Every finite subgroup of the multiplicative group of a field $F$ is cyclic.

??? note "Proof"
    Let $G$ be a subgroup of the multiplicative group of $F$ with $|G|=n$. Then $G$ is a finite abelian group. By the fundamental theorem of finite abelian groups, $G$ has an invariant factor decomposition $C_{n_1}\times\cdots\times C_{n_s}$ with $n_1\mid\cdots\mid n_s$. So every element $x$ of $G$ satisfies $x^{n_s}=1$. That is, the elements of $G$ are all roots of the polynomial $x^{n_s}-1$ over $F$. But $x^{n_s}-1$ has at most $n_s$ distinct roots, so $n\le n_s$. Also $n_s\le n$, so in fact $n_s=n$. This shows $G\cong C_{n_s}$, so $G$ is cyclic.

???+ note "Corollary"
    The multiplicative group of the finite field $\mathbf F_q$ satisfies $\mathbf F_q^\times\cong C_{q-1}$.

The cyclic group $\mathbf F_q^\times$ has $\varphi(q-1)$ generators, called the primitive elements of the finite field; here $\varphi(n)$ is [Euler's totient function](../number-theory/euler-totient.md).

???+ abstract "Primitive element"
    A generator of the multiplicative group of a finite field $\mathbf F_q$ is called a **primitive element** of $\mathbf F_q$.

??? warning "A primitive element of a simple extension is not the same as a primitive element of a finite field"
    Although they share the same name, a primitive element of a simple extension and a primitive element of a finite field are different things. A primitive element of a simple extension generates that simple extension, while a primitive element of a finite field generates its multiplicative group (as a cyclic group). A primitive element of a finite field viewed as a simple extension of its prime subfield need not be a primitive element of the finite field itself. For example, in $\mathbf F_{25}\cong\mathbf F_5[x]/(x^2+x+1)$, $\overline x$ is a primitive element of the field extension, but not a primitive element of the field $\mathbf F_{25}$, because its order is $3$.

??? warning "A primitive element of $\mathbf F_{q}$ is also not the same as a primitive root modulo $q$"
    For a finite field $\mathbf F_{q}$ of odd characteristic, a [primitive root](./ring-theory.md#应用整数同余类的乘法群) modulo $q$ always exists. But it should not be confused with a primitive element of the finite field $\mathbf F_{q}$. Both are generators of the corresponding multiplicative structure as a cyclic group, but $(\mathbf Z/q\mathbf Z)^\times$ and $\mathbf F_q$ are different when $q$ itself is not prime. For example, the order of the former is $\varphi(q)$ while the order of the latter is $q-1$, so the two multiplicative groups do not even have the same size.

Let $\alpha$ be a primitive element of the finite field $\mathbf F_q$. Then for every nonzero $x\in\mathbf F_q^\times$ there is a unique natural number $k<q-1$ with $x=\alpha^k$; this $k$ is called the **discrete logarithm** of $x$ in $\mathbf F_q$ to the base $\alpha$. As in $\mathbf F_p$, [algorithms for discrete logarithms](../number-theory/discrete-logarithm.md) all have fairly high complexity.

Through multiplication, a primitive element already generates all nonzero elements of the field. This shows that a finite field, as an extension of any of its subfields, is always a simple extension.

???+ note "Theorem"
    For a finite field $\mathbf F_q$ and a subfield $F$ of $\mathbf F_q$, $\mathbf F_q$ is a simple algebraic extension of $F$. Moreover, if $\alpha$ is a primitive element of $\mathbf F_q$, then $\mathbf F_q=F(\alpha)$.

The minimal polynomial of a primitive element is an irreducible polynomial over a subfield of the finite field.

### Inclusion relations

A subfield of a finite field is also a finite field. Inclusion between finite fields is also completely determined by their orders.

???+ note "Theorem"
    Let $\mathbf F_q$ and $\mathbf F_r$ be finite fields. Then $\mathbf F_r$ is a subfield of $\mathbf F_q$ if and only if there is $k$ with $q=r^k$. In other words, $\mathbf F_{p^d}$ is a subfield of $\mathbf F_{p^n}$ if and only if $d\mid n$.

??? note "Proof"
    If $\mathbf F_r$ is a subfield of $\mathbf F_q$, they must have the same characteristic $p$. The extensions $\mathbf F_q/\mathbf F_r$, $\mathbf F_r/\mathbf F_p$ and $\mathbf F_q/\mathbf F_p$ are all simple algebraic extensions. Call their degrees $k,d,n$; then $n=kd$. Also $r=p^d$ and $q=p^n$, so $q=p^n=p^{kd}=(p^d)^k=r^k$.
    
    Conversely, we must show that $\mathbf F_{p^d}$ is a subfield of $\mathbf F_{p^n}$ for every $d\mid n$. Let $r=p^d$ and $q=p^n$. Let $F$ be the set of all roots of $x^r-x=0$ in the finite field $\mathbf F_q$. Using the Frobenius endomorphism one can show that $F$ is a field; the key is to show there are exactly $r$ such roots, which gives $F\cong\mathbf F_r$. Since $d\mid n$, we have $(p^d-1)\mid(p^n-1)$, so $(x^{p^d-1}-1)\mid(x^{p^n-1}-1)$, that is, $(x^r-x)\mid (x^q-x)$. So $x^r-x$ splits over $\mathbf F_q$ and has $r$ distinct roots in $\mathbf F_q$. This shows $F\cong\mathbf F_r$ is a subfield of $\mathbf F_q$.

This theorem shows that inclusion between finite fields $\mathbf F_{p^n}$ corresponds to divisibility between the exponents $n$ in their orders $p^n$. The lattice formed by all finite fields $\mathbf F_{p^n}$ of characteristic $p$ is therefore isomorphic to the lattice of integers $n$ under divisibility. Of course, for operations such as intersections of the fields $\mathbf F_{p^n}$ to make sense, all fields of characteristic $p$ must be embedded in the algebraic closure of $\mathbf F_p$.

???+ note "Theorem"
    Let $F$ be the algebraic closure of $\mathbf F_p$. The set of roots of $x^{p^n}-x$ in $F$ forms the finite field $\mathbf F_{p^n}$. Then:
    
    1.  $F=\bigcup_{n=1}^\infty\mathbf F_{p^n}$; that is, the algebraic closure of $\mathbf F_p$ is the union of all finite fields of characteristic $p$;
    2.  The lattice formed by all finite fields $\mathbf F_{p^n}$ of characteristic $p$ under inclusion is isomorphic to the lattice of integers $n$ under divisibility. In particular, the intersection of $\mathbf F_{p^n}$ and $\mathbf F_{p^m}$ is $\mathbf F_{p^n}\cap\mathbf F_{p^m}=\mathbf F_{p^{\gcd(n,m)}}$, and the smallest field containing both $\mathbf F_{p^n}$ and $\mathbf F_{p^m}$ is $\mathbf F_{p^n}\mathbf F_{p^m}=\mathbf F_{p^{\operatorname{lcm}(n,m)}}$.

??? note "Proof"
    The key is to prove the first part, that $\bigcup_{n=1}^\infty\mathbf F_{p^n}$ is the algebraic closure of $\mathbf F_p$. The second part is a simple corollary of the earlier theorem about subfields of finite fields.
    
    Note that for any $\alpha\in\bigcup_{n=1}^\infty\mathbf F_{p^n}$, there is some $n\in\mathbf N_+$ with $\alpha\in\mathbf F_{p^n}$, so $\alpha$ is algebraic over $\mathbf F_p$. Hence $\bigcup_{n=1}^\infty\mathbf F_{p^n}$ is an algebraic extension of $\mathbf F_p$. Any polynomial $f(x)$ of degree $m$ over $\mathbf F_p$ has at most $m$ distinct roots $\{\alpha_i\}_{i=1}^m$ in the algebraic closure $F$. If the minimal polynomial of the root $\alpha_i$ has degree $n_i$, then $\alpha_i$ lies in the field $\mathbf F_{p^{n_i}}$. So all roots of $f(x)$ lie in $\bigcup_{n=1}^\infty\mathbf F_{p^n}$; that is, $f(x)$ splits over $\bigcup_{n=1}^\infty\mathbf F_{p^n}$. By the definition of algebraic closure, $\bigcup_{n=1}^\infty\mathbf F_{p^n}$ is the algebraic closure of $\mathbf F_p$.

### Automorphism group

Every subfield of a finite field $\mathbf F_q$ is the set of roots of a polynomial of the form $x^r-x$. In other words, each one is the set of fixed points of some map $x\mapsto x^r$. This reveals a deep correspondence between the subfields of a finite field and the subgroups of its automorphism group.

Every field of characteristic $p$ has the Frobenius endomorphism $\sigma_p:x\mapsto x^p$. For a finite field $\mathbf F_q$ this is also an automorphism, which shows that every finite field $\mathbf F_q$ is perfect. The automorphism group of $\mathbf F_q$ is the cyclic group $\langle \sigma_p\rangle$ of order $n$, and one generator is the Frobenius endomorphism $\sigma_p$.

???+ note "Theorem"
    The automorphism group $\operatorname{Aut}(\mathbf F_q)=\langle\sigma_p\rangle$ of a finite field $\mathbf F_q$ is a cyclic group of order $n$, and its generator $\sigma_p$ is the Frobenius endomorphism $x\mapsto x^p$.

??? note "Proof"
    First, the Frobenius endomorphism $\sigma_p$ is an automorphism of the finite field $\mathbf F_q$, because an injective map on a finite set is also surjective. So $\sigma_p\in\operatorname{Aut}(\mathbf F_q)$.
    
    Next, $\sigma_p$ has order $n$. This is because $\sigma_p^n(x)=x^{p^n}=x$ for all $x\in\mathbf F_q$, so $\sigma_p^n$ is the identity map; and for any $k<n$, $\sigma_p^k$ is not the identity, since otherwise every element of $\mathbf F_q$ would be a root of $x^{p^k}-x$, which is impossible.
    
    Finally, $\operatorname{Aut}(\mathbf F_q)$ has at most $n$ elements. Let $\alpha$ be a primitive element of $\mathbf F_q$. An automorphism $\sigma\in \operatorname{Aut}(\mathbf F_q)$ is uniquely determined by its value $\sigma(\alpha)$. But $\sigma$ must map $\alpha$ to one of its conjugates; otherwise $\alpha$ and $\sigma(\alpha)$ would no longer be roots of the same minimal polynomial. There are only $n$ such conjugates, which shows $\operatorname{Aut}(\mathbf F_q)$ has at most $n$ elements.
    
    So the $n$ elements of $\operatorname{Aut}(\mathbf F_q)$ are exactly $\langle\sigma_p\rangle$. This proves the theorem.

The subgroups of the automorphism group $\operatorname{Aut}(\mathbf F_q)$ correspond one-to-one with the subfields of the finite field $\mathbf F_q$.

???+ note "Theorem"
    Let $\mathbf F_q$ be a finite field, $\mathcal F$ the set of all its subfields, and $\mathcal G$ the set of all subgroups of its automorphism group $\operatorname{Aut}(\mathbf F_q)$. Then:
    
    1.  For $F\in\mathcal F$, let $\operatorname{Aut}(\mathbf F_q/F)$ be the set of automorphisms in $\operatorname{Aut}(\mathbf F_q)$ that fix $F$, that is, $\operatorname{Aut}(\mathbf F_q/F)=\{\sigma\in\operatorname{Aut}(\mathbf F_q):\forall x\in F(\sigma(x)=x)\}$. Then $\operatorname{Aut}(\mathbf F_q/F)\le\operatorname{Aut}(\mathbf F_q)$;
    2.  For $G\in\mathcal G$, let $F^G$ be the intersection of the fixed-point sets of all automorphisms in $G$, that is, $F^G=\{x\in\mathbf F_q:\forall\sigma\in G(\sigma(x)=x)\}$. Then $F^G$ is a subfield of $\mathbf F_q$;
    3.  The maps $F\rightarrow\operatorname{Aut}(\mathbf F_q/F)$ and $G\rightarrow F^G$ are inverse to each other and give a one-to-one correspondence between $\mathcal F$ and $\mathcal G$;
    4.  This correspondence turns extension relations between subfields into inclusion relations between subgroups (in reverse): for any $F_1\subseteq F_2$, we have $\operatorname{Aut}(\mathbf F_q/F_2)\le\operatorname{Aut}(\mathbf F_q/F_1)$.

This result is a special case of the fundamental theorem of Galois theory. It links field extensions with group theory, so that problems about field extensions can be solved with group-theoretic methods.

### Irreducible polynomials

Irreducible polynomials over a finite field $\mathbf F_q$ are easy to describe. Each irreducible polynomial of degree $n$ over $\mathbf F_q$ corresponds to an algebraic extension of degree $n$, and that extension is unique, so the roots of all irreducible polynomials of degree $n$ can be found in $\mathbf F_{q^n}$. This shows that an irreducible polynomial of degree $n$ over $\mathbf F_q$ must be a factor of $x^{q^n}-x$. To find all irreducible polynomials of degree $n$ over $\mathbf F_q$, we look at the factorization of $x^{q^n}-x$ over $\mathbf F_q$. This is very similar to the case of cyclotomic polynomials.

Algebraic elements over a finite field $\mathbf F_q$ can be classified by the degree of their minimal polynomial. Let $P_n$ be the set of algebraic elements whose minimal polynomial has degree exactly $n$. Then

$$
\mathbf F_{q^n} = \bigcup_{d\mid n}P_d.
$$

This corresponds to the factorization

$$
x^{q^n}-x = \prod_{d|n}\prod_{\zeta\in P_d}(x-\zeta).
$$

An irreducible polynomial of degree $n$ has $n$ roots, and their minimal polynomials all have degree $n$, so an irreducible polynomial of degree $n$ must be a factor of the polynomial

$$
\prod_{\zeta\in P_n}(x-\zeta) = \prod_{d\mid n}\left(x^{q^d}-x\right)^{\mu(n/d)}
$$

; this expression comes from applying [Möbius inversion](../number-theory/mobius.md) to the factorization above. Since the degree of this polynomial is

$$
\sum_{d\mid n}\mu(d)q^{n/d},
$$

the number of monic irreducible polynomials of degree $n$ over $\mathbf F_q$ is

$$
\frac1n\sum_{d\mid n}\mu(d)q^{n/d}
$$

. This is exactly the number of aperiodic necklaces of length $n$ that can be made from beads of $q$ colors, counted up to rotation ([proof](../combinatorics/polya.md#循环群)), so it is also called the necklace polynomial.

???+ note "Theorem"
    Over a finite field $\mathbf F_q$ there are irreducible polynomials of every degree.

Because irreducible polynomials over finite fields have such a simple structure, factoring polynomials over finite fields is quite easy. For example, to find all irreducible factors of degree $n$ of a given polynomial, just compute the greatest common divisor of the polynomial and $x^{q^n}-x$.[^ddf] Similarly, if a polynomial of degree $n$ is coprime to $x^{q^k}-x$ for every $k<n$, we can conclude that it is irreducible over $\mathbf F_q$.

As noted earlier, a root of an irreducible polynomial over a finite field need not be a primitive element of the corresponding extension field as a finite field. The minimal polynomial over the prime subfield $\mathbf F_p$ of a primitive element of $\mathbf F_q$ is also called a **primitive polynomial**[^prim-poly] over $\mathbf F_p$. Building the extension field with such a polynomial guarantees that $\overline x$ is a primitive element of the extension field. Primitive polynomials of degree $n$ over $\mathbf F_p$ can be found by factoring the cyclotomic polynomial $\Phi_{p^n-1}(x)$ over $\mathbf F_p$.

???+ note "Theorem"
    Let $p$ be a prime and $n$ a positive integer with $p\perp n$. Let $d$ be the order of $p$ in the multiplicative group $(\mathbf Z/n\mathbf Z)^\times$. Then the cyclotomic polynomial $\Phi_n(x)$ factors over $\mathbf F_p$ into a product of $\dfrac{\varphi(n)}{d}$ irreducible polynomials of degree $d$ over $\mathbf F_p$; moreover, these factors are primitive polynomials if and only if $n=p^d-1$. In particular, $\Phi_n(x)$ is irreducible over $\mathbf F_p$ if and only if $p$ is a primitive root modulo $n$.

??? note "Proof"
    Note that the roots of the $n$-th cyclotomic polynomial are all the primitive $n$-th roots of unity over $\mathbf F_p$, and the degree $d$ of the minimal polynomial of a primitive $n$-th root of unity equals the number of its conjugates (including itself), which equals the length of its orbit under the automorphism group $\langle\sigma_p\rangle$. From this, $d$ is the orbit length of the cyclic subgroup generated by the map $\zeta^i\mapsto\zeta^{ip}$ on $\{\zeta^i:i\perp n\}$, that is, the order of $p$ in $(\mathbf Z/n\mathbf Z)^\times$. If you prefer not to rely on Galois theory, you can also prove this by showing that $d$ is the smallest positive integer with $(x^n-1)\mid(x^{p^d-1}-1)$. The other statements are clear.

Although irreducible polynomials are important for implementing finite fields, there is no good deterministic method for finding an irreducible polynomial of degree $n$ over a finite field $\mathbf F_q$. In general, a randomized method can be used to generate one. Among all monic polynomials of degree $n$, the fraction that are irreducible is $\Theta(1/n)$, so we can generate a random monic polynomial of degree $n$ and test whether it is irreducible. This finds an irreducible polynomial after generating $\Theta(n)$ monic polynomials in expectation. Of course, an irreducible polynomial generated this way need not be primitive, and its coefficients need not be simple. In practice, if the size of the finite field is known in advance, one can often look up[^list-prim-poly] a primitive polynomial with simple coefficients in a table, which makes later computation easier.

### Reference implementation

This section gives a naive implementation of finite fields, for reference only. The code includes a method for randomly generating irreducible polynomials.

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/finite-field/finite-field_1.cpp"
    ```

The finite fields used most in cryptography are those of characteristic $2$. For such finite fields, field elements can be stored as 0/1 strings, and field operations can be implemented with bitwise operations.

## Applications

This section lists some applications of field extensions in competitive programming. The main situation is this: when evaluating an arithmetic expression over a field, we introduce in the middle of the computation some elements that do not exist in the original field, which makes a direct computation possible. Readers should already be familiar with using complex numbers to solve real-number problems, which is an example of extending the real field. What may be less familiar is extending finite fields. So here we mainly discuss extensions of finite fields, especially of the prime field $\mathbf F_p$.

In some cases a field extension lowers the complexity of the computation, so it is necessary, as with the [Fast Fourier Transform](../poly/fft.md) over the reals. In other cases a field extension is just one of many ways to solve the problem, and there is usually a method of similar complexity that avoids it, as with computing the Fibonacci sequence, discussed next. While learning these applications, readers should compare the strengths and weaknesses of different methods, so they can pick a suitable one when solving problems.

### Fibonacci sequence

Common methods for computing the [Fibonacci sequence](../combinatorics/fibonacci.md) are the $O(n)$ linear recurrence and $O(\log n)$ fast matrix exponentiation. In fact, it can also be computed with a field extension, again in $O(\log n)$ time. The Fibonacci sequence has the closed form:

$$
f(n) = \frac{1}{\sqrt{5}}\left(\left(\frac{1+\sqrt{5}}{2}\right)^n-\left(\frac{1-\sqrt{5}}{2}\right)^n\right).
$$

Now we want the value of $f(n)$ modulo a prime $p\neq 5$.[^fib-p5] To turn this into a computation in the finite field $\mathbf F_p$, the first question is what $\sqrt 5$ means in $\mathbf F_p$. Algebraically, it is a square root of the element $5$. So if $5$ has a square root in $\mathbf F_p$, that is, if $5$ is a quadratic residue modulo $p$, we can compute that square root directly and plug it in. Otherwise, we need to compute in the extension field $\mathbf F_p(\sqrt 5)\cong\mathbf F_p[x]/(x^2-5)$.

Of course, when computing in an extension field, we do not have to adjoin $\sqrt 5$ specifically. For example, for the Fibonacci sequence we can also let $\phi$ be a root of $x^2-x-1$, and then $f(n)$ can be written as

$$
f(n)=\frac{\phi^n-(-\phi)^{-n}}{2\phi-1}=\frac{\phi^n-(1-\phi)^n}{2\phi-1}.
$$

If $5$ is not a quadratic residue modulo $p$, the polynomial $x^2-x-1$ is irreducible. Then we can compute in the extension field $\mathbf F_p(\phi)\cong\mathbf F_p[x]/(x^2-x-1)$ and get the same result as before.

This method for the Fibonacci sequence can of course be generalized to other cases. But one thing needs care: whether a polynomial is irreducible over a finite field does not match whether it is irreducible over the rationals. For example, $x^4-10x^2+1$ is irreducible over $\mathbf Q$, with splitting field $\mathbf Q(\sqrt 2+\sqrt 3)=\mathbf Q(\sqrt 2,\sqrt 3)$. But over $\mathbf F_p$, if neither $2$ nor $3$ is a quadratic residue modulo $p$, it is a product of two irreducible polynomials; that is, the square root $\sqrt{3}$ already exists in the extension field $\mathbf F_p(\sqrt 2)$, and no further extension is needed.

### Generalizing to "extensions" of rings

As the previous section shows, field extensions come with all kinds of restrictions. For the Fibonacci sequence, extension fields alone only handle the case where the modulus $p$ is prime and $5$ is not a quadratic residue modulo $p$. But note that the discussion in the [Algebraic extensions](#algebraic-extensions) section shows that if we do not need division in the extended structure, we can extend rings instead.[^ring-extension] This section uses computing the Fibonacci sequence modulo an arbitrary $m$ as an example to briefly discuss this method. It can also be tried, when needed, in other common situations that do not involve much division, such as computing determinants or the Fast Fourier Transform.

Let $m$ be any positive integer and $f(n)$ the $n$-th Fibonacci number. The problem is to compute $f(n)\bmod m$. In principle we need to compute in $\mathbf Z/m\mathbf Z$. But as the previous section showed, under different moduli the polynomial $x^2-x-1$ may or may not be reducible and may or may not have repeated roots, so the closed form of the Fibonacci sequence can look very different. Moreover, if $\mathbf Z/m\mathbf Z$ is not itself a field, elements of the extension often have no valid inverse (for example, modulo $5$, the denominator $\sqrt 5$ is simply zero). Despite all these problems, it actually suffices to compute, with coefficients taken modulo $m$, the constant term of the remainder

$$
(1-x)^n-x^n\mod{x^2-x-1}
$$

. Comparing with the closed form above, why this works is clear: it looks like computing, in the "extension" $(\mathbf Z/m\mathbf Z)[x]/(x^2-x-1)$, the value of

$$
f(n)=\frac{(1-\phi)^n-\phi^n}{1-2\phi}
$$

where $\phi$ is a root of $x^2-x-1$.

Although less obvious, this method is also valid. Note that the closed form holds in the extension of the rationals $\mathbf Q(\phi)\cong\mathbf Q[x]/(x^2-x-1)$. This means that in $\mathbf Q[x]$,

$$
(1-x)^n-x^n \equiv f(n)(1-2x) \pmod{x^2-x-1}
$$

holds. This involves only polynomials with integer coefficients, so it also holds in $\mathbf Z[x]$. Write it as a division with remainder and reduce the coefficients on both sides modulo $m$; this gives an identity in $(\mathbf Z/m\mathbf Z)[x]$. The conclusion holds for every $m$.

In general, if an expression can be computed in an extension of the rational field $\mathbf Q$, then clearing denominators gives a result in $\mathbf Z[x]$, and reducing modulo $m$ gives a result in $(\mathbf Z/m\mathbf Z)[x]$. The key to making this idea work is that clearing denominators must not cause "irreversible" damage. For example, when computing the Fibonacci sequence, if we used the coefficient of the linear term instead of the constant term, the coefficient has a factor $2$, and $2$ has no inverse when $m$ is even, so $f(n)$ cannot be recovered. As another example, again for the Fibonacci sequence, if we used the closed form with the $(-\phi)^{-n}$ term, clearing denominators would bring in factors that are hard to handle, so no conclusion could be drawn from the reduced result. So choosing the right computation is the key to applying this trick.

### Cipolla's algorithm

This is a typical example of computing in an extension of a finite field. Given a quadratic residue $a$ modulo $p\neq 2$, we want to find its square root, that is, an $x$ with $x^2\equiv a\pmod p$. Although this is a problem in $\mathbf F_p$, [Cipolla's algorithm](../number-theory/quad-residue.md#cipolla-算法) computes in the finite field $\mathbf F_{p^2}$. This section explains the algorithm in the language of field theory. For a proof using elementary number theory, see the given link.

Specifically, Cipolla's algorithm first picks $r$ such that $r^2-a$ is a quadratic non-residue modulo $p$, which means $x^2-(r^2-a)$ is an irreducible polynomial. So, letting $u=r^2-a$, we can consider the extension field $\mathbf F_p(\sqrt u)$. The Frobenius endomorphism can only map an element to one of its conjugates, and in a quadratic extension that conjugate is unique, so $(r-\sqrt u)^p=r+\sqrt u$. Hence $(r-\sqrt u)^{p+1}=(r+\sqrt u)(r-\sqrt u)=r^2-u=a$. So to find the square root, we just compute $(r-\sqrt u)^{(p+1)/2}$. This value must lie in $\mathbf F_p$, because the splitting field of $x^2-a$ is $\mathbf F_p$ itself.

## Exercises

Finally, here are some problems that directly apply the content of this page, to deepen understanding. Note, however, that much of this content is not commonly tested in competitive programming.

-   Cyclotomic polynomials:
    -   [Luogu P1520 Factorization](https://www.luogu.com.cn/problem/P1520)
    -   [Gym102114C Call It What You Want](https://codeforces.com/gym/102114/problem/C)
-   Finite fields:
    -   [Luogu P3923 A College Math Problem](https://www.luogu.com.cn/problem/P3923)
    -   [\[COTS 2021\] Dish (Jelo)](https://www.luogu.com.cn/problem/P11192)
    -   [CF1310F. Bad Cryptography](https://codeforces.com/problemset/problem/1310/F)
    -   [LOJ 178. Polynomial Root Finding](https://loj.ac/p/178)
-   Field extensions:
    -   [\[Oleksandr Kulkov Contest 2\] Problem A. Square Root Partitioning](https://codeforces.com/gym/102354/problem/A)
    -   [CF1103E. Radix Sum](https://codeforces.com/problemset/problem/1103/E)

## References and notes

-   Dummit, D.S. and Foote, R.M. (2004) Abstract Algebra. 3rd Edition, John Wiley & Sons, Inc.
-   [Milne, J.S. Fields and Galois Theory.](https://www.jmilne.org/math/CourseNotes/FT.pdf)
-   [Factorization of polynomials - Wikipedia](https://en.wikipedia.org/wiki/Factorization_of_polynomials)
-   [Factorization of polynomials over finite fields - Wikipedia](https://en.wikipedia.org/wiki/Factorization_of_polynomials_over_finite_fields)
-   [Cyclotomic Polynomial - Wikipedia](https://en.wikipedia.org/wiki/Cyclotomic_polynomial)
-   [Brett Porter's Notes on Cyclotomic Polynomials](https://www.whitman.edu/documents/academics/majors/mathematics/2015/Final%20Project%20-%20Porter%2C%20Brett.pdf)
-   [Jordan Bell's Notes on Cyclotomic Polynomials](https://jordanbell.info/LaTeX/mathematics/cyclotomic/cyclotomic.pdf)
-   [Michel Waldschmidt. An introduction to the theory of finite fields](https://webusers.imj-prg.fr/~michel.waldschmidt/articles/pdf/FiniteFields.pdf)
-   [Finite Field Arithmetic - Wikipedia](https://en.wikipedia.org/wiki/Finite_field_arithmetic)

[^subfield-one]: This is because the unity $1_E$ of the field $E$ must satisfy the relation $x^2-x=0$ over $F$, and this equation has only two roots in $F$, namely $0_F$ and $1_F$. Since the definition of a field requires $1_E\neq 0_E$, we must have $1_E=1_F$ and $0_E=0_F$.

[^initial-object-ring]: In the language of category theory, $\mathbf Z$ is the [initial object](https://en.wikipedia.org/wiki/Initial_and_terminal_objects) of the category of rings with unity.

[^polynomial-universal]: Strictly speaking, this refers to the [universal property](https://en.wikipedia.org/wiki/Polynomial_ring#Polynomial_evaluation) of the polynomial ring $R[x]$.

[^multi-poly-ring]: This polynomial ring has infinitely many indeterminates. To define such a ring, first define monomials. Let $X$ be the set of indeterminates. A monomial on $X$ is a function $\alpha:X\rightarrow\mathbf N$ that is nonzero at only finitely many indeterminates, and can be written $x_{i_1}^{\alpha(i_1)}\cdots x_{i_k}^{\alpha(i_k)}$, where $i_1,\cdots,i_k$ are the indices of all indeterminates where $\alpha$ is nonzero. A polynomial is a linear combination of finitely many monomials. With suitably defined addition and multiplication, these form a ring. For finitely many indeterminates, one can prove that this definition agrees with the recursive definition in the [multivariate polynomial ring](./ring-theory.md#多元多项式环) section.

[^fundamental-algebra]: Despite its name, the fundamental theorem of algebra is not purely algebraic, because constructing the real numbers requires topology.

[^ddf]: This statement is not quite rigorous, because it also yields irreducible factors of degree $d\mid n$. But implementations usually split off factors starting from smaller degrees, so by the time the irreducible factors of degree $n$ are being split off, the smaller ones should already have been removed. So the statement is acceptable.

[^prim-poly]: Do not confuse this name with the primitive polynomials of polynomial theory (polynomials whose coefficients have greatest common divisor one).

[^list-prim-poly]: For example, the appendix of [Hansen, T., & Mullen, G. L. (1992). Primitive polynomials over finite fields. Mathematics of computation, 59(200), 639-643](https://www.ams.org/journals/mcom/1992-59-200/S0025-5718-1992-1134730-7/S0025-5718-1992-1134730-7.pdf) provides such a list.

[^fib-p5]: When $p=5$, the characteristic equation $x^2-x-1=0$ of the Fibonacci sequence has the double root $x=3$, so in $\mathbf F_5$ the closed form of the Fibonacci sequence is $f(n)=n3^{n-1}$.

[^ring-extension]: "Extension of a ring" usually has two meanings: one is a [generalization of group extensions](https://en.wikipedia.org/wiki/Algebra_extension), and the other is a [generalization of field extensions](https://en.wikipedia.org/wiki/Subring#Ring_extensions). This page uses the second meaning. More specifically, the extensions in this section are all [integral extensions](https://en.wikipedia.org/wiki/Integral_element#Integral_extensions) of commutative rings with unity, which generalize algebraic extensions of fields to commutative rings with unity.
