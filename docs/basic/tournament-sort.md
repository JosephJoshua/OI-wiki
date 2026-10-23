This page gives a short introduction to tournament sort.

## Definition

Tournament sort, also called tree selection sort, is an optimized version of [selection sort](./selection-sort.md) and a variant of [heap sort](./heap-sort.md) (both use a complete binary tree). It builds on selection sort by using a priority queue to find the next element to select.

## Introduction

Tournament sort gets its name from single-elimination tournaments. In such a tournament, many players compete in pairs, and each winner moves on to the next round. This format finds the best player, but the player who loses in the final round is not necessarily the second best: they may be weaker than someone who was knocked out earlier.

## How it works

Take a **min tournament tree** as an example:

![tournament-sort1](./images/tournament-sort1.svg)

The elements to be sorted are the ones shown at the leaves. The red edges show the path of the smaller element winning each comparison. Clearly, one "tournament" picks out the smallest element of a group.

In each round, comparing $n$ elements produces $\left\lceil\dfrac{n}{2}\right\rceil$ "winners": the smaller element of each pair moves on to the next round. If an element has no partner, it moves on to the next round directly.

![tournament-sort2](./images/tournament-sort2.svg)

After a "tournament" is finished, the chosen element must be removed. We simply set it to $\infty$ (similar to what [heap sort](./heap-sort.md) does), then hold another "tournament" to pick the next smallest element.

Repeat this until all elements are in order.

## Properties

### Stability

Tournament sort is not stable.

### Time complexity

Tournament sort takes $O(n\log n)$ time in the best, average and worst cases. It spends $O(n)$ time setting up the "tournament", and then $O(\log n)$ time to select each of the $n$ elements.

### Space complexity

Tournament sort uses $O(n)$ space.

## Implementation

=== "C++"
    ```cpp
    --8<-- "docs/basic/code/tournament-sort/tournament-sort_1.cpp:sort"
    ```

=== "Python"
    ```python
    --8<-- "docs/basic/code/tournament-sort/tournament-sort_1.py:sort"
    ```

## External links

-   [Tournament sort - Wikipedia](https://en.wikipedia.org/wiki/Tournament_sort)
