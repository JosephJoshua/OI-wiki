This page introduces random walk problems on graphs. It looks at them from three angles: grid graphs, sparse graphs and general graphs. It presents various methods for solving such problems and compares their strengths and weaknesses on different problems.

## Definition

Given a simple directed graph $G=(V, E)(V=\{v_1, v_2, \cdots, v_{|V|}\})$, a start vertex $s \in V$ and an end vertex $t \in V$, each edge $e=\left(x, y\right)$ has a positive weight $w_e$, such that $\forall x \in V \backslash\left\{t\right\}$, $\sum_{\left(x, y\right) \in E} w_{\left(x, y\right)}=1$, and from every vertex $x$ there is a path to $t$. A token starts at the start vertex. Every second, from its current vertex $x$, it picks the outgoing edge $\left(x, y\right)$ with probability $w_{(x, y)}$ and moves to $y$. It stops when it reaches the end vertex. Find the expected time spent.

In fact, this problem can also be written in matrix form. Define the matrix $P$:

$$
P_{x, y}=
\begin{cases}
w_{(x, y)} & \text{if } (x, y) \in E \text{ and } x \neq t \\
0 & \text{if } (x, y) \notin E \text{ or } x=t \\
\end{cases}
$$

The answer we want is:

$$
\sum_{k \geq 0} k \times\left(P^k\right)_{s, t}
$$

Here $\left(P^k\right)_{s, t}$ is the probability of reaching the end vertex for the first time after exactly $k$ steps. When the graph is finite and every vertex can reach the end vertex, one can prove from the definition of $P$ that all its eigenvalues are less than 1, so the answer always converges.

For convenience, unless stated otherwise, this page uses $n$ for $|V|$ and $m$ for $|E|$.

Also, on this page, a sparse graph means a graph whose number of edges is of the same order as its number of vertices.

## Grid graphs

???+ note "Example problem 1 [Circles of Waiting](https://codeforces.com/problemset/problem/963/E)"
    A token starts at the point $(0,0)$ of the Cartesian plane. Every second it moves randomly. If it is currently at $(x, y)$, then in the next second it moves to $(x-1, y)$ with probability $p_1$, to $(x, y-1)$ with probability $p_2$, to $(x+1, y)$ with probability $p_3$, and to $(x, y+1)$ with probability $p_4$. It is guaranteed that $p_1+p_2+p_3+p_4=1$.
    Find the expected time until it moves to a point whose Euclidean distance from the origin is greater than $R$. $0 \leq R \leq 50$, $p_1, p_2, p_3, p_4>0$, and the answer is taken modulo $10^9+7$.

### Naive approach

Let $f(i, j)$ be the expected time for the token, starting at $(i, j)$, to move to a point whose Euclidean distance from the origin is greater than $R$. The transition is:

$$
f(i, j)=
\begin{cases}
p_1 f(i-1, j) + p_2 f(i, j-1) + p_3 f(i+1, j) + p_4 f(i, j+1) + 1 & i^2 + j^2 \leq R^2 \\
0 & i^2 + j^2 > R^2
\end{cases}
$$

The transitions have no topological order, so we need Gaussian elimination to solve them. The time complexity is $O\left(R^6\right)$, which is too slow for this problem.

### Direct elimination

Notice that most coefficients in the equations to be eliminated are 0. If we only compute on the nonzero positions during elimination, the complexity drops.

Look at the elimination process. Eliminate the equations in order from top to bottom in the coordinate plane, and from left to right within the same row. Color the equations already eliminated yellow, the points adjacent to yellow points green, and the remaining points black, as in the figure below:

![graph-random-walk-1](images/graph-random-walk-1.svg)

Next we eliminate the equation of the next green cell. In this equation, only the variables of the green cells and of the first black cell below it can have nonzero coefficients; and only in the equations of the green cells and of the first black cell below it can the variable of the current cell have a nonzero coefficient.

There are only $O(R)$ green cells, so eliminating one equation takes $O\left(R^2\right)$ time. There are only $O\left(R^2\right)$ equations in total, so the time complexity drops to $O\left(R^4\right)$, which is fast enough for this problem.

### Pivot variable method

There are $O\left(R^2\right)$ equations and variables. If we can shrink the size to $O(R)$, then plain Gaussian elimination will be fast enough.

Make the variable of the leftmost cell in each row a pivot variable; there are $2 R+1$ of them. We try to express the variables of all other cells as linear functions of these pivot variables. Process the columns from left to right. For each cell $(i, j)$ in the current column, $f(i, j), f(i-1, j), f(i, j-1), f(i, j+1)$ are all already known as linear functions of the pivot variables. Rearranging the transition gives:

$$
f(i+1, j)=\frac{f(i, j)-p_1 f(i-1, j)-p_2 f(i, j-1)-p_4 f(i, j+1)-1}{p_3}
$$

This gives $f(i+1, j)$ as a linear function of the pivot variables. If $(i+1, j)$ is already farther than $R$ from the origin in Euclidean distance, we get an equation: $f(i+1, j)=0$. In the end we get $2 R+1$ equations, and we just run Gaussian elimination on them.

In the phase of computing the linear functions of the pivot variables, there are $O\left(R^2\right)$ variables, and computing each one takes $O(R)$ time; after that, the problem size is reduced to $O(R)$. Both parts take $O\left(R^3\right)$ time, so the total time complexity is also $O\left(R^3\right)$, which is fast enough for this problem.

### Comparing the two approaches

Below we compare the two approaches from several angles:

Time complexity: on a grid graph, the worst-case time complexity of the pivot variable method is $O(n \sqrt{n})$ (the worst case is when both the length and width of the grid are about $O(\sqrt{n})$), while the worst-case time complexity of direct elimination is $O\left(n^2\right)$. The pivot variable method is better here.

Precision: for problems that need real-number computation instead of modular arithmetic, direct elimination has better precision than the pivot variable method.

Applicability: the two approaches suit different situations.

When the grid has obstacles, or some edges have probability $0$, the pivot variable method needs one extra pivot variable for each obstacle or zero-probability edge. When there are more than $O(R)$ obstacles or zero-probability edges, the time complexity of the pivot variable method grows, while that of direct elimination stays the same.

However, the pivot variable method can also handle elimination for transitions that are similar to grid transitions, for example $f(i, j)=p_1 f(i+1, j)+p_2 f(i, j+1)+p_3 f(\operatorname{pre}(i, j))+1$, where $\operatorname{pre}(i, j)=(x, y)(x \leq i, y \leq j)$ is given by the problem. The complexity analysis of direct elimination does not apply to this model.

Besides, computing the determinant of the adjacency matrix of a grid graph also cannot use the pivot variable method; only direct elimination can be used to reduce the time complexity.

In summary, each approach has its own strengths, and you need to choose based on the specific problem.

## Sparse graphs

???+ note "Example problem 2 Expected Value"
    Given a simple undirected connected sparse graph $G=(V, E)$, a token starts at $v_1$. Every second, the token picks one of the edges incident to its current vertex uniformly at random and moves along it to the other endpoint. Find the expected time to reach $v_n$. $n \leq 2000$, and the answer is taken modulo $p$, where $p$ is a prime chosen at random in the range $\left[10^9, 1.01 \times 10^9\right]$.

### Background

**Definition 4.1.** Every polynomial $p(λ)$ with $p(A) = 0$ is called an annihilating polynomial of the matrix $A$.

**Definition 4.2.** Let $I_n$ be the $n \times n$ identity matrix. The characteristic polynomial of an $n × n$ matrix $A$ is defined as $p(λ) = \det(λI_n - A)$, where $\det$ is the determinant of a matrix.
It is easy to see that the degree of the characteristic polynomial of an $n \times n$ matrix $A$ is at most $n$.

**Theorem 4.2.** (Cayley–Hamilton theorem) The characteristic polynomial of any matrix is an annihilating polynomial of it.

So the lowest-degree annihilating polynomial of an $n \times n$ matrix also has degree at most $n$.

### Solving the original problem

Note that the expected walking time is $E(t)=\sum_{i\geq0}\Pr[t>i]$. If we can find the probability that the walk has not ended after $i$ steps, summing it over all $i ≥ 0$ gives the answer.

Let $f(i, j)$ be the probability that after $i$ steps the token is at $j$ and has never visited $n$. Then:

$$
f(i,j)=\sum_{(k,j)\in E}\frac{f(i-1,k)}{\deg_k}(j\neq n)
$$

Here $\deg_k$ is the degree of $k$.

The transition of $f$ does not depend on $i$, so one transition can be seen as multiplying by a matrix, that is, $f{i+1}=f_iM$. Since the minimal annihilating polynomial of $M$ has degree at most $n$, the shortest linear recurrence of $f$ has length at most $n$, so the shortest linear recurrence of $\Pr[t>i]=\sum_{j=1}^{n-1}f(i,j)$ also has length at most $n$. We can compute $\Pr[t>0],\Pr[t>1],\cdots,\Pr[t>3n]$ in $O(nm)$ time, then use the *Berlekamp–Massey* algorithm to find the shortest linear recurrence of $\Pr[t > i]$ in $O(n^2)$ time.

Consider the generating function of a linear recurrence sequence $a$ of order $k$. Suppose $a_i=\sum_{j=1}^kc_ja_{i-j}$ for $i ≥ i_0$, and let $A(x)$ and $C(x)$ be the generating functions of $a$ and $c$. Then $A(x)=A(x)C(x)+A_0(x)$, where $A_0(x)$ is determined by the terms with $i < i_0$.

Back to the original problem: since we can find the shortest linear recurrence of $\Pr[t > i]$, we can find $C(x)$ and $A_0(x)$ (defined as in the previous paragraph). Rearranging gives $A(x)=\frac{A_0(x)}{1-C(x)}$. We want $\sum_{i\geq0}[x^i]A(x)$, and it is easy to see this equals $A(1)$, so we just plug in $x = 1$. Since the modulus is a random prime, we can assume the denominator is not $0$.

In this way, we solve the problem in $O(nm+n^2)$ time. If the number of edges of $G$ is of the same order as the number of vertices, the time complexity here can be taken as $O(n^2)$.

## General graphs

???+ note "Example problem 3 Frank"
    Given a simple strongly connected directed graph $G = (V, E)$, for all $1 ≤ s ≤ n$, $1 ≤ t ≤ n$, $s ≠ t$, answer the following question:
    A token starts at $v_s$. Every second, the token picks one of the outgoing edges of its current vertex uniformly at random and moves to the vertex it points to. Find the expected time to reach $v_t$. $3 ≤ n ≤ 400$.

### Analysis and transformation

Let $p_{i, j}$ be the probability that the token at $i$ picks the outgoing edge $(i, j)$ and moves to $j$; in particular, the probability is $0$ if the edge does not exist. Let $f_{i,j}$ be the expected time for a random walk from $i$ to reach $j$; in particular, $f_{i,i} = 0$. When $i ≠ j$, the transition is:

$$
f_{i,j}=1+\sum_{1\leq k\leq n}p_{i,k}f_{k,j}
$$

When $i = j$, let $g_i$ be the expected time for a random walk starting at $i$ to return to $i$ for the first time. Then:

$$
f_{i,i}=1-g_i+\sum_{1\le k\le n}p_{i,k}f_{k,i}
$$

To make this easier to see, we write the transitions in matrix form. Let $P$ be the transition matrix of the graph, $F$ the answer matrix, $I$ the $n \times n$ identity matrix, $J$ the $n \times n$ all-ones matrix, and $G$ the $n \times n$ matrix with $G_{i,i} = g_i$ and $0$ elsewhere. Then:

$$
F=J-G+PF
$$

If we can find $G$, then we only need to solve the equation:

$$
(I − P)F = J − G
$$

### Finding G

**Definition 5.1.** The stationary distribution of an $n \times n$ transition matrix $P$ is an $n$-dimensional vector $π$ with $\sum_{i=1}^{n}\pi_{i}=1$ and $πP = π$. Every entry of $π$ lies in the interval $[0,1]$.

The meaning of the stationary distribution is easy to see. If at some moment the token is at $v_i$ with probability $π_i$, then at every later moment the token still follows this probability distribution. We can find $π$ in $O(n^3)$ time by solving equations with Gaussian elimination. So what is the relationship between $π$ and $G$?

**Theorem 5.1.** For every $1 ≤ i ≤ n$, $π_ig_i = 1$.

???+ note "Proof"
    From $F = J - G + PF$, rearranging gives:
    
    $$
    G = PF + J − F
    $$
    
    Multiplying both sides by $π$ on the left gives:
    
    $$
    πG = πPF + πJ − πF
    $$
    
    By the definition of $π$, $πP = π$, so:
    
    $$
    πG = πJ
    $$
    
    Therefore:
    
    $$
    \pi_ig_i=\sum_{j=1}^n\pi_j=1  
    $$

This proves the theorem.

So by introducing the stationary distribution, we can find $G$ in $O(n^3)$ time.

### Solving the original problem

While solving the equation, we run into a problem: $(I - P)$ is not of full rank, so we cannot solve it by multiplying by the inverse matrix.

**Definition 5.2.** For a directed graph $G = (V,E)$, a directed spanning tree rooted at $r\in V$ is a subgraph $T = (V,A)$ of $G$ such that:

1.  For every $i ≠ r$, the out-degree of $i$ is $1$.
2.  The out-degree of $r$ is $0$.
3.  $T$ contains no cycle.

**Lemma 5.1.** (Matrix-tree theorem for directed graphs) For a directed graph $G$, let $D$ be its out-degree matrix, that is, $D_{i,i} = d_i$ and $D_{i,j} = 0(i ≠ j)$, where $d_i$ is the out-degree of $i$, and let $A$ be its adjacency matrix. Then the number of directed spanning trees rooted at $r$ equals the determinant of $D - A$ with row $r$ and column $r$ removed.

**Theorem 5.2.** For the transition matrix $P$ of a strongly connected graph $G = (V,E)$, the rank of $(I - P)$ is $n - 1$.

???+ note "Proof"
    Multiplying a row of a matrix by a nonzero constant does not change its rank, so we multiply row $i$ of $(I - P)$ by the out-degree of $v_i$ to get a new matrix $L$. We only need to prove that the rank of $L$ is $n - 1$.  
    Since every row of $L$ sums to $0$, summing all column vectors of $L$ gives the zero vector, so these vectors are linearly
    dependent, and the rank of $L$ is not $n$.  
    It is easy to see that $L$ equals the out-degree matrix of $G$ minus its adjacency matrix. By Lemma 5.1, the determinant of $L$ with row $i$ and column $i$ removed
    is the number of directed spanning trees rooted at $v_i$.  
    Since G is strongly connected, the number of directed spanning trees rooted at any vertex is nonzero, so $L$ with row $i$
    and column $i$ removed still has full rank.  
    Adding a column cannot decrease the rank, so after removing row $i$ from $L$, all remaining row vectors are linearly independent. Therefore the rank of $L$ is $n - 1$.  
    Back to the original problem, consider solving the equation from it. For convenience, we write the equation as $AX = B$,
    where $A$ and $B$ are known and we need to find $X$. Since $A$ is not of full rank, there are infinitely many solutions; we first find a particular solution.
    Run Gaussian elimination on $A$ and $B$ together. Reduce the first $n - 1$ rows of $A$ so that only the main diagonal and column $n$ have values,
    and reduce the last row to all $0$, giving the following form:
    
    $$
    \begin{bmatrix}
    1 & 0 & 0 & \cdots & 0 & a_1 \\0&1&0&\cdots&0&a_2\\0&0&1&\cdots&0&a_3\\
    \vdots&\vdots&\vdots&\ddots&\vdots&\vdots
    \\0&0&0&\cdots&1&a_{n-1}\\0&0&0&\cdots&0&0
    \end{bmatrix}
    X=
    \begin{bmatrix}
    b_{1,1}&b_{1,2}&b_{1,3}&\cdots&b_{1,n-1}&b_{1,n}
    \\b_{2,1}&b_{2,2}&b_{2,3}&\cdots&b_{2,n-1}&b_{2,n}
    \\b_{3,1}&b_{3,2}&b_{3,3}&\cdots&b_{3,n-1}&b_{3,n}
    \\\vdots&\vdots&\vdots&\ddots&\vdots&\vdots
    \\b_{n-1,1}&b_{n-1,2}&b_{n-1,3}&\cdots&b_{n-1,n-1}&b_{n-1,n}
    \\0&0&0&\cdots&0&0
    \end{bmatrix}
    $$
    
    Setting $X_{n,i} = 0$, we can solve for a particular solution; call it $Y$. Next we adjust the particular solution into the real solution.  
    Since $X_{n,i} = 0$, by the combinatorial meaning we have $Y_{i,j} = 1 + Y_{j,j} + P_{i,k}X_{k,j}$, and it is easy to get $X_{i,j} = Y_{i,j} - Y_{j,j}$.
    In the end, this problem is solved in $O(n^3)$ time.

## References

1.  A Brief Discussion of Random Walk Problems on Graph Models. IOI2019 China National Candidate Team Papers (pp. 17-26) (in Chinese)
