This page gives a short introduction to bucket sort.

## Definition

Bucket sort is a sorting algorithm. It works well when the values to be sorted span a large range but are spread out fairly evenly.

## How it works

Bucket sort follows these steps:

1.  Set up an array of a fixed size to act as empty buckets;
2.  Go through the sequence and put each element into its matching bucket;
3.  Sort every bucket that is not empty;
4.  Take the elements out of the non-empty buckets and put them back into the original sequence.

## Properties

### Stability

If the inner sort is stable, and putting elements into buckets does not change their relative order, then bucket sort is a stable sorting algorithm.

Since each bucket holds only a few elements, insertion sort is usually used for the inner sort. In that case, bucket sort is stable.

### Time complexity

Let $n$ be the number of elements and $k$ the number of buckets. If the elements fall into buckets independently and uniformly, the average time complexity of bucket sort is $O(n + n^2/k + k)$ (splitting the value range evenly into $k$ blocks + sorting + merging the elements back). When $k\approx n$, this is $O(n)$.[^ref1]

The worst-case time complexity of bucket sort is $O(n^2+k)$.

## Implementation

In the code below, `a[]` is indexed from $1$. It requires $0\le a_i\le w$ and $0\le n<N$, where $w$ is an upper bound on the largest key.

=== "C++"
    ```cpp
    --8<-- "docs/basic/code/bucket-sort/bucket-sort_1.cpp:sort"
    ```

=== "Python"
    ```python
    --8<-- "docs/basic/code/bucket-sort/bucket-sort_1.py:sort"
    ```

## References and notes

[^ref1]: [Bucket sort - Wikipedia](https://en.wikipedia.org/wiki/Bucket_sort#Average-case_analysis)
