author: Link-cute, Xeonacid, ouuan, Alphnia, Lyccrius

## Introduction

Before learning about monotonic queues, let us look at an example problem.

???+ note "Example problem"
    [Sliding Window](http://poj.org/problem?id=2823)
    
    In short: given an array of length $n$, output the maximum and minimum of every $k$ consecutive numbers.

The brute-force idea is simple: for each segment $i \sim i+k-1$, compare the numbers one by one to find the maximum (and minimum). The time complexity is about $O(n \times k)$.

Clearly this does a lot of repeated work. Except for the first $k-1$ and the last $k-1$ numbers, every number is compared $k$ times. In this problem $100\%$ of the test data has $n \le 1000000$, so when $k$ is somewhat large, this will obviously get TLE.

This is where the monotonic queue comes in.

## Definition

As the name suggests, a monotonic queue has two key parts: "monotonic" and "queue".

"Monotonic" describes the "pattern" of the elements: increasing (or decreasing).

"Queue" means elements can only be operated on at the front and the back.

P.S. The "queue" in a monotonic queue is somewhat different from an ordinary queue; we will come back to this later

## Example analysis

### Explanation

With the idea of a "monotonic queue" above, it is natural to think of using one to speed things up.

We want the maximum (minimum) of every $k$ consecutive numbers. Clearly, when a number enters the range in which we "look for" the maximum, if it is larger than a number before it (one that entered the queue earlier), then that earlier number will leave the queue before this one and can never be the maximum again.

In other words, when this condition holds, we can "pop" the earlier numbers and then actually push the new number onto the back of the queue.

This amounts to maintaining a decreasing queue, which fits the definition of a monotonic queue and cuts down repeated comparisons. Moreover, since the queue only holds elements inside the query range and is decreasing, the front of the queue must be the maximum of that range. So we only need to output the front of the queue.

Clearly, in this algorithm every number enters and leaves the queue at most once, so the time complexity drops to $O(n)$.

Since the query range has a fixed length, a value outside the range cannot be output no matter how large it is. So we also need a `site` array that records the position in the original array of the $i$-th number in the queue, so that we can pop a front element that has gone out of range.

### Process

For example, building a monotonically increasing queue goes like this:

The original sequence is:

```text
1 3 -1 -3 5 3 6 7
```

Because we must always keep the queue **increasing**, the following happens: (assume $k = 3$)

| Operation | Queue state |
| --- | --- |
| Push 1 | `{1}` |
| 3 is larger than 1, push 3 | `{1 3}` |
| -1 is smaller than every element in the queue, so clear the queue and push -1 | `{-1}` |
| -3 is smaller than every element in the queue, so clear the queue and push -3 | `{-3}` |
| 5 is larger than -3, push it directly | `{-3 5}` |
| 3 is smaller than 5, pop 5, push 3 | `{-3 3}` |
| -3 is now outside the window, so pop -3; 6 is larger than 3, push 6 | `{3 6}` |
| 7 is larger than 6, push 7 | `{3 6 7}` |

???+ note "Reference code for the example problem"
    ```cpp
    --8<-- "docs/ds/code/monotonic-queue/monotonic-queue_1.cpp"
    ```

P.S. One big difference between this "queue" and an ordinary queue is that we can also operate on its back. The STL has a similar data structure, deque.

???+ note "Example problem 2 [Luogu P2698 Flowerpot S](https://www.luogu.com.cn/problem/P2698)"
    You are given the coordinates of $N$ water drops. $y$ is the height of a drop, and $x$ is where it lands on the $x$-axis. Each drop falls at 1 unit of length per second. You need to place a flowerpot somewhere on the $x$-axis so that the time between the first drop it catches and the last drop it catches is at least $D$.
    A drop counts as caught as soon as it lands on the $x$-axis within the pot's edges (landing exactly on an edge also counts). Given the coordinates of the $N$ drops and the value of $D$, find the minimum width $W$ of the flowerpot. $1\leq N \leq 100000 , 1 \leq D \leq 1000000, 0 \leq x,y\leq 10^6$

After sorting all drops by $x$-coordinate, the problem becomes: find a range with the smallest difference in $x$-coordinates such that the difference between the maximum and minimum $y$-coordinates in it is at least $D$. This problem is similar to the previous example, since both involve the maximum and minimum of a range. But here the size of the range is not fixed, and the range size itself is the answer we want.

We can still use two monotonic queues, one increasing and one decreasing, to maintain the maximum and minimum of $[L,R]$ as $R$ keeps moving right. Now notice that if $L$ is fixed, the maximum of $[L,R]$ can only grow and the minimum can only shrink. Let $f(R) = \max[L,R]-\min[L,R]$. Then $f(R)$ is an increasing function of $R$, so $f(R)\geq D \implies f(r)\geq D,R\lt r \leq N$. This means that for each fixed $L$, the first $R$ to the right that satisfies the condition is the best answer.
So the whole process is: first fix $L$ and move $R$ from left to right, using two monotonic queues to maintain the extreme values of $[L,R]$. When we find the first $R$ that satisfies the condition, update the answer and move $L$ to the right as well. As $L$ moves right, both monotonic queues must pop their fronts in time. This continues until $R$ reaches the end. Each element still enters and leaves each queue once, which guarantees $O(n)$ time complexity.

???+ note "Reference code"
    ```cpp
    --8<-- "docs/ds/code/monotonic-queue/monotonic-queue_2.cpp"
    ```
