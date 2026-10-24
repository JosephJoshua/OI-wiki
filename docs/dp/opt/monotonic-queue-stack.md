author: liujiaxi123456, Marcythm, hsfzLZH1, Ir1d, greyqz, Anguei, billchenchina, Chrogeek, ChungZH

## Introduction

Prerequisites: [Monotonic queue](../../ds/monotonic-queue.md), [Monotonic stack](../../ds/monotonic-stack.md).

A monotonic queue is mainly used to maintain the maximum/minimum of a range whose two endpoints both move forward (never backward). A monotonic stack is mainly used to find, for each value, the first earlier/later value that is greater/less than it.

???+ note "Note"
    -   To get the minimum, maintain a **strictly increasing/non-decreasing** monotonic queue/stack, and the other way around for the maximum.
    -   To maintain a strictly increasing/decreasing order, compare with **less than or equal/greater than or equal**; to maintain a non-decreasing/non-increasing order, compare with **less than/greater than**.

## Steps of monotonic queue optimization

-   Add the needed elements: keep pushing elements into the monotonic queue until the current element reaches the right end of the target range. This makes sure all needed elements are in the queue.
-   Pop out-of-range elements from the front: a monotonic queue really maintains the max/min of all inserted elements, but we usually want the max/min of a range. So we pop elements that are outside the left end, making sure every element in the queue is inside the target range.
-   Get the max/min: just take the front of the queue as the answer.

## Steps of monotonic stack optimization

-   Pop invalid tops: compare the current element with the top of the stack, and pop tops that would break the monotonic property. For example, with an increasing stack (largest at the top, used to maintain minimums), pop every element in the stack that is greater than or equal to the current element.
-   Add the current element: just push the current element onto the stack.

## Bounded knapsack with monotonic queue optimization

???+ note "Problem description"
    You have $n$ kinds of items. Item $i$ has weight $w_i$, value $v_i$, and there are $k_i$ copies of it. You have a knapsack with capacity $W$. Choose items to put into the knapsack so that the total weight does not exceed the capacity and the total value is as large as possible. Find the maximum value.

If you are not familiar with knapsack DP, please read [Knapsack DP](../knapsack/basic.md) first. Let $f_{i,j}$ be the maximum value when putting the first $i$ items into a knapsack of capacity $j$. The naive transition is

$$
f_{i,j}=\max_{k=0}^{k_i}(f_{i-1,j-k\times w_i}+v_i\times k)
$$

The time complexity is $O(W\sum k_i)$.

Let's optimize the transition for $f_i$. For convenience, let $g_{x,y}=f_{i,x\times w_i+y},g'_{x,y}=f_{i-1,x\times w_i+y}$, where $0\le y \lt w_i$. Then the transition can be written as:

$$
g_{x,y}=\max_{k=0}^{k_i}(g'_{x-k,y}+v_i\times k)
$$

Let $G_{x,y}=g'_{x,y}-v_i\times x$. Then the equation becomes:

$$
g_{x,y}=\max_{k=0}^{k_i}(G_{x-k,y})+v_i\times x
$$

Now this is the classic form for monotonic queue optimization. $G_{x,y}$ can be computed in $O(1)$, so for a fixed $y$, we can compute all $g_{x,y}$ in $O\left( \left\lfloor \dfrac{W}{w_i} \right\rfloor \right)$ time. So computing all $g_{x,y}$ takes $O\left( \left\lfloor \dfrac{W}{w_i} \right\rfloor \right)\times O(w_i)=O(W)$. The total complexity of the transitions drops to $O(nW)$.

In the implementation, we must enumerate $y$ first, so that the monotonic queue can be used while enumerating $x$. The queue stores $x-k$, not $k$, so when using it we get the corresponding $G_{x-k,y}$ through `f[last][q.front() * w[i] + y] - q.front() * v[i]`. It is easy to see that $x-k\in [x - k_i,x]$, so while enumerating $x$, we need to remove the elements of the queue that are outside this range.

??? note "Reference code"
    ```cpp
    --8<-- "docs/dp/code/opt/monotonic-queue-stack/monotonic-queue-stack_2.cpp"
    ```

## Exercises

???+ note "Example problem [CF372C Watching Fireworks is Fun](http://codeforces.com/problemset/problem/372/C)"
    Summary: a town has $n$ positions, and $m$ fireworks will be launched. Firework $i$ is launched at time $t_i$ at position $a_i$. If you are at position $x$ when it is launched, you gain $b_i-|a_i-x|$ happiness.
    
    You can start at any position, and in each unit of time you can move at most $d$ units of distance. Maximize the total happiness you get.

Let $f_{i,j}$ be the maximum happiness you can get if you are at position $j$ when the $i$-th firework is launched.

The state transition equation is: $f_{i,j}=\max\{f_{i-1,k}+b_i-|a_i-j|\}$, where $j-(t_{i}-t_{i-1})\times d\le k\le j+(t_{i}-t_{i-1})\times d$.

Let's rewrite it:

Since the $\max$ contains a fixed constant $b_i$, we can move it outside.

$f_{i,j}=\max\{f_{i-1,k}+b_i-|a_i-j|\}=\max\{f_{i-1,k}-|a_i-j|\}+b_i$

Once $i$ and $j$ are fixed, $|a_i-j|$ is also fixed, so we can move it outside too.

Finally, the formula becomes:

$$
f_{i,j}=\max\{f_{i-1,k}-|a_i-j|\}+b_i=\max\{f_{i-1,k}\}-|a_i-j|+b_i
$$

Now apply monotonic queue optimization. Since the $\max$ in the final formula only depends on the maximum over a contiguous segment of the previous state, when computing the states for a new $i$ we just build a monotonic queue over the old $f_{i-1}$ and maintain it, so that it gives $\max\{f_{i-1,k}\}$ in amortized $O(1)$ time. Then we compute $f_{i,j}$ from the formula.

The total time complexity is $O(nm)$.

??? note "Reference code"
    ```cpp
    --8<-- "docs/dp/code/opt/monotonic-queue-stack/monotonic-queue-stack_1.cpp"
    ```

-   [Luogu P1886 Sliding Window](https://loj.ac/problem/10175)
-   [NOI2005 Magnificent Waltz](https://www.luogu.com.cn/problem/P2254)
-   [SCOI2010 Stock Trading](https://loj.ac/problem/10183)
