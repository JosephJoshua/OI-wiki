## Introduction

This page lists some common optimization methods for dynamic programming (DP). "DP optimization" refers to the fact that for many DP problems, the naive state transition equation is easy to write down but slow to compute directly, so we need some tricks to lower the time complexity.

These methods are closely related, often share similar ideas, and frequently need to be combined. So this article only gives a rough classification and focuses on the most basic ideas.

## Optimization with common techniques

The transitions of many DP problems can be sped up with common algorithms and data structures.

There are two common situations for these techniques. In the first, the DP problem has a state transition equation like this:

$$
f(i) = F(a_i,\{f(j) : j < i\}).
$$

Here, computing the current state $f(i)$ depends on the current input $a_i$ and on the states of the whole sequence before it, $\{f(j):j < i\}$. So we can maintain a data structure and treat each computation of $f(i)$ as a query. After obtaining the current state $f(i)$, we perform an update on the data structure so it can be used by later transitions.

In the second situation, the DP problem has a state transition equation like this:

$$
f(i,\cdot) = F(a_i,f(i-1,\cdot)).
$$

Here, each $f(i,\cdot)$ is an array or some other fairly complex object. So although $f(i,\cdot)$ depends only on the single previous state, one transition is very expensive and needs to be optimized with data structures or other techniques.

### DP optimization with prefix sums

Related page: [Prefix sums](../../basic/prefix-sum.md#prefix-sums)

If computing the current state depends on the sum of a subarray of earlier states, we can speed it up by maintaining prefix sums. Problems that involve higher-dimensional prefix sums are also called [SOS DP](../../basic/prefix-sum.md#special-case-sum-over-subsets-dp).

Exercises:

-   [Luogu P2513 \[HAOI2009\] Inversion Sequence](https://www.luogu.com.cn/problem/P2513)
-   [AtCoder Educational DP Contest M - Candies](https://atcoder.jp/contests/dp/tasks/dp_m)

### DP optimization with monotonic queues/stacks

Main page: [Monotonic queue/stack optimization](./monotonic-queue-stack.md)

If the current state depends on information such as the maximum or minimum of earlier states over a range, we can speed things up by maintaining a monotonic queue or monotonic stack.

### DP optimization with segment trees/Fenwick trees

Related pages: [Segment tree](../../ds/seg.md), [Fenwick tree](../../ds/fenwick.md)

If each transition queries the sum, maximum/minimum or similar information over some range, or if a single update involves a range update, we can speed things up by maintaining a segment tree or Fenwick tree.

Exercises:

-   [AtCoder Educational DP Contest Q - Flowers](https://atcoder.jp/contests/dp/tasks/dp_q)
-   [AtCoder Educational DP Contest W - Intervals](https://atcoder.jp/contests/dp/tasks/dp_w)
-   [Codeforces 115 E. Linear Kingdom Races](https://codeforces.com/problemset/problem/115/E)

### DP optimization with CDQ divide and conquer

Main page: [DP optimization with CDQ divide and conquer](../../misc/cdq-divide.md#optimizing-1d1d-dynamic-programming-transitions-with-cdq-divide-and-conquer)

As above, view the whole DP process as a sequence of queries and updates. For some problems, computing them in order is too slow; instead, we can process all queries and updates offline and use CDQ divide and conquer to speed things up.

CDQ divide and conquer for DP optimization also often appears in the following kinds of problems:

-   [Convex hull trick DP based on CDQ divide and conquer](./slope.md#dp-optimization-with-binary-searchcdqbalanced-trees)
-   [Divide and conquer optimization for DP with monotonic slopes](./quadrangle.md#divide-and-conquer)

### DP optimization with binary lifting

Related page: [Binary lifting](../../basic/binary-lifting.md)

In some problems, the state $f(i)$ is defined as the result after applying $2^i$ transitions starting from the initial state. This uses the idea of binary lifting to transform the original problem, so it is often called binary lifting DP optimization.

Sometimes DP problems whose state transition equation looks like

$$
f(i,j) = f(i-1,f(i-1,j))
$$

are also called binary lifting (optimized) DP.

Exercises:

-   [Luogu P1081 \[NOIP 2012 Senior Group\] Driving Trip](https://www.luogu.com.cn/problem/P1081)
-   [Luogu P1613 Running Away](https://www.luogu.com.cn/problem/P1613)
-   [Luogu P4739 \[CERC2017\] Donut Drone](https://www.luogu.com.cn/problem/P4739)

## Optimization using problem structure

Many DP problems have structural properties such as convexity or monotonicity. Using these properties well can lead to fast solutions.

### Convex hull trick DP

Main page: [Convex hull trick](./slope.md)

Similar to the methods in the previous section, if the problem is convex, we can speed up each transition by maintaining a convex hull.

### Quadrangle inequality DP optimization

Main page: [Quadrangle inequality optimization](./quadrangle.md)

DP problems whose functions satisfy the quadrangle inequality often have some kind of decision monotonicity. Many dedicated methods use this property to lower the complexity. Common problem types include one-dimensional decision monotonicity problems, interval partition problems, and interval merging problems.

### Slope Trick DP optimization

Main page: [Slope Trick](./slope-trick.md)

In some problems, the differences (that is, the slopes) of the state function are easier to maintain during transitions. This optimization usually also requires the problem to be convex.

### WQS binary search / convex optimization DP

Main page: [WQS binary search](./wqs-binary-search.md)

For an optimization DP problem with a limit on the count, if the problem is easier to solve without the count limit, and the optimal value is a convex function of that limit, then WQS binary search can simplify the computation.

## Optimization with mathematical methods

The transitions of many DP problems can be sped up with mathematical tools.

### DP optimization with fast matrix exponentiation

Related page: [Fast exponentiation](../../math/binary-exponentiation.md)

If the state transition equation of a DP problem can be written in an autonomous form

$$
f(i) = F(f(i-1)),
$$

that is, the current state $f(i)$ depends only on the previous state $f(i-1)$ and not on any other input, then we can directly use fast exponentiation to compute

$$
f(n) = F^n(f(0))
$$

and get the final answer. Since a single step $F$ can often be written as a matrix, this method is usually called fast matrix exponentiation DP optimization. In fact, any associative transformation (that is, any element of a [monoid](../../math/algebra/basic.md#groups)) can be sped up this way.

Exercises:

-   [Luogu P1397 \[NOI2013\] Matrix Game](https://www.luogu.com.cn/problem/P1397)
-   [Luogu P3176 \[HAOI2015\] Splitting Digit Strings](https://www.luogu.com.cn/problem/P3176)
-   [Codeforces 576 D. Flights for Regular Customers](https://codeforces.com/problemset/problem/576/D)
-   [Luogu P6772 \[NOI2020\] Gourmet](https://www.luogu.com.cn/problem/P6772)

### DP optimization with FFT

Related page: [FFT](../../math/poly/fft.md)

If the state transition equation of a DP problem is a convolution, consider using FFT to speed up the transitions. Depending on the problem, other polynomial techniques may also be useful.

Exercises:

-   [Codeforces 553 E. Kyoya and Train](https://codeforces.com/contest/553/problem/E)
-   [Codeforces 1784 D. Wooden Spoon](https://codeforces.com/problemset/problem/1784/D)

### DP optimization with Lagrange interpolation

Related page: [Lagrange interpolation](../../math/numerical/interp.md#lagrange-interpolation)

In some DP problems, the state function $f(i,j)$ is a polynomial of degree $k$ in $j$. Then we can compute its values at $k+1$ points by brute force, and use Lagrange interpolation to find the expression of $f(i,\cdot)$. This speeds up transitions or even gives the answer directly.

Exercises:

-   [Luogu P5223 Function](https://www.luogu.com.cn/problem/P5223)
-   [Luogu P4463 \[National Training Team Mutual Test 2012\] calc](https://www.luogu.com.cn/problem/P4463)
-   [Luogu P5469 \[NOI2019\] Robot](https://www.luogu.com.cn/problem/P5469)

## Optimization by simplifying states

Besides optimizing transitions, we can also lower the complexity by simplifying the states.

### DP of DP and DFA minimization

Main pages: [DP of DP](../dp-of-dp.md), [DFA minimization](../../misc/fsm.md#dfa-minimization)

In some DP problems, the state function can be written as $f(i,x)$, but the transitions of $x$ itself are complicated and may even depend on another DP problem. For such problems, we can first build an automaton for the transitions of state $x$, reduce the number of states with DFA minimization, and then run the outer DP.

### DP optimization through state design

Main page: [State design optimization](./state.md)

Some special problems allow a clever state design that greatly reduces the number of states.

## Further reading

-   [A grab bag of DP optimization methods by Alex Wei (Chinese)](https://www.cnblogs.com/alex-wei/p/DP_Involution.html)
