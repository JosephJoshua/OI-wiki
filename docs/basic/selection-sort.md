This page gives a short introduction to selection sort.

## Definition

Selection sort is a simple and intuitive sorting algorithm. On step $i$, it finds the $i$-th smallest element (that is, the smallest element in $A_{i..n}$) and swaps it with the element at position $i$ of the array.

![selection sort animate example](images/selection-sort-animate.svg)

## Properties

### Stability

Whether selection sort is stable depends on how it is implemented.

With a linked list, inserting or deleting at any position takes $O(1)$, so no swap (exchanging two elements) is needed. Each time, pick the smallest element from the unsorted part (if there are several, pick the first one) and insert it before the first element of the unsorted part. This keeps the sort stable.

An array implementation usually uses `swap` to move the smallest element into the sorted part, which keeps the number of moves low, but makes the sort unstable.

All the implementations below swap array elements, so they are all **unstable**.

### Time complexity

Selection sort takes $O(n^2)$ time in the best, average and worst cases.

## Implementation

### Pseudocode

$$
\begin{array}{ll}
1 & \textbf{Input. } \text{An array } A \text{ consisting of }n\text{ elements.} \\
2 & \textbf{Output. } A\text{ will be sorted in nondecreasing order.} \\
3 & \textbf{Method. }  \\
4 & \textbf{for } i\gets 1\textbf{ to }n-1\\
5 & \qquad \textit{ith}\gets i\\
6 & \qquad \textbf{for }j\gets i+1\textbf{ to }n\\
7 & \qquad\qquad\textbf{if }A[j]<A[\textit{ith}]\\
8 & \qquad\qquad\qquad \textit{ith}\gets j\\
9 & \qquad \text{swap }A[i]\text{ and }A[\textit{ith}]\\
\end{array}
$$

=== "C++"
    ```cpp
    --8<-- "docs/basic/code/selection-sort/selection-sort_1.cpp"
    ```

=== "Python"
    ```python
    --8<-- "docs/basic/code/selection-sort/selection-sort_1.py:core"
    ```

=== "Java"
    ```java
    // The arr array is indexed from 1
    static void selection_sort(int[] arr, int n) {
        for (int i = 1; i < n; i++) {
            int ith = i;
            for (int j = i + 1; j <= n; j++) {
                if (arr[j] < arr[ith]) {
                    ith = j;
                }
            }
            // swap
            int temp = arr[i];
            arr[i] = arr[ith];
            arr[ith] = temp;
        }
    }
    ```
