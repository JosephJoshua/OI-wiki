author: Backl1ght, Tiphereth-A, Enter-tainer, Ir1d, ksyx, leoleoasd, Xeonacid, aaron20100919

## Introduction

Under certain conditions, sqrt decomposition with a Fenwick tree in each block can do some of the things that a tree-in-tree can do. Compared with a tree-in-tree, the code for sqrt decomposition plus Fenwick trees is shorter and easier to write.

## A simple example

A simple example is counting the points inside a rectangular region of a 2D plane.

???+ note "Rectangle query"
    Given $n$ points $(x_i, y_i)$ in a 2D plane, where $1 \le i \le n, 1 \le x_i, y_i \le n, 1 \le n \le 10^5$, support the following operations:
    
    1.  Given $a, b, c, d$, count the points inside the rectangle with top-left corner $(a, b)$ and bottom-right corner $c, d$.
    2.  Given $x, y$, change the y-coordinate of the point with x-coordinate $x$ to $y$.
    
    The problem is **forced online**, and it is guaranteed that $x_i \ne x_j(1 \le i, j \le n, i \ne j)$.

For operation 1, we can use inclusion–exclusion on the rectangle to turn it into 4 two-dimensional dominance (2D partial order) queries. Since the problem is forced online, offline algorithms such as CDQ divide and conquer cannot be used. So a tree-in-tree comes to mind, for example a Fenwick tree of Treaps. That does solve the problem, but the code is too long and not very easy to write.

Note that the problem also guarantees $x_i \ne x_j(1 \le i, j \le n, i \ne j)$. In this case we can use sqrt decomposition with Fenwick trees.

### Initialization

First, each $x$ corresponds to only one $y$, so we can store this mapping in an array. For example, let $Y_i$ be the y-coordinate of the point whose x-coordinate is $i$.

Then split the x-coordinates into blocks of size $\sqrt n$. Build a value-indexed Fenwick tree for each block. Let $T_i$ be the Fenwick tree for block $i$, where $T_{i, j}$ is the number of points in block $i$ whose y-coordinate lies in $(j - lowbit(j), j]$.

### Query

For operation 1, turn it into 4 two-dimensional dominance queries. Now we only need to solve: given $a, b$, count the points with $1 \le x_i \le a, 1\le y_i \le b$.

Now the range of x-coordinates to query is $[1, a]$. The rightmost part of the query range may not be a full block, so we scan that part by brute force, check whether $Y_i \le b$, and count the points there that satisfy the condition.

Now only the full blocks are left. Scan the earlier blocks by brute force, query each block's Fenwick tree for the number of values less than $b$, and add it to the answer.

Is that it? Not quite. Notice that handling the full blocks is really a prefix-sum query over $T$. If we also use the Fenwick tree trick on $T$ when updating, queries become even faster.

### Update

The plain approach is to find the block that contains point $x$, do two point updates on the value-indexed Fenwick tree (one subtract and one add), then set $Y_x$ to $y$.

With the optimization above, we also run a Fenwick tree update over $T$. Each update still consists of two point updates on value-indexed Fenwick trees, one subtract and one add.

With small changes to these steps, we can do more: subtract only, and it deletes a point; add only, and it inserts a point. But keep in mind that each $x$ can correspond to only one $y$.

### Space complexity

There are $\sqrt n$ blocks, and each block has a Fenwick tree using $O(n)$ space, so the space complexity is $O(n \sqrt n)$.

### Time complexity

For a query, scanning the partial block takes $O(\sqrt n)$. Then we do a Fenwick tree query over $T$, and each $T_i$ we visit also does a Fenwick tree query, which takes $O(\log (\sqrt n) \log n)$. So a query takes $O (\sqrt n + \log (\sqrt n) \log n)$ time.

An update is the same as a query, with complexity $O (\sqrt n + \log (\sqrt n) \log n)$.

## Example problem 1

???+ note "[Intersection of Permutations](https://codeforces.com/problemset/problem/1093/E)"
    Given two permutations $a$ and $b$, support the following two operations:
    
    1.  Given $l_a, r_a, l_b, r_b$, count the elements that appear both in $a[l_a ... r_a]$ and in $b[l_b ... r_b]$.
    2.  Given $x, y$, do $swap(b_x, b_y)$.
    
    The sequence length $n$ satisfies $2 \le n \le 2 \cdot 10^5$, and the number of operations $q$ satisfies $1 \le q \le 2 \cdot 10^5$.

For each value $i$, let $x_i$ be its index in permutation $b$ and $y_i$ its index in permutation $a$. Then operation 1 becomes counting the points in a rectangle, and operation 2 can be seen as two updates. Since these are permutations, each $x$ corresponds to exactly one $y$, so this problem can be solved with sqrt decomposition plus Fenwick trees.

??? note "Reference code (sqrt decomposition + Fenwick tree - 1s)"
    ```cpp
    #include <cmath>
    #include <cstdio>
    using namespace std;
    constexpr int N = 2e5 + 5;
    constexpr int M = 447 + 5;  // sqrt(N) + 5
    
    int n, m, pa[N], pb[N];
    
    int nn, block_size, block_cnt, block_id[N], L[N], R[N], T[M][N];
    
    void build(int n) {
      nn = n;
      block_size = sqrt(nn);
      block_cnt = nn / block_size;
      for (int i = 1; i <= block_cnt; ++i) {
        L[i] = R[i - 1] + 1;
        R[i] = i * block_size;
      }
      if (R[block_cnt] < nn) {
        ++block_cnt;
        L[block_cnt] = R[block_cnt - 1] + 1;
        R[block_cnt] = nn;
      }
      for (int j = 1; j <= block_cnt; ++j)
        for (int i = L[j]; i <= R[j]; ++i) block_id[i] = j;
    }
    
    int lb(int x) { return x & -x; }
    
    void add(int p, int v, int d) {
      for (int i = block_id[p]; i <= block_cnt; i += lb(i))
        for (int j = v; j <= nn; j += lb(j)) T[i][j] += d;
    }
    
    int getsum(int p, int v) {
      if (!p) return 0;
      int res = 0;
      int id = block_id[p];
      for (int i = L[id]; i <= p; ++i)
        if (pb[i] <= v) ++res;
      for (int i = id - 1; i; i -= lb(i))
        for (int j = v; j; j -= lb(j)) res += T[i][j];
      return res;
    }
    
    void update(int x, int y) {
      add(x, pb[x], -1);
      add(y, pb[y], -1);
      swap(pb[x], pb[y]);
      add(x, pb[x], 1);
      add(y, pb[y], 1);
    }
    
    int query(int la, int ra, int lb, int rb) {
      int res = getsum(rb, ra) - getsum(rb, la - 1) - getsum(lb - 1, ra) +
                getsum(lb - 1, la - 1);
      return res;
    }
    
    int main() {
      scanf("%d %d", &n, &m);
      int v;
      for (int i = 1; i <= n; ++i) scanf("%d", &v), pa[v] = i;
      for (int i = 1; i <= n; ++i) scanf("%d", &v), pb[i] = pa[v];
    
      build(n);
      for (int i = 1; i <= n; ++i) add(i, pb[i], 1);
    
      int op, la, lb, ra, rb, x, y;
      for (int i = 1; i <= m; ++i) {
        scanf("%d", &op);
        if (op == 1) {
          scanf("%d %d %d %d", &la, &ra, &lb, &rb);
          printf("%d\n", query(la, ra, lb, rb));
        } else if (op == 2) {
          scanf("%d %d", &x, &y);
          update(x, y);
        }
      }
      return 0;
    }
    ```

??? note "Reference code (Fenwick tree of Treaps - TLE)"
    ```cpp
    #include <cstdio>
    #include <random>
    using namespace std;
    constexpr int N = 2e5 + 5;
    mt19937 rng(random_device{}());
    
    int n, m, pa[N], pb[N];
    
    // Treap
    struct Treap {
      struct node {
        node *l, *r;
        int sz, rnd, v;
    
        node(int _v) : l(NULL), r(NULL), sz(1), rnd(rng()), v(_v) {}
      };
    
      int get_size(node*& p) { return p ? p->sz : 0; }
    
      void push_up(node*& p) {
        if (!p) return;
        p->sz = get_size(p->l) + get_size(p->r) + 1;
      }
    
      node* root;
    
      node* merge(node* a, node* b) {
        if (!a) return b;
        if (!b) return a;
        if (a->rnd < b->rnd) {
          a->r = merge(a->r, b);
          push_up(a);
          return a;
        } else {
          b->l = merge(a, b->l);
          push_up(b);
          return b;
        }
      }
    
      void split_val(node* p, const int& k, node*& a, node*& b) {
        if (!p)
          a = b = NULL;
        else {
          if (p->v <= k) {
            a = p;
            split_val(p->r, k, a->r, b);
            push_up(a);
          } else {
            b = p;
            split_val(p->l, k, a, b->l);
            push_up(b);
          }
        }
      }
    
      void split_size(node* p, int k, node*& a, node*& b) {
        if (!p)
          a = b = NULL;
        else {
          if (get_size(p->l) <= k) {
            a = p;
            split_size(p->r, k - get_size(p->l), a->r, b);
            push_up(a);
          } else {
            b = p;
            split_size(p->l, k, a, b->l);
            push_up(b);
          }
        }
      }
    
      void ins(int val) {
        node *a, *b;
        split_val(root, val, a, b);
        a = merge(a, new node(val));
        root = merge(a, b);
      }
    
      void del(int val) {
        node *a, *b, *c, *d;
        split_val(root, val, a, b);
        split_val(a, val - 1, c, d);
        delete d;
        root = merge(c, b);
      }
    
      int qry(int val) {
        node *a, *b;
        split_val(root, val, a, b);
        int res = get_size(a);
        root = merge(a, b);
        return res;
      }
    
      int qry(int l, int r) { return qry(r) - qry(l - 1); }
    };
    
    // Fenwick Tree
    Treap T[N];
    
    int lb(int x) { return x & -x; }
    
    void ins(int x, int v) {
      for (; x <= n; x += lb(x)) T[x].ins(v);
    }
    
    void del(int x, int v) {
      for (; x <= n; x += lb(x)) T[x].del(v);
    }
    
    int qry(int x, int mi, int ma) {
      int res = 0;
      for (; x; x -= lb(x)) res += T[x].qry(mi, ma);
      return res;
    }
    
    int main() {
      scanf("%d %d", &n, &m);
      int v;
      for (int i = 1; i <= n; ++i) scanf("%d", &v), pa[v] = i;
      for (int i = 1; i <= n; ++i) scanf("%d", &v), pb[i] = pa[v];
      for (int i = 1; i <= n; ++i) ins(i, pb[i]);
    
      int op, la, lb, ra, rb, x, y;
      for (int i = 1; i <= m; ++i) {
        scanf("%d", &op);
        if (op == 1) {
          scanf("%d %d %d %d", &la, &ra, &lb, &rb);
          printf("%d\n", qry(rb, la, ra) - qry(lb - 1, la, ra));
        } else if (op == 2) {
          scanf("%d %d", &x, &y);
          del(x, pb[x]);
          del(y, pb[y]);
          swap(pb[x], pb[y]);
          ins(x, pb[x]);
          ins(y, pb[y]);
        }
      }
      return 0;
    }
    ```

## Example problem 2

???+ note "[Complicated Computations](https://codeforces.com/contest/1436/problem/E)"
    Given a sequence $a$, let $b$ be the array formed by the MEX values of all contiguous subarrays of $a$. Find the MEX of $b$. The MEX of a sequence is the smallest **positive integer** that does not appear in it.
    
    The length $n$ of the sequence satisfies $1 \le n \le 10^5$.

**Observation**: a sequence has MEX $mex$ if and only if it contains $1$ to $mex-1$ but does not contain $mex$.

Check in turn whether there is a contiguous subarray with MEX $1$, $2$, ..., $n+1$. If there is no contiguous subarray with MEX $i$, the answer is $i$. If all of them exist, the answer is $n + 2$.

When checking $i$, view the sequence as several segments separated by zero or more occurrences of $i$. If some segment contains $1$ to $i - 1$ but not $i$, then there is a contiguous subarray with MEX $i$.

Use an array $Y_j$ to store the position of the previous element with value $a_j$, and take $j$ as $x$, $Y_j$ as $y$, and $a_j$ as $z$. Then checking whether a segment contains $1$ to $i - 1$ becomes a 3D dominance (3D partial order) problem. Formally, checking whether segment $[l, r]$ has MEX $i$ means checking whether the number of points with $l \le j \le r, Y_j \le l - 1, a_j \le i - 1$ equals $i-1$.

If we insert the points for value $i$ only after we finish checking $i$, then $[l, r]$ only contains elements with $a_j \le i - 1$, so the 3D dominance problem above reduces to a 2D dominance problem.

??? note "Reference code (sqrt decomposition + Fenwick tree - 78ms)"
    ```cpp
    #include <cmath>
    #include <cstdio>
    #include <vector>
    using namespace std;
    constexpr int N = 1e5 + 5;
    constexpr int M = 316 + 5;  // sqrt(N) + 5
    
    // sqrt decomposition
    int nn, b[N], block_size, block_cnt, block_id[N], L[N], R[N], T[M][N];
    
    void build(int n) {
      nn = n;
      block_size = sqrt(nn);
      block_cnt = nn / block_size;
      for (int i = 1; i <= block_cnt; ++i) {
        L[i] = R[i - 1] + 1;
        R[i] = i * block_size;
      }
      if (R[block_cnt] < nn) {
        ++block_cnt;
        L[block_cnt] = R[block_cnt - 1] + 1;
        R[block_cnt] = nn;
      }
      for (int j = 1; j <= block_cnt; ++j)
        for (int i = L[j]; i <= R[j]; ++i) block_id[i] = j;
    }
    
    int lb(int x) { return x & -x; }
    
    // d = 1: add point (p, v)
    // d = -1: delete point (p, v)
    void add(int p, int v, int d) {
      for (int i = block_id[p]; i <= block_cnt; i += lb(i))
        for (int j = v; j <= nn; j += lb(j)) T[i][j] += d;
    }
    
    // count points in [1, r] with y-coordinate at most val
    int getsum(int p, int v) {
      if (!p) return 0;
      int res = 0;
      int id = block_id[p];
      for (int i = L[id]; i <= p; ++i)
        if (b[i] && b[i] <= v) ++res;
      for (int i = id - 1; i; i -= lb(i))
        for (int j = v; j; j -= lb(j)) res += T[i][j];
      return res;
    }
    
    // count points in [l, r] with y-coordinate at most val
    int query(int l, int r, int val) {
      if (l > r) return -1;
      int res = getsum(r, val) - getsum(l - 1, val);
      return res;
    }
    
    // add point (p, v)
    void update(int p, int v) {
      b[p] = v;
      add(p, v, 1);
    }
    
    int n, a[N];
    vector<int> g[N];
    
    int main() {
      scanf("%d", &n);
    
      // sentinel nodes are added to reduce case analysis
      // a Fenwick tree may loop forever when adding at 0, so everything is shifted right by one
      // a_1 and a_{n+2} are sentinel nodes
      for (int i = 2; i <= n + 1; ++i) scanf("%d", &a[i]);
      for (int i = 2; i <= n + 1; ++i) g[a[i]].push_back(i);
    
      // sqrt decomposition
      build(n + 2);
    
      int ans = n + 2, lst, ok;
      for (int i = 1; i <= n + 1; ++i) {
        g[i].push_back(n + 2);
    
        lst = 1;
        ok = 0;
        for (int pos : g[i]) {
          if (query(lst + 1, pos - 1, lst) == i - 1) {
            ok = 1;
            break;
          }
          lst = pos;
        }
    
        if (!ok) {
          ans = i;
          break;
        }
    
        lst = 1;
        g[i].pop_back();
        for (int pos : g[i]) {
          update(pos, lst);
          lst = pos;
        }
      }
      printf("%d\n", ans);
      return 0;
    }
    ```

??? note "Reference code (segment tree of Treaps - 468ms)"
    ```cpp
    #include <cstdio>
    #include <random>
    #include <vector>
    using namespace std;
    constexpr int N = 1e5 + 5;
    
    vector<int> g[N];
    int n, a[N];
    
    mt19937 rng(random_device{}());
    
    struct Treap {
      struct node {
        node *l, *r;
        unsigned rnd;
        int sz, v;
    
        node(int _v) : l(NULL), r(NULL), rnd(rng()), sz(1), v(_v) {}
      };
    
      int get_size(node*& p) { return p ? p->sz : 0; }
    
      void push_up(node*& p) {
        if (!p) return;
        p->sz = get_size(p->l) + get_size(p->r) + 1;
      }
    
      node* root;
    
      node* merge(node* a, node* b) {
        if (!a) return b;
        if (!b) return a;
        if (a->rnd < b->rnd) {
          a->r = merge(a->r, b);
          push_up(a);
          return a;
        } else {
          b->l = merge(a, b->l);
          push_up(b);
          return b;
        }
      }
    
      void split_val(node* p, const int& k, node*& a, node*& b) {
        if (!p)
          a = b = NULL;
        else {
          if (p->v <= k) {
            a = p;
            split_val(p->r, k, a->r, b);
            push_up(a);
          } else {
            b = p;
            split_val(p->l, k, a, b->l);
            push_up(b);
          }
        }
      }
    
      void split_size(node* p, int k, node*& a, node*& b) {
        if (!p)
          a = b = NULL;
        else {
          if (get_size(p->l) <= k) {
            a = p;
            split_size(p->r, k - get_size(p->l), a->r, b);
            push_up(a);
          } else {
            b = p;
            split_size(p->l, k, a, b->l);
            push_up(b);
          }
        }
      }
    
      void insert(int val) {
        node *a, *b;
        split_val(root, val, a, b);
        a = merge(a, new node(val));
        root = merge(a, b);
      }
    
      int query(int val) {
        node *a, *b;
        split_val(root, val, a, b);
        int res = get_size(a);
        root = merge(a, b);
        return res;
      }
    
      int qry(int l, int r) { return query(r) - query(l - 1); }
    };
    
    // Segment Tree
    Treap T[N << 2];
    
    void insert(int x, int l, int r, int p, int val) {
      T[x].insert(val);
      if (l == r) return;
      int mid = (l + r) >> 1;
      if (p <= mid)
        insert(x << 1, l, mid, p, val);
      else
        insert(x << 1 | 1, mid + 1, r, p, val);
    }
    
    int query(int x, int l, int r, int L, int R, int val) {
      if (l == L && r == R) return T[x].query(val);
      int mid = (l + r) >> 1;
      if (R <= mid) return query(x << 1, l, mid, L, R, val);
      if (L > mid) return query(x << 1 | 1, mid + 1, r, L, R, val);
      return query(x << 1, l, mid, L, mid, val) +
             query(x << 1 | 1, mid + 1, r, mid + 1, R, val);
    }
    
    int query(int l, int r, int val) {
      if (l > r) return -1;
      return query(1, 1, n, l, r, val);
    }
    
    int main() {
      scanf("%d", &n);
      for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
      for (int i = 1; i <= n; ++i) g[a[i]].push_back(i);
    
      // a_0 and a_{n+1} are sentinel nodes
      int ans = n + 2, lst, ok;
      for (int i = 1; i <= n + 1; ++i) {
        g[i].push_back(n + 1);
    
        lst = 0;
        ok = 0;
        for (int pos : g[i]) {
          if (query(lst + 1, pos - 1, lst) == i - 1) {
            ok = 1;
            break;
          }
          lst = pos;
        }
    
        if (!ok) {
          ans = i;
          break;
        }
    
        lst = 0;
        g[i].pop_back();
        for (int pos : g[i]) {
          insert(1, 1, n, pos, lst);
          lst = pos;
        }
      }
      printf("%d\n", ans);
      return 0;
    }
    ```
