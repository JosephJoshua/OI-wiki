author: Ir1d, LeoJacob, Xeonacid, greyqz, StudyingFather, Marcythm, minghu6, Backl1ght

## Definitions of string prefixes and suffixes

For the definitions of prefix, proper prefix, suffix and proper suffix of a string, see [String basics](./basic.md).

## Prefix function

### Definition

Given a string $s$ of length $n$, its **prefix function** is defined as an array $\pi$ of length $n$.
Here $\pi[i]$ is defined as follows:

1.  If the substring $s[0\dots i]$ has a pair of equal proper prefix and proper suffix, $s[0\dots k-1]$ and $s[i - (k - 1) \dots i]$, then $\pi[i]$ is the length of this proper prefix (or proper suffix, since they are equal), that is, $\pi[i]=k$;
2.  If there is more than one such pair, then $\pi[i]$ is the length of the longest pair;
3.  If there is no such pair, then $\pi[i]=0$.

Put simply, $\pi[i]$ is the length of the longest proper prefix of the substring $s[0\dots i]$ that is also its proper suffix.

In mathematical notation:

$$
\pi[i] = \max_{k = 0 \dots i}\{k: s[0 \dots k - 1] = s[i - (k - 1) \dots i]\}
$$

In particular, we define $\pi[0]=0$.

### How it works

For example, for the string `abcabcd`:

$\pi[0]=0$, because `a` has no proper prefix or proper suffix, so it is 0 by definition

$\pi[1]=0$, because `ab` has no equal proper prefix and proper suffix

$\pi[2]=0$, because `abc` has no equal proper prefix and proper suffix

$\pi[3]=1$, because `abca` has only one pair of equal proper prefix and proper suffix: `a`, with length 1

$\pi[4]=2$, because the only equal proper prefix and proper suffix of `abcab` is `ab`, with length 2

$\pi[5]=3$, because the only equal proper prefix and proper suffix of `abcabc` is `abc`, with length 3

$\pi[6]=0$, because `abcabcd` has no equal proper prefix and proper suffix

In the same way, the prefix function of the string `aabaaab` is $[0, 1, 0, 1, 2, 2, 3]$.

## A naive algorithm for computing the prefix function

### How it works

Here is an algorithm that computes the prefix function directly from the definition:

-   In a loop, compute the values $\pi[i]$ in the order $i = 1\to n - 1$ ($\pi[0]$ is set to $0$).
-   To compute the current value $\pi[i]$, we let a variable $j$ try lengths starting from the largest proper prefix length, $i$.
-   If the proper prefix and proper suffix of the current length are equal, then this length is $\pi[i]$. Otherwise, decrease j by 1 and keep matching until $j=0$.
-   If $j = 0$ and there was still no match, set $\pi[i] = 0$ and move on to the next index $i + 1$.

???+ note "Implementation"
    The implementation is as follows:
    
    === "C++"
        ```cpp
        // Note:
        // string substr (size_t pos = 0, size_t len = npos) const;
        vector<int> prefix_function(string s) {
          int n = (int)s.length();
          vector<int> pi(n);
          for (int i = 1; i < n; i++)
            for (int j = i; j >= 0; j--)
              if (s.substr(0, j) == s.substr(i - j + 1, j)) {
                pi[i] = j;
                break;
              }
          return pi;
        }
        ```
    
    === "Python"
        ```python
        def prefix_function(s):
            n = len(s)
            pi = [0] * n
            for i in range(1, n):
                for j in range(i, -1, -1):
                    if s[0:j] == s[i - j + 1 : i + 1]:
                        pi[i] = j
                        break
            return pi
        ```
    
    === "Java"
        ```java
        static int[] prefix_function(String s) {
            int n = s.length();
            int[] pi = new int[n];
            for (int i = 1; i < n; i++) {
                for (int j = i; j >= 0; j--) {
                    if (s.substring(0, j).equals(s.substring(i - j + 1, i + 1))) {
                        pi[i] = j;
                        break;
                    }
                }
            }
            return pi;
        }
        ```

Clearly, this algorithm runs in $O(n^3)$ time, which leaves a lot of room for improvement.

## An efficient algorithm for computing the prefix function

### The first optimization

The first important observation is that **adjacent values of the prefix function increase by at most $1$**.

As the figure below shows, think of it this way: to make $\pi[i+1]$ as large as possible, the newly added character $s[i+1]$ must also match its corresponding character, that is, $s[i+1]=s[\pi[i]]$. In that case $\pi[i+1] = \pi[i]+1$.

$$
\underbrace{\overbrace{s_0 ~ s_1 ~ s_2}^{\pi[i] = 3} ~ s_3}_{\pi[i+1] = 4} ~ \dots ~ \underbrace{\overbrace{s_{i-2} ~ s_{i-1} ~ s_{i}}^{\pi[i] = 3} ~ s_{i+1}}_{\pi[i+1] = 4}
$$

So when we move to the next position, the value of the prefix function either increases by one, stays the same, or decreases.

???+ note "Implementation"
    The improved algorithm is now:
    
    === "C++"
        ```cpp
        vector<int> prefix_function(string s) {
          int n = (int)s.length();
          vector<int> pi(n);
          for (int i = 1; i < n; i++)
            for (int j = pi[i - 1] + 1; j >= 0; j--)  // improved: j=i => j=pi[i-1]+1
              if (s.substr(0, j) == s.substr(i - j + 1, j)) {
                pi[i] = j;
                break;
              }
          return pi;
        }
        ```
    
    === "Python"
        ```python
        def prefix_function(s):
            n = len(s)
            pi = [0] * n
            for i in range(1, n):
                for j in range(pi[i - 1] + 1, -1, -1):
                    if s[0:j] == s[i - j + 1 : i + 1]:
                        pi[i] = j
                        break
            return pi
        ```
    
    === "Java"
        ```java
        static int[] prefix_function(String s) {
            int n = s.length();
            int[] pi = new int[n];
            for (int i = 1; i < n; i++) {
                for (int j = pi[i - 1] + 1; j >= 0; j--) {
                    if (s.substring(0, j).equals(s.substring(i - j + 1, i + 1))) {
                        pi[i] = j;
                        break;
                    }
                }
            }
            return pi;
        }
        ```

In this first improved algorithm, the best case when computing each $\pi[i]$ is that the very first string comparison succeeds. So the baseline number of string comparisons is $n-1$.

Because `j = pi[i-1]+1` (with `pi[0]=0`) bounds the number of string comparisons, we can see that the upper bound on comparisons only grows by $1$ in the best case, and every extra comparison beyond the first uses up room for growth later.

From this we get the case with the most string comparisons: at least $1$ comparison used and at most $n-2$ comparisons accumulated, which gives $n-1 + n-2 = 2n-3$ string comparisons.

So after this optimization, computing the prefix function takes only $O(n)$ string comparisons, and the total complexity drops to $O(n^2)$.

### The second optimization

In the first optimization we discussed the best case for computing $\pi[i+1]$: $s[i+1]=s[\pi[i]]$, in which case $\pi[i+1] = \pi[i]+1$. Now let us push this idea further and discuss where to jump when $s[i+1] \neq s[\pi[i]]$.

![](images/prefix_str_1.svg)

As shown above, on a mismatch we want to find, for the substring $s[0\dots i]$, the second-longest length $j$ after $\pi[i]$ such that the prefix property at position $i$ still holds, that is, $s[0 \dots j - 1] = s[i - j + 1 \dots i]$:

$$
\overbrace{\underbrace{s_0 ~ s_1}_j ~ s_2 ~ s_3}^{\pi[i]} ~ \dots ~ \overbrace{s_{i-3} ~ s_{i-2} ~ \underbrace{s_{i-1} ~ s_{i}}_j}^{\pi[i]} ~ s_{i+1}
$$

If we find such a length $j$, we only need to compare $s[i + 1]$ and $s[j]$. If they are equal, then $\pi[i + 1] = j + 1$. Otherwise, we need to find the next-longest length $j^{(2)}$ after $j$ for the substring $s[0\dots i]$ that keeps the prefix property, and so on, until $j = 0$. If $s[i + 1] \neq s[0]$, then $\pi[i + 1] = 0$. The second comparison is illustrated below

![](images/prefix_str_2.svg)

Looking at the figure, since $s[0\dots \pi[i]-1] = s[i-\pi[i]+1\dots i]$, the second-longest length $j$ for $s[0\dots i]$ has the following property:

$$
s[0 \dots j - 1] = s[i - j + 1 \dots i]= s[\pi[i]-j\dots \pi[i]-1]
$$

This formula is illustrated below:

![](images/prefix_str_3.svg)

In other words, $j$ equals the prefix function value at $s[\pi[i]-1]$, which corresponds to the lower half of the figure, that is, $j=\pi[\pi[i]-1]$. Likewise, the next-longest length after $j$ equals the prefix function value at $s[j-1]$: $j^{(2)}=\pi[j-1]$.

This clearly gives us a transition formula for $j$: $j^{(n)}=\pi[j^{(n-1)}-1], \ \ (j^{(n-1)}>0)$

### The final algorithm

So in the end we can build an algorithm that does no string comparisons at all and performs only $O(n)$ operations.

And its implementation is surprisingly short and intuitive:

???+ note "Implementation"
    === "C++"
        ```cpp
        vector<int> prefix_function(string s) {
          int n = (int)s.length();
          vector<int> pi(n);
          for (int i = 1; i < n; i++) {
            int j = pi[i - 1];
            while (j > 0 && s[i] != s[j]) j = pi[j - 1];
            if (s[i] == s[j]) j++;
            pi[i] = j;
          }
          return pi;
        }
        ```
    
    === "Python"
        ```python
        def prefix_function(s):
            n = len(s)
            pi = [0] * n
            for i in range(1, n):
                j = pi[i - 1]
                while j > 0 and s[i] != s[j]:
                    j = pi[j - 1]
                if s[i] == s[j]:
                    j += 1
                pi[i] = j
            return pi
        ```
    
    === "Java"
        ```java
        static int[] prefix_function(String s) {
            int n = s.length();
            int[] pi = new int[n];
            for (int i = 1; i < n; i++) {
                int j = pi[i - 1];
                while (j > 0 && s.charAt(i) != s.charAt(j)) {
                    j = pi[j - 1];
                }
                if (s.charAt(i) == s.charAt(j)) {
                    j++;
                }
                pi[i] = j;
            }
            return pi;
        }
        ```

This is an **online** algorithm, meaning it processes data as it arrives. For example, you can read the string one character at a time and process each character right away to compute its prefix function value. The algorithm still has to store the string itself and the prefix function values computed so far. But if we know in advance the largest possible value $M$ of the prefix function, we only need to store the first $M + 1$ characters of the string and their prefix function values.

## Applications

### Finding a substring in a string: the Knuth–Morris–Pratt algorithm

This algorithm was published jointly by Knuth, Pratt and Morris in 1977[^kmp]. The task is a classic application of the prefix function.

#### How it works

Given a text $t$ and a string $s$, we want to find and report all occurrences of $s$ in $t$.

For simplicity, let $n$ be the length of the string $s$ and $m$ the length of the text $t$.

We build the string $s + \# + t$, where $\#$ is a separator that appears in neither $s$ nor $t$. Next we compute the prefix function of this string. Now consider what the prefix function values mean, apart from the first $n + 1$ values (those belonging to the string $s$ and the separator). By definition, $\pi[i]$ is the length of the longest proper substring ending at $i$ that is also a prefix. In our case, it is the length of the longest substring ending at $i$ that equals a prefix of $s$. Because of the separator, this length can never exceed $n$. And if $\pi[i] = n$ holds, then $s$ appears in full at this position (that is, it ends at position $i$). Note that this index refers to the string $s + \# + t$.

So if $\pi[i] = n$ holds at some position $i$, the string $s$ occurs in the string $t$ at position $i - (n - 1) - (n + 1) = i - 2n$. The figure below illustrates the indices.

![](./images/strstr_kmp_indices.svg)

As we mentioned when computing the prefix function, if we know the prefix function never exceeds some value, we do not need to store the whole string and the whole prefix function, only the beginning of each. In our case this means we only need to store the string $s + \#$ and its prefix function values. We can read the string $t$ one character at a time and compute the prefix function value at the current position.

So the Knuth–Morris–Pratt algorithm (KMP algorithm for short) solves this problem in $O(n + m)$ time and $O(n)$ memory.

???+ note "Implementation"
    === "C++"
        ```cpp
        vector<int> find_occurrences(string text, string pattern) {
          string cur = pattern + '#' + text;
          int sz1 = text.size(), sz2 = pattern.size();
          vector<int> v;
          vector<int> lps = prefix_function(cur);
          for (int i = 2 * sz2; i <= sz1 + sz2; i++) {
            if (lps[i] == sz2) v.push_back(i - 2 * sz2);
          }
          return v;
        }
        ```
    
    === "Python"
        ```python
        def find_occurrences(t, s):
            cur = s + "#" + t
            sz1, sz2 = len(t), len(s)
            ret = []
            lps = prefix_function(cur)
            for i in range(2 * sz2, sz1 + sz2 + 1):
                if lps[i] == sz2:
                    ret.append(i - 2 * sz2)
            return ret
        ```
    
    === "Java"
        ```java
        static List<Integer> find_occurrences(String text, String pattern) {
            String cur = pattern + '#' + text;
            int sz1 = text.length(), sz2 = pattern.length();
            List<Integer> v = new ArrayList<>();
            int[] lps = prefix_function(cur);
            for (int i = 2 * sz2; i <= sz1 + sz2; i++) {
                if (lps[i] == sz2) {
                    v.add(i - 2 * sz2);
                }
            }
            return v;
        }
        ```

### Periods of a string

For a string $s$ and $0 < p \le |s|$, if $s[i] = s[i+p]$ holds for all $i \in [0, |s| - p - 1]$, then $p$ is called a period of $s$.

For a string $s$ and $0 \le r < |s|$, if the prefix of $s$ of length $r$ equals the suffix of length $r$, then the prefix of $s$ of length $r$ is called a border of $s$.

If $s$ has a border of length $r$, then $|s|-r$ is a period of $s$.

From the definition of the prefix function, we can get the lengths of all borders of $s$: $\pi[n-1],\pi[\pi[n-1]-1], \ldots$.[^ref1]

So using the prefix function we can compute all periods of $s$ in $O(n)$ time. In particular, since $\pi[n-1]$ is the length of the longest border of $s$, $n - \pi[n-1]$ is the smallest period of $s$.

### Counting the occurrences of each prefix

In this section we discuss two problems at once. Given a string $s$ of length $n$, in the first version of the problem we want to count how many times each prefix $s[0 \dots i]$ occurs in the same string. In the second version we want to count how many times each prefix $s[0 \dots i]$ occurs in another given string $t$.

Let us solve the first problem first. Consider the prefix function value $\pi[i]$ at position $i$. By definition, it means that a prefix of $s$ of length $\pi[i]$ occurs at position $i$ and ends at $i$, and no longer prefix does. At the same time, shorter prefixes may also end at this position. It is easy to see that this is a question we already answered while computing the prefix function: given a prefix of length $j$ that is also a suffix ending at $i$, what is the next smaller prefix length $k < j$ such that the prefix of that length is also a suffix ending at $i$? So at position $i$ there end a prefix of length $\pi[i]$, a prefix of length $\pi[\pi[i] - 1]$, a prefix of length $\pi[\pi[\pi[i] - 1] - 1]$, and so on, until the length becomes $0$. Therefore we can compute the answer as follows.

???+ note "Implementation"
    === "C++"
        ```cpp
        vector<int> ans(n + 1);
        for (int i = 0; i < n; i++) ans[pi[i]]++;
        for (int i = n - 1; i > 0; i--) ans[pi[i - 1]] += ans[i];
        for (int i = 0; i <= n; i++) ans[i]++;
        ```
    
    === "Python"
        ```python
        ans = [0] * (n + 1)
        for i in range(0, n):
            ans[pi[i]] += 1
        for i in range(n - 1, 0, -1):
            ans[pi[i - 1]] += ans[i]
        for i in range(0, n + 1):
            ans[i] += 1
        ```

#### Explanation

In the code above, we first count how many times each prefix function value appears in the array $\pi$, and then compute the final answer: if we know that the prefix of length $i$ occurs exactly $\text{ans}[i]$ times, then this count must be added to the count of its longest substring that is both a suffix and a prefix. At the end, to count the original prefixes themselves, we add $1$ to every result.

Now consider the second problem. We use the trick from Knuth–Morris–Pratt: build the string $s + \# + t$ and compute its prefix function. The only difference from the first problem is that we only care about the prefix function values related to the string $t$, that is, $\pi[i]$ with $i \ge n + 1$. With these values, we can apply the same algorithm as in the first problem.

### The number of distinct substrings in a string

Given a string $s$ of length $n$, we want to count its distinct substrings.

We will solve this problem iteratively. In other words, knowing the current number of distinct substrings, we want a way to recompute this number after appending one character to the end of $s$.

Let $k$ be the current number of distinct substrings of $s$. We append a new character $c$ to $s$. Clearly, some new substrings end with the character $c$. We want to count those substrings that end with this character and that we have not seen before.

Build the string $t = s + c$ and reverse it to get the string $t^{\sim}$. Now our task is to count how many prefixes of $t^{\sim}$ do not occur anywhere else in $t^{\sim}$. If we compute the maximum value $\pi_{\max}$ of the prefix function of $t^{\sim}$, then the longest prefix that occurs in $s$ has length $\pi_{\max}$. Naturally, all shorter prefixes occur as well.

So the number of new substrings that appear after adding a new character is $|s| + 1 - \pi_{\max}$.

So for each added character we can compute the number of new substrings in $O(n)$ time, and the total complexity is $O(n^2)$.

Note that we can also recompute the number of distinct substrings when a character is added to the front, or when a character is removed from the end or the front.

### String compression

Given a string $s$ of length $n$, we want to find its shortest "compressed" representation. That is, we want to find the shortest string $t$ such that $s$ can be written as the concatenation of one or more copies of $t$.

Clearly, we only need to find the length of $t$. Once we know this length, the answer is the prefix of $s$ of that length.

Let us compute the prefix function of $s$. Using its last value $\pi[n - 1]$, we define $k = n - \pi[n - 1]$. We will prove that if $k$ divides $n$, then $k$ is the answer; otherwise there is no valid compression and the answer is $n$.

Suppose $n$ is divisible by $k$. Then the string can be split into blocks of length $k$. By the definition of the prefix function, the prefix of length $n - k$ equals the suffix of the same length. But this means the last block equals the second-to-last block, the second-to-last block equals the third-to-last block, and so on. As a result, all blocks are equal, so we can compress the string $s$ to length $k$.

???+ note "Proof"
    Of course, we still need to prove that this value is optimal. Indeed, if there were a compressed representation shorter than $k$, then the last prefix function value $\pi[n - 1]$ would have to be greater than $n - k$. So $k$ is the answer.
    
    Now suppose $n$ is not divisible by $k$. We will prove by contradiction that the answer is then $n$[^1]. Suppose the smallest compressed representation $r$ has length $p$ ($p$ divides $n$), so the string $s$ is split into $n / p \ge 2$ blocks. Then the last prefix function value $\pi[n - 1]$ must be greater than $n - p$ (if it were equal, $n$ would be divisible by $k$), which means the suffix it represents partly covers the first block. Now consider the second block of the string. This block can be read in two ways: first as $r_0 r_1 \dots r_{p - 1}$, and second as $r_{p - k} r_{p - k + 1} \dots r_{p - 1} r_0 r_1 \dots r_{p - k - 1}$. Since both readings describe the same string, we get a system of $p$ equations, which can be written briefly as $r_{(i + k) \bmod p} = r_{i \bmod p}$, where $\cdot \bmod p$ denotes the smallest non-negative residue modulo $p$.
    
    $$
    \begin{gathered}
    \overbrace{r_0 ~ r_1 ~ r_2 ~ r_3 ~ r_4 ~ r_5}^p ~ \overbrace{r_0 ~ r_1 ~ r_2 ~ r_3 ~ r_4 r_5}^p \\
    r_0 ~ r_1 ~ r_2 ~ r_3 ~ \underbrace{\overbrace{r_0 ~ r_1 ~ r_2 ~ r_3 ~ r_4 ~ r_5}^p ~ r_0 ~ r_1}_{\pi[11] = 8}
    \end{gathered}
    $$
    
    By the extended Euclidean algorithm we can find $x$ and $y$ such that $xk + yp = \gcd(k, p)$. By adding suitable multiples of the equation $pk - kp = 0$, we can get $x' > 0$ and $y' < 0$ such that $x'k + y'p = \gcd(k, p)$. This means that by repeatedly applying the equations of the system above, we get a new system $r_{(i + \gcd(k, p)) \bmod p} = r_{i \bmod p}$.
    
    Since $\gcd(k, p)$ divides $p$, this means $\gcd(k, p)$ is a period of $r$. Also, since $\pi[n - 1] > n - p$, we have $n - \pi[n - 1] = k < p$, so $\gcd(k, p)$ is a period of $r$ smaller than $p$. So the string $s$ has a compressed representation of length $\gcd(k, p) < p$, which contradicts the minimality of $p$.
    
    In summary, there is no compressed representation shorter than $k$, so the answer is $k$.

[^1]: This part of the proof seems to be wrong in both the Russian and the English versions. The proof of this part in this article was added by the author.

### Building an automaton from the prefix function

Let us return to the new string made by joining two strings with a separator. For strings $s$ and $t$, we compute the prefix function of $s + \# + t$. Clearly, since $\#$ is a separator, the prefix function value never exceeds $|s|$. So we only need to store the string $s + \#$ and its prefix function values, and then we can compute the prefix function values of all later characters on the fly:

$$
\underbrace{s_0 ~ s_1 ~ \dots ~ s_{n-1} ~ \#}_{\text{need to store}} ~ \underbrace{t_0 ~ t_1 ~ \dots ~ t_{m-1}}_{\text{do not need to store}}
$$

In fact, in this situation, knowing the next character $c$ of $t$ and the prefix function value at the previous position is enough to compute the prefix function value at the next position. We do not need any other characters of $t$ or their prefix function values.

In other words, we can build an **automaton** (a finite state machine): its state is the current prefix function value, and the transition from one state to another is determined by the next character.

So even without the string $t$, we can use the algorithm to build a transition table $( \text { old } \pi , c ) \rightarrow \text { new } _ { - } \pi$:

???+ note "Implementation"
    ```cpp
    void compute_automaton(string s, vector<vector<int>>& aut) {
      s += '#';
      int n = s.size();
      vector<int> pi = prefix_function(s);
      aut.assign(n, vector<int>(26));
      for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++) {
          int j = i;
          while (j > 0 && 'a' + c != s[j]) j = pi[j - 1];
          if ('a' + c == s[j]) j++;
          aut[i][c] = j;
        }
      }
    }
    ```

However, in this form, for the lowercase alphabet the time complexity of the algorithm is $O(|\Sigma|n^2)$. Note that we can use dynamic programming to reuse the parts of the table already computed. Whenever we go from the value $j$ to $\pi[j - 1]$, we are really saying that the transition $(j, c)$ leads to the same state as the transition $(\pi[j - 1], c)$, and we have already computed that answer exactly.

???+ note "Implementation"
    ```cpp
    void compute_automaton(string s, vector<vector<int>>& aut) {
      s += '#';
      int n = s.size();
      vector<int> pi = prefix_function(s);
      aut.assign(n, vector<int>(26));
      for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++) {
          if (i > 0 && 'a' + c != s[i])
            aut[i][c] = aut[pi[i - 1]][c];
          else
            aut[i][c] = i + ('a' + c == s[i]);
        }
      }
    }
    ```

In the end we can build this automaton in $O(|\Sigma|n)$ time.

When is this automaton useful? First, recall that most of the time we use the prefix function of the string $s + \# + t$ for one purpose: finding all occurrences of the string $s$ in the string $t$.

So the most direct benefit of this automaton is **speeding up the computation of the prefix function of $s + \# + t$**.

By building the automaton of $s + \#$, we no longer need to store the string $s$ or its prefix function values. All transitions have already been computed in the table.

But there is also a second, less obvious application. When the string $t$ is **a huge string built by some rules**, we can use this automaton to speed up the computation. Gray strings, or strings formed by recursively combining a few short input strings, are examples of this.

For completeness, let us solve the following problem: given a number $k \le 10^5$ and a string $s$ of length $\le 10^5$, count the occurrences of $s$ in the $k$-th Gray string. Recall that Gray strings are defined as follows:

$$
\begin{aligned}
g_1 &= \mathtt{a}\\
g_2 &= \mathtt{aba}\\
g_3 &= \mathtt{abacaba}\\
g_4 &= \mathtt{abacabadabacaba}
\end{aligned}
$$

Because of their astronomical length, here even building the string $t$ is impossible: the $k$-th Gray string has $2^k - 1$ characters. However, knowing only the first few prefix function values, we can still efficiently compute the prefix function value at the end of this string.

Besides the automaton, we also need to compute the values $G[i][j]$, the state of the automaton after processing $g_i$ starting from state $j$, and $K[i][j]$, the number of occurrences of $s$ in $g_i$ when processing $g_i$ starting from state $j$. In fact, $K[i][j]$ is the number of times the prefix function takes the value $|s|$ during the processing. The answer to the problem is clearly $K[k][0]$.

How do we compute these values? First, by definition, the initial conditions are $G[0][j] = j$ and $K[0][j] = 0$. All later values can be computed from earlier values using the automaton. To compute the values for some $i$, recall that the string $g_i$ is the concatenation of $g_{i - 1}$, the $i$-th character of the alphabet, and $g_{i - 1}$. So the automaton goes through the following states:

$$
\begin{gathered}
\text{mid} = \text{aut}[G[i - 1][j]][i] \\
G[i][j] = G[i - 1][\text{mid}]
\end{gathered}
$$

The values $K[i][j]$ can also be computed easily.

$$
K[i][j] = K[i - 1][j] + [\text{mid} == |s|] + K[i - 1][\text{mid}]
$$

Here $[\cdot]$ is $1$ when the expression inside is true and $0$ otherwise. With this, we can solve the Gray string problem, as well as a large class of similar problems. For example, the same method solves the following problem: given a string $s$ and some patterns $t_i$, where each pattern is given as follows: it consists of ordinary characters, and earlier strings may be inserted recursively in the form $t_{k}^{\text{cnt}}$, meaning that at this position we must insert the string $t_k$ $\text{cnt}$ times. Here is an example of such patterns:

$$
\begin{aligned}
t_1 &= \mathtt{abdeca} \\
t_2 &= \mathtt{abc} + t_1^{30} + \mathtt{abd} \\
t_3 &= t_2^{50} + t_1^{100} \\
t_4 &= t_2^{10} + t_3^{100}
\end{aligned}
$$

Recursive substitution makes the string lengths explode; they can even reach the order of $100^{100}$. And we must find the number of occurrences of the string $s$ in each of these strings.

This problem can also be solved by building the prefix function automaton. As before, we use previously computed results to compute the transitions for each pattern and count the answer accordingly.

## Exercises

-   [UVa 455 "Periodic Strings"](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=396)
-   [UVa 11022 "String Factoring"](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1963)
-   [UVa 11452 "Dancing the Cheeky-Cheeky"](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2447)
-   [UVa 12604 - Caesar Cipher](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4282)
-   [UVa 12467 - Secret Word](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3911)
-   [UVa 11019 - Matrix Matcher](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1960)
-   [SPOJ - Pattern Find](http://www.spoj.com/problems/NAJPF/)
-   [Codeforces - Anthem of Berland](http://codeforces.com/contest/808/problem/G)
-   [Codeforces - MUH and Cube Walls](http://codeforces.com/problemset/problem/471/D)

## References and notes

**This page is mainly translated from the article [Префикс-функция. Алгоритм Кнута-Морриса-Пратта](http://e-maxx.ru/algo/prefix_function) and its English translation [Prefix function. Knuth–Morris–Pratt algorithm](https://cp-algorithms.com/string/prefix-function.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**

[^ref1]: [Jin Ce - Selected Topics in String Algorithms](https://github.com/hzwer/shareOI/blob/master/%E5%AD%97%E7%AC%A6%E4%B8%B2/%E5%AD%97%E7%AC%A6%E4%B8%B2%E7%AE%97%E6%B3%95%E9%80%89%E8%AE%B2_%E9%87%91%E7%AD%96.pdf)

[^kmp]: Knuth, Donald E., James H. Morris, Jr, and Vaughan R. Pratt. "Fast pattern matching in strings." SIAM journal on computing 6.2 (1977): 323-350.[doi: 10.1137/0206024](https://epubs.siam.org/doi/abs/10.1137/0206024)
