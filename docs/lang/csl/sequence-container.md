author: MingqiHuang, Xeonacid, greyqz, i-Yirannn, ChenZ01

## `vector`

`std::vector` is an array (also called a list) data structure provided by the STL that is **stored contiguously in memory** and has **variable length**. It supports insertion and deletion in linear time and random access in constant time.

### Why use `vector`

As OIers, we care much more about program speed than about engineering-grade robustness. Because `vector` manages memory dynamically, it is sometimes slower than a static array, and it can be even worse when the OJ server does not turn on full optimization. So we usually do not use `vector` for ordinary data storage. Below are some nice features of `vector`; when you need them, `vector` can help a lot.

#### `vector` can allocate memory dynamically

Often we cannot allocate that much space in advance (e.g. when precomputing the divisors of every number from 1 to n). Even if we know the total amount of data fits in memory, a single piece of data can still be very large. In such cases we need `vector` to keep memory use within a reasonable range. `vector` can also grow dynamically, which comes in handy when memory is very tight.

#### `vector` overloads the comparison and assignment operators

`vector` overloads all six comparison operators, using lexicographic order. This makes it easy to check whether two containers are equal (in time linear in the container size). For example, you can compare strings using `vector<char>` (though `std::string` is faster and more convenient). `vector` also overloads the assignment operator, which makes copying arrays easier.

#### Convenient initialization of `vector`

Since `vector` overloads the `=` operator, we can easily assign a whole `vector` at once. Since C++11, `vector` also supports [list initialization](https://zh.cppreference.com/w/cpp/language/list_initialization), for example `vector<int> data {1, 2, 3};`.

### Using `vector`

Common usage is described below. For details, [see the C++ documentation](https://zh.cppreference.com/w/cpp/container/vector).

#### Constructors

See the code below for examples (assuming you have already brought the relevant types of the `std` namespace in with `using`):

```cpp
// 1. Create an empty vector; constant time
vector<int> v0;
// 1+. This line guarantees constant time when inserting the first 3 elements into the vector
v0.reserve(3);
// 2. Create a vector with initial size 3, whose elements default to 0; linear time
vector<int> v1(3);
// 3. Create a vector with initial size 3, whose elements default to 2; linear time
vector<int> v2(3, 2);
// 4. Create a vector with initial size 3, whose elements default to 1,
// using the allocator of v2; linear time
vector<int> v3(3, 1, v2.get_allocator());
// 5. Create vector v4 as a copy of v2, with the same elements as v2; linear time
vector<int> v4(v2);
// 6. Create vector v5 as a copy of part of v4, with contents {v4[1], v4[2]}; linear time
vector<int> v5(v4.begin() + 1, v4.begin() + 3);
// 7. Move v2 into the newly created vector v6 without copying; constant time; requires C++11
vector<int> v6(std::move(v2));  // or v6 = std::move(v2);
```

??? note "Test code"
    ```cpp
    // Test code below; if you are interested, compile and run it yourself.
    cout << "v1 = ";
    copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    cout << "v2 = ";
    copy(v2.begin(), v2.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    cout << "v3 = ";
    copy(v3.begin(), v3.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    cout << "v4 = ";
    copy(v4.begin(), v4.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    cout << "v5 = ";
    copy(v5.begin(), v5.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    cout << "v6 = ";
    copy(v6.begin(), v6.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    ```

With the methods above you can construct a `vector`, which is all we need.

#### Element access

`vector` provides the following ways to access elements

1.  `at()`

    `v.at(pos)` returns a reference to the element at index `pos`. If the index is out of bounds, it throws an exception of type `std::out_of_range`.

2.  `operator[]`

    `v[pos]` returns a reference to the element at index `pos`. It does not check bounds.

3.  `front()`

    `v.front()` returns a reference to the first element.

4.  `back()`

    `v.back()` returns a reference to the last element.

5.  `data()`

    `v.data()` returns a pointer to the first element of the contiguous memory that `v` uses to store its data.

#### Iterators

vector provides the following [iterators](./iterator.md)

1.  `begin()/cbegin()`

    Returns an iterator to the first element, where `*begin = front`.

2.  `end()/cend()`

    Returns an iterator to the past-the-end placeholder of the container. Note that there is no element there.

3.  `rbegin()/crbegin()`

    Returns a reverse iterator to the first element of the reversed array, which you can think of as the last element of the container.

4.  `rend()/crend()`

    Returns an iterator to the position after the last element of the reversed array. This corresponds to the position before the start of the container, and there is no element there.

Among the iterators listed above, those with the letter `c` are read-only (const) iterators: you cannot change the values of elements in the `vector` through them. If a `vector` is itself read-only, its normal iterators and read-only iterators are exactly the same. Read-only iterators are supported since C++11.

#### Size and capacity

`vector` has the following functions related to its size and capacity. Note that the size of a `vector` is the number of valid elements, while its capacity is the length of the memory actually allocated. See the implementation details later for more.

**Related to size**:

-   `empty()` returns a `bool` value, namely `v.begin() == v.end()`: `true` means empty, `false` means not empty.

-   `size()` returns the size of the container (the number of elements), namely `std::distance(v.begin(), v.end())`.

-   `resize(n)` changes the size of the `vector` to `n`. If `n` is larger than the current size, elements are added: if an element to add is given as an argument, that element is used; otherwise the default value is used. If `n` is smaller than the current size, the first `n` elements are kept and the rest are deleted.

-   `max_size()` returns the largest possible size of the container.

    **Related to capacity**:

-   `reserve()` makes the `vector` reserve some memory in advance, to avoid unnecessary allocations and copies.

-   `capacity()` returns the capacity of the container, i.e. how many elements the `vector` has currently allocated space for.

-   `shrink_to_fit()` makes the capacity of the `vector` equal to its size, freeing the capacity it does not use.

### Adding, removing and modifying elements

-   `clear()` removes all elements
-   `insert()` inserts elements at an iterator position; it can insert several at once. **Its time is linear in the distance from `pos` to the end, not constant**
-   `erase()` deletes the element at an iterator or the elements in a range, and returns the iterator after the last deleted element. Its complexity is the same as `insert`.
-   `push_back()` inserts an element at the end. Its amortized complexity is **constant**, and its worst case is linear.
-   `pop_back()` deletes the last element in constant time.
-   `swap()` swaps with another container. This takes **constant time**, not linear time.

### Implementation details of `vector`

Underneath, a `vector` is still a fixed-length array. It can grow dynamically because it adds steps to avoid overflowing that array. First note that the number of elements in a `vector` (its size) $n$ is not the same as the maximum number of elements its allocated memory can hold (its capacity) $N$; `vector` stores these two values separately. When an element is added and the container finds $n>N$, it allocates an array of size $2N$, copies the old data to the new array, and then frees the old memory. Although this operation takes $O(n)$ time, one can prove that its amortized cost is $O(1)$. Deleting an element at the end and accessing an element are still $O(1)$.
So as long as you estimate the size of a `vector` well and make good use of `resize()` and `reserve()`, a `vector` is not much slower than a fixed-length array.

### `vector<bool>`

The standard library provides a special version of `vector` for `bool`, where each "`bool`" takes only 1 bit and the vector can still grow dynamically. But its `operator[]` returns `vector<bool>::reference` instead of `bool&`. So be careful when using `vector<bool>`; consider using `deque<bool>` or `vector<char>` instead. If you need to save space, just use [`bitset`](./bitset.md).

## `array`(C++11)

`std::array` is an array data structure provided by the STL that is **stored contiguously in memory** and has **fixed length**. It is simply a thin wrapper around a built-in array.

### Why use `array`

`array` is really the STL's wrapper around an array. Compared with `vector`, it gives up dynamic growth, but in return its performance is almost the same as a built-in array (with full optimization on). So if you can use C++11 features, you can replace almost any fixed-length built-in array with `array`, and any dynamically allocated array with `vector`.

### Member functions

#### Implicitly defined member functions

| Function    | Purpose                             |
| ----------- | ----------------------------------- |
| `operator=` | overwrites each element of the `array` with the corresponding element of another `array` |

#### Element access

| Function     | Purpose              |
| ------------ | -------------------- |
| `at`         | accesses the given element, with bounds checking |
| `operator[]` | accesses the given element, **without** bounds checking |
| `front`      | accesses the first element |
| `back`       | accesses the last element |
| `data`       | returns a pointer to the first element of the array in memory |

`at` throws `std::out_of_range` if `pos >= size()`.

#### Capacity

| Function   | Purpose     |
| ---------- | ----------- |
| `empty`    | checks whether the container is empty |
| `size`     | returns the number of elements |
| `max_size` | returns the maximum possible number of elements |

Since every `array` is a fixed-size container, the value returned by `size()` equals the value returned by `max_size()`.

### Operations

| Function | Purpose  |
| ------ | -------- |
| `fill` | fills the container with the given value |
| `swap` | swaps the contents |

**Note: swapping two `array`s takes $\Theta(\text{size})$ time, not $O(1)$ like ordinary STL containers.**

### Non-member functions

| Function       | Purpose             |
| -------------- | ------------------- |
| `operator==` etc. | compares the values in the `array`s in lexicographic order |
| `std::get`     | accesses one element of an `array` |
| `std::swap`    | specialized `std::swap` algorithm |

Here is an example of using `array`:

```cpp
// 1. Create an array of length 3 with no initial values; constant time
std::array<int, 3> v0;
// 2. Create an array with the given constants; constant time
std::array<int, 3> v1{1, 2, 3};

v0.fill(1);  // fill the array

// access the array
for (int i = 0; i != arr.size(); ++i) cout << arr[i] << " ";
```

## `deque`

`std::deque` is a [double-ended queue](../../ds/queue.md#双端队列) data structure provided by the STL. It supports insertion and deletion in linear time and random access in constant time.

### Using `deque`

Common usage is described below. For details, [see the C++ documentation](https://zh.cppreference.com/w/cpp/container/deque). The iterator functions of `deque` are the same as those of `vector`, so they are not described in detail.

#### Constructors

See the code below (assuming you have already brought the relevant types of the `std` namespace in with `using`):

```cpp
// 1. Define an empty deque of int, v0
deque<int> v0;
// 2. Define a deque of int, v1, with initial size 10; linear time
deque<int> v1(10);
// 3. Define a deque of int, v2, initialized to ten 1s; linear time
deque<int> v2(10, 1);
// 4. Copy the existing deque v1; linear time
deque<int> v3(v1);
// 5. Create deque v4 as a copy of part of v2, with contents v2[0] to v2[2]; linear time
deque<int> v4(v2.begin(), v2.begin() + 3);
// 6. Move v2 into the newly created deque v5 without copying; constant time; requires C++11
deque<int> v5(std::move(v2));
```

#### Element access

Same as `vector`, but you cannot access the underlying memory. For why element access is still fast, see the implementation details section.

-   `at()` returns a reference to the element at the given position, with bounds checking, in **constant time**.
-   `operator[]` returns a reference to the element at the given position, without bounds checking, in **constant time**.
-   `front()` returns a reference to the first element.
-   `back()` returns a reference to the last element.

#### Iterators

Same as `vector`.

#### Size

Same as `vector`, but there are no `reserve()` and `capacity()` functions. (There is still a `shrink_to_fit()` function.)

#### Adding, removing and modifying elements

Same as `vector`, plus functions that add elements at the front of the queue.

-   `clear()` removes all elements
-   `insert()` inserts elements at an iterator position; it can insert several at once. **Its time is linear in the smaller of the distances from `pos` to the two ends**.
-   `erase()` deletes the element at an iterator or the elements in a range, and returns the iterator after the last deleted element. Its complexity is the same as `insert`.
-   `push_front()` inserts an element at the front in **constant time**.
-   `pop_front()` deletes the first element in **constant time**.
-   `push_back()` inserts an element at the end in **constant time**.
-   `pop_back()` deletes the last element in **constant time**.
-   `swap()` swaps with another container. This takes **constant time**, not linear time.

### Implementation details of `deque`

`deque` is usually implemented as several separate buffers; memory inside each buffer is contiguous. Each buffer also records a head pointer and a tail pointer that mark the range of valid data. When a buffer is full, a new buffer is allocated before or after it to store more data. For a more detailed explanation, see [*The Annotated STL Sources*: how deque is implemented](https://www.cnblogs.com/q1076452761/p/16903229.html).

## `list`

`std::list` is a [doubly linked list](../../ds/linked-list.md) data structure provided by the STL. It supports random access in linear time and insertion and deletion in constant time.

### Using `list`

`list` is used in almost the same way as `deque`, but the costs of insertion, deletion and access are different. For details, [see the C++ documentation](https://zh.cppreference.com/w/cpp/container/list). The functions of `list` for iterators, size, and adding, removing and modifying elements are the same as those of `deque`, so they are not described in detail.

#### Element access

Since `list` is implemented as a linked list, it does not provide random access. To access an element in the middle, you need to use iterators.

-   `front()` returns a reference to the first element.
-   `back()` returns a reference to the last element.

#### Operations

The `list` type also provides some STL algorithm functions implemented for its own structure. Since the general versions of these algorithms require [random access iterators](./iterator.md), `list` provides its own special versions for convenience. These algorithms include `splice()`, `remove()`, `sort()`, `unique()`, `merge()` and so on.

## `forward_list` (C++11)

`std::forward_list` is a [singly linked list](../../ds/linked-list.md) data structure provided by the STL. It uses less space than `std::list`.

### Using `forward_list`

`forward_list` is used almost the same way as `list`, but its iterators only go in one direction, so its usage is not described in detail. For details, [see the C++ documentation](https://zh.cppreference.com/w/cpp/container/forward_list)
