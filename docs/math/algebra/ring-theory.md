Prerequisites: [Basic Concepts of Abstract Algebra](./basic.md), [Group Theory](./group-theory.md)

## Introduction

**Ring theory** studies all kinds of rings.

The parts of ring theory covered in this article are closely tied to the theory of divisibility in number theory. First, similar to normal subgroups in group theory, this article introduces the kernel of a ring homomorphism, which is called an ideal of the ring; in fact, this generalizes the notion of a number in number theory to general rings. Then, by generalizing concepts on the ring of integers such as primes, the Euclidean algorithm and prime factorization to general rings, we get the concepts of different types of integral domains.

Many results from number theory still hold in other common rings. One could say that part of the work of ring theory is to ask whether these number-theoretic results hold in general rings, and if not, what restrictions must be put on a ring to make them hold.

???+ info "Notation"
    When there is no ambiguity, this article may omit the multiplication symbol of a ring, and may write the ring $(R,+,\cdot)$ simply as the ring $R$. In a ring $R$, the additive identity is also called the zero element, written $0$; the multiplicative identity is also called the unity (or identity), written $1$.

??? warning "Rings in this article are not required to have a unity"
    Note that the definition of a ring in this article does not require a unity. Some articles require rings to have a unity, in which case the statements of some results here need slight adjustments. For example, in this article ideals can be defined in terms of subrings, but in other articles they may need to be defined in terms of additive subgroups.

## Ideals

Similar to the case of groups, we can define subrings and ring homomorphisms.

???+ abstract "Subring"
    For a ring $(R,+,\cdot)$ and a subset $S$, if $(S,+,\cdot)$ is also a ring, then $S$ is called a **subring** of $R$.

???+ example "Example: the ring of integers $\mathbf Z$"
    For any integer $n$, $n\mathbf Z=\{nk:k\in\mathbf Z\}$ is a subring of $\mathbf Z$.

???+ abstract "Ring homomorphism"
    For rings $(R,+,\cdot)$ and $(S,\oplus,\odot)$, if $\pi$ preserves the addition and multiplication of the rings, that is, $\pi(r_1+r_2)=\pi(r_1)\oplus\pi(r_2)$ and $\pi(r_1\cdot r_2)=\pi(r_1)\odot\pi(r_2)$ for all $r_1,r_2\in R$, then the map $\pi:R\rightarrow S$ is called a **homomorphism** from the ring $R$ to the ring $S$.

??? info "When rings are required to have a unity"
    If the definition of a ring requires a unity, then the definition of a ring homomorphism also often requires the unity to be mapped to the unity. For homomorphisms between nonzero rings with unity, this extra requirement only ensures that the homomorphism does not map the whole ring to zero.

???+ example "Example: the ring of integers $\mathbf Z$ (continued)"
    For any nonzero integer $n$, the map taking residues modulo $n$, that is, $\pi:\mathbf Z\rightarrow\mathbf Z/n\mathbf Z$ with $\pi(a)=\bar a$, is a ring homomorphism.

The [discussion](./group-theory.md#group-homomorphisms) of kernels and images of group homomorphisms carries over here almost unchanged. The (relative) size of the image decides whether the homomorphism is surjective, and whether the kernel is trivial decides whether it is injective. The kernel of a ring homomorphism is defined as follows:

???+ abstract "Kernel of a homomorphism"
    The **kernel** of a homomorphism $\pi:R\rightarrow S$ from a ring $R$ to a ring $S$ is $\{r\in R:\pi(r)=0\}$, written $\ker\pi$, where $0$ is the additive identity of $S$.

Clearly, the kernel and image of a ring homomorphism are both subrings. Conversely, not every subring can be the kernel of some ring homomorphism. The subrings that can be kernels of ring homomorphisms are called ideals of the ring.

???+ abstract "Ideal"
    For a ring $R$ and a subring $I$, $I$ is called a

    -   **left ideal** of $R$ if $rI\subseteq I$ for all $r\in R$, where $rI=\{ra:a\in I\}$;
    -   **right ideal** of $R$ if $Ir\subseteq I$ for all $r\in R$, where $Ir=\{ar:a\in I\}$;
    -   **ideal** of $R$ if $I$ is both a left ideal and a right ideal of $R$.

Here an ideal $I$ is required to be closed under left and right multiplication by elements of $R$. This condition is natural: elements of an ideal are mapped to zero by the ring homomorphism, and any element multiplied on the left or right by zero should be zero, which is exactly the required closure. Beyond that, since the additive structure of a ring is an Abelian group, every subgroup is a normal subgroup; and the multiplicative structure of a ring is very primitive and puts no extra restrictions on substructures. This shows that being closed under left and right multiplication is also sufficient.

???+ example "Example: the ring of integers $\mathbf Z$ (continued)"
    As an example, the subring $n\mathbf Z$ mentioned earlier is actually an ideal of $\mathbf Z$. It is the set of all multiples of $n$. A multiple of $n$ times any integer is still a multiple of $n$. In fact, every ideal of $\mathbf Z$ has this form; such a ring is called a [principal ideal domain](#principal-ideal-domains). In a general ring, some ideals are not the set of multiples of a single element; the existence of such rings was the original motivation for studying ideals (rather than simply studying multiples)[^ideal-history].

### Quotient rings

Just like for groups, given an ideal of a ring, we can define a **quotient ring** on the set of all cosets (in the sense of the additive group). Consider the set

$$
R/I=\{a+I:a\in R\},
$$

where the coset is $a+I=\{a+b:b\in I\}$. One can prove that the operations

$$
\begin{aligned}
(a+I)+(b+I)&=(a+b)+I,\\
(a+I)(b+I)&=(ab)+I
\end{aligned}
$$

are well-defined, that is, their results do not depend on the choice of representatives of the cosets, if and only if $I$ is an ideal. Under these operations, $R/I$ forms a ring. Again just as for groups, we can establish the **first isomorphism theorem** for rings, and there is a natural homomorphism from a ring to its quotient ring. These show that ideals of rings play the same role in ring homomorphisms as normal subgroups do in group homomorphisms.

???+ note "First isomorphism theorem"
    Let $\pi:R\rightarrow S$ be a homomorphism from a ring $R$ to a ring $S$. Then $\ker\pi$ is an ideal of $R$, and $R/\ker\pi\cong\pi(R)$ is a subring of $S$.

???+ abstract "Natural homomorphism"
    For a ring $R$ and an ideal $I$, the map $\pi:R\rightarrow R/I$ given by $\pi(r)=r+I$ is a surjective homomorphism from $R$ to $R/I$, called the **natural homomorphism** from the ring $R$ to the quotient ring $R/I$.

???+ example "Example: the ring of integers $\mathbf Z$ (continued)"
    As an example, the ring $\mathbf Z/n\mathbf Z$ of residue classes of integers modulo $n$ is the quotient ring of $\mathbf Z$ modulo its ideal $n\mathbf Z$. This also explains the notation $\mathbf Z/n\mathbf Z$. The map $\pi:\mathbf Z\rightarrow\mathbf Z/n\mathbf Z$ taking residues modulo $n$ mentioned above is exactly the natural map here, and its kernel is exactly the ideal $n\mathbf Z$.

The other isomorphism theorems also hold for rings.

???+ note "Second isomorphism theorem"
    Let $R$ be a ring with a subring $A$ and an ideal $B$. Then $A+B=\{a+b:a\in A,b\in B\}$ is also a subring of $R$, $A\cap B$ is an ideal of $A$, $B$ is an ideal of $A+B$, and $(A+B)/B\cong A/(A\cap B)$.

???+ note "Third isomorphism theorem"
    Let $R$ be a ring with ideals $I,J$ such that $I\subseteq J$. Then $J/I$ is also an ideal of $R/I$, and $(R/I)/(J/I)\cong R/J$.

???+ note "Correspondence theorem"
    Let $R$ be a ring with an ideal $I$. Then there is a bijection $\varphi:\mathcal S\rightarrow\mathcal T$ between the set $\mathcal S=\{S:I\subseteq S\subseteq R\}$ of all subrings of $R$ containing $I$ and the set $\mathcal T=\{T:T\text{ is a subring of }R/I\}$ of all subrings of the quotient ring $R/I$, which maps $S\in\mathcal S$ to $S/I\in\mathcal T$. This bijection preserves inclusion between subrings, and ideals of $R$ are always mapped to ideals of $R/I$.

These theorems play a basic role when we discuss the structure of rings and ideals later.

### Operations on ideals

Various operations can be defined on the ideals of a ring. This is similar to how concepts such as greatest common divisor and least common multiple can be defined on the divisibility structure of the integers.

???+ abstract "Operations on ideals"
    Let $R$ be a ring with ideals $I,J$. We can define the following operations:

    -   The **sum** of ideals: $I+J=\{a+b:a\in I,b\in J\}$;
    -   The **product** of ideals: $IJ=\{\sum_{i=1}^na_ib_i:a_i\in I,b_i\in J\}$, that is, the set of all finite sums of products of the form $ab$;
    -   The **intersection** of ideals: $I\cap J$.

It is easy to check that the results of these operations are still ideals of the ring.

???+ example "Example: the ring of integers $\mathbf Z$ (continued)"
    Consider the ring of integers $\mathbf Z$. For ideals $n\mathbf Z$ and $m\mathbf Z$, we get

    $$
    \begin{aligned}
    n\mathbf Z+m\mathbf Z&=\gcd(m,n)\mathbf Z,\\
    (n\mathbf Z)(m\mathbf Z)&=(mn)\mathbf Z,\\
    (n\mathbf Z)\cap(m\mathbf Z)&=\mathrm{lcm}(m,n)\mathbf Z.
    \end{aligned}
    $$

In general, for a ring $R$ and its ideals $I$ and $J$, we always have

$$
IJ\subseteq I\cap J\subseteq I,J\subseteq I+J.
$$

With these definitions, the Chinese remainder theorem for integers can be generalized to general rings. But before that, we need to further generalize concepts such as primes and coprimality to general rings.

### Maximal ideals

We can understand the properties of a ring through the structure of its ideals.

A nonzero ring $R$ always has two trivial ideals, $\{0\}$ and $R$. If $R$ is also a commutative nonzero ring with unity, then a ring with only these two ideals is exactly a field[^simple-ring].

???+ note "Theorem"
    Let $R$ be a commutative nonzero ring with unity. Then $R$ is a field if and only if $R$ has only the trivial ideals $\{0\}$ and $R$.

??? note "Proof"
    If $R$ is a field, then for any nonzero ideal $I$ we can pick a nonzero element $a\in I$. Then any element $r\in R$ of the field satisfies $r=(ra^{-1})a\in (ra^{-1})I\subseteq I$, so $I=R$. Conversely, for any $a\in R$ with $a\neq 0$, one can check that $aR=\{ar:r\in R\}$ is an ideal. It must equal $R$, so there exists $b\in R$ with $ab=1$. This shows that $a$ has an inverse, so $R$ is a field.

The commutativity condition here is necessary; otherwise, we would need both the left ideals and the right ideals to be trivial to guarantee that the ring is a division ring.

This result can be generalized to the case where the ring itself is not a field. But then we need to look at quotient rings instead, and ask when a quotient ring of a commutative nonzero ring with unity is a field. A quotient ring $R/I$ being a field means that $R/I$ has only trivial ideals. By the correspondence theorem, the original ring $R$ has no ideal strictly between the ideal $I$ being quotiented out and $R$ itself. Such an ideal $I$ is called a maximal ideal.

???+ abstract "Maximal ideal"
    For a ring $R$ and an ideal $M$, if $M\neq R$, and the only ideals of $R$ containing $M$ are $M$ and $R$, then $M$ is called a **maximal ideal**.

???+ note "Theorem"
    Let $R$ be a commutative nonzero ring with unity and $M$ an ideal. Then the quotient ring $R/M$ is a field if and only if $M$ is a maximal ideal.

???+ example "Example: the ring of integers $\mathbf Z$ (continued)"
    For example, the ideal $n\mathbf Z$ of the ring of integers $\mathbf Z$ is a maximal ideal if and only if $n$ is prime. For a prime $p$, the quotient ring $\mathbf Z/p\mathbf Z$ is a field, also written $\mathbf F_p$.

Not every ring has a maximal ideal, but a nonzero ring with unity always does.

???+ note "Theorem (Krull)"
    For an ideal $I\neq R$ of a nonzero ring with unity $R$, there is always a maximal ideal $M$ of $R$ with $I\subseteq M$.

??? note "Proof"
    The idea is to use Zorn's lemma. Consider the set $\mathcal S$ of all proper ideals of $R$ (that is, ideals not equal to $R$) that contain $I$. Since $I\in\mathcal S$, it is nonempty, and it forms a partially ordered set under inclusion. For any chain $J_0\subseteq J_1\subseteq\cdots\subseteq J_n\subseteq\cdots$ in it, let $J$ be their union; it is easy to check that this is also an ideal. Moreover, $J\neq R$; otherwise $1\in J$, that is, there is some $n$ with $1\in J_n$, contradicting that $J_n$ is a proper ideal. Therefore, by Zorn's lemma, there exists a maximal ideal $M\supseteq I$.

In the theory of divisibility, the analogue of a maximal ideal is an irreducible element. This is because inclusion between ideals corresponds to divisibility between integers; having no ideal as a superset is like having no factor that divides it. However, the concept of a maximal ideal is broader than that of an irreducible element, because not every ideal is a principal ideal.

### Prime ideals

The condition for a field is stricter than that for an integral domain. An ideal that guarantees the quotient ring is an integral domain is called a prime ideal; it is similar to the concept of a prime number in the theory of divisibility.

???+ abstract "Prime ideal"
    For a commutative ring $R$ and an ideal $P$, if $P\neq R$, and for any elements $a,b\in R$ of the ring, whenever $ab\in P$ we have $a\in P$ or $b\in P$, then $P$ is called a **prime ideal**.

This definition may look a bit sudden, but compared with the [definition of a prime](../number-theory/basic.md#fundamental-theorem-of-arithmetic), this definition of a prime ideal is natural.

???+ note "Theorem"
    Let $R$ be a commutative nonzero ring with unity and $P$ an ideal. Then the quotient ring $R/P$ is an integral domain if and only if $P$ is a prime ideal.

??? note "Proof"
    For a commutative nonzero ring with unity $R$, the quotient ring $R/P$ is an integral domain if and only if $R/P$ has no zero divisors. Write $\bar a$ for the coset $a+P$. The quotient ring $R/P$ having no zero divisors is equivalent to $\bar a\bar b=\bar 0$ always implying $\bar a=\bar 0$ or $\bar b=\bar 0$. By the definition of the quotient ring, this is equivalent to $ab\in P$ always implying $a\in P$ or $b\in P$.

In the ring of integers $\mathbf Z$, $n\mathbf Z$ is a maximal ideal if and only if $n$ is prime, while $n\mathbf Z$ is a prime ideal if and only if $n$ is prime or $n=0$. In a general commutative ring, a maximal ideal is always a prime ideal, but of course the converse need not hold; this can be seen from the properties of the corresponding quotient rings.

???+ note "Theorem"
    For a commutative nonzero ring with unity $R$, every maximal ideal is a prime ideal.

We will see later that the converse holds only in rings with good properties that are similar enough to the ring of integers.

### Principal ideals

Similar to subgroups, when discussing rings we often need to consider the ideal generated by a subset.

???+ abstract "Ideal generated by a subset"
    For a nonzero ring with unity $R$ and a nonempty subset $A\subseteq R$, if $I$ is the smallest (with respect to inclusion) among the ideals of $R$ that contain $A$, then $I$ is called the **ideal generated by the subset $A$**, written $(A)$. In this case, $A$ is called a **generating set** of $(A)$.

???+ abstract "Principal ideal"
    An ideal generated by a single element $a\in R$ is called a **principal ideal**, written $(a)$. In this case, $a$ is called a **generator** of $(a)$.

For a set $A$, we can construct the ideal it generates. First, define

$$
\begin{aligned}
RA&=\{r_1a_1+\cdots+r_na_n:r_i\in R,a_i\in A,n\in\mathbf N_+\},\\
AR&=\{a_1r_1+\cdots+a_nr_n:r_i\in R,a_i\in A,n\in\mathbf N_+\}.
\end{aligned}
$$

These are in fact the left ideal and the right ideal generated by $A$, respectively. Then the ideal generated by the subset $A$ is $RAR$. For a commutative ring, all these structures are the same.

All ideals $n\mathbf Z$ of the ring of integers are principal ideals, and below they are often written $(n)$.

## Integral domains

An integral domain is a commutative nonzero ring with unity and no zero divisors. This concept is exactly a generalization of the ring of integers. However, rings obtained this way do not necessarily have good enough properties to let every result from the divisibility theory of integers carry over unchanged. To generalize results from number theory, we can put further restrictions on integral domains. The three most common kinds are Euclidean domains, principal ideal domains and unique factorization domains; each earlier concept is strictly contained in the later ones.

### Divisibility

First, we generalize the relevant concepts from the divisibility theory of integers to general commutative rings.

???+ abstract "Divisibility"
    Let $R$ be a commutative ring with elements $a,b\in R$. If there exists $x\in R$ with $a=bx$, then $b$ is said to **divide** $a$, written $b\mid a$. In this case, $b$ is called a **divisor** of $a$.

???+ abstract "Associates"
    Let $R$ be a commutative ring with elements $a,b\in R$. If they differ only by a unit, that is, there exists a unit $u\in R$ with $a=bu$, then $a$ and $b$ are called **associates** (or **associate**).

Divisibility is a [preorder](../order-theory.md#binary-relations) relation on the ring, and being associates is an equivalence relation on the ring. In terms of ideals, $a\mid b$ is equivalent to $(b)\subseteq (a)$, and $a$ and $b$ being associates is equivalent to $(a)=(b)$. So when discussing elements of a ring, we usually don't care about the difference between associates. As with the integers, the greatest common divisor of $a$ and $b$ in a commutative ring is defined as the greatest lower bound (infimum) of $\{a,b\}$.

???+ abstract "Greatest common divisor"
    For a commutative ring $R$ and elements $a,b\in R$, if there exists a nonzero element $d\in R$ such that $d\mid a$ and $d\mid b$, and $d'\mid d$ for every $d'$ satisfying $d'\mid a$ and $d'\mid b$, then $d$ is called a **greatest common divisor** of $a$ and $b$, written $\gcd(a,b)$.

In an integral domain, the greatest common divisor is unique up to associates. The discussion below is restricted to integral domains.

In integral domains, we can also set up concepts similar to primes. In the theory of integers, primes have two equivalent definitions, but in general integral domains these two definitions correspond to different concepts:

???+ abstract "Prime element"
    Let $R$ be an integral domain and $p\in R$ a nonzero element. If $(p)$ is a prime ideal, that is, $p$ is not a unit and $p\mid ab$ always implies $p\mid a$ or $p\mid b$, then $p$ is called a **prime** (prime element).

???+ abstract "Irreducible element"
    Let $R$ be an integral domain and $r\in R$ a nonzero element. If $r$ is not a unit, and for any $a,b\in R$ with $r=ab$, $a$ or $b$ is a unit, then $r$ is called an **irreducible** element, or $r$ is said to be irreducible. Conversely, if $r=ab$ where neither $a$ nor $b\in R$ is a unit, then $r$ is called reducible.

One can show that the principal ideal $(r)$ of an irreducible element $r$ must be maximal among all proper principal ideals of the ring; however, in a general integral domain, not all ideals are principal, so the concepts of irreducible element and maximal ideal are not equivalent.

Similar to proving that prime ideals are maximal ideals in a principal ideal domain, one can prove the following in general:

???+ note "Theorem"
    Let $R$ be an integral domain. If $a\in R$ is a prime, then $a$ must also be irreducible.

??? note "Proof"
    Let $r\in R$ be a prime, and let $a,b\in R$ satisfy $r=ab$. Since $r$ is prime, we may assume $r\mid a$, so $a=cr=cba$. Since the cancellation law holds in an integral domain, $1=bc$, so $b$ has the inverse $c$. This shows that $r$ is irreducible.

The converse does not hold.

??? example "Counterexample"
    In the quadratic integer ring $\mathbf Z[\sqrt{-5}]$, $3$ is irreducible, but $9=3\cdot 3=(2+\sqrt{-5})(2-\sqrt{-5})$, so it is not prime.

    Here is a proof of this counterexample. Readers not familiar with quadratic integer rings should first read the section on [quadratic integer rings](#example-quadratic-integer-rings). Let $N(\cdot)$ be the norm on the quadratic integer ring. For any factorization $3=ab$, we have $N(a)N(b)=N(3)=9$. If neither $a$ nor $b$ is a unit, then $N(a)$ and $N(b)$ are both greater than $1$, so we must have $N(a)=N(b)=3$. But $\mathbf Z[\sqrt{-5}]$ has no such element, that is, $x^2+5y^2=3$ has no integer solutions. This shows that $3$ is irreducible. As for $3$ not being prime, we need to show that $3$ does not divide $2\pm\sqrt{-5}$, which is obvious.

### Euclidean domains

Related reading: [(Extended) Euclidean algorithm](../number-theory/gcd.md), [Bézout's theorem](../number-theory/bezouts.md)

A Euclidean domain is an integral domain in which we can carry out repeated division (the Euclidean algorithm).

???+ abstract "Euclidean domain"
    For an integral domain $R$, if there is a map $N:R\setminus\{0\}\rightarrow\mathbf N$ such that for any $a,b\in R$ with $b\neq 0$, there exist $q,r\in R$ with $a=qb+r$ and either $r=0$ or $N(r)<N(b)$, then $R$ is called a **Euclidean domain** (ED). The map $N$ is called the norm of elements of the Euclidean domain.

??? info "Other equivalent definitions"
    The definition used in this article only defines the norm on nonzero elements. Different texts may handle the definition of a Euclidean domain differently. For example, some texts additionally define $N(0)=0$; but the value $N(0)$ is never used in the division with remainder, so this does not matter. As another example, the definition on [Wikipedia](https://en.wikipedia.org/wiki/Euclidean_domain) also requires the norm $N$ to satisfy: $N(a)\le N(ab)$ for any nonzero $a,b\in R$. However, it is easy to check that if a Euclidean domain $R$ has a norm $N(\cdot)$ with the properties required by the definition here, then we can define the norm $N'(a)=\min_{b\in R\setminus\{0\}} N(ab)$ so that it satisfies the extra property $N'(a)\le N'(ab)$. So these different definitions are all equivalent.

This definition is really a generalization of division with remainder for integers. The norm lets us compare the relative sizes of the remainder and the divisor. So during repeated division, the norms of the remainders keep decreasing; since the norm takes values in the natural numbers, the process must end when $r=0$. This gives the Euclidean algorithm on Euclidean domains.

Being able to run the Euclidean algorithm means that greatest common divisors can be computed efficiently in a Euclidean domain. Exactly as in the divisibility theory of integers, one can prove that the result of the Euclidean algorithm is always a greatest common divisor, and that Bézout's theorem holds, with the coefficients found by the extended Euclidean algorithm.

???+ note "Theorem"
    For a Euclidean domain $R$ and elements $a,b\in R$, the result $d$ of running the Euclidean algorithm on $a$ and $b$ is a greatest common divisor of $a$ and $b$, and there exist $x,y\in R$ with $d=ax+by$; conversely, every element of the form $ax+by$ is a multiple of $d$.

Note that in the language of ring theory, the elements of the form $ax+by$ are exactly the elements of the ideal $(a,b)$, and this theorem shows that $(a,b)$ must be the principal ideal $(d)$.

In fact, every ideal in a Euclidean domain is a principal ideal.

???+ note "Theorem"
    Every ideal in a Euclidean domain is a principal ideal.

??? note "Proof"
    Let $R$ be a Euclidean domain and $I$ an ideal. If $I=\{0\}$, it is clearly a principal ideal. Suppose $I$ is a nonzero ideal. By definition, $R$ has a norm $N(\cdot)$, so we can take a nonzero element $d$ of $I$ with the smallest norm. Then for any $a\in I$, we have $a=qd+r$ with $r=0$ or $N(r)< N(d)$. Since $r=a-qd\in I$, by the choice of $d$ we get $r=0$, that is, $a=qd\in (d)$. This shows that $I$ must be a principal ideal.

### Principal ideal domains

An integral domain in which every ideal is principal is called a principal ideal domain. This is a class of integral domains with quite good properties, and they are very common. In these integral domains, the concept of an ideal is the same as the concept of multiples in the integers.

???+ abstract "Principal ideal domain"
    For an integral domain $R$, if every ideal of $R$ is a principal ideal, then $R$ is called a **principal ideal domain** (PID).

So the last theorem of the previous section can be restated as follows:

???+ note "Theorem"
    Every Euclidean domain is a principal ideal domain.

In a principal ideal domain, maximal ideals are exactly the ideals generated by irreducible elements. Just as primes and irreducible elements are equivalent in the integers, these two concepts are also equivalent in a principal ideal domain, so maximal ideals and prime ideals are also completely equivalent.

???+ note "Theorem"
    Let $R$ be a principal ideal domain with a nonzero ideal $I$. Then $I$ is a prime ideal if and only if $I$ is a maximal ideal.

??? note "Proof"
    We only need to prove that every prime ideal is maximal. Let $R$ be a principal ideal domain with a nonzero prime ideal $(p)$, and let $(a)$ be an ideal with $(p)\subseteq(a)\subseteq R$. This means $a\mid p$, so there exists $b\in R$ with $p=ab$. Since $(p)$ is a prime ideal, $ab\in(p)$ means $a\in(p)$ or $b\in(p)$. If $a\in(p)$, then $(a)\subseteq (p)$, so $(a)=(p)$; if $b\in(p)$, then $b=cp$, so $p=acp$, and since $p\neq 0$, $1=ac$, that is, $a$ has the inverse $c$, so $(a)=R$. This shows that $(p)$ is a maximal ideal.

???+ note "Corollary"
    Let $R$ be a principal ideal domain with a nonzero element $r$. Then $r$ is prime if and only if $r$ is irreducible.

The analysis of Bézout's theorem in the previous section carries over to principal ideal domains.

???+ note "Theorem"
    Let $R$ be a principal ideal domain and $a,b\in R$ nonzero elements. Let $d\in R$ be a generator of the ideal $(a,b)$. Then $d$ is a greatest common divisor of $a$ and $b$, unique up to associates; moreover, there exist $x,y\in R$ with $ax+by=d$.

In other words, [Bézout's theorem](../number-theory/bezouts.md) still holds in principal ideal domains. Both have greatest common divisors; the biggest difference between Euclidean domains and principal ideal domains is that in the former, the greatest common divisor can be computed efficiently by the Euclidean algorithm, while principal ideal domains generally have no such efficient algorithm.

### Unique factorization domains

A more general concept than principal ideal domains is unique factorization domains. The unique factorization theorem for integers is called the [fundamental theorem of arithmetic](../number-theory/basic.md#fundamental-theorem-of-arithmetic). Similar unique factorization theorems actually still hold in some integral domains that are not principal ideal domains. Such integral domains are called unique factorization domains.

???+ abstract "Unique factorization domain"
    For an integral domain $R$, if every nonzero non-unit element $r$ can be written as $r=p_1\cdots p_n$, where $p_1,\cdots,p_n$ are irreducible elements (possibly repeated), and such a factorization is unique up to associates and reordering, then $R$ is called a **unique factorization domain** (UFD).

The fundamental theorem of arithmetic says that the ring of integers $\mathbf Z$ is a unique factorization domain.

Above we gave a counterexample of an irreducible element that is not prime; in the integral domain $\mathbf Z[\sqrt{-5}]$ involved there, unique factorization no longer holds. However, in every unique factorization domain, irreducible elements and primes are equivalent.

???+ note "Theorem"
    For a unique factorization domain $R$ and a nonzero element $a\in R$, $a$ is prime if and only if $a$ is irreducible.

??? note "Proof"
    We only need to prove that every irreducible element is prime. For an irreducible element $r$, if $r\mid ab$, then there exists $c\in R$ with $ab=rc$. Since $R$ is a unique factorization domain, we can factor each of $a,b,c\in R$ into a product of irreducible elements. Comparing both sides, uniqueness of factorization shows that $r$ must be associate to some irreducible factor of $a$ or $b$, so $r$ divides one of $a$ or $b$. This shows that $r$ is also prime.

Every principal ideal domain is a unique factorization domain.

???+ note "Theorem"
    Every principal ideal domain is a unique factorization domain.

??? note "Proof"
    Let $R$ be a principal ideal domain, and let $r\in R$ be neither zero nor a unit. To show that $r$ can be uniquely factored into a product of irreducible elements, we proceed in two steps: first prove that a factorization exists, then prove that it is unique.

    Existence of a factorization is fairly natural. If $r$ is already irreducible, there is nothing more to factor; otherwise, there must exist $r_1,r_2$ with $r=r_1r_2$ where neither $r_1$ nor $r_2$ is a unit. Then, if $r_1$ and $r_2$ are both irreducible, there is again nothing more to factor; otherwise, whichever of $r_1$ and $r_2$ is not irreducible can be factored further, so $r$ can be written as a product of more elements. In this way, as long as not all factors in the product are irreducible, the factoring process can continue. The factoring must stop after finitely many steps. Otherwise, the axiom of choice lets us pick an infinitely long chain of elements $\{r_{(i)}\}_{i=0}^\infty$ from $R$ with $r_{(0)}=r$ and $r_{(i+1)}\mid r_{(i)}$ for all $i\in\mathbf N$, where all these divisibility relations are strict, that is, the chain contains no associates. In the language of ideals, this corresponds to a strictly increasing infinite sequence of ideals: $I_{0}\subset I_{1}\subset \cdots\subset I_{i}\subset\cdots\subset R$, where $I_i=(r_{(i)})$. It is easy to check that the union $I=\bigcup_{i=0}^\infty I_i$ of these ideals is still an ideal, so it must be a principal ideal. Let $a$ be a generator of the principal ideal $I$; then there exists $n\in\mathbf N$ with $a\in I_n$. So $I=(a)\subseteq I_n$. This shows that such a strictly increasing infinite sequence of ideals does not exist, so the factoring process above must stop in finitely many steps.

    Next we prove uniqueness of the factorization, by induction on the number of factors. The key step of the induction is to check that if $r=p_1p_2\cdots p_n=q_1q_2\cdots q_m$ with $n\le m$, then $p_1$ must be associate to some $q_j$. Here we need the earlier result: in a principal ideal domain, every irreducible element is prime. Since $p_1$ is an irreducible element of $R$, it is also prime, so by induction on the product on the right-hand side, there must be some element $q_j$ with $p_1\mid q_j$. So there exists $c\in R$ with $q_j=p_1c$. Since $q_j$ is irreducible and $p_1$ is also irreducible, by definition $c$ must be a unit, so $p_1$ and $q_j$ are associates. Then we can use the cancellation law to cancel $p_1$ and $q_j$ from the two sides, and multiply the unit by which they differ into any one of the remaining elements. By the induction hypothesis, $p_2\cdots p_n$ and $q_1\cdots q_{j-1}q_{j+1}\cdots q_m$ must have the same number of irreducible factors, and these are the same up to associates. This proves the theorem.

Finally, the existence of greatest common divisors still holds in unique factorization domains.

???+ note "Theorem"
    Let $R$ be a unique factorization domain with nonzero elements $a,b\in R$, which factor as $a=up_1^{r_1}\cdots p_n^{r_n}$ and $b=vp_1^{s_1}\cdots p_n^{s_n}$, where $u,v$ are units, $p_1,\cdots,p_n$ are pairwise distinct irreducible elements, and $r_i,s_i$ are natural numbers. Then a greatest common divisor of them is $d=p_1^{\min\{r_1,s_1\}}\cdots p_n^{\min\{r_n,s_n\}}$.

This actually shows that the existence of greatest common divisors is a weaker property than unique factorization[^gcd-domain].

### Example: quadratic integer rings

Related reading: [Quadratic fields](../number-theory/quadratic.md)

You can't understand abstract algebra without examples. It was precisely because the study of Fermat's Last Theorem required studying the properties of a class of algebraic integers that today's ring theory gradually developed[^ring-theory-history]. Here we discuss the simplest algebraic integers, namely quadratic integers. The proofs of many results in this part need advanced algebraic number theory, so they are omitted.

A **quadratic integer** is a complex root of a quadratic equation $\alpha^2+b\alpha+c=0$ with integer coefficients and leading coefficient one. Every quadratic integer has the form

$$
\alpha=a+b\omega,~(a,b\in\mathbf Z)
$$

where

$$
\omega=\begin{cases}
\dfrac{1+\sqrt{D}}{2},& D\equiv 1\pmod 4,\\
\sqrt D,& D\equiv 2,3\pmod 4,
\end{cases}
$$

and $D$ is square-free.

??? note "Analysis"
    By the quadratic formula, the roots of this equation can always be written as

    $$
    \alpha=\frac{-b\pm\sqrt{b^2-4c}}{2}.
    $$

    When $b=2k+1$ is odd, the root can be written as

    $$
    \alpha=-k-\frac{1\pm\sqrt{4(k^2+k-c)+1}}{2}.
    $$

    Otherwise, when $b=2k$ is even, the root can be written as

    $$
    \alpha=-k\pm\sqrt{k^2-c}.
    $$

    From this we can conclude that quadratic integers must have the form above.

It is easy to check that for such an $\omega$, the set $\mathbf Z[\omega]=\{a+b\omega:a,b\in\mathbf Z\}$ forms a ring. This is called a **quadratic integer ring**, and its field of fractions is the quadratic field $\mathbf Q(\sqrt D)$. When $D>0$, all the quadratic integers are real, so it is also called a **real quadratic integer ring**; when $D<0$, all quadratic integers other than ordinary integers are non-real complex numbers, so it is also called an **imaginary quadratic integer ring**.

Every quadratic integer ring $\mathbf Z[\omega]$ is an integral domain. When $D=-1$, $\mathbf Z[\sqrt{-1}]$ (also written $\mathbf Z[\mathrm{i}]$) is called the ring of Gaussian integers; when $D=-3$, $\mathbf Z\left[\dfrac{1+\sqrt{-3}}{2}\right]$ is called the ring of Eisenstein integers.

For a quadratic integer $a+b\omega$, we define its **conjugate** to be $a+b\bar\omega$, where

$$
\bar\omega=\begin{cases}
\dfrac{1-\sqrt{D}}{2},& D\equiv 1\pmod 4,\\
-\sqrt D,& D\equiv 2,3\pmod 4,
\end{cases}
$$

Note that when $D>0$, quadratic integers are real numbers, so this notion of conjugate is not exactly the same as the complex conjugate; both are special cases of the notion of conjugate algebraic elements in field theory. Conjugate quadratic integers are roots of the same quadratic equation with integer coefficients.

On a quadratic integer ring we can define the **norm**

$$
\begin{aligned}
N(a+b\omega)&=(a+b\omega)(a+b\bar\omega)\\
&=\begin{cases}
a^2+ab+\dfrac{1-D}{4}b^2,& D\equiv 1\pmod 4,\\
a^2-Db^2,& D\equiv 2,3\pmod 4.
\end{cases}
\end{aligned}
$$

The norm of a quadratic integer is always an integer. In particular, when $D<0$, the norm is always a natural number. The norm preserves multiplication, that is, $N(ab)=N(a)N(b)$.

The units of a quadratic integer ring are exactly the elements of norm $\pm1$. For $D>0$, this amounts to finding solutions of the [Pell equation](../number-theory/pell-equation.md)  $x^2-Dy^2=\pm1$ or $x^2-Dy^2=\pm4$. For $D<0$, it is easy to check that, apart from the two special cases of the Gaussian integers $\mathbf Z[\rm{i}]$ with units $\{\pm1,\pm\rm{i}\}$ and the Eisenstein integers $\mathbf Z[\omega]$ with units $\{\pm1,\pm\omega,\pm\omega^2\}$, the only units are $\{\pm1\}$.

The norm $N(\alpha)$ defined on a quadratic integer ring can be used to prove that it is a Euclidean domain. For $D>0$, we need to use its absolute value $|N(\alpha)|$ as the norm in the definition of a Euclidean domain. Using the norm obtained this way, one can prove that for $D<0$ with

$$
D=-1,-2,-3,-7,-11
$$

or for $D>0$ with

$$
D=2, 3, 5, 6, 7, 11, 13, 17, 19, 21, 29, 33, 37, 41, 57, 73
$$

the corresponding quadratic integer rings are Euclidean domains with respect to $|N(\cdot)|$. However, the norm in the definition of a Euclidean domain need not be the norm defined above. For example, when $D=14,69$, the corresponding quadratic integer rings are also Euclidean domains, but a different norm is needed. For $D<0$, one can prove that the cases above are all the Euclidean domains among quadratic integer rings.

With more advanced methods, we can also decide whether a quadratic integer ring is a principal ideal domain. One can prove that for $D<0$, only

$$
D=-1,-2,-3,-7,-11,-19,-43,-67,-163
$$

give quadratic integer rings that are principal ideal domains. Comparing with the result above, cases such as $D=-19$ give examples of principal ideal domains that are not Euclidean domains. For $D>0$, there is no complete result yet.

However, one can prove that among quadratic integer rings, unique factorization domains and principal ideal domains are the same. The result above shows, for example, that $\mathbf Z[\sqrt{-5}]$ is not a principal ideal domain, and so it is not a unique factorization domain either. We already showed with an explicit example that unique factorization fails in it:

$$
9=3\times3=(2+\sqrt{-5})\times(2-\sqrt{-5}).
$$

Using the same example, we can show that the ideal $(3,2+\sqrt{-5})$ is not a principal ideal. We will see later that a simple example of a unique factorization domain that is not a principal ideal domain is the polynomial ring $\mathbf Z[x]$.

Although many quadratic integer rings are not unique factorization domains, they are all [Dedekind domains](https://en.wikipedia.org/wiki/Dedekind_domain). This means every nontrivial ideal in a quadratic integer ring can be uniquely factored into a product of prime ideals. But if the quadratic integer ring itself is not a principal ideal domain, these prime ideal factors do not necessarily correspond to prime elements, so the unique factorization theorem (factoring numbers into products of primes) no longer holds: this was the original motivation for studying ideals rather than numbers.

## Polynomial rings

Related reading: [Introduction to polynomial techniques](../poly/intro.md)

In competitive programming, we often meet various operations on polynomials. Multiplication, inversion, taking remainders and other polynomial operations can be seen as generalizations of operations on numbers to polynomial rings. The language of abstract algebra helps us understand the properties of these operations on polynomial rings more quickly.

???+ abstract "Polynomial"
    For a nonzero commutative ring with unity $R$, a **polynomial** over $R$ is a formal sum

    $$
    \sum_{k=0}^{n}a_kx^k = a_0+a_1x+\cdots+a_{n-1}x^{n-1}+a_nx^n,
    $$

    where $n\in\mathbf N$ and $a_k\in R$ for each $k$. These $a_k$ are called the **coefficients** of the polynomial, and the corresponding $a_kx^k$ are called its **terms**. The $k$ in the term $a_kx^k$ is called the **degree** of that term.

    The polynomial whose coefficients are all zero (the zero element) is called the **zero polynomial**, written $0$. For any other polynomial, we may assume $a_n\neq 0$, that is, $a_nx^n$ is the term of highest degree among the terms with nonzero coefficients. Then the natural number $n$ is called the **degree** of the polynomial, the term $a_nx^n$ is called the **leading term**, and $a_n$ is called the **leading coefficient**. A polynomial whose leading coefficient is one (the unity) is called **monic**. The degree of the zero polynomial is left undefined, or defined to be $-\infty$.

The $x$ appearing in the polynomial notation is called the **indeterminate** of the polynomial. It has no meaning of its own and no range of values. It is there only to mark the positions of the coefficients by its exponents. So a polynomial can also be written as a sequence over $R$

$$
(a_0,a_1,...,a_{n-1},a_n,0,0,\cdots).
$$

However, such a sequence can only have finitely many nonzero terms. Two polynomials are equal if their coefficient sequences are the same. This is the same as saying their formal sums are identical after filling in the terms with zero coefficients. Below we won't distinguish between different formal-sum notations of equal polynomials: if needed, readers can fill in the missing zero coefficients themselves.

Sometimes we need to substitute an element of the ring for the indeterminate of a polynomial. For example, if $f(x)$ is a polynomial over $R$ and $a\in R$, the result of substituting $a$ into $f(x)$ is $f(a)$. This means: replacing $x$ with $a$ in the formal sum of the polynomial gives an arithmetic expression in $R$, and $f(a)$ is the result of evaluating this expression in $R$.

??? info "Polynomials and polynomial functions"
    Readers should not confuse these two concepts. A polynomial is just a finite sequence of coefficients; it does not automatically become a function. Although substituting ring elements for the indeterminate does map polynomials to polynomial functions, this map is not necessarily injective. For example, $f(x)=x^p-x$ as a polynomial over the field $\mathbf F_p$ is clearly not the zero polynomial; but as a polynomial function $\mathbf F_p\rightarrow \mathbf F_p$, $f(x)$ is identically zero (this is Fermat's little theorem). Although the two concepts are different, many concepts for polynomial functions can be generalized to polynomials. For example, by imitating differentiation, indefinite integration and composition of polynomial functions, we can define (formal) [derivatives](../poly/intro.md#derivative), [indefinite integrals](../poly/intro.md#derivative), [composition](../poly/intro.md#composition) and so on for polynomials. These formal operations don't rely on any topological structure, but many rules of computation still hold.

For polynomials

$$
\begin{aligned}
f(x)&=a_0+a_1x+\cdots+a_{n-1}x^{n-1}+a_nx^n,\\
g(x)&=b_0+b_1x+\cdots+b_{n-1}x^{n-1}+b_nx^n,
\end{aligned}
$$

polynomial addition is defined as

$$
f(x)+g(x) = (a_0+b_0)+(a_1+b_1)x+\cdots+(a_{n-1}+b_{n-1})x^{n-1}+(a_n+b_n)x^n,
$$

and polynomial multiplication is defined as

$$
f(x)g(x) = a_0b_0+(a_1b_0+a_0b_1)x+(a_2b_0+a_1b_1+a_0b_2)x^2+\cdots,
$$

where the coefficient of the $x^k$ term is $\sum_{i=0}^ka_{k-i}b_i$. Under addition and multiplication defined this way, one can prove that all polynomials over $R$ form a ring, written $R[x]$.

The degree of a polynomial $f(x)$ is written $\deg f(x)$. Polynomials of degree zero are constant polynomials; they and the zero polynomial amount to the embedding of $R$ in $R[x]$. Clearly, $R$ has zero divisors if and only if $R[x]$ has zero divisors.

???+ note "Theorem"
    The polynomial ring $R[x]$ is an integral domain if and only if $R$ is an integral domain.

In the polynomial ring $R[x]$ over an integral domain $R$, the results of addition and multiplication satisfy

$$
\begin{aligned}
\deg(f(x)+g(x)) &\le \max\{\deg f(x),\deg g(x)\},\\
\deg(f(x)g(x)) &= \deg f(x) + \deg g(x).
\end{aligned}
$$

Here we set $\deg 0 = -\infty$. So the units of a polynomial ring must be among the units of its constant polynomials. No polynomial of degree one or higher is invertible.

The discussion below is restricted to polynomials over integral domains.

???+ info "Convention"
    Below, we use "polynomial over the ring $R$" and "polynomial in the polynomial ring $R[x]$" interchangeably. For example, a polynomial being irreducible over $R$ means it is irreducible in $R[x]$. Also, if $R$ is a subring of $S$, then polynomials over $R$ are automatically polynomials over $S$; we won't point this out again.

### Polynomial rings over fields

Among polynomial rings over integral domains, the ones with the simplest properties are of course polynomial rings over fields. In the polynomial ring $F[x]$ over a field $F$, coefficients can be divided, so we can define division with remainder. Let the norm of a nonzero polynomial $f(x)$ be $N(f(x))=\deg f(x)$. Then for a polynomial $f(x)$ and a nonzero polynomial $g(x)$ in $F[x]$, we can clearly divide with remainder:

$$
f(x)=g(x)q(x)+r(x),
$$

where $q(x),r(x)\in F[x]$, and $r(x)=0$ or $\deg r(x)<\deg g(x)$. This shows that polynomial rings over fields are Euclidean domains.

???+ note "Theorem"
    The polynomial ring $F[x]$ over a field $F$ is a Euclidean domain, a principal ideal domain, and a unique factorization domain.

In competitive programming, because of precision issues in computation, we usually work with the polynomial ring $\mathbf F_p[x]=(\mathbf Z/p\mathbf Z)[x]$, where the modulus $p$ must be prime. Such a ring allows operations like the Euclidean algorithm. However, for an arbitrary modulus $n$, the polynomial ring $(\mathbf Z/n\mathbf Z)[x]$ is not even an integral domain.

Having division with remainder means that a root of a polynomial always corresponds to a linear factor of it.

???+ abstract "Root"
    A **root** of a polynomial $f(x)$ is an element $\xi\in F$ such that $f(\xi)=0$.

???+ note "Theorem"
    For a polynomial $f(x)$ over a field $F$ and an element $\xi\in F$, $\xi$ is a root of $f(x)$ if and only if $f(x)$ has the linear factor $(x-\xi)$.

??? note "Proof"
    Division with remainder gives $q(x),r(x)$ with $f(x)=q(x)(x-\xi)+r(x)$ and $\deg r(x)<\deg(x-\xi)=1$. So $r(x)$ is a constant polynomial or the zero polynomial. Let $r(x)=c$; then $f(x)=q(x)(x-\xi)+c$. Substituting $x=\xi$ gives $0=f(\xi)=c$, that is, $f(x)=q(x)(x-\xi)$.

The concept of a root can be extended to multiple roots.

???+ abstract "Multiple root"
    If a polynomial $f(x)$ has the factor $(x-\xi)^k$ and $(x-\xi)^{k+1}$ does not divide $f(x)$, then $\xi$ is called a **root of multiplicity $k$** of $f(x)$. If $k>1$, the root $\xi$ is called a **multiple root** of $f(x)$; if $k=1$, the root $\xi$ is called a **simple root** of $f(x)$.

???+ note "Theorem"
    If a polynomial $f(x)$ over a field $F$ has the (possibly repeated) roots $\xi_1,\cdots,\xi_k$, then it must have the factor $(x-\xi_1)\cdots(x-\xi_k)$. Consequently, if a polynomial $f(x)$ over a field $F$ has degree $n$, it has at most $n$ roots (counted with multiplicity).

??? note "Proof"
    It is enough to note that $F[x]$ is a unique factorization domain.

Although unique factorization holds for polynomials over a field, there is no general way to decide whether a given polynomial is reducible. Low-degree cases are relatively easy. For example, every polynomial of degree one is irreducible. Over special fields, all irreducible polynomials have degree one. Such fields are called [algebraically closed fields](./field-theory.md#algebraically-closed-fields). Over such a field, every polynomial of positive degree has a root, so any polynomial of degree greater than one can be factored further. One example is the field of complex numbers $\mathbf C$. Over the field of real numbers $\mathbf R$, there are irreducible polynomials of degree two; over the field of rational numbers $\mathbf Q$, the structure of irreducible polynomials is even more complicated. The [field theory](./field-theory.md) page has more discussion of polynomials over the rational numbers and over finite fields.

The results above are all about polynomials over fields. Polynomials over more general integral domains can often be reduced to this case.

Next, consider the polynomial ring $R[x]$ over a unique factorization domain $R$. Working directly in $R[x]$, many operations are limited because coefficients often cannot be divided. Instead, we can extend $R$ to its field of fractions $F$, and factor a polynomial $f(x)$ of $R[x]$ in $F[x]$. Since $F[x]$ is a unique factorization domain, we can then work back from the factorization of $f(x)$ in $F[x]$ to a factorization in $R[x]$. Fortunately, this idea always works.

???+ note "Gauss's lemma"
    Let $R$ be a unique factorization domain with field of fractions $F$, and let $f(x)\in R[x]$. If $f(x)=A(x)B(x)$ in $F[x]$, then there must exist $s,t\in F$ such that $a(x)=sA(x)\in R[x]$, $b(x)=tB(x)\in R[x]$, and $f(x)=a(x)b(x)$. Therefore, if $f(x)$ of positive degree is irreducible in $R[x]$, then it is irreducible in $F[x]$.

??? note "Proof"
    Suppose $f(x)\in R[x]$ is reducible in $F[x]$, with $f(x)=A(x)B(x)$. Let $r_a$ and $r_b$ be the least common multiples of the denominators of all coefficients of $A(x)$ and $B(x)$ respectively. Then $\tilde a(x)=r_aA(x)$ and $\tilde b(x)=r_bB(x)$ are both polynomials over $R$. Let $r=r_ar_b$; then $rf(x)=\tilde a(x)\tilde b(x)$. If $r$ is a unit of $R$, we can take the factorization $f(x)=(r^{-1}\tilde a(x))\tilde b(x)$, which clearly satisfies the lemma.

    Otherwise, if $r$ has an irreducible factor $p$, we want to show that this factor can be cancelled from both sides while keeping all coefficients in the integral domain $R$. Note that $p$ must also be prime, so $(p)$ is a prime ideal. Taking both sides of the equation modulo $p$ gives the polynomial equation $0=\bar a(x)\bar b(x)$ over $(R/(p))[x]$, where $\bar a$ and $\bar b$ are the polynomials reduced modulo $p$. Since $R/(p)$ is an integral domain, $(R/(p))[x]$ is also an integral domain, so we may assume $\bar a(x)=0$. This shows that $p$ divides all coefficients of $\tilde a(x)$. So the factor $p$ can be cancelled directly from both sides.

    By the definition of a unique factorization domain, $r$ has at most finitely many such irreducible factors, so after cancelling them finitely many times we reach the case where $r$ is a unit of $R$. This proves the lemma.

???+ note "Corollary"
    Let $R$ be a unique factorization domain with field of fractions $F$. If $f(x)\in R[x]$ and the coefficients of $f(x)$ are coprime (that is, their greatest common divisor is the unity of $R$), then $f(x)$ is irreducible in $R[x]$ if and only if $f(x)$ is irreducible in $F[x]$.

In other words, the irreducible elements of the integer polynomial ring $\mathbf Z[x]$ are all irreducible elements of $\mathbf Q[x]$. An effective way to decide whether an integer polynomial is irreducible is Eisenstein's criterion. By Gauss's lemma, it also gives a way to decide whether a polynomial with rational coefficients is irreducible.

???+ note "Eisenstein's criterion"
    Let $f(x)=a_0+a_1x+\cdots+a_{n-1}x^{n-1}+a_nx^n$ be a polynomial of degree $n$ with integer coefficients. If there is a prime $p$ such that $p\mid a_i$ for all $i=0,1,\cdots,n-1$, $p$ does not divide $a_n$, and $p^2$ does not divide $a_0$, then $f(x)$ is irreducible over the field of rational numbers $\mathbf Q$. If moreover $\gcd(a_0,a_1,\cdots,a_n)=1$, then $f(x)$ is also irreducible over the ring of integers $\mathbf Z$.

??? note "Proof"
    By Gauss's lemma, if $f(x)$ is reducible over the field of rational numbers $\mathbf Q$, then it is also reducible over the ring of integers $\mathbf Z$. Let $f(x)=b(x)c(x)$ be its factorization in $\mathbf Z[x]$. Taking both sides modulo the prime $p$ gives a factorization in $\mathbf F_p[x]$: $\overline{f}(x)=\overline{b}(x)\overline{c}(x)$. But the conditions of the theorem say that $\overline{f}(x)=x^n$, so there must be an integer $m$ with $\overline b(x)=x^m$ and $\overline c(x)=x^{n-m}$, where $0<m<n$. So the constant terms $b_0$ and $c_0$ of the factors $b(x)$ and $c(x)$ are both multiples of $p$. Then the constant term $a_0=b_0c_0$ of $f(x)$ must be a multiple of $p^2$. This contradicts the given conditions.

??? example "Examples"
    1.  The polynomial $x^3-2$ is irreducible in $\mathbf Q[x]$. Just apply Eisenstein's criterion with $p=2$.
    2.  The polynomial $x^4+1$ is irreducible in $\mathbf Q[x]$. Otherwise, $(x+1)^4+1=x^4+4x^3+6x^2+4x+2$ would also be reducible. But applying Eisenstein's criterion with $p=2$ shows that the latter is irreducible.

For a unique factorization domain $R$, the polynomial ring over its field of fractions $F$ is a unique factorization domain, and Gauss's lemma shows that factorizations of polynomials over $F$ correspond to factorizations of polynomials over the original integral domain $R$. So $R[x]$ is also a unique factorization domain. This gives the following theorem:

???+ note "Theorem"
    The polynomial ring $R[x]$ is a unique factorization domain if and only if $R$ is a unique factorization domain.

Here $\mathbf Z[x]$ gives an example showing that a unique factorization domain is not necessarily a principal ideal domain. For example, in $\mathbf Z[x]$, $(2,x)$ is not a principal ideal.

There are many ways to extend a polynomial ring to a larger set. For example, the polynomial ring $R[x]$ over an integral domain can be extended to its field of fractions, written $R(x)$. This field of fractions is often called the **field of rational fractions**; its elements have the basic form $\dfrac{f(x)}{g(x)}$, where $f(x)$ and $g(x)$ are both polynomials.

### Multivariate polynomial rings

Polynomial rings can be generalized to the case of several indeterminates. For a commutative ring with unity $R$, we can define the polynomial ring over $R$, namely the univariate polynomial ring $R[x]$. Then we can define the polynomial ring $R[x][y]$ over $R[x]$, which can be seen as the bivariate polynomial ring $R[x,y]$ over $R$. In this way, we can inductively define the $k$-variate polynomial ring $R[x_1,\cdots,x_k]$ over $R$. When $R$ is an integral domain, every multivariate polynomial ring over it is an integral domain; similarly, the property of being a unique factorization domain also carries over to any multivariate polynomial ring.

### Formal power series rings

We can also allow formal sums with arbitrarily many nonzero coefficients. A **formal power series** over a commutative ring with unity $R$ is defined as

$$
\sum_{k=0}^\infty a_kx^k=a_0+a_1x+a_2x^2+\cdots.
$$

Addition and multiplication of power series can be defined in the same way as for the polynomial ring $R[x]$. Formal power series then also form a ring, written $R[[x]]$. We don't need to think about convergence of these formal power series, because each formal power series is really just its sequence of coefficients, with no extra topological structure.

The structure of formal power series rings is interesting. In a polynomial ring over an integral domain, the only units are constants. But in a formal power series ring, we can have

$$
(1-x)^{-1}=\sum_{k=0}^\infty x^k=1+x+x^2+\cdots.
$$

This happens in general. As long as the constant term $a_0$ of a formal power series is a unit in $R$, $\sum_{k=0}^\infty a_kx^k$ is also invertible. This is because if we set

$$
\left(\sum_{k=0}^\infty a_kx^k\right)\left(\sum_{k=0}^\infty b_kx^k\right)=1,
$$

then by writing down the system of equations the coefficients must satisfy, we can recursively find an expression for each $b_k$, which only involves the inverse of $a_0$.

Many operations can be defined on formal power series rings, such as inversion, division, compositional inverse, formal derivative and elementary functions. See [Introduction to polynomial techniques](../poly/intro.md) for details.

### Formal Laurent series rings

Formal power series rings can be extended further to allow terms of negative degree. A **formal Laurent series** over a commutative ring with unity $R$ is defined as

$$
\sum_{k=N}^\infty a_kx^k,
$$

where $N\in\mathbf Z$. So a formal Laurent series can have finitely many terms of negative degree. Extending the earlier addition and multiplication to formal Laurent series gives the formal Laurent series ring, written $R((x))$. If $F$ is a field, then $F((x))$ is also a field.

Formal Laurent series rings are used in [Lagrange inversion](../poly/lagrange-inversion.md).

## Chinese remainder theorem

Related reading: [Chinese remainder theorem](../number-theory/crt.md)

In number theory, the Chinese remainder theorem is commonly used to solve systems of congruences. The Chinese remainder theorem can also be established for general commutative rings with unity. Each congruence amounts to specifying the image of the unknown in some quotient ring, so the Chinese remainder theorem in a commutative ring with unity amounts to determining an element of the ring from its images in these quotient rings.

This discussion can be put in formal language. For a nonzero commutative ring with unity $R$ and ideals $I_1,\cdots,I_n$, consider the ring homomorphism $\varphi:R\rightarrow R/I_1\times \cdots\times R/I_n$ that maps $r$ to $(r+I_1,\cdots,r+I_n)$. Here $r+I_i$ is a coset, and $\times$ denotes the direct product of rings:

???+ abstract "Direct product"
    For rings $R_1$ and $R_2$, we can define multiplication on the direct product $R_1\times R_2$ of their additive groups by multiplying componentwise. Then $R_1\times R_2$ becomes a ring, called the **direct product** of $R_1$ and $R_2$, still written $R_1\times R_2$.

The kernel of the homomorphism $\varphi$ is $\ker\varphi=I_1\cap\cdots\cap I_n$. The question the Chinese remainder theorem answers is: under what conditions is this map surjective?

In number theory, the theorem requires the moduli to be pairwise coprime. This condition can be generalized to ring theory.

???+ abstract "Coprime ideals"
    Let $R$ be a ring with ideals $I$ and $J$. If $I+J=R$, then $I$ and $J$ are called **coprime** (comaximal).

For rings with unity, if we consider principal ideals $(a)$ and $(b)$, this condition is equivalent to the existence of $x,y\in R$ with $ax+by=1$, which is similar to Bézout's theorem for coprime integers. With this definition, we can establish the **Chinese remainder theorem** for commutative rings with unity, exactly imitating the case of the ring of integers.

???+ note "Chinese remainder theorem"
    Let $R$ be a nonzero commutative ring with unity with ideals $I_1,\cdots,I_n$. If they are pairwise coprime, then the ring homomorphism $\varphi$ defined above is surjective, and its kernel equals the product of these ideals, $\ker\varphi=I_1\cap\cdots\cap I_n=I_1\cdots I_n$. Therefore,

    $$
    R/(I_1\cdots I_n)=R/(I_1\cap\cdots\cap I_n)\cong R/I_1\times\cdots\times R/I_n.
    $$

??? note "Proof"
    The theorem says a lot, but only two claims still need proof: $\varphi$ is surjective, and $I_1\cap\cdots\cap I_n=I_1\cdots I_n$. The key is to make good use of the coprimality condition.

    First, prove the case $n=2$. Since the ideals $I_1$ and $I_2$ are coprime, that is, $I_1+I_2=R$, the unity $1$ of $R$ can be written as $a_1+a_2$ with $a_i\in I_i$. Since $a_1\in I_1$ and $a_1=1-a_2\in 1+I_2$, we have $\varphi(a_1)=(I_1,1+I_2)$; similarly, $\varphi(a_2)=(1+I_1,I_2)$. So $(\varphi(a_2),\varphi(a_1))$ plays a role similar to a "basis" in a vector space. Therefore, for any image $(r_1+I_1,r_2+I_2)$, we can find its preimage $r_1a_2+r_2a_1$ under $\varphi$. This shows that $\varphi$ is surjective.

    We still need to prove that $I_1\cap I_2=I_1I_2$. In a general ring, $I_1I_2\subseteq I_1\cap I_2$ always holds; the key is the reverse inclusion. For any $r\in I_1\cap I_2$, we have $r=r(a_1+a_2)=ra_1+ra_2\in I_1I_2$. So $I_1\cap I_2\subseteq I_1I_2$ also holds. This proves the claim.

    For $n>2$, we use mathematical induction. The key to the induction step is to prove that for pairwise coprime ideals $I_1,\cdots,I_n$, the ideals $I_1$ and $I_2\cdots I_n$ are always coprime. Since $I_1$ is coprime to each of $I_2,\cdots,I_n$, for each $i=2,\cdots,n$ there exist $a_i\in I_1$ and $b_i\in I_i$ with $1=a_i+b_i$. So $1=(a_2+b_2)\cdots(a_n+b_n)$. Hence $1\in (b_2\cdots b_n)+I_1\subseteq I_1+(I_2\cdots I_n)$. This shows that the ideals $I_1$ and $I_2\cdots I_n$ are coprime.

### Application: Lagrange interpolation formula

Related reading: [Lagrange interpolation](../numerical/interp.md#lagrange-interpolation), [Fast polynomial interpolation](../poly/multipoint-eval-interpolation.md#fast-polynomial-interpolation)

The interpolation problem is: given a set of point values $\{(x_i,y_i)\}_{i=1}^n$, find a polynomial $f(x)$ over a field $F$ such that $f(x_i)=y_i$ for all $i=1,\cdots,n$. Of course, we assume all $x_i$ are distinct. The Lagrange interpolation formula gives the general solution to this kind of problem.

For a polynomial $f(x)$ over a field $F$, the condition $f(x_i)=y_i$ is equivalent to $x_i$ being a root of the polynomial $f(x)-y_i$, which is equivalent to $(x-x_i)\mid(f(x)-y_i)$, that is, $f(x)\equiv y_i\pmod{x-x_i}$. So the interpolation problem is equivalent to solving the system of congruences

$$
\begin{cases}
f(x)\equiv y_1&\pmod{x-x_1},\\
f(x)\equiv y_2&\pmod{x-x_2},\\
\cdots\\
f(x)\equiv y_n&\pmod{x-x_n}.
\end{cases}
$$

The linear polynomials $\{x-x_i\}_{i=1}^n$ are pairwise coprime. By the Chinese remainder theorem, the solution should have the form

$$
f(x)=\sum_{i=1}^ny_iM_i(x),
$$

where $M_i(x)=m_i(x)\prod_{j\neq i}(x-x_j)$ and $M_i(x)\equiv 1\pmod{x-x_i}$. By the equivalence derived above, this is equivalent to $M_i(x_i)=1$, that is,

$$
m_i(x_i)\prod_{j\neq i}(x_i-x_j) = 1.
$$

We can take $m_i(x)$ to be a constant polynomial, namely

$$
m_i(x) = \frac{1}{\prod_{j\neq i}(x_i-x_j)}.
$$

This gives the Lagrange interpolation formula

$$
f(x)=\sum_{i=1}^ny_i\frac{\prod_{j\neq i}(x-x_j)}{\prod_{j\neq i}(x_i-x_j)}.
$$

In general, extending this method also leads to the [Hermite interpolation formula](https://en.wikipedia.org/wiki/Hermite_interpolation), which also allows fixing the values of several derivatives of the polynomial at each point.

### Application: the multiplicative group of integers modulo n

Related reading: [Primitive roots](../number-theory/primitive-root.md), [Fundamental theorem of finitely generated Abelian groups](./group-theory.md#classification-theorem)

As an application of the Chinese remainder theorem and group theory, here we discuss the structure of the multiplicative group of integers modulo $n$. In this section, we drop the bar notation for residue classes.

The **multiplicative group of integers modulo $n$** is $(\mathbf Z/n\mathbf Z)^\times$, the multiplicative group of the units of the quotient ring $\mathbf Z/n\mathbf Z$ (also called the unit group). The order of $(\mathbf Z/n\mathbf Z)^\times$ is $\varphi(n)$, since an element has an inverse if and only if it is coprime to $n$. Here $\varphi(n)$ is [Euler's totient function](../number-theory/euler-totient.md). Moreover, $(\mathbf Z/n\mathbf Z)^\times$ is always an Abelian group.

By the fundamental theorem of arithmetic, the modulus $n$ can be factored into a product of powers of distinct primes:

$$
n=p_1^{\alpha_1}\cdots p_s^{\alpha_s}.
$$

It is easy to check that for ideals of the ring of integers, the ideals being coprime is equivalent to their generators being coprime. So applying the Chinese remainder theorem gives

$$
\mathbf Z/n\mathbf Z\cong\mathbf Z/p_1^{\alpha_1}\mathbf Z\times\cdots\times\mathbf Z/p_s^{\alpha_s}\mathbf Z.
$$

An isomorphism of rings means the corresponding multiplicative structures are also isomorphic, so

$$
(\mathbf Z/n\mathbf Z)^\times\cong(\mathbf Z/p_1^{\alpha_1}\mathbf Z)^\times\times\cdots\times(\mathbf Z/p_s^{\alpha_s}\mathbf Z)^\times.
$$

This shows that $\varphi(n)=\varphi(p_1^{\alpha_1})\cdots\varphi(p_s^{\alpha_s})$, that is, Euler's totient function is multiplicative.

So to study a general modulus, it is enough to consider prime powers $p^k$ as the modulus. For prime powers, we need to consider two cases separately: $p=2$ and $p$ an odd prime:

-   For $p=2$, direct checking shows that $(\mathbf Z/2\mathbf Z)^\times\cong C_1$ and $(\mathbf Z/4\mathbf Z)^\times\cong C_2$. For $k\ge3$, we have $(\mathbf Z/2^k\mathbf Z)^\times\cong C_2\times C_{2^{k-2}}$.

    ??? note "Proof"
        Direct computation with the binomial theorem shows that

        $$
        \begin{aligned}
        5^{2^{k-2}}=(1+2^2)^{2^{k-2}}&\equiv 1\pmod {2^k},\\
        5^{2^{k-3}}=(1+2^2)^{2^{k-3}}&\equiv 1+2^{k-1}\pmod {2^k}.
        \end{aligned}
        $$

        So $5$ is an element of order $2^{k-2}$ in $(\mathbf Z/2^k\mathbf Z)^\times$. Also, $-1$ and $5^{2^{k-3}}$ are two different elements of order two, so $-1\notin\langle 5\rangle$. So $\langle-1\rangle$ and $\langle 5\rangle$ have trivial intersection, and by the characterization of direct products of groups,

        $$
        (\mathbf Z/2^k\mathbf Z)^\times\cong\langle-1\rangle\times\langle 5\rangle\cong C_2\times C_{2^{k-2}}.
        $$
-   For $p$ an odd prime, one can prove that $(\mathbf Z/p^k\mathbf Z)^\times$ is isomorphic to the cyclic group $C_{\varphi(p^k)}$.

    ??? note "Proof"
        To prove that $(\mathbf Z/p^k\mathbf Z)^\times$ is cyclic, by the fundamental theorem of finite Abelian groups it is enough to prove that each of its Sylow $q$‑subgroups is cyclic. First, for the Sylow $p$‑subgroup, direct computation shows that

        $$
        \begin{aligned}
        (1+p)^{p^{k-1}} &\equiv 1\pmod{p^k},\\
        (1+p)^{p^{k-2}} &\equiv 1+p^{k-1}\pmod{p^k}.
        \end{aligned}
        $$

        So $(1+p)$ is an element of order $p^{k-1}$. That is, the unique Sylow $p$‑subgroup of $(\mathbf Z/p^k\mathbf Z)^\times$ is the cyclic group $\langle 1+p\rangle$.

        For the other Sylow $q$‑subgroups ($q\neq p$), we can reduce to the case $k=1$ through a group homomorphism. Consider the group homomorphism $\varphi:(\mathbf Z/p^k\mathbf Z)^\times\rightarrow(\mathbf Z/p\mathbf Z)^\times$, which maps the coset $r+p^k\mathbf Z$ to the coset $r+p\mathbf Z$. The kernel of this map has size $p^{k-1}$, so when $\varphi$ is restricted to a Sylow $q$‑subgroup ($q\neq p$) of $(\mathbf Z/p^k\mathbf Z)^\times$, the kernel of the restricted map is trivial. So this Sylow $q$‑subgroup is isomorphic to its image, which is a Sylow $q$‑subgroup of $(\mathbf Z/p\mathbf Z)^\times$. Therefore, it is enough to prove that the Sylow $q$‑subgroups of $(\mathbf Z/p\mathbf Z)^\times$ are all cyclic.

        Finally, we prove that the Sylow $q$‑subgroups of $(\mathbf Z/p\mathbf Z)^\times$ are all cyclic. Since $(\mathbf Z/p\mathbf Z)^\times$ is a finite Abelian group, we can decompose it by invariant factors as

        $$
        C_{n_1}\times\cdots\times C_{n_r}.
        $$

        Here $n_1\mid n_2\mid \cdots \mid n_r$. So each direct factor has $n_1$ elements whose order divides $n_1$. If $r>1$, then strictly more than $n_1$ elements satisfy the equation $x^{n_1}=1$. But $\mathbf Z/p\mathbf Z$ is a field, and a polynomial of degree $n_1$ over a field has at most $n_1$ roots, so $r=1$. That is, $(\mathbf Z/p\mathbf Z)^\times\cong C_{p-1}$.

        This proves that $(\mathbf Z/p^k\mathbf Z)^\times\cong C_{p^{k-1}}\times C_{p-1}\cong C_{\varphi(p^{k})}$.

The structure of the multiplicative group for a general modulus then follows. From these results, we know that the multiplicative group of integers modulo $n$ is cyclic if and only if the modulus $n$ is

$$
1,2,4,p^k,2p^k
$$

where $p$ is an odd prime; otherwise, the multiplicative group of integers modulo $n$ must contain a subgroup $C_2\times C_2$, so it cannot be cyclic. When the multiplicative group is cyclic, its generators are called **primitive roots** modulo $n$. So the theorem here gives exactly the necessary and sufficient condition for primitive roots to exist.

Of course, analyzing the structure of the multiplicative group gives more information than just the condition for primitive roots to exist. It clearly shows the orders of different elements of the multiplicative group. In $(\mathbf Z/n\mathbf Z)^\times$, an element $x$ with $x^k=1$, that is, a solution of the congruence $x^k\equiv 1\pmod n$, is called a **$k$-th root of unity modulo $n$**; an element of order exactly $k$ is called a **primitive $k$-th root of unity modulo $n$**. Using the structure of the multiplicative group, the existence and number of these roots of unity can be computed exactly. Finally, the least common multiple of the orders of all elements of $(\mathbf Z/n\mathbf Z)^\times$, that is, the smallest positive integer $k$ with $x^k=1$ for all $x\in (\mathbf Z/n\mathbf Z)^\times$, viewed as a function of $n$, is the [Carmichael function](../number-theory/primitive-root.md#carmichael-function). Its many properties can all be derived from the structure of the multiplicative group.

## References and notes

-   Dummit, D.S. and Foote, R.M. (2004) Abstract Algebra. 3rd Edition, John Wiley & Sons, Inc.
-   [Quadratic integer - Wikipedia](https://en.wikipedia.org/wiki/Quadratic_integer)
-   [Formal power series - Wikipedia](https://en.wikipedia.org/wiki/Formal_power_series)
-   [Multiplicative group of integers modulo $n$- Wikipedia](https://en.wikipedia.org/wiki/Multiplicative_group_of_integers_modulo_n)

[^ideal-history]: <https://en.wikipedia.org/wiki/Ideal_(ring_theory)#History>

[^simple-ring]: As with groups, such a ring is called a **simple ring**. A commutative simple ring must be a field; the noncommutative case is much more complicated.

[^gcd-domain]: An integral domain in which greatest common divisors exist is called a [GCD domain](https://en.wikipedia.org/wiki/GCD_domain).

[^ring-theory-history]: A brief history of ring theory can be found [here](https://mathshistory.st-andrews.ac.uk/HistTopics/Ring_theory/).
