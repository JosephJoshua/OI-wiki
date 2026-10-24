## Definition

The minimum representation algorithm solves the problem of finding the minimum representation of a string.

## Minimum representation of a string

### Cyclic isomorphism

If we can choose a position $i$ in the string $S$ such that

$$
S[i\cdots n]+S[1\cdots i-1]=T
$$

then $S$ and $T$ are called cyclically isomorphic (cyclic shifts of each other)

### Minimum representation

The minimum representation of a string $S$ is the lexicographically smallest string among all strings cyclically isomorphic to $S$

## A simple brute force

Each time we compare the cyclic shifts starting at $i$ and at $j$. Let $k$ be the position currently being compared. Whenever we meet two different characters, we skip the larger one. What remains at the end is the optimal answer.

### Implementation

=== "C++"
    ```cpp
    int k = 0, i = 0, j = 1;
    while (k < n && i < n && j < n) {
      if (sec[(i + k) % n] == sec[(j + k) % n]) {
        ++k;
      } else {
        if (sec[(i + k) % n] > sec[(j + k) % n])
          ++i;
        else
          ++j;
        k = 0;
        if (i == j) i++;
      }
    }
    i = min(i, j);
    ```

=== "Python"
    ```python
    k, i, j = 0, 0, 1
    while k < n and i < n and j < n:
        if sec[(i + k) % n] == sec[(j + k) % n]:
            k += 1
        else:
            if sec[(i + k) % n] > sec[(j + k) % n]:
                i += 1
            else:
                j += 1
            k = 0
            if i == j:
                i += 1
    i = min(i, j)
    ```

### Explanation

This implementation works well on random data, but special test data can be constructed to make it slow.

For example, for $\texttt{aaa}\cdots\texttt{aab}$, it is easy to see that the complexity of this algorithm degrades to $O(n^2)$.

We notice that the algorithm becomes slow when the string contains many consecutive repeated substrings, so let us optimize this process.

## The minimum representation algorithm

### Core idea

Consider a pair of strings $A,B$ whose starting positions in the original string $S$ are $i,j$, and whose first $k$ characters are the same, that is,

$$
S[i \cdots i+k-1]=S[j \cdots j+k-1]
$$

First consider the case $S[i+k]>S[j+k]$. We find that no string whose starting index $l$ satisfies $i\le l\le i+k$ can be the answer. This is because for any string $S_{i+p}$ (the string starting at position $i+p$, $p \in [0, k]$), the string $S_{j+p}$ is always better.

So when comparing, we can skip the indices $l\in [i,i+k]$ and go straight to comparing $S_{i+k+1}$

This completes the optimization of the brute force above.

### Time complexity

$O(n)$

### How it works

1.  Initialize the pointer $i$ to $0$ and $j$ to $1$; initialize the match length $k$ to $0$
2.  Compare the characters at offset $k$, and move the corresponding pointer based on the result. If the two pointers become equal after moving, increase either one by one so that the two strings being compared are different
3.  Repeat the process above until the comparison ends
4.  The answer is the smaller of $i,j$

### Implementation

=== "C++"
    ```cpp
    int k = 0, i = 0, j = 1;
    while (k < n && i < n && j < n) {
      if (sec[(i + k) % n] == sec[(j + k) % n]) {
        k++;
      } else {
        sec[(i + k) % n] > sec[(j + k) % n] ? i = i + k + 1 : j = j + k + 1;
        if (i == j) i++;
        k = 0;
      }
    }
    i = min(i, j);
    ```

=== "Python"
    ```python
    k, i, j = 0, 0, 1
    while k < n and i < n and j < n:
        if sec[(i + k) % n] == sec[(j + k) % n]:
            k += 1
        else:
            if sec[(i + k) % n] > sec[(j + k) % n]:
                i = i + k + 1
            else:
                j = j + k + 1
            if i == j:
                i += 1
            k = 0
    i = min(i, j)
    ```
