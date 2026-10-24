#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
#define min(x, y) (x < y ? x : y)
#define max(x, y) (x > y ? x : y)
constexpr int N = 5e5 + 5, M = 2e6 + 5;
int n, m;

struct edge {
  int to, nt;
} e[M << 1];

int hd[N], tot;

void add(int u, int v) { e[++tot] = {v, hd[u]}, hd[u] = tot; }

void uadd(int u, int v) { add(u, v), add(v, u); }  // linked forward star (edge list)

using ll = long long;
#define P(x, y) ((ll)min(x, y) * N + (ll)max(x, y))
constexpr int hmod = 1e5 + 7;

struct hash {
  vector<ll> v1[hmod];
  vector<short> v2[hmod];

  short &operator[](ll x) {
    int y = x % hmod;
    for (int i = 0; i < v1[y].size(); i++)
      if (v1[y][i] == x) return v2[y][i];
    v1[y].push_back(x), v2[y].push_back(0);
    return v2[y].back();
  }
} re, be;  // hash table built on vectors, since both time and memory limits are tight

// re: checks for multi-edges; be: marks whether an edge is a bridge

// #define P(x, y) {min(x, y), max(x, y)}
// using pii = pair<int, int>;
// map<pii, int> re, be; // if limits are loose, a map works as the hash table

int dep[N], bz[N], sum[N];  // depth, difference value, subtree sum of differences
int vis[N], fa[N];          // visited flag, group id

void dfs(int x, int pre) {  // compute each vertex's depth and its difference value
  if (dep[x] < dep[pre]) bz[x]++, bz[pre]--;  // edge back to an ancestor: update difference values
  if (dep[x]) return;
  dep[x] = dep[pre] + 1;
  for (int i = hd[x]; i; i = e[i].nt) dfs(e[i].to, x);
}

int dfs2(int x, int pre) {  // compute subtree sums of differences
  if (vis[x] == 1) return sum[x];
  vis[x] = 1, sum[x] = bz[x];
  for (int i = hd[x]; i; i = e[i].nt) {
    int v = e[i].to;
    if (dep[v] > dep[x] && !vis[v]) sum[x] += dfs2(v, x);
  }
  if (sum[x] == 0 && re[P(x, pre)] == 1) be[P(x, pre)] = 1;  // mark bridge
  return sum[x];
}

int cnt;
vector<int> ans[N];

void dfs3(int x) {  // compute biconnected components
  if (fa[x]) return;
  ans[cnt].push_back(x), fa[x] = cnt;
  for (int i = hd[x]; i; i = e[i].nt) {
    int v = e[i].to;
    if (be[P(x, v)] != 1) dfs3(v);  // not a bridge: recurse into the subtree
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n >> m;
  int u, v;
  for (int i = 1; i <= m; i++) cin >> u >> v, uadd(u, v), re[P(u, v)]++;
  for (int i = 1; i <= n; i++)
    if (!dep[i]) dfs(i, 0);
  for (int i = 1; i <= n; i++)
    if (!vis[i]) dfs2(i, 0);
  for (int i = 1; i <= n; i++)
    if (!fa[i]) cnt++, dfs3(i);
  cout << cnt << '\n';
  for (int i = 1; i <= cnt; i++) {
    cout << ans[i].size() << ' ';
    for (int j = 0; j < ans[i].size(); j++) cout << ans[i][j] << ' ';
    cout << '\n';
  }
  return 0;
}