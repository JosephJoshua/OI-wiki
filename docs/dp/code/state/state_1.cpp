#include <algorithm>
#include <iostream>
using namespace std;
long long sta[2005], sit[2005], f[15][2005][105];
int n, k, cnt;

void dfs(int x, int num, int cur) {
  if (cur >= n) {  // found a new valid state
    sit[++cnt] = x;
    sta[cnt] = num;
    return;
  }
  dfs(x, num, cur + 1);  // no king at position cur
  dfs(x + (1 << cur), num + 1,
      cur + 2);  // put a king at cur; its neighbor cannot hold a king
}

bool compatible(int j, int x) {
  if (sit[j] & sit[x]) return false;
  if ((sit[j] << 1) & sit[x]) return false;
  if (sit[j] & (sit[x] << 1)) return false;
  return true;
}

int main() {
  cin >> n >> k;
  dfs(0, 0, 0);  // first precompute all valid states of one row
  for (int j = 1; j <= cnt; j++) f[1][j][sta[j]] = 1;
  for (int i = 2; i <= n; i++)
    for (int j = 1; j <= cnt; j++)
      for (int x = 1; x <= cnt; x++) {
        if (!compatible(j, x)) continue;  // skip invalid transitions
        for (int l = sta[j]; l <= k; l++) f[i][j][l] += f[i - 1][x][l - sta[j]];
      }
  long long ans = 0;
  for (int i = 1; i <= cnt; i++) ans += f[n][i][k];  // sum up the answer
  cout << ans << endl;
  return 0;
}