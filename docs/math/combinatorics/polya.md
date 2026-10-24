author: Wajov, Early0v0, Enter-tainer, Great-designer, iamtwz, Ir1d, MegaOwIer, mgt, StudyingFather, Tiphereth-A, warzone-oier, Xeonacid, c-forrest

Prerequisites: [Permutations and Arrangements](../permutation.md)

## Introduction

The Pólya enumeration theorem is usually used to solve counting problems that ask for "essentially different" objects.

???+ info "This article may involve group theory"
    This article may involve some group theory. We give short explanations of the group theory concepts used, so that readers unfamiliar with them can still understand and apply the Pólya enumeration theorem. For rigorous statements and discussion of group theory, see sections such as [Basic Concepts of Abstract Algebra](../algebra/basic.md) and [Group Theory](../algebra/group-theory.md).

??? info "\"Symmetry group\", \"symmetric group\" and \"permutation group\""
    This article cannot avoid using the names of all three kinds of groups. Although they are easy to confuse, they really refer to different concepts. Given a geometric structure, a symmetry operation on it is a geometric transformation that maps the structure onto itself, and the symmetry group is the set of these symmetry operations. The symmetric group is the set of all permutations of a given set. A permutation group is a subgroup of a symmetric group, i.e. a group made of some (not necessarily all) permutations. Later we explain how to represent the symmetry group of a given geometric structure as a permutation group and use it for counting.

## Burnside's lemma

Related reading: [Burnside's lemma](../algebra/group-theory.md#burnside-引理)

The Pólya enumeration theorem is an application and generalization of Burnside's lemma. Before introducing the Pólya enumeration theorem, we briefly review Burnside's lemma.

To find the general pattern, we first look at a simple example.

???+ example "Necklace coloring"
    A necklace has four beads, and each bead can be red or blue. How many essentially different necklaces are there? (Two colorings are considered the same if one can be turned into the other by rotating the necklace.)

??? example "Solution and analysis"
    This problem is simple enough to solve by enumeration. There are $4$ beads and each can take $2$ colors, so there are $2^4=16$ possible colorings in total. Grouping together the colorings that can be obtained from each other by rotation gives $6$ groups, as shown below. (Each coloring is encoded by the colors of the beads, starting from the bottom-left bead and going clockwise; $B$ means blue and $R$ means red. Colorings in the same group have the same background color.)
    
    ![Necklace coloring](../images/necklaces.svg)
    
    This example shows that the key to counting essentially different colorings is to know how many colorings correspond to each essentially identical coloring. In other words, we need to know the size of each group in the figure above.
    
    Colorings in the same group are exactly those that can be turned into each other by rotation. There are $4$ rotations in total:
    
    $$
    G=\{r_0,r_1,r_2,r_3\},
    $$
    
    meaning rotating $0,1,2,3$ times. Rotating $0$ times means doing nothing.
    
    First look at the group containing the coloring $RRBB$. Applying the four operations to it gives
    
    $$
    RRBB, RBBR, BBRR, BRRB.
    $$
    
    These four colorings are all different, so this group has $4$ elements.
    
    Next look at the group containing the coloring $BRBR$. Applying the same four operations gives
    
    $$
    BRBR, RBRB, BRBR, RBRB.
    $$
    
    Here, rotating twice gives the same result as not rotating, and rotating three times gives the same result as rotating once. So this group has $2$ elements.
    
    Finally look at the groups containing $BBBB$ and $RRRR$. All four operations leave them unchanged. So each of these groups has only $1$ element.
    
    Let $x$ be a coloring and $Gx$ the set of colorings obtained by applying the operations to $x$. From the example above we can see a pattern: the operations in $G$ act on $x$ with a kind of "periodicity".
    
    Let $|G|$ be the total number of operations. This "periodicity" means that if $m$ different operations in $G$ map the coloring $x$ to itself, then each result for $x$ under these operations appears $m$ times. So $x$ has $|G|/m$ different results under these operations, which is the size of the group containing $x$.
    
    In this example, only rotating zero times ($r_0$) maps $RRBB$ to itself, so its group has size $4/1=4$. Both $r_0$ and rotating twice ($r_2$) map $BRBR$ to itself, so its group has size $4/2=2$. Every rotation maps $BBBB$ to itself, so its group has size $4/4=1$.
    
    Below, let $G_x$ be the set of operations that map $x$ to itself, so $|G_x|$ is the $m$ above. Then the group containing $x$ has size $|G|/|G_x|$. To count the groups, we go over all colorings $x\in X$, and give weight $1/|Gx|$ to a coloring $x$ whose group has size $|Gx|$. Then the number of groups is
    
    $$
    |X/G|=\sum_{x\in X}\frac{1}{|Gx|}=\sum_{x\in X}\frac{|G_x|}{|G|}.
    $$
    
    This form is not convenient to use yet. Let $gx$ be the result of applying operation $g\in G$ to coloring $x\in X$. Then the set $G_x$ described above is $\{g\in G:gx=x\}$, so swapping the order of summation gives
    
    $$
    \begin{aligned}
    \sum_{x\in X}|G_x| 
    &=\sum_{x\in X}|\{g\in G:gx=x\}|\\
    &=\sum_{x\in X}\sum_{g\in G}[gx=x]\\
    &=\sum_{g\in G}\sum_{x\in X}[gx=x]\\
    &=\sum_{g\in G}|\{x\in X:gx=x\}|\\
    &=\sum_{g\in G}|X^g|.
    \end{aligned}
    $$
    
    Here $[\cdot]$ is the Iverson bracket. In the result after swapping the sums, $X^g=\{x\in X:gx=x\}$ is the set of colorings $x$ that stay unchanged under operation $g$. In short, it is the set of fixed points of $g$.
    
    After this discussion, we can now write the number of groups as
    
    $$
    |X/G|=\frac{1}{|G|}\sum_{g\in G}|X^g|.
    $$
    
    That is, the number of groups is the average number of fixed points of the rotations.
    
    As an application of this result, let us count the necklace colorings again. The fixed points of the rotations are listed below.
    
    | Operation |        Fixed points        |
    | :---: | :-----------------------: |
    | $r_0$ |            $X$            |
    | $r_1$ |      $\{BBBB,RRRR\}$      |
    | $r_2$ | $\{BBBB,BRBR,RBRB,RRRR\}$ |
    | $r_3$ |      $\{BBBB,RRRR\}$      |
    
    So the number of groups is
    
    $$
    \frac{16+2+4+2}{4} = 6.
    $$
    
    This matches the earlier result.

From this example we can derive a general result for solving this kind of counting problem. For convenience, this article discusses coloring problems, but the method applies to other settings too; examples are given later.

In a coloring problem, we are given some structure, and we color each colorable object in it (such as elements, vertices or edges), which gives different colorings. The structure has some symmetry, so colorings that look different may turn into each other after a series of symmetry operations. Colorings that can be turned into each other are called essentially the same. The problem is to count the essentially different colorings.

From the analysis in the example, to solve such a problem we first need to find all the symmetry operations of the given structure. The set $G$ of these symmetry operations is called the symmetry group of the structure. In practice, we usually do not need to know the definition of a group; we just need to list all the symmetry operations, without repeats or omissions. Later in this article we analyze several common symmetry groups, and the definition of a group is explained there.

Let $X$ be the set of all colorings, and $x$ a single coloring in it. Applying operation $g\in G$ to coloring $x\in X$ gives $gx$. Then all the results of applying some operation to $x$ form the set $Gx=\{gx:g\in G\}$, which is called the orbit of $x$ under the action of the group $G$. Different colorings in the same orbit are what we call "essentially the same" in this kind of problem. So the number of essentially different colorings equals the number of distinct orbits.

The analysis in the example generalizes to the general case.

???+ note "Burnside's lemma"
    Given an action of a group $G$ on a set $X$, the number of distinct orbits is
    
    $$
    |X/G|=\frac{1}{|G|}\sum_{g\in G}|X^g|.
    $$
    
    Here $X^g=\{x\in X:gx=x\}$ is the set of fixed points under the action of $g\in G$.

Its proof is almost the same as the analysis in the example above. However, the example relied on an observation: the action of $G$ on a single element $x$ has a kind of "periodicity", so the number of repeats equals the number of operations that map $x$ to itself. This observation is true in general, but since the structure of $G$ can be complicated, its "periodicity" is not always as direct as in the example. Stating this observation rigorously requires the [orbit-stabilizer theorem](../algebra/group-theory.md#稳定化子) from group theory.

To apply it, we just need to list all the symmetry operations and give the number of fixed points of each one; this solves the counting problem. Here is a slightly more complex application.

???+ example "Cube coloring"
    Color the faces of a cube with three colors. Find the number of essentially different colorings (two colorings that become the same after a rotation in space count as one).

??? example "Solution"
    A cube has $6$ faces and each face can be colored in $3$ ways, so there are $3^6$ colorings in total, i.e. $|X|=3^6$. Let $G$ be the symmetry group of the cube.
    
    ![](../images/cube.svg)
    
    Next we analyze all operations in $G$. They fall into the following classes (for convenience, call the six faces front, back, top, bottom, left and right):
    
    -   Doing nothing: the identity transformation. Every coloring stays the same under it, so $|X^g|=3^6$;
    -   $90^\circ$ rotation about the axis through the centers of two opposite faces: there are $3$ choices of the pair of opposite faces and $2$ directions of rotation, so this class has $6$ permutations. Suppose the axis goes through the centers of the front and back faces. For the coloring to stay the same after rotation, the top, bottom, left and right faces must have the same color. Then there are $3$ independently colorable regions, so $|X^g|=3^3$;
    -   $180^\circ$ rotation about the axis through the centers of two opposite faces: there are $3$ choices of the pair of opposite faces, and the direction of rotation does not matter, so this class has $3$ permutations. Suppose the axis goes through the centers of the front and back faces. For the coloring to stay the same, the top and bottom faces must have the same color, and the left and right faces must have the same color. Then there are $4$ independently colorable regions, so $|X^g|=3^4$;
    -   $180^\circ$ rotation about the axis through the midpoints of two opposite edges: there are $6$ choices of the pair of opposite edges, and again the direction does not affect the permutation, so this class has $6$ permutations. Suppose the opposite edges are the edge between the front and top faces and the edge between the bottom and back faces. For the coloring to stay the same, the front and top faces must have the same color, the bottom and back faces must have the same color, and the left and right faces must have the same color. Then there are $3$ independently colorable regions, so $|X^g|=3^3$;
    -   $120^\circ$ rotation about the axis through two opposite vertices: there are $4$ choices of the pair of opposite vertices and $2$ directions of rotation, so this class has $8$ permutations. Suppose the opposite vertices are the top-right corner of the front face and the bottom-left corner of the back face. For the coloring to stay the same, the front, top and right faces must have the same color, and the back, bottom and left faces must have the same color. Then there are $2$ independently colorable regions, so $|X^g|=3^2$.
    
    So the number of essentially different colorings is
    
    $$
    \frac{1\times3^6+6\times3^3+3\times3^4+6\times3^3+8\times3^2}{1+6+3+6+8}=57.
    $$

## Pólya enumeration theorem

The statement of Burnside's lemma never used the fact that $X$ is the set of all colorings of some structure. In fact, Burnside's lemma is not limited to counting colorings. For coloring problems, the Pólya enumeration theorem gives a more concrete way to compute. It can be seen as the general Burnside's lemma applied to coloring problems.

Compared with Burnside's lemma, what the Pólya enumeration theorem adds is a concrete way to compute the size $|X^g|$ of the fixed-point set in coloring problems.

This can be seen intuitively from the cube coloring example above. For every symmetry operation of the cube, the size of its fixed-point set has the form $m^{c(g)}$, where $m$ is the number of colors and $c(g)$ is the number of independently colorable regions under operation $g$. This observation also holds in general, but we need to make clear how to compute $c(g)$ for a given $g$.

In mathematical language, choosing a coloring of a structure means choosing a map $f:X\rightarrow C$ from the set $X$ of colorable objects of the structure (such as the beads of a necklace or the faces of a cube) to the set of colors $C$. So the set of colorings is $C^X$. The symmetry group $G$ of the structure acts on the structure, and so it naturally acts on the set $X$ as well. Each such symmetry operation corresponds to a bijection on $X$, i.e. a **permutation**.[^perm-group]

Now let us analyze the structure of the fixed-point set $(C^X)^g$. View a given $g$ as a permutation on $X$. As in the example, if position $x$ in $X$ can be moved to position $y$ by applying $g$ a finite number of times, then a fixed point $f\in (C^X)^g$ must satisfy $f(x)=f(y)$. In the language of orbits from the previous section, positions $x$ and $y$ lie in the same orbit under the action of $g$[^g-act], so they must have the same color. In the language of permutations, in the [cycle decomposition](../permutation.md#轮换表示) of $g$, positions $x$ and $y$ are in the same cycle, so they must have the same color. Different cycles in the decomposition need not share a color and can be colored independently. So the number of independently colorable regions is $c(g)$, the number of cycles in the cycle decomposition of $g$.

Therefore the number of fixed points of operation $g$ is $|C|^{c(g)}$. Substituting this into Burnside's lemma gives the unweighted version of the **Pólya enumeration theorem**.

???+ note "Pólya enumeration theorem (unweighted version)"
    Given an action of a group $G$ on a set $X$ and a set of colors $C$, the number of distinct colorings is
    
    $$
    |C^X/G|=\frac{1}{|G|}\sum_{g\in G}m^{c(g)},
    $$
    
    where $m$ is the number of colors and $c(g)$ is the number of cycles in the cycle decomposition of the permutation representation of $g\in G$.

??? info "About the meaning of the group $G$"
    The notation is slightly abused here. If the group $G$ acts on $X$, then the group action on the set of colorings $C^X$ needs to be defined again; we do not distinguish the two here.

As a simple application of the Pólya enumeration theorem, let us redo the earlier examples with it.

??? example "Another solution to necklace coloring"
    Label the four beads $1\sim 4$. Then the elements of the group $G$ in the example have the following permutation representations (all written as cycle decompositions):
    
    -   Rotating zero times, $r_0=(1)$, has $4$ cycles in total (note the omitted $1$‑cycles);
    -   Rotating once, $r_1=(1234)$, has $1$ cycle;
    -   Rotating twice, $r_2=(13)(24)$, has $2$ cycles;
    -   Rotating three times, $r_3=(1432)$, has $1$ cycle.
    
    So the number of essentially different colorings is
    
    $$
    \frac{2^4+2^1+2^2+2^1}{4}=6.
    $$

??? example "Another solution to cube coloring"
    The earlier analysis already gave the cycle representation of each class of permutations; it just did not write them out with numbers. So we do not repeat that analysis here. We only show one case as an example: the $180^\circ$ rotation about the axis through the midpoints of opposite edges. Number the front, back, top, bottom, left and right faces $1\sim6$. The corresponding permutation is $(13)(24)(56)$, so $c(g)=3$. Other kinds of permutations can be analyzed in the same way, and the final counting expression is exactly the same as above.

## Generalization with weights

The unweighted Pólya enumeration theorem can only count all essentially different colorings; it cannot handle finer questions. For example, if the coloring problem above also specifies how many times each color may be used, we cannot apply the Pólya formula above directly. To solve such problems, we need to go back to Burnside's lemma. Summarizing these results as a generating function gives the weighted version of the Pólya enumeration theorem.

???+ example "Necklace coloring (with constraints)"
    A necklace has four beads, and each bead can be red or blue. Exactly two red beads and two blue beads are available. How many essentially different necklaces are there? (Two colorings are considered the same if one can be turned into the other by rotating the necklace.)

??? example "Solution and analysis"
    We use Burnside's lemma. With two red and two blue beads, there are $\dbinom{4}{2}=6$ colorings in total. The symmetry group $G=\{r_0,r_1,r_2,r_3\}$ corresponds to rotating $0\sim3$ times. Their fixed-point sets are:
    
    -   Rotating zero times, $r_0=(1)$: all $6$ colorings are fixed points;
    -   Rotating once, $r_1=(1234)$: a fixed point requires all beads to have the same color, so there are no fixed points;
    -   Rotating twice, $r_2=(13)(24)$: there are two independently colorable regions, each of size $2$, and they must be colored red and blue respectively, so the fixed-point set has size $2$;
    -   Rotating three times, $r_3=(1432)$: same as rotating once, no fixed points.
    
    So by Burnside's lemma, the number of essentially different colorings is
    
    $$
    \frac{6+0+2+0}{4}=2.
    $$

From this example we get the following method. When the number of each color is restricted, we still color each cycle of each permutation in the symmetry group, but each color must be used exactly the given number of times. Such combinatorial problems usually have no explicit solution. Apart from special cases that can be computed with [combinatorics](../combinatorics/combination.md), they usually need to be solved as a [knapsack problem](../../dp/knapsack/basic.md).

Generating functions give the answer to this kind of counting problem. Given a permutation $g$ whose [type](../permutation.md#置换的型) is $1^{\alpha_1}2^{\alpha_2}\cdots n^{\alpha_n}$, i.e. it has $\alpha_k$ cycles of length $k$, and each cycle can be colored with one of $m$ colors, then in the generating function

$$
\prod_{k=1}^n\left(\sum_{i=1}^mx_i^k\right)^{\alpha_k}
$$

the coefficient of the monomial $x_1^{\beta_1}x_2^{\beta_2}\cdots x_m^{\beta_m}$ is the number of colorings in which color $i$ is used $\beta_i$ times ($1\le i\le m$). The combinatorial meaning of the expression $\sum_{i=1}^mx_i^k$ in parentheses is: for a cycle of length $k$, the number of colorings that use color $i$ exactly $k$ times is $1$, and the count for anything else is $0$. This describes exactly the requirement that all positions in the same cycle have the same color.

Given the generating function for counting colorings fixed by $g$, applying Burnside's lemma to each monomial gives the number of essentially different colorings for each combination of colors. For each monomial, the set of colorings counted by its coefficient is closed under the action of $G$, and taking the average is linear in the coefficients. So the generating function for the number of essentially different colorings is

$$
\frac1{|G|}\sum_{g\in G}\prod_{k=1}^n\left(\sum_{i=1}^mx_i^k\right)^{\alpha_k}.
$$

Expanding this expression, the coefficient of each monomial gives the number of essentially different colorings for that combination of colors.

In this process, there is nothing special about the generating function $\sum_{i=1}^mx_i^k$ for coloring each cycle; it can be replaced by other generating functions. So we have the following general version of the Pólya enumeration theorem.

???+ note "Cycle index of a permutation group"
    Given a permutation group $G$, the **cycle index** of $G$, often written $Z_G$ or $Z(G)$, is defined as
    
    $$
    Z_G(t_1,t_2,\cdots,t_n)=\frac{1}{|G|}\sum_{g\in G}t_1^{c_1(g)}t_2^{c_2(g)}\cdots t_n^{c_n(g)},
    $$
    
    where $c_k(g)$ is the number of cycles of length $k$ in the cycle decomposition of the permutation $g$, i.e. $1^{c_1(g)}2^{c_2(g)}\cdots n^{c_n(g)}$ is the type of $g$.

???+ note "Pólya enumeration theorem (weighted version)"
    Given an action of a group $G$ on a set $X$, where the colorings of each point are counted by the generating function $f(x_1,x_2,\cdots,x_m)$, the generating function for the number of essentially different colorings of $X$ is
    
    $$
    Z_G(f(x_1^1,x_2^1,\cdots,x_m^1),f(x_1^2,x_2^2,\cdots,x_m^2),\cdots,f(x_1^n,x_2^n,\cdots,x_m^n)),
    $$
    
    where $Z_G(t_1,t_2,\cdots,t_n)$ is the cycle index of the group $G$.

Here, if the generating function for coloring a single position is $f(x_1,x_2,\cdots,x_m)$, then the generating function for coloring a cycle of length $k$ is $f(x_1^k,x_2^k,\cdots,x_m^k)$. This reflects that if a coloring is a fixed point of a given permutation, all positions in the same cycle must have the same color. Evaluating the generating function at $x_i=1$ gives the unweighted Pólya enumeration theorem above.

The statement of the theorem uses the cycle index of a permutation group. It has nothing to do with the specific coloring problem; it describes the structure of the permutation group.

??? example "Another solution to the constrained necklace coloring problem"
    The cycle index of the rotation group is $\dfrac14\left(t_1^4+t_2^2+2t_4\right)$, and the generating function for coloring a single point is $r+b$. So the generating function for all colorings is
    
    $$
    \begin{aligned}
    F(r,b)&=\frac14\left((r+b)^4+(r^2+b^2)^2+2(r^4+b^4)\right)\\
    &=r^4+r^3b+2r^2b^2+rb^3+b^4.
    \end{aligned}
    $$
    
    The count we want is the coefficient of $r^2b^2$, i.e. $2$ essentially different colorings. As a bonus, this expression also gives the counts under other constraints.

### Applications

The weighted Pólya enumeration theorem plays an important role in combinatorial counting. Here we briefly discuss its applications; for a more general discussion see [Formal Methods for Combinatorial Problems](../poly/symbolic-method.md#有限制的构造).

???+ example "Diamond necklace"
    A necklace has four identical beads, and each bead can hold any number of diamonds. If there are four diamonds, how many essentially different ways are there to set them? (Two settings are considered the same if one can be turned into the other by rotating the necklace.)

??? example "Solution and analysis"
    The symmetry group of the necklace is the same as before. Ignoring the limit on the total number of diamonds, the generating function for the diamond settings of a single position is
    
    $$
    f(x)=1+x+x^2+\cdots=\sum_{i=0}^\infty x^i=\frac{1}{1-x}.
    $$
    
    By the weighted Pólya enumeration theorem, the generating function for all settings is
    
    $$
    \begin{aligned}
    F(x)&=\frac14\left(f(x)^4+f(x^2)^2+2f(x^4)\right)\\
    &=1+x+3x^2+5x^3+10x^4+\cdots.
    \end{aligned}
    $$
    
    So the number of settings we want is the coefficient of $x^4$, i.e. $10$ settings in total. As a check, enumeration shows that they are
    
    $$
    4000,3100,3010,3001,2200,2020,2110,2101,2011,1111.
    $$
    
    Here each group of four digits gives the number of diamonds on each bead.

This example shows that the weighted Pólya enumeration theorem can solve far more problems than just counting colorings. It gives a way to extend counts for single points to counts of essentially different configurations on the whole structure. Coloring problems are just a special case.

## Common symmetry groups

One of the difficulties in Pólya counting problems is analyzing the structure of the permutation group. Here we briefly discuss the structure of common symmetry groups and describe them by their cycle indices. Note that for the symmetry group of the same structure, if it acts on different sets of objects, the corresponding [group actions](../algebra/group-theory.md#群作用) are different, and so are their permutation representations. For example, the actions of the cube's symmetry group on its vertices, edges and faces correspond to the vertex, edge and face permutation groups of the cube. The numbers of vertices, edges and faces are all different, so these permutation groups and their cycle indices are of course also different. So when solving a concrete problem, do not forget to specify what the group acts on.

??? info "Relation between symmetry groups and permutation groups"
    Although the two concepts are very similar, they are definitely not the same object. In group theory terms, given a symmetry group $G$ and its action on a set $X$, the permutation representation of the action gives a homomorphism $\varphi$ from $G$ to the symmetric group $S_X$. In combinatorial counting, this permutation representation is usually faithful, i.e. $\ker\varphi=\{e\}$, so $\varphi$ is really an embedding of $G$ into $S_X$. The permutation group in this article is the image of this embedding, $\varphi(G)$, which is isomorphic to the symmetry group $G$ itself. So for the same symmetry group $G$ of a structure, different choices of group action give different permutation groups $\varphi(G)$, and thus different cycle indices (isomorphic permutation groups do not necessarily have the same cycle index).

Given a structure, its symmetry group is the set of all operations that map it onto itself. It must satisfy the following conditions:

-   Applying two symmetry operations in a row to the structure can be seen as applying another symmetry operation, i.e. the set of symmetry operations is closed under composition;
-   Composition of symmetry operations is associative;
-   There is an identity symmetry operation, i.e. leaving the structure unchanged also counts as an operation;
-   Every operation has an inverse operation that undoes its effect.

A [group](../algebra/basic.md#群) is the abstraction of everything that satisfies these conditions. Studying the structure of groups is the main subject of [group theory](../algebra/group-theory.md). Here we focus on symmetry groups, and our discussion of their structure mainly takes a geometric view. We give common examples, from which readers should learn the usual way of thinking about such problems.

### Cyclic group

Given a regular $n$-gon, the symmetry group formed by all its rotations is called the cyclic group, written $C_n$. Let $r$ be the counterclockwise rotation by $(360/n)^\circ$. Then the elements of $C_n$ can be written as

$$
C_n=\{e,r,r^2,\cdots,r^{n-1}\}.
$$

Here $r^k$ means applying $r$ $k$ times, i.e. rotating counterclockwise by $(360k/n)^\circ$, and $e=r^0$ is the identity transformation.

Whether the cyclic group acts on the set of all vertices or all edges of the regular $n$-gon, the permutation representation is the same. We analyze the permutation representation using the action on the set of vertices. Its cycle index is

$$
Z(C_n)=\frac1n\sum_{d\mid n}\varphi(d)t_{d}^{n/d}.
$$

Here $\varphi(\cdot)$ is [Euler's totient function](../number-theory/euler-totient.md) from number theory.

If only rotations count, the symmetry group of a necklace of length $n$ is $C_n$.

??? note "Analysis"
    Label the vertices $\{0,1,\cdots,n-1\}$ in counterclockwise order. Then $r^k(i)=(i+k)\bmod n$. The set of vertices in the cycle containing vertex $i$ is
    
    $$
    \{(i+\ell k)\bmod n:\ell\in\mathbf Z\}.
    $$
    
    Clearly $i\equiv i+\ell k\pmod n$ if and only if
    
    $$
    \frac{n}{\gcd(k,n)}\mid\ell.
    $$
    
    This means the cycle containing any vertex $i$ has length $\dfrac{n}{\gcd(k,n)}$. So the permutation $r^k$ has $\gcd(k,n)$ cycles of equal length. Now combine like terms in the cycle index. For a given $d\mid n$, there are $\varphi(d)$ values of $k$ with $\gcd(k,n)=n/d$, and each of them gives the monomial $t_d^{n/d}$. This gives the cycle index above.

### Dihedral group

Given a regular $n$-gon, all its rotations together with its reflections across symmetry axes also form a symmetry group, called the dihedral group, written $D_{2n}$. Let $r$ be the counterclockwise rotation by $(360/n)^\circ$, and let $s$ be the reflection across a fixed symmetry axis (for example the line through the center and a vertex). Then the operations of $D_{2n}$ can be written as

$$
D_{2n}=\{e,r,\cdots,r^{n-1},s,sr,\cdots,sr^{n-1}\}.
$$

Here $r^k$ is still a rotation. $sr^k$ means rotating $k$ times and then reflecting across the fixed axis, but it is equivalent to reflecting across another symmetry axis. So $D_{2n}$ has $1$ identity, $(n-1)$ rotations and $n$ reflections. Its actions on the set of vertices and on the set of edges also have the same cycle index[^dihedral-edge], namely

$$
Z(D_{2n})=\frac12Z(C_n)+
\begin{cases}
\dfrac12t_1t_2^k,&n=2k+1,\\
\dfrac14\left(t_1^2t_2^{k-1}+t_2^k\right),&n=2k.
\end{cases}
$$

??? note "Analysis"
    The analysis of the rotations $r^k$ in $D_{2n}$ (including the identity) is exactly the same as for the cyclic group $C_n$. The key is to analyze the remaining reflections. Here we need to split into cases by the parity of the number of vertices $n$.
    
    When $n=2k+1$, every reflection axis connects a vertex to the midpoint of the opposite edge, and there are $n$ such axes. After each reflection, the vertex on the axis stays fixed and the other vertices are swapped in pairs. So there is $1$ fixed point ($1$‑cycle) and $k$ $2$‑cycles.
    
    When $n=2k$, there are two kinds of axes. Half of the axes connect opposite vertices. A reflection across such an axis keeps the two vertices on the axis fixed and swaps the other vertices in pairs, giving $2$ fixed points ($1$‑cycles) and $(k-1)$ $2$‑cycles. The other half connect the midpoints of opposite edges. A reflection across such an axis swaps all vertices in pairs, giving $k$ $2$‑cycles.
    
    From this analysis, we can write the cycle index above.

### Symmetric group

Given $n$ elements, all permutations of them form a group, called the symmetric group of degree $n$, written $S_n$. It describes all the symmetries these $n$ elements can have. It is also the permutation representation of the action of these symmetry operations on the set of elements.

From the analysis in [Permutations and Arrangements](../permutation.md#置换的型), its cycle index is

$$
Z(S_n)=\sum_{\alpha_1+2\alpha_2+\cdots+n\alpha_n=n}\frac{t_1^{\alpha_1}t_2^{\alpha_2}\cdots t_n^{\alpha_n}}{1^{\alpha_1}2^{\alpha_2}\cdots n^{\alpha_n}\alpha_1!\alpha_2!\cdots\alpha_n!}.
$$

This uses the fact that the number of permutations of type $1^{\alpha_1}2^{\alpha_2}\cdots n^{\alpha_n}$ is

$$
\frac{n!}{1^{\alpha_1}2^{\alpha_2}\cdots n^{\alpha_n}\alpha_1!\alpha_2!\cdots\alpha_n!}.
$$

It satisfies the recurrence

$$
Z(S_n)=\frac1n\sum_{k=1}^nt_kZ(S_{n-k}),
$$

with starting value $Z(S_0)=1$. The combinatorial meaning of this recurrence is: to build a permutation of $n$ elements, first choose the length $k$ of the cycle containing element $n$, then build a permutation of the remaining $(n-k)$ elements.

Given the complete graph on $n$ vertices, its symmetry group is exactly $S_n$. The cycle index of its action on the set of all vertices is the $Z(S_n)$ above. But its action on the set of all edges has a different permutation representation. For example, the sets have different sizes: there are $n(n-1)/2$ edges. The edge case needs extra analysis. Here we give a simple example; for the general case see the exercises.

???+ example "Counting undirected simple graphs"
    Count the undirected simple graphs on $4$ vertices, up to isomorphism.

??? example "Solution"
    This is the same as coloring the edges of the complete graph on $4$ vertices with two colors and counting the essentially different colorings. The symmetry group is $S_4$, and we now find the cycle index of its edge permutation group $S_4^{(2)}$. Call the four vertices $a,b,c,d$, and number the six edges $1=ab$, $2=bc$, $3=cd$, $4=da$, $5=ac$, $6=bd$.
    
    -   Identity ($1$ of them): the edges also stay fixed, so the monomial is $1\cdot t_1^6$;
    -   Swapping two vertices ($6$ of them): suppose $a$ and $b$ are swapped. Then edges $1$ and $3$ stay fixed, edges $2$ and $5$ are swapped, and edges $4$ and $6$ are swapped, so the monomial is $6t_1^2t_2^2$;
    -   Cycling three vertices ($8$ of them): suppose the cycle is $(abc)$. Then the edges $1,2,5$ among them are cycled accordingly, and so are the edges $4,6,3$ connecting them to the fourth vertex $d$, so the monomial is $8t_3^2$;
    -   Swapping two pairs of vertices ($3$ of them): suppose $a$ and $b$ are swapped and $c$ and $d$ are swapped. Then edges $1$ and $3$ stay fixed, edges $2$ and $4$ are swapped, and edges $5$ and $6$ are swapped, so the monomial is $3t_1^2t_2^2$;
    -   Cycling four vertices ($6$ of them): suppose the cycle is $(abcd)$. Then the edges $1,2,3,4$ between adjacent vertices are cycled accordingly, and the edges $5,6$ between opposite vertices are swapped, so the monomial is $6t_2t_4$.
    
    So the cycle index of the edge permutation group is
    
    $$
    Z(S_4^{(2)})=\frac{1}{24}(t_1^6+9t_1^2t_2^2+8t_3^2+6t_2t_4).
    $$
    
    By the Pólya enumeration theorem, the number of undirected simple graphs on $4$ vertices up to isomorphism is
    
    $$
    \frac{2^6+9\times 2^4+8\times 2^2+6\times 2^2}{24} = 11.
    $$

### Polyhedral groups

The polyhedral groups are the symmetry groups of the regular polyhedra. There are only five regular polyhedra: the regular tetrahedron, cube, regular octahedron, regular dodecahedron and regular icosahedron. If we swap vertices and faces while keeping the adjacency relations among vertices, edges and faces, we get the dual regular polyhedron. The tetrahedron is dual to itself, the cube is dual to the octahedron, and the dodecahedron is dual to the icosahedron. Using duality simplifies the discussion of their symmetry groups.

Counting only the rotations that can be done in three-dimensional space, there are only three such symmetry groups.

-   The tetrahedral group, i.e. the symmetry group of the regular tetrahedron:

    -   The identity;
    -   Rotations by $120^\circ$ and $240^\circ$ about the line through a vertex and the center of the opposite face;
    -   Rotation by $180^\circ$ about the line through the midpoints of opposite edges.

    That is $1+2\times4+1\times3=12$ symmetry operations in total.

    The cycle indices of the corresponding permutation groups are as follows.

    -   Vertex and face permutation groups: $\dfrac1{12}\left(t_1^4+8t_1t_3+3t_2^2\right)$;
    -   Edge permutation group: $\dfrac1{12}\left(t_1^6+8t_3^2+3t_1^2t_2^2\right)$.

-   The octahedral group, i.e. the symmetry group of the cube (and the regular octahedron):

    -   The identity;
    -   Rotations by $120^\circ$ and $240^\circ$ about the line through opposite vertices;
    -   Rotation by $180^\circ$ about the line through the midpoints of opposite edges;
    -   Rotations by $90^\circ$, $180^\circ$ and $270^\circ$ about the line through the centers of opposite faces.

    That is $1+2\times 4+1\times 6+3\times 3=24$ symmetry operations in total.

    The cycle indices of the corresponding permutation groups of the cube are as follows.

    -   Vertex permutation group: $\dfrac{1}{24}\left(t_1^8+8t_1^2t_3^2+9t_2^4+6t_4^2\right)$;
    -   Edge permutation group: $\dfrac{1}{24}\left(t_1^{12}+8t_3^4+6t_1^2t_2^5+6t_4^3+3t_2^6\right)$;
    -   Face permutation group: $\dfrac{1}{24}\left(t_1^6+8t_3^2+6t_2^3+6t_1^2t_4+3t_1^2t_2^2\right)$.

    The permutation groups of the octahedron are similar, with the roles of vertices and faces swapped.

-   The icosahedral group, i.e. the symmetry group of the regular dodecahedron (and the regular icosahedron):

    -   The identity;
    -   Rotations by $120^\circ$ and $240^\circ$ about the line through opposite vertices;
    -   Rotation by $180^\circ$ about the line through the midpoints of opposite edges;
    -   Rotations by $72^\circ$, $144^\circ$, $216^\circ$ and $288^\circ$ about the line through the centers of opposite faces.

    That is $1+2\times 10+1\times 15+4\times 6=60$ symmetry operations in total.

    The cycle indices of the corresponding permutation groups of the dodecahedron are as follows.

    -   Vertex permutation group: $\dfrac{1}{60}\left(t_1^{20}+20t_1^2t_3^6+15t_2^{10}+24t_5^4\right)$;
    -   Edge permutation group: $\dfrac{1}{60}\left(t_1^{30}+20t_3^{10}+15t_1^2t_2^{14}+24t_5^6\right)$;
    -   Face permutation group: $\dfrac{1}{60}\left(t_1^{12}+20t_3^4+15t_2^6+24t_1^2t_5^2\right)$.

    The permutation groups of the icosahedron are similar, with the roles of vertices and faces swapped.

All the cycle indices given here are for permutation groups acting on a single kind of object (vertices, edges or faces). If different objects are colored at the same time, you need to write a joint cycle index.

## Exercises

### Coloring problems

These problems only require analyzing the structure of the permutation group and applying the Pólya enumeration theorem.

-   [Luogu P4980 [Template] Pólya Theorem](https://www.luogu.com.cn/problem/P4980)
-   [Luogu P2561 \[AHOI2002\] Black and White Tiles](https://www.luogu.com.cn/problem/P2561)
-   [TRANSP - Transposing is Fun](https://www.spoj.com/problems/TRANSP/)
-   [TRANSP2 - Transposing is Even More Fun](https://www.spoj.com/problems/TRANSP2/)
-   [Luogu P3307 \[SDOI2013\] Necklace](https://www.luogu.com.cn/problem/P3307)

When the allowed combinations of colors are restricted, you need knapsack DP or combinatorial methods to count the ways to color the cycles.

-   [Luogu P1446 \[HNOI2008\] Cards](https://www.luogu.com.cn/problem/P1446)
-   [UVA10601 Cubes](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1542)
-   [Luogu P4916 \[MtOI2018\] Magic Ring](https://www.luogu.com.cn/problem/P4916)

### Graph enumeration

The Pólya enumeration theorem can be used for [graph enumeration](../combinatorics/graph-enumeration.md) problems. The hard part of these problems is enumerating the edge permutation group of the graph.

-   [SGU 282. Isomorphism](https://codeforces.com/problemsets/acmsguru/problem/99999/282)
-   [Luogu P4727 \[HNOI2009\] Counting Graph Isomorphism Classes](https://www.luogu.com.cn/problem/P4727)
-   [Luogu P4128 \[SHOI2006\] Colored Graphs](https://www.luogu.com.cn/problem/P4128)

Another kind of graph enumeration problem that uses the Pólya enumeration theorem requires working directly with generating functions.

-   [LOJ 6538 Counting Alkyls, Enhanced Enhanced Version](https://loj.ac/p/6538)
-   [LOJ 6512 "Yali Training Camp 2018" Counting Alkanes](https://loj.ac/p/6512)
-   [Luogu P6597 Counting Alkenes](https://www.luogu.com.cn/problem/P6597)
-   [Luogu P5818 \[JSOI2011\] Counting Isomers](https://www.luogu.com.cn/problem/P5818)

## References and notes

-   [Pólya enumeration theorem - Wikipedia](https://en.wikipedia.org/wiki/P%C3%B3lya_enumeration_theorem)
-   [Notes on Pólya's Enumeration Theorem](https://www.diva-portal.org/smash/get/diva2:324594/FULLTEXT01.pdf)
-   [Cycle index - Wikipedia](https://en.wikipedia.org/wiki/Cycle_index)

[^perm-group]: So the symmetry group $G$ can be represented as a permutation group on the set $X$, i.e. a subgroup of the symmetric group $S_X$.

[^g-act]: Strictly speaking, under the action of the subgroup $\langle g\rangle\le G$.

[^dihedral-edge]: Unlike the cyclic group case, when $n$ is even, the permutation representations of these two group actions are not the same: a reflection across an axis through opposite vertices has type $1^22^{k-1}$ on the vertex set but $2^k$ on the edge set, and a reflection across an axis through midpoints of opposite edges is the other way around. However, there are equally many axes of each kind, so after summing, the cycle index is the same.
