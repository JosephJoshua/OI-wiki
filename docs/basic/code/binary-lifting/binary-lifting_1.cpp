#include <cstdio>
using namespace std;

constexpr int mod = 1000000007;

int modadd(int a, int b) {
  if (a + b >= mod) return a + b - mod;  // subtract instead of taking mod, which is faster
  return a + b;
}

int vi[1000005];

int go[60][1000005];  // make the array a bit larger to avoid out-of-bounds; put the smaller dimension first
int sum[60][1000005];

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", vi + i);
  }

  for (int i = 1; i <= n; ++i) {
    go[0][i] = (i + k) % n + 1;
    sum[0][i] = vi[i];
  }

  // m <= 10^18, so only levels 0..59 are needed
  for (int i = 1; i < 60; ++i) {
    for (int j = 1; j <= n; ++j) {
      go[i][j] = go[i - 1][go[i - 1][j]];
      sum[i][j] = modadd(sum[i - 1][j], sum[i - 1][go[i - 1][j]]);
    }
  }

  long long m;
  scanf("%lld", &m);

  int ans = 0;
  int curx = 1;
  for (int i = 0; m; ++i) {
    if (m & (1ll << i)) {  // see bitwise operations; checks whether bit i of m is 1
      ans = modadd(ans, sum[i][curx]);
      curx = go[i][curx];
      m ^= 1ll << i;  // clear bit i
    }
  }

  printf("%d\n", ans);
}
