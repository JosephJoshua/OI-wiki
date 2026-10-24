author: hyp1231, 383494

## Introduction

Inversion is useful when a problem involves tangency between several circles and/or lines. Using the properties of inversion, we can solve the problem in the inverted plane, which can greatly simplify the calculations.

## Definition

Given a center of inversion $O$ and a radius of inversion $R$, if points $P$ and $P'$ in the plane satisfy:

-   point $P'$ lies on the ray $\overrightarrow{OP}$
-   $|OP| \cdot |OP'| = R^2$

then $P$ and $P'$ are called inverse points of each other.

## Explanation

The figure below shows the inversion of a point $P$ in the plane:

![Inv1](./images/inverse1.png)

## Properties

1.  A point outside circle $O$ inverts to a point inside circle $O$, and vice versa; a point on circle $O$ inverts to itself.

2.  A circle $A$ that does not pass through point $O$ inverts to a circle that also does not pass through $O$.

    ![Inv2](./images/inverse2.png)

    -   Let the radius of circle $A$ be $r_1$, and the radius of its image, circle $B$, be $r_2$. Then:

        $$
        r_2 = \frac{1}{2}\left(\frac{1}{|OA| - r_1} - \frac{1}{|OA| + r_1}\right) R^2
        $$

    ???+ note "Proof"
        ![Inv3](./images/inverse3.png)
        
        By the definition of inversion:
        
        $$
        \begin{aligned}
        |OC|\cdot|OC'| &= (|OA|+r_1)\cdot(|OB|-r_2) = R^2 \\
        |OD|\cdot|OD'| &= (|OA|-r_1)\cdot(|OB|+r_2) = R^2
        \end{aligned}
        $$
        
        Eliminate $|OB|$ and solve the equations.

    -   Let point $O$ have coordinates $(x_0, y_0)$, point $A$ have coordinates $x_1, y_1$, and point $B$ have coordinates $x_2, y_2$. Then:

        $$
        \begin{aligned}
        x_2 &= x_0 + \frac{|OB|}{|OA|} (x_1 - x_0) \\
        y_2 &= y_0 + \frac{|OB|}{|OA|} (y_1 - y_0)
        \end{aligned}
        $$

        Here $|OB|$ can be obtained while computing $r_2$ above.

3.  A circle $A$ that passes through point $O$ inverts to a line that does not pass through $O$. This is because a point on circle $A$ that gets arbitrarily close to $O$ inverts to a point arbitrarily far from $O$.

    ![Inv4](./images/inverse4.png)

4.  If two figures are tangent at a point other than $O$, their images under inversion are also tangent.

## Example problem

### [ICPC 2013 Hangzhou Regional — Problem of Apollonius](https://acm.hdu.edu.cn/showproblem.php?pid=4773)

#### Problem summary

Find all circles that pass through a given point outside two circles and are tangent to both circles.

#### Solution

Solving this with analytic geometry looks very hard.

Instead, invert around the point the circle must pass through (any radius of inversion works). The image of each wanted circle is a line (Property $3$), and it is tangent (Property $4$) to the images of the two given circles (Property $2$).

So after inversion, the problem becomes: find all common tangent lines of two circles.

After finding the common tangents, invert them back to the original plane.

??? note "Sample code"
    ```cpp
    #include <algorithm>
    #include <cmath>
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    #include <vector>
    using namespace std;
    
    constexpr double EPS = 1e-8;   // precision tolerance
    const double PI = acos(-1.0);  // π
    constexpr int N = 4;
    
    // point
    struct Point {
      double x, y;
    
      Point(double x = 0, double y = 0) : x(x), y(y) {}
    
      bool operator<(Point A) const { return x == A.x ? y < A.y : x < A.x; }
    };
    
    // vector
    using Vector = Point;
    
    // vector addition
    Vector operator+(Vector A, Vector B) { return Vector(A.x + B.x, A.y + B.y); }
    
    // vector subtraction
    Vector operator-(Vector A, Vector B) { return Vector(A.x - B.x, A.y - B.y); }
    
    // multiply a vector by a scalar
    Vector operator*(Vector A, double p) { return Vector(A.x * p, A.y * p); }
    
    // divide a vector by a scalar
    Vector operator/(Vector A, double p) { return Vector(A.x / p, A.y / p); }
    
    // sign compared with 0
    int dcmp(double x) {
      if (fabs(x) < EPS) return 0;
      return x < 0 ? -1 : 1;
    }
    
    // dot product
    double Dot(Vector A, Vector B) { return A.x * B.x + A.y * B.y; }
    
    // vector length
    double Length(Vector A) { return sqrt(Dot(A, A)); }
    
    // cross product
    double Cross(Vector A, Vector B) { return A.x * B.y - A.y * B.x; }
    
    // projection of a point onto a line
    Point GetLineProjection(Point P, Point A, Point B) {
      Vector v = B - A;
      return A + v * (Dot(v, P - A) / Dot(v, v));
    }
    
    // circle
    struct Circle {
      Point c;
      double r;
    
      Circle() : c(Point(0, 0)), r(0) {}
    
      Circle(Point c, double r = 0) : c(c), r(r) {}
    
      // given a polar angle, return the point on the circle
      Point point(double a) { return Point(c.x + cos(a) * r, c.y + sin(a) * r); }
    };
    
    // common tangents of two circles; returns the number of tangents, -1 means infinitely many
    // a[i] and b[i] are the tangent points of the i-th tangent on circle A and circle B
    int getTangents(Circle A, Circle B, Point* a, Point* b) {
      int cnt = 0;
      if (A.r < B.r) {
        swap(A, B);
        swap(a, b);
      }
      double d2 =
          (A.c.x - B.c.x) * (A.c.x - B.c.x) + (A.c.y - B.c.y) * (A.c.y - B.c.y);
      double rdiff = A.r - B.r;
      double rsum = A.r + B.r;
      if (dcmp(d2 - rdiff * rdiff) < 0) return 0;  // one circle inside the other
    
      double base = atan2(B.c.y - A.c.y, B.c.x - A.c.x);
      if (dcmp(d2) == 0 && dcmp(A.r - B.r) == 0) return -1;  // infinitely many tangents
      if (dcmp(d2 - rdiff * rdiff) == 0) {  // internally tangent, one tangent
        a[cnt] = A.point(base);
        b[cnt] = B.point(base);
        ++cnt;
        return 1;
      }
      // there are external common tangents
      double ang = acos(rdiff / sqrt(d2));
      a[cnt] = A.point(base + ang);
      b[cnt] = B.point(base + ang);
      ++cnt;
      a[cnt] = A.point(base - ang);
      b[cnt] = B.point(base - ang);
      ++cnt;
      if (dcmp(d2 - rsum * rsum) == 0) {  // one internal common tangent
        a[cnt] = A.point(base);
        b[cnt] = B.point(PI + base);
        ++cnt;
      } else if (dcmp(d2 - rsum * rsum) > 0) {  // two internal common tangents
        double ang = acos(rsum / sqrt(d2));
        a[cnt] = A.point(base + ang);
        b[cnt] = B.point(PI + base + ang);
        ++cnt;
        a[cnt] = A.point(base - ang);
        b[cnt] = B.point(PI + base - ang);
        ++cnt;
      }
      return cnt;
    }
    
    // point O is outside circle A; find circle B, the inverse of circle A; R is the radius of inversion
    Circle Inversion_C2C(Point O, double R, Circle A) {
      double OA = Length(A.c - O);
      double RB = 0.5 * ((1 / (OA - A.r)) - (1 / (OA + A.r))) * R * R;
      double OB = OA * RB / A.r;
      double Bx = O.x + (A.c.x - O.x) * OB / OA;
      double By = O.y + (A.c.y - O.y) * OB / OA;
      return Circle(Point(Bx, By), RB);
    }
    
    // invert a line into circle B through point O; R is the radius of inversion
    Circle Inversion_L2C(Point O, double R, Point A, Vector v) {
      Point P = GetLineProjection(O, A, A + v);
      double d = Length(O - P);
      double RB = R * R / (2 * d);
      Vector VB = (P - O) / d * RB;
      return Circle(O + VB, RB);
    }
    
    // returns true if points A and B are on the same side of the line
    bool theSameSideOfLine(Point A, Point B, Point S, Vector v) {
      return dcmp(Cross(A - S, v)) * dcmp(Cross(B - S, v)) > 0;
    }
    
    int main() {
      int T;
      scanf("%d", &T);
      while (T--) {
        Circle A, B;
        Point P;
        scanf("%lf%lf%lf", &A.c.x, &A.c.y, &A.r);
        scanf("%lf%lf%lf", &B.c.x, &B.c.y, &B.r);
        scanf("%lf%lf", &P.x, &P.y);
        Circle NA = Inversion_C2C(P, 10, A);
        Circle NB = Inversion_C2C(P, 10, B);
        Point LA[N], LB[N];
        Circle ansC[N];
        int q = getTangents(NA, NB, LA, LB), ans = 0;
        for (int i = 0; i < q; ++i)
          if (theSameSideOfLine(NA.c, NB.c, LA[i], LB[i] - LA[i])) {
            if (!theSameSideOfLine(P, NA.c, LA[i], LB[i] - LA[i])) continue;
            ansC[ans++] = Inversion_L2C(P, 10, LA[i], LB[i] - LA[i]);
          }
        printf("%d\n", ans);
        for (int i = 0; i < ans; ++i) {
          printf("%.8f %.8f %.8f\n", ansC[i].c.x, ansC[i].c.y, ansC[i].r);
        }
      }
    
      return 0;
    }
    ```

## Exercises

[ICPC 2017 Nanning Regional Online Contest — Finding the Radius for an Inserted Circle](https://vjudge.net/problem/%E8%AE%A1%E8%92%9C%E5%AE%A2-A1283)

[CCPC 2017 Online Contest — The Designer](https://acm.hdu.edu.cn/showproblem.php?pid=6158)

## References and further reading

-   [Inversive geometry - Wikipedia](https://en.wikipedia.org/wiki/Inversive_geometry)

-   [Inversion of circles - ACdreamers's blog](https://blog.csdn.net/acdreamers/article/details/16966369)
