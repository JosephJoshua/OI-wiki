## Introduction

The sweep line is usually used on figures. It works just as its name suggests: a line sweeps across the whole figure. It is generally used for problems such as the area or perimeter of figures, and 2D point counting.

## Area of a union of rectangles in 2D

In a 2D coordinate system, you are given the bottom-left and top-right corners of several rectangles. Find the area of the figure formed by all the rectangles.

### How it works

From the picture, the total area can be found directly by brute force. But what if the input is large? This is where the **sweep line** algorithm comes in.

Now suppose we have a line that sweeps from bottom to top:

![](./images/scanning.svg)

As the figure shows, the whole shape is cut into small rectangles of different colors. The height of each small rectangle is the distance swept, while the horizontal width keeps changing.

Mark the bottom and top edges of each rectangle: a bottom edge gets mark 1 and a top edge gets mark -1. Whenever the line meets a horizontal edge, add the edge's mark to the weight of that edge (its projection interval on the horizontal axis).

???+ note "Note"
    This is similar to walking through a bracket sequence: an opening bracket adds 1 and a closing bracket subtracts 1. The "weight" corresponds to the depth at the current position, and whether the "weight" is greater than 0 corresponds to whether we are currently inside brackets, that is, whether this interval counts toward the width of the small rectangle.

The width of the small rectangle(s) (there may be more than one) is the total length of the intervals on the axis whose weight is greater than 0.

### Implementation

Use a segment tree to maintain the width of the rectangles, that is, the points on the axis covered more than 0 times. The operations we need are:

-   Add 1 to or subtract 1 from the weight of a range.
-   Find the "total length" of the intervals on the whole axis whose weight is greater than 0.

If you try to do this directly with an ordinary segment tree template, you may run into trouble. Specifically, during a range add, even when the range being modified exactly matches the range a node manages, we still cannot tell in constant time how the coverage counts change. This is because we cannot directly know how much of the managed range will go from 1 to 0 (or from 0 to 1).

This problem only needs plain divide and conquer: for each node's range, maintain two values, "the number of times the whole range is fully covered `v[]`" (like a lazy tag that never needs pushing down) and "the covered length `w[]`".

[Coordinate compression](../misc/discrete.md) is needed.

??? note "[Luogu P5490 [Template] Sweep Line & Area of Union of Rectangles](https://www.luogu.com.cn/problem/P5490) reference code"
    ```cpp
    --8<-- "docs/geometry/code/scanning/scanning_1.cpp"
    ```

??? note "[POJ 1151 Atlantis](http://poj.org/problem?id=1151) reference code"
    ```cpp
    --8<-- "docs/geometry/code/scanning/scanning_2.cpp"
    ```

### Exercises

-   [POJ1177 Picture](http://poj.org/problem?id=1177)
-   [POJ3832 Posters](http://poj.org/problem?id=3832)
-   [Luogu P1856 \[IOI1998\] \[USACO5.5\] Picture (rectangle perimeter)](https://www.luogu.com.cn/problem/P1856)
    -   The contribution of horizontal edges is the change in covered length.
    -   Computing once in each direction avoids having to handle vertical edges.
    -   When sorting operations, take care with the case where edges of two rectangles coincide.
    -   The constraints allow skipping the segment tree and simulating directly in quadratic time.

## B-dimensional orthogonal ranges

A B-dimensional orthogonal range is the set of points in a B-dimensional Cartesian coordinate system whose $i$-th coordinate lies in an integer range $[l_i,r_i]$ for every $i$.

In general, a 1D orthogonal range is called an interval, a 2D one a rectangle, and a 3D one a cuboid (the common "2D point counting" problem is about 2D orthogonal ranges).

For a static 2D problem, we can sweep one dimension with a sweep line and maintain the other dimension with a data structure.
As the sweep line moves from left to right, it produces some updates and queries on the dimension maintained by the data structure.
If the queried information can be split by differencing, use differencing directly; otherwise use divide and conquer. Differencing is usually maintained with a Fenwick tree or a segment tree, but since the Fenwick tree is easy to write and has a small constant factor, most people choose it. The divide and conquer is usually CDQ divide and conquer (which we don't cover here).

Another, easier way to look at the problem is from the point of view of a sequence instead of the 2D plane. Seen this way, the sweep line enumerates the right endpoint $r=1\cdots n$ and maintains a data structure that answers: for the current $r$ and a given $l$, what is the answer for $l$ to $r$? That is, the sweep line goes over the right endpoints of the queries, and the data structure keeps the answers for all left endpoints; in other words, we iterate over one dimension and the data structure maintains the other.

The complexity is usually $O((n+m)\log n)$.

## 2D point counting

Given a sequence of length $n$ and $m$ queries, each query asks how many elements in the range $[l,r]$ have values in $[x,y]$.

This problem is called 2D point counting. It is equivalent to counting the points inside a rectangle in the 2D plane. Here we explain the simplest way to handle it: sweep line + Fenwick tree.

Clearly this is a static 2D problem. With a sweep line, we can turn a static 2D problem into a dynamic 1D problem, and a dynamic 1D problem can be handled with a data structure over a sequence; here we can use a Fenwick tree.

First compress all the queries, and use a Fenwick tree indexed by value. For each query with $l$ and $r$, when the enumeration reaches $l-1$, count the numbers currently in $[x,y]$, call it $a$; keep enumerating, and when it reaches $r$, count the numbers currently in $[x,y]$, call it $b$. Then $b-a$ is the answer to the query.

### Example problems

???+ note "[Luogu P2163 \[SHOI2007\] The Gardener's Trouble](https://www.luogu.com.cn/problem/P2163)"
    First compress the coordinates. Let $ans_{x, y}$ be the number of points in the rectangle with bottom-left corner $(0, 0)$ and top-right corner $(x, y)$. Then the answer to a query can be split by differencing as $ans_{c, d} - ans_{a - 1, d} - ans_{c, b - 1} + ans_{a - 1, b - 1}$.
    
    ??? note "Code"
        ```cpp
        --8<-- "docs/geometry/code/scanning/scanning_3.cpp"
        ```

???+ note "[Luogu P1908 Inversions](https://www.luogu.com.cn/problem/P1908)"
    That's right, inversions can also be counted with the sweep line idea. Turn counting inversions into: enumerate each position $i$ from back to front, and count the points in the range $[i+1,n]$ whose values are in $[0,a_i]$. The values go up to $10^9$, so clearly we compress them first. We traverse the array from back to front; each time we reach a number, we update the Fenwick tree (or segment tree), then count how many numbers so far are smaller than the current one. Since we traverse from back to front, the count of smaller numbers is the number of inversions formed with this number. A Fenwick tree or segment tree with point updates and range queries does the job.
    
    ??? note "Code"
        ```cpp
        --8<-- "docs/geometry/code/scanning/scanning_4.cpp"
        ```

???+ note "[Luogu P1972 \[SDOI2009\] HH's Necklace](https://www.luogu.com.cn/problem/P1972)"
    Short statement: given a sequence, answer many queries asking how many distinct values are in the range $[l,r]$.
    
    For this kind of problem, we can derive some properties and then use a sweep line over all right endpoints, with a data structure maintaining the answer for each left endpoint. We can also move the problem to the 2D plane, where it becomes a rectangle query.
    
    In this problem, let $pre_i$ be the position where $a_i$ last appeared before $i$; if $a_i$ has not appeared before, $pre_i = 0$. By the statement, a value that appears several times in the range only contributes once. Let's say each value contributes at its first occurrence in the range. Then the total contribution is the number of positions with $pre_x \le l - 1$, which is easy to prove by contradiction.
    
    Now the problem is: given a sequence $pre$, answer many queries asking how many $pre_i \le l - 1$ there are in the range $[l,r]$.
    
    We can treat each $pre_i$ as a point in the 2D plane, with $i$ as the x-coordinate and $pre_i$ as the y-coordinate. The problem becomes 2D point counting: each query asks how many points lie in the rectangle with bottom-left corner $(l,0)$ and top-right corner $(r,l - 1)$.
    
    Note that the query can be split by differencing: the count in the rectangle from $(0,0)$ to $(r,l - 1)$ minus the count in the rectangle from $(0,0)$ to $(l - 1,l - 1)$. This makes it easy to apply the sweep line idea.
    
    Each operation costs $O(\log n)$. There are $n$ add-point operations and $2m$ query operations, so the total time complexity is $O((n + m) \log n)$.
    
    ??? note "Code"
        ```cpp
        --8<-- "docs/geometry/code/scanning/scanning_5.cpp"
        ```

### Exercises

-   [Luogu P8593 KDOI-02 A Bomb Throw](https://www.luogu.com.cn/problem/P8593) An application of inversions.
-   [AcWing 4709. Triples](https://www.acwing.com/problem/content/4712/) A weaker version of the previous problem, also an application of inversions.
-   [Luogu P8773 \[Lanqiao Cup 2022 Provincial A\] Choosing Numbers for XOR](https://www.luogu.com.cn/problem/P8773) A modified version of HH's Necklace.
-   [Luogu P8844 \[Chuanzhi Cup #4 Preliminary\] Xiaoka and the Fallen Leaves](https://www.luogu.com.cn/problem/P8844) Turn a tree problem into a sequence problem, then do 2D point counting.

In short, the main idea of 2D point counting is to maintain one dimension with a data structure and enumerate the other.

## References

-   [cnblogs/Yang1208: Sweep line explained, with a dynamically allocated segment tree](https://www.cnblogs.com/yangsongyi/p/8378629.html)
-   [csdn/riba2534: POJ1151 Atlantis editorial](https://blog.csdn.net/riba2534/article/details/76851233)
-   [csdn/Daodaogou0102: POJ1151 Atlantis editorial](https://blog.csdn.net/winddreams/article/details/38495093)
-   [A brief look at the sweep line](https://www.luogu.com.cn/article/f8q5bmnz)
