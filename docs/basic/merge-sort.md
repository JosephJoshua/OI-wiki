This page introduces merge sort and how to use it to count inversions.

## Definition

Merge sort ([merge sort](https://en.wikipedia.org/wiki/Merge_sort)) is an efficient, stable, comparison-based sorting algorithm.

## Properties

Merge sort is based on divide and conquer: it sorts the array in pieces and then merges them. Its time complexity is $\Theta (n \log n)$ in the best, worst, and average cases, and its space complexity is $\Theta (n)$.

Merge sort can be done with only $\Theta (1)$ auxiliary space, but for convenience it usually uses an auxiliary array as long as the original one.

## How it works

### Merging

The core of merge sort is the merge step: combining two sorted arrays `a` and `b` into one sorted array `c`.

Go through `a[i]` and `b[j]` from left to right, and each time write the smaller element into `c[k]`. When one array runs out, append the remaining elements of the other array to `c`.

To keep the sort stable, the first element of the front part must be taken as the minimum and put into `c[k]` when it is less than or equal to the first element of the back part (`a[i] <= b[j]`), not only when it is strictly less (`a[i] < b[j]`).

#### Implementation

=== "C/C++"
    === "Array version"
        ```cpp
        --8<-- "docs/basic/code/merge-sort/merge-sort_1.cpp:array"
        ```
    
    === "Pointer version"
        ```cpp
        --8<-- "docs/basic/code/merge-sort/merge-sort_1.cpp:pointer"
        ```
    
    You can also use the `std::merge` function from the `<algorithm>` library. It is used the same way as the pointer version above.

=== "Python"
    ```python
    --8<-- "docs/basic/code/merge-sort/merge-sort_1.py:merge"
    ```

### Merge sort with divide and conquer

1.  When the array has length $1$, it is already sorted and does not need to be split further.
2.  When the array is longer than $1$, it is probably not sorted. Split it into two parts, and check each part for being sorted (using rule 1). If both are sorted, merge them into one sorted array. Otherwise, apply rule 2 again to any part that is not yet sorted, and then merge.

You can prove by mathematical induction that this process turns any array into a sorted one.

To guarantee the complexity, we usually split the array into two parts of nearly equal length ($\textit{mid} = \left\lfloor \dfrac{l + r}{2} \right\rfloor$).

#### Implementation

Note that the ranges in the code below are $[l, r)$, $[l, \textit{mid})$, and $[\textit{mid}, r)$.

=== "C/C++"
    ```cpp
    --8<-- "docs/basic/code/merge-sort/merge-sort_1.cpp:recursive"
    ```

=== "Python"
    ```python
    --8<-- "docs/basic/code/merge-sort/merge-sort_1.py:recursive"
    ```

### Merge sort with binary lifting

We know that an array of length $1$ is already sorted.

Cut the whole array into pieces of length $1$.

From left to right, merge pairs of sorted pieces of length $1$, giving a series of sorted pieces of length $\le 2$;

From left to right, merge pairs of sorted pieces of length $\le 2$, giving a series of sorted pieces of length $\le 4$;

From left to right, merge pairs of sorted pieces of length $\le 4$, giving a series of sorted pieces of length $\le 8$;

...

Repeat until only one sorted piece is left. That piece is the original array, sorted.

???+ note "Why $\le$ and not $=$"
    The length of the array is probably not a power $2^x$. In that case, an incomplete piece may appear at the end, and the last piece may be left on its own without a partner.

#### Implementation

=== "C/C++"
    ```cpp
    --8<-- "docs/basic/code/merge-sort/merge-sort_1.cpp:iterative"
    ```

=== "Python"
    ```python
    --8<-- "docs/basic/code/merge-sort/merge-sort_1.py:iterative"
    ```

## Inversions

Related reading and reference implementation: [Inversions](../math/permutation.md#inversion-number)

An inversion is an ordered pair $(i, j)$ with $i < j$ and $a_i > a_j$.

A sorted array has no inversions. In the merge step of merge sort, each time the first element of the back part is taken out as the current minimum, the number of elements left in the front part is exactly the number of inversions removed by that step. So counting inversions with merge sort takes $\Theta (n \log n)$ time. Inversions can also be counted with a Fenwick tree or a segment tree, also in $O(n \log n)$ time; see the corresponding part of [Fenwick tree](../ds/fenwick.md#global-inversions-global-2d-partial-order) for a detailed explanation. Reference implementations of both algorithms are in the [Inversions](../math/permutation.md#inversion-number) section.

## External links

-   [Merge Sort - GeeksforGeeks](https://www.geeksforgeeks.org/merge-sort/)
-   [Merge sort - Wikipedia, the free encyclopedia (Chinese)](https://zh.wikipedia.org/wiki/%E5%BD%92%E5%B9%B6%E6%8E%92%E5%BA%8F)
-   [Inversion - Wikipedia, the free encyclopedia (Chinese)](https://zh.wikipedia.org/wiki/%E9%80%86%E5%BA%8F%E5%AF%B9)
