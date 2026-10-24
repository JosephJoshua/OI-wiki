## Introduction

For a class of two-dimensional DP problems, if the value function $f(i,x)$ is a convex function of $x$ for each fixed $i$, then we can treat the whole function $f(i,\cdot)$ as the state at $i$, and maintain its differences (or slopes)

$$
\Delta f(i,x) = f(i,x+1)-f(i,x)
$$

instead of the function itself. This often speeds up the transitions. This idea for optimizing DP is called Slope Trick.

???+ info "\"Slope\""
    Since in most problems the functions only take values at integer points, there is no real difference between calling these differences or slopes. Following the name Slope Trick, this article calls them slopes throughout.

How the slopes are maintained can vary from problem to problem. If the range of slope values is narrow, it is more convenient to maintain the points where the slope changes (the breakpoints). If the domain of the function is narrow, it may be more convenient to maintain the sequence of slopes itself. In more complex cases, you may need to maintain both the slope of each segment and its length. Whatever the specific method, the essence of these problems is the same: the sequence of slopes changes only a little in each transition, and we use this to simplify the transitions. So all of them can be called Slope Trick.

## Convex functions

Before discussing specific problems, we need to understand the basic properties of convex functions, and how their slopes change under various transformations.

### Convex functions on the real line

The fairly general definition of a convex function is given on $\mathbf R$.

![](../images/slope-trick/epigraph-convex-def.svg)

???+ abstract "Convex functions on $\mathbf R$"
    If a function $f:\mathbf R\rightarrow\mathbf R\cup\{\pm\infty\}$ satisfies, for all $x,y\in\mathbf R$ and $\alpha\in(0,1)$,
    
    $$
    f(\alpha x+(1-\alpha)y) \le \alpha f(x)+(1-\alpha)f(y),
    $$
    
    then $f$ is called a **convex function**. Here the arithmetic of $\pm\infty$ is defined so that multiplying $\pm\infty$ by any positive real number, or adding any real number to it, gives $\pm\infty$ itself, and $-\infty<x<+\infty$ for every real number $x\in\mathbf R$.

Of course, if the inequality sign is replaced with $\ge$, the function is called concave[^convex-def]. Since $-f$ is convex whenever $f$ is concave, this section only considers convex functions.

???+ info "This article only considers proper convex functions"
    To avoid discussing the value of $\infty-\infty$ and other extra complications, when discussing convex functions this article always assumes the function never takes the value $-\infty$ and is not identically $+\infty$. Such convex functions are called **proper convex functions**. This is enough to understand what competitive programming needs.

Of course, a function $f$ is often not defined for all real numbers. If the domain of $f$ is only a subset of $\mathbf R$, we can extend it to a function on $\mathbf R$:

$$
\tilde f(x) = \begin{cases} f(x), & x\in\operatorname{dom}f,\\ +\infty,& x\notin\operatorname{dom}f.\end{cases}
$$

Then $f$ is called convex if and only if the corresponding $\tilde f$ satisfies the definition above. So unless stated otherwise, the convex functions in this article have domain $\mathbf R$. Clearly, a convex function $f$ can only take finite values on an interval (that is, a convex subset of $\mathbf R$).

???+ example "Simple examples"
    Common examples of convex functions include:
    
    1.  Constant functions: $f(x)=c$, where $c\in\mathbf R$;
    2.  Linear functions: $f(x)=kx+b$, where $k,b\in\mathbf R$ and $k\neq 0$;
    3.  Absolute value functions: $f(x)=|x-a|$, where $a\in\mathbf R$;
    4.  The restriction of any convex function to an interval, for example $0_{[a,b]}(x)$ (in convex analysis also called the indicator function of $[a,b]$).

Of course, more complex convex functions can be built by combining the convexity-preserving transformations described below.

### Convex functions on discrete point sets

In competitive programming, many functions are only defined at some integer values. In general they are not convex functions (in the sense defined above), because their domain is no longer a convex set. To handle this, we need to define convexity separately for functions on discrete point sets. Simply put, we first linearly interpolate the function to extend its domain to an interval, and then check its convexity.

![](../images/slope-trick/epigraph-convex-discrete.svg)

???+ abstract "Convex functions on discrete point sets"
    Let $S\subset\mathbf R$ be a discrete point set, that is, $S\cap[a,b]$ is finite for every closed interval $[a,b]$. For a function $f:S\rightarrow\mathbf R\cup\{\pm\infty\}$, define the function $\tilde f:\mathbf R\rightarrow\mathbf R\cup\{\pm\infty\}$ as follows:
    
    -   when $x\in S$, $\tilde f(x)=f(x)$,
    -   when $x\in(\inf S,\sup S)\setminus S$, let $s_-=\max\{s\in S:s\le x\}$ and $s_+=\min\{s\in S:s\ge x\}$; then
    
        $$
        \tilde f(x) = \dfrac{s_+-x}{s_+-s_-}f(s_-)+\dfrac{x-s_-}{s_+-s_-}f(s_+),
        $$
    -   when $x\notin[\inf S,\sup S]$, $\tilde f(x)=+\infty$.
    
    Then, if $\tilde f(x)$ is a convex function on $\mathbf R$, we say $f(x)$ is a **convex function** on $S$.

Since convex functions on $\mathbf R$ are easier to work with, unless stated otherwise, "convex function" in this article means a convex function on $\mathbf R$. If a function in this article is only given at some integer points, its values at other real numbers are determined by $\tilde f$ from the definition. This is the same as working directly with the corresponding piecewise linear function $\tilde f$.

Convex functions on the integers $\mathbf Z$ have a more intuitive equivalent definition:

???+ note "Equivalent definition of convex functions on $\mathbf Z$"
    A function $f:\mathbf Z\rightarrow\mathbf R\cup\{\pm\infty\}$ is convex if and only if
    
    $$
    f(x)-f(x-1)\le f(x+1)-f(x)
    $$
    
    holds for all $x\in\mathbf Z$.

??? note "Proof"
    This statement is a simple consequence of the slope characterization of convex functions.
    
    If $f$ is a convex function on $\mathbf Z$, then since slopes are non-decreasing,
    
    $$
    \Delta f(x-1,x)\le \Delta f(x-1,x+1) \le\Delta f(x,x+1).
    $$
    
    This is exactly the condition above.
    
    Conversely, if the condition above holds, then for any $x_1<x_2$,
    
    $$
    \Delta f(x_1,x_2) = \dfrac{1}{x_2-x_1}\sum_{i=x_1}^{x_2-1}\left(f(i+1)-f(i)\right).
    $$
    
    This is the arithmetic mean of all differences with $x_1\le i<x_2$. Increasing $x_2$ by one adds a larger difference; increasing $x_1$ by one removes the smallest difference. Both operations make the mean non-decreasing. This shows that the slope $\Delta f(x_1,x_2)$ is non-decreasing, that is, $f$ is a convex function on $\mathbf Z$.

In other words, as long as the slopes (differences) are non-decreasing, the sequence can be seen as a convex function on $\mathbf Z$.

### Two characterizations of convex functions

In fact, characterizing convex functions by slopes also works in general.

???+ note "Slope characterization of convex functions"
    Let $S$ be $\mathbf R$ or a discrete subset of it. Then $f:S\rightarrow\mathbf R\cup\{\pm\infty\}$ is convex if and only if the slope
    
    $$
    \Delta f(x_1,x_2) = \dfrac{f(x_2)-f(x_1)}{x_2-x_1}
    $$
    
    for any $x_1,x_2\in S$ with $x_1<x_2$ is a non-decreasing function of both $x_1$ and $x_2$.

??? note "Proof"
    For a function $f(x)$ on $\mathbf R$ and $x_1<x_2$, for $\alpha\in(0,1)$ let $x_3=\alpha x_1+(1-\alpha)x_2$. Then
    
    $$
    \Delta f(x_1,x_3) \le \Delta f(x_1,x_2) \le \Delta f(x_3,x_2)
    $$
    
    is equivalent to
    
    $$
    \dfrac{f(x_3)-f(x_1)}{1-\alpha} \le f(x_2)-f(x_1) \le \dfrac{f(x_2)-f(x_3)}{\alpha}.
    $$
    
    The inequalities on both sides are equivalent to $f(x_3)\le\alpha f(x_1)+(1-\alpha)f(x_2)$, which is the convexity of $f(x)$.
    
    For a function $f(x)$ on a discrete subset $S$ of $\mathbf R$, the necessity of non-decreasing slopes follows from the convexity of $\tilde f(x)$. Now we prove sufficiency; for this it suffices to show that $\Delta\tilde f(x_1,x_2)$ is also non-decreasing. Let $S=\{s_i\}$ with $s_i$ strictly increasing in $i$, and let $s_{i_1}\le x_1\le s_{i_1+1}$ and $s_{i_2}\le x_2\le s_{i_2+1}$; naturally $i_1\le i_2$. Let $\Delta_i=\Delta f(s_i,s_{i+1})$. Then we can show that $\Delta_{i_1}\le\Delta\tilde f(x_1,x_2)\le\Delta_{i_2}$.
    
    There are two cases. If $i_1=i_2$, then $\Delta_{i_1}=\Delta\tilde f(x_1,x_2)=\Delta_{i_2}$, and the inequality clearly holds. Otherwise,
    
    $$
    \Delta\tilde f(x_1,x_2) = \dfrac{1}{x_2-x_1}\left((s_{i_1+1}-x_1)\Delta_{i_1}+(x_2-s_{i_2})\Delta_{i_2}+\sum_{j=i_1+1}^{i_2-1}(s_{j+1}-s_j)\Delta_j\right).
    $$
    
    Since slopes on $S$ are increasing, $\Delta_i$ is increasing in $i$, so $\Delta_{i_1}\le\Delta\tilde f(x_1,x_2)\le\Delta_{i_2}$.
    
    Using this, for $x_1<x_2$ and $\alpha\in(0,1)$, let $x_3=\alpha x_1+(1-\alpha)x_2$, and choose $i_3$ with $s_{i_3}\le x_3\le s_{i_3+1}$. Then
    
    $$
    \Delta\tilde f(x_1,x_3) \le \Delta_{i_3} \le \Delta\tilde f(x_3,x_2).
    $$
    
    Substituting the expression for $x_3$ gives the convexity of $\tilde f(x)$.

Non-decreasing slopes can be taken as an equivalent definition of a convex function. Precisely because the slopes of a convex function are monotonic, maintaining the slopes usually calls for data structures such as a [heap (priority queue)](../../ds/heap.md) or a [balanced binary search tree](../../ds/bst.md).

This article also uses another equivalent characterization of convex functions. For a function $f:\mathbf R\rightarrow\mathbf R\cup\{\pm\infty\}$, look at the region of the plane above its graph, that is,

$$
\operatorname{epi} f = \{(x,y)\in\mathbf R^2 : y\ge f(x)\}.
$$

This region is called the **epigraph** of $f$. A function is convex if and only if its epigraph is convex:

???+ note "Epigraph characterization of convex functions"
    A function $f:\mathbf R\rightarrow\mathbf R\cup\{\pm\infty\}$ is convex if and only if $\operatorname{epi}f$ is a convex set in $\mathbf R^2$.

??? note "Proof"
    If $f$ is convex, then for $(x_1,y_1),(x_2,y_2)\in\operatorname{epi}f$ and any $\alpha\in(0,1)$,
    
    $$
    \alpha y_1+(1-\alpha)y_2 \ge \alpha f(x_1)+(1-\alpha)f(x_2) \ge f(\alpha x_1+(1-\alpha) x_2).
    $$
    
    So $\alpha(x_1,y_1)+(1-\alpha)(x_2,y_2)\in\operatorname{epi}f$.
    
    Conversely, if $\operatorname{epi}f$ is a convex set, then for any $x_1<x_2$ and $\alpha\in(0,1)$,
    
    $$
    \alpha(x_1,f(x_1))+(1-\alpha)(x_2,f(x_2)) \in \operatorname{epi}f.
    $$
    
    This is equivalent to $\alpha f(x_1)+(1-\alpha)f(x_2)\ge f\left(\alpha x_1+(1-\alpha)x_2\right)$, which is the convexity of $f$.

As we will see later, the epigraph lets us connect the infimal convolution of convex functions with the Minkowski sum of convex sets.

## Transformations of convex functions

Next, this article introduces some convexity-preserving transformations that come up often in Slope Trick.

### Non-negative linear combinations

For convex functions $f$ and $g$ and non-negative reals $\alpha,\beta\ge0$, the function $\alpha f+\beta g$ is also convex. Moreover,

$$
\Delta(\alpha f+\beta g) = \alpha\Delta f + \beta\Delta g.
$$

So if we maintain the slopes of convex functions $f$ and $g$, the slopes of their non-negative linear combination $\alpha f+\beta g$ can be computed segment by segment.

In problems where we maintain slopes, one of the functions often has a simple form, and lazy tags can reduce the cost of updates. In problems where we maintain breakpoints, to get the breakpoints of $f+g$, just merge the breakpoints of $f$ and $g$.

### Infimal convolution (Minkowski sum)

Another common operation on convex functions is the infimal convolution. For functions $f$ and $g$, the function

$$
h(x) = \inf_{y\in\mathbf R}f(y)+g(x-y)
$$

is called the **infimal convolution**[^inf-conv] of $f$ and $g$. If $f$ and $g$ are both convex, their infimal convolution is also convex.

![](../images/slope-trick/epigraph-convex-minkowski.svg)

??? example "Explanation of the figure"
    As shown in the figure, to get the infimal convolution $h$ of $f$ and $g$, treat every point on the graph of $f$ (the red dashed line in the third figure) as an origin, and draw the graph of $g$ in the corresponding coordinate system (the blue dashed line in the third figure). As the origin moves along the graph of $f$, the outline of the region swept by the graph (epigraph) of $g$, that is, its lower convex hull, is the graph of $h$. You can see that each slope segment of $h$ is either a slope segment of $f$ or a slope segment of $g$, just re-sorted by slope. In this process, the roles of $f$ and $g$ can be swapped: moving the graph of $f$ along the graph of $g$ gives the same result.

Geometrically, $\operatorname{epi}h$ is the [Minkowski sum](../../geometry/convex-hull.md#闵可夫斯基和) of $\operatorname{epi}f$ and $\operatorname{epi}g$. If $f$ and $g$ are both piecewise linear, then $h$ is also piecewise linear, and its slope segments can be seen as the result of merging (and re-sorting) the slope segments of $f$ and $g$.

??? note "Proof"
    Let $f,g$ be convex functions and $h$ their infimal convolution. Let $x_1<x_2$ and $\alpha\in(0,1)$. By the definition of infimal convolution, for any $\varepsilon>0$, there exist $y_i,z_i\in\mathbf R$ with $y_i+z_i=x_i$ and
    
    $$
    h(x_i) + \varepsilon > f(y_i) + g(z_i).
    $$
    
    So, by the convexity of $f,g$ and the definition of $h$,
    
    $$
    \begin{aligned}
    \alpha h(x_1)+(1-\alpha)h(x_2) + \varepsilon 
    &> \alpha f(y_1) + (1-\alpha) f(y_2) + \alpha g(z_1) + (1-\alpha) g(z_2)\\
    &\ge f\left(\alpha y_1+(1-\alpha)y_2\right) + g\left(\alpha z_1+(1-\alpha)z_2\right)\\
    &\ge h(\alpha x_1+(1-\alpha)x_2).
    \end{aligned}
    $$
    
    Since $\varepsilon>0$ was arbitrary,
    
    $$
    \alpha h(x_1)+(1-\alpha)h(x_2) \ge h(\alpha x_1+(1-\alpha)x_2).
    $$
    
    This gives the convexity of $h$.
    
    Next, for the geometric picture, strictly speaking we can only prove the following:
    
    $$
    \operatorname{epi} f + \operatorname{epi} g\subseteq \operatorname{epi}h \subseteq \operatorname{cl}(\operatorname{epi} f + \operatorname{epi} g).
    $$
    
    where $\operatorname{cl}$ denotes the closure.
    
    For any $(x,y)\in\operatorname{epi} f + \operatorname{epi} g$, there exist $(x_1,y_1)\in\operatorname{epi} f$ and $(x_2,y_2)\in\operatorname{epi} g$ such that $x=x_1+x_2$ and
    
    $$
    y = y_1+y_2 \ge f(x_1)+g(x_2) \ge h(x_1+x_2)=h(x).
    $$
    
    So $(x,y)\in\operatorname{epi}h$. This shows $\operatorname{epi} f + \operatorname{epi} g\subseteq \operatorname{epi}h$.
    
    Conversely, for any $(x,y)\in\operatorname{epi}h$, we have $y\ge h(x)$. By the definition of $h$, for any $\varepsilon>0$, there exist $x_1+x_2=x$ such that
    
    $$
    y + \varepsilon > f(x_1) + g(x_2).
    $$
    
    Let $y_1=f(x_1)$ and $y_2=g(x_2)$; then $y+\varepsilon>y_1+y_2$. This shows that for any $\varepsilon>0$, the point $(x_1,y_1)+(x_2,y_2)\in\operatorname{epi} f + \operatorname{epi} g$ lies on the segment between $(x,y)$ and $(x,y+\varepsilon)$. Letting $\varepsilon\rightarrow 0$ gives $\operatorname{epi}h \subseteq \operatorname{cl}(\operatorname{epi} f + \operatorname{epi} g)$.
    
    So as long as $\operatorname{epi} f + \operatorname{epi} g$ is closed, $\operatorname{epi} f + \operatorname{epi} g = \operatorname{epi}h$. One sufficient condition is that $f$ and $g$ are both proper convex functions and [lower semicontinuous](https://en.wikipedia.org/wiki/Semi-continuity). For competitive programming this is enough; for example, piecewise linear functions always satisfy these conditions.

In practice, if one of $f$ and $g$ has few slope segments, just insert those few segments into the larger set of segments. Otherwise, you may need methods such as [small-to-large merging](../../graph/dsu-on-tree.md) or [mergeable heaps](../../ds/heap.md) to reduce the total cost of merging, or find a way that suits the specific problem.

### Max and min operations

The maximum of two convex functions is still convex, but the minimum of two convex functions is not necessarily convex.

Many common min operations can be turned into infimal convolutions:

???+ example "Examples"
    -   $f(x)=\min_{y\in [x+a,x+b]}g(y)$ is still convex, because it can be seen as an infimal convolution:
    
        $$
        f(x) = \min_{y\in\mathbf R}g(y) + 0_{[-b,-a]}(x-y).
        $$
    -   $f(x)=\min\{g(x-a_i)+b_i\}$ is a convex function on $\mathbf Z$, as long as $g(x)$ is a convex function on $\mathbf Z$ and the function $h:a_i\mapsto b_i$ defined on the finite set $\{a_i\}\subset\mathbf Z$ is also convex on that discrete set. This is because the extended function $\tilde f(x)$ can be seen as an infimal convolution:
    
        $$
        \tilde f(x) = \min_{y\in\mathbf R}\tilde h(y)+\tilde g(x-y).
        $$
    
        So the function $f(x)$ before extension is also convex.

But not every min operation preserves convexity.

???+ example "Counterexample"
    Let $g(x)$ be a convex function. Then $f(x)=\min\{g(x-1)+kx,g(x)\}$ is not necessarily convex.

In some special problems, even though the DP transition can be written as the minimum of two convex functions and is hard to turn into an infimal convolution, the value function still stays convex. In practice, you usually need to print out small cases and guess to find a reasonable way to transform the slopes for such problems.

With convex functions and their common transformations in hand, we can look at concrete problems to understand how Slope Trick optimizes DP. The example problems in this article fall roughly into two groups, maintaining breakpoints and maintaining slopes, to show the common operations and implementation details of each. But, as emphasized earlier, the way of maintaining things is not the essence of Slope Trick; you should choose a suitable way to maintain the slope segments based on what the problem needs.

## Maintaining breakpoints

These problems usually ask to minimize a sum of absolute values. In such problems, the absolute values of the slopes of the value function are small, so it is more convenient to maintain the breakpoints where the slope changes.

Maintaining breakpoints means maintaining the points of a piecewise linear function where the slope changes. Equivalently, for each slope segment $[l_i,r_i]$ with slope $k_i$, we only maintain its endpoints, and the slopes themselves need no extra bookkeeping. So in these problems, every change of slope should be by a fixed amount. For example, maintaining the breakpoint set $\xi_{-s}\le\cdots\le\xi_{-1}\le\xi_{1}\le\cdots\le\xi_{t}$ means: the slope is $0$ on $[\xi_{-1},\xi_1]$; going left, the slope decreases by one at each breakpoint; going right, it increases by one at each breakpoint. So the slope is $2$ on $[\xi_2,\xi_3]$, $-2$ on $[\xi_{-3},\xi_{-2}]$, and so on. Formally, the function can be written in terms of its breakpoints as

$$
f(x) = f(\xi_1) + \sum_{i=-s}^{-1}\max\{\xi_i-x,0\} + \sum_{i=1}^{t}\max\{x-\xi_i,0\}.
$$

Its minimum is $f(\xi_{-1})=f(\xi_1)$, attained anywhere in $[\xi_{-1},\xi_1]$.

![](../images/slope-trick/epigraph-convex-kinks.svg)

### Example problem: minimum-cost increasing sequence

???+ example "[\[BalticOI 2004\] Sequence](https://www.luogu.com.cn/problem/P4331)"
    Given a sequence $\{a_i\}$ of length $n$, find a strictly increasing sequence $\{b_i\}$ that minimizes $\sum_i|a_i-b_i|$. Output the minimum and any optimal $\{b_i\}$.

??? note "Solution"
    First, $\{b_i\}$ being strictly increasing is equivalent to $\{b'_i\}=\{b_i-i\}$ being non-decreasing. So we can find, for $\{a'_i\}=\{a_i-i\}$, the non-decreasing sequence $\{b'_i\}=\{b_i-i\}$ with the smallest difference, and then recover $\{b_i\}$.
    
    Consider the naive DP. Let $f_i(x)$ be the minimum difference between the chosen numbers and the first $i$ numbers of $\{a'_i\}$, when the first $i$ numbers of $\{b'_i\}$ have been chosen and the $i$-th one is at most $x$:
    
    $$
    f_i(x) = \min\sum_{j=1}^i|a'_j-b'_j|\text{ s.t. }b'_1\le b'_2\le\cdots\le b'_i\le x.
    $$
    
    It is easy to get the state transition equation
    
    $$
    f_i(x) = \min_{y\le x}f_{i-1}(y)+|a'_i-y|.
    $$
    
    The initial state is $f_0(x)\equiv 0$, and we want $\min_xf_n(x)$. Using the transformations of convex functions above, going from $f_{i-1}(x)$ to $f_i(x)$ takes two steps:
    
    1.  First, add $|a'_i-x|$. This adds $-1$ to every slope segment in $(-\infty,a'_i]$ and $1$ to every slope segment in $[a'_i,+\infty)$;
    2.  Take a running minimum of the result, turning $g(x)=f_{i-1}(x)+|a'_i-x|$ into $f_i(x)=\min_{y\le x}g(y)$. By the analysis above, this is the infimal convolution of $g(x)$ and $0_{[0,+\infty)}$. The latter has only one slope segment, with slope $0$ and extending infinitely to the right; inserting it into the slope segments of $g(x)$ amounts to deleting all positive slope segments.
    
    With these operations clear, we could already maintain all slope segments with a balanced binary search tree, but the code would be complex. Notice that in this problem the slope changes by at most $1$ each time, so the absolute value of every slope is at most $n$. Instead of maintaining slope segments directly, it is more convenient to maintain the breakpoints.
    
    Let the breakpoints of $f_{i-1}(x)$ be $\xi_{-k}\le\cdots\le\xi_{-1}\le\xi_{1}\le\cdots\le\xi_{\ell}$. Then the two steps above correspond to:
    
    1.  Add a breakpoint $a'_i$ for the negative slopes and a breakpoint $a'_i$ for the positive slopes;
    2.  Pop all breakpoints of the positive slopes, $\xi_1,\cdots,\xi_{\ell}$.
    
    In practice, after each operation there are no breakpoints with positive slopes, so the breakpoints have the form $\xi_{-k}\le\cdots\le\xi_{-1}$, and the operations always happen where negative and positive slopes meet. So we just keep all breakpoints in a max-heap. The two steps correspond to:
    
    1.  Insert $a'_i$ twice;
    2.  Pop the top of the heap.
    
    Of course, we also need to track the minimum of the current function after each step. After the operations there are no positive slope segments, so the minimum of the function is its value at the top of the max-heap. Let the top before the operation be $\xi_{-1}$, with minimum $f_{i-1}(\xi_{-1})$. Since the popped top is the smallest breakpoint of the positive slopes, the minimum of the function equals its value there, so we just compute the function value at the top before popping, that is,
    
    $$
    f_{i-1}(\max\{a'_i,\xi_{-1}\})+|\max\{a'_i,\xi_{-1}\}-a'_i|=f_{i-1}(\xi_{-1})+\max\{0,\xi_{-1}-a'_i\}.
    $$
    
    The first equality holds because $f_{i-1}(x)$ has no positive slope segments. So each time we only need to add $\max\{0,\xi_{-1}-a'_i\}$ to the running minimum.
    
    This problem also asks for an optimal solution. At the end, the optimal value is at the top of the heap, so $b'_n$ is determined directly. If we already know the $i$-th optimal value $b'_i$ and want the optimal solution of $f_{i-1}(x)$ subject to $x\le b'_i$, just note that $f_{i-1}(x)$ is convex, so the closer to its global minimum point, the better. So record the global minimum point of $f_{i-1}(x)$ and take the minimum of it and $b'_i$; this gives the optimal $b'_{i-1}$.
    
    The time complexity is $O(n\log n)$.
    
    ```cpp
    --8<-- "docs/dp/code/opt/slope-trick/sequence.cpp"
    ```

Template problems:

-   [Codeforces 713 C. Sonya and Problem Without a Legend](https://codeforces.com/problemset/problem/713/C)
-   [Luogu P2893 \[USACO08FEB\] Making the Grade G](https://www.luogu.com.cn/problem/P2893)
-   [Luogu P4331 \[BalticOI 2004\] Sequence](https://www.luogu.com.cn/problem/P4331)
-   [Luogu P4597 Sequence](https://www.luogu.com.cn/problem/P4597)
-   [AtCoder 2nd Dwango Programming Contest Qualifier E - Fireworks](https://atcoder.jp/contests/dwango2016-prelims/tasks/dwango2016qual_e)

### Example problem: transitions with a constraint

???+ example "[\[NOISG 2018 Finals\] Safety](https://www.luogu.com.cn/problem/P11598)"
    Given a sequence $\{a_i\}$ of length $n$, find a sequence $\{b_i\}$ such that $|b_i-b_{i-1}|\le h$ for all $1<i\le n$ and $\sum_i|a_i-b_i|$ is minimized. Output the minimum.

??? note "Solution"
    This is mostly like the previous problem; only the constraint on $\{b_i\}$ has changed. Similarly, let $f_i(x)$ be the minimum difference over the first $i$ numbers when the $i$-th number is $x$:
    
    $$
    f_i(x) = \min\sum_{j=1}^i|a_j-b_j|\text{ s.t. }|b_{j-1}-b_j|\le h,\forall 1<j\le i,~b_i=x.
    $$
    
    So the state transition equation is
    
    $$
    f_i(x) = |a_i-x| + \min_{|y-x|\le h} f_{i-1}(y). 
    $$
    
    The initial condition is $f_0(x)\equiv 0$. We still want $\min_xf_n(x)$.
    
    Break the transition into operations on convex functions, in two steps:
    
    1.  First take a minimum over $f_{i-1}(x)$, turning it into $\min_{|y-x|\le h} f_{i-1}(y)$. This is the infimal convolution of $f_{i-1}(x)$ and $0_{[-h,h]}(x)$;
    2.  Then add $|a_i-x|$ to the result.
    
    Again, the slope only changes by one each time, so we can maintain breakpoints. Then the two steps become:
    
    1.  Shift all negative slope segments left by $h$, and all positive slope segments right by $h$;
    2.  Insert $a_i$ twice.
    
    Clearly, for this problem it is convenient to maintain the negative and positive slopes separately. Since the operations mostly happen near the zero-slope segment, we can use a [pair of opposite heaps](../../ds/binary-heap.md#对顶堆): a max-heap for the breakpoints of the negative slopes and a min-heap for those of the positive slopes. The global shifts of breakpoints are done with lazy tags. The second step inserts one $a_i$ into each heap; after inserting, the top of the max-heap may no longer be less than or equal to the top of the min-heap. In that case, swap the two tops until the order between them is restored.
    
    Finally, consider how to update the minimum during the operations. The shift in the first step does not change the minimum, so we only need to look at swapping the tops. Suppose $\xi_{-1}>\xi_1$. When we swap the tops $\xi_{-1}$ and $\xi_1$, the function goes from
    
    $$
    \max\{0,\xi_{-1}-x\}+\max\{0,x-\xi_1\}
    $$
    
    to
    
    $$
    \max\{0,\xi_{1}-x\}+\max\{0,x-\xi_{-1}\}.
    $$
    
    In this process the shape of the function stays the same; it just moves down by $|\xi_{-1}-\xi_1|$. So to keep the function unchanged across the swap, just add $|\xi_{-1}-\xi_1|$ to the minimum.
    
    The time complexity is still $O(n\log n)$, because after each insertion, the swap of tops happens at most once.
    
    ```cpp
    --8<-- "docs/dp/code/opt/slope-trick/safety.cpp"
    ```

Template problems:

-   [Luogu P4272 \[CTSC2009\] Sequence Transformation](https://www.luogu.com.cn/problem/P4272)
-   [Luogu P11598 \[NOISG 2018 Finals\] Safety](https://www.luogu.com.cn/problem/P11598)
-   [AtCoder Beginner Contest 217 H - Snuketoon](https://atcoder.jp/contests/abc217/tasks/abc217_h)
-   [AtCoder Regular Contest 070 E - NarrowRectangles](https://atcoder.jp/contests/arc070/tasks/arc070_c)
-   [AtCoder Regular Contest 123 D - Inc, Dec - Decomposition](https://atcoder.jp/contests/arc123/tasks/arc123_d)

## Maintaining slopes

In some other problems, maintaining slopes is more convenient. These problems can usually also be solved with [regret greedy](../../basic/greedy.md#regret-approach) or by simulating min-cost flow. In a min-cost flow model, the minimum cost is often a convex function of the flow amount, which is the basis for using Slope Trick.

### Example problem: stock trading

???+ example "[Codeforces 865 D. Buy Low Sell High](https://codeforces.com/problemset/problem/865/D)"
    Given stock prices $\{p_i\}$ for $n$ days (all positive), you start with $0$ shares. Each day you may buy one share, sell one share, or do nothing. Find the maximum profit after $n$ days.

??? note "Solution"
    First consider the naive DP. Let $f_i(x)$ be the maximum profit at the end of day $i$ when holding $x\ge 0$ shares. Then
    
    $$
    f_i(x) = \max\{f_{i-1}(x-1)-p_i,f_{i-1}(x),f_{i-1}(x+1)+p_i\}.
    $$
    
    The initial state is $f_0(0)=0$, and $f_0(x)=-\infty$ for all $x\neq 0$. The answer is $f_n(0)$.
    
    Going from $f_{i-1}(x)$ to $f_i(x)$ takes two steps:
    
    1.  Take $f_{i-1}(x)$ and the function
    
        $$
        h_i(x) = \begin{cases}p_i,&x=-1,\\0,&x=0,\\-p_i,&x=1\end{cases}
        $$
    
        and form the supremal convolution of $f_{i-1}(x)$ with the piecewise linear function $\tilde h_i(x)$ corresponding to it (clearly a concave function);
    2.  This gives the function finite values on $[-1,0)$, which contradicts the requirement $x\ge 0$, so we need to keep only the part of the function on $[0,+\infty)$.
    
    In terms of slope segments, these are the following two steps:
    
    1.  Insert a slope segment of length $2$ with slope $-p_i$;
    2.  Among the slope segments with finite slope, delete a piece of length $1$ from the one with the largest slope.
    
    Since the lengths of slope segments are always natural numbers, we can maintain many slope segments of length one, so we only need to record the slope of each. Since we only need insertion and access to the maximum, a single max-heap suffices. The operation has two steps:
    
    1.  Insert $-p_i$ twice;
    2.  Pop the top of the heap.
    
    We also need to maintain $f_i(0)$. The function after the first step has value $f_{i-1}(0)+p_i$ at $x=-1$, so its value at $x=0$ is that plus the top that is about to be popped, which is the slope of the function on $[-1,0]$. Truncation does not change the value at $x=0$, so this is $f_i(0)$.
    
    Comparing this implementation with the code for [minimum-cost increasing sequence](#example-problem-minimum-cost-increasing-sequence) above, we see that this algorithm is equivalent to finding the minimum cost to turn the stock prices into a non-increasing sequence.
    
    The time complexity is $O(n\log n)$.
    
    ```cpp
    --8<-- "docs/dp/code/opt/slope-trick/stock.cpp"
    ```

Template problems:

-   [Codeforces 865 D. Buy Low Sell High](https://codeforces.com/problemset/problem/865/D)

### Example problem: moving soil

???+ example "[\[USACO16OPEN\] Landscaping P](https://www.luogu.com.cn/problem/P2748)"
    Given sequences $\{a_i\}$ and $\{b_i\}$ of length $n$, giving the amount of soil garden $i$ already has and the amount it needs (exactly, no more and no less). Buying one unit of soil and putting it in any garden costs $X$; removing one unit of soil from any garden costs $Y$; moving one unit of soil from garden $i$ to garden $j$ costs $Z|i-j|$. Find the minimum cost to meet the needs of all gardens. ($a_i,b_i\le 10$)

??? note "Solution"
    Consider the naive DP. Let $f_i(x)$ be the minimum cost to meet the needs of the first $i$ gardens with a net surplus of $x$ units of soil carried on to later gardens. If $x<0$, there is a net deficit of $|x|$ units of soil that must be brought from later gardens. Then the state transition equation is
    
    $$
    f_i(x) = \min_{y\in\mathbf R} f_{i-1}(y) + |y|Z + h((x-y)+(b_i-a_i)).
    $$
    
    Here $h(\delta)$ is the cost when the net amount of soil bought for the current garden is $\delta$, that is,
    
    $$
    h(\delta) = \max\{0,\delta\}X + \max\{0,-\delta\}Y = \max\{\delta X,-\delta Y\}.
    $$
    
    It is clearly convex. The meaning of the transition is:
    
    -   when the net surplus of the first $i-1$ gardens is $y$, the minimum cost is $f_{i-1}(y)$;
    -   moving the net surplus (deficit) of soil between $i$ and $i-1$ costs $|y|Z$;
    -   by buying and selling, adjusting the soil in garden $i$ from $a_i$ to $b_i$ and the net surplus from $y$ to $x$ costs at least $h((x-y)+(b_i-a_i))$.
    
    The initial state is $f_0(0)=0$, and $f_0(x)=+\infty$ for all $x\neq 0$. The answer is $f_n(0)$.
    
    Turning $f_{i-1}(x)$ into $f_i(x)$ takes three steps:
    
    1.  First, add $|x|Z$ to get $f_{i-1}(x)+|x|Z$;
    2.  Then take the infimal convolution with $h(x)$ to get $\min_{y\in\mathbf R}f_{i-1}(y)+|y|Z+h(x-y)$;
    3.  Finally, shift the function left by $(b_i-a_i)$ units.
    
    As operations on slope segments, there are also three steps:
    
    1.  Add $-Z$ to all slope segments left of the origin, and $Z$ to all slope segments right of the origin;
    2.  Replace all slopes less than $-Y$ with $-Y$, and all slopes greater than $X$ with $X$;
    3.  Shift all slope segments left by $(b_i-a_i)$ units.
    
    In the original problem $a_i$ and $b_i$ are small, so we only need to maintain slope segments of length $1$. Although there are infinitely many slope segments, the slopes are bounded above by $X$ and below by $-Y$, and there are not many segments strictly between the two. Since there is no insertion, we can maintain the slope segments on the two sides of the origin with two stacks, and do all range additions and range clamping with lazy tags. The three steps above correspond to:
    
    1.  Put lazy tags on the left and right stacks: add $-Z$ on the left and $Z$ on the right;
    2.  Every time an element is popped from a stack, take its max with $-Y$ and its min with $X$. If the left stack is empty, pop $-Y$. If the right stack is empty, pop $X$;
    3.  Pop $(b_i-a_i)$ elements from the top of the left stack and push them onto the right stack; of course, when $b_i-a_i<0$, do the reverse.
    
    When moving stack tops across, update the answer: moving left subtracts the current slope, and moving right adds the current slope.
    
    The complexity of the algorithm is $O(n\max\{a_i,b_i\})$.
    
    ```cpp
    --8<-- "docs/dp/code/opt/slope-trick/landscaping.cpp"
    ```

Template problems:

-   [Luogu P2748 \[USACO16OPEN\] Landscaping P](https://www.luogu.com.cn/problem/P2748)
-   [Kyoto University PC 2016 H - WAAAAAAAAAAAAALL](https://atcoder.jp/contests/kupc2016/tasks/kupc2016_h)
-   [JAG Practice Contest 2017 J - Farm Village](https://atcoder.jp/contests/jag2017autumn/tasks/jag2017autumn_j)

## Exercises

To finish, here are some problems from various competitions that can be solved with Slope Trick, for practice.

-   [Luogu P3642 \[APIO2016\] Fireworks](https://www.luogu.com.cn/problem/P3642)
-   [Luogu P9962 \[THUPC 2024 Preliminary\] A Tree](https://www.luogu.com.cn/problem/P9962)
-   [AtCoder Beginner Contest 383 G - Bar Cover](https://atcoder.jp/contests/abc383/tasks/abc383_g)
-   [Codeforces 280 D. k-Maximum Subsequence Sum](https://codeforces.com/problemset/problem/280/D)
-   [Codeforces 280 E. Sequence Transformation](https://codeforces.com/problemset/problem/280/E)
-   [Codeforces 802 O. April Fools' Problem (hard)](https://codeforces.com/contest/802/problem/O)
-   [Codeforces 1209 H. Moving Walkways](https://codeforces.com/contest/1209/problem/H)
-   [Codeforces 1229 F. Mateusz and Escape Room](https://codeforces.com/contest/1229/problem/F)
-   [Codeforces 1534 G. A New Beginning](https://codeforces.com/problemset/problem/1534/G)
-   [Codeforces 1787 H. Codeforces Scoreboard](https://codeforces.com/problemset/problem/1787/H)
-   [2019 Summer Petrozavodsk Camp H. Honorable Mention](https://codeforces.com/gym/102331/problem/H)
-   [2018 ACM-ICPC World Finals C. Conquer The World](https://codeforces.com/gym/102482/problem/C)
-   [300iq Contest 3 F. Farm of Monsters](https://codeforces.com/gym/102538/problem/F)

## References and notes

-   [\[Tutorial\] Slope Trick - zscoder](https://codeforces.com/blog/entry/47821)
-   [Slope trick explained - Kuroni](https://codeforces.com/blog/entry/77298)
-   [Slope Trick - USACO Guide](https://usaco.guide/adv/slope-trick?lang=cpp)
-   [\[Tutorial\] Intuition on Slope Trick - maomao90](https://codeforces.com/blog/entry/103222)

[^convex-def]: Different textbooks may use different names for convex functions.

[^inf-conv]: Also often called $\min$ convolution, $\inf$ convolution, or $(\min,+)$ convolution.
