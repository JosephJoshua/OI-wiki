author: Ir1d, YZircon, huhaoo, QAQAutoMaton, Enter-tainer, Marcythm, sshwy, partychicken, Konano, H-J-Granger, baker221, isdanni, ksyx

## Introduction

Linear programming (LP) is the general name for methods that find the maximum or minimum of a linear objective function under linear constraints. It is a branch of operations research with applications in many areas. Some special cases of linear programming, such as network flow and multi-commodity flow, can show up in contest problems. Contest problems that can only be solved with a linear programming algorithm are rare; most such problems can be solved more efficiently by other methods, such as modeling them as network flow.

### A simple example

For a problem to be written as a linear program, it needs some linear constraints and a linear objective function.

Consider the following example:

???+ example "Example"
    A breakfast cook makes a certain number of steamed buns (baozi) and fried dough sticks (youtiao) every day, and customers love both. To maximize profit, the cook wants to make as much as possible, but in practice is limited by ingredients, time and other resources. So the cook has recorded how much of each ingredient and how much time each item takes, and the profit from each, as shown in the table below:
    
    |  Item | Vegetable oil |  Flour |  Time |  Profit |
    | :-: | :-: | :-: | :-: | :-: |
    |  Steamed bun | $4$ | $7$ | $8$ | $5$ |
    |  Fried dough stick | $7$ | $3$ | $6$ | $6$ |
    
    Suppose the cook can buy at most $66$ units of vegetable oil and $60$ units of flour per day, and can spend at most $96$ units of time. How many steamed buns and fried dough sticks should the cook make to maximize daily profit?

In mathematical terms, let $x_1$ and $x_2$ be the numbers of steamed buns and fried dough sticks the cook makes. Then "the total vegetable oil needed is at most $66$ units" can be written as

$$
4x_1 + 7x_2 \le 66.
$$

Similarly, "the total flour needed is at most $60$ units" and "the total time needed is at most $96$ units" can be written as

$$
\begin{aligned}
7x_1 + 3x_2 &\le 60,\\
8x_1 + 6x_2 &\le 96.
\end{aligned}
$$

Also, the cook cannot make a negative amount of food, so we also have

$$
x_1,x_2\ge 0.
$$

Under these constraints, the cook wants to maximize the profit:

$$
z = 5x_1 + 6x_2.
$$

This is a typical linear programming problem. Its objective function is a linear function of the decision variables, and its constraints are linear equalities or inequalities in the decision variables.

### Graphical method

A linear program with only two decision variables can be solved visually with the graphical method.

Consider the geometric picture of the problem in this section

$$
\begin{aligned}
\max_{x_1,x_2}\;& z = 5x_1 + 6x_2 \\
\text{subject to } & 4x_1 + 7x_2 \le 66,\\
& 7x_1 + 3x_2 \le 60,\\
& 8x_1 + 6x_2 \le 96,\\
& x_1,x_2\ge 0
\end{aligned}
$$

The last constraint says the allowed points $(x_1,x_2)$ all lie in the first quadrant. The other three constraints say the allowed points must lie below the lines $4x_1 + 7x_2 = 66$, $7x_1 + 3x_2 = 60$ and $8x_1 + 6x_2 = 96$. The intersection of these regions (the green region in the figure below) is the set of all allowed points:

![](images/linear-programming.svg)

Next we want to maximize $z=5x_1+6x_2$. If we view this as the equation of the line $5x_1+6x_2=z$, then as $z$ changes we get a family of parallel lines, and the larger $z$ is, the further toward the upper right the line is. So we just keep moving the line until it reaches a critical position: moving it any further toward the upper right would make it miss the region entirely. The $z$ for that line is the maximum we want.

As the figure shows, this happens at the red point. It is the intersection of the lines $4x_1 + 7x_2 = 66$ and $7x_1 + 3x_2 = 60$. Solving the two equations together gives its coordinates $(6,6)$. This is the unique optimal solution of the problem. The cook's maximum profit is $z=66$.

When there are more than two decision variables, the graphical method no longer works. But some observations from this example still hold. Each inequality constraint in a linear program describes a "half-plane", and the set of all feasible solutions is the intersection of these "half-planes", so it is always a "convex polygon". The optimal value can always be attained at some "vertex" of this "convex polygon". The coordinates of these "vertices" can be found by solving the equations of the "boundaries" of the "half-planes" together. Extending these observations to higher dimensions leads to an efficient method for solving linear programs: the simplex method. It is also the method most often used in contests.

Another point worth noting is that, in principle, the cook cannot make fractions of a steamed bun or dough stick; the amounts should be integers. The solution above did not explicitly require this, but since the optimal solution turned out to be integral, the answer is still valid even with integer constraints added. For many optimization problems, however, the optimum may not be attained at an integer point. Such problems are really integer programming problems rather than simple linear programs. They are briefly discussed at the end of this page.

## Basic concepts

This section introduces the basic concepts of linear programming.

### Linear programming problems

A linear programming problem $P$ usually consists of two parts:

-   A linear objective function, that is, a function of the form

    $$
    f(x_1,x_2,\cdots,x_n)=c_1x_1+c_2x_2+\cdots+c_nx_n
    $$

    where $c_i\in\mathbf R$ are constants;

-   Linear constraints, that is, inequality or equality constraints of the form

    $$
    g_j(x_1,x_2,\cdots,x_n)=a_{j1}x_1+a_{j2}x_2+\cdots+a_{jn}x_n \le (=,\ge) b_j
    $$

    where $a_{ji},b_j\in\mathbf R$ are constants.

A linear programming problem asks us to maximize or minimize the objective function subject to the given constraints. A solution $(x_1,x_2,\cdots,x_n)\in\mathbf R^n$ that satisfies the constraints is called a **feasible solution**; among all feasible solutions, one where the objective function attains its optimum is called an **optimal solution**.

### Standard form

To make linear programs easier to describe and work with, we usually fix a standard form. Different sources may define it differently. This page uses the following standard form:

$$
\begin{aligned}
\min_{\{x_i\}}\;& \sum_{i=1}^n c_ix_i \\
\text{subject to }& \sum_{i=1}^n a_{ji}x_i = b_j \ge 0,~j=1,\cdots,m,\\
& x_i \ge 0,~i = 1,\cdots,n.
\end{aligned}
$$

In other words, the problem is a minimization problem, every decision variable has a non-negativity constraint, and apart from that there are only equality constraints whose right-hand constants are non-negative. Using [matrices](./linear-algebra/matrix.md), the problem can be written more compactly as:

$$
\min\{c^Tx : Ax = b \ge 0,~ x\ge 0\}.
$$

Here $x=(x_i)\in\mathbf R^n$ are the decision variables, and $b=(b_j)\in\mathbf R^m$ and $A=(a_{ji})\in\mathbf R^{m\times n}$ are the constants in the constraints. The size of a linear program means its number of decision variables and its number of constraints.

???+ tip "Vector inequalities"
    Vector inequalities such as $b \ge 0$ appear many times on this page. In general, for vectors $x,y\in\mathbf R^n$, the inequality $x\le y$ means $\forall i(x_i\le y_i)$, that is, the real numbers are compared coordinate by coordinate. This relation is a [partial order](./order-theory.md#binary-relations) on the vector space, which means some pairs of vectors cannot be compared.

The choice of standard form is only for convenience and has nothing special about it, because every linear program can be written equivalently in any of the following six forms:

$$
\begin{aligned}
&\min\{c^Tx : Ax = b,~ x\ge 0\},\\
&\min\{c^Tx : Ax \ge b\},\\
&\min\{c^Tx : Ax \ge b,~ x\ge 0\},\\
&\max\{c^Tx : Ax = b,~ x\ge 0\}, \\
&\max\{c^Tx : Ax \le b\},\\
&\max\{c^Tx : Ax \le b,~ x\ge 0\}.\\
\end{aligned}
$$

The following operations turn any linear program into an equivalent one in one of these six forms:

1.  Adding a minus sign, that is, replacing $c$ with $-c$, turns a maximization problem into a minimization problem and vice versa.
2.  Adding a minus sign, that is, replacing $a_j^Tx \lesseqqgtr b_j$ with $-a_j^Tx \gtreqqless -b_j$, flips the direction of an inequality constraint, or makes the right-hand constant of an equality constraint non-negative.
3.  Every equality constraint $a_j^Tx = b_j$ can be replaced with two inequality constraints in opposite directions, $a_j^Tx \ge b_j$ and $a_j^Tx \le b_j$.
4.  Every inequality constraint $a_j^Tx \le(\ge) b_j$ can be turned into an equality constraint $a_j^Tx +(-) s_j = b_j$ plus the non-negativity constraint $s_j\ge 0$ by adding a non-negative slack variable $s_j$.
5.  If a decision variable $x_i$ has no non-negativity constraint, it can be replaced with the difference of two non-negative variables: $x_i = x^+_i - x^-_i$ with $x^+_i,x^-_i \ge 0$.

These operations at most double the size of the problem, and feasible and optimal solutions are easy to convert back and forth. So a linear program in general form can always be converted to standard form (or one of the six forms above) first and then solved.

??? example "Example"
    Consider the linear program
    
    $$
    \begin{aligned}
    \max\;& 3x_1 - 2x_2 + x_3 \\
    \text{subject to }& 2x_1 + 3x_2 + 4x_3 \ge 1,\\
    & 3x_1 + 4x_2 \le 5,\\
    & 5x_2 - x_3 = -1, \\
    & x_1, x_2 \ge 0.
    \end{aligned}
    $$
    
    Using operations 1, 2 and 3, it can be turned into the form $\min\{c^Tx : Ax \ge b\}$:
    
    $$
    \begin{aligned}
    \min\;& -3x_1 + 2x_2 - x_3 \\
    \text{subject to }& 2x_1 + 3x_2 + 4x_3 \ge 1,\\
    & -3x_1 - 4x_2 \ge -5,\\
    & 5x_2 - x_3 \ge -1, \\
    & -5x_2 + x_3 \ge 1, \\
    & x_1 \ge 0,\\
    & x_2 \ge 0.
    \end{aligned}
    $$
    
    Using operations 4 and 5, it can be turned into the form $\max\{c^Tx : Ax = b,~ x\ge 0\}$:
    
    $$
    \begin{aligned}
    \max\;& 3x_1 - 2x_2 + x^+_3 - x^-_3 \\
    \text{subject to }& 2x_1 + 3x_2 + 4x^+_3 - 4x^-_3 - x_4 = 1,\\
    & 3x_1 + 4x_2 + x_5 = 5,\\
    & 5x_2 - x^+_3 + x^-_3 = -1, \\
    & x_1, x_2, x^+_3, x^-_3, x_4, x_5 \ge 0.
    \end{aligned}
    $$

### Feasible region and solutions

The set $\mathcal D\subseteq\mathbf R^n$ of all feasible solutions is called the **feasible region** of the linear program $P$. Geometrically, each inequality constraint $a_j^T x \le b_j$ describes a half-space $\{x\in\mathbf R^n:a_j^T x \le b_j\}$, and each equality constraint $a^T_jx = b_j$ describes a hyperplane $\{x\in\mathbf R^n:a_j^Tx=b_j\}$. So the feasible region is always the intersection of finitely many half-spaces and hyperplanes. In optimization[^poly-names], such a shape is usually called a **polyhedron** in $\mathbf R^n$. A polyhedron is always a closed convex set, but it need not be bounded. A bounded polyhedron is also called a **polytope**. A polytope can be seen as the generalization of a polygon in the plane to higher dimensions, and a polyhedron generalizes it further to the possibly unbounded case.

???+ example "Examples of polyhedra"
    Here are some common polyhedra:
    
    1.  The empty set $\varnothing$, also called the **nullitope**, whose dimension is defined to be $-1$.
    2.  An **affine subspace**, that is, an intersection of hyperplanes $\{x\in\mathbf R^n:Ax = b\}$. It is the solution set of the linear system $Ax = b$: if the system has no solution, it is empty; otherwise it can always be written as $x_0+V$, where $x_0\in\mathbf R^n$ and $V\subseteq\mathbf R^n$ is a linear subspace of dimension $n-\operatorname{rank}A$. In particular, a hyperplane is also an affine subspace.
    3.  A **polyhedral cone**, that is, the set of all non-negative linear combinations $\{\sum_i\alpha_ix_i:\alpha_i\ge 0\}$ of finitely many points $\{x_i\}$ in space. It is a convex cone with its apex at the origin. Equivalently, it is a polyhedron bounded by finitely many hyperplanes through the origin, $\{x\in\mathbf R^n : Ax\le 0\}$. In particular, a half-space is also a polyhedral cone.
    4.  A polytope, that is, a bounded polyhedron. In particular, polytopes of dimension $-1$, $0$, $1$, $2$, $3$ are the familiar empty set, point, line segment, polygon and (ordinary) polyhedron. A set is a polytope if and only if it is the convex hull $\{\sum_i\alpha_ix_i:\alpha_i\ge 0,~\sum_i\alpha_i=1\}$ of finitely many points $\{x_i\}$. A $k$-dimensional polytope is the convex hull of at least $k+1$ points.
    5.  A **simplex**, that is, a $k$-dimensional polytope generated by exactly $k+1$ points. It is the simplest $k$-dimensional polytope. In particular, simplices of dimension $-1$, $0$, $1$, $2$, $3$ are the empty set, point, line segment, triangle and tetrahedron. The simplest example of a $k$-dimensional simplex is $\{x\in\mathbf R^{k+1}:x_i\ge 0,~\sum_ix_i=1\}$. In fact, every $k$-dimensional simplex can be turned into this special case by an affine transformation (translation and scaling). Note that the simplex method does not actually work on a simplex.
    
    Every polyhedron can be seen as the [Minkowski sum](../geometry/convex-hull.md#minkowski-sum) of a polyhedral cone and a polytope: the cone describes the unbounded part of the polyhedron, and the polytope describes the shape of its bounded part. This polyhedral cone is unique: the cone obtained by decomposing the polyhedron $\{x\in\mathbf R^n:Ax\le b\}$ is always $\{x\in\mathbf R^n:Ax\le 0\}$.

The solutions of a linear program are closely tied to the structure of the polyhedron. For a polyhedron $\mathcal D\subseteq\mathbf R^n$ and a vector $c\in\mathbf R^n\setminus\{0\}$, consider the following linear program $P$ (the minimization case is similar):

$$
\max\{c^Tx:x\in\mathcal D\}.
$$

Geometrically, this means moving the hyperplane $H:c^Tx = z$ in the direction of $c$ to make $z$ as large as possible, while keeping at least one intersection point between $H$ and the feasible region $\mathcal{D}$. There are three possibilities:

-   The feasible region $\mathcal D$ is empty. Then $P$ has no feasible solution, and some of its constraints contradict each other. In this case $P$ is called **infeasible**, and its optimal value is defined to be $-\infty$.

-   The feasible region $\mathcal D$ is nonempty, but it contains a ray whose direction vector $d$ satisfies $c^Td>0$; that is, there is $x_0\in\mathbf R^n$ such that $x_0+td\in\mathcal D$ for all $t\ge 0$. We can keep moving the hyperplane $H$ in the direction of $c$, and during the movement $H\cap\mathcal D$ always contains some point of this ray, so it is never empty. Therefore the objective $c^Tx = c^Tx_0 + tc^Td$ can be made arbitrarily large. In this case $P$ is called **unbounded**, and its optimal value is defined to be $+\infty$.

-   The feasible region $\mathcal D$ is nonempty and contains no such ray. In this case $P$ is called **bounded**. Let $z^*\in\mathbf R$ be the optimal value of $P$. The hyperplane $H^*:c^Tx = z^*$ is in a critical position: it intersects the polyhedron $\mathcal D$, and $\mathcal D$ lies in the half-space $\{x:c^Tx\le z^*\}$. Such a hyperplane is called a **supporting hyperplane** of $\mathcal D$. The set of optimal solutions of $P$ is exactly $H^*\cap\mathcal D$. As the intersection of a supporting hyperplane and a polyhedron, $H^*\cap\mathcal D$ is always a polyhedron and lies on the boundary of $\mathcal D$. It is called a **face** of $\mathcal D$. Intuitively, a polyhedron is enclosed by its faces. Besides the faces formed by intersecting supporting hyperplanes with the polyhedron, a polyhedron is generally also considered to have two more faces: the empty set and the polyhedron itself. Under set inclusion, all faces of a polyhedron form a [lattice](../math/order-theory.md#directed-sets-and-lattices).

    The faces of a $d$-dimensional polyhedron have integer dimensions between $-1$ and $d$. A face of dimension $0$ (a single point) is called a **vertex** or **corner point** of $\mathcal D$, a face of dimension $1$ is called an **edge** of $\mathcal D$, and a face of dimension $d-1$ is called a **facet** of $\mathcal D$. However, not every polyhedron has vertices. A face of a face of a polyhedron is again a face of the polyhedron, and only affine subspaces have no strictly smaller nonempty faces, so all minimal faces of $\mathcal D$ are affine subspaces. Moreover, all minimal faces of the same polyhedron have the same dimension; in particular, the minimal faces of $\mathcal D=\{x\in\mathbf R^n:Ax\le b\}$ have dimension $n-\operatorname{rank}A$.

    Since the faces of a polyhedron are exactly the solution sets of bounded linear programs, we need to understand how to find the equations of a face. Suppose the polyhedron $\mathcal D$ is described by constraints $a_j^Tx \lesseqqgtr b_j$, and $F$ is a face of $\mathcal D$. If a constraint holds with equality at every $x\in F$, it is called **tight** on $F$. Points of $F$ obviously satisfy the system of equations obtained by turning these tight constraints into equalities, and the intersection of the affine subspace defined by this system with $\mathcal D$ is exactly $F$. Conversely, pick any subset of the constraints of $\mathcal D$, turn them into equalities and solve them together; the intersection of the resulting affine subspace with the polyhedron is a face of $\mathcal D$. Also, the more tight constraints we pick, the smaller (with respect to inclusion) the face.

    In particular, for the feasible region $\mathcal D=\{x\in\mathbf R^n:Ax=b,~x\ge 0\}$ of a linear program in standard form, the coefficient matrix $\begin{pmatrix}A\\ I\end{pmatrix}$ has rank $n$, so its minimal faces are its vertices. That is, if the problem is bounded, an optimal solution can always be chosen at a vertex. Moreover, such a vertex can be found by solving $n$ linearly independent tight constraints together. This is exactly why the standard form is convenient.

???+ example "Example"
    In the figure below, $\mathcal D$ is the feasible region. When the objective coefficients are $c_1,c_2,c_3$, we get three cases: a unique optimal solution, multiple optimal solutions, and unbounded. In the first two cases, the thick red line is (one of) the supporting hyperplane(s) for the solution set, and the optimal solution sets are the vertex $B$ and the edge $\overline{CD}$ of $\mathcal D$, respectively. In the third case, since $\mathcal D$ contains a ray in direction $c_3$, the hyperplane with normal vector $c_3$ can keep moving in direction $c_3$, so the problem is unbounded.
    
    ![](./images/lp-feasible.svg)

This discussion ignored the case $c=0$. In that case the linear program clearly cannot be unbounded, so either the problem is infeasible, or the optimal value is $0$ and the set of optimal solutions is $\mathcal D$ itself. This special kind of linear program is called a **feasibility linear program**.

It is worth pointing out that deciding whether a linear program is feasible or bounded, and finding a feasible solution of a system of inequalities, are all as hard as solving a linear program itself[^reducible]. For example, the proof of the strong duality theorem below shows that solving a bounded linear program is equivalent to finding a feasible solution of a system of inequalities. So for tasks such as deciding whether a system of inequalities has a solution or whether a system of equations has a non-negative solution, the most effective method is to solve the corresponding feasibility linear program[^other-methods].

Also, if a constraint of a linear program is not tight on any face of the feasible region, it is called **redundant**. In the breakfast cook example at the beginning of this page, the time constraint is redundant. To decide whether an inequality $a_j^Tx\le b_j$ in a given system is redundant, solve the linear program $\max\{a_j^Tx:x\in\mathcal D\}$ and compare the result with $b_j$.

## Common algorithms

In contests, very few problems can only be solved by linear programming algorithms. Most problems that can be solved with linear programming can usually also be solved by more specialized and more efficient algorithms, such as network flow.

Common algorithms for linear programming are:

-   [Simplex method](./simplex.md)
-   Ellipsoid method
-   Interior-point methods

Although the simplex method has exponential worst-case complexity while interior-point methods are polynomial, both perform very well on most practical problems. In contrast, the ellipsoid method has polynomial theoretical complexity but is usually slow and not practical.

It is still unknown whether linear programming has a strongly polynomial algorithm.

## Duality

Every linear program has a corresponding dual problem, and the solutions of the original (primal) problem and the dual are closely connected. The dual not only helps us understand the structure of the problem more deeply, but can often also make the primal problem faster to solve.

For the linear program $P$ (all lowercase variables here are vectors)

$$
\begin{aligned}
\min_{x_1,x_2,x_3}\;& c_1^Tx_1 + c_2^Tx_2 + c_3^Tx_3 \\
\text{subject to }& A_{11}x_1 + A_{12}x_2 + A_{13}x_3 \ge b_1,\\
& A_{21}x_1 + A_{22}x_2 + A_{23}x_3 = b_2,\\
& A_{31}x_1 + A_{32}x_2 + A_{33}x_3 \le b_3,\\
& x_1\ge 0,~ x_3\le 0,
\end{aligned}
$$

its dual problem $D$ is the linear program

$$
\begin{aligned}
\max_{y_1,y_2,y_3}\;&b_1^Ty_1+b_2^Ty_2+b_3^Ty_3 \\
\text{subject to }&A_{11}^Ty_1 + A_{21}^Ty_2 + A_{31}^Ty_3\le c_1,\\
&A_{12}^Ty_1 + A_{22}^Ty_2 + A_{32}^Ty_3 = c_2,\\
&A_{13}^Ty_1 + A_{23}^Ty_2 + A_{33}^Ty_3 \ge c_3,\\
&y_1\ge 0,~ y_3\le 0.
\end{aligned}
$$

Here the dual decision variables $y_1,y_2,y_3$ are the Lagrange multipliers of the three kinds of constraints in the primal; conversely, the primal decision variables $x_1,x_2,x_3$ are the Lagrange multipliers of the three kinds of constraints in the dual. It is easy to check that the dual of the dual is the primal.

The correspondence between the primal $P$ and the dual $D$ is as follows:

|  Minimization problem |  Maximization problem |
| :----: | :----: |
| $\ge$ constraint |  Non-negative variable  |
| $\le$ constraint |  Non-positive variable  |
|  Equality constraint  |  Free variable |
|  Non-negative variable  | $\le$ constraint |
|  Non-positive variable  | $\ge$ constraint |
|  Free variable |  Equality constraint  |
| Objective coefficients | Right-hand constants |
| Right-hand constants | Objective coefficients |

In particular, the dual of the standard-form linear program

$$
\min\{c^Tx:Ax=b,~x\ge 0\}
$$

is

$$
\max\{b^Ty:A^Ty\le c\}.
$$

### Duality principle

The primal and the dual are not only mirror images in form; their solutions are also closely related. This is called the **duality principle**. For convenience, this section states and proves the theorems with the primal problem in standard form.

First, the **weak duality theorem** says that the maximum of the dual is at most the minimum of the primal.

???+ note "Weak duality theorem"
    For all $A\in\mathbf R^{m\times n}$, $b\in\mathbf R^m$ and $c\in\mathbf R^n$,
    
    $$
    \max\{b^Ty:A^Ty\le c\} \le \min\{c^Tx:Ax=b,~x\ge 0\}.
    $$

??? note "Proof"
    If either the primal or the dual is infeasible, the inequality is trivial. Suppose both are feasible. Then for all feasible $x$ and $y$,
    
    $$
    b^Ty = x^TA^Ty \le x^Tc.
    $$
    
    Taking the optimum on both sides gives the weak duality theorem.

To go further into the relationship between the solutions of the primal and the dual, we need Farkas' lemma (and its variants). It gives a necessary and sufficient condition for a linear system to have a non-negative solution.

???+ note "Farkas' lemma"
    For $A\in\mathbf R^{m\times n}$ and $b\in\mathbf R^m$, exactly one of the following holds:
    
    1.  There is $x\in\mathbf R^n$ such that $Ax=b$ and $x\ge 0$;
    2.  There is $y\in\mathbf R^m$ such that $A^T y\ge 0$ and $b^Ty<0$.

??? note "Proof"
    If both held, we would have $0\le (A^Ty)^Tx = y^T(Ax) = b^Ty<0$, a contradiction. So at most one holds. Next we show at least one holds. Let $C=\{Ax:x\ge 0\}$ be the polyhedral cone generated by the columns of $A$. If $b\in C$, case 1 holds; otherwise we need to show case 2 holds. The polyhedral cone $C$ can also be written as the intersection of finitely many half-spaces through the origin, so it is a closed convex set. Since $b\notin C$, the hyperplane separation theorem gives $y\in\mathbf R^m$ and $\alpha\in\mathbf R$ such that $b^Ty<\alpha$ and $z^Ty>\alpha$ for all $z\in C$. Since $0\in C$, $\alpha<0$, and so $b^Ty<0$. Also, $t(A^Ty)^Tx>\alpha$ for all $x\ge 0$ and $t>0$; letting $t\to+\infty$ shows $(A^Ty)^Tx\ge 0$ for all $x\ge 0$, that is, $A^Ty\ge 0$. This is case 2.

Geometrically, case 1 says the point $b$ lies in the polyhedral cone $C$ generated by the columns of $A$; case 2 says there is a hyperplane $H:y^Tx = 0$ through the origin with normal vector $y$ that strictly separates the point $b$ from the cone $C$. So Farkas' lemma is a kind of [hyperplane separation theorem](https://en.wikipedia.org/wiki/Hyperplane_separation_theorem).

Using Farkas' lemma, we can decide whether the primal is unbounded from the feasibility of the primal and the dual.

???+ note "Corollary"
    A linear program is unbounded if and only if it is feasible and its dual is infeasible.

??? note "Proof"
    Again we take the primal in standard form. For a linear program in general form, just convert it to standard form first, because the conversions described [earlier](#standard-form) do not change the feasibility or boundedness of the problem or its dual.
    
    On one hand, if the primal is unbounded, it is clearly feasible and its optimal value is $-\infty$. Then the dual must be infeasible; otherwise its optimal value would be at least some real number, contradicting weak duality.
    
    On the other hand, suppose the primal is feasible and the dual is infeasible. Write the free variable in the constraint $A^Ty\le c$ as the difference of two non-negative variables $y=y^+-y^-$ and add a non-negative slack variable $s$. The constraint becomes equivalent to $Mz=c$ and $z\ge 0$, where $M=(A^T,-A^T,I)$ and $z=(y^+,y^-,s)$. Since $M^Td=(Ad,-Ad,d)$, applying Farkas' lemma to $M$ and $c$ shows that exactly one of the following holds: there is $y$ with $A^Ty\le c$, or there is $d\ge 0$ with $Ad=0$ and $c^Td<0$. By assumption, the second holds. Now take any feasible solution $x_0$ of the primal. Then $A(x_0+td)=b$ and $x_0+td\ge 0$ for all $t\ge 0$, while $c^T(x_0+td)=c^Tx_0+tc^Td\to-\infty~(t\to+\infty)$. So the primal is unbounded.

Combining weak duality with this corollary, the solutions of the primal and dual can only fall into these four cases:

1.  Both the primal and the dual are infeasible, i.e., $-\infty\le+\infty$;
2.  The primal is infeasible and the dual is unbounded, i.e., $+\infty\le+\infty$;
3.  The primal is unbounded and the dual is infeasible, i.e., $-\infty\le-\infty$;
4.  Both the primal and the dual are bounded.

In the fourth case, a stronger result holds: the optimal values of the primal and the dual are equal. Combining the last three cases gives the **strong duality theorem**: as long as either the primal or the dual is feasible, their optimal values must be equal.

???+ note "Strong duality theorem"
    For all $A\in\mathbf R^{m\times n}$, $b\in\mathbf R^m$ and $c\in\mathbf R^n$,
    
    $$
    \max\{b^Ty:A^Ty\le c\} = \min\{c^Tx:Ax=b,~x\ge 0\}.
    $$
    
    as long as one of the two sets is nonempty.

??? note "Proof"
    In the discussion above, the only case where the optimal value has not been determined is when both the primal and the dual are feasible. In this case, consider the following feasibility linear program $Q$:
    
    $$
    \max\{0:c^Tx \le b^Ty,~Ax=b,~x\ge 0,~A^Ty\le c\}.
    $$
    
    If $Q$ has a feasible solution $(x^*,y^*)\in\mathbf R^n\times\mathbf R^m$, then by weak duality and optimality,
    
    $$
    b^Ty^* \le \max\{b^Ty:A^Ty\le c\} \le \min\{c^Tx:Ax=b,~x\ge 0\} \le c^Tx^*,
    $$
    
    but $c^Tx^*\le b^Ty^*$, so all these inequalities hold with equality. That is, not only does strong duality hold, but $x^*$ and $y^*$ are optimal solutions of the primal and the dual, respectively.
    
    So we only need to prove that $Q$ is feasible. Suppose it is not. Following the proof of the corollary above, consider the dual $DQ$ of $Q$:
    
    $$
    \min\{c^T\mu - b^T\lambda : ct - A^T\lambda \ge 0,~ -bt + A\mu = 0,~t\ge 0,~\mu\ge 0\}.
    $$
    
    Since $(t,\lambda,\mu)=(0,0,0)$ is a feasible solution of $DQ$, by the corollary above, $Q$ being infeasible means $DQ$ is unbounded, that is, there is $(t^*,\lambda^*,\mu^*)$ such that
    
    $$
    c^T\mu^* - b^T\lambda^* <0,~ ct^* - A^T\lambda^* \ge 0,~ -bt^* + A\mu^* = 0,~t^*\ge 0,~\mu^*\ge 0.
    $$
    
    Now if $t^*>0$, these inequalities say that $(x,y)=(\mu^*/t^*,\lambda^*/t^*)$ is a feasible solution of the problem above, contradicting the assumption. So $t^*=0$. This means
    
    $$
    c^T\mu^* < b^T\lambda^*,~ A^T\lambda^*\le 0,~ A\mu^*=0,~\mu^*\ge 0.
    $$
    
    But we assumed that the primal and dual in the theorem are both feasible, that is, there is $(x_0,y_0)$ such that
    
    $$
    Ax_0 = b,~ x_0\ge 0,~ A^Ty_0\le c
    $$
    
    holds. Therefore
    
    $$
    0 = (A\mu^*)^Ty_0 = (A^Ty_0)^T\mu^* \le c^T\mu^* < b^T\lambda^* = x_0^TA^T\lambda^* \le 0.
    $$
    
    This is clearly a contradiction. The contradiction shows that $Q$ is feasible, and so strong duality holds.

The proof of the strong duality theorem also gives the following corollary:

???+ note "Corollary"
    Suppose feasible solutions $x^*$ and $y^*$ of the primal and dual satisfy strong duality, i.e., $c^Tx^* = b^Ty^*$. Then they are also optimal solutions of the primal and dual, respectively.

The strong duality theorem shows that for a feasible linear program, solving its dual is enough to get the optimal value of the primal.

### Complementary slackness

As with other optimization problems, complementary slackness is part of the optimality conditions for linear programs. Moreover, since the objective is linear, for linear programs complementary slackness is a necessary and sufficient condition for a feasible solution to be optimal.

The **complementary slackness** condition says that a variable in the dual (primal) can be nonzero only when the corresponding constraint in the primal (dual) holds with equality (that is, the constraint is tight). If we also think of "a variable being nonzero" as a slack constraint, this says that a variable and its corresponding constraint in the primal and dual cannot both be slack. That is why it is called complementary slackness.

For a linear program in standard form, the following holds:

???+ note "Theorem"
    Suppose $x^*$ and $y^*$ are feasible solutions of the primal $\min\{c^Tx:Ax=b,~x\ge 0\}$ and the dual $\max\{b^Ty:A^Ty\le c\}$, respectively. Then the complementary slackness condition, that is,
    
    $$
    (x^*)^T(A^Ty^*-c) = 0
    $$
    
    holds if and only if $x^*$ and $y^*$ are also optimal solutions of the primal and dual, respectively.

??? note "Proof"
    Since $x^*$ and $y^*$ are both feasible,
    
    $$
    b^Ty^* - c^Tx^* = (x^*)^T(A^T y^* - c).
    $$
    
    So complementary slackness holds if and only if $b^Ty^* = c^Tx^*$. By the corollary of the strong duality theorem, this holds if and only if $x^*$ and $y^*$ are optimal solutions of the primal and dual, respectively.

The standard form may be too special. A slightly more general form of the theorem is:

???+ note "Theorem"
    Suppose $x^*$ and $y^*$ are feasible solutions of the primal $\min\{c^Tx:Ax\ge b,~x\ge 0\}$ and the dual $\max\{b^Ty:A^Ty\le c,~y\ge 0\}$, respectively. Then the complementary slackness condition, that is,
    
    $$
    (x^*)^T(A^Ty^*-c) = (y^*)^T(Ax^*-b) = 0
    $$
    
    holds if and only if $x^*$ and $y^*$ are also optimal solutions of the primal and dual, respectively.

??? note "Proof"
    The proof is basically the same as above, except this time the difference is written as
    
    $$
    b^Ty^* - c^Tx^* = (x^*)^T(A^T y^* - c) - (y^*)^T(Ax^*-b).
    $$

Complementary slackness gives a simple test for whether a feasible solution of a linear program is optimal.

### Primal-dual method

The dual can help solve the primal. A method often used for linear programs is the **primal-dual method**. It solves a sequence of relatively simple auxiliary problems to improve a solution of the dual step by step, and in this way obtains an optimal solution of the primal.

For the primal problem in standard form

$$
(P)\qquad\min\{c^Tx : Ax=b\ge 0,~ x\ge 0\}
$$

and its dual

$$
(D)\qquad\max\{b^Ty : A^Ty\le c\},
$$

the previous section showed that to find optimal solutions, it is enough to find feasible solutions of $(P)$ and $(D)$ that satisfy complementary slackness $x^T(A^Ty-c)=0$. So consider the following procedure:

1.  Start from a feasible solution $y$ of the dual $(D)$ and compute the set of tight constraints of the dual

    $$
    I = \{i : (A^Ty - c)_i = 0\}.
    $$

2.  By complementary slackness, if there is a feasible solution $x$ of $(P)$ with $x_i>0$ only for $i\in I$, we have found optimal solutions. So consider the linear program

    $$
    (RP)\qquad
    \begin{aligned}
    \min_{x,s}\;& 1^Ts \\
    \text{subject to } & Ax + s = b, \\
    & x_i \ge 0,~\forall i \in I,\\
    & x_i = 0,~\forall i \notin I,\\
    & s \ge 0.
    \end{aligned}
    $$

3.  If the minimum of $(RP)$ is $0$, then in the optimal solution $(x^*,0)$, $x^*$ is an optimal solution of the primal $(P)$. Otherwise, we can find a solution $\bar y$ of its dual $(DRP)$:

    $$
    (DRP)\qquad
    \begin{aligned}
    \max_{y}\;& b^Ty \\
    \text{subject to }& \sum_{j}a_{ji}y_j \le 0,~\forall i\in I,\\
    & y \le 1.
    \end{aligned}
    $$

    By the strong duality theorem, $b^T\bar y = 1^Ts^*>0$.

4.  Use the solution of $(DRP)$ to improve the feasible solution of the dual $(D)$. Let $y' = y + \varepsilon \bar y$ with $\varepsilon>0$. Then $b^Ty' = b^Ty + \varepsilon b^T\bar y > b^Ty$. So we should choose $\varepsilon$ as large as possible while keeping $y'$ a feasible solution of the dual $(D)$.

    For $i\in I$,

    $$
    \sum_ja_{ji}y'_j = \sum_ja_{ji}y_j + \varepsilon \sum_ja_{ji}\bar y_j \le c_i,
    $$

    so these constraints of $(D)$ are always satisfied.

    For the remaining constraints, i.e., $i\notin I$, just take

    $$
    \varepsilon = \min\left\{\dfrac{c_i - \sum_{j}a_{ji}y_j}{\sum_{j}a_{ji}\bar y_j}:i\notin I,~\textstyle\sum_{j}a_{ji}\bar y_j>0\right\}
    $$

    This improves the dual solution as much as possible while keeping it feasible. Then go back to step 1 and repeat. In particular, if the set in the formula above is empty, i.e., $\varepsilon=+\infty$, the dual $(D)$ is unbounded and the primal $(P)$ is infeasible.

In this process, the only problem that really needs to be solved is $(DRP)$, which is linked to $(RP)$ by the strong duality theorem. $(DRP)$ gives a direction in which to improve the dual solution, and its form is simpler than the dual $(D)$ itself. $(DRP)$ is always feasible ($y=0$ is a feasible solution), and the constraint $y\le 1$ is only a normalization that keeps $(DRP)$ bounded.

In contests, the primal-dual method is widely used for all kinds of combinatorial optimization problems. For example, the [Hungarian algorithm](../graph/graph-matching/bigraph-weight-match.md#hungarian-algorithm-kuhnmunkres-algorithm) for maximum-weight bipartite matching, the [cycle-canceling algorithm](../graph/flow/min-cost.md) and the [SSP algorithm (primal-dual algorithm)](../graph/flow/min-cost.md#the-ssp-algorithm) for min-cost flow, [Dijkstra's algorithm](../graph/shortest-path.md#dijkstras-algorithm) for shortest paths, and the [Ford–Fulkerson augmenting path algorithm](../graph/flow/max-flow.md#fordfulkerson-augmentation) for maximum flow can all be seen as direct applications of the primal-dual method.

## Integer programming

**Integer programming** usually means **integer linear programming** (ILP). The standard form of an integer linear program is:

$$
\begin{aligned}
\min_{x}\; & c^Tx \\
\text{subject to } & Ax = b \ge 0,\\
& x \ge 0,\\
& x \in \mathbf Z^n,
\end{aligned}
$$

where $A\in\mathbf R^{m\times n}$, $b\in\mathbf R^m$, $c\in\mathbf R^n$. That is, an integer linear program is a linear program with the extra constraint that the decision variables must be integers.

The integer constraint makes integer programs much harder. Many combinatorial optimization problems, such as the knapsack problem, the satisfiability problem and many optimization problems in graph theory, can be written as integer programs, and most of these problems have been proven to be NP-hard.

### Totally unimodular matrices

For this reason, for many large integer optimization problems, people sometimes relax the integer constraints and solve a linear program instead. In general, the optimal value of the relaxed linear program is only a lower bound for the original integer program (assuming a minimization problem). But if an optimal solution of the relaxed linear program happens to be integral, it is also an optimal solution of the original integer program.

A natural question is whether there is a condition that guarantees the optimal solutions of a linear program are integral. The concept of a totally unimodular matrix gives such a condition.

???+ abstract "Totally unimodular matrix"
    If every square submatrix of a matrix $A\in\mathbf R^{m\times n}$ has determinant $0$ or $\pm 1$, then $A$ is called a **totally unimodular matrix**.

In particular, every entry of a totally unimodular matrix is $0$ or $\pm 1$. Using this concept, we can state the following result:

???+ note "Theorem"
    For a totally unimodular matrix $A\in\mathbf Z^{m\times n}$, $b\in\mathbf Z^{m}$ and $c\in\mathbf Z^n$, the linear program and its dual
    
    $$
    \min\{c^Tx : Ax=b,x\ge 0\} = \max\{b^Ty: A^Ty\le c\}
    $$
    
    both have integral optimal solutions, as long as they are bounded.

??? note "Proof"
    As shown earlier, the set of optimal solutions of a linear program can be taken to be one of its minimal faces, and a minimal face is the solution set of a system of equations formed from some linearly independent tight constraints:
    
    $$
    \{x\in\mathbf R^n : a_j^Tx = b_j,~\forall j\in J\}.
    $$
    
    Write this system as $A_Jx=b_J$ with $A_J=(A_1,A_2)$, where $A_1$ is a full-rank square matrix with determinant $\pm 1$. Then by Cramer's rule, the solution
    
    $$
    x = \begin{pmatrix}A_1^{-1}b_J \\ 0\end{pmatrix}
    $$
    
    is an integral solution on the minimal face.

In common graph models, the coefficient matrices of the linear programs for network flow, shortest paths, bipartite graphs and so on are all totally unimodular. So as long as these problems only involve integer parameters, their optimal solutions can be taken to be integral, and we do not need to worry about LP solutions that correspond to fractional flows, fractional matchings and the like. Therefore problems such as [maximum flow](../graph/flow/max-flow.md), [minimum cut](../graph/flow/min-cut.md), [min-cost flow](../graph/flow/min-cost.md), [shortest paths](../graph/shortest-path.md), [difference constraints](../graph/diff-constraints.md), and [maximum (weight) bipartite matching and minimum vertex cover](../graph/graph-matching/bigraph-match.md#linear-programming-formulation) can all be solved as linear programs. Moreover, maximum flow and minimum cut, shortest paths and difference constraints, and maximum bipartite matching and minimum vertex cover are pairs of dual problems.

There are also some common graph models whose feasible solutions are exactly all the vertices of some polytope whose vertices are all integer points. So by choosing the constraints cleverly, the solution of the combinatorial optimization problem is exactly an optimal solution of some linear program. General graph matching and spanning trees are examples of this, so problems such as [maximum (weight) matching in general graphs](../graph/graph-matching/general-weight-match.md) and [minimum spanning tree](../graph/mst.md) can also be turned into linear programs.

## References and notes

-   Schrijver, Alexander. Theory of linear and integer programming. John Wiley & Sons, 1998.
-   Papadimitriou, Christos H., and Kenneth Steiglitz. Combinatorial optimization: algorithms and complexity. Courier Corporation, 1998.
-   [Duality in linear programming. Part 1—definition and construction. by adamant - Codeforces blog](https://codeforces.com/blog/entry/105049)
-   [Duality in linear programming. Part 2—in competitive programming. by adamant - Codeforces blog](https://codeforces.com/blog/entry/105789)

[^poly-names]: Different sources may define these two terms differently: some call the bounded case a "polyhedron" and the unbounded case a "polytope"; some do not assume they are convex; some use "polyhedron" for polytopes in 3D space. This page uses definitions consistent with Schrijver (1998), Boyd and Vandenberghe (2004) and others.

[^reducible]: More precisely, they can be reduced to each other in polynomial time.

[^other-methods]: Other methods for solving systems of inequalities include Fourier–Motzkin elimination and the Agmon–Motzkin–Schoenberg relaxation method. They are more direct, but often less efficient.
