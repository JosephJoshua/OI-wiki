// https://judge.yosupo.jp/submission/407617
#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

// --8<-- [start:var]
using namespace std;

int n;
vector<vector<int>> G;
vector<int> p, rnk;

// --8<-- [end:var]

// --8<-- [start:mcs]
void mcs() {
  vector<int> head(n, 0), prev(n + 1), next(n + 1), label(n + 1, 0);
  p.assign(n + 1, 0);
  rnk.assign(n + 1, 0);
  auto insert = [&](int v) {
    prev[v] = 0;
    next[v] = head[label[v]];
    if (next[v]) prev[next[v]] = v;
    head[label[v]] = v;
  };
  auto erase = [&](int v) {
    if (prev[v])
      next[prev[v]] = next[v];
    else
      head[label[v]] = next[v];
    if (next[v]) prev[next[v]] = prev[v];
  };
  for (int v = 1; v <= n; v++) insert(v);
  int largest = 0;
  for (int i = n; i >= 1; i--) {
    while (!head[largest]) largest--;
    int v = head[largest];
    erase(v);
    p[i] = v;
    rnk[v] = i;
    for (int u : G[v]) {
      if (rnk[u]) continue;
      erase(u);
      label[u]++;
      insert(u);
      largest = max(largest, label[u]);
    }
  }
}

// --8<-- [end:mcs]

// --8<-- [start:core]
int fail_u, fail_v, fail_w;

bool check() {
  vector<vector<int>> bucket(n + 1);
  vector<int> mark(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    int u = p[i], first = 0;
    for (int v : G[u]) {
      if (rnk[v] > rnk[u] && (!first || rnk[v] < rnk[first])) first = v;
    }
    if (first) bucket[first].push_back(u);
  }

  fail_u = 0;
  for (int v = 1; v <= n; v++) {
    // one marking per group; mark[w] == v means w is adjacent to the current v
    for (int w : G[v]) mark[w] = v;
    for (int u : bucket[v]) {
      for (int w : G[u]) {
        if (rnk[w] > rnk[v] && mark[w] != v) {
          // record the last failing vertex in the order and its two neighbors
          if (!fail_u || rnk[u] > rnk[fail_u]) {
            fail_u = u;
            fail_v = v;
            fail_w = w;
          }
          break;
        }
      }
    }
  }
  return !fail_u;
}

// --8<-- [end:core]

vector<int> find_cycle() {
  // For the last failing vertex u in the MCS order, let v = f(u) and w be the neighbor that failed the check
  // there is a path between v and w whose inner vertices avoid u and its neighbors
  // take the shortest such path and add u to get a chordless cycle
  vector<bool> blocked(n + 1, false);
  blocked[fail_u] = true;
  for (int v : G[fail_u]) blocked[v] = true;
  blocked[fail_v] = blocked[fail_w] = false;
  vector<int> from(n + 1, -1);
  queue<int> q;
  q.push(fail_v);
  from[fail_v] = 0;
  while (!q.empty() && from[fail_w] == -1) {
    int v = q.front();
    q.pop();
    for (int w : G[v]) {
      if (blocked[w] || from[w] != -1) continue;
      from[w] = v;
      q.push(w);
    }
  }
  assert(from[fail_w] != -1);
  vector<int> cycle{fail_u};
  for (int v = fail_w; v; v = from[v]) cycle.push_back(v);
  return cycle;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int m;
  cin >> n >> m;
  G.assign(n + 1, {});
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u++;
    v++;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  mcs();
  if (check()) {
    cout << "YES\n";
    for (int i = 1; i <= n; i++) cout << p[i] - 1 << " \n"[i == n];
  } else {
    vector<int> cycle = find_cycle();
    cout << "NO\n" << cycle.size() << '\n';
    for (int i = 0; i < (int)cycle.size(); i++)
      cout << cycle[i] - 1 << " \n"[i + 1 == (int)cycle.size()];
  }
  return 0;
}
