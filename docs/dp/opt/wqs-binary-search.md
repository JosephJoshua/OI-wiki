## Introduction

This article introduces how to optimize dynamic programming problems with WQS binary search. In different articles it is also called weighted binary search, convex optimization DP, convex totally monotone DP, the Lagrange multiplier method, and so on; outside China it is also known as the Aliens Trick. It was first summarized by Wang Qinshi in the paper "A Brief Analysis of a Class of Binary Search Methods".

WQS binary search is usually used for a class of optimization problems that come with a count constraint. Solving them directly is expensive, but once the constraint is removed, the problem becomes much easier.

For example, suppose the problem is to choose $m$ items out of $n$ and optimize some fairly complicated objective function. If $f(i,j)$ is the optimal objective value when choosing $j$ items from the first $i$ items, then the answer to the original problem is $f(n,m)$. In problems like this, the transition equation is usually two-dimensional. Implementing it directly takes $O(nm)$ time, which is too slow.

Now further suppose that the optimization problem without the count constraint is easy to solve. However, the optimal number of chosen items may not satisfy the count constraint of the original problem. Suppose too many items are chosen. Then we can add a fixed penalty $k$ to every chosen item (this is the "weight" in "weighted binary search") and still solve the problem without the count constraint. The optimal number of chosen items depends on $k$, and it changes monotonically as $k$ changes. So we can binary search for a $k$ that makes the optimal number of chosen items exactly $m$. If the optimal objective value is then $f_k(n)$, we just remove the loss caused by the extra penalty to get the answer to the original problem: $f(n,m)=f_k(n)-km$. If solving the penalized problem once takes $O(T(n))$ time, the whole algorithm takes $O(T(n)\log L)$ time, where $O(\log L)$ is the number of binary search steps on $k$.

That is the basic idea of WQS binary search. But it only works if $f(n,m)$ is convex in $m$. Otherwise there may be no penalty $k$ that makes the optimal count exactly $m$. This is also why this DP optimization is often called "convex optimization DP" or "convex totally monotone DP".

## The traditional method

Let the nonempty set $X$ be the (finite) decision space, $f:X\rightarrow\mathbf R$ the objective function, and $g:X\rightarrow\mathbf R^d$ another function used to impose constraints. The problem we want to solve can be seen as evaluating, at some point, the value function $v(y)$ of the following optimization problem:

$$
\begin{aligned}
v(y)=\min_{x\in X}\;&f(x)\\
\text{subject to }&g(x)=y.
\end{aligned}
$$

For example, for the count-constrained problem mentioned above, $X$ can be seen as the family of all subsets of the item set, $x\in X$ is one subset, $f(x)$ is the value of that subset, and $g(x)$ is the number of elements in subset $x$. Of course, $g(x)$ does not have to be a count constraint; later sections give examples of more general constraints.

???+ info "Convention"
    For convenience, this article only discusses minimization problems. Maximization problems are similar; just replace the (downward) convex functions in this article with concave functions (also called upward convex functions). Alternatively, by adding a minus sign, a maximization problem can be turned into minimizing the negated objective.

### Geometric intuition

Most problems in competitive programming are combinatorial optimization problems, so the decision space $X$ usually has no nice structure. Instead, we can look at the set

$$
\mathcal D = \{(g(x),f(x))\in\mathbf R^d\times\mathbf R:x\in X\}.
$$

The traditional method mainly handles the case $d=1$, that is, a single constraint. The figure below shows one possible picture of the point set $\mathcal D$ in this case.

![](../images/wqs-binary-search/wqs-f-g-space.svg)

The red and blue points in the figure form the set $\mathcal D$, obtained by projecting every possible choice in $X$ onto the plane $(g(x),f(x))$. The original problem then asks for $v(y)$, the minimum y-coordinate among the points whose x-coordinate is $y$. As $y$ varies, all such points $(y,v(y))$ form the set of red points in the figure.

To find the y-coordinate of the point $(y,v(y))$, we can cut the set $\mathcal D$ with a line of slope $\lambda\in\mathbf R$. As the figure shows, when the slope is chosen well, the line through $(y,v(y))$ has the smallest intercept $f(x)-\lambda g(x)$ among all lines of slope $\lambda$ that pass through a point of $\mathcal D$. Denote this minimum by

$$
h(\lambda) = \min_{x\in X}f(x)-\lambda g(x).
$$

Then, since $(y,v(y))$ also lies on this line, we get the solution of the original problem:

$$
v(y) = h(\lambda) + \lambda y.
$$

Suppose $h(\lambda)$ is easy to compute for every $\lambda$ in a reasonable range. This is often true in competitive programming, because it removes the constraint of the original problem. Then the two most important questions are:

1.  Is there a slope $\lambda$ such that the minimum intercept is attained exactly at the point $(y,v(y))$? And
2.  If so, how do we find such a slope $\lambda$?

The first question is relatively easy. As the slope $\lambda$ changes, the region cut out by all these lines (that is, the intersection of their upper half-planes) is always a convex set. So these lines can pass through a point if and only if the point lies on the lower convex hull of that convex set. This is equivalent to saying that the function $v(y)$ is a [convex function](./slope-trick.md#convex-functions-on-discrete-point-sets).

The second question is more subtle. Since we already know the x-coordinate of the target point is $y$, a natural idea is to also compute, while computing $h(\lambda)$, the value of the constraint function $g(x)$ at the current optimal solution $x_\lambda$. For example, in the example above, when solving the penalized problem, we can record how many items are chosen in the optimal solution of the penalized objective. Then we compare $g(x_\lambda)$ with the desired $y$ and adjust $\lambda$ for the next computation accordingly. This is the most traditional form of WQS binary search.

To sum up, the basic process of traditional WQS binary search is:

1.  At the start, choose a reasonable interval for $\lambda$;
2.  Pick a $\lambda$ in the current interval;
3.  Solve the penalized problem $h(\lambda)=\min_{x\in X}f(x)-\lambda g(x)$, and record the value $g(x_\lambda)$ of $g(x)$ at its optimal solution $x_\lambda$;
4.  If $g(x_\lambda)=y$, we get the optimal value of the original problem $v(y)=h(\lambda)+\lambda y$ and stop;
5.  Otherwise, adjust the interval of $\lambda$ according to whether $g(x_\lambda)$ is larger or smaller than $y$, and go back to step 2.

This basic process is already enough for some problems, but it is not complete. Next, this article discusses improvements to it.

### Handling collinear points

When applying the basic process, the first problem is that it cannot correctly handle collinear points.

If three or more red points on the lower convex hull of $\mathcal D$ are collinear, the basic process above may misjudge whether $g(x_\lambda)$ is larger or smaller than $y$. For example, let the x-coordinates of three collinear red points be $y_1,y_2,y_3$, and let the slope of the line through them be $\lambda^*$. To compute $v(y_2)$ correctly, the last problem solved when the algorithm stops must be $h(\lambda^*)$, because $\lambda^*$ is the only slope for which the minimum-intercept line passes through $(y_2,v(y_2))$. But when solving $h(\lambda^*)$, the recorded $g(x_{\lambda^*})$ may be any of $y_1,y_2,y_3$. If the recorded $g(x_{\lambda^*})$ is not $y_2$, the algorithm wrongly keeps going and moves the interval of $\lambda$ away from $y_2$, ending with a wrong result.

One way to handle collinear points is to always make the recorded $g(x_\lambda)$ of the optimal solution $x_\lambda$ as large as possible (or as small as possible). At the same time, change the stopping condition of the binary search: instead of looking for a $\lambda$ with exactly $g(x_\lambda)=y$, look for the smallest (or largest) $\lambda$ with $g(x_\lambda)\ge y$ (or $g(x_\lambda)\le y$). In the example of the previous paragraph, this means that when solving $h(\lambda^*)$, the output $g(x_{\lambda^*})$ is $y_3$. This guarantees that the last problem solved when the algorithm stops is $h(\lambda^*)$. When implementing this, note that the final output is not $h(\lambda)+\lambda g(x_{\lambda})$ but $h(\lambda)+\lambda y$, because the recorded $g(x_\lambda)$ is not necessarily equal to the actual constraint $y$.

Another way is binary search over real numbers. If all numbers in the problem are integers, the slopes in WQS binary search are clearly integers too. Real numbers are introduced so that if the correct choice $\lambda^*$ is wrongly excluded, the fractional part can bring the search back, and it finally converges to the correct answer $\lambda^*$. For example, in the example above, if the recorded $g(x_{\lambda^*})$ when solving $h(\lambda^*)$ is $y_1$, which is smaller than the desired $y_2$, the algorithm then considers the interval $(\lambda^*,\lambda_r]$, where $\lambda_r$ is the right end of the current interval of $\lambda$. In the integer case, this interval would really be $[\lambda^*+1,\lambda_r]$, which rules out ever getting close to the correct answer $\lambda^*$ later. With real numbers, though, the interval is still $(\lambda^*,\lambda_r]$, and for any $\lambda$ in it, the recorded $g(x_\lambda)$ when solving $h(\lambda)$ is always at least $y_3$, and so strictly greater than $y_2$. So as the algorithm continues, it keeps discarding the right half, and the final range of $\lambda$ is guaranteed to be near $\lambda^*$. Of course, since we know the target slope is an integer, the real-number binary search does not need high precision when it stops: it only needs the interval to contain a single integer, and that integer is the $\lambda^*$ we want.

Once collinear points are handled correctly, WQS binary search can solve the vast majority of WQS binary search problems you will meet in competitive programming. But the method still has shortcomings: it cannot handle cases where $g(x_\lambda)$ is hard to record, nor cases in higher-dimensional WQS binary search where several points are coplanar. This article now looks further into the properties of the optimization problem $v(y)$ and proposes a more general approach.

## The dual method

This section introduces a way to implement WQS binary search that only requires that, for every $\lambda\in\mathbf R^d$, we can efficiently compute

$$
h(\lambda) = \min_{x\in X}f(x)-\lambda\cdot g(x)
$$

and that the optimal value $v(y)$ of the original problem is a convex function of $y\in\mathbf R^d$[^high-d-convex]. In one sentence, this section proves that the value function $v(y)$ of the original problem equals the optimal value of its dual problem

$$
v^\star(y) = \sup_{\lambda\in\mathbf R^d} h(\lambda)+\lambda\cdot y,
$$

and the objective function of the dual problem is concave in $\lambda\in\mathbf R^d$, hence unimodal. It can be solved efficiently with [ternary search](../../basic/binary.md#ternary-search) or [golden-section search](../../basic/binary.md#optimization-golden-section-search), and the complexity is still $O(T(n)\log^d L)$. This completely removes the problems that can arise from recording $g(x_\lambda)$ in the traditional WQS binary search method, and it also lets the idea of WQS binary search be applied in higher dimensions.

This section also shows that the range of $g(x_\lambda)$ can be obtained from $h(\lambda)$, without recording anything extra while solving $h(\lambda)$. For example, when $d=1$ and the problem only involves integers, one can prove that the range of values of $g(x_\lambda)$ is exactly

$$
[h(\lambda-1)-h(\lambda),h(\lambda)-h(\lambda+1)].
$$

For problems that must use the binary search process described earlier, this actually gives yet another way to deal with collinear points.

Next, this section uses convex analysis to prove these claims. For concrete applications of these methods, see the [Example problems](#example-problems) section.

### Lagrange duality

Consider solving the problem with the [Lagrange multiplier method](https://en.wikipedia.org/wiki/Lagrange_multiplier). Introduce the Lagrange multiplier $\lambda\in\mathbf R^d$. Then the Lagrangian can be written as

$$
L(x,\lambda,y) = f(x) - \lambda\cdot g(x)+\lambda\cdot y.
$$

If any component of $g(x)-y$ is nonzero, we can send the corresponding component of $\lambda$ to (positive or negative) infinity, so

$$
\sup_{\lambda\in\mathbf R^d}L(x,\lambda,y)
= \begin{cases}
f(x),&g(x)=y,\\
+\infty,&\text{otherwise}.
\end{cases}
$$

This shows that the original problem can be written as

$$
\begin{aligned}
v(y) &= \min_{x\in X}\sup_{\lambda\in\mathbf R^d}L(x,\lambda,y).
\end{aligned}
$$

Swapping the two extremum operations gives its [dual problem](https://en.wikipedia.org/wiki/Duality_%28optimization%29):

$$
\begin{aligned}
v^\star(y)&=\sup_{\lambda\in\mathbf R^d}\min_{x\in X}L(x,\lambda,y)\\
&=\sup_{\lambda\in\mathbf R^d}h(\lambda)+\lambda\cdot y.
\end{aligned}
$$

We will show shortly that when $v(y)$ is a convex function of $y$, strong duality holds, that is, $v^\star(y)=v(y)$.

### Convex conjugate

To show that strong duality holds, we need the concept of the convex conjugate.

???+ abstract "Convex conjugate"
    For a function $f:\mathbf R^d\rightarrow\mathbf R\cup\{\pm\infty\}$, its **convex conjugate**, also called the **Legendre–Fenchel transformation**, is the function
    
    $$
    f^*(x^*) = \sup_{x\in\mathbf R^d}x^*\cdot x - f(x).
    $$

As a function of $x^*$, $f^*(x^*)$ is the supremum of a family of linear functions, so it is always a convex function on $\mathbf R^d$.

???+ info "The \"slope vector\" and \"intercept\" of a hyperplane"
    Every hyperplane in the vector space $\mathbf R^{d+1}$ discussed in this article has an equation of the form
    
    $$
    y = k\cdot x + b.
    $$
    
    That is, this article never deals with hyperplanes parallel to the $y$ axis. For convenience, and somewhat loosely, this article calls $k$ the "slope vector" of the hyperplane and $b$ its "intercept". Written in a more standard form, the equation of this hyperplane is
    
    $$
    k\cdot x - y = -b.
    $$
    
    One of its normal vectors is $(k,-1)$. So the so-called slope vector is just the first $d$ components of the normal vector, after normalizing it so that its last component equals $-1$.

Geometrically, the convex conjugate of $f(x)$ describes the following: among all hyperplanes with slope vector $x^*$ that intersect the epigraph of $f(x)$

$$
\operatorname{epi}f = \{(x,y)\in\mathbf R^d\times\mathbf R:f(x)\le y\}
$$

the minimum intercept $f(x)-x^*\cdot x$ is $-f^*(x^*)$. In other words, the function $f(x)$ always lies above the hyperplane $y = x^*\cdot x-f^*(x^*)$ and touches it at the point $(x_0,f(x_0))$; of course, there may be other points of contact. Such a hyperplane is called a **supporting hyperplane** of $f(x)$ at $x_0$. The intercept of a supporting hyperplane of $f(x)$ is uniquely determined by its slope vector, and the convex conjugate is exactly this map from slope vectors to intercepts.

Minimizing $f(x)-\lambda\cdot g(x)$ over the set $X$ is equivalent to minimizing $v(y)-\lambda\cdot y$ over the set $\{(y,v(y))\}$:

$$
\begin{aligned}
\min_x f(x)-\lambda\cdot g(x) &= \min_{y\in g(X)}\left(\min_{x\in X:g(x)=y} f(x) - \lambda\cdot g(x)\right)\\
&= \min_{y\in g(X)}\left(\min_{x\in X:g(x)=y} f(x)\right) - \lambda\cdot y \\
&= \min_{y\in g(X)}v(y) - \lambda\cdot y.
\end{aligned}
$$

Therefore

$$
h(\lambda) = \min_{y\in g(X)}v(y) - \lambda\cdot y = -v^*(\lambda).
$$

This shows that $h(\lambda)$ is a concave function of $\lambda\in\mathbf R^d$. Moreover,

$$
v^\star(y) = \sup_{\lambda\in\mathbf R^d}\lambda\cdot y-v^*(\lambda) = v^{**}(y).
$$

That is, the value function $v^{\star}(y)$ of the dual problem is the convex conjugate applied twice to the value function $v(y)$ of the original problem, also called the **biconjugate**.

So the question becomes: which functions $v(y)$ are equal to their own biconjugate? The answer is given by the following theorem:

???+ note "Theorem (Fenchel–Moreau)"
    For a function $f:\mathbf R^d\rightarrow\mathbf R\cup\{\pm\infty\}$, its biconjugate equals itself, i.e. $f^{**}=f$, if and only if one of the following three conditions holds:
    
    1.  $f(x)$ is a proper convex function and is [lower semicontinuous](https://en.wikipedia.org/wiki/Semi-continuity),
    2.  $f(x)\equiv+\infty$, or
    3.  $f(x)\equiv-\infty$.

??? note "Proof"
    A function is proper if and only if it never takes the value $-\infty$ and is not identically $+\infty$.
    
    For improper functions, one can check that $f(x)\equiv+\infty$ and $f(x)\equiv-\infty$ are conjugates of each other. Apart from these, if $f(x)$ takes the value $-\infty$ at any point, then necessarily $f^*(x^*)\equiv+\infty$. So these two are the only improper functions with $f^{**}=f$. The discussion below is limited to proper functions. For a proper function, being lower semicontinuous and convex is equivalent to its epigraph being a closed convex set.
    
    Necessity is easy. Since $f=f^{**}$ is the convex conjugate of $f^*$, it is the supremum of a family of linear functions, so its epigraph is an intersection of closed convex sets and hence a closed convex set. This shows that a proper function with $f^{**}=f$ must be lower semicontinuous and convex.
    
    Conversely, these conditions are also sufficient. As with the proofs of other strong duality theorems, the proof has two steps.
    
    Step one: show weak duality, i.e. $f(x)\ge f^{**}(x)$. By the definition of the convex conjugate, for all $x,x^*\in\mathbf R^d$,
    
    $$
    f^*(x^*) \ge x^*\cdot x-f(x).
    $$
    
    So for all $x,x^*\in\mathbf R^d$ we also have
    
    $$
    f(x) \ge x^*\cdot x-f^*(x^*).
    $$
    
    Taking the supremum over $x^*$ on the right-hand side gives $f(x)\ge f^{**}(x)$.
    
    Step two: use the [hyperplane separation theorem](https://en.wikipedia.org/wiki/Hyperplane_separation_theorem) to show $f(x)\le f^{**}(x)$. Suppose not: there is $x_0\in\mathbf R^d$ with $f(x_0)>f^{**}(x_0)$. The epigraph $\operatorname{epi}(f)$ of $f(x)$ is a closed convex set, and the single-point set $\{(x_0,f^{**}(x_0))\}$ is a compact convex set. So by the hyperplane separation theorem, there exist $(\lambda,t)\in\mathbf R^d\times\mathbf R$ and $\alpha\in\mathbf R$ such that for all $x\in\operatorname{dom} f:=\{x\in\mathbf R^d:f(x)<+\infty\}$ and all $y\ge f(x)$,
    
    $$
    \lambda\cdot x-ty <\alpha <\lambda\cdot x_0 - tf^{**}(x_0)
    $$
    
    holds. Since $y$ can be chosen arbitrarily large, we must have $t\ge 0$. There are two cases.
    
    First, the case $t>0$. Divide every part of the inequality by $t$ and set $\lambda'=t^{-1}\lambda$ and $\alpha'=t^{-1}\alpha$. This gives
    
    $$
    \lambda'\cdot x-y < \alpha'< \lambda'\cdot x_0-f^{**}(x_0).
    $$
    
    For every $x\in\operatorname{dom} f$, setting $y=f(x)$ gives
    
    $$
    \alpha' > \lambda'\cdot x - f(x).
    $$
    
    So, taking the supremum over $x$ on the right-hand side,
    
    $$
    \alpha' \ge \sup_{x\in\mathbf R^d}\lambda'\cdot x - f(x) = f^*(\lambda').
    $$
    
    Then
    
    $$
    f^{**}(x_0) < \lambda'\cdot x_0-f^*(\lambda') \le \sup_{x^*\in\mathbf R^d}x^*\cdot x_0-f^*(x^*) = f^{**}(x_0).
    $$
    
    This contradiction shows that the case $t>0$ is impossible.
    
    Finally, the case $t=0$. In fact, we will show that a small perturbation turns it into the case $t>0$. Take any $\lambda_0\in\operatorname{dom}f^*$. By the definition of the convex conjugate, for any $x\in\operatorname{dom}f$ and $y\ge f(x)$,
    
    $$
    \lambda_0\cdot x-y\le f^*(\lambda_0).
    $$
    
    So for any $\varepsilon>0$,
    
    $$
    (\lambda+\varepsilon\lambda_0)\cdot x - \varepsilon y<\alpha+\varepsilon f^*(\lambda_0).
    $$
    
    At the same time, since $\alpha<\lambda\cdot x_0$, for small enough $\varepsilon>0$ we also have
    
    $$
    \alpha+\varepsilon f^*(\lambda_0) < (\lambda+\varepsilon\lambda_0)\cdot x_0 - \varepsilon f^{**}(x_0).
    $$
    
    So if we take $\lambda'=\lambda+\varepsilon\lambda_0$, $t'=\varepsilon$ and $\alpha'=\alpha+\varepsilon f^*(\lambda_0)$, then
    
    $$
    \lambda'\cdot x-t'y <\alpha' <\lambda'\cdot x_0 - t'f^{**}(x_0).
    $$
    
    This brings us back to the previous case, which still leads to a contradiction.
    
    This contradiction shows that there is no point $x_0\in\mathbf R^d$ with $f(x_0)>f^{**}(x_0)$. So we always have $f(x_0)\le f^{**}(x_0)$.
    
    Combining the two steps, we get $f^{**}(x)=f(x)$.

Therefore strong duality holds if and only if $v(y)$ is a convex function of $y\in\mathbf R^d$[^other-conditions].

### Subgradients

The previous section showed that the value function $h(\lambda)$ of the penalized problem is the negative of the convex conjugate of the value function $v(y)$ of the original problem. Since the definition of the convex conjugate is really a parametric optimization problem, a result similar to the [envelope theorem](https://en.wikipedia.org/wiki/Envelope_theorem) also holds for it. But convex functions are not differentiable everywhere, so we first need to extend the definition of the derivative to convex functions. This leads to the concept of subgradients.

???+ abstract "Subgradient"
    For a convex function $f:\mathbf R^d\rightarrow\mathbf R\cup\{\pm\infty\}$ and $x_0\in\operatorname{dom}f$, if a vector $x^*\in\mathbf R^d$ satisfies, for every $x\in\mathbf R^d$,
    
    $$
    f(x) \ge f(x_0)+x^*\cdot(x-x_0),
    $$
    
    then $x^*$ is called a **subgradient** of $f(x)$ at $x_0$. The set of all subgradients of $f(x)$ at $x_0$ is called its **subdifferential** there, written $\partial f(x_0)$.

Geometrically, the subdifferential of a convex function $f(x)$ at $x_0$ is the set of slope vectors of all its supporting hyperplanes at that point. In one dimension, the subdifferential is

$$
\partial f(x_0) = [\partial_-f(x_0),\partial_+f(x_0)],
$$

where $\partial_-f(x_0)$ and $\partial_+f(x_0)$ are the left and right derivatives of $f(x)$ at $x_0$. Further, for the function $\tilde f(x)$ extended from a convex function on the integers $f:\mathbf Z\rightarrow\mathbf R\cup\{\pm\infty\}$, its left and right derivatives at an integer point $x=k$ are the first differences on the left and right:

$$
\partial\tilde f(k) = [f(k)-f(k-1),f(k+1)-f(k)]. 
$$

Clearly, a convex function $f(x)$ is differentiable at $x_0$ if and only if its subdifferential $\partial f(x_0)$ there is a single point.

Since the convex conjugate maps the slope vector of a supporting hyperplane to its intercept, we can use the convex conjugate to tell whether a slope vector $x^*$ is a subgradient of a convex function $f(x)$ at a given point $x$.

???+ note "Theorem (convex conjugates and subgradients)"
    For a proper convex function $f:\mathbf R^d\rightarrow\mathbf R\cup\{\pm\infty\}$ and any $x,x^*\in\mathbf R^d$,
    
    $$
    x^*\in\partial f(x) \iff x^*\cdot x = f(x) + f^*(x^*).
    $$
    
    Moreover, if $f$ is also lower semicontinuous, both conditions are equivalent to $x\in\partial f^*(x^*)$.

??? note "Proof"
    By the definition of a subgradient, $x^*\in\partial f(x)$ if and only if
    
    $$
    f(x') \ge f(x) + x^*\cdot(x'-x),~\forall x'\in\mathbf R^d.
    $$
    
    This is equivalent to
    
    $$
    x^*\cdot x - f(x) \ge x^*\cdot x'-f(x'),~\forall x'\in\mathbf R^d.
    $$
    
    This in turn is equivalent to
    
    $$
    x^*\cdot x - f(x) \ge \sup_{x'\in\mathbf R^d}x^*\cdot x'-f(x') = f^*(x^*).
    $$
    
    But by the definition of the convex conjugate, we always have
    
    $$
    x^*\cdot x - f(x) \le f^*(x^*).
    $$
    
    So the "greater than or equal" sign in the previous inequality is really an equality, which is equivalent to
    
    $$
    x^*\cdot x = f(x) + f^*(x^*).
    $$
    
    This completes the proof of the first part.
    
    When $f$ is a lower semicontinuous proper convex function, the Fenchel–Moreau theorem gives $f^{**}=f$. So both conditions are equivalent to
    
    $$
    x^*\cdot x = f^*(x^*) + f^{**}(x).
    $$
    
    Applying the first part again, they are also equivalent to $x\in\partial f^*(x^*)$.

This result shows that if $f^{**}=f$, then the subdifferential $\partial f^{*}(x^*)$ of the convex conjugate $f^*$ at $x^*$ is exactly the set of $x$ components of the points where the supporting hyperplane with slope vector $x^*$ meets the epigraph $\operatorname{epi}f$.

???+ note "Corollary"
    For a lower semicontinuous proper convex function $f:\mathbf R^d\rightarrow\mathbf R\cup\{\pm\infty\}$ and any $x,x^*\in\mathbf R^d$,
    
    $$
    \begin{aligned}
    \partial f(x) &= \arg\max_{y^*\in\mathbf R^d} x\cdot y^* - f^*(y^*),\\
    \partial f^*(x^*) &= \arg\max_{y\in\mathbf R^d} x^*\cdot y - f(y).
    \end{aligned}
    $$

??? note "Proof"
    We prove the second equality below. The proof of the first is similar.
    
    By the definition of the convex conjugate,
    
    $$
    f^*(x^*) = \sup_{y\in\mathbf R^d} x^*\cdot y - f(y),
    $$
    
    so
    
    $$
    x \in \arg\max_{y\in\mathbf R^d} x^*\cdot y - f(y)
    $$
    
    holds if and only if $f^*(x^*) = x^*\cdot x - f(x)$, and this equality holds if and only if $x\in\partial f^*(x^*)$. This proves that the two sets are equal.

Applied to our setting, this result says that when solving the problem

$$
h(\lambda) = \min_{x\in X}f(x)-\lambda\cdot g(x) = \min_{y\in g(X)}v(y) - \lambda\cdot y
$$

the values of the constraint function $g(x)$ over the set of optimal decisions are exactly $\partial(-h(\lambda))$. When $d=1$ and the problem only involves integers, this set is the interval

$$
[h(\lambda-1)-h(\lambda),h(\lambda)-h(\lambda+1)].
$$

For consecutive integers $\lambda$, these intervals join end to end, so when using them in binary search, we only need to compute one endpoint.

## Proving convexity

The precondition for applying WQS binary search is that the value function is convex. In competitive programming, you can guess that convexity holds by printing tables of values, by intuition, and so on. But proving convexity rigorously is often not easy. Using the classic problem below, this section introduces the common ways to prove convexity in competitive programming.

???+ example "Tree planting problem"
    There are $n$ pits, and $m$ trees must be planted. Trees cannot be planted in two adjacent pits. You are given a sequence $\{a_i\}$ of length $n$, the profit of planting a tree in each pit; profits may be positive or negative. Find the maximum possible total profit after planting all $m$ trees.
    
    In short, this is the problem of finding a maximum-weight independent set of size $m$ on a path of length $n$.

These methods can be roughly divided into four kinds:

-   Reduce to the convexity of the value function of a convex optimization problem (such as [linear programming](../../math/linear-programming.md)) with respect to its parameters. This includes methods such as building a [min-cost flow](../../graph/flow/min-cost.md) model;
-   Prove convexity by induction using the transition equations, possibly with some [convexity-preserving transformations](./slope-trick.md#transformations-of-convex-functions);
-   For interval partition problems, check that the cost function of each interval satisfies the [quadrangle inequality](./quadrangle.md);
-   Finally, for special problems, convexity can also be shown directly with an exchange argument.

Each of these proof methods is usually tied to some way of solving the problem.

### Reducing to parametric convex optimization

Consider a parametric convex optimization problem of the form:

$$
v(y)=\inf_{x\in\mathcal D(y)} f(x,y).
$$

Here the objective function $f:\mathbf R^m\times\mathbf R^d\rightarrow\mathbf R\cup\{\pm\infty\}$ is a convex function of $x\in\mathbf R^m$ for each $y\in\mathbf R^d$, and the feasible region $\mathcal D:\mathbf R^d\rightarrow \mathcal P(\mathbf R^m)$ is a set-valued function on $\mathbf R^d$ such that $\mathcal D(y)$ is a convex set for each $y\in\mathbf R^d$. These conditions ensure that for any parameter $y\in\mathbf R^d$, this is a convex optimization problem.

???+ note "Theorem"
    Suppose the parametric convex optimization problem above satisfies:
    
    1.  The objective function $f(x,y)$ is a convex function of $(x,y)$;
    2.  The graph $\{(x,y):x\in\mathcal D(y)\}$ of the feasible-region map $y\mapsto\mathcal D(y)$ is a convex set.
    
    If $v(y)>-\infty$ for every $y\in\mathbf R^d$, then the value function $v(y)$ is a proper convex function of $y$.

??? note "Proof"
    For any $y_1,y_2\in\mathbf R^d$ and $\alpha\in(0,1)$, we need to prove
    
    $$
    v(\alpha y_1+(1-\alpha)y_2) \le \alpha v(y_1) + (1-\alpha) v(y_2).
    $$
    
    If $v(y_1)=+\infty$ or $v(y_2)=+\infty$, the right-hand side is $+\infty$ and the inequality holds trivially. Otherwise, $v(y_1)$ and $v(y_2)$ are both finite. For any $\varepsilon>0$ and $i=1,2$, there exists $x_i\in\mathcal D(y_i)$ with $f(x_i,y_i)< v(y_i)+\varepsilon$. By the convexity of the graph of the map $\mathcal D$,
    
    $$
    \alpha x_1+(1-\alpha)x_2 \in \mathcal D(\alpha y_1+(1-\alpha)y_2).
    $$
    
    That is, $\alpha x_1+(1-\alpha)x_2$ is a feasible solution of the optimization problem with parameter $\alpha y_1+(1-\alpha)y_2$. By optimality and the convexity of the objective function,
    
    $$
    \begin{aligned}
    v(\alpha y_1+(1-\alpha)y_2)
    &\le f(\alpha x_1+(1-\alpha)x_2,\alpha y_1+(1-\alpha)y_2) \\
    &\le \alpha f(x_1,y_1) + (1-\alpha)f(x_2,y_2) \\
    &< \alpha v(y_1) + (1-\alpha) v(y_2) + \varepsilon.
    \end{aligned}
    $$
    
    Since $\varepsilon$ was arbitrary, letting $\varepsilon\rightarrow 0$ gives
    
    $$
    v(\alpha y_1+(1-\alpha)y_2) \le \alpha v(y_1) + (1-\alpha) v(y_2).
    $$
    
    So the value function $v(y)$ is convex.

In competitive programming, the most common convex optimization problems are linear programs.

???+ note "Corollary"
    Let $c\in\mathbf R^n$, $A_1\in\mathbf R^{d_1\times n}$, $A_2\in\mathbf R^{d_2\times n}$, $y_1\in\mathbf R^{d_1}$, $y_2\in\mathbf R^{d_2}$. Consider the following parametric linear program:
    
    $$
    v(y_1,y_2)=\min_{x\in\mathbf R^n} c\cdot x \text{ subject to }A_1x\le y_1,A_2x=y_2,x\ge 0.
    $$
    
    Then the value function $v(y_1,y_2)$ is a convex function of $(y_1,y_2)$.

Whether the constraints are inequalities or equalities, the value function of a linear program is a convex function of the constraint parameters.

Many graph problems can be written as linear programs:

-   Network flow problems: maximum flow, minimum cut, min-cost flow;
-   Shortest path problems without negative cycles;
-   Maximum (weight) matching, minimum vertex cover and similar problems on bipartite graphs;
-   Maximum (weight) matching on general graphs;
-   The minimum spanning tree problem[^mst].

So the value functions of these problems are convex (or concave) functions of their parameters.

???+ warning "Integer constraints"
    When modeling real problems with graph models, there are usually hidden integer constraints, for example an edge is either chosen or not, or flows must be integers. So they can only be turned into integer linear programming (ILP) problems rather than linear programming (LP) problems. Since ILP problems are not convex optimization problems, their value functions are not necessarily convex in the parameters. Relaxing the integer constraints of an ILP gives an LP, but the LP may have no optimal solution that satisfies the integer constraints. So the optimal value of the relaxed LP may be strictly better than that of the ILP, and the two are not necessarily equivalent.
    
    The graph problems listed above can all be written as LPs without integer constraints. For some other problems, such as maximum independent set on general graphs, the integer constraints are necessary. Also, even if a graph problem can be written as an LP, adding extra linear constraints to it may break the equivalence between the ILP and the LP, so the constrained graph problem can no longer be written as a linear program.

For example, in the context of min-cost flow, there is a well-known result:

???+ note "Corollary"
    In the [min-cost flow model](../../graph/flow/min-cost.md), the minimum cost $v(m)$ is a convex function of the flow amount $m$.

??? note "Proof"
    Let $G=(V,E)$ be a directed graph, where edge $(i,j)$ has capacity $c_{ij}$ and cost $w_{ij}$ per unit of flow, and the source and sink are $s$ and $t$. Let the decision variables be $\{f_{ij}\}$, where $f_{ij}$ is the flow on edge $(i,j)\in E$. Then min-cost flow can be written as the following linear program:
    
    $$
    \begin{aligned}
    v(m)=\min_{\{f_{ij}\}}\;&\sum_{(i,j)\in E}w_{ij}f_{ij}\\
    \text{subject to }&\sum_{(j,i)\in E}f_{ji} - \sum_{(i,j)\in E}f_{ij} = 
    \begin{cases}
    -m, & i=s,\\
    m,  & i=t,\\
    0,  & \text{otherwise},
    \end{cases}
    ~\forall i\in V,\\
    &0\le f_{ij}\le c_{ij},~\forall (i,j)\in E.
    \end{aligned}
    $$
    
    So the minimum cost $v(m)$ is a convex function of the parameter $m$.

Many problems in competitive programming can be reduced to network flow or other graph problems, so the convexity of their value functions can be established in a similar way.

Using this method, we get the first convexity proof for the tree planting problem:

??? example "Convexity proof 1"
    The maximum profit of the tree planting problem can be obtained from the following maximum-cost maximum-flow model:
    
    -   From the source $s$, add an edge to vertex $r$ with capacity $m$ and cost $0$;
    -   From vertex $r$, add an edge to each odd vertex $i=1,3,\cdots,2\lceil n/2\rceil-1$ with capacity $1$ and cost $0$;
    -   From each even vertex $i=0,2,\cdots,2\lfloor n/2\rfloor$, add an edge to the sink $t$ with capacity $1$ and cost $0$;
    -   For each $i=1,\cdots,n$, add an edge from the odd one of $i-1$ and $i$ to the even one, with capacity $1$ and cost $a_i$.
    
    The final answer is the maximum cost found. If we convert this graph model into the corresponding linear program (see the proof of the corollary above for details), the total flow $m$ appears in the inequality that bounds the flow on edge $(s,r)$. By the corollary, the maximum cost $v(m)$ is a concave function of the flow amount $m$.
    
    With this cost flow model, the problem can be solved in $O(n\log n)$ time by simulating cost flow or by [regret greedy](../../basic/greedy.md#regret-approach).

### Using the transition equations

Although the transition equations do not give an efficient way to compute the answer, they can often be used to prove that the state function $f(i,j)$ is convex in the parameter $j$. Specifically, if we treat the function $f(i,\cdot)$ as the state at $i$, then the transition equation for $f(i,j)$ can be viewed as a recurrence for $f(i,\cdot)$, and we can prove by induction that every $f(i,\cdot)$ is convex. This way of proving convexity is more common in the setting of [Slope Trick DP optimization](./slope-trick.md), and that page also discusses common convexity-preserving transformations.

This method can also prove convexity for the tree planting problem:

??? example "Convexity proof 2"
    Let $f(i,j)$ be the maximum profit when $j$ trees are planted in the first $i$ pits. Consider the following transition equation:
    
    $$
    f(i,j) = \max\{f(i-1,j),f(i-2,j-1)+a_i\}.
    $$
    
    View this transition equation as a recurrence for the functions $f(i,\cdot)$. Since two different functions appear inside the max, it cannot be written as a supremal convolution. But we can still prove by induction that $f(i,\cdot)$ is concave.
    
    In fact, we need to prove two things by induction:
    
    -   $f(i,j)-f(i-2,j-1)$ is decreasing in $j$;
    -   $f(i,j)-f(i-1,j)$ is increasing in $j$.
    
    The base case is trivial. Suppose both hold for $i-1$ and all smaller natural numbers; we now prove them for $i$. We just check directly.
    
    First, by the induction hypothesis,
    
    $$
    f(i-1,j) - f(i-2,j-1) = (f(i-1,j)-f(i-3,j-1)) - (f(i-2,j-1)-f(i-3,j-1))
    $$
    
    is decreasing in $j$. So
    
    $$
    f(i,j) - f(i-2,j-1) = \max\{f(i-1,j) - f(i-2,j-1), a_i\}
    $$
    
    is decreasing in $j$, and
    
    $$
    f(i,j) - f(i-1,j) = \max\{0,a_i-(f(i-1,j) - f(i-2,j-1))\}
    $$
    
    is increasing in $j$. This completes the induction.
    
    Then
    
    $$
    f(i,j) - f(i,j-1) = (f(i,j)-f(i-2,j-1)) - (f(i,j-1) - f(i-1,j-1)) - (f(i-1,j-1) - f(i-2,j-1))
    $$
    
    is decreasing in $j$. This shows $f(i,j)$ is a concave function of $j$, so the value function $v(m)=f(n,m)$ is a concave function of $m$.
    
    A by-product of this proof is that for every $i$, there is a $p_i$ such that
    
    $$
    f(i,j) =
    \begin{cases}
    f(i-1,j), & j\le p_i,\\
    f(i-2,j-1) + a_i, & j> p_i.
    \end{cases}
    $$
    
    This means we can maintain the sequence $f(i,\cdot)$ directly with a balanced binary search tree, in $O(n\log^2n)$ time. The advantages are that it handles the general case with any spacing between trees, and that it gets all the values $v(m)$ at once.

### Quadrangle inequality

Another common kind of convex problem in competitive programming is the [interval partition problem](./quadrangle.md#interval-partition-problems). That page proves that if the cost function of a single interval satisfies the quadrangle inequality, then the minimum cost of partitioning into a limited number of intervals is a convex function of the number of intervals. That page also gives some ways to check whether a function $w(l,r)$ satisfies the quadrangle inequality. The most direct way is to compute its second-order mixed difference:

$$
\begin{aligned}
\Delta_l \Delta_r w(l,r) &= \Delta_l(w(l,r+1)-w(l,r)) \\
&= w(l+1,r+1)-w(l+1,r)-w(l,r+1)+w(l,r).
\end{aligned}
$$

The function $w(l,r)$ satisfies the quadrangle inequality if and only if $\Delta_l \Delta_r w(l,r)$ is non-positive. Intuitively, a function satisfying the quadrangle inequality usually means that growing an interval on both sides (moving the left end left and the right end right) has some kind of synergy.

The tree planting problem can also be viewed as an interval partition problem, and we can prove convexity by checking the quadrangle inequality.

??? example "Convexity proof 3"
    Add an $a_0$ in front of the profit sequence; it can be any value. Then the tree planting problem is equivalent to the interval partition problem of splitting the sequence $\{a_0,a_1,\cdots,a_n\}$ into $m$ segments, where the profit of each segment is
    
    $$
    w(l,r) = \max_{i\in[l+1,r]} a_i
    $$
    
    That is, the profit of each segment is the maximum profit among its trees other than the first one. This guarantees that trees are not adjacent.
    
    Since this is a maximization problem, we need to check that "crossing is at least containing", that is, for any $a<b<c<d$,
    
    $$
    w(a,c)+w(b,d) \ge w(a,d)+w(b,c).
    $$
    
    Substitute the profit function and let
    
    $$
    A = \max_{i\in[a+1,b]} a_i,~ B = \max_{i\in[b+1,c]} a_i,~ C = \max_{i\in[c+1,d]}a_i,
    $$
    
    Then the inequality to prove can be written as
    
    $$
    \max\{A,B\} + \max\{B,C\} \ge \max\{A,B,C\} + B.
    $$
    
    Note that the larger of the two terms $\max\{A,B\}$ and $\max\{B,C\}$ on the left equals $\max\{A,B,C\}$, and the smaller one is always at least $B$. So the inequality holds.
    
    After turning the tree planting problem into an interval partition problem, we just precompute range maxima with a sparse table or similar, so the cost of any interval can be computed in $O(1)$. Then we can apply the algorithms for interval partition problems and solve it in $O(n\log n\log L)$ or $O(n(n+m))$ time. This method also handles any spacing between trees.

### Exchange argument

In combinatorial optimization, proving convexity of the value function often uses an exchange argument. Specifically, starting from optimal solutions for parameters $m-1$ and $m+1$, we swap some of their elements to build feasible solutions for parameter $m$ whose value is at most $(v(m-1)+v(m+1))/2$, and then use the optimality of $v(m)$ to prove convexity. Unlike convex optimization, combinatorial optimization has no natural way to build an "intermediate form" between two solutions, so applying an exchange argument usually takes some skill.

???+ warning "\"Increasing marginal cost\" does not always imply convexity"
    In combinatorial optimization, the objective function often has some kind of "increasing marginal cost" property, but that does not necessarily imply convexity. A typical example is [\[IOI 2005\] Riv Rivers](https://www.luogu.com.cn/problem/P3354). The path version of this problem satisfies the quadrangle inequality and is therefore convex, but the tree version has counterexamples where convexity fails.
    
    A common property that captures "increasing marginal cost" is supermodularity. A function $f:\mathcal PX\rightarrow\mathbf R$ on the family of subsets $\mathcal PX$ of a finite set $X$ is called **supermodular** if it satisfies either of the following two equivalent properties:
    
    1.  (Crossing is at most containing) For any subsets $A,B\subseteq X$, $f(A)+f(B) \le f(A\cup B) + f(A\cap B)$;
    2.  (Increasing marginal cost) For any subsets $A\subseteq B\subseteq X$ and $x\in X\setminus B$, $f(A\cup\{x\})-f(A)\le f(B\cup\{x\})-f(B)$.
    
    However, in an optimization problem with a supermodular objective, the value function
    
    $$
    v(m) = \min_{A\subseteq X} f(A) \text{ subject to }|A|=m
    $$
    
    is **not necessarily** a convex function of $m$. The reason is that, in general, from optimal solutions of sizes $m-1$ and $m+1$ we cannot build feasible solutions of size $m$ that satisfy the required relation between the values.

The exchange argument gives yet another proof of convexity for the tree planting problem.

??? example "Convexity proof 4"
    Use an exchange argument. Let the optimal plans for planting $m-1$ trees and $m+1$ trees be given by $\{x_i^{(m-1)}\}\in\{0,1\}^n$ and $\{x_i^{(m+1)}\}\in\{0,1\}^n$, where $1$ means a tree is planted in that pit and $0$ means it is not. Define the sequence $\{z_i\}\in\{0,\pm 1\}^n$ by
    
    $$
    z_i = x_i^{(m+1)} - x_i^{(m-1)},~i=1,\cdots,n.
    $$
    
    This sequence marks the differences between the two plans. A $0$ means the pit has a tree in both plans or in neither; $-1$ and $+1$ mean the pit has a tree only in plan $x^{(m-1)}$ or only in plan $x^{(m+1)}$, respectively. Since no plan may plant trees in adjacent pits, we observe:
    
    -   Within a run of consecutive nonzero values, $z_i$ must alternate between $\pm 1$;
    -   The $0$s just to the left and right of a maximal nonzero run must mean that neither plan has a tree there.
    
    So if the values $z_i$ in some maximal nonzero run sum to exactly $+1$, meaning plan $x^{(m+1)}$ plants one more tree than plan $x^{(m-1)}$ in those pits, we can swap the two plans' tree positions within that run. This gives two feasible plans with $m$ trees each. Since we did not change the overall set of positions and number of trees across the two plans, only redistributed them, the total profit is still $v(m-1)+v(m+1)$. But the two $m$-tree plans are not necessarily optimal, so each of their profits is at most $v(m)$. This proves
    
    $$
    v(m-1) + v(m+1) \le 2v(m),
    $$
    
    that is, $v(m)$ is a concave function of $m$.
    
    Only one question remains: does a maximal nonzero run with sum exactly $+1$ exist? Since a run is a sum of alternating $\pm 1$ values, the sum of a nonzero run can only be $0$ or $\pm 1$. And since the sums of all maximal nonzero runs add up to $2$, there must be at least two maximal nonzero runs with sum exactly $+1$. This completes the proof.

## Example problems

This section presents several example problems that apply WQS binary search in different settings.

### Template problem

???+ example "[Luogu P1484 Planting Trees](https://www.luogu.com.cn/problem/P1484)"
    There are $n$ pits, and **at most** $m$ trees are planted. Trees cannot be planted in two adjacent pits. You are given a sequence $\{a_i\}$ of length $n$, the profit of planting a tree in each pit; profits may be positive or negative. Find the maximum possible total profit.

??? note "Solution"
    This differs slightly from the tree planting problem discussed earlier: here we plant at most $m$ trees, not exactly $m$. Still writing $v(m)$ for the value function of the earlier tree planting problem, the answer here is actually $\tilde v(m)=\max_{k\le m}v(k)$. Since $v(m)$ is concave, i.e. unimodal, the answer here keeps only the part of $v(m)$ that rises to the peak, after which the function stays at the peak; this amounts to keeping only the part with non-negative tangent slope. So the only difference from the earlier problem is that in WQS binary search, the initial slope range is $[0,\max_ia_i]$ rather than $[\min_ia_i,\max_ia_i]$.
    
    After WQS binary search removes the count constraint, the problem becomes computing a maximum-weight independent set on a path, with the profits $\{a_i\}$ replaced by $\{a_i+k\}$. This is a classic DP problem. Let $f(i,j)$ be the maximum profit of the subproblem on the first $i$ pits, where pit $i$ has a tree ($j=1$) or not ($j=0$). The transition equations are
    
    $$
    \begin{aligned}
    f(i,0) &= \max\{f(i-1,0),f(i-1,1)\},\\
    f(i,1) &= f(i-1,0) + a_i + k.
    \end{aligned}
    $$
    
    The initial conditions are $f(0,0)=0$ and $f(0,1)=-\infty$, and the final answer is $\max\{f(n,0),f(n,1)\}$. Each computation takes $O(n)$, so the total time complexity is $O(n\log L)$, where $L=\max_i|a_i|$.
    
    Reference implementations:
    
    === "Traditional method"
        ```cpp
        --8<-- "docs/dp/code/opt/wqs-binary-search/plant-tree-1.cpp"
        ```
    
    === "Dual method"
        ```cpp
        --8<-- "docs/dp/code/opt/wqs-binary-search/plant-tree-2.cpp"
        ```

???+ example "[Luogu P2619 \[National Training Team\] Tree I](https://www.luogu.com.cn/problem/P2619)"
    Given a weighted connected undirected graph where each edge is black or white, find the minimum weight of a spanning tree with exactly $m$ white edges.

??? note "Solution"
    First, an exchange argument proves that $v(m)$ is convex. We may assume all edge weights are distinct: if two edges have equal weight, a small perturbation makes all weights distinct; then letting the perturbation go to zero shows that convexity still holds in the limit, i.e. when some weights are equal. The key to the proof is the following lemma:[^edge-swap]
    
    ???+ note "Lemma"
        Let $S$ and $T$ be two spanning trees of a connected undirected graph $G=(V,E)$. For any $e\in S\setminus T$, there is at least one edge $f\in T\setminus S$ such that both $S-e+f$ and $T-f+e$ are spanning trees of $G$.
    
    ??? note "Proof"
        Let $e=(u,v)$, and let $P$ be the unique path in tree $T$ connecting $u$ and $v$. Since $P+e$ is the only cycle in the graph $T+e$, removing any edge $f$ of $P$ makes $T-f+e$ a spanning tree. Meanwhile, the graph $S-e$ is a forest with two connected components; call their vertex sets $V_1$ and $V_2$. So as long as we choose $f\in P$ connecting $V_1$ and $V_2$, $S-e+f$ is a spanning tree. Such an edge $f$ always exists, because $u$ and $v$ are in $V_1$ and $V_2$ respectively, and $P$ connects $u$ and $v$. Moreover, $f\notin S$, because $V_1$ and $V_2$ are not connected in $S-e$. This completes the proof.
    
    Let $T_{m-1}$ and $T_{m+1}$ be minimum spanning trees with $m-1$ and $m+1$ white edges. Let $e$ be a white edge in $T_{m+1}\setminus T_{m-1}$. Applying the lemma to it, there is an edge $f\in T_{m-1}\setminus T_{m+1}$ such that both $T'=T_{m+1}-e+f$ and $T''=T_{m-1}+e-f$ are spanning trees. Since we only swapped one pair of edges, the total edge weight of $T'$ and $T''$ is still $v(m-1)+v(m+1)$. There are two cases:
    
    -   If $f$ is a black edge, then $T'$ and $T''$ both have $m$ white edges. Neither has total weight less than $v(m)$. This proves $2v(m)\le v(m-1)+v(m+1)$, so $v(m)$ is convex in $m$.
    -   If $f$ is a white edge, then $T'$ and $T''$ have $m+1$ and $m-1$ white edges, so their total weights are at least $v(m+1)$ and $v(m-1)$ respectively. But we showed above that their total weights add up to exactly $v(m-1)+v(m+1)$. So the total weight of $T'$ equals $v(m+1)$. Comparing $T'$ with $T_{m+1}$, the weights of $e$ and $f$ must be equal. This contradicts our assumption, so this case cannot happen.
    
    This proves that $v(m)$ is a convex function of $m$.
    
    Once convexity of $v(m)$ is established, we can solve the problem with WQS binary search. Remove the count constraint, subtract $k$ from the weight of every white edge, and solve the minimum spanning tree problem. For this we can use [Kruskal's algorithm](../../graph/mst.md#kruskals-algorithm). With DSU maintaining connectivity, the algorithm takes $O(E\log E+E\alpha(V))$ time, where $E$ and $V$ are the numbers of edges and vertices and $\alpha(\cdot)$ is the inverse Ackermann function. The main part, $O(E\log E)$, is sorting the edges, and it can be optimized further here. Although WQS binary search computes the minimum spanning tree many times, each time only the white edge weights shift by a common amount. So we can sort the white and black edges separately in preprocessing, and each MST computation only needs to merge the adjusted white edges with the black edges. This reduces the total complexity to $O(E\log E+E\alpha(V)\log L)$, where $L$ is the length of the range of edge weights.
    
    Reference implementations:
    
    === "Traditional method"
        ```cpp
        --8<-- "docs/dp/code/opt/wqs-binary-search/black-white-mst-1.cpp"
        ```
    
    === "Dual method"
        ```cpp
        --8<-- "docs/dp/code/opt/wqs-binary-search/black-white-mst-2.cpp"
        ```

### Interval partition problems

???+ example "[Luogu P6246 \[IOI 2000\] Post Office, Enhanced Version of the Enhanced Version](https://www.luogu.com.cn/problem/P6246)"
    An increasing sequence of $n$ positive integers $\{a_i\}$ gives the positions of $n$ villages along a highway, and $m$ post offices must be built. Choose the post office positions to minimize the sum of distances from each village to its nearest post office. Find this minimum.

??? note "Solution"
    This is a typical [interval partition problem](./quadrangle.md#interval-partition-problems). For the implementation details of the binary-search queue, see that page.
    
    Each post office serves the villages closest to it, and these villages must be a group of consecutive villages along the highway. So building $m$ post offices is equivalent to splitting all villages into $m$ consecutive segments and building the cheapest post office for each segment. As is well known, a post office should be built at the median of the village positions. So the cost function of the interval $[l,r]$ is
    
    $$
    w(l,r) = \sum_{i=l}^r|a_i-a_{\lfloor(l+r)/2\rfloor}|.
    $$
    
    It satisfies the quadrangle inequality, because its second-order mixed difference is non-positive:
    
    $$
    \Delta_l\Delta_r w(l,r)
    = \Delta_l(a_{r+1} - a_{\lfloor(l+r+1)/2\rfloor})
    = a_{\lfloor(l+r+1)/2\rfloor}-a_{\lfloor(l+r+2)/2\rfloor} \le 0.
    $$
    
    So the problem can be solved in $O(n\log n\log L)$ time by combining the binary-search queue with WQS binary search.
    
    Reference implementations:
    
    === "Traditional method"
        ```cpp
        --8<-- "docs/dp/code/opt/wqs-binary-search/post-office-1.cpp"
        ```
    
    === "Dual method"
        ```cpp
        --8<-- "docs/dp/code/opt/wqs-binary-search/post-office-2.cpp"
        ```

### Two-dimensional constraints

???+ example "[Codeforces 739 E. Gosha is hunting](https://codeforces.com/problemset/problem/739/E)"
    There are $n$ Pokémon. The sequences $\{p_i\}$ and $\{q_i\}$ give the probabilities of catching the $i$-th Pokémon with a Poké Ball and with an Ultra Ball, respectively. For each Pokémon you may throw one Poké Ball, one Ultra Ball, one of each, or nothing. You have $m_1$ Poké Balls and $m_2$ Ultra Balls to distribute, and all balls are thrown at the same time. Find the maximum expected number of Pokémon caught. Whether one catch attempt succeeds is independent of all others.
    
    More generally, this can be abstracted as the following problem:
    
    Given three sequences of positive reals $\{A_i\},\{B_i\},\{C_i\}$ of length $n$ with $C_i\le A_i+B_i$ for all $i=1,\cdots,n$, find optimal index sets $X$ and $Y$ with $|X|=m_1$ and $|Y|=m_2$ that maximize
    
    $$
    \sum_{i\in X\setminus Y}A_i + \sum_{i\in Y\setminus X}B_i + \sum_{i\in X\cap Y}C_i.
    $$

??? note "Solution"
    The original problem is the special case of this more general problem with
    
    $$
    A_i = p_i,~ B_i = q_i,~ C_i = p_i+q_i-p_iq_i
    $$
    
    So we only need to discuss how to solve the more general problem.
    
    Let $v(m_1,m_2)$ be the value function of this problem. We need to prove that it is a concave function of $(m_1,m_2)$. Consider the following cost flow model:
    
    -   From the source $s$, add one edge to vertex $x$ and one to vertex $y$, with capacities $m_1$ and $m_2$ respectively, both with cost $0$;
    -   For every $i=1,\cdots,n$, add an edge from vertex $x$ to vertex $i$ and one from vertex $y$ to vertex $i$, both with capacity $1$, with costs $A_i$ and $B_i$ respectively;
    -   For every $i=1,\cdots,n$, add two edges from vertex $i$ to the sink $t$, both with capacity $1$, with costs $0$ and $C_i-A_i-B_i$ respectively.
    
    The answer is the maximum-cost maximum flow of this model. The condition $C_i-A_i-B_i\le 0$ ensures that when the flow through vertex $i$ is $1$, it leaves through the edge of cost $0$ first. If we write this cost flow model as a linear program, $m_1$ and $m_2$ appear in the inequalities bounding the flows on edges $(s,x)$ and $(s,y)$. So $v(m_1,m_2)$ is indeed a concave function of $(m_1,m_2)$.
    
    To apply WQS binary search, consider the optimization problem without the count constraints. Let $k_1$ and $k_2$ be the extra rewards for putting an index into set $X$ and set $Y$. Without count constraints, the decision for each index is independent, so
    
    $$
    h(k_1,k_2) = \sum_{i=1}^n\max\{0,A_i+k_1,B_i+k_2,C_i+k_1+k_2\}.
    $$
    
    The answer to the original problem is given by
    
    $$
    v(m_1,m_2) = \min_{k_1,k_2} h(k_1,k_2) - k_1m_1 - k_2m_2
    $$
    
    The total time complexity is $O(n\log^2L)$, where $O(\log L)$ is the number of binary search steps in one dimension.
    
    Reference implementation for the Pokémon catching problem:
    
    ```cpp
    --8<-- "docs/dp/code/opt/wqs-binary-search/gosha-is-hunting.cpp"
    ```

### More general constraints

???+ example "[Codeforces 1661 F. Teleporters](https://codeforces.com/problemset/problem/1661/F)"
    There are $n$ segments whose lengths are given by the sequence $\{a_i\}$. You may cut them anywhere into several segments of integer length, and the goal is to minimize the sum of the squares of all segment lengths. Find the minimum number of cuts needed to bring this sum of squares down to at most $V$.

??? note "Solution"
    Let $f(a,m)$ be the minimum sum of squares obtainable by cutting a segment of length $a$ $m$ times. By the AM–QM inequality, when the sum of two numbers is fixed, the smaller their difference, the smaller the sum of their squares. So the more even the resulting lengths, the smaller the total sum of squares. But because of the integer constraint, the most even case gives $a\bmod (m+1)$ segments of length $\lceil a/(m+1)\rceil$ and $m+1-(a\bmod (m+1))$ segments of length $\lfloor a/(m+1)\rfloor$. So we have the following expression:
    
    $$
    \begin{aligned}
    f(a,m) &= (a\bmod (m+1))\left\lceil\dfrac{a}{m+1}\right\rceil^2 + (m+1-(a\bmod (m+1)))\left\lfloor\dfrac{a}{m+1}\right\rfloor^2 \\
    &= (a\bmod (m+1))\left(\left\lfloor\dfrac{a}{m+1}\right\rfloor+1\right)^2 + (m+1-(a\bmod (m+1)))\left\lfloor\dfrac{a}{m+1}\right\rfloor^2.
    \end{aligned}
    $$
    
    The second equality holds because $\lceil a/(m+1)\rceil \neq \lfloor a/(m+1)\rfloor + 1$ if and only if $a\bmod (m+1) = 0$.
    
    We can prove that $f(a,m)$ is a convex function of $m$. To do so, extend it to $m\in\mathbf R_{+}$. When $\lfloor a/(m+1)\rfloor = q$,
    
    $$
    \begin{aligned}
    f(a,m) &= (a-(m+1)q)(q+1)^2 + ((m+1)(q+1)-a)q^2 \\
    &= a(2q+1) - q(q+1)(m+1).
    \end{aligned}
    $$
    
    This is a line with slope $-q(q+1)$. So $f(a,m)$ is piecewise linear, and its slope increases as $m$ increases. This shows that $f(a,m)$ is convex, and of course its restriction to integer points is convex too[^conv-int].
    
    Using $f(\cdot,\cdot)$, the minimum sum of squares after a total of $m$ cuts over all segments can be written as the value function of the following optimization problem:
    
    $$
    v(m) = \min_{\{m_i\}}\sum_i f(a_i,m_i)\text{ subject to }\sum_i m_i=m,~m_i\in\mathbf N.
    $$
    
    This is the [infimal convolution](./slope-trick.md#infimal-convolution-minkowski-sum) of several convex functions, so it is convex too. If the problem asked for $v(m)$, we could solve it the same way as the earlier examples in $O(n\log^2L)$ time. But this problem asks for the smallest $m$ with $v(m)\le V$. Computing $v(m)$ with WQS binary search and then binary searching on $m$ does not work: it takes $O(n\log^3L)$ time. For this problem, there are two approaches.
    
    **Approach 1**: Still binary search on the slope $k$, but base the decision on bounds for $v(m)$.
    
    In traditional WQS binary search, for a given slope $k$, we can compute the range of optimal values of $m$. Since these points $(m,v(m))$ are collinear, this is the same as determining the range of $v(m)$. So we can binary search directly on the slope $k$. Once we have the slope $k$, we can use the line equation
    
    $$
    v(m) = h(k) + km
    $$
    
    to compute the smallest $m$. The overall complexity is $O(n\log^2L)$.
    
    To determine the range of $v(m)$, we need the range of $m$. One way is to record the largest optimal solution when computing $h(k)$, and use it to compute a lower bound on the corresponding $v(m)$. Another way is to use $h(k)-h(k-1)$ to get an upper bound on the corresponding $m$, and from that a lower bound on the corresponding $v(m)$. The reference implementation uses the second way, which does not depend on the specific structure of the problem and needs no special handling.
    
    **Approach 2**: Rewrite the optimization problem so that the value function of the dual problem is exactly the answer to this problem.
    
    This problem can be viewed directly as the following optimization problem:
    
    $$
    m(V) = \min_{\{m_i\}} \sum_i m_i \text{ subject to }\sum_i f(a_i,m_i) \le V.
    $$
    
    The analysis in this article still applies to this problem. So we can use its dual problem to find the required $m(V)$:
    
    $$
    m(V) = \max_{\lambda} \sum_i\min_{m_i}(m_i - \lambda f(a_i,m_i)) + \lambda V.
    $$
    
    The overall complexity is still $O(n\log^2L)$.
    
    Reference code:
    
    === "Approach 1"
        This code is for illustration only. To pass the original constraints, you need 128-bit integers and must change the initial binary search interval to $[0,10^{60}]$.
        
        ```cpp
        --8<-- "docs/dp/code/opt/wqs-binary-search/teleporters-1.cpp"
        ```
    
    === "Approach 2"
        This code is for illustration only. Because of floating-point precision issues, it cannot pass the original constraints.
        
        ```cpp
        --8<-- "docs/dp/code/opt/wqs-binary-search/teleporters-2.cpp"
        ```

## Exercises

Finally, here are some problems that can be solved with WQS binary search, for practice:

-   [Luogu P1484 Planting Trees](https://www.luogu.com.cn/problem/P1484)
-   [Luogu P1792 \[National Training Team\] Planting Trees](https://www.luogu.com.cn/problem/P1792)
-   [Luogu P2619 \[National Training Team\] Tree I](https://www.luogu.com.cn/problem/P2619)
-   [Luogu P3620 \[APIO/CTSC2007\] Data Backup](https://www.luogu.com.cn/problem/P3620)
-   [Luogu P4072 \[SDOI2016\] Journey](https://www.luogu.com.cn/problem/P4072)
-   [Luogu P4383 \[Eight-Province Joint Exam 2018\] Link-Cut Tree](https://www.luogu.com.cn/problem/P4383)
-   [Luogu P4983 Forgetting](https://www.luogu.com.cn/problem/P4983)
-   [Luogu P5308 \[COCI 2018/2019 #4\] Akvizna](https://www.luogu.com.cn/problem/P5308)
-   [Luogu P5633 Degree-Constrained Minimum Spanning Tree](https://www.luogu.com.cn/problem/P5633)
-   [Luogu P5896 \[IOI 2016\] aliens](https://www.luogu.com.cn/problem/P5896)
-   [Luogu P6246 \[IOI 2000\] Post Office, Enhanced Version of the Enhanced Version](https://www.luogu.com.cn/problem/P6246)
-   [AtCoder Beginner Contest 218 H - Red and Blue Lamps](https://atcoder.jp/contests/abc218/tasks/abc218_h)
-   [AtCoder Beginner Contest 305 Ex - Shojin](https://atcoder.jp/contests/abc305/tasks/abc305_h)
-   [AtCoder Regular Contest 164 E - Segment-Tree Optimization](https://atcoder.jp/contests/arc164/tasks/arc164_e)
-   [Codeforces 125 E. MST Company](https://codeforces.com/problemset/problem/125/E)
-   [Codeforces 321 E. Ciel and Gondolas](https://codeforces.com/problemset/problem/321/E)
-   [Codeforces 739 E. Gosha is hunting](https://codeforces.com/problemset/problem/739/E)
-   [Codeforces 802 O. April Fools' Problem (hard)](https://codeforces.com/contest/802/problem/O)
-   [Codeforces 958 E2. Guard Duty (medium)](https://codeforces.com/problemset/problem/958/E2)
-   [Codeforces 1279 F. New Year and Handle Change](https://codeforces.com/problemset/problem/1279/F)
-   [Codeforces 1661 F. Teleporters](https://codeforces.com/problemset/problem/1661/F)
-   [Codeforces 1799 F. Halve or Subtract](https://codeforces.com/problemset/problem/1799/F)
-   [2019 Summer Petrozavodsk Camp H. Honorable Mention](https://codeforces.com/gym/102331/problem/H)

## References and notes

-   [Wang Qinshi, "A Brief Analysis of a Class of Binary Search Methods" (Chinese)](https://github.com/hzwer/shareOI/blob/master/%E5%9F%BA%E7%A1%80%E7%AE%97%E6%B3%95/%E6%B5%85%E6%9E%90%E4%B8%80%E7%B1%BB%E4%BA%8C%E5%88%86%E6%96%B9%E6%B3%95_%E7%8E%8B%E9%92%A6%E7%9F%B3.pdf)
-   [Theoretical grounds of lambda optimization by adamant - Codeforces blog](https://codeforces.com/blog/entry/98334)
-   [A rigorous WQS binary search method by YeahPotato - Luogu blog (Chinese)](https://www.luogu.com.cn/article/vsffwrc3)
-   [[Study notes] WQS binary search explained, with common misunderstandings by ikrvxt - CSDN blog (Chinese)](https://blog.csdn.net/Emm_Titan/article/details/124035796)
-   [Convex conjugate - Wikipedia](https://en.wikipedia.org/wiki/Convex_conjugate)
-   [Fenchel–Moreau theorem - Wikipedia](https://en.wikipedia.org/wiki/Fenchel%E2%80%93Moreau_theorem)
-   [Subderivative - Wikipedia](https://en.wikipedia.org/wiki/Subderivative)
-   [Boyd, Stephen P., and Lieven Vandenberghe. Convex optimization. Cambridge university press, 2004.](https://web.stanford.edu/~boyd/cvxbook/bv_cvxbook.pdf)
-   Papadimitriou, Christos H., and Kenneth Steiglitz. Combinatorial optimization: algorithms and complexity. Courier Corporation, 1998.
-   Conforti, Michele, Gérard Cornuéjols, and Giacomo Zambelli. Integer programming. Springer International Publishing, 2014.
-   Schrijver, Alexander. Combinatorial optimization: polyhedra and efficiency. Vol. 24, no. 2. Berlin: Springer, 2003.

[^high-d-convex]: In real problems, $y$ may only take finitely many lattice points in $\mathbf R^d$. The condition actually needed here is that the solution $v(y)$ of the original problem can be extended to a convex function $\tilde v:\mathbf R^d\rightarrow \mathbf R\cup\{\pm\infty\}$ on $\mathbf R^d$, i.e. $v(y)$ is **convex-extensible**. For convenience, the main text still writes $v(y)$ for the extended function. Geometrically, this means all points $\{(y,v(y))\}$ lie on the lower hull of their convex hull. In one dimension, this condition is [easy to describe algebraically](./slope-trick.md#convex-functions-on-discrete-point-sets); in higher dimensions it is a bit more complicated, and [these lecture notes](https://kzmurota.fpark.tmu.ac.jp/paper/HIMSummerSchool15Murota.pdf) give some simple sufficient conditions.

[^other-conditions]: The conditions in the theorem look somewhat stronger than plain convexity, but for situations that arise in competitive programming, especially when $X$ is finite, convexity alone is enough. The function $\tilde v$ extended from a proper convex function $v$ on a discrete set is always a lower semicontinuous convex function, because the convex hull of finitely many points is a closed convex set, and a lower semicontinuous convex function is exactly one whose epigraph is a closed convex set. As for the word "proper" in "proper convex function", it is guaranteed as long as $v(y)$ is convex and takes a finite value at at least one point.

[^mst]: There are two common [ways](https://math.arizona.edu/~glickenstein/math443f14/golari.pdf) to write the minimum spanning tree problem as a linear program: the subtour-elimination formulation and the cut-based formulation. Only the first guarantees that the resulting linear program is equivalent to the original problem.

[^edge-swap]: This lemma also holds for general [matroids](../../math/matroid.md). It is called the **symmetric base-exchange property**; see the [Wikipedia page](https://en.wikipedia.org/wiki/Basis_of_a_matroid) for more. So the convexity result for this problem generalizes to general matroids.

[^conv-int]: Of course, $f(a,m)$ is not the same as the convex hull of its restriction to integer points, because $f(a,m)$ may have breakpoints at non-integer positions. This shows that the real-domain function $f(a,m)$ cannot be used directly in the optimization problem of this problem.
