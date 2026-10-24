author: Ir1d, Catreap, TianyiQ, Tiphereth-A, Enter-tainer, Henry-ZHR, HeRaNO, iamtwz, ksyx, ouuan, sshwy, Xeonacid, GWBailang553

## Introduction

Given $n~(n\ge 1)$ points $P_1,P_2,\cdots,P_n$ in the plane, find a circle with the smallest radius such that no point lies outside it. This circle is called the **minimum enclosing circle** (MEC) of the points.

In this article we allow circles of radius $0$: when all points coincide at a single point $P$, we say the minimum enclosing circle of the $n$ points is the circle with center $P$ and radius $0$.

It is not hard to see that the minimum enclosing circle is unique.

??? note "Proof"
    Suppose there are two different minimum enclosing circles with centers $O_1,O_2$, both of radius $r$. Let $M$ be the midpoint of $O_1O_2$. Then for every point $P$,
    
    $$
    \begin{aligned}
        |P-M|^2&=\frac{|P-O_1|^2+|P-O_2|^2}{2}-\frac{|O_1-O_2|^2}{4}\\
        &\le r^2-\frac{|O_1-O_2|^2}{4}<r^2.
    \end{aligned}
    $$
    
    So we can build an enclosing circle with center $M$ and a smaller radius, a contradiction.
    
    ![](./images/smallest-enclosing-circle3.svg)

## How it works

The common way to solve the minimum enclosing circle problem is Welzl's algorithm[^welzl], which is based on the [randomized incremental method](random-incremental.md). Its core idea is: randomly shuffle the points first, then maintain the minimum enclosing circle of a point set while adding new points one by one. Although the algorithm has three nested loops, its expected time complexity is $O(n)$.

### Adding a point

First let's see what happens when we add a new point to the current set. Let the current circle $C$ be the minimum enclosing circle of the points processed so far, and now add point $P$.

-   If $P$ is inside $C$ or on its boundary, $C$ is still the minimum enclosing circle.
-   If $P$ is outside $C$, then $P$ must lie on the boundary of the new minimum enclosing circle. So the problem reduces to a subproblem: find the minimum enclosing circle given that $P$ is on its boundary.

??? tip "Why a new point outside the circle must be on the boundary of the new circle"
    Let the old and new circles have centers $O_0,O_1$ and radii $r_0,r_1$. Then $r_0\le r_1$. Suppose $P$ lies strictly inside the new circle. For $0<t<1$, consider the circle $(O_t,r_t)$ with
    
    $$
    O_t=(1-t)O_1+tO_0,\qquad r_t^2=(1-t)r_1^2+tr_0^2-t(1-t)|O_1-O_0|^2<r_1^2,
    $$
    
    and choose $t$ small enough that $P$ is still inside circle $(O_t,r_t)$. For any point $Q$, we have
    
    $$
    |Q-O_t|^2-r_t^2=(1-t)(|Q-O_1|^2-r_1^2)+t(|Q-O_0|^2-r_0^2).
    $$
    
    So the old points are still covered by circle $(O_t,r_t)$, and points that were fixed on the boundaries of both $(O_0,r_0)$ and $(O_1,r_1)$ are still on the boundary of $(O_t,r_t)$. Since $P$ is inside $(O_t,r_t)$, the circle $(O_t,r_t)$ is a valid enclosing circle, but $r_t<r_1$, contradicting the optimality of the new circle.
    
    ![](./images/smallest-enclosing-circle4.svg)

This result also holds when one or two points are already fixed on the boundary and a new point is added.

### Three nested loops

Now let's look at the main part of Welzl's algorithm. Randomly shuffle the input points uniformly, still calling them $P_1,P_2,\cdots,P_n$, and let $S_i=\{P_1,\cdots,P_i\}$, $S_0=\varnothing$. Maintain the current circle $C$; at the start, its center is $P_1$, its radius is $0$, and no point is fixed on its boundary.

1.  (Outer loop) No point fixed on the boundary: enumerate $i=2,\cdots,n$ in order. If $P_i$ is already in $C$, continue; otherwise fix $P_i$ on the boundary and recompute the smallest circle covering $S_{i-1}$.
2.  (Middle loop) One boundary point $P_i$ fixed: first set $C$ to the circle with diameter $P_iP_1$, then enumerate $j=2,\cdots,i-1$ in order. If $P_j$ is already in $C$, continue; otherwise also fix $P_j$ on the boundary and recompute the smallest circle covering $S_{j-1}$.
3.  (Inner loop) Two boundary points $P_i,P_j$ fixed: first set $C$ to the circle with diameter $P_iP_j$, then enumerate $k=1,\cdots,j-1$ in order. If $P_k$ is already in $C$, continue; otherwise update $C$ to the circumcircle of $\triangle P_iP_jP_k$.

Here "in the circle" always includes the boundary, and the current circle at each step is the **smallest circle** satisfying the corresponding constraints. When the inner loop ends, the circle covers $S_{j-1}$, and with $P_j$ on its boundary, it is exactly the answer the middle loop needs; likewise, when the middle loop ends, we get the answer the outer loop needs. The outer loops guarantee that the inner loops are feasible, and it is not hard to see that when the inner loop updates the circle, the three points $P_iP_jP_k$ are never collinear. So the algorithm is correct.

??? tip "Why the three points are never collinear when the inner loop updates the smallest circle"
    Since $P_j$ was once outside a circle passing through $P_i$, we have $P_i\ne P_j$. If $P_i,P_j,P_k$ are collinear and $P_k$ is outside the current circle $C$, then $P_k$ must lie outside segment $P_iP_j$. There are two cases:
    
    -   If $P_j$ lies between $P_i$ and $P_k$: when the middle loop reached $P_j$, the current smallest circle passed through $P_i$ and covered $P_k \in S_{j-1}$, so it also covered $P_j$ on segment $P_iP_k$. This contradicts $P_j$ triggering the inner loop.
    -   If $P_i$ lies between $P_j$ and $P_k$: when the outer loop reached $P_i$, the current smallest circle covered $P_j,P_k \in S_{i-1}$, so it also covered $P_i$ on segment $P_jP_k$. This contradicts $P_i$ triggering the middle loop.
    
    ![](./images/smallest-enclosing-circle5.svg)

### Computing the circumcircle

The geometric operations in Welzl's algorithm are fairly standard. There are three: testing whether a point is in a circle, the circle with two given points as diameter, and the circumcircle of three points. We skip the first two and focus on the third.

Given three non-collinear points $A=(x_A,y_A), B=(x_B,y_B), C=(x_C,y_C)$, their circumcenter is the intersection of the perpendicular bisectors of segments $AB$ and $AC$. You can compute it with the method in [Intersection point of two lines](./2d.md#intersection-point-of-two-lines).

You can also set up equations and solve them directly. Let the circumcenter be $O=(x,y)$. Then

$$
\begin{cases}
(x-x_A)^2+(y-y_A)^2=(x-x_B)^2+(y-y_B)^2,\\
(x-x_A)^2+(y-y_A)^2=(x-x_C)^2+(y-y_C)^2,
\end{cases}
$$

Let

$$
\begin{aligned}
A_1&=2(x_B-x_A),&B_1&=2(y_B-y_A),&C_1&=x_B^2+y_B^2-x_A^2-y_A^2,\\
A_2&=2(x_C-x_A),&B_2&=2(y_C-y_A),&C_2&=x_C^2+y_C^2-x_A^2-y_A^2,
\end{aligned}
$$

Then

$$
x=\frac{C_1B_2-C_2B_1}{A_1B_2-A_2B_1},\quad y=\frac{A_1C_2-A_2C_1}{A_1B_2-A_2B_1}.
$$

After finding the center, take $r=|O-A|$. A nonzero denominator $A_1B_2-A_2B_1$ means the three points are not collinear. When the three points are nearly collinear, the floating-point error of this method can be amplified, so be careful in practice.

### Example

Let $P_1=(-2,0)$, $P_2=(2,0)$, $P_3=(0,1)$, $P_4=(0,3)$. Let $C_i$ be the minimum enclosing circle after processing the first $i$ points. The figure below shows the results of the outer loop. The solid blue line is the current circle, the dashed gray line is the circle before the update, the solid orange point is the point added in this round, and hollow gray points are points not yet added.

![](./images/smallest-enclosing-circle1.svg)

At the start, the radius is $0$. After adding $P_2$, the current enclosing circle has $P_1P_2$ as its diameter. $P_3$ is inside the circle, so adding it changes nothing. $P_4$ is outside the circle, so we must recompute. After recomputing, the center is $(0,5/6)$ and the radius is $13/6$; $P_1,P_2,P_4$ are on the boundary and $P_3$ is inside.

Below we expand the recomputation for $i=4$. The orange point is the point being checked, and points with a purple outer ring are the boundary points fixed in this loop; their set is called $R$. The solid blue and dashed gray lines are the current circle and the circle from the previous step.

![](./images/smallest-enclosing-circle2.svg)

1.  $P_4$ is outside the old circle $C_3$, so we enter the middle loop.
2.  Fix $P_4$ and first take the circle with diameter $P_4P_1$. When checking $j=2$, we find $P_2$ is outside this circle, so we enter the inner loop.
3.  Fix $P_4,P_2$ and set the current circle to the one with diameter $P_4P_2$. When checking $k=1$, we find $P_1$ is still outside.
4.  Update to the circumcircle of $\triangle P_4P_2P_1$, which finishes the inner loop. Back in the middle loop, $P_3$ (for $j=3$) is already in the circle, so it is skipped, and we get $C_4$.

The temporary circles during recomputation only need to satisfy the constraints of the current subproblem, so they do not necessarily cover all points the outer level has already processed. For example, the circle in the second subfigure does not yet cover $P_2$, and the circle in the third subfigure does not yet cover $P_1$. That is exactly why we go into the next level or update to the circumcircle.

### Complexity analysis

From the structure, the worst-case time complexity of the algorithm is bounded by $O(n^3)$. But the random shuffle lowers the probability of entering the inner loops, bringing the expected time complexity down to $O(n)$.

The minimum enclosing circle is determined by at most three points: if there is only one distinct point, the radius is $0$; otherwise, the circle is determined by a pair of diameter endpoints or by three non-collinear points. With one boundary point fixed, at most two more points are needed to determine the optimal solution.

??? tip "Why at most two more points are needed after fixing one boundary point"
    Translate the fixed point to the origin. Let the center vector be $\vec{u}$; then the radius of the circle is $|\vec{u}|$. A point $x$ is covered if and only if
    
    $$
    |\vec{x}-\vec{u}|^2\le |\vec{u}|^2\iff 2\vec{u}\cdot \vec{x}\ge |\vec{x}|^2.
    $$
    
    Each point other than the origin puts a half-plane constraint on the center. Feasible centers lie in the [intersection of these half-planes](./half-plane.md), and the optimal center is the feasible point closest to the origin. In 2D, keeping at most two active constraints is enough to keep this closest point unchanged.[^note1] So besides the fixed point, keeping at most two more input points is enough to keep the optimal solution unchanged.
    
    In the figure below, the blue region $H$ is the set of all feasible centers, and the orange point $\vec{u}_*$ is the one closest to the origin. Removing the constraints of the gray boundaries does not change the optimal center.
    
    ![](./images/smallest-enclosing-circle6.svg)

Therefore, any point whose removal would change the optimal circle must belong to every such set of determining points. With no boundary point fixed, there are at most three such points; with one boundary point fixed, there are at most two.

Now we do a backward analysis. First fix $P_i$ and the unordered point set $S_j$ at some step of the middle loop. Since the initial order is random, $P_j$ is equally likely to be any point of $S_j$. Adding $P_j$ triggers the inner loop only if removing $P_j$ would change the constrained optimal circle, so the probability of triggering is at most $\min(1,2/j)$. The inner scan takes $O(j)$ time, so the expected time of the whole middle loop is

$$
O(1)+\sum_{j=2}^{i-1}\left(O(1)+\frac{2}{j}\cdot O(j)\right)=O(i).
$$

Similarly, fix the unordered point set $S_i$ of the outer loop. At most three points trigger a recomputation in the middle loop, so the probability is at most $\min(1,3/i)$. After fixing that point, the relative order of the earlier points is still random, so the conditional expected time of this recomputation is $O(i)$. Adding the cost of each test and of the initial shuffle, the total expected time complexity is

$$
O(n)+\sum_{i=2}^{n}\left(O(1)+\min\left(1,\frac{3}{i}\right)\cdot O(i)\right)=O(n).
$$

## Example problem

???+ note "[Luogu P1742 Minimum Enclosing Circle](https://www.luogu.com.cn/problem/P1742)"
    Given $N$ points, find the smallest circle containing all of them, and output its radius and the coordinates of its center.

The implementation below maintains the center and radius directly, and uses `std::shuffle` to shuffle the points. The three loops correspond to the subproblems above with zero, one and two fixed boundary points, and `geto` computes the circumcenter of three points.

??? note "Reference implementation"
    ```cpp
    --8<-- "docs/geometry/code/smallest-enclosing-circle/smallest-enclosing-circle_1.cpp"
    ```

## Exercises

-   [POI 2011 WYK-Plot](https://www.luogu.com.cn/problem/P3517)
-   [Library Checker - Minimum Enclosing Circle](https://judge.yosupo.jp/problem/minimum_enclosing_circle)

## References and notes

-   [Smallest-circle problem - Wikipedia](https://en.wikipedia.org/wiki/Smallest-circle_problem)
-   [Minimum Enclosing Circle - Algorithms for Competitive Programming](https://cp-algorithms.com/geometry/enclosing-circle.html)
-   [Computational Geometry Lecture 4: Smallest enclosing circles and more - University of Florida](https://www.cise.ufl.edu/~sitharam/COURSES/CG/kreveldnbhd.pdf)

[^welzl]: Welzl, E. (1991). Smallest enclosing disks (balls and ellipsoids). In: Maurer, H. (eds) New Results and New Trends in Computer Science. Lecture Notes in Computer Science, vol 555. Springer, Berlin, Heidelberg.

[^note1]: See [Linear programming](../math/linear-programming.md) for details.
