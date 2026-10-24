This page introduces a very important topic in linear algebra: the matrix. It mainly covers the properties and operations of matrices, and some applications of matrix multiplication.

## Vectors and matrices

In linear algebra, vectors are divided into column vectors and row vectors.

???+ warning "Warning"
    In Taiwan, the Chinese translations of "column" and "row" are exactly the opposite of those used in mainland China. **OI Wiki** follows the mainland China convention for the Chinese terms for column and row.

The main objects of study in linear algebra are column vectors, and by convention column vectors are written as bold lowercase letters. In linear algebra, where many vectors and matrices appear, the vector arrow over a letter can be omitted in handwriting as long as it causes no confusion.

A vector is also a special matrix. To denote a row vector, write the transpose symbol at the upper right of the bold lowercase letter. In linear algebra, row vectors usually represent equations.

## Introduction

Matrices come from systems of linear equations. Like vectors, matrices embody the idea of "packing data together and processing it as a whole".

For example, take the system of linear equations:

$$
\begin{equation}
    \begin{cases}
        7x_1+8x_2+9x_3=13 \\
        4x_1+5x_2+6x_3=12 \\
        x_1+2x_2+3x_3=11
    \end{cases}
\end{equation}
$$

Matrices are usually written with parentheses or square brackets. Pull out the coefficients above and write them as a matrix multiplication:

$$
\begin{equation}
    \begin{pmatrix}
        7 & 8 & 9 \\
        4 & 5 & 6 \\
        1 & 2 & 3
    \end{pmatrix}\begin{pmatrix}
        x_1 \\ x_2 \\ x_3
    \end{pmatrix}=\begin{pmatrix}
      13 \\ 12 \\ 11
    \end{pmatrix}
\end{equation}
$$

Written briefly as:

$$
Ax=b
$$

That is, the column vector of unknowns x, multiplied on the left by a matrix A, gives the column vector b. This equation can be seen as the basic form of linear algebra.

The main computational model in linear algebra is the inner product. An inner product multiplies and then adds: a row vector multiplied on the left of a column vector gives a single number.

Matrix multiplication extends the inner product. It takes a row from the left matrix and a column from the right matrix and computes their inner product to get the corresponding entry of the result. The mnemonic is "left row, right column".

When the object of study is the column vector on the right, matrix multiplication means multiplying the column vector on the left. From this left-multiplication point of view, a matrix is a transformation of column vectors: it transforms each column vector of the right matrix in the product, giving the corresponding column vector of the result.

A matrix can transform a single column vector, transform a group of column vectors "packed" together, or even transform the whole space, that is, all column vectors. When a matrix is seen as transforming the whole space, it is detached from the space and becomes a pure transformation.

## Definition

For a matrix $A$, the main diagonal consists of the entries $A_{i,i}$.

$I$ usually denotes the identity matrix, which has 1 on the main diagonal and 0 everywhere else.

### Matrices of the same shape

Two matrices with the same number of rows and the same number of columns are said to have the same shape.

### Square matrices

A matrix whose number of rows equals its number of columns is called a square matrix. A square matrix is a special kind of matrix. The usual phrase "matrix of order $n$" actually means an $n\times n$ square matrix. Square matrices of the same order have the same shape.

General matrices are used when studying systems of equations, sets of vectors and matrix rank. Square matrices are used when studying eigenvalues and eigenvectors, and quadratic forms.

#### Main diagonal

The entries of a square matrix whose row index equals the column index form the main diagonal.

#### Symmetric matrices

If the entries of a square matrix are symmetric about the main diagonal, that is, for any $i$ and $j$ the entry in row $i$, column $j$ equals the entry in row $j$, column $i$, the matrix is called a symmetric matrix.

#### Diagonal matrices

A square matrix whose entries off the main diagonal are all $0$ is called a diagonal matrix, usually written:

$$
\operatorname{diag}\{\lambda_1,\cdots,\lambda_n\}
$$

where $\lambda_1,\cdots,\lambda_n$ are the entries on the main diagonal.

A diagonal matrix is symmetric.

If the diagonal entries of a diagonal matrix are all $1$, it is called the identity matrix, written $I$. Any matrix, of any shape, stays unchanged when multiplied by the identity matrix, as long as the product is defined.

#### Triangular matrices

If all entries below and to the left of the main diagonal of a square matrix are $0$, it is called an upper triangular matrix. If all entries above and to the right of the main diagonal are $0$, it is called a lower triangular matrix.

The product of two upper (lower) triangular matrices is still upper (lower) triangular. If all diagonal entries are non-zero, an upper (lower) triangular matrix is invertible, and its inverse is also upper (lower) triangular.

#### Unit triangular matrices

If an upper triangular matrix $A$ has all $1$ on its diagonal, $A$ is called a unit upper triangular matrix. If a lower triangular matrix $A$ has all $1$ on its diagonal, $A$ is called a unit lower triangular matrix.

The product of two unit upper (lower) triangular matrices is still unit upper (lower) triangular, and the inverse of a unit upper (lower) triangular matrix is also unit upper (lower) triangular.

## Operations

### Linear operations on matrices

The linear operations on matrices are addition, subtraction and scalar multiplication, all done entry by entry. Only matrices of the same shape can be added or subtracted.

### Transpose

The transpose of a matrix is written with the symbol "T" at its upper right, and means swapping the rows and columns of the matrix.

A symmetric matrix is unchanged by transposition.

### Matrix multiplication

Matrix multiplication generalizes the inner product of vectors.

Multiplying two matrices only makes sense when the number of columns of the first matrix equals the number of rows of the second.

Let $A$ be a $P \times M$ matrix and $B$ an $M \times Q$ matrix, and let the matrix $C$ be the product of $A$ and $B$.

Then the entry in row $i$, column $j$ of $C$ is:

$$
C_{i,j} = \sum_{k=1}^MA_{i,k}B_{k,j}
$$

In matrix multiplication, the number in row $i$, column $j$ of the result $C$ is obtained by taking the $M$ numbers in row $i$ of $A$ and the $M$ numbers in column $j$ of $B$, and **multiplying them pairwise and adding up**. This **multiply and add** is exactly the inner product of vectors. The number in row $i$, column $j$ of the product is exactly the inner product of the $i$-th row vector of $A$ and the $j$-th column vector of $B$. The mnemonic is **left row, right column**.

The vectors studied in linear algebra are mostly column vectors. With this definition of matrix multiplication, we often study multiplying a column vector on the left by a matrix. Here we can also see the idea of "packing things together": many inner products of vectors are handled at once.

Matrix multiplication is associative, but in general not commutative.

Using associativity, matrix multiplication can be sped up with the idea of [fast exponentiation](../binary-exponentiation.md).

In contests, since a linear recurrence can be written as a matrix multiplication, fast matrix exponentiation is often used to find a given term of a linear recurrence.

#### Optimization

First, for fairly small matrices, consider unrolling the loops by hand to reduce the constant factor.

We can reorder the loops to improve spatial locality. This does not change the time complexity of matrix multiplication, but gives a constant-factor speedup.

```cpp
// Take the reference code below as an example
mat operator*(const mat& T) const {
  mat res;
  for (int i = 0; i < sz; ++i)
    for (int j = 0; j < sz; ++j)
      for (int k = 0; k < sz; ++k) {
        res.a[i][j] += mul(a[i][k], T.a[k][j]);
        res.a[i][j] %= MOD;
      }
  return res;
}

// is worse than
mat operator*(const mat& T) const {
  mat res;
  int r;
  for (int i = 0; i < sz; ++i)
    for (int k = 0; k < sz; ++k) {
      r = a[i][k];
      for (int j = 0; j < sz; ++j)
        res.a[i][j] += T.a[k][j] * r, res.a[i][j] %= MOD;
    }
  return res;
}
```

### Inverse of a square matrix

The inverse $P$ of a square matrix $A$ is the matrix such that $A \times P = I$.

The inverse does not always exist. If it exists, it can be found with [Gaussian elimination](../numerical/gauss.md).

### Determinant of a square matrix

The determinant is an operation on square matrices.

## Reference code

In general, a matrix can be simulated with a two-dimensional array.

```cpp
struct mat {
  LL a[sz][sz];

  mat() { memset(a, 0, sizeof a); }

  mat operator-(const mat& T) const {
    mat res;
    for (int i = 0; i < sz; ++i)
      for (int j = 0; j < sz; ++j) {
        res.a[i][j] = (a[i][j] - T.a[i][j]) % MOD;
      }
    return res;
  }

  mat operator+(const mat& T) const {
    mat res;
    for (int i = 0; i < sz; ++i)
      for (int j = 0; j < sz; ++j) {
        res.a[i][j] = (a[i][j] + T.a[i][j]) % MOD;
      }
    return res;
  }

  mat operator*(const mat& T) const {
    mat res;
    int r;
    for (int i = 0; i < sz; ++i)
      for (int k = 0; k < sz; ++k) {
        r = a[i][k];
        for (int j = 0; j < sz; ++j)
          res.a[i][j] += T.a[k][j] * r, res.a[i][j] %= MOD;
      }
    return res;
  }

  mat operator^(LL x) const {
    mat res, bas;
    for (int i = 0; i < sz; ++i) res.a[i][i] = 1;
    for (int i = 0; i < sz; ++i)
      for (int j = 0; j < sz; ++j) bas.a[i][j] = a[i][j] % MOD;
    while (x) {
      if (x & 1) res = res * bas;
      bas = bas * bas;
      x >>= 1;
    }
    return res;
  }
};
```

## Two ways to look at a system of linear equations

There are two ways to look at the matrix A, or the transformation A.

The first view: by rows, looking at each row of A. Then A is seen as a system of equations, which leads to solving equations by elimination.

The second view: by columns, looking at each column of A. A itself is made of column vectors. Now the transformation A is seen as a set of column vectors, and x holds the coefficients of the unknowns. The question is whether the column vectors in A, with suitable coefficients, can be combined to produce the column vector b.

For example, the example at the start of the page becomes:

$$
\begin{equation}
    \begin{pmatrix}
        7 \\ 4 \\ 1
    \end{pmatrix}x_1+\begin{pmatrix}
        8 \\ 5 \\ 2
    \end{pmatrix}x_2+\begin{pmatrix}
        9 \\ 6 \\ 3
    \end{pmatrix}x_3=\begin{pmatrix}
      13 \\ 12 \\ 11
    \end{pmatrix}
\end{equation}
$$

Solving the equations becomes the question of whether we can adjust the three coefficients x so that the three given basis vectors combine into the result vector.

The column view is less familiar than the row view. In the column view, we can study linear independence and linear dependence.

## Applications of matrix multiplication

### Speeding up recurrences with matrices

Take the [Fibonacci sequence](../combinatorics/fibonacci.md) as an example. In the Fibonacci sequence, $F_1 = F_2 = 1$ and $F_i = F_{i - 1} + F_{i - 2}(i \geq 3)$.

If a problem asks for the $n$-th Fibonacci number, the simplest way is to compute the recurrence directly. But if $n$ can be as large as $10^{18}$, direct computation is too slow, and we can use matrices to speed up the recurrence.

By the [matrix form of the Fibonacci recurrence](../combinatorics/fibonacci.md#matrix-form):

$$
\begin{bmatrix}
  F_{n-1} & F_{n-2}
\end{bmatrix} \begin{bmatrix}
  1 & 1 \\
  1 & 0
\end{bmatrix} = \begin{bmatrix}
  F_n & F_{n-1}
\end{bmatrix}
$$

Define the initial matrices $\text{ans} = \begin{bmatrix}F_2 & F_1\end{bmatrix} = \begin{bmatrix}1 & 1\end{bmatrix}, \text{base} = \begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}$. Then $F_n$ equals the entry in the first row and first column of the matrix $\text{ans} \text{base}^{n-2}$, that is, the first-row, first-column entry of $\begin{bmatrix}1 & 1\end{bmatrix} \begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}^{n-2}$.

???+ warning "Note"
    Matrix multiplication is not commutative, so it must not be written as the first-row, first-column entry of $\begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}^{n-2} \begin{bmatrix}1 & 1\end{bmatrix}$. Also, for $n \leq 2$, just output $1$ directly; there is no need for fast matrix exponentiation.

Why multiply by the $(n-2)$-th power of $\text{base}$ instead of the $n$-th power? Because $F_1, F_2$ are known without any matrix multiplication. In other words, after just one multiplication we already have $F_3$. If you still don't quite see why the exponent is $n-2$, try working it out by hand.

Below is sample code (the core part) for computing the $n$-th Fibonacci number modulo $10^9+7$.

```cpp
constexpr int mod = 1000000007;

struct Matrix {
  int a[3][3];

  Matrix() { memset(a, 0, sizeof a); }

  Matrix operator*(const Matrix &b) const {
    Matrix res;
    for (int i = 1; i <= 2; ++i)
      for (int j = 1; j <= 2; ++j)
        for (int k = 1; k <= 2; ++k)
          res.a[i][j] = (res.a[i][j] + a[i][k] * b.a[k][j]) % mod;
    return res;
  }
} ans, base;

void init() {
  base.a[1][1] = base.a[1][2] = base.a[2][1] = 1;
  ans.a[1][1] = ans.a[1][2] = 1;
}

void qpow(int b) {
  while (b) {
    if (b & 1) ans = ans * base;
    base = base * base;
    b >>= 1;
  }
}

int main() {
  int n = read();
  if (n <= 2) return puts("1"), 0;
  init();
  qpow(n - 2);
  println(ans.a[1][1] % mod);
}
```

Here is a slightly more complex example.

$$
\begin{gathered}
f_{1} = f_{2} = 0\\
f_{n} = 7f_{n-1}+6f_{n-2}+5n+4\times 3^n
\end{gathered}
$$

We see that $f_n$ depends on $f_{n-1}, f_{n-2}, n$, so we try to build a matrix that describes the state.

But if the matrix holds only these three elements $\begin{bmatrix}f_n& f_{n-1}& n\end{bmatrix}$, it is hard to build the transition, because the power and the $+1$ cannot be described by a matrix.

So we build a larger matrix.

$$
\begin{bmatrix}f_n& f_{n-1}& n& 3^n & 1\end{bmatrix}
$$

We want a recurrence matrix that transforms it into

$$
\begin{bmatrix}
f_{n+1}& f_{n}& n+1& 3^{n+1} & 1
\end{bmatrix}
$$

The transition matrix is

$$
\begin{bmatrix}
7 & 1 & 0 & 0 & 0\\
6 & 0 & 0 & 0 & 0\\
5 & 0 & 1 & 0 & 0\\
12 & 0 & 0 & 3 & 0\\
5 & 0 & 1 & 0 & 1
\end{bmatrix}
$$

### Expressing updates with matrices

???+ note "[THUSCH 2017 Great Magician](https://loj.ac/p/2980)"
    The great magician L has made $n$ magic crystal balls. Each ball has energy values for three attributes: water, fire and earth. L lines up the $n$ balls on the ground from front to back and starts today's magic show.
    
    Let $A_i,\ B_i,\ C_i$ be the water, fire and earth energy of the $i$-th ball from the front (indices start from $1$).
    
    L plans to cast $m$ spells. Each time, he picks a range $[l, r]$ and casts one of the following $7$ spells in $3$ categories:
    
    1.  Magic excitation: in every ball in the range, the energy of a **specific attribute** bursts out and strengthens the energy of another **specific attribute**. Specifically, there are three possible forms:
    
        -   Fire excites water: set $A_i = A_i + B_i$.
        -   Earth excites fire: set $B_i = B_i + C_i$.
        -   Water excites earth: set $C_i = C_i + A_i$.
    
            **Note that strengthening one attribute does not change the energy of the other attribute. For example, $A_i = A_i + B_i$ does not increase or decrease $B_i$.**
    2.  Magic enhancement: L waves his staff and spends $v$ points of his own mana to change the energy of a **specific attribute** of every ball in the range. Specifically, there are three possible forms:
    
        -   Fire energy fixed boost: set $A_i = A_i + v$.
        -   Water energy multiplied boost: set $B_i=B_i \cdot v$.
        -   Earth energy absorption and fusion: set $C_i = v$.
    3.  Magic release: L gathers the energy of all balls in the range and fuses it into a new crystal ball, which he gives to the audience. Each attribute of the new ball equals the sum of the corresponding energies of all balls in the range. **Note that magic release does not actually change the energy of the balls in the range**.
    
    It is worth mentioning that the raw material for the balls L makes and fuses is custom OI-factory crystal, so the balls have an energy threshold of $998244353$. When some attribute's energy in a ball is at least this threshold, it is automatically taken modulo the threshold, which keeps the ball from exploding.
    
    W is L's (only) audience member. W watches the whole show and receives every ball L fuses during it. W wants to know the three attribute energies contained in each of these balls.

Since matrix multiplication is associative and distributive, point updates extend naturally to ranges: after deriving the matrices, simply use a segment tree to maintain the product of matrices over ranges.

Here are a few examples.

The transition for $A_i = A_i + v$

$$
\begin{bmatrix}
A & B & C & 1
\end{bmatrix}
\begin{bmatrix}
1 & 0 & 0 & 0\\
0 & 1 & 0 & 0\\
0 & 0 & 1 & 0\\
v & 0 & 0 & 1\\
\end{bmatrix}=
\begin{bmatrix}
A+v & B & C & 1\\
\end{bmatrix}
$$

The transition for $B_i=B_i \cdot v$

$$
\begin{bmatrix}
A & B & C & 1
\end{bmatrix}
\begin{bmatrix}
1 & 0 & 0 & 0\\
0 & v & 0 & 0\\
0 & 0 & 1 & 0\\
0 & 0 & 0 & 1\\
\end{bmatrix}=
\begin{bmatrix}
A & B \cdot v & C & 1\\
\end{bmatrix}
$$

???+ note "[LibreOJ 6208 Queries on a Tree](https://loj.ac/p/6208)"
    There is a tree with $n$ nodes rooted at node $1$. Each node has two weights $k_i, t_i$, both initially $0$.
    
    There are three operations:
    
    1.  $\operatorname{Add}( x , d )$: for every node on the path from $x$ to the root, set $k_i\leftarrow k_i + d$
    2.  $\operatorname{Mul}( x , d )$: for every node on the path from $x$ to the root, set $t_i\leftarrow t_i + d \times k_i$
    3.  $\operatorname{Query}( x )$: ask for the weight $t_x$ of node $x$
    
        $n,~m \leq 100000, ~-10 \leq d \leq 10$

Thinking about it directly, it is not easy to figure out how to push down tags and maintain the information. But matrices express it easily.

$$
\begin{aligned}
\begin{bmatrix}k & t & 1 \end{bmatrix}
\begin{bmatrix}
1 & 0 & 0 \\
0 & 1 & 0 \\
d & 0 & 1
\end{bmatrix}
&=
\begin{bmatrix}k+d & t & 1 \end{bmatrix}\\
\begin{bmatrix}k & t & 1 \end{bmatrix}
\begin{bmatrix}
1 & d & 0 \\
0 & 1 & 0 \\
0 & 0 & 1
\end{bmatrix}
&=
\begin{bmatrix}k & t+d \times k & 1 \end{bmatrix}
\end{aligned}
$$

### Counting paths of fixed length

???+ note "Problem"
    You are given a directed graph with $n$ vertices where every edge has weight $1$, and an integer $k$. For every pair of vertices $(u,v)$, find the number of paths of length $k$ from $u$ to $v$ (not necessarily simple paths: vertices or edges may be visited more than once).

We represent the directed graph by its adjacency matrix $G$ (for each edge $(u\to v)$ in the graph set $G[u,v]=1$, and set the rest to $0$; if there are multiple edges, set $G[u,v]$ to the number of such edges). The algorithm below also works when the graph has self-loops.

Clearly, this adjacency matrix is the answer for $k=1$.

Suppose we know the matrix of path counts for length $k$, call it $C_k$, and we want $C_{k+1}$. Clearly we have the DP transition

$$
C_{k+1}[i,j] = \sum_{p = 1}^{n} C_k[i,p] \cdot G[p,j]
$$

We can see this as matrix multiplication, so the transition can be written as

$$
C_{k+1} = C_k \cdot G
$$

Unrolling this recurrence gives

$$
C_k = \underbrace{G \cdot G \cdots G}_{k \text{ times}} = G^k
$$

To compute this matrix power, we can use fast exponentiation (binary exponentiation) and get the result in $O(n^3 \log k)$ time.

### Shortest paths of fixed length

???+ note "Problem"
    You are given a weighted directed graph with $n$ vertices and an integer $k$. For each pair of vertices $(u,v)$, find the length of the shortest path from $u$ to $v$ that contains exactly $k$ edges. (Not necessarily a simple path: vertices or edges may be visited more than once.)

Again we build the adjacency matrix $G$ of the graph, where $G[i,j]$ is the weight of the edge from $i$ to $j$. If there is no edge between $i$ and $j$, then $G[i,j]=\infty$. (With multiple edges, take the minimum weight.)

Clearly this matrix is the answer for $k=1$. Again suppose we know the answer for $k$, the matrix $L_k$, and we want the answer for $k+1$. Clearly we have the transition

$$
L_{k+1}[i,j] = \min_{1\le p \le n} \left\{L_k[i,p] + G[p,j]\right\}
$$

In fact this is analogous to matrix multiplication: the transition just replaces the "multiply and sum" of matrix multiplication with "add and take the minimum". So we define this operation as $\odot$, that is

$$
A \odot B = C~~\Longleftrightarrow~~C[i,j]=\min_{1\le p \le n}\left\{A[i,p] + B[p,j]\right\}
$$

So we get

$$
L_{k+1} = L_k \odot G
$$

Unrolling the recurrence gives

$$
L_k = \underbrace{G \odot \ldots \odot G}_{k\text{ times}} = G^{\odot k}
$$

We can still compute this with fast matrix exponentiation, since the operation is clearly associative. The time complexity is $O(n^3 \log k)$.

### Counting paths / shortest paths with bounded length

The algorithms above only work when the number of edges is fixed. But we can improve them to handle paths with at most $k$ edges. Specifically, consider the following problem:

???+ note "Problem"
    You are given a directed graph with $n$ vertices and edge weights $1$, and an integer $k$. For each pair of vertices $(u,v)$, find the number of paths from $u$ to $v$ of length at most $k$ (not necessarily simple paths: vertices or edges may be visited more than once).

For each vertex $v$, add a virtual vertex $v'$ to record the answer, and add the two edges $(v,v')$ and $(v',v')$ to the graph. Then for a pair $(u,v)$, the number of paths from $u$ to $v$ with at most $k$ edges equals the number of paths from $u$ to $v'$ with exactly $k+1$ edges. This is because for every path with $m(m \le k)$ edges $(p_0=u)\to p_1\to p_2 \to \dots \to p_{m-1} \to (p_m=v)$, there is exactly one corresponding path with $k+1$ edges $(p_0=u)\to p_1 \to p_2 \to \dots \to p_{m-1} \to (p_m=v) \to v'  \to \dots \to v'$.

For shortest paths with at most $k$ edges, just add a self-loop of weight $0$ to every vertex.

## Exercises

-   [Luogu P1962 Fibonacci Sequence](https://www.luogu.com.cn/problem/P1962), the example problem above; same as POJ3070
-   [Luogu P1349 Generalized Fibonacci Sequence](https://www.luogu.com.cn/problem/P1349), the $\text{base}$ matrix needs some changes
-   [Luogu P1939 Template: Matrix Acceleration (Sequence)](https://www.luogu.com.cn/problem/P1939), the $\text{base}$ matrix becomes a $3 \times 3$ matrix; the derivation is similar to the one above.

**Parts of this page are translated from the article [Кратчайшие пути фиксированной длины, количества путей фиксированной длины](http://e-maxx.ru/algo/fixed_length_paths) and its English translation [Number of paths of fixed length/Shortest paths of fixed length](https://cp-algorithms.com/graph/fixed_length_paths.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**
