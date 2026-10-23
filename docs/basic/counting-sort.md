Prerequisite: [Prefix sums](./prefix-sum.md)

???+ warning "Note"
    This page is not about [**radix sort**](./radix-sort.md).

This page gives a short introduction to counting sort.

## Definition

Counting sort is a linear-time sorting algorithm.

## How it works

Counting sort uses an extra array $C$, where the $i$-th entry is the number of elements in the input array $A$ whose value equals $i$. It then uses $C$ to place each element of $A$ in its correct position.[^ref1]

It works in three steps:

1.  Count how many times each value appears;
2.  Compute the [prefix sums](./prefix-sum.md) of these counts;
3.  Using the prefix sums of the counts, compute the rank of each element, going from right to left.

### Why compute prefix sums

If we only need to sort plain keys and handle duplicate values, we can just rebuild the array from the counts. But to rearrange the original records stably, we use the prefix sums of the counts to find each element's output position.

By computing the prefix sum of each entry in the extra array $C$, together with the entry's own value, we can give each duplicate element a unique rank:

The value of each entry in $C$ is the number of duplicate elements with that key, and the prefix sum at that entry is the rank of the last of these duplicates.

If we place the elements by going through $A$ in reverse, the sorted array clearly keeps the original order of $A$ among equal keys. In other words, we get a stable sorting algorithm.

![counting sort animate example](images/counting-sort-animate.svg)

## Properties

### Stability

Counting sort is a stable sorting algorithm.

### Time complexity

The time complexity of counting sort is $O(n+w)$, where $w$ is the size of the value range of the data being sorted.

## Implementation

### Pseudocode

$$
\begin{array}{ll}
1 & \textbf{Input. } \text{An array } A \text{ consisting of }n\text{ positive integers no greater than } w. \\
2 & \textbf{Output. } \text{Array }A\text{ after sorting in nondecreasing order stably.} \\
3 & \textbf{Method. }  \\
4 & \textbf{for }i\gets0\textbf{ to }w\\
5 & \qquad \textit{cnt}[i]\gets0\\
6 & \textbf{for }i\gets1\textbf{ to }n\\
7 & \qquad \textit{cnt}[A[i]]\gets\textit{cnt}[A[i]]+1\\
8 & \textbf{for }i\gets1\textbf{ to }w\\
9 & \qquad \textit{cnt}[i]\gets \textit{cnt}[i]+\textit{cnt}[i-1]\\
10 & \textbf{for }i\gets n\textbf{ downto }1\\
11 & \qquad B[\textit{cnt}[A[i]]]\gets A[i]\\
12 & \qquad \textit{cnt}[A[i]]\gets \textit{cnt}[A[i]]-1\\
13 & \textbf{return } B
\end{array}
$$

=== "C++"
    ```cpp
    --8<-- "docs/basic/code/counting-sort/counting-sort_1.cpp"
    ```

=== "Python"
    ```python
    --8<-- "docs/basic/code/counting-sort/counting-sort_1.py:core"
    ```

## References and notes

[^ref1]: [Counting sort - Wikipedia, the free encyclopedia (Chinese)](https://zh.wikipedia.org/wiki/%E8%AE%A1%E6%95%B0%E6%8E%92%E5%BA%8F)
