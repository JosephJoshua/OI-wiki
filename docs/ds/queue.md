This page introduces queue-related data structures and their applications.

![](./images/queue.svg)

## Introduction

A queue is a list with the property that "elements that enter the queue first must leave it first". Because of this, a queue is also called a first in first out list, or FIFO list for short.

## Implementation

### Simulating a queue with an array

We usually simulate a queue with an array, using two variables to mark its front and back.

```cpp
int q[SIZE], ql = 1, qr;
```

The code for the queue operations is as follows:

-   Insert an element: `q[++qr] = x;`
-   Remove an element: `ql++;`
-   Access the front: `q[ql]`
-   Access the back: `q[qr]`
-   Clear the queue: `ql = 1; qr = 0;`

??? example "[Luogu B3616 [Template] Queue](https://www.luogu.com.cn/problem/B3616) reference implementation with an array"
    ```cpp
    --8<-- "docs/ds/code/queue/queue_1.cpp"
    ```

### Simulating a queue with two stacks

Another, less common, method is to simulate a queue with two [stacks](./stack.md).

This method uses two stacks $F$ and $S$ to simulate a queue, where $F$ is the stack for the back of the queue and $S$ is the stack for the front. It supports push (insert at the back) and pop (remove from the front):

-   push: push onto stack $F$.
-   pop: if $S$ is not empty, pop from $S$. Otherwise, move the elements of $F$ onto $S$ in reverse (really just popping them one by one and pushing them, which leaves them in reversed order), and then pop from $S$.

It is easy to prove that each element is pushed, moved and popped only once, so the amortized complexity is $O(1)$.

??? example "[Luogu B3616 [Template] Queue](https://www.luogu.com.cn/problem/B3616) reference implementation with two stacks"
    ```cpp
    --8<-- "docs/ds/code/queue/queue_2.cpp"
    ```

## Queues in the C++ STL

C++ provides the container `std::queue` in the STL. You need to include the `<queue>` header before using it.

???+ info "Definition of `queue` in the STL"
    ```cpp
    // clang-format off
    template<
        class T,
        class Container = std::deque<T>
    > class queue;
    ```
    
    `T` is the type of data stored in the queue.
    
    `Container` is the type of the underlying container that stores the elements. It must provide the following functions with the usual semantics:
    
    -   `back()`
    -   `front()`
    -   `push_back()`
    -   `pop_front()`
    
    The STL containers `std::deque` and `std::list` meet these requirements. If you do not specify one, `std::deque` is used as the underlying container by default.

The STL `queue` container provides a number of member functions. The most commonly used ones are:

-   Element access
    -   `q.front()` returns the front element
    -   `q.back()` returns the back element
-   Modifiers
    -   `q.push()` inserts an element at the back
    -   `q.pop()` removes the front element
-   Capacity
    -   `q.empty()` checks whether the queue is empty
    -   `q.size()` returns the number of elements in the queue

In addition, `queue` provides some operators. A commonly used one is the assignment operator `=` for assigning to a `queue`, for example:

```cpp
std::queue<int> q1, q2;

// push 1 to the back of q1
q1.push(1);

// assign q1 to q2
q2 = q1;

// print the front element of q2
std::cout << q2.front() << std::endl;
// output: 1
```

## Special queues

### Double-ended queue

A double-ended queue (deque) is a queue that can insert or remove elements at both the front and the back. It combines the abilities of a stack and a queue. Specifically, a deque supports 4 operations:

-   Insert an element at the front
-   Insert an element at the back
-   Remove an element from the front
-   Remove an element from the back

A deque is simulated with an array in the same way as an ordinary queue.

Likewise, we can maintain a deque using the two-stack idea. But note that when one stack is empty, alternately querying the front and the back breaks the amortized analysis. Instead, when moving elements, move only half of the non-empty stack's elements into the empty stack, keeping the roles of the front and back stacks. With this, insertion and deletion still take amortized constant time.

??? note "Brief proof"
    Insertion only costs constant time, so consider the pop operations. Suppose the queue starts with $m$ elements, and let us compute the time to pop all of them (from either end). The first rebalance costs $O(m)$. After that, each stack has $\frac{m}{2}$ elements. Then it takes $O(\frac{m}{2})$ time to empty one of the stacks, which may trigger another rebalance costing $O(\frac{m}{2})$, and so on, until all elements are popped. So the total complexity is
    
    $$
    T(m)=T\left(\frac{m}{2}\right)+O(m)
    $$
    
    By the master theorem, $T(m)=O(m)$. So the total cost of this approach is still amortized constant.

??? example "[Luogu B3656 [Template] Deque 1](https://www.luogu.com.cn/problem/B3656) reference implementation"
    ```cpp
    --8<-- "docs/ds/code/queue/queue_3.cpp"
    ```

#### Deques in the C++ STL

C++ also provides the container `std::deque` in the STL. You need to include the `<deque>` header before using it.

??? info "Definition of `deque` in the STL"
    ```cpp
    // clang-format off
    template<
        class T,
        class Allocator = std::allocator<T>
    > class deque;
    ```
    
    `T` is the type of data stored in the deque.
    
    `Allocator` is the allocator. We will not go into it here; the default is usually fine.

The STL `deque` container provides a number of member functions. The most commonly used ones are:

-   Element access
    -   `q.front()` returns the front element
    -   `q.back()` returns the back element
-   Modifiers
    -   `q.push_back()` inserts an element at the back
    -   `q.pop_back()` removes the back element
    -   `q.push_front()` inserts an element at the front
    -   `q.pop_front()` removes the front element
    -   `q.insert()` inserts an element before the given position (takes an iterator and an element)
    -   `q.erase()` removes the element at the given position (takes an iterator)
-   Capacity
    -   `q.empty()` checks whether the queue is empty
    -   `q.size()` returns the number of elements in the queue

In addition, `deque` provides some operators. The most commonly used ones are:

-   The assignment operator `=` for assigning to a `deque`, like `queue`.
-   `[]` for accessing elements, like `vector`.

The `<queue>` header also provides the priority queue `std::priority_queue`. Since it is closer to a [heap](./heap.md), we will not say much about it here.

#### Deques in Python

In Python, the deque container is provided by `collections.deque`.

Here is an example:

???+ note "Implementation"
    ```python
    from collections import deque
    
    # create a deque initialized with [1, 2, 3]
    queue = deque([1, 2, 3])
    
    # insert 4 at the back
    queue.append(4)
    
    # insert 0 at the front
    queue.appendleft(0)
    
    # access the queue
    # >>> queue
    # deque([0, 1, 2, 3, 4])
    ```

### Circular queue

Simulating a queue with an array causes a problem: over time, the whole queue moves toward the end of the array. Once it reaches the very end, pushing again causes an overflow even if there is free space at the front of the array (this overflow, which happens even though the array actually has free space, is called "false overflow").

The fix for false overflow is to organize the array storing the queue in a circular way: treat position 0 of the array as the successor of the last position. (The successor of the element at index `x` is `(x + 1) % SIZE`.) This gives a circular queue.

## References

1.  [std::queue - zh.cppreference.com](https://zh.cppreference.com/w/cpp/container/queue)
2.  [std::deque - zh.cppreference.com](https://zh.cppreference.com/w/cpp/container/deque)
