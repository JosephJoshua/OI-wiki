author: StudyingFather, Backl1ght, countercurrent-time, Ir1d, greyqz, MicDZ, ouuan, renbaoshuo, Lixuannan

Please make sure you already know ordinary Mo's algorithm. If not, first read the earlier page on [ordinary Mo's algorithm](./mo-algo.md).

## Features

Ordinary Mo's algorithm does not support modifications.

We can force it to support modifications. Just like in DP, we can add an extra dimension, the **time dimension**, which records the time of each operation.

The time dimension is the number of modifications that have happened so far.

That is, a query $[l,r]$ becomes $[l,r,\text{time}]$.

Now our position can also move along the time dimension. So $[l,r,\text{time}]$ gains one more direction to move in, and can become:

-   $[l-1,r,\text{time}]$
-   $[l+1,r,\text{time}]$
-   $[l,r-1,\text{time}]$
-   $[l,r+1,\text{time}]$
-   $[l,r,\text{time}-1]$
-   $[l,r,\text{time}+1]$

Each of these moves is still $O(1)$. The only difference is that sorting now has one more key, which is easy to handle.

By sorting and moving in a way similar to ordinary Mo's algorithm, we can reach $O(n^{5/3})$.

This time we sort by using blocks of size $n^{2/3}$, giving $n^{1/3}$ blocks. The first key is the block of the left endpoint, the second key is the block of the right endpoint, and the third key is the time.

???+ note "Optimal block size and time complexity analysis"
    Let the sequence length be $n$, with $m$ queries and $t$ modifications.
    
    Unlike ordinary Mo's algorithm, the second sorting key in Mo's algorithm with modifications is the block index of the right endpoint.
    
    Think about what happens if we do not split the right endpoints into blocks:
    
    -   If the right endpoints are unsorted, they move $n$ times per query.
    -   If the right endpoints are sorted, the times become unsorted, and time moves $t$ times per query.
    
    Either way, the running time is unacceptable.
    
    Next, we analyze the time complexity.
    
    Let the block size be $s$, so there are $\dfrac{n}{s}$ blocks. For blocks $i$ and $j$, let $q_{i,j}$ be the number of queries whose left endpoint is in block $i$ and right endpoint is in block $j$.
    
    For each "group" $(i,j)$ of queries where neither endpoint changes block, each endpoint moves $O(s)$ times per query, and the time increases monotonically, costing $O(t)$.
    
    The cost of endpoints changing blocks is negligible.
    
    Written out, this is:
    
    $$
    \begin{aligned}
    &\sum_{i=1}^{n/s}\sum_{j=i+1}^{n/s}(q_{i,j}\cdot s+t)\\
    =&ms+\left(\dfrac{n}{s}\right)^2t\\
    =&ms+\dfrac{n^2t}{s^2}
    \end{aligned}
    $$
    
    We find the minimum of this expression by taking the derivative. Let $f(s)=ms+\dfrac{n^2t}{s^2}$. Then $f'(s)=m-\dfrac{2n^2t}{s^3}=0$.
    
    This gives $s=\sqrt[3]{\dfrac{2n^2t}{m}}=\dfrac{2^{1/3}n^{2/3}t^{1/3}}{m^{1/3}}=s_0$.
    
    So when the block size is $\dfrac{n^{2/3}t^{1/3}}{m^{1/3}}$, we get the optimal time complexity $O\left(n^{2/3}m^{2/3}t^{1/3}\right)$.
    
    The commonly quoted $O\left(n^{5/3}\right)$ is the time complexity when $n,m,t$ are treated as being of the same order of magnitude.
    
    In practice, it is still recommended to use $n^{2/3}$ as the block size.

## Example problem

???+ note "Example problem [National Training Team — Counting Colors / Maintaining a Queue](https://www.luogu.com.cn/problem/P1903)"
    Summary: you are given a sequence and M operations of two kinds:
    
    1.  Change the number at some position of the sequence.
    2.  Ask how many distinct numbers there are in the interval $[l,r]$ (equal numbers count only once).

It is easy to see that without operation 1 (modification), we could solve this easily with ordinary Mo's algorithm.

But the problem also has point updates, so we use **Mo's algorithm with modifications**.

### How it works

First, recall how ordinary Mo's algorithm handles this:

-   When the interval grows, for each number added, check how many times it has already appeared. If it appeared $0$ times before being added, it is a new number, so the answer increases by $1$. Then increase that number's count by $1$.
-   When the interval shrinks, for each number removed, check its count after removal. If the count becomes $0$, that number has been completely removed from the current interval, meaning the interval has one fewer color, so the answer decreases by $1$. Then decrease that number's count by $1$.

Now consider modifications:

-   A point update changes the number at one position. If we move from a query that has seen $i$ modifications to a query that has seen $j$ modifications and $i<j$, we must apply modifications $i+1$ through $j$.
-   If $j<i$, we must undo modifications $i$ down to $j+1$.

How do we apply a modification? Suppose the modification changes the color at position $pos$ from $a$ to $b$, and suppose the current Mo's interval is $[l,r]$.

-   Applying the modification: first check whether $pos$ is inside $[l,r]$. If it is, this is the same as removing color $a$ from the interval and adding color $b$, and we also set the color at position $pos$ of the current color sequence to $b$. If $pos$ is not inside $[l,r]$, we just set position $pos$ of the current color sequence to $b$.
-   Undoing the modification: this is the same as applying a modification that changes position $pos$ from color $b$ back to color $a$.

And that is how Mo's algorithm with modifications solves this problem easily!

### Implementation

??? note "Reference code"
    ```cpp
    --8<-- "docs/misc/code/modifiable-mo-algo/modifiable-mo-algo_1.cpp"
    ```
