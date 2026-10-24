author: HeRaNO, JuicyMio, Xeonacid, sailordiary, ouuan, Pig-Eat-Earth

![](images/disjoint-set.svg)

## Introduction

A disjoint set union (DSU) is a data structure that tracks which set each element belongs to. It is implemented as a forest: each tree represents a set, and the nodes of a tree are the elements of that set.

As its other name, union-find, suggests, a DSU supports two operations:

-   Unite: merge the sets that two elements belong to (merge the corresponding trees).
-   Find: find the set an element belongs to (find the root of its tree). This can be used to check whether two elements are in the same set.

With some modifications, a DSU can support deleting or moving a single element, or maintaining edge weights on the trees. Using a dynamically allocated segment tree, you can also build a [persistent DSU](./persistent-seg.md#拓展基于主席树的可持久化并查集).

???+ warning "Warning"
    A DSU cannot split sets with low complexity.

## Initialization

At the start, every element is in its own set, represented by a tree with only a root. For convenience, we set the root's parent to itself.

???+ example "Implementation"
    === "C++"
        ```cpp
        struct dsu {
          vector<size_t> pa;
        
          explicit dsu(size_t size) : pa(size) { iota(pa.begin(), pa.end(), 0); }
        };
        ```
    
    === "Python"
        ```python
        class Dsu:
            def __init__(self, size):
                self.pa = list(range(size))
        ```

## Find

We move up the tree until we reach the root.

![](images/disjoint-set-find.svg)

???+ example "Implementation"
    === "C++"
        ```cpp
        size_t dsu::find(size_t x) { return pa[x] == x ? x : find(pa[x]); }
        ```
    
    === "Python"
        ```python
        def find(self, x):
            return x if self.pa[x] == x else self.find(self.pa[x])
        ```

### Path compression

Every element visited during a find belongs to the same set, so we can link each of them directly to the root to speed up later finds.

![](images/disjoint-set-compress.svg)

???+ example "Implementation"
    === "C++"
        ```cpp
        size_t dsu::find(size_t x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }
        ```
    
    === "Python"
        ```python
        def find(self, x):
            if self.pa[x] != x:
                self.pa[x] = self.find(self.pa[x])
            return self.pa[x]
        ```

## Unite

To merge two trees, we just link the root of one tree to the root of the other.

![](images/disjoint-set-merge.svg)

???+ example "Implementation"
    === "C++"
        ```cpp
        void dsu::unite(size_t x, size_t y) { pa[find(x)] = find(y); }
        ```
    
    === "Python"
        ```python
        def unite(self, x, y):
            self.pa[self.find(x)] = self.find(y)
        ```

### Union by size/rank

When merging, the choice of which root becomes the root of the new tree affects the complexity of later operations. We can link the tree with fewer nodes, or smaller depth, under the other one, so that the trees don't degenerate.

??? note "Detailed complexity discussion"
    Since we only need to support merging and finding sets, when we merge two sets into one, we get a correct result no matter which set we link under the other. But the different choices have different time complexities. Specifically, if we link a set tree that has both fewer nodes and smaller depth under a larger set tree, later finds clearly take less time than with the opposite choice (and this also gives a better worst-case time complexity).
    
    Of course, we don't always get sets that are exactly like this, with both fewer nodes and smaller depth. Since both the node count and the depth are easy to maintain, we usually pick one of them as the heuristic. Whichever we choose, the time complexity is $O (m\alpha(m,n))$; for the proof, see the papers cited in the References.
    
    In real contest code, even without union by size/rank, code usually finishes within the time limit. Tarjan's paper[^tarjan1984worst] proves that with only path compression and no union by size/rank, the worst-case time complexity is $O (m \log n)$. Andrew Yao's paper[^yao1985expected] proves that with only path compression and no union by size/rank, the average-case time complexity is still $O (m\alpha(m,n))$.
    
    If we use only union by size/rank and no path compression, the time complexity is $O(m\log n)$. Because path compression can cause many modifications in a single operation, it is sometimes not suitable. For example, a persistent DSU, or a DSU combined with segment tree divide and conquer, usually uses only union by size/rank.

A reference implementation of union by size (note that the initialization needs to change):

???+ example "Implementation"
    === "C++"
        ```cpp
        struct dsu {
          vector<size_t> pa, size;
        
          explicit dsu(size_t size_) : pa(size_), size(size_, 1) {
            iota(pa.begin(), pa.end(), 0);
          }
        
          void unite(size_t x, size_t y) {
            x = find(x), y = find(y);
            if (x == y) return;
            if (size[x] < size[y]) swap(x, y);
            pa[y] = x;
            size[x] += size[y];
          }
        };
        ```
    
    === "Python"
        ```python
        class Dsu:
            def __init__(self, size):
                self.pa = list(range(size))
                self.size = [1] * size
        
            def unite(self, x, y):
                x, y = self.find(x), self.find(y)
                if x == y:
                    return
                if self.size[x] < self.size[y]:
                    x, y = y, x
                self.pa[y] = x
                self.size[x] += self.size[y]
        ```

## Reference implementation

A complete DSU implementation with path compression and union by size is shown below:

??? example "Template problem [Luogu P3367 [Template] Disjoint Set Union](https://www.luogu.com.cn/problem/P3367) reference implementation"
    === "C++"
        ```cpp
        --8<-- "docs/ds/code/dsu/dsu_0.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/ds/code/dsu/dsu_0.py"
        ```

## Complexity

With both path compression and union by size/rank, each DSU operation takes only $O(\alpha(n))$ time on average, where $\alpha$ is the inverse Ackermann function, which grows extremely slowly. In other words, the average running time of a single DSU operation can be treated as a very small constant. The proof of the time complexity is on [this page](./dsu-complexity.md).

???+ info "The inverse Ackermann function"
    The [Ackermann function](https://en.wikipedia.org/wiki/Ackermann_function)  $A(m, n)$ is defined as follows:
    
    $A(m, n) = \begin{cases}n+1&\text{if }m=0\\A(m-1,1)&\text{if }m>0\text{ and }n=0\\A(m-1,A(m,n-1))&\text{otherwise}\end{cases}$
    
    The inverse Ackermann function $\alpha(n)$ is defined as the inverse of the Ackermann function, that is, the largest integer $m$ such that $A(m, m) \leqslant n$.

The space complexity of a DSU is clearly $O(n)$.

## Extended operations

On top of the plain DSU, we can make a series of changes so that it supports more operations or maintains more complex information.

### DSU with deletion

A plain DSU can't support deletion, because deleting a node unavoidably deletes every node in the subtree rooted at it. To solve this, a DSU with deletion can add virtual nodes so that every node that actually stores data is always a leaf. To do this, during initialization we create a virtual node for each data node and set the data node's parent to that virtual node. Since every merge only links the roots of the two trees, only virtual nodes ever have children. This guarantees that deleting a node never deletes other nodes by mistake.

Note that after deleting a single node, we must create a new virtual node as its parent; otherwise later merges and deletions won't work correctly.

??? example "Template problem [SPOJ JMFILTER - Junk-Mail Filter](https://www.spoj.com/problems/JMFILTER/) reference implementation"
    === "C++"
        ```cpp
        --8<-- "docs/ds/code/dsu/dsu_4.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/ds/code/dsu/dsu_4.py"
        ```

A similar method can also be used to move a single element between sets. See the example problem for details.

### Weighted DSU

We can also define some kind of weight on the DSU's edges, together with how these weights combine during path compression, to solve more problems. For example, in the classic "NOI2001 Food Chain", we can maintain the additive group modulo $3$ on the edge weights. For problems like this, where edge weights are taken modulo a very small number, we can also split each DSU element into several states. This special-case technique is also called a "DSU with categories" or "extended-domain DSU". The example problems below show these approaches.

To maintain edge weights in a DSU, we push each edge weight down to the child node. So each node stores the weight of the edge between it and its parent. We only need to adjust the weight when a node's parent changes. In general, this can happen during path compression and when merging two nodes. For example, if the edge weight is the distance between the node and its parent, then during path compression, each time we replace the node's parent with the root, we must add the parent-to-root distance to the weight stored at the node. Similarly, when merging the sets of two nodes, we need to compute the weight of the new edge between the two roots.

??? example "Template problem [Library Checker - Unionfind with Potential](https://judge.yosupo.jp/problem/unionfind_with_potential) reference implementation"
    === "C++"
        ```cpp
        --8<-- "docs/ds/code/dsu/dsu_5.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/ds/code/dsu/dsu_5.py"
        ```

## Example problems

In contests, problems that test DSU directly usually require designing a special structure for the problem.

???+ example "[UVa11987 Almost Union-Find](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3138)"
    Implement a DSU-like data structure that supports the following operations:
    
    1.  Merge the sets that two elements belong to.
    2.  Move a single element to the set containing another element.
    3.  Query the size and the element sum of the set containing an element.

??? note "Solution"
    In this problem, operations 1 and 3 are easy; the hard part is operation 2. Suppose we want to move element $x$ into the set containing element $y$. In a plain DSU, we can't just set the parent of $x$ to the root of $y$'s set, because that would also move every element in $x$'s subtree. The fix is to make sure element $x$ has no children. To do this, when building the DSU we create a virtual node $\tilde x$ for each element $x$ and point the parent of $x$ to its virtual node $\tilde x$. Then, when merging two sets, we always link one root to another, and all roots are virtual nodes, so only virtual nodes have children, and no node that actually stores an element has any children. Now moving an element is much easier.

??? note "Reference implementation"
    === "C++"
        ```cpp
        --8<-- "docs/ds/code/dsu/dsu_1.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/ds/code/dsu/dsu_1.py"
        ```

???+ example "[Luogu P2024 'NOI2011' Food Chain](https://www.luogu.com.cn/problem/P2024)"
    The animal kingdom has three kinds of animals, $A,B,C$, whose food chain forms an interesting cycle: $A$ eats $B$, $B$ eats $C$, and $C$ eats $A$.
    
    There are $N$ animals, numbered $1 \sim N$. Each animal is one of $A,B,C$, but we don't know which.
    
    Someone describes the food chain relations among these $N$ animals using two kinds of statements:
    
    -   The first kind is `1 X Y`, meaning $X$ and $Y$ are the same kind.
    -   The second kind is `2 X Y`, meaning $X$ eats $Y$.
    
    This person says $K$ statements about the $N$ animals, one after another, using the two kinds above. Some of the $K$ statements are true and some are false. A statement is false if it meets any one of the following three conditions; otherwise it is true.
    
    -   It conflicts with some earlier true statement;
    -   $X$ or $Y$ in it is greater than $N$;
    -   It says $X$ eats $X$.
    
    Your task is to output the total number of false statements, given $N$ and the $K$ statements.

??? note "Solution 1"
    Use a weighted DSU to maintain the food chain information. If $x$ and $y$ are the same kind, then $x\equiv y\pmod 3$; if $x$ eats $y$, then $x - y \equiv 1 \pmod 3$. This turns the problem into the template problem above.
    
    Specifically, for each statement, apart from the obviously false ones with $x>n$ or $y>n$, we check whether $x$ and $y$ are already connected. If they are, compute their distance modulo 3 and compare it with what the statement claims; otherwise, connect them according to the statement. Apart from the obvious cases, a statement is false if and only if the two nodes it mentions are already connected and their distance contradicts the statement.

??? note "Reference implementation 1"
    === "C++"
        ```cpp
        --8<-- "docs/ds/code/dsu/dsu_6.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/ds/code/dsu/dsu_6.py"
        ```

??? note "Solution 2"
    Split each animal $x$ into three states. In the implementation, we can simply treat different states as different elements:
    
    -   States in the same set as $x$ are the same species as $x$;
    -   States in the same set as $x+n$ can be eaten by $x$;
    -   States in the same set as $x+2n$ can eat $x$.
    
    So for a statement:
    
    -   `1 x y` is false if and only if:
    
        1.  $x>N$ or $y>N$;
        2.  $y$ is in the same set as either $x+n$ or $x+2n$.
    -   `2 x y` is false if and only if:
    
        1.  $x>N$ or $y>N$;
        2.  $y$ is in the same set as either $x$ or $x+2n$.
    -   If the statement is true, merge the corresponding states.

??? note "Reference implementation 2"
    === "C++"
        ```cpp
        --8<-- "docs/ds/code/dsu/dsu_2.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/ds/code/dsu/dsu_2.py"
        ```

???+ example "[ABC396E Min of Restricted Sum](https://atcoder.jp/contests/abc396/tasks/abc396_e)"
    You are given integers $N, M$ and integer sequences of length $M$: $X=(X_1,X_2,\ldots,X_M)$, $Y=(Y_1,Y_2,\ldots,Y_M)$, $Z=(Z_1,Z_2,\ldots,Z_M)$. All elements of $X$ and $Y$ are guaranteed to be between $1$ and $N$.
    
    A sequence of non-negative integers $A=(A_1,A_2,\ldots,A_N)$ of length $N$ is called a **good integer sequence** if and only if it satisfies the following condition:
    
    -   For every integer $i$ with $1 \leq i \leq M$, $A_{X_i} \oplus A_{Y_i} = Z_i$, where $\oplus$ denotes XOR.
    
    Determine whether such a good integer sequence exists. If it does, find the good integer sequence with the smallest element sum $\displaystyle \sum_{i=1}^N A_i$ and output it.

??? note "Solution"
    XOR is just a "same" or "different" relation on each individual bit. So if we split every $A_i$ into its bits, the XOR relations can be maintained with a weighted DSU (or a DSU with categories). The elements in one connected component always correspond to the same bit position of different numbers in $A$. When computing the answer, the elements of one component usually split into two groups that must take different values. We just assign $0$ to the larger group and $1$ to the other, which guarantees the smallest total.

??? note "Reference implementation"
    === "C++"
        ```cpp
        --8<-- "docs/ds/code/dsu/dsu_3.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/ds/code/dsu/dsu_3.py"
        ```

## Exercises

-   ["NOI2015" Automatic Program Analysis](https://uoj.ac/problem/127)
-   ["JSOI2008" Star Wars](https://www.luogu.com.cn/problem/P1197)
-   ["NOIP2023" Three-Valued Logic](https://www.luogu.com.cn/problem/P9869)
-   ["NOI2002" Legend of Galactic Heroes](https://www.luogu.com.cn/problem/P1196)

## Other applications

Kruskal's algorithm in [minimum spanning tree](../graph/mst.md) and Tarjan's algorithm in [lowest common ancestor](../graph/lca.md) are both built on DSU.

For related topics, see [DSU applications](../topic/dsu-app.md).

## References and further reading

1.  [Zhihu answer: Is there really a binary path compression optimization for DSU?](https://www.zhihu.com/question/28410263/answer/40966441)
2.  Gabow, H. N., & Tarjan, R. E. (1985). A Linear-Time Algorithm for a Special Case of Disjoint Set Union. JOURNAL OF COMPUTER AND SYSTEM SCIENCES, 30, 209-221.[PDF](https://dl.acm.org/doi/pdf/10.1145/800061.808753)
3.  [CSDN: Extended-domain DSU & weighted DSU](https://blog.csdn.net/qqqqqwerttwtwe/article/details/145440100)

[^tarjan1984worst]: Tarjan, R. E., & Van Leeuwen, J. (1984). Worst-case analysis of set union algorithms. Journal of the ACM (JACM), 31(2), 245-281.[ResearchGate PDF](https://www.researchgate.net/profile/Jan_Van_Leeuwen2/publication/220430653_Worst-case_Analysis_of_Set_Union_Algorithms/links/0a85e53cd28bfdf5eb000000/Worst-case-Analysis-of-Set-Union-Algorithms.pdf)

[^yao1985expected]: Yao, A. C. (1985). On the expected performance of path compression algorithms.[SIAM Journal on Computing, 14(1), 129-133.](https://epubs.siam.org/doi/abs/10.1137/0214010?journalCode=smjcat)
