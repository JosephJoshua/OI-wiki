## Description

Given a string $s$ of length $n$, find all pairs $(i, j)$ such that the substring $s[i \dots j]$ is a palindrome. A string $t$ is a palindrome when $t = t_{\text{rev}}$ ($t_{\text{rev}}$ is the reverse of $t$).

## Explanation

Clearly, in the worst case there can be $O(n^2)$ palindromes, so at first glance it seems there is no linear algorithm for this problem.

But the information about palindromes can be expressed in **a more compact way**: for each position $i = 0 \dots n - 1$, we find the values $d_1[i]$ and $d_2[i]$. They are the number of odd-length and even-length palindromes centered at position $i$, respectively. Seen another way, they are also the radius of the longest palindrome centered at position $i$ (the radii $d_1[i]$ and $d_2[i]$ both count the characters from position $i$ to the rightmost position of the palindrome).

For example, the string $s = \mathtt{abababc}$ has three odd-length palindromes centered at $s[3] = b$; the longest one has radius $3$, that is, $d_1[3] = 3$:

$$
a\ \overbrace{b\ a\ \underset{s_3}{b}\ a\ b}^{d_1[3]=3}\ c
$$

The string $s = \mathtt{cbaabd}$ has two even-length palindromes centered at $s[3] = a$; the longest one has radius $2$, that is, $d_2[3] = 2$:

$$
c\ \overbrace{b\ a\ \underset{s_3}{a}\ b}^{d_2[3]=2}\ d
$$

So the key idea is this: if there is a palindrome of length $l$ centered at some position $i$, then there are also palindromes of length $l - 2$, $l - 4$, and so on, centered at $i$. So the two arrays $d_1[i]$ and $d_2[i]$ are enough to describe all sub-palindromes of the string.

Surprisingly, there is a linear and fairly simple algorithm that computes these two "palindrome arrays" $d_1[]$ and $d_2[]$. In this article we describe it in detail.

## Solution

In general, this problem has several solutions: with string hashing it can be solved in $O(n \log n)$ time, and with a suffix array and fast LCA it can be solved in $O(n)$ time.

But the algorithm described here is **by far** the simplest, and it has smaller constant factors in both time and space. It was proposed by **Glenn K. Manacher** in 1975.

## The naive algorithm

To avoid ambiguity later, let us state what we mean by the "naive algorithm".

It works like this: for each center position $i$, it keeps increasing the answer by $1$ as long as possible, each time comparing a pair of corresponding characters.

This algorithm is slow: it computes the answer in $O(n^2)$ time.

The naive algorithm is implemented as follows:

???+ note "Implementation"
    === "C++"
        ```cpp
        vector<int> d1(n), d2(n);
        for (int i = 0; i < n; i++) {
          d1[i] = 1;
          while (0 <= i - d1[i] && i + d1[i] < n && s[i - d1[i]] == s[i + d1[i]]) {
            d1[i]++;
          }
        
          d2[i] = 0;
          while (0 <= i - d2[i] - 1 && i + d2[i] < n &&
                 s[i - d2[i] - 1] == s[i + d2[i]]) {
            d2[i]++;
          }
        }
        ```
    
    === "Python"
        ```python
        d1 = [0] * n
        d2 = [0] * n
        for i in range(0, n):
            d1[i] = 1
            while 0 <= i - d1[i] and i + d1[i] < n and s[i - d1[i]] == s[i + d1[i]]:
                d1[i] += 1
        
            d2[i] = 0
            while 0 <= i - d2[i] - 1 and i + d2[i] < n and s[i - d2[i] - 1] == s[i + d2[i]]:
                d2[i] += 1
        ```

## Manacher's algorithm

Here we only describe how the algorithm finds all odd-length sub-palindromes, that is, how it computes $d_1[]$. Finding all even-length sub-palindromes (computing the array $d_2[]$) only needs small changes to the odd case.

To compute quickly, we maintain the **bounds $[l, r]$** of the rightmost sub-palindrome found so far (that is, the palindrome with the largest $r$, where $l$ and $r$ are the positions of its left and right ends). Initially we set $l = 0$ and $r = -1$ (*-1* is not a reverse index here; it could be any negative number and is only there to make the start of the loop convenient).

### How it works

Now suppose we want to compute $d_1[i]$ for the next $i$, and all previous values of $d_1[]$ have already been computed. We compute it as follows:

-   If $i$ is outside the current sub-palindrome, that is, $i > r$, we run the naive algorithm.

    So we keep increasing $d_1[i]$, and at each step check whether the current substring $[i - d_1[i] \dots i + d_1[i]]$ ($d_1[i]$ is the radius, here and below) is a palindrome. The algorithm stops when we find the first pair of mismatched characters or reach the boundary of $s$. In both cases $d_1[i]$ is now computed. After that, remember to update $(l, r)$.

-   Now consider the case $i \le r$. We try to get some information from the values of $d_1[]$ already computed. First, reflect the position $i$ inside the sub-palindrome $(l, r)$, which gives $j = l + (r - i)$. Now look at the value $d_1[j]$. Since position $j$ is the mirror of position $i$, we can **almost always** set $d_1[i] = d_1[j]$. Here is an illustration of this idea (think of the palindrome centered at $j$ as being "copied" to the position centered at $i$):

    $$
    \ldots\
    \overbrace{
        s_l\ \ldots\
        \underbrace{
            s_{j-d_1[j]+1}\ \ldots\ s_j\ \ldots\ s_{j+d_1[j]-1}
        }_\text{palindrome}\
        \ldots\
        \underbrace{
            s_{i-d_1[j]+1}\ \ldots\ s_i\ \ldots\ s_{i+d_1[j]-1}
        }_\text{palindrome}\
        \ldots\ s_r
    }^\text{palindrome}\
    \ldots
    $$

    However, there is a **tricky case** that must be handled correctly: when the "inner" palindrome reaches the boundary of the "outer" palindrome, that is, $j - d_1[j] + 1 \le l$ (or equivalently, $i + d_1[j] - 1 \ge r$). Since symmetry is not guaranteed outside the "outer" palindrome, setting $d_1[i] = d_1[j]$ directly would be wrong: we do not have enough information to claim that the palindrome at position $i$ has the same length.

    In fact, to handle this case correctly, we should "truncate" the palindrome length, that is, set $d_1[i] = r - i + 1$. Then we run the naive algorithm to try to increase $d_1[i]$ as much as possible.

    This case is illustrated below (the palindrome centered at $j$ has been truncated to fit inside the "outer" palindrome):

    $$
    \ldots\
    \overbrace{
        \underbrace{
            s_l\ \ldots\ s_j\ \ldots\ s_{j+(j-l)}
        }_\text{palindrome}\
        \ldots\
        \underbrace{
            s_{i-(r-i)}\ \ldots\ s_i\ \ldots\ s_r
        }_\text{palindrome}
    }^\text{palindrome}\
    \underbrace{
        \ldots \ldots \ldots \ldots \ldots
    }_\text{try moving here}
    $$

    The illustration shows that although the palindrome centered at $j$ may be longer and extend beyond the "outer" palindrome, at position $i$ we can only use the part that lies entirely inside the "outer" palindrome. But the answer at position $i$ may be larger than this value, so we then run the naive algorithm to try to extend it beyond the "outer" palindrome, into the region marked "try moving here".

Finally, remember to update the values $(l, r)$ after computing each $d_1[i]$.

Also, let us repeat: the algorithm for the even-length palindrome array $d_2[]$ is very similar to the algorithm above for the odd-length palindrome array $d_1[]$.

## Complexity of Manacher's algorithm

Since we always run the naive algorithm when computing the answer for a given position, it is not obvious at first glance that the algorithm runs in linear time.

However, a more careful analysis shows that it is linear. It is worth pointing out that the [algorithm for computing the Z-function](./z-func.md) is quite similar to this one and also runs in linear time.

In fact, note that each iteration of the naive algorithm increases $r$ by $1$, and $r$ never decreases during the algorithm. These two observations tell us that the naive algorithm performs $O(n)$ iterations in total.

The other part of Manacher's algorithm is clearly linear too, so the total complexity is $O(n)$.

## Implementation of Manacher's algorithm

### Handling the two cases separately

To compute $d_1[]$, we have the following code:

=== "C++"
    ```cpp
    vector<int> d1(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
      int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
      while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
        k++;
      }
      d1[i] = k--;
      if (i + k > r) {
        l = i - k;
        r = i + k;
      }
    }
    ```

=== "Python"
    ```python
    d1 = [0] * n
    l, r = 0, -1
    for i in range(0, n):
        k = 1 if i > r else min(d1[l + r - i], r - i + 1)
        while 0 <= i - k and i + k < n and s[i - k] == s[i + k]:
            k += 1
        d1[i] = k
        k -= 1
        if i + k > r:
            l = i - k
            r = i + k
    ```

The code for $d_2[]$ is very similar, but the arithmetic expressions differ slightly:

=== "C++"
    ```cpp
    vector<int> d2(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
      int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
      while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
        k++;
      }
      d2[i] = k--;
      if (i + k > r) {
        l = i - k - 1;
        r = i + k;
      }
    }
    ```

=== "Python"
    ```python
    d2 = [0] * n
    l, r = 0, -1
    for i in range(0, n):
        k = 0 if i > r else min(d2[l + r - i + 1], r - i + 1)
        while 0 <= i - k - 1 and i + k < n and s[i - k - 1] == s[i + k]:
            k += 1
        d2[i] = k
        k -= 1
        if i + k > r:
            l = i - k - 1
            r = i + k
    ```

### Handling both cases together

Although in the explanation and the implementation above we computed $d_1[]$ and $d_2[]$ separately, a trick lets us reduce both to computing $d_1[]$.

Given a string $s$ of length $n$, we insert the separator $\#$ into each of its $n + 1$ gaps, building a string $s'$ of length $2n + 1$. For example, for the string $s = \mathtt{abababc}$, the corresponding $s' = \mathtt{\#a\#b\#a\#b\#a\#b\#c\#}$.

A $\#$ between letters stands for the corresponding "gap" in $s$. The $\#$ at both ends are only there to make the implementation easier.

Note that after computing $d_1[]$ for $s'$, for any position $i$, the longest sub-palindrome described by $d_1[i]$ must end with $\#$ (if it ended with a letter, that letter would have a $\#$ on each side, so we could extend it by one on each side to get a longer one). So for a maximal sub-palindrome of $s$ centered at a letter, with length $m + 1$, there is a corresponding maximal sub-palindrome in $s'$ centered at that letter with length $2m + 3$. And for a maximal sub-palindrome of $s$ centered at a gap, with length $m$, there is a corresponding maximal sub-palindrome in $s'$ centered at the $\#$ for that gap with length $2m + 1$ (in both cases $m$ is even, but whether this holds does not affect the conclusion). Combining these observations with a little calculation, it is easy to see that in $s'$, $d_1[i]$ equals **the total length plus one** of the maximal sub-palindrome of $s$ centered at the corresponding position.

This establishes the relation between $d_1[]$ of $s'$ and $d_1[]$ and $d_2[]$ of $s$.

Since this unified approach is really just computing $d_1[]$ of $s'$, once we have $s'$ the code is the same as the code for $d_1[]$ in the previous section.

## Exercises

-   [UVa #11475 "Extend to Palindrome"](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2470)
-   [National Training Team — Longest Double Palindrome](https://www.luogu.com.cn/problem/P4555)
-   [CF1326D2. Labyrinth](https://codeforces.com/contest/1326/problem/D2)

**This page is mainly translated from the article [Нахождение всех подпалиндромов](http://e-maxx.ru/algo/palindromes_count) and its English translation [Finding all sub-palindromes in $O(N)$](https://cp-algorithms.com/string/manacher.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**
