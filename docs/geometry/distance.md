author: Chrogeek, frank-xjh, ChungZH, hsfzLZH1, Marcythm, Planet6174, partychicken, i-Yirannn

## Euclidean distance

### Two-dimensional space

#### Definition

The Euclidean distance is the ordinary straight-line distance. In a Cartesian coordinate system, let points $A,B$ have coordinates $A(x_1,y_1),B(x_2,y_2)$. Then the Euclidean distance between them is:

$$
\left | AB \right | = \sqrt{\left ( x_2 - x_1 \right )^2 + \left ( y_2 - y_1 \right )^2}
$$

#### Explanation

For example, if a Cartesian coordinate system has two points $A(6,5),B(2,2)$, the formula easily gives the Euclidean distance between $A$ and $B$:

$$
\left | AB \right | = \sqrt{\left ( 2 - 6 \right )^2 + \left ( 2 - 5 \right )^2} = \sqrt{4^2+3^2} = 5
$$

Also, the Euclidean distance from $P(x,y)$ to the origin is:

$$
|P| = \sqrt{x^2+y^2}
$$

### n-dimensional space

#### Introduction

What about the Euclidean distance between two points in 3D space? Look at the figure below.

![dis-3-dimensional](./images/distance-0.png)

We can easily see that in $\triangle ADC$, $\angle ADC = 90^\circ$, and in $\triangle ACB$, $\angle ACB = 90^\circ$.

$$
\begin{aligned}
\therefore ~ |AB| &= \sqrt{|AC|^2+|BC|^2} \\
&= \sqrt{|AD|^2+|CD|^2+|BC|^2}
\end{aligned}
$$

#### Definition

So the formula for the Euclidean distance in 3D space is:

$$
\begin{gathered}
\left | AB \right | = \sqrt{\left ( x_2 - x_1 \right )^2 + \left ( y_2 - y_1 \right )^2 + \left ( z_2 - z_1 \right )^2} \\
|P| = \sqrt{x^2+y^2+z^2}
\end{gathered}
$$

#### Explanation

[NOIP2017 Senior Group — Cheese](https://uoj.ac/problem/332) uses this idea and can serve as an example problem for Euclidean distance.

Continuing in the same way, we get the formula for the Euclidean distance in $n$-dimensional space: for $\vec A(x_{11}, x_{12}, \cdots,x_{1n}) ,~ \vec B(x_{21}, x_{22}, \cdots,x_{2n})$,

$$
\begin{aligned}
\lVert\overrightarrow{AB}\rVert &= \sqrt{\left ( x_{11} - x_{21} \right )^2 + \left ( x_{12} - x_{22} \right )^2 + \cdot \cdot \cdot +\left ( x_{1n} - x_{2n} \right )^2}\\
&= \sqrt{\sum_{i = 1}^{n}(x_{1i} - x_{2i})^2}
\end{aligned}
$$

The Euclidean distance is very useful, but it also has a clear drawback: the distance between two lattice points is often a floating-point number, which brings some error.

## Manhattan distance

### Definition

In 2D space, the Manhattan distance between two points is the absolute difference of their x-coordinates plus the absolute difference of their y-coordinates. For points $A(x_1,y_1),B(x_2,y_2)$, the Manhattan distance between $A$ and $B$ is:

$$
d(A,B) = |x_1 - x_2| + |y_1 - y_2|
$$

### Explanation

Look at the figure below:

![manhattan-dis-diff](./images/distance-1.png)

Between $A$ and $B$, the yellow and orange lines both show the Manhattan distance, the red and blue lines show equivalent Manhattan distances, and the green line shows the Euclidean distance.

Using the same example as before, in the figure below $A$ and $B$ have coordinates $A(25,20),B(10,10)$.

![manhattan-dis](./images/distance-2.svg)

The formula easily gives the Manhattan distance between $A$ and $B$:

$$
d(A,B) = |20 - 10| + |25 - 10| = 10 + 15 = 25
$$

By the same reasoning, the Manhattan distance in $n$-dimensional space is:

$$
\begin{aligned}
d(A,B) &= |x_1 - y_1| + |x_2 - y_2| + \cdot \cdot \cdot + |x_n - y_n|\\
&= \sum_{i = 1}^{n}|x_i - y_i|
\end{aligned}
$$

### Properties

Besides the formula, the Manhattan distance has the following mathematical properties:

-   Non-negativity: the Manhattan distance is a non-negative number, that is, $d(i,j)\geq 0$.
-   Identity: the Manhattan distance from a point to itself is $0$, that is, $d(i,i) = 0$.
-   Symmetry: the Manhattan distance from $A$ to $B$ equals that from $B$ to $A$, that is, $d(i,j) = d(j,i)$.
-   Triangle inequality: the direct distance from point $i$ to $j$ is never larger than the distance via any other point $k$, that is, $d(i,j)\leq d(i,k)+d(k,j)$.

### Example problem

[P5098 USACO04OPEN Cave Cows 3](https://www.luogu.com.cn/problem/P5098)

For the expression $|x_1-x_2|+|y_1-y_2|$ in the problem, we may assume $x_1 - x_2 \geq 0$, and split into two cases by the sign of $y_1 - y_2$:

-   $(y_1 - y_2 \geq 0)\rightarrow |x_1-x_2|+|y_1-y_2|=x_1 + y_1 - (x_2 + y_2)$

-   $(y_1 - y_2 < 0)\rightarrow |x_1-x_2|+|y_1-y_2|=x_1 - y_1 - (x_2 - y_2)$

So we just need the maximum and minimum of $x+y$ and of $x-y$ to get the answer.

??? note "Reference code"
    === "C++"
        ```cpp
        #include <algorithm>
        #include <cstdio>
        using namespace std;
        
        int main() {
          int n, x, y, minx = 0x7fffffff, maxx = 0, miny = 0x7fffffff, maxy = 0;
          scanf("%d", &n);
          for (int i = 1; i <= n; i++) {
            scanf("%d%d", &x, &y);
            minx = min(minx, x + y), maxx = max(maxx, x + y);
            miny = min(miny, x - y), maxy = max(maxy, x - y);
          }
          printf("%d\n", max(maxx - minx, maxy - miny));
          return 0;
        }
        ```
    
    === "Python"
        ```python
        minx = 0x7FFFFFFF
        maxx = 0
        miny = 0x7FFFFFFF
        maxy = 0
        n = int(input())
        for i in range(1, n + 1):
            x, y = map(lambda x: int(x), input().split())
            minx = min(minx, x + y)
            maxx = max(maxx, x + y)
            miny = min(miny, x - y)
            maxy = max(maxy, x - y)
        print(max(maxx - minx, maxy - miny))
        ```

There is actually a second approach: convert the Manhattan distance into a Chebyshev distance. We cover it in the last part.

## Chebyshev distance

### Definition

The Chebyshev distance is a metric on a vector space, where the distance between two points is the largest difference among their coordinates.[^ref1]

In 2D space, the Chebyshev distance between two points is the larger of the absolute difference of their x-coordinates and the absolute difference of their y-coordinates. For points $A(x_1,y_1),B(x_2,y_2)$, the Chebyshev distance between $A$ and $B$ is:

$$
d(A,B) = \max(|x_1 - x_2|, |y_1 - y_2|)
$$

In $n$-dimensional space, the Chebyshev distance is:

$$
\begin{aligned}
d(x,y) &= \max\begin{Bmatrix} |x_1 - y_1|,|x_2 - y_2|,\cdot \cdot \cdot,|x_n - y_n|\end{Bmatrix} \\
&= \max\begin{Bmatrix} |x_i - y_i|\end{Bmatrix}(i \in [1, n])\end{aligned}
$$

### Explanation

With the same example again, in the figure below $A$ and $B$ have coordinates $A(25,20),B(10,10)$.

![Chebyshev-dis](./images/distance-2.svg)

$$
d(A,B) = \max(|20 - 10|, |25 - 10|) = \max(10, 15) = 15
$$

## Converting between Manhattan and Chebyshev distance

### How it works

First, let's draw all points in the Cartesian plane whose Manhattan distance to the origin is $1$.

From the formula, we get the equation $|x| + |y| = 1$.

Expanding the absolute values gives $4$ linear functions:

$$
\begin{aligned}
&y = -x + 1 &(x \geq 0, y \geq 0) \\
&y = x + 1 &(x \leq 0, y \geq 0) \\
&y = x - 1  &(x \geq 0, y \leq 0)  \\
&y = -x - 1  &(x \leq 0, y \leq 0) \\
\end{aligned}
$$

Drawing these $4$ functions in the plane gives a square with side length $\sqrt{2}$, as shown below:

![dis-diff-square-1](./images/distance-3.svg)

Every point on the boundary of this square has Manhattan distance $1$ to the origin.

Similarly, let's draw all points in the plane whose Chebyshev distance to the origin is $1$.

From the formula, we know $\max(|x|,|y|)=1$.

Expanding this also gives $4$ line segments:

$$
\begin{aligned}
&y = 1&(-1\leq x \leq 1) \\
&y = -1&(-1\leq x \leq 1) \\
&x = 1,&(-1\leq y \leq 1) \\
&x = -1,&(-1\leq y \leq 1) \\
\end{aligned}
$$

Drawing them in the plane gives a square with side length $2$, as shown below:

![dis-diff-square-2](./images/distance-4.svg)

Every point on the boundary of this square has Chebyshev distance $1$ to the origin.

Comparing the two figures, we make a surprising discovery:

The $2$ squares are similar figures.

### Proof

So is there a connection between the Manhattan distance and the Chebyshev distance?

Let's sketch a proof:

Let $A(x_1,y_1),B(x_2,y_2)$.

If we expand the absolute values in the Manhattan distance, we get four values. The largest of them is the sum of two non-negative numbers, which is exactly the Manhattan distance. So the Manhattan distance between $A$ and $B$ is:

$$
\begin{aligned}
d(A,B)&=|x_1 - x_2| + |y_1 - y_2|\\
&=\max\begin{Bmatrix} x_1 - x_2 + y_1 - y_2, x_1 - x_2 + y_2 - y_1,x_2 - x_1 + y_1 - y_2, x_2 - x_1 + y_2 - y_1\end{Bmatrix}\\
&= \max(|(x_1 + y_1) - (x_2 + y_2)|, |(x_1 - y_1) - (x_2 - y_2)|)
\end{aligned}
$$

We can easily see that this is the Chebyshev distance between the points $(x_1 + y_1,x_1 - y_1)$ and $(x_2 + y_2,x_2 - y_2)$.

So if we map every point $(x,y)$ to $(x + y, x - y)$, the Chebyshev distance in the new coordinate system equals the Manhattan distance in the original one.

Similarly, the Chebyshev distance between $A$ and $B$ is:

$$
\begin{aligned}
d(A,B)&=\max\begin{Bmatrix} |x_1 - x_2|,|y_1 - y_2|\end{Bmatrix}\\
&=\max\begin{Bmatrix} \left|\dfrac{x_1 + y_1}{2}-\dfrac{x_2 + y_2}{2}\right|+\left|\dfrac{x_1 - y_1}{2}-\dfrac{x_2 - y_2}{2}\right|\end{Bmatrix}
\end{aligned}
$$

And this is the Manhattan distance between the points $(\dfrac{x_1 + y_1}{2},\dfrac{x_1 - y_1}{2})$ and $(\dfrac{x_2 + y_2}{2},\dfrac{x_2 - y_2}{2})$.

So if we map every point $(x,y)$ to $(\dfrac{x + y}{2},\dfrac{x - y}{2})$, the Manhattan distance in the new coordinate system equals the Chebyshev distance in the original one.

### Conclusion

-   The Manhattan coordinate system is obtained by rotating the Chebyshev coordinate system by $45^\circ$ and then scaling it down to half its size.
-   After changing each point $(x,y)$ to $(x + y, x - y)$, the Manhattan distance in the original system equals the Chebyshev distance in the new system.
-   After changing each point $(x,y)$ to $(\dfrac{x + y}{2},\dfrac{x - y}{2})$, the Chebyshev distance in the original system equals the Manhattan distance in the new system.

When a problem asks for Chebyshev or Manhattan distances, we can often convert one into the other to solve it. Each distance has its own strengths and weaknesses in different problems, so use them flexibly.

### Example problems

[P4648 IOI2007 Pairs](https://www.luogu.com.cn/problem/P4648) (Manhattan distance to Chebyshev distance)

[P3964 TJOI2013 Squirrel Party](https://www.luogu.com.cn/problem/P3964) (Chebyshev distance to Manhattan distance)

Finally, here is the second solution to [P5098 USACO04OPEN Cave Cows 3](https://www.luogu.com.cn/problem/P5098):

We convert the Manhattan distance asked for in the problem into a Chebyshev distance, that is, change each point's coordinates $(x,y)$ to $(x + y, x - y)$.

The answer then becomes $\max\limits_{i,j\in n}\begin{Bmatrix} \max\begin{Bmatrix} |x_i - x_j|,|y_i - y_j|\end{Bmatrix}\end{Bmatrix}$.

To maximize the difference of x-coordinates and the difference of y-coordinates, we only need to precompute the maximum and minimum of $x$ and $y$.

??? note "Reference code"
    === "C++"
        ```cpp
        #include <algorithm>
        #include <cstdio>
        using namespace std;
        
        int main() {
          int n, x, y, a, b, minx = 0x7fffffff, maxx = 0, miny = 0x7fffffff, maxy = 0;
          scanf("%d", &n);
          for (int i = 1; i <= n; i++) {
            scanf("%d%d", &a, &b);
            x = a + b, y = a - b;
            minx = min(minx, x), maxx = max(maxx, x);
            miny = min(miny, y), maxy = max(maxy, y);
          }
          printf("%d\n", max(maxx - minx, maxy - miny));
          return 0;
        }
        ```
    
    === "Python"
        ```python
        minx = 0x7FFFFFFF
        maxx = 0
        miny = 0x7FFFFFFF
        maxy = 0
        n = int(input())
        for i in range(1, n + 1):
            a, b = map(lambda x: int(x), input().split())
            x = a + b
            y = a - b
            minx = min(minx, x)
            maxx = max(maxx, x)
            miny = min(miny, y)
            maxy = max(maxy, y)
        print(max(maxx - minx, maxy - miny))
        ```

Comparing the two programs, we find that two different ideas lead to code that is completely equivalent. Isn't that neat? Of course, deeper topics are left for you to explore on your own.

## Minkowski distance

For two points $X(x_1, x_2, \dots, x_n)$ and $Y(y_1, y_2, \dots, y_n)$ in $n$-dimensional space, we define the Minkowski distance between them as:

$$
D(X, Y) = \left(\sum_{i=1}^n \left\vert x_i - y_i \right\vert ^p\right)^{\frac{1}{p}}.
$$

In particular:

1.  When $p=1$, $D(X, Y) = \sum_{i=1}^n \left\vert x_i - y_i \right\vert$ is the Manhattan distance;
2.  When $p=2$, $D(X, Y) = \left(\sum_{i=1}^n (x_i - y_i)^2\right)^{1/2}$ is the Euclidean distance;
3.  When $p \to \infty$, $D(X, Y) = \lim_{p \to \infty}\left(\sum_{i=1}^n \left\vert x_i - y_i \right\vert ^p\right) ^{1/p} = \max\limits_{i=1}^n \left\vert x_i - y_i \right\vert$ is the Chebyshev distance.

Note: the Minkowski distance is a metric only when $p \ge 1$. For the proof, see [Minkowski distance - Wikipedia](https://en.wikipedia.org/wiki/Minkowski_distance).

## References and links

1.  [A brief look at three common distance metrics](https://www.luogu.com.cn/blog/xuxing/Distance-Algorithm). Thanks to the author xuxing for permission.

[^ref1]: [Chebyshev distance - Wikipedia (Chinese)](https://zh.wikipedia.org/wiki/%E5%88%87%E6%AF%94%E9%9B%AA%E5%A4%AB%E8%B7%9D%E7%A6%BB)
