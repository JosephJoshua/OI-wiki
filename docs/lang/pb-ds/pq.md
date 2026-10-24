author: Xeonacid, ouuan, Ir1d, WAAutoMaton, Chrogeek, abc1763613206, Planet6174, i-Yirannn, opsiff, GoodCoder666

## `__gnu_pbds::priority_queue`

See also: [Official documentation: complexity and constant-factor tests](https://gcc.gnu.org/onlinedocs/libstdc++/ext/pb_ds/pq_performance_tests.html#std_mod1)

```cpp
#include <ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
__gnu_pbds::priority_queue<T, Compare, Tag, Allocator>
```

## Template parameters

-   `T`: the type of the stored elements
-   `Compare`: a comparison type that provides a strict weak ordering
-   `Tag`: one of the five kinds of heap that `__gnu_pbds` provides. The default is `pairing_heap_tag`. The five are:
    -   `pairing_heap_tag`: pairing heap
        The official documentation says the pairing heap performs best for non-primitive elements (such as custom structs, `std::string` or `pair`)
    -   `binary_heap_tag`: binary heap
        The official documentation says the binary heap performs best for primitive elements, but in the author's tests it did not do that well
    -   `binomial_heap_tag`: binomial heap
        A binomial heap merges faster than a binary heap, but getting the top element has a higher complexity than in a binary heap
    -   `rc_binomial_heap_tag`: redundant-counter binomial heap
    -   `thin_heap_tag`: a tag whose complexities match a Fibonacci heap for everything except merging
-   `Allocator`: the memory allocator. It is rarely used in OI, so it is not covered here

This article is written for students learning competitive programming, so for the last four tags we only briefly list their complexities. For the first one we explain the member functions and how to use it.

The author tested basic heap operations on a Core i5 @3.1 GHz under macOS. Together with GNU's official complexity tests and a Dijkstra test, the results all show that:
at least for OIers, the four tags other than the pairing heap are of little value. They are either useless or have such large constants that they are slower than the `std` version, and they may cause MLE. So we only recommend the default pairing heap. The pairing heap is also better than `make_heap()` from the `algorithm` library.

## Construction

You must specify the namespace, because the class name clashes with the one in `std`.

```cpp
// __gnu_pbds::priority_queue<int>;
// __gnu_pbds::priority_queue<int, greater<int>>;
// __gnu_pbds::priority_queue<int, greater<int>, pairing_heap_tag>;
__gnu_pbds::priority_queue<int>::point_iterator id;  // point-type iterator
// modify and push both return a point_iterator; how to use it is explained below
id = q.push(1);
```

## Member functions

-   `push()`: pushes an element into the heap and returns an iterator to its position.
-   `pop()`: pops the top element of the heap.
-   `top()`: returns the top element of the heap.
-   `size()` returns the number of elements.
-   `empty()` returns whether the heap is empty.
-   `modify(point_iterator, const key)`: changes the `key` at the iterator's position to the given `key`, and reorders the underlying storage.
-   `erase(point_iterator)`: erases the key at the iterator's position from the heap.
-   `join(__gnu_pbds::priority_queue &other)`: merges `other` into `*this` and empties `other`.

The tag you choose determines the time complexity of each operation:

|                        | push                                         | pop                                          | modify                                       | erase                                        | Join              |
| ---------------------- | -------------------------------------------- | :------------------------------------------- | -------------------------------------------- | -------------------------------------------- | ----------------- |
| `pairing_heap_tag`     | $O(1)$                                       | worst $\Theta(n)$, amortized $\Theta(\log(n))$ | worst $\Theta(n)$, amortized $\Theta(\log(n))$ | worst $\Theta(n)$, amortized $\Theta(\log(n))$ | $O(1)$            |
| `binary_heap_tag`      | worst $\Theta(n)$, amortized $\Theta(\log(n))$ | worst $\Theta(n)$, amortized $\Theta(\log(n))$ | $\Theta(n)$                                  | $\Theta(n)$                                  | $\Theta(n)$       |
| `binomial_heap_tag`    | worst $\Theta(\log(n))$, amortized $O(1)$      | $\Theta(\log(n))$                            | $\Theta(\log(n))$                            | $\Theta(\log(n))$                            | $\Theta(\log(n))$ |
| `rc_binomial_heap_tag` | $O(1)$                                       | $\Theta(\log(n))$                            | $\Theta(\log(n))$                            | $\Theta(\log(n))$                            | $\Theta(\log(n))$ |
| `thin_heap_tag`        | $O(1)$                                       | worst $\Theta(n)$, amortized $\Theta(\log(n))$ | worst $\Theta(\log(n))$, amortized $O(1)$      | worst $\Theta(n)$, amortized $\Theta(\log(n))$ | $\Theta(n)$       |

## Example

```cpp
#include <algorithm>
#include <cstdio>
#include <ext/pb_ds/priority_queue.hpp>
#include <iostream>
using namespace __gnu_pbds;
// Since this is aimed at OIers, we use the common heap pairing_heap_tag as the example
// For easier reading, we define the following alias:
using pair_heap = __gnu_pbds::priority_queue<int>;
pair_heap q1;  // max-heap, pairing heap
pair_heap q2;
pair_heap::point_iterator id;  // an iterator

int main() {
  id = q1.push(1);
  // elements in the heap: [1];
  for (int i = 2; i <= 5; i++) q1.push(i);
  // elements in the heap: [1, 2, 3, 4, 5];
  std::cout << q1.top() << std::endl;
  // output: 5;
  q1.pop();
  // elements in the heap: [1, 2, 3, 4];
  id = q1.push(10);
  // elements in the heap: [1, 2, 3, 4, 10];
  q1.modify(id, 1);
  // elements in the heap: [1, 1, 2, 3, 4];
  std::cout << q1.top() << std::endl;
  // output: 4;
  q1.pop();
  // elements in the heap: [1, 1, 2, 3];
  id = q1.push(7);
  // elements in the heap: [1, 1, 2, 3, 7];
  q1.erase(id);
  // elements in the heap: [1, 1, 2, 3];
  q2.push(1), q2.push(3), q2.push(5);
  // elements in q1: [1, 1, 2, 3], elements in q2: [1, 3, 5];
  q2.join(q1);
  // q1 is empty, elements in q2: [1, 1, 1, 2, 3, 3, 5];
}
```

## Iterator invalidation guarantees in \_\_gnu\_pbds (invalidation\_guarantee)

In the example above and in some real uses (such as writing single-source shortest paths with the pb-ds heap from this chapter), you often need to store and use heap iterators (such as `__gnu_pbds::priority_queue<int>::point_iterator`).

However, the different Tag parameters of `__gnu_pbds::priority_queue` have different underlying implementations, so their iterators become invalid under different conditions. The \_\_gnu\_pbds library is designed with the following three cases, each derived from the one above it:

1.  Basic invalidation guarantee (basic\_invalidation\_guarantee): as long as the container is not modified, point-type iterators (point\_iterator), pointers and references (key/value) **stay** valid.

2.  Point invalidation guarantee (point\_invalidation\_guarantee): after the container is **modified**, point-type iterators (point\_iterator), pointers and references (key/value) **stay** valid as long as the element they refer to has not been erased from the container.

3.  Range invalidation guarantee (range\_invalidation\_guarantee): after the container is **modified**, in addition to property (2), every range-type iterator (including the return values of `begin()` and `end()`) is still correct. The tags with the range invalidation guarantee are `rb_tree_tag` and `splay_tree_tag` for `__gnu_pbds::tree`, and `pat_trie_tag` for `__gnu_pbds::trie`.

Running the code below shows that only `binary_heap_tag` has `basic_invalidation_guarantee`, so its iterators become invalid after a modification. All the others have `point_invalidation_guarantee`, so point-type iterators (point\_iterator) stay valid after modifications.

```cpp
#include <iostream>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
#include <cxxabi.h>

template <typename T>
void print_invalidation_guarantee() {
  using gute = __gnu_pbds::container_traits<T>::invalidation_guarantee;
  cout << abi::__cxa_demangle(typeid(gute).name(), 0, 0, 0) << endl;
}

int main() {
  using pairing =
      __gnu_pbds::priority_queue<int, greater<int>, pairing_heap_tag>;
  using binary = __gnu_pbds::priority_queue<int, greater<int>, binary_heap_tag>;
  using binomial =
      __gnu_pbds::priority_queue<int, greater<int>, binomial_heap_tag>;
  using rc_binomial =
      __gnu_pbds::priority_queue<int, greater<int>, rc_binomial_heap_tag>;
  using thin = __gnu_pbds::priority_queue<int, greater<int>, thin_heap_tag>;
  print_invalidation_guarantee<pairing>();
  print_invalidation_guarantee<binary>();
  print_invalidation_guarantee<binomial>();
  print_invalidation_guarantee<rc_binomial>();
  print_invalidation_guarantee<thin>();
  return 0;
}
```
