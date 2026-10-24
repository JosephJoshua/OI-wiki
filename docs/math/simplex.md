Prerequisites: [Linear programming basics](./linear-programming.md)

## Introduction

In competitive programming, the simplex method is often used to solve linear programming problems. However, most linear programs that come up in contests have a more special structure and can often be turned into network flow problems. So the simplex method is not used much, and it is less efficient than algorithms designed specifically for network flow.

## Basic concepts

Suppose we want to solve the following linear program in [standard form](./linear-programming.md#standard-form) with $n$ decision variables and $m+n$ constraints:

$$
\begin{aligned}
\min_{x}\; & z = c^Tx \\
\text{subject to }& Ax = b, \\
& x \ge 0.
\end{aligned}
$$

We may assume that the system of linear equations given by these $m$ equality constraints has a solution and that $A$ has full rank. Then $\operatorname{rank}A = m \le n$.

### An example

Before describing the steps of the simplex method precisely, this section first looks at a concrete example to make it easier to understand.

???+ example "Example"
    Consider the linear program
    
    $$
    \begin{aligned}
    \max\; & 10 x_1 + 12 x_2 + 12 x_3 \\
    \text{subject to } & x_1 + 2 x_2 + 2x_3 \le 20, \\
    & 2x_1 + x_2 + 2x_3 \le 20, \\
    & 2x_1 + 2x_2 + x_3 \le 20,\\
    & x_1,x_2,x_3 \ge 0.
    \end{aligned}
    $$
    
    Adding slack variables gives its standard form:
    
    $$
    \begin{aligned}
    \min\; & -10 x_1 - 12 x_2 - 12 x_3 \\
    \text{subject to } & x_1 + 2 x_2 + 2x_3 + x_4 = 20, \\
    & 2x_1 + x_2 + 2x_3 + x_5 = 20, \\
    & 2x_1 + 2x_2 + x_3 + x_6 = 20,\\
    & x_1,x_2,x_3,x_4,x_5,x_6 \ge 0.
    \end{aligned}
    $$
    
    Look at the equality constraints of this problem. They actually express the variables $x_4,x_5,x_6$ in terms of the variables $x_1,x_2,x_3$. Rearranging the original problem a little gives
    
    $$
    \begin{array}{rrrrrr}
    \min_{x_i\ge 0}  &  z  = &  0 &  -10x_1 &  -12x_2 &  -12x_3\;\\
    \text{subject to}& x_4 = & 20 &    -x_1 &   -2x_2 &   -2x_3, \\
                & x_5 = & 20 &   -2x_1 &    -x_2 &   -2x_3, \\
                & x_6 = & 20 &   -2x_1 &   -2x_2 &    -x_3. \\
    \end{array}
    $$
    
    From this form we can clearly see that setting $x_1=x_2=x_3=0$ gives a feasible solution of the original problem
    
    $$
    x = (0,0,0,20,20,20)^T.
    $$
    
    and its value is $z=0$. For convenience, call the variables set to zero, $x_1,x_2,x_3$, non-basic variables, and the remaining variables $x_4,x_5,x_6$ basic variables.
    
    This feasible solution is clearly not optimal. As long as we increase $x_1,x_2,x_3$ by suitable amounts so that $x_4,x_5,x_6$ stay non-negative, the solution stays feasible. Moreover, since the coefficients of $x_1,x_2,x_3$ in the objective function are all strictly negative, increasing them will definitely decrease the objective value. For example, we can choose to increase $x_1$. To decrease the objective as much as possible, we want to increase $x_1$ as much as possible. But to keep the solution feasible, we must keep $x_4,x_5,x_6\ge 0$. So $x_1$ can be increased to at most
    
    $$
    \min\left\{\dfrac{20}{1},\dfrac{20}{2},\dfrac{20}{2}\right\} = 10.
    $$
    
    The feasible solution then becomes
    
    $$
    x = (10,0,0,10,0,0)^T.
    $$
    
    Since $x_1$ has become a basic variable, to get back to the initial situation (three basic variables expressed in terms of three non-basic variables), we need to choose a new non-basic variable. Since $x_5$ and $x_6$ are both zero, either one can be chosen as the non-basic variable and set to zero. Let us choose $x_5$. Then, substituting
    
    $$
    x_1 = 10 - 0.5x_5 - 0.5x_2 - x_3
    $$
    
    into the original problem, we can rewrite it as
    
    $$
    \begin{array}{rrrrrr}
    \min_{x_i\ge 0}  &   z = &-100&   +5x_5 &   -7x_2 &   -2x_3\;\\
    \text{subject to}& x_4 = & 10 & +0.5x_5 & -1.5x_2 &    -x_3, \\
                & x_1 = & 10 & -0.5x_5 & -0.5x_2 &    -x_3, \\
                & x_6 = &  0 &    +x_5 &    -x_2 &    +x_3. \\
    \end{array}
    $$
    
    This brings us back to the initial situation.
    
    Keep looking at the current objective function. The coefficient of the non-basic variable $x_3$ is still negative, so we can consider increasing $x_3$. To keep $x_4,x_1,x_6\ge 0$, the variable $x_3$ can be increased to at most
    
    $$
    \min\left\{\dfrac{10}{1},\dfrac{10}{1}\right\} = 10.
    $$
    
    Note that since the coefficient of $x_3$ in the expression for $x_6$ is positive, no matter how much we increase $x_3$, $x_6$ will never become negative. That is why the braces contain only two terms this time. When $x_3$ is increased to $10$, both $x_1$ and $x_4$ become zero, so either one can be chosen as the new non-basic variable. Let us choose $x_4$. Then substituting
    
    $$
    x_3 = 10 + 0.5x_5 - 1.5x_2 - x_4
    $$
    
    into the problem above transforms it into
    
    $$
    \begin{array}{rrrrrr}
    \min_{x_i\ge 0}  &   z = &-120&   +4x_5 &   -4x_2 &   +2x_4\;\\
    \text{subject to}& x_3 = & 10 & +0.5x_5 & -1.5x_2 &    -x_4, \\
                & x_1 = &  0 &    -x_5 &    +x_2 &    +x_4, \\
                & x_6 = & 10 & +1.5x_5 & -2.5x_2 &    -x_4. \\
    \end{array}
    $$
    
    Just substituting $x_5=x_2=x_4=0$, we can read off from this form that the current feasible solution is
    
    $$
    x = (0,0,10,0,0,10)^T,
    $$
    
    and its value is $z=-120$.
    
    Repeat the previous step. Since the coefficient of $x_2$ is negative, we can increase it; but to keep $x_3,x_6$ non-negative, it can only go up to
    
    $$
    \min\left\{\dfrac{10}{1.5},\dfrac{10}{2.5}\right\} = 4.
    $$
    
    Since the minimum in the braces comes from the expression for $x_6$, $x_6$ becomes zero when $x_2=4$. Substituting the expression
    
    $$
    x_2 = 4 + 0.6x_5 - 0.4x_6 - 0.4x_4
    $$
    
    into the problem above, we can rewrite the original problem as
    
    $$
    \begin{array}{rrrrrr}
    \min_{x_i\ge 0}  &   z = &-136& +1.6x_5 & +1.6x_6 & +3.6x_4\;\\
    \text{subject to}& x_3 = &  4 & -0.4x_5 & +0.6x_6 & -0.4x_4, \\
                & x_1 = &  4 & -0.4x_5 & -0.4x_6 & +0.6x_4, \\
                & x_2 = &  4 & +0.6x_5 & -0.4x_6 & -0.4x_4. \\
    \end{array}
    $$
    
    Again setting the non-basic variables $x_5,x_6,x_4$ to zero gives the current feasible solution
    
    $$
    x = (4,4,4,0,0,0)^T.
    $$
    
    with value $z=-136$.
    
    Since all the coefficients of the non-basic variables in the objective function are positive, the process described above cannot improve the objective any further, so the current feasible solution is optimal. The algorithm terminates.

In this example, the algorithm starts from a feasible solution and keeps improving the objective function until no further improvement is possible. This is the basic idea of the simplex method.

### Basic feasible solutions

Since $A$ has full rank, we can always choose a subset $B\subseteq\{1,2,\cdots,n\}$ of size $m$ such that $A_B$ is an invertible square matrix. Then $x_B$ can be expressed in terms of the remaining variables $x_N$:

$$
x_B = A_B^{-1}b - A_B^{-1}A_Nx_N.
$$

Here $N=\{1,2,\cdots,n\}\setminus B$. The matrices $A_B,A_N$ are the submatrices of $A$ made of the columns with indices $i\in B$ and $i\in N$ respectively, and the vectors $x_B,x_N$ are the subvectors of $x$ made of the components with indices $i\in B$ and $i\in N$ respectively. If $i\in B$, $x_i$ is called a **basic variable**; otherwise, $x_i$ is called a **non-basic variable**. The set of all basic variables is called a **basis**, and in this article we denote a basis by its index set $B$.

???+ tip "\"Basis\""
    The name "basis" can be understood from the point of view of linear algebra. Let $V$ be the linear space spanned by all the column vectors of $A$. Then the column vectors corresponding to the basis $B$ form a basis of the space $V$.

In the expression for the basic variables $x_B$, setting $x_N=0$ gives a solution of all the equality constraints[^notation]

$$
x = (x_B,x_N) = (A_B^{-1}b,0).
$$

A solution obtained this way is called a **basic solution** of the linear program. If it also satisfies all the non-negativity constraints, i.e. $x\ge 0$, then it is also a feasible solution of the original problem, called a **basic feasible solution** (BFS). During the iterations of the simplex method, the current solution must always be a basic feasible solution.

### Pivoting

Each iteration of the simplex method is called a **pivot** (pivoting). In terms of the result, each pivot removes an old basic variable and adds a new one, which improves the objective value.

???+ tip "\"Pivot\""
    The name "pivot" can also be understood from linear algebra. As mentioned above, the column vectors of the basis $B$ form a basis of the space $V$, and so they correspond to a set of coordinate axes of $V$ in the representation given by that basis. So pivoting is the process of rotating one coordinate axis to a new position.

To decide which basic variable to add, we can write the objective function in terms of the non-basic variables as

$$
\begin{aligned}
c^Tx &= c^T_Bx_B + c^T_Nx_N \\
&= c_B^TA_B^{-1}b + (c_N^T - c_B^TA_B^{-1}A_N)x_N.
\end{aligned}
$$

Setting $x_N=0$ gives the objective value at the current basic feasible solution, $z=c_B^TA_B^{-1}b$. The coefficients of the second term give how the objective changes when $x_N$ changes:

$$
\tilde c_N = \dfrac{\partial z}{\partial x_N} = c_N - A_N^T(A_B^{-1})^Tc_B.
$$

Note that $c_B - A_B^T(A_B^{-1})^Tc_B = 0$, so we can call the vector

$$
\tilde c = (\tilde c_B^T,\tilde c_N^T)^T = c - A^T(A_B^{-1})^Tc_B
$$

the **reduced cost** of the linear program at the basic feasible solution $x$. A component $\tilde c_i<0$ means that increasing the variable $x_i$ improves the objective of the original problem. Such a variable can only be a non-basic variable, and it is called the **entering variable** of this pivot, because after the pivot $x_i$ becomes a basic variable and is no longer fixed at zero (though it may still equal zero).

After choosing the entering variable, we also need to choose an old basic variable to remove. For this, we just need to find which current basic variable becomes zero first as $x_i$ increases. Substituting $x_N=(x_i,x_{N\setminus\{i\}})=(x_i,0)$ into the expression for $x_B$ gives

$$
x_B = A_B^{-1}b - A_B^{-1}A_ix_i.
$$

So the maximum amount by which $x_i$ can increase is

$$
\theta = \min\left\{\dfrac{(A_B^{-1}b)_j}{(A_B^{-1}A_i)_j}:(A_B^{-1}A_i)_j>0\right\}.
$$

The variable that becomes zero first is the basic variable $x_{B_j}$ whose index $j$ attains the minimum in this expression. It is the "bottleneck" when increasing $x_i$: increasing $x_i$ any further would make $x_{B_j}$ negative. This variable is the **leaving variable** of this pivot. The method for finding the leaving variable is called the **minimum ratio test**.

Let the entering variable be $x_i$ and the leaving variable be $x_{i'}$. After the pivot, the basic variables are $x_{B\setminus\{i'\}\cup\{i\}}$ and the non-basic variables are $x_{N\setminus\{i\}\cup\{i'\}}$.

### Termination conditions

The simplex method starts from a basic feasible solution and keeps pivoting. The discussion of pivoting in the previous section is not complete; it ignores some special cases. Some special cases mean the algorithm terminates, and others need extra handling.

First, an entering variable may not exist, i.e. $\tilde c\ge 0$. Then there is no way to improve the objective value further, which means the current basic feasible solution is optimal, and the algorithm terminates. A rigorous proof uses the [complementary slackness conditions](./linear-programming.md#complementary-slackness). Let $y=(A_B^{-1})^Tc_B$. Note that throughout the algorithm, $x$ is always a feasible solution and complementary slackness always holds, that is,

$$
x^T(c-A^Ty) = \tilde c^Tx = \tilde c_B^Tx_B + \tilde c_N^Tx_N = 0.
$$

So as long as $y$ is a feasible solution of the dual problem, i.e. $A^Ty\le c$, we can conclude that $x$ and $y$ are optimal solutions of the primal and dual problems respectively. This condition is exactly $\tilde c\ge 0$, i.e. there is no entering variable.

???+ tip "\"Shadow price\""
    The vector $y=(A_B^{-1})^Tc_B$ is often called the **dual vector**. When the basic feasible solution for $B$ is an optimal solution of the primal problem, the vector $y$ is an optimal solution of the dual problem. So when the simplex method finds an optimal solution of the primal problem, it also gets an optimal solution of the dual problem. Since the vector $y$ is the partial derivative of the current value with respect to the constraint constants, i.e.
    
    $$
    \dfrac{\partial(c^Tx)}{\partial b} = (A_B^{-1})^Tc_B = y,
    $$
    
    it is also called the **shadow price**.

Second, a leaving variable may not exist, i.e. $A_B^{-1}A_i\le 0$. Then the pivot has no "bottleneck": we can keep improving the objective by increasing $x_i$, sending it to $-\infty$. This means the given linear program is unbounded, and the algorithm terminates.

Finally, the choice of entering and leaving variables may not be unique. A poor choice can cause too many pivots, or even make the algorithm cycle and never terminate. Handling this is a bit more involved; we need some [pivot rules](#pivot-rules) to prevent cycling and reduce the number of pivots.

### Simplex tableau

When implementing pivoting, we only need to maintain the coefficient matrix of the linear program after each pivot:

$$
\tilde T_B = 
\begin{pmatrix}
-z_B & \tilde c^T_N \\
x_B & A_B^{-1}A_N
\end{pmatrix}
=
\begin{pmatrix}
-c_B^TA_B^{-1}b & c_N^T - c_B^TA_B^{-1}A_N \\
A_B^{-1}b & A_B^{-1}A_N 
\end{pmatrix}.
$$

It corresponds to the linear program:

$$
\begin{array}{rrrr}
\min_{x\ge 0}    &       & c_B^TA_B^{-1}b & + \tilde c_N^Tx_N\; \\
\text{subject to}& x_B = & A_B^{-1}b      & - A_B^{-1}A_Nx_N.
\end{array}
$$

The matrix $\tilde T_B$ is called the **condensed simplex tableau** of the linear program with respect to the basis $B$. The top-left entry $(\tilde T_B)_{00}$ is (the negative of) the value of the current solution. The entry $(\tilde T_B)_{0i}$ in row $0$, column $i$ is the reduced cost of the $i$-th non-basic variable $x_{N_i}$. The entry $(\tilde T_B)_{j0}$ in row $j$, column $0$ is the value of the $j$-th basic variable $x_{B_j}$. And $A_B^{-1}A_N$ holds the coefficients of the expressions for the basic variables $x_B$ in terms of the non-basic variables $x_N$.

It is easy to see that all the information needed for pivoting can be read directly from the condensed simplex tableau. Specifically, with the condensed simplex tableau, one pivot consists of the following steps:

1.  Choose a column $i=1,\cdots,n-m$ with $(\tilde T_B)_{0i}<0$. If no such $i$ exists, the current solution is optimal and $-(\tilde T_B)_{00}$ is the optimal value.
2.  Choose a row $j=1,\cdots,m$ with $(\tilde T_B)_{ji}>0$ that minimizes $(\tilde T_B)_{j0}/(\tilde T_B)_{ji}$. If no such $j$ exists, the problem is unbounded.
3.  Let the variable $x_{N_i}$ enter the basis and $x_{B_j}$ leave it, and update the simplex tableau.

Now let us look at how exactly to update the simplex tableau. Before the update, row $j$ represents the equation

$$
x_{B_j} = (\tilde T_B)_{j0} - \sum_{i=1}^{n-m}(\tilde T_B)_{ji}x_{N_i}.
$$

To update the tableau, we need to express $x_{N_i}$ in terms of $x_{N\setminus\{N_i\}\cup\{B_j\}}$, that is:

$$
x_{N_i} = \dfrac{(\tilde T_B)_{j0}}{(\tilde T_B)_{ji}} - \dfrac{1}{(\tilde T_B)_{ji}}x_{B_j} - \sum_{i'\neq i}\dfrac{(\tilde T_B)_{ji'}}{(\tilde T_B)_{ji}}x_{N_{i'}}.
$$

Substituting this into the other equations gives

$$
x_{B_{j'}} = \left((\tilde T_B)_{j'0} - (\tilde T_B)_{j'i}\dfrac{(\tilde T_B)_{j0}}{(\tilde T_B)_{ji}}\right) + \dfrac{(\tilde T_B)_{j'i}}{(\tilde T_B)_{ji}}x_{B_j} - \sum_{i'\neq i}\left((\tilde T_B)_{j'i'}-(\tilde T_B)_{j'i}\dfrac{(\tilde T_B)_{ji'}}{(\tilde T_B)_{ji}}\right)x_{N_{i'}}.
$$

Row $0$ is similar, except that the left-hand side becomes $-z_B$. Although the formula looks complicated, the implementation takes only two steps:

1.  Update row $j$: let $\alpha=(\tilde T_B)_{ji}$, set the entry in column $i$ to $1$, then divide every entry in the row by $\alpha$;
2.  Update each row $j'\neq j$: let $\beta=(\tilde T_B)_{j'i}$, set the entry in column $i$ to $0$, then subtract $\beta$ times row $j$ from the whole row.

???+ tip "\"Simplex tableau\""
    The **simplex tableau** is the matrix
    
    $$
    T_B = 
    \begin{pmatrix}
    -z_B & \tilde c^T \\
    x_B & A_B^{-1}A 
    \end{pmatrix}
    =
    \begin{pmatrix}
    -c_B^TA_B^{-1}b & c^T - c_B^TA_B^{-1}A \\
    A_B^{-1}b & A_B^{-1}A 
    \end{pmatrix}.
    $$
    
    Compared with the condensed simplex tableau, it has $m$ extra columns, one for each of the $m$ basic variables. Moreover, the column for the $j$-th basic variable is always $e_j$, the vector that is $1$ in row $j$ and $0$ in every other row. Since these columns carry no extra information, implementations of the simplex method usually leave them out, which gives the condensed simplex tableau.
    
    The simplex tableau makes the update steps easier to understand. Every simplex tableau $T_B$ can be obtained from the same matrix $T_0$ by left-multiplying by an invertible matrix $L_B$ that depends on the basis, that is,
    
    $$
    T_B=
    \begin{pmatrix}
    -c_B^TA_B^{-1}b & c^T - c_B^TA_B^{-1}A \\
    A_B^{-1}b & A_B^{-1}A 
    \end{pmatrix}
    =
    \begin{pmatrix}
    1 & -c_B^TA_B^{-1} \\
    O & A_B^{-1}
    \end{pmatrix}
    \begin{pmatrix}
    0 & c^T \\
    b & A 
    \end{pmatrix}=L_BT_0,
    $$
    
    so these simplex tableaux and $T_0$ can be transformed into each other by a number of [elementary row operations](./linear-algebra/elementary-operations.md). So when updating the simplex tableau, we only need to apply elementary row operations that turn the column of the entering variable into $e_j$. Carrying these operations over to the condensed simplex tableau gives exactly the steps above.

A reference implementation for updating the condensed simplex tableau is as follows:

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/simplex/simplex_0.cpp:pivot"
    ```

From this implementation, one update of the simplex tableau takes $O(mn)$ time. When we discuss [pivot rules](#pivot-rules) later, we will see that finding the entering and leaving variables also takes at most $O(mn)$, so one pivot takes $O(mn)$ time.

To help understanding, here are the detailed steps for the earlier example, computed with the condensed simplex tableau.

???+ example "Example (continued)"
    Initially, the condensed simplex tableau is:
    
    $$
    \begin{array}{|l|c|ccc|}
    \hline
        &    & x_1 & x_2 & x_3 \\
    \hline
        & 0  & -10 & -12 & -12 \\
    \hline
    x_4= & 20 &   1 & 2   &   2 \\
    x_5= & 20 &   2 & 1   &   2 \\
    x_6= & 20 &   2 & 2   &   1 \\
    \hline
    \end{array}
    $$
    
    By the reduced costs in row $0$, any of $x_1,x_2,x_3$ may enter the basis. Let $x_1$ enter. Then by the minimum ratio test, either $x_5$ or $x_6$ may leave. Let $x_5$ leave. Updating the condensed simplex tableau accordingly gives:
    
    $$
    \begin{array}{|l|c|ccc|}
    \hline
        &    & x_5 & x_2 & x_3 \\
    \hline
        &100 & 5   & -7  & -2  \\
    \hline
    x_4= & 10 &-0.5 & 1.5 &   1 \\
    x_1= & 10 & 0.5 & 0.5 &   1 \\
    x_6= &  0 & -1  & 1   &  -1 \\
    \hline
    \end{array}
    $$
    
    By the reduced costs in row $0$, either $x_2$ or $x_3$ may enter the basis. Let $x_3$ enter. Then by the minimum ratio test, either $x_4$ or $x_1$ may leave. Let $x_4$ leave. Updating the condensed simplex tableau accordingly gives:
    
    $$
    \begin{array}{|l|c|ccc|}
    \hline
        &    & x_5 & x_2 & x_4 \\
    \hline
        &120 & 4   & -4  & 2   \\
    \hline
    x_3= & 10 &-0.5 & 1.5 &  1  \\
    x_1= &  0 &  1  & -1  & -1  \\
    x_6= & 10 & -1.5& 2.5 &  1  \\
    \hline
    \end{array}
    $$
    
    By the reduced costs in row $0$, only $x_2$ can enter the basis. Let $x_2$ enter. Then by the minimum ratio test, only $x_6$ can leave. Let $x_6$ leave. Updating the tableau with the elementary row operations above gives:
    
    $$
    \begin{array}{|l|c|ccc|}
    \hline
        &    & x_5 & x_6  & x_4 \\
    \hline
        &136 & 1.6 & 1.6 & 3.6 \\
    \hline
    x_3= & 4  & 0.4 &-0.6 & 0.4 \\
    x_1= &  4 & 0.4 & 0.4 &-0.6 \\
    x_2= &  4 & -0.6& 0.4 & 0.4 \\
    \hline
    \end{array}
    $$
    
    By the reduced costs in row $0$, there is no entering variable. So the current solution
    
    $$
    x=(4,4,4,0,0,0)^T
    $$
    
    is optimal, and the optimal value (of the minimization problem) is $-136$.

Besides implementing the simplex method with a simplex tableau, you can also use the revised simplex method. It further improves the time and space complexity, reducing the cost of one update to $O(m^2)$, and is especially efficient when $m\ll n$ or $A$ is sparse.

## Geometric background

This section explains the geometric background of the simplex method.

The [analysis](./linear-programming.md#feasible-region-and-solutions) of the feasible region of a linear program

$$
\mathcal D = \{x\in\mathbf R^n : Ax = b,~ x\ge 0\}
$$

shows that:

-   An optimal solution of a linear program (if one exists) can always be chosen to be a vertex of the feasible region $\mathcal D$. So solving a linear program becomes finding the vertex with the best objective value among all vertices.
-   The coordinates of each vertex can be found by solving the system of equations given by $n$ tight constraints. For constraints in standard form, all $m$ equality constraints are always tight, so the remaining $n-m$ constraints must be chosen from the non-negativity constraints. Choosing these non-negativity constraints to be tight is the same as setting the corresponding decision variables $x_N$ to $0$; then the system $Ax = b$ reduces to the linear system $A_Bx_B = b$ in the remaining $m$ decision variables $x_B$. As long as $A_B$ is invertible, we get $x_B = A_B^{-1}b$. This gives a solution $(x_B,x_N)=(A_B^{-1}b,0)$; if $x_B\ge 0$, it is the coordinates of a vertex of $\mathcal D$.

It is easy to see that vertex solutions are the same as the basic feasible solutions defined above. So finding the best basic feasible solution gives an optimal solution of the original problem. Although this simplifies the problem a lot, the feasible region can have exponentially many vertices, so brute-force enumeration is not practical.

To get around this, we can move along the [edges](./linear-programming.md#feasible-region-and-solutions) of the feasible region, from one vertex to a neighboring vertex. Since neighboring vertices lie on the same edge, they share at least $n-1$ tight constraints. In other words, the tight constraints of neighboring vertices differ in exactly one constraint. So for a basic feasible solution $x$, swapping one of its basic variables with a non-basic variable gives an **adjacent** basic feasible solution $x'$. This is exactly the pivot operation.

So the simplex method, which starts from a basic feasible solution and keeps pivoting to improve the objective, is really starting from a vertex of the feasible region and moving to neighboring vertices one after another to improve the objective.

???+ example "Example (continued)"
    In the example discussed in this article, the feasible region is a three-dimensional polyhedron with five vertices, as shown below:
    
    ![](./images/simplex-geo.svg)
    
    Geometrically, the solving process above corresponds to the following path between vertices of the polyhedron:
    
    $$
    (0,0,0) \rightarrow (10,0,0) \rightarrow (0,0,10) \rightarrow (4,4,4).
    $$

## Implementation details

With the simplex tableau we can already solve many linear programs. But for the most general case, there are still many details of the simplex method worth discussing.

### Slack form

We have already discussed the [method](./linear-programming.md#standard-form) for converting a linear program in general form into standard form. But to make it convenient for the simplex method, we also need the coefficient matrix $A$ to have full rank. Converting to standard form first and then removing linearly dependent constraints works, but to keep things simple, the following strategy is usually used:

1.  Convert the linear program to **inequality form**, i.e. the form $\min\{c^Tx : Ax \le b,~ x \ge 0\}$;
2.  Add slack variables $s$ to convert the problem to standard form: $\min\{c^Tx : Ax + s = b,~ x\ge 0,~ s \ge 0\}$.

The advantage is that the coefficient matrix $(A,I)$ of the resulting standard form always has full rank, and there is always a (not necessarily feasible) basic solution $(x,s)=(0,b)$. This special standard form is also called the **slack form**.

### Initial basic feasible solution

The simplex method described above always assumes that a basic feasible solution is known. Sometimes it is easy to find one. For example, if $b\ge 0$ in the slack form above, then $(x,s)=(0,b)$ is a basic feasible solution. This is the situation in the numerical example earlier.

In the general case, we can use the **two-phase method**. The two-phase method runs the simplex method twice. Phase one solves a feasibility linear program to get a basic feasible solution of the original problem. Phase two starts from this basic feasible solution and applies the simplex method to the original problem.

Suppose we have a problem in standard form $\min\{c^Tx : Ax = b \ge 0,~ x\ge 0\}$. In phase one, we solve the problem

$$
\min\{1^Tx_a : Ax + x_a = b,~ x\ge 0,~ x_a\ge 0\}.
$$

This is essentially a feasibility linear program, and the newly added variables $x_a$ are called **artificial variables**. It always has the basic feasible solution $(x,x_a)=(0,b)$, so it can be solved directly with the simplex method. If its optimal value is strictly greater than $0$, there is no $x\ge 0$ with $Ax=b$, i.e. the original problem is infeasible. If its optimal value equals $0$, the artificial variables in its optimal solution must all be zero. If some artificial variables are still basic, they can be moved out of the basis with a few pivots. Finally, when all artificial variables are non-basic, the basic solution from phase one can be used as the initial basic feasible solution for phase two.

???+ note "Implementing phase one without explicit artificial variables"
    When implementing phase one, there is no need to introduce artificial variables explicitly. For any chosen initial basis $B$, we have
    
    $$
    x_B + A_B^{-1}A_Nx_N = A_B^{-1}b.
    $$
    
    If $(A_B^{-1}b)_j\ge 0$, no artificial variable is needed; otherwise, we need to introduce an extra artificial variable $x^{-}_{B_j}$, that is,
    
    $$
    x_{B_j} - x^-_{B_j} + (A_B^{-1}A_N)_{(j)}x_N = (A_B^{-1}b)_j.
    $$
    
    Let the index set $L:=\{j:(A_B^{-1}b)_j<0\}$. Then every phase-one simplex tableau is obtained from the following simplex tableau by some elementary row operations:
    
    $$
    \begin{array}{|r|c|cccc|}
    \hline
                    &                       & x_N                      & x_{B_{\sim L}} & x_{B_L}  &x_{B_{L}}^- \\  
    \hline
                    & 0                     & 0^T                      & 0^T            & 0^T      & 1^T        \\
    \hline
    x_{B_{\sim L}}=  & (A_B^{-1}b)_{\sim L}  & (A_B^{-1}A_N)_{(\sim L)} & I              &  O       &  O         \\
    x_{B_{L}}^-=     & (A_B^{-1}b)_L         & (A_B^{-1}A_N)_{(L)}      & O              &  I       & -I         \\
    \hline
    \end{array}
    $$
    
    Just as we simplified the simplex tableau into the condensed simplex tableau, we can simplify this one: (left-multiply the $x_{B_{L}}^-$ rows by $1^T$ and add them to row $0$, then drop the last three columns)
    
    $$
    \begin{array}{|r|c|cccc|}
    \hline
                    &                      & x_N                      \\  
    \hline
                    & 1^T(A_B^{-1}b)_L     & 1^T(A_B^{-1}A_N)_{(L)}   \\
    \hline
    x_{B_{\sim L}}= & (A_B^{-1}b)_{\sim L} & (A_B^{-1}A_N)_{(\sim L)} \\
    -x_{B_{L}}=     & (A_B^{-1}b)_L        & (A_B^{-1}A_N)_{(L)}      \\
    \hline
    \end{array}
    $$
    
    This is mostly the same as an ordinary condensed simplex tableau, except that the variables in the last rows are marked with a minus sign. This means those rows still contain artificial variables, i.e. the original slack variables are still infeasible. Using this tableau, a pivot works as follows:
    
    1.  If $L=\varnothing$, the algorithm terminates.
    2.  Otherwise, choose the entering variable $x_{N_i}$ by the condition that its reduced cost in row $0$ is negative. If none exists, the original problem is infeasible, and the algorithm terminates.
    3.  Then choose the leaving variable $x_{B_j}$ using column $i$. We still use the minimum ratio test, but we must also make sure that currently feasible variables stay feasible and currently infeasible variables stay infeasible, i.e. choose
    
        $$
        \arg\min_{j}\left\{\dfrac{(\tilde T_B)_{j0}}{(\tilde T_B)_{ji}}:(j\notin L\land(\tilde T_B)_{ji}>0)\lor(j\in L\land(\tilde T_B)_{ji}<0)\right\}
        $$
    
        as the row of the leaving variable. If there are several such leaving variables, prefer an infeasible one.
    4.  Let $x_{N_i}$ enter the basis and $x_{B_j}$ leave, and update the simplex tableau.
    5.  If $j\in L$, remove $j$ from $L$ (i.e. remove the minus-sign mark from that row), and add one to $(\tilde T_B)_{0i}$.
    
    We can drop the columns of the artificial variables because: if they are still basic, their columns are $e_j$ and need not be stored; if they are no longer basic, they will never enter the basis again, so they need not be stored either. When an artificial variable leaves the basis, it must be replaced by the corresponding non-artificial variable, which is the purpose of the last step above.
    
    A reference implementation is as follows:
    
    ??? example "Reference implementation"
        ```cpp
        --8<-- "docs/math/code/simplex/simplex_0.cpp:initialize"
        ```
    
    Before phase one starts, add an extra row to record the phase-one objective function. When pivoting, pivot the whole tableau, including the phase-two objective. This way, when phase one finishes, the phase-two objective has been updated accordingly, and phase two of the simplex method can start right away.

The two-phase method can also be done with a single run of the simplex method. Just pick a sufficiently large positive number $M$ and directly solve the problem

$$
\min\{c^Tx + M1^Tx_a : Ax + x_a = b,~ x\ge 0,~ x_a\ge 0\}
$$

to get an optimal solution of the original problem. In the implementation, $M$ is not given a specific value; instead it is treated as an unknown, sufficiently large positive number during computation. This is called the **big $M$ method**.

???+ warning "The naive algorithm is exponential in practice"
    Since the slack form always has an initial basic solution, which just may not be feasible, a simple idea for finding an initial basic feasible solution is: start from an infeasible basic solution and pivot repeatedly, moving an infeasible basic variable out of the basis and bringing in a non-basic variable whose column has a negative entry in the same row, until all basic variables are non-negative. A reference implementation is as follows:
    
    ??? example "Reference implementation"
        ```cpp
        --8<-- "docs/math/code/simplex/simplex_2.cpp:initialize"
        ```
    
    This is simple, but compared with the two-phase method it has no objective function that measures how infeasible the current basis is, so it lacks a clear direction of improvement. Experiments show that while the two-phase method or the big $M$ method usually needs only $O(m)$ pivots, this naive algorithm usually needs $O(2^m)$ pivots, and it easily cycles when $n,m$ are large. Although the constant in the naive algorithm's number of pivots is small, it is only suitable for $n,m<50$.

### Pivot rules

When pivoting, if there are several possible entering or leaving variables, we need a **pivot rule** to decide which variable enters or leaves the basis. With the simplex tableau, all the rules discussed in this section can find the entering and leaving variables in $O(mn)$ time, so one pivot still takes $O(mn)$ time.

The choice of entering variable often determines how many pivots happen before the algorithm terminates. Common rules are:

-   choose the first entering variable found;
-   choose the entering variable with the smallest index; (part of Bland's rule)
-   choose the entering variable with the largest absolute reduced cost (i.e. $|\tilde c_i|$); (Dantzig's rule)
-   choose the entering variable that gives the largest improvement of the objective in a single pivot (i.e. $|\tilde c_i|\theta_i$);
-   choose the entering variable corresponding to the steepest edge, i.e. the one for which moving a unit length along the edge gives the largest improvement of the objective (i.e. $|\tilde c_i|/\sqrt{1+\|A_B^{-1}A_i\|^2}$);
-   choose an entering variable at random.

In practice, the steepest-edge rule is the most efficient[^steepest-edge]. It is generally believed that a suitable pivot rule finds the optimal solution of most problems in about $2m$ pivots. However, for every pivot rule known today, there are specially constructed examples[^klee-minty] that force an exponential number of pivots. This is why the simplex method runs very well in practice but has exponential worst-case complexity in theory.

The choice of leaving variable often determines whether the algorithm cycles. If several bases correspond to the same basic feasible solution (the degenerate case), the algorithm may keep cycling among these bases. Such cases are uncommon, so many implementations of the simplex method do not specify a rule for choosing the leaving variable. There are two common rules to avoid cycling:

-   Bland's rule: always choose the entering and leaving variables with the smallest index.
-   Lexicographic rule: always choose the leaving variable $x_{B_j}$ for the row $j$ with $(A_B^{-1}A_i)_j>0$ for which

    $$
    \left(\dfrac{(A_B^{-1}b)_j}{(A_B^{-1}A_i)_j},\dfrac{(A_B^{-1})_{j1}}{(A_B^{-1}A_i)_j},\cdots,\dfrac{(A_B^{-1})_{jm}}{(A_B^{-1}A_i)_j}\right)
    $$

    is lexicographically smallest. The choice of entering variable does not matter.

    Note that if the linear program is in slack form, all these quantities can be read directly from the simplex tableau $T_B$ in the form described above. Otherwise, after finding an initial basic solution (not necessarily feasible), you can use the coefficients of the columns of the basic variables of that initial basis (in a fixed order) as the coefficients of $A_B^{-1}$.

Bland's rule is very inefficient, because it chooses entering and leaving variables in the same way, which easily makes the same variable enter and leave the basis over and over. The lexicographic rule is more practical. It is equivalent to perturbing the parameters of the linear program[^lexico] so that there are no degenerate basic feasible solutions, and therefore no possibility of cycling.

## Reference implementation

This section gives a reference implementation of the two-phase simplex method based on the condensed simplex tableau.

??? example "[Luogu P13337 [Template] Linear Programming](https://www.luogu.com.cn/problem/P13337)"
    ```cpp
    --8<-- "docs/math/code/simplex/simplex_0.cpp:full-text"
    ```

## Example problems

???+ example "[NOI2008 Volunteer Recruitment](https://www.luogu.com.cn/problem/P3980)"
    An event lasts $n$ days and needs volunteers; day $i$ needs at least $b_i$ volunteers. There are $m$ types of volunteers. Volunteers of type $j$ can serve on the contiguous range of days $[l_j,r_j]$, and each costs $c_j$ to recruit. Find the best recruitment plan that minimizes the cost of recruiting volunteers.

??? note "Solution"
    Suppose we recruit $x_j$ volunteers of type $j$. Then the linear program is
    
    $$
    \begin{align*}
    \min_{x}\; & \sum_{j=1}^mc_jx_j \\
    \text{subject to }& \sum_{j=1}^m a_{ij}x_j \ge b_i,~i=1,\cdots,n,\\
    & x_j\ge 0,~j=1,\cdots,m.
    \end{align*}
    $$
    
    where the coefficients are
    
    $$
    a_{ij} = 
    \begin{cases}
    1,& l_j\le i\le r_j,\\
    0,& \text{otherwise.}
    \end{cases}
    $$
    
    The original problem has no obvious initial feasible solution. So let us consider its [dual problem](./linear-programming.md#duality):
    
    $$
    \begin{align*}
    \max_{y}\; & \sum_{i=1}^n b_iy_i \\
    \text{subject to } & \sum_{i=1}^na_{ij}y_i \le c_j,~j=1,\cdots,m,\\
    & y_i\ge 0,~i=1,\cdots,n.
    \end{align*}
    $$
    
    By adding slack variables, we easily get an initial feasible solution, so we can skip phase one and solve it directly with the simplex method. By duality, the solution we get is the solution of the original problem.
    
    ```cpp
    --8<-- "docs/math/code/simplex/simplex_1.cpp"
    ```

## Exercises

-   [Luogu P13337 [Template] Linear Programming](https://www.luogu.com.cn/problem/P13337)
-   [UOJ#179. Linear Programming](https://uoj.ac/problem/179)
-   [Luogu P4232 Hide and Seek Beyond the Unconscious](https://www.luogu.com.cn/problem/P4232)
-   [Codeforces 1430 G. Yet Another DAG Problem](https://codeforces.com/problemset/problem/1430/G)
-   [AtCoder Beginner Contest 231 H - Minimum Coloring](https://atcoder.jp/contests/abc231/tasks/abc231_h)

## References

-   [The Simplex Method for Linear Programming (super detailed explanation + illustrations)](https://www.cnblogs.com/ECJTUACM-873284962/p/7097864.html)
-   [2016 Chinese National Training Team Papers](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2016%E8%AE%BA%E6%96%87%E9%9B%86.pdf)
-   Introduction to Algorithms (CLRS)
-   Matoušek, Jiří, and Bernd Gärtner. Understanding and using linear programming. Vol. 1. Berlin: Springer, 2007.
-   Inayatullah, Syed, Nasir Touheed, and Muhammad Imtiaz. "A streamlined artificial variable free version of simplex method." PloS one 10, no. 3 (2015): e0116156.
-   Floudas, Christodoulos A., and Panos M. Pardalos, eds. Encyclopedia of optimization. Springer Science & Business Media, 2008.

[^notation]: Strictly speaking, since all vectors are column vectors by default, $(x_B,x_N)$ should be written $(x_B^T,x_N^T)^T$. But to simplify notation, all similar cases in this article are written directly as $(x_B,x_N)$, without the transpose symbols.

[^steepest-edge]: For test results, see Forrest, John J., and Donald Goldfarb. "Steepest-edge simplex algorithms for linear programming." Mathematical programming 57, no. 1 (1992): 341-374.

[^klee-minty]: For a classic counterexample, see Klee, Victor, and George J. Minty. "How good is the simplex algorithm." Inequalities 3, no. 3 (1972): 159-175.

[^lexico]: For a detailed explanation, see [these lecture notes](https://misha.fish/archive/docs/3272-fall-2022/lecture8.pdf).
