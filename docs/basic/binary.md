This page gives a short introduction to binary search, binary search on the answer, and ternary search, which grows out of the idea of binary search.

## Binary search

Binary search, also called half-interval search or logarithmic search, is an algorithm for finding an element in a sorted sequence.

### How it works

Take searching for a number in an array sorted in ascending order as an example.

At each step, the algorithm looks at the middle element of the part of the array still under consideration. If the middle element is the one we want, the search ends. If the middle element is smaller than the target, then every element to its left is no larger than the middle element, so none of them can be the target, and we only need to search the right side. If the middle element is larger than the target, the same reasoning applies, and we only need to search the left side.

More precisely, let the array $a$ be indexed from $1$ with length $n$, and suppose we want to find the position of the number $x$. Let $l,r$ mean that we currently only consider elements whose index $i$ satisfies $l\le i\le r$. At the start, set $l\gets1$ and $r\gets n$. Each time, look at the middle element $a_{\textit{mid}}$, where $\textit{mid}=\left\lfloor\dfrac{l+r}{2}\right\rfloor$, and handle the cases:

-   If $a_{\textit{mid}}<x$: since the array is ascending, every element with index at most $\textit{mid}$ is smaller than $x$. So we never need to look at them again, and only need to search indices greater than $\textit{mid}$. That is, set $l\gets \textit{mid}+1$ and leave $r$ unchanged.
-   If $a_{\textit{mid}}>x$: since the array is ascending, every element with index at least $\textit{mid}$ is larger than $x$. So we never need to look at them again, and only need to search indices less than $\textit{mid}$. That is, leave $l$ unchanged and set $r\gets \textit{mid}-1$.
-   If $a_{\textit{mid}}=x$: we have found the position of $x$, and the algorithm ends.

If the range under consideration becomes empty, that is, $l>r$, without finding $x$, then $x$ is not in the array $a$.

### Properties

#### Time complexity

The best-case time complexity of binary search is $O(1)$.

The average-case and worst-case time complexities of binary search are both $O(\log n)$. The algorithm halves the search range at every step, so for an array of length $n$ it makes at most $O(\log n)$ comparisons with the target.

#### Space complexity

The iterative version of binary search uses $O(1)$ space.

The recursive version (without tail call elimination) uses $O(\log n)$ space.

### Implementation

```cpp
int binary_search(int x, int l = 1, int r = n) {  // find the index of x in an ascending array
  int ret = -1;                                   // return -1 if not found
  while (l <= r) {
    int mid = (l + r) >> 1;  // l + r may overflow, see the Note below
    if (a[mid] < x)
      l = mid + 1;
    else if (a[mid] > x)
      r = mid - 1;
    else {  // check equality last, since most comparisons are either greater or less
      ret = mid;
      break;
    }
  }
  return ret;
}
```

???+ note "Note"
    -   As explained in [Compiler optimizations #Shifts instead of multiplication](../lang/optimizations.md#移位代替乘法), when $s$ is a signed number and you can guarantee $s\ge 0$, `s >> 1` takes fewer instructions than `s / 2`.
    
    -   When $l$ or $r$ is very large, $l+r$ may overflow. If $r-l$ does not overflow in that case, you can replace `(l + r) >> 1` in the code with `l + ((r - l) >> 1)`.

???+ warning "Warning"
    When $s$ is a negative odd number, `s >> 1` and `s / 2` differ by $1$. This is because the former rounds toward negative infinity (standardized in C++20; implementation-defined before that), while the latter rounds toward zero. See [C++ bitwise operators](../lang/op.md#位操作符) for details. So when $l + r$ may be negative, `(l + r) / 2` may equal $r$, which leads to an **infinite loop** in code that uses `r = mid`. For example, when $l = -1,~r = 0$, `(l + r) / 2` equals $0$. Keep this difference in mind when writing code.

### bsearch

The `bsearch` function is the C standard library's binary search, defined in `<stdlib.h>`. In the C++ standard library, it is defined in `<cstdlib>`. qsort and `bsearch` are the only two algorithm-style functions in the C standard library.

Compared with the four parameters of qsort ([STL for sorting](./stl-sort.md)), `bsearch` adds one more parameter on the far left: "the address of the element to search for". It is passed as an address so that you can reuse the same comparison function as qsort, which makes it easy to search right after sorting. Because of this, you cannot pass the value directly. Instead, store the value in a variable first, then pass the variable's address.

So `bsearch` takes five parameters in total: the address of the element to search for, the starting address of the array, the number of elements, the size of each element, and the comparison rule. The comparison rule is still given by a comparison function; see [STL for sorting](./stl-sort.md) for details.

`bsearch` returns the address of the element it found, with return type `void *`.

Note: `bsearch` differs from `std::lower_bound` and `std::upper_bound`, introduced below, in two ways:

-   When several elements match, which one is returned is unspecified.
-   When no matching element is found, it returns `NULL`.

`lower_bound` can do almost the same job as `bsearch` (it becomes exactly the same once you add a special check for the not-found case). So any problem that can be solved with `bsearch` can also be solved by rewriting it with `lower_bound`.

## Binary search on the answer

Binary search on the answer is a technique that uses a generalized ordering property of a problem's answer (often just called monotonicity) to find the answer quickly, in a way similar to binary search.

Unless stated otherwise, binary search on the answer usually means the integer version, that is, we know the answer must be an integer.

Problems that can be solved with binary search on the answer usually look like "find the largest (smallest) value satisfying condition $P$", and have the following properties:

1.  Given any number $x$, it is easy to check whether $x$ satisfies the condition;
2.  We can set rough lower and upper bounds for the answer, that is, find $L$ and $R$ such that if an answer $x$ exists, it must satisfy $L\le x \le R$;
3.  The range between these rough bounds is so large that checking every value one by one would be too slow;
4.  Condition $P$ has a generalized ordering property.

Suppose there is a function $f(x)$ such that $f(x)=1$ if and only if $x$ satisfies condition $P$, and $f(x)=0$ otherwise. Then the generalized ordering property of condition $P$ can be defined as follows:

-   For any $L\le i<j \le R$, $f(i)\le f(j)$, that is, $f(x)$ is non-decreasing. If you write $f(i)$ for $i=L,\dots,R$ as a 0/1 sequence, it looks like `00...011...1`. In this case, binary search on the answer finds the **minimum** value satisfying condition $P$.

-   For any $L \le i<j \le R$, $f(i)\ge f(j)$, that is, $f(x)$ is non-increasing. The 0/1 sequence looks like `11...100...0`. In this case, binary search on the answer finds the **maximum** value satisfying condition $P$.

In other words, the first ordering property means: if we know $x$ satisfies condition $P$, then every number larger than $x$ also satisfies $P$. Binary search on the answer finds the $x$ such that "every number smaller than it fails $P$, while it and every number larger than it satisfy $P$".

The second ordering property means: if we know $x$ satisfies condition $P$, then every number smaller than $x$ also satisfies $P$. Binary search on the answer finds the $x$ such that "it and every number smaller than it satisfy $P$, while every number larger than it fails $P$".

### How it works

Take finding the minimum with binary search on the answer as an example (here the problem must have the first ordering property described above). Let the rough lower and upper bounds of the answer be $L$ and $R$.

Let $l,r$ mean that we currently know the answer $x$ satisfies $l \le x \le r$. As in binary search, start with $l\gets L$ and $r\gets R$. Each time, check whether $\textit{mid}=\left\lfloor\dfrac{l+r}{2}\right\rfloor$ satisfies condition $P$, and handle the cases:

-   If $\textit{mid}$ fails the condition (that is, $f(\textit{mid})$ is $0$), then by the ordering property, no number less than or equal to $\textit{mid}$ satisfies the condition, so we can skip all of them. Set $l\gets \textit{mid}+1$ and leave $r$ unchanged.
-   If $\textit{mid}$ satisfies the condition (that is, $f(\textit{mid})$ is $1$), then by the ordering property, every number greater than or equal to $\textit{mid}$ satisfies the condition. But since we want the minimum, there is no need to consider numbers greater than $\textit{mid}$; we only need numbers less than or equal to $\textit{mid}$. Set $r \gets \textit{mid}$ and leave $l$ unchanged.

The algorithm ends when the range satisfies $l=r$ (that is, $l<r$ no longer holds). At that point, $l$ (or $r$) is the answer.

Note: if no answer exists within the bounds (what is usually called "no solution"), every query of $f(\textit{mid})$ returns $0$, so after the algorithm ends we have $l=r=R$ and $f(l)=0$. So if you need to detect the no-solution case, just check whether $f(l)$ equals $0$.

As in binary search, the algorithm halves the search range at each step, so its time complexity is $O(M \log (R-L+1))$, where $M$ is the time needed to check whether $\textit{mid}$ satisfies condition $P$.

### Implementation

Based on the description above, here is an implementation:

```cpp
// Find the smallest integer x in [L, R] satisfying condition P; requires L <= R
// Condition P must have the first ordering property, i.e. f(x) is non-decreasing
// In code, usually check(x) = f(x)
// Return -1 if there is no solution in the range
int binary_search_min(int L, int R) {
  if (L > R) return -1;
  int l = L, r = R;
  while (l < r) {
    int mid = (l + r) >> 1;
    if (check(mid))  // f(mid) = 1, condition P holds
      r = mid;       // the answer is in [l, mid]
    else
      l = mid + 1;  // the answer is in [mid + 1, r]
  }
  // now l == r
  if (!check(l)) return -1;  // check for no solution
  return l;
}
```

When you use `-1` to mean "no solution", make sure it cannot be confused with a valid answer.

### Implementation details

When reading solutions, you may see another way to write it:

```cpp
// Find the smallest integer x in [L, R] satisfying check(x)
// Requires check to be non-decreasing on [L, R]
// Return -1 if the range is empty or has no solution
int binary_search_min(int L, int R) {
  if (L > R) return -1;
  int l = L, r = R;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (check(mid))
      r = mid - 1;
    else
      l = mid + 1;
  }

  if (l > R) return -1;
  return l;
}
```

These two versions give the same answer, but they maintain different loop invariants.

??? note "Why do both versions find the smallest feasible value?"
    First assume $[L,R]$ is non-empty and contains an answer. Let $\textit{ans}$ be the smallest number satisfying condition $P$. Since $f$ is non-decreasing, on the original range $[L,R]$ we have
    
    $$
    f(x)=0\quad (x<\textit{ans}),\qquad
    f(x)=1\quad (x\ge \textit{ans}).
    $$
    
    **The `l < r` version keeps the answer inside a closed interval.**
    
    The invariant it maintains is
    
    $$
    l\le \textit{ans}\le r.
    $$
    
    Each step takes $\textit{mid}=\left\lfloor\dfrac{l+r}{2}\right\rfloor$. If $f(\textit{mid})=1$, then $\textit{ans}\le\textit{mid}$, so set $r\gets\textit{mid}$; if $f(\textit{mid})=0$, then $\textit{ans}>\textit{mid}$, so set $l\gets\textit{mid}+1$. Both updates keep the invariant.
    
    When $l<r$, we have $l\le\textit{mid}<r$, so every iteration strictly shrinks the range. When the loop ends, $l=r$, and by the invariant, $\textit{ans}=l$.
    
    **The `l <= r` version throws away the parts already decided, and the answer may sit just past the right boundary.**
    
    The invariant it maintains is: within the original range $[L,R]$, every $x<l$ has $f(x)=0$, and every $x>r$ has $f(x)=1$. Given that an answer exists, this means
    
    $$
    l\le \textit{ans}\le r+1.
    $$
    
    If $f(\textit{mid})=1$, then every $x\ge\textit{mid}$ in the original range has $f(x)=1$, so we can set $r\gets\textit{mid}-1$; if $f(\textit{mid})=0$, then every $x\le\textit{mid}$ in the original range has $f(x)=0$, so we can set $l\gets\textit{mid}+1$.
    
    Each iteration removes at least one integer from the range still to be searched, so the loop eventually ends.
    
    While the loop runs, $l\le\textit{mid}\le r$. If we do $r\gets\textit{mid}-1$, the new right boundary satisfies $r\ge l-1$; if we do $l\gets\textit{mid}+1$, the new left boundary satisfies $l\le r+1$. So whichever update happens, $l\le r+1$ holds afterward. The loop ends when $l>r$, and since the boundaries are integers, we must then have $l=r+1$. Combined with the invariant on the answer's position, $l\le\textit{ans}\le r+1$, we get $\textit{ans}=l$.
    
    Note: the range still to be searched, $[l,r]$, does not always contain the answer. For example, if this round happens to pick $\textit{mid}=\textit{ans}$, then after $r\gets\textit{mid}-1$ we have $\textit{ans}=r+1$. The answer is no longer inside $[l,r]$, but it still satisfies the invariant $l\le\textit{ans}\le r+1$, so the correctness proof above is not affected.
    
    **When there is no solution, the two versions stop at different positions.**
    
    For the `l <= r` version, if $l\le R$ after the loop ends, then since the left boundary always satisfies $l\ge L$, $l$ lies inside the original range. Then from $l=r+1$ and the invariant "every $x>r$ in the original range has $f(x)=1$", we get $f(l)=1$, so there is no need to call `check(l)` again.
    
    If there is no solution, we end with $l=R+1$, which is outside the original search range. Since we only require `check` to be usable on $[L,R]$, we should check `l > R` first, and must not call `check(l)` directly to decide whether a solution exists.
    
    For the `l < r` version, recall from the earlier description that if there is no solution in the range, we end with $l=r=R$. We then need an extra check of whether `check(l)` is $0$ to tell apart "the answer is $R$" from "no solution in the range".
    
    In summary, given $L\le R$ and $f$ non-decreasing on $[L,R]$, both versions finish after a finite number of iterations. If a feasible value exists in the range, both end with $l=\textit{ans}$ and return the smallest integer in the range that satisfies the condition. If there is no solution in the range, the `l < r` version detects it with `check(l)` after the loop, and the `l <= r` version detects it with `l > R` after the loop; both return the agreed no-solution marker. For an empty range with $L>R$, both pieces of code return the no-solution marker right away, before entering the loop. So although the two implementations maintain different loop invariants and stop at different positions, both correctly answer the "smallest feasible value" query and return the same result.

These two versions show that whether a binary search implementation is correct depends on how the meaning of the boundaries, the loop invariant, the loop condition and the update rules fit together. Just looking at whether the endpoints are included, or whether the loop uses `l < r` or `l <= r`, is not enough to tell whether an implementation is correct.

To prove an implementation correct, you need to confirm that:

1.  The initialization satisfies the loop invariant.
2.  Every update keeps the invariant and strictly reduces the number of integers in the range still to be searched, so the loop eventually ends.
3.  When the loop ends, the invariant and the stopping condition together show that the return value is the answer; if "no solution" is possible, you also need to explain how to detect it.

When discussing implementations, be careful to tell apart "the range still to be searched" from "the range guaranteed to contain the final answer". Because boundary conditions differ, the two are not always the same, and you cannot always require the answer to stay inside the range still to be searched.

Below are several common ways to write it. All of them assume $L\le R$, that the problem has the first ordering property, and that the smallest feasible value $\textit{ans}$ exists. Where the answer lies is given by the "Invariant on answer position" column.

| Version                     | Initial $l,r$        | Loop condition     | $\textit{mid}$                            | When $f(\textit{mid})=1$  | When $f(\textit{mid})=0$  | Invariant on answer position                   | At the end     | Return  |
| ---------------------- | --------------- | -------- | ----------------------------------------- | ---------------------- | ---------------------- | ------------------------- | ------- | --- |
| Closed interval $[l,r]$, discard decided parts    | $l=L,\ r=R$     | $l\le r$ | $\left\lfloor\dfrac{l+r}{2}\right\rfloor$ | $r\gets\textit{mid}-1$ | $l\gets\textit{mid}+1$ | $l\le\textit{ans}\le r+1$ | $l=r+1$ | $l$ |
| Closed interval $[l,r]$, keep the answer       | $l=L,\ r=R$     | $l<r$    | $\left\lfloor\dfrac{l+r}{2}\right\rfloor$ | $r\gets\textit{mid}$   | $l\gets\textit{mid}+1$ | $l\le\textit{ans}\le r$   | $l=r$   | $l$ |
| Half-open interval $[l,r)$, discard decided parts | $l=L,\ r=R+1$   | $l<r$    | $\left\lfloor\dfrac{l+r}{2}\right\rfloor$ | $r\gets\textit{mid}$   | $l\gets\textit{mid}+1$ | $l\le\textit{ans}\le r$   | $l=r$   | $l$ |
| Half-open interval $(l,r]$, keep the answer    | $l=L-1,\ r=R$   | $l+1<r$  | $\left\lfloor\dfrac{l+r}{2}\right\rfloor$ | $r\gets\textit{mid}$   | $l\gets\textit{mid}$   | $l<\textit{ans}\le r$     | $l+1=r$ | $r$ |
| Open interval $(l,r)$, maintain both boundaries     | $l=L-1,\ r=R+1$ | $l+1<r$  | $\left\lfloor\dfrac{l+r}{2}\right\rfloor$ | $r\gets\textit{mid}$   | $l\gets\textit{mid}$   | $l<\textit{ans}\le r$     | $l+1=r$ | $r$ |

A few more notes on the table:

-   In row 3, $[l, r)$ is the range still to be searched, but the answer may be exactly $r$.
-   Row 4 keeps the answer inside $(l, r]$, which relies on the initial right boundary $R$ satisfying $f(R) = 1$. While the loop runs, $r - l \ge 2$, so rows 4 and 5 are also correct if the midpoint is rounded up instead.
-   In row 5, $(l, r)$ means the positions between the two boundaries that are still undecided. You can think of the initial $L - 1$ as a virtual sentinel with value 0, and $R + 1$ as a virtual sentinel with value 1. The loop only calls the check function inside the original range, so the function never has to be evaluated at the sentinels.
-   To handle the no-solution case: rows 1, 3 and 5 can check whether the return value is $R + 1$; row 2 needs to check $f(l)$; row 4 needs to check $f(R)$ first.

### Minimizing the maximum and maximizing the minimum

Problems that ask you to minimize a maximum or maximize a minimum are classic examples that binary search on the answer can solve.

Take minimizing the maximum as an example. Usually each option comes with a set $S$ that we care about. If we want, over all options, to minimize the largest number in the option's set $S$, we can turn the problem into: find the smallest $k$ such that some option satisfies $\max(S) \le k$.

This problem has the generalized ordering property: if some option satisfies $\max(S) \le k$, then for any $i\ge k$, the same option also satisfies $\max(S)\le i$. So for $i \ge k$, some option satisfies $\max(S) \le i$, which also meets the requirement. Therefore binary search on the answer works. Maximizing the minimum works the same way.

### Binary search on the answer in the STL

#### std::lower\_bound and std::upper\_bound

The C++ standard library provides:

-   [`std::lower_bound`](https://zh.cppreference.com/w/cpp/algorithm/lower_bound), which finds the first element that is not less than a given value.
-   [`std::upper_bound`](https://zh.cppreference.com/w/cpp/algorithm/upper_bound), which finds the first element that is greater than a given value.

Both are implemented with binary search, so the elements must be sorted before calling them (here "sorted" is with respect to the comparison function described below, not necessarily sorted in the mathematical sense). Only then do their problems have the generalized ordering property (that is, for `std::lower_bound`, if $a_i$ is not less than the given value, every element after $i$ is also not less than it; for `std::upper_bound`, if $a_i$ is greater than the given value, every element after $i$ is also greater than it).

`std::lower_bound` and `std::upper_bound` both take four parameters:

-   `first`: the starting [iterator](../lang/csl/iterator.md) of the sequence, pointing to its first element.
-   `last`: the ending iterator of the sequence, pointing to the position **just past** its last element. In other words, if `last` is a bidirectional iterator, then `--last` points to the last element of the sequence.
-   `value`: the given value.
-   `comp` (optional): the comparison function, written the same way as for `sort`. Note that `std::lower_bound` calls it as `comp(element, value)`, while `std::upper_bound` calls it as `comp(value, element)`.

Both return an iterator to the matching element, of the same type as the iterators passed in. That is, if you pass in array pointers, you get back an array pointer to the matching element. If no element matches, they return `last`.

Both are defined in the header `<algorithm>`.

???+ note "Usage examples"
    -   In an array $a$ indexed from $1$ with length $n$, find the first number not less than $x$ among positions $l$ to $r$, and get its index: `lower_bound(a+l,a+r+1,x)-a`.
    -   In an array $a$ indexed from $0$ with length $n$, find the first number greater than $x$ (it must exist), and get its value: `*upper_bound(a,a+n,x)`.
    -   In a vector $a$ of length $n$, find the first number not less than $x$ and get its index (note that vector indices start at $0$): `lower_bound(a.begin(),a.end(),x)-a.begin()`.

???+ note "About iterators"
    The starting and ending iterators above must be ForwardIterators. Array pointers and the iterators of vector, set, map and string all meet this requirement.

??? note "About the time complexity"
    In libstdc++, the standard library implementation used by GCC, both functions use `std::advance` to reach the middle element. This means the functions only run in $O(\log n)$ when the iterators support random access (for example, array pointers or vector iterators). Without random access (for example, set or map), the cost is the total time spent reaching the middle elements, which is usually linear. For example, calling something like `lower_bound(st.begin(),st.end(),val)` on a set or map takes $O(n)$ time. In that case, use the member function `st.lower_bound(val)` instead.

??? note "Implementing `std::lower_bound` and `std::upper_bound` with `bsearch`"
    Since bsearch returns NULL when it cannot find the element (see [bsearch](./binary.md#bsearch)), using `bsearch` to do what `lower_bound` does becomes tricky, for example when searching for 3 in the sequence 1, 2, 4, 5, 6.
    
    To implement `std::lower_bound` and `std::upper_bound` with `bsearch`, we can use the argument convention of its comparison function: the first argument points to the element being searched for, and the second points to an element of the array. So it works as long as the comparison function knows the starting address of the array.
    
    ```cpp
    int A[100005];  // example global array
    
    // compare compares the values pointed to by two int pointers: returns a
    // positive number if *p1 > *p2, 0 if equal, and a negative number if less
    int compare(const void*, const void*);
    
    // find the address of the first element not less than the target
    int lower(const void* p1, const void* p2) {
      int* a = (int*)p1;
      int* b = (int*)p2;
      if ((b == A || compare(a, b - 1) > 0) && compare(a, b) > 0)
        return 1;
      else if (b != A && compare(a, b - 1) <= 0)
        return -1;  // uses pointer subtraction, so the element type must be specified
      else
        return 0;
    }
    
    // find the address of the first element greater than the target
    int upper(const void* p1, const void* p2) {
      int* a = (int*)p1;
      int* b = (int*)p2;
      if ((b == A || compare(a, b - 1) >= 0) && compare(a, b) >= 0)
        return 1;
      else if (b != A && compare(a, b - 1) < 0)
        return -1;  // uses pointer subtraction, so the element type must be specified
      else
        return 0;
    }
    ```
    
    Note: if the answer is the past-the-end position (for example, when the target is larger than every element), the method above still returns `NULL`, so you need to handle that case separately.
    
    Since few OI contestants write pure C nowadays and this method is of limited use, it is not a key topic. Beginners are advised to just use the C++ functions `std::lower_bound` and `std::upper_bound`.

#### std::partition\_point

C++11 introduced [`std::partition_point`](https://zh.cppreference.com/w/cpp/algorithm/partition_point). It uses binary search on the answer to quickly locate the "partition point" of an already partitioned sequence.

`std::partition_point` takes three parameters:

-   `first`, `last`: same as above.
-   `p`: a unary [predicate](../lang/csl/container.md#关联式容器). This is a callable object that takes one argument $v$ and returns a boolean saying whether $v$ meets the partition condition.

Let the sequence passed in be $a$. The function returns an iterator to the first element that does not meet the partition condition, that is, an iterator to the element with the smallest index $x$ such that $p(a_x)$ is `false`.

The sequence must already be partitioned, meaning it must have the second generalized ordering property described above. In other words, if you list $p(v)$ for every element $v$ as a 0/1 sequence, it looks like `11...100...0`, and the function returns an iterator to the position of the first $0$.

??? note "How `std::partition_point` relates to `std::lower_bound` and `std::upper_bound`"
    In fact, `std::lower_bound` and `std::upper_bound` are special cases of `std::partition_point`.
    
    Define a function `f` as: `bool f(int v) { return !(val <= v); }`. Passing `f` as the predicate to `std::partition_point` gives the same result as `std::lower_bound`. `std::upper_bound` works the same way.

### Binary search on real-valued answers

Binary search on real-valued answers, also called floating-point binary search, is binary search on the answer when the answer is a real number.

Unlike the integer version, it usually does not ask for the exact answer. Instead, it finds a real approximation that meets a given precision requirement.

#### How it works

Take finding the minimum as an example. Let the rough lower and upper bounds of the answer be $L$ and $R$. Let $l,r$ mean that we currently know the answer $x$ satisfies $l\le x\le r$. At the start, set $l\gets L$ and $r\gets R$. Each time, take $\textit{mid}=\dfrac{l+r}{2}$ (note that this is real-number arithmetic) and check whether $\textit{mid}$ satisfies condition $P$:

-   If $\textit{mid}$ satisfies the condition, then, as in the integer case, set $r\gets \textit{mid}$ and leave $l$ unchanged.
-   If $\textit{mid}$ fails the condition, then, as in the integer case, set $l\gets \textit{mid}$ and leave $r$ unchanged.

Note that, unlike the integer version, the real-valued version cannot shrink the range with `mid + 1` or `mid - 1`, because real numbers have no "neighboring" elements. You can only set a boundary equal to $\textit{mid}$ and rely on the range length halving again and again to close in on the answer.

The algorithm ends when the range length $r-l$ is at most the given precision $\textit{eps}$, or when a preset number of iterations is reached. At that point, $l$, $r$ or $\dfrac{l+r}{2}$ can all serve as an approximation of the answer (if the returned value must satisfy condition $P$, return $r$). To find the maximum instead, just flip the direction of the two cases above: if $\textit{mid}$ satisfies the condition, set $l\gets \textit{mid}$; otherwise set $r\gets \textit{mid}$ (and correspondingly, if the returned value must satisfy condition $P$, return $l$).

With `while (r - l > eps)`, binary search on real-valued answers takes $O(M \log((R-L)/\textit{eps}))$ time. With a fixed number of iterations $k$, it takes $O(Mk)$ time. Here $M$ is the time needed to check whether $\textit{mid}$ satisfies condition $P$. Because floating-point arithmetic has rounding errors, real implementations usually do not test $l=r$ directly. Instead, they test $r-l<\textit{eps}$, or just loop a fixed number of times, such as $60$ to $100$, to avoid infinite loops and guarantee precision.

#### Implementation

```cpp
double binary_search_iter(double L, double R) {  // fixed number of iterations
  double l = L, r = R;
  for (int i = 0; i < 100; ++i) {
    double mid = (l + r) / 2;
    if (check(mid))
      r = mid;
    else
      l = mid;
  }
  return r;
}

const double eps = 1e-7;  // precision; usually 1/100 of the required precision or smaller

double binary_search_eps(double L, double R) {  // eps version
  double l = L, r = R;
  while (r - l > eps) {
    double mid = (l + r) / 2;
    if (check(mid))
      r = mid;
    else
      l = mid;
  }
  return r;
}
```

???+ warning "Warning"
    `eps` should not be too large, or the precision will not be enough; it also should not be too small, or floating-point errors may keep the loop from ever reaching it, causing an infinite loop. If the answer range is very large or the required precision is very high, a fixed number of iterations is recommended over `while (r - l > eps)`.

### Example problem

???+ note "[Luogu P1873 Cutting Trees](https://www.luogu.com.cn/problem/P1873)"
    Lumberjack Mirko needs to cut down $M$ meters of wood. This is an easy job for Mirko, since he has a nice new woodcutting machine that can cut down forests like wildfire. However, Mirko is only allowed to cut a single row of trees.
    
    Mirko's machine works like this: Mirko sets a height parameter $H$ (in meters), the machine raises a giant saw blade to height $H$, and cuts off every part of each tree that is above $H$ (of course, the parts of trees no taller than $H$ meters stay as they are). Mirko then takes the parts that were cut off.
    
    For example, if the trees in a row have heights $20,~15,~10,~17$ and Mirko raises the blade to $15$ meters, the remaining heights after cutting will be $15,~15,~10,~15$. Mirko gets $5$ meters of wood from the first tree and $2$ meters from the fourth, $7$ meters in total.
    
    Mirko cares a lot about the environment, so he will not cut more wood than needed. That is why he sets the blade as high as possible. Your task is to help Mirko find the largest integer height $H$ for the blade such that he gets at least $M$ meters of wood. That is, if he raised the blade $1$ meter higher, he would not get $M$ meters of wood.

??? note "Solution idea"
    We could try every answer from $0$ to $10^9$, but this naive approach certainly won't get full marks, because going from $0$ to $10^9$ takes too long. Instead, we can binary search over $[0,~10^9]$ for the answer and check whether each candidate is feasible (usually with a greedy check). **This is binary search on the answer.**

??? note "Reference code"
    ```cpp
    --8<-- "docs/basic/code/binary/binary_2.cpp"
    ```
    
    After reading the code above, you probably have two questions:
    
    1.  Why is the search range half-open (closed on the left, open on the right)?
    
        Because near the end of the search, it looks like this (taking the largest valid value as an example):
    
        ![](./images/binary-final-1.svg)
    
        and then
    
        ![](./images/binary-final-2.svg)
    
        For the smallest valid value, it is exactly the opposite.
    2.  Why return the left value?
    
        Same reason as above. When the loop ends, $l+1=r$, `check(l)` is true and `check(r)` is false, so $l$ is the largest valid value.

## Ternary search

### Introduction

Binary search can be used to approximate the zeros of a function. To find the extreme point of a unimodal function, we usually use ternary search instead.

In this section we use the following strict definition of unimodal: for a function $f(x)$ defined on $[l,r]$, if there exists $x^*\in[l,r]$ such that $f(x)$ is strictly increasing on $[l,x^*]$ and strictly decreasing on $[x^*,r]$, then $f(x)$ is called a unimodal function. Both intervals include $x^*$, so $x^*$ is the unique maximum point, and $f(x^*)$ is the maximum value.

??? note "Why not find the extreme point by finding the zeros of the derivative?"
    First, being unimodal does not guarantee that the derivative has a unique zero, and a point where the derivative is zero is not necessarily the maximum point. For example,
    
    $$
    f(x)=\begin{cases}
      (x-1)^3+1,&0\le x<2,\\
      (3-x)^3+1,&2\le x\le 4.
    \end{cases}
    $$
    
    The zeros of $f'(x)$ are $x=1$ and $x=3$, but the maximum of $f(x)$ is at $x=2$, where it is not differentiable.
    
    Second, for some functions, taking the derivative is messy, and the result can be complicated; the function may not even be expressible in the form $y=f(x)$.
    
    Finally, in some problems the unimodal function whose extreme point we need is not a single function, but one built from several functions with special operations (for example, the maximum of the minimum of several linear functions with different monotonicity). Its derivative may then be piecewise, and the function may not be differentiable at some points.

???+ warning "Note"
    Ternary search can find both the maximum of a unimodal function and the minimum of a "unimodal valley" function. For convenience, unless stated otherwise, the text below uses finding the maximum of a unimodal function as the example.

### How it works

Ternary search is based on the same idea as binary search, but at each step it picks any two points $\textit{lmid} < \textit{rmid}$ (the two blue points in the figure below) inside the current interval $[l,r]$ (between the two orange points in the figure). As the figure shows, if $f(\textit{lmid})<f(\textit{rmid})$, then the function must be increasing on $[l,\textit{lmid})$ (the red part in the figure), so the maximum point (the green point in the figure) cannot be in this interval, and we can throw it away. However, we cannot rule out that the maximum point lies to the right of $\textit{rmid}$, so we cannot throw away anything more. The opposite case works the same way.

![](images/ternary.svg)

The correctness of ternary search does not depend on exactly how $\textit{lmid}$ and $\textit{rmid}$ are chosen. They only need to be two different points in the interval; usually you can take the two points that split it into three equal parts. However, the choice does affect efficiency. Each step throws away one of the two side intervals, so you can also pick two points close to the midpoint to make the discarded part larger. If you take $\textit{mid}\pm\delta$ with a small enough $\delta>0$, comparing the function values is like checking the sign of the approximate derivative $\dfrac{f(\textit{mid}+\delta)-f(\textit{mid}-\delta)}{2\delta}$. Functions in competitive programming are usually quite smooth, so we can use this to roughly decide which side of $\textit{mid}$ the extreme point is on, getting close to the efficiency of binary search.

### Implementation

Here is the pseudocode:

$$
\begin{array}{l}
\textbf{Algorithm}\operatorname{TernarySearch}(f,l,r):\\
\textbf{Input. } \text{A unimodal function } f(x) \text{ and its domain } [l,r].  \\
\textbf{Output. } \text{The maximizer }x^*\text{, up to an error of }\varepsilon\text{, and its value } f(x^*). \\
\textbf{Method. } \\
\begin{array}{ll}
1 & \textbf{while } r - l > \varepsilon\\
2 & \qquad \textit{mid}\gets (l+r)/2\\
3 & \qquad \textit{lmid}\gets \textit{mid} - \varepsilon / 3 \\
4 & \qquad \textit{rmid}\gets \textit{mid} + \varepsilon / 3 \\
5 & \qquad \textbf{if } f(\textit{lmid}) < f(\textit{rmid}) \\
6 & \qquad \qquad l\gets \textit{lmid} \\
7 & \qquad \textbf{else } \\
8 & \qquad \qquad r\gets \textit{rmid} \\
9 & x^* \gets (l+r)/2 \\
10& \textbf{return } x^*,~ f(x^*)
\end{array}
\end{array}
$$

???+ tip "Choosing the split points"
    In the code, the split points are chosen as $\textit{mid} \pm \varepsilon / 3$ to make sure they always lie between the current $l$ and $r$, which avoids getting stuck in an infinite loop.

???+ info "The integer case"
    If the domain of $f(x)$ is the integers, both the ternary search above and the golden-section search below should stop once $r-l$ is small. When $r-l$ is small, find the maximum point by brute force over the remaining values.

### Optimization: golden-section search

If each call to $f(x)$ is expensive and you need to cut down the number of calls further, you can improve the constant factor of ternary search with golden-section search. This is also a key part of the "optimal selection method" proposed by Hua Luogeng.

In ternary search, each iteration needs two function calls, and after one iteration the interval shrinks to at best $1/2$ of its length. This means that reaching precision $\varepsilon$ takes at least

$$
2\log_2\dfrac{r-l}{\varepsilon}
$$

function calls. This is the best ternary search can do. If you choose other split points, such as the trisection points, the number of calls goes up further, because the interval shrinks more slowly per iteration.

The idea of golden-section search is to reuse split points that have already been computed. Then, except for the first iteration, which needs two function calls, every later iteration needs only one. Let the golden ratio be

$$
\phi = \dfrac{\sqrt{5}-1}{2} \approx 0.618.
$$

In each iteration, the split points are the left and right golden-section points:

$$
m^l = \phi l +(1-\phi)r,~m^r = (1-\phi)l+\phi r.
$$

Splitting a segment at its golden-section points gives a self-similar structure. That is, $m^l$ is the left golden-section point of the segment $[l,r]$, and also the right golden-section point of the segment $[l,m^r]$. The benefit of choosing split points this way is that in iteration $k>1$, one of the two split points has always been computed before, so its result can be reused directly.

![](./images/golden-section-search.svg)

With split points chosen this way, reaching precision $\varepsilon$ takes only

$$
1 + \log_{\phi^{-1}}\dfrac{r-l}{\varepsilon} \approx 1 + 1.44\log_2\dfrac{r-l}{\varepsilon}
$$

function calls. Asymptotically, this uses fewer function calls.

Here is the pseudocode:

$$
\begin{array}{l}
\textbf{Algorithm}\operatorname{GoldenSectionSearch}(f,l,r):\\
\textbf{Input. } \text{A unimodal function } f(x) \text{ and its domain } [l,r].  \\
\textbf{Output. } \text{The maximizer }x^*\text{, up to an error of }\varepsilon\text{, and its value } f(x^*). \\
\textbf{Method. } \\
\begin{array}{ll}
1 & \textit{lmid} \gets \phi l + (1-\phi)r \\
2 & \textit{rmid} \gets (1-\phi)l + \phi r \\
3 & \textit{lval} \gets f(\textit{lmid}) \\
4 & \textit{rval} \gets f(\textit{rmid}) \\
5 & \textbf{while } r - l > \varepsilon \\
6 & \qquad \textbf{if } \textit{lval} > \textit{rval} \\
7 & \qquad \qquad r \gets \textit{rmid} \\
8 & \qquad \qquad \textit{rmid} \gets \textit{lmid} \\
9 & \qquad \qquad \textit{rval} \gets \textit{lval} \\
10& \qquad \qquad \textit{lmid} \gets \phi l + (1-\phi)r \\
11& \qquad \qquad \textit{lval} \gets f(\textit{lmid}) \\
12& \qquad \textbf{else} \\
13& \qquad \qquad l \gets \textit{lmid} \\
14& \qquad \qquad \textit{lmid} \gets \textit{rmid} \\
15& \qquad \qquad \textit{lval} \gets \textit{rval} \\
16& \qquad \qquad \textit{rmid} \gets (1-\phi)l + \phi r \\
17& \qquad \qquad \textit{rval} \gets f(\textit{rmid}) \\
18& x^* \gets (l+r)/2 \\
19& \textbf{return }x^*,~f(x^*)
\end{array}
\end{array}
$$

### Example problem

???+ note "[Luogu P3382 - Ternary Search](https://www.luogu.com.cn/problem/P3382)"
    Given a polynomial function of degree $N$ and a range $[l, r]$, find the unique value $x$ such that the function is increasing on $[l, x]$ and decreasing on $[x, r]$.

??? note "Solution idea"
    The problem asks for the value of the variable at which the degree-$N$ function reaches its maximum on $[l, r]$, so ternary search clearly applies. The implementation below uses the two trisection points and moves the interval endpoints to the split points that were actually compared; once the interval is small enough, it outputs the midpoint of the interval.

??? note "Reference code"
    === "C++"
        ```cpp
        --8<-- "docs/basic/code/binary/binary_1.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/basic/code/binary/binary_1.py"
        ```

### Exercises

-   [UVa 1476 - Error Curves](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4222)
-   [UVa 10385 - Duathlon](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1326)
-   [UOJ 162 - [Tsinghua Training Camp 2015] Light Bulb Testing](https://uoj.ac/problem/162)
-   [Luogu P7579 - [RdOI R2] Weighing (weigh)](https://www.luogu.com.cn/problem/P7579)

## Fractional programming

See also: [Fractional programming](../misc/frac-programming.md)

Fractional programming usually refers to the following kind of problem: each item has two attributes $c_i$ and $d_i$, and you need to choose some of the items in some way so that $\dfrac{\sum{c_i}}{\sum{d_i}}$ is as large or as small as possible.

Classic examples include the optimal ratio cycle, the optimal ratio spanning tree, and so on.

Fractional programming can be solved with binary search.

## References and notes

-   [Ternary search - Wikipedia](https://en.wikipedia.org/wiki/Ternary_search)
-   [Golden-section search - Wikipedia](https://en.wikipedia.org/wiki/Golden-section_search)
-   [Ternary search - CP Algorithms](https://cp-algorithms.com/num_methods/ternary_search.html)
