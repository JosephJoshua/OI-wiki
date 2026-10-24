## Conventions

For definitions related to strings, see [String basics](./basic.md).

String indices start from $1$.

The length of the string $s$ is $n$.

"Suffix $i$" means the suffix that starts at the $i$-th character. We store it as $i$, which stands for the suffix $s[i\dots n]$ of the string $s$.

## What is a suffix array?

A suffix array mainly involves two arrays: $sa$ and $rk$.

Here, $sa[i]$ is the index of the $i$-th smallest suffix after all suffixes are sorted. This is what we call the suffix array; below we also call it the index array $sa$.

$rk[i]$ is the rank of suffix $i$. It is an important helper array; below we also call it the rank array $rk$.

The two arrays satisfy: $sa[rk[i]]=rk[sa[i]]=i$.

### Explanation

An example of a suffix array:

[![](./images/sa1.png)][2]

## How do we compute a suffix array?

### O(n^2logn) approach

You can probably come up with this approach yourself: put all the suffixes into an array and `sort` it. Sorting does $O(n\log n)$ string comparisons, and each string comparison takes $O(n)$ character comparisons, so this sort runs in $O(n^2\log n)$ time.

### O(nlog^2n) approach

This approach uses the idea of doubling (binary lifting).

First, sort all substrings of $s$ of length $1$, that is, the individual characters. This gives the index array $sa_1$ and the rank array $rk_1$.

The doubling process:

1.  Use the ranks of two substrings of length $1$, namely $rk_1[i]$ and $rk_1[i+1]$, as the first and second sort keys. Then we can sort every substring of $s$ of length $2$: $\{s[i\dots \min(i+1, n)]\ |\ i \in [1,\ n]\}$, and get $sa_2$ and $rk_2$;

2.  Next, use the ranks of two substrings of length $2$, namely $rk_2[i]$ and $rk_2[i+2]$, as the first and second sort keys. Then we can sort every substring of $s$ of length $4$: $\{s[i\dots \min(i+3, n)]\ |\ i \in [1,\ n]\}$, and get $sa_4$ and $rk_4$;

3.  Keep doubling in this way: use the ranks of substrings of length $w/2$, namely $rk_{w/2}[i]$ and $rk_{w/2}[i+w/2]$, as the first and second sort keys. Then we can sort every substring of $s$ of length $w$, $s[i\dots \min(i+w-1,\ n)]$, and get $sa_w$ and $rk_w$. As in alphabetical ordering, when $i+w>n$, $rk_w[i+w]$ is treated as negative infinity;

4.  $rk_w[i]$ is the rank of the substring $s[i\dots i + w - 1]$. So once $w \geqslant n$, the index array $sa_w$ we get is exactly the suffix array we need.

#### Process

Illustration of the doubling sort:

[![](./images/sa2.png)][2]

Clearly there are $O(\log n)$ doubling rounds. In each round, sorting the substrings with `sort` takes $O(n\log n)$, and each substring comparison costs $2$ comparisons;

Besides that, after each round's `sort`, there is an extra $O(n)$ step to update $rk$, but it is negligible compared with $O(n\log n)$;

So the time complexity of this algorithm is $O(n\log^2n)$.

??? note "Implementation"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    
    using namespace std;
    
    constexpr int N = 1000010;
    
    char s[N];
    int n, w, sa[N], rk[N << 1], oldrk[N << 1];
    
    // The arrays are twice as large so that accessing rk[i+w] never goes out of bounds.
    // You could also check the bounds before each access, but doubling the size is simpler.
    
    int main() {
      int i, p;
    
      scanf("%s", s + 1);
      n = strlen(s + 1);
      for (i = 1; i <= n; ++i) sa[i] = i, rk[i] = s[i];
    
      for (w = 1; w < n; w <<= 1) {
        sort(sa + 1, sa + n + 1, [](int x, int y) {
          return rk[x] == rk[y] ? rk[x + w] < rk[y + w] : rk[x] < rk[y];
        });  // a lambda is used here
        memcpy(oldrk, rk, sizeof(rk));
        // computing rk overwrites the old rk, so make a copy first
        // equal substrings must get equal rk, so remove duplicates
        for (p = 0, i = 1; i <= n; ++i) {
          if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
              oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) {
            rk[sa[i]] = p;
          } else {
            rk[sa[i]] = ++p;
          }
        }
      }
    
      for (i = 1; i <= n; ++i) printf("%d ", sa[i]);
    
      return 0;
    }
    ```

### O(nlogn) approach

In the $O(n\log^2n)$ approach above, a single sort takes $O(n\log n)$. If we can sort in $O(n)$, we can compute the suffix array in $O(n\log n)$.

Prerequisites: [counting sort](../basic/counting-sort.md), [radix sort](../basic/radix-sort.md).

When computing the suffix array, the sort keys are ranks, whose values are in a range of size $O(n)$, and the sort uses two keys. So we can use radix sort to bring each sort down to $O(n)$.

??? note "Implementation"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    
    using namespace std;
    
    constexpr int N = 1000010;
    
    char s[N];
    int n, sa[N], rk[N << 1], oldrk[N << 1], id[N], cnt[N];
    
    int main() {
      int i, m, p, w;
    
      scanf("%s", s + 1);
      n = strlen(s + 1);
      m = 127;
      for (i = 1; i <= n; ++i) ++cnt[rk[i] = s[i]];
      for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
      for (i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;
      memcpy(oldrk + 1, rk + 1, n * sizeof(int));
      for (p = 0, i = 1; i <= n; ++i) {
        if (oldrk[sa[i]] == oldrk[sa[i - 1]]) {
          rk[sa[i]] = p;
        } else {
          rk[sa[i]] = ++p;
        }
      }
    
      for (w = 1; w < n; w <<= 1, m = n) {
        // counting sort by the second key: id[i] + w
        memset(cnt, 0, sizeof(cnt));
        memcpy(id + 1, sa + 1,
               n * sizeof(int));  // id keeps a copy of sa; it is essentially oldsa
        for (i = 1; i <= n; ++i) ++cnt[rk[id[i] + w]];
        for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; --i) sa[cnt[rk[id[i] + w]]--] = id[i];
    
        // counting sort by the first key: id[i]
        memset(cnt, 0, sizeof(cnt));
        memcpy(id + 1, sa + 1, n * sizeof(int));
        for (i = 1; i <= n; ++i) ++cnt[rk[id[i]]];
        for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; --i) sa[cnt[rk[id[i]]]--] = id[i];
    
        memcpy(oldrk + 1, rk + 1, n * sizeof(int));
        for (p = 0, i = 1; i <= n; ++i) {
          if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
              oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) {
            rk[sa[i]] = p;
          } else {
            rk[sa[i]] = ++p;
          }
        }
      }
    
      for (i = 1; i <= n; ++i) printf("%d ", sa[i]);
    
      return 0;
    }
    ```

### Some constant-factor optimizations

If you submit the code above to [LOJ #111: Suffix Sorting](https://loj.ac/problem/111):

![](./images/sa3.png)

This is because the code above really does have a large constant factor.

#### The second key does not need a counting sort

Think about what sorting by the second key actually does: it moves the $sa[i]$ that go past the end of the string (that is, $sa[i] + w > n$) to the front of the $sa$ array, and then puts the rest in their original order:

```cpp
int cur = 0;
for (int i = n - w + 1; i <= n; i++) id[++cur] = i;
for (int i = 1; i <= n; i++)
  if (sa[i] > w) id[++cur] = sa[i] - w;
```

#### Shrink the value range of the counting sort

Each time we update $rk$, we compute a value $p$. This $p$ is the value range of $rk$, so just use it as the range.

#### If all ranks are distinct, the suffix array is ready

Look at the new $rk$ array. If its values cover $[1,n]$, then every rank is distinct, and no more sorting is needed.

??? note "Implementation"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    
    using namespace std;
    
    constexpr int N = 1000010;
    
    char s[N];
    int n;
    int m, p, rk[N * 2], oldrk[N], sa[N * 2], id[N], cnt[N];
    
    int main() {
      scanf("%s", s + 1);
      n = strlen(s + 1);
      m = 128;
    
      for (int i = 1; i <= n; i++) cnt[rk[i] = s[i]]++;
      for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
      for (int i = n; i >= 1; i--) sa[cnt[rk[i]]--] = i;
    
      for (int w = 1;; w <<= 1, m = p) {  // m = p is the value-range optimization
        int cur = 0;
        for (int i = n - w + 1; i <= n; i++) id[++cur] = i;
        for (int i = 1; i <= n; i++)
          if (sa[i] > w) id[++cur] = sa[i] - w;
    
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; i++) cnt[rk[i]]++;
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; i--) sa[cnt[rk[id[i]]]--] = id[i];
    
        p = 0;
        memcpy(oldrk, rk, sizeof(oldrk));
        for (int i = 1; i <= n; i++) {
          if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
              oldrk[sa[i] + w] == oldrk[sa[i - 1] + w])
            rk[sa[i]] = p;
          else
            rk[sa[i]] = ++p;
        }
    
        if (p == n) break;  // no more sorting needed once p = n
      }
    
      for (int i = 1; i <= n; i++) printf("%d ", sa[i]);
    
      return 0;
    }
    ```

### O(n) approach

In typical problems, the doubling method with a small constant factor is fast enough. The parts of the solution other than building the suffix array often take $O(n\log n)$ anyway, so the doubling construction will not be the bottleneck.

But for special problems, problems with tight time limits, or if you just want a faster running time, you need to learn how to build a suffix array in $O(n)$.

#### SA-IS

See [Induced sorting and the SA-IS algorithm](https://riteme.site/blog/2016-6-19/sais.html). Its [comments page](https://github.com/riteme/riteme.github.io/issues/28) is also worth reading.

#### DC3

See [\[2009\] Suffix Arrays: A Powerful Tool for Processing Strings, by Luo Suiqian][2].

## Applications of suffix arrays

### Finding the smallest cyclic shift

Duplicate the string $S$ into $SS$, and the problem becomes a suffix sorting problem.

Example problem: [JSOI 2007 — Character Encryption](https://www.luogu.com.cn/problem/P4051).

### Finding a substring in a string

The task is to find a pattern $S$ in a text $T$ online. Online means that we know the text $T$ in advance, but we only learn the pattern $S$ when a query arrives. We can first build the suffix array of $T$, and then search for the substring $S$. If $S$ occurs in $T$, it must be a prefix of some suffixes of $T$. Since all the suffixes are already sorted, we can binary search for $S$ in the $p$ array. Comparing $S$ with the current suffix takes $O(|S|)$ time, so finding the substring takes $O(|S|\log |T|)$ time. Note that if the substring occurs in $T$ multiple times, all its occurrences are adjacent in the $p$ array. So the number of occurrences can be found with another binary search, and listing the positions of all occurrences is also easy.

### Taking characters from both ends to minimize the lexicographic order

Example problem: [USACO 2007 December — Best Cow Line](https://www.luogu.com.cn/problem/P2870).

Problem: you are given a string. Each time, take one character from its front or its back and append it to a new string. Among all strings that can be formed this way, find the lexicographically smallest one.

??? note "Solution"
    The brute-force approach decides, in $O(n)$ worst case each time, whether to take the front or the back (that is, it compares the string you get by taking from the front with the reversed string you get by taking from the back). We only need to speed up this decision.
    
    We need to compare elements of the set made of suffixes of the original string and suffixes of the reversed string. So append the reversed string to the original string, put a character that does not appear anywhere between them (such as `#`; in code you can simply use the null character), and build the suffix array. Then each decision takes $O(1)$.

??? note "Reference code"
    ```cpp
    --8<-- "docs/string/code/sa/sa_1.cpp"
    ```

## The height array

### LCP (longest common prefix)

The LCP of two strings $S$ and $T$ is the largest $x$ ($x\le \min(|S|, |T|)$) such that $S_i=T_i\ (\forall\ 1\le i\le x)$.

Below, $lcp(i,j)$ denotes (the length of) the longest common prefix of suffix $i$ and suffix $j$.

### Definition of the height array

$height[i]=lcp(sa[i],sa[i-1])$, that is, the longest common prefix of the suffix ranked $i$ and the suffix ranked just before it.

$height[1]$ can be treated as $0$.

### A lemma needed to compute the height array in O(n)

$height[rk[i]]\ge height[rk[i-1]]-1$

???+ note "Proof"
    When $height[rk[i-1]]\le1$, the inequality clearly holds (the right side is at most $0$).
    
    When $height[rk[i-1]]>1$:
    
    By the definition of $height$, $lcp(sa[rk[i-1]], sa[rk[i-1]-1]) = height[rk[i-1]] > 1$.
    
    Since suffix $i-1$ and suffix $sa[rk[i-1]-1]$ have a longest common prefix of length $height[rk[i-1]]$,
    
    let us write this longest common prefix as $aA$. (Here $a$ is a single character and $A$ is a non-empty string of length $height[rk[i-1]]-1$.)
    
    Then suffix $i-1$ can be written as $aAD$, and suffix $sa[rk[i-1]-1]$ can be written as $aAB$. ($B < D$; $B$ may be the empty string; $D$ is non-empty.)
    
    Going one step further, suffix $i$ can be written as $AD$, and there exists a suffix (suffix $sa[rk[i-1]-1]+1$) equal to $AB$.
    
    Suffix $sa[rk[i]-1]$ is ranked exactly one place below suffix $sa[rk[i]]$, which is suffix $i$, and $AB < AD$.
    
    So $AB \leqslant$ suffix $sa[rk[i]-1] < AD$. Clearly suffix $i$ and suffix $sa[rk[i]-1]$ share the common prefix $A$.
    
    Therefore $lcp(i,sa[rk[i]-1])$ is at least $height[rk[i-1]]-1$, that is, $height[rk[i]]\ge height[rk[i-1]]-1$.

### Code for computing the height array in O(n)

Using the lemma above, just compute it by brute force:

```cpp
for (i = 1, k = 0; i <= n; ++i) {
  if (rk[i] == 0) continue;
  if (k) --k;
  while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
  height[rk[i]] = k;
}
```

$k$ never exceeds $n$ and is decreased at most $n$ times, so it is increased at most $2n$ times. The total complexity is $O(n)$.

## Applications of the height array

### LCP of two substrings

$lcp(sa[i],sa[j])=\min\{height[i+1..j]\}$

Intuition: as long as $height$ stays above some value, that many leading characters never change. Conversely, since the suffixes are sorted, once they change they cannot change back.

For a rigorous proof, see [\[2004\] Suffix Arrays, by Xu Zhilei][1].

With this theorem, finding the LCP of two substrings becomes an [RMQ problem](../topic/rmq.md).

### Comparing two substrings of a string

Suppose we want to compare $A=S[a..b]$ and $B=S[c..d]$.

If $lcp(a, c)\ge\min(|A|, |B|)$, then $A<B\iff |A|<|B|$.

Otherwise, $A<B\iff rk[a]< rk[c]$.

### Number of distinct substrings

A substring is a prefix of a suffix. So we can go through every suffix, count its prefixes, and subtract the duplicates.

The "total number of prefixes" is just the number of substrings, $n(n+1)/2$.

If we go through the suffixes in sorted order, the new substrings added by each suffix are exactly its prefixes longer than the LCP with the previous suffix. These prefixes must be new, or else the property $lcp(sa[i],sa[j])=\min\{height[i+1..j]\}$ would be violated. And only these prefixes are new, because the LCP part was already counted with the previous suffix.

So the answer is:

$\frac{n(n+1)}{2}-\sum\limits_{i=2}^nheight[i]$

### Maximum length of a substring that occurs at least k times

Example problem: [USACO 2006 December — Milk Patterns](https://www.luogu.com.cn/problem/P2852).

??? note "Solution"
    Occurring at least $k$ times means that, after sorting the suffixes, there are at least $k$ consecutive suffixes that have this substring as a common prefix.
    
    So compute the minimum of every $k-1$ consecutive $height$ values; the maximum of these minimums is the answer.
    
    This can be done in $O(n)$ with a monotonic queue, but other methods are also good enough to get AC.

??? note "Reference code"
    ```cpp
    --8<-- "docs/string/code/sa/sa_2.cpp"
    ```

### Does some string occur at least twice in the text without overlapping?

Binary search on the length $|s|$ of the target string. Split the $h$ array into segments in which consecutive LCPs are all at least $|s|$. For each segment, use RMQ to find the largest and smallest index among the suffixes in it. If the distance between these two indices meets the condition, then some string of length $|s|$ occurs twice without overlapping.

### Several consecutive copies of the same substring

We can enumerate the length $|s|$ of the repeated unit, split the whole string into blocks of length $|s|$, and run LCP and LCS queries on the starting positions of adjacent blocks. For details, see [\[2009\] Suffix Arrays: A Powerful Tool for Processing Strings][2].

Example problem: [NOI 2016 — Excellent Split](https://loj.ac/p/2083).

### Combining with DSU

In some problems, you need to split the suffix array into segments in which consecutive LCPs are all at least some value; that is, split the $h$ array into segments whose minimum is at least some value, and compute an answer for each segment. If there are many queries, we can process them offline. Notice that as the given value decreases, the number of valid intervals only goes down; each new interval is formed by joining two or more old intervals, and the $h$ values in the new interval that are not inside an old interval all equal the value we have decreased to. So we only need to maintain a disjoint set union, merge two adjacent intervals each time, and maintain the statistics.

Classic problem: [NOI 2015 — Wine Tasting Party](https://uoj.ac/problem/131)

### Combining with a segment tree

Some problems ask for the first few numbers that satisfy a condition, and these numbers lie in a range of the sorted suffixes. In that case, we can merge the information of two nodes using the idea of merge sort, and use a segment tree to maintain and query the answer for a range.

### Combining with a monotonic stack

Example problem: [AHOI 2013 — Difference](https://loj.ac/problem/2377)

??? note "Solution"
    The first two terms of the sum are easy: they give $n(n-1)(n+1)/2$ (each suffix appears $n-1$ times, and the total length of all suffixes is $n(n+1)/2$). The key is the last term, the pairwise LCPs of the suffixes.
    
    We know that $lcp(i,j)=k$ is equivalent to $\min\{height[i+1..j]\}=k$. So we can count $lcp(i,j)$ as the contribution of $\min\{x|i+1\le x\le j, height[x]=lcp(i,j)\}$ to the answer.
    
    For each position, consider which pairs of suffixes it contributes the LCP of. It is exactly the pairs formed by picking one suffix from the run of consecutive positions to its left whose $height$ is greater than its own, and one suffix from the run of consecutive positions to its right whose $height$ is not smaller than its own. This can be computed with a [monotonic stack](../ds/monotonic-stack.md).
    
    The monotonic stack part is similar to [Luogu P2659 Beautiful Sequence](https://www.luogu.com.cn/problem/P2659) and the [hanging line method](../misc/hoverline.md).

??? note "Reference code"
    ```cpp
    --8<-- "docs/string/code/sa/sa_3.cpp"
    ```

A similar problem: [HAOI 2016 — Finding Identical Characters](https://loj.ac/problem/2064).

## Exercises

-   [UVa 760 - DNA Sequencing](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=701)
-   [UVa 1223 - Editor](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=3664)
-   [Codechef - Tandem](https://www.codechef.com/problems/TANDEM)
-   [Codechef - Substrings and Repetitions](https://www.codechef.com/problems/ANUSAR)
-   [Codechef - Entangled Strings](https://www.codechef.com/problems/TANGLED)
-   [Codeforces - Martian Strings](http://codeforces.com/problemset/problem/149/E)
-   [Codeforces - Little Elephant and Strings](http://codeforces.com/problemset/problem/204/E)
-   [SPOJ - Ada and Terramorphing](http://www.spoj.com/problems/ADAPHOTO/)
-   [SPOJ - Ada and Substring](http://www.spoj.com/problems/ADASTRNG/)
-   [UVa - 1227 - The longest constant gene](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=3668)
-   [SPOJ - Longest Common Substring](http://www.spoj.com/problems/LCS/en/)
-   [UVa 11512 - GATTACA](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2507)
-   [QOJ 11240 - Suffixes and Palindromes](https://qoj.ac/problem/11240)
-   [GYM - Por Costel and the Censorship Committee](http://codeforces.com/gym/100923/problem/D)
-   [UVa 1254 - Top 10](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3695)
-   [UVa 12191 - File Recover](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3343)
-   [UVa 12206 - Stammering Aliens](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=3358)
-   [Codechef - Jarvis and LCP](https://www.codechef.com/problems/INSQ16F)
-   [Luogu P8617 - Repeated Pattern](https://www.luogu.com.cn/problem/P8617)
-   [UVa 11107 - Life Forms](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2048)
-   [UVa 12974 - Exquisite Strings](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=862&page=show_problem&problem=4853)
-   [UVa 10526 - Intellectual Property](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1467)
-   [UVa 12338 - Anti-Rhyme Pairs](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=3760)
-   [DevSkills Reconstructing Blue Print of Life](https://devskill.com/CodingProblems/ViewProblem/328)
-   [UVa 12191 - File Recover](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3343)
-   [SPOJ - Suffix Array](http://www.spoj.com/problems/SARRAY/)
-   [Gym 102470J - Stammering Aliens](https://codeforces.com/gym/102470/problem/J)
-   [SPOJ - LCS2](http://www.spoj.com/problems/LCS2/)
-   [Codeforces - Fake News (hard)](http://codeforces.com/contest/802/problem/I)
-   [SPOJ - Longest Commong Substring](http://www.spoj.com/problems/LONGCS/)
-   [SPOJ - Lexicographical Substring Search](http://www.spoj.com/problems/SUBLEX/)
-   [Codeforces - Forbidden Indices](http://codeforces.com/contest/873/problem/F)
-   [Codeforces - Tricky and Clever Password](http://codeforces.com/contest/30/problem/E)
-   [Gym 101470B - Circle of digits](https://codeforces.com/gym/101470/problem/B)

## References

Parts of this page (those introduced in [4070a9b](https://github.com/OI-wiki/OI-wiki/pull/950/commits/4070a9b3db8576db16c74d3ec33806ad10476eef)) are mainly translated from the article [Суффиксный массив](http://e-maxx.ru/algo/suffix_array) and its English translation [Suffix Array](https://cp-algorithms.com/string/suffix-array.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.

Papers:

1.  [\[2004\] Suffix Arrays, by Xu Zhilei][1]

2.  [\[2009\] Suffix Arrays: A Powerful Tool for Processing Strings, by Luo Suiqian][2]

[1]: https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2004%E8%AE%BA%E6%96%87%E9%9B%86/%E8%AE%B8%E6%99%BA%E7%A3%8A--%E5%90%8E%E7%BC%80%E6%95%B0%E7%BB%84.pdf "[2004] Suffix Arrays, by Xu Zhilei"

[2]: https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2009%E8%AE%BA%E6%96%87%E9%9B%86/11.%E7%BD%97%E7%A9%97%E9%AA%9E%E3%80%8A%E5%90%8E%E7%BC%80%E6%95%B0%E7%BB%84%E2%80%94%E2%80%94%E5%A4%84%E7%90%86%E5%AD%97%E7%AC%A6%E4%B8%B2%E7%9A%84%E6%9C%89%E5%8A%9B%E5%B7%A5%E5%85%B7%E3%80%8B/%E5%90%8E%E7%BC%80%E6%95%B0%E7%BB%84%E2%80%94%E2%80%94%E5%A4%84%E7%90%86%E5%AD%97%E7%AC%A6%E4%B8%B2%E7%9A%84%E6%9C%89%E5%8A%9B%E5%B7%A5%E5%85%B7.pdf "[2009] Suffix Arrays: A Powerful Tool for Processing Strings, by Luo Suiqian"
