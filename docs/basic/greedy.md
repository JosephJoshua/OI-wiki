This page gives a short introduction to greedy algorithms.

## Introduction

A greedy algorithm uses a computer to simulate how a "greedy" person makes decisions. This person is very greedy: at every step, they always pick the best option according to some measure. They are also short-sighted: they only look at what is right in front of them and never think about what effect their choice may have later.

As you can imagine, the greedy method does not always find the optimal solution. So whenever you use a greedy method, you should make sure you can prove that it is correct.

## Explanation

### When it applies

Greedy algorithms work especially well on problems with optimal substructure. Optimal substructure means the problem can be broken into subproblems, and the optimal solutions of the subproblems can be combined step by step into the optimal solution of the whole problem.[^ref1]

### Proof

Common proof approaches are the exchange argument and mathematical induction. The two can also be combined.

1.  Exchange argument: start from any optimal solution. Through a finite number of exchanges or replacements, each of which keeps the solution feasible and does not make the objective worse, turn it into the solution produced by the greedy algorithm. This proves that the greedy solution is also optimal. Such proofs are often written as proofs by contradiction.
2.  Induction: first find the optimal solution $F_1$ for the base case (for example $n = 1$). Then prove that for every $n$, $F_{n+1}$ can be derived from $F_{n}$.

## Key points

### Common problem types

In problems below Senior Group difficulty, the two most common kinds of greedy are:

-   Sort XXX in some order, then choose items in some order (for example from smallest to largest).
-   Each time, take the largest/smallest thing in XXX and update XXX. (Sometimes taking the largest/smallest value can be sped up, for example by maintaining a priority queue.)

The difference is that the first kind is always offline: you can process everything first and then choose. The second kind may be online: you have to choose while processing.

### Sorting approach

The sorting method / adjacent exchange method is commonly used when the input is an array where each item has a few (usually one or two) weights. You find the optimal value by sorting and then simulating the computation in one pass.

???+ note "Example problem [NOIP 2012 King's Game](https://www.luogu.com.cn/problem/P1080)"
    It is the national day of country H, and the king invites $n$ ministers to play a game with prizes. First, he has each minister write one integer on their left hand and one on their right hand. The king also writes one integer on each of his own hands. Then the $n$ ministers line up in a row, with the king standing at the very front. Once the line is formed, every minister receives some gold coins from the king. The number of coins a minister gets is the product of the numbers on the left hands of everyone in front of him, divided by the number on his own right hand, rounded down.
    
    The king does not want any one minister to get an especially large reward. So he asks you to rearrange the line so that the largest reward any minister gets is as small as possible. Note that the king always stays at the front of the line.

??? note "Solution"
    Let $a_i, b_i$ be the numbers on the left and right hands of the $i$-th minister in the current order. We derive the greedy strategy with the adjacent exchange method.
    
    Ignore the rounding down for now, and let $s$ be the product of $a$ over everyone in front of minister $i$. Before swapping, the larger reward of the two ministers is
    
    $$
    \dfrac{s}{b_i b_{i+1}}\max(b_{i+1},a_i b_i),\tag{1}
    $$
    
    and after swapping, the larger reward of the two is
    
    $$
    \dfrac{s}{b_i b_{i+1}}\max(b_i,a_{i+1}b_{i+1}).\tag{2}
    $$
    
    If $a_i b_i\le a_{i+1}b_{i+1}$, then since $b_{i+1}\le a_{i+1}b_{i+1}$, expression $(1)$ is no larger than expression $(2)$. Rounding down is monotonic, and $\max(\lfloor u\rfloor,\lfloor v\rfloor)=\lfloor\max(u,v)\rfloor$, so swapping the two does not make the maximum reward smaller. Therefore sorting by $a_i b_i$ in increasing order gives an optimal answer.
    
    In the implementation, we store the two input numbers in a struct and overload the operator:
    
    ```cpp
    struct uv {
      int a, b;
    
      bool operator<(const uv& x) const { return 1LL * a * b < 1LL * x.a * x.b; }
    };
    ```

### Regret approach

The idea is to tentatively accept each new option. If this breaks a constraint, undo the option in the chosen set that is worst according to the greedy criterion. The strategy still needs a proof of correctness.

???+ note "Example problem ['USACO09OPEN' Work Scheduling](https://www.luogu.com.cn/problem/P2949)"
    John's workday starts at time $0$ and lasts $10^9$ units of time. In any unit of time, he can choose to complete any one of $N(1 \leq N \leq 10^5)$ jobs, numbered $1$ to $N$. Job $i$ has deadline $D_i(1 \leq D_i \leq 10^9)$, and completing it earns profit $P_i( 1\leq P_i\leq 10^9 )$. Given the profits and deadlines of the jobs, find the maximum total profit John can earn.

??? note "Solution"
    1.  First assume we do every job. Sort the jobs by deadline and push them into the queue;
    2.  When deciding whether to do job `i`: if its deadline allows it, take it. Otherwise, compare it with the job in the queue that has the smallest profit. If job `i` pays more (we "regret" the earlier choice), then `ans += a[i].p - q.top()`.  
        Use a priority queue (min-heap) so that the front element is always the smallest.
    3.  The condition `a[i].d<=q.size()` can be understood like this: from time 0 to time `a[i].d`, at most `a[i].d` jobs can be done. If `q.size()>=a[i].d`, then doing `q.size()` jobs takes at least `a[i].d` time. So when job `i` pays more, we should swap the smallest job out of the priority queue.

??? note "Reference code"
    === "C++"
        ```cpp
        --8<-- "docs/basic/code/greedy/greedy_1.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/basic/code/greedy/greedy_1.py"
        ```

??? note "Complexity analysis"
    -   Space complexity: with $n$ jobs as input, the array $a$ uses $n$ elements, and in the worst case the priority queue stores $n$ elements. So the space complexity is $O(n)$.
    -   Time complexity: `std::sort` takes $O(n\log n)$ time, and maintaining the priority queue takes $O(n\log n)$ time. Overall, the time complexity is $O(n\log n)$.

## Difference from dynamic programming

Ordinary greedy algorithms rely on local choices that can be proven safe. Dynamic programming instead keeps the optimal value for every state and compares candidate transitions.

## Exercises

-   ["USACO1.3" Barn Repair](https://www.luogu.com.cn/problem/P1209)
-   [Luogu P2123 Queen's Game](https://www.luogu.com.cn/problem/P2123)
-   [LeetCode problems tagged greedy](https://leetcode-cn.com/tag/greedy/)

## References and notes

[^ref1]: [Greedy algorithm - Wikipedia, the free encyclopedia (Chinese)](https://zh.wikipedia.org/wiki/%E8%B4%AA%E5%BF%83%E7%AE%97%E6%B3%95)
