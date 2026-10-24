## Introduction

This article introduces data structures that store fractions in lowest terms, along with some related concepts. They are closely tied to [continued fractions](./continued-fraction.md). In competitive programming they help solve a range of number theory problems, and they sometimes appear as the hidden background of a problem.

## Stern–Brocot tree

The Stern–Brocot tree is an elegant structure for working with fractions. It contains every distinct positive rational number. It was discovered independently by Moritz Stern in 1858 and by Achille Brocot in 1861.

### Construction

#### Level-by-level construction

The Stern–Brocot tree can be obtained while iteratively building the Stern–Brocot sequence of order $k$. The Stern–Brocot sequence of order $0$ consists of two simple fractions:

$$
\frac{0}{1},\ \frac{1}{0}.
$$

Strictly speaking, $\dfrac{1}{0}$ here is not a rational fraction. You can think of it as the fraction in lowest terms that represents $\infty$.

Between every two adjacent fractions $\dfrac{a}{b}$ and $\dfrac{c}{d}$ of the Stern–Brocot sequence of order $k$, insert their mediant[^mediant] $\dfrac{a+c}{b+d}$. This gives the Stern–Brocot sequence of order $k+1$. The general definition of the mediant allows the fraction to be reduced, but when building the Stern–Brocot tree you simply add the numerators and add the denominators, with no need to worry about reducing. In this way, you can build the Stern–Brocot sequences of all orders one after another. The first few iterations look like this:

$$
\begin{array}{ccccccccc}
&&&\dfrac{0}{1}, & \dfrac{1}{1}, & \dfrac{1}{0} &&&\\\\
&&\dfrac{0}{1}, & \dfrac{1}{2}, & \dfrac{1}{1}, & \dfrac{2}{1}, & \dfrac{1}{0} &&\\\\
\dfrac{0}{1}, & \dfrac{1}{3}, & \dfrac{1}{2}, & \dfrac{2}{3}, & \dfrac{1}{1}, & \dfrac{3}{2}, & \dfrac{2}{1}, & \dfrac{3}{1}, & \dfrac{1}{0}
\end{array}
$$

If you connect the fractions added in each iteration into a tree, you get the Stern–Brocot tree, as shown below:

![](./images/stern-brocot-tree.svg)

The Stern–Brocot sequence of order $k$, without its two endpoints, is exactly the in-order traversal of the Stern–Brocot tree of depth $k-1$.

#### Construction with triples

An equivalent construction starts with the triple

$$
\left(\dfrac{0}{1},\dfrac{1}{1},\dfrac{1}{0}\right)
$$

as the root. Then, under every node

$$
\left(\dfrac{a}{b},\dfrac{p}{q},\dfrac{c}{d}\right)
$$

add the two nodes

$$
\left(\dfrac{a}{b},\dfrac{a+p}{b+q},\dfrac{p}{q}\right),\ \left(\dfrac{p}{q},\dfrac{p+c}{q+d},\dfrac{c}{d}\right)
$$

as its left and right children. This builds the whole Stern–Brocot tree. In the triple stored at each node, the fraction the node actually holds is the middle one, $\dfrac{p}{q}$. The left and right fractions $\dfrac{a}{b}$ and $\dfrac{c}{d}$ are fractions that appeared earlier. Also, comparing with the first construction, you can see that $\dfrac{p}{q}$ is exactly the mediant inserted between $\dfrac{a}{b}$ and $\dfrac{c}{d}$.

#### Matrix representation and the Stern–Brocot number system

The triple construction means that every node of the Stern–Brocot tree corresponds to a matrix

$$
S = \begin{pmatrix}
b & d\\
a & c
\end{pmatrix}.
$$

The root of the Stern–Brocot tree is the identity matrix $I$. Moving to the left child or to the right child corresponds to multiplying the current node's matrix on the right by

$$
L=\begin{pmatrix}
1 & 1 \\
0 & 1
\end{pmatrix},~
R=\begin{pmatrix}
1 & 0 \\
1 & 1
\end{pmatrix}.
$$

The fraction a node actually represents is $f(S)=\dfrac{a+c}{b+d}$. Each node's matrix $S$ can be written as a product of matrices $L$ and $R$. You can also read this as a string made of $L$ and $R$ that describes the path from the root to the node. Every positive rational number has a unique such string, so this gives a way to represent positive rationals. It is called the **Stern–Brocot number system**.

#### Building the tree

To build the tree, just simulate the process above. The code below does an in-order traversal of the first $n$ levels of the Stern–Brocot tree.

???+ example "Building the tree"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/stern-brocot/tree-build.cpp:core"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/stern-brocot/tree-build.py:core"
        ```

Building the tree takes $O(2^n)$ time.

### Properties

Now we look at the properties of the Stern–Brocot tree. In short, the Stern–Brocot tree is a [binary search tree](../../ds/bst.md) containing all positive rational fractions in lowest terms. It is also a [heap](../../ds/binary-heap.md) on both numerators and denominators, and a [Cartesian tree](../../ds/cartesian-tree.md) on the pairs (denominator, numerator). If you consider the interval formed by the left and right endpoints in the triple construction, the Stern–Brocot tree can also be seen as a [segment tree](../../ds/seg.md) over $[0,\infty]$. All of these statements follow from the three basic properties below.

#### Monotonicity

In the construction above, the fractions on each level are strictly increasing. This follows by induction, because if $\dfrac{a}{b} < \dfrac{c}{d}$, then we must have

$$
\dfrac{a}{b} < \dfrac{a+c}{b+d} < \dfrac{c}{d}.
$$

You can check this by clearing the denominators in the inequalities. The base case is $\dfrac{0}{1} < \dfrac{1}{0}$, where monotonicity clearly holds.

#### Irreducibility

In the construction above, every fraction is in lowest terms. Again we use induction, this time to show that on every level, each pair of adjacent fractions $\dfrac{a}{b}$ and $\dfrac{c}{d}$ satisfies

$$
bc-ad = \det\begin{pmatrix}
b & d\\
a & c
\end{pmatrix} = 1.
$$

At the root the matrix is the identity, so this clearly holds. When moving down, we multiply by $L$ or $R$, both of which have determinant $1$. By the properties of the [determinant](../linear-algebra/determinant.md), the equality also holds on the next level:

$$
\det\begin{pmatrix}b & b+d \\ a & a+c \end{pmatrix} = \det\begin{pmatrix}b+d & d \\ a+c & c\end{pmatrix} = 1.
$$

For the base case $\dfrac{0}{1}$ and $\dfrac{1}{0}$ this is also obvious. So, by [Bézout's identity](./bezouts.md), the numerator and denominator of every fraction are coprime, which means every fraction is in lowest terms.

#### Completeness

Finally, we need to show that the Stern–Brocot tree contains every positive fraction in lowest terms. The first two properties show that the Stern–Brocot tree is a binary search tree. Any positive fraction $\dfrac{p}{q}$ in lowest terms lies between $\dfrac{0}{1}$ and $\dfrac{1}{0}$. If you search for it as in a binary search tree, the only way it can be missing from the tree is if the search goes on forever. We now show that for any positive rational $\dfrac{p}{q}$, the search cannot go on forever.

During the search, let $\dfrac{a}{b}$ be the current lower bound of $\dfrac{p}{q}$ and $\dfrac{c}{d}$ the current upper bound. The lower bound starts at $\dfrac{0}{1}$ and the upper bound starts at $\dfrac{1}{0}$. After that, the bounds are updated step by step depending on how $\dfrac{a+c}{b+d}$ compares with $\dfrac{p}{q}$. If the search never ended, then at every step we would have

$$
\dfrac{a}{b} < \dfrac{p}{q} < \dfrac{c}{d},
$$

so at every one of infinitely many steps we would have

$$
bp-aq \ge 1,\ cq-dp \ge 1.
$$

Multiplying the two inequalities by $(c+d)$ and $(a+b)$ respectively gives

$$
(c+d)(bp-aq) + (a+b)(cq-dp) \ge a+b+c+d.
$$

Using the equality $bc-ad=1$ shown above, this simplifies to

$$
p+q \ge a+b+c+d.
$$

However, each time the search goes one level deeper, the right-hand side strictly increases while the left-hand side stays the same. So this condition cannot hold for infinitely many steps, and the search must stop after a finite number of steps.

### Finding a fraction

When using the Stern–Brocot tree in practice, you often need to find where a given fraction is in the tree.

#### Naive algorithm

Since the Stern–Brocot tree is a binary search tree, you can find the path from the root to a given fraction just by comparing the current fraction with the target. Write a move to the left child as $L$ and a move to the right child as $R$. Then each path corresponds to a string of $L$ and $R$, which is exactly the representation of the rational number in the Stern–Brocot number system mentioned above. Finding the path to a rational number is the same as finding its representation in the Stern–Brocot number system.

The naive fraction-finding algorithm is implemented as follows:

???+ example "Naive fraction finding"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/stern-brocot/fraction-finding-1.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/stern-brocot/fraction-finding-1.py:core"
        ```

This algorithm runs in $O(p+q)$ time, so it is not practical in competitive programming.

In the Stern–Brocot number system, every positive irrational number corresponds to a unique infinite string, which can be built with the same algorithm. Every prefix of this infinite string corresponds to a rational fraction in lowest terms. If you list these fractions in order, their denominators are strictly increasing, and the limit of the sequence is the irrational number. So the Stern–Brocot tree can be used to find rational approximations of an irrational number to any precision. Note, however, that the distance between this sequence of rationals and the irrational number is not strictly decreasing. For the rigorous theory of rational approximation, see the [Diophantine approximation](./continued-fraction.md#丢番图逼近) section of the continued fractions page. When you use the Stern–Brocot tree to find the best approximation of a real number with denominator below some bound, remember at the end to compare the distances from both endpoints of the interval to that real number.

#### Fast algorithm

The naive fraction-finding algorithm is slow, but a simple optimization gives a fast $O(\log(p+q))$ algorithm. The key idea is to handle a run of consecutive $L$ moves or $R$ moves all at once.

Suppose the target fraction $\dfrac{p}{q}$ lies between $\dfrac{a}{b}$ and $\dfrac{c}{d}$. After $t$ consecutive moves to the right, the right boundary stays the same and the left boundary moves to $\dfrac{a+tc}{b+td}$. Conversely, after $t$ consecutive moves to the left, the left boundary stays the same and the right boundary moves to $\dfrac{ta+c}{tb+d}$. So the number of right moves and left moves can be found directly from $\dfrac{a+tc}{b+td}<\dfrac{p}{q}$ or $\dfrac{p}{q}<\dfrac{ta+c}{tb+d}$. The inequalities are strict because the algorithm moves the left and right endpoints, and the target fraction shows up as the mediant of the final endpoints.

???+ example "Fast fraction finding"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/stern-brocot/fraction-finding-2.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/stern-brocot/fraction-finding-2.py:core"
        ```

This algorithm requires the fraction $\dfrac{p}{q}$ to be known. If the target fraction is unknown, you usually have to find the number of moves for each run of right or left moves by binary lifting or binary search. The fraction-finding algorithm then takes $O(\log^2(p+q))$ time.

#### Algorithm based on continued fractions

When the fraction is known, continued fractions give an even simpler algorithm. Assume the first run of moves goes right; if not, say the first run of right moves has length zero. The endpoints are moved alternately right and left. List the endpoint positions after each run as follows:

$$
\dfrac{p_0}{q_0},~\dfrac{p_1}{q_1},~\dfrac{p_2}{q_2},~\cdots,~\dfrac{p_{n-2}}{q_{n-2}},~\dfrac{p_{n-1}}{q_{n-1}},~\dfrac{p_n}{q_n}.
$$

Here the even-numbered runs move right, so we record the left endpoint; the odd-numbered runs move left, so we record the right endpoint. Add two more endpoints in front of this list:

$$
\dfrac{p_{-2}}{q_{-2}}=\dfrac{0}{1},~\dfrac{p_{-1}}{q_{-1}}=\dfrac{1}{0}.
$$

Let $t_k$ be the number of moves in run $k$. From the relation between the number of moves and the endpoint positions found above, we get

$$
\dfrac{p_k}{q_k} = \dfrac{t_kp_{k-1}+p_{k-2}}{t_kq_{k-1}+q_{k-2}}.
$$

By the [recurrence](./continued-fraction.md#递推关系) for continued fractions, the endpoint is

$$
\dfrac{p_k}{q_k} = [t_0,t_1,\cdots,t_k].
$$

The final continued fraction is

$$
\dfrac{p}{q} = \dfrac{p_n+p_{n-1}}{q_n+q_{n-1}} = [t_0,t_1,\cdots,t_{n-1},t_n,1].
$$

So, in the [continued fraction representation](./continued-fraction.md#简单连分数) of the target fraction that ends in one, the terms before the final one encode the path in the Stern–Brocot tree from the root to the node. The even-indexed terms (indices start at $0$) are edges to right children, and the odd-indexed terms are edges to left children.

The continued fraction of a rational number can be computed with the Euclidean algorithm, so fraction finding based on continued fractions runs in $O(\log\min\{p,q\})$ time.

???+ example "Fraction finding with continued fractions"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/stern-brocot/fraction-finding-3.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/stern-brocot/fraction-finding-3.py:core"
        ```

Continued fractions also make it easy to write down a node's parent and children. For the node $[t_0,t_1,\cdots,t_n,1]$, its parent is the node reached by making one fewer move in the last direction: if $t_n>1$, the parent is $[t_0,t_1,\cdots,t_n - 1,1]$; otherwise, the parent is $[t_0,t_1,\cdots,t_{n-1},1]$. Its two children are $[t_0,t_1,\cdots,t_n+1,1]$ and $[t_0,t_1,\cdots,t_n,1,1]$. Which one is the left child and which is the right child depends on the parity of $n$.

## Calkin–Wilf tree

Another, even simpler structure for storing positive rational fractions is the Calkin–Wilf tree. It usually looks like this:

![pic](./images/calkin-wilf-tree.svg)

The root of the tree is $\dfrac{1}{1}$. For the node holding $\dfrac{p}{q}$, the left and right children are $\dfrac{p}{p+q}$ and $\dfrac{p+q}{q}$. As with the Stern–Brocot tree, every fraction in it is in lowest terms, and every positive fraction in lowest terms appears exactly once.

### Relation to continued fractions

Unlike the Stern–Brocot tree, the Calkin–Wilf tree is not a binary search tree, so it cannot be used for binary search over rationals.

In the Calkin–Wilf tree, when $p>q$, the parent of $\dfrac{p}{q}$ is $\dfrac{p-q}{q}$; when $p<q$, it is $\dfrac{p}{q-p}$. In the first case, starting from $\dfrac{p}{q}$, the node is the right child of its parent. You can keep moving up through right-child edges until the numerator is no longer larger than the denominator. At that point the node holds $\dfrac{p\bmod q}{q}$, and this run has $\left\lfloor\dfrac{p}{q}\right\rfloor$ moves. In the second case, the node is the left child of its parent. You can keep moving up through left-child edges until the denominator is no longer larger than the numerator. At that point the node holds $\dfrac{p}{q\bmod p}$, and this run has $\left\lfloor\dfrac{q}{p}\right\rfloor$ moves.

In the language of continued fractions, suppose the current node holds the complete quotient $s_k$ of some continued fraction. Moving up through right-child edges $\lfloor s_k\rfloor$ times reaches $\dfrac{1}{s_{k+1}}$, and then moving up through left-child edges $\lfloor s_{k+1}\rfloor$ times reaches $s_{k+2}$. So the path from the node $s_0=\dfrac{p}{q}$ up to the root $\dfrac{1}{1}$ is encoded by the continued fraction $[t_0,t_1,\cdots,t_n,1]$: ignoring the final $1$, the even-indexed terms (indices start at $0$) count moves up through right-child edges, and the odd-indexed terms count moves up through left-child edges.

For the node holding $\dfrac{p}{q}=[t_0,t_1,\cdots,t_n,1]$, the parent is:

1.  If $t_0>0$, the parent is $\dfrac{p-q}{q}=[t_0 - 1, t_1, \cdots, t_n,1]$;
2.  If $t_0=0$ and $t_1>1$, the parent is $\dfrac{p}{q-p} = [0, t_1 - 1, t_2, \cdots, t_n,1]$;
3.  If $t_0=0$ and $t_1=1$, the parent is $\dfrac{p}{q-p} = [t_2, t_3, \cdots, t_n,1]$.

Going the other way, its children are $\dfrac{p+q}{q}=[t_0+1,t_1,\cdots,t_n,1]$ and $\dfrac{p}{p+q}=[0,1,t_0,t_1,\cdots,t_n,1]$. When $t_0=0$, the continued fraction of the second child should be read as $[0,1+t_1,t_2,\cdots,t_n,1]$.

### Relation to the Stern–Brocot tree

Both trees are linked to continued fractions: along a path in the Stern–Brocot tree, the nodes follow the recurrence of the convergents, while along a path in the Calkin–Wilf tree, the nodes follow the recurrence of the complete quotients. A fraction has a fixed continued fraction representation, so the code of its path up to the root in the Calkin–Wilf tree is exactly the same as the code of the path from the root down to it in the Stern–Brocot tree. However, because the paths go in opposite directions, the two trees store the same fractions on each level, but in different positions.

Run a [breadth-first search](../../graph/bfs.md) on each tree and number the nodes in order, with the root numbered $1$. Then the children of node $v$ are $2v$ and $2v+1$. In the binary representation of a node's number, ignoring the leading $1$, each $1$ from the high bits to the low bits means a move to the right child, and each $0$ means a move to the left child. In the Calkin–Wilf tree, the node holding the rational number with continued fraction $[t_0,t_1,\cdots,t_n,1]$ has number

$$
1\cdots \underbrace{0\cdots 0}_{t_3}\underbrace{1\cdots 1}_{t_2}\underbrace{0\cdots 0}_{t_1}\underbrace{1\cdots 1}_{t_0}.
$$

Correspondingly, in the Stern–Brocot tree, the node holding the rational number with continued fraction $[t_0,t_1,\cdots,t_n,1]$ has number

$$
1\underbrace{1\cdots 1}_{t_0}\underbrace{0\cdots 0}_{t_1}\underbrace{1\cdots 1}_{t_2}\underbrace{0\cdots 0}_{t_3}\cdots.
$$

After removing the leading $1$, the remaining bits give exactly the position of the node within its level, counting from left to right starting at $0$. This shows that the orders of fractions on the same level of the Stern–Brocot tree and the Calkin–Wilf tree are bit-reversal permutations of each other, that is, the permutation of $0\sim (2^k-1)$ obtained by reversing the binary digits of the index (padded with leading $0$s).

Because of this, nodes of the Stern–Brocot tree are sometimes numbered by the numbers of the corresponding nodes in the Calkin–Wilf tree. The resulting numbering is shown below:

![pic](./images/stern-brocot-index.svg)

This numbering can be built recursively: the root has number $1$. Each time you move to the left child, replace the leading $1$ of the number with $10$; each time you move to the right child, replace the leading $1$ with $11$. Reading the number from right to left gives the path from the root to the node.

### Stern's diatomic sequence

If you list all fractions of the Calkin–Wilf tree in breadth-first-search order, or all fractions of the Stern–Brocot tree in the numbering shown above, you get the following sequence:

$$
\dfrac{1}{1},~\dfrac{1}{2},~\dfrac{2}{1},~\dfrac{1}{3},~\dfrac{3}{2},~\dfrac{2}{3},~\dfrac{3}{1},~\dfrac{1}{4},~\dfrac{4}{3},~\dfrac{3}{5},~\dfrac{5}{2},\cdots.
$$

Using the construction of the Calkin–Wilf tree, one can show that for any two adjacent fractions in this sequence, the denominator of the first equals the numerator of the second. Listing just the numerators gives Stern's diatomic sequence ([OEIS A002487](https://oeis.org/A002487)), also called the Stern–Brocot sequence. The sequence above is indexed from $1$, and we additionally define the $0$-th term to be $0$.

Let $a_n$ be the $n$-th term of Stern's diatomic sequence. It satisfies the recurrence:

$$
\begin{aligned}
a_{2n} &= a_n,\\
a_{2n+1} &= a_n + a_{n+1}. 
\end{aligned}
$$

The base cases are $a_0=0$ and $a_1=1$. Computing $a_n$ directly with this recurrence takes $O(\log^2n)$ time, which is not great. A better way is to view $a_n$ as the numerator of the fraction numbered $n$ in the Calkin–Wilf tree and use the continued-fraction-based recurrence described above. This takes $O(\log n)$ time.

## Farey sequence

The Farey sequence is very similar to the Stern–Brocot tree. Let $F_n$ denote the **Farey sequence of order $n$**. It is the sequence of all fractions in lowest terms in $[0,1]$ with denominator at most $n$, sorted in increasing order:

$$
\begin{array}{lllllllllllll}
F_1=\bigg\{&\dfrac{0}{1},&&&&&&&&&&\dfrac{1}{1}&\bigg\}\\\\
F_2=\bigg\{&\dfrac{0}{1},&&&&&\dfrac{1}{2},&&&&&\dfrac{1}{1}&\bigg\}\\\\
F_3=\bigg\{&\dfrac{0}{1},&&&\dfrac{1}{3},&&\dfrac{1}{2},&&\dfrac{2}{3},&&&\dfrac{1}{1}&\bigg\}\\\\
F_4=\bigg\{&\dfrac{0}{1},&&\dfrac{1}{4},&\dfrac{1}{3},&&\dfrac{1}{2},&&\dfrac{2}{3},&\dfrac{3}{4},&&\dfrac{1}{1}&\bigg\}\\\\
F_5=\bigg\{&\dfrac{0}{1},&\dfrac{1}{5},&\dfrac{1}{4},&\dfrac{1}{3},&\dfrac{2}{5},&\dfrac{1}{2},&\dfrac{3}{5},&\dfrac{2}{3},&\dfrac{3}{4},&\dfrac{4}{5},&\dfrac{1}{1}&\bigg\}
\end{array}
$$

By definition, the Farey sequence is monotonic, irreducible and complete. As shown above, every fraction that $F_k$ adds compared with $F_{k-1}$ is always the mediant of two adjacent fractions in $F_{k-1}$.

The algorithm above for building the Stern–Brocot tree also works for building the Farey sequence. Since the Stern–Brocot tree contains all fractions in lowest terms, you only need to change the stopping condition to a limit on the denominator to get code that builds the Farey sequence. The Farey sequence of order $n$, $F_n$, can be seen as a subsequence of the Stern–Brocot sequence of order $n$.

???+ example "Building the Farey sequence"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/stern-brocot/farey-build.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/stern-brocot/farey-build.py:core"
        ```

Building the Farey sequence directly takes $O(|F_n|)=O(n^2)$ time.

### Sequence length and finding fractions

The length of the Farey sequence can be found recursively. Compared with $F_{n-1}$, the new fractions in $F_n$ all have denominator $n$ and a numerator that is at most $n$ and coprime to $n$. So:

$$
\begin{aligned}
|F_n| &= |F_{n-1}| + \varphi(n) = 1 + \sum_{k=1}^n\varphi(k).
\end{aligned}
$$

Here $\varphi(n)$ is [Euler's totient function](./euler-totient.md). This sum can be computed in $O(n)$ with a [linear sieve](./sieve.md#筛法求欧拉函数), and the [Du's sieve](./hyperbola.md#杜教筛) brings it down to $O(n^{2/3})$.

More often than the length itself, you need the index of some fraction $r=\dfrac{p}{q}$ in $F_n$. This means computing

$$
1 + \sum_{k = 1}^n\sum_{i=1}^{\lfloor rk\rfloor}[i\perp k] = 1 + \sum_{d=1}^n\mu(d)\sum_{j=1}^{\lfloor n/d\rfloor}\lfloor rj\rfloor.
$$

The right-hand side comes from [Möbius inversion](./mobius.md). Combining a linear sieve with enumerating divisors gives $O(n)$ preprocessing and $O(n\log n)$ per query. Combining Du's sieve with the [floor-sum (Euclidean-like) algorithm](./euclidean.md) gives $O(n^{2/3})$ preprocessing and $O(\sqrt n\log n)$ per query.

Going the other way, to find the fraction with a given index, you can binary search over real numbers in $[0,1]$, or do a [binary search](#fast-algorithm) on the Stern–Brocot tree. The first may be limited by floating-point precision and makes $O(\log V)$ index queries, where $V$ is the precision range. The second has no precision issues but makes $O(\log^2n)$ index queries.

### Farey neighbors

If the fractions $\dfrac{a}{b}$ and $\dfrac{c}{d}$ are adjacent in some Farey sequence, they are called **Farey neighbors**, also known as a Farey pair.

Let $\dfrac{a}{b}<\dfrac{c}{d}$. From the way Farey sequences are built, of two adjacent fractions, the one added later must be the mediant of the other one and its earlier neighbor. So Farey neighbors are also adjacent in some Stern–Brocot sequence, and by the result proved in [Irreducibility](#irreducibility), we must have

$$
bc-ad=1.
$$

Conversely, this condition is also sufficient for two proper fractions in lowest terms to be Farey neighbors. Here is why. Assume $\dfrac{a}{b}$ is the one with the larger denominator. Then both fractions appear in $F_b$. Let $\dfrac{e}{f}$ be the term right after $\dfrac{a}{b}$ in $F_b$. By the necessity already shown, $be-af=1$. But the [linear congruence equation](./linear-equation.md)  $bx-ay=1$ has only one positive integer solution with $y\le b$, so we must have $(e,f)=(c,d)$.

In fact, the next fraction in lowest terms to appear between them must be $\dfrac{a+c}{b+d}$, so $\dfrac{a}{b}$ and $\dfrac{c}{d}$ are adjacent in every Farey sequence of order $\max\{b,d\}$ through $(b+d-1)$.

The figure below shows the Farey neighbor relation for denominators up to $9$:

![](./images/farey-diagram-ford-circle.svg)

The circles in the figure are called [Ford circles](https://en.wikipedia.org/wiki/Ford_circle): for every fraction $\dfrac{p}{q}$ in lowest terms in $[0,1]$, draw a circle centered at $\left(\dfrac{p}{q},\dfrac{1}{2q^2}\right)$ with radius $\dfrac{1}{2q^2}$. The figure shows that the Ford circles of two fractions can only be tangent or disjoint, and two circles are tangent if and only if the two fractions are Farey neighbors. Moreover, for any two tangent circles in the figure, there is exactly one third circle tangent to both. The fraction of this third circle is the mediant of the fractions of the two circles.

To check that tangent circles always correspond to Farey neighbors, compute the distance between the two centers directly:

$$
\left(\dfrac{a}{b}-\dfrac{c}{d}\right)^2 + \left(\dfrac{1}{2b^2}-\dfrac{1}{2d^2}\right)^2 = \left(\dfrac{1}{2b^2}+\dfrac{1}{2d^2}\right)^2+\frac{(bc-ad)^2-1}{b^2d^2}.
$$

Since the two fractions in lowest terms are different, $|bc-ad|\ge 1$, so the two circles can only be tangent or disjoint. Also, they are tangent if and only if $|bc-ad|=1$, which is the same as the two fractions being Farey neighbors.

Finally, let us count the Farey neighbors. Apart from $\left(\dfrac{0}{1},\dfrac{1}{1}\right)$, every pair of Farey neighbors has different denominators. Let $\dfrac{p}{q}$ be the one with the larger denominator. Then the other fraction must be a solution of the linear Diophantine equation

$$
qx-py=\pm 1
$$

Each of the two equations has exactly one positive integer solution with $y<q$, giving the neighbors on the left and on the right of $\dfrac{p}{q}$. So every proper fraction in $(0,1)$ has two Farey neighbors with smaller denominators. Adding in $\dfrac{0}{1}$ and $\dfrac{1}{1}$, this shows that $F_n$ has $(2|F_n|-3)$ pairs of Farey neighbors in total.

Of course, the fractions $\dfrac{a}{b}<\dfrac{c}{d}$ found this way are exactly the left and right neighbors of $\dfrac{p}{q}$ at the moment it is inserted into the sequence. So they are themselves Farey neighbors, and $\dfrac{p}{q}$ is their mediant. If $\dfrac{p}{q}=[t_0,t_1,\cdots,t_n,1]$, then these two Farey neighbors with smaller denominators are $[t_0,t_1,\cdots,t_n]$ and $[t_0,t_1,\cdots,t_{n-1}]$.

To find the other Farey neighbors of $\dfrac{p}{q}$, use the [extended Euclidean algorithm](./bezouts.md#两个变量的情形) to find all valid solutions.

### Recurrence

The Farey sequence has a neat recurrence that produces all fractions of the Farey sequence of order $n$ in order from left to right.

First, the analysis above shows that in $F_n$, a newly added term $\dfrac{p}{n}$ is always the mediant of its left and right neighbors. In fact, this holds for every fraction in $F_n$ (except the two endpoints). Let $\dfrac{a}{b}<\dfrac{p}{q}<\dfrac{c}{d}$. By the necessary and sufficient condition for Farey neighbors, we always have

$$
bp-aq = 1 = cq-dp \iff \frac{p}{q} = \dfrac{a+c}{b+d}.
$$

In general, though, the fraction $\dfrac{a+c}{b+d}$ may need to be reduced.

This observation leads to the following recurrence. Suppose $\dfrac{a}{b}$ and $\dfrac{p}{q}$ are known, and we want the third fraction $\dfrac{c}{d}$. There exists $k$ such that

$$
a+c = kp,\ b+d=kq
$$

holds. The difference

$$
\frac{kp-a}{kq-b} - \dfrac{p}{q} = \dfrac{bp-aq}{q(kq-b)} = \dfrac{1}{q(kq-b)}
$$

decreases as $k$ grows, and the fraction right after $\dfrac{p}{q}$ should be the one with the smallest difference among all fractions with $kq-b\le n$. Therefore, we must have

$$
k = \left\lfloor\dfrac{n+b}{q}\right\rfloor.
$$

One can check that the fraction obtained this way is always in $F_n$. So the numerators and denominators of the fractions in $F_n$ satisfy the recurrence:

$$
\begin{aligned}
p_k &= \left\lfloor\frac{n + q_{k-2}}{q_{k-1}}\right\rfloor p_{k-1} - p_{k-2},\\
q_k &= \left\lfloor\frac{n + q_{k-2}}{q_{k-1}}\right\rfloor q_{k-1} - q_{k-2}.
\end{aligned}
$$

The starting values are $(p_0,q_0)=(0,1)$ and $(p_1,q_1)=(1,n)$.

## Exercises

Problems based on the material in this article:

-   [LOJ 6685. Maze](https://loj.ac/p/6685)
-   [UVa 10077. The Stern-Brocot Number System](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=33&page=show_problem&problem=1018)
-   [Luogu P8058. \[BalkanOI2003\] Farey Sequence](https://www.luogu.com.cn/problem/P8058)
-   [UVa 12995. Farey Sequence](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=862&page=show_problem&problem=4878)
-   [UVa 10408. Farey Sequences](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1349)
-   [UVa 12438. Farey Polygon](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=279&page=show_problem&problem=3869)
-   [AtCoder ARC123F. Insert Addition](https://atcoder.jp/contests/arc123/tasks/arc123_f)

Problems that need binary search on the Stern–Brocot tree:

-   [AtCoder ABC333G. Nearest Fraction](https://atcoder.jp/contests/abc333/tasks/abc333_g)
-   [SPOJ DIVCNT1 - Counting Divisors](https://www.spoj.com/problems/DIVCNT1/)
-   [SPOJ AFS3 - Amazing Factor Sequence (hard)](https://www.spoj.com/problems/AFS3/)

## References and notes

-   [Stern–Brocot tree - Wikipedia](https://en.wikipedia.org/wiki/Stern%E2%80%93Brocot_tree)
-   [Calkin–Wilf tree - Wikipedia](https://en.wikipedia.org/wiki/Calkin%E2%80%93Wilf_tree)
-   [Farey sequence - Wikipedia](https://en.wikipedia.org/wiki/Farey_sequence)

**Parts of this page are translated from the article [Дерево Штерна-Броко. Ряд Фарея](http://e-maxx.ru/algo/stern_brocot_farey) and its English translation [The Stern-Brocot Tree and Farey Sequences](https://cp-algorithms.com/others/stern_brocot_tree_farey_sequences.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0. Other parts of this page are translated from the article [Continued fractions](https://cp-algorithms.com/algebra/continued-fractions.html), licensed under CC-BY-SA 4.0. All content has been modified.**

[^mediant]: The Chinese term for "mediant" used in the original page follows the Chinese translation of *Concrete Mathematics* by Zhang Mingyao and Zhang Fan, Section 4.5.
