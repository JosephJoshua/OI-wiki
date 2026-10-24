author: StudyingFather, CCXXXI, Chrogeek, ChungZH, countercurrent-time, Early0v0, Enter-tainer, GavinZhengOI, Great-designer, H-J-Granger, henrytbtrue, HeRaNO, huayucaiji, iamtwz, Ir1d, ksyx, MegaOwIer, NachtgeistW, P-Y-Y, qwqAutomaton, shuzhouliu, shuzhouliu-bot, Siger Young, sshwy, SukkaW, Tiphereth-A, tsentau, WhenMelancholy, Xeonacid, Yukimaikoriya, Zhoier, zyj-111, qute-firefly-26710-zjyjoe-lg-592080

## Introduction

Gaussian elimination is the classic algorithm for solving systems of linear equations. It plays an important role in modern mathematics and is a core part of any linear algebra course.

Gaussian elimination uses elementary row operations to bring the augmented matrix into row echelon form, and then solves the system by back substitution. Gauss–Jordan elimination goes further: it scales each pivot to $1$ and clears all other non-zero entries in the pivot's column, bringing the augmented matrix into reduced row echelon form. The two methods are closely related, but they differ in the elimination steps and in the final form of the matrix.

Besides solving linear systems, Gaussian elimination can also be used to compute determinants, find matrix inverses, and in many other computing and engineering tasks.

## Elimination and the idea behind Gaussian elimination

### Definition

Elimination means expressing one unknown in one equation in terms of another unknown and substituting it into another equation. This removes an unknown and lets you find one value. Alternatively, you can multiply one equation by a constant and add it to another equation, which also removes an unknown. Elimination is mainly used to solve systems of two linear equations in two unknowns.

### Explanation

Example 1: use elimination to solve the system of two linear equations in two unknowns:

$$
\begin{cases}
4x+y&=100 \\
x-y&=100
\end{cases}
$$

Solution: add the two equations to eliminate $y$:

$$
5x = 200
$$

This gives:

$$
x = 40
$$

Substitute $x = 40$ into the second equation:

$$
y = -60
$$

### The core of elimination

The core rules of elimination are:

-   Swapping two equations does not change the solution;

-   Multiplying an equation by a non-zero number $k$ does not change the solution;

-   Adding $k$ times one equation to another does not change the solution.

### The idea of Gaussian elimination

The German mathematician Gauss studied elimination and came to the following conclusions:

-   In elimination, what takes part in the computation and changes is the coefficients of the variables;

-   The variables themselves do not take part in the computation and do not change;

-   The position of a coefficient can stand for its variable, so the variables can be left out;

-   Leaving out the variables during the computation does not change the solution.

Gaussian elimination uses these ideas to bring the augmented matrix of the system into row echelon form with elementary row operations. If some row has all coefficients equal to $0$ but a non-zero constant, the system has no solution. Otherwise, you can choose the free unknowns and find the other unknowns by back substitution, which gives the general solution. If you also clear the non-zero entries above each pivot and scale each pivot to $1$ to get the reduced row echelon form, you are using Gauss–Jordan elimination.

## The five steps of Gauss–Jordan elimination

## Explanation

Below, the process of solving a consistent linear system with Gauss–Jordan elimination is split into five steps:

1.  Reduce the augmented matrix to reduced row echelon form with elementary row operations;

2.  Rewrite it as a linear system;

3.  Solve for the first variable of each equation;

4.  Add the free unknowns;

5.  Write the general solution in column form.

Let us use an example to show how the algorithm works.

## Process

Example 2: solve the linear system using the five steps of Gauss–Jordan elimination:

$$
\begin{cases}
2x_1+5x_3+6x_4&=9 \\
x_3+x_4&=-4 \\
2x_3+2x_4&=-8
\end{cases}
$$

### Reduce the augmented matrix to reduced row echelon form

The augmented matrix is the new matrix formed by joining the coefficient matrix $A$ of the system with the constant column $b$, written $(A | b)$. With the augmented matrix, the variables can be left out and represented by the positions of their coefficients. Below we use Gauss–Jordan elimination to bring the augmented matrix into reduced row echelon form. The vertical bar in the augmented matrix separates the coefficient matrix from the constant column and plays the role of the equals sign.

$$
\left(\begin{matrix}
2 & 0 & 5 & 6 \\
0 & 0 & 1 & 1 \\
0 & 0 & 2 & 2
\end{matrix} \middle|
\begin{matrix}
9 \\
-4 \\
-8
\end{matrix} \right)
$$

$$
\xrightarrow{r_3-2r_2}
\left(\begin{matrix}
2 & 0 & 5 & 6 \\
0 & 0 & 1 & 1 \\
0 & 0 & 0 & 0
\end{matrix} \middle|
\begin{matrix}
9 \\
-4 \\
0
\end{matrix} \right)
$$

This is now in row echelon form.

$$
\xrightarrow{\frac{r_1}{2}}
\left(\begin{matrix}
1 & 0 & 2.5 & 3 \\
0 & 0 & 1 & 1 \\
0 & 0 & 0 & 0
\end{matrix} \middle|
\begin{matrix}
4.5 \\
-4 \\
0
\end{matrix} \right)
$$

$$
\xrightarrow{r_1-r_2 \times 2.5}
\left(\begin{matrix}
1 & 0 & 0 & 0.5 \\
0 & 0 & 1 & 1 \\
0 & 0 & 0 & 0
\end{matrix} \middle|
\begin{matrix}
14.5 \\
-4 \\
0
\end{matrix} \right)
$$

This is now in reduced row echelon form.

### Rewrite as a linear system

$$
\begin{cases}
x_1+0.5x_4 &= 14.5\\
x_3+x_4 &= -4 \\
\end{cases}
$$

???+ note "Explanation"
    Rewriting as a linear system means taking the reduced row echelon form and writing it back as linear equations: give each coefficient back its variable, and turn the vertical bar back into an equals sign.

### Solve for the first variable

$$
\begin{cases}
x_1 = -0.5x_4+14.5\notag \\
x_3 = -x_4-4\notag
\end{cases}
$$

???+ note "Explanation"
    For the rewritten system, express the first variable of each equation in terms of the other quantities. Here these are $x_1$ and $x_3$, the first variables of the two equations.

### Add the free unknowns

$$
\begin{cases}
x_1 = -0.5x_4+14.5 \\
x_2 = x_2 \\
x_3 = -x_4-4 \\
x_4 = x_4
\end{cases}
$$

???+ note "Explanation"
    Step 3 solved for $x_1$ and $x_3$. This shows that the remaining variables $x_2$ and $x_4$ are not constrained by the system. They are free unknowns and can take any value, so we add them to the solution from step 3 as $x_2 = x_2,x_4 = x_4$. This way of adding them matches the definition of a free unknown and is easy to understand: since a free unknown is not constrained, it can only be equal to itself.

### Write the general solution in column form

$$
\begin{aligned}
\begin{pmatrix} x_1 \\ x_2 \\ x_3 \\ x_4 \end{pmatrix} &=
\begin{pmatrix} 0 \\ 1 \\ 0 \\ 0 \end{pmatrix} x_2+
\begin{pmatrix} -0.5 \\ 0 \\ -1 \\ 1 \end{pmatrix} x_4 +
\begin{pmatrix} 14.5 \\ 0 \\ -4 \\ 0 \end{pmatrix} \\
&= \begin{pmatrix} 0 \\ 1 \\ 0 \\ 0 \end{pmatrix} C_1+
\begin{pmatrix} -0.5 \\ 0 \\ -1 \\ 1 \end{pmatrix} C_2 +
\begin{pmatrix} 14.5 \\ 0 \\ -4 \\ 0 \end{pmatrix}
\end{aligned}
$$

where $C_1$ and $C_2$ are arbitrary constants.

???+ note "Explanation"
    Starting from step 4, write the solution as a combination of column vectors. Since $x_2$ and $x_4$ are free unknowns and can take any value, replace them on the right-hand side with arbitrary constants $C_1$ and $C_2$. This completes the solution of the system.

## Computing determinants

### Explanation

The determinant of an $N \times N$ square matrix can be thought of as the signed volume of the shape spanned by its column vectors.

For example:

$$
\begin{vmatrix}
1 & 0 \\
0 & 1 \end{vmatrix} = 1
$$

$$
\begin{vmatrix}
1 & 2 \\
2 & 1 \end{vmatrix} = -3
$$

The determinant is given by the formula

$$
\operatorname{det}(A)=\sum_{\sigma \in S_{n}} \operatorname{sgn}(\sigma) \prod_{i=1}^{n} a_{i, \sigma(i)}
$$

where $S_n$ is the set of all permutations of length $n$ and $\sigma$ is one permutation. If the number of inversions of $\sigma$ is even, then $\operatorname{sgn}(\sigma)=1$; otherwise $\operatorname{sgn}(\sigma)=−1$.

Thinking in terms of volume is a very simple way to understand how the determinant behaves:

-   Transposing a matrix does not change the determinant;

-   Swapping two rows (columns) negates the determinant;

-   Adding one row (column) to another or subtracting it does not change the determinant;

-   Multiplying every entry of a row (column) by a number $k$ scales the determinant by $k$.

So if we apply Gaussian elimination to a matrix, using only row swaps and adding a multiple of one row to another, we get an upper triangular matrix whose determinant is the product of its diagonal entries. The sign is determined by the number of row swaps (if it is odd, flip the sign of the determinant). Therefore we can compute the determinant with Gaussian elimination in $O(n^3)$ time.

Note that if at some point we cannot find a non-zero entry in the current column, the algorithm should stop and return 0.

??? note "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/numerical/gauss/gauss_1.cpp:core"
    ```

## Matrix inverse

For a square matrix $A$, if there is a square matrix $A^{-1}$ such that $A \times A^{-1} = A^{-1} \times A = I$, then $A$ is invertible and $A^{-1}$ is its inverse.

Given an $n \times n$ matrix $A$, find its inverse as follows:

1.  Build the $n \times 2n$ matrix $(A, I_n)$;
2.  Use Gauss–Jordan elimination to reduce it to reduced row echelon form $(I_n, A^{-1})$, which gives the inverse $A^{-1}$ of $A$. If the left half of the final reduced row echelon form is not the identity matrix $I_n$, then $A$ is not invertible.

Proving this method correct needs a fair amount of linear algebra, so we leave it out here. Interested readers can look it up.

## Extended Gaussian elimination

Let $A$ be an $m \times n$ matrix over a field $\mathbb{F}$. As with the matrix inverse, build the $m \times (m+n)$ matrix $(A \mid I_m)$. If $B$ is the result of Gaussian elimination on $A$, then

$$
(A \mid I_m) \longrightarrow (B \mid X), \qquad B = XA.
$$

Here the invertible $m \times m$ matrix $X$ records the row operations done during elimination. Some sources[^shoup] call this **extended Gaussian elimination**. When $A$ is an invertible square matrix and $B = I_n$, we have $X = A^{-1}$.

Let $r = \operatorname{rank}(A)$. Then the first $r$ rows of $B$ are non-zero and the last $m-r$ rows are all $0$. Using $B$ and $X$, we can find a basis of both the right kernel and the left kernel of $A$ at the same time.

The **right kernel** of $A$ is the solution space of the homogeneous system $Av = 0$, where $v \in \mathbb{F}^n$ is a column vector. Since $X$ is invertible, $Av = 0$ is equivalent to $Bv = 0$, so we can read off a basis of the right kernel directly.

Let the pivot columns of $B$ be $p_1, p_2, \ldots, p_r$ in order, and the non-pivot columns (corresponding to free unknowns) be $q_1, q_2, \ldots, q_{n-r}$. For each $1 \le j \le n-r$, set the $q_j$-th unknown to $1$ and the other free unknowns to $0$. This gives a solution vector $v^{(j)}$:

$$
v^{(j)}_{q_k} = \begin{cases}
1, & k = j, \\
0, & k \ne j,
\end{cases}
\qquad
v^{(j)}_{p_i} = -B_{i,q_j} \quad (1 \le i \le r).
$$

These vectors are linearly independent and span the whole right kernel, so $v^{(1)}, \ldots, v^{(n-r)}$ form a basis of the right kernel, and the right kernel has dimension $n-r$.[^mit-nullspace]

The **left kernel** of $A$ is the space of column vectors $u \in \mathbb{F}^m$ with $u^TA = 0$, which is the right kernel of $A^T$. Let $X_{i,*}$ be row $i$ of $X$. From $B = XA$, for every $r < i \le m$ we have

$$
X_{i,*} A = B_{i,*} = 0.
$$

So the last $m-r$ rows of $X$, transposed, all lie in the left kernel of $A$. Also, the rows of $X$ are linearly independent and the left kernel has dimension $m-r$, so these transposed rows form exactly a basis of the left kernel[^shoup][^mit-left-nullspace].

Also, if you only need the left kernel, it is enough to reduce $A$ to row echelon form.

## Solving XOR systems with Gauss–Jordan elimination

A system of XOR equations is a system of the form

$$
\begin{cases}
a_{1,1}x_1 \oplus a_{1,2}x_2 \oplus \cdots \oplus a_{1,n}x_n &= b_1\\
a_{2,1}x_1 \oplus a_{2,2}x_2 \oplus \cdots \oplus a_{2,n}x_n &= b_2\\
\cdots &\cdots \\ a_{m,1}x_1 \oplus a_{m,2}x_2 \oplus \cdots \oplus a_{m,n}x_n &= b_m
\end{cases}
$$

where $\oplus$ means "bitwise XOR" (that is, `xor`, or `^` in C++), and all coefficients and constants ($a_{i,j}$ and $b_i$) are $0$ or $1$.

Since XOR is commutative and associative, we can solve the system step by step with Gaussian elimination. Note that during elimination we should "eliminate by XOR" instead of "eliminate by adding/subtracting", and we never need to multiply or divide to change coefficients (because all coefficients are $0$ or $1$).

The augmented matrix of an XOR system is a $01$ matrix (it contains only $0$ and $1$), so we can speed things up with C++'s `std::bitset`, bringing the time complexity down to $O(\dfrac{n^2m}{\omega})$, where $n$ is the number of unknowns, $m$ is the number of equations, and $\omega$ is usually $32$ (it depends on the machine).

??? note "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/numerical/gauss/gauss_2.cpp:core"
    ```

## Exercises

-   [Codeforces - Wizards and Bets](http://codeforces.com/contest/167/problem/E)
-   [Luogu - SDOI2010 Alien Millipedes](https://www.luogu.com.cn/problem/P2447)

## References and notes

[^shoup]: Victor Shoup.[A Computational Introduction to Number Theory and Algebra](https://www.shoup.net/ntb/ntb-v1.pdf). Cambridge University Press, 2005.

[^mit-nullspace]: MIT OpenCourseWare.[Solving Ax = 0: Pivot Variables, Special Solutions](https://ocw.mit.edu/courses/18-06sc-linear-algebra-fall-2011/dddb31dfe72d2e2e2fd09e74713b7775_MIT18_06SCF11_Ses1.7sum.pdf#page=2). 18.06SC Linear Algebra, Fall 2011.

[^mit-left-nullspace]: MIT OpenCourseWare.[The Four Fundamental Subspaces](https://ocw.mit.edu/courses/18-06sc-linear-algebra-fall-2011/62a9db9eeab190694d40afe4734068ca_MIT18_06SCF11_Ses1.10sum.pdf#page=2). 18.06SC Linear Algebra, Fall 2011.
