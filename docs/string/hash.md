## Definition

We define a function $f$ that maps strings to integers. This $f$ is called a hash function.

We want this function $f$ to make it easy to check whether two strings are equal.

## The idea of hashing

The core idea of hashing is to map the input into a small range of values that are easy to compare.

??? warning "Warning"
    What "a small range of values" means depends on the situation.
    
    In a [hash table](../ds/hash.md), the range must be small enough that linear space and time in its size are acceptable.
    
    In string hashing, the range must be small enough that values can be compared quickly ($10^9$ and $10^{18}$ can both be compared quickly).
    
    At the same time, to keep the collision rate low, the range cannot be too small either.

## Properties

The two most important properties of a hash function can be summed up as follows:

1.  If the hash values are different, the two strings are definitely different;

2.  If the hash values are the same, the two strings are not necessarily the same (but they very likely are, and of course we hope they always are).

    When two different strings have the same hash value, we call it a hash collision.

## Explanation

What do we need to care about?

The time complexity and the accuracy of the hash.

We usually use polynomial hashing. For a string $s$ of length $l$, we can define the polynomial hash function as $f(s) = \sum_{i=1}^{l} s[i] \times b^{l-i} \pmod M$. For example, the hash value of the string $xyz$ is $xb^2+yb+z$.

Note that many people use a different definition of the hash function instead: $f(s) = \sum_{i=1}^{l} s[i] \times b^{i-1} \pmod M$. With this definition, the hash value of the same string $xyz$ becomes $x+yb+zb^2$.

Clearly, both definitions work. But they use different formulas for computing the hash of a substring, which we will discuss later. So be very careful **not to mix up these two kinds of hashing**.

The first definition is simpler to compute, more widely used, and can be understood as a number written in base $b$. So everything below uses the hash function defined by $f(s) = \sum_{i=1}^{l} s[i] \times b^{l-i} \pmod M$.

Also, sometimes for convenience and to get a larger modulus, in C++ we store the hash value in an `unsigned long long`. Because of how C++ works, this is the same as choosing the modulus $M$ to be $2^{64}$, which is also a good choice.

Accuracy is discussed below.

## Error rate of hashing

### Hash collisions

A hash collision is when two different strings map to the same hash value.

Let $d$ be the size of the hash value space (the number of all possible values), and let $n$ be the number of computations (the number of strings to hash).

Then the probability of a hash collision is:

$$
p(n,d) = 1 - \frac{d!}{d^n\left(d-n\right)!} \approx 1 - \exp(-\frac{n(n-1)}{2d} )
$$

??? note "Proof"
    When every hash value is equally likely, the probability of no collision is:
    
    $$
    \overline{p}(n,d) = 1 \cdot \left (1 - \frac{1}{d} \right) \cdot \left ( 1- \frac{2}{d}\right) \cdots \left ( 1- \frac{n-1}{d}\right)
    $$
    
    Simplifying gives:
    
    $$
    \begin{aligned}
    \overline{p}(n,d) 
    & = \frac{d}{d}\cdot \frac{d-1}{d}\cdot \frac{d-2}{d} \cdots \frac{d-n+1}{d}\\
    & = \frac{d\cdot (d-1)\cdot (d-2)\cdots(d-n+1)}{d^n}\\
    & = \frac{d!}{d^n\left(d-n\right)!}
    \end{aligned}
    $$
    
    So the probability of a hash collision is:
    
    $$
    p(n,d) = 1 - \frac{d!}{d^n\left(d-n\right)!}
    $$
    
    This formula is still too complicated, so we simplify it further.
    
    By Taylor's formula:
    
    $$
    \exp(x) = \sum_{k=0}^{\infty}\frac{x^k}{k!}=1+x+\frac{x^2}{2}+\frac{x^3}{6}+\frac{x^4}{24}+\cdots
    $$
    
    When $x$ is very small, $\exp(x)$ is close to $1+x$.
    
    Substitute this into the original formula for no collision:
    
    $$
    \overline{p}(n,d) \approx 1 \cdot \exp(-\frac{1}{d}) \cdot \exp(-\frac{2}{d}) \cdots \exp(-\frac{n-1}{d})
    $$
    
    Simplify:
    
    $$
    \begin{aligned}
    \overline{p}(n,d) & \approx \exp(-\frac{1}{d} - \frac{2}{d} - \cdots -\frac{n-1}{d})\\
    &=\exp(-\frac{n(n-1)}{2d} )
    \end{aligned}
    $$
    
    So the probability of a hash collision is:
    
    $$
    p(n,d) \approx 1 - \exp(-\frac{n(n-1)}{2d})
    $$

### Breaking a hash with a large modulus

Look at this formula:

$$
p(n,d) \approx 1 - \exp(-\frac{n(n-1)}{2d} )
$$

To break the hash, we need these conditions:

1.  $d$ must be larger than the modulus.
2.  $1-p(d,n)$ must be as small as possible.

For example:

If the alphabet is **uppercase and lowercase letters plus digits**, and the modulus is $10^9+7$:

$\log_{62}10^9+7\approx 6$

$p(10^6,62^{6}) \approx 0.9$

So in this setting, if we randomly generate $10^6$ strings of length $6$, the probability that two of them have the same hash value is as high as $90\%$.

### Breaking a natural-overflow hash

This kind of hash has too large a modulus to be broken with the method above, so we need another method.

First, this hash has the form $f(s) = \sum_{i=1}^{l} s[i] \times b^{l-i}$. We split into cases by $b$.

#### b is even

Here $f(s) = s_1\cdot b^l + s_2\cdot b^{l-1} + \cdots + s_l\cdot b \pmod M$, where $M$ is $2^{64}$.

It is easy to see that if $l \ge 64$, then $s_i\cdot b^l \equiv 0 \pmod M$.

So we only need to construct strings like:

`aaa...a`

`baa...a`

with length greater than $64$, and they will collide.

#### b is odd

Define $!s_i$ as $s_i$ with every character flipped.

For example:

$s_i = abaab$

$!s_i = babba$

That is, change `a` into `b` and `b` into `a`.

Next, define $hash_i$ as the hash value of $s_i$, and $!hash_i$ as the hash value of $!s_i$.

Repeatedly construct $s_i = s_{i-1} + !s_{i-1}$.

$s_{12}$ and $!s_{12}$ are the two strings we want.

??? note "Derivation"
    First, we have:
    
    $$
    \begin{aligned}
    hash_i = hash_{i-1}\cdot base^{2^{i-2}} + !hash_{i-1}\\
    !hash_{i} = !hash_{i-1}\cdot base^{2^{i-2}}+hash_{i-1}
    \end{aligned}
    $$
    
    Try subtracting them:
    
    $$
    \begin{aligned}
    &hash_i - !hash_i\\
    =\ &hash_{i-1}\cdot base^{2^{i-2}} + !hash_{i-1}-(!hash_{i-1}\cdot base^{2^{i-2}}+hash_{i-1})\\
    =\ &(hash_{i-1}-!hash_{i-1})\cdot (base^{2^{i-2}}-1)
    \end{aligned}
    $$
    
    A power of $2$ shows up, but the expression is too complicated, so we substitute:
    
    Let:
    
    $$
    \begin{aligned}
    f_i = hash_i - !hash_i\\
    g_i = base^{2^{i-2}}-1
    \end{aligned}
    $$
    
    From the expression above:
    
    $$
    \begin{aligned}
    f_i &= f_{i-1} \cdot g_i\\
        &=f_1 \cdot g_1 \cdot g_2 \cdots g_{i-1}\\
    \end{aligned}
    $$
    
    Since $base^{2^{i-2}}$ is always odd, $g_i$ is always even.
    
    So:
    
    $$
    2^{i-1} | f_i
    $$
    
    But this needs too large an $i$: we would need $i-1\ge 64$ to break the hash. Let us simplify further:
    
    $$
    g_i = base^{2^{i-2}}-1 = (base^{2^{i-3}}-1)\cdot(base^{2^{i-3}}+1)\\
    $$
    
    That is, $g_i$ has the form $g_{i-1} \cdot c\ (c \equiv 0 \pmod 2)$.
    
    So $2 | s_1$, $4 | s_2$, and so on, that is,
    
    $$
    \begin{aligned}
    & 2^i &| g_i\\
    &2^1\cdot2^2\cdot2^3\cdots2^{i-1} &| f_i\\
    &2^{i(i-1)/2} &| f_i
    \end{aligned}
    $$
    
    So with $i=12$ we get $2^{64} | hash_i - !hash_i$, as required.

### Example problems

???+ note "[Example problem: BZOJ 3097 Hash Killer I](https://hydro.ac/p/bzoj-P3097)"
    Given a hash implemented with **natural overflow**, construct a string that breaks it.

???+ note "[Example problem: BZOJ 3097 Hash Killer II](https://hydro.ac/p/bzoj-P3098)"
    Given a hash implemented with a **large modulus**, construct a string that breaks it.

???+ note "[Example problem: Luogu U461211 String Hash (Strengthened Data)](https://www.luogu.com.cn/problem/U461211)"
    Given $n$ strings, find how many distinct strings there are.

## Improving hashing

### Multi-value hashing

After all these ways of breaking hashes, of course there are ways to defend against them.

Multi-value hashing uses several hash functions, each with a different modulus. This solves the problem of hash collisions.

When comparing, if any one of the hash values differs, we consider the two strings different. If all hash values are equal, we consider the two strings equal.

In general, double hashing is enough.

### Many queries for substring hashes

Computing the hash of a string once takes $O(n)$, where $n$ is its length. That is no better than brute-force matching. If we need to query the hash of substrings of a string many times, recomputing it each time is very slow.

The usual approach is to first precompute the hash of every prefix of the whole string. Treat each hash as a base-$b$ number taken modulo $M$. Then the hash of any substring can be computed quickly:

Let $f_i(s)$ denote $f(s[1..i])$, the hash of the prefix of length $i$. By definition, $f_i(s)=s[1]\cdot b^{i-1}+s[2]\cdot b^{i-2}+\dots+s[i-1]\cdot b+s[i]$

Now we want to compute $f(s[l..r])$ quickly, in a way similar to prefix sums. By definition, the hash of $s[l..r]$ is $f(s[l..r])=s[l]\cdot b^{r-l}+s[l+1]\cdot b^{r-l-1}+\dots+s[r-1]\cdot b+s[r]$

Comparing the two formulas, we find that $f(s[l..r])=f_r(s)-f_{l-1}(s) \times b^{r-l+1}$ holds (you can check it by plugging in values by hand). So this formula gives the hash of a substring quickly. The powers $b^{r-l+1}$ can be precomputed in $O(n)$, so each query is answered in $O(1)$ (or you can use fast exponentiation to answer each query in $O(\log n)$).

## Implementation

### Hash with a modulus:

Note: this is slow and not recommended in practice.

=== "C++"
    ```cpp
    using std::string;
    
    constexpr int M = 1e9 + 7;
    constexpr int B = 233;
    
    using ll = long long;
    
    int get_hash(const string& s) {
      int res = 0;
      for (int i = 0; i < s.size(); ++i) {
        res = ((ll)res * B + s[i]) % M;
      }
      return res;
    }
    
    bool cmp(const string& s, const string& t) {
      return get_hash(s) == get_hash(t);
    }
    ```

=== "Python"
    ```python
    M = int(1e9 + 7)
    B = 233
    
    
    def get_hash(s):
        res = 0
        for char in s:
            res = (res * B + ord(char)) % M
        return res
    
    
    def cmp(s, t):
        return get_hash(s) == get_hash(t)
    ```

### Double hashing:

=== "C++"
    ```cpp
    using ull = unsigned long long;
    ull base = 131;
    ull mod1 = 212370440130137957, mod2 = 1e9 + 7;
    
    ull get_hash1(std::string s) {
      int len = s.size();
      ull ans = 0;
      for (int i = 0; i < len; i++) ans = (ans * base + (ull)s[i]) % mod1;
      return ans;
    }
    
    ull get_hash2(std::string s) {
      int len = s.size();
      ull ans = 0;
      for (int i = 0; i < len; i++) ans = (ans * base + (ull)s[i]) % mod2;
      return ans;
    }
    
    bool cmp(const std::string s, const std::string t) {
      bool f1 = get_hash1(s) != get_hash1(t);
      bool f2 = get_hash2(s) != get_hash2(t);
      return f1 || f2;
    }
    ```

=== "Python"
    ```python
    def get_hash1(s: str) -> int:
        base = 131
        mod1 = 212370440130137957
        ans = 0
        for char in s:
            ans = (ans * base + ord(char)) % mod1
        return ans
    
    
    def get_hash2(s: str) -> int:
        base = 131
        mod2 = 1000000007
        ans = 0
        for char in s:
            ans = (ans * base + ord(char)) % mod2
        return ans
    
    
    def cmp(s: str, t: str) -> bool:
        f1 = get_hash1(s) != get_hash1(t)
        f2 = get_hash2(s) != get_hash2(t)
        return f1 or f2
    ```

## Applications of hashing

### String matching

Compute the hash of the pattern. Then compute the hash of every substring of the text whose length equals the pattern's length, and compare each one with the pattern's hash.

### String matching with up to $k$ mismatches

Problem: given a source string $s$ of length $n$ and a pattern $p$ of length $m$, find how many substrings of the source string match the pattern. $s'$ matches $s$ if and only if $s'$ and $s$ have the same length and differ in at most $k$ positions. Here $1\leq n,m\leq 10^6$ and $0\leq k\leq 5$.

This problem cannot be solved with KMP, but it can be solved with hashing + binary search.

Enumerate every substring that could match. Say the current substring is $s'$. With hashing + binary search, we can quickly find the first position where $s'$ and $p$ differ. Then remove the parts of $s'$ and $p$ up to and including this mismatch position, and keep looking for the next mismatch. This happens at most $k$ times.

The total time complexity is $O(m+kn\log_2m)$.

### Longest palindromic substring

Binary search on the answer. To check whether a length works, enumerate the center of the palindrome (the axis of symmetry) and use hashing to check whether the two sides are equal. You need to precompute the hashes of both the string and its reverse. The time complexity is $O(n\log n)$.

This problem can be solved in $O(n)$ time with [Manacher's algorithm](./manacher.md).

Hashing can also solve it in $O(n)$. Let $R_i$ be the length of the longest palindrome ending at $i$; then the answer is $\max_{i=1}^nR_i$. Since $R_i\leq R_{i-1}+2$, we just start from $R_{i-1}+2$ and decrease by brute force until we find the first palindrome. Let $z$ be the current candidate for $R_i$, initially $0$. Each time $i$ increases, $z$ increases by $2$, and each step of the brute-force loop decreases it by $1$. So the brute-force loop runs at most $2n$ times, and the total time complexity is $O(n)$.

### Longest common substring

Problem: given $m$ non-empty strings with total length at most $n$, find the longest common substring of all of them. If there are several, output any one. Here $1\leq m, n\leq 10^6$.

Clearly, if a common substring of length $k$ exists, then a common substring of length $k-1$ also exists. So we can binary search on the length of the longest common substring. Say the current length is $k$. The logic of `check(k)` is: hash every substring of length $k$ of each string, store the hashes in $n$ hash tables, and then take their intersection.

The time complexity is $O(m+n\log n)$.

### Counting distinct substrings of a string

Problem: given a string of length $n$ made only of lowercase English letters, find the number of distinct substrings in it.

To solve this, we go through all substrings of every length $l=1,\cdots ,n$. For each length $l$, we multiply the hash of each substring by a power of $b$ so that they all share the same power, and store them in an array. The number of distinct elements in the array is the number of distinct substrings of length $l$, and we add this number to the final answer.

For convenience, we use $h [i]$ for the hash of the prefix, and define $h[0]=0$.

??? note "Reference code"
    ```cpp
    int count_unique_substrings(string const& s) {
      int n = s.size();
    
      constexpr static int b = 31;
      constexpr static int m = 1e9 + 9;
      vector<long long> b_pow(n);
      b_pow[0] = 1;
      for (int i = 1; i < n; i++) b_pow[i] = (b_pow[i - 1] * b) % m;
    
      vector<long long> h(n + 1, 0);
      for (int i = 0; i < n; i++)
        h[i + 1] = (h[i] + (s[i] - 'a' + 1) * b_pow[i]) % m;
    
      int cnt = 0;
      for (int l = 1; l <= n; l++) {
        set<long long> hs;
        for (int i = 0; i <= n - l; i++) {
          long long cur_h = (h[i + l] + m - h[i]) % m;
          cur_h = (cur_h * b_pow[n - i - 1]) % m;
          hs.insert(cur_h);
        }
        cnt += hs.size();
      }
      return cnt;
    }
    ```

### Example problems

???+ note "[CF1200E Compress Words](http://codeforces.com/contest/1200/problem/E)"
    You are given several strings. The answer string starts empty. In step $i$, append the $i$-th string to the end of the answer string, but remove as much overlap as possible (that is, remove the longest string that is both a suffix of the current answer string and a prefix of the $i$-th string). Find the final string.
    
    There are at most $10^5$ strings, with total length at most $10^6$.
    
    ??? note "Solution"
        Each step, we need the longest string that is both a suffix of the current answer string and a prefix of the $i$-th string. Enumerate its length and compare with hashing.
        
        Of course, this problem can also be solved with the [KMP algorithm](./kmp.md).
    
    ??? note "Reference code"
        ```cpp
        --8<-- "docs/string/code/hash/hash_1.cpp"
        ```

**Parts of this page are translated from the article [строковый хеш](https://github.com/e-maxx-eng/e-maxx-eng/blob/61aff51f658644424c5e1b717f14fb7bf054ae80/src/string/string-hashing.md) and its English translation [String Hashing](https://cp-algorithms.com/string/string-hashing.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**
