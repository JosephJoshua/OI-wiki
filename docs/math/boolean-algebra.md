In mathematical logic, boolean algebra is a branch of algebra. In elementary algebra, variables take numbers as values, and the main operations studied are addition, multiplication, exponentiation, and their inverses. In boolean algebra, a variable can only take two values, **true** and **false** (usually written $1$ and $0$), and the main operations studied are conjunction (AND, $\land$), disjunction (OR, $\lor$) and negation (NOT, $\lnot$). Just as elementary algebra is a formal way to describe operations on numbers, boolean algebra is a formal way to describe logical operations.

## Boolean functions

???+ abstract "Definition"
    A **boolean function** is a function of the form $f:\mathbf{B}^k\to \mathbf{B}$, where $\mathbf{B}=\{0,1\}$ is the **boolean domain** and the non-negative integer $k$ is the **arity** of the function. A boolean function with $k=1$ is a unary function, and so on. When $k=0$, we treat the function as a constant in $\mathbf{B}$.

We usually only study unary and binary boolean functions. Unless stated otherwise, boolean functions below are only unary or binary.

Besides the usual ways of writing a function, we can also describe a boolean function with a **truth table**, **logic gates**, or a [Venn diagram](https://en.wikipedia.org/wiki/Venn_diagram).

???+ abstract "Truth table"
    For a boolean function, we list every possible input together with the matching output in a table. This table is called a truth table.

An $n$-ary boolean function can also be written as a **propositional formula** in $n$ variables. Two propositional formulas $p$ and $q$ are **logically equivalent** if and only if they describe the same boolean function, written $p\iff q$.

Below are some common boolean functions. We also call them **logical connectives** or **logical operators**:

| Name (mathematical logic)                              | Other names                   | Notation                          |
| ------------------------------------------------------ | ----------------------------- | --------------------------------- |
| Truth (tautology)                                      |                               | $\top$                            |
| Falsity (contradiction)                                |                               | $\bot$                            |
| Proposition                                            | Identity                      | $A$                               |
| Negation                                               | NOT                           | $\lnot A$                         |
| Conjunction                                            | AND                           | $A \land B$                       |
| Disjunction                                            | OR                            | $A \lor B$                        |
| Non-conjunction                                        | NAND, Sheffer stroke          | $A \bar{\land} B$, $A\uparrow B$  |
| Non-disjunction                                        | NOR                           | $A \bar{\lor} B$, $A\downarrow B$ |
|                                                        | Exclusive-OR (XOR)            | $A \oplus B$                      |
|                                                        | Exclusive-NOR (XNOR)          | $A \odot B$                       |
| Material implication[^note1]                           |                               | $A \to B$                         |
| Material nonimplication[^note1]                        |                               | $A \nrightarrow B$                |
| Converse implication[^note1]                           |                               | $A \gets B$                       |
| Converse nonimplication[^note1]                        |                               | $A \nleftarrow B$                 |
| Biconditional, equivalence[^note1][^note2]             |                               | $A \leftrightarrow B$             |
| Non-equivalence[^note1][^note3]                        |                               | $A \nleftrightarrow B$            |

The matching truth tables (from [Wikipedia](https://commons.wikimedia.org/wiki/File:Logical_connectives_table.svg)):

![](./images/logical-connectives-table.svg)

The matching Venn diagrams and [Hasse diagram](./order-theory.md#偏序集的可视化表示hasse-图) (with set inclusion $\subseteq$ as the partial order, from [Wikipedia](https://en.wikipedia.org/wiki/File:Logical_connectives_Hasse_diagram.svg)):

![](./images/logical-connectives-hasse-diagram.svg)

An $n$-ary boolean function has $2^n$ possible inputs, so there are $2\uparrow (2\uparrow n)$ $n$-ary boolean functions, where $\uparrow$ is Knuth's up-arrow.

A combination of logical operators is called a **logical expression**.

If we view $\mathbf{B}$ as the [residue classes](./number-theory/basic.md#同余类与剩余系) modulo $2$, then XOR is the same as addition modulo $2$, and AND is the same as multiplication modulo $2$. So we sometimes also write the boolean domain as $\mathbf{Z}_2$.

### Precedence

Unary logical operators have higher precedence than binary ones, that is, $\lnot$ binds tighter than $\land$, $\lor$, $\oplus$, and so on.

There are several conventions for the precedence among binary logical operators. Some sources give $\land$, $\lor$, $\oplus$ higher precedence than $\to$, $\gets$, $\leftrightarrow$, while others say the opposite. So in practice, it is best to add extra parentheses to make the order clear.

For the rules in C++, see the [C++ operator precedence table](../lang/op.md#c-运算符优先级总表).

### Sole sufficient operators and functionally complete operator sets

In fact, NAND alone, or NOR alone, is enough to express every other logical operator, and CPUs are built on this fact. However, the four operators **AND, OR, NOT and XOR** have nicer properties, so when studying boolean algebra we usually use only these four.

??? example "How to express the other logical operators using NAND or NOR"
    We have
    
    -   $\lnot p=p\bar{\land} p=p\bar{\lor} p$,
    -   $p\land q=(p\bar{\land}q)\bar{\land}(p\bar{\land}q)=(p\bar{\lor}p)\bar{\lor}(q\bar{\lor}q)$,
    -   $p\lor q=(p\bar{\land}p)\bar{\land}(q\bar{\land}q)=(p\bar{\lor}q)\bar{\lor}(p\bar{\lor}q)$,
    -   $p\to q=p\bar{\land} (q\bar{\land} q)=((p\bar{\lor}p)\bar{\lor}q)\bar{\lor}((p\bar{\lor}p)\bar{\lor}q)$.
    
    Also,
    
    -   $p=\lnot\lnot p$,
    -   $p\nleftrightarrow q=p\oplus q=(p\lor q)\land\lnot (p\land q)$,
    -   $p\leftrightarrow q=p\odot q=\lnot(p\oplus q)$,
    -   $p\nrightarrow q=\lnot(p\to q)$,
    -   $p\gets q=q\to p$,
    -   $p\nleftarrow q=\lnot(p\gets q)$.

Can we describe every logical operator using only a given set of operators? This question leads to the definition of a functionally complete operator set.

???+ abstract "Definition"
    For a given set of logical operators, if every logical operator can be described using only the functions in this set, the set is called a **functionally complete operator set**. In particular, if a single logical operator is enough to describe every logical operator, that operator is called a **sole sufficient operator** or a **Sheffer function**.
    
    If removing any one element from a functionally complete operator set makes it unable to describe every logical operator, the set is called a **minimal functionally complete operator set**.

One can prove that among the logical operators, only $\bar{\land}$ and $\bar{\lor}$ are sole sufficient operators.

Below are the common minimal functionally complete operator sets[^vaughan1942complete]:

-   $\{\bar{\land}\}$, $\{\bar{\lor}\}$,
-   $\{\land,\lnot\}$, $\{\lor,\lnot\}$, $\{\gets,\lnot\}$, $\{\to,\lnot\}$, $\{\nleftarrow,\lnot\}$, $\{\nrightarrow,\lnot\}$,
-   $\{\gets,\bot\}$, $\{\to,\bot\}$, $\{\nleftarrow,\top\}$, $\{\nrightarrow,\top\}$,
-   $\{\gets,\nleftarrow\}$, $\{\to,\nleftarrow\}$, $\{\gets,\nrightarrow\}$, $\{\to,\nrightarrow\}$,
-   $\{\gets,\nleftrightarrow\}$, $\{\to,\nleftrightarrow\}$, $\{\nleftarrow,\leftrightarrow\}$, $\{\nrightarrow,\leftrightarrow\}$,
-   $\{\lor,\leftrightarrow,\bot\}$, $\{\lor,\leftrightarrow,\nleftrightarrow\}$, $\{\lor,\nleftrightarrow,\top\}$,
-   $\{\land,\leftrightarrow,\bot\}$, $\{\land,\leftrightarrow,\nleftrightarrow\}$, $\{\land,\nleftrightarrow,\top\}$.

### Properties

First, the properties related to algebraic structures:

-   AND and OR each form a [commutative monoid](./algebra/basic.md#群) on $\mathbf{B}$. That is, AND and OR are both commutative and associative, and both have an identity element ($x\land 1=x\lor 0=x$).
-   XOR and XNOR each form a [group](./algebra/basic.md#群) on $\mathbf{B}$. That is, XOR and XNOR are both commutative and associative, have an identity element ($x\oplus 0=x\odot 1=x$), and have inverses ($x\oplus x=0$, $x\odot x=1$).
-   NAND and NOR are not associative, so they do not form semigroups.

For $\land$ and $\lor$, we have

-   Distributive laws:
    -   $a\land(b\diamond c)=(a\land b)\diamond (a\land c)$, where $\diamond$ can be $\land$, $\lor$ or $\oplus$,
    -   $a\lor(b\diamond c)=(a\lor b)\diamond (a\lor c)$, where $\diamond$ can be $\land$, $\lor$ or $\odot$.
-   **Idempotence** laws: $x\land x=x$, $x\lor x=x$.
-   Monotonicity: $a\to b\iff(a\land c)\to(b\land c)$, $a\to b\iff(a\lor c)\to(b\lor c)$.
-   **Absorption** laws: $x\land(x\lor y)=x\lor(x\land y)=x$.
-   Relation to "$\to$":
    -   $a \lor b \iff (\lnot a \to b) \land (\lnot b \to a)$,
    -   $a \land b \iff \lnot((a \to \lnot b) \lor (b \to \lnot a))$.

???+ abstract "Monotonicity of boolean functions"
    Given a boolean function $f(x_1,\dots,x_n)$ and two elements $(a_1,\dots,a_n),(b_1,\dots,b_n)$ of $\mathbf{B}^n$, if $a_i\leq b_i,~~\forall i=1,\dots,n$ always implies $f(a_1,\dots,a_n)\leq f(b_1,\dots,b_n)$, then the boolean function is called monotone.

We also have the following properties:

-   **Law of excluded middle**: $p\lor\lnot p$ is always true.
-   $\lnot p\iff p\to\bot$.
-   Double negation, i.e. the **involution** law of $\lnot$: $\lnot\lnot x=x$.
-   Involution laws of $\oplus$ and $\odot$: $x\oplus y\oplus y=x$, $x\odot y\odot y=x$.
-   De Morgan's laws: $\lnot(p\land q)=\lnot p\lor \lnot q$, $\lnot(p\lor q)=\lnot p\land \lnot q$.

## Normal forms of logical expressions

Using the properties above, we can apply equivalent transformations to a logical expression so that it fits a particular normal form. This is used in automated theorem proving. Common normal forms are the **conjunctive normal form** (CNF), the **disjunctive normal form** (DNF) and the **algebraic normal form** (ANF).

???+ abstract "Conjunctive and disjunctive normal forms"
    We make the following recursive definitions:
    
    1.  **Literal**: for a variable $x$, both $x$ and $\lnot x$ are literals.
    2.  Clause:
        -   a literal is a clause,
        -   if $A$ is a literal and $B$ is a clause, then $A\lor B$ is a clause.
    3.  Conjunctive normal form:
        -   if $A$ is a clause, then $(A)$ is in conjunctive normal form,
        -   if $A$ is a clause and $B$ is in conjunctive normal form, then $(A)\land B$ is in conjunctive normal form.
    
    Similarly, swapping $\land$ and $\lor$ in the definition above gives the definition of disjunctive normal form.

For example, the following logical expressions are all in disjunctive normal form:

-   $(A\land\lnot B)\lor(C\land D\land\lnot E)$,
-   $(A\land B)\lor (C)$,
-   $(A\land B)$,
-   $(A)$.

The following logical expressions are all in conjunctive normal form:

-   $(\lnot A\lor\lnot B\lor C)\land(\lor D\lor\lnot E)$,
-   $(A\lor B)\land (C)$,
-   $(A\lor B)$,
-   $(A)$.

The following logical expressions are in neither conjunctive nor disjunctive normal form:

-   $\lnot(A\land B)$,
-   $A\land (B\lor (C\land D))$.

We can turn any logical expression that uses only $\lnot$, $\land$ and $\lor$ into DNF with the following steps:

$$
\begin{array}{rcccl}
    \lnot\lnot x &&\mapsto&& x,\\
    \lnot(x\lor y) &&\mapsto&& \lnot x\land \lnot y,\\
    \lnot(x\land y) &&\mapsto&& \lnot x\lor \lnot y,\\
    x\land(y\lor z) &&\mapsto&& (x\land y)\lor (x\land z),\\
    (x\lor y)\land z &&\mapsto&& (x\land z)\lor (y\land z).
\end{array}
$$

To get the CNF of an expression $X$, find the DNF of $\lnot X$, then negate it and apply De Morgan's laws.

???+ abstract "Algebraic normal form"
    First, we define a term recursively:
    
    -   a variable $x$ is a term,
    -   if $A$ is a term and $x$ is a variable, then $x\land A$ is a term.
    
    A logical expression is in algebraic normal form if it has one of the following three forms:
    
    1.  $1$ or $0$,
    2.  the XOR of several pairwise non-equivalent terms, such as $a\oplus b\oplus(a\land b)\oplus(a\land b\land c)$,
    3.  the XOR of several pairwise non-equivalent terms and a single $1$, such as $1\oplus a\oplus b\oplus(a\land b)\oplus(a\land b\land c)$.

Note that algebraic normal forms correspond one-to-one to polynomials over $\mathbf{Z}_2$, so the algebraic normal form is also called the **Zhegalkin polynomial**.

We can turn any logical expression that uses only $\lnot$, $\land$, $\lor$ and $\oplus$ into ANF with the following steps:

1.  $\oplus$: expand directly, e.g. $(1\oplus x)\oplus(1\oplus x\oplus y)=1\oplus x\oplus 1\oplus x\oplus y=y$,
2.  $\land$: expand with the distributive law, e.g. $x\land(1\oplus x\oplus y)=(x\land 1)\oplus (x\land x)\oplus (x\land y)=x\oplus (x\land y)$,
3.  $\lnot$: replace $\lnot x$ with $1\oplus x$, e.g. $\lnot(1\oplus x\oplus y)=1\oplus 1\oplus x\oplus y=x\oplus y$,
4.  $\lor$: replace $x\lor y$ with $1\oplus((1\oplus x)\land(1\oplus y))$ or $x\oplus y\oplus (x\land y)$, e.g. $(1\oplus x)\lor(1\oplus x\oplus y)=1\oplus((1\oplus 1\oplus x)\land(1\oplus 1\oplus x\oplus y))=1\oplus x\oplus(x\land y)$.

## References and notes

1.  [Boolean algebra - Wikipedia](https://en.wikipedia.org/wiki/Boolean_algebra)
2.  [Boolean function - Wikipedia](https://en.wikipedia.org/wiki/Boolean_function)
3.  [Logical connective - Wikipedia](https://en.wikipedia.org/wiki/Logical_connective)
4.  [Disjunctive normal form - Wikipedia](https://en.wikipedia.org/wiki/Disjunctive_normal_form)
5.  [Zhegalkin polynomial - Wikipedia](https://en.wikipedia.org/wiki/Zhegalkin_polynomial)

[^note1]: In propositional derivations, use double long arrows instead, such as $A\implies B$, $A\impliedby B$, $A\iff B$.

[^note2]: Equivalent to XNOR.

[^note3]: Equivalent to XOR.

[^vaughan1942complete]: Vaughan, H. E. (1942). Complete sets of logical functions.*Transactions of the American Mathematical Society 51*: 117–32.
