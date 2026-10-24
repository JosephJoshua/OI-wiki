// Verified by https://codeforces.com/gym/101649/problem/G.
// Codes associating I/O streams to files are omitted.
#include <iostream>
#include <vector>
using namespace std;

// --8<-- [start:core]
const int MAXN = 50005;

int n;
// This code assumes nodes are numbered from 1, i.e. i ∈ [1,n]
int siz[MAXN],  // the "size" of this node (nodes in all subtrees + this node)
    weight[MAXN];  // the "weight" of this node, i.e. the max "size" among its subtrees
vector<int> centroids;  // stores the centroids of the tree (as node indices)
vector<int> g[MAXN];

void dfs(int cur, int fa) {  // cur is the current node
  siz[cur] = 1;
  weight[cur] = 0;
  for (int v : g[cur]) {
    if (v != fa) {  // v is the node this directed edge leads to
      dfs(v, cur);
      siz[cur] += siz[v];
      weight[cur] = max(weight[cur], siz[v]);
    }
  }
  weight[cur] = max(weight[cur], n - siz[cur]);
  if (weight[cur] <= n / 2) {  // check against the definition of a centroid
    centroids.push_back(cur);
  }
}

void get_centroids() { dfs(1, 0); }

// --8<-- [end:core]
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  get_centroids();
  if (centroids.size() == 1)
    cout << centroids.front() << '\n';
  else
    cout << min(centroids.front(), centroids.back()) << " "
         << max(centroids.front(), centroids.back()) << '\n';
  return 0;
}
