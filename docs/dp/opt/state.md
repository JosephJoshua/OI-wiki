author: Marcythm, partychicken, Xeonacid, hhc0001

## Overview

When optimizing a DP, you don't have to start only from the transitions and try to speed them up. Sometimes you can start from the state definition instead, and improve the complexity by changing how the states are designed.

The annoying part is that most of these optimizations are not general: you can't apply them to many problems as a fixed recipe. So the text below works through concrete example problems. The aim is to give you ideas and hopefully some useful inspiration.

## Example 1

???+ note "Problem statement"
    Given two strings $A,B$ of lengths $n,m$ consisting only of lowercase letters, find the longest common subsequence of $A$ and $B$. $(n\le 10^6,m\le 10^3)$

### Naive solution

You solve it at a glance. Isn't this just the template problem?

Let the state $f_{i,j}$ be the length of the longest common subsequence of the first $i$ characters of $A$ and the first $j$ characters of $B$. Then

$$
f_{i,j}=
\begin{cases}
\max(f_{i-1,j},f_{i,j-1}) & ,A_i \neq B_j \\
f_{i-1,j-1}+1 & ,A_i = B_j 
\end{cases}
$$

This approach takes $O(nm)$ time, which is too slow for this problem.

### Better solution

Thinking more carefully, we notice a property: the final answer can never exceed $m$.

Thinking a bit more, we notice that LCS has a greedy property.

Change the state definition: let $f_{i,j}$ be the length of the shortest prefix of $A$ whose longest common subsequence with the first $i$ characters of $B$ has length $j$. (In other words, swap the answer of the naive approach with the first dimension of the state.)

By precomputing, for each position of $A$, the next occurrence of each letter $a,b,\cdots,z$, we can do each forward transition in $O(1)$.

The complexity is $O(m^2+26n)$, which is fast enough for this problem.

## Example 2

???+ note "Problem statement"
    Given an unweighted directed graph with $n$ vertices, determine whether it has a Hamiltonian cycle. $(2\le n\le 20)$

### Naive solution

Looking at the constraints, we think of bitmask DP.

Let $f_{s,i}$ say whether we can start from vertex $1$, use only vertices in the set $s$, and reach vertex $i$. Let $g$ be the adjacency matrix of the graph. Then

$$
f_{s, i} = \bigvee_{j\in s, j\neq i}f_{s \setminus \{i\}, j}\wedge g_{j, i} \left(i\in s\right)
$$

The time complexity is $O(n^2 \times 2^n)$. A well-written version might pass, but it is not elegant.

### Better solution

In the state design above, each $dp$ value is just one `bool`, which feels a bit wasteful.

For each state $s$, we can pack $f_{s,1},f_{s,2},\dots,f_{s,n}$ into a single `int`. If we pack the adjacency matrix the same way, each transition takes $O(1)$.

The time complexity is $O(n^2/w\times 2^n)$, which passes this problem. Here $w$ is the number of bits in an `int`.

## Example 3

???+ note "Problem statement"
    A standard knapsack problem. $n$ is the number of items, $m$ is the knapsack capacity, and $v_i, w_i$ are the volume and value of the $i$-th item. $1 \le n \le 10^3$, $1 \le m, v_i \le \color{red}{10^{18}}$, $1 \le \sum w_i \le 10^3$.

### Naive solution

This is a template knapsack problem.

Let the state $f_{i, j}$ be the maximum total value when we have considered the first $i$ items and the items in the knapsack use $j$ units of capacity.

It is easy to get $f_{i, j} = \max(f_{i - 1, j}, f_{i - 1, j - v_i} + w_i)$.

Since $v_i \le 10^{18}$, this cannot pass the problem.

### Better solution

Swap the answer with the second dimension of the state: let $f_{i, j}$ be the minimum total volume when we have considered the first $i$ items and the items in the knapsack **have total value $j$**.

Again, it is easy to get $f_{i, j} = \min(f_{i - 1, j}, f_{i - 1, j - w_i} + v_i)$.

Note that once the second dimension of the state changes, the transition must change with it.

The time complexity is $O(n \sum w_i)$, which passes this problem.
