#include <iostream>
using namespace std;

int m, n, c[1010], w[1010], x, t[10010][1010], ts, cnt[10010], dp[1010];

int main() {
  cin >> m >> n;
  for (int i = 1; i <= n; i++) {
    cin >> w[i] >> c[i] >> x;
    t[x][++cnt[x]] = i, ts = max(ts, x);
  }
  // --8<-- [start:core]
  for (int k = 1; k <= ts; k++)          // loop over each group
    for (int i = m; i >= 0; i--)         // loop over knapsack capacity
      for (int j = 1; j <= cnt[k]; j++)  // loop over each item in the group
        if (i >= w[t[k][j]])             // enough capacity left
          dp[i] =
              max(dp[i],
                  dp[i - w[t[k][j]]] + c[t[k][j]]);  // transition just like 0-1 knapsack
  // --8<-- [end:core]
  cout << dp[m] << '\n';
  return 0;
}
