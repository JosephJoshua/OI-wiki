This page introduces CDQ divide and conquer.

## Introduction

CDQ divide and conquer is an idea rather than a specific algorithm, much like [dynamic programming](../dp/index.md). Today this idea is used very widely. Depending on how it works and how it is written, its uses fall roughly into three types:

-   Solving problems about pairs of points.
-   Optimizing transitions in 1D dynamic programming.
-   Turning some dynamic problems into static problems with CDQ divide and conquer.

The idea of CDQ divide and conquer was first organized and summarized by Chen Danqi (CDQ), an IOI 2008 gold medalist, while she was in high school, and it is named after her.[^ref1]

## Solving problems about pairs of points

Most problems of this kind look like "given a sequence of length $n$, count the pairs of points $(i,j)$ with certain properties" or "given a sequence of length $n$, find a pair of points $(i,j)$ that maximizes some function".

CDQ divide and conquer solves this kind of problem as follows:

1.  Find the midpoint $mid$ of the sequence;

2.  Split all pairs $(i,j)$ into 3 types:

    1.  pairs with $1 \leq i \leq mid,1 \leq j \leq mid$;
    2.  pairs with $1  \leq i \leq mid ,mid+1 \leq j \leq n$;
    3.  pairs with $mid+1 \leq  i \leq n,mid+1 \leq j \leq n$.

3.  Split the sequence $(1,n)$ into two sequences $(1,mid)$ and $(mid+1,n)$. Now pairs of the first type and pairs of the third type each lie entirely within one of these two sequences;

4.  Handle these two types of pairs recursively;

5.  Find a way to handle the pairs of the second type.

As you can see, the idea of CDQ divide and conquer is to keep handing pairs to the left and right halves recursively.

In practice, we usually use a function `solve(l,r)` to handle the pairs with $l \leq i \leq r,l \leq j \leq r$. The recursive part of the process above is done by `solve(l,mid)` and `solve(mid+1,r)`. The remaining pairs of the second type need a separately designed algorithm.

### Example problems

???+ example "[3D Partial Order](https://www.luogu.com.cn/problem/P3810)"
    Given a sequence where each point has three attributes $a_i,b_i,c_i$, find how many pairs $(i,j)$ in the sequence satisfy $a_j \leq a_i$ and $b_j \leq b_i$ and $c_j \leq c_i$ and $j \ne i$.

??? note "Solution idea"
    3D partial order is a classic problem for CDQ divide and conquer.
    
    The problem asks us to count pairs of points in a sequence, so let us try CDQ divide and conquer.
    
    First, sort the sequence by $a$.
    
    Suppose we have written `solve(l,r)`, and the recursion has already taken care of `solve(l,mid)` and `solve(mid+1,r)`. What we need to do now is count, among the pairs $(i,j)$ with $l \leq i \leq mid$, $mid+1 \leq j \leq r$, how many also satisfy the constraints $a_{i} \leq a_{j}$, $b_{i} \leq b_{j}$, $c_{i} \leq c_{j}$.
    
    A little thought shows that the constraint $a_{i} \leq a_{j}$ no longer matters: since $i$ is less than $mid$ and $j$ is greater than $mid$, $i$ is certainly less than $j$; and since the sequence is sorted by $a$, we must have $a_{i} \leq a_{j}$. Two constraints remain: $b_{i} \leq b_{j}$ and $c_{i} \leq c_{j}$. With these constraints we can enumerate $j$ and count how many $i$ satisfy them.
    
    To make the enumeration easy, we sort all points in $(l,mid)$ and in $(mid+1,r)$ by $b$ from smallest to largest. Then we enumerate each $j$ in order, and insert every point $i$ with $b_{i} \leq b_{j}$ into some data structure (here we choose a [Fenwick tree](../ds/fenwick.md)). Now we just query how many points in the Fenwick tree have a $c$ value less than or equal to $c_{j}$, and that tells us how many $i$ can be validly paired with this $j$.
    
    When we insert a point whose $c$ value is $x$, we add one at position $x$ of the Fenwick tree. Querying how many points in the Fenwick tree are less than $x$ is really computing a [prefix sum](../basic/prefix-sum.md). As long as we [discretize](../misc/discrete.md) all the $c$ values beforehand, the complexity is fine.
    
    For each $j$, we need to insert every point $i$ with $b_{i} \leq b_{j}$ into the Fenwick tree. Since all the $i$ and $j$ are already sorted by $b$, we can insert points with two pointers, which cuts the number of Fenwick tree insertions from $O(n^2)$ to $O(n)$.
    
    With this process, we handle all information about the second type of pairs in $O(n\log n)$ time. The time complexity of the algorithm is then $T(n)=T(\lfloor \frac{n}{2} \rfloor)+T(\lceil \frac{n}{2} \rceil)+O(n\log n)=O(n\log^2n)$.

??? note "Example code"
    ```cpp
    --8<-- "docs/misc/code/cdq-divide/cdq-divide_1.cpp"
    ```

???+ example "[CQOI2011 Dynamic Inversions](https://www.luogu.com.cn/problem/P3157)"
    For a sequence $a$, its number of inversions is defined as the number of elements in the set $\{(i,j)| i < j \wedge a_i > a_j \}$.
    
    You are given a permutation of $1\sim n$. $m$ elements are deleted one by one in some order. Your task is to count the number of inversions in the whole sequence before each deletion.

??? note "Example code"
    ```cpp
    --8<-- "docs/misc/code/cdq-divide/cdq-divide_2.cpp"
    ```

## Optimizing 1D/1D dynamic programming transitions with CDQ divide and conquer

Related content: [Optimizing DP with CDQ divide and conquer](../dp/opt/dp-opt.md#dp-optimization-with-cdq-divide-and-conquer)

1D/1D dynamic programming refers to a particular kind of DP problem: the DP array is one-dimensional and each transition takes $O(n)$. If the conditions are right, CDQ divide and conquer can sometimes reduce the time complexity from $O(n^2)$ to $O(n\log^2n)$.

For example, given a sequence where each element has two attributes $a$ and $b$, we want to compute a DP with the following transition:

$dp_{i}=1+ \max_{j=1}^{i-1}dp_{j}[a_{j} < a_{i}][b_{j} < b_{i}]$

This is the DP for a two-dimensional longest increasing subsequence: only a point $j$ with $j < i,a_{j} < a_{i},b_{j} < b_{i}$ can update the DP value of point $i$.

Doing the transitions directly is clearly $O(n^2)$. Below we explain how to optimize the transitions with CDQ divide and conquer.

Notice that the transition from $dp_{j}$ to $dp_{i}$ is also a relation between pairs of points, so we handle it in a way similar to how CDQ divide and conquer handles pairs of points.

This transition process is fairly standard. Suppose the interval we are currently processing is $(l,r)$. The process is roughly:

1.  If $l=r$, the $\max$ part of $dp_{r}$ has already been computed, so just set $dp_{r} \gets dp_{r} + 1$ and return;
2.  Recursively call `solve(l,mid)`;
3.  Handle all transitions from $l \leq j \leq mid$ to $mid+1 \leq i \leq r$;
4.  Recursively call `solve(mid+1,r)`.

Step 3 works almost the same as using CDQ divide and conquer for 3D partial order. When handling the transitions from $l \leq j \leq mid$ to $mid+1 \leq i \leq r$, we no longer need to worry about the constraint $j < i$. So we again sort all points $i$ and $j$ by $a$, insert the points $j$ into a Fenwick tree with two pointers, and finally query the prefix maximum to update $dp_{i}$.

### Proof that the transitions are correct

The biggest difference between this version of CDQ and the version for pairs of points is the part that handles pairs with $l \leq j \leq mid$, $mid+1 \leq i \leq r$. In the version for pairs of points, this part can be placed anywhere. But when using CDQ divide and conquer to optimize DP, this step must be placed between $solve(l,mid)$ and $solve(mid+1,r)$. The reason is that DP transitions are **ordered**: they must satisfy two conditions, or the result is wrong:

1.  Every $dp_{j}$ used to compute $dp_{i}$ must already be fully computed; no "half-finished" values are allowed;

2.  Every $dp_{j}$ that should be used to compute $dp_{i}$ must actually update $dp_{i}$; no $dp_{j}$ may be missed.

These two conditions are easy to satisfy with the $O(n^2)$ brute force, but with CDQ divide and conquer the order of transitions is clearly scrambled, so we need to check that the transitions are correct.

The recursion tree of CDQ divide and conquer is shown below.

![Recursion tree of CDQ divide and conquer](./images/cdq-divide.svg)

Running the process above, take point $8$ as an example: its DP value is updated in the 3 functions `solve(1,8)`, `solve(5,8)` and `solve(7,8)`, and the points used to update it in these three calls are the three disjoint intervals $(1,4)$, $(5,6)$ and $(7,7)$. Take point $5$ as another example: its DP value is handled in `solve(1,4)`, and the interval that updates it is $(1,4)$. Looking closely, you will find that the DP value of a point $i$ is updated $\log$ times, and the intervals that update it are exactly the $\log$ intervals into which $(1,i)$ is split on the segment tree. So we do guarantee that every valid $j$ has updated point $i$, which satisfies condition 2.

Next, let us trace how the algorithm runs:

1.  The first function to finish is `solve(1,1)`. At this point $dp_{1}$ is fully computed;
2.  The first function to perform transitions is `solve(1,2)`. At this point all transitions into $dp_{2}$ are done;
3.  The second function to finish is `solve(2,2)`. At this point $dp_{2}$ is fully computed;
4.  Then `solve(1,2)` finishes, and all $dp$ values in the interval $(1,2)$ are computed;
5.  The next function to perform transitions is `solve(1,4)`. After these transitions, all transitions into $dp_{3}$ are done;
6.  The next function to finish is `solve(3,3)`. Now the dp value of $dp_{3}$ is computed;
7.  The next transitions are in `solve(3,4)`. $dp_{4}$ already received a transition from $(1,2)$ in `solve(1,4)`, and now it receives one from $(3,3)$, so all transitions into $dp_{4}$ are done too;
8.  `solve(4,4)` finishes, and $dp_{4}$ is fully computed;
9.  `solve(3,4)` finishes, and the values in $(3,4)$ are fully computed;
10. `solve(1,4)` finishes, and the values in $(1,4)$ are fully computed.
11. ...

By simulating the calls, we notice one thing: every time `solve(l,r)` finishes, all DP values in the interval $(l,r)$ are fully computed. Since `solve(l,mid)` has already finished every time we perform transitions, every transition we perform is valid, which satisfies condition 1.

From the process above, if we view the recursion tree of CDQ divide and conquer as a segment tree, then CDQ divide and conquer is an **in-order traversal** of this segment tree. So we effectively process all DP values in order; only the transitions are split apart. Therefore the algorithm is correct.

### Example problems

???+ example "[SDOI2011 Missile Interception](https://www.luogu.com.cn/problem/P2487)"
    To defend against missile attacks from an enemy country, a country has developed a missile interception system. But this system has a flaw: although its first shell can reach any height and intercept a missile of any speed, every later shell cannot be higher than the previous one, and the speed of the missile it intercepts cannot be greater than that of the previous one. One day, radar detects incoming enemy missiles. Since the system is still on trial, there is only one set of it, so it may not be able to intercept all the missiles.
    
    If we cannot intercept all the missiles, we of course want the plan that minimizes the country's losses, i.e. the plan that intercepts the most missiles. But there may be several plans that intercept the most missiles. If there are several optimal plans, we pick one of them at random as the final interception plan.
    
    Our spies have obtained the heights and speeds of all enemy missiles. Your task is to compute, under the decision rule above, the probability that each missile is intercepted.

??? note "Example code"
    ```cpp
    --8<-- "docs/misc/code/cdq-divide/cdq-divide_3.cpp"
    ```

## Turning dynamic problems into static problems

In the previous two cases, CDQ divide and conquer splits the sequence in half and recursively handles the relations between pairs of points to get a good complexity. In this section, however, what we split in half is not an ordinary sequence but the sequence of time.

It works for some data structure problems of the form "support modification xxx, then answer query xxx". Such problems have two features:

-   If the queries are handled [offline](offline.md), all operations naturally form a sequence ordered by time.
-   Each modification is closely related to the queries that come after it, and there are $O(n^2)$ such "modification–query" pairs in total.

We can use CDQ divide and conquer on this sequence of operations to handle the relations between modifications and queries.

Similar to CDQ divide and conquer for pairs of points, suppose the sequence being divided is $(l,r)$. We first recursively handle the modification–query relations within $(l,mid)$ and within $(mid,r)$, and then handle all modification–query relations with $l \leq i \leq mid$, $mid+1 \leq j \leq r$, where $i$ is a modification and $j$ is a query.

Note that if the modifications are **independent** of each other, we don't need to care about the time order between handling $l \leq i \leq mid$ and $mid+1 \leq j \leq r$ and the calls `solve(l,mid)` and `solve(mid+1,r)` (for example, in plain addition/subtraction problems). But if the modifications are not independent (for example, assignment operations), what the sequence looks like after a modification may depend on the sequence before it. In that case, the step that handles all modification–query relations crossing mid must be placed between `solve(l,mid)` and `solve(mid+1,r)`. The reason is the same as for optimizing 1D/1D DP with CDQ divide and conquer: only dividing in in-order traversal order guarantees that every modification is applied strictly in time order.

### Example problems

???+ example "Rectangle add, rectangle sum"
    Maintain a two-dimensional array that supports adding a number to every cell in a rectangular region, and answering queries for the sum of a rectangular region.

??? note "Solution idea"
    For the version of this problem without modifications, i.e. "given a two-dimensional array, answer many queries for the sum of a rectangular region", there is a classic approach using a sweep line with a segment tree. Split each rectangle into an insertion and a deletion, split each query into a difference of two-dimensional prefix sums, and then process everything offline. However, the original problem has modifications, so this approach cannot be used directly.
    
    Let us try CDQ divide and conquer. We take all queries and modifications offline. These operations form a sequence, and there are $O(N^2)$ modification–query relations. Following the usual CDQ process, we split all relations into three types. At each level of the division, we only handle the modification–query relations that cross $mid$; the rest are solved recursively.
    
    Notice that all these modifications are completed before the queries. So the problem becomes equivalent to "there are some static rectangles in the plane; answer many queries for the sum over a rectangular region".
    
    Use a sweep line to handle all modification–query relations crossing $mid$ in $O(n\log n)$ time. What is left is to recursively divide the modification–query relations on the left and right sides.
    
    In CDQ divide and conquer implemented this way, the same query is processed $O(\log n)$ times. That is fine, because the sets of modifications contributing to the query each time are disjoint. The total time complexity is $T(n)=T(\lfloor \frac{n}{2} \rfloor)+T(\lceil \frac{n}{2} \rceil)+ O(n\log n)=O(n\log^2n)$.
    
    Looking at the process above, at first we could only solve the static rectangle add / rectangle sum problem, but simply by applying CDQ divide and conquer, we can solve the dynamic rectangle add / rectangle sum problem offline. The key to turning a dynamic problem into a static one is that CDQ divide and conquer only handles the modification–query relations that cross a single point each time, so we only need to consider the simple problem where "all queries come after all modifications". This is exactly why CDQ divide and conquer is called "a tool for turning dynamic problems into static ones".

???+ example "[\[Ynoi2016\] Insects in the Mirror](https://www.luogu.com.cn/problem/P4690)"
    Maintain a sequence $a_i$ of length $n$, with $m$ operations:
    
    1.  Set every value in the interval $[l,r]$ to $x$;
    2.  Query how many distinct numbers appear in the interval $[l,r]$; a number that appears several times is counted once.
    
    In one sentence: range assignment, range count of distinct colors.

??? note "Solution idea"
    For each position, maintain the position of the nearest point to its left with the same color, written $pre_{i}$. Then counting distinct colors in a range becomes a classic two-dimensional point counting problem.
    
    By treating each contiguous run of one color as a single point, one can prove that the total number of changes to $pre$ is $O(n+m)$, i.e. each operation causes only amortized $O(1)$ changes to $pre$ values. So we can use CDQ divide and conquer to solve the dynamic problem of point add, rectangle sum.
    
    The exact changes to the $pre$ array can be handled with `std::set`. This trick of maintaining contiguous intervals with a set is also known as the [old driver tree](./odt.md).

??? note "Example code"
    ```cpp
    --8<-- "docs/misc/code/cdq-divide/cdq-divide_4.cpp"
    ```

???+ example "[\[HNOI2010\] City Construction](https://www.luogu.com.cn/problem/P3206)"
    The PS Kingdom is a large country with many cities. King Louis has racked his brains over transportation between the cities. Louis can build roads between some pairs of cities, and building roads between different cities costs different amounts.
    
    Louis wants to build the fewest roads so that all cities in the country are connected. But for various reasons, the cost of building a road between cities changes over time. Louis keeps receiving messages that the cost of some road has changed. After each message, he wants to know right away the minimum total cost of connecting the cities. Louis has decided to ask you to do this.
    
    In one sentence: given a graph that supports dynamic changes to edge weights, output the total weight of the minimum spanning tree after each change.

??? note "Solution idea"
    In fact, segment tree divide and conquer combined with LCT can solve this problem, but its constant factor is too large and may need clever constant-factor optimization to pass. So let us consider CDQ divide and conquer instead.
    
    Unlike the usual problems solved by CDQ divide and conquer, here there is no modification–query relation to divide on, because we cannot consider on its own "what one edge modification contributes to the MST of the whole graph". The traditional CDQ idea does not seem to work well.
    
    From the previous examples, we can see that ordinary CDQ divide and conquer has a special connection with segment trees: during CDQ divide and conquer we are implicitly building a segment tree (because the recursion tree of CDQ divide and conquer is a segment tree). Ordinary CDQ looks at the relation between the left and right children of a segment tree node. For this problem, we need to look at the relation between a parent and its children instead. In other words, when we are at the interval `$solve(l,r)$`, if we can find a way to make the size of the graph depend only on the length of the interval, we can solve the problem.
    
    So how exactly do we design the algorithm?
    
    Suppose we are building the MST edge set for the interval $(l,r)$, and we already know the MST edge set of its parent. We give the edges that change within the interval $(l,r)$ a weight of $+ \infty$ in one run and $-\infty$ in another, run Kruskal once for each, and find the edges that are in the MST.
    
    For an edge:
    
    -   If, with all modified edge weights set to $+\infty$, the edge does not appear in the MST, then it cannot appear in the MST for any query in $(l,r)$. So we only add the MST's tree edges to the edge set of $(l,r)$.
    -   If, with all modified edge weights set to $-\infty$, the edge appears in the MST, then it must appear in the MST for every query in the interval $(l,r)$. In that case we can use a DSU to contract the vertices joined by these edges, and add the weights of these edges to the answer.
    
    This builds the edge set for the interval $(l,r)$. The MST computed from these edges is equivalent to the MST computed directly on the original graph.
    
    So why is the complexity correct?
    
    First, modified edges are always added to our edge set, and there are $O(len)$ of them.
    
    Next we need to show that the edge set does not contain too many unmodified edges. We only add the tree edges of the MST where the modified edges have weight $+\infty$, so the number of edges we add is at most the number of vertices of the current graph.
    
    Now we only need to show that the number of vertices of the graph at each level of recursion is $O(len)$; then the number of edges is also $O(len)$.
    
    Showing that the number of vertices is $O(len)$ is now quite easy. Each time we recurse down, the edges we contract are the unmodified edges that appear in the $-\infty$ spanning tree. Looking at it the other way, we cut off all modified edges appearing in the $-\infty$ spanning tree. Clearly we cut at most $len$ edges, so the whole graph splits into at most $O(len)$ connected components, and the new graph has $O(len)$ vertices. This proves that every graph we run Kruskal on has size $O(len)$, so the time complexity of each level is $O(n\log n)$.
    
    The time complexity is $T(n)=T(\lfloor \frac{n}{2} \rfloor)+T(\lceil \frac{n}{2} \rceil)+ O(n\log n)=O(n\log^2n)$.
    
    The implementation may be a bit tricky. Note that the DSU cannot use path compression, otherwise it cannot support rollback. You also don't need to actually perform the contraction; each level's Kruskal can simply run directly on the previous level's DSU.

??? note "Example code"
    ```cpp
    --8<-- "docs/misc/code/cdq-divide/cdq-divide_5.cpp"
    ```

## References and notes

[^ref1]: [On the Application of a Class of Divide-and-Conquer Algorithms, Starting from "Cash"](https://www.cs.princeton.edu/~danqic/papers/divide-and-conquer.pdf)
