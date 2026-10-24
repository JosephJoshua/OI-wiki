author: Xeonacid, ksyx, Early0v0

## Stack

The STL [stack](../../ds/stack.md) (`std::stack`) is a Last In, First Out container adapter. It only supports reading or removing the most recently added element (the top of the stack). It does not support random access, and to keep the data strictly ordered, it does not support iterators.

### Header

```cpp
#include <stack>
```

### Definition

```cpp
std::stack<TypeName> s;  // Uses the default underlying container deque; the element type is TypeName
std::stack<TypeName, Container> s;  // Uses Container as the underlying container
std::stack<TypeName> s2(s1);        // Constructs s2 as a copy of s1
```

### Member functions

**All of the following functions take constant time**

-   `top()` accesses the top element (this is an error if the stack is empty)
-   `push(x)` inserts element x into the stack
-   `pop()` removes the top element
-   `size()` returns the number of elements in the container
-   `empty()` returns whether the container is empty

### Simple example

```cpp
std::stack<int> s1;
s1.push(2);
s1.push(1);
std::stack<int> s2(s1);
s1.pop();
std::cout << s1.size() << " " << s2.size() << std::endl;  // 1 2
std::cout << s1.top() << " " << s2.top() << std::endl;    // 2 1
s1.pop();
std::cout << s1.empty() << " " << s2.empty() << std::endl;  // 1 0
```

## Queue

The STL [queue](../../ds/queue.md) (`std::queue`) is a First In, First Out container adapter. It only supports reading or removing the earliest added element (the front of the queue). It does not support random access, and to keep the data strictly ordered, it does not support iterators.

### Header

```cpp
#include <queue>
```

### Definition

```cpp
std::queue<TypeName> q;  // Uses the default underlying container deque; the element type is TypeName
std::queue<TypeName, Container> q;  // Uses Container as the underlying container

std::queue<TypeName> q2(q1);  // Constructs q2 as a copy of q1
```

### Member functions

**All of the following functions take constant time**

-   `front()` accesses the front element (this is an error if the queue is empty)
-   `push(x)` inserts element x into the queue
-   `pop()` removes the front element
-   `size()` returns the number of elements in the container
-   `empty()` returns whether the container is empty

### Simple example

```cpp
std::queue<int> q1;
q1.push(2);
q1.push(1);
std::queue<int> q2(q1);
q1.pop();
std::cout << q1.size() << " " << q2.size() << std::endl;    // 1 2
std::cout << q1.front() << " " << q2.front() << std::endl;  // 1 2
q1.pop();
std::cout << q1.empty() << " " << q2.empty() << std::endl;  // 1 0
```

## Priority queue

The priority queue `std::priority_queue` is a [heap](../../ds/heap.md), usually a [binary heap](../../ds/binary-heap.md).

### Header

```cpp
#include <queue>
```

### Definition

```cpp
std::priority_queue<TypeName> q;             // The element type is TypeName
std::priority_queue<TypeName, Container> q;  // Uses Container as the underlying container
std::priority_queue<TypeName, Container, Compare> q;
// Uses Container as the underlying container and Compare as the comparison type

// The default underlying container is vector
// The default comparison type is less<TypeName> (then top() returns the maximum)
// If you want top() to return the minimum, use greater<TypeName> as the comparison type
// Note: you cannot skip Container and pass Compare directly

// Since C++11, if you use a lambda function as a custom Compare,
// you need to pass it as a constructor argument, for example:
auto cmp = [](const std::pair<int, int> &l, const std::pair<int, int> &r) {
  return l.second < r.second;
};
std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                    decltype(cmp)>
    pq(cmp);
```

### Member functions

**All of the following functions take constant time**

-   `top()` accesses the top element of the heap (the priority queue must not be empty)
-   `empty()` returns whether the container is empty
-   `size()` returns the number of elements in the container

**All of the following functions take logarithmic time**

-   `push(x)` inserts an element and reorders the underlying container
-   `pop()` removes the top element of the heap (the priority queue must not be empty)

### Simple example

```cpp
std::priority_queue<int> q1;
std::priority_queue<int, std::vector<int>> q2;
// Since C++11, the space can be omitted
std::priority_queue<int, std::deque<int>, std::greater<int>> q3;
// q3 is a min-heap
for (int i = 1; i <= 5; i++) q1.push(i);
// Elements in q1:  [1, 2, 3, 4, 5]
std::cout << q1.top() << std::endl;
// Output: 5
q1.pop();
// Elements in the heap: [1, 2, 3, 4]
std::cout << q1.size() << std::endl;
// Output: 4
for (int i = 1; i <= 5; i++) q3.push(i);
// Elements in q3:  [1, 2, 3, 4, 5]
std::cout << q3.top() << std::endl;
// Output: 1
```
