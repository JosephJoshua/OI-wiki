author: jifbt, billchenchina, Enter-tainer, Great-designer, iamtwz, ImpleLee, isdanni, Menci, ouuan, Tiphereth-A, warzone-oier, Xeonacid, c-forrest

This chapter gives a short introduction to abstract algebra. Competitive programming today does not directly test abstract algebra. However, basic concepts from abstract algebra often come up when describing algorithms or in problem editorials, so readers who know these basic concepts can understand some algorithms faster. So this material is not required for any contestant; it is just a reference for readers who are interested or who may benefit from it. This chapter also avoids covering abstract algebra too broadly or too deeply[^oi-wiki-not-wikipedia]. Instead, it focuses on the basic concepts and on the parts most closely connected to the rest of OI. Readers who want to learn abstract algebra systematically should study a proper abstract algebra textbook.

To help readers see what they might gain from this part, here are some examples where abstract algebra shows up in competitive programming:

-   Many theorems in number theory and polynomials are special cases of results in abstract algebra;
-   In data structures, structures such as the [segment tree](../../ds/seg.md) can maintain information from a monoid, and the recurrences of many DP problems can be abstracted into such a monoid structure;
-   In combinatorics, the rigorous statement and proof of the [Pólya enumeration theorem](../combinatorics/polya.md) need concepts from group theory.

With this in mind, this chapter focuses on the basics that cannot be skipped and on the parts directly related to these applications. To start, this article introduces the basic concepts of groups, rings and fields.

## Groups

A group is defined as follows.

???+ abstract "Group"
    Let $G$ be a non-empty set with a binary operation $\cdot:G\times G\rightarrow G$. If they satisfy the following properties, then $(G,\cdot)$ is called a **group**:
    
    1.  Associativity (associative property): for all $a,b,c\in G$, $a\cdot(b\cdot c)=(a\cdot b)\cdot c$ holds;
    2.  Existence of an identity: there is an $e\in G$ such that $a\cdot e = e\cdot a = a$ for every $a\in G$. Here $e$ is called the **identity element** of $G$ (also called the unit element);
    3.  Existence of inverses: for every $a\in G$, there is a corresponding $b\in G$ such that $a\cdot b=b\cdot a=e$. Here $b$ is called the **inverse element** of $a$.

??? info "About the closure condition in the definition"
    The binary operation here already implies the so-called closure condition: for any $a,b\in G$, we have $a\cdot b\in G$. Some texts list it as a separate condition.

???+ note "Basic properties of groups"
    For a group $(G,\cdot)$, the following properties always hold:
    
    1.  For any finite sequence $\{g_i\}_{i=1}^k\subseteq G$, the result of the product $g_1\cdot g_2\cdot\cdots\cdot g_k$ does not depend on how the parentheses are placed;
    2.  The identity element $e$ is always unique;
    3.  For any element $a\in G$, its inverse $a^{-1}$ is also unique;
    4.  Cancellation law: for $a,b,c\in G$, if $a\cdot c=b\cdot c$ or $c\cdot a=c\cdot b$, then $a=b$.

Groups are very common. Informally, all transformations that preserve some structure automatically form a group. Here are some common kinds of groups as examples.

???+ example "Examples of groups"
    -   **Symmetric group**: all [permutations](../permutation.md) of a set $M$, that is, all bijections from $M$ to itself, form a group $S_M$ under composition of maps. The identity element is the identity map, and the inverse is the inverse map (a bijection always has an inverse map). If $M$ is finite with size $n$, the group is often written $S_n$ and called the symmetric group of degree $n$.
    -   Symmetry group: for a geometric figure, all transformations that map the figure onto itself also form a group under composition of maps. This describes the spatial symmetry of the figure. For concrete examples, see [common symmetry groups](../combinatorics/polya.md#common-symmetry-groups).
    -   The additive group of integers: the set of integers $\mathbf Z$ forms a group $(\mathbf Z,+)$ under addition $+$. The identity element is $0$, and the inverse of a number is its negative.
    -   Multiplicative group of integers modulo $n$: for a modulus $n$, the [residue classes](../number-theory/basic.md#residue-classes-and-residue-systems) of all integers coprime to $n$ form a group $((\mathbf Z/n\mathbf Z)^\times,\times)$ under multiplication. The identity element is $\bar 1$, and the inverse is (the residue class of) the [modular multiplicative inverse](../number-theory/inverse.md) modulo $n$, whose existence is guaranteed by [Bézout's identity](../number-theory/bezouts.md). For an analysis of its structure, see [multiplicative group of integers modulo $n$](./ring-theory.md#application-the-multiplicative-group-of-integers-modulo-n).
    -   General linear group: all invertible $n\times n$ square matrices over a field $F$ form a group $GL_n(F)$ under multiplication. The identity element is the identity matrix, and the inverse is the inverse matrix.

To understand the definition of a group better, it helps to compare with some examples that are not groups.

???+ example "Examples that are not groups"
    -   The set of all maps from $M$ to itself (not necessarily bijections) is not a group, because maps that are not bijections have no inverse.
    -   The integers do not form a group under multiplication, because $2$ has no multiplicative inverse among the integers.
    -   The positive integers do not form a group under addition either, because the positive integers have no additive identity.
    -   The non-zero residue classes modulo $n$ often do not form a group under multiplication. For example, in $(\mathbf Z/6\mathbf Z)\setminus\{\overline 0\}$, $\overline 2\times\overline 3=\overline 0$ is not in the set. This means multiplication is not a well-defined binary operation on this set (in other words, it does not satisfy closure).

Sometimes we also need to study these less complete structures. So we can define the following concepts, which are broader than groups.

???+ abstract "Semigroup"
    For a non-empty set $G$ with a binary operation $\cdot$, if the operation is associative, then $(G,\cdot)$ is called a **semigroup**.

???+ abstract "Monoid"
    For a semigroup $(G,\cdot)$, if it also has an identity element, then $(G,\cdot)$ is called a **monoid**.

???+ example "Examples of monoids and semigroups"
    Among the examples above, $(\mathbf N_+,+)$ is a semigroup, and $(\mathbf Z,\times)$ is a monoid.

Finally, in many familiar groups the operation is not only associative but also commutative. These groups have a relatively simple structure. They are called Abelian groups, or commutative groups.

???+ abstract "Abelian group"
    For a group $(G,\cdot)$, if the operation $\cdot$ is also commutative (commutative property), that is, $a\cdot b=b\cdot a$ holds for all $a,b\in G$, then $(G,\cdot)$ is called an **Abelian group** or a **commutative group**.

???+ example "Examples of Abelian and non-Abelian groups"
    -   The additive group of integers $(\mathbf Z,+)$ is an Abelian group.
    -   For $n\ge3$, the symmetric group $S_n$ is not an Abelian group.

These are the basic definitions of group theory. For more on group theory, see [Group theory](./group-theory.md) or related books.

## Rings

A ring is defined as follows.

???+ abstract "Ring"
    For a non-empty set $R$ with two binary operations $+:R\times R\rightarrow R$ and $\cdot:R\times R\rightarrow R$, if they satisfy the following properties, then $(R,+,\cdot)$ is called a **ring**:
    
    1.  $(R,+)$ is an Abelian group. Its identity element is written $0$, and the inverse of an element $a\in R$ under $+$ is written $-a$.
    2.  $(R,\cdot)$ is a semigroup, that is, $\cdot$ is associative.
    3.  Distributivity (distributive property): for all $a,b,c\in R$, $a\cdot(b+c)=a\cdot b+a\cdot c$ and $(a+b)\cdot c=a\cdot c+b\cdot c$ hold.

For convenience, the two binary operations $+$ and $\cdot$ are often called the addition and multiplication of the ring. Accordingly, the additive identity is called the **zero**, and the multiplicative identity (if it exists) is called the **identity**. Don't confuse these with addition and multiplication in concrete number sets, or with the natural numbers zero and one.

??? info "Whether the definition requires a multiplicative identity"
    In some definitions, a ring must have a multiplicative identity; a structure without one is then called a **rng** (or pseudo-ring). When you meet the term, judge from the context. Wikipedia uses this definition[^ring-wiki].

The additive structure of a ring is quite simple, but its multiplicative structure is very primitive. So, by analogy with groups, we can put more requirements on the multiplication and get the following related definitions.

???+ abstract "Ring with identity"
    For a ring $(R,+,\cdot)$, if it has a multiplicative identity, written $1$, then $(R,+,\cdot)$ is called a **ring with identity**.

???+ abstract "Division ring"
    For a non-zero ring with identity $(R,+,\cdot)$, if every non-$0$ element $a\in R$ has a multiplicative inverse (written $a^{-1}$), then $(R,+,\cdot)$ is called a **division ring**.

???+ abstract "Commutative ring"
    For a ring $(R,+,\cdot)$, if its multiplication is commutative, then $(R,+,\cdot)$ is called a **commutative ring**.

An interesting point in the definition of a division ring is that it treats $0$ as a special element in the multiplicative structure. This is because $0 = 0\cdot a = a\cdot 0$[^zero-multiplication]. In other words, the additive identity of a ring times any element gives the additive identity itself. So it naturally has no multiplicative inverse, unless it is itself the multiplicative identity. The only such ring is the zero ring (see the examples below).

The lesson here is that to understand the multiplicative structure of a general ring, you should remove the effect of the additive identity and look at $R\setminus\{0\}$. Based on this idea, we have the following definitions.

???+ abstract "Zero divisor"
    For a ring $(R,+,\cdot)$, a non-zero element $a$ is called a **zero divisor** if there is some $b\in R$ with $b\ne 0$ such that $a\cdot b=0$ or $b\cdot a=0$.

???+ abstract "Invertible element (unit)"
    For a ring $(R,+,\cdot)$, an element $a\in R$ is called an **invertible element**, or a **unit**, if $a$ has a multiplicative inverse, that is, there is $b\in R$ such that $a\cdot b=b\cdot a=1$.

???+ warning "Unit vs. identity element"
    Please do not confuse these two concepts. To avoid confusion, the abstract algebra section uses the name "invertible element" instead of "unit".

A zero divisor can never be invertible, and an invertible element can never be a zero divisor. However, a non-zero element may be neither a zero divisor nor invertible.

If a ring has no zero divisors, then the set of all non-zero elements is closed under multiplication, that is, $(R\setminus\{0\},\cdot)$ is a semigroup. If we further require it to be a commutative monoid, we get the definition of an integral domain.

???+ abstract "Integral domain"
    A non-zero ring $(R,+,\cdot)$ is called an integral domain if it is commutative, has a multiplicative identity, and has no zero divisors.

Although elements of an integral domain need not have inverses, having no zero divisors is already enough to establish a cancellation law in an integral domain.

???+ note "Cancellation law in an integral domain"
    Let $R$ be an integral domain with elements $a,b,c\in R$ and $a\neq 0$. If $ab=ac$, then $b=c$.

For a general ring with identity, if we look only at all of its invertible elements, we again get a group structure. This is called the multiplicative group, or the unit group, of the ring.

???+ abstract "Multiplicative group (unit group)"
    For a ring with identity $(R,+,\cdot)$, let $R^\times$ be the set of all invertible elements of $R$. Then $(R^\times,\cdot)$ is a group, called the **multiplicative group**, or the **unit group**, of the ring $R$.

Here are some of the simplest examples of rings.

???+ example "Examples of rings"
    -   Zero ring: the set $\{0\}$ forms a ring under the usual addition $+$ and multiplication $\times$, called the zero ring. It is the only ring with exactly one element, and also the only ring whose additive identity equals its multiplicative identity.
    -   Ring of integers: the set of integers $\mathbf Z$ with the usual addition $+$ and multiplication $\times$ forms a ring $(\mathbf Z,+,\times)$. In fact, it is an integral domain, but it is not a division ring.
    -   Polynomial ring: for a ring $R$, we can define the [polynomial ring](./ring-theory.md#polynomial-rings)  $R[x]$ over it. If $R$ is an integral domain, then this polynomial ring is also an integral domain.
    -   Quaternions: by analogy with complex numbers, consider the set $\mathbf H=\{a+b\mathrm{i}+c\mathrm{j}+d\mathrm{k}:a,b,c,d\in\mathbf R\}$ and define addition and multiplication on it, where multiplication of $\mathrm{i},\mathrm{j},\mathrm{k}$ satisfies
    
        $$
        \mathrm{i}^2=\mathrm{j}^2=\mathrm{k}^2=-1,\ \mathrm{i}\mathrm{j}=-\mathrm{j}\mathrm{i}=\mathrm{k},\ \mathrm{j}\mathrm{k}=-\mathrm{k}\mathrm{j}=\mathrm{i},\ \mathrm{k}\mathrm{i}=-\mathrm{i}\mathrm{k}=\mathrm{j}.
        $$
    
        Then one can check that $\mathbf H$ is a ring, and moreover, it is a non-commutative division ring.
    -   The subset $2\mathbf Z$ of the integers forms a ring under the usual addition and multiplication. It is commutative and has no zero divisors, but it has no identity.
    -   The residue classes of integers modulo $n$, $\mathbf Z/n\mathbf Z$, form a ring under addition and multiplication of residue classes. It is commutative and has an identity ($\bar 1$). This ring has zero divisors if and only if $n$ is composite. So when $n$ is prime, the ring $(\mathbf Z/n\mathbf Z, +,\times)$ is an integral domain; moreover, it is then also a division ring, so it is actually a field. Its multiplicative group $((\mathbf Z/n\mathbf Z)^\times,\times)$ is exactly the multiplicative group of integers modulo $n$.
    -   Matrix ring: all $n\times n$ square matrices over a ring $R$ form a ring $M_n(R)$ under matrix addition and multiplication. In general, this ring has zero divisors and is not commutative.
    -   For the set $\mathcal P(A)$ of all subsets of a set $A$, if we use the symmetric difference $\triangle$ as addition and the intersection $\cap$ as multiplication, then $(\mathcal P(A),\triangle,\cap)$ is a ring. In general, this ring has an identity, has zero divisors, and is commutative.

Of course, there is much more to say about the structure of rings. To learn more, see [Ring theory](./ring-theory.md) or related books.

## Fields

A field is an algebraic structure with stronger properties than a ring. Specifically, a field is a commutative division ring. We can also write out its full definition.

???+ abstract "Field"
    For a non-empty set $F$ with two binary operations $+:F\times F\rightarrow F$ and $\cdot:F\times F\rightarrow F$, if they satisfy the following properties, then $(F,+,\cdot)$ is called a **field**:
    
    1.  $(F,+)$ is an Abelian group. Its identity element is written $0$, and the inverse of an element $a\in F$ under $+$ is written $-a$.
    2.  $(F\setminus\{0\},\cdot)$ is an Abelian group. Its identity element is written $1$, and the inverse of an element $a\in F\setminus\{0\}$ under $\cdot$ is written $a^{-1}$.
    3.  Distributivity: for all $a,b,c\in F$, $a\cdot(b+c)=a\cdot b+a\cdot c$ holds.

In other words, a field is an algebraic structure closed under all four arithmetic operations: addition, subtraction, multiplication and division.

Here are some common examples of fields.

???+ example "Examples of fields"
    -   Number fields: the rational numbers $\mathbf Q$, the real numbers $\mathbf R$ and the complex numbers $\mathbf C$ all form fields under the usual addition and multiplication.
    -   Finite field: the set $\mathbf Z/p\mathbf Z$ of residue classes of integers modulo a prime $p$ forms a field under addition and multiplication of residue classes. Of course, there are other finite fields too. Their structure is uniquely determined by their size, and the size must be a prime power.
    -   **Fraction field**: let $(R,+,\cdot)$ be an integral domain. Consider the set $Q$ of elements of the form $ab^{-1}$. Strictly speaking, define an equivalence relation on the set $R\times(R\setminus\{0\})$: $(a_1,b_1)\sim(a_2,b_2)$ if and only if $a_1b_2=a_2b_1$. Then the set $Q$ is the set of equivalence classes under this relation, $R\times(R\setminus\{0\})/\sim$, and the equivalence class containing $(a,b)$ is written $ab^{-1}$. If we define the operations on it as
    
        $$
        \begin{aligned}
        a_1b_1^{-1}+a_2b_2^{-1} &= (a_1\cdot b_2+a_2\cdot b_1)(b_1\cdot b_2)^{-1},\\
        (a_1b_1^{-1})\cdot(a_2b_2^{-1}) &= (a_1\cdot a_2)(b_1\cdot b_2)^{-1}
        \end{aligned}
        $$
    
        then $(Q,+,\cdot)$ is a field, called the fraction field of $R$. For example, the field of rational numbers $(\mathbf Q,+,\times)$ is the fraction field of the ring of integers $(\mathbf Z,+,\times)$.
    -   Quadratic field: it is the extension of the field of rational numbers $\mathbf Q$ obtained by adding $\sqrt d$, where $d\neq 0,1$ and $d$ has no square factors. For more, see [Quadratic fields](../number-theory/quadratic.md).

Compared with rings, fields have very simple additive and multiplicative structures. So the structure of a field itself is often simple. This makes the study of fields quite different from the study of rings: it usually turns to field extensions and the related Galois theory. In competitive programming, you sometimes need to compute in extensions of the rational numbers or of finite fields. For field theory, see [Field theory](./field-theory.md) or related books.

## Applications

Finally, let's use the following problem to show how abstract algebraic objects can help analyze a concrete problem.

???+ note "[Template: Dynamic DP & Dynamic Tree Divide and Conquer (Enhanced Version)](https://www.luogu.com.cn/problem/P4751)"
    Given a tree of size $n$ with vertex weights, perform $m$ vertex weight updates. After each update, output the total weight of the maximum-weight independent set of the tree. The problem must be solved online.

???+ note "Analysis"
    This problem is the dynamic DP template problem. An implementation with the correct complexity needs the [global balanced binary tree](../../ds/global-bst.md); sample code is on that page. Here we only analyze how to model the problem in this setting.
    
    To focus on the key idea, let's ignore for now how the global balanced binary tree handles the tree structure, and instead consider the DP for the maximum-weight independent set on a chain. Go through the vertices of the chain $[1,n]$ in order. Each vertex $i$ can be chosen ($1$) or not chosen ($0$). Let the optimal values of the subproblem on $[1,i]$ in these two cases be $f_{i,1}$ and $f_{i,0}$. Then the DP equations are
    
    $$
    \begin{aligned}
    f_{i,1}&=w_{i}+f_{i-1,0},\\
    f_{i,0}&=\max\{f_{i-1,1},f_{i-1,0}\}.
    \end{aligned}
    $$
    
    The initial value is $(f_{0,1},f_{0,0})=(0,0)$, and the final answer is $\max\{f_{n,1},f_{n,0}\}$. To express the effect of vertex $i$ on the final result, just note that the recurrence can be written as
    
    $$
    (f_{i,1},f_{i,0})=g(f_{i-1,1},f_{i-1,0};w_i).
    $$
    
    This is a series of maps from $\mathbf R^2$ to $\mathbf R^2$, each mapping $(f_{i-1,1},f_{i-1,0})$ to $(f_{i,1},f_{i,0})$. In the language of groups, these transformations form a monoid under composition of maps. This is exactly what a segment tree can maintain.
    
    However, unless the parameterized transformation $g(\cdot;w_i)$ has special structure, a general map from $\mathbf R^2$ to $\mathbf R^2$ cannot be described with finite-dimensional data. Here we need one more observation: if on $\mathbf R\cup\{-\infty\}$ we define $\max$ as addition and $+$ as multiplication, then $\mathbf R\cup\{-\infty\}$ forms a ring-like structure, where $-\infty$ is the additive identity and $0$ is the multiplicative identity. But it is not a ring, because not every element has an additive inverse. Such a structure is called a semiring[^semiring], and the semiring $(\mathbf R\cup\{-\infty\},\max,+)$ here is called the **tropical semiring**.
    
    Over the tropical semiring $(R,\oplus,\otimes)$, we can define matrix multiplication. For an $m\times n$ matrix $A=(a_{ij})$ and an $n\times p$ matrix $B=(b_{jk})$, define their product $AB$ as $(c_{ik})$, where each entry is
    
    $$
    c_{ik} = \bigoplus_{j=1}^n(a_{ij}\otimes b_{jk}) = \max_{1\le j\le n}\;(a_{ij}+b_{jk}).
    $$
    
    With this notation, the recurrence above can be viewed as a linear transformation over the tropical semiring, and written in matrix form as
    
    $$
    \left(\begin{matrix}f_{i,1}\\f_{i,0}\end{matrix}\right)
    =\left(\begin{matrix}-\infty&w_i\\0&0\end{matrix}\right)\left(\begin{matrix}f_{i-1,1}\\f_{i-1,0}\end{matrix}\right).
    $$
    
    So by maintaining the product of these matrices over the tropical semiring with a segment tree, we can answer the dynamic DP problem on a chain with many updates.
    
    Now return to the tree version of the problem. For a vertex $i$ of the tree, let $S(i)$ be its set of children. Then the DP equations there are
    
    $$
    \begin{aligned}
    f_{i,1}&=w_i+\sum_{j\in S(i)}f_{j,0},\\
    f_{i,0}&=\sum_{j\in S(i)}\max\{f_{j,1},f_{j,0}\}.
    \end{aligned}
    $$
    
    First, use heavy-light decomposition to turn the problem into the chain version. Let $h$ be the heavy child of $i$. Then the recurrence above can be written as
    
    $$
    \begin{aligned}
    f_{i,1}&=w_i+f_{h,0}+g_{i,1},\\
    f_{i,0}&=\max\{f_{h,0},f_{h,1}\}+g_{i,0},
    \end{aligned}
    $$
    
    where
    
    $$
    \begin{aligned}
    g_{i,1}&=\sum_{j\in S(i),\ j\neq h}f_{j,0},\\
    g_{i,0}&=\sum_{j\in S(i),\ j\neq h}\max\{f_{j,1},f_{j,0}\}
    \end{aligned}
    $$
    
    sum up the contributions of the light children. As described above, all these transformations can be written as matrices over the tropical semiring, so the whole problem can be maintained with a segment tree on top of the heavy-light decomposition. However, a single update with plain HLD plus a segment tree takes $O(\log^2n)$, so the global balanced binary tree mentioned above is needed to bring it down to $O(\log n)$. Of course, an LCT also works.
    
    The tropical semiring and the matrix operations over it are actually not rare. If we replace $\max$ above with $\min$, the corresponding tropical semiring is often used in shortest path problems. If an $n\times n$ matrix $A$ gives the (shortest) edge weights between pairs of vertices of a graph with $n$ vertices, then the $(i,j)$ entry of $A^k$ is the shortest distance from vertex $i$ to vertex $j$ using at most $k$ edges; in particular, $A^n$ is the distance matrix of the graph. Of course, in practice we do not actually compute this matrix power by brute force; instead we use the Floyd algorithm, which runs in $O(n^3)$.

## References and notes

-   Dummit, D.S. and Foote, R.M. (2004) Abstract Algebra. 3rd Edition, John Wiley & Sons, Inc.
-   [Tropical semiring - Wikipedia](https://en.wikipedia.org/wiki/Tropical_semiring)

[^oi-wiki-not-wikipedia]: Because [OI Wiki is not an encyclopedia](../../intro/what-oi-wiki-is-not.md#oi-wiki-is-not-an-encyclopedia).

[^ring-wiki]: [Ring (mathematics) - Wikipedia](https://en.wikipedia.org/wiki/Ring_%28mathematics%29)

[^zero-multiplication]: The derivation is $0\cdot a+0 = 0\cdot a = (0+0)\cdot a = 0\cdot a + 0\cdot a$. Here the first and second equalities follow from the definition of the additive identity, the third equality is distributivity, and the final implication is the cancellation law for addition. The multiplication on the other side is similar.

[^semiring]: A semiring is the algebraic structure obtained from the definition of a ring with identity by dropping the requirement that every element has an additive inverse. That is, its additive structure is a commutative monoid and its multiplicative structure is a monoid. For more, see [Wikipedia](https://en.wikipedia.org/wiki/Semiring).
