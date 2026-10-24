author: Backl1ght

The AHU algorithm checks whether two rooted trees are isomorphic.

Besides this, another common way to check tree isomorphism is [tree hashing](tree-hash.md).

Prerequisites: [Tree basics](tree-basic.md), [Centroid of a tree](tree-centroid.md)

It is a good idea to read this together with the examples given in the references.

## Definition of tree isomorphism

### Isomorphism of rooted trees

For two rooted trees $T_1(V_1,E_1,r_1)$ and $T_2(V_2,E_2,r_2)$, if there is a bijection $\varphi: V_1 \rightarrow V_2$ such that

$$
\forall u,v \in V_1,(u,v) \in E_1 \iff (\varphi(u),\varphi(v))  \in E_2
$$

**and** $\varphi(r_1)=r_2$, then the rooted trees $T_1(V_1,E_1,r_1)$ and $T_2(V_2,E_2,r_2)$ are called isomorphic.

### Isomorphism of unrooted trees

For two unrooted trees $T_1(V_1,E_1)$ and $T_2(V_2,E_2)$, if there is a bijection $\varphi: V_1 \rightarrow V_2$ such that

$$
\forall u,v \in V_1,(u,v) \in E_1 \iff (\varphi(u),\varphi(v))  \in E_2
$$

holds, then the unrooted trees $T_1(V_1,E_1)$ and $T_2(V_2,E_2)$ are called isomorphic.

Put simply: if we can relabel all nodes of tree $T_1$ so that $T_1$ and $T_2$ become **exactly the same**, then the two trees are isomorphic.

## Reducing the problem

The unrooted tree isomorphism problem can be reduced to the rooted one. Here is how:

For unrooted trees $T_1(V_1, E_1)$ and $T_2(V_2,E_2)$, first find **all** centroids of each tree.

-   If the two trees have different numbers of centroids, they are not isomorphic.
-   If both trees have exactly $1$ centroid, call them $c_1$ and $c_2$. Then the unrooted trees $T_1(V_1, E_1)$ and $T_2(V_2,E_2)$ are isomorphic if the rooted trees $T_1(V_1,E_1,c_1)$ and $T_2(V_2,E_2,c_2)$ are isomorphic, and not isomorphic otherwise.
-   If both trees have $2$ centroids, call them $c_1,c'_1$ and $c_2,c'_2$. Then the unrooted trees $T_1(V_1, E_1)$ and $T_2(V_2,E_2)$ are isomorphic if the rooted trees $T_1(V_1,E_1,c_1)$ and $T_2(V_2,E_2,c_2)$ are isomorphic **or** the rooted trees $T_1(V_1,E_1,c'_1)$ and $T_2(V_2,E_2,c_2)$ are isomorphic, and not isomorphic otherwise.

So once we can solve rooted tree isomorphism, we can use the method above to turn unrooted tree isomorphism into rooted tree isomorphism, and solve it that way.

If some algorithm solves rooted tree isomorphism in $O(\left|V\right|)$, then by the method above we can also solve unrooted tree isomorphism in $O(\left|V\right|)$ time.

## The naive AHU algorithm

The naive AHU algorithm is based on bracket sequences.

### Principle 1

A valid bracket sequence corresponds to exactly one rooted tree, and the bracket sequence of a tree is the concatenation of the bracket sequences of its subtrees. If we get a new bracket sequence by changing the order in which the subtrees' sequences are concatenated, then the tree of the new sequence is isomorphic to the tree of the original one.

### Principle 2

Tree isomorphism is transitive. That is, if $T_1$ is isomorphic to $T_2$ and $T_2$ is isomorphic to $T_3$, then $T_1$ is isomorphic to $T_3$.

### Corollary

Consider the recursive algorithm that computes a tree's bracket sequence: we concatenate the subtrees' sequences when backtracking. Suppose that when concatenating we always put the lexicographically smaller sequences first, and call the final result $NAME$.

Let the $NAME$ of the subtree rooted at node $r$ be the $NAME$ of node $r$, written $NAME(r)$. Then for rooted trees $T_1(V_1,E_1,r_1)$ and $T_2(V_2,E_2,r_2)$, if $NAME(r_1)=NAME(r_2)$, then $T_1$ and $T_2$ are isomorphic.

### Naming algorithm

???+ note "Implementation"
    $$
    \begin{array}{ll}
    1 & \textbf{Input. } \text{A rooted tree }T\\
    2 & \textbf{Output. } \text{The name of rooted tree }T\\
    3 & \text{ASSIGN-NAME(u)}\\
    4 & \qquad \text{if  } u \text{  is a leaf}\\
    5 & \qquad \qquad \text{NAME(} u \text{) = (0)}\\
    6 & \qquad \text{else }\\
    7 & \qquad \qquad \text{for all child } v \text{ of } u\\
    8 & \qquad \qquad \qquad \text{ASSIGN-NAME(}v\text{)}\\
    9 & \qquad \text{sort the names of the children of }u\\
    10 & \qquad \text{concatenate the names of all children }u\text{ to temp}\\
    11 & \qquad \text{NAME(} u \text{) = (temp)}
    \end{array}
    $$

### The AHU algorithm

???+ note "Implementation"
    $$
    \begin{array}{ll}
    1 & \textbf{Input. } \text{Two rooted trees }T_1(V_1,E_1,r_1)\text{ and }T_2(V_2,E_2,r_2) \\
    2 & \textbf{Output. } \text{Whether these two trees are isomorphic}\\
    3 & \text{AHU}(T_1(V_1,E_1,r_1), T_2(V_2,E_2,r_2))\\
    4 & \qquad \text{ASSIGN-NAME(}r_1\text{)}\\
    5 & \qquad \text{ASSIGN-NAME(}r_2\text{)}\\
    6 & \qquad \text{if  NAME}(r_1) = \text{NAME}(r_2)\\
    7 & \qquad \qquad \text{return true}\\
    8 & \qquad \text{else}\\
    10 & \qquad \qquad \text{return false}
    \end{array}
    $$

### Complexity proof

For a rooted tree with $n$ nodes, if it is a chain, a node's name can be up to $n$ long. Then the cost of ASSIGN-NAME is a constant times $1+2+\cdots+n$, which is $\Theta(n^2)$. So the naive AHU algorithm runs in $O(n^2)$.

## The optimized AHU algorithm

The weakness of the naive AHU algorithm is that a tree's $NAME$ can get very long. We can optimize exactly this.

### Principle 1

Split the tree into levels: nodes on level $i$ are at shortest distance $i$ from the root. The $NAME$ of a node on level $i$ can be built **only** by concatenating the $NAME$s of nodes on level $i+1$.

### Principle 2

Within one level, a node's $NAME$ can be uniquely identified by its rank within that level.

**Note**: here the rank is taken over both trees. If node $u$ is on level $i$, then the rank of $u$ equals the number of nodes on level $i$ of $T_1$ and $T_2$ whose $NAME$ is smaller than $NAME(u)$.

### Corollary

We can replace each node's original $NAME$ with its rank within its level, and replace string concatenation of $NAME$s with appending elements to an array.

Using integers and arrays instead of strings does not affect correctness, and it greatly lowers the complexity.

### Complexity proof

First note that the total length of the concatenated $NAME$s on level $i$ is the sum of the degrees of the nodes on level $i$, which is the total number of nodes on level $i+1$. Call it $L_i$. The next step of the algorithm treats these $NAME$s as strings (arrays), sorts them, and replaces each with its rank in the level (that is, remaps it to a single number). The following lemma gives the cost of sorting $m$ strings with total length $L$:

1.  We can sort them with radix sort in $O(L+|\Sigma|)$ time, where $|\Sigma|$ is the alphabet size. (There are some implementation details; see the references.)
2.  We can sort them with quicksort in $O(L \log m)$ time. The rough idea of the proof: the recursion tree of quicksort has height $O(\log m)$, and comparing two strings of lengths $\ell_1$ and $\ell_2$ directly costs $O(\min\{\ell_1,\ell_2\})$.

In the AHU algorithm, the alphabet for the strings on level $i$ has size at most the number of nodes on level $i+1$, which is $L_i$, so radix sort runs in linear time. Since $\sum_i L_i=O(n)$, adding up the cost over all levels shows that with radix sort on strings, the total complexity is $T(n)=O(n)$. Likewise, if we sort the strings with quicksort, then $T(n)=O(n \log n)$.

## Example problem

[SPOJ-TREEISO](https://www.spoj.com/problems/TREEISO/en/)

Problem summary: given two unrooted trees, decide whether they are isomorphic.

???+ note "Reference code"
    ```cpp
    --8<-- "docs/graph/code/tree-ahu/tree-ahu_1.cpp"
    ```

## References

Most of this article is translated from the [Paper](http://wwwmayr.in.tum.de/konferenzen/Jass08/courses/1/smal/Smal_Paper.pdf) and the [Slide](https://logic.pdmi.ras.ru/~smal/files/smal_jass08_slides.pdf). The proofs in the references are more complete and rigorous; this article simplifies them somewhat.

For the complexity analysis of the AHU algorithm and a linear-time radix sort for strings, see Section 3.2, Radix sorting, of The Design and Analysis of Computer Algorithms, and Example 3.2 there.
