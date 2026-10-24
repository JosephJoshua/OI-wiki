#include <cstring>
#include <iostream>
#include <vector>

constexpr int MXN = 40005;
using namespace std;
vector<int> v[MXN];
vector<int> w[MXN];

int fa[MXN][31], cost[MXN][31], dep[MXN];
int n, m;
int a, b, c;

// dfs, used to prepare for the lca algorithm. Takes two arguments: the start node of the dfs and its parent.
void dfs(int root, int fno) {
  // Initialize: the 2^0 = 1st ancestor is its parent, and dep is 1 more than the parent's.
  fa[root][0] = fno;
  dep[root] = dep[fa[root][0]] + 1;
  // Initialize the other ancestors: the 2^i-th ancestor is the 2^(i-1)-th ancestor
  // of the 2^(i-1)-th ancestor.
  for (int i = 1; i < 31; ++i) {
    fa[root][i] = fa[fa[root][i - 1]][i - 1];
    cost[root][i] = cost[fa[root][i - 1]][i - 1] + cost[root][i - 1];
  }
  // Go through the children and run dfs on them.
  int sz = v[root].size();
  for (int i = 0; i < sz; ++i) {
    if (v[root][i] == fno) continue;
    cost[v[root][i]][0] = w[root][i];
    dfs(v[root][i], root);
  }
}

// lca. Use binary lifting to find the lca of x and y.
int lca(int x, int y) {
  // Make y deeper than x.
  if (dep[x] > dep[y]) swap(x, y);
  // Bring y to the same depth as x.
  int tmp = dep[y] - dep[x], ans = 0;
  for (int j = 0; tmp; ++j, tmp >>= 1)
    if (tmp & 1) ans += cost[y][j], y = fa[y][j];
  // If now y = x, then x and y are both their own ancestor.
  if (y == x) return ans;
  // Otherwise, find the first two nodes that are not their common ancestors.
  for (int j = 30; j >= 0 && y != x; --j) {
    if (fa[x][j] != fa[y][j]) {
      ans += cost[x][j] + cost[y][j];
      x = fa[x][j];
      y = fa[y][j];
    }
  }
  // Return the result.
  ans += cost[x][0] + cost[y][0];
  return ans;
}

void Solve() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // Initialize the ancestor array fa, the cost array cost and the depth array dep.
  memset(fa, 0, sizeof(fa));
  memset(cost, 0, sizeof(cost));
  memset(dep, 0, sizeof(dep));
  // Read the tree: n nodes in total, m queries, each asking for the lca of two nodes.
  cin >> n >> m;
  // Initialize the tree edges and edge weights
  for (int i = 1; i <= n; ++i) {
    v[i].clear();
    w[i].clear();
  }
  for (int i = 1; i < n; ++i) {
    cin >> a >> b >> c;
    v[a].push_back(b);
    v[b].push_back(a);
    w[a].push_back(c);
    w[b].push_back(c);
  }
  // Run dfs in order to compute lca.
  dfs(1, 0);
  for (int i = 0; i < m; ++i) {
    cin >> a >> b;
    cout << lca(a, b) << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--) Solve();
  return 0;
}
