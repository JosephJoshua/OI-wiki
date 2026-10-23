author: Ir1d, ShadowsEpic, Fomalhauthmj, siger-young, MingqiHuang, Xeonacid, hsfzLZH1, orzAtalod, NachtgeistW

This page gives a short introduction to binary lifting.

## Definition

Binary lifting (also called doubling) means, as the name suggests, "growing by doubling". When we compute values by recurrence over a very large state space, an ordinary linear recurrence may be too slow or use too much memory. Instead, by growing in powers, we only compute the values at positions that are integer powers of $k$, and use them as representatives. When we need the value at some other position, we use the fact that "any integer can be written as a sum of powers of $k$" to build the needed value from the representatives computed earlier. So binary lifting also requires that the state space of the problem can be split up along powers of $k$. Usually $k$ is $2$.[^ref1]

This technique is used in many algorithms. The most common uses are the RMQ problem and finding the [LCA (lowest common ancestor)](../graph/lca.md).

## Applications

### The RMQ problem

See: [RMQ topic](../topic/rmq.md).

RMQ stands for Range Maximum/Minimum Query: finding the maximum (or minimum) value in a range. The way to solve RMQ with the binary lifting idea is the [sparse table](../ds/sparse-table.md).

### Finding the LCA with binary lifting on trees

See: [Lowest common ancestor](../graph/lca.md).

## Example problems

### Problem 1

???+ note "Example problem"
    How can you weigh every weight in $[0,31]$ using as few weights as possible? (Weights may only be placed on one side of the balance.)

??? note "Solution"
    The answer is to use five weights: 1, 2, 4, 8, 16. With them you can weigh everything in $[0,31]$. Likewise, to weigh everything in $[0,127]$, you can use seven weights: 1, 2, 4, 8, 16, 32, 64. If every weight we pick is a non-negative integer power of 2, we can weigh any amount we need with very few weights.
    
    For example, to weigh everything in $[0,1023]$, we only need 10 weights; to weigh everything in $[0,1048575]$, we only need 20. If the target range doubles, we only need 1 more weight. This is called "logarithmic" growth, because the number of weights needed is proportional to the logarithm of the target range.

### Problem 2

???+ note "Example problem"
    You are given a ring of length $n$ and a constant $k$. Each jump goes from point $i$ to point $(i+k)\bmod n+1$, and there are $m$ jumps in total. Each point has a weight $a_i$. Find the sum of the weights of the starting points of the $m$ jumps, modulo $10^9+7$.
    
    Constraints: $1\leq n\leq 10^6$, $1\leq m\leq 10^{18}$, $1\leq k\leq n$, $0\le a_i\le 10^9$.

??? note "Solution"
    Clearly we can't just simulate all $m$ jumps by brute force. $m$ can be as large as about $10^{18}$, so brute-force simulation would take far too long.
    
    So we need some preprocessing: combine some information in advance so that queries can be answered faster. But storing the result for every possible number of jumps would take too much time and memory.
    
    So how should we preprocess? Look back at the first example problem. Do you have an idea now?
    
    Back to this problem. We want to preprocess some information and then combine it into the answer as quickly as possible, while not storing too much. So we can preprocess information in units of non-negative integer powers of 2. This way the preprocessing only handles a small amount of information, and combining it later is also easy.
    
    For this problem, we precompute, for each point, the result of jumping 1, 2, 4, 8, ... steps from it (the point we land on and the sum of point weights along the way). Then to jump 13 steps, we just jump 1+4+8 steps. That is, jump 1 step from the start, then jump 4 steps from where we landed, then jump 8 more steps, adding up the precomputed weight sums along the way. This gives the weight sum for 13 steps.
    
    For $2^i$ steps starting from each point, store `go[i][x]`, the point reached after jumping $2^i$ steps from point $x$, and `sum[i][x]`, the sum of point weights collected when jumping $2^i$ steps from point $x$. For preprocessing, use two nested loops. Jumping $2^i$ steps can be seen as jumping $2^{i-1}$ steps and then another $2^{i-1}$ steps, since clearly $2^{i-1}+2^{i-1}=2^i$. So we have `sum[i][x] = sum[i-1][x]+sum[i-1][go[i-1][x]]` and `go[i][x] = go[i-1][go[i-1][x]]`.
    
    There are also some implementation details to watch for. To make sure nothing is counted twice or missed, we usually precompute weight sums as "half-open" ranges (closed on the left, open on the right). That is, for 1 step we only record the weight of the point itself; for 2 steps we only record the weights of the point and the next point. In other words, the weight of the end point is never included in `sum`. Then during preprocessing we can simply add the two parts' weight sums, without worrying that the end of the first part and the start of the second part get counted twice.
    
    Here $m\leq 10^{18}$. That looks scary, but in fact we only need to precompute levels $0$ through $59$ to solve it easily, which is much faster than brute force. In technical terms, the [time complexity](./complexity.md) of this approach is $\Theta(n\log m)$ for preprocessing and $\Theta(\log m)$ per query.

??? note "Reference code"
    ```cpp
    --8<-- "docs/basic/code/binary-lifting/binary-lifting_1.cpp"
    ```

## References and notes

[^ref1]: Quoted from Li Yudong, *Advanced Guide to Algorithm Competitions*, section 0x06 "Binary Lifting".
