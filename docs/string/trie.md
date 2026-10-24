## Definition

A trie (also called a prefix tree or dictionary tree) is, as the Chinese name "dictionary tree" suggests, a tree that works like a dictionary.

## Introduction

Here is a picture first:

![trie1](./images/trie1.png)

You can see that this trie uses edges to represent letters, and the path from the root to any node represents a string. For example, $1\to4\to 8\to 12$ represents the string `caa`.

The structure of a trie is easy to understand. We use $\delta(u,c)$ to denote the next node that node $u$ points to by character $c$, or in other words, the node of the string formed by appending character $c$ to the string of node $u$. (The range of $c$ depends on the alphabet size and is not necessarily $0\sim 26$.)

Sometimes we need to mark which strings were inserted into the trie. Just put a mark on the node representing each string when its insertion finishes.

## Implementation

Here is a template wrapped in a struct:

=== "C++"
    ```cpp
    struct trie {
      int nex[100000][26], cnt;
      bool exist[100000];  // whether a string ending at this node exists
    
      void insert(char *s, int l) {  // insert a string
        int p = 0;
        for (int i = 0; i < l; i++) {
          int c = s[i] - 'a';
          if (!nex[p][c]) nex[p][c] = ++cnt;  // if it does not exist, add a node
          p = nex[p][c];
        }
        exist[p] = true;
      }
    
      bool find(char *s, int l) {  // look up a string
        int p = 0;
        for (int i = 0; i < l; i++) {
          int c = s[i] - 'a';
          if (!nex[p][c]) return 0;
          p = nex[p][c];
        }
        return exist[p];
      }
    };
    ```

=== "Python"
    ```python
    class trie:
        def __init__(self):
            self.nex = [[0 for i in range(26)] for j in range(100000)]
            self.cnt = 0
            self.exist = [False] * 100000  # whether a string ending at this node exists
    
        def insert(self, s):  # insert a string
            p = 0
            for i in s:
                c = ord(i) - ord("a")
                if not self.nex[p][c]:
                    self.cnt += 1
                    self.nex[p][c] = self.cnt  # if it does not exist, add a node
                p = self.nex[p][c]
            self.exist[p] = True
    
        def find(self, s):  # look up a string
            p = 0
            for i in s:
                c = ord(i) - ord("a")
                if not self.nex[p][c]:
                    return False
                p = self.nex[p][c]
            return self.exist[p]
    ```

=== "Java"
    ```java
    public class Trie {
        int[][] tree = new int[10000][26];
        int cnt = 0;
        boolean[] end = new boolean[10000];
        
        public void insert(String word) {
            int p = 0;
            char[] chars = word.toCharArray();
            for (int i = 0; i < chars.length; i++) {
                int c = chars[i] - 'a';
                if (tree[p][c] == 0) {
                    tree[p][c] = ++cnt;
                }
                p = tree[p][c];
            }
            end[p] = true;
        }
        
        public boolean find(String word) {
            int p = 0;
            char[] chars = word.toCharArray();
            for (int i = 0; i < chars.length; i++) {
                int c = chars[i] - 'a';
                if (tree[p][c] == 0) {
                    return false;
                }
                p = tree[p][c];
            }
            return end[p];
        }
    }
    ```

## Applications

### Looking up strings

The most basic use of a trie: checking whether a string appears in the "dictionary".

???+ note "[And So His Wrong Roll Call Began](https://www.luogu.com.cn/problem/P2580)"
    You are given $n$ names, and then there are $m$ roll calls. For each one, you must answer one of "the name does not exist", "this name is called for the first time", or "this name has already been called".
    
    $1\le n\le 10^4$, $1\le m\le 10^5$, and every string has length at most $50$.
    
    ??? note "Solution"
        Build a trie of all the names. Then query the trie to check whether a string exists and whether it has already been called; mark it as called the first time it is called.
    
    ??? note "Reference code"
        ```cpp
        --8<-- "docs/string/code/trie/trie_1.cpp"
        ```

### Aho–Corasick automaton

A trie is part of the [Aho–Corasick automaton](./ac-automaton.md).

### Maximum XOR

Treat the binary representation of a number as a string, and you can build a trie over the alphabet $\{0,1\}$.

???+ note "[BZOJ1954 Longest XOR Path](https://hydro.ac/p/bzoj-P1954)"
    You are given a tree with edge weights. Find $(u, v)$ such that the XOR sum of edge weights on the path from $u$ to $v$ is maximum, and output this maximum. Here the XOR sum means the XOR of all edge weights.
    
    There are at most $10^5$ vertices, and edge weights are in $[0,2^{31})$.
    
    ??? note "Solution"
        Pick any vertex as the root $root$. Let $T(u, v)$ be the XOR sum of edge weights on the path between $u$ and $v$. Then $T(u,v)=T(root, u)\oplus T(root,v)$, because the part above the [LCA](../graph/lca.md) is XORed twice and cancels out.
        
        So if we insert all $T(root, u)$ into a trie, then for each $T(root, u)$ we can quickly find the $T(root, v)$ whose XOR with it is the largest:
        
        Start from the root of the trie. If we can go into the subtree whose current bit differs from the current bit of $T(root, u)$, go there; otherwise we have no choice.
        
        Why this greedy is correct: if we go that way, this bit is $1$; if we don't, this bit becomes $0$. And higher bits should be made as large as possible first.
    
    ??? note "Reference code"
        ```cpp
        --8<-- "docs/string/code/trie/trie_2.cpp"
        ```

### Maintaining XOR sums

A 01-trie is a trie over the alphabet $\{0,1\}$. A 01-trie can maintain the XOR sum of a set of numbers, and supports modification (delete + reinsert) and global increment (i.e., increasing every value it stores by `1`, which is really a special kind of modification).

To maintain XOR sums, build the trie from the lowest bit of each value to the highest.

**A convention**: in this text, **above** the current node means the path from the current node to the root, and **below** the current node means the subtree of the current node.

#### Insertion & deletion

To maintain the XOR sum, we **only** need to know the **parity** of the number of `0`s and `1`s at each bit. That is, the XOR has a `1` at a bit if and only if the number of `1`s at that bit is odd. Always keep this in mind: if we only maintain the XOR sum, we only need to know the number of `1`s at each bit, not which exact numbers the trie stores.

For each node, we record the following three quantities:

-   `ch[o][0/1]` are the two children of node `o`: `ch[o][0]` means the next bit is `0`, and likewise `ch[o][1]` means the next bit is `1`.
-   `w[o]` is the number of values on the edge from node `o` to its parent (its weight). Each time a number `x` is inserted, the weight of every edge on its binary path in the trie increases by `1`.
-   `xorv[o]` is the XOR sum maintained by the subtree rooted at `o`.

The code that maintains a node is shown below.

```cpp
void maintain(int o) {
  w[o] = xorv[o] = 0;
  if (ch[o][0]) {
    w[o] += w[ch[o][0]];
    xorv[o] ^= xorv[ch[o][0]] << 1;
  }
  if (ch[o][1]) {
    w[o] += w[ch[o][1]];
    xorv[o] ^= (xorv[ch[o][1]] << 1) | (w[ch[o][1]] & 1);
  }
  // w[o] = w[o] & 1;
  // We only need the parity, not the exact value. You can also delete this line, since the code above only uses its parity.
}
```

The code for insertion and deletion is very similar.

Things to note:

-   Here `MAXH` is the depth of the trie, i.e., we force every leaf to be at distance `MAXH` from the root. For small values, we sometimes would not need to go this deep (for example, inserting `4`, which is `100` in binary, only needs the three bits `001` starting from the root), but we always insert `MAXH` bits. This makes it easy to handle carries during a global `+1`. For example, if the original number is `3` (`11`), it becomes `4` (`100`) after incrementing; if we had inserted only `2` bits when inserting `3`, this carry would be lost.

-   For insertion and deletion, we only need to change `w[]` of the leaf, and then maintain the values on the way back up.

???+ note "Implementation"
    ```cpp
    namespace trie {
    constexpr int MAXH = 21;
    int ch[_ * (MAXH + 1)][2], w[_ * (MAXH + 1)], xorv[_ * (MAXH + 1)];
    int tot = 0;
    
    int mknode() {
      ++tot;
      ch[tot][1] = ch[tot][0] = w[tot] = xorv[tot] = 0;
      return tot;
    }
    
    void maintain(int o) {
      w[o] = xorv[o] = 0;
      if (ch[o][0]) {
        w[o] += w[ch[o][0]];
        xorv[o] ^= xorv[ch[o][0]] << 1;
      }
      if (ch[o][1]) {
        w[o] += w[ch[o][1]];
        xorv[o] ^= (xorv[ch[o][1]] << 1) | (w[ch[o][1]] & 1);
      }
      w[o] = w[o] & 1;
    }
    
    void insert(int &o, int x, int dp) {
      if (!o) o = mknode();
      if (dp > MAXH) return (void)(w[o]++);
      insert(ch[o][x & 1], x >> 1, dp + 1);
      maintain(o);
    }
    
    void erase(int o, int x, int dp) {
      if (dp > 20) return (void)(w[o]--);
      erase(ch[o][x & 1], x >> 1, dp + 1);
      maintain(o);
    }
    }  // namespace trie
    ```

#### Global increment

Global increment means adding `1` to every value in the trie.

Formally, if the values stored in the trie are $V_1, V_2, V_3 \dots V_n$, then after a global increment they should become $V_1+1, V_2+1, V_3+1 \dots V_n+1$.

```cpp
void addall(int o) {
  swap(ch[o][0], ch[o][1]);
  if (ch[o][0]) addall(ch[o][0]);
  maintain(o);
}
```

##### Process

Let's think about how `+1` works in binary.

We just find the first `0` going from the lowest bit up, change it to `1`, and change all the `1`s below that position to `0`.

Here are a few examples to get a feel for it (the number in parentheses is the decimal value):

    1000(8)  + 1 = 1001(9)  ;
    10011(19) + 1 = 10100(20) ;
    11111(31) + 1 = 100000(32);
    10101(21) + 1 = 10110(22) ;
    100000000111111(16447) + 1 = 100000001000000(16448);

In the trie, this simply means swapping the left and right children, and then recursing down along the `0` edge **after the swap**.

Recall the definition of `w[o]`: `w[o]` is the number of values on the edge from node `o` to its parent (its weight).

Does this definition feel a bit odd? Storing the weights of the edges to the two children in the parent node might feel more natural. But here, since we swap the left and right children, storing the weight of the edge to the parent in the child node is clearly more convenient.

### Merging 01-tries

This means merging two 01-tries like the ones above, along with the information they maintain.

There may not be many articles about merging tries, but merging tries is very similar to merging segment trees. You can search for "segment tree merging" to learn how to merge tries.

Merging tries is actually quite simple. Imagine a function `int merge(int a, int b)` that takes the node indices of two tries at the same relative position, merges them, and returns the index of the merged node.

#### Process

How do we implement it?

There are three cases:

-   If `a` has no node at this position, the merged node is `b`.
-   If `b` has no node at this position, the merged node is `a`.
-   If both `a` and `b` exist, merge the information of `b` into `a`; the merged node is `a`. Then recursively handle the left and right children of a.

    **Hint**: if you need to merge a and b into a new tree, you can create a new node here and merge into it. The code below only merges the information of b into a.

#### Implementation

```cpp
int merge(int a, int b) {
  if (!a) return b;  // if a has no node at this position, return b
  if (!b) return a;  // if b has no node at this position, return a
  /*
    If both `a` and `b` exist,
    merge the information of `b` into `a`.
  */
  w[a] = w[a] + w[b];
  xorv[a] ^= xorv[b];
  /* Do not use maintain():
    maintain() merges the information of a's two children,
    but here we need to merge the information of nodes a and b
   */
  ch[a][0] = merge(ch[a][0], ch[b][0]);
  ch[a][1] = merge(ch[a][1], ch[b][1]);
  return a;
}
```

In fact, any trie can be merged; in other words, trie merging is not limited to 01-tries.

???+ note "[[Luogu P6018] [Ynoi2010] Fusion tree](https://www.luogu.com.cn/problem/P6018)"
    You are given a tree with $n$ nodes, each with a weight. There are $m$ operations.
    The following operations must be supported:
    
    -   Add $1$ to the weight of every node at distance $1$ from a node $x$. Here the distance between two nodes in the tree is the number of edges on the shortest path between them.
    
    -   Subtract $v$ from the weight of a node $x$.
    
    -   Query the XOR sum of the weights of all nodes at distance $1$ from a node $x$.
        For $100\%$ of the data, $1\le n \le 5\times 10^5$, $1\le m \le 5\times 10^5$, $0\le a_i \le 10^5$, $1 \le x \le n$, $opt\in\{1,2,3\}$.
        It is guaranteed that every node's weight is non-negative at all times.
    
    ??? note "Solution"
        For each node, build a trie storing the weights of its children; the trie should support global increment.
        You can put a lazy tag on each node to record how much its children's weights have increased.
    
    ??? note "Reference code"
        ```cpp
        --8<-- "docs/string/code/trie/trie_3.cpp"
        ```

???+ note "[[Luogu P6623] [Provincial Selection Joint Exam 2020 Paper A] Tree](https://www.luogu.com.cn/problem/P6623)"
    You are given a rooted tree $T$ with $n$ nodes, numbered from $1$, with node $1$ as the root. Each node has a positive integer weight $v_i$.
    Let the nodes in the subtree of node $x$ (including $x$ itself) be $c_1,c_2,\dots,c_k$. Define the value of $x$ as:  
    $val(x)=(v_{c_1}+d(c_1,x)) \oplus (v_{c_2}+d(c_2,x)) \oplus \cdots \oplus (v_{c_k}+d(c_k, x))$, where $d(x,y)$  
    is the number of edges on the unique simple path between nodes $x$ and $y$ in the tree, and $d(x,x) = 0$. $\oplus$ denotes XOR.
    Find the value of $\sum\limits_{i=1}^n val(i)$.
    
    ??? note "Solution"
        Consider the contribution of each node to all its ancestors.
        Build a trie for each node, initially storing only that node's weight. Then, from the bottom up, merge the tries of each child into it, apply a global increment, and then add up the answer.
    
    ??? note "Reference code"
        ```cpp
        constexpr int _ = 526010;
        int n;
        int V[_];
        int debug = 0;
        
        namespace trie {
        constexpr int MAXH = 21;
        int ch[_ * (MAXH + 1)][2], w[_ * (MAXH + 1)], xorv[_ * (MAXH + 1)];
        int tot = 0;
        
        int mknode() {
          ++tot;
          ch[tot][1] = ch[tot][0] = w[tot] = xorv[tot] = 0;
          return tot;
        }
        
        void maintain(int o) {
          w[o] = xorv[o] = 0;
          if (ch[o][0]) {
            w[o] += w[ch[o][0]];
            xorv[o] ^= xorv[ch[o][0]] << 1;
          }
          if (ch[o][1]) {
            w[o] += w[ch[o][1]];
            xorv[o] ^= (xorv[ch[o][1]] << 1) | (w[ch[o][1]] & 1);
          }
          w[o] = w[o] & 1;
        }
        
        void insert(int &o, int x, int dp) {
          if (!o) o = mknode();
          if (dp > MAXH) return (void)(w[o]++);
          insert(ch[o][x & 1], x >> 1, dp + 1);
          maintain(o);
        }
        
        int merge(int a, int b) {
          if (!a) return b;
          if (!b) return a;
          w[a] = w[a] + w[b];
          xorv[a] ^= xorv[b];
          ch[a][0] = merge(ch[a][0], ch[b][0]);
          ch[a][1] = merge(ch[a][1], ch[b][1]);
          return a;
        }
        
        void addall(int o) {
          swap(ch[o][0], ch[o][1]);
          if (ch[o][0]) addall(ch[o][0]);
          maintain(o);
        }
        }  // namespace trie
        
        int rt[_];
        long long Ans = 0;
        vector<int> E[_];
        
        void dfs0(int o) {
          for (int i = 0; i < E[o].size(); i++) {
            int node = E[o][i];
            dfs0(node);
            rt[o] = trie::merge(rt[o], rt[node]);
          }
          trie::addall(rt[o]);
          trie::insert(rt[o], V[o], 0);
          Ans += trie::xorv[rt[o]];
        }
        
        int main() {
          n = read();
          for (int i = 1; i <= n; i++) V[i] = read();
          for (int i = 2; i <= n; i++) E[read()].push_back(i);
          dfs0(1);
          printf("%lld", Ans);
          return 0;
        }
        ```

### Persistent trie

See [Persistent trie](../ds/persistent-trie.md).
