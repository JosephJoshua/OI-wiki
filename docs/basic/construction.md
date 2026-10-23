author: leoleoasd, yzxoi, Estrella-Explore

This page gives a short introduction to constructive problems.

## Introduction

Constructive problems are a common type of problem in contests.

The answer to such a problem often follows some pattern, so even when the problem size grows quickly, there is still a chance to find the answer fairly easily.

This means that when solving one, you should think about how growing the problem size affects the answer, and whether that effect can be generalized. For example, when designing a dynamic programming solution, you need to think about what a transition from one state to the next one changes.

## Characteristics

A very notable feature of constructive problems is their high degree of freedom: a problem may have many valid constructions, but usually one fairly simple construction does the job. This seems to loosen the requirements and make the problem easier. But often it is exactly this freedom that leaves you with no clear direction and no idea where to start.

Another feature is that they are flexible in form and very varied. There is no general method or standard trick that solves all constructive problems. It is even hard to find anything the solutions have in common.

## Example problems

Below are some example problems to help you get a feel for the ideas behind constructive problems and to give you some inspiration. We suggest thinking each one through carefully before reading the solution. You are also welcome to share interesting constructive problems.

### Example 1

???+ note "[Codeforces Round #384 (Div. 2) C.Vladik and fractions](http://codeforces.com/problemset/problem/743/C)"
    For a given $n$, construct three pairwise distinct positive integers $x,y,z$ such that $\dfrac{1}{x}+\dfrac{1}{y}+\dfrac{1}{z}=\dfrac{2}{n}$.

??? note "Solution"
    The second sample hints at the construction.
    
    Split $\dfrac{2}{n}$ into $\dfrac{1}{n}+\dfrac{1}{n}$, then rewrite the second term as $\dfrac{1}{n+1}+\dfrac{1}{n(n+1)}$. So $n,n+1,n(n+1)$ is a valid answer. As a special case, there is no solution when $n=1$, because the sum of the reciprocals of three distinct positive integers is at most $1+\dfrac{1}{2}+\dfrac{1}{3}<2$.

### Example 2

???+ note "[Luogu P3599 Koishi Loves Construction](https://www.luogu.com.cn/problem/P3599)"
    Task1: Decide whether you can construct a permutation of $1\dots n$ (of length $n$) whose $n$ prefix sums are pairwise distinct modulo $n$, and if so, construct one.
    
    Task2: Decide whether you can construct a permutation of $1\dots n$ (of length $n$) whose $n$ prefix products are pairwise distinct modulo $n$, and if so, construct one.

??? note "Solution"
    For both tasks, when $n=1$ just take the permutation $[1]$. From now on assume $n>1$.
    
    For Task1:
    
    When $n$ is odd, no valid answer exists. When $n$ is even, we can construct a sequence of the form $n,1,n-2,3,\cdots$.
    
    First, notice that $n$ must be the first element of the sequence. Otherwise, the prefix sums just before and just after $n$ appears would be equal modulo $n$, which is not allowed.
    
    Next, let's think about how to construct the whole sequence:
    
    We can get the original sequence by constructing its prefix sum sequence instead. The differences between adjacent prefix sums (plus the first term) must be pairwise distinct modulo $n$, because the difference sequence of the prefix sums is exactly the original permutation.
    
    So we try to make the prefix sums, modulo $n$, look like
    
    $$
    0,1,-1,2,-2,\cdots
    $$
    
    It is easy to check that this satisfies all the constraints perfectly.
    
    For Task2:
    
    When $n$ is a composite number other than $4$, no valid answer exists. When $n=4$, take $[1,3,2,4]$ as a special case. When $n$ is prime, we can construct a sequence of the form $1,\dfrac{2}{1},\dfrac{3}{2},\cdots,\dfrac{n-1}{n-2},n$, where division means multiplying by the [modular inverse](../math/number-theory/inverse.md) modulo $n$ and then taking the representative in $[1,n]$.
    
    First, when does a solution exist?
    
    There is no solution when $n$ is a composite number other than $4$. For a composite number, there exist two smaller numbers $p,q$ with $p\times q \equiv 0 \pmod n$, such as $(3\times6)\bmod 9=0$. Once both $p$ and $q$ have appeared, every later prefix product is $0$. So composite numbers other than $4$ have no solution. As a special case, $4=2\times 2$, and no suitable $p,q$ exist, so a valid answer exists.
    
    Now, how do we construct the sequence?
    
    Using the same idea as task1, $1$ must be the first element. Otherwise, the prefix products just before and just after $1$ appears would be equal. Also, $n$ must be the last element, because every prefix product from the position of $n$ onward is $0$ modulo $n$. Looking at the samples, every one of them has a valid answer whose prefix products modulo $n$ are $1,2,3,\cdots,n$. So we can use the sequence described above to achieve this. We then only need to prove that these $n$ numbers are pairwise distinct.
    
    These numbers are each the inverse of one of $1 \cdots n-2$, plus $1$, so they are all different. This solves the problem.

### Example 3

???+ note "[AtCoder Grand Contest 032 B](https://atcoder.jp/contests/agc032/tasks/agc032_b)"
    Given an integer $N$, construct an undirected graph with $N$ vertices, numbered $1\ldots N$, that satisfies:
    
    -   It is a simple connected graph.
    -   There is an integer $S$ such that for every vertex, the sum of the indices of its neighbors is $S$.
    
    A solution is guaranteed to exist for the input.

??? note "Solution"
    By looking at the cases $n=3,4,5$, we can find a way to construct the graph.
    
    Build a complete $k$-partite graph where all $k$ parts have the same sum. Then every vertex has the same $S$, namely
    
    $$
    S=\dfrac{(k-1)\sum_{i=1}^{n}i}{k}.
    $$
    
    If $n$ is even, pair the numbers from both ends: $\{1,n\},\{2,n-1\}\cdots$.
    
    If $n$ is odd, put $n$ in a group by itself and pair up the remaining $n-1$ numbers: $\{n\},\{1,n-1\},\{2,n-2\}\cdots$.
    
    It is easy to show that the graph built this way is connected when $n\ge 3$, so we skip the details here.
    
    This solves the problem.

### Example 4

???+ note "[BZOJ 4971 'Lydsy1708 Monthly Contest' The Knapsack in Memory](https://vjudge.net/problem/BZOJ-4971)"
    After a long day of hard work, Little Q fell asleep. In his dream he recalled learning the 0/1 knapsack when he first started university. Back then, as a freshman, Little Q solved a simple 0/1 knapsack problem. The problem was:
    
    Given $n$ items with volumes $v_1,v_2,\ldots,v_n$, count the ways to choose some of them (choosing none is allowed) so that the total volume is exactly $w$. Since the answer can be very large, output it modulo $P$.
    
    Because he had stayed up late solving problems for so long, he could only see $w$ and $P$ in the sample input, and that the sample output was $k$. He couldn't make out how many items there were or what their volumes were. Even when he woke up, Little Q still couldn't see $n$ and $v$. Write a program to help Little Q recall that sample input.
    
    There are multiple test cases, with $50\le w\le20000$, $1\le P\le2^{30}$, $0\le k\le\min(20000,P-1)$. You must output $1\le n\le40$ items, with $1\le v_i\le20000$.

??? note "Solution"
    This is one of the constructive problems with the highest degree of freedom, which makes it hard to know where to begin.
    
    Since $k<P$, we can aim to directly construct a set of items whose number of ways is exactly $k$.
    
    One construction is to choose $i$ small items of volume $1$ and some large items of volume $w-t$, where $1\le i\le20$ and $0\le t\le i$. Since $i<w$ and $w-t\ge w-20>w/2$, any way to fill the knapsack exactly must use exactly one large item.
    
    Let $C$ be the number of ways contributed by each large item of volume $w-t$. Then $C=\dbinom{i}{t}$, and the contributions of different large items add up. Different items are counted separately even if they have the same volume.
    
    Let $f_{i,j}$ be the minimum number of large items needed when there are $i$ items of volume $1$ and the number of ways is $j$.
    
    Fix $i$. Set $f_{i,0}=0$ and all other states to $+\infty$. Compute the unbounded knapsack transition in increasing order of $j$:
    
    $$
    f_{i,j}=1+\min_{0\le t\le i;~C\le j}f_{i,j-C},\qquad 1\le j\le20000.
    $$
    
    Record the $t$ that achieves the minimum, and you can backtrack to recover the volume $w-t$ of each large item. Computing this for all $0\le k\le20000$ shows that $\min_{1\le i\le 20}(i+f_{i,k})\le 29<40$, so this precomputation range is enough.

??? note "Reference implementation"
    ```cpp
    --8<-- "docs/basic/code/construction/construction_1.cpp"
    ```
