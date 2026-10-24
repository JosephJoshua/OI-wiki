author: StudyingFather, Backl1ght, countercurrent-time, Ir1d, greyqz, MicDZ, ouuan, Linky, yinqf

## Mo's algorithm on trees via the bracket sequence

Ordinary Mo's algorithm only handles linear problems, so we have to flatten the tree into a sequence.

We can compute the bracket sequence of the tree, split it into blocks, and run Mo's algorithm on the bracket sequence.

How exactly does it work?

### How it works

We use DFS to build the bracket sequence of the tree (append $x$ to the sequence when entering node $x$, and append $x$ again when leaving node $x$; the sequence has total length $2N$).

Let $st_x$ be the time we enter $x$ and $ed_x$ the time we leave $x$.

By the properties of the bracket sequence, for a tree path $u \to v$ (assume $st_u \le st_v$):

-   If $\text{LCA}(u, v) = u$, the nodes on the path appear exactly once in the range $[st_u, st_v]$; nodes not on the path appear 0 or 2 times.
-   If $\text{LCA}(u, v) \neq u$, the nodes on the path other than $\text{LCA}(u, v)$ appear exactly once in the range $[ed_u, st_v]$; nodes not on the path appear 0 or 2 times. Note that $\text{LCA}(u, v)$ needs special handling: it appears 0 times.

So when running Mo's algorithm, whether a node we meet is being pushed or popped, what really happens is that its number of occurrences in the current range changes. We only need to track how many times each node $x$ appears: nodes appearing 0 or 2 times are not in the path set we are maintaining, and nodes appearing once are. So when the Mo pointers sit at $[st_u, st_v]$, we have almost exactly the node set of the tree path $u \to v$.

In practice, we can keep the number of occurrences of each node $x$ modulo 2, which tells us whether node $x$ is present. Then when moving a pointer, whether adding or removing, the update just flips the presence state of node $x$.

Note that for queries with $\text{LCA} \neq u$, after the Mo pointers are in place, we must temporarily add $\text{LCA}(u, v)$ to the set by hand (flip its state), compute and record the answer to the query, and then remove $\text{LCA}(u, v)$ from the set again (flip it back), so that it does not interfere with later pointer moves.

### Example problem

???+ note "Example problem [WC2013 Candy Park](https://uoj.ac/problem/58)"
    Statement: you are given a tree whose $i$-th vertex has color $c_i$. Each query gives a path $u_i$,$v_i$; compute, over this path,
    
    $\sum_{c}val_c\sum_{i=1}^{cnt_c}w_i$
    
    where $val$ is the value of the color, $cnt$ is the number of times the color appears, and $w$ is the value of the color's $i$-th occurrence

#### How it works

First turn the tree into a sequence. Each time we add/remove a vertex, its contribution to the answer can be found in $O(1)$ time, namely $val_c\times w_{cnt_{c+1}}$

But this also scans the subtree of the start vertex and adds extra contributions. What can we do?

During the scan, the vertices in the subtree of the start vertex are always scanned twice, so their contribution is 0.

So we can keep a $vis$ array, and each time we scan vertex x, XOR $vis_x$ with 1.

If $vis_x=0$, the contribution of this vertex is not counted.

So we can solve it with Mo's algorithm on trees.

For updates, just add a time dimension, giving Mo's algorithm on trees with updates.

Then, since the covered range may not contain the LCA, we remove the extra contribution in that case, and we are done.

#### Implementation

??? note "Reference code"
    ```cpp
    #include <algorithm>
    #include <cmath>
    #include <cstdio>
    using namespace std;
    
    constexpr int MAXN = 200010;
    
    int f[MAXN], g[MAXN], id[MAXN], head[MAXN], cnt, last[MAXN], dep[MAXN],
        fa[MAXN][22], v[MAXN], w[MAXN];
    int block, index, n, m, q;
    int pos[MAXN], col[MAXN], app[MAXN];
    bool vis[MAXN];
    long long ans[MAXN], cur;
    
    struct edge {
      int to, nxt;
    } e[MAXN];
    
    int cnt1 = 0, cnt2 = 0;  // Timestamps
    
    struct query {
      int l, r, t, id;
    
      bool operator<(const query &b) const {
        return (pos[l] < pos[b.l]) || (pos[l] == pos[b.l] && pos[r] < pos[b.r]) ||
               (pos[l] == pos[b.l] && pos[r] == pos[b.r] && t < b.t);
      }
    } a[MAXN], b[MAXN];
    
    void addedge(int x, int y) {
      e[++cnt] = edge{y, head[x]};
      head[x] = cnt;
    }
    
    void dfs(int x) {
      id[f[x] = ++index] = x;
      for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].to != fa[x][0]) {
          fa[e[i].to][0] = x;
          dep[e[i].to] = dep[x] + 1;
          dfs(e[i].to);
        }
      }
      id[g[x] = ++index] = x;  // Bracket sequence
    }
    
    int lca(int x, int y) {
      if (dep[x] < dep[y]) swap(x, y);
      if (dep[x] != dep[y]) {  // Climb to the same depth
        int dis = dep[x] - dep[y];
        for (int i = 20; i >= 0; i--)
          if (dis >= (1 << i)) dis -= 1 << i, x = fa[x][i];
      }
      if (x == y) return x;
      for (int i = 20; i >= 0; i--) {
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
      }
      return fa[x][0];
    }
    
    void add(int x) {
      if (vis[x])
        cur -= (long long)v[col[x]] * w[app[col[x]]--];
      else
        cur += (long long)v[col[x]] * w[++app[col[x]]];
      vis[x] ^= 1;
    }
    
    // Move along the time dimension
    void modify(int x, int t) {
      if (vis[x]) {
        add(x);
        col[x] = t;
        add(x);
      } else
        col[x] = t;
    }
    
    int main() {
      scanf("%d%d%d", &n, &m, &q);
      for (int i = 1; i <= m; i++) scanf("%d", &v[i]);
      for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
      for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        addedge(x, y);
        addedge(y, x);
      }
      for (int i = 1; i <= n; i++) {
        scanf("%d", &last[i]);
        col[i] = last[i];
      }
      dfs(1);
      for (int j = 1; j <= 20; j++)
        for (int i = 1; i <= n; i++)
          fa[i][j] = fa[fa[i][j - 1]][j - 1];  // Precompute ancestors
      int block = pow(index, 2.0 / 3);
      for (int i = 1; i <= index; i++) {
        pos[i] = (i - 1) / block;
      }
      while (q--) {
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 0) {
          b[++cnt2].l = x;
          b[cnt2].r = last[x];
          last[x] = b[cnt2].t = y;
        } else {
          if (f[x] > f[y]) swap(x, y);
          a[++cnt1] = query{lca(x, y) == x ? f[x] : g[x], f[y], cnt2, cnt1};
        }
      }
      sort(a + 1, a + cnt1 + 1);
      int L, R, T;  // Pointer positions
      L = R = 0;
      T = 1;
      for (int i = 1; i <= cnt1; i++) {
        while (T <= a[i].t) {
          modify(b[T].l, b[T].t);
          T++;
        }
        while (T > a[i].t) {
          modify(b[T].l, b[T].r);
          T--;
        }
        while (L > a[i].l) {
          L--;
          add(id[L]);
        }
        while (L < a[i].l) {
          add(id[L]);
          L++;
        }
        while (R > a[i].r) {
          add(id[R]);
          R--;
        }
        while (R < a[i].r) {
          R++;
          add(id[R]);
        }
        int x = id[L], y = id[R];
        int llca = lca(x, y);
        if (x != llca && y != llca) {
          add(llca);
          ans[a[i].id] = cur;
          add(llca);
        } else
          ans[a[i].id] = cur;
      }
      for (int i = 1; i <= cnt1; i++) {
        printf("%lld\n", ans[i]);
      }
      return 0;
    }
    ```

## True Mo's algorithm on trees

The Mo's algorithm on trees above only turns the tree into a chain. What follows is true Mo's algorithm on trees.

Since problems involving Mo's algorithm are all template problems, we won't explain the implementation much

### Sorting the queries

First, we know that Mo's algorithm is based on sqrt decomposition, so we need a way to split a tree into blocks that guarantees the time complexity.

Conditions:

-   The distance between nodes in the same block must not exceed the given block size
-   Each block must have neither too many nor too few nodes
-   Every node must belong to a block
-   Blocks with adjacent indices must not be too far apart

With these conditions in mind, look at the problem [SCOI2005 Royal Federation](https://loj.ac/problem/2152).

Building on that problem, we only need to also guarantee the last condition to solve the blocking problem.

??? note "Idea"
    Let lim be the desired block size. First, run a dfs over the whole tree; when the size of the subtrees exceeds lim, put them into one block. It is easy to see that some vertices may be left over at the root, so put them into the last block.

Method: use a stack to keep track of the current node as a parent while visiting its children. When the distance from the top of the stack to the parent exceeds the desired block size, pop these elements as one block. The last remaining part becomes a block on its own.

Final sorting method: if the first timestamp is greater than the second, swap them. Sort with the block of the first as the first key and the second timestamp as the second key.

### Moving the pointers

#### How it works

It is natural to mark the vertices counted in the answer, move the pointers straight toward their targets, and flip the vertices along the path.

But this has a problem. If both pointers start at x, x is clearly marked. When both pointers move to the same child (among many other cases), x should not be marked, but in fact it is, because each pointer flipped it once and they cancelled out.

How do we fix this?

There is an obvious property: these vertices must be some LCA, because only at an LCA can a vertex be undone twice so that the undo fails.

So each time we leave the LCA unmarked; when we need the answer to a query, we mark the LCA, then undo it.

#### Implementation

```cpp
// Flip all nodes on the path except the LCA
void move(int x, int y) {
  if (dp[x] < dp[y]) swap(x, y);
  while (dp[x] > dp[y]) update(x), x = fa[x];
  while (x != y) update(x), update(y), x = fa[x], y = fa[y];
  // x!=y ensures the LCA is not flipped
}
```

To find the LCA, we can use heavy-light decomposition. Then we can put the blocking step into the first dfs of the HLD, and the timestamps can just be the dfs order from the second dfs.

```cpp
int bl[100002], bls = 0;  // Block of each node, number of blocks
unsigned step;            // Block size
int fa[100002], dp[100002], hs[100002] = {0}, sz[100002] = {0};
// Parent, depth, heavy child, size
stack<int> sta;

void dfs1(int x) {
  sz[x] = 1;
  unsigned ss = sta.size();
  for (int i = head[x]; i; i = nxt[i])
    if (ver[i] != fa[x]) {
      fa[ver[i]] = x;
      dp[ver[i]] = dp[x] + 1;
      dfs1(ver[i]);
      sz[x] += sz[ver[i]];
      if (sz[ver[i]] > sz[hs[x]]) hs[x] = ver[i];
      if (sta.size() - ss >= step) {
        bls++;
        while (sta.size() != ss) bl[sta.top()] = bls, sta.pop();
      }
    }
  sta.push(x);
}

// main
if (!sta.empty()) {
  bls++;  // This line is optional
  while (!sta.empty()) bl[sta.top()] = bls, sta.pop();
}
```

### Time complexity

Now the key part: this determines the choice of block size.

Let the block size be $unit$:

-   For the x pointer: since the distance between nodes in each block is about $unit$, the x pointer moves $unit^2$ times per block ($unit\times dis_{\max}$), $n\times unit$ times in total ($unit^2 \times (\frac{n}{unit})$);
-   For the y pointer: it moves at most $O(n)$ times per block, $\frac{n^2}{unit}$ times in total ($n \times (\frac{n}{unit})$).

The sum is roughly minimized around the square root (since block sizes in Mo's algorithm on trees are not fixed, you don't have to follow this strictly).

### Example problem: WC2013 Candy Park

Since there is an extra time dimension, a block size of around $n^{0.6}$ is about right.

??? note "Reference code"
    ```cpp
    #include <algorithm>
    #include <cmath>
    #include <cstdio>
    #include <stack>
    using namespace std;
    
    int gi() {
      int x, c, op = 1;
      while (c = getchar(), c < '0' || c > '9')
        if (c == '-') op = -op;
      x = c ^ 48;
      while (c = getchar(), c >= '0' && c <= '9')
        x = (x << 3) + (x << 1) + (c ^ 48);
      return x * op;
    }
    
    int head[100002], nxt[200004], ver[200004], tot = 0;
    
    void add(int x, int y) {
      ver[++tot] = y, nxt[tot] = head[x], head[x] = tot;
      ver[++tot] = x, nxt[tot] = head[y], head[y] = tot;
    }
    
    int bl[100002], bls = 0;
    unsigned step;
    int fa[100002], dp[100002], hs[100002] = {0}, sz[100002] = {0}, top[100002],
                                id[100002];
    stack<int> sta;
    
    void dfs1(int x) {
      sz[x] = 1;
      unsigned ss = sta.size();
      for (int i = head[x]; i; i = nxt[i])
        if (ver[i] != fa[x]) {
          fa[ver[i]] = x, dp[ver[i]] = dp[x] + 1;
          dfs1(ver[i]);
          sz[x] += sz[ver[i]];
          if (sz[ver[i]] > sz[hs[x]]) hs[x] = ver[i];
          if (sta.size() - ss >= step) {
            bls++;
            while (sta.size() != ss) bl[sta.top()] = bls, sta.pop();
          }
        }
      sta.push(x);
    }
    
    int cnt = 0;
    
    void dfs2(int x, int hf) {
      top[x] = hf, id[x] = ++cnt;
      if (!hs[x]) return;
      dfs2(hs[x], hf);
      for (int i = head[x]; i; i = nxt[i])
        if (ver[i] != fa[x] && ver[i] != hs[x]) dfs2(ver[i], ver[i]);
    }
    
    int lca(int x, int y) {
      while (top[x] != top[y]) {
        if (dp[top[x]] < dp[top[y]]) swap(x, y);
        x = fa[top[x]];
      }
      return dp[x] < dp[y] ? x : y;
    }
    
    struct qu {
      int x, y, t, id;
    
      bool operator<(const qu a) const {
        return bl[x] == bl[a.x] ? (bl[y] == bl[a.y] ? t < a.t : bl[y] < bl[a.y])
                                : bl[x] < bl[a.x];
      }
    } q[100001];
    
    int qs = 0;
    
    struct ch {
      int x, y, b;
    } upd[100001];
    
    int ups = 0;
    long long ans[100001];
    int b[100001] = {0};
    int a[100001];
    long long w[100001];
    long long v[100001];
    long long now = 0;
    bool vis[100001] = {false};
    
    void back(int t) {
      if (vis[upd[t].x]) {
        now -= w[b[upd[t].y]--] * v[upd[t].y];
        now += w[++b[upd[t].b]] * v[upd[t].b];
      }
      a[upd[t].x] = upd[t].b;
    }
    
    void change(int t) {
      if (vis[upd[t].x]) {
        now -= w[b[upd[t].b]--] * v[upd[t].b];
        now += w[++b[upd[t].y]] * v[upd[t].y];
      }
      a[upd[t].x] = upd[t].y;
    }
    
    void update(int x) {
      if (vis[x])
        now -= w[b[a[x]]--] * v[a[x]];
      else
        now += w[++b[a[x]]] * v[a[x]];
      vis[x] ^= 1;
    }
    
    void move(int x, int y) {
      if (dp[x] < dp[y]) swap(x, y);
      while (dp[x] > dp[y]) update(x), x = fa[x];
      while (x != y) update(x), update(y), x = fa[x], y = fa[y];
    }
    
    int main() {
      int n = gi(), m = gi(), k = gi();
      step = (int)pow(n, 0.6);
      for (int i = 1; i <= m; i++) v[i] = gi();
      for (int i = 1; i <= n; i++) w[i] = gi();
      for (int i = 1; i < n; i++) add(gi(), gi());
      for (int i = 1; i <= n; i++) a[i] = gi();
      for (int i = 1; i <= k; i++)
        if (gi())
          q[++qs].x = gi(), q[qs].y = gi(), q[qs].t = ups, q[qs].id = qs;
        else
          upd[++ups].x = gi(), upd[ups].y = gi();
      for (int i = 1; i <= ups; i++) upd[i].b = a[upd[i].x], a[upd[i].x] = upd[i].y;
      for (int i = ups; i; i--) back(i);
      fa[1] = 1;
      dfs1(1), dfs2(1, 1);
      if (!sta.empty()) {
        bls++;
        while (!sta.empty()) bl[sta.top()] = bls, sta.pop();
      }
      for (int i = 1; i <= n; i++)
        if (id[q[i].x] > id[q[i].y]) swap(q[i].x, q[i].y);
      sort(q + 1, q + qs + 1);
      int x = 1, y = 1, t = 0;
      for (int i = 1; i <= qs; i++) {
        if (x != q[i].x) move(x, q[i].x), x = q[i].x;
        if (y != q[i].y) move(y, q[i].y), y = q[i].y;
        int f = lca(x, y);
        update(f);
        while (t < q[i].t) change(++t);
        while (t > q[i].t) back(t--);
        ans[q[i].id] = now;
        update(f);
      }
      for (int i = 1; i <= qs; i++) printf("%lld\n", ans[i]);
      return 0;
    }
    ```
