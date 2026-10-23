This page gives a short introduction to sorting algorithms.

## Definition

A **sorting algorithm** is an algorithm that arranges a given set of data in a certain order. There are many kinds of sorting algorithms, and most of them have different properties.

## Properties

### Stability

Stability is about whether equal elements keep their relative order after sorting.

A stable algorithm keeps records with equal keys in their original relative order. That is, if a sorting algorithm is stable and there are two records $R$ and $S$ with equal keys, where $R$ comes before $S$ in the original list, then $R$ will also come before $S$ in the sorted list.

Radix sort, counting sort, insertion sort, bubble sort and merge sort are stable.

Selection sort, heap sort, quicksort and Shell sort are not stable.

### Time complexity

Main page: [Complexity](./complexity.md)

Time complexity measures how an algorithm's running time grows with the size of its input. It is usually written with $O$.

A simple way to work out the complexity is to count how many times "simple operations" are executed. Sometimes you can also just count the number of nested loops for a rough estimate.

There are best-case, average-case and worst-case time complexities. In OI contests we usually care about the worst-case time complexity, because it is a guarantee on how the algorithm performs: during judging, it will never do worse than that.

Any comparison-based algorithm that sorts $n$ distinct elements needs $\Omega(n\log n)$ comparisons in the worst case.

Of course, some sorts are not $O(n\log n)$. For example, [counting sort](./counting-sort.md) runs in $O(n+w)$ time, where $w$ is the size of the range of input values.

Below is a comparison of several sorting algorithms.

![A comparison of several sorting algorithms](images/sort-intro-1.apng)

### Space complexity

Like time complexity, space complexity describes how much memory an algorithm uses. In general, the lower the space complexity, the better the algorithm.

## External links

-   [Sorting algorithm - Wikipedia (Chinese)](https://zh.wikipedia.org/wiki/%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95)
