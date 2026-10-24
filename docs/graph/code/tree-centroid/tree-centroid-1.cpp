#include <iostream>
#include <vector>
using namespace std;

constexpr int N = 3e5 + 5;

int n, q;  // number of nodes, number of queries
int fa[N];
vector<int> son[N];
int siz[N],     // subtree size
    ans[N],     // the centroid of the subtree rooted at u is ans[u]
    weight[N];  // node weight (not counting the upward subtree)

void dfs(int u) {
  siz[u] = 1, ans[u] = u;
  int hson = 0;  // heavy child
  for (int v : son[u]) {
    dfs(v);
    siz[u] += siz[v];
    if (siz[v] > weight[u]) weight[u] = siz[v], hson = v;
  }
  if (hson) {
    int p = ans[hson];
    while (p != u) {
      if (max(weight[p], siz[u] - siz[p]) <= siz[u] / 2) {
        ans[u] = p;
        break;
      } else
        p = fa[p];
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin >> n >> q;
  for (int v = 2; v <= n; v++) cin >> fa[v], son[fa[v]].push_back(v);
  dfs(1);
  while (q--) {
    int u;
    cin >> u;
    cout << ans[u] << '\n';
  }
  return 0;
}
