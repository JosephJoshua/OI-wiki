## Definition

A minimum spanning tree on a directed graph (Directed Minimum Spanning Tree) is called a minimum arborescence.

The usual algorithm is the Chu–Liu algorithm (also called Edmonds' algorithm), which solves the minimum arborescence problem in $O(nm)$ time.

## Process

1.  For each vertex, pick the incoming edge with the smallest weight.
2.  If there is no cycle, the algorithm stops. Otherwise, contract the cycle and update the distances from other vertices to the cycle.

## Implementation

```cpp
bool solve() {
  ans = 0;
  int u, v, root = 0;
  for (;;) {
    f(i, 0, n) in[i] = 1e100;
    f(i, 0, m) {
      u = e[i].s;
      v = e[i].t;
      if (u != v && e[i].w < in[v]) {
        in[v] = e[i].w;
        pre[v] = u;
      }
    }
    f(i, 0, m) if (i != root && in[i] > 1e50) return 0;
    int tn = 0;
    memset(id, -1, sizeof id);
    memset(vis, -1, sizeof vis);
    in[root] = 0;
    f(i, 0, n) {
      ans += in[i];
      v = i;
      while (vis[v] != i && id[v] == -1 && v != root) {
        vis[v] = i;
        v = pre[v];
      }
      if (v != root && id[v] == -1) {
        for (int u = pre[v]; u != v; u = pre[u]) id[u] = tn;
        id[v] = tn++;
      }
    }
    if (tn == 0) break;
    f(i, 0, n) if (id[i] == -1) id[i] = tn++;
    f(i, 0, m) {
      u = e[i].s;
      v = e[i].t;
      e[i].s = id[u];
      e[i].t = id[v];
      if (e[i].s != e[i].t) e[i].w -= in[v];
    }
    n = tn;
    root = id[root];
  }
  return ans;
}
```

## Tarjan's DMST algorithm

Tarjan proposed an algorithm that solves the minimum arborescence problem in $O(m+n\log n)$ time.

The description and reference code here are based on Professor Uri Zwick's lecture notes. See the original for more details.

### Process

Tarjan's algorithm has two phases: **contraction** and **expansion**. We first describe **contraction**.

We assume the input graph is strongly connected. If it is not, add $O(n)$ edges with infinite weight to make it strongly connected.

We need a heap that stores, for each vertex, the indices of its incoming edges, the incoming edge weights, the vertex's total cost and so on. Since heaps will be merged later, we implement this with a [leftist heap](../ds/leftist-tree.md) and a [disjoint set union](../ds/dsu.md). At each step, the algorithm picks an arbitrary vertex $v$ that is not the root and has no incoming edge in the heap yet. It then adds the minimum incoming edge of $v$ to the heap. If this new edge makes the edges in the heap form a cycle, the vertices on that cycle are contracted. We call such contracted vertices **super vertices**. The process then continues. When all vertices have been contracted into a single super vertex, contraction is finished. The whole contraction phase produces a contraction tree, which we then expand.

The edges in the heap always form a path $v_0\leftarrow v_1\leftarrow \dots\leftarrow v_k$. Since the graph is strongly connected, this path always exists. Each $v_i$ may be an original single vertex or a contracted super vertex.

Initially $v_o=a$, where $a$ is any vertex of the graph. Each time we pick a minimum incoming edge $v_k\leftarrow u$. If $u$ is not one of $v_0,v_1,\dots,v_k$, we extend the path with $v_{k+1}=u$. If $u$ is one of them, say $v_i$, we have found a cycle $v_i\leftarrow\dots\leftarrow v_k\leftarrow v_i$, and we contract it into a super vertex $c$.

Put all vertices or super vertices into a queue $P$, and start from an arbitrary vertex $a$. While the queue is not empty, do the following:

1.  Take the minimum incoming edge of $a$, making sure it is not a self-loop, and find the vertex $b$ at its other end. If $b$ has not been marked yet, no cycle has formed; set $a\leftarrow b$ and keep going to look for a cycle.

2.  If $b$ has already been marked, a cycle has appeared. Increase the total vertex count by one, relabel all vertices on the cycle, merge their heaps, and update the total weight of the vertices/super vertices. Updating the weights means collecting the incoming edges of all vertices on the cycle and subtracting from them the weight of that vertex's incoming edge on the cycle.

![dmst1](./images/dmst1.png)

Take the picture as an example. After contraction, the strongly connected graph on the left becomes the contraction tree on the right. Here $a$ is the super vertex formed by contracting vertices 1 and 2, $b$ is the super vertex formed by contracting vertices 3, 4 and 5, and $A$ is formed by contracting the two super vertices $a$ and $b$.

Expansion is relatively simple. Start from the required root $r$ and expand every cycle on the way from $r$ to the root of the contraction tree. Then start from the ancestor $f_r$ of $r$ and expand the cycles on its way to the root, until all vertices have been visited.

### Implementation

```cpp
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

using ll = long long;
constexpr int MAXN = 102;
constexpr int INF = 0x3f3f3f3f;

struct UnionFind {
  int fa[MAXN << 1];

  UnionFind() { memset(fa, 0, sizeof(fa)); }

  void clear(int n) { memset(fa + 1, 0, sizeof(int) * n); }

  int find(int x) { return fa[x] ? fa[x] = find(fa[x]) : x; }

  int operator[](int x) { return find(x); }
};

struct Edge {
  int u, v, w, w0;
};

struct Heap {
  Edge *e;
  int rk, constant;
  Heap *lch, *rch;

  Heap(Edge *_e) : e(_e), rk(1), constant(0), lch(NULL), rch(NULL) {}

  void push() {
    if (lch) lch->constant += constant;
    if (rch) rch->constant += constant;
    e->w += constant;
    constant = 0;
  }
};

Heap *merge(Heap *x, Heap *y) {
  if (!x) return y;
  if (!y) return x;
  if (x->e->w + x->constant > y->e->w + y->constant) swap(x, y);
  x->push();
  x->rch = merge(x->rch, y);
  if (!x->lch || x->lch->rk < x->rch->rk) swap(x->lch, x->rch);
  if (x->rch)
    x->rk = x->rch->rk + 1;
  else
    x->rk = 1;
  return x;
}

Edge *extract(Heap *&x) {
  Edge *r = x->e;
  x->push();
  x = merge(x->lch, x->rch);
  return r;
}

vector<Edge> in[MAXN];
int n, m, fa[MAXN << 1], nxt[MAXN << 1];
Edge *ed[MAXN << 1];
Heap *Q[MAXN << 1];
UnionFind id;

void contract() {
  bool mark[MAXN << 1];
  // Record, for each vertex in the graph, the vertices connected to it.
  for (int i = 1; i <= n; i++) {
    queue<Heap *> q;
    for (int j = 0; j < in[i].size(); j++) q.push(new Heap(&in[i][j]));
    while (q.size() > 1) {
      Heap *u = q.front();
      q.pop();
      Heap *v = q.front();
      q.pop();
      q.push(merge(u, v));
    }
    Q[i] = q.front();
  }
  mark[1] = true;
  for (int a = 1, b = 1, p; Q[a]; b = a, mark[b] = true) {
    // Find the minimum incoming edge and its endpoint, making sure there is no loop.
    do {
      ed[a] = extract(Q[a]);
      a = id[ed[a]->u];
    } while (a == b && Q[a]);
    if (a == b) break;
    if (!mark[a]) continue;
    // Contract the cycle found: relabel the vertices in it and update the total weights.
    for (a = b, n++; a != n; a = p) {
      id.fa[a] = fa[a] = n;
      if (Q[a]) Q[a]->constant -= ed[a]->w;
      Q[n] = merge(Q[n], Q[a]);
      p = id[ed[a]->u];
      nxt[p == n ? b : p] = a;
    }
  }
}

ll expand(int x, int r);

ll expand_iter(int x) {
  ll r = 0;
  for (int u = nxt[x]; u != x; u = nxt[u]) {
    if (ed[u]->w0 >= INF)
      return INF;
    else
      r += expand(ed[u]->v, u) + ed[u]->w0;
  }
  return r;
}

ll expand(int x, int t) {
  ll r = 0;
  for (; x != t; x = fa[x]) {
    r += expand_iter(x);
    if (r >= INF) return INF;
  }
  return r;
}

void link(int u, int v, int w) { in[v].push_back({u, v, w, w}); }

int main() {
  int rt;
  scanf("%d %d %d", &n, &m, &rt);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    link(u, v, w);
  }
  // Make the graph strongly connected
  for (int i = 1; i <= n; i++) link(i > 1 ? i - 1 : n, i, INF);
  contract();
  ll ans = expand(rt, n);
  if (ans >= INF)
    puts("-1");
  else
    printf("%lld\n", ans);
  return 0;
}
```

## References

Uri Zwick. (2013),[Directed Minimum Spanning Trees](http://www.cs.tau.ac.il/~zwick/grad-algo-13/directed-mst.pdf), Lecture notes on "Analysis of Algorithms"

<https://riteme.site/blog/2018-6-18/mdst.html#_3>
