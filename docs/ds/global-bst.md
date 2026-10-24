## Introduction

Prerequisites: [Heavy-light decomposition](../graph/hld.md)

Heavy-light decomposition takes $O(n\log^2 n)$ time. The familiar LCT takes $O(n\log n)$ time, but its constant factor is large, and it may even be slower than heavy-light decomposition. So is there a method that is $O(n\log n)$ and also has a relatively small constant? This is where the global balanced binary tree comes in.

A global balanced binary tree is actually a forest of binary trees, where each binary tree maintains one heavy path. But the binary trees in this forest are linked to each other: the root of each binary tree links to the parent of the top node of its heavy path, just like in an LCT. Unlike an LCT, though, the global balanced binary tree is a static tree: once built, its shape never changes.

A global balanced binary tree is a data structure for path updates/queries on a tree. It can do:

-   Update a whole path in $O(\log n)$.
-   Query a whole path in $O(\log n)$.
-   Find the lowest common ancestor, update a subtree, query a subtree, etc. in $O(\log n)$; these complexities are the same as with heavy-light decomposition.

## Main properties

1.  A global balanced binary tree consists of many binary trees linked by light edges. Each binary tree maintains one heavy path of the original tree, and its in-order traversal visits that heavy path in increasing order of depth. Each node appears in exactly one binary tree.
2.  Edges are either heavy or light. Heavy edges are the edges inside the binary trees; we maintain them like a normal binary tree, recording left and right children and the parent. A light edge points from the root of a binary tree to the parent of the top node of its heavy path. Light edges are maintained "parent-only": you can go from the child to the parent but not the other way. Note that edges in the global balanced binary tree do not correspond to edges in the original tree.
3.  Counting both heavy and light edges, the height of a global balanced binary tree is $O(\log n)$. This property is what guarantees the time complexity of the global balanced binary tree.

Below is an example of building a global balanced binary tree. The first figure is the original tree, rooted at node 1. Solid lines are heavy edges.

![global-bst-1](images/global-bst-1.svg)

The second figure is the resulting global balanced binary tree. Dashed lines are light edges, solid lines are heavy edges, and each binary tree is circled in red.

![global-bst-2](images/global-bst-2.svg)

## Building the tree

First, as in ordinary heavy-light decomposition, one DFS finds the heavy child of each node. Then, starting from the root, we find the heavy path containing the root, recursively build trees for the light children of these nodes, and connect the light edges. Next we build a binary tree for the nodes on the heavy path. We store the heavy path's nodes in an array and compute, for each node, the total subtree size of its light children plus one (that is, the size contributed by the node itself). Using these weights, we find the weighted midpoint of the heavy path, make it the root of the binary tree, recursively build the two sides, and connect the heavy edges.

The code is as follows:

???+ note "Implementation"
    ```cpp
    std::vector<int> G[N];
    int n, fa[N], son[N], sz[N];
    
    void dfsS(int u) {
      sz[u] = 1;
      for (int v : G[u]) {
        dfsS(v);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
      }
    }
    
    int b[N], bs[N], l[N], r[N], f[N], ss[N];
    
    // build a binary tree on the nodes in b[bl,br), return the root of the binary tree
    int cbuild(int bl, int br) {
      int x = bl, y = br;
      while (y - x > 1) {
        int mid = (x + y) >> 1;
        if (2 * (bs[mid] - bs[bl]) <= bs[br] - bs[bl])
          x = mid;
        else
          y = mid;
      }
      // binary search for the midpoint weighted by bs
      y = b[x];
      ss[y] = br - bl;  // ss: size of the heavy subtree in the binary tree
      if (bl < x) {
        l[y] = cbuild(bl, x);
        f[l[y]] = y;
      }
      if (x + 1 < br) {
        r[y] = cbuild(x + 1, br);
        f[r[y]] = y;
      }
      return y;
    }
    
    int build(int x) {
      int y = x;
      do
        for (int v : G[y])
          if (v != son[y])
            f[build(v)] =
                y;  // recursively build and link light edges; link from the binary tree's root, not from the child
      while (y = son[y]);
      y = 0;
      do {
        b[y++] = x;                              // store the nodes of the heavy path
        bs[y] = bs[y - 1] + sz[x] - sz[son[x]];  // bs: prefix sums of (light children's size sum + 1)
      } while (x = son[x]);
      return cbuild(0, y);
    }
    ```

From the code, building takes $O(n\log n)$ time. Next we can prove that the tree height is $O(\log n)$: consider jumping from any node to the root via parents. Jumping a light edge means moving to another heavy path in the original tree, and by the properties of heavy-light decomposition we jump at most $O(\log n)$ light edges. When building a binary tree, the root is the weighted midpoint counting light children, so each jump along a heavy edge at least doubles the size (counting light children), so we jump at most $O(\log n)$ heavy edges too. So the overall tree height is $O(\log n)$.

## Queries

That covers the global balanced binary tree itself. The remaining operations, path updates and path queries, are relatively simple: start from the target node and keep jumping up to the root. Operating on all nodes of a node's heavy path with smaller depth than it is essentially the same as operating on all nodes to the left of the target node in the binary tree of that heavy path. These operations can be broken into a series of subtree operations, handled like in an ordinary binary tree, which involves maintaining subtree sums and placing subtree tags. Here we use permanent tags (tags that are never pushed down). You could also place tags with pushdown and maintain subtree sums with pushup, but that may be more complicated: normally a binary tree is processed top-down, but here we must first find the jump path and then push down from top to bottom, which may lead to a large constant factor.

The code is as follows:

???+ note "Implementation"
    ```cpp
    // a: subtree add tag
    // s: subtree sum (not counting the add tags)
    int a[N], s[N];
    
    void add(int x) {
      bool t = true;
      int z = 0;
      while (x) {
        s[x] += z;
        if (t) {
          a[x]++;
          if (r[x]) a[r[x]]--;
          z += 1 + ss[l[x]];
          s[x] -= ss[r[x]];
        }
        t = (x != l[f[x]]);
        if (t && x != r[f[x]]) z = 0;  // reset after crossing a light edge
        x = f[x];
      }
    }
    
    int query(int x) {
      int ret = 0;
      bool t = true;
      int z = 0;
      while (x) {
        if (t) {
          ret += s[x] - s[r[x]];
          ret -= 1ll * ss[r[x]] * a[r[x]];
          z += 1 + ss[l[x]];
        }
        ret += 1ll * z * a[x];
        t = (x != l[f[x]]);
        if (t && x != r[f[x]]) z = 0;  // reset after crossing a light edge
        x = f[x];
      }
      return ret;
    }
    ```

Also, subtree operations need to account for light children, so you need to additionally maintain a subtree sum and subtree tag that include light children. You can try "[P3384 [Template] Heavy-Light Decomposition](https://www.luogu.com.cn/problem/P3384)".

## Example problems

??? note "[P4751 [Template] 'Dynamic DP' & Dynamic Tree Divide and Conquer (Enhanced Version)](https://www.luogu.com.cn/problem/P4751)"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    constexpr int MAXN = 1000000;
    constexpr int MAXM = 3000000;
    constexpr int INF = 0x3FFFFFFF;
    using namespace std;
    
    struct edge {
      int to;
      edge *nxt;
    } edges[MAXN * 2 + 5];
    
    edge *ncnt = &edges[0], *Adj[MAXN + 5];
    int n, m;
    
    struct Matrix {
      int M[2][2];
    
      Matrix operator*(const Matrix &B) const {
        static Matrix ret;
        for (int i = 0; i < 2; i++)
          for (int j = 0; j < 2; j++) {
            ret.M[i][j] = -INF;
            for (int k = 0; k < 2; k++)
              ret.M[i][j] = max(ret.M[i][j], M[i][k] + B.M[k][j]);
          }
        return ret;
      }
    } matr1[MAXN + 5], matr2[MAXN + 5];  // each node maintains two matrices
    
    int root;
    int w[MAXN + 5], dep[MAXN + 5], son[MAXN + 5], siz[MAXN + 5], lsiz[MAXN + 5];
    int g[MAXN + 5][2], f[MAXN + 5][2], trfa[MAXN + 5], bstch[MAXN + 5][2];
    int stk[MAXN + 5], tp;
    bool vis[MAXN + 5];
    
    void AddEdge(int u, int v) {
      edge *p = ++ncnt;
      p->to = v;
      p->nxt = Adj[u];
      Adj[u] = p;
    
      edge *q = ++ncnt;
      q->to = u;
      q->nxt = Adj[v];
      Adj[v] = q;
    }
    
    void DFS(int u, int fa) {
      siz[u] = 1;
      for (edge *p = Adj[u]; p != NULL; p = p->nxt) {
        int v = p->to;
        if (v == fa) continue;
        dep[v] = dep[u] + 1;
        DFS(v, u);
        siz[u] += siz[v];
        if (!son[u] || siz[son[u]] < siz[v]) son[u] = v;
      }
      lsiz[u] = siz[u] - siz[son[u]];  // sum of light children's siz + 1
    }
    
    void DFS2(int u, int fa) {
      f[u][1] = w[u], f[u][0] = 0;
      g[u][1] = w[u], g[u][0] = 0;
      if (son[u]) {
        DFS2(son[u], u);
        f[u][0] += max(f[son[u]][0], f[son[u]][1]);
        f[u][1] += f[son[u]][0];
      }
      for (edge *p = Adj[u]; p != NULL; p = p->nxt) {
        int v = p->to;
        if (v == fa || v == son[u]) continue;
        DFS2(v, u);
        f[u][0] += max(f[v][0], f[v][1]);  // f[][] is the normal DP array
        f[u][1] += f[v][0];
        g[u][0] += max(f[v][0], f[v][1]);  // g[][] only counts the node itself and its light children
        g[u][1] += f[v][0];
      }
    }
    
    void PushUp(int u) {
      matr2[u] = matr1[u];  // matr1 is the single node plus light children's info; matr2 is the range info
      if (bstch[u][0]) matr2[u] = matr2[bstch[u][0]] * matr2[u];
      // mind the direction of the transition; with a different matrix product definition, the direction may differ
      if (bstch[u][1]) matr2[u] = matr2[u] * matr2[bstch[u][1]];
    }
    
    int getmx2(int u) { return max(matr2[u].M[0][0], matr2[u].M[0][1]); }
    
    int getmx1(int u) { return max(getmx2(u), matr2[u].M[1][0]); }
    
    int SBuild(int l, int r) {
      if (l > r) return 0;
      int tot = 0;
      for (int i = l; i <= r; i++) tot += lsiz[stk[i]];
      for (int i = l, sumn = lsiz[stk[l]]; i <= r; i++, sumn += lsiz[stk[i]])
        if (sumn * 2 >= tot)  // this is the centroid
        {
          int lch = SBuild(l, i - 1), rch = SBuild(i + 1, r);
          bstch[stk[i]][0] = lch;
          bstch[stk[i]][1] = rch;
          trfa[lch] = trfa[rch] = stk[i];
          PushUp(stk[i]);  // gather the range information
          return stk[i];
        }
      return 0;
    }
    
    int Build(int u) {
      for (int pos = u; pos; pos = son[pos]) vis[pos] = true;
      for (int pos = u; pos; pos = son[pos])
        for (edge *p = Adj[pos]; p != NULL; p = p->nxt)
          if (!vis[p->to])  // it is a light child
          {
            int v = p->to, ret = Build(v);
            trfa[ret] = pos;  // hook up the light child's treefa[]
          }
      tp = 0;
      for (int pos = u; pos; pos = son[pos]) stk[++tp] = pos;  // extract the heavy path
      int ret = SBuild(1, tp);  // run a separate SBuild on the heavy path (I guess it means Special Build?)
      return ret;               // return the root of the current heavy path's binary tree
    }
    
    void Modify(int u, int val) {
      matr1[u].M[1][0] += val - w[u];
      w[u] = val;
      for (int pos = u; pos; pos = trfa[pos])
        if (trfa[pos] && bstch[trfa[pos]][0] != pos && bstch[trfa[pos]][1] != pos) {
          matr1[trfa[pos]].M[0][0] -= getmx1(pos);
          matr1[trfa[pos]].M[0][1] = matr1[trfa[pos]].M[0][0];
          matr1[trfa[pos]].M[1][0] -= getmx2(pos);
          PushUp(pos);
          matr1[trfa[pos]].M[0][0] += getmx1(pos);
          matr1[trfa[pos]].M[0][1] = matr1[trfa[pos]].M[0][0];
          matr1[trfa[pos]].M[1][0] += getmx2(pos);
        } else
          PushUp(pos);
    }
    
    int read() {
      int ret = 0, f = 1;
      char c = 0;
      while (c < '0' || c > '9') {
        c = getchar();
        if (c == '-') f = -f;
      }
      ret = 10 * ret + c - '0';
      while (true) {
        c = getchar();
        if (c < '0' || c > '9') break;
        ret = 10 * ret + c - '0';
      }
      return ret * f;
    }
    
    void print(int x) {
      if (x == 0) return;
      print(x / 10);
      putchar(x % 10 + '0');
    }
    
    int main() {
      scanf("%d %d", &n, &m);
      for (int i = 1; i <= n; i++) w[i] = read();
      int u, v;
      for (int i = 1; i < n; i++) {
        u = read(), v = read();
        AddEdge(u, v);
      }
      DFS(1, -1);
      // find heavy children
      DFS2(1, -1);
      // compute the initial DP values; this could also be done inside Build(), but this way matches the HLD style
      for (int i = 1; i <= n; i++) {
        matr1[i].M[0][0] = matr1[i].M[0][1] = g[i][0];
        matr1[i].M[1][0] = g[i][1], matr1[i].M[1][1] = -INF;  // initialize the matrices
      }
      root = Build(1);  // root is the centroid of the heavy path containing the root node
      int lastans = 0;
      for (int i = 1; i <= m; i++) {
        u = read(), v = read();
        u ^= lastans;  // forced online
        Modify(u, v);
        lastans = getmx1(root);  // read the answer directly
        if (lastans == 0)
          putchar('0');
        else
          print(lastans);
        putchar('\n');
      }
      return 0;
    }
    ```

## References

[P4211 \[LNOI2014\] LCA | Global balanced binary tree](https://www.luogu.com.cn/blog/nederland/globalbst)
