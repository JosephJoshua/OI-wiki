## Tandem repetitions

### Definition

Let $s$ be a string of length $n$.

A string written twice in a row is called a **tandem repetition**. Below, to be precise, we call the string being repeated the base string. In other words, a tandem repetition corresponds to a pair of indices $(i, j)$ such that $s[i \dots j]$ is the concatenation of two identical strings.

Your goal is to find all tandem repetitions in the given string $s$. Or, to solve a simpler problem: find any tandem repetition, or the longest one, in the string $s$.

The algorithm below was proposed by Michael Main and Richard J. Lorentz in 1982.

???+ note "Conventions"
    All string indices below start from $0$.
    
    Below, $\overline{s}$ denotes the reverse of $s$. For example, $\overline{\tt abc} = \tt cba$.

### Explanation

Consider the string $\tt acababaee$. It contains three tandem repetitions:

-   $s[2 \dots 5] = \tt abab$
-   $s[3 \dots 6] = \tt baba$
-   $s[7 \dots 8] = \tt ee$

Here is another example. The string $\tt abaaba$ has only two tandem repetitions:

-   $s[0 \dots 5] = \tt abaaba$
-   $s[2 \dots 3] = \tt aa$

### The number of tandem repetitions

A string of length $n$ can have as many as $O(n^2)$ tandem repetitions. An obvious example is a string of $n$ identical letters: in that case every substring of even length is a tandem repetition. In general, a periodic string with a small period has many tandem repetitions.

But this does not stop us from computing the number of tandem repetitions in $O(n \log n)$ time, because the algorithm represents tandem repetitions in a compressed form that lets us group many of them into one.

Here are some interesting facts about the number of tandem repetitions:

-   If the base string of a tandem repetition is not itself a tandem repetition, we call it a **primitive repetition**. It can be proved that there are at most $O(n \log n)$ primitive repetitions.
-   Suppose we compress tandem repetitions into Crochemore triples $(i, p, r)$, where $i$ is the starting position of the tandem repetition, $p$ is the length of one of its periods (note: not the length of the base string!), and $r$ is the number of times this period repeats. Then all tandem repetitions of a string can be described by $O(n \log n)$ Crochemore triples.
-   Fibonacci strings are defined as follows:

$$
\begin{align} t_0 &= a, \\ t_1 &= b, \\ t_i &= t_{i-1} + t_{i-2}, \end{align}
$$

Fibonacci strings are highly periodic. For the Fibonacci string $t_i$ of length $f_i$, even with Crochemore triple compression there are $O(f_i \log f_i)$ triples. The number of its primitive repetitions is also $O(f_i \log f_i)$.

## The Main–Lorentz algorithm

### Explanation

The core idea of the Main–Lorentz algorithm is **divide and conquer**.

The algorithm splits the string into a left half and a right half. It first counts the tandem repetitions lying entirely in the left half (or the right half), and then counts those that start in the left half and end in the right half. (Below we call these **crossing repetitions**.)

Counting crossing repetitions is the key part of the Main–Lorentz algorithm, and we discuss it in detail below.

### How it works

#### Finding crossing repetitions

Let the left half of the string be $u$ and the right half be $v$. Then $s = u + v$, and the lengths of $u, v$ are each about half the length of $s$.

For any tandem repetition, consider its middle character. Here we call the first character of the right half of a tandem repetition its middle character; in other words, if $s[i...j]$ is a tandem repetition, its middle character is $s[(i + j + 1)/2]$. If the middle character of a tandem repetition is in $u$, the tandem repetition is called **left**; otherwise it is called **right**.

Next we discuss how to find all left tandem repetitions.

Let the length of a left tandem repetition be $2l$. Consider the first character of the tandem repetition that falls into $v$ (that is, $s[|u|]$). This character must equal some character $u[\textit{cntr}]$ in $u$.

We fix $\textit{cntr}$ and find all tandem repetitions that match. For example, for the string $\tt c \; \underset{\textit{cntr}}{a} \; c \; | \; a \; d \; a$ (the $\tt |$ separates the two halves), fixing $cntr = 1$, we find that the tandem repetition $\tt caca$ matches.

Clearly, once we fix $\textit{cntr}$, we also fix the value of $l$. Once we know how to find all such tandem repetitions, we can enumerate $\textit{cntr}$ from $0$ to $|u| - 1$ and find all matching tandem repetitions.

#### Criterion for left tandem repetitions

Even with $\textit{cntr}$ fixed, there may still be several matching tandem repetitions. How do we find all of them?

Let us look at another example. For the tandem repetition $\overbrace{\tt a}^{l_1} \overbrace{\underset{\textit{cntr}}{\tt b} \tt c}^{l_2} \overbrace{\tt a}^{l_1}  \; | \; \overbrace{\tt b \; \tt c}^{l_2}$ in the string $\tt abcabcac$, let $l_1$ be the length of the substring from the first character of the tandem repetition to $s[\textit{cntr} - 1]$, and let $l_2$ be the length of the substring from $s[\textit{cntr}]$ to the last character of the left copy of the base string.

We can now give a **necessary and sufficient condition** for a substring of length $2l = 2(l_1 + l_2) = 2(|u| - \textit{cntr})$ to be a tandem repetition:

Let $k_1$ be the largest integer such that $u[\textit{cntr} - k_1 \dots \textit{cntr} - 1] = u[|u| - k_1 \dots |u| - 1]$, and let $k_2$ be the largest integer such that $u[\textit{cntr} \dots \textit{cntr} + k_2 - 1] = v[0 \dots k_2 - 1]$. Then for every pair $(l_1, l_2)$ with $l_1 \leq k_1$ and $l_2 \leq k_2$, there is exactly one corresponding tandem repetition.

To sum up:

-   Fix a $\textit{cntr}$.
-   Then all tandem repetitions we are looking for have length $2l = 2(|u| - \textit{cntr})$. There may still be several matching tandem repetitions, depending on the values of $l_1$ and $l_2$.
-   Compute $k_1$ and $k_2$ as described above.
-   Then all matching tandem repetitions satisfy:

$$
\begin{align} l_1 + l_2 &= l = |u| - \textit{cntr} \\ l_1 &\le k_1, \\ l_2 &\le k_2. \\ \end{align}
$$

Now we only need to compute $k_1$ and $k_2$ quickly. With the [Z-function](./z-func.md), we can compute each of them in $O(1)$:

-   To compute $k_1$: compute the Z-function of $\overline{u}$.
-   To compute $k_2$: compute the Z-function of $v + \# + u$, where $\#$ is a character that appears in neither $u$ nor $v$.

#### Right tandem repetitions

Right tandem repetitions are found almost the same way as left ones. Consider the first character of the tandem repetition that falls into $u$ (that is, $s[|u| - 1]$). It must equal some character in $v$; let the position of that character in $v$ be $\textit{cntr}$.

Let $k_1$ be the largest integer such that $v[\textit{cntr} - k_1 + 1 \dots \textit{cntr}] = u[|u| - k_1 \dots |u| - 1]$, and $k_2$ the largest integer such that $v[\textit{cntr} + 1 \dots \textit{cntr} + k_2] = v[0 \dots k_2 - 1]$. Then we can get $k_1$ and $k_2$ by computing the Z-functions of $\overline{u} + \# + \overline{v}$ and $v$ respectively.

Enumerate $\textit{cntr}$ and find the right tandem repetitions in the same way.

### Implementation

The Main–Lorentz algorithm reports all tandem repetitions as quadruples $(\textit{cntr}, l, k_1, k_2)$. If you only need the number of tandem repetitions, or only the longest one, these quadruples give enough information. By the [master theorem](../basic/complexity.md#master-theorem), the time complexity of the Main–Lorentz algorithm is $O(n \log n)$.

Note that if you want to use these quadruples to get the start and end positions of all tandem repetitions, the worst-case time complexity becomes $O(n^2)$. The program below does exactly this, storing the start and end positions of all tandem repetitions in `repetitions`.

```cpp
vector<int> z_function(string const& s) {
  int n = s.size();
  vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; i++) {
    if (i <= r) z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }
  return z;
}

int get_z(vector<int> const& z, int i) {
  if (0 <= i && i < (int)z.size())
    return z[i];
  else
    return 0;
}

vector<pair<int, int>> repetitions;

void convert_to_repetitions(int shift, bool left, int cntr, int l, int k1,
                            int k2) {
  for (int l1 = max(1, l - k2); l1 <= min(l, k1); l1++) {
    if (left && l1 == l) break;
    int l2 = l - l1;
    int pos = shift + (left ? cntr - l1 : cntr - l - l1 + 1);
    repetitions.emplace_back(pos, pos + 2 * l - 1);
  }
}

void find_repetitions(string s, int shift = 0) {
  int n = s.size();
  if (n == 1) return;

  int nu = n / 2;
  int nv = n - nu;
  string u = s.substr(0, nu);
  string v = s.substr(nu);
  string ru(u.rbegin(), u.rend());
  string rv(v.rbegin(), v.rend());

  find_repetitions(u, shift);
  find_repetitions(v, shift + nu);

  vector<int> z1 = z_function(ru);
  vector<int> z2 = z_function(v + '#' + u);
  vector<int> z3 = z_function(ru + '#' + rv);
  vector<int> z4 = z_function(v);

  for (int cntr = 0; cntr < n; cntr++) {
    int l, k1, k2;
    if (cntr < nu) {
      l = nu - cntr;
      k1 = get_z(z1, nu - cntr);
      k2 = get_z(z2, nv + 1 + cntr);
    } else {
      l = cntr - nu + 1;
      k1 = get_z(z3, nu + 1 + nv - 1 - (cntr - nu));
      k2 = get_z(z4, (cntr - nu) + 1);
    }
    if (k1 + k2 >= l) convert_to_repetitions(shift, cntr < nu, cntr, l, k1, k2);
  }
}
```

**This page is mainly translated from the article [Поиск всех тандемных повторов в строке. Алгоритм Мейна-Лоренца](http://e-maxx.ru/algo/string_tandems) and its English translation [Finding repetitions](https://cp-algorithms.com/string/main_lorentz.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**
