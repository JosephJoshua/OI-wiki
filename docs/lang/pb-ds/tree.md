## `__gnu_pbds::tree`

See also: [Official documentation](https://gcc.gnu.org/onlinedocs/libstdc++/ext/pb_ds/tree_based_containers.html)

```cpp
#include <ext/pb_ds/assoc_container.hpp>  // tree is defined here, so this header is needed
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
__gnu_pbds::tree<Key, Mapped, Cmp_Fn = std::less<Key>, Tag = rb_tree_tag,
                 Node_Update = null_tree_node_update,
                 Allocator = std::allocator<char>>
```

## Template parameters

-   `Key`: the type of the stored elements. If you want to store several equal `Key` elements, use something like `std::pair` or a `struct`, and search with the `lower_bound` and `upper_bound` member functions
-   `Mapped`: the mapping policy (Mapped-Policy) type. To make the associative container a **set**, storing elements like `std::set` does, put `null_type` here (in older versions of `g++` it is `null_mapped_type`). To make it a **set with values**, storing elements like `std::map` does, put the `Value` type here, as in `std::map<Key, Value>`
-   `Cmp_Fn`: the key comparison functor, for example `std::less<Key>`
-   `Tag`: chooses the underlying data structure. The default is `rb_tree_tag`. `__gnu_pbds` provides three different balanced trees:
    -   `rb_tree_tag`: red-black tree. This is the one you normally use; the other two usually perform worse than the red-black tree
    -   `splay_tree_tag`: splay tree
    -   `ov_tree_tag`: ordered-vector tree. It is just an ordered structure built on `vector`, like implementing a balanced tree with a sorted `vector`. Its performance depends on whether the test data is out to get you
-   `Node_Update`: the policy for updating nodes. The default is `null_node_update`. To use the `order_of_key` and `find_by_order` methods, you need `tree_order_statistics_node_update`
-   `Allocator`: the memory allocator type

## Construction

```cpp
__gnu_pbds::tree<std::pair<int, int>, __gnu_pbds::null_type,
                 std::less<std::pair<int, int>>, __gnu_pbds::rb_tree_tag,
                 __gnu_pbds::tree_order_statistics_node_update>
    trr;
```

## Member functions

-   `insert(x)`: inserts an element `x` into the tree and returns `std::pair<point_iterator, bool>`. The first item is an iterator to the inserted position, and the second item says whether the insertion succeeded.
-   `erase(x)`: removes an element/iterator `x` from the tree. If `x` is an iterator, it returns an iterator to the element after `x` (or `end()` if `x` is `end()`). If `x` is a `Key`, it returns whether the removal succeeded (it fails if the element does not exist).
-   `order_of_key(x)`: returns the number of elements strictly less than `x` (using `Cmp_Fn` for comparison), that is, its rank counting from $0$.
-   `find_by_order(x)`: returns an iterator to the element with the given rank under `Cmp_Fn`.
-   `lower_bound(x)`: returns an iterator to the first element not less than `x` (using `Cmp_Fn` for comparison).
-   `upper_bound(x)`: returns an iterator to the first element strictly greater than `x` (using `Cmp_Fn` for comparison).
-   `join(x)`: merges tree `x` into the current tree and empties tree `x` (the two trees must have the same **comparison function** and **element type**).
-   `split(x,b)`: compares with `Cmp_Fn`; elements less than or equal to `x` stay in the current tree, and the rest go to tree `b`.
-   `empty()`: returns whether the tree is empty.
-   `size()`: returns the size.

???+ warning "Note"
    `join(x)` requires that the key range of the tree being merged in and the key range of the current tree **do not overlap** (that is, every value in the merged tree must be greater than, or less than, every value in the current tree). Otherwise it throws a `join_error` exception.
    
    To merge two trees whose value ranges overlap, you have to insert the elements of one tree into the other one by one.

## Example

```cpp
// Common Header Simple over C++11
#include <iostream>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
__gnu_pbds::tree<pair<int, int>, __gnu_pbds::null_type, less<pair<int, int>>,
                 __gnu_pbds::rb_tree_tag,
                 __gnu_pbds::tree_order_statistics_node_update>
    trr;

int main() {
  int cnt = 0;
  trr.insert(make_pair(1, cnt++));
  trr.insert(make_pair(5, cnt++));
  trr.insert(make_pair(4, cnt++));
  trr.insert(make_pair(3, cnt++));
  trr.insert(make_pair(2, cnt++));
  // elements in the tree: {(1,0), (2,4), (3,3), (4,2), (5,1)}

  auto it = trr.lower_bound(make_pair(2, 0));
  trr.erase(it);
  // elements in the tree: {(1,0), (3,3), (4,2), (5,1)}

  // print the first of the element with rank 1 among ranks 0 1 2 3
  auto it2 = trr.find_by_order(1);
  cout << (*it2).first << endl;  // output: 3

  // print its rank
  int pos = trr.order_of_key(*it2);
  cout << pos << endl;  // output: 1

  // split trr at it2
  decltype(trr) newtr;
  trr.split(*it2, newtr);
  for (auto i = newtr.begin(); i != newtr.end(); ++i) {
    cout << (*i).first << ' ';  // output: 4 5
  }
  cout << endl;

  // merge tree newtr into tree trr; newtr is emptied.
  trr.join(newtr);
  for (auto i = trr.begin(); i != trr.end(); ++i) {
    cout << (*i).first << ' ';  // output: 1 3 4 5
  }
  cout << endl;
  cout << newtr.size() << endl;  // output: 0

  return 0;
}
```

## References

-   [Tree-Based Containers](https://gcc.gnu.org/onlinedocs/libstdc++/ext/pb_ds/tree_based_containers.html)
-   [Implementation of `join` in GCC 14.1.0](https://gcc.gnu.org/onlinedocs/gcc-14.1.0/libstdc++/api/a18391_source.html#l00043)
-   [Implementation of `erase` in GCC 14.1.0](https://gcc.gnu.org/onlinedocs/gcc-14.1.0/libstdc++/api/a18211_source.html#l00043)
