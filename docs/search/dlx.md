author: LeverImmy, 383494

This page introduces the exact cover problem and the set cover problem with repetition allowed, "Algorithm X" which solves both, and Dancing Links, the doubly linked cross list used to speed up Algorithm X. It also shows how to use DLX, together with suitable modeling, to solve some search problems.

## Exact cover problem

### Definition

The exact cover problem is: given many sets $S_i (1 \le i \le n)$ and a set $X$, find an unordered tuple $(T_1, T_2, \cdots , T_m)$ satisfying the following conditions:

1.  $\forall i, j \in [1, m],T_i\bigcap T_j = \varnothing (i \neq j)$
2.  $X = \bigcup\limits_{i = 1}^{m}T_i$
3.  $\forall i \in[1, m], T_i \in \{S_1, S_2, \cdots, S_n\}$

### Explanation

For example, given

$$
\begin{aligned}
  & S_1 = \{5, 9, 17\} \\
  & S_2 = \{1, 8, 119\} \\
  & S_3 = \{3, 5, 17\} \\
  & S_4 = \{1, 8\} \\
  & S_5 = \{3, 119\} \\
  & S_6 = \{8, 9, 119\} \\
  & X = \{1, 3, 5, 8, 9, 17, 119\}
\end{aligned}
$$

then $(S_1, S_4, S_5)$ is a valid solution.

### Reformulating the problem

If we discretize all the numbers in $\bigcup\limits_{i = 1}^{n}S_i$, we get the following model:

> Given a 0/1 matrix, choose some rows so that in the end every column[^note1] contains exactly one 1.
> For example, modeling the example above gives this matrix:

$$
\begin{pmatrix}
0 & 0 & 1 & 0 & 1 & 1 & 0 \\
1 & 0 & 0 & 1 & 0 & 0 & 1 \\
0 & 1 & 1 & 0 & 0 & 1 & 0 \\
1 & 0 & 0 & 1 & 0 & 0 & 0 \\
0 & 1 & 0 & 0 & 0 & 0 & 1 \\
0 & 0 & 0 & 1 & 1 & 0 & 1
\end{pmatrix}
$$

> Here row $i$ represents $S_i$, and the numbers in this row represent, in order, $[1 \in S_i],[3 \in S_i],[5 \in S_i],\cdots,[119 \in S_i]$.

### Implementation

#### Brute force 1

One approach is to enumerate which rows to choose, and then check whether the choice is valid.

Each row has two states, chosen or not chosen, so enumerating the rows takes $O(2^n)$ time;

and each check takes $O(nm)$ time. So the total complexity is $O(nm\cdot2^n)$.

??? note "Implementation"
    ```cpp
    int ok = 0;
    for (int state = 0; state < 1 << n; ++state) {  // enumerate whether each row is chosen
      for (int i = 1; i <= n; ++i)
        if ((1 << i - 1) & state)
          for (int j = 1; j <= m; ++j) a[i][j] = 1;
      int flag = 1;
      for (int j = 1; j <= m; ++j)
        for (int i = 1, bo = 0; i <= n; ++i)
          if (a[i][j]) {
            if (bo)
              flag = 0;
            else
              bo = 1;
          }
      if (!flag)
        continue;
      else {
        ok = 1;
        for (int i = 1; i <= n; ++i)
          if ((1 << i - 1) & state) printf("%d ", i);
        puts("");
      }
      memset(a, 0, sizeof(a));
    }
    if (!ok) puts("No solution.");
    ```

#### Brute force 2

Because of the special structure of a 0/1 matrix, each row can be seen as an $m$-bit binary number.

So the original problem becomes

> Given $n$ binary numbers of $m$ bits each, choose some of them so that the AND of any two chosen numbers is 0, and the OR of all chosen numbers is $2^m - 1$. `tmp` is the OR of the binary numbers chosen so far.

Each row has two states, chosen or not chosen, so enumerating the rows takes $O(2^n)$ time;

and each computation of `tmp` takes $O(n)$ time. So the total complexity is $O(n\cdot2^n)$.

??? note "Implementation"
    ```cpp
    int ok = 0;
    for (int i = 1; i <= n; ++i)
      for (int j = m; j >= 1; --j) num[i] = num[i] << 1 | a[i][j];
    for (int state = 0; state < 1 << n; ++state) {
      int tmp = 0;
      bool flag = true;
      for (int i = 1; i <= n; ++i)
        if ((1 << i - 1) & state) {
          if (tmp & num[i]) {
            flag = false;
            break;
          }
          tmp |= num[i];
        }
      if (flag && tmp == (1 << m) - 1) {
        ok = 1;
        for (int i = 1; i <= n; ++i)
          if ((1 << i - 1) & state) printf("%d ", i);
        puts("");
      }
    }
    if (!ok) puts("No solution.");
    ```

## Set cover with repetition allowed

This problem is similar to the exact cover problem, but without the restriction that elements must not overlap. [Algorithm X](#algorithm-x), introduced below, was originally designed for the exact cover problem, but with some changes and optimizations (marked in the text) it can solve this problem efficiently as well.

## Algorithm X

Donald E. Knuth proposed Algorithm X. Its idea is about the same as the brute force above, but it is easier to optimize.

### Process

Continuing with the example above, we get this 0/1 matrix:

$$
\begin{pmatrix}
  0 & 0 & 1 & 0 & 1 & 1 & 0 \\
  1 & 0 & 0 & 1 & 0 & 0 & 1 \\
  0 & 1 & 1 & 0 & 0 & 1 & 0 \\
  1 & 0 & 0 & 1 & 0 & 0 & 0 \\
  0 & 1 & 0 & 0 & 0 & 0 & 1 \\
  0 & 0 & 0 & 1 & 1 & 0 & 1
\end{pmatrix}
$$

1.  Now row 1 has $3$ ones, row 2 has $3$ ones, row 3 has $3$ ones, row 4 has $2$ ones, row 5 has $2$ ones, and row 6 has $3$ ones. Choose row 1, delete it, and mark every column that contains one of its $1$s;

    $$
    \begin{pmatrix}
      \color{Blue}0 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 & \color{Blue}0 \\
      1 & 0 & \color{Red}0 & 1 & \color{Red}0 & \color{Red}0 & 1 \\
      0 & 1 & \color{Red}1 & 0 & \color{Red}0 & \color{Red}1 & 0 \\
      1 & 0 & \color{Red}0 & 1 & \color{Red}0 & \color{Red}0 & 0 \\
      0 & 1 & \color{Red}0 & 0 & \color{Red}0 & \color{Red}0 & 1 \\
      0 & 0 & \color{Red}0 & 1 & \color{Red}1 & \color{Red}0 & 1
      \end{pmatrix}
    $$

2.  Take all marked columns, delete them, and mark every row that has a $1$ in these columns (for the set cover problem with repetition, no rows need to be marked);

    $$
    \begin{pmatrix}
      \color{Blue}0 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 & \color{Blue}0 \\
      1 & 0 & \color{Blue}0 & 1 & \color{Blue}0 & \color{Blue}0 & 1 \\
      \color{Red}0 & \color{Red}1 & \color{Blue}1 & \color{Red}0 & \color{Blue}0 & \color{Blue}1 & \color{Red}0 \\
      1 & 0 & \color{Blue}0 & 1 & \color{Blue}0 & \color{Blue}0 & 0 \\
      0 & 1 & \color{Blue}0 & 0 & \color{Blue}0 & \color{Blue}0 & 1 \\
      \color{Red}0 & \color{Red}0 & \color{Blue}0 & \color{Red}1 & \color{Blue}1 & \color{Blue}0 & \color{Red}1
    \end{pmatrix}
    $$

3.  Take all marked rows and delete them;

    $$
    \begin{pmatrix}
      \color{Blue}0 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 & \color{Blue}0 \\
      1 & 0 & \color{Blue}0 & 1 & \color{Blue}0 & \color{Blue}0 & 1 \\
      \color{Blue}0 & \color{Blue}1 & \color{Blue}1 & \color{Blue}0 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 \\
      1 & 0 & \color{Blue}0 & 1 & \color{Blue}0 & \color{Blue}0 & 0 \\
      0 & 1 & \color{Blue}0 & 0 & \color{Blue}0 & \color{Blue}0 & 1 \\
      \color{Blue}0 & \color{Blue}0 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 & \color{Blue}0 & \color{Blue}1
    \end{pmatrix}
    $$

    **This means the row has been chosen, and the columns where this row has a $1$ may not contain any other $1$**.

    This gives a new, smaller 0/1 matrix:

    $$
    \begin{pmatrix}
      1 & 0 & 1 & 1 \\
      1 & 0 & 1 & 0 \\
      0 & 1 & 0 & 1
    \end{pmatrix}
    $$

4.  Now row 1 (originally row 2) has $3$ ones, row 2 (originally row 4) has $2$ ones, and row 3 (originally row 5) has $2$ ones. Choose row 1 (originally row 2), delete it, and mark every column that contains one of its $1$s;

    $$
    \begin{pmatrix}
      \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 \\
      \color{Red}1 & 0 & \color{Red}1 & \color{Red}0 \\
      \color{Red}0 & 1 & \color{Red}0 & \color{Red}1
    \end{pmatrix}
    $$

5.  Take all marked columns, delete them, and mark every row that has a $1$ in these columns;

    $$
    \begin{pmatrix}
      \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 \\
      \color{Blue}1 & \color{Red}0 & \color{Blue}1 & \color{Blue}0 \\
      \color{Blue}0 & \color{Red}1 & \color{Blue}0 & \color{Blue}1
    \end{pmatrix}
    $$

6.  Take all marked rows and delete them;

    $$
    \begin{pmatrix}
      \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 \\
      \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 \\
      \color{Blue}0 & \color{Blue}1 & \color{Blue}0 & \color{Blue}1
    \end{pmatrix}
    $$

    This gives an empty matrix. But the last deleted row, `1 0 1 1`, is not all $1$s, so the choice was wrong;

    $$
    \begin{pmatrix}
    \end{pmatrix}
    $$

7.  Backtrack to step 4 and try choosing row 2 (originally row 4) instead. Delete it, and mark every column that contains one of its $1$s;

    $$
    \begin{pmatrix}
      \color{Red}1 & 0 & \color{Red}1 & 1 \\
      \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 \\
      \color{Red}0 & 1 & \color{Red}0 & 1
    \end{pmatrix}
    $$

8.  Take all marked columns, delete them, and mark every row that has a $1$ in these columns;

    $$
    \begin{pmatrix}
      \color{Blue}1 & \color{Red}0 & \color{Blue}1 & \color{Red}1 \\
      \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 \\
      \color{Blue}0 & 1 & \color{Blue}0 & 1
    \end{pmatrix}
    $$

9.  Take all marked rows and delete them;

    $$
    \begin{pmatrix}
      \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 \\
      \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 \\
      \color{Blue}0 & 1 & \color{Blue}0 & 1
      \end{pmatrix}
    $$

    So we get this matrix:

    $$
    \begin{pmatrix}
      1 & 1
    \end{pmatrix}
    $$

10. Now row 1 (originally row 5) has $2$ ones. Delete all of them, which gives an empty matrix:

    $$
    \begin{pmatrix}
    \end{pmatrix}
    $$

11. The row deleted last time was all $1$s, so we have succeeded and the algorithm ends.

    The answer is the three deleted rows: $1, 4, 5$.

We strongly recommend simulating the deletion, restoration and backtracking of the matrix by hand once before reading on.

From the steps above, Algorithm X can be summarized as follows:

1.  For the current matrix $M$, choose and mark a row $r$, and add $r$ to $S$;
2.  If every $r$ has been tried and there is no solution, the algorithm ends and reports no solution;
3.  Mark the rows $r_i$ and columns $c_i$ related to $r$ (related rows and columns are defined as in step 2 of [Algorithm X](#process); the same below);
4.  Delete all marked rows and columns to get a new matrix $M'$;
5.  If $M'$ is empty and $r$ is all $1$s, the algorithm ends and outputs the set $S$ of deleted rows;

    If $M'$ is empty and $r$ is not all $1$s, restore the rows $r_i$ and columns $c_i$ related to $r$, and go to step 1;

    If $M'$ is not empty, go to step 1.

It is easy to see that Algorithm X needs a lot of "delete row", "delete column", "restore row" and "restore column" operations.

A naive idea is to store the matrix in a 2D array, and use four more arrays to store the numbers of the neighboring rows of each row; each deletion and restoration then only needs to update elements of the four arrays. But in typical problems the matrix has far more 0s than 1s, so the space complexity of this approach is unacceptable.

Donald E. Knuth came up with the idea of using a doubly linked cross list to support these operations.

The process of constantly jumping around on the doubly linked cross list is vividly compared to "dancing", so the doubly linked cross list used to optimize Algorithm X is also called "Dancing Links".

## Algorithm X optimized with Dancing Links

### Preprocessor directive

```cpp
#define IT(i, A, x) for (i = A[x]; i != x; i = A[i])
```

### Definition

A doubly linked cross list has four pointer fields, pointing to the elements above, below, to the left, and to the right. Each element $i$ corresponds to one cell in the whole doubly linked cross list, so we also need to store the column and row that $i$ is in, as shown in the figure:

![dlx-1.svg](./images/dlx-1.svg)

A large doubly linked cross list is more complicated:

![dlx-2.svg](./images/dlx-2.svg)

Each row has a row-head indicator, and each column has a column indicator.

The row-head indicator is `first[]`, and the column indicators are $c + 1$ sentinel nodes that we create. Note that **the row-head indicator is not a sentinel node in the list**. It is virtual, like the `first[]` array in an adjacency list, and **points directly** to the first element of the row.

Also, each column has `siz[]`, the number of elements in that column.

In particular, node $0$ having no right node is equivalent to the Dancing Links being empty.

```cpp
constexpr int MS = 1e5 + 5;
int n, m, idx, first[MS], siz[MS];
int L[MS], R[MS], U[MS], D[MS];
int col[MS], row[MS];
```

### Process

#### The remove operation

`remove(c)` deletes column $c$ from the Dancing Links, together with its related rows and columns.

First delete $c$. Then:

-   The right node of the node to the left of $c$ should become the right node of $c$.
-   The left node of the node to the right of $c$ should become the left node of $c$.

That is, `L[R[c]] = L[c], R[L[c]] = R[c];`.

![dlx-3.svg](./images/dlx-3.svg)

Then walk down this column and delete every row we pass.

How do we delete each row? Enumerate the pointer $j$ in the current row. Then:

-   The lower node of the node above $j$ should become the lower node of $j$.
-   The upper node of the node below $j$ should become the upper node of $j$.

Remember to update the number of elements in each column.

That is, `U[D[j]] = U[j], D[U[j]] = D[j], --siz[col[j]];`.

![dlx-4.svg](./images/dlx-4.svg)

The code of the `remove` function is as follows:

???+ note "Implementation"
    ```cpp
    void remove(const int &c) {
      int i, j;
      L[R[c]] = L[c], R[L[c]] = R[c];
      // walk down this column from top to bottom
      IT(i, D, c)
      // walk along this row from left to right
      IT(j, R, i)
      U[D[j]] = U[j], D[U[j]] = D[j], --siz[col[j]];
    }
    ```

#### The recover operation

`recover(c)` restores column $c$ in the Dancing Links, together with its related rows and columns.

`recover(c)` is the inverse of `remove(c)`, so we will not go into detail here.

**Note that all the operations of** `recover(c)` **are done in exactly the reverse order of those in**  `remove(c)`.

The code of `recover(c)` is as follows:

???+ note "Implementation"
    ```cpp
    void recover(const int &c) {
      int i, j;
      IT(i, U, c) IT(j, L, i) U[D[j]] = D[U[j]] = j, ++siz[col[j]];
      L[R[c]] = R[L[c]] = c;
    }
    ```

#### The build operation

`build(r, c)` creates a new Dancing Links of size $r \times c$, that is, with $r$ rows and $c$ columns.

Create $c + 1$ nodes as column indicators.

Node $i$ has left node $i - 1$, right node $i + 1$, upper node $i$, and lower node $i$. In particular, the left node of node $0$ is $c$, and the right node of node $c$ is $0$.

This gives a circular doubly linked list:

![dlx-5.svg](./images/dlx-5.svg)

This initializes a Dancing Links.

The code of `build(r, c)` is as follows:

???+ note "Implementation"
    ```cpp
    void build(const int &r, const int &c) {
      n = r, m = c;
      for (int i = 0; i <= c; ++i) {
        L[i] = i - 1, R[i] = i + 1;
        U[i] = D[i] = i;
      }
      L[0] = c, R[c] = 0, idx = c;
      memset(first, 0, sizeof(first));
      memset(siz, 0, sizeof(siz));
    }
    ```

#### The insert operation

`insert(r, c)` inserts a node at row $r$, column $c$.

There are two cases for insertion:

-   If row $r$ has no elements, insert the element directly and make `first[r]` point to it.

    This can be done with `first[r] = L[idx] = R[idx] = idx;`.

-   If row $r$ already has elements, connect the new element to $c$ and $first(r)$ in a special way.

    Let the new element be $idx$. Then:

    -   Insert $idx$ directly below $c$. Then:

        -   The node below $idx$ is the original lower node of $c$;
        -   The upper node of the node below $idx$ (that is, the original lower node of $c$) is $idx$;
        -   The upper node of $idx$ is $c$;
        -   The lower node of $c$ is $idx$.

        Remember to record the column and row of $idx$, and to update the number of elements in this column.

        ```cpp
        col[++idx] = c, row[idx] = r, ++siz[c];
        U[idx] = c, D[idx] = D[c], U[D[c]] = idx, D[c] = idx;
        ```

        **We strongly recommend fully understanding the order of these steps before reading on.**

    -   Insert $idx$ directly to the right of $first(r)$. Then:

        -   The node to the right of $idx$ is the original right node of $first(r)$;
        -   The left node of the node originally to the right of $first(r)$ is $idx$;
        -   The left node of $idx$ is $first(r)$;
        -   The right node of $first(r)$ is $idx$.

        ```cpp
        L[idx] = first[r], R[idx] = R[first[r]];
        L[R[first[r]]] = idx, R[first[r]] = idx;
        ```

        **We strongly recommend fully understanding the order of these steps before reading on.**

The figure below helps in understanding the `insert(r, c)` operation:

![dlx-6.svg](./images/dlx-6.svg)

Pay attention to the direction of the curved arrows.

The code of `insert(r, c)` is as follows:

???+ note "Implementation"
    ```cpp
    void insert(const int &r, const int &c) {
      row[++idx] = r, col[idx] = c, ++siz[c];
      U[idx] = c, D[idx] = D[c], U[D[c]] = idx, D[c] = idx;
      if (!first[r])
        first[r] = L[idx] = R[idx] = idx;
      else {
        L[idx] = first[r], R[idx] = R[first[r]];
        L[R[first[r]]] = idx, R[first[r]] = idx;
      }
    }
    ```

#### The dance operation

`dance()` is the process of recursively deleting and restoring rows and columns.

1.  If node $0$ has no right node, the matrix is empty; record the answer and return;
2.  Choose the column with the fewest elements and delete it;
3.  Go through every row that has a $1$ in this column, and enumerate whether it is chosen;
4.  Call `dance()` recursively. If it succeeds, return; if not, restore the chosen row;
5.  If there is no solution, return.

The code of `dance()` is as follows:

???+ note "Implementation"
    ```cpp
    bool dance(int dep) {
      int i, j, c = R[0];
      if (!R[0]) {
        ans = dep;
        return true;
      }
      IT(i, R, 0) if (siz[i] < siz[c]) c = i;
      remove(c);
      IT(i, D, c) {
        stk[dep] = row[i];
        IT(j, R, i) remove(col[j]);
        if (dance(dep + 1)) return true;
        IT(j, L, i) recover(col[j]);
      }
      recover(c);
      return false;
    }
    ```

Here `stk[]` records the answer.

Note that each time we prefer to delete the column with the fewest elements. This gives the program a heuristic flavor and keeps the number of branches in the search tree as small as possible.

For the set cover problem with repetition, we can prune during the search with an evaluation function (similar to the one in [A\*](astar.md)): if, even in the best case, the number of chosen rows would exceed the best solution found so far, we can return immediately.

## Template

??? note "[Template code](https://www.luogu.com.cn/problem/P4929)"
    ```cpp
    --8<-- "docs/search/code/dlx/dlx_1.cpp"
    ```

## Properties

The number of recursions and backtracks of DLX depends on the number of $1$s in the matrix, not on parameters like $r$ and $c$. Its time complexity is **exponential**: in theory roughly $O(c^n)$, where $c$ is some constant very close to $1$ and $n$ is the number of $1$s in the matrix.

But in practice DLX performs well and can usually solve most problems.

## Modeling

The hard part of DLX is not so much building the linked list as building the model.

Please make sure you fully understand the DLX template before reading on.

Whenever we get a problem, we should think about what the rows and columns mean:

-   Rows represent *decisions*, because each row corresponds to a set, which corresponds to choosing or not choosing it;

-   Columns represent *states*, because column $i$ corresponds to some condition $P_i$.

For a given row, since the values in different columns differ, we **define a decision by the different states**.

### Example problem 1 [P1784 Sudoku](https://www.luogu.com.cn/problem/P1784)

??? note "Solution idea"
    First, consider what a decision is.
    
    In this problem, each decision can be written as an ordered triple $(r, c, w)$.
    
    Note that the "box" is not a parameter of a decision, because it **can be determined by each fixed $(r, c)$**.
    
    So there are $9 \times 9 \times 9 = 729$ rows.
    
    Next, consider what the states are.
    
    Let us think about what effect the decision $(r, c, w)$ has. Let $b$ be the box containing $(r, c)$.
    
    1.  Row $r$ uses a $w$ (represented by $9 \times 9 = 81$ columns);
    2.  Column $c$ uses a $w$ (represented by $9 \times 9 = 81$ columns);
    3.  Box $b$ uses a $w$ (represented by $9 \times 9 = 81$ columns);
    4.  A number is filled into $(r, c)$ (represented by $9 \times 9 = 81$ columns).
    
    So there are $81 \times 4 = 324$ columns and $729 \times 4 = 2916$ $1$s in total.
    
    With this, we have turned the $9 \times 9$ Sudoku problem into an exact cover problem **with $729$ rows, $324$ columns, and $2916$ $1$s in total**.

??? note "Reference code"
    ```cpp
    --8<-- "docs/search/code/dlx/dlx_2.cpp"
    ```

### Example problem 2 [Target Sudoku](https://www.luogu.com.cn/problem/P1074)

??? note "Solution idea"
    The model for this problem is **exactly the same** as for [Sudoku](https://www.luogu.com.cn/problem/P1784); the main difference is how the answer is updated.
    
    For this problem we can keep an array of weights. Every time we find a Sudoku solution,
    
    we multiply the number in each cell by the corresponding weight and add it to the answer.

??? note "Reference code"
    ```cpp
    --8<-- "docs/search/code/dlx/dlx_3.cpp"
    ```

### Example problem 3 [NOI 2005 Smart Beads Game](https://www.luogu.com.cn/problem/P4205)

??? note "Solution idea"
    Definition: the shape of a bead piece as given in the problem is called its *standard shape*.
    
    Clearly, we can change the shape of a bead piece by changing two parameters: $d$ (the number of $90^{\circ}$ clockwise rotations) and $f$ (whether it is flipped horizontally).
    
    As before, we first consider what a decision is.
    
    In this problem, each decision can be written as an ordered tuple $(v, d, f, i)$.
    
    It means that the top-left corner of the *standard shape* of the $i$-th bead piece is at the position numbered $v$, after $d$ clockwise rotations of $90^{\circ}$.
    
    Conveniently, we can let $f = 1$ mean no horizontal flip and $f = -1$ mean a horizontal flip, which simplifies the code.
    
    So there are $55 \times 4 \times 2 \times 12 = 5280$ rows.
    
    Note that because some placements are invalid, such as $(1, 0, 1, 4)$,
    
    **in practice, even for an empty board, only $2730$ rows need to be built.**
    
    Next, consider what the states are.
    
    The states in this problem are fairly simple.
    
    Let us think about what effect the decision $(v, d, f, i)$ has.
    
    1.  Some cells become occupied (represented by $55$ columns);
    2.  The $i$-th bead piece is used (represented by $12$ columns).
    
    So there are $55 + 12 = 67$ columns and $5280 \times (5 + 1) = 31680$ $1$s in total.
    
    With this, we have turned the Smart Beads Game into an exact cover problem **with $5280$ rows, $67$ columns, and $31680$ $1$s in total**.

??? note "Reference code"
    ```cpp
    --8<-- "docs/search/code/dlx/dlx_4.cpp"
    ```

## Exercises

-   [SUDOKU - Sudoku](https://www.spoj.com/problems/SUDOKU/)
-   ["kuangbin Takes You Flying" Topic 3: Dancing Links](https://vjudge.net/contest/65998#overview)

## External links

-   [The jumping dancer: the Dancing Links algorithm for solving exact cover problems - Wancang Yishu](https://www.cnblogs.com/grenet/p/3145800.html)
-   [Search: the DLX algorithm - Jingting Fengyin](https://www.cnblogs.com/aininot260/p/9629926.html)
-   [*Algorithm Competition Classics: Training Guide*](https://book.douban.com/subject/35431537/)

## Notes

[^note1]: (Regional terminology difference) In Taiwan, the Chinese words for "row" and "column" are used the other way around from mainland China.
