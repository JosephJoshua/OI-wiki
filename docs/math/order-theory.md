## Introduction

Order theory is the branch of mathematics that makes the idea of "order" precise using binary relations. Below we introduce the basic definitions of this branch.

## Definitions

### Binary relations

???+ note "Definition"
    A **binary relation** $R$ over sets $X$ and $Y$ is a tuple $(X,Y,G(R))$, where $X$ is called the domain, $Y$ is called the codomain, and $G(R)\subseteq X\times Y=\{(x,y):x\in X,y\in Y\}$ is called the graph of $R$. $xRy$ holds if and only if $(x,y)\in G(R)$.
    
    If $X=Y$, the relation is called a homogeneous relation or an endorelation.
    
    Unless stated otherwise, all binary relations below are homogeneous.

For example, divisibility $\mid$ and less-than-or-equal $\leq$ on $\mathbf{N}_+$ are both binary relations.

When studying binary relations, we often care whether they have certain special properties. For a binary relation $R$ on a set $S$, we define the following properties:

1.  Reflexive: $(\forall~a \in S)~~aRa$,
2.  Irreflexive (anti-reflexive): $(\forall~a \in S)~~\lnot(aRa)$,
3.  Symmetric: $(\forall~a,b \in S)~~aRb \iff bRa$,
4.  Antisymmetric: $(\forall~a,b \in S)~~(aRb \land bRa) \implies a=b$,
5.  Asymmetric: $(\forall~a,b \in S)~~aRb \implies \lnot(bRa)$,
6.  Transitive: $(\forall~a,b,c \in S)~~(aRb \land bRc) \implies aRc$,
7.  Connected: $(\forall~a,b \in S)~~a \neq b \implies (aRb \lor bRa)$,
8.  Well-founded: $(\forall~X \subseteq S)~~X \neq \varnothing \implies(\exists~m \in X)~~(\forall~a \in X\setminus\{m\})~~\lnot(aRm)$ (that is, every non-empty set $X$ has a minimal element $m$),
9.  Transitive of incomparability: $(\forall~a,b,c \in S)~~(\lnot(aRb \lor bRa) \land \lnot(bRc \lor cRb)) \implies \lnot(aRc \lor cRa)$ (if $\lnot(aRb \lor bRa)$, we say $a$ and $b$ are incomparable).

We also define some special kinds of binary relations:

| Binary relation | Reflexive | Irreflexive | Symmetric | Antisymmetric | Asymmetric | Transitive | Connected | Well-founded | Transitive of incomparability |
| --------------------------- | --- | ---- | --- | ---- | ---- | --- | --- | --- | ------- |
| Equivalence relation  | Yes   |      | Yes   |      |      | Yes   |     |     |         |
| Preorder (quasi-order) | Yes   |      |     |      |      | Yes   |     |     |         |
| Partial order           | Yes   |      |     | Yes    |      | Yes   |     |     |         |
| Total order             | Yes   |      |     | Yes    |      | Yes   | Yes   |     |         |
| Well-quasi-order       | Yes   |      |     |      |      | Yes   |     | Yes   |         |
| Well-order              | Yes   |      |     | Yes    |      | Yes   | Yes   | Yes   |         |
| Strict preorder       |     | Yes    |     |      |      | Yes   |     |     |         |
| Strict partial order  |     | Yes    |     |      | Yes    | Yes   |     |     |         |
| Strict weak order     |     | Yes    |     |      | Yes    | Yes   |     |     | Yes       |
| Strict total order    |     | Yes    |     |      | Yes    | Yes   | Yes   |     |         |

### Operations on relations

For binary relations $R$ and $S$ over sets $X$ and $Y$, we can define the following operations:

1.  The union $R\cup S$ of $R$ and $S$ satisfies $G(R\cup S):=\{(x,y):xRy \lor xSy\}$ (for example, $\leq$ is the union of $<$ and $=$),
2.  The intersection $R\cap S$ of $R$ and $S$ satisfies $G(R\cap S):=\{(x,y):xRy \land xSy\}$,
3.  The complement $\bar{R}$ of $R$ satisfies $G(\bar{R}):=\{(x,y):\lnot(xRy)\}$,
4.  The converse $R^T$ of $R$ satisfies $G(R^T):=\{(y,x):xRy\}$.

For a binary relation $R$ over sets $X$ and $Y$ and a binary relation $S$ over sets $Y$ and $Z$, we define their composition $S\circ R$ by $G(S\circ R):=\{(x,z):(\exists~y\in Y)~~xRy\land ySz\}$.

### Partially ordered sets

???+ note "Definition"
    If a binary relation $\preceq$ on a set $S$ is **reflexive**, **antisymmetric** and **transitive**, then $S$ is called a **partially ordered set** (poset), and $\preceq$ is a **partial order** on it.
    
    If the partial order $\preceq$ is also **connected**, it is called a **total order**, and the set is called a **totally ordered set**, a **linearly ordered set** (loset) or a **simply ordered set**.

It is easy to see that $\mathbf{N}$, $\mathbf{Z}$, $\mathbf{Q}$ and $\mathbf{R}$ are all totally ordered sets under $\leq$.

### Visualizing posets: Hasse diagrams

For a finite poset, we can draw its partial order intuitively with a Hasse diagram.

???+ note "Definition"
    For a finite poset $S$ with partial order $\preceq$, define $x\prec y\iff (x\preceq y\land x\neq y)$. Its **Hasse diagram** is the graph $G=\langle V,E\rangle$ such that:
    
    -   $V=S$,
    -   $E=\{(x,y)\in S\times S: x\prec y \land ((\nexists~z\in S)~~x\prec z\prec y)\}$

For example, for the power set $S$ of $\{0,1,2\}$ under set inclusion $\subseteq$, the Hasse diagram is:

![](images/order-theory1.svg)

Since a partial order is antisymmetric, a Hasse diagram is always a [directed acyclic graph](../graph/dag.md). So we can use [topological sort](../graph/topo.md) to extend any finite poset to a total order.

### Chains and antichains

???+ note "Definition"
    For a poset $S$ with partial order $\preceq$, a totally ordered subset of $S$ is called a **chain**. If any two distinct elements of a subset $T$ of $S$ are incomparable (that is, $(\forall~a,b \in T)~~a \neq b \implies (a \npreceq b \land b \npreceq a)$), then $T$ is called an **antichain**.
    
    For a poset $S$ with partial order $\preceq$, the length of the longest antichain of $S$ is called its **width** (partial order width).

For example, for the power set $S$ of $\{0,1,2\}$ under inclusion $\subseteq$, $\{\varnothing,\{1\},\{1,2\}\}$ is a chain, $\{\{1\},\{0,2\}\}$ is an antichain, and the width of $S$ is $3$.

### Special elements in a preordered set

In a preordered set we can define maximal (minimal) elements, upper (lower) bounds, suprema (infima) and so on. These ideas carry over to other kinds of order relations.

???+ note "Definition"
    For a preordered set $S$ with preorder $\preceq$, take an element $m$ of $S$:
    
    1.  If $(\forall~a \in S\setminus\{m\})~~\lnot(m\preceq a)$, then $m$ is a **maximal element**,
    2.  If for $T \subseteq S$ we have $(\forall~t\in T)~~t\preceq m$, then $m$ is an **upper bound** of $T$,
    3.  If for $T \subseteq S$, $m$ is an upper bound of $T$ and $m \preceq n$ for every upper bound $n$ of $T$, then $m$ is the **supremum** of $T$.
    
    **Minimal elements**, **lower bounds** and the **infimum** are defined in the same way.

For example, $1$ is a minimal element and a lower bound of $\mathbf{N}_+$.

One can prove:

-   In a preordered set, maximal (minimal) elements, upper (lower) bounds and suprema (infima) do not always exist, and even when they exist they are not always unique.

-   If a subset $T$ of a poset $S$ has a supremum (infimum), it is unique.

    We write the supremum and infimum of $T$ as $\sup T$ and $\inf T$. If a poset $S$ has both an upper bound and a lower bound, $S$ is called bounded.

In an infinite poset, a maximal element may not exist. **Zorn's lemma** can be used to decide whether an infinite poset has a maximal element.

???+ note "[Zorn's lemma](https://en.wikipedia.org/wiki/Zorn%27s_lemma)"
    **Zorn's lemma**, also called the **Kuratowski–Zorn lemma**, states: if every chain in a non-empty poset has an upper bound, then the poset has a maximal element.

Zorn's lemma is equivalent to the **[axiom of choice](https://en.wikipedia.org/wiki/Axiom_of_choice)** and the **[well-ordering theorem](https://en.wikipedia.org/wiki/Well-ordering_theorem)**.

### Directed sets and lattices

We know that if a subset of a poset has a supremum (infimum), it is unique. This is not true for maximal (minimal) elements. For example, consider the poset $S=\{\{0\},\{1\},\{2\},\{0,1\},\{0,2\},\{1,2\}\}$ under $\subseteq$. It is easy to see that it has $3$ maximal elements and $3$ minimal elements.

We want to add conditions to a poset so that a maximal (minimal) element, if it exists, is unique. Then we can define the greatest (least) element.

???+ note "Directed set"
    For a preordered set $S$ with preorder $\preceq$, if $(\forall~a,b\in S)~~(\exists~c\in S)~~a\preceq c\land b\preceq c$, then $\preceq$ is called a **direction** on $S$, and $S$ is called a **directed set** or **filtered set**.
    
    A set satisfying this definition is sometimes called an **upward directed set**. A **downward directed set** is defined in the same way.

A directed set can also be defined as follows:

???+ note "Equivalent definition of a directed set"
    For a preordered set $S$ with preorder $\preceq$, if every finite subset $T$ of $S$ has an upper bound, then $\preceq$ is a direction on $S$ and $S$ is a directed set.

It is easy to see that:

-   If an upward directed set has a maximal element, it is unique. We call the maximal element of an upward directed set its **greatest element**.
-   If a downward directed set has a minimal element, it is unique. We call the minimal element of a downward directed set its **least element**.

In a directed poset, for any elements $a,b$, the set $\{a,b\}$ has an upper bound. If we replace "upper bound" with "supremum", we get the definition of a join-semilattice.

For a poset $S$ with partial order $\preceq$:

???+ note "Join-semilattice"
    If for any elements $a,b$ of $S$, $\{a,b\}$ has a supremum $c$, then $S$ is called a **join-semilattice** (upper semilattice), and $c$ is called the **join** of $a$ and $b$, written $a\lor b$.

???+ note "Meet-semilattice"
    If for any elements $a,b$ of $S$, $\{a,b\}$ has an infimum $c$, then $S$ is called a **meet-semilattice** (lower semilattice), and $c$ is called the **meet** of $a$ and $b$, written $a\land b$.

???+ note "Lattice"
    If $S$ is both a join-semilattice and a meet-semilattice, then $S$ is called a **lattice**.

For example, the set of positive divisors of $60$, $S=\{1,2,3,4,5,6,10,12,15,20,30,60\}$, is a poset under divisibility. For any positive integers $a,b$ in it, $\operatorname{lcm}(a,b)$ is the join of $a$ and $b$ and $\gcd(a,b)$ is their meet, so $S$ is a lattice.

### Duality

Duality is a very common idea in order theory. For example, maximal and minimal elements are dual, upper and lower bounds are dual, and suprema and infima are dual.

For a poset $P$ with partial order $\preceq$, its **dual** (opposite) poset $P^d$ is defined by: $x \preceq y$ holds in $P$ if and only if $y \preceq x$ holds in $P^d$. Reversing the edges of the Hasse diagram of $P$ gives the Hasse diagram of $P^d$.

## Dilworth's theorem and Mirsky's theorem

For a finite poset $S$ with partial order $\preceq$, we have the following pair of dual theorems:

???+ note "Dilworth's theorem"
    The width of $S$ (the length of the longest antichain) equals the minimum number of chains needed to cover $S$.
    
    ??? note "Proof"
        We use induction. When $|S|\leq 3$, the statement clearly holds.
        
        Assume the statement holds for all posets with fewer than $|S|$ elements, and let the width of $S$ be $d$. If all elements of $|S|$ are pairwise incomparable, the statement clearly holds. Otherwise, take a chain of length greater than $1$ in $S$, and let $m$ be its least element and $M$ its greatest element.
        
        Let $T=S\setminus\{m,M\}$. If the width of $T$ is at most $d-1$, then by the induction hypothesis $T$ can be covered by at most $d-1$ chains, so $S$ can be covered by these chains plus the chain $\{m,M\}$, and the statement holds. Otherwise, the width of $T$ is also $d$; let $A$ be a longest antichain in $T$.
        
        Consider the following two sets:
        
        $$
        S^+:=\{x\in S:(\exists~a\in A)~~a\preceq x\}
        $$
        
        $$
        S^-:=\{x\in S:(\exists~a\in A)~~x\preceq a\}
        $$
        
        It is easy to see that:
        
        -   $S^+\cup S^-=S$,
        -   $S^+\cap S^-=A$,
        -   $|S^+|<|S|$,$|S^-|<|S|$ (because $m\notin S^+$ and $M\notin S^-$).
        
        Apply the induction hypothesis to both $S^+$ and $S^-$. Each of them has a minimum chain cover of $d$ chains, and each of these chains contains exactly one element $a$ of $A$. Call these chains $C_a^+$ and $C_a^-$. Then $\{C_a^-\cup\{a\}\cup C_a^+\}_{a\in A}$ is a minimum chain cover of $S$, which proves the statement.

???+ note "Mirsky's theorem"
    The length of the longest chain of $S$ equals the minimum number of antichains needed to cover $S$.
    
    ??? note "Proof"
        Let the length of the longest chain of $S$ be $d$. By definition, at least $d$ antichains are needed to cover $S$.
        
        Let $f(s)$ be the length of the longest chain whose least element is $s$. Notice that if $f(s)=f(t)$, then $s$ and $t$ are incomparable, so $(\forall~n\in\mathbf{N})~~f^{-1}(\{n\})$ is always an antichain, where $f^{-1}(\{n\}):=\{a\in S:f(a)=n\}$ is called a [level set](https://en.wikipedia.org/wiki/Level_set).
        
        So it follows that $\{f^{-1}(\{i\}):1\leq i\leq d\}$ is an antichain cover, and hence the minimum number of antichains needed is at most $d$.

Dilworth's theorem is equivalent to [Hall's marriage theorem](../graph/graph-matching/graph-match.md#halls-theorem).

We can use Dilworth's theorem to prove the following theorem:

???+ note "Erdős–Szekeres theorem"
    A sequence of real numbers $\{a_i\}$ with at least $rs+1$ elements has either a non-decreasing subsequence of length $r+1$ or a non-increasing subsequence of length $s+1$.
    
    ??? note "Proof"
        Let the length of the sequence be $n\geq rs+1$. Define the poset $\{(i,a_i)\}_{i=1}^{n}$ with the partial order $\preceq$ given by:
        
        $$
        (i,a_i)\preceq (j,a_j)\iff (i\leq j\land a_i\leq a_j)
        $$
        
        Suppose the width of this poset is at most $s$. By Dilworth's theorem, the poset can be covered by at most $s$ chains. If all these chains had length at most $r$, the sequence would have at most $rs$ elements, a contradiction.

### Example problems

???+ note "[Luogu P1020 \[NOIP1999 Senior Group\] Missile Interception](https://www.luogu.com.cn/problem/P1020)"
    To defend against missile attacks from an enemy country, a country has developed a missile interception system. But the system has a flaw: its first shell can reach any height, but every later shell cannot be higher than the one before it. One day, radar detects incoming enemy missiles. Since the system is still in its trial phase, there is only one system, so it may not be able to intercept all the missiles.
    
    Given the heights of the missiles in the order they arrive, compute the maximum number of missiles this system can intercept, and the minimum number of such systems needed to intercept all of them.
    
    For all test data, the missile heights are positive integers not exceeding $5\times 10^4$.
    
    ??? note "Solution"
        Let there be $n$ missiles in total, and let the height of the $i$-th missile be $h_i$. Then the set $\{(i,h_i)\}_{i=1}^{n}$ is a poset with the partial order $\preceq$ defined by:
        
        $$
        (i,h_i)\preceq(j,h_j) \iff (i\leq j \land h_i\geq h_j)
        $$
        
        By Dilworth's theorem: **the minimum number of non-increasing subsequences needed to cover the sequence equals the length of the longest strictly increasing subsequence**. So the problem can be solved with the [$O(n\log n)$ method for the longest non-decreasing subsequence](../dp/basic.md#algorithm-2).
    
    ??? note "Reference code"
        ```cpp
        --8<-- "docs/math/code/order-theory/order-theory_1.cpp"
        ```

???+ note "[\[TJOI2015\] Combinatorics](https://www.luogu.com.cn/problem/P3974)"
    You are given a grid with $n$ rows and $m$ columns, where each cell holds some pieces of treasure. Each trip starts from the top-left corner and can only move right or down, and each time you pass through a cell you can pick up at most one piece of treasure. What is the minimum number of trips needed to collect all the treasure?
    
    $1\le n \le 1000$, $1\le m \le 1000$, and each cell holds at most $10^6$ pieces of treasure.
    
    ??? note "Solution"
        Ignoring the vertex weights of the grid, it is easy to see that walking on the grid under these rules is the same as walking on a DAG. So we can treat it as a Hasse diagram and build a poset from it. By Dilworth's theorem: **the minimum chain cover of a DAG equals the size of its maximum independent set of vertices**.
        
        So the answer is the total weight of the maximum-weight independent set of the grid.
        
        Let $a_{ij}$ be the weight of the grid at $(i,j)$, and let $f(i,j)$ be the answer for the subgrid from $(i,j)$ to $(1,m)$. Notice that each cell is not adjacent to the cell up and to its right, so the transition is:
        
        $$
        f(i,j)=\max\{f(i-1,j),f(i,j+1),f(i-1,j+1)+a_{ij}\}
        $$
        
        The answer is $f(n,1)$.
    
    ??? note "Reference code"
        ```cpp
        --8<-- "docs/math/code/order-theory/order-theory_2.cpp"
        ```

### Exercises

-   [\[CTSC2008\] Sacrifice](https://www.luogu.com.cn/problem/P4298)
-   [CodeForces 590E Birthday](https://codeforces.com/problemset/problem/590/E)

## Applications in C++

See also: [Sorting in the STL - Basic algorithms](../basic/stl-sort.md).

Order theory shows up in the C++ STL's [algorithms and data structures that use comparisons](https://en.cppreference.com/w/cpp/named_req/Compare#Standard_library). We often need custom comparators in C++, and the STL [requires](https://en.cppreference.com/w/cpp/named_req/Compare) them to be **strict weak orders**. Let $<$ be the custom comparator. Then we can define:

-   $x>y$ as $y<x$;
-   $x \leq y$ as $y \nless x$;
-   $x \geq y$ as $x \nless y$;
-   $x=y$ as $x \nless y\land y \nless x$.

## References and further reading

1.  [Order theory - From Academic Kids](https://academickids.com/encyclopedia/index.php/Order_theory)
2.  [Binary Relation - Wikipedia](https://en.wikipedia.org/wiki/Binary_relation)
3.  [Order Theory - Wikipedia](https://en.wikipedia.org/wiki/Order_theory)
4.  [Hasse diagram - Wikipedia](https://en.wikipedia.org/wiki/Hasse_diagram)
5.  [Directed set - Wikipedia](https://en.wikipedia.org/wiki/Directed_set)
6.  [Order Theory, Lecture Notes by Mark Dean for Decision Theory](http://www.columbia.edu/~md3405/DT_Order_15.pdf)
7.  Lu Kaicheng, Lu Huaming, [*Combinatorics* (3rd edition)](http://www.tup.tsinghua.edu.cn/bookscenter/book_00458101.html), 2006
8.  [List of Order Theory Topics - Wikipedia](https://en.wikipedia.org/wiki/List_of_order_theory_topics)
9.  [On the uses of adjacent-swap sorting and the pitfalls to watch for, by ouuan](https://ouuan.github.io/post/%E6%B5%85%E8%B0%88%E9%82%BB%E9%A1%B9%E4%BA%A4%E6%8D%A2%E6%8E%92%E5%BA%8F%E7%9A%84%E5%BA%94%E7%94%A8%E4%BB%A5%E5%8F%8A%E9%9C%80%E8%A6%81%E6%B3%A8%E6%84%8F%E7%9A%84%E9%97%AE%E9%A2%98/)
10. [One thing you should know about comparators—Strict Weak Ordering](https://codeforces.com/blog/entry/72525)
11. [Dilworth's theorem - Wikipedia](https://en.wikipedia.org/wiki/Dilworth%27s_theorem)
12. [Dilworth's Theorem | Brilliant Math & Science Wiki](https://brilliant.org/wiki/dilworths-theorem/)
13. [Hall's marriage theorem - Wikipedia](https://en.wikipedia.org/wiki/Hall's_marriage_theorem)
14. [Hall's Marriage Theorem | Brilliant Math & Science Wiki](https://brilliant.org/wiki/hall-marriage-theorem/)
15. [Dilworth study notes - Selfish](https://www.luogu.com.cn/blog/Rolling-Code/dilworth)
