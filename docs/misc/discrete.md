author: GavinZhengOI, PlanariaIce

## Introduction

Discretization (coordinate compression) is a data-processing technique. In essence it can be seen as a kind of [hashing](../string/hash.md#the-idea-of-hashing) that guarantees the data keeps its original [total/partial order](../math/order-theory.md#partially-ordered-sets) relation after hashing.

Put simply: sometimes the values are too large, or of a type that cannot be used directly as an array index, so they are awkward to handle. If the final result only depends on the relative order of the elements, we can replace each value by its rank and work with ranks instead. This is discretization.

You can discretize big integers, floating-point numbers, strings, and so on.

## Implementation

A common use case is to discretize an array and then answer queries on it.

### Method 1

The original array usually contains duplicate elements. Normally equal elements are mapped to the same value.

The method is as follows:

1.  Make a copy of the original array.

2.  Sort the values in the copy from smallest to largest.

3.  Remove duplicates from the sorted copy.

4.  For each element of the original array, find its position in the copy. The position is its rank, and we use it as the discretized value.

```cpp
// arr[i] is the original array, with indices in [1, n]

for (int i = 1; i <= n; ++i)  // step 1
  tmp[i] = arr[i];
std::sort(tmp + 1, tmp + n + 1);                          // step 2
int len = std::unique(tmp + 1, tmp + n + 1) - (tmp + 1);  // step 3
for (int i = 1; i <= n; ++i)                              // step 4
  arr[i] = std::lower_bound(tmp + 1, tmp + len + 1, arr[i]) - tmp;
```

For the STL algorithms used in the reference implementation, see [STL algorithms](../lang/csl/algorithm.md).

In the same way, we can also discretize a [std::vector](../lang/csl/sequence-container.md#vector):

```cpp
// std::vector<int> arr;
std::vector<int> tmp(arr);  // tmp is a copy of arr
std::sort(tmp.begin(), tmp.end());
tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());
for (int i = 0; i < n; ++i)
  arr[i] = std::lower_bound(tmp.begin(), tmp.end(), arr[i]) - tmp.begin();
```

### Method 2

Depending on the problem, equal elements sometimes need to be mapped to different values according to their input order.

In this case, using `std::lower_bound()` becomes awkward, so we need a different approach:

1.  Make a copy of the original array, and record the position of each element.

2.  Sort the copy by value from smallest to largest. When values are equal, sort by position from smallest to largest.

3.  Put the discretized numbers back into the original array.

```cpp
struct Data {
  int idx, val;

  bool operator<(const Data& o) const {
    if (val == o.val)
      return idx < o.idx;  // for equal values, the element that appears first gets the smaller discretized value
    return val < o.val;
  }
} tmp[MAXN];  // std::pair also works

for (int i = 1; i <= n; ++i) tmp[i] = Data{i, arr[i]};
std::sort(tmp + 1, tmp + n + 1);
for (int i = 1; i <= n; ++i) arr[tmp[i].idx] = i;
```

### Complexity

For Method 1, removing duplicates takes $O(n)$, sorting takes $O(n \log n)$, and the final $n$ lookups take $O(n \log n)$.

For Method 2, sorting takes $O(n \log n)$.

So both methods have a total time complexity of $O(n \log n)$.

The space complexity is $O(n)$.

## Exercises

-   [\[HAOI2014\] Posters](https://www.luogu.com.cn/problem/P3740)
-   [\[NOI2015\] Automatic Program Analysis](https://www.luogu.com.cn/problem/P1955)
