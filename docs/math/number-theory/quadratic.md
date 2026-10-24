This page gives a short introduction to the concepts around quadratic fields. Two important examples are the Gaussian integers and the Eisenstein integers, which can be used to solve some number theory problems.

## Basic concepts

This section first introduces a series of basic concepts. Quadratic fields and rings of quadratic integers are special cases of the more general algebraic extension fields and rings of algebraic integers, so almost every definition and result in this section extends naturally to the general case. Here we only discuss the special case of quadratic fields and avoid bringing in too much algebraic number theory.

### Quadratic fields

The elements of a quadratic field are all quadratic algebraic numbers.

A **quadratic algebraic number** is a complex number that is a root of a quadratic equation in one variable with integer coefficients. By the quadratic formula, every quadratic algebraic number can be written in the form

$$
a+b\sqrt{d}
$$

where $a$ and $b$ are rational numbers and $d$ is a square-free integer. Every number of this form is also a quadratic algebraic number. Quadratic algebraic numbers split into rational numbers and **quadratic irrational numbers**. Clearly, a quadratic irrational number can be written in this form in only one way.

For any square-free integer $d\neq 0,1$, one can check that the set $\mathbf Q(\sqrt{d})=\{a+b\sqrt{d}:a,b\in\mathbf Q\}$ is closed under addition, subtraction, multiplication and division. A set closed under the four arithmetic operations is called a [field](../algebra/basic.md#fields), so the set $\mathbf Q(\sqrt{d})$ is called a **quadratic field**. Every quadratic field contains all rational numbers, so each one is a [quadratic extension](../algebra/field-theory.md#field-extensions) of the field of rational numbers $\mathbf Q$. When $d>0$, all numbers in the quadratic field $\mathbf Q(\sqrt{d})$ are real, and $\mathbf Q(\sqrt{d})$ is called a real quadratic field. When $d<0$, no number in the quadratic field is real except the rational numbers, and $\mathbf Q(\sqrt{d})$ is called an imaginary quadratic field.

### Conjugates and norms

The **conjugate** of a quadratic irrational number $a+b\sqrt{d}$ is defined as $a-b\sqrt{d}$. Conjugate quadratic irrational numbers are the two distinct roots of the same quadratic equation with integer coefficients. In a real quadratic field, the conjugate of a quadratic irrational number is not the same as its conjugate as a complex number. In an imaginary quadratic field, the conjugate of a quadratic irrational number is exactly its complex conjugate. Finally, the conjugate of a rational number is defined to be itself. This defines conjugates for all quadratic algebraic numbers.

In any quadratic field, equations built from addition, subtraction, multiplication and division cannot tell conjugates apart. That is, if you replace every number in such an equation by its conjugate, i.e., flip the sign of every quadratic square root, the equation still holds.

Using conjugates, we can build several maps from quadratic algebraic numbers to rational numbers. They let us turn questions about quadratic algebraic numbers into questions about rational numbers. The simplest is the **trace** of a quadratic algebraic number $\alpha$, the sum of the number and its conjugate, written $\operatorname{tr}(\alpha)$. It is just $2$ times the rational part, so it does not carry much information.

The norm of a quadratic algebraic number is more useful. The product of a quadratic algebraic number and its conjugate is called its **norm**:

$$
N(a+b\sqrt{d})=a^2-db^2
$$

Clearly, in an imaginary quadratic field the norm agrees with the squared modulus of a complex number. In a real quadratic field, however, the two concepts differ.

The norm has nice properties. First, $d$ is square-free, so it cannot be a perfect square, and therefore only $0$ has norm $0$. Second, the norm preserves multiplication and division:

$$
N(a_1+b_1\sqrt{d})N(a_2+b_2\sqrt{d})=N((a_1+b_1\sqrt{d})(a_2+b_2\sqrt{d})),
$$

$$
\frac{N(a_1+b_1\sqrt{d})}{N(a_2+b_2\sqrt{d})}=N\left(\frac{a_1+b_1\sqrt{d}}{a_2+b_2\sqrt{d}}\right).
$$

Also, the reciprocal of a quadratic algebraic number is its conjugate divided by its norm:

$$
\dfrac{1}{a+b\sqrt{d}}=\frac{a-b\sqrt{d}}{N(a+b\sqrt{d})}.
$$

By Vieta's formulas, a quadratic algebraic number $\alpha$ is in fact a root of the equation

$$
x^2-\operatorname{tr}(\alpha)x+N(\alpha)=0
$$

The discriminant of this equation is also called the **discriminant** of the quadratic algebraic number, written $\operatorname{disc}(\alpha)$. Its value is $4db^2$.

???+ note "Matrix representation"
    Like complex numbers, quadratic algebraic numbers can be represented by matrices. Let $d\neq 0,1$ be a square-free integer and $a,b$ rational numbers. Then $a+b\sqrt{d}$ can be represented by the matrix
    
    $$
    \begin{pmatrix}a & b \\ db & a\end{pmatrix}.
    $$
    
    One can check that adding, subtracting, multiplying and dividing these matrices matches the corresponding operations on quadratic algebraic numbers. The trace and determinant of the matrix match the trace and norm of the quadratic algebraic number, and the discriminant of the matrix's characteristic polynomial is the discriminant of the quadratic algebraic number. The adjugate matrix corresponds to the conjugate of the quadratic algebraic number.

### Rings of quadratic integers

Quadratic integers are a special kind of quadratic algebraic number. A **quadratic integer** is a complex number that is a root of a quadratic equation in one variable with integer coefficients and leading coefficient one. The only difference from quadratic algebraic numbers is this restriction on the leading coefficient. By the quadratic formula, the two roots of $x^2+px+q=0$ are

$$
\frac{-p\pm\sqrt{p^2-4q}}{2}.
$$

If $p$ is even, i.e., $p=2k$, the two roots can be written as $-k\pm\sqrt{k^2-q}$. If $p$ is odd, i.e., $p=2k+1$, the two roots can be written as $-k-\dfrac{1\pm\sqrt{4(k^2+k-q)+1}}{2}$. From these two cases we conclude that every quadratic integer in $\mathbf Q(\sqrt{d})$ can be written in the form

$$
a+b\omega
$$

where $a$ and $b$ are integers and

$$
\omega=\begin{cases}
\dfrac{1+\sqrt{d}}{2}, & d\equiv 1\pmod 4,\\
\sqrt{d}, & d\equiv 2,3\pmod 4.
\end{cases}
$$

Conversely, every complex number of this form is a quadratic integer. Every irrational quadratic integer can be written in this form in only one way.

The set of all quadratic integers in the quadratic field $\mathbf Q(\sqrt{d})$ is written $\mathbf Z[\omega]$. This set is closed under addition, subtraction and multiplication, so it is also called a **ring of quadratic integers**. The rational numbers in a ring of quadratic integers are exactly the integers. If we take the set of all ratios of quadratic integers in $\mathbf Z[\omega]$, we get the corresponding quadratic field $\mathbf Q(\sqrt{d})$.

The trace, norm and discriminant of a quadratic integer are all integers. Among all quadratic irrational numbers in the ring $\mathbf Z[\omega]$, the discriminant with the smallest absolute value is also called the discriminant of the corresponding quadratic field $\mathbf Q(\sqrt{d})$. When $d\equiv 1\pmod 4$, the discriminant is $d$. When $d\equiv 2,3\pmod 4$, the discriminant is $4d$.

### Divisibility, associates and units

Just as for integers, we can build a theory of divisibility for quadratic integers. Of course, everything has to happen inside one ring of quadratic integers.

For quadratic integers $\alpha$ and $\beta$ in the ring $\mathbf Z[\omega]$, if there is a quadratic integer $\gamma$ in the same ring with $\beta=\alpha\gamma$, we say $\alpha$ divides $\beta$ and write $\alpha\mid\beta$. Divisibility is a [preorder](../order-theory.md#binary-relations) on the ring of quadratic integers. If both $\alpha\mid\beta$ and $\beta\mid\alpha$ hold, then $\alpha$ and $\beta$ can be treated as the same number in divisibility theory, and they are called **associates**. Being associates is an equivalence relation on the ring.

For integers, being associates just means being negatives of each other. Divisibility theory for integers usually only needs natural numbers, so we don't have to consider negative numbers. For quadratic integers, associates can be more complicated. If quadratic integers $\alpha$ and $\beta$ are associates, there are quadratic integers $\gamma$ and $\delta$ with $\beta=\alpha\gamma$ and $\alpha=\beta\delta$. So the ratio $\gamma$ of $\beta$ to $\alpha$ must be a special quadratic integer: there is a quadratic integer $\delta$ with $\gamma\delta=1$. Such a quadratic integer $\gamma$ is called a **unit**, or an invertible element. Two quadratic integers are associates if and only if their ratio is a unit. So to understand associates in a ring of quadratic integers, we need to understand the structure of its units.

The norm preserves multiplication, and the norm of a quadratic integer is always an integer, so the norm turns divisibility of quadratic integers into divisibility of integers. That is, if $\alpha\mid\beta$, then $N(\alpha)\mid N(\beta)$. Likewise, a quadratic integer $\alpha$ is a unit if and only if its norm is $N(\alpha)=\pm 1$. So to find all units in the ring $\mathbf Z[\omega]$, we only need to solve the Diophantine equation:

$$
N(a+b\omega)=\pm 1,
$$

where the norm is given by

$$
N(a+b\omega)=\begin{cases}
a^2+ab+\dfrac{1-d}{4}b^2, & d\equiv 1\pmod 4,\\
a^2-db^2, & d\equiv 2,3\pmod 4.
\end{cases}
$$

For imaginary rings of quadratic integers, i.e., when $d<0$, the norm is always a non-negative integer. It is easy to check that for every square-free negative $d\neq -1,-3$, the only solutions are $(a,b)=(\pm 1,0)$. That is, apart from $\mathbf Z[\sqrt{-1}]$ and $\mathbf Z[\frac{1+\sqrt{-3}}{2}]$, the only units of an imaginary ring of quadratic integers are $\pm 1$. Write $\mathrm{i}=\sqrt{-1}$. The ring $\mathbf Z[\mathrm{i}]$ is also called the ring of Gaussian integers, and its set of units is $\{\pm 1,\pm\mathrm{i}\}$. Write $\omega=\frac{1+\sqrt{-3}}{2}$. The ring $\mathbf Z[\omega]$ is also called the ring of Eisenstein integers, and its set of units is $\{\pm 1,\pm\omega,\pm\omega^2\}$.

For real rings of quadratic integers, i.e., when $d>0$, things are more complicated. The question turns into a study of the corresponding [Pell equation](./pell-equation.md). From the results on Pell equations, the set of all units can be written as $\{\pm u^k:k\in\mathbf Z\}$, where $u$ is called a **fundamental unit**. A fundamental unit can be found by solving the corresponding Pell equation. The fundamental unit is not unique: if $u$ is a fundamental unit, then its conjugate $\bar u$, as well as $-u$ and $-\bar u$, are also fundamental units.

The structure of units in rings of quadratic integers extends to general [rings of algebraic integers](../algebra/field-theory.md#algebraic-extensions). [Dirichlet's unit theorem](https://en.wikipedia.org/wiki/Dirichlet%27s_unit_theorem) in algebraic number theory says that the units of any ring of algebraic integers form a [finitely generated abelian group](../algebra/group-theory.md#finitely-generated-abelian-groups), and it also gives the rank of this group.

Ideas from integer divisibility theory, such as the greatest common divisor, division with remainder, Bézout's theorem and the unique factorization theorem, can be extended to some or all rings of quadratic integers. Whether such an extension works in a given ring reflects how close that ring is to the ring of integers. Unique factorization does not hold in every ring of quadratic integers, and among the rings where it does hold, only some allow division with remainder. For more on this, see the [rings of quadratic integers](../algebra/ring-theory.md#example-quadratic-integer-rings) section on the ring theory page or related books.

### Unique factorization

If unique factorization for integers extends to a ring of quadratic integers, it should look like this: every quadratic integer in the ring $\mathbf Z[\omega]$ can be written as a product of irreducible elements, and this factorization is unique up to associates and order. Here an [irreducible element](../algebra/ring-theory.md#divisibility) is a quadratic integer that cannot be split further into a product of non-units, much like a prime in the integer unique factorization theorem. As mentioned above, unique factorization does not hold in every ring of quadratic integers.

For example, in $\mathbf Z[\sqrt{-5}]$ we have $9=3\times 3=(2+\sqrt{-5})\times(2-\sqrt{-5})$, but $3$ and $2\pm\sqrt{-5}$ are all irreducible, so the factorization is not unique. To see that these three numbers are irreducible, look at their norms: each has norm $9$. If one of them could be factored into non-units, each factor would have norm $3$, but $\mathbf Z[\sqrt{-5}]$ has no quadratic integer with norm $3$.

The main reason unique factorization fails in general rings of quadratic integers is that factoring with quadratic integers alone does not go deep enough. For example, if we want to factor the product $abcd$ but the only building blocks available are $\{ab,cd,ac,bd\}$, the factorization will naturally not be unique. To get unique factorization, we have to go further and consider $\{a,b,c,d\}$. In a ring of quadratic integers, the finer structure beyond quadratic integers is the [ideals](../algebra/ring-theory.md#ideals) of the ring. Mapping a quadratic integer to its principal ideal embeds its class of associates into the set of ideals, so factoring numbers is just a special case of factoring ideals. If we factor ideals in a ring of quadratic integers, we can prove that every ideal factors uniquely into a product of prime ideals. This shows that every ring of quadratic integers is a [Dedekind domain](https://en.wikipedia.org/wiki/Dedekind_domain). More generally, every ring of algebraic integers is a Dedekind domain.

If unique factorization holds in a ring of quadratic integers, then its prime ideals correspond one-to-one to its irreducible elements (up to associates). So for such rings, factoring ideals into prime ideals is the same as factoring quadratic integers into irreducible elements. In this case, irreducible elements are also called [prime elements](../algebra/ring-theory.md#divisibility), which play the role of primes among the integers. The discussion below uses prime ideals and related concepts. Readers not familiar with them can replace them word for word with prime elements; the statements are still correct when unique factorization holds.

To fully understand unique factorization in a general ring of quadratic integers $\mathbf Z[\omega]$, we need to know what the prime ideals of $\mathbf Z[\omega]$ are. First, every prime ideal of $\mathbf Z[\omega]$ divides (the principal ideal of) its norm. Factor the norm into primes over the integers. By unique factorization, the prime ideal must divide (the principal ideal of) one of these prime factors. So every prime ideal of $\mathbf Z[\omega]$ comes from further factoring a prime of the integers. To list all prime ideals of $\mathbf Z[\omega]$, we only need the unique factorization of (the principal ideal of) each prime $p$ of $\mathbf Z$ in $\mathbf Z[\omega]$. The norm of (the principal ideal of) $p$ in $\mathbf Z[\omega]$ is $p^2$, and factoring it into prime ideals means each prime ideal's norm divides $p^2$, so it must be $p$ or $p^2$. This leaves only three possibilities:

1.  $p$ is **inert** in $\mathbf Z[\omega]$, i.e., $(p)$ is still a prime ideal in $\mathbf Z[\omega]$;
2.  $p$ **splits** in $\mathbf Z[\omega]$, i.e., $(p)$ can be written in $\mathbf Z[\omega]$ as the product of two distinct conjugate prime ideals;
3.  $p$ **ramifies** in $\mathbf Z[\omega]$, i.e., $(p)$ can be written in $\mathbf Z[\omega]$ as the square of a prime ideal.

One can further prove that to decide which of the three cases a prime $p$ falls into, we only need to compute the [Kronecker symbol](https://en.wikipedia.org/wiki/Kronecker_symbol) $\left(\dfrac{D}{p}\right)$, where $D$ is the discriminant of the quadratic field containing $\mathbf Z[\omega]$. The three cases correspond to the three values of the Kronecker symbol: $-1$, $+1$ and $0$. When $p$ is an odd prime, the Kronecker symbol is the [Legendre symbol](./quad-residue.md#legendre-symbol), and the three cases correspond to $D$ being a [quadratic non-residue](./quad-residue.md) modulo $p$, $D$ being a [quadratic residue](./quad-residue.md) modulo $p$, and $p$ dividing $D$. When $p=2$, the three cases correspond to $D\equiv \pm 3\pmod 8$, $D\equiv \pm 1\pmod 8$ and $2$ dividing $D$.

## Gaussian integers

In this section, $\mathrm{i}=\sqrt{-1}$ denotes the imaginary unit. The quadratic field $\mathbf Q(\mathrm{i})$ is also called the Gaussian field, and it is also the fourth [cyclotomic field](../algebra/field-theory.md#cyclotomic-fields). The corresponding ring of quadratic integers $\mathbf Z[\mathrm{i}]$ is called the ring of Gaussian integers, and its elements are called **Gaussian integers**. There are four Gaussian integer units, $\pm 1$ and $\pm\mathrm{i}$, so each nonzero Gaussian integer has four associates (including itself). In the complex plane, Gaussian integers are exactly the lattice points, and the norm of a Gaussian integer $N(a+b\mathrm{i})=a^2+b^2$ is the norm in the complex plane.

![](./images/gaussian-integer.svg)

Gaussian integers support division with remainder: for Gaussian integers $a$ and $b\neq 0$, there are always Gaussian integers $q$ and $r$ with $a=bq+r$ and $N(r)<N(b)$. To compute such a division, first compute $\dfrac{a}{b}$ in $\mathbf Q(\mathrm{i})$, then take the nearest lattice point in the complex plane as $q$, and then compute $r=a-bq$. The remainder obtained this way always satisfies $N(r)\le\dfrac{1}{2}N(b)$. With division with remainder, the Euclidean algorithm and Bézout's theorem carry over to Gaussian integers, and from there we get unique factorization.

### Gaussian primes

Using the results of the previous section, we can find the prime elements of the Gaussian integers (also called Gaussian primes). The discriminant of the ring of Gaussian integers is $-4$. The Kronecker symbol $\left(\dfrac{-4}{n}\right)$ is $0$ for even $n$, and for odd $n$ it equals $\left(\dfrac{-1}{n}\right)=(-1)^{(n-1)/2}$. So

$$
\left(\dfrac{-4}{n}\right) = \begin{cases}
+1,& n\equiv 1\pmod 4,\\
-1,& n\equiv 3\pmod 4,\\
0,& 2\mid n.
\end{cases}
$$

So there are three kinds of Gaussian primes:

1.  Integer primes of the form $4k+3$;
2.  The two conjugate Gaussian prime factors of an integer prime of the form $4k+1$;
3.  The factor $1+\mathrm{i}$ of the prime $2$, whose conjugate is its associate.

For example, in $\mathbf Z[\mathrm{i}]$ we have the factorization $60=2^2\times 3\times 5=-(1+\mathrm{i})^4\times 3\times(2+\mathrm{i})\times(2-\mathrm{i})$.

Asking whether a prime $p$ factors further in $\mathbf Z[\mathrm{i}]$ is really the same as asking whether $p$ can be written as a sum of two squares $a^2+b^2$. So from the result here, a prime $p$ is a sum of two squares if and only if $p=2$ or $p\equiv 1\pmod 4$. This is [Fermat's theorem on sums of two squares](https://en.wikipedia.org/wiki/Fermat%27s_theorem_on_sums_of_two_squares).

### Lattice points on a circle

In the complex plane, Gaussian integers are all the lattice points. The norm of a Gaussian integer is the squared Euclidean distance from the lattice point to the origin. So quadratic integers with the same norm correspond to the lattice points on a circle centered at the origin. That is, the number of lattice points on the circle $x^2+y^2=n$ is the number of Gaussian integers $x+y\mathrm{i}$ with norm $n$.

To solve $N(x+y\mathrm{i})=n$, factor the Gaussian integer $x+y\mathrm{i}$ into primes. The product of the norms of these prime factors equals $n$. So once we have the factorization of $n$, the prime factors of $n$ tell us which prime factors $x+y\mathrm{i}$ can have. Let the prime factorization of the integer $n$ be

$$
n=2^kp_1^{r_1}\cdots p_\ell^{r_\ell}q_1^{s_1}\cdots q_{m}^{s_m},
$$

where $p_1,\cdots,p_\ell$ are prime factors of the form $4k+1$ and $q_1,\cdots,q_m$ are prime factors of the form $4k+3$.

First, $N(x+y\mathrm{i})=n$ has a solution if and only if the exponents $s_1,\cdots,s_m$ of the $4k+3$ prime factors of $n$ are all even. This is because $q_1,\cdots,q_m$ are also Gaussian primes and their norms are their squares, so they must appear in pairs in the prime factorization of the norm.

Now suppose the equation has solutions. Then every solution has the form

$$
u(1+\mathrm{i})^k(a_1+b_1\mathrm{i})^{r_{1}^+}(a_1-b_1\mathrm{i})^{r_{1}^-}\cdots(a_\ell+ b_\ell\mathrm{i})^{r_\ell^+}(a_\ell-b_\ell\mathrm{i})^{r_\ell^-}q_1^{s_1/2}\cdots q_{m}^{s_m/2},
$$

where $u$ is a unit, $a_j\pm b_j\mathrm{i}$ are the conjugate prime factors of $p_j$ in the Gaussian integers, and $r_j^++r_j^-=r_j$. So the number of solutions is

$$
4(1+r_1)\cdots(1+r_\ell).
$$

Let $f(n)$ be the number of integer solutions of $x^2+y^2=n$. When there are solutions, $f(n)$ is given by the expression above; otherwise $f(n)=0$. It is easy to check that $\dfrac14f(n)$ is a [multiplicative function](./basic.md#multiplicative-functions). A multiplicative function is determined by its values at prime powers. From the expression for $f(n)$, the values of $\dfrac14f(n)$ at prime powers $p^k$ are:

1.  If $p$ is a prime of the form $4k+3$, then $\dfrac14f(1)=1,\dfrac14f(p)=0,\dfrac14f(p^2)=1,\dfrac14f(p^3)=0,\cdots$;
2.  If $p$ is a prime of the form $4k+1$, then $\dfrac14f(p^k)=k+1$;
3.  If $p=2$, then $\dfrac14f(2^k)=1$.

It is easy to check that all three cases can be written as

$$
\dfrac14f(p^k) = \sum_{j=0}^k\left(\dfrac{-4}{p}\right)^j = \sum_{j=0}^k\left(\dfrac{-4}{p^j}\right) = \sum_{d\mid p^k}\left(\dfrac{-4}{d}\right).
$$

Since the Kronecker symbol $\left(\dfrac{-4}{n}\right)$ is completely multiplicative, we get

$$
f(n) = 4\sum_{d\mid n}\left(\dfrac{-4}{d}\right)=4\sum_{d\mid n}\chi_{4,3}(d).
$$

The notation in the rightmost sum uses the fact that the Kronecker symbol $\left(\dfrac{-4}{n}\right)$ is a real [Dirichlet character](https://en.wikipedia.org/wiki/Dirichlet_character) modulo $4$.

### The Pythagorean equation

Gaussian integers give the general solution of the Pythagorean equation. The Pythagorean equation is the following quadratic Diophantine equation:

$$
x^2+y^2=z^2.
$$

Comparing with the previous section, this means solving $N(x+y\mathrm{i})=z^2$. Let $z$ have the prime factorization in $\mathbf Z$

$$
z=2^kp_1^{r_1}\cdots p_\ell^{r_\ell}q_1^{s_1}\cdots q_{m}^{s_m},
$$

so a solution $x+y\mathrm{i}$ has the prime factorization in $\mathbf Z[\mathrm{i}]$

$$
x+y\mathrm{i} = u(1+\mathrm{i})^{2k}(a_1+b_1\mathrm{i})^{r_{1}^+}(a_1-b_1\mathrm{i})^{r_{1}^-}\cdots(a_\ell+ b_\ell\mathrm{i})^{r_\ell^+}(a_\ell-b_\ell\mathrm{i})^{r_\ell^-}q_1^{s_1}\cdots q_{m}^{s_m}
$$

with $r_j^++r_j^-=2r_j$. We can compute the greatest common divisor of $x+y\mathrm{i}$ and $z$, which is the integer:

$$
\kappa = 2^kp_1^{\min\{r_1^+,r_1^-\}}\cdots p_\ell^{\min\{r_\ell^+,r_\ell^-\}}q_1^{s_1}\cdots q_m^{s_m}.
$$

After removing this common factor, $\kappa^{-1}(x+y\mathrm{i})$ only has prime factors of the form $a_j\pm b_j\mathrm{i}$, conjugate factors no longer appear in pairs, and the exponents $|r_j^+-r_j^-|$ must be even (because their sum $2r_j$ is even). So $\kappa^{-1}(x+y\mathrm{i})$ is the square of some quadratic integer $u+v\mathrm{i}$. This gives:

$$
x+y\mathrm{i} = \kappa(u+v\mathrm{i})^2,\ z=\kappa N(u+v\mathrm{i}).
$$

Over the integers $\mathbf Z$, this is the system:

$$
x = \kappa(u^2-v^2),\ y = 2\kappa uv,\ z = \kappa(u^2+v^2).
$$

Conversely, for any integers $u$ and $v$, the $(x,y,z)$ given by these expressions satisfies the Pythagorean equation. So this is the general solution of the Pythagorean equation.

From this process we also see that in a primitive Pythagorean triple $(x,y,z)$ (that is, $x,y,z$ have no common factor other than one), one of $x,y$ is odd and the other is even, and $z$ is odd with only prime factors of the form $4k+1$.

A similar method gives the general solution of $x^2+y^2=z^3$, or proves that $x^4+y^4=z^4$ has no solutions. Of course, using the general solution of the Pythagorean equation and infinite descent, we can prove a stronger result: $x^4+y^4=z^2$ has no solutions.

## Eisenstein integers

In this section, let $\omega=\dfrac{-1+\sqrt{3}\mathrm{i}}{2}=e^{2\pi\mathrm{i}/3}$.[^omega] The quadratic field $\mathbf Q(\sqrt{3}\mathrm{i})$ is the third and sixth [cyclotomic field](../algebra/field-theory.md#cyclotomic-fields), and its algebraic integers are called Eisenstein integers. The ring $\mathbf Z[\omega]$ of all Eisenstein integers is called the ring of Eisenstein integers. It has six units: $\pm 1$, $\pm\omega$ and $\pm\omega^2$. In the complex plane, the Eisenstein integers form a triangular lattice. Unlike the Gaussian integers, these lattice points are usually not integer points.

![](./images/eisenstein-integer.svg)

The norm of an Eisenstein integer is

$$
N(a+b\omega) = a^2-ab+b^2,
$$

which is also the squared distance from the lattice point to the origin in the complex plane.

Eisenstein integers are very similar to Gaussian integers. On Eisenstein integers we can also use the norm $N(\cdot)$ to define division with remainder, and establish the Euclidean algorithm, Bézout's theorem, unique factorization and so on. As above, we can work out how primes factor in the ring of Eisenstein integers. For this, note that the discriminant of $\mathbf Z[\omega]$ is $-3$, and the Kronecker symbol is

$$
\left(\dfrac{-3}{n}\right) = \begin{cases}
+1, & n\equiv 1\pmod 3,\\
-1, & n\equiv 2\pmod 3,\\
0,  & 3\mid n,
\end{cases}
$$

So the prime elements of the ring of Eisenstein integers, i.e., the Eisenstein primes, come in three kinds:

1.  Integer primes of the form $3k+2$, i.e., $2$ and primes of the form $6k+5$;
2.  The two conjugate Eisenstein prime factors of an integer prime of the form $3k+1$ (that is, of the form $6k+1$);
3.  The factor $(3+\sqrt{3}\mathrm{i})/2$ of the prime $3$, whose conjugate is its associate.

Using the method of the previous section, we can count the Eisenstein integers with norm $n$. Call this number $f(n)$. Then

$$
f(n)=6\sum_{d\mid n}\left(\dfrac{-3}{d}\right)=6\sum_{d\mid n}\chi_{3,2}(d). 
$$

Here $\chi_{3,2}(n)=\left(\dfrac{-3}{n}\right)$ is the real Dirichlet character modulo $3$. This expression shows that such Eisenstein integers exist if and only if every prime factor of $n$ of the form $3k+2$ has an even exponent.

By the norm formula above, $f(n)$ is also the number of integer solutions of the Diophantine equation $x^2-xy+y^2=n$, or of $x^2+xy+y^2=n$. Geometrically, it is the number of lattice points on the tilted ellipse $x^2\pm xy+y^2=n$.

Closely related to these equations is another Diophantine equation, $x^2+3y^2=n$, whose integer solutions correspond to lattice points on an axis-aligned ellipse. The substitution $x=(u+v)/2$ and $y=(u-v)/2$ turns it into the already solved equation $u^2-uv+v^2=n$. However, while every integer solution of $x^2+3y^2=n$ gives an integer solution of $u^2-uv+v^2=n$, the converse is not always true. If $n$ is even, then $u$ and $v$ must both be even, which means $x$ and $y$ must be integers, so the number of integer solutions of $x^2+3y^2=n$ is still $f(n)$. But if $n$ is odd, $u$ and $v$ may be one odd and one even, or both odd, so the corresponding $x$ and $y$ may both be half-integers or both be integers. This case needs a closer look.

Given one integer solution $(u,v)$ of $u^2-uv+v^2=n$, the integer solutions corresponding to the Eisenstein integers associated with $u+v\omega$ (including itself) are

$$
(u,v),(u-v,u),(-v,u-v),(-u,-v),(v-u,-u),(v,v-u).
$$

If the three integers $u,v,u-v$ are not all even, then exactly two are odd and one is even. So among these six solutions, two have both entries odd and four have one odd and one even entry. This shows that when $n$ is odd, only $\dfrac13$ of the integer solutions of $u^2-uv+v^2=n$ have both entries odd, and only those correspond to integer solutions of $x^2+3y^2=n$. So when $n$ is odd, the number of integer solutions of $x^2+3y^2=n$ is $\dfrac13f(n)$.

Finally, in the same way as for the Pythagorean equation, Eisenstein integers can solve the following Diophantine equations:

$$
x^2-xy+y^2=z^2
$$

$$
x^2+xy+y^2=z^2
$$

$$
x^2+3y^2=z^2
$$

$$
x^2+3y^2=z^3
$$

We won't write out their general solutions here. A similar method can also prove that $x^3+y^3=z^3$ has no solutions.

## References and notes

-   [Quadratic field - Wikipedia](https://en.wikipedia.org/wiki/Quadratic_field)
-   [Quadratic integer - Wikipedia](https://en.wikipedia.org/wiki/Quadratic_integer)
-   [Gaussian integer - Wikipedia](https://en.wikipedia.org/wiki/Gaussian_integer)
-   [Eisenstein integer - Wikipedia](https://en.wikipedia.org/wiki/Eisenstein_integer)
-   [Kronecker symbol - Wolfram MathWorld](https://mathworld.wolfram.com/KroneckerSymbol.html)
-   [Dirichlet character - Wikipedia](https://en.wikipedia.org/wiki/Dirichlet_character)
-   [Theodorus J. Dekker's Notes on Primes in Quadratic Fields](https://staff.science.uva.nl/t.j.dekker/PrimesPaper/Primes.pdf)
-   [Franz Lemmermeyer's Notes on Ideals in Quadratic Number Fields](http://www.fen.bilkent.edu.tr/~franz/ant/ant02.pdf)
-   [J.S. Milne - Algebraic Number Theory](https://www.jmilne.org/math/CourseNotes/ANT301.pdf)

[^omega]: Note that this choice of $\omega$ differs from the one above. By convention, when discussing general rings of quadratic integers one usually sets $\omega=(1+\sqrt{d})/2$ (when $d\equiv 1\pmod4$), while for the ring of Eisenstein integers one usually sets $\omega=(-1+\sqrt{-3})/2$. The difference has no real effect, but it may change the form of some expressions. Note that the ring of Eisenstein integers should not be written as $\mathbf Z[\sqrt{-3}]$.
