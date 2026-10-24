#include <cstring>
#include <iostream>
#include <string>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 100;

int T, a[MAXN + 1], h[MAXN + 1];
int g[MAXN + 1], m, n;
int nxt[1 << 16]
       [4];  // transition table: nxt[mask][ch] is the new state after appending ch in state mask
int f[1001]
     [1 << 16];  // DP array: f[i][mask] is the number of ways with length i in state mask
int ans[MAXN +
        1];  // final answer: ans[i] is the number of ways of length m with i matched positions

void add(int &x, int y) { x = (x + y) % MOD; }

int calc(int mask, int x) {  // given the current state mask and current character
                             // x (0~3), return the new state
  int res = 0;
  for (int i = 0; i < n; ++i) g[i + 1] = g[i] + ((mask >> i) & 1);

  for (int i = 1; i <= n; ++i) {
    if (a[i] == x)
      h[i] = g[i - 1] + 1;
    else
      h[i] = max(h[i - 1], g[i]);
  }

  for (int i = 1; i <= n; ++i)
    if (h[i] > h[i - 1]) res |= (1 << (i - 1));

  return res;
}

int popcount(int x) {  // count the 1s in mask (i.e. how many positions matched)
  int res = 0;
  while (x) {
    res += x & 1;
    x >>= 1;
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> T;
  while (T--) {
    string S;
    cin >> S >> m;
    n = S.length();

    memset(f, 0, sizeof(f));
    memset(ans, 0, sizeof(ans));
    memset(a, 0, sizeof(a));

    for (int i = 0; i < n; ++i) {
      if (S[i] == 'A') a[i + 1] = 0;
      if (S[i] == 'C') a[i + 1] = 1;
      if (S[i] == 'G') a[i + 1] = 2;
      if (S[i] == 'T') a[i + 1] = 3;
    }

    int lim = (1 << n);
    for (int i = 0; i < lim; ++i)
      for (int j = 0; j < 4; ++j) nxt[i][j] = calc(i, j);

    f[0][0] = 1;
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < lim; ++j)
        if (f[i][j])
          for (int k = 0; k < 4; ++k) add(f[i + 1][nxt[j][k]], f[i][j]);

    for (int i = 0; i < lim; ++i) add(ans[popcount(i)], f[m][i]);

    for (int i = 0; i <= n; ++i) cout << ans[i] << '\n';
  }

  return 0;
}
