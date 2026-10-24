author: HeRaNO, Xeonacid, AzurIce

## Structure

Let's start with the structure of a binary heap. It is a binary tree, and in fact a complete binary tree. Each node stores one element (in other words, a weight).

Heap property: the weight of a parent is not less than the weights of its children (a max-heap). In the same way we can define a min-heap. This article uses a max-heap as the example.

By the heap property, the root stores the maximum value (so the getmax operation is solved).

## Process

### Insertion

Insertion means adding an element to the binary heap, and the tree must still be a complete binary tree afterwards.

The simplest way is to insert after the rightmost leaf on the bottom level.

If the bottom level is full, start a new level.

But after insertion, the heap property may no longer hold.

**Sift up**: if the weight of this node is greater than the weight of its parent, swap them. Repeat until this no longer holds or we reach the root.

It can be shown that after inserting and sifting up, no other node violates the heap property.

Sifting up takes $O(\log n)$ time.

![Insertion into a binary heap](./images/binary_heap_insert.svg)

### Deletion

Deletion means removing the largest element of the heap, that is, removing the root.

But if we just remove it, we are left with two heaps, which is hard to deal with.

So let's think about doing insertion in reverse: try to move the root to the position of the last node, then simply delete it.

That is not easy to do directly, so the usual approach is to swap the root with the last node.

Then we simply delete the root (now at the last node's position). But the new root may violate the heap property...

**Sift down**: among the children of this node, pick the largest one and swap it with this node. Repeat until we reach the bottom.

It can be shown that after deleting and sifting down, no other node violates the heap property.

The time complexity is $O(\log n)$.

### Increasing the weight of a node

Clearly, after changing the value directly, one sift-up is enough. The time complexity is $O(\log n)$.

## Implementation

Notice that the operations above mainly rely on two core steps: sift up and sift down.

We use a sequence $h$ to represent the heap. The two children of $h_i$ are $h_{2i}$ and $h_{2i+1}$, and $1$ is the root:

![The heap structure of h](./images/binary-heap-array.svg)

Reference code:

```cpp
void up(int x) {
  while (x > 1 && h[x] > h[x / 2]) {
    std::swap(h[x], h[x / 2]);
    x /= 2;
  }
}

void down(int x) {
  while (x * 2 <= n) {
    t = x * 2;
    if (t + 1 <= n && h[t + 1] > h[t]) t++;
    if (h[t] <= h[x]) break;
    std::swap(h[x], h[t]);
    x = t;
  }
}
```

### Building a heap

Consider this problem: starting from an empty heap, insert $n$ elements, in any order.

Inserting them one by one takes $O(n \log n)$ time. Is there a better way?

#### Method 1: sift up

Start from the root and go in BFS order.

```cpp
void build_heap_1() {
  for (i = 1; i <= n; i++) up(i);
}
```

This is still the same as inserting one by one; the elements are just placed in the array beforehand, which improves the constant factor. So in the worst case, the running time satisfies the recurrence $T(n) = T(n - 1) + \Theta(\log n)$, and summing up gives $T(n) = \Theta(n \log n)$.

#### Method 2: sift down

Now try a different idea: start from the leaves and sift down each node one by one.

```cpp
void build_heap_2() {
  for (i = n; i >= 1; i--) down(i);
}
```

Another way to see it: each step "merges" two heaps that are already valid. This shows that the method is correct.

Note that leaves do not need to be adjusted, so we can start from about position $n/2$ of the sequence, which improves the constant factor. Thinking of each step as merging two heaps, we get the recurrence $T(n) = 2T(\dfrac{n}{2}) + O(\log n)$ for the running time, and the master theorem gives $T(n) = \Theta(n)$.

We can build a heap in $\Theta(n)$ because the heap property is weak: a binary heap for a given set of elements is not unique.

With a strong condition like being sorted, it would be a different story.

## Applications

### Two-heap technique

??? note "[SPOJ RMID2 - Running Median Again](https://www.spoj.com/problems/RMID2/)"
    Maintain a sequence that supports two operations:
    
    1.  Insert an element into the sequence
    2.  Print and delete the median of the current sequence (if the length is even, print the smaller median)

This problem can be generalized to: dynamically maintain the $k$-th largest number in a sequence, where the value of $k$ may change.

For problems like this, we can use the **two-heap technique** (it saves the trouble of writing a value segment tree or a BST).

The two-heap structure consists of a max-heap and a min-heap. The min-heap holds the large values, that is, the top $k$ values (including the $k$-th). The max-heap holds the small values, that is, the numbers smaller than the $k$-th largest.

Together, the two heaps support the following operations:

-   Rebalance: while the min-heap has fewer than $k$ elements, keep moving the top of the max-heap into the min-heap until the min-heap has exactly $k$ elements; while the min-heap has more than $k$ elements, keep moving the top of the min-heap into the max-heap until the min-heap has exactly $k$ elements;
-   Insert an element: if the new element is greater than or equal to the top of the min-heap, insert it into the min-heap, otherwise insert it into the max-heap; then rebalance;
-   Query the $k$-th largest element: it is the top of the min-heap;
-   Delete the $k$-th largest element: delete the top of the min-heap, then rebalance;
-   Change $k$ by $+1/-1$: rebalance according to the new value of $k$.

Clearly, querying the $k$-th largest element takes $O(1)$ time. After an insertion, a deletion or a change of $k$, the size of the min-heap differs from the desired $k$ by at most $1$, so each rebalance moves at most one element between the max-heap and the min-heap. Therefore, all these operations take $O(\log n)$ time.

??? note "Reference code"
    ```cpp
    --8<-- "docs/ds/code/binary-heap/binary-heap_1.cpp"
    ```

### Exercises

-   [SPOJ RMID - Running Median](https://www.spoj.com/problems/RMID)
-   [Luogu P1801 Black Box](https://www.luogu.com.cn/problem/P1801)
