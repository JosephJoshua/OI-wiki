The Steiner tree problem is a combinatorial optimization problem. Like the minimum spanning tree, it is a kind of shortest network problem. A minimum spanning tree looks for the shortest network that connects all points using only the given points and edges. A minimum Steiner tree allows extra points beyond the given ones, so that the resulting shortest network costs as little as possible.

## Introduction to the problem

In the early 19th century, Steiner, a famous geometer at the University of Berlin, studied a very simple but enlightening problem: connect three villages with roads of minimum total length. Mathematically, given three points $A$, $B$, $C$ in the plane, find a fourth point $P$ in the plane such that the sum $a+b+c$ is as small as possible, where $a$, $b$, $c$ are the distances from $P$ to $A$, $B$, $C$.

The answer is: if every interior angle of triangle $\textit{ABC}$ is less than $120^{\circ}$, then $P$ is the point at which the sides $\textit{AB}$, $\textit{BC}$, $\textit{AC}$ each subtend an angle of $120^{\circ}$. If one angle of triangle $\textit{ABC}$, say angle $C$, is at least $120^{\circ}$, then $P$ coincides with vertex $C$.

### Generalizations

1.  In Steiner's problem, three fixed points $A,B,C$ are given. It is natural to generalize this to $n$ given points $A_1,A_2,\dots,A_n$: find a point $P$ in the plane that minimizes the sum of distances $a_1+a_2+\dots+a_n$, where $a_i$ is the distance $PA_i$.

2.  To account for other factors related to the points, weights are added. Other factors of the $n$ points can be converted into a weight for each point. Find a point $P$ in the plane that minimizes the weighted sum of distances $a_1\cdot w_1+a_2\cdot w_2+\dots+a_n\cdot w_n$, where $w_i$ is the weight of each point.

3.  R. Courant and H. Robbins pointed out that the first generalization is superficial. To get a truly valuable generalization of Steiner's problem, we must give up looking for a single point $P$ and look instead for a "road network" with the shortest total length. Mathematically: given $n$ points $A_1,A_2,\cdots,A_n$, find a system of straight line segments with the shortest total length that connects these $n$ points, such that any two points can be joined by a polyline made of segments in the system. They called this new problem the **Steiner tree problem**. For $n$ given points, there are at most $n-2$ junction points (Steiner points). At most three edges pass through each Steiner point. If there are three edges, every two of them meet at an angle of $120^{\circ}$. If there are two edges, this Steiner point must be one of the given points, and the angle between the two edges must be at least $120^{\circ}$.

Shortest networks connecting more than three points

![steiner-tree1](./images/steiner-tree-1.svg)

In the first case, the solution consists of five segments with two Steiner points (red $s_1,s_2$), where three segments meet at angles of $120^{\circ}$ to each other. The solution in the second case has three Steiner points. In the third case, one or more Steiner points may degenerate, that is, be replaced by one or more of the given points.

Now let us state the Steiner tree problem in graph-theoretic form.

![steiner-tree2](./images/steiner-tree-2.svg)

For form one, let the key points be $\{1,2,3,4\}$. Connecting these four key points directly gives a minimum total edge weight of 12, which is clearly not optimal. If we also use node 5, the minimum total edge weight becomes 9, a better answer.

For form two, let the key points be $\{1,2,3,4\}$. Some of these key points are not even directly connected by an edge, so we must use junction points (Steiner points). Including node 5 gives a minimum total edge weight of 9.

We can also see that in both graphs, the Steiner points for nodes 1 and 4 have degenerated and are replaced by node 1 or node 4.

## Example problems

First, let us get familiar with the minimum Steiner tree problem through a template problem: [\[Template\] Minimum Steiner Tree](https://www.luogu.com.cn/problem/P6192).

The statement is clear: given $n$ vertices of a connected graph $G$ and $k$ key vertices, connect the $k$ key vertices so that the total weight of all edges of the resulting tree is as small as possible.

From the discussion above, we know that connecting the $k$ key vertices directly does not always give the smallest total weight, and the $k$ key vertices may not even be directly (adjacently) connected. So we should use the remaining $n-k$ vertices.

We solve it with bitmask DP. Let $f(i,S)$ be the minimum total edge weight of a tree rooted at $i$ that contains all vertices in set $S$.

State transitions:

-   First, transition by merging connected subsets: $f(i,S)\leftarrow \min(f(i,S),f(i,T)+f(i,S-T))$.

-   Then, for the current subset, relax edges: $f(i,S)\leftarrow \min(f(i,S),f(j,S)+w(j,i))$. In the code below, `tree[tot]` stores information about two connected vertices $i,j$.

??? note "Reference implementation"
    ```cpp
    --8<-- "docs/graph/code/steiner-tree/steiner-tree_1.cpp"
    ```

Another classic example problem is [\[WC2008\] Sightseeing Plan](https://www.luogu.com.cn/problem/P4294).

This problem asks for the Steiner tree with the minimum total vertex weight. Let $f(i,S)$ be the minimum total vertex weight of a tree rooted at $i$ that contains all vertices in set $S$, and let $a_i$ be the vertex weight.

State transitions:

-   $f(i,S)\leftarrow \min(f(i,S),f(i,T)+f(i,S-T)-a_i)$. When merging here, the same vertex weight $a_i$ is added twice, so we subtract it once.

-   $f(i,S)\leftarrow \min(f(i,S),f(j,S)+w(j,i))$.

The transitions are similar to the template problem above. The tricky part is outputting the answer: we also need to record the path during the DP.

Use `pre[i][s]` to record the vertex and set information from which the state with root $i$ and connected set $s$ was reached. After the DP, start from `pre[root][S]`, find the vertices connected to the vertices in the set and split the set $S$ step by step, using the ans array to record the vertices that are used. The search ends when the set has been fully split.

??? note "Reference implementation"
    ```cpp
    --8<-- "docs/graph/code/steiner-tree/steiner-tree_2.cpp"
    ```

## Exercises

-   [\[Template\] Minimum Steiner Tree](https://www.luogu.com.cn/problem/P6192)
-   [\[WC2008\] Sightseeing Plan](https://www.luogu.com.cn/problem/P4294)
-   [\[JLOI2015\] Pipe Connection](https://loj.ac/problem/2110)
-   [\[APIO2013\] Robots](https://www.luogu.com.cn/problem/P3638)
