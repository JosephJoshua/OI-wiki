2D Mo's algorithm, as the name suggests, is Mo's algorithm where each state can be extended in four directions.

In 2D Mo's algorithm, each pointer move processes a whole row or column of numbers. The implementation is similar to ordinary 1D Mo's algorithm, so we won't repeat it here. This page focuses on choosing the block size.

## Choosing the block size

Let the number of queries be $q$, let the current matrix have top-left corner $(x_1,\ y_1)$ and bottom-right corner $(x_2,\ y_2)$, and let the block size be $B$.

Then the pointer $x_1$ moves $\Theta(q\cdot B)$ times, and the pointer $y_2$ moves $\Theta(n^4\cdot B^{-3})$ times.

So we just set $q\cdot B=n^4\cdot B^{-3}$, i.e. $B=n\cdot q^{-\frac 14}$.

Note that $B$ computed this way **may be $0$**, so **handle this case specially**.

In the end, the computation part takes $\Theta(n^2\cdot q^{\frac 34})$ time. Adding the sorting of the queries, the total time complexity is $\Theta(n^2\cdot q^{\frac 34}+q\log q)$.

## Example problem 1

???+ note "[BZOJ 2639 Rectangle Computation](https://hydro.ac/p/bzoj-P2639)"
    You are given an $n\times m$ matrix in which every element is an integer, and then $q$ queries, each asking for the weight of a submatrix. The weight of a matrix is defined as follows: if an integer $x$ appears $p$ times in the matrix, it contributes $p^2$ to the weight of the matrix.
    
    Constraints: $1\leq n,\ m\leq 200$, $0\leq q\leq 10^5$, $|$ matrix element $| \leq 2\times 10^9$.

??? note "Solution idea"
    First do coordinate compression. Then, during 2D Mo's algorithm, use an array to record how many times each number currently appears.

??? note "Sample code"
    ```cpp
    --8<-- "docs/misc/code/mo-algo-2dimen/mo-algo-2dimen_1.cpp"
    ```

## Example problem 2

???+ note "[Luogu P1527 \[National Training Team\] Matrix Multiplication](https://www.luogu.com.cn/problem/P1527)"
    You are given an $n\times n$ matrix and $q$ queries. Each query asks for the $k$-th smallest number in a subrectangle.
    
    Constraints: $1\leq n\leq 500$, $1\leq q\leq 6\times 10^4$, $0\leq a_{i,j}\leq 10^9$.

First, as in the previous problem, compress the values of the whole matrix. But note that in this problem, besides splitting the positions into blocks, we also need sqrt decomposition over the range of values to get the answer.

We also need odd-even sorting as an optimization here; see [ordinary Mo's algorithm](../misc/mo-algo.md#普通莫队的优化) for details.

The time limit for this problem is not very generous, so pay attention to the constant factor of your code. The computed block size is usually small: with $n,\ q$ both at their maximum, it is around $11$, so you can just hard-code it as a constant to save time.

??? note "Sample code"
    ```cpp
    --8<-- "docs/misc/code/mo-algo-2dimen/mo-algo-2dimen_2.cpp"
    ```
