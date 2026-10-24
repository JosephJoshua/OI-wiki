Prerequisites: [Bitwise operations](./bit.md#bitwise-operations), [Integers and bit sequences](./bit.md#integers-and-bit-sequences).

The binary representation of a number can be viewed as a set ($0$ means the element is not in the set, $1$ means it is). For example, the set $\{1,3,4,8\}$ can be written as $(100011010)_2$. Bitwise operations can then be viewed as operations on sets.

| Operation   |    Set notation     |         Bitwise notation          |
| ------ | :-------------: | :-------------------------: |
| Intersection   |   $a \cap b$    | $a \operatorname{AND} b$ |
| Union   |   $a \cup b$    | $a \operatorname{OR} b$ |
| Complement   |    $\bar{a}$    | $\operatorname{NOT} a$ (the universal set has every binary bit equal to 1) |
| Difference   | $a \setminus b$ | $a \operatorname{AND} \operatorname{NOT} b$ |
| Symmetric difference | $a\triangle b$  | $a \operatorname{XOR} b$  |

Before we go on to iterating over the subsets of a set, let us look at some applications of bitwise operations.

### Modulo a power of 2

Taking a number modulo a non-negative integer power of $2$ is the same as keeping its last few binary digits, which is the same as ANDing it with $mod-1$.

=== "C++"
    ```cpp
    int modPowerOfTwo(int x, int mod) { return x & (mod - 1); }
    ```

=== "Python"
    ```python
    def modPowerOfTwo(x, mod):
        return x & (mod - 1)
    ```

From this we see that a non-negative integer power of $2$ taken modulo itself gives $0$. That is, if $n$ is a non-negative integer power of $2$, then $n$ AND $n-1$ is $0$.

In fact, for a positive integer $n$, $n-1$ clears the lowest $1$ bit of $n$ and sets every bit below it to $1$. So $n$ AND $n-1$ is the same as removing the lowest $1$ bit of $n$.

We can use this to check whether a number is a non-negative integer power of $2$. $n$ is a non-negative integer power of $2$ if and only if its binary representation has exactly one $1$.

=== "C++"
    ```cpp
    bool isPowerOfTwo(int n) { return n > 0 && (n & (n - 1)) == 0; }
    ```

=== "Python"
    ```python
    def isPowerOfTwo(n):
        return n > 0 and (n & (n - 1)) == 0
    ```

### Iterating over subsets

Iterating over all subsets of a set represented by a binary number is the same as enumerating all submasks of the corresponding mask.

A mask is a string of bits that is ANDed with a source value to get a new operand in which some of the source's bits are masked out.

A mask acts like a cover over the source value. A $1$ bit in the mask means the corresponding bit of the source is kept, and a $0$ bit in the mask means the corresponding bit of the source is set to $0$. Changing some $1$ bits of a mask to $0$ gives a submask of that mask. A mask is also a submask of itself.

Given a mask $m$, we want to iterate efficiently over all of its submasks $s$. We can do this with a bit trick.

```cpp
// iterate over the non-empty subsets of m in descending order
int s = m;
while (s > 0) {
  // s is a non-empty subset of m
  s = (s - 1) & m;
}
```

Or with a more compact for statement:

```cpp
// iterate over the non-empty subsets of m in descending order
for (int s = m; s; s = (s - 1) & m)
// s is a non-empty subset of m
```

Neither piece of code handles the submask equal to $0$. To handle it too, you can do something else, for example:

```cpp
// iterate over the subsets of m in descending order
for (int s = m;; s = (s - 1) & m) {
  // s is a subset of m
  if (s == 0) break;
}
```

Next we prove that the code above visits every submask of $m$ exactly once, in descending order.

Suppose we have a current mask $s$ and want to move on to the next one. Subtracting $1$ from $s$ removes the rightmost set bit of $s$ and turns every bit to its right into $1$.

To turn $s-1$ into a new submask, we need to remove all the extra $1$ bits that are not in $m$. The operation `(s - 1) & m` does exactly this.

Together these two steps cut $s-1$ down to the largest value that can be reached, which is the next submask after $s$ in descending order.

So the algorithm generates all submasks of the mask in descending order, doing only two operations per iteration.

The special case is $s=0$. After computing $s-1$ we get $-1$, in which every bit is $1$. After `(s - 1) & m` the new $s$ equals $m$. So if the loop does not stop at $s=0$, it never terminates.

Let $\text{popcount}(m)$ be the number of $1$ bits in the binary form of $m$. With this method we can iterate over the subsets of the set $m$ in $O(2^{\text{popcount}(m)})$ time.

### Iterating over the submasks of all masks

In problems that use bitmask DP, we sometimes want to iterate over all submasks of every mask:

```cpp
for (int m = 0; m < (1 << n); ++m)
  // iterate over the non-empty subsets of m in descending order
  for (int s = m; s; s = (s - 1) & m)
// s is a non-empty subset of m
```

This iterates over every subset of every subset of a set of size $n$.

Next we prove that this takes $O(3^n)$ time, where $n$ is the total number of bits in a mask, that is, the number of elements in the set.

Consider bit $i$, that is, the $i$-th element of the set. There are three cases:

- It is $0$ in the mask $m$, so it is $0$ in the submask $s$. The element is in neither the larger nor the smaller subset.
- It is $1$ in $m$ but $0$ in $s$. The element is only in the larger subset, not the smaller one.
- It is $1$ in both $m$ and $s$. The element is in both subsets.

There are $n$ bits in total, so there are $3^n$ different combinations.

Here is another proof:

If the mask $m$ has $k$ ones, it has $2^k$ submasks. For a given $k$, there are $\dbinom{n}{k}$ masks $m$, so the total number of pairs is:

$$
\sum_{k=0}^n \dbinom{n}{k} 2^k
$$

By the binomial theorem, this sum is the expansion of $(1+2)^n$, so there are $3^n$ different combinations.

### References

**This page is mainly translated from the post [Перебор всех подмасок данной маски](http://e-maxx.ru/algo/all_submasks) and its English translation [Submask Enumeration](https://cp-algorithms.com/algebra/all-submasks.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**

### Exercises

- [Atcoder - Close Group](https://atcoder.jp/contests/abc187/tasks/abc187_f)
- [Codeforces - Nuclear Fusion](http://codeforces.com/problemset/problem/71/E)
- [Codeforces - Sandy and Nuts](http://codeforces.com/problemset/problem/599/E)
- [UVa 1439 - Exclusive Access 2](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4185)
- [UVa 11825 - Hackers' Crackdown](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2925)
