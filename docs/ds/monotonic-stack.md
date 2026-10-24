## Introduction

What is a monotonic stack? As the name suggests, a monotonic stack is a stack whose elements are monotonic. Compared with a monotonic queue, elements enter and leave it at only one end.

For convenience, the examples and pseudocode below maintain a monotonically increasing stack of integers.

## Process

### Insertion

When inserting an element into a monotonic stack, to keep the stack monotonic, we pop as few elements as possible such that the whole stack is still monotonic after the new element is pushed on top.

For example, suppose the elements in the stack from top to bottom are $\{0,11,45,81\}$.

![](images/monotonic-stack-before.svg)

To insert $14$ while keeping the stack monotonic, we must pop the elements $0,11$ in order. After that, the stack becomes $\{14,45,81\}$.

![](images/monotonic-stack-after.svg)

In pseudocode:

???+ note "Implementation"
    ```text
    insert x
    while !sta.empty() && sta.top()<x
        sta.pop()
    sta.push(x)
    ```

### Usage

We simply read an element from the top of the stack. This element is at one end of the monotonic order.

For instance, in the example above it is the minimum value in the stack.

## Applications

??? note "[POJ3250 Bad Hair Day](http://poj.org/problem?id=3250)"
    $N$ cows stand in a row from left to right, and each cow has a height $h_i$. Let $c_i$ be the number of cows between the $i$-th cow from the left and "the first cow to its right with height $≥h_i$". Find $\sum_{i=1}^{N} c_i$.

A basic application is this problem, which is just a simple use of a monotonic stack. Record the position where each cow gets popped; if a cow is never popped, use the far end. With a little extra processing you get the required result.

A monotonic stack can also be used to solve the RMQ problem offline.

We sort all queries by their right endpoint. Then we scan the sequence from left to right up to the right endpoint of the current query, inserting each scanned element into the monotonic stack. This way, whenever we answer a query, the stack holds the candidate positions $\le r$ that could be the answer, and these elements are monotonic. The first element in the stack at a position $\ge l$ is the answer to the current query, and we can find it with binary search. Solving RMQ with a monotonic stack takes $O(q\log q + q\log n)$ time and $O(n)$ space.

## Exercises

-   [Luogu P5788 [Template] Monotonic Stack](https://www.luogu.com.cn/problem/P5788)
-   [Luogu P1901 Transmitting Stations](https://www.luogu.com.cn/problem/P1901)
