## Introduction

A **Young tableau** is a combinatorial object commonly used in representation theory and Schubert calculus.

A Young tableau is a special kind of matrix. It makes it convenient to study group representations and properties of the symmetric group and the general linear group. Young tableaux were first introduced in 1900 by Alfred Young, a mathematician at the University of Cambridge. In 1903 the German mathematician Ferdinand Georg Frobenius applied them to the study of the symmetric group.

???+ note "Notes"
    **Representation theory** is a branch of mathematics. It studies abstract algebraic structures by representing their elements as linear transformations of vector spaces. **Schubert calculus** is a branch of algebraic geometry. It was introduced in the 19th century by Hermann Schubert to solve counting problems in projective geometry.

## Definition

### Young diagram

A **Young diagram** (also called a [Ferrers diagram](https://en.wikipedia.org/wiki/Partition_%28number_theory%29#Ferrers_diagram) when drawn with dots; see the section on [partitions](./combinatorics/partition.md#ferrers-diagram)) is a finite collection of boxes, or cells, arranged in left-justified rows, with row lengths in non-increasing order. If we list the number of boxes in each row, we get an **integer partition** $\lambda$ of a non-negative integer $n$ (the total number of boxes). So we can think of the shape of the Young diagram as $\lambda$, since it carries the same information as its integer partition.

Containment between Young diagrams defines a [partial order](../math/order-theory.md#partially-ordered-sets) on integer partitions. This order has the structure of a [lattice](../math/order-theory.md#directed-sets-and-lattices), and is called **Young's lattice**. If we list the number of boxes in each column of a Young diagram, we get the "conjugate partition" (or "transpose partition") of $\lambda$. Its Young diagram is obtained by reflecting the original diagram across the main diagonal.

The position of each box in a Young diagram is given by two coordinates: the **row** and the **column**. Columns go from left to right, and rows go from the row with the most boxes to the row with the fewest. Note that there are two different conventions for drawing Young diagrams: the first puts rows with fewer boxes below rows with more boxes, and the second stacks the rows upward from largest to smallest. Since the first is mainly used in English-speaking countries and the second is usually used in French-speaking countries, they are customarily called English notation and French notation.

The following list shows the two ways to draw the Young diagram of the integer partition $(5,4,1)$:

-   English notation: ![](./images/young-diagram-1.svg)
-   French notation: ![](./images/young-diagram-2.svg)

### Young tableau

#### Definition

A **Young tableau** is obtained by filling the boxes of a Young diagram with symbols taken from some alphabet, which is usually required to be a totally ordered set. The entries are written as $x_{1}$, $x_{2}$, $x_{3}$, $\ldots$. For convenience, we simply fill in positive integers.

When Young tableaux were first applied to the representation theory of the symmetric group, any distinct positive integers from $1$ to $n$ could be placed in the $n$ boxes of the Young diagram. But most research today uses "standard" Young tableaux, where the numbers in each row and each column must be strictly increasing. The numbers of distinct standard Young tableaux with $n$ boxes form the [involution numbers](https://en.wikipedia.org/wiki/Telephone_number_%28mathematics%29):

???+ note "Notes"
    The **involution numbers** (also called telephone numbers) are an integer sequence in mathematics. They count the ways to connect $n$ telephone lines to each other when each line can connect to at most one other line. They also describe the number of matchings in the complete graph on $n$ vertices, the number of permutations of $n$ elements that are involutions, the sum of the absolute values of the coefficients of Hermite polynomials, the number of standard Young tableaux with $n$ cells, and the sum of the degrees of the irreducible representations of the symmetric group.

$1, 1, 2, 4, 10, 26, 76, 232, 764, 2620, 9496, \ldots$ (sequence [A000085](https://oeis.org/A000085) in the [OEIS](https://en.wikipedia.org/wiki/On-Line_Encyclopedia_of_Integer_Sequences))

In other applications, a Young diagram may also be filled with repeated numbers. If the numbers in each column are strictly increasing and the numbers in each row are non-decreasing, the tableau is called **semistandard** (Semistandard Young Tableaux, sometimes called column-strict). The sequence recording how many times each number appears in the tableau is called the **weight** of the tableau. So the weight of a standard Young tableau is always $(1,1,\ldots,1)$, because in a standard Young tableau each positive integer from $1$ to $n$ appears exactly once.

#### Insertion algorithm for standard Young tableaux

Properties of permutations can be shown visually by Young tableaux. The **RSK insertion algorithm** gives a way to connect Young tableaux and permutations. It was introduced by Robinson, Schensted and Knuth.

Let $S$ be a Young tableau. Define $S \leftarrow x$ as inserting $x$ into the tableau starting from the first row, as follows:

1.  In the current row, find the smallest number $y$ that is larger than $x$.
2.  If such a $y$ exists, replace $y$ with $x$, move to the next row, set $x \leftarrow y$, and repeat step 1.
3.  If no such $y$ exists, put $x$ at the end of the row and stop. Say $x$ ends up in row $s$, column $t$. Then $(s, t)$ must be a corner. A cell $(s, t)$ is a corner if and only if there is no cell at $(s + 1, t)$ or at $(s, t + 1)$.

For example, the steps for inserting $3$ into the Young tableau $(2, 5, 9)(6, 7)(8)$ are:

![](./images/young-tableau-insert.svg)

### Variations

There are many variations of Young tableaux that are not strictly standard. For example, a row-strict Young tableau requires the numbers in each row to be strictly increasing and the numbers in each column to be non-decreasing; this is the conjugate of a column-strict tableau. Also, in the theory of plane partitions, it is customary to replace "increasing" in the definitions above with "decreasing". Other variations, such as ribbon tableaux, first group some boxes together and then require all boxes in the same group to be filled with the same number.

### Skew tableaux

Given two Young diagrams $\lambda = (\lambda{1}, \lambda{2} \ldots)$ and $\mu = (\mu{1}, \mu{2},\ldots)$ such that $\lambda$ contains $\mu$, that is, $\mu{i} \leq \mu{i}$ for all $i$. Define the "skew diagram" $\lambda/\mu$ as all the boxes of $\lambda$ minus all the boxes of $\mu$, that is, the set difference of $\lambda$ and $\mu$. Filling the boxes of a skew diagram with entries gives a **skew tableau**.

For example, the figure below shows a standard skew tableau for the integer partition $(5,4,1)$:

![](./images/skew-tableau.svg)

Similarly, if the numbers in each column are strictly increasing and the numbers in each row are non-decreasing, the skew tableau is called a **semistandard skew tableau**. If a semistandard skew tableau is filled with the numbers $1$ to $n$ (the total number of boxes) without repetition, it is called a **standard skew tableau**. Note that different $\lambda$ and $\mu$ can give the same $\lambda/\mu$. Although most properties of skew tableaux depend only on the boxes left after taking the difference, some operations still depend on the choice of $\lambda$ and $\mu$. So $\lambda/\mu$ must be seen as carrying two pieces of information: $\lambda$ and $\mu$. When $\mu$ is the empty partition (the only partition of $0$), the skew tableau $\lambda/\mu$ becomes the Young tableau $\lambda$.

## Applications

Young tableaux are often used in combinatorics, representation theory and algebraic geometry. Different ways of counting Young tableaux lead to the definition of Schur functions and related identities. In competitive programming, problems often test the hook length formula for Young tableaux.

### Hook length

Given a Young tableau $\pi_{\lambda}$ with $n$ boxes in total, fill the $n$ numbers from $1$ to $n$ into it so that every row increases from left to right and every column increases from bottom to top. Let $dim_{\pi_{\lambda}}$ be the number of ways to do this.

For a box $v$ in the tableau, define its **hook length** $\mathrm{hook}(v)$ as the number of boxes to its right in the same row, plus the number of boxes above it in the same column, plus 1 (the box itself).

### Hook length formula

Let $dim_{\lambda}$ denote this number of ways. The **hook length formula** says that the number of ways equals $n!$ divided by the product of the hook lengths of all boxes.

$$
\dim \pi _{\lambda}={\frac {n!}{\prod_{{x\in Y(\lambda)}}{\mathrm {hook}}(x)}}.
$$

![](./images/young-tableau-2.svg)

So for the Young tableau of the integer partition $10 = 5 + 4 + 1$, shown in the figure above, there are

$$
\dim \pi _{\lambda }={\frac  {10!}{7\cdot 5\cdot 4\cdot 3\cdot 1\cdot 5\cdot 3\cdot 2\cdot 1\cdot 1}}=288.
$$

ways.

## Example problems

### Subsequence problems

For a permutation $X = x_{1}, \ldots , x_{n}$ of $1$ to $n$, let $P$ (written $P_{X}$) be the Young tableau it produces.

1.  The length of the first row of $P_{X}$ equals the length of the **longest increasing subsequence (LIS)** of $X$. Note that the first row of $P$ is not necessarily an LIS itself, so you cannot directly use this property to solve problems like "LIS partitioning".

2.  For a permutation $X$ and the Young tableau $P_{X}$ it produces, if $X^R$ is the reverse of $X$, then the tableau $P_{X^R}$ produced by $X^R$ is $P_{X}$ with rows and columns swapped.

    For example, for the permutations $X = 1, 5, 7, 2, 8, 6, 3, 4$ and $X^R = 4, 3, 6, 8, 2, 7, 5, 1$, we get the following Young tableau $P_{X}$:

    ![](./images/young-tableau-LIS.svg)

3.  The length of the first column of $P_{X}$ equals the length of the **longest decreasing subsequence (LDS)** of $X$.

Define $k-LIS$ and $k-LDS$ as subsequences whose $LIS/LDS$ length is at most $k$. We can also solve this kind of problem with Young tableaux. For $1-LIS$, clearly the longest $1-LIS$ subsequence is the $LDS$ of the sequence, which is exactly the first column of the tableau. In the same way, the total length of the first $k$ columns of the tableau is the length of the longest $k-LIS$ subsequence. The proof is as follows:

For a permutation $X$ and its Young tableau $P$ with $m$ rows, let the permutation $X^∗$ be $(P_{m,1}\ldots,P_{m,λ_{m}},P_{m−1,1}\ldots,P_{1,1}\ldots P_{1,λ_{1}})$ (that is, write the rows of the tableau one after another from bottom to top). Then $X$ can always be turned into $X^*$ by swap operations.

So the length of the longest $k-LIS$ subsequence can be written as $F(k)=\sum_{i=1}^{m} \min(k,\lambda_{i})$, the total length of the first $k$ columns.

???+ note "[CTSC 2017 Longest Increasing Subsequence](https://uoj.ac/problem/301)"
    There is a sequence $b$ of length $n$. For the sequence $B_{m} = (b_{1}, b_{2},\ldots, b_{m})$, let $C$ be a subsequence of $B_{m}$ whose longest increasing subsequence has length at most $k$. Find the maximum length of $C$.

??? note "Solution idea"
    With many queries, consider a sweep line approach. Then we need to maintain the Young tableau of every prefix. Using the conclusion above, the problem becomes how to quickly maintain the total length of the first $k$ columns of the tableau. Maintaining it directly costs $O(n^2 \log n)$, which is too slow. Instead, maintain the first $\sqrt{n}$ columns and the first $\sqrt{n}$ rows.
    
    Notice that the tableau can never completely cover this $W \times H$ rectangle. If $K \leq W$, we can get the answer directly. If $K > W$, the part beyond $W$ must lie within the first $H$ rows. So we need to maintain the first $\sqrt{n}$ columns and the first $\sqrt{n}$ rows at the same time. Reversing the permutation gives the transposed tableau, so we only need to also maintain $-A_{i}$. The complexity is $O(n \sqrt{n} \log n)$.

???+ note "[BJWC 2018 Longest Increasing Subsequence](https://www.luogu.com.cn/problem/P4484)"
    Given a random permutation of length $n$, find the expected length of its longest increasing subsequence.

???+ note "[CF1268B Domino for Young](https://codeforces.com/problemset/problem/1268/B)"
    You are given a histogram with $n$ columns of lengths $a_{1} ,a_{2},\ldots,a_{n}\,(a_{1} \geq a_{2} \geq \ldots \geq a_{n} \geq 1)$. (For example, the Young diagram of $a=[3,2,2,2,1]$.) Find the maximum number of non-overlapping dominoes ($1 \times 2$ or $2 \times 1$ rectangles) that can be drawn inside this histogram.

## References and further reading

1.  [Young Tableau - from Wolfram MathWorld](https://mathworld.wolfram.com/YoungTableau.html)
2.  [Young tableau - Wikipedia](https://en.wikipedia.org/wiki/Young_tableau)
3.  [Hook length formula - Wikipedia](https://en.wikipedia.org/wiki/Hook_length_formula)
4.  Yuan Fangzhou, ["On the Applications of Young Tableaux in Competitive Programming", IOI2019](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2019%E8%AE%BA%E6%96%87%E9%9B%86.pdf), Collected Papers of the Chinese National Team Candidates, 202-229
