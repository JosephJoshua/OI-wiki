author: Lyccrius, AtomAlpaca

## Overview

Sometimes we meet problems that look like a good fit for Mo's algorithm, but a single transition is not $O(1)$. In that case, using Mo's algorithm directly gives the wrong complexity even if we tune the block size.

If the contribution of each transition to the answer can be expressed as a difference, we can split these transitions apart, store them offline, and process them in batches with another algorithm.

Let $f(x, l, r)$ denote the contribution of $x$ with respect to $[l, r]$.

For example, when extending the current interval $[l, r]$ to $[l, r + 1]$, we need $f(a_{r + 1}, l, r)$. If it can be written as a difference, it becomes $f(a_{r + 1}, 1, r) - f(a_{r + 1}, 1, l - 1)$. The first term can be precomputed for every $r$. For the second term, we store each such term offline at the corresponding $l - 1$, then enumerate from small to large and process them with a sweep line. The other transition directions can be handled similarly.

This technique, which takes the transitions of the offline Mo's algorithm offline a second time, is called Mo's algorithm with secondary offline processing.

Let's understand it through actual problems.

## Example problems

???+ note "[Luogu P5047 \[Ynoi2019 Mock Contest\] Yuno loves sqrt technology II](https://www.luogu.com.cn/problem/P5047)"
    You are given a sequence $a$ of length $n$ and $m$ queries. Each query asks for the number of inversions in a range.
    
    Constraints: $1 \leq n,m \leq 10^5$, $0 \leq a_i \leq 10^9$.

With plain Mo's algorithm, each transition costs at least $O(\log n)$. Observe that each transition needs "the rank of a number within some range", and this information can be expressed as a difference over ranges, so we consider secondary offline processing.

When extending $[l, r]$ to $[l, r + 1]$, we need the number of values in $[l, r]$ that are greater than $a_{r + 1}$.
Let $f(x, r)$ be the number of values in $[1, r]$ greater than $a_x$, and $g(x, r)$ the number of values in $[1, r]$ less than $a_x$. Then the change in the answer can be written as $f(r + 1, r) - f(r + 1, l - 1)$.

Similarly, the change when shrinking $[l, r]$ to $[l, r - 1]$ can be written as $-f(r, r - 1) + f(r, l - 1)$; extending $[l, r]$ to $[l - 1, r]$ can be written as $g(l - 1, r) - g(l - 1, l - 2)$, and shrinking $[l, r]$ to $[l + 1, r]$ can be written as $- g(l, r) + g(l, l - 1)$.

The terms $f(x, x - 1)$ and $g(x, x - 1)$ in these formulas can be precomputed in $O(n \log n)$ with a Fenwick tree. For the other $f(x, p)$ and $g(x, p)$ terms, we store $x$ offline at $l$ and process them in batches.

Here is a space-saving trick: when processing each query, the $x$ values stored offline at $p$ form one contiguous segment. So we don't need to store every single move, only the segment being adjusted. This reduces the space from the total number of moves, $O(n\sqrt{m})$, to the number of queries, $O(m)$.

Now let's handle the problem we took offline the second time: insert numbers into a set, and query the rank of a number in the set. Mo's algorithm moves the endpoints $O(n\sqrt{m})$ times in total, while the array has only $O(n)$ length. So we use sqrt decomposition over values, with $O(\sqrt{n})$ insertion and $O(1)$ query.

With this, we solve the problem in $O(n \sqrt{m} + n \sqrt{n})$ time and $O(n + m)$ space.

Finally, note that what we computed is the change in the answer each time, not the answer itself, so we need to take prefix sums to get the final answers.

??? note "Sample code"
    ```cpp
    --8<-- "docs/misc/code/mo-algo-secondary-offline/mo-algo-secondary-offline_1.cpp"
    ```

???+ note "[Luogu P5501 \[LnOI2019\] Welcome Those Who Come, Don't Chase Those Who Leave](https://www.luogu.com.cn/problem/P5501)"
    Answer many queries for the sum of the "Abbi values" of all numbers in the range $[l, r]$.
    
    The Abbi value is defined as follows: if $a_i$ is the $k$-th smallest in the query range $[l,r]$, its "Abbi value" is $ka_i$.

Let $f(x,r)$ be the sum of the numbers in $[1,r]$ greater than $a_x$, and $g(x,r)$ the count of the numbers in $[1,r]$ greater than $a_x$. Then when we move the right endpoint to the right, the contribution is $f(r,r-1)-f(r,l-1) + a_r(r-l+ 1-(g(r,r-1)-g(r,l-1)))$. The other directions can be written out in the same way, so we won't go into them here.

The terms $f(r, r - 1)$ and $g(r, r - 1)$ above can again be precomputed, and the rest are stored offline at the other endpoint and processed with a sweep line. It is easy to see that we still have to handle $O(n)$ insertions and $O(n\sqrt{m})$ rank queries, so we again use sqrt decomposition over values.

??? note "Sample code"
    ```cpp
    --8<-- "docs/misc/code/mo-algo-secondary-offline/mo-algo-secondary-offline_2.cpp"
    ```
