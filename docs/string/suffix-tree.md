A suffix tree is a data structure that stores all suffixes of a string.

## Notation

Let $S$ be the string we build the suffix tree for, with length $n$ and alphabet $\Sigma$.

Let $S[i]$ denote the $i$-th character of $S$, where $1 \le i \le n$.

Let $S [l, r]$ denote the string made of the $l$-th through $r$-th characters of $S$; it is called a substring of $S$.

Let $S [i, n]$ be the suffix of $S$ starting at $i$, and $S [1, i]$ be the prefix of $S$ ending at $i$.

## Definition

The **suffix trie** of a string $S$ is the trie obtained by inserting all suffixes of S into a trie. In the suffix trie, the string of a node x is the string formed by the characters on the path from the root to x. Nodes in the suffix trie whose string is some
suffix of $S$ are called suffix nodes.

The suffix trie has a nice property: its non-root nodes accept exactly all distinct non-empty substrings of $S$. But building a suffix trie takes $O(n^2)$ time and space, which is often too much, so we introduce the suffix tree.

Call a node of the suffix trie a key node if it has more than one child or it is a suffix node. Keep only the key nodes and compress each chain of non-key nodes into a single edge; the resulting compressed trie is the **suffix tree**. If instead we call a node a key node only if it has more than one child or it is a leaf, then the compressed trie that keeps only these key nodes is the **implicit suffix tree**. Clearly, the implicit suffix tree is a further compressed version of the suffix tree.

In the suffix tree and the implicit suffix tree, each edge corresponds to a string. Each non-root node $x$ corresponds to a set of strings: take the string on the path from the root to $x$'s parent $fa_x$, then append any non-empty prefix of the string on the edge from $fa_x$ to $x$. We call this $str_x$. Also, in the implicit suffix tree, a suffix that does not correspond to any node is called an **implicit suffix**.

The figure below shows, from left to right, the suffix trie, the suffix tree and the implicit suffix tree of the string $\texttt{cabab}$.

![suffix-tree\_cabab1.png](./images/suffix-tree1.png)

Consider inserting the suffixes of $S$ into the suffix trie one by one. From the second insertion on, each insertion adds at most one node with more than one child and one suffix node. So the suffix tree has at most $2n$ nodes, which is very good.

## Building the suffix tree

### An algorithm that supports adding characters at the front

The parent tree of the SAM built on the reversed string is exactly the suffix tree of the string. So we just add the characters of the reversed string to a SAM one by one.

???+ note "Reference implementation"
    ```cpp
    struct SuffixAutomaton {
      int tot, lst;
      int siz[N << 1];
      int buc[N], id[N << 1];
    
      struct Node {
        int len, link;
        int ch[26];
      } st[N << 1];
    
      SuffixAutomaton() : tot(1), lst(1) {}
    
      void extend(int ch) {
        int cur = ++tot, p = lst;
        lst = cur;
        siz[cur] = 1, st[cur].len = st[p].len + 1;
        for (; p && !st[p].ch[ch]; p = st[p].link) st[p].ch[ch] = cur;
        if (!p)
          st[cur].link = 1;
        else {
          int q = st[p].ch[ch];
          if (st[q].len == st[p].len + 1)
            st[cur].link = q;
          else {
            int pp = ++tot;
            st[pp] = st[q];
            st[pp].len = st[p].len + 1;
            st[cur].link = st[q].link = pp;
            for (; p && st[p].ch[ch] == q; p = st[p].link) st[p].ch[ch] = pp;
          }
        }
      }
    } SAM;
    ```

### An algorithm that supports adding characters at the end

Ukkonen's algorithm is an incremental construction algorithm. We insert the characters of $S$ into the tree one at a time, and after each insertion we correctly maintain the current suffix tree.

#### The naive algorithm

First, let's look at a fairly brute-force way to build it. We use the string $\texttt {abbbc}$ to show the process.

Start with a root node, called node $0$. For each edge we keep an interval $[l,r]$, meaning the string on this edge is $S[l,r]$. We also keep $m$, the number of characters inserted so far, initially $0$.

First insert the character $\texttt a$: add an edge from node $0$ labeled $[1,\infty]$, pointing to a new node. Here $\infty$ is a very large value, which you can think of as the end of the string. This way, when new characters are inserted, this edge automatically includes them.

![suffix-tree\_a.webp](./images/suffix-tree2.webp)

Next we insert the character $\texttt b$. Again we add an edge from $0$, labeled $[2,\infty⁡]$. Notice that the meaning of the earlier edge $[1,\infty]$ changes automatically: as the end of the string moves, the string it represents changes from $\texttt a$ to $\texttt {ab}$. This is correct, because all earlier suffixes already appear in the tree as leaves, and we only need to append the current character to the end of every leaf.

![suffix-tree\_ab.webp](./images/suffix-tree3.webp)

Next we insert another $\texttt b$. But $\texttt b$ is a substring of the string inserted so far, so the tree already contains $\texttt b$. In this case we do nothing, and record $k$ such that $S[k,m]$ is the current longest implicit suffix.

![suffix-tree\_abb.webp](./images/suffix-tree4.webp)

Next we insert one more $\texttt b$. Since the previous $\texttt b$ was not inserted, now $k=3$, meaning the suffix to insert is $\texttt {bb}$. We search for $\texttt {bb}$ from the root and find that it is also already in the tree. So again, we do nothing.

![suffix-tree\_abbb.webp](./images/suffix-tree5.webp)

Notice that we ignore the suffixes after $k$. This is because if $S[k,m]$ is an implicit suffix, then $S[l,m]$ is also an implicit suffix for every $l>k$. Since $S[k,m]$ is an implicit suffix, there is a character $c$ such that $S[k, m] + c$ is a substring of $S$. So $S [ l, m] + c$ is also a substring of $S$, and by the definition of the implicit suffix tree, $S[ l, m]$ does not appear as a leaf either.

Next we insert $\texttt c$. Now $k=3$, so we search down from the root for $\texttt {bbc}$ and find that it is not in the tree. We need to add an outgoing edge $[5,\infty]$ from the node representing $\texttt {bb}$. But this node does not actually exist; it lies in the middle of an edge. So we split that edge, create a new node, and add the new outgoing edge from the created node. The insertion succeeds, so we set $k\to k+1$, since $S[k,m]$ is no longer an implicit suffix.

![suffix-tree\_abbbc1.webp](./images/suffix-tree6.webp)

Since $k$ has changed, we repeat this process until an implicit suffix appears again, or $k>m$ (in this example, the latter).

![suffix-tree\_abbbc2.webp](./images/suffix-tree7.webp)

The construction is done.

Each brute-force search and insertion from the root costs $O(n)$ in the worst case, so the total complexity is $O(n^2)$.

#### Suffix links

The naive algorithm is slow mainly because every extend has to search from the root for the insertion position of the longest implicit suffix. So we remember this position. We use a pair $(now,rem)$ to describe the current longest implicitly contained suffix $S[k,m]$: starting at node $now$, take the outgoing edge that begins with $S[m-rem+1]$ and walk a length of $rem$; the position reached represents a unique string. When inserting a new character, we only need to search from the position described by $now$ and $rem$.

Now we only need to update $(now,rem)$ when $k\to k + 1$. If $now=0$, we just set $rem \to rem-1$, because the next suffix to insert is one shorter than the one just inserted. Otherwise, let the substring of $str_{now}$ be $S[l,r]$; we need to find a node $now'$ corresponding to $S[l+1,r]$ and set $now\to now'$.

First, a lemma: for any node $x$ in the implicit suffix tree that is neither a leaf nor the root, there is another non-leaf node $y$ in the tree such that $str_y$ is the substring of $str_x$ with its first character removed.

Proof. Let $s$ be the string obtained by removing the first character of $str_x$. By the definition of the implicit suffix tree, there are two different characters $c_1,c_2$ such that both $str_x + c1$ and $str_x + c_2$ are substrings of $S$. So $s + c_1$ and $s + c_2$ are also substrings of $S$, which means $s$ also corresponds to a branching key node in the suffix trie, i.e., there is a $y$ in the implicit suffix trie with $str_y=s$. This completes the proof.

By this lemma, we define $\operatorname{Link}(x)=y$, called the **suffix link** of x. So $now'=\operatorname{Link}(now)$ always exists. Now we just need to compute $\operatorname{Link}$ for every node of the implicit suffix tree that is neither the root nor a leaf.

#### Ukkonen's algorithm

The overall process of Ukkonen's algorithm is as follows.

To build the implicit suffix tree, we add the characters of $S$ from front to back. Suppose the root is $0$, and we have already built the implicit suffix tree of $S[1, m]$ with its suffix links. The longest implicit suffix of $S [1, m]$ is $S [k, m]$, at position $(now, rem)$ in the tree. Let $S [m + 1] = x$; now we need to add the character $x$. Every suffix of $S [1, m]$ needs $x$ appended to its end. Since every explicit suffix corresponds to some leaf whose parent edge has right endpoint $\infty$, they need no work. So we only have to consider how appending x to the implicit suffixes changes the shape of the tree. First consider $S [k, m]$. There are two cases:

1.  There is already a transition by $x$ at position $(now, rem)$. Then the shape of the suffix tree does not change. Since $S [k, m+1]$ already appears in the suffix tree, $S [ l, m + 1]$ also appears in it for every $l > k$. We just set $rem\to rem + 1$ and make no other changes.
2.  There is no transition by $x$ at $(now, rem)$. If $(now, rem)$ is exactly a node of the tree, add a new outgoing edge $x$ to this node; otherwise split at this position, add a new node there, and add the outgoing edge $x$ to the new node. Now, for $l > k$, we do not know how $S [ l, m]$ will affect the shape of the suffix tree, so we must go on to consider $S [k + 1, m]$. To find the position of $S [k + 1, m]$ in the suffix tree: if $now$ is not $0$, use the suffix link and set $now = \operatorname{Link}(now)$; otherwise set $rem\to rem − 1$. Finally set $k\to k + 1$ and repeat this process.

Each step takes only constant time, and the algorithm stops after all characters are inserted, so the time complexity is $O(n)$.

Ukkonen's algorithm only builds the implicit suffix tree of $S$, and the implicit suffix tree may be less powerful than the suffix tree for some problems. When needed, append a character that never appears in $S$ to its end; then all suffixes of S correspond one-to-one with the leaves of the tree.

???+ note "Reference implementation"
    ```cpp
    struct SuffixTree {
      int ch[M + 5][RNG + 1], st[M + 5], len[M + 5], link[M + 5];
      int s[N + 5];
      int now{1}, rem{0}, n{0}, tot{1};
    
      SuffixTree() { len[0] = inf; }
    
      int new_node(int s, int le) {
        ++tot;
        st[tot] = s;
        len[tot] = le;
        return tot;
      }
    
      void extend(int x) {
        s[++n] = x;
        ++rem;
        for (int lst{1}; rem;) {
          while (rem > len[ch[now][s[n - rem + 1]]])
            rem -= len[now = ch[now][s[n - rem + 1]]];
          int &v{ch[now][s[n - rem + 1]]}, c{s[st[v] + rem - 1]};
          if (!v || x == c) {
            lst = link[lst] = now;
            if (!v)
              v = new_node(n, inf);
            else
              break;
          } else {
            int u{new_node(st[v], rem - 1)};
            ch[u][c] = v;
            ch[u][x] = new_node(n, inf);
            st[v] += rem - 1;
            len[v] -= rem - 1;
            lst = link[lst] = v = u;
          }
          if (now == 1)
            --rem;
          else
            now = link[now];
        }
      }
    } Tree;
    ```

## Applications

The path from any node of the suffix tree to the root is a non-empty substring of $S$, which is useful for many string problems.

The DFS order of the suffix tree is the suffix array. A subtree of the suffix tree corresponds to a range of the suffix array. The longest common prefix of two suffixes is the LCA of their leaves in the suffix tree. So the result about the height array of the suffix array can be understood as: the LCA of several nodes in a tree equals the LCA of the nodes with the smallest and largest DFS order.

## Example problems

### [Luogu P3804 [Template] Suffix Automaton (SAM)](https://www.luogu.com.cn/problem/P3804)

Problem:

You are given a string $S$ of lowercase letters.

Among all substrings of $S$ that occur more than once, find the maximum value of (number of occurrences) times (length of the substring).

??? note "Solution"
    Build the implicit suffix tree with a terminator character inserted. Every path from the root in the tree forms a substring. The number of occurrences of an explicit suffix is the number of leaves in the subtree of its node. Implicit suffixes can be ignored: the occurrence count of an implicit suffix equals that of the explicit suffix at the first node below it, and that explicit suffix is always longer. So traverse the whole tree, computing the number of leaves in each node's subtree and the length of the path from each node to the root. If the leaf count is $>1$, update the answer. The complexity is $O(|S||\Sigma|)$.

??? note "Reference code"
    ```cpp
    --8<-- "docs/string/code/suffix-tree/suffix-tree_1.cpp"
    ```

### [CF235C Cyclical Quest](https://codeforces.com/problemset/problem/235/C)

Problem: given a main string $S$ of lowercase letters and $n$ query strings, for each query string $x_i$, find the total number of occurrences in the main string of all its cyclic rotations.

??? note "Solution"
    Build the implicit suffix tree with a terminator character inserted.
    
    Enumerate which rotation we are at, and record how long a prefix we can find in the tree.
    
    Repeat a process similar to Ukkonen's algorithm, keeping the current matched position $(now,rem)$. Each time, try to insert the next character; if it succeeds, keep going, otherwise break out of the loop.
    
    If at some point the current rotation is fully matched, and this rotation has not appeared before, update the answer.
    
    Then, when moving to the next rotation, we need to delete the first character of the currently matched substring: this is exactly setting $now \to \operatorname{Link}(now)$. Of course, if $now=1$, we just set $rem\to rem-1$.
    
    The complexity is $O(|S||\Sigma|+\sum|x_i|)$.

??? note "Reference code"
    ```cpp
    --8<-- "docs/string/code/suffix-tree/suffix-tree_2.cpp"
    ```

## References

1.  Dai Chenxin, "Construction of Suffix Trees", 2021 China National Training Team paper
2.  [Cool Suffix Tree Magic - EternalAlexander's blog](https://www.luogu.com.cn/blog/EternalAlexander/xuan-ku-hou-zhui-shu-mo-shu)
