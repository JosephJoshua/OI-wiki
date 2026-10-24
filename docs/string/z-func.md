author: LeoJacob, Marcythm, minghu6

Convention: string indices start from $0$.

## Definition

For a string $s$ of length $n$, define $z[i]$ as the length of the longest common prefix (LCP) of $s$ and $s[i,n-1]$ (the suffix starting at $s[i]$). Then $z$ is called the **Z-function** of $s$. In particular, $z[0] = 0$.

Outside China, the algorithm that computes this array is usually called the **Z Algorithm**, while in China it is called **extended KMP** (exKMP).

This article introduces an algorithm that computes the Z-function in $O(n)$ time, along with its various applications.

## Explanation

The following examples show the Z-function of a few different strings:

-   $z(\mathtt{aaaaa}) = [0, 4, 3, 2, 1]$
-   $z(\mathtt{aaabaab}) = [0, 2, 1, 0, 2, 1, 0]$
-   $z(\mathtt{abacaba}) = [0, 0, 1, 0, 3, 0, 1]$

## Naive algorithm

The naive algorithm for the Z-function takes $O(n^2)$ time:

???+ note "Implementation"
    === "C++"
        ```cpp
        vector<int> z_function_trivial(string s) {
          int n = (int)s.length();
          vector<int> z(n);
          for (int i = 1; i < n; ++i)
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
          return z;
        }
        ```
    
    === "Python"
        ```python
        def z_function_trivial(s):
            n = len(s)
            z = [0] * n
            for i in range(1, n):
                while i + z[i] < n and s[z[i]] == s[i + z[i]]:
                    z[i] += 1
            return z
        ```

## Linear algorithm

As with most algorithms in string topics, the key is to use the idea of automata: find a state transition under certain constraints, so that earlier states help us compute new states faster.

In this algorithm, we compute $z[i]$ in order for $i$ from $1$ to $n-1$ (with $z[0]=0$). While computing $z[i]$, we use the already computed values $z[0],\ldots,z[i-1]$.

For $i$, we call the interval $[i,i+z[i]-1]$ the **match segment** of $i$, also called the Z-box.

During the algorithm, we keep the match segment whose right endpoint is furthest to the right. For convenience, we denote it $[l,r]$. By definition, $s[l,r]$ is a prefix of $s$. When computing $z[i]$, we make sure that $l\le i$. Initially $l=r=0$.

While computing $z[i]$:

-   If $i\le r$, then by the definition of $[l,r]$ we have $s[i,r] = s[i-l,r-l]$, so $z[i]\ge \min(z[i-l],r-i+1)$. Then:
    -   If $z[i-l] < r-i+1$, then $z[i] = z[i-l]$.
    -   Otherwise $z[i-l]\ge r-i+1$. In this case, set $z[i] = r-i+1$, then extend $z[i]$ by brute force, checking the next character one at a time until it can no longer be extended.
-   If $i>r$, we just use the naive algorithm: compare starting from $s[i]$ and compute $z[i]$ by brute force.
-   After computing $z[i]$, if $i+z[i]-1>r$, we need to update $[l,r]$, i.e., set $l=i, r=i+z[i]-1$.

You can visit [this website](https://personal.utdallas.edu/~besp/demo/John2010/z-algorithm.htm) to see a simulation of the Z-function computation.

### Implementation

=== "C++"
    ```cpp
    vector<int> z_function(string s) {
      int n = (int)s.length();
      vector<int> z(n);
      for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r && z[i - l] < r - i + 1) {
          z[i] = z[i - l];
        } else {
          z[i] = max(0, r - i + 1);
          while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        }
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
      }
      return z;
    }
    ```

=== "Python"
    ```python
    def z_function(s):
        n = len(s)
        z = [0] * n
        l, r = 0, 0
        for i in range(1, n):
            if i <= r and z[i - l] < r - i + 1:
                z[i] = z[i - l]
            else:
                z[i] = max(0, r - i + 1)
                while i + z[i] < n and s[z[i]] == s[i + z[i]]:
                    z[i] += 1
            if i + z[i] - 1 > r:
                l = i
                r = i + z[i] - 1
        return z
    ```

## Complexity analysis

Each run of the inner `while` loop moves $r$ to the right by at least $1$, and $r< n-1$, so it runs only $n$ times in total.

The outer loop is a single linear pass.

The total complexity is $O(n)$.

## Applications

Let's now look at how the Z-function is used in several concrete situations.

These applications are largely similar to those of the [prefix function](./kmp.md).

### Finding all occurrences of a pattern

To avoid confusion, we call $t$ the **text** and $p$ the **pattern**. The problem is: find all occurrences of the pattern $p$ in the text $t$.

To solve this, we build a new string $s = p + \diamond + t$, i.e., we concatenate $p$ and $t$ with a separator character $\diamond$ in between (we choose $\diamond$ so that it never appears in $p$ or $t$).

First compute the Z-function of $s$. Then, for any $i$ in the range $[0,|t| - 1]$, look at the Z-function value $k = z[i + |p| + 1]$ of the suffix of $s$ starting at $t[i]$. If $k = |p|$, then $p$ occurs at position $i$ of $t$; otherwise it does not.

The time complexity (and also the space complexity) is $O(|t| + |p|)$.

### Number of distinct substrings

Given a string $s$ of length $n$, count the number of distinct substrings of $s$.

We compute the increase: knowing the number of distinct substrings of the current $s$, compute the number after appending one character to the end of $s$.

Let $k$ be the number of distinct substrings of the current $s$. We append a new character $c$ to the end of $s$. Clearly, some new substrings ending in $c$ appear (substrings ending in $c$ that did not appear before).

Let $t$ be the reverse of $s + c$ (the reverse is the string with the characters of the original in reverse order). Our task is to count how many prefixes of $t$ do not appear anywhere else in $t$. Compute the Z-function of $t$ and find its maximum $z_{\max}$. Then the reverses of the prefixes of $t$ with length at most $z_{\max}$ are substrings ending in $c$ that already appeared in $s$.

So the number of new substrings after appending $c$ to $s$ is $|t| - z_{\max}$.

The time complexity of the algorithm is $O(n^2)$.

It is worth noting that, in the same way, we can recompute the number of distinct substrings in $O(n)$ time after adding or deleting one character at either end (the back or the front).

### Period of a string

Given a string $s$ of length $n$, find its shortest full period, i.e., the shortest string $t$ such that $s$ is a concatenation of several copies of $t$.

Compute the Z-function of $s$. Then the length of the shortest period is the smallest divisor $i$ of $n$ such that $i+z[i]=n$.

The proof of this fact is the same as the one for the [prefix function](./kmp.md).

## Exercises

-   [Luogu P5410 [Template] Extended KMP/exKMP (Z-function)](https://www.luogu.com.cn/problem/P5410)
-   [Luogu P7114 [NOIP2020] String Matching](https://www.luogu.com.cn/problem/P7114)
-   [CF126B Password](http://codeforces.com/problemset/problem/126/B)
-   [UVa # 455 Periodic Strings](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=396)
-   [UVa # 11022 String Factoring](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1963)
-   [UVa 11475 - Extend to Palindrome](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2470)
-   [Codechef - Chef and Strings](https://www.codechef.com/problems/CHSTR)
-   [Codeforces - Prefixes and Suffixes](http://codeforces.com/problemset/problem/432/D)
-   [Leetcode 2223 - Sum of Scores of Built Strings](https://leetcode.com/problems/sum-of-scores-of-built-strings/)

**This page is mainly translated from the blog post [Z-функция строки и её вычисление](http://e-maxx.ru/algo/z_function) and its English translation [Z-function and its calculation](https://cp-algorithms.com/string/z-function.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**
