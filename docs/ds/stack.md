## Introduction

![](./images/stack.svg)

A stack is a linear data structure that is used a lot in OI. Note that this page is about the stack as a data structure, not the system stack (stack memory) used while a program runs.

A stack is modified and accessed in last-in, first-out order, so it is often called a last in first out list, or LIFO list for short.

??? warning "Warning"
    LIFO means that, among the elements **currently in the container**, the last one to come in is the first one to go out.
    
    Consider the following stack:
    
    ```text
    push(1)
    pop(1)
    push(2)
    pop(2)
    ```
    
    If we look at the whole history, 1 is pushed first and popped first, and 2 is pushed last and popped last. That would make it a first-in, first-out list, which is clearly wrong.
    
    So when deciding whether a data structure is LIFO or FIFO, you should look at what is currently inside the container.

## Simulating a stack with an array

We can easily simulate a stack with an array, like this:

???+ note "Implementation"
    === "C++"
        ```cpp
        int st[N];
        // Here st[0] (i.e. *st) stores the number of elements in the stack, which is also the index of the top
        
        // Push:
        st[++*st] = var1;
        // Read the top:
        int u = st[*st];
        // Pop: watch out for underflow; you cannot pop when *st == 0
        if (*st) --*st;
        // Clear the stack
        *st = 0;
        ```
    
    === "Python"
        ```python
        st = [0] * N
        # Here st[0] stores the number of elements in the stack, which is also the index of the top
        
        # Push:
        st[st[0] + 1] = var1
        st[0] = st[0] + 1
        # Read the top:
        u = st[st[0]]
        # Pop: watch out for underflow; you cannot pop when *st == 0
        if st[0]:
            st[0] = st[0] - 1
        # Clear the stack
        st[0] = 0
        ```

## The stack in the C++ STL

The C++ STL also provides a container `std::stack`. You need to include the `stack` header before using it.

???+ info "Definition of `stack` in the STL"
    ```cpp
    // clang-format off
    template<
        class T,
        class Container = std::deque<T>
    > class stack;
    ```
    
    `T` is the type of the data stored in the stack.
    
    `Container` is the type of the underlying container used to store the elements. It must provide the following functions with their usual meaning:
    
    -   `back()`
    -   `push_back()`
    -   `pop_back()`
    
    The STL containers `std::vector`, `std::deque` and `std::list` meet these requirements. If you do not specify one, `std::deque` is used as the underlying container by default.

The STL `stack` container provides a number of member functions. The most commonly used ones are:

-   Element access
    -   `st.top()` returns the top element
-   Modifiers
    -   `st.push()` pushes the given argument onto the top
    -   `st.pop()` pops the top element
-   Capacity
    -   `st.empty()` returns whether the stack is empty
    -   `st.size()` returns the number of elements

`std::stack` also provides some operators. The most common one is the assignment operator `=`, used to assign one `stack` to another. Example:

```cpp
// Create two stacks st1 and st2
std::stack<int> st1, st2;

// Push 1 into st1
st1.push(1);

// Assign st1 to st2
st2 = st1;

// Print the top element of st2
cout << st2.top() << endl;
// Output: 1
```

## Simulating a stack with a Python list

In Python, you can use a list to simulate a stack:

???+ note "Implementation"
    ```python
    st = [5, 1, 4]
    
    # Use append() to add elements to the top
    st.append(2)
    st.append(3)
    # >>> st
    # [5, 1, 4, 2, 3]
    
    # Use pop to remove the top element
    st.pop()
    # >>> st
    # [5, 1, 4, 2]
    
    # Use clear to empty the stack
    st.clear()
    ```

## References

1.  [std::stack - zh.cppreference.com](https://zh.cppreference.com/w/cpp/container/stack)
