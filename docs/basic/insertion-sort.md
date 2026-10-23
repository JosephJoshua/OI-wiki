This page gives a short introduction to insertion sort.

## Definition

Insertion sort is a simple and intuitive sorting algorithm. It works by splitting the elements into two parts, "sorted" and "unsorted". Each step takes one element from the "unsorted" part and inserts it into its correct position in the "sorted" part.

It works the same way as picking up playing cards: you take one card from the table, insert it into your hand according to its value, then take the next card.

![insertion sort animate example](images/insertion-sort-animate.svg)

## Properties

### Stability

Insertion sort is a stable sorting algorithm.

### Time complexity

The best-case time complexity of insertion sort is $O(n)$. It is very efficient when the array is almost sorted.

Both the worst-case and the average time complexity of insertion sort are $O(n^2)$.

## Implementation

### Pseudocode

$$
\begin{array}{ll}
1 & \textbf{Input. } \text{An array } A \text{ consisting of }n\text{ elements.} \\
2 & \textbf{Output. } A\text{ will be sorted in nondecreasing order stably.} \\
3 & \textbf{Method. }  \\
4 & \textbf{for } i\gets 2\textbf{ to }n\\
5 & \qquad \textit{key}\gets A[i]\\
6 & \qquad j\gets i-1\\
7 & \qquad\textbf{while }j>0\textbf{ and }A[j]>\textit{key}\\
8 & \qquad\qquad A[j + 1]\gets A[j]\\
9 & \qquad\qquad j\gets j - 1\\
10 & \qquad A[j + 1]\gets \textit{key}
\end{array}
$$

=== "C++"
    ```cpp
    --8<-- "docs/basic/code/insertion-sort/insertion-sort_1.cpp"
    ```

=== "Python"
    ```python
    --8<-- "docs/basic/code/insertion-sort/insertion-sort_1.py:core"
    ```

=== "Java"
    ```java
    --8<-- "docs/basic/code/insertion-sort/insertion-sort_1.java"
    ```

## Binary insertion sort

Insertion sort can also be sped up with binary search. The improvement is more noticeable when there are many elements to sort.

### Time complexity

Binary insertion sort uses binary search to find the insertion position, which cuts the total number of comparisons down to $O(n\log n)$. However, in the worst case it still has to move $\Theta(n^2)$ elements, so its worst-case time complexity is still $\Theta(n^2)$.

### Implementation

=== "C++"
    ```cpp
    void insertion_sort(int arr[], int len) {
      if (len < 2) return;
      for (int i = 1; i != len; ++i) {
        int key = arr[i];
        auto index = upper_bound(arr, arr + i, key) - arr;
        // Moving elements with memmove is faster than a for loop; the time complexity is still O(n)
        memmove(arr + index + 1, arr + index, (i - index) * sizeof(int));
        arr[index] = key;
      }
    }
    ```
