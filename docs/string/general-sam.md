## Prerequisites

The general suffix automaton builds on the following topics:

-   [Trie](./trie.md)
-   [Suffix automaton](./sam.md)

Make sure you are very familiar with both topics before reading this article. In particular, you should have a good understanding of **suffix links** in the **suffix automaton**.

## Introduction

### Origin

The general suffix automaton is a structure proposed by Liu Yanyi in his 2015 national training team paper "Extending the Suffix Automaton to Tries". The idea is to build a suffix automaton directly on a trie.

> Most string problems that can be solved with a suffix automaton can be extended to tries. — Liu Yanyi

### Conventions

See [string conventions](./basic.md).

There are $k$ strings, namely $S_1, S_2, S_3 \dots S_k$.

The root of both the trie and the general suffix automaton is node $0$.

### Overview

The suffix automaton (SAM) is a powerful tool for substring problems on a single string.

The general suffix automaton combines the suffix automaton with a trie to solve substring problems on multiple strings.

## Common fake general suffix automata

1.  Join the strings together with special separator symbols, then build a SAM on the result.
2.  For each string, build it into the same SAM again, resetting the `last` pointer to zero before each string.

Methods 1 and 2 are easy to implement, and on contest problems they are usually just as correct as a general suffix automaton. That is why many people online use them. For example, the last application in the suffix automaton article uses method 1 [(link to the article)](./sam.md).

However, the time complexity of both method 1 and method 2 is risky.

## Building the general suffix automaton

According to the original paper, you should first build a trie on the strings, and then build the general suffix automaton on top of the trie.

### Using the trie

First build a trie from all the strings. This is not hard: if you already know the prerequisites, you can build it quickly. To keep the code in this article consistent, here is one possible trie implementation.

??? note "Implementation"
    ```cpp
    constexpr int MAXN = 2000000;
    constexpr int CHAR_NUM = 30;
    
    struct Trie {
      int next[MAXN][CHAR_NUM];  // transitions
      int tot;                   // total number of nodes: [0, tot)
    
      void init() { tot = 1; }
    
      int insertTrie(int cur, int c) {
        if (next[cur][c]) return next[cur][c];
        return next[cur][c] = tot++;
      }
    
      void insert(const string &s) {
        int root = 0;
        for (auto ch : s) root = insertTrie(root, ch - 'a');
      }
    };
    ```

This gives us a trie built on the `next` array.

### Building the suffix automaton

If we treat this tree directly as a suffix automaton, we get the following facts:

-   For node `i`, `len[i]` equals its depth in the trie.
-   If we topologically sort the trie, we get a sequence in which `len` is non-decreasing. BFS gives the same result.

Building a suffix automaton can be seen as repeatedly inserting values of `len` that strictly increase by exactly $1$ each time. So we can take the topological order of the trie as a queue and insert the nodes into the suffix automaton in that order.

In an ordinary suffix automaton, the `len` of the previous node is fixed: it is the `len` of the `last` node. In the general suffix automaton, however, the insertion queue is only non-decreasing, not strictly increasing. So for each value, its `last` must be known and fixed; on the trie, it is the node's parent.

Since the trie already forms something close to a suffix automaton, we only need to process the trie's structure a bit to turn it into a general suffix automaton. We update every node of the trie in the queue order given above, and in the end we get the general suffix automaton.

The update for each node is a slightly modified version of the insert operation of a SAM.

One thing to watch out for during insertion: since nodes are inserted in non-decreasing order of `len`, when copying data after a `clone`, you must not copy data whose `len` is smaller than the current `len`.

### Process

Following the logic above, the whole construction can be described as these steps:

1.  Insert all strings into the trie.
2.  Run BFS from the root of the trie, recording the order and the parent of each node.
3.  Go through the BFS order and build each node on the original trie. Be careful not to operate on data whose `len` is smaller than the current `len`.

### Proof that the number of operations is linear

Since we only process the sequence produced by BFS, every node in the trie is visited exactly once.

In the worst case, consider the trie with as many nodes as possible, that is, no two strings share a common prefix. Then the number of nodes is $\sum_{i=1}^{k}|S_i|$, the total length of all strings.

The complexity of the update operation in a suffix automaton has already been proven in [Suffix automaton](./sam.md).

So the worst-case complexity is linear.

The average complexity of a fake general suffix automaton is usually the same as the worst-case complexity of a real general suffix automaton. With a large number of strings, a fake general suffix automaton is much less efficient than a standard one.

### Implementation

A few necessary changes to the insert function give us the function we need.

??? note "Reference code"
    ```cpp
    struct GSA {
      int len[MAXN];             // node length
      int link[MAXN];            // suffix link
      int next[MAXN][CHAR_NUM];  // transitions
      int tot;                   // total number of nodes: [0, tot)
    
      int insertSAM(int last, int c) {
        int cur = next[last][c];
        len[cur] = len[last] + 1;
        int p = link[last];
        while (p != -1) {
          if (!next[p][c])
            next[p][c] = cur;
          else
            break;
          p = link[p];
        }
        if (p == -1) {
          link[cur] = 0;
          return cur;
        }
        int q = next[p][c];
        if (len[p] + 1 == len[q]) {
          link[cur] = q;
          return cur;
        }
        int clone = tot++;
        for (int i = 0; i < CHAR_NUM; ++i)
          next[clone][i] = len[next[q][i]] != 0 ? next[q][i] : 0;
        len[clone] = len[p] + 1;
        while (p != -1 && next[p][c] == q) {
          next[p][c] = clone;
          p = link[p];
        }
        link[clone] = link[q];
        link[cur] = clone;
        link[q] = clone;
        return cur;
      }
    
      void build() {
        queue<pair<int, int>> q;
        for (int i = 0; i < CHAR_NUM; ++i)
          if (next[0][i]) q.push({i, 0});
        while (!q.empty()) {
          auto item = q.front();
          q.pop();
          auto last = insertSAM(item.second, item.first);
          for (int i = 0; i < CHAR_NUM; ++i)
            if (next[last][i]) q.push({i, last});
        }
      }
    }
    ```

-   In the order produced by BFS, the parent node keeps changing, so we do not need to store a `last` pointer.
-   In the insert operation, `int cur = next[last][c];` differs from `int cur = tot++;` in a normal suffix automaton. The node we insert already exists in the tree structure, so we just fetch it.
-   When copying data after `clone`, there is the check `next[clone][i] = len[next[q][i]] != 0 ? next[q][i] : 0;`. This differs from the direct assignment `next[clone][i] = next[q][i];` in a normal suffix automaton. It avoids copying nodes whose `len` is larger than the current node's, because a node's `len` in the array is set if and only if that node has been visited by BFS and inserted into the suffix automaton.

## Properties

1.  The general suffix automaton has the same structure as a suffix automaton, and almost all properties of a suffix automaton also hold for it ([properties of the suffix automaton](./sam.md)).
2.  Once the general suffix automaton is built, the trie structure is usually destroyed, so you usually cannot use the general suffix automaton to solve trie problems. Of course, you can also allocate twice the memory and build the suffix automaton in a separate space.

## Applications

### Number of distinct substrings over all strings

From the properties of the suffix automaton, the number of substrings that end at node $i$ is $len[i] - len[link[i]]$.

So we can get the answer by summing over all nodes.

Example problem: [\[Template\] General Suffix Automaton (General SAM)](https://www.luogu.com.cn/problem/P6139)

??? note "Reference code"
    ```cpp
    --8<-- "docs/string/code/general-sam/general-sam_1.cpp"
    ```

### Longest common substring of multiple strings

For each node, create an array `flag` of length $k$. (For this problem it can be just a marker array. If you need the number of occurrences of the substring, change it into a counting array.)

When inserting strings into the trie, mark every node in the array slot of the current string.

Then go through the nodes in decreasing order of `len`, and merge the current node's `flag` into other nodes through suffix links.

Go through all nodes and find the node with the largest `len` whose `flag` is nonzero for all `k` strings. The $len$ of that node is the answer.

Example problem: [SPOJ Longest Common Substring II](https://www.spoj.com/problems/LCS2/)

??? note "Reference code"
    ```cpp
    --8<-- "docs/string/code/general-sam/general-sam_2.cpp"
    ```
