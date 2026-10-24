#include <algorithm>
#include <iostream>
using namespace std;

int fa[1010];  // define parent
int n, m, k;

struct edge {
  int u, v, w;
};

int l;
edge g[10010];

void add(int u, int v, int w) {
  l++;
  g[l].u = u;
  g[l].v = v;
  g[l].w = w;
}

// standard DSU
int findroot(int x) { return fa[x] == x ? x : fa[x] = findroot(fa[x]); }

void Merge(int x, int y) {
  x = findroot(x);
  y = findroot(y);
  fa[x] = y;
}

bool cmp(edge A, edge B) { return A.w < B.w; }

// Kruskal's algorithm
void kruskal() {
  int tot = 0;  // number of edges chosen
  int ans = 0;  // total cost
  for (int i = 1; i <= m; i++) {
    int xr = findroot(g[i].u), yr = findroot(g[i].v);
    if (xr != yr) {        // if the roots differ
      Merge(xr, yr);       // merge
      tot++;               // one more edge
      ans += g[i].w;       // add the cost
      if (tot == n - k) {  // check whether the edge count gives k marshmallows
        cout << ans << '\n';
        return;
      }
    }
  }
  cout << "No Answer\n";  // cannot be connected
}

int main() {
  cin >> n >> m >> k;
  if (n == k) {  // handle the edge case
    cout << "0\n";
    return 0;
  }
  for (int i = 1; i <= n; i++) {  // initialize
    fa[i] = i;
  }
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    add(u, v, w);  // add edge
  }
  sort(g + 1, g + m + 1, cmp);  // sort by edge weight first
  kruskal();
  return 0;
}
