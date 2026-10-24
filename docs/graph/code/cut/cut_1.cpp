/*
Luogu P3388 [Template] Cut Vertices (Articulation Points)
*/
#include <iostream>
#include <vector>
using namespace std;
int n, m;  // n: number of vertices, m: number of edges
int dfn[100001], low[100001], idx, res;
// dfn: timestamp of each vertex
// low: smallest timestamp reachable without going through the parent; idx: timestamp counter; res: number of answers
bool vis[100001], flag[100001];  // flag: answer; vis: visited mark
vector<int> edge[100001];        // adjacency lists

void Tarjan(int u, int fa) {  // u: current vertex, fa: its parent
  vis[u] = true;              // mark
  low[u] = dfn[u] = ++idx;    // assign timestamp
  int child = 0;              // number of children of this vertex
  for (const auto &v : edge[u]) {  // visit all neighbors of this vertex (C++11)
    if (!vis[v]) {
      child++;                       // one more child
      Tarjan(v, u);                  // recurse
      low[u] = min(low[u], low[v]);  // update the smallest reachable timestamp
      if (fa != u && low[v] >= dfn[u] && !flag[u]) {  // main logic
        // if u is not the root, the smallest vertex reachable from v without the parent meets the cut-vertex condition, and u is not marked yet
        // the condition: without u, v cannot reach above u, i.e. it reaches at most u
        flag[u] = true;
        res++;  // count the answer
      }
    } else if (v != fa) {
      // if v is not the parent, update the smallest reachable timestamp
      low[u] = min(low[u], dfn[v]);
    }
  }
  // main logic: the root needs at least 2 children
  if (fa == u && child >= 2 && !flag[u]) {
    flag[u] = true;
    res++;  // count the answer
  }
}

int main() {
  cin >> n >> m;                  // read input
  for (int i = 1; i <= m; i++) {  // note: vertices are numbered from 1
    int x, y;
    cin >> x >> y;
    edge[x].push_back(y);
    edge[y].push_back(x);
  }  // store the graph with vectors
  for (int i = 1; i <= n; i++)  // the graph may be disconnected
    if (!vis[i]) {
      idx = 0;       // reset the timestamp to 0
      Tarjan(i, i);  // start from vertex i, with itself as parent
    }
  cout << res << endl;
  for (int i = 1; i <= n; i++)
    if (flag[i]) cout << i << " ";  // print the result
  return 0;
}
