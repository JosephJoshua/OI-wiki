This page gives a short introduction to heap sort.

## Definition

Heapsort is a sorting algorithm built on the [binary heap](../ds/binary-heap.md) data structure. Heap sort works on arrays.

## How it works

At its core, heap sort is selection sort done on top of a heap.

### Sorting

First, build a max-heap. Then take out the top element of the heap as the maximum, swap it with the last element of the array, and restore the heap property for the remaining heap;

Next, take out the top element of the heap as the second largest value, swap it with the second-to-last element of the array, and restore the heap property for the remaining heap;

Keep going like this. After the $(n-1)$-th step, the whole array is sorted.

### Building a binary heap on an array

Starting from the root, place the nodes of each level into the array one level after another.

Then, for the node at index `i` in the array, its parent, left child and right child are:

```cpp
iParent(i) = (i - 1) / 2;
iLeftChild(i) = 2 * i + 1;
iRightChild(i) = 2 * i + 2;
```

## Properties

### Stability

Just like selection sort, the swaps in heap sort may change the relative order of equal elements, so heap sort is not stable.

### Time complexity

The worst-case time complexity of heap sort is $O(n\log n)$.

### Space complexity

Since the heap can be built on the input array itself, heap sort is an in-place algorithm.

## Implementation

=== "C++"
    ```cpp
    --8<-- "docs/basic/code/heap-sort/heap-sort_1.cpp:sort"
    ```

=== "Python"
    ```python
    --8<-- "docs/basic/code/heap-sort/heap-sort_1.py:sort"
    ```

## External links

-   [Heapsort - Wikipedia (Chinese)](https://zh.wikipedia.org/wiki/%E5%A0%86%E6%8E%92%E5%BA%8F)
