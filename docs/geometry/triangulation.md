author: xehoth

In geometry, a triangulation divides a planar object into triangles, and by extension divides a higher-dimensional geometric object into simplices.
A given point set has many possible triangulations, for example:

![Three triangulations](./images/triangulation-0.svg)

This article introduces the 2D Delaunay triangulation (DT for short) and a divide and conquer algorithm to build it.

## Delaunay triangulation

### Definition

In mathematics and computational geometry, for a given discrete point set $P$ in the plane, its Delaunay triangulation DT($P$) satisfies:

1.  Empty circle property: DT($P$) is **unique** (no four points are concyclic), and in DT($P$) no other point lies inside the circumcircle of **any** triangle.
2.  Maximizing the minimum angle: among all triangulations of the point set $P$, the triangles of DT($P$) have the largest minimum angle. In this sense, DT($P$) is the triangulation **closest to regular**. Specifically, for two adjacent triangles forming a convex quadrilateral, swapping the diagonal does not increase the minimum of their interior angles.

![A Delaunay triangulation with circumcircles shown](./images/triangulation-1.svg)

### Properties

1.  Closest: triangles are formed from the three nearest points, and no two segments (triangle edges) cross.
2.  Uniqueness: no matter where in the region you start building, you always get the same result (as long as no four points in the set are concyclic).
3.  Optimality: if the diagonal of the convex quadrilateral formed by any two adjacent triangles can be swapped, swapping it does not increase the smallest of the six interior angles of the two triangles.
4.  Most regular: if you sort the minimum angles of all triangles in a triangulation in ascending order, the Delaunay triangulation gives the largest sequence.
5.  Locality: adding, removing or moving a vertex only affects nearby triangles.
6.  Convex outer boundary: the outermost boundary of the triangulation forms a convex polygon.

## Divide and conquer algorithm for building the DT

There are many algorithms for building a DT. Below we introduce a divide and conquer algorithm with time complexity $O(n \log n)$.

The first step is to sort the given points by $x$-coordinate in **ascending** order, breaking ties by $y$-coordinate in ascending order, and to remove duplicate points. The figure below shows a sorted point set of size $10$.

![A sorted point set of size 10](./images/triangulation-2.svg)

If there are fewer than $2$ points, no edges are needed. Otherwise, keep splitting the sorted point set in the middle until each subset has size $2$ or $3$. Two points are joined by an edge; three non-collinear points are joined into a triangle; three collinear points only get edges between the two pairs that are adjacent after sorting.

![Divided into point sets of 2 or 3 points](./images/triangulation-3.svg)

Then, while returning from the recursion, merge the triangulations of the left and right subsets one by one. After merging, the edges fall into LL-edges (inside the left subset), RR-edges (inside the right subset) and LR-edges (connecting the left and right subsets), shown in gray, red and blue in the figure below. To keep the DT property, merging **may** need to delete some LL-edges and RR-edges, but it **never** adds edges of these two kinds.

![The three kinds of edges after merging](./images/triangulation-4.svg)

The first step in merging the left and right triangulations is to find the lower common tangent of the two convex hulls and insert the corresponding base LR-edge. The recursion returns boundary edges of the left and right hulls. Starting from the rightmost point of the left hull and the leftmost point of the right hull, move along the hull boundaries until no point lies to the right of the directed line from the left endpoint to the right endpoint.

![Merging the left and right triangulations](./images/triangulation-5.svg)

Next, we need to find the LR-edge **immediately above** the base LR-edge. For example, for the right point set, the possible endpoints (right endpoints) of the next LR-edge are the other endpoints of the RR-edges connected to the right endpoint of the base LR-edge (points $6, 7, 9$), and the left endpoint is point $2$.

![The next LR-edge](./images/triangulation-6.svg)

Take the right endpoint as an example. Starting from the ray pointing to the left endpoint of the base LR-edge, check the RR-edges connected to the right endpoint in clockwise order:

1.  Only endpoints strictly above the base LR-edge are valid candidates, that is, points to the left of the directed line from the base's left endpoint to its right endpoint. The corresponding clockwise turning angle must be in $(0^\circ,180^\circ)$.
2.  Let the current candidate be $c$, and let the next neighbor in the same direction be $d$. If $d$ lies strictly inside the circumcircle of the two endpoints of the base LR-edge and $c$, delete the RR-edge leading to $c$, and go on to check the edge leading to $d$.
3.  Otherwise keep the current candidate and stop checking this side. Since this side is already a Delaunay triangulation, we only need to compare adjacent candidate edges in the circular order.

![Checking valid candidates](./images/triangulation-7.svg)

In the figure above, points $6,7,9$ are checked in order. The green circle for point $6$ contains the next neighbor $7$, so the RR-edge leading to $6$ is deleted. The purple circle for point $7$ does not contain the next neighbor $9$, so $7$ is kept as the right candidate. It still has to be compared with the left candidate to determine the next LR-edge.

For the left point set, do the mirror image: start from the ray pointing to the right endpoint of the base LR-edge and go in counterclockwise order.

![Checking valid candidates on the left](./images/triangulation-8.svg)

When neither side has a valid candidate, the current base LR-edge is the upper common tangent, and the merge is done. If only one side has a valid candidate, connect it to the other endpoint of the base LR-edge to get the new LR-edge.

When both sides have valid candidates: if the right candidate lies strictly inside the circumcircle of the left candidate and the two endpoints of the base, choose the right candidate; otherwise choose the left candidate. Connect the chosen candidate to the base endpoint on the other side to get the new LR-edge. If the four points are concyclic, either choice works.

![The next LR-edge](./images/triangulation-9.svg)

Once this LR-edge is added, use it as the new base LR-edge and repeat the steps above to add the next one, until the merge is complete.

![Merging](./images/triangulation-10.svg)

### Implementation

If you store edges only in unordered adjacency lists and scan all edges of both endpoints every time an LR-edge is added, the time complexity becomes $O(n^2)$, because one endpoint may form many LR-edges in a row, so its adjacency list is scanned again and again.

The reference implementation uses the quad-edge[^quad-edge] structure to maintain the circular order of edges. Each undirected edge is recorded as four directed edges: two for the two directions in the original graph, and two for the two directions in the dual graph. The records of one group are stored contiguously, so we only need to store, for each directed edge, its origin and the next counterclockwise edge with the same origin. This supports the following operations in $O(1)$ time:

| Operation       | Meaning                                                  |
| --------------- | -------------------------------------------------------- |
| `rev(e)`        | the reversed edge                                        |
| `onext(e)`      | the next counterclockwise edge with the same origin      |
| `oprev(e)`      | the previous counterclockwise edge with the same origin  |
| `lnext(e)`      | move one edge forward along the boundary of the left face |
| `onext(rev(e))` | move one edge backward along the boundary of the right face |

`splice(a, b)` changes the circular orders of both the original graph and the dual graph at once; it is used to join or split the rings that the two edges belong to. `connect(a, b)` connects the end of `a` and the start of `b` within the same face. To delete an edge, remove each of its two directions from the corresponding ring. These topological operations only change a constant number of records. The reference implementation allocates and recycles edges with a dynamic array, so each takes amortized $O(1)$ time.

In the code, `base` points from the right point set to the left point set, so the points "above" the base LR-edge in the figures lie to the right of the directed edge `base`. The left candidate edge is `onext(rev(base))` and the right candidate edge is `oprev(base)`. After deleting a candidate edge, just keep moving along the circular order on that side.

??? note "Implementation"
    ```cpp
    --8<-- "docs/geometry/code/triangulation/triangulation_1.cpp:delaunay"
    ```

### Complexity

Suppose one merge involves $k$ points. When finding the lower common tangent, each move advances along the hull boundary of one side, for $O(k)$ moves in total. When choosing candidates, each further step comes with the deletion of an LL-edge or RR-edge, and the two sub-triangulations have only $O(k)$ edges in total. Apart from these deletions, each iteration of the merge's main loop does a constant number of tests and adds one LR-edge; newly added LR-edges are never deleted during this merge, and there are $O(k)$ of them. So one merge takes $O(k)$ time in total.

The initial sort takes $O(n \log n)$, and the recursion satisfies $T(n)=T(\lfloor n/2 \rfloor)+T(\lceil n/2 \rceil)+O(n)$, so the total time complexity is $O(n \log n)$. At any moment, $O(n)$ edges are kept, and the code recycles the storage of deleted edges instead of keeping all past edges, so the space complexity is $O(n)$.

## Voronoi diagram

Given $n\ge 1$ distinct seed points in the plane, the Voronoi region of a seed point consists of all points whose distance to that seed is no greater than their distance to any other seed. These regions are convex (possibly unbounded), their interiors are disjoint, and together they cover the whole plane. The common boundary of two adjacent regions lies on the perpendicular bisector of the segment joining their two seeds.

For a point set that is not all collinear and has no four concyclic points, the Voronoi diagram and the Delaunay triangulation are duals of each other: each triangular face corresponds to its circumcenter; each interior edge corresponds to the segment joining the circumcenters of the triangles on its two sides; each convex hull edge corresponds to a ray that starts at the circumcenter of its triangle, is perpendicular to the edge, and points outward from the hull. If four points are concyclic, you need to merge coinciding circumcenters and remove zero-length dual edges after building. If all points are collinear, the Voronoi edges are the perpendicular bisector lines of adjacent points after sorting; if there is only one point, its region is the whole plane.

![Duality between the Voronoi diagram and the Delaunay triangulation](./images/triangulation-11.svg)

In the figure above, the solid points $P_i$ are seeds and the hollow points $O_i$ are triangle circumcenters. The solid blue lines form the Voronoi diagram, and the dashed orange lines form the Delaunay triangulation. Background colors distinguish the Voronoi regions, and arrows mark unbounded edges; only the part inside a finite window is shown.

After building the DT, we can enumerate faces and edges using the existing circular order of edges, and do the conversion above in $O(n)$ time. So the total time complexity of building the Voronoi diagram is $O(n \log n)$.

## Problems

[Luogu P6362 Euclidean Minimum Spanning Tree in the Plane](https://www.luogu.com.cn/problem/P6362) a classic application of triangulation

[SGU 383 Caravans](https://codeforces.com/problemsets/acmsguru/problem/99999/383) triangulation + binary lifting

[ContestHunter. Endless Destruction](http://noi-test.zzstep.com/contest/Beta%20Round%20%EF%BC%832%20%28%E6%96%B0%E7%96%86%E7%9C%81%E9%98%9F%E4%BA%92%E6%B5%8BWeek1-Day2%29/%E6%97%A0%E5%B0%BD%E7%9A%84%E6%AF%81%E7%81%AD) build the Voronoi diagram as the dual graph of a triangulation

[Codeforces Gym 103485M. Constellation collection](https://codeforces.com/gym/103485/problem/M) triangulate, build a graph, then flood fill

## References and further reading

1.  [Wikipedia - Triangulation (geometry)](https://en.wikipedia.org/wiki/Triangulation_%28geometry%29)
2.  [Wikipedia - Delaunay triangulation](https://en.wikipedia.org/wiki/Delaunay_triangulation)
3.  [Samuel Peterson - Computing Constrained Delaunay Triangulations in 2-D (1997-98)](http://www.geom.uiuc.edu/~samuelp/del_project.html)

[^quad-edge]: Leonidas Guibas, Jorge Stolfi.[Primitives for the Manipulation of General Subdivisions and the Computation of Voronoi Diagrams](https://people.eecs.berkeley.edu/~jrs/meshpapers/GuibasStolfi.pdf). ACM Transactions on Graphics, 4(2), 1985, 74–123.
