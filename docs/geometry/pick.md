## Pick's theorem

Pick's theorem: for a simple polygon whose vertices are all lattice points, Pick's theorem relates its area ${\displaystyle A}$ to the number of lattice points inside it, ${\displaystyle i}$, and the number of lattice points on its boundary, ${\displaystyle b}$: ${\displaystyle A=i+{\frac {b}{2}}-1}$.

Proof: [Pick's theorem](https://en.wikipedia.org/wiki/Pick%27s_theorem)

It has the following generalizations:

-   Take the area of the basic cell of the lattice as one unit. Pick's theorem still holds on a parallelogram lattice. On an arbitrary triangular lattice, Pick's theorem becomes ${\displaystyle A=2 \times i+b-2}$.
-   For a non-simple polygon ${\displaystyle P}$, Pick's theorem reads ${\displaystyle A=i+{\frac {b}{2}}-\chi (P)}$, where ${\displaystyle \chi (P)}$ is the **Euler characteristic** of ${\displaystyle P}$.
-   Higher-dimensional generalization: the Ehrhart polynomial
-   Pick's theorem is equivalent to **Euler's formula** (${\displaystyle V-E+F=2}$).

## An example problem ([POJ 1265](http://poj.org/problem?id=1265))

### Problem summary

In a Cartesian coordinate system, a robot starts from some point and makes $\textit{n}$ moves; each move goes $\textit{dx}$ to the right and $\textit{dy}$ up. In the end it traces a closed simple polygon in the plane. Find the number of lattice points on the boundary, the number of lattice points inside the polygon, and the area of the polygon.

### Solution

This problem uses the following three facts:

-   For a segment with lattice-point endpoints, if both $\textit{dx}$ and $\textit{dy}$ are nonzero, it passes through $\gcd(\textit{dx}, \textit{dy}) + 1$ lattice points. Of course, when counting a whole figure, the extra point is already counted by the previous edge, so we don't add it. So the number of points covered by one edge is $\gcd(\textit{dx},\textit{dy})$, where $\textit{dx},\textit{dy}$ are the horizontal and vertical extents of the segment. If $\textit{dx}$ or $\textit{dy}$ is $0$, the number of covered points is $\textit{dy}$ **or** $\textit{dx}$, respectively.
-   Pick's theorem: the area of a simple polygon in the plane with lattice-point vertices = (points on the boundary)/2 + (points inside) - 1.
-   The area of any polygon is half the sum of the cross products of the vectors from the origin to each pair of consecutive vertices, taken in order (this can also be derived with a definite integral going clockwise).

??? note "Reference code"
    ```cpp
    --8<-- "docs/geometry/code/pick/pick_1.cpp"
    ```
