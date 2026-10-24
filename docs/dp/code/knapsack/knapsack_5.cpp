#include <iostream>
using namespace std;

string a, b;
int n, W, w[10010], v[10010], cnt[10010], dp[10010];

int main() {
  cin >> a >> b >> n;
  for (int i = 1; i <= n; i++) {
    cin >> w[i] >> v[i] >> cnt[i];
  }
  if (a.size() < 5) a = '0' + a;
  if (b.size() < 5) b = '0' + b;
  int h1 = (a[0] - '0') * 10 + (a[1] - '0'),
      m1 = (a[3] - '0') * 10 + (a[4] - '0');
  int h2 = (b[0] - '0') * 10 + (b[1] - '0'),
      m2 = (b[3] - '0') * 10 + (b[4] - '0');
  W = (h2 - h1) * 60 + (m2 - m1);
  // --8<-- [start:core]
  for (int i = 1; i <= n; i++) {
    if (cnt[i] == 0) {  // unlimited count: use the unbounded knapsack core code
      for (int weight = w[i]; weight <= W; weight++) {
        dp[weight] = max(dp[weight], dp[weight - w[i]] + v[i]);
      }
    } else {  // limited count: use the bounded knapsack core code, which also handles 0-1 knapsack
      for (int weight = W; weight >= w[i]; weight--) {
        for (int k = 1; k * w[i] <= weight && k <= cnt[i]; k++) {
          dp[weight] = max(dp[weight], dp[weight - k * w[i]] + k * v[i]);
        }
      }
    }
  }
  // --8<-- [end:core]
  cout << dp[W] << '\n';
  return 0;
}
