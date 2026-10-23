This page gives a short introduction to bubble sort.

## Definition

Bubble sort is a simple sorting algorithm. It gets its name from the way smaller elements slowly "float" to the top of the list, like bubbles rising in water, as the algorithm runs.

## How it works

Bubble sort repeatedly looks at each pair of neighboring elements. If the two are in the wrong order, it swaps them. Once a full pass finds no pair that needs swapping, the list is sorted.

After $i$ passes, the last $i$ positions are guaranteed to hold the $i$ largest elements in their final places. So $n-1$ passes are always enough to sort the array.

## Properties

### Stability

Bubble sort is stable: equal elements keep their original relative order.

### Time complexity

If the list is already sorted, bubble sort makes just one pass over the array and performs no swaps, so it runs in $O(n)$ time.

In the worst case, bubble sort performs $\dfrac{(n-1)n}{2}$ swaps, giving $O(n^2)$ time.

On average, bubble sort also takes $O(n^2)$ time.

## Implementation

### Pseudocode

$$
\begin{array}{ll}
1 & \textbf{Input. } \text{An array } A \text{ consisting of }n\text{ elements.} \\
2 & \textbf{Output. } A\text{ will be sorted in nondecreasing order stably.} \\
3 & \textbf{Method. }  \\
4 & \textit{flag}\gets \mathrm{True}\\
5 & \textbf{while }\textit{flag}\\
6 & \qquad \textit{flag}\gets \mathrm{False}\\
7 & \qquad\textbf{for }i\gets1\textbf{ to }n-1\\
8 & \qquad\qquad\textbf{if }A[i]>A[i + 1]\\
9 & \qquad\qquad\qquad \textit{flag}\gets \mathrm{True}\\
10 & \qquad\qquad\qquad \text{Swap } A[i]\text{ and }A[i + 1]
\end{array}
$$

=== "C++"
    ```cpp
    --8<-- "docs/basic/code/bubble-sort/bubble-sort_1.cpp"
    ```

=== "Python"
    ```python
    --8<-- "docs/basic/code/bubble-sort/bubble-sort_1.py:core"
    ```

=== "Java"
    ```java
    // Assumes the array has size n + 1; sorting starts at index 1
    static void bubble_sort(int[] a, int n) {
        boolean flag = true;
        while (flag) {
            flag = false;
            for (int i = 1; i < n; i++) {
                if (a[i] > a[i + 1]) {
                    flag = true;
                    int t = a[i];
                    a[i] = a[i + 1];
                    a[i + 1] = t;
                }
            }
        }
    }
    ```
