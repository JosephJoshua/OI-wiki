This page gives a short introduction to the string matching problem and how to solve it.

## The string matching problem

### Definition

Also called pattern matching. The problem can be summed up as "given strings $S$ and $T$, find the substring $T$ in the main string $S$". The string $T$ is called the pattern.

### Types

-   Single-pattern matching: given one pattern and one text, find all positions of the pattern in the text.
-   Multi-pattern matching: given several patterns and one text, find all positions of these patterns in the text.
    -   If there are several texts, you can simply join them together and treat them as one text.
    -   You could treat it directly as single-pattern matching, but that is not efficient enough.
-   Other types: for example, matching any suffix of one string, matching any suffix of several strings, and so on.

## Brute force

Called the BF (Brute Force) algorithm for short. The basic idea is to compare the first character of the main string $S$ with the first character of the pattern $T$. If they are equal, keep comparing the following characters of both; otherwise, move the pattern $T$ back to its first character and compare it again with the second character of the main string $S$. Repeat this until all characters of $S$ or $T$ have been compared.

### Implementation

=== "C++"
    ```cpp
    /*
     * s: the main string to search in
     * t: the pattern
     * n: length of the main string
     * m: length of the pattern
     */
    std::vector<int> match(char *s, char *t, int n, int m) {
      std::vector<int> ans;
      int i, j;
      for (i = 0; i < n - m + 1; i++) {
        for (j = 0; j < m; j++) {
          if (s[i + j] != t[j]) break;
        }
        if (j == m) ans.push_back(i);
      }
      return ans;
    }
    ```

=== "Python"
    ```python
    def match(s, t, n, m):
        if m < 1:
            return []
    
        ans = []
        for i in range(0, n - m + 1):
            for j in range(0, m):
                if s[i + j] != t[j]:
                    break
            else:
                ans.append(i)
        return ans
    ```

### Time complexity

Let $n$ be the length of the main string and $m$ the length of the pattern. Assume $m\ll n$.

When BF matching succeeds: in the best case, only one pass succeeds, taking $m$ comparisons, and every other, failed pass fails at the first character of the pattern, taking $n-m$ more comparisons. The total is $n$ comparisons, so the time complexity is $O(n)$. In the worst case, $n-m+1$ passes succeed, each taking $m$ comparisons, for a total of $m(n-m+1)$ comparisons, so the time complexity is $O(mn)$.

When BF matching fails: in the best case, every failed pass fails at the first character of the pattern, so the BF algorithm makes $n-m+1$ comparisons and the time complexity is $O(n)$. In the worst case, every failed pass fails at the last character of the pattern, so the BF algorithm makes $m(n-m+1)$ comparisons and the time complexity is $O(mn)$.

If the pattern has at least two different characters, the average time complexity of the BF algorithm is $O(n)$. But in OI problems, the given strings are usually not purely random.

## Hashing

See: [String hashing](./hash.md)

## The KMP algorithm

See: [Prefix function and the KMP algorithm](./kmp.md)
