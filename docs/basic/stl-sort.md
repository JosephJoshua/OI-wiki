This page gives a short introduction to the sorting algorithms provided by the C and C++ standard libraries.

Unless stated otherwise, the functions on this page are defined in the header `<algorithm>`.

## qsort

See: [`qsort`](https://zh.cppreference.com/w/c/algorithm/qsort), [`std::qsort`](https://zh.cppreference.com/w/cpp/algorithm/qsort)

This is the general-purpose array sorting function of the C standard library. The actual algorithm is up to the library implementation. It is defined in `<stdlib.h>`. In the C++ standard library, it is defined in `<cstdlib>`.

???+ warning "Note[^note2]"
    Despite its name, neither the C standard nor POSIX requires `qsort` to use [quicksort](./quick-sort.md), and they have never guaranteed any complexity or stability.

### Comparison functions for qsort and bsearch

The qsort function takes four arguments: the array, the number of elements, the size of each element, and the comparison rule. The comparison rule is given as a comparison function, and different comparison functions give different sorting orders.

The comparison function must take exactly two parameters of type `const void *`. It must return a positive number, a negative number, or 0.

Here is one way to write a comparison function:

```c
int compare(const void* p1, const void* p2)  // comparison function for an int array
{
  int* a = (int*)p1;
  int* b = (int*)p2;
  if (*a > *b)
    return 1;  // a positive value means a is greater than b
  else if (*a < *b)
    return -1;  // a negative value means a is less than b
  else
    return 0;  // 0 means a and b are equivalent
}
```

Note: returning the difference of the two elements instead of a positive/negative number is a classic mistake, because the subtraction can overflow.

Here is an example of sorting structs:

```c
struct eg  // example struct
{
  int e;
  int g;
};

// comparison function for an array of struct eg: sort by member e
int compare(const void* p1, const void* p2) {
  struct eg* a = (struct eg*)p1;
  struct eg* b = (struct eg*)p2;
  if (a->e > b->e)
    return 1;  // a positive value means a is greater than b
  else if (a->e < b->e)
    return -1;  // a negative value means a is less than b
  else
    return 0;  // 0 means a and b are equivalent
}
```

This also shows that "equivalent" does not mean "equal". It only means the two elements are equivalent under this comparison rule.

## std::sort

See: [`std::sort`](https://zh.cppreference.com/w/cpp/algorithm/sort)

Usage:

```cpp
// a[0] .. a[n - 1] is the sequence to sort
// sort a in place, in increasing order
std::sort(a, a + n);

// cmp is a custom comparison function
std::sort(a, a + n, cmp);
```

Note: the comparison function for sort returns `true` or `false`, which tells the order between two elements. Its meaning is completely different from qsort's three-way comparison function. See the sort documentation linked above for details.

If `cmp` defines a strict weak ordering, then to convert it into qsort's three-way comparison rule, return `cmp(a,b) ? -1 : cmp(b,a) ? 1 : 0`. Equivalent elements must return zero.

`std::sort` is the more commonly used C++ library sorting function. Its last argument is a binary comparison function. If no `cmp` function is given, it sorts in increasing order by default.

Older C++ standards only required its **average** time complexity to be $O(n\log n)$. C++11 and later standards require its **worst-case** time complexity to be $O(n\log n)$.

The C++ standard does not strictly specify which algorithm this function uses; that depends on the standard library. For example, the implementations in [libstdc++ 14.2.0](https://github.com/gcc-mirror/gcc/blob/releases/gcc-14.2.0/libstdc%2B%2B-v3/include/bits/stl_algo.h#L1876-L1908) and [libc++ 20.1.8](https://github.com/llvm/llvm-project/blob/llvmorg-20.1.8/libcxx/include/__algorithm/sort.h#L709-L727) both use [introsort](./quick-sort.md#introsort).

## std::nth\_element

See: [`std::nth_element`](https://zh.cppreference.com/w/cpp/algorithm/nth_element)

Usage:

```cpp
std::nth_element(first, nth, last);
std::nth_element(first, nth, last, cmp);
```

It rearranges the elements in `[first, last)` so that the element pointed to by `nth` becomes the element that would be in that position if `[first, last)` were sorted. Every element before this new `nth` element is less than or equal to every element after it.

The actual implementation is up to the standard library. Common implementations use algorithms such as [quickselect](https://en.wikipedia.org/wiki/Quickselect) or [introselect](https://en.wikipedia.org/wiki/Introselect): after each partition, they only keep working on the side that contains the target position.

For both forms above, the C++ standard requires an average time complexity of $O(n)$, where n is `std::distance(first, last)`.

It is often used to build a [K-D Tree](../ds/kdt.md).

## std::stable\_sort

See: [`std::stable_sort`](https://zh.cppreference.com/w/cpp/algorithm/stable_sort)

Usage:

```cpp
std::stable_sort(first, last);
std::stable_sort(first, last, cmp);
```

A stable sort: equal elements keep the same relative order after sorting as in the original sequence.

Its time complexity is $O(n\log^2 n)$, or $O(n\log n)$ when extra memory is available.

## std::partial\_sort

See: [`std::partial_sort`](https://zh.cppreference.com/w/cpp/algorithm/partial_sort)

Usage:

```cpp
// mid = first + k
std::partial_sort(first, mid, last);
std::partial_sort(first, mid, last, cmp);
```

It picks the `k` elements of `[first,last)` that come first in the order given by `cmp`, and places them, sorted, in `[first,mid)`. The order of the remaining elements is not guaranteed. If no `cmp` function is given, it sorts in increasing order by default.

Complexity: about $(\textit{last}-\textit{first})\log(\textit{mid}-\textit{first})$ applications of `cmp`.

How it works:

The idea behind `std::partial_sort` is as follows. Run `make_heap()` on the elements in `[first, mid)` of the original container to build a max-heap. Then compare each element of `[mid, last)` with `first`, which always holds the maximum of the heap. If the element is smaller than this maximum, swap them and adjust the elements in `[first, mid)` to restore the max-heap order. After all comparisons are done, run a heap sort `sort_heap()` on `[first, mid)` so that it is in increasing order. Note that heap order and increasing order are not the same thing.

## Custom comparison

See: [Operator overloading](https://zh.cppreference.com/w/cpp/language/operators)

For both built-in types (such as `int`) and user-defined structs, you can customize the comparison function used when calling the STL sorting functions. Just pass a function that implements a binary comparison as the last argument.

For a user-defined struct, before using an STL sorting function on it, you must either define at least one relational operator or pass a binary comparison function when calling it. Defining `operator<` is usually recommended.[^note1]

Example:

```cpp
int a[1009], n = 10;
// ...
std::sort(a + 1, a + 1 + n);                  // sort in increasing order
std::sort(a + 1, a + 1 + n, greater<int>());  // sort in decreasing order
```

```cpp
struct data {
  int a, b;

  bool operator<(const data rhs) const {
    return (a == rhs.a) ? (b < rhs.b) : (a < rhs.a);
  }
} da[1009];

bool cmp(const data u1, const data u2) {
  return (u1.a == u2.a) ? (u1.b > u2.b) : (u1.a > u2.a);
}

// ...
std::sort(da + 1, da + 1 + 10);  // use the < operator defined in the struct; increasing order
std::sort(da + 1, da + 1 + 10, cmp);  // compare using cmp; decreasing order
```

### Strict weak ordering

See also: [Applications in C++ - Order theory](../math/order-theory.md#c-中的应用)

The operator used for sorting must be a [strict weak ordering](../math/order-theory.md#二元关系). Otherwise, unpredictable things can happen (such as runtime errors or incorrect sorting).

Common mistakes:

-   Using `<=` to define the less-than operator for sorting.
-   Having the sorting operator read an array whose values may be changed from outside (common in shortest path algorithms).
-   Using a comparison of the max/min of several numbers as the sorting operator (a classic mistake in problems like Queen's Game / Flow Shop Scheduling).

## External links

-   [On the uses of adjacent exchange sorting and the pitfalls to watch for (Chinese)](https://ouuan.github.io/浅谈邻项交换排序的应用以及需要注意的问题/)

## References and notes

[^note1]: Because most standard algorithms compare with `operator<` by default.

[^note2]: [qsort, qsort\_s - cppreference.com](https://en.cppreference.com/c/algorithm/qsort)
