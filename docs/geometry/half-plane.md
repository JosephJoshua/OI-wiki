author: wjy-yy, Ir1d, Xeonacid

## Definition

### Half-plane

A half-plane is a line together with one side of it. A half-plane is a set of points, namely the points of a line and one side of it. If the line itself is included, it is called a closed half-plane; if not, an open half-plane.

Its equation usually has the form $Ax+By+C\ge 0$.

In computational geometry, a half-plane is represented by a vector, and within a problem we consistently take either the left side or the right side of each vector as its half-plane.

![Half-plane](./images/hpi1.svg)

### Half-plane intersection

A half-plane intersection is the intersection of several half-planes. Since half-planes are point sets, their intersection is also a point set. It encloses a region in the Cartesian plane.

This looks a lot like an ordinary linear programming problem: the half-plane intersection is the feasible region in linear programming. In most cases the half-plane intersection is bounded, and problems often ask about things like its area.

You can think of it as the intersection of the right sides of all vectors in a set, or as the solution set of the following system:

$$
\begin{cases}
A_1x+B_1y+C\ge 0\\
A_2x+B_2y+C\ge 0\\
\cdots
\end{cases}
$$

### Kernel of a polygon

If, for every point in a point set, the segment from it to any point on the polygon meets the polygon nowhere else, the point set is called the kernel of the polygon.

Treat each edge of the polygon as a vector, joined head to tail. Then the intersection of the half-planes of these vectors on the inner side of the polygon is the kernel of the polygon.

## Solution - the S&I algorithm

### Sorting by polar angle

C has a library function `atan2(double y,double x)`, which returns $\theta\in (-\pi,\pi]$ with $\theta =\arctan \frac{y}{x}$.

Call this function with each vector as its argument, and sort by the return value to get a new set of edges (vectors).

While sorting, if you meet collinear vectors (pointing the same way), keep the one closer to the feasible region. For example, if two vectors have the same polar angle and we want the left half-plane of each vector, we only need to keep the vector further to the left. To check this, take the start or end point of one vector and test whether it is on the left or the right of the other.

### Maintaining a monotonic queue

The half-plane intersection is a convex polygon, so we need to maintain a convex hull. A newly added edge can only affect the edges added first or added last (the hull is connected at this point), so we only need to delete elements at the front and back of the queue. That is why we use a monotonic queue.

We go through the sorted vectors and maintain another array of intersection points. Once the queue has more than 2 elements, intersection points appear between them.

For the current vector, if the previous intersection point is on the **opposite side** of the half-plane this vector represents, then the previous edge is no longer useful.

![Monotonic queue](./images/hpi2.svg)

In the figure above, suppose we take the left half-plane of each vector. After sorting by polar angle, the order of traversal is $\vec a\to\vec b\to\vec c$. When $\vec a$ and $\vec b$ enter the queue, a point $D$ appears in the intersection array (the intersection array stores, at each index, the intersection of the vector at that index in the queue with the previous vector).

Next, when we reach $\vec c$, we find that $D$ is on the right of $\vec c$. Since **the vector that produced** $D$ **must have a smaller polar angle than** $\vec c$, the vector that produced $D$ (that is, $\vec b$) no longer affects the half-plane intersection.

Another possible case happens near the end: a newly added vector may affect the queue from the front.

![Effect on the front of the queue](./images/hpi7.svg)

Again take the left half-plane of each vector. After adding vector $\vec f$, the first intersection point $G$ is on the right of $\vec f$. Applying the rule above in reverse, we see that we should now delete vector $\vec a$, the vector at the **front** of the queue.

Finally, use the vector at the front to remove extra vectors at the back. The front vector gets constrained by later ones, but the back vector does not. At this point they form a cycle, so the front vector can constrain the back vector.

### Getting the half-plane intersection

If the half-plane intersection is a convex $n$-gon, the intersection array ends up with $n$ points. Joining them head to tail gives an $n$-gon with a consistent orientation (clockwise or counterclockwise).

Then you can compute its area by triangulation. (Computing the area is the most basic kind of question.)

Sometimes the half-plane intersection is empty or has area 0, so take care with edge cases.

### Things to watch out for

If a vector can pop all points out of the queue (that is, every point in the queue is on the right of the vector), then we **must** handle the back of the queue first and then the front. So in the loop, we do the `--r;` part first and the `++l;` part second; otherwise the result is wrong. Here is why.

![](./images/hpi4.svg)

In the usual case, when we add an edge (vector $\vec w$) after the queue (in queue order $\left\{\vec{u},\vec{v}\right\}$), a new intersection point $N$ appears and shrinks the range after $\vec{v}$.

![](./images/hpi5.svg)

But each step is general, so point $M$ might get "squeezed out".

![](./images/hpi6.svg)

If a vector $\vec a$ now appears with $M$ on its right, then $M$ must leave the queue. If we then pop from the front with `++l`, we clearly enlarge the region. In fact, $M$ is formed by both $\vec u$ and $\vec v$, so we need to consider which of them affects the current process. Since the vectors are in counterclockwise order after sorting by polar angle, $\vec v$ has the larger effect.

As in the figure above, if $M$ is confirmed to be on the right of $\vec a$, then $\vec v$ can no longer contribute anything to the half-plane intersection.

We remove from the front because **the current vector is more restrictive than the front vector**. This only holds when the queue has more than two segments (vectors); otherwise the situation above happens.

So always remove from the back first, then from the front.

???+ note "Code - comparison"
    ```cpp
    friend bool operator<(seg x, seg y) {
      db t1 = atan2((x.b - x.a).y, (x.b - x.a).x);
      db t2 = atan2((y.b - y.a).y, (y.b - y.a).x);  // compute polar angles
      if (fabs(t1 - t2) > eps)                      // if the polar angles differ
        return t1 < t2;
      return (y.a - x.a) * (y.b - x.a) >
             eps;  // check which side of y vector x is on, so the leftmost comes first
    }
    ```

???+ note "Code - incremental part"
    ```cpp
    // pnt its(seg a,seg b) computes the intersection of segments a and b
    // s[] holds the vectors sorted by polar angle
    // q[] is the vector queue
    // t[i] is the intersection of s[i-1] and s[i]
    // [code style] the queue range is (l,r]
    // we want the half-plane on the left of each vector
    int l = 0, r = 0;
    for (int i = 1; i <= n; ++i)
      if (s[i] != s[i - 1]) {
        // note: check the back of the queue first
        while (r - l > 1 && (s[i].b - t[r]) * (s[i].a - t[r]) >
                                eps)  // if the last intersection is on the right of the vector, pop the back
          --r;
        while (r - l > 1 && (s[i].b - t[l + 2]) * (s[i].a - t[l + 2]) >
                                eps)  // if the first intersection is on the right of the vector, pop the front
          ++l;
        q[++r] = s[i];
        if (r - l > 1) t[r] = its(q[r], q[r - 1]);  // compute the new intersection
      }
    while (r - l > 1 &&
           (q[l + 1].b - t[r]) * (q[l + 1].a - t[r]) > eps)  // remember to delete extra elements
      --r;
    t[r + 1] = its(q[l + 1], q[r]);  // then compute the new intersection
    ++r;
    // note: you cannot do ++r inside the t[] index here...
    ```

## Exercises

[POJ 2451 Uyuw's Concert](http://poj.org/problem?id=2451) watch the edge cases

[POJ 1279 Art Gallery](http://poj.org/problem?id=1279) kernel of a polygon

[CQOI2006 Convex Polygons](https://www.luogu.com.cn/problem/P4196)
