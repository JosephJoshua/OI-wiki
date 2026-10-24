## 2D convex hull

### Definition

#### Convex polygon

A convex polygon is a **simple polygon** whose interior angles all lie in the range $[0,\pi]$.

#### Convex hull

The smallest convex polygon in the plane that contains all the given points is called the convex hull.

Formally: for a given set $X$, the intersection $S$ of all convex sets that contain $X$ is called the **convex hull** of $X$.

In practice, you can picture it as the shape a rubber band takes when stretched around all the given points.

The convex hull encloses all the given points with the smallest perimeter. If a concave polygon encloses all the points, its perimeter is certainly not the smallest, as shown below. By the triangle inequality, a convex polygon is always optimal in terms of perimeter.

![](./images/ch.png)

### Andrew's algorithm for the convex hull

The common methods are the Graham scan and Andrew's algorithm. Here we mainly introduce Andrew's algorithm.

#### Properties

The time complexity of this algorithm is $O(n\log n)$, where $n$ is the number of points. The bottleneck is sorting all points by their coordinates with two keys.

#### How it works

First sort all points with the x-coordinate as the first key and the y-coordinate as the second key.

Clearly, the smallest and largest elements after sorting must be on the convex hull. Also, since the hull is a convex polygon, if we walk counterclockwise from a point, the path always "turns left". As soon as it turns right, that part is not on the convex hull. So we can maintain the lower and upper hulls with a monotonic stack.

Looking from left to right, the lower and upper hulls turn in different directions. To make the monotonic stack work, we first **enumerate in ascending order** to get the lower hull, then **in descending order** to get the upper hull.

When building a hull, if the point about to be pushed ($P$) and the two points at the top of the stack ($S_1,S_2$, where $S_1$ is the top) turn to the right, that is, the cross product is less than $0$: $\overrightarrow{S_2S_1}\times \overrightarrow{S_1P}<0$, then pop the top of the stack and go back to check again, until $\overrightarrow{S_2S_1}\times \overrightarrow{S_1P}\ge 0$ or only one element is left in the stack.

Usually we don't need to keep the points that lie on the edges of the convex hull. So in the condition $\overrightarrow{S_2S_1}\times \overrightarrow{S_1P}<0$ above, the "$<$" can be changed to $\le$ as needed, and the second condition should then become $>$.

![Andrew](./images/andrew.svg)

#### Implementation

???+ note "Implementation"
    === "C++"
        ```cpp
        // stk[] is an int array that stores indices
        // p[] stores the vectors or points
        tp = 0;                       // initialize the stack
        std::sort(p + 1, p + 1 + n);  // sort the points
        stk[++tp] = 1;
        // push the first element without updating used, so that 1 also updates the monotonic stack when the hull is closed at the end
        for (int i = 2; i <= n; ++i) {
          while (tp >= 2  // on the next line, operator * is overloaded as the cross product
                 && (p[stk[tp]] - p[stk[tp - 1]]) * (p[i] - p[stk[tp]]) <= 0)
            used[stk[tp--]] = 0;
          used[i] = 1;  // used means the point is on the hull
          stk[++tp] = i;
        }
        int tmp = tp;  // tmp is the size of the lower hull
        for (int i = n - 1; i > 0; --i)
          if (!used[i]) {
            // ↓ building the upper hull must not affect the lower hull
            while (tp > tmp && (p[stk[tp]] - p[stk[tp - 1]]) * (p[i] - p[stk[tp]]) <= 0)
              used[stk[tp--]] = 0;
            used[i] = 1;
            stk[++tp] = i;
          }
        for (int i = 1; i <= tp; ++i)  // copy into a new array
          h[i] = p[stk[i]];
        int ans = tp - 1;
        ```
    
    === "Python"
        ```python
        stk = []  # an int array that stores indices
        p = []  # stores the vectors or points
        tp = 0  # initialize the stack
        p.sort()  # sort the points
        tp = tp + 1
        stk[tp] = 1
        # push the first element without updating used, so that 1 also updates the monotonic stack when the hull is closed at the end
        for i in range(2, n + 1):
            while tp >= 2 and (p[stk[tp]] - p[stk[tp - 1]]) * (p[i] - p[stk[tp]]) <= 0:
                # on the next line, operator * is overloaded as the cross product
                used[stk[tp]] = 0
                tp = tp - 1
            used[i] = 1  # used means the point is on the hull
            tp = tp + 1
            stk[tp] = i
        tmp = tp  # tmp is the size of the lower hull
        for i in range(n - 1, 0, -1):
            if used[i] == False:
                #      ↓ building the upper hull must not affect the lower hull
                while tp > tmp and (p[stk[tp]] - p[stk[tp - 1]]) * (p[i] - p[stk[tp]]) <= 0:
                    used[stk[tp]] = 0
                    tp = tp - 1
                used[i] = 1
                tp = tp + 1
                stk[tp] = i
        for i in range(1, tp + 1):
            h[i] = p[stk[i]]
        ans = tp - 1
        ```

With the code above, the convex hull ends up with $\textit{ans}$ points (point $1$ is stored one extra time, so the array $h$ holds $\textit{ans}+1$ elements), in counterclockwise order. The perimeter is

$$
\sum_{i=1}^{\textit{ans}}\left|\overrightarrow{h_ih_{i+1}}\right|
$$

### Graham scan

#### Properties

Like Andrew's algorithm, the Graham scan runs in $O(n\log n)$ time, and the bottleneck is again sorting all the points.

#### How it works

First find the point $P$ with the smallest y-coordinate. By the definition of the convex hull, this point must be on the hull. Then sort all points by their polar angle relative to point P.

![](./images/ch1.svg)

As in Andrew's algorithm, if we start from point $P$ and walk counterclockwise along the convex hull, every point we pass must be a "left turn". Formally, for any three consecutive points $P_1, P_2, P_3$ in counterclockwise order on the hull, we must have $\overrightarrow{P_1 P_2} \times \overrightarrow{P_2 P_3} \ge 0$.

Create a stack to store the hull. Push $P$ first, then try to add each point in polar angle order. If the point being pushed, $P_0$, and the two points at the top of the stack, $P_1, P_2$ (where $P_1$ is the top), make a "right turn", pop $P_1$ from the top. Repeat this until the new point and the top two points satisfy the condition, or only one element is left in the stack, then push $P_0$.

![](./images/ch2.svg)

![](./images/ch3.svg)

???+ note "Implementation"
    ```cpp
    struct Point {
      double x, y, ang;
    
      Point operator-(const Point& p) const { return {x - p.x, y - p.y, 0}; }
    } p[MAXN];
    
    double dis(Point p1, Point p2) {
      return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }
    
    bool cmp(Point p1, Point p2) {
      if (p1.ang == p2.ang) {
        return dis(p1, p[1]) < dis(p2, p[1]);
      }
      return p1.ang < p2.ang;
    }
    
    double cross(Point p1, Point p2) { return p1.x * p2.y - p1.y * p2.x; }
    
    int main() {
      for (int i = 2; i <= n; ++i) {
        if (p[i].y < p[1].y || (p[i].y == p[1].y && p[i].x < p[1].x)) {
          std::swap(p[1], p[i]);
        }
      }
      for (int i = 2; i <= n; ++i) {
        p[i].ang = atan2(p[i].y - p[1].y, p[i].x - p[1].x);
      }
      std::sort(p + 2, p + n + 1, cmp);
      sta[++top] = 1;
      for (int i = 2; i <= n; ++i) {
        while (top >= 2 &&
               cross(p[sta[top]] - p[sta[top - 1]], p[i] - p[sta[top]]) < 0) {
          top--;
        }
        sta[++top] = i;
      }
      return 0;
    }
    ```

## Minkowski sum

### Definition

The Minkowski sum $P+Q$ of point sets $P$ and $Q$ is defined as $P+Q=\{a+b|a\in P,b\in Q\}$. In other words, treat each point of $Q$ as a vector and translate each point of $P$ by these vectors; the set of all resulting points is $P+Q$. Here we only discuss the Minkowski sum of **convex hulls**.

For example, take the point sets $P=\{(0,0),(-3,3),(2,1)\}$ and $Q=\{(0,0),(-1,3),(1,4),(2,2)\}$:

![](./images/convex-hull1.svg)

Translate $P$ by each vector of $Q$:

![](./images/convex-hull2.svg)

It is easy to see that the new figure is also a **convex hull**:

![](./images/convex-hull3.svg)

### Properties

1.  If point sets $P$ and $Q$ are convex, their Minkowski sum $P+Q$ is also convex.

    ??? note "Proof"
        Let $e,f\in P+Q$. Then there are $a,b \in P$ and $c,d\in Q$ with $e=a+c,f=b+d$, and for any $t\in[0,1]$:
        
        $$
        \begin{aligned}
        te + (1-t)f &= t(a+c)+(1-t)(b+d)\\
        &=(ta+(1-t)b)+(tc+(1-t)d)\\
        &\in P+Q.
        \end{aligned}
        $$
        
        This completes the proof.
2.  If point sets $P$ and $Q$ are convex, the edges of their Minkowski sum $P+Q$ are the edges of $P$ and $Q$ sorted by polar angle and joined together.

    ??? note "Proof"
        Assume without loss of generality that no edge of $P$ has the same slope as an edge of $Q$. Rotate the coordinate system so that an edge $XY$ of $P$ is parallel to the $x$-axis and is the lowest part of $P$.
        
        Let $U$ be the lowest point of $Q$ at this moment, and let $A$ be the **lowest**, **leftmost** point of $P+Q$.
        
        We know $\vec{A} = \vec{X} + \vec{U}$, so $A$ must be on the boundary of $P+Q$.
        
        Similarly, the **lowest**, **rightmost** point $B$ of $P+Q$ satisfies $\vec{B} = \vec{Y} + \vec{U}$, and it must also be on the boundary of $P+Q$.
        
        Therefore $\vec{AB} = \vec{XY} + \vec{U}$.
        
        If we keep rotating in order, the results form every edge of $P+Q$ one after another.
        
        This completes the proof.

### Implementation

By Property 2, sort the edges of convex sets $P,Q$ by polar angle to get the order in which they appear on $P+Q$. Take $P_1+Q_1$ as the starting point of $P+Q$, then place the edges one by one in a **merge**-like way.

Time complexity: $O(n+m)$

???+ note "Implementation"
    ```cpp
    template <class T>
    struct Point {
      T x, y;
    
      Point(T x = 0, T y = 0) : x(x), y(y) {}
    
      friend Point operator+(const Point &a, const Point &b) {
        return {a.x + b.x, a.y + b.y};
      }
    
      friend Point operator-(const Point &a, const Point &b) {
        return {a.x - b.x, a.y - b.y};
      }
    
      // dot product
      friend T operator*(const Point &a, const Point &b) {
        return a.x * b.x + a.y * b.y;
      }
    
      // cross product
      friend T operator^(const Point &a, const Point &b) {
        return a.x * b.y - a.y * b.x;
      }
    };
    
    template <class T>
    vector<Point<T>> minkowski_sum(vector<Point<T>> a, vector<Point<T>> b) {
      vector<Point<T>> c{a[0] + b[0]};
      for (usz i = 0; i + 1 < a.size(); ++i) a[i] = a[i + 1] - a[i];
      for (usz i = 0; i + 1 < b.size(); ++i) b[i] = b[i + 1] - b[i];
      a.pop_back(), b.pop_back();
      c.resize(a.size() + b.size() + 1);
      merge(a.begin(), a.end(), b.begin(), b.end(), c.begin() + 1,
            [](const Point<T> &a, const Point<T> &b) { return (a ^ b) < 0; });
      for (usz i = 1; i < c.size(); ++i) c[i] = c[i] + c[i - 1];
      return c;
    }
    ```

### Example problem

???+ note "[Example problem: \[JSOI2018\] War](https://loj.ac/p/2549)"
    There are two convex hulls $P,Q$. $Q$ is translated $q$ times; after each move, determine whether they share a point. $1\le n,m\le 10^5,1\le q\le 10^5$.

??? note "Implementation"
    ```cpp
    --8<-- "docs/geometry/code/convex-hull/convex-hull_1.cpp"
    ```

## 3D convex hull

### Background

> Circle inversion: with center of inversion $O$ and radius of inversion $R$, if a line through $O$ passes through $P$ and $P'$, and $OP\times OP'=R^{2}$, then $P$ and $P'$ are called inverses of each other with respect to $O$.

### How it works

The hull is built as follows:

-   First apply a tiny random perturbation to the points, so that no four points are coplanar.
-   Given a known convex hull, add a new point $P$. Treat $P$ as a point light source shining rays at the hull. The faces lit by the light and the faces not lit must be separated by some edges.
-   Delete the lit faces, and add the new faces formed by $P$ and those separating edges.
    Just repeat this process. By [Pick's theorem](./pick.md), Euler's formula (for a convex polyhedron, the number of vertices $V$, edges $E$ and faces $F$ satisfy $V−E+F=2$) and circle inversion, the complexity is $O(n^2)$.[^3d-v]

### Template problem

[P4724 [Template] 3D Convex Hull](https://www.luogu.com.cn/problem/P4724)

Repeating the process above gives the answer.

???+ note "Implementation"
    ```cpp
    --8<-- "docs/geometry/code/3d/3d_1.cpp"
    ```

## Exercises

-   [UVa11626 Convex Hull](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=78&page=show_problem&problem=2673)

-   [USACO5.1 Fencing the Cows](https://www.luogu.com.cn/problem/P2742)

-   [POJ1873 The Fortified Forest](http://poj.org/problem?id=1873)

-   [POJ1113 Wall](http://poj.org/problem?id=1113)

-   [USACO22JAN Multiple Choice Test P](https://www.luogu.com.cn/problem/P8101)

-   [SHOI2012 Credit Card Convex Hull](https://www.luogu.com.cn/problem/P3829)

## References and notes

[^3d-v]: [Notes on learning the 3D convex hull](https://www.cnblogs.com/xzyxzy/p/10225804.html)
