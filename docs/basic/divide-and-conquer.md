author: fudonglai, AngelKitty, labuladong

This page explains the difference between recursion and divide and conquer, and how they are used together.

## Recursion

### Definition

In mathematics and computer science, recursion means defining a function in terms of itself. In computer science, it also means a way of solving a problem by repeatedly breaking it down into smaller subproblems of the same kind.

### Introduction

To understand recursion, you first have to understand recursion.

The basic idea of recursion is that a function calls itself, directly or indirectly. This turns solving the original problem into solving many smaller subproblems of the same kind. When solving it, you only need to think about how to split the original problem into suitable subproblems; you don't need to worry too much about how each subproblem gets solved.

Here are some examples that may help you understand recursion:

1.  [What is recursion?](./divide-and-conquer.md)
2.  How do you sort a pile of numbers? Answer: split it into two halves, sort the left half, then sort the right half, and finally merge them. As for how to sort the left and right halves, please read this sentence again.
3.  How old are you this year? Answer: one year older than I was last year. I was born in 1999.
4.  ![An example for understanding recursion](images/divide-and-conquer-1.png)

Recursion is very common in mathematics. For example, set theory formally defines the natural numbers like this: 1 is a natural number, and every natural number has a successor, which is also a natural number.

The two most important features of recursive code are the base case and the self-call. The self-call solves a subproblem, and the base case gives the answer to the simplest subproblem.

```cpp
int func(input value) {
  if (base case) return answer to the smallest subproblem;
  return func(smaller input);
}
```

### Why write recursive code

1.  The structure is clear and easy to read. For example, here is [merge sort](./merge-sort.md) implemented in different ways:

    === "C++"
        ```cpp
        --8<-- "docs/basic/code/divide-and-conquer/divide-and-conquer_1.cpp:sort"
        ```

    === "Python"
        ```python
        --8<-- "docs/basic/code/divide-and-conquer/divide-and-conquer_1.py:sort"
        ```

    In both versions, `merge(a, front, mid, end)` merges, in place, the two sorted closed ranges `[front,mid]` and `[mid+1,end]` of the same array.

2.  It is good practice for analyzing the structure of a problem. Once you have written enough recursion, you will quickly notice when a problem can be broken into smaller problems with the same structure, and you can then solve it efficiently.

### Drawbacks of recursion

When a program runs, recursion is implemented using the call stack. Each time a function is called, a new stack frame is pushed onto the stack; each time a function returns, a stack frame is popped. The stack is not infinitely large, so when the recursion goes too deep, it causes a **stack overflow**.

A recursive implementation may need extra space on the call stack, while an iterative implementation can use only constant extra space. For example, given the head of a linked list, compute its length:

```cpp
// A typical iterative traversal
int size(Node *head) {
  int size = 0;
  for (Node *p = head; p != nullptr; p = p->next) size++;
  return size;
}

// Recursive traversal, handling one node per level
int size_recursion(Node *head) {
  if (head == nullptr) return 0;
  return size_recursion(head->next) + 1;
}
```

[![Comparison of the two](images/divide-and-conquer-2.svg)](https://quick-bench.com/q/rZ7jWPmSdltparOO5ndLgmS9BVc)

### Optimizing recursion

Main pages: [Search optimization](../search/opt.md) and [Memoized search](../dp/memo.md)

A naive recursive implementation may make too many recursive calls and easily exceed the time limit. In that case, the recursion needs to be optimized.[^ref1]

## Divide and conquer

### Definition

Divide and conquer, as the name says, means "divide it up and conquer each part". You split a complex problem into two or more identical or similar subproblems, and keep splitting until the subproblems can be solved directly. The answer to the original problem is then obtained by combining the answers to the subproblems.

### How it works

The core idea of divide and conquer is "divide it up and conquer each part".

The process roughly has three steps: divide -> conquer -> combine.

1.  Divide the original problem into subproblems with the same structure;
2.  Once the division reaches a boundary that is easy to solve, solve the subproblems recursively;
3.  Combine the answers to the subproblems into the answer to the original problem.

Problems that divide and conquer can solve usually have these features:

-   Once the problem is made small enough, it can be solved easily.
-   The problem can be split into several smaller instances of the same problem. That is, the problem has optimal substructure: the answers to the subproblems it splits into can be combined into the answer to the problem itself.
-   The subproblems are independent of each other, meaning they share no common subproblems.

???+ warning "Note"
    If the subproblems are not independent, divide and conquer will solve the shared subproblems again and again, doing a lot of unnecessary work. Divide and conquer can still be used in that case, but [dynamic programming](../dp/basic.md) is usually a better choice.

Take merge sort as an example. Say the function that implements merge sort is called `merge_sort`. First be clear about what the function is responsible for: **sorting the array passed to it**. This problem can clearly be broken down. Sorting an array is the same as sorting its left half and its right half separately, then merging them into one array.

```cpp
void merge_sort(an array) {
  if (easy to handle) return;
  merge_sort(left half of the array);
  merge_sort(right half of the array);
  merge(left half of the array, right half of the array);
}
```

Pass it half of an array, and when it's done, that half is sorted. Notice that `merge_sort` looks very much like the template for a post-order traversal of a binary tree. This is because the pattern of divide and conquer is **divide -> conquer (hit the bottom) -> combine (backtrack)**: first split into left and right, then do the combining. Backtracking is popping the stack, which is just like a post-order traversal.

The `merge` function works the same way as merging two sorted linked lists.

## Key points

### Key points for writing recursion

**Understand what a function does and trust that it will do it. Never jump into the function trying to work out every detail,** or you will get lost in endless details. How many stack frames can a human brain hold, anyway?

Take traversing a binary tree as an example.

```cpp
void traverse(TreeNode* root) {
  if (root == nullptr) return;
  traverse(root->left);
  traverse(root->right);
}
```

These few lines are enough to traverse any binary tree. For the recursive function `traverse(root)`, just trust that if you give it a root node `root`, it will traverse that tree. So all you need to do is pass the node's left and right children to the same function.

The same idea extends to traversing an $N$-ary tree, written in exactly the same way as for a binary tree. Of course, an $N$-ary tree has no in-order traversal.

```cpp
void traverse(TreeNode* root) {
  if (root == nullptr) return;
  for (auto child : root->children) traverse(child);
}
```

## Differences

### Recursion vs. enumeration

The difference between recursion and enumeration is this: enumeration splits a problem horizontally and solves the pieces one after another, while recursion breaks a problem down level by level, which is a vertical split.

### Recursion vs. divide and conquer

Recursion is a programming technique, a way of thinking about solving problems. Divide and conquer is an algorithmic idea for solving more specific problems, and it is largely built on recursion.

## Worked example

???+ note "[437. Path Sum III](https://leetcode-cn.com/problems/path-sum-iii/)"
    You are given a binary tree. Each node stores an integer value.
    
    Find the number of paths whose values add up to a given number.
    
    A path does not have to start at the root or end at a leaf, but it must go downward (only from parent nodes to child nodes).
    
    The binary tree has at most 1000 nodes, and node values are integers in the range $[-10^6,10^6]$.
    
    Example:
    
    ```text
    root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8
    
          10
         /  \
        5   -3
       / \    \
      3   2   11
     / \   \
    3  -2   1
    
    Return 3. The paths that sum to 8 are:
    
    1.  5 -> 3
    2.  5 -> 2 -> 1
    3. -3 -> 11
    ```
    
    ```cpp
    --8<-- "docs/basic/code/divide-and-conquer/divide-and-conquer_2.h"
    ```

??? note "Reference code"
    ```cpp
    --8<-- "docs/basic/code/divide-and-conquer/divide-and-conquer_2.cpp"
    ```

??? note "Solution"
    The problem looks complicated, but the code is extremely short.
    
    First, note that solving a tree problem recursively always requires traversing the whole tree, so the binary tree traversal framework (calling the function itself on the left and right subtrees) must appear in the main function pathSum. So what should each node do? Each node should count how many valid paths there are in itself and its subtrees. And that's it, the problem is solved.
    
    Following the technique described earlier, use this analysis to clearly define what each recursive function should do:
    
    The `pathSum` function: given a node and a target value, return the total number of paths in the tree rooted at this node whose sum equals the target value.
    
    The `count` function: given a node and a target value, return how many paths in the tree rooted at this node start at this node and have a sum equal to the target value.
    
    ??? note "Reference code"
        ```cpp
        --8<-- "docs/basic/code/divide-and-conquer/divide-and-conquer_2.cpp"
        ```
    
    Once again: **understand what each function can do, and trust that it will do it.**
    
    To sum up, the `pathSum` function provides the binary tree traversal framework, and calls the `count` function on each node during the traversal (pre-order traversal is used here, but in-order or post-order traversal works too). The `count` function is also a binary tree traversal; it finds paths that start at the given node and sum to the target value.

## Exercises

-   [Recursion practice on LeetCode](https://leetcode.com/explore/learn/card/recursion-i/)
-   [Divide and conquer practice on LeetCode](https://leetcode.com/tag/divide-and-conquer/)

## References and notes

[^ref1]: [labuladong's algorithm notes - Recursion explained](https://labuladong.gitbook.io/algo/suan-fa-si-wei-xi-lie/di-gui-xiang-jie)
