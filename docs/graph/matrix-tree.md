author: pw384, s0cks5, Watersail2005, Xeonacid

The matrix-tree theorem solves the problem of counting the spanning trees of a graph.

## Notation used on this page

Graphs on this page, whether undirected or directed, may have multiple edges, but by default they have no self-loops.

??? note "Graphs with self-loops"
    Self-loops do not change the number of spanning trees, so just ignore them when computing the Laplacian matrix. However, when counting Eulerian circuits with the BEST theorem, the degrees must include self-loops.

### Undirected graphs

Let $G$ be an undirected graph with $n$ vertices. Define the degree matrix $D(G)$ as

$$
D_{ii}(G) = \mathrm{deg}(i),\ D_{ij} = 0,\ i\neq j.
$$

Let $\#e(i,j)$ be the number of edges between vertex $i$ and vertex $j$, and define the adjacency matrix $A$ as

$$
A_{ij}(G)=A_{ji}(G)=\#e(i,j),\ i\neq j.
$$

Define the Laplacian matrix (also called the Kirchhoff matrix) $L$ as

$$
L(G) = D(G) - A(G).
$$

Let $t(G)$ be the number of spanning trees of $G$.

### Directed graphs

Let $G$ be a directed graph with $n$ vertices. Define the out-degree matrix $D^\mathrm{out}(G)$ as

$$
D^\mathrm{out}_{ii}(G) = \mathrm{deg}^\mathrm{out}(i),\ D^\mathrm{out}_{ij} = 0,\ i\neq j.
$$

Define the in-degree matrix $D^\mathrm{in}(G)$ in the same way.

Let $\#e(i,j)$ be the number of directed edges from vertex $i$ to vertex $j$, and define the adjacency matrix $A$ as

$$
A_{ij}(G)=\#e(i,j),\ i\neq j.
$$

Define the out-degree Laplacian matrix $L^\mathrm{out}$ as

$$
L^\mathrm{out}(G) = D^\mathrm{out}(G) - A(G).
$$

Define the in-degree Laplacian matrix $L^\mathrm{in}$ as

$$
L^\mathrm{in}(G) = D^\mathrm{in}(G) - A(G).
$$

Let $t^\mathrm{root}(G,k)$ be the number of root-directed arborescences of $G$ rooted at $k$. A root-directed arborescence (in-tree) is one whose underlying undirected graph is a tree and whose edges all point toward the parent.

Let $t^\mathrm{leaf}(G,k)$ be the number of leaf-directed arborescences of $G$ rooted at $k$. A leaf-directed arborescence (out-tree) is one whose underlying undirected graph is a tree and whose edges all point toward the children.

## Statement of the theorem

The matrix-tree theorem comes in several forms.

Let $[n]=\{1,2,\cdots,n\}$. For a matrix $A$, the submatrix $A_{S,T}$ is the submatrix formed by the entries $A_{i,j}\pod{i\in S,j\in T}$.

???+ note "Theorem 1 (matrix-tree theorem, undirected graphs, determinant form)"
    For an undirected graph $G$ and any $k$,
    
    $$
    t(G) = \det L(G)_{[n]\setminus\{k\},[n]\setminus\{k\}}.
    $$
    
    In other words, all $(n-1)$-th order principal minors of the Laplacian matrix of an undirected graph are equal, and they all equal the number of spanning trees of the graph.

???+ note "Corollary 1 (matrix-tree theorem, undirected graphs, eigenvalue form)"
    Let $\lambda_1\ge\lambda_2\ge\cdots\ge\lambda_{n-1}\ge\lambda_n=0$ be the $n$ eigenvalues of $L(G)$. Then
    
    $$
    t(G) = \frac{1}{n}\lambda_1\lambda_2\cdots\lambda_{n-1}.
    $$

???+ note "Theorem 2 (matrix-tree theorem, directed graphs, root-directed trees, determinant form)"
    For a directed graph $G$ and any $k$,
    
    $$
    t^\mathrm{root}(G,k) = \det L^\mathrm{out}(G)_{[n]\setminus\{k\},[n]\setminus\{k\}}.
    $$
    
    In other words, the principal minor of the out-degree Laplacian of a directed graph obtained by deleting row $k$ and column $k$ equals the number of root-directed arborescences rooted at $k$.

So to count all root-directed arborescences of a graph, just enumerate every root $k$ and sum $t^\mathrm{root}(G,k)$.

???+ note "Theorem 3 (matrix-tree theorem, directed graphs, leaf-directed trees, determinant form)"
    For a directed graph $G$ and any $k$,
    
    $$
    t^\mathrm{leaf}(G,k) = \det L^\mathrm{in}(G)_{[n]\setminus\{k\},[n]\setminus\{k\}}.
    $$
    
    In other words, the principal minor of the in-degree Laplacian of a directed graph obtained by deleting row $k$ and column $k$ equals the number of leaf-directed arborescences rooted at $k$.

So to count all leaf-directed arborescences of a graph, just enumerate every root $k$ and sum $t^\mathrm{leaf}(G,k)$.

???+ note "Remark"
    Root-directed arborescences are also called inward arborescences (in-trees). But they are counted using out-degrees, so to avoid confusing $\mathrm{in}$ and $\mathrm{out}$, we use the term "root-directed".

## Proof of the theorem

The theorems above look very similar. Here we give one unified proof, and extend the earlier results to weighted graphs.

The outline of the proof is:

-   First, every case can be reduced to counting root-directed arborescences in a directed graph;
-   Use the language of matrices to give a necessary and sufficient condition for a set of chosen edges to form a root-directed arborescence;
-   Link the choice of edges to the determinant of the Laplacian matrix via the Cauchy–Binet formula;
-   Finally, turn the determinant form into the eigenvalue form.

### Lemma: the Cauchy–Binet formula

???+ note "Lemma 1 (Cauchy–Binet)"
    Given an $n\times m$ matrix $A$ and an $m\times n$ matrix $B$,
    
    $$
    \det(AB)=\sum_{S\subset[m];~|S|=n}\det A_{[n],S}\det B_{S,[n]},
    $$
    
    Here the sum means $S$ ranges over all subsets of $[m]$ of size $n$. If $n>m$, then necessarily $\det(AB)=0$.

??? note "Proof (combinatorial view)"
    Following the model of [NOI2021 Path Intersections](https://loj.ac/p/3533), first consider the following combinatorial meaning of the determinant. For an $n\times n$ matrix $C$, build a directed acyclic graph $G=(V,E)$. Its vertex set is $V=[2]\times[n]\subset\mathbb R^2$, that is, two columns of points in the plane. Call the left column $L=\{l_i=(1,i):i\in[n]\}$ and the right column $R=\{r_i=(2,i):i\in[n]\}$. The directed edge set is $E=\{(l_i,r_j):i,j\in[n]\}$, with edge weights $w(l_i,r_j)=C_{i,j}$. In this graph, a subset $E^\sigma\subset E$ of $n$ edges is called a path system if its starting points are all distinct and its end points are all distinct. Clearly, path systems $E^\sigma$ correspond one-to-one with permutations $\sigma$ of $[n]$. Notice that if we draw a path system in the plane, its edges may cross each other, and the number of crossings (counted with multiplicity) equals the number of inversions of $\sigma$. This is because edge $(l_i,r_{\sigma(i)})$ and edge $(l_j,r_{\sigma(j)})$ cross if and only if $(i-j)(\sigma(i)-\sigma(j))< 0$, that is, they form an inversion. For convenience, we call the parity of the number of inversions of the corresponding permutation, which is also the parity of the number of crossings of the path system, the parity of the path system. So if we count these path systems by weight, and subtract the count of path systems with an odd number of crossings from the count with an even number, we get the Leibniz expansion of the determinant:
    
    $$
    \det(C)=\sum_{\sigma\in S_n}\mathrm{sgn}(\sigma)\prod_{i\in[n]}C_{i,\sigma(i)},
    $$
    
    Here $S_n$ is the permutation group on $[n]$, and $\mathrm{sgn}(\sigma)$ is the sign of the permutation $\sigma$ (it is $1$ when the number of inversions is even and $-1$ when it is odd).
    
    With this combinatorial meaning of the determinant, we can prove the Cauchy–Binet formula using the following combinatorial model. For an $n\times m$ matrix $A$ and an $m\times n$ matrix $B$, build a directed acyclic graph $G=(V,E)$. Its vertex set is $V=L\cup D\cup R$, where $L=\{l_i=(1,i):i\in[n]\}$, $D=\{d_i=(2,i):i\in[m]\}$ and $R=\{r_i=(3,i):i\in[n]\}$. The directed edge set is $E=E_L\cup E_R$, where $E_L=\{(l_i,d_j):i\in[n],j\in[m]\}$ and $E_R=\{(d_j,r_i):j\in[m],i\in[n]\}$, with edge weights $w(l_i,d_j)=A_{i,j}$ and $w(d_j,r_i)=B_{j,i}$ respectively. Again, consider path systems from $L$ through $D$ to $R$ (where no two paths share a vertex), count them by weight, and subtract the count with an odd number of crossings from the count with an even number. We now show that the two sides of the Cauchy–Binet formula compute this quantity in two different ways.
    
    For the left side, starting from the graph $G$ described above, build a new graph $G'$ with vertex set $V'=L\cup R$ and edge set $E'=\{(l_i,r_j):i,j\in[n]\}$, where edge $(l_i,r_j)$ gets weight $\sum_{k\in[m]}A_{i,k}B_{k,j}$, the weighted count of simple paths from $l_i$ to $r_j$ in the original graph $G$. This weight is exactly $(AB)_{i,j}$. This simplifies the three-layer graph into a two-layer graph. However, path systems in the two-layer graph $G'$ (counted by weight) do not correspond one-to-one with path systems in the three-layer graph $G$. In the two-layer graph, each path corresponds to several simple paths in the three-layer graph. When counting path systems in the two-layer graph, we multiply weights, which amounts to combining the corresponding sets of paths in the three-layer graph in all possible ways. This inevitably includes cases where paths share an intermediate vertex. But such pairs of paths sharing an intermediate vertex contribute nothing to the final answer. For $i_1< i_2$, $j_1< j_2$ and any intermediate vertex $d$, there are two pairs of simple paths, $(l_{i_1}\rightarrow d\rightarrow r_{j_1}, l_{i_2}\rightarrow d\rightarrow r_{j_2})$ and $(l_{i_1}\rightarrow d\rightarrow r_{j_2}, l_{i_2}\rightarrow d\rightarrow r_{j_1})$, and the parities of their numbers of crossings in the three-layer graph must be opposite, because looking only at starting and end points, the two pairs have swapped end points. So in the count on the simplified two-layer graph, the contributions of paths sharing an intermediate vertex cancel in pairs. For the remaining cases, once the starting and end points of two paths are fixed, the parity of their number of crossings does not depend on how the intermediate vertices are chosen (as long as they are different). So all path systems in the original graph $G$ that correspond to one path system in $G'$ have the same parity. Therefore $\det(AB)$ gives one way to compute the difference of path system counts described above.
    
    The right side enumerates all possible combinations of intermediate vertices. Given any set of intermediate vertices $S\subset D=[m]$ with $|S|=n$, consider path systems from $L$ to $S$ and from $S$ to $R$. Joining them gives a path system from $L$ to $R$, and the composition of the permutations of the first two path systems equals the permutation of the joined path system. So the product of the parities of the first two path systems equals the parity of the joined one. Hence the difference of counts for all path systems whose set of intermediate vertices is $S$ equals the product of the difference of counts for path systems from $L$ to $S$ and that for path systems from $S$ to $R$. Summing over all possible $S$ gives the right side, so it is exactly the difference of path system counts described above.

??? note "Proof (algebraic view)"
    The combinatorial proof above can actually be translated word for word into an algebraic proof. Here we give a different, more technical algebraic proof that uses a few well-known results. When $m< n$, the determinant is zero, because
    
    $$
    \mathrm{rank}(AB)\le \min\{\mathrm{rank}(A),\mathrm{rank}(B)\}\le m< n.
    $$
    
    When $m=n$, the Cauchy–Binet formula just says that the determinant of a product of square matrices equals the product of their determinants.
    
    When $m>n$, note that
    
    $$
    x^{m-n}\det(xI_n+AB) = \det(xI_m+BA).
    $$
    
    It is also known that the coefficient of $x^{n-k}$ in $\det(xI_n+C)$ is the sum of all $k$-th order principal minors of $C$. So comparing coefficients on both sides of the equation above gives
    
    $$
    \det(AB) = \sum_{S\subset[m];~|S|=n}\det (BA)_{S,S} = \sum_{S\subset[m];~|S|=n}\det B_{S,[n]}\det A_{[n],S} = \sum_{S\subset[m];~|S|=n}\det A_{[n],S}\det B_{S,[n]}.
    $$
    
    Here the second equality uses the result for the case $m=n$.

### Describing the graph structure with incidence matrices

Consider a directed graph $G=(V,E)$ with $n$ vertices and $m$ edges, where edge $e$ has weight $w(e)$. We can define the $m\times n$ out-degree incidence matrix

$$
M^\mathrm{out}_{ij}=\begin{cases}
\sqrt{w(e_i)},&\exists u(e_i=(v_j,u)),\\
0,&\textrm{otherwise},
\end{cases}
$$

and the $m\times n$ in-degree incidence matrix

$$
M^\mathrm{in}_{ij}=\begin{cases}
\sqrt{w(e_i)},&\exists u(e_i=(u,v_j)),\\
0,&\textrm{otherwise}.
\end{cases}
$$

Each row of these matrices records one edge: the out-degree incidence matrix $M^\mathrm{out}$ records the starting point of the edge, and the in-degree incidence matrix $M^\mathrm{in}$ records its end point.

A simple calculation shows that

$$
D^\mathrm{out}(G) = (M^\mathrm{out})^T M^\mathrm{out},\ A(G) = (M^\mathrm{out})^T M^\mathrm{in},\ D^\mathrm{in}(G) = (M^\mathrm{in})^T M^\mathrm{in}.
$$

Hence

$$
L^\mathrm{out}(G) = (M^\mathrm{out})^T (M^\mathrm{out}-M^\mathrm{in}),\ L^\mathrm{in}(G) = (M^\mathrm{in}-M^\mathrm{out})^T M^\mathrm{in}.
$$

The Cauchy–Binet formula above shows that a principal minor of the Laplacian matrix is really a sum over a family of substructures. Each substructure reflects a property of the corresponding subgraph.

???+ note "Lemma 2"
    For a vertex subset $W\subseteq V$ and an edge subset $S\subseteq E$ with $|W|=|S|\le n$: when the subgraph $T=(V,S)$ is a root-directed forest with roots $V\setminus W$, the expression
    
    $$
    \det(M^\mathrm{out}_{S,W})\det(M^\mathrm{out}_{S,W}-M^\mathrm{in}_{S,W})
    $$
    
    equals $\prod_{e\in S}w(e)$, written $w(T)$; otherwise, the expression equals zero.

??? note "Proof"
    We may assume $w(e)=1$. This is because the determinant is multilinear: from each row of each determinant we can factor out $\sqrt{w(e)}$, and the product of these factors is $w(T)$.
    
    First, look at when each of the two factors is zero. In the first factor $\det(M^\mathrm{out}_{S,W})$, each row has at most one nonzero entry, namely $+1$. If any row is all zero, or two rows have their $+1$ in the same column, the determinant must be zero. So this determinant is nonzero if and only if every row and every column has exactly one $+1$; that is, every edge in $S$ starts in $W$, and every vertex in $W$ is the starting point of exactly one edge in $S$. For $T$ to be a root-directed forest with roots $V\setminus W$, a necessary condition is that every vertex except the roots has exactly one parent, and this makes the factor nonzero. The converse does not necessarily hold, because there may be cycles, so we also need to look at the second factor. Note that the end points of edges in $S$ need not be in $W$.
    
    Assume the first factor is nonzero. Then the subgraph $T$ is a root-directed forest if and only if $T$ has no cycles. In this case, each row of the second factor $\det(M^\mathrm{out}_{S,W}-M^\mathrm{in}_{S,W})$ has one $+1$, and possibly one or zero $-1$. For an edge whose end point is also in $W$: if the end point of $e_i$ is the starting point of $e_j$, add the row of $e_j$ to the row of $e_i$, which cancels the $-1$ in row $e_i$. You can think of this row as now describing the simple path formed by joining $e_i$ and $e_j$ end to end. If a new $-1$ appears in the row, the end point of $e_j$ is also in $W$, and the position of the $-1$ is the end point of $e_j$. Then we can find the edge starting at the end point of $e_j$ and add it to the row again. Such an edge always exists, because the previous paragraph showed that every vertex in $W$ is the starting point of exactly one edge in $S$. This continues until no $-1$ remains in the row, which amounts to repeatedly extending the simple path $e_i\rightarrow e_j\rightarrow \cdots\rightarrow e_k$. At that point, if only one $+1$ is left in the row, the end point of $e_k$ is not among the chosen vertices $W$, and the process stops. If the last added edge happens to cancel the existing $+1$, so the row becomes all zero, then the end point of the new edge $e_k$ is the starting point of the first edge $e_i$, which means a cycle appeared. If the process never stops, the path has entered a cycle, and the rows of the edges on that cycle also become zero. So there are no cycles if and only if these operations can turn the determinant into a form where every row has exactly one $+1$. Since the positions of these $+1$s are the starting points of the edges of the rows, the resulting matrix is exactly $M^\mathrm{out}_{S,W}$, so the two determinants are equal.
    
    In summary, if $T$ is not a root-directed forest, then either $\det(M^\mathrm{out}_{S,W})=0$ or $\det(M^\mathrm{out}_{S,W}-M^\mathrm{in}_{S,W})=0$. Otherwise, both are nonzero, and their product equals $\left(\det(M^\mathrm{out}_{S,W})\right)^2=1$.

### Matrix-tree theorem for weighted directed graphs

Now we can prove the main result of this page. All the matrix-tree theorems above are special cases of it.

???+ note "Theorem 4 (matrix-tree theorem, weighted directed graphs, root-directed trees, determinant form)"
    For any $k$,
    
    $$
    \sum_{T\in\mathcal T^\mathrm{root}(G,k)}w(T)=\det L^\mathrm{out}(G)_{[n]\setminus\{k\},[n]\setminus\{k\}}.
    $$
    
    Here $\mathcal T^\mathrm{root}(G,k)$ is the set of root-directed arborescences of $G$ rooted at $k$.

??? note "Proof"
    Let $W=[n]\setminus\{k\}$ be the set of all vertices except $k$. Then by the Cauchy–Binet formula, the right side can be written as
    
    $$
    \det L^\mathrm{out}(G)_{W,W} = \sum_{S\subset[m];~|S|=n-1}\det(M^\mathrm{out}_{S,W})\det(M^\mathrm{out}_{S,W}-M^\mathrm{in}_{S,W}).
    $$
    
    Go through all $S$. By Lemma 2, the right side gains a term $w(T)$ if and only if $T=(V,S)$ is a root-directed forest with roots $V\setminus W=\{k\}$, that is, if and only if $T$ is a root-directed arborescence rooted at $k$.

When $w(e)=1$, every tree has weight $1$, so the left side is just the number of trees, $t^\mathrm{root}(G,k)$. This gives Theorem 2. In the same way, the result extends directly to leaf-directed arborescences, which gives Theorem 3. Finally, to count spanning trees of an undirected graph, apply the following corollary.

???+ note "Corollary 2 (matrix-tree theorem, weighted undirected graphs, determinant form)"
    For an undirected graph $G$ and any $k$,
    
    $$
    \sum_{T\in\mathcal T(G)}w(T) = \det L(G)_{[n]\setminus\{k\},[n]\setminus\{k\}}.
    $$
    
    Here $\mathcal T(G)$ is the set of spanning trees of $G$. This also shows that all $(n-1)$-th order principal minors of $L(G)$ are equal.

??? note "Proof"
    For an undirected graph $G=(V,E)$, build a directed graph $G'=(V,E')$ with $E'=\{(v_i,v_j):(v_i,v_j)\in E\}\cup\{(v_j,v_i):(v_i,v_j)\in E\}$; that is, each undirected edge of $G$ is split into two directed edges with opposite directions. Pick any $k$. Then root-directed arborescences of $G'$ rooted at $k$ correspond one-to-one with spanning trees of $G$. To go from the former to the latter, just drop the edge directions and the choice of root. To go from the latter to the former, start from the chosen root $k$ and orient every edge toward the root. So
    
    $$
    \sum_{T\in\mathcal T(G)}w(T) = \sum_{T\in\mathcal T^\mathrm{root}(G',k)}w(T) = \det L^\mathrm{out}(G')_{[n]\setminus\{k\},[n]\setminus\{k\}} = \det L(G)_{[n]\setminus\{k\},[n]\setminus\{k\}}.
    $$
    
    Here we used the fact $L^\mathrm{out}(G')=L(G)$, which is easy to check directly.

### Eigenvalue form

Again, we first consider the result for directed graphs.

???+ note "Theorem 5"
    For a directed graph $G$, define the multivariate polynomial
    
    $$
    \chi(x_1,\cdots,x_n)=\det(\mathrm{diag}(x_1,\cdots,x_n)-L^\mathrm{out}(G)).
    $$
    
    Here $\mathrm{diag}(x_1,\cdots,x_n)$ is the diagonal matrix with diagonal entries $x_1,\cdots,x_n$. Then
    
    $$
    (-1)^{n-r}[x_{k_1}\cdots x_{k_r}]\chi(x_1,\cdots,x_n)
    $$
    
    equals the (weighted) number of root-directed forests of $G$ with roots $\{k_1,\cdots,k_r\}$.

??? note "Proof"
    As in the proof of Theorem 4, note that if we let $W=[n]\setminus\{k_1,\cdots,k_r\}$, the expression in the theorem is just $\det L^\mathrm{out}(G)_{W,W}$ (you can see this directly from the Leibniz expansion of the determinant). By the Cauchy–Binet formula, it equals
    
    $$
    \det L^\mathrm{out}(G)_{W,W} = \sum_{S\subset[m];~|S|=n-r}\det(M^\mathrm{out}_{S,W})\det(M^\mathrm{out}_{S,W}-M^\mathrm{in}_{S,W}).
    $$
    
    Go through all $S$. By Lemma 2, the right side gains a term $w(T)$ if and only if $T=(V,S)$ is a root-directed forest with roots $V\setminus W=\{k_1,\cdots,k_r\}$.

Substituting $x$ for all the variables gives the characteristic polynomial of the Laplacian matrix

$$
P(x) = \det(xI-L^\mathrm{out}(G)) = \chi(x,\cdots,x).
$$

???+ note "Lemma 3"
    The Laplacian matrix $L^\mathrm{out}(G)$ has at least one zero eigenvalue.

??? note "Proof"
    It suffices to show that its determinant is zero. As in the proofs of Theorems 4 and 5, take $W=[n]$ (so the set of roots is empty). Then the determinant should equal the number of root-directed forests with zero trees. No such forest exists, so the determinant is zero.

???+ note "Corollary 3"
    For a directed graph $G$, the total weight of all root-directed forests made of $k$ trees equals the coefficient
    
    $$
    (-1)^{n-k}[x^k]P(x).
    $$

??? note "Proof"
    Just sum over all possible choices of $k$ roots.

A $k$-spanning forest is a spanning subgraph of the graph that has $k$ connected components and no cycles.

???+ note "Corollary 4"
    Let $\mathcal T_k(G)$ be the set of $k$-spanning forests of the undirected graph $G$, and let $P(x)=\det(xI-L(G))$ be the characteristic polynomial of its Laplacian matrix. Then
    
    $$
    \sum_{T\in\mathcal T_k(G)}w(T)Q(T) = (-1)^{n-k}[x^k]P(x).
    $$
    
    Here $Q(T)$ is the product of the numbers of vertices of the connected components of the forest $T$. In particular, when $k=1$, $Q(T)=n$, so
    
    $$
    n\sum_{T\in\mathcal T(G)}w(T) = \lambda_1\lambda_2\cdots\lambda_{n-1}.
    $$

??? note "Proof"
    As in the proof of Corollary 2, we can use Corollary 3 directly. Each root-directed forest of $k$ trees in the directed graph corresponds to a $k$-spanning forest of the undirected graph. But each $k$-spanning forest $T$ has $Q(T)$ ways to choose its roots, so it appears in $Q(T)$ root-directed forests of the directed graph.

## Applications

### Cayley's formula

???+ note "Corollary 5 (Cayley)"
    There are $n^{n-2}$ labeled unrooted trees on $n$ vertices.

??? note "Proof"
    Equivalently, we only need to show that the complete graph on $n$ vertices has $n^{n-2}$ spanning trees. Write down its Laplacian matrix
    
    $$
    L(G) = \left(\begin{matrix} n-1 & -1 & \cdots & -1 \\ -1 & n-1 & \cdots & -1 \\ \vdots & \vdots & \ddots & \vdots \\ -1 & -1 & \cdots & n-1  \end{matrix}\right)_{n\times n}.
    $$
    
    Computing any of its principal minors gives
    
    $$
    \det(nI_{n-1}-{\bf 1}{\bf 1}^T) = n^{n-1}\det(I_{n-1}-n^{-1}{\bf 1}{\bf 1}^T) = n^{n-1}(1-n^{-1}{\bf 1}^T{\bf 1}) = n^{n-1}(1-(n-1)/n) = n^{n-2}.
    $$
    
    Applying Theorem 1 gives the result.

### BEST theorem

Prerequisites: [Eulerian graphs](./euler.md)

This theorem relates the number of Eulerian circuits in a directed Eulerian graph to the number of root-directed arborescences of the graph, which solves the problem of counting Eulerian circuits in directed graphs. Note that counting Eulerian circuits in a general undirected graph is #P-complete.

When implementing this, first check whether the given graph is Eulerian and remove all vertices of degree zero. Then build the graph, count its root-directed arborescences, and use the BEST theorem to get the number of Eulerian circuits. Note that if the Eulerian circuits must start at a given vertex, multiply the answer by that vertex's out-degree, which amounts to enumerating the first edge of the circuit.

Before proving the BEST theorem, we need the following result.

???+ note "Property (when a directed graph has an Eulerian circuit)"
    A directed graph has an Eulerian circuit if and only if its vertices with nonzero degree are strongly connected and every vertex has equal in-degree and out-degree.

In an Eulerian graph, in-degree equals out-degree, so we drop the superscript and write $\mathrm{deg}(v)$. The BEST theorem can be stated as follows.

???+ note "Theorem 6 (BEST theorem)"
    Let $G$ be a directed Eulerian graph and $k$ any vertex. Then the total number $\mathrm{ec}(G)$ of distinct Eulerian circuits of $G$ is
    
    $$
    \mathrm{ec}(G) = t^\mathrm{root}(G,k)\prod_{v\in V}(\deg (v) - 1)!.
    $$
    
    This also shows that for any two vertices $k, k'$ of an Eulerian graph $G$, $t^\mathrm{root}(G,k)=t^\mathrm{root}(G,k')$.

??? note "Proof"
    The rough idea is to build a correspondence between Eulerian circuits starting at $k$ and pairs consisting of a root-directed arborescence rooted at $k$ and orderings of the outgoing edges at every vertex. Once the Eulerian circuit is required to start at $k$, the count we need to prove is
    
    $$
    \mathrm{deg}(k)\mathrm{ec}(G) = t^\mathrm{root}(G,k)\deg(k)!\prod_{v\neq k}(\deg (v) - 1)!.
    $$
    
    The combinatorial meaning of this count corresponds to the following construction. For an Eulerian circuit starting at $k$, from the order in which edges appear in the circuit we can build
    
    -   a root-directed arborescence rooted at $k$, made of the last outgoing edge at each non-root vertex, which gives $t^\mathrm{root}(G,k)$,
    -   the order of all outgoing edges at the root $k$, which gives $\mathrm{deg}(k)!$, and
    -   at each non-root vertex $v\neq k$, the order of all outgoing edges except the last one, which gives $(\mathrm{deg}(v)-1)!$.
    
    Below we show that the map given by this construction is a bijection.
    
    On one hand, given an Eulerian circuit, we need to show that the last outgoing edges at all non-root vertices form a root-directed arborescence. By construction, each non-root vertex in the tree has exactly one outgoing edge, so we only need to show that these edges form no cycle. Notice that if we order all vertices by their last appearance in the Eulerian circuit, the last outgoing edge of a non-root vertex must point to a vertex that comes strictly later in this order. If there were a cycle, it would contain a vertex that comes last in the order. Since it lies on the cycle, it points to a vertex that does not come later, which contradicts the above. So the last outgoing edges of the non-root vertices must form a root-directed arborescence.
    
    On the other hand, given any root-directed arborescence and orderings of the remaining outgoing edges, we can recover an Eulerian circuit that the construction above maps to exactly this arborescence and these orderings. To do so, start from the root $k$. Each time we arrive at a vertex, use the given ordering of that vertex's outgoing edges and take the earliest outgoing edge not used yet as the next edge of the circuit. If all edges in that vertex's ordering have been used, take the vertex's outgoing edge in the root-directed arborescence as the next edge. Since the graph is Eulerian, every vertex has equal in-degree and out-degree, so this process cannot stop at a non-root vertex; that is, the resulting path is indeed a circuit. To show it is a valid Eulerian circuit, we only need to show that the process uses every edge.
    
    If not, some outgoing edge of some vertex $v$ is never used. Consider vertex $v$. It cannot be the root: the process ends at the root, and if the root still had unused outgoing edges, the process would not have ended, a contradiction. So $v$ is not the root. By the process described above, as long as the non-root vertex $v$ has any unused outgoing edge, its outgoing edge $e$ in the tree must also be unused. Let $e=(v,u)$. Since some incoming edge of $u$ is unused, and the out-degree of $u$ equals its in-degree, some outgoing edge of $u$ must be unused. Then we can examine vertex $u$ in the same way. This reasoning moves the vertex under consideration from $v$ to $u$, one step along the root-directed arborescence toward the root. By induction, some outgoing edge of the root $k$ must then be unused. We showed above that this is impossible, a contradiction. So the path obtained in the previous paragraph is indeed a valid Eulerian circuit.
    
    One can check that these maps are all injective, so they must both be bijections. This proves the theorem.

## Implementation

Write down the Laplacian matrix of the graph, delete one row and the matching column, and compute the determinant of the resulting matrix. The determinant can be computed with Gaussian elimination.

For example, the number of spanning trees of a square graph:

$$
\begin{pmatrix}
2 & 0 & 0 & 0 \\
0 & 2 & 0 & 0 \\
0 & 0 & 2 & 0 \\
0 & 0 & 0 & 2 \end{pmatrix}-\begin{pmatrix}
0 & 1 & 0 & 1 \\
1 & 0 & 1 & 0 \\
0 & 1 & 0 & 1 \\
1 & 0 & 1 & 0 \end{pmatrix}=\begin{pmatrix}
2 & -1 & 0 & -1 \\
-1 & 2 & -1 & 0 \\
0 & -1 & 2 & -1 \\
-1 & 0 & -1 & 2 \end{pmatrix}
$$

$$
\begin{vmatrix}
2 & -1 & 0 \\
-1 & 2 & -1 \\
0 & -1 & 2 \end{vmatrix} = 4
$$

This can be solved with Gaussian elimination in $O(n^3)$ time.

??? note "Implementation"
    ```cpp
    #include <algorithm>
    #include <cmath>
    #include <cstdlib>
    #include <cstring>
    #include <iostream>
    using namespace std;
    constexpr double eps = 1e-7;
    
    struct matrix {
      static constexpr int MAXN = 20;
      int n, m;
      double mat[MAXN][MAXN];
    
      matrix() { memset(mat, 0, sizeof(mat)); }
    
      void print() {
        cout << "MATRIX " << n << " " << m << endl;
        for (int i = 0; i < n; i++) {
          for (int j = 0; j < m; j++) {
            cout << mat[i][j] << "\t";
          }
          cout << endl;
        }
      }
    
      void random(int n) {
        this->n = n;
        this->m = n;
        for (int i = 0; i < n; i++)
          for (int j = 0; j < n; j++) mat[i][j] = rand() % 100;
      }
    
      void initSquare() {
        this->n = 4;
        this->m = 4;
        memset(mat, 0, sizeof(mat));
        mat[0][1] = mat[0][3] = -1;
        mat[1][0] = mat[1][2] = -1;
        mat[2][1] = mat[2][3] = -1;
        mat[3][0] = mat[3][2] = -1;
        mat[0][0] = mat[1][1] = mat[2][2] = mat[3][3] = 2;
        this->n--;  // remove a row
        this->m--;  // remove a column
      }
    
      double gauss() {
        double ans = 1;
        for (int i = 0; i < n; i++) {
          int sid = i;
          for (int j = i + 1; j < n; j++)
            if (abs(mat[j][i]) > abs(mat[sid][i])) sid = j;
          if (abs(mat[sid][i]) <= eps) return 0;
          if (sid != i) {
            for (int j = 0; j < n; j++) swap(mat[sid][j], mat[i][j]);
            ans = -ans;
          }
          for (int j = i + 1; j < n; j++) {
            double ratio = mat[j][i] / mat[i][i];
            for (int k = 0; k < n; k++) {
              mat[j][k] -= mat[i][k] * ratio;
            }
          }
        }
        for (int i = 0; i < n; i++) ans *= mat[i][i];
        return ans;
      }
    };
    
    int main() {
      srand(1);
      matrix T;
      // T.random(2);
      T.initSquare();
      T.print();
      double ans = T.gauss();
      T.print();
      cout << ans << endl;
    }
    ```

## Example problems

???+ note "Example problem 1: [HEOI2015 Little Z's Rooms](https://loj.ac/problem/2122)"
    **Solution** A direct application of the matrix-tree theorem. Treat each empty room as a vertex and build the graph from the input. After getting the Laplacian matrix, delete row $i$ and column $i$ of $L$ for any $i$, and compute the determinant of this minor. To compute the determinant, use Gaussian elimination to reach an upper triangular matrix and multiply the diagonal entries. Also, this problem needs Gaussian elimination over $\mathbb{Z}/10^9\mathbb{Z}$, which can be done with the Euclidean algorithm.

???+ note "Example problem 2: [FJOI2007 Wheel Virus](https://www.luogu.com.cn/problem/P2144)"
    **Solution** There are many ways to solve this problem; the matrix-tree theorem is the most direct. For input $n$, it is easy to write down its Laplacian matrix of order $n+1$:
    
    $$
    L_n = \begin{bmatrix}
    n&  -1&  -1&  -1&  \cdots&  -1&  -1\\
    -1&  3&  -1&  0&  \cdots&  0&  -1\\
    -1&  -1&  3&  -1&  \cdots&  0&  0\\
    -1&  0&  -1&  3&  \cdots&  0&  0\\
    \vdots&  \vdots&  \vdots&  \vdots&  \ddots&  \vdots&  \vdots\\
    -1&  0&  0&  0&  \cdots&  3&  -1\\
    -1&  -1&  0&  0&  \cdots&  -1&  3\\
    \end{bmatrix}_{n+1}
    $$
    
    Compute the determinant of one of its $n$-th order minors. All that is left is big-integer arithmetic.

??? note "Example problem 2+"
    A harder version of example problem 2: $n\leq 100000$, but the answer is taken modulo 1000007. (Solving this requires some linear algebra.)
    
    **Solution** Derive a recurrence, then use fast matrix exponentiation.
    
    Deriving the recurrence:
    
    Notice that the matrix obtained by deleting row 1 and column 1 of $L_n$ has a very regular pattern, so we really need the determinant of the matrix
    
    $$
    M_n = \begin{bmatrix}
    3&  -1&  0&  \cdots&  0&  -1\\
    -1&  3&  -1&  \cdots&  0&  0\\
    0&  -1&  3&  \cdots&  0&  0\\
    \vdots&  \vdots&  \vdots&  \ddots&  \vdots&  \vdots\\
    0&  0&  0&  \cdots&  3&  -1\\
    -1&  0&  0&  \cdots&  -1&  3\\
    \end{bmatrix}_{n}
    $$
    
    Expanding the determinant of $M_n$ along the first column gives
    
    $$
    \det M_n = 3\det \begin{bmatrix}
    3&  -1&  \cdots&  0&  0\\
    -1&  3&  \cdots&  0&  0\\
    \vdots&  \vdots&  \ddots&  \vdots&  \vdots\\
    0&  0&  \cdots&  3&  -1\\
    0&  0&  \cdots&  -1&  3\\
    \end{bmatrix}_{n-1} + \det\begin{bmatrix}
    -1&  0&  \cdots&  0&  -1\\
    -1&  3&  \cdots&  0&  0\\
    \vdots&  \vdots&  \ddots&  \vdots&  \vdots\\
    0&  0&  \cdots&  3&  -1\\
    0&  0&  \cdots&  -1&  3\\
    \end{bmatrix}_{n-1} + (-1)^n \det\begin{bmatrix}
    -1&  0&  \cdots&  0&  -1\\
    3&  -1&  \cdots&  0&  0\\
    -1&  3&  \cdots&  0&  0\\
    \vdots&  \vdots&  \ddots&  \vdots&  \vdots\\
    0&  0&  \cdots&  3&  -1\\
    \end{bmatrix}_{n-1}
    $$
    
    Denote the determinants of the three matrices above by $d_{n-1}, a_{n-1}, b_{n-1}$.  
    Notice that $d_n$ is a tridiagonal determinant. Expanding in a similar way gives the recurrence $d_n=3d_{n-1}-d_{n-2}$. Similarly, expansion gives $a_{n-1}=-d_{n-2}-1$ and $(-1)^n b_{n-1}=-d_{n-2}-1$.  
    Substituting these into the equation above gives:
    
    $$
    \det M_n = 3d_{n-1}-2d_{n-2}-2
    $$
    
    $$
    d_n = 3d_{n-1}-d_{n-2}
    $$
    
    So we guess that $\det M_n$ also satisfies a non-homogeneous second-order linear recurrence. Using the method of undetermined coefficients, the final recurrence is
    
    $$
    \det M_n = 3\det M_{n-1} - \det M_{n-2} + 2
    $$
    
    After rewriting it as $(\det M_n+2) = 3(\det M_{n-1}+2) - (\det M_{n-2} + 2)$, fast matrix exponentiation gives the answer.

???+ note "Example problem 3: [BZOJ3659 WHICH DREAMED IT](https://hydro.ac/p/bzoj-P3659)"
    **Solution** This is a direct application of the BEST theorem. But note that the problem says "two ways of completing the task are different if and only if the keys are used in a different order". So for each Eulerian circuit, room 1 can leave along any of its outgoing edges, and the answer must also be multiplied by the out-degree of room 1.

???+ note "Example problem 4: [Joint Provincial Selection 2020 A - Homework](https://loj.ac/p/3304)"
    **Solution** First, use Möbius inversion to reduce the problem to computing the sum of edge weights over all spanning trees. This part is not closely related to this page, so we skip it.
    
    Write each entry of the determinant as $w_ix+1$. The answer is the coefficient of the linear term of the determinant, because the answer is really the sum, over each edge fixed in advance, of the number of spanning trees containing it $\times$ its weight; the edge multiplied by the linear coefficient is the fixed edge. So we can drop all terms of degree higher than one, giving complexity $O(n^3)$.
    
    [Beijing Provincial Selection Training 2019 - Counting Spanning Trees](https://www.luogu.com.cn/problem/P5296) is a more general case: compute the sum of the $k$-th powers of the total weights of spanning trees. Build the determinant entries in a similar way; see the Luogu editorials for details.

???+ note "Example problem 5: [AGC051D C4](https://atcoder.jp/contests/agc051/tasks/agc051_d)"
    **Solution** Counting Eulerian circuits in an undirected graph is #P-complete, but the graph in this problem is simple. Once we decide how many of the $S-T$ edges point from $S$ to $T$, the orientations of the other three edges are determined. Then applying the BEST theorem directly gives an $O(a+b+c+d)$ solution.
