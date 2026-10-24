## Definition

Memoized search is a way to implement search that records information about states it has already visited, so it never explores the same state twice.

Because memoized search guarantees that each state is visited only once, it is also a common way to implement dynamic programming.

## Introduction

???+ note "[\[NOIP2005\] Herb Gathering](https://www.luogu.com.cn/problem/P1048)"
    There are $M$ different herbs in a cave. Picking herb $i$ takes time $t_i$, and each herb has its own value $v_i$. You are given a total time $T$, during which you can pick some of the herbs. Maximize the total value of the herbs you pick.
    
    $1 \leq T \leq 10^3$, $1 \leq t_i,v_i,M \leq 100$

### Naive [DFS](../search/dfs.md) approach

A naive search is easy to write. During the search, keep three parameters: which item we are about to decide on, how much time is left, and how much value we have collected so far. Then try both choices for the current item (take it or not) and move to the corresponding state.

???+ note "Implementation"
    === "C++"
        ```cpp
        int n, t;
        int tcost[103], mget[103];
        int ans = 0;
        
        void dfs(int pos, int tleft, int tans) {
          if (tleft < 0) return;
          if (pos == n + 1) {
            ans = max(ans, tans);
            return;
          }
          dfs(pos + 1, tleft, tans);
          dfs(pos + 1, tleft - tcost[pos], tans + mget[pos]);
        }
        
        int main() {
          cin >> t >> n;
          for (int i = 1; i <= n; i++) cin >> tcost[i] >> mget[i];
          dfs(1, t, 0);
          cout << ans << endl;
          return 0;
        }
        ```
    
    === "Python"
        ```python
        tcost = [0] * 103
        mget = [0] * 103
        ans = 0
        
        
        def dfs(pos, tleft, tans):
            global ans
            if tleft < 0:
                return
            if pos == n + 1:
                ans = max(ans, tans)
                return
            dfs(pos + 1, tleft, tans)
            dfs(pos + 1, tleft - tcost[pos], tans + mget[pos])
        
        
        t, n = map(lambda x: int(x), input().split())
        for i in range(1, n + 1):
            tcost[i], mget[i] = map(lambda x: int(x), input().split())
        dfs(1, t, 0)
        print(ans)
        ```

The time complexity of this approach is exponential, so it is too slow for this problem.

### Optimization

Why is the approach above so slow? Because the same state gets visited many times.

If we store the information of each state once we have computed it, then the next time we need that state we can just reuse the stored result and avoid computing it again. This takes full advantage of the fact that many dynamic programming problems have lots of overlapping subproblems. It is the idea of "memoization": trading space for time.

For this problem, we start from the naive DFS and add an array `mem` that records the return value of each `dfs(pos,tleft)`. At the beginning, set every value in `mem` to `-1` (meaning "not computed yet"). Whenever we need a state, if its value in `mem` is `-1`, we visit it recursively. Otherwise, we simply use the value already stored in `mem`.

With this change, each state is visited only once, so the time complexity of the algorithm is $O(TM)$.

???+ note "Implementation"
    === "C++"
        ```cpp
        int n, t;
        int tcost[103], mget[103];
        int mem[103][1003];
        
        int dfs(int pos, int tleft) {
          if (mem[pos][tleft] != -1)
            return mem[pos][tleft];  // state already visited: return the stored value
          if (pos == n + 1) return mem[pos][tleft] = 0;
          int dfs1, dfs2 = -INF;
          dfs1 = dfs(pos + 1, tleft);
          if (tleft >= tcost[pos])
            dfs2 = dfs(pos + 1, tleft - tcost[pos]) + mget[pos];  // state transition
          return mem[pos][tleft] = max(dfs1, dfs2);  // finally, store the value of the current state
        }
        
        int main() {
          memset(mem, -1, sizeof(mem));
          cin >> t >> n;
          for (int i = 1; i <= n; i++) cin >> tcost[i] >> mget[i];
          cout << dfs(1, t) << endl;
          return 0;
        }
        ```
    
    === "Python"
        ```python
        tcost = [0] * 103
        mget = [0] * 103
        mem = [[-1 for i in range(1003)] for j in range(103)]
        
        
        def dfs(pos, tleft):
            if mem[pos][tleft] != -1:
                return mem[pos][tleft]
            if pos == n + 1:
                mem[pos][tleft] = 0
                return mem[pos][tleft]
            dfs1 = dfs2 = -INF
            dfs1 = dfs(pos + 1, tleft)
            if tleft >= tcost[pos]:
                dfs2 = dfs(pos + 1, tleft - tcost[pos]) + mget[pos]
            mem[pos][tleft] = max(dfs1, dfs2)
            return mem[pos][tleft]
        
        
        t, n = map(lambda x: int(x), input().split())
        for i in range(1, n + 1):
            tcost[i], mget[i] = map(lambda x: int(x), input().split())
        print(dfs(1, t))
        ```

## How it relates to and differs from iterative DP

When solving dynamic programming problems, code for memoized search and code for iterative (bottom-up) DP look very similar. This is because they use the same state representation and similar transitions. For the same reason, the two implementations usually have the same time complexity.

Below is the iterative version (without the rolling array optimization, to make comparison easier). Comparing them shows how similar the two are in form.

```cpp
int n, t, w[105], v[105], f[105][1005];

int main() {
  cin >> n >> t;
  for (int i = 1; i <= n; i++) cin >> w[i] >> v[i];
  for (int i = 1; i <= n; i++)
    for (int j = 0; j <= t; j++) {
      f[i][j] = f[i - 1][j];
      if (j >= w[i])
        f[i][j] = max(f[i][j], f[i - 1][j - w[i]] + v[i]);  // state transition equation
    }
  cout << f[n][t];
  return 0;
}
```

When solving dynamic programming problems, both memoized search and iterative DP make sure each state is solved at most once. They achieve this in slightly different ways: iterative DP avoids repeated visits by fixing an explicit order of evaluation, while memoized search has no explicit order but reaches the same goal by marking states that have already been visited.

Compared with iterative DP, memoized search does not require an explicit evaluation order, so it is sometimes easier to write, and it handles boundary cases more conveniently. This is a major advantage of memoized search. On the other hand, it is hard to apply optimizations such as rolling arrays to memoized search, and because of recursion it runs slower than iterative DP. So you should choose whichever implementation fits the problem better.

## How to write a memoized search

### Method 1

1.  Write down the DP states and transition equation for the problem
2.  Write a dfs function based on them
3.  Add a memoization array

Example:

$dp_{i} = \max\{dp_{j}+1\}\quad (1 \leq j < i \land a_{j}<a_{i})$ (longest increasing subsequence)

becomes

=== "C++"
    ```cpp
    int dfs(int i) {
      if (mem[i] != -1) return mem[i];
      int ret = 1;
      for (int j = 1; j < i; j++)
        if (a[j] < a[i]) ret = max(ret, dfs(j) + 1);
      return mem[i] = ret;
    }
    
    int main() {
      memset(mem, -1, sizeof(mem));
      // input reading omitted
      int ret = 0;
      for (int j = 1; j <= n; j++) {
        ret = max(ret, dfs(j));
      }
      cout << ret << endl;
    }
    ```

=== "Python"
    ```python
    def dfs(i):
        if mem[i] != -1:
            return mem[i]
        ret = 1
        for j in range(1, i):
            if a[j] < a[i]:
                ret = max(ret, dfs(j) + 1)
        mem[i] = ret
        return mem[i]
    ```

### Method 2

1.  Write a brute-force search program for the problem (preferably a [dfs](../search/dfs.md))
2.  Turn this dfs into one that "does not need external variables"
3.  Add a memoization array

Example: the "Herb Gathering" example in this article
