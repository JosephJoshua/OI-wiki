Prerequisites: [Fermat's little theorem](./fermat.md#费马小定理), [Euler's theorem](./fermat.md#欧拉定理), [Lagrange's theorem](./congruence-equation.md#素数模同余方程)

Orders and primitive roots are key tools for understanding the multiplicative structure of the [reduced residue system](./basic.md#同余类与剩余系) $\mathbf Z_m^*$ modulo $m$. Building on them, one can define concepts such as the [discrete logarithm](./discrete-logarithm.md). For a more general treatment, see the related sections of the abstract algebra pages on [group theory](../algebra/group-theory.md#阶) and [ring theory](../algebra/ring-theory.md#应用整数同余类的乘法群).

## Order

In this section, we always assume that the modulus $m\in\mathbf N_+$ and the base $a\in\mathbf Z$ are coprime, that is, $(a,m)=1$, also written $a\perp m$.

For $n\in\mathbf Z$, the powers $a^n\bmod m$ form a cycle. The minimum length of this cycle is the order of $a$ modulo $m$. The order is defined as the exponent at which the power $a^n \bmod m$ first returns to the start $a^0\bmod m = 1$:

???+ abstract "Order"
    For $a\in\mathbf Z,m\in\mathbf N_+$ with $a\perp m$, the smallest positive integer $n$ satisfying the congruence $a^n \equiv 1 \pmod m$ is called **the order of $a$ modulo $m$**, written $\delta_m(a)$ or $\operatorname{ord}_m(a)$.

???+ tip "Note"
    In [abstract algebra](../algebra/group-theory.md#阶), the "order" here is exactly the order of the element $a$ in the group formed by the reduced residue system modulo $m$ under multiplication. The notation $\delta$ for the order is only used for this particular group. Many of the properties below generalize directly to properties of the order of elements in abstract groups.
    
    There is also the concept of a "half order", written $\delta^-$ in number theory. It is the smallest positive integer satisfying the congruence $a^n \equiv -1 \pmod m$. The half order is not a group-theoretic concept. The order always exists, but the half order may not.

### Cyclic structure of powers

The order describes the cyclic structure of powers. For a power $a^n\bmod m$, divide the exponent $n$ by the order $\delta_m(a)$ with remainder:

$$
n = \delta_m(a)q + r, ~ 0\le r < \delta_m(a). 
$$

Then, by the rules of exponents,

$$
a^n = a^{\delta_m(a)q + r} = (a^{\delta_m(a)})^q \cdot a^r \equiv a^r \pmod m.
$$

So a power with any exponent can be shifted into the first nonnegative cycle. This gives a series of properties of the order.

???+ note "Property 1"
    For $a\in\mathbf Z,m\in\mathbf N_+$ with $a\perp m$, the powers $a^0(=1),a,a^2,\cdots,a^{\delta_m(a)-1}$ are pairwise incongruent modulo $m$.

??? note "Proof"
    By contradiction. Suppose there are two numbers $0\le i< j<\delta_m(a)$ with $a^i\equiv a^j\pmod m$. Then $a^{j - i}\equiv 1\pmod m$. But $0 < j - i < \delta_m(a)$, which contradicts the minimality of the order. So the claim holds.

???+ note "Property 2"
    For $a,n\in\mathbf Z,m\in\mathbf N_+$ with $a\perp m$, the congruence $a^n \equiv 1 \pmod m$ holds if and only if $\delta_m(a)\mid n$.

??? note "Proof"
    As shown above, $a^{n}\equiv a^{n\bmod\delta_m(a)}\pmod m$. By Property 1, the only $r$ with $0\le r < \delta_m(a)$ and $a^r\equiv 1\pmod m$ is $r=0$. So $a^n \equiv 1 \pmod m$ if and only if $n\bmod \delta_m(a) = 0$, that is, $\delta_m(a)\mid n$.

In [Euler's theorem](./fermat.md#欧拉定理), the congruence $a^{\varphi(m)}\equiv 1\pmod m$ holds for all $a\perp m$. Combined with Property 2, this means $\delta_m(a)\mid\varphi(m)$ for all $a\perp m$. In other words, $\varphi(m)$ is a common multiple of the orders of all $a\perp m$. For a positive integer $m$, the least common multiple of the orders $\delta_m(a)$ of all $a\perp m$, written $\lambda(m)$, is the [Carmichael function](#carmichael-function) of $m$. Its properties are discussed in detail later.

As with other cyclic structures, the order of $a^k$ can be computed from the order of $a$.

???+ note "Property 3"
    For $k,a\in\mathbf Z,m\in\mathbf N_+$ with $a\perp m$,
    
    $$
    \delta_m(a^k) = \dfrac{\delta_m(a)}{(\delta_m(a),k)}.
    $$

??? note "Proof"
    By Property 2, the congruence $(a^k)^n = a^{kn} \equiv 1\pmod m$ holds if and only if $\delta_m(a) \mid kn$. This condition is equivalent to
    
    $$
    \dfrac{\delta_m(a)}{\left(\delta_m(a),k\right)} \mid n.
    $$
    
    The smallest positive integer satisfying this condition is
    
    $$
    \delta_m(a^k)=\dfrac{\delta_m(a)}{\left(\delta_m(a),k\right)}.
    $$

### Order of a product

Let $a,b$ be distinct integers coprime to $m$. If the orders $\delta_m(a)$ and $\delta_m(b)$ are known, we can also get some information about the order $\delta_{m}(ab)$ of their product $ab$.

???+ note "Property 4"
    For $a,b\in\mathbf Z,m\in\mathbf N_+$ with $a,b\perp m$,
    
    $$
    \dfrac{[\delta_m(a),\delta_m(b)]}{(\delta_m(a),\delta_m(b))} \mid \delta_m(ab) \mid [\delta_m(a),\delta_m(b)].
    $$

??? note "Proof"
    Since $[\delta_m(a),\delta_m(b)]$ is a multiple of both $\delta_m(a)$ and $\delta_m(b)$, Property 2 gives
    
    $$
    (ab)^{[\delta_m(a),\delta_m(b)]} = a^{[\delta_m(a),\delta_m(b)]} b^{[\delta_m(a),\delta_m(b)]} \equiv 1 \pmod m.
    $$
    
    Applying Property 2 again gives
    
    $$
    \delta_m(ab) \mid [\delta_m(a),\delta_m(b)].
    $$
    
    This is the divisibility on the right.
    
    Conversely, since
    
    $$
    1 \equiv (ab)^{\delta_m(ab)\delta_m(b)} \equiv a^{\delta_m(ab)\delta_m(b)} \pmod m,
    $$
    
    Property 2 gives $\delta_m(a)\mid\delta_m(ab)\delta_m(b)$. Dividing both sides by $(\delta_m(a),\delta_m(b))$ gives
    
    $$
    \dfrac{\delta_m(a)}{(\delta_m(a),\delta_m(b))}\mid\delta_m(ab)\dfrac{\delta_m(b)}{(\delta_m(a),\delta_m(b))}.
    $$
    
    After removing the common factor, the two fractions are coprime, so
    
    $$
    \dfrac{\delta_m(a)}{(\delta_m(a),\delta_m(b))}\mid\delta_m(ab).
    $$
    
    Similarly,
    
    $$
    \dfrac{\delta_m(b)}{(\delta_m(a),\delta_m(b))}\mid\delta_m(ab).
    $$
    
    Since the left sides of these two divisibilities are coprime,
    
    $$
    \dfrac{[\delta_m(a),\delta_m(b)]}{(\delta_m(a),\delta_m(b))} =\dfrac{\delta_m(a)\delta_m(b)}{(\delta_m(a),\delta_m(b))^2}\mid\delta_m(ab).
    $$
    
    This is the divisibility on the left.

When the orders of $a$ and $b$ are coprime, this result takes a simpler form.

???+ note "Property 4'"
    For $a,b\in\mathbf Z,m\in\mathbf N_+$ with $a,b\perp m$,
    
    $$
    \delta_m(ab) = \delta_m(a)\delta_m(b) \iff \delta_m(a)\perp\delta_m(b).
    $$

??? note "Proof"
    If $\delta_m(a)\perp\delta_m(b)$, then all divisibilities in Property 4 are equalities, so
    
    $$
    \delta_m(ab) = [\delta_m(a),\delta_m(b)] = \delta_m(a)\delta_m(b).
    $$
    
    Conversely, if $\delta_m(ab)=\delta_m(a)\delta_m(b)$, then by Property 4,
    
    $$
    \delta_m(a)\delta_m(b) = \delta_m(ab) \mid [\delta_m(a),\delta_m(b)].
    $$
    
    This immediately gives $(\delta_m(a),\delta_m(b))=1$, that is, $\delta_m(a)\perp\delta_m(b)$.

In general, the bounds from Property 4 are already tight. It is easy to construct a case where the order of the product reaches the lower bound: for example, with $(a,b,m)=(3,5,7)$, $\delta_m(a)=\delta_m(b)=6$, but the order of their product is $\delta_m(ab)=1$.

Although in general the order of the product $ab$ need not be the least common multiple of their orders, we can always find an element whose order equals this least common multiple.

???+ note "Property 5"
    For $a,b\in\mathbf Z,m\in\mathbf N_+$ with $a,b\perp m$, there always exists $c\in\mathbf Z$ with $c\perp m$ such that
    
    $$
    \delta_m(c) = [\delta_m(a),\delta_m(b)].
    $$

??? note "Proof"
    Consider the prime factorizations:
    
    $$
    \delta_m(a) = \prod_p p^{\alpha_p},~ \delta_m(b) = \prod_p p^{\beta_p}.
    $$
    
    By comparing $\alpha_p$ and $\beta_p$, split all prime factors into two classes:
    
    $$
    A = \{p : \alpha_p \ge \beta_p\}, ~ B = \{p : \alpha_p < \beta_p\}.
    $$
    
    Then set
    
    $$
    \gamma_A = \prod_{p\in A}p^{\alpha_p},~\gamma_B = \prod_{p\in B}p^{\alpha_p},~\eta_A = \prod_{p\in A}p^{\beta_p},~\eta_B = \prod_{p\in B}p^{\beta_p},
    $$
    
    so that $\delta_m(a) = \gamma_A\gamma_B$ and $\delta_m(b)=\eta_A\eta_B$. By Property 3,
    
    $$
    \begin{aligned}
    \delta_m(a^{\gamma_B}) &= \dfrac{\delta_m(a)}{(\delta_m(a),\gamma_B)} = \dfrac{\delta_m(a)}{\gamma_B} = \gamma_A,\\
    \delta_m(b^{\eta_A}) &= \dfrac{\delta_m(b)}{(\delta_m(b),\eta_A)} = \dfrac{\delta_m(b)}{\eta_A} = \eta_B.
    \end{aligned}
    $$
    
    Since $\gamma_A\perp\eta_B$, Property 4' gives
    
    $$
    \delta_m(a^{\gamma_B}b^{\eta_A}) = \gamma_A\eta_B = \prod_p p^{\max\{\alpha_p,\beta_p\}} = [\delta_m(a),\delta_m(b)].
    $$
    
    So $c=a^{\gamma_B}b^{\eta_A}$ is an element of order $[\delta_m(a),\delta_m(b)]$.

This result is often used to construct elements of a given order.

## Primitive root

Primitive roots are special elements whose order equals the number of elements in the reduced residue system modulo $m$.

???+ abstract "Primitive root"
    For $m\in\mathbf N_+$, if there exists $g\in\mathbf Z$ with $g\perp m$ such that $\delta_m(g)=|\mathbf Z_m^*|=\varphi(m)$, then $g$ is called a **primitive root modulo $m$**. Here $\varphi(m)$ is [Euler's totient function](./euler-totient.md).

Not every positive integer $m$ has a primitive root modulo $m$. By [Property 1](#cyclic-structure-of-powers) above, if a primitive root $g$ modulo $m$ exists, then $g,g^2,\cdots,g^{\varphi(m)}$ lie in pairwise different residue classes and form a reduced residue system modulo $m$. In particular, for a prime $p$, the remainders $g^i\bmod p$ for $i=1,2,\cdots,p-1$ are pairwise distinct.

???+ tip "Note"
    In [abstract algebra](../algebra/ring-theory.md#应用整数同余类的乘法群), a primitive root is a generator of a cyclic group. The name "primitive root" is only used for the group formed by the reduced residue system modulo $m$ under multiplication; in a general cyclic group it is called a "generator". Not every such group is cyclic: having a primitive root means the group is isomorphic to a cyclic group, and having none means it is not.

When the modulus is $1$, the multiplicative group of integers modulo $1$ is $\{0\}$. This is clearly a cyclic group, so the primitive root is $0$.

### Primitive root test

If all prime factors of $\varphi(m)$ are known, it is easy to check whether a given $g$ is a primitive root modulo $m$.

???+ note "Theorem"
    For an integer $m\ge 3$ and $g\perp m$, $g$ is a primitive root modulo $m$ if and only if for every prime factor $p$ of $\varphi(m)$,
    
    $$
    g^{\frac{\varphi(m)}{p}}\not\equiv 1 \pmod m.
    $$

??? note "Proof"
    Necessity is obvious. To prove sufficiency, use contradiction. If $g$ is not a primitive root modulo $m$, then $\delta_m(g)< \varphi(m)$. By [Property 2](#cyclic-structure-of-powers) and Euler's theorem, $\delta_m(g)\mid\varphi(m)$. So let $p$ be a prime factor of $\dfrac{\varphi(m)}{\delta_m(g)}$; then $\delta_m(g)\mid\dfrac{\varphi(m)}{p}$. Applying Property 2 again gives
    
    $$
    g^{\frac{\varphi(m)}{p}} \equiv 1 \pmod m.
    $$
    
    But $p$ is also a prime factor of $\varphi(m)$, which contradicts the assumption. So sufficiency holds.

### Number of primitive roots

A primitive root, if it exists, need not be unique. In general, the possible orders of elements of the reduced residue system modulo $m$ and the number of elements of each order are given by:

???+ note "Theorem"
    If the positive integer $m$ has a primitive root $g$, then elements of order $d$ modulo $m$ exist if and only if $d\mid\varphi(m)$, and there are exactly $\varphi(d)$ of them. In particular, there are $\varphi(\varphi(m))$ primitive roots modulo $m$.

??? note "Proof"
    By the definition of a primitive root, every reduced residue class modulo $m$ can be written as $g^k\bmod m$ with $k$ one of $1,2,\cdots,\varphi(m)$. By [Property 3](#cyclic-structure-of-powers), the order of such an element is
    
    $$
    \delta_m(g^k) = \dfrac{\varphi(m)}{(\varphi(m),k)}.
    $$
    
    So an element of order $d$ exists if and only if $d\mid\varphi(m)$. Moreover, for $d\mid\varphi(m)$, let $d'=\varphi(m)/d$; the set of these elements is
    
    $$
    \begin{aligned}
    A &= \{g^k : (\varphi(m),k)=d',~1\le k \le\varphi(m)\} \\
    &= \{g^k : d'\mid k,~ (d, k/d') = 1,~ 1 \le k/d' \le d\}.
    \end{aligned}
    $$
    
    The values $k'=k/d'$ for these elements are exactly the positive integers not exceeding $d$ and coprime to $d$. By the definition of Euler's totient function, there are $\varphi(d)$ of them.

### Existence theorem for primitive roots

This section proves the following existence theorem for primitive roots:

???+ note "Theorem"
    A primitive root modulo $m$ exists if and only if $m=1,2,4,p^e,2p^e$, where $p$ is an odd prime and $e\in\mathbf N_+$.

To show this, we discuss the following four cases separately:

1.  $m=1,2,4$: the primitive roots are $g=0,1,3$ respectively, so they clearly exist.

2.  $m=p^{e}$ is a power of an odd prime, where $p$ is an odd prime and $e\in\mathbf N_+$.

    ???+ note "Lemma 1"
        For an odd prime $p$, a primitive root modulo $p$ exists.

    ??? note "Proof"
        The proof has two steps.
        
        **Step 1**: For $d\mid(p-1)$, the congruence $x^d\equiv 1\pmod p$ has exactly $d$ distinct solutions.
        
        Let $p-1=kd$ and consider the polynomial
        
        $$
        f(x) = x^{d(k-1)} + x^{d(k-2)} + \cdots + x^d + 1. 
        $$
        
        By [Euler's theorem](./fermat.md#欧拉定理), the congruence $(x^d-1)f(x)=x^{p-1}-1\equiv 0\pmod{p}$ has exactly $p-1$ distinct solutions. Each of these is a root of either $x^d-1$ or $f(x)$. By [Lagrange's theorem](./congruence-equation.md#素数模同余方程), these have at most $d$ and at most $d(k-1)$ distinct roots respectively. Since $d+d(k-1)=p-1$, the former must have exactly $d$ distinct roots. So the congruence $x^d\equiv 1\pmod p$ has exactly $d$ distinct solutions.
        
        **Step 2**: For $d\mid(p-1)$, there are exactly $\varphi(d)$ elements of order $d$.
        
        Sort all divisors of $p-1$ and use induction. The only element of order $1$ is $1$, so there is exactly one, and the base case holds. For $d\mid(p-1)$, by [Property 2](#cyclic-structure-of-powers) above, every solution of $x^d\equiv 1\pmod p$ satisfies $\delta_p(x)\mid d$. So the number of elements of order $d$ among them is
        
        $$
        N(d) = d - \sum_{e\mid d,~e\neq d} N(e) = d - \sum_{e\mid d,~e\neq d} \varphi(e) = \varphi(d).
        $$
        
        The second equality is the induction hypothesis, and the third is a property of Euler's totient function. By induction, for every $d\mid(p-1)$ there are exactly $\varphi(d)$ elements of order $d$.
        
        In particular, for $d=p-1$ there are exactly $\varphi(p-1)$ elements of order $(p-1)$. So a primitive root modulo $p$ exists.

    ???+ note "Lemma 2"
        For an odd prime $p$ and $e \in \mathbf{N}_+$, a primitive root modulo $p^e$ exists.

    ??? note "Proof"
        The proof has three steps.
        
        **Step 1**: There is a primitive root $g$ modulo $p$ such that $g^{p-1}\not\equiv 1\pmod{p^2}$.
        
        Take any primitive root $g$ modulo $p$. If it does not satisfy the condition, that is, $g^{p-1}\equiv 1\pmod{p^2}$, then we can show that $g+p$ does: $g+p$ is also a primitive root modulo $p$, and
        
        $$
        \begin{aligned}
        (g+p)^{p-1} &\equiv \binom{p-1}{0}g^{p-1} + \binom{p-1}{1}g^{p-2}p \\
        &= g^{p-1} + g^{p-2}p(p-1) \\ 
        &\equiv 1 - pg^{p-2} \not\equiv 1 \pmod{p^2}.
        \end{aligned}
        $$
        
        **Step 2**: For the $g$ chosen above, $g^{\varphi(p^e)}\not\equiv 1\pmod{p^{e+1}}$ for every $e\ge 1$.
        
        The choice of $g$ ensures the claim holds for $e=1$. Suppose it holds for $e$; we show it also holds for $e+1$. For any $e \ge 1$, by Euler's theorem there is an integer $t$ such that
        
        $$
        g^{\varphi(p^e)} = 1 + t p^e
        $$
        
        By the induction hypothesis, $t\perp p$. Since $\varphi(p^{e+1})=p\varphi(p^e)$,
        
        $$
        g^{\varphi(p^{e+1})} = \left(g^{\varphi(p^{e})}\right)^p = (1 + t p^e)^p \equiv 1 + t p^{e+1} \pmod{p^{e+2}}.
        $$
        
        Together with $t\perp p$, this gives $g^{\varphi(p^{e+1})}\not\equiv 1\pmod{p^{e+2}}$. By induction, the claim holds.
        
        **Step 3**: The $g$ chosen above is a primitive root modulo $p^e$ for every $e\ge 1$.
        
        The choice of $g$ ensures the claim holds for $e=1$. Suppose it holds for $e$; we show it also holds for $e+1$. Write $\delta$ for $\delta_{p^{e+1}}(g)$. Since $g^\delta\equiv 1\pmod{p^{e+1}}$, also $g^\delta\equiv 1\pmod{p^e}$. By the induction hypothesis, $\delta_{p^e}(g) = \varphi(p^e)$. So by [Property 2](#cyclic-structure-of-powers) of the order, $\varphi(p^e)\mid\delta$. Also, by Euler's theorem, $\delta\mid\varphi(p^{e+1})$. But $\varphi(p^{e+1})=p\varphi(p^e)$. So there are only two possibilities: $\delta=\varphi(p^e)$ or $\delta=\varphi(p^{e+1})$. However, Step 2 shows that $g^{\varphi(p^e)}\not\equiv 1\pmod{p^{e+1}}$, so $\delta=\varphi(p^e)$ is impossible. The only possibility is $\delta=\varphi(p^{e+1})$, which means $g$ is a primitive root modulo $p^{e+1}$. By induction, the claim holds for all $e\ge 1$.

3.  $m=2p^{e}$, where $p$ is an odd prime and $e\in\mathbf N_+$.

    ???+ note "Lemma 3"
        For an odd prime $p$ and $e \in \mathbf{N}_+$, a primitive root modulo $2p^e$ exists.

    ??? note "Proof"
        Let $g$ be a primitive root modulo $p^{e}$; then $g+p^e$ is also a primitive root modulo $p^{e}$. One of the two must be odd; without loss of generality, call it $g$. Clearly $(g,2p^e)=1$. Let $\delta=\delta_{2p^e}(g)$; we need to show $\delta=\varphi(2p^e)$. By Euler's theorem, $\delta\mid\varphi(2p^e)$. Also, by definition $g^\delta\equiv 1\pmod{2p^e}$, so $g^\delta\equiv 1\pmod{p^e}$. Hence, by [Property 2](#cyclic-structure-of-powers) of the order and the choice of $g$, $\delta_{p^e}(g)=\varphi(p^e)\mid \delta$. From the formula for Euler's totient function, $\varphi(2p^e) = \varphi(p^e)$. So $\delta=\delta_{2p^e}(g)=\varphi(p^e)=\varphi(2p^e)$. This shows that $g$ is a primitive root modulo $2p^e$.

4.  $m\ne 1,2,4,p^{e},2p^{e}$, where $p$ is an odd prime and $e\in\mathbf N_+$.

    ???+ note "Lemma 4"
        Suppose $m\neq 1,2,4$ and there is no odd prime $p$ and positive integer $e$ with $m=p^e$ or $m=2p^e$. Then no primitive root modulo $m$ exists.

    ??? note "Proof"
        For $m=2^e$ with $e\ge 3$, suppose a primitive root $g$ modulo $m$ exists. Since $g\perp m$, it must be odd. Write $g=2k+1$ with $k\in\mathbf N$; then
        
        $$
        \begin{aligned}
        g^{2^{e-2}}
        &=(2k+1)^{2^{e-2}} \\
        &\equiv 1 + \binom{2^{e-2}}{1}(2k) + \binom{{2^{e-2}}}{2}(2k)^2 \\
        &= 1 + 2^{e-1}k + 2^{e-1}(2^{e-2}-1)k^2 \\
        &= 1 + 2^{e-1}(k + (2^{e-2}-1)k^2) \\
        &\equiv 1 \pmod{2^{e}}.
        \end{aligned}
        $$
        
        In the second-to-last line, $k$ and $(2^{e-2}-1)k^2$ have the same parity, so their sum is even. By the definition of the order, $\delta_{2^{e}}(g)\le 2^{e-2}< \varphi(2^{e}) = 2^{e-1}$. This contradicts the assumption that $g$ is a primitive root. So by contradiction, no such primitive root exists.
        
        Suppose $m$ satisfies the stated condition and is not a power of $2$. Then there exist $2 < m_1 < m_2$ with $m_1\perp m_2$ and $m=m_1m_2$. Suppose a primitive root $g$ modulo $m$ exists. Since $g\perp m$, we have $g\perp m_i$ for $i=1,2$. By Euler's theorem,
        
        $$
        g^{\varphi(m_i)} \equiv 1 \pmod{m_i}.
        $$
        
        Since $m_i > 2$, $\varphi(m_i)$ is even, so for $i=1,2$,
        
        $$
        g^{\frac{1}{2}\varphi(m_1)\varphi(m_2)} \equiv 1 \pmod{m_i}.
        $$
        
        By the [Chinese remainder theorem](./crt.md),
        
        $$
        g^{\frac{1}{2}\varphi(m_1)\varphi(m_2)} \equiv 1 \pmod{m}.
        $$
        
        Also, since $\varphi(m)=\varphi(m_1)\varphi(m_2)$, by the definition of the order,
        
        $$
        \delta_m(g) \le \frac{1}{2}\varphi(m_1)\varphi(m_2) = \dfrac{1}{2}\varphi(m) < \varphi(m).
        $$
        
        This contradicts the assumption that $g$ is a primitive root modulo $m$. So by contradiction, no primitive root modulo $m$ exists.

Combining the four cases above gives a necessary and sufficient condition for a number to have a primitive root.

### Algorithms for finding primitive roots

For any modulus $m$ that has a primitive root, to find a primitive root $g$ it is enough to enumerate candidate positive integers and check each one. There are usually two ways to enumerate: go through them one by one from small to large, or generate random positive integers. In practice, the two are about equally efficient.

Enumerating from small to large finds the smallest primitive root $g_m$ modulo $m$, so the cost of the enumeration depends on the size of $g_m$. The following estimates are known:

-   Upper bound: Wang Yuan[^yuan1959note] and Burgess[^burgess1962character] proved that the smallest primitive root of a prime $p$ is $g_p=O\left(p^{0.25+\epsilon}\right)$, where $\epsilon>0$. Cohen, Odoni, and Stothers[^cohen1974least] and Elliott and Murata[^elliott1998least] proved that the same estimate holds for the moduli $p^2$ and $2p^2$ respectively, where $p$ is an odd prime. Since for $e>2$ a primitive root modulo $p^2$ (or $2p^2$) is also a primitive root modulo $p^e$ (or $2p^e$), the upper bound $O\left(p^{0.25+\epsilon}\right)$ on the smallest primitive root holds in all cases.
-   Lower bound: Fridlender[^fridlender1949least] and Salié[^salie1949kleinsten] proved that there is a $C>0$ such that for infinitely many primes $p$, the smallest primitive root satisfies $g_p > C\log p$.
-   Average case: Burgess and Elliott[^burgess1968average] proved that on average, the smallest primitive root of a prime $p$ is $g_p=O((\log p)^2(\log\log p)^4)$. Elliott and Murata[^elliott1997average] further conjectured that the average of the smallest primitive root of a prime $p$ is a constant, and numerical checks[^more-evidence] put it at about $4.926$. Later, Elliott and Murata[^elliott1998least] extended this conjecture to the modulus $2p^2$.

From this analysis, when searching for the smallest primitive root by brute force, the enumeration cost $O(g_m(\log m)^2)$ is acceptable.

Besides enumerating from small to large, primitive roots can also be found by generating random positive integers and checking them. Primitive roots are not rare:[^density-prim-root]

$$
\dfrac{\varphi(\varphi(m))}{m} = \Omega\left(\dfrac{1}{\log\log m}\right).
$$

So when searching for a primitive root randomly, the expected cost of the enumeration is $O((\log m)^2\log\log m)$.

Note that testing for a primitive root requires the prime factorization of $\varphi(m)$. Among the [prime factorization algorithms common in contests](./pollard-rho.md), even the fastest, Pollard Rho, needs $O(m^{1/4+\epsilon})$ time. So whenever the prime factorization of $\varphi(m)$ is unknown, no matter which enumeration method is used, the bottleneck of finding a primitive root is the factorization step, not the enumeration and checking.

## Carmichael function

While the order of an element modulo $m$ is a local concept, the Carmichael function is a global one. It is the smallest common cycle length of the powers of all integers coprime to $m$.

???+ abstract "Carmichael function"
    For $m\in\mathbf N_+$, define $\lambda(m)$ as the smallest positive integer $n$ such that the congruence $a^n\equiv 1\pmod m$ holds for all $a\perp m$. The function $\lambda:\mathbf N_+\to\mathbf N_+$ is called the **Carmichael function**.

By [Property 2](#cyclic-structure-of-powers), $a^n\equiv 1\pmod m$ holding for all $a\perp m$ means $\delta_m(a)\mid n$ for all $a\perp m$. That is, any positive integer $n$ meeting this condition must be a common multiple of all $\delta_m(a)$. So the smallest such $n$ is their least common multiple:

$$
\lambda(m) = \operatorname{lcm}\{\delta_m(a) : a\perp m\}.
$$

This is also often used as an equivalent definition of the Carmichael function.

Applying [Property 5](#order-of-a-product) repeatedly shows that there is always some element $a\perp m$ with $\delta_m(a)=\lambda(m)$. So the formula above can also be written as

$$
\lambda(m) = \max\{\delta_m(a) : a\perp m\}.
$$

An element $a\perp m$ attaining this maximum is also called a **$\lambda$-primitive root** modulo $m$. It exists for every modulus $m$.

### Recursive formula

The Carmichael function is an [arithmetic function](./basic.md#数论函数). This section derives a recursive formula for it, and from it gives another proof of the existence theorem for primitive roots.

Although it is not a multiplicative function, the Carmichael function can still be computed by handling coprime factors separately.

???+ note "Lemma"
    For coprime positive integers $m_1,m_2$, $\lambda(m_1m_2)=[\lambda(m_1),\lambda(m_2)]$.

??? note "Proof"
    Let $a_1$ and $a_2$ be $\lambda$-primitive roots modulo $m_1$ and $m_2$ respectively. Let $m=m_1m_2$. By the [Chinese remainder theorem](./crt.md), there is $a\perp m$ with $a\equiv a_i\pmod{m_i}$ for $i=1,2$. Since $a^{\lambda(m)}\equiv 1\pmod m$, we have $a_i^{\lambda(m)} \equiv 1\pmod{m_i}$ for $i=1,2$, and then by [Property 2](#cyclic-structure-of-powers) and the choice of $a_i$, $\lambda(m_i)=\delta_{m_i}(a_i)\mid \lambda(m)$. This shows $[\lambda(m_1),\lambda(m_2)]\mid\lambda(m)$.
    
    Conversely, for any $a\perp m$ and $i=1,2$, we have $a^{[\lambda(m_1),\lambda(m_2)]} \equiv 1 \pmod{m_i}$. By the Chinese remainder theorem, $a^{[\lambda(m_1),\lambda(m_2)]} \equiv 1 \pmod{m}$ holds for all $a\perp m$. By the definition of the Carmichael function, $\lambda(m)\mid [\lambda(m_1),\lambda(m_2)]$.
    
    So the equality in the claim holds.

So it remains to compute the Carmichael function at prime powers. First, handle powers of $2$.

???+ note "Lemma"
    For $m=2^e$ with $e\in\mathbf N_+$, $\lambda(2)=1$, $\lambda(4)=2$, and $\lambda(m)=2^{e-2}$ for all $e\ge 3$.

??? note "Proof"
    The cases $m=2,4$ can be checked directly. For $m=2^e$ with $e\ge 3$, first repeat the first part of the proof of [Lemma 4](#existence-theorem-for-primitive-roots) above to get $\lambda(m)\le 2^{e-2}$. Then it suffices to show that an element of order $2^{e-2}$ exists. Indeed,
    
    $$
    5^{2^{e-3}} = (1 + 2^2)^{2^{e-3}} \equiv 1 + 2^2\times 2^{e-3} = 1 + 2^{e-1} \not\equiv 1 \pmod{2^e}.
    $$
    
    This shows $\delta_m(5)\nmid 2^{e-3}$; since also $\delta_m(5) \mid 2^{e-2}$, $5$ must have order $2^{e-2}$. So $\lambda(m)=2^{e-2}$.

The proof of this lemma actually describes the structure of the reduced residue system modulo $2^e$:

???+ note "Corollary"
    Let the modulus be $2^e$ with $e \ge 2$. Then every odd number is congruent to exactly one integer of the form $\pm 5^k$, where $k\in\mathbf N$ and $k < 2^{e-2}$. That is, $\pm 1,\pm 5,\cdots,\pm 5^{2^{e-2}-1}$ are pairwise incongruent and form a reduced residue system.

??? note "Proof"
    The case $e=2$ is easy to check. For $e \ge 3$, the proof above already shows that the order of $5$ modulo $2^e$ is $2^{e-2}$, so $1,5,\cdots,5^{2^{e-2}-1}$ are pairwise incongruent. Since all these integers are $1$ modulo $4$ and their negatives are all $3$ modulo $4$, the numbers $\pm 1,\pm 5,\cdots,\pm 5^{2^{e-2}-1}$ are pairwise incongruent modulo $2^e$. There are $2^{e-1}$ of them, exactly the size of the reduced residue system modulo $2^{e}$, so they form the reduced residue system itself.

Next, handle powers of odd primes.

???+ note "Lemma"
    For $m=p^e$, where $p$ is an odd prime and $e\in\mathbf N_+$, $\lambda(m)=p^{e-1}(p-1)$.

??? note "Proof"
    First prove the claim for $e=1$, that is, when $m=p$ is an odd prime. By the definition of the Carmichael function, every integer $a$ coprime to $p$ is a solution of $x^{\lambda(p)}\equiv 1\pmod{p}$. Modulo $p$, this equation has $p-1$ distinct solutions. By [Lagrange's theorem](./congruence-equation.md#素数模同余方程), $p-1\le\lambda(p)$. Also, Euler's theorem requires $\lambda(p)\mid\varphi(p)=p-1$. So $\lambda(p)=p-1$.
    
    For $m=p^e$ with $e> 1$, start by showing that $1+p$ has order $p^{e-1}$. Indeed,
    
    $$
    (1+p)^{p^{e-1}} \equiv 1,\quad (1+p)^{p^{e-2}} \equiv 1 + p^{e-1} \not\equiv 1 \pmod{p^e}.
    $$
    
    So $\delta_m(1+p)=p^{e-1}$. Also, let $g$ be a primitive root modulo $p$. Since $g^{\delta_m(g)}\equiv 1 \pmod{p}$, [Property 2](#cyclic-structure-of-powers) of the order gives $p-1\mid\delta_m(g)$. By the definition of the Carmichael function and Euler's theorem,
    
    $$
    p^{e-1}(p-1) \mid [\delta_m(1+p),\delta_m(g)] \mid \lambda(m) \mid \varphi(m) = p^{e-1}(p-1).
    $$
    
    So $\lambda(m)=p^{e-1}(p-1)$.

Summing up the results of this section gives the recursive formula for the Carmichael function:

???+ note "Theorem"
    For any positive integer $m$,
    
    $$
    \lambda(m) = \begin{cases}
    \varphi(m), & \text{if }m=1,2,4,p^e\text{ for odd prime }p\text{ and }e \ge 1,\\
    \frac{1}{2}\varphi(m), &\text{if }m=2^e,~e\ge 3,\\
    \operatorname{lcm}\{\lambda(p_1^{e_1}),\lambda(p_2^{e_2}),\cdots,\lambda(p_s^{e_s})\}, &\text{if }m = p_1^{e_1}p_2^{e_2}\cdots p_s^{e_s}\text{ for distinct }p_1,p_2,\cdots,p_s.
    \end{cases}
    $$

This recursive formula strengthens the earlier result:

???+ note "Corollary"
    For positive integers $m_1,m_2$, $\lambda([m_1,m_2])=[\lambda(m_1),\lambda(m_2)]$.

Comparing the definitions of primitive roots and the Carmichael function, a primitive root modulo $m$ exists if and only if $\lambda(m)=\varphi(m)$. The recursive formula for the Carmichael function easily gives the following result:

???+ note "Corollary"
    A primitive root modulo $m$ exists if and only if $m=1,2,4,p^e,2p^e$, where $p$ is an odd prime and $e\in\mathbf N_+$.

Since the proof of the recursive formula in this section did not use the existence theorem for primitive roots, this gives another proof of that theorem.

### Carmichael numbers

The Carmichael function lets us discuss the properties and distribution of Carmichael numbers (OEIS: [A002997](https://oeis.org/A002997)). These are the composites that the [Fermat primality test](./prime.md#fermat-素性测试) can never correctly rule out.

???+ abstract "Carmichael number"
    A composite $n$ is called a **Carmichael number** if the congruence $a^{n-1} \equiv 1 \pmod n$ holds for all integers $a\perp n$.

The smallest Carmichael number is $561 = 3 \times 11 \times 17$.

By the definition of the Carmichael function, a composite $n$ is a Carmichael number if and only if $\lambda(n)\mid n-1$, where $\lambda(n)$ is the Carmichael function. Going further, we get the following way to decide whether a composite $n$ is a Carmichael number:

???+ note "Korselt's criterion[^korselt1899probleme]"
    A composite $n$ is a Carmichael number if and only if $n$ is squarefree and $(p-1) \mid (n-1)$ for every prime factor $p$ of $n$.

??? note "Proof"
    First, necessity. Suppose $\lambda(n)\mid (n-1)$. Checking the recursive formula for the Carmichael function shows that if $n$ has a square factor $p^2$, then $p\mid \lambda(n)$. But $p\nmid (n-1)$, a contradiction. Similarly, for any prime factor $p$ of $n$, the recursive formula shows $(p-1)\mid \lambda(n)$, so $(p-1) \mid (n-1)$ as well.
    
    Next, sufficiency. Since $n$ is a squarefree composite, it has at least two distinct prime factors, so it has an odd prime factor $p$. From $(p-1)\mid(n-1)$, $n-1$ is even, so $n$ is odd. For a squarefree odd composite $n$, the recursive formula gives $\lambda(n)=\operatorname{lcm}\{p-1:p\mid n\}$. So as long as $(p-1) \mid (n-1)$ for every prime factor $p$, we have $\lambda(n)\mid (n-1)$.

From this criterion, we get some simple properties of Carmichael numbers:

???+ note "Corollary"
    Carmichael numbers are odd, squarefree, and have at least $3$ distinct prime factors.

??? note "Proof"
    The first two properties follow directly from Korselt's criterion and its proof. For the third, it remains to show that a product $n=p_1p_2$ of two distinct primes $p_1,p_2$ is never a Carmichael number. Suppose $n=p_1p_2$ is a Carmichael number. By Korselt's criterion, $(p_i-1)\mid (n-1)$. But
    
    $$
    n-1=p_1p_2-1\equiv p_2-1 \pmod{p_1-1}.
    $$
    
    So $(p_1-1)\mid(p_2-1)$. Similarly, $(p_2-1)\mid(p_1-1)$. That is, $p_1=p_2$, contradicting the assumption. So a Carmichael number $n$ has at least $3$ distinct prime factors.

Analytic number theory gives some further properties of the distribution of Carmichael numbers. Let $C(n)$ be the number of Carmichael numbers less than or equal to $n$. Alford, Granville, and Pomerance[^alford1994infinitely] proved that $C(n)>n^{2/7}$ for sufficiently large $n$. So there are infinitely many Carmichael numbers. Before that, Erdős[^erdos1956pseudoprimes] had already proved $C(n) < n\exp\left(-c\dfrac{\ln n\ln\ln\ln n}{\ln\ln n}\right)$, where $c$ is a constant. So Carmichael numbers are very sparse (compared with primes). In fact,[^pinchcarmichael] $C(10^9)=646$ and $C(10^{18})=1~401~644$.

## References and notes

-   [Primitive root modulo n - Wikipedia](https://en.wikipedia.org/wiki/Primitive_root_modulo_n)
-   [The order of a unit - Course Notes](https://crypto.stanford.edu/pbc/notes/numbertheory/order.html)
-   [The primitive root theorem - Amin Witno's notes](http://witno.com/philadelphia/notes/won5.pdf)
-   [Carmichael function - Wikipedia](https://en.wikipedia.org/wiki/Carmichael_function)
-   [Carmichael's Lambda Function - Brilliant Math & Science Wiki](https://brilliant.org/wiki/carmichaels-lambda-function/)
-   [Carmichael number - Wikipedia](https://en.wikipedia.org/wiki/Carmichael_number)
-   [Carmichael Number - Wolfram MathWorld](https://mathworld.wolfram.com/CarmichaelNumber.html)

[^yuan1959note]: Wang Y. "On the least primitive root of a prime." (in Chinese). Acta Math Sinica, 1959, 4: 432–441; English transl. in*Sci. Sinica*, 1961, 10: 1–14.

[^burgess1962character]: BURGESS, David A. "On character sums and primitive roots." Proceedings of the London Mathematical Society, 1962, 3.1: 179-192.

[^cohen1974least]: Cohen, S. D., R. W. K. Odoni, and W. W. Stothers. "On the least primitive root modulo $p^2$." Bulletin of the London Mathematical Society 6, no. 1 (1974): 42-46.

[^elliott1998least]: Elliott, P. D. T. A., and L. Murata. "The least primitive root mod $2p^2$." Mathematika 45, no. 2 (1998): 371-379.

[^fridlender1949least]: FRIDLENDER, V. R. "On the least n-th power non-residue." Dokl. Akad. Nauk SSSR. 1949. p. 351-352.

[^salie1949kleinsten]: SALIÉ, Hans. "Über den kleinsten positiven quadratischen Nichtrest nach einer Primzahl." Mathematische Nachrichten, 1949, 3.1: 7-8.

[^burgess1968average]: Burgess, D. A., and P. D. T. A. Elliott. "The average of the least primitive root." Mathematika 15, no. 1 (1968): 39-50.

[^elliott1997average]: Elliott, Peter DTA, and Leo Murata. "On the average of the least primitive root modulo p." Journal of The London Mathematical Society 56, no. 3 (1997): 435-454.

[^more-evidence]: For more results, see [Least prime primitive root of prime numbers](https://sweet.ua.pt/tos/p_roots.html).

[^density-prim-root]: If a primitive root modulo $m$ exists, then $\varphi(m)\ge\dfrac{1}{3}m$, with equality only at $m=2\times 3^e~(e\in\mathbf N_+)$. Moreover, for $m > 2$, Euler's totient function satisfies the estimate $\varphi(m)>\dfrac{m}{e^{\gamma}\log\log m+\frac{3}{\log\log m}}$. Combining the two gives the expression in the text. For this estimate of Euler's totient function, see Rosser, J. Barkley, and Lowell Schoenfeld. "Approximate formulas for some functions of prime numbers." Illinois Journal of Mathematics 6, no. 1 (1962): 64-94.

[^korselt1899probleme]: Korselt, A. R. (1899). "Problème chinois." L'Intermédiaire des Mathématiciens. 6: 142–143.

[^alford1994infinitely]: W. R. Alford; Andrew Granville; Carl Pomerance (1994). "There are Infinitely Many Carmichael Numbers." Annals of Mathematics. 140 (3): 703–722.

[^erdos1956pseudoprimes]: Erdős, P. (1956). "On pseudoprimes and Carmichael numbers." Publ. Math. Debrecen. 4 (3–4): 201–206.

[^pinchcarmichael]: PINCH, Richard GE. The Carmichael numbers up to ${10}^{20}$.
