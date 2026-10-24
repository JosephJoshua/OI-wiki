## Introduction

A **matroid** is an abstract algebraic structure introduced by Hassler Whitney in 1935. It unifies and generalizes the idea of independence, such as linear independence in linear algebra and acyclicity in graph theory.

Matroids are a powerful theoretical tool for optimization problems involving independence. They are widely used in combinatorics, graph theory, algorithm design and other fields, and in particular they give a mathematical foundation for optimization methods such as greedy algorithms.

## Definition

### Matroid

A **matroid** can be written as $M = (E, \mathcal{I})$, where:

-   $E$ is a finite set, called the **ground set**.
-   $\mathcal{I}$ is a family of subsets of $E$, called the **family of independent sets**; its members are called **independent sets**. It has the following three properties:

    -   **Non-emptiness**: the empty set is independent, i.e., $\emptyset \in \mathcal{I}$.

    -   **Hereditary property**: every subset of an independent set is independent. If $I \in \mathcal{I}$, then $I' \in \mathcal{I}$ for every $I' \subseteq I$.

    -   **Exchange (augmentation) property**: if $I, J \in \mathcal{I}$ and $|I| < |J|$, then there is $j \in J \setminus I$ such that $I \cup \{j\} \in \mathcal{I}$.

A structure of the form $(E, \mathcal{I})$ that satisfies these three properties is called a matroid.

### Basis

A **basis** is a maximal independent set of the matroid, that is, an independent set to which no element can be added while keeping it independent. The set of all bases is called the **family of bases**, written $\mathcal{B}$.

**Properties**:

1.  **Equal cardinality**: all bases have the same size, called the **rank** of the matroid.

2.  **Extension**: every independent set can be extended to a basis by adding elements of a basis.

### Circuit

A **circuit** is a minimal dependent set of the matroid: all of its proper subsets are independent, but it is not independent itself. No circuit contains another circuit.

### Rank

The **rank function** $r: 2^E \rightarrow \mathbb{Z}_{\geq 0}$ maps subsets of the ground set $E$ to non-negative integers. For any $S \subseteq E$, $r(S)$ is defined as the size of the largest independent set inside $S$:

$$
r(S) = \max \{ |I| \mid I \subseteq S \wedge I \in \mathcal{I} \}.
$$

**Properties**:

1.  **Non-negativity (boundedness)**: for any $S \subseteq E$, $0 \leq r(S) \leq |S|$.

2.  **Monotonicity**: if $A \subseteq B \subseteq E$, then $r(A) \leq r(B)$.

3.  **Submodularity**: for any $A, B \subseteq E$, $r(A \cup B) + r(A \cap B) \leq r(A) + r(B)$.

## Typical examples

### 1. Uniform matroid

**Definition**: given a ground set $E$ and a non-negative integer $k$, the independent sets of the uniform matroid $U_{k,E}$ are all subsets of size at most $k$:

$$
\mathcal{I} = \{ I \subseteq E \mid |I| \leq k \}.
$$

-   **Bases**: all subsets of size $k$.

-   **Circuits**: all subsets of size $k + 1$.

-   **Rank**: $r(E) = \min(k, |E|)$, i.e., an independent set has at most $k$ elements.

### 2. Graphical matroid

**Definition**: given an undirected graph $G = (V, E)$, the ground set of the graphical matroid $M(G)$ is the edge set $E$, and its independent sets are all edge sets that contain no cycle, i.e., all forests.

-   **Bases**: the spanning trees of the graph (if the graph is connected). A spanning tree is a maximal independent set: adding any edge creates a cycle.

-   **Circuits**: the simple cycles of the graph. Removing any edge from a cycle leaves an independent set.

-   **Rank**: $r(E) = |V|  - c$, where $c$ is the number of connected components of the graph. For a connected undirected graph, the rank is the number of vertices minus one, $|V|  - 1$.

### 3. Linear matroid

**Definition**: linear matroids are based on vector spaces. Given a vector space $V$, the ground set $E$ is a finite set of vectors in $V$, and the independent sets are all linearly independent subsets of $E$.

-   **Bases**: maximal linearly independent sets of vectors; their size equals the dimension of the vector space.

-   **Circuits**: minimal linearly dependent sets of vectors: every proper subset is independent, but the set itself is linearly dependent.

-   **Rank**: the rank of a linear matroid is $r(E) = \dim(V)$, the dimension of the vector space. An independent set cannot be larger than the dimension of the vector space.

### 4. Partition matroid

**Definition**: partition the ground set $E$ into disjoint subsets $E_1, E_2, \dots, E_m$, and assign each subset $E_i$ a non-negative integer $k_i$. The independent sets of the partition matroid are the subsets that take at most $k_i$ elements from each part:

$$
\mathcal{I} = \left\{ I \subseteq E \mid \forall i,\, |I \cap E_i|  \leq k_i \right\}.
$$

-   **Bases**: the independent sets with $|I \cap E_i| = k_i$ are the bases of the partition matroid. Each basis takes exactly $k_i$ elements from each part.

-   **Circuits**: the circuits of a partition matroid are its minimal dependent sets, i.e., sets that take more than $k_i$ elements from at least one part (minimally so).

-   **Rank**: the rank of a partition matroid is $r(E) = \sum_{i=1}^m k_i$, i.e., the size of the largest independent set equals the sum of the maximum numbers of elements allowed from each part.

### 5. Colored matroid

**Definition**: a colored matroid is a special form of partition matroid in which each element is given a color. Given a ground set $E$ and a set of colors $C$, each element $e \in E$ is associated with some color $c \in C$. An independent set of a colored matroid must satisfy the usual independence conditions of a matroid and also obey the limits placed on the colors, for example taking at most a certain number of elements of each color.

-   **Bases**: the bases of a colored matroid are the maximal independent sets that satisfy the color limits and the independence conditions.

-   **Circuits**: circuits are minimal dependent sets, i.e., sets of elements that violate the independence conditions or the color limits.

-   **Rank**: the rank of a colored matroid is the size of the largest independent set satisfying the color limits. It depends both on the structure of the matroid and on the specific color limits.

## Constructions and operations

### Duality

Given a matroid $M = (E, \mathcal{I})$, its **dual matroid** $M^* = (E, \mathcal{I}^*)$ is defined by:

$$
\mathcal{I}^* = \{ I^* \subseteq E \mid \exists B \in \mathcal{I}, |B| = r(E), B \subseteq E \setminus I^* \}.
$$

**Properties**:

-   **Bases**: the bases of the dual matroid $M^*$ are the complements in $E$ of the bases of $M$. In other words, if $B$ is a basis of $M$, then $E \setminus B$ is a basis of $M^*$.

-   **Rank function**: the rank function of the dual matroid is $r^*(S) = |S| - r(E) + r(E \setminus S)$, where $S$ is a subset of $E$. So the rank in the dual can be computed from the size of the set, the rank of the original matroid, and the rank of what remains after removing $S$ from the ground set.

-   **Involution**: the dual of the dual is the original matroid, i.e., $(M^*)^* = M$.

**Example**:

For an undirected graph $G = (V, E)$, the dual $M(G)^*$ of the graphical matroid $M(G)$ is the matroid formed by the cuts of the graph (the bond matroid). The bases of $M(G)$ are the spanning trees of the graph, and the bases of the dual $M(G)^*$ are the complements of these spanning trees. The circuits of the dual $M(G)^*$ are the minimal cuts of the graph, i.e., minimal edge sets whose removal splits the graph into two disconnected parts.

For example, consider a simple triangle graph $G$ with edge set $E = \{e_1, e_2, e_3\}$. The bases of $M(G)$ are the sets of two edges (such as $\{e_1, e_2\}$), and the bases of the dual $M(G)^*$ are single edges (such as $\{e_3\}$). The circuits of $M(G)^*$ are sets of two edges (the minimal cuts, such as $\{e_2,e_3\}$), because removing them splits the graph into two connected components.

### Deletion and contraction

**Deletion**:

For $A \subseteq E$, deleting $A$ from the matroid $M$ gives a new matroid $M \setminus A$, whose family of independent sets $\mathcal{I}'$ is defined as:

$$
\mathcal{I}' = \{ I \subseteq E \setminus A \mid I \in \mathcal{I} \}.
$$

So deletion simply removes some elements from the matroid and keeps the independent sets formed by the remaining elements. The original independent sets are unchanged; only the elements are removed.

**Contraction**:

For $A \subseteq E$, contracting $A$ in the matroid $M$ gives the matroid $M / A$, whose family of independent sets $\mathcal{I}''$ is defined as:

$$
\mathcal{I}'' = \left\{ I \subseteq E \setminus A \,\bigg|\, \exists B \subseteq A,\, B \in \mathcal{I},\, r(B) = r(A),\, I \cup B \in \mathcal{I} \right\}
$$

Contraction can be understood as shrinking the elements of $A$ away, and considering the independent sets that the remaining elements form together with a basis of $A$. The result depends on the bases of $A$; the independent sets after contraction are really obtained by reducing higher-rank subsets of the original matroid.

**Example: graphical matroids**:

-   **Deletion**: in a graphical matroid, deletion means removing some edges from the graph. After removing an edge from a graph $G$, we consider the independent sets formed by the remaining edges, i.e., the edge sets with no cycle. For example, if we remove one edge from a triangle, the remaining two edges are still a forest.

-   **Contraction**: contraction shrinks an edge into a single vertex. In a graphical matroid, contracting an edge means merging its two endpoints into one vertex and deleting the edge; after the merge, the other edges of the graph can still form independent sets. For example, in a triangle, contracting any edge merges two vertices into one, and the remaining two edges form a new matroid.

## Matroids and greedy algorithms

**Problem statement**:

One application of matroids is solving optimization problems with greedy algorithms. Concretely, given a matroid $M = (S, \mathcal{I})$, where $S$ is the ground set and $\mathcal{I}$ is the family of independent sets, assign each element $x \in S$ a positive integer weight $w(x)$. The goal is to find an independent set of maximum weight, formally:

$$
\max_{A \in \mathcal{I}} w(A) = \max_{A \in \mathcal{I}} \sum_{x \in A} w(x)
$$

Clearly, a maximum-weight independent set must be a maximal independent set. If an independent set $A$ is not maximal, there is an element $x$ that can be added to $A$, and since $w(x) > 0$, adding it increases the weight, so $A$ is not a maximum-weight independent set.

### Steps

The greedy algorithm for finding a maximum-weight independent set works as follows:

1.  **Sort the elements**: sort the ground set $S$ by weight in decreasing order, giving the sequence $e_1, e_2, \dots, e_n$.
2.  **Initialize**: let the independent set be $A = \emptyset$.
3.  **Build the independent set**: consider the sorted elements $e_i$ one by one; if $A \cup \{ e_i \} \in \mathcal{I}$, set $A = A \cup \{ e_i \}$.
4.  **Output**: the final set $A$ is a maximum-weight independent set.

**Complexity analysis**:

Let $n = |S|$ be the size of the ground set, and let $f(n)$ be the cost of checking whether a set is independent. The time complexity of the greedy algorithm is:

$$
O(n \log n + n f(n))
$$

Here $O(n \log n)$ is the cost of sorting, and $O(n f(n))$ is the cost of the independence checks.

???+ note "Remarks"
    -   In a graphical matroid, a [disjoint set union (DSU)](../ds/dsu.md) can check efficiently whether a cycle is formed, making $f(n)$ close to constant time.
    -   In a linear matroid, independence checks usually involve matrix operations, and their cost depends on the implementation.

**Proof of correctness**:

Let $M = (S, \mathcal{I})$ be a matroid and $A \in \mathcal{I}$ an independent set that is a subset of some maximum-weight independent set $T$. Define $P = \{ x \in S \setminus A \mid A \cup \{x\} \in \mathcal{I} \}$, the set of all elements that keep $A$ independent when added to it.

Let $y$ be the element of maximum weight in $P$. Then $A' = A \cup \{ y \}$ is also a subset of some maximum-weight independent set. Proof:

Suppose $A' = A \cup \{ y \}$ is not a subset of any maximum-weight independent set. Then there is a maximum-weight independent set $T$ with $|A'| < |T|$.

Since $|A'|< |T|$, by the **exchange property** of matroids there is $x \in T \setminus A'$ such that $A' \cup \{ x \} \in \mathcal{I}$.

Using the **exchange property** repeatedly, keep adding such elements $x$ to $A'$, until we build a new independent set $A''$ with $|A''| = |T|$.

Let $K = A'' \cap T$. Then $x = T \setminus K$ and $y = A'' \setminus K$. Since $y$ is the element of maximum weight in $P$, $w(x) \leq w(y)$.

Therefore $w(A'') = w(K) + w(y) \geq w(K) + w(x) = w(T)$. Now:

-   If $w(A'') > w(T)$, then $T$ is not a maximum-weight independent set, contradicting the assumption.
-   If $w(A'') = w(T)$, then $A''$ is a maximum-weight independent set and $A'$ is a subset of it, contradicting the assumption that $A'$ is not a subset of any maximum-weight independent set.

So the assumption is false: $A' = A \cup \{ y \}$ must be a subset of some maximum-weight independent set. Therefore, by applying the greedy strategy repeatedly, we eventually find a maximum-weight independent set.

### Example

**Minimum spanning tree**:

Given a connected undirected graph $G = (V, E)$ where each edge $e \in E$ has a weight $w(e)$, find a spanning tree that contains all vertices and has minimum total weight.

**Building the matroid**:

To state the minimum spanning tree problem as a matroid problem, build the graphical matroid $M(G)$:

-   **Ground set**: $S = E$, i.e., all edges of the graph.
-   **Family of independent sets**: $\mathcal{I}$ is all edge sets with no cycle (i.e., all forests).

**Greedy algorithm**:

In the framework of graphical matroids, [Kruskal's algorithm](../graph/mst.md#kruskal-算法) is a typical greedy algorithm based on matroid theory and can be used to build a minimum spanning tree. [Prim's algorithm](../graph/mst.md#prim-算法) is also an effective greedy algorithm that finds a minimum spanning tree, but it does not strictly rely on the matroid greedy algorithm. So in discussions of matroid theory, Kruskal's algorithm is the main example of a greedy algorithm.

-   **Kruskal's algorithm**:
    1.  **Sort the edges**: sort all edges by weight in increasing order.
    2.  **Select step by step**: take the edges from smallest weight up; if adding an edge does not create a cycle, add it to the spanning tree.
    3.  **Stop condition**: repeat until the spanning tree has $|V| - 1$ edges.

-   **Prim's algorithm**:
    -   **Idea**: Prim's algorithm starts from one vertex and grows the spanning tree step by step, each time choosing the minimum-weight edge connecting a vertex inside the tree to one outside it.
    -   Although Prim's algorithm is also greedy, its selection strategy is different from greedy algorithms based on the matroid exchange property. So in the strict sense of matroid theory, Prim's algorithm is not considered a typical matroid greedy algorithm.

## Matroid intersection

For two matroids $M_1 = (S, \mathcal{I}_1)$ and $M_2 = (S, \mathcal{I}_2)$ on the same ground set $S$, if $\mathcal{I} = \mathcal{I}_1 \cap \mathcal{I}_2$ satisfies the three properties of a family of independent sets, then $M = (S, \mathcal{I})$ is called the **intersection** of $M_1$ and $M_2$.

**Note**: the intersection of two matroids is not always a matroid. It is a matroid only when the intersection of their families of independent sets satisfies the three properties in the definition.

### Problem statement

1.  **Maximum independent set**: find the largest independent set (the one with maximum cardinality) in $\mathcal{I}_1 \cap \mathcal{I}_2$.
2.  **Weighted maximum independent set**: given a weight function $w: S \to \mathbb{R}$, find the independent set in $\mathcal{I}_1 \cap \mathcal{I}_2$ with maximum total weight.

### Algorithm

**Unweighted version**:

1.  **Initialize**: pick an initial independent set $I \in \mathcal{I}_1 \cap \mathcal{I}_2$, usually $I = \emptyset$.
2.  **Iterate**:
    -   **Build the exchange graph**: build the exchange graph $D_{M_1, M_2}(I)$ from the current independent set $I$.
    -   **Find a path**: in the exchange graph, find an augmenting path $P$ from the source $s$ to the sink $t$.
    -   **Augment**: walk along $P$ from $s$ to $t$, visiting each node:
        -   If the node is a left-side vertex (an element of $I$), remove that element from $I$.
        -   If the node is a right-side vertex (an element of $S \setminus I$), add that element to $I$.
    -   **Repeat**: after updating $I$, repeat the steps above until no new augmenting path can be found.
3.  **Result**: the final independent set $I$ is a maximum independent set of the matroid intersection $M = M_1 \cap M_2$.

**Weighted version**:

To find an independent set with maximum total weight, the algorithm needs to choose augmenting paths more carefully.

1.  **Set weights**: for each element $e \in S$, define its weight $w'(e)$ in the exchange graph:
    -   **Left-side vertices** (elements of $I$): $w'(e) = -w(e)$.
    -   **Right-side vertices** (elements of $S \setminus I$): $w'(e) = w(e)$.
2.  **Find a path**: in the exchange graph $D_{M_1, M_2}(I)$, find an **augmenting path** $P$ from the source $s$ to the sink $t$ such that augmenting along it increases the total weight of $I$ the most.
    -   **Augmenting condition**: the total weight of the elements added along $P$ is greater than the total weight of the elements removed, i.e., $\sum_{y \in \text{added elements}} w(y) > \sum_{x \in \text{removed elements}} w(x)$
3.  **Augment**: walk along $P$ from $s$ to $t$, visiting each node:
    -   If the node is a left-side vertex (an element of $I$), remove that element from $I$.
    -   If the node is a right-side vertex (an element of $S \setminus I$), add that element to $I$.
4.  **Iterate**: repeat steps 1 to 3, building the exchange graph and finding augmenting paths again and again, to improve the total weight of $I$ step by step.
5.  **Stop condition**: the algorithm stops when no path satisfying the augmenting condition can be found in the exchange graph.
6.  **Result**: the final independent set $I$ is a **maximum-weight independent set** of the matroid intersection $M = M_1 \cap M_2$.

**Complexity**:

-   **Number of augmentations**: if the maximum ranks of the two matroids are $r_1$ and $r_2$, there are at most $\min(r_1, r_2)$ augmentations.

-   **Cost of each augmentation**:
    -   Building the exchange graph costs $O(n^2)$, where $n = |S|$.
    -   Finding an augmenting path depends on the search strategy; it is usually $O(n^2)$, for example with breadth-first search.

-   **Total time complexity**: the overall time complexity is $O(r \cdot n^2)$, where $r = \min(r_1, r_2)$.

## Example problems

**Minimum spanning tree**:

Given an undirected graph $G = (V, E)$ where each edge $e \in E$ has a weight $w(e)$, find a spanning tree that contains all vertices and has minimum total weight.

-   Details: [Minimum spanning tree](../graph/mst.md).
-   Template problem: [Luogu P3366 [Template] Minimum Spanning Tree](https://www.luogu.com.cn/problem/P3366).

??? note "Solution idea"
    Use Kruskal's algorithm: sort all edges by weight in increasing order, then pick edges one by one, adding an edge to the spanning tree if it does not create a cycle. The resulting spanning tree is a minimum spanning tree.

**Colorful Graph**:

Given an undirected graph $G = (V, E)$ whose edges have several colors, where each edge has one color, find the largest edge set such that:

1.  The chosen edges form no cycle.
2.  Each color has at most $k$ edges ($k$ is a given positive integer).

??? note "Solution idea"
    1.  **Matroid modeling**:
    
        -   **Graphical matroid ($M_1$)**: the edge sets that form no cycle, i.e., the family of independent sets $\mathcal{I}_1$ contains all acyclic edge sets.
        -   **Color matroid ($M_2$)**: the edge sets with at most $k$ edges of each color, i.e., the family of independent sets $\mathcal{I}_2$ contains all edge sets with $\leq k$ edges of each color.
    2.  **Solve the matroid intersection**: by solving $M = M_1 \cap M_2$, find the largest edge set that forms no cycle and has at most $k$ edges of each color.

**Constrained resource allocation**:

In a resource allocation problem, there is a set of resources $R = \{r_1, r_2, \dots, r_n\}$ and a set of projects $P = \{p_1, p_2, \dots, p_m\}$. Each project $p_i$ needs a certain amount of resources, and the total amount allocated of each resource cannot exceed its supply.

**Goal**: find a resource allocation that meets all project demands without exceeding the resource supplies.

??? note "Solution idea"
    1.  **Matroid modeling**:
    
        -   **Demand matroid ($M_1$)**: allocations that satisfy the projects' resource demands, i.e., the family of independent sets $\mathcal{I}_1$ contains all resource allocations that meet the project demands.
        -   **Supply matroid ($M_2$)**: allocations that do not exceed the supply of each resource, i.e., the family of independent sets $\mathcal{I}_2$ contains all resource allocations that respect the supply limits.
    2.  **Solve the matroid intersection**: by solving $M = M_1 \cap M_2$, find a resource allocation that meets all project demands and does not exceed the resource supplies.

## References and notes

1.  [Wikipedia - Matroid](https://en.wikipedia.org/wiki/Matroid)
2.  [Baidu Baike - Matroid (Chinese)](https://baike.baidu.com/item/%E6%8B%9F%E9%98%B5)
3.  [Luogu - Matroids and optimization problems (Chinese)](https://www.luogu.com.cn/article/87d02q9f)
4.  [Luogu - From matroid basics to the Shannon switching game (Chinese)](https://www.luogu.com.cn/article/fuj3x886)
