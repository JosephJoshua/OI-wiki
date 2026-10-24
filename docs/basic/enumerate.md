author: Early0v0, frank-xjh, Great-designer, ksyx, qiqistyle, Tiphereth-A , Saisyc, shuzhouliu, Xeonacid, xyf007

This page gives a short introduction to enumeration.

## Introduction

Enumeration is a problem-solving strategy that guesses answers based on what is already known.

The idea is to keep guessing: try every candidate in the set of possibilities one by one, and check whether it satisfies the conditions of the problem.

## Key points

### Define the solution space

Build a simple, clear mathematical model.

When enumerating, think carefully: what are the possible cases? Which elements do we need to enumerate?

### Shrink the search space

What range should we enumerate over? Do we really need to enumerate everything?

When solving a problem by enumeration, always think these two questions through. Otherwise you will waste time.

### Choose a good enumeration order

Decide based on the problem. For example, if the problem asks for the largest prime that satisfies some condition, it naturally makes sense to enumerate from largest to smallest.

## Example problem

Here is an example of solving a problem by enumeration and then shrinking the enumeration range.

??? note "Example problem"
    Given an array whose elements are pairwise distinct and all nonzero, count the ordered pairs in the array whose sum is $0$.

??? note "Solution"
    The code that enumerates both numbers is easy to write.
    
    === "C++"
        ```cpp
        for (int i = 0; i < n; ++i)
          for (int j = 0; j < n; ++j)
            if (a[i] + a[j] == 0) ++ans;
        ```
    
    === "Python"
        ```python
        for i in range(n):
            for j in range(n):
                if a[i] + a[j] == 0:
                    ans += 1
        ```
    
    === "Java"
        ```java
        for (int i = 0; i < n; ++i)
          for (int j = 0; j < n; ++j)
            if (a[i] + a[j] == 0) ++ans;
        ```
    
    Let's see how to shrink the enumeration range. If $(a_i,a_j)$ satisfies the condition, then so does $(a_j,a_i)$. Also, since no element is $0$, any valid pair must have $i\ne j$. So we can enumerate only $j<i$, counting each unordered pair once, and then multiply the result by $2$ to get the number of ordered pairs. The code is:
    
    === "C++"
        ```cpp
        for (int i = 0; i < n; ++i)
          for (int j = 0; j < i; ++j)
            if (a[i] + a[j] == 0) ++ans;
        ans *= 2;
        ```
    
    === "Python"
        ```python
        for i in range(n):
            for j in range(i):
                if a[i] + a[j] == 0:
                    ans += 1
        ans *= 2
        ```
    
    === "Java"
        ```java
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < i; ++j)
                if (a[i] + a[j] == 0) ++ans;
        ans *= 2;
        ```
    
    Notice that this already shrinks the range of $j$, which cuts the running time of this code.
    
    We can optimize further.
    
    Do we really need to enumerate both numbers? Once we fix one number, the problem's condition already determines what the other number must be. If we can find a way to check directly whether that number exists, we save the time spent enumerating the second number. As a more advanced trick, when the value range allows it, we can use a bucket[^1] to record the numbers we have already seen.
    
    === "C++"
        ```cpp
        --8<-- "docs/basic/code/enumerate/enumerate_1.cpp"
        ```
    
    === "Python"
        ```python
        met = [False] * (MAXN * 2 + 1)
        for i in range(n):
            if met[MAXN - a[i]]:
                ans += 1
            met[a[i] + MAXN] = True
        ans *= 2
        ```
    
    === "Java"
        ```java
        boolean[] met = new boolean[MAXN * 2 + 1];
        for (int i = 0; i < n; ++i) {
            if (met[MAXN - a[i]]) ++ans;
            met[MAXN + a[i]] = true;
        }
        ans *= 2;
        ```

### Complexity analysis

-   Time complexity: one pass over the array $a$ is enough to solve the problem, so when $n$ is large enough the time complexity is $O(n)$.
-   Space complexity: $O(n+\max\{|x|:x\in a\})$.

## Exercises

-   [2811: Light-Off Problem - OpenJudge](http://bailian.openjudge.cn/practice/2811/)

## References and notes

[^1]: [Bucket sort](../basic/bucket-sort.md), the [majority element problem](../misc/main-element.md#offline-algorithm), and [an explanation of the bucket data structure on Stack Overflow](https://stackoverflow.com/questions/42399355/what-is-a-bucket-or-double-bucket-data-structure) (in English)
