author: Marcythm, zyf0726, hsfzLZH1, MingqiHuang, Ir1d, greyqz, billchenchina, Chrogeek, StudyingFather, NFLSCode, c-forrest

Quadrangle inequality optimization takes advantage of decision monotonicity in the state transition equation, so it is also often called **decision monotonicity DP optimization**.

## Basics

Consider the simplest case. We want to solve the following family of optimization problems:

$$
f(i) = \min_{1 \leq j \leq i} w(j,i) \qquad \left(1 \leq i \leq n\right) \tag{1}
$$

Here we assume the cost function $w(j,i)$ can be computed in $O(1)$ time.

???+ info "Conventions"
    A DP state transition equation can often be written as a family of optimization problems. Take equation (1) as an example. These problems have a parameter $i$, and both the objective function and the feasible region may depend on $i$. Each problem, for a given parameter $i$, chooses some feasible solution $j$ to minimize the objective function. For convenience, below we call the optimization problem with parameter $i$ "problem $i$", a feasible solution $j$ of it "decision $j$", and the value of the objective at the optimal solution "state $f(i)$". We also write $\operatorname{opt}(i)$ for the smallest optimal decision point of problem $i$.

In general, solving all these problems takes $O(n^2)$ time in total, because for problem $i$ we need to consider every possible decision $j$. But when decision monotonicity holds, we can shrink the decision space effectively and lower the total complexity.

-   **Decision monotonicity**: for any $i_1 < i_2$, we always have $\operatorname{opt}(i_1) \leq \operatorname{opt}(i_2)$.

??? note "Remark"
    For problem $i$, the set of optimal decisions is not necessarily an interval. Decision monotonicity can actually be defined on the sets of optimal decisions. For sets $A$ and $B$, we can define $A \leq B$ if and only if for any $a\in A$ and $b\in B$, we have $\min\{a,b\}\in A$ and $\max\{a,b\}\in B$. This implies monotonicity of the smallest (largest) optimal decision point, which is the definition used here. The conclusions in this article about the smallest optimal decision point also apply to the largest optimal decision point. However, it can happen that the smallest optimal decision of a larger problem is strictly less than the largest optimal decision of a smaller problem; that is, for some $i_1 < i_2$ we may have $\mathop{\mathrm{optmax}}(i_1) > \mathop{\mathrm{optmin}}(i_2)$. So when writing code, make sure you always find the smallest, or always the largest, optimal decision point.
    
    On the other hand, the problems that share the same smallest optimal decision form an interval. As a function of the smallest optimal decision, this interval should be strictly increasing. That is, given $j_1 = \operatorname{opt}(i_1)$ and $j_2 = \operatorname{opt}(i_2)$, if $j_1 < j_2$ then we must have $i_1 < i_2$. In other words, if decisions $j_1 < j_2$ are the smallest optimal decisions for the problem intervals $[l_{j_1},r_{j_1}]$ and $[l_{j_2},r_{j_2}]$ respectively, then $r_{j_1} < l_{j_2}$.

The most common way to establish decision monotonicity is through the quadrangle inequality. In different contexts this property is also called the Monge property (for a matrix $A_{j,i}$) or submodularity (for a function $f([j,i])$ whose argument is an interval).

-   **Quadrangle inequality**: if for any $a\leq b\leq c\leq d$ we have

    $$
    w(a,c)+w(b,d) \leq w(a,d)+w(b,c),
    $$

    then the function $w$ satisfies the quadrangle inequality (in short, "crossing is at most containing"). If equality always holds, we say $w$ satisfies the **quadrangle identity**.

Unless stated otherwise, $a\leq b\leq c\leq d$ is always assumed below. The quadrangle inequality gives a sufficient but not necessary condition for decision monotonicity.

???+ note "Theorem 1"
    If $w$ satisfies the quadrangle inequality, then problem (1) has decision monotonicity.

??? note "Proof"
    We prove this by contradiction. Suppose that for some $c < d$ we have $a = \operatorname{opt}(d) < \operatorname{opt}(c) = b$. Then $a < b \leq c < d$. By optimality, $w(a,d) \leq w(b,d)$ and $w(b,c) < w(a,c)$, so $w(a,d) - w(b,d) \leq 0 < w(a,c) - w(b,c)$, which contradicts the quadrangle inequality.

The quadrangle inequality can be understood as saying that, on a suitable domain, the second-order mixed difference $\Delta_i\Delta_jw(j,i)$ of $w$ is non-positive.

Using decision monotonicity, many common algorithms can bring the complexity down to $O(n\log n)$. These algorithms differ in where they apply, how hard they are to implement, and how fast they run, so you need to pick the right one for the situation. This mainly depends on the properties of $w(j,i)$. Unless stated otherwise, this article assumes $w(j,i)$ supports **random access**, that is, $w(j,i)$ can be queried or computed in $O(1)$ time. However, $w(j,i)$ is not that easy to compute in every problem. So besides the basic case, this article also discusses how to use decision monotonicity to optimize DP when $w(j,i)$ only has the following properties:

-   **Incremental access**: $w(j,i)$ can be obtained from $w(j\pm 1,i)$ or $w(j,i\pm 1)$ in $O(1)$ time. (Similar to the situation in [Mo's algorithm](../../misc/mo-algo.md).)
-   **Online computation**: computing $w(j,i)$ depends on $\{f(j'):j' < j\}$. This means $f$ and $w$ can only be computed in order. The interval partition problem without a limit on the number of intervals, introduced below, falls into this case.

These two properties are not mutually exclusive: $w(j,i)$ may both need online computation and only support incremental access.

### Divide and conquer

To solve all states, it is enough to find all optimal decision points. To find $\operatorname{opt}(i)$ for all $1 \leq i \leq n$, first compute $\operatorname{opt}(n/2)$, then compute $\operatorname{opt}(i)$ for $1 \leq i < n/2$ and for $n/2 < i \leq n$ separately. Note that we now know $\operatorname{opt}(i)$ for the first half must lie between $1$ and $\operatorname{opt}(n/2)$ (inclusive), and $\operatorname{opt}(i)$ for the second half must lie between $\operatorname{opt}(n/2)$ and $n$ (inclusive). Handle the two subintervals the same way, until the optimal decision of every problem is found. By recording the lower and upper search bounds during divide and conquer, the complexity stays within $O(n\log n)$. The recursion tree has $O(\log n)$ levels, and within each level a single decision point is evaluated at most twice, so the total number of evaluations is $O(n\log n)$.

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/dp/code/opt/quadrangle/quadrangle-divide-conquer.cpp:core"
    ```

Besides the basic case with random access, the divide and conquer algorithm also works when $w(j,i)$ only supports incremental access. Just maintain a cursor $(j,i)$ and the corresponding value $w(j,i)$ during the computation; whenever a new value is needed, move the cursor step by step to the current position and update the value. The time complexity is still $O(n\log n)$. For a more detailed discussion, see the section [Simplified LARSCH algorithm](#simplified-larsch-algorithm) below. However, divide and conquer cannot handle the case where $w(j,i)$ needs online computation, because it has no way to compute the smallest optimal decision $\operatorname{opt}(n/2)$ at the midpoint before the problems in the left half are solved.

### Binary search with a queue

Note that for each decision point $j$, the problems $i$ for which $j$ is the smallest optimal decision point always form an interval. We can use a monotonic queue to record, for each decision point so far, the interval of problems it handles. Then the optimal solution of each problem can be computed from the decision points recorded in the queue.

Specifically, the algorithm goes through the decision points in order. When it reaches decision point $k$, the queue must record, for each feasible decision point $j$ so far, a **triple** made of $j$ and the left and right endpoints $l_j$ and $r_j$ of the interval of problems it handles. For problems in the interval $[l_j,r_j]$, $j$ should be the smallest optimal decision among the decision points considered so far (that is, those in $[1,k]$). At any moment, the decisions stored in the queue need not be consecutive, but the unsolved problems $[k,n]$ must be the disjoint union of the problem intervals stored in the queue.

To show that, as the queue is updated, the problems $i$ for which decision point $j$ is the smallest optimal decision always form a contiguous interval, we need to strengthen the earlier result a little:

???+ note "Corollary 1"
    Let $\operatorname{opt}_k(i)$ be the smallest optimal decision of problem $i$ when only decisions in $[1,k]$ are considered. If $w$ satisfies the quadrangle inequality, then for any $i_1 < i_2$, we always have $\operatorname{opt}_k(i_1) \leq \operatorname{opt}_k(i_2)$.

??? note "Proof"
    Let $M$ be a sufficiently large positive real number. The function $w'(j,i) = w(j,i) + M[j > k]$ still satisfies the quadrangle inequality, where $[\cdot]$ is the Iverson bracket. Consider an auxiliary DP with cost function $w'$. In this auxiliary DP, for any problem $i$, a decision $j > k$ can never be the smallest optimal one, that is, $\operatorname{opt}'(i) = \operatorname{opt}'_k(i) = \operatorname{opt}_k(i)$. Applying Theorem 1 to the auxiliary DP gives this corollary.

The algorithm works as follows:[^cmp-min-opt]

-   At the start, the queue is empty. As with a monotonic queue, each time we consider the next decision $j$, we perform a pop step and a push step.
-   **Pop**: first remove the previous problem $j-1$ from the queue. If the right endpoint of the problems handled by the front decision is exactly $j-1$, pop the front directly; otherwise, update the left endpoint of the problems handled by the front decision to $j$.
-   **Push**: to push decision $j$, first compare it with the decision $j'$ at the back of the queue.
    -   If, for problem $l_{j'}$, the new decision $j$ is strictly better than the existing decision $j'$, that is, $w(j,l_{j'}) < w(j',l_{j'})$, pop the back decision $j'$. Repeat until the queue is empty or the back decision $j'$ is better than $j$ for problem $l_{j'}$.
    -   If the queue is empty, push $(j,j,n)$, meaning decision $j$ is considered optimal for all unsolved problems.
    -   If the back decision $j'$ is also no worse than the new decision $j$ for problem $r_{j'}$, then when $r_{j'} < n$, push $(j,r_{j'}+1,n)$, meaning $j$ is the smallest optimal decision for problems $[r_{j'}+1,n]$; otherwise, $j$ does not need to be pushed, because it is not better than the existing decisions.
    -   The last case is that the back decision $j'$ is strictly better than the new decision $j$ for problem $l_{j'}$, but strictly worse for problem $r_{j'}$. This means there is a problem $i\in(l_{j'},r_{j'}]$ such that the smallest optimal decision of problems $[l_{j'},i-1]$ is $j'$ and that of problems $[i,r_{j'}]$ is $j$. So we use **binary search** to find the smallest $i\in[l_{j'},r_{j'}]$ with $w(j,i) < w(j',i)$, change the right endpoint $r_{j'}$ of the back interval to $i-1$, and push $(j,i,n)$.
-   After decision $j$ is processed, all decisions up to $j$ have been processed. Now the front decision is the smallest optimal decision of problem $j$, and we can record the corresponding optimal value.

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/dp/code/opt/quadrangle/quadrangle-monotone-queue.cpp:core"
    ```

As with a monotonic queue, each decision point is pushed at most once and popped at most once. Popping takes $O(1)$, and pushing takes $O(\log n)$ (it may need a binary search), so the total time complexity is $O(n\log n)$.

Since the binary search queue algorithm considers all problems and decision points in order, it works when $w(j,i)$ needs online computation. This is its advantage over divide and conquer. However, because its binary search step relies on random access to $w(j,i)$, it cannot be used when $w(j,i)$ only supports incremental access.

???+ example "Example problem 1: [POI2011 Lightning Conductor](https://loj.ac/problem/2157)"
    Given a sequence $a_1,a_2,\cdots,a_n$ of length $n$, for each $1 \leq i \leq n$, find the smallest non-negative integer $f_i$ such that
    
    $$
    \forall j\in\left[1,n\right]:a_j \leq a_i + f_i - \sqrt{|i-j|}.
    $$

??? note "Idea"
    Clearly, by rearranging the inequality, the integer we want is $f_i = \max_{j}\{a_j+\sqrt{|i-j|}-a_i\}$. Let's first consider $j \leq i$ (the other case is similar). Then we get the state transition equation:
    
    $$
    f_i = -\min_{j\le i}\{-a_j-\sqrt{i-j}+a_i\}.
    $$
    
    By the convexity of $-\sqrt{x}$, it is easy to show (details below) that the function $w(j,i) = -a_j-\sqrt{i-j}+a_i$ satisfies the quadrangle inequality, so applying the algorithm above solves this problem in $O(n\log n)$ time.

??? note "Implementation"
    ```cpp
    --8<-- "docs/dp/code/opt/quadrangle/quadrangle_1.cpp"
    ```

### Simplified LARSCH algorithm

Neither of the previous two algorithms can handle the case where $w(j,i)$ both needs online computation and only supports incremental access. This section introduces an algorithm that overcomes both difficulties at once. It is a simplified version of the LARSCH algorithm proposed by Larmore and Schieber in 1991[^larsch], so it is called the **simplified LARSCH algorithm**. The original version can solve decision monotonicity DP problems in $O(n)$ time, but it is more complicated to implement and is not covered here.

We still use divide and conquer. When solving the problems in the interval $(l,r]$, assume the following are known:

-   the smallest optimal decision $\operatorname{opt}(i)$ and the optimal value of each problem $i$ in $[1,l]$, and
-   the smallest optimal decision $\operatorname{opt}_l(r)$ and the optimal value of problem $r$ when only decisions in $[1,l]$ are considered.

When we finish solving the problems in $(l,r]$, we must have the smallest optimal decisions and optimal values of the problems in $(l,r]$.

Let $\textit{mid}$ be the midpoint of $(l,r]$. The procedure is:

1.  Go through the decisions $j\in[\operatorname{opt}(l),\operatorname{opt}_l(r)]$ and update the smallest optimal decision and optimal value of problem $\textit{mid}$.
2.  Recursively solve the problems in $(l,\textit{mid}]$.
3.  Go through the decisions $j\in(l,\textit{mid}]$ and update the smallest optimal decision and optimal value of problem $r$.
4.  Recursively solve the problems in $(\textit{mid},r]$.

Before running the recursion on the whole interval $[1,n]$, first update problems $i\in\{1,n\}$ with decision $j=1$. The recursion stops when it reaches $l=r$.

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/dp/code/opt/quadrangle/quadrangle-simplified-larsch.cpp:core"
    ```

First, let's show the algorithm is correct. It suffices to check that the preconditions above hold before each recursive step (steps 2 and 4). By Corollary 1 from the previous section, $\operatorname{opt}(l)=\operatorname{opt}_l(l)\le\operatorname{opt}_l(\textit{mid})\le\operatorname{opt}_l(r)$, so after step 1, $\operatorname{opt}_l(\textit{mid})$ is known, and the preconditions for recursively solving the problems in $(l,\textit{mid}]$ in step 2 hold. Since $\{\operatorname{opt}(i):i\in[1,l]\}$ was known before, and step 2 gives the values $\{\operatorname{opt}(i):i\in(l,\textit{mid}]\}$, all of $\{\operatorname{opt}(i):i\in[1,\textit{mid}]\}$ are known afterwards. Also, since $\operatorname{opt}_l(r)$ was known before, after step 3 $\operatorname{opt}_\textit{mid}(r)$ is known too. So the preconditions for recursively solving the problems in $(\textit{mid},r]$ in step 4 also hold.

Next, we show the complexity is still $O(n\log n)$. The recursion tree has $O(\log n)$ levels. For each node on the same level, we go through the decisions in $[\operatorname{opt}(l),\operatorname{opt}_l(r)]$ and in $(l,\textit{mid}]$. Since $\operatorname{opt}(l)\le\operatorname{opt}_l(r)\le\operatorname{opt}(r)$, each decision point is visited only $O(1)$ times within one level. So the total number of visits on each level of the recursion tree is $O(n)$. Assuming each access or computation of $w(j,i)$ takes $O(1)$, the time complexity of the algorithm is $O(n\log n)$.

For some cases where $w(j,i)$ only supports incremental access, the complexity of this algorithm is still $O(n\log n)$. In that case, we maintain separate cursors $(j,i)$ and current values $w(j,i)$ for step 1 and step 3. Each time a new value is needed, move the cursor $(j,i)$ step by step from its last position to the current one and update $w(j,i)$ along the way. It is easy to check that, over the whole traversal of the recursion tree, the total number of these moves is $O(n\log n)$. So the time complexity of the algorithm is still $O(n\log n)$.

??? note "Complexity proof without random access"
    We only need to show that the cursors move $O(n\log n)$ times in total. Let $A$ and $B$ be the cursors for steps 1 and 3. We can in fact guarantee that before solving the problems in $(l,r]$, cursor $A$ is at $(\operatorname{opt}(l),l)$ and cursor $B$ is at $(l,l)$; afterwards, cursor $A$ is at $(\operatorname{opt}(r),r)$ and cursor $B$ is at $(r,r)$.
    
    Consider the following cursor movement rule. In step 1, move cursor $A$ along the path
    
    $$
    (\operatorname{opt}(l),l)\to(\operatorname{opt}(l),\textit{mid})\to(\operatorname{opt}_l(r),\textit{mid})\to(\operatorname{opt}(l),\textit{mid})\to(\operatorname{opt}(l),l)
    $$
    
    Now cursors $A$ and $B$ are both at the required positions for starting to solve the problems in $(l,\textit{mid}]$. In step 2, by the rule, cursor $A$ moves to $(\operatorname{opt}(\textit{mid}),\textit{mid})$ and cursor $B$ moves to $(\textit{mid},\textit{mid})$. In step 3, move cursor $B$ along the path
    
    $$
    (\textit{mid},\textit{mid}) \to (l,\textit{mid}) \to (l, r) \to (\textit{mid},r) \to (\textit{mid},\textit{mid})
    $$
    
    Now cursors $A$ and $B$ are both at the required positions for starting to solve the problems in $(\textit{mid},r]$. In step 4, by the rule, cursor $A$ moves to $(\operatorname{opt}(r),r)$ and cursor $B$ moves to $(r,r)$. Both cursors end at the required positions for finishing the problems in $(l,r]$. So this movement rule matches the requirements above. Moreover, it is enough to do all the computations in steps 1 and 3. Counting the cursor moves under this rule directly, step 1 needs
    
    $$
    2(\operatorname{opt}_l(r) - \operatorname{opt}(l)) + 2(\textit{mid} - l)
    $$
    
    moves, and step 3 needs
    
    $$
    2(\textit{mid}-l)+2(r-\textit{mid}) = 2(r-l)
    $$
    
    moves. Summing these over all nodes of the recursion tree, and using the fact that all $[l,r]$ and all $[\operatorname{opt}(l),\operatorname{opt}_l(r)]$ on the same level overlap only at their endpoints, we see that the total number of moves is $O(n\log n)$.
    
    Since this rule adds more waypoints than the cursors actually need during the computation, the actual number of cursor moves cannot exceed the estimate under this rule. So the actual number of cursor moves is also $O(n\log n)$.

Since this algorithm has already computed the optimal values $f(i)$ in $[1,l]$ before solving the problems in $(l,r]$, it also works when $w(j,i)$ needs online computation.

## Interval partition problems

Consider the problem of splitting an interval into several subintervals. Formally, split the given interval $[1,n]$ into $[a_1,b_1],\cdots,[a_k,b_k]$, where $a_1=1$, $b_k=n$, and $b_{i}+1=a_{i+1}$ for every $i < k$. The cost of a split is $\sum_{i=1}^kw(a_i,b_i)$, and we want to minimize it. We can write the following 1D1D state transition equation.

$$
f(i) = \min_{1\leq j\leq i} f(j-1)+w(j,i) \qquad (1\leq i\leq n)
$$

Here $f(0)=0$. Note that as long as $w(j,i)$ satisfies the quadrangle inequality, $f(j-1)+w(j,i)$ also satisfies it, because the first term has no cross term in $j$ and $i$ and cancels out in the mixed difference. But since the cost depends on earlier subproblems, this transition can only be computed in order, so the first algorithm above (divide and conquer) does not apply. Usually only the binary search queue algorithm or the simplified LARSCH algorithm is suitable. The complexity is $O(n\log n)$.

### With a limit on the number of intervals

The problem above can be strengthened by limiting the number of intervals: the problem requires splitting the interval into exactly $m$ subintervals. Then the number of intervals so far has to be one dimension of the state. Correspondingly, we have the following 2D1D state transition equation.

$$
f(k,i) = \min_{1\leq j\leq i} f(k-1,j-1)+w(j,i) \qquad (1\leq k\leq m,\ 1\leq i\leq n) \tag{2}
$$

Here $f(0,0)=0$, and $f(0,i)=f(k,0)=\infty$ for every $1\leq k\leq m$ and $1\leq i\leq n$. For the same reason as above, $f(k-1,j-1)+w(j,i)$ satisfies the quadrangle inequality. Now computing layer $k$ no longer depends on results from the same layer, so each layer can be computed with any of the algorithms from the previous section, for a total complexity of $O(mn\log n)$.

For this problem, there are actually other optimizations based on decision monotonicity. The second idea relies on the following result. This optimization is very similar to Knuth's optimization, described in detail below.

???+ note "Theorem 2"
    If $w$ satisfies the quadrangle inequality, then problem (2) satisfies $\operatorname{opt}(k-1,i) \leq \operatorname{opt}(k,i) \leq \operatorname{opt}(k,i+1)$.

??? note "Proof"
    The second inequality is just decision monotonicity within layer $k$. The key is the first inequality.
    
    We now prove $\operatorname{opt}(k,i) \leq \operatorname{opt}(k+1,i)$. Suppose we have the following two partitions of $[1,i]$ (numbered in reverse): $[a_{k},d_{k}],\cdots,[a_1,d_1]$ and $[b_{k+1},c_{k+1}],\cdots,[b_1,c_1]$. Here the left endpoint of each interval is the smallest optimal decision for the problem at its right endpoint; likewise, considering all possible partitions from right to left, the right endpoint is also the smallest optimal decision for the problem at the left endpoint. For example, $d_j$ and $c_j$ are the smallest optimal decisions for the right endpoint of the first interval from the left when splitting $[a_j,i]$ and $[b_j,i]$ into $j$ parts, respectively. By decision monotonicity, if $a_{j-1} > b_{j-1}$, that is, $d_j > c_j$, then $a_j > b_j$. So if the claim fails, then $a_1 > b_1$, and by induction we get $a_{k} > b_{k}$. This clearly contradicts the assumption. This completes the proof.
    
    The first inequality can also be proved another way. Consider the same two partitions as above. If the claim fails, then $a_1 > b_1$; but since $a_{k} < b_{k}$, we can find the smallest $j>1$ with $a_j \leq b_j$. Then $a_{j-1} > b_{j-1}$, so $d_j>c_j$. We have found intervals with $a_j \leq b_j \leq c_j < d_j$. Now consider recombining the two partitions. Take the partition $[b_{k+1},c_{k+1}],\cdots,[b_{j+1},c_{j+1}],[b_j,d_j],[a_{j-1},d_{j-1}],\cdots,[a_1,d_1]$, which has $(k+1)$ parts. By the optimality assumed above,
    
    $$
    \begin{aligned}
    &w(b_{k+1},c_{k+1})+\cdots+w(b_{j+1},c_{j+1})+w(b_j,c_j)+w(b_{j-1},c_{j-1})+\cdots+w(b_1,c_1) \\
    &\qquad \leq w(b_{k+1},c_{k+1})+\cdots+w(b_{j+1},c_{j+1})+w(b_j,d_j)+w(a_{j-1},d_{j-1})+\cdots+w(a_1,d_1).
    \end{aligned}
    $$
    
    Similarly, take the partition $[a_{k},d_{k}],\cdots,[a_{j+1},d_{j+1}],[a_j,c_j],[b_{j-1},c_{j-1}],\cdots,[b_1,c_1]$, which has $k$ parts. Then
    
    $$
    \begin{aligned}
    &w(a_{k},d_{k})+\cdots+w(a_{j+1},d_{j+1})+w(a_j,d_j)+w(a_{j-1},d_{j-1})+\cdots+w(a_1,d_1) \\
    &\qquad < w(a_{k},d_{k})+\cdots+w(a_{j+1},d_{j+1})+w(a_j,c_j)+w(b_{j-1},c_{j-1})+\cdots+w(b_1,c_1).
    \end{aligned}
    $$
    
    Here the inequality is strict because $a_1 > b_1$, while by assumption $a_1$ is the smallest optimal left endpoint of the last part among all $k$-part partitions. Adding the two inequalities gives $w(b_j,c_j) + w(a_j,d_j) < w(b_j,d_j) + w(a_j,c_j)$, which contradicts the quadrangle inequality. So the claim holds.

Using this result, we can limit the search range of decision $j$. In the implementation, loop over $k$ forward and over $i$ backward, and search $j$ by brute force within the bounds already determined. This guarantees a complexity of $O(n(n+m))$.

??? warning "Note"
    The complexity here is not $O(nm)$. To count correctly, consider the $n\times m$ state matrix. For problem $(k,i)$ we only need to consider decisions with $\operatorname{opt}(k-1,i) \leq j \leq \operatorname{opt}(k,i+1)$, so the problems on each anti-diagonal (where $i-k$ is constant) need $O(n)$ decisions in total. There are $(n+m)$ such diagonals, so the total time complexity is $O(n(n+m))$.

The last optimization comes from the following observation.

???+ note "Theorem 3"
    If $w$ satisfies the quadrangle inequality, then the optimal value $g(k):=f(k,n)$ of problem (2) is a convex function of $k$.

??? note "Proof"
    We now prove $g(k-1) + g(k+1) \ge 2g(k)$. Consider the optimal partitions into $(k-1)$ parts and $(k+1)$ parts: $[a_1,d_1],\cdots,[a_{k-1},d_{k-1}]$ and $[b_1,c_1],\cdots,[b_{k+1},c_{k+1}]$. Take the smallest $1 \leq j \leq k-1$ with $c_{j+1} \leq d_j$; it exists because $c_{k} < n = d_{k-1}$. By its minimality, $b_{j+1} > a_j$. So $a_j < b_{j+1} \leq c_{j+1} \leq d_j$. As above, swapping the second halves of the two partitions gives the following two partitions:
    
    $$
    \begin{aligned}
    & [a_1,d_1],\cdots,[a_{j-1},d_{j-1}],[a_j,c_{j+1}],[b_{j+2},c_{j+2}],\cdots,[b_{k+1},c_{k+1}], \\
    & [b_1,c_1],\cdots,[b_j,c_j],[b_{j+1},d_j],[a_{j+1},d_{j+1}],\cdots,[a_{k-1},d_{k-1}].
    \end{aligned}
    $$
    
    Both resulting partitions have $k$ parts, so by optimality
    
    $$
    \begin{aligned}
    2g(k) &\le w(a_1,d_1) + \cdots + w(a_{j-1},d_{j-1}) + w(a_j,c_{j+1}) + w(b_{j+2},c_{j+2}) + \cdots + w(b_{k+1},c_{k+1}) \\
    &\quad + w(b_1,c_1) + \cdots + w(b_j,c_j) + w(b_{j+1},d_j) + w(a_{j+1},d_{j+1}) + \cdots + w(a_{k-1},d_{k-1}) \\
    &\le w(a_1,d_1) + \cdots + w(a_{j-1},d_{j-1}) + w(a_j,d_j) + w(a_{j+1},d_{j+1}) + \cdots + w(a_{k-1},d_{k-1}) \\
    &\quad + w(b_1,c_1) + \cdots + w(b_j,c_j) + w(b_{j+1},c_{j+1}) + w(b_{j+2},c_{j+2}) + \cdots + w(b_{k+1},c_{k+1}) \\
    &= g(k-1) + g(k+1).
    \end{aligned}
    $$
    
    The second inequality here is exactly the quadrangle inequality. This proves the convexity.

This result guarantees that the problem can be solved with WQS binary search (known outside China as the Aliens trick). Specifically, consider the parameterized cost function $w_c(j,i):=w(j,i)+c$, solve the problem without a limit on the number of intervals, and let its optimal value be $f_c(n)$. As the real number $c$ increases, the number of intervals in the optimal solution decreases monotonically, so we can binary search for the parameter $c$ that makes the optimal number of intervals exactly $m$. Then the optimal value of the original problem is $f(m,n) = f_c(n)-cm$. The real number $c$ here can be seen as the Lagrange multiplier of the constraint on the number of intervals. Implementing this algorithm involves many details; see the [WQS binary search](./wqs-binary-search.md) page. Its time complexity is $O(n\log n\log C)$, where $C$ is the size of the range of the parameter $c$.

The three algorithms for interval partition with a limit on the number of intervals each have strengths and weaknesses for different data ranges, so choose the right one for the specific problem.

???+ example "Example problem 3: [P4767 \[IOI2000\] Post Office, Enhanced](https://www.luogu.com.cn/problem/P4767)  [P6246 \[IOI2000\] Post Office, Enhanced Further](https://www.luogu.com.cn/problem/P6246)"
    There are some villages beside a highway. The highway is an integer number line, and the position of each village is given by a single integer coordinate. No two villages are at the same place. The distance between two positions is the absolute difference of their integer coordinates.
    
    Post offices will be built in some, but not necessarily all, of the villages. To build the post offices, choose their locations so that the total distance between each village and its nearest post office is minimized.
    
    Write a program that, given the positions of the villages and the number of post offices, computes the minimum possible sum of the distances between each village and its nearest post office.

??? note "Idea"
    Each village has a nearest post office, so each post office also has a set of villages it serves, and it is easy to see this is an interval.
    
    Consider splitting the $n$ villages into $m$ intervals, and then choosing one post office in each interval.
    
    By a standard math fact, for interval $[i,j]$, the post office should be built at village $\left\lfloor\dfrac{i+j}2\right\rfloor$. Using prefix sums, $w(i,j)$ is easy to compute.
    
    The problem becomes interval partition with a limit on the number of intervals. One can prove that $w$ satisfies the quadrangle inequality, so the optimizations above apply directly.

??? note "Implementation 1, the second optimization above, complexity $O(n(n+m))$"
    ```cpp
    --8<-- "docs/dp/code/opt/quadrangle/quadrangle_2.cpp"
    ```

??? note "Implementation 2, WQS binary search, complexity $O(n\log n\log C)$"
    ```cpp
    --8<-- "docs/dp/code/opt/quadrangle/quadrangle_3.cpp"
    ```

## Interval merging problems

Another kind of DP problem that can be optimized with the quadrangle inequality is the interval merging problem: merge $n$ intervals $[i,i]$ of length one pairwise until we get the interval $[1,n]$. Each merge of $[j,k]$ and $[k+1,i]$ costs $w(j,i)$. Find the cheapest way to merge. For such problems, we have the following 2D1D state transition equation:

$$
f(j,i) = \min_{j \leq k < i} f(j,k) + f(k+1,i) + w(j,i) \qquad (1\le j< i\le n) \tag{3}
$$

where the initial cost is $f(i,i)=0$. The brute-force algorithm takes $O(n^3)$ in total, and when decision monotonicity holds, this can be optimized to $O(n^2)$. This algorithm was first proposed by Knuth when solving the optimal binary search tree problem, and was further studied and summarized by Frances Yao. Outside China it is called Knuth's optimization or the Knuth-Yao speedup.

Besides the quadrangle inequality, decision monotonicity for interval merging also requires the cost function to be monotone under interval inclusion.

-   **Monotonicity under interval inclusion**: if for any $a \leq b \leq c \leq d$ we have

    $$
    w(b,c) \leq w(a,d),
    $$

    then the function $w$ is monotone with respect to interval inclusion.

This is really a first-order condition on the cost function: $w(j,i)$ is decreasing in $j$ and increasing in $i$.

???+ note "Lemma 1"
    If $w$ is monotone under interval inclusion and satisfies the quadrangle inequality, then the state $f(j,i)$ satisfies the quadrangle inequality.

??? note "Proof"
    Assume $a \leq b \leq c \leq d$. We prove $f(a,d) + f(b,c) \geq f(a,c) + f(b,d)$ by induction on $d-a$. When $a=b$ or $c=d$, the claim is an equality. In the general case, we split into cases based on where $d'=\operatorname{opt}(a,d)$ lies.
    
    Case 1: $c \leq d'$ or $d' < b$, that is, $[b,c]$ is contained in $[a,d']$ or in $[d'+1,d]$.
    
    Assume $c \leq d'$; the other case is similar. Then
    
    $$
    \begin{aligned}
    f(a,d) + f(b,c)
    & = f(a,d') + f(d'+1,d) + w(a,d) + f(b,c) \\
    & \geq f(a,c) + f(b,d') + f(d'+1,d) + w(a,d) \\
    & \geq f(a,c) + f(b,d') + f(d'+1,d) + w(b,d) \\
    & \geq f(a,c) + f(b,d).
    \end{aligned}
    $$
    
    Here the first inequality comes from the induction hypothesis $f(a,c) + f(b,d') \leq f(a,d') + f(b,c)$, the second from monotonicity under interval inclusion $w(b,d) \leq w(a,d)$, and the third from the optimality condition $f(b,d) \leq f(b,d') + f(d'+1,d) + w(b,d)$.
    
    Case 2: $b \leq d' < c$, that is, $d'$ lies in $[b,c]$. Now consider where $c'=\operatorname{opt}(b,c)$ lies.
    
    Assume $c' \leq d'$, that is, $[b,c']$ is contained in $[a,d']$; the other case is similar. Then
    
    $$
    \begin{aligned}
    f(a,d) + f(b,c)
    & = f(a,d') + f(d'+1,d) + w(a,d) + f(b,c') + f(c'+1,c) + w(b,c) \\
    & \geq f(a,c') + f(c'+1,c) + w(b,c) + f(b,d') + f(d'+1,d) + w(a,d) \\
    & \geq f(a,c') + f(c'+1,c) + w(a,c) + f(b,d') + f(d'+1,d) + w(b,d) \\
    & \geq f(a,c) + f(b,d).
    \end{aligned}
    $$
    
    Here the first inequality comes from the induction hypothesis $f(a,c') + f(b,d') \leq f(a,d') + f(b,c')$, the second from the quadrangle inequality $w(a,c) + w(b,d) \leq w(a,d) + w(b,c)$, and the third from the optimality conditions of $f(a,c)$ and $f(b,d)$.

???+ note "Theorem 4"
    If $w$ is monotone under interval inclusion and satisfies the quadrangle inequality, then the smallest optimal decision $\operatorname{opt}(j,i)$ in problem (3) satisfies
    
    $$
    \operatorname{opt}(j,i-1) \leq \operatorname{opt}(j,i) \leq \operatorname{opt}(j+1,i). \qquad (j + 1 < i)
    $$

??? note "Proof"
    Lemma 1 has shown that $f(j,i)$ satisfies the quadrangle inequality, so the objective $f(j,k) + f(k+1,i) + w(j,i)$, as a function of $(k,i)$ for a fixed $j$, satisfies the quadrangle inequality. By Theorem 1, $\operatorname{opt}(j,i-1) \leq \operatorname{opt}(j,i)$. Note that terms that do not involve both $k$ and $i$ do not affect the quadrangle inequality. Similarly, as a function of $(j,k)$ for a fixed $i$, it also satisfies the quadrangle inequality, so $\operatorname{opt}(j,i) \leq \operatorname{opt}(j+1,i)$. This proves the claim.

Using this result, we can also limit the search range of the decision point $k$. Here, loop over the interval length $i-j+1$ in increasing order, then over all intervals $[j,i]$ of that length. Search all $k$ between $\operatorname{opt}(j,i-1)$ and $\operatorname{opt}(j+1,i)$ by brute force to get the optimal value $f(j,i)$, and record the smallest optimal decision $\operatorname{opt}(j,i)$. For all intervals of the same length, the total length of the decision ranges in this algorithm is $O(n)$, and there are $O(n)$ possible lengths, so the total complexity is $O(n^2)$.

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/dp/code/opt/quadrangle/quadrangle-knuth-optimization.cpp:core"
    ```

## Functions that satisfy the quadrangle inequality

To make it easier to prove that a function satisfies the quadrangle inequality, we have the following properties:

**Property 1**: if functions $w_1(j,i)$ and $w_2(j,i)$ both satisfy the quadrangle inequality (or monotonicity under interval inclusion), then for any $c_1,c_2\geq 0$, the function $c_1w_1+c_2w_2$ also satisfies the quadrangle inequality (or monotonicity under interval inclusion).

**Property 2**: if there exist functions $f(x)$ and $g(x)$ such that $w(j,i) = f(j)-g(i)$, then $w$ satisfies the quadrangle identity. When $f$ and $g$ are increasing, $w$ is also monotone under interval inclusion.

**Property 3**: let $h(x)$ be an increasing convex function. If $w(j,i)$ satisfies the quadrangle inequality and is monotone under interval inclusion, then the composition $h(w(j,i))$ also satisfies the quadrangle inequality and is monotone under interval inclusion.

**Property 4**: let $h(x)$ be a convex function. If $w(j,i)$ satisfies the quadrangle identity and is monotone under interval inclusion, then the composition $h(w(j,i))$ satisfies the quadrangle inequality.

First, one point needs clarifying: Chinese textbooks disagree on the definition of a convex function. Here a convex function means "convex downward", that is, (when differentiable) a function whose first derivative is increasing.

??? note "Proof"
    The first two properties are easy to prove from the definitions. Below we prove the third property; the proof of Property 4 is similar. Since $h(x)$ is monotone, $h(w(j,i))$ naturally stays monotone under interval inclusion. The key is the quadrangle inequality.
    
    For this, consider the second-order mixed difference over $a \leq j \leq b \leq c \leq i \leq d$.
    
    $$
    \begin{aligned}
    \Delta_i\Delta_j h\left(w(j,i)\right)
    &= h\left(w(b,d)\right) - h\left(w(a,c) + \Delta_jw(j,c) + \Delta_iw(a,i)\right) \\
    &\quad + h\left(w(a,c) + \Delta_jw(j,c) + \Delta_iw(a,i)\right) - h\left(w(a,c) + \Delta_jw(j,c)\right) \\
    &\quad - h\left(w(a,c) + \Delta_iw(a,i)\right) + h\left(w(a,c)\right).
    \end{aligned}
    $$
    
    Here, by interval monotonicity, $\Delta_iw(a,i) := w(a,d) - w(a,c) \geq 0$ and $\Delta_jw(j,c) := w(b,c) - w(a,c) \leq 0$. Since $h(x)$ is convex, for $t_1,t_2\geq 0$ we have $h(x + t_1 - t_2) - h(x + t_1) \leq h(x - t_2) - h(x)$, so the sum of the last two lines is non-positive. Also, by the quadrangle inequality, $w(b,d) \leq w(a,c) + \Delta_jw(j,c) + \Delta_iw(a,i) = w(b,c) + w(a,d) - w(a,c)$, so the difference on the first line is also non-positive when $h(x)$ is increasing. So the total second-order mixed difference is non-positive. This is exactly the quadrangle inequality.
    
    This proof is really a discrete version of the following derivative argument.
    
    $$
    \frac{\partial^2}{\partial x\partial y}h(w(x,y)) = h''(w(x,y))\frac{\partial }{\partial x}w(x,y)\frac{\partial}{\partial y}w(x,y) + h'(w(x,y))\frac{\partial^2}{\partial x\partial y}w(x,y) \leq 0.
    $$
    
    This clearly holds when $h' \geq 0$, $h'' \geq 0$, $w_x \leq 0$, $w_y \geq 0$ and $w_{xy} \leq 0$. Here, monotonicity under interval inclusion gives the first-order conditions on $w$, and the quadrangle inequality gives its second-order condition.

## Exercises

-   [Codeforces - Ciel and Gondolas](https://codeforces.com/contest/321/problem/E)(Be careful with I/O!)
-   [SPOJ - LARMY](https://www.spoj.com/problems/LARMY/)
-   [Codechef - CHEFAOR](https://www.codechef.com/problems/CHEFAOR)
-   [Hackerrank - Guardians of the Lunatics](https://www.hackerrank.com/contests/ioi-2014-practice-contest-2/challenges/guardians-lunatics-ioi14)
-   [ACM ICPC World Finals 2017 - Money](https://open.kattis.com/problems/money)

## References and notes

-   [Quora Answer by Michael Levin](https://www.quora.com/What-is-divide-and-conquer-optimization-in-dynamic-programming)
-   [Video Tutorial by "Sothe" the Algorithm Wolf](https://www.youtube.com/watch?v=wLXEWuDWnzI)
-   [Divide and Conquer DP](https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html)
-   [Knuth's Optimization](https://cp-algorithms.com/dynamic_programming/knuth-optimization.html)
-   [Quadrangle Inequality Properties](https://codeforces.com/blog/entry/86306)
-   [Wang Qinshi, "A Brief Analysis of a Class of Binary Search Methods" (Chinese)](https://github.com/hzwer/shareOI/blob/master/%E5%9F%BA%E7%A1%80%E7%AE%97%E6%B3%95/%E6%B5%85%E6%9E%90%E4%B8%80%E7%B1%BB%E4%BA%8C%E5%88%86%E6%96%B9%E6%B3%95_%E7%8E%8B%E9%92%A6%E7%9F%B3.pdf)
-   [Simplified LARSCH Algorithm by noshi91 (Japanese)](https://noshi91.hatenablog.com/entry/2023/02/18/005856)
-   [Quadrangle inequality and decision monotonicity by b6e0\_ - Luogu Column (Chinese)](https://www.luogu.com.cn/article/h81hh5lk)
-   [A budget LARSCH algorithm for online decision monotonicity by Register\_int - Luogu Column (Chinese)](https://www.luogu.com.cn/article/vqf42hah)

[^cmp-min-opt]: "Worse" and "better" in the algorithm description should be read as a lexicographic order that first compares function values and then compares decision points. Under this order, "better" means either a smaller function value, or the same function value with a smaller decision point.

[^larsch]: Larmore, Lawrence L., and Baruch Schieber. "On-line dynamic programming with applications to the prediction of RNA secondary structure." Journal of Algorithms 12, no. 3 (1991): 490-515.
