This page gives a short introduction to digit DP.

## Introduction

"Digits" means splitting a number into its ones, tens, hundreds, thousands and so on, and looking at the digit in each position. For a decimal number, each digit is 0\~9; other bases work the same way.

Digit DP solves a specific kind of problem. These problems are fairly easy to recognize. They usually have these features:

1.  You are asked to count how many numbers satisfy some condition (that is, the final goal is counting);

2.  After some transformation, the conditions can be understood and checked digit by digit;

3.  The input gives a range of numbers (sometimes only an upper bound) that limits what is counted;

4.  The upper bound is very large (for example $10^{18}$), so brute-force enumeration and checking would be too slow.

The basic idea of digit DP:

Think about how people count. The simplest way is to start small and add one each time. But for numbers with many digits, this process repeats a lot of work. For example, counting from 7000 to 7999, from 8000 to 8999, and from 9000 to 9999 are very similar: in each case the last three digits go from 000 to 999, and only the thousands digit is different. So we can merge these processes and store the counts they produce in one shared array. The states of this array are set up according to what the problem asks, and transitions are done by recurrence or DP.

Digit DP often uses standard counting tricks, such as splitting the answer for a range into the difference of two parts (that is, $\mathit{ans}_{[l, r]} = \mathit{ans}_{[0, r]}-\mathit{ans}_{[0, l - 1]}$)

Once we have the shared answer array, the next step is to compute the answer. This can be done with memoized search or with an iterative loop. To count every number not exceeding the upper bound exactly once, enumerate the digits from the highest to the lowest, consider which digits can go in each position, and then use the shared answer array to add up the answer.

Now let's look at some concrete problems.

## Example problem 1

???+ note "Example 1 [Luogu P2602 Digit Counting](https://www.luogu.com.cn/problem/P2602)"
    Summary: given two positive integers $a,b$, find how many times each digit appears across all integers in $[a,b]$.

### Method 1

#### Solution

Notice that among all numbers with exactly $\mathit{i}$ digits (padded), every digit appears the same number of times. So let $\mathit{dp}_i$ be the number of times each digit appears among all $i$-digit numbers, ignoring leading zeros for now. Then $\mathit{dp}_i=10 \times \mathit{dp}_{i−1}+10^{i−1}$. The first term is the contribution of the first $i-1$ digits, and the second is the contribution of the $i$-th digit.

With the $\mathit{dp}$ array, let's see how to compute the answer. Split the upper bound into digits and enumerate from high to low. When we are not hugging the upper bound, the remaining digits can be anything. When we are hugging the upper bound, the remaining digits can only go from $0$ up to the bound. Compute the contributions of these two parts separately. Finally, handle leading zeros: when the $i$-th digit is a leading $0$, digits $1$ to $\mathit{i-1}$ are also $0$, which means we have overcounted by the answer for filling all $i-1$ digits, so we need to subtract that.

#### Implementation

???+ note "Reference code"
    ```cpp
    #include <cstdio>
    using namespace std;
    constexpr int N = 15;
    using ll = long long;
    ll l, r, dp[N], mi[N];
    ll ans1[N], ans2[N];
    int a[N];
    
    void solve(ll n, ll *ans) {
      ll tmp = n;
      int len = 0;
      while (n) a[++len] = n % 10, n /= 10;
      for (int i = len; i >= 1; --i) {
        for (int j = 0; j < 10; j++) ans[j] += dp[i - 1] * a[i];
        for (int j = 0; j < a[i]; j++) ans[j] += mi[i - 1];
        tmp -= mi[i - 1] * a[i], ans[a[i]] += tmp + 1;
        ans[0] -= mi[i - 1];
      }
    }
    
    int main() {
      scanf("%lld%lld", &l, &r);
      mi[0] = 1ll;
      for (int i = 1; i <= 13; ++i) {
        dp[i] = dp[i - 1] * 10 + mi[i - 1];
        mi[i] = 10ll * mi[i - 1];
      }
      solve(r, ans1), solve(l - 1, ans2);
      for (int i = 0; i < 10; ++i) printf("%lld ", ans1[i] - ans2[i]);
      return 0;
    }
    ```

### Method 2

#### Solution

This problem can also be solved with memoized search. $\mathit{dp}_i$ is the answer for $i$ digits when not hugging the upper bound and with no leading zeros.

See the comments in the code for details.

#### Process

???+ note "Reference code"
    ```cpp
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    using namespace std;
    using ll = long long;
    constexpr int N = 50005;
    ll a, b;
    ll f[15], ksm[15], p[15], now[15];
    
    ll dfs(int u, int x, bool f0,
           bool lim) {  // u: number of digits, f0: whether there are leading zeros, lim: whether every digit so far hugs the upper bound
      if (!u) {
        if (f0) f0 = false;
        return 0;
      }
      if (!lim && !f0 && (~f[u])) return f[u];
      ll cnt = 0;
      int lst = lim ? p[u] : 9;
      for (int i = 0; i <= lst; i++) {  // enumerate the digit to place here
        if (f0 && i == 0)
          cnt += dfs(u - 1, x, 1, lim && i == lst);  // handle leading zeros
        else if (i == x && lim && i == lst)
          cnt += now[u - 1] + 1 +
                 dfs(u - 1, x, 0,
                     lim && i == lst);  // here the digits enumerated so far all hug the given upper bound.
        else if (i == x)
          cnt += ksm[u - 1] + dfs(u - 1, x, 0, lim && i == lst);
        else
          cnt += dfs(u - 1, x, 0, lim && i == lst);
      }
      if ((!lim) && (!f0)) f[u] = cnt;  // only memoize when not hugging the upper bound and without leading zeros
      return cnt;
    }
    
    ll gans(ll d, int dig) {
      int len = 0;
      memset(f, -1, sizeof(f));
      while (d) {
        p[++len] = d % 10;
        d /= 10;
        now[len] = now[len - 1] + p[len] * ksm[len - 1];
      }
      return dfs(len, dig, 1, 1);
    }
    
    int main() {
      scanf("%lld%lld", &a, &b);
      ksm[0] = 1;
      for (int i = 1; i <= 12; i++) ksm[i] = ksm[i - 1] * 10ll;
      for (int i = 0; i < 9; i++) printf("%lld ", gans(b, i) - gans(a - 1, i));
      printf("%lld\n", gans(b, 9) - gans(a - 1, 9));
      return 0;
    }
    ```

## Example problem 2

???+ note "Example 2 [HDU 2089 No 62](https://acm.hdu.edu.cn/showproblem.php?pid=2089)"
    Summary: count the numbers in a range whose digits contain no 4 and no consecutive "62".

### Solution

For "no 4", we just check while enumerating: if we never place a 4, the state stays valid, so this constraint needs no memoization. "62" involves two digits: the counts differ depending on whether the previous digit is 6 or not, so we need a state to record the number of ways for each case. $\mathit{dp}_{\mathit{pos},\mathit{sta}}$ means we are at digit $\mathit{pos}$, with state telling whether the previous digit is 6. Here $\mathit{sta}$ only needs two values, 0 and 1: all "not 6" cases can be treated as the same, which does not affect the count.

### Implementation

???+ note "Reference code"
    ```cpp
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    using namespace std;
    int x, y, dp[15][3], p[50];
    
    void pre() {
      memset(dp, 0, sizeof(dp));
      dp[0][0] = 1;
      for (int i = 1; i <= 10; i++) {
        dp[i][0] = dp[i - 1][0] * 9 - dp[i - 1][1];
        dp[i][1] = dp[i - 1][0];
        dp[i][2] = dp[i - 1][2] * 10 + dp[i - 1][1] + dp[i - 1][0];
      }
    }
    
    int cal(int x) {
      int cnt = 0, ans = 0, tmp = x;
      while (x) {
        p[++cnt] = x % 10;
        x /= 10;
      }
      bool flag = false;
      p[cnt + 1] = 0;
      for (int i = cnt; i; i--) {  // enumerate digits from high to low
        ans += p[i] * dp[i - 1][2];
        if (flag)
          ans += p[i] * dp[i - 1][0];
        else {
          if (p[i] > 4) ans += dp[i - 1][0];
          if (p[i] > 6) ans += dp[i - 1][1];
          if (p[i] > 2 && p[i + 1] == 6) ans += dp[i][1];
          if (p[i] == 4 || (p[i] == 2 && p[i + 1] == 6)) flag = true;
        }
      }
      return tmp - ans;
    }
    
    int main() {
      pre();
      while (~scanf("%d%d", &x, &y)) {
        if (!x && !y) break;
        if (x > y) swap(x, y);
        printf("%d\n", cal(y + 1) - cal(x));
      }
      return 0;
    }
    ```

## Example problem 3

???+ note "Example 3 [SCOI2009 Windy Numbers](https://loj.ac/problem/10165)"
    Summary: given a range $[l,r]$, count the numbers in it that **have no leading $0$ and in which any two adjacent digits differ by at least $2$**.

### Solution

First, turn the problem into a simpler form. Let $\mathit{ans}_i$ be the number of valid numbers in $[1,i]$. Then the answer is $\mathit{ans}_r-\mathit{ans}_{l-1}$.

For any number less than $n$, going from high to low, there must be some digit where its value is less than the corresponding digit of $n$, while all the earlier digits equal those of $n$.

Using this property, define $f(i,st,op)$ as the count of numbers when we are about to decide the $i$-th digit from the top, the state of the current prefix is $st$, and the relation between the prefix and the number being solved for is $op$ ($op=1$ means equal, $op=0$ means less). In this problem, the state of the prefix is the value of the previous digit, because which values the next digit cannot take depends only on the previous digit. In other problems this value could be: the digit sum of the prefix, the $\gcd$ of all digits in the prefix, the prefix modulo some number, or a combination of two or more of these.

Write the **state transition equation**: $f(i,st,op)=\sum_{k=1}^{\mathit{maxx}} f(i+1,k,op=1~ \operatorname{and}~ k=\mathit{maxx} )\quad (|\mathit{st}-k|\ge 2)$

Here $k$ is the value of the next digit being enumerated, and $\mathit{maxx}$ is the largest value this digit can take. This is because if $\mathit{op}=1$, the value at this digit cannot exceed the corresponding digit of the number being solved for; otherwise there is no limit.

Notice that even if the prefixes chosen are different, as long as the three parameters of $f$ are the same, the answer is the same. To avoid computing this answer many times, we can implement it with [memoized search](./memo.md).

### Implementation

???+ note "Reference code"
    ```cpp
    int dfs(int x, int st, int op)  // op=1 =; op=0 <
    {
      if (!x) return 1;
      if (!op && ~f[x][st]) return f[x][st];
      int maxx = op ? dim[x] : 9, ret = 0;
      for (int i = 0; i <= maxx; i++) {
        if (abs(st - i) < 2) continue;
        if (st == 11 && i == 0)
          ret += dfs(x - 1, 11, op & (i == maxx));
        else
          ret += dfs(x - 1, i, op & (i == maxx));
      }
      if (!op) f[x][st] = ret;
      return ret;
    }
    
    int solve(int x) {
      memset(f, -1, sizeof f);
      dim.clear();
      dim.push_back(-1);
      int t = x;
      while (x) {
        dim.push_back(x % 10);
        x /= 10;
      }
      return dfs(dim.size() - 1, 11, 1);
    }
    ```

## Example problem 4

???+ note "Example 4.[SPOJMYQ10](https://www.spoj.com/problems/MYQ10/en/)"
    Summary: if you write down all integers in $[n,m]$ by hand, how many of them look exactly the same as their reflection in a mirror? ($n,m<10^{44}, T<10^5$)

### Solution

Note: since we are dealing with mirror images, only $0,1,8$ are their own mirror images. So "exactly the same" here is not a palindrome in the usual sense, but a palindrome that contains only $0,1,8$.

First, clearly only $0,1,8$ can be chosen during the digit DP.

Second, since the values exceed the range of long long, $[n,m]=[1,m]-[1,n-1]$ no longer works (big-number arithmetic is tedious). Instead, we check whether $n$ itself is valid, which gives $[n,m]=[1,m]-[1,n]+\mathrm{check}(n)$.

Mirroring is handled. How do we check for palindromes?

We use a small array to record the earlier digits. Before reaching half the length, we only need to stay within the upper bound. After passing half the length, we also need to check that each digit equals its "mirror" digit.

Note in particular that the memoization part of this problem must not use `memset`, otherwise it will exceed the time limit.

### Implementation

???+ note "Reference code"
    ```cpp
    int check(char cc[]) {  // special check for n
      int strc = strlen(cc);
      for (int i = 0; i < strc; ++i) {
        if (!(cc[i] == cc[strc - i - 1] &&
              (cc[i] == '1' || cc[i] == '8' || cc[i] == '0')))
          return 0ll;
      }
      return 1ll;
    }
    
    // now: current digit, eff: number of effective digits, fulc: whether all digits hug the bound, ful0: whether all digits are 0
    int dfs(int now, int eff, bool ful0, bool fulc) {
      if (now == 0) return 1ll;
      if (!fulc && f[now][eff][ful0] != -1)  // memoization
        return f[now][eff][ful0];
    
      int res = 0, maxk = fulc ? dig[now] : 9;
      for (int i = 0; i <= maxk; ++i) {
        if (i != 0 && i != 1 && i != 8) continue;
        b[now] = i;
        if (ful0 && i == 0)  // all leading 0s
          res += dfs(now - 1, eff - 1, 1, 0);
        else if (now > eff / 2)                                  // first half not finished
          res += dfs(now - 1, eff, 0, fulc && (dig[now] == i));  // past the halfway point
        else if (b[now] == b[eff - now + 1])
          res += dfs(now - 1, eff, 0, fulc && (dig[now] == i));
      }
      if (!fulc) f[now][eff][ful0] = res;
      return res;
    }
    
    char cc1[100], cc2[100];
    int strc, ansm, ansn;
    
    int get(char cc[]) {  // wrapper
      strc = strlen(cc);
      for (int i = 0; i < strc; ++i) dig[strc - i] = cc[i] - '0';
      return dfs(strc, strc, 1, 1);
    }
    
    scanf("%s%s", cc1, cc2);
    printf("%lld\n", get(cc2) - get(cc1) + check(cc1));
    ```

## Example problem 5

???+ note "Example 5.[P3311 Counting](https://www.luogu.com.cn/problem/P3311)"
    Statement: a positive integer $x$ is called a lucky number if and only if its decimal representation contains no element of the string set $S$ as a substring. For example, when $S = \{22, 333, 0233\}$, $233233$ is a lucky number, while $23332333$, $2023320233$ and $32233223$ are not. Given $n$ and $S$, count the lucky numbers not greater than $n$. Output the answer modulo $10^9 + 7$.
    
    $1 \leq n<10^{1201}, 1 \leq m \leq 100, 1 \leq \sum_{i = 1}^m |s_i| \leq 1500, \min_{i = 1}^m |s_i| \geq 1$, where $|s_i|$ is the length of string $s_i$. $n$ has no leading $0$, but $s_i$ may have leading $0$s.

### Solution

Reading the statement, if we treat numbers as strings, this is a multi-pattern matching task, which naturally suggests the Aho–Corasick automaton. In ordinary digit DP, we enumerate digit positions from high to low and then what to put in each one. In this problem, this naturally becomes: enumerate how many digits have been placed, then enumerate which node of the Aho–Corasick automaton we are currently at, and move from the current node to its children in the automaton.

Let $f(i,j,0/1)$ mean that, going from high to low, we have placed $i$ digits (that is, walked $i$ edges in the Aho–Corasick automaton), we are now at node $j$, and the last flag says whether we are exactly hugging the upper bound.

As for the "contains no" condition, just mark the end node of every pattern in the Aho–Corasick automaton, and skip such end nodes whenever the DP reaches them.

The transitions are easy to come up with; see the main function in the code.

### Implementation

???+ note "Reference code"
    ```cpp
    #include <cstdio>
    #include <cstring>
    #include <queue>
    using namespace std;
    using ll = long long;
    constexpr int N = 1505;
    constexpr int mod = 1000000007;
    int n, m;
    char s[N], c[N];
    int ch[N][10], fail[N], ed[N], tot, len;
    
    void insert() {
      int now = 0;
      int L = strlen(s);
      for (int i = 0; i < L; ++i) {
        if (!ch[now][s[i] - '0']) ch[now][s[i] - '0'] = ++tot;
        now = ch[now][s[i] - '0'];
      }
      ed[now] = 1;
    }
    
    queue<int> q;
    
    void build() {
      for (int i = 0; i < 10; ++i)
        if (ch[0][i]) q.push(ch[0][i]);
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 10; ++i) {
          if (ch[u][i]) {
            fail[ch[u][i]] = ch[fail[u]][i], q.push(ch[u][i]),
            ed[ch[u][i]] |= ed[fail[ch[u][i]]];
          } else
            ch[u][i] = ch[fail[u]][i];
        }
      }
      ch[0][0] = 0;
    }
    
    ll f[N][N][2], ans;
    
    void add(ll &x, ll y) { x = (x + y) % mod; }
    
    int main() {
      scanf("%s", c);
      n = strlen(c);
      scanf("%d", &m);
      for (int i = 1; i <= m; ++i) scanf("%s", s), insert();
      build();
      f[0][0][1] = 1;
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= tot; ++j) {
          if (ed[j]) continue;
          for (int k = 0; k < 10; ++k) {
            if (ed[ch[j][k]]) continue;
            add(f[i + 1][ch[j][k]][0], f[i][j][0]);
            if (k < c[i] - '0') add(f[i + 1][ch[j][k]][0], f[i][j][1]);
            if (k == c[i] - '0') add(f[i + 1][ch[j][k]][1], f[i][j][1]);
          }
        }
      }
      for (int j = 0; j <= tot; ++j) {
        if (ed[j]) continue;
        add(ans, f[n][j][0]);
        add(ans, f[n][j][1]);
      }
      printf("%lld\n", ans - 1);
      return 0;
    }
    ```

This problem is a good way to understand how digit DP works.

## Exercises

[AHOI2009 self Same-Class Distribution](https://www.luogu.com.cn/problem/P4127)

[Luogu P3413 SAC#1 - Cute Numbers](https://www.luogu.com.cn/problem/P3413)

[HDU 6148 Valley Number](https://acm.hdu.edu.cn/showproblem.php?pid=6148)

[CF55D Beautiful numbers](http://codeforces.com/problemset/problem/55/D)

[CF628D Magic Numbers](http://codeforces.com/problemset/problem/628/D)
