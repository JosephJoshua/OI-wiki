author: HeRaNO, Zhoier, Ir1d, Xeonacid, wangdehu, ouuan, ranwen, ananbaobeichicun, Ycrpro, dbxxx-oi, HowieHz, y-kx-b

## Introduction

A Fenwick tree (also called a binary indexed tree) is a data structure with little code that supports **point updates** and **range queries**.

??? note "What are 'point updates' and 'range queries'?"
    Suppose we have this problem:
    
    Given a sequence $a$, perform the following two kinds of operations:
    
    -   Given $x, y$, increase $a[x]$ by $y$.
    -   Given $l, r$, compute the sum of $a[l \ldots r]$.
    
    The first operation is a "point update", and the second is a "range query".
    
    Similarly, there are also "range updates" and "point queries". Here is an example of each:
    
    -   Range update: given $l, r, x$, increase every number in $a[l \ldots r]$ by $x$;
    -   Point query: given $x$, find the value of $a[x]$.
    
    Note that range problems are generally strictly stronger than point problems, since an operation on a single point is the same as an operation on a range of length $1$.

The information and operation maintained by a plain Fenwick tree must be **associative** and **invertible**, such as addition (sum), multiplication (product), XOR, and so on.

-   Associative: $(x \circ y) \circ z = x \circ (y \circ z)$, where $\circ$ is a binary operator.
-   Invertible: the operation has an inverse, that is, given $x \circ y$ and $x$, we can recover $y$.

Things to note:

-   For multiplication modulo a number to be invertible, every number must have a modular inverse (this always holds when the modulus is prime);
-   Information like $\gcd$ and $\max$ is not invertible, so a plain Fenwick tree can't handle it. However:
    -   Two Fenwick trees can be used to handle range minimum/maximum queries; see [Efficient Range Minimum Queries using Binary Indexed Trees](http://history.ioinformatics.org/oi/files/volume9.pdf#page=41).
    -   This page also covers an extended Fenwick tree that supports queries on non-invertible information in $\Theta(\log^2n)$ time.

In fact, the problems a Fenwick tree can solve are a subset of those a segment tree can solve: anything a Fenwick tree can do, a segment tree can also do, but not the other way around. Still, Fenwick tree code is much shorter than segment tree code and has a smaller constant factor, so it is still worth learning.

Sometimes, with the help of a difference array and auxiliary arrays, a Fenwick tree can also solve the stronger **range add, point query** and **range add, range sum** problems.

## Fenwick tree

### A first look

Let's start with an example: how do we find the prefix sum of $a[1 \ldots 7]$?

One way is to compute $a_1 + a_2 + a_3 + a_4 + a_5 + a_6 + a_7$, which adds up $7$ numbers.

But suppose you already know three numbers $A$, $B$, $C$, where $A$ is the sum of $a[1 \ldots 4]$, $B$ is the sum of $a[5 \ldots 6]$, and $C$ is the sum of $a[7 \ldots 7]$ (which is just $a[7]$ itself). How would you compute it? You would certainly answer $A + B + C$, which only adds up $3$ numbers.

This is why a Fenwick tree can compute information quickly: we can always split a prefix $[1, n]$ into **at most $\boldsymbol{\log n}$ ranges** whose information is **already known**.

Then we only need to combine the information of these $\log n$ ranges to get the answer. Compared with directly combining $n$ pieces of information, this is much faster.

It is easy to see that the information must be associative; otherwise we couldn't combine it like this.

The figure below shows how a Fenwick tree works:

![](./images/fenwick.svg)

The eight blocks at the bottom are the original data array $a$. The uneven blocks above them (the same array as the eight blocks at the top) are the array one level above $a$: the array $c$.

The array $c$ stores the sums of certain ranges of the original array $a$. In other words, the information for these ranges is known, and our goal is to split the queried prefix into these small ranges.

For example, the figure shows that:

-   $c_2$ covers $a[1 \ldots 2]$;
-   $c_4$ covers $a[1 \ldots 4]$;
-   $c_6$ covers $a[5 \ldots 6]$;
-   $c_8$ covers $a[1 \ldots 8]$;
-   Every remaining $c[x]$ covers just $a[x]$ itself (a small range $a[x \ldots x]$ of length $1$).

Notice that $c[x]$ always covers a range whose right end is $x$. Let's ignore the left end for now and get a feel for how a Fenwick tree answers a query.

Example: compute the sum of $a[1 \ldots 7]$.

Process: start at $c_{7}$ and jump backwards. $c_{7}$ covers only the element $a_{7}$. Next we look at $c_{6}$, which covers $a[5 \ldots 6]$. Then we jump to $c_{4}$, which covers the elements $a[1 \ldots 4]$. Then we try to jump to $c_0$, but $c_0$ doesn't exist, so we stop.

The $c$ values we just found are $c_7, c_6, c_4$. These are exactly the three small ranges that $a[1 \ldots 7]$ splits into, and combining them gives the answer $c_7 + c_6 + c_4$.

Example: compute the sum of $a[4 \ldots 7]$.

We again start at $c_7$, jump to $c_6$ and then to $c_4$. Now we notice that $c_4$ covers the sum of $a[1 \ldots 4]$, but we don't want the $a[1 \ldots 3]$ part. What do we do? Simple: subtract the sum of $a[1 \ldots 3]$.

So we might as well, from the start, turn the query for the sum of $a[4 \ldots 7]$ into a query for the sum of $a[1 \ldots 7]$ and a query for the sum of $a[1 \ldots 3]$, and take the difference of the two results.

![](images/fenwick-query.svg)

### Covered ranges

So here's the question: how far to the left does the range covered by $c[x](x \ge 1)$ extend? In other words, how long is that range?

In a Fenwick tree, the range covered by $c[x]$ has length $2^{k}$, where:

-   Numbering the lowest binary bit as bit $0$, $k$ is exactly the position of the lowest `1` bit in the binary representation of $x$;
-   $2^k$ (the length of the range covered by $c[x]$) is exactly the number formed by the lowest `1` bit of $x$ together with all the `0` bits after it.

For example, which range does $c_{88}$ cover?

Since $88_{(10)}=01011000_{(2)}$, the lowest `1` bit and the `0` bits after it form the binary number `1000`, which is $8$. So $c_{88}$ covers $8$ elements of the array $a$.

Therefore, $c_{88}$ holds the information of the range $a[81 \ldots 88]$.

Let $\operatorname{lowbit}(x)$ be the number formed by the lowest `1` bit of $x$ and the `0` bits after it. Then the range covered by $c[x]$ is $[x-\operatorname{lowbit}(x)+1, x]$.

???+ warning "Note"
    $\operatorname{lowbit}$ is not the position $k$ of the lowest `1` bit, but the number $2^k$ formed by that `1` and all the `0` bits after it.

How do we compute `lowbit`? Using bit operations, we get `lowbit(x) = x & -x`.

??? note "Why lowbit works"
    Flipping all bits of `x` and then adding 1 gives the binary encoding of `-x`. For example, the binary encoding of $6$ is `110`; flipping all bits gives `001`, and adding `1` gives `010`.
    
    Suppose `x` is `(...)10...00` in binary. Flipping all bits gives `[...]01...11`, and adding `1` gives `[...]10...00`, which is the binary encoding of `-x`. Here the first `1` shown in `x` is the lowest `1` bit of `x`.
    
    Each bit in the `(...)` part is the opposite of the corresponding bit in the `[...]` part, so `x & -x = (...)10...00 & [...]10...00 = 10...00`, and the result is exactly `lowbit`.

???+ note "Implementation"
    === "C++"
        ```cpp
        int lowbit(int x) {
          // The number formed by the lowest 1 bit of x and all the 0 bits after it.
          // lowbit(0b01011000) == 0b00001000
          //          ~~~~^~~~
          // lowbit(0b01110010) == 0b00000010
          //          ~~~~~~^~
          return x & -x;
        }
        ```
    
    === "Python"
        ```python
        def lowbit(x):
            """
            The number formed by the lowest 1 bit of x and all the 0 bits after it.
            lowbit(0b01011000) == 0b00001000
                    ~~~~~^~~
            lowbit(0b01110010) == 0b00000010
                    ~~~~~~~^~
            """
            return x & -x
        ```

### Range query

Now let's look at how the Fenwick tree operations are implemented, starting with range queries.

Recall how we queried $a[4 \ldots 7]$: we turned it into two subproblems, querying the sums of $a[1 \ldots 7]$ and $a[1 \ldots 3]$, and then took the difference.

In fact, any range query can be done this way: the sum of $a[l \ldots r]$ is the sum of $a[1 \ldots r]$ minus the sum of $a[1 \ldots l - 1]$. This turns a range problem into prefix problems, which are easier to handle.

Indeed, turning a range query over $l \ldots r$ into prefix queries over $1 \ldots r$ and $1 \ldots l - 1$ and taking the difference is a very common trick in contests.

So how do we answer a prefix query? Recall how we queried $a[1 \ldots 7]$:

> Start at $c_{7}$ and jump backwards. $c_{7}$ covers only the element $a_{7}$. Next we look at $c_{6}$, which covers $a[5 \ldots 6]$. Then we jump to $c_{4}$, which covers the elements $a[1 \ldots 4]$. Then we try to jump to $c_0$, but $c_0$ doesn't exist, so we stop.
>
> The $c$ values we just found are $c_7, c_6, c_4$. These are exactly the three small ranges that $a[1 \ldots 7]$ splits into; combining them, the answer is $c_7 + c_6 + c_4$.

Looking at this process, each backward jump must land one position left of the current range's left end, which becomes the right end of the new range. Only then is the prefix split without gaps or overlaps. For example, $c_6$ covers $a[5 \ldots 6]$, so next we jump to $5 - 1 = 4$, that is, we visit $c_4$.

We can now write down the process for querying $a[1 \ldots x]$:

-   Start at $c[x]$ and jump backwards; $c[x]$ covers $a[x-\operatorname{lowbit}(x)+1 \ldots x]$;
-   Set $x \gets x - \operatorname{lowbit}(x)$. If $x = 0$, we have reached the end, so stop; otherwise go back to step one.
-   Combine all the $c$ values we visited.

In the implementation, we don't have to collect all the $c$ values first and then combine them; we can combine as we jump.

For example, if the information is a sum, start with $\mathrm{ans} = 0$, and each time we reach some $c[x]$, do $\mathrm{ans} \gets \mathrm{ans} + c[x]$. In the end, $\mathrm{ans}$ is the combined result.

???+ note "Implementation"
    === "C++"
        ```cpp
        int getsum(int x) {  // sum of a[1]..a[x]
          int ans = 0;
          while (x > 0) {
            ans = ans + c[x];
            x = x - lowbit(x);
          }
          return ans;
        }
        ```
    
    === "Python"
        ```python
        def getsum(x):  # sum of a[1]..a[x]
            ans = 0
            while x > 0:
                ans = ans + c[x]
                x = x - lowbit(x)
            return ans
        ```

### Properties of the Fenwick tree and its tree shape

Before explaining point updates, let's go over some basic properties of the Fenwick tree and where its tree shape comes from. This will help you understand point updates better.

We use the following conventions:

-   $l(x) = x - \operatorname{lowbit}(x) + 1$. That is, $l(x)$ is the left end of the range covered by $c[x]$.
-   Any positive integer $x$ can always be written as $s \times 2^{k + 1} + 2^k$, where $\operatorname{lowbit}(x) = 2^k$.
-   Below, "$c[x]$ and $c[y]$ are disjoint" means the ranges covered by $c[x]$ and $c[y]$ don't overlap, that is, $[l(x), x]$ and $[l(y), y]$ are disjoint. Statements like "$c[x]$ is contained in $c[y]$" are defined the same way.

**Property $\boldsymbol{1}$: for $\boldsymbol{x \le y}$, either $\boldsymbol{c[x]}$ and $\boldsymbol{c[y]}$ are disjoint, or $\boldsymbol{c[x]}$ is contained in $\boldsymbol{c[y]}$.**

??? note "Proof"
    Proof: suppose $c[x]$ and $c[y]$ overlap, that is, $[l(x), x]$ and $[l(y), y]$ overlap. Then we must have $l(y) \le x \le y$.
    
    Write $y$ as $s \times 2^{k +1} + 2^k$; then $l(y) = s \times 2^{k + 1} + 1$. So $x$ can be written as $s \times 2^{k +1} + b$, where $1 \le b \le 2^k$.
    
    It is easy to see that $\operatorname{lowbit}(x) = \operatorname{lowbit}(b)$. And since $b - \operatorname{lowbit}(b) \ge 0$,
    
    we get $l(x) = x - \operatorname{lowbit}(x) + 1 = s \times 2^{k +1} + b - \operatorname{lowbit}(b) +1 \ge s \times 2^{k +1} + 1 = l(y)$, that is, $l(y) \le l(x) \le x \le y$.
    
    So if $c[x]$ and $c[y]$ overlap, the range covered by $c[x]$ must be entirely contained in $c[y]$.

**Property $\boldsymbol{2}$: $\boldsymbol{c[x]}$ is properly contained in $\boldsymbol{c[x + \operatorname{lowbit}(x)]}$.**

??? note "Proof"
    Proof: let $y = x + \operatorname{lowbit}(x)$ and $x = s \times 2^{k + 1} + 2^k$. Then $y = (s + 1) \times 2^{k +1}$ and $l(x) = s \times 2^{k + 1} + 1$.
    
    It is easy to see that $\operatorname{lowbit}(y) \ge 2^{k + 1}$, so $l(y) = (s + 1) \times 2^{k + 1} - \operatorname{lowbit}(y) + 1 \le s \times 2^{k +1} + 1= l(x)$, that is, $l(y) \le l(x) \le x < y$.
    
    So $c[x]$ is properly contained in $c[x + \operatorname{lowbit}(x)]$.

**Property $3$: for any $\boldsymbol{x < y < x + \operatorname{lowbit}(x)}$, $\boldsymbol{c[x]}$ and $\boldsymbol{c[y]}$ are disjoint.**

??? note "Proof"
    Proof: let $x = s \times 2^{k + 1} + 2^k$. Then $y = x + b = s \times 2^{k + 1} + 2^k + b$, where $1 \le b < 2^k$.
    
    It is easy to see that $\operatorname{lowbit}(y) = \operatorname{lowbit}(b)$. And since $b - \operatorname{lowbit}(b) \ge 0$,
    
    we get $l(y) = y - \operatorname{lowbit}(y) + 1 = x + b - \operatorname{lowbit}(b) + 1 > x$, that is, $l(x) \le x < l(y) \le y$.
    
    So $c[x]$ and $c[y]$ are disjoint.

With these three properties in place, let's look at the tree shape of the Fenwick tree (ignore the edges from $a$ to $c$).

![](./images/fenwick.svg)

In fact, the tree shape of a Fenwick tree is the graph obtained by adding an edge from each $x$ to $x + \operatorname{lowbit}(x)$, where $x + \operatorname{lowbit}(x)$ is the parent of $x$.

Note that when we think about the tree shape, we ignore the size of the Fenwick tree; that is, we treat it as an infinitely large tree, which makes the analysis easier. In a real implementation, we only need $c[x]$ for $x \le n$, where $n$ is the length of the original array.

This tree naturally has many nice properties. Here are some of them (let $fa[u]$ be the direct parent of $u$):

-   $u < fa[u]$.
-   $u$ is greater than every descendant of $u$ and less than every ancestor of $u$.
-   The $\operatorname{lowbit}$ of $u$ is strictly less than the $\operatorname{lowbit}$ of $fa[u]$.

??? note "Proof"
    Let $y = x + \operatorname{lowbit}(x)$ and $x = s \times 2^{k + 1} + 2^k$. Then $y = (s + 1) \times 2^{k +1}$, and clearly $\operatorname{lowbit}(y) \ge 2^{k + 1} > \operatorname{lowbit}(x)$. Done.

-   The height of node $x$ is $\log_2\operatorname{lowbit}(x)$, that is, the position of the lowest `1` bit of $x$.

??? note "Definition of height"
    The height $h(x)$ of node $x$ is defined as: if $x \bmod 2 = 1$, then $h(x) = 0$; otherwise $h(x) = \max(h(y)) + 1$, where $y$ ranges over all children of $x$ (in this case $x$ has at least one child, $x - 1$).
    
    In other words, a node's height is exactly $1$ more than the height of its tallest child. A node with no children has height $0$.
    
    We introduce the idea of height here to make the complexity explanation later easier.

-   $c[u]$ is properly contained in $c[fa[u]]$ (Property $2$).
-   $c[u]$ is properly contained in $c[v]$, where $v$ is any ancestor of $u$ (by induction on the previous property).
-   $c[u]$ properly contains $c[v]$, where $v$ is any descendant of $u$ (the previous property with $u$ and $v$ swapped).
-   For any $v' > u$, if $v'$ is not an ancestor of $u$, then $c[u]$ and $c[v']$ are disjoint.

??? note "Proof"
    Among $u$ and its ancestors, there must be a node $v$ with $v < v' < fa[v]$. By Property $3$, $c[v']$ and $c[v]$ are disjoint, and $c[v]$ contains $c[u]$, so $c[v']$ and $c[u]$ are disjoint.

-   For any $v < u$, if $v$ is not in the subtree of $u$, then $c[u]$ and $c[v]$ are disjoint (the previous property with $u$ and $v'$ swapped).
-   For any $v > u$, $c[u]$ is properly contained in $c[v]$ if and only if $v$ is an ancestor of $u$ (a summary of the properties above). This is the core idea behind point updates in a Fenwick tree.
-   Let $u = s \times 2^{k + 1} + 2^k$. Then $u$ has $k = \log_2\operatorname{lowbit}(u)$ children, numbered $u - 2^t(0 \le t < k)$.
    -   Example: suppose $k = 3$ and $u$ is `...1000` in binary. Then $u$ has three children, which are `...0111`, `...0110` and `...0100` in binary.

??? note "Proof"
    Subtracting $2^t$ from a number $x$ flips bit $t$ of $x$, while the lower bits stay the same.
    
    Consider a child $v$ of $u$. We have $v + \operatorname{lowbit}(v) = u$, that is, $v = u - 2^t$ and $\operatorname{lowbit}(v) = 2^t$. Let $u = s \times 2^{k + 1} + 2^k$.
    
    **Consider $\boldsymbol{0 \le t < k}$**: bit $t$ of $u$ and all bits below it are $0$, so in $v = u - 2^t$ bit $t$ becomes $1$ and the lower bits stay $0$. This **satisfies** $\operatorname{lowbit}(v) = 2^t$.
    
    **Consider $\boldsymbol{t = k}$**: then $v = u - 2^k$, and bit $k$ of $v$ becomes $0$, which **does not satisfy** $\operatorname{lowbit}(v) = 2^t$.
    
    **Consider $\boldsymbol{t > k}$**: then $v = u - 2^t$, and bit $k$ of $v$ is $1$, so $\operatorname{lowbit}(v) = 2^k$, which **does not satisfy** $\operatorname{lowbit}(v) = 2^t$.

-   The ranges covered by the $c$ values of all children of $u$ join together to form exactly $[l(u), u - 1]$.
    -   Example: suppose $k = 3$ and $u$ is `...1000` in binary. Then $u$ has three children, which are `...0111`, `...0110` and `...0100` in binary.
    -   `c[...0100]` represents `a[...0001 ~ ...0100]`.
    -   `c[...0110]` represents `a[...0101 ~ ...0110]`.
    -   `c[...0111]` represents `a[...0111 ~ ...0111]`.
    -   It is easy to see that the union of these three ranges is exactly `a[...0001 ~ ...0111]`, that is, $[l(u), u - 1]$.

??? note "Proof"
    The children of $u$ can always be written as $u - 2^t(0 \le t < k)$. Clearly, the smaller $t$ is, the larger $u - 2^t$ is, and the further right its range is. Let $f(t) = u - 2^t$; then $f(k - 1), f(k - 2), \ldots, f(0)$ are the children of $u$ from left to right.
    
    It is easy to see that $\operatorname{lowbit}(f(t)) = 2^t$, so $l(f(t)) = u - 2^t - 2^t + 1 = u - 2^{t + 1} + 1$.
    
    Consider two adjacent children $f(t + 1)$ and $f(t)$. The right end of the former's range is $f(t + 1) = u - 2^{t + 1}$, and the left end of the latter's range is $l(f(t)) = u - 2^{t + 1} + 1$, so they meet exactly.
    
    Consider the leftmost child $f(k - 1)$. The left end of its range, $l(f(k - 1)) = u - 2^k + 1$, is exactly $l(u)$.
    
    Consider the rightmost child $f(0)$. The right end of its range is exactly $u - 1$.
    
    So the ranges of these children join together to form exactly $[l(u), u - 1]$.

### Point update

Now let's look at how to do a point update on $a[x]$.

Our goal is to maintain the array $c$ quickly and correctly. For efficiency, we only visit and update every $c[y]$ that covers $a[x]$, since the other $c$ values clearly don't change.

Any $c[y]$ that covers $a[x]$ must contain $c[x]$ (by Property $1$), so $y$ is an ancestor of $x$ in the Fenwick tree's tree shape. Therefore we start at $x$ and keep jumping to the parent until we go past the length of the original array.

Let $n$ be the size of $a$. The process for a point update on $a[x]$ is easy to write:

-   Start with $x' = x$.
-   Update $c[x']$.
-   Set $x' \gets x' + \operatorname{lowbit}(x')$. If $x' > n$, we have reached the end, so stop; otherwise go back to step two.

How $c[x']$ is updated depends on both the range information and the kind of point update. Here are some examples:

-   If $c[x']$ maintains range sums and the update adds $p$ to $a[x]$, then we add $p$ to every such $c[x']$ as well.
-   If $c[x']$ maintains range products and the update multiplies $a[x]$ by $p$, then we multiply every such $c[x']$ by $p$ as well.

However, point updates are flexible, so the kind of update and the maintained information need not use the same operation. For example, if $c[x']$ maintains range sums and the update sets $a[x]$ to $p$, we can turn it into adding $p - a[x]$ to $a[x]$. If the update multiplies $a[x]$ by $p$, we can turn it into adding $a[x] \times p - a[x]$ to $a[x]$.

Below is an implementation for range sums with point addition.

???+ note "Implementation"
    === "C++"
        ```cpp
        void add(int x, int k) {
          while (x <= n) {  // must not go out of bounds
            c[x] = c[x] + k;
            x = x + lowbit(x);
          }
        }
        ```
    
    === "Python"
        ```python
        def add(x, k):
            while x <= n:  # must not go out of bounds
                c[x] = c[x] + k
                x = x + lowbit(x)
        ```

### Building the tree

That is, building the Fenwick tree from the initial sequence (precomputing all of $c$).

Usually we can just turn this into $n$ point updates, for a time complexity of $\Theta(n \log n)$ (the complexity analysis comes later).

For example, to build the tree for the sequence $a = (5, 1, 4)$, just treat it as adding $5$ to $a[1]$, $1$ to $a[2]$ and $4$ to $a[3]$.

There is also a $\Theta(n)$ way to build the tree; see the section [$\Theta(n)$ construction](#thetan-construction) on this page.

### Complexity analysis

The space complexity is clearly $\Theta(n)$.

Time complexity:

-   Range query: the whole iteration $x \gets x - \operatorname{lowbit}(x)$ can be seen as turning all the $1$ bits of $x$ into $0$ one by one, from low to high. The number of ranges we split into equals the number of $1$ bits in $x$ (that is, $\operatorname{popcount}(x)$). So a single query takes $\Theta(\log n)$ time;
-   Point update: when jumping to the parent, the height of the visited node strictly increases, and we always have $x \le n$. Since the height of node $x$ is $\log_2\operatorname{lowbit}(x)$, the height never exceeds $\log_2n$, so the number of $c$ values visited is on the order of $\log n$. So a single point update takes $\Theta(\log n)$ time.

## Range add, range sum

Prerequisites: [Prefix sums & difference arrays](../basic/prefix-sum.md).

This problem can be solved by using two Fenwick trees to maintain a difference array.

Consider the difference array $d$ of the sequence $a$, where $d[i] = a[i] - a[i - 1]$. Since the prefix sums of a difference array give back the original array, $a_i=\sum_{j=1}^i d_j$.

As before, we turn a range-sum query into prefix-sum queries by taking a difference. So consider querying the sum of $a[1 \ldots r]$, that is, $\sum_{i=1}^{r} a_i$, and derive:

$$
\begin{aligned}
&\sum_{i=1}^{r} a_i\\=&\sum_{i=1}^r\sum_{j=1}^i d_j
\end{aligned}
$$

Looking at this formula, each $d_j$ is added $r - j + 1$ times in total. Continuing:

$$
\begin{aligned}
&\sum_{i=1}^r\sum_{j=1}^i d_j\\=&\sum_{i=1}^r d_i\times(r-i+1)
\\=&\sum_{i=1}^r d_i\times (r+1)-\sum_{i=1}^r d_i\times i
\end{aligned}
$$

We can't derive $\sum_{i=1}^r d_i \times i$ from $\sum_{i=1}^r d_i$, so we use two Fenwick trees to maintain the sums of $d_i$ and of $d_i \times i$ separately.

So how do we do a range add? Consider the effect on $d$ of adding $x$ to the range $a[l \ldots r]$ of the original array.

Since the difference array is $d[i] = a[i] - a[i - 1]$:

-   $a[l]$ grows by $v$ while $a[l - 1]$ stays the same, so $d[l]$ grows by $v$.
-   $a[r + 1]$ stays the same while $a[r]$ grows by $v$, so $d[r + 1]$ shrinks by $v$.
-   For any $i$ other than $l$ and $r+1$, either neither $a[i]$ nor $a[i - 1]$ changes, or both grow by $v$, and $a[i] + v - (a[i - 1] + v)$ is still $a[i] - a[i - 1]$, so all other $d[i]$ stay the same.

Now the maintenance method is easy to see: in the Fenwick tree for $d_i$, add $v$ at $l$ and add $-v$ at $r + 1$; in the Fenwick tree for $d_i \times i$, add $v \times l$ at $l$ and add $-v \times (r + 1)$ at $r + 1$.

For the weaker problem "range add, point query", we only need one Fenwick tree to maintain the difference array $d_i$. To query the value of $a[x]$, just compute the sum of $d[1 \ldots x]$.

Here is the code for "range add, range sum":

???+ note "Implementation"
    === "C++"
        ```cpp
        int t1[MAXN], t2[MAXN], n;
        
        int lowbit(int x) { return x & (-x); }
        
        void add(int k, int v) {
          int v1 = k * v;
          while (k <= n) {
            t1[k] += v, t2[k] += v1;
            // Note: can't write t2[k] += k * v, because k is no longer the index in the original array
            k += lowbit(k);
          }
        }
        
        int getsum(int *t, int k) {
          int ret = 0;
          while (k) {
            ret += t[k];
            k -= lowbit(k);
          }
          return ret;
        }
        
        void add1(int l, int r, int v) {
          add(l, v), add(r + 1, -v);  // split the range add into two prefix adds via differences
        }
        
        long long getsum1(int l, int r) {
          return (r + 1ll) * getsum(t1, r) - 1ll * l * getsum(t1, l - 1) -
                 (getsum(t2, r) - getsum(t2, l - 1));
        }
        ```
    
    === "Python"
        ```python
        t1 = [0] * MAXN
        t2 = [0] * MAXN
        n = 0
        
        
        def lowbit(x):
            return x & (-x)
        
        
        def add(k, v):
            v1 = k * v
            while k <= n:
                t1[k] = t1[k] + v
                t2[k] = t2[k] + v1
                k = k + lowbit(k)
        
        
        def getsum(t, k):
            ret = 0
            while k:
                ret = ret + t[k]
                k = k - lowbit(k)
            return ret
        
        
        def add1(l, r, v):
            add(l, v)
            add(r + 1, -v)
        
        
        def getsum1(l, r):
            return (
                (r) * getsum(t1, r)
                - l * getsum(t1, l - 1)
                - (getsum(t2, r) - getsum(t2, l - 1))
            )
        ```

Following the same idea, you should be able to implement "range multiply, range product", "XOR a range with a number, query the range XOR", and so on, as long as the maintained information and the range operation are the same operation. Interested readers can try it themselves.

## 2D Fenwick tree

### Point update, submatrix query

A 2D Fenwick tree, also called a Fenwick tree of Fenwick trees, handles point updates and prefix information on a 2D array.

As with the 1D Fenwick tree, let $c(x, y)$ be the combined information of the matrix $a(x - \operatorname{lowbit}(x) + 1, y - \operatorname{lowbit}(y) + 1) \ldots a(x, y)$, that is, the combined information of the matrix whose bottom-right corner is $a(x, y)$, with height $\operatorname{lowbit}(x)$ and width $\operatorname{lowbit}(y)$.

For point updates, let:

$$
f(x, i) = \begin{cases}x &i = 0\\f(x, i - 1) + \operatorname{lowbit}(f(x, i - 1)) & i > 0\\\end{cases}
$$

That is, $f(x, i)$ is the $i$-th ancestor of $x$ in the Fenwick tree's tree shape (the $0$-th ancestor is itself).

Then only the entries $c(f(x, i), f(y, j))$ cover $a(x, y)$. When updating $a(x, y)$, we only need to update all $c(f(x, i), f(y, j))$ with $f(x, i) \le n$ and $f(y, j) \le m$.

??? note "Proof of correctness"
    We want the range of $p$ and $q$ such that $c(p, q)$ covers $a(x, y)$.
    
    Consider a 1D Fenwick tree $c_1$ of size $n$ (over the original array $a_1$) and a 1D Fenwick tree $c_2$ of size $m$ (over the original array $a_2$).
    
    Then the question is equivalent to finding when $c_1(p)$ covers $a_1[x]$ and $c_2(q)$ covers $a_2[y]$.
    
    That is, in the Fenwick tree's tree shape, $p$ is $x$ or one of its ancestors, and $q$ is $y$ or one of its ancestors.
    
    So $p = f(x, i)$ and $q = f(y, j)$.

For queries, let:

$$
g(x, i) = \begin{cases}x &i = 0\\g(x, i - 1) - \operatorname{lowbit}(g(x, i - 1)) & i, g(x, i - 1) > 0\\0&\text{otherwise.}\end{cases}
$$

Then combine all $c(g(x, i), g(y, j))$ with $g(x, i), g(y, j) > 0$.

??? note "Proof of correctness"
    Let $\circ$ be the operator that combines two pieces of information (for example, if the information is a range sum, then $\circ = +$).
    
    Consider a 1D Fenwick tree $c_1$: $c_1[g(x, 0)] \circ c_1[g(x, 1)] \circ c_1[g(x, 2)] \circ \cdots$ is exactly the information of the range $[1 \ldots x]$ of the original array.
    
    Similarly, let $t(x) = c(x, g(y, 0)) \circ c(x, g(y, 1)) \circ c(x, g(y, 2)) \circ \cdots$. Then $t(x)$ is exactly the information of the matrix $a(x - \operatorname{lowbit}(x) + 1, 1) \ldots a(x, y)$.
    
    Again similarly, $t(g(x, 0)) \circ t(g(x, 1)) \circ t(g(x, 2)) \circ \cdots$ is the information of the matrix $a(1, 1) \ldots a(x, y)$.
    
    In fact, if we view the function $t(x)$ as a Fenwick tree, this is a Fenwick tree nested inside a Fenwick tree, which is where the name "Fenwick tree of Fenwick trees" comes from.

Below is the code for point add and submatrix sum query.

???+ note "Implementation"
    === "Point add"
        ```cpp
        void add(int x, int y, int v) {
          for (int i = x; i <= n; i += lowbit(i)) {
            for (int j = y; j <= m; j += lowbit(j)) {
              // Note: we must use loop variables here; we can't just write while (x <= n) like in the 1D case
              c[i][j] += v;
            }
          }
        }
        ```
    
    === "Submatrix sum query"
        ```cpp
        int sum(int x, int y) {
          int res = 0;
          for (int i = x; i > 0; i -= lowbit(i)) {
            for (int j = y; j > 0; j -= lowbit(j)) {
              res += c[i][j];
            }
          }
          return res;
        }
        
        int ask(int x1, int y1, int x2, int y2) {
          // query the submatrix sum
          return sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1, y2) + sum(x1 - 1, y1 - 1);
        }
        ```

### Submatrix add, submatrix sum

Prerequisites: [Prefix sums & difference arrays](../basic/prefix-sum.md) and the section [Range add, range sum](#range-add-range-sum) on this page.

As with the 1D "range add, range sum" problem, we maintain a difference array.

The difference array of a 2D array is:

$$
d(i, j) = a(i, j) - a(i - 1, j) - a(i, j - 1) + a(i - 1, j - 1).
$$

??? note "Why define it this way?"
    Ideally, taking 2D prefix sums of the difference matrix should give back the original matrix, because the two are inverse operations.
    
    The formula for 2D prefix sums is:
    
    $s(i, j) = s(i - 1, j) + s(i, j - 1) - s(i - 1, j - 1) + a(i, j)$.
    
    So with $a$ the original array and $d$ the difference array, we have:
    
    $a(i, j) = a(i - 1, j) + a(i, j - 1) - a(i - 1, j - 1) + d(i, j)$
    
    Rearranging gives the formula for the 2D difference array.
    
    $d(i, j) = a(i, j) - a(i - 1, j) - a(i, j - 1) + a(i - 1, j - 1)$.

So adding $v$ to the submatrix with top-left corner $(x_1, y_1)$ and bottom-right corner $(x_2, y_2)$ is the same as, on the difference array, adding $v$ at $d(x_1, y_1)$ and at $d(x_2 + 1, y_2 + 1)$, and adding $-v$ at $d(x_2 + 1, y_1)$ and at $d(x_1, y_2 + 1)$.

To see why, write out each of these four $d$ values using the definition and check how each term changes.

For example, if the difference array starts as $0$, then after adding $v$ to the submatrix $a(2, 2) \ldots a(3, 4)$, the difference array becomes:

$$
\begin{pmatrix}0&0&0&0&0\\0&v&0&0&-v\\0&0&0&0&0\\0&-v&0&0&v\end{pmatrix}
$$

(Here the submatrix $a(2, 2) \ldots a(3, 4)$ is exactly the $2 \times 3$ matrix in the middle above.)

So a submatrix add is done by turning it into four point adds on the difference array.

Now consider a submatrix sum query:

For a point $(x, y)$, its 2D prefix sum can be written as:

$$
\sum_{i = 1}^x\sum_{j = 1}^y\sum_{h = 1}^i\sum_{k = 1}^j d(h, k)
$$

This is because the prefix sum of the prefix sum of the difference array is the original prefix sum.

As with the 1D "range add, range sum" problem, count how many times $d(h, k)$ appears: $(x - h + 1) \times (y - k + 1)$ times.

Then continue the derivation:

$$
\begin{aligned}
&\sum_{i = 1}^x\sum_{j = 1}^y\sum_{h = 1}^i\sum_{k = 1}^j d(h, k)
\\=&\sum_{i = 1}^x\sum_{j = 1}^y d(i, j) \times (x - i + 1) \times (y - j + 1)
\\=&\sum_{i = 1}^x\sum_{j = 1}^y d(i, j) \times (xy + x + y + 1) - d(i, j) \times i \times (y + 1) - d(i, j) \times j \times (x + 1) + d(i, j) \times i \times j
\end{aligned}
$$

So we maintain four Fenwick trees, for the sums of $d(i, j)$, $d(i, j) \times i$, $d(i, j) \times j$ and $d(i, j) \times i \times j$.

Of course, as in 1D, if we only need submatrix add with point queries, maintaining one difference array and querying prefix sums is enough.

Here is the code:

???+ note "Implementation"
    ```cpp
    using ll = long long;
    ll t1[N][N], t2[N][N], t3[N][N], t4[N][N];
    
    void add(ll x, ll y, ll z) {
      for (int X = x; X <= n; X += lowbit(X))
        for (int Y = y; Y <= m; Y += lowbit(Y)) {
          t1[X][Y] += z;
          t2[X][Y] += z * x;  // note it is z * x, not z * X; same below
          t3[X][Y] += z * y;
          t4[X][Y] += z * x * y;
        }
    }
    
    void range_add(ll xa, ll ya, ll xb, ll yb,
                   ll z) {  //(xa, ya) to (xb, yb) submatrix
      add(xa, ya, z);
      add(xa, yb + 1, -z);
      add(xb + 1, ya, -z);
      add(xb + 1, yb + 1, z);
    }
    
    ll ask(ll x, ll y) {
      ll res = 0;
      for (int i = x; i; i -= lowbit(i))
        for (int j = y; j; j -= lowbit(j))
          res += (x + 1) * (y + 1) * t1[i][j] - (y + 1) * t2[i][j] -
                 (x + 1) * t3[i][j] + t4[i][j];
      return res;
    }
    
    ll range_ask(ll xa, ll ya, ll xb, ll yb) {
      return ask(xb, yb) - ask(xb, ya - 1) - ask(xa - 1, yb) + ask(xa - 1, ya - 1);
    }
    ```

## Fenwick tree over values and applications

We know that a plain Fenwick tree is built directly on the original sequence: $c_6$ holds the information of the range $a[5 \ldots 6]$.

In fact, we can also build a Fenwick tree on the value-count array of the original sequence. This is called a Fenwick tree over values.

??? note "What is a value-count array?"
    The value-count array $b$ of a sequence $a$ is defined so that $b[x]$ is the number of times $x$ appears in $a$.
    
    For example, the value-count array of $a = (1, 3, 4, 3, 4)$ is $b = (1, 0, 2, 2)$.
    
    Clearly, the size of $b$ depends on the range of values in $a$.
    
    If the range of values in the original sequence is too large, and what matters is the relative order of values rather than the values themselves, we usually [compress the coordinates](../misc/discrete.md) of the original array first and then build the value-count array.
    
    Also, the value-count array is an order-free representation of the original array: it describes the elements of the array and ignores their order. If two arrays differ only in order and contain the same elements, their value-count arrays are the same.
    
    So for problems where the order of the given array doesn't affect the answer, it is usually more intuitive to think in terms of the value-count array, for example [\[NOIP2021\] Sequence](https://www.luogu.com.cn/problem/P7961).

With a Fenwick tree over values, we can solve some classic problems.

### Point update, global $k$-th smallest query

Here we only discuss the $k$-th smallest; a $k$-th largest problem can be turned into a $k$-th smallest problem with simple arithmetic.

Coordinate compression works for this problem: if the range of values in the original sequence $a$ is too large, compress it and then build the value-count array $b$. Note that the values that appear in point updates must be compressed too, not just the elements of the original array $a$.

For point updates, just turn a point update on the original sequence into point updates on the value-count array. Specifically, if $a[x]$ changes from $y$ to $z$, then on the value-count array $b$ we subtract $1$ from $b[y]$ and add $1$ to $b[z]$.

To find the $k$-th smallest, binary search on $x$ and query the prefix sum of $[1, x]$ in the value-count array. Find $x_0$ such that the prefix sum of $[1, x_0]$ is $< k$ and the prefix sum of $[1, x_0 + 1]$ is $\ge k$; then the $k$-th smallest number is $x_0 + 1$ (note: here the prefix sum of $[1, 0]$ is taken to be $0$).

This takes $\Theta(\log^2n)$ time.

Let's use binary lifting instead of binary search.

Set $x = 0$ and $\mathrm{sum} = 0$, and let $i$ go from $\log_2n$ down to $0$:

-   Query the range sum $t$ of $[x + 1 \ldots x + 2^i]$ in the value-count array.
-   If $\mathrm{sum} + t < k$, the extension succeeds: $x \gets x + 2^i$ and $\mathrm{sum} \gets \mathrm{sum} + t$. Otherwise the extension fails and we do nothing.

The resulting $x$ is the largest value whose prefix sum over $[1 \ldots x]$ is $< k$, so $x + 1$ is the answer.

It may look like this doesn't improve the running time at all, but in fact, querying the range sum of $[x + 1 \ldots x + 2^i]$ only needs the value of $c[x + 2^i]$.

The reason is simple. Consider $\operatorname{lowbit}(x + 2^i)$: it must be $2^i$, because $x$ has so far only accumulated values $2^j$ with $j > i$. So the range covered by $c[x + 2^i]$ is exactly $[x + 1 \ldots x + 2^i]$.

This brings the time complexity down to $\Theta(\log n)$.

???+ note "Implementation"
    === "C++"
        ```cpp
        // Fenwick tree over values: find the k-th smallest
        int kth(int k) {
          int sum = 0, x = 0;
          for (int i = log2(n); ~i; --i) {
            x += 1 << i;                   // try to extend
            if (x > n || sum + t[x] >= k)  // if the extension fails
              x -= 1 << i;
            else
              sum += t[x];
          }
          return x + 1;  // returns n + 1 if not found
        }
        ```
    
    === "Python"
        ```python
        # Fenwick tree over values: find the k-th smallest
        def kth(k):
            sum = 0
            x = 0
            i = int(log2(n))
            while ~i:
                x = x + (1 << i)  # try to extend
                if x > n or sum + t[x] >= k:  # if the extension fails
                    x = x - (1 << i)
                else:
                    sum = sum + t[x]
                i = i - 1
            return x + 1  # returns n + 1 if not found
        ```

### Global inversions (global 2D partial order)

Related reading and reference implementation: [Inversions](../math/permutation.md#逆序数)

Global inversions can also be counted neatly with a Fenwick tree over values. The problem is: given a sequence $a$ of length $n$, count the pairs $(i, j)$ in $a$ with $i < j$ and $a[i] > a[j]$.

Coordinate compression works for this problem: if the range of values in the original sequence $a$ is too large, compress it and then build the value-count array $b$.

Enumerate $i$ in reverse from $n$ to $1$ as the index of the first element of an inversion, count how many $j > i$ satisfy $a[j] < a[i]$, and add up the answers.

In fact, we only need to do this (let the current $a[i] = x$):

-   Query the prefix sum of $b[1 \ldots x - 1]$; this is the number of inversions whose left element is $a[i]$.
-   Increase $b[x]$ by $1$;

The reason is natural: elements counted in $b[1 \ldots x-1]$ must be smaller than the current $x = a[i]$, and since we enumerate $i$ in reverse, the elements already in the value-count array have original indices $j$ greater than the current index $i$.

Take $a = (4, 3, 1, 2, 1)$ as an example.

Scan $i$ from $5 \to 1$:

-   $a[5] = 1$: the prefix sum of $b[1 \ldots 0]$ is $0$; increase $b[1]$ by $1$, so $b = (1, 0, 0, 0)$.
-   $a[4] = 2$: the prefix sum of $b[1 \ldots 1]$ is $1$; increase $b[2]$ by $1$, so $b = (1, 1, 0, 0)$.
-   $a[3] = 1$: the prefix sum of $b[1 \ldots 0]$ is $0$; increase $b[1]$ by $1$, so $b = (2, 1, 0, 0)$.
-   $a[2] = 3$: the prefix sum of $b[1 \ldots 2]$ is $3$; increase $b[3]$ by $1$, so $b = (2, 1, 1, 0)$.
-   $a[1] = 4$: the prefix sum of $b[1 \ldots 3]$ is $4$; increase $b[4]$ by $1$, so $b = (2, 1, 1, 1)$.

So the final answer is $0 + 1 + 0 + 3 + 4 = 8$.

Note that for each $i$, the two steps (query $b[1 \ldots x - 1]$ and increment $b[x]$) can be swapped: increment $b[x]$ first and then query $b[1 \ldots x - 1]$, without changing the answer. There are two ways to see this:

-   Updating $b[x]$ does not affect the query on $b[1 \ldots x - 1]$.
-   After swapping, we are really counting pairs with $i \le j$ and $a[i] > a[j]$. When $i = j$, $a[i] > a[j]$ never holds, so $i \le j$ is the same as $i < j$, and this is equivalent to the original inversion problem.

If we want the number of non-strict inversions ($i < j$ and $a[i] \ge a[j]$), we must instead query the sum of $b[1 \ldots x]$, and then the two steps can't be swapped. Again, two ways to see this:

-   Updating $b[x]$ **does affect** the query on $b[1 \ldots x]$.
-   After swapping, we are really counting pairs with $i \le j$ and $a[i] \ge a[j]$. When $i = j$, $a[i] \ge a[j]$ always holds, so $i \le j$ is **not the same as** $i < j$, and this is **not equivalent** to the original problem.

If we want the number of pairs with $i \le j$ and $a[i] \ge a[j]$, then the two steps do need to be swapped.

Also, for the original inversion problem, another approach is to enumerate $j$ forwards and count how many $i < j$ satisfy $a[i] > a[j]$. The method is as follows (let $x = a[j]$):

-   Query the range sum of $b[x + 1 \ldots V]$ (where $V$ is the size of $b$, that is, the range of values of $a$, or the range after coordinate compression).
-   Increase $b[x]$ by $1$.

Reason: elements counted in $b[x + 1 \ldots V]$ must be larger than the current $x = a[j]$, and since we enumerate $j$ forwards, the elements already in the value-count array have original indices $i$ less than the current index $j$.

Inversions can also be counted with [merge sort](../basic/merge-sort.md#inversions). This method avoids coordinate compression, and its time complexity is also $O(n\log n)$. Reference implementations of both algorithms are in the [Inversions](../math/permutation.md#逆序数) section.

## Maintaining non-invertible information with a Fenwick tree

For example, range minimum/maximum.

Note that although this method needs little code, both point updates and range queries take $\Theta(\log^2n)$ time, which is worse than the $\Theta(\log n)$ of a segment tree.

### Range query

We still use the earlier idea of jumping backwards from $r$ along $\operatorname{lowbit}$, but we must not jump past the left of $l$.

So when we reach $c[x]$, we first check whether the next jump target $x - \operatorname{lowbit}(x)$ is less than $l$:

-   If it is less than $l$, we merge **the single point $\boldsymbol{a[x]}$** into the total and then jump to $c[x - 1]$.
-   If it is at least $l$, we haven't gone out of range, so we merge $c[x]$ as usual and jump to $c[x - \operatorname{lowbit}(x)]$.

Below is code for the range maximum query as an example:

???+ note "Implementation"
    ```cpp
    int getmax(int l, int r) {
      int ans = 0;
      while (r >= l) {
        ans = max(ans, a[r]);
        --r;
        for (; r - lowbit(r) >= l; r -= lowbit(r)) {
          // Note: don't write the loop condition as r - lowbit(r) + 1 >= l,
          // or when l = 1, r jumps to 0 and loops forever
          ans = max(ans, C[r]);
        }
      }
      return ans;
    }
    ```

It can be shown that the algorithm above runs in $\Theta(\log^2n)$ time.

??? note "Proof of time complexity"
    Consider the highest bit where $r$ and $l$ differ. $r$ must have a $1$ there and $l$ a $0$ (since $r \ge l$).
    
    If $r$ still has a $1$ below this bit, then $r - \operatorname{lowbit}(r) \ge l$, so the next step must clear the lowest $1$ bit of $r$ to $0$;
    
    If this $1$ bit is the lowest $1$ bit of $r$, then whether we do $r \gets r - \operatorname{lowbit}(r)$ or $r \gets r - 1$, this $1$ bit of $r$ must become $0$.
    
    So after at most $\log n$ steps, the highest bit where $r$ and $l$ differ must move down by one. So the total time complexity is $\Theta(\log^2n)$.

### Point update

???+ note "Note"
    Before reading this section, make sure you understand the following two properties of the Fenwick tree's tree shape.
    
    -   Let $u = s \times 2^{k + 1} + 2^k$. Then $u$ has $k = \log_2\operatorname{lowbit}(u)$ children, numbered $u - 2^t(0 \le t < k)$.
    -   The ranges covered by the $c$ values of all children of $u$ join together to form exactly $[l(u), u - 1]$.
    
    The meaning and proofs of both properties can be found in the section [Properties of the Fenwick tree and its tree shape](#properties-of-the-fenwick-tree-and-its-tree-shape) on this page.

After updating $a[x]$, we only need to update the $c[y]$ where $y$ is an ancestor of $x$ in the Fenwick tree's tree shape.

For min/max (take max as an example), a common wrong idea is: if $a[x]$ is changed to $p$, update every $c[y]$ to $\max(c[y], p)$. Here is a counterexample: in $(1, 2, 3, 4, 5)$, change $5$ to $4$. The maximum is $4$, but the update above gives $5$. Setting $c[y]$ directly to $p$ is also wrong; a counterexample is changing the $3$ in the example above to $4$.

In fact, for non-invertible information, there is no way to update $c[y]$ directly from $p$. An update is really "removing" the old number from the range and then adding a new one. "Removing" affects the range information like an "inverse operation", and non-invertible information has no "inverse operation", so we can't update $c[y]$ directly.

In other words, for every affected $c[y]$, we must rebuild the information for its range.

Look at the children of $c[y]$. Their information must be correct (because we update children before parents), and these children together cover exactly $[l(y), y - 1]$. Merging in the single point $a[y]$ then gives $[l(y), y]$, which is $c[y]$. This way, we can rebuild each $c$ that needs updating by merging at most $\log n$ ranges.

???+ note "Implementation"
    ```cpp
    void update(int x, int v) {
      a[x] = v;
      for (int i = x; i <= n; i += lowbit(i)) {
        // enumerate the affected ranges
        C[i] = a[i];
        for (int j = 1; j < lowbit(i); j *= 2) {
          C[i] = max(C[i], C[i - j]);
        }
      }
    }
    ```

It is easy to see that the algorithm above runs in $\Theta(\log^2n)$ time.

### Building the tree

We can split it into $n$ point updates and build the tree in $\Theta(n\log^2n)$.

There is also a $\Theta(n)$ way to build the tree; see method 1 in the section [$\Theta(n)$ construction](#thetan-construction) on this page.

## Tricks

### $\Theta(n)$ construction

We use range sums as an example.

Method 1:

Each node's value is the sum of the values of its direct children. So we can think about contributions in reverse: once a node's value is final, use it to update its direct parent.

???+ note "Implementation"
    === "C++"
        ```cpp
        // Θ(n) construction
        void init() {
          for (int i = 1; i <= n; ++i) {
            t[i] += a[i];
            int j = i + lowbit(i);
            if (j <= n) t[j] += t[i];
          }
        }
        ```
    
    === "Python"
        ```python
        # Θ(n) construction
        def init():
            for i in range(1, n + 1):
                t[i] = t[i] + a[i]
                j = i + lowbit(i)
                if j <= n:
                    t[j] = t[j] + t[i]
        ```

Method 2:

As mentioned earlier, $c[i]$ covers the range $[i-\operatorname{lowbit}(i)+1, i]$, so we can first precompute a prefix-sum array $\mathrm{sum}$ and then compute the array $c$.

???+ note "Implementation"
    === "C++"
        ```cpp
        // Θ(n) construction
        void init() {
          for (int i = 1; i <= n; ++i) {
            t[i] = sum[i] - sum[i - lowbit(i)];
          }
        }
        ```
    
    === "Python"
        ```python
        # Θ(n) construction
        def init():
            for i in range(1, n + 1):
                t[i] = sum[i] - sum[i - lowbit(i)]
        ```

### Timestamp optimization

This is a very common trick for multiple test cases. If we clear the whole Fenwick tree by brute force for each new test case, we may exceed the time limit. Instead, we use a $\mathrm{tag}$ array that stores when each node was last used (that is, which test case last used it). On each operation, we compare the time in $\mathrm{tag}$ at that position with the current time to decide whether the position should be $0$ or the value stored in the array.

???+ note "Implementation"
    === "C++"
        ```cpp
        // timestamp optimization
        int tag[MAXN], t[MAXN], Tag;
        
        void reset() { ++Tag; }
        
        void add(int k, int v) {
          while (k <= n) {
            if (tag[k] != Tag) t[k] = 0;
            t[k] += v, tag[k] = Tag;
            k += lowbit(k);
          }
        }
        
        int getsum(int k) {
          int ret = 0;
          while (k) {
            if (tag[k] == Tag) ret += t[k];
            k -= lowbit(k);
          }
          return ret;
        }
        ```
    
    === "Python"
        ```python
        # timestamp optimization
        tag = [0] * MAXN
        t = [0] * MAXN
        Tag = 0
        
        
        def reset():
            Tag = Tag + 1
        
        
        def add(k, v):
            while k <= n:
                if tag[k] != Tag:
                    t[k] = 0
                t[k] = t[k] + v
                tag[k] = Tag
                k = k + lowbit(k)
        
        
        def getsum(k):
            ret = 0
            while k:
                if tag[k] == Tag:
                    ret = ret + t[k]
                k = k - lowbit(k)
            return ret
        ```

## Example problems

-   [Fenwick tree 1: point update, range query](https://loj.ac/problem/130)
-   [Fenwick tree 2: range update, point query](https://loj.ac/problem/131)
-   [Fenwick tree 3: range update, range query](https://loj.ac/problem/132)
-   [2D Fenwick tree 1: point update, range query](https://loj.ac/problem/133)
-   [2D Fenwick tree 2: range update, point query](https://loj.ac/problem/134)
-   [2D Fenwick tree 3: range update, range query](https://loj.ac/problem/135)
