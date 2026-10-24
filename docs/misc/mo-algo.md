author: StudyingFather, Backl1ght, countercurrent-time, Ir1d, greyqz, MicDZ, ouuan

## Form

Assume $n=m$. For range query problems on a sequence, if from the answer for $[l,r]$ we can get the answers for $[l-1,r],[l+1,r],[l,r+1],[l,r-1]$ (the intervals adjacent to $[l,r]$) in $O(1)$, then we can answer all queries in $O(n\sqrt{n})$ total time.

## Explanation

Read all queries offline and sort them, then process them in order, moving by brute force from the answer of the previous interval to the answer of the next one (just move one step at a time).

## Sorting method

For an interval $[l,r]$, sort in ascending order with the index of the block containing $l$ as the first key and $r$ as the second key.

## Implementation

```cpp
void move(int pos, int sign) {
  // update nowAns
}

void solve() {
  BLOCK_SIZE = int(ceil(pow(n, 0.5)));
  sort(queries, queries + m);
  for (int i = 0; i < m; ++i) {
    const query &q = queries[i];
    while (l > q.l) move(--l, 1);
    while (r < q.r) move(++r, 1);
    while (l < q.l) move(l++, -1);
    while (r > q.r) move(r--, -1);
    ans[q.id] = nowAns;
  }
}
```

## Complexity analysis

Below we assume $n$ and $m$ are of the same order.

First comes the blocking step, which takes $O(\sqrt{n}\cdot\sqrt{n}\log\sqrt{n}+n\log n)=O(n\log n)$ time.

Next comes the heart of Mo's algorithm. Below we use plain, middle-school-level reasoning to prove that its time complexity is $O(n\sqrt{n})$.

???+ note "Proof"
    Proof: let the maximum of $L$ in each block be $\max_1,\max_2,\max_3, \cdots , \max_{\lceil\sqrt{n}\rceil}$.
    
    From the first sorting key, $\max_1 \le \max_2 \le \cdots \le \max_{\lceil\sqrt{n}\rceil}$.
    
    Clearly, computing the first query of each block by brute force takes $O(n)$ time.
    
    In the worst case, the maximum of $R$ in every block is $n$, and every update has to move $L$ from $\max_{i - 1}$ to $\max_i$ or from $\max_i$ to $\max_{i - 1}$.
    
    Consider $R$: since $R$ is already sorted within a block, moving it within one block takes $O(n)$ time in total. Over all blocks that is $O(n\sqrt{n})$.
    
    Now focus on $L$: each change costs $O(\max_i-\max_{i-1})$, so within one block the cost is $O(\sqrt{n}\cdot(\max_i-\max_{i-1}))$.
    
    Adding up the cost of $L$ over all blocks, we get:
    
    The total time for $L$ is
    
    $$
    \begin{aligned}
    & O(\sqrt{n}(\max{}_1-1)+\sqrt{n}(\max{}_2-\max{}_1)+\sqrt{n}(\max{}_3-\max{}_2)+\cdots+\sqrt{n}(\max{}_{\lceil\sqrt{n}\rceil}-\max{}_{\lceil\sqrt{n}\rceil-1))} \\
    = \phantom{} & O(\sqrt{n}\cdot(\max{}_1-1+\max{}_2-\max{}_1+\max{}_3-\max{}_2+\cdots+\max{}_{\lceil\sqrt{n}\rceil-1}-\max{}_{\lceil\sqrt{n}\rceil-2}+\max{}_{\lceil\sqrt{n}\rceil}-\max{}_{\lceil\sqrt{n}\rceil-1)}) \\
    = \phantom{} & O(\sqrt{n}\cdot(\max{}_{\lceil\sqrt{n}\rceil}-1))\\
    \end{aligned}
    $$
    
    (telescoping sum)
    
    Since $\max_{\lceil\sqrt{n}\rceil}$ is at most $n$, the total time for $L$ in the worst case is $O(n\sqrt{n})$.

In summary, the time complexity of Mo's algorithm is $O(n\sqrt{n})$.

But for other values of $m$, such as $m<n$, the blocking needs to change to work better.

How should we choose the blocks?

Let the block size be $S$. For any number of queries in the same block, the right pointer moves a distance of $n$. There are $\displaystyle \frac{n}{S}$ blocks, so the total number of moves is $\displaystyle \frac{n^2}{S}$. Moves may also cross blocks, so we add $mS$, giving a total complexity of $\displaystyle O\left(\frac{n^2}{S}+mS\right)$. To make this as small as possible, we make the two terms as equal as possible, and find that $S = \displaystyle \frac{n}{\sqrt{m}}$ is optimal. The complexity is then $\displaystyle O\left(\frac{n^2}{\displaystyle \frac{n}{\sqrt{m}}}+m\left(\frac{n}{\sqrt{m}}\right)\right)=O(n\sqrt{m})$.

In fact, if the block size is not set correctly, the time complexity of Mo's algorithm suffers a lot. For example, if $m$ is of the same order as $\sqrt n$ and the block size is wrongly set to $\sqrt n$, it is easy to construct data that makes the complexity $O(n \sqrt n)$ instead of the correct $O(n^{5/4})$.

Mo's algorithm looks very brute-force, largely because its block-sorting method looks crude. We might think of sorting all intervals with a seemingly finer method. One way is to view each interval $[l, r]$ as a point $(l, r)$ in the plane, build a Manhattan minimum spanning tree on all points, and move the answer between queries along the edges of this tree. This looks like it could improve the time complexity of Mo's algorithm, but in fact the upper bound of the block-sorting method is already optimal.

Assume $n, m$ are of the same order and $n$ is a perfect square. Consider intervals of the form $[a \sqrt n, b \sqrt n](1 \le a, b \le \sqrt n)$; there are $n$ such intervals. If we view all intervals as points in the plane, the Manhattan distance between two points is exactly the cost of moving between the two intervals, and the minimum Manhattan distance between any two intervals is $\sqrt n$. So handling all queries takes at least $O(n \sqrt n)$ time. Data for other cases can be constructed similarly.

Mo's algorithm has one more feature: for fixed $n$, the larger $m$ is, the smaller the average transition cost per query. Some other offline algorithms share this feature (such as Tarjan's algorithm for LCA), but for Mo's algorithm the average transition cost changes most noticeably with $m$.

## Example problem & code

???+ note "Example problem [National Training Team: Little Z's Socks](https://www.luogu.com.cn/problem/P1494)"
    Summary:
    
    There is a sequence $\{c_i\}$ of length $n$. You are given $m$ queries. Each gives two numbers $l,r$; randomly choose two different numbers from those with indices between $l$ and $r$, and find the probability that the two numbers are equal.

### How it works

Idea: this is a template problem for Mo's algorithm.

For an interval $[l,r]$, sort in ascending order with the index of the block containing $l$ as the first key and $r$ as the second key.

Then compute answers starting from the first query. The first query is computed directly by brute force in $O(n)$, and each later query gets its answer based on the previous one.

Details:

For an interval $[i,i]$, there is only one element, so the answer is easy to know. Then move step by step from the current interval (whose answer is known) toward the next interval.

Let $col[i]$ be how many times color $i$ currently appears, and $ans$ the current number of valid pairs (the number of ways to pick a pair of socks of the same color). Update the answer on every move: let the current color be $k$. If the interval grows, add $\dbinom{col[k]+1}{2}-\dbinom{col[k]}{2}$ to $ans$; if it shrinks, subtract $\dbinom{col[k]}{2}-\dbinom{col[k]-1}{2}$ from $ans$. The answer to the query is $\displaystyle \frac{ans}{\dbinom{r-l+1}{2}}$.

Here is an optimization: $\displaystyle \dbinom{a}{2}=\frac{a (a-1)}{2}$.

So $\displaystyle \dbinom{a+1}{2}-\dbinom{a}{2}=\frac{(a+1) a}{2}-\frac{a (a-1)}{2}=\frac{a}{2}\cdot (a+1-a+1)=\frac{a}{2}\cdot 2=a$.

So $\dbinom{col[k]+1}{2}-\dbinom{col[k]}{2}=col[k]$.

Total complexity of the algorithm: $O(n\sqrt{n} )$

In the code below, `deno` is the denominator of the answer, `nume` is the numerator, `sqn` is the block size $\sqrt{n}$, `arr` is the input array, `node` is the struct that stores a query, `tab` is the (sorted) query list, and `col` is as described above.

**Note: because of `++l` and `--r`, the positions of the 4 while loops that move the interval in the code below are crucial. Do not change their relative order arbitrarily.**

??? note "Discussion of the order of the four loops"
    Moving the interval in Mo's algorithm is equivalent to having added the elements of $[1,r]$ and removed the elements of $[1,l-1]$. So:
    
    -   When $l\le r$, the elements of $[1,l-1]$ have been added once and removed once, the elements of $[l,r]$ have been added once, and the elements of $[r+1,+\infty)$ have not been added. This is a valid interval.
    -   When $l=r+1$, the elements of $[1,r]$ have been added once and removed once, and the elements of $[r+1,+\infty)$ have not been added. The interval is then empty.
    -   When $l>r+1$, the elements of $[r+1,l-1]$ (a nonempty range) have been removed once but never added, so their add count is negative.
    
    So if $l>r+1$ happens at some moment, some element has a negative add count. This causes trouble in some problems. For example, if we maintain all numbers in the interval with a `set`, we run into "needing to delete an element that is not in the `set`".
    
    The four while loops in the code can be ordered in $4!=24$ ways. Suppose the first loop moves the left endpoint; then there are the following $12$ orders (the other $12$ are symmetric). The table below shows whether each of these 12 orders is correct, with counterexamples for the wrong ones.
    
    | Loop order              | Correct? | Counterexample or note       |
    | ----------------- | --- | ----------- |
    | `l--,l++,r--,r++` | Wrong  | $l<r<l'<r'$ |
    | `l--,l++,r++,r--` | Wrong  | $l<r<l'<r'$ |
    | `l--,r--,l++,r++` | Wrong  | $l<r<l'<r'$ |
    | `l--,r--,r++,l++` | Correct  | Proof is tedious       |
    | `l--,r++,l++,r--` | Correct  |             |
    | `l--,r++,r--,l++` | Correct  |             |
    | `l++,l--,r--,r++` | Wrong  | $l<r<l'<r'$ |
    | `l++,l--,r++,r--` | Wrong  | $l<r<l'<r'$ |
    | `l++,r++,l--,r--` | Wrong  | $l<r<l'<r'$ |
    | `l++,r++,r--,l--` | Wrong  | $l<r<l'<r'$ |
    | `l++,r--,l--,r++` | Wrong  | $l<r<l'<r'$ |
    | `l++,r--,r++,l--` | Wrong  | $l<r<l'<r'$ |
    
    Of all 24 orders, only 6 are correct. The proofs for 2 of them are tedious, so we only prove 4 of them here.
    
    What these 4 correct orders have in common is that the first two steps grow the interval (`l--` or `r++`) and the last two steps shrink it (`l++` or `r--`). Growing the interval in the first two steps keeps $l\le r+1$. After the first two steps, $l\le l'\le r'\le r$ must hold, and the last two steps only shrink the interval down to $[l',r']$, so $l\le r+1$ still holds. Therefore this order is correct.

### Implementation

??? note "Reference code"
    ```cpp
    --8<-- "docs/misc/code/mo-algo/mo-algo_1.cpp"
    ```

## Optimizing ordinary Mo's algorithm

### How it works

Look at the following data:

```text
// Suppose the block size is 2
1 1
2 100
3 1
4 100
```

Simulating by hand, you can see the r pointer moves about 300 times. After we finish the first block, $l = 2, r = 100$. At that point we only need to move the l pointer twice to get the answer to the fourth query. Instead, we move the r pointer to 1 for the third query, then back to 100 for the fourth query, which costs ninety-odd extra pointer moves. How can we optimize this? Here we use odd-even sorting.

What is odd-even sorting? For queries in odd-numbered blocks, sort r in ascending order; for queries in even-numbered blocks, sort r in descending order. This way, after the r pointer finishes the queries of an odd block, it handles the queries of the even block on its way back, then moves toward n again for the next odd block. This reduces the number of r pointer moves. In general, this optimization makes the program about 30% faster.

### Implementation

Sorting code:

=== "Compact"
    ```cpp
    // clang-format off
    // There is a small detail here that will be explained below
    int unit; // Block size
    struct node {
      int l, r, id;
      bool operator < (const node &x) const {
        return l / unit == x.l / unit ? (r == x.r ? 0 : ((l / unit) & 1) ^ (r < x.r)) : l < x.l;
      }
    };
    ```

=== "Expanded"
    ```cpp
    struct node {
      int l, r, id;
    
      bool operator<(const node &x) const {
        if (l / unit != x.l / unit) return l < x.l;
        // Note: the next two lines must not use <= (>=), or it will go wrong (see the small detail below)
        if ((l / unit) & 1) return r < x.r;
        return r > x.r;
      }
    };
    ```

???+ warning "Small detail"
    When using `sort` to compare two structs, $a < b$ and $b < a$ must never both be true; otherwise you get a runtime error. See [common mistakes](../contest/common-mistakes.md#会导致-re) for details.

For the compact version, without the special check `r == x.r`, when the l values are in the same odd block and the r values are equal, the problem from the small detail above occurs (simulate it by hand). For the expanded version, writing <= (>=) causes the same problem.

## References

-   [Mo's algorithm study notes | Sengxian's Blog](https://blog.sengxian.com/algorithms/mo-s-algorithm)
