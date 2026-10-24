In the STL, an iterator is an object used to access and inspect elements in an STL container. It behaves much like a pointer, but it wraps some validity checks and provides a uniform way to access elements. Similar concepts exist in many other high-level languages, such as Python's `__iter__` function and C#'s `IEnumerator`.

## Basic usage

Iterators may sound obscure, but an iterator can be thought of as a pointer to data. Iterators mainly support two operators: increment (`++`) and dereference (the unary `*` operator). Increment moves the iterator, and dereference reads or modifies the element it points to.

The type of an iterator to elements of an [STL container](./container.md)  `container` is usually `container::iterator`.

You can use iterators to traverse a container. For example, the following two for loops do the same thing:

```cpp
vector<int> data(10);

for (int i = 0; i < data.size(); i++)
  cout << data[i] << endl;  // Access elements by index

for (vector<int>::iterator iter = data.begin(); iter != data.end(); iter++)
  cout << *iter << endl;  // Access elements with an iterator
// Since C++11, you can write auto iter = data.begin() to simplify the code above
```

???+ tip "Using `auto` in contests"
    Most contestants like to use `auto` instead of long iterator declarations. According to the [Supplementary Notes on Programming Language Restrictions in NOI-Series Events](https://www.noi.cn/xw/2021-09-01/735729.shtml) published in September 2021, NOI-series contests (including CSP J/S) are judged with **C++14**, which already supports the `auto` keyword.

## Categories

In the STL definition, iterators are divided into the following categories according to the operations they support:

-   InputIterator: only needs to support copying, incrementing, and reading through dereference.
-   OutputIterator: only needs to support copying, incrementing, and assigning through dereference.
-   ForwardIterator: on top of InputIterator, supports traversing and reading through dereference multiple times, and guarantees that repeated reads give the same result.
-   BidirectionalIterator: on top of ForwardIterator, supports decrement (that is, moving backward).
-   RandomAccessIterator: on top of BidirectionalIterator, supports addition/subtraction and comparison (that is, random access).
-   ContiguousIterator: on top of RandomAccessIterator, requires that for a dereferenceable iterator `a + n`, `*(a + n)` is equivalent to `*(std::address_of(*a) + n)` (that is, contiguous storage, where `a` is a contiguous iterator and `n` is an integer).

    ContiguousIterator was formally introduced in C++17.

???+ tip "Why is an input iterator called an input iterator?"
    "Input" means "you can get input from the iterator", and "output" means "you can output to the iterator".
    
    The one doing the "input" and "output" is the rest of the program, not the iterator itself.

These categories are not mutually exclusive. In fact, except for output iterators, each iterator earlier in the list includes all the ones after it. For example, where a forward iterator is required, you can also use a bidirectional iterator. Starting from forward iterators, if these iterators also provide the functionality of output iterators (that is, allow writing), they are called mutable iterators. This gives categories such as "mutable random access iterator".

Different [STL containers](./container.md) support different iterator types, so keep this in mind when using them.

Array pointers meet all the requirements of contiguous iterators (or random access iterators, for C++14 and earlier), so they can be used as contiguous iterators.

## Related functions

Many [STL functions](./algorithm.md) take iterators as arguments.

You can use `std::advance(it, n)` to move iterator `it` forward by `n` steps. If `n` is negative, it moves backward, and the iterator must then be a bidirectional iterator; otherwise the behavior is undefined.

Since C++11, you can use `std::next(it)` to get the successor of a forward iterator `it` (the iterator `it` itself does not change), and `std::next(it, n)` to get the `n`-th successor of a forward iterator `it`.

Since C++11, you can use `std::prev(it)` to get the predecessor of a bidirectional iterator `it` (the iterator `it` itself does not change), and `std::prev(it, n)` to get the `n`-th predecessor of a bidirectional iterator `it`.

[STL containers](./container.md) usually support access starting from one or both ends, and support the [const qualifier](../const.md). For example, a container's `begin()` function gives an iterator to the first element of the container, `rbegin()` gives a reverse iterator to the last element, `cbegin()` gives a const iterator to the first element, and `end()` gives an iterator to the end of the container (the "end" is not the last element; think of it as the successor of the last element. The predecessor of the "end" is the last element in the container, and the end itself does not point to any element).

See [Iterator library - cppreference.com](https://en.cppreference.com/w/cpp/iterator) for more usage.
