author: cesonic, Enter-tainer, Great-designer, Ir1d, ksyx, lychees, MegaOwIer, RUIN-RISE, wjy-yy, rsdbkhusky, ouuan, Menci, Tiphereth-A

Recall the idea of basis vectors from solid geometry in high school math. In three-dimensional Euclidean space we can find a set of basis vectors $\boldsymbol{i}$, $\boldsymbol{j}$, $\boldsymbol{k}$, and then every vector in the space can be written in terms of them. In other words, we can **describe the infinite three-dimensional space with finitely many basis vectors**, which shows how important basis vectors are.

Three-dimensional Euclidean space is a special [vector space](./vector-space.md), and its basis vectors generalize to a basis of a vector space.

In OI, applications of bases usually involve only two kinds of vector spaces: the $n$-dimensional real vector space $\mathbf{R}^n$ and the $n$-dimensional vector space over the [Boolean domain](https://en.wikipedia.org/wiki/Boolean_domain) $\mathbf{Z}_2^n$. We cover them in detail in the [Applications](#applications) section. If you are not familiar with linear algebra, we recommend starting from the applications part.

Below we introduce bases starting from general vector spaces, and give their common properties.

Prerequisites: [vector space](./vector-space.md).

A basis of a vector space (also called a linear basis) is an important tool for studying vector spaces.

## Definition

A maximal linearly independent set of a vector space $V$ is called a **Hamel basis** or **linear basis** of $V$, or simply a **basis**.

By convention, the basis of the vector space $\{\theta\}$ is the empty set.

One can prove that every vector space has a basis[^existence_basis]. We define the **dimension** of a vector space $V$ as the number of elements (or cardinality) of a basis, written $\dim V$.

## Properties

1.  Let $V$ be a finite-dimensional vector space of dimension $n$. Then:

    1.  Any $n+1$ vectors in $V$ are linearly dependent.

    2.  Any $n$ linearly independent vectors in $V$ form a basis of $V$.

    3.  If every vector in $V$ is a linear combination of the vectors $a_1,a_2,\dots,a_n$, then they form a basis of $V$.

        ???+ note "Proof"
            Take any basis $b_1,b_2,\dots,b_n$ of $V$. By assumption, $b_1,b_2,\dots,b_n$ are linear combinations of $a_1,a_2,\dots,a_n$, so
            
            $$
            n=\operatorname{rank}\{b_1,b_2,\dots,b_n\}\leq\operatorname{rank}\{a_1,a_2,\dots,a_n\}\leq n
            $$
            
            Hence $\operatorname{rank}\{a_1,a_2,\dots,a_n\}=n$

    4.  Any linearly independent set $a_1,a_2,\dots,a_m$ in $V$ can be extended to a basis of $V$ by adding some vectors.

2.  (Dimension formula for subspaces) Let $V_1,V_2$ be finite-dimensional vector spaces over $\Bbb{P}$ such that $V_1+V_2$ and $V_1\cap V_2$ are also finite-dimensional. Then $\dim V_1+\dim V_2=\dim(V_1+V_2)+\dim(V_1\cap V_2)$

    ???+ note "Proof"
        Let $\dim V_1=n_1$,$\dim V_2=n_2$,$\dim(V_1\cap V_2)=m$.
        
        Take a basis $a_1,a_2,\dots,a_m$ of $V_1\cap V_2$ and extend it to bases of $V_1$ and $V_2$: $a_1,a_2,\dots,a_m,b_1,b_2,\dots,b_{n_1-m}$ and $a_1,a_2,\dots,a_m,c_1,c_2,\dots,c_{n_2-m}$.
        
        It is enough to show that the vectors $a_1,a_2,\dots,a_m,b_1,b_2,\dots,b_{n_1-m},c_1,c_2,\dots,c_{n_2-m}$ are linearly independent.
        
        Suppose $\sum_{i=1}^m r_ia_i+\sum_{i=1}^{n_1-m} s_ib_i+\sum_{i=1}^{n_2-m} t_ic_i=\theta$.
        
        Then $\sum_{i=1}^{n_2-m} t_ic_i=-\sum_{i=1}^m r_ia_i-\sum_{i=1}^{n_1-m} s_ib_i$.
        
        The left side lies in $V_2$ and the right side lies in $V_1$, so both sides lie in $V_1\cap V_2$. Hence $\sum_{i=1}^{n_2-m} t_ic_i=\sum_{i=1}^m k_ia_i$
        
        So $t_1=t_2=\dots=t_{n_2-m}=k_1=k_2=\dots=k_m=0$, and then $r_1=r_2=\dots=r_m=s_1=s_2=\dots=s_{n_1-m}=t_1=t_2=\dots=t_{n_2-m}=0$

3.  Let $V_1,V_2$ be finite-dimensional vector spaces over $\Bbb{P}$ such that $V_1+V_2$ and $V_1\cap V_2$ are also finite-dimensional. Then the following are equivalent:

    1.  $V_1+V_2=V_1\oplus V_2$.

    2.  $\dim V_1+\dim V_2=\dim(V_1+V_2)$.

    3.  If $a_1,a_2,\dots,a_n$ is a basis of $V_1$ and $b_1,b_2,\dots,b_m$ is a basis of $V_2$, then $a_1,a_2,\dots,a_n,b_1,b_2,\dots,b_m$ is a basis of $V_1+V_2$.

    ???+ note "Note"
        Items 1 and 3 generalize to infinite-dimensional vector spaces.

## Examples

Consider bases of $\Bbb{R}^2$.

1.  As shown in the figure

    ![](./images/basis-1.svg)

    $u,v$ is a basis.

2.  As shown in the figure

    ![](./images/basis-2.svg)

    $u,v$ is a basis.

3.  As shown in the figure

    ![](./images/basis-3.svg)

    $u,v$ is not a basis, because $u=-v$.

4.  As shown in the figure

    ![](./images/basis-4.svg)

    $u,v,w$ is not a basis, because $u+4v+6w=\theta$.

## Orthogonal bases and orthonormal bases

If a basis $B$ of a vector space $V$ satisfies $\forall b,b'\in B,~(b,b')\ne 0\iff b=b'$ (that is, its vectors are pairwise orthogonal), it is called an **orthogonal basis**.

If an orthogonal basis $B$ of $V$ also satisfies $\forall b\in B,~|b|=\sqrt{(b,b)}=1$, it is called an **orthonormal basis**.

Any basis of a finite-dimensional vector space $V$ can be turned into an orthogonal basis with [Gram–Schmidt orthogonalization](https://en.wikipedia.org/wiki/Gram%E2%80%93Schmidt_process).

## Applications

Based on the above, we can use a basis to:

1.  find the rank of a given set of vectors;
2.  for a given set of vectors, find a maximal linearly independent subset (or a basis of the space it spans);
3.  insert some vectors into a given set, and find a maximal linearly independent subset of the new set (or a basis of the space it spans);
4.  for a maximal linearly independent subset (or basis) we found, decide whether a given vector is a linear combination of it;
5.  for a maximal linearly independent subset (or basis) we found, find special elements of the space it spans (such as the largest or smallest element).

In OI, a basis of the $n$-dimensional real vector space $\mathbf{R}^n$ is usually called a **real linear basis**, and a basis of the $n$-dimensional Boolean vector space $\mathbf{Z}_2^n$ is called a **XOR basis**.

???+ tip "Tip"
    In $\mathbf{Z}_2$, addition is XOR and multiplication is AND. One can prove that $\mathbf{Z}_2$ is a field.
    
    One can prove that the algebraic system $(\mathbf{Z}_2^n,+,\cdot,\mathbf{Z}_2)$ is a vector space, where:
    
    $$
    (a_1,\dots,a_n)+(b_1,\dots,b_n):=(a_1+b_1,\dots,a_n+b_n),
    $$
    
    $$
    k\cdot(a_1,\dots,a_n):=(ka_1,\dots,ka_n).
    $$
    
    That is, addition is XOR and scalar multiplication is AND.

Take the XOR basis as an example. From a given set of Boolean sequences $X=\{x_1,\dots,x_m\}$ we can build a XOR basis $B=\{b_1,\dots,b_n\}$ with the following properties:

1.  The XOR of any non-empty subset of $B$ is not $0$;
2.  For any element $x$ of $X$, we can pick some elements of $B$ whose XOR is $x$;
3.  Any set $B'$ satisfying the two properties above has at least as many elements as $B$.

With a XOR basis we can:

1.  decide whether a number can be written as the XOR of a subset of a given set of numbers;
2.  count the ways a number can be written as the XOR of a subset of a given set;
3.  find the maximum / minimum / $k$-th largest / $k$-th smallest XOR of a subset of a given set;
4.  find the rank of a number among the subset XORs of a given set.

### How to build one

A XOR basis and a real linear basis are not essentially different, so below we use the XOR basis as the example. The code for a real linear basis needs only small changes.

#### Greedy method

Write each number $p$ in the original set in binary and scan from the highest bit to the lowest. For each bit $x$ that is $1$: if $a_x$ does not exist, set $a_x \leftarrow p$ and stop scanning; if it exists, set $p\leftarrow p~\text{xor}~a_x$.

To find the maximum $\text{xor}$ of any elements of the original set, scan the basis from the highest bit to the lowest. If XORing the current $a_x$ into the answer makes the answer larger, XOR $a_x$ into the answer.

Why does this work? Because we scan from high bits to low bits, when we are at bit $i$, we can guarantee that bit $i$ of the answer is $1$, and later steps have no chance to change bit $i$.

The minimum $\text{xor}$ of any elements of the original set is simply the smallest element of the basis.

Checking whether a number can be obtained by XOR works like insertion: if the number $p$ being inserted ends up XORed to $0$, then it can be obtained.

??? example "Code (Luogu P3812 [Template: Linear Basis](https://www.luogu.com.cn/problem/P3812))"
    ```cpp
    --8<-- "docs/math/code/basis/basis_1.cpp"
    ```

#### Gaussian elimination method

Gaussian elimination builds the basis from the point of view of a system of linear equations, and its correctness is obvious.

??? example "Code (Luogu P3812 [Template: Linear Basis](https://www.luogu.com.cn/problem/P3812))"
    ```cpp
    --8<-- "docs/math/code/basis/basis_2.cpp"
    ```

### Properties

A basis built with the greedy method has these properties:

-   No subset of the basis has XOR equal to $0$.
-   The numbers in the basis all have different highest set bits.

A basis built with Gaussian elimination has this property:

-   The matrix after Gaussian elimination is in reduced row echelon form.

    > This property includes both properties of the basis built with the greedy method.

    If you don't see why this property holds, see [Gaussian elimination](../numerical/gauss.md).

Here is a sample input:

```text
5
633 211 169 841 1008
```

In binary:

```text
1001111001
0011010011
0010101001
1101001001
1111110000
```

The basis produced by the greedy method:

```text
1001111001
0100110000
0011010011
0001111010
0000000000
0000010000
0000000000
0000000000
0000000000
0000000000
```

The basis produced by Gaussian elimination:

```text
1000000011
0100100000
0010101001
0001101010
0000010000
0000000000
0000000000
0000000000
0000000000
0000000000
```

This is a very nice property that makes many problems easier. For example: given some numbers, choose some of them and XOR them together to get the maximum value. With the greedy basis, we need another greedy pass: if the current bit of `ans` is `0`, XORing always helps; if the current bit is `1`, it never helps. With the Gaussian elimination basis, we simply XOR all elements of the basis together and output the result.

For other classic problems (checking whether a number can be obtained by XOR, finding the $k$-th largest obtainable number, and so on), the basis from Gaussian elimination also makes things easier.

### Time complexity

Let the vector length be $n$ and the number of vectors be $m$. The time complexity is $O(nm)$. Gaussian elimination has a slightly larger constant factor.

For a real linear basis, the time complexity is $O(n^2m)$.

### Merging bases

To merge bases, just use brute force: insert every vector of one basis into the other. One merge takes $O(n^2)$ time (XOR basis) or $O(n^3)$ time (real linear basis).

### Intersecting bases

Strictly speaking, intersecting two bases means finding a basis of the intersection of the two spaces they span. This section introduces two algorithms. Both take $O(n^2)$ time (XOR basis) or $O(n^3)$ time (real linear basis) per intersection.

#### Naive algorithm

Let the bases to intersect be $\alpha$ and $\beta$. The intersection algorithm only needs the following changes to the brute-force merge algorithm (using the XOR basis as the example):

-   Try to insert each vector $\beta_j$ of basis $\beta$ into $\alpha$ using the [greedy method](#greedy-method), and initialize the intersection $\gamma$ as the empty set;
-   During insertion, record the contribution of elements of $\beta$ to the vector being inserted. Specifically, keep a new vector $b$, initialized to $\beta_j$. Whenever the vector being inserted is XORed with the basis vector at position $x$, also XOR the contribution $b$ with the contribution $b_x$ recorded at position $x$;
-   If the insertion succeeds and the vector $\beta_j'$ is placed at position $x$ of the basis, set the recorded $b_x$ at position $x$ to the contribution $b$ of elements of $\beta$ collected while producing $\beta_j'$;
-   If the insertion fails, insert the recorded contribution $b$ of elements of $\beta$ into $\gamma$.

The resulting basis $\gamma$ is the intersection we want. Of course, the algorithm also finds the union of the bases.

??? note "Explanation of the algorithm"
    Let the merged basis be $\{\alpha_1,\cdots,\alpha_m,\beta'_{j_1},\cdots,\beta'_{j_\ell}\}$, where $\beta'_{j_k}$ is the vector finally obtained when inserting $\beta_{j_k}$. Then $\{\alpha_1,\cdots,\alpha_m,\beta_{j_1},\cdots,\beta_{j_\ell}\}$ is also a merged basis. Write $\beta^+$ for the set $\{\beta_{j_1},\cdots,\beta_{j_\ell}\}$, so the merged basis can be written as $\alpha\cup\beta^+$. Moreover, every vector $c$ in the sum space can be uniquely written as
    
    $$
    c = a\oplus b
    $$
    
    where $a\in\operatorname{span}\alpha$ and $b\in\operatorname{span}\beta^+$. The $b$ in this decomposition is exactly the "contribution of elements of $\beta$" that the algorithm above **tries** to record. Strictly speaking, it is only the contribution of the vectors of $\beta$ that were successfully inserted in the end.
    
    For a successful insertion, the final recorded $b$ is the $b$ term of this decomposition. Let $\beta_j\in\beta^+$. Initially $\beta_j=0\oplus\beta_j$, which is already the correct decomposition of $\beta_j$ over the basis $\alpha\cup\beta^+$. When we update $\beta'_j=a\oplus b$ to $\beta'_j\oplus c_x$, since $\beta_j'\oplus c_x=(a\oplus a_x)\oplus(b\oplus b_x)$, we only need to update $b$ to $b\oplus b_x$ to keep the decomposition correct. So by induction, when $\beta'_j$ is finally inserted into the merged basis, the recorded contribution $b$ is the $b$ term of the decomposition above.
    
    For a failed insertion, the vector being inserted must end up as $0$, and then the contribution $b$ is inserted into $\gamma$. Repeating the argument above, we still always have $\beta_j'=a\oplus b$ during insertion with $a\in\operatorname{span}\alpha$, except that $b$ no longer lies in $\operatorname{span}\beta^+$. This is because at initialization, the $\beta_j$ in $\beta_j=0\oplus\beta_j$ satisfies $\beta_j\notin\beta^+$. Apart from that, every term XORed in when updating the contribution lies in $\operatorname{span}\beta^+$. So in fact $b\oplus\beta_j\in\operatorname{span}\beta^+$.
    
    So why does inserting all these $b$ from failed insertions into $\gamma$ give a basis of the intersection? First, if inserting $\beta_j$ fails, we must end with $0=a\oplus b$, where $a\in\operatorname{span}\alpha$ and $b\in\operatorname{span}(\beta^+\cup\{\beta_j\})\subseteq\operatorname{span}\beta$. Hence $b=a$ must lie in the intersection $\operatorname{span}\alpha\cap\operatorname{span}\beta$. Conversely, let $c$ be any element of the intersection. Since $c\in\operatorname{span}\beta$, $c$ can be written as a linear combination (XOR sum) of elements of $\beta$:
    
    $$
    c = \bigoplus_{\beta_j\in\beta}\lambda_j\beta_j,
    $$
    
    where $\lambda_j\in\{0,1\}$. For each $\beta_j\notin\beta^+$, let $b_j$ be the corresponding contribution inserted into $\gamma$. Then
    
    $$
    c\oplus\bigoplus_{\beta_j\notin\beta^+}\lambda_jb_j = \bigoplus_{\beta_j\in\beta^+}\lambda_j\beta_j+\bigoplus_{\beta_j\notin\beta^+}\lambda_j(\beta_j\oplus b_j),
    $$
    
    Note that $b_j$ and $c$ both lie in the intersection, so the left side also lies in the intersection, and hence it can be written as a linear combination of elements of $\alpha$. Meanwhile, every term on the right side has either $\beta_j\in\beta^+$, or $\beta_j\notin\beta^+$ and $\beta_j\oplus b_j\in\beta^+$, so the right side is actually a linear combination of elements of $\beta^+$. But $\alpha\cup\beta^+$ is linearly independent, so all coefficients are $0$. That is, $c=\bigoplus_{\beta_j\notin\beta^+}\lambda_jb_j\in\operatorname{span}\{b_1,\cdots,b_j\}$. This shows that the contributions $b$ of the vectors that failed to insert together span the intersection.
    
    From this explanation, the real purpose of maintaining the contribution $b$ is to maintain the decomposition $a\oplus b$. Also, when a contribution is finally inserted into $\gamma$, we always have $a=b$. So whether we maintain the contribution of elements of $\alpha$ or of $\beta$ (that is, whether we maintain $a$ or $b$), the result is correct. To maintain the contribution of elements of $\alpha$, just change the initial contributions: each vector $\alpha_i$ in $\alpha$ starts with contribution $\alpha_i$, and each inserted $\beta_j$ starts with contribution $0$.

Code for the template problem:

??? example "Code (Library Checker [Intersection of $\mathbf F_2$ vector spaces](https://judge.yosupo.jp/problem/intersection_of_f2_vector_spaces))"
    ```cpp
    --8<-- "docs/math/code/basis/basis_intersect_1.cpp"
    ```

#### Zassenhaus algorithm

An equivalent approach is the Zassenhaus algorithm, which also computes both the union and the intersection of two bases. Its complexity is exactly the same as above.

The steps are:

-   Initialize an empty basis $\gamma$ of vectors of length $2n$. Write its vectors as $(a,b)$, where $a$ and $b$ both have length $n$;
-   Insert each element $\alpha_i$ of $\alpha$ into $\gamma$ as $(\alpha_i,\alpha_i)$;
-   Insert each element $\beta_j$ of $\beta$ into $\gamma$ as $(\beta_j,0)$;
-   Among all non-zero elements $(c_k,d_k)$ of the final basis $\gamma$, the $c_k$ from the vectors with non-zero $c_k$ together form a basis of the union of $\alpha$ and $\beta$, and the $d_k$ from the vectors with zero $c_k$ together form a basis of the intersection of $\alpha$ and $\beta$.

The basis-building method used in the algorithm can be the [greedy method](#greedy-method) or [Gaussian elimination](#gaussian-elimination-method), as long as the basis $\gamma$ forms a matrix in row echelon form.

Comparing the elimination steps of the Zassenhaus algorithm with the naive algorithm above, it is easy to see that the Zassenhaus algorithm based on the greedy method is the same as the naive algorithm that maintains the contribution of elements of $\alpha$. If we instead first insert all $(\alpha_i,0)$ and then insert all $(\beta_j,\beta_j)$, the greedy-based Zassenhaus algorithm becomes the naive algorithm that maintains the contribution of elements of $\beta$. Since the elimination steps are equivalent, the Zassenhaus algorithm is also correct.

Besides that, here is an independent and more general algebraic proof:

??? note "Proof of correctness"
    Let $V$ be a vector space with subspaces $U=\operatorname{span}\alpha$ and $W=\operatorname{span}\beta$. The algorithm reduces to row echelon form to find a basis $\gamma$ of the subspace
    
    $$
    H = \operatorname{span}(\{(\alpha_i,\alpha_i):\alpha_i\in\alpha\}\cup\{(\beta_j,0):\beta_j\in\beta\})
    $$
    
    At the end of the algorithm, the elements $(c_k,d_k)$ of $\gamma$ are split into two groups by whether $c_k\neq 0$, so consider the projection $\pi:H\rightarrow V$ with $\pi(a,b)=a$. Then $\pi(H)=U+W$, and it is easy to check that
    
    $$
    \begin{aligned}
    \ker\pi &= H\cap(\{0\}\times V) = \{0\}\times(U\times W).
    \end{aligned}
    $$
    
    By the [theorems on linear maps](./linear-mapping.md#kernel-and-image-of-a-linear-map), $\dim H = \dim\pi(H)+\dim\ker\pi = \dim(U+W)+\dim(U\cap W)$.
    
    The first few columns of a matrix in row echelon form are still in row echelon form, so the number of rows with $c_k\neq 0$ equals the row rank of $\alpha\cup\beta$, i.e. $\dim(U+W)$; moreover, the $c_k$ of these rows form a basis of $U+W$. The remaining non-zero rows number exactly $\dim(U\cap W)$, and all have $c_k=0$. For the $d_k$ in these rows, since $(0,d_k)\in\ker\pi$, we have $d_k\in U\cap W$; also, the $(0,d_k)$ are rows of a row echelon matrix, so they are linearly independent, which means the $d_k$ are linearly independent. Together, the $d_k$ form a linearly independent set of size $\dim(U\cap W)$ in the intersection $U\cap W$, so they must be a basis of that space.

Code for the template problem:

??? example "Code (Library Checker [Intersection of $\mathbf F_2$ vector spaces](https://judge.yosupo.jp/problem/intersection_of_f2_vector_spaces))"
    ```cpp
    --8<-- "docs/math/code/basis/basis_intersect_2.cpp"
    ```

Note that when printing, you only need to consider the vectors whose first $n$ bits are all zero.

### Extension: prefix linear basis

This section only covers XOR bases, and assumes that a single vector can be stored in $O(1)$ space and that each single operation takes $O(1)$ time.

When we need to answer many queries for the maximum XOR over a range, a common approach is a [cat tree](../../ds/cat-tree.md) combined with linear bases, with time complexity $O(nm\log m+n^2q)$, where $n$ is the vector length, $m$ is the sequence length and $q$ is the number of queries. Another approach uses a prefix linear basis (also called a timestamped linear basis), which brings the complexity down to $O(n(m+q))$.

A prefix linear basis maintains, for each prefix of the sequence, the bases of all suffixes of that prefix, so it can answer queries for the basis of any range. Note that the bases of all suffixes $[j,i]$ of a prefix $[1,i]$ are nested: the basis of $[j,i]$ always contains the basis of $[j+1,i]$. So among these suffix bases there are at most $n$ distinct ones, and we can always get all the suffix bases from $[i,i]$ to $[1,i]$ by adding new vectors one at a time to the empty set. Using this monotonicity, we only need to mark each added vector $v$ with the largest index $t$ at which it appears, and then we can store the bases of all suffixes in $O(n)$ space. To query the basis of range $[j,i]$, take the prefix linear basis at $i$ and keep only the vectors with mark $t\ge j$.

Call the mark $t$ of each vector $v$ its timestamp. A vector $v$ in the basis can always be written as the XOR of some elements of the original sequence, such as $v_{i_1}\oplus v_{i_2}\oplus\cdots\oplus v_{i_k}$. Over all such possible representations, the largest possible minimum index is $t$, that is,

$$
t(v) = \max\{j:\exists i_1,\cdots,i_k\in[j,i]\text{ s.t. }v=v_{i_1}\oplus v_{i_2}\oplus\cdots\oplus v_{i_k}\}.
$$

This expression just restates the previous paragraph in formal language. What it suggests is that to maintain the timestamp of each vector $v$ in the basis, we only need to greedily replace old vectors with vectors that are as new as possible.

Starting from the [greedy method](#greedy-method) above, the prefix linear basis makes the following changes during construction:

-   Store a timestamp $t_x$ for every vector $a_x$ kept in the basis, initially all $0$;
-   To add the $i$-th vector $v$ of the sequence, still scan from the highest bit to the lowest, but also keep track of the current time $i$;
-   If bit $x$ of $v$ is one, compare the timestamp $t_x$ of the existing basis vector $a_x$ with the current time $i$:
    -   If $i>t_x$, the vector being added is newer: set $a_x$ to $v$, update the timestamp to $i$, and continue the adding process with $a_x\oplus v$ (the old $a_x$ XOR $v$) using the previously recorded time $t_x$;
    -   If $i<t_x$, the vector being added is older: leave $a_x$ and $t_x$ unchanged, XOR $v$ with $a_x$, and continue adding.

In other words, if the current bit can be represented by a newer vector, use the newer vector; otherwise keep the old one. When updating the vector at position $x$, we cannot store the XOR result $a_x\oplus v$ at position $x$, because its timestamp is $\min\{t(a_x)=t(v)\}=t(a_x)$, which is smaller than the timestamp $t(v)$ of the vector $v$ being added. For the same reason, building a basis with [Gaussian elimination](#gaussian-elimination-method) may break the timestamp property when it updates upward, so it no longer works for building a prefix linear basis.

Code for the template problem:

??? example "Code (Codeforces [1100F Ivan and Burgers](https://codeforces.com/problemset/problem/1100/F))"
    ```cpp
    --8<-- "docs/math/code/basis/prefix_basis.cpp"
    ```

If queries must be answered online, we can also spend $O(mn)$ space to store the prefix linear basis at every prefix and then query. This can be seen as a kind of "persistent" linear basis. If you need the properties of the basis produced by Gaussian elimination, handle that separately at query time.

### Exercises

-   [Luogu P3812 Template: Linear Basis](https://www.luogu.com.cn/problem/P3812)
-   [Acwing 3164. Linear Basis](https://www.acwing.com/problem/content/description/3167)
-   [SGU 275 to xor or not xor](https://codeforces.com/problemsets/acmsguru/problem/99999/275)
-   [HDU 3949 XOR](https://acm.hdu.edu.cn/showproblem.php?pid=3949)
-   [HDU 6579 Operation](https://acm.hdu.edu.cn/showproblem.php?pid=6579)
-   [Luogu P4151 \[WC2011\] Maximum XOR Path](https://www.luogu.com.cn/problem/P4151)
-   [Library Checker - Intersection of $\mathbf F_2$ vector spaces](https://judge.yosupo.jp/problem/intersection_of_f2_vector_spaces)
-   [AtCoder Grand Contest 045 A - Xor Battle](https://atcoder.jp/contests/agc045/tasks/agc045_a)
-   [Codeforces 1100F Ivan and Burgers](https://codeforces.com/problemset/problem/1100/F)
-   [Luogu P3292 \[SCOI2016\] Lucky Numbers](https://www.luogu.com.cn/problem/P3292)

## References and notes

1.  Qiu Weisheng, *Advanced Algebra* (Volume 2). Tsinghua University Press.
2.  [Basis (linear algebra) - Wikipedia](https://en.wikipedia.org/wiki/Basis_%28linear_algebra%29)
3.  [Vector Basis -- from Wolfram MathWorld](https://mathworld.wolfram.com/VectorBasis.html)
4.  [Zassenhaus algorithm - Wikipedia](https://en.wikipedia.org/wiki/Zassenhaus_algorithm)

[^existence_basis]: [Proof that every vector space has a basis](https://en.wikipedia.org/wiki/Basis_%28linear_algebra%29#Proof_that_every_vector_space_has_a_basis)
