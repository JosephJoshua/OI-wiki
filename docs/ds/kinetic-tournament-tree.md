author: Jerry3128

Prerequisite: [segment tree](./seg.md)

## Motivating problem

Given a sequence of single-variable linear functions $F=\{f_1,\dots,f_n\}$ with $f_i: \mathbf{R} \rightarrow \mathbf{R}$, where $f_i(x)=k_ix+b_i$ and $k_i,b_i \in \mathbf{R}$. We need to support the following operations:

-   $\operatorname{QueryMax}(l,r)$: given $l$ and $r$, return $\max_{i=l}^r{f_i(0)}$.
-   $\operatorname{TranslateLeft}(l,r,\delta)$: given $l$, $r$ and $\delta$, for all $i\in[l,r]$, perform $f_i(x) \leftarrow f_i(x+\delta)$. This is equivalent to $b_i\leftarrow b_i+k_i\delta$. Here $\delta > 0$.

For convenience, we assume all functions are distinct.

Shifting the linear functions in a range to the left is essentially $b_i \leftarrow k_i\cdot \delta$: for the constant term $b_i$, add the slope $k_i$ times the horizontal shift $\delta$. This operation is the same as the "range add weighted by per-position coefficients" seen in many data structure problems: for each index $i$ in the range $[l, r]$, add a fixed number $\delta$ times that position's own coefficient $k_i$ to its value. So shifting linear functions in a range is really just range addition weighted by per-position coefficients.

To show KTT's unique binary-tree divide and conquer structure, we start directly from the range shift.

## Kinetic Data Structures

Kinetic Data Structures are abbreviated KDS. A KDS maintains properties of a system of geometric objects while they move continuously.

### Event queue

We assume each point has a known flight plan, which gives full or partial information about its motion. For example, the curve or line formed by the function $f_i(x)$ describes the trajectory of moving point $i$ well. The flight plan may change at any time, for example because of a collision or interaction with the environment. We call whatever causes a change in the flight plan an event. The event queue gives the events in time order.

A key aspect of a KDS is having events that are easy to maintain: the event types in the event queue correspond to possible combinatorial changes, and each change involves a constant (and usually small) number of objects. For example, in this problem, one event type we use is "the order between $f_i(0)$ and $f_{j}(0)$ changes".

The event queue can be maintained implicitly.

### Certificates

These events should be equivalent to being guaranteed by the intersection of a set of low-degree algebraic conditions, each involving a finite number of objects. We call these conditions the certificates of the KDS. For example, $[f_i(0) > f_j(0)]$.

## Kinetic Tournament Tree

### Introduction

The Kinetic Tournament Tree (KTT) is a kind of Kinetic Data Structure. It first appeared in the 1999 paper [Data Structures for Mobile Data](https://www.sciencedirect.com/science/article/pii/S0196677498909889) and is used to maintain continuously changing data. More generally, any structure that uses the following kinetization strategy can be called a Kinetic Tournament:

-   Create correctness certificates for the key operations (such as comparisons) of a static algorithm, and attach each certificate to a global event queue that records when the certificate may fail.
-   When a certificate fails, we can efficiently update the algorithm's output and maintain the set of certificates.

In the competitive programming community, it became popular through the 2020 Chinese national training team paper "[A Brief Discussion on Dynamically Maintaining Function Maxima](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/IOI2020%E4%B8%AD%E5%9B%BD%E5%9B%BD%E5%AE%B6%E5%80%99%E9%80%89%E9%98%9F%E8%AE%BA%E6%96%87%E9%9B%86%20%E9%9D%9E%E6%AD%A3%E5%BC%8F%E7%89%88.pdf)". The KTT used in academia and the KTT used in competitive programming differ in applications and implementation, so we introduce a KTT with some optimizations for competitive programming.

### Basic structure

First, let's design a data structure similar to a segment tree for maintaining a static maximum. Build a segment tree, and for each non-leaf node, let its value be the larger of its two children's values. After $O(n)$ comparisons, the root's value is the global maximum. Now the values start to change. As long as the KTT can detect every time the source of a tree node's maximum changes, we can maintain the global maximum.

So that the KTT can detect every time the source of a maximum in the tree changes, for a tree node $x$ and the functions $f_L$ and $f_R$ provided by its left and right children, we define the certificate as "the order between $f_L$ and $f_R$ stays the same". When a certificate fails, we walk down the tree to the node whose certificate failed and update its information. To keep track of when each certificate fails, note that a certificate fails exactly when the two functions have the same value. So the problem becomes finding the x-coordinate of the intersection of two linear functions, which takes $O(1)$ time.

For each tree node, we maintain the function that achieves the maximum at $0$, the time when the current certificate fails, and the earliest failure time of any certificate in the whole subtree. Then whenever a node's certificate fails, we can find that node at that moment and update its information. This information records the functions themselves. Next we handle the range shift operation. Since shifts simply add up, we can handle range shifts with lazy tags.

We define the lazy tag $\Delta_v$ to mean that the functions on all other nodes in $v$'s subtree should be shifted left by $\Delta_v$ units. Now, for a tree node $v$, a new operation shifts all functions in its subtree to the left by $\delta$, that is, $f(x)\leftarrow f(x+\delta)$. We update the lazy tag: $\Delta_v\leftarrow \Delta_v + \delta$, which accumulates the offset of all other nodes in the subtree. A left shift also means the function values at $0$ change. If the certificate fails at x-coordinate $t$, then after the shift it fails at $t-\delta$. If $t-\delta$ crosses $0$, the certificate has failed, so we recurse down to the node holding that certificate, update it, and push the new information up to the root. This process can be done together with the update.

This gives a simple implementation.

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/ds/code/ktt/ktt_1.cpp:core"
    ```

### Complexity analysis

Proving the time complexity of KTT needs potential analysis.

Let $d(x)$ be the depth of node $x$ in the segment tree, with the root at depth $1$. Define the potential of node $x$ in the segment tree as:

$$
\alpha(x) = \begin{cases}
d(x) & \text{if the lower slope function has larger value}  \\
0    & \text{otherwise}\\
\end{cases}
$$

That is, among the two functions compared at $x$, if the one with the smaller slope has the larger value at $0$, the node's potential is $d(x)$; otherwise it is $0$.

Define the potential of the whole KTT as the sum of the potentials of all nodes:

$$
\Phi = \sum_x \alpha(x)
$$

Consider one update of node $x$ and its parent $p$ with actual cost $c=1$, and let the potentials before and after the update be $\Phi$ and $\Phi'$. We compute the amortized cost of updating node $x$. Since node $x$ is being updated, its potential must drop from $d(x)$ to $0$ at this moment. For $p$, in the worst case its potential may rise from $0$ to $d(p)$:

$$
\begin{aligned}
\hat{c} &= 1 + \Phi' - \Phi\\
    &= 1 + (\alpha'(p) + \alpha'(x)) - (\alpha(p) + \alpha(x))\\
    &= 1 + (\alpha'(p) - \alpha(p)) + (\alpha'(x) - \alpha(x))\\
    &\leq 1 + d(p) - d(x)\\
    &= 0
\end{aligned}
$$

Summing the actual costs, with initial potential $\Phi_s$ and final potential $\Phi_t$:

$$
\begin{aligned}
\sum c  &= \sum \hat{c} + \Phi_{s} - \Phi_{t}\\
    &\leq \Phi_{s} - \Phi_{t}\\
    &=O(n\log n)
\end{aligned}
$$

This is the number of certificate-failure updates the KTT performs when there are only global updates.

Additionally, consider how range shifts affect the potential. For one range shift, the nodes we need to consider are those whose subtree contains some, but not all, of the tree nodes being shifted. These are exactly the nodes we pass through in the tree during the update, and there are at most $O(\log n)$ of them. In the worst case each such node's potential rises by $d(x)\le \log n$, so each operation raises the potential by $O(\log^2 n)$.

To support range shifts, the certificate update operation is performed $O(n\log n + m\log^2 n)$ times. Each certificate update walks down the tree to the node whose certificate failed, which takes $O(\log n)$. So the total time complexity is $O(n\log^2 n+ m\log^3 n)$.

What makes this method great is that it already reaches the lower bound $O(\lambda_{s}(n)\log^2 n)$ for the problem's time complexity. Here $\lambda_{s}(n)$ is the maximum length of an (n, s) Davenport–Schinzel sequence. Linear functions correspond to $s=1$, with $\lambda_1(n)=n$. This belongs to computational geometry, so we won't go into it here.

### Higher-degree case

What if we maintain polynomial functions, or even more complex functions, instead of linear ones? Two complex functions may have several intersection points. Given a sequence of continuous, totally defined single-variable functions $F=\{f_1,\dots,f_n\}$ with $f_i: \mathbf{R} \rightarrow \mathbf{R}$, where the graphs of any two functions intersect in at most $s$ points. A typical example is a set of polynomial functions of degree $s$.

For the same problem, we use potential analysis.

Let $d(x)$ be the depth of node $x$ in the segment tree, with the root at depth $1$. Let $I(x)$ be the number of intersection points after $0$ of the two functions compared at node $x$. Define the potential of node $x$ in the segment tree as:

$$
\alpha(x)=d(x)^{\log_2(s+1)}I(x)
$$

Define the potential of the whole KTT as the sum of the potentials of all nodes:

$$
\Phi = \sum_x \alpha(x)
$$

Consider one update of node $x$ and its parent $p$ with actual cost $c=1$, and let the potentials before and after the update be $\Phi$ and $\Phi'$. We compute the amortized cost of updating node $x$. Since node $x$ is being updated, its potential must drop from $d(x)^{\log_2(s+1)}I(x)$ to $d(x)^{\log_2(s+1)}(I(x)-1)$ at this moment. For $p$, in the worst case its potential may rise from $0$ to $d(p)^{\log_2(s+1)}$:

$$
\begin{aligned}
        \hat{c} &= 1 + \Phi' - \Phi\\
                &= 1 + (\alpha'(x) - \alpha(x)) + (\alpha'(p) - \alpha(p))\\
                &\leq 1 - d(x)^{\log_2{(s+1)}} + s(d(x)-1)^{\log_2{(s+1)}}\\
                &\leq 0
    \end{aligned}
$$

Going from the third line to the fourth, we used the fact that $d(x)$ is a positive integer.

Summing the actual costs, with initial potential $\Phi_s$ and final potential $\Phi_t$:

$$
\begin{aligned}
    \sum c  &= \sum \hat{c} - \Phi_t + \Phi_s\\
            &\leq \Phi_s - \Phi_t\\
            &= O(ns (\log n)^{\log_2{(s+1)}})
\end{aligned}
$$

This gives the upper bound $O(ns (\log n)^{1+\log_2{(s+1)}} + ms (\log n)^{2+\log_2{(s+1)}})$.[^ref1]

### Approximate case

Given a sequence of continuous, totally defined single-variable functions $F=\{f_1,\dots,f_n\}$, define $\mathfrak U_F(x)$, $\mathfrak L_F(x)$ and $\mathfrak E_F(x)$ as the upper envelope, lower envelope and extent respectively.

$$
\begin{aligned}
    \mathfrak U_F(x) & = \max\{f_i(x) \mid f_i \in F\} \\
    \mathfrak L_F(x) & = \min\{f_i(x) \mid f_i \in F\} \\
    \mathfrak E_F(x) & = \mathfrak U_F(x) - \mathfrak L_F(x)
\end{aligned}
$$

If we only require the program to return $\tilde{\mathfrak U}_F(x)$ such that

$$
\mathfrak U_F(x) \geq \tilde{\mathfrak U}_F(x) \geq \mathfrak U_F(x) - \epsilon \mathfrak E_F(x)
$$

then even in the complex case we can achieve $O((1/\epsilon^2)n\log^3 n)$, independent of the polynomial degree, and we can also allow functions to be shifted left or right over ranges.

## References and notes

[^ref1]: Note that this only gives an upper bound; the lower bound on the complexity should be $O(\lambda_{s}(n)\log n)$. The author suspects that, to get a tighter upper bound, the potential function here should be built based on the closed form of $\lambda_{s}(n)$ for Davenport–Schinzel sequences.

-   P. K. Agarwal, S. Har-Peled, and K. R. Varadarajan. Approximating extent measures of points. J. ACM, 51(4):606–635, July 2004.
-   J. Basch, L. J. Guibas, and J. Hershberger. Data structures for mobile data. Journal of Algorithms, 31(1):1–28, 1999.
-   G. Alexandron, H. Kaplan, and M. Sharir. Kinetic and dynamic data structures for convex hulls and upper envelopes. Computational Geometry, 36(2):144–158, 2007.
