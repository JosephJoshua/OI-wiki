This page mainly introduces rotating calipers.

## Introduction

The rotating calipers algorithm builds on convex hull algorithms. It enumerates the edges of the convex hull while maintaining the other points it needs, and can solve problems related to convex hull properties, such as the diameter of a convex hull or the minimum-area enclosing rectangle, in linear time.

???+ note "About the Chinese name"
    The most common Chinese name of this algorithm is "xuanzhuan qiake", literally "rotating and clamping the shell". You can read it like this: for the edge we are enumerating, we can draw a line through each maintained point that is either parallel or perpendicular to that edge. To make sure the current edge is handled optimally, our task is to make these lines clamp the convex hull exactly. The edges are usually enumerated in order of rotating in one direction, so the whole process is "rotating" while "clamping".
    
    The English name "rotating calipers" refers to calipers, the measuring tool. The paper that first introduced the term[^ref1] meant: clamp the convex hull with an adjustable "caliper", then "rotate" that "caliper" around the hull.

## Diameter of a convex hull

???+ note "Example problem 1: [Luogu P1452 Beauty Contest G](https://www.luogu.com.cn/problem/P1452)"
    Given $n$ points in the plane, find the largest distance between any pair of points. ($2\leq n \leq 50000,|x|,|y| \leq 10^4$)

### How it works

First compute the convex hull of all given points with any convex hull algorithm; the pair with the largest distance must lie on the hull. Because of the shape of a convex hull, if we walk counterclockwise along its edges and find, for each edge, the point farthest from it, then as the edge turns, the corresponding farthest point also moves counterclockwise and never goes backward. This means that while enumerating the hull edges counterclockwise, we can keep track of the current farthest point and keep computing and updating the answer.

After computing the hull, the array is naturally in counterclockwise order. Remember to append the bottom-left node 1 to the end of the array beforehand, so that enumerating edges $(i,i+1)$ one by one covers every edge.

![](images/rotating-calipers1.png)

During the enumeration, for each edge, check whether point $j+1$ is farther from edge $(i,i+1)$ than $j$ is. If it is, increase $j$ by one; otherwise $j$ is the best point for this edge. To compare distances from points to the edge, compute the areas of the two triangles with the cross product (in the figure, the yellow and blue triangles with the same base) and compare them directly.

### Implementation

???+ note "Core code"
    === "C++"
        ```cpp
        int sta[N], top;  // the indices of the hull nodes are stored in a stack; the first and last indices are the same
        
        ll pf(ll x) { return x * x; }
        
        ll dis(int p, int q) { return pf(a[p].x - a[q].x) + pf(a[p].y - a[q].y); }
        
        ll sqr(int p, int q, int y) { return abs((a[q] - a[p]) * (a[y] - a[q])); }
        
        ll mx;
        
        void get_longest() {  // diameter of the convex hull
          int j = 3;
          if (top < 4) {
            mx = dis(sta[1], sta[2]);
            return;
          }
          for (int i = 1; i < top; ++i) {
            while (sqr(sta[i], sta[i + 1], sta[j]) <=
                   sqr(sta[i], sta[i + 1], sta[j % top + 1]))
              j = j % top + 1;
            mx = max(mx, max(dis(sta[i + 1], sta[j]), dis(sta[i], sta[j])));
          }
        }
        ```
    
    === "Python"
        ```python
        sta = [0] * N
        top = 0  # the indices of the hull nodes are stored in a stack; the first and last indices are the same
        
        
        def pf(x):
            return x * x
        
        
        def dis(p, q):
            return pf(a[p].x - a[q].x) + pf(a[p].y - a[q].y)
        
        
        def sqr(p, q, y):
            return abs((a[q] - a[p]) * (a[y] - a[q]))
        
        
        def get_longest():  # diameter of the convex hull
            j = 3
            if top < 4:
                mx = dis(sta[1], sta[2])
                return
            for i in range(1, top):
                while sqr(sta[i], sta[i + 1], sta[j]) <= sqr(
                    sta[i], sta[i + 1], sta[j % top + 1]
                ):
                    j = j % top + 1
                mx = max(mx, max(dis(sta[i + 1], sta[j]), dis(sta[i], sta[j])))
        ```

## Minimum-area enclosing rectangle

[Luogu P3187 Minimum Rectangle Cover](https://www.luogu.com.cn/problem/P3187)

Given the coordinates of some points, find the rectangle with the smallest area that covers all of them. ($3\leq n \leq 50000$)

### How it works

With the previous problem as groundwork, the natural idea here is again to use rotating calipers. But this time we want an area. Maintaining a single best point as in the previous problem only gives a pair of parallel lines with the smallest distance; we also need the left and right sides of the rectangle. So this time we maintain three points: one on the opposite side of the enumerated line, and two on the two lateral sides. The best opposite point is still compared by computing areas with the cross product; comparing these areas compares one side length of the rectangle. The best lateral points are compared with the dot product, since comparing dot products compares projection lengths, and the sum of the left and right projection lengths gives the other side length of the rectangle. The optimality of these two side lengths is independent, so finding the three best points determines the smallest area of a rectangle covering all points when one of its sides lies on the line of the current edge.

![](images/rotating-calipers2.png)

When computing the final answer, if the problem does not ask for all four vertices, there is a neat way to compute the area of the rectangle directly with cross and dot products. Let $S$ be twice the area of the purple region. Then the area is

$$
S\times (|\overrightarrow{AD}\cdot \overrightarrow{AB}|+|\overrightarrow{BC}\cdot \overrightarrow{BA}|-|\overrightarrow{AB}\cdot \overrightarrow{BA}|)/|\overrightarrow{AB}\cdot \overrightarrow{BA}|
$$

### Implementation

We skip the necessary convex hull computation; here is the core code for this problem:

???+ note "Core code"
    === "C++"
        ```cpp
        void get_biggest() {
          int j = 3, l = 2, r = 2;
          double t1, t2, t3, ans = 2e10;
          for (int i = 1; i < top; ++i) {
            while (sqr(sta[i], sta[i + 1], sta[j]) <=
                   sqr(sta[i], sta[i + 1], sta[j % top + 1]))
              j = j % top + 1;
            while (dot(sta[i + 1], sta[r % top + 1], sta[i]) >=
                   dot(sta[i + 1], sta[r], sta[i]))
              r = r % top + 1;
            if (i == 1) l = r;
            while (dot(sta[i + 1], sta[l % top + 1], sta[i]) <=
                   dot(sta[i + 1], sta[l], sta[i]))
              l = l % top + 1;
            t1 = sqr(sta[i], sta[i + 1], sta[j]);
            t2 = dot(sta[i + 1], sta[r], sta[i]) + dot(sta[i + 1], sta[l], sta[i]);
            t3 = dot(sta[i + 1], sta[i + 1], sta[i]);
            ans = min(ans, t1 * t2 / t3);
          }
        }
        ```
    
    === "Python"
        ```python
        def get_biggest():
            j = 3
            l = 2
            r = 2
            ans = 2e10
            for i in range(1, top):
                while sqr(sta[i], sta[i + 1], sta[j]) <= sqr(
                    sta[i], sta[i + 1], sta[j % top + 1]
                ):
                    j = j % top + 1
                while dot(sta[i + 1], sta[r % top + 1], sta[i]) >= dot(
                    sta[i + 1], sta[r], sta[i]
                ):
                    r = r % top + 1
                if i == 1:
                    l = r
                while dot(sta[i + 1], sta[l % top + 1], sta[i]) <= dot(
                    sta[i + 1], sta[l], sta[i]
                ):
                    l = l % top + 1
                t1 = sqr(sta[i], sta[i + 1], sta[j])
                t2 = dot(sta[i + 1], sta[r], sta[i]) + dot(sta[i + 1], sta[l], sta[i])
                t3 = dot(sta[i + 1], sta[i + 1], sta[i])
                ans = min(ans, t1 * t2 / t3)
        ```

## Exercises

-   [POJ 3608. Bridge Across Islands](http://poj.org/problem?id=3608)
-   [2011 ACM-ICPC World Finals, Problem K. Trash Removal](https://codeforces.com/gym/101175)
-   [ICPC WF Moscow Invitational Contest - Online Mirror, Problem F. Framing Pictures](https://codeforces.com/contest/1578/problem/F)

## References and notes

[^ref1]: Toussaint, Godfried T. (1983). "Solving geometric problems with the rotating calipers". Proc. MELECON '83, Athens. CiteSeerX 10.1.1.155.5671

-   <https://en.wikipedia.org/wiki/Rotating_calipers>

-   <http://www-cgrl.cs.mcgill.ca/~godfried/research/calipers.html>

-   Shamos, Michael (1978). "Computational Geometry" (PDF). Yale University. pp. 76–81.
