## Overview

The Chtholly Tree is also known as ODT (Old Driver Tree). It originated from [CF896C](https://codeforces.com/problemset/problem/896/C).

The name refers to a technique of "maintaining same-color segments, with amortized analysis, using a balanced tree (`std::set`, `std::map`, etc.) or a linked list (`std::list`, a hand-written list, etc.)", not to one particular data structure. Its core idea is to merge each run of positions with the same value into a single node. Compared with traditional data structures such as segment trees, the Chtholly tree makes it more convenient to maintain the value of each covered interval in problems with range-assignment operations.

## Implementation (std::set)

### Node type

```cpp
struct Node_t {
  int l, r;
  mutable int v;

  Node_t(const int &il, const int &ir, const int &iv) : l(il), r(ir), v(iv) {}

  bool operator<(const Node_t &o) const { return l < o.l; }
};
```

Here, `int v` is the extra data you choose to attach.

???+ note "What does the `mutable` keyword mean?"
    `mutable` means "changeable". It lets us change the value of `v` in later operations. In C++, mutable exists to get around the restrictions of const. A variable marked mutable (mutable can only be applied to non-static data members of a class) is always modifiable, even inside a const function.
    
    This means we can directly change the `v` value of an element already inserted into a `set`, without taking the element out and inserting it into the `set` again.

### Node storage

We want to maintain all nodes so that the left endpoints of their intervals are increasing and the intervals are pairwise disjoint. Ideally, the union of all intervals should be one maximal contiguous range. Here we use `std::set` as an example and maintain all nodes in a `set<Node_t> odt;`.

At initialization, insert one very long interval into the Chtholly tree (for example, if the problem asks you to maintain positions $1$ to $n$, insert the interval $[1,n+1]$).

### The split operation

The `split` operation is the core of the Chtholly tree. It takes a position $x$, splits the interval that contains $x$ (say $[l, r]$) into two intervals $[l, x)$ and $[x, r]$, and returns an iterator to the second one.

Reference code:

```cpp
auto split(int x) {
  auto it = odt.lower_bound(Node_t(x, 0, 0));
  if (it != odt.end() && it->l == x) return it;
  --it;
  int l = it->l, r = it->r, v = it->v;
  odt.erase(it);
  odt.insert(Node_t(l, x - 1, v));
  return odt.insert(Node_t(x, r, v)).first;
}
```

On compilers that do not support return type deduction with `auto`, you can change the return type to `set<Node_t>::iterator`.

### The assign operation

Another important operation is `assign`, which assigns a value to a whole interval. Suppose we want to set the interval $[l,r]$ to $v$.

First, cut out the interval $[l, r]$. Call `split(r + 1), split(l)` in that order, and call the returned iterators $itr, itl$. Then the iterator range $[itl, itr)$ covers all the intervals of the Chtholly tree contained in $[l,r]$.

Next, delete the old information. `std::set` has a member function `erase` with the signature `iterator erase( const_iterator first, const_iterator last );`, which removes the elements in the range `[first; last)`. So we call `odt.erase(itl, itr);` to delete the old information.

Finally, insert the new value for the interval $[l,r]$ by calling `odt.insert(Node_t(l, r, v))`.

Reference code:

```cpp
void assign(int l, int r, int v) {
  auto itr = split(r + 1), itl = split(l);
  odt.erase(itl, itr);
  odt.insert(Node_t(l, r, v));
}
```

???+ note "Why must we call `split(r + 1)` before `split(l)`?"
    1.  `std::set::erase` invalidates references and iterators to the erased elements. Other references and iterators are not affected.
    2.  `std::set::insert` does not invalidate any iterators or references.
    3.  The `split` operation breaks intervals apart. After calling `split(r + 1)`, $r + 1$ becomes the left endpoint of the right one of the two new intervals. When we then `split` on the left, we will never touch the interval whose left endpoint is $r + 1$, so we will not break it apart, which would delete the interval starting at $r + 1$ and invalidate the iterator. On the other hand, if we call `split(l)` first and then `split(r + 1)`, the interval with left endpoint $l$ might be deleted, invalidating its iterator.

### The perform operation

This extracts an interval from the Chtholly tree and operates on it. It is similar to `assign`, except that instead of deleting the intervals, we iterate over them.

Reference code:

```cpp
void perform(int l, int r) {
  auto itr = split(r + 1), itl = split(l);
  for (; itl != itr; ++itl) {
    // Perform Operations here
  }
}
```

Note that you should not overuse this kind of extraction, or the time complexity may become wrong. See the "Complexity analysis" section below.

## Implementation (std::map)

Compared with the `std::set` implementation, the `split` operation is simpler to write with `std::map`. Apart from that, the other operations are no different from the `std::set` version.

### Node storage

Since the intervals stored in a Chtholly tree are contiguous, we do not have to record the right endpoints. We can use a `map<int, int> mp;` to store all intervals. The key is the left endpoint, and the value is the value of the range from that left endpoint up to just before the next left endpoint.

At initialization, if the problem asks you to maintain positions $1$ to $n$, call `mp[1] = -1, mp[n + 1] = -1`. This sets $[1,n+1)$, that is $[1, n]$, to the special value $-1$. The interval $[n+1, +\infty)$ is used as a sentinel, and it can also be initialized.

### The split operation

Reference code (version 1):

```cpp
void split(int x) {
  auto it = prev(mp.upper_bound(x));  // find the interval whose left endpoint is <= x.
  mp[x] = it->second;  // create a new interval and copy the previous interval's value to it.
}
```

Reference code (version 2):

```cpp
auto split(int pos) {
  auto it = prev(mp.upper_bound(pos));  // find the interval whose left endpoint is <= x.
  return mp.insert(it, make_pair(pos, it->second));
  // create a new interval and copy the previous interval's value to it.
}
```

This uses the overload `iterator insert( const_iterator pos, const value_type& value );` of `std::map::insert`, which inserts `value` as close as possible to the position just before `pos`. If the insertion happens exactly just before `pos`, the complexity is amortized constant; otherwise it is logarithmic in the size of the container.

### The assign operation

For assign, we need to delete all left endpoints in $[l,r−1]$ and then create the new interval.

```cpp
void assign(int l, int r, int v) {  // note: r here is the right endpoint of the interval + 1
  split(l);
  split(r);
  auto it = mp.find(l);
  while (it->first != r) {
    it = mp.erase(it);
  }
  mp[l] = v;
}
```

### The perform operation

```cpp
void perform(int l, int r) {  // note: r here is the right endpoint of the interval + 1
  split(l);
  split(r);
  auto it = mp.find(l);
  while (it->first != r) {
    // Perform Operations here
    it = next(it);
  }
}
```

## Implementation (linked list)

The mainstream implementation today uses `set` to maintain the nodes. But since the number of intervals maintained is small on average, `set` does not have a clear advantage. In comparison, a linked list (or an array) can handle splitting and merging more simply.

### Node storage

```cpp
using i64 = int64_t;

struct Block {
  Block *next;  // next node in the list
  int l, r;     // interval range
  i64 val;      // value on the interval

  Block(Block *next, int l, int r, i64 val)
      : next(next), l(l), r(r), val(val) {}

  bool operator<(const Block &b) const { return val < b.val; }
} *root;
```

### The split operation

```cpp
// return the interval whose left endpoint is mid+1
Block *split(int mid) {
  for (Block *b = root; b; b = b->next) {  // traverse the list
    if (b->l == mid + 1) {                 // left endpoint is mid+1
      return b;
    }
    // find the interval [l, r] containing both mid and mid+1, and split it into [l, mid] and [mid+1,
    // r]
    if (b->l <= mid && mid + 1 <= b->r) {
      b->next = new Block(b->next, mid + 1, b->r, b->val);
      b->r = mid;
      return b->next;
    }
  }
  return nullptr;  // not found, return null
}
```

Since we cannot maintain only part of an interval, each of the operations below must split the intervals first and then do its work.

```cpp
Block *lb, *rb;

// split in advance so that later operations stay inside [l, r]
void prepare(int l, int r) {
  lb = split(l - 1);
  rb = split(r);
}
```

### The assign operation

```cpp
void assign(int l, int r, i64 val) {
  prepare(l, r);
  lb->r = r;  // change the interval [lb.l, lb.r] into [lb.l, r]
  lb->val = val;
  lb->next = rb;  // link [lb.l, r] to the adjacent interval on its right
}

// Note: the memory of the deleted nodes is not freed here; add that yourself if needed
```

### The perform operation

```cpp
void perform(int l, int r) {
  prepare(l, r);
  for (Block *b = lb; b != rb; b = b->next) {
    // Perform Operations here
  }
}
```

## Complexity analysis

### Calling assign on the same interval right after perform

Observe that the two `split` operations add at most two intervals. One `assign` deletes all intervals in the range and adds one interval, while traversing the deleted intervals. So the number of intervals we traverse is linear in the number we delete, and each operation adds only $O(1)$ intervals. Therefore the number of intervals we operate on is linear in the number of operations (including initialization), and the time complexity is amortized $O(m\log n)$, where $m$ is the number of operations and $n$ is the maximum number of intervals in the Chtholly tree (we can assume $n\leq m$).

### Not calling assign after perform

If the test data can be specially constructed, this will definitely be broken. The data just needs to create enough distinct intervals in the Chtholly tree and traverse them repeatedly, and the complexity of the Chtholly tree reaches quadratic or even worse.

To guarantee correct complexity, the data must be random. See [the proof of the Chtholly tree's complexity on Codeforces](http://codeforces.com/blog/entry/56135?#comment-398940). For a more detailed, rigorous proof, see [Complexity Analysis of the Chtholly Tree](https://zhuanlan.zhihu.com/p/102786071). The conclusion is: a Chtholly tree implemented with `std::set` runs in $O(n \log \log n)$, while one implemented with a linked list runs in $O(n \log n)$.

## Exercises

-   [Luogu 1840 — Color the Axis](https://www.luogu.com.cn/problem/P1840)
-   ~~[SCOI2010 — Sequence Operations](https://www.luogu.com.cn/problem/P2572)~~ (hack data has been added to this problem at its source)
-   [SHOI2015 — Brain Hole Treatment Device](https://loj.ac/problem/2037)
-   [Luogu 4979 — Mine Tunnel: Collapse](https://www.luogu.com.cn/problem/P4979)
-   [Luogu 8146 — risrqnis](https://www.luogu.com.cn/problem/P8146)

## Further reading

[Generalizing the Mapping Idea of ODT - Luogu Column (luogu.com.cn)](https://www.luogu.com.cn/article/0mys9qkh)

## References and notes

-   [Problem - 896C - Codeforces](https://codeforces.com/problemset/problem/896/C) (the origin of the Chtholly tree)
-   [CF896C Willem, Chtholly and Seniorious Editorial - Luogu Column (luogu.com.cn)](https://www.luogu.com.cn/article/gyxbe23s) (reference for the `std::set` implementation)
-   [The map Implementation of the Chtholly Tree - Zhihu (zhihu.com)](https://zhuanlan.zhihu.com/p/469794466) (reference for the `std::map` implementation)
-   [Editorial for CF896C "Willem, Chtholly and Seniorious" - Luogu Column (luogu.com.cn)](https://www.luogu.com.cn/article/umiw1fwp) (reference for the linked-list implementation)
-   [Codeforces Round #449 Editorial - Codeforces](https://codeforces.com/blog/entry/56135?#comment-398940) (proof of the Chtholly tree's complexity)
-   [Complexity Analysis of the Chtholly Tree - Zhihu (zhihu.com)](https://zhuanlan.zhihu.com/p/102786071) (complexity analysis of the Chtholly tree)
