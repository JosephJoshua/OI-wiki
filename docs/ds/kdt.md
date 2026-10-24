author: hsfzLZH1, Ir1d, JosephusW

A k-D Tree (KDT, k-dimensional tree) is a data structure that can **efficiently handle information in $k$-dimensional space**.

When the number of nodes $n$ is much larger than $2^k$, a k-D Tree runs very efficiently.

In competitive programming problems, usually $k=2$. When analyzing time complexity on this page, we treat $k$ as a constant.

## Building the tree

A k-D Tree has the shape of a binary search tree, and each node of this binary search tree corresponds to a point in $k$-dimensional space. The points in each subtree all lie inside a $k$-dimensional hyperrectangle, and all points inside this hyperrectangle are also in that subtree.

Suppose we know the coordinates of $n$ distinct points in $k$-dimensional space and want to build a k-D Tree from them. The steps are:

1.  If the current hyperrectangle contains only one point, return that point.

2.  Choose a dimension, and split the current hyperrectangle into two hyperrectangles along this dimension.

3.  Choose the split point: pick a point along the chosen dimension. Points whose value in this dimension is less than this point's value go into one hyperrectangle (the left subtree), and the rest go into the other hyperrectangle (the right subtree).

4.  Make the chosen point the root of this subtree, recursively build the left and right subtrees from the two hyperrectangles, and maintain the subtree information.

To make this easier to understand, here is an example with $k=2$.

![](./images/kdt1.jpg)

The k-D Tree built from it might look like this:

![](./images/kdt2.jpg)

The coordinates on each node of the tree are the coordinates of the chosen split point, and the $x$ or $y$ next to each non-leaf node is the chosen split dimension.

With this approach, the complexity is not guaranteed. For steps $2$ and $3$, we propose two optimizations:

1.  Choose the $k$ dimensions in turn, so that every dimension is split at least once in any $k$ consecutive levels.
2.  Each time, choose the **median** along the dimension as the split point. This keeps the sizes of the left and right subtrees as equal as possible.

You can see that with optimization $2$, the height of the k-D Tree is at most $\log n+O(1)$.

Now the bottleneck in building a k-D Tree is quickly finding the median along a dimension, putting the points whose value in that dimension is less than the median to its left and the rest to its right. If we sort along that dimension with `sort` every time, the time complexity is $O(n\log^2 n)$. In fact, finding the median of $n$ elements and putting it in its correct sorted position can be done in $O(n)$.

Let's recall the idea of quicksort. Each time we pick a number, put the numbers smaller than it on its left and the numbers larger than it on its right, so that this number is at its correct sorted position. Then we recursively sort the left and right parts. The expected complexity is $O(n\log n)$. But a k-D Tree only needs the median to be at its correct sorted position, so we only need to recursively sort the **one side** that contains the median. One can prove that the expected complexity of this is $O(n)$. The `algorithm` library has a function `nth_element()` that does exactly this. To find the value that would be at position `s[mid]` after sorting the values between `s[l]` and `s[r]` by the ordering `cmp`, while making sure the values left of `s[mid]` are smaller than `s[mid]` and the values on its right are larger, just write `nth_element(s+l,s+mid,s+r+1,cmp)`.

Using this idea, building a k-D Tree takes $O(n\log n)$ time.

## Operations in high-dimensional space

To query some information about all points inside a high-dimensional rectangle, store for each node the maximum and minimum coordinates in each dimension over its subtree. If the rectangle of the current subtree does not intersect the query rectangle, do not search its subtree. If the rectangle of the current subtree lies entirely inside the query rectangle, return the sum of the weights of all points in the current subtree. Otherwise, check whether the current point is inside the query rectangle, update the answer, and recursively search the left and right subtrees.

??? note "Implementation"
    ```cpp
    int query(int p) {
      if (!p) return 0;
      bool flag{false};
      for (int k : {0, 1}) flag |= (!(l.x[k] <= t[p].L[k] && t[p].R[k] <= h.x[k]));
      if (!flag) return t[p].sum;
      for (int k : {0, 1})
        if (t[p].R[k] < l.x[k] || h.x[k] < t[p].L[k]) return 0;
      int ans{0};
      flag = false;
      for (int k : {0, 1}) flag |= (!(l.x[k] <= t[p].x[k] && t[p].x[k] <= h.x[k]));
      if (!flag) ans = t[p].v;
      return ans += query(t[p].l) + query(t[p].r);
    }
    ```

### Complexity analysis

First consider the 2D case. When querying a rectangle $R$, we split the nodes of the k-D Tree into three kinds:

1.  Disjoint from $R$.
2.  Fully contained in $R$.
3.  Partly contained in $R$.

Clearly, the cost of a single query is the number of nodes of kind 3. Note that the rectangles of kind-3 nodes either fully contain $R$ or do not contain each other. There are clearly only $O(h)=O(\log n)$ of the former, so now we count the latter.

First, we may shift all edges of the query rectangle by $\epsilon$, so that the query rectangle does not pass through any existing point. Clearly this does not change the set of points covered by the query.

Note that for kind-3 nodes whose rectangles do not contain each other, some edge of $R$ must pass through each of those rectangles. So we only need to count how many rectangles each edge of $R$ passes through, that is, the maximum number of node rectangles any one segment can pass through.

Consider a node $u$. It has four grandchildren, and going from $u$ to each grandchild makes one split in each of the two dimensions. If you look at this carefully, you will see that when a rectangle is split into four sub-rectangles this way, a segment parallel to an axis passes through at most two of the regions. That is, a query starting from $u$ goes down into at most two grandchildren that still contain kind-3 nodes. (This may fail if the segment lies exactly on a split boundary, but shifting the query rectangle's edges rules this case out.)

When building the tree, each point is the median of its whole subtree in the current split dimension, so the subtree size is always halved. So if the size of $u$'s subtree is $n$, we get the recurrence:

$$
T(n)=2T(n/4)+O(1)
$$

By the master theorem, $T(n)=O(\sqrt{n})$.

Generalizing the recurrence to a fixed dimension $k\ge 2$ gives $T(n)=2^{k-1}T(n/2^k)+O(1)$, so $T(n)=O(n^{1-\frac1k})$. When $k=1$, the recurrence is $T(n)=T(n/2)+O(1)$, and the complexity is $O(\log n)$.

### Insertion/deletion

If the $k$-dimensional point set can change, meaning points may be inserted or deleted, then the balance of the k-D Tree is no longer guaranteed. Because of how a k-D Tree is structured, you cannot use binary search tree rotations to keep it balanced, and random priorities like those in an FHQ Treap do not guarantee the complexity either. Below are several ways to maintain it. All of them assume $k\ge 2$ is a constant and the query is a count or weight sum over a rectangle.

#### Scapegoat-style rebuilding

Consider the insert-only case. After an insertion, check the subtree sizes along the insertion path, flatten any unbalanced subtree, and rebuild it using medians. When rebuilding, still choose the split dimension cyclically by node depth. Fix a constant $\frac12<\alpha<1$, and require that after each operation, every node satisfies

$$
\max\{\operatorname{size}(\mathrm{left}),\operatorname{size}(\mathrm{right})\}\le\alpha\operatorname{size}(\mathrm{parent}).
$$

Under this weight-balance condition, the worst-case time of a single query is guaranteed to be

$$
O(n^p),\qquad p=\frac{k-1}{k-1+\log_2(1/\alpha)}.
$$

Here $n$ is the number of nodes kept in the tree. For fixed $\frac12<\alpha<1$, we have $1-\frac1k<p<1$. For example, with $k=2$ and $\alpha=0.6$, $p\approx 0.5757$; with $k=2$ and $\alpha=0.75$, $p\approx 0.7067$.

??? note "Proof of complexity"
    Consider the hyperplane $x_i=c$ that contains one of the boundaries, and count only the non-empty subtrees whose bounding boxes are crossed by this hyperplane.
    
    When splitting along dimension $i$, at most one child's bounding box is crossed, and that child's size is at most $\alpha$ times its parent's. When splitting along other dimensions, at most two children's bounding boxes are crossed, but their total size is at most the parent's size. So every time we go down a full $k$ levels, the number of crossed subtrees grows by a factor of at most $b=2^{k-1}$, and **the total size of these subtrees** shrinks by a factor of at least $\alpha$.
    
    Let $a_j$ be the number of crossed non-empty subtrees at depth $jk$. Bounding it by count and by total size separately gives
    
    $$
    a_j\le b^j,\qquad a_j\le n\alpha^j,
    $$
    
    Between two adjacent such depths there are only $k-1$ levels, which add at most a constant factor more nodes. So the total is
    
    $$
    O\left(\sum_{j\ge 0}\min\{b^j,n\alpha^j\}\right).
    $$
    
    Let $L=\lfloor\log_{b/\alpha}n\rfloor$ and split the sum at $L$. Bound the first part with $b^j$ and the second part with $n\alpha^j$. This gives
    
    $$
    \sum_{j\ge 0}\min\{b^j,n\alpha^j\}
    \le\sum_{j=0}^{L}b^j+n\sum_{j=L+1}^{\infty}\alpha^j
    =O(n^{\log_{b/\alpha}b})=O(n^p).
    $$
    
    Every node where the recursion continues has a bounding box crossed by some boundary hyperplane of the query rectangle, and each such node visits at most two extra children. Adding up the contributions of all $2k$ boundaries gives the upper bound for a single query.

Rebuilding a subtree of size $s$ takes $O(s\log s)$ time. Right after a rebuild, both children have size at most $s/2$. To break the fixed $\alpha$ weight balance again, at least $\Omega(s)$ points must be inserted into this subtree. Spreading the rebuild cost over these insertions, each insertion pays $O(\log N)$ at each ancestor, and there are $O(\log N)$ ancestors. So the amortized cost of one insertion is $O(\log^2 N)$, where $N$ is the maximum size of the tree during the operations.

#### Sqrt rebuilding

On insertion, first store the points to be inserted, and rebuild once every $B$ insertions.

For deletion, just mark the point as deleted. If you need stricter bounds, you can keep track of how many points in the tree have been deleted and rebuild when this reaches $B$.

Updates cost amortized $O(n\log n/B)$, and queries cost $O(B+n^{1-\frac1k})$. If the numbers of the two are of the same order, $B=O(\sqrt{n\log n})$ is optimal (updates $O(\sqrt{n\log n})$, queries $O(\sqrt{n\log n}+n^{1-\frac1k})$).

#### Binary grouping

Maintain several k-D Trees whose sizes are powers of $2$ (with natural-number exponents), so that their sizes add up to $n$.

On insertion, add a new k-D Tree of size $1$, then keep merging trees of the same size (just flatten and rebuild). In the implementation, you can rebuild only once.

It is easy to see that the trees to be merged always start from size $2^0$ with consecutive exponents. Starting from an empty structure and doing $n$ insertions, a tree of size $2^i$ is rebuilt at most $O(n/2^i)$ times, each costing $O(2^i(i+1))$ time. Summing over all $i$, the total time is $O(n\log^2 n)$, so the amortized cost of one insertion is $O(\log^2 n)$.

To query, simply query each tree separately. The complexity is $O\left(\sum_{i\geq0} (\frac n{2^i})^{1-\frac1k}\right)=O(n^{1-\frac1k})$.

So for a sequence of operations with only insertions and rectangle count/sum queries, binary grouping keeps $O(\log^2 n)$ amortized insertion and $O(n)$ space, while giving a better query bound than the weight-balance analysis above with a fixed $\alpha>\frac12$.

### Example problem

???+ note "[Luogu P4148 Simple Problem](https://www.luogu.com.cn/problem/P4148)"
    On an $n\times n$ 2D matrix whose values are all initially $0$, perform $q$ operations. Each operation is one of the following:
    
    1.  `1 x y A`: add $A$ to the number at $(x,y)$.
    2.  `2 x1 y1 x2 y2`: output the sum of the numbers inside the rectangle (including its border) whose lower-left corner is $(x1,y1)$ and upper-right corner is $(x2,y2)$.
    
    The problem is forced online. Memory limit `20M`. The answer and all intermediate values are guaranteed to fit in `int`.
    
    $1\le n\le 500000 , 1\le q\le 200000$

The 20M memory limit rules out all tree-of-trees approaches, and forcing the problem online rules out CDQ divide and conquer, so the only choice is a k-D Tree.

Here is reference code using binary grouping.

??? note "Reference code"
    ```cpp
    --8<-- "docs/ds/code/kdt/kdt_3.cpp"
    ```

## Neighborhood queries

???+ warning "Warning"
    A single nearest-point query with a k-D Tree still takes $O(n)$ time in the worst case, but it is a very good partial-credit trick. Keep this in mind when you use it. The explanation of neighborhood queries here is only meant to deepen your understanding of the k-D Tree structure.

???+ note "Example problem [Luogu P1429 Closest Pair of Points in the Plane (Enhanced)](https://www.luogu.com.cn/problem/P1429)"
    Given $n$ points $(x_i,y_i)$ in the plane, find the [Euclidean distance](../geometry/distance.md#欧氏距离) between the closest pair of points.
    
    $2\le n\le 200000 , 0\le x_i,y_i\le 10^9$

First build a 2-D Tree on these $n$ points.

Enumerate each node, and for each node find the point closest to it other than itself. This gives the answer. Brute-force traversing every node of the 2-D Tree takes $O(n)$ time per query, so we need pruning. We can maintain the minimum and maximum coordinates in each dimension over all nodes in a subtree. Suppose the distance of the closest pair found so far is $ans$. If the **minimum** distance from the query point to the rectangle containing all points in a subtree is greater than or equal to $ans$, then that subtree cannot contain the answer, so the search does not enter it.

Also, you can use a heuristic search: if both subtrees of a node may contain the answer, search the subtree closer to the query point first. You can think of **the minimum distance from the query point to a subtree's rectangle as the heuristic function for this problem**.

??? note "Reference code"
    ```cpp
    --8<-- "docs/ds/code/kdt/kdt_1.cpp"
    ```

???+ note "Example problem [CQOI2016 K Farthest Point Pairs](https://loj.ac/problem/2043)"
    Given $n$ points $(x_i,y_i)$ in the plane, find the Euclidean distance of the $k$-th farthest unordered pair of points.
    
    $n\le 100000 , 1\le k\le 100 , 0\le x_i,y_i<2^{31}$

This is similar to the previous example, but instead of the closest pair we want the $k$-th farthest pair, and the heuristic function becomes the maximum distance from the query point to the rectangle of a subtree. Use a min-heap to keep the distances of the $k$ farthest pairs found so far. If a pair found is farther than the heap top, pop the heap top and push this distance. Likewise, use the distance at the heap top for pruning.

Since the problem asks about unordered pairs, meaning swapping the two points gives the same pair, each ordered pair is counted twice. So the $k$ read from input should be multiplied by $2$.

??? note "Reference code"
    ```cpp
    --8<-- "docs/ds/code/kdt/kdt_2.cpp"
    ```

## Exercises

[SDOI2010 Hide and Seek](https://www.luogu.com.cn/problem/P2479)

[Violet Angel Doll / SJY Placing Chess Pieces](https://www.luogu.com.cn/problem/P4169)

[National Training Team JZPFAR](https://www.luogu.com.cn/problem/P2093)

[BOI2007 Mokia](https://www.luogu.com.cn/problem/P4390)

[Luogu P4475 Chocolate Kingdom](https://www.luogu.com.cn/problem/P4475)

[CH Weak Province Mock R2 TATT](https://www.luogu.com.cn/problem/P3769)
