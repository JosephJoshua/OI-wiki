???+ note "Tip"
    This article is still being edited and discussed. You are welcome to add more learning paths or share your ideas in the comments!

This article introduces a learning path for competitive programming.

This learning path is both a guide for beginners learning competitive programming and a checklist for review.

## 1 C++ basics

Start by learning C++ syntax, one step at a time.

### 1.1 Hello, World!

Begin your competitive programming journey with a `Hello, World!`!

At the same time, get a rough idea of what the basic structure of a C++ source program looks like.

-   [Hello, World!](../lang/helloworld.md)
-   [C++ syntax basics](../lang/basic.md)

### 1.2 Variables and operations

Computers were first invented to compute. So let's first learn how to do some simple calculations.

-   [Variables](../lang/var.md)
-   [Operations](../lang/op.md)

### 1.3 Control flow

#### 1.3.1 Branching

Sometimes we need to run different statements under different conditions. For that we use branching statements.

-   [Branching](../lang/branch.md)

Branching statements include the following:

-   if statements
-   if-else statements
-   if-elif-else statements
-   switch statements

#### 1.3.2 Loops

To run some statements many times, we use loop statements.

-   [Loops](../lang/loop.md)

Loop statements include the following:

-   for statements
-   while statements
-   do-while statements

### 1.4 Arrays and structs

Arrays store large amounts of data of the same type. Structs bundle several variables together.

-   [Arrays](../lang/array.md)
-   [Structs](../lang/struct.md)

### 1.5 Functions and recursion

Use functions to make your program modular and easier to write.

Recursion is a hurdle for beginners. "A function calling itself" does not sound easy to understand. But if you dig into it, you will find that "calling itself" and "calling another function" are not fundamentally different.

-   [Functions](../lang/func.md)
-   [Recursion & divide and conquer](../basic/divide-and-conquer.md)

## 2 CSP-J (Junior level)

### 2.1 Enumeration and simulation

By now you can use C++ to do some simple tasks, but that is far from enough.

To solve some simple problems, you need to learn to turn the logic in your head into code, by brute-force enumeration or simulation. This may not look very efficient, but sometimes it works well.

-   [Enumeration](../basic/enumerate.md)
-   [Simulation](../basic/simulate.md)

### 2.2 Recursion and divide and conquer

Recursion means a function keeps calling itself in its own definition. Divide and conquer means repeatedly splitting a problem into several subproblems, solving them, and then combining the results.

-   [Recursion & divide and conquer](../basic/divide-and-conquer.md)

### 2.3 Strings

A data type you will often meet in informatics problems is the string. You need to learn some STL functions for working with strings. Of course, simulation is also a good way to solve string problems.

-   [String basics](../string/basic.md)
-   [STL functions](../string/lib-func.md)

### 2.4 Sorting

When you have a set of data, how to turn it from unordered to ordered is also a very important question. When you have no idea how to solve a problem, try sorting the array. Sorting is also the basis of many algorithms that come later.

There are quite a few sorting methods, but once you understand them they are not hard to remember.

-   [Introduction to sorting](../basic/sort-intro.md)
-   [Selection sort](../basic/selection-sort.md)
-   [Bubble sort](../basic/bubble-sort.md)
-   [Insertion sort](../basic/insertion-sort.md)
-   [Counting sort](../basic/counting-sort.md)
-   [Radix sort](../basic/radix-sort.md)
-   [Quicksort](../basic/quick-sort.md)
-   [Merge sort](../basic/merge-sort.md)
-   [Heapsort](../basic/heap-sort.md)
-   [Bucket sort](../basic/bucket-sort.md)
-   [Sorting in the STL](../basic/stl-sort.md)

The NOI syllabus only requires three sorting algorithms at the Junior level: selection, bubble and insertion sort. But the others are not very hard either, and may appear in the first-round written exam, so they are all listed here.

### 2.5 Binary search and binary lifting

Binary search is essentially an application of divide and conquer: it keeps shrinking the search range until it finds the answer. Note, though, that this kind of search only works on ordered data structures.

-   [Binary search](../basic/binary.md)

Binary lifting is different: it keeps doubling, turning work over a linear range into logarithmic work, which greatly improves the time complexity. (This topic needs a little math background; it is fine to skip it for now.)

-   [Binary lifting](../basic/binary-lifting.md)

### 2.6 Search

At the Junior level, search problems often appear as maze problems, usually with map-like data. Search is also very commonly used to efficiently enumerate and build valid solutions, and it can also be used to earn partial credit.

#### 2.6.1 Depth-first search (DFS)

Depth-first search here means using recursive functions to conveniently implement brute-force enumeration. It is somewhat similar to the DFS algorithm in graph theory, but not exactly the same.

-   [DFS (search)](../search/dfs.md)

#### 2.6.2 Breadth-first search (BFS)

Treat each state as a vertex in a graph, and you can search it thoroughly, layer by layer.

-   [BFS (search)](../search/bfs.md)

#### 2.6.3 Search optimization

Many problems can be solved with DFS, but its complexity is clearly too high to pass. So you need some optimizations to make it run faster. Such optimizations cut out attempts that cannot succeed, and are called "pruning". Optimizations for BFS are more flexible, but the basic idea is the same.

-   [DFS pruning](../search/opt.md)

### 2.7 Introduction to data structures

#### 2.7.1 Linear data structures

Arrays, linked lists, queues and stacks are all linear structures. Used cleverly, they make many things convenient.

-   [Stack](../ds/stack.md)
-   [Queue](../ds/queue.md)
-   [Linked list](../ds/linked-list.md)

#### 2.7.2 More complex data structures

-   [Trees and binary trees](../graph/tree-basic.md)
-   [Graph concepts](../graph/concept.md)
-   [Storing graphs](../graph/save.md)

### 2.8 Introduction to dynamic programming

Dynamic programming (DP) is a method for solving complex problems by breaking the original problem into relatively simple subproblems.

Since dynamic programming is not a specific algorithm but a method for solving certain kinds of problems, it appears together with all kinds of data structures, and the related problems are very varied.

-   [Introduction to dynamic programming](../dp/index.md)

#### 2.8.1 Knapsack problems

You are given a knapsack with limited capacity and some items, each with a size and a value. Choose items to put in so that the total value is as large as possible. This is the first big hurdle for many OIers; from here on, algorithms start to get a bit harder to understand.

-   [Knapsack DP](../dp/knapsack/basic.md)

#### 2.8.2 Linear dynamic programming

One of the hardest parts of dynamic programming is designing the state, which needs constructive techniques. Once you have written down the state and the transition equation, finishing a DP problem is not hard.

-   [Constructive algorithms](../basic/construction.md)
-   [DP basics](../dp/basic.md)

Memoized search is a way of implementing search that records information about states already visited, so that the same state is never explored twice. For some problems, memoized search can also make the thinking easier.

Since memoized search makes sure each state is visited only once, it is also a common way to implement dynamic programming.

-   [Memoized search](../dp/memo.md)

#### 2.8.3 More complex dynamic programming

Interval DP is an extension of linear DP. When it splits a problem into stages, it depends heavily on the order in which elements appear within a stage and on which elements of the previous stage are merged to form them.

-   [Interval DP](../dp/interval.md)

### 2.9 Mathematics

#### 2.9.1 Arbitrary-precision arithmetic

What if even long long (or int64) is not big enough? Use arbitrary-precision (big number) arithmetic. It is essentially a simulation of the four basic operations.

-   [Big number arithmetic](../math/bignum.md)

#### 2.9.2 Base conversion

In computers, besides binary, octal and hexadecimal are also commonly used. Sometimes using the right base helps a lot in solving a problem.

-   [Numeral systems](../math/numeral-sys/base.md)

#### 2.9.3 Bitwise operations

Bitwise operations work on the binary representation of integers. Since computers store data in binary internally, bitwise operations are very fast.

There are 6 basic bitwise operations: bitwise AND, bitwise OR, bitwise XOR, bitwise NOT, left shift and right shift.

-   [Bitwise operations](../math/bit.md)

#### 2.9.4 Number theory

-   [Number theory basics](../math/number-theory/basic.md)
-   [Primes](../math/number-theory/prime.md)
-   [Sieves](../math/number-theory/sieve.md)
-   [Greatest common divisor](../math/number-theory/gcd.md)
-   [Euler's totient function](../math/number-theory/euler-totient.md)
-   [Prime factorization](../math/number-theory/pollard-rho.md)

#### 2.9.5 Combinatorial counting

-   [Permutations and combinations](../math/combinatorics/combination.md)
-   [Pigeonhole principle](../math/combinatorics/drawer-principle.md)
-   [Inclusion–exclusion principle](../math/combinatorics/inclusion-exclusion-principle.md)

***

You have now learned every algorithm within the scope of the Junior level. But to master them, you need to keep solving enough problems to consolidate what you have learned.
