author: Ir1d, Tiphereth-A, sshwy, ksyx, Marcythm, orzAtalod, Xeonacid, Enter-tainer, GavinZhengOI, Henry-ZHR, iamtwz, 383494, abc1763613206, aofall, Chrogeek, CoelacanthusHex, Dafenghh, DanJoshua, Gesrua, kenlig, lyccrius, Menci, opsiff, ouuan, partychicken, Persdre, Ruakker, shuzhouliu, StudyingFather, szdytom, XuYueming520, ZXyaang, alphagocc, c-forrest, Early0v0, GoodCoder666, HeRaNO, liangbob2023, qq2964, r-value, rickyxrc, Rickyxrc, shawlleyw, Unnamed2964, zica87, ZnPdCo, sun2snow

## Overview

The AC (Aho–Corasick) automaton is an automaton **built on the structure of a trie** combined with **the idea of KMP**. It is used for tasks such as matching many patterns at once.

In essence, the Aho–Corasick automaton is an automaton on a trie.

Before reading this article, please read [KMP](./kmp.md) and [Trie](./trie.md) first.

## Explanation

Simply put, building an Aho–Corasick automaton takes two steps:

1.  The basic trie structure: build a trie from all the patterns;
2.  The idea of KMP: build failure pointers for every node of the trie.

Once it is built, you can use it to match many patterns at once.

## Building the trie

The Aho–Corasick automaton starts by inserting all the patterns into a trie, and then builds the automaton on that trie. This trie is just an ordinary trie, built in the usual way.

Note that each node of the trie represents a prefix of some pattern. Later in this article we also call these nodes states. One node is one state, and the edges of the trie are the transitions between states.

Formally, for patterns $s_1,s_2,\cdots,s_n$, let $Q$ be the set of all states of the trie built from them.

## Failure pointers

The Aho–Corasick automaton uses a fail pointer to help match multiple patterns.

The fail pointer of state $u$ points to another state $v$, where $v\in Q$ and $v$ is the longest suffix of $u$ (that is, among all states that are suffixes, take the longest one as the fail pointer).

Comparing the fail pointer with the next pointer in [KMP](./kmp.md):

1.  What they share: both are pointers used to jump when a mismatch happens.
2.  How they differ: the next pointer gives the longest border (the longest string that is both a proper prefix and a suffix), while the fail pointer points to the longest suffix of the current state that is a prefix of some pattern.

This is because KMP matches only one pattern, while the Aho–Corasick automaton matches many. The node the fail pointer points to may belong to a different pattern, with a different prefix.

To sum up, the failure pointer of the Aho–Corasick automaton points to the longest suffix state of the current state.

Note: when the Aho–Corasick automaton matches, several patterns can match at the same position.

### Building the pointers

Here is the **basic idea** of building fail pointers:

To build fail pointers, we can borrow the idea of building the next pointers in KMP.

Consider the current node $u$ in the trie. Its parent is $p$, and $p$ points to $u$ through an edge labeled with character $c$, that is, $\operatorname{trie}(p, c)=u$. Assume the fail pointers of all nodes shallower than $u$ are already known.

1.  If $\operatorname{trie}(\operatorname{fail}(p), c)$ exists: let the fail pointer of $u$ point to $\operatorname{trie}(\operatorname{fail}(p), c)$. This is like appending a character $c$ to both $p$ and $\operatorname{fail}(p)$, giving $u$ and $\operatorname{fail}(u)$ respectively;
2.  If $\operatorname{trie}(\operatorname{fail}(p), c)$ does not exist: then we go on to look at $\operatorname{trie}(\operatorname{fail}(\operatorname{fail}(p)), c)$. Repeat this check, following fail pointers all the way up to the root;
3.  If it still does not exist, let the fail pointer point to the root.

This completes the construction of $\operatorname{fail}(u)$.

### Example

The GIF animations below show how fail pointers are built for the trie made from the strings $\mathtt{i}$, $\mathtt{he}$, $\mathtt{his}$, $\mathtt{she}$, $\mathtt{hers}$:

1.  Yellow node: the current node $u$.
2.  Green nodes: nodes already visited by BFS.
3.  Orange edges: fail pointers.
4.  Red edge: the fail pointer just computed.

![AC\_automation\_gif\_b\_3.gif](./images/ac-automaton1.gif)

Let us look closely at how the fail pointer of node $6$ is built:

![AC\_automation\_6\_9.png](./images/ac-automaton1.png)

Find the parent of $6$, which is $5$, with $\operatorname{fail}(5)=10$. But node $10$ has no outgoing edge labeled $\mathtt{s}$. So we jump on to the fail pointer of $10$: $\operatorname{fail}(10)=0$. Node $0$ does have an outgoing edge labeled $\mathtt{s}$, pointing to node $7$. So $\operatorname{fail}(6)=7$.

The figure below shows the finished state:

![finish](./images/ac-automaton4.png)

## Trie and trie graph

Look at the construction function `build`. It has two goals: build the fail pointers, and build the automaton. The variables are defined as follows:

1.  `tr[u].son[c]`: this can be read in two ways. We can simply see it as an edge of the trie, that is, $\operatorname{trie}(u, c)$. Or we can see it as the state (node) reached by appending a character $c$ to state (node) $u$, that is, a state transition function $\operatorname{trans}(u, c)$. For convenience, we use the second reading below.
2.  Queue `q`: used to traverse the trie with BFS.
3.  `tr[u].fail`: the fail pointer of node $u$.

???+ note "Implementation"
    === "C++"
        ```cpp
        void build() {
          queue<int> q;
          for (int i = 0; i < 26; i++)
            if (tr[0].son[i]) q.push(tr[0].son[i]);
          while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; i++) {
              if (tr[u].son[i]) {
                tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];
                q.push(tr[u].son[i]);
              } else
                tr[u].son[i] = tr[tr[u].fail].son[i];
            }
          }
        }
        ```
    
    === "Python"
        ```python
        def build():
            for i in range(0, 26):
                if tr[0][i] != 0:
                    q.append(tr[0][i])
            while q:
                u = q.pop(0)
                for i in range(0, 26):
                    if tr[u][i] != 0:
                        fail[tr[u][i]] = tr[fail[u]][i]
                        q.append(tr[u][i])
                    else:
                        tr[u][i] = tr[fail[u]][i]
        ```

### Explanation

The `build` function pushes nodes into the queue in BFS order and computes their fail pointers one by one. Here the root of the trie is $0$, and we push the root's children into the queue one by one. If we pushed the root itself, then in the first BFS step the fail pointers of the root's children would be set to themselves. That is why we push the root's children instead of the root.

Then BFS starts. Each time, take the node $u$ at the front of the queue ($\operatorname{fail}(u)$ was already computed earlier in the BFS), and go over the alphabet (here $0 \sim 25$, standing for $\mathtt{a} \sim \mathtt{z}$, that is, each child of $u$):

1.  If $\operatorname{trans}(u, c)$ exists, set the fail pointer of $\operatorname{trans}(u, c)$ to $\operatorname{trans}(\operatorname{fail}(u), c)$. By the description above, we should use a `while` loop that keeps following fail pointers, checks whether a node for character $c$ exists, and then assigns it. But a special trick here simplifies that code; it is explained below;
2.  Otherwise, let $\operatorname{trans}(u, c)$ point to the state $\operatorname{trans}(\operatorname{fail}(u), c)$.

The trick is that the code in the `else` branch changes the structure of the trie: a missing trie state is linked to the matching state of the failure pointer. In the original trie, each node represents a string $S$ that is a prefix of some pattern. After the structure is changed, many transitions are added, but the string each node (state) represents stays the same.

$\operatorname{trans}(S, c)$ means appending a character $c$ to $S$ to get another state $S'$. If $S'$ exists, some pattern has $S'$ as a prefix. Otherwise, we let $\operatorname{trans}(S, c)$ point to $\operatorname{trans}(\operatorname{fail}(S), c)$. Since the string of $\operatorname{fail}(S)$ is a suffix of $S$, the string of $\operatorname{trans}(\operatorname{fail}(S), c)$ is also a suffix of $S'$.

In other words, when moving on a trie, we only move from $S$ to $S'$, which matches $S'$. But when moving on the Aho–Corasick automaton, we move from $S$ to a suffix of $S'$: we match one character $c$ and drop part of the prefix of $S$. Dropping a prefix clearly still gives a match. Also, if the text matches $S$, it clearly matches every suffix of $S$, so the fail pointer is also dropping a prefix. The fail pointers really just describe a set of suffixes of $S$.

There is another, simpler way to understand the child array `son` of a trie node. If a mismatch happens at position $u$, we jump to $\operatorname{fail}(u)$. This may force us to follow the fail array many times before reaching the next position that can match. So we use `son` to directly record the next position that can match, which keeps the time complexity under control.

Changing the trie structure here makes the matching transitions complete. It also compresses the paths of fail pointer jumps, so what would have taken many fail jumps now takes just one.

### Process

Again, GIF animations show the construction:

![AC\_automation\_gif\_b\_pro3.gif](./images/ac-automaton2.gif)

1.  Blue node: the node $u$ visited by BFS.
2.  Blue edges: edges added at the current node when the automaton changes the trie structure.
3.  Black edges: edges added when the automaton changes the trie structure.
4.  Red edge: the fail pointer computed for the current node.
5.  Yellow edges: fail pointers.
6.  Gray edges: trie edges.

You can see that the many crossing black edges turn the trie into a **trie graph**. Black edges pointing to the root are left out of the figure (otherwise it would be even messier). Let us look closely at what happens when node $5$ is visited. We compute the fail pointer of $\operatorname{trans}(5, \mathtt{s})=6$:

![AC\_automation\_b\_7.png](./images/ac-automaton2.png)

The original strategy is to follow fail pointers: we jump to $\operatorname{fail}(5)=10$ and find no trie edge labeled $\mathtt{s}$, so we jump to $\operatorname{fail}(10)=0$ and find $\operatorname{trie}(0, \mathtt{s})=7$, so $\operatorname{fail}(6)=7$. But with the black and blue edges, after jumping to $\operatorname{fail}(5)=10$ we can directly follow $\operatorname{trans}(10, \mathtt{s})=7$ and arrive at node $7$.

These are the two things `build` does: build the fail pointers and build the trie graph. The trie graph also plays a key role during queries.

## Multi-pattern matching

Next, let us look at the matching function `query`:

???+ note "Implementation"
    === "C++"
        ```cpp
        int query(const char t[]) {
          int u = 0, res = 0;
          for (int i = 1; t[i]; i++) {
            u = tr[u].son[t[i] - 'a'];
            for (int j = u; j && tr[j].cnt != -1; j = tr[j].fail) {
              res += tr[j].cnt, tr[j].cnt = -1;
            }
          }
          return res;
        }
        ```
    
    === "Python"
        ```python
        def query(t: str) -> int:
            u, res = 0, 0
            for c in t:
                u = tr[u][c - ord("a")]
                j = u
                while j and e[j] != -1:
                    res += e[j]
                    e[j] = -1
                    j = fail[j]
            return res
        ```

### Explanation

Here $u$ is the trie node matched so far, and `res` is the answer to return. We loop over the text, and $u$ follows the current character on the trie. Using the fail pointers, we find all matching patterns and add them to the answer. Then we set the occurrence count of each matched pattern to zero, so the same pattern is not counted twice. As analyzed above, the trie structure is really a trans function. Once this function is built, while matching we drop part of the prefix to keep the smallest necessary match, and the fail pointers point to further matching states. Here is one last figure. For the automaton above:

![AC\_automation\_b\_13.png](./images/ac-automaton3.png)

Starting from the root, we try to match $\mathtt{ushersheishis}$. Then $p$ changes as follows:

![AC\_automation\_gif\_c.gif](./images/ac-automaton3.gif)

1.  Red node: node $p$.
2.  Pink arrows: the moves of $p$ on the automaton.
3.  Blue edges: successfully matched patterns.
4.  Blue nodes: nodes (states) visited while following fail pointers.

## Efficiency optimization

For a problem, see Luogu [P5357 \[Template\] AC Automaton](https://www.luogu.com.cn/problem/P5357).

In our Aho–Corasick automaton, each match keeps following fail edges to find all matches. This is slow and will exceed the time limit on some problems.

So how do we optimize it? First, we need a property of fail pointers: in an Aho–Corasick automaton, if we keep only the fail edges, the remaining graph is always a tree.

This is clear: fail pointers never form a cycle, and each one points to a shallower node, which proves it.

So matching on the Aho–Corasick automaton becomes a problem of summing along paths in the fail tree, and we only need to optimize that part.

Here are two approaches.

### Topological sort optimization

Notice that most of the time is wasted on following fail pointers every time. If we record the values first and sum them all at the end, it becomes faster.

So we do one topological sort on the fail tree (an in-tree, with edges pointing toward the root), and get the number of occurrences of all patterns at once.

The `build` function adds in-degree counting on top of the original version, to prepare for the topological sort.

???+ note "Build"
    ```cpp
    void build() {
      queue<int> q;
      for (int i = 0; i < 26; i++)
        if (tr[0].son[i]) q.push(tr[0].son[i]);
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
          if (tr[u].son[i]) {
            tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];
            tr[tr[tr[u].fail].son[i]].du++;  // count in-degree
            q.push(tr[u].son[i]);
          } else
            tr[u].son[i] = tr[tr[u].fail].son[i];
        }
      }
    }
    ```

Then during a query we only mark `ans` on the nodes we reach, and compute the answers with a topological sort at the end.

???+ note "Query"
    ```cpp
    void query(const char t[]) {
      int u = 0;
      for (int i = 1; t[i]; i++) {
        u = tr[u].son[t[i] - 'a'];
        tr[u].ans++;
      }
    }
    
    void topu() {
      queue<int> q;
      for (int i = 0; i <= tot; i++)
        if (tr[i].du == 0) q.push(i);
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        ans[tr[u].idx] = tr[u].ans;
        int v = tr[u].fail;
        tr[v].ans += tr[u].ans;
        if (!--tr[v].du) q.push(v);
      }
    }
    ```

Finally, the main function:

???+ note "Main function"
    ```cpp
    int main() {
      // do_something();
      AC::build();
      scanf("%s", s + 1);
      AC::query(s);
      AC::topu();
      for (int i = 1; i <= n; i++) printf("%d\n", AC::ans[idx[i]]);
      // do_another_thing();
    }
    ```

??? note "Reference code with topological sort optimization for the template problem [Luogu P5357 \[Template\] AC Automaton](https://www.luogu.com.cn/problem/P5357)"
    ```cpp
    --8<-- "docs/string/code/ac-automaton/ac-automaton_topu.cpp"
    ```

### DFS optimization

This is close to the topological sort idea, but we use DFS instead. The two methods are essentially the same: both compute subtree sums on the fail tree.

See template 3 in the summary for the full code.

## DP on the Aho–Corasick automaton

This part uses [P2292 \[HNOI2004\] L Language](https://www.luogu.com.cn/problem/P2292) as the example problem.

A naive idea comes easily: build the Aho–Corasick automaton, do transitions over the substrings along all fail pointers, and take the maximum as the answer.

The main code is below. If you are not familiar with the type definitions in it, look at the full code at the end first:

???+ note "Main code of the query"
    ```cpp
    int query(const char t[]) {
      int u = 0, len = strlen(t + 1);
      for (int i = 1; i <= len; i++) dp[i] = 0;
      for (int i = 1; i <= len; i++) {
        u = tr[u].son[t[i] - 'a'];
        for (int j = u; j; j = tr[j].fail) {
          if (tr[j].idx && (dp[i - tr[j].depth] || i - tr[j].depth == 0)) {
            dp[i] = dp[i - tr[j].depth] + tr[j].depth;
          }
        }
      }
      int ans = 0;
      for (int i = 1; i <= len; i++) ans = std::max(ans, dp[i]);
      return ans;
    }
    ```

But this idea is not linear (it follows the fail pointers of every node), and it exceeds the time limit on the second subtask. So we need to optimize.

Look at a special property of the problem: every word has length at most $20$. This suggests a bitmask optimization.

The current bottleneck is following fail pointers. If we can make this step $O(1)$, the whole problem can be solved in strictly linear time.

We can record the possible substring lengths among the last $20$ letters, pack them into a bitmask, and store it in each node.

Then `build` can be written like this:

???+ note "Building fail pointers"
    ```cpp
    void build() {
      queue<int> q;
      for (int i = 0; i < 26; i++)
        if (tr[0].son[i]) {
          q.push(tr[0].son[i]);
          tr[tr[0].son[i]].depth = 1;
        }
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        int v = tr[u].fail;
        // state updates happen here
        tr[u].stat = tr[v].stat;
        if (tr[u].idx) tr[u].stat |= 1 << tr[u].depth;
        for (int i = 0; i < 26; i++) {
          if (tr[u].son[i]) {
            tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];
            tr[tr[u].son[i]].depth = tr[u].depth + 1;  // record the depth
            q.push(tr[u].son[i]);
          } else
            tr[u].son[i] = tr[tr[u].fail].son[i];
        }
      }
    }
    ```

Then the query no longer needs the loop that follows fail pointers, and the code becomes:

???+ note "Query"
    ```cpp
    int query(const char t[]) {
      int u = 0, mx = 0;
      unsigned st = 1;
      for (int i = 1; t[i]; i++) {
        u = tr[u].son[t[i] - 'a'];
        st <<= 1;  // moved down one step, so every length grows by 1
        if (tr[u].stat & st) st |= 1, mx = i;
      }
      return mx;
    }
    ```

`tr[u].stat` stores the set of lengths along the whole fail chain starting at node $u$ (the lengths are less than $32$, so this fits). `st` stores the set of lengths for the query string so far, limited to the last $32$ positions (the bitmask overflows naturally).

If the result of `&` is not $0$, the two length sets intersect, and we have found a match.

??? note "Full code for [P2292 \[HNOI2004\] L Language](https://www.luogu.com.cn/problem/P2292)"
    ```cpp
    --8<-- "docs/string/code/ac-automaton/ac_automaton_luoguP2292.cpp"
    ```

## Summary

Time complexity: let $|s_i|$ be the length of each pattern, $|S|$ the length of the text, and $|\Sigma|$ the alphabet size (a constant, usually $26$). If the trie graph is built, the time complexity is $O(\sum|s_i|+n|\Sigma|+|S|)$, where $n$ is the number of nodes in the automaton and can be as large as $O(\sum|s_i|)$. If the trie graph is not built, and empty children are skipped while building fail pointers, the time complexity is $O(\sum|s_i|+|S|)$.

??? note "Reference code for the template problem [Luogu P3808 AC Automaton (Easy Version)](https://www.luogu.com.cn/problem/P3808)"
    ```cpp
    --8<-- "docs/string/code/ac-automaton/ac-automaton_1.cpp"
    ```

??? note "Reference code for the template problem [Luogu P3796 AC Automaton (Easy Version II)](https://www.luogu.com.cn/problem/P3796)"
    ```cpp
    --8<-- "docs/string/code/ac-automaton/ac-automaton_2.cpp"
    ```

??? note "Reference code with DFS optimization for the template problem [Luogu P5357 \[Template\] AC Automaton](https://www.luogu.com.cn/problem/P5357)"
    ```cpp
    --8<-- "docs/string/code/ac-automaton/ac-automaton_3.cpp"
    ```
