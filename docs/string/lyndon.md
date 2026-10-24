author: sshwy, StudyingFather, orzAtalod

## Definition

First we introduce the concept of the Lyndon factorization.

Lyndon word: a string $s$ is called a simple string, or a **Lyndon word**, if $s$ is strictly lexicographically smaller than all of its suffixes. For example, `a`,`b`,`ab`,`aab`,`abb`,`ababb`,`abcd` are all Lyndon words. Equivalently, $s$ is a Lyndon word if and only if $s$ is strictly lexicographically smaller than all of its nontrivial cyclic shifts (nontrivial: non-empty and different from itself).

Lyndon factorization: the Lyndon factorization of a string $s$ is written $s=w_1w_2\cdots w_k$, where every $w_i$ is a simple string and they are in non-increasing lexicographic order, that is, $w_1\ge w_2\ge\cdots\ge w_k$. It can be shown that such a factorization exists and is unique.

## Duval's algorithm

### Explanation

Duval's algorithm finds the Lyndon factorization of a string in $O(n)$ time.

First we introduce another concept: if a string $t$ can be written as $t=ww\cdots\overline{w}$, where $w$ is a Lyndon word and $\overline{w}$ is a prefix of $w$ ($\overline{w}$ may be empty), then $t$ is called pre-simple, or a pre-Lyndon word. A Lyndon word is also a pre-Lyndon word.

Duval's algorithm uses a greedy idea. During the algorithm we split the string $s$ into three parts $s=s_1s_2s_3$, where $s_1$ is a Lyndon word whose Lyndon factorization has already been recorded, $s_2$ is a pre-Lyndon word, and $s_3$ is the part not yet processed.

### How it works

In short, at each step the algorithm tries to append the first character of $s_3$ to the end of $s_2$. If $s_2$ is no longer a pre-Lyndon word, we can cut off some prefixes of $s_2$ (that is, parts of the Lyndon factorization) and append them to the end of $s_1$.

Let us explain the process in more detail. Let a pointer $i$ point to the first character of $s_2$; $i$ runs from $1$ to $n$ (the length of the string). Inside the loop, we let another pointer $j$ point to the first character of $s_3$, and a pointer $k$ point to the character of $s_2$ we are currently looking at (it is the character corresponding to $j$ in the previous period of $s_2$). Our goal is to append $s[j]$ to the end of $s_2$, so we compare $s[j]$ with $s[k]$:

1.  If $s[j]=s[k]$, appending $s[j]$ to the end of $s_2$ does not break its pre-simplicity. So we just increment the pointers $j,k$ (move them to the next position).
2.  If $s[j]>s[k]$, then $s_2s[j]$ becomes a Lyndon word. So we increment the pointer $j$ and let $k$ point to the first character of $s_2$. Now $s_2$ becomes a new Lyndon word that repeats only once.
3.  If $s[j]<s[k]$, then $s_2s[j]$ is no longer pre-simple. So we split off a Lyndon substring from $s_2$; its length is $j-k$, which is one period of $s_2$. Then $s_2$ becomes what remains after the split, and we keep looping (note that in this case we do not change the pointers $j,k$) until all full periods have been cut off. For the remaining part, we just "roll back" our progress to the start of the remaining part.

### Implementation

The code below returns the Lyndon factorization of the string $s$.

=== "C++"
    ```cpp
    // duval_algorithm
    vector<string> duval(string const& s) {
      int n = s.size(), i = 0;
      vector<string> factorization;
      while (i < n) {
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) {
          if (s[k] < s[j])
            k = i;
          else
            k++;
          j++;
        }
        while (i <= k) {
          factorization.push_back(s.substr(i, j - k));
          i += j - k;
        }
      }
      return factorization;
    }
    ```

=== "Python"
    ```python
    # duval_algorithm
    def duval(s):
        n, i = len(s), 0
        factorization = []
        while i < n:
            j, k = i + 1, i
            while j < n and s[k] <= s[j]:
                if s[k] < s[j]:
                    k = i
                else:
                    k += 1
                j += 1
            while i <= k:
                factorization.append(s[i : i + j - k])
                i += j - k
        return factorization
    ```

### Complexity analysis

Next we prove the complexity of this algorithm.

The outer loop runs at most $n$ times, because $i$ increases every time. The second inner loop is also $O(n)$, since it only records the Lyndon factorization. Now let us analyze the first inner loop. It is easy to see that the Lyndon words found in each iteration of the outer loop are longer than the remaining part we compared, so the total length of the remaining parts is less than $n$, and the inner loop runs at most $O(n)$ times. In fact, the total number of loop iterations is at most $4n-3$, so the time complexity is $O(n)$.

## Minimum representation (finding the smallest cyclic shift)

For a string $s$ of length $n$, we can use the algorithm above to find its minimum representation.

We build the Lyndon factorization of the string $ss$, then find the Lyndon word $t$ in this factorization whose start is less than $n$ and whose end is at least $n$. Using the properties of the Lyndon factorization, it is easy to prove that the first character of the substring $t$ is the first character of the minimum representation of $s$. That is, the $n$ characters starting at the beginning of $t$ form the minimum representation of $s$.

So we only need to record the start of each pre-Lyndon word during the factorization.

=== "C++"
    ```cpp
    // smallest_cyclic_string
    string min_cyclic_string(string s) {
      s += s;
      int n = s.size();
      int i = 0, ans = 0;
      while (i < n / 2) {
        ans = i;
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) {
          if (s[k] < s[j])
            k = i;
          else
            k++;
          j++;
        }
        while (i <= k) i += j - k;
      }
      return s.substr(ans, n / 2);
    }
    ```

=== "Python"
    ```python
    # smallest_cyclic_string
    def min_cyclic_string(s):
        s += s
        n = len(s)
        i, ans = 0, 0
        while i < n / 2:
            ans = i
            j, k = i + 1, i
            while j < n and s[k] <= s[j]:
                if s[k] < s[j]:
                    k = i
                else:
                    k += 1
                j += 1
            while i <= k:
                i += j - k
        return s[ans : ans + n / 2]
    ```

## Exercises

-   [UVa #719 - Glass Beads](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=660)

    **This page is mainly translated from the article [Декомпозиция Линдона. Алгоритм Дюваля. Нахождение наименьшего циклического сдвига](http://e-maxx.ru/algo/duval_algorithm) and its English translation [Lyndon factorization](https://cp-algorithms.com/string/lyndon_factorization.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**
