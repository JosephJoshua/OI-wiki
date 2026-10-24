## Introduction

The **Garsia–Wachs algorithm** is an efficient algorithm that a computer uses to build **optimal binary search trees** and **alphabetic Huffman codes** in **$O(n\log n)$ time**. It is named after Adriano Garsia and Michelle L. Wachs, who published the paper on it in 1977.

## Problem statement

Given an integer $n$ and $n+1$ nonnegative weights $w_{0},w_{1},\dots ,w_{n}$, build a rooted binary tree in which each of the $n$ internal nodes has two children, which means the tree has $n+1$ leaves. The $n+1$ input values are mapped one-to-one, in order, onto the leaves of the binary tree. The goal is to find, among all possible tree shapes with $n$ internal nodes, the tree that minimizes the weighted sum of the external path lengths from the root to each leaf.

### Optimal binary search trees

This problem can be understood as building a binary search tree for $n$ ordered keys, assuming the tree will only be used to search for values that are not in the tree. In this case, the $n$ keys split the space of search values into $n+1$ intervals, and the weight of each interval can be taken as the probability that a searched value falls into it. The weighted sum of the external path lengths controls the expected search time.

### Alphabetic Huffman codes

The problem can also be used to build Huffman codes. This is a way to encode $n+1$ given values unambiguously with variable-length sequences of binary digits. In this view, a value's code is given by the sequence of left and right steps from parent to child along the path from the root of the tree to the leaf (for example, $0$ for left and $1$ for right). Unlike standard Huffman codes, Huffman codes built this way are alphabetic: the sorted order of the binary codes is the same as the input order of the values. If a value's weight is its frequency in the message to be encoded, the output of the Garsia–Wachs algorithm is the alphabetic Huffman code that compresses the message to the shortest length.

## How it works

The Garsia–Wachs algorithm usually consists of three phases:

1.  Build a binary tree with the values at the leaves, possibly in the wrong order.
2.  Compute the distance from the root to each leaf in the tree.
3.  Build another binary tree with the same leaf distances, but in the correct order.

![](./images/garsia-wachs.png)

The figure above shows the binary tree built in the first phase by finding and merging out-of-order triples of the input sequence (left), and the correctly ordered binary tree output by the algorithm, whose leaf heights are the same as in the other tree.

The first phase is easier to describe if the input is extended with two sentinel values $\infty$ (or any large enough finite value) at the start and end of the sequence. So when using the Garsia–Wachs algorithm in contest solutions, for an array $\mathit{num}$ of length $n$, we usually define $\mathit{num}[0] = \mathit{num}[n+1] = \infty$.

The first phase maintains a forest that starts as one single-node tree for each non-sentinel input weight. Each tree is associated with a value, the sum of the weights of its leaves, and each non-sentinel input weight forms one tree node. The sequence of these values is maintained with a sentinel value at each end. The initial sequence is just the leaf weights in input order. Then the following steps are repeated, each one shortening the sequence, until only one tree contains all the leaves:

-   Find the first three consecutive weights $x$, $y$, $z$ in the sequence with $x \leq z$. Such a triple always exists, because the sentinel at the end of the sequence is larger than any two earlier finite values combined.
-   Remove $x$ and $y$ from the sequence, and create a new tree node as the parent of the $x$ and $y$ nodes, with value $x+y$.
-   Reinsert the new node just to the right of the nearest value before the old position of $x$ that is greater than or equal to $x+y$. Such a position always exists, because of the left sentinel.

To implement this phase efficiently, the algorithm can keep the current sequence of values in any balanced binary search tree structure. Such a structure lets us remove $x$ and $y$ and reinsert their new parent in logarithmic time. At every step, the weights at even indices up to $y$ form a decreasing sequence, and the weights at odd indices form another decreasing sequence. So the position to reinsert $x+y$ can be found in logarithmic time by two binary searches on these two decreasing sequences using the balanced tree. The search for the first position satisfying $x \leq z$ can be done in linear total time with a sequential search that starts from the $z$ of the previous triple.

The proof of the third phase of the Garsia–Wachs algorithm, namely that another tree with the same distances exists and that this tree gives the optimal solution, is important. But there are several proofs and they are too complicated, so we skip them here. Assuming the third phase is correct, the second and third phases are easy to implement in linear time. So on an input sequence of length $n$, the total time complexity of the Garsia–Wachs algorithm is $O(n\log n)$.

## Applications

The [garsia-wachs package](https://hackage.haskell.org/package/garsia-wachs) for the functional programming language Haskell gives a functional implementation of the Garsia–Wachs algorithm. It is mainly used to build optimal search tables, or to balance the [rope](https://hackage.haskell.org/package/rope) data structure with optimal complexity.

???+ note "Note"
    **rope** is a Haskell tool for working with [finger trees](../ds/finger-tree.md) of bytestrings with optional annotations.

## Example problems

???+ note "[POJ 1738 An old Stone Game](http://poj.org/problem?id=1738)"
    There is an old stone game. At the start, the player puts $n$($1 \leq n \leq 50000$) piles of stones in a row. The goal is to merge the stones into one pile under this rule: at each step, the player can merge two adjacent piles into a new pile, and scores the number of stones in the new pile. Find the minimum possible total score.

??? note "Solution idea"
    Stone merging is a classic problem, usually solved with interval DP. But when the input is large, like $n$($1 \leq n \leq 50000$) in this problem, the Garsia–Wachs algorithm is more efficient. Step one: set up an array $\mathit{num}[n]$ of size $n$, with $\mathit{num}[0] = \mathit{num}[n+1] = \infty$. Step two: each time, find the smallest $i$ with $\mathit{num}[i-1] \leq \mathit{num}[i+1]$, and merge $\mathit{num}[i-1], \mathit{num}[i]$ into $\mathit{temp}$; find the largest $j$ before it with $\mathit{num}[j] > \mathit{temp}$, and move $\mathit{temp}$ to just after $j$. Repeat this step until only $1$ pile is left.
    As for the rule that only adjacent piles may be merged: since $\mathit{num}[j]\geq \mathit{num}[i-1] + \mathit{num}[i]$, we can treat $\mathit{num}[j+1]$ through $\mathit{num}[i-2]$ as one block $\mathit{num}[mid]$, so $\mathit{sum}$ must be merged first. So the rule of the problem is not broken.

???+ note "[ATCODER N-Slimes](https://atcoder.jp/contests/dp/tasks/dp_n)"
    $N$ slimes stand in a row. At first, the $i$-th slime from the left has size $a_{i}$. Taro wants to combine all the slimes into one larger slime. He repeats the following operation until only one slime is left:
    Choose two adjacent slimes and combine them into a new slime. The new slime has size $x+y$, where $x$ and $y$ are the sizes of the slimes before combining. This step costs $x+y$. The relative positions of the slimes do not change when they are combined. Find the minimum possible total cost.

## References and further reading

1.  [Garsia–Wachs algorithm - Wikipedia](https://en.wikipedia.org/wiki/Garsia%E2%80%93Wachs_algorithm)
2.  [Data.Algorithm.GarsiaWachs - Hackage Haskell](https://hackage.haskell.org/package/garsia-wachs-1.2/docs/Data-Algorithm-GarsiaWachs.html)
3.  [garsia-wachs: A Functional Implementation of the Garsia-Wachs Algorithm](https://hackage.haskell.org/package/garsia-wachs)
4.  [Sentinel value - Wikipedia](https://en.wikipedia.org/wiki/Sentinel_value)
5.  [A new proof of the Garsia-Wachs algorithm](https://www.sciencedirect.com/science/article/abs/pii/0196677488900090)
