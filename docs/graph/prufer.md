???+ note "Note"
    This page is translated from [e-maxx Prüfer Code](https://github.com/e-maxx-eng/e-maxx-eng/blob/master/src/graph/pruefer_code.md). Note that the original numbers nodes from $0$; this page numbers them from $1$, as most people are used to.

This page introduces the Prüfer sequence (Prüfer code), a way to represent a labeled tree by a unique sequence of integers.

Using Prüfer sequences, we can prove [Cayley's formula](#cayleys-formula). We will also show how to count the ways to add edges to a graph to make it connected.

**Note**: we do not consider trees with only $1$ node.

## Prüfer sequence

### Introduction

A Prüfer sequence represents a labeled tree with $n$ nodes by $n-2$ integers in $[1,n]$. You can also think of it as a bijection between the spanning trees of a complete graph and sequences. It is commonly used in combinatorial counting problems.

Heinz Prüfer invented this sequence in 1918 to prove [Cayley's formula](#cayleys-formula).

### Building the Prüfer sequence of a tree

The Prüfer sequence is built like this: each time, pick the leaf with the smallest label, delete it, and write down the node it was connected to in the sequence. After repeating this $n-2$ times, only two nodes remain, and the algorithm ends.

Clearly, using a heap gives $O(n\log n)$ complexity.

???+ note "Implementation"
    === "C++"
        ```cpp
        // Code taken from the original article; nodes are numbered from 0
        vector<vector<int>> adj;
        
        vector<int> pruefer_code() {
          int n = adj.size();
          set<int> leafs;
          vector<int> degree(n);
          vector<bool> killed(n);
          for (int i = 0; i < n; i++) {
            degree[i] = adj[i].size();
            if (degree[i] == 1) leafs.insert(i);
          }
        
          vector<int> code(n - 2);
          for (int i = 0; i < n - 2; i++) {
            int leaf = *leafs.begin();
            leafs.erase(leafs.begin());
            killed[leaf] = true;
            int v;
            for (int u : adj[leaf])
              if (!killed[u]) v = u;
            code[i] = v;
            if (--degree[v] == 1) leafs.insert(v);
          }
          return code;
        }
        ```
    
    === "Python"
        ```python
        # Nodes are numbered from 0
        adj = [[]]
        
        
        def pruefer_code():
            n = len(adj)
            leafs = set()
            degree = [0] * n
            killed = [False] * n
            for i in range(1, n):
                degree[i] = len(adj[i])
                if degree[i] == 1:
                    leafs.intersection(i)
            code = [0] * (n - 2)
            for i in range(1, n - 2):
                leaf = leafs[0]
                leafs.pop()
                killed[leaf] = True
                for u in adj[leaf]:
                    if killed[u] == False:
                        v = u
                code[i] = v
                if degree[v] == 1:
                    degree[v] = degree[v] - 1
                    leafs.intersection(v)
            return code
        ```

For example, here is how the Prüfer sequence of a tree with 7 nodes is built:

![Prüfer](./images/prufer1.png)

The final sequence is $2,2,3,3,2$.

There is also a linear-time algorithm.

### Linear-time construction of the Prüfer sequence

The idea of the linear construction is to keep a pointer to the node we are about to delete. First note that the number of leaves never increases: when a leaf is deleted, the total number of leaves either stays the same or decreases by 1.

So consider this process: keep a pointer $p$, which initially points to the leaf with the smallest label. We also keep the degree of every node, so that when we delete a node we know whether a new leaf appears. The steps are:

1.  Delete the node that $p$ points to, and check whether a new leaf appears.
2.  If a new leaf appears, say with label $x$, compare $p$ and $x$. If $x>p$, do nothing else. Otherwise, delete $x$ right away, then check whether deleting $x$ creates a new leaf, and repeat step $2$ until no new leaf appears or the new leaf's label is $>p$.
3.  Increase the pointer $p$ until it reaches a leaf that has not been deleted.

#### Correctness

Repeating the steps above $n-2$ times builds the sequence. Now let us check that the algorithm is correct.

$p$ is the leaf with the smallest label right now. If deleting $p$ creates no new leaf, we just have to look for the next leaf. If it creates a leaf $x$:

-   If $x>p$, then $p$ will reach it anyway as it scans forward, so we do nothing.
-   If $x<p$: $p$ was the smallest label, and $x$ is even smaller, so $x$ is now the leaf with the smallest label and must be deleted first. After deleting $x$, keep checking in the same way until there is no smaller leaf.

For the complexity: each edge is visited at most once (when decreasing degrees), and the pointer passes over each node at most once, so the complexity is $O(n)$.

#### Implementation

=== "C++"
    ```cpp
    // Code taken from the original article, also numbered from 0
    vector<vector<int>> adj;
    vector<int> parent;
    
    void dfs(int v) {
      for (int u : adj[v]) {
        if (u != parent[v]) parent[u] = v, dfs(u);
      }
    }
    
    vector<int> pruefer_code() {
      int n = adj.size();
      parent.resize(n), parent[n - 1] = -1;
      dfs(n - 1);
    
      int ptr = -1;
      vector<int> degree(n);
      for (int i = 0; i < n; i++) {
        degree[i] = adj[i].size();
        if (degree[i] == 1 && ptr == -1) ptr = i;
      }
    
      vector<int> code(n - 2);
      int leaf = ptr;
      for (int i = 0; i < n - 2; i++) {
        int next = parent[leaf];
        code[i] = next;
        if (--degree[next] == 1 && next < ptr) {
          leaf = next;
        } else {
          ptr++;
          while (degree[ptr] != 1) ptr++;
          leaf = ptr;
        }
      }
      return code;
    }
    ```

=== "Python"
    ```python
    # Also numbered from 0
    adj = [[]]
    parent = [0] * n
    
    
    def dfs(v):
        for u in adj[v]:
            if u != parent[v]:
                parent[u] = v
                dfs(u)
    
    
    def pruefer_code():
        n = len(adj)
        parent[n - 1] = -1
        dfs(n - 1)
    
        ptr = -1
        degree = [0] * n
        for i in range(0, n):
            degree[i] = len(adj[i])
            if degree[i] == 1 and ptr == -1:
                ptr = i
    
        code = [0] * (n - 2)
        leaf = ptr
        for i in range(0, n - 2):
            next = parent[leaf]
            code[i] = next
            if degree[next] == 1 and next < ptr:
                degree[next] = degree[next] - 1
                leaf = next
            else:
                ptr = ptr + 1
                while degree[ptr] != 1:
                    ptr = ptr + 1
                leaf = ptr
        return code
    ```

### Properties of the Prüfer sequence

1.  After building the Prüfer sequence, two nodes of the original tree remain, and one of them is always the node with the largest label, $n$.
2.  Each node appears in the sequence exactly (its degree minus $1$) times. (Nodes that do not appear are leaves.)

### Rebuilding the tree from a Prüfer sequence

Rebuilding the tree works in a similar way. From the properties of the Prüfer sequence, we get the degree of every node in the original tree. Then we can find the leaf with the smallest label, and this node must be connected to the node given by the first number of the Prüfer sequence. Then we decrease the degrees of both nodes by one.

By now you may already see what to do. Each time, pick the node of degree $1$ with the smallest label, connect it to the current node of the Prüfer sequence, and decrease the degrees of both. At the end, two nodes of degree $1$ remain, and one of them is node $n$; connect them. Maintain this process with a heap: whenever a node's degree drops to $1$, push it into the heap. This takes $O(n\log n)$ time.

???+ note "Implementation"
    ```cpp
    // Code taken from the original article
    vector<pair<int, int>> pruefer_decode(vector<int> const& code) {
      int n = code.size() + 2;
      vector<int> degree(n, 1);
      for (int i : code) degree[i]++;
    
      set<int> leaves;
      for (int i = 0; i < n; i++)
        if (degree[i] == 1) leaves.insert(i);
    
      vector<pair<int, int>> edges;
      for (int v : code) {
        int leaf = *leaves.begin();
        leaves.erase(leaves.begin());
    
        edges.emplace_back(leaf, v);
        if (--degree[v] == 1) leaves.insert(v);
      }
      edges.emplace_back(*leaves.begin(), n - 1);
      return edges;
    }
    ```

### Rebuilding the tree in linear time

This works just like the linear construction of the Prüfer sequence. Decreasing degrees may create a new leaf; compare it with the pointer $p$, and if it is smaller, handle it first.

#### Implementation

```cpp
// Code taken from the original article
vector<pair<int, int>> pruefer_decode(vector<int> const& code) {
  int n = code.size() + 2;
  vector<int> degree(n, 1);
  for (int i : code) degree[i]++;

  int ptr = 0;
  while (degree[ptr] != 1) ptr++;
  int leaf = ptr;

  vector<pair<int, int>> edges;
  for (int v : code) {
    edges.emplace_back(leaf, v);
    if (--degree[v] == 1 && v < ptr) {
      leaf = v;
    } else {
      ptr++;
      while (degree[ptr] != 1) ptr++;
      leaf = ptr;
    }
  }
  edges.emplace_back(leaf, n - 1);
  return edges;
}
```

These processes show that Prüfer sequences give a bijection with labeled unrooted trees.

## Cayley's formula

The complete graph $K_n$ has $n^{n-2}$ spanning trees.

How do we prove this? There are many ways, but the proof with Prüfer sequences is very simple. Every integer sequence of length $n-2$ with values in $[1,n]$ corresponds, through the Prüfer bijection, to exactly one spanning tree, so the count is $n^{n-2}$.

## Number of ways to make a graph connected

Prüfer sequences may be even more powerful than you think. They can give formulas more general than [Cayley's formula](#cayleys-formula). For example, consider this problem:

> A labeled undirected graph with $n$ vertices and $m$ edges has $k$ connected components. We want to add $k-1$ edges to make the whole graph connected. Count the number of ways.

### Proof

Let $s_i$ be the number of vertices in the $i$-th connected component. We build a Prüfer sequence over the $k$ connected components. Since there are many ways to connect two components, this is not an ordinary Prüfer sequence. So let $d_i$ be the degree of the $i$-th component. Since the sum of degrees is twice the number of edges, $\sum_{i=1}^kd_i=2k-2$. Then for a given sequence $d$, the number of Prüfer sequences is

$$
\binom{k-2}{d_1-1,d_2-1,\cdots,d_k-1}=\frac{(k-2)!}{(d_1-1)!(d_2-1)!\cdots(d_k-1)!}
$$

For the $i$-th component, there are ${s_i}^{d_i}$ ways to connect it, so for a given sequence $d$, the number of ways to make the graph connected is

$$
\binom{k-2}{d_1-1,d_2-1,\cdots,d_k-1}\cdot \prod_{i=1}^k{s_i}^{d_i}
$$

Now we enumerate the sequence $d$, and the expression becomes

$$
\sum_{d_i\ge 1,\sum_{i=1}^kd_i=2k-2}\binom{k-2}{d_1-1,d_2-1,\cdots,d_k-1}\cdot \prod_{i=1}^k{s_i}^{d_i}
$$

Well, this is a very unpleasant expression. But don't panic! We have the multinomial theorem:

$$
(x_1 + \dots + x_m)^p = \sum_{\substack{c_i \ge 0 ,\  \sum_{i=1}^m c_i = p}} \binom{p}{c_1, c_2, \cdots ,c_m}\cdot \prod_{i=1}^m{x_i}^{c_i}
$$

Now substitute $e_i=d_i-1$. Clearly $\sum_{i=1}^ke_i=k-2$, so the expression becomes

$$
\sum_{e_i\ge 0,\sum_{i=1}^ke_i=k-2}\binom{k-2}{e_1,e_2,\cdots,e_k}\cdot \prod_{i=1}^k{s_i}^{e_i+1}
$$

Simplifying gives

$$
(s_1+s_2+\cdots+s_k)^{k-2}\cdot \prod_{i=1}^ks_i
$$

that is,

$$
n^{k-2}\cdot\prod_{i=1}^ks_i
$$

which is the answer.

## Exercises

-   [Luogu P6086 \[Template\] Prüfer Sequence](https://www.luogu.com.cn/problem/P6086) (template problem)
-   [Luogu P11039 \[MX-X3-T6\] \[RiOI-4\] TECHNOPOLIS 2085](https://www.luogu.com.cn/problem/P11039)
-   [UVa #10843 - Anne's game](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=20&page=show_problem&problem=1784)
-   [Timus #1069 - Prufer Code](http://acm.timus.ru/problem.aspx?space=1&num=1069)
-   [Codeforces - Clues](http://codeforces.com/contest/156/problem/D)
-   [Topcoder - TheCitiesAndRoadsDivTwo](https://archive.topcoder.com/ProblemStatement/pm/10774)
