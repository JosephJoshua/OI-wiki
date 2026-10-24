author: aaron20100919

Tree DP is DP done on a tree. Because trees are naturally recursive, tree DP is usually implemented with recursion.

## Basics

We use the problem below to show the general process of tree DP.

???+ note "Example problem [Luogu P1352 A Party Without a Boss](https://www.luogu.com.cn/problem/P1352)"
    A university has $n$ staff members, numbered $1 \sim N$. They have a reporting hierarchy, so their relationships form a tree rooted at the principal, where each parent node is the direct boss of its child nodes. There is an anniversary party now. Each staff member who is invited adds a certain happiness index $a_i$. However, if a staff member's direct boss comes to the party, that staff member refuses to come no matter what. Write a program to decide which staff members to invite so that the total happiness index is maximized, and output the maximum happiness index.

Let $f(i,0/1)$ be the optimal answer for the subtree rooted at $i$ (a second index of 0 means $i$ does not attend the party, and 1 means $i$ attends).

For each state there are two choices (below, $x$ ranges over the children of $i$):

-   If the boss does not attend, each subordinate may attend or not, so $f(i,0) = \sum\max \{f(x,1),f(x,0)\}$;
-   If the boss attends, none of the subordinates attend, so $f(i,1) = \sum{f(x,0)} + a_i$.

We can use DFS and update the optimal answer of the current node when returning to the level above.

```cpp
--8<-- "docs/dp/code/tree/tree_1.cpp"
```

Usually, a tree DP state is the optimal answer for the current node. First use DFS to compute the optimal answers of all subtrees, then pass them up to the parent to do the transition. In the end, the value at the root is the optimal answer we want.

### Exercises

-   [HDU 2196 Computer](https://acm.hdu.edu.cn/showproblem.php?pid=2196)

-   [POJ 1463 Strategic game](http://poj.org/problem?id=1463)

-   [\[POI2014\]FAR-FarmCraft](https://www.luogu.com.cn/problem/P3574)

## Knapsack on a tree

Knapsack on a tree is, simply put, a combination of the knapsack problem and tree DP.

???+ note "Example problem [Luogu P2014 CTSC1997 Course Selection](https://www.luogu.com.cn/problem/P2014)"
    There are $n$ courses. Course $i$ is worth $a_i$ credits. Each course has zero or one prerequisite. A course with a prerequisite can only be taken after its prerequisite has been completed.
    
    A student wants to take $m$ courses. Find the maximum number of credits they can get.
    
    $n,m \leq 300$

Each course has at most one prerequisite. This is similar to a rooted tree, where each node has at most one parent.

So we can build a tree from this property, and all the courses form a forest. For convenience, we add a new course worth $0$ credits (call it course $0$) and make it the prerequisite of every course that has no prerequisite. This turns the forest into a single tree rooted at course $0$.

Let $f(u,i,j)$ be the maximum credits in the subtree rooted at node $u$, when we have processed the first $i$ child subtrees of $u$ and chosen $j$ courses.

The transition combines tree DP with [knapsack DP](./knapsack/basic.md). We enumerate each child $v$ of $u$, and also enumerate how many courses are chosen in the subtree rooted at $v$, then merge the subtree's result into $u$.

Let $s_x$ be the number of children of node $x$ and $\textit{siz}_x$ the size of the subtree rooted at $x$. The transition is:

$$
f(u,i,j)=\max_{v,k \leq j,k \leq \textit{siz}_v} f(u,i-1,j-k)+f(v,s_v,k)
$$

Note the constraints in the transition above. They make sure meaningless states are never visited.

The second dimension of $f$ can easily be dropped with a rolling array. In that case, $j$ must be enumerated in decreasing order.

It can be shown that the time complexity of this method is $O(nm)$[^note1].

??? note "Reference code"
    ```cpp
    --8<-- "docs/dp/code/tree/tree_2.cpp"
    ```

### Exercises

-   [CTSC1997 Course Selection](https://www.luogu.com.cn/problem/P2014)

-   [JSOI2018 Infiltration](https://loj.ac/problem/2546)

-   [SDOI2017 Apple Tree](https://loj.ac/problem/2268)

-   [Codeforces Round 875 Div. 1 Problem D. Mex Tree](https://codeforces.com/contest/1830/problem/D)

## Rerooting DP

Rerooting DP in tree DP is also called "two-pass scanning". Usually the root is not given, and changing the root affects some values, such as the sum of node depths or the sum of node weights.

It usually takes two DFS passes. The first DFS precomputes information such as depths and weight sums. The second DFS runs the rerooting DP.

Next, we use some example problems to get familiar with this technique.

???+ note "Example problem [\[POI2008\]STA-Station](https://www.luogu.com.cn/problem/P3478)"
    Given a tree with $n$ nodes, find a node such that, when the tree is rooted at it, the sum of the depths of all nodes is maximized.

Let $u$ be the current node and $v$ a child of the current node. First, let $s_i$ be the number of nodes in the subtree rooted at $i$, with $s_u=1+\sum s_v$. Clearly one DFS is enough to compute all $s_i$. This DFS is the preprocessing step: it gives us the number of nodes in each subtree for a fixed root.

Now consider the transition. This is where "rerooting" comes in. Let $f_u$ be the sum of the depths of all nodes when the tree is rooted at $u$.

$f_v\leftarrow f_u$ represents rerooting, that is, moving the root from $u$ to $v$. Clearly, during rerooting, whether the root is $v$ or $u$ changes the depths of some nodes. Specifically:

-   Every node in the subtree of $v$ has its depth decreased by one, so the total depth decreases by $s_v$;

-   Every node not in the subtree of $v$ has its depth increased by one, so the total depth increases by $n-s_v$;

From these two facts we get the transition $f_v = f_u - s_v + n - s_v=f_u + n - 2 \times s_v$.

So in the second DFS we traverse the whole tree and apply the transition $f_v=f_u + n - 2 \times s_v$. This gives the depth sum for every possible root. Finally, we only need to go over the depth sums of all roots once to get the answer.

??? note "Reference code"
    ```cpp
    --8<-- "docs/dp/code/tree/tree_3.cpp"
    ```

### Exercises

-   [Atcoder Educational DP Contest, Problem V, Subtree](https://atcoder.jp/contests/dp/tasks/dp_v)

-   [Educational Codeforces Round 67, Problem E, Tree Painting](https://codeforces.com/contest/1187/problem/E)

-   [POJ 3585 Accumulation Degree](http://poj.org/problem?id=3585)

-   [\[USACO10MAR\]Great Cow Gathering G](https://www.luogu.com.cn/problem/P2986)

-   [CodeForce 708C Centroids](http://codeforces.com/problemset/problem/708/C)

## References and notes

[^note1]: [Proof of the complexity of subtree-merging knapsack DP - LYD729's CSDN blog](https://blog.csdn.net/lyd_7_29/article/details/79854245)
