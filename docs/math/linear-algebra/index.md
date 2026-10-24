author: codewasp942

??? tip "Tip"
    This page is not closely related to the other pages under "Linear Algebra". But the author believes it is worthwhile to talk about the essence of linear algebra, trace concepts back to their roots and connections, and give readers a first but systematic picture of the subject.

People were already using systems of linear equations to solve problems thousands of years ago, and today linear algebra is still widely used.

Linear algebra comes from observation. People found that many objects share similar properties, for example:

-   Forces can be decomposed and combined.

-   For any $k,x_0$, $k \sin (x-x_0)$ can be decomposed into $k_1\sin x + k_2\cos x$.

These properties are about **scaling**, **decomposing**, and **superposing** the objects being described. Linear algebra abstracts these properties away from concrete objects and studies them as an independent subject. In OI, linear algebra can be used directly to solve problems, and also to optimize algorithms, data structures and so on. For example:

-   using heavy-light decomposition to maintain linear bases and find the maximum XOR on a path

-   using the matrix-tree theorem to turn counting the spanning trees of a graph into computing the determinant of a matrix

-   using fast matrix exponentiation to speed up recurrences
