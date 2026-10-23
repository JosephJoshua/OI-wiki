Prerequisites: [Time complexity](./complexity.md)

This page introduces the basics of amortized complexity.

## Introduction

Amortized analysis is a technique for analyzing the performance of algorithms and dynamic data structures. Instead of looking only at the cost of a single operation, it looks at the average cost over a whole sequence of operations, which gives a more accurate picture of overall performance. Amortized analysis does not involve probability. It only guarantees the average time per operation in the worst case; it does not tell you the average-case performance of the system. In the worst case, amortized analysis spreads the cost of expensive operations over the cheap ones, showing that the average cost per operation stays within a reasonable bound.

There are three main methods of amortized analysis: aggregate analysis, the accounting method, and the potential method. Each has its own focus and suits different situations, but they share the same goal: by balancing out the costs of operations, they show how well a data structure performs overall in the worst case.

## Content

Consider a growable array, such as `vector` in C++, with an initial capacity of $m = 1$. Each time a new element is inserted, if the array is full, we double the array's size, copy the elements from the old array into the new one, and then insert the new element.

Next, we use insertion into this dynamic array as an example and analyze its amortized cost with each of the three methods: aggregate analysis, the accounting method, and the potential method.

### Aggregate analysis

Aggregate analysis computes the total cost of a sequence of operations and divides it evenly among the operations, which gives the amortized time complexity of each operation.

For the dynamic array, we first identify the two key costs of an insertion:

-   If the array is not full, an insertion costs $O(1)$.
-   If the array is full, the insertion has to grow the array, and copying the elements after growing costs $O(m)$, where $m$ is the current size of the array.

So to compute the total cost of $n$ insertions, we can split it into two parts:

1.  **Cost of inserting**: the direct cost of inserting each new element is constant time $O(1)$, so for $n$ operations the total is $O(n)$;
2.  **Cost of growing the array**: each time the array grows, the elements of the old array are copied into the new one. This happens when the array size is a power of $2$. The old capacities copied during growth add up to the sum of all powers of two strictly less than $n$. For $n\ge1$, the total copying cost is $\sum_{i=0}^{\lceil\log_2 n\rceil - 1}2^i=2^{\lceil\log_2 n\rceil}-1<2n$, so the total is $O(n)$.

Therefore, the total cost of all insertions is $O(n)$, and the amortized cost per operation is $O(1)$. Even in the worst case, the average cost of an insertion is still constant time.

### Accounting method

The accounting method assigns each operation a fixed amortized cost up front, and makes sure the total actual cost of all operations never exceeds the sum of these assigned costs. It works like **paying in advance**: cheap operations save up part of their charge to pay for expensive operations later.

For the dynamic array, we can give each insertion a fixed amortized cost, so that enough has been saved up by the time the array needs to grow.

1.  **Assigning charges**:
    -   Suppose the actual cost of each insertion is $1$, and we set its amortized cost to $3$.
    -   Of this, $1$ pays for the current insertion, and $2$ is saved for a possible future growth.

2.  **Using the savings**:
    -   When the array is full, it has to grow, with an actual cost of $O(m)$, where $m$ is the current size of the array.
    -   Suppose the array holds $n$ elements before growing. The $n/2$ elements in the second half of the array together saved $n$ units of amortized cost when they were inserted, which is exactly enough to pay for the growth.

Here is a concrete example:

```text
Initial state:
arr    = [1, 2, 3, 4]  // initial array
amount = [2, 2, 2, 2]  // savings stored by each element

// First growth: the array is full and needs to grow
arr    = [1, 2, 3, 4, null, null, null, null]  // array after growing
amount = [2, 2, 0, 0, 0, 0, 0, 0]  // the savings of 3 and 4 pay for the growth

// Keep inserting new elements until the array is full again
arr    = [1, 2, 3, 4, 5, 6, 7, 8]  // keep filling the array
amount = [2, 2, 0, 0, 2, 2, 2, 2]  // newly inserted elements also store savings

// Second growth: the array is full again and needs more space
arr    = [1, 2, 3, 4, 5, 6, 7, 8, null, null, null, null, null, null, null, null]  // array after growing
amount = [2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]  // the savings of 5, 6, 7, 8 pay for the growth
```

This shows that the amortized cost saved by each insertion is enough to pay for future growth, so the amortized cost of each operation stays at $O(1)$.

### Potential method

The potential method defines a potential function (usually written $\Phi$) that measures the **potential energy** of a data structure, that is, resources stored up in the state of the system that can pay for expensive operations later. Changes in potential are used to balance the total cost of a sequence of operations, keeping the amortized cost of the whole algorithm within a reasonable bound.

#### Principle

First, define a **state** $S$ as the state of the data structure at some moment. It may include the number of elements, the capacity, pointers, and so on. The initial state $S_0$ is the state before any operation is performed.

Next, define a potential function $\Phi(S)$ that measures the potential of state $S$. With initial state $S_0$, every reachable state $S$ must satisfy $\Phi(S) \geq \Phi(S_0)$[^clemson][^uci][^stanford]. Some sources also require $\Phi(S_0)=0$[^cornell], but this is actually unnecessary.

For each operation, its amortized cost $\hat{c}$ is defined as:

$$
\hat{c} = c + \Phi(S') - \Phi(S)
$$

Here $c$ is the actual cost of the operation, and $S$ and $S'$ are the states of the data structure before and after the operation. The formula says that the amortized cost equals the actual cost plus the change in potential. If the operation increases the potential (that is, $\Phi(S') > \Phi(S)$), the amortized cost goes up; if the operation uses up potential (that is, $\Phi(S') < \Phi(S)$), the amortized cost goes down.

We can use the potential function to analyze the total cost of a sequence of operations. Let $S_1, S_2, \dots, S_m$ be the sequence of states produced by $m$ operations starting from the initial state $S_0$, and let $c_i$ be the actual cost of the $i$-th operation. Then the amortized cost $p_i$ of the $i$-th operation is:

$$
p_i = c_i + \Phi(S_i) - \Phi(S_{i-1})
$$

So the total time spent on $m$ operations is:

$$
\sum_{i=1}^m c_i = \sum_{i=1}^m p_i + \Phi(S_0) - \Phi(S_m)
$$

Since $\Phi(S) \geq \Phi(S_0)$, the total time has the upper bound:

$$
\sum_{i=1}^m p_i \geq \sum_{i=1}^m c_i
$$

Therefore, if $p_i = O(T(n))$, then $O(T(n))$ is an upper bound on the amortized complexity.

#### Example: analyzing growth of a dynamic array

Take insertion into the dynamic array `vector` as an example. Let the initial state be $h_0$, and define the potential function $\Phi(h)$ as:

$$
\Phi(h) = 2n - m
$$

Here $n$ is the number of elements in the array and $m$ is its current capacity. Changes in this potential function reflect the savings stored up to pay for future growth going up and down. In the initial state, an empty array with capacity $1$, $\Phi(h_0)=-1$. In every non-empty state reachable by only inserting and doubling when full, $m\leq 2n$, so $\Phi(h)\geq 0>\Phi(h_0)$.

1.  **Insertion (no growth needed)**:
    -   **Actual cost**: $O(1)$, since only one element is inserted.
    -   **Change in potential**: after the insertion, the number of elements goes up by 1, so the potential goes up by $2$.
        -   $\Phi(h') - \Phi(h) = 2(n + 1) - m - (2n - m) = 2$.
    -   **Amortized cost**: $1 + 2 = 3$.

2.  **Insertion (triggers growth)**:
    -   Suppose the current capacity is $m = n$. Inserting a new element triggers growth, and the new capacity becomes $2n$.
    -   **Actual cost**: $O(n)$, since all elements must be copied into the new array and then the new element is inserted.
    -   **Change in potential**: after growing and inserting, the potential changes by $2-n$, which is a decrease only when $n>2$.
        -   $\Phi(h') - \Phi(h) = 2(n + 1) - 2n - (2n - n) = 2 - n$.
    -   **Amortized cost**: $n + 1 + (2 - n) = 3$.

From this analysis we can see that even though growing the array has a high actual cost, thanks to the choice of potential function, the overall amortized cost still stays constant, $O(1)$.

## Further example: stack operations

Stack operations are a classic application of amortized analysis. Suppose we start from an empty stack and `pop` is only used on a non-empty stack. The stack `S` supports the following three operations:

| Operation        | Description                                | Actual cost $c_i$           |
| ---------------- | ------------------------------------------ | --------------------------- |
| `S.push(x)`      | Push element $x$ onto the stack            | $1$                         |
| `S.pop()`        | Pop the top element                        | $1$                         |
| `S.multi-pop(k)` | Pop at most $k$ elements from the top      | $O(\min(\lvert S\rvert,k))$ |

We will analyze the amortized cost of these stack operations with the three methods: aggregate analysis, the accounting method, and the potential method.

### Aggregate analysis

Aggregate analysis computes the total cost of all operations and divides it evenly among them to get the amortized cost.

1.  For $n_{\text{push}}$ `push(x)` operations, each costs $O(1)$, so the total cost is $O(n_{\text{push}})$;
2.  For $n_{\text{pop}}$ `pop()` operations, each costs $O(1)$, so the total cost is $O(n_{\text{pop}})$;
3.  For $n_{\text{multi-pop}}$ `multi-pop(k)` operations, even though each one actually costs $O(\min(\lvert S \rvert, k))$, the number of elements they pop can never exceed the number of elements pushed earlier by `push(x)`, so their total cost is still bounded by $n_{\text{push}}$.

The total number of operations is $n=n_{\text{push}}+n_{\text{pop}}+n_{\text{multi-pop}}$, and $n_{\text{push}}\le n$. Each element is pushed at most once and popped at most once, so the total cost, charged per element, is $O(n_{\text{push}})=O(n)$. Even if we also count a constant checking cost for each call, the total cost is still $O(n)$, and the amortized cost is $O(1)$.

### Accounting method

The accounting method sets aside part of the charge for each `push(x)` operation to pay for a possible future `pop()` or `multi-pop(k)` operation.

1.  **`S.push(x)`**: suppose each `push(x)` has an amortized cost of $2$. $1$ unit pays for the current operation, and the other $1$ unit is saved to pay for a future `pop()` or `multi-pop(k)`;
2.  **`S.pop()`**: the actual cost is $1$, but since the earlier `push(x)` already saved $1$ unit for it, its amortized cost is $0$;
3.  **`S.multi-pop(k)`**: each popped element has an actual cost of $1$, which can be paid with the savings from that element's earlier `push(x)`, so the amortized cost is $0$.

From this analysis, the savings stored by each push are enough to pay for popping that element later, so the amortized cost of each operation is $O(1)$.

### Potential method

The potential method defines a potential function that measures the state of the stack, and uses changes in potential to balance the costs of operations.

1.  **Potential function**: let $\Phi(h)$ be the number of elements in the stack, that is, $\Phi(h) = \lvert S \rvert$. Each element contributes $1$ unit of potential;
2.  **`S.push(x)`**: each `push(x)` adds an element to the stack, raising the potential by $1$, so its amortized cost is $1 + 1 = 2$;
3.  **`S.pop()`**: each `pop()` removes an element from the stack, lowering the potential by $1$, so its amortized cost is $1 - 1 = 0$;
4.  **`S.multi-pop(k)`**: let $t=\min(\lvert S\rvert,k)$. `multi-pop(k)` actually pops $t$ elements, lowering the potential by $t$, so the amortized cost charged per element is $t-t=0$; counting the call overhead, it is $O(1)$.

With this potential function, `push(x)` has an amortized cost of $2$, while `pop()` and `multi-pop(k)` have an amortized cost of $0$. So every stack operation has an amortized cost of $O(1)$.

## References and notes

-   [Amortized Analysis - Wikipedia](https://en.wikipedia.org/wiki/Amortized_analysis)

[^clemson]: [Clemson University - Amortized Analysis + Splay Trees](https://people.computing.clemson.edu/~srimani/8380_F22/Course_Materials_Web/5_F22_Amortized%20Analysis%2BSplay%20Trees.pdf#page=8)

[^uci]: [UC Irvine - Amortized Analysis](https://ics.uci.edu/~goodrich/teach/cs263/notes/02-Amortized.pdf#page=5)

[^stanford]: [Stanford CS166 - Amortized Analysis](https://web.stanford.edu/class/archive/cs/cs166/cs166.1206/lectures/07/Small07.pdf#page=69)

[^cornell]: [Cornell CS 3110 - Lecture 20: Amortized Analysis](https://www.cs.cornell.edu/courses/cs3110/2011sp/Lectures/lec20-amortized/amortized.htm)
