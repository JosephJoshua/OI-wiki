#include <algorithm>
#include <iostream>
using namespace std;
constexpr int N = 105;
int n, m, ans;

struct Node {
  int a, b;  // a is the time, b is the value
  double f;
} node[N];

bool operator<(Node p, Node q) { return p.f > q.f; }

int f(int t, int v) {  // max value of the remaining items with the current time
  int tot = 0;
  for (int i = 1; t + i <= n; i++)
    if (v >= node[t + i].a) {
      v -= node[t + i].a;
      tot += node[t + i].b;
    } else
      return (int)(tot + v * node[t + i].f);
  return tot;
}

void work(int t, int p, int v) {
  ans = max(ans, v);
  if (t > n) return;                         // base case: there are only n items
  if (f(t, p) + v > ans) work(t + 1, p, v);  // optimality pruning
  if (node[t].a <= p) work(t + 1, p - node[t].a, v + node[t].b);  // feasibility pruning
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> m >> n;
  for (int i = 1; i <= n; i++) {
    cin >> node[i].a >> node[i].b;
    node[i].f = 1.0 * node[i].b / node[i].a;  // f is the value per unit of time
  }
  sort(node + 1, node + n + 1);  // sort by value per unit of time
  work(1, m, 0);
  cout << ans << '\n';
  return 0;
}
