This page gives a short introduction to the basics of number theory.

## Divisibility

???+ note "Definition"
    Let $a,b\in\mathbf{Z}$ with $a\ne 0$. If $\exists q\in\mathbf{Z}$ such that $b=aq$, we say $b$ is **divisible** by $a$, written $a\mid b$. If $b$ is not divisible by $a$, we write $a\nmid b$.

Properties of divisibility:

-   $a\mid b\iff-a\mid b\iff a\mid-b\iff|a|\mid|b|$
-   $a\mid b\land b\mid c\implies a\mid c$
-   $a\mid b\land a\mid c\iff\forall x,y\in\mathbf{Z}, a\mid(xb+yc)$
-   $a\mid b\land b\mid a\implies b=\pm a$
-   If $m\ne0$, then $a\mid b\iff ma\mid mb$.
-   If $b\ne0$, then $a\mid b\implies|a|\le|b|$.
-   If $a\ne0,b=qa+c$, then $a\mid b\iff a\mid c$.

### Divisors

???+ note "Definition"
    If $a\mid b$, we call $b$ a **multiple** of $a$, and $a$ a **divisor** of $b$.

$0$ is a multiple of every nonzero integer. An integer $b\ne0$ has only finitely many divisors.

Trivial divisors (trivial factors): for an integer $b\ne0$, $\pm1$ and $\pm b$ are the trivial divisors of $b$. When $b=\pm1$, $b$ has only two trivial divisors.

For an integer $b\ne 0$, the other divisors of $b$ are called proper divisors (also proper factors, nontrivial divisors, or nontrivial factors).

Properties of divisors:

-   Let $b\ne0$ be an integer. As $d$ runs over all divisors of $b$, $\dfrac{b}{d}$ also runs over all divisors of $b$.
-   Let $b\gt 0$ be an integer. As $d$ runs over all positive divisors of $b$, $\dfrac{b}{d}$ also runs over all positive divisors of $b$.

In concrete problems, **unless stated otherwise, "divisor" always means a positive divisor.**

## Division with remainder

???+ note "Remainder"
    Let $a,b$ be two given integers with $a\ne0$, and let $d$ be a given integer. Then there is exactly one pair of integers $q$ and $r$ such that $b=qa+r,d\le r<|a|+d$.

Whatever the value of the integer $d$, $r$ is called a remainder. $a\mid b$ is equivalent to $a\mid r$.

Usually we take $d=0$. The equation $b=qa+r,0\le r<|a|$ is then called division with remainder. The remainder $r$ here is called the least nonnegative remainder.

Two other common choices of remainder are:

-   Absolute least remainder: take $d$ to be minus half the absolute value of $a$. That is, $b=qa+r,-\dfrac{|a|}{2}\le r<|a|-\dfrac{|a|}{2}$.
-   Least positive remainder: take $d=1$. That is, $b=qa+r,1\le r<|a|+1$.

The remainder in division with remainder is only the least nonnegative remainder. **Unless stated otherwise, "remainder" always means the least nonnegative remainder.**

Properties of remainders:

-   When any integer is divided by a positive integer $a$, the remainder is exactly one of the $a$ numbers $0$ to $(a-1)$.
-   When $a$ consecutive integers are divided by a positive integer $a$, they give exactly the $a$ remainders above. In particular, exactly one of them is divisible by $a$.

## Greatest common divisor and least common multiple

For the definitions of the four terms common divisor, common multiple, greatest common divisor and least common multiple, see [Greatest Common Divisor](./gcd.md).

???+ warning "Warning"
    Some authors say the greatest common divisor of $0$ and $0$ is undefined; others usually take it to be $0$. The C++ STL implementation uses the latter, that is, the greatest common divisor of $0$ and $0$ is $0$[^gcdcpp].

The greatest common divisor has the following properties:

-   $(a_1,\dots,a_n)=(|a_1|,\dots,|a_n|)$;
-   $(a,b)=(b,a)$;
-   if $a\ne 0$, then $(a,0)=(a,a)=|a|$;
-   $(bq+r,b)=(r,b)$;
-   $(a_1,\dots,a_n)=((a_1,a_2),a_3,\dots,a_n)$. Furthermore, $\forall 1<k<n-1,~(a_1,\dots,a_n)=((a_1,\dots,a_k),(a_{k+1},\dots,a_n))$;
-   for integers $a_1,\dots,a_n$ that are not all $0$ and a nonzero integer $m$, $(ma_1,\dots,ma_n)=|m|(a_1,\dots,a_n)$;
-   for integers $a_1,\dots,a_n$ that are not all $0$, if $(a_1,\dots,a_n)=d$, then $(a_1/d,\dots,a_n/d)=1$;
-   $(a^n,b^n)=(a,b)^n$.

The greatest common divisor also has the following properties related to coprimality:

-   if $b|ac$ and $(a,b)=1$, then $b\mid c$;
-   if $b|c$, $a|c$ and $(a,b)=1$, then $ab\mid c$;
-   if $(a,b)=1$, then $(a,bc)=(a,c)$;
-   if $(a_i,b_j)=1,~\forall 1\leq i\leq n,1\leq j\leq m$, then $\left(\prod_i a_i,\prod_j b_j\right)=1$. In particular, if $(a,b)=1$, then $(a^n,b^m)=1$;
-   for integers $a_1,\dots,a_n$, if $\exists v\in \mathbf{Z},~\prod_i a_i=v^m$ and $(a_i,a_j)=1,~\forall i\ne j$, then $\forall 1\leq i\leq n,~\sqrt[m]{a_i}\in\mathbf{Z}$.

The least common multiple has the following properties:

-   $[a_1,\dots,a_n]=[|a_1|,\dots,|a_n|]$;
-   $[a,b]=[b,a]$;
-   if $a\ne 0$, then $[a,1]=[a,a]=|a|$;
-   if $a\mid b$, then $[a,b]=|b|$;
-   $[a_1,\dots,a_n]=[[a_1,a_2],a_3,\dots,a_n]$. Furthermore, $\forall 1<k<n-1,~[a_1,\dots,a_n]=[[a_1,\dots,a_k],[a_{k+1},\dots,a_n]]$;
-   if $a_i\mid m,~\forall 1\leq i\leq n$, then $[a_1,\dots,a_n]\mid m$;
-   $[ma_1,\dots,ma_n]=|m|[a_1,\dots,a_n]$;
-   $[a,b,c][ab,bc,ca]=[a,b][b,c][c,a]$;
-   $[a^n,b^n]=[a,b]^n$.

The greatest common divisor and least common multiple combine into many neat identities, such as:

-   $(a,b)[a,b]=|ab|$;
-   $(ab,bc,ca)[a,b,c]=|abc|$;
-   $\dfrac{(a,b,c)^2}{(a,b)(b,c)(a,c)}=\dfrac{[a,b,c]^2}{[a,b][b,c][a,c]}$.

All of these properties can be proved from the definitions or with the [unique factorization theorem](#fundamental-theorem-of-arithmetic). The proofs using unique factorization are easier to understand.

### Coprime integers

???+ note "Definition"
    If $(a_1,a_2)=1$, we say $a_1$ and $a_2$ are **coprime** (**relatively prime**).
    
    If $(a_1,\ldots,a_k)=1$, we say $a_1,\ldots,a_k$ are **coprime** (**relatively prime**).

Several integers being coprime does not mean they are pairwise coprime. For example, $6$, $10$ and $15$ are coprime, but no two of them are coprime.

For properties of coprimality and the theory of greatest common divisors, see Bézout's identity: [Bézout's Identity](./bezouts.md).

### Euclidean algorithm

The Euclidean algorithm (repeated division) is an algorithm, also called Euclid's algorithm. See [Greatest Common Divisor](./gcd.md).

## Primes and composites

For algorithms on primes, see [Primes](./prime.md).

???+ note "Definition"
    Let $p\ne0,\pm1$ be an integer. If $p$ has no divisors other than its trivial divisors, we call $p$ a **prime** (**irreducible**).
    
    If an integer $a\ne0,\pm 1$ is not prime, we call $a$ a **composite**.

$p$ and $-p$ are always both prime or both composite. **Unless stated otherwise, "prime" always means a positive prime.**

If a divisor of an integer is prime, that prime is called a prime factor (prime divisor) of the integer.

Simple properties of primes and composites:

-   An integer $a$ greater than $1$ is composite if and only if $a$ can be written as a product of integers $d$ and $e$ ($1<d,e<a$).
-   If a prime $p$ has a divisor $d$ greater than $1$, then $d=p$.
-   Every integer $a$ greater than $1$ can be written as a product of primes.
-   For a composite $a$, there is always a prime $p\le\sqrt{a}$ with $p\mid a$.
-   There are infinitely many primes.
-   Every prime greater than $3$ can be written in the form $6n\pm 1$[^ref1].

## Fundamental theorem of arithmetic

???+ note "Fundamental lemma of arithmetic"
    Let $p$ be a prime with $p\mid a_1a_2$. Then at least one of $p\mid a_1$ and $p\mid a_2$ holds.

With a small change, the converse of the fundamental lemma of arithmetic gives another definition of primes.

???+ note "Another definition of primes"
    For an integer $p\ne 0,\pm 1$, if $p\mid a_1$ or $p\mid a_2$ holds for all integers $a_1,a_2$ with $p\mid a_1a_2$, we call $p$ a prime.

??? tip "Tip"
    The motivation for this definition comes from [prime ideals](../algebra/ring-theory.md#素理想).

???+ note "Fundamental theorem of arithmetic (unique factorization theorem)"
    Every positive integer $a$ can be written as
    
    $$
    a=p_1p_2\cdots p_s
    $$
    
    where each $p_j(1\le j\le s)$ is prime. Moreover, this representation is unique up to the order of the factors.

???+ note "Standard prime factorization"
    Grouping equal primes in the representation above gives
    
    $$
    a={p_1}^{\alpha_1}{p_2}^{\alpha_2}\cdots{p_s}^{\alpha_s},p_1<p_2<\cdots<p_s
    $$
    
    which is called the standard prime factorization of the positive integer $a$.

The fundamental theorem of arithmetic and the fundamental lemma of arithmetic are equivalent.

## Congruence

???+ note "Definition"
    Let $m\ne0$ be an integer. If $m\mid(a-b)$, we call $m$ the **modulus**, say that $a$ is congruent to $b$ modulo $m$, and call $b$ a **residue** of $a$ modulo $m$. We write $a\equiv b\pmod m$.
    
    Otherwise, $a$ is not congruent to $b$ modulo $m$, and $b$ is not a residue of $a$ modulo $m$. We write $a\not\equiv b\pmod m$.
    
    Such a relation is called a congruence modulo $m$, or simply a **congruence**.

By the properties of divisibility, the congruence above is also equivalent to $a\equiv b\pmod{(-m)}$.

From here on, unless stated otherwise, the modulus is always a **positive integer**.

Here $b$ is a residue of $a$ modulo $m$, and this concept is exactly the same as the remainder. By restricting the range of $b$, we get the least nonnegative residue, the absolute least residue and the least positive residue of $a$ modulo $m$.

Properties of congruence:

-   Congruence is an [equivalence relation](../order-theory.md#二元关系), that is, congruence is
    -   Reflexive: $a\equiv a\pmod m$.
    -   Symmetric: if $a\equiv b\pmod m$, then $b\equiv a\pmod m$.
    -   Transitive: if $a\equiv b\pmod m,b\equiv c\pmod m$, then $a\equiv c\pmod m$.
-   Linear operations: if $a,b,c,d\in\mathbf{Z},m\in\mathbf{N}^*,a\equiv b\pmod m,c\equiv d\pmod m$, then:
    -   $a\pm c\equiv b\pm d\pmod m$.
    -   $a\times c\equiv b\times d\pmod m$.
-   Let $f(x)=\sum_{i=0}^n a_ix^i$ and $g(x)=\sum_{i=0}^n b_ix^i$ be two polynomials with integer coefficients, $m\in\mathbf{N}^*$, and $a_i\equiv b_i\pmod m,~0\leq i\leq n$. Then $f(x)\equiv g(x)\pmod m$ for every integer $x$. Furthermore, if $s\equiv t\pmod m$, then $f(s)\equiv g(t)\pmod m$.
-   If $a,b\in\mathbf{Z},k,m\in\mathbf{N}^*,a\equiv b\pmod m$, then $ak\equiv bk\pmod{mk}$.
-   If $a,b\in\mathbf{Z},d,m\in\mathbf{N}^*,d\mid a,d\mid b,d\mid m$, then whenever $a\equiv b\pmod m$ holds, we have $\dfrac{a}{d}\equiv\dfrac{b}{d}\left(\bmod\;{\dfrac{m}{d}}\right)$.
-   If $a,b\in\mathbf{Z},d,m\in\mathbf{N}^*,d\mid m$, then whenever $a\equiv b\pmod m$ holds, we have $a\equiv b\pmod d$.
-   If $a,b\in\mathbf{Z},d,m\in\mathbf{N}^*$, then whenever $a\equiv b\pmod m$ holds, we have $(a,m)=(b,m)$. If $d$ divides $m$ and one of $a,b$, then $d$ must also divide the other one.

Another property is the modular multiplicative inverse. See [Modular Inverse](./inverse.md).

## Residue classes and residue systems

For convenience, for sets $A,B$ and an element $r$, we introduce the following notation:

-   $r+A:=\{r+a:a\in A\}$;
-   $rA:=\{ra:a\in A\}$;
-   $A+B:=\{a+b:a\in A,b\in B\}$;
-   $AB:=\{ab:a\in A,b\in B\}$.

???+ note "Residue class"
    For a nonzero integer $m$, split all integers into $|m|$ pairwise disjoint sets so that any two numbers in the same set are congruent modulo $m$. Each of these $|m|$ sets is called a **congruence class** or **residue class** modulo $m$. We write $r\bmod m$ for the residue class modulo $m$ that contains the integer $r$.
    
    It is not hard to prove that for every nonzero integer $m$, such a partition exists and is unique.

From the definition of residue classes:

-   $r\bmod m=\{r+km:k\in\mathbf{Z}\}$;
-   $r\bmod m=s\bmod m\iff r\equiv s\pmod m$;
-   for any $r,s\in\mathbf{Z}$, either $r\bmod m=s\bmod m$ or $(r\bmod m)\cap (s\bmod m)=\varnothing$;
-   if $m_1\mid m$, then $r+m\mathbf{Z}\subseteq r+m_1\mathbf{Z}$ for every integer $r$.

Since congruence is an equivalence relation, residue classes are exactly the equivalence classes of the congruence relation.

We write $\mathbf{Z}_m$ for the set of all residue classes modulo $m$, that is

$$
\mathbf{Z}_m:=\{r\bmod m:0\leq r<m\}
$$

It is easy to see that:

-   for any integer $a$, $a+\mathbf{Z}_m=\mathbf{Z}_m$;
-   for any integer $b$ coprime to $m$, $b\mathbf{Z}_m=\mathbf{Z}_m$.

By the definition of a [quotient group](../algebra/group-theory.md#商群), $\mathbf{Z}_m=\mathbf{Z}/m\mathbf{Z}$, so we sometimes also write $\mathbf{Z}/m\mathbf{Z}$ for $\mathbf{Z}_m$.

By the [pigeonhole principle](../combinatorics/drawer-principle.md):

-   Among any $m+1$ integers, two of them are congruent modulo $m$.
-   There exist $m$ integers that are pairwise incongruent modulo $m$.

This leads to the definition of a complete residue system:

???+ note "(Complete) residue system"
    For $m$ integers $a_1,a_2,\dots,a_m$, if for every number $x$ there is exactly one $a_i$ with $x$ congruent to $a_i$ modulo $m$, then the $m$ integers $a_1,a_2,\dots,a_m$ are called a **complete residue system** modulo $m$, or simply a **residue system**.

We can also define the following systems modulo $m$:

-   least nonnegative (complete) residue system: $0,\dots,m-1$;
-   least positive (complete) residue system: $1,\dots,m$;
-   absolute least (complete) residue system: $-\lfloor m/2\rfloor,\dots,-\lfloor -m/2\rfloor-1$;
-   greatest nonpositive (complete) residue system: $-m+1,\dots,0$;
-   greatest negative (complete) residue system: $-m,\dots,-1$.

Unless stated otherwise, we usually use only the least nonnegative residue system.

Note that the following statement holds:

-   In any residue class modulo $m$, any two integers $a_1,a_2$ satisfy $(a_1,m)=(a_2,m)$.

Consider the residue class $r\bmod m$. If $(r,m)=1$, then every element of this class is coprime to $m$. This suggests that we may be able to understand the structure of the set of all integers coprime to $m$ in a similar way.

???+ note "Reduced residue class"
    For a residue class $r\bmod m$, if $(r,m)=1$, we call it a **reduced congruence class** or **reduced residue class**.
    
    We write $\varphi(m)$ for the number of reduced residue classes modulo $m$, and call it [Euler's totient function](./euler-totient.md).

We write $\mathbf{Z}_m^*$ for the set of all reduced residue classes modulo $m$, that is

$$
\mathbf{Z}_m^*:=\{r\bmod m:0\leq r<m,(r,m)=1\}
$$

???+ warning "Warning"
    For any integer $a$ and any integer $b$ coprime to $m$, $b\mathbf{Z}_m^*=\mathbf{Z}_m^*$, but $a+\mathbf{Z}_m^*$ is not necessarily $\mathbf{Z}_m^*$. This is different from $\mathbf{Z}_m$.

By the [pigeonhole principle](../combinatorics/drawer-principle.md):

-   Among any $\varphi(m)+1$ integers coprime to $m$, two of them are congruent modulo $m$.
-   There exist $\varphi(m)$ integers that are coprime to $m$ and pairwise incongruent modulo $m$.

This leads to the definition of a reduced residue system:

???+ note "Reduced residue system"
    For $t=\varphi(m)$ integers $a_1,a_2,\dots,a_t$, if $(a_i,m)=1,~\forall 1\leq i\leq t$, and for every number $x$ with $(x,m)=1$ there is exactly one $a_i$ with $x$ congruent to $a_i$ modulo $m$, then the $t$ integers $a_1,a_2,\dots,a_t$ are called a **reduced residue system**, **reduced system of residues** or **simplified residue system** modulo $m$.

In the same way, we can define the least nonnegative reduced residue system and similar concepts.

Unless stated otherwise, we usually use only the least nonnegative reduced residue system.

### Combining residue systems

For a positive integer $m$, we have the following theorem:

-   If $m=m_1m_2,~1\leq m_1,m_2$, and $Z_{m_1},Z_{m_2}$ are **complete** residue systems modulo $m_1,m_2$ respectively, then for every $a$ coprime to $m_1$:

    $$
    Z_m=aZ_{m_1}+m_1Z_{m_2}.
    $$

    is a **complete** residue system modulo $m$. Furthermore, if $m=\prod_{i=1}^k m_i,~1\leq m_1,m_2,\dots,m_k$, and $Z_{m_1},\dots,Z_{m_k}$ are **complete** residue systems modulo $m_1,\dots,m_k$ respectively, then:

    $$
    Z_m=\sum_{i=1}^k\left(\prod_{j=1}^{i-1}m_j\right)Z_{m_i}.
    $$

    is a **complete** residue system modulo $m$.

???+ note "Proof"
    We only need to show that for any $x,x'\in Z_{m_1}$, $y,y'\in Z_{m_2}$ with $ax+m_1y\equiv ax'+m_1y'\pmod{m_1m_2}$, we have:
    
    $$
    ax+m_1y=ax'+m_1y'.
    $$
    
    Indeed, since $m_1\mid m_1m_2$, we have $ax+m_1y\equiv ax'+m_1y'\pmod{m_1}$, so $ax\equiv ax'\pmod{m_1}$. Since $(a,m_1)=1$, we get $x\equiv x'\pmod{m_1}$, and therefore $x=x'$.
    
    Next, $m_1y\equiv m_1y'\pmod{m_1m_2}$, so $y\equiv y'\pmod{m_2}$, that is, $y=y'$.
    
    Therefore,
    
    $$
    ax+m_1y=ax'+m_1y'.
    $$

-   If $m=m_1m_2,~1\leq m_1,m_2,(m_1,m_2)=1$, and $Z_{m_1}^*,Z_{m_2}^*$ are **reduced** residue systems modulo $m_1,m_2$ respectively, then:

    $$
    Z_m^*=m_2Z_{m_1}^*+m_1Z_{m_2}^*.
    $$

    is a **reduced** residue system modulo $m$.

???+ tip "Tip"
    This theorem is equivalent to the statement that Euler's totient function is [multiplicative](#multiplicative-functions).

???+ note "Proof"
    Let $Z_{m_1},Z_{m_2}$ be complete residue systems modulo $m_1,m_2$ respectively. We have already proved that
    
    $$
    Z_m=m_2Z_{m_1}+m_1Z_{m_2}
    $$
    
    is a complete residue system modulo $m$. Let $M=\{a\in Z_m:(a,m)=1\}\subseteq Z_m$. Clearly $M$ is a reduced residue system modulo $m$, so we only need to prove $M=Z_m^*$.
    
    Clearly $Z_m^*\subseteq Z_m$.
    
    Take any $m_2x+m_1y\in M$, where $x\in Z_{m_1}$ and $y\in Z_{m_2}$. Then $(m_2x+m_1y,m_1m_2)=1$. Since $(m_1,m_2)=1$, we get
    
    $$
    1=(m_2x+m_1y,m_1)=(m_2x,m_1)=(x,m_1),
    $$
    
    $$
    1=(m_2x+m_1y,m_2)=(m_1y,m_2)=(y,m_2).
    $$
    
    Hence $x\in Z_{m_1}^*$ and $y\in Z_{m_2}^*$, that is, $M\subseteq Z_m^*$.
    
    Take any $m_2x+m_1y\in Z_m^*$, where $x\in Z_{m_1}^*$ and $y\in Z_{m_2}^*$. Then $(x,m_1)=1$ and $(y,m_2)=1$. Since $(m_1,m_2)=1$, we get
    
    $$
    (m_2x+m_1y,m_1)=(m_2x,m_1)=(x,m_1)=1,
    $$
    
    $$
    (m_2x+m_1y,m_2)=(m_1y,m_2)=(x,m_2)=1,
    $$
    
    Hence $(m_2x+m_1y,m_1m_2)=1$, that is, $Z_m^*\subseteq M$.
    
    Putting it all together,
    
    $$
    Z_m^*=m_2Z_{m_1}^*+m_1Z_{m_2}^*.
    $$
    
    is a **reduced** residue system modulo $m$.

## Arithmetic functions

An arithmetic function (also called a number-theoretic function) is a function whose domain is the positive integers. An arithmetic function can also be seen as a sequence.

### Multiplicative functions

???+ note "Definition"
    In number theory, if a function $f(n)$ satisfies $f(1)=1$, and $f(xy)=f(x)f(y)$ holds for all coprime $x, y \in\mathbf{N}^*$, then $f(n)$ is a **multiplicative function**.
    
    In number theory, if a function $f(n)$ satisfies $f(1)=1$ and $f(xy)=f(x)f(y)$ holds for all $x, y \in\mathbf{N}^*$, then $f(n)$ is a **completely multiplicative function**.

#### Properties

If $f(x)$ and $g(x)$ are both multiplicative, then the following functions are also multiplicative:

$$
\begin{aligned}
h(x)&=f(x^p)\\
h(x)&=f^p(x)\\
h(x)&=f(x)g(x)\\
h(x)&=\sum_{d\mid x}f(d)g\left(\dfrac{x}{d}\right)
\end{aligned}
$$

For a positive integer $x$, let its unique prime factorization be $x=\prod p_i^{k_i}$, where the $p_i$ are primes.

If $F(x)$ is multiplicative, then $F(x)=\prod F(p_i^{k_i})$.

If $F(x)$ is completely multiplicative, then $F(x)=\prod F(p_i^{k_i})=\prod F(p_i)^{k_i}$.

#### Examples

-   Unit function: $\varepsilon(n)=[n=1]$. (completely multiplicative)
-   Power function: $\operatorname{id}_k(n)=n^k$. $\operatorname{id}_{1}(n)$ is usually written simply as $\operatorname{id}(n)$. (completely multiplicative)
-   Constant function: $1(n)=1$. (completely multiplicative)
-   Divisor function: $\sigma_{k}(n)=\sum_{d\mid n}d^{k}$. $\sigma_{0}(n)$ is usually written as $d(n)$ or $\tau(n)$, and $\sigma_{1}(n)$ is usually written as $\sigma(n)$.
-   Euler's totient function: $\varphi(n)=\sum_{i=1}^n[(i,n)=1]$.
-   Möbius function: $\mu(n)=\begin{cases}1&n=1\\0&\exists d>1,d^{2}\mid n\\(-1)^{\omega(n)}&\text{otherwise}\end{cases}$, where $\omega(n)$ is the number of distinct prime factors of $n$.

### Additive functions

???+ note "Definition"
    In number theory, if a function $f(n)$ satisfies $f(1)=0$ and $f(xy)=f(x)+f(y)$ holds for all coprime $x, y \in\mathbf{N}^*$, then $f(n)$ is an **additive function**.
    
    In number theory, if a function $f(n)$ satisfies $f(1)=0$ and $f(xy)=f(x)+f(y)$ holds for all $x, y \in\mathbf{N}^*$, then $f(n)$ is a **completely additive function**.

???+ warning "Additive functions"
    In this section, "additive function" means an additive function in the number-theoretic sense (additive function). Do not confuse it with an additive map in algebra.

#### Properties

For a positive integer $x$, let its unique prime factorization be $x=\prod p_i^{k_i}$, where the $p_i$ are primes.

If $F(x)$ is additive, then $F(x)=\sum F(p_i^{k_i})$.

If $F(x)$ is completely additive, then $F(x)=\sum F(p_i^{k_i})=\sum F(p_i)\cdot k_i$.

#### Examples

For convenience, let $\mathbf P$ be the set of all primes.

-   Multiplicity of $p$ in the prime factorization: $\nu_p(n) = \max\{k\in\mathbf N: p^k\mid n\}$, where $p\in\mathbf P$. (completely additive)
-   Number of prime factors counted with multiplicity: $\Omega(n)=\sum_{p \in\mathbf P} \nu_p(n)$. (completely additive)
-   Number of distinct prime factors: $\omega(n)=\sum_{p \in\mathbf P} [p \mid n]$.
-   Sum of prime factors counted with multiplicity: $a_0(n)=\sum_{p \in\mathbf P} \nu_p(n)\cdot p$. (completely additive)
-   Sum of distinct prime factors: $a_1(n)=\sum_{p \in\mathbf P} [p \mid n] \cdot p$.

## Floor and ceiling functions

For a real number $x$, the **floor function** and the **ceiling function** are defined as

$$
\lfloor x\rfloor = \max\{k\in\mathbf Z:k\le x\},~\lceil x\rceil = \min\{k\in\mathbf Z:k\ge x\}.
$$

Using the floor function, a real number splits into an integer part and a fractional part: $x = \lfloor x\rfloor + \{x\}$. Here $\{x\}$ denotes the fractional part of $x$.

The floor and ceiling functions have the following basic properties ($x\in\mathbf R,~n\in\mathbf Z$):

-   $x\in\mathbf Z \iff x = \lfloor x\rfloor = \lceil x\rceil$.
-   $\lceil x\rceil - \lfloor x\rfloor = [x\notin\mathbf Z]$.
-   $x - 1 < \lfloor x\rfloor \le x \le \lceil x\rceil < x + 1$.
-   $\lfloor -x\rfloor = -\lceil x\rceil,~\lceil -x\rceil = -\lfloor x\rfloor$.
-   $\lfloor x + n\rfloor = \lfloor x\rfloor + n,~\lceil x + n\rceil = \lceil x \rceil + n$.
-   $\lfloor x\rfloor$ and $\lceil x\rceil$ are both monotonically non-decreasing functions of $x$.

Proofs of identities involving floor (ceiling) often use the following equivalent forms ($x\in\mathbf R,~n\in\mathbf Z$):

-   $\lfloor x\rfloor = n \iff n \le x < n + 1 \iff x - 1 < n \le x$.
-   $\lceil x\rceil = n \iff n - 1 < x \le n \iff x \le n < x + 1$.

Proofs of inequalities involving floor (ceiling) often use the following equivalent forms ($x\in\mathbf R,~n\in\mathbf Z$):

-   $x < n \iff \lfloor x\rfloor < n$.
-   $n < x \iff n < \lceil x\rceil$.
-   $x \le n \iff \lceil x\rceil \le n$.
-   $n \le x \iff n \le \lfloor x\rfloor$.

Properties involving sums and differences ($x,y\in\mathbf R$):

-   $\lfloor x\rfloor + \lfloor y\rfloor \le \lfloor x + y\rfloor \le \lfloor x\rfloor + \lfloor y\rfloor + 1$, and exactly one of the two equalities holds.
-   $\lceil x\rceil +\lceil y\rceil -1\leq \lceil x+y\rceil \leq \lceil x\rceil +\lceil y\rceil$, and exactly one of the two equalities holds.
-   $\lfloor|x - y|\rfloor \le |\lfloor x\rfloor - \lfloor y\rfloor| \le \lceil|x - y|\rceil$.
-   $\lfloor|x - y|\rfloor \le |\lceil x\rceil - \lceil y\rceil| \le \lceil|x-y|\rceil$.

Properties involving quotients ($x\in\mathbf R,~n\in\mathbf Z,~m\in\mathbf Z_+$):

-   $\left\lceil\dfrac{n}{m}\right\rceil = \left\lfloor\dfrac{n+m-1}{m}\right\rfloor,~\left\lfloor\dfrac{n}{m}\right\rfloor = \left\lceil\dfrac{n-m+1}{m}\right\rceil$.
-   $\left\lfloor\dfrac{x + n}{m} \right\rfloor = \left\lfloor\dfrac{\lfloor x\rfloor + n}{m} \right\rfloor,~\left\lceil\dfrac{x + n}{m} \right\rceil = \left\lceil\dfrac{\lceil x\rceil + n}{m} \right\rceil$.
-   $\left\lfloor\dfrac{\lfloor x/n\rfloor}{m}\right\rfloor = \left\lfloor\dfrac{x}{nm}\right\rfloor,~\left\lceil\dfrac{\lceil x/n\rceil}{m}\right\rceil = \left\lceil\dfrac{x}{nm}\right\rceil$.
-   For $x > 0$, $\displaystyle\left\lfloor\dfrac{x}{m}\right\rfloor = \sum_{k=1}^{\lfloor x\rfloor}[m\mid k]$.

The second and third properties are both direct corollaries of the following result:

-   Let $f$ be a continuous increasing function such that $f(x)\in\mathbf Z$ implies $x\in\mathbf Z$. Then

    $$
    \lfloor f(x)\rfloor = \lfloor f(\lfloor x\rfloor)\rfloor,~ \lceil f(x)\rceil = \lceil f(\lceil x\rceil)\rceil.
    $$

    ??? note "Proof"
        By symmetry, we only need to prove the first equation. If $x$ is an integer, the claim is obvious. Otherwise, $\lfloor x\rfloor < x$. Since $f$ and the floor function are monotonic, $\lfloor f(x)\rfloor \ge \lfloor f(\lfloor x\rfloor)\rfloor$. Suppose equality does not hold, and let $y = \lfloor f(x)\rfloor$. Then $\lfloor f(\lfloor x\rfloor)\rfloor < y \le \lfloor f(x)\rfloor$, which is equivalent to $f(\lfloor x\rfloor) < y \le f(x)$. Since $f$ is continuous, there is some $\lfloor x\rfloor < x_0 \le x$ with $f(x_0)=y$. Because $y\in\mathbf Z$, we get $x_0\in\mathbf Z$, which contradicts the definition of $\lfloor x\rfloor$. So equality holds, that is, $\lfloor f(x)\rfloor = \lfloor f(\lfloor x\rfloor)\rfloor$.

Finally, here are some results on sums involving floor and ceiling ($x\in\mathbf R,~n\in\mathbf Z,~m\in\mathbf Z_+$):

-   $n = \left\lfloor\dfrac{n}{2}\right\rfloor + \left\lceil\dfrac{n}{2}\right\rceil$.
-   $n = \left\lfloor\dfrac{n}{m} \right\rfloor + \left\lfloor\dfrac{n+1}{m} \right\rfloor + \cdots + \left\lfloor\dfrac{n+m-1}{m} \right\rfloor$.
-   $n = \left\lceil\dfrac{n}{m} \right\rceil + \left\lceil\dfrac{n-1}{m} \right\rceil + \cdots + \left\lceil\dfrac{n-m+1}{m} \right\rceil$.
-   $\lfloor mx\rfloor = \lfloor x\rfloor + \left\lfloor x+\dfrac{1}{m}\right\rfloor + \cdots + \left\lfloor x+\dfrac{m-1}{m}\right\rfloor$.
-   $\lceil mx\rceil = \lceil x\rceil + \left\lceil x - \dfrac{1}{m}\right\rceil + \cdots + \left\lceil x - \dfrac{m-1}{m}\right\rceil$.
-   When $m\perp n$, $\displaystyle\sum_{k=1}^{m-1}\left\lfloor\dfrac{kn}{m}\right\rfloor=\dfrac{1}{2}(n-1)(m-1)$.
-   When $m\perp n$, $\displaystyle\sum_{k=1}^{m-1}\left\lceil\dfrac{kn}{m}\right\rceil=\dfrac{1}{2}(n+1)(m-1)$.

For derivations of these and more general sums of this kind, see the [Floor Sum (Euclidean-like Algorithm)](./euclidean.md) page.

For more properties and applications of floor and ceiling, see the following pages:

-   The modulo operation: $n\bmod m = n - \left\lfloor\dfrac{n}{m}\right\rfloor m$. It can be used to [speed up integer modulo operations](./mod-arithmetic.md#相关算法).
-   Using Gauss's lemma to prove the [law of quadratic reciprocity](./quad-residue.md#二次互反律).
-   [Divisor blocks (sqrt decomposition in number theory)](./sqrt-decomposition.md), especially the proofs of its properties.
-   [Legendre's formula](./factorial.md#legendre-公式) for the exponent of a prime in a factorial.
-   [Beatty sequences](../game-theory/impartial-game.md#wythoff-游戏), Rayleigh's theorem, and Wythoff's game.

## References and notes

-   Pan Chengdong, Pan Chengbiao. Elementary Number Theory. Peking University Press.
-   [Floor and ceiling functions - Wikipedia](https://en.wikipedia.org/wiki/Floor_and_ceiling_functions)
-   Graham, Ronald L., Donald E. Knuth, and Oren Patashnik. "Concrete mathematics: a foundation for computer science." (1989).

[^ref1]: [Are all primes (past 2 and 3) of the forms 6n+1 and 6n-1?](https://primes.utm.edu/notes/faq/six.html)

[^gcdcpp]: [std::gcd - cppreference.com](https://en.cppreference.com/w/cpp/numeric/gcd)
