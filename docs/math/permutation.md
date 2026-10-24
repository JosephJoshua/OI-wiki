author: 2008verser, aofall, CoelacanthusHex, Early0v0, Great-designer, Marcythm, Persdre, shuzhouliu, Tiphereth-A, Enter-tainer, gavinliu266, gi-b716, hjsjhn, Ir1d, MegaOwIer, wjy-yy, c-forrest

Permutations are a common concept in all kinds of problems.

???+ warning "This page is not about the number of permutations"
    This page is about full permutations, not the number of $k$-permutations from combinatorics. For the number of permutations, see [Permutations and Combinations](./combinatorics/combination.md).

???+ info "Convention"
    Unless stated otherwise, all sets on this page are finite.

## Definition

A bijection (one-to-one correspondence) $\sigma$ from a set $X$ to itself is called a **permutation** of $X$. If the set $X$ also has a [total order](./order-theory.md#二元关系), a permutation of it is often also called a **(full) arrangement**. This total order is called the natural order of the set.

??? info "Permutation as a rearrangement vs. as an arrangement"
    In Chinese, two different words are used here: one usually means changing the order of elements (a rearrangement), and the other usually means putting the elements in a row (an arrangement). When the elements have a natural order, the two ideas are the same thing: an arrangement can be seen as the result of a rearrangement, and compared with the natural order of the elements, the order of elements in an arrangement determines the rearrangement. Whenever this page talks about arrangements, it assumes the set has a natural order, so the page does not distinguish between the two ideas.
    
    Of course, elements without a natural order can also be "arranged". Such arrangements often show up in combinatorial counting problems. That is beyond the scope of this page.

If the set $X$ has size $n$, then the number of all permutations of $X$ is $n!$. In particular, $0!=1$: the empty set has exactly one permutation, the empty permutation.

???+ info "Notation"
    Permutations are about how elements correspond to each other, not about what the elements actually are. So when discussing a set of size $n$, we usually assume the set is $\{1,2,\cdots,n\}$; when a natural order is needed, we usually use the natural order of the natural numbers.

## Representations

There are several ways to write down a permutation. Here we use the following permutation as an example to discuss them.

$$
\sigma(1) = 2,\
\sigma(2) = 6,\
\sigma(3) = 5,\
\sigma(4) = 4,\
\sigma(5) = 3,\
\sigma(6) = 1.
$$

### Two-line notation

A permutation of the set $X=\{x_1,x_2,\cdots,x_n\}$ can be written as

$$
\sigma=\begin{pmatrix}x_1&x_2&\cdots&x_n\\
x_{p_1}&x_{p_2}&\cdots&x_{p_n}
\end{pmatrix}.
$$

It means that the permutation $\sigma$ maps the element $x_i$ to $x_{p_i}$. Of course, this requires $X=\{x_{p_1},x_{p_2},\cdots,x_{p_n}\}$. In two-line notation, the order of the elements in the first row does not matter; what matters is the correspondence between the two rows.

For example, the permutation above can be written in two-line notation as

$$
\sigma=
\begin{pmatrix}
1 & 2 & 3 & 4 & 5 & 6 \\
2 & 6 & 5 & 4 & 3 & 1
\end{pmatrix},
$$

or equally as

$$
\sigma=
\begin{pmatrix}
6 & 5 & 4 & 3 & 2 & 1 \\
1 & 3 & 4 & 5 & 6 & 2
\end{pmatrix}.
$$

### One-line notation

Often the set $X$ has a natural order. If we agree that the first row of the two-line notation is always written in the natural order, we can drop the first row, and the permutation can be written as

$$
\sigma=\sigma(1)\sigma(2)\cdots\sigma(n).
$$

This is closer to the everyday idea of an arrangement. So this ordered tuple is sometimes also called an "arrangement".

The example above in one-line notation is

$$
\sigma=265431.
$$

One-line notation is often used to compare different permutations.

### Cycle notation

There is an even more compact way to write a permutation, called cycle notation. It writes the permutation as a product of disjoint cycles. Below are the steps for writing a given permutation in cycle notation.

Given a permutation $\sigma$, write it in cycle notation as follows:

1.  If some element of $X$ has not been written yet, write a left parenthesis, then write any one such element;
2.  If the last element written is $x$, then
    -   if $\sigma(x)$ has already been written, write a right parenthesis and go back to step 1;
    -   if $\sigma(x)$ has not been written yet, write $\sigma(x)$ and repeat step 2;
3.  Repeat the steps above until every element of $X$ has been written.

Each pair of parentheses is one cycle. The number of elements inside the parentheses is the length of that cycle. In practice, cycles of length one are often omitted.

The example above in cycle notation is

$$
\sigma=(126)(35)(4)=(126)(35).
$$

In the identity permutation all cycles have length one; it is usually written as $(1)$ instead of omitting everything.

## Composition

Composition of permutations is just composition of maps. Composition of permutations is also often called multiplication of permutations.

Given two permutations

$$
\sigma=\begin{pmatrix}x_1&x_2&\cdots&x_n\\ x_{p_1}&x_{p_2}&\cdots&x_{p_n}\end{pmatrix},\ \pi=\begin{pmatrix}x_{p_1}&x_{p_2}&\cdots&x_{p_n}\\ x_{q_1}&x_{q_2}&\cdots&x_{q_n}\end{pmatrix},
$$

their product $\pi\circ\sigma$ is

$$
\pi\circ\sigma=\begin{pmatrix}x_1&x_2&\cdots&x_n\\
x_{q_1}&x_{q_2}&\cdots&x_{q_n}\end{pmatrix}.
$$

Simply put, we first apply the map $\sigma$, then apply the map $\pi$. Note that in the two-line notation above, the order of the second row of the inner map $\sigma$ matches the order of the first row of the outer map $\pi$.

Since the permutations $\sigma$ and $\pi$ are really two maps, $(\pi\circ\sigma)(x)=\pi(\sigma(x))$. Composition of permutations is evaluated from right to left. Multiplication of permutations is not commutative, so computing in the wrong order may give a wrong result.

Composing the same permutation with itself many times gives a power of the permutation, which can be computed quickly with [fast exponentiation](./binary-exponentiation.md#多次置换).

### Inverse permutation

Since a permutation is a bijection, every permutation has an inverse permutation.

Given the permutation

$$
\sigma=\begin{pmatrix}x_1&x_2&\cdots&x_n\\ x_{p_1}&x_{p_2}&\cdots&x_{p_n}\end{pmatrix},
$$

its inverse is

$$
\sigma^{-1}=\begin{pmatrix}x_{p_1}&x_{p_2}&\cdots&x_{p_n}\\x_1&x_2&\cdots&x_n\end{pmatrix}.
$$

In cycle notation, inverting each cycle gives the inverse of the whole permutation, and to invert a cycle you just write its elements in reverse order. For example, the inverse of the example $\sigma$ above in cycle notation is

$$
\sigma^{-1} = (621)(53) = (162)(35).
$$

Given a permutation of $1\sim n$, it and the sequence of positions of each element in it are inverse permutations of each other.

## Cycles

A **cycle** is itself a special kind of permutation. Its defining feature is that, starting from any point $x$ of the cycle, you can reach any other point $y$ of the cycle by applying the permutation $\sigma$ repeatedly. A cycle of length $k$ is also called a **$k$‑cycle**. Applying a $k$‑cycle $k$ times gives the identity permutation, that is, every element returns to where it started.

Cycle notation can be seen as writing a permutation as a product of these special permutations (cycles), so cycle notation is also called the **cycle decomposition** of the permutation. For every permutation, the way it decomposes into a product of cycles is unique up to order. Cycles can be thought of as the basic building blocks of permutations.

The cycle decomposition has a clear geometric meaning. If we treat each ordered pair $(x,\sigma(x))$ of a permutation on $X$ as an edge of a directed graph whose vertices are $X$, then the cycles are exactly the cycles of this graph. If $\sigma$ decomposes into $m$ cycles, the corresponding directed graph has $m$ cycles in total (including self-loops). These cycles are naturally pairwise disjoint.

### Fixed points

The elements of $1$‑cycles are the **fixed points** of the permutation. For a permutation $\sigma$ on a set $X$, the set of fixed points of $\sigma$ is usually written $X^\sigma$, that is, $X^\sigma=\{x\in X:\sigma(x)=x\}$.

### Transpositions

A $2$‑cycle is also called a **transposition**. In other words, a transposition is a permutation that only swaps the positions of one pair of elements. Its cycle notation is $(x_ix_j)$, meaning it swaps $x_i$ and $x_j$.

Every permutation can be written as a product of transpositions. This is the same as saying that any arrangement can be brought back to a given sorted order by a series of swaps of two elements. This is exactly what swap-based sorting algorithms do.

Going further, the correctness of [bubble sort](../basic/bubble-sort.md) actually shows that every permutation can be written as a product of adjacent transpositions. Here an **adjacent transposition** is a transposition that only swaps two neighboring elements.

## Properties

In applications, we often care about the properties of a single permutation.

### Parity

The way to decompose a cycle into transpositions is not unique. For example,

$$
(123)=(13)(12)=(12)(23)=(12)(13)(12)(13).
$$

However, when a permutation is decomposed into transpositions, the parity of the number of transpositions is fixed. The parity of the number of transpositions in a decomposition of a permutation is called the **parity** of the permutation.

A permutation that can be written as a product of an even number of transpositions is called an even permutation, and one that can be written as a product of an odd number of transpositions is called an odd permutation. When $n\ge2$, there are equally many odd and even permutations of $n$ elements.

### Sign

Based on parity, we can also define the **sign** of a permutation, written $\operatorname{sgn}\sigma$. The sign of an even permutation is defined as $+1$, and the sign of an odd permutation is defined as $-1$.

The sign of a product of permutations equals the product of their signs, that is,

$$
\operatorname{sgn}(\pi\circ\sigma)=\operatorname{sgn}
\pi\cdot\operatorname{sgn}\sigma.
$$

In other words, composing two permutations of the same parity gives an even permutation, and composing two permutations of different parity gives an odd permutation. This is obvious from the point of view of transposition decompositions.

In particular, a single transposition always changes the parity of a permutation. This also explains why, although the decomposition into transpositions is not unique, the parity of the number of transpositions needed is fixed.

The sign of a permutation appears in the [Leibniz expansion of the determinant](./linear-algebra/determinant.md#全排列方法定义).

### Order of a permutation

The **order** of a permutation is the smallest positive integer $a$ such that after applying the permutation $a$ times, every element is back in its original place. That is,

$$
\operatorname{ord}\sigma=\min\{a\in\mathbf N_+:\sigma^a=(1)\}.
$$

On a finite set, every permutation has finite order. This means that if you start from some initial order and keep shuffling a sequence with the same fixed pattern, it will always return to its original arrangement after a finite number of steps.

### Cycle type

Decompose a permutation of $n$ elements into cycles. The **cycle type** of the permutation is the multiset of cycle lengths in the decomposition. These cycle lengths form an integer partition of $n$. If the decomposition contains $\alpha_k$ cycles of length $k$, the cycle type is often written as

$$
1^{\alpha_1}2^{\alpha_2}\cdots n^{\alpha_n},
$$

and the exponents satisfy $\sum_{k=1}^nk\alpha_k=n$.

For a given cycle type, the number of different permutations is

$$
\frac{n!}{1^{\alpha_1}2^{\alpha_2}\cdots n^{\alpha_n}\alpha_1!\alpha_2!\cdots\alpha_n!}.
$$

??? note "Analysis"
    Given any permutation of $1\sim n$, we can cut it into a cycle decomposition according to the cycle type. But the order among cycles of the same length does not affect the permutation, so the total must be divided by $\prod_k\alpha_k!$. Also, each cycle is really a circular arrangement, and the choice of its starting point does not affect the permutation, so we must also divide by $\prod_kk^{\alpha_k}$. This gives the formula above.

If we only know the number $k$ of cycles in the decomposition, the number of different permutations is the [Stirling number of the first kind](./combinatorics/stirling.md#第一类斯特林数stirling-number) $\begin{bmatrix}n\\ k\end{bmatrix}$. The number of different cycle types is the [partition number](./combinatorics/partition.md)  $p_n$ of $n$.

From the cycle type, it is easy to find properties of the permutation such as its order and parity.

Since a $k$‑cycle has order $k$ and different cycles are disjoint, the order of the permutation $\sigma$ is

$$
\operatorname{lcm}\{k:\alpha_k>0\}.
$$

Similarly, since the parity of a $k$‑cycle is opposite to the parity of $k$, the parity of the permutation $\sigma$ is the parity of

$$
\sum_k(k-1)\alpha_k=\sum_{k}k\alpha_k-\sum_{k}\alpha_k=n-c(\sigma)
$$

Here $c(\sigma)$ is the number of cycles (including $1$‑cycles, i.e., fixed points).

Cycle types play an important role in [Pólya counting](./combinatorics/polya.md).

## Topics on arrangements

If the set $X$ has a natural order, the permutation $\sigma$ is often called an arrangement and is written in one-line notation as

$$
\sigma(1)\sigma(2)\cdots\sigma(n)
$$

Be careful not to confuse this with cycle notation.

### Inversion number

In a permutation, if a larger number appears before a smaller number, the two numbers form an **inversion**. The comparison here uses the natural order.

The total number of inversions in a permutation is called its **inversion number**. The inversion number of a permutation is the minimum number of adjacent transpositions needed to sort it. So the parity of the inversion number equals the parity of the corresponding permutation. This can serve as an equivalent definition of the parity of a permutation.

The inversion number can be computed with [merge sort](../basic/merge-sort.md#inversions) or a [Fenwick tree](../ds/fenwick.md#全局逆序对全局二维偏序), both in $O(n\log n)$ time. See the corresponding sections for explanations of the two algorithms; reference implementations are given here.

??? example "Reference implementation"
    === "Merge sort"
        ```cpp
        --8<-- "docs/math/code/permutation/inversion_2.cpp"
        ```
    
    === "Fenwick tree"
        ```cpp
        --8<-- "docs/math/code/permutation/inversion_1.cpp"
        ```

### Ordering

Permutations can be compared. Since each one-line notation is a string, the order of permutations is the [lexicographic order](../string/basic.md#字典序) on these strings.

In the C++ standard library header `<algorithm>`, `prev_permutation` and `next_permutation` find the previous and next permutation of the current one in lexicographic order.

### Rank

List all permutations of $n$ elements in increasing lexicographic order; the position of a permutation in this list is its rank. This gives a one-to-one correspondence between permutations and positive integers, which is often used for state compression in problems about permutations.

In the Chinese competitive programming community, this rank is often called the "Cantor expansion" of the permutation, but this name is not standard. More precisely, the **Cantor expansion** of the rank of a permutation corresponds to the **Lehmer code** of that permutation.

??? info "About the \"Cantor expansion\""
    As the name suggests, the Cantor expansion is a way of expanding a natural number into a sequence of digits. It can be seen as a special numeral system, also called the [factorial number system](./numeral-sys/base.md#混合基数进制). In this system, different digit positions have different radixes. For example, the decimal number $463_{10}$ can be written in the factorial number system as
    
    $$
    463_{10}=341010_{!}.
    $$
    
    It means
    
    $$
    463=3\times 5!+4\times 4!+1\times 3!+0\times 2!+1\times 1!+0\times 0!.
    $$
    
    Cantor studied numeral systems with such mixed radixes, so the digit representation of a natural number in this system is often called the Cantor expansion of that number.

??? example "Example"
    Readers not familiar with computing ranks can use this simple example to understand the basic idea of the algorithm below.
    
    To compute the rank of the permutation $\sigma=452631$, we count how many permutations are lexicographically smaller than $\sigma$, then add one. The idea is similar to [digit DP](../dp/number.md): we go position by position.
    
    -   If the 1st position is smaller than in $\sigma$, it can only be from $\{1,2,3\}$, and the remaining $5$ positions are arbitrary, giving $3\times 5!$ permutations;
    -   If the 1st position is also $4$, then for the 2nd position to be smaller than in $\sigma$, it can only be from $\{1,2,3\}$ ($4$ is already used), and the remaining $4$ positions are arbitrary, giving $3\times 4!$ permutations;
    -   Similarly, if the first $2$ positions match $\sigma$, then for the 3rd position to be smaller it can only be from $\{1\}$, and the remaining $3$ positions are arbitrary, giving $1\times 3!$ permutations;
    -   If the first $3$ positions match $\sigma$, then for the 4th position to be smaller it can only be from $\{1,3\}$, and the remaining $2$ positions are arbitrary, giving $2\times 2!$ permutations;
    -   If the first $4$ positions match $\sigma$, then for the 5th position to be smaller it can only be from $\{1\}$, and the remaining $1$ position is arbitrary, giving $1\times 1!$ permutations;
    -   If the first $5$ positions match $\sigma$, no choice of the 6th position gives a smaller permutation, so there are $0\times 0!$ permutations.
    
    So the rank of $\sigma$ is
    
    $$
    1+3\times 5!+3\times 4!+1\times 3!+2\times 2!+1\times 1!+0\times 0!=444.
    $$
    
    For different permutations, the key is to find the coefficients in front of the factorials. These coefficients are exactly the numbers of elements that come after a position but are smaller than the element at that position.

From the example, the algorithm for finding the rank of a given permutation has two steps:

1.  Convert the given permutation of length $n$ into its Lehmer code, that is, a sequence $L_\sigma$ of length $n$ whose $i$-th entry is

    $$
    L_\sigma(i)=\#\{j>i:\sigma(j)<\sigma(i)\},
    $$

    that is, the number of elements that come after position $i$ in the permutation but are smaller than $\sigma(i)$. It equals the rank (minus one) of the given element among the elements not used yet.

2.  Treat the Lehmer code as the Cantor expansion of a natural number, recover that natural number, and add one. In other words, the rank is

    $$
    \operatorname{rank}\sigma=1+L_\sigma(1)(n-1)!+L_\sigma(2)(n-2)!+\cdots+L_\sigma(n)0!.
    $$

To solve the inverse problem, that is, to find the permutation with a given rank, just run the process above backwards. The sum of the digits of the Lehmer code found along the way is the inversion number of the permutation.

In an implementation, the key is to quickly find "the rank of a given element among the unused elements" (when computing the rank) and "the element with a given rank among the unused elements" (when computing the permutation). Both can be maintained with data structures such as a [Fenwick tree](../ds/fenwick.md) or a [segment tree](../ds/seg.md). Both directions take $O(n\log n)$ time.

??? example "Reference implementation"
    === "Rank of a given permutation"
        ```cpp
        --8<-- "docs/math/code/permutation/perm_rank.cpp"
        ```
    
    === "Permutation with a given rank"
        ```cpp
        --8<-- "docs/math/code/permutation/rank_perm.cpp"
        ```

## References and notes

-   [Permutation - Wikipedia](https://en.wikipedia.org/wiki/Permutation)
-   [Lehmer code - Wikipedia](https://en.wikipedia.org/wiki/Lehmer_code)
-   [Factorial number system - Wikipedia](https://en.wikipedia.org/wiki/Factorial_number_system)
