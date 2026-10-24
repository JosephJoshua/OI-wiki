In combinatorics, graph enumeration is the branch that studies counting graphs with given properties. [Generating functions](../poly/intro.md), [Pólya's enumeration theorem](./polya.md), the [symbolic method](../poly/symbolic-method.md#%E9%9B%86%E5%90%88%E7%9A%84-cycle-%E6%9E%84%E9%80%A0) and the [OEIS](https://oeis.org/) are the most important mathematical tools for these problems. Graph enumeration problems fall into two big classes, labeled and unlabeled. In most cases[^1], the labeled version of a problem is simpler than the matching unlabeled one, so we look at labeled counting first.

[^1]: Unlabeled binary trees may be a counterexample. When the structure is simple, the corresponding permutation group is the identity group, and the labeled version can be obtained directly by multiplying by $n!$.

## Labeled trees

This is Cayley's formula; see the article on [Prüfer sequences](../../graph/prufer.md). We can also get this result with [Kirchhoff's matrix tree theorem](../../graph/matrix-tree.md), or with [generating functions](../poly/intro.md#生成函数) and the [Lagrange inversion theorem](https://codeforces.com/blog/entry/104184).

### Exercises

-   [Hihocoder 1047. Random Tree](https://vjudge.net/problem/HihoCoder-1047)

## Labeled connected graphs

### Example problem: POJ 1737 Connected Graph

???+ note "Example problem [POJ 1737 Connected Graph](http://poj.org/problem?id=1737)"
    Summary: count the labeled connected graphs with $n$ nodes ($n \leq 50$).

This kind of problem first appeared in Lou Tiancheng's "Eight Problems for Men" series. Let $g_n$ be the number of labeled graphs on $n$ vertices, and $c_n$ the sequence we want. A graph on $n$ vertices has at most $\binom{n}{2}$ edges, and each edge is either present or absent, independently of the others, so $g_n = 2^{\binom{n}{2}}$. Fix one vertex and enumerate the size $i$ of its connected component; then we need to choose $i-1$ of the remaining $n-1$ vertices to form a connected component with it. Vertices outside this component can be joined by edges arbitrarily, so we get the following recurrence:

$$
\begin{align}
\sum_{i=1}^{n} \binom{n-1}{i-1} c_i g_{n-i} &= g_n \\
c_n &= g_n - \sum_{i=1}^{n-1} \binom{n-1}{i-1} c_i g_{n-i} 
\end{align}
$$

Rearranging gives an $O(n^2)$ recurrence for $c_n$, which is enough to solve this problem.

### Example problem: National Training Team Homework 2013, City Planning

???+ note "Example problem [National Training Team Homework 2013 - City Planning](https://www.luogu.com.cn/problem/P4841)"
    Summary: count the labeled connected graphs with $n$ nodes ($n \leq 130000$).

For sequence problems with larger constraints, we usually need to build the generating functions of these sequences so we can use fast polynomial algorithms.

#### Method 1: divide-and-conquer FFT

The recurrence above can be seen as a self-convolution, so it can be computed with divide-and-conquer FFT in $O(n\log^2n)$ time.

#### Method 2: polynomial inverse

Expand the binomial coefficients in the recurrence above and rearrange:

$$
\begin{align}
\sum_{i=1}^{n} \binom{n-1}{i-1} c_i g_{n-i} &= g_n \\
\sum_{i=1}^{n} \frac{c_i}{(i-1)!} \frac{g_{n-i}}{(n-i)!} &= \frac{g_n}{(n-1)!}
\end{align}
$$

Define the polynomials:

$$
\begin{align}
C(x) &= \sum_{n=1} \frac{c_n}{(n-1)!} x^n \\
G(x) &= \sum_{n=0} \frac{g_n}{n!} x^n \\
H(x) &= \sum_{n=1} \frac{g_n}{(n-1)!} x^n
\end{align}
$$

Substituting into the equation above gives $CG = H$. Use the [polynomial inverse](../poly/elementary-func.md#%E5%A4%9A%E9%A1%B9%E5%BC%8F%E6%B1%82%E9%80%86) and then a convolution to solve for $C(x)$.

#### Method 3: polynomial exp

Another approach uses the [combinatorial meaning of the polynomial exp of an EGF](../poly/egf.md#egf-%E4%B8%AD%E5%A4%9A%E9%A1%B9%E5%BC%8F-exp-%E7%9A%84%E7%BB%84%E5%90%88%E6%84%8F%E4%B9%89). Let the EGFs of the sequences of labeled connected graphs and labeled simple graphs be $C(x)$ and $G(x)$. Then they satisfy:

$$
\begin{align}
\exp(C(x)) &= G(x) \\
C(x) &= \ln(G(x))
\end{align}
$$

Use the [polynomial ln](../poly/elementary-func.md#多项式对数函数--指数函数) to solve for $C(x)$.

## Labeled Eulerian graphs and bipartite graphs

### Example problem: SPOJ KPGRAPHS Counting Graphs

???+ note "Example problem [SPOJ KPGRAPHS Counting Graphs](http://www.spoj.com/problems/KPGRAPHS/)"
    Summary: for $n$ nodes, count the labeled graphs with each of the following properties ($n \leq 1000$).
    
    -   Connected graphs [A001187](https://oeis.org/A001187).
    -   Eulerian graphs [A033678](https://oeis.org/A033678).
    -   Bipartite graphs [A047864](https://oeis.org/A047864).

This problem limits code length, so we cannot paste in polynomial templates directly, but generating functions still help with the analysis.

Connected graphs were handled in the previous example, so consider Eulerian graphs. Note that all the methods above for counting connected graphs generalize to labeled connected graphs with any property. For example, in the recurrence for connected graphs, we can replace $g_n$ (all graphs) with the number of graphs whose vertices all have even degree; the resulting $c_n$ then counts Eulerian graphs.

We wrap the recurrence from POJ 1737 into a "connectify" function,

```cpp
void ln(Int C[], Int G[]) {
  for (int i = 1; i <= n; ++i) {
    C[i] = G[i];
    for (int j = 1; j <= i - 1; ++j)
      C[i] -= binom[i - 1][j - 1] * C[j] * G[i - j];
  }
}
```

and the first two parts are easy:

```cpp
for (int i = 1; i <= n; ++i) G[i] = pow(2, binom[i][2]);
ln(C, G);
for (int i = 1; i <= n; ++i) G[i] = pow(2, binom[i - 1][2]);
ln(E, G);
```

Note that this connectify recurrence is really equivalent to taking the polynomial ln of the EGF. In the same way we can write the inverse connectify function, which is equivalent to taking the polynomial exp of the EGF.

```cpp
void exp(Int G[], Int C[]) {
  for (int i = 1; i <= n; ++i) {
    G[i] = C[i];
    for (int j = 1; j <= i - 1; ++j)
      G[i] += binom[i - 1][j - 1] * C[j] * G[i - j];
  }
}
```

Next we discuss counting labeled bipartite graphs.

Let $b_n$ be the number of bipartite graphs on n vertices, and $g_n$ the number of graphs on $n$ vertices together with a 2-coloring of the vertices such that no edge joins two vertices of the same color. Enumerating the number of vertices of one color gives[^2]:

$$
g_n = \sum_{i=0}^{n} \binom{n}{i}2^{i(n-i)}
$$

[^2]: [PinkRabbit's blog](https://www.luogu.com.cn/blog/PinkRabbit/solution-sp4420) tells us that this sequence can also be sped up with the [Chirp Z-Transform](../poly/czt.md).

Next we use two different methods to relate $g_n$ and $b_n$.

#### Method 1: double counting

Let $c_{n, k}$ be the number of bipartite graphs with k connected components. Then it is easy to get:

$$
\begin{align}
b_n &= \sum_{i=1}^{n} c_{n, i} \\
g_n &= \sum_{i=1}^{n} c_{n, i} 2^i 
\end{align}
$$

Comparing the two expressions for $g_n$ and expanding gives:

$$
\begin{align}
\sum_{i=0}^{n} \binom{n}{i}2^{i(n-i)} &= \sum_{i=1}^{n} c_{n, i} 2^i \\
c_{n, i} &= \sum_{i=0}{n-1} \binom{n-1}{i-1} c_{n, 1}c_{n-i,k-1}
\end{align}
$$

From this it is easy to get a recurrence for $b_n$ in $O(n^3)$ time. Using inclusion–exclusion further brings it down to $O(n^2)$, which solves this problem.

#### Method 2: connectify recurrence

Methods 2 and 3 both use connected bipartite graphs $b1_n$ [A001832](https://oeis.org/A001832) as the bridge between $g_n$ and $b_n$.

Note that each connected bipartite graph has exactly two different colorings, which correspond to two different connected 2-colored graphs.
So applying connectify to $g_n$ gives a sequence that is exactly twice $b1_n$, and $b_n$ is obtained by applying inverse connectify to $b1_n$.

So:

```cpp
for (int i = 1; i <= n; ++i) {
  G[i] = 0;
  for (int j = 0; j < i + 1; ++j) G[i] += binom[i][j] * pow(2, j * (i - j));
}
ln(B1, G);
for (int i = 1; i <= n; ++i) B1[i] /= 2;
exp(B, B1);
```

Both recurrences run in $O(n^2)$ time, which solves this problem.

#### Method 3: polynomial exp

Note that we can also understand the recurrence above through EGFs.

Let $G(x)$ be the EGF of $g_n$, $B1(x)$ the EGF of $b1_n$, and $B(x)$ the EGF of $b_n$. Applying the idea of Method 2, we have:

$$
\begin{align}
G(x) &= \exp(2B1(x)) \\
B(x) &= \exp(B1(x))  \\
     &= \exp(\frac{\ln{G(x)}}{2}) \\
     &= \sqrt{G}
\end{align}
$$

We can differentiate both sides and compare coefficients to get a recurrence that is easy to code, which solves this problem.
Note that Methods 2 and 3 are essentially the same, and in general Method 3 gives a better time complexity.

$$
\begin{align}
B_n^2 &= G  \\
2B_nB_n' &= G' 
\end{align}
$$

??? note "Reference code"
    ```cpp
    --8<-- "docs/math/code/combinatorics/graph-enumeration/graph-enumeration_1.cpp"
    ```

### Exercises

-   [UOJ Goodbye Jihai D. New Year's Chase](https://uoj.ac/contest/50/problem/498)
-   [BZOJ 3864. Big Friend and Multiway Trees](https://hydro.ac/p/bzoj-P3864)
-   [BZOJ 2863. The Angry Leader](https://hydro.ac/p/bzoj-P2863)
-   [Luogu P6295. Counting Labeled DAGs](https://www.luogu.com.cn/problem/P6295)
-   [LOJ 6569. Counting Cacti](https://loj.ac/p/6569)
-   [LOJ 6570. Counting Caterpillars](https://loj.ac/p/6570)
-   [Luogu P5434. Counting Labeled Deserts](https://www.luogu.com.cn/problem/P5434)
-   [Luogu P3343. \[ZJOI2015\] Gensokyo After the Earthquake](https://www.luogu.com.cn/problem/P3343)
-   [HDU 5279. YJC plays Minecraft](https://acm.hdu.edu.cn/showproblem.php?pid=5279)
-   [Luogu P7364. Counting Labeled Bipartite Graphs](https://www.luogu.com.cn/problem/P7364)
-   [Luogu P5827. Counting Vertex-Biconnected Graphs](https://www.luogu.com.cn/problem/P5827)
-   [Luogu P5828. Counting Edge-Biconnected Graphs](https://www.luogu.com.cn/problem/P5828)
-   [Luogu P6596. How Many of Them](https://www.luogu.com.cn/problem/P6596)
-   [Luogu U152448. Counting Labeled Strongly Connected Graphs](https://www.luogu.com.cn/problem/U152448)
-   [Project Euler 434. Rigid graphs](https://projecteuler.net/problem=434)

## Riddell's Formula

The use of exp of an EGF above is sometimes called Riddell's formula for labeled graphs. The [Euler transform](../poly/symbolic-method.md#%E9%9B%86%E5%90%88%E7%9A%84-multiset-%E6%9E%84%E9%80%A0) of a generating function is sometimes called Riddell's formula for unlabeled graphs. The latter first appeared in Euler's study of integer partitions, and besides graph enumeration problems, it also shows up in the unbounded knapsack problem.

For a given sequence $a_i$ with OGF $A(x)$, define the Euler transform of $A(x)$ as:

$$
\begin{align}
\mathcal{E}(A(x)) &= \prod_{i} (1-x^i)^{-a_i}  \\
                  &= \exp (\sum_{i} \frac{A(x^i)}{i})  
\end{align}
$$

Let $b_i$ be the coefficients of $\mathcal{E}(A(x))$, and define the helper array $c_i = \sum_{d|n} d a_d$. Then we have the recurrence

$$
n b_n = c_n + \sum_{i=1}^{n-1} c_i b_{n-i}
$$

## Unlabeled trees

### Example problem: SPOJ PT07D Let us count 1 2 3

???+ note "Example problem [SPOJ PT07D Let us count 1 2 3](https://www.spoj.com/problems/PT07D/)"
    Summary: for n nodes, count the trees with each of the following properties.
    
    -   Labeled rooted trees [A000169](https://oeis.org/A000169).
    -   Labeled unrooted trees [A000272](https://oeis.org/A000272).
    -   Unlabeled rooted trees [A000081](https://oeis.org/A000081).
    -   Unlabeled unrooted trees [A000055](https://oeis.org/A000055).

#### Rooted trees

The labeled case was handled earlier. Now consider unlabeled rooted trees. Let their OGF be $F(x)$. Applying the Euler transform gives:

$$
F(x) = x\mathcal{E}(F(x))
$$

Then just read off the coefficients.

#### Unrooted trees

Use inclusion–exclusion: from the count of rooted trees, subtract the cases where the root is not a centroid, and split into cases by the parity of $n$.

When $n$ is odd:

There must be a subtree of size $\geq \left\lceil \frac{n}{2}\right\rceil$. Enumerating the size of this subtree gives:

$$
g_n = f_n - \sum_{i=\left\lceil\frac{n}{2}\right\rceil}^{n-1} f_i f_{n-i}
$$

When $n$ is even:

Note that when there are two centroids, the process above only subtracts once, so we also need to subtract

$$
g_n = f_n - \sum_{i=\frac{n}{2}+1}^{n-1} f_i f_{n-i} - \binom{f_{\frac{n}{2}}}{2}
$$

### Example problem: Luogu P5900 Counting Unlabeled Unrooted Trees

???+ note "Example problem [Luogu P5900 Counting Unlabeled Unrooted Trees](https://www.luogu.com.cn/problem/P5900)"
    Summary: count the unlabeled unrooted trees with n nodes ($n \leq 200000$).

For larger constraints the approach is the same: apply the Euler transform and then use polynomial templates.

## Unlabeled simple graphs

### Example problem: SGU 282. Isomorphism

???+ note "Example problem [SGU 282. Isomorphism](https://codeforces.com/problemsets/acmsguru/problem/99999/282)"
    Summary: count the ways to color the edges of an unlabeled complete graph on n vertices with m colors.

Note that when m = 2, we are counting exactly the unlabeled simple graphs [A000088](https://oeis.org/A000088). Consider Pólya's enumeration theorem:

$$
\frac{1}{|G|}\sum_{g\in G} m^{c(g)}
$$

In this problem, the permutation group $G$ is the group of edge permutations induced by the symmetric group of degree $n$ on the vertices. But brute force would enumerate $O(n!)$ permutations, which is too slow for this problem.

Instead, classify permutations by their cycle structure. Each cycle structure corresponds to an integer partition, and we generate the partitions with dfs(). The problem then becomes finding, for each partition $p$, the number of permutations $w(p)$ with that cycle structure and the number of cycles $c(p)$ in each such permutation. The answer is

$$
\frac{1}{|G|} \sum_{p \in P} w(p) m^{c(p)}
$$

Consider $w(p)$. Each part of the partition corresponds to a cyclic arrangement, and the order among parts of the same size does not matter, so we have:

$$
w(p) = \frac{n!}{\prod_{i}(p_i)\prod_{i}(q_i!)} 
$$

Here $q_i$ is the number of times parts of size $i$ appear in $p$.

Consider $c(p)$. The number of cycles on the vertex set under $p$ is $|p|$, but the problem asks about edge colorings, so we also need to look at the edge permutation induced by the vertex permutation.

If both endpoints of an edge are in the same cycle, of size $p_i$, then the edges produce exactly $\left\lfloor \frac{p_i}{2} \right\rfloor$ cycles.

If the endpoints of an edge are in two different cycles, of sizes $p_i$ and $p_j$, then each edge cycle has length $\operatorname{lcm}(p_i,p_j)$, so the edges produce exactly $\frac{p_i p_j}{\operatorname{lcm}(p_i,p_j)} = \gcd(p_i, p_j)$ cycles.

??? note "Reference code"
    ```cpp
    --8<-- "docs/math/code/combinatorics/graph-enumeration/graph-enumeration_2.cpp"
    ```

## Exercises

-   [CodeForces 438 E. The Child and Binary Tree](https://codeforces.com/problemset/problem/438/E)
-   [Luogu P5448. \[THUPC2018\] Counting Good Graphs](https://www.luogu.com.cn/problem/P5448)
-   [Luogu P5818. \[JSOI2011\] Counting Isomers](https://www.luogu.com.cn/problem/P5818)
-   [Luogu P6597. Counting Alkenes](https://www.luogu.com.cn/problem/P6597)
-   [Luogu P6598. Counting Alkanes](https://www.luogu.com.cn/problem/P6598)
-   [Luogu P4128. \[SHOI2006\] Colored Graphs](https://www.luogu.com.cn/problem/P4128)
-   [Luogu P4727. \[HNOI2009\] Counting Graph Isomorphism Classes](https://www.luogu.com.cn/problem/P4727)
-   [AtCoder Beginner Contest 222 H. Binary Tree](https://atcoder.jp/contests/abc222/tasks/abc222_h)
-   [AtCoder Beginner Contest 284 Ex. Count Unlabeled Graphs](https://atcoder.jp/contests/abc284/tasks/abc284_h)
-   [Luogu P4708. Drawing](https://www.luogu.com.cn/problem/P4708)
-   [Luogu P7592. Counting Trees (2021 CoE-II E)](https://www.luogu.com.cn/problem/P7592)
-   [Luogu P5206. \[WC2019\] Counting Trees](https://www.luogu.com.cn/problem/P5206)

## References and notes

1.  [WC2015, Gu Yuzhou's camper presentation notes: Graphical Enumeration](https://github.com/lychees/ACM-Training/blob/master/Note/%E5%86%AC%E4%BB%A4%E8%90%A5/2015/%E9%A1%BE%E6%98%B1%E6%B4%B2%E8%90%A5%E5%91%98%E4%BA%A4%E6%B5%81%E8%B5%84%E6%96%99%20Graphical%20Enumeration.pdf)
2.  [WC2019, Generating Functions, Polynomial Algorithms and Graph Counting](https://github.com/lychees/ACM-Training/tree/master/Note/%E5%86%AC%E4%BB%A4%E8%90%A5/2019/d4)
3.  [Counting labeled graphs - Algorithms for Competitive Programming](https://cp-algorithms.com/combinatorics/counting_labeled_graphs.html)
4.  [Graphical Enumeration Paperback, Frank Harary, Edgar M. Palmer](https://github.com/lychees/ACM-Training/blob/master/Note/Book/)
5.  [The encyclopedia of integer sequences, N. J. A. Sloane, Simon Plouffe](https://github.com/lychees/ACM-Training/blob/master/Note/Book/The%20encyclopedia%20of%20integer%20sequences%20\(N.%20J.A.%20Sloane%2C%20Simon%20Plouffe\).pdf)
6.  [Combinatorial Problems and Exercises, László Lovász](https://github.com/lychees/ACM-Training/blob/master/Note/Book/Combinatorial%20Problems%20and%20Exercises_L%C3%A1szl%C3%B3%20Lov%C3%A1sz.pdf)
7.  [Graph Theory and Additive Combinatorics](https://yufeizhao.com/gtacbook/)
