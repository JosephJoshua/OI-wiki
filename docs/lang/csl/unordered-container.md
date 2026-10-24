## Overview

Since C++11, four unordered associative containers based on [hashing](../../ds/hash.md) have been part of the C++ standard library: `unordered_set`, `unordered_multiset`, `unordered_map` and `unordered_multimap`.

??? note "Usage when the compiler does not support C++11"
    Before C++11, the unordered associative containers were part of the C++ TR1 extensions. So if your compiler does not support C++11, add the `tr1/` prefix to the header name and use the `std::tr1` namespace. For example, change `#include <unordered_map>` to `#include <tr1/unordered_map>`, and change `std::unordered_map` to `std::tr1::unordered_map` (or `tr1::unordered_map` if you use `using namespace std;`).

They have a lot in common with the corresponding associative containers in features, member functions and so on. The biggest difference is this: the ordinary associative containers are usually implemented with red-black trees, and their elements are kept sorted in a specific order; the unordered associative containers store elements by hashing, and their elements are not sorted in any particular order, so there is no guarantee about the order in which you visit them.

Because they use hashing, the unordered associative containers can do most operations (including lookup, insertion and deletion) in constant time **on average**. This is better than the associative containers, whose time complexity is logarithmic in the container size.

??? warning "Warning"
    In the worst case, insertion, deletion, lookup and other operations on an unordered associative container take time **linear in the container size**! This usually happens when there are many hash collisions in the container.
    
    Also, operations on unordered associative containers usually have a large constant factor, so they are sometimes not much faster than the ordinary associative containers.
    
    So use the unordered associative containers with care and avoid overusing them (for example, skipping coordinate compression out of laziness and using `unordered_map<int, int>` as an ordinary array with unlimited space).

Since the unordered associative containers share many uses and operations with the corresponding associative containers, we do not cover their operations here. See [Associative containers](./associative-container.md) for those.

## Creating hash collisions

As mentioned above, in the worst case some operations on an unordered associative container take time linear in the container size.

When the hash function is fixed, one can construct data that causes many hash collisions in the container, so the complexity reaches its upper bound.

In the standard library implementation, each element's hash value is the value taken modulo a prime. More precisely, the primes come from [this list](https://github.com/gcc-mirror/gcc/blob/releases/gcc-8.1.0/libstdc%2B%2B-v3/src/shared/hashtable-aux.cc) (with g++ 6 and earlier, this prime is usually $126271$; with g++ 7 and later, it is usually $107897$).

So inserting multiples of these moduli into the container produces a large number of hash collisions.

## Custom hash functions

A custom hash function is an effective way to avoid the many hash collisions caused by constructed data.

To use a custom hash function, define a struct and overload the `()` operator in it, like this:

```cpp
struct my_hash {
  size_t operator()(int x) const { return x; }
};
```

Of course, to make sure the hash function is not broken quickly (for example, when someone hacks a Codeforces submission that uses unordered associative containers), you can add some randomization (such as the current time) to the hash function to make it harder to break.

For example, [this blog post](https://codeforces.com/blog/entry/62393) gives the following hash function:

```cpp
struct my_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM =
        chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }

  // hash function for std::pair<int, int> as the key type
  size_t operator()(pair<uint64_t, uint64_t> x) const {
    static const uint64_t FIXED_RANDOM =
        chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x.first + FIXED_RANDOM) ^
           (splitmix64(x.second + FIXED_RANDOM) >> 1);
  }
};
```

After writing the custom hash function, you can pass it to the container with a definition like `unordered_map<int, int, my_hash> my_map;` or `unordered_map<pair<int, int>, int, my_hash> my_pair_map;`.
